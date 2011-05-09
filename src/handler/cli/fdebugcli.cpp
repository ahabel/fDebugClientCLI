#include "string.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fnmatch.h>

#include "global.h"
#include "handler/cli/fdebugcli.h"
#include "json/cJSON.h"

#include "fdebugconfig.h"
#include <fstream>

// XML reader libraries for parsing fDebug Variables
#include "libxml/xmlreader.h"
#include "libxml/parser.h"
#include "libxml/tree.h"
#include "libxml/xmlmemory.h"


fDebugCli::fDebugCli() {
	this->config = fDebugConfig::getInstance();
}

bool fDebugCli::process(fDebugMessage *message) {
   if (!this->applyFilter(message)) {
      return false;
   }
   
   switch(message->type) {
      case FDEBUG_CONTROL: {
         this->handleControl(message);
         break;
      }
      case FDEBUG_MESSAGE: {
         this->handleMessage(message);
         break;
      }
      case FDEBUG_WARNING: {
         this->handleWarning(message);
         break;
      }
      case FDEBUG_ERROR: {
         this->handleError(message);
         break;
      }
      case FDEBUG_FATAL: {
         this->handleFatal(message);
         break;
      }
      case FDEBUG_VARIABLES: {
         this->handleVariables(message);
         break;
      }
   }
   
   return true;
}

bool fDebugCli::applyFilter(fDebugMessage *message) {
   if (this->config->options.filter) {
      cJSON * payload = message->getPayload();
      char *msg = cJSON_GetObjectItem(payload, "message")->valuestring;

      switch(this->config->options.filterList.type) {
         case FILTER_FNMATCH: {
            if (fnmatch(this->config->options.filterList.pattern, msg, 0) == FNM_NOMATCH) {
               return false;
            }
            break;
         }
      }
   }

   return true;
}

void fDebugCli::printDetails(fDebugMessage *message) {
   messageDetails details = message->getFullMessage();
   printf("---------------------------------------------------------------------------------------\n"
      "[MESSAGE]\n"
      "%s%s%s()\n"
      "Line %d in %s\n%s\n\n%s\n",
      details.className.c_str(),
      details.type.c_str(),
      details.method.c_str(),
      details.line,
      details.file.c_str(),
      details.version.c_str(),
      message->message.c_str()
   );
}

void fDebugCli::handleControl(fDebugMessage *message) {
   if (!this->config->options.control) { return; }
	// {"type":"CONTROL","payload":{"action":"HELO","url":"\/de\/site\/index.xml","server":"bluepoints.mobile"}}
	// {"type":"CONTROL","payload":{"action":"PING"}}
	// {"type":"CONTROL","payload":{"action":"QUIT"}}
	
   printf(NORMAL "[CONTROL]  %s received\n", message->message.c_str());
}

void fDebugCli::handleMessage(fDebugMessage *message) {
   if (!this->config->filter.message) { return; }
   printf(NORMAL);
   
   if (!this->config->options.details) {
      printf("[MESSAGE]  %s\n", message->message.c_str());
   } else {
      this->printDetails(message);
   }
}

void fDebugCli::handleWarning(fDebugMessage *message) {
   if (!this->config->filter.warning) { return; }
   printf(COLOR_WARNING);
   if (!this->config->options.details) {
      printf("[WARNING]  %s\n", message->message.c_str());
   } else {
      this->printDetails(message);
   }
   printf(NORMAL);
}

void fDebugCli::handleError(fDebugMessage *message) {
   if (!this->config->filter.error) { return; }
   printf(COLOR_ERROR);
   if (!this->config->options.details) {
      printf("[ERROR]  %s\n", message->message.c_str());
   } else {
      this->printDetails(message);
   }
   printf(NORMAL);
}

void fDebugCli::handleFatal(fDebugMessage *message) {
   if (!this->config->filter.fatal) { return; }
   printf(COLOR_FATAL);
   if (!this->config->options.details) {
      printf("[FATAL]  %s\n", message->message.c_str());
   } else {
      this->printDetails(message);
   }
   printf(NORMAL);
}

void fDebugCli::handleVariables(fDebugMessage *message) {
   if (!this->config->options.variables) { return; }
   
	/*
	 * {"type":    "VARIABLES",
	 *  "payload":
	 *     {"xml":"<?xml version=\"1.0\" encoding=\"utf-8\" ?>
	 *             <vardump>
	 *                <vargroup name=\"OTHER\" type=\"\">
	 *                <vargroup name=\"fVars\" type=\"\">
	 *                <vargroup name=\"VAR\" type=\"\">
	 *                   <var key=\"siteLang\">de<\/var>
	 *                </vargroup>
	 *             </vardump>
	 */
	
	LIBXML_TEST_VERSION
	
	printf(NORMAL);
	
	xmlDocPtr  doc;
	xmlNodePtr root,group;
	
	cJSON * payload = message->getPayload();
	char *xml = cJSON_GetObjectItem(payload, "xml")->valuestring;
	
	doc = xmlReadMemory(xml, strlen(xml), "noname.xml", NULL, 0);
	if (doc == NULL) {
		printf("parsing xml failed\n");
	}
	
	root = xmlDocGetRootElement(doc);
	if (root == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}
	
	if (xmlStrcmp(root->name, (const xmlChar*) "vardump")) {
		fprintf(stderr, "invalid documentElement");
		xmlFreeDoc(doc);
		return;
	}
	
	// loop <vargroup>
	for(group = root->children; group != NULL; group = group->next) {
		this->processVariablesGroups(group);
	}
	
	xmlFree(root);
	xmlFree(group);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	delete [] payload;
	return;
}

void fDebugCli::processVariablesGroups(xmlNodePtr group) {
	xmlChar *name = xmlGetProp(group, (const xmlChar*)"name");
	printf(BOLD "-- %s\n" NORMAL, name);
   
	xmlNodePtr cNode;
	
	for(cNode = group->children; cNode != NULL; cNode = cNode->next) {
		// sub <vargroup>
		if (strcmp((const char*)cNode->name, "vargroup") == 0) {
			printf("\t");
			this->processVariablesGroups(cNode);
			printf("\n");
			continue;
		}
		
		// <var>
		if (strcmp((const char*)cNode->name, "var") == 0) {
			xmlChar *key   = xmlGetProp(cNode, (const xmlChar*)"key");
	   	xmlChar *value = xmlNodeGetContent(cNode);
	   	printf("\tvar: %s -> %s\n", key, value);
	   	xmlFree(key);
	   	xmlFree(value);
		}
   }
	
	xmlFree(name);
}




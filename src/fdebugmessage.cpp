#include "string.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

#include "global.h"
#include "fdebugexception.h"
#include "fdebugmessage.h"
#include "json/cJSON.h"


fDebugMessage::fDebugMessage(string message) {
	this->parse(message);
}

bool fDebugMessage::parse(string message) {
   cJSON *root = cJSON_Parse(message.c_str());

   if (root->type != 6) {
		// message is not an json object / 6 = CJSON_OBJECT
		throw fDebugException("Parsing json failed");
	}
   
	this->json    = message;
	this->payload = cJSON_GetObjectItem(root, "payload");
	string type   = cJSON_GetObjectItem(root, "type")->valuestring;
	
	if (type == "CONTROL") {
	   this->type = FDEBUG_CONTROL;
	   this->message = cJSON_GetObjectItem(this->payload, "action")->valuestring;
	} else if (type == "VARIABLES") {
	   this->type = FDEBUG_VARIABLES;
	} else if (type == "SOURCE") {
	   this->type = FDEBUG_SOURCE;
	} else if (type == "MESSAGE") {
	   string level  = cJSON_GetObjectItem(this->payload, "level")->valuestring;
	   this->message = cJSON_GetObjectItem(this->payload, "message")->valuestring;
	   
	   if (level == "MESSAGE") { this->type = FDEBUG_MESSAGE; } else
	   if (level == "WARNING") { this->type = FDEBUG_WARNING; } else
	   if (level == "ERROR")   { this->type = FDEBUG_ERROR; } else 
	   if (level == "FATAL")   { this->type = FDEBUG_FATAL; } 
	} else {
	   printf("*WARNING* Unhandled fdebug message received: %s\n", type.c_str());
	}
	
	delete [] root;
	return true;
}

int fDebugMessage::getType() {
	return this->type;
}

cJSON* fDebugMessage::getPayload() {
	return this->payload;
}

messageDetails fDebugMessage::getFullMessage() {
   /*
    {"type":"MESSAGE","payload":
        {"context":"fCore",
         "level":"MESSAGE",
         "message":"process complete",
         "line":1028,
         "class":"fSite",
         "method":"run",
         "type":"->",
         "file":"fsite.lib.fcmsv5.php",
         "version":"$Revision: 1.7 $ ($Date: 2011/01/15 01:17:44 $)"
        }
      }
    */
   messageDetails details;
   details.context   = cJSON_GetObjectItem(this->payload, "context")->valuestring;
   details.level     = cJSON_GetObjectItem(this->payload, "level")->valuestring;
   details.line      = cJSON_GetObjectItem(payload, "line")->valueint;
   details.className = cJSON_GetObjectItem(payload, "class")->valuestring;
   details.method    = cJSON_GetObjectItem(payload, "method")->valuestring;
   details.type      = cJSON_GetObjectItem(payload, "type")->valuestring;
   details.file      = cJSON_GetObjectItem(payload, "file")->valuestring;
   details.version   = cJSON_GetObjectItem(payload, "version")->valuestring;
   return details;
}








#include "string.h"
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

#include "fsocket/fsocket.h"
#include "fdebugexception.h"
#include "fdebugconfig.h"
#include "fdebugclient.h"
#include "fdebugmessage.h"
#include "handler/cli/fdebugcli.h"
#include "json/cJSON.h"
#include <string>

using namespace std;

fDebugClient::fDebugClient(fSocket *socket) {
   this->socket = socket;
}

char* fDebugClient::getServer() {
	return this->server;
}

char* fDebugClient::getURL() {
	return this->url;
}

bool fDebugClient::process() {
   try {
      if (!this->clientHasData()) {
         printf("No data from client\n");
         return false;
      }
      
      if (!this->init()) {
         printf("Initializing client failed\n");
         return false;
      }
      
      fDebugCli *handler = new fDebugCli();
      while (this->clientHasData()) {
         try {
            fDebugMessage *message = new fDebugMessage(this->buffer);
            handler->process(message);
            delete message;
         } catch(fDebugException e) {
            printf("MESSAGE ERROR: %s\n", e.getMessage());
         }
      }
	} catch(fSocketException e) {}
	
	return true;
}

bool fDebugClient::init() {
	// {"type":"CONTROL","payload":{"action":"HELO","url":"\/de\/site\/index.xml","server":"bluepoints.mobile"}}
	cJSON *root = cJSON_Parse(this->buffer.c_str());
	if (root->type != 6) {
		// message is not an json object / 6 = CJSON_OBJECT
		printf("ERROR: parsing json failed: %s\n", this->buffer.c_str());
		return false;
	}
	
	cJSON *payload = cJSON_GetObjectItem(root, "payload");
	char *action   = cJSON_GetObjectItem(payload, "action")->valuestring;
	this->server   = cJSON_GetObjectItem(payload, "server")->valuestring;
	this->url      = cJSON_GetObjectItem(payload, "url")->valuestring;
	
	if (strcmp(action, "HELO") != 0) {
		printf("Client did not start with expected HELO\n");
		return false;
	}
	
	printf("\n---------------------------------------------------------------------------------------\nConnection from %s (%s) (%s)\n",
	   this->server,
	   this->socket->getRemoteAddress(),
	   this->url
	);
	
	delete [] root;
	delete [] payload;
	delete [] action;
	return true;
}

bool fDebugClient::clientHasData() {
   this->buffer = this->socket->receive();
   this->socket->send("OK\n");
   return true;
}



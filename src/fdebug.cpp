#include <iostream>
#include <getopt.h>
#include "string.h"
#include <stdlib.h>
#include <stdio.h>

#include "fsocket/fsocket.h"
#include "fdebugclient.h"
#include "json/cJSON.h"

#include "fdebugconfig.h"
#include "fdebugexception.h"

using namespace std;

int main(int argc, char **argv) {
	char in[2];
	printf(BOLD "fDebug Client %s" NORMAL " - Copyright (c) by Andreas Habel\n\n", FDEBUG_VERSION);
	
	// init fdebug config
	fDebugConfig *config = fDebugConfig::getInstance();
	config->init(argc, argv);
	
	fSocket *socket = new fSocket(config->getPort());
	
	while (1) {
		try {
		   socket->acceptConnections();
		   
		   fDebugClient *client = new fDebugClient(socket);
		   
		   // need to confirm new connections?
			if (config->options.strict) {
				printf("Accept incoming connection from %s ? [N/y]", socket->getRemoteAddress());
				cin.getline(in, 2, '\n');
				if (strcasecmp(in, (const char*)"Y") != 0) {
					socket->close();
					delete client;
					continue;
				}
			}
			
			//TODO: verify client (allowed hosts?)
			if (!client->process()) {
				printf("Handling request failed!\n");
			}
			
			socket->close();
			delete client;
		} catch(fDebugException e) {
			printf("Exception caught: %s", e.getMessage());
			exit(1);
		}
	}
	
	return 0;
}

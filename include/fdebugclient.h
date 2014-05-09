/**
 * @author Andreas Habel
 * $Id: fdebugclient.h,v 1.6 2011/01/16 20:54:02 virus-d Exp $
 *
 * @class fDebugClient
 * @brief Client Connection/Session Manager
 *
 * @package fDebug
 */


#ifndef FDEBUGCLIENT_H_
#define FDEBUGCLIENT_H_

#include <netinet/in.h>
#include <string>
#include "fsocket/fsocket.h"
using namespace std;


class fDebugClient {
public:
   /**
	 * fDebugClient Constructor
	 *
	 * @param socket Socket handle created by fDebugSocket
	 * @param addr Socket address struct
	 */
	fDebugClient(fSocket *socket);
   
	/**
	 * Main process
	 * After a new client has connected, it initializes the client session
	 * and loops over the fetched data from the socket to process the received messages
	 */
	bool process();
   
	/**
	 * Return information about the connected client
	 * @return current server name
	 */
	char* getServer();

	/**
	 * Return information about the connected client
	 * @return current server URL (domain.tld/de/site/index.xml)
	 */
	char* getURL();

	/**
	 * Return information about the connected client
	 * @return client remote address
	 */
	char* getRemoteAddress();
private:

	/**
	 * Initialize a new client connection
	 * - checks if received data is valid JSON formatted data and if it is a correct HELO
	 * (see fDebug Protocol for information on the handshake process)
	 * - set server name
	 * - set server URL
	 * -
	 *
	 * @return true if initialization was successfull
	 */
	bool init();

	/**
	 * Fetches new data from the socket and stores them in the buffer property
	 */
	bool clientHasData();
   
	/**
    * @property buffer
    * Message buffer
    */
	string buffer;
   
	/**
	 * @property sock
	 * Socket handle set by construct()
	 */
	fSocket *socket;
	
   /**
    * @property server
    * server name
    */
	char *server;

	/**
	 * @property url
	 * server URL
	 */
	char *url;
};

#endif /*FDEBUGCLIENT_H_*/

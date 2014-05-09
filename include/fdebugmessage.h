/**
 * @author Andreas Habel
 * $Id: fdebugmessage.h,v 1.8 2011/01/15 01:17:44 virus-d Exp $
 *
 * @class fDebugMessage
 * @brief Message container object
 *
 * @package fDebug
 */

#ifndef FDEBUGMESSAGE_H_
#define FDEBUGMESSAGE_H_

#include "json/cJSON.h"
#include <string>
using namespace std;

struct messageDetails {
   string context;
   string level;
   int    line;
   string className;
   string method;
   string type;
   string file;
   string version;
};

class fDebugMessage {
private:

   /**
    * Parses and analyzes the given message
    * @param message fdebug message
    */
	bool parse(string message);

	/**
	 * @property json
	 * Holds the complete JSON formatted message
	 */
	string json;

	/**
	 * @property payload
	 * Holds the message content as a cJSON object
	 */
	cJSON *payload;
	

public:
	string message;
	
	/**
    * @property type
    * Holds the message type (WARNING, VARIABLES, FATAL, ...)
    */
   int type;
	
	/**
	 * Constructor
	 * @param message fdebug message
	 */
	fDebugMessage(string message);

	/**
	 * Returns the message type
	 * @return: message type
	 * @see type
	 */
	int getType();

	/**
	 * Returns the message content
	 * @return message content
	 * @see payload
	 */
	cJSON* getPayload();
	
	messageDetails getFullMessage();
};

#endif /*FDEBUGMESSAGE_H_*/

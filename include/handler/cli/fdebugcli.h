/**
 * @author Andreas Habel
 * $Id: fdebugcli.h,v 1.3 2011/01/15 01:36:36 virus-d Exp $
 *
 * @class fDebugCli
 * @brief Commandline Output Handler
 *
 * @package fDebug
 */


#ifndef FDEBUGCLI_H_
#define FDEBUGCLI_H_

#include <netinet/in.h>
#include "fdebugmessage.h"
#include "fdebugconfig.h"

#include "libxml2/libxml/tree.h"


class fDebugCli {
public:
	fDebugCli();

	/**
	 * Process a fdebug message
	 *
	 * @param message fDebugMessage
	 */
	bool process(fDebugMessage *message);

private:

	/**
	 * Apply configured filters to the message
	 *
	 * @param message fDebugMessage
	 * @return
    *   - false - one or more filters has matched the message payload
	 *   - true - none of the configured filters has matched
	 */
	bool applyFilter(fDebugMessage *message);
   
	void printDetails(fDebugMessage *message);
	
	/**
	 * Internal handler for messages of type CONTROL
	 *
	 * @param message fDebugMessage
	 */
	void handleControl(fDebugMessage *message);

	/**
	 * Internal handler for messages of type MESSAGE
	 *
	 * @param message fDebugMessage
	 */
	void handleMessage(fDebugMessage *message);
	void handleWarning(fDebugMessage *message);
	void handleError(fDebugMessage *message);
	void handleFatal(fDebugMessage *message);
	
	/**
	 * Internal handler for messages of type VARIABLES
	 *
	 * @param message fDebugMessage
	 */
	void handleVariables(fDebugMessage *message);

	/**
	 * Helper function for processing variables recursivly
	 *
	 * @param group XML Node
	 */
	void processVariablesGroups(xmlNodePtr group);
	
	/**
	 * @property config
	 *
	 * Reference to the fDebugConfig instance
	 */
	fDebugConfig *config;
};

#endif /*FDEBUGCLI_H_*/

/**
 * @author Andreas Habel
 * $Id: fdebugconfig.h,v 1.6 2011/01/12 22:01:29 virus-d Exp $
 *
 * @package fDebug
 */


#include "global.h"

#ifndef FDEBUGCONFIG_H_
#define FDEBUGCONFIG_H_


/**
 * @struct displayFilter
 * @brief
 * Message filter display flags
 */
struct displayFilter {
   /**
    * @property message
    * If set to bool(true) items of type MESSAGE will be displayed
    */
	bool message;

	/**
    * @property warning
    * If set to bool(true) items of type MESSAGE will be displayed
    */
	bool warning;

	/**
    * @property error
    * If set to bool(true) items of type MESSAGE will be displayed
    */
	bool error;

	/**
    * @property fatal
    * If set to bool(true) items of type MESSAGE will be displayed
    */
	bool fatal;
};



#define FILTER_FNMATCH 1

/**
 * @struct messageFilter
 * @brief
 * Filter configuration
 */
struct messageFilter {

   /**
    * @property type
    * filter type
    */
   int type;

   /**
    * @property pattern
    * filter pattern to match message payload
    */
   char * pattern;
};



/**
 * @struct debugOptions
 * @brief Configuration Options
 */
struct debugOptions {

   /**
    * @property port
    * fDebug port to use for listering for incoming connections
    * The default port is set to 5005
    */
	int port;

	/**
    * @property control
    * show fdebug control messages
	 */
	bool control;

	/**
	 * @property details
	 * show message details
	 */
	bool details;

	/**
	 * @property variables
	 * show fdebug variables
	 */
	bool variables;

	/**
	 * @property strict
	 * ask before accepting connections from unknown hosts
	 */
	bool strict;

	/**
	 * @property filter
	 * toggle enable filters
	 */
	bool filter;

	/**
	 * @property filterList
	 * list of configured and load message filters
	 *
	 * @see messageFilter for detailed information on the messageFilter struct
	 */
	messageFilter filterList;


	// generic options

	/**
	 * @property debug
	 * enable verbose mode
	 */
	bool debug;
};



/**
 * @class fDebugConfig
 * @brief Configuration and CLI parameter Manager
 */
class fDebugConfig {
public:
	static fDebugConfig* getInstance();
	
	/**
	 * Initialize the Configuration manager
	 * @param argc cli arguments from main method
	 * @param argv cli arguments from main method
	 */
	void   init(int argc, char **argv);

	/**
	 * Return the port fDebug should listen for new connections
	 * @return fdebug port for incoming connections
	 * Default: 5005
	 */
	int    getPort();
	
	/**
	 * @property filter
	 * list of configured filters
	 * @see displayFilter
	 */
	displayFilter filter;

	/**
	 * @property options
	 * main fdebug options
	 * @see debugOptions
	 */
	debugOptions  options;
	

private:
	static fDebugConfig *instance;
	
	fDebugConfig() {}
	
	/**
	 * Print the usage description for fDebug (--help)
	 */
	void printUsage();

	/**
	 * Inits the display filter settings
	 * @see displayFilter
	 */
	void initDisplayFilter(displayFilter filter);
};

#endif /*FDEBUGCONFIG_H_*/

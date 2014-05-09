/**
 * @author Andreas Habel
 * $Id: fdebugconfig.h,v 1.6 2011/01/12 22:01:29 virus-d Exp $
 *
 * @package fDebug
 */


#include "config/displayfilter.h"
#include "config/messagefilter.h"
#include "config/options.h"


#ifndef FDEBUGCONFIG_H_
#define FDEBUGCONFIG_H_


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

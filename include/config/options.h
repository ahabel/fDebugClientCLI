/**
 * @author Andreas Habel
 * @package fDebug
 */

#ifndef FDEBUGCONFIG_OPTIONS_H_
#define FDEBUGCONFIG_OPTIONS_H_

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

#endif

/**
 * @author Andreas Habel
 * @package fDebug
 */

#ifndef FDEBUGCONFIG_MESSAGEFILTER_H_
#define FDEBUGCONFIG_MESSAGEFILTER_H_


/**
 * Flag for FNMATCH filter functions
 */
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

#endif

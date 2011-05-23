/**
 * @author Andreas Habel
 * @package fDebug
 */

#ifndef FDEBUGCONFIG_DISPLAYFILTER_H_
#define FDEBUGCONFIG_DISPLAYFILTER_H_

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


#endif

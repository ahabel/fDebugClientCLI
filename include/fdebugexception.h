/**
 * @author Andreas Habel
 * $Id: fdebugexception.h,v 1.3 2010/09/03 15:52:46 virus-d Exp $
 *
 * @class fDebugException
 * @brief fDebug Exception
 *
 * @package fDebug
 */

#ifndef FDEBUGEXCEPTION_H_
#define FDEBUGEXCEPTION_H_

class fDebugException {
private:

   /**
    * @property message
    * Exception message content
    */
	char *message;

public:

	/**
	 * Constructor
	 * @param message exception content
	 */
	fDebugException(const char * message);

	/**
	 * Returns the exception content
	 * @return exception message
	 */
	char* getMessage();
};

#endif /*FDEBUGEXCEPTION_H_*/

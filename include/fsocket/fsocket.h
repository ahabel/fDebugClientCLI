/**
 * @author Andreas Habel
 * $Id: fsocket.h,v 1.1 2011/01/16 20:54:03 virus-d Exp $
 *
 * @class fDebugSocket
 * @brief Socket Handler
 *
 * @package fDebug
 */

#ifndef FSOCKET_H_
#define FSOCKET_H_
#include <netinet/in.h>
#include <string>
using namespace std;

class fSocket {
public:
   /**
    * Constructor
    * @param port port to bind socket to
    */
   fSocket(int port);
   
   void     acceptConnections();
   string   receive();
   bool     send(const char *msg);
   void     close();
   
   char*    getRemoteAddress();
   
private:
   /**
    * @property sock
    * Socket handle
    */
   int sock;
   int clientSock;
   
   /**
    * @property srv_addr
    * Socket information struct
    */
   sockaddr_in srv_addr;
   
   sockaddr_in cli_addr;
};

#endif /*FSOCKET_H_*/



#ifndef FSOCKETEXCEPTION_H_
#define FSOCKETEXCEPTION_H_

class fSocketException {
private:
   char *message;
public:
   fSocketException(const char * message);
   char* getMessage();
};

#endif /*FSOCKETEXCEPTION_H_*/


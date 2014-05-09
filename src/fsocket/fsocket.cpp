#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "global.h"
#include "fdebugexception.h"
#include "fsocket/fsocket.h"
#include "config/fdebugconfig.h"

const int MAX_CONNECTIONS = 1;

fSocket::fSocket(int port) {
	printf("Listen on port %d\n", port);
	
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock == -1) {
		perror("Cannot create socket");
		exit(1);
	}
	
	// TIME WAIT fix
	int on = 1;
	if ( setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, (const char*) &on, sizeof (on)) == -1 ) {
		perror("Cannot set socket options");
		exit(1);
	}
	
	this->srv_addr.sin_family      = AF_INET;
   this->srv_addr.sin_addr.s_addr = INADDR_ANY;
   this->srv_addr.sin_port        = htons(port);
   
   int ret = bind(this->sock, (struct sockaddr *) &this->srv_addr, sizeof(this->srv_addr));
   if (ret == -1) {
      perror("Binding socket failed");
      exit(1);
   }
   
   ret = listen(this->sock, MAX_CONNECTIONS);
   if (ret == -1) {
      perror("Socket listen() failed");
      exit(1);
   }
}

void fSocket::acceptConnections() {
	printf(NORMAL "Waiting for incomming connections...\n\n");
	
	int addrlen = sizeof(this->cli_addr);
	this->clientSock = accept(this->sock, (struct sockaddr *) &this->cli_addr, (socklen_t *) &addrlen);
	if (this->clientSock <= 0) {
		perror("Socket accept() failed");
		throw fDebugException("accepting incoming connection failed");
	}
	return;
}

char* fSocket::getRemoteAddress() {
   return inet_ntoa(this->cli_addr.sin_addr);
}

string fSocket::receive() {
   string line;
   char buf[20000];
   
   int rec = recv(this->clientSock, buf, sizeof(buf) -1, 0);
   if (rec < 1) {
      if (rec == -1) {
         perror("recv failed");
      }
      throw fSocketException("No data received");
   }
   
   line.append(buf,rec);
   string::size_type i = line.find_last_of(" \t\n\v");
   line = line.erase(i);
   
   fDebugConfig *config = fDebugConfig::getInstance();
   if (config->options.debug) {
      printf("Recv: bytes[%d] [%s]\n\n", rec, line.c_str());
   }
   
   return line;
}

bool fSocket::send(const char *msg) {
   char buffer[1024];
   sprintf(buffer, msg, "\r\n");
   int bytes = ::send(this->clientSock, buffer, strlen(buffer), 0);
   if (bytes == -1) {
      perror("Sending to socket failed");
      return false;
   }
   return true;
}

void fSocket::close() {
   shutdown(this->clientSock, SHUT_RDWR);
}




//
// fSocketException
//
fSocketException::fSocketException(const char * message) {
   this->message = (char*) message;
}
char* fSocketException::getMessage() {
   fDebugConfig *config = fDebugConfig::getInstance();
   if (config->options.debug) {
      printf("DEBUG: SOCKET ERROR: %s\n", this->message);
   }
   return this->message;
}



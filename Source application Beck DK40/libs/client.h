#ifndef CLIENT_H
#define CLIENT_H

#include "clib.h"
#include <stdio.h>

class client
{
	private:
   	char * IPServeur;
      int PortServeur;
      struct sockaddr_in addr;
		int result, error_code, error;
      int sd;
   	int bufLen;
   public:
   	bool connecte;
   	client(char * ip, int port);
      ~client();
      void connexion();
      void deconnexion();
      void sendCode(char * code);
      int waitResponse();
};

#endif // CLIENT_H
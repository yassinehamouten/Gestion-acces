#include <stdio.h>
#include <dos.h>
#include <cstring>
#include <stdio.h>
#include "clib.h"

#include "beckdk40.h"
#include "client.h"
#include "rfidgrove125.h"
#include "serrure.h"

/***************************************************************************/
// Main
/***************************************************************************/
void main (void)
{
	beckdk40 * beck;
	client * cl;
	rfidGrove125 * rfid;
	serrure * ser;
	char * ip;
	int port;
	char * salle = "B01";
	int portCOM = 0;

	FILE * fichier;
	char str[20];
  	fichier = fopen ("config.ini","r");
  	if (fichier!=NULL)
  	{
		int i=0;
		while(fgets (str, sizeof(str), fichier)!=NULL){
			if(i==0){
				strcpy(ip, str);
				ip[strlen(ip)-1] = 0;
			}else{
				port = atoi(str);
			}
			i++;
		}
		fclose (fichier);
  	}else{
		printf("impossible d'ouvrir le fichier de configuration!");
		exit(0);
	}

	beck = new beckdk40(portCOM);
	beck->focus(1);

	printf("ip : %s  port : %d", ip, port);
	cl = new client(ip, port);
	cl->connexion();

	if(cl->connecte){
		printf("Connecte au serveur distant!\n");
		rfid = new rfidGrove125(portCOM);
		ser = new serrure();

		while(true){
			rfid->readCode();  // Bloquant
			char * code = rfid->getCode();
			char message[100];
			strcpy(message, "<code>");
			strcat(message, code);
			strcat(message, "</code><salle>");
			strcat(message, salle);
			strcat(message, "</salle>");
			cl->sendCode(message);
			int rep = cl->waitResponse();
			if(rep == 1){
				ser->ouvrir();
			}else if(rep == 2){
				printf("\nPas de reponse!\n");
			}else {
					printf("\nAcces refuse!\n");
			}
		}
	}else{
    	printf("Impossible de se connecter au serveur!\n");
		printf("Verifier que le serveur est bien lance\n");
		printf("Verifier le fichier de configuration(config.ini)");
	}


	beck->focus(0);
	exit(0);

}

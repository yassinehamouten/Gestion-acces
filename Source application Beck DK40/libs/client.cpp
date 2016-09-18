#include "client.h"

client::client(char * ip, int port){
   this->IPServeur = ip ;
	this->PortServeur = port ;
	this->bufLen = 1024;
	this->addr.sin_family = PF_INET ;
	this->addr.sin_addr.s_addr =  0 ;
   // Convertit entier depuis l'ordre des octets de l'hôte vers celui du réseau
	this->addr.sin_port = htons (this->PortServeur) ;
   // Convertit l'adresse ip en binaire
	inet_addr (this->IPServeur, &addr.sin_addr.s_addr);

	this->sd = opensocket(1, 0);
   if(this->sd!=-1){
    	printf("\nSocket ouvert!\n");
   }
}

client::~client(){
	closesocket(this->sd, &this->error_code);
}

void client::connexion(){
	result = connect( sd, (const struct sockaddr far *)&addr, &error_code );
  	if(result == 0){
   	//Connexion reussie
      this->connecte = true;
   }else{
   	//Connexion echouee
      this->connecte = false;
   }
}

void client::deconnexion(){
	closesocket(this->sd, &this->error_code);
}

void client::sendCode(char * code){
	int rez = send(this->sd, code, bufLen, MSG_BLOCKING, 0);
	if(rez!=-1){
		printf("Message envoye : %s\n",code);
	}else{
		printf("Message PAS envoye !\n");
	}
}

int client::waitResponse(){
	printf("En attente de reponse du serveur\n");
	char reponse[3] = " ";
   int retour;
   int len = 3;
	int rep = recv(this->sd, reponse, len, MSG_TIMEOUT , 15000, &this->error);
   printf("message recu : '%s'\n", reponse);
   if(reponse[0] == 'o' && reponse[1] == 'k'){
   	retour = 1;
   }else if(reponse[0] == ' '){
   	retour = 2;
   }else {
   	retour = 0;
   }
   return retour;
}

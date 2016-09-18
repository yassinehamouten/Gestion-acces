#include "rs232.h"

rs232::rs232(int port)
{
	// Initialisation du port COM (ici EXT) dans le constructeur

	//Init Fossil
   this->portCom = port;
   if(fossil_init(this->portCom)!=6484){
       printf("Erreur Init fossil!\n");
   }else{
   	printf("Pas d'erreur Init fossil!\n");
	}
   // Purge des buffers
   fossil_purge_output(this->portCom);
   fossil_purge_input(this->portCom);

   //  Definition des parametres pour le portCom
   fossil_setbaud (this->portCom , 9600L, 0, 8, 1);
   fossil_set_flowcontrol(this->portCom,0);

   printf("RS232 OK!\r\n");
}

rs232::~rs232(){
	fossil_deinit(this->portCom);
}

char rs232::getByte(){
	// Lit un caractere sur le port COM
   return fossil_getbyte_wait(this->portCom);
}

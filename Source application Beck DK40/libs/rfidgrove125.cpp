#include "rfidGrove125.h"

rfidGrove125::rfidGrove125(int port): rs232(port)
{
   printf("RFID OK!\r\n");
}

rfidGrove125::~rfidGrove125(){
}

void rfidGrove125::readCode(){
	printf("\n\nEn attente du code RFID\n");

	int i = 0;
   char c;
	while(i<12){
      c = this->getByte();
		if(c != 0x02 && c != 0x03){
        	code[i] = c;
         i++;
      }
   }

   printf("Code RFID lu : %s\n",code);
}

char * rfidGrove125::getCode(){
   return code;
}
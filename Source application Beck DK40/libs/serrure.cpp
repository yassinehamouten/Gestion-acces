#include "serrure.h"

serrure::serrure()
{
   printf("SERRURE OK!\r\n");
}

serrure::~serrure(){
}

void serrure::ouvrir(){
   printf("\nOuverture de la porte\n");
   this->clearPIO();
	this->writePIO(0xC0);
   RTX_Sleep_Time(2000);
   this->clearPIO();
   printf("Fermeture de la porte\n");
}

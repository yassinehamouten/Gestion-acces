#include "pio.h"

pio::pio()
{
  	// Enable bus mask, 7 bit outputs are on databus , 1 bit output is PIO
  	pfe_enable_bus(0xFFFF, 0);
  	// Enable programmable chip selects
  	pfe_enable_pcs(0x06);

   printf("PIO OK!\r\n");
}

pio::~pio(){
}

void pio::writePIO(unsigned char value){
	//0x10 -> PIN5
   //0x20 -> PIN6
   //0x40 -> PIN7
   //0x80 -> PIN8

  	// ecrit les donnees
  	hal_write_bus(0x600, value, 0xFFFF, 0x0000);

  	if (value&0x80){
   	//exemple: 0x10 & 0x80 -> 1 0000 & 1000 0000 -> pin n�4 (5eme led) allumee
    	hal_write_pio(13, 1);
  	}else{
    	hal_write_pio(13, 0);
  	}
}

void pio::clearPIO(){
	this->writePIO(0x00);
}
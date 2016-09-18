#ifndef RFIDGROVE125_H
#define RFIDGROVE125_H

#include "clib.h"
#include <stdio.h>

#include "rs232.h"

class rfidGrove125 : public rs232
{
	private:
   	char code[12];
   public:
   	rfidGrove125(int port);
      ~rfidGrove125();
      void readCode();
      char * getCode();
};

#endif // RFIDGROVE125_H

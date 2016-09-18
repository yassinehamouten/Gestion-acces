#ifndef PIO_H
#define PIO_H

#include "clib.h"
#include <stdio.h>

class pio
{
   public:
   	pio();
      ~pio();
      void writePIO(unsigned char value);
      void clearPIO();
};

#endif // SERRURE_H

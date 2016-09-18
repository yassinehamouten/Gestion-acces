#ifndef SERRURE_H
#define SERRURE_H

#include "clib.h"
#include <stdio.h>

#include "pio.h"

class serrure : public pio
{
   public:
   	serrure();
      ~serrure();
      void ouvrir();
};

#endif // SERRURE_H

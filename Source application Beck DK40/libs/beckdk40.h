#ifndef BECKDK40_H
#define BECKDK40_H

#include <stdio.h>

#include "clib.h"

class beckdk40
{
	private:
   	int portCom;
    public:
      beckdk40(int port);
      ~beckdk40();
      int status();
      void reboot();
      void focus(int param);
} ;

#endif // BECKDK40_H

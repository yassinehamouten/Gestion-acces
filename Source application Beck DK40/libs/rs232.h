#ifndef RS232_H
#define RS232_H

#include "clib.h"
#include <stdio.h>

class rs232
{
	private:
   	int portCom;
   public:
   	rs232(int port);
      ~rs232();
      char getByte();
};

#endif // RS232_H

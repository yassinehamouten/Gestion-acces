#include "beckdk40.h"

beckdk40::beckdk40(int port)
{
	this->portCom = port;
}

beckdk40::~beckdk40(){
}

int beckdk40::status(){
   return fossil_status_request(this->portCom);
}

void beckdk40::reboot(){
	BIOS_Reboot();
}

void beckdk40::focus(int param){
	// Permet de definir le focus
	if(param == 0){
   	BIOS_Set_Focus(FOCUS_SHELL);
   }else if(param == 1){
   	BIOS_Set_Focus(FOCUS_APPLICATION);
   }else{
   	BIOS_Set_Focus(FOCUS_BOTH);
   }
}

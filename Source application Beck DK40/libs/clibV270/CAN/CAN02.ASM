;/****************************************************************************
;* (C) 1999-2005 by BECK IPC GmbH
;*
;*  BECK IPC GmbH
;*  Germany
;*  
;*  http://www.beck-ipc.com
;*
;* ---------------------------------------------------------------------------
;*  Abstract:  Dynamic linked version of CAN API
;* ---------------------------------------------------------------------------
;   $Header: CAN02.asm$
;   $Log:$
;
;****************************************************************************



    INCLUDE CAN_API.DEF


_TEXT	SEGMENT BYTE PUBLIC 'CODE'			
	ASSUME CS:_TEXT, DS:NOTHING, ES:NOTHING, SS:NOTHING 

;/ Global ////////////////////////////////////////////////////////////////////
;//
;//  Function:    CAN_Rx_Filters
;//
;//  Purpose:    Install link (far JMP) to desired CAN function.
;//  
;//////////////////////////////////////////////////////////////////////////////
	PUBLIC	_CAN_Rx_Filters

_CAN_Rx_Filters PROC FAR

    LINKER_PATCH            ; Replaced by FAR JMP direct into RTOS

    MOV AX,CAN_API_RX_FILT     ; AH = 80 -> Dynamic link, AL = link selector
    int CAN_SWI

    ; IP is rolled back on return from software interrupt so that the
    ;  new FAR JMP is executed immediately following the code patch.

_CAN_Rx_Filters ENDP

_TEXT ENDS			

	END	


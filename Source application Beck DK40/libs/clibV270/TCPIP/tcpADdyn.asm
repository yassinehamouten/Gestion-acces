;******************************************************************************
;
; (c) 2007 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     tcpADdyn.asm
; Function:   Dynamic linking of TCPI/IP API Function Dev_Get_Handle_By_Name()
;
;
;******************************************************************************
;
; $Header$
;
;******************************************************************************



INCLUDE tcpipapi.def



_TEXT SEGMENT BYTE PUBLIC 'CODE'
      ASSUME CS:_TEXT, DS:NOTHING, ES:NOTHING, SS:NOTHING



;******************************************************************************
; Prototypes
;******************************************************************************
PUBLIC _Dev_Get_Handle_By_Name_Dyn



;******************************************************************************
; Dev_Get_Handle_By_Name_Dyn()
;******************************************************************************
_Dev_Get_Handle_By_Name_Dyn PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, TCPIP_DYN_LINK_DEV_GET_HANDLE_BY_NAME  ; AH = 0, AL = Function number
  INT TCPIP_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_Dev_Get_Handle_By_Name_Dyn ENDP



_TEXT ENDS
END       
; End of file

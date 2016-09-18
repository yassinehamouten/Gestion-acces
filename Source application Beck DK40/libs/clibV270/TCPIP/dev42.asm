;******************************************************************************
;
; (c) 2010 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     dev42.asm
; Function:   Dynamic linking of TCP/IP device driver API Function
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
PUBLIC _Dev_Set_IfaceMTU



;******************************************************************************
; Dev_Set_IfaceMTU()
;******************************************************************************
_Dev_Set_IfaceMTU PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, TCPIP_DYN_LINK_Dev_Set_IfaceMTU  ; AH = 0, AL = Function number
  INT TCPIP_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_Dev_Set_IfaceMTU ENDP



_TEXT ENDS
END       
; End of file

;******************************************************************************
;
; (c) 2010 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     bsd30.asm
; Function:   Dynamic linking of TCP/IP BSD API Function
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
PUBLIC _inet_addr_bsd



;******************************************************************************
; inet_addr_bsd()
;******************************************************************************
_inet_addr_bsd PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, TCPIP_DYN_LINK_inet_addr_bsd  ; AH = 0, AL = Function number
  INT TCPIP_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_inet_addr_bsd ENDP



_TEXT ENDS
END       
; End of file

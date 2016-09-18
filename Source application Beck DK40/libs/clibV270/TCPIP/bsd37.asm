;******************************************************************************
;
; (c) 2010 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     bsd37.asm
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
PUBLIC _setsockopt_bsd



;******************************************************************************
; setsockopt_bsd()
;******************************************************************************
_setsockopt_bsd PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, TCPIP_DYN_LINK_setsockopt_bsd  ; AH = 0, AL = Function number
  INT TCPIP_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_setsockopt_bsd ENDP



_TEXT ENDS
END       
; End of file

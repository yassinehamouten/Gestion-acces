;******************************************************************************
;
; (c) 2015 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     cry46.asm
; Function:   Dynamic linking of TCPI/IP API Function Crypt_RSA_Sign()
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
PUBLIC _Crypt_RSA_Sign



;******************************************************************************
; Crypt_RSA_Sign()
;******************************************************************************
_Crypt_RSA_Sign PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, TCPIP_DYN_LINK_Crypt_RSA_Sign  ; AH = 0, AL = Function number
  INT TCPIP_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_Crypt_RSA_Sign ENDP



_TEXT ENDS
END       
; End of file

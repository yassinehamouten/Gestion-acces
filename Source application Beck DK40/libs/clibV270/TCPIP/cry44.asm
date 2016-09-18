;******************************************************************************
;
; (c) 2013 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     cry44.asm
; Function:   Dynamic linking of TCPI/IP API Function Crypt_SHA256_Update()
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
PUBLIC _Crypt_SHA256_Update



;******************************************************************************
; Crypt_SHA256_Update()
;******************************************************************************
_Crypt_SHA256_Update PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, TCPIP_DYN_LINK_Crypt_SHA256_Update  ; AH = 0, AL = Function number
  INT TCPIP_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_Crypt_SHA256_Update ENDP



_TEXT ENDS
END       
; End of file

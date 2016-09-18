;******************************************************************************
;
; (c) 2013 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     cry43.asm
; Function:   Dynamic linking of TCPI/IP API Function Crypt_SHA256_Init()
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
PUBLIC _Crypt_SHA256_Init



;******************************************************************************
; Crypt_SHA256_Init()
;******************************************************************************
_Crypt_SHA256_Init PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, TCPIP_DYN_LINK_Crypt_SHA256_Init  ; AH = 0, AL = Function number
  INT TCPIP_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_Crypt_SHA256_Init ENDP



_TEXT ENDS
END       
; End of file

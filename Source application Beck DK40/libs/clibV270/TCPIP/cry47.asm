;******************************************************************************
;
; (c) 2015 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     cry47.asm
; Function:   Dynamic linking of TCPI/IP API Function Crypt_RSA_Verify()
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
PUBLIC _Crypt_RSA_Verify



;******************************************************************************
; Crypt_RSA_Verify()
;******************************************************************************
_Crypt_RSA_Verify PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, TCPIP_DYN_LINK_Crypt_RSA_Verify  ; AH = 0, AL = Function number
  INT TCPIP_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_Crypt_RSA_Verify ENDP



_TEXT ENDS
END       
; End of file

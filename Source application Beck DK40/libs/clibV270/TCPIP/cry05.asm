;******************************************************************************
;
; (c) 2010 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     cry05.asm
; Function:   Dynamic linking of TCPI/IP API Function Crypt_AES_MakeDecryptKey()
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
PUBLIC _Crypt_AES_MakeDecryptKey_Dyn



;******************************************************************************
; Crypt_AES_MakeDecryptKey()
;******************************************************************************
_Crypt_AES_MakeDecryptKey_Dyn PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, TCPIP_DYN_LINK_Crypt_AES_MakeDecryptKey  ; AH = 0, AL = Function number
  INT TCPIP_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_Crypt_AES_MakeDecryptKey_Dyn ENDP



_TEXT ENDS
END       
; End of file

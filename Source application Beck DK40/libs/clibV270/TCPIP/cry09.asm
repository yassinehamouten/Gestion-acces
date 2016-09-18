;******************************************************************************
;
; (c) 2010 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     cry09.asm
; Function:   Dynamic linking of TCPI/IP API Function Crypt_Blowfish_MakeKey()
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
PUBLIC _Crypt_Blowfish_MakeKey



;******************************************************************************
; Crypt_Blowfish_MakeKey()
;******************************************************************************
_Crypt_Blowfish_MakeKey PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, TCPIP_DYN_LINK_Crypt_Blowfish_MakeKey  ; AH = 0, AL = Function number
  INT TCPIP_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_Crypt_Blowfish_MakeKey ENDP



_TEXT ENDS
END       
; End of file

;******************************************************************************
;
; (c) 2010 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     rtxdyn03.asm
; Function:   Dynamic linking of RTX API Function
;
;
;******************************************************************************
;
; $Header$
;
;******************************************************************************



INCLUDE  rtxDLapi.def



_TEXT SEGMENT BYTE PUBLIC 'CODE'
      ASSUME CS:_TEXT, DS:NOTHING, ES:NOTHING, SS:NOTHING



;******************************************************************************
; Prototypes
;******************************************************************************
PUBLIC _RTX_GetPublication



;******************************************************************************
; RTX_GetPublication()
;******************************************************************************
_RTX_GetPublication PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, IDX_RTX_GetPublication  ; AH = 0, AL = Function number
  INT RTX_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_RTX_GetPublication ENDP



_TEXT ENDS
END       
; End of file

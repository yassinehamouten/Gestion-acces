;******************************************************************************
;
; (c) 2010 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     rtxdyn01.asm
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
PUBLIC _RTX_Set_TimeDate_us



;******************************************************************************
; RTX_Set_TimeDate_us()
;******************************************************************************
_RTX_Set_TimeDate_us PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, IDX_RTX_Set_TimeDate_us  ; AH = 0, AL = Function number
  INT RTX_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_RTX_Set_TimeDate_us ENDP



_TEXT ENDS
END       
; End of file

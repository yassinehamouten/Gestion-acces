;******************************************************************************
;
; (c) 2010 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     htons.asm
; Function:   Swap byte order
;
;
;******************************************************************************
;
; $Header$
;
;******************************************************************************

    ; "DIST" is defined as either FAR or NEAR inside this include file.
    ; "RETADDR_DEF" is defined as either DD or DW
INCLUDE ../common/asmRules.def


HTONS_FRAME   STRUC    

                RETADDR_DEF     ?   ; Our far return address
        ;;;;;;;;;  Input Parameter from Caller  ;;;;;;;;;;;;
    value       DW              ?   ; WORD whose endian is to be swapped

HTONS_FRAME  ENDS

_TEXT SEGMENT BYTE PUBLIC 'CODE'
      ASSUME CS:_TEXT, DS:NOTHING, ES:NOTHING, SS:NOTHING



;******************************************************************************
; Prototypes
;******************************************************************************
PUBLIC _htons



;******************************************************************************
;  htons()
;******************************************************************************
_htons PROC DIST

    mov     BX,SP
    MOV     AX,SS:[BX].value
    XCHG    AL,AH

    RET

_htons ENDP



_TEXT ENDS
END       
; End of file

;******************************************************************************
;
; (c) 2010 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     htonl.asm
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
    value_lsw   DW              ?   ; DWORD whose endian is to be swapped
    value_msw   DW              ?   ; DWORD whose endian is to be swapped

HTONS_FRAME  ENDS

_TEXT SEGMENT BYTE PUBLIC 'CODE'
      ASSUME CS:_TEXT, DS:NOTHING, ES:NOTHING, SS:NOTHING



;******************************************************************************
; Prototypes
;******************************************************************************
PUBLIC _htonl


;******************************************************************************
;  htonl()
;******************************************************************************
_htonl PROC DIST

    mov     BX,SP
    MOV     DX,SS:[BX].value_lsw    ; Returned in MSW
    XCHG    DL,DH
    MOV     AX,SS:[BX].value_msw    ; Returned in LSW
    XCHG    AL,AH

    RET             ; Swapped DWORD now in DX:AX register pair

_htonl ENDP



_TEXT ENDS
END       
; End of file

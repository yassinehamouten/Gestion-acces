;******************************************************************************
;
; (c) 2006 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     usb01.asm
; Function:   Dynamic linking of USB-API-Function usbSend()
;
;
;******************************************************************************
;
; $Header$
;
;******************************************************************************



INCLUDE usb_api.def



_TEXT SEGMENT BYTE PUBLIC 'CODE'
      ASSUME CS:_TEXT, DS:NOTHING, ES:NOTHING, SS:NOTHING



;******************************************************************************
; Prototypes
;******************************************************************************
PUBLIC _usbSend



;******************************************************************************
; usbSend()
;******************************************************************************
_usbSend PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, USB_SERVICE_SEND  ; AH = 0, AL = Function number
  INT USB_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_usbSend ENDP



_TEXT ENDS
END       
; End of file

;******************************************************************************
;
; (c) 2006 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     usb03.asm
; Function:   Dynamic linking of USB-API-Function usbWakeup()
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
PUBLIC _usbWakeup



;******************************************************************************
; usbWakeup()
;******************************************************************************
_usbWakeup PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, USB_SERVICE_WAKEUP  ; AH = 0, AL = Function number
  INT USB_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_usbWakeup ENDP



_TEXT ENDS
END       
; End of file

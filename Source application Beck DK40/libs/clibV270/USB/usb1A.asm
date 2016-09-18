;******************************************************************************
;
; (c) 2006 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     usb1A.asm
; Function:   Dynamic linking of USB-API-Function usbDeviceEnableEp()
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
PUBLIC _usbDeviceEnableEp



;******************************************************************************
; usbDeviceEnableEp()
;******************************************************************************
_usbDeviceEnableEp PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, USB_SERVICE_DEVICE_ENABLE_EP  ; AH = 0, AL = Function number
  INT USB_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_usbDeviceEnableEp ENDP



_TEXT ENDS
END       
; End of file

;******************************************************************************
;
; (c) 2006 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     usb26.asm
; Function:   Dynamic linking of USB-API-Function usbHostGetDeviceInfo()
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
PUBLIC _usbHostGetDeviceInfo



;******************************************************************************
; usbHostGetDeviceInfo()
;******************************************************************************
_usbHostGetDeviceInfo PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, USB_SERVICE_HOST_GET_DEVICE_INFO  ; AH = 0, AL = Function number
  INT USB_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_usbHostGetDeviceInfo ENDP



_TEXT ENDS
END       
; End of file

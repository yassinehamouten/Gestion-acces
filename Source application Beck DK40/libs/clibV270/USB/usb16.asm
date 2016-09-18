;******************************************************************************
;
; (c) 2006 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     usb16.asm
; Function:   Dynamic linking of USB-API-Function usbDeviceAddSpecificDesc()
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
PUBLIC _usbDeviceAddSpecificDesc



;******************************************************************************
; usbDeviceAddSpecificDesc()
;******************************************************************************
_usbDeviceAddSpecificDesc PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, USB_SERVICE_DEVICE_ADD_SPECIFIC_DESC  ; AH = 0, AL = Function number
  INT USB_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_usbDeviceAddSpecificDesc ENDP



_TEXT ENDS
END       
; End of file

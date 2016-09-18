;******************************************************************************
;
; (c) 2007 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     tcpAFdyn.asm
; Function:   Dynamic linking of TCPI/IP API Function Dev_Config_Iface_IPv6()
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
PUBLIC _Dev_Config_Iface_IPv6_Dyn



;******************************************************************************
; Dev_Config_Iface_IPv6_Dyn()
;******************************************************************************
_Dev_Config_Iface_IPv6_Dyn PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, TCPIP_DYN_LINK_DEV_CONFIG_IFACE_IPV6  ; AH = 0, AL = Function number
  INT TCPIP_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_Dev_Config_Iface_IPv6_Dyn ENDP



_TEXT ENDS
END       
; End of file

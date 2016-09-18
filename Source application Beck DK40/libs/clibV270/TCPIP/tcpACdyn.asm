;******************************************************************************
;
; (c) 2007 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     tcpACdyn.asm
; Function:   Dynamic linking of TCPI/IP API Function Dev_PPP_Get_Peer_DNSIP()
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
PUBLIC _Dev_PPP_Get_Peer_DNSIP_Dyn



;******************************************************************************
; Dev_PPP_Get_Peer_DNSIP_Dyn()
;******************************************************************************
_Dev_PPP_Get_Peer_DNSIP_Dyn PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, TCPIP_DYN_LINK_DEV_PPP_GET_PEER_DNSIP  ; AH = 0, AL = Function number
  INT TCPIP_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_Dev_PPP_Get_Peer_DNSIP_Dyn ENDP



_TEXT ENDS
END       
; End of file

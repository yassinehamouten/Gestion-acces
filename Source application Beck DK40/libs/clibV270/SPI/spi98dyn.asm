;******************************************************************************
;
; (c) 2007 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     spi98dyn.asm
; Function:   Dynamic linking of SPI API Function spi_slave_init_dyn()
;
;
;******************************************************************************
;
; $Header$
;
;******************************************************************************



INCLUDE spiapi.def



_TEXT SEGMENT BYTE PUBLIC 'CODE'
      ASSUME CS:_TEXT, DS:NOTHING, ES:NOTHING, SS:NOTHING



;******************************************************************************
; Prototypes
;******************************************************************************
PUBLIC _spi_slave_init_dyn



;******************************************************************************
; spi_slave_init_dyn()
;******************************************************************************
_spi_slave_init_dyn PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, SPI_DYN_LINK_SLAVE_INIT  ; AH = 0, AL = Function number
  INT I2C_SPI_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_spi_slave_init_dyn ENDP



_TEXT ENDS
END       
; End of file

;******************************************************************************
;
; (c) 2007 by BECK IPC GmbH
; http://www.beck-ipc.com
;
;******************************************************************************
;
; Module:     spi95dyn.asm
; Function:   Dynamic linking of SPI API Function spi_read_hw_dyn()
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
PUBLIC _spi_read_hw_dyn



;******************************************************************************
; spi_read_hw_dyn()
;******************************************************************************
_spi_read_hw_dyn PROC FAR
  LINKER_PATCH            ; Will be replaced by dynamic linking code

  MOV AX, SPI_DYN_LINK_READ_HW  ; AH = 0, AL = Function number
  INT I2C_SPI_SWI

  ; IP-Register will be adjusted on return from software interrupt so that the
  ; new code is executed immediately.

_spi_read_hw_dyn ENDP



_TEXT ENDS
END       
; End of file

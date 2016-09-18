;/****************************************************************************
;* (C) 1999-2005 by BECK IPC GmbH
;*
;*  BECK IPC GmbH
;*  Germany
;*  
;*  http://www.beck-ipc.com
;*
;* ---------------------------------------------------------------------------
;*  Abstract:  Provide default _PCSEGM and _PCMASK constants for use
;*            by linker when Paradigm Beck Edition compiler is not
;*            used.
;* ---------------------------------------------------------------------------
;   $Header: PCSEGM.asm$
;   $Log:$
;
;****************************************************************************



; The public constants __PCSHIFT and __PCMASK are declared by Paradigm
; Beck Edition compiler code to allow the linker to apply the shift
; counts and address pointer masks related to CPU paragraph size.
; These same constants are defined here to cover builds which use
; the Beck C-Library with BC5 compiler, which does not define these
; Paradigm inventions.
;

public  __AHSHIFT, __PCSHIFT, __PCMASK, __PCINCR, __PCFAST

;# IFNDEF   __ADDR24__

    ; For normal 80186 with 16 byte paragraphs
__AHSHIFT   =  12
__PCSHIFT   =  4
__PCFAST    =  12
__PCMASK    =  00fh
__PCINCR    =  1000h

;# ELSE

    ; For extended 24 bit 80186 with 256 byte paragraphs
;# __AHSHIFT   =  8
;# __PCSHIFT   =  8
;# __PCFAST    =  8
;# __PCMASK    =  0ffh
;# __PCINCR    =  0100h

;# ENDIF


	END	


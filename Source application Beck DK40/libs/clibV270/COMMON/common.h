/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
*  Module  :  COMMON.H
*  Function:  Some common definitinos for the C libraries
* ---------------------------------------------------------------------------

$Header: common.h, 6, 04.05.2005 20:53:24, Jack Gatrost$

****************************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

#ifdef WIN32                //  Browser data base build with MS Visual C?
#include <msvc_patch.h>     //  Applies  only to browser build.
#endif

/*************************************************************************
*  System Type Definitions
*************************************************************************/

/******** Fundamental Types *****************************/
typedef unsigned char  UCHAR ;
typedef unsigned int   UINT ;

typedef unsigned char  BYTE ;
#ifndef _WINDOWS_
typedef unsigned int   WORD ;
#endif
typedef unsigned long  DWORD ;

typedef int            BOOL ;          // For backwards compatibility
typedef unsigned char  BOOL_ ;         // Smaller version


/*************************************************************************
*  System Wide Constants
*************************************************************************/

#define CARRY_FLAG (0x1)        // x86

#ifndef _WINDOWS_
#define FALSE (0)
#define TRUE  (1)
#endif

#ifdef _MSC_VER /* If Microsoft C Compiler is used, define new FP_SEG and FP_OFF Macro */
   #ifdef FP_SEG
      #undef FP_SEG
   #endif
   #define FP_SEG(ptr)    ((unsigned int)(((unsigned long)ptr)>>16))

   #ifdef FP_OFF
      #undef FP_OFF
   #endif
   #define FP_OFF(ptr)    ((unsigned int)(((unsigned long)ptr)&0xFFFF))

#define asm _asm
#endif

////////////////////////////////////////////////////////////////////////
//    20 bit address / 24 bit address selection constants
////////////////////////////////////////////////////////////////////////
// The constants here allow the linker to supply code patches for
// shift and mask constants related to CPU paragraph size.
// When linking with Paradigm Beck Edition compiler, these constants
// are provided by the compiler environment.
// When linking with any other compiler, these constants are defined
// in RTX/PCSEGM.ASM C-Library source file.

extern unsigned far _PCSHIFT; // Paradigm defines for address mode
extern unsigned far _PCMASK;  // Paradigm defines for address mode

    // SEG_MASK constant:
    //   = 0x0F for 20 bit address mode
    //   = 0xFF for 24 bit address mode
#define SEG_MASK       (FP_OFF(&_PCMASK))

    // SEG_SHIFT constant:
    //   = 4 for 20 bit address mode
    //   = 8 for 24 bit address mode
#define SEG_SHIFT      (FP_OFF(&_PCSHIFT))

/*************************************************************************
*  Globally Useful Macros
*************************************************************************/
// _USE_PORT_INTRINSICS will cause dos.h to provide in-line code
//   for functions such as inport / outport
#define _USE_PORT_INTRINSICS

#define _CLEAR(x)          memset(&x, 0, sizeof(x))
#define _ELEMENTS(array)   (sizeof(array)/sizeof(array[0]))

#define MASK_INTERRUPTS    asm { cli }
#define ENABLE_INTERRUPTS  asm { sti }
#define SAVE_AND_MASK      asm { pushf } \
                           asm { cli }
#define RESTORE_MASK       asm { popf }

// PROTECTED_READ allows reading multi-word objects under interrupt
//   protection.
#define PROTECTED_READ(to, from) \
     SAVE_AND_MASK ; \
     to = from ; \
     RESTORE_MASK

// PROTECTED_WRITE allows writing multi-word objects under interrupt
//   protection.
#define PROTECTED_WRITE(to, from) \
     SAVE_AND_MASK ; \
     to = from ; \
     RESTORE_MASK


#endif  // _COMMON_H_

/************************************************************
*   End common.h  
************************************************************/



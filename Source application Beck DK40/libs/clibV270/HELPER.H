/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : HELPER.H
* Function       : prototypes, constants for helper functions
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\HELPER.H, 13, 14.01.2009 16:04:51, Jan Schatz$

*****************************************************************************/

#ifndef HELPER_H
#define HELPER_H

#include <dos.h>

/***************************************************************************/
// Defines
/***************************************************************************/
#define CHIPDLL_ERR_OK          0 // The CHIPDLL was loaded successfully
#define CHIPDLL_ERR_NOTFOUND   -1 // The CHIPDLL could not be found on the drive
#define CHIPDLL_ERR_COULDNTLD  -2 // There occured an system error while loading
                                  // (not enough memory?)
#define CHIPDLL_ERR_BLOCKING   -3 // Waiting for the DLLEnter function (THIS CODE
                                  // MUST NOT RETURNED BY THE DLLEnter and DLLLeave
                                  // FUNCTION!)
#define CHIPDLL_ERR_INVALIDFPL -4 // The function pointer list returned (FPL) by
                                  // the DLL loader is not equal to the FPL expected
                                  // by the import library.
                                  
                                  
                                  
/*******************************************************************************
* Macro functions
*******************************************************************************/
// Swap a 16 bit word
#define swap16(x)       ((((x) & 0xFF00U) >> 8)     \
                         | (((x) & 0x00FFU) << 8))
// Swap a 32 bit word
#define swap32(x)       ((((x) & 0xFF000000UL) >> 24)     \
                         | (((x) & 0x00FF0000UL) >> 8)    \
                         | (((x) & 0x0000FF00UL) << 8)    \
                         | (((x) & 0x000000FFUL) << 24))
// Convert 16/32 bit words from host's endianness to big/little endian
#define hostToLE16(x)   (x)
#define hostToLE32(x)   (x)
#define hostToBE16(x)   (swap16(x))
#define hostToBE32(x)   (swap32(x))
// Convert 16/32 bit words from big/little endian to host's endianess
#define lEToHost16(x)   (x)
#define lEToHost32(x)   (x)
#define bEToHost16(x)   (swap16(x))
#define bEToHost32(x)   (swap32(x))

// General unpack/pack for x86
#define packAll(p, v)  (*(p) = (v))
#define unpackAll(p)  (*(p))
#define packArrayAll(p, i, v) (((p)[i]) = (v))
#define unpackArrayAll(p, i)  ((p)[i])


/*******************************************************************************
* packBool(unsigned char *p, bool value)
/*******************************************************************************/
#ifdef __cplusplus
#define packBool(p, v)  packAll((bool *)p, v)
#endif


/*******************************************************************************
* packUChar(unsigned char *p, unsigned char value)
/*******************************************************************************/
#define packUChar(p, v)  packAll((unsigned char *)p, v)


/*******************************************************************************
* packChar(unsigned char *p, char value)
/*******************************************************************************/
#define packChar(p, v)  packAll((char *)p, v)


/*******************************************************************************
* packUShort(unsigned char *p, unsigned short value)
********************************************************************************/
#define packUShort(p, v)  packAll((unsigned short *)p, v)


/*******************************************************************************
* packShort(unsigned char *p, short value)
/*******************************************************************************/
#define packShort(p, v)  packAll((short *)p, v)


/*******************************************************************************
* packULong(unsigned char *p, unsigned long value) 
********************************************************************************/
#define packULong(p, v)  packAll((unsigned long *)p, v)


/*******************************************************************************
* packLong(unsigned char *p, long value)
/*******************************************************************************/
#define packLong(p, v)  packAll((long *)p, v)


/*******************************************************************************
* packFloat(unsigned char *p, float value)
/*******************************************************************************/
#define packFloat(p, v)  packAll((float *)p, v)


/*******************************************************************************
* packDouble(unsigned char *p, double value)
/*******************************************************************************/
#define packDouble(p, v)  packAll((double *)p, v)


/*******************************************************************************
* unpackBool(p)
/*******************************************************************************/
#ifdef __cplusplus
#define unpackBool(p)  unpackAll((bool *)p)
#endif


/*******************************************************************************
* unpackUChar(unsigned char *p)
********************************************************************************/
#define unpackUChar(p)  unpackAll((unsigned char *)p)


/*******************************************************************************
* unpackChar(unsigned char *p)
/*******************************************************************************/
#define unpackChar(p)  unpackAll((char *)p)


/*******************************************************************************
* unpackUShort(unsigned char *p)
********************************************************************************/
#define unpackUShort(p)  unpackAll((unsigned short *)p)


/*******************************************************************************
* unpackShort(unsigned char *p)
/*******************************************************************************/
#define unpackShort(p)  unpackAll((short *)p)


/*******************************************************************************
* unpackULong(unsigned char *p)
********************************************************************************/
#define unpackULong(p)  unpackAll((unsigned long *)p)


/*******************************************************************************
* unpackLong(unsigned char *p)
/*******************************************************************************/
#define unpackLong(p)  unpackAll((long *)p)


/*******************************************************************************
* unpackFloat(unsigned char *p)
/*******************************************************************************/
#define unpackFloat(p)  unpackAll((float *)p)


/*******************************************************************************
* unpackDouble(unsigned char *p)
/*******************************************************************************/
#define unpackDouble(p)  unpackAll((double *)p)


/*******************************************************************************
* packBoolArray(unsigned char *p, int index, value) 
********************************************************************************/
#ifdef __cplusplus
#define packBoolArray(p, i, v)  packArrayAll((bool *)p, i, v)
#endif


/*******************************************************************************
* packUShortArray(unsigned char *p, int index, unsigned short value)
********************************************************************************/
#define packUShortArray(p, i, v)  packArrayAll((unsigned short *)p, i, v)


/*******************************************************************************
* packULongArray(unsigned char *p, int index, unsigned long value)
********************************************************************************/
#define packULongArray(p, i, v)  packArrayAll((unsigned long *)p, i, v)


/*******************************************************************************
* unpackUShortArray(unsigned char *p, int index)
********************************************************************************/
#define unpackUShortArray(p, i)  unpackArrayAll((unsigned short *)p, i)


/*******************************************************************************
* unpackShortArray(unsigned char *p, int index)
********************************************************************************/
#define unpackShortArray(p, i)  unpackArrayAll((short *)p, i)


/*******************************************************************************
* unpackULongArray(unsigned char *p, int index)
********************************************************************************/
#define unpackULongArray(p, i)  unpackArrayAll((unsigned long *)p, i)



/***************************************************************************/
// Prototyps
/***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

typedef int _cdecl (far * Sprintf_Fptr)(char far * buf,
                                        const char far * fmt,
                                        void far * ap);

void         _cdecl helper_strout( const char far *s );
int          _cdecl helper_chrout( char ch, int zero );
void         _cdecl helper_dezout( unsigned int x, int zero );
void         _cdecl helper_hexdig( unsigned char dig );
void         _cdecl helper_hexout( unsigned hex );
int          _cdecl helper_printf( const char *fmt, ...);
int          _cdecl helper_sprintf( char *buffer, const char *fmt, ...);

unsigned int _cdecl helper_alloc_rtos_mem  ( unsigned long size );
int          _cdecl helper_release_rtos_mem( unsigned int seg );

unsigned int _cdecl helper_alloc_rtos_fast_mem(unsigned long size);
int          _cdecl helper_assign_mem(void far *mem_block,
                                      unsigned int taskid) ;

#define helper_check_license(id, secret, length) \
( _ES = FP_SEG((secret)), \
  _BX = FP_OFF((secret)), \
  _CX = (length),         \
  _AL = (id),             \
  _AH = 0x5A,             \
  geninterrupt(0xA0),     \
  _AX                     \
)

unsigned short _cdecl helper_clibVersion (void) ;

int          _cdecl helper_load_library (const char * libPath,
                                         void * pFpl,
                                         int  * pFplLen,
                                         int    fplSize);
int          _cdecl helper_unload_library(const char * libPath);
void far *   _cdecl progParentData(void) ;

#ifdef __cplusplus
}
#endif


#endif // HELPER_H

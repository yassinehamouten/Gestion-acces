/****************************************************************************
* (C) 1999-2011 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : HEAP.H
* Function       : Re-entrant heap functions for multitasking use.
* ---------------------------------------------------------------------------

$Id: heap.h 1765 2013-09-28 15:17:05Z de6jga $

*****************************************************************************/

#ifndef _HEAP_H_
#define _HEAP_H_

#include <systypes.h>

// Result codes for heap lock functions
#define HEAP_OK       (1)
#define HEAP_FAIL     (0)

///////////////////////////////////////////////////////////////////
// Sneak into Paradigm C-Libraries private internals,
//  for which we are offered no header files.
///////////////////////////////////////////////////////////////////
void * __cdecl _clib_malloc( size_t nbytes ) ;
void   __cdecl _clib_free( void * ap ) ;
void * __cdecl _clib_realloc( void * ptr, size_t size ) ;
void _FAR * __cdecl _clib_farmalloc( unsigned long nbytes ) ;
void        __cdecl _clib_farfree( void _FAR * ap ) ;
void _FAR * __cdecl _clib_farrealloc( void _FAR * ptr, unsigned long size ) ;
unsigned long _clib_farcoreleft(void) ;

BOOL __cdecl HeapLockNoBlock (void);
void __cdecl HeapUnlock (void);

#endif // _HEAP_H_
// End HEAP.H


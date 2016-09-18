/****************************************************************************
* (C) 1999-2011 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : HEAP.C
* Function       : Re-entrant heap functions for multitasking use.
* ---------------------------------------------------------------------------

$Id: heap.c 1954 2014-07-09 10:48:32Z de6jga $

*****************************************************************************/

#include <stddef.h>
#include <alloc.h>

#include "RTOS.H"

#include "heap.h"

///////////////////////////////////////////////////////////////////
// _FAR_HEAP_TOO compilation switch
//
//  Comment out this _FAR_HEAP_TOO switch in either of following
//  two cases:
//
//   1) You don't need the FAR heap functions and you would like
//     to remove these unused functions to reduce your program's
//     image size a bit.
//
//   2) Your program uses SMALL or MEDIUM memory models, and you
//     want only the near heap functions here.  This way you may
//     use the BeckHeapS.LIB or BeckHeapM.LIB libraries for your
//     far heap, while this file supplies a re-entrant near heap.
//
///////////////////////////////////////////////////////////////////
#define _FAR_HEAP_TOO

// Define _NEAR_HEAP_WALK to include optional _nearHeapWalk() procedure.
//#define _NEAR_HEAP_WALK

///////////////////////////////////////////////////////////////////
//  Private internal data
///////////////////////////////////////////////////////////////////

static int  idHeapSemaphore ;
static int  _HeapLockCnt ;
static char _HeapSemaName[] = { 'h', 'e', 'a', 'p' } ;

// Private //////////////////////////////////////////////////////////////////
//
//  Function:     _HeapLock ()
//
//  Purpose:   Gain exclusive access to heap.
//
//  Return Value:
//      status  -   1 on success, 0 if failed to create semaphore at startup.
//
//////////////////////////////////////////////////////////////////////////////
static int near _HeapLock (void)
{
    // Set the critical section.
    disable();

    // Increment and check the heap lock count.
    if (++_HeapLockCnt == 1)            // Are we first one here?
    {
        // We now have the resource locked for our exclusive use.
        // Release the critical section.
        enable() ;
        return HEAP_OK ;
    }
    // Release the critical section.
    enable() ;

    // Alternate strategy to cover case where RTOS semaphore allocation
    // has failed:
    //
    //  1)  The program could have been aborted back in init_rtl_heap()
    //   if this needed system resource was not available.  This would
    //   have the advantage that this run time check could then be
    //   eliminated.
    //
    //  2)  Move this idHeapSemaphore test up to the entry of this
    //     procedure.  This will force an immediate memory allocation
    //     failure on the first call to malloc(), thereby making the
    //     allocation failure more apparent.  With the test placed
    //     down here, we do not fail at malloc() until two threads
    //     access the heap functions concurrently.

    // Did the semaphore allocation fail back in init_rtl_heap()?
    if (idHeapSemaphore == 0)
    {
        return HEAP_FAIL ;
    }

    // Pend on the semaphore.
    RTX_Wait_Sem_Priority ( idHeapSemaphore, 0, 0) ;
      return HEAP_OK ;
    
}   // _HeapLock()


// Private ///////////////////////////////////////////////////////////////////
//
//  Function:     _HeapUnlock ()
//
//  Purpose:   Release lock on heap.
//
//////////////////////////////////////////////////////////////////////////////
static void near _HeapUnlock(void)
{
    // Set the critical section and decrement the lock count for the entry.
    disable() ;

    // If nobody else is waiting on this lock ...
    if ( --_HeapLockCnt != 0)
    {
        // Other threads are waiting.
        enable() ;
        RTX_Signal_Sem( idHeapSemaphore ) ;
    }
    enable() ;

}   // _HeapUnlock()


// Public ////////////////////////////////////////////////////////////////
//
//  Function:     HeapLockNoBlock ()
//
//  Purpose:   Attempt gaining exclusive access to heap.  Return
//             immediately if blocking would be required.
//
//             Caller must follow this call with a HeapUnlock() call
//             if and only if this function returns TRUE.
//
//  Parameters:
//      -- none --
//
//  Return Value:
//      locked  -   Boolean TRUE if caller now has access to the heap.
//
///////////////////////////////////////////////////////////////////////////
BOOL __cdecl HeapLockNoBlock (void)
{
    BOOL locked = FALSE ;
    // Set the critical section.
    disable();
    if (_HeapLockCnt == 0) {            // Heap is available?
        _HeapLockCnt++ ;                // Take access.
        locked = TRUE ;
    }
    // Release the critical section.
    enable() ;
    return locked ;
}


// Public //////////////////////////////////////////////////////////////////
//
//  Function:     HeapUnlock ()
//
//  Purpose:   Release lock on heap.
//
//  Return Value:
//      None
//
//////////////////////////////////////////////////////////////////////////////
void __cdecl HeapUnlock()
{
  _HeapUnlock();
}

// Public ///////////////////////////////////////////////////////////////////
//
//  Function:     malloc ()
//
//  Purpose:   Allocate heap memory in a thread safe manner.
//
//////////////////////////////////////////////////////////////////////////////
void * __cdecl malloc( size_t size )
{
    void * result = NULL ;
    if (_HeapLock())
    {
        result = _clib_malloc( size ) ;
        _HeapUnlock() ;
    }
    return result ;
}

#ifdef _FAR_HEAP_TOO
// Public ///////////////////////////////////////////////////////////////////
//
//  Function:     farmalloc ()
//
//  Purpose:   Allocate heap memory in a thread safe manner.
//
//////////////////////////////////////////////////////////////////////////////
void _FAR * __cdecl farmalloc( unsigned long size )
{
    void _FAR * result = NULL ;
    if (_HeapLock())
    {
        result = _clib_farmalloc( size ) ;
        _HeapUnlock() ;
    }
    return result ;
}
#endif // _FAR_HEAP_TOO

// Public ///////////////////////////////////////////////////////////////////
//
//  Function:     free ()
//
//  Purpose:   Release heap memory in a thread safe manner.
//
//////////////////////////////////////////////////////////////////////////////
void __cdecl free( void * p )
{
    _HeapLock() ;
    _clib_free( p ) ;
    _HeapUnlock() ;
}

#ifdef _FAR_HEAP_TOO
// Public ///////////////////////////////////////////////////////////////////
//
//  Function:     farfree ()
//
//  Purpose:   Release heap memory in a thread safe manner.
//
//////////////////////////////////////////////////////////////////////////////
void __cdecl farfree( void _FAR * p )
{
    _HeapLock() ;
    _clib_farfree( p ) ;
    _HeapUnlock() ;
}
#endif // _FAR_HEAP_TOO

// Public ///////////////////////////////////////////////////////////////////
//
//  Function:     realloc ()
//
//  Purpose:   Reallocate heap memory in a thread safe manner.
//
//////////////////////////////////////////////////////////////////////////////
void * __cdecl realloc( void * p, size_t size )
{
    void * result ;
    _HeapLock() ;
    result = _clib_realloc( p, size ) ;
    _HeapUnlock() ;
    return result ;
}

#ifdef _FAR_HEAP_TOO
// Public ///////////////////////////////////////////////////////////////////
//
//  Function:     farrealloc ()
//
//  Purpose:   Reallocate heap memory in a thread safe manner.
//
//////////////////////////////////////////////////////////////////////////////
void _FAR * __cdecl farrealloc( void _FAR * p, unsigned long size )
{
    void _FAR * result ;
    _HeapLock() ;
    result = _clib_farrealloc( p, size ) ;
    _HeapUnlock() ;
    return result ;
}

// Public ///////////////////////////////////////////////////////////////////
//
//  Function:     farcoreleft ()
//
//  Purpose:   Read out amount of heap space remaining.
//
//////////////////////////////////////////////////////////////////////////////

unsigned long __cdecl farcoreleft( void )
{
    unsigned long result ;
    _HeapLock() ;
    result = _clib_farcoreleft() ;
    _HeapUnlock() ;
    return result ;
}

#endif // _FAR_HEAP_TOO

#if (defined( __MEDIUM__) || defined(__SMALL__))
#ifdef _NEAR_HEAP_WALK
// Public ///////////////////////////////////////////////////////////////////
//
//  Function:     _nearHeapWalk ()
//
//  Purpose:   Reallocate heap memory in a thread safe manner.
//
//////////////////////////////////////////////////////////////////////////////
#include <alloc.h>
#include <stdio.h>
#include <helper.h>

void  __cdecl _nearHeapWalk( void )
{
    extern unsigned int _first ;    // First block of near heap.
    extern unsigned int __brklvl ;  // With three underscores (at ASM level)!

    // All data used here is put into data segment so that RTX tasks can 
    //  use this function, when DS != SS.
    static struct heapinfo hi ;

    static unsigned int totalBytes = 0 ;
    static unsigned int inUseBytes = 0 ;
    static unsigned int blockCnt = 0 ;
    static unsigned int inUseBlkCnt = 0 ;
    helper_printf(" --- NEAR HEAP SPAN: [%04X] to [%04X] (%u bytes) ----\r\n",
            _first, __brklvl, __brklvl - _first) ;
    _HeapLock() ;
    hi.ptr = NULL ;
    while(1)
    {
        int status = heapwalk( &hi ) ;
        if (status == _HEAPOK)
        {
            const char far *allocStatus = "Free" ;
            if (hi.in_use)
            {
                inUseBlkCnt++ ;
                inUseBytes += hi.size ;
                allocStatus = "Allocated" ;
            }
            blockCnt++ ;
            totalBytes += hi.size ;
            helper_printf("block [%04X], size=%5u bytes, %s\r\n",
                          hi.ptr, hi.size, allocStatus) ;
        }
        else
        {
            if (status == _HEAPEMPTY)
            {
                helper_printf("near heap is zero size\r\n") ;
            }
            break ;
        }
    }

    helper_printf("Bytes:  Total %5u, Used %5u, Free %5u\r\n",
            totalBytes, inUseBytes, totalBytes - inUseBytes) ;
    helper_printf("Blocks: Total %5u, Used %5u, Free %5u\r\n",
            blockCnt, inUseBlkCnt, blockCnt - inUseBlkCnt) ;
    _HeapUnlock() ;
}

#endif // _NEAR_HEAP_WALK
#endif // (defined( __MEDIUM__) || defined(__SMALL__))


// Private ///////////////////////////////////////////////////////////////////
//
//  Function:     init_rtl_heap ()
//
//  Purpose:   At program start-up, attempt RTX semaphore allocation.
//             For MEDIUM or SMALL memory models, initialize the
//             near heap.
//
//////////////////////////////////////////////////////////////////////////////
static void __cdecl init_rtl_heap(void)
{
#if (defined( __MEDIUM__) || defined(__SMALL__))
    extern void _initNearHeap(void) ;   // in RTL's nheapMT.asm
    _initNearHeap() ;
#endif
    RTX_Create_Sem( &idHeapSemaphore, _HeapSemaName, 0 ) ;
}
#pragma startup init_rtl_heap 16


// Private ///////////////////////////////////////////////////////////////////
//
//  Function:     cleanup_rtl_heap ()
//
//  Purpose:   At program exit, release the RTX semaphore.
//
//////////////////////////////////////////////////////////////////////////////
static void __cdecl cleanup_rtl_heap(void)
{
    if ( idHeapSemaphore )
    {
        RTX_Delete_Sem( idHeapSemaphore ) ;
    }
}
#pragma exit cleanup_rtl_heap 16

// End HEAP.C


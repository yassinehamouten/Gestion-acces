/****************************************************************************
* (C) 1999-2007 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : HELPER.C
* Function       : Some useful helper functions
* ---------------------------------------------------------------------------

$Header: HELPER.C, 37, 20.01.2009 10:19:43, Andre Pribil$

*****************************************************************************/

#include <stdarg.h>
#include <dos.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

#include "config.h"
#include "common.h"
#include "rtos.h"
#include "bios_api.h"
#include "helper.h"

/*
 @doc DOC_INDEX
 ---------------------------------------------------------------
 Helper API Table of Contents
 ---------------------------------------------------------------
 @clibidx  <tab><cfont>#include <InBraces HELPER\.H><efont> |

 @libcat1x  Character |  Output | helper01 |
    helper_strout | String output |
 @libcat1x  Character |  Output | helper02 |
    helper_chrout | Char output |
 @libcat1x  Character |  Output | helper03 |
    helper_dezout | Dezimal output |
 @libcat1x  Character |  Output | helper04 |
    helper_hexdig | Hex digit output |
 @libcat1x  Character |  Output | helper05 |
    helper_hexout | Hex value output |
 @libcat1x  Character |  Output | helper06A |
    helper_printf | Printf output |
 @libcat1x  Character |  Output | helper06 |
    helper_sprintf | String formatting |

 @libcat2x  Memory |   Allocation  | helper07 |
    helper_alloc_rtos_mem | Allocate RTOS memory |
 @libcat2x  Memory |   Allocation  | helper08 |
    helper_release_rtos_mem | Release allocated RTOS memory |
 @libcat2x  Memory |   Allocation  | helper09 |
    helper_alloc_rtos_fast_mem | Allocate RTOS memory from fast memory pool|
 @libcat2x  Memory |   Allocation  | helper0A |
    helper_assign_mem | Assign RTOS memory ownership |
 @libcat2x  Memory |   Allocation  | helperM1 |
    malloc | <nl>Allocate program heap memory |  <tab><tab>--- Reentrant Heap ---<nl>
 @libcat2x  Memory |   Allocation  | helperM2 |
    free | Release program heap memory |
 @libcat2x  Memory |   Allocation  | helperM3 |
    realloc | Reallocate program heap memory |
 @libcat2x  Memory |   Allocation  | helperM4 |
    farcoreleft | Report available memory in far heap |

 @libcat3x  Other |    | helper_clibVersion |
    helper_clibVersion | Get C-Library version number |
 @libcat3x  Other |    | helper0B |
    helper_check_license | Check for installed license |
 @libcat3x  Other |    | helper_load_library |
    helper_load_library | Load a Dynamic Link Library |
 @libcat3x  Other |    | helper_unload_library |
    helper_unload_library | Unload a Dynamic Link Library |
 @libcat3x  Other |  | progParentData | progParentData | Access parent program's data area |
 @libcat3x  Other |  | swap16 | swap16 | Swap a 16 bit value |
 @libcat3x  Other |  | swap32 | swap32 | Swap a 32 bit value |
 @libcat3x  Other |  | hostToLE16 | hostToLE16 | Convert 16 bit value to little endian |
 @libcat3x  Other |  | hostToLE32 | hostToLE32 | Convert 32 bit value to little endian |
 @libcat3x  Other |  | hostToBE16 | hostToBE16 | Convert 16 bit value to big endian |
 @libcat3x  Other |  | hostToBE32 | hostToBE32 | Convert 32 bit value to big endian |
 @libcat3x  Other |  | lEToHost16 | lEToHost16 | Convert 16 bit value from little endian |
 @libcat3x  Other |  | lEToHost32 | lEToHost32 | Convert 32 bit value from little endian |
 @libcat3x  Other |  | bEToHost16 | bEToHost16 | Convert 16 bit value from big endian |
 @libcat3x  Other |  | bEToHost32 | bEToHost32 | Convert 32 bit value from big endian|
*/

/*************************************************************************/
//Private defines used internal by that module
/*************************************************************************/
#define MAX_PATH_LENGTH 128
#define CHIPDLL_INT     0x67

// Application sign-on and return function pointer list
#define CHIPDLL_ISR_SIGNON_DLL                     0x01FF
// Remove an DLL Isr from the cascace list
#define CHIPDLL_ISR_REPLACE_CASCADED_ISR           0x02FF
// Application sign-off
#define CHIPDLL_ISR_SIGNOFF_DLL                    0x03FF

/*************************************************************************/
//Prototypes of private functions used internal by different modules
/*************************************************************************/
char * helper_extractLibName(char *libPath, int * libStringLen);


/////////////////////////////////////////////////////////////////
// Note: Code for the three multitask heap functions
//      is in HEAP.C file.  This file must be linked into
//      the user's project file.
/////////////////////////////////////////////////////////////////

/*
 @doc DOC_helperM1_
 ---------------------------------------------------------------
 malloc
 ---------------------------------------------------------------
 @clib_nl  malloc | Reentrant malloc() for use with multitasking.  |
        <cfont>void * malloc (unsigned int size); <efont> |
 @parm  int | size  | Number of bytes to allocate from heap.
 @rdesc Pointer to newly allocated memory on success<nl>
        NULL pointer on allocation failure<nl>
 @comm  This function provides semaphore protection
     around the compiler's standard C-library malloc() function.<nl>
     <nl>
     <bold>This function is available only with the Paradigm Beck IPC Edition
     compiler.<bolde><s2> The necessary hooks into the compiler's Run-Time 
     Library (RTL) are not available with other compilers.<nl>
     <nl>
     This function is not part of the Beck C-Library.<s2>
     You must link the provided HEAP.C source file directly into your
     project to use this reentrant heap manager.<s2> This source file can be
     found in the Paradigm Beck IPC Edition compiler's installation
     area in the Source/Beck directory.<nl>
     <nl>
     These alternative heap functions may only be linked with the
     single-threaded Run-Time Library (RTL).<s2> An equivalent to these
     heap functions is already built into either of the multi-threaded
     Paradigm RTL optional libraries, so there is no need for this
     HEAP.C source file when the multi-tasking libraries are used.
     <nl><nl>
     The reentrant malloc(), 
     <linkto>helperM2.htm<linkmid>free()<linktail>,
     <linkto>helperM3.htm<linkmid>realloc()<linktail> and
     <linkto>helperM4.htm<linkmid>farcoreleft()<linktail> come together
     as one package inside the HEAP.C source file.<nl>
     <nl>
     Refer to your compiler's standard library documentation
     for a description of this API's basic functionality.<nl>
     <nl>
     Note:
     <ul>
        A further alternative for a multi-tasking far heap is offered by the
        <linkto>../BeckHeap/BeckHeap.htm<linkmid>BeckHeap library<linktail>.
        The density of objects is greater with the BeckHeap, and it resolves
        the
        <linkto>../../config.htm#DOSLOADER_MEMGAP<linkmid>MEMGAP<linktail>
        problem.
     <ule>

 @Also  helper07.htm | helper_alloc_rtos_mem |
        helperM2.htm | free  |
        helperM3.htm | realloc
 @Also  helperM4.htm | farcoreleft |
         |   |
         | 
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/


/*
 @doc DOC_helperM2_
 ---------------------------------------------------------------
 free
 ---------------------------------------------------------------
 @clib_nl  free | Reentrant free() for use with multitasking.  |
        void free (void * p);  |
 @parm  int | p  | Pointer to heap memory to be released.
 @rdesc -- none --<nl>
 @comm   This function provides semaphore protection
     around the compiler's standard C-library free() function.<nl>
     <nl>
     <bold>This function is available only with the Paradigm Beck IPC Edition
     compiler.<bolde><s2> Refer to the reentrant
     <linkto>helperM1.htm<linkmid>malloc()<linktail> description
     for more details on how to install this version of free() into your 
     program.<nl>
     <nl>
     Refer to your compiler's standard library documentation
     for a description of this API's basic functionality.<nl>

 @Also  helperM1.htm | malloc  |
        helperM3.htm | realloc |
        helperM4.htm | farcoreleft 
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/

/*
 @doc DOC_helperM3_
 ---------------------------------------------------------------
 realloc
 ---------------------------------------------------------------
 @clib_nl  realloc | Reentrant realloc() for use with multitasking. |
        void * realloc (void * p, unsigned int size);  |
 @parm  int | p  | Pointer to heap memory to be reallocated.
 @parm  int | size  | Number of bytes for new allocation.
 @rdesc Pointer to newly allocated memory on success<nl>
        NULL pointer on allocation failure<nl>
 @comm   This function provides semaphore protection
     around the compiler's standard C-library realloc() function.<nl>
     <nl>
     <bold>This function is available only with the Paradigm Beck IPC Edition
     compiler.<bolde><s2> Refer to the reentrant
     <linkto>helperM1.htm<linkmid>malloc()<linktail> description
     for more details on how to install this version of realloc() into your 
     program.<nl>
     <nl>
     Refer to your compiler's standard library documentation
     for a description of this API's basic functionality.<nl>
 @Also  helperM1.htm | malloc  |
        helperM2.htm | free |
        helperM4.htm | farcoreleft 
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/


/*
 @doc DOC_helperM4_
 ---------------------------------------------------------------
 free
 ---------------------------------------------------------------
 @clib_nl  farcoreleft | Reentrant farcoreleft() for use with multitasking.  |
        unsigned long farcoreleft (void);  |
 @rdesc Amount of heap memory available<nl>
 @comm   This function provides semaphore protection
     around the compiler's standard C-library <code>farcoreleft()<codee> function.<nl>
     <nl>
     <bold>This function is available only with the Paradigm Beck IPC Edition
     compiler.<bolde><s2> Refer to the reentrant
     <linkto>helperM1.htm<linkmid>malloc()<linktail> description
     for more details on how to install this version of <code>coreleft()<codee> into your 
     program.<nl>
     <nl>
     Refer to your compiler's standard library documentation
     for a description of this API's basic functionality.<nl>
     <nl>
     For COMPACT, LARGE and HUGE memory models, this function must be used
     instead of <code>coreleft()<codee> in order to have the heap semaphore
     protection.<s2> The <code>coreleft()<codee> name will reach the same
     RTL function, but without the surrounding semaphore protection.

 @Also  helperM1.htm | malloc  |
        helperM3.htm | realloc |
        helperM2.htm | free
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/

/*
 @doc DOC_swap16_
 ---------------------------------------------------------------
  swap16()
 ---------------------------------------------------------------
 @clib_nl  swap16 | This macro function swaps a 16 bit value |
           swap16(x) |
 @parm     unsigned short | x | Value to be swapped
 @rdesc    Swapped 16 bit value

 @target_clib V2.16
*/



/*
 @doc DOC_swap32_
 ---------------------------------------------------------------
  swap32()
 ---------------------------------------------------------------
 @clib_nl  swap32 | This macro function swaps a 32 bit value |
           swap32(x) |
 @parm     unsigned long | x | Value to be swapped
 @rdesc    Swapped 32 bit value

 @target_clib V2.16
*/



/*
 @doc DOC_hostToLE16_
 ---------------------------------------------------------------
  hostToLE16()
 ---------------------------------------------------------------
 @clib_nl  hostToLE16 | This macro function converts a 16 bit value from host's
           endianess to little endian. |
           hostToLE16(x) |
 @parm     unsigned short | x | Value to be converted
 @rdesc    Converted 16 bit value

 @target_clib V2.16
*/



/*
 @doc DOC_hostToLE32_
 ---------------------------------------------------------------
  hostToLE32()
 ---------------------------------------------------------------
 @clib_nl  hostToLE32 | This macro function converts a 32 bit value from host's
           endianess to little endian. |
           hostToLE32(x) |
 @parm     unsigned long | x | Value to be converted
 @rdesc    Converted 32 bit value

 @target_clib V2.16
*/



/*
 @doc DOC_hostToBE16_
 ---------------------------------------------------------------
  hostToBE16()
 ---------------------------------------------------------------
 @clib_nl  hostToBE16 | This macro function converts a 16 bit value from host's
           endianess to big endian. |
           hostToBE16(x) |
 @parm     unsigned short | x | Value to be converted
 @rdesc    Converted 16 bit value

 @target_clib V2.16
*/



/*
 @doc DOC_hostToBE32_
 ---------------------------------------------------------------
  hostToBE32()
 ---------------------------------------------------------------
 @clib_nl  hostToBE32 | This macro function converts a 32 bit value from host's
           endianess to big endian. |
           hostToBE32(x) |
 @parm     unsigned long | x | Value to be converted
 @rdesc    Converted 32 bit value

 @target_clib V2.16
*/



/*
 @doc DOC_lEToHost16_
 ---------------------------------------------------------------
  lEToHost16()
 ---------------------------------------------------------------
 @clib_nl  lEToHost16 | This macro function converts a 16 bit value from little
           endian to host's endianess. |
           lEToHost16(x) |
 @parm     unsigned short | x | Value to be converted
 @rdesc    Converted 16 bit value

 @target_clib V2.16
*/



/*
 @doc DOC_lEToHost32_
 ---------------------------------------------------------------
  lEToHost32()
 ---------------------------------------------------------------
 @clib_nl  lEToHost32 | This macro function converts a 32 bit value from little
           endian to host's endianess. |
           lEToHost32(x) |
 @parm     unsigned long | x | Value to be converted
 @rdesc    Converted 32 bit value

 @target_clib V2.16
*/



/*
 @doc DOC_bEToHost16_
 ---------------------------------------------------------------
  bEToHost16()
 ---------------------------------------------------------------
 @clib_nl  bEToHost16 | This macro function converts a 16 bit value from big
           endian to host's endianess. |
           bEToHost16(x) |
 @parm     unsigned short | x | Value to be converted
 @rdesc    Converted 16 bit value

 @target_clib V2.16
*/



/*
 @doc DOC_bEToHost32_
 ---------------------------------------------------------------
  bEToHost32()
 ---------------------------------------------------------------
 @clib_nl  bEToHost32 | This macro function converts a 32 bit value from big
           endian to host's endianess. |
           bEToHost32(x) |
 @parm     unsigned long | x | Value to be converted
 @rdesc    Converted 32 bit value

 @target_clib V2.16
*/



#ifdef _helper01_
/*
 @doc DOC_helper01_
 ---------------------------------------------------------------
 Strout
 ---------------------------------------------------------------
 @clib  helper_strout | String output function |
        <cfont>void helper_strout ( const char far *str ); <efont> |
 @parm  char far | str  | Zero terminated output string to print over STDOUT
 @rdesc -- none --
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../dosemu.htm#0x210x09<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void helper_strout( const char far *s )
{
  asm push ds
  asm lds  dx, s
  asm mov  ah, 0x9
  asm int  0x21
  asm pop  ds
} // helper_strout
#endif


#ifdef _helper02_
/*
 @doc DOC_helper02_
 ---------------------------------------------------------------
 Chrout
 ---------------------------------------------------------------
 @clib  helper_chrout | Character output function |
        <cfont>int helper_chrout ( char ch, int zero ); <efont> |
 @parm  char  | ch    | Character to print over STDOUT
 @parm  int   | zero  | Zero-Mode<nl>
                        if ch<gt>=10 zero is ignored.<nl>
                        if ch<lt>10 zero is ignored but the character printed out is ch + 48.<nl>
                        if ch==0 and zero==0 character print is ch + 48.<nl>
                        if ch==0 and zero <lt> 0 no character is printed<nl>
                        if ch==0 and zero <gt> 0 a space character is printed.<nl>
 @rdesc Value in zero is returned
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0x100x0E<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
int helper_chrout( char ch, int zero )
{
  if( ch < 10 )
  {
    if( ch || ( zero == 0 ))
    {
      zero = 0;
      _AL = '0' + ch;

    }
    else
    {
      if( zero < 0 )
        return zero;

      _AL = ' ';

    } // if

  }
  else
  {
    _AL = ch;
  }

  _AH = 0xE;
  _BH = 0;
  asm int 10h

  return zero;

} // helper_chrout
#endif


#ifdef _helper03_
/*
 @doc DOC_helper03_
 ---------------------------------------------------------------
 Dezout
 ---------------------------------------------------------------
 @clib  helper_dezout | Character output function |
        <cfont>void helper_dezout ( unsigned int x, int zero ); <efont> |
 @parm  int   | x     | Decimal value to print over STDOUT
 @parm  int   | zero  | Zero-Mode<nl>
                        if zero==0, leading zeros are printed as zeros.<nl>
                        if zero<lt>0, leading zeros are not printed<nl>
                        if zero<gt>0, leading zeros are printed as spaces.<nl>
 @rdesc -- none --
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0x100x0E<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void helper_dezout( unsigned int x, int zero )
{
  zero = helper_chrout( x / 10000,zero );
  x %= 10000;

  zero = helper_chrout( x / 1000,zero );
  x %= 1000;

  zero = helper_chrout( x / 100,zero );
  x %= 100;

  helper_chrout( x / 10,zero );
  helper_chrout( x % 10,0 );

} // helper_dezout
#endif


#ifdef _helper04_
/*
 @doc DOC_helper04_
 ---------------------------------------------------------------
 Hexdig
 ---------------------------------------------------------------
 @clib  helper_hexdig | Hexadecimal digit output function |
        <cfont>void helper_hexdig ( unsigned char dig ); <efont> |
 @parm  char  | dig  | Hexadecimal digit (nibble) to print over STDOUT
 @rdesc -- none --
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0x100x0E<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void helper_hexdig( unsigned char dig )
{
  dig &= 0xF;

  if( dig > 9 )
    dig += 'A' - 10;
  else
    dig += '0';

  helper_chrout( dig,-1 );

} // helper_hexdig
#endif


#ifdef _helper05_
/*
 @doc DOC_helper05_
 ---------------------------------------------------------------
 Hexout
 ---------------------------------------------------------------
 @clib  helper_hexout | Hexadecimal integer output function |
        <cfont>void helper_hexout ( unsigned int hex ); <efont> |
 @parm  int  | hex  | Hexadecimal integer to print over STDOUT
 @rdesc -- none --
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0x100x0E<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void helper_hexout( unsigned hex )
{
  helper_chrout( '0', -1 );
  helper_chrout( 'x', -1 );
  helper_hexdig( hex >> 12 );
  helper_hexdig( hex >>  8 );
  helper_hexdig( hex >>  4 );
  helper_hexdig( hex       );

} // helper_hexout
#endif

extern int _Get_Sprintf(void) ;     // Share with  helper_printf()
extern Sprintf_Fptr _sprintf_fptr ;
extern char         _printf_direct ;

#ifdef _helper06_
/*
 @doc DOC_helper06_
 ---------------------------------------------------------------
 printf
 ---------------------------------------------------------------
 @clib  helper_sprintf | String formatting like the standard 
   library <cfont>sprintf<efont> function. |
        <cfont>int helper_sprintf (char *buffer,<nl>
        <tab><tab><tab><tab><tab>const char *fmt, ... ); <efont> |
 @parm  char *  | buffer  | Output parameter:<s2> Formatted text
    will be written into this buffer.
 @parm  char *  | fmt  | Format specifier string.<s2> Note: Floating
    point types are not suppported by this implementation.
 @rdesc
   Number of characters output to <cfont>buffer<efont> not counting
   the final NIL string terminating character.<s2> (If @Chip-RTOS version does
   not support this function, then this return value will always be zero.)
 @comm
   Using this function instead of the standard library <cfont>sprintf<efont>
   will reduce a program's memory requirements.<nl>
   <nl>
   <hangpara 6:18>
   <bold>WARNING for small and medium memory models:<bolde><paraend>
   <nl>
   Pointers which are passed to this function after the
    first two declared arguments must be explicitly cast as type "far".<s2>
    (Compiler has no clue about these additional arguments
   so your help is needed.)<s2> For example:<nl>
   <nl>
   <tab><cfont>helper_sprintf(buffer, format, (char far *)string);<efont><nl>
   <nl>
   The exception to this rule are pointers
   for display with the %p format.<s2> These are taken as long by default
   (regardless of your program's memory model) and can be specified explicitly
   as near with the N input format modifier, in which case you should only 
   pass a 16 bit pointer.<s2>  See your compiler's  
   <cfont>sprintf<efont> documentation for more details.<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x56<linkmid>documentation<linktail>
        for more details.
 @target      SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     V1.20 | V1.20 | V1.20 | V0.91 | V1.00

 @target_clib V2.03
*/
Sprintf_Fptr _sprintf_fptr ;
char         _printf_direct ;       // Boolean flag

// _Get_Sprintf() returns 0 on success.
int _Get_Sprintf(void)              // Shared with helper_printf()
{
    _BX = 0 ;               // For RTOS version detection.
    _AH = 0x56 ;
    //get pointer of rtos internal sprintf function
    asm{ int 0xA0 } ;       // BIOS SWI
    // BX = 0x1 if vsprintf() suppports direct console output.
    _printf_direct = _BL ;  
    if (_AX==0)
    {
        _sprintf_fptr =  MK_FP(_ES,_DI);
    }
    return _AX ;

}   /* End _Get_Sprintf() */

 
int helper_sprintf(char *buffer, const char *fmt, ...)
{
    int rslt = 0;
    
    if (  (FP_SEG(_sprintf_fptr) != 0)  // Vector set?
        ||(_Get_Sprintf() == 0)         // Now vector is set?
       )
    {
        void far *parg;
        va_start(parg, fmt);
        rslt = (*_sprintf_fptr)(buffer, fmt, parg);
        va_end(parg);
    }
    return rslt ;

} // helper_sprintf
#endif

#ifdef _helper06A_
/*
 @doc DOC_helper06A_
 ---------------------------------------------------------------
 printf
 ---------------------------------------------------------------
 @clib  helper_printf | Formatted console output function like the standard 
   library <cfont>printf<efont> function. |
        <cfont>int helper_printf ( const char *fmt, ... ); <efont> |
 @parm  char *  | fmt  | Format specifier string.<s2> Note: Floating
    point types are not suppported by this implementation.
 @rdesc
   Number of characters output to console.<s2> (If @Chip-RTOS version does
   not support this function, then this return value will always be zero.)
 @comm
   Using this function instead of the standard library <cfont>printf<efont>
   will reduce a program's memory requirements.<nl>
   <nl>
   <hangpara 6:18>
   <bold>WARNING for small and medium memory models:<bolde><paraend>
   <nl>
   Pointers which are passed to this function after the
    first declared argument must be explicitly cast as type "far".<s2>
    (Compiler has no clue about these additional arguments
   so your help is needed.)<s2>   For example:<nl>
   <nl>
   <tab><cfont>helper_printf(format, (char far *)string);<efont><nl>
   <nl>
    The exception to this rule are pointers
   for display with the %p format.<s2> These are taken as long by default
   (regardless of your program's memory model) and can be specified explicitly
   as near with the N input format modifier, in which case you should only 
   pass a 16 bit pointer.<s2>  See your compiler's <cfont>printf<efont> 
   documentation for more details.<nl>
   <nl>
   <hangpara 6:18>
   <bold>CAUTION:<bolde><paraend>
   <nl>
   When this function is used with SC1x @Chip-RTOS versions prior to 
   version 1.20 a stack buffer will overflow if the total number of
   characters headed to the console exceeds 179 characters.<s2> For
   subsequent @Chip-RTOS versions there is no such limitation.<nl>

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x56<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V0.91 | V1.00
*/

///////////////////////////////////////////////////////
// To cover for old RTOS versions.
static int near old_printf(const char * fmt,
                           void far   * parg)
{
  char bfr[180];
  int  rslt = (*_sprintf_fptr)(bfr, fmt, parg);
  helper_strout(bfr);
  return rslt;

} // old_printf()

///////////////////////////////////////////////////////
int helper_printf(const char *fmt, ...)
{
    int rslt = 0;
    
    if (  (FP_SEG(_sprintf_fptr) != 0)  // Vector set earlier?
        ||(_Get_Sprintf() == 0)         // Vector is set now?
       )
    {
        void far *parg ;
        va_start(parg, fmt) ;
        if (_printf_direct == 0)        // Old RTOS that needs stack buffer?
        {
            rslt = old_printf(fmt, parg) ;  // Need caller's stack space.
        }
        else
        {
            // Output directly to console through the RTOS's vsprintf().
            rslt = (*_sprintf_fptr)(MK_FP(0, 0x22), fmt, parg);
        }
        va_end(parg);
    }
    return rslt;

} // helper_printf
#endif


#ifdef _helper07_
/*
 @doc DOC_helper07_
 ---------------------------------------------------------------
  System Heap Memory
 ---------------------------------------------------------------
 @clib  helper_alloc_rtos_mem | Allocate memory from @CHIP-RTOS memory pool (Int21h function 48h) |
        <cfont>unsigned int helper_alloc_rtos_mem(unsigned long size);<efont> |
 @parm  long  | size  | Requested memory size in bytes
 @rdesc If 0, memory allocation failed.
        Else segment of the allocated memory area

 @comm The returned segment can be used to build a normalized pointer to the allocated memory area e.g.
       <cfont>seg=helper_alloc_rtos_mem(1024);<nl>
       ptr = MK_FP(seg,0);<efont>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../dosemu.htm#0x210x48<linkmid>documentation<linktail>
        for more details.
 @Also   helper08.htm | helper_release_rtos_mem  |
         helper09.htm | helper_alloc_rtos_fast_mem |
         helper0A.htm | helper_assign_mem
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned int helper_alloc_rtos_mem(unsigned long size)
{
    // Required paragraph count-> BX.
  _BX = (unsigned int)((size + SEG_MASK) >> SEG_SHIFT) ;
  _AH = 0x48;
  asm int 21h
  return _AX;
}
#endif

#ifdef _helper08_
/*
 @doc DOC_helper08_
 ---------------------------------------------------------------
  System Heap Memory
 ---------------------------------------------------------------
 @clib  helper_release_rtos_mem | Release allocated RTOS memory (Int21h function 49h) |
        <cfont>int helper_release_rtos_mem(unsigned int seg);<efont> |
 @parm  int  | seg  | Segment of the memory area to be released
 @rdesc 0 success<nl>
        -1 failed<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../dosemu.htm#0x210x49<linkmid>documentation<linktail>
        for more details.
 @Also  helper07.htm | helper_alloc_rtos_mem |
        helper09.htm | helper_alloc_rtos_fast_mem  | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int helper_release_rtos_mem(unsigned int seg)
{
  unsigned int ax_tmp;

  _ES=seg;
  _AH=0x49;
  asm int 21h

  ax_tmp=_AX;

  if((_FLAGS & 0x0001/*CF*/) && (ax_tmp==9))
  {
     return -1;
  }
  return 0;
}
#endif

#ifdef _helper09_
/*
 @doc DOC_helper09_
 ---------------------------------------------------------------
  System Heap Memory
 ---------------------------------------------------------------
 @clib  helper_alloc_rtos_fast_mem | Allocate memory from @CHIP-RTOS fast memory pool
        (BIOSIntA0h function 57h) |
        <cfont>unsigned int helper_alloc_rtos_fast_mem(unsigned long size);<efont> |
 @parm  long  | size  | Requested memory size in bytes
 @rdesc If 0, memory allocation failed.
        Else segment of the allocated memory area

 @comm The returned segment can be used to build a normalized pointer 
        to the allocated memory area in the manner shown here:<nl>
        <ol><nl>
       <cfont>seg=helper_alloc_rtos_fast_mem(1024);<nl>
       ptr = MK_FP(seg,0);<efont><nl>
       <nl>
       <ole>
       This allocated memory can be released with the 
       <linkto>helper08.htm<linkmid>helper_release_rtos_mem<linktail> API.<nl>
       <nl>
       <bold>Note:<bolde><nl>
       <nl>
       The software Cryptographic Engine used by 
       <linkto>../../config.htm#SSH_ENABLE<linkmid>SSH<linktail>,
       <linkto>../TCPIP/lib_index.htm#PKI<linkmid>SSL<linktail> or
       <linkto>../../ipsecover.htm<linkmid>IPsec<linktail> will
       operate noticeably quicker during key negotiation 
       (e.g. Diffie-Hellmann, RSA, DSS) if a
       block of memory in the fast memory pool is available.<s2>
       A memory block of roughly 45 Kbyte size is required
       by the Cryptographic Engine.<s2> If the block is not
       available in this fast RAM area, then an attempt is
       made to allocate it from the normal system memory as a 
       last resort.<nl>

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x57<linkmid>documentation<linktail>
        for more details.
 @Also  helper07.htm | helper_alloc_rtos_mem |
        helper08.htm | helper_release_rtos_mem  |
        helper0A.htm | helper_assign_mem
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00
*/
unsigned int helper_alloc_rtos_fast_mem(unsigned long size)
{
    // Required paragraph count-> BX.
  _BX = (unsigned int)((size + SEG_MASK) >> SEG_SHIFT) ;
  _AH = 0x57;
  asm int 0A0h
  return _AX;
}
#endif

#ifdef _helper0A_
/*
 @doc DOC_helper0A_
 ---------------------------------------------------------------
  System Heap Memory
 ---------------------------------------------------------------
 @clib  helper_assign_mem | Assign memory block ownership to
    a specific task. |
        int helper_assign_mem(void far *mem_block, unsigned int taskid); |
 @parm  long  | mem_block  | Pointer to RTOS system memory block.
 @parm  int   | taskid  | Task ID of the
 <linkto>../RTX/RTX01.htm<linkmid>task<linktail> to assign the ownership
  of this memory block.<s2> This parameter may be set to zero to
  assign ownership to the current task which is making this call.
 @rdesc error code<nl>
    <ul>
    0:<s2> Success<nl>
    -1:<s2>Invalid task ID parameter, <code>taskid<codee><nl>
    -38:<s2>Invalid RTOS memory pointer, <code>mem_block<codee><nl>.
    <ule>
 @comm
   The referenced memory block must be one that originated from one of the
   RTOS <linkto>../../dosemu.htm#0x210x48<linkmid>system memory<linktail>
   allocators.<s2>  This includes those blocks allocated by either
   <linkto>helper07.htm<linkmid>helper_alloc_rtos_mem<linktail>
   or <linkto>helper09.htm<linkmid>helper_alloc_rtos_fast_mem<linktail>
   API.<nl>
   <nl>
   This function can be useful to control the lifespan of a
   given block of memory.<s2> After the specified task has been
   assigned ownership of this memory block, this memory block
   will automatically be released when that task is
   <linkto>..\RTX\rtx03.htm<linkmid>deleted<linktail>
   from the system if the block had not already been released.<nl>
   <nl>
   A task's stack space allocated from RTOS memory can safely
   be released in this manner.<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x48<linkmid>documentation<linktail>
        for more details.
 @Also  helper07.htm | helper_alloc_rtos_mem |
        helper09.htm | helper_alloc_rtos_fast_mem |
        helper08.htm | helper_release_rtos_mem
 @Also  ..\RTX\rtx03.htm | RTX_Delete_Task  |
         |  |
         | 
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.23 | V1.23 | V1.23 | V1.12 | V1.00
 @target_clib V2.09
*/
int helper_assign_mem(void far *mem_block, unsigned int taskid)
{
  _BX = FP_OFF(mem_block) ;
  _ES = FP_SEG(mem_block) ;
  _CX = taskid ;
  _AH = 0x48;
  asm int 0A0h
  return _AX;
}
#endif


/*
 @doc DOC_helper0B_
 ---------------------------------------------------------------
  Check for installed license
 ---------------------------------------------------------------
 @clib  helper_check_license | Check for installed license. |
        int helper_check_license(unsigned char id,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned char far *secret,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned short length); |
 @parm  unsigned char  | id  | ID of license key
 @parm  unsigned char far * | secret  | Pointer to secret key
 @parm  unsigned short | length  | Length of secret key in bytes
 @rdesc error code<nl>
    <ul>
    0:<s2> Success, found a valid license<nl>
    -1:<s2> Error, no valid license for specified ID found<nl>
    -2:<s2> Error, reading product data failed<nl>
    -3:<s2> Error, MD5 functions failed<nl>
    <ule>
 @comm The function validates that a license for the specified ID is installed correctly.
       Computers without a valid license can be rejected by calling this function.
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x5A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.27 | V1.27 | V1.27 | V1.35 | V1.35
 @target_clib V2.18
*/


#ifdef _helper_load_library_
/*
 @doc DOC_helper_load_library_
 ---------------------------------------------------------------
  Load Dynamic Link Library
 ---------------------------------------------------------------
 @clib  helper_load_library | Load and link a dynamic link library (DLL). |
        int helper_load_library( const char far * libName,<nl>
        <tab><tab><tab><tab><tab><tab> void far * pFpl,<nl>
        <tab><tab><tab><tab><tab><tab> int * pFplSize,<nl>
        <tab><tab><tab><tab><tab><tab> int maxFplSize); |
 @parm  char far * | libName | File name of the DLL (with extension!)
 @parm  void far * | pFpl    | Output Parameter:<s2> Pointer to the 
                               vector list where on success
                               the addresses of the DLL's exported functions
                               will be written.
 @parm  int * | pFplSize | Output Parameter:<s2> The number of bytes 
                    written to the vector table at <i>pFpl<ie> will
                    be reported here.<s2>  This will be at most
                    <i>maxFplSize<ie> bytes.
 @parm  int   | maxFplSize  | Maximal size of vector table
        at <i>pFpl<ie>, in bytes.
 @rdesc error code<nl>
    <ul>
    CHIPDLL_ERR_OK:<s2> Success, DLL was loaded and functions were exported<nl>
    CHIPDLL_ERR_COULDNTLD: <s2> DLL could not be loaded<nl>
    CHIPDLL_ERR_NOTFOUND:  <s2> The dll was not found<nl>
    DLL specifix error code, defined by the DLL developer.<nl>
    <ule>
 @comm If the DLL is not yet loaded, this function loads and starts the DLL.<nl>
        <nl>
       The order of the exported functions in the function pointer list
       is equal to the order in the DLL,s project export function declaration.<nl><nl>
        Example:
 @raw
        <code>
        struct MYDLL
        {
          int  (*myFirstDllFunction)(int k);
          long (*mySecondDllFunction)(char *s);
        };

        int result;
        int fplSize;
        struct MYDLL myDll;

        // Sign in to the DLL. When the DLL is not loaded yet it will be loaded automatically.
        result = helper_load_library( "myLibrary.dll", &myDll, &fplSize, sizeof(myDll) );
        if (result != CHIPDLL_ERR_OK)
        {
          // Error while load DLL!
          return -1;
        }

        if ( fplSize < sizeof(myDll) )
        {
          // Not all functions linked! Maybe it is an older
          // version of the DLL ?
          helper_unload_library( "myLibrary.dll" );
          return -2;
        }

        // Now the DLL's function can be called
        myDll.myFirstDllFunction(5);
        myDll.mySecondDllFunction("hello");

        // When the DLL is no longer required, the application should sign off.
        // When no more applications are signed in, the DLL will be removed from memory.
        helper_unload_library( "myLibrary.dll" );
        <codee>
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.10 | V1.00
 @target_clib V2.13
*/

//
// internal function, used by helper_load_library
//
static int near helper_getFunctionPointerList(char * libName, void far * (*pFpl) )
{
  // declare all variables as "volatile" cause they must not
  // allocated in registers. Note that the ChipDLL Isr does
  // modify the DI register!!
  volatile int dLLNameLen     = strlen(libName);
  volatile char far *pAckDLLName;
  volatile int       ackDLLNameLen;
  volatile void far *fpl;
  volatile int      fplLen;

  volatile unsigned short RES = 0;
  volatile unsigned short RBX = 0;


  asm pusha; // DI and SI must not be modfied! (they could hold local vars)

  RTX_Disable_Task_Scheduling(); // enter critical section

  // call the DLLs interrupt routine
  _ES = FP_SEG((void far *)libName);
  _BX = FP_OFF((void far *)libName);
  _CX = dLLNameLen;
  _AX = CHIPDLL_ISR_SIGNON_DLL;
  asm int CHIPDLL_INT;

  fplLen        = _AX;
  ackDLLNameLen = _CX;
  pAckDLLName   = (char far *)MK_FP(_DX, _DI);
  //fpl = (struct CHIPDLL_FUNTIONTABLE *)MK_FP(_ES, _BX);
  RBX = _BX;
  RES = _ES;
  fpl = (struct CHIPDLL_FUNTIONTABLE far *)MK_FP(RES, RBX);

  RTX_Enable_Task_Scheduling(); // leave critical section

  asm popa; // DI and SI must not be modfied! (they could hold local vars)

  // check if the function table pointer was initialized by the driver
  if ( (void far *)fpl == (void far *)libName
   || !( dLLNameLen == ackDLLNameLen
      && _fmemcmp( (void far *)libName, pAckDLLName, dLLNameLen)==0 ))
  {
    // error, may be DLL is not loaded yet ?
    *pFpl = NULL;
    return 0;
  }
  else
  {
    // success, function pointer list ist valid now
    *pFpl = fpl;
    return fplLen;
  }
}

//
// internal function, used by "helper_load_library" and "helper_unload_library".
// It gets a path string (optionally with drive letter and
// directories) and returns the pointer to the beginning of the filename.
// Also it removes the extension ".DLL" if exists.
//
char * helper_extractLibName(char *libPath, int * libPathStrLen)
{
  char *pLibName;

  *libPathStrLen = strlen(libPath);

  // 1st - search for last '\\' or ':' (or first from back)
  pLibName = &libPath[*libPathStrLen];
  while (*pLibName != '\\' && *pLibName != ':'&& pLibName != &libPath[0])
  {
    pLibName--;
  }

  // 2nd - remove extension (".DLL")
  if ( *libPathStrLen>=4 && stricmp( &libPath[ *libPathStrLen - 4 ], ".DLL" ) == 0 )
  {
     // remove the extension from the cmdline
     *libPathStrLen -= 4;
     libPath[ *libPathStrLen ] = '\0';
  }

  return pLibName;
}


/*
#pragma option -k   //  Workaround if Standard Stack Frame Option is switched off
static int huge _dllInitCallback(long l)
{
    gDllLoadState = (int)l;
    return 0;
}
#pragma option -k.  //  Reset Standard Stack Frame Option
*/

int helper_load_library (const char * libPath,    // filename, e.g "a:\\mydll.exe"
                         void * pFpl,       // pointer to the function pointer list
                         int  * pFplLen,    // size of the result fpl in bytes
                         int    maxFplSize) // maximal size of fpl in bytes
{
  char *pLibName;
  char cmdLine[MAX_PATH_LENGTH + 13 + 1];
                     // DLL name could be up to 255 characters including ".DLL"
                     // plus command line argument "Callback pointer"
                     // example: "A:\\mydll.exe /c 1234:5678"
  int  cmdLineLen = 0;
  void far *dllFpl;
  int  dllFplLen;
  int _dllLoadState;

  // assume error
  *pFplLen = 0;

  // create copy of libPath
  strncpy(cmdLine, libPath, MAX_PATH_LENGTH );

  // extract the filename (without DLL extension) from path
  pLibName = helper_extractLibName(cmdLine, &cmdLineLen);

  // try to get function pointer list (sign on)
  if ( ( dllFplLen=helper_getFunctionPointerList(pLibName, &dllFpl) ) <= 0)
  {
     // check if the DLL file exists
     if (access(libPath, 0) == 0)
     {
        // append callback commandline argument
        strcat(cmdLine, ".dll /C ");
        itoa( FP_SEG((void far *)&_dllLoadState),
              &cmdLine[strlen(cmdLine)],
              0x10 );
        strcat(cmdLine, ":");
        itoa( FP_OFF((void far *)&_dllLoadState),
              &cmdLine[strlen(cmdLine)],
              0x10 );

    /*
        Use strcat instead of snprintf to save ressources
        snprintf(&cmdLine[cmdLineLen], sizeof(cmdLine)-cmdLineLen-1,
                 ".dll /C %04X:%04X",
                 FP_SEG((void far *)&_dllLoadState),
                 FP_OFF((void far *)&_dllLoadState) );
    */

        // init the dll load state variable (will be modified by callback function)
        _dllLoadState = CHIPDLL_ERR_BLOCKING;

        // try to load it
        if (BIOS_Execute(cmdLine) != 0)
        {
            return CHIPDLL_ERR_COULDNTLD; // DLL could not be loaded!
        }

        RTX_Sleep_Time(1); // give DLL time to execute startup code
                          // (respectively shrink used memory)


        // wait until DLL is loaded and callback was called
        while (_dllLoadState == CHIPDLL_ERR_BLOCKING)
        {
            RTX_Sleep_Time(10);
        }

        // check if loading was successful
        if (_dllLoadState < 0)
        {
           // init has still failed, so return with the error
           return _dllLoadState; // Error while DLL load process!
        }

        // remove the added extension ".dll" and the commandline
        // arguments from BIOS_Execute() call
        cmdLine[cmdLineLen] = '\0';

        // try to sign in
        if ( ( dllFplLen=helper_getFunctionPointerList(pLibName, &dllFpl) ) <= 0)
        {
           // init has still failed, so return with an error
           return CHIPDLL_ERR_COULDNTLD; // Error while DLL load process!
        }
     }
     else
     {
        return CHIPDLL_ERR_NOTFOUND; // DLL file not found!
     }
  }

  if (maxFplSize < dllFplLen)
  {
    // The dll exports more functions than the application expects.
    // Export only the number of function that the app expects!
    *pFplLen = maxFplSize;
  }
  else
  {
    // The application expects more function than the DLL exports.
    // Export all DLL function and inform the application about the
    // number of exported functions.
    *pFplLen = dllFplLen;
  }

  _fmemcpy( (void far *)pFpl, dllFpl, *pFplLen );
  return CHIPDLL_ERR_OK; // success
}
#endif  // _helper_load_library_

#ifdef _helper_unload_library_
/*
 @doc DOC_helper_unload_library_
 ---------------------------------------------------------------
  Unload Dynamic Link Library
 ---------------------------------------------------------------
 @clib  helper_unload_library | Unload a dynamic link library. |
        int helper_unload_library( const char far * libName); |
 @parm  char far * | libName | Filen ame of the DLL (with extension!)
 @rdesc error code<nl>
    <ul>
    CHIPDLL_ERR_OK:<s2> Success, DLL was unloaded successfully<nl>
    <ule>
 @comm If there are no more applications signed on to the DLL,
       it will be removed from memory within this call.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.10 | V1.00
 @target_clib V2.13
*/
int helper_unload_library(const char *libPath)
{
  char *pLibName;
  char cmdLine[MAX_PATH_LENGTH + 13 + 1];
                     // DLL name could be up to 255 characters including ".DLL"
                     // plus command line argument "Callback pointer"
                     // example: "A:\\mydll.exe /c 1234:5678"
  int  cmdLineLen = 0;

  unsigned dllEnvironmentSegment;

  // create copy of libPath
  strncpy(cmdLine, libPath, MAX_PATH_LENGTH );

  // extract the filename (without DLL extension) from path
  pLibName = helper_extractLibName(cmdLine, &cmdLineLen);

  asm pusha; // DI and SI must not be modfied! (they could hold local vars)

  RTX_Disable_Task_Scheduling();

  // call the DLLs interrupt routine
  _ES = FP_SEG((void far *)pLibName);
  _BX = FP_OFF((void far *)pLibName);
  _CX = strlen(pLibName);
  _AX = CHIPDLL_ISR_SIGNOFF_DLL;
  asm int CHIPDLL_INT;

  // BX contains the segment of the DLLs instance memory. That memory block
  // must be released by the import library, since the DLL is not required anymore.
  // If the ES:BX is a null pointer the DLL is still required by other applications.
  asm mov dllEnvironmentSegment, bx

  RTX_Enable_Task_Scheduling();

  asm popa; // DI and SI must not be modfied! (the could hold local vars)

  if (dllEnvironmentSegment != 0)
  {
      // unload the DLL
      helper_release_rtos_mem( dllEnvironmentSegment );
  }

  return 1; // success
}
#endif  // _helper_unload_library_

/*
 @doc DOC_progParentData_
 ---------------------------------------------------------------
  progParentData()
 ---------------------------------------------------------------
 @clib_nl  progParentData | Retrieve pointer to parent program's data. |
           void far * progParentData(void) |
 @rdesc    Pointer to <cfont>report<efont> object passed to
           <linkto>..\BIOS\bios20B.htm<linkmid>BIOS_ExecuteExt()<linktail> API
           by the parent program which invoked this child program.<s2>
           If this program was not invoked with
           the <cfont>BIOS_ExecuteExt()<efont> API, the return value
           will be NULL.

 @comm The form of the object referenced by the pointer returned
     from this function is user defined, with the restriction that
     the first two integer values of this structure must correspond
     to the first two members of the
  <linkto>../../biosstruc.htm#CmdFeedbackS<linkmid>CmdFeedbackS<linktail>
     data structure.
        <s2>For compatibility with future @Chip-RTOS versions, the first
        integer (unsigned) of this user defined structure should be set 
        to the size of this user structure.  The second integer (signed)
        will be set to the program's DOS exit code value by the @Chip-RTOS.<s2>
        Note that this exit code is truncated to 8 bits by the DOS 
        <linkto>../../dosemu.htm#0x210x4C<linkmid>exit API<linktail>
        and is then sign extended into this integer value, with a resulting
        program exit code range from -128 up to 127, inclusive<s2>  The 
        <cfont>BIOS_ExecuteExt()<efont>
        caller is free to preset this value to a value outside of this
        range to  provide a positive program termination detection
        using a polling mechanism.<nl>
        <nl>
        The remainder of the structure
        following these two required integer values can be what ever the
        user desires.<nl>
     <nl>
     No call into the @Chip-RTOS occurs from within this library function.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.18
*/
#ifdef _progParentData_
// Standard library function name used  to find the _TEXT segment.
// (Program's PSP lies 256 bytes before the start of the _TEXT segment.)
extern void _terminate(void) ;
   
#define PSP_PARENT_REPORT_OFFSET  (0x3C)        // BYTE  offset

void far * progParentData(void)
{
    // The Program Status Prefix (PSP) area lies 256 bytes before the
    // start of the _TEXT section.
    DWORD far *psp = MK_FP(FP_SEG(_terminate) - (256 >> SEG_SHIFT), 0) ;
    //  For SC1x programs, or any programs which were not invoked by
    //  BIOS_ExecuteExt(), this location read from the PSP will be NULL.

    return (void far *) psp[PSP_PARENT_REPORT_OFFSET / sizeof(void far *) ] ;
}
#endif // _progParentData_

#ifdef _helper_clibVersion_
/*
 @doc DOC_helper_clibVersion_
 ---------------------------------------------------------------
  Get C-Library version number
 ---------------------------------------------------------------
 @clib  helper_clibVersion | Get C-Library version number in
      BCD format. |
        unsigned short helper_clibVersion( void ); |
 @rdesc Identifier for this version of the Beck C library.<nl>
        C-Library version 2.20, for example, will return value  0x0220.
 @comm This function provides a version number for the Beck C library version in use.<nl>
        <nl>
        Example:<nl>
 @raw
        <code>
int main (void)
{
        unsigned short version = helper_clibVersion();

        printf("\r\nThis program was compiled with CLIB version V%X.%02X\r\n", 
              version >> 8, 
              version & 0xFF);
        return 0 ;
}
        <codee>

 @target_clib V2.20
*/
#define CLIB_VERSION_HEX_MSD   (CLIB_VERSION/1000) 
#define CLIB_VERSION_HEX_D3    ((CLIB_VERSION - CLIB_VERSION_HEX_MSD * 1000)/100) 
#define CLIB_VERSION_HEX_D2    ((CLIB_VERSION - CLIB_VERSION_HEX_MSD * 1000 \
                               - CLIB_VERSION_HEX_D3 * 100)/10) 
#define CLIB_VERSION_HEX_LSD   (CLIB_VERSION % 10)

#define CLIB_VERSION_BCD   (   CLIB_VERSION_HEX_LSD          \
                             |(CLIB_VERSION_HEX_D2  << 4)    \
                             |(CLIB_VERSION_HEX_D3  << 8)    \
                             |(CLIB_VERSION_HEX_MSD << 12) )

unsigned short helper_clibVersion (void)
{
    return CLIB_VERSION_BCD ;
}
#endif // _helper_clibVersion_
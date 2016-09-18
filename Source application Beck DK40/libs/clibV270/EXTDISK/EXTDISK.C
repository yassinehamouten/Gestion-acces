/****************************************************************************
* (C) 2006-2007 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module        : EXTDISK.C
* Function      : External Disk Interface API Library
* ---------------------------------------------------------------------------

$Header: EXTDISK.C, 6, 12.11.2008 12:50:57, Andre Pribil$

****************************************************************************/



/****************************************************************************/
//includes
/****************************************************************************/

#include <dos.h>
#include <config.h>
#include <common.h>
#include <EXTDISK.H>
#include "EXT_PRIV.H"

/*
 @doc DOC_INDEX
 ---------------------------------------------------------------
 External Disk Interface API Table of Contents
 ---------------------------------------------------------------
 @clibidx  <tab><cfont>#include <InBraces EXTDISK\.H><efont> |

 Here is the CLIB API for an external disk B: and D: drive.<s2>
 This interface allows you to add an external B: or D: drive.<s2> This drive must be
 block (sector) oriented.<s2> Each sector should be 512 bytes long.<s2> The
 application must provide a software interrupt 0xB1 function for drive B:
 or 0xB2 for drive D: to read and write these sectors on this drive.<nl>
 <nl>
 On SC1x systems, the maximum disk size is about 2 Gigabytes.<s2> (This
 limitation is due to the FAT16 disk format used on SC1x systems.)<s2>
 SC1x systems support only drive B:
 <nl><nl>
 The SC1x3/SC2x systems support FAT32 format.  The maximum disk size
 on SC1x3/SC2x systems is about 8 Terabytes.<s2>
 The maximum file size is 2**32 bytes minus one cluster (=32 kbyte), which
 is about 4 Gigabyte.<s2> SC1x3/SC2x systems support drive B: and drive D:.<s2>

 @libcat1  Driver  | ext01 | Extdisk_install_drive    | Install a drive B: |
 @libcat1  Driver  | ext02 | Extdisk_remove_drive     | Deinstall the drive B: |
 @libcat1  Driver  | ext05 | Extdisk_install_drive2   | Install a drive D: |
 @libcat1  Driver  | ext06 | Extdisk_remove_drive2    | Deinstall the drive D: |

 @libcat2  Status  | ext03 | Extdisk_install_callback | Install a notification callback |
 @libcat2  Status  | ext04 | Extdisk_remove_callback  | Deinstall the notification callback |
*/


/*************************************************************************/
//Install drive B:
/*************************************************************************/
#ifdef _ext01_
/*
 @doc DOC_ext01_
 ---------------------------------------------------------------
 Install drive B:
 ---------------------------------------------------------------
 @clib  Extdisk_install_drive | Install a drive B: |
        <cfont>int Extdisk_install_drive ( unsigned long totalsectors );<efont> |
 @parm  unsigned long | totalsectors | Total sector count of disk
 @rdesc = 0: success<nl>
        != 0: failed
 @comm  Prior to this call the application must provide a disk read/write
        function installed at interrupt 0xB1.<s2> The required interface
        for this installed handler
        is specified <linkto>../../disk_API.htm<linkmid>here<linktail>.
 @Also  ext02.htm | Extdisk_remove_drive |
        ext05.htm | Extdisk_install_drive2 | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../extdisk.htm#0xB00x01<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

 @target_clib V2.04
*/
int Extdisk_install_drive (unsigned long totalsectors)
{
    _BX = (unsigned int) (totalsectors >> 16);
    _DX = (unsigned int) totalsectors;
    _AH = EXTDISK_INSTALL_DRIVE;
    asm { int EXTDISKINT  } ;
    return _AX;
}
#endif

/*************************************************************************/
//Deinstall drive B:
/*************************************************************************/
#ifdef _ext02_
/*
 @doc DOC_ext02_
 ---------------------------------------------------------------
 Deinstall drive B:
 ---------------------------------------------------------------
 @clib  Extdisk_remove_drive | Deinstall the drive B: |
        <cfont>int Extdisk_remove_drive ( void );<efont> |
 @parm  byte |  | -- none --
 @rdesc = 0: success<nl>
        != 0: failed
 @Also  ext01.htm | Extdisk_install_drive |
        ext06.htm | Extdisk_remove_drive2 | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../extdisk.htm#0xB00x02<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

 @target_clib V2.04
*/
int Extdisk_remove_drive (void)
{
    _AH = EXTDISK_REMOVE_DRIVE;
    asm { int EXTDISKINT  } ;
    return _AX;
}
#endif


/*************************************************************************/
//Install callback
/*************************************************************************/
#ifdef _ext03_
/*
 @doc DOC_ext03_
 ---------------------------------------------------------------
 Install callback
 ---------------------------------------------------------------
 @clib  Extdisk_install_callback | Install a notification callback function |
        <cfont>int Extdisk_install_callback ( EXTDISK_CALLBACK callback );<efont> |
 @parm  EXTDISK_CALLBACK | callback | Pointer to the callback function of the
        type <cfont>EXTDISK_CALLBACK<efont><nl>
        <nl>
        <cfont>EXTDISK_CALLBACK<efont> is defined as follows:<ul>
        <cfont>typedef void (far * EXTDISK_CALLBACK)(unsigned int event);<efont><ule>        
 @rdesc = 0: success<nl>
        != 0: failed
 @comm  The external drives B: and D: may be hot-plugable. This means that the
        drive medium might be removed or inserted while your application is
        running. In some cases it may be important for you to be notified if a
        medium is removed or inserted, for example if one of your tasks has set
        its working directory to the external drive. By default @CHIP-RTOS will
        reset the working directory of all tasks that previously had their
        working directory on a drive that has been removed to A:\\. However this
        might not be appropriate. So a reaction on the removal of a hot-pluggable
        medium might be to set a new valid working directory.<nl>
        To be notified of insertion and removal events, install an EXTDISK callback
        function.<nl>
        <nl>
        A maximum of 12 EXTDISK callback functions can be installed.<nl>
        <nl>
        The following events may be passed along with the callback function's
        <cfont>event<efont> parameter:<nl>
        <cfont>EXTDISK_EVENT_INSTALL_B<efont> = 0x01<ul>
          Drive B: has been installed<ule>
          <nl>
        <cfont>EXTDISK_EVENT_REMOVE_B<efont> = 0x02<ul>
          Drive B: has been uninstalled<ule>
          <nl>
        <cfont>EXTDISK_EVENT_INSTALL_D<efont> = 0x03<ul>
          Drive D: has been installed<ule>
          <nl>
        <cfont>EXTDISK_EVENT_REMOVE_D<efont> = 0x04<ul>
          Drive D: has been uninstalled<ule>
 @ex The following example demonstrates the general usage of the notification 
     callback function: |
void huge callback(unsigned int event)
{
  switch(event)
  {
    case EXTDISK_EVENT_INSTALL_B:
      ...  // Event handling
      break;
      
    case ...
  }
}

void main()
{
  if(Extdisk_install_callback(callback) != 0)
    ...  // Error handling
    
  ...
  
  if(Extdisk_remove_callback(callback) != 0)
    ...  // Error handling
}
 @Also  ext04.htm | Extdisk_remove_callback |
        | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../extdisk.htm#0xB00x03<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.07 | V1.00

 @target_clib V2.04
*/
int Extdisk_install_callback (EXTDISK_CALLBACK callback)
{
    _ES = FP_SEG(callback);
    _DI = FP_OFF(callback);
    _AH = EXTDISK_INSTALL_CALLBACK;
    asm { int EXTDISKINT  } ;
    return _AX;
}
#endif


/*************************************************************************/
//Deinstall callback
/*************************************************************************/
#ifdef _ext04_
/*
 @doc DOC_ext04_
 ---------------------------------------------------------------
 Deinstall callback
 ---------------------------------------------------------------
 @clib  Extdisk_remove_callback | Uninstall the notification callback function |
        <cfont>int Extdisk_remove_callback ( EXTDISK_CALLBACK callback );<efont> |
 @parm  EXTDISK_CALLBACK | callback | Pointer to the callback function of the
        type <cfont>EXTDISK_CALLBACK<efont> (see 
        <linkto>ext03.htm<linkmid>Extdisk_install_callback<linktail> for details)
 @rdesc = 0: success<nl>
        != 0: failed
 @Also  ext03.htm | Extdisk_install_callback |
        | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../extdisk.htm#0xB00x04<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00

 @target_clib V2.04
*/
int Extdisk_remove_callback (EXTDISK_CALLBACK callback)
{
    _ES = FP_SEG(callback);
    _DI = FP_OFF(callback);
    _AH = EXTDISK_REMOVE_CALLBACK;
    asm { int EXTDISKINT  } ;
    return _AX;
}
#endif

/*************************************************************************/
//Install drive D:
/*************************************************************************/
#ifdef _ext05_
/*
 @doc DOC_ext05_
 ---------------------------------------------------------------
 Install drive D:
 ---------------------------------------------------------------
 @clib  Extdisk_install_drive2 | Install a drive D: |
        <cfont>int Extdisk_install_drive2 ( unsigned long totalsectors );<efont> |
 @parm  unsigned long | totalsectors | Total sector count of disk
 @rdesc = 0: success<nl>
        != 0: failed
 @comm  Prior to this call the application must provide a disk read/write
        function installed at interrupt 0xB2.<s2> The required interface
        for this installed handler
     is specified <linkto>../../disk_API.htm<linkmid>here<linktail>.
 @Also  ext06.htm | Extdisk_remove_drive2 |
        ext01.htm | Extdisk_install_drive | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../extdisk.htm#0xB00x05<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.07 | V1.00

 @target_clib V2.06
*/
int Extdisk_install_drive2 (unsigned long totalsectors)
{
    _BX = (unsigned int) (totalsectors >> 16);
    _DX = (unsigned int) totalsectors;
    _AH = EXTDISK_INSTALL_DRIVE2;
    asm { int EXTDISKINT  } ;
    return _AX;
}
#endif

/*************************************************************************/
//Deinstall drive D:
/*************************************************************************/
#ifdef _ext06_
/*
 @doc DOC_ext06_
 ---------------------------------------------------------------
 Deinstall drive D:
 ---------------------------------------------------------------
 @clib  Extdisk_remove_drive2 | Deinstall the drive D: |
        <cfont>int Extdisk_remove_drive2 ( void );<efont> |
 @parm  byte |  | -- none --
 @rdesc = 0: success<nl>
        != 0: failed
 @Also  ext05.htm | Extdisk_install_drive2 |
        ext02.htm | Extdisk_remove_drive | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../extdisk.htm#0xB00x06<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.07 | V1.00

 @target_clib V2.06
*/
int Extdisk_remove_drive2 (void)
{
    _AH = EXTDISK_REMOVE_DRIVE2;
    asm { int EXTDISKINT  } ;
    return _AX;
}
#endif

// End EXTDISK.C ////////////////////////


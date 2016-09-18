/****************************************************************************
* (C) 2006 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* MOdule      :   EXT_PRIV.H
* Function    :   Internal information for External Disk Interface C Library.
* ---------------------------------------------------------------------------

$Header: EXT_PRIV.H, 2, 29.08.2006 13:00:54, Andre Pribil$

*****************************************************************************/

#ifndef __EXT_PRIV_H__
#define __EXT_PRIV_H__

#define EXTDISKINT               0xB0

/*************************************************************************/
// EXTDISK API Services
/*************************************************************************/
    // "Unsigned" 'u' appended here to assure Paradigm Beck Edition compiler
    //  that we do not care about sign bit after the 8 bit left shift.
#define EXTDISK_INSTALL_DRIVE     0x01u
#define EXTDISK_REMOVE_DRIVE      0x02u
#define EXTDISK_INSTALL_CALLBACK  0x03u
#define EXTDISK_REMOVE_CALLBACK   0x04u
#define EXTDISK_INSTALL_DRIVE2    0x05u
#define EXTDISK_REMOVE_DRIVE2     0x06u


/*************************************************************************/
#endif /* __EXT_PRIV_H__*/

/*************************************************************************/
//end ext_priv.h
/*************************************************************************/
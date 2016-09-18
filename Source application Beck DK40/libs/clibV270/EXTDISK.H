/****************************************************************************
* (C) 2006 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module        : EXTDISK.H
* Function      : Defines and typedefs for EXTDISK.C
* ---------------------------------------------------------------------------

$Header: EXTDISK.H, 3, 12.09.2006 11:40:28, Andre Pribil$

****************************************************************************/

#ifndef __EXTDISK_H__
#define __EXTDISK_H__


/*************************************************************************/
//prototypes
/*************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#define EXTDISK_EVENT_INSTALL     0x0001
#define EXTDISK_EVENT_REMOVE      0x0002
#define EXTDISK_EVENT_INSTALL_B   0x0001
#define EXTDISK_EVENT_REMOVE_B    0x0002
#define EXTDISK_EVENT_INSTALL_D   0x0003
#define EXTDISK_EVENT_REMOVE_D    0x0004

typedef void (far * EXTDISK_CALLBACK)(unsigned int event);

int _cdecl Extdisk_install_drive    (unsigned long totalsectors);
int _cdecl Extdisk_remove_drive     (void);
int _cdecl Extdisk_install_drive2   (unsigned long totalsectors);
int _cdecl Extdisk_remove_drive2    (void);

int _cdecl Extdisk_install_callback (EXTDISK_CALLBACK callback);
int _cdecl Extdisk_remove_callback  (EXTDISK_CALLBACK callback);

#ifdef __cplusplus
}
#endif

/*************************************************************************/
#endif /* __EXTDISK_H__*/

/*************************************************************************/
//end extdisk.h
/*************************************************************************/
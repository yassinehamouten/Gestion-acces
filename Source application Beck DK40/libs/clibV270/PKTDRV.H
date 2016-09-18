/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module        : PKTDRV.H
* Function      : Definitions for Packet driver interface
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\PKTDRV.H, 12, 10.02.2007 11:09:10, Jack Gatrost$

/**************************************************************************/

#ifndef _PKT_DRV_H_
#define _PKT_DRV_H_

// Note: #include <Pktdrv_EXT.H> appears down below for CLIB_CUSTOMER_SPECIFIC


/**************************************************************************/
// Defines
/**************************************************************************/
#ifdef _MSC_VER /* If Microsoft C Compiler is used, define new FP_SEG and FP_OFF Macro */
    #ifdef FP_SEG
        #undef FP_SEG
    #endif
    #define FP_SEG(ptr)    ((unsigned int)(((unsigned long)ptr)>>16))

    #ifdef FP_OFF
        #undef FP_OFF
    #endif
    #define FP_OFF(ptr)    ((unsigned int)(((unsigned long)ptr)&0xFFFF))
#endif


#define PKTVECT  0xAE

//frame size
#define SIZE_ETH_HEADER    (int)14
#define ETH_MIN            (int)64
#define ETH_MAX            (int)1500

/* Packet driver error return codes */
#define NO_ERROR             0
#define BAD_HANDLE           1 /* invalid handle number */
#define BAD_TYPE             5 /* bad packet type specified */
#define NO_SPACE             9 /* operation failed because of insufficient space */
#define TYPE_INUSE          10 /* the type had previously been accessed, and not released */
#define BAD_COMMAND         11 /* the command was out of range, or not implemented */
#define CANT_SEND           12 /* the packet couldn't be sent (usually hardware error) */


/* Packet driver function call numbers */
#ifndef SUPPRESS_DRIVER_INFO  // Conflict with C-Library extension?
#define DRIVER_INFO          1
#endif 
#define ACCESS_TYPE          2
#define RELEASE_TYPE         3
#define SEND_PKT             4
#define GET_ADDRESS          6
#define SET_RCVMODE         20
#define GET_RCVMODE         21
#define SET_MULTICAST       22     /*set/add multicast mac address*/
#define DEL_MULTICAST       39     /*remove multicast mac address*/
#define INSTALL_WILDCARD    40

/*Receive modes*/
#define    RCV_BCAST        3  // accept own address and broadcasts (default)
#define    RCV_BCAST_MCAST  5  // own address, broadcasts and multicasts
#define    RCV_ALL          6  // all incoming packets are accepted

/************************************************************************/
// type definitions
/************************************************************************/

#ifndef MY_PKT_SIZE
#define MY_PKT_SIZE  ETH_MAX
#endif

// Ethernet Frame
typedef struct tag_ethernet_packet_format
{
    unsigned char	dest[6];
    unsigned char	src[6];
    unsigned int	type;
    unsigned char	data[MY_PKT_SIZE];
} Eth_Packet;


typedef union union_eth
{
    Eth_Packet     packstruc;
    unsigned char  packet[sizeof(Eth_Packet)];
}Ethernet_Packet;


// Avoid conflict for special cases where some other definition
//   for 'Driver_Info' exits within the set of header files.
//   By default, this SUPPRESS_DRIVER_INFO is not defined.
#ifndef SUPPRESS_DRIVER_INFO    // Conflict with another definition?

// Driver info
typedef struct tag_driver_info
{
   unsigned char basic;
   unsigned char _class;
   unsigned char number;
   unsigned int  type;
   unsigned int  version;
} Driver_Info;
#endif // SUPPRESS_DRIVER_INFO

typedef void huge (far *fpFktPtr)(void);

#ifdef CLIB_CUSTOMER_SPECIFIC
// Supply some optional patches for customer specific library.
// (For standard Beck library, this extra file does not exists.)
#include <Pktdrv_EXT.H>
#endif

/************************************************************************/
//prototypes
/************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

unsigned char _cdecl PktDriver_Installed(void);
#ifndef SUPPRESS_DRIVER_INFO    // Conflict with another definition?
unsigned char _cdecl Get_Driver_Info(Driver_Info * drv_info );

#ifndef Set_Access_Type // No alternative definition in use?
unsigned int  _cdecl Set_Access_Type(const Driver_Info * drv_info, 
                                     const void far    * Receiver, 
                                     const int  far    * pkt_type, 
                                           int         * handle) ;
#endif // Set_Access_Type

#ifndef Set_WildcardAccess_Type // No alternative definition in use?
unsigned int  _cdecl Set_WildcardAccess_Type(const Driver_Info * drv_info,
                                             const void far    * Receiver,
                                             const int far     * pkt_type,
                                                   int         * handle) ;
#endif // Set_WildcardAccess_Type

#endif // SUPPRESS_DRIVER_INFO

unsigned char _cdecl Get_Eth_Address(unsigned char far *buffer, unsigned int len);
unsigned char _cdecl Send_Packet(const unsigned char far * buffer, unsigned int len);

#ifndef Release_Type // No alternative definition in use?
unsigned int  _cdecl Release_Type(unsigned int handle);
#endif  // Release_Type

unsigned int  _cdecl Set_Multicast(const unsigned char far * mac_addr, int set);

unsigned int  _cdecl Get_Receive_Mode(unsigned char * error);
unsigned int  _cdecl Set_Receive_Mode(unsigned int mode, unsigned char * error);


#ifdef __cplusplus
}
#endif
/************************************************************************/

#endif

/************************************************************************/
//end pktdrv.h
/************************************************************************/

/****************************************************************************
* (C) 1999-2007 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module        : PKTDRV.C
* Function      : Packet driver interface enables access to the Ethernet
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\Pktdrv\PKTDRV.C, 21, 04.12.2008 16:24:22, Markus Bartat$

****************************************************************************/


/************************************************************************/
// Includes
/************************************************************************/
#include <DOS.H>

#include "config.h"
#include <PKTDRV.H>

/*
 // Note:  The DOCLIST.EXE tool used by the C-Library HTML build process reacts
 //  to the token "#DOCLIST:" when it appears as the first non-white space
 //  on a line.  The tool transfers the text which follows into the 
 //  BeckCLib.LST file that is used for the context sensitive help.
 //
 #DOCLIST:Eth_Packet CLIB/PKTDRV/eth_pack.htm.htm
*/

/*
 @doc DOC_INDEX
 ---------------------------------------------------------------
 Ethernet Packet Driver API Table of Contents
 ---------------------------------------------------------------
 @clibidx  <tab><cfont>#include <InBraces PKTDRV\.H><efont><nl>
    <tab><linkto>#COMM<linkmid>Communication<linktail><tab>
    <tab><linkto>#COMM<linkmid>Configuration<linktail><tab> |
    
 Packet driver API for direct access to the IPC@CHIP&reg; Ethernet device.
 <nl><nl>
 Packet drivers provide a simple, common programming interface that allows multiple
 applications to share a network interface at the data link level.
 The packet driver demultiplex incoming packets among the applications by using
 the network media's standard packet type.
 The packet driver provides calls to initiate access to a specific packet type,
 to end access to it, to send a packet, and to get information about the interface.<nl>
 
 @libcat1a  COMM | Communication | pkt02 | Set_Access_Type | Install an Access Handler |
 @libcat1a  COMM | Communication | pkt28 | Set_WildcardAccess_Type | Install an Wildcard Access handler |
 @libcat1a  COMM | Communication | pkt03 | Release_Type | Uninstall an Access Handler |
 @libcat1a  COMM | Communication | pkt04 | Send_Packet | Send an Ethernet Packet |

 @libcat2a  CONFIG | Config | pktAvail | PktDriver_Installed | Is the Packet Driver available |
 @libcat2a  CONFIG | Config | pkt01 | Get_Driver_Info | Get Driver Info |
 @libcat2a  CONFIG | Config | pkt14 | Set_Receive_Mode | Set the receive mode of the Ethernet device |
 @libcat2a  CONFIG | Config | pkt15 | Get_Receive_Mode | Get the receive mode of the Ethernet device |
 @libcat2a  CONFIG | Config | pkt16_27 | Set_Multicast | Set or Delete an Ethernet Multicast MAC Address |
 @libcat2a  CONFIG | Config | pkt06 | Get_Eth_Address | Get the @CHIPs Ethernet MAC Address |

*/

/*
 @doc DOC_Eth_Packet_
 ---------------------------------------------------------------
   Eth_Packet data structure
 ---------------------------------------------------------------
 @cstruc  Eth_Packet data structure | Ethernet Frame | 
        typedef<s2>struct tag_ethernet_packet_format { | <nl>
        unsigned char   dest[6]  ;<nl>
        unsigned char src[6]  ;<nl>
        unsigned int type  ;<nl>
        unsigned char data[MY_PKT_SIZE]  ;<nl> 
        |
        }  Eth_Packet ; 
 @element   int  | dest  | Ethernet address of packet's destination.<s2>
 @element   int  | src  | Ethernet address where packet came from.<s2>
   For outgoing packets, this field can be set with the 
   <linkto>pkt06.htm<linkmid>Get_Eth_Address<linktail> API.
 @element   int  | type  | Ethernet packet type in big endian 
    byte order.
 @element   int  | data  | Array of data bytes.
 @comm
     This data structure describes the form of the Ethernet
     data frames provided by the 
     <linkto>lib_index.htm<linkmid>Packet Driver<linktail>.<nl>
     <nl>
     The user is free to trim the size of the <code>data<codee>
     array to suite your specific application by defining the
     <code>MY_PKT_SIZE<codee> constant
     prior to inclusion of the <lt>pktdrv.h<gt> header file.<s2>
     The maximum size is 1500 bytes, which is the default.<s2>
     (The packet driver library functions are unaware of this
     array size.)<nl>
     <nl>
     However, if you do optimize the size of this object
     for your application and return a pointer to an
     instance of this data structure in ES:DI in the
     packet driver callback, you must assure that the received
     data size specified in register CX is less than or equal
     to the resulting <code>sizeof(Eth_Packet)<codee>.
 @Also pkt04.htm |  Send_Packet | 
       pkt02.htm |  Set_Access_Type |
       pkt28.htm |  Set_WildcardAccess_Type
*/


#ifdef _pkt01_
/*
 @doc DOC_pkt01_
 ---------------------------------------------------------------
 Get Packet Driver info
 ---------------------------------------------------------------
 @clib  Get_Driver_Info | Get information about the packet driver |
        unsigned char Get_Driver_Info( Driver_Info *drv_info ) ; |
 @parm  int  | drv_info | Pointer to Driver_Info struct, where driver information should be stored
 @rdesc 0<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../pktdrv.htm#0xAE0x01<linkmid>documentation<linktail>
        for more details.
 @Also  pkt02.htm | Set_Access_Type  |
         |  |
         | 
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | n/a   | V0.90 | V1.00
*/
unsigned char Get_Driver_Info(Driver_Info * drv_info )
{
     unsigned int  rbx;
     unsigned char ral;

     asm push ds
     asm push si
     _AH = 0x01;
     asm int PKTVECT
     asm pop si
     asm pop ds

     if(_FLAGS&0x01) return _DH;
     rbx = _BX;                  // save BX
     ral = _AL;                  // save AL
     drv_info->version = rbx;
     drv_info->basic   = ral;
     drv_info->_class  = _CH;
     drv_info->number  = _CL;
     drv_info->type    = _DX;
     return 0;
}
#endif

#ifdef _pkt02_
/*
 @doc DOC_pkt02_
 ---------------------------------------------------------------
 Install an Access Handler
 ---------------------------------------------------------------
 @clib  Set_Access_Type | Installs an access Handler for Ethernet Packets. |
        unsigned int Set_Access_Type ( const Driver_Info *drv_info,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; const void far * Receiver,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; const int *pkt_type,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; int *handle ); |
 @parm  int  | drv_info | Pointer to struct returned from
        <linkto>pkt01.htm<linkmid>Get_Driver_Info<linktail>.<s2>
        (This parameter is not used and may be left NULL.)
 @parm  int  | Receiver | Pointer to receiver handler function
 @parm  int  | pkt_type | Pointer to packet type (in network byte order,
      e.g. 0x0008 for IP).<s2>
      The value referenced here must be persistent due to that the @Chip-RTOS
      will reference this value during operation.<s2> (No copy is made by this
      API.)
 @parm  int  | handle   | Output Parameter:<s2> Pointer where handle should
    be stored.<s2> This handle will be needed for the
    <linkto>pkt03.htm<linkmid>Release_Type<linktail> API.
 @rdesc 0 on Success<nl>
        else error code:<nl>
          <ul><code>
           5<tab>BAD_TYPE <tab> - Type not allowed<nl>
           9<tab>NO_SPACE   <tab> - Limit of 5 accesses reached<nl>
           10<s3>TYPE_INUSE  <s2> - The type is already accessed<nl>
          <codee><ule>
 @comm  Ethernet frame format: <ul>
        <nl>
        48 Bits (6 Bytes) Destination address<nl>
        48 Bits (6 Bytes) Source address<nl>
        16 Bits (2 Bytes) Type field e.g 0x0608 for ARP, 0x0008 for IP or user defined types<nl>
        46 to 1500 Bytes of user data.<ule>

        The maximum number of installed handlers is limited to five.<s2>
        <nl><nl>
        When an Ethernet packet of the type specified here at [DS:SI] is received by the
        the IPC@CHIP's network device driver, this driver will perform callbacks to the
        receiver handler function specified here in ES:DI.<s2> This callback will be
        done twice:<ul><nl>
        <li>First call:<ul>
        <hang1>
        Input parameters to your handler: AX = 0, CX = received packet length.<pare>
        <hang1>
        Return value from your handler:<s2> ES:DI - Pointer to buffer where
        driver can load the CX received bytes.
        Return with register ES set to zero if you do not want a second call
        performed following a copy operation to the ES:DI buffer.<pare><ule>
        <nl>
        <li>Second call:<ul>
        <hang1>
        Input parameters to your handler: AX = 1, the received Ethernet data is
            now available in your buffer.<s2> The format of this received
            data fits the
            <linkto>eth_pack.htm<linkmid>Eth_Packet<linktail> type defined
            in the pktdrv.h header file.<pare>
        <hang1>
        Return value from your handler:<s2> -- none --<pare><ule>
        <ule><nl>
        On the first call, your handler produces a buffer into which the driver can transfer
        the received packet.<s2> This byte transfer occurs  between the two calls to your
        handler function, if the provided ES:DI buffer is != 0.<nl>
        <nl>
        <hang1>
        <bold>Important:<bolde> Due to that the @Chip-RTOS 80x86 type processor is a
        little endian machine, exchange the bytes for the packet type e.g. use 0x0008
        for the IP type instead of 0x0800.<s2> This way round, the "network byte order"
        requirement on this packet type is satisfied.<pare>
 @Also  pkt01.htm | Get_Driver_Info  |
        pkt28.htm | Set_WildcardAccess_Type |
        pkt03.htm | Release_Type
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../pktdrv.htm#0xAE0x02<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | n/a   | V0.90 | V1.00
*/

/*************************************************************************/
//                 set access type
/*************************************************************************/
unsigned int Set_Access_Type(const Driver_Info * drv_info,
                             const void far    * Receiver,
                             const int far     * pkt_type,
                                   int         * handle)
{
   asm push ds
   _AH = 0x02;
   _CX = sizeof(int);       /* size of type, must be 2 */
   asm les di, Receiver     /* _ES = FP_SEG(Receiver); _DI = FP_OFF(Receiver); */
   asm lds si, pkt_type     /* _DS = FP_SEG(pkt_type); _SI = FP_OFF(pkt_type); */
   asm int PKTVECT
   asm pop ds

   if(_FLAGS&0x01)
   {
      return (unsigned)_DH;
   }
   else
   {
      *handle = _AX;
      return 0;
   }
}
#endif


#ifdef _pkt03_
/*
 @doc DOC_pkt03_
 ---------------------------------------------------------------
 Release an Access Handler
 ---------------------------------------------------------------
 @clib  Release_Type | Uninstalls an access Handler |
        <cfont>unsigned int Release_Type( unsigned int handle );<efont> |
 @parm  int  | handle | Handle of access handler which should be uninstalled (returned
        from Set_Access_Type).
 @rdesc 0 on Success<nl>
        else error code:<nl>
          <ul><code>
           1<tab>BAD_HANDLE  <s2> - <code>handle<codee> not recognized<nl>
          <codee><ule>
 @Also  pkt02.htm | Set_Access_Type  | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../pktdrv.htm#0xAE0x03<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | n/a   | V0.90 | V1.00
*/

unsigned int Release_Type(unsigned int handle)
{
  _BX = handle;
  _AH = 0x03;
  asm int PKTVECT
  if(_FLAGS&0x01)
  {
      return (unsigned)_DH;
  }
  return 0;
}
#endif


#ifdef _pkt04_
/*
 @doc DOC_pkt04_
 ---------------------------------------------------------------
 Send Packet
 ---------------------------------------------------------------
 @clib  Send_Packet | Sends an Ethernet Packet |
        unsigned char Send_Packet ( const unsigned char *buffer,<nl>
        <tab><tab><tab><tab><tab><tab><tab>unsigned int len ); |
 @parm  int | buffer | Pointer to packet buffer
 @parm  int | len    | Length of packet buffer
 @rdesc 0 on Success<nl>
        else error code:<nl>
          <ul><code>
           12<tab>CANT_SEND  <s2> - Send failed<nl>
          <codee><ule>
 @comm
     The format of the outgoing packet is described by the
     <linkto>eth_pack.htm<linkmid>Eth_Packet<linktail> type defined
     in the pktdrv.h header file.<s2> The user must set the source 
     and destination IP addresses and packet type in this 
     structure.<nl>
 @Also  pkt06.htm | Get_Eth_Address  | 
        pkt02.htm | Set_Access_Type  |
         | 
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../pktdrv.htm#0xAE0x04<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | n/a   | V0.90 | V1.00
*/
unsigned char Send_Packet(const unsigned char far * buffer, unsigned int len)
{
    asm push ds
    _DS = FP_SEG(buffer);
    _SI = FP_OFF(buffer);
    _CX = len;
    _AH = 0x04;
    asm int PKTVECT
    asm pop ds

    if(_FLAGS&0x01)
    {
      return (unsigned)_DH;
    }
    return 0;
}
#endif


#ifdef _pkt06_
/*
 @doc DOC_pkt06_
 ---------------------------------------------------------------
 Get Ethernet Mac Address
 ---------------------------------------------------------------
 @clib  Get_Eth_Address | Get the @CHIP Ethernet MAC Address |
        <cfont>unsigned char Get_Eth_Address( unsigned char *buffer,<nl>
        <tab><tab><tab><tab><tab><tab><s3><tab>unsigned int len );<efont> |
 @parm  int  | buffer | Pointer to 6 byte buffer where the MAC Address should be stored
 @parm  int  | len | Length of the buffer (must be 6)
 @rdesc 0<nl>
 @Also  pkt04.htm | Send_Packet   |
         |  |
         | 
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../pktdrv.htm#0xAE0x06<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | n/a   | V0.90 | V1.00
*/
unsigned char Get_Eth_Address(unsigned char far *buffer, unsigned int len)
{
   len = len; /* avoid compiler warning */

   _ES = FP_SEG(buffer);
   _DI = FP_OFF(buffer);
   _CX = 6;
   _AH = 0x06;
   asm int PKTVECT
   return 0;
}
#endif

#ifdef _pkt14_
/*
 @doc DOC_pkt14_
 ---------------------------------------------------------------
 Set Receive Mode
 ---------------------------------------------------------------
 @clib  Set_Receive_Mode | Set receive mode of the Ethernet device |
        <cfont>unsigned char Set_Receive_Mode( unsigned int mode,<nl>
        <tab><tab><tab><tab><tab><tab><tab><tab>unsigned char *error );<efont> |
 @parm  int  | mode | receive mode
 @parm  int  | error | Output Parameter:<s2> Pointer where error code should
    be stored.<s2>Set to zero on success, else 11 (= BAD_COMMAND) on failure.
 @rdesc 0   on Success<nl>
        -1  invalid mode
 @comm  Settable modes:<ul>
        <code>
           RCV_BCAST //accept packets with own mac address or broadcast<nl>
           RCV_ALL<tab>//accept all incoming packets<nl>
        <codee><ule>
 @Also  pkt15.htm    | Get_Receive_Mode  | 
        pkt16_27.htm | Set_Multicast  |
         | 
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../pktdrv.htm#0xAE0x14<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | n/a   | V0.90 | V1.00
*/
unsigned int Set_Receive_Mode(unsigned int mode,unsigned char * error)
{
  *error=0;
  _CX = mode;
  _AH = 0x14;
  asm int PKTVECT

  if(_FLAGS&0x01)
  {
      *error=_DH;
      return 0;
  }
  return _AX;
}
#endif


#ifdef _pkt15_
/*
 @doc DOC_pkt15_
 ---------------------------------------------------------------
 Get Receive Mode
 ---------------------------------------------------------------
 @clib  Get_Receive_Mode | Get the current receive mode of the Ethernet device |
        <cfont>unsigned char Get_Receive_Mode( unsigned char *error );<efont> |
 @parm  int  | error | Output Parameter:<s2> Pointer where error code should
    be stored.<s2>Set to zero on success.<s2> (No failure is expected here if
    \@Chip-RTOS supports the packet driver API.)
 @rdesc 0   on Success<nl>
        -1  API failed
 @comm  Possible Receive modes:<ul>
        <code>
          RCV_BCAST<tab><tab>//accept own address and broadcasts<nl>
          RCV_BCAST_MCAST //accept broadcasts and installed multicasts<nl>
          RCV_ALL<tab><tab>//all incoming packets are accepted<nl>
        <codee><ule>
 @Also  pkt14.htm    | Set_Receive_Mode  | 
        pkt16_27.htm | Set_Multicast  |
         | 
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../pktdrv.htm#0xAE0x15<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | n/a   | V0.90 | V1.00
*/
unsigned int Get_Receive_Mode(unsigned char * error)
{
  *error=0;
  _AH = 0x15;
  asm int PKTVECT

  if(_FLAGS&0x01)
  {
    *error=_DH;
    return 0;
  }
  return _AX;
}
#endif


#ifdef _pkt16_27_
/*
 @doc DOC_pkt16_27_
 ---------------------------------------------------------------
 Set Multicast
 ---------------------------------------------------------------
 @clib  Set_Multicast | Set Ethernet multicast Address |
        unsigned int Set_Multicast(const unsigned char *mac_addr,<nl>
        <tab><tab><tab><tab><tab><tab><s2> int set ) ; |
 @parm  int  | mac_addr | Pointer to multicast mac address buffer (6 bytes)
 @parm  int  | set | 1 to set, 0 to delete
 @rdesc 0 on Success<nl>
        else packet driver API is not supported by this @Chip-RTOS version.
 @Also  pkt15.htm | Get_Receive_Mode  |
        pkt14.htm | Set_Receive_Mode  | 
         | 
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../pktdrv.htm#0xAE0x16<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | n/a   | V0.90 | V1.00
*/
unsigned int Set_Multicast(const unsigned char far * mac_addr, int set)
{

  _ES = FP_SEG(mac_addr);
  _DI = FP_OFF(mac_addr);
  _CX = 6;

  if(set)
  {
    _AH = 0x16;
  }
  else
  {
    _AH = 0x27;
  }
  asm int PKTVECT

  if(_FLAGS&0x01)
  {
      return  (unsigned int)_DH;
  }
  else
  {
      return 0;
  }
}
#endif


#ifdef _pkt28_
/*
 @doc DOC_pkt28_
 ---------------------------------------------------------------
 Install an Wildcard Access Handler
 ---------------------------------------------------------------
 @clib  Set_WildcardAccess_Type | Installs an wildcard packet access Handler for Ethernet Packets. |
        unsigned int Set_WildcardAccess_Type (  |
                const Driver_Info *drv_info,<nl>
                const void far * Receiver,<nl>
                const int *pkt_type,<nl>
                int *handle ) ;
 @parm  int  | drv_info | Pointer to struct returned from 
        <linkto>pkt01.htm<linkmid>Get_Driver_Info<linktail>.<s2>
        (This parameter is not used and may be left NULL.)
 @parm  int  | Receiver | Pointer to receiver handler function
 @parm  int  | pkt_type | Pointer to packet type (e.g. 0xFFFF for accepting 
   every Ethernet packet).<s2> This referenced value must be persistent.
 @parm  int  | handle   | Output Parameter:<s2> Pointer where handle should
    be stored.<s2> This handle will be needed for the 
    <linkto>pkt03.htm<linkmid>Release_Type<linktail> API.
 @rdesc 0 on Success<nl>
        else packet driver API is not supported by this @Chip-RTOS version.
 @comm  Only one wildcard could be installed.<s2> Installing a new type overwrites the previous.<nl>
        <nl>
        If a packet type of 0xFFFF is installed, any incoming packet will be accepted.<nl>
        <nl>
        A wild card handler is removed by installing a wildcard with the packet type 0x0000.<nl>
        <nl>
        The "normal" handlers installed with <linkto>pkt02.htm<linkmid>Set_Access_Type<linktail>
        API are not overwritten by installing a wildcard.<s2> Refer to the
        <linkto>pkt02.htm<linkmid>Set_Access_Type<linktail> API description for explanation
        on how the installed callback function is used.<nl>
 @Also  pkt02.htm | Set_Access_Type  |
        pkt01.htm | Get_Driver_Info  | 
        pkt03.htm | Release_Type
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../pktdrv.htm#0xAE0x28<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | n/a   | V0.90 | V1.00
*/
unsigned int Set_WildcardAccess_Type(const Driver_Info * drv_info, 
                                     const void far    * Receiver,
                                     const int far     * pkt_type,
                                           int         * handle)
{
   asm push ds
   _CX = sizeof(int);       /* size of type, must be 2 */
   _AH = 0x28;
   asm les di, Receiver     /* _ES = FP_SEG(Receiver); _DI = FP_OFF(Receiver); */
   asm lds si, pkt_type     /* _DS = FP_SEG(pkt_type); _SI = FP_OFF(pkt_type); */
   asm int PKTVECT
   asm pop ds

   if(_FLAGS&0x01)
   {
      return (unsigned)_DH;
   }
   else
   {
      *handle = _AX;
      return 0;
   }
}
#endif


#ifdef _pktAvail_
/*
 @doc DOC_pktAvail_
 ---------------------------------------------------------------
 PktDriver_Installed
 ---------------------------------------------------------------
 @clib  PktDriver_Installed | Checks if the packet driver is available  |
        unsigned char PktDriver_Installed ( void ); |
 @parm  void | | -- none --
 @rdesc 1: installed<nl>
        0: not installed<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x16<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned char PktDriver_Installed(void)
{
   _AH = 0x16;
   asm int 0xA0 // BIOS_VECT

   //check bit3 of dx
   if (_DX & 0x08)
   {
      return 1;
   }
   return 0;

}
#endif


/************************************************************************/
//end pktdrv.c
/************************************************************************/

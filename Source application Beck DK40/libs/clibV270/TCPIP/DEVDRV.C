/****************************************************************************
* (C) 1999-2010 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : DEVDRV.C
* Function       : TCPIP Device Driver API functions
* ---------------------------------------------------------------------------

$Header: $

*****************************************************************************/

#include <STDLIB.H>
#include <DOS.H>
#include "common.h"
#include "config.h"
#include <TCPIPAPI.H>
#include <TCPIP.H>
#include "TCPPRIV.H"


/*

 @doc DOC_INDEX
 ---------------------------------------------------------------
 TCP/IP Device Driver API Table of Contents
 ---------------------------------------------------------------
 @clibLinkIdx  <tab><cfont>#include <InBraces TCPIP\.H><efont><nl>
  <tab><tab><tab><tab><tab><arial>which includes<ariale> <cfont>
 <InBraces TCPIPAPI\.H><efont> |
    <linkto>#Configure<linkmid>Configure<linktail><tab>
    <tab><linkto>#Operation<linkmid>Operation<linktail><tab>
    <tab><linkto>#DHCP<linkmid>DHCP<linktail><tab>
    <tab><linkto>#PPP<linkmid>PPP<linktail><tab><nl>
    <nl>
  |
  <bold>Related<bolde>:
  <ul>
      <li> Device Driver <linkto>../../ip_dev.htm<linkmid>Overview<linktail><nl>
      <li> Device Driver <linkto>../../ddvstruc.htm<linkmid>Data Structures<linktail><nl>
      <li> TCP/IP C-Library <linkto>lib_index.htm<linkmid>Main List<linktail>  <nl>
  <ule>


 @libcat1  Configure | ddvA1 | Dev_Close_Interface |  Close user device driver/interface |
 @libcat1  Configure | ddvAE | Dev_Config_Iface      | IPv4 device configuration |
 @libcat1  Configure | ddvAF | Dev_Config_Iface_IPv6 | IPv6 configuration of an interface |
 @libcat1  Configure | ddvAD | Dev_Get_Handle_By_Name | Get device driver handle by device name |
 @libcat1  Configure | ddv9F | Dev_Get_IP         | Get IP address of a user defined device |
 @libcat1  Configure | ddvA0 | Dev_Open_Interface | Install user device driver | 
 @libcat1  Configure | dev42 | Dev_Set_IfaceMTU |  Set interface MTU |
 @libcat1  Configure | ddvB0 | Dev_UnConfig_Iface | Remove IPv4 or IPv6 device configuration from particular home index |
 @libcat1  Operation | ddvB4 | Dev_SetSpecificFlags_IPv4 | Set/Erase specific device driver flags |

 @libcat2  Operation | ddvA5 | Dev_Get_Buffer | Get a buffer from TCP/IP stack        |
 @libcat2  Operation | ddvB3 | Dev_Notify_Ioctl | Execute specific functions TCP/IP device interface |
 @libcat2  Operation | ddvA4 | Dev_Notify_ISR | Signal from Interrupt Service Routine |
 @libcat2  Operation | ddvA2 | Dev_Recv_Interface |  Receive and process incoming data |
 @libcat2  Operation | ddvA3 | Dev_Recv_Wait | Waits for data received signal |
 @libcat2  Operation | ddvA6 | Dev_Send_Complete | Signal message send complete     |

 @libcat3  DHCP | ddvB2 | Dev_Get_DHCP_Data | Get the DHCP data of a TCP/IP device interface |
 @libcat3  DHCP | ddvA7 | Dev_Wait_DHCP_Complete | Waits for DHCP completion   |

 @libcat4  PPP | ddvAC | Dev_PPP_Get_Peer_DNSIP | Get IP address of the DNS server from a PPP peer |
 @libcat4  PPP | ddvAB | Dev_PPP_Get_Peer_IP | Get IP address of a PPP peer |
 @libcat4  PPP | ddvB1 | Dev_PPP_Get_Peer_IPv6 | Get IPv6 address of a PPP peer |
 @libcat4  PPP | ddvA8 | Dev_PPP_Register_Chap | Register a PPP CHAP authentication callback function |
 @libcat4  PPP | ddvA9 | Dev_PPP_Register_Pap  | Register a PPP PAP  authentication callback function |
 @libcat4  PPP | ddvAA | Dev_PPP_Set_Option | Set PPP options  |


*/

#ifdef _dev42_
/*
 @doc DOC_dev42_
 ---------------------------------------------------------------
 Set TCP/IP device interface MTU
 ---------------------------------------------------------------
 @clibSub  Dev_Set_IfaceMTU |  devdrv_index.htm |
    Set device interface MTU. |

        <cfont>int far Dev_Set_IfaceMTU( DevUserIfaceHandle IfaceHandle,<nl>
        <tab><tab><tab><tab><tab><tab><s1> int ifMTU);<efont> |

 @parm  void *  | DevHandlePtr  |
 <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm  int  | ifMTU    | The Maximum Transmission Unit (MTU) for a device. [bytes]
 @rdesc 0:  success <nl>
        Non-zero:   <linkto>../../iperrlst.htm<linkmid>Error code<linktail>
 @comm
    The minimum MTU for IPv4 networks is 68 bytes.<s2> For IPv6 the minimum is
    1280 bytes.<nl>
    <nl>
    The device handle may be obtained using the 
    <linkto>ddvAD.htm<linkmid>Dev_Get_Handle_By_Name()<linktail> API.
 @Also  ddvA0.htm | Dev_Open_Interface  |
        ddvAD.htm | Dev_Get_Handle_By_Name   |
         |
 @related TCP/IP Device Driver  | ../../ip_dev.htm | overview |
 @rtos  On the first call, this library function invokes a software
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>interrupt<linktail>
        which modifies the code at the calling site inside your application
        program.<s2> A direct FAR JMP into the <chiprtos>
        implementation for this function is installed so that on
        return and on any subsequent calls to this API this
        dynamic link  reaches the function's
        implementation directly.<nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.36 | V1.36
 @target_clib V2.20
*/
#endif



#ifdef _ddv9F_
/*
 #DOCLIST:Dev_Get_IP_Dyn clib\tcpip\ddv9F.htm

 @doc DOC_ddv9F_
 ---------------------------------------------------------------
 Get TCP/IP device driver interface IP address and netmask
 ---------------------------------------------------------------
 @clibSub  Dev_Get_IP |  devdrv_index.htm | Get device IP address and netmask. |

        <cfont>int  Dev_Get_IP( DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab>unsigned long * ipaddr,<nl>
        <tab><tab><tab><tab>unsigned long * netmask,<nl>
        <tab><tab><tab><tab>int * errorcode);<efont> |

 @parm  void *  | DevHandlePtr  |
 <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm  int  | ipaddr    | Output parameter:<s2>Pointer to 32 bit location
        which will receive the IP address in big endian (network) byte order.
 @parm  int  | netmask    | Output parameter:<s2>Pointer to 32 bit location
        which will receive the net mask in big endian (network) byte order.
        <s2> (This parameter can be set to NULL  if netmask is not desired
        or does not apply.)
 @parm  int  | errorcode    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>errorcode<codee>.
 @Also  ddvA0.htm | Dev_Open_Interface  |
        ddvAB.htm | Dev_PPP_Get_Peer_IP |
        ddvAC.htm | Dev_PPP_Get_Peer_DNSIP
 @Also  ddvB1.htm | Dev_PPP_Get_Peer_IPv6 | | | |
 @related TCP/IP Device Driver  | ../../ip_dev.htm | overview |
  @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x9F<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_Get_IP_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
        <cfont>#define TCPIP_DYN_LINK_DEV<nl>
        #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/
int  Dev_Get_IP( DevUserIfaceHandle DevHandlePtr,
                 unsigned long * ipaddr,
                 unsigned long * netmask,
                 int  * errorcode)
{
   _ES = FP_SEG(DevHandlePtr);
   _DI = FP_OFF(DevHandlePtr);
   _DX = FP_SEG(ipaddr);
   _SI = FP_OFF(ipaddr) ;
   _CX = FP_OFF(netmask) ;
   _BX = FP_SEG(netmask) ;

   _AH = DEV_GET_IP;
   asm { int TCPIPVECT  } ;
   *errorcode=_AX;
   return _DX;
}
#endif



#ifdef _ddvA0_
/*
 #DOCLIST:Dev_Open_Interface_Dyn clib\tcpip\ddvA0.htm

 @doc DOC_ddvA0_
 ---------------------------------------------------------------
 Install/Add TCP/IP device driver interface
 ---------------------------------------------------------------
 @clibSub  Dev_Open_Interface |  devdrv_index.htm | Install user device driver. |

        <cfont>int Dev_Open_Interface(DevUserDriver far * DriverInfo,<nl>
        <tab><tab><tab><tab><tab> int * errorcode);<efont> |

 @parm  int  | DriverInfo  | Pointer to
         <linkto>../../ddvstruc.htm#DevUserDriver<linkmid>user driver information<linktail>.
 @parm  int  | errorcode    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>errorcode<codee>.
 @comm
     The caller must fill in the referenced <code>DevUserDriver<codee> object
     prior to calling.<s2> On the initial call of this API for a particular
     device, the <code>IfaceHandle<codee> member must be NULL.<s2> On success,
     this API will put the new device's handle into this member for use with
     the various driver related API.<nl>
     <nl>
     An installed device can be reconfigured by first calling the 
     <linkto>ddvA1.htm<linkmid>Dev_Close_Interface()<linktail>
     and then calling this <code>Dev_Open_Interface()<codee> again,
     this time with the <code>IfaceHandle<codee> member of the
     <linkto>../../ddvstruc.htm#DevUserDriver<linkmid>DevUserDriver<linktail>
     still set to the value output from the first call.<nl>
     <nl>
     An Ethernet interface can be configured using DHCP by setting the 
     <cfont>use_dhcp<efont> member to 1.<s2> In this case, the
     <linkto>ddvA7.htm<linkmid>Dev_Wait_DHCP_Complete()<linktail>
     should be called following a successful call to this API in order to
     retrieve the IPv4 address and network mask.

     This API performs two steps during its execution.<s2> The first step 
     is to add the new device to the TCP/IP stack (this step is irreversible).<s2>
     This step is performed only when the <code>IfaceHandle<codee> member was set
     to NULL by the caller.<s2> This step will fail with error code 
     237 if a device with the same name has already been
     installed and that device is not currently closed.<s2> The
     <linkto>ddvA1.htm<linkmid>Dev_Close_Interface()<linktail> API is used
     to close a device.

     The second step is to configure the device.<s2> This second step is
     performed only if the device has been added successfully (either on 
     this immediate call, or a previous one) and the <code>DEV_ADD_ONLY<codee>
     flag is not set in the 
     <linkto>../../ddvstruc.htm#iface_type<linkmid>iface_type<linktail> member of 
     the referenced
     <linkto>../../ddvstruc.htm#DevUserDriver<linkmid>DevUserDriver<linktail>
     object.

     Go <linkto>../../ip_dev.htm<linkmid>here<linktail> for further
     explanations and an example with source code.

    Once a device has been installed, there is no mechanism short of a system reset
    to remove that device from the TCP/IP stack.<s2> However, you can deactivate the 
    device with the 
     <linkto>ddvA1.htm<linkmid>Dev_Close_Interface()<linktail> API.
    This step is important prior to a driver program exit in order that another
    instance of the driver program can later use this API to open this same 
    device again.<s2> On this second installation, the new program instance's 
    callback vectors will be installed.


 @Also  ddvA1.htm | Dev_Close_Interface |
        ddvA2.htm | Dev_Recv_Interface |
        ddvA3.htm | Dev_Recv_Wait
 @Also  ddvA4.htm | Dev_Notify_ISR |
        ddvA5.htm | Dev_Get_Buffer |
        ddvA6.htm | Dev_Send_Complete
 @Also  ddvA7.htm | Dev_Wait_DHCP_Complete |
        ddvA8.htm | Dev_PPP_Register_Chap |
        ddvA9.htm | Dev_PPP_Register_Pap
 @Also  ddvAA.htm | Dev_PPP_Set_Option |
        ddvAB.htm | Dev_PPP_Get_Peer_IP |
        ddvAC.htm | Dev_PPP_Get_Peer_DNSIP
 @Also  ddvB1.htm | Dev_PPP_Get_Peer_IPv6 | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xA0<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_Open_Interface_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
        <cfont>#define TCPIP_DYN_LINK_DEV<nl>
        #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @related     | ../../ip_dev.htm#Install_Dev
        | Example | - Installing device driver
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00


*/
int  Dev_Open_Interface(DevUserDriver far * DriverInfo,int * errorcode)
{
   _ES = FP_SEG(DriverInfo);
   _DI = FP_OFF(DriverInfo);
   _AH = DEV_OPEN_IFACE;
   asm { int TCPIPVECT  } ;
   *errorcode = _AX;
   return (int)_DX;
}
#endif


#ifdef _ddvA1_
/*
 #DOCLIST:Dev_Close_Interface_Dyn clib\tcpip\ddvA1.htm

 @doc DOC_ddvA1_
 ---------------------------------------------------------------
 Close TCP/IP device driver interface
 ---------------------------------------------------------------
 @clibSub  Dev_Close_Interface | devdrv_index.htm | Close user device driver/interface. |

        <cfont>int  Dev_Close_Interface(DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab>int * errorcode);<efont> |

 @parm  void *  | DevHandlePtr  |
 <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm  int  | errorcode    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>errorcode<codee>.
 @comm 
    Note that closing a device driver does not remove that device 
    from the system.<s2> Once a device has been installed, there is
    no mechanism short of a system reset to remove that device from
    the TCP/IP stack.

    Before a device driver program terminates, it is important to call this
    API on the installed TCP/IP device.<s2> This will allow a subsequent 
    instance of that driver program to successfully use the 
     <linkto>ddvA0.htm<linkmid>Dev_Open_Interface()<linktail> to reestablish
     the device's operation with connections made to the new program
     instance.


 @Also  ddvA0.htm | Dev_Open_Interface  |
         |  |  |
  @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xA1<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_Close_Interface_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
        <cfont>#define TCPIP_DYN_LINK_DEV<nl>
        #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @related     | ../../ip_dev.htm#Close_Dev
        | Example | - Closing device driver
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
int  Dev_Close_Interface(DevUserIfaceHandle DevHandlePtr, int * errorcode)
{
   _ES = FP_SEG(DevHandlePtr);
   _DI = FP_OFF(DevHandlePtr);
   _AH = DEV_CLOSE_IFACE;
   asm { int TCPIPVECT  } ;
   *errorcode=_AX;
   return _DX;
}
#endif

#ifdef _ddvA2_
/*
 #DOCLIST:Dev_Recv_Interface_Dyn clib\tcpip\ddvA2.htm

 @doc DOC_ddvA2_
 ---------------------------------------------------------------
 Receive and process incoming data at the TCP/IP stack
 ---------------------------------------------------------------
 @clibSub  Dev_Recv_Interface | devdrv_index.htm |
    Receive and process incoming data at the TCP/IP stack. |
        <cfont>int Dev_Recv_Interface( DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab><tab><s3> int * errorcode);<efont> |

 @parm  void *  | DevHandlePtr  |
 <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm  int  | errorcode    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>errorcode<codee>.
 @comm
        Go <linkto>../../ip_dev.htm#ISR_and_RECVTask<linkmid>here<linktail>
        for example usage of this API.<nl>
        <nl>
        This API invokes your device driver's receiver 
        <linkto>../../ddvstruc.htm#DevRecv<linkmid>callback<linktail>
        function to collect the incoming data from your device.<s2>
        Your receiver callback function will then pass the received data up 
        the TCP/IP stack.<nl>

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xA2<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_Recv_Interface_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
        <cfont>#define TCPIP_DYN_LINK_DEV<nl>
        #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @Also  ddvA0.htm | Dev_Open_Interface  |
        ddvA3.htm | Dev_Recv_Wait |
        ddvA4.htm | Dev_Notify_ISR
 @Also  ddvA6.htm | Dev_Send_Complete  |
        ddvA7.htm | Dev_Wait_DHCP_Complete |
          |
 @related     | ../../ip_dev.htm#DeviceReceive
        | Example | - function which would be called by this API
 @related     | ../../ip_dev.htm#ISR_and_RECVTask
        | Example | - Receiver Task which calls this API
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
int  Dev_Recv_Interface(DevUserIfaceHandle DevHandlePtr, int * errorcode)
{
   _ES = FP_SEG(DevHandlePtr);
   _DI = FP_OFF(DevHandlePtr);
   _AH = DEV_RECV_IFACE;
   asm { int TCPIPVECT  };
   *errorcode=_AX;
   return _DX;
}
#endif

#ifdef _ddvA3_
/*
 #DOCLIST:Dev_Recv_Wait_Dyn clib\tcpip\ddvA3.htm

 @doc DOC_ddvA3_
 ---------------------------------------------------------------
 Wait for received data.
 ---------------------------------------------------------------
 @clibSub  Dev_Recv_Wait | devdrv_index.htm |
    Waits for data received signal from 
 <linkto>../HW/hal84A.htm<linkmid>Interrupt Service Routine<linktail>. |

        <cfont>int Dev_Recv_Wait( DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab><s3>int * errorcode);<efont> |

 @parm  void *  | DevHandlePtr  |
 <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm  int  | errorcode    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>errorcode<codee>.
 @comm
     This function will block until your device's Interrupt Service Routine
     signals that incoming packets are available by calling the
     <linkto>ddvA4.htm<linkmid>Dev_Notify_ISR()<linktail> API.

 @Also   ddvA0.htm | Dev_Open_Interface  |
         ddvA2.htm | Dev_Recv_Interface |
         ddvA4.htm | Dev_Notify_ISR
 @Also   ddvA6.htm | Dev_Send_Complete  |
         ddvA7.htm | Dev_Wait_DHCP_Complete |
          |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xA3<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_Recv_Wait_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
        <cfont>#define TCPIP_DYN_LINK_DEV<nl>
        #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @related     | ../../ip_dev.htm#ISR_and_RECVTask
        | Example | - Receiver Task
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Dev_Recv_Wait(DevUserIfaceHandle DevHandlePtr, int * errorcode)
{
   _ES = FP_SEG(DevHandlePtr);
   _DI = FP_OFF(DevHandlePtr);
   _AH = DEV_RECV_WAIT;
   asm { int TCPIPVECT  };
   *errorcode=_AX;
   return _DX;
}
#endif

#ifdef _ddvA4_
/*
 #DOCLIST:Dev_Notify_ISR_Dyn clib\tcpip\ddvA4.htm

 @doc DOC_ddvA4_
 ---------------------------------------------------------------
 Signal from ISR
 ---------------------------------------------------------------
 @clibSub  Dev_Notify_ISR | devdrv_index.htm |
     Notify the TCP/IP stack from inside of a 
     <linkto>../HW/hal84A.htm<linkmid>RTX registered<linktail>
     Interrupt Service Routine that there is incoming data available
     (and/or that the device has sent a frame successfully).
            |
        <cfont>int Dev_Notify_ISR( DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab><s3> unsigned int receivedPackets,<nl>
        <tab><tab><tab><tab><s3> unsigned int sentPackets);<efont> |

 @parm  void *  | DevHandlePtr  |
    <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm  int  | receivedPackets | Number of available received packets
 @parm  int  | sentPackets     | Number of sent packets completed (provisional)
 @rdesc 0:  success <nl>
        -1:  See reported <code>errorcode<codee>.
 @comm
    Go <linkto>../../ip_dev.htm#ISR_and_RECVTask<linkmid>here<linktail> for example
    usage of this API for receiving data from a device.<nl>
    <nl>
    This asynchronous call will release your receiver task from its wait at the
    <linkto>ddvA3.htm<linkmid>Dev_Recv_Wait()<linktail> API, when the
    <cfont>receivedPackets<efont> parameter is non-zero.<s2> Your receiver task
    can then go and handle these received packets.<s2> Note that 
    <linkto>ddvA3.htm<linkmid>Dev_Recv_Wait()<linktail> 
    will fall through once for each <cfont>receivedPackets<efont> count 
    delivered by this API.<nl>
    <nl>
    Assuming that your receiver task is constructed such that the
    <linkto>ddvA2.htm<linkmid>Dev_Recv_Interface()<linktail> API
    is called from within a while loop, as shown in the 
    <linkto>../../ip_dev.htm#ISR_and_RECVTask<linkmid>myReceiveTask()<linktail>
    example, more efficient operation will result by always passing 1 for
    the <cfont>receivedPackets<efont> count here anytime there were
    one or more packets available at your device receiver.<s2> This
    will avoid unnecessary loops through your receiver task's outer loop.<nl>
    <nl>
    The provisional <cfont>sentPackets<efont> parameter passed to this API 
    should be set to zero for receiver events.<nl>

 @Also  ddvA0.htm | Dev_Open_Interface  |
        ddvA3.htm | Dev_Recv_Wait |
         |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xA4<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_Notify_ISR_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
        <cfont>#define TCPIP_DYN_LINK_DEV<nl>
        #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Dev_Notify_ISR(DevUserIfaceHandle DevHandlePtr,
                   unsigned int receivedPackets,
                   unsigned int sentPackets)
{
   _BX = receivedPackets;
   _CX = sentPackets;
   _ES = FP_SEG(DevHandlePtr);
   _DI = FP_OFF(DevHandlePtr);
   _AH = DEV_NOTIFY_ISR;
   asm { int TCPIPVECT  };
   return _AX;
}
#endif

#ifdef _ddvA5_
/*
 #DOCLIST:Dev_Get_Buffer_Dyn clib\tcpip\ddvA5.htm

 @doc DOC_ddvA5_
 ---------------------------------------------------------------
 Get a buffer from TCP/IP stack
 ---------------------------------------------------------------
 @clibSub  Dev_Get_Buffer | devdrv_index.htm |
    Get a buffer for storing incoming data 
    from the system's TCP/IP memory 
    <linkto>../../config.htm#IP_TCPIPMEM<linkmid>block<linktail>. |
        <cfont>int Dev_Get_Buffer( DevUserBufferHandle BufHandlePtr,<nl>
        <tab><tab><tab><tab><s3> char far * far * buffer,<nl>
        <tab><tab><tab><tab><s3> unsigned int length);<efont> |

 @parm  void *  | BufHandlePtr  | Output Parameter:<s2> Pointer to location where this
        function will on success set a handle to the allocated buffer.<s2>  This
        handle is used internally by the @Chip-RTOS TCP/IP stack to manage the
        subsequent release of this allocated buffer.<s2>This buffer release
        occurs automatically without further assistance from your
        application program.<s2>
        (This value is for internal use only.)<nl>
 @parm  void *  | buffer | Output Parameter:<s2>
        Holds on success the pointer to the beginning of the allocated buffer.
 @parm  int  | length     | Number of bytes buffer required
 @rdesc 0:  success , *buffer points to the beginning of the allocated buffer<nl>
        -1:  Allocation failed, *buffer is a null pointer.
 @comm
        This API is intended for use exclusively from inside TCP/IP device
        driver receiver 
        <linkto>../../ddvstruc.htm#DevRecv<linkmid>callback<linktail> 
        functions.<s2> The <cfont>BufHandlePtr<efont>
        passed to this API must be that received from the system in your
        receiver callback.<s2> The TCP/IP stack obtains
        this handle in this manner.<nl>
        <nl>
        Go <linkto>../../ip_dev.htm#DeviceReceive<linkmid>here<linktail> for
        example usage.
 @Also  ddvA0.htm | Dev_Open_Interface  |
        ddvA2.htm | Dev_Recv_Interface |
        ddvA6.htm | Dev_Send_Complete
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xA5<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_Get_Buffer_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
        <cfont>#define TCPIP_DYN_LINK_DEV<nl>
        #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Dev_Get_Buffer(DevUserBufferHandle BufHandlePtr,
                   char far * far * buffer,
                   unsigned int length)
{
   *buffer=NULL;
   asm{ push ds }
   asm{ les di,BufHandlePtr }
   _AH = DEV_GET_BUF ;
   _CX = length ;
   asm{ int TCPIPVECT }
   asm{ push dx }
   if(_AX==0)
   {
      *buffer = MK_FP(_DS,_SI);
   }
   asm pop dx
   asm pop ds
   return _DX;
}
#endif

#ifdef _ddvA6_
/*
 #DOCLIST:Dev_Send_Complete_Dyn clib\tcpip\ddvA6.htm

 @doc DOC_ddvA6_
 ---------------------------------------------------------------
 Signal message send complete
 ---------------------------------------------------------------
 @clibSub  Dev_Send_Complete | devdrv_index.htm |
    This API signals the TCP/IP stack that the final frame in a message
         has been sent.<s2> (Note that a message can be fragmented into
        multiple link layer frames.) |

        <cfont>int Dev_Send_Complete(DevUserIfaceHandle DevHandlePtr);<efont> |

 @parm  void *  | DevHandlePtr  |
   <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @rdesc 0:  success<nl>
        Otherwise: error
 @Also  ddvA0.htm | Dev_Open_Interface  |
        ddvA2.htm | Dev_Recv_Interface |
        ddvA3.htm | Dev_Recv_Wait
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xA6<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_Send_Complete_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
        <cfont>#define TCPIP_DYN_LINK_DEV<nl>
        #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @related     | ../../ip_dev.htm#DeviceSend
        | Example | - User's Device Send Function
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/

int Dev_Send_Complete(DevUserIfaceHandle DevHandlePtr)
{
   _ES = FP_SEG(DevHandlePtr);
   _DI = FP_OFF(DevHandlePtr);
   _AH = DEV_SND_COMPLETE;
   asm { int TCPIPVECT  };
   return _AX;
}
#endif


#ifdef _ddvA7_
/*
 #DOCLIST:Dev_Wait_DHCP_Complete_Dyn clib\tcpip\ddvA7.htm

 @doc DOC_ddvA7_
 ---------------------------------------------------------------
 Wait for DHCP completion
 ---------------------------------------------------------------
 @clibSub  Dev_Wait_DHCP_Complete | devdrv_index.htm |
    Waits for completion of IPv4 configuration process
        by DHCP<nl> (<i>Dynamic Host Configuration Protocol<ie>).<s2> |
        <cfont>int  Dev_Wait_DHCP_Complete(DevUserDriver far * DriverInfo,<nl>
        <tab><tab><tab><tab><tab><tab><s2> unsigned int time_s,<nl>
        <tab><tab><tab><tab><tab><tab><s2> int * errorcode);<efont> |

 @parm  void *  | DriverInfo  | Pointer to
         <linkto>../../ddvstruc.htm#DevUserDriver<linkmid>user driver information<linktail>.
 @parm  int  | time_s | Timeout seconds.<s2> This value will depend on the DHCP server used.<s2>
           A minimum value of 15 seconds is recommended.
 @parm  int  | errorcode    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.

 @rdesc 0:  success<nl>
        -1:  See reported <code>errorcode<codee>.
 @comm
   On success, the IPv4 address and netmask obtained via DHCP will be output
   to the <linkto>../../ddvstruc.htm#IpAddr<linkmid>IpAddr<linktail> and 
   <linkto>../../ddvstruc.htm#Netmask<linkmid>Netmask<linktail>
   members of the referenced 
   <linkto>../../ddvstruc.htm#DevUserDriver<linkmid>DevUserDriver<linktail>
   object.<s2> Additional
   DHCP information can then be found at the location reported in
   the <linkto>../../ddvstruc.htm#Dhcp_Data<linkmid>Dhcp_Data<linktail> member.<nl>
   <nl>
   This function should only be used following a successful call to 
   <linkto>ddvA0.htm<linkmid>Dev_Open_Interface()<linktail> when the
   <linkto>../../ddvstruc.htm#use_dhcp<linkmid>use_dhcp<linktail> member of 
   the <linkto>../../ddvstruc.htm#DevUserDriver<linkmid>DevUserDriver<linktail> 
   structure was set to 1.<nl>
   <nl>
   Go <linkto>../../ip_dev.htm#Install_Dev<linkmid>here<linktail> for further
   explanations and an example with source code.


 @Also  ddvA0.htm | Dev_Open_Interface  |
        ddvA2.htm | Dev_Recv_Interface |
        ddvA3.htm | Dev_Recv_Wait
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xA7<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_Wait_DHCP_Complete_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
          <cfont>#define TCPIP_DYN_LINK_DEV<nl>
          #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
int  Dev_Wait_DHCP_Complete(DevUserDriver far * DriverInfo, unsigned int time_s, int * errorcode)
{
   _CX = time_s;
   _ES = FP_SEG(DriverInfo);
   _DI = FP_OFF(DriverInfo);
   _AH = DEV_WAIT_DHCP_COMPLETE;
   asm { int TCPIPVECT  };
   *errorcode=_AX;
    return _DX;
}
#endif



#ifdef _ddvA8_
/*
 #DOCLIST:Dev_PPP_Register_Chap_Dyn clib\tcpip\ddvA8.htm

 @doc DOC_ddvA8_
 ---------------------------------------------------------------
 Register a PPP CHAP authentication callback function
 ---------------------------------------------------------------
 @clibSub  Dev_PPP_Register_Chap | devdrv_index.htm |
    Register a PPP CHAP authentication callback function. |
        <cfont>int Dev_PPP_Register_Chap(DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab><tab><tab><tab> const void far * AuthCallbackFunction,<nl>
        <tab><tab><tab><tab><tab><tab><tab> int *error);<efont> |

 @parm  void *  | DevHandlePtr  |
        <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm  void *  | AuthCallbackFunction | Pointer to the authentication callback function.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success<nl>
        -1:  failed

 @comm  The prototype of the user provided function is defined as:<nl><nl>
        <cfont>char huge * myCHAPAuthenticate(char *username) ;<efont><nl><nl>
        which returns the password (secret) corresponding to this user.<s2>
        If the user name is invalid, this function must return a NULL pointer.<nl>
 @Also  ddvA9.htm | Dev_PPP_Register_Pap  |
        ddvAA.htm | Dev_PPP_Set_Option |
        ddvAB.htm | Dev_PPP_Get_Peer_IP
 @Also  ddvAC.htm | Dev_PPP_Get_Peer_DNSIP |
        ddvB1.htm | Dev_PPP_Get_Peer_IPv6 | |
 @related TCP/IP Device Driver  | ../../ip_dev.htm | overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xA8<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_PPP_Register_Chap_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
          <cfont>#define TCPIP_DYN_LINK_DEV<nl>
          #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.11 | V1.01 | V1.01 | V0.90 | V1.00
*/
int  Dev_PPP_Register_Chap(DevUserIfaceHandle DevHandlePtr,
                           const void far * AuthCallbackFunction, int * error)
{
    asm { push DS } ;
    // Note: This higher level notation has the advantage over the assembly
    //    LES DI and LDS SI in that for small or medium memory models the
    //    compiler can figure out that FP_SEG(x) means DS register for near
    //    pointers.  For far pointers it compiles into the LES/LDS opcodes.
    _ES = FP_SEG(DevHandlePtr) ;
    _DI = FP_OFF(DevHandlePtr) ;

    _DS = FP_SEG(AuthCallbackFunction) ;
    _SI = FP_OFF(AuthCallbackFunction) ;

    _AH = DEV_PPP_REGISTER_CHAP ;
    asm { int TCPIPVECT } ;
    asm { pop DS } ;

    *error = _AX ;
    return   _DX ;
}
#endif

#ifdef _ddvA9_
/*
 #DOCLIST:Dev_PPP_Register_Pap_Dyn clib\tcpip\ddvA9.htm

 @doc DOC_ddvA9_
 ---------------------------------------------------------------
 Register a PPP PAP authentication callback function
 ---------------------------------------------------------------
 @clibSub  Dev_PPP_Register_Pap | devdrv_index.htm |
    Register a PPP PAP authentication callback function. |
        <cfont>int Dev_PPP_Register_Pap(DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab><tab><tab><tab> const void far * AuthCallbackFunction,<nl>
        <tab><tab><tab><tab><tab><tab><tab> int *error);<efont> |

 @parm  void *  | DevHandlePtr  |
    <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm  void *  | AuthCallbackFunction | Pointer to the authentication callback function.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success<nl>
        -1:  failed
 @comm  The prototype of the user provided function is defined as:<nl><nl>
        <cfont>int huge myPAPAuthenticate(char *username, char * password) ;<efont><nl><nl>
        which returns 1 for a valid username/password pair, else 0.<nl>

 @Also  ddvA8.htm | Dev_PPP_Register_Chap  |
        ddvAA.htm | Dev_PPP_Set_Option |
        ddvAB.htm | Dev_PPP_Get_Peer_IP
 @Also  ddvAC.htm | Dev_PPP_Get_Peer_DNSIP  |
        ddvB1.htm | Dev_PPP_Get_Peer_IPv6 |
         |

 @related TCP/IP Device Driver  | ../../ip_dev.htm | overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xA9<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_PPP_Register_Pap_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
          <cfont>#define TCPIP_DYN_LINK_DEV<nl>
          #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.11 | V1.01 | V1.01 | V0.90 | V1.00
*/
int  Dev_PPP_Register_Pap(DevUserIfaceHandle DevHandlePtr,
                          const void far * AuthCallbackFunction, int * error)
{
    asm { push DS } ;
    // Note: This higher level notation has the advantage over the assembly
    //    LES DI and LDS SI in that for small or medium memory models the
    //    compiler can figure out that FP_SEG(x) means DS register for near
    //    pointers.  For far pointers it compiles into the LES/LDS opcodes.
    _ES = FP_SEG(DevHandlePtr) ;
    _DI = FP_OFF(DevHandlePtr) ;

    _DS = FP_SEG(AuthCallbackFunction) ;
    _SI = FP_OFF(AuthCallbackFunction) ;

    _AH = DEV_PPP_REGISTER_PAP ;
    asm { int TCPIPVECT } ;
    asm { pop DS } ;

    *error = _AX ;
    return   _DX ;
}
#endif

#ifdef _ddvAA_
/*
 #DOCLIST:Dev_PPP_Set_Option_Dyn clib\tcpip\ddvAA.htm

 @doc DOC_ddvAA_
 -------------------------------------------------------------------
 Set PPP options on an own installed device driver from type of PPP
 -------------------------------------------------------------------
 @clibSub  Dev_PPP_Set_Option | devdrv_index.htm |
    Set PPP option on an own PPP device driver. |
        <cfont>int Dev_PPP_Set_Option(DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab><tab><tab> const PPP_Option far * ppp_option,<nl>
        <tab><tab><tab><tab><tab><tab> int *error);<efont> |

 @parm  void *  | DevHandlePtr  |
    <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm  void *  | ppp_option | Pointer to the
    <linkto>../../tcpstruc.htm#PPP_Option<linkmid>PPP option<linktail>
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success<nl>
        -1:  failed
 @Also  ddvA8.htm | Dev_PPP_Register_Chap  |
        ddvA9.htm | Dev_PPP_Register_Pap |
        ddvAB.htm | Dev_PPP_Get_Peer_IP
 @Also  ddvAC.htm | Dev_PPP_Get_Peer_DNSIP  |
        ddvB1.htm | Dev_PPP_Get_Peer_IPv6 |
         |
 @related TCP/IP Device Driver  | ../../ip_dev.htm | overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xAA<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_PPP_Set_Option_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
          <cfont>#define TCPIP_DYN_LINK_DEV<nl>
          #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.11 | V1.01 | V1.01 | V0.90 | V1.00
*/

int  Dev_PPP_Set_Option(DevUserIfaceHandle DevHandlePtr,
                        const PPP_Option far * ppp_option, int * error)
{
    asm { push DS } ;
    // Note: This higher level notation has the advantage over the assembly
    //    LES DI and LDS SI in that for small or medium memory models the
    //    compiler can figure out that FP_SEG(x) means DS register for near
    //    pointers.  For far pointers it compiles into the LES/LDS opcodes.
    _ES = FP_SEG(DevHandlePtr) ;
    _DI = FP_OFF(DevHandlePtr) ;

    _DS = FP_SEG(ppp_option) ;
    _SI = FP_OFF(ppp_option) ;

    _AH = DEV_PPP_SET_OPTION ;
    asm { int TCPIPVECT } ;
    asm { pop DS } ;

    *error = _AX ;
    return   _DX ;
}
#endif


#ifdef _ddvAB_
/*
 #DOCLIST:Dev_PPP_Get_Peer_IP_Dyn clib\tcpip\ddvAB.htm

 @doc DOC_ddvAB_
 -------------------------------------------------------------------
 Get PPP peer IP address
 -------------------------------------------------------------------
 @clibSub  Dev_PPP_Get_Peer_IP | devdrv_index.htm |
    Get IP address of a PPP peer. |
        <cfont>int Dev_PPP_Get_Peer_IP(DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab><tab><tab> long far * Address,<nl>
        <tab><tab><tab><tab><tab><tab> int *error);<efont> |

 @parm  void *  | DevHandlePtr  |
    <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm  long *  | Address | Output parameter:<s2>Pointer to the storage
            where the peer's IPv4 address in network byte order will be
            written by this API.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success, address points to the IP of the PPP peer<nl>
        -1:  failed
 @Also  ddvA8.htm | Dev_PPP_Register_Chap  |
        ddvA9.htm | Dev_PPP_Register_Pap |
        ddvAA.htm | Dev_PPP_Set_Option
 @Also  ddvAC.htm | Dev_PPP_Get_Peer_DNSIP  |
        ddvB1.htm | Dev_PPP_Get_Peer_IPv6  |
        ddv9F.htm | Dev_Get_IP
 @related TCP/IP Device Driver | ../../ip_dev.htm | overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xAB<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_PPP_Get_Peer_IP_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
          <cfont>#define TCPIP_DYN_LINK_DEV<nl>
          #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.11 | V1.01 | V1.01 | V0.90 | V1.00
*/

int Dev_PPP_Get_Peer_IP(DevUserIfaceHandle DevHandlePtr,
                        long far * Address, int * error)
{
    asm { push DS } ;
    // Note: This higher level notation has the advantage over the assembly
    //    LES DI and LDS SI in that for small or medium memory models the
    //    compiler can figure out that FP_SEG(x) means DS register for near
    //    pointers.  For far pointers it compiles into the LES/LDS opcodes.
    _ES = FP_SEG(DevHandlePtr) ;
    _DI = FP_OFF(DevHandlePtr) ;

    _DS = FP_SEG(Address) ;
    _SI = FP_OFF(Address) ;

    _AH = DEV_PPP_GET_PEER_IP ;
    asm { int TCPIPVECT } ;
    asm { pop DS } ;

    *error = _AX ;
    return   _DX ;
}
#endif

#ifdef _ddvAC_
/*
 #DOCLIST:Dev_PPP_Get_Peer_DNSIP_Dyn clib\tcpip\ddvAC.htm

 @doc DOC_ddvAC_
 ----------------------------------------------------------------------------------
 Get PPP DNS server address
 ----------------------------------------------------------------------------------
 @clibSub  Dev_PPP_Get_Peer_DNSIP | devdrv_index.htm |
    Get IP address of the DNS server from a PPP peer. |
        <cfont>int Dev_PPP_Get_Peer_DNSIP(DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab><tab><tab>long far * Address,<nl>
        <tab><tab><tab><tab><tab><tab>int flag,<nl>
        <tab><tab><tab><tab><tab><tab>int *error);<efont> |

 @parm  void *  | DevHandlePtr  |
    <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm  long *  | Address | Output parameter:<s2>Pointer to the storage
            where the DNS server's IPv4 address will be written by this API.
 @parm  int  | flag | 1: get IP of primary DNS server, 2: Get IP of secondary DNS server
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success, address points to the IP of the DNS server<nl>
        -1:  failed
 @Also  ddvA8.htm | Dev_PPP_Register_Chap  |
        ddvA9.htm | Dev_PPP_Register_Pap |
        ddvAA.htm | Dev_PPP_Set_Option
 @Also  ddvAB.htm | Dev_PPP_Get_Peer_IP  |
        ddvB1.htm | Dev_PPP_Get_Peer_IPv6  |
         |
 @related TCP/IP Device Driver  | ../../ip_dev.htm | overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xAC<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_PPP_Get_Peer_DNSIP_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
          <cfont>#define TCPIP_DYN_LINK_DEV<nl>
          #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.11 | V1.01 | V1.01 | V0.90 | V1.00
*/

int Dev_PPP_Get_Peer_DNSIP(DevUserIfaceHandle DevHandlePtr,
                           long far * Address, int flag, int * error)
{
    asm { push DS } ;
    // Note: This higher level notation has the advantage over the assembly
    //    LES DI and LDS SI in that for small or medium memory models the
    //    compiler can figure out that FP_SEG(x) means DS register for near
    //    pointers.  For far pointers it compiles into the LES/LDS opcodes.
    _ES = FP_SEG(DevHandlePtr) ;
    _DI = FP_OFF(DevHandlePtr) ;

    _DS = FP_SEG(Address) ;
    _SI = FP_OFF(Address) ;

    _BX = flag ;
    _AH = DEV_PPP_GET_PEER_DNS ;
    asm { int TCPIPVECT } ;
    asm { pop DS } ;

    *error = _AX ;
    return   _DX ;
}
#endif



#ifdef _ddvAD_
/*
 #DOCLIST:Dev_Get_Handle_By_Name_Dyn clib\tcpip\ddvAD.htm

 @doc DOC_ddvAD_
 ----------------------------------------------------------------------------------
 Get Device handle by name
 ----------------------------------------------------------------------------------
 @clibSub  Dev_Get_Handle_By_Name | devdrv_index.htm |
    Lookup a TCP/IP device driver by name.
        Obtain a handle to that device if found. |
        <cfont>int Dev_Get_Handle_By_Name( const char * drivername,<nl>
        <tab><tab><tab><tab><tab><tab><tab>DevUserIfaceHandle far * DevHandlePtr,<nl>
        <tab><tab><tab><tab><tab><tab><tab>int *error);
        <efont><nl> |

 @parm  void * * | DevHandlePtr  | Output parameter:<s2> On success,
    the device's 
    <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>handle<linktail>
    is put here.
 @parm  char *  | drivername | Driver name e.g. "Lance0" (type RTOS command
        <linkto>../../command.htm#IPCFG<linkmid>IPCFG<linktail>)
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success, DevHandlePtr contains the device handle pointer<nl>
        -1:  failed

 @comm  The device handle is required as a parameter to some API functions
      e.g. <linkto>ddvAE.htm<linkmid>Dev_Config_Iface()<linktail>.<nl>
      <nl>
      The <i>drivername<ie> match is done in a case sensitive manner.

 @related TCP/IP Device Driver | ../../ip_dev.htm | overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xAD<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_Get_Handle_By_Name_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
          <cfont>#define TCPIP_DYN_LINK_DEV<nl>
          #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/

int Dev_Get_Handle_By_Name(const char * drivername,DevUserIfaceHandle far * DevHandlePtr,
                           int *error)
{
    unsigned int es_reg ;
    *error=0;
    *DevHandlePtr=NULL; //Preset
    asm { push DS } ;
    _DS = FP_SEG(drivername) ;
    _SI = FP_OFF(drivername) ;
    _AH = DEV_GET_HANDLE_BYNAME;
    asm { int TCPIPVECT } ;
    asm { pop DS } ;

    if(_AX==0)
    {
        es_reg =_ES;
        *DevHandlePtr=MK_FP(es_reg,_DI);
        return 0;
    }
    *error = _AX ;
    return   _DX ;
}
#endif


#ifdef _ddvAE_
/*
 #DOCLIST:Dev_Config_Iface_Dyn clib\tcpip\ddvAE.htm

 @doc DOC_ddvAE_
 ----------------------------------------------------------------------------------
 IPv4 configuration of a device interface
 ----------------------------------------------------------------------------------
 @clibSub  Dev_Config_Iface | devdrv_index.htm |
    This API sets the IPv4 configuration of 
    an interface for particular multihome index. |
        <cfont>int Dev_Config_Iface(DevIpv4IfaceCfg far * devcfg, int *error);<efont><nl>|

 @parm  void *  | devcfg | <linkto>../../ddvstruc.htm#DevIpv4IfaceCfg<linkmid>DevIpv4IfaceCfg<linktail>
                 filled by the caller. Contains the device handle,IPv4 configuration
                 and the multihome index number.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>,<s2> 0 on success.
 @rdesc 0:  success,<nl>
        -1:  failed<nl>

 @comm  This functions provides the means for configuring a device interface
        (e.g. the standard internal Ethernet interface) with multiple IP
        addresses.<s2> A multihome index is specified to designate which
        IP address is being configured.<nl>
        <nl>
        If an interface is already configured at the specified
        multihome index number, the user  must first unconfigure
        it with <linkto>ddvB0.htm<linkmid>Dev_UnConfig_Iface()<linktail>.<nl>
        <nl>
        DHCP configuration of a device is only possible at multihomeindex 0.<nl>
        <nl>
        This API is recommended only for changing IP configuration on your own
        device interfaces or the internal Ethernet interface for multihome 
        index 1..4 (SC1x 1 ..3).<nl>
        <nl>
        Here is an example for adding an IP address to the internal Ethernet
        device at multihome index 1 on a SC1x3/SC2x system (for SC1x, 
        the LAN device name would instead be "NE2000"):

        @raw
        DevUserIfaceHandle DevHandlePtr;
        DevIpv4IfaceCfg  devcfg;
        int error;
        //Get the driver handle by name
        if(-1==Dev_Get_Handle_By_Name("Lance0",&DevHandlePtr,&error))
        {
          printf("\r\nError: Cannot detect driver handle, code %d",error);
          return 0;
        }
        //Set ip configuration
        devcfg.IfaceHandle    = DevHandlePtr;
        devcfg.flags          = 0;
        devcfg.multiHomeIndex = 1;  // configure multihome index 1
        inet_addr("192.168.200.59",&devcfg.IpAddr);
        inet_addr("255.255.255.0"",&devcfg.Netmask)

        if(-1==Dev_Config_Iface(&devcfg,&error))
        {
             printf("Error %d\r\n",error);
        }

 @related TCP/IP Device Driver | ../../ip_dev.htm | overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xAE<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_Config_Iface_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
          <cfont>#define TCPIP_DYN_LINK_DEV<nl>
          #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.


 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/

int Dev_Config_Iface(DevIpv4IfaceCfg far * devcfg, int *error)
{
    _ES = FP_SEG(devcfg) ;
    _DI = FP_OFF(devcfg) ;
    _AH = DEV_CONFIG_IFACE;
    asm { int TCPIPVECT } ;
    *error =_AX;
    return _DX;
}
#endif


#ifdef _ddvAF_
/*
 #DOCLIST:Dev_Config_Iface_IPv6_Dyn clib\tcpip\ddvAF.htm

 @doc DOC_ddvAF_
 ----------------------------------------------------------------------------------
 Configure a device interface with IPv6
 ----------------------------------------------------------------------------------
 @clibSub  Dev_Config_Iface_IPv6 | devdrv_index.htm |
    IPv6 configuration of an interface |
        <cfont>int Dev_Config_Iface_IPv6(DevIpv6IfaceCfg far * devcfg, int *error);<efont><nl>|

 @parm  void *  | devcfg | <linkto>../../ddvstruc.htm#DevIpv6IfaceCfg<linkmid>DevIpv4IfaceCfg<linktail>
                 filled by the caller. Contains the device handle,IPv6 configuration
                 and the multihomeindex number.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success,<nl>
        -1:  failed<nl>

 @comm  This functions provides the possibility to configure a device interface
        (e.g. the standard internal ethernet interface) with multiple IPv6 addresses
        by enter a particular multihome index number.<s2>
        If an interface is already configured at the specified multihomeindex number, the user
        first has to unconfigure it with 
        <linkto>ddvB0.htm<linkmid>Dev_UnConfig_Iface()<linktail>.<s2>
        DHCP configuration of a device is only possible at multihomeindex 0.<nl>
        <nl>
        It is recommended to use this function only for changing the IP
        configuration on either your own device interfaces or on
        the internal Ethernet interface for multihomeindex 1..4.
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xAF<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_Config_Iface_IPv6_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
          <cfont>#define TCPIP_DYN_LINK_DEV<nl>
          #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.


 @related TCP/IP Device Driver  | ../../ip_dev.htm | overview |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  | n/a   | V1.05 | V1.00
 @target_clib V2.04
*/

int Dev_Config_Iface_IPv6(DevIpv6IfaceCfg far * devcfg, int *error)
{
    _ES = FP_SEG(devcfg) ;
    _DI = FP_OFF(devcfg) ;
    _AH = DEV_CONFIG_IFACE_IPV6;
    asm { int TCPIPVECT } ;
    *error =_AX;
    return _DX;
}
#endif



#ifdef _ddvB0_
/*
 #DOCLIST:Dev_UnConfig_Iface_Dyn clib\tcpip\ddvB0.htm

 @doc DOC_ddvB0_
 ----------------------------------------------------------------------------------
 Remove a IPv4 or IPv6 configuration from a device interface (ip multihome)
 ----------------------------------------------------------------------------------
 @clibSub  Dev_UnConfig_Iface | devdrv_index.htm |
    Remove IPv4 or IPv6 device configuration |
        <cfont>int Dev_UnConfig_Iface( DevUserIfaceHandle DevHandlePtr, <nl>
        <tab><tab><tab><tab><tab><tab>unsigned int proto,<nl>
        <tab><tab><tab><tab><tab><tab>unsigned char mHomeIndex,<nl>
        <tab><tab><tab><tab><tab><tab>int *error);
        <efont><nl> |

 @parm  void * | DevHandlePtr  |
    <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm   int  | proto      | Protocol family AF_INET or AF_INET6
 @parm  int  | mHomeIndex | Multi home index number of the device
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success,<nl>
        -1:  failed
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xB0<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_UnConfig_Iface_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
          <cfont>#define TCPIP_DYN_LINK_DEV<nl>
          #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @comm
 Remove an IP configuration from an interface for a particular multi home index<nl>
 @related TCP/IP Device Driver  | ../../ip_dev.htm | overview |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.10 | V1.00
 @target_clib V2.04
*/

int Dev_UnConfig_Iface(DevUserIfaceHandle DevHandlePtr, int proto, unsigned char mHomeIndex, int *error)
{
    _ES = FP_SEG(DevHandlePtr) ;
    _DI = FP_OFF(DevHandlePtr) ;
    _BX = proto;
    _AL = mHomeIndex;
    _AH = DEV_UNCONFIG_IFACE;
    asm { int TCPIPVECT } ;
    *error =_AX;
    return _DX;
}
#endif




#ifdef _ddvB1_
/*
 #DOCLIST:Dev_PPP_Get_Peer_IPv6_Dyn clib\tcpip\ddvB1.htm

 @doc DOC_ddvB1_
 ----------------------------------------------------------------------------------
 Get IPv6 address of a PPP peer
 ----------------------------------------------------------------------------------
 @clibSub  Dev_PPP_Get_Peer_IPv6 | devdrv_index.htm |
    Get IPv6 address of a PPP peer |
        <cfont>int Dev_PPP_Get_Peer_IPv6(DevUserIfaceHandle DevHandlePtr, <nl>
        <tab><tab><tab><tab><tab><tab><tab>struct sockaddr_storage *Address,
        <tab><tab><tab><tab><tab><tab><tab>int *error);
        <efont><nl> |

 @parm  void * | DevHandlePtr  |
    <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
 @parm  void * | Address | Output parameter:<s2>Pointer to the storage
            where the peer's IPv6 address in network byte order will be
            written by this API.
 @parm  int  | error | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success, address points to the IPv6 address of the PPP peer<nl>
        -1:  failed
 @Also  ddvA8.htm | Dev_PPP_Register_Chap  |
        ddvA9.htm | Dev_PPP_Register_Pap |
        ddvAA.htm | Dev_PPP_Set_Option
 @Also  ddvAC.htm | Dev_PPP_Get_Peer_IP  |
        ddvAC.htm | Dev_PPP_Get_Peer_DNSIP  |
        ddv9F.htm | Dev_Get_IP
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xAB<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of a
        software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>Dev_PPP_Get_Peer_IPv6_Dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>TCPIP_DYN_LINK_DEV<efont>
        to your program before including the CLIB's header file(s):<nl>
        <ul><nl>
          <cfont>#define TCPIP_DYN_LINK_DEV<nl>
          #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @related TCP/IP Device Driver  | ../../ip_dev.htm | overview |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.11 | V1.01 | V1.01 | V0.90 | V1.00
 @target_clib V2.10
*/

int Dev_PPP_Get_Peer_IPv6( DevUserIfaceHandle DevHandlePtr,
                           struct sockaddr_storage *Address,
                           int *error )
{
  asm { push DS } ;
  // Note: This higher level notation has the advantage over the assembly
  //    LES DI and LDS SI in that for small or medium memory models the
  //    compiler can figure out that FP_SEG(x) means DS register for near
  //    pointers.  For far pointers it compiles into the LES/LDS opcodes.
  _ES = FP_SEG(DevHandlePtr) ;
  _DI = FP_OFF(DevHandlePtr) ;

  _DS = FP_SEG(Address) ;
  _SI = FP_OFF(Address) ;

  _AH = DEV_PPP_GET_PEER_IPV6 ;
  asm { int TCPIPVECT } ;
  asm { pop DS } ;

  *error = _AX ;
  return   _DX ;
}
#endif


#ifdef _ddvB2_
/*
 @doc DOC_ddvB2_
 ----------------------------------------------------------------------------------
 This function is used to get the DHCP data of a TCP/IP device interface.
 ----------------------------------------------------------------------------------
 @clibSub  Dev_Get_DHCP_Data | devdrv_index.htm |
    Get the DHCP data of a TCP/IP device interface |
        <cfont>int Dev_Get_DHCP_Data( DevUserIfaceHandle DevHandlePtr, <nl>
        <tab><tab><tab><tab><tab><s3>UserEthDhcp_Entry far * * dhcpDataPtr);<nl>
        <efont><nl> |

 @parm  void * | DevHandlePtr  |
         <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>

 @parm  void * | dhcpDataPtr      |
                 Pointer to a pointer that will be set by this API call, referencing a
                 <linkto>../../tcpstruc.htm#UserEthDhcp_Entry<linkmid>UserEthDhcp_Entry<linktail>
                 data structure within @CHIP-RTOS memory.

 @rdesc 0: success, If no data is available the dhcpDataPtr  will be set to NULL<nl>

 @related TCP/IP Device Driver  | ../../ip_dev.htm | overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xB2<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   |  n/a  |  n/a  | V1.80 | V1.80
 @target_clib V2.50
*/
int Dev_Get_DHCP_Data(DevUserIfaceHandle DevHandlePtr, UserEthDhcp_Entry far * * dhcpDataPtr)
{
    unsigned int dx_reg;
    unsigned int si_reg;

    _ES = FP_SEG(DevHandlePtr);
    _DI = FP_OFF(DevHandlePtr);
    _CX = 0;
    _AH = DEV_GET_DHCP_DATA;
    asm { int TCPIPVECT } ;
    dx_reg = _DX;
    si_reg = _SI;

    *dhcpDataPtr = (UserEthDhcp_Entry far *) MK_FP(dx_reg, si_reg);
    return 0;
}
#endif



#ifdef _ddvB3_
/*

 @doc DOC_ddvB3_
 ----------------------------------------------------------------------------------
 This function is used execute specific TCP/IP device driver functions.
 ----------------------------------------------------------------------------------
 @clibSub  Dev_Notify_Ioctl | devdrv_index.htm |
    Execute specific control functions
     on a TCP/IP device interface |
        <cfont>int Dev_Notify_Ioctl( DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab><tab><s1>  int flag<nl>
        <tab><tab><tab><tab><tab><s1> void * optionPtr,<nl>
        <tab><tab><tab><tab><tab><s1> int optionLen,<nl>
        <tab><tab><tab><tab><tab><s1> int * error<nl>
        <efont><nl> |

 @parm  void * | DevHandlePtr  |
         <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>

 @parm  int    | flag  |   The flag parameter specifies the requested functionality.
                           <nl>It is formed by ORing one or more of the following:<nl>
                           [0x4 - 0x0100] Device specific flags, other bits
                           are reserved by TCP/IP

 @parm  void * | optionPtr |  Specific parameters
 @parm  int    | optionLen |  Length in bytes of specific parameters.

 @parm  int * | error | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.

 @rdesc 0:  success<nl>
       -1:  failed
 @comm
  This API allows the user to call the driver
  <linkto>../../ddvstruc.htm#DevIoctl<linkmid>I/O control function<linktail>
  for executing special driver functions.<nl>
  An example for a special function would be to request the current
  PHY tranceiver link status for an Ethernet device.<nl><nl>
  IOCTL Flags already used:<nl>
  0x0001 : Called by TCPIP to inform about IPv4 configuration.<nl>
  <tab><tab><tab>optionPtr is  a pointer to a structure of type @ref DevIpv4IfaceCfg<nl>
  0x0002 : Not implemented yet, reserved for IPv6 configuration notification.<nl>
  0x0200 : Reserved by TCPIP for future use.<nl>
  0x0400 : Reserved by TCPIP for future use.<nl>
  0x0800 : The driver should enable a multicast address.<nl>
  <tab><tab><tab>optionPtr points to a to array of multicast MAC addresses with optionLen addresses.<nl>
  0x1000 : The driver should enable all multicast entries.<nl>
  0x2000 : The driver should erase its internal multicast table.<nl>
  0x4000 : Reserved by TCPIP for future use.<nl>
  0x8000 : Reserved by Beck IPC for own device driver implementations.<nl>


 @related TCP/IP Device Driver  | ../../ip_dev.htm | overview |
 @rtos  This library function invokes a RTOS software interrupt
        <linkto>../../tcpipapi.htm#0xAC0xB3<linkmid>documentation<linktail>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   |  n/a  |  n/a  | V1.35 | V1.35
 @target_clib V2.18
*/

int Dev_Notify_Ioctl(DevUserIfaceHandle DevHandlePtr, int flag,
                     void * optionPtr, int optionLen, int *error)
{
    _ES = FP_SEG(DevHandlePtr) ;
    _DI = FP_OFF(DevHandlePtr) ;
    _BX = FP_SEG(optionPtr);
    _SI = FP_OFF(optionPtr);
    _CX = flag;
    _DX = optionLen;
    _AH = DEV_NOTIFY_IOCTL;
    asm { int TCPIPVECT } ;
    *error = _AX ;
    return   _DX ;
}
#endif




#ifdef _ddvB4_
/*

 @doc DOC_ddvB4_
 ----------------------------------------------------------------------------------
 This function is used execute specific TCP/IP device driver functions.
 ----------------------------------------------------------------------------------
 @clibSub  Dev_SetSpecificFlags_IPv4 | devdrv_index.htm |
    Set/Erase specific device driver flags |
        <cfont>int Dev_SetSpecificFlags_IPv4( DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab><tab><s1> int flags)<nl>
        <efont><nl> |

 @parm  void * | DevHandlePtr  |
         <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>

 @parm  int    | flag  |  Flag parameter (By default these features are enabled)<nl>
                          Bit10 0: Disable IP Forwarding, 1: Enable IP Forwarding from/to the device<nl>
                          Bit11 0: Disable forwarding of IP directed broadcasts to and from this device<nl>
                          Bit13 0: Disable forwarding of IP multicast messages<nl>
                          Other flag bits must be set to zero.<nl>

 @rdesc 0:  success<nl>
       -1:  failed, Device not found

 @related TCP/IP Device Driver  | ../../ip_dev.htm | overview |
 @rtos  This library function invokes a RTOS software interrupt
        <linkto>../../tcpipapi.htm#0xAC0xB4<linkmid>documentation<linktail>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   |  n/a  |  n/a  | V1.40 | V1.40
 @target_clib V2.20
*/
int Dev_SetSpecificFlags_IPv4(DevUserIfaceHandle DevHandlePtr,int flags)
{
    _ES = FP_SEG(DevHandlePtr) ;
    _DI = FP_OFF(DevHandlePtr) ;
    _BX = flags;
    _AH = DEV_SET_SPECFLAGS;
    asm { int TCPIPVECT } ;
    return   _AX ;
}
#endif
/**************************************************************************/
//end DEVDRV.c
/*************************************************************************/

/****************************************************************************
* (C) 1999-2012 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : TCPIP.C
* Function       : TCPIP API socket functions
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\TCPIP\TCPIP.C, 129, 30.01.2009 17:12:03, Markus Bartat$

*****************************************************************************/

#include <STDLIB.H>
#include <DOS.H>
#include "common.h"
#include "config.h"
#include <TCPIPAPI.H>
#include <TCPIP.H>
#include "TCPPRIV.H"


/*************************************************************************/
//HTONS
/*************************************************************************/
#define HTONS(value)  ( (unsigned)(value<<8)|(unsigned)(value>>8) )

#define BIOS_VECT  (0xA0)       // Software Interrupt number for BIOS API
// Services


/*
  Note: The DOCLIST.EXE tool used by the C-Library HTML build process reacts
        to the token "#DOCLIST:" when it appears as the first non-white space
        on a line.  The tool transfers the text which follows into the
        BeckCLib.LST file that is used for the context sensitive help.

  #DOCLIST:*TCP CLIB\TCPIP\lib_index.htm
  #DOCLIST:ArpHeader tcpstruc.htm#ArpHeader
  #DOCLIST:ArpRouteCacheEntry tcpstruc.htm#ArpRouteCacheEntry
  #DOCLIST:ArpUserCallbackInfo tcpstruc.htm#ArpUserCallbackInfo
  #DOCLIST:atEntry tcpstruc.htm#atEntry
  #DOCLIST:Crypt_AES_Context crystruc.htm#Crypt_AES_Context
  #DOCLIST:Crypt_AES_ContextPtr crystruc.htm#Crypt_AES_Context
  #DOCLIST:Crypt_BigNumS crystruc.htm#Crypt_BigNumS
  #DOCLIST:Crypt_BigNumConstS crystruc.htm#Crypt_BigNumConstS
  #DOCLIST:Crypt_BlowfishKeyS crystruc.htm#Crypt_BlowfishKeyS
  #DOCLIST:Crypt_DesKeyScheduleS crystruc.htm#Crypt_DesKeyScheduleS
  #DOCLIST:Crypt_3DesKeyScheduleS crystruc.htm#Crypt_3DesKeyScheduleS
  #DOCLIST:Crypt_GenericKey crystruc.htm#Crypt_GenericKey
  #DOCLIST:Crypt_GenericKeyPtr crystruc.htm#Crypt_GenericKey
  #DOCLIST:Crypt_MD5_Context crystruc.htm#Crypt_MD5_Context
  #DOCLIST:Crypt_MD5_ContextPtr crystruc.htm#Crypt_MD5_Context
  #DOCLIST:Crypt_SHA1_Context crystruc.htm#Crypt_SHA1_Context
  #DOCLIST:Crypt_SHA1_ContextPtr crystruc.htm#Crypt_SHA1_Context
  #DOCLIST:DevUserBuffer ddvstruc.htm#DevUserBuffer
  #DOCLIST:DevUserBufferHandle ddvstruc.htm#DevUserBufferHandle
  #DOCLIST:DevUserDriver ddvstruc.htm#DevUserDriver
  #DOCLIST:DevUserIfaceHandle ddvstruc.htm#DevUserIfaceHandle
  #DOCLIST:DevIpv4IfaceCfg ddvstruc.htm#DevIpv4IfaceCfg
  #DOCLIST:DevIpv6IfaceCfg ddvstruc.htm#DevIpv6IfaceCfg
  #DOCLIST:DevUserLinkLayer ddvstruc.htm#DevUserLinkLayer
  #DOCLIST:DnsMailHost tcpstruc.htm#DnsMailHost
  #DOCLIST:fd_mask tcpstruc.htm#fd_set
  #DOCLIST:fd_set tcpstruc.htm#fd_set
  #DOCLIST:GetSocketOption tcpstruc.htm#GetSocketOption
  #DOCLIST:IcmpMib tcpstruc.htm#IcmpMib
  #DOCLIST:Iface_Entry tcpstruc.htm#Iface_Entry
  #DOCLIST:Iface_Entry_Ext tcpstruc.htm#Iface_Entry_Ext
  #DOCLIST:IfaceIPv6_Entry tcpstruc.htm#IfaceIPv6_Entry
  #DOCLIST:IfMib tcpstruc.htm#IfMib
  #DOCLIST:in_addr tcpstruc.htm#in_addr
  #DOCLIST:in6_addr tcpstruc.htm#in6_addr
  #DOCLIST:IpMib tcpstruc.htm#IpMib
  #DOCLIST:IpUserCallbackInfo tcpstruc.htm#IpUserCallbackInfo
  #DOCLIST:ntohl clib\TCPIP\htonl.htm
  #DOCLIST:ntohs clib\TCPIP\htons.htm
  #DOCLIST:Packet_Count tcpstruc.htm#Packet_Count
  #DOCLIST:PasCallBack tcpstruc.htm#PasCallBack
  #DOCLIST:Ping tcpstruc.htm#Ping
  #DOCLIST:PKI_CERT_ADD_Entry tcpstruc.htm#PKI_CERT_ADD_Entry
  #DOCLIST:PKI_OWNKEYPAIR_ADD_Entry tcpstruc.htm#PKI_OWNKEYPAIR_ADD_Entry
  #DOCLIST:PPPClient_Init tcpstruc.htm#PPPClient_Init
  #DOCLIST:PPPClient_Init_IPv6 tcpstruc.htm#PPPClient_Init_IPv6
  #DOCLIST:PPPDial tcpstruc.htm#PPPDial
  #DOCLIST:PPP_IPCfg_Data tcpstruc.htm#PPP_IPCfg_Data
  #DOCLIST:PPP_IPCfg_Data_IPv6 tcpstruc.htm#PPP_IPCfg_Data_IPv6
  #DOCLIST:PPP_ModemHangup tcpstruc.htm#PPP_ModemHangup
  #DOCLIST:PPP_Option tcpstruc.htm#PPP_Option
  #DOCLIST:recv_params tcpstruc.htm#recv_params
  #DOCLIST:Route_Entry tcpstruc.htm#Route_Entry
  #DOCLIST:send_params tcpstruc.htm#send_params
  #DOCLIST:SetSocketOption tcpstruc.htm#SetSocketOption
  #DOCLIST:sockaddr_in tcpstruc.htm#sockaddr_in
  #DOCLIST:sockaddr tcpstruc.htm#sockaddr
  #DOCLIST:sockaddr_in6 tcpstruc.htm#sockaddr_in6
  #DOCLIST:sockaddr_storage tcpstruc.htm#sockaddr_storage
  #DOCLIST:SocketInfo tcpstruc.htm#SocketInfo
  #DOCLIST:SocketInfoIPv4v6 tcpstruc.htm#SocketInfoIPv4v6
  #DOCLIST:SSL_SESSION_NEW_Entry tcpstruc.htm#SSL_SESSION_NEW_Entry
  #DOCLIST:TcpMib tcpstruc.htm#TcpMib
  #DOCLIST:timeval tcpstruc.htm#timeval
  #DOCLIST:UdpMib tcpstruc.htm#UdpMib
  #DOCLIST:UserEthDhcp_Entry tcpstruc.htm#UserEthDhcp_Entry



 @doc DOC_INDEX
 ---------------------------------------------------------------
 TCP/IP API Table of Contents
 ---------------------------------------------------------------
 @clibLinkIdx  <tab><cfont>#include <InBraces TCPIP\.H><efont><nl>
  <tab><tab><tab><tab><tab><arial>which includes<ariale> <cfont>
 <InBraces TCPIPAPI\.H><efont> |
    <tab><linkto>#TCP<linkmid>TCP/IP<linktail><tab>
    <tab><linkto>#PKI<linkmid>PKI/SSL<linktail><tab>
    <linkto>#Client<linkmid>PPP Client<linktail><tab>
    <linkto>#Server<linkmid>PPP Server<linktail><tab>
    <linkto>#Other<linkmid>Other<linktail><tab>
    | <nl>
    
  This API provides access to the IPC@CHIP&reg; TCP/IP stack's socket interface
  for programming TCP/IP applications.<nl>
  <nl>  
  Please note, that we cannot explain the entire functionality of the TCP/IP protocol and
  the working of the socket interface in this document.<s2> Good books for understanding
  TCP/IP and the socket interface are:
  <ul>
  1. Internetworking with TCP/IP, Volume 1-3 from Douglas E.Comer<nl>
  2. TCP/IP Illustrated, Volume 1 from W. Richard Stevens<nl>
  <ule>
  
  <bold>Related<bolde>:<ul>
      <li>TCP/IP <linkto>../../tcpstruc.htm<linkmid>Data Structures<linktail><nl>
      <li>TCP/IP <linkto>../../iperrlst.htm<linkmid>Error Codes<linktail> Listing<nl>
      <li><linkto>devdrv_index.htm<linkmid>Device Driver<linktail> API<s2> (For user defined TCP/IP devices)<nl>
      <li><linkto>crypt_index.htm<linkmid>Cryptographic<linktail> API<nl>
      <li><linkto>ipsec_index.htm<linkmid>IP Security<linktail> API<nl>
      <li><linkto>bsd_index.htm<linkmid>BSD compatible<linktail> alternative socket API<nl>
      <li><linkto>../../ip6.htm<linkmid>TCP/IP IPv4/v6 Dual layer stack<linktail><nl>
      <li><linkto>../../tcpclsrv.htm<linkmid>Client/Server applications<linktail><nl>   
  <ule>


 @libcat1a  TCP | TCP/IP | tcpIPR | Get_IPConfig | Get IP, subnet mask and/or gateway |
 @libcat1a  TCP | TCP/IP | tcpIPW | Set_IPConfig | Set IP, subnet mask and/or gateway |
 @libcat1a  TCP | TCP/IP | tcpPSIp | PPP_Server_GetIP | Get IP Address of the PPP Server |
 @libcat1a  TCP | TCP/IP | tcpPCIp | PPP_Client_GetIP | Get IP Address of the PPP Client |
 @libcat1a  TCP | TCP/IP | tcp11 | InetToAscii | Convert an IPv4 address to an IP string |
 @libcat1a  TCP | TCP/IP | tcp08 | inet_addr | Converts a string containing
    an IPv4 address in dot notation  |
 @libcat1a  TCP | TCP/IP | tcpC1 | inet_pton | Convert an IP address
    (IPv4 or IPv6) from standard text representation to binary|
 @libcat1a  TCP | TCP/IP | tcpC2 | inet_ntop | Convert an IP address
    (IPv4 or IPv6) from binary to standard text representation|

 @libcat1a  TCP | TCP/IP | tcp01  | opensocket   | <nl>Open TCP or UDP IPv4 socket | <tab><tab>--- Socket Functions ---<nl>
 @libcat1a  TCP | TCP/IP | tcpC3  | opensocket_ext   | Open an IPv4 or IPv6 socket |
 @libcat1a  TCP | TCP/IP | tcp02  | closesocket  | Close socket |
 @libcat1a  TCP | TCP/IP | tcp03  | bind         | Associates a local address with a socket |
 @libcat1a  TCP | TCP/IP | tcp04  | connect | Establish a connection to a specifed socket |
 @libcat1a  TCP | TCP/IP | tcp0C | GetWaitingBytes | Report the number of bytes on a socket |
 @libcat1a  TCP | TCP/IP | tcp15 | Set_IP_Type_Of_Service | Set socket's Type-Of-Service |
 @libcat1a  TCP | TCP/IP | tcp16 | setsockopt | Set options on a socket |
 @libcat1a  TCP | TCP/IP | tcp17 | getsockopt | Get options on a socket |
 @libcat1a  TCP | TCP/IP | tcp18 | Set_Blocking_Mode | Set a socket in blocking or non-blocking mode |
 @libcat1a  TCP | TCP/IP | tcp21 | get_socketerror | Get last socket error |
 @libcat1a  TCP | TCP/IP | tcp1A | select | Await events on a selected set of sockets |
 @libcat1a  TCP | TCP/IP | tcp1Am | select_ms | Alternative socket event wait method |

 @libcat1a  TCP | TCP/IP | tcpcon | tcp_connect  | <nl>Open TCP/IP socket and connect | <tab><tab>--- TCP/IP Sockets ---<nl>
 @libcat1a  TCP | TCP/IP | tcp0D | accept | Accept the next incoming connection |
 @libcat1a  TCP | TCP/IP | tcp0E | listen | Listen for incoming connections |
 @libcat1a  TCP | TCP/IP | htons | htons | Converts a 16 bit word from host to TCP/IP network byte order |
 @libcat1a  TCP | TCP/IP | htonl | htonl | Converts a 32 bit long word from host to TCP/IP network byte order |
 @libcat1a  TCP | TCP/IP | tcp0F | send | Transmit a message (TCP) |
 @libcat1a  TCP | TCP/IP | tcp10 | recv | Receive message (TCP) |
 @libcat1a  TCP | TCP/IP | tcp12 | ResetConnection | Abort a connection on a socket |
 @libcat1a  TCP | TCP/IP | tcp13 | setlinger | Set linger time on close (TCP) |
 @libcat1a  TCP | TCP/IP | tcp14 | setreuse | Set reuse option on a listening socket |
 @libcat1a  TCP | TCP/IP | tcp22 | Get_TCP_Socket_State | Find TCP socket and return state |
 @libcat1a  TCP | TCP/IP | tcp24 | Get_TCP_Socket_State_IP_All | Find TCP socket and return state (IPv4 and IPv6)|
 @libcat1a  TCP | TCP/IP | tcp23 | FindAllOpenSockets | Get information about all open sockets |
 @libcat1a  TCP | TCP/IP | tcp25 | FindAllOpenSockets_IP_All | Get information about all open sockets (IPv4 and IPv6)|
 @libcat1a  TCP | TCP/IP | tcp26 | shutdown | Shutdown socket in read,write or both directions |

 @libcat1a  TCP | TCP/IP | tcp05 | recvfrom | <nl>Receive a datagram and store the source address | <tab><tab>--- UDP Sockets ---<nl>
 @libcat1a  TCP | TCP/IP | tcp27 | recvfromto | <nl>Receive a datagram and store source and dest. address |
 @libcat1a  TCP | TCP/IP | tcp29 | recvfromto_iface | <nl>Receive a datagram and store source, dest. address and interface|
 @libcat1a  TCP | TCP/IP | tcp06 | sendto | Transmit a datagram |
 @libcat1a  TCP | TCP/IP | tcp28 | sendto_iface | Transmit a datagram via specified device|

 @libcat1a  TCP | TCP/IP | tcp30 | getHostByName   | <nl>Get a host's address(es) by domain name (IPv4) | <tab><tab>--- DNS Resolver ---<nl>
 @libcat1a  TCP | TCP/IP | tcp31 | getHostByName2  | Get a host's address(es) by domain name (IPv6) |
 @libcat1a  TCP | TCP/IP | tcp32 | getHostByAddr  | Get a host's domain name by address (IPv4) |
 @libcat1a  TCP | TCP/IP | tcp33 | getHostByAddr2  | Get a host's domain name by address (IPv6) |
 @libcat1a  TCP | TCP/IP | tcp34 | getMailHosts  | Get mail hosts |
 @libcat1a  TCP | TCP/IP | tcp35 | setNameServer  | Add prioritised name server |

 @libcat1b  PKI | PKI/SSL| tcpD0 | PKI_CertificateAdd  | <nl>Add a certificate to the PKI | <tab><tab>--- PKI Functions ---<nl>
 @libcat1b  PKI | PKI/SSL| tcpD1 | PKI_CertificateDel  | Delete a certificate from the PKI |
 @libcat1b  PKI | PKI/SSL| tcpD2 | PKI_OwnKeyPairAdd   | Add own private/public key pair |

 @libcat1b  PKI | PKI/SSL| tcpD8 | SSL_SessionNew      | <nl>Open a new SSL session | <tab><tab>--- SSL Functions ---<nl>
 @libcat1b  PKI | PKI/SSL| tcpD7 | SSL_SessionClose    | Close a SSL session |
 @libcat1b  PKI | PKI/SSL| tcpD9 | SSL_SessionProp     | Set SSL session proposals |
 @libcat1b  PKI | PKI/SSL| tcpDA | SSL_SessionOpt      | Set SSL session options |
 @libcat1b  PKI | PKI/SSL| tcpDB | SSL_AddClientCA     | Add a client CA certificate |
 @libcat1b  PKI | PKI/SSL| tcpDC | SSL_ClientStart     | Start the SSL client |
 @libcat1b  PKI | PKI/SSL| tcpDD | SSL_SendFlush       | Flush SSL user data |
 @libcat1b  PKI | PKI/SSL| tcpDE | SSL_ConnClose       | Close a SSL connection |
 @libcat1b  PKI | PKI/SSL| tcpD5 | SSL_Get_ConnState   | Get SSL connection state information |
 @libcat1b  PKI | PKI/SSL| tcpD6 | SSL_HandshakeComplete  | Check handshake status |

 @libcat2y  PPP | Client | tcp40 | PPP_Client_Installed | Check if PPP client is installed |
 @libcat2y  PPP | Client | tcp41 | PPP_Client_Open | Open a PPP connection (IPv4) |
 @libcat2y  PPP | Client | tcp46 | PPP_Client_Open_IPv6  | Open a PPP
        connection with IPv6 address config |
 @libcat2y  PPP | Client | tcp42 | PPP_Client_Close | Close a PPP client connection |
 @libcat2y  PPP | Client | tcp43 | PPP_Client_GetStatus | Get PPP client status |
 @libcat2y  PPP | Client | tcp44 | PPP_Client_Get_DNSIP | Get DNS IP |
 @libcat2y  PPP | Client | tcp45 | PPP_Client_SetOptions | Set PPP options for the PPP client |
 @libcat2y  PPP | Client | tcpPCIp | PPP_Client_GetIP | Get IP Address of the PPP Client |
 @libcat2y  PPP | Client | tcp47 | PPP_Client_Pause | Pause/resume the PPP client task |

 @libcat3y  PPP | Server | tcp50 | PPP_Server_Installed | Check if PPP server is installed |
 @libcat3y  PPP | Server | tcp51 | PPP_Server_Suspend | Suspend the PPP server task |
 @libcat3y  PPP | Server | tcp52 | PPP_Server_Activate | Activate the PPP server |
 @libcat3y  PPP | Server | tcp53 | PPP_Server_GetStatus | Get the current state of the PPP server |
 @libcat3y  PPP | Server | tcp54 | PPP_Server_Get_Cfg | Get configuration data of
                        the IPv4 PPP server |
 @libcat3y  PPP | Server | tcp56 | PPP_Server_Get_Cfg_IPv6 | Get configuration data of
                        the IPv6 PPP server |
 @libcat3y  PPP | Server | tcp55 | PPP_Server_SetOptions | Set PPP options for the PPP server |
 @libcat3y  PPP | Server | tcpPSIp | PPP_Server_GetIP | Get IP Address of the PPP Server |
 @libcat3y  PPP | Server | tcp57 | PPP_Server_Pause | Pause/resume the PPP server task |

 @libcat4  Other | tcp65 | Get_FTP_Login_Counters | <nl>Access the FTP server login counters | <tab><tab>--- Monitoring ---<nl>
 @libcat4  Other | tcp66 | Get_Telnet_Login_Counters | Access the Telnet server login counters |
 @libcat4  Other | tcp67 | Get_Telnet_State | Check if have an active telnet session |
 @libcat4  Other | tcp70 | Get_Installed_Servers | Get information about running servers |
 @libcat4  Other | tcp78 | Get_TCPIP_Memory_Status | Get information about TCP/IP stack memory usage |
 @libcat4  Other | tcp74 | Get_TCPIP_Statistics | Access the internal network packet counter |
 @libcat4  Other | tcp60 | Get_SNMP_Data | Get internal TCP/IP SNMP variables |
 @libcat4  Other | tcp60a | Get_SNMP_DataEx | Get internal TCP/IP SNMP variables (Extended) |

 @libcat4  Other | tcp72 | DHCP_use | <nl>Set/Reset DHCP usage of the Ethernet interface | <tab><tab>--- DHCP ---<nl>
 @libcat4  Other | tcp73 | Get_DHCP_Status | Get DHCP status of the Ethernet interface |
 @libcat4  Other | tcp73a | Get_DHCP_Status_Ext | Get DHCP status of the Ethernet interface |

 @libcat4  Other | tcp75 | Ping_Open | <nl>Open and start ICMP echo requests | <tab><tab>--- ping ---<nl>
 @libcat4  Other | tcp76 | Ping_Close | Finish ICMP echo requests |
 @libcat4  Other | tcp77 | Ping_Statistics | Retrieve ping information |

 @libcat4  Other | tcp79 | Set_FTPServer_Idle_Timeout | <nl>Set FTP server time-out  | <tab><tab>--- Server Time-outs ---<nl>
 @libcat4  Other | tcp79a | Set_TelnetServer_Idle_Timeout | Set Telnet server time-out  |
 @libcat4  Other | tcp79b | Get_FTPServer_Idle_Timeout | Get FTP server time-out value  |
 @libcat4  Other | tcp79c | Get_TelnetServer_Idle_Timeout | Get Telnet server time-out value  |

 @libcat4  Other | tcp80 | AddDefaultGateway | <nl><depr> Add the default gateway | <tab><tab>--- Gateway ---<nl>
 @libcat4  Other | tcp80a | AddDefaultGatewayEx | Add the default gateway (Extended) |
 @libcat4  Other | tcp81 | DelDefaultGateway | Delete the default gateway |
 @libcat4  Other | tcp82 | GetDefaultGateway | Get the current default gateway |
 @libcat4  Other | tcp83 | AddStaticRoute | Add a route for an interface |
 @libcat4  Other | tcp83a | AddStaticRouteEx | Add a route for an interface (extended)|
 @libcat4  Other | tcp84 | DelStaticRoute | Delete a route from an interface |
 @libcat4  Other | tcp7F | TCPIP_SetOption | Set TCPIP options |


 @libcat4  Other | tcp88 | DelArpEntryByPhys | <nl>Delete ARP entry by physical address | <tab><tab>--- ARP cache access ---<nl>
 @libcat4  Other | tcp89 | AddArpEntry | Add an entry in the ARP table |
 @libcat4  Other | tcp8A | GetARPRouteCacheEntries | Read ARP cache table|

 @libcat4  Other | tcp90 | Add_IGMP_Membership | <nl>Install an IP multicast address entry | <tab><tab>--- IP Multicast ---<nl>
 @libcat4  Other | tcp91 | Drop_IGMP_Membership | Delete an IP multicast address entry |
 @libcat4  Other | tcp92 | IPMulticast_to_MacAddr | Map IP multicast address to Ethernet address |

 @libcat4  Other | tcp19 | RegisterCallbackFunction | <nl>Register a user TCP callback function | <tab><tab>--- Callback Installers ---<nl>
 @libcat4  Other | tcp7a | RegisterIPCallbackHandler | Register an User callback handler for incoming IP packets |
 @libcat4  Other | tcp7c | RegisterIPCallbackHandler_Snd | Register an User callback handler for outgoing IP packets |
 @libcat4  Other | tcp7b | Register_ARP_User_CB | Register an ARP User callback handler |
 @libcat4  Other | tcp7d | RegisterIPConfigCallback | Register an callback handler for IP configuration changes |

 @libcat4  Other | tcp09 | api_sleep | <nl><depr> Sleep for specified number of milliseconds | <tab><tab>--- Miscellaneous ---<nl>
 @libcat4  Other | tcp71 | Reconfigure_ethernet | Reconfigure Ethernet interface |
 @libcat4  Other | tcp8D | Get_Iface_Entries | <depr> Read table of TCP/IP device interfaces |
 @libcat4  Other | tcp8F | Get_Iface_Entries_Ext | Read table of TCP/IP device interfaces with all IPv4 configurations/per interface|
 @libcat4  Other | tcp8E | SetIfaceMTU | Set MTU of an device interface |
 @libcat4  Other | tcpC0 | Get_IPv6_Iface_Entries | TCP/IP IPv6 device interface information |

*/

/*************************************************************************/
//
/*************************************************************************/
#ifdef _htonl_
/*
 @doc DOC_htonl_
 ---------------------------------------------------------------
 Converts a 32 bit long word from host to TCP/IP network byte order
 ---------------------------------------------------------------
 @clib  htonl | Converts a 32 bit long word from host to TCP/IP network
    byte order. |
        <cfont>unsigned long htonl ( unsigned long hostlong );<efont> |
 @parm  int  | hostlong  | 32 bit value whose byte order is to be swapped
 @rdesc input value returned with byte order swapped
 @comm  This function converts the provided 32 bit value from Intel byte
        ordering (little endian) to network byte order (big endian),
        or vice-versa.

    For example, calling with input value 0x12345678 will return the
    value 0x78563412.

        No entry into the @CHIP-RTOS API is made here.<s2> This action
        is taken immediately within this library call.

        The macro <cfont>ntohl<efont> shown below is defined for use where
        you want to state that the conversion is from network byte order to
        host byte order.<s2>  Either  way, the same library code does
        the job.

  @raw
    <tab><tab> #define  ntohl htonl
        

 @Also  htons.htm | htons  |
        tcp03.htm | bind     | |
*/

// Implemented with assembly code.
#endif
/*************************************************************************/
//
/*************************************************************************/
#ifdef _htons_
/*
 @doc DOC_htons_
 ---------------------------------------------------------------
 Converts a 16 bit word from host to TCP/IP network byte order
 ---------------------------------------------------------------
 @clib  htons | Converts a 16 bit word from host to TCP/IP network byte order. |
        <cfont>unsigned short htons ( unsigned short hostshort );<efont> |
 @parm  int  | hostshort  | 16 bit value whose byte order is to be swapped
 @rdesc input value returned with byte order swapped
 @comm  This function converts the provided 16 bit value from Intel byte
        ordering (little endian) to network byte order (big endian),
        or vice-versa.<s2>
        This is commonly needed for TCP/IP port number specifications.

      For example, calling with input value 0x1234 will return the
    value 0x3412.

  No entry into the @CHIP-RTOS API is made here.<s2> This action
        is taken immediately within this library call.

        The macro <cfont>ntohs<efont> shown below is defined for use where
        you want to state that the conversion is from network byte order to
        host byte order.<s2>  Either way, the same library code executes.

  @raw
    <tab><tab> #define  ntohs htons
        
 @Also  tcp04.htm | connect  |
        tcp03.htm | bind     |
        htonl.htm | ntohl
*/

// Implemented with assembly code.

#endif


/*************************************************************************/
// Get IP of the Ethernet interface
/*************************************************************************/
#ifdef _tcpIPR_
/*
 @doc DOC_tcpIPR_
 ---------------------------------------------------------------
 Get IP, Net Mask of the default Ethernet interface and the Gateway
 ---------------------------------------------------------------
 @clib  Get_IPConfig | Get IP, subnet mask
        and/or gateway of the default Ethernet interface. |
        <cfont>void Get_IPConfig ( char far *IP,<nl>
        <tab><tab><tab><tab><tab>char far *Mask,<nl>
        <tab><tab><tab><tab><tab>char far *Gateway );<efont> |
 @parm  int  | IP  | Output parameter:<s2> Pointer to a 16 byte memory area
        where the IP address is to be stored as a null terminated string.
 @parm  int  | Mask  | Output parameter:<s2> Pointer to a 16 byte memory area
        where the subnet mask is to be stored as a null terminated string.
 @parm  int  | Gateway | Output parameter:<s2> Pointer to a 16 byte memory
        area where the gateway address is to be stored as a null terminated
        string.
 @rdesc -- none --
 @comm  Any of the three output parameters can be set to NULL pointers if
        the respective output is not desired.
 @commtarget SC1x3/SC2x |
        This function applies only to the IPv4 configuration of the internal
        integrated Ethernet device interface.<nl>
        <nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x01<linkmid>documentation<linktail>
        for more details.

 @Also tcpIPW.htm | Set_IPConfig  |
       tcpC0.htm | Get_IPv6_Iface_Entries |  |
 @Also tcp08.htm | inet_addr  |
       bsd30.htm | inet_addr_bsd |  |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 |  n/a  | V0.90 | V1.00
*/
void Get_IPConfig (char far *IP, char far * Mask, char far *Gateway)
{
    if (FP_SEG(IP))
    {
        _DX = FP_OFF(IP);
        _ES = FP_SEG(IP);
        _AH = 0x01;                         // Get IP Address in [ES:DX]
        asm { int BIOS_VECT  } ;
    }

    if (FP_SEG(Mask))
    {
        _DX = FP_OFF(Mask);
        _ES = FP_SEG(Mask);
        _AH = 0x03;                         // Get Net Mask in [ES:DX]
        asm { int BIOS_VECT  } ;
    }

    if (FP_SEG(Gateway))
    {
        _DX = FP_OFF(Gateway);
        _ES = FP_SEG(Gateway);
        _AH = 0x05;                         // Get Gateway in [ES:DX]
        asm { int BIOS_VECT  } ;
    }
}
#endif

/*************************************************************************/
// Set IP configuration,becomes valid after call of reconfigure Ethernet
/*************************************************************************/
#ifdef _tcpIPW_
/*
 @doc DOC_tcpIPW_
 ---------------------------------------------------------------
 Set IP, Net Mask of the default Ethernet interface and/or Gateway
 ---------------------------------------------------------------
 @clib  Set_IPConfig | Set IP, subnet mask of the default Ethernet interface
         and/or gateway. |
        <cfont>void Set_IPConfig ( const char far *IP,<nl>
        <tab><tab><tab><tab><tab>const char far *Mask,<nl>
        <tab><tab><tab><tab><tab>const char far *Gateway );<efont> |
 @parm  int  | IP  | Pointer to new IP address expressed as a null
        terminated ASCII string in network address dot notation.
 @parm  int  | Mask  | Pointer to new net submask expressed as a null
        terminated ASCII string in dot notation.
 @parm  int  | Gateway | Pointer to new gateway address expressed as a null
        terminated ASCII string in dot notation.
 @rdesc -- none --
 @comm  Any of the three parameters can be set to NULL pointers if
        the respective value is not to be set.<nl>
        A new IP configuration must be activated by calling the ipeth command
        or <linkto>tcp71.htm<linkmid>Reconfigure_ethernet<linktail>.<nl>
 @commtarget SC1x3/SC2x |
        This function applies only to the IPv4 configuration of the internal
        integrated Ethernet device interface.<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x02<linkmid>documentation<linktail>
        for more details.
 @Also  tcpPSIp.htm | PPP_Server_GetIP |
        tcpPCIp.htm | PPP_Client_GetIP |
        tcpIPR.htm  | Get_IPConfig
 @Also tcp11.htm | InetToAscii  |  |  |  |
 @related [IP]<s2> | ../../config.htm#IP_ADDRESSx | ADDRESS |
        - CHIP.INI entry
 @related [IP]<s2> | ../../config.htm#IP_NETMASKx | NETMASK |
        - CHIP.INI entry
 @related [IP]<s2> | ../../config.htm#IP_GATEWAY | GATEWAY |
        - CHIP.INI entry

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 |  n/a  | V0.90 | V1.00

*/
void Set_IPConfig(const char far *IP,
                  const char far *Mask,
                  const char far *Gateway)
{
    if (FP_SEG(IP))
    {
        _DX = FP_OFF(IP);
        _ES = FP_SEG(IP);
        _AH = 0x02;                         // Set IP Address in [ES:DX]
        asm { int BIOS_VECT  } ;
    }

    if (FP_SEG(Mask))
    {
        _DX = FP_OFF(Mask);
        _ES = FP_SEG(Mask);
        _AH = 0x04;                         // Set Net Mask in [ES:DX]
        asm { int BIOS_VECT  } ;
    }

    if (FP_SEG(Gateway))
    {
        _DX = FP_OFF(Gateway);
        _ES = FP_SEG(Gateway);
        _AH = 0x06;                         // Set Gateway in [ES:DX]
        asm { int BIOS_VECT  } ;
    }
}
#endif

/*************************************************************************/
//PPP Server IP
/*************************************************************************/
#ifdef _tcpPSIp_
/*
 @doc DOC_tcpPSIp_
 ---------------------------------------------------------------
 Reads the IP Address of the PPP Server
 ---------------------------------------------------------------
 @clib  PPP_Server_GetIP | Reads the IP Address of the PPP Server |
        <cfont>void PPP_Server_GetIP (char far *IP );<efont> |
 @parm  int  | IP  | Output parameter:<s2> Pointer to a 16 byte
        memory area where the IPv4 address is to be stored as a null
        terminated string.
 @rdesc -- none --
 @comm  Copies the current IPv4 address of the PPP Server into the provided
        string.<s2> If no IP address of the PPP Server is available, the string
        will be empty.<nl>
 @commtarget SC1x3/SC2x |
        <bold>This function is deprecated,<bolde> because it does not work if the
        PPP server uses the IPv6 protocol.<s2> The IP configuration of
        all TCP/IP devices can be read
        by using <linkto>tcp8D.htm<linkmid>Get_Iface_Entries<linktail>
        or <linkto>tcpC0.htm<linkmid>Get_IPv6_Iface_Entries<linktail>.<nl>

 @Also  tcpIPR.htm | Get_IPConfig |
        tcpPCIp.htm | PPP_Client_GetIP | |
 @Also  tcp8D.htm | Get_Iface_Entries |
        tcpC0.htm | Get_IPv6_Iface_Entries | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x50<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
void PPP_Server_GetIP (char far *IP)
{
    _DX = FP_OFF(IP);
    _ES = FP_SEG(IP);
    _AH = 0x50;
    asm { int BIOS_VECT  } ;
}
#endif





/*************************************************************************/
//PPP Client IP
/*************************************************************************/
#ifdef _tcpPCIp_
/*
 @doc DOC_tcpPCIp_
 ---------------------------------------------------------------
 Reads the IP Address of the PPP Client
 ---------------------------------------------------------------
 @clib  PPP_Client_GetIP | Reads the IP Address of the PPP Client |
        <cfont>void PPP_Client_GetIP ( const char far *IP );<efont> |
 @parm int  | IP  | Output parameter:<s2> Pointer to a 16 byte
        memory area where the IPv4 address is to be stored as a null
        terminated string.
 @rdesc -- none --
 @comm   Copies the current IPv4 address of the PPP Client into the provided
        string.<s2> If no IP address of the PPP Client is available, the string
        will be empty.<nl>
 @commtarget SC1x3/SC2x |
        <bold>This function is deprecated,<bolde> because it does not work if the
        PPP server uses the IPv6 protocol.<s2> The IP configuration of
        all TCP/IP devices can be read using either
         <linkto>tcp8D.htm<linkmid>Get_Iface_Entries<linktail>
        or <linkto>tcpC0.htm<linkmid>Get_IPv6_Iface_Entries<linktail>.<nl>
 @Also  tcpIPR.htm | Get_IPConfig |
        tcpPSIp.htm | PPP_Server_GetIP | |
 @Also  tcp8D.htm | Get_Iface_Entries |
        tcpC0.htm | Get_IPv6_Iface_Entries | |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x55<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void PPP_Client_GetIP (const char far *IP)
{
    _DX = FP_OFF(IP);
    _ES = FP_SEG(IP);
    _AH = 0x55;
    asm { int BIOS_VECT  } ;
}
#endif


/*****************************************************************************
*
*  open a tcp connection
*
*  DestIPStr: destination IP address format xxx.xxx.xxx.xxx
*  ClientPort: local port (0=random port)
*  HostPort: remote port
*  error: TCP/IP error
*
*
*  return: socket descriptor (-1 = error)
*/

#ifdef _tcpcon_
/*
 @doc DOC_tcpcon_
 ---------------------------------------------------------------
 open a tcp connection
 ---------------------------------------------------------------
 @clib  tcp_connect | Open a client TCP/IP socket connection to a specified
        host. |
        <cfont>int tcp_connect ( const char far *DestIPStr,<nl>
        <tab><tab><tab><tab>&nbsp; unsigned int ClientPort,<nl>
        <tab><tab><tab><tab>&nbsp; unsigned int HostPort,<nl>
        <tab><tab><tab><tab>&nbsp; int *error );<efont> |
 @parm  int  | DestIPStr  | Pointer to server's IPv4 address,
        expressed as a null terminated ASCII string in network dot notation.
 @parm  int  | ClientPort  | Optional local port number to assign to socket.<s2>
        Set this to zero if a bind operation is not desired (random port).
 @parm  int  | HostPort    | Remote port number to which connection is desired.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -1 = Failure (see <code>error<codee> output parameter) <nl>
        else new socket descriptor
 @comm This function calls the required set of TCP/IP functions
        to establish a IPv4 client connection to a host.<nl>
        <nl>
        Pseudo code:<nl>
        <nl>
        <code>
        struct sockaddr_in addr;<nl>
        int sd = opensocket(SOCK_STREAM, error) ;<nl>
        addr.sin_family = PF_INET ;<nl>
        addr.sin_addr.s_addr =  0 ;<nl>
        IF ClientPort != 0 THEN<nl>
        <tab>addr.sin_port = htons(ClientPort) ;<nl>
        <tab>bind(sd, &addr, error) ;<nl>
        ENDIF<nl>
        addr.sin_port = htons(HostPort) ;<nl>
        error = inet_addr(DestIPStr, &addr.sin_addr.s_addr) ;<nl>
        error = connect (sd, (const struct sockaddr *)&addr) ;<nl>
        return sd ;<nl>
        <codee><nl>
        <nl>
        The error handling is not shown in the above simplified pseudo code.<s2>
        In case of errors, the socket is closed by this API function and a return
        is made from the point of the error with return value -1.<s2>
        On success, the new socket descriptor is returned.<s2> The caller is then
        responsible for calling <linkto>tcp02.htm<linkmid>closesocket<linktail> when
        finished with the connection.
 @commtarget SC1x3/SC2x |
        The actual library function reached
        here is named <code>tcp_connect_ipstackV2<codee>.<s2> The name change
        occurs due to a macro in the library header file.

 @Also  tcp01.htm | opensocket  |
        htons.htm | htons  |
        tcp03.htm | bind
 @Also  tcp08.htm | inet_addr  |
        tcp04.htm | connect  |
        tcp02.htm | closesocket
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
#undef tcp_connect     // Maintain original name

    // This version is for original SC12 TCP/IP stack
int tcp_connect (const char far *DestIPStr,
                 unsigned int ClientPort,
                 unsigned int HostPort,
                 int *error)
{
    int local_error;
    // sd = socket descriptor, open socket
    int sd = opensocket (SOCK_STREAM, &local_error) ;
    if (local_error == 0)                       // Open successful?
    {
        struct sockaddr_in_ipstack addr;

        addr.sin_family = PF_INET ;
        addr.sin_addr.s_addr =  0 ;
        if (ClientPort != 0)
        {   // force client port
            addr.sin_port = HTONS(ClientPort);  // convert byte order
            bind (sd, (const struct sockaddr *)&addr, &local_error ) ;
        }
        if (local_error == 0)                   // No bind failure?
        {
            addr.sin_port = HTONS(HostPort); // convert byte order
            // convert server IP address string to binary
            local_error = inet_addr (DestIPStr, &addr.sin_addr.s_addr);
            if (local_error == 0)               // Valid IP address?
            {
                // establish a connection to the server
                connect (sd, (const struct sockaddr *)&addr, &local_error) ;
            }
        }
        if (local_error)                        // Failure?
        {
            int discard_error ;
            closesocket (sd, &discard_error) ;  // Give up.
            sd = -1 ;
        }
    }
    *error = local_error ;                      // Set output parameter

    return sd ;
}  // tcp_connect()

#endif //tcpcon

#ifdef _tcpcone_
    // This version is for new TCP/IP version, used  at target sc123
int tcp_connect_ipstackV2(const char far *DestIPStr,
                          unsigned int ClientPort,
                          unsigned int HostPort,
                          int *error)
{
    int local_error;
    // sd = socket descriptor, open socket
    int sd = opensocket (SOCK_STREAM, &local_error) ;
    if (local_error == 0)                       // Open successful?
    {
        struct sockaddr_in_ipstackV2 addr;

        addr.sin_family = PF_INET ;
        addr.sin_addr.s_addr =  0 ;
        if (ClientPort != 0)
        {   // force client port
            addr.sin_port = HTONS(ClientPort);  // convert byte order
            bind (sd, (const struct sockaddr *)&addr, &local_error ) ;
        }
        if (local_error == 0)                   // No bind failure?
        {
            addr.sin_port = HTONS(HostPort); // convert byte order
            // convert server IP address string to binary
            local_error = inet_addr (DestIPStr, &addr.sin_addr.s_addr);
            if (local_error == 0)               // Valid IP address?
            {
                // establish a connection to the server
                connect (sd, (const struct sockaddr *)&addr, &local_error) ;
            }
        }
        if (local_error)                        // Failure?
        {
            int discard_error ;
            closesocket (sd, &discard_error) ;  // Give up.
            sd = -1 ;
        }
    }
    *error = local_error ;                      // Set output parameter

    return sd ;
}  // tcp_connect()
#endif  //tcpcon_e

/*************************************************************************/
// open socket
/*************************************************************************/
#ifdef _tcp01_
/*
 @doc DOC_tcp01_
 ---------------------------------------------------------------
 open socket
 ---------------------------------------------------------------
 @clib  opensocket | Open a socket. |
        <cfont>int opensocket ( unsigned char type, int *error );<efont> |
 @parm  int  | type  | SOCK_STREAM = 1 for TCP socket<nl>
        SOCK_DGRAM = 2 for UDP datagram socket.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -1: Failure (see <code>error<codee> output parameter)<nl>
        else socket descriptor
 @comm  Creates an endpoint for communication and returns a socket descriptor.
        This function provides functionality similar to the BSD 
        <code>socket()<codee> function.
 @commtarget SC1x3/SC2x |
        This function applies only to IPv4 sockets.<s2> Either the
        <linkto>tcpC3.htm<linkmid>opensocket_ext<linktail> legacy API 
        or the BSD compatible <linkto>bsd41.htm<linkmid>socket<linktail> API
        may be used to open IPv4 or IPv6 sockets.
 @Also  tcp02.htm | closesocket  |
        tcp03.htm | bind |
        tcp04.htm | connect
 @Also  tcpC3.htm | opensocket_ext  |
        bsd41.htm | socket  |
         |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x01<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int opensocket (unsigned char type, int *error)
{
    int sd ;
    int error_code = 0 ;
    _AL = type ;
    _AH = API_OPENSOCKET;
    asm { int TCPIPVECT  } ;
    sd = _AX ;
    if (_DX != 0)
    {
        error_code = sd ;       // Error code was returned in AX.
        sd = -1 ;
    }
    *error = error_code ;
    return sd ;
}
#endif


/*************************************************************************/
// close socket
/*************************************************************************/
#ifdef _tcp02_
/*
 @doc DOC_tcp02_
 ---------------------------------------------------------------
 close socket
 ---------------------------------------------------------------
 @clib  closesocket | Close a socket. |
        <cfont>int closesocket ( int sd, int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | error | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -1: Failure (see <code>error<codee> output parameter)<nl>
         0: success
 @comm  Closes the socket indicated by <code>sd<codee> and releases all of
        its associated resources.

 @commtarget SC1x3/SC2x |
    This legacy version of <i>closesocket()<ie> specified here is not compatible 
    to the BSD 4.4 Socket API.<s2> The <i>closesocket()<ie> function can be used
    in BSD 4.4 compatible mode if the compilation switch<nl>
    <nl><code>
        <tab> #define  BSD44_SOCKET_API_STYLE<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files.<s2> Using this switch the C-Library TCPIP_Socket.H include
    file redefines <i>closesocket()<ie> to 
    <linkto>bsd28.htm<linkmid>close_bsd()<linktail>.<s2>The parameters 
    to <i>close_bsd()<ie> are identical to the parameters of the BSD4.4
    socket <i>close()<ie> function.

 @Also tcp01.htm | opensocket  |
       tcpC3.htm | opensocket_ext |
       bsd28.htm | close_bsd

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x02<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int closesocket (int sd, int *error)
{
    _BX = sd ;
    _AH = API_CLOSESOCKET;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX ;
}
#endif

/*************************************************************************/
// bind
/*************************************************************************/
#ifdef _tcp03_
/*
 @doc DOC_tcp03_
 ---------------------------------------------------------------
 Bind socket
 ---------------------------------------------------------------
 @clib  bind | Bind an unnamed socket to an address and port number. |
        <cfont>int bind ( int sd,<nl>
        <tab><tab>&nbsp;&nbsp; const struct sockaddr far *addressPtr,<nl>
        <tab><tab>&nbsp;&nbsp; int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm int  | addressPtr  | Pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
         (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6, <i>SC1x3/SC2x only!<ie>) data structure preset by caller.

 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>

 @comm  It is only necessary to use the bind call in server applications.<s2>
        If you use the bind call in a client application, the client uses the
        given port number as its own source port address.<s2> Otherwise a random
        16-bit source port number will be used when no bind call is made.<nl>
        <nl>
        The caller must fill in the
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail> (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6, <i>SC1x3/SC2x only!<ie>) data structure at <code>addressPtr<codee> prior
          to making this API call.<s2>An example (IPv4) of how this
        can be done follows.<s2> This function's prototype uses a pointer to the
        generic type <code>sockaddr<codee> for its <code>addressPtr<codee> parameter,
        for compatibility between IPv4 and IPv6 protocols.<s2> The pointer to the
        <code>sockaddr_in<codee> (IPv4) or <code>sockaddr_in6<codee> (IPv6)
        data structure which
        is actually used should be cast to this type as shown below to avoid
        compiler warnings, "Suspicious pointer conversion".<nl>

        @raw
        // Example
        int ClientPort = 4000 ;
        struct sockaddr_in addr ;
        int error_code ;

        addr.sin_family = PF_INET ;
        addr.sin_addr.s_addr =  0 ;
        addr.sin_port = htons(ClientPort);   // convert byte order
        error_code = bind (sd, (const struct sockaddr *)&addr, &error_code) ;

 @commtarget SC1x3/SC2x |
    This legacy version of <i>bind()<ie> specified here is not compatible 
    to the BSD 4.4 Socket API.<s2> The <i>bind()<ie> function can be used
    in BSD 4.4 compatible mode if the compilation switch<nl>
    <nl><code>
    <tab> #define  BSD44_SOCKET_API_STYLE<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files.<s2> Using this switch the C-Library TCPIP_Socket.H include
    file redefines <i>bind()<ie> to 
    <linkto>bsd26.htm<linkmid>bind_bsd()<linktail>.<s2>The parameters 
    to <i>bind_bsd()<ie> are identical to the parameters of the BSD4.4 socket
    <i>bind()<ie> function.

 @Also  tcp01.htm | opensocket  |
        tcpC3.htm | opensocket_ext  |
        tcp0E.htm | listen
 @Also  bsd26.htm | bind_bsd     |
        |  |
        | 

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x03<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int bind (int sd, const struct sockaddr far * addressPtr, int *error)
{
    _DX = FP_SEG(addressPtr);
    _SI = FP_OFF(addressPtr);
    _BX = sd ;
    _AH = API_BIND;
    asm { int TCPIPVECT  } ;
    *error = _AX;
    return _DX ;
}
#endif

/*************************************************************************/
// connect
/*************************************************************************/
#ifdef _tcp04_
/*
 @doc DOC_tcp04_
 ---------------------------------------------------------------
 Connect socket
 ---------------------------------------------------------------
 @clib  connect | Connect to another socket. |
        <cfont>int connect ( int sd,<nl>
        <tab><tab><tab>&nbsp; const struct sockaddr far *addressPtr,<nl>
        <tab><tab><tab>&nbsp; int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm int  | addressPtr  | Pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>  (IPv4) or
         <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
          (IPv6, <i>SC1x3/SC2x only!<ie>) data structure containing host's IP
          address and port number.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm   The caller must fill in the
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>  (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6, <i>SC1x3/SC2x only!<ie>) data structure at <code>addressPtr<codee>
         prior to calling here.<s2> An example of how
        this normally would be done follows.<s2> The PF_INET setting for the
        <code>sin_family<codee> is required for IPv4.<s2> For IPv6 set
        <code>sin6_family<codee> to PF_INET6.<nl>
        <nl>
        This function's prototype uses a pointer to the
        generic type <code>sockaddr<codee> for its <code>addressPtr<codee> parameter,
        for compatibility between IPv4 and IPv6 protocols.<s2> The pointer to the
        <code>sockaddr_in<codee> or <code>sockaddr_in6<codee> data structure which
        is actually used should be cast to this type as shown below to avoid
        compiler warnings, "Suspicious pointer conversion".<nl>
        Connect() in non-blocking mode:<nl>
        If the socket was switched into the non-blocking mode, the connect() procedure
        becomes internally started and  the connect() function will return immediateley with
        the current status at the <code>error<codee> output parameter.
        In that case connect() must be called in a loop like shown below.


        @raw
        // ******  Example  for connect with socket in blocking mode  **********
        char szHostIPStr[] = "172.30.1.68" ;
        int HostPort = 4000 ;
        struct sockaddr_in addr ;
        int result,error_code ;

        addr.sin_family = PF_INET ;
        addr.sin_addr.s_addr =  0 ;
        addr.sin_port = htons (HostPort) ;   // convert byte order

        // convert server IP address string to binary
        inet_addr (szHostIPStr, &addr.sin_addr.s_addr);
        // establish a connection to the server
        result = connect (sd, (const struct sockaddr far *)&addr,&error_code) ;

        // *********  Loop example for connect in non-blocking mode ************
        Set_Blocking_Mode ( sd, 0,&error_code );
        do
        {
           result= connect( sd, (const struct sockaddr far *)&addr, &error_code );
           if(result == 0)
           {
               break;
           }
           RTX_Sleep_Time(xxxxx);
           timeout+=xxxxx;
           if(timeout>MAX_CONNECT_TIMEOUT)
           {
              closesocket( sd, &error_code );
              return -1; //time exceeded
           }
        }while((error_code==236) || (error_code==237));
        if(error!=0)
        {
          //exit on other errors
          closesocket( sd, &error );
          return -1;
        }
        //error_code==0: success (even if result==-1!)


 @commtarget SC1x3/SC2x |
    This legacy version of <i>connect()<ie> specified here is not compatible
    to the BSD 4.4 Socket API.<s2> The <i>connect()<ie> function can be used
    in BSD 4.4 compatible mode if the compilation switch<nl>
    <nl><code>
    <tab> #define  BSD44_SOCKET_API_STYLE<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files.<s2> Using this switch the C-Library TCPIP_Socket.H include
    file redefines <i>connect()<ie> to 
    <linkto>bsd27.htm<linkmid>connect_bsd()<linktail>.<s2>The parameters 
    to <i>connect_bsd()<ie> are identical to the parameters of the BSD4.4 socket
    <i>connect()<ie> function.

 @Also  tcp01.htm | opensocket |
        tcpcon.htm | tcp_connect  |
        htons.htm | htons
 @Also  tcpc3.htm | opensocket_ext |
        tcp08.htm | inet_addr |
        tcp03.htm | bind
 @Also  bsd27.htm | connect_bsd     |
        |  |
        | 

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x04<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00


*/
int connect (int sd, const struct sockaddr far * addressPtr, int *error)
{
    _DX = FP_SEG(addressPtr);
    _SI = FP_OFF(addressPtr);
    _BX = sd ;
    _AH = API_CONNECT;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX ;
}
#endif


/*************************************************************************/
//recvfrom
/*************************************************************************/
#ifdef _tcp05_
/*
 @doc DOC_tcp05_
 ---------------------------------------------------------------
 UDP only, receive message from another socket
 ---------------------------------------------------------------
 @clib  recvfrom | Receive message from another socket. |
        <cfont>int recvfrom ( int sd, char far *bufptr, int bufLen,<nl>
        <tab><tab><tab>&nbsp;&nbsp; int flags, unsigned long timeout,<nl>
        <tab><tab><tab>&nbsp;&nbsp; struct sockaddr far *fromPtr,<nl>
        <tab><tab><tab>&nbsp;&nbsp; int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | bufptr  | Pointer to input buffer where received
        characters will be output.
 @parm  int  | bufLen  | Maximum characters to store in
        buffer at <code>bufptr<codee>.
 @parm  int  | flags  | Wait option:<nl>
        <ul>
        <li><bold>MSG_BLOCKING<bolde>  - Sleep until data comes in<nl>
        <li><bold>MSG_TIMEOUT<bolde>  - The caller wakes up after timeout or
           if <code>bufLen<codee> data bytes are received.<nl>
        <li><bold>MSG_PEEK<bolde>  - “Peek” at the data present on the socket.
                                      The data is returned, but not consumed,
                                      so that a subsequent receive operation
                                      will see the same data.<nl>
        <li><bold>MSG_DONTWAIT<bolde> - Return immediately after collecting
           what ever data is ready<nl>
        <ule>
 @parm  int  | timeout  | Maximum milliseconds to wait if <code>flags<codee> is set
        to MSG_TIMEOUT:<nl>
 @parm int  | fromPtr  | Output parameter:<s2>Pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
         (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6, <i>SC1x3/SC2x only!<ie>) data structure, which will be set
         to indicate from where the received data originated.<s2> This pointer
         can be set to NULL if this information is not desired.<nl>
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -1:  Failure, see error value reported<nl>
        otherwise: Count of bytes received and placed in <code>bufptr<codee><s2>
        (0 if time-out)
 @comm   This API function applies only to UDP sockets.<nl>
        <nl>
        The MSG_BLOCKING mode will not work if the socket has
        been put into non-blocking mode using the
        <linkto>tcp18.htm<linkmid>Set_Blocking_Mode<linktail> API.<nl>
        <nl>
 @comm  This function's prototype takes a pointer to the
        generic type <linkto>../../tcpstruc.htm#sockaddr<linkmid>sockaddr<linktail>
        for its <i>fromPtr<ie> parameter,
        for compatibility between IPv4 and IPv6 protocols.<s2> The pointer to the
        <code>sockaddr_in<codee>  (IPv4) or <code>sockaddr_in6<codee>
        (IPv6, <i>SC1x3/SC2x only!<ie>) data structure which
        is actually used should be cast to a <code>sockaddr<codee> type
        pointer to avoid compiler warnings, "Suspicious pointer conversion".<nl>
        <nl>

 @commtarget SC1x |
        recvfrom() can only return complete UDP datagrams at the user provided buffer.<s2>
        If the waiting datagram at the internal socket receive queue has size larger
        than the specified <cfont>bufLen<efont>,
        recvfrom returns with -1 and  error code 240
        ("Message too long") without writing the datagram into the user buffer.<s2>
        You can use <linkto>tcp0C.htm<linkmid>GetWaitingBytes<linktail>
        to detect the sum of bytes over all waiting datagrams at the internal receive queue
        of this socket.<nl>

 @commtarget SC1x3/SC2x |
        The actual library function reached
        here is named <code>recvfrom_ipstackV2<codee>.<s2> The name change
        occurs due to a macro in the library header file.<nl>
        <nl>
        If the waiting datagram at the internal socket receive queue has size larger
        than the specified <i>bufLen<ie>, <code>recvfrom()<codee> returns with -1 and
        error code 240 ("Message too long").<s2>
        The receive buffer contains the truncated datagram.<nl>
        <nl>
    This legacy version of <i>recvfrom()<ie> specified here is not compatible
    to the BSD 4.4 Socket API.<s2> The <i>recvfrom()<ie> function can be used
    in BSD 4.4 compatible mode if the compilation switch<nl>
    <nl><code>
       <tab> #define  BSD44_SOCKET_API_STYLE<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files.<s2> Using this switch the C-Library TCPIP_Socket.H include
    file redefines <i>recvfrom()<ie> to 
    <linkto>bsd33.htm<linkmid>recvfrom_bsd()<linktail>.<s2>The parameters 
    to <i>recvfrom_bsd()<ie> are identical to the parameters of the BSD4.4
    socket <i>recvfrom()<ie> function, except for the one additional 
    <code>timeout<codee> parameter which is suppressed by the <code>recvfrom()<codee>
    remapping macro by passing a zero for that parameter.<nl>
    <nl>
    The <i>recvfrom_bsd()<ie> method uses dynamical linking, so therefore 
    executes faster than this legacy API's sofware interrupt method.  The 
    compilation  switch<nl>
    <nl><code>
      <tab> #define  TCPIP_DYN_LINK_SOCK<nl>
    <codee><nl>
    may be defined in the user application prior to including the Beck C-Library
    header files to implement this legacy <i>recvfrom()<ie> method using 
    the faster <i>recvfrom_bsd()<ie> dynamic linked API.<nl>
    <nl>
    The first compilation switch takes precedence.<s2> This second compilation 
    option, <bold>TCPIP_DYN_LINK_SOCK<bolde> will be not affect this API
    when the first option (<bold>BSD44_SOCKET_API_STYLE<bolde>) is defined.


 @Also  tcp06.htm | sendto  |
        tcp01.htm | opensocket |
        tcp18.htm | Set_Blocking_Mode
 @Also  tcpC3.htm | opensocket_ext  |
        tcp1A.htm | select |
        tcp1Am.htm | select_ms
 @Also  tcp10.htm | recv  |
        bsd33.htm | recvfrom_bsd |
         |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x05<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
#undef recvfrom     // Maintain original name
                   // This version is for the new TCP/IP version, used  at target sc123
int recvfrom(int sd, char far * bufptr, int bufLen, int flags,
             unsigned long timeout,
             struct sockaddr far * fromPtr,
             int *error)
{
    int bytes_received ;
    int the_error_code = 0 ;
    int fromLen;
    struct recv_params R;



    //fill the struct recv_param R
    fromLen          =   sizeof(struct sockaddr_in_ipstack);
    R.bufferPtr      =   bufptr;
    R.bufferLength   =   bufLen;
    R.flags          =   flags;
    R.fromPtr        =   (struct sockaddr *)fromPtr;
    R.fromlengthPtr  =   &fromLen;
    R.timeout        =   timeout; /*milliseconds*/


    //API
    _BX = sd;
    _DX = FP_SEG(&R);
    _SI = FP_OFF(&R);
    _AH = API_RECVFROM;
    asm { int TCPIPVECT  } ;
    bytes_received = _AX ;
    if (_DX != 0)
    {
        the_error_code = bytes_received ;       // AX value
        bytes_received = API_ERROR ;
    }
    *error = the_error_code ;
    return bytes_received ;

}
#endif //#ifdef _tcp05_

#ifdef _tcp05e_
    // This version is for SC123 TCP/IP version supporting IPv6
int recvfrom_ipstackV2(int sd, char far * bufptr, int bufLen, int flags,
                       unsigned long timeout,
                       struct sockaddr far * fromPtr,
                       int *error)
{
    int bytes_received ;
    int the_error_code = 0 ;
    int fromLen   =   sizeof(struct sockaddr_in6);
    struct recv_params R;

    //fill the struct recv_param R

    // Note: If optional parameter fromPtr is NULL, then we do a harmless
    //     read from low memory here.
    if ( ((struct sockaddr_in_ipstackV2 far *)fromPtr)->sin_family == AF_INET)
    {
       fromLen          =   sizeof(struct sockaddr_in_ipstackV2);
    }
    R.bufferPtr      =   bufptr;
    R.bufferLength   =   bufLen;
    R.flags          =   flags;
    R.fromPtr        =   (struct sockaddr *)fromPtr;
    R.fromlengthPtr  =   &fromLen;
    R.timeout        =   timeout; /*milliseconds*/

    //API
    _BX = sd;
    _DX = FP_SEG(&R);
    _SI = FP_OFF(&R);
    _AH = API_RECVFROM;
    asm { int TCPIPVECT  } ;
    bytes_received = _AX ;
    if (_DX != 0)
    {
        the_error_code = bytes_received ;       // AX value
        bytes_received = API_ERROR ;
    }
    *error = the_error_code ;
    return bytes_received ;

}
#endif //#ifdef _tcp05e


/*************************************************************************/
//recvfromto
/*************************************************************************/
#ifdef _tcp27_
/*
 @doc DOC_tcp27_
 -----------------------------------------------------------------------------
 UDP only, receive message from another socket and store destination address
 -----------------------------------------------------------------------------
 @clib  recvfromto | Same as recvfrom, but returns the destination address |
        <cfont>int recvfromto ( int sd, char far *bufptr, int bufLen,<nl>
        <tab><tab><tab>&nbsp;&nbsp; int flags, unsigned long timeout,<nl>
        <tab><tab><tab>&nbsp;&nbsp; struct sockaddr far *fromPtr,<nl>
        <tab><tab><tab>&nbsp;&nbsp; struct sockaddr far *toPtr,<nl>
        <tab><tab><tab>&nbsp;&nbsp; int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | bufptr  | Pointer to input buffer where received
        characters will be output.
 @parm  int  | bufLen  | Maximum characters to store in
        buffer at <code>bufptr<codee>.
 @parm  int  | flags  | Wait option:<nl>
        <ul>
        <li><bold>MSG_BLOCKING<bolde>  - Sleep until data comes in<nl>
        <li><bold>MSG_TIMEOUT<bolde>  - The caller wakes up after timeout or
           if <code>bufLen<codee> data bytes are received.<nl>
        <li><bold>MSG_PEEK<bolde>  - “Peek” at the data present on the socket.
                                      The data is returned, but not consumed,
                                      so that a subsequent receive operation
                                      will see the same data.<nl>
        <li><bold>MSG_DONTWAIT<bolde> - Return immediately after collecting
           what ever data is ready<nl>
        <ule>
 @parm  int  | timeout  | Maximum milliseconds to wait if <code>flags<codee> is set
        to MSG_TIMEOUT:<nl>
 @parm int  | fromPtr  | Output parameter:<s2>Pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
         (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6, <i>SC1x3/SC2x only!<ie>) data structure, which will be set
         to indicate from where the received data originated.<s2> This pointer
         can be set to NULL if this information is not desired.<nl>

 @parm int  | toPtr  | Output parameter:<s2>Pointer to a user provided storage from type
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
         (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6, <i>SC1x3/SC2x only!<ie>) data structure, which will contain
         (after sucessful return) the destination address.<nl>

 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -1:  Failure, see error value reported<nl>
        otherwise: Count of bytes received and placed in <code>bufptr<codee><s2>
        (0 if time-out). Storage pointed by toPtr holds the destination address.<nl>
        occurs due to a macro in the library header file.

 @Also  tcp05.htm | recvfrom |
        tcp1A.htm | select |
        tcp1Am.htm | select_ms

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x27<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  | n/a   | n/a   | V1.07 | V1.00

*/
int recvfromto(int sd, char far * bufptr, int bufLen, int flags,
               unsigned long timeout,
               struct sockaddr far * fromPtr,
               struct sockaddr far * toPtr,
               int *error)
{
    int bytes_received ;
    int the_error_code = 0 ;
    int fromLen;
    struct recv_params R;

    //fill the struct recv_param R
    fromLen          =   sizeof(struct sockaddr_in_ipstack);
    R.bufferPtr      =   bufptr;
    R.bufferLength   =   bufLen;
    R.flags          =   flags;
    R.fromPtr        =   (struct sockaddr *)fromPtr;
    R.fromlengthPtr  =   &fromLen;
    R.timeout        =   timeout; /*milliseconds*/


    //API
    _BX = sd;
    _DX = FP_SEG(&R);
    _SI = FP_OFF(&R);
    _ES = FP_SEG(toPtr);
    _DI = FP_OFF(toPtr);
    _AH = API_RECVFROM_TO;
    asm { int TCPIPVECT  } ;
    bytes_received = _AX ;
    if (_DX != 0)
    {
        the_error_code = bytes_received ;       // AX value
        bytes_received = API_ERROR ;
    }
    *error = the_error_code ;
    return bytes_received ;

}
#endif //#ifdef _tcp27_


/*************************************************************************/
//recvfromto_iface
/*************************************************************************/
#ifdef _tcp29_
/*
 @doc DOC_tcp29_
 -----------------------------------------------------------------------------
 UDP only, receive message from another socket and store destination address
 and interface handle
 -----------------------------------------------------------------------------
 @clib  recvfromto_iface | Same as recvfromto, but returns also the interface handle
        over which the packet arrived and the physical address the packet was received from. |
        <cfont>int recvfromto_iface ( int sd, char far *bufptr, int bufLen,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp; int flags, unsigned long timeout,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp; struct sockaddr far *fromPtr,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp; struct sockaddr far *toPtr,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp; unsigned char far *fromPhyAddrPtr,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp; int far *fromPhyAddrLenPtr,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp; DevUserIfaceHandle * DevHandlePtr,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp; int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | bufptr  | Pointer to input buffer where received
        characters will be output.
 @parm  int  | bufLen  | Maximum characters to store in
        buffer at <code>bufptr<codee>.
 @parm  int  | flags  | Wait option:<nl>
        <ul>
        <li><bold>MSG_BLOCKING<bolde>  - Sleep until data comes in<nl>
        <li><bold>MSG_TIMEOUT<bolde>  - The caller wakes up after timeout or
           if <code>bufLen<codee> data bytes are received.<nl>
        <li><bold>MSG_PEEK<bolde>  - “Peek” at the data present on the socket.
                                      The data is returned, but not consumed,
                                      so that a subsequent receive operation
                                      will see the same data.<nl>
        <li><bold>MSG_DONTWAIT<bolde> - Return immediately after collecting
           what ever data is ready<nl>
        <ule>
 @parm  int  | timeout  | Maximum milliseconds to wait if <code>flags<codee> is set
        to MSG_TIMEOUT:<nl>
 @parm int  | fromPtr  | Output parameter:<s2>Pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
         (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6, <i>SC1x3/SC2x only!<ie>) data structure, which will be set
         to indicate from where the received data originated.<s2> This pointer
         can be set to NULL if this information is not desired.<nl>

 @parm int  | toPtr  | Output parameter:<s2>Pointer to a user provided storage from type
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
         (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6, <i>SC1x3/SC2x only!<ie>) data structure, which will contain
         (after sucessful return) the destination address.<nl>

 @parm  int  | fromPhyAddrPtr | Output parameter:<s2>Pointer to a buffer, which is
        used to store the physical address from which the data comes.

 @parm  int  | fromPhyAddrLenPtr | The value referenced by this pointer is both an input
        and output parameter, which should be preset to the size of the
        <code>fromPhyAddrPtr<codee>.
        Normally this would be 6 bytes to store the Ethernet MAC address.

 @parm  int  | DevHandlePtr  | Output parameter:<s2>This is the pointer to the
        interface handle on which the packet arrived.

 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.

 @rdesc -1:  Failure, see error value reported<nl>
        otherwise: Count of bytes received and placed in <code>bufptr<codee><s2>
        (0 if time-out). Storage pointed by toPtr holds the destination address.<nl>
        occurs due to a macro in the library header file.

 @Also  tcp27.htm | recvfromto |
        tcp28.htm | sendto_iface | |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x29<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  | n/a   | n/a   | V1.50 | V1.50
 @target_clib V2.22

*/
int recvfromto_iface(int sd, char far * bufptr, int bufLen, int flags,
               unsigned long timeout,
               struct sockaddr far * fromPtr,
               struct sockaddr far * toPtr,
               unsigned char far *fromPhyAddrPtr,
               int far *fromPhyAddrLenPtr,
               DevUserIfaceHandle * DevHandlePtr,
               int *error)
{
    int bytes_received ;
    int the_error_code = 0 ;
    int fromLen;
    struct recv_params2 R;

    //fill the struct recv_param R
    fromLen              =   sizeof(struct sockaddr_in_ipstack);
    R.bufferPtr          =   bufptr;
    R.bufferLength       =   bufLen;
    R.flags              =   flags;
    R.fromPtr            =   (struct sockaddr *)fromPtr;
    R.fromlengthPtr      =   &fromLen;
    R.timeout            =   timeout; /*milliseconds*/
    R.fromPhyAddrPtr     =   fromPhyAddrPtr;
    R.fromPhyAddrLenPtr  =   fromPhyAddrLenPtr;
    R.DevHandlePtr       =   DevHandlePtr;

    //API
    _BX = sd;
    _DX = FP_SEG(&R);
    _SI = FP_OFF(&R);
    _ES = FP_SEG(toPtr);
    _DI = FP_OFF(toPtr);
    _AH = API_RECVFROM_TO_IFACE;
    asm { int TCPIPVECT  } ;
    bytes_received = _AX ;
    if (_DX != 0)
    {
        the_error_code = bytes_received ;       // AX value
        bytes_received = API_ERROR ;
    }
    *error = the_error_code ;
    return bytes_received ;

}
#endif //#ifdef _tcp29_



/*************************************************************************/
//sendto
/*************************************************************************/
#ifdef _tcp06_
/*
 @doc DOC_tcp06_
 ---------------------------------------------------------------
 Transmit a datagram
 ---------------------------------------------------------------
 @clib  sendto | Transmit a datagram. |
        <cfont>int sendto ( int sd, const char far *bufptr, int bufLen,<nl>
        <tab><tab><tab> int flags, const struct sockaddr far *toPtr,<nl>
        <tab><tab><tab> int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | bufptr  | Pointer to output buffer containing
        characters to be transmitted.
 @parm  int  | bufLen  | Maximum characters to output from <code>bufptr<codee>.
 @parm  int  | flags  | Wait option:<nl>
        <ul>
        <li><bold>MSG_BLOCKING<bolde>  - Wait for data send to complete.<nl>
        <li><bold>MSG_DONTWAIT<bolde> - Don't wait for data send to complete.<nl>
        <ule>
 @parm  int  | toPtr  | Data destination, pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
         (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6, <i>SC1x3/SC2x only!<ie>) data structure.

 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -1:  Failure, see error value reported<nl>
        otherwise: Count of bytes transfered into the socket send queue.
 @comm  This API function applies only to UDP sockets.<s2>
        This function will output up to <i>bufLen<ie> bytes from the buffer
        at <i>bufptr<ie> to the IP address specified by the
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
        (IPv4) structure or
        the  <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
        (IPv6, <i>SC1x3/SC2x only!<ie>) structure referenced by the
        <i>toPtr<ie> parameter.<nl>
        <nl>
        This function's prototype takes a pointer to the
        generic type <linkto>../../tcpstruc.htm#sockaddr<linkmid>sockaddr<linktail> 
        for its <code>toPtr<codee> parameter, for compatibility between IPv4 and 
        IPv6 protocols.<s2> The pointer to the  <code>sockaddr_in<codee> (IPv4)
        or <code>sockaddr_in6<codee> (IPv6, <i>SC1x3/SC2x only!<ie>) data structure
        which is actually used should be cast to a <code>sockaddr<codee> type
        pointer to avoid compiler warnings, "Suspicious pointer conversion".<nl>
        <nl>
        The <bold>MSG_BLOCKING<bolde> mode will not work if the socket has
        been put into non-blocking mode using the
        <linkto>tcp18.htm<linkmid>Set_Blocking_Mode<linktail> API.<nl>
        <nl>
 @commtarget SC1x3/SC2x |
        The actual library function reached here is named
        <code>sendto_ipstackV2<codee> (when neither of the compilation 
        switches discussed below are used).<s2> The name change
        occurs due to a macro in the library header file.<nl>
        <nl>
    This legacy version of <i>sendto()<ie> specified here is not compatible 
    to the BSD 4.4 Socket API.<s2> The <i>sendto()<ie> function can be used
    in BSD 4.4 compatible mode if the compilation switch<nl>
    <nl><code>
       <tab> #define  BSD44_SOCKET_API_STYLE<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files.<s2> Using this switch the C-Library TCPIP_Socket.H include
    file redefines <i>sendto()<ie> to 
    <linkto>bsd35.htm<linkmid>sendto_bsd()<linktail>.<s2>The parameters 
    to <i>sendto_bsd()<ie> are identical to the parameters of the BSD4.4
    socket <i>sendto()<ie> function.<nl>
    <nl>
    The <i>sendto_bsd()<ie> method uses dynamical linking, so therefore 
    executes faster than this legacy API's sofware interrupt method.  The 
    compilation  switch<nl>
    <nl><code>
      <tab> #define  TCPIP_DYN_LINK_SOCK<nl>
    <codee><nl>
    may be defined in the user application prior to including the Beck C-Library
    header files to implement this legacy <i>sendto()<ie> method using 
    the faster <i>sendto_bsd()<ie> dynamic linked API.<nl>
    <nl>
    The first compilation switch takes precedence.<s2> This second compilation 
    option, <bold>TCPIP_DYN_LINK_SOCK<bolde> will be not affect this API
    when the first option (<bold>BSD44_SOCKET_API_STYLE<bolde>) is defined.


 @Also  tcp05.htm | recvfrom  |
        tcp01.htm | opensocket |
        tcp18.htm | Set_Blocking_Mode
 @Also  bsd35.htm | sendto_bsd  |
        tcp0F.htm | send |
        bsd35.htm | sendto_bsd


 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x06<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
#undef sendto     // Maintain original name

   // This version is for original SC12 TCP/IP stack
int sendto (int sd, const char far * bufptr, int bufLen, int flags,
            const struct sockaddr far * toPtr, int *error)
{
    int bytes_sent ;
    int the_error_code = 0 ;
    int toLen;
    struct send_params S;

    toLen = sizeof(struct sockaddr_in_ipstack);

    //Init the struct send_param S for API-Call

    S.bufferPtr      = bufptr;
    S.bufferLength   = bufLen;
    S.flags          = flags;
    S.toPtr          = (struct sockaddr *) toPtr;
    S.tolengthPtr    = &toLen;

    //API
    _BX = sd;
    _DX = FP_SEG(&S);
    _SI = FP_OFF(&S);
    _AH = API_SENDTO;
    asm { int TCPIPVECT  } ;
    bytes_sent = _AX ;
    if (_DX != 0)
    {
        the_error_code = bytes_sent ;       // AX value
        bytes_sent = API_ERROR ;
    }
    *error = the_error_code ;
    return bytes_sent ;
}
#endif

#ifdef _tcp06e_
// This version is for the new TCP/IP version, used  at target sc123
int sendto_ipstackV2(int sd, const char far * bufptr, int bufLen, int flags,
                      const struct sockaddr far * toPtr, int *error)
{
    int bytes_sent ;
    int the_error_code = 0 ;
    int toLen;
    struct send_params S;

    if ( ((struct sockaddr_in_ipstackV2 far *)toPtr)->sin_family == AF_INET)
    {
       toLen = sizeof(struct sockaddr_in_ipstackV2);
    }
    else
    {
       toLen = sizeof(struct sockaddr_in6);
    }

    //Init the struct send_param S for API-Call
    S.bufferPtr      = bufptr;
    S.bufferLength   = bufLen;
    S.flags          = flags;
    S.toPtr          = (struct sockaddr *) toPtr;
    S.tolengthPtr    = &toLen;

    //API
    _BX = sd;
    _DX = FP_SEG(&S);
    _SI = FP_OFF(&S);
    _AH = API_SENDTO;
    asm { int TCPIPVECT  } ;
    bytes_sent = _AX ;
    if (_DX != 0)
    {
        the_error_code = bytes_sent ;       // AX value
        bytes_sent = API_ERROR ;
    }
    *error = the_error_code ;
    return bytes_sent ;
}
#endif  //#ifdef _tcp06e


/*************************************************************************/
// inet_addr
/*************************************************************************/
#ifdef _tcp08_
/*
 @doc DOC_tcp08_
 ---------------------------------------------------------------
 Converts a dotted decimal IP address string to an unsigned long
 ---------------------------------------------------------------
 @clib  inet_addr | Converts a dotted decimal IP address string to an unsigned long. |
        <cfont>int inet_addr ( const char far *IPAddressStringPtr,<nl>
        <tab><tab><tab><tab>unsigned long far *IPAddress );<efont> |
 @parm  int  | IPAddressStringPtr  | Pointer to null terminated
        ASCII string of network address in dot notation.
 @parm  int  | IPAddress  | Output parameter:<s2>Pointer to a
        32 bit location where binary equivalent to the provided ASCII
        IP address will be output.  This IP address is stored in network
        byte order.
 @rdesc 0:  success <nl>
        non-zero:  Invalid IP address.

 @commtarget SC1x3/SC2x |
        This function applies only to IPv4 addresses.<s2> The
        <linkto>tcpC1.htm<linkmid>inet_pton<linktail> API can be used
        for either IPv4 or IPv6 address conversions.<nl>
        <nl>
    This legacy version of <i>inet_addr()<ie> specified here is not compatible 
    to the BSD 4.4 Socket API.<s2> The <i>inet_addr()<ie> function can be used
    in BSD 4.4 compatible mode if the compilation switch<nl>
    <nl><code>
    <tab> #define  BSD44_SOCKET_API_STYLE<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files.<s2> Using this switch the C-Library TCPIP_Socket.H include
    file redefines <i>inet_addr()<ie> to 
    <linkto>bsd30.htm<linkmid>inet_addr_bsd()<linktail>.<s2>The parameters 
    to <i>inet_addr_bsd()<ie> are identical to the parameters of the BSD4.4
    socket <i>inet_addr()<ie> function.

 @Also  tcpcon.htm | tcp_connect |
        tcp11.htm | InetToAscii |
        tcpC1.htm | inet_pton
 @Also  bsd30.htm | inet_addr_bsd |
        |  |
        |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x08<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int inet_addr (const char far * IPAddressStringPtr,
               unsigned long far * IPAddress)
{
    _BX = FP_SEG(IPAddressStringPtr);
    _SI = FP_OFF(IPAddressStringPtr);
    _ES = FP_SEG(IPAddress);
    _DI = FP_OFF(IPAddress);

    _AH = API_INETADDR;
    asm { int TCPIPVECT  } ;
    return _DX ;
}
#endif

/*************************************************************************/
//sleep
/*************************************************************************/
#ifdef _tcp09_
/*
 @doc DOC_tcp09_
 ---------------------------------------------------------------
 The application sleeps for given number of milliseconds
 ---------------------------------------------------------------
 @clib  api_sleep | The calling task sleeps for specified
        number of milliseconds. |
        <cfont>void api_sleep ( unsigned int howlong );<efont> |
 @depr  ../RTX/rtx00.htm | RTX_Sleep_Time
 @parm  int  | howlong  | Sleep period in milliseconds
 @rdesc -- none --
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x09<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
void api_sleep (unsigned int howlong)
{
    _BX = howlong ;
    _AH = API_SLEEP ;
    asm { int TCPIPVECT  } ;
}
#endif


/*************************************************************************/
//get waiting bytes
/*************************************************************************/
#ifdef _tcp0C_
/*
 @doc DOC_tcp0C_
 ---------------------------------------------------------------
 Get the number of bytes on a socket, waiting for read
 ---------------------------------------------------------------
 @clib  GetWaitingBytes | Report the number of bytes available
        on a socket, waiting to be read. |
        <cfont>int GetWaitingBytes ( int sd, int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -1 on failure, see error reported<nl>
        else count of received bytes waiting on socket.

 @comm  If the specified socket is an UDP socket, GetWaitingBytes() will return
        the sum of bytes over all waiting datagrams at the internal socket
        receive queue.

 @Also  tcp10.htm | recv  |
        tcp05.htm | recvfrom |
        tcp01.htm | opensocket


 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x0C<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int GetWaitingBytes (int sd, int *error)
{
    int bytes_ready ;
    int the_error_code = 0 ;

    _BX = sd ;
    _AH = API_GETRCV_BYTES ;
    asm { int TCPIPVECT  } ;
    bytes_ready = _AX ;
    if (_DX != 0)
    {
        the_error_code = bytes_ready ;
        bytes_ready = API_ERROR ;
    }

    *error = the_error_code ;
    return bytes_ready ;
}
#endif

/*************************************************************************/
//accept
/*************************************************************************/
#ifdef _tcp0D_
/*
 @doc DOC_tcp0D_
 ---------------------------------------------------------------
 accept the next incoming connection
 ---------------------------------------------------------------
 @clib  accept | Accept the next incoming connection. |
        <cfont>int accept ( int sd,<nl>
        <tab><tab><tab> struct sockaddr far *addressPtr,<nl>
        <tab><tab><tab> int *error );<efont> |
 @parm  int  | sd  | Socket descriptor (must be switched into
        listen mode using <linkto>tcp0E.htm<linkmid>listen<linktail> API).
 @parm int  | addressPtr  | Optional output parameter:<s2>Pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>  (IPv4)
        or  <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6 <linktail>
         (IPv6, <i>SC1x3/SC2x only!<ie>) data structure.<s2>
        On success, this function fills in this sockaddr_in or sockaddr_in6 structure with the
        IP address and port number of the accepted connection.<s2>
        This pointer can be set to NULL if this address and port number report is not desired.

 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -1: Failure, error code output to <code>error<codee><nl>
        otherwise: New socket descriptor for the connection
 @comm  This call is used by a TCP server.<nl>
        <nl>
        This API function extracts the first connection on the queue
        of pending connections.<s2>  It then creates
        a new socket for this connection.<s2> This new socket will have
        the same socket options as the listening socket, <code>sd.<codee><s2>
        On success, the handle to this new socket is returned.<nl>
        <nl>
        This function's prototype uses a pointer to the
        generic type <code>sockaddr<codee> for its <code>addressPtr<codee> parameter,
        for compatibility between IPv4 and IPv6 protocols.<s2> The pointer to the
        <code>sockaddr_in<codee>  (IPv4) or <code>sockaddr_in6<codee>
        (IPv6, <i>SC1x3/SC2x only!<ie>) data structure which
        is actually used should be cast to <code>sockaddr<codee> pointer type here
        to avoid compiler warnings, "Suspicious pointer conversion".<nl>

 @commtarget SC1x3/SC2x |
    This legacy version of <i>accept()<ie> specified here is not compatible 
    to the BSD 4.4 Socket API.<s2> The <i>accept()<ie> function can be used
    in BSD 4.4 compatible mode if the compilation switch<nl>
    <nl><code>
    <tab> #define  BSD44_SOCKET_API_STYLE<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files.<s2> Using this switch the C-Library TCPIP_Socket.H include
    file redefines <i>accept()<ie> to 
    <linkto>bsd25.htm<linkmid>accept_bsd()<linktail>.<s2>The parameters 
    to <i>accept_bsd()<ie> are identical to the parameters of the BSD4.4 socket
    <i>accept()<ie> function.

 @Also  tcp0E.htm | listen     |
        tcp01.htm | opensocket |
        tcpC3.htm | opensocket_ext
 @Also  bsd25.htm | accept_bsd     |
        |  |
        | 
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x0D<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int accept (int sd,
            struct sockaddr far * addressPtr,
            int *error)
{
    int sd_accepted ;
    int the_error_code = 0 ;

    _BX = sd ;
    _DX = FP_SEG(addressPtr);
    _SI = FP_OFF(addressPtr);

    _AH = API_ACCEPT ;
    asm { int TCPIPVECT  } ;
    sd_accepted = _AX ;
    if (_DX != 0)
    {
        the_error_code = sd_accepted ;
        sd_accepted = API_ERROR ;
    }

    *error = the_error_code ;
    return sd_accepted ;
}
#endif


/*************************************************************************/
//listen
/*************************************************************************/
#ifdef _tcp0E_
/*
 @doc DOC_tcp0E_
 ---------------------------------------------------------------
 Listen for incoming connections
 ---------------------------------------------------------------
 @clib  listen | Listen for incoming connections. |
        <cfont>int listen ( int sd, int backlog, int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | backlog  | The maximum number (limited to 5) of allowed
        outstanding connections
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm  This API function places the socket in passive mode and sets the
        number of incoming TCP connections that the system will queue
        (<code>backlog<codee>).<nl>
        <nl>
        This call is used by a TCP server.

 @commtarget SC1x3/SC2x |
    This legacy version of <i>listen()<ie> specified here is not compatible 
    to the BSD 4.4 Socket API.<s2> The <i>listen()<ie> function can be used
    in BSD 4.4 compatible mode if the compilation switch<nl>
    <nl><code>
    <tab> #define  BSD44_SOCKET_API_STYLE<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files.<s2> Using this switch the C-Library TCPIP_Socket.H include
    file redefines <i>listen()<ie> to 
    <linkto>bsd31.htm<linkmid>listen_bsd()<linktail>.<s2>The parameters 
    to <i>listen_bsd()<ie> are identical to the parameters of the BSD4.4 socket
    <i>listen()<ie> function.

 @Also  tcp0D.htm | accept  |
        tcp01.htm | opensocket |
        tcpC3.htm | opensocket_ext
 @Also  bsd31.htm | listen_bsd  |
        | | 
        |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x0E<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int listen (int sd, int backlog, int * error)
{
    _BX = sd ;
    _CX = backlog ;

    _AH = API_LISTEN ;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX;
}
#endif


/*************************************************************************/
//send
/*************************************************************************/
#ifdef _tcp0F_
/*
 @doc DOC_tcp0F_
 ---------------------------------------------------------------
 Transmit a message
 ---------------------------------------------------------------
 @clib  send | Transmit a message. |
        <cfont>int send ( int sd, const char far *bufptr, int bufLen,<nl>
        <tab><tab>&nbsp;&nbsp; int flags, int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | bufptr  | Pointer to output buffer containing
        data to be transmitted.
 @parm  int  | bufLen  | Maximum characters to output from <i>bufptr<ie>.
 @parm  int  | flags  | Wait option:<nl>
        <ul>
        <li><bold>MSG_BLOCKING<bolde>  - Wait for data send
        to complete.<nl>
        <li><bold>MSG_DONTWAIT<bolde> - Don't wait for data
        send to complete.<nl>
        <ule>
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -1:  Failure, see error value reported<nl>
        otherwise: Count of bytes transfered into the socket send queue
 @comm  This API function applies only to TCP sockets.<s2>
        It transmits a message to another transport end-point.<s2>
        It may be used only if the socket is in a
        connected state.<nl>
        <nl>
        The MSG_BLOCKING mode will not work if the socket has
        been put into non-blocking mode using the
        <linkto>tcp18.htm<linkmid>Set_Blocking_Mode<linktail> API.

 @commtarget SC1x3/SC2x |
    This legacy version of <i>send()<ie> specified here is not compatible 
    to the BSD 4.4 Socket API.<s2> The<nl> <i>send()<ie> function can be used
    in BSD 4.4 compatible mode if the compilation switch<nl>
    <nl><code>
    <tab> #define  BSD44_SOCKET_API_STYLE<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files.<s2> Using this switch the C-Library TCPIP_Socket.H include
    file redefines <i>send()<ie> to 
    <linkto>bsd34.htm<linkmid>send_bsd()<linktail>.<s2>The parameters 
    to <i>send_bsd()<ie> are identical to the parameters of the BSD4.4 socket
    <i>send()<ie> function.<nl>
    <nl>
    The <i>send_bsd()<ie> method uses dynamical linking, so therefore executes
    faster than this legacy API's sofware interrupt method.  The compilation 
    switch<nl>
    <nl><code>
    <tab> #define  TCPIP_DYN_LINK_SOCK<nl>
    <codee><nl>
    may be defined in the user application prior to including the Beck C-Library
    header files to implement this legacy <i>send()<ie> method using 
    the faster <i>send_bsd()<ie> dynamic linked API.<nl>
    <nl>
    The first compilation switch takes precedence.<s2> This second compilation 
    option, <bold>TCPIP_DYN_LINK_SOCK<bolde> will be not affect this API
    when the first option (<bold>BSD44_SOCKET_API_STYLE<bolde>) is defined.

 @Also  tcp10.htm | recv  |
        tcp06.htm | sendto |
        tcp01.htm | opensocket
 @Also  tcp18.htm | Set_Blocking_Mode  |
        tcp06.htm | sendto |
        bsd34.htm | send_bsd

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x0F<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int send(int sd, const char far * bufptr, int bufLen,
         int flags, int *error)
{
    int bytes_sent ;
    int the_error_code = 0 ;

    //Init the struct send_param S for API-Call
    struct send_params S;
    S.bufferPtr      = bufptr;
    S.bufferLength   = bufLen;
    S.flags          = flags;
    S.toPtr          = NULL ;
    S.tolengthPtr    = NULL ;

    //API
    _BX = sd;
    _DX = FP_SEG(&S);
    _SI = FP_OFF(&S);
    _AH = API_SEND;
    asm { int TCPIPVECT  } ;
    bytes_sent = _AX ;
    if (_DX != 0)
    {
        the_error_code = bytes_sent ;       // AX value
        bytes_sent = API_ERROR ;
    }
    *error = the_error_code ;
    return bytes_sent ;
}
#endif


/*************************************************************************/
//recv
/*************************************************************************/
#ifdef _tcp10_
/*
 @doc DOC_tcp10_
 ---------------------------------------------------------------
 Receive a message
 ---------------------------------------------------------------
 @clib  recv | Receive a message from another socket. |
        <cfont>int recv ( int sd, char far *bufptr, int bufLen,<nl>
        <tab><tab>&nbsp;&nbsp; int flags, unsigned long timeout,<nl>
        <tab><tab>&nbsp;&nbsp; int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | bufptr  | Output parameter:<s2> Pointer to input buffer
        where received characters will be stored.
 @parm  int  | bufLen  | Maximum characters to store in
        buffer at <code>bufptr<codee>.
 @parm  int  | flags  | Wait option:<nl>
         <ul>
        <li><bold>MSG_BLOCKING<bolde>  - Sleep until data comes in.<nl>
        <li><bold>MSG_TIMEOUT<bolde>  - The caller wakes up after timeout
        or if any data is received.<nl>
        <li><bold>MSG_PEEK<bolde>  - “Peek” at the data present on the socket.
                                      The data is returned, but not consumed,
                                      so that a subsequent receive operation
                                      will see the same data.<nl>
        <li><bold>MSG_DONTWAIT<bolde> - Return immediately after collecting what
        ever data is ready.<nl>
        <ule>
 @parm  int  | timeout  | Maximum milliseconds to wait if <code>flags<codee> is set
        to MSG_TIMEOUT<nl>
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -1:  Failure, see error value reported<nl>
        otherwise: Count of received bytes stored in buffer at <code>bufptr<codee>
 @comm  This API function applies only to TCP sockets.<s2>
        It receives a message from another socket.<s2>
        This API function may be used only if the socket is in a
        connected state.<nl>
        <nl>
        If <code>flags<codee> parameter is set to MSG_DONTWAIT, this API call returns
        immediately.<s2>If no data is available -1 is returned and output parameter
        <code>error<codee> is set to 235.<nl>
        <nl>If <code>flags<codee> parameter is set to MSG_BLOCKING, the <code>recv<codee>
        call waits for either a message to arrive or a socket error condition to occur
        (such as connection lost or socket closed).<s2>
        By default the blocking mode is set for all sockets at the
        <linkto>tcp01.htm<linkmid>opensocket<linktail> call.<s2> If however
        the socket was subsequently set to non-blocking mode with the
        <linkto>tcp18.htm<linkmid>Set_Blocking_Mode<linktail> API, the MSG_BLOCKING flag
        will then not work here.
 @commtarget SC1x3/SC2x |
    This legacy version of <i>recv()<ie> specified here is not compatible 
    to the BSD 4.4 Socket API.<s2> The <i>recv()<ie> function can be used
    in BSD 4.4 compatible mode if the compilation switch<nl>
    <nl><code>
    <tab> #define  BSD44_SOCKET_API_STYLE<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files.<s2> Using this switch the C-Library TCPIP_Socket.H include
    file redefines <i>recv()<ie> to 
    <linkto>bsd32.htm<linkmid>recv_bsd()<linktail>.<s2>The parameters 
    to <i>recv_bsd()<ie> are identical to the parameters of the BSD4.4 socket
    <i>recv()<ie> function, except for the one additional 
    <code>timeout<codee> parameter which is suppressed by the <code>recv()<codee>
    remapping macro by passing a zero for that parameter.<nl>
    <nl>
    The <i>recv_bsd()<ie> method uses dynamical linking, so therefore executes
    faster than this legacy API's sofware interrupt method.  The compilation 
    switch<nl>
    <nl><code>
    <tab> #define  TCPIP_DYN_LINK_SOCK<nl>
    <codee><nl>
    may be defined in the user application prior to including the Beck C-Library
    header files to implement this legacy <i>recv()<ie> method using 
    the faster <i>recv_bsd()<ie> dynamic linked API.<nl>
    <nl>
    The first compilation switch takes precedence.<s2> This second compilation 
    option, <bold>TCPIP_DYN_LINK_SOCK<bolde> will be not affect this API
    when the first option (<bold>BSD44_SOCKET_API_STYLE<bolde>) is defined.

 @Also  tcp0F.htm | send  |
        tcp05.htm | recvfrom |
        tcp01.htm | opensocket
 @Also  tcp18.htm | Set_Blocking_Mode |
        tcp1A.htm  | select |
        tcp1Am.htm | select_ms
 @Also  bsd32.htm | recv_bsd |
         |  |
         |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x10<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int recv (int sd, char far * bufptr, int bufLen, int flags,
          unsigned long timeout, int *error)
{
    int bytes_received ;
    int the_error_code = 0 ;
    struct recv_params R;

    //fill the struct recv_param R
    R.bufferPtr      =   bufptr;
    R.bufferLength   =   bufLen;
    R.flags          =   flags;
    R.fromPtr        =   NULL ;
    R.fromlengthPtr  =   NULL ;
    R.timeout        =   timeout; /*milliseconds*/

    //API
    _BX = sd;
    _DX = FP_SEG(&R);
    _SI = FP_OFF(&R);
    _AH = API_RECV ;
    asm { int TCPIPVECT  } ;
    bytes_received = _AX ;
    if (_DX != 0)
    {
        the_error_code = bytes_received ;       // AX value
        bytes_received = API_ERROR ;
    }
    *error = the_error_code ;
    return bytes_received ;
}
#endif

/*************************************************************************/
// InetToAscii
/*************************************************************************/
#ifdef _tcp11_
/*
 @doc DOC_tcp11_
 ---------------------------------------------------------------
 Convert an IP address to an IP string
 ---------------------------------------------------------------
 @clib  InetToAscii | Convert an IP address to an ASCII dotted decimal
        IP  string. |
        <cfont>int InetToAscii ( const unsigned long far *IPAddress,<nl>
        <tab><tab><tab><tab>&nbsp; char far *IPAddressStringPtr );<efont> |
 @parm  int  | IPAddress  | Pointer to the 32 bit IP address in
        network byte order ("big endian").
 @parm  int  | IPAddressStringPtr  | Output parameter:<s2>
        Pointer to a <bold>16 character buffer<bolde> (minimum)
        where a null terminated ASCII string
        will be written by this API function containing the
        IP address expressed in dotted decimal notation.
 @rdesc Always 0
 @comm  This buffer at <code>IPAddressStringPtr<codee> must have
        space for 16 Bytes!.
 @commtarget SC1x3/SC2x |
        This function applies only to IPv4 addresses.<s2> The
        <linkto>tcpC2.htm<linkmid>inet_ntop<linktail> API can be used
        for either IPv4 or IPv6 address conversions.
 @Also  tcp08.htm | inet_addr |
        tcpC2.htm | inet_ntop | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x11<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int InetToAscii (const unsigned long far * IPAddress,
                 char far * IPAddressStringPtr)
{
    _BX = FP_SEG(IPAddress) ;
    _SI = FP_OFF(IPAddress) ;
    _ES = FP_SEG(IPAddressStringPtr) ;
    _DI = FP_OFF(IPAddressStringPtr) ;

    _AH = API_INETTOASCII ;
    asm { int TCPIPVECT  } ;
    return 0;
}
#endif


/*************************************************************************/
//reset connection
/*************************************************************************/
#ifdef _tcp12_
/*
 @doc DOC_tcp12_
 ---------------------------------------------------------------
 Abort a connection on a socket
 ---------------------------------------------------------------
 @clib  ResetConnection | Abort a connection on a TCP socket. |
        <cfont>int ResetConnection ( int sd, int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm  This function only works on TCP sockets andis used to abort a connection on a socket.
        It sends a RST and discards all outstanding data.<s2>
        <nl><nl>
        A reset socket cannot be used for a new connection.<nl>
        The socket is not closed.<s2> This must be done
        using the <linkto>tcp02.htm<linkmid>closesocket<linktail> API.<nl>

 @Also  tcp02.htm | closesocket |
        tcp01.htm | opensocket  |
        tcpC3.htm | opensocket_ext
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x12<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int ResetConnection (int sd, int * error)
{
    _BX = sd ;

    _AH = API_RESETCONNECTION ;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX ;                    // AX = 0, unless error code
}
#endif



/*************************************************************************/
// set linger time on close
/*************************************************************************/
#ifdef _tcp13_
/*
 @doc DOC_tcp13_
 ---------------------------------------------------------------
 Set linger time on close
 ---------------------------------------------------------------
 @clib  setlinger | Set linger time on close (TCP only). |
        <cfont>int setlinger ( int sd, int seconds, int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | seconds  | Linger time in seconds, default: 20 sec,
        0 means linger turned off.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm  This API function works only with TCP sockets.
 @Also  tcp01.htm | opensocket |
        tcpC3.htm | opensocket_ext  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x13<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int setlinger (int sd, int seconds, int *error)
{
    _BX = sd ;
    _CX = seconds ;

    _AH = API_SETLINGER ;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX ;
}
#endif

/*************************************************************************/
// set resuse option on a listening socket
/*************************************************************************/
#ifdef _tcp14_
/*
 @doc DOC_tcp14_
 ---------------------------------------------------------------
 Set reuse option on a listening socket
 ---------------------------------------------------------------
 @clib  setreuse | Set reuse option on a listening socket. |
        <cfont>int setreuse ( int sd, int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm  This API function works only with TCP sockets.<s2>
        In earlier SC12 @CHIP-RTOS versions, this API was necessary when
        a listening socket was closed and was to be re-opened and bound to
        the same port as it was bound to before.<nl>
        <nl>
        Since SC12 @CHIP-RTOS 071, every TCP socket is set by default as
        reusable so use of this API function is no longer necessary.
 @Also  tcp01.htm | opensocket |
        tcp03.htm | bind | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x14<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int setreuse (int sd, int *error)
{
    _BX = sd ;

    _AH = API_SETREUSE ;
    asm { int TCPIPVECT  } ;
    *error = _AX;
    return _DX;
}
#endif

/*************************************************************************/
// Set IP Type-Of-Service on a socket
/*************************************************************************/
#ifdef _tcp15_
/*
 @doc DOC_tcp15_
 ---------------------------------------------------------------
 Set socket's Type-Of-Service
 ---------------------------------------------------------------
 @clib  Set_IP_Type_Of_Service | Set socket's default Type-Of-Service
        put into the IP datagram header's TOS field. |
        <cfont>int Set_IP_Type_Of_Service ( int sd,<nl>
        <tab><tab><tab><tab><tab><tab><tab> unsigned char tos,<nl>
        <tab><tab><tab><tab><tab><tab><tab> int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | tos  | Type-Of-Service for IP datagrams
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm  Bits in the IP Type-Of-Service field of a IP datagram:<nl>
        <ul>
        Bits 0-2: Datagram precedence, 7 is the highest.<nl>
        Bits 3-5: type of transport, see TCP/IP documentation e.g.<nl>
        <tab><tab>Internet networking with TCP/IP by Douglas E.Comer<nl>
        Bits 6-7: unused<nl>
        <ule><nl>
        Note:<s2> Many routers ignore this IP datagram header field.<nl>
 @Also  tcp01.htm | opensocket | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x15<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Set_IP_Type_Of_Service (int sd, unsigned char tos, int *error)
{
    _BX = sd ;

    _AL = tos ;
    _AH = API_SETIPTOS ;
    asm { int TCPIPVECT  } ;
    *error = _AX;
    return _DX ;
}
#endif

/*************************************************************************/
// set socket option
/*************************************************************************/
#ifdef _tcp16_
/*
 @doc DOC_tcp16_
 ---------------------------------------------------------------
 Set options on a socket
 ---------------------------------------------------------------
 @clib  setsockopt | Set options on a socket. |
        <cfont>int setsockopt ( int sd,<nl>
        <tab><tab><tab><tab> const SetSocketOption far *sockoptptr,<nl>
        <tab><tab><tab><tab> int *error);<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | sockoptptr  | Pointer to SetSocketOption
        <linkto>../../tcpstruc.htm#SetSocketOption<linkmid>type<linktail> that
        specifies the socket options (see tcpipapi.h).
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm  This API function makes it possible to manipulate options associated
        with a socket.<s2>Prior to calling this function the caller must fill in
        a SetSocketOption
        <linkto>../../tcpstruc.htm#SetSocketOption<linkmid>type<linktail>
        data structure.<s2>The socket options of an incoming connection (using
        <linkto>tcp0D.htm<linkmid>accept<linktail>) will be the same as the
        socket options of the listening socket.
 @commtarget SC1x3/SC2x |
    This legacy version of <i>setsockopt()<ie> specified here is not compatible 
    to the BSD 4.4 Socket API.<s2> The <i>setsockopt()<ie> function can be used
    in BSD 4.4 compatible mode if the compilation switch<nl>
    <nl><code>
    <tab> #define  BSD44_SOCKET_API_STYLE<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files.<s2> Using this switch the C-Library TCPIP_Socket.H include
    file redefines <i>setsockopt()<ie> to 
    <linkto>bsd37.htm<linkmid>setsockopt_bsd()<linktail>.<s2>The parameters 
    to <i>setsockopt_bsd()<ie> are identical to the parameters of the BSD4.4 socket
    <i>setsockopt()<ie> function.

 @Also  tcp01.htm | opensocket |
        tcp0D.htm | accept |
        tcp17.htm | getsockopt
 @Also  tcpC3.htm | opensocket_ext |
        bsd37.htm | setsockopt_bsd |
        |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x16<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int setsockopt (int sd, const SetSocketOption far *sockoptptr, int *error)
{
    _BX = sd ;

    _ES = FP_SEG(sockoptptr);
    _DI = FP_OFF(sockoptptr);

    _AH = API_SETSOCKOPT ;
    asm { int TCPIPVECT  } ;
    *error = _AX;
    return _DX ;
}
#endif

/*************************************************************************/
// get socket option
/*************************************************************************/
#ifdef _tcp17_
/*
 @doc DOC_tcp17_
 ---------------------------------------------------------------
 Get options on a socket
 ---------------------------------------------------------------
 @clib  getsockopt | Get options on a socket. |
        <cfont>int getsockopt ( int sd,<nl>
        <tab><tab><tab><tab> const GetSocketOption far *sockoptptr,<nl>
        <tab><tab><tab><tab> int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | sockoptptr  | Pointer to GetSocketOption
        <linkto>../../tcpstruc.htm#GetSocketOption<linkmid>type<linktail> that
        specifies the socket options (see tcpipapi.h) and contains pointers
        to where the specified socket option will be reported to.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm  On success, this function reports the requested socket option value to
        the buffer pointed to by the <code>optionValue<codee> member of
        GetSocketOption type at <code>sockoptptr<codee> and the length
        of this reported value is written to the location pointed to by
        the <code>optionLen<codee> member.<nl>
        <nl>
        The caller must setup the GetSocketOption
        <linkto>../../tcpstruc.htm#GetSocketOption<linkmid>type<linktail> structure
        prior to calling.<s2>In particular, the <code>optionValue<codee>
        member must point to a sufficiently large buffer to receive the
        reported option value and the size of this buffer must be stated
        in the location referenced by the <code>optionLen<codee> member.<s2>
        Note that this length specifier is both an input and an output
        parameter for this function.<s2>If on entry, the location referenced
        by <code>optionLen<codee> contains a value less than the buffer
        space required to report the requested socket option value, then
        the function will fail and return error code 242.<nl>
        <nl>
        The socket options of an incoming connection (using
        <linkto>tcp0D.htm<linkmid>accept<linktail>) will be the same as the
        socket options of the listening socket.
 @commtarget SC1x3/SC2x |
    This legacy version of <i>getsockopt()<ie> specified here is not compatible 
    to the BSD 4.4 Socket API.<s2> The <i>getsockopt()<ie> function can be used
    in BSD 4.4 compatible mode if the compilation switch<nl>
    <nl><code>
    <tab> #define  BSD44_SOCKET_API_STYLE<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files.<s2> Using this switch the C-Library TCPIP_Socket.H include
    file redefines <i>getsockopt()<ie> to 
    <linkto>bsd29.htm<linkmid>getsockopt_bsd()<linktail>.<s2>The parameters 
    to <i>getsockopt_bsd()<ie> are identical to the parameters of the BSD4.4 socket
    <i>getsockopt()<ie> function.

 @Also  tcp01.htm | opensocket |
        tcp16.htm | setsockopt | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x17<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int getsockopt (int sd, const GetSocketOption far *sockoptptr, int *error)
{
    _BX = sd ;

    _ES = FP_SEG(sockoptptr);
    _DI = FP_OFF(sockoptptr);

    _AH = API_GETSOCKOPT ;
    asm { int TCPIPVECT  } ;
    *error = _AX;
    return _DX;
}
#endif

/*************************************************************************/
//Set blocking mode on a socket (default is blocking!!)
/*************************************************************************/
#ifdef _tcp18_
/*
 @doc DOC_tcp18_
 ---------------------------------------------------------------
 Set a socket in blocking or non-blocking mode
 ---------------------------------------------------------------
 @clib  Set_Blocking_Mode | Set a socket in blocking or non-blocking mode. |
        <cfont>int Set_Blocking_Mode ( int sd,<nl>
        <tab><tab><tab><tab><tab><tab>unsigned char blocking_mode,<nl>
        <tab><tab><tab><tab><tab><tab>int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | blocking_mode  | 0: switch blocking off, 1:switch blocking on.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm  By default all sockets are in blocking mode.<s2> If a socket is
        set to non blocking mode, socket calls such as
        <linkto>tcp04.htm<linkmid>connect<linktail> and
        <linkto>tcp0D.htm<linkmid>accept<linktail> do not wait until
        full completion.<s2>Instead they  return immediately.<nl>
        <nl>
        Example usage of non-blocking mode:<nl><ul>
        The <linkto>tcp04.htm<linkmid>connect<linktail> call returns
        at a non blocking socket with error code 236 or 237, when
        the connection was not completed.<s2> The user can repeat this
        API call in a periodic loop until a successful connection is
        established. In this case the connect function returns error code
        0 or 256 (socket is already connected).<nl>
        <ule>
 @Also  tcp04.htm | connect  |
        tcp0D.htm | accept |
        tcp10.htm | recv
 @Also  tcp05.htm | recvfrom  |
        tcp0F.htm | send |
        tcp06.htm | sendto
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x18<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Set_Blocking_Mode (int sd, unsigned char blocking_mode, int *error)
{
    _BX = sd ;

    _AL = blocking_mode ;
    _AH = API_SETBLOCKINGMODE ;
    asm { int TCPIPVECT  } ;
    *error = _AX;
    return _DX ;                    // AX = 0, unless error code
}
#endif


/*************************************************************************/
//Register callback function on socket events
/*************************************************************************/
#ifdef _tcp19_
/*
 @doc DOC_tcp19_
 ---------------------------------------------------------------
 Register a user callback function
 ---------------------------------------------------------------
 @clib  RegisterCallbackFunction | Register a TCP user callback function. |
        <cfont>int RegisterCallbackFunction ( int sd,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; void far *funcptr,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; int eventflagmask,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | funcptr  | Pointer to user's callback function.
 @parm  int  | eventflagmask  | Event flag mask bit field (see menu below)
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm  The events which trigger the callback are controlled with the
        <code>eventflagmask<codee> input parameter.<s2>The set of possible
        event flags are (defined in TCPIPAPI.H):<nl>
        <nl>
        <ul>
        <li>CB_CONNECT_COMPLT - connection complete<nl>
        <li>CB_ACCEPT<s2>     - remote has established a connection to our listening server<nl>
        <li>CB_RECV<s2>     - incoming data arrived<nl>
        <li>CB_SEND_COMPLT<s2>     - sending of data has been acknowledged by the peer<nl>
        <li>CB_REMOTE_CLOSE<s2>     - peer has shut down the connection<nl>
        <li>CB_SOCKET_ERROR<s2>     - an error occured on the connection<nl>
        <li>CB_RESET<s2>     - peer has sent a rest on the connection<nl>
        <li>CB_CLOSE_COMPLT<s2>     - close has been completed<nl>
        <ule>
        <nl>
        These flags can be OR'ed together to form the mask for the set of events
        at which you want to be called.<nl>
        <nl>
        The callback function should satisfy the following prototype (Borland C):<nl>
        <nl>
        <code>void huge socketCallBackFunc(int socketdescriptor,<nl>
        <tab><tab><tab><tab><tab><tab><tab> int eventFlags) ;<codee>
        <nl><nl>
        The callback function's parameter <code>eventFlags<codee> contains the event(s)
        that have occured.<s2>This bit field is encoded the same as the
        <code>eventflagmask<codee> input parameter to this API function.
        <nl><nl>
        Note that most of the call back calls will be made in the context of the drivers
        receive task (e.g. task ETH0). Therefore processing should be kept at a minimum in the
        call back function. The user call back function should set a flag or increase a counter and
        signal the user application task.<nl>
        <nl>
        A socket callback may be removed by calling this API function with
        both a null <code>funcptr<codee> and zero <code>eventflagmask<codee>.<s2>
        <linkto>tcp02.htm<linkmid>Closing<linktail> the socket also deactivates
        the callback.<s2>
        Before exiting a program, any sockets which have callbacks installed must either
        be closed or have the callback removed.<s2> Otherwise a callback could be present
        which references a program no longer loaded into memory.<nl>
 @Also  tcp01.htm | opensocket  |
        tcp02.htm | closesocket |
        tcp7a.htm | RegisterIPCallbackHandler
 @Also  tcpC3.htm | opensocket_ext  |
        tcp7B.htm | Register_ARP_User_CB |
        tcp7C.htm | RegisterIPCallbackHandler_Snd
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x19<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int RegisterCallbackFunction (int sd, void far *funcptr, int eventflagmask, int *error)
{
    _BX = sd ;
    _CX = eventflagmask ;
    _ES = FP_SEG(funcptr) ;
    _DI = FP_OFF(funcptr) ;

    _AH = API_REGISTERCALLBACK ;
    asm { int TCPIPVECT  } ;
    *error = _AX;
    return _DX;
}
#endif


/*************************************************************************/
#ifdef _tcp1A_
/*
 @doc DOC_tcp1A_
 ---------------------------------------------------------------
 Await specified events on a selected set of sockets
 ---------------------------------------------------------------
 @clib  select | Await specified events on a selected set of sockets. |
        int select ( int nfds,<nl>
        <tab><tab><tab> fd_set far *readfds,<nl>
        <tab><tab><tab> fd_set far *writefds,<nl>
        <tab><tab><tab> fd_set far *exceptfds,<nl>
        <tab><tab><tab> const struct timeval FAR *timeout ) ; |
 @parm  int  | nfds  | One greater than highest socket descriptor to be
     monitored in the following set of three <cfont>fd_set<efont> objects.
 @parm  int  | readfds  | Input/Output Parameter:<s2> Pointer to a
   <linkto>../../tcpstruc.htm#fd_set<linkmid>fd_set<linktail> bit field
   that on input specifies the set of sockets to be monitored for receiver
   activity.<s2> On return those sockets for which receiver data is ready
   among those specified for monitoring will have their bits in this field
   set to '1'.<s2> All other bits will be zeroed.<nl>
 @parm  int  | writefds  | Input/Output Parameter:<s2> Pointer to a
   <linkto>../../tcpstruc.htm#fd_set<linkmid>fd_set<linktail> bit field that
   on input specifies the set of sockets to be monitored for send ready
   condition.<s2> On return those sockets ready for send among those
   specified for monitoring here will have their bits in this field set
   to '1'.<s2> All other bits will be zeroed.<nl>
 @parm  int  | exceptfds  | Input/Output Parameter:<s2> Pointer to a
   <linkto>../../tcpstruc.htm#fd_set<linkmid>fd_set<linktail> bit field
   that on input specifies the set of sockets to be monitored for error
   conditions.<s2> On return  those sockets with errors among those
   specified for monitoring here will have their bits in this field
   set to '1'.<s2> All other bits will be zeroed.<nl>
 @parm  int  | timeout    | Input Parameter:<s2>Pointer to
    a <linkto>../../tcpstruc.htm#timeval<linkmid>timeval<linktail> data structure
    which specifies the maximum wait time.<s2>  This pointer
    can be NULL to block until an event occurs on one of the
    specified sockets.<nl>
 @rdesc 0 if timeout, otherwise number of hits.<s2> This is the
     number of selected sockets for which a specified event has occurred.<nl>
     <nl>
     If <code>nfds<codee> input parameter was invalid, then the
     return value will also be zero.<nl>
 @comm
     This function and its <linkto>tcp1Am.htm<linkmid>select_ms()<linktail> variant
     API operate similarly to the standard Berkeley sockets implementation.<s2>
     This API is useful when a single program thread is to manage the activity
     on more than one socket.<s2>  The thread can sleep for up to a specified
     amount of time, awaiting events on a selected set of sockets.<s2>
     These events,  selected by the caller, can be receiver activity,
     transmitter activity and/or socket error conditions.<nl>
     <nl>
     The most common use of this API is to sleep on a combination of
     receiver activity or error conditions.<s2> In this manner, your
     thread will wakeup when either data is received by one of your specified
     sockets, or if one of the sockets is closed by the peer.<s2> For
     this usage, the <code>writefds<codee> parameter would be NULL to
     indicate that you are not interested in hearing about any socket
     transmit activity.<nl>
     <nl>
     Note that when only a single socket is involved, the
     <linkto>tcp10.htm<linkmid>recv()<linktail> and
     <linkto>tcp05.htm<linkmid>recvfrom()<linktail> API provide a more
     efficient receiver sleep mechanism than <code>select().<codee><nl>
     <nl>
     This API's three pointer parameters to
     <linkto>../../tcpstruc.htm#fd_set<linkmid>fd_set<linktail> objects can
     point to the same object.<s2> For example, for the receiver
     activity wait call, the <code>readfds<codee> and  <code>exceptfds<codee>
     parameters could both reference the same <code>fd_set<codee> object.<s2>
     This is commonly done this way.<s2> You lose the resolution over whether
     the error or receiver activity event occurred, but this
     can be resolved on a subsequent <linkto>tcp10.htm<linkmid>recv()<linktail>
     (or <linkto>tcp05.htm<linkmid>recvfrom()<linktail>) call that would
     normally follow a return from the <code>select().<codee><nl>
     <nl>
     In the parameter description above for <code>readfds<codee>,
     <code>writefds<codee> and <code>exceptfds<codee> it says
     <i>"All other bits will be zeroed"<ie>.<s2> Here "all bits"
     means those bits with indexes lower than the <code>nfds<codee>
     input parameter value.<s2> (Caller is responsible for zeroing the
     others with indexes higher). <s2> This assumes that
      either no two pointers are pointing to the same <code>fd_set<codee>
      or that the other events have not occurred.<s2> The point here is
      that zeros are returned for sockets which have no event.<s2>
      For the case where a pointer to the same <code>fd_set<codee>
      object is passed for both the <code>readfds<codee>
      and <code>exceptfds<codee> parameters, for example,
      the returned bits will be set if either receiver data is ready
      or an error condition has occurred.<s2> The bits set
      represent a logical OR of input parameter conditions which
      referenced the <code>fd_set.<codee><nl>
     <nl>
     The <code>nfds<codee> can be jammed to the <code>MAX_BECK_SOCKETS<codee>
     constant value and this API will operate.<s2>(The lazy programmer's
     approach.)<s2> However, efficiency down inside the TCP/IP
     stack is improved if you confine the bit field range over which the
     system must operate by setting the <code>nfds<codee> input parameter
     to one count greater than your highest socket descriptor bit
     set in any of your <code>fd_set<codee> fields.<nl>
     <nl>
     This API is reentrant so long as it is called for a mutually
     exclusive set of sockets.<s2> However, when two threads call
     concurrently with an overlapping set of sockets specified, the last
     thread to call will receive a zero hit count return value.<s2>
     This should be avoided.<nl>
     <nl>
     The alternative non-standard calling convention
     offered by <linkto>tcp1Am.htm<linkmid>select_ms()<linktail>
     is recommended when Berkeley sockets compatibility is not
     required.<s2> This other API works the same except for that
     it uses the simplified timeout argument specified in milliseconds.<nl>

 @Also  tcp1Am.htm | select_ms  |
        tcp05.htm  | recvfrom |
        tcp27.htm  | recvfromto
 @Also  tcp10.htm  | recv  |
        FDnext.htm | FD_Next |
         |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x1A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.22 | V1.22 | V1.22 | V1.11 | V1.00
 @target_clib V2.08

*/
int select (int          nfds,
            fd_set far * readfds,
            fd_set far * writefds,
            fd_set far * exceptfds,
            const struct timeval far * timeout )
{
    _BX = FP_OFF(&nfds) ;
    _AX = API_SELECT << 8 | 0x1 ;   // AL = 1 indicates timeval pointer.
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif


/*************************************************************************/
#ifdef _tcp1Am_
/*
 @doc DOC_tcp1Am_
 ---------------------------------------------------------------
 Await specified events on a selected set of sockets
 ---------------------------------------------------------------
 @clib  select_ms | Poll, await up to a maximum number of
  milliseconds, or wait forver for specified events on a
  selected set of sockets.
. |
        int select_ms ( int <tab><s3> nfds,<nl>
        <tab><tab><tab><s3> fd_set far *readfds,<nl>
        <tab><tab><tab><s3> fd_set far *writefds,<nl>
        <tab><tab><tab><s3> fd_set far *exceptfds,<nl>
        <tab><tab><tab><s3> long <tab><s2> timeout ) ; |
 @parm  int  | nfds  | One greater than highest socket descriptor to be
     monitored in the following set of three <cfont>fd_set<efont> objects.
 @parm  int  | readfds  | Input/Output Parameter:<s2> Pointer to a
   <linkto>../../tcpstruc.htm#fd_set<linkmid>fd_set<linktail> bit field
   that on input specifies the set of sockets to be monitored for receiver
   activity.<s2> On return those sockets for which receiver data is ready
   among those specified for monitoring will have their bits in this field
   set to '1'.<s2> All other bits will be zeroed.<nl>
 @parm  int  | writefds  | Input/Output Parameter:<s2> Pointer to a
   <linkto>../../tcpstruc.htm#fd_set<linkmid>fd_set<linktail> bit field that
   on input specifies the set of sockets to be monitored for send ready
   condition.<s2> On return those sockets ready for send among those
   specified for monitoring here will have their bits in this field set
   to '1'.<s2> All other bits will be zeroed.<nl>
 @parm  int  | exceptfds  | Input/Output Parameter:<s2> Pointer to a
   <linkto>../../tcpstruc.htm#fd_set<linkmid>fd_set<linktail> bit field
   that on input specifies the set of sockets to be monitored for error
   conditions.<s2> On return  those sockets with errors among those
   specified for monitoring here will have their bits in this field
   set to '1'.<s2> All other bits will be zeroed.<nl>
 @parm  int  | timeout    | Timeout in milliseconds.<s2> Set to a minus value
    to block without timeout.<s2> Set to zero for polling.
 @rdesc 0 if timeout, otherwise number of hits.<s2> This is the
     number of selected sockets for which a specified event has occurred.<nl>
     <nl>
     If <code>nfds<codee> input parameter was invalid, then the
     return value will also be zero.<nl>
 @comm
     This alternative to <linkto>tcp1A.htm<linkmid>select()<linktail>
     API is available for when Berkeley sockets compatible source is
     not required.<s2> The only difference is that this function takes
     the timeout value as a simple long value in units of milliseconds.<s2>
     And a zero value for the <code>timeout<codee> argument allows for
     polling.<nl>
     <nl>
     Refer to the <linkto>tcp1A.htm<linkmid>select()<linktail>
     API description for more information about these API.

 @Also  tcp1A.htm | select  |
        FDnext.htm | FD_Next |
         |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x1A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.22 | V1.22 | V1.22 | V1.11 | V1.00
 @target_clib V2.08

*/
int select_ms (int          nfds,
               fd_set far * readfds,
               fd_set far * writefds,
               fd_set far * exceptfds,
               long         timeout )
{
    _BX = FP_OFF(&nfds) ;
    _AX = API_SELECT << 8 ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif


/*************************************************************************/
#ifdef _FDNext_
/*
 @doc DOC_FDNext_
 ---------------------------------------------------------------
 fd_set iterator
 ---------------------------------------------------------------
 @clib  FD_Next | Iterator for sets of sockets. |
        int FD_Next ( const fd_set * fds_set,<nl>
        <tab><tab><tab><s1> int previous_fds ); |
 @parm  int  | fds_set  | Pointer to the
   <linkto>../../tcpstruc.htm#fd_set<linkmid>fd_set<linktail> bit field
   whose sockets are bing iterated.<nl>
 @parm  int  | previous_fds  | One count greater than the bit number
      in the fds_set->fds_bits[] bit field at which to start the scan.<s2>
      (This argument serves as the iterator's cursor.)<s2> The
      bit scan sequences from high indexes down to zero.<nl>
 @rdesc If greater or equal zero:<s2>Next socket descriptor<nl>
        Negative:<s2> End of list (no more sockets)<nl>
 @comm
    This library function can be used to iterate through the set of sockets
    created by a <linkto>tcp1A.htm<linkmid>select()<linktail> (or
    <linkto>tcp1Am.htm<linkmid>select_ms()<linktail>) call.<nl>
    <nl>
    On first call, the <code>previous_fds<codee> should be set one
    count greater than the highest socket descriptor being handled.<s2>
    This would normally be the same value as had been passed to the
    <linkto>tcp1A.htm<linkmid>select()<linktail> API as the <code>nfds<codee>
    parameter.<s2> Then on subsequent calls to this socket iterator,
    the <code>previous_fds<codee> should be set to the previous
    return value from this function.<nl>
    <nl>
    When a negative value is returned, all sockets have been
    interated and the end of list has been reached.<nl>

  @Also  tcp1A.htm  | select  |
         tcp1Am.htm | select_ms |
         |
 @rtos  This library function is implemented without any
     calls into the @CHIP-RTOS.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version      any |   any |  any  |  any  | any
 @target_clib V2.08

*/
int FD_Next (const fd_set * fds_set, int previous_fds)
{
    WORD mask ;
    previous_fds-- ;
    // Examples: If previous_fds = 0 here, then get mask = 0x0001.
    mask = 0xFFFF >> (15 - (previous_fds & 0xF)) ;
    while (previous_fds >= 0)
    {
        WORD field = fds_set->fds_bits[previous_fds >> 4] ;
        if (field & mask)               // Found something?
        {
            // If here on first pass through outer while() loop,
            //  then following shift can be non-zero.  On subsequent
            //  loops, the shift is always zero bits to right.
            mask = 0x8000 >> (15 - (previous_fds & 0xF)) ;
            while((field & mask) == 0)  // Believe the bit must be there!
            {
                mask >>= 1 ;
                previous_fds-- ;
            }
            return previous_fds ;
        }
        mask  = 0xFFFF ;                // After first pass, test all bits.
        previous_fds &= ~0xF ;
        previous_fds-- ;                // Now lower 4 bits are 1's.
    }
    return previous_fds ;
}
#endif


/*************************************************************************/
//get last socket error
/*************************************************************************/
#ifdef _tcp21_
/*
 @doc DOC_tcp21_
 ---------------------------------------------------------------
 Get last socket error
 ---------------------------------------------------------------
 @clib  get_socketerror | Get last socket error. |
        <cfont>int get_socketerror ( int sd );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @rdesc <linkto>../../iperrlst.htm<linkmid>error<linktail> code
 @comm  Returns the last error which occured on specified socket.
 @commtarget SC1x3/SC2x |
    A faster dynamic linked version of this API is available starting
    with <chiprtos> version 1.36.<s2> This alternative API is
    named <i>get_socketerror_Dyn<ie> .  When the compilation switch<nl>
    <nl><code>
    <tab> #define  TCPIP_DYN_LINK_SOCK<nl>
    <codee><nl>
    is defined in the user application prior to including the Beck C-Library
    header files, the C-Library TCPIP_Socket.H include
    file redefines <i>get_socketerror<ie> to <i>get_socketerror_Dyn<ie>.<nl>
    <nl>
    With  or without this compilation switch set, the
    <i>get_socketerror_Dyn()<ie> alternative may be called explicitly.

 @Also  tcp01.htm | opensocket  | tcpC3.htm | opensocket_ext | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x21<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00

*/
int get_socketerror (int sd)
{
    _BX = sd ;
    _AH = API_GET_SOCKETERROR ;
    asm { int TCPIPVECT  } ;

    return _AX ;
}
#endif


/*********************************************************************************/
// search for tcp socket by given local and return state,remote ip and local port
/*********************************************************************************/
#ifdef _tcp22_
/*
 @doc DOC_tcp22_
 ---------------------------------------------------------------
 Find TCP socket and return state
 ---------------------------------------------------------------
 @clib  Get_TCP_Socket_State | Find TCP socket and return its state. |
        <cfont>unsigned char Get_TCP_Socket_State ( unsigned int localPort,<nl>
        <tab><tab><tab><tab><tab><tab><tab> unsigned long far *remoteIP,<nl>
        <tab><tab><tab><tab><tab><tab><tab> unsigned int *remotePort );<efont> |
 @parm  int  | localPort  | Local port (e.g. htons(23) for telnet).
 @parm  int  | remoteIP  | Output parameter:<s2>Pointer to storage for
        32 bit remote IPv4 address.
 @parm  int  | remotePort  | Output parameter:<s2>Pointer to storage for
        16 bit remote peer port number.
 @rdesc Socket state (see list below)

 @comm  This API searches for a TCP socket by a given local port number, returning the
        socket state, IP address and port number of the remote peer (if any).<nl>
        <nl>
        If the return value is not INVALID (=20) and is greater or equal to SYN_SENT (=2)
        then a TCP connection is established.<s2>In this case the storage at
        <code>remoteIP<codee> holds the 32 bit IP address of the connected remote peer
        and <code>remotePort<codee> contains the remote peer port number.

        Possible TCP socket states:<nl>

        <tab>0:<s2>CLOSED<nl>
        <tab>1:<s2>LISTEN<nl>
        <tab>2:<s2>SYN_SENT<nl>
        <tab>3:<s2>SYN_RECEIVED<nl>
        <tab>4:<s2>ESTABLISHED<nl>
        <tab>5:<s2>CLOSE_WAIT<nl>
        <tab>6:<s2>FIN_WAIT_1<nl>
        <tab>7:<s2>CLOSING<nl>
        <tab>8:<s2>LAST_ACK<nl>
        <tab>9:<s2>FIN_WAIT_2<nl>
        <tab>10:<s2>TIME_WAIT<nl>
        <tab>20:<s2>INVALID<nl>

 @commtarget SC1x3/SC2x | Deprecated, because only IPv4 addresses can be stored at the
         provided 32-bit buffer at <code>remoteIP<codee>.<s2> The alternative
         <linkto>tcp24.htm<linkmid>Get_TCP_Socket_State_IP_All<linktail> API is
         instead recommended, which covers both IPv4 and IPv6 protocols.<nl>

 @Also  tcp01.htm | opensocket |
        htons.htm | htons    |
        tcp24.htm | Get_TCP_Socket_State_IP_All
 @Also  tcpc3.htm | opensocket_ext |
         | |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x22<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.04 | V1.00 | V1.00 | V0.90 | V1.00

*/
unsigned char Get_TCP_Socket_State (unsigned int localPort,
                                    unsigned long far * remoteIP,
                                    unsigned int * remotePort)
{
    unsigned char state ;

    _BX = localPort ;
    _ES = FP_SEG(remoteIP) ;
    _DI = FP_OFF(remoteIP) ;

    _AH = API_GET_TCP_STATE ;
    asm { int TCPIPVECT  } ;

    state = _AL ;
    *remotePort = _CX ;

    return state ;
}
#endif


/*********************************************************************************/
// IPv4 and IPv6 SC123:
// search for tcp socket by given local and return state,remote ip and local port
/*********************************************************************************/
#ifdef _tcp24_
/*
 @doc DOC_tcp24_
 ---------------------------------------------------------------
 Find TCP socket and return state (IPv4 and IPv6)
 ---------------------------------------------------------------
 @clib  Get_TCP_Socket_State_IP_All | Find TCP socket and return its state. |
        <cfont>unsigned char Get_TCP_Socket_State_IP_All (<nl>
        <tab><tab><tab><tab><tab><tab><tab> unsigned int localPort,<nl>
        <tab><tab><tab><tab><tab><tab><tab> struct in6_addr far *remoteIP,<nl>
        <tab><tab><tab><tab><tab><tab><tab> unsigned int *remotePort );<efont> |
 @parm  int  | localPort  | Local port (e.g. htons(23) for telnet).
 @parm  int  | remoteIP  | Output parameter:<s2>Pointer to a
        <linkto>../../tcpstruc.htm#in6_addr<linkmid>in6_addr<linktail>
        structure which will receive the remote IP address.
 @parm  int  | remotePort  | Output parameter:<s2>Pointer to storage for
        16 bit remote peer port number.
 @rdesc Socket state (see list below)
 @comm  Search for a TCP socket by a given local port number, returning the
        socket state, IP address and port number of the remote peer (if any).<nl>
        <nl>
        If the return value is not INVALID (=20) and is greater or equal to SYN_SENT (=2)
        then a TCP connection is established.<s2>In this case the storage at
        <code>remoteIP<codee> holds the IP address of the connected remote peer
        and <code>remotePort<codee> contains the remote peer port number.

        Possible TCP socket states:<nl>
        @raw
        CLOSED          0
        LISTEN          1
        SYN_SENT        2
        SYN_RECEIVED    3
        ESTABLISHED     4
        CLOSE_WAIT      5
        FIN_WAIT_1      6
        CLOSING         7
        LAST_ACK        8
        FIN_WAIT_2      9
        TIME_WAIT      10
        INVALID        20
 @Also  tcp01.htm | opensocket |
        tcp22.htm | Get_TCP_Socket_State |
        htons.htm | htons
 @Also  tcpC3.htm | opensocket_ext | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x24<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V0.90 | V1.00

*/
unsigned char Get_TCP_Socket_State_IP_All(unsigned int localPort,
                                          struct in6_addr far * remoteIP,
                                          unsigned int * remotePort)
{
    unsigned char state ;

    _BX = localPort ;
    _ES = FP_SEG(remoteIP) ;
    _DI = FP_OFF(remoteIP) ;

    _AH = API_GET_TCP_STATE_IP_ALL ;
    asm { int TCPIPVECT  } ;

    state = _AL ;
    *remotePort = _CX ;

    return state ;
}
#endif





#ifdef _tcp23_
/*
 @doc DOC_tcp23_
 ---------------------------------------------------------------
 Get information about all open sockets
 ---------------------------------------------------------------
 @clib  int FindAllOpenSockets | Find/return information about all open sockets
        listed in the internal socket table. |
        <cfont>int FindAllOpenSockets( SocketInfo far * SockInfoPtr,<nl>
        <tab><tab><tab><tab><tab><s3> int max);<efont> |
 @parm  void *  | SockInfoPtr  | Output Parameter:<s2> Pointer to an array of
        <cfont>max<efont>
        <linkto>../../tcpstruc.htm#SocketInfo<linkmid>SocketInfo<linktail> structures
        in the user's memory space into which this API will report the socket information.
 @parm  int | max | Size of the array (maximum number of table entries reported).

 @rdesc Returns the number of open sockets.<s2>
        The user provided array holds the socket information
        for up to <cfont>max<efont> sockets (the lesser of
        two counts: Return value, <cfont>max<efont>).<nl>

 @commtarget SC1x3/SC2x | Deprecated, because only IPv4 addresses can be stored
         at the provided 32-bit IP address buffer in the <code>SocketInfo<codee>
         structure.<nl>
         <nl>
        Use <linkto>tcp25.htm<linkmid>FindAllOpenSockets_IP_All<linktail>
        instead.<nl>

 @Also  tcp25.htm | FindAllOpenSockets_IP_All | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x23<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
int FindAllOpenSockets(SocketInfo far * SockInfoPtr, int max)
{
   _CX = max;
   _ES = FP_SEG(SockInfoPtr);
   _DI = FP_OFF(SockInfoPtr);
   _AH = API_FINDALL_SOCKETS;
   asm {  int TCPIPVECT };
   return _AX;
}
#endif


#ifdef _tcp25_
/*
 @doc DOC_tcp25_
 ---------------------------------------------------------------
 Get information about all open sockets
 ---------------------------------------------------------------
 @clib  int FindAllOpenSockets_IP_All | Find/return information about all open
        sockets listed in the internal socket table. (IPv4 and IPv6) |
        <cfont>int FindAllOpenSockets_IP_All(<nl>
        <tab><tab><tab><tab><tab><s3> SocketInfoIPv4v6 far * SockInfoPtr,<nl>
        <tab><tab><tab><tab><tab><s3> int max);<efont> |
 @parm  void *  | SockInfoPtr  | Output Parameter:<s2> Pointer to an array of
        <cfont>max<efont>
        <linkto>../../tcpstruc.htm#SocketInfoIPv4v6<linkmid>SocketInfoIPv4v6<linktail>
        structures in the user's memory space into which this API will report
        the socket information.
 @parm  int | max | Size of the array (maximum number of table entries reported).

 @rdesc Returns the number of all open sockets.<s2>
        The user provided array holds the socket information
        for up to <cfont>max<efont> sockets (the lesser of
        two counts: Return value, <cfont>max<efont>).<nl>
 @Also  tcp23.htm | FindAllOpenSockets | | | |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x25<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V0.90 | V1.00
*/
int FindAllOpenSockets_IP_All(SocketInfoIPv4v6 far * SockInfoPtr, int max)
{
   _CX = max;
   _ES = FP_SEG(SockInfoPtr);
   _DI = FP_OFF(SockInfoPtr);
   _AH = API_FINDALL_SOCKETS_IP_ALL;
   asm {  int TCPIPVECT };
   return _AX;
}
#endif



/*************************************************************************/
//shutdown socket
/*************************************************************************/
#ifdef _tcp26_
/*
 @doc DOC_tcp26_
 ---------------------------------------------------------------
 Shutdown a socket
 ---------------------------------------------------------------
 @clib  shutdown | Shutdown a socket in read, write or both directions. |
        <cfont>int shutdown ( int sd, unsigned char dir, int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | dir | Direction:    0:read, 1:write, 2: both
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm  This API function only works on TCP sockets.<s2>
        <nl><nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x26<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V0.90 | V1.00

 @target_clib V2.01
*/
int shutdown (int sd, unsigned char dir, int * error)
{
    _BX = sd ;
    _AL = dir;
    _AH = API_SHUTDOWN ;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX ;                    // AX = 0, unless error code
}
#endif

/*************************************************************************/
//sendto
/*************************************************************************/
#ifdef _tcp28_
/*
 @doc DOC_tcp28_
 ---------------------------------------------------------------
 Transmit a datagram
 ---------------------------------------------------------------
 @clib  sendto_iface | Transmit a datagram via specified interface. |
        <cfont>int sendto_iface ( int sd, const char far *bufptr, int bufLen,<nl>
        <tab><tab><tab> int flags, const struct sockaddr far *toPtr,<nl>
        <tab><tab><tab> DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab> int *error );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @parm  int  | bufptr  | Pointer to output buffer containing
        characters to be transmitted.
 @parm  int  | bufLen  | Maximum characters to output from <code>bufptr<codee>.
 @parm  int  | flags  | Wait option:<nl>
        <ul>
        <li><bold>MSG_BLOCKING<bolde>  - Wait for data send to complete.<nl>
        <li><bold>MSG_DONTWAIT<bolde> - Don't wait for data send to complete.<nl>
        <ule>
 @parm  int  | toPtr  | Data destination, pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
         (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6, <i>SC1x3/SC2x only!<ie>) data structure.
 @parm  int  | DevHandlePtr  | Driver handle pointer
        <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>,
        which caller must fill in prior to call. TCPIP send the packet via this specified
        Device handle.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -1:  Failure, see error value reported<nl>
        otherwise: Count of bytes transfered into the socket send queue.
 @comm  This API function applies only to UDP sockets and works similiar than the
        <linkto>tcp06.htm<linkmid>sendto<linktail> function.<s2>
        It is required, when the user wants to send a datagram with a multicast destination
        address via a specified device interface.
        It is not necessary to use this function, if the packet should by send via
        the default Ethernet interface of the IPC@CHIP&reg;.
        The existing API function <linkto>tcp06.htm<linkmid>sendto()<linktail> function
        (or <linkto>bsd35.htm<linkmid>sendto_bsd()<linktail> function)
        does this by default, if a the multicast destination address is specified.
        <nl>
 @commtarget SC1x3/SC2x |
        The actual library function reached here is named
        <code>sendto_iface_ipstackV2<codee>, unless the
        <bold>TCPIP_DYN_LINK_SOCK<bolde> compilation switch discussed
        below is defined.<s2> This name change
        occurs due to a macro in the library header file.<nl>
        <nl>
    The  compilation  switch<nl>
    <nl><code>
      <tab> #define  TCPIP_DYN_LINK_SOCK<nl>
    <codee><nl>
    may be defined in the user application prior to including the Beck C-Library
    header files to use the faster executing dynamic link variant of this C-Library
    function.<s2>  In this case, the C-Library header file will redefine the
    <code>sendto_iface<codee> symbol to <code>sendto_iface_Dyn<codee>
    to reach this dynamic linked substitute API function.<nl>
    <nl>



 @Also  tcp06.htm | sendto  |
        ddvAD.htm | Get driver handle pointer | |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x28<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.21 | V1.21 | V1.21 | V1.10 | V1.00

*/

#undef sendto_iface     // Maintain original name
   // This version is for original SC12 TCP/IP stack
int sendto_iface (int sd, const char far * bufptr, int bufLen, int flags,
                  const struct sockaddr far * toPtr,
                  DevUserIfaceHandle DevHandlePtr,
                  int *error)
{
    int bytes_sent ;
    int the_error_code = 0 ;
    int toLen;
    struct send_params S;

    toLen = sizeof(struct sockaddr_in_ipstack);

    //Init the struct send_param S for API-Call
    S.bufferPtr      = bufptr;
    S.bufferLength   = bufLen;
    S.flags          = flags;
    S.toPtr          = (struct sockaddr *) toPtr;
    S.tolengthPtr    = &toLen;

    //API
    _BX = sd;
    _DX = FP_SEG(&S);
    _SI = FP_OFF(&S);
    _ES = FP_SEG(DevHandlePtr);
    _DI = FP_OFF(DevHandlePtr);
    _AH = API_SENDTO_IFACE;
    asm { int TCPIPVECT  } ;
    bytes_sent = _AX ;
    if (_DX != 0)
    {
        the_error_code = bytes_sent ;       // AX value
        bytes_sent = API_ERROR ;
    }
    *error = the_error_code ;
    return bytes_sent ;
}
#endif

#ifdef _tcp28e_
// This version is for the new TCP/IP version, used  at target sc123
int sendto_iface_ipstackV2(int sd, const char far * bufptr, int bufLen, int flags,
                           const struct sockaddr far * toPtr,
                           DevUserIfaceHandle DevHandlePtr,
                           int *error)
{
    int bytes_sent ;
    int the_error_code = 0 ;
    int toLen;
    struct send_params S;

    if ( ((struct sockaddr_in_ipstackV2 far *)toPtr)->sin_family == AF_INET)
    {
       toLen = sizeof(struct sockaddr_in_ipstackV2);
    }
    else
    {
       toLen = sizeof(struct sockaddr_in6);
    }

    //Init the struct send_param S for API-Call
    S.bufferPtr      = bufptr;
    S.bufferLength   = bufLen;
    S.flags          = flags;
    S.toPtr          = (struct sockaddr *) toPtr;
    S.tolengthPtr    = &toLen;

    //API
    _BX = sd;
    _DX = FP_SEG(&S);
    _SI = FP_OFF(&S);
    _ES = FP_SEG(DevHandlePtr);
    _DI = FP_OFF(DevHandlePtr);
    _AH = API_SENDTO_IFACE;
    asm { int TCPIPVECT  } ;
    bytes_sent = _AX ;
    if (_DX != 0)
    {
        the_error_code = bytes_sent ;       // AX value
        bytes_sent = API_ERROR ;
    }
    *error = the_error_code ;
    return bytes_sent ;
}
#endif  //#ifdef _tcp28e

/*************************************************************************/
//PPP client installed
/*************************************************************************/
#ifdef _tcp40_
/*
 @doc DOC_tcp40_
 ---------------------------------------------------------------
 Check if PPP client installed
 ---------------------------------------------------------------
 @clib  PPP_Client_Installed | Check if PPP client is installed. |
        <cfont>int PPP_Client_Installed ( void );<efont> |
 @parm  int  |   | -- none --
 @rdesc 0:   PPP client is not installed<nl>
        non-zero: PPP client is installed<nl>
 @comm  Tests if PPP client services are available in @CHIP-RTOS
        version and not disabled via CHIP.INI
        <linkto>../../config.htm#PPPCLIENT_ENABLE<linkmid>configuration<linktail>.
 @Also  tcp41.htm | PPP_Client_Open  |
        tcp70.htm | Get_Installed_Servers | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x40<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int PPP_Client_Installed (void)
{
    _AH = PPPCLIENT_INSTALLED ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif
/*************************************************************************/
//PPP client open  IPv4 address configuration
/*************************************************************************/
#ifdef _tcp41_
/*
 @doc DOC_tcp41_
 ---------------------------------------------------------------
 Open a PPP connection
 ---------------------------------------------------------------
 @clib  PPP_Client_Open | Open a PPP connection. |
        <cfont>int PPP_Client_Open ( PPPClient_Init far *ptr, int *error );<efont> |
 @parm  int  | ptr  | Pointer to a
        <linkto>../../tcpstruc.htm#PPPClient_Init<linkmid>PPPClient_Init<linktail>
        type data structure (declared in tcpipapi.h)<nl>
        The structure must be persistent. The RTOS does not make a copy.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#client<linkmid>code<linktail>, 0 on success.
 @rdesc 0  = Success <nl>
        -1 = Failure, see <code>error<codee> output parameter.<nl>
        -2 = Failure, PPP client is disabled by
        <linkto>../../config.htm#PPPCLIENT_ENABLE<linkmid>CHIP.INI<linktail> entry.<nl>

 @comm  On success, the structure at <code>ptr<codee> contains the needed
        IP data for further TCP/IP socket communication.<nl>
        <nl>
        Refer to the PPPCLIE.C example for how to use this API.<s2>
        Also refer to the
        <linkto>../../tcpstruc.htm#PPPClient_Init<linkmid>PPPClient_Init<linktail>
        data structure documentation.<nl>
        <nl>
        Note: <bold>Only one PPP client connection can be opened
        at a time!!<bolde><nl>
 @commtarget SC1x3/SC2x | This API applies to IPv4 type PPP connections.<s2>
        For IPv6 connections, see
        <linkto>tcp46.htm<linkmid>PPP_Client_Open_IPv6<linktail> API.<nl>
 @Also  tcp40.htm | PPP_Client_Installed  |
        tcp42.htm | PPP_Client_Close  |
        tcp43.htm | PPP_Client_GetStatus
 @Also  tcp46.htm | PPP_Client_Open_IPv6  |
        | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x41<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int PPP_Client_Open (PPPClient_Init far * ptr, int *error)
{
    _ES = FP_SEG(ptr) ;
    _DI = FP_OFF(ptr) ;
    _AH = PPPCLIENT_OPEN ;
    asm { int TCPIPVECT  } ;
    *error = _AX;
    return _DX ;
}
#endif


/*************************************************************************/
//PPP client close
/*************************************************************************/
#ifdef _tcp42_
/*
 @doc DOC_tcp42_
 ---------------------------------------------------------------
 Close a PPP client connection
 ---------------------------------------------------------------
 @clib  PPP_Client_Close | Close a PPP client connection. |
        <cfont>int PPP_Client_Close ( int * error );<efont> |
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#client<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        -1 = failure, see <code>error<codee> output parameter.<nl>
        -2 = failure, PPP client is disabled by
        <linkto>../../config.htm#PPPCLIENT_ENABLE<linkmid>CHIP.INI<linktail> entry.<nl>
 @comm  Within this API call, after closing the PPP session the
        PPP Client executes the modem hang-up commands specified in the
        <linkto>../../tcpstruc.htm#PPPClient_Init<linkmid>PPPClient_Init<linktail>
        data structure
        defined in the <linkto>tcp41.htm<linkmid>PPP_Client_Open<linktail>
        call.<nl>
 @Also  tcp41.htm | PPP_Client_Open  |  |  |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x42<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int PPP_Client_Close (int *error)
{
    _AH = PPPCLIENT_CLOSE ;
    asm { int TCPIPVECT  } ;
    *error = _AX;
    return _DX ;
}
#endif

/*************************************************************************/
//PPP client get status
/*************************************************************************/
#ifdef _tcp43_
/*
 @doc DOC_tcp43_
 ---------------------------------------------------------------
 Get PPP client status
 ---------------------------------------------------------------
 @clib  PPP_Client_GetStatus | Get PPP client status. |
        <cfont>int PPP_Client_GetStatus ( int *error );<efont> |
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#client<linkmid>code<linktail>, 0 on success.<nl>
        Currently identical with return value.<nl>

 @rdesc Non-negative:  PPP client
        <linkto>../../iperrlst.htm#status<linkmid>status<linktail> code<nl>
        -2:  Failure, PPP client is disabled by
        <linkto>../../config.htm#PPPCLIENT_ENABLE<linkmid>CHIP.INI<linktail> entry.<nl>

 @Also  tcp41.htm | PPP_Client_Open  |
        tcp40.htm | PPP_Client_Installed | |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x43<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int PPP_Client_GetStatus (int *error)
{
    _DX = 0;
    _AH = PPPCLIENT_GET_STATUS ;
    asm { int TCPIPVECT  } ;
    *error = _DX;
    return _AX;
}
#endif

/*************************************************************************/
//PPP client get DNS IP as negotiated by the remote PPP server
/*************************************************************************/
#ifdef _tcp44_
/*
 @doc DOC_tcp44_
 ---------------------------------------------------------------
 Get DNS IP
 ---------------------------------------------------------------
 @clib  PPP_Client_Get_DNSIP | Get DNS IP. |
        <cfont>int PPP_Client_Get_DNSIP ( unsigned long far *IPaddress,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; int primary_sec, int *error );<efont> |
 @parm  int  | IPaddress  | Output parameter:<s2>DNS address is stored here.
 @parm  int  | primary_sec  | 1:<s2> Get primary DNS address<nl>
        2:<s2> Get secondary address.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#client<linkmid>code<linktail>, 0 on success.
 @rdesc 0  = Success, output parameter <code>IPaddress<codee> contains the DNS IP.<nl>
        -1 = Failure, see <code>error<codee> output parameter.<nl>
        -2 = Failure, PPP client is disabled by
        <linkto>../../config.htm#PPPCLIENT_ENABLE<linkmid>CHIP.INI<linktail> entry.<nl>

 @comm  This API function reports the DNS addresses as negotiated by
        the remote PPP server.
 @Also  tcp41.htm | PPP_Client_Open  | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x44<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.04 | V1.00 | V1.00 | V0.90 | V1.00
*/
int PPP_Client_Get_DNSIP (unsigned long far * IPaddress,
                          int primary_sec,
                          int *error)
{
    _BX = primary_sec ;
    _ES = FP_SEG(IPaddress);
    _DI = FP_OFF(IPaddress);

    _AH = PPPCLIE_GET_DNSIP ;
    asm { int TCPIPVECT  } ;
    *error = _DX;
    return _AX ;
}
#endif

/*************************************************************************/
// PPP client set options
/*************************************************************************/
#ifdef _tcp45_
/*
 @doc DOC_tcp45_
 ---------------------------------------------------------------
 Set PPP options for the PPP client
 ---------------------------------------------------------------
 @clib  PPP_Client_SetOptions | Set PPP options for the PPP client. |
        <cfont>int PPP_Client_SetOptions ( const PPP_Option far *ptr );<efont> |
 @parm  int  | ptr  | Pointer to an array of
        <linkto>../../tcpstruc.htm#PPP_Option<linkmid>PPP_Option<linktail>
        type data structures
 @rdesc Returns always 0.

        @comm If you want to use this function, you have to call it before opening
        a connection.<s2> <bold>Setting options during an established connection
        does not work!<bolde><s2>
        The settings are only valid for the next established connection.<s2>
        While establishing a connection the <code>PPP_Option<codee> structure
        referenced by the <code>ptr<codee> parameter must remain valid.<s2>
        After the
        <linkto>tcp41.htm<linkmid>PPP_Client_Open<linktail> function is finished, the structure
        can then be released.
        <nl>
        <nl>
        The array of data structures at <code>ptr<codee> is terminated by
        the first structure encountered with a NULL <code>optionValuePtr<codee>
        member.<nl>
        <nl>

        @raw
        // Simplified C-Example:
        unsigned int  ipcp_comp   = 1;
        unsigned long DNS_Pri_IP  = 0L;
        unsigned long DNS_Sec_IP  = 0L;

        PPP_Option My_Options[] = {

          // Allow remote to peer to use VJ TCPIP header compression.
          { PPP_IPCP_PROTOCOL, PPP_OPTION_ALLOW, PPP_IPCP_COMP_PROTOCOL,
              (const char *)&ipcp_comp, sizeof(ipcp_comp)},

          // Allow remote to peer to set primary DNS IP.
          { PPP_IPCP_PROTOCOL, PPP_OPTION_WANT, PPP_IPCP_DNS_PRI,
              (const char *)&DNS_Pri_IP, sizeof(DNS_Pri_IP)},

          // Allow remote to peer to set secondary DNS IP.
          { PPP_IPCP_PROTOCOL, PPP_OPTION_WANT, PPP_IPCP_DNS_SEC,
              (const char *)&DNS_Sec_IP, sizeof(DNS_Sec_IP)},

          // Terminate list of options.
          { 0, 0, 0, NULL, 0}
        } ;

        //***** call the functions like this ****

        // Install option with CLIB function
        PPP_Client_SetOptions(&My_Options[0]);  // Point to first member of array

        PPP_Client_Open(&pppclient);           // Open the connection

 @Also  tcp41.htm | PPP_Client_Open   | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x45<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00

*/
int PPP_Client_SetOptions (const PPP_Option far *ptr)
{
    _ES = FP_SEG(ptr);
    _DI = FP_OFF(ptr);

    _AH = PPPCLIENT_SET_OPTIONS ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif

/*************************************************************************/
//PPP client open  IPv6 address configuration
/*************************************************************************/
#ifdef _tcp46_
/*
 @doc DOC_tcp46_
 ---------------------------------------------------------------
 Open a PPP connection
 ---------------------------------------------------------------
 @clib  PPP_Client_Open_IPv6 | Open a PPP connection with IPv6 address configuration. |
        <cfont>int PPP_Client_Open_IPv6 ( PPPClient_Init_IPv6 far *ptr,<nl>
        <tab><tab><tab><tab><tab><tab><s2> int *error );<efont> |
 @parm  int  | ptr  | Pointer to a
        <linkto>../../tcpstruc.htm#PPPClient_Init_IPv6<linkmid>PPPClient_Init_IPv6<linktail>
        type  data structure (declared in tcpipapi.h)
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#client<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        -1 = Failure, see <code>error<codee> output parameter.<nl>
        -2 = Failure, PPP client is disabled by
        <linkto>../../config.htm#PPPCLIENT_ENABLE<linkmid>CHIP.INI<linktail> entry.<nl>

 @comm  IPv6 address configuration is done by an auto negotiation process.<s2>
        At connection time the peers negotiate an Interface-ID for the PPP device and
        auto configure their link-local scope addresses.<s2> After sucessful
        return of this function the  <cfont>PPPClieipAddrStr<efont> and
        <cfont>PPPClieRemipAddrStr<efont> members of the <cfont>PPPClient_Init_IPv6<efont>
        data structure are filled with the negotiated IPv6 addresses.<nl>
        <nl>
        On success, the structure at <code>ptr<codee> contains the needed
        IP data for further TCP/IP socket communication.<nl>
        <nl>
        Refer to the PPP6CLIE.C example for how to use this API.<s2>
        Also refer to
        <linkto>../../tcpstruc.htm#PPPClient_Init_IPv6<linkmid>PPPClient_Init_IPv6<linktail>
        data structure documentation.<nl>
        <nl>
        Note: <bold>Only one PPP client connection can be opened
        at a time!!<bolde><nl>
 @Also  tcp40.htm | PPP_Client_Installed  |
        tcp42.htm | PPP_Client_Close  |
        tcp43.htm | PPP_Client_GetStatus
 @Also  tcp41.htm | PPP_Client_Open  |
        | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x46<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V0.90 | V1.00

*/
int PPP_Client_Open_IPv6(PPPClient_Init_IPv6 far * ptr, int *error)
{
    _ES = FP_SEG(ptr) ;
    _DI = FP_OFF(ptr) ;
    _AH = PPPCLIENT_OPEN_IPV6;
    asm { int TCPIPVECT  } ;
    *error = _AX;
    return _DX ;
}
#endif

/*************************************************************************/
//PPP client  pause
/*************************************************************************/
#ifdef _tcp47_
/*
 @doc DOC_tcp47_
 ---------------------------------------------------------------
 Pause/resume the PPP client task
 ---------------------------------------------------------------
 @clib  PPP_Client_Pause | Pause/resume the PPP client task. |
        <cfont>int PPP_Client_Pause (int pause, int *error );<efont> |
 @parm  int  | pause  | 1: Pause the PPP client task<nl>0:resume.
 @parm  int  | error    | Output parameter:<s2>Failure code:<nl>
                         -1 Action not allowed due to the current state of the PPP client<nl>
                         -2 PPP client is not running (disabled)<nl>
                         -3 PPP client timeout (should not happen)<nl>
                         0 on success.

 @rdesc 0  = Success <nl>
        -1 = Failure, Action not allowed due to the current state of the PPP client.<nl>
        -2 = Failure, PPP client is disabled by
        <linkto>../../config.htm#PPPCLIENT_ENABLE<linkmid>CHIP.INI<linktail> entry.<nl>
        -3 = Failure PPP client response timeout (should not happen).<nl>


 @comm  If this API function is called with parameter <cfont>pause=1<efont>,
        the PPP client task stops listening for incoming data at its RS232 port.
        Also it stops sending of data via the serial port.<nl>
        The RS232 port of the PPP client is now ready to
        use for other purposes (e.g. for sending a SMS).<nl>
        The server must be resumed by a call of this function with parameter
        <cfont>pause==0<efont>.<nl>
        Please note:<nl>
        If the PPP client was halted during a running PPP session, the
        PPP session could be closed by the remote peer.<nl>
        Open TCP connections via the PPP device are possibly closed by the peers.<nl>
        The internal idle timeout counters are cleared, if the client task stay at the HALT state.<nl>

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x47<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   |  n/a  | n/a   | V1.30 | V1.30

 @target_clib V2.17

*/
int PPP_Client_Pause(int pause, int *error)
{
    _BX = pause;
    _AH = PPPCLIENT_PAUSE;
    asm { int TCPIPVECT  } ;
    *error = _DX;
    return _AX ;
}
#endif




/*************************************************************************/
//PPP server installed
/*************************************************************************/
#ifdef _tcp50_
/*
 @doc DOC_tcp50_
 ---------------------------------------------------------------
 Check if PPP server is installed
 ---------------------------------------------------------------
 @clib  PPP_Server_Installed | Check if PPP server is installed. |
        <cfont>int PPP_Server_Installed ( void );<efont> |
 @parm  int  |   | -- none --
 @rdesc zero: PPP server is not installed<nl>
        non-zero: PPP server is installed
 @comm  The CHIP.INI can specify that the PPP server not be
       <linkto>../../config.htm#PPPSERVER_ENABLE<linkmid>installed<linktail>.
 @Also  tcp52.htm | PPP_Server_Activate  |
        tcp70.htm |Get_Installed_Servers | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x50<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int PPP_Server_Installed (void)
{
    _AH = PPPSERVER_INSTALLED ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif


/*************************************************************************/
//PPP server suspend
/*************************************************************************/
#ifdef _tcp51_
/*
 @doc DOC_tcp51_
 ---------------------------------------------------------------
 Suspend the PPP server task
 ---------------------------------------------------------------
 @clib  PPP_Server_Suspend | Suspend the PPP server task. |
        <cfont>int PPP_Server_Suspend (int timeoutsecs, int *error );<efont> |
 @parm  int  | timeoutsecs  | Time-out in seconds.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm  This API function closes an active (if there is one) connection
        and blocks any activity of the PPP server.
        The PPP server can be (re)activated by
        <linkto>tcp52.htm<linkmid>PPP_Server_Activate<linktail>.<nl>
        Note that the time-out value in <code>timeoutsecs<codee>
        depends on your time-out entries for the modem commands
        specified in chip.ini.<s2> If this call returns with -1, the most
        likely reason is that the modem commands are not finished after
        specified time-out.<nl>
        After execution of this command the serial port and/or the connected modem
        can be used for othere purposes.

 @related Chip.ini   | ../../config.htm#PPPSERVERHANGUPTIMEOUTx
        | entry: | PPPSERVER HANGUPTIMEOUTx
        time-out in seconds for wait on answer from modem
 @Also  tcp52.htm | PPP_Server_Activate  |
        tcp53.htm | PPP_Server_GetStatus | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x51<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int PPP_Server_Suspend (int timeoutsecs, int *error)
{
    _BX = timeoutsecs ;
    _AH = PPPSERVER_SUSPEND ;
    asm { int TCPIPVECT  } ;
    *error = _DX;
    return _AX ;
}
#endif

/*************************************************************************/
//PPP server  activate
/*************************************************************************/
#ifdef _tcp52_
/*
 @doc DOC_tcp52_
 ---------------------------------------------------------------
 Activate the PPP server
 ---------------------------------------------------------------
 @clib  PPP_Server_Activate | Activate the PPP server. |
        <cfont>int PPP_Server_Activate ( int timeoutsecs, int *error );<efont> |
 @parm  int  | timeoutsecs  | Time-out in seconds.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>
 @comm  If successful, the PPP server is now able to serve a connection.<nl>
        <nl>
        Note that the time-out value in <code>timeoutsecs<codee>
        depends on your time-out entries for the modem commands
        specified in chip.ini.<s2> If this call returns with -1, the most
        likely reason is that the modem commands are not finished after
        specified time-out.<nl>
        If the PPP server is not installed at boot time (by chip.ini setting)
        and the function is called the first time, the timeoutsecs parameter has no effect.
        In that case the PPP Server interface and the receiver task become installed.
        During this phase the modem is initialized. The time for this initialization
        depends on your time-out entries for the modem commands specified in chip.ini.<nl>

 @Also  tcp51.htm | PPP_Server_Suspend  |
        tcp50.htm | PPP_Server_Installed  |
        tcp53.htm | PPP_Server_GetStatus
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x52<linkmid>documentation<linktail>
        for more details.
 @related Chip.ini   | ../../config.htm#PPPSERVERHANGUPTIMEOUTx
        | entry: | PPPSERVER HANGUPTIMEOUTx
        time-out in seconds for wait on answer from modem
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int PPP_Server_Activate (int timeoutsecs, int *error)
{
    _BX = timeoutsecs ;
    _AH = PPPSERVER_ACTIVATE ;
    asm { int TCPIPVECT  } ;
    *error = _DX;
    return _AX ;
}
#endif

/*************************************************************************/
//PPP server, get status
/*************************************************************************/
#ifdef _tcp53_
/*
 @doc DOC_tcp53_
 ---------------------------------------------------------------
 Get the current state of the PPP server
 ---------------------------------------------------------------
 @clib  PPP_Server_GetStatus | Get the current state of the PPP server. |
        <cfont>int PPP_Server_GetStatus ( void );<efont> |
 @parm  int  |   | -- none --
 @rdesc PPP server state defined below
 @comm  PPP server states:<nl>
        <ul>
       -2<s2> Server task is disabled by CHIP.INI
              <linkto>../../config.htm#PPPSERVERENABLE<linkmid>setting<linktail>,
              activation required with
              <linkto>tcp52.htm<linkmid>PPP_Server_Activate<linktail><nl>
        -1<s2>  Error state, should not happen<nl>
        1<s3>  Server suspended<nl>
        2<s3>  Server enabled, waiting for connection<nl>
        3<s3>  PPP connection is established<nl>
        4<s3>  Server tries to hang up modem<nl>
        5<s3>  Server tries to initialize modem<nl>
        6<s3>  Server halted by a call of
               <linkto>tcp57.htm<linkmid>PPP_Server_Pause()<linktail><nl>

        <ul>
 @Also  tcp51.htm | PPP_Server_Suspend  |
        tcp52.htm | PPP_Server_Activate  |
        tcp50.htm | PPP_Server_Installed
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x53<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int PPP_Server_GetStatus(void)
{
    _AH = PPPSERVER_GET_STATUS ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif


/*************************************************************************/
//PPP server  get config
/*************************************************************************/
#ifdef _tcp54_
/*
 @doc DOC_tcp54_
 ---------------------------------------------------------------
 Get configuration data of the PPP server
 ---------------------------------------------------------------
 @clib  PPP_Server_Get_Cfg | Get the current main configuration
        data of the PPP server . |
        <cfont>int PPP_Server_Get_Cfg ( PPP_IPCfg_Data far *ptr, int *error );<efont> |
 @parm  int  | ptr  | Output Parameter:<s2> Pointer to a
        <linkto>../../tcpstruc.htm#PPP_IPCfg_Data<linkmid>PPP_IPCfg_Data<linktail>
        type data structure which will be set by this function.
 @parm  int  | error | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc Non-zero = Failure (see <code>error<codee> output parameter)<nl>
        zero: The user structure <code>PPP_IPCfg_Data<codee> is filled with
        the PPP server configuration data<nl>
 @comm  This API applies to PPP server operating
        with IPv4 protocol.<s2>  Refer to
        <linkto>tcp56.htm<linkmid>PPP_Server_Get_Cfg_IPv6<linktail>
        API for IPv6 PPP server configuration access.
 @Also  tcp51.htm | PPP_Server_Suspend  |
        tcp53.htm | PPP_Server_GetStatus  |
        tcp52.htm | PPP_Server_Activate
 @Also  tcp55.htm | PPP_Server_SetOptions |
        tcp56.htm | PPP_Server_Get_Cfg_IPv6 | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x54<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int PPP_Server_Get_Cfg (PPP_IPCfg_Data far *ptr, int *error)
{
    _ES = FP_SEG(ptr);
    _DI = FP_OFF(ptr);
    _AH = PPPSERVER_GET_CFG ;
    asm { int TCPIPVECT  } ;
    *error = _DX;
    return _AX ;
}
#endif

/*************************************************************************/
// PPP server set options
/*************************************************************************/
#ifdef _tcp55_
/*
 @doc DOC_tcp55_
 ---------------------------------------------------------------
 Set PPP options for the PPP server
 ---------------------------------------------------------------
 @clib  PPP_Server_SetOptions | Set PPP options for the PPP server. |
        <cfont>int PPP_Server_SetOptions ( const PPP_Option far *ptr );<efont> |
 @parm  byte | ptr  | Pointer to an array of <code>PPP_Option<codee>
        <linkto>../../tcpstruc.htm#PPP_Option<linkmid>type<linktail>
        data structures (defined in tcpipapi.h).
 @rdesc 0:<s2> Success, options will be installed as shown below.
 @comm  It is only possible to set PPP options when the PPP server is suspended.<s2>
        (PPP server status reported by
        <linkto>tcp53.htm<linkmid>PPP_Server_GetStatus<linktail> must be 1.)<s2>
        Setting options when the PPP server is active
        (states 2, 3, 4 and 5) does not have any effect.<s2>
        The installed options take affect when the PPP server is activated.<s2>
        If you want to reset the options, call this function with a
        null <code>ptr<codee> parameter.<nl>
        <nl>
        The array of data structures at <code>ptr<codee> is terminated by
        the first structure encountered with a NULL <code>optionValuePtr<codee>
        member.<nl>

        @raw

        //  Simplified C-Example:
        unsigned int  ipcp_comp   = 1;
        unsigned long DNS_Pri_IP  = 0L;
        unsigned long DNS_Sec_IP  = 0L;

        static PPP_Option My_Options[] = {
          // Allow remote to peer to use VJ TCPIP header compression.
          { PPP_IPCP_PROTOCOL, PPP_OPTION_ALLOW, PPP_IPCP_COMP_PROTOCOL,
             (const char *)&ipcp_comp, sizeof(ipcp_comp)},

          // Allow remote to peer to set primary DNS IP, but do no request for it.
          { PPP_IPCP_PROTOCOL, PPP_OPTION_ALLOW, PPP_IPCP_DNS_PRI,
             (const char *)&DNS_Pri_IP, sizeof(DNS_Pri_IP)},

          // Allow remote to peer to set secondary DNS IP, but do no request for it.
          { PPP_IPCP_PROTOCOL, PPP_OPTION_ALLOW, PPP_IPCP_DNS_SEC,
             (const char *)&DNS_Sec_IP, sizeof(DNS_Sec_IP)},

          { 0, 0, 0, NULL, 0}   // End of array marker
        } ;

        //*****call the functions like this****

        PPP_Server_Suspend(20);                 // Suspend the PPP server
        // Install option with CLIB function
        PPP_Server_SetOptions(&My_Options[0]);  // point to first member of array

        PPP_Server_Activate(20);                // Activate

 @Also  tcp51.htm | PPP_Server_Suspend  |
        tcp53.htm | PPP_Server_GetStatus  |
        tcp52.htm | PPP_Server_Activate
 @Also  tcp54.htm | PPP_Server_Get_Cfg  | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x55<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.03 | V1.00 | V1.00 | V0.90 | V1.00

*/
int PPP_Server_SetOptions (const PPP_Option far * ptr)
{
    _ES = FP_SEG(ptr);
    _DI = FP_OFF(ptr);
    _AH = PPPSERVER_SET_OPTIONS ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif

/*************************************************************************/
//PPP server  get config (IPv6)
/*************************************************************************/
#ifdef _tcp56_
/*
 @doc DOC_tcp56_
 ---------------------------------------------------------------
 Get configuration data of the PPP server
 ---------------------------------------------------------------
 @clib  PPP_Server_Get_Cfg_IPv6 | Get the current main configuration
        data of the PPP server. |
        <cfont>int PPP_Server_Get_Cfg_IPv6 (<nl>
        <tab><tab><tab><tab><tab> PPP_IPCfg_Data_IPv6 far *ptr,<nl>
        <tab><tab><tab><tab><tab> int *error );<efont> |
 @parm  int  | ptr  | Output parameter:<s2>Pointer to a
        <linkto>../../tcpstruc.htm#PPP_IPCfg_Data_IPv6<linkmid>PPP_IPCfg_Data_IPv6<linktail>
        type data structure which will be set by this function.
 @parm  int  | error | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc Non-zero = Failure (see <code>error<codee> output parameter)<nl>
        zero: The user structure <code>PPP_IPCfg_Data_IPv6<codee> is filled with
        the PPP server configuration data<nl>
 @comm  Only PPP IPv6 connections are supported by this API.<s2>
        IPv6 address configuration is done by an auto negotiation process.<s2>
        At connection time, the peers negotiate an Interface-ID for the PPP device and
        auto configure their link-local scope addresses.<nl>
        <nl>
        Refer to <linkto>tcp54.htm<linkmid>PPP_Server_Get_Cfg<linktail>
        API for IPv4 PPP server configuration access.
 @Also  tcp51.htm | PPP_Server_Suspend  |
        tcp53.htm | PPP_Server_GetStatus  |
        tcp52.htm | PPP_Server_Activate
 @Also  tcp55.htm | PPP_Server_SetOptions |
        tcp54.htm | PPP_Server_Get_Cfg | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x56<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V0.90 | V1.00
*/
int PPP_Server_Get_Cfg_IPv6(PPP_IPCfg_Data_IPv6 far *ptr, int *error)
{
    _ES = FP_SEG(ptr);
    _DI = FP_OFF(ptr);
    _AH = PPPSERVER_GET_CFG_IPV6;
    asm { int TCPIPVECT  } ;
    *error = _DX;
    return _AX ;
}
#endif



/*************************************************************************/
//PPP server  pause
/*************************************************************************/
#ifdef _tcp57_
/*
 @doc DOC_tcp57_
 ---------------------------------------------------------------
 Pause/resume the PPP server task
 ---------------------------------------------------------------
 @clib  PPP_Server_Pause | Pause/resume the PPP server task. |
        <cfont>int PPP_Server_Pause (int pause, int *error );<efont> |
 @parm  int  | pause  | 1: Pause the PPP server task<nl>0:resume.
 @parm  int  | error    | Output parameter:<s2>Failure code:<nl>
                         -1 Action not allowed due to the current state of the PPP server<nl>
                         -2 PPP server is not running (disabled)<nl>
                         -3 PPP server timeout (should not happen)<nl>
                         0 on success.

 @rdesc 0 = success <nl>
        Non-zero = Failure (see <code>error<codee> output parameter)<nl>

 @comm  If this API function is called with parameter <cfont>pause=1<efont>,
        the PPP server stops listening for incoming data at its RS232 port.
        Also it stops sending of data via the serial port.<nl>
        The RS232 port of the PPP server is now ready to
        use for other purposes (e.g. for sending a SMS).<nl>
        The server must be resumed by a call of this function with parameter
        <cfont>pause==0<efont>.<nl>
        Please note:<nl>
        If the PPP server was halted during a running PPP session, the
        PPP session could be closed by the remote peer.<nl>
        Open TCP connections via the PPP device are possibly closed by the peers.<nl>
        The internal idle timeout counters are cleared, if the server stay at the HALT state.<nl>

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x57<linkmid>documentation<linktail>
        for more details.
        
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.30 | V1.30

 @target_clib V2.17

*/

int PPP_Server_Pause(int pause, int *error)
{
    _BX = pause;
    _AH = PPPSERVER_PAUSE;
    asm { int TCPIPVECT  } ;
    *error = _DX;
    return _AX ;
}
#endif





/*************************************************************************/
//Get pointer to internal TCIP SNMP mib structures
/*************************************************************************/
#ifdef _tcp60_
/*
 @doc DOC_tcp60_
 ---------------------------------------------------------------
 Get internal TCP/IP SNMP variables
 ---------------------------------------------------------------
 @clib  Get_SNMP_Data | Get internal TCP/IP SNMP variables. |
        <cfont>int Get_SNMP_Data ( unsigned char which,<nl>
        <tab><tab><tab><tab><tab>void far * *snmp_mib_ptr );<efont> |
 @parm  int  | which  | Specifies which data to access.<nl>
        <ul>
         1:<s2>  Get pointer to
        <linkto>../../tcpstruc.htm#IfMib<linkmid>IfMib<linktail>
        data structure<nl>
         2:<s2> Get pointer to
         <linkto>../../tcpstruc.htm#IpMib<linkmid>IpMib<linktail>
         data structure<nl>
         3:<s2>  Get pointer to
         <linkto>../../tcpstruc.htm#IcmpMib<linkmid>IcmpMib<linktail>
         data structure<nl>
         4:<s2> Get pointer to
         <linkto>../../tcpstruc.htm#TcpMib<linkmid>TcpMib<linktail>
         data structure<nl>
         5:<s2>  Get pointer to
         <linkto>../../tcpstruc.htm#UdpMib<linkmid>UdpMib<linktail>
         data structure<nl>
         6:<s2>  Get pointer to
         <linkto>../../tcpstruc.htm#atEntry<linkmid>atEntry<linktail>
         data structure<nl>
         <ule>
 @parm  int  | snmp_mib_ptr  | Output Parameter:<s2> Pointer to a
         far pointer in user memory which will be set with a pointer
         to requested object time within the @CHIP-RTOS memory space.<nl>
 @rdesc non-zero : BIOS without internal SNMP mib variables<nl>
        0:  Location refereced by <code>snmp_mib_ptr<codee> contains a pointer
        to the structure<nl>
 @comm  This API provides access to the internal TCP/IP variables
        which will be required if the user is to implement a SNMP (Simple
        Network Management Protocol) agent.<nl>
        <nl>
 @commtarget SC1x3/SC2x  | This API currently only supports IPv4 protocol.
 @commtarget SC1x  | These structures are only available in @CHIP-RTOS versions
        which contain the SNMP option.<s2> A SNMP agent is not part of the @CHIP-RTOS.<nl>
        <nl>
        The SNMP variables are not a part of our current official 6 SC1x @CHIP-RTOS
        versions.<s2> You must order directly an SC1x @CHIP-RTOS version which includes
        this feature.<nl>
 @Also  tcp78.htm | Get_TCPIP_Memory_Status  |
        tcp74.htm | Get_TCPIP_Statistics  |
        tcp60a.htm | Get_SNMP_DataEx

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x60<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
int Get_SNMP_Data(unsigned char which , void far * * snmp_mib_ptr)
{
    unsigned int es_reg ;
    _AL = which ;
    _AH = API_SNMP_GET ;
    asm { int TCPIPVECT  } ;
    if(_AX==0)
    {
       es_reg = _ES ;
       *snmp_mib_ptr = (void far *)MK_FP(es_reg, _DI) ;
       return 0;
    }
    return _AX;
}
#endif


#ifdef _tcp60a_
/*
 @doc DOC_tcp60a_
 ---------------------------------------------------------------
 Get internal TCP/IP SNMP variables
 ---------------------------------------------------------------
 @clib  Get_SNMP_DataEx | Get internal TCP/IP SNMP variables (Extended). |
        <cfont>int Get_SNMP_DataEx ( unsigned char which,<nl>
        <tab><tab><tab><tab><tab>&nbsp; void far * *snmp_mib_ptr,<nl>
        <tab><tab><tab><tab><tab>&nbsp; int *max );<efont> |
 @parm  int  | which  | Specifies which data to access.<nl>
        <nl>
        1:<s2>   Get pointer to
        <linkto>../../tcpstruc.htm#IfMib<linkmid>IfMib<linktail>
        data structure<nl>
         2:<s2>   Get pointer to
         <linkto>../../tcpstruc.htm#IpMib<linkmid>IpMib<linktail>
         data structure<nl>
         3:<s2>   Get pointer to
         <linkto>../../tcpstruc.htm#IcmpMib<linkmid>IcmpMib<linktail>
         data structure<nl>
         4:<s2>   Get pointer to
         <linkto>../../tcpstruc.htm#TcpMib<linkmid>TcpMib<linktail>
         data structure<nl>
         5:<s2>   Get pointer to
         <linkto>../../tcpstruc.htm#UdpMib<linkmid>UdpMib<linktail>
         data structure<nl>
         6:<s2>   Get pointer to
         <linkto>../../tcpstruc.htm#atEntry<linkmid>atEntry<linktail>
         data structure<nl>
         7:<s2>   Set array of pointers to
         <linkto>../../tcpstruc.htm#IfMib<linkmid>IfMib<linktail>
         entries of all current open TCP/IP device interfaces (Local Loopback,
         Ethernet, PPP server, PPP client).<s2> The value at
         <cfont>max<efont> must specify the maximum number of pointers in this array.<nl>
         8:<s2> Get pointer to unsigned long <i>system up-time<ie> variable (100 Hz counter).<nl>
 @parm  int  | snmp_mib_ptr  |
         Output Parameter:<nl>
         <nl>
         For cases where <cfont>which<efont> is not set to 7, this is a
         pointer to a single far pointer in user memory which will be set by this API
         with a pointer to requested object within the @CHIP-RTOS memory space.<nl>
         <nl>
         For case where <cfont>which<efont> is set to 7, this is a pointer to
         an array of far pointers within the caller's memory.<s2>
         This array will be set by this API call with pointers to
         <linkto>../../tcpstruc.htm#IfMib<linkmid>IfMib<linktail>
         data structures located in @CHIP-RTOS memory.<s2> One pointer for each device
         interface will be reported, up to a maximum limited by the count specified
         at the <cfont>max<efont> input parameter.
 @parm  int  | max  | Input/Output Parameter:<s2> This parameter only applies
         to case where <cfont>which<efont> is set to 7.<s2> It is otherwise not used.<s2>
         For <cfont>which<efont> case 7, this location must be preset by caller to
         the number of pointers in the array referenced by the
         <cfont>snmp_mib_ptr<efont> input parameter.<s2>  On return, the referenced
         count will indicate the number of devices for which
         <linkto>../../tcpstruc.htm#IfMib<linkmid>IfMib<linktail> pointers have
         been listed in the <cfont>snmp_mib_ptr<efont> output array.
 @rdesc non-zero : RTOS version  without internal SNMP mib variables<nl>
        0:  Location refereced by <code>snmp_mib_ptr<codee> contains a pointer
        to the structure<nl>
 @comm  This API provides access to the internal TCP/IP variables
        which will be required if the user is to implement a SNMP (Simple
        Network Management Protocol) agent.<nl>
 @commtarget SC1x3/SC2x  | This API currently only supports IPv4 protocol.
 @commtarget SC1x  | These structures are only available in @CHIP-RTOS versions
        which contain the SNMP option.<s2> A SNMP agent is not part of the @CHIP-RTOS.<nl>
        <nl>
        The SNMP variables are not a part of our current official 6 SC1x @CHIP-RTOS
        versions.<s2> You must order directly an SC1x @CHIP-RTOS version which includes
        this feature.<nl>
 @Also  tcp78.htm | Get_TCPIP_Memory_Status  |
        tcp74.htm | Get_TCPIP_Statistics  |
        tcp60.htm | Get_SNMP_Data
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x60<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.01 | V1.00 | V1.00 | V0.90 | V1.00
*/
int Get_SNMP_DataEx(unsigned char which , void far * * snmp_mib_ptr, int * max)
{
   unsigned int es_reg;
   if (which == 7)
   {
      _CX = *max;
      asm push ds
      _DS = FP_SEG(snmp_mib_ptr) ;      // Not necessarily a far ptr
      _SI = FP_OFF(snmp_mib_ptr) ;
   }
   asm{
         mov al,which
         mov ah,API_SNMP_GET
         int TCPIPVECT
   }
   if(_AX==0)
   {
      if (which != 7)
      {
        es_reg = _ES;
        *snmp_mib_ptr = (void *)MK_FP(es_reg,_DI);
      }
      else
      {
          // Note: 'max' may be a near pointer, so we must restore DS
          //       before de-referencing 'max'.
        asm pop ds
        *max =  _CX;
      }
      return 0;
   }
   return _AX;
}
#endif

/*************************************************************************/
//FTP server: Return the addresss of the FTPserver login counters
/*************************************************************************/
#ifdef _tcp65_
/*
 @doc DOC_tcp65_
 ---------------------------------------------------------------
 Access the FTP server login counters
 ---------------------------------------------------------------
 @clib1 Get_FTP_Login_Counters | Access the FTP server login counters. |
        <cfont>int Get_FTP_Login_Counters (<nl>
        <tab><tab><tab><tab><tab>unsigned long far * * FTP_Login_Count,<nl>
        <tab><tab><tab><tab><tab>unsigned long far * * FTP_Login_failCount );<efont> |
 @parm  int  | FTP_Login_Count  | Output parameter:<s2>  A far pointer to the
        32 bit login counter will be output to the location pointed to by this
        parameter.<s2>  On failure, a NULL pointer is output here.
 @parm  int  | FTP_Login_failCount  | Output parameter:<s2>  A far pointer to the
        32 bit login fail counter will be output to the location pointed to by
        this parameter.<s2>  On failure, a NULL pointer is output here.
 @rdesc 0:  success <nl>
        non-zero:  @CHIP-RTOS doesn't support FTP server
        pointers are set to NULL).
 @Also  tcp66.htm | Get_Telnet_Login_Counters  | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x65<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.01 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Get_FTP_Login_Counters(unsigned long far *  * FTP_Login_Count,
                           unsigned long far *  * FTP_Login_failCount)
{
    int error_code ;
    unsigned int es_reg, ds_reg ;

    _AH = API_FTP_GET_LOGIN ;
    asm { push DS } ;
    asm { int TCPIPVECT  } ;
    error_code = _AX ;
    ds_reg = _DS ;
    es_reg = _ES ;
    asm { pop DS } ;

    if (error_code != 0)
    {
        es_reg = 0 ;
        ds_reg = 0 ;
        _DI = 0 ;
        _SI = 0 ;
    }
    *FTP_Login_Count     = (unsigned long far *)MK_FP(es_reg, _DI);
    *FTP_Login_failCount = (unsigned long far *)MK_FP(ds_reg, _SI);

    return error_code ;
}
#endif

/*************************************************************************/
//Telnet server: Return the addresss of the Telnetserver login counters
/*************************************************************************/
#ifdef _tcp66_
/*
 @doc DOC_tcp66_
 ---------------------------------------------------------------
 Access the Telnet server login counters
 ---------------------------------------------------------------
 @clib1 Get_Telnet_Login_Counters | Access the Telnet server login counters. |
        <cfont>int Get_Telnet_Login_Counters(<nl>
        <tab><tab><tab><tab> unsigned long far * * Telnet_Login_Count,<nl>
        <tab><tab><tab><tab> unsigned long far * * Telnet_Login_failCount);<efont> |
 @parm  int  | Telnet_Login_Count  | Output parameter:<s2>  A far pointer to the
        32 bit login counter will be output to the location pointed to by this
        parameter.<s2>  On failure, a NULL pointer is output here.
 @parm  int  | Telnet_Login_failCount  | Output parameter:<s2>  A far pointer to the
        32 bit login fail counter will be output to the location pointed to by
        this parameter.<s2>  On failure, a NULL pointer is output here.
 @rdesc 0:  success <nl>
        non-zero:  @CHIP-RTOS doesn't support Telnet server
        (pointers are set to NULL).
 @Also  tcp65.htm | Get_FTP_Login_Counters  | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x66<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.01 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Get_Telnet_Login_Counters(unsigned long far *  * Telnet_Login_Count,
                              unsigned long far *  * Telnet_Login_failCount)
{
    int error_code ;
    unsigned int es_reg, ds_reg ;

    _AH = API_TELNET_GET_LOGIN ;
    asm { push DS } ;
    asm { int TCPIPVECT  } ;
    error_code = _AX ;
    ds_reg = _DS ;
    es_reg = _ES ;
    asm { pop DS } ;

    if (error_code != 0)
    {
        es_reg = 0 ;
        ds_reg = 0 ;
        _DI = 0 ;
        _SI = 0 ;
    }
    *Telnet_Login_Count     = (unsigned long far *)MK_FP(es_reg, _DI);
    *Telnet_Login_failCount = (unsigned long far *)MK_FP(ds_reg, _SI);

    return error_code ;
}
#endif

/*************************************************************************/
//Get telnet state
/*************************************************************************/
#ifdef _tcp67_
/*
 @doc DOC_tcp67_
 ---------------------------------------------------------------
 Check if have an active telnet session
 ---------------------------------------------------------------
 @clib  Get_Telnet_State | Check if have an active telnet session. |
        <cfont>int Get_Telnet_State ( int *error );<efont> |

 @parm  int  | error | Output parameter:<s2><nl>
         0:  ok<nl>
        -1:  (SC1x only) RTOS variant doesn't support Telnet server

 @rdesc
         0:  no Telnet session<nl>
         1:  Telnet session is active<nl>
        -1:  (SC1x only) RTOS variant doesn't support Telnet server

 @Also  tcp66.htm | Get_Telnet_Login_Counters  |
        tcp70.htm | Get_Installed_Servers  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x67<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.01 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Get_Telnet_State ( int *error)
{
    _AH = API_GET_TELNET_STATE ;
    asm { int TCPIPVECT  } ;

    *error = _DX;
    return _AX;
}
#endif



/*************************************************************************/
//Get installed servers and devices of the SC12
/*************************************************************************/
#ifdef _tcp70_
/*
 @doc DOC_tcp70_
 ---------------------------------------------------------------
 Get information about running servers
 ---------------------------------------------------------------
 @clib  Get_Installed_Servers | Get information about running servers
        and interfaces of the TCP/IP Stack. |
        <cfont>void Get_Installed_Servers ( unsigned int far* first,<nl>
        <tab><tab><tab><tab><tab><tab><tab> unsigned int far* second );<efont> |
 @parm  int  | first    | The first eight possible available servers:<nl>
        <ul>
         Bit 0: GIS_ETHERNET - Ethernet device<nl>
         Bit 1: GIS_PPP_SERVER  - PPP server<nl>
         Bit 2: GIS_PPP_CLIENT - PPP client<nl>
         Bit 3: GIS_WEB_SERVER - Web server<nl>
         Bit 4: GIS_TELNET_SERVER - Telnet server<nl>
         Bit 5: GIS_FTP_SERVER - FTP server<nl>
         Bit 6: GIS_TFTP_SERVER - TFTP server<nl>
         Bit 7: GIS_DHCP - DHCP client<nl>
         <ule>
 @parm  int  | second    | The next eight possible available servers:<nl>
         <ul>
         Bit 0: GIS_SNMP_MIB - SNMP MIB variables support<nl>
         Bit 1: GIS_CFG_SERVER - UDP Config server<nl>
         Bit 2: GIS_PING_CLIENT - Ping client<nl>
         <ule>
 @rdesc -- none --
 @comm  The masked listed here are defined in the tcpip.h header file.<nl>
 @Also  tcp50.htm | PPP_Server_Installed  |
        tcp40.htm | PPP_Client_Installed  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x70<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.01 | V1.00 | V1.00 | V0.90 | V1.00

*/
void Get_Installed_Servers ( unsigned int far *first, unsigned int far *second )
{
    _AH = GET_INSTALLED_SERVERS ;
    asm { int TCPIPVECT  } ;
    *first = _AX;
    *second = _DX;
}
#endif

/*************************************************************************/
//Reconfigure Ethernet interface
/*************************************************************************/
#ifdef _tcp71_
/*
 @doc DOC_tcp71_
 ---------------------------------------------------------------
 Reconfigure Ethernet interface
 ---------------------------------------------------------------
 @clib  Reconfigure_ethernet | Reconfigure Ethernet interface after
        changing the IP configuration. |
        <cfont>int Reconfigure_ethernet ( void );<efont> |
 @parm  int  |   | -- none --.
 @rdesc 0:  success <nl>
        non-zero:  error <linkto>../../iperrlst.htm<linkmid>code<linktail><nl>
        <nl>
        (Error code 237 indicates that an Ethernet interface configuration was
        already in progress.)
 @comm  A new IP configuration set with the prompt
        <linkto>../../command.htm#IP_address<linkmid>commands<linktail>
        <cfont>ip<efont>, <cfont>netmask<efont> and
        <cfont>gateway<efont> (or the corresponding library
        <linkto>tcpIPW.htm<linkmid>Set_IPConfig<linktail> call)
        becomes valid after a successful call to this function.<nl>
        <nl>
        If DHCP is changed from 1 to 0 then a new IP address, subnet mask
        and gateway should be set with the prompt
        <linkto>../../command.htm#IP_address<linkmid>commands<linktail>
        <cfont>ip<efont>, <cfont>netmask<efont> and <cfont>gateway<efont>
        or <linkto>tcpIPW.htm<linkmid>Set_IPConfig<linktail>
        library call.
 @Also  tcpIPW.htm | Set_IPConfig  |
        tcp72.htm | DHCP_use  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x71<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Reconfigure_ethernet(void)
{
    _AH = REINIT_ETHERNET ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif

/*************************************************************************/
//DHCP use   dhcp_use 0/1
/*************************************************************************/
#ifdef _tcp72_
/*
 @doc DOC_tcp72_
 ---------------------------------------------------------------
 Set/Reset DHCP usage on the Ethernet interface
 ---------------------------------------------------------------
 @clib  DHCP_use | Set/Reset DHCP usage on the Ethernet interface. |
        <cfont>int DHCP_use ( unsigned char dhcp_use );<efont>  |
 @parm  int  | dhcp_use  | 0: do not use DHCP, 1: Use DHCP.
 @rdesc 0:  success <nl>
        non-zero:  DHCP not available in this RTOS version.
 @comm  This entry becomes valid only after rebooting the system  or after
        calling the
        <linkto>tcp71.htm<linkmid>Reconfigure_ethernet<linktail>
        library function.<nl>
        <nl>
        If DHCP is changed from 1 to 0 then a new IP address, subnet mask
        and gateway should be set with either the
        prompt <linkto>../../command.htm#IP_address<linkmid>commands<linktail>
        or the <linkto>tcpIPW.htm<linkmid>Set_IPConfig<linktail>
        library call.<nl>
 @Also  tcp71.htm  | Reconfigure_ethernet  |
        tcpIPW.htm | Set_IPConfig  |
        tcp73.htm  | Get_DHCP_Status
 @Also  tcp73a.htm | Get_DHCP_Status_Ext  | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x72<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int DHCP_use(unsigned char dhcp_use)
{
    _AL = dhcp_use ;
    _AH = DHCP_USE ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif

/*************************************************************************/
//DHCP Stat
/*************************************************************************/
#ifdef _tcp73_
/*
 @doc DOC_tcp73_
 ---------------------------------------------------------------
 Get DHCP status of the Ethernet interface
 ---------------------------------------------------------------
 @clib  Get_DHCP_Status | Get DHCP status of the Ethernet interface. |
        <cfont>void Get_DHCP_Status ( unsigned int *dhcp_use,<nl>
        <tab><tab><tab><tab> unsigned int *dhcp_stat );<efont> |
 @parm  int  | dhcp_use  | Output parameter:<s2>Pointer to a where
        a "DHCP in use" boolean value will be output to.<s2>The
        location will be set to '1' if the DHCP is currently being
        used and '0' if not in use.
 @parm  int  | dhcp_stat  | Output parameter:<s2>Pointer to a where
        a DHCP status word will be stored.<s2> The status is encoded
        as follows:<nl>
        <ul>
          0: System is not configured (is in progress)<nl>
          1: System is configured by a DHCP Server<nl>
          2: System configure retry failed (or no retry started before)<nl>
        <ule>
 @rdesc  -- none --
 @Also  tcp73a.htm | Get_DHCP_Status_Ext  |
        tcp72.htm  | DHCP_use | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x73<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
void Get_DHCP_Status(unsigned int * dhcp_use, unsigned int *dhcp_stat)
{
    asm push DI

    _AH = DHCP_STAT ;
    asm { int TCPIPVECT  } ;

    asm pop DI
    
    *dhcp_use  = _AX ;
    *dhcp_stat = _DX ;
}
#endif


/*************************************************************************/
//DHCP Stat extended function with getting dhcp config data
//(requires BIOS 1.03B or higher)
/*************************************************************************/
#ifdef _tcp73a_
/*
 @doc DOC_tcp73a_
 ---------------------------------------------------------------
 Get DHCP status of the Ethernet interface
 ---------------------------------------------------------------
 @clib  Get_DHCP_Status_Ext | Get DHCP status of the Ethernet interface. |
        <cfont>void Get_DHCP_Status_Ext ( unsigned int *dhcp_use,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; unsigned int *dhcp_stat,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; UserEthDhcp_Entry far * *dhcpptr );<efont> |
 @parm  int  | dhcp_use  | Output parameter:<s2>Pointer to a where
        a "DHCP in use" boolean value will be output to.<s2>The
        location will be set to '1' if the DHCP is currently being
        used and '0' if not in use.
 @parm  int  | dhcp_stat  | Output parameter:<s2>Pointer to a where
        a DHCP status word will be stored.<s2> The status is encoded
        as follows:<nl>
        <ul>
          0: System is not configured (is in progress)<nl>
          1: System is configured by a DHCP Server<nl>
          2: System configure retry failed (or no retry started before)<nl>
        <ule>
 @parm  int | dhcpptr | Output Parameter:<s2>Pointer to a pointer that will
        be set by this API call, referencing a
        <linkto>../../tcpstruc.htm#UserEthDhcp_Entry<linkmid>UserEthDhcp_Entry<linktail>
        data structure within @CHIP-RTOS memory.<s2>
        This structure will contain some DHCP configuration data (read-only!).<s2>
        If no data is available the pointer will be set to NULL.
 @rdesc -- none --
 @comm  The UserEthDhcp_Entry data is a read-only information.<s2>
        Do not write to this data structure!
 @Also  tcp73.htm | Get_DHCP_Status  |
        tcp72.htm | DHCP_use | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x73<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
void Get_DHCP_Status_Ext(unsigned int * dhcp_use, unsigned int *dhcp_stat, UserEthDhcp_Entry far * * dhcpptr)
{
    unsigned int es_reg;
    unsigned int di_reg;

    _AH = DHCP_STAT ;
    asm { int TCPIPVECT  } ;
    es_reg = _ES;
    di_reg = _DI;
    *dhcp_use  = _AX ;
    *dhcp_stat = _DX ;
    if (_DX != 1)
    {
        es_reg =
        di_reg = 0 ;
    }

    *dhcpptr = (UserEthDhcp_Entry far *) MK_FP(es_reg, di_reg);
    return;
}
#endif
/*************************************************************************/
//return the address of TCP/IP packet counter struct
/*************************************************************************/
#ifdef _tcp74_
/*
 @doc DOC_tcp74_
 ---------------------------------------------------------------
 Access the internal network packet counter
 ---------------------------------------------------------------
 @clib  Get_TCPIP_Statistics | Access the internal network packet counters. |
        <cfont>void Get_TCPIP_Statistics ( Packet_Count far * *pkt_cnt_ptr );<efont> |
 @parm  int | pkt_cnt_ptr | Output Parameter:<s2>Pointer to location in
        user memory which will receive a pointer to a
        <linkto>../../tcpstruc.htm#Packet_Count<linkmid>Packet_Count<linktail>
        data structure residing in @CHIP-RTOS memory space (read-only!).<s2> This
        referenced @CHIP-RTOS data structure contains further
        pointers to the counters for each protocol.
 @rdesc -- none --
 @comm  The counters referenced by <code>Packet_Count<codee>
        data structure members
       <code>count_all_packets<codee> and <code>cnt_all_sended_packets<codee>
       count only Ethernet packets.<nl>
       <nl>
       Other counters referenced also count the packets from and
       to other devices: e.g. local loop back packets and PPP packets.<nl>
       <nl>
       The user is free to read and/or reset any of these referenced
       counters.<nl>
 @Also tcp78.htm | Get_TCPIP_Memory_Status  |
       tcp60.htm | Get_SNMP_Data  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x74<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
void Get_TCPIP_Statistics ( Packet_Count far * * pkt_cnt_ptr )
{
    unsigned es_reg;
    _ES = 0 ;
    _DI = 0 ;       // [ES:DI] remains null if no TCP/IP in RTOS.

    _AH = TCPIP_STATISTICS ;
    asm { int TCPIPVECT  } ;
    es_reg = _ES;
    *pkt_cnt_ptr = (Packet_Count far *)MK_FP(es_reg, _DI);
}
#endif

/*************************************************************************/
//ping open
/*************************************************************************/
#ifdef _tcp75_
/*
 @doc DOC_tcp75_
 ---------------------------------------------------------------
 Open and start ICMP echo requests
 ---------------------------------------------------------------
 @clib  Ping_Open | Open and start ICMP echo requests. |
        <cfont>int Ping_Open ( Ping far *pingptr, int *error );<efont> |
 @parm  int  | pingptr  | Pointer to user's  <code>Ping<codee>
        <linkto>../../tcpstruc.htm#Ping<linkmid>structure<linktail>.<nl>
        The contents of this structure will be initialized by this
        function call.
        <nl>
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -2: Ping API not supported by RTOS version<nl>
        -1:  Failure, see reported <code>error<codee> code.<nl>
        <gt>= 0:  Socket descriptor<nl>
 @Also  tcp76.htm | Ping_Close  |
        tcp77.htm | Ping_Statistics | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x75<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Ping_Open (Ping far * pingptr, int * error)
{
    _ES = FP_SEG(pingptr);
    _DI = FP_OFF(pingptr);
    _AH = PING_OPEN ;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX ;
}
#endif

/*************************************************************************/
//ping close
/*************************************************************************/
#ifdef _tcp76_
/*
 @doc DOC_tcp76_
 ---------------------------------------------------------------
 Finish ICMP echo requests
 ---------------------------------------------------------------
 @clib  Ping_Close | Stop ICMP echo requests. |
        <cfont>int Ping_Close ( int sd );<efont> |
 @parm  int  | sd  | Socket descriptor.
 @rdesc -2: Ping API not supported by RTOS<nl>
        -1: Ping close failed, should not happen, only if socket
        descriptor is invalid<nl>
        0: Success<nl>
 @Also  tcp75.htm | Ping_Open |
        tcp77.htm | Ping_Statistics  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x76<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Ping_Close (int sd)
{
    _BX = sd ;
    _AH = PING_CLOSE ;
    asm { int TCPIPVECT  } ;
    return _DX ;
}
#endif

/*************************************************************************/
//ping statistics
/*************************************************************************/
#ifdef _tcp77_
/*
 @doc DOC_tcp77_
 ---------------------------------------------------------------
 Retrieve ping information
 ---------------------------------------------------------------
 @clib  Ping_Statistics | Retrieve ping information. |
        <cfont>int Ping_Statistics ( Ping far *pingptr );<efont> |
 @parm  int  | pingptr  | Output parameter:<s2>
        Pointer to user's  <code>Ping<codee>
        <linkto>../../tcpstruc.htm#Ping<linkmid>structure<linktail>
        from the
        <linkto>tcp75.htm<linkmid>Ping_Open<linktail> call.<nl>
 @rdesc -2: Ping API not supported by RTOS version<nl>
        -1: Failure<nl>
        0: Success<nl>
 @comm  The structure at <code>pingptr<codee> is filled with
        the ping statistics.<nl>
 @Also  tcp75.htm | Ping_Open  |
        tcp76.htm | Ping_Close | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x77<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Ping_Statistics(Ping far * pingptr)
{
    _ES = FP_SEG(pingptr);
    _DI = FP_OFF(pingptr);
    _AH = PING_STATISTICS ;
    asm { int TCPIPVECT  } ;
    return _DX ;
}
#endif

/*************************************************************************/
//memory
/*************************************************************************/
#ifdef _tcp78_
/*
 @doc DOC_tcp78_
 ---------------------------------------------------------------
 Get information about TCP/IP stack memory usage
 ---------------------------------------------------------------
 @clib  Get_TCPIP_Memory_Status | Get information about TCP/IP stack
        memory usage. |
        <cfont>void Get_TCPIP_Memory_Status ( unsigned long far *total,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; unsigned long far *used );<efont> |
 @parm  int  | total  | Output parameter:<s2>Pointer to 32 bit location
        what will receive the maximum number of bytes of available memory.
 @parm  int  | used  | Output parameter:<s2>Pointer to 32 bit location
        what will receive the number of bytes of memory currently used.
 @rdesc -- none --
 @Also  tcp60.htm | Get_SNMP_Data  |
        tcp74.htm | Get_TCPIP_Statistics  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x78<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
void Get_TCPIP_Memory_Status(unsigned long far * total,
                             unsigned long far * used)
{
    asm { push DS } ;
    _ES = FP_SEG(total);
    _DI = FP_OFF(total);
    _DS = FP_SEG(used);
    _SI = FP_OFF(used);

    _AH = GET_MEMORY_INFO ;
    asm { int TCPIPVECT  } ;
    asm { pop DS } ;
}
#endif


/*************************************************************************/
//Set FTP Server Idle timeout (using: Set/Get Server Idle Timeout)
/*************************************************************************/
#ifdef _tcp79_
/*
 @doc DOC_tcp79_
 ---------------------------------------------------------------
 Set FTP server time-out
 ---------------------------------------------------------------
 @clib  Set_FTPServer_Idle_Timeout | Set FTP server time-out. |
        <cfont>int Set_FTPServer_Idle_Timeout ( unsigned int timeout );<efont> |
 @parm  int  | timeout  | Time out value in seconds.
 @rdesc 0:  success <nl>
        non-zero:  FTP server not available in this RTOS version
 @comm  This function inserts the specified FTP time-out into the
        CHIP.INI file.<s2> A reboot is required, before the new time-out value
        takes affect.<nl>
        <nl>
        Refer to
        <linkto>../../config.htm#FTP_TIMEOUT<linkmid>FTP_TIMEOUT<linktail>
        in CHIP.INI documentation.
 @Also  tcp79a.htm | Set_TelnetServer_Idle_Timeout  |
        tcp79b.htm | Get_FTPServer_Idle_Timeout |
        tcp79c.htm | Get_TelnetServer_Idle_Timeout
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x79<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Set_FTPServer_Idle_Timeout ( unsigned int timeout )
{
    _BX = 0x00;                 // Ftp server
    _DX = timeout;

    _AL = 0x00;                 // set timeout
    _AH = SET_SERVER_IDLE_TIMEOUT ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif

/*************************************************************************/
//Set Telnet Server Idle timeout (using: Set/Get Server Idle Timeout)
/*************************************************************************/
#ifdef _tcp79a_
/*
 @doc DOC_tcp79a_
 ---------------------------------------------------------------
 Set Telnet server time-out
 ---------------------------------------------------------------
 @clib  Set_TelnetServer_Idle_Timeout | Set Telnet server time-out. |
        <cfont>int Set_TelnetServer_Idle_Timeout ( unsigned int timeout );<efont> |
 @parm  int  | timeout  | Time out in seconds.
 @rdesc 0:  success <nl>
        non-zero:  Telnet server not available in this RTOS version
 @comm  This function inserts the specified Telnet time-out into the
        CHIP.INI file.<s2> The new time-out value takes affect
        immediately, without requiring a reboot.<nl>
        <nl>
        Refer to
        <linkto>../../config.htm#TELNET_TIMEOUT<linkmid>TELNET_TIMEOUT<linktail>
        in CHIP.INI documentation.
 @Also  tcp79.htm  | Set_FTPServer_Idle_Timeout   |
        tcp79c.htm | Get_TelnetServer_Idle_Timeout |
        tcp79b.htm | Get_FTPServer_Idle_Timeout
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x79<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Set_TelnetServer_Idle_Timeout( unsigned int timeout )
{
    _BX = 0x01;                 // Telnet server
    _DX = timeout;

    _AL = 0x00;                 // set timeout
    _AH = SET_SERVER_IDLE_TIMEOUT ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif

/*************************************************************************/
//Get FTP Server Idle timeout (using: Set/Get Server Idle Timeout)
/*************************************************************************/
#ifdef _tcp79b_
/*
 @doc DOC_tcp79b_
 ---------------------------------------------------------------
 Get FTP server time-out value
 ---------------------------------------------------------------
 @clib  Get_FTPServer_Idle_Timeout | Get FTP server time-out value. |
        <cfont>unsigned int Get_FTPServer_Idle_Timeout ( void );<efont> |
 @parm  int  |   | -- none --
 @rdesc 0xFFFF or 0xFFFE:<s2>FTP server not available in this RTOS version<nl>
        Otherwise:<s2> Existing FTP server time-out value, in seconds.
 @comm  This function accesses the  FTP server's existing time-out value.<nl>
        <nl>
        Refer to
        <linkto>../../config.htm#FTP_TIMEOUT<linkmid>FTP_TIMEOUT<linktail>
        in CHIP.INI documentation.
 @Also  tcp79.htm  | Set_FTPServer_Idle_Timeout   |
        tcp79a.htm | Set_TelnetServer_Idle_Timeout |
        tcp79c.htm | Get_TelnetServer_Idle_Timeout
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x79<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00

*/
unsigned int Get_FTPServer_Idle_Timeout (void)
{
    _BX = 0x00;                 // FTP server

    _AL = 0x01;                 // get timeout
    _AH = SET_SERVER_IDLE_TIMEOUT ;
    asm { int TCPIPVECT  } ;
    return _DX ;
}
#endif

/*************************************************************************/
// Get Telnet Server Idle timeout (using: Set/Get Server Idle Timeout)
/*************************************************************************/
#ifdef _tcp79c_
/*
 @doc DOC_tcp79c_
 ---------------------------------------------------------------
 Get Telnet server time-out value
 ---------------------------------------------------------------
 @clib  Get_TelnetServer_Idle_Timeout | Get Telnet server time-out value. |
        <cfont>unsigned int Get_TelnetServer_Idle_Timeout ( void );<efont> |
 @parm  int  |   | -- none --.
 @rdesc 0xFFFF or 0xFFFE:<s2>Telnet server not available in this RTOS version<nl>
        Otherwise:<s2> Existing Telnet server time-out value, in seconds.
 @comm  This function accesses the  Telnet server's existing time-out value.
        <nl>
        <nl>
        Refer to
        <linkto>../../config.htm#TELNET_TIMEOUT<linkmid>TELNET_TIMEOUT<linktail>
        in CHIP.INI documentation.
 @Also  tcp79a.htm | Set_TelnetServer_Idle_Timeout |
        tcp79.htm  | Set_FTPServer_Idle_Timeout   |
        tcp79b.htm | Get_FTPServer_Idle_Timeout
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x79<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00

*/
unsigned int Get_TelnetServer_Idle_Timeout(void)
{
    _BX = 0x01;                 // Telnet server
    _AL = 0x01;                 // get timeout
    _AH = SET_SERVER_IDLE_TIMEOUT ;
    asm { int TCPIPVECT  } ;
    return _DX ;
}
#endif

/*************************************************************************/
//Register an IP callback function on incoming packets
/*************************************************************************/

#ifdef _tcp7A_

/*
 @doc DOC_tcp7a_
 ---------------------------------------------------------------
 Register an IP user callback handler
 ---------------------------------------------------------------
 @clib  RegisterIPCallbackHandler | Register an IP User callback handler. |
        <cfont>int RegisterIPCallbackHandler ( void far *funcptr );<efont> |
 @parm  int  | funcptr  | Pointer to user's IP callback Handler.
 @rdesc 0 = success <nl>
 @comm  This function allows the application programmer to install a ip packet
        filter callback function. The application programmer can implement a
        function fitting the following type definition:<nl>
        <nl>
        <tab><cfont>typedef int (huge *IPSortOutFuncPtr)(<nl>
        <tab><tab><tab><tab>
          <linkto>../../tcpstruc.htm#IpUserCallbackInfo<linkmid>IpUserCallbackInfo<linktail>
          *ipInfo ); <efont><nl>
        <nl>
        If a function of this type is installed by the user, the TCP/IP stack
        will call this function at any incoming IP packet.<s2> Inside of this
        function the user is able to check the given IP parameters and decide
        if the TCP/IP stack should process this packet or ignore it.<s2>
        If the callback function returns -1 the incoming packet will be ignored
        by the TCP/IP stack.<nl>
        <nl>
        To uninstall the callback function, this API call must be called with
        a null pointer.<s2>
        <i><bold>Do not forget to uninstall the function if your application exits!
        <bolde><ie>
 @commtarget SC1x3/SC2x | <bold>Important:<bolde><s2> The callback will only execute
        on incoming IPv4 packets.<nl>
 @Also  tcp19.htm | RegisterCallbackFunction |
        tcp7B.htm | Register_ARP_User_CB |
        tcp7C.htm | RegisterIPCallbackHandler_Snd
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x7A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RegisterIPCallbackHandler(void far *funcptr)
{
    _ES = FP_SEG(funcptr) ;
    _DI = FP_OFF(funcptr) ;

    _AH = IP_CALLBACK;
    asm { int TCPIPVECT  } ;
    return _DX;
}
#endif




/*************************************************************************/
//Register ARP  callback function
//(requires RTOS 1.10B or higher)
/*************************************************************************/
#ifdef _tcp7B_
/*
 @doc DOC_tcp7b_
 ---------------------------------------------------------------
 Register an ARP user callback handler
 ---------------------------------------------------------------
 @clib  Register_ARP_User_CB | Register an ARP User callback handler. |
        <cfont>void Register_ARP_User_CB(void far * funcPtr);<efont> |
 @parm  int  | funcptr  | Pointer to ARP callback function (or set to null to remove
                         a previously installed callback)
 @rdesc returns nothing<nl>
 @comm
        The application programmer can implement a function fitting the following
        type definition:<nl>
        <nl>
        <tab><cfont>typedef int (huge *MyArpCallbackFuncPtr)(<nl><tab><tab><tab><tab>
        <linkto>../../tcpstruc.htm#ArpUserCallbackInfo<linkmid>ArpUserCallbackInfo_t<linktail>
        far *arpInfo );<efont><nl>
        <nl>
        If a function of this type is installed by the user, the TCP/IP stack will call this
        function for any incoming ARP packet.<s2> The input parameter to the callback function
        allows access to the ARP packet.<s2> Inside of this function the user is able
        to check the content  of the incoming ARP packet and decide whether the TCP/IP
        stack should process this packet or ignore it.<s2> If the callback function
        returns -1, the incoming packet will be ignored by the TCP/IP stack.<nl>
        If the size of the returned structure
        <linkto>../../tcpstruc.htm#ArpUserCallbackInfo<linkmid>ArpUserCallbackInfo_t<linktail>
        is equal or bigger 12, the structure now contains a
        <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>devicehandle_ptr<linktail>
        to determine the source device of the incoming packet for filtering.<nl>
        <nl>
        <nl>
        For structure of an ARP packet see
        <linkto>../../tcpstruc.htm#ArpHeader<linkmid>ArpHeader<linktail>.<nl>
        <nl>
        To remove the callback function, this function call must be called with a null pointer.<s2>
        <bold><i>Do not forget to uninstall the callback if your application exits!<bolde><ie><nl>
        <nl>
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x7B<linkmid>documentation<linktail>
        for more details.
 @Also  tcp19.htm | RegisterCallbackFunction |
        tcp7A.htm | RegisterIPCallbackHandler |
        tcp7C.htm | RegisterIPCallbackHandler_Snd

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x7B<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
void Register_ARP_User_CB(void far * funcPtr)
{
    _ES = FP_SEG(funcPtr) ;
    _DI = FP_OFF(funcPtr) ;

    _AH = ARP_USER_CB;
    asm { int TCPIPVECT  } ;
}
#endif

/*************************************************************************/
//Register an IP callback function on outgoing packets
/*************************************************************************/
#ifdef _tcp7C_

/*
 @doc DOC_tcp7C_
 ---------------------------------------------------------------
 Register an IP user callback handler
 ---------------------------------------------------------------
 @clib  RegisterIPCallbackHandler_Snd | Register an IP user callback handler
        on outgoing packets. |
        <cfont>int RegisterIPCallbackHandler_Snd ( void far *funcptr );<efont> |
 @parm  int  | funcptr  | Pointer to user's IP callback Handler.
 @rdesc 0 = success <nl>
 @comm  This function allows the application programmer to install an IP packet
        filter callback function.<s2> The application programmer can implement a
        function fitting the following type definition:<nl>
        <nl>
        <tab><cfont>typedef int (huge *IPCheckOutPacketFuncPtr)(<nl>
        <tab><tab><tab><tab>
          <linkto>../../tcpstruc.htm#IpUserCallbackInfo<linkmid>IpUserCallbackInfo_t<linktail>
          *ipInfo );<efont><nl>
        <nl>
        If a function of this type is installed by the user, the TCP/IP stack
        will call this function at any end IP packet.<s2> Inside of this
        function the user is able to check the given IP parameters and decide
        if the TCP/IP stack should send this packet or ignore it.<s2>
        If the callback function returns -1 the incoming packet will be ignored
        by the TCP/IP stack.<nl>
        <nl>
        To uninstall the callback function, this API call must be called with
        a null pointer.<s2>
        <bold><i>Do not forget to uninstall the function if your application exits!
        <bolde><ie>
 @commtarget SC1x3/SC2x | <bold>Important:<bolde><s2> The callback will only execute
        on incoming IPv4 packets.<nl>
 @Also  tcp19.htm | RegisterCallbackFunction |
        tcp7A.htm | RegisterIPCallbackHandler |
        tcp7B.htm | Register_ARP_User_CB
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x7C<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.11 | V1.01 | V1.01 | V0.90 | V1.00


*/
int RegisterIPCallbackHandler_Snd(void far *funcptr)
{
    _ES = FP_SEG(funcptr) ;
    _DI = FP_OFF(funcptr) ;
    _AH = IP_CALLBACK_SND;
    asm { int TCPIPVECT  } ;
    return _DX;
}
#endif


/*************************************************************************/
//Register callback function for IP configuration changes
/*************************************************************************/
#ifdef _tcp7D_
/*
 @doc DOC_tcp7D_
 ---------------------------------------------------------------
 Register an user callback handler for IP configuration changes
 ---------------------------------------------------------------
 @clib  RegisterIPConfigCallback | Register an user callback handler for IP configuration changes. |
        <cfont>void RegisterIPConfigCallback (void far * funcPtr);<efont> |
 @parm  int  | funcptr  | Pointer to callback function (or set to null to remove
                          a previously installed callback)
 @rdesc 0 = success <nl>
 @comm
        The application programmer can implement a function fitting the following
        type definition:<nl>
        <nl>
        <tab><cfont>typedef int (huge *MyIpConfigCallbackFuncPtr)(DevUserIfaceHandle DevHandlePtr);<efont><nl>
        <nl>
          If a function of this type is installed by the user, the TCP/IP stack will
          call this function for any IP configuration change.<nl>
          <nl>
        <nl>
        To remove the callback function, this function call must be called with a null pointer.<s2>
        <bold><i>Do not forget to uninstall the callback if your application exits!<bolde><ie><nl>
        <nl>
 @Also  tcp7A.htm | RegisterIPCallbackHandler |
        tcp7C.htm | RegisterIPCallbackHandler_Snd | |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x7D<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.53 | V1.53
*/
int RegisterIPConfigCallback (void far * funcPtr)
{
    _ES = FP_SEG(funcPtr) ;
    _DI = FP_OFF(funcPtr) ;
    _AH = IPCONF_CALLBACK;
    asm { int TCPIPVECT  } ;
    return _DX;
}
#endif

/*************************************************************************/
// Add gateway
/*************************************************************************/
#ifdef _tcp80_
/*
 @doc DOC_tcp80_
 ---------------------------------------------------------------
 Add the default gateway
 ---------------------------------------------------------------
 @clib  AddDefaultGateway | Add the default gateway. |
        <cfont>int AddDefaultGateway ( IP_INTERFACE which_interface,<nl>
        <tab><tab><tab><tab><tab><tab>const unsigned long far *Gateway,<nl>
        <tab><tab><tab><tab><tab><tab>int *error );<efont> |
 @depr  tcp80A.htm | AddDefaultGatewayEx
 @parm  int  | which_interface  | Enumeration type:<nl>
        <ul>
        <li>II_ETHERNET = 0:<s2>  Ethernet
        <li>II_PPP_SERVER = 1:<s2>  PPP server
        <li>II_PPP_CLIENT = 2:<s2>  PPP client
        <ule>
 @parm  int  | Gateway  | Pointer to gateway IP address in network
       byte order.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.
 @comm  If this function is used, the
        <linkto>../../config.htm#IP_GATEWAY<linkmid>gateway<linktail>
        entry in the <cfont>CHIP.INI<efont> becomes invalidated, but
        unchanged.<s2> If the PPP server or PPP client is specified by the
        <code>which_interface<codee> parameter, then the gateway is set
        to the remote peer IP address.
 @Also  tcp80a.htm | AddDefaultGatewayEx |
        tcp81.htm | DelDefaultGateway  |
        tcp82.htm |  GetDefaultGateway
 @Also  tcp83.htm | AddStaticRoute  |
        tcp84.htm | DelStaticRoute  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x80<linkmid>documentation<linktail>
        for more details.

 @related IP | ../../config.htm#IP_GATEWAY | Gateway |
    <cfont>CHIP.INI<efont> Configuration
 @related PPP server | ../../config.htm#PPPSERVER_GATEWAY | Gateway |
    <cfont>CHIP.INI<efont> Configuration
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
int  AddDefaultGateway (IP_INTERFACE which_interface,
                        const unsigned long far * Gateway,
                        int * error)
{
    _BX = which_interface ;
    _ES = FP_SEG(Gateway);
    _DI = FP_OFF(Gateway);
    _AH = ADD_DEFAULT_GATEWAY ;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX ;
}
#endif


#ifdef _tcp80a_
/*
 @doc DOC_tcp80a_
 ---------------------------------------------------------------
 Add the default gateway
 ---------------------------------------------------------------
 @clib  AddDefaultGatewayEx | Add the default gateway (Extended). |
        <cfont>int AddDefaultGatewayEx ( IP_INTERFACE which_interface,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; unsigned long far *Gateway,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; void far *userIfaceHandle,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; int *error );<efont> |
 @parm  int  | which_interface  | Enumeration type:<nl>
        <ul>
        <li>II_ETHERNET = 0:<s2>  Ethernet
        <li>II_PPP_SERVER = 1:<s2>  PPP server
        <li>II_PPP_CLIENT = 2:<s2>  PPP client
        <li>II_USER_DEVICE = 3:<s2>  user device driver
        <ule>
 @parm  int  | Gateway  | Pointer to gateway IPv4 address in network
      byte order.
 @parm  int  | userIfaceHandle | If <cfont>which_interface<efont>==3,
        user device handle.  (Otherwise not used.)
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.
 @comm  If this function is used, the
        <linkto>../../config.htm#IP_GATEWAY<linkmid>gateway<linktail>
        entry in the <cfont>CHIP.INI<efont> becomes invalidated, but
        unchanged.<s2> If the PPP server or PPP client is specified by the
        <code>which_interface<codee> parameter, then the gateway is set
        to the remote peer IP address.
 @Also  tcp81.htm | DelDefaultGateway  |
        tcp82.htm |  GetDefaultGateway | |

 @Also  tcp83.htm | AddStaticRoute  |
        tcp84.htm | DelStaticRoute  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x80<linkmid>documentation<linktail>
        for more details.

 @related IP | ../../config.htm#IP_GATEWAY | Gateway |
    <cfont>CHIP.INI<efont> Configuration
 @related PPP server | ../../config.htm#PPPSERVER_GATEWAY | Gateway |
    <cfont>CHIP.INI<efont> Configuration
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int  AddDefaultGatewayEx (IP_INTERFACE which_interface,
                          const unsigned long far * Gateway,
                          const void  far * userIfaceHandle,
                          int * error)
{
    _BX = which_interface ;
    _ES = FP_SEG(Gateway);
    _DI = FP_OFF(Gateway);
    _DX = FP_SEG(userIfaceHandle);
    _SI = FP_OFF(userIfaceHandle);
    _AH = ADD_DEFAULT_GATEWAY ;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX ;
}
#endif


/*************************************************************************/
// Delete gateway
/*************************************************************************/
#ifdef _tcp81_
/*
 @doc DOC_tcp81_
 ---------------------------------------------------------------
 Delete the default gateway
 ---------------------------------------------------------------
 @clib  DelDefaultGateway | Delete the default gateway. |
        <cfont>int DelDefaultGateway ( const unsigned long far *Gateway,<nl>
        <tab><tab><tab><tab><tab><tab>int *error );<efont> |
 @parm  int  | Gateway  | Pointer to gateway IP address to be
        removed.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.
 @comm  If this function is used, the
        <linkto>../../config.htm#IP_GATEWAY<linkmid>gateway<linktail>
        entry in the <cfont>CHIP.INI<efont> becomes invalidated, but
        unchanged.
 @Also  tcp80a.htm | AddDefaultGatewayEx |
        tcp82.htm | GetDefaultGateway | |
 @Also  tcp83.htm | AddStaticRoute  |
        tcp84.htm | DelStaticRoute  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x81<linkmid>documentation<linktail>
        for more details.

 @related IP | ../../config.htm#IP_GATEWAY | Gateway |
    <cfont>CHIP.INI<efont> Configuration
 @related PPP server | ../../config.htm#PPPSERVER_GATEWAY | Gateway |
    <cfont>CHIP.INI<efont> Configuration
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int  DelDefaultGateway (const unsigned long far * Gateway, int * error)
{
    _ES = FP_SEG(Gateway);
    _DI = FP_OFF(Gateway);
    _AH = DEL_DEFAULT_GATEWAY ;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX ;
}
#endif

/*************************************************************************/
// Get gateway
/*************************************************************************/
#ifdef _tcp82_
/*
 @doc DOC_tcp82_
 ---------------------------------------------------------------
 Get the current default gateway
 ---------------------------------------------------------------
 @clib  GetDefaultGateway | Get the current default gateway. |
        <cfont>int GetDefaultGateway ( unsigned long far *Gateway,<nl>
        <tab><tab><tab><tab><tab><tab>int *error );<efont> |
 @parm  int  | Gateway  | Output parameter:<s2>Pointer to where
        the gateway IP will be written in network byte order.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.
 @Also  tcp80a.htm | AddDefaultGatewayEx  |
        tcp81.htm | DelDefaultGateway  | |
 @Also  tcp83.htm | AddStaticRoute  |
        tcp84.htm | DelStaticRoute  | |
 @related [IP]<s2> | ../../config.htm#IP_GATEWAY | GATEWAY |
        - CHIP.INI entry
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x82<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int  GetDefaultGateway (unsigned long far * Gateway, int * error)
{
    _ES = FP_SEG(Gateway);
    _DI = FP_OFF(Gateway);
    _AH = GET_DEFAULT_GATEWAY ;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX ;
}
#endif


/*************************************************************************/
// Add a static route
/*************************************************************************/
#ifdef _tcp83_
/*
 @doc DOC_tcp83_
 ---------------------------------------------------------------
 Add a route for a interface
 ---------------------------------------------------------------
 @clib  AddStaticRoute | Add a route for an interface. |
        <cfont>int AddStaticRoute ( IP_INTERFACE which_interface,<nl>
        <tab><tab><tab><tab><tab> const Route_Entry far *route,<nl>
        <tab><tab><tab><tab><tab> int *error );<efont> |
 @parm  int  | which_interface  | Enumeration type:<nl>
        <ul>
        <li>II_ETHERNET = 0:<s2>  Ethernet
        <li>II_PPP_SERVER = 1:<s2>  PPP server
        <li>II_PPP_CLIENT = 2:<s2>  PPP client
        <ule>
 @parm  int  | route  | Pointer to user <code>Route_Entry<codee>
        <linkto>../../tcpstruc.htm#Route_Entry<linkmid>structure<linktail>
        (defined in tcpipapi.h).
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.
 @comm 
    IP packets destined for the specified network will be routed to the 
    specified device.<nl>
    <nl>
    The alternative  <linkto>tcp83a.htm<linkmid>AddStaticRouteEx()<linktail> API
    must be used for user defined devices.
 @commtarget SC1x3/SC2x | <bold>Important:<bolde><s2> The current SC1x3/SC2x Chip-RTOS version supports
        only route definitions based on the IPv4 protocol.<nl>
 @Also  tcp83a.htm | AddStaticRouteEx |
        tcp84.htm | DelStaticRoute | |
 @Also  tcp80a.htm | AddDefaultGatewayEx |
        tcp81.htm | DelDefaultGateway |
        tcp82.htm | GetDefaultGateway
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x83<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
int  AddStaticRoute(IP_INTERFACE which_interface,
                     const Route_Entry far * route,
                     int * error)
{
    _BX = which_interface;
    _ES = FP_SEG(route);
    _DI = FP_OFF(route);
    _AH = ADD_STATIC_ROUTE ;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX ;
}
#endif


/*************************************************************************/
// Add a static route
/*************************************************************************/
#ifdef _tcp83a_
/*
 @doc DOC_tcp83A_
 ---------------------------------------------------------------
 Add a route for a interface (extended version)
 ---------------------------------------------------------------
 @clib  AddStaticRouteEx | Add a route for a interface (extended version). |
        <cfont>int AddStaticRouteEx ( IP_INTERFACE which_interface,<nl>
        <tab><tab><tab><tab><tab> const Route_Entry far *route,<nl>
        <tab><tab><tab><tab><tab> DevUserIfaceHandle DevHandlePtr,<nl>
        <tab><tab><tab><tab><tab> int *error);<efont> |
        
 @parm  int  | which_interface  | Enumeration type:<nl>
        <ul>
        <li>II_ETHERNET    = 0:<s2>  Ethernet
        <li>II_PPP_SERVER  = 1:<s2>  PPP server
        <li>II_PPP_CLIENT  = 2:<s2>  PPP client
        <li>II_USER_DEVICE = 3:<s2>  User device

        <ule>
 @parm  int  | route  | Pointer to user <code>Route_Entry<codee>
        <linkto>../../tcpstruc.htm#Route_Entry<linkmid>structure<linktail>
        (defined in tcpipapi.h).
 @parm  int  | DevHandlePtr |  If <code>which_interface==3<codee>:
          User driver
     <linkto>../../ddvstruc.htm#DevUserIfaceHandle<linkmid>Device handle<linktail>
     (e.g. ETH1 or WLAN driver handle)

 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.
 @comm 
    IP packets destined for the specified network will be routed to the 
    specified device.<nl>
    <nl>
    For the built-in internal devices, the <linkto>tcp83.htm<linkmid>AddStaticRoute()<linktail> API
    with one less parameter can instead be used.
 @commtarget SC1x3/SC2x | <bold>Important:<bolde><s2> The current SC1x3/SC2x Chip-RTOS version supports
        only route definitions based on the IPv4 protocol.<nl>
 @Also  tcp83.htm | AddStaticRoute  |
        tcp84.htm | DelStaticRoute | |
 @Also  tcp80a.htm | AddDefaultGatewayEx |
        tcp81.htm | DelDefaultGateway |
        tcp82.htm | GetDefaultGateway
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x83<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
 @target_clib V2.15
*/
int  AddStaticRouteEx(IP_INTERFACE which_interface,
                      const Route_Entry far * route,
                      DevUserIfaceHandle DevHandlePtr,
                      int * error)
{
    _BX = which_interface;
    _ES = FP_SEG(route);
    _DI = FP_OFF(route);
    _DX = FP_SEG(DevHandlePtr);
    _SI = FP_OFF(DevHandlePtr);
    _AH = ADD_STATIC_ROUTE ;
    asm { int TCPIPVECT  } ;
    *error = _AX ;
    return _DX ;
}
#endif


/*************************************************************************/
// Delete a static route
/*************************************************************************/
#ifdef _tcp84_
/*
 @doc DOC_tcp84_
 ---------------------------------------------------------------
 Delete a route from an interface
 ---------------------------------------------------------------
 @clib  DelStaticRoute | Delete a route. |
        <cfont>int DelStaticRoute ( IP_INTERFACE which_interface,<nl>
        <tab><tab><tab><tab><tab> const Route_Entry far *route,<nl>
        <tab><tab><tab><tab><tab> int *error );<efont> |
 @parm  int  | which_interface  | This parameter is not used, so
        therefore it can be set to any value.<nl>
 @parm  int  | route  | Pointer to user  <code>Route_Entry<codee>
        <linkto>../../tcpstruc.htm#Route_Entry<linkmid>structure<linktail>.
        Only <code>destIPAddress<codee>
        and <code>destNetmask<codee> members of this structure need be
        set valid before calling.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.
 @Also  tcp83.htm | AddStaticRoute  | 
        tcp83a.htm| AddStaticRouteEx | |
 @Also  tcp80a.htm | AddDefaultGatewayEx  |
        tcp81.htm | DelDefaultGateway |
        tcp82.htm | GetDefaultGateway
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x84<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00

*/
int  DelStaticRoute (IP_INTERFACE which_interface,
                     const Route_Entry far * route,
                     int * error)
{
 // _BX = which_interface;  .. not used
    _ES = FP_SEG(route);
    _DI = FP_OFF(route);
    _AH = DEL_STATIC_ROUTE ;
    asm { int TCPIPVECT  } ;
    *error= _AX ;
    return _DX ;
}
#endif

/*************************************************************************/
// Delete ARP entry by physical address
/*************************************************************************/
#ifdef _tcp88_
/*
 @doc DOC_tcp88_
 ---------------------------------------------------------------
 Delete ARP entry by physical address
 ---------------------------------------------------------------
 @clib  DelArpEntryByPhys | Delete ARP entry by physical address. |
        <cfont>int DelArpEntryByPhys ( const unsigned char far *phy,<nl>
        <tab><tab><tab><tab><tab><s3> int *error );<efont> |
 @parm  unsigned char far *  | phy | Pointer to the physical address (6 Byte)
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.

 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.
 @comm  Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xA8<linkmid>documentation<linktail>
        for more details.
 @Also  tcp89.htm | AddArpEntry  |
        tcp8A.htm | GetARPRouteCacheEntries | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x88<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
int DelArpEntryByPhys(const unsigned char far *phy, int *error)
{
    _ES = FP_SEG(phy);
    _DI = FP_OFF(phy);
    _AH = DEL_ARP_ENTRY_BY_PHYS;
    asm { int TCPIPVECT  } ;
    *error= _AX ;
    return _DX ;
}
#endif


/*************************************************************************/
// Add ARP entry
/*************************************************************************/
#ifdef _tcp89_
/*
 @doc DOC_tcp89_
 ---------------------------------------------------------------
 Add ARP entry
 ---------------------------------------------------------------
 @clib  AddArpEntry | Add an entry in the ARP table. |
        <cfont>int AddArpEntry ( const unsigned long far *ip,<nl>
        <tab><tab><tab><tab>&nbsp; const unsigned char far *phy,<nl>
        <tab><tab><tab><tab>&nbsp; int *error );<efont> |
 @parm  unsigned long far *  | ip  | Pointer to the IP address
 @parm  unsigned char far *  | phy | Pointer to the physical address (6 Byte)
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.
 @Also  tcp88.htm | DelArpEntryByPhys  |
        tcp8A.htm | GetARPRouteCacheEntries  |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x89<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
int AddArpEntry(const unsigned long far *ip, const unsigned char far *phy, int *error)
{
    _BX = FP_SEG(ip);
    _SI = FP_OFF(ip);
    _ES = FP_SEG(phy);
    _DI = FP_OFF(phy);
    _AH = ADD_ARP_ENTRY;
    asm { int TCPIPVECT  } ;
    *error= _AX ;
    return _DX ;
}
#endif


/*************************************************************************/
// Get ARP cache copy
/*************************************************************************/
#ifdef _tcp8A_
/*
 @doc DOC_tcp8A_
 ---------------------------------------------------------------
 Read ARP/Route cache table
 ---------------------------------------------------------------
 @clib  GetARPRouteCacheEntries |This function returns all valid entries
        in the internal ARP/Route cache table.|
        <cfont>int GetARPRouteCacheEntries(<nl>
        <tab><tab><tab><tab>ArpRouteCacheEntry far * arpuserptr);<efont> |
 @parm  void *  | arpuserptr  | Output Parameter:<s2> Pointer to a user provided array of
            <linkto>../../config.htm#IP_ARPENTRIES<linkmid>ARP entries<linktail>
           (default 64) ArpRouteCacheEntry data <linkto>../../tcpstruc.htm#ArpRouteCacheEntry<linkmid>structures<linktail>
            for storing ARP/Route cache table.

 @comm  The API call returns only a copy of the current device interface variables.<nl>
        In order to always have the current table status, it is necessary to
        cyclically (e.g. every 10 seconds) request the table with this API.<nl>

 @rdesc  Number of valid entries output to table at <cfont>arpuserptr<efont>.<s2>
         This user provided array contains the current ARP/Route cache table.<nl>
 @Also  tcp88.htm | DelArpEntryByPhys  |
        tcp89.htm | AddArpEntry  |   |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x8A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
int GetARPRouteCacheEntries(ArpRouteCacheEntry far * arpuserptr)
{
    _BX = FP_SEG(arpuserptr);
    _SI = FP_OFF(arpuserptr);
    _AH = GET_ARPROUTE_CACHE;
    asm { int TCPIPVECT  } ;
    return _CX ;   //number of valid entries at arpuser array
}
#endif
/*************************************************************************/
//interface information
/*************************************************************************/
#ifdef _tcp8D_
/*
 @doc DOC_tcp8D_
 ---------------------------------------------------------------
 Read table of TCP/IP device interfaces
 ---------------------------------------------------------------
 @clib  Get_Iface_Entries |This function returns information about all
        installed TCP/IP device interfaces.|
        <cfont>int Get_Iface_Entries(Iface_Entry far * iface_entry, int max);<efont> |
 @depr  tcp8F.htm | Get_Iface_Entries_Ext
 @parm  void *  | iface_entry  | Output Parameter:<s2> Pointer to a user
            provided array of
             <linkto>../../tcpstruc.htm#Iface_Entry<linkmid>Iface_Entry<linktail>
             type data structures which will receive the information.
 @parm  int   | max | Number of data structures in array.<s2> Up to this number of
               device interfaces will be reported.
 @rdesc  Number of valid entries in the array at
         <cfont>iface_entry<efont> containing
         reported  device interface information.
 @commtarget SC1x3/SC2x |  This function works only for IPv4 device interfaces.<s2>
         The <linkto>tcpC0.htm<linkmid>Get_IPv6_Iface_Entries<linktail> API
         should be used to read out information for IPv6 interfaces.
 @Also  tcpC0.htm | Get_IPv6_Iface_Entries  |  |  |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x8D<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
int Get_Iface_Entries(Iface_Entry far * iface_entry, int max)
{
    _BX = FP_SEG(iface_entry);
    _SI = FP_OFF(iface_entry);
    _CX = max;
    _AH = GET_IFACE_ENTRIES;
    asm { int TCPIPVECT  } ;
    return (int)_AX ;   //number of valid entries at iface_entry array
}
#endif


#ifdef _tcp8F_
/*
 @doc DOC_tcp8F_
 ---------------------------------------------------------------
 Read table of TCP/IP device interfaces (extended)
 ---------------------------------------------------------------
 @clib  Get_Iface_Entries_Ext |This function returns information about all
        installed TCP/IP device interfaces.|
        <cfont>int Get_Iface_Entries_Ext(Iface_Entry_Ext far * iface_entry, int max);<efont> |
 @parm  void *  | iface_entry  | Output Parameter:<s2> Pointer to a user
            provided array of
             <linkto>../../tcpstruc.htm#Iface_Entry_Ext<linkmid>Iface_Entry_Ext<linktail>
             type data structures which will receive the information.
 @parm  int   | max | Number of data structures in array.<s2> Up to this number of
               device interfaces will be reported.
 @rdesc  Number of valid entries in the array at
         <cfont>iface_entry<efont> containing
         reported  device interface information.

 @comm  This function is different from <linkto>../../tcpipapi.htm#0xAC0x8D<linkmid>GET_IFACE_ENTRIES<linktail>.
        It stores at the user provided array from type <linkto>../../tcpstruc.htm#Iface_Entry_Ext<linkmid>structures<linktail>
        all ip configurations (IP multihoming on one interface) of each interface found, not only the first one.

 @commtarget SC1x3/SC2x |  This function works only for IPv4 device interfaces.<s2>
         The <linkto>tcpC0.htm<linkmid>Get_IPv6_Iface_Entries<linktail> API
         should be used to read out information for IPv6 interfaces.
 @Also  tcpC0.htm | Get_IPv6_Iface_Entries  |  |  |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x8F<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.10 | V1.00
 @target_clib V2.04

*/
int Get_Iface_Entries_Ext(Iface_Entry_Ext far * iface_entry, int max)
{
    _BX = FP_SEG(iface_entry);
    _SI = FP_OFF(iface_entry);
    _CX = max;
    _AH = GET_IFACE_ENTRIES_EXT;
    asm { int TCPIPVECT  } ;
    return (int)_AX ;   //number of valid entries at iface_entry array
}
#endif





/*************************************************************************/
//interface mtu
/*************************************************************************/
#ifdef _tcp8E_
/*
@doc DOC_tcp8E_
 ---------------------------------------------------------------
 Set MTU of a device interface
 ---------------------------------------------------------------
 @clib  SetIfaceMTU | Set MTU (Maximum Transfer Unit) of a device interface. |
        <cfont>int SetIfaceMTU ( IP_INTERFACE which_interface,<nl>
        <tab><tab><tab><tab>&nbsp; const void far *userIfaceHandle,<nl>
        <tab><tab><tab><tab>&nbsp; int mtu,<nl>
        <tab><tab><tab><tab>&nbsp; int *error );<efont> |
 @parm  int  | which_interface  | Enumeration type:<nl>
        <ul>
        <li>II_ETHERNET = 0:<s2>  Ethernet
        <li>II_PPP_SERVER = 1:<s2>  PPP server
        <li>II_PPP_CLIENT = 2:<s2>  PPP client
        <li>II_USER_DEVICE = 3:<s2>  user device driver
        <ule>
 @parm  int  | userIfaceHandle | If <cfont>which_interface<efont> is 3,
        this parameter is a pointer to user device handle.
 @parm  int  | mtu      | Maximum Transfer Unit
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.

 @comm  Changing the MTU can only be done, if the interface is closed,
        e.g. after execution of
        <linkto>tcp42.htm<linkmid>PPP_Client_Close().<linktail>

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x8E<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.11 | V1.01 | V1.01 | V0.90 | V1.00
*/
int SetIfaceMTU(IP_INTERFACE which_interface,const void  far * userIfaceHandle,
                unsigned int mtu, int *error)
{
   _BX = which_interface;
   _CX = mtu;
   _ES = FP_SEG(userIfaceHandle);
   _DI = FP_OFF(userIfaceHandle);
   _AH = SET_IFACE_MTU;
   asm { int TCPIPVECT  } ;
   *error = _AX ;
   return _DX ;
}
#endif
/*************************************************************************/
// Install an IP multicast address, join a multicast group
/*************************************************************************/
#ifdef _tcp90_
/*
 @doc DOC_tcp90_
 ---------------------------------------------------------------
 Install an IP multicast address entry
 ---------------------------------------------------------------
 @clib  Add_IGMP_Membership | Install an IP multicast address entry. |
        <cfont>int Add_IGMP_Membership ( const unsigned long far *MulticastIP,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; const unsigned char far *MacAddress,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; int *error );<efont> |
 @parm int  | MulticastIP  | Pointer to multicast IPv4 address
      in network byte order.
 @parm  int  | MacAddress  | Pointer to a 6 byte array that
        contains the corresponding Ethernet address.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.
 @comm
        IP Multicasting is the Internet abstraction of hardware multicasting.<s2> It allows transmission of
        IP datagrams to a group of hosts that form a single multicast group.<s2> Membership in a multicast group
        is dynamic.<s2> Hosts may join or leave the group at any time.<s2> Each multicast group
        has unique IP multicast address (Class D address).<s2> The first four bits of an IP multicast
        address must match to binary 1110.<s2> IP multicast addresses range from 224.0.0.0 through
        239.255.255.255.<nl>
        <nl>
        For the usage of IP multicasting on an Ethernet interface, IP multicast addresses must be mapped to
        Ethernet hardware addresses.<s2> The Ethernet multicast address corresponding to the IP multicast
        address can be determined with the <linkto>tcp92.htm<linkmid>IPMulticast_to_MacAddr<linktail> API,
        and used here as the <code>MacAddress<codee> parameter.
        <nl><nl>
        The Ethernet device of the IPC@CHIP&reg; will be switched into the Ethernet
        multicast mode.<s2> In this mode it receives any incoming IP packet with the mapped Ethernet multicast
        address and forwards it to the TCP/IP layer.<s2>
        Likewise, each out going IP multicast packet sent to this multicast IP address will be sent
        with the mapped Ethernet multicast address.<nl>
        <nl>
        Sending and receiving of IP multicast packets is only usable with UDP sockets (datagram sockets).<s2>
        This is due to that multicast IP packet must be receivable by any member of a multicast group,
        and that would violate the concept of a one to one TCP socket connection.<nl>
        <nl>
        After installing a IP multicast address with this API, the application programmer is able to use this
        address as a destination address when sending datagrams.<s2> A UDP socket is able to receive datagrams
        at the specified multicast address.<nl>
        <nl>
        The maximum number of supported IP multicast addresses in the IPC@CHIP&reg; is limited to 15.<s2>
        <nl>
        <nl>
        This implementation does not support multicast routing.<s2>
        Sending and receiving multicast datagrams works only on the local network.<nl>
        <nl>
        Use of multicast addresses is only possible on the Ethernet interface.<s2>

 @commtarget SC1x3/SC2x |  This API applies only to IPv4 multicast.
 @Also  tcp91.htm | Drop_IGMP_Membership  |
        tcp92.htm |  IPMulticast_to_MacAddr | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x90<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00

*/
int  Add_IGMP_Membership(const unsigned long far * MulticastIP,
                         const unsigned char far * MacAddress,
                         int * error)
{

    asm { push DS } ;
   // Note: This higher level notation has the advantage over the assembly
   //    LES DI and LDS SI in that for small or medium memory models the
   //    compiler can figure out that FP_SEG(x) means DS register for near
   //    pointers.  For far pointers it compiles into the LES/LDS opcodes.
   _ES = FP_SEG(MulticastIP) ;
   _DI = FP_OFF(MulticastIP) ;

   _DS = FP_SEG(MacAddress) ;
   _SI = FP_OFF(MacAddress) ;

   _AH = ADD_IGMP_MEMBERSHIP;
   asm { int TCPIPVECT } ;
   asm { pop DS } ;
    *error = _AX ;
    return _DX ;
}
#endif

/*************************************************************************/
//Delete an IP multicast address, leave a multicast group
/*************************************************************************/
#ifdef _tcp91_
/*
 @doc DOC_tcp91_
 ---------------------------------------------------------------
 Delete an IP multicast address entry
 ---------------------------------------------------------------
 @clib  Drop_IGMP_Membership | Delete an IP multicast address entry. |
        <cfont>int Drop_IGMP_Membership ( const unsigned long far *MulticastIP,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; int *error );<efont> |
 @parm  int  | MulticastIP  | Pointer to multicast IP address
        to be deleted.<s2> This address is in network byte order.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.
 @commtarget SC1x3/SC2x |  This API applies only to IPv4 multicast.
 @Also  tcp90.htm | Add_IGMP_Membership  |
        tcp92.htm |  IPMulticast_to_MacAddr | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x91<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00

*/
int  Drop_IGMP_Membership (const unsigned long far * MulticastIP, int * error)
{
   _ES = FP_SEG(MulticastIP);
   _DI = FP_OFF(MulticastIP);
   _AH = DROP_IGMP_MEMBERSHIP;
   asm { int TCPIPVECT  } ;
   *error = _AX ;
    return _DX ;
}
#endif

/*************************************************************************/
//Map IP multicast to Ethernet multicast
/*************************************************************************/
#ifdef _tcp92_
/*
 @doc DOC_tcp92_
 ---------------------------------------------------------------
 Map IP multicast address to Ethernet address
 ---------------------------------------------------------------
 @clib  IPMulticast_to_MacAddr | Map IP multicast address to Ethernet address. |
        <cfont>int IPMulticast_to_MacAddr (<nl>
        <tab><tab><tab><tab><tab> const unsigned long far *MulticastIP,<nl>
        <tab><tab><tab><tab><tab> unsigned char far *MacAddress,<nl>
        <tab><tab><tab><tab><tab> int *error );<efont> |
 @parm  int  | MulticastIP  | Pointer to multicast IP address in network
     byte order.
 @parm  int  | MacAddress  | Output Parameter:<s2>Pointer to a 6 byte array
        where the corresponding MAC address will be stored by this function.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success <nl>
        -1:  See reported <code>error<codee> code.
 @comm  This API function computes the MAC address in the following way:<nl>
        To map an IP multicast address to a corresponding Ethernet multicast
        address, place the low-order 23 bits of the IP multicast address
        into the low order 23 bits of the special Ethernet multicast
        address<nl>
        <tab>01 00 5E 00 00  00<nl>
        <nl>
        e.g. IP multicast address 224.0.0.1 becomes Ethernet
        address<nl>
        <tab>01 00 5E 00 00 01
 @commtarget SC1x3/SC2x |  This API applies only to IPv4 multicast addresses.<nl>
 @Also  tcp90.htm | Add_IGMP_Membership  |
        tcp91.htm | Drop_IGMP_Membership |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0x92<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00

*/
int  IPMulticast_to_MacAddr (const unsigned long far * MulticastIP,
                             unsigned char far * MacAddress,
                             int * error)
{

   asm { push DS } ;
   // Note: This higher level notation has the advantage over the assembly
   //    LES DI and LDS SI in that for small or medium memory models the
   //    compiler can figure out that FP_SEG(x) means DS register for near
   //    pointers.  For far pointers it compiles into the LES/LDS opcodes.
   _ES = FP_SEG(MulticastIP) ;
   _DI = FP_OFF(MulticastIP) ;

   _DS = FP_SEG(MacAddress) ;
   _SI = FP_OFF(MacAddress) ;

   _AH = MCASTIP_TO_MACADDR;
   asm { int TCPIPVECT } ;
   asm { pop DS } ;
    *error = _AX ;
    return _DX ;
}
#endif









#ifdef _tcpC0_
/*
 @doc DOC_tcpC0_
 ---------------------------------------------------------------
 Read table of TCP/IP IPv6 device interfaces
 ---------------------------------------------------------------
 @clib  Get_IPv6_Iface_Entries | This function returns information about all
        installed TCP/IP IPv6 device interfaces.|
        <cfont>int Get_IPv6_Iface_Entries(<nl>
        <tab><tab><tab><tab><tab><tab>IfaceIPv6_Entry  far * iface_ipv6_entries,<nl>
        <tab><tab><tab><tab><tab><tab>int max);<efont> |
 @parm  void *  | iface_ipv6_entries  | Output Parameter:<s2> Pointer to a
       user provided array of
       <linkto>../../tcpstruc.htm#IfaceIPv6_Entry<linkmid>IfaceIPv6_Entry<linktail>
        type data structures which will receive the information.
 @parm  int   | max | Number of data structures in array.<s2> Up to this number of
               device interfaces will be reported.
 @rdesc  Number of valid entries in the array at
         <cfont>iface_ipv6_entries<efont> containing
         reported  device interface information.
 @comm  This function works only for IPv6 device interfaces.<s2>
         The <linkto>tcp8D.htm<linkmid>Get_Iface_Entries<linktail> API
         should be used to read out information for IPv4 interfaces.
 @Also  tcp8D.htm | Get_Iface_Entries  |  |  |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xC0<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   |  n/a  |  n/a  | V0.90 | V1.00
*/

int Get_IPv6_Iface_Entries(IfaceIPv6_Entry  far * iface_ipv6_entries, int max)
{
   _CX = max;
   _ES = FP_SEG(iface_ipv6_entries);
   _DI = FP_OFF(iface_ipv6_entries);
   _AH = GET_IPV6_IFACE_ENTRIES;
   asm { int TCPIPVECT  };
   return _AX;
}
#endif

#ifdef _tcpC1_
/*
 @doc DOC_tcpC1_
 ---------------------------------------------------------------
 Convert an IP address text to binary
 ---------------------------------------------------------------
 @clib  inet_pton | Convert an IP address from standard text representation to binary.|
        <cfont>int inet_pton( int af,<nl>
        <tab><tab><tab><s2> const char far * source_ptr,<nl>
        <tab><tab><tab><s2> void far * dest_ptr);<efont> |
 @parm  int    | af     | Address family, AF_INET (for IPv4) or AF_INET6 (for IPv6)
 @parm  void * | src    | Input Parameter:<s2> Pointer to the IP address text
        (null terminated) to be converted
 @parm  void * | dst    | Output Parameter:<s2> Storage provided by the user which
        will receive the converted binary IP address.<s2> This buffer must provide
        4 bytes for AF_INET and 16 Bytes for AF_INET6.
 @rdesc <hangpara 12:18>1:<s2>  Success, the <cfont>dst<efont> buffer contains the converted
            binary IP in network byte order.<paraend>
        <hangpara 12:18>0:<s2>   Input string at <cfont>src<efont> was not a valid IP address of
        indicated type (IPv4 or IPv6).<paraend>
        <hangpara 12:18>-1:  The <cfont>af<efont> parameter was set to an invalid
        address family.<paraend>
 @Also  tcpC2.htm | inet_ntop  |
        tcp08.htm| inet_addr |  |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xC1<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   |  n/a  |  n/a  | V0.90 | V1.00
 */
int inet_pton(int af, const char far * source_ptr, void far * dest_ptr)
{
    asm { push DS } ;
    // Note: This higher level notation has the advantage over the assembly
    //    LES DI and LDS SI in that for small or medium memory models the
    //    compiler can figure out that FP_SEG(x) means DS register for near
    //    pointers.  For far pointers it compiles into the LES/LDS opcodes.
    _ES = FP_SEG(source_ptr) ;
    _DI = FP_OFF(source_ptr) ;

    _DS = FP_SEG(dest_ptr) ;
    _SI = FP_OFF(dest_ptr) ;

    _BX = af ;
    _AH = INET_PTON;
    asm { int TCPIPVECT } ;
    asm { pop DS } ;

    return _DX;
}
//#endif
#endif

#ifdef _tcpC2_
/*
 @doc  DOC_tcpC2_
 -----------------------------------------------------------------------------------
 Convert an IP address from the binary format to standard text representation format
 -----------------------------------------------------------------------------------
 @clib  inet_ntop | Convert an IP address from binary to standard text. |
        <cfont>int inet_ntop( int af,<nl>
        <tab><tab><tab><s2> const void far * source_ptr,<nl>
        <tab><tab><tab><s2> char far * dest_ptr,int max);<efont> |
 @parm  int    | af     | Address family, AF_INET (for IPv4) or AF_INET6 (for IPv6)
 @parm  void * | src    | Input Parameter:<s2> Pointer to the binary IP address
            in network byte order to be converted to ASCII text.
 @parm  void * | dst    | Output Parameter:<s2> Storage provided by the caller which
        will receive the converted IP address text.<s2> This text will be a null
        terminated string.<nl>
 @parm  int    | max    | Size in bytes, of the provided buffer at <cfont>dst<efont>.<s2>
                          This string buffer should provide 16 bytes for AF_INET
                          and 46 Bytes for AF_INET6.
 @rdesc <hangpara 12:18>0:<s2>  Success, the <cfont>dst<efont> buffer contains the converted IP address string.
        <paraend>
        <hangpara 12:18>-1:<s2>  Failure, which could be due to invalid address family
                    value <cfont>af<efont>,
                   inadequate buffer size specified by <cfont>max<efont>, or NULL pointer
                   for either <cfont>src<efont> or <cfont>dst<efont> parameters.<paraend>
 @Also  tcpC1.htm | inet_pton  |
        tcp11.htm| InetToAscii |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xC2<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   |  n/a  |  n/a  | V0.90 | V1.00
*/
int inet_ntop(int af , const void far * source_ptr, char far * dest_ptr, int max)
{

  asm { push DS } ;
   // Note: This higher level notation has the advantage over the assembly
   //    LES DI and LDS SI in that for small or medium memory models the
   //    compiler can figure out that FP_SEG(x) means DS register for near
   //    pointers.  For far pointers it compiles into the LES/LDS opcodes.
   _ES = FP_SEG(source_ptr) ;
   _DI = FP_OFF(source_ptr) ;

   _DS = FP_SEG(dest_ptr) ;
   _SI = FP_OFF(dest_ptr) ;

   _CX = max;
   _BX = af ;
   _AH = INET_NTOP;
   asm { int TCPIPVECT } ;
   asm { pop DS } ;
   return _DX;
}
#endif

#ifdef _tcpC3_
/*
 @doc DOC_tcpC3_
 ---------------------------------------------------------------
 open socket for IPv4 or IPv6 family
 ---------------------------------------------------------------
 @clib opensocket_ext | Open an IPv4 or IPv6 socket. |
        <cfont>int opensocket_ext(int family, unsigned char type,  int *error);<efont> |
 @parm  int  | family  | address family AF_INET (2) for IPv4 or AF_INET6 (28) for IPv6<nl>
 @parm  int  | type  | SOCK_STREAM = 1 for TCP socket<nl>
        SOCK_DGRAM = 2 for UDP datagram socket.
 @parm  int  | error   | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm<linkmid>code<linktail>, 0 on success.
 @rdesc -1: Failure (see <code>error<codee> output parameter)<nl>
        else socket descriptor
 @comm  Creates an endpoint for communication and returns a socket descriptor.<nl>
 <nl>
     This legacy function is equivalent to the BSD compatible
     <linkto>bsd41.htm<linkmid>socket()<linktail> functionality, with 
     the additional functionality of outputting the error code.<s2>  The
     <linkto>bsd41.htm<linkmid>socket()<linktail> alternative function
     will execute slightly faster (after first call) due to that it uses
     dynamic linking instead of software interrupt to reach the <chiprtos>.

 @Also  tcp02.htm | closesocket  |
        tcp03.htm | bind |
        tcp04.htm | connect

 @Also  bsd41.htm | socket  |
        tcp01.htm | opensocket |
         |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xC3<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   |  n/a  |  n/a  | V0.90 | V1.00

*/
int opensocket_ext(int family, unsigned char type,  int *error)
{
    int sd;
    unsigned char fcode;
    int error_code = 0 ;

    fcode = (family==AF_INET)?API_OPENSOCKET:API_OPENSOCKET_IPV6;

    _AL = type ;
    _AH = fcode;
    asm { int TCPIPVECT  } ;
    sd = _AX ;
    if (_DX != 0)
    {
        error_code = sd ;       // Error code was returned in AX.
        sd = -1 ;
    }
    *error = error_code ;
    return sd ;
}
#endif


#ifdef _tcpD0_
/*
@doc DOC_tcpD0_
 ----------------------------------------------------------------------------------
 Add a certificate
 ----------------------------------------------------------------------------------
 @clib  PKI_CertificateAdd | Add a certificate to the public key infrastructure.
        The CA certificate must be added before the certificate is added.
        In addition, the private/public key pair for a local certificate must be
        added before adding the local certificate. |
        <cfont>int PKI_CertificateAdd(PKI_CERT_ADD_EntryPtr addEntryPtr, int *error);<efont> |
 @parm  PKI_CERT_ADD_EntryPtr  | addEntryPtr |
    <linkto>../../tcpstruc.htm#PKI_CERT_ADD_Entry<linkmid>Certificate Add structure<linktail>
 @parm  int  | error    | Output parameter:<s2>A bit-wise combination of failure
        <linkto>../../iperrlst.htm#error<linkmid>flags<linktail>, 0 on success.
 @rdesc 0:  success<nl>
        -1:  failed
 @Also  tcpD1.htm | PKI_CertificateDel |
        tcpD2.htm | PKI_OwnKeyPairAdd  |
                  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xD0<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int PKI_CertificateAdd(PKI_CERT_ADD_EntryPtr addEntryPtr, int *error)
{
  _DI = FP_OFF(addEntryPtr);
  _ES = FP_SEG(addEntryPtr);
  _AH = PKI_CERT_ADD;
  asm { int TCPIPVECT  } ;
  *error = _AX ;
  return   _DX ;
}
#endif


#ifdef _tcpD1_
/*
@doc DOC_tcpD1_
 ----------------------------------------------------------------------------------
 Delete a certificate
 ----------------------------------------------------------------------------------
 @clib  PKI_CertificateDel | Delete a certificate from the public key infrastructure. |
        <cfont>int PKI_CertificateDel(void far *idPtr, int certType, int *error);<efont> |
 @parm  void far * | idPtr | pointer to certificate identification string
 @parm  int  | certType | certificate type:<nl> 
        <tab>Bit0 = 1: local certificate,<nl>
        <tab>Bit1 = 1: non local certificate (CA or peer)<nl>         
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#error<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success<nl>
        -1:  failed
 @Also  tcpD0.htm | PKI_CertificateAdd |
        tcpD2.htm | PKI_OwnKeyPairAdd  |
                  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xD1<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int PKI_CertificateDel(void far * idPtr, int certType, int *error)
{
  _DI = FP_OFF(idPtr);
  _ES = FP_SEG(idPtr);
  _BX = certType;
  _AH = PKI_CERT_DEL;
  asm { int TCPIPVECT  } ;
  *error = _AX ;
  return   _DX ;
}
#endif


#ifdef _tcpD2_
/*
@doc DOC_tcpD2_
 ----------------------------------------------------------------------------------
 Add a private/public key pair
 ----------------------------------------------------------------------------------
 @clib  PKI_OwnKeyPairAdd | Add a public/private key pair for a local certificate to the public
        key infrastructure. |
        <cfont>int PKI_OwnKeyPairAdd(PKI_OWNKEYPAIR_ADD_EntryPtr keyEntryPtr,<nl>
               <tab><tab><tab><tab><tab>&nbsp; int *error);<efont> |
 @parm  PKI_OWNKEYPAIR_ADD_EntryPtr  | keyEntryPtr |
    <linkto>../../tcpstruc.htm#PKI_OWNKEYPAIR_ADD_Entry<linkmid>Own key pair structure<linktail>
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#error<linkmid>code<linktail>, 0 on success.
 @rdesc 0:  success<nl>
        -1:  failed
 @Also  tcpD0.htm | PKI_CertificateAdd  |
        tcpD1.htm | PKI_CertificateDel  |
                  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xD2<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int PKI_OwnKeyPairAdd(PKI_OWNKEYPAIR_ADD_EntryPtr keyEntryPtr, int *error)
{
  _DI = FP_OFF(keyEntryPtr);
  _ES = FP_SEG(keyEntryPtr);
  _AH = PKI_OWNKEYPAIR_ADD;
  asm { int TCPIPVECT  } ;
  *error = _AX ;
  return   _DX ;
}
#endif


#ifdef _tcpD5_
/*
@doc DOC_tcpD5_
 ----------------------------------------------------------------------------------
 Get SSL connection state information
 ----------------------------------------------------------------------------------

 SSL_GetConnState(int sd, void far * * connStatePtr, int *error)

 @clib  SSL_GetConnState | Get status data of the specified SSL socket connection  |
        <cfont>int SSL_GetConnState(int sd, void far * * connStatePtr, int *error);<efont> |
 @parm  int  | sd | Socket descriptor
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#error<linkmid>code<linktail>, 0 on success.
 @parm  void * | connStatePtr    | Output parameter: Points to internal SSL connection data.

 @rdesc
        0: success, *connStatePtr points to the internal SSL socket connection data<nl>
        -1: failed<nl>
 @comm  Currently this function is only required for the driver
        of the wireless module WL01.
        The driver requires the internal informations, when
        using the EAP_TLS protocol.

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xD5<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.17 | V1.17

 @target_clib V2.12
*/
int SSL_GetConnState(int sd, void far * * connStatePtr, int *error)
{
    _BX = sd ;
    _AH = SSL_GET_CONNSTATE;
    asm { int TCPIPVECT  } ;
    *error = _AX;
    *connStatePtr = MK_FP(_CX,_DI);
    return _DX ;
}
#endif



#ifdef _tcpD6_
/*
@doc DOC_tcpD6_
 ----------------------------------------------------------------------------------
 Close a SSL session
 ----------------------------------------------------------------------------------
 @clib  SSL_HandshakeComplete | Check handshake status.  |
        <cfont>int SSL_HandshakeComplete(int sd,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned int timeout);<efont> |
 @parm  int  | sd | Socket descriptor
 @parm  int  | timeout | Block period in milliseconds:<nl>
                        <ul>
                        = 0xFFFF for block forever<nl>
                        = 0 for no blocking (polling)<nl>
                        = 1 through 65534 milliseconds maximum wait.<nl>
                        <ule>
 @rdesc status:<nl>
        <ul>
        -3:<s2>  Handshake failure<nl>
        -2:<s2>  Invalid socket descriptor<nl>
        -1:<s2>  Not a TCP type socket<nl>
        0:<s2>  Either not an SSL type socket or handshake in progress<nl>
        1:<s2>  SSL handshake completed<nl>
        <ule>
 @comm  Use of this function is optional.<s2>  It allows the user to
       determine whether or not the SSL handshake process has completed and
       that the data socket is now ready for data transmission and
       reception of user data.<nl>
       <nl>
       This API can be used in either polling mode
       (<cfont>timeout<efont> = 0) or blocking mode.<s2>
       Blocking mode will return as soon as the status indication
       return value is non-zero, or the specified time-out period
       has elapsed.<s2>
       The <cfont>timeout<efont> parameter may be set to 0xFFFF
       to block for an indefinite amount of time, in which case
       the return value is guaranteed to be non-zero on return.
       <nl>
       <nl>
       Alternatively, the user can simply make repeated calls to the
       <linkto>tcp0F.htm<linkmid>send()<linktail> and/or
       <linkto>tcp10.htm<linkmid>recv()<linktail> functions until this
       handshake is completed.<s2>
       The SSL handshake is performed in the user's thread, so one of these
       three functions must be called in order to complete the SSL connection.
       <nl>

 @Also  tcpD8.htm | SSL_SessionNew |
        tcp0F.htm | send()     |
        tcp10.htm | recv()
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xD6<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.10 | V1.00

 @target_clib V2.07
*/
int SSL_HandshakeComplete(int sd, unsigned int timeout)
{
    _CX = timeout ;
    _BX = sd ;
    _AH = SSL_HANDSHAKE_COMPLETE;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif


#ifdef _tcpD7_
/*
@doc DOC_tcpD7_
 ----------------------------------------------------------------------------------
 Close a SSL session
 ----------------------------------------------------------------------------------
 @clib  SSL_SessionClose | Close a SSL session.  |
        <cfont>int SSL_SessionClose(int sessionID, int *error);<efont> |
 @parm  int  | sessionId | Session ID
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#error<linkmid>code<linktail>, 0 on success.
 @rdesc 0: Success<nl>
        -1:  failed
 @comm  All cached connection information in this session will be freed too.
        User should close the SSL connection or the socket, first.

 @Also  tcpD8.htm | SSL_SessionNew |
                  |                |
                  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xD7<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int SSL_SessionClose(int sessionID, int *error)
{
  _BX = sessionID;
  _AH = SSL_SESSION_CLOSE;
  asm { int TCPIPVECT  } ;
  *error = _AX ;
  return   _DX ;
}
#endif

#ifdef _tcpD8_
/*
@doc DOC_tcpD8_
 ----------------------------------------------------------------------------------
 Open a new SSL session
 ----------------------------------------------------------------------------------
 @clib  SSL_SessionNew | Open a new SSL session. Could be used as either SSL
        server session or SSL client session. If it is used as a server session
        the field certIdentity in the structure should be non-null, otherwise
        the SSL server can't run on this session. |
        <cfont>int SSL_SessionNew(SSL_SESSION_NEW_EntryPtr newSessionPtr,<nl>
               <tab><tab><tab><tab>&nbsp;&nbsp; int *error);<efont> |
 @parm  SSL_SESSION_NEW_EntryPtr  | newSessionPtr |
    <linkto>../../tcpstruc.htm#SSL_SESSION_NEW_Entry<linkmid>New SSL structure<linktail>
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#error<linkmid>code<linktail>, 0 on success.
 @rdesc <gt>0: Session ID<nl>
        -1:  failed
 @comm Each session maintains its own connect information for the convenience
       of resumption.<s2> You can resume a previous connection only if the current
       connect attempt and the previous one are in the same SSL session, and
       your previous connection cache hasn't been overwritten yet.<nl>
       <nl>
       For SSL server, all connections spawned from a single listening socket
       belong to one session, you should assign the session ID to the listening
       socket. All accepted sockets will inherit that session ID.<nl>
       <nl>
       For SSL client, user determines which session one connection belongs to.
       For example, users may decide that any connection to the same SSL server
       uses a single session ID, so that when user is trying to connect to the
       same server again, he may resume the previous connection.

 @Also  tcpD9.htm | SSL_SessionProp |
        tcpDA.htm | SSL_SessionOpt  |
        tcpD7.htm | SSL_SessionClose

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xD8<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int SSL_SessionNew(SSL_SESSION_NEW_EntryPtr newSessionPtr, int *error)
{
  _DI = FP_OFF(newSessionPtr);
  _ES = FP_SEG(newSessionPtr);
  _AH = SSL_SESSION_NEW;
  asm { int TCPIPVECT  } ;
  if (_DX == 0)
  {
    *error = _DX;
    return _AX;     // AX contains SessionID
  }
  else
  {
    *error = _AX ;  // AX contains ErrorCode
    return   _DX ;
  }
}
#endif

#ifdef _tcpD9_
/*
@doc DOC_tcpD9_
 ----------------------------------------------------------------------------------
 Set proposals for a SSL session
 ----------------------------------------------------------------------------------
 @clib  SSL_SessionProp | Use this function to set proposals for a SSL session.
        For a client session, the proposals are used to construct the Client
        Hello message. For a server session, the proposals are used to match
        Client Hello message in order to determine the final cipher suite to use. |
        <cfont>int SSL_SessionProp(int sessionID, int far *proposals, int count,<nl>
              <tab><tab><tab><tab><tab>int *error);<efont> |
 @parm  int   | sessionID | Session ID for SSL session
 @parm  int * | proposals | Array of integer with Session proposals
 @parm  int  | count | Number of entries in the proposal array
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#error<linkmid>code<linktail>, 0 on success.
 @rdesc 0: Suceess<nl>
        -1:  failed
 @comm To use this function on a server session, a previous call to function
       <linkto>tcpDA.htm<linkmid>SSL_SessionOpt<linktail> is needed.
       If the user doesn't call this function to set any session proposals,
       the default value is going to be used.<nl><nl>
       <bold>Possible proposals array entries:<bolde><nl>
       @raw
             TLS_RSA_NULL_MD5          = 0x0001
             TLS_RSA_NULL_SHA          = 0x0002
             TLS_RSA_EXPORT_RC4_40_MD5 = 0x0003
             TLS_RSA_RC4_128_MD5       = 0x0004
             TLS_RSA_RC4_128_SHA       = 0x0005
             TLS_RSA_3DES_EDE_CBC_SHA  = 0x000A
             TLS_RSA_AES_128_CBC_SHA   = 0x002F
             TLS_RSA_AES_256_CBC_SHA   = 0x0035
             TLS_RSA_EPT1K_RC4_56_SHA  = 0x0064

 @Also  tcpD8.htm | SSL_SessionNew  |
        tcpDA.htm | SSL_SessionOpt  |
                  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xD9<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.07 | V1.00

 @target_clib V2.02
*/
int SSL_SessionProp(int sessionID, int far *proposals, int count, int *error)
{
  _DI = FP_OFF(proposals);
  _ES = FP_SEG(proposals);
  _BX = sessionID;
  _CX = count;
  _AH = SSL_SESSION_PROP;
  asm { int TCPIPVECT  } ;
  *error = _AX ;
  return   _DX ;
}
#endif

#ifdef _tcpDA_
/*
@doc DOC_tcpDA_
 ----------------------------------------------------------------------------------
 Set options for a SSL session
 ----------------------------------------------------------------------------------
 @clib  SSL_SessionOpt | Call this function to set SSL session options. |
        <cfont>int SSL_SessionOpt(int sessionID, int option, int value,<nl>
              <tab><tab><tab><tab>&nbsp;&nbsp; int *error);<efont> |
 @parm  int  | sessionID | Session ID for SSL session
 @parm  int  | option    | option<nl>
             <ul>1: Client Authentication<nl>
                 2: Server Proposals<ule>
 @parm  int  | value     | option value<nl>
             <ul>0: disable option<nl>
                 1: enable option<ule>
 @parm  int  | error     | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#error<linkmid>code<linktail>, 0 on success.
 @rdesc 0: Suceess<nl>
        -1:  failed
 @comm The client authentication option is used to enable client authentication
       on a SSL server session. It takes effect only if the session is bound to an
       SSL server socket, in which case, upon receiving the ClientHello message,
       the SSL server is going to send back a CertificateRequest message along with its
       own Certificate, ServerHello and ServerHelloDone messages.<nl>
       <nl>
       The server proposals option is used to allow the SSL server to have more control
       on which cipher suite to use. If this option is not used on an SSL server session,
       upon receiving a ClientHello message, the SSL server just chooses the first matched
       cipher suite from its own session proposal list, according to server's preference.
       If a cipher suite proposed by the client is not the SSL server session's proposal
       list, even if the SSL server supports that cipher suite, it won't be chosen.
       For example, if server proposals option is enabled and server prefers cipher suites
       1,2,3,4 and in this order. However, client only offers 4,3,2 and in this order,
       then cipher suite 2 will be chosen.

 @Also  tcpD8.htm | SSL_SessionNew  |
        tcpD9.htm | SSL_SessionProp  |
        tcpDB.htm | SSL_AddClientCA

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xDA<linkmid>documentation<linktail>
        for more details.

 @target      SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int SSL_SessionOpt(int sessionID, int option, int value, int *error)
{
  _BX = sessionID;
  _DX = option;
  _CX = value;
  _AH = SSL_SESSION_OPT;
  asm { int TCPIPVECT  } ;
  *error = _AX ;
  return   _DX ;
}
#endif

#ifdef _tcpDB_
/*
@doc DOC_tcpDB_
 ----------------------------------------------------------------------------------
 Add a client CA certificate
 ----------------------------------------------------------------------------------
 @clib  SSL_AddClientCA | Call this function to add client CAs to ServerHello message. |
        <cfont>int SSL_AddClientCA(int sessionID, void far *caIdPtr,<nl>
              <tab><tab><tab><tab><tab>int *error);<efont> |
 @parm  int          | sessionID | Session ID for SSL session
 @parm  void far *   | caIdPtr   | Pointer to client CA certificate identity name
 @parm  int  | error | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#error<linkmid>code<linktail>, 0 on success.
 @rdesc 0: Suceess<nl>
        -1:  failed
 @comm If client authentication option is used to enable client authentication
       on a SSL server session, this call can be used to add CAs to the ServerHello message
       (called CertificateRequest).<nl>
       This function must be called against an SSL server session. The SSL server will list
       CA's Distinguished Name to the client in his ServerHello message . This function can
       be called multiple times to add multiple potential CAs for client certificates.
       <nl>
       Before you can use this call, the client CAs certificate must be added to the PKI.

 @Also  tcpD0.htm | PKI_CertificateAdd  |
        tcpD8.htm | SSL_SessionNew      |
        tcpDA.htm | SSL_SessionOpt
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xDB<linkmid>documentation<linktail>
        for more details.

 @target      SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int SSL_AddClientCA(int sessionID, void far *caIdPtr, int *error)
{
  _BX = sessionID;
  _DI = FP_OFF(caIdPtr);
  _ES = FP_SEG(caIdPtr);
  _AH = SSL_CLI_CA_ADD;
  asm { int TCPIPVECT  } ;
  *error = _AX ;
  return   _DX ;
}
#endif

#ifdef _tcpDC_
/*
@doc DOC_tcpDC_
 ----------------------------------------------------------------------------------
 Start the SSL client
 ----------------------------------------------------------------------------------
 @clib  SSL_ClientStart | Call this function to start the SSL client and SSL handshaking.
        Before this call, the user should set proper socket options on socket
        descriptor.  |
        <cfont>int SSL_ClientStart(int sd, char far * srvCommonName, int *error);<efont> |
 @parm  int  | sd | Socket descriptor
 @parm  char far * | srvCommonName | Server common name.<nl>
        The common name is used to verify the certificate of the peer. If user
        passes in a NULL string, the certificate identity is not checked. This
        means, any valid certificate, even if it belongs to a bad party, will be
        accepted.
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#error<linkmid>code<linktail>, 0 on success.
 @rdesc 0: Success<nl>
        -1:  failed
 @comm  The certificate identity (common name field) may contain the wildcard character
        * which is considered to match any single domain name component or component fragment.
        E.g., "*.a.com" in certificate Common Name matches the server common name
        "foo.a.com" but not "bar.foo.a.com". And certificate common name "f*.com" matches
        server common name "foo.com" but not "bar.com".

 @Also  tcpD8.htm | SSL_SessionNew |
        tcp16.htm | setsockopt     |
                  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xDC<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int SSL_ClientStart(int sd, char far *srvCommonName, int *error)
{
  _BX = sd;
  _DI = FP_OFF(srvCommonName);
  _ES = FP_SEG(srvCommonName);
  _AH = SSL_CLI_START;
  asm { int TCPIPVECT  } ;
  *error = _AX ;
  return   _DX ;
}
#endif

#ifdef _tcpDD_
/*
@doc DOC_tcpDD_
 ----------------------------------------------------------------------------------
 Send queued SSL user data
 ----------------------------------------------------------------------------------
 @clib  SSL_SendFlush | Queued SSL user data will be flushed.
        SSL will queue user data if the send path is not triggered up when
        socket option TCP_SSL_SEND_MIN_SIZE is greater than zero. All data
        will be sent out rigth away, if this function is called. |
        <cfont>int SSL_SendFlush(int sd, int *error);<efont> |
 @parm  int  | sd | Socket descriptor
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#error<linkmid>code<linktail>, 0 on success.
 @rdesc 0: Success<nl>
        -1:  failed

 @Also  tcp16.htm | setsockopt     |
                  |                |
                  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xDD<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int SSL_SendFlush(int sd, int *error)
{
  _BX = sd;
  _AH = SSL_SEND_FLUSH;
  asm { int TCPIPVECT  } ;
  *error = _AX ;
  return   _DX ;
}
#endif


#ifdef _tcpDE_
/*
@doc DOC_tcpDE_
 ----------------------------------------------------------------------------------
 Close a SSL connection
 ----------------------------------------------------------------------------------
 @clib  SSL_ConnClose | Close a SSL connection.
        The user data will be flushed and a close notify message
        will be send to the SSL peer. User may also close the whole
        socket instead of only closing the SSL layer. |
        <cfont>int SSL_ConnClose(int sd, int *error);<efont> |
 @parm  int  | sd | Socket descriptor
 @parm  int  | error    | Output parameter:<s2>Failure
        <linkto>../../iperrlst.htm#error<linkmid>code<linktail>, 0 on success.
 @rdesc 0: Success<nl>
        -1:  failed
 @comm  Note that the peer may not accept any data after the SSL layer
        is closed.

 @Also  tcp02.htm | closesocket    |
                  |                |
                  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xDE<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int SSL_ConnClose(int sd, int *error)
{
  _BX = sd;
  _AH = SSL_CONN_CLOSE;
  asm { int TCPIPVECT  } ;
  *error = _AX ;
  return   _DX ;
}
#endif



#ifdef _tcp7F_
/*
@doc DOC_tcp7F_
 ----------------------------------------------------------------------------------
 Set various TCPIP options
 ----------------------------------------------------------------------------------
 @clib  TCPIP_SetOption | Set TCPIP option.
        This call is used to set various options that are used by the TCP/IP stack.
        | <cfont> int TCPIP_SetOption(int	optionName, long optionValue);<efont> |
 @parm  int  | optionName | The option to change (see below)

 @parm  long  | optionValue  | The value to change it to

 @rdesc 0: Success<nl>
        -1:  failed

 @comm
 Option constants (defined at TCPIPAPI.H):<nl>
 <ul>
 <li>TCPIP_OPTION_ARP_MAX_RETRY      4<nl>
 The maximum number of ARP retries before going into the ARP quiet time state.
   Default: 6, Minimum: 1<nl>
 <li>TCPIP_OPTION_ARP_TIMEOUT_TIME   5<nl>
  The amount of time in seconds between ARP retries. Default: 1, Minimum: 1<nl>
 <li>TCPIP_OPTION_ARP_QUIET_TIME     6<nl>
 The length of the ARP quiet time state in seconds. Default: 20, Minimum: 1<nl>
 <li>TCPIP_OPTION_ARP_TTL            7<nl>
  The length of time that an ARP entry should be kept in the ARP cache in seconds.
 To disable ARP aging, set to TCPIP_RTE_INF. Default: 600, Minimum: 1 <nl>
 <li>TCPIP_IP_FORWARDING            13<nl>
  A boolean(0 or 1) to enable IP forwarding. Default: 1 <nl>
 <li> TCPIP_IP_DBCAST_FORWARD        14<nl>
 A boolean (0 or 1) to enable directed broadcast forwarding. Default: 1<nl>
 <li>TCPIP_OPTION_IP_FRAGMENT       15<nl>
 A boolean (0 or 1) to enable IP fragmentation. Default: 1 <nl>
 <li>TCPIP_OPTION_IP_TTL            16<nl>
 The initial time-to-live in seconds for IP datagrams. Default: 64 , Range: 0-255<nl>
 <li>define TCPIP_OPTION_IP_TOS            17<nl>
  The default Type-Of-Service for IP datagrams. Default: 0, Valid values: 0 - 0xFF<nl>
 <li>define TCPIP_OPTION_IP_FRAG_TTL       18<nl>
 Fragment re-assembly timeout value in seconds. Default: 64, Range: 1-128 <nl>
 <li>TCPIP_OPTION_UDP_CHECKSUM      20<nl>
 A boolean (0 or 1) to enable/disable UDP checksums on outgoing packets. Default: 1<nl>
 <li>TCPIP_OPTION_ARP_MAX_ENTRIES   21<nl>
 Maximum number of ARP entries (32 - 512) in the ARP cache. Default: 64<nl>
 <li>TCPIP_OPTION_ARP_SMART         25<nl>
 Boolean (0 or 1) to indicate whether the ARP logic should store all ARP
 mappings broadcast on the local network, even if we were not waiting for a reply,
 or if the request was not for us. Default: 0 <nl>
 <ule>
 <nl>

@rtos  This library function invokes a RTOS software interrupt.<nl>
       See <linkto>../../tcpipapi.htm#0xAC0x7F<linkmid>documentation<linktail>.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.10 | V1.16

 @target_clib V2.23
*/

int TCPIP_SetOption(int	optionName, long optionValue)
{

  _ES = FP_SEG(&optionValue);
  _DI = FP_OFF(&optionValue);
  _BX = optionName;
  _AH = SET_TRECK_OPTIONS;
  asm { int TCPIPVECT  } ;
  return   _AX ;
}
#endif
/**************************************************************************/
//end tcpip.c
/*************************************************************************/

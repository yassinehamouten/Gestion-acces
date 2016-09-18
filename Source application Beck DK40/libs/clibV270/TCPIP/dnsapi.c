/*******************************************************************************
*
* (c) 2006-2007 by BECK IPC GmbH
* http://www.beck-ipc.com
*
********************************************************************************
*
* Module:    dnsapi.c
* Function:  DNS resolver CLIB-API
*
********************************************************************************
*
* $Header: dnsapi.c, 8, 12.11.2008 12:50:56, Andre Pribil$
*
*******************************************************************************/



#include <dos.h>
#include <common.h>
#include <dnsapi.h>



/*******************************************************************************
* Constants
*******************************************************************************/
// Service numbers
#define DNS_GET_HOST_BY_NAME   0x30
#define DNS_GET_HOST_BY_NAME2  0x31
#define DNS_GET_HOST_BY_ADDR   0x32
#define DNS_GET_HOST_BY_ADDR2  0x33
#define DNS_GET_MAIL_HOSTS     0x34
#define DNS_SET_NAME_SERVER    0x35 

// Number of TCP/IP software interrupt
#define TCPIP_INT  0xAC



/*******************************************************************************
* getHostByName()
*******************************************************************************/
#ifdef _tcp30_
/*
  @doc DOC_tcp30_

  @clib  getHostByName |
         This function can be used to find the IPv4 addresses of a remote
         host associated to its domain name via the Domain Name Service (DNS).<nl>
         The operating system manages a DNS cache. Thus it is save to call this
         function each time you want to connect to the respective domain. The
         function will not issue another request to the name server before the
         cached address has expired. |
         short getHostByName( const char far *domainName,      <nl> |
                              unsigned char nAddresses,        <nl>
                              struct in_addr far *addresses );
  @parm const char far * | domainName |
        Domain name of the host (e.g. "www.beck-ipc.com")
  @parm void far * | nAddresses |
        Maximum number of IP addresses that the function is to return
  @parm struct in_addr far * | addresses |
        Pointer to an array of type <linkto>../../tcpstruc.htm#in_addr<linkmid>
        <cfont>struct in_addr<efont><linktail> where the function is to store
        the found IP addresses; must be large enough to hold the number of IP
        addresses stated in nAddresses.
  @rdesc Number of addresses actually stored in the given array or negative
         <linkto>../../iperrlst.htm#dns<linkmid>error code<linktail>
  @comm DNS queries consume a relative large part of your task's stack.
  @Also  tcp31.htm | getHostByName2 |
         tcp32.htm | getHostByAddr |
         tcp33.htm | getHostByAddr2
  @Also  tcp34.htm | getMailHosts |
         tcp35.htm | setNameServer | |
  @rtos  This library function invokes a RTOS software interrupt.
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0x30<linkmid>DNS_GET_HOST_BY_NAME<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.05 | V1.00
  @target_clib V2.04
*/
short _cdecl getHostByName( const char far *domainName,
                            unsigned char nAddresses,
                            struct in_addr far *addresses )
{
  _ES = FP_SEG( domainName );
  _BX = FP_OFF( domainName );
  _AL = nAddresses;
  _CX = FP_SEG( addresses );
  _DX = FP_OFF( addresses );

  _AH = DNS_GET_HOST_BY_NAME;

  asm int TCPIP_INT;

  return _AX;
}
#endif



/*******************************************************************************
* getHostByName2()
*******************************************************************************/
#ifdef _tcp31_
/*
  @doc DOC_tcp31_

  @clib  getHostByName2 |
         This function can be used to find the IPv6 addresses of a remote
         host associated to its domain name via the Domain Name Service (DNS).<nl>
         The operating system manages a DNS cache. Thus it is save to call this
         function each time you want to connect to the respective domain. The
         function will not issue another request to the name server before the
         cached address has expired. |
         short getHostByName2( const char far *domainName,        <nl> |
                               unsigned char nAddresses,          <nl>
                               struct in6_addr far *addresses );
  @parm const char far * | domainName |
        Domain name of the host (e.g. "www.beck-ipc.com")
  @parm void far * | nAddresses |
        Maximum number of IP addresses that the function is to return
  @parm struct in6_addr far * | addresses |
        Pointer to an array of type <linkto>../../tcpstruc.htm#in6_addr<linkmid>
        <cfont>struct in6_addr<efont><linktail> where the function is to store
        the found IP addresses; must be large enough to hold the number of IP
        addresses stated in nAddresses.
  @rdesc Number of addresses actually stored in the given array or negative
         <linkto>../../iperrlst.htm#dns<linkmid>error code<linktail>
  @comm DNS queries consume a relative large part of your task's stack.
  @Also  tcp30.htm | getHostByName |
         tcp32.htm | getHostByAddr |
         tcp33.htm | getHostByAddr2
  @Also  tcp34.htm | getMailHosts |
         tcp35.htm | setNameServer | |
  @rtos  This library function invokes a RTOS software interrupt.
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0x31<linkmid>DNS_GET_HOST_BY_NAME2<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.05 | V1.00
  @target_clib V2.04
*/
short _cdecl getHostByName2( const char far *domainName,
                             unsigned char nAddresses,
                             struct in6_addr far *addresses )
{
  _ES = FP_SEG( domainName );
  _BX = FP_OFF( domainName );
  _AL = nAddresses;
  _CX = FP_SEG( addresses );
  _DX = FP_OFF( addresses );

  _AH = DNS_GET_HOST_BY_NAME2;

  asm int TCPIP_INT;

  return _AX;
}
#endif



/*******************************************************************************
* getHostByAddr()
*******************************************************************************/
#ifdef _tcp32_
/*
  @doc DOC_tcp32_

  @clib  getHostByAddr |
         This function can be used to find the (canonical) domain name
         associated with a host by one of its IPv4 addresses via the Domain Name
         Service (DNS).<nl>
         The operating system manages a DNS cache. Thus it is save to call this
         function each time you need the respective domain name. The function
         will not issue another request to the name server before the cached
         name has expired. |
         short getHostByAddr( struct in_addr far *address, <nl> |
                              char far *domainName );

  @parm struct in_addr far * | address |
        Pointer to the host's IP address of type
        <linkto>../../tcpstruc.htm#in_addr<linkmid>
        <cfont>struct in_addr<efont><linktail>.
  @parm char far * | domainName |
        Pointer to a buffer where the function is to store the domain name; A
        domain name can be up to 254 characters long. Adding one byte for the
        trailing zero byte of the string, the buffer must have a size of at
        least 255 bytes.
  @rdesc Zero in case of success or negative
         <linkto>../../iperrlst.htm#dns<linkmid>error code<linktail>
  @comm DNS queries consume a relative large part of your task's stack.
  @Also  tcp30.htm | getHostByName |
         tcp31.htm | getHostByName2 |
         tcp33.htm | getHostByAddr2
  @Also  tcp34.htm | getMailHosts |
         tcp35.htm | setNameServer | |
  @rtos  This library function invokes a RTOS software interrupt.
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0x32<linkmid>DNS_GET_HOST_BY_ADDR<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.05 | V1.00
  @target_clib V2.04
*/
short _cdecl getHostByAddr( struct in_addr far *address,
                            char far *domainName )
{
  _ES = FP_SEG( address );
  _BX = FP_OFF( address );
  _CX = FP_SEG( domainName );
  _DX = FP_OFF( domainName );

  _AH = DNS_GET_HOST_BY_ADDR;

  asm int TCPIP_INT;

  return _AX;
}
#endif



/*******************************************************************************
* getHostByAddr2()
*******************************************************************************/
#ifdef _tcp33_
/*
  @doc DOC_tcp33_

  @clib  getHostByAddr2 |
         This function can be used to find the (canonical) domain name
         associated with a host by one of its IPv6 addresses via the Domain Name
         Service (DNS).<nl>
         The operating system manages a DNS cache. Thus it is save to call this
         function each time you need the respective domain name. The function
         will not issue another request to the name server before the cached
         name has expired. |
         short getHostByAddr2( struct in6_addr far *address, <nl> |
                               char far *domainName );

  @parm struct in_addr far * | address |
        Pointer to the host's IP address of type
        <linkto>../../tcpstruc.htm#in6_addr<linkmid>
        <cfont>struct in6_addr<efont><linktail>.
  @parm char far * | domainName |
        Pointer to a buffer where the function is to store the domain name; A
        domain name can be up to 254 characters long. Adding one byte for the
        trailing zero byte of the string, the buffer must have a size of at
        least 255 bytes.
  @rdesc Zero in case of success or negative
         <linkto>../../iperrlst.htm#dns<linkmid>error code<linktail>
  @comm DNS queries consume a relative large part of your task's stack.
  @Also  tcp30.htm | getHostByName |
         tcp31.htm | getHostByName2 |
         tcp32.htm | getHostByAddr
  @Also  tcp34.htm | getMailHosts |
         tcp35.htm | setNameServer | |
  @rtos  This library function invokes a RTOS software interrupt.
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0x33<linkmid>DNS_GET_HOST_BY_ADDR2<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.05 | V1.00
  @target_clib V2.04
*/
short _cdecl getHostByAddr2( struct in6_addr far *address,
                             char far *domainName )
{
  _ES = FP_SEG( address );
  _BX = FP_OFF( address );
  _CX = FP_SEG( domainName );
  _DX = FP_OFF( domainName );

  _AH = DNS_GET_HOST_BY_ADDR2;

  asm int TCPIP_INT;

  return _AX;
}
#endif



/*******************************************************************************
* getMailHosts()
*******************************************************************************/
#ifdef _tcp34_
/*
  @doc DOC_tcp34_

  @clib  getMailHosts |
         Use this function to determine the mail host(s) of a domain, i.e. host
         accepting internet mail for the domain.<nl>
         The operating system manages a DNS cache. Thus it is save to call this
         function each time you need the respective mail host. The function will
         not issue another request to the name server before the cached mail
         host entry has expired. |
         short getMailHosts( const char far *domainName, <nl> |
                             unsigned char nHosts,       <nl>
                             DnsMailHost far *hosts );

  @parm const char far * | domainName |
        Domain name to find mail hosts for (e.g. "beck-ipc.com")
  @parm unsigned char | nHosts |
        Maximum number of host names that the function is to return
  @parm DnsMailHost far * | hosts |
        Pointer to an array of type <linkto>../../tcpstruc.htm#DnsMailHost<linkmid>
        <cfont>DnsMailHost<efont><linktail> where domain name and preference
        value of the mail hosts will be stored; The array must be large enough
        to hold the number of entries passed in nHosts.
  @rdesc Number of mail hosts actually stored or negative
         <linkto>../../iperrlst.htm#dns<linkmid>error code<linktail>
  @comm DNS queries consume a relative large part of your task's stack.
  @Also  tcp30.htm | getHostByName |
         tcp31.htm | getHostByName2 |
         tcp32.htm | getHostByAddr
  @Also  tcp33.htm | getHostByAddr2 |
         tcp35.htm | setNameServer | |
  @rtos  This library function invokes a RTOS software interrupt.
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0x34<linkmid>DNS_GET_MAIL_HOSTS<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.05 | V1.00
  @target_clib V2.04
*/
short _cdecl getMailHosts( const char far *domainName,
                           unsigned char nHosts,
                           DnsMailHost far *hosts )
{
  _ES = FP_SEG( domainName );
  _BX = FP_OFF( domainName );
  _AL = nHosts;
  _CX = FP_SEG( hosts );
  _DX = FP_OFF( hosts );

  _AH = DNS_GET_MAIL_HOSTS;

  asm int TCPIP_INT;

  return _AX;
}
#endif



/*******************************************************************************
* setNameServer()
*******************************************************************************/
#ifdef _tcp35_
/*
  @doc DOC_tcp35_

  @clib  setNameServer |
         This function can be used to add a prioritised name server which
         will be queried before all other name servers. Normally the DNS
         resolver determines name server addresses automatically from network
         devices configured via DHCP or PPP. In addition you can specify two
         name servers in the CHIP.INI
         <linkto>../../config.htm#DNS_NAME_SERVER1<linkmid>configuration file<linktail>.
         Name servers found via DHCP have the lowest priotity. Next come name
         servers found via PPP, then the two configured in CHIP.INI.
         The name server added here has the highest priority.
         Note that calling this function a second time overwrites the name
         server address added first. |
         short setNameServer( int addressFamily,   <nl> |
                              void far *address );

  @parm int | addressFamily |
        Address family, AF_INET for IPv4 or AF_INET6 for IPv6
  @parm void far * | address |
        Pointer to the IP address of the name server; should point to a
        structure of either type <linkto>../../tcpstruc.htm#in_addr<linkmid>
        <cfont>struct in_addr<efont><linktail> or
        <linkto>../../tcpstruc.htm#in6_addr<linkmid>
        <cfont>struct in6_addr<efont><linktail>.
  @rdesc Zero in case of success or negative
         <linkto>../../iperrlst.htm#dns<linkmid>error code<linktail>
  @Also  tcp30.htm | getHostByName |
         tcp31.htm | getHostByName2 |
         tcp32.htm | getHostByAddr
  @Also  tcp33.htm | getHostByAddr2 |
         tcp34.htm | getMailHosts | |
  @rtos  This library function invokes a RTOS software interrupt.
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0x35<linkmid>DNS_SET_NAME_SERVER<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.05 | V1.00
  @target_clib V2.04
*/
short _cdecl setNameServer( int addressFamily,
                            void far *address )
{
  _CX = addressFamily;
  _ES = FP_SEG( address );
  _BX = FP_OFF( address );

  _AH = DNS_SET_NAME_SERVER;

  asm int TCPIP_INT;

  return _AX;
}
#endif



// End of file








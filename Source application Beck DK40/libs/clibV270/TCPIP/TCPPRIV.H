/****************************************************************************
* (C) 1999-2006 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module        : TCPPRIV.H
* Function      : Private information for TCP/IP C Library code
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\TCPIP\TCPPRIV.H, 28, 28.09.2007 14:20:01, Markus Bartat$

*****************************************************************************************************/

#ifndef _TCPPRIV_H__
#define _TCPPRIV_H__


/*****************************************************************************/
//API defines
/*****************************************************************************/

// TCP/IP Services
#define TCPIPVECT  (0xAC)

#define API_OPENSOCKET          0x01
#define API_CLOSESOCKET         0x02
#define API_BIND                0x03  /* assign an address to an unnamed socket,port*/
#define API_CONNECT             0x04  /* TCP client only, connect  */
#define API_RECVFROM            0x05  /* UDP recvfrom */
#define API_SENDTO              0x06  /* UDP sendto*/
#define API_HTONS               0x07
#define API_INETADDR            0x08
#define API_SLEEP               0x09
#define API_MALLOC              0x0A
#define API_FREE                0x0B
#define API_GETRCV_BYTES        0x0C
#define API_ACCEPT              0x0D  /* TCP server only  */
#define API_LISTEN              0x0E  /* TCP server only  */
#define API_SEND                0x0F  /* TCP  only  */
#define API_RECV                0x10  /* TCP  only  */
#define API_INETTOASCII         0x11
#define API_RESETCONNECTION     0x12  /* TCP  only  */
#define API_SETLINGER           0x13  /* TCP  only  */
#define API_SETREUSE            0x14  /* TCP server only */
#define API_SETIPTOS            0x15  /* set Type Of Service for a socket */
#define API_SETSOCKOPT          0x16  /* set socket options*/
#define API_GETSOCKOPT          0x17  /* get socket options*/
#define API_SETBLOCKINGMODE     0x18  /* set a socket in blocking or non blocking mode*/
#define API_REGISTERCALLBACK    0x19  /* register call back function on socket events*/
#define API_SELECT              0x1A  // select()
#define API_GET_SOCKETERROR     0x21  /* Get the last socket error */
#define API_GET_TCP_STATE       0x22
#define API_FINDALL_SOCKETS     0x23  
#define API_GET_TCP_STATE_IP_ALL   0x24  // recommended at sc123, because of ipv6 addresses
#define API_FINDALL_SOCKETS_IP_ALL 0x25  // recommended at sc123, because of ipv6 addresses
#define API_SHUTDOWN            0x26     // Shutdown a socket in read,write or both directions
#define API_RECVFROM_TO         0x27     // Recvfrom, which returns also the dest. address
#define API_SENDTO_IFACE        0x28     // Send UDP datagram via specified interface handle
#define API_RECVFROM_TO_IFACE   0x29     // Recvfromto_iface

#define PPPCLIENT_INSTALLED     0x40     /* PPP client API calls */
#define PPPCLIENT_OPEN          0x41
#define PPPCLIENT_CLOSE         0x42
#define PPPCLIENT_GET_STATUS    0x43
#define PPPCLIE_GET_DNSIP       0x44     /* Get DNS ip negotiated by the remote PPP server */
#define PPPCLIENT_SET_OPTIONS   0x45
#define PPPCLIENT_OPEN_IPV6     0x46
#define PPPCLIENT_PAUSE         0x47

#define PPPSERVER_INSTALLED     0x50     /* PPP server API calls */
#define PPPSERVER_SUSPEND       0x51
#define PPPSERVER_ACTIVATE      0x52
#define PPPSERVER_GET_STATUS    0x53
#define PPPSERVER_GET_CFG       0x54
#define PPPSERVER_SET_OPTIONS   0x55
#define PPPSERVER_GET_CFG_IPV6  0x56
#define PPPSERVER_PAUSE         0x57

#define API_SNMP_GET            0x60  /* SNMP API calls, only available at SNMP RTOS versions */
#define API_FTP_GET_LOGIN       0x65  /* get addresses of FTP server login counters*/
#define API_TELNET_GET_LOGIN    0x66  /* get addresses of Telnet server login counters*/
#define API_GET_TELNET_STATE    0x67  /* get state of Telnet server 1:active, 0:closed*/

#define GET_INSTALLED_SERVERS   0x70  /* Get list of installed servers and devices */
#define REINIT_ETHERNET         0x71  /* Reconfigure ethernet interface */

#define DHCP_USE                0x72  /* DHCP usage */
#define DHCP_STAT               0x73
#define TCPIP_STATISTICS        0x74

#define PING_OPEN               0x75  /* Ping API */
#define PING_CLOSE              0x76
#define PING_STATISTICS         0x77

#define GET_MEMORY_INFO         0x78  /* memory */

#define SET_SERVER_IDLE_TIMEOUT 0x79
#define IP_CALLBACK             0x7A  /* Install a users callback for filter out ip incoming packets */
#define ARP_USER_CB             0x7B  /* Install a users callback for filter out arp incoming packets */
#define IP_CALLBACK_SND         0x7C  /* Install a users callback for checking outgoing ip packets */
#define IPCONF_CALLBACK         0x7D  /* Install a users callback for IP configuration changes */

#define SET_TRECK_OPTIONS       0x7F  /* Set vairous options on the TCPIP stack */


#define ADD_DEFAULT_GATEWAY     0x80  /* Routing */
#define DEL_DEFAULT_GATEWAY     0x81
#define GET_DEFAULT_GATEWAY     0x82
#define ADD_STATIC_ROUTE        0x83
#define DEL_STATIC_ROUTE        0x84

#define GET_ARP_ENTRY_BY_IP     0x85  /* ARP cache */
#define GET_ARP_ENTRY_BY_PHYS   0x86
#define DEL_ARP_ENTRY_BY_IP     0x87
#define DEL_ARP_ENTRY_BY_PHYS   0x88
#define ADD_ARP_ENTRY           0x89
#define GET_ARPROUTE_CACHE      0x8A

#define GET_IFACE_ENTRIES       0x8D  /* Interface information */
#define SET_IFACE_MTU           0x8E  /* Interface mtu */
#define GET_IFACE_ENTRIES_EXT   0x8F  /* Extended Interface information */

#define ADD_IGMP_MEMBERSHIP     0x90  /* IGMP */
#define DROP_IGMP_MEMBERSHIP    0x91
#define MCASTIP_TO_MACADDR      0x92

#define DEV_GET_IP              0x9F  /* Get IP and netmask of user interface */
#define DEV_OPEN_IFACE          0xA0  /* Install and open interface and device driver */
#define DEV_CLOSE_IFACE         0xA1  /* Close interface */
#define DEV_RECV_IFACE          0xA2  /* Move received data into TCPIP stack */
#define DEV_RECV_WAIT           0xA3  /* Block a task until received data event has occured */
#define DEV_NOTIFY_ISR          0xA4  /* Notify TCPIP stack from an ISR, that there are data waiting to received */
#define DEV_GET_BUF             0xA5  /* Get a buffer from TCPIP stack for fill in received data*/
#define DEV_SND_COMPLETE        0xA6  /* Inform the TCPIP stack, that data has been sent*/
#define DEV_WAIT_DHCP_COMPLETE  0xA7  /* Wait for DHCP request completion*/

#define DEV_PPP_REGISTER_CHAP   0xA8  // Register a CHAP authentication callback
#define DEV_PPP_REGISTER_PAP    0xA9  // Register a PAP authentication callback
#define DEV_PPP_SET_OPTION      0xAA  // Set ppp options
#define DEV_PPP_GET_PEER_IP     0xAB  // Get the ip of the ppp remote peer
#define DEV_PPP_GET_PEER_DNS    0xAC  // Get DNS server address primary or secondary

#define DEV_GET_HANDLE_BYNAME   0xAD  // Get driver handle pointer by driver name
#define DEV_CONFIG_IFACE        0xAE  // IPv4 Configuration of a device interface (multiple addresses possible)
#define DEV_CONFIG_IFACE_IPV6   0xAF  // IPv6 Configuration of a device interface (multiple addresses possible)
#define DEV_UNCONFIG_IFACE      0xB0  // Remove an IPv4 or IPv6 Configuration of a device interface

#define DEV_PPP_GET_PEER_IPV6   0xB1  // Get the IPv4 address of the PPP remote peer
#define DEV_GET_DHCP_DATA       0xB2  // Get DHCP boot data of a specified device interface
#define DEV_NOTIFY_IOCTL        0xB3  // Execute/Trigger specific device functions
#define DEV_SET_SPECFLAGS       0xB4  // Set/Erase specific flags (e.g.forwarding device driver flags)


//IPv6
#define GET_IPV6_IFACE_ENTRIES      0xC0 //Read for each interface all ipv6 informations
#define INET_PTON                   0xC1 //Convert an IP address from standard text representation to binary
#define INET_NTOP                   0xC2 //Convert an IP address from binary to text representation
#define API_OPENSOCKET_IPV6         0xC3 //Open a IPv6 (AF_INET6) socket

#define IPSEC_VECTORS               0xCFu
// PKI, SSL
#define PKI_CERT_ADD                0xD0
#define PKI_CERT_DEL                0xD1
#define PKI_OWNKEYPAIR_ADD          0xD2
#define SSL_GET_CONNSTATE           0xD5
#define SSL_HANDSHAKE_COMPLETE      0xD6
#define SSL_SESSION_CLOSE           0xD7
#define SSL_SESSION_NEW             0xD8
#define SSL_SESSION_PROP            0xD9
#define SSL_SESSION_OPT             0xDA
#define SSL_CLI_CA_ADD              0xDB
#define SSL_CLI_START               0xDC
#define SSL_SEND_FLUSH              0xDD
#define SSL_CONN_CLOSE              0xDE

// CRYPT functions
#define CRYPT_HASH                  0xDF
#define CRYPT_CIPHER                0xE0



struct sockaddr_in_ipstack        //old definition at treck2.x
{
	short           sin_family; // AF_INET
	unsigned int    sin_port;   // 16bit Port Number in network byte order
	struct  in_addr sin_addr;   // 32bit netid/hostid in network byte order
	char            sin_zero[8];// unused
};


struct sockaddr_in_ipstackV2    //new definition at treck4.x used at sc123
{
   unsigned char   sin_len;     //
	unsigned char   sin_family;  // AF_INET or AF_INET6
	unsigned int    sin_port;    // 16bit Port Number in network byte order
	struct  in_addr sin_addr;    // 32bit netid/hostid in network byte order
	char            sin_zero[8]; // unused
};


/*****************************************************************************/
#endif _TCPPRIV_H__
/*****************************************************************************/
//end tcppriv.h
/***************************************************************************/

/****************************************************************************
* (C) 1999-2012 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module        : TCPIPAPI.H
* Function      : Constants and data structures for access to
*                 the Socket interface
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\TCPIPAPI.H, 40, 23.01.2009 14:06:20, Markus Bartat$

******************************************************************************/

#ifndef _TCPIP_API_H__
#define _TCPIP_API_H__
/*****************************************************************************/

// Compilation configuration switches for target version
#include <target.h>

/*****************************************************************************
*
* BSD Structure Definitions
*
*****************************************************************************/
struct sockaddr
{
	unsigned char  sa_len;      /* Total Length */
	unsigned char  sa_family;   /* Address Family AF_xxx */
	char    sa_data[14]; /* up to 14 bytes of protocol specific address */
};


struct in_addr
{
   unsigned long s_addr;       /* 32bit netis/hostid address in network byte order */
};

// struct sockaddr_in has changed from SC12/SC13 RTOS TCPIP stack to SC123 RTOS TCPIP stack
#ifdef TCPIP_STACK_V2
struct sockaddr_in              // For TCP/IP with IPv6 support
{
   unsigned char   sin_len;     //
	unsigned char   sin_family;  // AF_INET
	unsigned int    sin_port;    // 16bit Port Number in network byte order
	struct  in_addr sin_addr;    // 32bit netid/hostid in network byte order
	char            sin_zero[8]; // unused
};
#else
struct sockaddr_in              // For original SC12 TCP/IP stack
{
	short           sin_family; // AF_INET
	unsigned int    sin_port;   // 16bit Port Number in network byte order
	struct  in_addr sin_addr;   // 32bit netid/hostid in network byte order
	char            sin_zero[8];// unused
};
#endif    // TCPIP_STACK_V2


struct in6_addr
{
    //128-bit IPv6-formatted address in network byte order
    union
    {
        unsigned char  ip6U8[16];
        unsigned short ip6U16[8];
        unsigned long  ip6U32[4];
    }ip6Addr;
};


struct sockaddr_in6
{
    unsigned  char   sin6_len;       //Length (in bytes) of the sockaddr_in6 structure
    unsigned char    sin6_family;    //Address family, set to AF_INET6
    unsigned short   sin6_port;      //Transport layer port number
    unsigned long    sin6_flowinfo;  //IPv6 packet header Flow Label
    struct in6_addr  sin6_addr;      //128-bit IPv6-formatted address in network byte order.
    unsigned long    sin6_scope_id;  //sin6_scope_id for local scope (i.e. link-local, site-local)
};

struct sockaddr_storage
{
    union
    {
        struct sockaddr_in6     ipv6;
        struct sockaddr_in      ipv4;
    }addr;
};


////////////////////////////////////////////////////
// Support structures for select()
////////////////////////////////////////////////////

struct timeval {
  long    tv_sec;         // seconds
  long    tv_usec;        // and microseconds
};


#ifdef TCPIP_STACK_V2
#define MAX_BECK_SOCKETS  (256)     // SC1x3 systems
#else
#define MAX_BECK_SOCKETS  (64)      // SC1x systems
#endif

typedef unsigned int fd_mask ;
typedef struct fd_set
{
    fd_mask fds_bits[MAX_BECK_SOCKETS/16] ;    // Socket bit field
} fd_set;

#define FD_SET(n, p)                                    \
    ((p)->fds_bits[(n) >> 4] |=                         \
                           (fd_mask)(1 << ((n) & 0xF)))
#define FD_CLR(n, p)                                      \
    ((p)->fds_bits[(n) >> 4] &=                           \
                           (fd_mask)(~(1 << ((n) & 0xF))))
#define FD_ISSET(n, p)            \
    (   ((p)->fds_bits[(n) >> 4]) \
      & (1 << ((n) & 0xF))  )

#define FD_ZERO(p)         memset(p, 0, sizeof(*(p)))
#define FD_COPY(src, dest) memcpy(dest, src, sizeof(*(dest)))


/*****************************************************************************/
struct recv_params
{
   char  far              *   bufferPtr;
   int                        bufferLength;
   int                        flags;            /* Blocking or  dontwait */
   struct sockaddr far    *   fromPtr;          /* only needed for UDP */
   int  far               *   fromlengthPtr;    /* only needed for UDP */
   unsigned long              timeout;          /* timeout milliseconds */
};

struct recv_params2
{
   char  far              *   bufferPtr;
   int                        bufferLength;
   int                        flags;            /*Blocking or  dontwait*/
   struct sockaddr far    *   fromPtr;          /* only needed for UDP */
   int  far               *   fromlengthPtr;    /* only needed for UDP */
   unsigned long              timeout;          /*timeout milliseconds*/
   unsigned char  far     *   fromPhyAddrPtr;   /*physical address*/
   int  far               *   fromPhyAddrLenPtr;/*length of physical address*/
   void  far      *       *   DevHandlePtr;     /*interface handle*/
};

struct send_params
{
   const char far         *   bufferPtr;
   int                        bufferLength;
   int                        flags;            /* Blocking or  dontwait */
   struct sockaddr far    *   toPtr;            /* only needed for UDP */
   int far                *   tolengthPtr;      /* only needed for UDP */

};

/*****************************************************************************/
//Set and get socket options structure
/*****************************************************************************/

typedef struct tag_setsockopt
{
   int protocol_level;            /* protocol level ip level,tcp level or socket level */
   int optionName;                /* options name */
   const char far * optionValue;  /* pointer to the option value */
   int optionLength;              /* length of option value */

}SetSocketOption;

typedef struct tag_getsockopt
{
   int protocol_level;            // protocol level ip level,tcp level or socket level
   int optionName;                // options name
   char far   * optionValue;      // pointer to the option value buffer, where Value
                                  // can be filled in by the API call
   int far    * optionLength;     // length of option value buffer

}GetSocketOption;

/*****************************************************************************/
//Socket information (see API call 0x23
/*****************************************************************************/
typedef struct tag_socketinfo
{
   unsigned int  socIndex;
   unsigned char protocol;       /*6:TCP   17 UDP*/
   unsigned int  localPort;
   unsigned long IfIpAddress;
   unsigned int  remotePort;
   unsigned long remoteIP;
   unsigned char tcpState;

}SocketInfo;


/*****************************************************************************/
//Socket information (see API call 0x25
/*****************************************************************************/
typedef struct tag_socketinfo_ipv4v6
{
   unsigned int  socIndex;
   unsigned char protocol;       /*6:TCP   17 UDP*/
   unsigned int  localPort;
   struct in6_addr IfIpAddress;
   unsigned int  remotePort;
   struct in6_addr remoteIP;
   unsigned char tcpState;
}SocketInfoIPv4v6;


typedef  struct tagIpUserCallbackInfo
{
   int              size;        // size of this struct
   unsigned long    srcAddr;     // source IP Address (in long format, already in correct byte order)
   unsigned long    destAddr;    // destination IP Address (in long format, already in correct byte order))
   unsigned int     srcPort;     // source Port (already in correct byte order)
   unsigned int     destPort;    // destination Port (already in correct byte order)
   unsigned char    protocol;    // Protocol (see list below)
   int              fragmented;  // 0: it is a unfragmented package, 1: it is a fragment
   unsigned int     dataLength;  // Length of the data in the IP package (only available if package is not fragmented!)
   void far *       dataPtr;     // Pointer to the IP data (only available if package is not fragmented!)
   void far *       ipHdrPtr;    // Pointer to the IP header
   unsigned int     ipHdrLen;    // length of IP header
   void far *       devHandlePtr; // Device handle pointer of this incoming packet

} IpCallbackUserInfo;


typedef struct ArpUserCallbackInfo
{
   int              size;         // size of this struct
   unsigned int     dataLength;   // Length of the data in the Arp package
   void far *       dataPtr;      // Pointer to the Arp data
   void far *       devHandlePtr; // Device handle pointer of this incoming packet

}ArpCallbackUserInfo_t;

typedef struct tag_ArpHeader
{
   unsigned int     arpHardware;
   unsigned int     arpProtocol;
   unsigned char    arpHardwareLength;
   unsigned char    arpProtocolLength;
   unsigned int     arpOperation;
   unsigned char    arpSendPhyAddress[6];
   unsigned char    arpSendNetAddress[4];
   unsigned char    arpTargetPhyAddress[6];
   unsigned char    arpTargetNetAddress[4];

}ArpHeader;

/*****************************************************************************/
//PPP server config information structure
/*****************************************************************************/
typedef struct tag_pppipcfg_data
{
   char          IP[16];
   char          RemIP[16];
   char          Netmask[16];
   char          Gateway[16];
   unsigned int  comport;     /* 0==EXT, 1==COM of the SC12*/
   unsigned int  auth;        /* 0==No auth, 1==PAP authentication, 2:CHAP*/
   unsigned int  modem;       /* 0==Nullmodem, 1==usage of modem*/
   unsigned int  flow;
   long          baud;
}PPP_IPCfg_Data;

/*****************************************************************************/
//PPP server IPv6 config information structure
/*****************************************************************************/
typedef struct tag_pppipcfg_data_ipv6
{
     char          IP[46];          // Auto configured PPP server IP
     char          RemIP[46];       // Auto configured  Remote peer IP
     unsigned int  comport;         // COM port: EXT=0, COM=1
     unsigned int  auth;            // 0: no authentication 1:PAP 2:CHAP
     unsigned int  modem;           // Analog Modem=1, Null Modem cable=0
     unsigned int  flow;            // Flow control
     long          baud;            // BAUD rate
} PPP_IPCfg_Data_IPv6;
/*****************************************************************************/
//PPP client constants,structures enum
/*****************************************************************************/
#define PPP_MAX_DIAL     7
#define PPPCLIE_MAX_CTRL 3

typedef struct tag_pppdial
{
   char far * modemcmd;     // modem command string
   char far * modemans;     // modem answer  string
   int   timeout;           // seconds
   int   retries;
   char  expect_send;
   /*flag:
     expect = 0: pppclient sends modemcmd and expects modemanswer
     expect = 1: pppclient expects modemanswer and sends modemcmd
   */
}PPPDial;


typedef struct tag_pppclie_hangup
{
   char far *modemcmdmode;           // switch modem into command mode e.g. +++
   int     delay;                    // delay time after switching in seconds
   PPPDial pppdial[PPP_MAX_DIAL];    // modem commands and answer for hangups
}PPP_ModemHangup;


typedef struct tag_pppclie_modem_cmd
{
    char  far * modemcmd;
    char  far * modemans;
    int   timeout;
    int   retries;
}PPPClie_ModemCmd;


typedef struct tag_pppclie_modem_ctrl
{
   //idle interval time, at which the pppclient executes the configured control commands
   int ctrl_idle_secs;
   //modem control commands to execute
   PPPClie_ModemCmd ctrlcmd[3];
}PPPClie_ModemCtrl;


typedef struct tag_ppp_client
{
   /************************************************************************************/
   //user PPP config data
   /************************************************************************************/
   int  port;                     //serial port (0:EXT 1:COM)

   int  auth;                     // 0: no authentication
                                  // 1:PAP  Client must send username and password for PAP authentication to the peer
                                  // 2:CHAP Client must send username and password for CHAP authentication to the peer
                                  // 3:PAP  Client expects PAP username and password  from the peer
                                  // 4:CHAP Client expects CHAP username and password from the peer

   int  modem;                    //modem usage (see enum PPPClient_ModemModes)
   int  flow;                     //serial flow control (0: none, 1:XON/XOFF, 2:RTS/CTS)
   long baud;                     //serial baudrate
   unsigned long idletimeout;     //closing ppp after idle time seconds (0: no closing after idle time)

   char username[50];             //username, if auth <=4 and !=0
   char password[50];             //password, if auth <=4 and !=0

   void far * dptr;               //dummy ptr

   /************************************************************************************/
   //filled in after successful API call: IP cfg data given from server
   /************************************************************************************/
   char PPPClieipAddrStr[16];     // If IP is set to "0.0.0.0" the client expects IP address from the peer,
                                  // the received IP is stored here after connection is established.
                                  // If IP is set to a string != "0.0.0.0", the client wants to use this IP address during the ppp session.
   char PPPClieRemipAddrStr[16];  // If RemoteIP is set to "0.0.0.0", the client allow the peer to use its own IP during the PPP session.
                                  // The RemoteIP is stored here after connection is established.
                                  // If RemoteIP is set to a string != "0.0.0.0" client wants to configure the remote peer with this IP.


   char PPPClienetMaskStr[16];
   char PPPClieipGatewayStr[16];

   /************************************************************************************/
   //modem parameters
   /************************************************************************************/
   PPPDial          pppdial[PPP_MAX_DIAL]; // modem/dial entries
   PPP_ModemHangup  modem_hangup;          // modem hangup commands

   unsigned int    break_modem;     /*
                                       flag for breaking host <-> modem control communication, dialing, waiting for connect,..
                                       setting break_modem to 1, interrupts current modem communication between
                                       SC12 and the modem at a pppclient open or close call,
                                       The pppclient read this flag and breaks the modem dialing, or waiting.
                                       This flag could be set from another task, to interrupt the dialing.
                                       If a ppp link  is established, it doesn't break the session.
                                       Don't forget to set this flag to zero after breaking
                                     */

}PPPClient_Init;



typedef struct tag_ppp_client_ipv6
{
   /************************************************************************************/
   //user PPP config data
   /************************************************************************************/
   int  port;         // serial port (0:EXT 1:COM 2:SER2 3:SER3)
   int  auth;         // 0: no authentication
                      // 1:PAP  Client must send user name and password
                      //        for PAP authentication to the peer
                      // 2:CHAP Client must send user name and password
                      //        for CHAP authentication to the peer
                      // 3:PAP  Client expects PAP user name and password
                      //        from the peer
                      // 4:CHAP Client expects CHAP user name and password
                      //        from the peer
   int  modem;        // modem usage (see enum PPPClient_ModemModes)
   int  flow;         // serial flow control (0: none, 1:XON/XOFF, 2:RTS/CTS)
   long baud;         // serial baudrate
   unsigned long idletimeout;        // Closing PPP after idle time seconds
                                     //    (0: no closing after idle time)
   char username[50];   //username, if auth <=4 and !=0
   char password[50];   //password, if auth <=4 and !=0
   void far * dptr;                      // dummy ptr
   /************************************************************************************/
   //filled in after successful API call: IP cfg data given from server
   /************************************************************************************/
   char PPPClieipAddrStr[46];    //If this IP is set to "::0" client expect IP form the peer, IP is filled in after sucessful connection
                                 //If this IP is set to a string != "::0" client wants to use this IP during the ppp session
   char PPPClieRemipAddrStr[46]; //If RemoteIP is set to "::0" client allow the peer to use its own IP during the PPP session
                                 //the RemoteIP is filled in after sucessful  connection
                                 //If RemoteIP is set to a string != "::0" client wants to configure the remote peer with this IP

   /************************************************************************************/
   //modem parameters
   /************************************************************************************/
   PPPDial              pppdial[PPP_MAX_DIAL];// modem/dial entries
   PPP_ModemHangup      modem_hangup;      // modem hang-up commands
   int                  break_modem;       //flag for interrupt host<->modem communication, break dialing, connect
                                           // control communication (dialing, waiting for connect)
                                           // Setting break_modem to 1 breaks current modem control communication
                                           // between IPC@CHIP and the modem at a PPP client open or close call.
                                           // The PPP client reads this flag and breaks the dialing, if flag is set.
                                           // This flag can be set from another task.  It will not break an established
                                           // PPP link!  Don't forget to clear this flag to zero after breaking.
}PPPClient_Init_IPv6;

/*****************************************************************************/
//PPP client modem mode constants
/*****************************************************************************/
typedef enum
{
       NULLMODEM =0,
       /* No modem (using a "null modem" cable).*/
       MODEM=1,
       /* Modem usage with execution of the specified modem
             commands at pppdial and modem_hangup 1.
       */
       MODEM_CARRIERCHECK_BY_CMD_IDLE =2,
       /* Modem usage with additional "carrier loss" check enabled (in idle case).
            After each time interval during the PPP client receives no serial data,
            the PPP client executes cyclic in intervals of a defined idle time
            an user defined set of modem commands to check the status of the
            modem. The PPP client closes the current connection,
            if the execution of one of these commands failed.
            The idle interval and the modem command set must be specified
            at a variable of type @ref PPPClie_ModemCtrl.
            The PPP client expects the address of this variable at the pointer
            <i>dptr</i> of the @ref PPPClient_Init structure variable.
            Due to the loss of performance caused by the cyclic execution
            of the defined modem commands, we recommend the usage of modem mode
            MODEM_CARRIERCHECK_BY_DCD .
       */
       MODEM_CARRIERCHECK_BY_CMD =3,
       /*
          Modem usage with cyclic "carrier loss" check enabled. Same as
          MODEM_CARRIERCHECK_BY_CMD_IDLE with one difference:<br>
          After each time interval the client executes the configured modem commands.
          In this mode the configured modem commands are not printed
          via STDOUT at execution time, even if chip.ini setting "MODEMTRACE"
          is enabled.<br>
        */
       MODEM_CARRIERCHECK_BY_DCD =4,
       /*
         The PPP client closes the current PPP session, it it detects
         if it detects a "carrier loss" signaled by the connected modem with
         the serial port signal DCD=low.<br>
         This mode is recommended for an efficient and safe detection of
         "carrier loss" during an established PPP session.<br>
       */
}PPPClient_ModemModes ;


/*****************************************************************************/
//PPP Option
/*****************************************************************************/
typedef struct tag_ppp_option
{
   int         protocolLevel;
   int         remoteLocalFlag;
   int         optionName;
   const char far *optionValuePtr;
   int         optionLength;
} PPP_Option;

/*****************************************************************************/
//TCPIP statistics  structure (needed by function TCPIP_STATISTISTICS 0x74)
/*****************************************************************************/
typedef struct tag_cnt_packet{
   /*recv counter*/
   unsigned int far * cnt_all_packets;        //count all incoming ethernet packets
   unsigned int far * cnt_ip_packets;         //count incoming IP packets
   unsigned int far * cnt_arp_packets;        //count incoming ARP packets
   unsigned int far * cnt_tcp_packets;        //count incoming TCP packets
   unsigned int far * cnt_udp_packets;        //count incoming UDP packets
   unsigned int far * cnt_icmp_packets;       //count incoming ICMP packets

   /*send counter*/
   unsigned int far * cnt_all_sended_packets; //count all sended ethernet packets
   unsigned int far * cnt_ip_sended_packets;  //count all sended ip packets
   unsigned int far * cnt_arp_sended_packets; //count all sended arp packets
   unsigned int far * cnt_tcp_sended_packets; //count all sended tcp packets
   unsigned int far * cnt_udp_sended_packets; //count all sended udp packets
   unsigned int far * cnt_icmp_sended_packets;//count all sended icmp packets

   /*chksum error  counter on incoming packets*/
   unsigned int far * cnt_ip_chksum_errs;     //count all chksum errors on incoming ip packets
   unsigned int far * cnt_udp_chksum_errs;    //count all chksum errors on incoming udp packets
   unsigned int far * cnt_tcp_chksum_errs;    //count all chksum errors on incoming tcp packets
   unsigned int far * cnt_eth_errs;           //count all ethernet error, CRC, FAE and FIFO overrun
}Packet_Count;

/*****************************************************************************/
//Ping API
/*****************************************************************************/

typedef struct tag_ping_command
{
   int           sd;                //socket descriptor, filled by PING_OPEN
   char far *    remoteHostNamePtr; //remote ip
   int           pingInterval;      //seconds
   int           pingDataLength;    //max. 1024 Bytes
   unsigned long count;             //number of pings to send
   unsigned char pingstate;         //pin socket state, 1: open 0: closed

   //statistics, filled by ping command
   unsigned long transmitted;       //sended ping requests
   unsigned long received;          //received replies
   unsigned int  lastsenderr;       //last send error
   unsigned int  lastrcverr;        //last receive error
   unsigned long maxRtt;            //Max round trip time, rounded off to 100ms steps
   unsigned long minRtt;            //Minimum round trip time in milliseconds, (100 ms steps)
   unsigned long lastRtt;           //round trip time (100 ms steps) of the last ping request/reply
}Ping;

/*****************************************************************************/
//Routing
/*****************************************************************************/
typedef struct tag_route_entry
{
   unsigned long destIPAddress;    //The IP address to add the route for
   unsigned long destNetmask;      //The netmask for the route
   unsigned long gateway;          //IP address of the gateway of the route
   int hops;                       //Number of routers between this host and route
}Route_Entry;


typedef struct tagArpRouteCacheEntry
{
   unsigned int   ifIndex;       //interface index fpr this entry
   unsigned long  flags;         //type of entry
   unsigned long  arpIpAddress;  //IP address
   unsigned long  mask;
   long           arpTtl;        //TimeToLive in milliseconds
   long           hops;          //number of routers between this host and the route

   union
   {
      struct
      {
         //device IP address for Local routing entry
         unsigned long  DevIpAddress;
      }LocalNetRouteEntry;

      struct
      {
         //device Ethernet address for ARP entry
         unsigned char MacAddress[6];
         unsigned char filler[2];
      }ArpEntry;

      struct
      {
         unsigned long  GatewayIpAddress;   //indirect route
      }GatewayEntry;

   }ArpRouteGwayUnion;

}ArpRouteCacheEntry;

/*****************************************************************************/
//Interface information
/*****************************************************************************/
typedef struct tag_iface_device
{
   unsigned int  devIndex;       //Internal index number
   char          devName[14];    //Device name
   unsigned long devIPAddr;      //IP address for this interface
   unsigned long devNetmask;     //Netmask for the route
   unsigned long devDestIpAddr;  //Remote peer address for PPP
   unsigned char PhysAddr[6];    //Physical device address, max. 6 Bytes
   int           devType;        // type of the device driver:
                                 // 0: unknown,
                                 // 1: ethernet driver,
                                 // 2: PPP protocol
                                 // 4: SLIP protocol (not supported)
                                 // 5: Internal loopback
   int           devDHCP;        // Interface configured by DHCP? 1:0
   int           devFlag;
   int           devMTU;         //Max. Transfer Unit

   void far *    reserved;
}Iface_Entry;


#ifndef TCPIP_STACK_V2
//Contains all possible IPv4 configuration of an interface (IP multihoming)
typedef struct tag_iface_device_ext
{
     unsigned int  devIndex;       //Internal index number
     char          devName[14];    //Device name
     unsigned long devIPAddr[4];      //IP addresses for this interface
     unsigned long devNetmask[4];     //Netmasks for the route
     unsigned long devDestIpAddr[4];  //Remote peer addresses for PPP
     unsigned char PhysAddr[6];       //Physical device address, max. 6 Bytes

     int  devType;                  // type of the device driver:
                                    // 0: unknown,
                                    // 1: ethernet driver,
                                    // 2: use PPP protocol   server
                                    // 3: use PPP protocol client
                                    // 4: Internal loopback
     int  devDHCP[4]; // Interface configured by DHCP 1:0
     int  devFlag;
     int  devMTU;                   //Max. Transfer Unit
     void far *    IfaceHandle;    // handle type , to identify the interface internal
}Iface_Entry_Ext;
#else
typedef struct tag_iface_device_ext
{
     unsigned int  devIndex;       //Internal index number
     char          devName[14];    //Device name
     unsigned long devIPAddr[5];      //IP addresses for this interface
     unsigned long devNetmask[5];     //Netmasks for the route
     unsigned long devDestIpAddr[5];  //Remote peer addresses for PPP
     unsigned char PhysAddr[6];       //Physical device address, max. 6 Bytes

     int  devType;                  // type of the device driver:
                                    // 0: unknown,
                                    // 1: ethernet driver,
                                    // 2: use PPP protocol   server
                                    // 3: use PPP protocol client
                                    // 4: Internal loopback
     int  devDHCP[5]; // Interface configured by DHCP 1:0
     int  devFlag;
     int  devMTU;                   //Max. Transfer Unit
     void far *    IfaceHandle;    // handle type , to identify the interface internal
}Iface_Entry_Ext;
#endif
/*********************************************************************************/
/*
   SNMP MIB structures: Only available at BIOS version which contains SNMP MIB variables.
   Note: We don't have a SNMP agent inside of the BIOS but
   if an user is able to implement an own snmp agent at the IPC@Chip based at the
   TCPIP API, he needs access to TCPIP internal variables of these defined structures
*/
/********************************************************************************/
typedef struct tagIfMib     /*interface, only ethernet is supported*/
{
   long          ifIndex;               /* index of this interface  1 for ethernet, currently only ethernet*/
   char          ifDescr[32];           /* description of interface */
   long          ifType;                /* network device type  */
   long          ifMtu;                 /* maximum transfer unit */
   unsigned long ifSpeed;               /* bandwidth in bits/sec    */
   unsigned char ifPhysAddress[11];     /* interface's address */
   unsigned char PhysAddrLen;           /* length of physAddr: 6 */
   long          ifAdminStatus;         /* desired state of interface, not supported */
   long          ifOperStatus;          /* current operational status, not supported  */
   //counters
   unsigned long   devLastChange;       /* value of sysUpTime when current state entered */
   unsigned long   devInOctets;         /* number of octets received on interface */
   unsigned long   devInUcastPkts;      /* number of unicast packets delivered */
   unsigned long   devInMulticastPkts;  /* number of multicast packets delivered, not supported */
   unsigned long   devInBroadcastPkts;  /* broadcasts delivered */
   unsigned long   devInDiscards;       /* number of broadcasts */
   unsigned long   devInErrors;         /* number of packets containing errors */
   unsigned long   devInUnknownProtos;  /* number of packets with unknown protocol */
   unsigned long   devOutOctets;        /* number of octets transmitted */
   unsigned long   devOutUcastPkts;     /* number of unicast packets sent */
   unsigned long   devOutMulticastPkts; /* number of multicast packets sent */
   unsigned long   devOutBroadcastPkts; /* broadcasts sent */
   unsigned long   devOutDiscards;      /* number of packets discarded with no error */
   unsigned long   devOutErrors;        /* number of pkts discarded with an error */
   unsigned long   devOutQLen;          /* number of packets in output queue */
}IfMib;


typedef struct tagIpMib
{
   long            ipForwarding;        /* 1: enabled  */
   long            ipDefaultTTL;        /* default TTL for pkts originating here */
   unsigned long   ipInReceives;        /* IP packets received from interfaces */
   unsigned long   ipInHdrErrors;       /* Pkts discarded due to header errors */
   unsigned long   ipInAddrErrors;      /* Pkts discarded due to bad address */
   unsigned long   ipForwDatagrams;     /* Pkts forwarded through this entity */
   unsigned long   ipInUnknownProtos;   /* Local-addressed pkts w/unknown proto */
   unsigned long   ipInDiscards;        /* Error-free packets discarded */
   unsigned long   ipInDelivers;        /* Datagrams delivered to upper level */
   unsigned long   ipOutRequests;       /* IP datagrams originating locally */
   unsigned long   ipOutDiscards;       /* Error-free output IP pkts discarded */
   unsigned long   ipOutNoRoutes;       /* IP pkts discarded due to no route */
   long            ipReasmTimeout;      /* Seconds fragment is held awaiting reassembly */
   unsigned long   ipReasmReqds;        /* Fragments needing reassembly (here) */
   unsigned long   ipReasmOKs;          /* Number of fragments reassembled */
   unsigned long   ipReasmFails;        /* Number of failures in IP reassembly */
   unsigned long   ipFragOKs;           /* Number of datagrams fragmented here */
   unsigned long   ipFragFails;         /* Pkts unable to be fragmented here */
   unsigned long   ipFragCreates;       /* Number of IP fragments created here */
   unsigned long   ipRoutingDiscards;
} IpMib;


typedef struct tagIcmpMib
{
   unsigned long   icmpInMsgs;          /* Total of ICMP msgs received */
   unsigned long   icmpInErrors;        /* Total of ICMP msgs received with errors */
   unsigned long   icmpInDestUnreachs;
   unsigned long   icmpInTimeExcds;
   unsigned long   icmpInParmProbs;
   unsigned long   icmpInSrcQuenchs;
   unsigned long   icmpInRedirects;
   unsigned long   icmpInEchos;
   unsigned long   icmpInEchoReps;
   unsigned long   icmpInTimestamps;
   unsigned long   icmpInTimestampReps;
   unsigned long   icmpInAddrMasks;
   unsigned long   icmpInAddrMaskReps;
   unsigned long   icmpOutMsgs;
   unsigned long   icmpOutErrors;
   unsigned long   icmpOutDestUnreachs;
   unsigned long   icmpOutTimeExcds;
   unsigned long   icmpOutParmProbs;
   unsigned long   icmpOutSrcQuenchs;
   unsigned long   icmpOutRedirects;
   unsigned long   icmpOutEchos;
   unsigned long   icmpOutEchoReps;
   unsigned long   icmpOutTimestamps;
   unsigned long   icmpOutTimestampReps;
   unsigned long   icmpOutAddrMasks;
   unsigned long   icmpOutAddrMaskReps;
} IcmpMib;


typedef struct tagTcpMib
{
   long            tcpRtoAlgorithm;  /* retransmission timeout algorithm */
   long            tcpRtoMin;        /* minimum retransmission timeout (mS) */
   long            tcpRtoMax;        /* maximum retransmission timeout (mS) */
   long            tcpMaxConn;       /* maximum tcp connections possible */
   unsigned long   tcpActiveOpens;   /* number of SYN-SENT -> CLOSED transitions */
   unsigned long   tcpPassiveOpens;  /* number of SYN-RCVD -> LISTEN transitions */
   unsigned long   tcpAttemptFails;  /* (SYN-SENT,SYN-RCVD)->CLOSED or SYN-RCVD->LISTEN*/
   unsigned long   tcpEstabResets;   /* (ESTABLISHED,CLOSE-WAIT) -> CLOSED */
   unsigned long   tcpCurrEstab;     /* number in ESTABLISHED or CLOSE-WAIT state */
   unsigned long   tcpInSegs;        /* number of segments received */
   unsigned long   tcpOutSegs;       /* number of segments sent */
   unsigned long   tcpRetransSegs;   /* number of retransmitted segments */
   unsigned long   tcpInErrs;        /* number of received errors */
   unsigned long   tcpOutRsts;       /* number of transmitted resets */
} TcpMib;


typedef struct tagUdpMib
{
   unsigned long   udpInDatagrams;   /* UDP datagrams delivered to users */
   unsigned long   udpNoPorts;       /* UDP datagrams to port with no listener */
   unsigned long   udpInErrors;      /* UDP datagrams unable to be delivered */
   unsigned long   udpOutDatagrams;  /* UDP datagrams sent from this entity */
}UdpMib;

typedef struct tag_atEntry
{
   long            IfIndex;          /* interface on which this entry maps */
   unsigned char   PhysAddress[6];  /* physical address of destination */
   unsigned char   PhysAddressLen;   /* length of atPhysAddress */
   unsigned long   NetAddress;       /* IP address of physical address */
}atEntry;

typedef struct tag_UserDhcpEthEntry
{
   unsigned long   BootSIpAddress;      // BOOT Server (TFTP server), not supported
   unsigned long   Dns1ServerIpAddress; // Domain name server
   unsigned long   Dns2ServerIpAddress; // Second domain name server
   unsigned long   Yiaddr;              // Our (leased) IP address
   unsigned long   NetMask;             // Our subnet mask
   unsigned long   DefRouter;           // Default router
   unsigned long   DhcpServerId;        // DHCP selected server IP address
   unsigned long   internal1;           // Internal use only
   unsigned long   internal2;           // Internal use only
   unsigned long   DhcpLeaseTime;       // DHCP Address lease time in milliseconds
   unsigned long   internal3;           // internal use only
   unsigned long   internal4;           // internal use only
   unsigned char   DomainName[64];      // Domain name
   unsigned char   BootSname[64];       // TFTP server name, not used
   unsigned char   BootFileName[128];   // Boot file name (for TFTP download), not supported
   unsigned short  BootFileSize;        // Boot file size in 512 Bytes blocks (for TFTP download), not supported
   unsigned short  internal5;           // internal use only
}UserEthDhcp_Entry;

typedef void          far *  DevUserIfaceHandle;   /* handle type , to identify the interface internal*/
typedef void          far *  DevUserBuffer;        /* Device buffer handle type*/
typedef void          far *  DevUserLinkLayer;     /* handle type , to identiy link layer internal*/
typedef DevUserBuffer far *  DevUserBufferHandle;




/***********************************************************************************/
//Device driver function pointers
/***********************************************************************************/

#define DEV_ADD_ONLY         (0x80)         // Flag bit OR'ed into iface_type
#define DEV_ETHERNET            (1)
#define DEV_PPP_SERVER          (2)
#define DEV_PPP_CLIENT          (3)
#define DEV_PPPoE_CLIENT        (5)         // SC1x3/SC2x only
#define DEV_IP_TUNNEL           (6)         // SC1x3/SC2x only

//main structure for installing device driver and TCPIP interface
typedef struct tag_DevUserDriver
{
   int                    DevIndex;        // internal device index
   char far *             DevName;         // unique name max. 13 chars + 0
   unsigned long          IpAddr;          // IP address
   unsigned long          Netmask;         // Netmask

   DevUserIfaceHandle     IfaceHandle;     // handle to identify the interface internal
   DevUserLinkLayer       LinkLayerHandle; // handle to identify the link layer internal

   unsigned char          iface_type;      // type of the device driver:
        // 0: unknown user specific device,
        // 1 = DEV_ETHERNET: device is an Ethernet controller,
        // 2 = DEV_PPP_SERVER: use PPP protocol as a server
        // 3 = DEV_PPP_CLIENT: use PPP protocol as a client
        // 4: use SLIP protocol (currently not supported)
        // 5 = DEV_PPPoE_CLIENT: use PPP protocol over Ethernet as a client  (SC1x3/SC2x only)
        // 6 = DEV_IP_TUNNEL:  (SC1x3/SC2x only)


   unsigned char           use_dhcp;       // set to 1, if you want to use IP configuration by a DHCP server

   UserEthDhcp_Entry far * Dhcp_Data;      // Pointer to storage dhcp data, only, if use_dhcp==1 and iface_type==1(ethernet)

   void far *              PPPLinkNotify;  // Used only, if the iface_type == 2 or 3 (PPPserver or client)
                                           // Pointer to a user provided "link notify" callback function,
                                           // which is called by the PPP layer to inform the user
                                           // about the current PPP device status.
                                           // The function should look like this:
                                           // void huge PPPnotify(DevUserIfaceHandle ifaceHandle, int flags);
                                           // The function is called with the interface handle and a flag.
                                           // The flag is set to one or more of the following bits:
                                           // 0x0002:  PPP device is ready to accept data from the user.
                                           // 0x0008:  Close procedure started.
                                           // 0x0010:  PPP device has closed.
                                           // 0x0020:  LCP layer is up.
                                           // Set pointer to NULL, if the PPP layer shall
                                           // not execute a link notify function

   PPP_Option  far *      PPPoptions;      //Pointer to the first PPPoption of an user provide PPP option array,
                                           //These options will be set inside the Dev_Open_Interface call
                                           //The Dev_Open_Interface call returns 222, if trhe setting of the option failed
                                           //As an end marker, the element protocol_level of the last option must be 0.

   // Variant whose usage depends on the iface_type enumerator.
    union {
        // Peer address in network byte order, required for DEV_IP_TUNNEL 
        //  type device drivers.  This address specifies the remote
        //  end of the IP tunnel.
       unsigned long    peerIPv4 ;
   } u ;


   //set of driver functions, user has to write
   void  far *             DevOpen;        // Driver Open/initialize function, optional (pass a Null pointer, if not used)
   void  far *             DevClose;       // Driver Close function, optional (pass a Null pointer, if not used)
   void  far *             DevSend;        // Driver send function
   void  far *             DevRecv;        // Driver recv function
   void  far *             DevGetPhysAddr; // Ethernet driver only, returns MAC address, else pass a Null pointer
   void  far *             DevFreeRecv;    // Free own allocated buffer, optional (pass a Null pointer, if not used)
   void  far *             DevIoctl;       // currently not supported, pass a Null pointer

   int   far *             ErrorCode;      // contains errorcode, if install (API call 0xAC 0xA0) failed
   void  far *             Reserved4;      // reserved for future extensions
   void  far *             Reserved5;
   void  far *             Reserved6;
}DevUserDriver;


typedef struct tag_DevIpv4IfaceCfg
{
  DevUserIfaceHandle     IfaceHandle;     // handle to identify the interface internal
  unsigned long          IpAddr;          //IP address
  unsigned long          Netmask;         //Netmask
  int                    flags;           //Device flags
  int                    reserved;        //currently not used
  unsigned char          multiHomeIndex;  //The index for this IP address for multihoming
}DevIpv4IfaceCfg;



typedef struct tag_DevIpv6IfaceCfg
{
  DevUserIfaceHandle                   IfaceHandle;  // handle to identify the interface internal
  const struct sockaddr_storage far *  IpAddrPtr;        //IP address
  int                              prefixLen;     // Prefix Length
  int                              reserved;
  int                              ipv6flags;
  void far *                       reservedPtr;      //reserved, currently not used
  unsigned char                    multiHomeIndex;  //The index for this IP address for multihoming
}DevIpv6IfaceCfg;



//Reserved for Beck device driver ioctl extensions
typedef struct tagDevIoctlSubOption
{
    int code;
    void far * optionPtr;
    void far * optionLength;
}DevIoctlSubOption;

/*****************************************************************************/
//IPv6 device configuration
/*****************************************************************************/
typedef struct tag_user_iface_ipv6_entry{
    void  far *     devIfaceHandle;       // Device handle pointer (internal used)
    int             devIndex;             // Internal used index number
    int             devType;              // Type of the device driver:
                                          // 0: unknown,
                                          // 1: Ethernet driver,
                                          // 2: PPP protocol
                                          // 4: SLIP protocol (not supported)
                                          // 5: Internal loopback
    char            devName[14];          // Device name, terminated by zero
    unsigned int    devFlags;             // Device status flag
                                          // Bit1 == 1  Device opened
                                          // Bit2 == 1  Device IPv6 config in progress
                                          // Bit3 == 1  Device open completed
    unsigned int    devIPv6Flags;         // IPv6 status flags
                                          // Bit1 == 1  Link-layer address configured
                                          // Bit2 == 1  Link-local address configured (or is pending)
                                          // Bit3 == 1  Site-local address configured (or is pending)
                                          // Bit4 == 1  Global scope IPv6 native address
                                          // Bit5 == 1  Global scope IPv4-compatible IPv6 address configured
                                          // Bit6 == 1  Global scope 6-to-4 IPv6 address
                                          // Bit7 == 1  IPv6 connectivity establish on PPP interface
    unsigned int    devIPv6Mtu;           // The MTU of the IPv6 link
    struct in6_addr devIPv6PPPPeerIpAddr; // Remote peer address for PPP
    struct in6_addr devIPv6AddrArray[10]; // Array of all configured IPv6 addresses on this interface
    unsigned char   devIPv6PrefixLen[10]; // Array of all configured Prefixlength of all IPv6 addresses
    unsigned char   devIPv6AddrFlagsArray[10]; // Array of configuration flags
    unsigned char   devPhysAddr[6];       // Physical address of the interface
    void far       * devIPv6ExtensionPtr; //for future use
}IfaceIPv6_Entry;






/*****************************************************************************/
//PKI, SSL structures
/*****************************************************************************/
typedef struct tag_pki_cert_add_entry
{
  void far *    fileNamePtr;
  int           fileFormat;
  int           certType;
  void far *    idPtr;
  int           idLength;
  void far *    caIdPtr;
} PKI_CERT_ADD_Entry;
typedef PKI_CERT_ADD_Entry far * PKI_CERT_ADD_EntryPtr;

typedef struct tag_pki_ownkeypair_add_entry
{
  void far *    fileNamePtr;
  int           fileFormat;
  int           keyType;
} PKI_OWNKEYPAIR_ADD_Entry;
typedef PKI_OWNKEYPAIR_ADD_Entry far * PKI_OWNKEYPAIR_ADD_EntryPtr;

typedef struct tag_ssl_session_new_entry
{
  char far *    certIdentity;
  unsigned int  maxCaches;
  int           version;
} SSL_SESSION_NEW_Entry;
typedef SSL_SESSION_NEW_Entry far * SSL_SESSION_NEW_EntryPtr;




/*****************************************************************************/
//BSD Socket defines
/*****************************************************************************/

#define AF_INET         2
#define PF_INET         AF_INET

#define AF_INET6        28
#define PF_INET6        AF_INET6

#define SOCK_STREAM     1       /* stream socket  , TCP */
#define SOCK_DGRAM      2       /* datagram socket, UDP */

//ulps
#define IP_ICMP         (unsigned char)1
#define IP_IGMP         (unsigned char)2
#define IP_TCP          (unsigned char)6
#define IP_UDP          (unsigned char)17

    // For SC2x3 C-Lib compatibility
#define IPPROTO_TCP     6
#define IPPROTO_UDP     17

#define EWOULDBLOCK     235        /* Operation would block.
                                    *  No data is available to be read. 
                                    */
#define ECONNREFUSED    261        /*!< Connection refused */

/*****************************************************************************/
#define MSG_BLOCKING    0x0000  /* this message should be blocking */
#define MSG_TIMEOUT     0x0001  /* wake up from recv after we have timed out*/
#define MSG_PEEK        0x0002  /* “Peek” at the data present on the
                                   socket; the data is returned, but not
                                   consumed, so that a subsequent
                                   receive operation will see the same data*/
#define MSG_DONTWAIT    0x0080  /* this message should be nonblocking */

/*****************************************************************************/
//Socket options
/*****************************************************************************/
//protocol levels
#define IP_PROTOIP_LEVEL        0       /* ip level     */
#define IP_PROTOTCP_LEVEL       6       /* tcp level    */
#define IP_PROTOIP              0       /* ip level BSD style  */
#define IP_PROTOTCP             6       /* tcp level BSD style */

#ifndef TCPIP_STACK_V2
#define SOCKET_LEVEL            0x7fff  /* socket level */
#define SOL_SOCKET              0x7fff  /* socket level BSD style*/
#else
#define SOCKET_LEVEL            0xffff  /* socket level */
#define SOL_SOCKET              0xffff  /* socket level BSD style*/
#endif

//ip level options
#ifndef TCPIP_STACK_V2
#define IPO_TTL                 0x0001  /* IP Time to live, default 64 seconds*/
#define IPO_TOS                 0x0002  /* IP type of service , default 0*/
#else
#define IPO_TOS                 0x0003  /* IP type of service , default 0*/
#define IPO_TTL                 0x0004  /* IP Time to live, default 64 seconds*/
#endif

//tcp level options
#define TCP_NODELAY             0x0001  /* Disable/enable the nagle algorithm*/
#define TCP_NOPUSH              0x0004  /* Delay sending until a full segment is buffered*/
#define TCP_TS                  0x0100  /* Disable/enable TCP time stamp option*/
#define TCP_SLOW_START          0x0200  /* Disable/enable TCP slow start algorithm*/

#define TCP_KEEPALIVE           0x4001  /* Set idle time,before sending keepalive probes, default 7200 seconds*/
#define TCP_DELAY_ACK           0x4002  /* Set the TCP delay ack time in millseconds*/
#define TCP_KEEPALIVE_INTV      0x4004  /* Set keep alive interval probes (default 75 seconds) */
#define TCP_KEEPALIVE_CNT       0x4005  /* Set max. number of keep alive probes, before tcp gives up, default 12*/
#define TCP_FINWT2TIME          0x4006  /* Set the max. amount of time TCP will wait for the remote side to close, after it initiate a close*/
#define TCP_2MSLTIME            0x4007  /* Set the max. amount of time TCP will wait in the TIME WAIT state, once it has initiated a close*/
#define TCP_RTO_DEF             0x4008  /* Set the default retransmission timeout value in milliseconds, default is 3000 ms */
#define TCP_RTO_MIN             0x4009  /* Set the minimum retransmission timeout value in milliseconds, default is 100 ms */
#define TCP_RTO_MAX             0x400A  /* Set the maximum retransmission timeout value in milliseconds, default is 64000 ms */
#define TCP_MAXRT               0x0010  /* Set the TCP/IP Timeout, OptionLength: 2 Bytes (INT) */
#define TCP_MAXREXMIT           0x4003  /* Set the Maximal TCP/IP Send retries,OptionLength: 2 Bytes (INT) */

#define TCP_SSL_CLIENT          0x5000  /* Set this option to enable SSL client negotiation */
#define TCP_SSL_SERVER          0x5001  /* Set this option to enable SSL server negotiation */
#define TCP_SSLSESSION          0x5002  /* Set the SSL session number for this socket */
#define TCP_SSL_SEND_MIN_SIZE   0x5004  /* Set the SSL send minimum size */
#define TCP_SSL_SEND_MAX_SIZE   0x5005  /* Set the SSL record maximum size */

//socket level options
#define SO_ACCEPTCONN           0x0002  /* Socket has had listen() */
#define SO_REUSEADDR            0x0004  /* allow local address reuse ,default 0 disable*/
#define SO_KEEPALIVE            0x0008  /* keep connections alive, default  0 disable*/
#define SO_BROADCAST            0x0020  /* Permit sending of broadcast msgs */
#define SO_USELOOPBACK          0x0040  /* Bypass hardware when possible */
#define SO_LINGER               0x0080  /* Linger on close if data present */
#define SO_REUSEPORT            0x0200  /* Allow local address & port reuse */
#define SO_TIMESTAMP            0x0400  /* Timestamp received dgram traffic */
#define SO_IPHDRINCL            0x0800  /* IP Header included on the socket */
#define SO_SNDBUF               0x1001  /* send buffer size, default TCP 4096, UDP 2048 bytes */
#define SO_RCVBUF               0x1002  /* receive buffer size,default TCP 4096, UDP 2048 bytes */




/*****************************************************************************/
////socket call back function and event flags, TCP sockets only!!
/*****************************************************************************/
#define CB_CONNECT_COMPLT       0x0001  /* connection complete*/
#define CB_ACCEPT               0x0002  /* remote has establ. a connection to our listening server*/
#define CB_RECV                 0x0004  /* incoming data arrived*/
#define CB_SEND_COMPLT          0x0010  /* sending of data has been acked by the peer*/
#define CB_REMOTE_CLOSE         0x0020  /* peer has shutdown the connection*/
#define CB_SOCKET_ERROR         0x0040  /* an error occured on the connection*/
#define CB_RESET                0x0080  /* peer has sent a rest on the connection*/
#define CB_CLOSE_COMPLT         0x0100  /* close has been completed*/

/*****************************************************************************/
////ArpRouteCache Entry flags
/*****************************************************************************/
#define INDIRECT   0x00000002UL  // Indirect route  (struct GatewayEntry)
#define LINKLAYER  0x00000008UL  // Valid Arp entry (struct ArpEntry)
#define LOCALROUTE 0x00000010UL  // Local route     (struct LocalNetRouteEntry)
#define STATIC     0x00000020UL  // Static route
#define CLONED_ARP 0x00000C00UL  // Cloned arp entry
#define ROUTE_UP   0x00010000UL  // Route is up
#define HOST_IP    0x00020000UL  // arpIpAddress entry is a host address, 0: network address

/*****************************************************************************/
//PPP options
/*****************************************************************************/
 // PPP Protocol levels
 #define PPP_LCP_PROTOCOL      0x21c0  // LCP,  Link control protocol
 #define PPP_IPCP_PROTOCOL     0x2180  // IPCP, Internet protocol control protocol
 #define PPP_PAP_PROTOCOL      0x23c0  // PAP authentication
 #define PPP_CHAP_PROTOCOL     0x23c2  // CHAP authentication
 #define PPP_PROTOCOL          0x0000  // PPP common

 // For .remoteLocalFlag
 #define PPP_OPTION_WANT       0     // What we want to use for our side
 #define PPP_OPTION_ALLOW      1     // What we will allow the remote side to use

 // Protocol options for .optionName field
 // LCP protocol options
 #define PPP_LCP_MAX_RECV_UNIT     1  // Maximum receive unit
 #define PPP_LCP_ACCM              2  // Async Ctrl Char Map
 #define PPP_LCP_AUTH_PROTOCOL     3  // Authentication, def. 0, else PPP_PAP or PPP_CHAP
 #define PPP_LCP_MAGIC_NUMBER      5  // Specify a magic number
 #define PPP_LCP_PROTOCOL_COMP     7  // Turn On/Off protocol field compression
 #define PPP_LCP_ADDRCONTROL_COMP  8  // Turn ON/OFF address/control field compression
 #define PPP_LCP_TERM_RETRY        9  // Terminate retries,
 #define PPP_LCP_CONFIG_RETRY      10 // Config retries,
 #define PPP_LCP_TIMEOUT           11 // Retransmission timeout in seconds
 #define PPP_LCP_MAX_FAILURES      12 // LCP maximum failure

 // IPCP protocol options
 #define PPP_IPCP_COMP_PROTOCOL    2  // VJ-TCP/IP header compression
 #define PPP_IPCP_IP_ADDRESS       3  // IP Address the requesting system wishes to use
 #define PPP_IPCP_VJ_SLOTS         4  // Number of VJ slots
 #define PPP_IPCP_RETRY            5  // IPCP Timeout, retry options
 #define PPP_IPCP_TIMEOUT          6  // IPCP timeout seconds
 #define PPP_IPCP_MAX_FAILURES     7  // LCP maximum failures
 #define PPP_IPCP_DNS_PRI         29  // Specify DNS prim. server IP
 #define PPP_IPCP_DNS_SEC         31  // Specify DNS sec.  server IP

  //PAP protocol options
 #define PPP_PAP_USERNAME         1  // The local username to authenticate with
 #define PPP_PAP_PASSWORD         2  // The local password to authenticate with
 #define PPP_PAP_RETRY            3  // PAP timeout, retry options
 #define PPP_PAP_TIMEOUT          4  // PAP timeout in seconds

 //CHAP protocol options
 #define PPP_CHAP_USERNAME        1   // The local username to authenticate with
 #define PPP_CHAP_SECRET          2   // The local secret to authenticate with
 #define PPP_CHAP_RETRY           3   // CHAP timeout, retry options
 #define PPP_CHAP_TIMEOUT         4   // CHAP timeout


 //PPP options
 #define PPP_SEND_BUFFER_SIZE      1  // Data buffered by PPP link layer, before the device driver send function
                                      // is called, length 2, def. 1 (Byte)
 #define PPP_OVER_ETHERNET         3  // PPPoE mode
 //Authentication constants
 #define PPP_PAP    0x23c0            // PAP authentication
 #define PPP_CHAP   0x23c2            // CHAP authentication

/*****************************************************************************/
//Device driver functions
/*****************************************************************************/
#ifdef TCPIP_STACK_V2
  #define DEV_IP_DHCP        0x0080  //Configure IP address via DHCP protocol
  #define DEV_IP_FORW_ENB    0x0400  //IP forwarding enabled
  #define DEV_IP_FORW_DB_ENB 0x0800  //IP forwarding of directed broadcast enabled
  #define DEV_IP_FORW_MCAST_ENB    0x2000 //forwarding multicast s

  #define DEV_IOCTL_IPCFG_NOTIFY     0x0001 //new or modified IPv4 address
  #define DEV_IOCTL_IPV6CFG_NOTIFY   0x0002 //new or modified IPv6 address
  //Reserved for Beck device driver extensions
  #define DEV_IOCTL_EXTENDED      0x8000
  #define DEV_SUBIOCTL_KILL       1
#else
  #define DEV_IP_FORW_ENB    0x0080  //IP forwarding enabled
  #define DEV_IP_FORW_DB_ENB 0x0100  //IP forwarding of directed broadcast enabled
  #define DEV_IP_DHCP        0x0800  //Configure IP address via DHCP protocol
#endif

/*****************************************************************************/
//SSL defines
/*****************************************************************************/
#define TLS_RSA_NULL_MD5          0x0001
#define TLS_RSA_NULL_SHA          0x0002
#define TLS_RSA_EXPORT_RC4_40_MD5 0x0003
#define TLS_RSA_RC4_128_MD5       0x0004
#define TLS_RSA_RC4_128_SHA       0x0005
#define TLS_RSA_3DES_EDE_CBC_SHA  0x000A
#define TLS_RSA_AES_128_CBC_SHA   0x002F
#define TLS_RSA_AES_256_CBC_SHA   0x0035
#define TLS_RSA_EPT1K_RC4_56_SHA  0x0064

/*****************************************************************************/
//Errorcodes
/*****************************************************************************/
#define API_NOT_SUPPORTED       -2
#define API_ERROR               -1
#define API_ENOERROR             0

//PPP server states
#define PPPS_UNDEFINED          -1    /* Undefined, should not happen*/
#define PPPS_NOT_STARTED         0    /* PPP server was not started*/
#define PPPS_DISABLED            1    /* Server started, but disabled */
#define PPPS_ENABLED             2    /* Server enabled, not connected*/
#define PPPS_LNKUP               3    /* Connection established*/
#define PPPS_MODEMCLOSING        4    /* Server hangs up modem*/
#define PPPS_MODEMINIT           5    /* Server tries init modem*/

//PPP client states
#define PPP_NOTAVAIL            -1    /* Client is not running*/
#define PPP_LNKDOWN              0    /* Link is down*/
#define PPP_LNKWILLOPEN          1    /* open link in progress*/
#define PPP_LNKUP                2    /* Link is established*/
#define PPP_HALTED               3    /* Halted by PPP_Client_Pause() call*/


//PPP client errorcodes
#define PPP_INV_COMPORT         -1    /* invalid comport specified,
                                         this errorCode also occurs, if
                                         the pppclient is interrupted while dialing
                                         (e.g. user break with setting the flag modem_break
                                          at the struct pppclient_init
                                          or another modem error)
                                      */
#define PPP_INUSE               -2    /* ppp client already in use     */
#define PPP_INV_USER            -3    /* invalid user or password      */
#define PPP_OPEN_FAIL           -4    /* connection failed             */
#define PPP_INV_DEV             -5    /* pppclient interface not found */
#define PPP_IPCFG_FAIL          -6    /* got an invalid IP from the peer */
#define PPP_CONNECT_FAIL        -7    /* connection to the peer failed  */
#define PPP_CLOSETIMEOUT        -8    /* Timeout at closing connection   */

    // Possible error flags for PKI certificate add function.
    // (Error codes can be bit-wise combinations of these flags.)
#define PKI_CERT_BADCERT        0x01  // Critical error
#define PKI_CERT_REVOKED        0x02  // Revoked certiticate
#define PKI_CERT_EXPIRED        0x04  // Expired certificate
#define PKI_CERT_UNMATCHED      0x08  // Identity not matched
#define PKI_CERT_UNKNOWNCA      0x10  // CA is unknown
#define PKI_CERT_NOTVERIFIED    0x20  // The mentioned CA fails to verify the certificate

/*******************************************************************************
 General TCPIP stack options to use at TCPIP_SetOption()
*******************************************************************************/
/* The maximum number of ARP retries before going into the ARP quiet %time state.
   Default: 6, Minimum: 1 */
#define TCPIP_OPTION_ARP_MAX_RETRY      4
/* The amount of time in seconds between ARP retries. Default: 1, Minimum: 1*/
#define TCPIP_OPTION_ARP_TIMEOUT_TIME   5
/*! The length of the ARP quiet %time state in seconds. Default: 20, Minimum: 1*/
#define TCPIP_OPTION_ARP_QUIET_TIME     6
/* The length of %time that an ARP entry should be kept in the ARP cache in seconds.
   To disable ARP aging, set to TCPIP_RTE_INF. Default: 600, Minimum: 1*/
#define TCPIP_OPTION_ARP_TTL            7
/* A boolean(0 or 1) to enable IP forwarding. Default: 1 */
#define TCPIP_IP_FORWARDING            13
/* A boolean (0 or 1) to enable directed broadcast forwarding. Default: 1*/
#define TCPIP_IP_DBCAST_FORWARD        14
/* A boolean (0 or 1) to enable IP fragmentation. Default: 1*/
#define TCPIP_OPTION_IP_FRAGMENT       15
/* The initial time-to-live in seconds for IP datagrams. Default: 64 , Range: 0-255*/
#define TCPIP_OPTION_IP_TTL            16
/* The default Type-Of-Service for IP datagrams. Default: 0, Valid values: 0 - 0xFF*/
#define TCPIP_OPTION_IP_TOS            17
/* Fragment re-assembly timeout value in seconds. Default: 64, Range: 1-128 */
#define TCPIP_OPTION_IP_FRAG_TTL       18
/* A boolean (0 or 1) to enable/disable UDP checksums on outgoing packets.
   Default: 1*/
#define TCPIP_OPTION_UDP_CHECKSUM      20
/* Maximum number of ARP entries (32 - 512) in the ARP cache. Default: 64*/
#define TCPIP_OPTION_ARP_MAX_ENTRIES   21
/*  Boolean (0 or 1) to indicate whether the ARP logic should store all ARP
   mappings broadcast on the local network, even if we were not waiting for a reply,
   or if the request was not for us. Default: 0 */
#define TCPIP_OPTION_ARP_SMART         25
/* Infinite time to live for an ARP entry(TCPIP_OPTION_ARP_TTL)*/
#define TCPIP_RTE_INF 0x7FFFFFFF



//************************************************************************************
//BSD defines, macros
//************************************************************************************
#define INET6_ADDRSTRLEN       46  //max length of an IPv6 address int text format
#define INET_ADDRSTRLEN        16  //max length of an IPv4 string

// Compare 2 IPv6 addresses
// Parameter: const struct in6_addr *Addr1
//            const struct in6_addr *Addr1
#define IN6_ARE_ADDR_EQUAL(Addr1, Addr2) \
    (   ((Addr1)->ip6Addr.ip6U32[0] == (Addr2)->ip6Addr.ip6U32[0]) \
     && ((Addr1)->ip6Addr.ip6U32[1] == (Addr2)->ip6Addr.ip6U32[1]) \
     && ((Addr1)->ip6Addr.ip6U32[2] == (Addr2)->ip6Addr.ip6U32[2]) \
     && ((Addr1)->ip6Addr.ip6U32[3] == (Addr2)->ip6Addr.ip6U32[3]))

//Test if address is local loopback
//Parameter: const struct in6_addr *Addr
#define IN6_IS_ADDR_LOOPBACK(Addr) \
    (   ((Addr)->ip6Addr.ip6U32[0] == (0UL)) \
     && ((Addr)->ip6Addr.ip6U32[1] == (0UL)) \
     && ((Addr)->ip6Addr.ip6U32[2] == (0UL)) \
     && ((Addr)->ip6Addr.ip6U32[3] == (0x01000000UL)))


//Check IPv6 address to see if it is the unspecified address (i.e. all 0's)
//Parameter: const struct in6_addr *Addr
#define IN6_IS_ADDR_UNSPECIFIED(Addr) \
    (   ((Addr)->ip6Addr.ip6U32[0] == (0UL)) \
     && ((Addr)->ip6Addr.ip6U32[1] == (0UL)) \
     && ((Addr)->ip6Addr.ip6U32[2] == (0UL)) \
     && ((Addr)->ip6Addr.ip6U32[3] == (0UL)))


//Test, if IPv6 address is a multicast address
//Parameter: const struct in6_addr *Addr
#define IN6_IS_ADDR_MULTICAST(Addr) \
    ((Addr)->ip6Addr.ip6U8[0] == (unsigned char) 0xff)



//Test IPv6 address, if it is a link-local scope
//Parameter: const struct in6_addr *Addr
#define IN6_IS_ADDR_LINKLOCAL(Addr) \
        (((Addr)->ip6Addr.ip6U8[0] == (unsigned char) 0xfe) \
     && (((Addr)->ip6Addr.ip6U8[1] &  (unsigned char) 0xc0) == (unsigned char) 0x80))

//Test IPv6 address to see if it is a site-local scope  unicast address.
//Parameter: const struct in6_addr *Addr
#define IN6_IS_ADDR_SITELOCAL(Addr) \
        (((Addr)->ip6Addr.ip6U8[0] == (unsigned char) 0xfe) \
     && (((Addr)->ip6Addr.ip6U8[1] &  (unsigned char) 0xc0) == (unsigned char) 0xc0))

//Test IPv6 address,if it represents an IPv4 address (i.e. IPv4-mapped IPv6 address)
//Parameter: const struct in6_addr *Addr
#define IN6_IS_ADDR_V4MAPPED(Addr) \
        ((((Addr)->ip6Addr.ip6U32[0]) == (0UL)) && \
         (((Addr)->ip6Addr.ip6U32[1]) == (0UL)) && \
         (((Addr)->ip6Addr.ip6U32[2]) == (0xFFFF0000UL)))


//Test IPv6 address, if it is an IPv4-compatible IPv6 address.
//Parameter: const struct in6_addr *Addr
#define IN6_IS_ADDR_V4COMPAT(Addr) \
        ((((Addr)->ip6Addr.ip6U32[0]) == (0UL)) && \
         (((Addr)->ip6Addr.ip6U32[1]) == (0UL)) && \
         (((Addr)->ip6Addr.ip6U32[2]) == (0UL)) && \
         (((Addr)->ip6Addr.ip6U32[3]) != (0UL)) && \
         (((Addr)->ip6Addr.ip6U32[3]) != (0x01000000UL)))

//Copy one IPv6 address to another
//Parameter: const struct in6_addr *AddrSrc
//Parameter: const struct in6_addr *AddrDest

#define IPV6_addr_copy(AddrSrc, AddrDst) \
{ \
    (AddrDst)->ip6Addr.ip6U32[0] = (AddrSrc)->ip6Addr.ip6U32[0]; \
    (AddrDst)->ip6Addr.ip6U32[1] = (AddrSrc)->ip6Addr.ip6U32[1]; \
    (AddrDst)->ip6Addr.ip6U32[2] = (AddrSrc)->ip6Addr.ip6U32[2]; \
    (AddrDst)->ip6Addr.ip6U32[3] = (AddrSrc)->ip6Addr.ip6U32[3]; \
}

//BSD address constants used for IPv4, in host byte order, must be used with htonl()
#define INADDR_ANY              (0x00000000UL)
#define INADDR_LOOPBACK         (0x7F000001UL)


/*****************************************************************************/
#endif _TCPIP_API_H__
/*****************************************************************************/
//end tcpipapi.h
/***************************************************************************/

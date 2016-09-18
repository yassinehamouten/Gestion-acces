/****************************************************************************
* (C) 1999-2010 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : TCPIP_Socket.h
* Function       : prototypes, constants for TCP/IP socket functions
* ---------------------------------------------------------------------------

$Header: $

****************************************************************************/

#ifndef __TCPIP_SOCKET_H__
#define __TCPIP_SOCKET_H__

/*************************************************************************/
//prototypes
/*************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

int _cdecl far accept_bsd( int sd, 
                           struct sockaddr far * addressPtr, 
                           int far * addressLengthPtr);

int _cdecl far bind_bsd( int sd, 
                         const struct sockaddr far * addressPtr, 
                         int addressLength);

int _cdecl far connect_bsd( int sd, 
                            const struct sockaddr far * addressPtr, 
                            int addressLength);

int _cdecl far close_bsd(int sd);
int _cdecl far getsockopt_bsd( int sd, 
                               int protocol_level,
                               int optionName,
                               char far * optionValue,
                               int far * optionLengthPtr);

unsigned long _cdecl far inet_addr_bsd(const char * IPAddressStringPtr) ;

int _cdecl far listen_bsd(int sd, int backlog);

int _cdecl far recv_bsd( int sd,
                         char far * bufptr, 
                         int buflen, 
                         int flags, 
                         unsigned long timeout) ;
int _cdecl far recvfrom_bsd( int sd,
                             char far * bufptr, 
                             int buflen, 
                             int flags, 
                             struct sockaddr far * fromPtr, 
                             int far * fromLengthPtr,
                             unsigned long timeout) ;

int _cdecl far send_bsd( int sd, 
                         const char far * bufptr, 
                         int buflen,
                         int flags);
int _cdecl far sendto_bsd( int sd,
                           const char far * bufptr, 
                           int buflen, 
                           int flags, 
                           const struct sockaddr far * toPtr, 
                           int toLength);
int _cdecl far setsockopt_bsd( int sd, 
                               int protocol_level,
                               int optionName,
                               const char far * optionValue,
                               int optionLength);

int _cdecl far shutdown_bsd(int sd, int  dir);


#ifdef BSD44_SOCKET_API_STYLE  
//*************************************************************************
#define accept           accept_bsd
#define bind             bind_bsd
#define connect          connect_bsd
#define closesocket      close_bsd
#define getsockopt       getsockopt_bsd
#define inet_addr        inet_addr_bsd
#define listen           listen_bsd
#define recv(sd,bufptr,bufLen,flags)  recv_bsd(sd,bufptr,bufLen,flags,0)
#define recvfrom(sd,bufptr,bufLen,flags,fromPtr,fromlengthPtr) \
    recvfrom_bsd(sd,bufptr,bufLen,flags,fromPtr,fromlengthPtr,0)
#define send             send_bsd
#define sendto           sendto_bsd
#define shutdown         shutdown_bsd
#define setsockopt       setsockopt_bsd


//*************************************************************************
#else   // BSD44_SOCKET_API_STYLE

#ifdef TCPIP_STACK_V2
    // Select an alternate C-library functions for SC1x3/SC2x targets
#ifdef TCPIP_DYN_LINK_SOCK
    // Make connections to the faster dynamic links for data transfer API.
#define recv            recv_Dyn
#define recvfrom        recvfrom_Dyn
#define send            send_Dyn
#define sendto          sendto_Dyn

#else  // Not TCPIP_DYN_LINK_SOCK
#define recvfrom    recvfrom_ipstackV2  
#define sendto      sendto_ipstackV2

#endif  // TCPIP_DYN_LINK_SOCK

#endif  // TCPIP_STACK_V2

int  _cdecl accept(int sd, struct sockaddr far * addressPtr, int *error);
int  _cdecl bind (int sd, const struct sockaddr far * addressPtr, int *error);
int  _cdecl connect (int sd, 
                     const struct sockaddr far * addressPtr, 
                     int *error);
int  _cdecl closesocket (int sd, int *error) ;
int  _cdecl getsockopt (int sd, 
                        const GetSocketOption far *sockoptptr, 
                        int *error);

int  _cdecl inet_addr(const char far * IPAddressStringPtr, unsigned long far * IPAddress);

int  _cdecl listen(int sd,int backlog, int *error) ;

int  _cdecl recv(int sd, char far * bufptr, int bufLen, int flags, unsigned long timeout,
                 int *error);


int  _cdecl recvfrom(int sd, 
                     char far * bufptr, 
                     int bufLen, 
                     int flags,
                     unsigned long timeout,
                     struct sockaddr far * fromPtr, 
                     int *error);

int  _cdecl send( int sd, 
                  const char far * bufptr, 
                  int bufLen, 
                  int flags, 
                  int *error);

int  _cdecl sendto (int sd, 
                    const char far * bufptr, 
                    int bufLen, 
                    int flags,
                    const struct sockaddr far * toPtr, 
                    int *error);

int  _cdecl setsockopt (int sd, 
                        const SetSocketOption far *sockoptptr, 
                        int *error) ;

int _cdecl shutdown (int sd, unsigned char dir, int * error);

//*************************************************************************
#endif  // BSD44_SOCKET_API_STYLE



int  _cdecl GetWaitingBytes(int sd, int *error);

// Offer dynamic linked version explicitly.
int _cdecl far get_socketerror_Dyn(int sd);

#ifdef TCPIP_STACK_V2
#ifdef TCPIP_DYN_LINK_SOCK

    // Make connections to the faster dynamic link versions of API.
#define get_socketerror     get_socketerror_Dyn
#define recvfromto          recvfromto_Dyn

#else  // not TCPIP_DYN_LINK_SOCK

int _cdecl get_socketerror(int sd);

#endif // TCPIP_DYN_LINK_SOCK

int  _cdecl recvfromto(int sd,
                       char far * bufptr,
                       int bufLen,
                       int flags,
                       unsigned long timeout,
                       struct sockaddr far * fromPtr,
                       struct sockaddr far * toPtr,
                       int *error);

int  _cdecl recvfromto_iface(int sd,
                       char far * bufptr,
                       int bufLen,
                       int flags,
                       unsigned long timeout,
                       struct sockaddr far * fromPtr,
                       struct sockaddr far * toPtr,
                       unsigned char far *fromPhyAddrPtr,
                       int far *fromPhyAddrLenPtr,
                       DevUserIfaceHandle * DevHandlePtr,
                       int *error);

#endif // TCPIP_STACK_V2

int  _cdecl ResetConnection (int sd, int *error) ;

#ifdef TCPIP_STACK_V2
#define tcp_connect   tcp_connect_ipstackV2   // Select an alternate C-library function
#endif

int  _cdecl tcp_connect(const char far *DestIPStr, unsigned int ClientPort,
                        unsigned int HostPort, int *error);



#ifdef TCPIP_STACK_V2
#ifdef TCPIP_DYN_LINK_SOCK

    // Make connections to the faster dynamic link version of API.
#define sendto_iface        sendto_iface_Dyn
#else  // not TCPIP_DYN_LINK_SOCK

#define sendto_iface   sendto_iface_ipstackV2    // Select an alternate C-library function

#endif // TCPIP_DYN_LINK_SOCK
#endif // TCPIP_STACK_V2

int  _cdecl sendto_iface (int sd, 
                          const char far * bufptr, 
                          int bufLen, 
                          int flags,
                          const struct sockaddr far * toPtr,
                          DevUserIfaceHandle DevHandlePtr,
                          int *error);


int  _cdecl setlinger(int sd, int seconds, int *error);

int  _cdecl setreuse (int sd, int *error);

int  _cdecl Set_IP_Type_Of_Service (int sd, unsigned char tos, int *error) ;

int  _cdecl opensocket(unsigned char type, int *error);

#ifdef TCPIP_STACK_V2
int  _cdecl opensocket_ext(int family, unsigned char type,  int *error);
    // BSD style alternative to opensocket_ext
int _cdecl far socket (int family, int type, int protocol) ;
#endif

int  _cdecl Set_Blocking_Mode(int sd, unsigned char blocking_mode, int *error);

int  _cdecl RegisterCallbackFunction(int sd, void far * funcptr, int eventflagmask, int *error) ;

int  _cdecl GetRegisterCallbackFunction(int sd, void far * funcptr, int eventflagmask ,int *error);


unsigned char _cdecl Get_TCP_Socket_State(unsigned int localPort,
                                          unsigned long far * remoteIP,
                                          unsigned int * remotePort);

unsigned char _cdecl Get_TCP_Socket_State_IP_All(unsigned int localPort,
                                                 struct in6_addr far * remoteIP,
                                                 unsigned int * remotePort);

int _cdecl FindAllOpenSockets(SocketInfo far * SockInfoPtr, int max);
int _cdecl FindAllOpenSockets_IP_All(SocketInfoIPv4v6 far * SockInfoPtr, int max);


int _cdecl select (int          nfds, 
                   fd_set far * readfds, 
                   fd_set far * writefds, 
                   fd_set far * exceptfds, 
                   const struct timeval far * timeout ) ;

int _cdecl select_ms (int          nfds, 
                      fd_set far * readfds, 
                      fd_set far * writefds, 
                      fd_set far * exceptfds, 
                      long         timeout ) ;  // milliseconds

int _cdecl FD_Next (const fd_set * fds_set, int previous_fds) ;



#ifdef __cplusplus
}
#endif


/*************************************************************************/
#endif /* __TCPIP_SOCKET_H__*/
/*************************************************************************/
//end TCPIP_Socket.h
/*************************************************************************/

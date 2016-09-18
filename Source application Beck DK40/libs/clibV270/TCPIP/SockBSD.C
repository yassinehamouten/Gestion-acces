/****************************************************************************
* (C) 1999-2012 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : SockBSD.C
* Function       : TCPIP BSD Sockets API functions
* ---------------------------------------------------------------------------

$Header: $

*****************************************************************************/

#define  SC123                  // So that TCPIP_STACK_V2 will be defined

#define TCPIP_DYN_LINK_SOCK     // Use dynamic link prototypes in this module.

#include <STDLIB.H>
#include <DOS.H>
#include "common.h"
#include "config.h"
#include <TCPIPAPI.H>
#include <TCPIP.H>
#include "TCPPRIV.H"


/***

 @doc DOC_INDEX
 ---------------------------------------------------------------
 TCP/IP BSD Sockets API Table of Contents
 ---------------------------------------------------------------
 @clibLinkIdx  <tab><cfont>#include <InBraces TCPIP\.H><efont><nl>
  <tab><tab><tab><tab><tab><arial>which includes<ariale> <cfont>
 <InBraces TCP_Socket\.H><efont> |
    <tab><linkto>#Control<linkmid>Control<linktail><tab>
    <tab><linkto>#Data<linkmid>Data Send/Receive<linktail><tab>
    <tab><linkto>#Utilities<linkmid>Utilities<linktail><tab>
    |
  <nl>
  These functions are available for <i>SC1x3/SC2x only!<ie>.<nl>
  <nl>
  This set of socket functions are compatible with the BSD 4.4 Socket
  standard.<s2> They reach the function implementation inside the <chiprtos> 
  using <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>dynamic linking<linktail>,
  which has a speed advantage (after the first call) over the legacy 
  software interrupt based API.<nl>
  <nl>
  <bold>Related<bolde>:
  <ul>
      <li> TCP/IP  <linkto>../../tcpstruc.htm<linkmid>Data Structures<linktail><nl>
      <li> TCP/IP C-Library <linkto>lib_index.htm<linkmid>Main List<linktail>  <nl>
  <ule>

 @libcat1  Control |  bsd25 | accept_bsd     | TCP Server accept connection | 
 @libcat1  Control |  bsd26 | bind_bsd     | Bind socket | 
 @libcat1  Control |  bsd27 | connect_bsd     | Connect to a TCP server | 
 @libcat1  Control |  bsd28 | close_bsd     | Close socket | 
 @libcat1  Control |  bsd29 | getsockopt_bsd     | Read socket option | 
 @libcat1  Control |  bsd31 | listen_bsd     | TCP Server listen for client connect | 
 @libcat1  Control |  bsd37 | setsockopt_bsd     | Set socket option | 
 @libcat1  Control |  bsd36 | shutdown_bsd     | Shutdown TCP socket| 
 @libcat1  Control |  bsd41 | socket     | Create a socket | 

 @libcat2  Data |  bsd32 | recv_bsd     | Receive TCP data | 
 @libcat2  Data |  bsd33 | recvfrom_bsd     | Receive a UDP datagram | 
 @libcat2  Data |  bsd34 | send_bsd     | Send TCP data | 
 @libcat2  Data |  bsd35 | sendto_bsd     | Transmit a UDP datagram | 

 @libcat3  Utilities |  bsd30 | inet_addr_bsd     | Convert ASCII IPv4 address | 

*/



///////////////////////////////////////////////////////////////////////////////
//
//     CAUTION!!  -  Compilation switches are required by DOCLIST tool
//
//   Even though we have no code to compile for these dynamic linked API, 
//  we still must place the "#ifdef _bsd25_" like compilation switches 
//  around the documentation to assist the DOCLIST tool.  The DOCLIST tool
//  uses these compilation switch macro names like _bsd25_ to construct the
//  corresponding HTM file "bsd25.htm" to which it will link the  extracted
//  Beck C-Lib procedure name, like accept_bsd() for this case below.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef _bsd25_
/*
@doc DOC_bsd25_
 ----------------------------------------------------------------------------------
 accept
 ----------------------------------------------------------------------------------
 @clibSub  accept_bsd | bsd_index.htm | Accept client connection |
        <cfont>int far accept_bsd ( int sd,<nl>
          <tab><tab><tab><tab><tab> struct sockaddr far * addressPtr,<nl>
          <tab><tab><tab><tab><tab> int far * addressLengthPtr ) ;<efont> |
 @parm  int  | sd  | Socket descriptor, which must have been switched into
        listen mode using <linkto>bsd31.htm<linkmid>listen_bsd()<linktail> 
        (or <linkto>tcp0E.htm<linkmid>listen()<linktail>) API.
 @parm int  | addressPtr  | Optional output parameter:<s2>Pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>  (IPv4)
        or  <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6 <linktail>
         (IPv6) data structure.<s2>
        On success, this function fills in this <i>sockaddr_in<ie> or
        <i>sockaddr_in6<ie> structure with the
        IP address and port number of the accepted connection.<s2>
        This pointer can be set to NULL if this address and port number report
        is not desired.

 @parm  void | addressLengthPtr | Input/Output Parameter:<s2> 
    This parameter may be set to NULL if <i>addressPtr<ie> is NULL.<s2>
    Otherwise this pointer must reference an integer value set to
    the size  of the object referenced by <i>addressPtr<ie>.<s2> And
    on return, this same integer will be set to the size of the
    information written to  <i>addressPtr<ie>.
 @rdesc -1: Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror<linktail><nl>
        otherwise: New socket descriptor for the connection
 @comm 
    This call is used by a TCP server.<nl>
        <nl>
        This API function extracts the first connection on the queue
        of pending connections.<s2>  It then creates
        a new socket for this connection.<s2> This new socket will have
        the same socket options as the listening socket, <i>sd<ie>.<s2>
        On success, the handle to this new socket is returned.<nl>
        <nl>
        This function's prototype uses a pointer to the generic type 
        <linkto>../../tcpstruc.htm#sockaddr<linkmid>sockaddr<linktail> for 
        its <i>addressPtr<ie> parameter, for compatibility 
        between IPv4 and IPv6 protocols.<s2> The pointer to the
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
        (IPv4) or 
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6 <linktail>
        (IPv6) data structure which
        is actually used should be cast to <code>sockaddr<codee> pointer type here
        to avoid compiler warnings, "Suspicious pointer conversion".<nl>
    <nl>
    The parameters to <i>accept_bsd()<ie> are identical to the parameters of 
    the BSD4.4 <i>accept()<ie> socket function.<nl>
    <nl>
    If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>accept()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above.<s2>
    Using this switch the CLIB TCPIP_Socket.H redefines <i>accept()<ie>
    to <i>accept_bsd()<ie>.
    <nl>

 @Also  bsd31.htm | listen_bsd |
        tcp21.htm | get_socketerror  |
        tcp01.htm | opensocket
 @Also  tcp0D.htm | accept |
         | |
         |
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


#ifdef _bsd26_
/*
@doc DOC_bsd26_
 ----------------------------------------------------------------------------------
 bind
 ----------------------------------------------------------------------------------
 @clibSub  bind_bsd | bsd_index.htm | Bind an unnamed socket to an address
        and port number. |
        <cfont>int far bind_bsd ( int sd,<nl>
          <tab><tab><tab><tab><tab> const struct sockaddr far * addressPtr,<nl>
          <tab><tab><tab><tab><tab> int addressLength ) ;<efont> |
 @parm  int | sd | Socket descriptor
 @parm  void | addressPtr |  Pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
         (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6) data structure preset by caller.

 @parm  int | addressLength | Length of object at <i>addressPtr<ie> 
    in bytes, which must be either<nl>
    <tab> <code>sizeof(struct sockaddr_in)<codee><nl>
    or<nl>
    <tab> <code>sizeof(struct sockaddr_in6)<codee>.
 @rdesc 0 on success<nl>
        -1: Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror<linktail>.
 @comm 
    The bind call assigns the socket a specific port number for its
    source port address.<s2> Otherwise a random
    16-bit source port number will be used when no bind call is made.<s2>
    This binding is usually only necessary in server applications, where
    remote clients must find the server at an agreed upon port number.<nl>
        <nl>
    If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>bind()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above.<s2>
    Using this switch the C-Library TCPIP_Socket.H header file 
    redefines <i>bind()<ie> to <i>bind_bsd()<ie>.<nl>
    <nl>
     The caller must fill in the
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail> (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6) data structure at <i>addressPtr<ie> prior
          to making this API call.<s2>An example (IPv4) of how this
        can be done follows.<s2> This function's prototype uses a pointer to the
        generic type <linkto>../../tcpstruc.htm#sockaddr<linkmid>sockaddr<linktail>
        for its <code>addressPtr<codee> parameter,
        for compatibility between IPv4 and IPv6 protocols.<s2> The pointer to the
        <code>sockaddr_in<codee> (IPv4) or <code>sockaddr_in6<codee> (IPv6)
        data structure which
        is actually used should be cast to this type as shown below to avoid
        compiler warnings, "Suspicious pointer conversion".<nl>    
    <nl>

        @raw
        // Example
        int ClientPort = 4000 ;
        struct sockaddr_in addr ;
        int error_code = 0 ;

        addr.sin_family = PF_INET ;
        addr.sin_addr.s_addr =  0 ;
        addr.sin_port = htons(ClientPort);   // Network byte order
        if (bind_bsd ( sd, 
                      (const struct sockaddr *)&addr,
                       sizeof(struct sockaddr_in)) != 0)
        {
            error_code = get_socketerror(sd) ;
        }
 @Also  tcp03.htm | bind |
        tcp01.htm | opensocket  |
        tcp21.htm | get_socketerror
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

#ifdef _bsd27_
/*
@doc DOC_bsd27_
 ----------------------------------------------------------------------------------
    connect
 ----------------------------------------------------------------------------------
 @clibSub  connect_bsd | bsd_index.htm | Connect to another socket. |
        <cfont>int far connect_bsd ( int sd,<nl>
          <tab><tab><tab><tab><tab><s1> const struct sockaddr far * addressPtr,<nl>
          <tab><tab><tab><tab><tab><s1> int addressLength ) ;<efont> |
 @parm  int | sd | Socket descriptor
 @parm  void | addressPtr | Pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>  (IPv4) or
         <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
          (IPv6) data structure specifying host's IP
          address and port number.
 @parm  int | addressLength | Length of object at <cfont>addressPtr<efont> in bytes.
 @rdesc 0 on success<nl>
        -1: Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror<linktail>.
 @comm 
    <nl>
    If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>connect()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above.<s2>
    Using this switch the CLIB TCPIP_Socket.H redefines <i>connect()<ie>
    to <i>connect_bsd()<ie>.<nl>
    <nl>
    The caller must fill in the
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>  (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6) data structure at <i>addressPtr<ie>
         prior to calling here.<s2> An example of how
        this normally would be done follows.<s2> The PF_INET setting for the
        <code>sin_family<codee> is required for IPv4.<s2> For IPv6, set
        <code>sin6_family<codee> to PF_INET6.<nl>
        <nl>
        This function's prototype uses a pointer to the generic type 
        <linkto>../../tcpstruc.htm#sockaddr<linkmid>sockaddr<linktail> for
        its <i>addressPtr<ie> parameter,
        for compatibility between IPv4 and IPv6 protocols.<s2> The pointer to the
        <code>sockaddr_in<codee> or <code>sockaddr_in6<codee> data structure which
        is actually used should be cast to this type as shown below to avoid
        compiler warnings, "Suspicious pointer conversion".<nl>
        <nl>

        @raw
        // Example
        char szHostIPStr[] = "172.30.1.68" ;
        int  HostPort = 4000 ;
        struct sockaddr_in addr ;
        int error_code = 0 ;

            // Convert server IP address string to binary.
            //  (In network byte order)
        addr.sin_addr.s_addr = inet_addr_bsd (szHostIPStr) ;
        addr.sin_port = htons (HostPort) ;  // Network byte order
        addr.sin_family = PF_INET ;         // IPv4 protocol

        // Establish a connection to the server.
        if ( connect_bsd( sd, 
                         (const struct sockaddr *) &addr,
                          sizeof(struct sockaddr_in))
            != 0)
        {
            error_code = get_socketerror(sd) ;    
        }

 @Also  tcp04.htm | connect |
        tcp01.htm | opensocket  |
        tcp21.htm | get_socketerror
 @Also  bsd30.htm | inet_addr_bsd |
        |   |
        |
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

#ifdef _bsd28_
/*
@doc DOC_bsd28_
 ----------------------------------------------------------------------------------
    close socket
 ----------------------------------------------------------------------------------
 @clibSub  close_bsd | bsd_index.htm | Close a socket. |
        <cfont>int far close_bsd ( int sd) ;<efont> |
 @parm  int | sd | Socket descriptor
 @rdesc 0 on success<nl>
        -1: Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror<linktail>.
 @comm 
    Closes the socket indicated by <code>sd<codee> and releases all of
    its associated resources.<nl>
        <nl>
    The parameters to <i>close_bsd()<ie> are identical to the parameters of 
    the BSD4.4 <i>close()<ie> socket function.<nl>
    <nl>
    If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>closesocket()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above.<s2>
    Using this switch the CLIB TCPIP_Socket.H redefines <i>closesocket()<ie>
    to <i>close_bsd()<ie>.
    <nl>

 @Also tcp01.htm | opensocket  |
       tcpC3.htm | opensocket_ext | 
       tcp02.htm | closesocket

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


#ifdef _bsd29_
/*
@doc DOC_bsd29_
 ----------------------------------------------------------------------------------
    Get Socket Option getsockopt
 ----------------------------------------------------------------------------------
 @clibSub  getsockopt_bsd | bsd_index.htm | Get socket option. |
        <cfont>int far getsockopt_bsd (  int sd,<nl>
          <tab><tab><tab><tab><tab><tab> int protocol_level,<nl>
          <tab><tab><tab><tab><tab><tab> int optionName,<nl>
          <tab><tab><tab><tab><tab><tab> char far * optionValue,<nl>
          <tab><tab><tab><tab><tab><tab> int far * optionLengthPtr ) ;<efont> |
 @parm  int | sd | Socket descriptor
 @parm  int | protocol_level | One of following constants:<nl>
   <ul>
        <bold>IP_PROTOIP_LEVEL<bolde><nl>
        <bold>IP_PROTOTCP_LEVEL<bolde><nl>
        <bold>SOCKET_LEVEL<bolde> <nl>
   <ule>
 @parm  int | optionName | Option's name 
      <linkto>../../tcpstruc.htm#SocketOptions<linkmid>constant<linktail>.
 @parm  int | optionValue | Output Parameter:<s2> Option value is
     reported here (type varies).
 @parm  int | optionLengthPtr | Input/Output Parameter:<s2> Caller sets
    this referenced integer to the number of bytes space available
    in buffer referenced by <i>optionValue<ie> parameter.<s2> 
    On success, this API then sets this same integer to the size in bytes
    of the reported option.
 @rdesc 0 on success<nl>
        -1: Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror<linktail>.
 @comm
    On success, this function reports the requested socket option value to
    the buffer pointed to by the <i>optionValue<ie> parameter and the length
    of this reported value is written to the location pointed to by
    the <i>optionLengthPtr<ie> parameter.<nl>
        <nl>
    The <i>optionValue<ie> parameter must point to a sufficiently
    large buffer to receive the reported option value and the size
    of this buffer must be stated in the location referenced by 
    the <i>optionLengthPtr<ie> parameter.<s2> Note that this length
    specifier is both an input and an output parameter for this 
    function.<s2> If on entry, the location referenced
    by <i>optionLengthPtr<ie> contains a value less than the buffer
    space required to report the requested socket option value, then
    the function will fail with socket error code 242.<nl>
        <nl>
    The socket options of an incoming connection (using either
    <linkto>bsd25.htm<linkmid>accept_bsd()<linktail> or
    <linkto>tcp0D.htm<linkmid>accept()<linktail>) will be the same as the
    socket options of the listening socket.<nl>
    <nl>
     If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>getsockopt()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above.<s2>
    Using this switch the CLIB TCPIP_Socket.H redefines <i>getsockopt()<ie>
    to <i>getsockopt_bsd()<ie>.
    <nl>
 @Also  bsd37.htm | setsockopot_bsd |
        tcp17.htm | getsockopt  |
        tcp21.htm | get_socketerror
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


#ifdef _bsd30_
/*
@doc DOC_bsd30_
 ----------------------------------------------------------------------------------
    Convert IP address inet_addr
 ----------------------------------------------------------------------------------
 @clibSub  inet_addr_bsd | bsd_index.htm | Converts a dotted decimal IPv4 address string
     to an unsigned long.. |
        <cfont>unsigned long far inet_addr_bsd ( <nl>
          <tab><tab><tab><tab> const char * IPAddressStringPtr ) ;<efont> |
 @parm  int | IPAddressStringPtr | IPv4 dotted string IPv4 address
 @rdesc The IPv4 address in network byte order.<nl>
     An invalid dotted decimal string will yield -1, 
     same as would the string:<nl>
       <tab>   "255.255.255.255"

 @comm 
        This function applies only to IPv4 addresses.<s2> The
        <linkto>tcpC1.htm<linkmid>inet_pton<linktail> API can be used
        for either IPv4 or IPv6 address conversions.<nl>
    <nl>
     If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>inet_addr()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above.<s2>
    Using this switch the CLIB TCPIP_Socket.H redefines <i>inet_addr()<ie>
    to <i>inet_addr_bsd()<ie>.
    <nl>
 @Also  tcp08.htm | inet_addr |
        tcpC1.htm | inet_pton |
        tcp11.htm | InetToAscii
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


#ifdef _bsd31_
/*
@doc DOC_bsd31_
 ----------------------------------------------------------------------------------
    listen
 ----------------------------------------------------------------------------------
 @clibSub  listen_bsd | bsd_index.htm | Listen for incoming connections. |
        <cfont>int far listen_bsd ( int sd,<nl>
          <tab><tab><tab><tab><tab> int backlog ) ;<efont> |
 @parm  int | sd | Socket descriptor
 @parm  int | backlog | The maximum number (limited to 5) of allowed
        outstanding connections.
 @rdesc 0 on success<nl>
        -1: Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror<linktail>.
 @comm 
   This API function places the socket in passive mode and sets the
        number of incoming TCP connections that the system will queue
        (<i>backlog<ie>).<nl>
        <nl>
        This call is used by a TCP server.<nl>
        <nl>
     If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>listen()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above.<s2>
    Using this switch the CLIB TCPIP_Socket.H redefines <i>listen()<ie>
    to <i>listen_bsd()<ie>.
 @Also  bsd25.htm | accept_bsd |
        tcp01.htm | opensocket |
        tcpC3.htm | opensocket_ext
 @Also  tcp0E.htm | listen |
        tcp21.htm | get_socketerror |
        |
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


#ifdef _bsd32_
/*
@doc DOC_bsd32_
 ----------------------------------------------------------------------------------
    recv
 ----------------------------------------------------------------------------------
 @clibSub  recv_bsd | bsd_index.htm | Receive data from TCP socket. |
        <cfont>int far recv_bsd ( int sd,<nl>
          <tab><tab><tab><tab><s2> char far * bufptr,<nl>
          <tab><tab><tab><tab><s2> int buflen,<nl>
          <tab><tab><tab><tab><s2> int flags,<nl>
          <tab><tab><tab><tab><s2> unsigned long timeout ) ;<efont> |
 @parm  int | sd | Socket descriptor
 @parm  int | bufptr | Output Parameter:<s2>  Received data will be put here.
 @parm  int | buflen | Maximum bytes to write to the buffer at 
               <i>bufptr<ie>.
 @parm  int | flags | Control flags:<s2> Either MSG_BLOCKING (=0) or MSG_DONTWAIT.<nl>
      <nl>
      Additionally, the MSG_PEEK flag can be bitwise OR'ed in to return without 
      freeing the packet.<s2>The data is returned, but not consumed so that
      a subsequent receive operation will see the same data.
 @parm  int | timeout | Maximum wait time in milliseconds.<s2> Set to
            zero to wait forever when blocking mode is in effect.<s2>
            This parameter has no effect if the MSG_DONTWAIT flag is set.
 @rdesc > 0:<s2>  Number of data bytes placed at <i>bufptr<ie>.<nl>
        -1:<s2> Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror()<linktail>.
 @comm 
    This API function applies only to TCP sockets.<s2>
    It receives a message from another socket.<s2>
    This API function may be used only if the socket is in a
    connected state.<nl>
    <nl>
    The MSG_BLOCKING mode will not work if the socket has been put into 
    non-blocking mode using the 
    <linkto>tcp18.htm<linkmid>SocketBlockingMode()<linktail> function.<nl>
    <nl>
    If <i>flags<ie> parameter is set to MSG_DONTWAIT, this API call returns
    immediately.<s2>If no data is available -1 is returned and 
    <linkto>tcp21.htm<linkmid>get_socketerror()<linktail> will report
    error code 235 in this case.<nl>
     <nl>
     If <i>flags<ie> parameter is set to MSG_BLOCKING and this socket
     had not been switched to non-blocking mode, the <code>recv_bsd()<codee>
    call waits for either a message to arrive, <code>timeout<codee> milliseconds
    (assuming <code>timeout<codee> was non-zero), or a socket error condition
    to occur (such as connection lost or socket closed).<s2>
    By default the blocking mode is set true at the
    <linkto>tcp01.htm<linkmid>opensocket()<linktail> call.<s2>
    The socket may subsequently be set to non-blocking mode with the
    <linkto>tcp18.htm<linkmid>Set_Blocking_Mode()<linktail> API.<s2>
    The MSG_DONTWAIT flag set here will override this internal socket
    state.<nl>
    <nl>
     If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>recv()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above, except for the
    <code>timeout<codee> parameter.<s2>
    Using this switch the CLIB TCPIP_Socket.H redefines <i>recv()<ie>
    to <i>recv_bsd()<ie> with a zero supplied for the <code>timeout<codee>
    parameter that is not part of the BSD API.<nl>

 @Also  bsd34.htm | send_bsd  |
        bsd33.htm | recvfrom_bsd |
        tcp01.htm | opensocket
 @Also  tcp18.htm | Set_Blocking_Mode |
        tcp1A.htm  | select |
        tcp1Am.htm | select_ms
 @Also  tcp10.htm | recv |
        tcp21.htm | get_socketerror |
         |
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


#ifdef _soc32_
int recv_Dyn (int sd, char far * bufptr, int bufLen, int flags,
              unsigned long timeout, int *error)
{
    int byte_cnt ;
    int the_error = 0 ;
    if (flags == MSG_TIMEOUT)
    {
        flags = MSG_BLOCKING ;
    }
    else
    {
        timeout = 0 ;
    }
    byte_cnt = recv_bsd(sd, bufptr, bufLen, flags, timeout) ;
    if (byte_cnt == -1)
    {
        the_error = get_socketerror_Dyn(sd) ;
    }
    *error = the_error  ;

    return byte_cnt ;

}
#endif 


#ifdef _bsd33_
/*
@doc DOC_bsd33_
 ----------------------------------------------------------------------------------
    recvfrom
 ----------------------------------------------------------------------------------
 @clibSub  recvfrom_bsd | bsd_index.htm | Receive a UDP datagram. |
        <cfont>int far recvfrom_bsd ( int sd,<nl>
          <tab><tab><tab><tab><s2> char far * bufptr,<nl>
          <tab><tab><tab><tab><s2> int buflen,<nl>
          <tab><tab><tab><tab><s2> int flags,<nl>
          <tab><tab><tab><tab><s2> struct sockaddr far * fromPtr,<nl>
          <tab><tab><tab><tab><s2> int far * fromLengthPtr,<nl>
          <tab><tab><tab><tab><s2> unsigned long timeout ) ;<efont> |
 @parm  int | sd | Socket descriptor
 @parm  int | bufptr | Output Parameter:<s2>  Received data will be put here.
 @parm  int | buflen | Maximum bytes to write to the buffer at 
               <i>bufptr<ie>.
 @parm  int | flags | Control flags:<s2> Either MSG_BLOCKING (=0) or MSG_DONTWAIT.<nl>
      <nl>
      Additionally, the MSG_PEEK flag can be bitwise OR'ed in to return without 
      freeing the packet.<s2>The data is returned, but not consumed so that
      a subsequent receive operation will see the same data.
 @parm  int | fromPtr |  Output Parameter:<s2> Pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
         (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6) data structure, which will be set
         to indicate from where the received data originated.<s2> This pointer
         can be set to NULL if this information is not desired.<nl>
 @parm  int | fromLengthPtr | Input/Output Parameter:<s2> The integer 
      referenced by this pointer must be set prior to calling to the 
      length of the object at <i>fromPtr<ie>.<s2>  If <i>fromPtr<ie> is
      NULL, then this parameter is not required and can be set to NULL.<s2>
      On return the length of object written o <i>fromPtr<ie> will be 
      reported here.
 @parm  int | timeout | Maximum wait time in milliseconds.<s2> Set to
            zero to wait forever when blocking mode is in effect.<s2>
            This parameter has no effect if the MSG_DONTWAIT flag is set.
 @rdesc > 0:  Number of data bytes placed at <i>bufptr<ie>.<nl>
        -1:<s2> Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror()<linktail>.
 @comm 
    This API applies to UDP sockets.<nl>
    <nl>
    The MSG_BLOCKING mode will not work if the socket has been put into 
    non-blocking mode using the 
    <linkto>tcp18.htm<linkmid>SocketBlockingMode()<linktail> function,
    unless the <code>timeout<codee> parameter is non-zero.<nl>
    <nl>
    If <i>flags<ie> parameter is set to MSG_DONTWAIT, this API call returns
    immediately.<s2>If no data is available -1 is returned and 
    <linkto>tcp21.htm<linkmid>get_socketerror()<linktail> will report
    error code 235 in this case.<nl>
    <nl>
    If the waiting datagram at the internal socket receive queue has a size larger
    than the specified <i>bufLen<ie>, the return value will be -1 and 
    error code 240 ("Message too long") will be reported by the
    <linkto>tcp21.htm<linkmid>get_socketerror()<linktail> in this case.<s2>
    The receive buffer contains the truncated datagram.<nl>
    <nl>
    This function's prototype takes a pointer to the
    generic type <linkto>../../tcpstruc.htm#sockaddr<linkmid>sockaddr<linktail>
    for its <i>fromPtr<ie> parameter,for compatibility between IPv4 and IPv6
    protocols.<s2> The pointer to the <code>sockaddr_in<codee> (IPv4) or 
    <code>sockaddr_in6<codee> (IPv6) data structure which is actually used
    should be cast to a <code>sockaddr<codee> type pointer to avoid compiler
    warnings, "Suspicious pointer conversion".<nl>
      <nl>
     If <i>flags<ie> parameter is set to MSG_BLOCKING and this socket
     had not been switched to non-blocking mode, the <code>recvfrom_bsd()<codee>
    call waits for either a message to arrive, <code>timeout<codee> milliseconds
    (assuming <code>timeout<codee> was non-zero), or a socket error condition
    to occur (such as connection lost or socket closed).<s2>
    By default the blocking mode is set true at the
    <linkto>tcp01.htm<linkmid>opensocket()<linktail> call.<s2>
    The socket may subsequently be set to non-blocking mode with the
    <linkto>tcp18.htm<linkmid>Set_Blocking_Mode()<linktail> API.<s2>
    The MSG_DONTWAIT flag set here will override this internal socket
    state.<nl>
    <nl>
    If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>recvfrom()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above, except for the
    <code>timeout<codee> parameter.<s2>
    Using this switch the CLIB TCPIP_Socket.H redefines <i>recvfrom()<ie>
    to <i>recvfrom_bsd()<ie> with a zero supplied for the <code>timeout<codee>
    parameter that is not part of the BSD API.<nl>
      
 @Also  bsd35.htm | sendto_bsd  |
        bsd32.htm | recv_bsd |
        tcp01.htm | opensocket
 @Also  tcp18.htm | Set_Blocking_Mode |
        tcp1A.htm  | select |
        tcp1Am.htm | select_ms
 @Also  tcp05.htm | recvfrom |
        tcp21.htm | get_socketerror |
         |
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

#ifdef _soc33_
int recvfrom_Dyn( int sd, 
                  char far * bufptr, 
                  int bufLen,
                  int flags,
                  unsigned long timeout,
                  struct sockaddr far * fromPtr,
                  int *error)
{
    int byte_cnt ;
    int the_error = 0 ;
    int fromLen =  sizeof(struct sockaddr_in6);

    // Note: If optional parameter fromPtr is NULL, then we do a harmless
    //     read from low memory here.
    if ( ((struct sockaddr_in_ipstackV2 far *)fromPtr)->sin_family == AF_INET)
    {
       fromLen = sizeof(struct sockaddr_in_ipstackV2);
    }
    if (flags == MSG_TIMEOUT)
    {
        flags = MSG_BLOCKING ;
    }
    else
    {
        timeout = 0 ;
    }
    byte_cnt = recvfrom_bsd( sd, 
                             bufptr,
                             bufLen,
                             flags, 
                             fromPtr,
                            &fromLen,
                             timeout) ;
    if (byte_cnt == -1)
    {
        the_error = get_socketerror_Dyn(sd) ;
    }
    *error = the_error  ;

    return byte_cnt ;

}
#endif 


#ifdef _bsd34_
/*
@doc DOC_bsd34_
 ----------------------------------------------------------------------------------
    send
 ----------------------------------------------------------------------------------
 @clibSub  send_bsd | bsd_index.htm | Send TCP data. |
        <cfont>int far send_bsd ( int sd,<nl>
          <tab><tab><tab><tab><s2> const char far * bufptr,<nl>
          <tab><tab><tab><tab><s2> int buflen,<nl>
          <tab><tab><tab><tab><s2> int flags ) ;<efont> |
 @parm  int | sd | Socket descriptor
 @parm  int | bufptr | Data to be sent.
 @parm  int | buflen | Maximum characters to output 
        from <i>bufptr<ie>.
 @parm  int | flags | Wait option:<nl>
        <ul>
        <li><bold>MSG_BLOCKING<bolde>  - Wait for data send
        to complete.<nl>
        <li><bold>MSG_DONTWAIT<bolde> - Don't wait for data
        send to complete.<nl>
        <ule>
 @rdesc -1:  Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror()<linktail><nl>
        otherwise:<s2> Count of bytes transfered into the socket 
        send queue
 @comm  This API function applies only to TCP sockets.<s2>
        It transmits a message to another transport end-point.<s2>
        It may be used only if the socket is in a
        connected state.<nl>
        <nl>
        The <bold>MSG_BLOCKING<bolde> mode will not work if the socket has
        been put into non-blocking mode using the
    <linkto>tcp18.htm<linkmid>SocketBlockingMode()<linktail> function,
    unless the <code>timeout<codee> parameter is non-zero.<nl>
      <nl>
     If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>send()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above.<s2>
    Using this switch the CLIB TCPIP_Socket.H redefines <i>send()<ie>
    to <i>send_bsd()<ie>.<nl>
      
 @Also  bsd35.htm | sendto_bsd  |
        bsd32.htm | recv_bsd |
        tcp01.htm | opensocket
 @Also  tcp18.htm | Set_Blocking_Mode |
        tcp1A.htm  | select |
        tcp1Am.htm | select_ms
 @Also  tcp0F.htm | send |
        tcp21.htm | get_socketerror |
         |
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


#ifdef _soc34_
int send_Dyn( int              sd, 
              const char far * bufptr, 
              int              bufLen,
              int              flags, 
              int            * error)
{
    int the_error = 0 ;
    int byte_cnt = send_bsd( sd, 
                             bufptr,
                             bufLen,
                             flags) ;
    if (byte_cnt == -1)
    {
        the_error = get_socketerror_Dyn(sd) ;
    }
    *error = the_error  ;

    return byte_cnt ;

}
#endif 


#ifdef _bsd35_
/*
@doc DOC_bsd35_
 ----------------------------------------------------------------------------------
    sendto
 ----------------------------------------------------------------------------------
 @clibSub  sendto_bsd | bsd_index.htm | Transmit a UDP datagram. |
        <cfont>int far sendto_bsd ( int sd,<nl>
          <tab><tab><tab><tab><tab> const char far * bufptr,<nl>
          <tab><tab><tab><tab><tab> int buflen,<nl>
          <tab><tab><tab><tab><tab> int flags,<nl>
          <tab><tab><tab><tab><tab> const struct sockaddr far * toPtr,<nl>
          <tab><tab><tab><tab><tab> int toLength ) ;<efont> |
 @parm  int | sd | Socket descriptor
 @parm  int | bufptr | Data to be sent.
 @parm  int | buflen | Number of bytes to send.
 @parm  int | flags | Wait option:<nl>
        <ul>
        <li><bold>MSG_BLOCKING<bolde>  - Wait for data send
        to complete.<nl>
        <li><bold>MSG_DONTWAIT<bolde> - Don't wait for data
        send to complete.<nl>
        <ule>
 @parm  int | toPtr | IP address information datagram destination.<s2>
    Pointer to a
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
         (IPv4) or
        <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
         (IPv6) data structure set by caller prior to call.
 @parm  int | toLength | Size of object pointed to by 
        <i>toPtr<ie>.
 @rdesc -1:  Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror()<linktail><nl>
        otherwise:<s2> Count of bytes transfered into the socket 
        send queue
 @comm 
    This API function applies only to UDP sockets.<s2>
    This function will output up to <i>bufLen<ie> bytes from the buffer
    at <i>bufptr<ie> to the IP address specified by the
    <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
    (IPv4) structure or the
    <linkto>../../tcpstruc.htm#sockaddr_in6<linkmid>sockaddr_in6<linktail>
    (IPv6) structure referenced by the <i>toPtr<ie> parameter.<nl>
        <nl>
    This function's prototype takes a pointer to the
    generic type <linkto>../../tcpstruc.htm#sockaddr<linkmid>sockaddr<linktail> 
    for its <i>toPtr<ie> parameter, for compatibility between IPv4 and IPv6 
    protocols.<s2> The pointer to the <code>sockaddr_in<codee> (IPv4) or
    <code>sockaddr_in6<codee> (IPv6) data structure which is actually used 
    should be cast to a <code>sockaddr<codee> type pointer to avoid compiler
    warnings, "Suspicious pointer conversion".<nl>
        <nl>
    The <bold>MSG_BLOCKING<bolde> mode will not work if the socket has
    been put into non-blocking mode using the
    <linkto>tcp18.htm<linkmid>Set_Blocking_Mode<linktail> API.<nl>
      <nl>
     If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>sendto()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above.<s2>
    Using this switch the CLIB TCPIP_Socket.H redefines <i>sendto()<ie>
    to <i>sendto_bsd()<ie>.<nl>
      
 @Also  bsd34.htm | send_bsd  |
        bsd33.htm | recvfrom_bsd |
        tcp01.htm | opensocket
 @Also  tcp18.htm | Set_Blocking_Mode |
        tcp1A.htm  | select |
        tcp1Am.htm | select_ms
 @Also  tcp06.htm | sendto |
        tcp21.htm | get_socketerror |
         |
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


#ifdef _soc35_
int sendto_Dyn ( int sd, 
                 const char far * bufptr, 
                 int bufLen, 
                 int flags,
                 const struct sockaddr far * toPtr, 
                 int *error)
{
    int byte_cnt ;
    int the_error = 0 ;
    int toLen = sizeof(struct sockaddr_in_ipstackV2) ;

    if ( ((struct sockaddr_in_ipstackV2 far *)toPtr)->sin_family != AF_INET)
    {
       toLen = sizeof(struct sockaddr_in6);
    }
    byte_cnt = sendto_bsd( sd, 
                           bufptr,
                           bufLen,
                           flags, 
                           toPtr,
                           toLen) ;
    if (byte_cnt == -1)
    {
        the_error = get_socketerror_Dyn(sd) ;
    }
    *error = the_error  ;

    return byte_cnt ;

}
#endif 

#ifdef _bsd36_
/*
@doc DOC_bsd36_
 ----------------------------------------------------------------------------------
    shutdown
 ----------------------------------------------------------------------------------
 @clibSub  shutdown_bsd | bsd_index.htm | Shutdown TCP socket |
        <cfont>int far shutdown_bsd(int sd, int  dir);<efont> |
 @parm  int | sd | Socket descriptor
 @parm  int | dir | Direction:<s2> 0=Read, 1=write, 2=both
 @rdesc 0 on success<nl>
        -1: Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror()<linktail> API.
 @comm 
   Shutdown a socket in read, write or both directions.<s2>
   This API function only works on TCP sockets.<nl>
      <nl>
     If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>shutdown()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above.<s2>
    Using this switch the CLIB TCPIP_Socket.H redefines <i>shutdown()<ie>
    to <i>shutdown_bsd()<ie>.<nl>
      
 @Also  tcp26.htm | shutdown  |
        tcp02.htm | closesocket |
        tcp01.htm | opensocket
 @Also  tcp21.htm | get_socketerror |
         | |
         |
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


#ifdef _bsd37_
/*
@doc DOC_bsd37_
 ----------------------------------------------------------------------------------
    Set Socket Option setsockopt
 ----------------------------------------------------------------------------------
 @clibSub  setsockopt_bsd | bsd_index.htm | Set socket option. |
        <cfont>int far setsockopt_bsd (  int sd,<nl>
          <tab><tab><tab><tab><tab><tab> int protocol_level,<nl>
          <tab><tab><tab><tab><tab><tab> int optionName,<nl>
          <tab><tab><tab><tab><tab><tab> const char far * optionValue,<nl>
          <tab><tab><tab><tab><tab><tab>  int optionLength ) ;<efont> |
 @parm  int | sd | Socket descriptor
 @parm  int | protocol_level | One of following constants:<nl>
   <ul>
        <bold>IP_PROTOIP_LEVEL<bolde><nl>
        <bold>IP_PROTOTCP_LEVEL<bolde><nl>
        <bold>SOCKET_LEVEL<bolde> <nl>
   <ule>
 @parm  int | optionName | Option's name 
      <linkto>../../tcpstruc.htm#SocketOptions<linkmid>constant<linktail>.
 @parm  int | optionValue | Pointer to socket option's desired value.
 @parm  int | optionLength | Size of option data, in bytes.
 @rdesc 0 on success<nl>
        -1: Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror<linktail>.
 @comm 
    This API function makes it possible to manipulate options associated
    with a socket.<nl>
    <nl>
    Note that the socket options of an incoming connection (using
    <linkto>tcp0D.htm<linkmid>accept<linktail> or
    <linkto>bsd25.htm<linkmid>accept_bsd<linktail>) will be the same
    as the socket options of the listening socket.<nl>
    <nl>
     If the compilation switch<nl>
    <nl>
        <code>
        <tab> #define  BSD44_SOCKET_API_STYLE<codee><nl>
    <nl>
    is set as a global define in the user application prior to including the
    Beck C-library header files, the <i>setsockopt()<ie> call can be used in 
    BSD 4.4 compatible style with the parameters specified above.<s2>
    Using this switch the CLIB TCPIP_Socket.H redefines <i>setsockopt()<ie>
    to <i>setsockopt_bsd()<ie>.<nl>
      
 @Also  bsd29.htm | getsockopt_bsd |
        tcp16.htm | setsockopt  |
        tcp21.htm | get_socketerror
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


//////////////////////////////////////////////////////////////////
// Dynamic link variant for recvfromto().
//////////////////////////////////////////////////////////////////
#ifdef _soc38_

// recvFromTo_Link() is implemented in assembly.
extern int far recvFromTo_Link( int                  sd,
                                char            far *bufferPtr,
                                int                  bufferLength,
                                int                  flags,
                                struct sockaddr far *fromAddressPtr,
                                int             far *addressLengthPtr,
                                struct sockaddr far *toAddressPtr,
                                long                 timeout) ;

/////////////////////////////////////////////////////////////////////
int  recvfromto_Dyn( int sd, 
                     char far * bufptr, 
                     int bufLen, 
                     int flags,
                     unsigned long timeout,
                     struct sockaddr far * fromPtr,
                     struct sockaddr far * toPtr,
                     int *error)
{
    int result ;
    int the_error = 0 ;
    int   addressLength = sizeof(struct sockaddr_in_ipstack) ;
    if (flags == MSG_TIMEOUT)
    {
        flags = MSG_BLOCKING ;
    }
    else
    {
        timeout = 0 ;
    }
    result = recvFromTo_Link( sd, 
                              bufptr,
                              bufLen,
                              flags,
                              fromPtr,
                              &addressLength,
                              toPtr,
                              timeout) ;
    if (result < 0)
    {
        the_error = get_socketerror_Dyn(sd) ;
    }
    *error = the_error ;
    return result ;

}
#endif 


//////////////////////////////////////////////////////////////////
// Dynamic link variant for sendto_iface().
//////////////////////////////////////////////////////////////////
#ifdef _soc40_

    // sendto_iface_Link() is implemented in assembly.
extern int far sendto_iface_Link ( int                  sd,
                             const char            far *bufferPtr, 
                                   int                  bufferLength,
                                   int                  flags,
                             const struct sockaddr far *toAddressPtr,
                                   int                  toAddressLength,
                                   DevUserIfaceHandle   interfaceHandle,
                                   unsigned char        mhomeIndex ) ;


/////////////////////////////////////////////////////////////////////
int  _cdecl sendto_iface_Dyn ( int                   sd, 
                         const char            far * bufptr, 
                               int                   bufLen, 
                               int                   flags,
                         const struct sockaddr far * toPtr,
                               DevUserIfaceHandle    DevHandlePtr,
                               int                 * error)
{
    int bytes_sent ;
    int the_error = 0 ;
    int toLen = sizeof(struct sockaddr_in6) ;   // Unlikely assumption.
    
    if ( ((struct sockaddr_in_ipstackV2 *)toPtr)->sin_family == AF_INET)
    {
        toLen = sizeof(struct sockaddr_in_ipstackV2);   // Likely correction.
    }
    
    bytes_sent = sendto_iface_Link( sd,
                                    bufptr,
                                    bufLen,
                                    flags,
                                    toPtr,
                                    toLen,
                                    DevHandlePtr,
                                    0);
    if (bytes_sent <= 0)                // Failure?
    {
        bytes_sent = API_ERROR ;
        the_error = get_socketerror_Dyn(sd) ;
    }
    *error = the_error ;
    return bytes_sent ;
    
}   // sendto_iface_Dyn()

#endif 

#ifdef _bsd41_
/*
@doc DOC_bsd41_
 ----------------------------------------------------------------------------------
    send
 ----------------------------------------------------------------------------------
 @clibSub  socket | bsd_index.htm | Create a socket. |
        <cfont>int far socket ( int family,<nl>
          <tab><tab><tab><tab><s2> int type,<nl>
          <tab><tab><tab><tab><s2> int protocol ) ;<efont> |
 @parm  int | family |  
        <bold>AF_INET<bolde> (=2) for IPv4 address family<nl>
        <bold>AF_INET6<bolde> (=28) for IPv6 address family
 @parm  int | type |  <bold>SOCK_STREAM<bolde> (=1) : Stream based socket<nl>
    <bold>SOCK_DGRAM<bolde> (=2) : Datagram based socket 

 @parm  int | protocol |  <bold>IPPROTO_TCP<bolde> (=6) :<s2> TCP socket<nl>
    <bold>IPPROTO_UDP<bolde> (=17) :<s2> UDP socket 

 @rdesc -1:  Failure, error code is available using 
        <linkto>tcp21.htm<linkmid>get_socketerror(-1)<linktail><nl>
        otherwise:<s2> New socket descriptor
 @comm  Creates an endpoint for communication and returns a socket
    descriptor.<s2> This function provides the BSD socket functionality.<nl>
    <nl>

 @Also  bsd27.htm | connect_bsd |
        bsd31.htm | listen_bsd |
        bsd25.htm | accept_bsd
 @Also  tcpC3.htm | opensocket_ext  |
          |  |
          |
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


/**************************************************************************/
//end SockBSD.c
/*************************************************************************/

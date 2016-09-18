/*******************************************************************************
*
* (c) 2006 by BECK IPC GmbH
* http://www.beck-ipc.com
*
********************************************************************************
*
* Module:             dnsapi.h
* Function:           Constants, data types and function prototypes of DNS
*                     resolver API.
*
********************************************************************************
*
* $Header: c:\prjPib\IPC@CHIP\CLib\DNSAPI.H, 2, 02.03.2006 08:46:01, Jan Schatz$
*
*******************************************************************************/



#ifndef DNS_API_H
#define DNS_API_H



/*******************************************************************************
* Maximum length of a domain name in dotted notation including trailing dot.
* E.g. "www.beck-ipc.com."
*******************************************************************************/
#define DNS_SIZE_NAME_STRING  254



/******************************************************************************
* Error Codes
******************************************************************************/
#define DNS_ERROR_ILLEGAL_ARGUMENT     -1   // An argument with an invalid value
                                            // was passed
#define DNS_ERROR_RESOURCE_LACK        -2   // Lack of a resource such as
                                            // memory or sockets
#define DNS_ERROR_SERVERS_UNREACHABLE  -3   // No name server could be reached
#define DNS_ERROR_NO_RESOLUTION        -4   // No resolution could be found



/******************************************************************************
* Definition of types
******************************************************************************/
// A variable of this type holds infomation on a mail host.
typedef struct DnsMailHost_
{
  char name[DNS_SIZE_NAME_STRING + 1];  // Domain name of the host
  unsigned short preference;            // Preference value of the host. Lower
                                        // values are preferred.
} DnsMailHost;



/******************************************************************************
* Prototypes of functions
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

short _cdecl getHostByName( const char far *domainName,
                            unsigned char nAddresses,
                            struct in_addr far *addresses );
short _cdecl getHostByName2( const char far *domainName,
                             unsigned char nAddresses,
                             struct in6_addr far *addresses );
short _cdecl getHostByAddr( struct in_addr far *address,
                            char far *domainName );
short _cdecl getHostByAddr2( struct in6_addr far *address,
                             char far *domainName );
short _cdecl getMailHosts( const char far *domainName,
                           unsigned char nHosts,
                           DnsMailHost far *hosts );
short _cdecl setNameServer( int addressFamily,
                            void far *address );

#ifdef __cplusplus
}
#endif



#endif
// End of file

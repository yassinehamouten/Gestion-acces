/*******************************************************************************
*
* (c) 2006 by BECK IPC GmbH
* http://www.beck-ipc.com
*
********************************************************************************
*
* Module:             ipsec.h
* Function:           Constants, data types and function prototypes 
*                     for IP Security API.
*
********************************************************************************
*
* $Header: c:\prjPib\IPC@CHIP\CLib\IPsec.h, 12, 09.05.2007 11:13:11, Jack Gatrost$
*
*******************************************************************************/



#ifndef _IPSEC_H_
#define _IPSEC_H_

#include <TCPIPAPI.H>

////////////////////////////////////////////////////////////////////////////
//  Policy Pairs
////////////////////////////////////////////////////////////////////////////
typedef struct sIPSEC_POLICY_PAIR
{
    unsigned int        iSelectorIndex ;
    unsigned char       bContentIndex ;
    unsigned char       bDirection ;

} tIPSEC_POLICY_PAIR ;

////////////////////////////////////////////////////////////////////////////
//  IPsec Selector Address Specifier
////////////////////////////////////////////////////////////////////////////
typedef struct sIPSEC_ADDR
{
    unsigned char Usage ;       // How this specifier is to be used.

    unsigned char Family ;      // AF_INET (IPv4) or AF_INET6 (IPv6)

    // All IP addresses here are in network byte order.
    // Length:  IPv4 - 4 bytes (trailing 12 ignored)
    //          IPv6 - 16 bytes
    unsigned char IpAddr1[16] ;  // Single IP, or start of range
    unsigned char IpAddr2[16] ;  // End or range, or netmask, or unused.

    unsigned int  Port ;        // Set to IPSEC_WILD_PORT for no port filtering.

} tIPSEC_ADDR ;


////////////////////////////////////////////////////////////////////////////
//  Policy Selector
////////////////////////////////////////////////////////////////////////////
typedef struct sIPSEC_POLICY_SELECTOR 
{
    struct sIPSEC_ADDR    Local ;
    struct sIPSEC_ADDR    Remote ;
    unsigned char         Protocol ;    // Optional filter
    unsigned char         _pad_ ;       // reserved (set to 0)

} tIPSEC_POLICY_SELECTOR ;


////////////////////////////////////////////////////////////////////////////
//  Tunnel End Points
////////////////////////////////////////////////////////////////////////////
typedef struct sIPSEC_TUNNEL
{
    // All IP addresses here are in network byte order.
    // Length:  IPv4 - 4 bytes (trailing 12 ignored)
    //          IPv6 - 16 bytes
    unsigned char FamilyLocal ;  // AF_INET (IPv4) or AF_INET6 (IPv6)
    unsigned char IpLocal[16] ;  // IP address of our side of tunnel.

    unsigned char FamilyRemote ; // AF_INET (IPv4) or AF_INET6 (IPv6)
    unsigned char IpRemote[16] ; // IP address of other end of tunnel.

} tIPSEC_TUNNEL ;


////////////////////////////////////////////////////////////////////////////
//  Policy Content
////////////////////////////////////////////////////////////////////////////
typedef struct sIPSEC_POLICY_CONTENT    // For user API
{
    // AH | ESP, tunnel|transport, policy|packet determination
    unsigned int            RuleFlags ; 
    // ESP may also have authentication algorithm
    unsigned char           AuthAlg ;
    unsigned char           EncryptAlg ;
    unsigned long           LifeSeconds ;
    unsigned long           LifeKbytes ;
    struct sIPSEC_TUNNEL    Tunnel ;
    unsigned int            _spare_ ;   // Reserved (set to zero)

}  tIPSEC_POLICY_CONTENT ;

////////////////////////////////////////////////////////////////////////////
//  TKE Phase 1 Transform
////////////////////////////////////////////////////////////////////////////
typedef struct sIPSEC_TKE_PHASE1
{
    unsigned int    eEncryptAlg ;
    unsigned int    eHashAlg ;
    unsigned int    eAuthMethod ;
    unsigned int    iDH_Group ;
    unsigned long   lLifeKbytes ;
    unsigned long   lLifeSeconds ;

} tIPSEC_TKE_PHASE1 ;

////////////////////////////////////////////////////////////////////////////
//  IP Security binary policy data file header format
////////////////////////////////////////////////////////////////////////////

#define IPSEC_SANE_HEADER        (0xA345) 
#define IPSEC_FILE_VERSION       (1)
typedef struct sIPSEC_FILE_HEADER 
{
    unsigned int  Sanity_Check ;
    unsigned int  File_Version ;
    unsigned int  SelectorCount ;
    unsigned int  ContentCount ;
    unsigned int  PairCount ;
    unsigned int  PresharedKeyCount ;
} 
tIPSEC_FILE_HEADER ;

////////////////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////////////////
#define USE_OUR_IP          (0x80)      // May OR into Family.
#define HAVE_DOMAIN_NAME    (0x40)      // BeckIPSec may OR into Family.
    // BeckIPSec tool uses the 0x40 bit in tIPSEC_TUNNEL.FamilyLocal or
    // tIPSEC_TUNNEL.FamilyRemote bytes to indicate that the respective
    // IP address was entered by domain name and this domain name
    // is appended to the end of the policy file in a string bucket.
    // The system ignores this 0x40 bit.

#define IPSEC_WILD_PORT      (0)        // For tIPSEC_ADDR.Port
#define IPSEC_WILD_PROTOCOL  (0)        // For IPSEC_POLICY_SELECTOR.Protocol
    // Following apply to the 'IPSEC_POLICY_SELECTOR.Usage' enumerator:
#define IPSEC_WILD_ADDR    (0)     // Useful for setting a broad BYPASS policy.
#define IPSEC_SINGLE_ADDR  (1)     // A specific IP address is provided.
#define IPSEC_RANGE_ADDR   (2)     // Range from IpAddr1 to IpAddr2, inclusive.
#define IPSEC_NETMASK_ADDR (3)     // IpAddr2 contains a netmask to be applied
                                   //   over IpAddr1 for compare.

////////////////////////////////////////////////////////////////////////////
// Following two bits may be OR'ed into the tIPSEC_ADDR.Usage BYTE by the
// BeckIPSec policy editor tool.  These flags indicate that a domain name 
// for the respective entry is stored in the option string bucket at the
// end of the policy file.  The system ignores these bits.  You can
// also ignore these bits.  They are specified here only to fully document
// what the BeckIPSec tool is doing.
#define IPSEC_IP1_DOMAIN  (0x40)    // Domain name associated with IpAddr1
#define IPSEC_IP2_DOMAIN  (0x80)    // Domain name associated with IpAddr2

////////////////////////////////////////////////////////////////////////
// Legal values for .bDirection in tIPSEC_POLICY_PAIR
////////////////////////////////////////////////////////////////////////
#define IPSEC_INBOUND           0x01 
#define IPSEC_OUTBOUND          0x02
#define IPSEC_BOTH_DIRECTION    0x03 

////////////////////////////////////////////////////////////////////////
// Bit definitions for .RuleFlags in tIPSEC_POLICY_CONTENT
////////////////////////////////////////////////////////////////////////
#define     IPSEC_FLAG_TUNNEL           (0x0001)
#define     IPSEC_FLAG_TRANSPORT        (0x0002)
#define     IPSEC_FLAG_AH               (0x0004)
#define     IPSEC_FLAG_ESP              (0x0008)
#define     IPSEC_FLAG_RIP_PACKET       (0x0010)
#define     IPSEC_FLAG_RPT_PACKET       (0x0020)
#define     IPSEC_FLAG_LIP_PACKET       (0x0040)
#define     IPSEC_FLAG_LPT_PACKET       (0x0080)
#define     IPSEC_FLAG_PROTO_PACKET     (0x0100)
#define     IPSEC_FLAG_BYPASS           (0x0200)
#define     IPSEC_FLAG_DISCARD          (0x0400)

////////////////////////////////////////////////////////////////////////
// Authentication Header algorithms
////////////////////////////////////////////////////////////////////////
#define    IPSEC_AALG_NULL              0
#define    IPSEC_AALG_MD5HMAC           1 
#define    IPSEC_AALG_SHA1HMAC          2 
#define    IPSEC_AALG_SHA256HMAC        5 

////////////////////////////////////////////////////////////////////////
// ESP algorithms
////////////////////////////////////////////////////////////////////////
#define    IPSEC_EALG_NULL              0
#define    IPSEC_EALG_DESCBC            8 
#define    IPSEC_EALG_3DESCBC           9
#define    IPSEC_EALG_BLOWFISHCBC      14
//#define    IPSEC_EALG_ARCFOUR           10   // NOT SUPPORTED!
#define    IPSEC_KEY_192BIT       0x40          // Key length modifier
#define    IPSEC_KEY_256BIT       0x80
#define    IPSEC_EALG_AESCBC            16      // Default, 128 bit key
#define    IPSEC_EALG_AESCBC_192 (IPSEC_EALG_AESCBC | IPSEC_KEY_192BIT)
#define    IPSEC_EALG_AESCBC_256 (IPSEC_EALG_AESCBC | IPSEC_KEY_256BIT)

////////////////////////////////////////////////////////////////////////
// IKE Phase1 Encryption methods 
//     (eEncryptAlg member of tIPSEC_TKE_PHASE1)
////////////////////////////////////////////////////////////////////////
#define IPSEC_IKE_DES_CBC           1
#define IPSEC_IKE_BLOWFISH_CBC      3
#define IPSEC_IKE_3DES_CBC          5
#define IPSEC_IKE_AES_CBC           7       // RFC 3602

////////////////////////////////////////////////////////////////////////
// IKE Phase1 Hash methods 
//     (eHashAlg member of tIPSEC_TKE_PHASE1)
////////////////////////////////////////////////////////////////////////
#define IPSEC_IKE_MD5               1
#define IPSEC_IKE_SHA1              2

////////////////////////////////////////////////////////////////////////
// IKE Phase1 Authentication methods 
//     (eAuthMethod member of tIPSEC_TKE_PHASE1)
////////////////////////////////////////////////////////////////////////
#define IPSEC_IKE_PRESHARED_KEY     1
//#define IPSEC_IKE_DSS_SIG         2   (Not available)
#define IPSEC_IKE_RSA_SIG           3

////////////////////////////////////////////////////////////////////////
// IP Security states, returned from IPsec_Start()
////////////////////////////////////////////////////////////////////////

#define  IPSEC_OFF              (0)
#define  IPSEC_FAILED           (1)
#define  IPSEC_READY            (2)

////////////////////////////////////////////////////////////////////////
// IP Security / IKE Options for IPsec_Set_Option()
////////////////////////////////////////////////////////////////////////

#define IPSEC_OPT_ANTIREPLAY               1
#define IPSEC_OPT_PFSKEY                   2
#define IPSEC_OPT_AGGRESS                  3
#define IPSEC_OPT_AGGRESSDHGROUP           4
#define IPSEC_OPT_INITCONTACT              5
#define IPSEC_OPT_ICMPBYPASS               6
#define IPSEC_OPT_ICMPSRCCHKBYPASS         7
#define IPSEC_OPT_ICMP6NDMLDBYPASS         8
#define IPSEC_OPT_NESTIKE_BYPASS           9
#define IPSEC_OPT_DFBIT                    10

    // Values to use with IPSEC_OPT_DFBIT option:
#define IPSEC_VAL_DFBIT_CLEAR  0
#define IPSEC_VAL_DFBIT_SET    1
#define IPSEC_VAL_DFBIT_COPY   2

/******************************************************************************
* Prototypes of functions
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

int  _cdecl IPsec_Add_Policy (const tIPSEC_POLICY_PAIR     *pairs,
                              const tIPSEC_POLICY_SELECTOR *selectors,
                              const tIPSEC_POLICY_CONTENT  *content,
                              int  npair) ;

int  _cdecl IPsec_Clear_Policy (void) ;
int  _cdecl IPsec_Add_Preshared_Key (const char *remote_ip, 
                              const char *preshared_key) ;

int  _cdecl IPsec_Remove_Preshared_Key (const char *remote_ip) ;
void _cdecl IPsec_Clear_Preshared_Keys (void) ;
int  _cdecl IPsec_Start (void) ;
int  _cdecl IPsec_Status (int *error_code) ;
int  _cdecl IPsec_IKE_Status (void) ;
int  _cdecl IPsec_Set_Option (unsigned int option, unsigned int value) ;
int  _cdecl IPsec_IKE_Phase1_Set (int index, const tIPSEC_TKE_PHASE1 *param) ;
int  _cdecl IPsec_IKE_Phase1_Delete (int index) ;
int  _cdecl IPsec_Restore_Policy (const char *filename) ;

int  _cdecl IPsec_Store_Policy ( 
                     const char                   *file_name,
                     const tIPSEC_POLICY_SELECTOR *selectors,
                     unsigned int                  selector_count,
                     const tIPSEC_POLICY_CONTENT  *contents,
                     unsigned int                  content_count,
                     const tIPSEC_POLICY_PAIR     *pairs,
                     unsigned int                  pair_count,
                     const char           * const *preshared_keys,
                     unsigned int                  preshared_key_count) ;

#ifdef __cplusplus
}
#endif  


#endif  // _IPSEC_H_

// End of file

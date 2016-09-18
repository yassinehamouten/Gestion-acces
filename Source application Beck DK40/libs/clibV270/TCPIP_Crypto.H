/****************************************************************************
* (C) 1999-2010 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : TCPIP_Crypto.H
* Function       : prototypes, constants for TCP/IP cyptographic API functions
* ---------------------------------------------------------------------------

$Header: $

****************************************************************************/

#ifndef __TCPIP_CYRPTO_H__
#define __TCPIP_CYRPTO_H__

/*****************************************************************************/
//CRYPT structures
/*****************************************************************************/

/* Data structure for MD5 (Message-Digest) computation */
typedef struct tag_crypt_md5_context
{
/* number of _bits_ handled mod 2^64 */
  unsigned long i[2];
/* scratch buffer */
  unsigned long buf[4];
/* input buffer */
  unsigned char in[64];
/* actual digest after MD5Final call */
  unsigned char digest[16];
} Crypt_MD5_Context;
typedef Crypt_MD5_Context far * Crypt_MD5_ContextPtr;

/* Data structure for SHA1 computation */
typedef struct tag_crypt_sha1_context
{
/* Message digest */
  unsigned long shaDigest[5];
/* 64-bit bit count */
  unsigned long shaCountLo;
  unsigned long shaCountHi;
/* SHA data buffer */
  unsigned long shaData[16];
/* actual digest after SHA1Final call */
  unsigned char digest[20];
} Crypt_SHA1_Context;
typedef Crypt_SHA1_Context far * Crypt_SHA1_ContextPtr;

typedef struct tag_crypt_sha256_context
{
    unsigned long internalUse[ 37  ];
    unsigned char digest[32];       // Crypt_SHA256_Final() result
} Crypt_SHA256_Context;
typedef Crypt_SHA256_Context far * Crypt_SHA256_ContextPtr;

/* Data structure for cipher key */
typedef struct tag_crypt_GenericKey
{
    const unsigned char far *  keyDataPtr;
    int                  keyRounds;  // not used for AES
    unsigned int         keyBits;
} Crypt_GenericKey;
typedef Crypt_GenericKey far * Crypt_GenericKeyPtr;

/* Data structure for AES computation */
typedef struct tag_crypt_aes_context
{
    unsigned long far rd_key[60];
    int rounds;
} Crypt_AES_Context;
typedef Crypt_AES_Context far * Crypt_AES_ContextPtr;


/*******************************************************************************
* Crypt_BigNumS
****************************************************************************/
typedef struct Crypt_BigNumT 
{
    unsigned short      bnDigitCnt ;
    unsigned short      bnSign ;
    unsigned int far   *bnDataPtr ;
} Crypt_BigNumS ;


/*******************************************************************************
* Crypt_BigNumConstS
****************************************************************************/
typedef struct Crypt_BigNumConstT 
{
    unsigned short          bnDigitCnt ;
    unsigned short          bnSign ;
    const unsigned int far *bnDataPtr ;
} Crypt_BigNumConstS ;


/*******************************************************************************
* BlowfishKeyS
****************************************************************************/
typedef struct Crypt_BlowfishKeyT 
{
    /*! For internal use only  */
    unsigned long p[18];
    /*! For internal use only  */
    unsigned long s[4*256];

} Crypt_BlowfishKeyS ;


/*******************************************************************************
* Crypt_DesKeyScheduleS
****************************************************************************/
typedef struct Crypt_DesKeyScheduleT
{
    /*! For internal use only.  This array holds two 28 bit subkey halfs
     * for each of the DES cipher's 16 rounds.
     */
    unsigned long  subkey[32] ;
} Crypt_DesKeyScheduleS ;

/*******************************************************************************
* Crypt_DesKeyScheduleS
****************************************************************************/
typedef struct Crypt_3DesKeyScheduleT
{
    /*! For internal use only.  The 3DES cipher uses 3 passes through
     *  the DES cipher.  This structure holds the subkey schedule
     *  for each of these passes.
     */
    Crypt_DesKeyScheduleS  pass[3] ;
} Crypt_3DesKeyScheduleS ;


/*******************************************************************************
* Crypt_RSA_Hash_Type
*
* Enum for specifying which hash algorithm should be used during RSA computation.
*******************************************************************************/
typedef enum
{
  Crypt_RSA_SHA1,
  Crypt_RSA_SHA256
} Crypt_RSA_Hash_Type;



/*************************************************************************/
//prototypes
/*************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif


// CRYPT functions

    ////////////////////////////////////////////////////
    //      3DES
    ////////////////////////////////////////////////////
int _cdecl far Crypt_3DES_Decrypt ( const Crypt_3DesKeyScheduleS far *schedule,
                                    const void                   far *in, 
                                          void                   far *out ) ;

int _cdecl far Crypt_3DES_Encrypt ( const Crypt_3DesKeyScheduleS far *schedule, 
                                    const void                   far *in, 
                                          void                   far *out ) ;
int _cdecl far Crypt_3DES_MakeKey ( const unsigned char     far * key,
                                    Crypt_3DesKeyScheduleS  far * schedule) ;

    ////////////////////////////////////////////////////
    //      AES
    ////////////////////////////////////////////////////
#ifdef TCPIP_DYN_LINK
    // Dynamically linked versions
int _cdecl far Crypt_AES_Decrypt_Dyn (const Crypt_AES_Context far *aescontext,
                                      const void far * in,
                                            void far * out);
int _cdecl far Crypt_AES_Encrypt_Dyn (const Crypt_AES_Context far *aescontext,
                                      const void far * in,
                                            void far * out);
int _cdecl far Crypt_AES_MakeDecryptKey_Dyn (const Crypt_GenericKey far *key,
                                             Crypt_AES_Context far *aescontext);

int _cdecl far Crypt_AES_MakeEncryptKey_Dyn (const Crypt_GenericKey far *key,
                                             Crypt_AES_Context far *aescontext);

    // Remap legacy fuunctions to their dynamically linked counterparts.
#define Crypt_AES_Decrypt           Crypt_AES_Decrypt_Dyn
#define Crypt_AES_Encrypt           Crypt_AES_Encrypt_Dyn
#define Crypt_AES_MakeDecryptKey    Crypt_AES_MakeDecryptKey_Dyn
#define Crypt_AES_MakeEncryptKey    Crypt_AES_MakeEncryptKey_Dyn

#else   // TCPIP_DYN_LINK
    // Legacy connections
int _cdecl Crypt_AES_Decrypt (const Crypt_AES_Context *aescontext,
                              const void far * in,
                                    void far * out);
int _cdecl Crypt_AES_Encrypt (const Crypt_AES_Context *aescontext,
                              const void far * in,
                                    void far * out);
int _cdecl Crypt_AES_MakeDecryptKey (const Crypt_GenericKey *key,
                                     Crypt_AES_ContextPtr aescontext);

int _cdecl Crypt_AES_MakeEncryptKey (const Crypt_GenericKey *key,
                                     Crypt_AES_ContextPtr aescontext);
#endif  // TCPIP_DYN_LINK

    ////////////////////////////////////////////////////
    //      Blowfish
    ////////////////////////////////////////////////////
int _cdecl far Crypt_Blowfish_Decrypt ( const Crypt_BlowfishKeyS far *subkeys, 
                                        const void               far *in, 
                                              void               far *out ) ;
int _cdecl far Crypt_Blowfish_Encrypt ( const Crypt_BlowfishKeyS far *subkeys, 
                                        const void               far *in, 
                                              void               far *out ) ;
int _cdecl far Crypt_Blowfish_MakeKey ( Crypt_BlowfishKeyS  far * subkeys,
                                        int                       len,
                                        const unsigned char far * key) ;

    ////////////////////////////////////////////////////
    //      Big Number Support
    ////////////////////////////////////////////////////
int _cdecl far Crypt_BN_Div( const Crypt_BigNumConstS far *dividend, 
                             const Crypt_BigNumConstS far *divisor,
                                   Crypt_BigNumS      far *quotient,
                                   Crypt_BigNumS      far *remainder) ;

int _cdecl far Crypt_BN_Mod_Exp(       Crypt_BigNumS       far  *result ,
                                 const Crypt_BigNumConstS  far *a,
                                 const Crypt_BigNumConstS  far *power,
                                 const Crypt_BigNumConstS  far *modulo) ;
int _cdecl far Crypt_BN_Mod_Inverse(      Crypt_BigNumS      far *result,
                                    const Crypt_BigNumConstS far *a, 
                                    const Crypt_BigNumConstS far *b) ;
int _cdecl far Crypt_BN_Mod_Mul(       Crypt_BigNumS      far *result,
                                 const Crypt_BigNumConstS far *a, 
                                 const Crypt_BigNumConstS far *b,
                                 const Crypt_BigNumConstS far *m) ;
int _cdecl far Crypt_BN_Mul(       Crypt_BigNumS      far *result,
                             const Crypt_BigNumConstS far *a, 
                             const Crypt_BigNumConstS far *b) ;

    ////////////////////////////////////////////////////
    //      DES
    ////////////////////////////////////////////////////
int _cdecl far Crypt_DES_Decrypt ( const Crypt_DesKeyScheduleS far *schedule, 
                                   const void                  far *in, 
                                         void                  far *out ) ;
int _cdecl far Crypt_DES_Encrypt ( const Crypt_DesKeyScheduleS far *schedule,
                                   const void                  far *in, 
                                         void                  far *out ) ;
int _cdecl far Crypt_DES_MakeKey ( const unsigned char    far * key,
                                   Crypt_DesKeyScheduleS  far * schedule) ;


    ////////////////////////////////////////////////////
    //      MD5
    ////////////////////////////////////////////////////
#ifdef TCPIP_DYN_LINK
    // Dynamically linked versions
int _cdecl far Crypt_MD5_Init_Dyn  ( Crypt_MD5_ContextPtr md5context);
int _cdecl far Crypt_MD5_Update_Dyn ( Crypt_MD5_ContextPtr md5context,
                                      const void far *inBuffer,
                                      unsigned int length);
int _cdecl far Crypt_MD5_Final_Dyn  ( Crypt_MD5_ContextPtr md5context);

    // Remap legacy fuunctions to their dynamically linked counterparts.
#define Crypt_MD5_Init    Crypt_MD5_Init_Dyn
#define Crypt_MD5_Update  Crypt_MD5_Update_Dyn
#define Crypt_MD5_Final   Crypt_MD5_Final_Dyn


#else   // TCPIP_DYN_LINK
    // Legacy connections
int _cdecl Crypt_MD5_Init   (Crypt_MD5_ContextPtr md5context);
int _cdecl Crypt_MD5_Update (Crypt_MD5_ContextPtr md5context,
                             const void far *inBuffer,
                             unsigned int length);
int _cdecl Crypt_MD5_Final  (Crypt_MD5_ContextPtr md5context);

#endif  // TCPIP_DYN_LINK

    ////////////////////////////////////////////////////
    //      SHA1
    ////////////////////////////////////////////////////
#ifdef TCPIP_DYN_LINK
    // Dynamically linked versions
int _cdecl far Crypt_SHA1_Init_Dyn   (Crypt_SHA1_ContextPtr sha1context) ;
int _cdecl far Crypt_SHA1_Update_Dyn (Crypt_SHA1_ContextPtr sha1context,
                                      const void far *inBuffer,
                                      unsigned int length) ;
int _cdecl far Crypt_SHA1_Final_Dyn  (Crypt_SHA1_ContextPtr sha1context) ;

    // Remap legacy fuunctions to their dynamically linked counterparts.
#define Crypt_SHA1_Init    Crypt_SHA1_Init_Dyn
#define Crypt_SHA1_Update  Crypt_SHA1_Update_Dyn
#define Crypt_SHA1_Final   Crypt_SHA1_Final_Dyn


#else   // TCPIP_DYN_LINK
    // Legacy connections
int _cdecl Crypt_SHA1_Init   (Crypt_SHA1_ContextPtr sha1context);
int _cdecl Crypt_SHA1_Update (Crypt_SHA1_ContextPtr sha1context,
                              const void far *inBuffer,
                              unsigned int length);
int _cdecl Crypt_SHA1_Final  (Crypt_SHA1_ContextPtr sha1context);

#endif  // TCPIP_DYN_LINK

    ////////////////////////////////////////////////////
    //      SHA256
    ////////////////////////////////////////////////////
int _cdecl huge Crypt_SHA256_Init   ( Crypt_SHA256_ContextPtr sha256context);
int _cdecl huge Crypt_SHA256_Update ( Crypt_SHA256_ContextPtr sha256context,
                                      const void far *inBuffer,
                                      unsigned int length);
int _cdecl huge  Crypt_SHA256_Final ( Crypt_SHA256_ContextPtr sha256context);

    ////////////////////////////////////////////////////
    //      RSA
    ////////////////////////////////////////////////////
int _cdecl huge  Crypt_RSA_Sign(const char   far *keyBuffer, 
                                const void   far *hash, 
                               Crypt_RSA_Hash_Type hashType,
                                void         far *sign, 
                                unsigned int      signLength);

int _cdecl huge  Crypt_RSA_Verify(const char  far *keyBuffer, 
                                  const void  far *hash, 
                               Crypt_RSA_Hash_Type hashType,
                                  const void  far *sign, 
                                  unsigned int     signLength);

int _cdecl huge  Crypt_RSA_GetKeySize(const char *keyBuffer);

    ////////////////////////////////////////////////////
    //      Random Numbers
    ////////////////////////////////////////////////////
int _cdecl far Crypt_Random_Bytes ( unsigned char far *buf, int num );


#ifdef __cplusplus
}
#endif


/*************************************************************************/
#endif /* __TCPIP_CYRPTO_H__*/
/*************************************************************************/
//end TCPIP_Crypto.h
/*************************************************************************/

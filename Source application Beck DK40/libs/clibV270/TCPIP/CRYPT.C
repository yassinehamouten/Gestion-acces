/****************************************************************************
* (C) 1999-2013 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : CRYPT.C
* Function       : TCPIP API cryptograhpic functions
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


/***

 @doc DOC_INDEX
 ---------------------------------------------------------------
 TCP/IP API Table of Contents
 ---------------------------------------------------------------
 @clibLinkIdx  <tab><cfont>#include <InBraces TCPIP\.H><efont><nl>
  <tab><tab><tab><tab><tab><arial>which includes<ariale> <cfont>
 <InBraces TCPIP_Crypto\.H><efont> |
    <tab><linkto>#Hash<linkmid>Hash<linktail><tab>
    <tab><linkto>#Cipher<linkmid>Cipher<linktail><tab>
    <tab><linkto>#Number<linkmid>Big Number<linktail><tab>
    <tab><linkto>#Other<linkmid>Other<linktail><tab>
    |

  <nl>
  <bold>Related<bolde>:
  <ul>
      <li> <linkto>../../crystruc.htm<linkmid>Data Structures<linktail><nl>
      <li> Cipher API <linkto>../../cryptTbl.htm<linkmid>Timing Measurements<linktail>  <nl>
      <li> TCP/IP C-Library <linkto>lib_index.htm<linkmid>Main List<linktail>  <nl>
  <ule>

 @libcat1  Hash |  tcpDFA | Crypt_MD5_Init     | <nl>Init MD5 checksum generator | <tab><tab>--- MD5 Functions ---<nl>
 @libcat1  Hash |  tcpDFB | Crypt_MD5_Update   | Update MD5 hash |
 @libcat1  Hash |  tcpDFC | Crypt_MD5_Final    | Finalize MD5 hash |
 @libcat1  Hash |  tcpDFD | Crypt_SHA1_Init    | <nl><nl>Init SHA1 checksum generator | <nl><tab><tab>--- SHA1 Functions ---<nl>
 @libcat1  Hash |  tcpDFE | Crypt_SHA1_Update  | Update SHA1 hash |
 @libcat1  Hash |  tcpDFF | Crypt_SHA1_Final   | Finalize SHA1 hash |
 @libcat1  Hash |  cry43  | Crypt_SHA256_Init   | <nl><nl>Init SHA256 checksum generator | <nl><tab><tab>--- SHA256 Functions ---<nl>
 @libcat1  Hash |  cry44  | Crypt_SHA256_Update | Update SHA256 hash |
 @libcat1  Hash |  cry45  | Crypt_SHA256_Final  | Finalize SHA256 hash |


 @libcat2  Cipher | tcpE04 | Crypt_AES_Decrypt  | <nl>Decrypt AES message |<tab><tab>--- AES Functions ---<nl>
 @libcat2  Cipher | tcpE03 | Crypt_AES_Encrypt  | Encrypt AES message |
 @libcat2  Cipher | tcpE02 | Crypt_AES_MakeDecryptKey | Make AES decrypt key |
 @libcat2  Cipher | tcpE01 | Crypt_AES_MakeEncryptKey | Make AES encrypt key |

 @libcat2  Cipher | cry07 | Crypt_Blowfish_Decrypt | <nl><nl>Decrypt BLOWFISH message | <nl><tab><tab>--- BLOWFISH Functions ---<nl>
 @libcat2  Cipher | cry08 | Crypt_Blowfish_Encrypt | Encrypt BLOWFISH message |
 @libcat2  Cipher | cry09 | Crypt_Blowfish_MakeKey  | Make BLOWFISH key |

 @libcat2  Cipher | cry15 | Crypt_DES_Decrypt | <nl><nl>Decrypt DES message | <nl><tab><tab>--- DES Functions ---<nl>
 @libcat2  Cipher | cry16 | Crypt_DES_Encrypt | Encrypt DES message |
 @libcat2  Cipher | cry17 | Crypt_DES_MakeKey  | Make DES key |

 @libcat2  Cipher | cry00 | Crypt_3DES_Decrypt | <nl><nl>Decrypt 3DES message | <nl><tab><tab>--- 3DES Functions ---<nl>
 @libcat2  Cipher | cry01 | Crypt_3DES_Enrypt | Encrypt 3DES message |
 @libcat2  Cipher | cry02 | Crypt_3DES_MakeKey  | Make 3DES key |

 @libcat2  Cipher | cry46 | Crypt_RSA_Sign | <nl><nl>RSA Signature | <nl><tab><tab>--- RSA Sign/Verify ---<nl>
 @libcat2  Cipher | cry47 | Crypt_RSA_Verify | RSA Verify|
 @libcat2  Cipher | cry48 | Crypt_RSA_GetKeySize | Check RSA key size |

 @libcat3y  Big | Number | cry10 | Crypt_BN_Div | Big number division |
 @libcat3y  Big | Number | cry11 | Crypt_BN_Mod_Exp | Big number modulo exponentiation |
 @libcat3y  Big | Number | cry12 | Crypt_BN_Mod_Inverse | Big number modulo inverse |
 @libcat3y  Big | Number | cry13 | Crypt_BN_Mod_Mul | Big number modulo multiply |
 @libcat3y  Big | Number | cry14 | Crypt_BN_Mul | Big number multiply |

 @libcat4  Other | cry24 | Crypt_Random_Bytes  | Get pseudo random numbers |

*/



/////////////////////////////////////////////////////////////////////////////////////////////////
//
//     CAUTION!!  -  Compilation switches are required by DOCLIST tool
//
//   Even though we have no code to compile for these dynamic linked API, we still must
//  place the "#ifdef _cry00_" like compilation switches around the documentation to assist
//  the DOCLIST tool.  The DOCLIST tool uses these compilation switch macro names like
//  _cry00_ to construct the corresponding HTM file "cry00.htm" to which it will link the
//  extracted Beck C-Lib procedure name, like Crypt_3DES_Decrypt() for this case below.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _cry00_
/*
@doc DOC_cry00_
 ----------------------------------------------------------------------------------
 3DES decryption
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_3DES_Decrypt | crypt_index.htm |
        Decrypt one cipher block of data using 3DES decryption method. |
        <cfont>int far Crypt_3DES_Decrypt (<nl>
          <tab><tab><tab> const Crypt_3DesKeyScheduleS far *schedule,<nl>
          <tab><tab><tab> const void                   far *in,<nl>
          <tab><tab><tab><tab><s2> void                   far *out ) ;<efont> |
 @parm  Crypt_3DesKeyScheduleS | schedule | Pointer to
        3DES 
        <linkto>../../crystruc.htm#Crypt_3DesKeyScheduleS<linkmid>subkey schedule<linktail>
        generated by
        <linkto>cry02.htm<linkmid>Crypt_3DES_MakeKey()<linktail>.
 @parm  void | in | Pointer to 8 byte cipher text to
        be decrypted
 @parm  void | out | Pointer to 8 byte buffer where the resulting
        decrypted clear text will be written by this API.
 @rdesc 0 constant (provisional error code)
 @comm 
    This API decrypts one 8 byte cipher block of data using the 3DES
    decryption method.<s2> It can be called repeatedly until your entire 
    message has been recovered.<s2> When your message is not an integral
    number of 8 byte blocks in length, then you will obtain on the final
    call the pad bytes that were appended to the original message at the
    encryption step.

    The 3DES cipher treats data as little endian long words.<s2> Any required 
    data endian handling is done inside this API, so the caller must not perform
    any such handling on their side.<s2>  (Since the <chiprtos> CPU is itself little
    endian, this note applies only for code which is to be ported to big
    endian Beck platforms.)

    The <cfont>in<efont> and <cfont>out<efont> parameters may reference the same location.

  Go <linkto>../../cryptTbl.htm<linkmid>here<linktail> for a summary of cipher method execution times.


 @Also  cry01.htm | Crypt_3DES_Encrypt |
        cry02.htm | Crypt_3DES_MakeKey  |
        cry15.htm | Crypt_DES_Decrypt
 @rtos  On the first call, this library function invokes a software
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>interrupt<linktail>
        which modifies the code at the calling site inside your application
        program.<s2> A direct FAR JMP into the <chiprtos>
        implementation for this function is installed so that on
        return and on any subsequent calls to this API this
        dynamic link  reaches the function's
        implementation directly.<nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 


#ifdef _cry01_
/*
@doc DOC_cry01_
 ----------------------------------------------------------------------------------
 3DES encryption
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_3DES_Encrypt | crypt_index.htm |
    Encrypt one cipher block of data using 3DES encryption method. |
        <cfont>int far Crypt_3DES_Encrypt (<nl>
          <tab><tab><tab> const Crypt_3DesKeyScheduleS far *schedule,<nl>
          <tab><tab><tab> const void                   far *in,<nl>
          <tab><tab><tab><tab><s2> void                   far *out ) ;<efont> |
 @parm  Crypt_3DesKeyScheduleS | schedule | Pointer to
        3DES 
        <linkto>../../crystruc.htm#Crypt_3DesKeyScheduleS<linkmid>subkey schedule<linktail>
        generated by
        <linkto>cry02.htm<linkmid>Crypt_3DES_MakeKey()<linktail>.
 @parm  void | in |  Pointer to 8 byte clear text to
        be encrypted
 @parm  void | out | Pointer to 8 byte buffer where the resulting
        decrypted clear text will be written by this API.
 @rdesc 0 constant  (provisional error code)
 @comm  
    This API encrypts one 8 byte cipher block of data using the 3DES encryption
    method.<s2> It can be called repeatedly until your entire message has
    been encrypted.<s2> When your message is not an integral number of 8 byte
    blocks in length, then you must pad the final block with some pattern
    agreed upon with your decryption side.

    The 3DES cipher 3DES treats data as little endian long words.<s2> Any required 
    data endian handling is done inside this API, so the caller must not perform
    any such handling on their side.<s2>  (Since the <chiprtos> CPU is itself little
    endian, this note applies only for code which is to be ported to big
    endian Beck platforms.)

  The <cfont>in<efont> and <cfont>out<efont> parameters may reference the same location.

  Go <linkto>../../cryptTbl.htm<linkmid>here<linktail> for a summary of cipher method execution times.

 @Also  cry00.htm | Crypt_3DES_Decrypt |
        cry02.htm | Crypt_3DES_MakeKey  |
        cry16.htm | Crypt_DES_Encrypt
 @rtos  On the first call, this library function invokes a software
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>interrupt<linktail>
        which modifies the code at the calling site inside your application
        program.<s2> A direct FAR JMP into the <chiprtos>
        implementation for this function is installed so that on
        return and on any subsequent calls to this API this
        dynamic link  reaches the function's
        implementation directly.<nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 

#ifdef _cry02_
/*
@doc DOC_cry02_
 ----------------------------------------------------------------------------------
 3DES key generation
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_3DES_MakeKey | crypt_index.htm | 
     Generates a 3DES subkey schedule based on a supplied 24 byte key. |
        <cfont>int far Crypt_3DES_MakeKey (<nl>
          <tab><tab><tab> const unsigned char     far * key,<nl>
          <tab><tab><tab> Crypt_3DesKeyScheduleS  far * schedule ) ;<efont> |
 @parm  char | key | [in]<s2> Secret 24 random byte key to be
    used to generate the subkey schedule.  
 @parm  void | schedule | [out]<s2>  Pointer to
        <linkto>../../crystruc.htm#Crypt_3DesKeyScheduleS<linkmid>Crypt_3DesKeyScheduleS<linktail>
        structure to be initialized by this API.<s2> The subkey schedule
        is written here.
 @rdesc 0 success:<nl>
        else <linkto>../../iperrlst.htm<linkmid>error code<linktail>.
 @comm  Each byte of the 24 byte key contains 7 key bits plus an odd parity
    bit (LS bit) for a total key size of 168 bits.<s2> The parity bits are
    not tested by this API.<s2> (If desired, this key byte odd parity check
    could be done on the user side.)<nl>
    <nl>
    The key is tested to assure that it is not cryptographically too weak.<s2> This
    test fails if the first 8 bytes match the second 8 bytes, or if the second group
    of 8 bytes match the third group of 8 bytes.<s2> On failure, no subkey schedule 
    is generated and <linkto>../../iperrlst.htm<linkmid>error code<linktail>
     222 is returned.<s2> (Note: If the odd parity 
    bits are the only difference in the 8 byte sections of the key, then this quick
    check for key strength done by this API will have not accomplished its purpose
    and a weak key could be accepted here as ok without any error code resulting.)<nl>
    <nl>
    No presetting of the memory at <cfont>schedule<efont> is required by
    the caller.<s2> This API fully initializes this block of memory with
    a new 3DES subkey schedule based on the provided key.<nl>

   The 3DES cipher encryption/decryption speed improves slightly (~3%) when the
    <linkto>../../crystruc.htm#Crypt_3DesKeyScheduleS<linkmid>Crypt_3DesKeyScheduleS<linktail>
    object is allocated from the system's 
    <linkto>../HELPER/helper09.htm<linkmid>fast RAM<linktail> heap area. Go
    <linkto>../../cryptTbl.htm<linkmid>here<linktail> for a summary of
    cipher method execution times.

 @Also  cry00.htm | Crypt_3DES_Decrypt |
        cry01.htm | Crypt_3DES_Encrypt  |
        cry17.htm | Crypt_DES_MakeKey
 @rtos  On the first call, this library function invokes a software
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>interrupt<linktail>
        which modifies the code at the calling site inside your application
        program.<s2> A direct FAR JMP into the <chiprtos>
        implementation for this function is installed so that on
        return and on any subsequent calls to this API this
        dynamic link  reaches the function's
        implementation directly.<nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 


#ifdef _cry07_
/*
@doc DOC_cry07_
 ----------------------------------------------------------------------------------
 BLOWFISH decryption
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_Blowfish_Decrypt | crypt_index.htm | 
    Decrypt one cipher block of data using BLOWFISH decryption method. |
        <cfont>int far Crypt_Blowfish_Decrypt (<nl>
          <tab><tab><tab> const Crypt_BlowfishKeyS far *subkeys,<nl>
          <tab><tab><tab> const void                   far *in,<nl>
          <tab><tab><tab><tab><s2> void                   far *out ) ;<efont> |
 @parm  void | subkeys | Pointer to BLOWFISH 
        <linkto>../../crystruc.htm#Crypt_BlowfishKeyS<linkmid>subkey schedule<linktail>
        generated by
        <linkto>cry09.htm<linkmid>Crypt_Blowfish_MakeKey()<linktail>.
 @parm  void | in |  Pointer to 8 byte clear text to
        be encrypted
 @parm  void | out |  Pointer to 8 byte buffer where the resulting
        decrypted clear text will be written by this API.
 @rdesc 0 constant  (provisional error code)
 @comm  This API uses the BLOWFISH algorithm to convert one 8 byte cipher block of
    encrypted data back to plain text.<s2> It can be called repeatedly until your
    entire message has been recovered.<s2> When your message is not an integral
    number of 8 byte blocks in length, then you will obtain on the final call the
    pad bytes that were appended to the original message at the encryption step.

    This implementation of BLOWFISH uses 16 rounds.

        Blowfish treats data as big endian ("network byte order") long words.<s2>
        Any required data endian handling is done inside this API, so the caller
        must not perform any such endian swapping on their side.

  The <cfont>in<efont> and <cfont>out<efont> parameters may reference the same location.

  Go <linkto>../../cryptTbl.htm<linkmid>here<linktail> for a summary of
  cipher method execution times.

 @Also  cry08.htm | Crypt_Blowfish_Encrypt |
        cry09.htm | Crypt_Blowfish_MakeKey  |
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
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 

#ifdef _cry08_
/*
@doc DOC_cry08_
 ----------------------------------------------------------------------------------
 BLOWFISH encryption
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_Blowfish_Encrypt | crypt_index.htm |
    Encrypt one cipher block of data using BLOWFISH encryption method. |
        <cfont>int far Crypt_Blowfish_Encrypt (<nl>
          <tab><tab><tab> const Crypt_BlowfishKeyS far *subkeys,<nl>
          <tab><tab><tab> const void                   far *in,<nl>
          <tab><tab><tab><tab><s2> void                   far *out ) ;<efont> |
 @parm  void | subkeys | [in]<s2> Pointer to
        BLOWFISH 
        <linkto>../../crystruc.htm#Crypt_BlowfishKeyS<linkmid>subkey schedule<linktail>
        generated by
        <linkto>cry09.htm<linkmid>Crypt_Blowfish_MakeKey()<linktail>.
 @parm  void | in | [in]<s2> Pointer to 8 byte clear text to
        be encrypted
 @parm  void | out | [out]<s2> Pointer to 8 byte buffer where the resulting
        decrypted clear text will be written by this API.
 @rdesc 0 constant (provisional error code)
 @comm   This API encrypts one 8 byte cipher block of data using the BLOWFISH
    encryption method.<s2> It can be called repeatedly until your entire
    message has been encrypted.<s2> When your message is not an integral 
    number of 8 byte blocks in length, then you must pad the final block
    with some pattern agreed upon with your decryption side.
        
    This implementation of BLOWFISH uses 16 rounds.

    Blowfish treats data as big endian ("network byte order") long words.<s2>
        Any required data endian handling is done inside this API, so the caller
        must not perform any such endian swapping on their side.<nl> 
        <nl>
    The <cfont>in<efont> and <cfont>out<efont> parameters may reference the same location.

  Go <linkto>../../cryptTbl.htm<linkmid>here<linktail> for a summary of
  cipher method execution times.

 @Also  cry07.htm | Crypt_Blowfish_Decrypt |
        cry09.htm | Crypt_Blowfish_MakeKey  |
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
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 

#ifdef _cry09_
/*
@doc DOC_cry09_
 ----------------------------------------------------------------------------------
 BLOWFISH subkey generation
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_Blowfish_MakeKey | crypt_index.htm | 
        Generate the Blowfish subkey arrays. |
        <cfont>int far Crypt_Blowfish_MakeKey (<nl>
          <tab><tab><tab> Crypt_BlowfishKeyS  far * subkeys,<nl>
          <tab><tab><tab> int                       len,<nl>
          <tab><tab><tab> const unsigned char far * key ) ;<efont> |
 @parm  void | subkeys | <hangpara 20:20> [out]<s2>  Pointer to a 
        <linkto>../../crystruc.htm#Crypt_BlowfishKeyS<linkmid>Crypt_BlowfishKeyS<linktail>
        structure to be initialized by this API.<s2> The generated subkey arrays are
        written here.
 @parm  void | len | [in]<s2>  Number of bytes key material 
            provided at <cfont>key<efont>.
 @parm  void | key | [in]<s2>  This is the secret, typically 
        some random data.
 @rdesc 0 constant (provisional error code)
 @comm   This API performs some preprocessing on the key to generate the
    Blowfish subkey arrays based on the supplied key.<s2> These subkey
    arrays will then be used by the Blowfish encryption and decryption API.

  The amount of key material supplied may be any non-zero number of 
    bytes.<s2> Up to 72 bytes from these will be used for subkey 
    generation.<s2> Any additional key bytes will be ignored.

    No presetting of the memory at <cfont>subkeys<efont> is required by the
    caller.<s2> This API fully initializes this block of memory with the
    Blowfish subkeys based on the provided key material.<nl>
    
   The BLOWFISH cipher is the fastest cipher offered by the 
    <chiprtos> API.<nl> And the variable size key range allows
    a larger key (more bits) then any of the other API.<s2> The encryption/decryption
    speed can be significantly improved by allocating the 
    <linkto>../../crystruc.htm#Crypt_BlowfishKeyS<linkmid>Crypt_BlowfishKeyS<linktail>
    object from the system's <linkto>../HELPER/helper09.htm<linkmid>fast RAM<linktail>
    heap area.

  Go <linkto>../../cryptTbl.htm<linkmid>here<linktail> for a summary of
  cipher method execution times.

 @Also  cry07.htm | Crypt_Blowfish_Decrypt |
        cry08.htm | Crypt_Blowfish_Encrypt  |
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
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 


#ifdef _cry46_
/*
@doc DOC_cry46_
 ----------------------------------------------------------------------------------
 RSA Signature
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_RSA_Sign | crypt_index.htm | 
        Sign a SHA1 or SHA256 checksum with a RSA private key. |
        <cfont>int Crypt_RSA_Sign(<nl>
          <tab><tab><tab> const char far *keyBuffer,<nl>
          <tab><tab><tab> const void far *hash,<nl>
          <tab><tab><tab>
   <linkto>../../crystruc.htm#Crypt_RSA_Hash_Type<linkmid>Crypt_RSA_Hash_Type<linktail>
         hashType,<nl>
          <tab><tab><tab> void far *sign,<nl>
          <tab><tab><tab> unsigned int signBufLen) ;<efont> |
 @parm  void | keyBuffer | <hangpara 20:20> [in]<s2> Pointer to a NULL terminated 
     string containing the RSA private key in PEM format.
 @parm  void | hash | [in]<s2>  Pointer to data to be signed.<s2>  This must be
      either a 20 byte SHA1 checksum or a 32 byte SHA256 checksum.
 @parm  void | hashType | [in]<s2>  Type of hash being passed to the
     RSA signing computation.
 @parm  void | sign | [out]<s2>  Output buffer where the computed digital
      signature shall be stored.
 @parm  void | signBufLen | [in]<s2>  Length of the provided <code>sign<codee>
      output buffer in bytes.

 @rdesc 
    >0 : Size of the created signature in bytes (Success)<nl>
    -1 : NULL pointer passed in input arguments<nl>
    -3 : Error loading private key<nl>
    -4 : Provided buffer size for signature is too small<nl>
    -5 : Unknown hash type specified<nl>
    -6 : Error during RSA sign operation<nl>
 @comm   
     This function computes the digital signature of either a SHA1 or 
     SHA256 checksum, using the RSA private key provided by the user.<nl>
  <nl>
  Assure that the storage space in the buffer referenced by the <code>sign<codee>
      output parameter covers at least the number of bits in
      your RSA private key (this is not the size of the PEM data, but instead the
      strength of the underlying private key conveyed by this data).<s2> The
      maximum key size that this system supports is 4096 bits, or 512 bytes.
      So a 512 byte output buffer would always be safe on this system.<nl>
  
  For large key sizes, this computation can require some significant 
  amount of time.<s2> Here are some typical execution times to sign
  either a SHA1 or SHA256 checksum.<nl><nl>
      <tabl>
      <tr><th> Key size [bits]  <eth><th> Key size [bytes]  <eth><th> Execution time  <eth><etr>
      <tr><td> 1024 bits   <etd><td> 128 bytes  <etd><td> 1.07 seconds <etd>
      <tr><td> 2048 bits   <etd><td> 256 bytes  <etd><td> 7.60 seconds <etd>
      <tr><td> 4096 bits   <etd><td> 512 bytes  <etd><td> 57 seconds <etd>
      <etabl>
      <nl>


 @Also  cry47.htm | Crypt_RSA_Verify |
        cry48.htm | Crypt_RSA_GetKeySize | | 
 @rtos  On the first call, this library function invokes a software
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>interrupt<linktail>
        which modifies the code at the calling site inside your application
        program.<s2> A direct FAR JMP into the <chiprtos>
        implementation for this function is installed so that on
        return and on any subsequent calls to this API this
        dynamic link  reaches the function's
        implementation directly.<nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V2.01 | V2.01
 @target_clib V2.70
*/
#endif 

#ifdef _cry47_
/*
@doc DOC_cry47_
 ----------------------------------------------------------------------------------
 RSA Signature Verify
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_RSA_Verify | crypt_index.htm | 
        Verify either a SHA1 or SHA256 checksum with a RSA public key. |
        <cfont>int Crypt_RSA_Verify(<nl>
          <tab><tab><tab> const char far *keyBuffer,<nl>
          <tab><tab><tab> const void far *hash,<nl>
          <tab><tab><tab>
   <linkto>../../crystruc.htm#Crypt_RSA_Hash_Type<linkmid>Crypt_RSA_Hash_Type<linktail>
          hashType,<nl>
          <tab><tab><tab> const void far *sign,<nl>
          <tab><tab><tab> unsigned int signLength) ;<efont> |
 @parm  void | keyBuffer | <hangpara 20:20> [in]<s2>   Pointer to a NULL
    terminated string containing the RSA public key in PEM format.
 @parm  void | hash | [in]<s2>  Pointer to either SHA1 (20 bytes) or 
     SHA256 (32 bytes) checksum data to be verified.
 @parm  void | hashType | [in]<s2>  Type of hash being passed to the
     RSA verify computation.
 @parm  void | sign | [in]<s2>  Input buffer containing the digital signature
    to be verified.
 @parm  void | signLength | [in]<s2>  Length of the provided digital signature
    [bytes].
 @rdesc 
    0 : The signature was successfully verified<nl>
   -1 : NULL pointer passed in input arguments<nl>
   -3 : Error loading public key<nl>
   -5 : Unknown hash type specified<nl>
   -6 : Error during RSA operation<nl>
 @comm   
   This function verifies the digital signature of either a SHA1 or a 
   SHA256 checksum, using the RSA public key provided by the user.<nl>
   <nl>
   Here are some typical execution times to verify either a SHA1 or SHA256
   checksum.<nl><nl>
      <tabl>
      <tr><th> Key size [bits]  <eth><th> Key size [bytes]  <eth><th> Execution time  <eth><etr>
      <tr><td> 1024 bits   <etd><td> 128 bytes  <etd><td> 69 milliseconds <etd>
      <tr><td> 2048 bits   <etd><td> 256 bytes  <etd><td> 258 milliseconds <etd>
      <tr><td> 4096 bits   <etd><td> 512 bytes  <etd><td> 1.00 seconds <etd>
     <etabl>
      <nl>
  Note that verifying a signature executes much faster than a corresponding
  <linkto>cry46.htm<linkmid>signing<linktail> action.<nl>

 @Also  cry46.htm | Crypt_RSA_Sign |
        cry48.htm | Crypt_RSA_GetKeySize | | 
 @rtos  On the first call, this library function invokes a software
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>interrupt<linktail>
        which modifies the code at the calling site inside your application
        program.<s2> A direct FAR JMP into the <chiprtos>
        implementation for this function is installed so that on
        return and on any subsequent calls to this API this
        dynamic link  reaches the function's
        implementation directly.<nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V2.01 | V2.01
 @target_clib V2.70
*/
#endif 

#ifdef _cry48_
/*
@doc DOC_cry48_
 ----------------------------------------------------------------------------------
 Get RSA key size
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_RSA_GetKeySize | crypt_index.htm | 
        Get the size in bytes of a public or private RSA key. |
        <cfont>int Crypt_RSA_Verify(<nl>
          <tab><tab><tab> const char far *keyBuffer) ;<efont> |
 @parm  void | keyBuffer | <hangpara 20:20> [in]<s2>   Pointer to a NULL
    terminated string containing the RSA key in PEM format.
 @rdesc 
   Key size in bytes on success<nl>
  -1 : NULL pointer passed in input arguments<nl>
  -3 : Error loading private/public key<nl>
 @comm   
   This function determines the size in bytes of the RSA key provided
   by the user.<nl>

 @Also  cry46.htm | Crypt_RSA_Sign |
        cry47.htm | Crypt_RSA_Verify | | 
 @rtos  On the first call, this library function invokes a software
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>interrupt<linktail>
        which modifies the code at the calling site inside your application
        program.<s2> A direct FAR JMP into the <chiprtos>
        implementation for this function is installed so that on
        return and on any subsequent calls to this API this
        dynamic link  reaches the function's
        implementation directly.<nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V2.01 | V2.01
 @target_clib V2.70
*/
#endif 

#ifdef _cry10_
/*
@doc DOC_cry10_
 ----------------------------------------------------------------------------------
 Big Number DIV
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_BN_Div | crypt_index.htm | Big number division. | 
        <cfont>int far Crypt_BN_Div (<nl>
          <tab><tab><tab>  const Crypt_BigNumConstS far *dividend,<nl>
          <tab><tab><tab> const Crypt_BigNumConstS far *divisor,<nl>
          <tab><tab><tab><tab><s2> Crypt_BigNumS <tab> far *quotient,<nl>
          <tab><tab><tab><tab><s2> Crypt_BigNumS <tab>  far *remainder ) ;<efont> |
 @parm  void | dividend | [in]<s2>  Pointer to 
            big number to be divided (numerator).
 @parm  void | divisor | [in]<s2>   Pointer to big number
        to be used as demoninator.
 @parm  void | quotient | <hangpara 20:20> [out]<s2>  Resulting quotient will be
        written here.<s2> This output parameter is optional and may be
        set to NULL if the resulting quotient value is not needed.
 @parm  void | remainder | <hangpara 20:20> [out]<s2>  The remainder
        resulting from the divide operation will be written here.<s2> This
        output parameter is optional and may be set to NULL if the remainder
        is not needed.
 @rdesc error code:
    <ul>
        0 - Success (no error).<nl>
        1 - Memory allocation failed. <nl>
        3 - Invalid big number size. <nl>
        5 - No solution found (e.g. divisor was zero).<nl> 
    <ule>

 @comm   
        The value computed is:<nl>
        <nl>
        <tab><cfont>  quotient = dividend / divisor ;<efont><nl>
        <nl>
        The divisor must not exceed 512 bytes size or an error will result.<s2> The
        dividend may range up to twice this size, plus one extra digit, for a total
        of 1028 bytes.<nl>
        <nl>
        This API has two output parameters, <cfont>quotient<efont> and
        <cfont>remainder<efont>.<s2> Both of
        these output parameters are optional and either pointer parameter can
        be set to NULL if the respective result is not needed.<s2> Otherwise
        these must reference a 
        <linkto>../../crystruc.htm#Crypt_BigNumS<linkmid>Crypt_BigNumS<linktail>
        object.<nl>
        <nl>
        Either of the two output parameters may reference one of the two 
        input values, if the caller no longer needs the old values.<s2> This
        will not affect the resulting calculation.<s2> Note that 
        <linkto>../../crystruc.htm#Crypt_BigNumS<linkmid>Crypt_BigNumS<linktail>
        and  <linkto>../../crystruc.htm#Crypt_BigNumConstS<linkmid>Crypt_BigNumConstS<linktail>
        structure definitions are identical other than the <cfont>bnDataPtr<efont>
        member's <cfont>const<efont> nature, so pointers to these two types 
        can can safely be cast to one another.<nl>
        <nl>
        For the 
        <linkto>../../crystruc.htm#Crypt_BigNumS<linkmid>Crypt_BigNumS<linktail>
        object referenced by the output parameters <cfont>quotient<efont>
        and <cfont>remainder<efont>, only the <cfont>bnDataPtr<efont> member
        must be initialized by the user.<s2> The reference buffer must have 
        space for <cfont>divisor->bnDigitCnt<efont> digits, where each digit
        is an <cfont>unsigned int<efont> type.

  This function requires an 8 kByte workspace allocated from the system memory.<s2>
  The function will execute significantly faster if this workspace memory 
  is available in the system's 
  <linkto>../HELPER/helper09.htm<linkmid>fast memory<linktail> area.

 @Also  cry14.htm | Crypt_BN_Mul |
        cry13.htm | Crypt_BN_Mod_Mul  |
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
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 

#ifdef _cry11_
/*
@doc DOC_cry11_
 ----------------------------------------------------------------------------------
 Big Number MOD EXP
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_BN_Mod_Exp | crypt_index.htm | Big number modulo exponentiation. |
    <cfont>int far Crypt_BN_Mod_Exp( Crypt_BigNumS <tab>   far *result,<nl>
    <tab><tab><tab><tab><s3> const Crypt_BigNumConstS  far *a,<nl>
    <tab><tab><tab><tab><s3> const Crypt_BigNumConstS  far *power,<nl>
    <tab><tab><tab><tab><s3> const Crypt_BigNumConstS  far *modulo) ;<efont> |
 @parm  void | result | <hangpara 20:20> [out]<s2>  Pointer to 
         <linkto>../../crystruc.htm#Crypt_BigNumS<linkmid>big number<linktail>
        where result will be written.<s2> Caller must provide a buffer of
        sufficient size at <cfont>result->bnDataPtr<efont>.<s2> That is the
        only member of this referenced data structure which the caller must
        initialize.
 @parm  void | a | [in]<s2>  Pointer to 
         <linkto>../../crystruc.htm#Crypt_BigNumConstS<linkmid>big number<linktail>
        which will be raised to the specified exponent.
 @parm  void | power | [in]<s2>  Pointer to big number
        to be used as the exponent.
 @parm  void | modulo | [in]<s2>  Pointer to big number containing the large 
        prime number to be used for the modulo value.
 @rdesc error code:
    <ul>
        0 - Success (no error).<nl>
        1 - Memory allocation failed. <nl>
        3 - Invalid big number size. <nl>
        4 - The <cfont>modulo<efont> prime number was not odd.<nl>
        5 - No solution found (e.g. divisor was zero).<nl> 
    <ule>
 @comm   This API performs the modulo exponentiation operation.<s2> This
    operation is fundamental to many of the key exchange schemes.<nl>
    <nl>
    The value computed is:<nl>
    <nl>
    <tab><cfont> result = (a ** power) MOD modulo ;<efont><nl>
    <nl>
    The big numbers must not exceed 512 bytes size or an error will result.<nl>
    <nl>
    The prime number at <cfont>modulo<efont> must be an odd number.<nl>

  This function requires a 44 kByte workspace allocated from the system memory.<s2>
  The function will execute significantly faster if this workspace memory 
  is available in the system's 
  <linkto>../HELPER/helper09.htm<linkmid>fast memory<linktail> area.

 @Also  cry12.htm | Crypt_BN_Mod_Inverse |
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
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 

#ifdef _cry12_
/*
@doc DOC_cry12_
 ----------------------------------------------------------------------------------
 Big Number modulo inverse
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_BN_Mod_Inverse | crypt_index.htm | Big number modulo inverse. |
        <cfont>int far Crypt_BN_Mod_Inverse ( Crypt_BigNumS <tab>  far *result,<nl>
          <tab><tab><tab><tab><tab><tab> const Crypt_BigNumConstS far *a,<nl>
          <tab><tab><tab><tab><tab><tab> const Crypt_BigNumConstS far *b) ;<efont> |
 @parm  void | result | <hangpara 20:20> [out]<s2> On success the modulo inverse of
        <cfont>a<efont> is reported here.<s2> This location may reference
        one of the other inputs, which would then be overwritten.<s2>
        ( Note that pointers to 
         <linkto>../../crystruc.htm#Crypt_BigNumConstS<linkmid>Crypt_BigNumConstS<linktail>
         type can be safely cast to pointers to 
         <linkto>../../crystruc.htm#Crypt_BigNumS<linkmid>Crypt_BigNumS<linktail>
         type. )<s2> The caller must provide<nl>
         <cfont>b->bnDigitCnt<efont> digits
         of space in the buffer referenced by <cfont>result->bnDataPtr<efont>.<s2>
         The <cfont>bnDataPtr<efont> member is the only field at
         <cfont>result<efont> which must be initialized by the caller.
 @parm  void | a | [in]<s2> Pointer to big number whose modulo inverse
        is to be found.
 @parm  void | b | [in]<s2> Pointer to the big number modulo value.
 @rdesc error code:
    <ul>
        0 - Success (no error).<nl>
        1 - Memory allocation failed. <nl>
        3 - Invalid big number size. <nl>
        5 - No solution found (e.g. divisor was zero).<nl> 
    <ule>
 @comm   This API performs the modulo inverse operation.

      The function solves the following equation for '<cfont>result<efont>':

     <tab> <cfont> 1 == (a * result) mod b <efont>

    In some cases, this equation has no solution.

    The big numbers must not exceed 512 bytes size or an error will result.

  This function requires a 12 kByte workspace allocated from the system memory.<s2>
  The function will execute significantly faster if this workspace memory 
  is available in the system's 
  <linkto>../HELPER/helper09.htm<linkmid>fast memory<linktail> area.

 @Also  cry11.htm | Crypt_BN_Mod_Exp |
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
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 

#ifdef _cry13_
/*
@doc DOC_cry13_
 ----------------------------------------------------------------------------------
 Big Number modulo multiply
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_BN_Mod_Mul | crypt_index.htm | Big number modulo multiply. |
        <cfont>int far Crypt_BN_Mod_Mul ( Crypt_BigNumS <tab>  far *result,<nl>
          <tab><tab><tab><tab><tab> const Crypt_BigNumConstS far *a,<nl>
          <tab><tab><tab><tab><tab> const Crypt_BigNumConstS far *b,<nl>
          <tab><tab><tab><tab><tab> const Crypt_BigNumConstS far *m) ;<efont> |
 @parm  void | result | <hangpara 20:20> [out]<s2> On success the modulo product
        of <cfont>a<efont> and <cfont>b<efont> will be reported here.<s2>
        This location may reference one of the other inputs, which would 
        then be overwritten.<s2> ( Note that pointers to 
        <linkto>../../crystruc.htm#Crypt_BigNumConstS<linkmid>Crypt_BigNumConstS<linktail>
        type can be safely cast to pointers to  
        <linkto>../../crystruc.htm#Crypt_BigNumS<linkmid>Crypt_BigNumS<linktail>
        type. )<s2> The caller must provide
        <cfont>m->bnDigitCnt<efont> digits of space in the buffer referenced by<nl>
        <cfont>result->bnDataPtr<efont>.
 @parm  void | a | Input Parameter:<s2> Pointer to big number 
         for first factor of product.
 @parm  void | b | Input Parameter:<s2> Pointer to the big number
         for second factor of product.
 @parm  void | m | Input Parameter:<s2> Pointer to the big number
        modulo value.
 @rdesc error code:
    <ul>
        0 - Success (no error).<nl>
        1 - Memory allocation failed. <nl>
        3 - Invalid big number size. <nl>
        5 - No solution found (e.g. divisor was zero).<nl> 
    <ule>
 @comm  
    This API performs the modulo multiplication operation.<nl>
    <nl>
    The value computed is:<nl>
    <nl>
    <tab><cfont> result = a * b (mod m) ;<efont><nl>
    <nl>
    The big numbers must not exceed 512 bytes size or an error will result.

  This function requires a 44 kByte workspace allocated from the system memory.<s2>
  The function will execute significantly faster if this workspace memory 
  is available in the system's 
  <linkto>../HELPER/helper09.htm<linkmid>fast memory<linktail> area.

 @Also  cry14.htm | Crypt_BN_Mul |
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
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 

#ifdef _cry14_
/*
@doc DOC_cry14_
 ----------------------------------------------------------------------------------
 Big Number multiply
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_BN_Mul | crypt_index.htm | Big number multiply. |
        <cfont>int far Crypt_BN_Mul ( Crypt_BigNumS <tab>  far *result,<nl>
          <tab><tab><tab><tab> const Crypt_BigNumConstS far *a,<nl>
          <tab><tab><tab><tab> const Crypt_BigNumConstS far *b) ;<efont> |
 @parm  void | result | <hangpara 20:20> [out]<s2> On success the product 
        of <cfont>a<efont> and <cfont>b<efont> will be reported here.<s2>
        This location may reference one of the other inputs, which would
        then be overwritten.<s2> 
        ( Note that pointers to 
        <linkto>../../crystruc.htm#Crypt_BigNumConstS<linkmid>Crypt_BigNumConstS<linktail>
        type can be safely cast to pointers to  
        <linkto>../../crystruc.htm#Crypt_BigNumS<linkmid>Crypt_BigNumS<linktail>
        type. )<s2>
         In any case, the caller must provide space for at least<nl>
        <nl>
             <tab><tab><cfont> a->bnDigitCnt<efont><nl>
             <tab><tab><tab><tab> plus<nl>
             <tab><tab><cfont> b->bnDigitCnt<efont><nl>
        <nl>
        digits in the buffer referenced by <cfont>result->bnDataPtr<efont>.
 @parm  void | a  | [in]<s2> Pointer to big number for 
        the first factor of product.
 @parm  void | b |  [in]<s2> Pointer to the big number for
        the second factor of product.
 @rdesc error code:
    <ul>
        0 - Success (no error).<nl>
        1 - Memory allocation failed. <nl>
        3 - Invalid big number size. <nl>
    <ule>
 @comm  
        This API multiplies two big numbers.<s2> The value computed is:

    <tab><cfont> result = a * b ;<efont>

    The big number inputs must not exceed 512 bytes size or an error will result.<s2>
    The result can range up to twice this size.

  This function requires a 5 kByte workspace allocated from the system memory.<s2>
  The function will execute significantly faster if this workspace memory 
  is available in the system's 
  <linkto>../HELPER/helper09.htm<linkmid>fast memory<linktail> area.


 @Also  cry13.htm | Crypt_BN_Mod_Mul |
        cry10.htm | Crypt_BN_Div  |
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
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 

#ifdef _cry15_
/*
@doc DOC_cry15_
 ----------------------------------------------------------------------------------
 DES decryption
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_DES_Decrypt | crypt_index.htm | Decrypt one cipher block of data using DES 
        decryption method. |
        <cfont>int far Crypt_DES_Decrypt (<nl>
          <tab><tab><tab> const Crypt_DesKeyScheduleS far *schedule,<nl>
          <tab><tab><tab> const void                   far *in,<nl>
          <tab><tab><tab><tab><s2> void                   far *out ) ;<efont> |
 @parm  Crypt_3DesKeyScheduleS | schedule | Pointer to DES 
        <linkto>../../crystruc.htm#Crypt_DesKeyScheduleS<linkmid>subkey schedule<linktail>
        generated by
        <linkto>cry17.htm<linkmid>Crypt_DES_MakeKey()<linktail>.
 @parm  void | in | Pointer to 8 byte cipher text to
        be decrypted
 @parm  void | out | Pointer to 8 byte buffer where the resulting
        decrypted clear text will be written by this API.
 @rdesc 0 constant (provisional error code)
 @comm
    This API decrypts one 8 byte cipher block of data using the DES
    decryption method.<s2> It can be called repeatedly until your entire 
    message has been recovered.<s2> When your message is not an integral
    number of 8 byte blocks in length, then you will obtain on the final
    call the pad bytes that were appended to the original message at the
    encryption step.

    The DES cipher treats data as little endian long words.<s2> Any required 
    data endian handling is done inside this API, so the caller must not perform
    any such handling on their side.<s2>  (Since the <chiprtos> CPU is itself little
    endian, this note applies only for code which is to be ported to big
    endian Beck platforms.)

    The <cfont>in<efont> and <cfont>out<efont> parameters may reference the same location.

  Go <linkto>../../cryptTbl.htm<linkmid>here<linktail> for a summary of
  cipher method execution times.

 @Also  cry16.htm | Crypt_DES_Encrypt |
        cry17.htm | Crypt_DES_MakeKey  |
        cry00.htm | Crypt_3DES_Decrypt
 @rtos  On the first call, this library function invokes a software
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>interrupt<linktail>
        which modifies the code at the calling site inside your application
        program.<s2> A direct FAR JMP into the <chiprtos>
        implementation for this function is installed so that on
        return and on any subsequent calls to this API this
        dynamic link  reaches the function's
        implementation directly.<nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 


#ifdef _cry16_
/*
@doc DOC_cry16_
 ----------------------------------------------------------------------------------
 DES encryption
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_DES_Encrypt | crypt_index.htm | 
    Encrypt one cipher block of data using DES encryption method. |
        <cfont>int far Crypt_DES_Encrypt (<nl>
          <tab><tab><tab> const Crypt_DesKeyScheduleS far *schedule,<nl>
          <tab><tab><tab> const void                   far *in,<nl>
          <tab><tab><tab><tab><s2> void                   far *out ) ;<efont> |
 @parm  Crypt_DesKeyScheduleS | schedule |  Pointer to
        DES 
        <linkto>../../crystruc.htm#Crypt_DesKeyScheduleS<linkmid>subkey schedule<linktail>
        generated by
        <linkto>cry17.htm<linkmid>Crypt_DES_MakeKey()<linktail>.
 @parm  void | in | Pointer to 8 byte clear text to
        be encrypted
 @parm  void | out | Pointer to 8 byte buffer where the resulting
        decrypted clear text will be written by this API.
 @rdesc 0 constant  (provisional error code)
 @comm 
    This API encrypts one 8 byte cipher block of data using the DES encryption
    method.<s2> It can be called repeatedly until your entire message has
    been encrypted.<s2> When your message is not an integral number of 8 byte
    blocks in length, then you must pad the final block with some pattern
    agreed upon with your decryption side.

    The DES cipher treats data as little endian long words.<s2> Any required 
    data endian handling is done inside this API, so the caller must not perform
    any such handling on their side.<s2>  (Since the <chiprtos> CPU is itself little
    endian, this note applies only for code which is to be ported to big
    endian Beck platforms.)

    The <cfont>in<efont> and <cfont>out<efont> parameters may reference the same location.

  Go <linkto>../../cryptTbl.htm<linkmid>here<linktail> for a summary of
  cipher method execution times.

 @Also  cry15.htm | Crypt_DES_Decrypt |
        cry17.htm | Crypt_DES_MakeKey  |
        cry01.htm | Crypt_3DES_Encrypt
 @rtos  On the first call, this library function invokes a software
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>interrupt<linktail>
        which modifies the code at the calling site inside your application
        program.<s2> A direct FAR JMP into the <chiprtos>
        implementation for this function is installed so that on
        return and on any subsequent calls to this API this
        dynamic link  reaches the function's
        implementation directly.<nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 

#ifdef _cry17_
/*
@doc DOC_cry17_
 ----------------------------------------------------------------------------------
 DES key generation
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_DES_MakeKey | crypt_index.htm | 
    Generates a DES subkey schedule based on a supplied 8 byte key. |
        <cfont>int far Crypt_DES_MakeKey (<nl>
          <tab><tab><tab> const unsigned char     far * key,<nl>
          <tab><tab><tab> Crypt_DesKeyScheduleS  far * schedule ) ;<efont> |
 @parm  char | key | [in]<s2> The secret 8 byte (64 bit) DES key,
        to be used to generate the new DES subkey schedule.
 @parm  void | schedule | [out]<s2> Pointer to
        <linkto>../../crystruc.htm#Crypt_DesKeyScheduleS<linkmid>Crypt_DesKeyScheduleS<linktail>
        structure to be initialized by this API.
 @rdesc 0 constant (provisional error code)
 @comm  Each byte of the 8 byte key contains 7 key bits plus an odd parity
    bit (LS bit) for a total key size of 56 bits.<s2> The parity bits are
    not tested by this API.<s2> (If desired, this key byte odd parity check
    could be done on the user side.)<nl>
    <nl>
    No presetting of the memory at <cfont>schedule<efont> is required by
    the caller.<s2> This API fully initializes this block of memory with
    a new DES subkey schedule based on the provided key.<nl>

   The DES cipher encryption/decryption speed improves slightly (~3%) when the
    <linkto>../../crystruc.htm#Crypt_DesKeyScheduleS<linkmid>Crypt_DesKeyScheduleS<linktail>
    object is allocated from the system's 
    <linkto>../HELPER/helper09.htm<linkmid>fast RAM<linktail> heap area. Go
    <linkto>../../cryptTbl.htm<linkmid>here<linktail> for a summary of
    cipher method execution times.

 @Also  cry15.htm | Crypt_DES_Decrypt |
        cry16.htm | Crypt_DES_Encrypt  |
        cry02.htm | Crypt_3DES_MakeKey
 @rtos  On the first call, this library function invokes a software
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>interrupt<linktail>
        which modifies the code at the calling site inside your application
        program.<s2> A direct FAR JMP into the <chiprtos>
        implementation for this function is installed so that on
        return and on any subsequent calls to this API this
        dynamic link  reaches the function's
        implementation directly.<nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 

#ifdef _cry24_
/*
@doc DOC_cry24_
 ----------------------------------------------------------------------------------
 Random Numbers
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_Random_Bytes | crypt_index.htm | 
    Generate a stream of pseudo random bytes. |
        <cfont>int far Crypt_Random_Bytes (<nl>
          <tab><tab><tab> unsigned char far *buf,<nl>
          <tab><tab><tab> unsigned int length ) ;<efont> |
 @parm  char | buf | [out]<s2>  The random data will be
        written here.
 @parm  void | length | [in]<s2> Number of bytes to generate.
 @rdesc 0 constant (provisional error code)
 @comm
     This function uses the psuedo random number generator
     provided in hardware.
     
     All bytes generataed will be non-zero.<nl>

 @rtos  On the first call, this library function invokes a software
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>interrupt<linktail>
        which modifies the code at the calling site inside your application
        program.<s2> A direct FAR JMP into the <chiprtos>
        implementation for this function is installed so that on
        return and on any subsequent calls to this API this
        dynamic link  reaches the function's
        implementation directly.<nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.19
*/
#endif 



#ifdef _tcpDFA_
/*
@doc DOC_tcpDFA_
 ----------------------------------------------------------------------------------
 Build MD5 checksums (init)
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_MD5_Init | crypt_index.htm | Initialize MD5 hash checksum generator. |
        <cfont>int Crypt_MD5_Init ( Crypt_MD5_ContextPtr md5context );<efont> |
 @parm  Crypt_MD5_ContextPtr | md5context | [out]  Pointer to
        <linkto>../../crystruc.htm#Crypt_MD5_Context<linkmid>MD5 context structure<linktail>
        to be initialized by this API.
 @rdesc 0: Success<nl>
        -1:  failed
 @comm   This function must be called prior to making the first call to
    <linkto>tcpDFB.htm<linkmid>Crypt_MD5_Update()<linktail>
    when a MD5 hash value is to be computed.

      No initialization of the object at <code>md5context<codee> by the
      caller is required.<s2> This API will perform the initialization.

 @Also  tcpDFB.htm | Crypt_MD5_Update |
        tcpDFC.htm | Crypt_MD5_Final  |
         |
 @Also  tcpDFD.htm | Crypt_SHA1_Init |
        cry43.htm  | Crypt_SHA256_Init  |
         |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xDF<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>= 1.35, CLIB version <gt>= 2.19) there
        is also a version of this function available which uses dynamic 
        linking instead of the software interrupt.<s2>  This reduces the
        function's overhead and thus speeds up your application.<s2> This
        function's name is <cfont>Crypt_MD5_Init_Dyn<efont>, however you
        should not use this function  directly.<s2> Instead you should add
        the define <cfont>TCPIP_DYN_LINK<efont> to your program before 
        including the CLIB's header file(s), as follows:<nl>
        <ul><nl>
            <cfont>#define TCPIP_DYN_LINK<nl>
            #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This compilation switch will map the original function's name
        to the dynamic link version.<s2>  In this manner, you can easily
        switch existing programs over to the 
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>dynamic link<linktail> API.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/
int Crypt_MD5_Init (Crypt_MD5_ContextPtr md5context)
{
  _ES = FP_SEG(md5context);
  _DI = FP_OFF(md5context);
  _AL = 1;
  _AH = CRYPT_HASH;
  asm { int TCPIPVECT  } ;
  return   _DX ;
}
#endif


#ifdef _tcpDFB_
/*
@doc DOC_tcpDFB_
 ----------------------------------------------------------------------------------
 Build MD5 checksums (update)
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_MD5_Update | crypt_index.htm | Update MD5 hash checksum generator. |
        <cfont>int Crypt_MD5_Update ( Crypt_MD5_ContextPtr md5context,
        <tab><tab><tab><tab><tab><tab>const void far * inBuffer,
        <tab><tab><tab><tab><tab><tab>unsigned int length );<efont> |
 @parm  Crypt_MD5_ContextPtr | md5context | Pointer to
        <linkto>../../crystruc.htm#Crypt_MD5_Context<linkmid>MD5 context structure<linktail>
 @parm  unsigned char far *   | inBuffer   | Pointer to user data
 @parm  unsigned int          | length     | Length of <code>inBuffer<codee> in bytes
 @rdesc 0: Success<nl>
        -1:  failed
 @comm  This function runs the provided data at <code>inBuffer<codee> into
    the hash value accumulator.<s2> The total data set can be passed into
    the hash value over a series of calls to this function.

    A call to <linkto>tcpDFA.htm<linkmid>Crypt_MD5_Init()<linktail> must 
    precede your first call to this function.<s2> After you have passed all
    of your data into this hash computer with a series of 
    <code>Crypt_MD5_Update()<codee> calls (one or more calls),
    the <linkto>tcpDFC.htm<linkmid>Crypt_MD5_Final()<linktail> must
    be called at the end to pick up the answer.

  Go <linkto>../../cryptTbl.htm#HASHTIMING<linkmid>here<linktail> for a 
  summary of hash method execution times.

 @Also  tcpDFA.htm | Crypt_MD5_Init |
        tcpDFC.htm | Crypt_MD5_Final  |
         |
 @Also  tcpDFE.htm | Crypt_SHA1_Update |
        cry44.htm  | Crypt_SHA256_Update |
         |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xDF<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>= 1.35, CLIB version <gt>= 2.19) there
        is also a version of this function available which uses dynamic 
        linking instead of the software interrupt.<s2>  This reduces the
        function's overhead and thus speeds up your application.<s2> This
        function's name is <cfont>Crypt_MD5_Update_Dyn<efont>, however you
        should not use this function  directly.<s2> Instead you should add
        the define <cfont>TCPIP_DYN_LINK<efont> to your program before 
        including the CLIB's header file(s), as follows:<nl>
        <ul><nl>
            <cfont>#define TCPIP_DYN_LINK<nl>
            #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This compilation switch will map the original function's name
        to the dynamic link version.<s2>  In this manner, you can easily
        switch existing programs over to the 
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>dynamic link<linktail> API.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/
int Crypt_MD5_Update (Crypt_MD5_ContextPtr md5context,
                      const void far *inBuffer, 
                      unsigned int length)
{
  _ES = FP_SEG(md5context);
  _DI = FP_OFF(md5context);
  _DX = FP_SEG(inBuffer);
  _SI = FP_OFF(inBuffer);
  _CX = length;
  _AL = 2;
  _AH = CRYPT_HASH;
  asm { int TCPIPVECT  } ;
  return   _DX ;
}
#endif

#ifdef _tcpDFC_
/*
@doc DOC_tcpDFC_
 ----------------------------------------------------------------------------------
 Build MD5 checksums (final)
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_MD5_Final | crypt_index.htm | Final MD5 checksum generator. |
        <cfont>int Crypt_MD5_Final ( Crypt_MD5_ContextPtr md5context );<efont> |
 @parm  Crypt_MD5_ContextPtr | md5context | Pointer to
        <linkto>../../crystruc.htm#Crypt_MD5_Context<linkmid>MD5 context structure<linktail>
 @rdesc 0: Success<nl>
        -1:  failed
 @comm  This function is called to get the result after the final call to
        <linkto>tcpDFB.htm<linkmid>Crypt_MD5_Update()<linktail> 
        has passed all of the desired data into the hash generator.
    
      After this call, the 16 byte MD5 hash result can be found in 
      <code>md5context-<gt>digest<codee>.
 @Also  tcpDFA.htm | Crypt_MD5_Init |
        tcpDFB.htm | Crypt_MD5_Update  |
        | 
 @Also  tcpDFF.htm | Crypt_SHA1_Final |
        cry45.htm  | Crypt_SHA256_Final  |
        | 
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xDF<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>= 1.35, CLIB version <gt>= 2.19) there
        is also a version of this function available which uses dynamic 
        linking instead of the software interrupt.<s2>  This reduces the
        function's overhead and thus speeds up your application.<s2> This
        function's name is <cfont>Crypt_MD5_Final_Dyn<efont>, however you
        should not use this function  directly.<s2> Instead you should add
        the define <cfont>TCPIP_DYN_LINK<efont> to your program before 
        including the CLIB's header file(s), as follows:<nl>
        <ul><nl>
            <cfont>#define TCPIP_DYN_LINK<nl>
            #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This compilation switch will map the original function's name
        to the dynamic link version.<s2>  In this manner, you can easily
        switch existing programs over to the 
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>dynamic link<linktail> API.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/
int Crypt_MD5_Final (Crypt_MD5_ContextPtr md5context)
{
  _ES = FP_SEG(md5context);
  _DI = FP_OFF(md5context);
  _AL = 3;
  _AH = CRYPT_HASH;
  asm { int TCPIPVECT  } ;
  return   _DX ;
}
#endif

#ifdef _tcpDFD_
/*
@doc DOC_tcpDFD_
 ----------------------------------------------------------------------------------
 Build SHA1 checksums (init)
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_SHA1_Init | crypt_index.htm | Initialize SHA1 hash checksum generator. |
        <cfont>int Crypt_SHA1_Init ( Crypt_SHA1_ContextPtr sha1context );<efont> |
 @parm  Crypt_SHA1_ContextPtr | sha1context | [out]<s2> Pointer to
        <linkto>../../crystruc.htm#Crypt_SHA1_Context<linkmid>SHA1 context structure<linktail>
         to be initialized by this API.
@rdesc 0: Success<nl>
        -1:  failed
 @comm  This function must be called prior to making the first call to
        <linkto>tcpDFE.htm<linkmid>Crypt_SHA1_Update()<linktail> 
        when a SHA1 hash value is to be computed.

      No initialization of the object at <code>sha1context<codee> by the
      caller is required.<s2> This API will perform the initialization.

 @Also  tcpDFE.htm | Crypt_SHA1_Update |
        tcpDFF.htm | Crypt_SHA1_Final  |
         |
 @Also  tcpDFA.htm | Crypt_MD5_Init |
        cry43.htm  | Crypt_SHA256_Init  |
         |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xDF<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>= 1.35, CLIB version <gt>= 2.19) there
        is also a version of this function available which uses dynamic 
        linking instead of the software interrupt.<s2>  This reduces the
        function's overhead and thus speeds up your application.<s2> This
        function's name is <cfont>Crypt_SHA1_Init_Dyn<efont>, however you
        should not use this function  directly.<s2> Instead you should add
        the define <cfont>TCPIP_DYN_LINK<efont> to your program before 
        including the CLIB's header file(s), as follows:<nl>
        <ul><nl>
            <cfont>#define TCPIP_DYN_LINK<nl>
            #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This compilation switch will map the original function's name
        to the dynamic link version.<s2>  In this manner, you can easily
        switch existing programs over to the 
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>dynamic link<linktail> API.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.11 | V1.00
 @target_clib V2.08
*/
int Crypt_SHA1_Init (Crypt_SHA1_ContextPtr sha1context)
{
  _ES = FP_SEG(sha1context);
  _DI = FP_OFF(sha1context);
  _AL = 4;
  _AH = CRYPT_HASH;
  asm { int TCPIPVECT  } ;
  return   _DX ;
}
#endif


#ifdef _tcpDFE_
/*
@doc DOC_tcpDFE_
 ----------------------------------------------------------------------------------
 Build SHA1 checksums (update)
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_SHA1_Update | crypt_index.htm | Update SHA1 hash checksum generator. |
        <cfont>int Crypt_SHA1_Update ( Crypt_SHA1_ContextPtr sha1context,
        <tab><tab><tab><tab><tab><tab>const void far * inBuffer,
        <tab><tab><tab><tab><tab><tab>unsigned int length );<efont> |
 @parm  Crypt_SHA1_ContextPtr | sha1context | Pointer to
        <linkto>../../crystruc.htm#Crypt_SHA1_Context<linkmid>SHA1 context structure<linktail>
 @parm  unsigned char far *   | inBuffer   | Pointer to user data
 @parm  unsigned int          | length     | Length of <code>inBuffer<codee> in bytes
 @rdesc 0: Success<nl>
        -1:  failed
 @comm  This function runs the provided data at <code>inBuffer<codee> into 
    the hash value accumulator.<s2> The total data set can be passed into 
    the hash value over a series of calls to this function.

    A call to <linkto>tcpDFD.htm<linkmid>Crypt_SHA1_Init()<linktail>
    must precede your first call to this function.<s2> After you have
    passed all of your data into this hash computer with a series
    of <code>Crypt_SHA1_Update()<codee> calls (one or more calls), the 
    <linkto>tcpDFF.htm<linkmid>Crypt_SHA1_Final()<linktail> must
    be called at the end to pick up the answer.

  Go <linkto>../../cryptTbl.htm#HASHTIMING<linkmid>here<linktail> for a summary
  of hash method execution times.
 @Also  tcpDFD.htm | Crypt_SHA1_Init |
        tcpDFF.htm | Crypt_SHA1_Final  |
         |
 @Also  tcpDFB.htm | Crypt_MD5_Update |
        cry44.htm  | Crypt_SHA256_Update  |
         |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xDF<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>= 1.35, CLIB version <gt>= 2.19) there
        is also a version of this function available which uses dynamic 
        linking instead of the software interrupt.<s2>  This reduces the
        function's overhead and thus speeds up your application.<s2> This
        function's name is <cfont>Crypt_SHA1_Update_Dyn<efont>, however you
        should not use this function  directly.<s2> Instead you should add
        the define <cfont>TCPIP_DYN_LINK<efont> to your program before 
        including the CLIB's header file(s), as follows:<nl>
        <ul><nl>
            <cfont>#define TCPIP_DYN_LINK<nl>
            #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This compilation switch will map the original function's name
        to the dynamic link version.<s2>  In this manner, you can easily
        switch existing programs over to the 
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>dynamic link<linktail> API.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.11 | V1.00
 @target_clib V2.08
*/
int Crypt_SHA1_Update (Crypt_SHA1_ContextPtr sha1context,
                       const void far *inBuffer, 
                       unsigned int length)
{
  _ES = FP_SEG(sha1context);
  _DI = FP_OFF(sha1context);
  _DX = FP_SEG(inBuffer);
  _SI = FP_OFF(inBuffer);
  _CX = length;
  _AL = 5;
  _AH = CRYPT_HASH;
  asm { int TCPIPVECT  } ;
  return   _DX ;
}
#endif

#ifdef _tcpDFF_
/*
@doc DOC_tcpDFF_
 ----------------------------------------------------------------------------------
 Build SHA1 checksums (final)
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_SHA1_Final | crypt_index.htm | Final SHA1 hash checksum generator. |
        <cfont>int Crypt_SHA1_Final ( Crypt_SHA1_ContextPtr sha1context );<efont> |
 @parm  Crypt_SHA1_ContextPtr | sha1context | Pointer to
        <linkto>../../crystruc.htm#Crypt_SHA1_Context<linkmid>SHA1 context structure<linktail>
 @rdesc 0: Success<nl>
        -1:  failed
 @comm  This function is called to get the result after the final call to 
    <linkto>tcpDFE.htm<linkmid>Crypt_SHA1_Update()<linktail> 
    has passed all of the desired data into the hash generator.

      After this call, the 20 byte SHA1 hash result can be found in 
      <code>sha1context-<gt>digest<codee>.
 @Also  tcpDFD.htm | Crypt_SHA1_Init |
        tcpDFE.htm | Crypt_SHA1_Update  |
        |
 @Also  tcpDFC.htm | Crypt_MD5_Final |
        cry45.htm | Crypt_SHA256_Final  |
        |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xDF<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>= 1.35, CLIB version <gt>= 2.19) there
        is also a version of this function available which uses dynamic 
        linking instead of the software interrupt.<s2>  This reduces the
        function's overhead and thus speeds up your application.<s2> This
        function's name is <cfont>Crypt_Crypt_SHA1_Final_Dyn<efont>, however you
        should not use this function  directly.<s2> Instead you should add
        the define <cfont>TCPIP_DYN_LINK<efont> to your program before 
        including the CLIB's header file(s), as follows:<nl>
        <ul><nl>
            <cfont>#define TCPIP_DYN_LINK<nl>
            #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This compilation switch will map the original function's name
        to the dynamic link version.<s2>  In this manner, you can easily
        switch existing programs over to the 
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>dynamic link<linktail> API.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.11 | V1.00
 @target_clib V2.08
*/
int Crypt_SHA1_Final (Crypt_SHA1_ContextPtr sha1context)
{
  _ES = FP_SEG(sha1context);
  _DI = FP_OFF(sha1context);
  _AL = 6;
  _AH = CRYPT_HASH;
  asm { int TCPIPVECT  } ;
  return   _DX ;
}
#endif

/*
@doc DOC_cry43_
 ----------------------------------------------------------------------------------
 Build SHA256 checksums (init)
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_SHA256_Init | crypt_index.htm | Initialize SHA256 hash checksum generator. |
        <cfont>int Crypt_SHA256_Init ( Crypt_SHA256_ContextPtr sha256context );<efont> |
 @parm  Crypt_SHA256_ContextPtr | sha256context | [out]<s2> Pointer to
        <linkto>../../crystruc.htm#Crypt_SHA256_Context<linkmid>SHA256 context structure<linktail>
         to be initialized by this API.
@rdesc 0: Success<nl>
 @comm  This function must be called prior to making the first call to
        <linkto>cry44.htm<linkmid>Crypt_SHA256_Update()<linktail> 
        when a SHA256 hash value is to be computed.

      No initialization of the object at <code>sha256context<codee> by the
      caller is required.<s2> This API will perform the initialization.

 @Also  cry44.htm | Crypt_SHA256_Update |
        cry45.htm | Crypt_SHA256_Final  |
         | 
 @Also  tcpDFA.htm | Crypt_MD5_Init |
        tcpDFD.htm | Crypt_SHA1_Init  |
         | 
 @rtos  On the first call to this library function, an
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>RTOS software interrupt<linktail>
        API is used to install a dynamic link.  This link then is used from then
        on to directly call the @Chip-RTOS function.


 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.80 | V1.80
 @target_clib V2.50
*/


/*
@doc DOC_cry44_
 ----------------------------------------------------------------------------------
 Build SHA256 checksums (update)
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_SHA256_Update | crypt_index.htm | Update SHA256 hash checksum generator. |
        <cfont>int Crypt_SHA256_Update ( Crypt_SHA256_ContextPtr sha256context,
        <tab><tab><tab><tab><tab><tab><s2><s2>const void far * inBuffer,
        <tab><tab><tab><tab><tab><tab><s2><s2>unsigned int length );<efont> |
 @parm  Crypt_SHA256_ContextPtr | sha256context | Pointer to
        <linkto>../../crystruc.htm#Crypt_SHA256_Context<linkmid>SHA256 context structure<linktail>
 @parm  unsigned char far *   | inBuffer   | Pointer to user data
 @parm  unsigned int          | length     | Length of <code>inBuffer<codee> in bytes
 @rdesc 0<nl>
 @comm  This function runs the provided data at <code>inBuffer<codee> into 
    the hash value accumulator.<s2> The total data set can be passed into 
    the hash value over a series of calls to this function.

    A call to <linkto>cry43.htm<linkmid>Crypt_SHA256_Init()<linktail>
    must precede your first call to this function.<s2> After you have
    passed all of your data into this hash computer with a series
    of <code>Crypt_SHA256_Update()<codee> calls (one or more calls), the 
    <linkto>cry45.htm<linkmid>Crypt_SHA256_Final()<linktail> must
    be called at the end to pick up the answer.

  Go <linkto>../../cryptTbl.htm#HASHTIMING<linkmid>here<linktail> for a summary
  of hash method execution times.

 @Also  cry43.htm | Crypt_SHA256_Init |
        cry45.htm | Crypt_SHA256_Final  |
         | 
 @Also  tcpDFB.htm | Crypt_MD5_Update |
        tcpDFE.htm | Crypt_SHA1_Update  |
         | 
 @rtos  On the first call to this library function, an
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>RTOS software interrupt<linktail>
        API is used to install a dynamic link.  This link then is used from then
        on to directly call the @Chip-RTOS function.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.80 | V1.80
 @target_clib V2.50
*/

/*
@doc DOC_cry45_
 ----------------------------------------------------------------------------------
 Build SHA256 hash (final)
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_SHA256_Final | crypt_index.htm | Final SHA256 hash checksum generator. |
        <cfont>int Crypt_SHA256_Final ( Crypt_SHA256_ContextPtr sha256context );<efont> |
 @parm  Crypt_SHA256_ContextPtr | sha256context | Pointer to
        <linkto>../../crystruc.htm#Crypt_SHA256_Context<linkmid>SHA256 context structure<linktail>
 @rdesc 0<nl>
 @comm  This function is called to get the result after the final call to 
    <linkto>cry44.htm<linkmid>Crypt_SHA256_Update()<linktail> 
    has passed all of the desired data into the hash generator.

      After this call, the 32 byte SHA256 hash result can be found in 
      <code>sha256context-<gt>digest<codee>.
 @Also  cry43.htm | Crypt_SHA256_Init |
        cry44.htm | Crypt_SHA256_Update  |
        tcpDFF.htm | Crypt_SHA1_Final
 @rtos  On the first call to this library function, an
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>RTOS software interrupt<linktail>
        API is used to install a dynamic link.  This link then is used from then
        on to directly call the @Chip-RTOS function.


 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.80 | V1.80
 @target_clib V2.50
*/


#ifdef _tcpE01_
/*
@doc DOC_tcpE01_
 ----------------------------------------------------------------------------------
 Make AES encrypt key
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_AES_MakeEncryptKey | crypt_index.htm | Generate AES encryption key. |
        <cfont>int Crypt_AES_MakeEncryptKey ( const Crypt_GenericKey *key,
        <tab><tab><tab><tab><tab><tab><tab><s2> Crypt_AES_ContextPtr aescontext );<efont> |
 @parm  Crypt_GenericKeyPtr | key | [in]<s2> Pointer to
        <linkto>../../crystruc.htm#Crypt_GenericKey<linkmid>Generic key structure<linktail>
 @parm  Crypt_AES_ContextPtr | aescontext | [out]<s2> Pointer to
        <linkto>../../crystruc.htm#Crypt_AES_Context<linkmid>AES context structure<linktail>
        where internal key information will be put by this API.
 @rdesc 0: Success<nl>
        -1:  failed
 @comm  This API creates an AES encryption key based on supplied key material.

    The AES (Advanced Encryption Standard) key size is selected by the
    caller's <code>key->keyBits<codee> value.<s2> The <code>key->keyDataPtr<codee>
    must be set to reference the key material (usually some randomly selected 
    values).<s2> The same key material must be used for both this
    <code>Crypt_AES_MakeEncryptKey()<codee> and the
    <linkto>tcpE02.htm<linkmid>Crypt_AES_MakeDecryptKey()<linktail> in order
    for a given message to be succesfully encrypted and decrypted.

    The amount of key material provided must cover the key size.<s2> So this
    means that for a 128 bit key, 16 bytes of key material are required.<s2> For
    192 bit key, 24 bytes are required.<s2> And for a 256 bit key, 32 bytes are
    required.

    The object referenced by the <i>aescontext<ie> argument, while
    allocated by the user, is used only by the AES API to maintain the
    key state information.<s2> The user should ignore this object's
    contents.<s2> No particular preset is required on it by the user.

   The AES cipher encryption/decryption speed improves slightly (~4%) when the
    <linkto>../../crystruc.htm#Crypt_AES_Context<linkmid>Crypt_AES_Context<linktail>
    object is allocated from the system's 
    <linkto>../HELPER/helper09.htm<linkmid>fast RAM<linktail> heap area. Go
    <linkto>../../cryptTbl.htm<linkmid>here<linktail> for a summary of
    cipher method execution times.


 @Also  tcpE02.htm | Crypt_AES_MakeDecryptKey |
        tcpE03.htm | Crypt_AES_Encrypt  |
        tcpE04.htm | Crypt_AES_Decrypt
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xE0<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>= 1.35, CLIB version <gt>= 2.19) there
        is also a version of this function available which uses dynamic 
        linking instead of the software interrupt.<s2>  This reduces the
        function's overhead and thus speeds up your application.<s2> This
        function's name is <cfont>Crypt_AES_MakeEncryptKey_Dyn<efont>, however you
        should not use this function  directly.<s2> Instead you should add
        the define <cfont>TCPIP_DYN_LINK<efont> to your program before 
        including the CLIB's header file(s), as follows:<nl>
        <ul><nl>
            <cfont>#define TCPIP_DYN_LINK<nl>
            #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This compilation switch will map the original function's name
        to the dynamic link version.<s2>  In this manner, you can easily
        switch existing programs over to the 
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>dynamic link<linktail> API.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.11 | V1.00
 @target_clib V2.08
*/
int Crypt_AES_MakeEncryptKey (const Crypt_GenericKey *key,
                              Crypt_AES_ContextPtr aescontext)
{
  _ES = FP_SEG(key);
  _DI = FP_OFF(key);
  _DX = FP_SEG(aescontext);
  _SI = FP_OFF(aescontext);
  _AL = 1;
  _AH = CRYPT_CIPHER;
  asm { int TCPIPVECT  } ;
  return   _DX ;
}
#endif

#ifdef _tcpE02_
/*
@doc DOC_tcpE02_
 ----------------------------------------------------------------------------------
 Make AES decrypt key
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_AES_MakeDecryptKey | crypt_index.htm | Generate AES decryption key. |
        <cfont>int Crypt_AES_MakeDecryptKey ( const Crypt_GenericKey *key,
        <tab><tab><tab><tab><tab><tab><tab><s2> Crypt_AES_ContextPtr aescontext );<efont> |
 @parm  Crypt_GenericKeyPtr | key | [in]<s2> Pointer to
        <linkto>../../crystruc.htm#Crypt_GenericKey<linkmid>Generic key structure<linktail>
        containing the key generation specifics provided by caller.
 @parm  Crypt_AES_ContextPtr | aescontext | [out]<s2> Pointer to
        <linkto>../../crystruc.htm#Crypt_AES_Context<linkmid>AES context structure<linktail>
        where internal key information will be put by this API.
 @rdesc 0: Success<nl>
        -1:  failed
 @comm  This API creates an AES decryption key based on supplied key material.
 
        See <linkto>tcpE01.htm<linkmid>Crypt_AES_MakeEncryptKey()<linktail>
        for more details.

 @Also  tcpE01.htm | Crypt_AES_MakeEncryptKey |
        tcpE03.htm | Crypt_AES_Encrypt  |
        tcpE04.htm | Crypt_AES_Decrypt
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xE0<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>= 1.35, CLIB version <gt>= 2.19) there
        is also a version of this function available which uses dynamic 
        linking instead of the software interrupt.<s2>  This reduces the
        function's overhead and thus speeds up your application.<s2> This
        function's name is <cfont>Crypt_AES_MakeDecryptKey_Dyn<efont>, however you
        should not use this function  directly.<s2> Instead you should add
        the define <cfont>TCPIP_DYN_LINK<efont> to your program before 
        including the CLIB's header file(s), as follows:<nl>
        <ul><nl>
            <cfont>#define TCPIP_DYN_LINK<nl>
            #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This compilation switch will map the original function's name
        to the dynamic link version.<s2>  In this manner, you can easily
        switch existing programs over to the 
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>dynamic link<linktail> API.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.11 | V1.00
 @target_clib V2.08
*/
int Crypt_AES_MakeDecryptKey (const Crypt_GenericKey *key,
                              Crypt_AES_ContextPtr aescontext)
{
  _ES = FP_SEG(key);
  _DI = FP_OFF(key);
  _DX = FP_SEG(aescontext);
  _SI = FP_OFF(aescontext);
  _AL = 2;
  _AH = CRYPT_CIPHER;
  asm { int TCPIPVECT  } ;
  return   _DX ;
}
#endif

#ifdef _tcpE03_
/*
@doc DOC_tcpE03_
 ----------------------------------------------------------------------------------
 Encrypt AES message
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_AES_Encrypt | crypt_index.htm |
    Use AES to encrypt one cipher block of a message. |
        <cfont>int Crypt_AES_Encrypt ( const Crypt_AES_Context * aescontext,
        <tab><tab><tab><tab><tab><tab>const void far * in,<nl>
        <tab><tab><tab><tab><tab><tab>void far * out );<efont> |
 @parm  const Crypt_AES_Context * | aescontext | Pointer to
        <linkto>../../crystruc.htm#Crypt_AES_Context<linkmid>AES context structure<linktail>
        (key data)
 @parm  const void far * | in  | Pointer to 16 bytes (one cipher block) of
       "plain text" input data
 @parm  void far * | out | Pointer to a 16 byte output buffer to
        receive the resulting encrypted data.  (This may optionally be the same buffer
        as 'in' references.)
 @rdesc 0: Success<nl>
        -1:  failed
 @comm  The AES (Advanced Encryption Standard) is a block cipher method.<s2> This
     API encrypts one block of a message.<s2> The cipher block size is 16 bytes.

     This API may be used repeatedly until your entire message has been 
     encrypted.<s2> When your message is not an integral number of 16
     byte blocks in length, then you must pad the final block with some
     pattern agreed upon with your decryption side.

    Prior to calling this API for the first block of the message, the
    <linkto>tcpE01.htm<linkmid>Crypt_AES_MakeEncryptKey()<linktail> must be
    used to initialize the encryption key.

  Go <linkto>../../cryptTbl.htm<linkmid>here<linktail> for a summary of
  cipher method execution times.

 @Also  tcpE01.htm | Crypt_AES_MakeEncryptKey |
        tcpE02.htm | Crypt_AES_MakeDecryptKey  |
        tcpE04.htm | Crypt_AES_Decrypt
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xE0<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>= 1.35, CLIB version <gt>= 2.19) there
        is also a version of this function available which uses dynamic 
        linking instead of the software interrupt.<s2>  This reduces the
        function's overhead and thus speeds up your application.<s2> This
        function's name is <cfont>Crypt_AES_Encrypt_Dyn<efont>, however you
        should not use this function  directly.<s2> Instead you should add
        the define <cfont>TCPIP_DYN_LINK<efont> to your program before 
        including the CLIB's header file(s), as follows:<nl>
        <ul><nl>
            <cfont>#define TCPIP_DYN_LINK<nl>
            #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This compilation switch will map the original function's name
        to the dynamic link version.<s2>  In this manner, you can easily
        switch existing programs over to the 
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>dynamic link<linktail> API.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.11 | V1.00
 @target_clib V2.08
*/
int Crypt_AES_Encrypt (const Crypt_AES_Context *aescontext,
                       const void far * in,
                       void far * out)
{
  _DX = FP_SEG(aescontext);
  _SI = FP_OFF(aescontext);
  _ES = FP_SEG(in);
  _DI = FP_OFF(in);
  _CX = FP_SEG(out);
  _BX = FP_OFF(out);
  _AL = 3;
  _AH = CRYPT_CIPHER;
  asm { int TCPIPVECT  } ;
  return   _DX ;
}
#endif

#ifdef _tcpE04_
/*
@doc DOC_tcpE04_
 ----------------------------------------------------------------------------------
 Decrypt AES message
 ----------------------------------------------------------------------------------
 @clibSub  Crypt_AES_Decrypt | crypt_index.htm | 
    Decrypt one cipher block of an AES encrypted message. |
        <cfont>int Crypt_AES_Decrypt ( const Crypt_AES_Context *aescontext,
        <tab><tab><tab><tab><tab><tab>const void far * in,<nl>
        <tab><tab><tab><tab><tab><tab>void far * out );<efont> |
 @parm  const Crypt_AES_Context * | aescontext | Pointer to
        <linkto>../../crystruc.htm#Crypt_AES_Context<linkmid>AES context structure<linktail>
        (key data)
 @parm  const void far * | in  | Pointer to 16 bytes (one cipher block)
        of encrypted input data
 @parm  void far * | out |  Pointer to a 16 byte 
    output buffer to receive the recovered "plain text" data.  (This may optionally
    be the same buffer as 'in' references.)
 @rdesc 0: Success<nl>
        -1:  failed
 @comm  The AES (Advanced Encryption Standard) is a block cipher method.<s2> This 
     API decrypts one block of a message.<s2> The cipher block size is 16 bytes.

    Prior to calling for the first block of the message, the 
    <linkto>tcpE02.htm<linkmid>Crypt_AES_MakeDecryptKey()<linktail> 
    must be used to initialize the decryption key.

    This API may be used repeatedly until your entire message has been
    recovered.<s2> When your message is not an integral number of
    16 byte blocks in length, then you will obtain on the final call the
    pad bytes that were appended to the original message at the
    encryption step.

  Go <linkto>../../cryptTbl.htm<linkmid>here<linktail> for a summary of
  cipher method execution times.

 @Also  tcpE01.htm | Crypt_AES_MakeEncryptKey |
        tcpE02.htm | Crypt_AES_MakeDecryptKey  |
        tcpE03.htm | Crypt_AES_Encrypt
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../tcpipapi.htm#0xAC0xE0<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>= 1.35, CLIB version <gt>= 2.19) there
        is also a version of this function available which uses dynamic 
        linking instead of the software interrupt.<s2>  This reduces the
        function's overhead and thus speeds up your application.<s2> This
        function's name is <cfont>Crypt_AES_Decrypt_Dyn<efont>, however you
        should not use this function  directly.<s2> Instead you should add
        the define <cfont>TCPIP_DYN_LINK<efont> to your program before 
        including the CLIB's header file(s), as follows:<nl>
        <ul><nl>
            <cfont>#define TCPIP_DYN_LINK<nl>
            #include <lt>clib.h<gt><efont><nl>
        <ule><nl>
        This compilation switch will map the original function's name
        to the dynamic link version.<s2>  In this manner, you can easily
        switch existing programs over to the 
        <linkto>../../tcpipapi.htm#0xAC0x00<linkmid>dynamic link<linktail> API.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.11 | V1.00
 @target_clib V2.08
*/
int Crypt_AES_Decrypt (const Crypt_AES_Context *aescontext,
                       const void far * in,
                       void far * out)
{
  _DX = FP_SEG(aescontext);
  _SI = FP_OFF(aescontext);
  _ES = FP_SEG(in);
  _DI = FP_OFF(in);
  _CX = FP_SEG(out);
  _BX = FP_OFF(out);
  _AL = 4;
  _AH = CRYPT_CIPHER;
  asm { int TCPIPVECT  } ;
  return   _DX ;
}
#endif

/**************************************************************************/
//end CRYPT.c
/*************************************************************************/

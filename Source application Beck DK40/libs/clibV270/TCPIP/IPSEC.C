/*******************************************************************************
*
* (c) 2006-2007 by BECK IPC GmbH
* http://www.beck-ipc.com
*
********************************************************************************
*
* Module:    ipsec.c
* Function:  IP Security CLIB-API
*
********************************************************************************
*
* $Header: IPSEC.C, 21, 12.11.2008 12:51:05, Andre Pribil$
*
*******************************************************************************/



#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <common.h>
#include "config.h"
#include <ipsec.h>


#include "TCPPRIV.H"


/*******************************************************************************
* Constants
*******************************************************************************/
#define IPSEC_ADD_POLICY            ((IPSEC_VECTORS << 8) | 0)
#define IPSEC_CLEAR_POLICY          ((IPSEC_VECTORS << 8) | 1)
#define IPSEC_ADD_PRESHARED_KEY     ((IPSEC_VECTORS << 8) | 2)
#define IPSEC_REMOVE_PRESHARED_KEY  ((IPSEC_VECTORS << 8) | 3)
#define IPSEC_CLEAR_PRESHARED_KEYS  ((IPSEC_VECTORS << 8) | 4)
#define IPSEC_START                 ((IPSEC_VECTORS << 8) | 5)
#define IPSEC_STATUS                ((IPSEC_VECTORS << 8) | 6)
#define IPSEC_SET_OPTIONS           ((IPSEC_VECTORS << 8) | 7)
#define IPSEC_IKE_PHASE1_SET        ((IPSEC_VECTORS << 8) | 8)
#define IPSEC_IKE_PHASE1_DELETE     ((IPSEC_VECTORS << 8) | 9)
#define IPSEC_RESTORE_POLICY        ((IPSEC_VECTORS << 8) | 10)

/*

 @doc DOC_INDEX
 ---------------------------------------------------------------
 IP Security API Table of Contents
 ---------------------------------------------------------------
 @clibidx  <tab><cfont>#include <InBraces IPsec\.H><efont>
     |
  <ul>
  <li>IP Security <linkto>../../ipsecover.htm<linkmid>over view<linktail><nl>
  <li>IP Security <linkto>../../ipsecstruc.htm<linkmid>data structures<linktail><nl>
  <li>IP Security/IKE <linkto>../../IKEerr.htm<linkmid>error codes<linktail><nl>
  <li>IPsec <linkto>../../ipsecBench.htm<linkmid>timing measurements<linktail><nl>
  <li>Known <linkto>../../ipsecNotes.htm<linkmid>problems<linktail> with implementation.<nl>
      <li> TCP/IP C-Library <linkto>lib_index.htm<linkmid>Main List<linktail>  <nl>
  <ule>

 @libcat1  Configuration | ipsec05 | IPsec_Start | Start IP Security running |
 @libcat1  Configuration | ipsec07 | IPsec_Set_Option | Set IPsec/IKE Options |
 @libcat1  Configuration | ipsec00 | IPsec_Add_Policy | Add Policies |
 @libcat1  Configuration | ipsec0A | IPsec_Restore_Policy | Read Policy file |
 @libcat1  Configuration | ipsecX1 | IPsec_Store_Policy | Write Policy file |
 @libcat1  Configuration | ipsec01 | IPsec_Clear_Policy | Clear Policies |
 @libcat1  Configuration | ipsec06 | IPsec_Status | Check state |
 @libcat1  Configuration | ipsec06I | IPsec_IKE_Status | Check IKE state |

 @libcat2  IKE | ipsec08 | IPsec_IKE_Phase1_Set | Add a phase 1 transform |
 @libcat2  IKE | ipsec09 | IPsec_IKE_Phase1_Delete | Remove a phase 1 transform |

 @libcat3  Preshared Key | ipsec02 | IPsec_Add_Preshared_Key | Add a preshared key |
 @libcat3  Preshared Key | ipsec03 | IPsec_Remove_Preshared_Key | Remove a preshared key |
 @libcat3  Preshared Key | ipsec04 | IPsec_Clear_Preshared_Keys | Clear out all preshared keys |

  @normal
*/

/*
 // Note:  The DOCLIST.EXE tool used by the C-Library HTML build process reacts
 //  to the token "#DOCLIST:" when it appears as the first non-white space
 //  on a line.  The tool transfers the text which follows into the 
 //  BeckCLib.LST file that is used for the context sensitive help.
 //
 // Another Note:  The *IPSec indicates that any names that start with
 //      IPSec and do not match any other name in our list should lead
 //      to the HTML page stated after the *IPSec.
 //
 //      The links to data structures are duplicated here to cover
 //      for older versions of Beck help invokers which could not
 //      handle the anchor suffix, like #tIPSEC_ADDR.


 #DOCLIST:*IPSec CLIB\TCPIP\ipsec_index.htm
 #DOCLIST:sIPSEC_ADDR ipsecstruc.htm#tIPSEC_ADDR
 #DOCLIST:sIPSEC_ADDR ipsecstruc.htm
 #DOCLIST:sIPSEC_FILE_HEADER ipsecstruc.htm#tIPSEC_FILE_HEADER
 #DOCLIST:sIPSEC_FILE_HEADER ipsecstruc.htm
 #DOCLIST:sIPSEC_POLICY_CONTENT ipsecstruc.htm#tIPSEC_POLICY_CONTENT
 #DOCLIST:sIPSEC_POLICY_CONTENT ipsecstruc.htm
 #DOCLIST:sIPSEC_POLICY_PAIR ipsecstruc.htm#tIPSEC_POLICY_PAIR
 #DOCLIST:sIPSEC_POLICY_PAIR ipsecstruc.htm
 #DOCLIST:sIPSEC_POLICY_SELECTOR ipsecstruc.htm#tIPSEC_POLICY_SELECTOR
 #DOCLIST:sIPSEC_POLICY_SELECTOR ipsecstruc.htm
 #DOCLIST:sIPSEC_TKE_PHASE1 ipsecstruc.htm#tIPSEC_TKE_PHASE1
 #DOCLIST:sIPSEC_TKE_PHASE1 ipsecstruc.htm
 #DOCLIST:sIPSEC_TUNNEL ipsecstruc.htm#tIPSEC_TUNNEL
 #DOCLIST:sIPSEC_TUNNEL ipsecstruc.htm

 #DOCLIST:tIPSEC_ADDR ipsecstruc.htm#tIPSEC_ADDR
 #DOCLIST:tIPSEC_ADDR ipsecstruc.htm
 #DOCLIST:tIPSEC_FILE_HEADER ipsecstruc.htm#tIPSEC_FILE_HEADER
 #DOCLIST:tIPSEC_FILE_HEADER ipsecstruc.htm
 #DOCLIST:tIPSEC_POLICY_CONTENT ipsecstruc.htm#tIPSEC_POLICY_CONTENT
 #DOCLIST:tIPSEC_POLICY_CONTENT ipsecstruc.htm
 #DOCLIST:tIPSEC_POLICY_PAIR ipsecstruc.htm#tIPSEC_POLICY_PAIR
 #DOCLIST:tIPSEC_POLICY_PAIR ipsecstruc.htm
 #DOCLIST:tIPSEC_POLICY_SELECTOR ipsecstruc.htm#tIPSEC_POLICY_SELECTOR
 #DOCLIST:tIPSEC_POLICY_SELECTOR ipsecstruc.htm
 #DOCLIST:tIPSEC_TKE_PHASE1 ipsecstruc.htm#tIPSEC_TKE_PHASE1
 #DOCLIST:tIPSEC_TKE_PHASE1 ipsecstruc.htm
 #DOCLIST:tIPSEC_TUNNEL ipsecstruc.htm#tIPSEC_TUNNEL
 #DOCLIST:tIPSEC_TUNNEL ipsecstruc.htm


*/


/*******************************************************************************
* IPsec_Add_Policy() 
*******************************************************************************/
#ifdef _ipsec00_
/*
  @doc DOC_ipsec00_

  @clibSub  IPsec_Add_Policy |  ipsec_index.htm |
         This function appends the list of policies in affect for the
         IP Security. |
         <cfont>int IPsec_Add_Policy(const tIPSEC_POLICY_PAIR  *pairs,<nl>
         <tab><tab><tab><tab><tab> const tIPSEC_POLICY_SELECTOR *selectors,<nl>
         <tab><tab><tab><tab><tab> const tIPSEC_POLICY_CONTENT  *content,<nl>
         <tab><tab><tab><tab><tab> int  pair_cnt) ;<efont><nl>  |
  @parm void * | pairs |
        An array of 
        <linkto>../../ipsecstruc.htm#tIPSEC_POLICY_PAIR<linkmid>tIPSEC_POLICY_PAIR<linktail> 
        data structures which map 
        <cfont>tIPSEC_POLICY_SELECTOR<efont> structures to their
        corresponding <cfont>tIPSEC_POLICY_CONTENT<efont> structure.
  @parm void far * | selectors |
        An array of 
         <linkto>../../ipsecstruc.htm#tIPSEC_POLICY_SELECTOR<linkmid>tIPSEC_POLICY_SELECTOR<linktail> 
       that will be used to select IP Security policies to be applied
        to IP traffic.
  @parm void far * | content |
        An array of 
         <linkto>../../ipsecstruc.htm#tIPSEC_POLICY_CONTENT<linkmid>tIPSEC_POLICY_CONTENT<linktail> 
        that specify IP Security policies to be applied
        to IP traffic.
  @parm int | pair_cnt |
        The number of data structures listed in the array at
        <cfont>pairs<efont>.
  @rdesc <linkto>../../iperrlst.htm<linkmid>Error code<linktail>,
        zero on success
  @comm
         The IP security must be 
         <linkto>ipsec05.htm<linkmid>started<linktail> prior to using this API.<nl>
         <nl>
         The 
         <linkto>../../ipsecstruc.htm#tIPSEC_POLICY_PAIR<linkmid>tIPSEC_POLICY_PAIR<linktail>
         structures at <cfont>pairs<efont> are used to connect the members of the other two
         structure arrays, mapping policy selectors to policy content.<s2>
         Care must be taken to assure that these indexes map to existing structures
         within these two arrays.<nl>
         <nl>
         Following return from this API, the user data referenced is no longer
         required and need not be static.<s2>  The system has copied this 
         information into its IPsec policy database.<nl>
         <nl>
         Policies are selected with a search through the database which
         stops at the first entry whose selector matches some specified
         conditions.<s2>  This search is performed in the reverse order
         in which policies are added.<s2>  Newest policies are checked first.<s2>
         Policies are added starting at the top of the list of <cfont>pairs<efont>.<s2>
         Consequently, the policy pairs listed last are selected ahead of
         the policy pairs listed first.<s2>  So catch all policies for bypass
         or discard should therefore be listed first.<nl>
         <nl>
         When this API is called more than once without an intervening 
         <linkto>ipsec01.htm<linkmid>IPsec_Clear_Policy()<linktail> call,
         the policies from the most recent call take precedence over any
         earlier call's policies.<s2> Again, newest policies are checked
         first.<nl>
         <nl>
  @Also  ipsec01.htm | IPsec_Clear_Policy() |
         ipsecX1.htm | IPsec_Store_Policy() |
          | 
  @Also  ipsec0A.htm | IPsec_Restore_Policy() |
          |  |
          | 
  @rtos  This library function invokes a RTOS 
         <linkto>../../tcpipapi.htm#0xAC0xCF<linkmid>software<linktail>
         interrupt.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.07 | V1.00
  @target_clib V2.06
*/
int IPsec_Add_Policy (const tIPSEC_POLICY_PAIR     *pairs,
                      const tIPSEC_POLICY_SELECTOR *selectors,
                      const tIPSEC_POLICY_CONTENT  *content,
                      int  pair_cnt)
{
    _CX = pair_cnt ;
    _DX = FP_SEG(content) ;
    _SI = FP_OFF(content) ;
    _ES = FP_SEG(selectors) ;
    _DI = FP_OFF(selectors) ;
    asm { push DS } ;   // Compiler did not save our DS, so do so explicitly.
    _BX = FP_OFF(pairs) ;
    _DS = FP_SEG(pairs) ;

    _AX = IPSEC_ADD_POLICY ;
    asm { int TCPIPVECT  } ;

    asm { pop DS } ;
    
    return _AX ;
}
#endif


/*******************************************************************************
* IPsec_Clear_Policy()
*******************************************************************************/
#ifdef _ipsec01_
/*
  @doc DOC_ipsec01_

  @clibSub  IPsec_Clear_Policy | ipsec_index.htm |
         This function clears the list of policies in affect for the
         IP Security. |
         <cfont>int IPsec_Clear_Policy(void) ;<efont><nl>  |
  @parm int | -- none -- |
  @rdesc <linkto>../../iperrlst.htm<linkmid>Error code<linktail>,
        zero on success
  @comm
         The IP security must be 
         <linkto>ipsec05.htm<linkmid>started<linktail> prior to using this API.<nl>
         <nl>
         A default policy of BYPASS for all IP addresses will be
         used following this action.<nl>
  @Also  ipsec00.htm | IPsec_Add_Policy() |
         ipsec07.htm  | IPsec_Set_Option() |
          | 
  @rtos  This library function invokes a RTOS software interrupt.<s2>
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0xCF<linkmid>IPSEC_VECTORS<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.07 | V1.00
  @target_clib V2.06
*/
int IPsec_Clear_Policy (void)
{

    _AX = IPSEC_CLEAR_POLICY ;
    asm { int TCPIPVECT  } ;

    return _AX ;
}
#endif


/*******************************************************************************
* IPsec_Add_Preshared_Key()
*******************************************************************************/
#ifdef _ipsec02_
/*
  @doc DOC_ipsec02_

  @clibSub  IPsec_Add_Preshared_Key | ipsec_index.htm |
         This function adds a preshared key for use with the
         specified remote IP during Internet Key Exchange (IKE). |
         <cfont>int IPsec_Add_Preshared_Key(<nl>
         <tab><tab><tab><tab><tab> const char *remote_ip,<nl>
         <tab><tab><tab><tab><tab> const char *preshared_key) ;<efont><nl>  |
  @parm void * | remote_ip |
        Zero terminated ASCII string specifying the IP address of
        the remote side.
  @parm void * | preshared_key |
        Zero terminated ASCII string specifying the preshared key.
  @rdesc <linkto>../../iperrlst.htm<linkmid>Error code<linktail>,
        zero on success
  @comm
         The IP security must be 
         <linkto>ipsec05.htm<linkmid>started<linktail> 
         prior to using this API.<nl>
         <nl>
         The IP address may be either IPv4 of IPv6.<s2> Domain names
         must be 
         <linkto>../TCPIP/tcp30.htm<linkmid>resolved<linktail>
         first by the caller and are not supported
         by this API.
  @Also  ipsec03.htm | IPsec_Remove_Preshared_Key() |
          tcp30.htm |  getHostByName() |
          |
  @Also  ipsec04.htm | IPsec_Clear_Preshared_Keys() |
          |  |
          |  
 @related  | ../../config.htm#IPSEC_PRESHARED_KEY | PRESHARED_KEY | definition
       in CHIP.INI file
  @rtos  This library function invokes a RTOS software interrupt.<s2>
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0xCF<linkmid>IPSEC_VECTORS<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.07 | V1.00
  @target_clib V2.06
*/
int IPsec_Add_Preshared_Key (const char *remote_ip, 
                             const char *preshared_key)
{
    _DX = FP_SEG(preshared_key) ;
    _SI = FP_OFF(preshared_key) ;
    _ES = FP_SEG(remote_ip) ;
    _BX = FP_OFF(remote_ip) ;
    _AX = IPSEC_ADD_PRESHARED_KEY ;
    asm { int TCPIPVECT  } ;

    return _AX ;
}
#endif


/*******************************************************************************
* IPsec_Remove_Preshared_Key()
*******************************************************************************/
#ifdef _ipsec03_
/*
  @doc DOC_ipsec03_

  @clibSub  IPsec_Remove_Preshared_Key | ipsec_index.htm |
         This function removes any preshared key that had been 
         established for the specified remote IP. |
         <cfont>int IPsec_Remove_Preshared_Key(<nl>
         <tab><tab><tab><tab><tab> const char *remote_ip) ;<efont><nl>  |
  @parm void * | remote_ip |
        Zero terminated ASCII string specifying the IP address of
        the remote side.<s2> This string must match what was used
        when adding this key.<nl>
  @rdesc <linkto>../../iperrlst.htm<linkmid>Error code<linktail>,
        zero on success
  @comm
         The IP security must be 
         <linkto>ipsec05.htm<linkmid>started<linktail> 
         prior to using this API.<nl>
         <nl>
         The IP address may be either IPv4 of IPv6.<s2> Domain names
         must be 
         <linkto>../TCPIP/tcp30.htm<linkmid>resolved<linktail>
         first by the caller and are not supported
         by this API.
  @Also  ipsec02.htm | IPsec_Add_Preshared_Key() |
          tcp30.htm |  getHostByName() |
          |
  @Also  ipsec04.htm | IPsec_Clear_Preshared_Keys() |
          |  |
          |  
 @related  | ../../config.htm#IPSEC_PRESHARED_KEY | PRESHARED_KEY | definition
       in CHIP.INI file
  @rtos  This library function invokes a RTOS software interrupt.<s2>
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0xCF<linkmid>IPSEC_VECTORS<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.07 | V1.00
  @target_clib V2.06
*/
int IPsec_Remove_Preshared_Key (const char *remote_ip)
{
    _ES = FP_SEG(remote_ip) ;
    _BX = FP_OFF(remote_ip) ;
    _AX = IPSEC_REMOVE_PRESHARED_KEY ;
    asm { int TCPIPVECT  } ;

    return _AX ;
}
#endif

/*******************************************************************************
* IPsec_Clear_Preshared_Keys()
*******************************************************************************/
#ifdef _ipsec04_
/*
  @doc DOC_ipsec04_

  @clibSub  IPsec_Clear_Preshared_Keys | ipsec_index.htm |
         Clear all preshared keys from the database. |
         <cfont>void IPsec_Clear_Preshared_Keys(void) ;<efont><nl>  |
  @parm void * | -- none -- |
  @rdesc -- none --
  @Also  ipsec02.htm | IPsec_Add_Preshared_Key() |
          |  |
          |  
  @Also  ipsec03.htm | IPsec_Remove_Preshared_Key() |
          |  |
          |  
 @related IPSEC  | ../../config.htm#IPSEC_ENABLE | ENABLE | from CHIP.INI file
  @rtos  This library function invokes a RTOS software interrupt.<s2>
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0xCF<linkmid>IPSEC_VECTORS<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.07 | V1.00
  @target_clib V2.06
*/
void IPsec_Clear_Preshared_Keys (void)
{
    _AX = IPSEC_CLEAR_PRESHARED_KEYS ;
    asm { int TCPIPVECT  } ;
}
#endif

/*******************************************************************************
* IPsec_Start()
*******************************************************************************/
#ifdef _ipsec05_
/*
  @doc DOC_ipsec05_

  @clibSub  IPsec_Start | ipsec_index.htm |
         This function activates the IP security function and
         IKE task within the system's TCP/IP stack. |
         <cfont>int IPsec_Start(void) ;<efont><nl>  |
  @parm void * | -- none -- |
  @rdesc  error code, zero on success.<s2> Otherwise on failure:<nl>
         <ul>
         less than 5000:<s2>  Look
        <linkto>../../iperrlst.htm<linkmid>here<linktail> for error code
        description.<nl>
        <ule><nl>
        <ul>
        5000 <lt>= error code <lt> 6000:<s2>  The 
        <linkto>../../config.htm#IPSEC_POLICY_FILE<linkmid>POLICY_FILE<linktail>
        restore operation has failed.<s2> Subtract 5100 from this
        value and check 
        <linkto>ipsec0A.htm#errors<linkmid>here<linktail> for
        resulting error value.<nl>
        <ule><nl>
        <ul>
        6000 <lt>= error code <lt> 7000:<s2>  The 
        <linkto>../../config.htm#IPSEC_PRESHARED_KEY<linkmid>PRESHARED_KEY<linktail>
        loading failed.<s2> Subtract 6100 from this error code and look
        <linkto>../../iperrlst.htm<linkmid>here<linktail> for a description
        of the resulting error code.<nl>
        <ule>
   @comm  Alternatively, the IP Security can be started by
       setting the IPSEC 
       <linkto>../../config.htm#IPSEC_ENABLE<linkmid>ENABLE<linktail>
       value in the CHIP.INI or by using the 
       <linkto>../../command.htm#IKE<linkmid>IKE<linktail> START
       console command.
  @Also  ipsec00.htm | IPsec_Add_Policy() |
         ipsec06.htm | IPsec_Status() |
         ipsec07.htm  | IPsec_Set_Option() 
  @Also  ipsec0A.htm |  IPsec_Restore_Policy() |
         ipsec08.htm | IPsec_IKE_Phase1_Set() |
          |  
 @related IPSEC  | ../../config.htm#IPSEC_ENABLE | ENABLE | from CHIP.INI file
 @related  | ../../command.htm#IKE | IKE | command
  @rtos  This library function invokes a RTOS software interrupt.<s2>
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0xCF<linkmid>IPSEC_VECTORS<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.07 | V1.00
  @target_clib V2.06
*/
int IPsec_Start (void)
{
    _AX = IPSEC_START ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif

/*******************************************************************************
* IPsec_Status()
*******************************************************************************/
#ifdef _ipsec06_
/*
  @doc DOC_ipsec06_

  @clibSub  IPsec_Status | ipsec_index.htm |
         Read out the status of the IP security function within
         the system's TCP/IP stack. |
         <cfont>int IPsec_Status(int *error_code) ;<efont><nl>  |
  @parm void * | error_code |  Optional output parameter is the
     <linkto>../../iperrlst.htm<linkmid>error<linktail> code 
     reported when IP Security initialization was not successful.<s2>
     Set this parameter to NULL if not interested.
  @rdesc Enumerator:<nl>
  <ul><nl>
        IPSEC_OFF (0) - Not <linkto>ipsec05.htm<linkmid>started<linktail> yet.<nl>
        IPSEC_FAILED  (1) - Startup failed, perhaps insufficient 
            <linkto>../../config.htm#IP_TCPIPMEM<linkmid>memory<linktail>.<nl>
        IPSEC_READY (2) -  Ready for operation.<nl>
    <ule>

  @comm  The optional error code value returned to <cfont>error_code<efont>
     will be non-zero if the reported state is <cfont>IPSEC_FAILED<efont>.<nl>
  @Also  ipsec05.htm | IPsec_Start() |
         ipsec06I.htm |  IPsec_IKE_Status() |
           |  
  @rtos  This library function invokes a RTOS software interrupt.<s2>
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0xCF<linkmid>IPSEC_VECTORS<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.07 | V1.00
  @target_clib V2.06
*/
int IPsec_Status (int *error_code)
{
    int status ;
    int bx_error ;
    // The only reason we set _DX and _CX here is to signal the
    //  compiler to not use this register for its own
    //  purposes.  The compiler was storing error_code
    //  pointer here for small memory model, and then
    //  losing this vector due to the SWI.
    _CX = _DX = _AX = IPSEC_STATUS ;
    asm { int TCPIPVECT  } ;
    status   = _AX ;
    bx_error = _BX ;
    if (error_code != 0)            // Pointer supplied?
    {
        *error_code = bx_error ;
    }
    return status ;
}
#endif

/*******************************************************************************
* IPsec_IKE_Status()
*******************************************************************************/
#ifdef _ipsec06I_
/*
  @doc DOC_ipsec06I_

  @clibSub  IPsec_IKE_Status | ipsec_index.htm |
         Read out the status of the IP security 
         Internet Key Exchange (IKE) function within
         the system's TCP/IP stack. |
         <cfont>int IPsec_IKE_Status(void) ;<efont><nl>  |
  @parm void * |  |  -- none --
  @rdesc IKE <linkto>../../IKEerr.htm<linkmid>error code<linktail>
  @comm  The returned error code will indicate zero if IP
      security and IKE have not yet been activated.<nl>
  @Also  ipsec05.htm | IPsec_Start() |
         ipsec06.htm |  IPsec_Status() |
           |  
  @rtos  This library function invokes a RTOS software interrupt.<s2>
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0xCF<linkmid>IPSEC_VECTORS<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.15 | V1.00
  @target_clib V2.10
*/
int IPsec_IKE_Status (void)
{
    _AX = IPSEC_STATUS ;
    asm { int TCPIPVECT  } ;
    return _CX ;
}
#endif

/*******************************************************************************
* IPsec_Set_Option()
*******************************************************************************/
#ifdef _ipsec07_
/*
  @doc DOC_ipsec07_

  @clibSub  IPsec_Set_Option | ipsec_index.htm |
         Set options controlling IPsec/IKE behavior. |
         <cfont>int IPsec_Set_Option(unsigned int option,<nl>
         <tab><tab><tab><tab><tab> unsigned int value) ;<efont><nl>  |
  @parm int | option |  An enumerator that specifies which
     option to set.
  @parm int | value | The options value to be set.
  @rdesc 0:<s2> Success<nl>
        -1:<s2> Failure, invalid option or value
  @comm  This function allows the IP Security and Internet Key Exchange 
    (IKE) protocol options to be adjusted at run-time.<s2> The
    IP Security function must have been started either from the
    <linkto>../../config.htm#IPSEC_ENABLE<linkmid>CHIP.INI<linktail> or 
    <linkto>ipsec05.htm<linkmid>IPsec_Start()<linktail> API before using 
    this API.<nl>
    <nl>
    For all options here which have a Boolean sense, a value 1 enables
    the option and 0 disables the option.<nl>
    <nl>
    The options available are:<nl>
    <ul><nl>
       <cfont>IPSEC_OPT_ANTIREPLAY<efont>= 1<s2> Specifies
         if anti-replay is used or not.<s2> By default anti-replay is
         used (value = 1).<nl>
         <nl>
       <cfont>IPSEC_OPT_PFSKEY<efont>= 2<s2> Specifies if Perfect 
            Forward Secrecy (PFS) is used of not.<s2> By default PFS is
         used (value = 1).<nl>
         <nl>
       <cfont>IPSEC_OPT_AGGRESS<efont>= 3<s2> Specifies if aggressive
            mode is used in IKE phase 1.<s2> By default this option
            is not selected (value = 0).<nl>
         <nl>
       <cfont>IPSEC_OPT_AGGRESSDHGROUP<efont>= 4<s2> Specifies which
        Diffie-Hellman group is going to be used in aggressive mode.<s2>
        Value must be 1, 2, 5 or 14.<s2> The default is group 2 
        (using 1024 bit prime number).<nl>
         <nl>
       <cfont>IPSEC_OPT_INITCONTACT<efont>= 5<s2> Specifies if Initial
        Contact message is to be sent to the peer or not.<s2> Value 1
        will enable IKE to send Initial contact upon finishing IKE
        phase 1 negotiation.<s2> Value 0 will disable it.<s2> By
        default this option is enabled.<nl>
         <nl>
       <cfont>IPSEC_OPT_ICMPBYPASS<efont>= 9<s2> Specifies if the
          policy check for incoming ICMP packets is bypassed or not.<s2>
          Value 1 will bypass the incoming policy check for incoming 
          ICMP packets.<s2> By default this option is selected
          (value = 1).<nl>
         <nl>
       <cfont>IPSEC_OPT_ICMPSRCCHKBYPASS<efont>= 10<s2> Specifies if ICMP
            source address should be checked against IPsec policy or not.<s2>
            Value 1 will bypass this check.<s2> By default this option
            is not selected (value = 0).
         <nl>
       <cfont>IPSEC_OPT_ICMP6NDMLDBYPASS<efont>= 11<s2> Specifies if
            ICMPv6 packets bypass IPsec policy or not.<s2>
            Value 1 will bypass IPsec.<s2> By default this option
            is selected (value = 1).<nl>
         <nl>
       <cfont>IPSEC_OPT_NESTIKE_BYPASS<efont>= 12<s2> Specifies if
            nested IKE packets are to be checked against IPsec
            policy or not.<s2>
            Value 1 will bypass all IKE packets.<s2> Value 0 will force
            all IKE packets to go through IPsec policy checking.<s2> By
            default this option is not selected (value = 0).<nl>
         <nl>
       <cfont>IPSEC_OPT_DFBIT<efont>= 13<s2> Specifies how to set 
            the outside IP header’s <i>Dont Fragment<ie> bit if 
            a tunnel is used.<s2> Valid values are:<nl>
            <ul>
                <cfont>IPSEC_VAL_DFBIT_CLEAR<efont> = 0<nl>
                <cfont>IPSEC_VAL_DFBIT_SET<efont> = 1<nl>
                <cfont>IPSEC_VAL_DFBIT_COPY<efont> = 2<nl>
            <ule>
            By default, the <cfont>IPSEC_VAL_DFBIT_COPY<efont> = 2
            value is used.<nl>
    <ule>
  @Also  ipsec05.htm | IPsec_Start() |
           | |
           | 
  @related  | ../../config.htm#IPSEC_IKE_PH1_AGGRESSIVE | IKE_PH1_AGGRESSIVE | definition
       in CHIP.INI file
  @related  | ../../config.htm#IPSEC_IKE_PH2_PFS | IKE_PH2_PFS | definition
       in CHIP.INI file
  @rtos  This library function invokes a RTOS software interrupt.<s2>
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0xCF<linkmid>IPSEC_VECTORS<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.07 | V1.00
  @target_clib V2.06
*/
int IPsec_Set_Option (unsigned int option, unsigned int value)
{
    _CX = value ;
    _BX = option ;
    _AX = IPSEC_SET_OPTIONS ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif

/*******************************************************************************
* IPsec_IKE_Phase1_Set()
*******************************************************************************/
#ifdef _ipsec08_
/*
  @doc DOC_ipsec08_

  @clibSub  IPsec_IKE_Phase1_Set | ipsec_index.htm |
         Specify a transform for IKE's phase 1 proposal. |
         <cfont>int IPsec_IKE_Phase1_Set(int index,<nl>
         <tab><tab><tab><tab> const tIPSEC_TKE_PHASE1 *param) ;<efont><nl>  |
  @parm int | index |  Index 0 or 1 selects which of the two phase 1
        IKE transforms is to be set.
  @parm void * | param |  Pointer to a
     <linkto>../../ipsecstruc.htm#tIPSEC_TKE_PHASE1<linkmid>tIPSEC_TKE_PHASE1<linktail>
            data structure used to specify the transform's parameters.<s2> A
            copy of this data is made inside this API, so the caller's image
            need not persist beyond the return from this function.
  @rdesc <linkto>../../iperrlst.htm<linkmid>error code<linktail>,
        zero on success.<s2>
  @comm  This function adds a user specified phase 1 transform to 
        IKE’s phase 1 proposal.<s2> The user is able to configure up to
        two such transforms.<s2> The most preferred has index 0, the
        less preferred has index 1.<s2> If the user configures either of
        these, the default transform will not be used.<nl>
        <nl>
 <linktag DefaultPhase1>
        When neither of these optional phase1 proposals is set,
        the default transform will be used in the phase 1 proposal.<s2>
        This default transform has the following settings:<nl>
        <ul><nl>
            Encryption Algorithm:<s2> 3DES CBC<nl>
            Hash Algorithm:<tab><tab> SHA1<nl>
            Diffie-Hellman Group:<s2> 2<nl>
            SA Lifetime seconds:<s2> 86400 seconds (=1 day)<nl>
            SA Lifetime kBytes:<s2> 0x10000 kByte (=64 MByte)<nl>
        <ule><nl>
        The default authentication method is
        <linkto>../../CONFIG.htm#IPSEC_PRESHARED_KEY<linkmid>preshared key<linktail>
        unless a local
        <linkto>../../CONFIG.htm#IPSEC_IKE_LOCALCERT<linkmid>certificate<linktail>
        has been specified in the CHIP.INI file.<nl>
        <nl>
        If this API is used to set both of the phase 1 transforms
        available for user control, then the authentication method
        specified in these two transforms must be set the same.<s2>
        Otherwise unpredictable operation may result.<nl>
  @Also  ipsec09.htm | IPsec_IKE_Phase1_Delete() |
          |  |
           |  
  @related  | ../../config.htm#IPSEC_IKE_PH1_AGGRESSIVE | IKE_PH1_AGGRESSIVE | definition
       in CHIP.INI file
  @rtos  This library function invokes a RTOS software interrupt.<s2>
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0xCF<linkmid>IPSEC_VECTORS<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.07 | V1.00
  @target_clib V2.06
*/
int IPsec_IKE_Phase1_Set (int index, const tIPSEC_TKE_PHASE1 *param)
{
    _CX = index ;
    _ES = FP_SEG(param) ;
    _BX = FP_OFF(param) ;

    _AX = IPSEC_IKE_PHASE1_SET ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif

/*******************************************************************************
* IPsec_IKE_Phase1_Delete()
*******************************************************************************/
#ifdef _ipsec09_
/*
  @doc DOC_ipsec09_

  @clibSub  IPsec_IKE_Phase1_Delete | ipsec_index.htm |
       Remove one of the IKE phase 1 transforms. |
         <cfont>int IPsec_IKE_Phase1_Delete(int index) ;<efont><nl>  |
  @parm int | index |  Index 0 or 1 selects which of two phase 1
         IKE transforms is to be deleted.
  @rdesc <linkto>../../iperrlst.htm<linkmid>error code<linktail>,
        zero on success.<s2>
  @comm  This function removes one of the two IKE phase 1 transforms
      which the user can set.<s2>
      If both user settable phase 1 transforms are not present,
      then the 
      <linkto>ipsec08.htm#DefaultPhase1<linkmid>default<linktail>
      transform will be used.<nl>
  @Also  ipsec08.htm | IPsec_IKE_Phase1_Set() |
          |  |
           |  
  @rtos  This library function invokes a RTOS software interrupt.<s2>
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0xCF<linkmid>IPSEC_VECTORS<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.07 | V1.00
  @target_clib V2.06
*/
int IPsec_IKE_Phase1_Delete (int index)
{
    _CX = index ;
    _AX = IPSEC_IKE_PHASE1_DELETE ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif

/*******************************************************************************
* IPsec_Restore_Policy()
*******************************************************************************/
#ifdef _ipsec0A_
/*
  @doc DOC_ipsec0A_

  @clibSub  IPsec_Restore_Policy | ipsec_index.htm |
       Restore IP security policy and/or preshared keys from file. |
         <cfont>int IPsec_Restore_Policy(const char *filename) ;<efont><nl>  |
  @parm int | filename |  Path to binary file containing IP
      security policy and preshared keys.
  <linktag errors>
  @rdesc Zero on success<nl>
          On failure non-zero indicates error:<nl>
          <ul>
          -3 : <s2> Policy file exceeded 64 Kbyte size limit<nl>
          -4 : <s2> Work buffer memory allocation failed<nl>
          -5 : <s2> Invalid policy file contents<nl>
          202 :<s2> Policy file open failed<nl>
          Between 1000 and 1999 :<nl>
          <ul>Policy add operation failed.<s2> Subtract 1000 from
             this error code and look  
            <linkto>../../iperrlst.htm<linkmid>here<linktail>
            for resulting error code description.<nl>
          <ule>
          Between 2000 and 2999:<nl>
          <ul>Preshared key add operation failed.<s2> Subtract 
             2000 from this error code and look  
            <linkto>../../iperrlst.htm<linkmid>here<linktail>
            for resulting error code description.<nl>
          <ule>
          <ule>
  @comm  
         The IP security must be 
         <linkto>ipsec05.htm<linkmid>started<linktail> 
         prior to using this API.<nl>
         <nl>
    This API allows IP security policy and preshared keys to be
  set based on a stored binary file's contents.<s2> The file can be created
  with the <linkto>ipsecX1.htm<linkmid>IPsec_Store_Policy()<linktail>
  library function, or other tools conforming to the  
  <linkto>../../ipsecstruc.htm#tIPSEC_FILE_HEADER<linkmid>specified<linktail>
  format.<nl>
  <nl>
  The policies from the file are appended to any which are already
  in affect.<s2>  The 
  <linkto>ipsec01.htm<linkmid>IPsec_Clear_Policy()<linktail>
  can be used before this API for a fresh start.<nl>
  <nl>
  An alternative way to load policy from file is to use the
  <linkto>../../config.htm#IPSEC_POLICY_FILE<linkmid>POLICY_FILE<linktail>
  entry in the CHIP.INI file.
  @Also  ipsec00.htm | IPsec_Add_Policy() |
         ipsecX1.htm | IPsec_Store_Policy() |
          |  
  @Also  ipsec01.htm | IPsec_Clear_Policy() |
         | |
          |  
  @rtos  This library function invokes a RTOS software interrupt.<s2>
         Refer to the RTOS API function
         <linkto>../../tcpipapi.htm#0xAC0xCF<linkmid>IPSEC_VECTORS<linktail>
         for more details.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.07 | V1.00
  @target_clib V2.06
*/
int IPsec_Restore_Policy (const char *filename)
{
    _BX = FP_OFF(filename) ;
    _ES = FP_SEG(filename) ;
    _AX = IPSEC_RESTORE_POLICY ;
    asm { int TCPIPVECT  } ;
    return _AX ;
}
#endif


/*******************************************************************************
* IPsec_Store_Policies()
*******************************************************************************/
#ifdef _ipsecX1_
/*
  @doc DOC_ipsecX1_

  @clibSub  IPsec_Store_Policy | ipsec_index.htm |
       Create a binary file containing IP Security policy and/or preshared
       keys. |
         <cfont>int IPsec_Store_Policy(<nl>
         <tab><tab>const char<tab><tab><tab><tab><s2> *file_name,<nl>
         <tab><tab>const tIPSEC_POLICY_SELECTOR *selectors,<nl>
         <tab><tab>unsigned int<tab><tab><tab><tab><s1> selector_count,<nl>
         <tab><tab>const tIPSEC_POLICY_CONTENT<s1>  *contents,<nl>
         <tab><tab>unsigned int<tab><tab><tab><tab><s1> content_count,<nl>
         <tab><tab>const tIPSEC_POLICY_PAIR<tab> *pairs,<nl>
         <tab><tab>unsigned int<tab><tab><tab><tab><s1>  pair_count,<nl>
         <tab><tab>const char<tab><tab><s2> * const *preshared_keys,<nl>
         <tab><tab>unsigned int<tab><tab><tab><tab><s1>  preshared_key_count);<efont><nl>  |
  @parm int | file_name |  Zero terminated ASCII string specifies
  the path for the binary data file which will be created by this
  library function.
  @parm int | selectors | Points to an array of <cfont>selector_count<efont>
    <linkto>../../ipsecstruc.htm#tIPSEC_POLICY_SELECTOR<linkmid>tIPSEC_POLICY_SELECTOR<linktail>
    data structures to be stored in the file that is created.<nl>
  @parm int | selector_count | Number of
    data structures in array referenced by <cfont>selectors<efont>.<nl>
  @parm int | contents | Points to an array of <cfont>content_count<efont>
    <linkto>../../ipsecstruc.htm#tIPSEC_POLICY_CONTENT<linkmid>tIPSEC_POLICY_CONTENT<linktail>
    data structures to be stored in the file that is created.<nl>
  @parm int | content_count | Number of
    data structures in array referenced by <cfont>contents<efont>.<nl>
  @parm int | pairs | Points to an array of <cfont>pair_count<efont>
    <linkto>../../ipsecstruc.htm#tIPSEC_POLICY_PAIR<linkmid>tIPSEC_POLICY_PAIR<linktail>
    data structures to be stored in the file that is created.<nl>
  @parm int | pair_count | Number of
    data structures in array referenced by <cfont>pairs<efont>.<nl>
  @parm int | preshared_keys | Pointer to an array of ASCIIZ string pointers.<s2> Each
     ASCII string specifies an IP address and preshared key using the same format as the
     <linkto>../../config.htm#IPSEC_PRESHARED_KEY<linkmid>PRESHARED_KEY<linktail> entries in the
     CHIP.INI.<nl>
  @parm int | preshared_key_count | Number of
     pointers to zero terminated ASCII strings listed in 
     array of pointers at <cfont>preshared_keys<efont>.<nl>
  @rdesc Error code:<nl>
  <ul><nl>
     0 - Success, file created without problem.<nl>
     1 - Unable to create the file.<nl>
     2 - File write failed.<nl>
     3 - File exceeded 64K byte limit in size.<nl>
  <ule>
  @comm  This function creates a binary file which can be
    specified in the 
    <linkto>../../config.htm#IPSEC_POLICY_FILE<linkmid>CHIP.INI<linktail>
    to restore IP security policies at start up or passed to the
    <linkto>ipsec0A.htm<linkmid>IPsec_Restore_Policy()<linktail> at run time.<nl>
    <nl>
    These policy files must not exceed 64 Kbyte size.<nl>
    <nl>
    One reason this function
    has been included in the library is to provide users access to
    source code which creates the Beck format binary files that hold
    the IP security policy information, and thereby explicitly documenting
    this binary file's format.<s2> (Note that the source code for these
    C-library functions is available from Beck.)
  @Also  ipsec00.htm | IPsec_Add_Policy() |
         ipsec0A.htm | IPsec_Restore_Policy() |
           |  
  @rtos  This library function uses no @Chip-RTOS API directly.  Indirectly
      the compiler's file I/O C-library functions will access the DOS
      interrupt <linkto>../../dosemu.htm#0x210x3C<linkmid>0x21<linktail> 
      to produce the file.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.07 | V1.00
  @target_clib V2.06
*/

int IPsec_Store_Policy (const char                   *file_name,
                        const tIPSEC_POLICY_SELECTOR *selectors,
                        unsigned int                  selector_count,
                        const tIPSEC_POLICY_CONTENT  *contents,
                        unsigned int                  content_count,
                        const tIPSEC_POLICY_PAIR     *pairs,
                        unsigned int                  pair_count,
                        const char           * const *preshared_keys,
                        unsigned int                  preshared_key_count)
{
    int error_code = 1 ;                // Return value
    FILE *file = fopen(file_name, "w+b") ;
    if (file != NULL)
    {
        error_code = 2 ;                // File write success (assume).
        while (1)   // No actual loop, used only for structured GO-TO
        {
            unsigned int i ;
            unsigned long file_size ;
            tIPSEC_FILE_HEADER header ;
            header.Sanity_Check      = IPSEC_SANE_HEADER ;
            header.File_Version      = IPSEC_FILE_VERSION ;
            header.SelectorCount     = selector_count ;
            header.ContentCount      = content_count ;
            header.PairCount         = pair_count ;
            header.PresharedKeyCount = preshared_key_count ;
            
            if (fwrite(&header, 1, sizeof(header), file) != sizeof(header))
            {
                break ;             // Failed
            }
            file_size = sizeof(header) ;
            if ( fwrite(&selectors[0], sizeof(tIPSEC_POLICY_SELECTOR),
                        selector_count, file)
                 != selector_count)
            {
                break ;             // Failed
            }
            file_size += (unsigned long)sizeof(tIPSEC_POLICY_SELECTOR)
                       * selector_count ;

            if ( fwrite(&contents[0], sizeof(tIPSEC_POLICY_CONTENT), 
                        content_count, file)
                   != content_count)
            {
                break ;             // Failed
            }
            file_size += (unsigned long)sizeof(tIPSEC_POLICY_CONTENT)
                       * content_count ;

            if ( fwrite(&pairs[0], sizeof(tIPSEC_POLICY_PAIR), 
                        pair_count, file)
                  != pair_count)
            {
                break ;             // Failed
            }
            file_size += (unsigned long)sizeof(tIPSEC_POLICY_PAIR)
                       * pair_count ;

            error_code = 0 ;                // Assume success.
            // Append nil terminated preshared key specifier strings
            //  to end of file.
            for (i = 0; i < preshared_key_count ; i++)
            {
                const char *string = preshared_keys[i] ;
                unsigned int len = strlen(string) + 1 ;          // Count NIL char.
                file_size += (unsigned long) len ;
                if ( fwrite(string, 1, len, file) != len)
                {
                    error_code = 2 ;        // Failure
                    break ;
                }    
            }
            if (file_size >= 0x10000)       // Too large?
            {
                error_code = 3 ;
            }
            break ;                         // Exit fake while loop.
        }
        fclose(file) ;
    }
    return error_code ;
}
#endif

// End of file








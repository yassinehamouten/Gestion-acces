/****************************************************************************
* (C) 1999-2007 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module      : CGIAPI.C
* Function    : cgi api functions
* ---------------------------------------------------------------------------

$Header: CGIAPI.C, 37, 12.11.2008 12:50:55, Andre Pribil$

*****************************************************************************/

#include <STDLIB.H>
#include <DOS.H>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h> // for toupper

#include "config.h"
#include "CGIAPI.H"

/*************************************************************************/

/*
 @doc DOC_INDEX
 ---------------------------------------------------------------
 CGI API Table of Contents
 ---------------------------------------------------------------
 @clibidx  <tab><cfont>#include <InBraces CGIAPI\.H><efont> |

 The CGI ("Common Gateway Interface") API provides
 access to the CGI implementation of the IPC@CHIP&reg; Web server.<nl>
 CGI at the IPC@CHIP&reg; provides the possibility to install at the IPC@CHIP&reg; Web server
 own programmed CGI functions. These functions are bound with a fixed name and are executed by
 the Web server task, if a http request with such a fixed name comes in. This mechanism allows
 dynamic usage of the IPC@CHIP&reg; Web server.
 For better understanding of CGI and possibilities for
 using, see description of available program examples at the example link below.<nl>
 <nl>
 <linkto>../../cgiover.htm#File<linkmid>File Upload<linktail>:<nl>
 Also there is a possibility to upload files to the @CHIP's disk.<s2> This does not use the CGI
 interface but the Web server.<s2> Therefore you only need a defined HTML form which sends
 the required data to the @CHIP Web server.<s2> An example can be found in the CGI Example Zip file.
 <nl><nl><bold>Notes:<bolde>
 <ol>
 <li>For test and demonstration purpose two pages are preinstalled at the IPC@CHIP&reg;:<nl>
 a)<bold>main.htm:<bolde> Static html introduction page.<nl>
 b)<bold>chipcfg:<bolde> Dynamic page with system time/date and configuration data of the requested IPC@CHIP&reg;.
 <li>
 For configuring the web server and CGI, see the provided <linkto>../../config.htm#WEBENABLE<linkmid>chip.ini entries<linktail>.
 <li>
 For some useful comments see also under <linkto>../../program.htm<linkmid>Programming notes<linktail><nl>
 <ole>
 @textlinkpara  Web Server  | ../../cgiover.htm | Overview  |
 @textlinkpara  Web Server  | ../../cgifile.htm | File  | Types
  <nl>
 @textlinkpara  CGI API | ../../cgierrs.htm | Error Codes |
 @textlinkpara  CGI API | ../../cgiexamp.htm | Examples | Available
 @textlinkpara  CGI API | ../../cgistruc.htm | Data Structures  |
 
 
 @libcat1  CGI | cgi01 | CGI_Install | Install a CGI function |
 @libcat1  CGI | cgi02 | CGI_Delete | Remove a CGI function |

 @libcat1  CGI | cgi03 | CGI_SetMainPage | Select a new main page |
 @libcat1  CGI | cgi06 | CGI_GetMainPage | Get main page name |

 @libcat1  CGI | cgi0E | CGI_SetMainPagePost | Select a new main page (POST method) |
 @libcat1  CGI | cgi0F | CGI_GetMainPagePost | Get main page name (POST method) |

 @libcat1  CGI | cgi10 | CGI_SetRootDrive | Set Web server's root drive |
 @libcat1  CGI | cgi11 | CGI_GetRootDrive | Get Web server's root drive |

 @libcat1  CGI | cgi04 | CGI_SetRootDir | Set Web server's root directory |
 @libcat1  CGI | cgi05 | CGI_GetRootDir | Get Web server's root directory |

 @libcat1  CGI | cgi14 | CGI_SetCredentials | Set Web server's user names and passwords |
 
 @libcat1  CGI | cgigetarg | CGI_GetArgument | Returns the next available argument |
 @libcat1  CGI | cgiUrlEncode | CGI_UrlEncode | Encodes a URL string |
 @libcat1  CGI | cgiUrlDecode | CGI_UrlDecode | Decodes a URL string |

 @libcat1  CGI | cgigcookie | CGI_GetCookie | Returns the next available cookie |
 @libcat1  CGI | cgiscookie | CGI_SetCookie | Creates a new cookie or modifies an old one |

 @libcat1  CGI | cgi07 | CGI_GetFormItem | <depr> Split a form item into name and value |
 @libcat1  CGI | cgi08 | CGI_GetNextItem | <depr> Return pointer to the next form item |

 @libcat1  CGI | cgi0A | CGI_Install_Func_OnErr    | Install error cgi function |
 @libcat1  CGI | cgi13 | CGI_Install_Func_OnUpload | Install upload cgi function |
 
 @libcat1  CGI | cgi12 | CGI_Enable_Upload | Enable/Disable HTTP file upload | 

 @libcat1  CGI | cgi0B | CGI_Install_MIME_Table | Install a custom MIME table |
 @libcat1  CGI | cgi0C | CGI_Remove_MIME_Table  | Remove the custom MIME table |

 @libcat1  CGI | cgi0D | CGI_Install_ContentEncoding_Table  | Install the custom content-encoding table |
 @libcat1  CGI | cgiRmContentEncoding | CGI_Remove_ContentEncoding_Table  | Remove the custom content-encoding table |

 @libcat1  CGI | cgi15 | CGI_Install_Headers_Table | Install the custom headers table |
 @libcat1  CGI | cgiRmHeaders | CGI_Remove_Headers_Table | Remove the custom headers table |

 @libcat2  SSI | cgi81 | SSI_Set_File_Filter | Set a SSI file filter |
 @libcat2  SSI | cgi82 | SSI_Register_Tag    | Register a SSI tag    |
 @libcat2  SSI | cgi85 | SSI_Deregister_Tag  | Deregister a SSI tag    |
 @libcat2  SSI | cgi83 | SSI_Set_TagLength   | Set the maximum SSI tag length |
 @libcat2  SSI | cgi84 | SSI_Send_Buffer     | Send a buffer over a HTTP connection |
 @libcat2  SSI | cgi86 | SSI_Get_Connection_Params | Get SSI connection parameters |
*/

/*************************************************************************/
//Private defines used internal by that module
/*************************************************************************/
#define CGIVECT       0xAB

// Cookie and argument handling
#define CGI_MAX_COOKIE_SIZE     1024 /* maximal size of the cookie header */

#define CGI_COKNV_END           0    /* no more data                              */
#define CGI_COKNV_MORE_PAIRS    1    /* more name-value-pairs follow              */
#define CGI_COKNV_MORE_COOKIES  2    /* no more name-value-pairs, but new cookies */

#define CGI_COOKIE_PAIR_DELIMITER               ';' /* delimiter between to cookie attributes */
#define CGI_COOKIE_PAIR_END_OF_PAIRS_DELIMITER  ';' /* delimiter behind last cookie attribute */
#define CGI_ARGUMENTS_PAIR_DELIMITER            '&' /* delimiter between to CGI arguments */

/*************************************************************************/
//Prototypes of private functions used internal by different modules
/*************************************************************************/
char far * CGI_GetNameValuePair(char far ** name,
                                char far ** value,
                                int         pairDelimiter,
                                int         endOfPairsDelimiter,
                                char far  * pBuffer,
                                int       * more);


/*************************************************************************/
//install cgi function
/*************************************************************************/
#ifdef _cgi01_
/*
 @doc DOC_cgi01_
 ---------------------------------------------------------------
 Install a CGI function
 ---------------------------------------------------------------
 @clib  CGI_Install | Install a CGI function. |
        <cfont>int CGI_Install ( CGI_Entry far  *cgiptr );<efont>  |
 @parm  int  | cgiptr  | Pointer to a temporary <code>CGI_Entry<codee>
        <linkto>../../cgistruc.htm#typedef_CGI_Entry<linkmid>type<linktail> structure.
 @rdesc 0:  success <nl>
        non-zero:  Failure, return value contains error code
        CGI_NO_FREE_ENTRY or CGI_INVALID_METHOD
 @comm  This API function makes a copy of the information in the
        provided <code>CGI_Entry<codee> structure, so your structure
        at <code>cgiptr<codee> need not be persistent.
 @Also  cgi02.htm | CGI_Delete  | | | |
 @related <cfont>cgistat<codee> | ../../command.htm#cgistat | command | line
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x01<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int CGI_Install (CGI_Entry far  * cgiptr)
{
    _DX = FP_SEG(cgiptr);
    _SI = FP_OFF(cgiptr);

    _AH = CGI_INSTALL;
    asm { int CGIVECT  } ;

    return _AX ;
}
#endif

/*************************************************************************/
// delete cgi function
/*************************************************************************/
#ifdef _cgi02_
/*
 @doc DOC_cgi02_
 ---------------------------------------------------------------
 Remove a CGI function
 ---------------------------------------------------------------
 @clib  CGI_Delete | Remove a CGI function. |
        <cfont>int CGI_Delete ( char far * PathPtr );<efont>  |
 @parm  int  | PathPtr  | Pointer to the null terminated URL path name.
 @rdesc 0:  success <nl>
        non-zero:  Failure, return value contains error code
        CGI_NOT_FOUND
 @comm  The CGI function to be deleted is identified by the provided
        URL string.<nl>
        <nl>
        It is also possible to remove the two predefined
        cgi functions main.htm and ChipCfg from the table.<nl>
 @Also  cgi01.htm | CGI_Install  |
        cgi03.htm | CGI_SetMainPage | |
 @related <cfont>cgistat<codee> | ../../command.htm#cgistat | command | line
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x02<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int CGI_Delete (char far * PathPtr)
{
    _DX = FP_SEG(PathPtr);
    _SI = FP_OFF(PathPtr);

    _AH = CGI_REMOVE;
    asm { int CGIVECT  } ;

    return _AX ;
}
#endif


/*************************************************************************/
//Set main page
/*************************************************************************/
#ifdef _cgi03_
/*
 @doc DOC_cgi03_
 ---------------------------------------------------------------
 Set a new main page
 ---------------------------------------------------------------
 @clib  CGI_SetMainPage | Set a new main page. |
        <cfont>int CGI_SetMainPage ( const char far *mainPageName );<efont> |
 @parm  int  | mainPageName  | Pointer to name of new main page.
 @rdesc 0:  success <nl>
        non-zero:  Failure, return value contains error code
        CGI_INVALID_NAME
 @comm  The string at <code>mainPageName<codee> is null terminated
        with a maximum length of 64 characters (not counting the
        terminating zero).<nl>
 @Also  cgi06.htm | CGI_GetMainPage  |
        cgi04.htm | CGI_SetRootDir   | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x03<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int CGI_SetMainPage (const char far *mainPageName)
{
    _DX = FP_SEG(mainPageName);
    _SI = FP_OFF(mainPageName);

    _AH = CGI_SETMAIN;
    asm { int CGIVECT  } ;

    return _AX ;
}
#endif

/*************************************************************************/
//Set main page (Post method)
/*************************************************************************/
#ifdef _cgi0E_
/*
 @doc DOC_cgi0E_
 ---------------------------------------------------------------
 Set a new main page (POST method)
 ---------------------------------------------------------------
 @clib  CGI_SetMainPagePost | Set a new main page (POST method). |
        <cfont>int CGI_SetMainPagePost ( const char far *mainPageName );<efont> |
 @parm  int  | mainPageName  | Pointer to name of new main page.
 @rdesc 0:  success <nl>
        non-zero:  Failure, return value contains error code
        CGI_INVALID_NAME
 @comm  The string at <code>mainPageName<codee> is null terminated
        with a maximum length of 64 characters (not counting the
        terminating zero).<nl>
 @Also  cgi0F.htm | CGI_GetMainPagePost  |
        cgi04.htm | CGI_SetRootDir   | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x0E<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.25 | V1.25 | V1.25 | V1.20 | V1.20
 @target_clib V2.14
*/
int CGI_SetMainPagePost (const char far *mainPageName)
{
    _DX = FP_SEG(mainPageName);
    _SI = FP_OFF(mainPageName);

    _AH = CGI_SETMAIN_POST;
    asm { int CGIVECT  } ;

    return _AX ;
}
#endif

/*************************************************************************/
//Set root drive
/*************************************************************************/
#ifdef _cgi10_
/*
 @doc DOC_cgi10_
 ---------------------------------------------------------------
 Set Web server's root drive
 ---------------------------------------------------------------
 @clib  CGI_SetRootDrive | Set Web server's root drive. |
        <cfont>int CGI_SetRootDrive ( const char driveLetter );<efont> |
 @parm  int  | driveLetter | Letter of the new drive.
 @rdesc 0:  success <nl>
        non-zero:  Failure, return value contains error code
        CGI_INVALID_DIR
 @comm  The driveLetter one in-case-sensetive character which specifies
        the new web server root drive (for example 'A', 'B', 'b', ...).
 @Also  cgi11.htm | CGI_GetRootDrive  |
        cgi05.htm | CGI_GetRootDir |
        cgi04.htm | CGI_SetRootDir
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x10<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.26 | V1.26 | V1.26 | V1.21 | V1.21
 @target_clib V2.15
*/
int CGI_SetRootDrive (const char driveLetter)
{
    _DX = toupper(driveLetter) - 'A';
    _AH = CGI_SETROOTDRIVE;
    asm { int CGIVECT  } ;

    return _AX ;
}
#endif

/*************************************************************************/
//Get root drive
/*************************************************************************/
#ifdef _cgi11_
/*
 @doc DOC_cgi11_
 ---------------------------------------------------------------
 Get Web server's root drive
 ---------------------------------------------------------------
 @clib  CGI_GetRootDrive | Get Web server's root drive. |
        <cfont>char CGI_GetRootDrive ( );<efont> |
 @rdesc Letter which specifies the web servers root drive.<nl>
 @comm  The return value specifies
        the new web server root drive (for example 'A', 'B', 'b', ...).
 @Also  cgi10.htm | CGI_SetRootDrive  |
        cgi04.htm | CGI_SetRootDir |
        cgi05.htm | CGI_GetRootDir
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x11<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.26 | V1.26 | V1.26 | V1.21 | V1.21
 @target_clib V2.15
*/
char CGI_GetRootDrive (void)
{
    int rootdrive;

    _AH = CGI_GETROOTDRIVE;
    asm { int CGIVECT  } ;

    rootdrive = _DX;
    return toupper((char)rootdrive) + 'A';
}
#endif

/*************************************************************************/
//Set root dir
/*************************************************************************/
#ifdef _cgi04_
/*
 @doc DOC_cgi04_
 ---------------------------------------------------------------
 Set Web server's root directory
 ---------------------------------------------------------------
 @clib  CGI_SetRootDir | Set Web server's root directory. |
        <cfont>int CGI_SetRootDir ( const char far *rootDirName );<efont> |
 @parm  int  | rootDirName  | Pointer to the name of new root directory
        for Web server.
 @rdesc 0:  success <nl>
        non-zero:  Failure, return value contains error code
        CGI_INVALID_DIR
 @comm  The string at <code>rootDirName<codee> is null terminated with a maximum
        length of 64 characters (not counting the terminating zero).
 @Also  cgi05.htm | CGI_GetRootDir  |
        cgi11.htm | CGI_GetRootDrive |
        cgi03.htm | CGI_SetMainPage
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x04<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int CGI_SetRootDir (const char far *rootDirName)
{
    _DX = FP_SEG(rootDirName);
    _SI = FP_OFF(rootDirName);

    _AH = CGI_SETROOTDIR;
    asm { int CGIVECT  } ;

    return _AX ;
}
#endif


/*************************************************************************/
// Get root dir
/*************************************************************************/
#ifdef _cgi05_
/*
 @doc DOC_cgi05_
 ---------------------------------------------------------------
 Get Web server's root directory
 ---------------------------------------------------------------
 @clib  CGI_GetRootDir | Get Web server's root directory. |
        <cfont>int CGI_GetRootDir ( char far **rootDirName );<efont> |
 @parm  char far **  | rootDirName  | Contains pointer to root directory name.
 @rdesc 0:<tab>The variable rootDirName contains a pointer to the Web server's root directory name.
 @comm  The referenced root directory name string is null terminated and is in
        the  RTOS's data space.<nl>
        <nl>
        The caller must treat this string as a
        constant and must not modify it.
 @Also  cgi04.htm | CGI_SetRootDir  |
        cgi10.htm | CGI_SetRootDrive  |
        cgi06.htm | CGI_GetMainPage
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x05<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int CGI_GetRootDir(char far **rootDirName)
{
    unsigned int tmp_es;

    _AH = CGI_GETROOTDIR;
    asm { int CGIVECT  } ;

    tmp_es = _ES;

    *rootDirName = (char far *)MK_FP( tmp_es, _DI );

    return _DX;
}
#endif



/*************************************************************************/
//Get main page name
/*************************************************************************/
#ifdef _cgi06_
/*
 @doc DOC_cgi06_
 ---------------------------------------------------------------
 Get main page name
 ---------------------------------------------------------------
 @clib  CGI_GetMainPage | Get main page name. |
        <cfont>int CGI_GetMainPage ( char far **mainPageName );<efont> |
 @parm  char far **  | mainPageName  | Contains pointer to current main page name.
 @rdesc 0:<tab>The variable mainPageName contains a pointer to a string containing name of current main page
 @comm  The referenced main page name string is null terminated and is in
        the  RTOS's data space.<nl>
        <nl>
        The caller must treat this string as a constant and must not modify it.
 @Also  cgi03.htm | CGI_SetMainPage |
        cgi05.htm | CGI_GetRootDir  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x06<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int CGI_GetMainPage(char far **mainPageName)
{
   unsigned int tmp_es;

   _AH = CGI_GETMAIN;
   asm { int CGIVECT  } ;

   tmp_es = _ES;

	*mainPageName = (char far *)MK_FP( tmp_es, _DI );

   return _DX;
}
#endif

/*************************************************************************/
//Get main page name (POST method)
/*************************************************************************/
#ifdef _cgi0F_
/*
 @doc DOC_cgi0F_
 ---------------------------------------------------------------
 Get main page name (POST method)
 ---------------------------------------------------------------
 @clib  CGI_GetMainPagePost | Get main page name (POST method). |
        <cfont>int CGI_GetMainPagePost ( char far **mainPageName );<efont> |
 @parm  char far **  | mainPageName  | Contains pointer to current main page name.
 @rdesc 0:<tab>The variable mainPageName contains a pointer to a string containing name of current main page
 @comm  The referenced main page name string is null terminated and is in
        the  RTOS's data space.<nl>
        <nl>
        The caller must treat this string as a constant and must not modify it.
 @Also  cgi03.htm | CGI_SetMainPagePost |
        cgi05.htm | CGI_GetRootDir  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x0F<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.25 | V1.25 | V1.25 | V1.20 | V1.20
 @target_clib V2.14
*/
int CGI_GetMainPagePost(char far **mainPageName)
{
   unsigned int tmp_es;

   _AH = CGI_GETMAIN_POST;
   asm { int CGIVECT  } ;

   tmp_es = _ES;

	*mainPageName = (char far *)MK_FP( tmp_es, _DI );

   return _DX;
}
#endif

/*************************************************************************/
// CGI_SetCookie
/*************************************************************************/
#ifdef __PARADIGM__ /* this function requires the paradigm compiler */
#ifdef _cgiscookie_

// internal function, used by "CGI_SetCookie"
static int near CGI_CreateCookieHeader(const char          *name,
                                       const char          *value,
                                       const char          *domain,
                                       const unsigned long *expires, // secs from now
                                       const char          *path,
                                       const int            secure,
                                       char                *pHeaderBuffer,
                                       int                  iHeaderBufferSize,
                                       int                  numOfCookies)
{
  char * pBuffer = pHeaderBuffer;
  char * pEOBuf = pBuffer + iHeaderBufferSize;

  time_t timer;
  struct tm *timeStruct;
  static const char *CGI_MONTHS2STR[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
                                         "Aug", "Sep", "Oct", "Nov", "Dec"};
  static const char *CGI_DAYSOFWEEK[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};


  if (!pHeaderBuffer
    || !name  || !(*name)
    )
  {
    return CGI_COOKIE_ERR_PARAM;
  }

  if (!value || !(*value) )
  {
    // no value indicates that the cookie should be deleted
    value = "";
  }

  // find end of last cookie
  while (numOfCookies--)
  {
     // set pBuffer behind the cookie string
     pBuffer += strlen(pBuffer) + 1;
  }

  // required attribute
  pBuffer += snprintf((char *)pBuffer, (size_t)(pEOBuf-pBuffer), (const char *)"%s=%s", name, value );

  // optional attributes
  if (domain  && *domain) pBuffer += snprintf(pBuffer,
                                              (size_t)(pEOBuf-pBuffer),
                                              "%c domain=%s",
                                              CGI_COOKIE_PAIR_DELIMITER,
                                              domain);
  if (expires)
  {
     time(&timer);                // get current local time
     timer += *expires;           // add expire timeout
     timeStruct = gmtime(&timer); // convert to GMT

     // generate date-time string
     pBuffer += snprintf(pBuffer, (size_t)(pEOBuf-pBuffer),
                         "%c expires=%s, %02u-%s-%04u %02u:%02u:%02u GMT",
                                              CGI_COOKIE_PAIR_DELIMITER,
                                              CGI_DAYSOFWEEK[timeStruct->tm_wday],
                                              timeStruct->tm_mday,
                                              CGI_MONTHS2STR[timeStruct->tm_mon],
                                              timeStruct->tm_year+1900,
                                              timeStruct->tm_hour,
                                              timeStruct->tm_min,
                                              timeStruct->tm_sec);
  } // if (expires)
  if (path    && *path)   pBuffer += snprintf(pBuffer,
                                              (size_t)(pEOBuf-pBuffer),
                                              "%c path=%s",
                                              CGI_COOKIE_PAIR_DELIMITER,
                                              path);
  if (secure)             pBuffer += snprintf(pBuffer,
                                              (size_t)(pEOBuf-pBuffer),
                                              "%c secure",
                                              CGI_COOKIE_PAIR_DELIMITER);

/*
  // required attribute
  pBuffer += snprintf(pBuffer, (size_t)(pEOBuf-pBuffer), "%c Version=%d",
                                                         CGI_COOKIE_PAIR_DELIMITER
                                                         ,version);
*/
  // check for error (suppressed buffer overflow) in steps above
  if (pBuffer == pEOBuf) return CGI_COOKIE_ERR_SIZE;

  // success
  return CGI_COOKIE_ERR_OK;
}

/*
 @doc DOC_cgiscookie_
 ---------------------------------------------------------------
 Creates a new cookie or modifies an old one.
 ---------------------------------------------------------------
 @clib  CGI_SetCookie | Creates a new cookie or modifies an old one. |
        <cfont>int CGI_SetCookie ( const char far *name,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; const char far *value,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; const char far *domain,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; const unsigned long far *expires,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; const char far *path,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; const int secure,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; rpCgiPtr CgiRequest);<efont> |
 @parm  const char far * | name | Input Parameter:<s2>
        A pointer to a c-string which represents cookies-name.
 @parm  const char far * | value | Input Parameter:<s2>
        A pointer to a c-string which represents cookies-value.
 @parm  const char far * | domain | Input Parameter:<s2>
        A pointer to a c-string which represents cookies-domain.
        If you are not interest in the cookie-domain then you can pass a
        null pointer.
 @parm  const unsigned long far * | expires | Input Parameter:<s2>
        A pointer to an unsigned long which represents cookies-expire-time.
        If you are not interest in the cookie-expire-time then you can pass a
        null pointer.
 @parm  const char far * | path | Input Parameter:<s2>
        A pointer to a c-string which represents cookies-path.
        If you are not interest in the cookie-path then you can pass a
        null pointer.
 @parm  const int | secure | Input Parameter:<s2>
        This integer value defines the secure state of the cookie.<nl>
        0 : no secure cookie<nl>
        !=0 : secure cookie<nl>
 @parm  rpCgiPtr | CgiRequest  | Input Parameter:<s2>
        The cgi request pointer which was passed to the cgi function.
 @rdesc CGI_COOKIE_ERR_OK:  Success, the cookie was created <nl>
        CGI_COOKIE_ERR_SIZE: The cookie parameters in sum are too large. All cookies together
        must not be larger than 1024 bytes.<nl>
        CGI_COOKIE_ERR_PARAM: Invalid parameters, e.g. no cookie-name .
 @comm  The argument strings are copied internal, so they are not required after the function
        call and could by deleted or modified.<nl>
        Note that the date and time and also the timezone have to be set when you are using
        the <code>expires<codee> argument.<nl>
        This function must be called within the context of a cgi function.
        The pointers returned by the function are valid only while the cgi function
        is active. On return from the cgi function the pointer will become invalid.<nl>
        <nl>
        Example:
 @raw
        <code>
        int result = CGI_SetCookie("username",
                                   "otto",
                                   NULL,
                                   NULL,
                                   NULL,
                                   0,
                                   CgiRequest);
        if (result != CGI_COOKIE_ERR_OK)
        {
           // ERROR!
        }
        <codee>
 @Also  cgigcookie.htm | CGI_GetCookie  | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V1.15 | V1.00
 @target_clib V2.10
*/
int CGI_SetCookie(const char          *name,
                  const char          *value,
                  const char          *domain,
                  const unsigned long *expires,
                  const char          *path,
                  const int            secure,
                  rpCgiPtr             CgiRequest)
{
   static char setCookieBuffer[CGI_MAX_COOKIE_SIZE];
   int error;

   error = CGI_CreateCookieHeader(name, value, domain, expires,
                                  path, secure, setCookieBuffer,
                                  sizeof(setCookieBuffer),
                                  CgiRequest->fNumOfSetCookieHeaders);

   if (error == CGI_COOKIE_ERR_OK)
   {
      CgiRequest->fSetCookieHeaders = (char far *)setCookieBuffer;
      CgiRequest->fNumOfSetCookieHeaders++;
   }

   return error;
}
#endif // _cgiscookie_
#endif // __PARADIGM__ /* this function requires the paradigm compiler */


/*************************************************************************/
// CGI_GetCookie
/*************************************************************************/
#ifdef __PARADIGM__ /* this function requires the paradigm compiler */
#ifdef _cgigcookie_

// internal function, used by "CGI_GetCookie"
static char far * near CGI_GetCookieFromHeader(char far **name,
                                               char far **value,
                                               char far **domain,
                                               char far **path,
                                               char far **port,
                                               char far **version,
                                               char far * pHeaderBuffer)
{
  char far *pBuffer = pHeaderBuffer;
  char far *_name;
  char far *_value;

  int more;

  // init cookie attributes
  *name = *value = NULL;
  
  if (domain)    
    *domain = NULL;
  if (path)
    *path = NULL;
  if (port)
    *port = NULL; 
  if (version)    
    *version = NULL;

  pBuffer = CGI_GetNameValuePair(name, value,
                                 CGI_COOKIE_PAIR_DELIMITER,
                                 CGI_COOKIE_PAIR_END_OF_PAIRS_DELIMITER,
                                 pBuffer,
                                 &more);

  while (more == CGI_COKNV_MORE_PAIRS)
  {
    pBuffer = CGI_GetNameValuePair(&_name, &_value,
                                   CGI_COOKIE_PAIR_DELIMITER,
                                   CGI_COOKIE_PAIR_END_OF_PAIRS_DELIMITER,
                                   pBuffer,
                                   &more);

    if ( _fstricmp(_name, (const char far *)"Path") == 0 )
    { 
      if (path)
        *path = _value;
    }          
    else if ( _fstricmp(_name, (const char far *)"Domain") == 0 )
    { 
      if (domain)
        *domain = _value;
    }         
    else if ( _fstricmp(_name, (const char far *)"Port") == 0 ) 
    {
      if (port)
        *port = _value;
    }      
    else if ( _fstricmp(_name, (const char far *)"Version") == 0 ) 
    {
      if (version) 
        *version = _value;
    }        
  }

  if (more == CGI_COKNV_END) pBuffer = NULL;

  return pBuffer;
}

/*
 @doc DOC_cgigcookie_
 ---------------------------------------------------------------
 Returns the next available cookie
 ---------------------------------------------------------------
 @clib  CGI_GetCookie | Returns the next available cookie. |
        <cfont>int CGI_GetCookie ( char far **name,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; char far **value,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; char far **domain,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; char far **path,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; char far **port,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; char far **version,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; rpCgiPtr CgiRequest);<efont> |
 @parm  char far ** | name | Output Parameter:<s2>
        A pointer to a valid char-pointer variable. After the function call
        the char-pointer variable points to a c-string with the cookie-name.
 @parm  char far ** | value | Output Parameter:<s2>
        A pointer to a valid char-pointer variable. After the function call
        the char-pointer variable points to a c-string with the cookie-value.
 @parm  char far ** | domain | Output Parameter:<s2>
        A pointer to a valid char-pointer variable. After the function call
        the char-pointer variable points to a c-string with the cookie-domain.
        If you are not interest in the cookie-domain then you can pass a
        null pointer.
 @parm  char far ** | path | Output Parameter:<s2>
        A pointer to a valid char-pointer variable. After the function call
        the char-pointer variable points to a c-string with the cookie-path.
        If you are not interest in the cookie-path then you can pass a
        null pointer.
 @parm  char far ** | port | Output Parameter:<s2>
        A pointer to a valid char-pointer variable. After the function call
        the char-pointer variable points to a c-string with the cookie-port.
        If you are not interest in the cookie-port then you can pass a
        null pointer.
 @parm  char far ** | version | Output Parameter:<s2>
        A pointer to a valid char-pointer variable. After the function call
        the char-pointer variable points to a c-string with the cookie-version.
        If you are not interest in the cookie-version then you can pass a
        null pointer.

 @parm  rpCgiPtr | CgiRequest  | Input Parameter:<s2>
        The cgi request pointer which was passed to the cgi function.
 @rdesc CGI_COOKIE_ERR_OK:  success <nl>
        CGI_COOKIE_ERR_NONE: there was no more cookie found
 @comm  On the first call the function returns the first found cookie. On next
        calls the function returns the next found cookie, until no more cookie
        could be found.<nl>
        Note that this function must be called within the context of a cgi function.
        The pointers returned by the function are valid only while the cgi function
        is active. On return from the cgi function the pointer will become invalid.<nl>
        <nl>
        Example:
 @raw
        <code>
        char *name;
        char *value;
        char *domain;
        char *path;
        char *port;
        char *version;

        while ( CGI_GetCookie( &name, &value, &domain, &path, &port, &version ) == CGI_COOKIE_ERR_OK)
        {
            // do something with the found cookie
            printf( "Cookie found:\r\n"
                    "Name   : %s\r\n",
                    "Value  : %s\r\n",
                    "Domain : %s\r\n",
                    "Path   : %s\r\n",
                    "Port   : %s\r\n",
                    "Version: %s\r\n",
                    name, value, domain, path, port, version );
        }
        <codee>
 @Also  cgiscookie.htm | CGI_SetCookie  | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V1.15 | V1.00
 @target_clib V2.10
*/
int CGI_GetCookie(char far **name,
                  char far **value,
                  char far **domain,
                  char far **path,
                  char far **port,
                  char far **version,
                  rpCgiPtr CgiRequest)
{
  if (CgiRequest->fCookieHeader == NULL) return CGI_COOKIE_ERR_NONE; // no cookie available

  CgiRequest->fCookieHeader = CGI_GetCookieFromHeader(name,
                                                      value,
                                                      domain,
                                                      path,
                                                      port,
                                                      version,
                                                      CgiRequest->fCookieHeader);
  return CGI_COOKIE_ERR_OK; // success, cookie was found
}
#endif // _cgigcookie_
#endif // __PARADIGM__ /* this function requires the paradigm compiler */



/*******************************************************************************
* CGI_UrlEncode()
*
* Encodes a URL string
*******************************************************************************/
#ifdef _cgiUrlEncode_
/*
 @doc DOC_cgiUrlEncode_
 @clib  CGI_UrlEncode | Encodes a URL string |
        <cfont>void CGI_UrlEncode ( char *dst,<nl>
        <tab><tab><tab><tab><tab>&nbsp; const char far *src );<efont> |
 @parm  char far * | dst | Output Parameter: Pointer to the buffer the encoded
        string is to be stored in; must be large enough. The encoded string can
        be up to three times as large as the original string.
 @parm  const char far * | src | String that is to be encoded
 @comm  In URL-encoded strings all non-alphanumerical characters except '-', '_'
        and '.' are encoded as a hexadecimal value preceded by a percent sign
        (e.g. %26 for the ampersand). The space character is replaced by a plus
        sign. The text "Test 123 .&%" (without the quotes) would be encoded as
        "Test+123+.%26%25".<nl>
        This kind of encoding is for example used to pass arguments to a CGI
        page with the URL.
 @Also  cgiUrlDecode.htm | CGI_UrlDecode  | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
 @target_clib V2.12
*/
void CGI_UrlEncode(char *dst, const char far *src)
{
  for(; *src; ++src)
  {
    if((('0' <= *src) && (*src <= '9'))
       || (('a' <= *src) && (*src <= 'z'))
       || (('A' <= *src) && (*src <= 'Z'))
       || (*src == '_') || (*src == '-') || (*src == '.'))
    {
      *dst++ = *src;
    }
    else if(*src == ' ')
    {
      *dst++ = '+';
    }
    else
    {
      dst += sprintf(dst, "%%%02X", (unsigned char)*src);
    }
  }
  *dst = '\0';
}
#endif



/*******************************************************************************
* CGI_UrlDecode()
*
* Decode a URL string
*******************************************************************************/
#ifdef _cgiUrlDecode_
/*
 @doc DOC_cgiUrlDecode_
 @clib  CGI_UrlDecode | Decodes a URL string |
        <cfont>void CGI_UrlDecode ( char far *dst,<nl>
        <tab><tab><tab><tab><tab>&nbsp; const char far *src );<efont> |
 @parm  char far * | dst | Output Parameter: Pointer to the buffer the decoded
        string is to be stored in; must be large enough.
 @parm  const char far * | src | URL-encoded string that is to be decoded
 @comm  In URL-encoded strings all non-alphanumerical characters except '-', '_'
        and '.' are encoded as a hexadecimal value preceded by a percent sign
        (e.g. %26 for the ampersand). The space character is replaced by a plus
        sign. The text "Test 123 .&%" (without the quotes) would be encoded as
        "Test+123+.%26%25".<nl>
        This kind of encoding is for example used to pass arguments to a CGI
        page with the URL.<nl>
        <nl>
        You can pass the same pointer as <cfont>src<efont> and <cfont>dst<efont>
        parameter. The encoded string will in this case be overwritten with the
        decoded string.<nl>
        Example:<nl>
        <code>CGI_UrlDecode(url, url);<codee>
 @Also  cgiUrlEncode.htm | CGI_UrlEncode  | | | |
 @Also  cgigetarg.htm | CGI_GetArgument  | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
 @target_clib V2.12
*/
void CGI_UrlDecode(char far *dst, const char far *src)
{
  register char c;
  register int i;


  if(src)
  {
    while(*src)
    {
      switch(*src)
      {
        case '+':
           *(dst++) = ' ';
           src++;
           break;

        case '%':
           src++;
           if(*src && *(src+1))
           {
              // parse and convert hexdecimal Ascii code

              i = 2; // two digits
              *dst = 0;
              while(i--)
              {
                *dst <<= 4;
                c = *(src++);
                if(c >= '0' && c <= '9')
                  *dst |= c - '0';
                else if(c >= 'a' && c <= 'f')
                  *dst |= c - 'a' + 0xa;
                else if(c >= 'A' && c <= 'F')
                  *dst |= c - 'A' + 0xa;
                else
                  *dst = 0;
              }
              dst++;
           }
           else
           {
              // invalid character, ommit it!
              if(*src)
                src++;
           }
           break;

        default:
           *(dst++) = *(src++);
      } // switch
    } // while
    *dst = '\0';
  } // if
}
#endif



/*************************************************************************/
// Get argument
/*************************************************************************/
#ifdef _cgigetarg_

// internal function, used by "CGI_Arguments_GetNameValuePairs"
static char far * near CGI_Cookie_FindEndOfName(char far *pBuffer)
{
  while (*pBuffer != ' '
      && *pBuffer != ';'
      && *pBuffer != ','
      && *pBuffer != '='
      && *pBuffer != '&'
      && *pBuffer != '\0'
      && *pBuffer != '\r'
      && *pBuffer != '\n')
  {
     pBuffer++;
  }

  return pBuffer;
}

// internal function, used by "CGI_Arguments_GetNameValuePairs"
static char far * near CGI_Cookie_FindEndOfValue(char far *pBuffer)
{
  if (*pBuffer != '"')
  {
     // The value does not begin with '"', so its a normal token
     // like a name
     return CGI_Cookie_FindEndOfName(pBuffer);
  }

  // skip '"'
  pBuffer++;

  // its a quoted-string, search for ending '"'
  while (*pBuffer != '\0'
      && *pBuffer != '"')
  {
     if (*pBuffer == '\\' && *(pBuffer+1) != '\0')
     {
       pBuffer++; // ignore next character because of quote sign
     }

     pBuffer++;
  }

  // skip '"' cause its part of the value
  if (*pBuffer == '"') pBuffer++;

  return pBuffer;
}



// internal function, used by "CGI_GetArgument" and "CGI_GetCookieFromHeader"
char far * CGI_GetNameValuePair(char far ** name,
                                char far ** value,
                                int         pairDelimiter,
                                int         endOfPairsDelimiter,
                                char far *  pBuffer,
                                int      *  more)
{
  char far *pch; // help char pointer
  char far *eon = NULL; // end of name
  char far *eov = NULL; // end of value

  // init name and value with ""
  *name  = *value = NULL;

  if (pBuffer == NULL) return NULL;

  // skip spaces
  while (*pBuffer == ' ') pBuffer++;

  // parse name
  pch = CGI_Cookie_FindEndOfName(pBuffer);
  if (pch>pBuffer && name)
  {
     *name = pBuffer;
     eon  = pch;
  }
  pBuffer = pch;

  // skip spaces
  while (*pBuffer == ' ') pBuffer++;

  // Check for end of name-value pair (name without value)
  if (*pBuffer != '=')
  {
    // check for more cookies
    if ((int)*pBuffer == endOfPairsDelimiter)
    {
      // name-value-pairs done for this cookie, but next cookie follows
      *more = CGI_COKNV_MORE_COOKIES;
    }
    else if ((int)*pBuffer == pairDelimiter)
    {
      // next name-value-pairs for this cookie follows
      *more = CGI_COKNV_MORE_PAIRS;
    }
    else
    {
      // no more data in cookie header
      *more = CGI_COKNV_END;
    }

    if (*pBuffer != '\0')
      pBuffer++;       // skip the name terminating char

    if (eon)
      *eon = '\0';     // null-terminate the name

    return pBuffer;
  }

  // Skip '='
  pBuffer++;

  // skip spaces
  while (*pBuffer == ' ') pBuffer++;

  // parse value
  pch = CGI_Cookie_FindEndOfValue(pBuffer);
  if (pch>pBuffer && value)
  {
     *value = pBuffer;
     eov = pch;
  }
  pBuffer = pch;

  // skip spaces
  while (*pBuffer == ' ') pBuffer++;

  // check for more cookies
  if ((int)*pBuffer == endOfPairsDelimiter)
  {
     // name-value-pairs done for this cookie, but next cookie follows
     *more = CGI_COKNV_MORE_COOKIES;
     pBuffer++;
  }
  else if ((int)*pBuffer == pairDelimiter)
  {
     // next name-value-pairs for this cookie follows
     *more = CGI_COKNV_MORE_PAIRS;
     pBuffer++;
  }
  else
  {
     // no more data in cookie header
     *more = CGI_COKNV_END;
  }

  if (eon) *eon = '\0'; // null-terminate the name
  if (eov) *eov = '\0'; // null-terminate the value

  return pBuffer;
}


/*
 @doc DOC_cgigetarg_
 ---------------------------------------------------------------
 Returns the next available argument by name and value
 ---------------------------------------------------------------
 @clib  CGI_GetArgument | Returns the next available argument (name-value pair). |
        <cfont>int CGI_GetArgument ( char far **name,<nl>
        <tab><tab><tab><tab><tab>&nbsp; char far **value,<nl>
        <tab><tab><tab><tab><tab>&nbsp; rpCgiPtr CgiRequest);<efont> |
 @parm  char far ** | name | Output Parameter:<s2>
        A pointer to a valid char-pointer variable. After the function call
        the char-pointer variable points to a c-string with the argument-name.
 @parm  char far ** | value | Output Parameter:<s2>
        A pointer to a valid char-pointer variable. After the function call
        the char-pointer variable points to a c-string with the argument-value.
 @parm  rpCgiPtr | CgiRequest  | Input Parameter:<s2>
        The cgi request pointer which was passed to the cgi function.
 @rdesc CGI_ARGUMENT_ERR_OK:  success <nl>
        CGI_ARGUMENT_ERR_NONE: there was no more argument found
 @comm  On the first call the function returns the first found argument. On next
        calls the function returns the next found argument, until no more arguments
        could be found.<nl>
        Note that this function must be called within the context of a cgi function.
        The pointers returned by the function are valid only while the cgi function
        is active. On return from the cgi function the pointer will become invalid.<nl>
        The name, value pairs returned by this function are already decoded. You
        don't have to call <linkto>cgiUrlDecode.htm<linkmid>CGI_UrlDeocde<linktail>
        yourself.<nl>
        <nl>
        Example:
 @raw
        <code>
        char *name;
        char *value;

        while ( CGI_GetArgument( &name, &value, CgiRequest ) == CGI_ARGUMENT_ERR_OK )
        {
           printf("Argument found:\r\n"
                  "Name : %s\r\n"
                  "Value: %s\r\n",
                  name, value);
        }
        <codee>

 @Also  cgi07.htm | CGI_GetFormItem  | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
 @target_clib V2.10
*/
int CGI_GetArgument(char far **name,
                    char far **value,
                    rpCgiPtr CgiRequest)
{
  int more;
  char far *pBuffer;

  if (CgiRequest->fArgumentBufferLength > 0)
  {
    pBuffer = CGI_GetNameValuePair(name, value,
                                   CGI_ARGUMENTS_PAIR_DELIMITER,
                                   -1,
                                   CgiRequest->fArgumentBufferPtr,
                                   &more);
    CgiRequest->fArgumentBufferPtr = pBuffer;

    // convert to ascii
    CGI_UrlDecode(*name, *name);
    CGI_UrlDecode(*value, *value);

    // check if argument could be parsed
    if (name != NULL && name[0] != '\0') return CGI_ARGUMENT_ERR_OK;
  }

  return CGI_ARGUMENT_ERR_NONE;
}
#endif // cgigetarg


/*************************************************************************/
// Get formitem
/*************************************************************************/
#ifdef _cgi07_
/*
 @doc DOC_cgi07_
 ---------------------------------------------------------------
 Split a form item into name and value
 ---------------------------------------------------------------
 @clib  CGI_GetFormItem | Split a form item into name and value. |
        <cfont>void CGI_GetFormItem ( const char far *ArgumentBufferPtr,<nl>
        <tab><tab><tab><tab><tab>&nbsp;&nbsp; FormItem far *formitem );<efont> |
 @depr  cgigetarg.htm | CGI_GetArgument
 @parm  int  | ArgumentBufferPtr  | Input Parameter:<s2>
        Pointer to argument buffer to  be parsed.
 @parm  int  | formitem  | Input/Output Parameters:<s2>
        Pointer to a <code>FormItem<codee>
        <linkto>../../cgistruc.htm#typedef_FormItem<linkmid>type<linktail> structure
 @rdesc  -- none --
 @comm  On initial call, the <code>ArgumentBufferPtr<codee> provided by the caller
        is a copy of the <code>fArgumentBufferPtr<codee> member of
        the <code>rbCgi<codee>
        <linkto>../../cgistruc.htm#rpCgi<linkmid>structure<linktail> passed by the
        Web server to the CGI callback function.<s2> On subsequent calls
        to pick up additional form items, the pointer returned from the
        <linkto>cgi08.htm<linkmid>CGI_GetNextItem<linktail>
        function can be used here.<nl>
        <nl>
        Prior to calling the two members of the <code>FormItem<codee>
        <linkto>../../cgistruc.htm#typedef_FormItem<linkmid>structure<linktail>
        must be set by the caller.<s2>
        Both member pointers in the <code>FormItem<codee> data structure
        reference buffers allocated by the
        user, which will receive strings produced by this API call.<nl>
 @Also  cgi08.htm | CGI_GetNextItem  |
        cgigetarg.htm | GGI_GetArgument | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x07<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void CGI_GetFormItem (const char far * ArgumentBufferPtr,
                      FormItem far * formitem)
{
    _BX = FP_SEG(ArgumentBufferPtr);
    _SI = FP_OFF(ArgumentBufferPtr);

    _ES = FP_SEG(formitem);
    _DI = FP_OFF(formitem);

    _AH = CGI_GETFORMITEM;
    asm { int CGIVECT  } ;
}
#endif

/*************************************************************************/
//Get next formitem
/*************************************************************************/
#ifdef _cgi08_
/*
 @doc DOC_cgi08_
 ---------------------------------------------------------------
 Return pointer to the next form item
 ---------------------------------------------------------------
 @clib  CGI_GetNextItem | Get the next form item. |
        <cfont>int CGI_GetNextItem ( char far *ArgumentBufferPtr,<nl>
        <tab><tab><tab><tab><tab>&nbsp;&nbsp;char far **nextItemString );<efont> |
 @depr  cgigetarg.htm | CGI_GetArgument
 @parm  char far *  | ArgumentBufferPtr  | CGI request argument pointer.
 @parm  char far **  | nextItemString  | Pointer to the found item.
 @rdesc 0:<tab>Item was found<nl>
        -1:<tab>No more items found
 @comm  Most forms have more than one item.<s2> This function searches for
        the next form item in a CGI request argument string.<s2> It can
        only be used after a
        <linkto>cgi07.htm<linkmid>CGI_GetFormItem<linktail> call.<nl>
        <nl>
        The string referenced by <code>ArgumentBufferPtr<codee> is not
        modified in any way by this function.
 @Also  cgi07.htm | CGI_GetFormItem  |
        cgigetarg.htm | GGI_GetArgument | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x08<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int CGI_GetNextItem (char far * ArgumentBufferPtr, char far **nextItemString)
{
    unsigned int tmp_es;

    _BX = FP_SEG(ArgumentBufferPtr);
    _SI = FP_OFF(ArgumentBufferPtr);

    _AH = CGI_FINDNEXTITEM;
    asm { int CGIVECT  } ;

    tmp_es = _ES;

    if (_DX == 0)
        *nextItemString = MK_FP( tmp_es, _DI );
    else
        *nextItemString = NULL;

    return _DX;
}
#endif


/*************************************************************************/
//Redirect to own files on http errors
/*************************************************************************/
#ifdef _cgi0A_
/*
 @doc DOC_cgi0A_
 ---------------------------------------------------------------
 Install CGI function on http error messages (e.g.404)
 ---------------------------------------------------------------
 @clib  CGI_Install_Func_OnErr | Install CGI function on http errors |
        <cfont>int CGI_Install_Func_OnErr( unsigned int error_state,
        <tab><tab><tab><tab><tab><tab>void far *CgiFuncOnErr);<nl>
 <efont> |
 @parm  unsigned int | error_state | http error state (see below)
 @parm  void far *  | CgiFuncOnErr   | CGI Function pointer
 @rdesc 0:<tab>CGI function installed<nl>
        -1:<tab>CGI function not installed <nl>
 @comm
 The CGI function must be implemented in the same way than a CGI function,
 installed with <linkto>../../cgi.htm#0xAB0x01<linkmid>CGI_INSTALL<linktail>.
 For deleting an entry, install a null pointer.<nl><nl>

 Possible Http error states(parameter error_state):<nl>
 07: 401 Unauthorized<nl>
 08: 404 not found<nl>
 10: 500 Server error (File system error)<nl>
 22: 503 Service not available (Out of memory)<nl>

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x0A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.11 | V1.01 | V1.01 | V1.12 | V1.00
*/
int CGI_Install_Func_OnErr( unsigned int error_state, void far *CgiFuncOnErr)
{
    asm les di,CgiFuncOnErr
    asm mov bx,error_state
    asm mov ah,CGI_ERR_FUNC;
    asm { int CGIVECT  } ;
    return _DX;
}
#endif

/*************************************************************************/
//Redirect to own cgi function on http upload requests
/*************************************************************************/
#ifdef _cgi13_
/*
 @doc DOC_cgi13_
 ---------------------------------------------------------------
 Install CGI function on http upload requests
 ---------------------------------------------------------------
 @clib  CGI_Install_Func_OnUpload | Install CGI function on http upload requests |
        <cfont>int CGI_Install_Func_OnUpload(void far *CgiFuncOnUpload);<nl>
 <efont> |
 @parm  void far *  | CgiFuncOnUpload | CGI Function pointer
 @rdesc 0:<tab>CGI function installed<nl>
        -1:<tab>CGI function not installed <nl>
 @comm
 The upload handler function will be called after a successful HTTP file
 upload. It is a CGI function that must be implemented in the same way than a
 normal CGI function, installed with <linkto>../../cgi.htm#0xAB0x01<linkmid>CGI_INSTALL<linktail>.
 For removing the upload handler function install a null pointer.<nl><nl>

 The name and path of the uploaded file is stored in the CgiRequests 
 fPathPtr element.

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x13<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V1.30 | V1.30

 @target_clib V2.17
*/
int CGI_Install_Func_OnUpload(void far *CgiFuncOnUpload)
{
    asm les di,CgiFuncOnUpload
    asm mov ah,CGI_UPLOAD_FUNC;
    asm { int CGIVECT  } ;
    return _DX;
}
#endif

/*************************************************************************/
//Enable/Disable HTTP file upload
/*************************************************************************/
#ifdef _cgi12_
/*
 @doc DOC_cgi12_
 ---------------------------------------------------------------
 Enable/Disable HTTP file upload
 ---------------------------------------------------------------
 @clib  CGI_Enable_Upload | Enables or disables the HTTP file upload. |
        <cfont>int CGI_Enable_Upload(int enable);<nl>
 <efont> |
 @parm  int  | enable | 1=enable file upload, 0=disable file upload
 @rdesc always 0
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x12<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V1.30 | V1.30
 
 @target_clib V2.17
*/
int CGI_Enable_Upload(int enable)
{
    asm mov dx,enable
    asm mov ah,CGI_ENABLEUPLOAD;
    asm { int CGIVECT  } ;
    return _DX;
}
#endif


/*************************************************************************/
//Install user custom MIME table
/*************************************************************************/
#ifdef _cgi0B_
/*
 @doc DOC_cgi0B_
 ---------------------------------------------------------------
 Install user custom MIME table
 ---------------------------------------------------------------
 @clib  CGI_Install_MIME_Table | Install user custom MIME table |
        <cfont>int CGI_Install_MIME_Table( unsigned int entries,
        <tab><tab><tab><tab><tab><tab><tab>CUSTOM_MIMETYPES_TABLE far *mimeTable);<nl>
 <efont> |
 @parm  unsigned int | entries       | Number of entries in MIME table
 @parm  CUSTOM_MIMETYPES_TABLE far * | mimeTable | Pointer to custom
        <linkto>../../cgistruc.htm#typedef_CUSTOM_MIMETYPES_TABLE<linkmid>MIME table<linktail>
 @rdesc 0:<tab>OK<nl>
        -1:<tab>Error<nl>
 @comm The MIME table must be persistent. The RTOS does not make a copy.
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x0B<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00

 @target_clib V2.04
*/
int CGI_Install_MIME_Table( unsigned int entries,
                            CUSTOM_MIMETYPES_TABLE far *mimeTable)
{
    asm les di,mimeTable
    asm mov bx,entries
    asm mov ah,CGI_MIME_INSTALL;
    asm { int CGIVECT  } ;
    return _DX;
}
#endif


/*************************************************************************/
//Install user custom content-encoding table
/*************************************************************************/
#ifdef _cgi0D_
/*
 @doc DOC_cgi0D_
 ---------------------------------------------------------------
 Install user custom content-encoding table
 ---------------------------------------------------------------
 @clib  CGI_Install_ContentEncoding_Table | Install user custom content-encoding table |
        <cfont>int CGI_Install_ContentEncoding_Table( unsigned int entries,
        <tab><tab><tab>CUSTOM_CONTENTENCODING_TABLE far *contentEncodingTable);<nl>
 <efont> |
 @parm  unsigned int | entries       | Number of entries in content-encoding table (must be equal to
                                       the user custom mime table size).
 @parm  CUSTOM_CONTENTENCODING_TABLE far * | contentEncodingTable | Pointer to custom
        <linkto>../../cgistruc.htm#typedef_CUSTOM_CONTENTENCODING_TABLE<linkmid>content-encoding table<linktail>
 @rdesc 0:<tab>OK<nl>
        -1:<tab>Error (wrong number of entries)<nl>
 @comm The content encoding table references to the custom MIME table.
       So the content encoding table assigns every mime type defined
       in the MIME table a correspondent content encoding type.<nl>
       The custom content encoding table must be persistent. The RTOS does not make a copy.
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x0D<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V1.16 | V1.00

 @target_clib V2.11
*/
int CGI_Install_ContentEncoding_Table( unsigned int entries,
                                       CUSTOM_CONTENTENCODING_TABLE far *contentEncodingTable)
{
    asm les di,contentEncodingTable
    asm mov bx,entries
    asm mov ah,CGI_CONTENTENCODING_INSTALL;
    asm { int CGIVECT  } ;
    return _DX;
}
#endif

/*************************************************************************/
//Remove user custom content-encoding table
/*************************************************************************/
#ifdef _cgiRmContentEncoding_
/*
 @doc DOC_cgiRmContentEncoding_
 ---------------------------------------------------------------
 Remove user custom content-encoding table
 ---------------------------------------------------------------
 @clib  CGI_Remove_ContentEncoding_Table | Deinstall user custom content-encoding table |
        <cfont>int CGI_Remove_ContentEncoding_Table( void );<efont> |
 @rdesc 0:<tab>OK<nl>
        -1:<tab>Error<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x0D<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V1.16 | V1.00

 @target_clib V2.11
*/
int CGI_Remove_ContentEncoding_Table( void )
{
    asm xor bx, bx
    asm mov ah,CGI_CONTENTENCODING_INSTALL;
    asm { int CGIVECT  } ;
    return _DX;
}
#endif


/*************************************************************************/
//Remove user custom MIME table
/*************************************************************************/
#ifdef _cgi0C_
/*
 @doc DOC_cgi0C_
 ---------------------------------------------------------------
 Remove user custom MIME table
 ---------------------------------------------------------------
 @clib  CGI_Remove_MIME_Table | Deinstall user custom MIME table |
        <cfont>int CGI_Remove_MIME_Table( void );<efont> |
 @rdesc 0:<tab>OK<nl>
        -1:<tab>Error<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x0C<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00

 @target_clib V2.04
*/
int CGI_Remove_MIME_Table( void )
{
    asm mov ah,CGI_MIME_REMOVE;
    asm { int CGIVECT  } ;
    return _DX;
}
#endif


/*************************************************************************/
//Change user names and passwords
/*************************************************************************/
#ifdef _cgi14_
/*
 @doc DOC_cgi14_
 ---------------------------------------------------------------
 Change user names and passwords
 ---------------------------------------------------------------
 @clib  CGI_SetCredentials | Set web server credentials |
        <cfont>int CGI_SetCredentials( const char far *username,<nl>
        <tab><tab><tab><tab><tab><tab>const char far *password,<nl> 
        <tab><tab><tab><tab><tab><tab>int accType, int accIdx);<efont> |
 @parm  char far * | username |  User name. Maximum length is 19 characters.
 @parm  char far * | password |  Password. Maximum length is 19 characters.
 @parm  int        | accType  |  Account type: 0=Upload account, 1=Secure account
 @parm  int        | accIdx   |  Account index: 0=User0/Password0, 1=User1/Password1 etc.
 @rdesc 0:<tab>OK<nl>
        -1:<tab>Error<nl>
 @comm  The modified user name and password entries will only change for this run.
        The CHIP.INI will not be updated by this function.
        It lies within the responsibility of the user to call 
        <linkto>../BIOS/bios223.htm<linkmid>BIOS_Set_Ini_String()<linktail>
        for the modified entries.
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x14<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.41 | V1.41

 @target_clib V2.21
*/
int CGI_SetCredentials( const char far *username, 
                        const char far *password,
                        int accType, int accIdx)
{
    _BX = FP_SEG(password);
    _SI = FP_OFF(password);
    _ES = FP_SEG(username);
    _DI = FP_OFF(username);    
    asm mov ah, CGI_SET_CREDENTIALS;    
    asm mov dx, accType
    asm mov cx, accIdx 
    asm { int CGIVECT  } ;
    return _DX;
}
#endif

/*************************************************************************/
// SSI API
/*************************************************************************/
#ifdef _cgi81_
/*
 @doc DOC_cgi81_
 ---------------------------------------------------------------
 Set SSI file filter
 ---------------------------------------------------------------
 @clib  SSI_Set_File_Filter | Set Server Side Include (SSI) file filter |
        <cfont>int SSI_Set_File_Filter( char far * matchStr,<nl>
        <tab><tab><tab><tab><tab><tab> int matchType,<nl>
        <tab><tab><tab><tab><tab><tab> int server);<efont> |
 @parm  const char far * | matchStr  | Pointer to null-terminated string
        depending on the machted type
 @parm  int              | matchType | Match type, possible values are:<nl>
        <nl>
        <cfont>SSI_MATCH_FILE_NAME(0x01)<efont> = File name, Example: "table.htm"<nl>
        <cfont>SSI_MATCH_FILE_EXT (0x02)<efont> = File extension, Example: "htm"<nl>
        <cfont>SSI_MATCH_FILE_PATH(0x03)<efont> = Full path to file, Example: "/web/ssi/table.htm"<nl>
        <cfont>SSI_MATCH_DIR_NAME (0x04)<efont> = Directory name, Example: "ssi"<nl>
        <cfont>SSI_MATCH_DIR_PATH (0x05)<efont> = Directory path, Example: "/web/ssi"
 @parm  int              | server | 0 = register for HTTP server<nl>
                                    1 = register for HTTPS (SSL) server
 @rdesc 0:  success <nl>
        non-zero:  Failure, return value contains error code CGI_INVALID_METHOD

 @comm  SSI commands are special HTML comment tags in web pages, and parsed
        by the web server while the pages are being served. They allow
        dynamically generated content to be inserted into a static page,
        without having to dynamically generate the whole page.<nl>
        There's no official standard for SSI command. Thus we provide an API
        to register a SSI tag string and a handler function. When a registered
        SSI tag is found in a page being served, the handler function will be
        called to process it.

 @Also  cgi82.htm | SSI_Register_Tag  |
        cgi83.htm | SSI_Set_TagLength |
                  |

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x81<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int SSI_Set_File_Filter( char far * matchStr,
                         int matchType,
                         int server)
{
    _DI = FP_OFF(matchStr);
    _ES = FP_SEG(matchStr);
    _BX = matchType;
    _CX = server;
    _AH = SSI_SET_FILE_FILTER;
    asm { int CGIVECT  } ;
    return _AX;
}
#endif


/*************************************************************************/
// SSI API
/*************************************************************************/
#ifdef _cgi82_
/*
 @doc DOC_cgi82_
 ---------------------------------------------------------------
 Register a SSI tag string
 ---------------------------------------------------------------
 @clib  SSI_Register_Tag | Register Server Side Include (SSI) tag string |
        <cfont>int SSI_Register_Tag( const char far * tagStr,<nl>
        <tab><tab><tab><tab><tab>&nbsp; SSI_Handler handler,<nl>
        <tab><tab><tab><tab><tab>&nbsp; int server);<efont> |
 @parm  const char far * | tagStr  | Tag string, Pointer to null-terminated string
 @parm  SSI_Handler      | handler | Pointer to callback function<nl>
        <nl>
        <bold>Callback function prototype:<bolde><nl>
        <cfont>typedef<nl>
        &nbsp; int huge (far *SSI_Handler) (unsigned long conhandle, const char far * tagPtr);<efont><nl>
        <nl>
        <bold>Possible callback function return values:<bolde><nl>
        <cfont>SSI_OUTPUT_ENABLE(0x00)<efont> = Enable web server to output static content<nl>
        <cfont>SSI_OUTPUT_DISABLE(0x01)<efont> = Disable web server to output static content<nl>
        <cfont>SSI_ABORT_PAGE(0x02)<efont> = Stop processing the current file<nl>
        other = The web server will send an error message and stop serving the HTTP request
 @parm  int              | server | 0 = register for HTTP server<nl>
                                    1 = register for HTTPS (SSL) server
 @rdesc 0:  success <nl>
        non-zero:  Failure, return value contains error code CGI_INVALID_METHOD or
                   CGI_NO_FREE_ENTRY

 @comm  Currently only one tag per server can be registered.

 @Also  cgi81.htm | SSI_Set_File_Filter |
        cgi83.htm | SSI_Set_TagLength |
        cgi84.htm | SSI_Send_Buffer

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x82<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int SSI_Register_Tag( const char far * tagStr,
                      SSI_Handler handler,
                      int server)
{
    _DI = FP_OFF(tagStr);
    _ES = FP_SEG(tagStr);
    _SI = FP_OFF(handler);
    _BX = FP_SEG(handler);
    _CX = server;
    _AH = SSI_REGISTER_TAG;
    asm { int CGIVECT  } ;
    return _AX;
}
#endif


/*************************************************************************/
// SSI API
/*************************************************************************/
#ifdef _cgi83_
/*
 @doc DOC_cgi83_
 ---------------------------------------------------------------
 Set maximum SSI tag length
 ---------------------------------------------------------------
 @clib  SSI_Set_TagLength | Set maximum length of Server Side Include (SSI) tag string |
        <cfont>int SSI_Set_TagLength( int tagLength );<efont> |
 @parm  int | tagLength | length in bytes (default is 90)
 @rdesc 0:  success <nl>
        non-zero:  Failure, return value contains error code CGI_INVALID_METHOD

 @comm  Smaller values will optimize the performance of the SSI parser.

 @Also  cgi81.htm | SSI_Set_File_Filter |
        cgi83.htm | SSI_Set_TagLength |
                  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x83<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int SSI_Set_TagLength( int tagLength )
{
    _BX = tagLength;
    _AH = SSI_SET_TAG_LEN;
    asm { int CGIVECT  } ;
    return _AX;
}
#endif

/*************************************************************************/
// SSI API
/*************************************************************************/
#ifdef _cgi84_
/*
 @doc DOC_cgi84_
 ---------------------------------------------------------------
 Transmit a user buffer
 ---------------------------------------------------------------
 @clib  SSI_Send_Buffer | Transmit a user buffer to the HTTP client through the HTTP connection |
        <cfont>int SSI_Send_Buffer( unsigned long conHandle,<nl>
        <tab><tab><tab><tab><tab> const char far *buffer,<nl>
        <tab><tab><tab><tab><tab> int bufferlen,<nl>
        <tab><tab><tab><tab><tab> int flag );<efont> |
 @parm  unsigned long   | conHandle | connection handle, given by callback function
 @parm  const char far *| buffer    | pointer to send buffer
 @parm  int | bufferlen | length of buffer in bytes, max. 32767
 @parm  int | flag      | flag, set to 1

 @rdesc 0:  success <nl>
        non-zero:  Failure, return value contains error code

 @comm  Smaller values will optimize the performance of the SSI parser.

 @Also  cgi81.htm | SSI_Set_File_Filter |
        cgi82.htm | SSI_Register_Tag    |
                  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x84<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00

 @target_clib V2.02
*/
int SSI_Send_Buffer( unsigned long conHandle,
                     const char far *buffer,
                     int bufferlen,
                     int flag )
{
    _BX = (unsigned int)(conHandle>>16);
    _SI = (unsigned int)conHandle;
    _DI = FP_OFF(buffer);
    _ES = FP_SEG(buffer);
    _CX = bufferlen;
    _DX = flag;
    _AH = SSI_SEND_BUFFER;
    asm { int CGIVECT  } ;
    return _AX;
}
#endif

/*************************************************************************/
// SSI API
/*************************************************************************/
#ifdef _cgi85_
/*
 @doc DOC_cgi85_
 ---------------------------------------------------------------
 Deregister a SSI tag string
 ---------------------------------------------------------------
 @clib  SSI_Deregister_Tag | Deregister Server Side Include (SSI) tag string |
        <cfont>int SSI_Deregister_Tag( SSI_Handler handler,<nl>
        <tab><tab><tab><tab><tab><tab>int server);<efont> |
 @parm  SSI_Handler      | handler | Pointer to installed callback function
 @parm  int              | server | 0 = deregister for HTTP server<nl>
                                    1 = deregister for HTTPS (SSL) server
 @rdesc 0:  success <nl>
        non-zero:  Failure, return value contains error code CGI_INVALID_METHOD

 @Also  cgi81.htm | SSI_Set_File_Filter |
        cgi83.htm | SSI_Set_TagLength |
        cgi85.htm | SSI_Register_Tag

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x85<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.21 | V1.21

 @target_clib V2.15
*/
int SSI_Deregister_Tag(  SSI_Handler handler,
                         int server)
{
    _SI = FP_OFF(handler);
    _BX = FP_SEG(handler);
    _CX = server;
    _AH = SSI_DEREGISTER_TAG;
    asm { int CGIVECT  } ;
    return _AX;
}
#endif


/*************************************************************************/
// SSI API
/*************************************************************************/
#ifdef _cgi86_
/*
 @doc DOC_cgi86_
 ---------------------------------------------------------------
 Get SSI connection parameters
 ---------------------------------------------------------------
 @clib  SSI_Get_Connection_Params | Get SSI connection parameters |
        <cfont>int SSI_Get_Connection_Params( unsigned long conHandle,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; SSI_Params * params);<efont> |
 @parm  unsigned long  | conHandle | Connection handle, given by callback function.
 @parm  SSI_params *   | params    | Pointer to
        <linkto>../../cgistruc.htm#typedef_SSI_Params<linkmid>SSI_Params<linktail>
        structure, that will be filled with information.
        Set the structVersion member to zero before calling this function.
 @rdesc 0:  success <nl>
        non-zero:  Failure, return value contains error code CGI_INVALID_METHOD

 @Also  cgi81.htm | SSI_Set_File_Filter |
        cgi83.htm | SSI_Set_TagLength |
        cgi85.htm | SSI_Register_Tag

 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x86<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.24 | V1.24

 @target_clib V2.17
*/
int SSI_Get_Connection_Params(  unsigned long conHandle,
                                SSI_Params * params)
{
    _DI = FP_OFF(params);
    _ES = FP_SEG(params);
    _BX = (unsigned int)(conHandle>>16);
    _SI = (unsigned int)conHandle;
    _AH = SSI_GET_CONN_PARAMS;
    asm { int CGIVECT  } ;
    return _AX;
}
#endif

/*************************************************************************/
//Install custom headers table
/*************************************************************************/
#ifdef _cgi15_
/*
 @doc DOC_cgi15_
 ---------------------------------------------------------------
 Install custom headers table
 ---------------------------------------------------------------
 @clib  CGI_Install_Headers_Table | Install custom headers table |
        <cfont>int CGI_Install_Headers_Table( unsigned int entries,
        <tab><tab><tab>CUSTOM_HEADERS_TABLE far *headersTable);<nl>
 <efont> |
 @parm  unsigned int | entries     | Number of entries in custom headers table (must be equal to
                                       the user custom mime table size).
 @parm  CUSTOM_HEADERS_TABLE far * | headersTable | Pointer to custom
        <linkto>../../cgistruc.htm#typedef_CUSTOM_HEADERS_TABLE<linkmid>headers table<linktail>
 @rdesc 0:<tab>OK<nl>
        -1:<tab>Error (wrong number of entries)<nl>
 @comm The custom headers table references to the custom MIME table.
       So the headers table assigns every mime type defined
       in the MIME table one or more correspondent headers fields.<nl>
       The custom header table must be persistent. The RTOS does not make a copy.
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x15<linkmid>documentation<linktail>
        for more details.
 @target     SC12 | SC13 | SC11 | SC1x3 | SC2x
 @version    n/a  |  n/a |  n/a | V1.41 | V1.41

 @target_clib V2.21
*/
int CGI_Install_Headers_Table( unsigned int entries,
                               CUSTOM_HEADERS_TABLE far *headersTable)
{
    asm les di, headersTable
    asm mov bx, entries
    asm mov ah, CGI_HEADERS_INSTALL;
    asm { int CGIVECT  } ;
    return _DX;
}
#endif

/*************************************************************************/
//Remove custom headers table
/*************************************************************************/
#ifdef _cgiRmHeaders_
/*
 @doc DOC_cgiRmHeaders_
 ---------------------------------------------------------------
 Remove custom headers table
 ---------------------------------------------------------------
 @clib  CGI_Remove_Headers_Table | Deinstall custom headers table |
        <cfont>int CGI_Remove_Headers_Table( void );<efont> |
 @rdesc 0:<tab>OK<nl>
        -1:<tab>Error<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../cgi.htm#0xAB0x15<linkmid>documentation<linktail>
        for more details.
 @target     SC12 | SC13 | SC11 | SC1x3 | SC2x
 @version     n/a |  n/a |  n/a | V1.41 | V1.41

 @target_clib V2.21
*/
int CGI_Remove_Headers_Table( void )
{
    asm xor bx, bx
    asm mov ah, CGI_HEADERS_INSTALL;
    asm { int CGIVECT  } ;
    return _DX;
}
#endif

/*************************************************************************/
//end cgiapi.c

/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module      : CGIAPI.H
* Function    : cgi api prototypes
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\CGIAPI.H, 18, 18.04.2008 14:40:05, Christoph Stoidner$

*****************************************************************************/

#ifndef _CGI_API_H__
#define _CGI_API_H__

/*************************************************************************/
#include <CGI.H>

/*************************************************************************/
// definitions
/*************************************************************************/
#ifdef _MSC_VER /* If Microsoft C Compiler is used, define new FP_SEG and FP_OFF Macro */
   #ifdef FP_SEG
      #undef FP_SEG
   #endif
   #define FP_SEG(ptr)    ((unsigned int)(((unsigned long)ptr)>>16))

   #ifdef FP_OFF
      #undef FP_OFF
   #endif
   #define FP_OFF(ptr)    ((unsigned int)(((unsigned long)ptr)&0xFFFF))
#endif


#ifdef __cplusplus
extern "C" {
#endif


/*************************************************************************/
//install cgi function
/*************************************************************************/
int _cdecl CGI_Install (CGI_Entry far  * cgiptr);

/*************************************************************************/
//delete cgi function
/*************************************************************************/
int _cdecl CGI_Delete (char far * PathPtr);


/*************************************************************************/
//Get formitem
/*************************************************************************/
void _cdecl CGI_GetFormItem (const char far * ArgumentBufferPtr,
                             FormItem far * formitem);

/*************************************************************************/
//Get next formitem
/*************************************************************************/
int _cdecl CGI_GetNextItem(char far * ArgumentBufferPtr,
                           char far ** nextItemString);

/*************************************************************************/
//Set Main Page Name
/*************************************************************************/
int _cdecl CGI_SetMainPage (const char far *mainPageName);

/*************************************************************************/
//Set Main Page Name (POST method)
/*************************************************************************/
int _cdecl CGI_SetMainPagePost (const char far *mainPageName);

/*************************************************************************/
//Set Root Drive
/*************************************************************************/
int _cdecl CGI_SetRootDrive (const char driveLetter);

/*************************************************************************/
//Get Root Drive
/*************************************************************************/
char _cdecl CGI_GetRootDrive (void);

/*************************************************************************/
//Set Root Dir
/*************************************************************************/
int _cdecl CGI_SetRootDir (const char far *rootDirName);

/*************************************************************************/
//Get Main Page Name
/*************************************************************************/
int _cdecl CGI_GetMainPage(char far **mainPageName);

/*************************************************************************/
//Get Main Page Name (Post method)
/*************************************************************************/
int _cdecl CGI_GetMainPagePost(char far **mainPageName);

/*************************************************************************/
//Get Root Dir
/*************************************************************************/
int _cdecl CGI_GetRootDir(char far **rootDirName);

/*************************************************************************/
//Install cgi function on http error
/*************************************************************************/
int _cdecl CGI_Install_Func_OnErr( unsigned int error_state,
                                   void far *CgiFuncOnErr);

/*************************************************************************/
//Install cgi function on http file upload
/*************************************************************************/
int _cdecl CGI_Install_Func_OnUpload(void far *CgiFuncOnUpload);

/*************************************************************************/
//Enable/Disable HTTP file upload
/*************************************************************************/
int _cdecl CGI_Enable_Upload(int enable);

/*************************************************************************/
//Install MIME table
/*************************************************************************/
int _cdecl CGI_Install_MIME_Table( unsigned int entries,
                                   CUSTOM_MIMETYPES_TABLE far *mimeTable);

/*************************************************************************/
//Install content-encoding table
/*************************************************************************/
int _cdecl CGI_Install_ContentEncoding_Table( unsigned int entries,
                   CUSTOM_CONTENTENCODING_TABLE far *contentEncodingTable);
/*************************************************************************/
//Install content-encoding table
/*************************************************************************/
int _cdecl CGI_Remove_ContentEncoding_Table( void );

/*************************************************************************/
//Remove MIME table
/*************************************************************************/
int _cdecl CGI_Remove_MIME_Table( void );

/*************************************************************************/
//Set Cookie
/*************************************************************************/
int _cdecl CGI_SetCookie(const char          *name,
                         const char          *value,
                         const char          *domain,
                         const unsigned long *expires,
                         const char          *path,
                         const int            secure,
                         rpCgiPtr             CgiRequest);

/*************************************************************************/
//Get Cookie
/*************************************************************************/
int _cdecl CGI_GetCookie(char far **name,
                         char far **value,
                         char far **domain,
                         char far **path,
                         char far **port,
                         char far **version,
                         rpCgiPtr CgiRequest);

/*************************************************************************/
// Encode URL
/*************************************************************************/
void _cdecl CGI_UrlEncode(char *dst, const char far *src);

/*************************************************************************/
// Decode URL
/*************************************************************************/
void _cdecl CGI_UrlDecode(char far *dst, const char far *src);

/*************************************************************************/
//Get Argument
/*************************************************************************/
int _cdecl CGI_GetArgument(char far **name,
                           char far **value,
                           rpCgiPtr CgiRequest);

/*************************************************************************/
// Set user names and passwords
/*************************************************************************/
int _cdecl CGI_SetCredentials( const char far *username,
                               const char far *password,
                               int accType, int accIdx);

/*************************************************************************/
// Install custom headers table
/*************************************************************************/
int _cdecl CGI_Install_Headers_Table( unsigned int entries,
                                      CUSTOM_HEADERS_TABLE far *headersTable);

/*************************************************************************/
// Remove custom headers table
/*************************************************************************/
int _cdecl CGI_Remove_Headers_Table( void );


/*************************************************************************/
//SSI API
/*************************************************************************/
int _cdecl SSI_Set_File_Filter( char far * matchStr,
                                int matchType,
                                int server);
int _cdecl SSI_Register_Tag   ( const char far * tagStr,
                                SSI_Handler handler,
                                int server);
int _cdecl SSI_Deregister_Tag(  SSI_Handler handler,
                                int server);
int _cdecl SSI_Set_TagLength  ( int tagLength );
int _cdecl SSI_Send_Buffer    ( unsigned long conHandle,
                                const char far *buffer,
                                int bufferlen,
                                int flag );
int _cdecl SSI_Get_Connection_Params ( unsigned long conHandle,
                                SSI_Params * params );
#ifdef __cplusplus
}
#endif

/*************************************************************************/
#endif /* _CGI_API_H__*/
/*************************************************************************/
//end cgiapi.h

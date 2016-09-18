/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module        : CGI.H
* Function      : types and definitions for access to webservers cgi
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\CGI.H, 17, 04.01.2009 15:02:32, Jack Gatrost$

*****************************************************************************/

#ifndef _CGI_H__
#define _CGI_H__

/*****************************************************************************/
//CGI defines
/*****************************************************************************/

//Cgi HTTP requests
#define CgiHttpGet                    1  /*  Cgi request is HTTP GET  */
#define CgiHttpHead                   2  /*  Cgi request is HTTP HEAD */
#define CgiHttpPost                   3  /*  Cgi request is HTTP POST */
#define CgiHttpAll                  255  /*  Cgi request for all methods */


//Cgi HTTP responses
#define    CgiHttpOk                  0  /*  Cgi returns HTTP 200 Ok                 */
#define    CgiHttpOkStatic            1  /*  Cgi returns HTTP 200 Ok - Static Object */
#define    CgiHttpRedirect            2  /*  Cgi returns HTTP 302 Moved Temp         */
#define    CgiHttpNotModified         3  /*  Cgi returns HTTP 304 Not Modified       */
#define    CgiHttpUnauthorized        4  /*  Cgi returns HTTP 401 Unauthorized       */
#define    CgiHttpNotFound            5  /*  Cgi returns HTTP 404 Not Found          */
#define    CgiHttpOKNoDoc             6  /*  Cgi returns HTTP 204 No document follows*/
#define    CgiHttpNotAvail            7  /*  Cgi returns HTTP 503 Service Not Available */
#define    CgiHttpSrvError            8  /*  Cgi returns HTTP 500 Internal Srv Error    */


//CGI constants for content types ,fDatatype

#define  CGIDataTypeHtml                  0 /* CGI returns  text/html */
#define  CGIDataTypeImageGif              1 /* image/gif */
#define  CGIDataTypeApplet                2 /* application/octet-stream */
#define  CGIDataTypeText                  3 /* text/plain */
#define  CGIDataTypeImageJpeg             4 /* image/jpeg */
#define  CGIDataTypeImagePict             5 /* image/pict */
#define  CGIDataTypeImageTiff             6 /* image/tiff */
#define  CGIDataTypeImagePng              7 /* image/png  */
#define  CGIDataTypeForm                  8 /* application/x-www-form-urlencoded */
#define  CGIDataTypeIpp                   9 /* application/ipp */
#define  CGIDataTypeCss                  10 /* text/css */
#define  CGIDataTypeXml                  11 /* text/xml */
#define  CGIDataTypeWav                  12 /* audio/wav */
#define  CGIDataTypePdf                  13 /* application/pdf */
#define  CGIDataTypeJavaArchive          14 /* application/java-archive */
#define  CGIDataTypeOctet                15 /* application/octet-stream */
#define  CGIDataTypeVndWapWml            16 /* text/vnd.wap.wml */
#define  CGIDataTypeVndWapWbmp           17 /* image/vnd.wap.wbmp  */
#define  CGIDataTypeVndWapWmlc           18 /* application/vnd.wap.wmlc */
#define  CGIDataTypeVndWapWmlscript      19 /* text/vnd.wap.wmlscript   */
#define  CGIDataTypeVndWapWmlscriptc     20 /* text/vnd.wap.wmlscriptc  */
#define  CGIDataTypeScaleVectGraph       21 /* image/svg+xml */
#define  CGIDataTypeScaleVectGraphZipped 24 /* image/svg+xml (content-encoding: gzip) */

/*****************************************************************************/
//CGI API calls
/*****************************************************************************/
#define CGI_INSTALL                 0x01  /* Install a cgi function */
#define CGI_REMOVE                  0x02  /* Delete a cgi function  */
#define CGI_SETMAIN                 0x03  /* Set new main page name  */
#define CGI_SETROOTDIR              0x04  /* Set webservers root directory */
#define CGI_GETROOTDIR              0x05  /* Get webservers root directory */
#define CGI_GETMAIN                 0x06  /* Get name of main page*/
#define CGI_GETFORMITEM             0x07  /* Split argumentbuf into form item's name and value*/
#define CGI_FINDNEXTITEM            0x08  /* Find next formitem, if one */
#define CGI_INSTALL_PAS             0x09  /* Install a Turbo Pascal cgi procedure */
#define CGI_ERR_FUNC                0x0A  /* Install cgi function on http errors (e.g. 404) */
#define CGI_MIME_INSTALL            0x0B  /* Install a custom MIME table */
#define CGI_MIME_REMOVE             0x0C  /* Remove the custom MIME table */
#define CGI_CONTENTENCODING_INSTALL 0x0D  /* Install a custom content-encoding table */
#define CGI_SETMAIN_POST            0x0E  /* Set new main page name (POST method) */
#define CGI_GETMAIN_POST            0x0F  /* Get name of main page (POST method) */
#define CGI_SETROOTDRIVE            0x10  /* Set webservers root drive */
#define CGI_GETROOTDRIVE            0x11  /* Get webservers root drive */
#define CGI_ENABLEUPLOAD            0x12  /* Enable/disable http file upload */
#define CGI_UPLOAD_FUNC             0x13  /* Install cgi function on http uploads */
#define CGI_SET_CREDENTIALS         0x14  /* Set user names and passwords */
#define CGI_HEADERS_INSTALL         0x15  /* Installs a custom headers table */

/*****************************************************************************/
//CGI Error codes
/*****************************************************************************/
#define CGI_ARGUMENT_ERR_OK      0   /* Success */
#define CGI_ARGUMENT_ERR_NONE   -1   /* No argument found */

#define CGI_COOKIE_ERR_OK        0   /* Success */
#define CGI_COOKIE_ERR_SIZE     -1   /* Cookie too large or to much cookies         */
#define CGI_COOKIE_ERR_PARAM    -2   /* Wrong attributes (maybe no name or no value */
#define CGI_COOKIE_ERR_NONE     -3   /* No cookie found                             */

/*****************************************************************************/
//SSI API calls
/*****************************************************************************/
#define SSI_SET_FILE_FILTER        0x81  /* Set SSI file filter */
#define SSI_REGISTER_TAG           0x82  /* Register SSI tag */
#define SSI_SET_TAG_LEN            0x83  /* Set the maximum SSI tag length */
#define SSI_SEND_BUFFER            0x84  /* Transmit a user buffer to HTTP client */
#define SSI_DEREGISTER_TAG         0x85  /* Deregister SSI tag */
#define SSI_GET_CONN_PARAMS        0x86  /* Get SSI connection parameters */

/*****************************************************************************/
//CGI API general Errorcodes
/*****************************************************************************/
#define CGI_NOT_SUPPORTED            -2
#define CGI_ERROR                    -1
#define CGI_ENOERROR                  0

/*****************************************************************************/
//CGI API special Errorcodes, returned at the ax-register
/*****************************************************************************/
#define CGI_INVALID_METHOD           -1
#define CGI_INVALID_NAME             -2
#define CGI_INVALID_DIR              -3
#define CGI_NO_FREE_ENTRY            -4
#define CGI_NOT_FOUND                -5

/*****************************************************************************/
//CGI API flags
/*****************************************************************************/
#define CGI_FLAG_TRANSFERENCODING_CHUNKED  1 // if true, response will be sent in chunked mode
#define CGI_FLAG_CALL_AGAIN                2 // if true, the CGI will be called again
#define CGI_FLAG_REQUEST_ABORTED           4 // if true, the http request was aborted

/*****************************************************************************/
//SSI API match types
/*****************************************************************************/
#define SSI_MATCH_FILE_NAME   0x01
#define SSI_MATCH_FILE_EXT    0x02
#define SSI_MATCH_FILE_PATH   0x03
#define SSI_MATCH_DIR_NAME    0x04
#define SSI_MATCH_DIR_PATH    0x05
/*****************************************************************************/
//SSI API callback return values
/*****************************************************************************/
#define SSI_OUTPUT_ENABLE     0x00
#define SSI_OUTPUT_DISABLE    0x01
#define SSI_ABORT_PAGE        0x02

/*****************************************************************************/
//types
/*****************************************************************************/
typedef struct tag_cgi_table{

     char far *   PathPtr;      // name of the page
     int          method;       // httpmethod: get or post
     void far *   CgiFuncPtr;   // ptr to callback function of this page

} CGI_Entry;



/*
   this type is needed, if the function CGI_GETFORMITEM will be used,
   the user must set the pointers of the structure
   to his own buffers look at example submit.c.
*/

typedef struct tag_form_item{

     char far * NamePtr;
     char far * ValuePtr;

} FormItem;


/*
   the called cgi function gets as a parmeter
   a pointer of the following structure, which contains
   the needed http-request data and response data
*/

typedef struct {

    //Request fields, read only!!!!

    unsigned char       fConnectionId;         //  internal use only
    int                 fHttpRequest;          //  internal use only
    char far *          fPathPtr;              //  URL
    char far *          fHostPtr;              //  Host:
    char far *          fRefererPtr;           //  (at time not supported)
    char far *          fAgentPtr;             //  (at time not supported)
    char far *          fLanguagePtr;          //  (at time not supported)
    unsigned long       fBrowserDate;          //  Date:   (internal)
    char far *          fArgumentBufferPtr;    //  Pointer at argument buffer
    long                fArgumentBufferLength; //  length of argument buffer, -1 buffer empty
    char far *          fUserNamePtr;          //  Username from Authorization
    char far *          fPasswordPtr;          //  Password from Authorization


    long far *          fRemoteIPPtr;          //  Pointer to RemoteIP in wrong byte order
                                               //  , do not modify

    //Response fields,

    int                 fResponseState;          // internal, do not modify
    int                 fHttpResponse;           // response msg mostly CgiHttpOK
    int                 fDataType;               // content type mostly text/html
    char far *          fResponseBufferPtr;      // pointer to created dynamic html page
    long                fResponseBufferLength;   // length of the created page
    unsigned long       fObjectDate;             // internal, do not modify
    unsigned int        fHostIndex;              // internal, do not modify

    char far *          fSetCookieHeaders;      // The SetCookie header to send to browser
    int                 fNumOfSetCookieHeaders; // Number of cookies to send to browser
    char far *          fCookieHeader;          // The cookie header, recved from browser
    char far *          fResponseHeadersPtr;    // Pointer to a string that contains user 
                                                // specific headers. The headers have to 
                                                // be separated by "\r\n".    
    unsigned int        fFlags;                 // contains several flags according to the request
    unsigned long       fLongParam;     /* 32 bit parameter, could be used by the application
                                           to keep management data when the CGI_FLAG_CALL_AGAIN
                                           flag is used */
} rpCgi, far *rpCgiPtr;

// SSI callback handler
typedef int huge (far *SSI_Handler) (unsigned long conhandle, const char far * tagPtr);

// SSI connection parameters
typedef struct
{
    unsigned char             structVersion;
    /* Version of this struct, for future extenstions of this struct.
     * Set to zero for current version V0.*/
    unsigned char             serverHandle;  /* V0 member, Server handle<br>
                                              0 = HTTP / 1 = HTTPS (SSL) server */
    struct sockaddr_storage * peerSockAddr;  /* V0 member, Peer socket address */
    struct sockaddr_storage * localSockAddr; /* V0 member, Local socket address */
    char *                    pathPtr;       /* V0 member, URL path name */
    char *                    hostPtr;       /* V0 member, Host name */
    char *                    userNamePtr;   /* V0 member, User name from authorization */
    char *                    passwordPtr;   /* V0 member, Password from authorization */
} SSI_Params;

// User custom MIME table
typedef struct
{
  unsigned int mimeId;    // must be greater than internal numbers
  char far*    mimeExt;   // file extension, e.g. "gif"
  char far*    mimeType;  // mime type, e.g. "image/gif"
} CUSTOM_MIMETYPES_TABLE;

// User custom content-encoding table
typedef char far *CUSTOM_CONTENTENCODING_TABLE;

// Custom headers table
typedef char far *CUSTOM_HEADERS_TABLE;

/*****************************************************************************/
#endif /*_CGI_H__*/

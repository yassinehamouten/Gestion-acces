/****************************************************************************
* (C) 1999-2007 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module      : BIOS_API.H
* Function    : prototypes and constants fpr BIOS API library
* ---------------------------------------------------------------------------

$Header: BIOS_API.H, 29, 04.04.2008 11:03:52, Andre Pribil$

*****************************************************************************/

#ifndef _BIOS_API_H__
#define _BIOS_API_H__

#include <tcpipapi.h>

#ifdef CLIB_CUSTOMER_SPECIFIC
// Supply some optional patches for customer specific library.
// (For standard Beck library, this file does not exists.)
#include <BIOS_EXT.H>
#endif

/*****************************************************************************/
// Constants
/*****************************************************************************/
// Bit definitions for bit field returned by BIOS_Get_Features():
#define BGF_ETHERNET           (0x0001)
#define BGF_PPP_SERVER         (0x0002)
#define BGF_PPP_CLIENT         (0x0004)
#define BGF_WEB_SERVER         (0x0008)
#define BGF_TELNET_SERVER      (0x0010)
#define BGF_FTP_SERVER         (0x0020)
#define BGF_TFTP_SERVER        (0x0040)
#define BGF_DHCP_CLIENT        (0x0080)
#define BGF_IPV6               (0x0100)
#define BGF_SSLWEB_SERVER      (0x0200)

#define BGF_I2C_BUS       (0x00010000L)
#define BGF_HW_API        (0x00020000L)
#define BGF_RTOS_API      (0x00040000L)
#define BGF_PACKET        (0x00080000L)
#define BGF_XMODEM        (0x00100000L)
#define BGF_EXT_DISK      (0x00200000L)
#define BGF_SOFT_SPI      (0x00400000L)

#define BGF_SNMP_MIB      (0x01000000L)
#define BGF_UDP_CONFIG    (0x02000000L)
#define BGF_PING_CLIENT   (0x04000000L)
#define BGF_DEVICE_DRIVER (0x08000000L)
#define BGF_WEB_PUT       (0x10000000L)

// Maximum file path size for and name size for "long file names"
#define LFN_MAXPATH  (260)  // Including nil terminator
#define LFN_MAXNAME  (256)  // Including nil terminator

/* ---------------------------------------------------------------------*/
// MS-DOS File attributes (see fields xffattr and xst_dosattr) 

#define FJ_DA_NORMAL    0x00
#define FJ_DA_RDONLY    0x01
#define FJ_DA_HIDDEN    0x02
#define FJ_DA_SYSTEM    0x04
#define FJ_DA_VOLUME    0x08
#define FJ_DA_DIRENT    0x10
#define FJ_DA_ARCHIVE   0x20

// Bit definitions for bit field returned by BIOS_Select_Stdio():
    // 'ports' bit field
#define STDIO_EXT                 (0x01)
#define STDIO_COM                 (0x02)
#define STDIO_TELNET              (0x04)
#define STDIO_USER                (0x08)
#define STDIO_SSH                 (0x10)

    // 'direction' bit field
#define SET_STDOUT                (0x1)
#define SET_STDIN                 (0x2)

#define BDC_SAVE_1_FAT             (0x1)
#define BDC_ABORT_READ_WRITE       (0x2)


/*****************************************************************************/
//  Types
/*****************************************************************************/
typedef enum {FOCUS_SHELL = 1, FOCUS_APPLICATION = 2, FOCUS_BOTH = 3
 } IO_FOCUS ;

typedef enum { BATCH_CONCURRENT = 0, BATCH_SEQUENTIAL= 1
 } BATCH_MODE ;

typedef enum { SS_FTP_SERVER     = 0,
               SS_TELNET_SERVER  = 1,
               SS_WEB_SERVER     = 2,
               SS_SSL_WEB_SERVER = 3,
               SS_SSH_SERVER     = 4
 } SERVER_SPEC ;

typedef void huge _pascal (far *USER_ERROR_HANDLER) (int error_code) ;

typedef int huge _pascal (far *USER_INTNOTSUPPORTED_HANDLER) (int intnumber,
                                                              int ax) ;

typedef struct
{
    unsigned int  bytesPerSector;
    unsigned int  sectorsPerCluster;
    unsigned long freeClusters;
    unsigned long totalClusters;
} BiosDiskInfo;

/////////////////////////////////////////////////////////////////////
// CvStatS -  Statistics for BIOS_Execute_Ext("CV") report.
/////////////////////////////////////////////////////////////////////
typedef struct CvStatT
{
    // Inputs:  API user sets these prior to calling.

    unsigned            cvSize ;            // Size of this data structure.
    unsigned            cvQuiet ;           // Boolean non-zero for no console output.

    // Outputs:  Following report values are set by system within CV command action.

    unsigned             cvStatus ;             // Status: CV_STATUS_OK, ...
    unsigned long        cvTotalBytes ;         // Overall number of RTOS bytes.
    unsigned long        cvBadBytesCnt ;        // Number of bytes that did not verify.
    unsigned long        cvBadLoc ;             // Linear address of first bad byte.

    const unsigned char *cvFastCodeStart ;      // First block of RTOS code starts here.
    unsigned long        cvFastCodeByteCnt ;    // Size of first block [bytes]
    const unsigned char *cvCodeStart ;          // First block of RTOS code starts here
    unsigned long        cvCodeByteCnt ;        // Size of second block [bytes]

    unsigned             cvIvtChgCnt ;          // Number of vectors different.
    unsigned             cvIvtFirstChgIdx ;     // IVT index of first different vector.

} CvStatS ;

    // Values reported in 'cvStatus' by CV command.
#define CV_STATUS_OK                  (0)
#define CV_STATUS_DETECT_CODE_DAMAGE  (1)
#define CV_STATUS_MALLOC_FAILED       (2)



/////////////////////////////////////////////////////////////////////
// DiskStatS -  Statistics for CHKDSK summary report.
/////////////////////////////////////////////////////////////////////
typedef struct DiskStatT
{
    unsigned        dsStructSize ;          // = sizeof(DiskStatS)
    unsigned char   dsPlpFormat ;           // TRUE if drive has PLP format.
    unsigned char   dsParamErr ;            // TRUE if had command line problems.
    unsigned char   dsDidCheck ;            // FALSE if had resource problem.
    unsigned char   dsFaultDetected ;       // TRUE if some fault detected.
    unsigned char   dsFatSize ;             // Bits per FAT entry: 12, 16 or 32
    unsigned char   dsFatNum ;              // Number of FAT drive has.
    unsigned        dsProgressTick ;        // Upcounter to indicate activity.
    unsigned        dsClusterSize ;         // [bytes]
    unsigned        dsSectorPerCluster ;    // [sectors]
    unsigned        dsRootNodes ;           // [Directory nodes]
    unsigned long   dsTotalClusters ;       // [clusters]
        // Remaining members are fault counters.
    unsigned long   dsLostClusters ;        // Allocated, but in no file/dir chain.
    unsigned long   dsBadClusters ;         // Bad cluster count.
    unsigned long   dsClustersNotAlloc ;    // In use, but not allocated.
    unsigned long   dsCorruptLFN ;          // Long file names bad
    unsigned long   dsCorruptLFNNodes ;     // Long file names nodes bad
    unsigned long   dsBadDotRef ;           // '.' or '..' dir reference wrong.
        // End of errors fixed by "/F" option.
    unsigned long   dsMultiDots ;           // '.' or '..' repeated.
    unsigned long   dsMultiUseCluster ;     // Cluster appears in more than on chain.
    unsigned long   dsDirDepthExceeded ;    // The CKDISK_MAX_DEPTH limit exceeded.
    unsigned long   dsInvalidClusterNo ;    // In a file.
    unsigned long   dsInvalidClusterFix ;   // END_OF_CHAIN set in a file.
    unsigned long   dsBlockFailCnt ;        // Block writes failed at "fix"
    unsigned long   dsInfiniteLoop ;        // File contains infinite loop.
    unsigned long   dsFatMismatch ;         // Sectors diff between FAT0 & FAT1.
    unsigned long   dsFatFixFailCnt ;       // Block writes failed at "fix"
    unsigned long   dsFileTooShort ;        // Too few clusters in chain.
    unsigned long   dsFileTooLong ;         // Too many cluster in chain
    unsigned        dsStatusFlags;          // Discrete bits (see DS_* below).

} DiskStatS ;


// Bit assignments for 'DiskStatS.dsStatusFlags
#define DS_CLUSTERS_ALIGNED     (0x1)       // SD card clusters aligned to flash page.
#define DS_CLUSTERS_MISALIGNED  (0x2)       // SD card clusters misaligned to flash page.

//////////////////////////////////////////////////////////////////////////
//  CmdFeedbackS  -  Used by BIOS_ExecuteExt() API for certain commands.
//////////////////////////////////////////////////////////////////////////
typedef struct CmdFeedbackT
{
    unsigned int  cfSize ;      // Size of this user provided data structure.
    int           cfStatus ;    // Return value from command.
    unsigned long cfProgress ;  // Up counter indicating progress.
    unsigned long cfGoal ;      // Count expected upon completion.

}  CmdFeedbackS ;

//////////////////////////////////////////////////////////////////////////
//  ProgFeedbackS  -  Used by BIOS_ExecuteExt() API for EXE programs
//////////////////////////////////////////////////////////////////////////
typedef struct ProgFeedbackT
{
    unsigned int    pfSize ;        // Size  of structure, with user bytes
    int             pfExitCode ;    // DOS exit code set by system.

} ProgFeedbackS ;

#define FS_MAXSHORTNAME 12              // 8 name + 1 dot + 3 extension
                                        //  not including terminating NIL.
#define FS_SHORTBUF     FS_MAXSHORTNAME+2   // Space for NIL char rounded up
                                            //  for WORD alignment.

#define FS_MAXLONGPATH  (260)               // Including NIL char

typedef struct tag_filetimestamp
{
    // Date = ((year - 80) shl 9) or (month shl 5)) or day
    unsigned short int filedate;
    // Time = (hour shl 11) or (min shl 5)) or (sec / 2)
    unsigned short int filetime;
} FS_FILETIME ;                        // Time & date last modified

// Define FILEFIND_OLD_RTOS before inclusion of BIOS_API.H header
// if application program must operate with versions of @Chip-RTOS
// prior to the SC1x @Chip-RTOS 1.20 version.
#ifdef FILEFIND_OLD_RTOS
#define FFIND_PRIVATE_SIZE (180)
#else
#define FFIND_PRIVATE_SIZE (32)
#endif

typedef struct filefind {

    char    filename[12];               // Null terminated filename
    char    fileext[4];                 // and extension
    unsigned short fileattr;            // MS-DOS file attributes
    short int      reserved;            // Reserved

    FS_FILETIME filetimestamp;          // Time & date last modified

    unsigned long   filesize ;              // File size
#ifndef FILEFIND_OLD_RTOS
    char    szShort_Name[FS_SHORTBUF] ;
#endif

    // private_field[] area is used internally by the @Chip-RTOS.
    char            private_field[FFIND_PRIVATE_SIZE]; 

} FILE_FIND ;


// For long file names
typedef struct LFN_filefind {
    char    far    *pszLong_Name ;          // FS_MAXLONGPATH size

    char            filename[12];           // Null terminated filename
    char            fileext[4];             // and extension
    unsigned short  fileattr;               // MS-DOS file attributes
    short int       reserved;               // Reserved

    FS_FILETIME filetimestamp;              // Time & date last modified

    unsigned long   filesize ;              // File size
    char            szShort_Name[FS_SHORTBUF] ; // DOS Alias

    // private_field[] area is used internally by the @Chip-RTOS.
    char            private_field[40]; 

} LFN_FILE_FIND ;

//For modifying FTP, telnet or SSH user/pw settings
typedef struct  tagServerCredentials{
        unsigned int idx;               //user/password array index
        const char * user;              //max. length 20 (including the '\0' character)
        const char * password;          //max. length 20 (include the '\0' character)
        unsigned int ftpAccessRights;  //ftp access rights (1: write denied)
        const char * sshUserKeyFile;   //ssh user key file name
}ServerCredentials;



// For BIOS_Install_User_Stdio function ///////////////////////////////
typedef int  huge _cdecl (far *USER_KBHIT) (void);
typedef void huge _cdecl (far *USER_PUTCH) (char chr);
typedef void huge _cdecl (far *USER_PUTSTR)(const char far * pch, int n);
typedef int  huge _cdecl (far *USER_GETCH) (void);

typedef struct tag_user_stdio
{
   USER_KBHIT   user_kbhit;
   USER_GETCH   user_getch;
   USER_PUTCH   user_putch;
   USER_PUTSTR  user_putstr;

} USER_STDIO_FUNCS ;


// For BIOS_Connection_Handler function ///////////////////////////////
// See TCPIPAPI.H header file for definition of sockaddr_in structure
typedef int  huge _cdecl (far *CONN_HANDLER) (struct sockaddr far *sockptr);

// For BIOS_Install_UDP_Cfg_Callback function ///////////////////////////////
typedef struct UdpCfgSrv_UserCBInfo {

     int    length ;                        // Length of this structure
     struct sockaddr far *fromAddrPtr;      // Sender address pointer
     int    udpCfgSD;                       // Socket descriptor from
                                            //   UDP Config Server Socket
     char   far *dataPtr;                   // Data of Request package
     unsigned   dataLength;                 // Length of request package

} UDPCFGSRV_USERCBINFO ;

typedef void huge _cdecl (far *UDP_CFG_CALLBACK)(struct UdpCfgSrv_UserCBInfo *infoPtr) ;


/*****************************************************************************/
// Prototypes
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

unsigned int  _cdecl BIOS_getch (void) ;
unsigned int  _cdecl BIOS_kbhit (void) ;
void          _cdecl BIOS_putch (unsigned char output) ;
unsigned long _cdecl BIOS_Get_Serial_Number (void) ;
unsigned long _cdecl BIOS_Get_Product_Serial_Number (void) ;
unsigned int  _cdecl BIOS_Get_Hardware_Rev (void) ;
unsigned int  _cdecl BIOS_Get_Product_Hardware_Rev (void) ;
int           _cdecl BIOS_Execute (const char far *command_line) ;
int           _cdecl BIOS_ExecuteExt (const char far *command_line,
                                            void far *report) ;
void          _cdecl BIOS_Set_Timer_0x1C (unsigned int interval_ms) ;
void          _cdecl BIOS_Set_Timer_0xAF (unsigned int interval_ms) ;

void          _cdecl BIOS_Set_Focus (IO_FOCUS focus) ;
unsigned int  _cdecl BIOS_Get_Boot_Version (void) ;
unsigned int  _cdecl BIOS_Get_RTOS_Version (unsigned int *beta_flag) ;
void          _cdecl BIOS_Set_Batch_Mode (BATCH_MODE mode, unsigned int enable_timeout) ;
void          _cdecl BIOS_Batch_Continue (void) ;
unsigned long _cdecl BIOS_Get_Features (void) ;
void          _cdecl BIOS_Get_MAC (unsigned char far *mac) ;
void          _cdecl BIOS_Get_MAC2 (unsigned char far *mac);
void          _cdecl BIOS_Power_Save (void) ;
int           _cdecl BIOS_Power_SaveEx (unsigned char mode);
void          _cdecl BIOS_Config_Server_Level (unsigned int level) ;
USER_ERROR_HANDLER _cdecl BIOS_Install_Error_Handler (USER_ERROR_HANDLER vector) ;
int _cdecl BIOS_Set_Error(unsigned errorCode,
                          unsigned long details);
USER_INTNOTSUPPORTED_HANDLER _cdecl BIOS_Install_IntNotSupported_Handler (USER_INTNOTSUPPORTED_HANDLER vector);

void          _cdecl BIOS_Reboot (void) ;
void          _cdecl BIOS_Version_String (char far *version, int max_len) ;

int           _cdecl BIOS_Set_Ini_String (const char far *section,
                                          const char far *item_name,
                                          const char far *item_text) ;
int           _cdecl BIOS_Get_Ini_String (const char far *section,
                                          const char far *item_name,
                                          char far *item_text,
                                          unsigned int max_len) ;
int           _cdecl BIOS_Set_Ini_String_Ext (const char far *fileName,
                                              const char far *section,
                                              const char far *item_name,
                                              const char far *item_text) ;
int           _cdecl BIOS_Get_Ini_String_Ext (const char far *fileName,
                                              const char far *section,
                                              const char far *item_name,
                                              char far *item_text,
                                              unsigned int max_len) ;
                                              
void          _cdecl BIOS_Set_Focus_Hotkey (unsigned char hotkey) ;

void          _cdecl BIOS_Get_Device_Names (char far **fixed_name,
                                            char far **configured_name) ;
void          _cdecl BIOS_Get_Device_NamesEx (char far **fixed_name,
                                              char far **configured_name,
                                              char far **beckproduct_name) ;

int           _cdecl BIOS_Server_On_Off (SERVER_SPEC which_server,
                                         unsigned int activate) ;
int           _cdecl BIOS_Server_State (SERVER_SPEC which_server);

int           _cdecl BIOS_Fast_Findfirst (const char far *filename,
                                          FILE_FIND far *find,
                                          unsigned int attributes) ;
int           _cdecl BIOS_Fast_Findnext  (FILE_FIND far *find) ;
int           _cdecl BIOS_Fast_Find_Done (FILE_FIND far *find) ;
unsigned int  _cdecl BIOS_Ethernet_State (unsigned int *init_error,
                                          unsigned int *phy_state);
int           _cdecl BIOS_Set_Memory_Gap (unsigned int paragraphs) ;
int           _cdecl BIOS_Select_Stdio (unsigned int ports, unsigned char direction) ;
unsigned int  _cdecl BIOS_Get_Stdio (void) ;
void          _cdecl BIOS_Install_User_Stdio (const USER_STDIO_FUNCS far *vectors) ;
int           _cdecl BIOS_Connection_Handler (CONN_HANDLER handler,
                                              SERVER_SPEC which_server) ;
int           _cdecl BIOS_Get_File_Sharing_Mode (void) ;
void          _cdecl BIOS_Set_File_Sharing_Mode (unsigned int enable_sharing) ;
int           _cdecl BIOS_Get_File_Name (char far * filename, unsigned int handle) ;

void          _cdecl BIOS_Install_UDP_Cfg_Callback (UDP_CFG_CALLBACK callback) ;
void          _cdecl BIOS_Get_PPPServer_IP (char far *ipaddr);
void          _cdecl BIOS_Get_PPPClient_IP (char far *ipaddr);

void          _cdecl BIOS_Write_Persistent_Data ( const void far *data, unsigned char size );
void          _cdecl BIOS_Read_Persistent_Data  ( void far *data, unsigned char size );

int         _cdecl BIOS_LFN_Findfirst (const char far    *filename,
                                       LFN_FILE_FIND far *find,
                                       unsigned char      lock_the_node) ;
int         _cdecl BIOS_LFN_Findnext  (LFN_FILE_FIND far *find) ;
void        _cdecl BIOS_LFN_Find_Done (LFN_FILE_FIND far *find) ;
int         _cdecl BIOS_LFN_Get_Name (char far * filename, 
                                      unsigned int handle) ;
void          _cdecl BIOS_Disk_Info (unsigned int drive, 
                                     BiosDiskInfo * disk_info) ;
unsigned long _cdecl BIOS_Disk_Space (unsigned int drive) ;

int           _cdecl BIOS_Disk_Close (const char *path, unsigned int flags) ;


int _cdecl   BIOS_Set_ServerCredentials(int server, ServerCredentials * sc);




#ifdef __cplusplus
}
#endif


/*****************************************************************************/
#endif /*_BIOS_API_H__*/

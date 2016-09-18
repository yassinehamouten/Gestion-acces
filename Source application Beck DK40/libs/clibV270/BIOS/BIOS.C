/****************************************************************************
* (C) 1999-2013 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : BIOS.C
* Function       : BIOS API functions
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\BIOS\BIOS.C, 83, 16.02.2009 17:17:41, Markus Bartat$

*****************************************************************************/


/****************************************************************************/
//includes
/****************************************************************************/

#include <dos.h>

#include <config.h>
#include <common.h>
#include <BIOS_API.H>

/*
 @doc DOC_INDEX
 ---------------------------------------------------------------
 BIOS API Table of Contents
 ---------------------------------------------------------------
 @clibidx  <tab><cfont>#include <InBraces BIOS_API\.H><efont> |
    <tab><linkto>#stdio<linkmid>stdio<linktail><tab>
    <linkto>#Files<linkmid>Files<linktail><tab>
    <linkto>#Ethernet/PPP<linkmid>Ethernet/PPP <linktail><tab>
    <linkto>#IPC@CHIP&reg;<linkmid>IPC@CHIP&reg;<linktail><tab>
    
 Here are the interface definition for the BIOS Interrupts.<nl>
 <nl>
 The system BIOS in a regular PC offers many services, only a subset of which is
 required in embedded systems.<s2>  This subset is described here.<nl>

 Some additional functions not found in a normal PC BIOS are
 provided for your convenience.<nl><nl>
 
 @textlinkpara  BIOS API | ../../biosstruc.htm | Data Structures  | 
 
 @libcat1  stdio   | bios101 | BIOS_kbhit | Test if character is ready on standard input. |
 @libcat1  stdio   | bios100 | BIOS_getch | Get character from standard input, with wait. |
 @libcat1  stdio   | bios10E | BIOS_putch | Output character on standard output. |
 @libcat1  stdio   | bios211 | BIOS_Set_Focus | Select stdio focus. |
 @libcat1  stdio   | bios225 | BIOS_Set_Focus_Hotkey | Set the stdio focus key. |
 @libcat1  stdio   | bios233 | BIOS_Select_Stdio | Specify stdin/stdout channels. |
 @libcat1  stdio   | bios234 | BIOS_Get_Stdio | Check stdin/stdout channels. |
 @libcat1  stdio   | bios235 | BIOS_Install_User_Stdio | Install user stdio handlers. |


 @libcat2  Files   | bios237 | BIOS_Get_File_Sharing_Mode | Check the file sharing mode.|
 @libcat2  Files   | bios237a | BIOS_Set_File_Sharing_Mode | Enable/Disable file sharing.|
 @libcat2  Files   | bios228 | BIOS_Fast_Findfirst | Fast findfirst.|
 @libcat2  Files   | bios229 | BIOS_Fast_Findnext | Fast findnext.|
 @libcat2  Files   | bios230 | BIOS_Fast_Find_Done | Unlock directory after search.|
 @libcat2  Files   | bios238 | BIOS_Get_File_Name | Get file name by handle.|
 @libcat2  Files   | bios22A | BIOS_LFN_Findfirst | Long file name findfirst.|
 @libcat2  Files   | bios22B | BIOS_LFN_Findnext | Long file name findnext.|
 @libcat2  Files   | bios22C | BIOS_LFN_Find_Done | Unlock directory after search.|
 @libcat2  Files   | bios23A | BIOS_LFN_Get_Name | Get long file name by handle.|
 @libcat2  Files   | bios20A | BIOS_Disk_Info | Report disk statistics.|
 @libcat2  Files   | bios20Aa | BIOS_Disk_Space | Report disk bytes free.|
 @libcat2  Files   | bios20C | BIOS_Disk_Close | Close disk.|


 @libcat3  Ethernet/PPP   | bios217 | BIOS_Get_MAC |
        Get MAC address of the Ethernet interface.|
 @libcat3  Ethernet/PPP   | bios258 | BIOS_Get_MAC2 |
        Get MAC address of the second ethernet interface.|
 @libcat3  Ethernet/PPP  | bios219 | BIOS_Config_Server_Level |
        Change level for configuration server.|
 @libcat3  Ethernet/PPP  | bios227 | BIOS_Server_On_Off | Suspend/Resume system servers.|
 @libcat3  Ethernet/PPP  | bios22D | BIOS_Server_State | Get state of system servers.|
 @libcat3  Ethernet/PPP  | bios231 | BIOS_Ethernet_State | Detect Ethernet link state.|
 @libcat3  Ethernet/PPP  | bios236 | BIOS_Connection_Handler |
            Install a system server connection handler.|
 @libcat3  Ethernet/PPP  | bios23B | BIOS_Set_Ethernet_Mode |
           Set operation mode of the internal ethernet controller.|
 @libcat3  Ethernet/PPP  | bios23C | BIOS_Set_ServerCredentials |
           Modify user/password settings for FTP,Telnet or SSH server. |
 @libcat3  Ethernet/PPP  | bios240 | BIOS_Install_UDP_Cfg_Callback |
            Install a UDP Config Server user callback.|
 @libcat3  Ethernet/PPP  | bios250 | BIOS_Get_PPPServer_IP |
            Get the IP address of the PPP server. |
 @libcat3  Ethernet/PPP  | bios255 | BIOS_Get_PPPClient_IP |
            Get the IP address of the PPP client. |

 @libcat4  IPC@CHIP&reg;   | bios200 | BIOS_Get_Serial_Number |
    Get the serial number of the IPC@CHIP&reg;.|
 @libcat4  IPC@CHIP&reg;   | bios200A | BIOS_Get_Product_Serial_Number |
    Get the serial number of the BECK product.|
 @libcat4  IPC@CHIP&reg;   | bios200B | BIOS_Get_Hardware_Rev |
    Get the hardware revision number of the IPC@CHIP&reg; device.|
 @libcat4  IPC@CHIP&reg;   | bios200C | BIOS_Get_Product_Hardware_Rev |
    Get the hardware revision number of the BECK product.|
 @libcat4  IPC@CHIP&reg;   | bios212 | BIOS_Get_Boot_Version | Get bootstrap version number.|
 @libcat4  IPC@CHIP&reg;   | bios213 | BIOS_Get_RTOS_Version | Get RTOS version.|
 @libcat4  IPC@CHIP&reg;   | bios222 | BIOS_Version_String | Get RTOS version string.|

 @libcat4  IPC@CHIP&reg;   | bios207 | BIOS_Execute | Execute a command shell command.|
 @libcat4  IPC@CHIP&reg;   | bios20B | BIOS_ExecuteExt | 
            Execute a shell command with feedback.|
 @libcat4  IPC@CHIP&reg;   | bios208 | BIOS_Set_Timer_0x1C | Set timer 0x1C interval.|
 @libcat4  IPC@CHIP&reg;   | bios209 | BIOS_Set_Timer_0xAF | Set timer 0xAF interval.|
 @libcat4  IPC@CHIP&reg;   | bios214 | BIOS_Set_Batch_Mode | Set Batch file mode.|
 @libcat4  IPC@CHIP&reg;   | bios215 | BIOS_Batch_Continue | Continue batch file execution.|
 @libcat4  IPC@CHIP&reg;   | bios216 | BIOS_Get_Features | Report RTOS features.|
 @libcat4  IPC@CHIP&reg;   | bios218 | BIOS_Power_Save | Enter low power standby mode.|
 @libcat4  IPC@CHIP&reg;   | bios218A | BIOS_Power_SaveEx | Make power save mode settings.|
 @libcat4  IPC@CHIP&reg;   | bios220 | BIOS_Install_Error_Handler | Install a user fatal error handler. |
 @libcat4  IPC@CHIP&reg;   | bios259 | BIOS_Set_Error | Set fatal error record |
 @libcat4  IPC@CHIP&reg;   | bios22E | BIOS_Install_IntNotSupported_Handler | Install a user int not supported handler. |
 @libcat4  IPC@CHIP&reg;   | bios221 | BIOS_Reboot | Reboot the CPU.|
 @libcat4  IPC@CHIP&reg;   | bios223 | BIOS_Set_Ini_String | Insert an entry into CHIP.INI.|
 @libcat4  IPC@CHIP&reg;   | bios224 | BIOS_Get_Ini_String | Get an entry from CHIP.INI.|
 @libcat4  IPC@CHIP&reg;   | bios241 | BIOS_Set_Ini_String_Ext | Insert an entry into given INI file.|
 @libcat4  IPC@CHIP&reg;   | bios242 | BIOS_Get_Ini_String_Ext | Get an entry from given INI file.|
 @libcat4  IPC@CHIP&reg;   | bios226 | BIOS_Get_Device_Names | Get the IPC@CHIP&reg; device names.|
 @libcat4  IPC@CHIP&reg;   | bios226A | BIOS_Get_Device_NamesEx | Get the IPC@CHIP&reg; device names. (Extended)|
 @libcat4  IPC@CHIP&reg;   | bios232 | BIOS_Set_Memory_Gap |
            Set a memory gap between DOS programs.|
 @libcat4  IPC@CHIP&reg;   | bios245 | BIOS_Write_Persistent_Data |
            Writes persistent data into the @CHIPs Flash memory |
 @libcat4  IPC@CHIP&reg;   | bios246 | BIOS_Read_Persistent_Data |
            Reads persistent data from the @CHIPs Flash memory. |

*/

// Local Data ////////////////////////////////////////////////////////////////
#define BIOS_SWI_1                 (0x10)

// SWI 0x10 services (AH reg)
#define BIOS_GETCHAR               (0x00)
#define BIOS_CHAR_READY            (0x01)
#define BIOS_PUTCHAR               (0x0E)

#define BIOS_SWI_2                 (0xA0)

// SWI 0xA0 services (AH reg)
#define BIOS_GET_SN                (0x00)
#define BIOS_EXECUTE               (0x07)
#define BIOS_SET_TIMER_1C          (0x08)
#define BIOS_SET_TIMER_AF          (0x09)
#define BIOS_DISK_INFO             (0x0A)
#define BIOS_EXEC_EXT              (0x0B)
#define BIOS_DISK_CLOSE            (0x0C)
#define BIOS_SET_IO_FOCUS          (0x11)
#define BIOS_GET_BOOT_VERSION      (0x12)
#define BIOS_GET_RTOS_VERSION      (0x13)
#define BIOS_SET_BATCH_MODE        (0x14)
#define BIOS_BATCH_CONTINUE        (0x15)
#define BIOS_FEATURES              (0x16)
#define BIOS_GET_MAC               (0x17)
#define BIOS_POWER_SAVE            (0x18)
#define BIOS_SERVER_LEVEL          (0x19)
#define BIOS_INSTALL_ERR           (0x20)
#define BIOS_REBOOT                (0x21)
#define BIOS_VERSION_STRING        (0x22)
#define BIOS_SET_CHIP_INI          (0x23)
#define BIOS_GET_CHIP_INI          (0x24)
#define BIOS_FOCUS_HOTKEY          (0x25)
#define BIOS_GET_DEVICE_NAMES      (0x26)
#define BIOS_SERVER_ON_OFF         (0x27)
#define BIOS_FAST_FINDFIRST        (0x28)
#define BIOS_FAST_FINDNEXT         (0x29)
#define BIOS_LFN_FINDFIRST         (0x2A)
#define BIOS_LFN_FINDNEXT          (0x2B)
#define BIOS_LFN_FINDDONE          (0x2C)
#define BIOS_SERVER_STATE          (0x2D)
#define BIOS_INSTALL_INTNOTSUPP    (0x2E)
#define BIOS_FAST_FINDDONE         (0x30)
#define BIOS_ETHERNET_STATE        (0x31)
#define BIOS_MEMORY_GAP            (0x32)
#define BIOS_SELECT_STDIO          (0x33)
#define BIOS_GET_STDIO             (0x34)
#define BIOS_INSTALL_USER_STDIO    (0x35)
#define BIOS_INSTALL_CONN_HANDLER  (0x36)
#define BIOS_FILE_SHARING          (0x37)
#define BIOS_GET_FILENAME          (0x38)
#define BIOS_LFN_FILENAME          (0x3A)
#define BIOS_SET_ETH_MODE          (0x3B)
#define BIOS_SET_SRV_CRED          (0x3C)
#define BIOS_UDP_CALLBACK          (0x40)
#define BIOS_SET_CHIP_INI_EXT      (0x41)
#define BIOS_GET_CHIP_INI_EXT      (0x42)
#define BIOS_WRITE_PERSISTENT_DATA (0x45)
#define BIOS_READ_PERSISTENT_DATA  (0x46)
#define BIOS_GET_PPPSERVER_IP      (0x50)
#define BIOS_GET_PPPCLIENT_IP      (0x55)
#define BIOS_GET_MAC2              (0x58)
#define BIOS_SET_ERROR             (0x59)

// Data structures for exchange of parameters (software interrupt interface)
typedef struct
{
  const char far *fileName;
  const char far *sectionName;
  const char far *itemName;
  char       far *target;          // Output parameter
} BiosIniGetParams;


typedef struct
{
  const char far *fileName;
  const char far *sectionName;
  const char far *itemName;
  const char far *text;
} BiosIniSetParams;


/*************************************************************************/
// Get character from stdio
/*************************************************************************/
#ifdef _bios100_
/*
 @doc DOC_bios100_
 ---------------------------------------------------------------
 Get char from standard input
 ---------------------------------------------------------------
 @clib  BIOS_getch | Get char from standard input, with wait. |
        <cfont>unsigned int BIOS_getch ( void );<efont> |
 @parm  void |  | -- none --
 @rdesc Lower byte:  input character<nl>
        Upper byte:  Source of input - 1: EXT, 2: COM, 4: Telnet, 8: User channel
 @comm  If only the input character is of interest, the return value can be cast
        to a character to suppress the data source indication carried in the
        upper byte.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0x100x00<linkmid>documentation<linktail>
        for more details.
 @Also  bios101.htm |  BIOS_kbhit |
        bios10E.htm |  BIOS_putch |
        bios211.htm |  BIOS_Set_Focus
 @Also  bios225.htm |  BIOS_Set_Focus_Hotkey |
        bios233.htm |  BIOS_Select_Stdio | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned int BIOS_getch (void)
{
    _AH = BIOS_GETCHAR ;
    asm { int BIOS_SWI_1  } ;

    asm mov ah, dl ; // place source of input in AH

    return _AX;
}
#endif

/*************************************************************************/
// Test if character ready at stdin
/*************************************************************************/
#ifdef _bios101_
/*
 @doc DOC_bios101_
 ---------------------------------------------------------------
 Test if char ready at standard input
 ---------------------------------------------------------------
 @clib  BIOS_kbhit | Test if character is ready at standard input(s). |
        <cfont>unsigned int BIOS_kbhit ( void );<efont> |
 @parm  void |  | -- none --
 @rdesc Boolean: '1' if characters is ready, '0' if no character ready.
 @comm  All devices selected as standard input (e.g. EXT, COM and Telnet)
        are polled for data ready.<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0x100x01<linkmid>documentation<linktail>
        for more details.
 @Also  bios100.htm |  BIOS_getch |
        bios10E.htm |  BIOS_putch|
        bios211.htm |  BIOS_Set_Focus
 @Also  bios225.htm |  BIOS_Set_Focus_Hotkey |
        bios233.htm |  BIOS_Select_Stdio |
        bios234.htm |  BIOS_Get_Stdio
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned int BIOS_kbhit (void)
{
    _AH = BIOS_CHAR_READY ;
    asm { int BIOS_SWI_1  } ;
    return _AX ;
}
#endif

/*************************************************************************/
// Output character to standard output.
/*************************************************************************/
#ifdef _bios10E_
/*
 @doc DOC_bios10E_
 ---------------------------------------------------------------
 Output character to standard output.
 ---------------------------------------------------------------
 @clib  BIOS_putch | Output character to standard output(s). |
        <cfont>void BIOS_putch ( unsigned char output );<efont> |
 @parm  unsigned char | output | Character to be output
 @rdesc -- none --
 @comm  This character is output to each device selected for standard output
        (e.g. EXT, COM and Telnet).<nl>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0x100x0E<linkmid>documentation<linktail>
        for more details.
 @Also  bios100.htm |  BIOS_getch |
        bios101.htm |  BIOS_kbhit |
        bios211.htm |  BIOS_Set_Focus
 @Also  bios225.htm |  BIOS_Set_Focus_Hotkey |
        bios233.htm |  BIOS_Select_Stdio |  |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_putch (unsigned char output)
{
    _AL = output ;
    _AH = BIOS_PUTCHAR ;
    asm { int BIOS_SWI_1  } ;
}
#endif

/*************************************************************************/
// Get chip serial number
/*************************************************************************/
#ifdef _bios200_
/*
 @doc DOC_bios200_
 ---------------------------------------------------------------
 Get the serial number of the CPU device
 ---------------------------------------------------------------
 @clib  BIOS_Get_Serial_Number | Get the serial number of the IPC@CHIP&reg; device. |
        <cfont>unsigned long BIOS_Get_Serial_Number ( void );<efont> |
 @parm  void |  | -- none --
 @rdesc IPC@CHIP&reg; serial number
 @comm  The IPC@CHIP&reg; serial number is a 24 bit value.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x00<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00

*/
unsigned long BIOS_Get_Serial_Number (void)
{
    union {

        struct {
            unsigned int  Lower ;
            unsigned int  Upper ;
        } Halfs ;
        unsigned long Whole ;

    }  serial_number ;

    asm push DI
    asm push SI

    _AH = BIOS_GET_SN ;
    asm { int BIOS_SWI_2  } ;

    asm pop SI
    asm pop DI

    serial_number.Halfs.Lower = _AX ;
    serial_number.Halfs.Upper = _BX ;

    return serial_number.Whole ;
}
#endif


/*************************************************************************/
// Get BECK product serial number
/*************************************************************************/
#ifdef _bios200A_
/*
 @doc DOC_bios200A_
 ---------------------------------------------------------------
 Get the serial number of the BECK product
 ---------------------------------------------------------------
 @clib  BIOS_Get_Product_Serial_Number | Get the serial number of the BECK product. |
        <cfont>unsigned long BIOS_Get_Product_Serial_Number ( void );<efont> |
 @parm  void |  | -- none --
 @rdesc BECK product serial number
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x00<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned long BIOS_Get_Product_Serial_Number (void)
{
    union {

        struct {
            unsigned int  Lower ;
            unsigned int  Upper ;
        } Halfs ;
        unsigned long Whole ;

    }  serial_number ;


    asm push DI
    asm push SI

    _AH = BIOS_GET_SN ;
    asm { int BIOS_SWI_2  } ;

    asm pop SI
    asm pop DI


    serial_number.Halfs.Lower = _CX ;
    serial_number.Halfs.Upper = _DX ;

    return serial_number.Whole ;
}
#endif


/*************************************************************************/
// Get IPC@CHIP hardware revision
/*************************************************************************/
#ifdef _bios200B_
/*
 @doc DOC_bios200B_
 ---------------------------------------------------------------
 Get the hardware revision number of the IPC@CHIP device
 ---------------------------------------------------------------
 @clib  BIOS_Get_Hardware_Rev | Get the hardware revision number
        of the IPC@CHIP&reg; device. |
        <cfont>unsigned int BIOS_Get_Hardware_Rev ( void );<efont> |
 @parm  void |  | -- none --
 @rdesc IPC@CHIP&reg; hardware revision number
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x00<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned int BIOS_Get_Hardware_Rev (void)
{
    asm push SI
    
    _AH = BIOS_GET_SN ;
    asm { int BIOS_SWI_2  } ;

    asm pop SI

    return _DI;
}
#endif


/*************************************************************************/
// Get BECK product hardware revision
/*************************************************************************/
#ifdef _bios200C_
/*
 @doc DOC_bios200C_
 ---------------------------------------------------------------
 Get the hardware revision number of the BECK product
 ---------------------------------------------------------------
 @clib  BIOS_Get_Product_Hardware_Rev | Get the hardware revision number
        of the BECK product. |
        <cfont>unsigned int BIOS_Get_Product_Hardware_Rev ( void );<efont> |
 @parm  void |  | -- none --
 @rdesc BECK product hardware revision number
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x00<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned int BIOS_Get_Product_Hardware_Rev (void)
{
    asm push DI

    _AH = BIOS_GET_SN ;
    asm { int BIOS_SWI_2  } ;

    asm pop DI
    
    return _SI;
}
#endif

/*************************************************************************/
// Execute command
/*************************************************************************/
#ifdef _bios207_
/*
 @doc DOC_bios207_
 ---------------------------------------------------------------
 Execute a command shell command
 ---------------------------------------------------------------
 @clib  BIOS_Execute | Execute a command shell command. |
        <cfont>int BIOS_Execute ( const char far *command_line );<efont> |
 @parm  byte | command_line | Pointer to a null terminated command line.
 @rdesc 
     0    -  Successful<nl>
     +1   -  Internal command had a problem<nl>
     -1   -  Attempt to launch a DOS program by this name failed<nl>
 @comm  This function passes the command string to the command interpreter.<nl>
        <nl>
        Internal commands are processed in the current task, external
        commands (.exe files) are loaded and executed in a new task.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x07<linkmid>documentation<linktail>
        for more details.
 @Also  bios20B.htm |  BIOS_ExecuteExt |
         |   |
         |  
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int BIOS_Execute (const char far *command_line)
{
    _ES = FP_SEG (command_line) ;
    _DX = FP_OFF (command_line) ;
    _AH = BIOS_EXECUTE ;
    asm { int BIOS_SWI_2  } ;
    return _AX;
}
#endif

/*************************************************************************/
// Set timer 0x1C speed
/*************************************************************************/
#ifdef _bios208_
/*
 @doc DOC_bios208_
 ---------------------------------------------------------------
 Set timer 0x1C interval
 ---------------------------------------------------------------
 @clib  BIOS_Set_Timer_0x1C | Set timer 0x1C interval. |
        <cfont>void BIOS_Set_Timer_0x1C ( unsigned int interval_ms ); <efont> |
 @parm  unsigned int | interval_ms | Timer interval in milliseconds.
 @rdesc -- none --
 @comm  This function defines the interval in milliseconds that timer
        interrupt 0x1C will use..<nl>
        <nl>
        Use <code>setvect(0x1c,your_routine)<codee> to change the interrupt
        vector.<s2> Define your routine as:<nl>
        <nl>
        <tab8><code>void interrupt my_function(void)<codee><nl>
        <nl>
        You must restore the old timer interrupt vector before ending
        the program.<nl>
        <nl>
        Your interrupt routine must be as short as possible without
        any waiting or endless loops.<s2> Avoid the usage of large CLib
        functions like <code>printf<codee>.<nl>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x08<linkmid>documentation<linktail>
        for more details.
 @Also  bios209.htm |  BIOS_Set_Timer_0xAF | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Set_Timer_0x1C (unsigned int interval_ms)
{
    _BX = interval_ms ;
    _AH = BIOS_SET_TIMER_1C ;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Set timer 0xAF speed
/*************************************************************************/
#ifdef _bios209_
/*
 @doc DOC_bios209_
 ---------------------------------------------------------------
 Set timer 0xAF interval
 ---------------------------------------------------------------
 @clib  BIOS_Set_Timer_0xAF | Set timer 0xAF interval. |
        <cfont>void BIOS_Set_Timer_0xAF ( unsigned int interval_ms );<efont> |
 @parm  int | interval_ms | Timer interval in milliseconds.
 @rdesc -- none --
 @comm  This function defines the interval in milliseconds that timer
        interrupt 0xAF will use..<nl>
        <nl>
        Use <code>setvect(0xAF,your_routine)<codee> to change the interrupt
        vector.<s2> Define your routine as:<nl>
        <nl>
        <tab8><code>void interrupt my_function(void)<codee><nl>
        <nl>
        You must restore the old timer interrupt vector before ending
        the program.<nl>
        <nl>
        Your interrupt routine must be as short as possible without
        any waiting or endless loops.<s2> Avoid the usage of large CLib
        functions like <code>printf<codee>.<nl>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x09<linkmid>documentation<linktail>
        for more details.
 @Also  bios208.htm |  BIOS_Set_Timer_0x1C | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Set_Timer_0xAF (unsigned int interval_ms)
{
    _BX = interval_ms ;
    _AH = BIOS_SET_TIMER_AF ;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Get large disk info
/*************************************************************************/
#ifdef _bios20A_
/*
 @doc DOC_bios20A_
 ---------------------------------------------------------------
 Get large disk info
 ---------------------------------------------------------------
 @clib  BIOS_Disk_Info | Get disk drive information. |
        <cfont>void BIOS_Disk_Info ( unsigned int drive,<nl>
        <tab><tab><tab><tab><tab><s1> BiosDiskInfo * disk_info ); <efont> |
 @parm  unsigned int | drive | Drive index:<nl>
        <ul>
        0 = current drive<nl>
        1 = A: drive<nl>
        2 = B: drive<nl>
        ... and so on.
        <ule><nl>
 @parm  unsigned int | disk_info | Output parameter:<s2> Pointer to
        <linkto>../../biosstruc.htm#BiosDiskInfo<linkmid>BiosDiskInfo<linktail>
        data structure that will be set by this API.
 @rdesc -- none --
 @comm  This function may be used for any drive, but it will be required
        for drives which exceed the DOS interrupt 0x21
        <linkto>../../DOSEMU.htm#0x210x36<linkmid>service 0x36<linktail>
        API's reporting capacity of 0xFFFF clusters maximum.<nl>
        <nl>
        The resulting value for the <code>SectorsPerCluster<codee> member
        of the output data structure will be 0xFFFF if the drive specified
        was not valid.<nl>
        <nl>
      The number of
     bytes disk free space can be calculated as<nl>
     <nl>
       <tab><code>FreeClusters * sectorsPerCluster * bytesPerSector<codee><nl>
    <nl>
      and the drive's total number of bytes as<nl>
     <nl>
       <tab><code>TotalClusters * sectorsPerCluster * bytesPerSector<codee><nl>
    <nl>
    Note that for drives larger than 4 Giga-byte, mulitple precision 
    integer arithmetic will be required for these calculations.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x0A<linkmid>documentation<linktail>
        for more details.
 @Also  bios20Aa.htm |  BIOS_Disk_Space | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.23 | V1.23 | V1.23 | V1.16 | V1.00
 @target_clib V2.11

*/
void BIOS_Disk_Info (unsigned int drive, BiosDiskInfo * disk_info)
{
    _ES = FP_SEG(disk_info) ;
    _BX = FP_OFF(disk_info) ;
    _AL = (unsigned char) drive ;
    _AH = BIOS_DISK_INFO ;

    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Get large disk info
/*************************************************************************/
#ifdef _bios20Aa_
/*
 @doc DOC_bios20Aa_
 ---------------------------------------------------------------
 Get large disk space
 ---------------------------------------------------------------
 @clib  BIOS_Disk_Space | Report number of free bytes on specified
        disk drive. |
        <cfont>unsigned long BIOS_Disk_Space (unsigned int drive ); <efont> |
 @parm  unsigned int | drive | Drive index:<nl>
        <ul>
        0 = current drive<nl>
        1 = A: drive<nl>
        2 = B: drive<nl>
        ... and so on.
        <ule><nl>
 @rdesc Available disk space, number of bytes free.<s2> This value will
       be zero if the drive number specified was invalid.
 @comm  This function applies to drives with under 4 Giga-bytes of disk space.<s2>
        For drives larger than 4 Giga-bytes, the free disk space may exceed
        the capacity of this API's 32 bit return value, resulting in a garbage
        result.<nl>
        <nl>
        This API will be required
        for drives which exceed the DOS interrupt 0x21
        <linkto>../../DOSEMU.htm#0x210x36<linkmid>service 0x36<linktail>
        API's reporting capacity of 0xFFFF clusters maximum.<nl>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x0A<linkmid>documentation<linktail>
        for more details.
 @Also  bios20A.htm |  BIOS_Get_Disk_Info | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.23 | V1.23 | V1.23 | V1.16 | V1.00
 @target_clib V2.11

*/
unsigned long BIOS_Disk_Space (unsigned int drive)
{
    BiosDiskInfo disk_info ;
    _ES = FP_SEG(&disk_info) ;
    _BX = FP_OFF(&disk_info) ;
    _AL = (unsigned char) drive ;
    _AH = BIOS_DISK_INFO ;

    asm { int BIOS_SWI_2  } ;

    // Calculate free bytes:  = [bytes/cluster] * freeClusters
    return (disk_info.bytesPerSector * disk_info.sectorsPerCluster) 
          * disk_info.freeClusters ;
}
#endif


/*************************************************************************/
// Execute command
/*************************************************************************/
#ifdef _bios20B_
/*
 @doc DOC_bios20B_
 ---------------------------------------------------------------
 Execute a command shell command
 ---------------------------------------------------------------
 @clib  BIOS_ExecuteExt | Execute a shell command with feedback. |
        <cfont>int BIOS_ExecuteExt ( const char far *command_line,<nl>
        <tab><tab><tab><tab><tab>&nbsp;&nbsp;void far *report);<efont> |
 @parm  byte | command_line | Pointer to a null terminated command line.
 @parm  byte | report | Output parameter: Object in user memory where
         certain commands provide feedback.
 @rdesc
     0    -  Successful<nl>
     +1   -  Internal command had a problem<nl>
     -1   -  Attempt to launch a DOS program by this name failed<nl>
 @comm  This function passes the command string to the command interpreter
        and specifies with the <cfont>report<efont> argument an object
        where the caller desires feedback be written by the invoked command.<nl>
        <nl>
        Internal commands are processed in the current task, external
        commands (.exe files) are loaded and executed in a new task.<nl>
        <nl>
        Only certain commands will make use of this provided 
        <cfont>report<efont> argument.  The structure of the
        referenced object is specific to each command which 
        provides feedback.  These commands are:<nl>
        <ul><nl>
    <li><linkto>../../command.htm#COPY<linkmid>COPY<linktail> - 
           <cfont>report<efont> data structure 
  <linkto>../../biosstruc.htm#CmdFeedbackS<linkmid>CmdFeedbackS<linktail>
        <nl><nl>
    <li><linkto>../../command.htm#CHKDSK<linkmid>CHKDSK<linktail> - 
           <cfont>report<efont> data structure 
  <linkto>../../DiskStat.htm<linkmid>DiskStatS<linktail>
        <nl><nl>
    <li><linkto>../../command.htm#CV<linkmid>CV<linktail> - 
           <cfont>report<efont> data structure 
  <linkto>../../CvStat.htm<linkmid>CvStatS<linktail>
        <nl><nl>
    <li><linkto>../../command.htm#FORMAT<linkmid>FORMAT<linktail> - 
           <cfont>report<efont> data structure 
  <linkto>../../biosstruc.htm#CmdFeedbackS<linkmid>CmdFeedbackS<linktail>
        <nl><nl>
    <li>external commands (.exe files) -  The invoked program can access
        the object at <cfont>report<efont> using the 
        <linkto>../helper/progParentData.htm<linkmid>progParentData()<linktail>
        function.
        <s2> The format of this object is user defined, however the first two
        integer values must correspond to the the
  <linkto>../../biosstruc.htm#ProgFeedbackS<linkmid>ProgFeedbackS<linktail>
        data structure.
        <s2>For compatibility with future @Chip-RTOS versions, the first
        integer (unsigned) of this user defined structure should be set 
        to the size of this user structure.  The second integer (signed)
        will be set to the program's 
        <linkto>../../dosemu.htm#0x210x4C<linkmid>DOS<linktail>
        exit code value.  The remainder of the structure
        following these two required integer values can be what ever the
        user desires.
        <ule>
        <nl>
         The <cfont>report<efont> argument is ignored by any other commands.<s2>
         However, for compatibility with future @Chip-RTOS versions this should
         not be relied upon.<nl>
         <nl>
        <bold>Caution:<bolde><nl>
        <ul>
        When another program is invoked using this API, the data area 
        referenced by <cfont>report<efont> must persist until that invoked 
        program terminates.  The @Chip-RTOS will write the program's exit
        code to the second 16 bit location within this referenced memory when
        the invoked program terminates.  Note that due to DOS 
        <linkto>../../dosemu.htm#0x210x4C<linkmid>exit API<linktail>
        limitations, this exit code is truncated to 8 bits and then sign extended.
        <ule>
        

 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x0B<linkmid>documentation<linktail>
        for more details.
 @Also  bios207.htm |  BIOS_Execute |
         |   |
         |  
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
 @target_clib V2.18
*/
int BIOS_ExecuteExt (const char far *command_line, void far *report)
{
    _ES = FP_SEG (command_line) ;
    _BX = FP_OFF (command_line) ;
    _DX = FP_SEG (report) ;
    _CX = FP_OFF (report) ;
    _AH = BIOS_EXEC_EXT ;
    asm { int BIOS_SWI_2  } ;
    return _AX;
}
#endif

/*************************************************************************/
// Close disk
/*************************************************************************/
#ifdef _bios20C_
/*
 @doc DOC_bios20C_
 ---------------------------------------------------------------
 Close disk
 ---------------------------------------------------------------
 @clib  BIOS_Disk_Close | Close a drive. |
        <cfont>int BIOS_Disk_Close ( const char *path <nl>
        <tab><tab><tab><tab><tab><s1> unsigned int flags); <efont> |
 @parm  unsigned char * | path | Zero terminated ASCII string containing 
     the drive letter followed by a colon.<s2>
     For example "B:".<nl>
 @parm int | flags | Bit field to request special actions:<nl>
     <ul><nl>
         <li><code>BDC_SAVE_1_FAT<codee> = 0x1 - Save only one copy of
           the File Allocation Table (FAT) in order to save time.<nl>
         <li><code>BDC_ABORT_READ_WRITE<codee> = 0x2 - Cut short
           any read/write activity currently in progress, so that
           drive can be closed with a minimum of delay.<nl>
     <ule><nl>
       These bit flags may be OR'ed together.
 @rdesc status:<nl>
    <ul>
       0  -  Success<nl>
       -1 -  Invalid <i>path<ie> or drive was already closed.<nl>
 @comm  This function is provided for use at time of a power fail warning,
   for systems equipped with an adequate power supply signal for this
   purpose.<s2> This function will save the state of the specified drive,
   assuming sufficient time for these actions is available from the 
   power supply.<nl>
   <nl>
   The <i>flags<ie> bit field can be used to specify certain short cuts 
   to speed up the disk close operation.<s2> These bit flags may be OR'ed
   together.<s2> The undefined bits should be set zero for compatibility
   with future software versions.<nl>
   <nl>
   This API will close all files that were opened on this drive.<s2> However
   this action is not coordinated with your program's standard C-library
   buffered I/O functions, such as fwrite(), fread() and fclose().<s2>
   Any unflushed data written to these files will be lost.<nl>
   <nl>
   Any further references to files that were opened on this drive must be 
   avoided, since your local C-library I/O functions will no longer be in 
   synch with the @CHIP-RTOS-x86 for this drive.<nl>
   <nl>
   A system reset should follow use of this API.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x0C<linkmid>documentation<linktail>
        for more details.
 @Also  ../HW/hal84.htm |  hal_install_isr | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.40 | V1.40
 @target_clib V2.20

*/
int BIOS_Disk_Close (const char *path, unsigned int flags)
{
    _CX = flags ;
    _ES = FP_SEG(path) ;
    _BX = FP_OFF(path) ;
    _AH = BIOS_DISK_CLOSE ;
    asm { int BIOS_SWI_2  } ;
    return _AX ;
}
#endif


/*************************************************************************/
// Set STDIO focus
/*************************************************************************/
#ifdef _bios211_
/*
 @doc DOC_bios211_
 ---------------------------------------------------------------
 Set STDIO focus
 ---------------------------------------------------------------
 @clib  BIOS_Set_Focus | Set STDIO focus. |
        <cfont>void BIOS_Set_Focus ( IO_FOCUS focus );<efont> |
 @parm  int | focus | Enumeration type:<nl>
        <ul>
        FOCUS_SHELL = 1:  Set focus to command shell<nl>
        FOCUS_APPLICATION = 2:  Set focus to application<nl>
        FOCUS_BOTH = 3: Set focus to both application and command shell<nl>
        <ule>
 @rdesc -- none --
 @comm  This function sets the focus of STDIO to either console, application
        or both.<nl>
        <nl>
        If your application requires input from the user, you should set the
        focus to the application.<s2> You should take care that only one
        application requests input from STDIO.<nl>
        <nl>
        The user can change the focus by using the focus hot key (default
        Ctrl-F).<s2> Changing the focus clears the serial input and output
        queues immediately.<nl>
        <nl><bold>Important<bolde>:<nl>
        <ul>
        All buffered incoming and outgoing characters in the internal serial
        send and receive queues are lost after this call.<nl>
        <ule>
        <nl>
        This function includes a one millisecond sleep.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x11<linkmid>documentation<linktail>
        for more details.
 @related | ../../config.htm#STDIO_FOCUSKEY | Focus | key definition
 @Also  bios225.htm |  BIOS_Set_Focus_Hotkey |
        bios100.htm |  BIOS_getch |
        bios10E.htm |  BIOS_putch
 @Also  bios101.htm |  BIOS_kbhit |
        bios233.htm |  BIOS_Select_Stdio |
        bios234.htm |  BIOS_Get_Stdio
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Set_Focus (IO_FOCUS focus)
{
    _AL = (unsigned char) focus ;
    _AH = BIOS_SET_IO_FOCUS ;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Get bootstrap version number
/*************************************************************************/
#ifdef _bios212_
/*
 @doc DOC_bios212_
 ---------------------------------------------------------------
 Get bootstrap version number
 ---------------------------------------------------------------
 @clib  BIOS_Get_Boot_Version | Get bootstrap version number. |
        <cfont>unsigned int BIOS_Get_Boot_Version ( void );<efont> |
 @parm   void |  | -- none --
 @rdesc Bootstrap program version number, in BCD format:<nl>
        MSB is major version, LSB is minor version.
 @comm  Example:<nl><ul>
        If the function returns 0x020C, this means that you have version 2.12.
        <ule>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x12<linkmid>documentation<linktail>
        for more details.
 @Also  bios213.htm |  BIOS_Get_RTOS_Version | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned int BIOS_Get_Boot_Version (void)
{
    _AH = BIOS_GET_BOOT_VERSION ;
    asm { int BIOS_SWI_2  } ;
    return _AX ;
}
#endif

/*************************************************************************/
// Get RTOS version number
/*************************************************************************/
#ifdef _bios213_
/*
 @doc DOC_bios213_
 ---------------------------------------------------------------
 Get RTOS version number
 ---------------------------------------------------------------
 @clib  BIOS_Get_RTOS_Version | Get RTOS version number. |
        <cfont>unsigned int BIOS_Get_RTOS_Version( unsigned int *beta_flag );<efont> |
 @parm  int | beta_flag | Optional output parameter:<s2>
        If non-null, this location will be set as a Boolean to
        indicate if the RTOS is a beta version.<s2>A zero indicates
        that it is not a beta version, non-zero indicates a
        beta version.
 @rdesc RTOS program version number, in split binary format:<nl>
        MSB is binary major version, LSB is binary minor version.
 @comm  Example:<nl><ul>
        If the function returns 0x0100, this means that you have RTOS
        version 1.00.
        <ule>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x13<linkmid>documentation<linktail>
        for more details.
 @Also  bios212.htm |  BIOS_Get_Boot_Version |
        bios222.htm |  BIOS_Version_String | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned int BIOS_Get_RTOS_Version (unsigned int *beta_flag)
{
    unsigned int prog_num ;
    _DX = 0 ;               // In case API does not support beta flag
    _AH = BIOS_GET_RTOS_VERSION ;
    asm { int BIOS_SWI_2  } ;
    prog_num = _AX ;
    if (beta_flag != 0)         // Caller wants to see the flag?
    {
        *beta_flag = _DX ;
    }
    return prog_num ;
}
#endif

/*************************************************************************/
// Set Batch file mode
/*************************************************************************/
#ifdef _bios214_
/*
 @doc DOC_bios214_
 ---------------------------------------------------------------
 Set batch file mode
 ---------------------------------------------------------------
 @clib  BIOS_Set_Batch_Mode | Set <linkto>../../autoexec.htm#batchfile<linkmid>batch file<linktail> mode. |
        <cfont>void  BIOS_Set_Batch_Mode ( BATCH_MODE mode,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; unsigned int enable_timeout );<efont> |
 @parm  int | mode |
        BATCH_CONCURRENT= 0: <s2> Sets <code>BATCHMODE<codee>=0 = concurrent<nl>
        BATCH_SEQUENTIAL= 1: <s2> Sets <code>BATCHMODE<codee>=1 = sequential<nl>
 @parm  int | enable_timeout | Boolean:<nl>
        0: <s2> Disable the maximum delayed execution time-out of DOS programs<nl>
        1: <s2> Enable the maximum delayed execution time-out of DOS programs in a batchfile,
        if <code>BATCHMODE<codee> = 1 (sequential)<nl>
 @rdesc -- none --
 @comm  This function sets the batch file execution mode of DOS programs
        for either concurrent or sequential execution.<s2> See
        <code>BATCHMODE<codee> initialization
        <linkto>../../config.htm#BATCH_BATCHMODE<linkmid>documentation<linktail>
        for details.<nl>
        <nl>
        The <code>enable_timeout<codee> parameter only applies to
        <code>BATCH_SEQUENTIAL<codee> mode.
        <nl>
        <bold>Important:<bolde><nl>
        <ul>
        If<s1> <code>BATCHMODE=1<codee> take care that every program in your batch
        file which has a successor program either exits
        <linkto>../../dosemu.htm#0x210x4C<linkmid>(int21h 0x4C)<linktail>
        or terminates resident with
        <linkto>../../dosemu.htm#0x210x31<linkmid>int21h 0x31<linktail>.<s2>
        A program which runs forever should call
        <linkto>bios215.htm<linkmid>BIOS_Batch_Continue<linktail> API function,
        which immediately enables further batch file sequencing.<nl>
        <nl>
        By default the maximum delay time for execution of the next listed
        program in the batch file is 15 seconds.<s2>
        If <code>enable_timeout<codee> parameter is set to 0, the successor program
        in a batch file waits forever for execution, if the predecessor program does
        not finish or call <linkto>bios215.htm<linkmid>BIOS_Batch_Continue<linktail>.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x14<linkmid>documentation<linktail>
        for more details.
 @Also  bios215.htm |  BIOS_Batch_Continue | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Set_Batch_Mode (BATCH_MODE mode, unsigned int enable_timeout)
{
    _BX = enable_timeout ;
    _AL = (unsigned char) mode ;
    _AH = BIOS_SET_BATCH_MODE ;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Continue Batch file execution
/*************************************************************************/
#ifdef _bios215_
/*
 @doc DOC_bios215_
 ---------------------------------------------------------------
 Continue Batch file execution
 ---------------------------------------------------------------
 @clib  BIOS_Batch_Continue | Continue <linkto>../../autoexec.htm#batchfile<linkmid>batch file<linktail> execution. |
        <cfont>void BIOS_Batch_Continue ( void );<efont> |
 @parm  int |  |  -- none --
 @rdesc -- none --
 @comm  This call allows the  next program listed in a batch file to start execution.<s2>
        This is necessary when the
        <linkto>../../config.htm#BATCH_BATCHMODE<linkmid>BATCHMODE<linktail> is set to
        '1' for sequential execution of programs.<nl>
        <nl>
        This function is implemented by waking up a batch file execution task which
        dispatches any subsequent program listed in the batch file.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x15<linkmid>documentation<linktail>
        for more details.
 @Also  bios214.htm |  BIOS_Set_Batch_Mode | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Batch_Continue (void)
{
    _AH = BIOS_BATCH_CONTINUE ;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Get Features
/*************************************************************************/
#ifdef _bios216_
/*
 @doc DOC_bios216_
 ---------------------------------------------------------------
 Get RTOS features
 ---------------------------------------------------------------
 @clib  BIOS_Get_Features | Report RTOS features. |
        <cfont>unsigned long BIOS_Get_Features ( void );<efont> |
 @parm  int |  |  -- none --
 @rdesc Bit field indicating features in this RTOS version with following
        bit assignments:<nl>
        <nl>
        Bit 0:<s2> BGF_ETHERNET   - Ethernet device for TCPIP<nl>
        Bit 1:<s2> BGF_PPP_SERVER - PPP server<nl>
        Bit 2:<s2> BGF_PPP_CLIENT - PPP client<nl>
        Bit 3:<s2> BGF_WEB_SERVER - Web server<nl>
        Bit 4:<s2> BGF_TELNET_SERVER - Telnet server<nl>
        Bit 5:<s2> BGF_FTP_SERVER - FTP server<nl>
        Bit 6:<s2> BGF_TFTP_SERVER - TFTP server<nl>
        Bit 7:<s2> BGF_DHCP_CLIENT - DHCP client<nl>
        Bit 8:<s2> BGF_IPV6 - IPv6 support<nl>
        Bit 9:<s2> BGF_SSLWEB_SERVER - SSL Web server<nl>
        ....<nl>
        Bit 16:<s2> BGF_I2C_BUS - I2C-Bus API<nl>
        Bit 17:<s2> BGF_HW_API - Hardware API<nl>
        Bit 18:<s2> BGF_RTOS_API - RTOS API<nl>
        Bit 19:<s2> BGF_PACKET - Packet driver interface for ethernet<nl>
        Bit 20:<s2> BGF_XMODEM - Serial XMODEM filetransfer<nl>
        Bit 21:<s2> BGF_EXT_DISK - External disk interface<nl>
        Bit 22:<s2> BGF_SOFT_SPI - Software SPI API<nl>
        ....<nl>
        Bit 24:<s2> BGF_SNMP_MIB - SNMP MIB variables support (see
        <linkto>../TCPIP/tcp60.htm<linkmid>Get_SNMP_Data<linktail>)<nl>
        Bit 25:<s2> BGF_UDP_CONFIG - UDP config server<nl>
        Bit 26:<s2> BGF_PING_CLIENT - Ping client (see
        <linkto>../TCPIP/tcp75.htm<linkmid>Ping_Open<linktail>)<nl>
        Bit 27:<s2> BGF_DEVICE_DRIVER - TCP/IP device driver<nl>
        Bit 28:<s2> BGF_WEB_PUT - Webfile upload (Webserver PUT method)<nl>
        <nl>
        The mask names stated here (e.g. BGF_PPP_SERVER) are defined in
        BIOS_API.H include file.
 @comm  The bit field returned is coded as so:<nl>
        <nl>
        <ul>
        Bit=0: service or device is not available.<nl>
        Bit=1: service or device is available.<nl>
        <ule>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x16<linkmid>documentation<linktail>
        for more details.
 @Also  bios213.htm |  BIOS_Get_RTOS_Version | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned long BIOS_Get_Features (void)
{
    union {

        struct {
            unsigned int  AX ;
            unsigned char DL ;
            unsigned char BL ;
        } Parts ;
        unsigned long Whole ;

    }  bitmap ;

    _AH = BIOS_FEATURES ;
    asm { int BIOS_SWI_2  } ;

    bitmap.Parts.AX = _AX ;
    bitmap.Parts.DL = _DL ;
    bitmap.Parts.BL = _BL ;

    return bitmap.Whole ;
}
#endif


/*************************************************************************/
// Get Mac address
/*************************************************************************/
#ifdef _bios217_
/*
 @doc DOC_bios217_
 ---------------------------------------------------------------
 Get Mac address
 ---------------------------------------------------------------
 @clib  BIOS_Get_MAC | Get MAC address of the Ethernet interface. |
        <cfont>void  BIOS_Get_MAC ( unsigned char far *mac );<efont> |
 @parm  int | mac |  Output parameter:<s2>Pointer to a 6 byte memory
        area where the MAC address will be stored
 @rdesc -- none --
 @comm  This function outputs the Ethernet MAC address as a six byte
        array.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x17<linkmid>documentation<linktail>
        for more details.
 @Also  ../tcpip/tcpIPR.htm | Get_IPConfig |
          bios258.htm | BIOS_Get_MAC2 |
           |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Get_MAC (unsigned char far *mac)
{
    _ES = FP_SEG(mac) ;
    _DX = FP_OFF(mac) ;

    _AH = BIOS_GET_MAC ;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Power save
/*************************************************************************/
#ifdef _bios218_
/*
 @doc DOC_bios218_
 ---------------------------------------------------------------
 Power save
 ---------------------------------------------------------------
 @clib  BIOS_Power_Save | Power save. |
        <cfont>void BIOS_Power_Save ( void );<efont> |
 @parm  int |  |  -- none --
 @rdesc -- none --
 @comm  This function slows down the internal timer for
        the RTOS and puts the CPU in a halt mode until the next
        interrupt occurs.<s2>
        Call this function when your program is in idle state.<nl>
        <nl>
        Power savings are marginal since DRAM is used by the CPU.<nl>
        <nl>
        Note:
        <ul>
        This function will affect the internal date/time.<nl>
        Power consumption may differ slightly when
        the date code of the IPC@CHIP&reg; is changed.<nl>
        <ule>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x18<linkmid>documentation<linktail>
        for more details.
 @Also  bios218a.htm | BIOS_Power_SaveEx | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Power_Save (void)
{
    _AH = BIOS_POWER_SAVE ;
    _DX = 0;
    asm { int BIOS_SWI_2  } ;
}
#endif


/*************************************************************************/
// Power save Exdended
/*************************************************************************/
#ifdef _bios218A_
/*
 @doc DOC_bios218A_
 ---------------------------------------------------------------
 Power save
 ---------------------------------------------------------------
 @clib  BIOS_Power_SaveEx | Power save. |
        <cfont>int BIOS_Power_SaveEx ( unsigned char mode );<efont> |
 @parm1 SC11/SC13  | mode |
        0x01: Restore full speed mode<nl>
        0x02: Set 1/2 speed mode<nl>
        0x04: Set 1/4 speed mode (serial baudrates <gt> 57600 will no longer be accurate)<nl>
        0x80: Enter sleep mode (RTOS 1ms timer and time/date will be affected)<nl>
        0x81: Wakeup from sleep mode<nl>
        0x20: Power down Ethernet controller (no Ethernet communication is possible)<nl>
        0x21: Power up Ethernet controller<nl>
 @parm2 SC1x3/SC2x  | mode |
        0x01: Restore full speed mode<nl>
        0x02: Set 1/2 speed mode<nl>
        0x04: Set 1/4 speed mode<nl>
        0x20: Power down Ethernet controller (no Ethernet communication is possible)<nl>
        0x21: Power up Ethernet controller<nl>
        0x22: Disable the Ethernet Energy Detect Power-Down mode<nl>
        0x23: Enable the Ethernet Energy Detect Power-Down mode<nl>
 @rdesc 0 if successful
 @comm  This function slows down the processor clock and puts the CPU
        in a powersave mode until the original mode is restored.<nl>
        <nl>
        Note:
        Power consumption may differ slightly when
        the date code of the IPC@CHIP&reg; is changed.<nl>
 @commtarget SC12 | For SC12 the <cfont>mode<efont> parameter has no affect.<s2>
        The <linkto>bios218.htm<linkmid>BIOS_Power_Save<linktail> API
        is recommended for SC12.
 @commtarget SC1x3/SC2x | In mode 0x23 the Ethernet PHY is partially powered down.<s2>
        The PHY powers-up when there is valid energy from the line:
        100Base-TX, 10 Base-T or auto negotiation.<nl>
        If the user calls this function with mode = 4 (Set 1/4 speed mode),
        the internal ethernet controller doesn't work in the 100 MBit mode.
        Because of this behaviour, it is recommended to set the
        <linkto>../../config.htm#IP_ETH_MODE<linkmid>ethernet mode<linktail>
        at chip.ini fix to 10MBit Halfduplex.<nl>
        <nl>
        The modes 0x02 and 0x04 influence the USB API. In mode 0x02 the
        USB API cannot be used at all. The SC1x3/SC2x will crash if you do.
        In mode 0x04 the USB API can only be used in Device mode, because
        Host mode needs better performance.<nl>


 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x18<linkmid>documentation<linktail>
        for more details.
 @Also  bios218.htm | BIOS_Power_Save | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | V1.00 | V1.00 | V0.90 | V1.00
*/
int BIOS_Power_SaveEx (unsigned char mode)
{
    _AH = BIOS_POWER_SAVE ;
    _DX = 0xABCD;
    _CX = 0x1234;
    _AL = mode;
    asm { int BIOS_SWI_2  } ;
    return _AX;
}
#endif

/*************************************************************************/
// Change level for configuration server
/*************************************************************************/
#ifdef _bios219_
/*
 @doc DOC_bios219_
 ---------------------------------------------------------------
 Change level for configuration server
 ---------------------------------------------------------------
 @clib  BIOS_Config_Server_Level | Change level for configuration server. |
        <cfont>void BIOS_Config_Server_Level ( unsigned int level );<efont> |
 @parm  int | level  |  The supported level
 @rdesc -- none --
 @comm  This function changes the supported level for the configuration server.<s2>
        For a description of the possible levels, refer to
        <linkto>../../config.htm#UDPCFG_LEVEL<linkmid>UDPCFG<linktail> level
        topic.<nl>
        <nl>
        Note that if the level defined in the
        <cfont>CHIP.INI<efont> is 0 (zero),
        the configuration server task is not started and changing the
        supported level has no effect.<s2> To avoid this, use an unlisted
        support level such as 0x1000 in the <cfont>CHIP.INI<efont>.<nl>
        <nl>
        The entry in the <cfont>CHIP.INI<efont> file is not changed by
        this call.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x19<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Config_Server_Level (unsigned int level)
{
    _BX = level ;
    _AH = BIOS_SERVER_LEVEL ;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Install a user fatal error handler
/*************************************************************************/
#ifdef _bios220_
/*
 @doc DOC_bios220_
 ---------------------------------------------------------------
 Install a user fatal error handler
 ---------------------------------------------------------------
 @clib  BIOS_Install_Error_Handler | Install a user fatal error handler. |
        <cfont>USER_ERROR_HANDLER BIOS_Install_Error_Handler (
        <tab><tab><tab><tab><tab>USER_ERROR_HANDLER vector );<efont> |
 @parm  int | vector  |  Far pointer to callback procedure.<s2>Set to zero
        to un-install the handler.
 @rdesc Old handler (since SC1x RTOS V1.25 and SC1x3/SC2x RTOS V1.20)
 @comm  The user can install an error handler function, that will execute if a
        fatal error occurs in an application or inside of the @CHIP-RTOS.<s2>
        Only one error handler callback is supported by the system.<s2>
        Calling this API with a NULL <cfont>vector<efont> will remove
        any previously installed handler.<s2> Before a program exits, it
        must remove any installed callback.<nl>
        <nl>
        A second call with a non-zero <cfont>vector<efont> will replace
        any previous callback vector.<nl>
        <nl>
        The callback function must have the following form:<nl>
        <nl>
        <tab><code>void huge _pascal Err_Handler (int error_code)<codee><nl>
        
        The <cfont>error_code<efont> input parameter can have the
        following values:<nl>
        <ul>
        1: Invalid opcode (usually caused by corrupted memory).
           The current task will be suspended.<nl>
        2: Fatal kernel error (usually caused by corrupted memory
           or a task stack overflow)<nl>
        3: Fatal internal TCPIP error, calling task is supended<nl>
        4: TCPIP stack reaches memory limit<nl>
        5: TCPIP memory allocation error<nl>
        6: Ethernet bus error (hardware defect)<nl>
        7: Ethernet link error(SC13 only, cable not connected?)<nl>
        8: Flash write error -<gt> Flash defect (IPC@CHIP&reg; is no longer usable)<nl>
        9: Low Memory error -<gt> called if an alloc (system or user) failed<nl>
        10: RTOS memory list corrupted<nl>
        11: Flash weak (SC1x3/SC2x only)<nl>
        12: Internal software error inside @CHIP-RTOS (SC1x3/SC2x only)<nl>
        13: The process that has registered to the watchdog manager under the given handle has failed to refresh the watchdog manager in time.<nl>
        14: End process error -<gt> called if terminate program API does not find the task id<nl>
        <ule>
        <nl>
        Error codes in the range[1000..9999] are reserved for Beck drivers
        or libraries. Currently the following codes are used:<nl>
        <nl>
        <ul>
        1000: GCLIB - The communication between the IPC@CHIP® and the
              graphics controller failed.
        <ule>
              <nl>
        Error codes starting from 10000 can be used by user applications
        with the <linkto>bios259.htm<linkmid>BIOS_Set_Error<linktail> API.<nl>
        <ule>

        In all cases (except error code 7 and 9, driver/library and application
        codes depend) we recommend to reboot the IPC@CHIP&reg; (see below).
        If the flash device has a defect, the IPC@CHIP&reg; is no longer usable
        <nl>
        
        <bold>Important:<bolde><nl>
        Do not use any message printing inside your error handler
        if <cfont>errorcode<efont> is 3 or 4 and telnet is part of your 
        <linkto>../../config.htm#STDIO_STDIN<linkmid>STDIO<linktail>.<s2>
        In this case
        your exit handler would hang inside of the print call.<nl>
  @COMMTARGET SC1x3/SC2x |
        If a flash error (code 8) or flash weak (code 11) condition has been
        recorded, an immediate callback made from within this API
        will be made to the user.<s2> Note that flash problem records are
        held in non-volatile memory and therefore the error may be residual
       from a previous power up session.<s2> Due to their importance, these
       error records are held until the user explicitly resets the error
       history with the console 
       <linkto>../../command.htm#ERRORS<linkmid>ERRORS RESET<linktail>
        command.<nl>
        <nl>
        Refer to the <linkto>../../command.htm#ERRORS<linkmid>ERRORS<linktail>
        command documentation for an explanation of what is meant 
        by "flash weak".<nl>

 @rtos  This library function invokes a RTOS 
        <linkto>../../biosints.htm#0xA00x20<linkmid>software interrupt<linktail>.
 @also  bios221.htm |  BIOS_Reboot | | | |
 @also  bios259.htm | BIOS_Set_Error | | | |
 @also  ../../command.htm#ERRORS | ERRORS | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.25 | V1.25 | V1.25 | V1.20 | V1.20
*/
USER_ERROR_HANDLER BIOS_Install_Error_Handler (USER_ERROR_HANDLER vector)
{
    _ES = FP_SEG(vector) ;
    _DI = FP_OFF(vector) ;
    _AH = BIOS_INSTALL_ERR ;
    asm { int BIOS_SWI_2  } ;

    return MK_FP(_ES, _DI);
}
#endif

/*************************************************************************/
// Reboot the CPU.
/*************************************************************************/
#ifdef _bios221_
/*
 @doc DOC_bios221_
 ---------------------------------------------------------------
 Reboot the CPU.
 ---------------------------------------------------------------
 @clib  BIOS_Reboot | Reboot the CPU. |
        <cfont>void BIOS_Reboot ( void );<efont> |
 @parm  int |  |  -- none --
 @rdesc No return from this function
 @comm  This function works the same as the shell reboot command.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x21<linkmid>documentation<linktail>
        for more details.
 @Also  bios220.htm |  BIOS_Install_Error_Handler | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Reboot (void)
{
    _AH = BIOS_REBOOT ;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Get RTOS version string
/*************************************************************************/
#ifdef _bios222_
/*
 @doc DOC_bios222_
 ---------------------------------------------------------------
 Get RTOS version string
 ---------------------------------------------------------------
 @clib  BIOS_Version_String | Get RTOS version string. |
        <cfont>void BIOS_Version_String ( char far *version, int max_len );<efont> |
 @parm  int | version  | Output parameter:<s2>
        Up to <code>max_len<codee> characters of the RTOS's
        version string will be output here.<nl>
 @parm  int | max_len  | Maximum length of <code>version<codee> string to copy 
        (including the binary zero character for terminating the string).
 @rdesc -- none --
 @comm  <bold>Caution:<bolde><nl>
        <ul>
        The string at <code>version<codee> must be one greater
        than <code>max_len<codee> to accommodate the string
        terminating nil character which is output after
        the <code>version<codee> string.
        <ule>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x22<linkmid>documentation<linktail>
        for more details.
 @Also  bios213.htm |  BIOS_Get_RTOS_Version | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Version_String (char far *version, int max_len)
{
    _CX = max_len ;
    _ES = FP_SEG(version) ;
    _DI = FP_OFF(version) ;
    _AH = BIOS_VERSION_STRING ;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Insert an entry into CHIP.INI
/*************************************************************************/
#ifdef _bios223_
/*
 @doc DOC_bios223_
 ---------------------------------------------------------------
 Insert an entry into CHIP.INI
 ---------------------------------------------------------------
 @clib  BIOS_Set_Ini_String | Insert an entry into CHIP.INI. |
        <cfont>int BIOS_Set_Ini_String ( const char far *section,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; const char far *item_name,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; const char far *item_text );<efont> |
 @parm  int | section  | Pointer to section string (max. 40 chars)
 @parm  int | item_name  | Pointer to item name (max. 40 chars)
 @parm  int | item_text  | Pointer to item text (max. 128 chars)<nl>
                           Pass a NULL pointer here to erase the complete item line
 @rdesc 0:<s2>success<nl>
       -1:<s2>Invalid string length, low heap memory or file error.
 @comm Leading and trailing white space characters will be cut. The function stops
       reading the entry when it finds an invalid character (<lt>0x20).<nl>
       <nl>
       This API is thread safe and reentrant.<s2> This function will
       fail (no operation) if insufficient system heap memory is
       available to momentarily hold the contents of the CHIP.INI file.<nl>
       <nl>
       No write to the CHIP.INI occurs if the specified
       entry already exists with the specified value.<nl>
        <nl>
        Example usage:<nl>
        @raw
        BIOS_Set_Ini_String ("MY_SECTION", "MY_ITEM", "VALUE_TEXT") ;

        ... produces the following CHIP.INI entry

        [MY_SECTION]
        MY_ITEM=VALUE_TEXT

 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x23<linkmid>documentation<linktail>
        for more details.
 @Also  bios224.htm |  BIOS_Get_Ini_String | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
*/
int BIOS_Set_Ini_String (const char far *section,
                         const char far *item_name,
                         const char far *item_text)
{
    asm { push DS } ;
    _BX = FP_SEG(section) ;
    _SI = FP_OFF(section) ;
    asm { LES DI,item_name } ;
    asm { LDS DX,item_text } ;
    _AH = BIOS_SET_CHIP_INI ;
    asm { int BIOS_SWI_2  } ;
    asm {pop DS } ;
    return _AX ;
}
#endif

/*************************************************************************/
// Get an entry from CHIP.INI
/*************************************************************************/
#ifdef _bios224_
/*
 @doc DOC_bios224_
 ---------------------------------------------------------------
 Get an entry from CHIP.INI
 ---------------------------------------------------------------
 @clib  BIOS_Get_Ini_String | Get an entry from CHIP.INI. |
        <cfont>int BIOS_Get_Ini_String ( const char far *section,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; const char far *item_name,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; char far *item_text,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; unsigned int max_len );<efont> |
 @parm  int | section  | Pointer to section string (max. 40 chars)
 @parm  int | item_name  | Pointer to item name (max. 40 chars)
 @parm  int | item_text  | Output parameter:<s2>Pointer to where
        up to <code>max_len<codee> characters of item text will be written,
        plus a terminating nil character.
 @parm  int | max_len  | Maximum characters to output to
        <code>item_text<codee>, not including terminating nil character.<nl>
        <nl>
        <bold>Caution:<bolde><s2>
        Buffer at <code>item_text<codee> must be <code>max_len<codee> + 1
        size.
 @rdesc 0:<s2>Entry not found<nl>
        <gt>0 :<s2>Length of the string found<nl>
        -1 :<s2>CHIP.INI file not found<nl>
 @comm  This API is thread safe and reentrant.<s2> This function will
        fail (returns -1) if insufficient system heap memory is
        available to momentarily hold the contents of the CHIP.INI
        file.<nl>
        <nl>
        Example usage:<nl>
        @raw
        // Declare an output buffer to receive the item's text
        unsigned char item_text[100] ;

        unsigned int text_length =
        BIOS_Get_Ini_String("MY_SECTION", "MY_ITEM",item_text, sizeof(item_text)-1);

 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x24<linkmid>documentation<linktail>
        for more details.
 @Also  bios223.htm |  BIOS_Set_Ini_String | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int BIOS_Get_Ini_String (const char far *section,
                         const char far *item_name,
                         char far *item_text,
                         unsigned int max_len)
{
    asm { push DS } ;
    _CX = max_len ;
    _BX = FP_SEG(section) ;
    _SI = FP_OFF(section) ;
    asm { LES DI,item_name } ;
    asm { LDS DX,item_text } ;
    _AH = BIOS_GET_CHIP_INI ;
    asm { int BIOS_SWI_2  } ;
    asm {pop DS } ;
    return _AX ;
}
#endif

/*************************************************************************/
// Set the Stdio Focuskey
/*************************************************************************/
#ifdef _bios225_
/*
 @doc DOC_bios225_
 ---------------------------------------------------------------
 Set the Stdio Focus key
 ---------------------------------------------------------------
 @clib  BIOS_Set_Focus_Hotkey | Set the stdio focus key. |
        <cfont>void BIOS_Set_Focus_Hotkey ( unsigned char hotkey );<efont> |
 @parm  int | hotkey  | New focus key code
        in range:<s2> [ 0 .. 254 ]<nl>
 @rdesc -- none --
 @comm  The default hot key is CTRL-F, ASCII 6.<nl>
        <nl>If the focus key is set to zero, the switching of stdio
        from the console is disabled.<nl>
        <nl>At runtime, the hot key (e.g. Ctrl-F) toggles the stdio between
        three modes:<nl><nl>
        <ul>
        Stdio: Shell<s2>  -<s2> Focus set to command shell<nl>
        Stdio: User<s2> -<s2> Focus set to applications<nl>
        Stdio: Both<s2> -<s2> Command shell and applications<nl>
        <ule>
        <nl>
        The focus key is not usable by the command shell or DOS executable.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x25<linkmid>documentation<linktail>
        for more details.
 @related | ../../config.htm#STDIO_FOCUSKEY | Focus | key definition
          in CHIP.INI.
 @Also  bios211.htm |  BIOS_Set_Focus |
        bios100.htm |  BIOS_getch |
        bios10E.htm |  BIOS_putch
 @Also  bios101.htm |  BIOS_kbhit |
        bios233.htm |  BIOS_Select_Stdio |  |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.01 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Set_Focus_Hotkey (unsigned char hotkey)
{
    _AL = hotkey ;
    _AH = BIOS_FOCUS_HOTKEY ;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Get the IPC@CHIP device names
/*************************************************************************/
#ifdef _bios226_
/*
 @doc DOC_bios226_
 ---------------------------------------------------------------
 Get the IPC@CHIP device names
 ---------------------------------------------------------------
 @clib  BIOS_Get_Device_Names | Get the IPC@CHIP&reg; device names. |
        <cfont>void BIOS_Get_Device_Names ( char far **fixed_name,<nl>
        <tab><tab><tab><tab><tab><tab><tab> char far **configured_name );<efont> |
 @parm  int | fixed_name  | Output parameter:<s2> Pointer to a
        string pointer which will receive a pointer to the
        fixed device name stored in the IPC@CHIP&reg; flash.
 @parm  int | configured_name  | Output parameter:<s2> Pointer to a
        string pointer which will receive a pointer to the device
        name configured in CHIP.INI.
 @rdesc -- none --
 @comm  You cannot write to the string at <code>fixed_name<codee>, because
        it is located in flash memory.<nl>
        <nl>
        The string at <code>configured_name<codee> is up to 20 characters
        long.<nl><nl>
        Both returned strings are zero terminated.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x26<linkmid>documentation<linktail>
        for more details.
 @related  | ../../config.htm#DEVICENAME | Device name | definition
        in CHIP.INI file
 @Also  bios226A.htm |  BIOS_Get_Device_NamesEx | | | |  
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Get_Device_Names (char far **fixed_name,
                            char far **configured_name)
{
    WORD bx, es ;
    _AH = BIOS_GET_DEVICE_NAMES ;
    asm { int BIOS_SWI_2  } ;
    bx = _BX ;              // Compiler needs this one.
    es = _ES;               // Compiler needs this one.
    *configured_name = MK_FP(bx, _SI) ;
    *fixed_name = MK_FP(es, _DI) ;
}
#endif


/*************************************************************************/
// Get the IPC@CHIP device names (Extended)
/*************************************************************************/
#ifdef _bios226A_
/*
 @doc DOC_bios226A_
 ---------------------------------------------------------------
 Get the IPC@CHIP device names (Extended)
 ---------------------------------------------------------------
 @clib  BIOS_Get_Device_NamesEx | Get the IPC@CHIP&reg; device names. (Extended) |
        <cfont>void BIOS_Get_Device_NamesEx ( char far **fixed_name,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; char far **configured_name,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; char far **beckproduct_name );<efont> |
 @parm  int | fixed_name  | Output parameter:<s2> Pointer to a
        string pointer which will receive a pointer to the
        fixed device name stored in the IPC@CHIP&reg; flash.
 @parm  int | configured_name  | Output parameter:<s2> Pointer to a
        string pointer which will receive a pointer to the device
        name configured in CHIP.INI.
 @parm  int | beckproduct_name  | Output parameter:<s2> Pointer to a
        string pointer which will receive a pointer to the
        fixed BECK product device name stored in the IPC@CHIP&reg; flash.
 @rdesc -- none --
 @comm  You cannot write to the string at <code>fixed_name<codee>, because
        it is located in flash memory.<nl>
        <nl>
        The string at <code>configured_name<codee> is up to 20 characters
        long.<nl><nl>
        All returned strings are zero terminated.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x26<linkmid>documentation<linktail>
        for more details.
 @Also  bios226.htm |  BIOS_Get_Device_Names | | | |  
 @related  | ../../config.htm#DEVICENAME | Device name | definition
        in CHIP.INI file
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Get_Device_NamesEx (char far **fixed_name,
                              char far **configured_name,
                              char far **beckproduct_name)
{
    WORD bx,es ;
    _AH = BIOS_GET_DEVICE_NAMES ;
    asm { int BIOS_SWI_2  } ;
    bx = _BX ;              // Compiler needs this one.
    es = _ES;               // Compiler needs this one.
    *configured_name = MK_FP(bx, _SI) ;
    *fixed_name = MK_FP(es, _DI) ;
    *beckproduct_name = MK_FP(_DX, _CX) ;
}
#endif

/*************************************************************************/
// Suspend/Resume System Servers
/*************************************************************************/
#ifdef _bios227_
/*
 @doc DOC_bios227_
 ---------------------------------------------------------------
 Suspend/Resume System Servers
 ---------------------------------------------------------------
 @clib  BIOS_Server_On_Off | Suspend/Resume system servers. |
        <cfont>int BIOS_Server_On_Off ( SERVER_SPEC which_server,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; unsigned int activate );<efont> |
 @parm   int | which_server  | Enumerator:<nl>
      <ul>
        SS_FTP_SERVER = 0, SS_TELNET_SERVER = 1, SS_WEB_SERVER = 2, SS_SSL_WEB_SERVER = 3,
        SS_SSH_SERVER = 4
      <ule>
 @parm int | activate  | Boolean:<s2> 0:<s2> Resume,<s2> 1:<s2> Suspend.
 @rdesc 0:<s2>Success<nl>
        1:<s2>Server was already in the postulated state<nl>
        -1: Invalid parameters
 @comm This function may be used to enable a server that was
       disabled at startup due to a CHIP.INI entry.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x27<linkmid>documentation<linktail>
        for more details.
 @related  | ../../config.htm#FTP_ENABLE | FTP_ENABLE | definition
       in CHIP.INI file
 @related  | ../../config.htm#TELNET_ENABLE | TELNET_ENABLE | definition
       in CHIP.INI file
 @related  | ../../config.htm#WEB_ENABLE | WEB_ENABLE | definition
       in CHIP.INI file
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00
*/
int BIOS_Server_On_Off (SERVER_SPEC which_server, unsigned int activate)
{
    _BX = which_server ;
    _AL = (unsigned char) activate ;
    _AH = BIOS_SERVER_ON_OFF ;
    asm { int BIOS_SWI_2  } ;

    return _AX;
}
#endif

/*************************************************************************/
// Get state of system servers
/*************************************************************************/
#ifdef _bios22D_
/*
 @doc DOC_bios22D_
 ---------------------------------------------------------------
 Get state of system servers
 ---------------------------------------------------------------
 @clib  BIOS_Server_State | Get state of system servers. |
        <cfont>int BIOS_Server_State ( SERVER_SPEC which_server);<efont> |
 @parm   int | which_server  | Enumerator:<nl>
      <ul>
        SS_FTP_SERVER = 0, SS_TELNET_SERVER = 1, SS_WEB_SERVER = 2, SS_SSL_WEB_SERVER = 3,
        SS_SSH_SERVER = 4
      <ule>
 @rdesc 0:<s2>Server is enabled<nl>
        1:<s2>Server is suspened<nl>
        -1: Invalid parameters
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x2D<linkmid>documentation<linktail>
        for more details.
 @related  | ../../config.htm#FTP_ENABLE | FTP_ENABLE | definition
       in CHIP.INI file
 @related  | ../../config.htm#TELNET_ENABLE | TELNET_ENABLE | definition
       in CHIP.INI file
 @related  | ../../config.htm#WEB_ENABLE | WEB_ENABLE | definition
       in CHIP.INI file
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.27 | V1.27 | V1.27 | V1.30 | V1.30
 @target_clib V2.17
*/
int BIOS_Server_State (SERVER_SPEC which_server)
{
    _BX = which_server ;
     _AH = BIOS_SERVER_STATE ;
    asm { int BIOS_SWI_2  } ;

    return _AX;
}
#endif

/*************************************************************************/
// Fast findfirst
/*************************************************************************/
#ifdef _bios228_
/*
 @doc DOC_bios228_
 ---------------------------------------------------------------
 Fast findfirst
 ---------------------------------------------------------------
 @clib  BIOS_Fast_Findfirst | Begins a file system directory scan with 
        node locked. |
        <cfont>int BIOS_Fast_Findfirst (const char far *filename,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; FILE_FIND far *find,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; unsigned int attributes );<efont> |
 @parm   int | filename  | Pointer to null terminated ASCII file name pattern
         for search which may contain * and ? wild card characters.
 @parm   int | find  | Pointer to a 
    <linkto>../../biosstruc.HTM#FILE_FIND<linkmid>FILE_FIND<linktail>
     structure that will be initialized inside this API call.
 @parm   int | attributes  | File attributes (provisional, not used!)
 @rdesc  0:<s2>No file found<nl>
         1:<s2>Success
 @comm   This function and the
         <linkto>bios229.htm<linkmid>BIOS_Fast_Findnext<linktail>
         provide a slightly faster
         findfirst/next access than do the DOS compatible functions available on
         software interrupt
         <linkto>../../DOSEMU.HTM#0x210x4E<linkmid>0x21<linktail>.<s2>
         (Historically, this function was significantly faster than
         the @Chip-RTOS's DOS findfirst/findnext implementation.<s2> But
         since this time the DOS functions have been corrected so the
         speed advantage is no longer an issue here.)<s2>
         This function places a delete protection
         lock on the directory being searched.<nl>
       <nl>
       This function is reentrant.<s2>  However, eventually the system will
       run out of file system resources (e.g. directory nodes) if too many sessions
       are simultaneously active.<nl>
       <nl>
         These functions work in a similar way to the DOS SWI 0x21 findfirst/next
         functions.<s2> <code>BIOS_Fast_Findfirst<codee> must be called first.<s2> Then the
         <code>BIOS_Fast_Findnext<codee> is used repeatedly as required to iterate through
         all the files in a directory matching the specified <code>filename<codee>
         pattern.<nl>
         <nl>
         When a lock protection against directory delete is not desired
         between calls to the file iteration functions, the normal C-library
         findfirst/findnext functions may instead be used. (Or
         <linkto>bios22A.htm<linkmid>BIOS_LFN_Findfirst<linktail> functions
         for SC1x3/SC2x case.)<nl>
         <nl>
         <bold>CAUTION:<bolde><nl>
         <nl>
       The <linkto>bios230.htm<linkmid>BIOS_Fast_Find_Done<linktail> function
       must be called if the Findfirst/Findnext sequence is stopped prior to 
       these iteration functions returning with a zero ("File not found")
       indication.<s2> This is important so that the directory can be unlocked
       and file system resources released!<nl>

 @commtarget SC1x3/SC2x |  Long file names can be accessed with the 
        <linkto>bios22A.htm<linkmid>BIOS_LFN_Findfirst<linktail> function.
        Long file names cannot be accessed with this API.  Only DOS 8.3 file
        names can be accessed with this API.

 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x28<linkmid>documentation<linktail>
        for more details.
 @Also  bios229.htm |  BIOS_Fast_Findnext |
        bios230.htm |  BIOS_Fast_Find_Done |
        bios22A.htm |  BIOS_LFN_Findfirst
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V0.91 | V1.00
*/
int BIOS_Fast_Findfirst (const char far *filename,
                         FILE_FIND far *find,
                         unsigned int attributes)
{
    _CX = attributes ;
    _BX = FP_SEG(filename) ;
    _SI = FP_OFF(filename) ;
    _ES = FP_SEG(find) ;
    _DI = FP_OFF(find) ;

    _AH = BIOS_FAST_FINDFIRST ;
    asm { int BIOS_SWI_2  } ;

    return _AX ;
}
#endif

/*************************************************************************/
// Fast findnext
/*************************************************************************/
#ifdef _bios229_
/*
 @doc DOC_bios229_
 ---------------------------------------------------------------
 Fast findnext
 ---------------------------------------------------------------
 @clib  BIOS_Fast_Findnext | Continue iteration of files in a directory
        locked against delete. |
        <cfont>int BIOS_Fast_Findnext ( FILE_FIND far *find );<efont> |
 @parm  int | find | Pointer to the
    <linkto>../../biosstruc.HTM#FILE_FIND<linkmid>FILE_FIND<linktail>
     structure initialized by a
        <linkto>bios228.htm<linkmid>BIOS_Fast_Findfirst<linktail> call.
 @rdesc 0:<s2>No file found<nl>
        1:<s2>Success
 @comm  This function continues the iteration of files found in a directory.
        <s2>The directory search process must be started with the
        <linkto>bios228.htm<linkmid>BIOS_Fast_Findfirst<linktail> function.<nl>
        <nl>
       This function is reentrant.<nl>
       <nl>
        <bold>Important:<bolde>
        <ul>
        The <linkto>bios230.htm<linkmid>BIOS_Fast_Find_Done<linktail> function
        must be called when finished with the iteration to unlock the
        directory unless a zero "No file found" indication was
        returned on your final call to <code>BIOS_Fast_Findnext<codee>.<s2>
        (The resources have already been released in this case.)
        <nl>
        <ule>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x29<linkmid>documentation<linktail>
        for more details.
 @Also  bios228.htm |  BIOS_Fast_Findfirst |
        bios230.htm |  BIOS_Fast_Find_Done | 
        bios22B.htm |  BIOS_LFN_Findnext
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V0.91 | V1.00
*/
int BIOS_Fast_Findnext (FILE_FIND far *find)
{
    _ES = FP_SEG(find) ;
    _DI = FP_OFF(find) ;

    _AH = BIOS_FAST_FINDNEXT ;
    asm { int BIOS_SWI_2  } ;

    return _AX ;
}
#endif

/*************************************************************************/
// LFN findfirst
/*************************************************************************/
#ifdef _bios22A_
/*
 @doc DOC_bios22A_
 ---------------------------------------------------------------
 LFN findfirst
 ---------------------------------------------------------------
 @clib  BIOS_LFN_Findfirst | Begin iteration of files in a specified long
         file name path. |
        <cfont>int BIOS_LFN_Findfirst (const char far *filename,<nl>
        <tab><tab><tab><tab><tab><s3> LFN_FILE_FIND far *find),<nl>
        <tab><tab><tab><tab><tab><s3> unsigned char<tab> lock_the_node);<efont> |
 @parm   int | filename  | Pointer to null terminated ASCII file name pattern
         for search which may contain * and ? wild card characters.
 @parm   int | find  | Pointer to a
    <linkto>../../biosstruc.HTM#LFN_FILE_FIND<linkmid>LFN_FILE_FIND<linktail>
     structure that will be initialized inside this API call.
 @parm   int | lock_the_node  | Boolean set non-zero to leave the directory
         node lock protected against delete on successful return.<s2> Set
         to zero to leave the directory unlocked on return. 
 @rdesc  0:<s2>No file found<nl>
         1:<s2>Success
 @comm   This function and the
         <linkto>bios22B.htm<linkmid>BIOS_LFN_Findnext<linktail>
         provide access to the long file names.<s2>  When the
         <code>lock_the_node<codee> Boolean is FALSE then these functions
         behave similar to the DOS findfirst/findnext functions provided 
         by the compiler C-libraries.<s2> A significant difference is
         that the <linkto>bios22C.htm<linkmid>BIOS_LFN_Find_Done<linktail>
         function must be called to prevent a memory leak if the
         search is terminated before the end.<nl>
         <nl>
         When the <code>lock_the_node<codee> Boolean is TRUE then these
         functions behave similar to the 
         <linkto>bios228.htm<linkmid>BIOS_Fast_Findfirst<linktail> and
         <linkto>bios229.htm<linkmid>BIOS_Fast_Findnext<linktail> functions.
         <s2> A delete protection lock is placed on the directory being
         scanned by these functions.<nl>
       <nl>
       This function is reentrant.<s2>  However, eventually the system will
       run out of file system resources (e.g. directory nodes) if too 
       many sessions are simultaneously active.<nl>
       <nl>
        For <linkto>../../PLP.htm<linkmid>PLP<linktail> drives, setting the
        <code>lock_the_node<codee> non-zero will make the 
        <linkto>bios22B.htm<linkmid>BIOS_LFN_Findnext<linktail> function
        operate more efficiently.<s2>  When <code>lock_the_node<codee> here is zero,
        the <linkto>bios22B.htm<linkmid>BIOS_LFN_Findnext<linktail> function must
        rescan the directory block list from the top on each call in order to
        reestablish its cursor position within the directory list.<s2> (This rescan
        covers for possible block movement that may have occurred on the PLP drive
        since the previous call.)<s2>  For directories
        with lots of files, this could require some significant amount of FAT reading
        on each <linkto>bios22B.htm<linkmid>BIOS_LFN_Findnext<linktail> call.
       <nl><nl>
         <bold>CAUTION:<bolde><nl>
         <nl><ul>
       The <linkto>bios22C.htm<linkmid>BIOS_LFN_Find_Done<linktail> function
       must be called if the Findfirst/Findnext sequence is stopped prior to 
       these iteration functions returning with a zero ("File not found")
       indication.<s2> This is important so that the directory can be unlocked
       and system resources released!<nl>
       <ule>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x28<linkmid>documentation<linktail>
        for more details.
 @Also  bios22B.htm |  BIOS_LFN_Findnext |
        bios22C.htm |  BIOS_LFN_Find_Done | 
        bios228.htm |  BIOS_Fast_Findfirst
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00
 @target_clib V2.02
*/
int BIOS_LFN_Findfirst (const char    far *filename,
                        LFN_FILE_FIND far *find,
                        BOOL_              lock_the_node)
{
    _CX = 0 ;                   // Remains so if no support in RTOS
    _BX = FP_SEG(filename) ;
    _SI = FP_OFF(filename) ;
    _ES = FP_SEG(find) ;
    _DI = FP_OFF(find) ;
    _AL = lock_the_node ;
    _AH = BIOS_LFN_FINDFIRST ;
    asm { int BIOS_SWI_2  } ;

    return _CX ;
}
#endif  // bios22a

/*************************************************************************/
// LFN findnext
/*************************************************************************/
#ifdef _bios22B_
/*
 @doc DOC_bios22B_
 ---------------------------------------------------------------
 Long file name findnext
 ---------------------------------------------------------------
 @clib  BIOS_LFN_Findnext | Continue iteration of files in a directory. |
        <cfont>int BIOS_LFN_Findnext ( LFN_FILE_FIND far *find );<efont> |
 @parm  int | find | Pointer to the
    <linkto>../../biosstruc.HTM#LFN_FILE_FIND<linkmid>LFN_FILE_FIND<linktail>
    structure initialized by a 
        <linkto>bios22A.htm<linkmid>BIOS_LFN_Findfirst<linktail> call.
 @rdesc 0:<s2>No file found<nl>
        1:<s2>Success
 @comm  This function continues the iteration of files found in a directory.
        <s2>The directory search process must first be started with the
        <linkto>bios22A.htm<linkmid>BIOS_LFN_Findfirst<linktail> function.<nl>
        <nl>
       This function is reentrant.<nl>
        <nl>
        <bold>Important:<bolde>
        <ul>
        The <linkto>bios22C.htm<linkmid>BIOS_LFN_Find_Done<linktail> function
        must be called when finished with the iteration to unlock the
        directory unless a zero "No file found" indication was
        returned on your final call to <code>BIOS_LFN_Findnext<codee>.<s2>
        (The resources have already been released in this case.)
        <nl>
        <ule>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x2B<linkmid>documentation<linktail>
        for more details.
 @Also  bios22A.htm |  BIOS_LFN_Findfirst |
        bios22C.htm |  BIOS_LFN_Find_Done | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00
 @target_clib V2.02
*/
int BIOS_LFN_Findnext (LFN_FILE_FIND far *find)
{
    _CX = 0 ;                   // Remains so if no support in RTOS
    _ES = FP_SEG(find) ;
    _DI = FP_OFF(find) ;

    _AH = BIOS_LFN_FINDNEXT ;
    asm { int BIOS_SWI_2  } ;

    return _CX ;
}
#endif


/*************************************************************************/
// LFN find done
/*************************************************************************/
#ifdef _bios22C_
/*
 @doc DOC_bios22C_
 ---------------------------------------------------------------
 LFN find done
 ---------------------------------------------------------------
 @clib  BIOS_LFN_Find_Done | Unlock the directory following Findfirst/next
        operation.  |
        <cfont>void BIOS_LFN_Find_Done ( LFN_FILE_FIND far *find ); <efont> |
 @parm  int | find | Pointer to the
    <linkto>../../biosstruc.HTM#LFN_FILE_FIND<linkmid>LFN_FILE_FIND<linktail>
    structure initialized by a 
        <linkto>bios22A.htm<linkmid>BIOS_LFN_Findfirst<linktail> call.
 @rdesc  -- none --
 @comm  The function release memory resources and unlocks the directory 
        being searched by the
        <linkto>bios22A.htm<linkmid>BIOS_LFN_Findfirst<linktail>
        and <linkto>bios22B.htm<linkmid>BIOS_LFN_Findnext<linktail>
        functions.<nl>
        <nl>
        This resource releasing call is necessary when a 
        <linkto>bios22A.htm<linkmid>BIOS_LFN_Findfirst()<linktail>
        / <linkto>bios22B.htm<linkmid>BIOS_LFN_Findnext()<linktail>
        sequence is aborted prior to a "file not found" zero return
        value from one of these directory scan API.<s2>  Calling this
        function after the "file not found" zero was returned by the
        other functions does no harm and performs no operation since
        the resources had already been released in this case.<nl>
       <nl>
       This function is reentrant.<nl>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x2C<linkmid>documentation<linktail>
        for more details.
 @Also  bios22A.htm |  BIOS_LFN_Findfirst |
        bios22B.htm |  BIOS_LFN_Findnext | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00
 @target_clib V2.02
*/
void BIOS_LFN_Find_Done (LFN_FILE_FIND far *find)
{
    _ES = FP_SEG(find) ;
    _DI = FP_OFF(find) ;

    _AH = BIOS_LFN_FINDDONE ;
    asm { int BIOS_SWI_2  } ;
}
#endif


/*************************************************************************/
// Install a user int not supported handler
/*************************************************************************/
#ifdef _bios22E_
/*
 @doc DOC_bios22E_
 ---------------------------------------------------------------
 Install a user int not supported handler
 ---------------------------------------------------------------
 @clib  BIOS_Install_IntNotSupported_Handler | Install a user interrupt not supported handler. |
        <cfont>USER_INTNOTSUPPORTED_HANDLER BIOS_Install_IntNotSupported_Handler (
        <tab><tab><tab><tab><tab>USER_INTNOTSUPPORTED_HANDLER vector );<efont> |
 @parm  int | vector  |  Far pointer to callback procedure.<s2>Set to zero
        to un-install the handler.
 @rdesc Old handler
 @comm  The user can install an handler function, that will execute if an
        unsupported interrupt is called by an application or inside of the @CHIP-RTOS.<s2>
        Only one handler callback is supported by the system.<s2>
        Calling this API with a NULL <cfont>vector<efont> will remove
        any previously installed handler.<s2> Before a program exits, it
        must remove any installed callback.<nl>
        <nl>
        A second call with a non-zero <cfont>vector<efont> will replace
        any previous callback vector.<nl>
        <nl>
        The callback function must have the following form:<nl>
        <nl>
        <tab><code>int huge _pascal IntNotSupp_Handler (int intnumber, int ax)<codee><nl>
        <nl>
        If the callback function returns the value 0, the error message
        that is normally output to STDOUT is skipped by the RTOS. If the callback
        returns the value 1, the printing of the error message depends on a
        <linkto>../../config.htm#TRACEINTNOTSUPP<linkmid>CHIP.INI<linktail> setting.<nl>
        <nl>

 @rtos  This library function invokes a RTOS
        <linkto>../../biosints.htm#0xA00x2E<linkmid>software interrupt<linktail>.
 @also  bios221.htm |  BIOS_Reboot | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.52 | V1.52
*/
USER_INTNOTSUPPORTED_HANDLER BIOS_Install_IntNotSupported_Handler (USER_INTNOTSUPPORTED_HANDLER vector)
{
    _ES = FP_SEG(vector) ;
    _DI = FP_OFF(vector) ;
    _AH = BIOS_INSTALL_INTNOTSUPP ;
    asm { int BIOS_SWI_2  } ;

    return MK_FP(_ES, _DI);
}
#endif


/*************************************************************************/
// Fast find done
/*************************************************************************/
#ifdef _bios230_
/*
 @doc DOC_bios230_
 ---------------------------------------------------------------
 Fast find done
 ---------------------------------------------------------------
 @clib  BIOS_Fast_Find_Done | Unlock the directory following Findfirst/next
        operation.  |
        <cfont>int BIOS_Fast_Find_Done ( FILE_FIND far *find ); <efont> |
 @parm  int | find  | Pointer to the FILE_FIND structure used at the
        <linkto>bios228.htm<linkmid>BIOS_Fast_Findfirst<linktail> call.
 @rdesc  0 (constant)
 @comm  The function unlocks the directory being searched by the
        <linkto>bios228.htm<linkmid>BIOS_Fast_Findfirst<linktail>
        and <linkto>bios229.htm<linkmid>BIOS_Fast_Findnext<linktail>
        functions.<nl>
        <nl>
        This call is necessary when a 
        <linkto>bios228.htm<linkmid>BIOS_Fast_Findfirst()<linktail>
        / <linkto>bios229.htm<linkmid>BIOS_Fast_Findnext()<linktail>
        sequence is aborted prior to a "file not found" zero return
        value from one of these directory scan API.<s2>  Calling this
        function after the "file not found" zero was returned by the
        other functions does no harm and performs no operation since
        the resources had already been released in this case.<nl>
       <nl>
       This function is reentrant.<nl>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x30<linkmid>documentation<linktail>
        for more details.
 @Also  bios228.htm |  BIOS_Fast_Findfirst |
        bios229.htm |  BIOS_Fast_Findnext | 
        bios22C.htm |  BIOS_LFN_Find_Done
@target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00
*/
int BIOS_Fast_Find_Done (FILE_FIND far *find)
{
    _ES = FP_SEG(find) ;
    _DI = FP_OFF(find) ;

    _AH = BIOS_FAST_FINDDONE ;
    asm { int BIOS_SWI_2  } ;

    return _DX ;
}
#endif

/*************************************************************************/
// Detect Ethernet link state
/*************************************************************************/
#ifdef _bios231_
/*
 @doc DOC_bios231_
 ---------------------------------------------------------------
 Detect Ethernet link state
 ---------------------------------------------------------------
 @clib  BIOS_Ethernet_State | Detect Ethernet link state.  |
        <cfont>unsigned int BIOS_Ethernet_State ( unsigned int *init_error,<nl>
        <tab><tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; unsigned int *phy_state );<efont> |
 @parm  int | init_error  | non-zero indicates initialization or reset procedure
        of Ethernet device failed.
 @parm  int | phy_state  | SC13/SC1x3/SC2x only: phy status<nl>
        Bit 14 <tab><tab> 1 = Link Not detected<nl>
        Bit 07 <tab><tab> 1 = 100Base-TX mode, 0=10Base-T mode<nl>
        Bit 06 <tab><tab> 1 = Device in Full Duplex mode
 @rdesc non-zero indicates have no Ethernet link.
 @comm  If return value is non-zero (no Ethernet link), this
        may be due to the network cable not being connected.<nl>
        In the SC12, a zero is output to <cfont>phy_state<efont>.
 @commtarget SC1x3 | This function references ETH0.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x31<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.03 | V1.00 | n/a   | V0.90 | V1.00
*/
unsigned int BIOS_Ethernet_State (unsigned int *init_error,
                                  unsigned int *phy_state)
{
    _AH = BIOS_ETHERNET_STATE ;
    asm { int BIOS_SWI_2  } ;

    *init_error = _DX;
    *phy_state  = _CX;

    return _AX;
}
#endif

/*************************************************************************/
// Set a memory gap between DOS programs
/*************************************************************************/
#ifdef _bios232_
/*
 @doc DOC_bios232_
 ---------------------------------------------------------------
 Set a memory gap between DOS programs
 ---------------------------------------------------------------
 @clib  BIOS_Set_Memory_Gap | Set the memory gap used between the loaded
        DOS programs.  |
        <cfont>int BIOS_Set_Memory_Gap ( unsigned int paragraphs );<efont> |
 @parm  int | paragraphs  | Size of memory gap in 16 byte (SC1x) or 256 byte (SC2x/SC1x3)
        paragraphs:<s2>
        range [0 .. 2048]
 @rdesc 0:<s2>Successful<nl>
        -1:<s2>Failure, invalid value in <code>paragraphs<codee><nl>
 @comm  This function sets the size of the memory gap that will be used between
        subsequently loaded DOS programs.<s2>This gap serves as a memory reserve.<nl>
        <nl>
        Some programs compiled with Borland C 5.02 try to increase the
        size of their program memory block at runtime before, for
        example, opening a file with Borland C-Library function fopen.<s2>
        (The programs calls int21h
        <linkto>../../DOSEMU.HTM#0x210x4A<linkmid>0x4A<linktail>.<s2>
        This happens down inside the
        C-Library fopen function and is not directly visible to the application programmer.)<s2>

        This memory resize call fails if another program has been loaded after
        the one making the call due to now there is no memory space
        left for increasing the memory size of the first program.<s2> The program
        returns from fopen with  an error.<s2>
        The global program variable errno is set to value 8 (not enough memory).<s2>
        To prevent this error the size of a memory gap between two loaded programs can
        be controlled.<s2>
        The value is defined in terms of memory paragraphs 
        (1 paragraph = 16 bytes on SC1x / 256 bytes on SC2x/SC1x3).<s2>
        This value can also defined in the
        <linkto>../../config.htm#DOSLOADERMEMGAP<linkmid>CHIP.INI<linktail> file.<nl>
        <nl>
        This strategy could fail in the cases where programs are terminated and
        are started again.<nl>
        <nl>
        It is usually not necessary to set this entry, if the application does not show
        the described error.<s2>Only if a C-Library function call sets errno to 8,
        should this value be defined.<s2> We recommend in that case a value of 
        128 paragraphs for SC1x or 8 paragraphs for SC1x3 (2048 bytes in either case).<s2>

  @commtarget SC1x3/SC2x |
      The <linkto>../BeckHeap/BeckHeap.htm<linkmid>BeckHeap library<linktail> provides an
      alternative solution to this memory problem.

 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x32<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00
*/
int BIOS_Set_Memory_Gap (unsigned int paragraphs)
{
    _BX = paragraphs ;

    _AH = BIOS_MEMORY_GAP ;
    asm { int BIOS_SWI_2  } ;

    return _AX ;
}
#endif

/*************************************************************************/
//Specify the stdin/stdout channels
/*************************************************************************/
#ifdef _bios233_
/*
 @doc DOC_bios233_
 ---------------------------------------------------------------
 Specify the stdin/stdout channels
 ---------------------------------------------------------------
 @clib  BIOS_Select_Stdio | Specify the stdin / stdout channels.  |
        <cfont>int BIOS_Select_Stdio ( unsigned int ports, unsigned char direction );<efont> |
 @parm  int | ports  | Bit field specifying the channels
        using a combination of following masks:<nl>
        <nl>
        <ul>
        B0:<s2>STDIO_EXT - EXT serial port<nl>
        B1:<s2>STDIO_COM - COM serial port<nl>
        B2:<s2>STDIO_TELNET - Telnet<nl>
        B3:<s2>STDIO_USER - User port<nl>
        B4:<s2>STDIO_SSH - SSH (SC1x3/SC2x only)<nl>
        <ule>
 @parm  int | direction  | Bit field specifying
        either stdin, stdout or both using a
        combination of following masks<nl><nl>
        <ul>
        B0:<s2>SET_STDOUT<nl>
        B1:<s2>SET_STDIN<nl>
        <ule>
 @rdesc  0:<s2>Successful<nl>
        -1:<s2>Failure due to an invalid input parameter<nl>
 @comm  The bit masks are defined in BIOS_API.H include file.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x33<linkmid>documentation<linktail>
        for more details.
 @Also  bios234.htm |  BIOS_Get_Stdio  |
        bios101.htm |  BIOS_kbhit |
        bios10E.htm |  BIOS_putch
 @Also  bios211.htm |  BIOS_Set_Focus |
        bios225.htm |  BIOS_Set_Focus_Hotkey |
        bios100.htm |  BIOS_getch
 @Also  bios235.htm |  BIOS_Install_User_Stdio | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V1.07 | V1.00
*/
int BIOS_Select_Stdio (unsigned int ports, unsigned char direction)
{
    _BX = ports ;

    _AL = direction ;
    _AH = BIOS_SELECT_STDIO ;
    asm { int BIOS_SWI_2  } ;

    return _AX ;
}
#endif

/*************************************************************************/
// Get the current stdin/stdout channels
/*************************************************************************/
#ifdef _bios234_
/*
 @doc DOC_bios234_
 ---------------------------------------------------------------
 Get the the stdin/stdout channels
 ---------------------------------------------------------------
 @clib  BIOS_Get_Stdio | Get the stdin / stdout channels setting.  |
        <cfont>unsigned int BIOS_Get_Stdio ( void );<efont> |
 @parm  int |   | -- none --
 @rdesc Two bit fields, each one byte.<s2>
        LSB specifies the stdin, MSB specifies the stdout.<s2>
 @comm  Both bit fields returned (MSB for stdout, LSB for
        stdin) are coded as follows:<nl>
        <nl>
        <ul>
        B0:<s2>STDIO_EXT - EXT serial port<nl>
        B1:<s2>STDIO_COM - COM serial port<nl>
        B2:<s2>STDIO_TELNET - Telnet<nl>
        B3:<s2>STDIO_USER - User port<nl>
        B4:<s2>STDIO_SSH - SSH (SC1x3/SC2x only)<nl>
        <ule>
        <nl>
        The bit masks are defined in BIOS_API.H include file.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x34<linkmid>documentation<linktail>
        for more details.
 @Also  bios233.htm |  BIOS_Select_Stdio |
        bios101.htm |  BIOS_kbhit |
        bios10E.htm |  BIOS_putch
 @Also  bios211.htm |  BIOS_Set_Focus |
        bios225.htm |  BIOS_Set_Focus_Hotkey |
        bios100.htm |  BIOS_getch
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V1.07 | V1.00
*/
unsigned int BIOS_Get_Stdio (void)
{
    _AH = BIOS_GET_STDIO ;
    asm { int BIOS_SWI_2  } ;

    asm mov ah, bl // move STDOUT to high byte
    asm mov al, cl // move STDIN  to low  byte

    return _AX;
}
#endif

/*************************************************************************/
// Install user specific stdio handlers
/*************************************************************************/
#ifdef _bios235_
/*
 @doc DOC_bios235_
 ---------------------------------------------------------------
 Install user specific stdio handlers
 ---------------------------------------------------------------
 @clib  BIOS_Install_User_Stdio | Install user specific stdio handlers.  |
        <cfont>void BIOS_Install_User_Stdio ( const USER_STDIO_FUNCS far *vectors );<efont> |
 @parm  int | vectors  | Pointer to a USER_STDIO_FUNCS type data
        structure prepared by caller.<s2>Set this parameter to null to
        uninstall the user's device handlers.
 @rdesc -- none --
 @comm  This function installs user specific stdio channel handlers, allowing
        the user to connect their own input/output device such as a display
        or keyboard to the IPC@CHIP&reg;.<s2> A TCP application similar to Telnet
        would be another example.<nl>
        <nl>
        The user must implement four functions in their application to cover
        reading and writing characters from/to their new stdin/stdout device.<s2>
        After installing these functions with this API call and then setting stdin
        and/or stdout to the new user channel with the
        <linkto>bios233.htm<linkmid>BIOS_Select_Stdio<linktail><s2> API,
        the @Chip-RTOS will call these user functions at each stdin and
        stdout operation.<nl>
        <nl>

        The following type definitions can be found in BIOS_API.H header
        file:<nl>
        <nl>
        typedef int  huge (far *USER_KBHIT) (void);<nl>
        typedef void huge(far *USER_PUTCH) (char chr);<nl>
        typedef void huge(far *USER_PUTSTR) (const char far * pch, int n);<nl>
        typedef int huge (far *USER_GETCH) (void);<nl>
        <nl><nl>
        typedef struct tag_user_stdio<nl>
        {<nl>
        <tab><tab>   USER_KBHIT<s2>  user_kbhit;<nl>
        <tab><tab>   USER_GETCH<s2>  user_getch;<nl>
        <tab><tab>   USER_PUTCH<s2>  user_putch;<nl>
        <tab><tab>   USER_PUTSTR     user_putstr;<nl>
        } USER_STDIO_FUNCS;<nl><nl>

        <nl>
        Functions to be implemented by the user:<nl><nl>
        // user_kbhit returns a 1 if a character is available, 0 if not.<nl>
        int  huge user_kbhit(void);<nl>
        <nl>
        // user_getch reads a char from stdin (waits if none available)<nl>
        int  huge user_getch(void);<nl>
        <nl>
        // user_putch writes a single character to stdout<nl>
        void huge user_putch(char chr);<tab>  //write a single char to stdout<nl>
        <nl>
        // user_putstr writes a string of n characters to stdout<nl>
        void huge user_putstr(const char far * pch, int n);<nl>
        <nl>
        The user must set the vectors to this set of four callback functions in the
        USER_STDIO_FUNCS structure referenced by the <code>vectors<codee> input
        parameter.<nl>
        <nl>
        The user handlers are uninstalled by calling this API with the
        <code>vectors<codee> parameter set to zero.<nl>
        <nl>
        <bold>Important<bolde>: <nl>
        <ul>
        1. The USER_STDIO_FUNCS data structure must be static.<s2>
        The @Chip-RTOS does not make a copy of this information, but instead
        references this provided data structure during operation.<nl>
        2. If your application exits, don't forget to uninstall your stdio handler
        by calling this API call with <code>vectors<codee> parameter set to zero.
        <s2> This call will also deselect the <code>STDIO_USER<codee> from the
        stdin and stdout, in same manor as a call to
        <linkto>bios233.htm<linkmid>BIOS_Select_Stdio<linktail> could
        accomplish.<nl>
        3. Do not call your stdio functions from within your application,
        these functions must only be called from the @Chip-RTOS.<nl>
        <ule>
        <nl>
        Example (Borland C):<nl>
        @raw
        USER_STDIO_FUNCS user_stdio_funcs ;    // global variable

        // implementations of user's stdio functions
        int  huge my_kbhit(void)
        {
           //........
        }

        int huge my_getch(void)
        {
           //........
        }

        void huge my_putch(char chr)
        {
           //........
        }

        void huge my_putstr (const char * pch, int n)
        {
           //.......
        }

        void install_my_stdio_channel (void)
        {
           user_stdio_funcs.user_kbhit  = my_kbhit;
           user_stdio_funcs.user_getch  = my_getch;
           user_stdio_funcs.user_putch  = my_putch;
           user_stdio_funcs.user_putstr = my_putstr;

           BIOS_Install_User_Stdio ( &user_stdio ) ;
           BIOS_Select_Stdio ( STDIO_COM | STDIO_TELNET | STDIO_USER, // ports
                   SET_STDOUT | SET_STDIN) ;              // direction
        }

        void remove_my_stdio_channel (void)
        {
           BIOS_Install_User_Stdio ( 0 ) ;             // un-install
           // Note: This uninstall call has deselected the STDIO_USER
           //    from the stdin and stdout, so no explicit 
           //    BIOS_Select_Stdio() is needed here.
        }

        int main (void)
        {
           //......
           install_my_stdio_channel();
           //....

           // at the end of the program
           remove_my_stdio_channel():
        }

 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x35<linkmid>documentation<linktail>
        for more details.
 @Also  bios233.htm |  BIOS_Select_Stdio |
        bios101.htm |  BIOS_kbhit |
        bios10E.htm |  BIOS_putch
 @Also  bios211.htm |  BIOS_Set_Focus |
        bios225.htm |  BIOS_Set_Focus_Hotkey |
        bios100.htm |  BIOS_getch
 @Also  bios234.htm |  BIOS_Get_Stdio | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Install_User_Stdio (const USER_STDIO_FUNCS far *vectors)
{
    _ES = FP_SEG(vectors) ;
    _DI = FP_OFF(vectors) ;

    _AH = BIOS_INSTALL_USER_STDIO ;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Install a System Server Connection Handler function
/*************************************************************************/
#ifdef _bios236_
/*
@doc DOC_bios236_
 ---------------------------------------------------------------
 Install a System Server Connection Handler function
 ---------------------------------------------------------------
 @clib  BIOS_Connection_Handler | Install a system server
        connection handler function.  |
        <cfont>int BIOS_Connection_Handler ( CONN_HANDLER handler,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp; SERVER_SPEC which_server );<efont> |
 @parm  int | handler  | Vector to callback function
 @parm  int | which_server  | Enumerator:<nl>
        <ul>
        SS_FTP_SERVER = 0<nl>
        SS_TELNET_SERVER = 1<nl>
        SS_WEB_SERVER = 2<nl>

        SC1x3/SC2x only:<nl>
        SS_SSL_WEB_SERVER = 3<nl>
        SS_SSH_SERVER      = 4

        <ule>
 @rdesc 0:<s2>Success<nl>
        -1:<s2>Invalid <code>which_server<codee> parameter<nl>
 @comm   The installed connection handler will be executed by TCPIP
         if a client establishes a connection
         to the server (FTP, WEB, Telnet,SSL Webserver, SSH Server).<s2>

        A connection handler function must be declared in the following way:<nl><nl>
        <code>int huge UserConnectionHandler( <nl>
        <tab><tab><tab><tab><tab> struct sockaddr far *sockptr );<codee><nl><nl>

        <nl>
        Example usage:<nl>
        <nl>
        The implemented handler function could check the source IP address
        (Client's IP), comparing this IP with an application internal list of
        allowed IP addresses and reject the connection by returning a non-zero
        value if the source IP is not in the list.<nl><nl>
        If the connection handler returns zero the connection will be established.<s2>
        If it returns a non-zero value, the connection will be aborted.<nl>
        <ule>
        A connection handler can be removed by calling <cfont>BIOS_Connection_Handler<efont>
        with a null pointer for the <cfont>handler<efont> parameter.


        @commtarget SC1x | Example handler:<nl>
        The handler can read the IP Address
        and the Port in the <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in struct
        <linktail>.  (If desired, the IP address in the <cfont>sin_addr<efont> structure
        member can be converted to ASCII using the TCP/IP
        <linkto>../../tcpipapi.htm#0xAC0x11<linkmid>API_INETTOASCII<linktail> function.)<s2>


        <cfont>
        int huge UserConnectionHandler( struct sockaddr * SockAddr )<nl>
        {<nl>
        <tab>char ip_str[INET_ADDRSTRLEN];<nl>
        <tab>InetToAscii(&((struct sockaddr_in *)SockAddr)->sin_addr.s_addr<nl>
        <tab><tab><tab><tab>,ip_str);<nl>
        <tab>helper_printf("\r\nHost %s, Port %u",ip_str,<nl>
        <tab><tab><tab><tab>((struct sockaddr_in *)SockAddr)->sin_port);<nl>
        <tab>return 0;<nl>
        }<nl><efont>

        @commtarget SC1x3/SC2x | Example handler:<nl>
        The handler can read the IP Address
        and the Port in the <linkto>../../tcpstruc.htm#sockaddr_storage<linkmid>sockaddr_storage struct
        <linktail>.
        Both address modes IPv4 and IPv6 are supported.<nl>

        @raw
        int huge UserConnectionHandler( struct sockaddr * SockAddr )
        {
          char ip_str[INET6_ADDRSTRLEN];
          struct sockaddr_in ipv4SockAddr;

          if(IN6_IS_ADDR_V4MAPPED(
              &((struct sockaddr_storage *)SockAddr)->addr.ipv6.sin6_addr))
          {
           //IPv4, copy data into  sockaddr_in variable<nl>
           ipv4SockAddr.sin_addr.s_addr=((struct sockaddr_storage *)SockAddr)
                                        ->addr.ipv6.sin6_addr.ip6Addr.ip6U32[3];
           ipv4SockAddr.sin_port=
                  ((struct sockaddr_storage *)SockAddr)->addr.ipv6.sin6_port;
           //Convert to string
           inet_ntop( AF_INET,&ipv4SockAddr.sin_addr,ip_str,INET_ADDRSTRLEN);

           //helper_printf(.........);
          }
         else
          {
           //IPv6: //Convert to string
           inet_ntop( AF_INET6,
                     &((struct sockaddr_storage *)SockAddr)
                     ->addr.ipv6.sin6_addr,ip_str,INET6_ADDRSTRLEN);
           //helper_printf(...........);
          }
          return 0;
        }


 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x36<linkmid>documentation<linktail>
        for more details.
 @Also  ../TCPIP/tcp11.htm | InetToAscii |
        ../TCPIP/tcpC2.htm | inet_ntop | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00
*/




int BIOS_Connection_Handler (CONN_HANDLER handler, SERVER_SPEC which_server)
{
    _BX = which_server ;
    _ES = FP_SEG(handler) ;
    _DI = FP_OFF(handler) ;

    _AH = BIOS_INSTALL_CONN_HANDLER ;
    asm { int BIOS_SWI_2  } ;

    return _AX ;
}
#endif


/*************************************************************************/
// Get the current file sharing mode
/*************************************************************************/
#ifdef _bios237_
/*
 @doc DOC_bios237_
 ---------------------------------------------------------------
 Get the current file sharing mode
 ---------------------------------------------------------------
 @clib  BIOS_Get_File_Sharing_Mode | Get the current file sharing mode.  |
        <cfont>int BIOS_Get_File_Sharing_Mode ( void );<efont> |
 @parm  int |  | -- none --
 @rdesc sharing mode:<s2>Non-zero if sharing mode is enabled
 @comm  By default file sharing is disabled.<s2> This has the effect, that
        a file which is opened for write access can't be opened a second time for
        read or write access.<s2>
        To avoid this security feature you can enable file sharing.<s2> This
        can also be done with the CHIP.INI entry
        <linkto>../../config.htm#DEVICE_FILESHARING<linkmid>FILESHARING<linktail>.
        <nl>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x37<linkmid>documentation<linktail>
        for more details.
 @Also  bios237a.htm | BIOS_Set_File_Sharing_Mode  | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00
*/
int BIOS_Get_File_Sharing_Mode (void)
{
    _AL = 1 ;                   // Get mode.
    _AH = BIOS_FILE_SHARING ;
    asm { int BIOS_SWI_2  } ;

    return _AX ;
}
#endif

/*************************************************************************/
// Enable/Disable file sharing
/*************************************************************************/
#ifdef _bios237a_
/*
 @doc DOC_bios237a_
 ---------------------------------------------------------------
 Enable/Disable file sharing
 ---------------------------------------------------------------
 @clib  BIOS_Set_File_Sharing_Mode | Set the file sharing mode.  |
        <cfont>void BIOS_Set_File_Sharing_Mode ( unsigned int enable_sharing );<efont> |
 @parm  int | enable_sharing  | Boolean:<s2>Set non-zero to enable file
        sharing, or zero to disable file sharing.
 @rdesc -- none --
 @comm  By default file sharing is disabled.<s2> This has the effect, that
        a file which is opened for write access can't be opened a second time for
        read or write access.<s2>
        To avoid this security feature you can enable file sharing.<s2> This
        can also be done with the CHIP.INI entry
        <linkto>../../config.htm#DEVICE_FILESHARING<linkmid>FILESHARING<linktail>.
        <nl>
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x37<linkmid>documentation<linktail>
        for more details.
 @Also  bios237.htm |  BIOS_Get_File_Sharing_Mode  | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Set_File_Sharing_Mode (unsigned int enable_sharing)
{
    _BX = enable_sharing ;

    _AL = 0 ;                   // Set mode.
    _AH = BIOS_FILE_SHARING ;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Get file name by handle
/*************************************************************************/
#ifdef _bios238_
/*
 @doc DOC_bios238_
 ---------------------------------------------------------------
 Get file name by handle
 ---------------------------------------------------------------
 @clib  BIOS_Get_File_Name | Get file name by handle.  |
        <cfont>int BIOS_Get_File_Name ( char far * filename,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned int handle );<efont> |
 @parm  int | filename  | Output parameter:<s2> Pointer to 13
        character buffer which will receive the nil terminated
        file name associated with the provided handle.
 @parm  int | handle  | File handle.
 @rdesc 0:<s2> Success<nl>
       -1:<s2> Invalid file handle
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x38<linkmid>documentation<linktail>
        for more details.
  @commtarget SC1x3/SC2x | The alternative
         <linkto>bios23A.htm<linkmid>BIOS_LFN_Get_Name<linktail>
         function can be used to retrieve the long file names.
 @Also  bios23A.htm |  BIOS_LFN_Get_Name  | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int BIOS_Get_File_Name (char far * filename, unsigned int handle)
{
    asm{
         mov cx,handle
         les bx,filename
         mov ah, BIOS_GET_FILENAME
         int BIOS_SWI_2
    }
    return _AX;
}
#endif

/*************************************************************************/
// Get long file name by handle
/*************************************************************************/
#ifdef _bios23A_
/*
 @doc DOC_bios23A_
 ---------------------------------------------------------------
 Get long file name by handle
 ---------------------------------------------------------------
 @clib  BIOS_LFN_Get_Name | Get long file name by handle.  |
        <cfont>int BIOS_LFN_Get_Name ( char far * filename,<nl>
        <tab><tab><tab><tab><tab><tab>unsigned int handle );<efont> |
 @parm  int | filename  | Output parameter:<s2> Pointer to 260
        character (LFN_MAXPATH) buffer which will receive the nil terminated
        long file name associated with the provided handle.
 @parm  int | handle  | File handle.
 @rdesc 0:<s2> Success<nl>
       -1:<s2> Invalid file handle
 @comm  The <linkto>bios238.htm<linkmid>BIOS_Get_File_Name<linktail>
       function can be used to retrieve the short alias DOS file names.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x3A<linkmid>documentation<linktail>
        for more details.
 @Also  bios238.htm |  BIOS_Get_File_Name  | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00
 @target_clib V2.02
*/
int BIOS_LFN_Get_Name (char far * filename, unsigned int handle)
{
    asm{
         mov cx,handle
         les bx,filename
         mov ah, BIOS_LFN_FILENAME
         int BIOS_SWI_2
    }
    return _AX;
}
#endif



#ifdef _bios23B_
/*
 @doc DOC_bios23B_
 ---------------------------------------------------------------
 Set ethernet operation mode
 ---------------------------------------------------------------

 @clib  BIOS_Set_Ethernet_Mode | Set operation mode of the internal ethernet controller. |
        <cfont>int BIOS_Set_Ethernet_Mode(unsigned char ethMode);<efont> |
 @parm  int | ethMode  | Input parameter:<s2>
        The internal Ethernet controller is able to operate in different operating modes.
        Select the following operating modes of the internal Ethernet device:<nl>
        <nl>
        0: Auto negotiation, Default mode<nl>
        1: Fixed 010 MBit/s, Half duplex<nl>
        2: Fixed 010 MBit/s, Full duplex<nl>
        3: Fixed 100 MBit/s, Half duplex<nl>
        4: Fixed 100 MBit/s, Full duplex<nl>

 @rdesc The current value of the ethernet operating mode.

 @comm
 This setting overlays temporarily the CHIP.INI setting
 <linkto>../../config.htm#IP_ETH_MODE<linkmid>ETH_MODE<linktail>.<nl>
 The setting becomes valid when executing the shell command
 <linkto>../../command.htm#IPETH<linkmid>IPETH<linktail> or after execution of
 <linkto>../TCPIP/tcp71.htm<linkmid>Reconfigure_ethernet<linktail> or
 BIOS interrupt 0xA0 hidden service 0x39 (ethernet hardware restart only).

 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x3B<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.23 | V1.23
 @target_clib V2.16
*/

int BIOS_Set_Ethernet_Mode(unsigned char ethMode)
{
   asm{ mov cl, ethMode
        mov ah, BIOS_SET_ETH_MODE
        int BIOS_SWI_2
   }
   return _AX;
}
#endif



#ifdef _bios23C_
/*
 @doc DOC_bios23C_
 ---------------------------------------------------------------
 Set server credentials
 ---------------------------------------------------------------

 @clib  BIOS_Set_ServerCredentials | Modify user/password settings for FTP,Telnet or SSH server temporary. |
        <cfont>BIOS_Set_ServerCredentials(int server, ServerCredentials * sc);<efont> |
 @parm  int | server  | Enumerator:<nl>
        <ul>
        SS_FTP_SERVER = 0<nl>
        SS_TELNET_SERVER = 1<nl>
        SS_SSH_SERVER      = 4
        <ule>
 @parm  int | sc | Pointer to a
                   <linkto>../../biosstruc.htm#ServerCredentials<linkmid>structure<linktail>
                   variable provided by the caller, which must contain
                   the new credentials.<nl>

 @rdesc 0:  success<nl>
        -1: Invalid parameters<nl>

 @comm
 This setting overlays temporarily the CHIP.INI setting.
 Changing the corresponding chip.ini setting can be done by calling
 <linkto>bios223.htm<linkmid>BIOS_Set_Ini_String()<linktail>

 @related | ../../config.htm#FTP_USERx | FTP user | definition in CHIP.INI.
 @related | ../../config.htm#TELNET_USERx | Telnet user | definition in CHIP.INI.
 @related | ../../config.htm#SSH_USERx | SSH user | definition in CHIP.INI.



 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x3C<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.50 | V1.50
 @target_clib V2.22
*/

int BIOS_Set_ServerCredentials(int server, ServerCredentials * sc)
{
   _CX = server ;
   _ES = FP_SEG(sc) ;
   _BX = FP_OFF(sc) ;
   _AH = BIOS_SET_SRV_CRED;
   asm { int BIOS_SWI_2  } ;
   return _AX;
}
#endif



/*************************************************************************/
// Install a UDP Config Server User Callback function
/*************************************************************************/
#ifdef _bios240_
/*
 @doc DOC_bios240_
 ---------------------------------------------------------------
 Install a UDP Config Server User Callback function
 ---------------------------------------------------------------
 @clib  BIOS_Install_UDP_Cfg_Callback | Install a UDP Config Server
        user callback function.  |
        <cfont>void BIOS_Install_UDP_Cfg_Callback ( UDP_CFG_CALLBACK callback );<efont> |
 @parm  int | callback  | Vector to callback function
 @rdesc -- none --
 @comm  This function installs a user callback function for
        the UDP Config Server.<s2> This function will be invoked when a UDP
        configuration request with command number 06 is received.<s2>
        This allows you to implement your own UDP Config sub protocol and
        commands.<nl>
        <nl>
        The UDP Cfg callback function must have the following form:<nl>
        <code><nl>
        <tab>void huge MyUdpCfgSrvCB( struct UdpCfgSrv_UserCBInfo far *infoPtr );<nl>
        <nl> <codee>
        The UDP Cfg callback function is passed an argument with
        information about the UDP Cfg Request and its requester.<s2>
        This data structure, defined in
        BIOS_API.H header file, is repeated below.<s2>The
        <linkto>../../tcpstruc.htm#sockaddr_in<linkmid>sockaddr_in<linktail>
        structure definition can be found in TCPIPAPI.H<nl>
        <nl>
        If the callback function sets a pointer in the <code>dataPtr<codee>
        member of the <code>UdpCfgSrv_UserCBInfo<codee> structure, the UDP Config will
        be sent the referenced data using the <code>dataLength<codee> member of the
        structure for the byte count.<s2> If this pointer is set to null or
        the <code>dataLength<codee> field is set to 0 then no data will be sent back to
        the requester.<nl>
        <nl>
        To remove an installed callback function, call this API function
        with a null pointer.<nl>
        <nl>
        For more information on the UDP Config Server and its protocol have
        a look at the UDP Config Server description available on our website.<nl>
        <nl>
        Note:<s2> The amount data sent and received is limited to 300 bytes maximum.

       @raw
       typedef struct UdpCfgSrv_UserCBInfo
       {
         int    length ;                         // Length of this structure
         struct sockaddr_in far *fromAddrPtr;    // Sender address pointer
         int    udpCfgSD;                        // Socket descriptor from UDP Config Server Socket
         char   far *dataPtr;                    // Data of Request package
         unsigned   dataLength;                  // Length of request package

       } UDPCFGSRV_USERCBINFO ;

 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x40<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.03 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Install_UDP_Cfg_Callback (UDP_CFG_CALLBACK callback)
{
    _ES = FP_SEG(callback) ;
    _DI = FP_OFF(callback) ;

    _AH = BIOS_UDP_CALLBACK ;
    asm { int BIOS_SWI_2  } ;
}
#endif


/*************************************************************************/
// Insert an entry into INI file
/*************************************************************************/
#ifdef _bios241_
/*
 @doc DOC_bios241_
 ---------------------------------------------------------------
 Insert an entry into INI file
 ---------------------------------------------------------------
 @clib  BIOS_Set_Ini_String_Ext | Insert an entry into INI file. |
        <cfont>int BIOS_Set_Ini_String_Ext ( const char far *fileName,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp; const char far *section,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp; const char far *item_name,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp; const char far *item_text );<efont> |
 @parm  int | fileName | Pointer to INI file name
 @parm  int | section  | Pointer to section string (max. 40 chars)
 @parm  int | item_name  | Pointer to item name (max. 40 chars)
 @parm  int | item_text  | Pointer to item text (max. 128 chars)<nl>
                           Pass a NULL pointer here to erase the complete item line
 @rdesc 0:<s2>success<nl>
       -1:<s2>Invalid string length, low heap memory or file error.
 @comm The function accepts a file name for the used INI file.
       It performs the same operations like <linkto>bios223.htm<linkmid>BIOS_Set_Ini_String()<linktail>,
       which operates always on the system CHIP.INI file. <nl><nl>
       Leading and trailing white space characters will be cut. The function stops
       reading the entry when it finds an invalid character (<lt>0x20).<nl>
       <nl>
       This API is thread safe and reentrant.<s2> This function will
       fail (no operation) if insufficient system heap memory is
       available to momentarily hold the contents of the INI file.<nl>
       <nl>
       No write to the INI file occurs if the specified
       entry already exists with the specified value.<nl>
        <nl>
        Example usage:<nl>
        @raw
        BIOS_Set_Ini_String_Ext ("A:\\MYFILE.INI", "MY_SECTION", "MY_ITEM", "VALUE_TEXT") ;

        ... produces the following INI entry in file "MYFILE.INI"

        [MY_SECTION]
        MY_ITEM=VALUE_TEXT

 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x41<linkmid>documentation<linktail>
        for more details.
 @Also  bios242.htm |  BIOS_Get_Ini_String_Ext | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.27 | V1.27 | V1.27 | V1.60 | V1.60
*/
int BIOS_Set_Ini_String_Ext (const char far *fileName,
                             const char far *section,
                             const char far *item_name,
                             const char far *item_text)
{
    BiosIniSetParams p;

    p.fileName    = fileName;
    p.sectionName = section;
    p.itemName    = item_name;
    p.text        = item_text;

    _BX = FP_SEG(&p) ;
    _SI = FP_OFF(&p) ;
    _AH = BIOS_SET_CHIP_INI_EXT ;
    asm { int BIOS_SWI_2  } ;
    return _AX ;
}
#endif

/*************************************************************************/
// Get an entry from INI file
/*************************************************************************/
#ifdef _bios242_
/*
 @doc DOC_bios242_
 ---------------------------------------------------------------
 Get an entry from INI file
 ---------------------------------------------------------------
 @clib  BIOS_Get_Ini_String_Ext | Get an entry from given INI file. |
        <cfont>int BIOS_Get_Ini_String_Ext ( const char far * fileName,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp; const char far *section,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp; const char far *item_name,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp; char far *item_text,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp; unsigned int max_len );<efont> |
 @parm  int | fileName | Pointer to INI file name
 @parm  int | section  | Pointer to section string (max. 40 chars)
 @parm  int | item_name  | Pointer to item name (max. 40 chars)
 @parm  int | item_text  | Output parameter:<s2>Pointer to where
        up to <code>max_len<codee> characters of item text will be written,
        plus a terminating nil character.
 @parm  int | max_len  | Maximum characters to output to
        <code>item_text<codee>, not including terminating nil character.<nl>
        <nl>
        <bold>Caution:<bolde><s2>
        Buffer at <code>item_text<codee> must be <code>max_len<codee> + 1
        size.
 @rdesc 0:<s2>Entry not found<nl>
        <gt>0 :<s2>Length of the string found<nl>
        -1 :<s2>INI file not found<nl>
 @comm  The function accepts a file name for the used INI file.
        It performs the same operations like <linkto>bios224.htm<linkmid>BIOS_Get_Ini_String()<linktail>,
        which operates always on the system CHIP.INI file. <nl><nl>
        This API is thread safe and reentrant.<s2> This function will
        fail (returns -1) if insufficient system heap memory is
        available to momentarily hold the contents of the INI file.<nl>
        <nl>
        Example usage:<nl>
        @raw
        // Declare an output buffer to receive the item's text
        unsigned char item_text[100] ;

        unsigned int text_length =
        BIOS_Get_Ini_String_Ext("A:\\MYFILE.INI", "MY_SECTION", "MY_ITEM",item_text, sizeof(item_text)-1);

 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x42<linkmid>documentation<linktail>
        for more details.
 @Also  bios241.htm |  BIOS_Set_Ini_String_Ext | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.27 | V1.27 | V1.27 | V1.60 | V1.60
*/
int BIOS_Get_Ini_String_Ext (const char far *fileName,
                             const char far *section,
                             const char far *item_name,
                             char far *item_text,
                             unsigned int max_len)
{
    BiosIniGetParams p;

    p.fileName    = fileName;
    p.sectionName = section;
    p.itemName    = item_name;
    p.target      = item_text;
    
    _CX = max_len ;
    _BX = FP_SEG(&p) ;
    _SI = FP_OFF(&p) ;
    _AH = BIOS_GET_CHIP_INI_EXT ;
    asm { int BIOS_SWI_2  } ;
    return _AX ;
}
#endif


/*************************************************************************/
// Write Persistent user data
/*************************************************************************/
#ifdef _bios245_
/*
 @doc DOC_bios245_
 ---------------------------------------------------------------
 Write Persistent User Data
 ---------------------------------------------------------------
 @clib  BIOS_Write_Persistent_Data | Write Persistent User Data.  |
        <cfont>void BIOS_Write_Persistent_Data ( const void far *data,<nl>
        <tab><tab><tab><tab><tab><tab><tab><tab>&nbsp; unsigned char size );<efont> |
 @parm  int | data  | data buffer which contains data to write
 @parm  int | size  | number of bytes to write, max. 192
 @rdesc none
 @comm
       A block of the IPC@CHIP flash is provided for storage of non-volatile customer
       product data.<s2>  This block is independent from the IPC@CHIP&reg file system.<s2>
       The size of this area for the targets SC1x and SC1x3/SC2x is 192 Bytes.<s2>
       Developers of IPC@CHIP-based products can use this block in any way they want,
       e.g. for programming serial number of their product or other important data.<nl>
       <nl>
       This flash area is not affected by an RTOS upgrade.<nl>

 @Also  bios246.htm |  BIOS_Read_Persistent_Data | | | |

 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x45<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Write_Persistent_Data(const void far *data, unsigned char size)
{
    _ES = FP_SEG(data);
    _SI = FP_OFF(data);
    _CL = size;
    _AH = BIOS_WRITE_PERSISTENT_DATA;
    asm { int BIOS_SWI_2  } ;
}
#endif


/*************************************************************************/
// Read Persistent user data
/*************************************************************************/
#ifdef _bios246_
/*
 @doc DOC_bios246_
 ---------------------------------------------------------------
 Read Persistent User Data
 ---------------------------------------------------------------
 @clib  BIOS_Read_Persistent_Data | Read Persistent User Data.  |
        <cfont>void BIOS_Read_Persistent_Data ( void far *data,<nl>
        <tab><tab><tab><tab><tab><tab><tab><tab> unsigned char size );<efont> |
 @parm  int | data  | data buffer where read data should be stored
 @parm  int | size  | number of bytes to read, max. 192
 @rdesc none
 @comm
       A block of the IPC@CHIP flash is provided for storage of non-volatile customer
       product data.<s2>  This block is independent from the IPC@CHIP&reg file system.<s2>
       The size of this area for the targets SC1x and SC1x3/SC2x is 192 Bytes.<s2>
       Developers of IPC@CHIP-based products can use this block in any way they want,
       e.g. for programming serial number of their product or other important data.<nl>
       <nl>
       This flash area is not affected by an RTOS upgrade.<nl>

 @Also  bios245.htm |  BIOS_Write_Persistent_Data | | | |

 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x46<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Read_Persistent_Data(void far *data, unsigned char size)
{
    _ES = FP_SEG(data);
    _DI = FP_OFF(data);
    _CL = size;
    _AH = BIOS_READ_PERSISTENT_DATA;
    asm { int BIOS_SWI_2  } ;
}
#endif


/*************************************************************************/
// Get IP address of the PPP server
/*************************************************************************/
#ifdef _bios250_
/*
 @doc DOC_bios250_
 ---------------------------------------------------------------
 Get IP address of the PPP server
 ---------------------------------------------------------------
 @clib  BIOS_Get_PPPServer_IP | Get the IP address of the PPP server.  |
        <cfont>void BIOS_Get_PPPServer_IP ( char far *ipaddr );<efont> |
 @parm  char far *| ipaddr  | Pointer to a 16 byte memory area where the IP
        address is to be stored as a null terminated string. If no PPP IP
        address is set (e.g. no link is established) the function return an
        empty string.
 @rdesc none
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x50<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Get_PPPServer_IP(char far *ipaddr)
{
    _ES = FP_SEG(ipaddr);
    _DX = FP_OFF(ipaddr);
    _AH = BIOS_GET_PPPSERVER_IP;
    asm { int BIOS_SWI_2  } ;
}
#endif

/*************************************************************************/
// Get IP address of the PPP client
/*************************************************************************/
#ifdef _bios255_
/*
 @doc DOC_bios255_
 ---------------------------------------------------------------
 Get IP address of the PPP client
 ---------------------------------------------------------------
 @clib  BIOS_Get_PPPClient_IP | Get the IP address of the PPP client.  |
        <cfont>void BIOS_Get_PPPClient_IP ( char far *ipaddr );<efont> |
 @parm  char far *| ipaddr  | Pointer to a 16 byte memory area where the IP
        address is to be stored as a null terminated string. If no PPP IP
        address is set (e.g. no link is established) the function return an
        empty string.
 @rdesc none
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x55<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void BIOS_Get_PPPClient_IP(char far *ipaddr)
{
    _ES = FP_SEG(ipaddr);
    _DX = FP_OFF(ipaddr);
    _AH = BIOS_GET_PPPCLIENT_IP;
    asm { int BIOS_SWI_2  } ;
}
#endif


/*************************************************************************/
// Get Mac address
/*************************************************************************/
#ifdef _bios258_
/*
 @doc DOC_bios258_
 ---------------------------------------------------------------
 Get Mac address of the second ethernet controller
 ---------------------------------------------------------------
 @clib  BIOS_Get_MAC2 | Get MAC address of the second ethernet device. |
        <cfont>void  BIOS_Get_MAC2 ( unsigned char far *mac );<efont> |
 @parm  int | mac |  Output parameter:<s2>Pointer to a 6 byte memory
        area where the MAC address will be stored
 @rdesc -- none --
 @comm  This function outputs the Ethernet MAC address as a six byte
        array.
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x58<linkmid>documentation<linktail>
        for more details.
 @comm The second ethernet controller has no phy controller.
       An MII interface is provided.
       It is only accessible with an external connected phy and
       an external driver program, which must base on the
               <linkto>../../ip_dev.htm<linkmid>TCPIP device driver API<linktail>.
 @Also  ../tcpip/tcpIPR.htm | Get_IPConfig |
          bios217.htm | BIOS_Get_MAC |
           |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V0.90 | n/a
*/
void BIOS_Get_MAC2 (unsigned char far *mac)
{
    _ES = FP_SEG(mac) ;
    _DX = FP_OFF(mac) ;

    _AH = BIOS_GET_MAC2 ;
    asm { int BIOS_SWI_2  } ;
}
#endif


/*************************************************************************/
// Set fatal error record
/*************************************************************************/
#ifdef _bios259_
/*
 @doc DOC_bios259_
 ---------------------------------------------------------------
 Set fatal error record
 ---------------------------------------------------------------
 @clib  BIOS_Set_Error | Set fatal error record |
        <cfont>int  BIOS_Set_Error(unsigned errorCode, unsigned long details);<efont> |
 @parm  int | errorCode | Error code<nl>
        Codes 0..999 are reserved for the RTOS.<nl>
        Codes 1000..9999 are reserved for Beck drivers and libraries. (see
        <linkto>bios220.htm<linkmid>BIOS_Install_Error_Handler<linktail>)<nl>
        Codes 10000... can be used for user applications.
 @parm  long | details | This arbitrary integer value can be used to describe
        the error more detailed.
 @rdesc 0:  Success<nl>
        -1: Illegal (reserved) error code
 @comm  Sets the RTOS' fatal error record
 @rtos  This library function invokes an RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../biosints.htm#0xA00x59<linkmid>documentation<linktail>
        for more details.
 @also  bios220.htm | BIOS_Install_Error_Handler | | | |
 @also  ../../command.htm#ERRORS | ERRORS | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V1.30 | V1.30
 @target_clib V2.17
*/
int BIOS_Set_Error(unsigned errorCode,
                   unsigned long details)
{
    _DX = (unsigned)details;
    _CX = (unsigned)(details >> 16);
    _BX = errorCode;
    _AH = BIOS_SET_ERROR;
    asm { int BIOS_SWI_2 };
    return _AX;
}
#endif
// End BIOS.C ////////////////////////


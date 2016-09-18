/****************************************************************************
* (C) 1999-2007 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module    : FOSSIL.C
* Function  : Fossil interface, accessing the serial devices of the IPC@CHIP
* ---------------------------------------------------------------------------

$Header: FOSSIL.C, 45, 12.11.2008 12:50:58, Andre Pribil$

*****************************************************************************/

#include <dos.h>

#include "config.h"
#include "..\hw\hw_priv.h"
#include "fossil.h"
#include "hwapi.h"

#define FOSSILVECT 0x14

/*
  Note: The DOCLIST.EXE tool used by the C-Library HTML build process reacts
        to the token "#DOCLIST:" when it appears as the first non-white space
        on a line.  The tool transfers the text which follows into the
        BeckCLib.LST file that is used for the context sensitive help.

  Note: The *fossil indicates that any names that start with fossil and do not
        match any other name in our list should lead to the HTML page stated
        after the *fossil.

  #DOCLIST:*fossil clib\fossil\lib_index.htm
  #DOCLIST:FossilDriverInfo_t clib\fossil\fosInfo.htm
  #DOCLIST:fossil_event_t clib\fossil\fosEvent.htm
  #DOCLIST:FossilExternalPortCallbacks clib\fossil\FosExtCB.htm
  #DOCLIST:FOSSIL_EXT clib\fossil\fos04.htm
  #DOCLIST:FOSSIL_COM clib\fossil\fos04.htm
  #DOCLIST:FOSSIL_SER2 clib\fossil\fos04.htm
  #DOCLIST:FOSSIL_SER3 clib\fossil\fos04.htm
  #DOCLIST:FOSSIL_OUTPUT_BUFFER_EMPTY clib\fossil\fos03.htm
  #DOCLIST:FOSSIL_OUTPUT_NOT_FULL clib\fossil\fos03.htm
  #DOCLIST:FOSSIL_LINE_BREAK clib\fossil\fos03.htm
  #DOCLIST:FOSSIL_FRAMING_ERROR clib\fossil\fos03.htm
  #DOCLIST:FOSSIL_PARITY_ERROR clib\fossil\fos03.htm
  #DOCLIST:FOSSIL_OVERRUN_ERROR clib\fossil\fos03.htm
  #DOCLIST:FOSSIL_DATA_AVAILABLE clib\fossil\fos03.htm
  #DOCLIST:FOSSIL_RS485_LOWACTIVE clib\fossil\fos80.htm
  #DOCLIST:FOSSIL_RS485_LOWACTIVE clib\fossil\fos80.htm
  #DOCLIST:FOSSIL_RS485_HIGHACTIVE clib\fossil\fos80.htm
  #DOCLIST:FOSSIL_RS485_DISABLE clib\fossil\fos80.htm
  #DOCLIST:RS485_MODE clib\fossil\fos80.htm
  #DOCLIST:FOSSIL_PARITY_NO clib\fossil\fosA4.htm
  #DOCLIST:FOSSIL_PARITY_ODD clib\fossil\fosA4.htm
  #DOCLIST:FOSSIL_PARITY_EVEN clib\fossil\fosA4.htm
  #DOCLIST:FOSSIL_PARITY_MARK clib\fossil\fosA4.htm
  #DOCLIST:FOSSIL_PARITY_SPACE clib\fossil\fosA4.htm
  #DOCLIST:FOSSIL_PARITY clib\fossil\fosA4.htm
  #DOCLIST:FOSSIL_FLOWCTRL_OFF clib\fossil\fos0F.htm
  #DOCLIST:FOSSIL_FLOWCTRL_XONXOFF_SEND clib\fossil\fos0F.htm
  #DOCLIST:FOSSIL_FLOWCTRL_RTSCTS clib\fossil\fos0F.htm
  #DOCLIST:FOSSIL_FLOWCTRL_XONXOFF_RECV clib\fossil\fos0F.htm
  #DOCLIST:FOSSIL_FLOWCTRL_XONXOFF_SEND_RECV clib\fossil\fos0F.htm
  #DOCLIST:FOS_FLOW_CTRL clib\fossil\fos0F.htm
  #DOCLIST:FOS_LONG_BREAK clib\fossil\fos83.htm
  #DOCLIST:FOS_SHORT_BREAK clib\fossil\fos83.htm
  #DOCLIST:FOS_EXTRALONG_BREAK clib\fossil\fos83.htm
  #DOCLIST:FOS_BREAK_SIZE clib\fossil\fos83.htm
  #DOCLIST:FOS_DISABLE clib\fossil\fos84.htm
  #DOCLIST:FOS_ENABLE clib\fossil\fos84.htm
  #DOCLIST:FOS_TXRX_MODE clib\fossil\fos84.htm
  #DOCLIST:RTS_LOW clib\fossil\fos86.htm
  #DOCLIST:RTS_HIGH clib\fossil\fos86.htm
  #DOCLIST:RTS_NORMAL clib\fossil\fos86.htm
  #DOCLIST:FOS_RTS_MODE clib\fossil\fos86.htm
  #DOCLIST:FE_DATA_AVAIL clib\fossil\FosEvent.htm
  #DOCLIST:FE_DATA_SENT clib\fossil\FosEvent.htm
  #DOCLIST:FE_DATA_AVAIL9 clib\fossil\FosEvent.htm
  #DOCLIST:FE_DATA_SENT9 clib\fossil\FosEvent.htm
  #DOCLIST:FE_SENDQ_EMPTY clib\fossil\FosEvent.htm
  #DOCLIST:FE_ERROR_DETECTED clib\fossil\FosEvent.htm
  #DOCLIST:FE_IGNORE_DATA clib\fossil\FosEvent.htm


 @doc DOC_INDEX
 ---------------------------------------------------------------
 Fossil API Table of Contents
 ---------------------------------------------------------------
 @clibidx <tab><cfont>#include <InBraces FOSSIL\.H><efont> |
 Here is the API definition for access to the serial ports.<nl>
 <nl>
 The @Chip-RTOS offers the Fossil API for serial port communication.
 The Fossil standard uses software interrupt 0x14.
 These functions provide
 access to the @Chip-RTOS internal serial port driver for receiving and
 sending data via the serial ports.<nl>
 <nl>
 Here is a short description how the @Chip-RTOS internal serial port driver operates:<nl>
 <nl>
 Each serial port has two software buffers (queues), one for data pending
 transmission and one for storing received data bytes. The default size of
 each queue is 1024 bytes. The size of these transmit
 and receive queues are configurable via
 <linkto>../../config.htm#SERIAL_EXT_RECVQUEUE<linkmid>CHIP.INI<linktail> entries.<nl>
 <nl>
 Transfers between these software queues and the serial port hardware
 are carried out by either Direct Memory Access (DMA) hardware or by
 hardware interrupt (IRQ) driven software. By default, the available
 DMA machines are applied to the serial port receivers. This configuration
 reduces the likelihood of character loss at the receiver. This leaves the
 serial port transmitters operating with hardware interrupt (IRQ) driven software.
 Alternately, receivers can be configured for interrupt driven mode (IRQ receive mode)
 with the <linkto>../../config.htm#SERIAL_EXT_DMA<linkmid>CHIP.INI<linktail> options,
 which frees up the DMA device for other usage.
 The DMA can be applied to transmitters with the SERIAL
 <linkto>../../config.htm#SERIAL_SEND_DMA<linkmid>SEND_DMA<linktail> option.<nl>
 <nl>
 The serial port hardware issues a signal to either software (IRQ hardware interrupt)
 or to the DMA when ever the serial port transmit register is empty or a
 receiver byte is ready. This signal initiates the next byte transfer
 between the appropriate software queue and the hardware register, in or out. (This
 discussion is slightly over simplified. The driver actually uses an
 additional intermediate RAM buffer for DMA transfers.)<nl>
 <nl>

 Note that the serial port hardware send/receive buffers are only one byte (four bytes)
 deep on the SC1x (SC1x3/SC2x). So interrupt driven receivers (as opposed
 to DMA driven) can easily lose characters, particularly at higher baud rates.<nl>
 <nl>
 The serial ports may also be referred to as a UART (abbreviation for
 "Universal Asynchronous Receiver/Transmitter").<nl>
  <nl>
  For some useful comments see
 <linkto>../../program.htm<linkmid>Programming notes<linktail><nl><nl><nl>

 <tab><linkto>#Configuration<linkmid>Configuration<linktail>
 <tab><linkto>#Transmitter<linkmid>Transmitter<linktail>
 <tab><linkto>#Receiver<linkmid>Receiver<linktail>
 <tab><linkto>#ExternalPort<linkmid>External Port<linktail><tab>


 @libcat1  Configuration | fos04   | fossil_init | Initialize the fossil driver |
 @libcat1  Configuration | fos05   | fossil_deinit | Deinitialize fossil driver |
 @libcat1  Configuration | fosA4 | fossil_setbaud | Set baud rate |
 @libcat1  Configuration | fos00   | fossil_setbaud_std | Set baud rate to standard rates |
 @libcat1  Configuration | fos81   | fossil_set_extctrl | <depr> Extended line control initialization |
 @libcat1  Configuration | fos0F   | fossil_set_flowcontrol | Enable/disable flow control |
 @libcat1  Configuration | fos86   | fossil_force_rts | Force RTS signal |
 @libcat1  Configuration | fos87   | fossil_read_cts  | Read CTS signal  |
 @libcat1  Configuration | fosA1   | fossil_user_callback | Install a Fossil User Callback Function |

 @libcat1  Configuration | fos03 | fossil_status_request | <nl>Get port status | <tab> -- Status Functions --<nl>
 @libcat1  Configuration | fos1B | fossil_get_driver_info | Get driver info |
 @libcat1  Configuration | fosA0 | fossil_get_bytes_in_uart |
        Report number of bytes in UART transmit hardware buffers. |

 @libcat1  Configuration | fos80 | fossil_set_rs485 | <nl>Enable/Disable RS485 mode | <tab> -- RS-485 Control --<nl>
 @libcat1  Configuration | fos82 | fossil_set_rs485_txenable | Select RS485 pin |


 @libcat2  Transmitter | fos01 | fossil_putbyte_wait |
        Put byte in output buffer, wait if needed |
 @libcat2  Transmitter | fos0B | fossil_putbyte |
        Put byte in output buffer (without wait) |
 @libcat2  Transmitter | fos19 | fossil_writeblock |
        Write a block of data |
 @libcat2  Transmitter | fos08 | fossil_flush_output |
        Await empty transmit buffer |
 @libcat2  Transmitter | fos09 | fossil_purge_output |
        Purge output buffer |
 @libcat2  Transmitter | fos83 | fossil_send_break |
        Send break |
 @libcat2  Transmitter | fos85 | fossil_enable_transmitter |
        Enable/Disable transmitter |
 @libcat2  Transmitter | fosA5 | fossil_output_done |
        Check for empty transmitter |


 @libcat3  Receiver | fos02 | fossil_getbyte_wait |
        Get byte from input buffer (with wait) |
 @libcat3  Receiver | fos18A | fossil_getbyte |
        Get byte from input buffer (no wait) |
 @libcat3  Receiver | fos0C | fossil_peek_input |
        Peek if next byte is available |
 @libcat3  Receiver | fos18 | fossil_readblock |
        Read block of data |
 @libcat3  Receiver | fos0A | fossil_purge_input |
        Purge input buffer |
 @libcat3  Receiver | fos84 | fossil_enable_receiver |
        Enable/Disable receiver |
 @libcat3  Receiver | fosA6 | fossil_data_avail |
        Check for data available|

 @libcat4a  ExternalPort | External Port | fosA2 | fossil_register_external_port |
            Register an external port |
 @libcat4a  ExternalPort | External Port | fosA2_ext | fossil_register_external_port_ext |
            Register an external port (extended)|
 @libcat4a  ExternalPort | External Port | fosA3 | fossil_unregister_external_port |
            Unregister an external port |
*/

/******************************************************************************/
#ifdef _fos00_
/*
 @doc DOC_fos00_
 ---------------------------------------------------------------
 Set baudrate to standard baud rates
 ---------------------------------------------------------------
 @clib  fossil_setbaud_std | Set a standard baud rate and
        port configuration. |
        int fossil_setbaud_std( int port_idx,<nl>
        <tab><tab><tab><tab><tab><tab>unsigned char  config ) ; |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm   int  | config  | Configuration parameter:<nl>
    This bitmap field specifies the communication parameters.<nl>
    <nl>
    Bits 7-5: Baud rate<nl>
    <ul>
    <code>000<tab><codee>19200<nl>
    <code>001<tab><codee>38400<nl>
    <code>010<tab><codee>300<nl>
    <code>011<tab><codee>600<nl>
    <code>100<tab><codee>1200<nl>
    <code>101<tab><codee>2400<nl>
    <code>110<tab><codee>4800<nl>
    <code>111<tab><codee>9600<nl>
    <ule><nl>
    Bits 4-3: Parity<nl>
    <ul>
    <code>00<s5><codee>None<nl>
    <code>01<s5><codee>Odd<nl>
    <code>11<s5><codee>Even<nl>
    <ule><nl>
    Bit 2: Stop bits<nl>
    <ul>
    <code>0<s6><codee>1 Stop bit<nl>
    <code>1<s6><codee>2 Stop bits<nl>
    <ule><nl>
    Bits 1-0: Word length<nl>
    <ul>
    <code>10<s5><codee>7 bits<nl>
    <code>11<s5><codee>8 bits<nl>
    <ule>

 @rdesc Undefined if <cfont>port_idx<efont> parameter is invalid<nl>
        Else status code (bit field):<ul>
          bit 6: FOSSIL_OUTPUT_BUFFER_EMPTY<nl>
          bit 5: FOSSIL_OUTPUT_NOT_FULL<nl>
          bit 4: FOSSIL_LINE_BREAK   Line break detected<nl>
          bit 3: FOSSIL_FRAMING_ERROR   Framing error detected<nl>
          bit 2: FOSSIL_PARITY_ERROR   Parity error detected<nl>
          bit 1: FOSSIL_OVERRUN_ERROR   Set if overrun occurred on receiver.<nl>
          bit 0: FOSSIL_DATA_AVAILABLE   Set if data is available in receiver buffer.<ule>
 @comm
    This API is restricted to the standard UART baud rates listed above.<nl>
    <nl>
    For applications which operate with only a few fixed UART configurations,
    using this API with a constant defined for the <code>config<codee>
    argument will save some code space.<nl>
    <nl>
       If the DMA mode (send or receive mode) is enabled at
        <linkto>../../config.htm#SERIAL_SEND_DMA<linkmid>CHIP.INI<linktail>,
        the following port settings are not allowed:<ul>
            1. 8N2 (this limitation applies only to SC1x systems)<nl>
            2. 8S1<nl>
            3. 8M1<ule>
               <nl>
 @commtarget SC1x  |
             Two stop bits are only available if no parity is set.<nl>
 @commtarget SC1x3/SC2x |
             Two stop bits are only available if no parity is set or word length is
             equal to 7 bits.<nl>

 @Also fos05.htm |  fossil_deinit |
       fos81.htm |  fossil_set_extctrl  |
       fos0F.htm |  fossil_set_flowcontrol
 @Also fosA4.htm |  fossil_setbaud |
        | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x00<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
 @target_clib V2.08
*/

int fossil_setbaud_std (int port_idx, unsigned char config)
{
    _DX = port_idx ;
    _AX = config;           // AH = 0, service index
    asm { int FOSSILVECT  } ;
    return _AH ;
}
#endif


/******************************************************************************/
/*
 @doc DOC_fosA4_
 ---------------------------------------------------------------
 Set baudrate
 ---------------------------------------------------------------
 @clib  fossil_setbaud | Set baud rate and port configuration. |
        <cfont>int fossil_setbaud (int port, long baudrate, int parity,<nl>
        <tab><tab><tab><tab><tab>int wordlen, int stopbits );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  int  | baudrate  | Desired baud rate, bits per second
 @parm  int  | parity  | Enumeration type:<ul>
        FOSSIL_PARITY_NO     = 0<nl>
        FOSSIL_PARITY_ODD    = 1<nl>
        FOSSIL_PARITY_EVEN   = 2<nl>
        FOSSIL_PARITY_MARK   = 3<nl>
        FOSSIL_PARITY_SPACE  = 4<ule>
 @parm  int  | wordlen  | Bits per character (7 or 8)
 @parm  int  | stopbits  | Stop bits (1 or 2)
 @rdesc -1 = Illegal parameter<nl>
        Else status code (bit field):<ul>
          bit 6: FOSSIL_OUTPUT_BUFFER_EMPTY<nl>
          bit 5: FOSSIL_OUTPUT_NOT_FULL<nl>
          bit 4: FOSSIL_LINE_BREAK   Line break detected<nl>
          bit 3: FOSSIL_FRAMING_ERROR   Framing error detected<nl>
          bit 2: FOSSIL_PARITY_ERROR   Parity error detected<nl>
          bit 1: FOSSIL_OVERRUN_ERROR   Set if overrun occurred on receiver.<nl>
          bit 0: FOSSIL_DATA_AVAILABLE   Set if data is available in receiver buffer.<ule>
          <nl>
       The header file contains the indicated mask definitions.
 @comm Set baud rate and other parameters for specified port.<nl>
       <nl>
       If the DMA mode (send or receive mode) is enabled at
        <linkto>../../config.htm#SERIAL_SEND_DMA<linkmid>CHIP.INI<linktail>,
        the following port settings are not allowed:<ul>
            1. 8N2 (this limitation applies only to SC1x systems)<nl>
            2. 8S1<nl>
            3. 8M1<ule>
               <nl>
 @commtarget SC1x  |
       Two stop bits are only available if no parity is set.<nl>
       <nl>
       For standard baud rates, this function uses Fossil interrupt
       0x14 Service <linkto>../../fossil.htm#0x140x00<linkmid>0x00<linktail>.<nl>
       For non-standard baud rates the HAL interrupt 0xA1 "Get Frequencies"
       function <linkto>../../hardware.htm#0xA10x8A<linkmid>0x8A<linktail>
       is used to determine the maximum baud rate.<s2> Based on this
       maximum baud rate a baud rate divider is computed for the
       "Extended Line Control Initialization" Fossil interrupt
       <linkto>../../fossil.htm#0x140x81<linkmid>0x81<linktail> service.<s2>
       Then the Fossil interrupt
       <linkto>../../fossil.htm#0x140x03<linkmid>0x03<linktail> service reports
       the port's status.<nl>
       <nl>
 @commtarget SC1x3/SC2x |
       Two stop bits are only available if no parity is set or word length is
       7 bits.<nl>
       <nl>
       This function invokes Fossil interrupt 0x14 Service
       <linkto>../../fossil.htm#0x140xA4<linkmid>0xA4<linktail>.
       <nl>
       The behaviour of this function has been changed in version 2.17. It won't
       work anymore on older RTOS versions. To achieve backward compatibility to
       older RTOS versions, define FOSSIL_SETBAUD_LEGACY before including the
       CLIB headers.

 @Also fos05.htm |  fossil_deinit |
       fos81.htm |  fossil_set_extctrl  |
       fos0F.htm |  fossil_set_flowcontrol
 @Also fos00.htm |  fossil_setbaud_std |
        | | |
 @rtos This library function invokes a RTOS software interrupt (see above).
       Refer to this RTOS API function's documentation for more details.
       <ule>
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V1.30 | V1.30
*/
#ifdef _fosA4_old_
int fossil_setbaud_old(int port,
                       long baudrate,
                       FOSSIL_PARITY  parity,
                       int wordlen,
                       int stopbits)
{
    #define BAUD_LIST_SIZE (sizeof(baudtab)/sizeof(baudtab[0]))

    static unsigned int baudtab[8] = {19200, 38400, 300, 600, 1200, 2400, 4800, 9600};
    int baud_idx;

    stopbits-- ;
    if (  (wordlen < 7) || (wordlen > 8)
        ||((unsigned int)parity > (unsigned int)FOSSIL_PARITY_SPACE)
        ||((unsigned int)stopbits >= 2)
       )
    {
       return -1 ;                  // Illegal parameters
    }
    wordlen -= 5 ;

    // check parameters
    for (baud_idx = 0; baud_idx < BAUD_LIST_SIZE; baud_idx++)
    {
        if (baudrate == (long) baudtab[baud_idx])
        {
            break;
        }
    }

    // init port
    if (  (baud_idx < BAUD_LIST_SIZE)           // Found in list?
        &&(parity <= FOSSIL_PARITY_EVEN)        // No EXT CTRL needed?
       )
    {
        // use function 0x00 for baudrates up to 38400

        if (parity == FOSSIL_PARITY_EVEN)
        {
            parity = 3 ;
        }

        _AX = (wordlen + (stopbits << 2) + (parity << 3) + (baud_idx << 5))
             & 0xFF ;   // AH = 0 -> SWI service index

    } // if (baud_idx<=7)
    else
    {
        long baud_max ;
        // use extended line control init for other baud rates
        if (parity > 4)
        {
            return -1 ;                 // Illegal parameter
        }

        // get max. baudrate value
       _AX = ((unsigned)HAL_GET_FREQUENCIES << 8)  // AH = service index
           | GET_FRQ_MAX_BAUD ;                    // AL = frequency selector

        asm { int HAL_INT  } ;
        asm { mov WORD PTR baud_max,   AX } ;
        asm { mov WORD PTR baud_max+2, dx } ;

        // calc divider with integer rounding
        // Scaled @B1 so can round off divisor to nearest fit.
        // Add the '+1' as part of the round off operation.
        _CX = (unsigned int)(   (((2*baud_max) / baudrate) + 1)
         // Scaled @B1 so can round off divisor to nearest fit.
                                   >> 1) ;

        _BH = parity ;
        _BL = stopbits ;
        _DX = port;
        _AL = wordlen ;
        _AH = 0x81;              // Extended line control initialization
        asm { int FOSSILVECT  } ;

        // get status of port for final return value.
        _AH = 0x03 ;

    } // else (baud_idx<=7)

    _DX = port;
    asm { int FOSSILVECT  } ;
    return _AH ;
}  // fossil_setbaud()
#endif

#ifdef _fosA4_
#undef fossil_setbaud     // Maintain original name
int fossil_setbaud(int port,
                   long baudrate,
                   FOSSIL_PARITY  parity,
                   int wordlen,
                   int stopbits)
{
  unsigned char al;

  al = (((stopbits - 1) & 0x03) << 6) | (((wordlen - 7) & 0x03) << 4) | (parity & 0x0F);
  _BX = (unsigned short)(baudrate >> 16);
  _CX = (unsigned short)baudrate;
  _DX = port;
  _AL = al;
  _AH = 0xA4;
  asm { int FOSSILVECT  } ;
  return _AX;
}
#endif


/******************************************************************************/
#ifdef _fos01_
/*
 @doc DOC_fos01_
 ---------------------------------------------------------------
 Put byte in tx buffer, wait for room if needed
 ---------------------------------------------------------------
 @clib  fossil_putbyte_wait | Put byte in output buffer, wait if needed. |
        <cfont>int fossil_putbyte_wait ( int port, int ch );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  int  | ch  | Byte to output
 @rdesc Status  code (bit field):<ul>
          bit 6: FOSSIL_OUTPUT_BUFFER_EMPTY<nl>
          bit 5: FOSSIL_OUTPUT_NOT_FULL<nl>
          bit 4: FOSSIL_LINE_BREAK   Line break detected<nl>
          bit 3: FOSSIL_FRAMING_ERROR   Framing error detected<nl>
          bit 2: FOSSIL_PARITY_ERROR   Parity error detected<nl>
          bit 1: FOSSIL_OVERRUN_ERROR   Set if overrun occurred on receiver.<nl>
          bit 0: FOSSIL_DATA_AVAILABLE   Set if data is available in receiver buffer.<ule>
          <nl>
        The header file contains the indicated mask definitions.
 @comm  Character is queued for transmission.<s2>If there is space
        in the transmitter buffer when this call is made, the character
        will be stored and control returned to caller.<s2> If the buffer
        is full, the driver will wait for space.<s2> (This can be dangerous
        when used in combination with flow control.)
 @Also  fos0B.htm |  fossil_putbyte |
        fos02.htm |  fossil_getbyte_wait |
        fos19.htm |  fossil_writeblock
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x01<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/

int fossil_putbyte_wait(int port, int ch)
{
    _AH = 0x01;
    _AL = (char) ch;
    _DX = port;
    asm { int FOSSILVECT  } ;
    return _AH ;
}
#endif


/******************************************************************************/
#ifdef _fos02_
/*
 @doc DOC_fos02_
 ---------------------------------------------------------------
 get char, wait if needed
 ---------------------------------------------------------------
 @clib  fossil_getbyte_wait | Get byte from input buffer (with wait). |
        <cfont>int fossil_getbyte_wait ( int port );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc Received byte
 @comm  Reads a byte from the receiver buffer.<s2> Wait for a byte
        to arrive if none is available.
 @Also  fos18A.htm |  fossil_getbyte |
        fos18.htm |  fossil_readblock |
        fos01.htm |  fossil_putbyte_wait
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x02<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int fossil_getbyte_wait (int port)
{
    _AH = 0x02;
    _DX = port;
    asm { int FOSSILVECT  } ;
    return _AL ;
}
#endif


/******************************************************************************/
#ifdef _fos03_
/*
 @doc DOC_fos03_
 ---------------------------------------------------------------
 Get port status
 ---------------------------------------------------------------
 @clib  fossil_status_request | Get port status. |
        <cfont>int fossil_status_request ( int port );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc Status  code (bit field):<ul>
          bit 6: FOSSIL_OUTPUT_BUFFER_EMPTY<nl>
          bit 5: FOSSIL_OUTPUT_NOT_FULL<nl>
          bit 4: FOSSIL_LINE_BREAK   Line break detected<nl>
          bit 3: FOSSIL_FRAMING_ERROR   Framing error detected<nl>
          bit 2: FOSSIL_PARITY_ERROR   Parity error detected<nl>
          bit 1: FOSSIL_OVERRUN_ERROR   Set if overrun occurred on receiver.<nl>
          bit 0: FOSSIL_DATA_AVAILABLE   Set if data is available in receiver buffer.<ule>
          <nl>
        The header file contains the indicated mask definitions.
 @comm  Any reported UART error flags are cleared after the
        read is made for this call.<nl>
        <nl>
        For efficient receiver polling, the
        <linkto>fos18A.htm<linkmid>fossil_getbyte<linktail> or
        <linkto>fos18.htm<linkmid>fossil_readblock<linktail> methods
        are recommended.
 @Also  fos02.htm  | fossil_getbyte_wait |
        fos18A.htm | fossil_getbyte |
        fos18.htm  | fossil_readblock
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x03<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int fossil_status_request (int port)
{
    _AH = 0x03;
    _DX = port;
    asm { int FOSSILVECT  } ;
    return _AH ;
}
#endif

/*****************************************************************************
*/
#ifdef _fos04_
/*
 @doc DOC_fos04_
 ---------------------------------------------------------------
 Initialize fossil driver
 ---------------------------------------------------------------
 @clib  fossil_init | Initialize the fossil driver for specified port |
        <cfont>int fossil_init ( int port );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc 0x1954, signature from Fossil driver
 @comm  Use this function to initialize the fossil interface for a specified port.<s2>
        The user must make sure that only one process opens a port.<s2>
        If this port is used for standard
        <linkto>../../config.htm#STDIO_STDIN<linkmid>input<linktail>
        or <linkto>../../config.htm#STDIO_STDOUT<linkmid>output<linktail>
        (console), then stdin/stdout will be disabled for this port.
 @Also  fos05.htm   |  fossil_deinit |
        fosA4.htm | fossil_setbaud |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x04<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int fossil_init (int port)
{
    _DX = port ;
    _AH = 0x04 ;                // Service index
    asm { int FOSSILVECT  } ;
    return _AX ;
}
#endif


/******************************************************************************/
#ifdef _fos05_
/*
 @doc DOC_fos05_
 ---------------------------------------------------------------
 Deinitialize fossil driver
 ---------------------------------------------------------------
 @clib  fossil_deinit | Deinitialize fossil driver. |
        <cfont>void fossil_deinit ( int port );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc None
 @comm  This function restores the specified RS-232 port to
        its default settings.
 @Also  fos04.htm   | fossil_init |
        fosA4.htm | fossil_setbaud  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x05<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void fossil_deinit(int port)
{
    _DX = port ;
    _AH = 0x05 ;                // Service index
    asm { int FOSSILVECT  } ;
}
#endif

/******************************************************************************/
#ifdef _fos08_
/*
 @doc DOC_fos08_
 ---------------------------------------------------------------
 Flush output buffer, wait until done
 ---------------------------------------------------------------
 @clib  fossil_flush_output | Flush output buffer, wait until done. |
        <cfont>void fossil_flush_output ( int port );<efont>  |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc None
 @comm  Wait for all output in the output buffer to be transmitted.
 @Also  fos09.htm |  fossil_purge_output |
        fos0A.htm |  fossil_purge_input  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x08<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void fossil_flush_output (int port)
{
    _DX = port ;
    _AH = 0x08 ;                // Service index
    asm { int FOSSILVECT  } ;
}
#endif


/******************************************************************************/
#ifdef _fos09_
/*
 @doc DOC_fos09_
 ---------------------------------------------------------------
 Purge output buffer
 ---------------------------------------------------------------
 @clib  fossil_purge_output | Purge output buffer and discard the data. |
        <cfont>void fossil_purge_output ( int port );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc None
 @comm  Remove all data from the output buffer and discard it.
 @Also  fos08.htm |  fossil_flush_output |
        fos0A.htm |  fossil_purge_input  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x09<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void fossil_purge_output (int port)
{
    _DX = port ;
    _AH = 0x09 ;                // Service index
    asm { int FOSSILVECT  } ;
}
#endif


/******************************************************************************/
#ifdef _fos0A_
/*
 @doc DOC_fos0A_
 ---------------------------------------------------------------
 Purge input buffer
 ---------------------------------------------------------------
 @clib  fossil_purge_input | Purge input buffer and discard the data. |
        <cfont>void fossil_purge_input ( int port );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc None
 @comm  Remove all data from the receive buffer and discard the data.
 @Also  fos08.htm |  fossil_flush_output |
        fos09.htm |  fossil_purge_output | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x0A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void fossil_purge_input (int port)
{
    _DX = port ;
    _AH = 0x0A ;                // Service index
    asm { int FOSSILVECT  } ;
}  // fossil_purge_input()
#endif


/******************************************************************************/
#ifdef _fos0B_
/*
 @doc DOC_fos0B_
 ---------------------------------------------------------------
 Put byte in output buffer (without wait)
 ---------------------------------------------------------------
 @clib  fossil_putbyte | Put byte in output buffer (without wait). |
        <cfont>int fossil_putbyte ( int port, int ch );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  int  | ch  | Byte to send
 @rdesc 0 if byte was not accepted (no space in buffer)<nl>
        1 if byte was placed in output buffer
 @comm  Place a byte into the transmit buffer if there is space available.<s2>
        Otherwise simply return with 0, without handling the transmit byte.
 @Also  fos01.htm  | fossil_putbyte_wait |
        fos19.htm  | fossil_writeblock   |
        fos18A.htm | fossil_getbyte
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x0B<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int fossil_putbyte (int port, int ch)
{
    _DX = port ;
    _AL = (char) ch ;
    _AH = 0x0B ;                // Service index
    asm { int FOSSILVECT  } ;
    return _AX ;
}
#endif

/******************************************************************************/
#ifdef _fos0C_
/*
 @doc DOC_fos0C_
 ---------------------------------------------------------------
 Peek if next byte is available
 ---------------------------------------------------------------
 @clib  fossil_peek_input | Peek if next byte is available. |
        <cfont>int fossil_peek_input ( int port );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc -1 if no character available,<nl>
        Else next character in receiver buffer.
 @comm  Returns the next byte available in the receive buffer,
        without removing it from the buffer.
 @Also  fos02.htm  | fossil_getbyte_wait |
        fos18A.htm | fossil_getbyte  |
        fos03.htm  | fossil_status_request
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x0C<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int fossil_peek_input(int port)
{
    _DX = port ;
    _AH = 0x0C ;                // Service index
    asm { int FOSSILVECT  } ;
    return (int)_AX;
}
#endif


/******************************************************************************/
#ifdef _fos0F_
/*
 @doc DOC_fos0F_
 ---------------------------------------------------------------
 Enable/disable flow control
 ---------------------------------------------------------------
 @clib  fossil_set_flowcontrol | Enable/disable flow control. |
        void fossil_set_flowcontrol ( int port,<nl> |
        <tab><tab><tab> FOS_FLOW_CTRL flowctrl );
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  int  | flowctrl  | Enumerator specifies desired type of
        flow control:<nl>
        <nl>
        FOSSIL_FLOWCTRL_OFF = 0x0: No flow control<nl>
        FOSSIL_FLOWCTRL_XONXOFF_SEND = 0x1:<nl><ul>
          XON/XOFF on transmit<s2>(watch for XOFF while sending)
          <ule>
        FOSSIL_FLOWCTRL_RTSCTS       = 0x2:<nl><ul>
            CTS/RTS (CTS on transmit/RTS on receive)
            <ule>
        FOSSIL_FLOWCTRL_XONXOFF_RECV = 0x8:<nl><ul>
            XON/XOFF on receive (send XOFF when buffer near full)
            <ule>
        FOSSIL_FLOWCTRL_XONXOFF_SEND_RECV = 0x9:<nl><ul>
            XON/XOFF used on both Tx and Rx
        <ule>
 @rdesc  None
 @comm  Configures the flow control for a port.<nl>
        <nl>
        Since SC12 @CHIP-RTOS 1.02B XON/XOFF mode is also available if the
        <linkto>../../config.htm#SERIAL_EXT_DMA<linkmid>DMA<linktail>
        mode for the COM port is enabled but because of the internal
        functionality of DMA it is not possible to detect an XON or XOFF
        of the peer immediateley.<s2> It is possible that an overrun situation
        at the connected peer (e.g. GSM modem) could occur.<s2> We enable this
        mode now because GSM modems (any??) supports only XON/XOFF flow ctrl.<nl>
 @Also  fosA4.htm |  fossil_setbaud | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x0F<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void fossil_set_flowcontrol (int port, FOS_FLOW_CTRL flowctrl)
{
    _DX = port ;
    _AL = (unsigned char) flowctrl ;
    _AH = 0x0F ;                // Service index
    asm { int FOSSILVECT  } ;
}
#endif


/******************************************************************************/
#ifdef _fos18_
/*
 @doc DOC_fos18_
 ---------------------------------------------------------------
 Read block of data
 ---------------------------------------------------------------
 @clib  fossil_readblock | Read block of data (no wait). |
        <cfont>unsigned int fossil_readblock ( int port,<nl>
        <tab><tab><tab><tab><tab><tab><tab><tab>unsigned char far *buffer,<nl>
        <tab><tab><tab><tab><tab><tab><tab><tab>unsigned int count );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  int  | buffer  | Output parameter:<s2>Pointer to
        buffer to put received bytes into.
 @parm  int  | count  | Size of <code>buffer<codee>, maximum
        number of bytes to transfer.
 @rdesc Number of bytes transfered
 @comm  Read up to a specified number of bytes from a serial port
        input <linkto>../../CONFIG.HTM#SERIAL_EXT_RECVQUEUE<linkmid>queue<linktail>
        and return immediately.
 @Also  fos19.htm  | fossil_writeblock |
        fos02.htm  | fossil_getbyte_wait |
        fos18A.htm | fossil_getbyte
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x18<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned int fossil_readblock (int port,
                               unsigned char far *buffer,
                               unsigned int count)
{
    asm { LES  DI, buffer } ;
    _CX = count ;
    _DX = port ;
    _AH = 0x18 ;                // Service index
    asm { int FOSSILVECT  } ;
    return _AX ;
}
#endif

/******************************************************************************/
#ifdef _fos18A_
/*
 @doc DOC_fos18A_
 ---------------------------------------------------------------
 Read block of data
 ---------------------------------------------------------------
 @clib  fossil_getbyte | Get byte from input buffer (no wait). |
        <cfont>int fossil_getbyte ( int port );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc -1 if no data is available in receiver buffer,
        else next received byte
 @comm  This function uses Fossil interrupt
        0x14 Service <linkto>../../fossil.htm#0x140x18<linkmid>0x18<linktail>
        to read out a block of length one.<s2>This method of polling for
        single characters at the receiver will be considerably more
        efficient than the alternative method using the
        <linkto>fos03.htm<linkmid>fossil_status_request<linktail>
        and <linkto>fos02.htm<linkmid>fossil_getbyte_wait<linktail>
        function pair.
 @Also  fos18.htm | fossil_readblock |
        fos02.htm | fossil_getbyte_wait |
        fos03.htm | fossil_status_request
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x18<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int fossil_getbyte (int port)
{
    unsigned int buffer ;      // Read out one char into here.
    unsigned int read_count ;

    buffer = 0 ;                // Clear upper byte.

    _ES = _SS ;
    asm { LEA  DI, buffer } ;   // ES:DI = far ptr to buffer
    _CX = 1 ;
    _DX = port ;
    _AH = 0x18 ;                // Service index
    asm { int FOSSILVECT  } ;
    read_count = _AX ;
    if (read_count == 0)        // No data ready?
    {
        buffer = -1 ;           // Set "no data" indication
    }
    return buffer ;
}
#endif

/******************************************************************************/
#ifdef _fos19_
/*
 @doc DOC_fos19_
 ---------------------------------------------------------------
 Write a block of data
 ---------------------------------------------------------------
 @clib  fossil_writeblock | Write a block of data (no wait). |
        <cfont>unsigned int fossil_writeblock ( int port,<nl>
        <tab><tab><tab><tab><tab><tab><s2> const unsigned char far *buffer,<nl>
        <tab><tab><tab><tab><tab><tab><tab><tab> unsigned int count );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  int  | buffer  | Input parameter:<s2>Pointer to
        data to be transmitted
 @parm  int  | count  | Maximum number of bytes to transfer.
 @rdesc Number of bytes transfered to transmit buffer from
        <code>buffer<codee>.
 @comm  Write a block of data to the serial port output buffer.<s2>
        This function returns immediately after transfering as many
        bytes as <linkto>../../CONFIG.HTM#SERIAL_EXT_SENDQUEUE<linkmid>space<linktail>
        in transmit buffer allows.
 @Also  fos18.htm |  fossil_readblock |
        fos01.htm |  fossil_putbyte_wait |
        fos0B.htm |  fossil_putbyte
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x19<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned int fossil_writeblock (int port,
                                const unsigned char far *buffer,
                                unsigned int count)
{
    asm { LES  DI, buffer } ;
    _CX = count ;
    _DX = port ;
    _AH = 0x19 ;                // Service index
    asm { int FOSSILVECT  } ;
    return _AX ;
}
#endif

/******************************************************************************/

/***************************************************************************/
//  FossilDriverInfo Data Structure
/***************************************************************************/
/*
 @doc DOC_FosDrInfo_
 ---------------------------------------------------------------
 FossilDriverInfo
 ---------------------------------------------------------------
 @cstruc FossilDriverInfo data structure | Fossil Driver Info |
         <cfont>
         typedef<s2>struct FossilDriverInfo<nl>
         {<nl>
         <tab>unsigned size;<nl>
         <tab>unsigned char version;<s2>// (not used)<nl>
         <tab>unsigned char level;<s2>// (not used)<nl>
         <tab>char far *id;<s2>// (not used)<nl>
         <nl>
         <tab>unsigned inputBuffSize;<nl>
         <tab>unsigned inputAvailable;<nl>
         <tab>unsigned outputBuffSize;<nl>
         <tab>unsigned outputAvailable;<nl>
         <tab>unsigned char screenWidth;<s2>// (not used)<nl>
         <tab>unsigned char screenHeight;<s2>// (not used)<nl>
         <tab>unsigned char baudrateMask;<s2>// (not used)<nl>
         }  FossilDriverInfo_t ;<efont> | |
 @element   int  | size  | Size of this data structure, set to 19 by
            <linkto>fos1B.htm<linkmid>fossil_get_driver_info<linktail>.
 @element   int  | inputBuffSize  | Size of receiver buffer.
 @element   int  | inputAvailable  | Bytes available in receiver buffer.
 @element   int  | outputBuffSize  | Size of transmit buffer.
 @element   int  | outputAvailable  | Space available in transmit buffer.
 @comm   Unused fields are set to zero by
         <linkto>fos1B.htm<linkmid>fossil_get_driver_info<linktail>.
 @Also  fos1B.htm |  fossil_get_driver_info | | | |
*/
/******************************************************************************/
#ifdef _fos1B_
/*
 @doc DOC_fos1B_
 ---------------------------------------------------------------
 Get driver info
 ---------------------------------------------------------------
 @clib  fossil_get_driver_info | Get driver info. |
        int fossil_get_driver_info (int port,<nl>
        <tab><tab>FossilDriverInfo_t far *drv_info); |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  void * | drv_info  | Output parameter:<s2>  Pointer to
        <linkto>FosInfo.htm<linkmid>FossilDriverInfo<linktail>
        data structure which will be filled by this call.
 @rdesc 0x13, = sizeof(FossilDriverInfo_t)
 @comm  Get information about a serial port and driver.
 @Also  fosA0.htm |  fossil_get_bytes_in_uart | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x1B<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int fossil_get_driver_info (int port, FossilDriverInfo_t far *drv_info)
{
    asm { LES  DI, drv_info } ;
    _CX = sizeof (FossilDriverInfo_t) ;
    _DX = port ;
    _AH = 0x1B ;                // Service index
    asm { int FOSSILVECT  } ;
    return _AX ;
}
#endif

/******************************************************************************/
#ifdef _fos80_
/*
 @doc DOC_fos80_
 ---------------------------------------------------------------
 Enable/Disable RS485 mode
 ---------------------------------------------------------------
 @clib  fossil_set_rs485 | Enable/Disable RS485 mode. |
        <cfont>void fossil_set_rs485 ( int port, RS485_MODE mode);<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  int  | mode  | RS 485 mode enumerator:<nl><ul>
        FOSSIL_RS485_LOWACTIVE = 0:<s2> TxEnable low active<nl>
        FOSSIL_RS485_HIGHACTIVE = 1:<s2> TxEnable high active<nl>
        FOSSIL_RS485_DISABLE<tab>&nbsp; = 2:<s2> Disable RS485 mode<ule>
 @rdesc None
 @comm  By default the RTS signals (pins) are used to
        enable/disable the respective transmitter. (TxEnable)
 @Also  fos0F.htm |  fossil_set_flowcontrol |
        fos82.htm |  fossil_set_rs485_txenable | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x80<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void fossil_set_rs485(int port, RS485_MODE mode)
{
    _DX = port ;
    _AL = mode ;
    _AH = 0x80 ;                // Service index
    asm { int FOSSILVECT  } ;
}
#endif

/******************************************************************************/
#ifdef _fos81_
/*
 @doc DOC_fos81_
 ---------------------------------------------------------------
 Extended line control initialization
 ---------------------------------------------------------------
 @clib  fossil_set_extctrl | Extended line control initialization. |
        <cfont>void fossil_set_extctrl ( int port,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; int baud_divider,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; FOSSIL_PARITY parity,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; int wordlen,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; int stopbits );<efont> |
 @depr  fosA4.htm | fossil_setbaud
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  int  | baud_divider  | This parameter
    is the baud_divider computed as:<nl>
    <ul><nl>
        <code>baud_divider  = maximum_baud_rate / desired baud
        rate<codee><nl>
    <ule><nl>
    where <code>maximum_baud_rate<codee> is obtained through HAL
    <linkto>../HW/hal8A.htm<linkmid>hal_get_frequencies<linktail>
    function.<nl>
    <nl>
    To arrive at the closest fit value, the following round
    off calculation provides a good digital implementation
    of the above equation:<nl>
    <ul><nl>
        <code>baud_divider  = (unsigned int)<nl>
        <tab>((((2*maximum_baud_rate) / desired_baud) + 1)<nl>
        <tab><tab><tab> <gt><gt> 1) ;
        <codee><nl>
    <ule><nl>
    This calculation first scales up the baud divider to @B1, then adds
    one for round off and finally scales the baud divider back to
    \@B0 scaling with the 1 bit right shift, thereby arriving at the
    closest fit count for the desired baud rate.<nl>
 @parm  int  | parity  | Enumeration type:<ul>
        FOSSIL_PARITY_NO     = 0<nl>
        FOSSIL_PARITY_ODD    = 1<nl>
        FOSSIL_PARITY_EVEN   = 2<nl>
        FOSSIL_PARITY_MARK   = 3<nl>
        FOSSIL_PARITY_SPACE  = 4<ule>
 @parm  int  | wordlen  | Bits per character (7 or 8)
 @parm  int  | stopbits  | Stop bits (1 or 2)
 @rdesc  None
 @comm  If the DMA mode (send or receive mode) is enabled at
        <linkto>../../config.htm#SERIAL_SEND_DMA<linkmid>CHIP.INI<linktail>,
        the following port settings are not allowed:<ul>
            1. 8N2 (this limitation applies only to SC1x systems)<nl>
            2. 8S1<nl>
            3. 8M1<ule>
 @commtarget SC1x  |
             Two stop bits are only available if no parity is set.<nl>
 @commtarget SC1x3/SC2x |
             Two stop bits are only available if no parity is set or word length is
             equal to 7 bits.<nl>
 @Also  fosA4.htm |  fossil_setbaud |
        fos00.htm   | fossil_setbaud_std | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x81<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void fossil_set_extctrl (int port, int baud_divider, FOSSIL_PARITY parity,
                         int wordlen, int stopbits)
{
    _BH = parity ;
    _BL = stopbits - 1 ;
    _DX = port;
    _CX = baud_divider ;
    _AL = wordlen - 5 ;
    _AH = 0x81;               // Extended line control initialization
    asm { int FOSSILVECT  } ;
}
#endif


/******************************************************************************/
#ifdef _fos82_
/*
 @doc DOC_fos82_
 ---------------------------------------------------------------
 Select RS485 pin
 ---------------------------------------------------------------
 @clib  fossil_set_rs485_txenable | Select RS485 pin. |
        <cfont>void fossil_set_rs485_txenable ( int port, int pin );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm_sc1x  int | pin  | PIO pin number, [0..13]
 @parm_sc1x3 int | pin  | PIO pin number, [0..24,26..31]<nl>
             Use -1 to select the RTS pin (hardware functionality / default)
 @parm_sc2x int | pin  | PIO pin number, [0..1,9..11,13,18..23,27..28]<nl>
             Use -1 to select the RTS pin (hardware functionality / default)
 @rdesc None
 @comm  By default the RTS signals (pins) are used to enable/disable the
        respective transmitter. (TxEnable)<s2>
        This function lets you select any PIO as TxEnable (but not all
        make sense).<s2>To change the default, call this function before you call
        the <linkto>fos80.htm<linkmid>fossil_set_rs485<linktail> function.<s2>
 @Also  fos80.htm |  fossil_set_rs485 | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x82<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void fossil_set_rs485_txenable (int port, int pin)
{
    _DX = port;
    _AL = pin ;
    _AH = 0x82;                       // Service index
    asm { int FOSSILVECT  } ;
}
#endif


/******************************************************************************/
#ifdef _fos83_
/*
 @doc DOC_fos83_
 ---------------------------------------------------------------
 Send break.
 ---------------------------------------------------------------
 @clib  fossil_send_break | Send break |
        <cfont>void fossil_send_break ( int port, FOS_BREAK_SIZE break_size );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  int  | break_size  | Enumeration type:<ul>
        FOS_LONG_BREAK = 1, long break<nl>
        FOS_SHORT_BREAK = 2, short break<nl>
        FOS_EXTRALONG_BREAK = 3, extra long break<ule>
 @rdesc None
 @comm  A short break is a continuous Low on the TXD output for a duration of
        more than one frame transmission time M, where:<nl>
        <nl>
        <tab>M = startbit + data bits (+ parity bit)+ stop bit<nl>
        <nl>
        A long break is a continuous Low on the TXD output for a duration
        of more than two frame transmission times plus the transmission
        time for three additional bits (2M+3).<nl>
        <nl>
        A extra long break is a continuous Low on the TXD output for a duration
        of more than three frame transmission times.
 @Also  fosA4.htm |  fossil_setbaud | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x83<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void fossil_send_break (int port, FOS_BREAK_SIZE break_size )
{
    _DX = port;
    _AL = (unsigned char) break_size ;
    _AH = 0x83;                       // Service index
    asm { int FOSSILVECT  } ;
}
#endif


/******************************************************************************/
#ifdef _fos84_
/*
 @doc DOC_fos84_
 ---------------------------------------------------------------
 Enable/Disable receiver.
 ---------------------------------------------------------------
 @clib  fossil_enable_receiver | Enable/Disable receiver |
        <cfont>void fossil_enable_receiver ( int port, unsigned char mode );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  unsigned char  | mode  | Mode:<s2> FOS_DISABLE = 0, disable receiver,<s2>
                                           FOS_ENABLE = 1, enable receiver<ule>
 @rdesc None
 @comm This function is useful when using the SM35 as RS485 adapter.
       Use this function to disable the receiver before transmitting data.
       Wait until all data is send and reenable the receiver again.
       This way you don't receive your own transmitted data.<nl><nl>

       By default the receiver is enabled.
 @Also fos85.htm |  fossil_enable_transmitter | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x84<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void fossil_enable_receiver (int port, unsigned char mode)
{
    _DX = port;
    _AL = mode ;
    _AH = 0x84;                       // Service index
    asm { int FOSSILVECT  } ;
}
#endif

/******************************************************************************/
#ifdef _fos85_
/*
 @doc DOC_fos85_
 ---------------------------------------------------------------
 Enable/Disable transmitter.
 ---------------------------------------------------------------
 @clib  fossil_enable_transmitter | Enable/Disable transmitter |
        <cfont>void fossil_enable_transmitter ( int port, unsigned char mode );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  unsigned char  | mode  | Mode:<s2> FOS_DISABLE = 0, disable transmitter,<s2>
                                           FOS_ENABLE = 1, enable transmitter<ule>
 @rdesc None
 @comm  By default the transmitter is enabled.
 @Also  fos84.htm |  fossil_enable_receiver | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x85<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void fossil_enable_transmitter (int port, unsigned char mode)
{
    _DX = port;
    _AL = mode ;
    _AH = 0x85;                       // Service index
    asm { int FOSSILVECT  } ;
}
#endif


/******************************************************************************/
#ifdef _fos86_
/*
 @doc DOC_fos86_
 ---------------------------------------------------------------
 Force RTS
 ---------------------------------------------------------------
 @clib  fossil_force_rts | Force RTS# to low, high or reset to normal activity |
        <cfont>void fossil_force_rts ( int port, unsigned char mode );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  unsigned char  | mode  | Mode:<nl><ul>
                RTS_LOW = 0, force RTS to low<nl>
                RTS_HIGH = 1, force RTS to high<nl>
                RTS_NORMAL = 2, reset to normal activity<ule>
 @rdesc None
 @commtarget SC1x |  RTS/CTS flow control must be enabled to use this function.
 @Also  fos0F.htm | fossil_set_flowcontrol | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x86<linkmid>documentation<linktail>
        for more details.
 @target      SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     V1.20 | V1.20 | V1.20 | V1.05 | V1.00

 @target_clib V2.04
*/
void fossil_force_rts (int port, unsigned char mode)
{
    _DX = port;
    _AL = mode ;
    _AH = 0x86;                       // Service index
    asm { int FOSSILVECT  } ;
}
#endif


/******************************************************************************/
#ifdef _fos87_
/*
 @doc DOC_fos87_
 ---------------------------------------------------------------
 Read CTS
 ---------------------------------------------------------------
 @clib  fossil_read_cts | Read level on CTS# pin |
        <cfont>unsigned char fossil_read_cts ( int port );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc 0, CTS# is low<nl>
        1, CTS# is high<nl>
 @comm  RTS/CTS flow control must be enabled to use this function.
 @Also  fos0F.htm | fossil_set_flowcontrol | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140x87<linkmid>documentation<linktail>
        for more details.
 @target      SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     V1.20 | V1.20 | V1.20 | V1.05 | V1.00

 @target_clib V2.04
*/
unsigned char fossil_read_cts (int port)
{
    _DX = port;
    _AH = 0x87;                       // Service index
    asm { int FOSSILVECT  } ;
    return _AL;
}
#endif


/******************************************************************************/
#ifdef _fosA0_
/*
 @doc DOC_fosA0_
 ---------------------------------------------------------------
 Get Bytes in UART
 ---------------------------------------------------------------
 @clib  fossil_get_bytes_in_uart | Get number of bytes currently
        in UART hardware transmit buffers. |
        <cfont>int fossil_get_bytes_in_uart ( int port );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc Number of transmitter bytes in the UART, pending output<nl>
        -1 if UART transmitter is disabled (since SC1x version V1.20 and SC1x3 version V1.05)
 @comm  Returns the number of bytes which are currently in the UART
        hardware transmit buffers.<nl>
        <nl>
        With this function you can check how many bytes are currently stored at the
        internal UART transmit registers.<s2> This may be necessary to know if your communication pauses
        because of a handshake problem.<s2> If you want to know, how many bytes
        are stored at the fossil driver software transmit queue, you can use
        <linkto>fos1B.htm<linkmid>fossil_get_driver_info<linktail> function.<s2>
        However, fossil_get_driver_info does not check the UART transmit
        hardware buffers.
 @Also  fos1B.htm |  fossil_get_driver_info | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140xA0<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int fossil_get_bytes_in_uart (int port)
{
    _DX = port;
    _AH = 0xA0 ;                      // Service index
    asm { int FOSSILVECT  } ;
    return _AX ;
}
#endif


#ifdef _fosA5_
/*
 @doc DOC_fosA5_
 ---------------------------------------------------------------
 Output done
 ---------------------------------------------------------------
 @clib  fossil_output_done | Check if output buffer and transmitter are empty. |
        <cfont>int fossil_output_done ( int port );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc 0 = output buffer or transmitter is not empty<nl>
        1 = output buffer and transmitter are empty
 @Also  fos08.htm |  fossil_flush_output | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140xA5<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.27 | V1.27 | V1.27 | V1.45 | V1.45
 @target_clib V2.22
*/
int fossil_output_done (int port)
{
    _DX = port;
    _AH = 0xA5 ;                      // Service index
    asm { int FOSSILVECT  } ;
    return _AX ;
}
#endif


#ifdef _fosA6_
/*
 @doc DOC_fosA6_
 ---------------------------------------------------------------
 Data avail
 ---------------------------------------------------------------
 @clib  fossil_data_avail | Check if serial data bytes are available |
        <cfont>int fossil_data_avail ( int port );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @rdesc 0 = no data available<nl>
        1 = data is available
 @Also  fos0C.htm |  fossil_peek_input | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140xA6<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.27 | V1.27 | V1.27 | V1.45 | V1.45
 @target_clib V2.22
*/
int fossil_data_avail (int port)
{
    _DX = port;
    _AH = 0xA6 ;                      // Service index
    asm { int FOSSILVECT  } ;
    return _AX ;
}
#endif

/******************************************************************************/

/***************************************************************************/
//  Fossil User CallBack Event Data Structure
/***************************************************************************/
/*
 @doc DOC_FosUCBEvent_
 ---------------------------------------------------------------
 FossilUCBEvent
 ---------------------------------------------------------------
 @cstruc  Fossil User CallBack Event data structure | Fossil User CallBack Event |
        <cfont>
        typedef struct<nl>
        {<nl>
        <tab>int size;<s2><nl>
        <tab>int port;<s2><nl>
        <tab>int event;<s2><nl>
        <tab>void far *data;<s2><nl>
        <tab>unsigned data_length;<s2><nl>
        }  fossil_event_t ;<efont> | |
 @element int  | size  | Size of this struct (sizeof(fossil_event_t))
 @element int  | port  | Serial port:<nl><ul>
                <cfont>FOSSIL_EXT = 0<efont> for EXT port<nl>
                <cfont>FOSSIL_COM = 1<efont> for COM port<nl>
                <cfont>FOSSIL_SER2= 2<efont> for SER2 port (SC1x3/SC2x only)<nl>
                <cfont>FOSSIL_SER3= 3<efont> for SER3 port (SC1x3/SC2x only)<nl>
                <ule>
 @element int  | event  | Following events are possible:<nl>
        <ul>
        <cfont>FE_DATA_AVAIL<tab> 0x01<efont><s2> : New data received (in the data field)<nl>
        <cfont>FE_DATA_SENT<tab>&nbsp; 0x02<efont><s2> : New character placed to the UART shift register<nl>
        <cfont>FE_DATA_AVAIL9<tab>0x03<efont><s2> : New data received with 9. data bit set<nl>
        <cfont>FE_DATA_SENT9<tab> 0x04<efont><s2> : New character with 9. data bit set placed to the UART<nl>
        <tab><tab><tab><tab><tab><tab><tab><tab><tab><tab><tab><tab> shift register<nl>
        <cfont>FE_SENDQ_EMPTY<tab>0x05<efont><s2> : Data send queue is empty<nl>
        <cfont>FE_ERROR_DETECTED  0x10<efont><s2> : Data contains status information<nl>
        <ule>
 @element void*  | data  | Data pointer
 @element unsigned  | data_length  | Data length in bytes

 @comm  In case of event <cfont>FE_ERROR_DETECTED<efont> the first two bytes of
        the data buffer should be interpreted as an unsigned short int (16 bit)
        that contains status information. The third byte will hold the received char.
        The following bit positions are defined in the status information:<nl>
        <nl><ul>
          <cfont>Bit3=1<efont><s2> - Parity Error Detected<nl>
          <cfont>Bit5=1<efont><s2> - Framing Error Detected<nl>
          <cfont>Bit9=1<efont><s2> - Short Break Detected<nl>
          <cfont>Bit10=1<efont><s2>- Long Break Detected<nl>
        <ule>
        <nl>
        Also the callback function could return a fossil_event_struct.
        Then the returned struct contains an action event which the caller of the callback
        (the fossil interface) has to do.<nl>
        Following events are possible:<nl>
        <nl><ul>
        <cfont>FE_IGNORE_DATA<s2> 0x01<efont><s2> : do not copy the reveived data in the receive queue<nl>
        <ule><nl>
        If the callback does not return any event, the return value must be a null pointer (=0L).
 @Also  fosA1.htm |  Fossil User Callback Function | | | |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.25 | V1.25 | V1.25 | V1.81 | V1.81

*/
/******************************************************************************/
#ifdef _fosA1_
/*
 @doc DOC_fosA1_
 ---------------------------------------------------------------
 Install a Fossil User Callback Function
 ---------------------------------------------------------------
 @clib  fossil_user_callback | Install a Fossil User Callback Function.
        The User Callback function will be called when a fossil event occurs. |
        <cfont>void fossil_user_callback ( int port,<nl>
        <tab><tab><tab><tab><tab><tab><tab>FOSSIL_USER_CALLBACK pfFossUCB );<efont> |
 @parm  int | port | Port number:<nl>
        This can be either a numeric value or one of the following constants:<nl>
        <ul>
          <code>FOSSIL_EXT = 0<s1><codee> for the EXT (COM0) port (SC1x, SC1x3)<nl>
          <code>FOSSIL_COM = 1<s1><codee> for the COM (COM1) port (SC1x, SC1x3, SC2x)<nl>
          <code>FOSSIL_SER2 = 2<codee> for the COM2 port (SC1x3, SC2x)<nl>
          <code>FOSSIL_SER3 = 3<codee> for the COM3 port (SC1x3, SC2x)<nl>
        <ule><nl>
        Besides the numbers for the IPC@CHIP&reg;'s internal ports, a number of
        an external serial port can be passed if such a port is installed (see
        <linkto>fosA2.htm<linkmid>fossil_register_external_port<linktail>).
 @parm  FOSSIL_USER_CALLBACK  | pfFossUCB  | Pointer to Fossil User CallBack function
 @comm  This function installs a user callback function for the specified serial
        port. The callback function must be very short! Long fossil callback
        functions could lead to character losing. To use the fossil callback
        functions you have to switch the corresponding serial port into the IRQ
        Mode (see <linkto>../../config.htm#SERIAL_EXT_DMA<linkmid>CHIP.INI<linktail>).
        In DMA Mode the callback functions do not work!<nl>
        <nl>
        The callback function must be declared like the function below:<nl>
        <code><linkto>FosEvent.htm<linkmid>fossil_event_t<linktail>
        far *(huge my_fossil_callback)(<nl>
        <tab>fossil_event_t far *e )<codee><nl>
        <nl>
        The callback function must be installed like below:<nl>
        <code>fossil_user_callback( port,<nl>
        <tab8><tab8><s6>(FOSSIL_USER_CALLBACK)my_fossil_callback );<codee><nl>
        <nl>
        Note that only one user callback function can be installed per port.
        To uninstall a user callback function, simply call this function again
        with another function pointer or with a NULL pointer.
 @Also  FosEvent.htm | Fossil Event Data Structure | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140xA1<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void fossil_user_callback(int port, FOSSIL_USER_CALLBACK pfFossUCB)
{
    asm { LES  DI, pfFossUCB } ;   // ES:DI = far ptr to the User Callback function
    _DX = port;
    _AH = 0xA1 ;                   // Service index
    asm { int FOSSILVECT  } ;
}
#endif


#ifdef _fosA2_
// This variable stores the callback funtions the user driver has registered.
static FossilExternalPortCallbacks *gCallbacks;
unsigned short gCallbacksVers;

/*
 * This function is registered as the external port callback function by
 * fossil_register_external_port(). It switches to the several callback function
 * the user driver provides to fossil_register_external_port() and which are
 * stored in the variable gCallbacks.
 */
unsigned huge fossil_external_port_callback(unsigned ax, unsigned bx, unsigned cx,
                                            unsigned dx, unsigned es, unsigned di)
{
  // AH and AL register
  unsigned char ah, al;
  // Baudrates used by service 0x14, 0x00
  unsigned short standardBaudrates[] = { 19200U, 38400U, 300U, 600U, 1200U,
                                         2400U, 4800U, 9600U };
  // Parities used by service 0x14, 0x00
  FOSSIL_PARITY standardParities[] = { FOSSIL_PARITY_NO, FOSSIL_PARITY_ODD,
                                       FOSSIL_PARITY_NO, FOSSIL_PARITY_EVEN };
  // Baudrates used by service 0x14, 0x1E
  unsigned long extendedStandardBaudrates[] = { 110UL, 150UL, 300UL, 600UL,
                                                1200UL, 2400UL, 4800UL, 9600UL,
                                                19200UL, 28800UL, 38400UL,
                                                57600UL, 76800UL, 115200UL };
  // Index of the above baudrates array
  unsigned char baudrateIndex;


  ah = (unsigned char)(ax >> 8);
  al = (unsigned char)ax;


  // Dispatch to the several user functions depending on AH register
  switch(ah)
  {
    case 0x01:  // putbyte_wait()
      if(gCallbacks->putbyte_wait)
      {
        // Software interrupt expects result in ah
        return ((unsigned int)gCallbacks->putbyte_wait(dx, al) << 8);
      }
      break;

    case 0x02:  // getbyte_wait()
      if(gCallbacks->getbyte_wait)
        return gCallbacks->getbyte_wait(dx);
      break;

    case 0x03:  // status_request()
      if(gCallbacks->status_request)
      {
        // Software interrupt expects result in ah
        return ((unsigned int)gCallbacks->status_request(dx) << 8);
      }
      break;

    case 0x04:  // init()
      if(gCallbacks->init)
        return gCallbacks->init(dx);
      break;

    case 0x05:  // deinit()
      if(gCallbacks->deinit)
      {
        gCallbacks->deinit(dx);
        return 0;
      }
      break;

    case 0x08:  // flush_output()
      if(gCallbacks->flush_output)
      {
        gCallbacks->flush_output(dx);
        return 0;
      }
      break;

    case 0x09:  // purge_output()
      if(gCallbacks->purge_output)
      {
        gCallbacks->purge_output(dx);
        return 0;
      }
      break;

    case 0x0A:  // purge_input()
      if(gCallbacks->purge_input)
      {
        gCallbacks->purge_input(dx);
        return 0;
      }
      break;

    case 0x0B:  // putbyte()
      if(gCallbacks->putbyte)
        return gCallbacks->putbyte(dx, al);
      break;

    case 0x0C:  // peek_input()
      if(gCallbacks->peek_input)
        return gCallbacks->peek_input(dx);
      break;

    case 0x0F:  // set_flowcontrol()
      if(gCallbacks->set_flowcontrol)
      {
        gCallbacks->set_flowcontrol(dx, al);
        return 0;
      }
      break;

    case 0x18:  // readblock()
      if(gCallbacks->readblock)
        return gCallbacks->readblock(dx, MK_FP(es, di), cx);
      break;

    case 0x19:  // writeblock()
      if(gCallbacks->writeblock)
        return gCallbacks->writeblock(dx, MK_FP(es, di), cx);
      break;

    case 0x1B:  // get_driver_info()
      if(gCallbacks->get_driver_info)
        return gCallbacks->get_driver_info(dx, MK_FP(es, di));
      break;

    case 0x80:  // set_rs485()
      if(gCallbacks->set_rs485)
      {
        gCallbacks->set_rs485(dx, al);
        return 0;
      }
      break;

    case 0x82:  // set_rs485_txenable()
      if(gCallbacks->set_rs485_txenable)
      {
        gCallbacks->set_rs485_txenable(dx, al);
        return 0;
      }
      break;

    case 0x83:  // send_break()
      if(gCallbacks->send_break)
      {
        gCallbacks->send_break(dx, al);
        return 0;
      }
      break;

    case 0x84: // enable_receiver()
      if(gCallbacks->enable_receiver)
      {
        gCallbacks->enable_receiver(dx, al);
        return 0;
      }
      break;

    case 0x85:  // enable_transmitter()
      if(gCallbacks->enable_transmitter)
      {
        gCallbacks->enable_transmitter(dx, al);
        return 0;
      }
      break;

    case 0x86:  // force_rts()
      if(gCallbacks->force_rts)
      {
        gCallbacks->force_rts(dx, al);
        return 0;
      }
      break;

    case 0x87:  // read_cts()
      if(gCallbacks->read_cts)
        return gCallbacks->read_cts(dx);
      break;

    case 0xA0:  // get_bytes_in_uart()
      if(gCallbacks->get_bytes_in_uart)
        return gCallbacks->get_bytes_in_uart(dx);
      break;

    case 0xA1:  // user_callback()
      if(gCallbacks->user_callback)
      {
        gCallbacks->user_callback(dx, (FOSSIL_USER_CALLBACK)MK_FP(es, di));
        return 0;
      }
      break;

    /*
     * Setting baudrate, etc.
     * This is a little bit tricky. The external serial port driver must
     * implement two functions for this. setbaud() is handed the baudrate while
     * set_ext_ctrl() is handed a baud rate devider. The software interrupt
     * services 0x00, 0x1E, 0x81 and 0xA4 are mapped to these two functions.
     */
    case 0x00:  // Baudrate, etc. encoded in al
      if(gCallbacks->setbaud)
      {
        return gCallbacks->setbaud(dx, standardBaudrates[al >> 5],
                                   standardParities[(al >> 3) & 0x03],
                                   (al & 0x01) ? 8 : 7, ((al >> 2) & 0x01) + 1);
      }
      break;

    case 0x1E:  // Standard baud rates selected via cl
      if(gCallbacks->setbaud)
      {
        baudrateIndex = (unsigned char)cx;
        if(baudrateIndex & 0x80)
          baudrateIndex = (baudrateIndex & 0x7F) + 9;
        if(baudrateIndex >= sizeof(extendedStandardBaudrates)
                            / sizeof(extendedStandardBaudrates[0]))
        {
          return 0;
        }

        gCallbacks->setbaud(dx, extendedStandardBaudrates[baudrateIndex],
                            bx >> 8, (cx >> 8) + 5, (bx & 0x00FF) + 1);
        return 0;
      }
      break;

    case 0x81:  // Baudrate via divider
      if(gCallbacks->set_extctrl)
      {
        gCallbacks->set_extctrl(dx, cx, (bx >> 8), al + 5, (bx & 0x00FF) + 1);
        return 0;
      }
      break;
      
    case 0xA4: // Real setbaud
      if(gCallbacks->set_extctrl)
      {
        return gCallbacks->setbaud(dx,
                                   (((unsigned long)bx) << 16) + (unsigned long)cx,
                                   al & 0x0F, ((al >> 4) & 0x03) + 7,
                                   ((al >> 6) & 0x03) + 1);
      }
      break;

    case 0xA5: // V2 - Output done
      if ( (gCallbacksVers >= 2) && (gCallbacks->output_done) )
      {
        return gCallbacks->output_done(dx);
      }
      break;

    case 0xA6: // V2 - Data avail done
      if ( (gCallbacksVers >= 2) && (gCallbacks->data_avail) )
      {
        return gCallbacks->data_avail(dx);
      }
      break;

  }

  // Unsupported interrupt - notify driver
  return gCallbacks->unsupported_interrupt(ax, bx, cx, dx, es, di);
}


/*
 @doc DOC_FosExtCB_
 ---------------------------------------------------------------
 FossilExternalPortCallbacks
 ---------------------------------------------------------------
 @cstruc FossilExternalPortCallbacks data structure |
         Structure holding pointers to callback functions to be registered in
         conjunction with an external port |
         <cfont>
         typedef struct<nl>
         {<nl>
         <s2>int<tab8><s2> (far *init)(int port);<nl>
         <s2>void<tab8><s1> (far *deinit)(short port);<nl>
         <s2>int<tab8><s2> (far *setbaud)(int port, long baudrate, int parity,<nl>
         <tab8><tab8><tab8><tab><s2> int wordlen, int stopbits);<nl>
         <s2>void<tab8><s1> (far *set_extctrl)(int port, int baud_divider,<nl>
         <tab8><tab8><tab8><tab8><s2> FOSSIL_PARITY parity, int wordlen,<nl>
         <tab8><tab8><tab8><tab8><s2> int stopbits);<nl>
         <s2>void<tab8><s1> (far *set_flowcontrol)(int port, FOS_FLOW_CTRL flowctrl);<nl>
         <s2>void<tab8><s1> (far *force_rts)(int port, unsigned char mode);<nl>
         <s2>unsigned char (far *read_cts)(int port);<nl>
         <s2>void<tab8><s1> (far *user_callback)(int port,<nl>
         <tab8><tab8><tab8><tab8><tab> FOSSIL_USER_CALLBACK pfFossUCB);<nl>
         <s2>int<tab8><s2> (far *status_request)(int port);<nl>
         <s2>int<tab8><s2> (far *get_driver_info)(int port,<nl>
         <tab8><tab8><tab8><tab8><tab><s1> FossilDriverInfo_t far *drv_info);<nl>
         <s2>int<tab8><s2> (far *get_bytes_in_uart)(int port);<nl>
         <s2>void<tab8><s1> (far *set_rs485)(int port, RS485_MODE mode);<nl>
         <s2>void<tab8><s1> (far *set_rs485_txenable)(int port, int pin);<nl>
         <s2>int<tab8><s2> (far *putbyte_wait)(int port, int ch);<nl>
         <s2>int<tab8><s2> (far *putbyte)(int port, int ch);<nl>
         <s2>unsigned int<s1> (far *writeblock)(int port,<nl>
         <tab8><tab8><tab8><tab8><s1> const unsigned char far *buffer,<nl>
         <tab8><tab8><tab8><tab8><s1> unsigned int count);<nl>
         <s2>void<tab8><s1> (far *flush_output)(int port);<nl>
         <s2>void<tab8><s1> (far *purge_output)(int port);<nl>
         <s2>void<tab8><s1> (far *send_break)(int port, FOS_BREAK_SIZE break_size);<nl>
         <s2>void<tab8><s1> (far *enable_transmitter)(int port, unsigned char mode);<nl>
         <s2>int<tab8><s2> (far *getbyte_wait)(int port);<nl>
         <s2>int<tab8><s2> (far *peek_input)(int port);<nl>
         <s2>unsigned int<s1> (far *readblock)(int port, unsigned char far *buffer,<nl>
         <tab8><tab8><tab8><tab8> unsigned int count);<nl>
         <s2>void<tab8><s1> (far *purge_input)(int port);<nl>
         <s2>void<tab8><s1> (far *enable_receiver)(int port, unsigned char mode);<nl>
         <s2>unsigned int<s1> (far *unsupported_interrupt)(unsigned ax, unsigned bx,<nl>
         <tab8><tab8><tab8><tab8><tab8><tab> unsigned cx, unsigned dx,<nl>
         <tab8><tab8><tab8><tab8><tab8><tab> unsigned es, unsigned di);<nl>
         <nl><s2>// V2 members<nl>
         <s2>int<tab8><s2> (far *output_done)(int port);<nl>
         <s2>int<tab8><s2> (far *data_avail)(int port);<nl>
         } FossilExternalPortCallbacks;<efont> | |
 @element   void * | init | Pointer to function that will be called when
            <linkto>fos04.htm<linkmid>fossil_init<linktail> is
            called for the external port.
 @element   void * | deinit | Pointer to function that will be called when
            <linkto>fos05.htm<linkmid>fossil_deinit<linktail> is
            called for the external port.
 @element   void * | setbaud | Pointer to function that will be called when
            <linkto>fosA4.htm<linkmid>fossil_setbaud<linktail>
            or <linkto>fos00.htm<linkmid>fossil_setbaud_std<linktail>
            are called for the external port. Depending on the configuration
            values a call to <cfont>fossil_setbaud<efont> might also trigger the
            <cfont>set_extctrl<efont> callback function.
 @element   void * | set_extctrl | Pointer to function that will be called when
            <linkto>fos81.htm<linkmid>fossil_set_extctrl<linktail>
            is called for the external port. A call to
            <linkto>fosA4.htm<linkmid>fossil_setbaud<linktail>
            for the external port may also trigger this callback function,
            depending on the configuration values.
 @element   void * | set_flowcontrol | Pointer to function that will be called when
            <linkto>fos0F.htm<linkmid>fossil_set_flowcontrol<linktail>
            is called for the external port.
 @element   void * | force_rts | Pointer to function that will be called when
            <linkto>fos86.htm<linkmid>fossil_force_rts<linktail>
            is called for the external port.
 @element   void * | read_cts | Pointer to function that will be called when
            <linkto>fos87.htm<linkmid>fossil_read_cts<linktail>
            is called for the external port.
 @element   void * | user_callback | Pointer to function that will be called when
            <linkto>fosA1.htm<linkmid>fossil_user_callback<linktail>
            is called for the external port. Note that your driver program must
            manage storing and calling the user callback function on its own.
            The RTOS doesn't handle this for external ports.
 @element   void * | status_request | Pointer to function that will be called when
            <linkto>fos03.htm<linkmid>fossil_status_request<linktail>
            is called for the external port.
 @element   void * | get_driver_info | Pointer to function that will be called when
            <linkto>fos1B.htm<linkmid>fossil_get_driver_info<linktail>
            is called for the external port.
 @element   void * | get_bytes_in_uart | Pointer to function that will be called when
            <linkto>fosA0.htm<linkmid>fossil_get_bytes_in_uart<linktail>
            is called for the external port.
 @element   void * | set_rs485 | Pointer to function that will be called when
            <linkto>fos80.htm<linkmid>fossil_set_rs485<linktail>
            is called for the external port.
 @element   void * | set_rs485_txenable | Pointer to function that will be called when
            <linkto>fos82.htm<linkmid>fossil_set_rs485_txenable<linktail>
            is called for the external port.
 @element   void * | putbyte_wait | Pointer to function that will be called when
            <linkto>fos01.htm<linkmid>fossil_putbyte_wait<linktail>
            is called for the external port.
 @element   void * | putbyte | Pointer to function that will be called when
            <linkto>fos0B.htm<linkmid>fossil_putbyte<linktail>
            is called for the external port.
 @element   void * | writeblock | Pointer to function that will be called when
            <linkto>fos19.htm<linkmid>fossil_writeblock<linktail>
            is called for the external port.
 @element   void * | flush_output | Pointer to function that will be called when
            <linkto>fos08.htm<linkmid>fossil_flush_output<linktail>
            is called for the external port.
 @element   void * | purge_output | Pointer to function that will be called when
            <linkto>fos09.htm<linkmid>fossil_purge_output<linktail>
            is called for the external port.
 @element   void * | send_break | Pointer to function that will be called when
            <linkto>fos83.htm<linkmid>fossil_send_break<linktail>
            is called for the external port.
 @element   void * | enable_transmitter | Pointer to function that will be called when
            <linkto>fos85.htm<linkmid>fossil_enable_transmitter<linktail>
            is called for the external port.
 @element   void * | getbyte_wait | Pointer to function that will be called when
            <linkto>fos02.htm<linkmid>fossil_getbyte_wait<linktail>
            is called for the external port.
 @element   void * | peek_input | Pointer to function that will be called when
            <linkto>fos0C.htm<linkmid>fossil_peek_input<linktail>
            is called for the external port.
 @element   void * | readblock | Pointer to function that will be called when
            <linkto>fos18.htm<linkmid>fossil_readblock<linktail>
            is called for the external port.
 @element   void * | purge_input | Pointer to function that will be called when
            <linkto>fos0A.htm<linkmid>fossil_purge_input<linktail>
            is called for the external port.
 @element   void * | enable_receiver | Pointer to function that will be called when
            <linkto>fos84.htm<linkmid>fossil_enable_receiver<linktail>
            is called for the external port.
 @element   void * | unsupported_interrupt | Pointer to function that will be
            called when no specific callback function is registered for a
            fossil software interrupt. This might be the case if either one of
            the above callback function pointers is set to NULL or an invalid
            software interrupt has been called or the fossil API has been
            extended since the external port driver was compiled.<nl>
            The arguments passed to this calback function match the registers
            used for the RTOS' software interrupt interface.
 @element   int | output_done | Pointer to function that will be called when
            <linkto>fosA5.htm<linkmid>fossil_output_done<linktail>
            is called for the external port. <bold>Note:<bolde> This is a V2 member
            of this structure. The callbacks must be installed with
            fossil_register_external_port_ext() and <i>version<ie> set to 2
            to support this function.
 @element   int | data_avail | Pointer to function that will be called when
            <linkto>fosA6.htm<linkmid>fossil_data_avail<linktail>
            is called for the external port. <bold>Note:<bolde> This is a V2 member
            of this structure. The callbacks must be installed with
            fossil_register_external_port_ext() and <i>version<ie> set to 2
            to support this function.

 @comm      When implementing the callback functions make sure they exactly
            match the documentation of the corresponding <cfont>fossil_*<efont>
            functions. Not doing so may result in incompatibility with newer
            RTOS versions.<nl>
            At least the callback function <cfont>unsupported_interrupt<efont>
            must be implemented. All other callback function pointers can
            optionally be set to <cfont>NULL<efont>. If such a function is
            triggered by one of the <cfont>fossil_*<efont> API functions, the
            <cfont>unsupported_interrupt<efont> callback function will be called
            instead. This callback function is also called when an unknown
            software interrupt function is triggered. This might happen for
            example if your external port driver runs on an RTOS version which
            knows of more fossil API functions than the CLIB you compiled your
            driver against did.<nl>
            <nl>
            Note that there are no callback counterparts for the API functions
            <cfont>fossil_setbaud_std<efont> and <cfont>fossil_getbyte<efont>,
            since these are mapped to other functions internally. Of course
            there are also no callback counterparts for the API functions
            <cfont>fossil_register_external_port<efont> and
            <cfont>fossil_unregister_external_port<efont>.
 @Also  fosA2.htm |  fossil_register_external_port | | | |


 @doc DOC_fosA2_
 ---------------------------------------------------------------
 Register an external port
 ---------------------------------------------------------------
 @clib       fossil_register_external_port |
             This function registers an external port, i.e. a serial port which
             is handled by an external driver program. The driver program must
             provide several callback functions, which are called when another
             program accesses the assigned port number.<nl>
             This mechanism can be used to integrate additional real serial
             ports (additional UART hardware) or virtual serial ports, which are
             for example forwarded via USB, into the RTOS. |
             <cfont>short fossil_register_external_port ( short port,<nl>
             <tab8><tab8><tab8><tab8><tab><s2>FossilExternalPortCallbacks<nl>
             <tab8><tab8><tab8><tab8><tab8>*callbacks );<efont> |
 @parm  short | port |
        Designated port number, -1 if an arbitrary port number is to be assigned
 @parm  FossilExternalPortCallbacks * | callbacks |
        Pointer to structure holding pointers to the several callback functions.
        For details see
        <linkto>FosExtCB.htm<linkmid>FossilExternalPortCallbacks<linktail>.
 @rdesc On success, port number assigned to the external port driver<nl>
        -1, if the designated port number is not free or belongs to one the the
        RTOS' standard serial ports<nl>
        -2, if the maximum number of external port drivers has already been
        registered.<nl>
        -3, if either the argument <cfont>callbacks<efont> or
        <cfont>callbacks->unsupported_interrupt<efont> is NULL
 @ex    The following example shows how to register an external port driver.
        It is assumed that the callback functions are named
        <cfont>myFossil_*<efont>. |
int myFossil_init(int port)
{
  ... // Implementation
}

... // Other callback functions

unsigned int myUnsupported_interrupt(unsigned ax, unsigned bx, unsigned cx,
                                     unsigned dx, unsigned es, unsigned di)
{
  ... // Implementation
}

void main(void)
{
  FossilExternalPortCallbacks callbacks;
  short portNumber;
  ...

  callbacks.init = myFossil_init;
  ... // Other callback functions
  callbacks.set_rs485 = NULL;  // Unimplemented function
  callbacks.unsupported_interrupt = myUnsupported_interrupt;

  portNumber = fossil_register_external_port(-1, &callbacks);
  if(portNumber < 0)
    ...  // Error handling

  ... // Program runs

  portNumber = fossil_unregister_external_port(portNumber);
  if(portNumber < 0)
    ...  // Error handling
}
 @Also  FosA3.htm | fossil_unregister_external_port | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140xA2<linkmid>documentation<linktail>
        for more details.<nl>
        Please do not use the software interrupt version of this function
        directly, since parts of the functionality are implemented within the
        C-library.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.20 | V1.20
 @target_clib V2.13
*/
short fossil_register_external_port(short port, FossilExternalPortCallbacks *callbacks)
{
  short result;  // Result of the software interrupt


  // Check arguments
  if(!callbacks || !callbacks->unsupported_interrupt)
    return -3;

  // Call software interrupt
  asm mov ax, seg fossil_external_port_callback
  asm mov es, ax
  asm mov di, offset fossil_external_port_callback
  _DX = port;
  _AH = 0xA2;
  asm int FOSSILVECT
  result = _AX;

  // Store callback functions
  if(result > 0)
    gCallbacks = callbacks;

  return result;
}
#endif


#ifdef _fosA2_ext_
extern unsigned short gCallbacksVers;

/*
 @doc DOC_fosA2_ext_
 ---------------------------------------------------------------
 Register an external port (extented)
 ---------------------------------------------------------------
 @clib       fossil_register_external_port_ext |
             This function registers an external port, i.e. a serial port which
             is handled by an external driver program. The driver program must
             provide several callback functions, which are called when another
             program accesses the assigned port number.<nl>
             This mechanism can be used to integrate additional real serial
             ports (additional UART hardware) or virtual serial ports, which are
             for example forwarded via USB, into the RTOS. |
             <cfont>short fossil_register_external_port_ext ( short port,<nl>
             <tab8><tab8><tab8><tab8><tab><tab><s2>FossilExternalPortCallbacks<nl>
             <tab8><tab8><tab8><tab8><tab><tab8>*callbacks,
             <tab8><tab8><tab8><tab8><tab><tab><s2>version,<nl>);<efont> |
 @parm  short | port |
        Designated port number, -1 if an arbitrary port number is to be assigned
 @parm  FossilExternalPortCallbacks * | callbacks |
        Pointer to structure holding pointers to the several callback functions.
        For details see
        <linkto>FosExtCB.htm<linkmid>FossilExternalPortCallbacks<linktail>.
 @parm  unsigned short | version |
        Structure version, set to 2 to support V2 members
 @rdesc On success, port number assigned to the external port driver<nl>
        -1, if the designated port number is not free or belongs to one the the
        RTOS' standard serial ports<nl>
        -2, if the maximum number of external port drivers has already been
        registered.<nl>
        -3, if either the argument <cfont>callbacks<efont> or
        <cfont>callbacks->unsupported_interrupt<efont> is NULL
 @Also  FosA2.htm | fossil_register_external_port | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140xA2<linkmid>documentation<linktail>
        for more details.<nl>
        Please do not use the software interrupt version of this function
        directly, since parts of the functionality are implemented within the
        C-library.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.45 | V1.45
 @target_clib V2.22
*/
short fossil_register_external_port_ext(short port,
                                        FossilExternalPortCallbacks *callbacks,
                                        unsigned short version)
{
  gCallbacksVers = version;
  return fossil_register_external_port(port, callbacks);
}
#endif

#ifdef _fosA3_
/*
 @doc DOC_fosA3_
 ---------------------------------------------------------------
 Unregister an external port
 ---------------------------------------------------------------
 @clib       fossil_unregister_external_port |
             This function unregisters an external port. |
             <cfont>short fossil_unregister_external_port ( short port );<efont> |
 @parm  short | port |
        Number of the external port
 @rdesc 0 on success<nl>
        -1, if no external port has been registered under the given number
 @Also  FosA2.htm | fossil_register_external_port | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../fossil.htm#0x140xA3<linkmid>documentation<linktail>
        for more details.<nl>
        Please do not use the software interrupt version of this function
        directly, since parts of the functionality are implemented within the
        C-library.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.20 | V1.20
 @target_clib V2.13
*/
short fossil_unregister_external_port(short port)
{
  _DX = port;
  _AH = 0xA3;
  asm int FOSSILVECT
  return _AX;
}
#endif

/****************************************************************************/
// end of file
/****************************************************************************/


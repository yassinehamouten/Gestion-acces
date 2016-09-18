/****************************************************************************
* (C) 1999-2011 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module        : I2C_API.C
* Function      : I2C API Library
* ---------------------------------------------------------------------------
* History       :
*  Vx.yy                   Author  Changes
*  V1.00      17.07.00     roth    Create
* ---------------------------------------------------------------------------
*  Published on the BECK WebSite with kind permission of Bernhard Roth.

$Header: I2C_API.C, 33, 12.11.2008 12:51:04, Andre Pribil$

****************************************************************************/



/****************************************************************************/
//includes
/****************************************************************************/

#include <dos.h>
#include <config.h>
#include <common.h>
#include <I2C_API.H>
#include "I2C_priv.H"
#include <hwAPI.H>
#include <rtos.h>

/*
 @doc DOC_INDEX
 ---------------------------------------------------------------
 I2C API Table of Contents
 ---------------------------------------------------------------
 @clibidx  <tab><cfont>#include <InBraces I2C_API\.H><efont> |
    <tab><linkto>#Control<linkmid>Control<linktail><tab>
    <linkto>#Transmit<linkmid>Transmit<linktail><tab>
    <linkto>#Receive<linkmid>Receive<linktail><tab>

 Here is the CLIB API for access to the IPC@CHIP&reg;'s I2C bus.<nl>

 Philips was the inventor of the Inter-IC or I²C-bus, and it is now firmly
 established as the worldwide de-facto solution for embedded applications.
 It is used extensively in a variety of microcontroller-based professional,
 consumer and telecommunications applications as a control, diagnostic and
 power management bus. As a two-wire serial bus, its inherently simple
 operation was crucial to its emergence as the worldwide de-facto standard.<nl>

 @libcat1  Control   | i2c80 | I2C_init                | I2C Master: Initialize the I2C Bus |
 @libcat1  Control   | i2c81 | I2C_scan                | I2C Master: Scan for I2C slave devices |
 @libcat1  Control   | i2c85 | I2C_scan_ext            | I2C Master: Scan for I2C slave devices (extended address)|
 @libcat1  Control   | i2c84 | I2C_release             | I2C Master: Release I2C bus |
 @libcat1  Control   | i2c8b | I2C_restart             | I2C Master: Restart I2C |
 @libcat1  Control   | i2c8e | I2C_select_clock_pin    | I2C Master: Select I2C Clock Pin |
 @libcat1  Control   | i2c8f | I2C_select_data_pin     | I2C Master: Select I2C Data Pin |
 @libcat1  Control   | i2cb0 | I2C_set_speed           | I2C Master/Slave: Select I2C bus speed |
 @libcat1  Control   | i2cb1 | I2C_reset               | I2C Master/Slave: Reset I2C bus controller |
 @libcat1  Control   | i2c88 | I2C_set_timeout         | I2C Master: Set I2C bus timeout |
 @libcat1  Control   | i2cb8 | I2C_bus_reset           | I2C Master: Reset I2C bus by clock transitions |


 @libcat2  Transmit  | i2c82t | I2C_transmit_char      | I2C Master: Send a single character |
 @libcat2  Transmit  | i2c83t | I2C_transmit_block     | I2C Master: Send a block of characters |
 @libcat2  Transmit  | i2c86t | I2C_transmit_char_ext  | I2C Master: Send a single character (extended address)|
 @libcat2  Transmit  | i2c87t | I2C_transmit_block_ext | I2C Master: Send a block of characters (extended address)|

 @libcat3  Receive   | i2c82r | I2C_receive_char       | I2C Master: Receive a single character |
 @libcat3  Receive   | i2c83r | I2C_receive_block      | I2C Master: Receive block of characters |
 @libcat3  Receive   | i2c86r | I2C_receive_char_ext   | I2C Master: Receive a single character (extended address)|
 @libcat3  Receive   | i2c87r | I2C_receive_block_ext  | I2C Master: Receive block of characters (extended address) |

 @libcat4  Slave     | i2cb2 | I2C_slave_address       | I2C Slave: Set I2C bus slave address |
 @libcat4  Slave     | i2cb3 | I2C_slave_getstate      | I2C Slave: Get I2C bus state |
 @libcat4  Slave     | i2cb4 | I2C_slave_sendack       | I2C Slave: Send a I2C bus acknowledge |
 @libcat4  Slave     | i2cb5 | I2C_slave_readbyte      | I2C Slave: Read byte from I2C bus |
 @libcat4  Slave     | i2cb6 | I2C_slave_sendbyte      | I2C Slave: Send byte to I2C bus |
 @libcat4  Slave     | i2cb7 | I2C_slave_idle          | I2C Slave: Set the I2C internal state back to idle |
*/


/*************************************************************************/
//Init the I2C Interface
/*************************************************************************/
#ifdef _i2c80_
/*
 @doc DOC_i2c80_
 ---------------------------------------------------------------
 I2C init I2C-function
 ---------------------------------------------------------------
 @clib  I2C_init | Initialize the I2C Bus |
        <cfont>void I2C_init ( void );<efont> |
 @parm  byte |  | -- none --
 @rdesc -- none --
 @comm  This function configures two of the
        programmable I/O (PIO) pins for usage as I2C bus data and clock signals.<nl><nl>
        The user can specify which two PIO are used for I2C
        <linkto>i2c8e.htm<linkmid>clock<linktail> and <linkto>i2c8f.htm<linkmid>data<linktail>.<s2>
        After calling this initialization function, these two pins will no longer be available
        as PIO pins unless the <linkto>../../hardware.htm#0xA20x82<linkmid>PFE Enable<linktail> function
        is called for these pins following this function call.
 @commtarget SC1x3/SC2x | On SC1x3/SC2x the default is to use the hardware I2C interface on the dedicated pins.
        If the user calls functions 8eh and 8fh to select other PIOs for the bus, the I2C bus will be
        software emulated on the selected PIO pins.<nl>
        <nl>
        If the hardware interface is used, the calling task will go to sleep,
        until the I2C interrupt issues a wakeup. Therefore the user should not
        make own wakeup calls to the I2C API calling task, while sleeping inside
        I2C functions.

 @Also  i2c8e.htm | I2C_select_clock_pin |
        i2c8f.htm | I2C_select_data_pin  | |
 @Related PFE:  | ../../hardware.htm#0xA20x82 | Enable | Programmable I/O Pins
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x80<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void I2C_init (void)
{
    _AH = I2C_INIT ;
    asm { int I2CINT  } ;
}
#endif

/*************************************************************************/
//Scan for interfaces on I2C
/*************************************************************************/
#ifdef _i2c81_
/*
 @doc DOC_i2c81_
 ---------------------------------------------------------------
 I2C scan I2C-devices
 ---------------------------------------------------------------
 @clib  I2C_scan | Scan for I2C slave devices |
        <cfont>unsigned char I2C_scan ( unsigned char start_addr,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned char end_addr ); <efont> |
 @parm  byte | start_addr  | First slave address (even address, LSB=0)
 @parm  byte | end_addr  | Last slave address (even address, LSB=0)
 @rdesc 0 =<gt> no slave found<nl>
        Non-zero =<gt> address of the first slaved device found <nl>
 @comm  This is an iterator function which is called repetitively to determine
        all connected slaves.<s2> Specify on each successive call a new restricted
        slave address range until no further address is returned by this function.<s2>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x81<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned char I2C_scan (unsigned char start_addr, unsigned char end_addr)
{
    _CL = end_addr ;
    _AL = start_addr ;
    _AH = I2C_SCAN ;
    asm { int I2CINT  } ;
    return _AL ;
}
#endif


/*************************************************************************/
//Scan for interfaces on I2C (extended address)
/*************************************************************************/
#ifdef _i2c85_
/*
 @doc DOC_i2c85_
 ---------------------------------------------------------------
 I2C scan I2C-devices (extended address)
 ---------------------------------------------------------------
 @clib  I2C_scan_ext | Scan for I2C slave devices (extended address)|
        <cfont>unsigned int I2C_scan_ext ( unsigned int start_addr,<nl>
        <tab><tab><tab><tab><tab><tab><tab> unsigned int end_addr ); <efont> |
 @parm  word | start_addr  | First slave address (even address, LSB=0)
 @parm  word | end_addr  | Last slave address (even address, LSB=0)
 @rdesc 0 =<gt> no slave found<nl>
        Non-zero =<gt> address of the first slaved device found <nl>
 @comm  This is an iterator function which is called repetitively to determine
        all connected slaves.<s2> Specify on each successive call a new restricted
        slave address range until no further address is returned by this function.<s2>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x85<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V0.90 | V1.00

 @target_clib V2.01
*/
unsigned int I2C_scan_ext (unsigned int start_addr, unsigned int end_addr)
{
    _CX = end_addr ;
    _DX = start_addr ;
    _AH = I2C_SCAN_EXT ;
    asm { int I2CINT  } ;
    return _AX ;
}
#endif

/*************************************************************************/
//Receive one Character
/*************************************************************************/
#ifdef _i2c82r_
/*
@doc DOC_i2c82r_
 ---------------------------------------------------------------
  I2C receive character
 ---------------------------------------------------------------
 @clib  I2C_receive_char | Receive a single character |
        <cfont>int I2C_receive_char ( unsigned char slave,<nl>
        <tab><tab><tab><tab><tab>&nbsp;&nbsp; char far *char_in,<nl>
        <tab><tab><tab><tab><tab>&nbsp;&nbsp; unsigned char not_last );<efont> |
 @parm  byte | slave  | 7 bit slave address in B7-B1, B0=Don't care
 @parm  byte | char_in  | Pointer to one character buffer provided by caller where
        received character will be placed.
 @parm  byte | not_last  | = 0 for last char to be received, otherwise non-zero. <nl>
 @rdesc 0: Success, received char is output to 'char_in' location.<nl>
        8: Timeout<nl>
        9: Slave faulty or not available<ule>
 @rdesc_sc1x3_sc2x
         On SC1x3/SC2x these additional return values are possible
         if the hardware I2C interface is used:<nl>
         3: Arbitration lost, general call address received<nl>
         4: Arbitration lost, own slave address received,
            master wants to read<nl> (change from master to slave)<nl>
         5: Arbitration lost, own slave address received,
            master wants to write<nl> (change from master to slave)<nl>
         6: Arbitration lost<nl>
         7: Bus error<nl>
 @comm  The IPC@CHIP&reg; is the I2C bus master.<nl><nl>
        This function will automatically generated a I2C Start or Restart
        condition.
 @Also  i2c83r.htm |  I2C_receive_block |
        i2c82t.htm |  I2C_transmit_char | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x82<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int I2C_receive_char (unsigned char slave,
                      char *char_in,
                      unsigned char not_last)
{
    unsigned char  flags;
    unsigned char result ;
    char the_char ;

    _CL = not_last ;         // = 0 if last char.
    _AX = (I2C_TRANS_RECV_CHAR << 8) | 0x01 | (unsigned)slave  ;
    asm {
      int I2CINT
      lahf
    } ;
    flags    = _AH ;    // Before they gets lost.
    result   = _AL ;
    the_char = _CH ;

    if (flags & CARRY_FLAG)
    {
        the_char = 0 ;
    }
    else
    {
        result = 0 ;
    }

    *char_in = the_char ;               // Set output parameter
    return (int) ((unsigned int) result) ;
}
#endif

/*************************************************************************/
//Receive one Character (extended address)
/*************************************************************************/
#ifdef _i2c86r_
/*
@doc DOC_i2c86r_
 ---------------------------------------------------------------
  I2C receive character (extended address)
 ---------------------------------------------------------------
 @clib  I2C_receive_char_ext | Receive a single character (extended address)|
        <cfont>int I2C_receive_char_ext ( unsigned int slave,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; char far *char_in,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; unsigned char not_last );<efont> |
 @parm  word | slave  | 10 bit slave address in B10-B1, B0=Don't care
 @parm  byte | char_in  | Pointer to one character buffer provided by caller where
        received character will be placed.
 @parm  byte | not_last  | = 0 for last char to be received, otherwise non-zero. <nl>
 @rdesc 0: Success, received char is output to 'char_in' location.<nl>
        8: Timeout<nl>
        9: Slave faulty or not available<ule>
 @rdesc_sc1x3_sc2x
         On SC1x3/SC2x these additional return values are possible
         if the hardware I2C interface is used:<nl>
         3: Arbitration lost, general call address received<nl>
         4: Arbitration lost, own slave address received,
            master wants to read<nl> (change from master to slave)<nl>
         5: Arbitration lost, own slave address received,
            master wants to write<nl> (change from master to slave)<nl>
         6: Arbitration lost<nl>
         7: Bus error<nl>
 @comm  The IPC@CHIP&reg; is the I2C bus master.<nl><nl>
        This function will automatically generated a I2C Start or Restart
        condition.
 @Also  i2c87r.htm |  I2C_receive_block_ext |
        i2c86t.htm |  I2C_transmit_char_ext | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x86<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V0.90 | V1.00

 @target_clib V2.01
*/
int I2C_receive_char_ext (unsigned int slave,
                          char *char_in,
                          unsigned char not_last)
{
    unsigned char  flags;
    unsigned char result ;
    char the_char ;

    _CL = not_last ;         // = 0 if last char.
    _AX = (I2C_TRANS_RECV_CHAR_EXT << 8) | 0x01 | slave  ;
    asm {
      int I2CINT
      lahf
    } ;
    flags    = _AH ;    // Before they gets lost.
    result   = _AL ;
    the_char = _CH ;

    if (flags & CARRY_FLAG)
    {
        the_char = 0 ;
    }
    else
    {
        result = 0 ;
    }

    *char_in = the_char ;               // Set output parameter
    return (int) ((unsigned int) result) ;
}
#endif

/*************************************************************************/
//Transmit one character
/*************************************************************************/
#ifdef _i2c82t_
/*
@doc DOC_i2c82t_
 ---------------------------------------------------------------
  I2C send character
 ---------------------------------------------------------------
 @clib  I2C_transmit_char | Send a single character |
        <cfont>int I2C_transmit_char ( unsigned char slave,<nl>
        <tab><tab><tab><tab><tab><tab>char char_out );<efont> |
 @parm  byte | slave  | 7 bit slave address in B7-B1, B0=Don't care
 @parm  byte | char_out  | Byte to transmit.
 @rdesc 0: Success<nl>
        8: Timeout<nl>
        9: Slave faulty or not available<ule>
 @rdesc_sc1x3_sc2x
         On SC1x3/SC2x these additional return values are possible
         if the hardware I2C interface is used:<nl>
         3: Arbitration lost, general call address received<nl>
         4: Arbitration lost, own slave address received,
            master wants to read<nl> (change from master to slave)<nl>
         5: Arbitration lost, own slave address received,
            master wants to write<nl> (change from master to slave)<nl>
         6: Arbitration lost<nl>
         7: Bus error<nl>
 @comm  The IPC@CHIP&reg; is the I2C bus master.<nl><nl>
        This function will automatically generated a I2C Start or Restart
        condition.
 @Also  i2c83t.htm |  I2C_transmit_block   |
        i2c82r.htm |  I2C_receive_char | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x82<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int I2C_transmit_char (unsigned char slave, char char_out)
{
    unsigned char  flags;
    int result ;

    _CL = char_out ;

    _AX = (I2C_TRANS_RECV_CHAR << 8)
        | (unsigned)(slave & 0xFE) ;
    asm {
        int I2CINT
        lahf
    } ;
    flags    = _AH ;    // Before they gets lost.
    result   = (int)((unsigned int) _AL) ;

    if ((flags & CARRY_FLAG) == 0)
    {
        result = 0 ;
    }
    return result ;
}
#endif

/*************************************************************************/
//Transmit one character (extended address)
/*************************************************************************/
#ifdef _i2c86t_
/*
@doc DOC_i2c86t_
 ---------------------------------------------------------------
  I2C send character (extended address)
 ---------------------------------------------------------------
 @clib  I2C_transmit_char_ext | Send a single character (extended address)|
        <cfont>int I2C_transmit_char_ext ( unsigned int slave,<nl>
        <tab><tab><tab><tab><tab><tab><tab>char char_out );<efont> |
 @parm  word | slave  | 10 bit slave address in B10-B1, B0=Don't care
 @parm  byte | char_out  | Byte to transmit.
 @rdesc 0: Success<nl>
        8: Timeout<nl>
        9: Slave faulty or not available<ule>
 @rdesc_sc1x3_sc2x
         On SC1x3/SC2x these additional return values are possible
         if the hardware I2C interface is used:<nl>
         3: Arbitration lost, general call address received<nl>
         4: Arbitration lost, own slave address received,
            master wants to read<nl> (change from master to slave)<nl>
         5: Arbitration lost, own slave address received,
            master wants to write<nl> (change from master to slave)<nl>
         6: Arbitration lost<nl>
         7: Bus error<nl>
 @comm  The IPC@CHIP&reg; is the I2C bus master.<nl><nl>
        This function will automatically generated a I2C Start or Restart
        condition.
 @Also  i2c87t.htm |  I2C_transmit_block_ext   |
        i2c86r.htm |  I2C_receive_char_ext | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x86<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V0.90 | V1.00

 @target_clib V2.01
*/
int I2C_transmit_char_ext (unsigned int slave, char char_out)
{
    unsigned char  flags;
    int result ;

    _CL = char_out ;

    _AX = (I2C_TRANS_RECV_CHAR_EXT << 8)
        | (slave & 0x7FE) ;
    asm {
        int I2CINT
        lahf
    } ;
    flags    = _AH ;    // Before they gets lost.
    result   = (int)((unsigned int) _AL) ;

    if ((flags & CARRY_FLAG) == 0)
    {
        result = 0 ;
    }
    return result ;
}
#endif

/*************************************************************************/
//Receive Block
/*************************************************************************/
#ifdef _i2c83r_
/*
 @doc DOC_i2c83r_
 ---------------------------------------------------------------
 I2C receive block
 ---------------------------------------------------------------
 @clib  I2C_receive_block | Receive block of data on I2C bus |
        <cfont>int I2C_receive_block ( unsigned char slave,<nl>
        <tab><tab><tab><tab><tab><tab>char far *buffer,<nl>
        <tab><tab><tab><tab><tab><tab>int length );<efont> |
 @parm  byte   | slave  | 7 bit slave address in B7..B1; B0 n/a
 @parm  void * | buffer | Pointer to where data will be placed
 @parm  int    | length  | Number of bytes to receive
 @rdesc result  -  0 = Success<nl>
        <tab>non-zero indicates error:<nl><ul>
        8: Timeout<nl>
        9: Slave faulty or not available<nl>
        <ule>
 @rdesc_sc1x3_sc2x
         On SC1x3/SC2x these additional return values are possible
         if the hardware I2C interface is used:<nl>
         3: Arbitration lost, general call address received<nl>
         4: Arbitration lost, own slave address received,
            master wants to read<nl> (change from master to slave)<nl>
         5: Arbitration lost, own slave address received,
            master wants to write<nl> (change from master to slave)<nl>
         6: Arbitration lost<nl>
         7: Bus error<nl>
 @comm  This function will dwell until either 'length' bytes are received and stored in the buffer, or
        until an error occurs.<nl><nl>
        This function will automatically generated a I2C Start or Restart
        condition.
 @Also  i2c82r.htm |  I2C_receive_char |
        i2c83t.htm |  I2C_transmit_block | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x83<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int I2C_receive_block (unsigned char slave, char far * buffer, int length)
{
    unsigned char  flags;
    int result ;
    asm { LES  BX,buffer }
    _CX = length ;
    _AX = (I2C_TRANS_RECV_BLOCK << 8) | 0x01
        | (unsigned)slave  ;
    asm {
        int I2CINT
        lahf
    } ;
    flags    = _AH ;    // Before they gets lost.
    result   = (int)((unsigned int) _AL) ;

    if ((flags & CARRY_FLAG) == 0)
    {
        result = 0 ;
    }
    return result ;
}
#endif

/*************************************************************************/
//Receive Block (extended address)
/*************************************************************************/
#ifdef _i2c87r_
/*
 @doc DOC_i2c87r_
 ---------------------------------------------------------------
 I2C receive block (extended address)
 ---------------------------------------------------------------
 @clib  I2C_receive_block_ext | Receive block of data on I2C bus (extended address) |
        <cfont>int I2C_receive_block_ext ( unsigned int slave,<nl>
        <tab><tab><tab><tab><tab><tab><tab>char far *buffer,<nl>
        <tab><tab><tab><tab><tab><tab><tab>int length );<efont> |
 @parm  word   | slave  | 10 bit slave address in B10..B1; B0 n/a
 @parm  void * | buffer | Pointer to where data will be placed
 @parm  int    | length  | Number of bytes to receive
 @rdesc result  -  0 = Success<nl>
        <tab>non-zero indicates error:<nl><ul>
        8: Timeout<nl>
        9: Slave faulty or not available<nl>
        <ule>
 @rdesc_sc1x3_sc2x
         On SC1x3/SC2x these additional return values are possible
         if the hardware I2C interface is used:<nl>
         3: Arbitration lost, general call address received<nl>
         4: Arbitration lost, own slave address received,
            master wants to read<nl> (change from master to slave)<nl>
         5: Arbitration lost, own slave address received,
            master wants to write<nl> (change from master to slave)<nl>
         6: Arbitration lost<nl>
         7: Bus error<nl>
 @comm  This function will dwell until either 'length' bytes are received and stored in the buffer, or
        until an error occurs.<nl><nl>
        This function will automatically generated a I2C Start or Restart
        condition.
 @Also  i2c86r.htm |  I2C_receive_char_ext |
        i2c87t.htm |  I2C_transmit_block_ext | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x87<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V0.90 | V1.00

 @target_clib V2.01
*/
int I2C_receive_block_ext (unsigned int slave, char far * buffer, int length)
{
    unsigned char  flags;
    int result ;
    asm { LES  BX,buffer }
    _CX = length ;
    _AX = (I2C_TRANS_RECV_BLOCK_EXT << 8) | 0x01
        | slave  ;
    asm {
        int I2CINT
        lahf
    } ;
    flags    = _AH ;    // Before they gets lost.
    result   = (int)((unsigned int) _AL) ;

    if ((flags & CARRY_FLAG) == 0)
    {
        result = 0 ;
    }
    return result ;
}
#endif

/*************************************************************************/
//Transmit Block
/*************************************************************************/
#ifdef _i2c83t_
/*
 @doc DOC_i2c83t_
 ---------------------------------------------------------------
 I2C transmit block
 ---------------------------------------------------------------
 @clib  I2C_transmit_block | Send block of data on I2C bus |
        <cfont>int I2C_transmit_block ( unsigned char slave,<nl>
        <tab><tab><tab><tab><tab><tab> const char far *buffer,<nl>
        <tab><tab><tab><tab><tab><tab> int length );<efont> |
 @parm  byte   | slave  | 7 bit slave address in B7..B1; B0 n/a
 @parm  void * | buffer | Pointer to data source
 @parm  int    | length  | Number of bytes to send from buffer
 @rdesc result  -  0 = Success<nl>
        <tab>non-zero indicates error:<nl><ul>
        8: Timeout<nl>
        9: Slave faulty or not available<nl>
        <ule>
 @rdesc_sc1x3_sc2x
         On SC1x3/SC2x these additional return values are possible
         if the hardware I2C interface is used:<nl>
         3: Arbitration lost, general call address received<nl>
         4: Arbitration lost, own slave address received,
            master wants to read<nl> (change from master to slave)<nl>
         5: Arbitration lost, own slave address received,
            master wants to write<nl> (change from master to slave)<nl>
         6: Arbitration lost<nl>
         7: Bus error<nl>
 @comm This function will dwell until 'length' bytes from the buffer are transmitted or until an
       error occurs.<nl><nl>
       This function will automatically generated a I2C Start or Restart
       condition.
 @Also i2c82t.htm |  I2C_transmit_char |
       i2c83r.htm |  I2C_receive_block | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x83<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int I2C_transmit_block (unsigned char slave, const char far * buffer, int length)
{
    unsigned char  flags;
    int result ;
    asm { LES  BX,buffer }
    _CX = length ;
    _AX = (I2C_TRANS_RECV_BLOCK << 8)
        | (unsigned)(slave & 0xFE) ;
    asm {
        int I2CINT
        lahf
    } ;
    flags    = _AH ;    // Before they gets lost.
    result   = (int)((unsigned int) _AL) ;

    if ((flags & CARRY_FLAG) == 0)
    {
        result = 0 ;
    }
    return result ;
}
#endif

/*************************************************************************/
//Transmit Block (extended address)
/*************************************************************************/
#ifdef _i2c87t_
/*
 @doc DOC_i2c87t_
 ---------------------------------------------------------------
 I2C transmit block (extended address)
 ---------------------------------------------------------------
 @clib  I2C_transmit_block_ext | Send block of data on I2C bus (extended address)|
        <cfont>int I2C_transmit_block_ext ( unsigned int slave,<nl>
        <tab><tab><tab><tab><tab><tab><tab> const char far *buffer,<nl>
        <tab><tab><tab><tab><tab><tab><tab> int length );<efont> |
 @parm  word   | slave  | 10 bit slave address in B10..B1; B0 n/a
 @parm  void * | buffer | Pointer to data source
 @parm  int    | length  | Number of bytes to send from buffer
 @rdesc result  -  0 = Success<nl>
        <tab>non-zero indicates error:<nl><ul>
        8: Timeout<nl>
        9: Slave faulty or not available<nl>
        <ule>
 @rdesc_sc1x3_sc2x
         On SC1x3/SC2x these additional return values are possible
         if the hardware I2C interface is used:<nl>
         3: Arbitration lost, general call address received<nl>
         4: Arbitration lost, own slave address received,
            master wants to read<nl> (change from master to slave)<nl>
         5: Arbitration lost, own slave address received,
            master wants to write<nl> (change from master to slave)<nl>
         6: Arbitration lost<nl>
         7: Bus error<nl>
 @comm This function will dwell until 'length' bytes from the buffer are transmitted or until an
       error occurs.<nl><nl>
       This function will automatically generated a I2C Start or Restart
       condition.
 @Also i2c86t.htm |  I2C_transmit_char_ext |
       i2c87r.htm |  I2C_receive_block_ext | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x87<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V0.90 | V1.00

 @target_clib V2.01
*/
int I2C_transmit_block_ext (unsigned int slave, const char far * buffer, int length)
{
    unsigned char  flags;
    int result ;
    asm { LES  BX,buffer }
    _CX = length ;
    _AX = (I2C_TRANS_RECV_BLOCK_EXT << 8)
        | (slave & 0x7FE) ;
    asm {
        int I2CINT
        lahf
    } ;
    flags    = _AH ;    // Before they gets lost.
    result   = (int)((unsigned int) _AL) ;

    if ((flags & CARRY_FLAG) == 0)
    {
        result = 0 ;
    }
    return result ;
}
#endif

/*************************************************************************/
//Release I2C bus
/*************************************************************************/
#ifdef _i2c84_
/*
 @doc DOC_i2c84_
 ---------------------------------------------------------------
 Release I2C bus
 ---------------------------------------------------------------
 @clib  I2C_release | Release I2C Bus |
        <cfont>int I2C_release ( void ); <efont>  |
 @parm  byte |  | -- none --
 @rdesc I2C error code
 @comm  This function provides the I2C bus stop condition:
        a data low to high transition during clock high.<s2> Both clock and
        data output pins are left tri-stated.
 @Also  i2c8b.htm |  I2C_restart | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x84<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.26 | V1.26 | V1.26 | V1.23 | V1.23
*/
int I2C_release (void)
{
    _AX = I2C_RELEASE << 8 ;        // AL = 0
    asm { int I2CINT  } ;
    return _AX;
}
#endif

/*************************************(***********************************/
//Restart I2C
/*************************************************************************/
#ifdef _i2c8b_
/*
 @doc DOC_i2c8b_
 ---------------------------------------------------------------
 Restart I2C
 ---------------------------------------------------------------
 @clib  I2C_restart | Restart I2C Bus |
        <cfont>void I2C_restart ( void );<efont>  |
 @parm  byte | | -- none --
 @rdesc -- none --
 @comm  This function provides the I2C bus start condition:
        a data high to low transition during clock high.
 @Also  i2c84.htm |  I2C_release | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x8B<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void I2C_restart (void)
{
    _AX = I2C_RESTART << 8 ;         // AL = 0
    asm { int I2CINT  } ;
}
#endif

/*************************************************************************/
// Select I2C Clock Pin
/*************************************************************************/
#ifdef _i2c8e_
/*
 @doc DOC_i2c8e_
 ---------------------------------------------------------------
 Select I2C Clock Pin
 ---------------------------------------------------------------
 @clib  I2C_select_clock_pin | Select I2C Clock Pin |
        <cfont>void I2C_select_clock_pin ( unsigned char pio_no );<efont> |
 @parm_sc1x  byte  | pio_no  | PIO pin number, [0..13]
 @parm_sc1x3 byte  | pio_no  | PIO pin number, [0..24, 26..31]
 @parm_sc2x byte   | pio_no  | PIO pin number, [0..1, 9..11, 13, 18..23, 27..28]
 @rdesc -- none --
 @commtarget SC1x | The default I2C clock pin is PIO 0.<nl><nl>
        To change the I2CCLK pin this function must be called before the
        <linkto>i2c80.htm<linkmid>I2C_init<linktail> function is called.
 @commtarget SC1x3/SC2x | To use the I2C hardware interface do not call the functions
         "Select I2C Clock Pin" and "Select I2C Data Pin" or call them both with
         PIO pin number 0.
 @Also  i2c8f.htm |  I2C_select_data_pin |
        i2c80.htm |  I2C_init |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x8E<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void I2C_select_clock_pin(unsigned char pio_no)
{
    _AL = pio_no ;
    _AH = I2C_SELECT_CLK_PIN ;
    asm { int I2CINT  } ;
}
#endif

/*************************************************************************/
//Select I2C data Pin
/*************************************************************************/
#ifdef _i2c8f_
/*
 @doc DOC_i2c8f_
 ---------------------------------------------------------------
 Select I2C Data Pin
 ---------------------------------------------------------------
 @clib  I2C_select_data_pin | Select I2C Data Pin |
        <cfont>void I2C_select_data_pin ( unsigned char pio_no );<efont> |
 @parm_sc1x  byte   | pio_no  | PIO pin number, [0..13]
 @parm_sc1x3 byte   | pio_no  | PIO pin number, [0..24, 26..31]
 @parm_sc2x byte    | pio_no  | PIO pin number, [0..1, 9..11, 13, 18..23, 27..28]
 @rdesc -- none --
 @commtarget SC1x | The default I2C data pin is PIO 1.<nl><nl>
        To change the I2CDAT pin this function must be called before the
        <linkto>i2c80.htm<linkmid>I2C_init<linktail> function is called.
 @commtarget SC1x3/SC2x | To use the I2C hardware interface do not call the functions
         "Select I2C Clock Pin" and "Select I2C Data Pin" or call them both with
         PIO pin number 0.
 @Also  i2c8e.htm |  I2C_select_clock_pin |
        i2c80.htm |  I2C_init |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x8F<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void I2C_select_data_pin(unsigned char pio_no)
{
    _AL = pio_no ;
    _AH = I2C_SELECT_DATA_PIN ;
    asm { int I2CINT  } ;
}
#endif

/*************************************************************************/
//Select I2C speed (hardware interface only)
/*************************************************************************/
#ifdef _i2cb0_
/*
 @doc DOC_i2cb0_
 ---------------------------------------------------------------
 Select I2C speed (hardware interface only)
 ---------------------------------------------------------------
 @clib  I2C_set_speed | Select I2C frequency |
        <cfont>void I2C_set_speed ( unsigned char n, unsigned char m );<efont> |
 @parm  byte   | n  | parameter n (allowed value range 0-7)
 @parm  byte   | m  | parameter m (allowed value range 0-15)
 @rdesc -- none --
 @comm  This function sets the I2C bus speed, if the I2C hardware interface
        is used.<nl><nl>
        FREQsample = CPU clock / 2^N<nl>
        FREQoscl = CPU clock / ((2^N) * (M+1) * 10)<nl>
        <nl>
        FREQoscl is the frequency of the I²C clock line when the I²C controller
        is in master mode.<nl>
        FREQsample is the frequency at which the I²C bus is sampled.
        This frequency should be at least 10 times faster than the fastest
        master on the bus, to ensure that START and STOP conditions are
        always detected.<nl>
        <nl>
        Default is N=4, M=5, which sets FREQsample to 6 MHz and FREQoscl to
        100 KHz at 96 MHz CPU frequency.
 @Also  i2c80.htm |  I2C_init |  | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xB0<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/
void I2C_set_speed(unsigned char n, unsigned char m)
{
    _BL = n ;
    _BH = m ;
    _AH = I2C_SET_SPEED ;
    asm { int I2CINT  } ;
}
#endif

/*************************************************************************/
//Reset the I2C controller (hardware interface only)
/*************************************************************************/
#ifdef _i2cb1_
/*
 @doc DOC_i2cb1_
 ---------------------------------------------------------------
 Reset I2C controller (hardware interface only)
 ---------------------------------------------------------------
 @clib  I2C_reset | Reset I2C bus hardware controller |
        <cfont>void I2C_reset ( void );<efont> |
 @rdesc -- none --
 @comm  This function resets the I2C bus hardware controller.
 @Also  i2c80.htm |  I2C_init |  | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xB1<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/
void I2C_reset(void)
{
    _AH = I2C_RESET ;
    asm { int I2CINT  } ;
}
#endif


/*************************************************************************/
//Set I2C bus timeout
/*************************************************************************/
#ifdef _i2c88_
/*
 @doc DOC_i2c88_
 ---------------------------------------------------------------
 Set I2C bus timeout
 ---------------------------------------------------------------
 @clib  I2C_set_timeout | Set I2C bus timeout |
        <cfont>void I2C_set_timeout ( unsigned int value );<efont> |
 @parm  int  | value | Timeout value.<nl><nl>
        If the I2C hardware interface is used, this value has a resolution in
        milliseconds. This means that the internal I2C functions will wait for BX
        milliseconds if the I2C clock signal is released by the I2C slave.<nl>
        <nl>
        If the software I2C emulation is used, this value is interpreted as a
        cycle count. This means that the internal I2C functions check BX times
        if the I2C clock signal is released by the I2C slave.
 @rdesc -- none --
 @comm  If the I2C slave uses clock stretching, this timeout specifies the maximum
        waiting time, before the access is aborted.<nl><nl>
        The default timeout is:<nl>
        SC12: 50 cycles<nl>
        SC12B: 100 cycles<nl>
        SC13/SC11: 250 cycles<nl>
        SC1x3/SC2x: 3000 cycles / 50 ms
 @Also  i2c80.htm |  I2C_init |  | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x88<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.22 | V1.22 | V1.22 | V1.11 | V1.00

 @target_clib V2.08
*/
void I2C_set_timeout(unsigned int value)
{
    _BX = value ;
    _AH = I2C_SET_TIMEOUT ;
    asm { int I2CINT  } ;
}
#endif

/*************************************************************************/
//Select I2C slave address (hardware interface only)
/*************************************************************************/
#ifdef _i2cb2_
/*
 @doc DOC_i2cb2_
 ---------------------------------------------------------------
 Set I2C bus slave address (hardware interface only)
 ---------------------------------------------------------------
 @clib  I2C_slave_address | Set the I2C bus slave address |
        <cfont>void I2C_slave_address ( unsigned int addr, unsigned char gencalladdr );<efont> |
 @parm  word   | addr         | Slave address:<nl>
                                Bit0: don't care<nl>
                                Bit7-1: 7 bit slave address or<nl>
                                Bit10-1: 10 bit slave address
 @parm  byte   | gencalladdr  | 0: don't listen to general call address<nl>
                                1: listen to general call address
 @rdesc -- none --
 @comm  This function initializes the I2C bus slave interface.
        To use the I2C slave interface the user has to install an interrupt
        service routine for the I2C interrupt. An interrupt occurs when the
        I2C state changes. The user should than read the I2C state with
        function I2C_slave_getstate.<nl>
        <nl>
        The I2C bus intialize function must be called previously.
        The Slave mode works only if the I2C hardware interface in used.<nl>
        <nl>
        If the I2C slave mode is no longer used, the program should uninstall
        the interrupt service routine and call the I2C_slave_address() function
        with address 0 to disable the slave mode.
 @Also  i2c80.htm |  I2C_init |  | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xB2<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/
void I2C_slave_address(unsigned int addr, unsigned char gencalladdr)
{
    _BX = addr & 0xFFFE ;
    _CL = gencalladdr ;
    _AH = I2C_SLAVE_SET_ADDR ;
    asm { int I2CINT  } ;
}
#endif

/*************************************************************************/
//Get I2C slave state (hardware interface only)
/*************************************************************************/
#ifdef _i2cb3_
/*
 @doc DOC_i2cb3_
 ---------------------------------------------------------------
 Get I2C bus slave state (hardware interface only)
 ---------------------------------------------------------------
 @clib  I2C_slave_getstate | Get the I2C bus state |
        <cfont>unsigned int I2C_slave_getstate ( void );<efont> |
 @rdesc I2C bus state:<nl>
        3: General call address received<nl>
        4: Own slave address received, master wants to read<nl>
        5: Own slave address received, master wants to write<nl>
        6: Arbitration lost<nl>
        7: Bus error<nl>
        10: Data byte received from master<nl>
        11: Data byte transmitted to master, master wants next byte<nl>
        12: Last data byte transmitted to master<nl>
        13: STOP or repeated START condition received<nl>
 @comm  This function reads the current I2C bus state and should be used inside
        the I2C interrupt handler, if the I2C slave interface is used.
 @Also  i2cb2.htm |  I2C_slave_address |  | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xB3<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/
unsigned int I2C_slave_getstate(void)
{
    _AH = I2C_SLAVE_GET_STATE ;
    asm { int I2CINT  } ;
    return _AX;
}
#endif


/*************************************************************************/
//Send I2C slave acknowledge (hardware interface only)
/*************************************************************************/
#ifdef _i2cb4_
/*
 @doc DOC_i2cb4_
 ---------------------------------------------------------------
 Send I2C bus slave acknowledge (hardware interface only)
 ---------------------------------------------------------------
 @clib  I2C_slave_sendack | Send a I2C bus acknowledge |
        <cfont>void I2C_slave_sendack ( unsigned char ack );<efont> |
 @parm  byte   | ack  | 0: Send a non acknowledge<nl>
                        1: Send acknowledge
 @rdesc -- none --
 @comm  This function should be used inside the I2C interrupt handler,
        if the I2C slave interface is used and the return state signals
        that the master wants to write a byte.
 @Also  i2cb3.htm |  I2C_slave_getstate |  | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xB4<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/
void I2C_slave_sendack(unsigned char ack)
{
    _AH = I2C_SLAVE_SEND_ACK ;
    _AL = ack;
    asm { int I2CINT  } ;
}
#endif

/*************************************************************************/
//Read byte from I2C bus as slave (hardware interface only)
/*************************************************************************/
#ifdef _i2cb5_
/*
 @doc DOC_i2cb5_
 ---------------------------------------------------------------
 Read a byte from I2C bus as slave  (hardware interface only)
 ---------------------------------------------------------------
 @clib  I2C_slave_readbyte | Read a byte from I2C bus as slave |
        <cfont>unsigned char I2C_slave_readbyte ( void );<efont> |
 @rdesc The read byte
 @comm  This function should be used inside the I2C interrupt handler,
        if the I2C slave interface is used and the return state signals that
        the master has written a byte, which can now be read out.
 @Also  i2cb6.htm |  I2C_slave_sendbyte |  | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xB5<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/
unsigned char I2C_slave_readbyte(void)
{
    _AH = I2C_SLAVE_READ ;
    asm { int I2CINT  } ;
    return _AL ;
}
#endif


/*************************************************************************/
//Send byte to I2C bus as slave (hardware interface only)
/*************************************************************************/
#ifdef _i2cb6_
/*
 @doc DOC_i2cb6_
 ---------------------------------------------------------------
 Send a byte to I2C bus as slave  (hardware interface only)
 ---------------------------------------------------------------
 @clib  I2C_slave_sendbyte | Send a byte to I2C bus as slave |
        <cfont>void I2C_slave_sendbyte ( unsigned char data, unsigend char next );<efont> |
 @parm  byte   | data  | Byte to write
 @parm  byte   | next  | 1: Signal that more bytes are available<nl>
                         0: Signal that this is the last byte that can be transfered
 @rdesc -- none --
 @comm  This function should be used inside the I2C interrupt handler,
        if the I2C slave interface is used and the return state signals that
        the master wants to read a byte.
 @Also  i2cb5.htm |  I2C_slave_readbyte |  |  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xB6<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/
void I2C_slave_sendbyte(unsigned char data, unsigned char next)
{
    _BL = next;
    _AL = data;
    _AH = I2C_SLAVE_SEND ;
    asm { int I2CINT  } ;
}
#endif

/*************************************************************************/
//Return the I2C controller to idle state (hardware interface only)
/*************************************************************************/
#ifdef _i2cb7_
/*
 @doc DOC_i2cb7_
 ---------------------------------------------------------------
 Return the I2C controller to the idle state (hardware interface only)
 ---------------------------------------------------------------
 @clib  I2C_slave_idle | Set the I2C internal state back to idle |
        <cfont>void I2C_slave_idle ( void );<efont> |
 @rdesc -- none --
 @comm  This function should be used inside the I2C interrupt handler,
        if the I2C slave interface is used and the return state signals that
        the last byte was transmitted to the master.
 @Also  i2cb3.htm |  I2C_slave_getstate |  | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xB7<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/
void I2C_slave_idle(void)
{
    _AH = I2C_SLAVE_IDLE ;
    asm { int I2CINT  } ;
}
#endif


#ifdef _i2cb8_
/*
 @doc DOC_i2cb8_
 ---------------------------------------------------------------
 Reset I2C bus by clock transitions
 ---------------------------------------------------------------
 @clib  I2C_Bus_Reset | Reset I2C bus by clock transitions |
        <cfont>int I2C_bus_reset(unsigned short sdaPio, unsigned short sclPio);<efont> |
 @parm  word   | sdaPio        | PIO number of SDA line
 @parm  word   | sclPio        | PIO number of SCL line <nl>
                                 If sdaPio and sclPio == 0 default I2C pios of hardware I2C are used.<nl>
 @rdesc Number of executed clock transitions (max.10) until SDA Line was pulled to high by the slave.

 @comm  Executing an I2C-Reset with clock 1-0 transitions.<nl>
 This function can be executed by an I2C-Master in case, that the connected I2C-slaves are not
 responding. <nl>
 At I2C bus systems the situation could occur (in rare cases), that an I2C slave hangs.
 This situation is a general problem and not a specific problem of the IPC@CHIP I2C bus.
 An application note from "Analog Devices"  (AN-686) describes this problem in detail.
 One solution to get a slave out of the hang-up situation is to reset the slave  with a separate PIO.
 Another possibilty(implemented here) is the execution of "clock sequences" by the I2C-Bus master,
 also described at this application note.<nl>
 The master executes up to 10 High-Low transitions of SCL line. It stops, when it detects
 a high signal at the SDA line.<nl>
 After execution <linkto>i2c80.htm<linkmid>I2C_init<linktail> must be called.<nl>

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.21
*/
int I2C_bus_reset(unsigned short sdaPio, unsigned short sclPio)
{
   int i;
   if((sdaPio==0) && (sclPio==0))
   {
     sdaPio=13;sclPio=31;   //HW I2C
   }
   pfe_enable_pio(sdaPio,1);    //Pio input pullup
   pfe_enable_pio(sclPio,1);
   RTX_Sleep_Time(3);
   for(i=0;i<10;i++)
   {
      if(hal_read_pio(sdaPio)==0)
      {
        pfe_enable_pio(sclPio,5);  //Pio output 0
        RTX_Sleep_Time(1);
        pfe_enable_pio(sclPio,1);
        RTX_Sleep_Time(1);
      }
      else
      {
         break;
      }
   }
   return i;
}
#endif

// End I2C_API.C ////////////////////////


/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* MOdule      :   I2C_PRIV.H
* Function    :   Internal information for I2C C Library.
* ---------------------------------------------------------------------------

$Header: I2C_PRIV.H, 7, 16.02.2007 17:23:38, Andre Pribil$

*****************************************************************************/

#ifndef __I2_PRIV_H__
#define __I2_PRIV_H__

#define I2CINT               0xAA

/*************************************************************************/
// I2C Api Services
/*************************************************************************/
    // "Unsigned" 'u' appended here to assure Paradigm Beck Edition compiler
    //  that we do not care about sign bit after the 8 bit left shift.
#define I2C_INIT                 0x80u
#define I2C_SCAN                 0x81u
#define I2C_SCAN_EXT             0x85u
#define I2C_TRANS_RECV_CHAR      0x82u
#define I2C_TRANS_RECV_CHAR_EXT  0x86u
#define I2C_TRANS_RECV_BLOCK     0x83u
#define I2C_TRANS_RECV_BLOCK_EXT 0x87u
#define I2C_RELEASE              0x84u
#define I2C_RESTART              0x8Bu
#define I2C_SET_TIMEOUT          0x88u
#define I2C_SELECT_CLK_PIN       0x8Eu
#define I2C_SELECT_DATA_PIN      0x8Fu
#define I2C_SET_SPEED            0xB0u
#define I2C_RESET                0xB1u
#define I2C_SLAVE_SET_ADDR       0xB2u
#define I2C_SLAVE_GET_STATE      0xB3u
#define I2C_SLAVE_SEND_ACK       0xB4u
#define I2C_SLAVE_READ           0xB5u
#define I2C_SLAVE_SEND           0xB6u
#define I2C_SLAVE_IDLE           0xB7u


/*************************************************************************/
#endif /* __I2_PRIV_H__*/
/*************************************************************************/
//end i2c_priv.h
/*************************************************************************/
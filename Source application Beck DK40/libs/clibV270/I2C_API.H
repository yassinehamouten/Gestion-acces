/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module        : I2C_API.H
* Function      : Defines and typedefs for I2C_API.C
* ---------------------------------------------------------------------------
* History       :
*  Vx.yy                   Author  Changes
*  V1.00      17.07.00     roth    Create
* ---------------------------------------------------------------------------
*  Published on the BECK WebSite with kind permission of Bernhard Roth.

$Header: I2C_API.H, 10, 12.06.2008 12:39:21, Andre Pribil$

****************************************************************************/

#ifndef __I2CAPI_H__
#define __I2CAPI_H__


/*************************************************************************/
//prototypes
/*************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

void _cdecl I2C_init             (void);
int  _cdecl I2C_release          (void);
void _cdecl I2C_restart          (void);
unsigned char _cdecl I2C_scan    (unsigned char start_addr, unsigned char end_addr);
int  _cdecl I2C_transmit_block   (unsigned char slave,
                                  const char far * buffer,
                                  int length);
int  _cdecl I2C_receive_block    (unsigned char slave, char far * buffer, int length);
int  _cdecl I2C_transmit_char    (unsigned char slave, char char_out);
int  _cdecl I2C_receive_char     (unsigned char slave,
                                  char * char_in,
                                  unsigned char not_last);
void _cdecl I2C_select_clock_pin (unsigned char pio_no);
void _cdecl I2C_select_data_pin  (unsigned char pio_no);
void _cdecl I2C_set_timeout      (unsigned int value);

// Extended address versions
unsigned int _cdecl I2C_scan_ext  (unsigned int start_addr, unsigned int end_addr);
int  _cdecl I2C_transmit_block_ext(unsigned int slave,
                                   const char far * buffer,
                                   int length);
int  _cdecl I2C_receive_block_ext (unsigned int slave, char far * buffer, int length);
int  _cdecl I2C_transmit_char_ext (unsigned int slave, char char_out);
int  _cdecl I2C_receive_char_ext  (unsigned int slave,
                                   char * char_in,
                                   unsigned char not_last);

// SC123/SC143 functions
void _cdecl I2C_set_speed         (unsigned char n, unsigned char m);
void _cdecl I2C_reset             (void);
void _cdecl I2C_slave_address     (unsigned int addr, unsigned char gencalladdr);
unsigned int  _cdecl I2C_slave_getstate(void);
void _cdecl I2C_slave_sendack     (unsigned char ack);
unsigned char _cdecl I2C_slave_readbyte (void);
void _cdecl I2C_slave_sendbyte    (unsigned char data, unsigned char next);
void _cdecl I2C_slave_idle        (void);

int _cdecl I2C_bus_reset(unsigned short sdaPio, unsigned short sclPio);


#ifdef __cplusplus
}
#endif

/*************************************************************************/
#endif /* __I2CAPI_H__*/
/*************************************************************************/
//end i2c_api.h
/*************************************************************************/
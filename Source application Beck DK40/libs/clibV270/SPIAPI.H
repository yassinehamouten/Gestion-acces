/****************************************************************************
* (C) 1999-2007 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : SPIAPI.H
* Function       : prototypes, constants for SPI API functions
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\SPIAPI.H, 13, 03.04.2007 13:51:39, Jan Schatz$

*****************************************************************************/

#ifndef SPIAPI_H
#define SPIAPI_H

/***************************************************************************/
// Prototyps
/***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif



// If SPI_DYN_LINK is defined, the following functions will be mapped to
// their pendant with the _Dyn suffix. Dynamic linking will be used instead of a
// software interrupt to trigger the respective RTOS function in this case.
// Dynamic linking for the SPI CLIB will not work on older RTOS versions.
// Check the CLIB documentation for further information.
#ifdef SPI_DYN_LINK
  void          far _cdecl spi_init_dyn               (unsigned mode, char clock, char dataIn, char dataOut);
  void          far _cdecl spi_write_dyn              (const void far *bufferPtr, unsigned short nbytes);
  void          far _cdecl spi_read_dyn               (void far *bufferPtr, unsigned short nbytes);
  void          far _cdecl spi_read_write_dyn         (void far *rbufferPtr, const void far *wbufferPtr, unsigned short nbytes);
  
  void          far _cdecl spi_init_hw_dyn            (unsigned mode, unsigned div);
  unsigned int  far _cdecl spi_write_hw_dyn           (const void far *bufferPtr, unsigned short nbytes);
  unsigned int  far _cdecl spi_read_hw_dyn            (void far *bufferPtr, unsigned short nbytes);
  unsigned int  far _cdecl spi_read_write_hw_dyn      (void far *rbufferPtr, const void far *wbufferPtr, unsigned short nbytes);
  
  void          far _cdecl spi_slave_init_dyn         (unsigned mode);
  void          far _cdecl spi_slave_write_dyn        (unsigned char data);
  unsigned char far _cdecl spi_slave_read_dyn         (void);
  unsigned char far _cdecl spi_slave_read_write_dyn   (unsigned char data);
  unsigned int  far _cdecl spi_waiton_sem_dyn         (void);
  unsigned int  far _cdecl spi_waiton_sem_setmode_dyn (unsigned mode, unsigned div);
  int           far _cdecl spi_waiton_sem_ext_dyn     (long timeout, unsigned priority);
  int           far _cdecl spi_waiton_sem_setmode_ext_dyn (unsigned mode, unsigned div, long timeout, unsigned priority);

  unsigned int  far _cdecl spi_release_sem_dyn        (void);

  #define spi_init                    spi_init_dyn
  #define spi_write                   spi_write_dyn
  #define spi_read                    spi_read_dyn
  #define spi_read_write              spi_read_write_dyn

  #define spi_init_hw                 spi_init_hw_dyn
  #define spi_write_hw                spi_write_hw_dyn
  #define spi_read_hw                 spi_read_hw_dyn
  #define spi_read_write_hw           spi_read_write_hw_dyn

  #define spi_slave_init              spi_slave_init_dyn
  #define spi_slave_write             spi_slave_write_dyn
  #define spi_slave_read              spi_slave_read_dyn
  #define spi_slave_read_write        spi_slave_read_write_dyn
  #define spi_waiton_sem              spi_waiton_sem_dyn
  #define spi_waiton_sem_setmode      spi_waiton_sem_setmode_dyn
  #define spi_waiton_sem_ext          spi_waiton_sem_ext_dyn
  #define spi_waiton_sem_setmode_ext  spi_waiton_sem_setmode_ext_dyn
  #define spi_release_sem             spi_release_sem_dyn
#else
  void          _cdecl spi_init               (unsigned mode, char clock, char dataIn, char dataOut);
  void          _cdecl spi_write              (const void far *bufferPtr, unsigned short nbytes);
  void          _cdecl spi_read               (void far *bufferPtr, unsigned short nbytes);
  void          _cdecl spi_read_write         (void far *rbufferPtr, const void far *wbufferPtr, unsigned short nbytes);

  void          _cdecl spi_init_hw            (unsigned mode, unsigned div);
  unsigned int  _cdecl spi_write_hw           (const void far *bufferPtr, unsigned short nbytes);
  unsigned int  _cdecl spi_read_hw            (void far *bufferPtr, unsigned short nbytes);
  unsigned int  _cdecl spi_read_write_hw      (void far *rbufferPtr, const void far *wbufferPtr, unsigned short nbytes);

  void          _cdecl spi_slave_init         (unsigned mode);
  void          _cdecl spi_slave_write        (unsigned char data);
  unsigned char _cdecl spi_slave_read         (void);
  unsigned char _cdecl spi_slave_read_write   (unsigned char data);
  unsigned int  _cdecl spi_waiton_sem         (void);
  unsigned int  _cdecl spi_waiton_sem_setmode (unsigned mode, unsigned div);
  int           _cdecl spi_waiton_sem_ext     (long timeout, unsigned priority);
  int           _cdecl spi_waiton_sem_setmode_ext (unsigned mode, unsigned div, long timeout, unsigned priority);
  unsigned int  _cdecl spi_release_sem        (void);
#endif  // #ifdef SPI_DYN_LINK



#define SPI_MODE0          0x0000
#define SPI_MODE1          0x0001
#define SPI_MODE2          0x0002
#define SPI_MODE3          0x0003
#define SPI_OPEN_DRAIN     0x0004
#define SPI_AUTODRIVE      0x0008
#define SPI_INVERT_CS      0x0010
#define SPI_SHIFT1         0x0020
#define SPI_SHIFT2         0x0040
#define SPI_SHIFT3         0x0060
#define SPI_SHIFT4         0x0080
#define SPI_SHIFT5         0x00A0
#define SPI_SHIFT6         0x00C0
#define SPI_SHIFT7         0x00E0
#define SPI_SHIFT8         0x0000
#define SPI_ALTERNATE_IO   0x0100

#ifdef __cplusplus
}
#endif

#endif  // SPIAPI_H


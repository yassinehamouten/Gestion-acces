/****************************************************************************
* (C) 1999-2007 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : SPIAPI.C
* Function       : SPI API functions
* ---------------------------------------------------------------------------

$Header: SPIAPI.C, 28, 12.11.2008 12:51:10, Andre Pribil$

*****************************************************************************/

/***************************************************************************/
// Includes
/***************************************************************************/
#include <dos.h>

#include "config.h"
#include "spiapi.h"
#include "spi_priv.h"

/*
 @doc DOC_INDEX
 ---------------------------------------------------------------
 SPI API Table of Contents
 ---------------------------------------------------------------
 @clibidx  <tab><cfont>#include <InBraces SPIAPI\.H><efont> |

 Here is the CLIB API for access to the IPC@CHIP&reg;'s SPI bus.<nl>
 
 SPI is a serial bus standard established by Motorola. The Serial Peripheral
 Interface (SPI) is a synchronous serial interface useful for communicating
 with other peripheral or microcontroller devices. These peripheral devices
 may be Serial EEPROMs, shift registers, display drivers, A/D converters, etc.<nl>
 
 @libcat1a  Init | SPI Init | spi90 |
    spi_init | Init the SPI Interface (software emulation)|
 @libcat1a Init | SPI Init | spi90A |
    spi_init_hw | Init the SPI Interface (hardware interface)|

 @libcat2a  Access | SPI Access| spi95  |
    spi_write | Write to the SPI Interface (software emulation/hardware interface)|
 @libcat2a  Access | SPI Access | spi96 |
    spi_read | Read from the SPI Interface (software emulation/hardware interface)|
 @libcat2a  Access | SPI Access | spi97 |
    spi_read_write | Read and write from/to the SPI Interface (software emulation/hardware interface)|
 @libcat2a  Access | SPI Access | spi95A |
    spi_write_hw | Write to the SPI Interface (with return value for hardware interface)|
 @libcat2a Access | SPI Access | spi96A |
    spi_read_hw | Read from the SPI Interface (with return value for hardware interface)|
 @libcat2a  Access | SPI Access | spi97A |
    spi_read_write_hw | Read and write from/to the SPI Interface (with return value for hardware interface)|
 @libcat2a  Access | SPI Access | spiA8 |
    spi_waiton_sem | Wait on SPI semaphore (hardware interface)|
 @libcat2a  Access | SPI Access | spiA8C |
    spi_waiton_sem_ext | Wait on SPI semaphore with timeout (hardware interface)|
 @libcat2a  Access | SPI Access | spiA8B |
    spi_waiton_sem_setmode | Wait on SPI semaphore, set SPI mode and divider (hardware interface)|
 @libcat2a  Access | SPI Access | spiA8D |
    spi_waiton_sem_setmode_ext | Wait on SPI semaphore with timeout, set SPI mode and divider (hardware interface)|
 @libcat2a  Access | SPI Access | spiA8A |
    spi_release_sem | Release the SPI semaphore (hardware interface)|

 @libcat3a  Slave | SPI Slave | spiA0 |
    spi_slave_init | Init the SPI Slave Interface (hardware interface)|
 @libcat3a  Slave | SPI Slave | spiA5 |
    spi_slave_write | Write to the SPI Slave Interface (hardware interface)|
 @libcat3a  Slave | SPI Slave | spiA6 |
    spi_slave_read | Read from the SPI Slave Interface (hardware interface)|
 @libcat3a  Slave | SPI Slave | spiA7 |
    spi_slave_read_write | Read and write from/to the SPI Slave Interface (hardware interface)|
*/

/***************************************************************************/
// Init SPI
/***************************************************************************/
#ifdef _spi90_
/*
 #DOCLIST:spi_init_dyn clib\spi\spi90.htm

 @doc DOC_spi90_
 ---------------------------------------------------------------
 Init SPI
 ---------------------------------------------------------------
 @clib  spi_init | Init the SPI Interface (software emulation) |
        <cfont>void spi_init ( unsigned int mode, char clock,<nl>
        <tab><tab><tab><tab>char dataIn, char dataOut ); <efont> |
 @parm  unsigned int  | mode  | must be '0'<nl>
 @parm  char  | clock | Number of the pio which should be used as clock pin
 @parm  char  | dataIn  | Number of the pio which should be used as data in pin
 @parm  char  | dataOut | Number of the pio which should be used as data out pin
 @rdesc -- none --
 @Also  spi95.htm |  spi_write |
        spi96.htm |  spi_read  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x90<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_init_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
 @target_clib V2.01
*/
void spi_init( unsigned mode, char clock, char dataIn, char dataOut)
{
  _BX = mode;
  _CL = clock;
  _CH = dataIn;
  _DL = dataOut;
  _AH = SPI_INIT;
  asm int SPI_INT
}
#endif


/***************************************************************************/
// Init SPI (hardware interface)
/***************************************************************************/
#ifdef _spi90A_
/*
 #DOCLIST:spi_init_hw_dyn clib\spi\spi90A.htm

 @doc DOC_spi90A_
 ---------------------------------------------------------------
 Init SPI (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_init_hw | Init the SPI Interface (hardware interface) |
        <cfont>void spi_init_hw ( unsigned int mode, unsigned int div );<efont> |
 @parm  unsigned int  | mode  | Combine the following defines with a bitwise OR to select the operation mode.<nl><nl>
        SPI mode:<nl>
          <tab>set one of these: <cfont>SPI_MODE0, SPI_MODE1, SPI_MODE2 or SPI_MODE3<efont><nl>
        Open-Drain-Mode:<nl>
          <tab>select <cfont>SPI_OPEN_DRAIN<efont> for open-drain-mode,<nl>
          <tab>else output mode is used<nl>
        Autodrive:<nl>
          <tab>select <cfont>SPI_AUTODRIVE<efont> to autodrive SLVSEL chipselect pin,<nl>
          <tab>works only together with SPI_ALTERNATE_IO<nl>
          <tab>else do not drive SLVSEL pin<nl>
        Invert chipselect:<nl>
          <tab>select <cfont>SPI_INVERT_CS<efont> to invert SLVSEL chipselect pin (active high),<nl>
          <tab>else do not invert SLVSEL pin (active low)<nl>
        Shift count:<nl>
          <tab>select the shift count with these defines:<nl>
          <tab><cfont>SPI_SHIFT1, SPI_SHIFT2, SPI_SHIFT3, SPI_SHIFT4,<efont><nl>
          <tab><cfont>SPI_SHIFT5, SPI_SHIFT6, SPI_SHIFT7, SPI_SHIFT8<efont><nl>
        Swap SDI and SDO:<nl>
          <tab>select <cfont>SPI_ALTERNATE_IO<efont> to swap SDI and SDO pins<nl>
 @parm  unsigned int  | div  | SPI speed clock divider (valid values: 0-65535)<nl>
         The SPI clock frequency is calculated with the formula:<nl>
         SPI freq = CPU freq / (divider*2+2)<nl>
 @comm  A Wired-OR mode is provided which allows multiple masters to collide on the bus
        without risk of damage. In this mode, an external pull-up resistor is required
        on the Master Out Slave In (MOSI) and Master In Slave Out (MISO) pins.
        Generally, pull-ups are recommended on all of the external SPI signals to ensure
        they are held in a valid state, even when the SPI interface is disabled.<nl>
 @rdesc -- none --
 @Also  spi95A.htm |  spi_write_hw |
        spi96A.htm |  spi_read_hw  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x90<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_init_hw_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00
 @target_clib V2.01
*/
void spi_init_hw( unsigned mode, unsigned div)
{
  _BX = mode;
  _CX = 0; // select hardware SPI
  _DL = 0; // select hardware SPI
  _SI = div;
  _AH = SPI_INIT;
  asm int SPI_INT
}
#endif


/***************************************************************************/
// SPI Write
/***************************************************************************/
#ifdef _spi95_
/*
 #DOCLIST:spi_write_dyn clib\spi\spi95.htm

 @doc DOC_spi95_
 ---------------------------------------------------------------
 SPI Write
 ---------------------------------------------------------------
 @clib  spi_write | Write to the SPI Interface |
        <cfont>void spi_write ( const void far *bufferPtr, unsigned short nbytes );<efont> |
 @parm  void * | bufferPtr  | Pointer to buffer which contains write data
 @parm  int    | nbytes     | number of bytes to write
 @rdesc  -- none --
 @Also  spi90.htm |  spi_init |
        spi96.htm |  spi_read | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x95<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_write_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
  @target_clib V2.01
*/
void spi_write (const void far *bufferPtr, unsigned short nbytes)
{
  // write data
  _ES = FP_SEG(bufferPtr);
  _SI = FP_OFF(bufferPtr);
  _CX = nbytes;
  _AH = SPI_WRITE;
  asm int SPI_INT
}
#endif

/***************************************************************************/
// SPI Write (hardware interface)
/***************************************************************************/
#ifdef _spi95A_
/*
 #DOCLIST:spi_write_hw_dyn clib\spi\spi95A.htm

 @doc DOC_spi95A_
 ---------------------------------------------------------------
 SPI Write (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_write_hw | Write to the SPI Interface (hardware interface) |
        <cfont>unsigned int spi_write_hw ( const void far *bufferPtr,
        <tab><tab><tab><tab><tab><tab><tab>unsigned short nbytes );<efont> |
 @parm  void * | bufferPtr  | Pointer to buffer which contains write data
 @parm  int    | nbytes     | number of bytes to write
 @rdesc <ul>
         <li>1, if illegal arguments were passed
         <li>Else status bitmap:<ul>
          <li>BIT5 = 1: A collision has occurred between multiple masters<nl>
          <li>BIT6 = 1: An overrun was detected<ule><ule>
 @comm  Use this function if the hardware interface is used.<nl>
        Overrun detection only works if the SLVSEL pin is used as chipselect.
 @Also  spi90A.htm |  spi_init_hw |
        spi96A.htm |  spi_read_hw | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x95<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_write_hw_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00
 @target_clib V2.01
*/
unsigned int spi_write_hw (const void far *bufferPtr, unsigned short nbytes)
{
  // write data
  _ES = FP_SEG(bufferPtr);
  _SI = FP_OFF(bufferPtr);
  _CX = nbytes;
  _AH = SPI_WRITE;
  asm int SPI_INT
  return _AX;
}
#endif

/***************************************************************************/
// SPI Read
/***************************************************************************/
#ifdef _spi96_
/*
 #DOCLIST:spi_read_dyn clib\spi\spi96.htm

 @doc DOC_spi96_
 ---------------------------------------------------------------
 SPI Read
 ---------------------------------------------------------------
 @clib  spi_read | Read from the SPI Interface |
        <cfont>void spi_read ( void far *bufferPtr, unsigned short nbytes );<efont> |
 @parm  void * | bufferPtr  | Pointer to buffer where read data should be stored
 @parm  int    | nbytes     | number of bytes to read
 @rdesc  -- none --
 @Also  spi90.htm |  spi_init  |
        spi95.htm |  spi_write | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x96<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_read_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
 @target_clib V2.01
*/
void spi_read (void far *bufferPtr, unsigned short nbytes)
{
  // read data
  _ES = FP_SEG(bufferPtr);
  _DI = FP_OFF(bufferPtr);
  _CX = nbytes;
  _AH = SPI_READ;
  asm int SPI_INT
}
#endif

/***************************************************************************/
// SPI Read (hardware interface)
/***************************************************************************/
#ifdef _spi96A_
/*
 #DOCLIST:spi_read_hw_dyn clib\spi\spi96A.htm

 @doc DOC_spi96A_
 ---------------------------------------------------------------
 SPI Read (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_read_hw | Read from the SPI Interface (hardware interface)|
        <cfont>unsigned int spi_read_hw ( void far *bufferPtr, unsigned short nbytes );<efont> |
 @parm  void * | bufferPtr  | Pointer to buffer where read data should be stored
 @parm  int    | nbytes     | number of bytes to read
 @rdesc <ul>
         <li>1, if illegal arguments were passed
         <li>Else status bitmap:<ul>
          <li>BIT5 = 1: A collision has occurred between multiple masters<nl>
          <li>BIT6 = 1: An overrun was detected<ule><ule>
 @comm  Use this function if the hardware interface is used.<nl>
        Overrun detection only works if the SLVSEL pin is used as chipselect.
 @Also  spi90A.htm |  spi_init_hw  |
        spi95A.htm |  spi_write_hw | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x96<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_read_hw_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00
 @target_clib V2.01
*/
unsigned int spi_read_hw (void far *bufferPtr, unsigned short nbytes)
{
  // read data
  _ES = FP_SEG(bufferPtr);
  _DI = FP_OFF(bufferPtr);
  _CX = nbytes;
  _AH = SPI_READ;
  asm int SPI_INT
  return _AX;
}
#endif


/***************************************************************************/
// SPI Read and Write
/***************************************************************************/
#ifdef _spi97_
/*
 #DOCLIST:spi_read_write_dyn clib\spi\spi97.htm

 @doc DOC_spi97_
 ---------------------------------------------------------------
 SPI Read and Write
 ---------------------------------------------------------------
 @clib  spi_read_write | Read and write from the SPI Interface simultaneously |
        <cfont>void spi_read_write ( void far *rbufferPtr, const void far *wbufferPtr,
        <tab><tab><tab><tab><tab>&nbsp; unsigned short nbytes );<efont> |
 @parm  void * | rbufferPtr | Pointer to buffer where read data should be stored
 @parm  void * | wbufferPtr | Pointer to buffer which contains write data
 @parm  int    | nbytes     | number of bytes to read
 @rdesc  -- none --
 @Also  spi90.htm |  spi_init  |
        spi95.htm |  spi_write |
        spi96.htm |  spi_read
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x97<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_read_write_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
 @target_clib V2.01
*/
void spi_read_write (void far *rbufferPtr, const void far *wbufferPtr, unsigned short nbytes)
{
  // read and write data
  asm push ds
  _DS = FP_SEG(rbufferPtr);
  _DI = FP_OFF(rbufferPtr);
  _ES = FP_SEG(wbufferPtr);
  _SI = FP_OFF(wbufferPtr);
  _CX = nbytes;
  _AH = SPI_READ_WRITE;
  asm int SPI_INT
  asm pop ds
}
#endif


/***************************************************************************/
// SPI Read and Write (hardware interface)
/***************************************************************************/
#ifdef _spi97A_
/*
 #DOCLIST:spi_read_write_hw_dyn clib\spi\spi97A.htm

 @doc DOC_spi97A_
 ---------------------------------------------------------------
 SPI Read and Write (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_read_write_hw | Read and write from the SPI Interface simultaneously (hardware interface)|
        <cfont>unsigned int spi_read_write_hw ( void far *rbufferPtr,
        <tab><tab><tab><tab><tab><tab><tab><tab> const void far *wbufferPtr,
        <tab><tab><tab><tab><tab><tab><tab><tab> unsigned short nbytes );<efont> |
 @parm  void * | rbufferPtr | Pointer to buffer where read data should be stored
 @parm  void * | wbufferPtr | Pointer to buffer which contains write data
 @parm  int    | nbytes     | number of bytes to read
 @rdesc <ul>
         <li>1, if illegal arguments were passed
         <li>Else status bitmap:<ul>
          <li>BIT5 = 1: A collision has occurred between multiple masters<nl>
          <li>BIT6 = 1: An overrun was detected<ule><ule>
 @comm  Use this function if the hardware interface is used.<nl>
        Overrun detection only works if the SLVSEL pin is used as chipselect.
 @Also  spi90A.htm |  spi_init_hw  |
        spi95A.htm |  spi_write_hw |
        spi96A.htm |  spi_read_hw
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0x97<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_read_write_hw_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/
unsigned int spi_read_write_hw (void far *rbufferPtr, const void far *wbufferPtr, unsigned short nbytes)
{
  // read and write data
  asm push ds
  _DS = FP_SEG(rbufferPtr);
  _DI = FP_OFF(rbufferPtr);
  _ES = FP_SEG(wbufferPtr);
  _SI = FP_OFF(wbufferPtr);
  _CX = nbytes;
  _AH = SPI_READ_WRITE;
  asm int SPI_INT
  asm pop ds
  return _AX;
}
#endif


/***************************************************************************/
// Init SPI slave (hardware interface)
/***************************************************************************/
#ifdef _spiA0_
/*
 #DOCLIST:spi_slave_init_dyn clib\spi\spiA0.htm

 @doc DOC_spiA0_
 ---------------------------------------------------------------
 Init SPI slave (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_slave_init | Init the SPI Slave Interface (hardware interface) |
        <cfont>void spi_slave_init ( unsigned int mode );<efont> |
 @parm  unsigned int  | mode  | Combine the following defines with a bitwise OR to select the operation mode<nl><nl>
        SPI mode:<nl>
          <tab>set one of these: <cfont>SPI_MODE0, SPI_MODE1, SPI_MODE2 or SPI_MODE3<efont><nl>
        Open-Drain-Mode:<nl>
          <tab>select <cfont>SPI_OPEN_DRAIN<efont> for open-drain-mode,<nl>
          <tab>else output mode is used<nl>
        Invert chipselect:<nl>
          <tab>select <cfont>SPI_INVERT_CS<efont> to invert SLVSEL chipselect pin (active high),<nl>
          <tab>else do not invert SLVSEL pin (active low)<nl>
        Swap SDI and SDO:<nl>
          <tab>select <cfont>SPI_ALTERNATE_IO<efont> to swap SDI and SDO pins<nl>
 @comm  To use the SPI slave interface the user has to install an interrupt service routine
        for the SPI interrupt. An interrupt occurs when the SLVSEL pin transitions from active to inactive.<nl>
        <nl>
        A Wired-OR mode is provided which allows multiple masters to collide on the bus
        without risk of damage. In this mode, an external pull-up resistor is required
        on the Master Out Slave In (MOSI) and Master In Slave Out (MISO) pins.
        Generally, pull-ups are recommended on all of the external SPI signals to ensure
        they are held in a valid state, even when the SPI interface is disabled.<nl>
 @rdesc -- none --
 @Also  spiA5.htm |  spi_slave_write |
        spiA6.htm |  spi_slave_read  | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xA0<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_slave_init_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00
 @target_clib V2.01
*/
void spi_slave_init( unsigned mode )
{
  _BX = mode;
  _AH = SPI_SLAVE_INIT;
  asm int SPI_INT
}
#endif


/***************************************************************************/
// SPI Slave Write (hardware interface)
/***************************************************************************/
#ifdef _spiA5_
/*
 #DOCLIST:spi_slave_write_dyn clib\spi\spiA5.htm

 @doc DOC_spiA5_
 ---------------------------------------------------------------
 SPI Slave Write (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_slave_write | Write to the SPI Slave Interface (hardware interface) |
        <cfont>void spi_slave_write ( unsigned char data );<efont> |
 @parm  unsigned char    | data     | Data to write
 @rdesc -- none --
 @comm  Use this function if the hardware slave interface is used.
 @Also  spiA0.htm |  spi_slave_init |
        spiA6.htm |  spi_slave_read | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xA5<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_slave_write_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/
void spi_slave_write (unsigned char data)
{
  // write data
  _BL = data;
  _AH = SPI_SLAVE_WRITE;
  asm int SPI_INT
}
#endif

/***************************************************************************/
// SPI Slave Read (hardware interface)
/***************************************************************************/
#ifdef _spiA6_
/*
 #DOCLIST:spi_slave_read_dyn clib\spi\spiA6.htm

 @doc DOC_spiA6_
 ---------------------------------------------------------------
 SPI Slave Read (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_slave_read | Read from the SPI Slave Interface (hardware interface) |
        <cfont>unsigned char spi_slave_read ( void );<efont> |
 @rdesc Read data
 @comm  Use this function if the hardware slave interface is used.
 @Also  spiA0.htm |  spi_slave_init |
        spiA5.htm |  spi_slave_write | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xA6<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_slave_read_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00
 @target_clib V2.01
*/
unsigned char spi_slave_read (void)
{
  // read data
  _AH = SPI_SLAVE_READ;
  asm int SPI_INT
  return _AL;
}
#endif

/***************************************************************************/
// SPI Slave Read and Write (hardware interface)
/***************************************************************************/
#ifdef _spiA7_
/*
 #DOCLIST:spi_slave_read_write_dyn clib\spi\spiA7.htm

 @doc DOC_spiA7_
 ---------------------------------------------------------------
 SPI Slave Read and Write (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_slave_read_write | Read and write from the SPI Slave Interface simultaneously (hardware interface) |
        <cfont>unsigned char spi_slave_read_write ( unsigned char data );<efont> |
 @parm  unsigned char    | data     | Data to write
 @rdesc Read data
 @comm  Use this function if the hardware slave interface is used.
 @Also  spiA0.htm |  spi_slave_init  |
        spiA5.htm |  spi_slave_write |
        spiA6.htm |  spi_slave_read
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xA7<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_slave_read_write_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00
 @target_clib V2.01
*/
unsigned char spi_slave_read_write (unsigned char data)
{
  // read and write data
  _BL = data;
  _AH = SPI_SLAVE_READ_WRITE;
  asm int SPI_INT
  return _AL;
}
#endif

/***************************************************************************/
// SPI Wait on semaphore (hardware interface)
/***************************************************************************/
#ifdef _spiA8_
/*
 #DOCLIST:spi_waiton_sem_dyn clib\spi\spiA8.htm

 @doc DOC_spiA8_
 ---------------------------------------------------------------
 SPI Wait on semaphore (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_waiton_sem | Wait on the SPI semaphore (hardware interface) |
        <cfont>unsigned int spi_waiton_sem ( void );<efont> |
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  If multiple tasks use the SPI hardware master interface to access
        different slaves through different slave chip select PIO pins,
        this call should be used to synchronise the SPI activity on the bus.
        The external MMC/SD driver examples uses this call since version V1.02.
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xA8<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_waiton_sem_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00
 @target_clib V2.02
*/
unsigned int spi_waiton_sem (void)
{
  // wait on the semaphore
  _BX = 1;
  _AH = SPI_SEMAPHORE;
  asm int SPI_INT
  return _AX;
}
#endif

/***************************************************************************/
// SPI Release the semaphore (hardware interface)
/***************************************************************************/
#ifdef _spiA8A_
/*
 #DOCLIST:spi_release_sem_dyn clib\spi\spiA8A.htm

 @doc DOC_spiA8A_
 ---------------------------------------------------------------
 SPI Release the semaphore (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_release_sem | Release the SPI semaphore (hardware interface) |
        <cfont>unsigned int spi_release_sem ( void );<efont> |
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  If multiple tasks use the SPI hardware master interface to access
        different slaves through different slave chip select PIO pins,
        this call should be used to synchronise the SPI activity on the bus.
        The external MMC/SD driver examples uses this call since version V1.02.
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xA8<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_release_sem_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.91 | V1.00
 @target_clib V2.02
*/
unsigned int spi_release_sem (void)
{
  // release the semaphore
  _BX = 0;
  _AH = SPI_SEMAPHORE;
  asm int SPI_INT
  return _AX;
}
#endif

/***************************************************************************/
// SPI Wait on semaphore (hardware interface)
/***************************************************************************/
#ifdef _spiA8B_
/*
 #DOCLIST:spi_waiton_sem_setmode_dyn clib\spi\spiA8B.htm

 @doc DOC_spiA8B_
 ---------------------------------------------------------------
 SPI Wait on semaphore and set mode (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_waiton_sem_setmode | Wait on the SPI semaphore, set mode and divider (hardware interface) |
        <cfont>unsigned int spi_waiton_sem_setmode ( unsigned mode, unsigned div );<efont> |
 @parm  unsigned int  | mode  | Combine the following defines with a bitwise OR to select the operation mode<nl><nl>
        SPI mode:<nl>
          <tab>set one of these: <cfont>SPI_MODE0, SPI_MODE1, SPI_MODE2 or SPI_MODE3<efont><nl>
        Open-Drain-Mode:<nl>
          <tab>select <cfont>SPI_OPEN_DRAIN<efont> for open-drain-mode,<nl>
          <tab>else output mode is used<nl>
        Autodrive:<nl>
          <tab>select <cfont>SPI_AUTODRIVE<efont> to autodrive SLVSEL chipselect pin,<nl>
          <tab>works only together with SPI_ALTERNATE_IO<nl>
          <tab>else do not drive SLVSEL pin<nl>
        Invert chipselect:<nl>
          <tab>select <cfont>SPI_INVERT_CS<efont> to invert SLVSEL chipselect pin (active high),<nl>
          <tab>else do not invert SLVSEL pin (active low)<nl>
        Shift count:<nl>
          <tab>select the shift count with these defines:<nl>
          <tab><cfont>SPI_SHIFT1, SPI_SHIFT2, SPI_SHIFT3, SPI_SHIFT4,<efont><nl>
          <tab><cfont>SPI_SHIFT5, SPI_SHIFT6, SPI_SHIFT7, SPI_SHIFT8<efont><nl>
        Swap SDI and SDO:<nl>
          <tab>select <cfont>SPI_ALTERNATE_IO<efont> to swap SDI and SDO pins<nl>
 @parm  unsigned int  | div  | SPI speed clock divider (valid values: 0-65535)<nl>
         The SPI clock frequency is calculated with the formula:<nl>
         SPI freq = CPU freq / (divider*2+2)<nl>
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  If multiple tasks use the SPI hardware master interface to access
        different slaves through different slave chip select PIO pins,
        this call should be used to synchronise the SPI activity on the bus.
        The external MMC/SD driver examples uses this call since version V1.02.
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xA8<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_waiton_sem_setmode_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.05 | V1.00
 @target_clib V2.04
*/
unsigned int spi_waiton_sem_setmode ( unsigned mode, unsigned div )
{
  // wait on the semaphore and set mode
  _BX = 2;
  _CX = mode;
  _SI = div;
  _AH = SPI_SEMAPHORE;
  asm int SPI_INT
  return _AX;
}
#endif

/***************************************************************************/
// SPI Wait on semaphore with timeout (hardware interface)
/***************************************************************************/
#ifdef _spiA8C_
/*
 #DOCLIST:spi_waiton_sem_ext_dyn clib\spi\spiA8C.htm

 @doc DOC_spiA8C_
 ---------------------------------------------------------------
 SPI Wait on semaphore with timeout (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_waiton_sem_ext | Wait on the SPI semaphore with timeout (hardware interface) |
        <cfont>int spi_waiton_sem_ext ( long timeout, unsigned priority );<efont> |
 @parm  long  | timeout  | Maximum number of milliseconds to wait:<nl><nl>
        Zero -> Wait forever for semaphore<nl>
        Positive value -> Maximum number of milliseconds to wait for resource<nl>
        Negative value -> Polling mode, return immediately.<s2> If semaphore was
        not available the return value will be the -27 time-out indication.
 @parm  unsigned int | priority | The priority at which the caller wishes to wait
        (0 = highest).<s2> (Note that this priority has no connection to task priorities.)
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  If multiple tasks use the SPI hardware master interface to access
        different slaves through different slave chip select PIO pins,
        this call should be used to synchronise the SPI activity on the bus.
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xA8<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_waiton_sem_ext_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.53 | V1.53
 @target_clib V2.23
*/
int spi_waiton_sem_ext (long timeout, unsigned priority)
{
  // wait on the semaphore
  _ES = (unsigned int)(timeout >> 16);
  _DI = (unsigned int)(timeout);
  _DX = priority;
  _BX = 3;
  _AH = SPI_SEMAPHORE;
  asm int SPI_INT
  return _AX;
}
#endif


/***************************************************************************/
// SPI Wait on semaphore with timeout (hardware interface)
/***************************************************************************/
#ifdef _spiA8D_
/*
 #DOCLIST:spi_waiton_sem_setmode_ext_dyn clib\spi\spiA8D.htm

 @doc DOC_spiA8D_
 ---------------------------------------------------------------
 SPI Wait on semaphore with timeout and set mode (hardware interface)
 ---------------------------------------------------------------
 @clib  spi_waiton_sem_setmode_ext | Wait on the SPI semaphore with timeout, set mode and divider (hardware interface) |
        <cfont>int spi_waiton_sem_setmode_ext ( unsigned mode, unsigned div,<nl>
        <tab><tab><tab><tab><tab><tab><tab><tab> long timeout, unsigned priority );<efont> |
 @parm  unsigned int  | mode  | Combine the following defines with a bitwise OR to select the operation mode<nl><nl>
        SPI mode:<nl>
          <tab>set one of these: <cfont>SPI_MODE0, SPI_MODE1, SPI_MODE2 or SPI_MODE3<efont><nl>
        Open-Drain-Mode:<nl>
          <tab>select <cfont>SPI_OPEN_DRAIN<efont> for open-drain-mode,<nl>
          <tab>else output mode is used<nl>
        Autodrive:<nl>
          <tab>select <cfont>SPI_AUTODRIVE<efont> to autodrive SLVSEL chipselect pin,<nl>
          <tab>works only together with SPI_ALTERNATE_IO<nl>
          <tab>else do not drive SLVSEL pin<nl>
        Invert chipselect:<nl>
          <tab>select <cfont>SPI_INVERT_CS<efont> to invert SLVSEL chipselect pin (active high),<nl>
          <tab>else do not invert SLVSEL pin (active low)<nl>
        Shift count:<nl>
          <tab>select the shift count with these defines:<nl>
          <tab><cfont>SPI_SHIFT1, SPI_SHIFT2, SPI_SHIFT3, SPI_SHIFT4,<efont><nl>
          <tab><cfont>SPI_SHIFT5, SPI_SHIFT6, SPI_SHIFT7, SPI_SHIFT8<efont><nl>
        Swap SDI and SDO:<nl>
          <tab>select <cfont>SPI_ALTERNATE_IO<efont> to swap SDI and SDO pins<nl>
 @parm  unsigned int  | div  | SPI speed clock divider (valid values: 0-65535)<nl>
         The SPI clock frequency is calculated with the formula:<nl>
         SPI freq = CPU freq / (divider*2+2)<nl>
 @parm  long  | timeout  | Maximum number of milliseconds to wait:<nl><nl>
        Zero -> Wait forever for semaphore<nl>
        Positive value -> Maximum number of milliseconds to wait for resource<nl>
        Negative value -> Polling mode, return immediately.<s2> If semaphore was
        not available the return value will be the -27 time-out indication.
 @parm  unsigned int | priority | The priority at which the caller wishes to wait
        (0 = highest).<s2> (Note that this priority has no connection to task priorities.)
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  If multiple tasks use the SPI hardware master interface to access
        different slaves through different slave chip select PIO pins,
        this call should be used to synchronise the SPI activity on the bus.
        The external MMC/SD driver examples uses this call since version V1.02.
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../i2c_spi.htm#0xAA0xA8<linkmid>documentation<linktail>
        for more details.<nl>
        <nl>
        On SC1x3/SC2x (RTOS version <gt>=1.13, CLIB version <gt>=2.10) there's
        also a version of this function which uses dynamic linking instead of
        a software interrupt, which reduces the function's overhead and thus
        speeds up your application. This function's name is
        <cfont>spi_waiton_sem_setmode_dyn<efont>. You should however not use this function
        directly. Instead you should add the define <cfont>SPI_DYN_LINK<efont>
        to your program before including the CLIB's header file(s):<nl>
        <cfont>#define SPI_DYN_LINK<nl>
        #include <lt>clib.h<gt><efont><nl>
        This will map the original function's name to the dynamic linking
        version. This way you can also easily switch existing programs to
        dynamic linking.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.53 | V1.53
 @target_clib V2.23
*/
int spi_waiton_sem_setmode_ext ( unsigned mode, unsigned div,
                                 long timeout, unsigned priority )
{
  // wait on the semaphore and set mode
  _ES = (unsigned)(timeout >> 16);
  _DI = (unsigned)(timeout);
  _DX = priority;
  _BX = 4;
  _CX = mode;
  _SI = div;
  _AH = SPI_SEMAPHORE;
  asm int SPI_INT
  return _AX;
}
#endif


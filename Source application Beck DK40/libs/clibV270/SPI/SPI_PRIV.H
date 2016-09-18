/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module         : SPI_PRIV.H
* Function       : Private definitions for SPI API functions
* ---------------------------------------------------------------------------

$Header: SPI_PRIV.H, 8, 27.01.2006 16:46:41, Andre Pribil$

*****************************************************************************/


#ifndef SPI_PRIV_H
#define SPI_PRIV_H


/***************************************************************************/
// SPI API Function Numbers
/***************************************************************************/

#define SPI_INIT              0x90
#define SPI_WRITE             0x95
#define SPI_READ              0x96
#define SPI_READ_WRITE        0x97
#define SPI_SLAVE_INIT        0xA0
#define SPI_SLAVE_WRITE       0xA5
#define SPI_SLAVE_READ        0xA6
#define SPI_SLAVE_READ_WRITE  0xA7
#define SPI_SEMAPHORE         0xA8

/***************************************************************************/
// Interrupt Vectors
/***************************************************************************/
#define SPI_INT  0xAA


#endif  // SPI_PRIV_H


/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module    : HW_PRIV.H
* Function  : Internal definitions for HW API library
* ---------------------------------------------------------------------------

$Header: HW_PRIV.H, 8, 21.11.2006 13:43:39, Andre Pribil$

*****************************************************************************/


#ifndef HW_PRIV_H
#define HW_PRIV_H


/***************************************************************************/
// Hardware API Function Numbers
/***************************************************************************/
// PFE Services
#define PFE_ENABLE_DATA_BUS             0x80
#define PFE_ENABLE_NON_MULTI_ADDR_BUS   0x81
#define PFE_ENABLE_PIO                  0x82
#define PFE_ENABLE_PCS                  0x83
#define PFE_ENABLE_EXTERNAL_IRQ         0x84
#define PFE_ENABLE_EXTERNAL_TIMER       0x85
#define PFE_SET_EDGE_LEVEL_INTR_MODE    0x86
#define PFE_ENABLE_PWD                  0x87
#define PFE_ENABLE_EXTERNAL_DMA         0x88
#define PFE_ENABLE_INT_CASCADE_MODE     0x89
#define PFE_SET_WAIT_STATES             0x8A
#define PFE_SET_WAIT_STATES2            0x8B
#define PFE_SET_WAIT_STATES_UCS         0x8C
#define PFE_ENABLE_BUS_SIGNALS          0x8D
#define PFE_GET_VECTORS                 0x90

// HAL Services
#define HAL_SET_INT0_VECT               0x10
#define HAL_READ_DATA_BUS               0x80
#define HAL_WRITE_DATA_BUS              0x81
#define HAL_READ_PIO                    0x82
#define HAL_WRITE_PIO                   0x83
#define HAL_INSTALL_ISR                 0x84
#define HAL_INIT_TIMER                  0x85
#define HAL_START_TIMER                 0x86
#define HAL_STOP_TIMER                  0x87
#define HAL_READ_TIMER_COUNT            0x88
#define HAL_WRITE_TIMER_COUNT           0x89
#define HAL_GET_FREQUENCIES             0x8A
#define HAL_SET_DUTY_CYCLE_WAVEFORM     0x8B
#define HAL_READ_SPECIFIC_PIO           0x8C
#define HAL_WRITE_SPECIFIC_PIO          0x8D
#define HAL_GIVE_EOI                    0x8E
#define HAL_INIT_TIMER_EXT              0x8F
#define HAL_GET_SET_WATCHDOG_MODE       0x90
#define HAL_REFRESH_WATCHDOG            0x91
#define HAL_MASK_INT                    0x92
#define HAL_WRITE_PIO2                  0x93
#define HAL_WATCHDOG_MANAGER_SIGN_ON    0x94
#define HAL_WATCHDOG_MANAGER_REFRESH    0x95
#define HAL_WATCHDOG_MANAGER_SIGN_OFF   0x96
#define HAL_BLOCK_READ_DATA_BUS         0xA0
#define HAL_BLOCK_WRITE_DATA_BUS        0xA1
#define HAL_START_DMA                   0xB0
#define HAL_STOP_DMA                    0xB1
#define HAL_GET_DMA_INFO                0xB2
#define HAL_INIT_REST_NON_VOLATILE_DATA 0xC0
#define HAL_SAVE_NON_VOLATILE_DATA      0xC1
#define HAL_GET_REBOOT_REASON           0xC2
#define HAL_INSTALL_PFAILDONE_CALLBACK  0xC3


/***************************************************************************/
// Interrupt Vectors
/***************************************************************************/
#define PFE_INT  0xA2
#define HAL_INT  0xA1



#endif  // HW_PRIV_H


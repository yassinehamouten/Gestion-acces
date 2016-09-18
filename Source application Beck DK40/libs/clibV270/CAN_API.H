/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module      : CAN_API.H
* Function    : CAN Driver Application Programmers Interface
* ---------------------------------------------------------------------------

  $Header: c:\prjPib\IPC@CHIP\CLib\CAN_API.H, 8, 28.07.2006 15:15:28, Jack Gatrost$

*****************************************************************************/

#ifndef _CAN_API_H
#define _CAN_API_H

/////////////////////////////////////////////////////////////////////////////
//  CAN API constant definitions
/////////////////////////////////////////////////////////////////////////////

#define NUM_CAN_PORTS (2)       // Built into CPU
#define NUM_CAN_TX  (3)         // Each CAN device has 3 transmit registers

// All CAN baud specifications are in units [kHz]
#define CAN_BAUD_10K    (10)
#define CAN_BAUD_20K    (20)
#define CAN_BAUD_50K    (50)
#define CAN_BAUD_100K  (100)
#define CAN_BAUD_125K  (125)
#define CAN_BAUD_250K  (250)
#define CAN_BAUD_500K  (500)
#define CAN_BAUD_800K  (800)
#define CAN_BAUD_1M   (1000)

#define CAN_RX_Q_SIZE_MIN      (1)
#define CAN_RX_Q_SIZE_MAX      (500)

    // Note:  CAN Driver provides three Tx queues, one per Tx register set.
#define CAN_TX_Q_SIZE_MIN      (0)
#define CAN_TX_Q_SIZE_MAX      (500)

#define CAN0_PORT  (0)
#define CAN1_PORT  (1)

#define CAN_TX1    (0)
#define CAN_TX2    (1)
#define CAN_TX3    (2)

// If CAN_TX_PRIORITY_QUEUES mode was selected in CAN_CONFIG,
// then following two transmit indexes apply:
#define CAN_TX_NORMAL  (0)      // Normal priority transmit
#define CAN_TX_HIGH    (1)      // Higher priority transmit

// Receiver filter references, 'filter_idx' parameter to CAN_Rx_Filters()
#define CAN_FILT1    (0)
#define CAN_FILT2    (1)
#define CAN_FILT3    (2)

// CAN API error codes
#define CAN_EC_SUCCESS               (0)    // No problem
#define CAN_EC_INVALID_PARAMS       (-1)
#define CAN_EC_INVALID_BAUD         (-2)
#define CAN_EC_PORT_NOT_OPENED      (-3)
#define CAN_EC_PORT_ALREADY_OPENED  (-4)
#define CAN_EC_NO_BUF_SPACE         (-5)    // Queue full
#define CAN_EC_TIMEOUT              (-6)
#define CAN_EC_LOW_RESOURCES        (-7)
#define CAN_EC_NO_SUCH_SERVICE      (-8)    // Invalid service index in AH
#define CAN_EC_INVALID_Q_SIZE       (-9)
#define CAN_EC_LOW_MEMORY           (-10)   // Ring buffer alloc failed
#define CAN_EC_BUS_OFF              (-11)


/////////////////////////////////////////////////////////////////////////////
//  Bit assigments for CAN event group
/////////////////////////////////////////////////////////////////////////////
    // CAN_EV_... "EV" = Event Bits for signaling events.
    // CAN0
#define CAN0_EV_RX_RDY      (0x0001)    // Receiver data ready
#define CAN0_EV_TX1_EMP     (0x0002)    // TX1 reg and queue empty
#define CAN0_EV_TX2_EMP     (0x0004)    // TX2 reg and queue empty
#define CAN0_EV_TX3_EMP     (0x0008)    // TX3 reg and queue empty
#define CAN0_EV_TX_ANY      (0x000E)    // TX1, TX2 or TX3
#define CAN0_EV_BUS_OFF     (0x0010)    // Bus off condition
    // CAN1
#define CAN1_EV_RX_RDY      (0x0100)    // Receiver data ready
#define CAN1_EV_TX1_EMP     (0x0200)    // TX1 reg and queue empty
#define CAN1_EV_TX2_EMP     (0x0400)    // TX2 reg and queue empty
#define CAN1_EV_TX3_EMP     (0x0800)    // TX3 reg and queue empty
#define CAN1_EV_TX_ANY      (0x0E00)    // TX1, TX2 or TX3
#define CAN1_EV_BUS_OFF     (0x1000)    // Bus off condition

// Tx/Rx control selection flags for CAN_Control() parameters:
//   enables, disables. purge_fifos
// and CAN_Status() CAN_STATUS.Device_Enable
#define CAN_RX_SEL   (0x8000)   // Receiver control flag
#define CAN_TX1_SEL  (0x0800)   // TX1 reg control flag
#define CAN_TX2_SEL  (0x1000)   // TX2 reg control flag
#define CAN_TX3_SEL  (0x2000)   // TX3 reg control flag
#define CAN_ALL_TX_SEL (CAN_TX1_SEL | CAN_TX2_SEL | CAN_TX3_SEL)

/////////////////////////////////////////////////////////////////////////////
//  Masks for CAN_Set_Callback() events
/////////////////////////////////////////////////////////////////////////////
#define CAN_CALLBACK_RX     (CAN0_EV_RX_RDY  | CAN1_EV_RX_RDY)
#define CAN_CALLBACK_TX     (CAN0_EV_TX_ANY  | CAN1_EV_TX_ANY)
#define CAN_CALLBACK_ERR    (CAN0_EV_BUS_OFF | CAN1_EV_BUS_OFF)
#define CAN_CALLBACK_ALL    (0xFFFF)

/////////////////////////////////////////////////////////////////////////////
//    Data Types
/////////////////////////////////////////////////////////////////////////////

typedef int CAN_BOOL ;              // Booleans, TRUE/FALSE

typedef struct CAN_ID_
{
    unsigned int    Normal ;        // 11 bit ID left justified,
    unsigned int    Extended ;      // Additional for 29 bit ID
} CAN_ID ;

// CAN_RX_FILT.Id_Mask bits which apply to CAN_ID.Extended word
#define CAN_FILT_IDE    (0x4)   // Extended ID (29 bit)
#define CAN_FILT_RTR    (0x2)   // Remote Transmit Request

typedef struct CAN_RX_FILT_
{
    // Mask 1 bits = Don't care 
    // Mask 0 bits = Must match specified values
    CAN_ID          Id_Mask ;       // 
    unsigned int    Data_Mask ;     // 2 byte data mask
    CAN_ID          Id_Value ;      // 
    unsigned int    Data_Value ;    // 2 byte data mask

} CAN_RX_FILT ;

typedef struct CAN_CONFIG_
{
    unsigned int    Baud ;          // In KHz
    unsigned int    Mode ;          // Bit field, options defined below.
    // For Mask and Value, see CAN_CFG_* defines below.
    unsigned int    Mask ;          // Bits to be affected
    unsigned int    Value ;         // Values to apply under mask.
    unsigned int    Bit_Rate_Div ;  // B10:B0 = (Clk prescaler - 1)
    // Bit_Rate_Div is ignored unless all the CAN_CFG_TSEG2_MASK
    //  and CAN_CFG_TSEG2_MASK bits are set in above Config_Mask word.
} CAN_CONFIG ;

// Mode bit assignments for CAN_CONFIG.Mode
#define CAN_PASSIVE_MODE        (0x2)
#define CAN_LOOP_BACK_MODE      (0x4)
#define CAN_TXQ1_DRIVES_ALL     (0x8)
#define CAN_TX_PRIORITY_QUEUES  (0x10)

// Option bits for CAN_CONFIG Mask and Value
#define CAN_CFG_OVERWRITE_LAST_MESSAGE (0x8000)
#define CAN_CFG_TSEG2_MASK             (0x7000)
#define CAN_CFG_TSEG1_MASK             (0x0F00)
#define CAN_CFG_AUTO_RESTART           (0x0010)
#define CAN_CFG_SYNC_JMP_WIDTH         (0x000C)
#define CAN_CFG_RX_SAMPLE_3_POINTS     (0x0002)
#define CAN_CFG_RX_EDGE_SYNC_MODE      (0x0001)
   
typedef struct CAN_PORT_INIT_
{
    CAN_BOOL        fDisable_Rx ;   // Initially disable Recvr
    CAN_CONFIG      Config ;        // Configuration Reg settings
    unsigned int    Rx_Q_Size ;     // Number of CAN msgs
    unsigned int    Tx_Q_Size[NUM_CAN_TX] ;
} CAN_PORT_INIT ;

typedef struct CAN_STATUS_
{
    CAN_BOOL        fPort_Opened ;  // TRUE if port is now open
    unsigned long   Baud ;          // In Hertz
    unsigned int    Device_Enable ; // Bit field for Rx & 3 Tx.
    unsigned int    Errors ;        // Bit field
    unsigned int    Rx_Count ;      // Messages in ring buffer
    unsigned int    Tx_Count[NUM_CAN_TX] ;

} CAN_STATUS ;

// Bit definitions for CAN_STATUS.Errors
#define CAN_ARBLOSS     0x0004      // Arbitration lost during tx
#define CAN_OVRLOAD     0x0008      // Overload condition
#define CAN_RX_OVR_ERR  0x0010      // Receiver overrun in hardware
#define CAN_BIT_ERR     0x0020      // Bit error during tx or rx
#define CAN_STUF_ERR    0x0040      // Stuffing error during tx or rx
#define CAN_ACK_ERR     0x0080      // Ack error during tx or rx
#define CAN_FORM_ERR    0x0100      // Format error during tx or rx
#define CAN_CRC_ERR     0x0200      // CRC error during tx or rx
#define CAN_BUS_OFF     0x0400      // CAN is in bus off state
#define CAN_SW_RX_OVR   0x0800      // Software Rx ring buffer overflow.

#define HW_ERR_REPORT_MASK (0x07FC) // Bits in Interrupt Flag register

typedef struct CAN_ERRORS_
{
    unsigned char   TxErrCnt ;      // Bosch defined Tx Error Count
    unsigned char   RxErrCnt ;      // Bosch defined Rx Error Count

    unsigned int    BusStatus ;     // Bit field, see CAN_BS_* masks below.

} CAN_ERRORS ;

#define CAN_BS_RX96     (0x0008)        // Rx error counter >= 96
#define CAN_BS_TX96     (0x0004)        // Tx error counter >= 96
#define CAN_BS_BUS_OFF  (0x0002)        // Bus off flag
#define CAN_BS_PASSIVE  (0x0001)        // Error passive state (if not bus off)


typedef struct CAN_MSG_
{
    CAN_ID          Id ;        // 11 or 29 bit identifier
    unsigned char   Data[8] ;   // 0..8 bytes data
    unsigned int    Len_Ctrl ;  // Data Length Count, [0..8] and some flags
        
} CAN_MSG ;

// Masks for Len_Ctrl word for CAN_Recv() or CAN_Send()
#define CAN_DLC_FIELD  (0x000F) // Data Length Count, [0..8]
#define CAN_IDE_FLAG   (0x0010) // Extended (29 bit) ID flag
#define CAN_RTR_FLAG   (0x0020) // Remote Request flag
// Following bits in Len_Ctrl apply to CAN_Recv() only
#define CAN_RX_AF1     (0x0100) // Received through acceptance filter 1
#define CAN_RX_AF2     (0x0200) // Received through acceptance filter 2
#define CAN_RX_AF3     (0x0400) // Received through acceptance filter 3
// User RX callback can set the CAN_RX_DISCARD bit in Len_Ctrl to discard msg.
#define CAN_RX_DISCARD (0x8000) // Callback setting to filter out a msg.


// CAN ISR callback type
typedef void huge (*CAN_ISR_CALLBACK)(unsigned int       event, 
                                      const CAN_MSG far *msg) ;


/////////////////////////////////////////////////////////////////////////////
//    Prototypes
/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif

int far _cdecl CAN_Open_Port (unsigned int             port_idx, 
                              const CAN_PORT_INIT far *init) ;

int far _cdecl CAN_Rx_Filters (unsigned int           port_idx, 
                               unsigned int           filter_idx,
                               const CAN_RX_FILT far *filt) ;

int far _cdecl CAN_Send (unsigned int       port_idx, 
                         unsigned int       channel,
                         const CAN_MSG far *msg) ;

int far _cdecl CAN_Recv (unsigned int  port_idx, 
                         CAN_MSG  far *msg, 
                         int           timeout) ;

int far _cdecl CAN_Peek (unsigned int  port_idx, 
                         CAN_MSG  far *msg) ;

int far _cdecl CAN_Reconfig (unsigned int          port_idx, 
                             const CAN_CONFIG far *config) ;

int far _cdecl CAN_Status (unsigned int port_idx, CAN_STATUS far *sts) ;

int far _cdecl CAN_Error_Counts (unsigned int port_idx, 
                                 CAN_ERRORS far *errors) ;

int far _cdecl CAN_Control (unsigned int port_idx, 
                            unsigned int enables, 
                            unsigned int disables, 
                            unsigned int purge_fifos) ;

int far _cdecl CAN_Close_Port (unsigned int port_idx) ;

unsigned int far _cdecl CAN_Event_Sleep (unsigned int events, int timeout) ;

int far _cdecl CAN_Set_Callback(unsigned int     port_idx,
                                CAN_ISR_CALLBACK vector,
                                unsigned int     events) ;

#ifdef __cplusplus
}
#endif

#endif // _CAN_API_H

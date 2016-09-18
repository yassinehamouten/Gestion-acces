/****************************************************************************
* (C) 1999-2011 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module        : CAN.C
* Function      : CAN bus driver API
* ---------------------------------------------------------------------------

$Header: CAN.C, 26, 12.11.2008 12:50:54, Andre Pribil$

****************************************************************************/


/************************************************************************/
// Includes
/************************************************************************/
#include <DOS.H>

#include <config.h>
#include <CAN_API.H>

///////////////////////////////////////////////////////////////////////
//  Software Interrupt and service indexes (AH contents)
///////////////////////////////////////////////////////////////////////
#define CAN_SWI   (0xBF)                    // Shared with USB API

#define CAN_API_START  (0x80)               // Shared with USB

#define CAN_API_DYN_LINK    (CAN_API_START + 0)
#define CAN_API_OPEN        (CAN_API_START + 1)
#define CAN_API_RX_FILT     (CAN_API_START + 2)
#define CAN_API_SEND        (CAN_API_START + 3)
#define CAN_API_RCV         (CAN_API_START + 4)
#define CAN_API_PEEK        (CAN_API_START + 5)
#define CAN_API_RECONFIG    (CAN_API_START + 6)
#define CAN_API_STATUS      (CAN_API_START + 7)
#define CAN_API_CONTROL     (CAN_API_START + 8)
#define CAN_API_CLOSE       (CAN_API_START + 9)
#define CAN_API_EVENT       (CAN_API_START + 0xA)
#define CAN_API_CALLBACK    (CAN_API_START + 0xB)
#define CAN_API_ERRORS      (CAN_API_START + 0xC)


/*
 // Note:  The DOCLIST.EXE tool used by the C-Library HTML build process reacts
 //  to the token "#DOCLIST:" when it appears as the first non-white space
 //  on a line.  The tool transfers the text which follows into the 
 //  BeckCLib.LST file that is used for the context sensitive help.
 //
 // Another Note:  The *CAN indicates that any names that start with
 //      CAN and do not match any other name in our list should lead
 //      to the HTM page stated after the *CAN.
 //
 #DOCLIST:*CAN CLIB\CAN\lib_index.htm
 #DOCLIST:CAN_BOOL canstruc.htm#CAN_BOOL
 #DOCLIST:CAN_CONFIG canstruc.htm#CAN_CONFIG
 #DOCLIST:CAN_ID canstruc.htm#CAN_ID
 #DOCLIST:CAN_MSG canstruc.htm#CAN_MSG
 #DOCLIST:CAN_PORT_INIT canstruc.htm#CAN_PORT_INIT
 #DOCLIST:CAN_RX_FILT canstruc.htm#CAN_RX_FILT
 #DOCLIST:CAN_STATUS canstruc.htm#CAN_STATUS
 #DOCLIST:CAN_ERRORS canstruc.htm#CAN_ERRORS


 @doc DOC_INDEX
 ---------------------------------------------------------------
 CAN Bus Driver API Table of Contents
 ---------------------------------------------------------------
 @clibidx  <tab><cfont>#include <InBraces CAN_API\.H><efont><nl>
     |
 The CLIB API definition for sending and receiving data on 
 the CAN (Controller Area Network) buses is defined here.<s2> <bold>
 This API is only available in the SC1x3/SC2x @CHIP-RTOS.<bolde><nl>
 <nl>
 The SC1x3/SC2x offers two CAN bus channels which can be operated with this API.<nl>
 <nl>Each CAN channel has three hardware transmit
 registers and a four CAN message deep hardware receiver FIFO.<s2> The CAN
 driver provides send and receive software FIFO's with user specified sizes
 around each of these hardware devices.<nl>
 <nl>
 One required step in using the CAN ports is to call the 
 <linkto>can01.htm<linkmid>CAN_Open_Port()<linktail> function,
 which configures the port for a specific baud rate and sets
 the driver's software FIFO sizes.<nl>
 <nl>In hardware, each receive channel offers three configurable
 receiver filters which can be used to reduce the load placed on the
 CPU by the CAN receivers.<s2> These registers are configured
 with the <linkto>can02.htm<linkmid>CAN_Rx_Filters()<linktail> 
 function.
 
 @textlinkpara  CAN API | ../../canstruc.htm | Data Structures  |
 @textlinkpara  CAN API | ../../canerr.htm | Error Codes |
 
 @libcat1  Configuration | can01 | CAN_Open_Port | Open specified CAN port |
 @libcat1  Configuration | can02 | CAN_Rx_Filters | Configure receive filters |
 @libcat1  Configuration | can06 | CAN_Reconfig | Reconfigure CAN port |
 @libcat1  Configuration | can08 | CAN_Control | Enable, disable and purge |
 @libcat1  Configuration | can09 | CAN_Close_Port | Shut down specified CAN port |

 @libcat2  Transmit | can03 | CAN_Send | Output a CAN message |

 @libcat3  Receive | can04 | CAN_Recv | Pickup a received CAN message |
 @libcat3  Receive | can05 | CAN_Peek | Look at received CAN message, leave in queue |

 @libcat4  Status | can07 | CAN_Status | Check port status |
 @libcat4  Status | can0C | CAN_Error_Counts | Check port error counts |
 @libcat4  Status | can0A | CAN_Event_Sleep | Sleep until port event occurs |
 @libcat4  Status | can0B | CAN_Set_Callback | Install/Remove ISR callback |
*/

#ifdef _can01_
/*
 @doc DOC_can01_
 ---------------------------------------------------------------
 Open CAN port
 ---------------------------------------------------------------
 @clib  CAN_Open_Port | Open one of the CAN ports. |
        int CAN_Open_Port ( unsigned int port_idx,<nl> |
        <tab>const CAN_PORT_INIT far *init );
 @parm  int  | port_idx | CAN port specifier:<s2>
 <cfont>CAN0_PORT<efont> = 0, or <cfont>CAN1_PORT<efont> = 1
 @parm  int  | init | Pointer to port initialization data
   <linkto>../../canstruc.htm#CAN_PORT_INIT<linkmid>structure<linktail>
   set by caller.
 @rdesc <linkto>../../canerr.htm<linkmid>Error<linktail> code -<nl>
        <cfont>CAN_EC_SUCCESS<efont> = 0:<s2> Success, CAN port opened.<nl>
        <cfont>CAN_EC_INVALID_PARAMS<efont> =  -1:<s2>
           <cfont>port_idx<efont> invalid or NULL <cfont>init<efont> pointer<nl>
        <cfont>CAN_EC_INVALID_BAUD<efont> = -2:<s2> Invalid baud rate
           or bit timing specification.<nl>
        <cfont>CAN_EC_PORT_ALREADY_OPENED<efont> = -4:<s2>  Specified port was already opened<nl>
        <cfont>CAN_EC_LOW_RESOURCES<efont> = -7:<s2>  Unable to create required event group.<nl>
        <cfont>CAN_EC_INVALID_Q_SIZE<efont> = -9:<s2>  One of the queue sizes was invalid.<nl>
        <cfont>CAN_EC_LOW_MEMORY<efont> = -10:<s2>  Unable to allocate heap memory.<nl>
 @comm
    Either this function or the <linkto>can02.htm<linkmid>CAN_Rx_Filters<linktail>
   (required in order to receive any CAN messages) would be the starting point
   in preparing a CAN port for use.<s2>
   This function allocates receive and send FIFOs per the caller's
   <linkto>../../canstruc.htm#Rx_Q_Size<linkmid>FIFO size<linktail>
   specifications.<s2> The CAN port is initialized for operation at the
   specified <linkto>../../canstruc.htm#Baud<linkmid>baud<linktail>
   rate.<s2> An RTX <linkto>../RTX/rtx40.htm<linkmid>event group<linktail>
   is allocated if this action has not already been taken for the adjacent CAN port.<s2>
   (The driver uses a single RTX event group for the CAN port pair.)<nl>
   <nl>
   No operation is performed if the port has already been opened.<s2> In this
   case an error code <cfont>CAN_EC_PORT_ALREADY_OPENED<efont> is returned.<s2>
   If necessary, limited configuration changes on an open CAN port can be made
   with the <linkto>can06.htm<linkmid>CAN_Reconfig<linktail> API.<nl>
   <nl>
    Inside this API the interrupts are masked for a short period and then
    re-enabled.<s2> This function is reentrant.<nl>
    <nl>
    When CAN1 is opened, the PIO14 and PIO15 are configured for NORMAL
    operation.<nl>
    <nl>
    <bold>Important Note:<bolde><nl>
    <nl><ul>
    No CAN messages will be received until the port's receiver
    filters have been enabled for reception using the
    <linkto>can02.htm<linkmid>CAN_Rx_Filters<linktail> API.<s2>
    Following a system reset, the CAN receiver filters are initialized
    to reject all incoming CAN messages by default.
    <ule>
 @Also  can02.htm | CAN_Rx_Filters  |
        can09.htm | CAN_Close_Port |
        can06.htm | CAN_Reconfig
 @rtos  This library function uses a
    <linkto>../../canswi.htm#0xBF0x80<linkmid>dynamic<linktail>
      link to reach the <linkto>../../canswi.htm#0xBF0x81<linkmid>service<linktail>
      offered by RTOS software
      <linkto>../../canswi.htm<linkmid>interrupt<linktail>.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.07 | V1.00

 @target_clib V2.01
*/

/*************************************************************************/
//                 Open CAN port
/*************************************************************************/
int far _cdecl CAN_Open_Port (unsigned int port_idx,
                              const CAN_PORT_INIT far *init)
{
    _DX = port_idx ;
    _ES = FP_SEG(init);
    _BX = FP_OFF(init);
    _AH = CAN_API_OPEN ;

    asm int CAN_SWI ;

    return _AX ;
}
#endif


#ifdef _can02_
/*
 @doc DOC_can02_
 ---------------------------------------------------------------
 Open CAN port
 ---------------------------------------------------------------
 @clib  CAN_Rx_Filters | Initialize a receiver filter. |
        int CAN_Rx_Filters ( unsigned int port_idx, |
        <tab><s1>unsigned int           filter_idx,<nl>
        <tab><s1>const CAN_RX_FILT far *filt);
 @parm  int  | port_idx | CAN port specifier:<s2>
 <cfont>CAN0_PORT<efont> = 0, or <cfont>CAN1_PORT<efont> = 1
 @parm  int  | filter_idx | Receiver filter specifier:<nl><ul>
    <cfont>CAN_FILT1<efont> = 0<nl>
    <cfont>CAN_FILT2<efont> = 1<nl>
    <cfont>CAN_FILT3<efont> = 2<nl>
    <ule>
 @parm  int  | filt | Pointer to 
        <linkto>../../canstruc.htm#CAN_RX_FILT<linkmid>filter<linktail>
        initialization data structure set by caller.<s2> This may be
        set to NULL to disable the respective receiver filter so that
        no CAN messages are accepted by the filter.
 @rdesc <linkto>../../canerr.htm<linkmid>Error<linktail> code -<nl>
        <cfont>CAN_EC_SUCCESS<efont> = 0:<s2> Success<nl>
        <cfont>CAN_EC_INVALID_PARAMS<efont> = -1:<s2> <cfont>port_idx<efont> or
           <cfont>filter_idx<efont> invalid<nl>
 @comm      
    <bold><i>This function must be called<bolde><ie> in order to receive any CAN
    messages on respective port.<s2> If all three hardware message filters are
    disabled, no messages are received.<s2> This is the default condition
    following a reset.<nl>
    <nl>
    This function is used to initialize one of the CAN receiver's 
        three sets of acceptance filter registers.<s2>  The receiver 
        acceptance filters may be used to limit the incoming message 
        traffic to those CAN messages which apply to this node in the network.
        <nl><nl>
    <bold>Note:<bolde><nl>
    <ul>
       The receiver callbacks installed with the 
       <linkto>can0B.htm<linkmid>CAN_Set_Callback()<linktail> API may also
       be used to filter out received CAN messages before the ISR 
       registers them into the receiver queue.
    <ule>
    To receive all messages, one message filter must be enabled
    and programmed with all its fields as "don't care" ('1's).<nl>
    <nl>
        This function may be used either before or after the respective
        CAN port has been <linkto>can01.htm<linkmid>opened<linktail>.<nl>
    <nl>
    Inside this API the interrupts are masked for a short period and then
    re-enabled.<s2> This function is reentrant.

 @Also  can01.htm | CAN_Open_Port  |
         | | |
 @rtos  This library function uses a 
    <linkto>../../canswi.htm#0xBF0x80<linkmid>dynamic<linktail>
      link to reach the <linkto>../../canswi.htm#0xBF0x82<linkmid>service<linktail>
      offered by RTOS software 
      <linkto>../../canswi.htm<linkmid>interrupt<linktail>.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/

/*************************************************************************/
//                 Open CAN port
/*************************************************************************/
int far _cdecl CAN_Rx_Filters (unsigned int           port_idx, 
                               unsigned int           filter_idx,
                               const CAN_RX_FILT far *filt)
{
    _DX = port_idx ;
    _CX = filter_idx ;
    _ES = FP_SEG(filt);
    _BX = FP_OFF(filt);
    _AH = CAN_API_RX_FILT ;

    asm int CAN_SWI ;

    return _AX ;
}
#endif


#ifdef _can03_
/*
 @doc DOC_can03_
 ---------------------------------------------------------------
 Send message out CAN port
 ---------------------------------------------------------------
 @clib  CAN_Send | Queue a CAN message for transmission. |
        int CAN_Send (<s1> unsigned int port_idx, |
        unsigned int       channel,<nl>
        const CAN_MSG far *msg );
 @parm  int  | port_idx | CAN port specifier:<s2>
 <cfont>CAN0_PORT<efont> = 0, or <cfont>CAN1_PORT<efont> = 1
 @parm  int  | channel | Transmit register specifier:<nl><ul>
    <cfont>CAN_TX1<efont> = 0<nl>
    <cfont>CAN_TX2<efont> = 1<nl>
    <cfont>CAN_TX3<efont> = 2<nl>
    <ule>
    <nl>
    or when operating in 
    <linkto>../../canstruc.htm#CAN_TX_PRIORITY_QUEUES<linkmid>CAN_TX_PRIORITY_QUEUES<linktail>
    mode:<nl><ul>
        <cfont>CAN_TX_NORMAL<efont> = 0<nl>
        <cfont>CAN_TX_HIGH<efont> = 1<nl>
        (2 works same as CAN_TX_HIGH here)<nl>
    <ule>
 @parm  int  | msg | Pointer to a 
        <linkto>../../canstruc.htm#CAN_MSG<linkmid>CAN_MSG<linktail>
        data structure holding contents of CAN message to be
        transmitted, set by caller.
 @rdesc <linkto>../../canerr.htm<linkmid>Error<linktail> code:<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_SUCCESS<efont> = 0:<s2> Success, message has been
        transferred into specified transmit queue.<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_INVALID_PARAMS<efont> = -1:<s2> <cfont>port_idx<efont>,
           <cfont>filter_idx<efont> invalid 
           or NULL <cfont>msg<efont> pointer.<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_PORT_NOT_OPENED<efont> = -3:<s2>Port has not been
        <linkto>can01.htm<linkmid>opened<linktail>.<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_NO_BUF_SPACE<efont> = -5:<s2> Transmit queue for this
        output channel is full, message not accepted.<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_BUS_OFF<efont> = -11: "Bus Off" state due to transmit
            or receive errors.<nl>
 @comm  
    Three different modes of operation are available for the CAN
    transmission, selected at the
    <linkto>can01.htm<linkmid>CAN_Open_Port<linktail> API call:<nl>
    <nl>
    <ol>
    <li><bold>Default mode<bolde><nl>
    <nl>
    This mode uses three transmit software FIFO queues, where each FIFO 
    feeds a specific hardware transmit register.<s2>  The size of
    each FIFO is configurable.
    <nl>
    <lie>
    <bold><li>CAN_TX_PRIORITY_QUEUES Mode<bolde><nl>
    <nl>
    This mode is selected by setting the <cfont>CAN_TX_PRIORITY_QUEUES<efont>
    bit in the <linkto>../../canstruc.htm#CAN_CONFIG<linkmid>CAN_CONFIG<linktail>
    structure's <cfont>Mode<efont> word.<s2>
    In this mode two transmit FIFO's are used, one with normal
    priority and one with high priority.<s2> The size of the
    normal priority queue is specified by the 
    <cfont>Tx_Q_Size[CAN_TX_NORMAL]<efont> value in the
    <linkto>../../canstruc.htm#CAN_PORT_INIT<linkmid>CAN_PORT_INIT<linktail>
    structure at the <linkto>can01.htm<linkmid>CAN_Open_Port<linktail> call.<s2>
    The high priority queue size is specified here with the 
    <cfont>Tx_Q_Size[CAN_TX_HIGH]<efont> value.<nl>
    <lie><nl>
    <bold><li>CAN_TXQ1_DRIVES_ALL Mode<bolde><nl>
    <nl>
    This mode is selected by setting the <cfont>CAN_TXQ1_DRIVES_ALL<efont>
    bit in the <linkto>../../canstruc.htm#CAN_CONFIG<linkmid>CAN_CONFIG<linktail>
    structure's <cfont>Mode<efont> word.<s2>
    In this mode, a single queue feeds more than one of the 
    hardware transmit registers.<s2>  If a queue size  of zero
    is specified for channels <cfont>CAN_TX2<efont> and
    <cfont>CAN_TX3<efont>, then the respective hardware transmit
    registers will be fed from the common FIFO.<s2> If both
    the <cfont>Tx_Q_Size[CAN_TX2]<efont> and <cfont>Tx_Q_Size[CAN_TX3]<efont>
    values in the 
    <linkto>../../canstruc.htm#CAN_PORT_INIT<linkmid>CAN_PORT_INIT<linktail>
    structure are zero when <linkto>can01.htm<linkmid>CAN_Open_Port<linktail>
    is called, then the single FIFO whose size was specified by
    <cfont>Tx_Q_Size[CAN_TX1]<efont> drives all three hardware
    transmit channels.
    <nl>
    <lie>
    <ole>
    <bold>Comments General to All Operation Modes<bolde><nl>
    <nl>
    The <cfont>CAN_Send()<efont> function either places the provided
    CAN message directly into the hardware register when there is no 
    message currently pending output already in this register, or into
    the software ring buffer queue.<s2>
    When no more space is available in the output queue, an error code
    <cfont>CAN_EC_NO_BUF_SPACE<efont> is returned and no operation is
    performed.<nl>
    <nl>
    The driver feeds the output queues into the hardware transmit 
    registers in an interrupt driven fashion.<s2>   The hardware 
    prioritizes the three transmit registers based on "first recessive
    bit" logic, similar to that used for normal CAN bus arbitration.<s2>
    However in this case, the "arbitration" is performed internally prior 
    to presentation of the outgoing CAN message on the bus.<s2>
    This priorization mechanism can lead to transmission which is not done
    in FIFO order for the operational modes which drive more than one
    hardware transmit register from a single FIFO.<nl>
    <nl>
    Inside this API the interrupts are masked for a short period and then
    re-enabled.<s2> This function is reentrant.<nl>
    <nl>
    If the <cfont>CAN_EC_BUS_OFF<efont> error is returned and the port
      has been configured with the 
      <linkto>../../canstruc.htm#AUTO_RESTART<linkmid>CAN_CFG_AUTO_RESTART<linktail>
      flag reset, then the 
      <linkto>can06.htm<linkmid>CAN_Reconfig()<linktail> API
      call will be required to restart the bus.<nl>
    <nl>

    <bold>Comments on Default Mode<bolde><nl>
    <nl>
    The CAN driver provides three queues for outgoing CAN messages.<s2>
    Each queue is fed into one of the three hardware transmit registers 
    provided by the CAN device.<nl>
    <nl>
    The output queues can be loaded with this API prior to
    enabling the respective hardware transmit register.<s2> In this
    case no output from this channel will occur until the channel
    is enabled with the appropriate channel enable command to the 
    <linkto>can08.htm<linkmid>CAN_Control()<linktail> function.<nl>
    <nl>
    <bold>Comments on CAN_TX_PRIORITY_QUEUES Mode<bolde><nl>
    <nl>
    The <cfont>CAN_TX_PRIORITY_QUEUES<efont>
    option bit in the 
    <linkto>../../canstruc.htm#CAN_CONFIG<linkmid>CAN_CONFIG<linktail> 
    <cfont>Mode<efont> word selects this mode.<s2> CAN messages from the 
    <cfont>CAN_TX_NORMAL<efont> queue
    will only be loaded into the CAN hardware transmit registers
    when the <cfont>CAN_TX_HIGH<efont> queue is empty.<s2>  The
    CAN messages in the <cfont>CAN_TX_HIGH<efont> queue are higher
    priority and will be loaded before those in the 
    <cfont>CAN_TX_NORMAL<efont> queue.<nl>
    <nl>
    When using this <cfont>CAN_Send()<efont> API, the <cfont>channel<efont>
    parameter is used to specify either the normal (<cfont>CAN_TX_NORMAL<efont>)
    or high (<cfont>CAN_TX_HIGH<efont>) priority queues.<nl>
    <nl>
    Note that when this API is called with <cfont>channel<efont> set to
    <cfont>CAN_TX_HIGH<efont>, any CAN messages from the
    <cfont>CAN_TX_NORMAL<efont> queue which have already been
    loaded into the hardware registers will remain there.<s2>
    Consequently, it can happen that pending CAN 
    messages from the <cfont>CAN_TX_NORMAL<efont> queue that have
    already been loaded into one of the three hardware transmit
    registers may
    be transmitted after calling this API with a
    <cfont>CAN_TX_HIGH<efont> message and before this
    higher priority message is loaded into the transmit
    registers by the CAN driver.<s2>  The new high priority
    message will only be loaded when one of the three
    transmit registers becomes available (empty).<nl>
    <nl>
    Once loaded into the hardware register, the CAN message 
    recessive bit prioritization logic is used by hardware to select among
    the three transmit registers.<s2>  This too may lead to
    messages from the normal priority queue being
    transmitted ahead of a high priority CAN message, if the high
    priority queue's
    message does not have a high priority CAN message ID (low number).<s2>
    For applications where this behavior is not tolerable, you might consider
    disabling all but one of the transmit registers.<s2> However, this
    may lead to performance problems so should be avoided when possible.<s2>
    The queues will drain through what ever transmit registers
    have been enabled.
    <nl>
    <nl>
    <bold>Comments on CAN_TXQ1_DRIVES_ALL Mode<bolde><nl>
    <nl>
    This mode is selected by setting the <cfont>CAN_TXQ1_DRIVES_ALL<efont>
    option bit in the 
    <linkto>../../canstruc.htm#CAN_CONFIG<linkmid>CAN_CONFIG<linktail>
    <cfont>Mode<efont> word.<s2> (The <cfont>CAN_TX_PRIORITY_QUEUES<efont>
    bit must be zero.)<s2> In this mode the hardware transmit registers 
    <cfont>CAN_TX2<efont> and/or <cfont>CAN_TX3<efont> can be driven
    from the <cfont>CAN_TX1<efont> FIFO by specifying zero  
    <linkto>../../canstruc.htm#Tx_Q_Size<linkmid>sizes<linktail> for 
    the <cfont>CAN_TX2<efont> and/or <cfont>CAN_TX3<efont> software
    FIFO's.<nl>
    <nl>
    Example #1:<nl>
    <ul><nl>
    <cfont>
    CAN_PORT_INIT init ;<nl>
    init.Config.Mode = CAN_TXQ1_DRIVES_ALL ;<nl>
    init.Tx_Q_Size[CAN_TX1] = 20 ;<nl>
    init.Tx_Q_Size[CAN_TX2] = 5 ;<nl>
    init.Tx_Q_Size[CAN_TX3] = 0 ;<nl>
    <efont>
    <ule>
    <nl>
    These settings would cause TX1 and TX3 hardware transmit 
    registers to both be driven from the 20 message 
    <cfont>CAN_TX1<efont> FIFO.<s2>  The TX2 hardware transmit
    register is connected to its private 5 message queue.<nl>
    <nl>
    Example #2:<nl>
    <ul><nl>
    <cfont>
    CAN_PORT_INIT init ;<nl>
    init.Config.Mode = CAN_TXQ1_DRIVES_ALL ;<nl>
    init.Tx_Q_Size[CAN_TX1] = 20 ;<nl>
    init.Tx_Q_Size[CAN_TX2] = 0 ;<nl>
    init.Tx_Q_Size[CAN_TX3] = 0 ;<nl>
    <efont>
    <ule>
    <nl>
    These settings would cause all three hardware
    transmit registers to be filled from the 20 message 
    <cfont>CAN_TX1<efont> FIFO.<nl>
    <nl>
    When the <cfont>CAN_TXQ1_DRIVES_ALL<efont> option is used
    to drive more than one hardware transmit register from the first
    software transmit FIFO, the CAN transmissions may not necessarily
    come out in FIFO order.<s2>  This is due to the CAN bus 
    arbitration based on CAN label performed within the CAN port 
    device's set of transmit registers.<s2>  A typical scenerio
    would be that the CAN driver software
    takes three CAN messages from the send FIFO and places these into
    the three hardware transmit registers.<s2> Then the hardware transmit
    arbitration logic selects the CAN message among these three
    with the lowest CAN ID for transmission.<nl>
    <nl>
    When the  <cfont>CAN_TXQ1_DRIVES_ALL<efont> option is used to 
    drive <cfont>CAN_TX2<efont> and <cfont>CAN_TX3<efont> transmit
    registers, calling this <cfont>CAN_Send()<efont> API with the
    <cfont>channel<efont> argument set to either 
    <cfont>CAN_TX2<efont> or <cfont>CAN_TX3<efont> performs nearly
    the same operation as <cfont>CAN_TX1<efont>.<s2> In the case
    where the provided CAN message is placed in the single send FIFO,
    the functionality is identical.<s2> When the FIFO and specified
    transmit register are empty, there is a slight difference.<s2>
    In this case the <cfont>channel<efont> argument specifies 
    which hardware transmit registers is loaded.<nl>
 @Also  can04.htm | CAN_Recv  |
        can08.htm | CAN_Control |
        can01.htm | CAN_Open_Port
 @rtos  This library function uses a 
    <linkto>../../canswi.htm#0xBF0x80<linkmid>dynamic<linktail>
      link to reach the <linkto>../../canswi.htm#0xBF0x83<linkmid>service<linktail>
      offered by RTOS software 
      <linkto>../../canswi.htm<linkmid>interrupt<linktail>.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.45 | V1.45

 @target_clib V2.01
*/

/*************************************************************************/
//            Send CAN message
/*************************************************************************/
int far _cdecl CAN_Send (unsigned int       port_idx, 
                         unsigned int       channel,
                         const CAN_MSG far *msg)

{
    _DX = port_idx ;
    _CX = channel ;
    _ES = FP_SEG(msg);
    _BX = FP_OFF(msg);
    _AH = CAN_API_SEND ;

    asm int CAN_SWI ;

    return _AX ;
}
#endif


#ifdef _can04_
/*
 @doc DOC_can04_
 ---------------------------------------------------------------
 Pickup received CAN message
 ---------------------------------------------------------------
 @clib  CAN_Recv | Receive a CAN message, with optional time-out. |
        int CAN_Recv ( unsigned int port_idx, |
        CAN_MSG  far *msg,<nl>
        int           timeout );
 @parm  int  | port_idx | CAN port specifier:<s2>
    <cfont>CAN0_PORT<efont> = 0, or <cfont>CAN1_PORT<efont> = 1
 @parm  int  | msg | Output Parameter:<s2> Pointer to a 
        <linkto>../../canstruc.htm#CAN_MSG<linkmid>CAN_MSG<linktail>
        data structure were this API will output the next
        CAN message if one is available.
 @parm  int  | timeout | Time-out<nl>
    <ul>
    Negative value:<s2>  No wait, return immediately<nl>
    Zero:<s2> Wait forever for a CAN message<nl>
    Positive value:<s2>  Maximum milliseconds to wait for a CAN message<nl>
    <ule>
 @rdesc <linkto>../../canerr.htm<linkmid>Error<linktail> code:<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_SUCCESS<efont> = 0:<s2> Success, new message is in
        data structure referenced by <cfont>msg<efont> pointer.<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_INVALID_PARAMS<efont> = -1:<s2> <cfont>port_idx<efont> or
           <cfont>msg<efont> pointer invalid.<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_PORT_NOT_OPENED<efont> = -3:<s2> Port has not been
        <linkto>can01.htm<linkmid>opened<linktail>.<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_TIMEOUT<efont> = -6:<s2> Time period expired and still
        no message available.<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_BUS_OFF<efont> = -11: "Bus Off" state due to transmit
            or receive errors.<nl>
 @comm  This function is used to pick up the next received CAN message 
        from the receiver FIFO queue.<s2> The message is removed from the
        input queue upon transfer here to the user.<nl>
        <nl>
        The <cfont>timeout<efont> parameter allows the caller to optionally
        sleep on the receiver a specified number of milliseconds until a
        received CAN message becomes available.<nl>
        <nl>
        Note that if the CAN port is closed, the 
        <linkto>can09.htm<linkmid>CAN_Close_Port<linktail> API strobes the
        event bits to assure that a program thread which is sleeping on the
        receiver within this API will return (and not be left hanging on
        a no longer existant event group).<nl>
    <nl>
    If the <cfont>CAN_EC_BUS_OFF<efont> error is returned and the port
      has been configured with the 
      <linkto>../../canstruc.htm#AUTO_RESTART<linkmid>CAN_CFG_AUTO_RESTART<linktail>
      flag reset, then the 
      <linkto>can06.htm<linkmid>CAN_Reconfig()<linktail> API
      call will be required to restart the bus.<nl>
    <nl>
    Inside this API the interrupts are masked for a short period and then
    re-enabled.<s2> This function is reentrant.<nl>
    <nl>
    <bold>Important Note:<bolde><nl>
    <nl><ul>
    No CAN messages will be received until the port's receiver
    filters have been enabled for reception using the
    <linkto>can02.htm<linkmid>CAN_Rx_Filters<linktail> API.<s2> 
    Following a system reset, the CAN receiver filters are initialized
    to reject all incoming CAN messages by default.
    <ule>
 @Also  can05.htm | CAN_Peek  |
        can03.htm | CAN_Send  |
        can01.htm | CAN_Open_Port
 @Also  can09.htm | CAN_Close_Port |
        can02.htm | CAN_Rx_Filters |
          |
 @rtos  This library function uses a 
    <linkto>../../canswi.htm#0xBF0x80<linkmid>dynamic<linktail>
      link to reach the <linkto>../../canswi.htm#0xBF0x84<linkmid>service<linktail>
      offered by RTOS software 
      <linkto>../../canswi.htm<linkmid>interrupt<linktail>.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.45 | V1.45

 @target_clib V2.01
*/

/*************************************************************************/
//            Pickup received CAN message
/*************************************************************************/
int far _cdecl CAN_Recv (unsigned int  port_idx, 
                         CAN_MSG  far *msg, 
                         int           timeout)
{
    _DX = port_idx ;
    _CX = timeout ;
    _ES = FP_SEG(msg);
    _BX = FP_OFF(msg);
    _AH = CAN_API_RCV ;

    asm int CAN_SWI ;

    return _AX ;
}
#endif


#ifdef _can05_
/*
 @doc DOC_can05_
 ---------------------------------------------------------------
 Pickup received CAN message and leave it in queue
 ---------------------------------------------------------------
 @clib  CAN_Peek | Look at next CAN message, but leave it in queue. |
        int CAN_Peek ( unsigned int port_idx, |
        CAN_MSG  far *msg );
 @parm  int  | port_idx | CAN port specifier:<s2>
    <cfont>CAN0_PORT<efont> = 0, or <cfont>CAN1_PORT<efont> = 1
 @parm  int  | msg | Output Parameter:<s2> Pointer to a 
        <linkto>../../canstruc.htm#CAN_MSG<linkmid>CAN_MSG<linktail>
        data structure were this API will copy the next
        CAN message from receiver queue, if one is available.
 @rdesc <linkto>../../canerr.htm<linkmid>Error<linktail> code:<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_SUCCESS<efont> = 0:<s2> Success, a copy of next
        CAN message in queue is in the data structure referenced by 
        the <cfont>msg<efont> pointer.<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_INVALID_PARAMS<efont> = -1:<s2> <cfont>port_idx<efont> or
           <cfont>msg<efont> pointer invalid.<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_PORT_NOT_OPENED<efont> = -3:<s2> Port has not been
        <linkto>can01.htm<linkmid>opened<linktail>.<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_TIMEOUT<efont> = -6:<s2> No message available, receiver
        queue is empty.<nl>
     <hangpara 20:30>
        <cfont>CAN_EC_BUS_OFF<efont> = -11: "Bus Off" state due to transmit
            or receive errors.<nl>
 @comm  This function picks up a copy of the next received CAN message from
        the receiver queue FIFO without removing that message from the
        queue.<s2>  This function always returns immediately.<s2> If no
        message was available, the return value is <cfont>CAN_EC_TIMEOUT<efont>.
    <nl><nl>
    Inside this API the interrupts are masked for a short period and then
    re-enabled.<s2> This function is reentrant.<nl>
    <nl>
    If the <cfont>CAN_EC_BUS_OFF<efont> error is returned and the port
      has been configured with the 
      <linkto>../../canstruc.htm#AUTO_RESTART<linkmid>CAN_CFG_AUTO_RESTART<linktail>
      flag reset, then the 
      <linkto>can06.htm<linkmid>CAN_Reconfig()<linktail> API
      call will be required to restart the bus.<nl>
    <nl>
    <bold>Important Note:<bolde><nl>
    <nl><ul>
    No CAN messages will be received until the port's receiver
    filters have been enabled for reception using the
    <linkto>can02.htm<linkmid>CAN_Rx_Filters<linktail> API.<s2> 
    Following a system reset, the CAN receiver filters are initialized
    to reject all incoming CAN messages by default.
    <ule>
 @Also  can04.htm | CAN_Recv  |
        can02.htm | CAN_Rx_Filters |
        can01.htm | CAN_Open_Port
 @rtos  This library function uses a 
    <linkto>../../canswi.htm#0xBF0x80<linkmid>dynamic<linktail>
      link to reach the <linkto>../../canswi.htm#0xBF0x85<linkmid>service<linktail>
      offered by RTOS software 
      <linkto>../../canswi.htm<linkmid>interrupt<linktail>.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.45 | V1.45

 @target_clib V2.01
*/

/*************************************************************************/
//      Pickup received CAN message and leave it in queue
/*************************************************************************/
int far _cdecl CAN_Peek (unsigned int  port_idx, 
                         CAN_MSG  far *msg)
{
    _DX = port_idx ;
    _ES = FP_SEG(msg);
    _BX = FP_OFF(msg);
    _AH = CAN_API_PEEK ;

    asm int CAN_SWI ;

    return _AX ;
}
#endif


#ifdef _can06_
/*
 @doc DOC_can06_
 ---------------------------------------------------------------
 Reconfigure CAN port
 ---------------------------------------------------------------
 @clib  CAN_Reconfig | Adjust baud rate or bit timing parameters
        on an open CAN port. |
        int CAN_Reconfig ( unsigned int port_idx, |
        <s3>const CAN_CONFIG far *config);
 @parm  int  | port_idx | CAN port specifier:<s2>
    <cfont>CAN0_PORT<efont> = 0, or <cfont>CAN1_PORT<efont> = 1
 @parm  int  | config | Pointer to a 
        <linkto>../../canstruc.htm#CAN_CONFIG<linkmid>CAN_CONFIG<linktail>
        data structure containing requested bit timing (baud) and
        control information set by caller.
 @rdesc <linkto>../../canerr.htm<linkmid>Error<linktail> code -<nl>
        <cfont>CAN_EC_SUCCESS<efont> = 0:<s2> Success, new settings were
           accepted.<nl>
        <cfont>CAN_EC_INVALID_PARAMS<efont> = -1:<s2> <cfont>port_idx<efont> or
           <cfont>config<efont> pointer is invalid.<nl>
        <cfont>CAN_EC_INVALID_BAUD<efont> = -2:<s2> Invalid baud rate
           or bit timing specification.<nl>
        <cfont>CAN_EC_PORT_NOT_OPENED<efont> = -3:<s2> Port has not been
        <linkto>can01.htm<linkmid>opened<linktail>.
 @comm  This function allows bit timing to be adjusted on a CAN port which 
    has already been opened.<s2> (Under normal circumstances it is not 
    expected that this function will be used.)<nl>
    <nl>
    This function may also be used to manually switch back on a CAN bus
    following a <linkto>can0A.htm#BUS_OFF<linkmid>bus off<linktail>
    event.<s2>  By default, this is performed
    automatically by the driver.<s2> However the user may specify a
    manual <linkto>../../canstruc.htm#AUTO_RESTART<linkmid>restart<linktail> mode.
    <nl><nl>
    A successful call to this API zeroes the port's 
    <cfont>CANn_EV_BUS_OFF<efont> event.
    <nl><nl>
    Inside this API the interrupts are masked for a short period and then
    re-enabled.<s2> This function is reentrant.
 @Also  can01.htm | CAN_Open_Port  |
         | | |
 @rtos  This library function uses a 
    <linkto>../../canswi.htm#0xBF0x80<linkmid>dynamic<linktail>
      link to reach the <linkto>../../canswi.htm#0xBF0x86<linkmid>service<linktail>
      offered by RTOS software 
      <linkto>../../canswi.htm<linkmid>interrupt<linktail>.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.11 | V1.00

 @target_clib V2.01
*/

/*************************************************************************/
//            Reconfigure CAN port
/*************************************************************************/
int far _cdecl CAN_Reconfig (unsigned int          port_idx, 
                             const CAN_CONFIG far *config)
{
    _DX = port_idx ;
    _ES = FP_SEG(config);
    _BX = FP_OFF(config);
    _AH = CAN_API_RECONFIG ;

    asm int CAN_SWI ;

    return _AX ;
}
#endif


#ifdef _can07_
/*
 @doc DOC_can07_
 ---------------------------------------------------------------
 Read out CAN port status
 ---------------------------------------------------------------
 @clib  CAN_Status | Read out status information for specified CAN port. |
        int CAN_Status ( unsigned int port_idx,  |
        <s1>CAN_STATUS far *sts );
 @parm  int  | port_idx | CAN port specifier:<s2> 
    <cfont>CAN0_PORT<efont> = 0, or <cfont>CAN1_PORT<efont> = 1
 @parm  int  | sts | Pointer to a 
        <linkto>../../canstruc.htm#CAN_STATUS<linkmid>CAN_STATUS<linktail>
        data structure that will be written to by this API to report
        the status information for the specified CAN port.
 @rdesc <linkto>../../canerr.htm<linkmid>Error<linktail> code -<nl>
        <cfont>CAN_EC_SUCCESS<efont> = 0:<s2> Success<nl>
        <cfont>CAN_EC_INVALID_PARAMS<efont> = -1:<s2> <cfont>port_idx<efont>
        invalid or <cfont>sts<efont> pointer invalid<nl>
 @comm  This function reports various status information concerning the 
    specified CAN port.<s2>  After reading out the reported error flags, 
     the internal error flag registers are cleared (a destructive read)
     with one exception which is the <cfont>CAN_BUS_OFF<efont> error flag.<nl>
     <nl>
     The <cfont>CAN_BUS_OFF<efont> flag is cleared
     only after the bus is running again.<s2> If the port
      has been configured with the 
      <linkto>../../canstruc.htm#AUTO_RESTART<linkmid>CAN_CFG_AUTO_RESTART<linktail>
      flag reset, then the 
      <linkto>can06.htm<linkmid>CAN_Reconfig()<linktail> API
      call will be required to restart the bus.<nl>
    <nl>
    When the port  has been configured with
      <linkto>../../canstruc.htm#AUTO_RESTART<linkmid>CAN_CFG_AUTO_RESTART<linktail>
      flag set,  the <cfont>CAN_BUS_OFF<efont> flag in
    the <linkto>../../canstruc.htm#CAN_STATUS<linkmid>CAN_STATUS<linktail> 
    <cfont>Errors<efont> bit field will appear set once following a bus off
    condition even if by the time this API call is made the bus has already
    automatically restarted.<s2> So in this case the meaning of the 
    <cfont>CAN_BUS_OFF<efont> flag is that the bus is either currently off
    or had transitioned to off since the last time this status API was
    executed for this CAN port.<nl>
    <nl>
    Inside this API the interrupts are masked for a short period and then
    re-enabled.<s2> This function is reentrant.

 @Also  can08.htm | CAN_Control  |
        can01.htm | CAN_Open_Port |
        can09.htm | CAN_Close_Port
 @rtos  This library function uses a 
    <linkto>../../canswi.htm#0xBF0x80<linkmid>dynamic<linktail>
      link to reach the <linkto>../../canswi.htm#0xBF0x87<linkmid>service<linktail>
      offered by RTOS software 
      <linkto>../../canswi.htm<linkmid>interrupt<linktail>.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.45 | V1.45

 @target_clib V2.01
*/

/*************************************************************************/
//      Read out CAN port status
/*************************************************************************/
int far _cdecl CAN_Status (unsigned int port_idx, CAN_STATUS far *sts)
{
    _DX = port_idx ;
    _ES = FP_SEG(sts);
    _BX = FP_OFF(sts);
    _AH = CAN_API_STATUS ;

    asm int CAN_SWI ;

    return _AX ;
}
#endif


#ifdef _can08_
/*
 @doc DOC_can08_
 ---------------------------------------------------------------
 Enable or disable channels. Purge FIFO's
 ---------------------------------------------------------------
 @clib  CAN_Control | Enable or disable specified channels.<s2> 
     Purge specified FIFO's. |
        int CAN_Control ( unsigned int port_idx, |
        <s2>unsigned int enables,<nl>
        <s2>unsigned int disables,<nl>
        <s2>unsigned int purge_fifos ) ;
 @parm  int  | port_idx | CAN port specifier:<s2>
    <cfont>CAN0_PORT<efont> = 0, or <cfont>CAN1_PORT<efont> = 1
 @parm  int  | enables | Bit field indicating which devices to enable.
 @parm  int  | disables | Bit field indicating which devices to disable.
 @parm  int  | purge_fifos | Bit field indicating which FIFO's to clear.
 @rdesc <linkto>../../canerr.htm<linkmid>Error<linktail> code -<nl>
        <cfont>CAN_EC_SUCCESS<efont> = 0:<s2> Success<nl>
        <cfont>CAN_EC_INVALID_PARAMS<efont> = -1:<s2> <cfont>port_idx<efont> is
            invalid<nl>
        <cfont>CAN_EC_PORT_NOT_OPENED<efont> = -3:<s2> Port has not been
        <linkto>can01.htm<linkmid>opened<linktail>.
 @comm  This function provides a way to enable or disable the receiver and
    the three individual transmit register channels.<s2>  Also, any or all
    of the receiver or transmit FIFO's can be cleared.<nl>
    <nl>
    The <linkto>can01.htm<linkmid>CAN_Open_Port()<linktail> enables
    all three transmitters and optionally the receiver as well.<s2> So
    this provisional API here is not necessarily required for CAN
    port operation.<nl>
    <nl>
    The input parameters <cfont>enables<efont>,  <cfont>disables<efont>
    and <cfont>purge_fifos<efont> are each bit fields with the identical
    bit mapping as follows:<nl>
    <nl><ul>
    <cfont>CAN_RX_SEL<efont> = 0x8000, Receiver control flag<nl>
    <cfont>CAN_TX1_SEL<efont> = 0x0800, TX1 register control flag<nl>
    <cfont>CAN_TX2_SEL<efont> = 0x1000, TX2 register control flag<nl>
    <cfont>CAN_TX3_SEL<efont> = 0x2000, TX3 register control flag<nl>
    <nl><ule>
    A bit set indicates that the action associated with the particular 
    CPU register should be taken for the device designed by the bit.<s2>
    For example:<nl>
    <nl><ul><cfont>
    CAN_Control(CAN0_PORT,<nl>
    <tab><tab><tab>CAN_TX3_SEL,<tab><s3> // = enables<nl>
    <tab><tab><tab>CAN_TX2_SEL,<tab><s3> // = disables<nl>
    <tab>CAN_RX_SEL \| CAN_TX2_SEL) ;  // = purge_fifos<nl>
    <ule><efont><nl>
     This example API call will enable transmit register #3.<s2> It will disable 
     transmit register #2.<s2> It will purge (delete the contents of) the
     receiver FIFO and the FIFO associated with transmit register #2.<nl>
     <nl>
     When transmit FIFO's are purged, any CAN message pending output in the 
     specified hardware transmit register is also aborted.<nl>
     <nl>
     In the non-sense case where a device's bit is set in both the
     <cfont>enables<efont> and <cfont>disables<efont> input parameters,
     indicating that both an enabling and disabling action should be taken
     on the same device, the enabling will take precedence and the device 
     will be enabled.<nl>
     <nl>
     Note that when the <cfont>CAN_TX1<efont> transmit FIFO is feeding
     more than just the TX1 transmit register 
     (<cfont>CAN_TXQ1_DRIVES_ALL<efont>  
     <linkto>../../canstruc.htm#CAN_CONFIG<linkmid>configuration<linktail>
     option), all of the transmit registers fed must be blocked
     with the <cfont>disables<efont> mask in order to stop transmission
     from this FIFO.<nl>
     <nl>
     e.g.<nl>
     <tab><cfont>disables = CAN_TX1_SEL \| CAN_TX2_SEL \| CAN_TX3_SEL ;<efont><nl>
     <nl>
     would be needed to stop transmission from the <cfont>CAN_TX1<efont> FIFO
     if all three transmit registers were being fed from this FIFO.<s2>
     And likewise, bits for all channels associated with the queue would 
     need to be set in the <cfont>enables<efont> to obtain a full
     bandwidth draining of the queue into the available hardware
     transmit registers.
     <nl><nl>
    Inside this API the interrupts are masked for a short period and then
    re-enabled.<s2> This function is reentrant.
 @Also  can01.htm | CAN_Open_Port |
        can07.htm | CAN_Status  | |
 @rtos  This library function uses a 
    <linkto>../../canswi.htm#0xBF0x80<linkmid>dynamic<linktail>
      link to reach the <linkto>../../canswi.htm#0xBF0x88<linkmid>service<linktail>
      offered by RTOS software 
      <linkto>../../canswi.htm<linkmid>interrupt<linktail>.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/

/*************************************************************************/
//      Enable or disable channels. Purge FIFO's
/*************************************************************************/
int far _cdecl CAN_Control (unsigned int port_idx, 
                            unsigned int enables, 
                            unsigned int disables, 
                            unsigned int purge_fifos)
{
    _DX = port_idx ;
    _CX = enables ;
    _SI = disables ;
    _BX = purge_fifos ;
    _AH = CAN_API_CONTROL ;

    asm int CAN_SWI ;

    return _AX ;
}
#endif


#ifdef _can09_
/*
 @doc DOC_can09_
 ---------------------------------------------------------------
  Close specified CAN port
 ---------------------------------------------------------------
 @clib  CAN_Close_Port | Close down a specified CAN port. |
        int CAN_Close_Port ( unsigned int port_idx ); |
 @parm  int  | port_idx | CAN port specifier:<s2>
    <cfont>CAN0_PORT<efont> = 0, or <cfont>CAN1_PORT<efont> = 1
 @rdesc <linkto>../../canerr.htm<linkmid>Error<linktail> code -<nl>
        <cfont>CAN_EC_SUCCESS<efont> = 0:<s2> Success<nl>
        <cfont>CAN_EC_INVALID_PARAMS<efont> = -1:<s2> <cfont>port_idx<efont> 
            invalid<nl>
 @comm  This function closes a CAN port, releasing any resources it was
    using (e.g. heap memory for FIFO's and RTX event group).<s2>   Prior to
    releasing the <linkto>../rtx/rtx41.htm<linkmid>event group<linktail>, the event
    bits in the RTX event group associated with this port are 
    <linkto>../rtx/rtx42.htm<linkmid>strobed<linktail>
    in order to release any program threads which were 
    <linkto>can0A.htm<linkmid>waiting<linktail> on
    events for this port which is now being closed.<nl>
    <nl>
    Any user <linkto>can0B.htm<linkmid>callback<linktail> vectors that had
    been set for this port will be removed.<nl>
    <nl>
    <nl>
    The CAN device is deactivated.<s2> Any pending transmission is aborted.<s2>
    Aborting a pending transmission requires some additional time beyond when
    this API returns such that if the port were to be immediately reopened,
    a subsequent call to <linkto>can03.htm<linkmid>CAN_Send<linktail> could
    fail due to a transmit buffer still busy condition.<nl>
    <nl>
    Inside this API the interrupts are masked for a short period and then
    re-enabled.<s2> This function is reentrant.

 @Also  can01.htm | CAN_Open_Port  |
        can0A.htm | CAN_Event_Sleep | 
        can04.htm | CAN_Recv
 @Also  can0B.htm | CAN_Set_Callback  |
        |  | 
        |
 @rtos  This library function uses a 
    <linkto>../../canswi.htm#0xBF0x80<linkmid>dynamic<linktail>
      link to reach the <linkto>../../canswi.htm#0xBF0x89<linkmid>service<linktail>
      offered by RTOS software 
      <linkto>../../canswi.htm<linkmid>interrupt<linktail>.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/

/*************************************************************************/
//    Close specified CAN port
/*************************************************************************/
int far _cdecl CAN_Close_Port (unsigned int port_idx)
{
    _DX = port_idx ;
    _AH = CAN_API_CLOSE ;

    asm int CAN_SWI ;

    return _AX ;
}
#endif


#ifdef _can0A_
/*
 @doc DOC_can0A_
 ---------------------------------------------------------------
  Sleep awaiting a CAN event
 ---------------------------------------------------------------
 @clib  CAN_Event_Sleep | Await any one event from a specified
        set of CAN port events. |
        unsigned int CAN_Event_Sleep ( unsigned int events, |
        <tab><s2>int timeout );
 @parm  int  | events | Bit field specifying a set of events to await
 @parm  int  | timeout | Time-out<nl><ul>
    Negative value:<s2> No wait, return immediately<nl>
    Zero:<s2> Wait forever for the CAN event(s)<nl>
    Positive value:<s2> Maximum milliseconds to wait for the CAN event(s)<nl>
    <ule>
 @rdesc = 0 indicates no events occurred (time-out)<nl>
      non-zero = event bits which came true among those that were
      specified in <cfont>events<efont> input parameter
 @comm  This function sleeps on the event group used internally by the 
    CAN driver, awaiting specified CAN events.<s2>  Note that the events
    can be on either of the two CAN ports.<s2> The events specified in the
    bit field input parameter <cfont>events<efont> can be any combination 
    of the following:<nl>
    <nl>
    <linktag BUS_OFF>
    CAN0_EV_RX_RDY = 0x0001, CAN0 Receiver data ready<nl>
    CAN0_EV_TX1_EMP = 0x0002, CAN0 Transmitter #1 empty<nl>
    CAN0_EV_TX2_EMP = 0x0004, CAN0 Transmitter #2 empty<nl>
    CAN0_EV_TX3_EMP = 0x0008, CAN0 Transmitter #3 empty<nl>
    CAN0_EV_BUS_OFF = 0x0010, CAN0 Bus off condition<nl>
    <nl>
    CAN1_EV_RX_RDY = 0x0100, CAN1 Receiver data ready<nl>
    CAN1_EV_TX1_EMP = 0x0200, CAN1 Transmitter #1 empty<nl>
    CAN1_EV_TX2_EMP = 0x0400, CAN1 Transmitter #2 empty<nl>
    CAN1_EV_TX3_EMP = 0x0800, CAN1 Transmitter #3 empty<nl>
    CAN1_EV_BUS_OFF = 0x1000, CAN1 Bus off condition<nl>
    <nl>
    This function returns when any one of the specified events occurs.<s2>
    If no events are specified the function returns immediately with 
    a return value zero.<s2>  Any event bits in input parameter
    <cfont>events<efont> which apply to a port which is not open will
    be ignored and treated as zeros.<nl>
    <nl>
    This function has no affect on the event flags.<s2> Event flags are
    <bold><i>not<ie><bolde> cleared as a side affect of this function
    call.<nl>
    <nl>
    The <cfont>CANn_EV_RX_RDY<efont> event is cleared after
    the respective receiver queue is emptied by calls to the
    <linkto>can04.htm<linkmid>CAN_Recv()<linktail> API.<s2>
    The <cfont>CANn_EV_BUS_OFF<efont> event is cleared by
    calls to
    <linkto>can01.htm<linkmid>CAN_Open_Port()<linktail>,
    <linkto>can06.htm<linkmid>CAN_Reconfig()<linktail> or
    <linkto>can09.htm<linkmid>CAN_Close_Port()<linktail> API.<nl>
    <nl>
    The transmit event flags operate differently depending on
    whether or not the <cfont>CAN_TXQ1_DRIVES_ALL<efont>
    or <cfont>CAN_TX_PRIORITY_QUEUES<efont> modes are being
    used.<s2>  When either of these transmit modes are used, 
    the <linkto>can03.htm<linkmid>CAN_Send<linktail> API clears
    the transmit flags for all channels associated with the software
    queue that the output CAN message is directed to.<s2> And this same 
    group of transmit channel event flags will be set to '1' 
    simultaneously when the software queue(s) feeding those
    channels is (are) emptied.<s2> However there may still be
    a CAN message or two awaiting output in the CAN 
    hardware transmit registers after the events are set.<nl>
    <nl>
    When the transmitters are operated in neither 
    <cfont>CAN_TXQ1_DRIVES_ALL<efont> nor
    <cfont>CAN_TX_PRIORITY_QUEUES<efont> mode,  the 
    <linkto>can03.htm<linkmid>CAN_Send<linktail> API clears the
    single event flag bit associated with the channel that the
    CAN message is directed.<s2>  Then the respective transmit event
    bit will be set to '1' after the
    hardware register is emptied (CAN message sent) and no further
    queued messages were pending for this transmit device.<nl>
    <nl>
    A port closing will cause this function to return if any event wait 
    bits applied to that port which closed.<s2> In this case the event flags
    returned for the closed port should be ignored, since they were created
    artificially.<nl>
    <nl>
    The handle to the event group which the CAN driver uses to implement
    this API can be retrieved with the 
    <linkto>../RTX/RTX46.htm<linkmid>RTX_Find_EventGroup()<linktail>
    API provided that the user has not stepped on the name given this
    group with yet another event group by the same name.<s2> The name
    given this event group by the CAN driver is "_CAN".<s2> This event
    group exists only so long as one of the two CAN ports is 
    <linkto>can01.htm<linkmid>opened<linktail>.<nl>
    <nl>
    An event group provides 16 independent events, of which this CAN
    driver uses ten (five events for each of two CAN ports).<s2> These
    ten event bits are specified above.<s2> The
    other six event flags are available to the user.<s2> If the
    user chooses to use these additional event flags for their own purposes
    then they should call directly the 
    <linkto>../RTX/RTX43.htm<linkmid>RTX_Wait_For_Event()<linktail>
    rather then using this API.<s2>  When this <code>CAN_Event_Sleep()<codee>
    API is used, any
    event flags outside the scope of the ten used by the CAN driver are
    ignored.<s2> Furthermore, this API only waits for event flag '1'
    conditions.<s2> Using the <code>RTX_Wait_For_Event()<codee> API
    directly, the user would have more flexibility.<nl>
    <nl>
    Inside this API the interrupts are masked for a short period and then
    re-enabled.<s2> This function is reentrant.
 @Also  can01.htm | CAN_Open_Port  |
        can04.htm | CAN_Recv |
        can0B.htm | CAN_Set_Callback
 @Also  can09.htm | CAN_Close_Port  |
        can03.htm | CAN_Send |
        can06.htm | CAN_Reconfig
 @rtos  This library function uses a 
    <linkto>../../canswi.htm#0xBF0x80<linkmid>dynamic<linktail>
      link to reach the <linkto>../../canswi.htm#0xBF0x8A<linkmid>service<linktail>
      offered by RTOS software 
      <linkto>../../canswi.htm<linkmid>interrupt<linktail>.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00

 @target_clib V2.01
*/

/*************************************************************************/
//    Close specified CAN port
/*************************************************************************/
unsigned int far _cdecl CAN_Event_Sleep (unsigned int events, int timeout)
{
    _DX = events ;
    _CX = timeout ;
    _AH = CAN_API_EVENT ;

    asm int CAN_SWI ;

    return _AX ;
}
#endif

#ifdef _can0B_
/*
 @doc DOC_can0B_
 ---------------------------------------------------------------
  Install ISR callback for specified CAN port
 ---------------------------------------------------------------
 @clib  CAN_Set_Callback | Install a callback function to be
      called on specified event(s) within CAN interrupt
      service routine (ISR). |
        int CAN_Set_Callback ( unsigned int<tab> port_idx,<nl>
        <tab><tab><tab><tab><tab> CAN_ISR_CALLBACK vector,<nl>
        <tab><tab><tab><tab><tab> unsigned int <tab> events) ; |
 @parm  int  | port_idx | CAN port specifier:<s2>
    <cfont>CAN0_PORT<efont> = 0, or <cfont>CAN1_PORT<efont> = 1
 @parm  int  | vector | User procedure address, or NULL to
       remove a callback previously installed.
 @parm  int  | events | Bit field specifying on which CAN
      events the callback should be made.  These are combinations
      of masks <cfont>CAN_CALLBACK_RX<efont>,
    <cfont>CAN_CALLBACK_TX<efont>, and <cfont>CAN_CALLBACK_ERR<efont>.
 @rdesc <linkto>../../canerr.htm<linkmid>Error<linktail> code -<nl>
        <cfont>CAN_EC_SUCCESS<efont> = 0:<s2> Success<nl>
        <cfont>CAN_EC_INVALID_PARAMS<efont> = -1:<s2> <cfont>port_idx<efont> 
            invalid<nl>
 @comm
    This function either installs or removes a user callback
    procedure that is called from 
    within the CAN driver's Interrupt Service Routine (ISR)
    upon specified events.<s2>
    The <cfont>vector<efont> argument can be set to NULL to remove
    existing vectors.<s2> Note that the 
    <linkto>CAN09.htm<linkmid>CAN_Close_Port<linktail> will
    remove any callbacks established for the CAN port being
    closed.<nl>
    <nl>
    The callback will be made from within the CAN driver's interrupt
    service routine, which has been 
    <linkto>../HW/hal84A.htm<linkmid>registered<linktail> with the 
    RTX @Chip-RTOS.<s2> No stack switch is performed by this ISR, so 
    the stack from which ever task was interrupted will be used within
    this callback.<s2> This means that the amount of stack space available
    is not well known, and therefore this user callback should be conservative
    with its use of stack space.
    <nl>
    <nl>
    The system maintains three independent callbacks for each CAN port:<nl>
    <ol><nl>
    <li>Receiver event callback:<tab><tab><s2>  <cfont>CAN_CALLBACK_RX<efont><nl>
    <li>Transmit event callback:<tab><tab><s2>  <cfont>CAN_CALLBACK_TX<efont><nl>
    <li>Bus off error event callback:<tab>  <cfont>CAN_CALLBACK_ERR<efont><nl>
    <ole>
    <nl>
    The <cfont>events<efont> argument determines which
    callbacks are set by this API.<s2>  The masks defined
    for this purpose in CAN_API.H are indicated above.<s2>  Combinations
    of these masks can be formed by OR'ing them together when 
    it is desired that events share the same user
    callback.<s2>  For example, the <cfont>CAN_CALLBACK_ALL<efont> mask
    will set all three callbacks to a single provided vector.<nl>
    <nl>
    The set of three callbacks was implemented so that less logic
    is required inside the user callback to figure out why
    it had been called, when independent callback functions
    are used.<s2>  Note that all three transmit events
    are mapped to a single transmit callback.<nl>
    <nl>
    The prototype for the user callback is as follows.<nl>
    <nl><cfont>
    <tab>void huge my_Callback(unsigned int       event,<nl>
    <tab><tab><tab><tab><tab><tab>const <linkto>../../canstruc.htm#CAN_MSG<linkmid>CAN_MSG<linktail> far *msg) ;<nl>
    <nl><efont>
    This prototype corresponds to the <cfont>CAN_ISR_CALLBACK<efont> type.  The receiver
    callback is a special case, for  which the user callback may choose to
    violate the constant nature of the object
    referenced by the <cfont>msg<efont> pointer argument with a cast in order
    to write <cfont>CAN_RX_DISCARD<efont> into the <cfont>Len_Ctrl<efont>
    member of the 
    <linkto>../../canstruc.htm#CAN_MSG<linkmid>CAN_MSG<linktail>
    object.   When this most significant bit, <cfont>CAN_RX_DISCARD<efont>, 
    is set in <cfont>Len_Ctrl<efont> member, this signals the receiver 
    ISR to discard this message and
    not register the message in the driver's software receive message queue.
    <nl>
    <nl>
    For example, the following cast notation around the <cfont>msg<efont> pointer
    can be used to force the compiler to set a member of the object which
    the callback's prototype had declared constant.<nl><nl>
    <cfont>
    <tab><tab> ((CAN_MSG far *)msg)->Len_Ctrl = CAN_RX_DISCARD ;<nl>
    <efont>
    <nl>
    This action will cause the CAN driver ISR to discard this message.
    <nl>
    <nl><bold>Note:<bolde><nl>
    <ul>
    The use of the <cfont>CAN_RX_DISCARD<efont> flag by the receiver
    callback to filter out received CAN messages requires SC1x3/SC2x <chiprtos>
    version 1.41 or newer.
    <ule>
    <nl><nl>
    The <cfont>event<efont> parameter in this callback will be
    a single bit that indicates the reason for the callback.<s2> 
    This bit is the same as used for the 
    <linkto>can0A.htm<linkmid>CAN_Event_Sleep()<linktail>
    API's event masks, <cfont>CAN0_EV_RX_RDY<efont>
    through <cfont>CAN1_EV_BUS_OFF<efont>.<s2>  Note that which
    CAN channel the event occurred on is conveyed by this
    event bit.<nl>
    <nl>
    The <cfont>msg<efont> pointer argument passed to the bus error
    callback is always NULL.<s2> No CAN message is associated
     with this callback.<s2>  For receive events, the 
     <cfont>msg<efont> pointer references
    the CAN message that was just received.<s2> For transmit events, 
    the <cfont>msg<efont> pointer references
    the CAN message that just completed transmission.<nl>
    <nl>
    The user callback function must preserve the DS, SS and SP registers.<s2>
    All other registers the callback is free to modify.<s2>
    The code within this callback must be keep to a minimum.<s2> This
    callback is performed within the CAN interrupt service.<s2> Interrupts
    are masked on entry to the callback and must remain masked.<s2> To
    encourage assembly language programming of this time critical
    callback, the parameters are also made available in registers:<nl>
    <ul><nl>
    <li>CX - Contains the <cfont>event<efont> parameter.<nl>
    <nl>
    <li>ES:DI - Contains the <cfont>msg<efont> far pointer to a
    <linkto>../../canstruc.htm#CAN_MSG<linkmid>CAN_MSG<linktail> input parameter<nl>
    <ule><nl>
    These parameters are also pushed onto the stack to support a standard
    C language interface.<nl>
    <nl>
    Inside this API the interrupts are masked for a short period and then
    re-enabled.<s2> This function is reentrant.<nl>
    <nl><bold>Note:<bolde><nl>
    <ul>
    Use of callbacks may overload the system when CPU is operated in
    <linkto>../../config.htm#DEVICE_POWERSAVE<linkmid>power save mode<linktail>
     and CAN is operated at high baud rates.
    <ule>

 @Also  can09.htm | CAN_Close_Port  |
        can0A.htm | CAN_Event_Sleep | 
        can04.htm | CAN_Recv
 @rtos  This library function uses a 
    <linkto>../../canswi.htm#0xBF0x80<linkmid>dynamic<linktail>
      link to reach the <linkto>../../canswi.htm#0xBF0x8B<linkmid>service<linktail>
      offered by RTOS software 
      <linkto>../../canswi.htm<linkmid>interrupt<linktail>.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.06 | V1.00

 @target_clib V2.05
*/

/*************************************************************************/
//    Close specified CAN port
/*************************************************************************/
int far _cdecl CAN_Set_Callback(unsigned int     port_idx,
                                CAN_ISR_CALLBACK vector,
                                unsigned int     events)
{
    _CX = events ;
    _DX = port_idx ;
    _ES = FP_SEG(vector) ;
    _BX = FP_OFF(vector) ;
    _AH = CAN_API_CALLBACK ;

    asm int CAN_SWI ;

    return _AX ;
}
#endif

#ifdef _can0C_
/*
 @doc DOC_can0C_
 ---------------------------------------------------------------
 Read out CAN port Rx/Tx error count and status
 ---------------------------------------------------------------
 @clib  CAN_Error_Counts |Read out CAN Rx/Tx error count and errror
    status information for specified CAN port. |
        int CAN_Error_Counts ( unsigned int port_idx,  |
        <tab><s1>CAN_ERRORS far *errors );
 @parm  int  | port_idx | CAN port specifier:<s2> 
    <cfont>CAN0_PORT<efont> = 0, or <cfont>CAN1_PORT<efont> = 1
 @parm  int  | errors | Pointer to a 
        <linkto>../../canstruc.htm#CAN_ERRORS<linkmid>CAN_ERRORS<linktail>
        data structure that will be written to by this API to report
        the error count and error status information for the specified CAN port.
 @rdesc <linkto>../../canerr.htm<linkmid>Error<linktail> code -<nl>
        <cfont>CAN_EC_SUCCESS<efont> = 0:<s2> Success<nl>
        <cfont>CAN_EC_INVALID_PARAMS<efont> = -1:<s2> <cfont>port_idx<efont>
        invalid or <cfont>errors<efont> pointer invalid<nl>
 @comm  This function reports transmitter/receiver error counts as specified
    by the Bosch CAN specification.<s2> Also some discrete bits
    are reported which indicate the bus error state.
    <nl><nl>
    Inside this API the interrupts are masked for a short period and then
    re-enabled.<s2> This function is reentrant.

 @Also  can08.htm | CAN_Control  |
        can01.htm | CAN_Open_Port |
        can09.htm | CAN_Close_Port
 @Also  can07.htm | CAN_Status  |
        | |
        |
 @rtos  This library function uses a 
    <linkto>../../canswi.htm#0xBF0x80<linkmid>dynamic<linktail>
      link to reach the <linkto>../../canswi.htm#0xBF0x8C<linkmid>service<linktail>
      offered by RTOS software
      <linkto>../../canswi.htm<linkmid>interrupt<linktail>.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.07 | V1.00

 @target_clib V2.06
*/

/*************************************************************************/
//      Read out CAN port status
/*************************************************************************/
int far _cdecl CAN_Error_Counts (unsigned int port_idx, CAN_ERRORS far *errors)
{
    _DX = port_idx ;
    _ES = FP_SEG(errors);
    _BX = FP_OFF(errors);
    _AH = CAN_API_ERRORS ;

    asm int CAN_SWI ;

    return _AX ;
}
#endif

/************************************************************************/
// end CAN.c
/************************************************************************/

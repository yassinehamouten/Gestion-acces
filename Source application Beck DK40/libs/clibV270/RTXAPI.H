/****************************************************************************
* (C) 1999-2007 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module        : RTXAPI.H
* Function      : Constants and type definitions for RTX library API
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\RTXAPI.H, 13, 22.01.2007 10:58:01, Jack Gatrost$

******************************************************************************/

#ifndef RTX_API_H_
#define RTX_API_H_

#ifdef CLIB_CUSTOMER_SPECIFIC
// Supply some optional patches for customer specific library.
// (For standard Beck library, this file does not exists.)
#include "RTXAPI_EXT.H"     
#endif

/**********************************************************/
// Returned common API errorcodes at DX register, 
// special RTOS error codes are listed at the HTML-Doc
/**********************************************************/
#define RTX_ENOERROR        0
#define RTX_ERROR          -1
#define RTX_NOT_SUPPORTED  -2

    // Return codes from WAKEUP_TASK
#define RTX_TASK_NOT_WAITING    2   // Warn: task not waiting; wake is pending
#define RTX_STILL_NOT_WAITING (-6)  // Err: task not waiting (after 2nd wake)	

/*****************************************************************************/
//typedefs
/*****************************************************************************/
/* ID type for tasks ,semaphores */

typedef unsigned int RTOS_ID ;


typedef void huge (far *PROC_VECTOR)(void) ;

// Task Definition Structure
typedef struct tag_taskdefblock
{
        PROC_VECTOR   proc ;            // task procedure pointer
        char    name[4];                // name 4 characters not null terminated
        unsigned int far * stackptr;    // task stack pointer (Top of stack)       
        unsigned int stacksize;         // size of task stack (bytes)   
        unsigned short int attrib;      // task attributes, TA_SAVE_STACK
        short int priority;             // task priority,  range: 2 <= priority <= 127 
        unsigned short int time_slice;  // 0: none, !=0: number of milliseconds before task
                                        //  force to relinquish processor
        short int mailboxlevel1;        // -- Task mailbox not implemented --
        short int mailboxlevel2;
        short int mailboxlevel3;
        short int mailboxlevel4;
} TaskDefBlock;


typedef void huge (far *PARAM_TASK)(unsigned short Param1, unsigned short Param2) ;

// Task Definition Structure for tasks passed a parameter
typedef struct tag_TASK_PARAM_DEF
{
        PARAM_TASK    proc ;            // task procedure pointer
        char    name[4];                // name 4 characters not null terminated
        unsigned int far * stackptr;    // task stack pointer (Top of stack)       
        unsigned int stacksize;         // size of task stack (bytes)   
        unsigned short int attrib;      // task attributes, TA_SAVE_STACK
        short int priority;             // task priority,  range: 2 <= priority <= 127 
        unsigned short int time_slice;  // 0: none, !=0: number of milliseconds before task
                                        //  force to relinquish processor
        unsigned short Param1 ;         // LSH if a far pointer is used
        unsigned short Param2 ;         // MSH if a far pointer is used

} TASK_PARAM_DEF ;

#define TA_SAVE_STACK (0x1)  // attrib bit to reduce task stack
                             //  space used by system

typedef struct tagtasklist
{
     unsigned int taskID;         /*task identifier*/
     char taskname[5];            /* unique name 4 characters , 0 terminated */
}TaskList;



typedef struct tag_task_statedata{
        unsigned int taskID;
        unsigned int taskPrio;
        unsigned int taskState;     /*taskstate see below*/
        unsigned int taskCount;     /*count of the taskmonitor, if taskmon is active*/
        unsigned int stackused;     /*used stack in percent*/
        unsigned int stacksize;     /*whole stacksize*/
}Task_StateData;

/*taskstates (16Bit value)
Bit0 timer wait (used with other bits)
Bit1 trigger wait (i.e. idle)
Bit2 semaphore wait
Bit3 event group wait
Bit4 message exchange wait
Bit5 message send wait
Bit6 suspended (waiting for resume)
Bit7 waiting for wake
>Bit7 internal use only
*/


/*Time/Date Structure*/
typedef struct tag_time
{
        unsigned char sec;      /* seconds      (0-59)  */
        unsigned char min;      /* minutes      (0-59)  */
        unsigned char hr;       /* hours        (0-23)  */
        unsigned char dy;       /* day          (1-31)  */
        unsigned char mn;       /* month        (1-12)  */
        unsigned char yr;       /* year         (0-99)  */
        unsigned char dow;      /* day of week  (Mon=1 to Sun=7) */
        unsigned char dcen;     /* century (19 or 20) */
}TimeDate_Structure;

typedef struct TimeDateFineT
{
    unsigned short usec;    /*!< Microseconds [0-999]  */
    unsigned short msec;    /*!< Milliseconds [0-999]  */
    unsigned char sec;      /*!< Seconds      [0-59]  */
    unsigned char min;      /*!< Minutes      [0-59]  */
    unsigned char hr;       /*!< Hours        [0-23]  */
    unsigned char dy;       /*!< Day          [1-31]  */
    unsigned char mn;       /*!< Month        [1-12]  */
    unsigned char yr;       /*!< Year         [0-99]  */
    /*! Day of week  [Mon=1 to Sun=7]<br>
     *  This member plays no role for RTX_Set_TimeDate_us().  Day
     *  of week will be calculated by the system based on 
     *  the provided %date. */
    unsigned char dow;      
    /*! Century<br>
     * A zero here will be translated by RTX_Set_TimeDate_us() API to 20.
     */
    unsigned char dcen;     
} TimeDateFineS ;

/*Timer procedure structure*/
#ifndef TimerProc_Structure  // No alternate definition in use?
typedef struct tag_timer_proc
{
   unsigned int  far * timerID;     /*pointer to storage the unique timerID*/
   PROC_VECTOR  proc ;              /*pointer to the procedure to be executed*/
   void  far   *dummyptr;           /* Optional parameter to timer procedure */
   char         name[4];            /*pointer to a unique 4 character name*/
   long         interval;           /*timer execution interval*/
}TimerProc_Structure;
#endif // TimerProc_Structure


/*Event manager: Wait for event structure*/
typedef struct tag_rtx_event_wait
{
  unsigned int mask;    // 16-Bit mask identifying the flags of interest of the group.
  unsigned int value;   // 16 Bit value, which specfies the states of interest
                        //  for each flag selected by the mask.
  int match;            // event match requirements, 0:only one flag must match with value,
                        // !=0: all by mask specified flags must match
  long timeout;         // Maximum time (milliseconds) for waiting for an event match
}RTX_Wait_Event;


// Message exchange create structure
typedef struct tag_rtx_msg{
  unsigned int  msgID;  // Output parameter, unique message exchange ID
  char name[4];         // name 4 characters, not null terminated
  int  mb0;             // numbers of message envelopes
  int  mb1;
  int  mb2;
  int  mb3;
} RTX_Msg;


// Message exchange wait structure
typedef struct tag_rtx_wait_msg
{
  unsigned int  msgID;         // ID of the message exchange
  int           prio;          // priority for wait,  0=highest
  void far     *msg;           // pointer ot user buffer to storage the arrived message
  long          timeout;       // Maximum time (milliseconds) for waiting for a message
} RTX_Wait_Msg;

    // Note: Parameters to timer callback procedures may be ignored and
    //      procedure declared without any parameter.
typedef void huge _cdecl (far *RTX_TIMER_CALLBACK)(unsigned int timer_id,
                                                   unsigned long lParam) ;

// Type used by RTX_GetFineTick() API
typedef struct {
    union {
        unsigned long   Full ;      // 32 bit RTI counter
        struct {
            unsigned int Lsh ;      // Least Significant Half
            unsigned int Msh ;      // Most Significant Half
        } Part ;
    } Rti_Count ;

    unsigned int    Timer2_Count ;

} RTX_FINE_TICK ;

///////////////////////////////////////////////////////////////////
//
//  RTX_FineTickInit() variables
//
//     Following group of global variables are produced by the
//     RTX_FineTickInit() API.
//
///////////////////////////////////////////////////////////////////
extern unsigned long far  *_pRti_Tick ;
extern unsigned int        _RTI_kHz ;
extern unsigned int        _us_per_RTI ;
extern unsigned int        _Timer2_Limit ;
extern unsigned int        _Timer2Tick_per_us ;

/////////////////////////////////////////////////////////////////////////////
//  Data structures used by RTX_Count_Resources() API
/////////////////////////////////////////////////////////////////////////////

typedef struct tag_rtx_detail_sem
{
    unsigned int  Handle ;      // Semaphore "ID"
    char          szName[5] ;   // Nil terminated 4 char name
    char          Type ;        // Enumerator = KRTX_SEM_TYPE
    unsigned int  TaskQHead ;   // Task ID of task awaiting msg.
    unsigned char Use_Count ;   // Semaphore use counter
    unsigned char Attribute ;   // B0=1 if resource type semaphore
    int           Value ;       // Semaphore up/down counter
    unsigned int  Owner ;       // ID of task owning this semaphore

} RTX_DETAIL_SEM ;

// Masks for RTX_DETAIL_SEM.Attribute bit field
#define KRTX_RESOURCE_SEM  (0x1)    // Resource type semaphore
#define KRTX_SEM_BUSY      (0x2)    // Currently locked.

/////////////////////////////////////////////////////////////
typedef struct tag_rtx_detail_event
{
    unsigned int  Handle ;          // Event Group "ID"
    char          szName[5] ;       // Nil terminated 4 char name
    char          Type ;            // Enumerator = KRTX_EVENT_GROUP_TYPE
    unsigned int  TaskQHead ;       // Task ID of task awaiting msg.
    unsigned int  Current_Events ;  // Current state
} RTX_DETAIL_EVENT ;


/////////////////////////////////////////////////////////////
typedef struct tag_rtx_detail_tmr
{
    unsigned int  Handle ;      // Timer "ID"
    // Note: @Chip-RTOS timers have no 4 letter name.
 RTX_TIMER_CALLBACK Callback ;  // Vector to timer's callback.
    char          fStopped ;    // Timer stopped
    char          Type ;        // Enumerator = KRTX_TIMER_TYPE
    unsigned long Period ;      // [ms]
    unsigned long Param ;       // Timer procedures parameter

} RTX_DETAIL_TMR ;


/////////////////////////////////////////////////////////////
typedef struct tag_rtx_detail_msgxchg
{
    unsigned int  Handle ;      // Message Exchange "ID"
    char          szName[5] ;   // Nil terminated 4 char name
    char          Type ;        // Enumerator = KRTX_MSG_XCHG_TYPE
    unsigned int  TaskQHead ;   // Task ID of task awaiting msg.
    unsigned char Busy ;        // xchg busy flag
    unsigned char AvailFlags ;  // Message available flags
    // Following arrays have an entry for each message priority
    unsigned int  Slots[4];     // Msg slots available 
    unsigned int  MaxMsg[4] ;   // Maximum number of messages

} RTX_DETAIL_MSGXCHG ;


/////////////////////////////////////////////////////////////
typedef struct tag_rtx_detail_task
{
    unsigned int  Handle ;      // Task "ID"
    char          szName[5] ;   // Nil terminated 4 char name
    char          Type ;        // Enumerator = KRTX_TASK_TYPE
    unsigned int  WaitQ ;       // Node in list of tasks awaiting an object.
    unsigned int  Status ;      // Task state
    unsigned int  WaitParam ;   // Semaphore handle, if awaiting semaphore.
    unsigned int  WaitParam2 ;  // Msg Xchg handle, if awaiting message.

} RTX_DETAIL_TASK ;


// Constants for 'Type' member enumerator
#define KRTX_SEM_TYPE           (0)
#define KRTX_TIMER_TYPE         (1)
#define KRTX_EVENT_GROUP_TYPE   (2)
#define KRTX_MSG_XCHG_TYPE      (3)
#define KRTX_TASK_TYPE          (4)


/////////////////////////////////////////////////////////////
// RTX_Count_Resources(filter) bit field assignments:
//
//     This masks can be combined with '&'. For example
//
//        filter = (RTX_FILT_SEM & RTX_FILT_EVENT_GROUP)
//
//     would report both semaphores and Event Groups.

#define RTX_FILT_SEM            0xFFFE       // Report semaphores
#define RTX_FILT_TIMER          0xFFFD       // Report timers
#define RTX_FILT_EVENT_GROUP    0xFFFB       // Report Event Groups
#define RTX_FILT_MSGXCHG        0xFFF7       // Report Message Exchanges
#define RTX_FILT_TASK           0xFFEF       // Report tasks


/////////////////////////////////////////////////////////////
typedef union tag_rtx_detail
{
    void                 *pBuf ;
    RTX_DETAIL_SEM       *pSem ;           // Semaphore details
    RTX_DETAIL_TMR       *pTimer ;         // Timer details
    RTX_DETAIL_EVENT     *pEvent ;         // Event details
    RTX_DETAIL_TASK      *pTask ;          // Task details
    RTX_DETAIL_MSGXCHG   *pMsgXchg ;       // Message Exchange details

} RTX_DETAILS ;


/////////////////////////////////////////////////////////////
typedef struct tag_rtx_counts
{
    unsigned int    nTask_Avail ;       // Tasks control blocks available.
    unsigned int    nTask_In_Use ;      // Tasks control blocks in use.

    unsigned int    nObj_Avail ;        // RTX objects available.
    unsigned int    nSem_In_Use ;       // Number of semaphores existing.
    unsigned int    nTimer_In_Use ;     // Number of timers existing.
    unsigned int    nEventGrp_In_Use ;  // Number of Event Groups existing.

    unsigned int    nMsg_Xchg_Avail ;   // Number of Msg Exchanges available.
    unsigned int    nMsg_Xchg_In_Use ;  // Number of Msg Exchanges in use.

    unsigned int    nEnvelop_Avail ;    // Number of Msg Envelopes available.
    unsigned int    nEnvelop_In_Use ;   // Number of Msg Envelopes in use.

    unsigned int    nReport_Cnt ;       // Number of objects report if all
                                        // unfiltered objects were reported.
    unsigned int    nReport_Bytes ;     // Size in bytes report would be if all
                                        // unfiltered objects were reported.
    unsigned int    Internal_Err ;      // Should be zero, else RTX unhealthy.

    unsigned int    TCB_Q_Offset ;      // Wait Q offset in Task Control Block
    unsigned int    RTX_Data_Segment ;  // Segment where TCB reside

} RTX_COUNTS ;

#define TCB_NAME_OFFSET (0x8)   // Byte offset into Task Control Block
                                // where 4 byte name is located (not zero
                                // terminated).  5th byte here is validity
#define TCB_VALID_MARK  (0x50)  // marker, = ASCII 'P'.

/*****************************************************************************/
#endif  /*RTX_API_H_*/
/*****************************************************************************/
//rtxapi.h

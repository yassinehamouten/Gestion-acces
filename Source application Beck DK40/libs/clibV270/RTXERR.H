/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module      :  RTXERR.H
* Function    :  RTX RTOS error code return value definitions
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\RTXERR.H, 3, 12.04.2005 13:40:21, Andre Pribil$

****************************************************************************/

#ifndef _RTX_ERRORS___
#define _RTX_ERRORS___

////////////////////////////////////////////////////////////////////////////
//      Error Codes
////////////////////////////////////////////////////////////////////////////

    // The indented defines marked "Never happens" will never appear
    // as error codes from the RTX API.  These definitions are left
    // only for compatilibity with earlier C-library headers.

#define RTX_EC_NO_SUCH_TASK               (-1) // Invalid Task ID
#define RTX_EC_NO_FREE_MSG_ENVELOPE       (-2)
#define RTX_EC_NO_MAILBOX_DEFINED         (-3)
#define RTX_EC_MAILBOX_FULL               (-4)
#define RTX_EC_AWAKE_BEFORE_TIMEOUT       (-5)
#define RTX_EC_TASK_NOT_WAITING_2ND_WAKE  (-6)
  #define RTX_EC_CALLING_TASK_NOT_WAITING   (-7)  // Never happens
  #define RTX_EC_MSG_NOT_FROM_SEND_CALL     (-8)  // Never happens
#define RTX_EC_LOW_MEMORY                  (-9)

#define RTX_EC_NOT_OWNED_BY_CALLER        (-12)
#define RTX_EC_INVALID_TASK_PRIORITY      (-17)
#define RTX_EC_NO_FREE_TCB                (-18) // No free Task Control Block
#define RTX_EC_NO_FREE_TIMER              (-19) // No free interval timer
#define RTX_EC_NO_ABORT_PERMITTED         (-20) // Task abort (stop, kill,delete) not allowed.
#define RTX_EC_NO_SUCH_SEMAPHORE          (-22)
#define RTX_EC_SEMAPHORE_IN_USE           (-23)
#define RTX_EC_INVALID_SEMAPHORE_VALUE    (-24) // On creation
#define RTX_EC_TIMED_OUT                  (-27)
#define RTX_EC_NO_MESSAGE_AVAILABLE       (-28)
  #define RTX_EC_CALLING_TASK_WAITING       (-29) // Never happens
#define RTX_EC_NO_FREE_EVENT_GROUP        (-32)
#define RTX_EC_EVENT_GROUP_IN_USE         (-33)

#define RTX_EC_NO_SUCH_MSG_XCHG           (-41) // No such message exchange, invalid ID.
#define RTX_EC_NO_FREE_MSG_XCHG           (-42)
#define RTX_EC_MSG_XCHG_IN_USE            (-43)
#define RTX_EC_INVALID_MAILBOX_SIZE       (-44)
#define RTX_EC_NO_FREE_SEMAPHORE          (-45)
#define RTX_EC_NO_SUCH_EVENT_GROUP        (-46) // Invalid ID.
#define RTX_EC_NO_SUCH_TIMER              (-47) // Invalid ID.
#define RTX_EC_INVALID_TIMER_INTERVAL     (-48)
#define RTX_EC_SEMAPHORE_BUSY             (-51)

#define RTX_EC_NAME_NOT_FOUND             (-57)
#define RTX_EC_CALL_ILLEGAL               (-58)
#define RTX_EC_NAME_IN_USE                (-59)


////////////////////////////////////////////////////////////////////////////
//      Task State Bit Masks
//
//      Apply to Task_StateData structure taskState member
//      and RTX_Get_Task_State_Ext output parameter, 'taskstate'.
//
////////////////////////////////////////////////////////////////////////////

#define RTX_TS_TIMER_WAIT                 (0x1)
#define RTX_TS_TRIGGER_WAIT               (0x2)
#define RTX_TS_SEMAPHORE_WAIT             (0x4)
#define RTX_TS_EVENT_WAIT                 (0x8)
#define RTX_TS_MSG_XCHG_WAIT              (0x10)
#define RTX_TS_MSG_SEND_WAIT              (0x20) // Not implemented
#define RTX_TS_SUSPEND_WAIT               (0x40)
#define RTX_TS_WAITING_FOR_WAKE           (0x80)


/*************************************************************************/
#endif /* _RTX_ERRORS___ */
/*************************************************************************/
//end rtxerr.h

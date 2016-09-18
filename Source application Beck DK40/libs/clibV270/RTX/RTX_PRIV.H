/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
*  Module      :   RTX_PRIV.H
*  Function    :   Internal information for RTOS C Library.
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\RTX\RTX_PRIV.H, 10, 25.01.2007 20:36:19, Jack Gatrost$

*****************************************************************************/

#ifndef __RTX_PRIV_H__
#define __RTX_PRIV_H__

/*************************************************************************/
// RTOS Api Services
/*************************************************************************/
#define RTOSVECT     0xAD

/*****************************************************************************/
//function numbers
/*****************************************************************************/
// Task control
#define RTX_SLEEP_TIME              0x00 /* Sleep for a defined time */
#define RTX_TASK_CREATE             0x01 /* Create and start a task  */
#define RTX_TASK_KILL               0x02 /* Stop and kill a task */
#define RTX_TASK_DELETE             0x03 /* Remove a task from the system */
#define RTX_GET_TASKID              0x04 /* Get ID of the current running task */
#define RTX_SLEEP_REQ               0x05 /* Sleep, until a wake request occurs */
#define RTX_WAKEUP_TASK             0x06 /* Wake a task, which is waiting */
#define RTX_END_EXEC                0x07 /* End task execution */
#define RTX_CHANGE_PRIO             0x08 /* Change the priority of a task */
#define RTX_ACCESS_FILESYSTEM       0x09 /* Enable filesystem access for task */
#define RTX_GET_TASK_STATE          0x0A /* Get the state of a task */
#define RTX_GET_TASK_LIST           0x0B /* Get tasklist */
#define RTX_START_TASK_MONITOR      0x0C /* Start task monitoring */
#define RTX_STOP_TASK_MONITOR       0x0D /* Stop task monitoring */
#define RTX_SUSPEND_TASK            0x0E /* Suspend a task */
#define RTX_RESUME_TASK             0x0F /* Resume a task */
#define RTX_RESTART_TASK            0x10 /* Restart a killed task */
#define RTX_TASK_CREATE_WITHOUT_RUN 0x11 /* Create a task without startingRestart a killed task */
#define RTX_GET_TASK_STATE_EXT      0x12 /* Get the state of a task without taskmonitoring mode */
#define RTX_COUNT_RESOURCES         0x13 // RTX_Count_Resources()

#define RTX_DISABLE_TASK_SCHEDULING 0x20 /* Disable the taskscheduler (Taskswitching) */
#define RTX_ENABLE_TASK_SCHEDULING  0x21 /* Enable the taskscheduler (Taskswitching) */

// Semaphores
#define RTX_CREATE_SEM              0x14 /* Create a semaphore */
#define RTX_DELETE_SEM              0x15 /* Delete a semaphore */
#define RTX_FREE_RES                0x16 /* Free a resource semaphore  */
#define RTX_GET_SEM                 0x17 /* Get use of a counting semaphore(no wait) */
#define RTX_RELEASE_SEM             0x18 /* Release a resource semaphore */
#define RTX_RESERVE_RES             0x19 /* Reserve a resource semaphore */
#define RTX_SIGNAL_SEM              0x1A /* Signal a counting semaphore */
#define RTX_WAIT_SEM                0x1B /* Wait on a counting semaphore (optional timeout) */
#define RTX_FIND_SEM                0x1C /* Find a Semaphore, using 4 char name tag */

// More Task Control actions
#define RTX_SLEEP_FINE              0x1D   // Increased resolution sleep
#define RTX_WAIT_SEM_PRIO           0x1E   // Wait on a semaphore at priority

// Time/Date control
#define RTX_GET_TIMEDATE            0x28
#define RTX_SET_TIMEDATE            0x29
#define RTX_GET_TICKS               0x2A
#define RTX_RTI_COUNT               0x2B    // SC1x3 only, for higher RTI rates

// Timer procedures
#define RTX_TIMER_FINE              0x2F /* Install a high resolution timer procedure */
#define RTX_INSTALL_TIMER           0x30 /* Install a timer procedure */
#define RTX_REMOVE_TIMER            0x31 /* Remove a timer procedure from the system */
#define RTX_START_TIMER             0x32 /* Start periodic execution of a installed timer procedure */
#define RTX_STOP_TIMER              0x33 /* Stop periodic execution of a timer procedure */
#define RTX_TIMER_DELAY             0x34 // Set delay time to next callback
#define RTX_SET_RTI_HOOK            0x35 // Timer ISR callback

// Event manager
#define RTX_CREATE_EVENTGROUP       0x40 /* Create an event group */
#define RTX_DELETE_EVENTGROUP       0x41 /* Delete an event group */
#define RTX_SIGNAL_EVENTS           0x42 /* Signal one or more events in a group */
#define RTX_WAIT_EVENTS             0x43 /* Wait for all/any of a set of events in a group */
#define RTX_GET_EVENTGROUP_STATE    0x44 /* Read current state of events in a group */
#define RTX_GET_EVENT_FLAGS         0x45 /* Get saved event flags */
#define RTX_FIND_EVENTGROUP         0x46 /* Find the eventgroup id of an event group with a specific tag */

// Message exchange manager
#define RTX_CREATE_MSG              0x50 /* Create a messsage exchange */
#define RTX_DELETE_MSG              0x51 /* Delete a message exchange */
#define RTX_SEND_MSG                0x52 /* Send a message to a message exchange */
#define RTX_GET_MSG                 0x53 /* Get a message ,if any (no wait) */
#define RTX_WAIT_MSG                0x54 /* Wait for message to arrive (optional timeout) */
#define RTX_FIND_MSG                0x55 /* Find exchange ID of a message exchange by name tag */


/*************************************************************************/
#endif /* __RTX_PRIV_H__*/
/*************************************************************************/
//end rtx_priv.h
/*************************************************************************/
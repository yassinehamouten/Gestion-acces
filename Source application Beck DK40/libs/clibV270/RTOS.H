/****************************************************************************
* (C) 1999-2007 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module      : RTOS.H
* Function    : prototypes and constants of RTOS API
* ---------------------------------------------------------------------------

$Header: c:\prjPib\IPC@CHIP\CLib\RTOS.H, 23, 21.10.2008 13:18:50, Jack Gatrost$

*****************************************************************************/

#ifndef _RTOS_H___
#define _RTOS_H___

/*************************************************************************/
//includes
/*************************************************************************/
#include <DOS.H>
#include <rtxapi.h>

#ifdef CLIB_CUSTOMER_SPECIFIC
// Supply some optional patches for customer specific library.
// (For standard Beck library, this file does not exists.)
#include <RTOS_EXT.H>
#endif

/*************************************************************************/
//defines
/*************************************************************************/

#ifdef _MSC_VER /* If Microsoft C Compiler is used, define new FP_SEG and FP_OFF Macro */
    #ifdef FP_SEG
        #undef FP_SEG
    #endif
    #define FP_SEG(ptr)    ((unsigned int)(((unsigned long)ptr)>>16))

    #ifdef FP_OFF
        #undef FP_OFF
    #endif
    #define FP_OFF(ptr)    ((unsigned int)(((unsigned long)ptr)&0xFFFF))
#endif


/*************************************************************************/
//prototypes
/*************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************/
//Create a task
/*************************************************************************/
int  _cdecl RTX_Create_Task(int  far * taskID, 
                            const TaskDefBlock far *taskdefblock);
int  _cdecl RTX_Create_Task_Without_Run(int far * taskID, 
                            const TaskDefBlock far *taskdefblock);

int  _cdecl RTX_Param_Task(int  * taskID, 
                            const TASK_PARAM_DEF *taskdefblock);
int  _cdecl RTX_Param_Task_Without_Run (int                   * taskID,
                                        const TASK_PARAM_DEF  * taskdefblock) ;

/*************************************************************************/
//Delete a task from the system
/*************************************************************************/
int  _cdecl RTX_Delete_Task(int taskID);

/*************************************************************************/
//Stop and kill a task
/*************************************************************************/
int  _cdecl RTX_Kill_Task(int taskID);

/*************************************************************************/
//Go to sleep for a defined time
/*************************************************************************/
int  _cdecl RTX_Sleep_Time(unsigned int time_ms);
int  _cdecl RTX_Sleep_Fine(unsigned int time_rti);
int  _cdecl RTX_Sleep_Long(long time_rti);

/*************************************************************************/
//Go to sleep, until  wakerequest
/*************************************************************************/
int  _cdecl RTX_Sleep_Request(void);

/*************************************************************************/
//Wakeup a sleeping task
/*************************************************************************/
int  _cdecl RTX_Wakeup(int taskID);

/*************************************************************************/
//End execution of task by itself, this functions never returns
/*************************************************************************/
int  _cdecl RTX_End_Execution(void);

/*************************************************************************/
//Suspend/Resume task execution
/*************************************************************************/
int  _cdecl RTX_Suspend_Task(int taskID);
int  _cdecl RTX_Resume_Task (int taskID);

/*************************************************************************/
//Change taskprio
/*************************************************************************/
int  _cdecl RTX_Change_TaskPrio(int taskID, int priority, int  *error);
int  _cdecl RTX_Task_Priority  (int taskID, int priority) ;
#define PRIORITY_READ_ONLY (0x5ABC)

/*************************************************************************/
//Get the ID of the current running task
/*************************************************************************/
int  _cdecl RTX_Get_TaskID(void);

/*************************************************************************/
//file access
/*************************************************************************/
int  _cdecl RTX_Access_Filesystem(void);

/*************************************************************************/
//Get state of a task, using the task monitoring
/*************************************************************************/
int  _cdecl RTX_Get_Task_State(const char far * taskname, 
                               Task_StateData far * taskdata, 
                               int  * error);

/*************************************************************************/
//Get state of a task, without using the task monitoring
/*************************************************************************/
int  _cdecl RTX_Get_Task_State_Ext(const char far * taskname,
                                   unsigned int far * taskstate,
                                   int * error);

/*************************************************************************/
//Get task  list
/*************************************************************************/
int  _cdecl RTX_Get_Task_List(TaskList far * tasklist, int length);

/*************************************************************************/
//Start taskmonitoring
/*************************************************************************/
void _cdecl RTX_Start_Task_Monitor(void);

/*************************************************************************/
//Start taskmonitoring
/*************************************************************************/
void _cdecl RTX_Stop_Task_Monitor(void);

/*************************************************************************/
//Restart a  task, killed with call 0x02
/*************************************************************************/
int  _cdecl RTX_Restart_Task(int taskID);
#define     RTX_Trigger_Task  RTX_Restart_Task      // An alias

/*************************************************************************/
//Disable the Task Scheduling
/*************************************************************************/
void _cdecl RTX_Disable_Task_Scheduling(void);

/*************************************************************************/
//Enable the Task Scheduling
/*************************************************************************/
void _cdecl RTX_Enable_Task_Scheduling(void);

/*************************************************************************/
// Count RTX resources
/*************************************************************************/
int _cdecl RTX_Count_Resources (RTX_COUNTS far *counts,
                                void       far *details,
                                unsigned int    list_size,
                                unsigned int    filter) ;

/*************************************************************************/
// Read out list of tasks awaiting an RTX object
/*************************************************************************/
int _cdecl RTX_Wait_Queue (unsigned int  handle,
                           void     far *details,
                           unsigned int  list_size,
                           unsigned int  filter) ;

/*************************************************************************/
//Create a semaphore
/*************************************************************************/
int  _cdecl RTX_Create_Sem(int far *semID, const char far *name, 
                           int initvalue);

/*************************************************************************/
//Delete a  semaphore
/*************************************************************************/
int  _cdecl RTX_Delete_Sem(int semID);

/*************************************************************************/
//Free a  resource semaphore
/*************************************************************************/
int  _cdecl RTX_Free_Sem(int semID);

/*************************************************************************/
//Get a  counting semaphore
/*************************************************************************/
int  _cdecl RTX_Get_Sem(int semID);

/*************************************************************************/
//Release a  resoure semaphore
/*************************************************************************/
int  _cdecl RTX_Release_Sem(int semID);

/*************************************************************************/
//Reserve a  resoure semaphore (optional timeout)
/*************************************************************************/
int  _cdecl RTX_Reserve_Sem(int semID, long   far  * time_ms);


/*************************************************************************/
//Signal a  counting semaphore
/*************************************************************************/
int  _cdecl RTX_Signal_Sem(int semID);

/*************************************************************************/
//Wait on a  counting semaphore (optional timeout)
/*************************************************************************/
#define FIXED_WAIT_PRIORITY (20)    // Use this for 'wait_priority' on all
                                    //  RTX_Reserve_Sem calls if FIFO order
                                    //  is desired.
int  _cdecl RTX_Wait_Sem(int semID, long  far  *time_ms);
int  _cdecl RTX_Wait_Sem_Priority (int          semID, 
                                   long         time_ms, 
                                   unsigned int wait_priority) ;


/*************************************************************************/
//Find an semaphore, specified by 4 char name tag
/*************************************************************************/
#ifndef RTX_Find_Sem
int  _cdecl RTX_Find_Sem(int far *ID, const char far *name);
#endif

/*************************************************************************/
//Get system time and date
/*************************************************************************/
int      _cdecl RTX_Get_TimeDate   (TimeDate_Structure  far  * td);
int  far _cdecl RTX_Get_TimeDate_us(TimeDateFineS  far  * td);

/*************************************************************************/
//Set system time and date
/*************************************************************************/
int      _cdecl RTX_Set_TimeDate   (const TimeDate_Structure  far  * td);
int  far _cdecl RTX_Set_TimeDate_us(const TimeDateFineS  far  * td);

/*************************************************************************/
//Set system ticks
/*************************************************************************/
void _cdecl RTX_Get_System_Ticks(unsigned long far * ticks);

unsigned long _cdecl RTX_GetTickCount (   void  ) ;
#ifdef RTI_ADJUSTABLE
unsigned long _cdecl RTX_Get_RTI_Ticks(void) ;  // SC1x3 only
unsigned int  _cdecl RTX_Get_RTI_Rate(void) ;
#else
#define RTX_Get_RTI_Ticks  RTX_GetTickCount     // For SC1x systems
#define RTX_Get_RTI_Rate()  (1)                 // Fixed 1 kHz rate
#endif

void _cdecl RTX_FineTickInit (void) ;
void _cdecl RTX_GetFineTick (RTX_FINE_TICK *report) ;
unsigned long _cdecl RTX_GetTick_us (void) ;

typedef unsigned char huge (far * RTI_HOOK) (void) ;
void _cdecl RTX_Install_RTI_Hook (RTI_HOOK vector, unsigned char delay) ;

/*************************************************************************/
//Install timer procedure
/*************************************************************************/
int  _cdecl RTX_Install_Timer (const TimerProc_Structure far * TProcPtr) ;

/*************************************************************************/
// Alternate timer procedure install method, using explicit
//   parameters, equivalent to RTX_Install_Timer().
/*************************************************************************/

int  _cdecl RTX_Install_TimerP (unsigned int  far  *timerID, 
                                RTX_TIMER_CALLBACK  proc,
                                unsigned long       lParam, 
                                unsigned long       name,
                                long                interval) ;

#ifdef RTI_ADJUSTABLE           // SC1x3 only
int  _cdecl RTX_Fine_Timer (const TimerProc_Structure far * TProcPtr) ;
int  _cdecl RTX_Fine_TimerP (unsigned int  far  *timerID, 
                             RTX_TIMER_CALLBACK  proc,
                             unsigned long       lParam, 
                             unsigned long       name,
                             long                rti_ticks) ;

#else                           // For SC1x

#define RTX_Fine_Timer  RTX_Install_Timer
#define RTX_Fine_TimerP RTX_Install_TimerP

#endif  // RTI_ADJUSTABLE

/*************************************************************************/
// Remove timer procedure
/*************************************************************************/
int  _cdecl RTX_Remove_Timer(unsigned int timerID);

/*************************************************************************/
// Start periodic execution of timer procedure
/*************************************************************************/
int  _cdecl RTX_Start_Timer(unsigned int timerID);
int  _cdecl RTX_Timer_Delay(unsigned int timerID, long delay_ms) ;
int  _cdecl RTX_Timer_Delay_RTI(unsigned int timerID, long rti_ticks) ;

/*************************************************************************/
// Stop periodic execution of timer procedure
/*************************************************************************/
int  _cdecl RTX_Stop_Timer(unsigned int timerID);

/*************************************************************************/
// Create event group
/*************************************************************************/
int  _cdecl RTX_Create_EventGroup (unsigned int far *id_ptr, 
                                   const char   far *name, 
                                   unsigned int init_value) ;

/*************************************************************************/
// Delete an event group
/*************************************************************************/
int  _cdecl RTX_Delete_EventGroup(unsigned int id);

/*************************************************************************/
// Signal events group
/*************************************************************************/
int  _cdecl RTX_Signal_Events (unsigned int id, 
                               unsigned int event_mask, 
                               unsigned int event_value) ;

/*************************************************************************/
// Wait for events
/*************************************************************************/
int  _cdecl RTX_Wait_For_Event (unsigned int id, 
                                const RTX_Wait_Event far * event_ptr) ;

// Alternative method, using explicit parameters
int  _cdecl RTX_Wait_For_EventP (unsigned int id,    unsigned int mask,  
                                 unsigned int value, int match, long timeout) ;

/*************************************************************************/
// Read current events on a group
/*************************************************************************/
int  _cdecl RTX_Get_EventGroup_State (unsigned int id, 
                                      unsigned int far * event) ;

/*************************************************************************/
// Get the saved event flags/bits
/*************************************************************************/
int  _cdecl RTX_Get_Saved_Events(unsigned int far *Event);

/*************************************************************************/
//Find an event group, specified by 4 char name tag
/*************************************************************************/
int  _cdecl RTX_Find_EventGroup(unsigned int far * id_ptr, 
                                const char far * name);

/*************************************************************************/
//Create message exchange
/*************************************************************************/
int  _cdecl RTX_Create_Msg(RTX_Msg far * msg_ptr);

/*************************************************************************/
//Delete a message exchange
/*************************************************************************/
int  _cdecl RTX_Delete_Msg(unsigned int id);

/*************************************************************************/
//Send a message to a message exchange
/*************************************************************************/
int  _cdecl RTX_Send_Msg(unsigned int id, int prio, const void far * msg);

/*************************************************************************/
//Get a message from a message exchange, no wait
/*************************************************************************/
int  _cdecl RTX_Get_Msg(unsigned int id, void far * msg);

/*************************************************************************/
//Wait for a message, optional timeout
/*************************************************************************/
#ifndef   RTX_Wait_For_Msg    // Not already defined?
int  _cdecl RTX_Wait_For_Msg (const RTX_Wait_Msg far * msg_ptr);
#endif // RTX_Wait_For_Msg

// Alternate method, with direct parameters
int  _cdecl RTX_Wait_For_MsgP (unsigned int msgID, unsigned int prio,
                               void far *msg, long timeout);

/*************************************************************************/
//Find an message exchange, specified by 4 char name tag
/*************************************************************************/
int  _cdecl RTX_Find_Msg(unsigned int far * id_ptr, const char far * name);


// SYSTEM_PUBLIC_OBJ may be used as 'data' argument to RTX_Publish()
#define SYSTEM_PUBLIC_OBJ(size)  ((void *)MK_FP(0, size))

int far _cdecl  RTX_Publish(const void far *data, const char far *nameTag) ;

const void far * far _cdecl RTX_GetPublication(const char far *nameTag) ;


#ifdef __cplusplus
}
#endif

/*************************************************************************/
#endif /* _RTOS_H___ */
/*************************************************************************/
//end rtos.h

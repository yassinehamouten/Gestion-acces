/****************************************************************************
* (C) 1999-2010 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module      : RTOS.C
* Function    : RTOS api functions
* ---------------------------------------------------------------------------

$Header: RTOS.C, 64, 12.11.2008 12:51:08, Andre Pribil$

*****************************************************************************/

#include "config.h"

#define RTI_ADJUSTABLE  // Expose declarations in rtxapi.h

#include "..\common\common.h"

#include "rtos.h"
#include "rtx_priv.h"

/*
 // Note:  The DOCLIST.EXE tool used by the C-Library HTML build process reacts
 //  to the token "#DOCLIST:" when it appears as the first non-white space
 //  on a line.  The tool transfers the text which follows into the
 //  BeckCLib.LST file that is used for the context sensitive help.
 //
 // Another Note:  The *RTX indicates that any names that start with
 //      RTX and do not match any other name in our list should lead
 //      to the HTM page stated after the *RTX.

 #DOCLIST:*RTX CLIB\RTX\lib_index.htm
 #DOCLIST:RTX_COUNTS rtxstruc.htm#RTX_COUNTS
 #DOCLIST:RTX_DETAILS rtxstruc.htm#RTX_DETAILS
 #DOCLIST:RTX_DETAIL_EVENT rtxstruc.htm#RTX_DETAIL_EVENT
 #DOCLIST:RTX_DETAIL_MSGXCHG rtxstruc.htm#RTX_DETAIL_MSGXCHG
 #DOCLIST:RTX_DETAIL_SEM rtxstruc.htm#RTX_DETAIL_SEM
 #DOCLIST:RTX_DETAIL_TASK rtxstruc.htm#RTX_DETAIL_TASK
 #DOCLIST:RTX_DETAIL_TMR rtxstruc.htm#RTX_DETAIL_TMR
 #DOCLIST:RTX_Msg rtxstruc.htm#RTX_Msg
 #DOCLIST:RTX_Wait_Event rtxstruc.htm#RTX_Wait_Event
 #DOCLIST:RTX_Wait_Msg rtxstruc.htm#RTX_Wait_Msg
 #DOCLIST:TaskDefBlock rtxstruc.htm#TaskDefBlock
 #DOCLIST:TASK_PARAM_DEF rtxstruc.htm#TASK_PARAM_DEF
 #DOCLIST:TaskList rtxstruc.htm#TaskList
 #DOCLIST:Task_StateData rtxstruc.htm#Task_StateData
 #DOCLIST:TimeDate_Structure rtxstruc.htm#TimeDate_Structure
 #DOCLIST:TimeDateFineS rtxstruc.htm#TimeDateFineS
 #DOCLIST:TimerProc_Structure rtxstruc.htm#TimerProc_Structure

 @doc DOC_INDEX
 ---------------------------------------------------------------
 RTX API Table of Contents
 ---------------------------------------------------------------
 @clibLinkIdx  <tab><cfont>#include <InBraces RTOS\.H><efont><nl>
 <tab><tab><tab><tab><tab><arial>which includes<ariale> <cfont>
 <InBraces RTXAPI\.H><efont> |
    <tab><linkto>#Task<linkmid>Task Control<linktail><tab>
    <linkto>#Semaphore<linkmid>Semaphores<linktail><tab>
    <linkto>#Timing<linkmid>Timing<linktail><tab>
    <linkto>#Event<linkmid>Events<linktail><tab>
    <linkto>#Message<linkmid>Messages<linktail><tab>
    | <nl>
    
  These API provides access to the RTOS of the IPC@CHIP&reg;.<nl>
 <nl>
 All RTOS API functions listed here are reentrant.<nl>
 <nl>
 For a general introduction about multitasking with the @CHIP-RTOS see
 <linkto>../../multitasking.htm<linkmid>Multitasking introduction<linktail>. 
 Please note that we cannot explain in detail all principles of a multitasking system in this document.<nl>
 A good book for understanding the architecture of Real-Time-Kernels is  "MicroC/OS" from Jean.J.Labrosse.<nl><nl>
 For some useful comments see also the <linkto>../../program.htm<linkmid>programming notes<linktail>.<nl>

 @textlinkpara  RTOS API | ../../rtxover.htm | Overview  |
 @textlinkpara  RTOS API | ../../rtxerrs.htm | Error Codes |
 @textlinkpara  RTOS API | ../../rtxdev.htm | Developer | Notes
 @textlinkpara  RTOS API | ../../rtxexamp.htm | Examples | Available
 @textlinkpara  RTOS API | ../../rtxstruc.htm | Data Structures  |
 @textlinkpara  IPC@CHIP&reg; System | ../../rtxtask.htm | Tasks  |  
  
 @libcat1x  Task | Control  | rtx01 | RTX_Create_Task | Create and start a task |
 @libcat1x  Task | Control  | rtx01A | RTX_Param_Task | Create and start a task with parameters |
 @libcat1x  Task | Control  | rtx11 | RTX_Create_Task_Without_Run | Create a task |
 @libcat1x  Task | Control  | rtx11A | RTX_Param_Task_Without_Run | Create a task with parameters |
 @libcat1x  Task | Control  | rtx03 | RTX_Delete_Task | Delete a task |
 @libcat1x  Task | Control  | rtx02 | RTX_Kill_Task | Stop and kill a task |
 @libcat1x  Task | Control  | rtx10 | RTX_Restart_Task | Start execution of task |
 @libcat1x  Task | Control  | rtx07 | RTX_End_Execution  | End execution of current task |
 @libcat1x  Task | Control  | rtx00 | RTX_Sleep_Time | Sleep for a defined time |
 @libcat1x  Task | Control  | rtx1D  | RTX_Sleep_Fine | Sleep for a number of RTI |
 @libcat1x  Task | Control  | rtx1DA | RTX_Sleep_Long | Sleep for a long number of RTI |
 @libcat1x  Task | Control  | rtx05 | RTX_Sleep_Request  | Sleep until wakeup request |
 @libcat1x  Task | Control  | rtx06 | RTX_Wakeup  | Wakeup a sleeping task |
 @libcat1x  Task | Control  | rtx0E | RTX_Suspend_Task  | Suspend execution of a task |
 @libcat1x  Task | Control  | rtx0F | RTX_Resume_Task  | Resume execution of a suspended task |
 @libcat1x  Task | Control  | rtx04 | RTX_Get_TaskID  | Get the ID of the current task |
 @libcat1x  Task | Control  | rtx08 | RTX_Change_TaskPrio  | <depr> Change specified task's priority |
 @libcat1x  Task | Control  | rtx08A | RTX_Task_Priority  | Read/write specified task's priority |
 @libcat1x  Task | Control  | rtx20 | RTX_Disable_Task_Scheduling  | Disable task switching |
 @libcat1x  Task | Control  | rtx21 | RTX_Enable_Task_Scheduling  | Re-enable task switching |
 @libcat1x  Task | Control  | rtx09 | RTX_Access_Filesystem  | Reserve file system access by task |

 @libcat1x  Task | Control  | rtx0B | RTX_Get_Task_List  | <nl>Get list of current tasks | <tab>-- Task Monitoring --<nl>
 @libcat1x  Task | Control  | rtx0A | RTX_Get_Task_State  | Get state of a task  |
 @libcat1x  Task | Control  | rtx12 | RTX_Get_Task_State_Ext  | Get state of a task |
 @libcat1x  Task | Control  | rtx0C | RTX_Start_Task_Monitor  | Install task monitor. |
 @libcat1x  Task | Control  | rtx0D | RTX_Stop_Task_Monitor  | Disable task monitoring |
 @libcat1x  Task | Control  | rtx13 | RTX_Count_Resources  | Count available/used resources |
 @libcat1x  Task | Control  | rtx13A | RTX_Wait_Queue  | Diagnostic routine |

 @libcat2  Semaphore  | rtx14 | RTX_Create_Sem  | Create a semaphore |
 @libcat2  Semaphore  | rtx15 | RTX_Delete_Sem | Delete a  semaphore |
 @libcat2  Semaphore  | rtx1C | RTX_Find_Sem |Find semaphore by name |
 @libcat2  Semaphore  | rtx1E | RTX_Wait_Sem_Priority | <nl>Wait with specified priority |
    <tab>-- For either type Semaphore --<nl>

 @libcat2  Semaphore  | rtx17 | RTX_Get_Sem | <nl>Get a  counting semaphore, no wait | <tab>-- For Counting Semaphores --<nl>
 @libcat2  Semaphore  | rtx1B | RTX_Wait_Sem | Wait on a  counting semaphore |
 @libcat2  Semaphore  | rtx1A | RTX_Signal_Sem | Signal a counting semaphore |

 @libcat2  Semaphore  | rtx19 | RTX_Reserve_Sem | <nl>Reserve a resource semaphore | <tab>-- For Resource Semaphores --<nl>
 @libcat2  Semaphore  | rtx16 | RTX_Free_Sem | Set use count to zero |
 @libcat2  Semaphore  | rtx18 | RTX_Release_Sem | Decrement use count by 1 |

 @libcat3  Timing   | rtx28    | RTX_Get_TimeDate    | <nl>Get system time and date  | <tab>-- Time/Date --<nl>
 @libcat3  Timing   | rtxdyn00 | RTX_Get_TimeDate_us | Get system time and date with high resolution |
 @libcat3  Timing   | rtx29    | RTX_Set_TimeDate    | Set system time and date |
 @libcat3  Timing   | rtxdyn01 | RTX_Set_TimeDate_us | Set system time and date with high resolution |
 @libcat3  Timing   | rtx2A | RTX_Get_System_Ticks | <nl>Get tick count of system clock | <tab>-- System Time --<nl>
 @libcat3  Timing   | rtx2AA | RTX_GetTickCount | Return tick count of system clock |
 @libcat3  Timing   | rtxtf3 | RTX_GetTick_us | Return system clock microseconds |
 @libcat3  Timing   | rtxtf2 | RTX_GetFineTick | Read system clock with high resolution |
 @libcat3  Timing   | rtxtf1 | RTX_FineTickInit | Initialize for RTX_GetTickCount() use |
 @libcat3  Timing   | rtx2B | RTX_Get_RTI_Ticks | Get Real-Time Interrupt count |
 @libcat3  Timing   | rtx2BA | RTX_Get_RTI_Rate | Get Real-Time Interrupt rate |

 @libcat3  Timing   | rtx30 | RTX_Install_Timer | <nl>Install timer procedure | <tab>-- RTX Timer Callbacks --<nl>
 @libcat3  Timing   | rtx30A | RTX_Install_TimerP | Install timer procedure (alternate method) |
 @libcat3  Timing   | rtx2F | RTX_Fine_Timer | Install high resolution timer |
 @libcat3  Timing   | rtx2FA | RTX_Fine_TimerP | Install high resolution timer (alternate method) |
 @libcat3  Timing   | rtx31 | RTX_Remove_Timer | Remove timer procedure |
 @libcat3  Timing   | rtx32 | RTX_Start_Timer | Start periodic execution of timer procedure |
 @libcat3  Timing   | rtx33 | RTX_Stop_Timer | Stop periodic execution of timer procedure |
 @libcat3  Timing   | rtx34 | RTX_Timer_Delay | Set timer delay milliseconds |
 @libcat3  Timing   | rtx34A | RTX_Timer_Delay_RTI | Set timer delay RTI ticks |
 @libcat3  Timing   | rtx35 | RTX_Install_RTI_Hook |  Install callback to execute in
        real-time interrupt |

 @libcat4  Event   | rtx40 | RTX_Create_EventGroup  | Create event group |
 @libcat4  Event   | rtx41 | RTX_Delete_EventGroup | Delete an event group |
 @libcat4  Event   | rtx42 | RTX_Signal_Events | Signal events group |
 @libcat4  Event   | rtx43 | RTX_Wait_For_Event | Wait for events |
 @libcat4  Event   | rtx43A | RTX_Wait_For_EventP | Wait for events (alternate method)|
 @libcat4  Event   | rtx44 | RTX_Get_EventGroup_State | Read current events on a group |
 @libcat4  Event   | rtx45 | RTX_Get_Saved_Events | Get the saved event flags/bits |
 @libcat4  Event   | rtx46 | RTX_Find_EventGroup | Find an event group |

 @libcat5  Message   | rtx50 | RTX_Create_Msg  | Create message exchange |
 @libcat5  Message   | rtx51 | RTX_Delete_Msg  | Delete a message exchange |
 @libcat5  Message   | rtx52 | RTX_Send_Msg  | Send a message to a message exchange |
 @libcat5  Message   | rtx53 | RTX_Get_Msg  | Get a message from a message exchange, no wait |
 @libcat5  Message   | rtx54 | RTX_Wait_For_Msg  | Wait for a message, optional timeout |
 @libcat5  Message   | rtx54A | RTX_Wait_For_MsgP  | Wait for a message, optional timeout (alternate method)|
 @libcat5  Message   | rtx55 | RTX_Find_Msg  | Find a message exchange by name |
 @libcat5  Message   | rtxdyn02 | RTX_Publish  | <nl>Post global publication  |  
    <tab>-- Global Data Registry --<nl>
 @libcat5  Message   | rtxdyn03 | RTX_GetPublication  | Find a global publication by name |

*/

#define T2CNT  0xff60           // IO address for Timer #2 Count register
#define T2CMPA 0xff62           // Timer #2 Compare register
#define T2CON  0xff66           // Timer #2 Control/Mode register
#define INTSTS 0x0FF30          // Interrupt Status: B2=TMR2 pending ...
#define TMR2_BIT 0x4            // B2 Bit within INTSTS reg


/*************************************************************************/
//Task control functions
/*************************************************************************/


/*************************************************************************/
// Go to sleep for a defined time
/*************************************************************************/
#ifdef _rtx00_
/*
 @doc DOC_rtx00_
 ---------------------------------------------------------------
 RTX Sleep Time
 ---------------------------------------------------------------
 @clib  RTX_Sleep_Time | Go to sleep for a specified number of milliseconds.  |
        <cfont>int RTX_Sleep_Time ( unsigned int time_ms ); <efont> |
 @parm  int | time_ms | Sleep time in milliseconds.<s2> A zero delay
          time is translated to 1 millisecond within this API.
 @rdesc 0 on success else <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The  <linkto>rtx06.htm<linkmid>RTX_Wakeup<linktail> function can wake
        up a sleeping task before its sleep timer has expired.<nl>
        <nl>
        If the task has an outstanding wake request pending when it calls here,
        the task will continue execution immediately without waiting.<nl>
        <nl>
        For sleep times over 65 seconds, see
        <linkto>rtx1DA.htm<linkmid>RTX_Sleep_Long<linktail> API.
 @Also  rtx05.htm |  RTX_Sleep_Request |
        rtx06.htm | RTX_Wakeup  |
        rtx1D.htm | RTX_Sleep_Fine
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x00<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
*/
int RTX_Sleep_Time(unsigned int time_ms)
{
    _BX = time_ms ;
    _AH   = RTX_SLEEP_TIME ;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif

/***********************************************************************************************/
//create/start a task
/************************************************************************************************/
#ifdef _rtx01_
/*
 @doc DOC_rtx01_
 ---------------------------------------------------------------
 RTX Create and start a task
 ---------------------------------------------------------------
 @clib  RTX_Create_Task | Create and start a task |
        <cfont>int RTX_Create_Task ( int far *taskID,<nl>
        <tab><tab><tab><tab><tab>&nbsp; const TaskDefBlock far *taskdefblock );<efont> |
 @parm  int *  | taskID  | Output Parameter:<s2>  Pointer to 16 bit storage
        for the taskID, allocated by the caller<nl>
 @parm  int *  | taskdefblock  | Input Parameter:<s2>  Pointer to a
        <linkto>../../rtxstruc.htm#TaskDefBlock<linkmid>TaskDefBlock<linktail> type data structure
        prepared by caller.<nl>
 @rdesc 0, task is running, output location <code>taskID<codee> contains the 16 bit taskID<nl>
        non-zero --<gt>  <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The caller must <linkto>../../rtxstruc.htm#taskfill<linkmid>fill<linktail> in portions of the
        <linkto>../../rtxstruc.htm#TaskDefBlock<linkmid>TaskDefBlock<linktail> structure
        prior to making this call.<nl>
        <nl>
        The new task is immediately placed in the system's task ready queue.<s2> Execution begins if
        the task is higher priority than any other task currently ready (including task which called
        <code>RTX_Create_Task<codee>).
        This function differs with <linkto>rtx11.htm<linkmid>RTX_Create_Task_Without_Run<linktail>
        in that the new task is released to run within this function call.<nl>
        <nl>
        You may want to use the <linkto>../helper/helper07.htm<linkmid>helper_alloc_rtos_mem<linktail>
        API to allocate the new task's stack space.<s2> You can then optionally
        use the <linkto>../helper/helper0A.htm<linkmid>helper_assign_mem<linktail> API to
        reassign this stack space memory allocation to the new task.<s2> This step would
        be taken after this <code>RTX_Create_Task<codee> API has provided you the new
        task ID.<s2> Assigning the stack memory allocation to the task has the advantage
        that this stack memory will then be released automatically by the system when
        this new task is later deleted from the system.<nl>
        <nl>
        <bold>Caution:<bolde><s2>
        For small or medium memory model, the task's stack allocation will need to be made
        from the program data segment in order that the model's DS == SS flat segment requirement
        be met.<s2> This means that the RTOS memory allocation
        cited here will not be a good idea for these memory models.<s2> Although small or
        medium memory models provide more efficient programs than large memory model,
        the large memory model is highly recommended for all users interested in
        getting their program up and running without a lot of adventure.
 @Also  rtx11.htm |  RTX_Create_Task_Without_Run |
        rtx03.htm | RTX_Delete_Task  |
        ../helper/helper07.htm | helper_alloc_rtos_mem
 @Also  ../helper/helper0A.htm | helper_assign_mem |
         |   |
         |
 @related IPC@CHIP&reg; System | ../../rtxtask.htm | Tasks |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x01<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Create_Task(int far * taskID, const TaskDefBlock  far * taskdefblock)
{
    _BX = FP_SEG(taskID);
    _SI  = FP_OFF(taskID);
    asm { LES DI,taskdefblock }
    _AH   = RTX_TASK_CREATE;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif

/***********************************************************************************************/
//create/start a task
/************************************************************************************************/
#ifdef _rtx01A_
/*
 @doc DOC_rtx01A_
 ---------------------------------------------------------------
 RTX Create and start a task
 ---------------------------------------------------------------
 @clib  RTX_Param_Task | Create and start a task which is passed parameters by system. |
        <cfont>int RTX_Param_Task ( int *taskID,<nl>
        <tab><tab><tab><tab><tab>&nbsp; const TASK_PARAM_DEF *taskdefblock );<efont> |
 @parm  int *  | taskID  | Output Parameter:<s2>  Pointer to 16 bit storage
        for the taskID, allocated by the caller<nl>
 @parm  int *  | taskdefblock  | Input Parameter:<s2>  Pointer to a
        <linkto>../../rtxstruc.htm#TASK_PARAM_DEF<linkmid>TASK_PARAM_DEF<linktail> type data structure
        prepared by caller.<nl>
 @rdesc 0, task is running, output location <code>taskID<codee> contains the 16 bit taskID<nl>
        non-zero --<gt>  <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm
        The caller must fill in portions of the
        <linkto>../../rtxstruc.htm#TASK_PARAM_DEF<linkmid>TASK_PARAM_DEF<linktail> structure
        prior to making this call.<nl>
        <nl>
        The new task is immediately placed in the system's task ready queue.<s2> Execution begins if
        the task is higher priority than any other task currently ready (including task which called
        <code>RTX_Param_Task<codee>).<nl>
        <nl>
        This function differs with <linkto>rtx11A.htm<linkmid>RTX_Param_Task_Without_Run<linktail>
        in that the new task is released to run within this function call.<nl>
        <nl>
        This API is identical to the <linkto>rtx01.htm<linkmid>RTX_Create_Task<linktail>, with
        one difference.<s2> The task definition data structure used here allows a 32 bit
        parameter to specified which the system passes to the task on the stack.<s2> Any of
        the following would be valid prototypes for your task:<nl>
        <ul><nl><code>
          void huge My_TaskA(unsigned short Param1,<nl>
          <tab><tab><tab><tab><tab>unsigned short Param2) ;<nl>
          void huge My_TaskB(unsigned short Param1) ;<nl>
          void huge My_TaskC(void far *this_object) ;<nl>
          void huge My_TaskD(void near *this_object) ;<nl>
        <codee><ule><nl>
        Each of these tasks, except for <code>My_TaskA<codee>, would need to be cast
        to type <code>PARAM_TASK<codee> when assigned to the <code>proc<codee> member of the
        <linkto>../../rtxstruc.htm#TASK_PARAM_DEF<linkmid>TASK_PARAM_DEF<linktail> structure.<s2>
        For My_TaskC case, the following settings for <code>Param1<codee> and
        <code>Param2<codee>
        <linkto>../../rtxstruc.htm#TParams<linkmid>members<linktail> in the <code>TASK_PARAM_DEF<codee>
        structure would be required so that the far pointer <code>this_object<codee> parameter
        would point to <code>My_Object<codee>:<nl>
        <ul><nl>
          Task_Def.Param1 = FP_OFF(&My_Object) ;<nl>
          Task_Def.Param2 = FP_SEG(&My_Object) ;<nl>
        <ule><nl>
        For My_TaskD case, the pointer to the near <code>My_Object<codee> can be set using
        only the first 16 bit parameter as follows:<nl>
        <ul><nl>
          Task_Def.Param1 = (unsigned short)((void near *)&My_Object) ;<nl>
        <ule><nl>
        In the case where your task only uses a single 16 bit parameter, the system has
        pushed the second parameter onto the stack as well but it is of no consequence
        to your task.<nl>
 @Also  rtx11A.htm |  RTX_Param_Task_Without_Run |
        rtx01.htm | RTX_Create_Task |
        rtx03.htm | RTX_Delete_Task
 @related IPC@CHIP&reg; System | ../../rtxtask.htm | Tasks |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x01<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/
int RTX_Param_Task(int * taskID, const TASK_PARAM_DEF  * taskdefblock)
{
    _BX = FP_SEG(taskID);
    _SI  = FP_OFF(taskID);
    _ES  = FP_SEG(taskdefblock) ;
    _DI  = FP_OFF(taskdefblock) ;
    _AH   = RTX_TASK_CREATE;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif


#ifdef _rtx11_
/*
 @doc DOC_rtx11_
 ---------------------------------------------------------------
 RTX Create task without run
 ---------------------------------------------------------------
 @clib  RTX_Create_Task_Without_Run | Create a task which is passed parameters
    by system, but do not start the task yet.|
        <cfont>int RTX_Create_Task_Without_Run ( int far *taskID,<nl>
        <tab><tab><tab><tab><tab><tab> const TaskDefBlock far *taskdefblock ); <efont> |
 @parm  int *  | taskID  | Output Parameter:<s2>Pointer to 16 bit storage
        for the taskID, allocated by the caller<nl>
 @parm  int *  | taskdefblock  | Input Parameter:<s2>Pointer to a
        <linkto>../../rtxstruc.htm#TaskDefBlock<linkmid>TaskDefBlock<linktail> type data structure
        prepared by caller.<nl>
 @rdesc 0, task is created, output location <code>taskID<codee> contains the 16 bit taskID<nl>
        non-zero --<gt>  <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The caller must <linkto>../../rtxstruc.htm#taskfill<linkmid>fill<linktail> in portions of the
        <linkto>../../rtxstruc.htm#TaskDefBlock<linkmid>TaskDefBlock<linktail> structure
        prior to making this call.<nl>
        <nl>
        The <linkto>rtx10.htm<linkmid>RTX_Restart_Task<linktail> function must be called to
        start this new task.
 @Also  rtx01.htm | RTX_Create_Task  |
        rtx03.htm | RTX_Delete_Task  |
        rtx10.htm | RTX_Restart_Task
 @Also  rtx11A.htm | RTX_Param_Task_Without_Run  |
         |   |  |
 @related IPC@CHIP&reg; System | ../../rtxtask.htm | Tasks |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x11<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.01 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Create_Task_Without_Run (int                 far * taskID,
                                 const TaskDefBlock  far * taskdefblock)
{
    _BX  = FP_SEG(taskID);
    _SI  = FP_OFF(taskID);
    asm { LES DI,taskdefblock }
    _AH   = RTX_TASK_CREATE_WITHOUT_RUN ;
    asm { int RTOSVECT  } ;
    return _AX ;                        // return error code
}
#endif

#ifdef _rtx11A_
/*
 @doc DOC_rtx11A_
 ---------------------------------------------------------------
 RTX Create task with parameters, do not run yet
 ---------------------------------------------------------------
 @clib  RTX_Param_Task_Without_Run | Create a task which will be passed
     a parameter, but do not start it yet.|
        <cfont>int RTX_Param_Task_Without_Run ( int *taskID,<nl>
        <tab><tab><tab><tab><tab><tab> const TASK_PARAM_DEF *taskdefblock ); <efont> |
 @parm  int *  | taskID  | Output Parameter:<s2>Pointer to 16 bit storage
        for the taskID, allocated by the caller<nl>
 @parm  int *  | taskdefblock  | Input Parameter:<s2>Pointer to a
        <linkto>../../rtxstruc.htm#TASK_PARAM_DEF<linkmid>TASK_PARAM_DEF<linktail>
        type data structure prepared by caller.<nl>
 @rdesc 0, task is created, output location <code>taskID<codee> contains the 16 bit taskID<nl>
        non-zero --<gt>  <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The caller must fill in portions of the
        <linkto>../../rtxstruc.htm#TASK_PARAM_DEF<linkmid>TASK_PARAM_DEF<linktail> structure
        prior to making this call.<nl>
        <nl>
        The <linkto>rtx10.htm<linkmid>RTX_Restart_Task<linktail> function must be called to
        start this new task.<nl>
        <nl>
        This API is identical to the
        <linkto>rtx11.htm<linkmid>RTX_Create_Task_Without_Run<linktail>, with
        one difference.<s2>  The task definition data structure used here allows
        a 32 bit parameter to specified which the system passes to the task
        on the stack.<nl>

 @Also  rtx01.htm | RTX_Param_Task  |
        rtx03.htm | RTX_Delete_Task  |
        rtx10.htm | RTX_Restart_Task
 @Also  rtx11.htm | RTX_Create_Task_Without_Run  |
         |   |  |
 @related IPC@CHIP&reg; System | ../../rtxtask.htm | Tasks |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x11<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/
int RTX_Param_Task_Without_Run (int                   * taskID,
                                const TASK_PARAM_DEF  * taskdefblock)
{
    _BX  = FP_SEG(taskID);
    _SI  = FP_OFF(taskID);
    _ES  = FP_SEG(taskdefblock) ;
    _DI  = FP_OFF(taskdefblock) ;
    _AH   = RTX_TASK_CREATE_WITHOUT_RUN ;
    asm { int RTOSVECT  } ;
    return _AX ;                        // return error code
}
#endif


/*************************************************************************/
// Stop and kill a task
/*************************************************************************/
#ifdef _rtx02_
/*
 @doc DOC_rtx02_
 ---------------------------------------------------------------
 RTX Kill task
 ---------------------------------------------------------------
 @clib  RTX_Kill_Task | Kill the specified task.<s2>
        The killed task remains in the system and can be restarted.  |
        <cfont>int RTX_Kill_Task ( int taskID );<efont> |
 @parm  int  | taskID  | Task handle returned from
        <linkto>rtx01.htm<linkmid>RTX_Create_Task<linktail> or
        <linkto>rtx11.htm<linkmid>RTX_Create_Task_Without_Run<linktail>.
 @rdesc 0, success<nl>
        non-zero --<gt>  <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  This function will force a ready, executing or suspended task to end.<s2>
        All requests for task execution pending at the time of the kill request
        will be erased.
        <nl><nl>
        A task can kill itself.
        <nl><nl>
        You should not delete or kill a task which is waiting on a
        <linkto>../../rtxover.htm#Semaphore<linkmid>semaphore<linktail>,
        <linkto>../../rtxover.htm#Message<linkmid>Message Exchange<linktail>
        or <linkto>../../rtxover.htm#Event<linkmid>Event Group<linktail>.<s2>
        Same goes for a task that is in possession of
        a resource type semaphore.<s2>  Also the consequences of killing a task that had
        acquired a counting semaphore must be considered.

 @Also  rtx07.htm | RTX_End_Execution |
        rtx03.htm | RTX_Delete_Task   |
        rtx10.htm | RTX_Restart_Task
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x02<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Kill_Task(int taskID)
{
    _BX = taskID ;
    _AH   = RTX_TASK_KILL ;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif



/*************************************************************************/
// Delete a task
/*************************************************************************/
#ifdef _rtx03_
/*
 @doc DOC_rtx03_
 ---------------------------------------------------------------
 RTX Delete task
 ---------------------------------------------------------------
 @clib  RTX_Delete_Task | Remove specified task from system. |
        <cfont>int RTX_Delete_Task ( int taskID );<efont> |
 @parm  int  | taskID  | Task handle returned from
        <linkto>rtx01.htm<linkmid>RTX_Create_Task<linktail> or
        <linkto>rtx11.htm<linkmid>RTX_Create_Task_Without_Run<linktail>.
 @rdesc 0, task is removed.<nl>
        non-zero --<gt>  <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm   You should not delete or kill a task which is waiting on a
        <linkto>../../rtxover.htm#Semaphore<linkmid>semaphore<linktail>,
        <linkto>../../rtxover.htm#Message<linkmid>Message Exchange<linktail>
        or <linkto>../../rtxover.htm#Event<linkmid>Event Group<linktail>.<s2>
        Same goes for a task that is in possession of
        a resource type semaphore.<s2>  Also the consequences of killing a task that had
        acquired a counting semaphore must be considered.
        <nl><nl>
        After making this call, the <code>taskID<codee> is no longer valid.<nl><nl>
        A task can remove itself.
        <nl><nl>
         CAUTION:<nl>
         <ul><nl>
         Any memory allocated from the system by the task which is
         being deleted here will be released.<nl>
         <ule>
 @Also  rtx01.htm | RTX_Create_Task |
        rtx11.htm | RTX_Create_Task_Without_Run |
        rtx02.htm | RTX_Kill_Task
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x03<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Delete_Task(int taskID)
{
    _BX = taskID ;
    _AH   = RTX_TASK_DELETE ;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif



/*************************************************************************/
// Get the ID of the current running task
/*************************************************************************/
#ifdef _rtx04_
/*
 @doc DOC_rtx04_
 ---------------------------------------------------------------
 RTX Get Task ID
 ---------------------------------------------------------------
 @clib  RTX_Get_TaskID | Get ID of the currently executing task. |
        <cfont>int RTX_Get_TaskID ( void );<efont> |
 @parm  int  | | -- none --
 @rdesc task ID.
 @Also  rtx01.htm |  RTX_Create_Task | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x04<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Get_TaskID(void)
{
    _AH = RTX_GET_TASKID ;
    asm { int RTOSVECT  } ;
    return _AX ;            // Return task ID
}
#endif


/*************************************************************************/
// Go to sleep, until wakeup request
/*************************************************************************/
#ifdef _rtx05_
/*
 @doc DOC_rtx05_
 ---------------------------------------------------------------
 RTX Sleep Request
 ---------------------------------------------------------------
 @clib  RTX_Sleep_Request | The calling task will sleep until
        some other task makes a
        <linkto>rtx06.htm<linkmid>RTX_Wakeup<linktail> call. |
        <cfont>int RTX_Sleep_Request ( void );<efont> |
 @parm  int  |   | -- none --
 @rdesc 0: Always success.
 @comm  If the task has an outstanding wake request pending when it
        calls here, the task will continue execution immediately without waiting.
 @Also  rtx06.htm | RTX_Wakeup |
        rtx00.htm | RTX_Sleep_Time  | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x05<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Sleep_Request(void)
{
    _AH   = RTX_SLEEP_REQ ;
    asm { int RTOSVECT  } ;
    return _DX;
}
#endif

/*************************************************************************/
// Wakeup a sleeping task
/*************************************************************************/
#ifdef _rtx06_
/*
 @doc DOC_rtx06_
 ---------------------------------------------------------------
 RTX Wakeup
 ---------------------------------------------------------------
 @clib  RTX_Wakeup | Wake up a task expected to be waiting within a
        <linkto>rtx05.htm<linkmid>RTX_Sleep_Request<linktail> or
        <linkto>rtx00.htm<linkmid>RTX_Sleep_Time<linktail> call. |
        <cfont>int RTX_Wakeup ( int taskID );<efont> |
 @parm  int  | taskID  | Task handle returned from
        <linkto>rtx01.htm<linkmid>RTX_Create_Task<linktail> or
        <linkto>rtx11.htm<linkmid>RTX_Create_Task_Without_Run<linktail>.
 @rdesc 0, success<nl>
        non-zero --<gt>  <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  If the task is not currently sleeping, then the RTOS sets a "wakeup pending"
        flag for the respective task such that on the next call the task makes
        to one of the sleep functions it will return ("wake up") immediately.<nl>
        <nl>
        An immediate task switch will occur if the task being wakened is of
        higher priority than the current task.
 @Also  rtx05.htm |  RTX_Sleep_Request |
        rtx00.htm | RTX_Sleep_Time  | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x06<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Wakeup(int taskID)
{
    _BX = taskID ;
    _AH = RTX_WAKEUP_TASK ;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif

/*************************************************************************/
// End execution of task by itself, this functions never returns
/*************************************************************************/
#ifdef _rtx07_
/*
 @doc DOC_rtx07_
 ---------------------------------------------------------------
 RTX End execution
 ---------------------------------------------------------------
 @clib  RTX_End_Execution | End execution of current task.<s2>
        This call can only be used to terminate the task which is
        making the call.  |
        <cfont>int RTX_End_Execution ( void );<efont> |
 @parm  int  |   | -- none --
 @rdesc There is no return from this function.
 @comm  A call to this function is equivalent to a return from the
        task's main procedure.<nl>
        <nl>
        The task can later be restarted with the
        <linkto>rtx10.htm<linkmid>RTX_Restart_Task()<linktail> API.
        <nl>
 @Also  rtx03.htm | RTX_Delete_Task  |
        rtx10.htm | RTX_Restart_Task |
        rtx02.htm | RTX_Kill_Task
 @Also  rtx0E.htm | RTX_Suspend_Task  | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x07<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_End_Execution(void)
{
    _AH   = RTX_END_EXEC ;
    asm { int RTOSVECT  } ;
    return _AX;
}
#endif

/*************************************************************************/
// Change taskprio
/*************************************************************************/
#ifdef _rtx08_
/*
 @doc DOC_rtx08_
 ---------------------------------------------------------------
 RTX Change Priority
 ---------------------------------------------------------------
 @clib  RTX_Change_TaskPrio | Change specified task's priority. |
        <cfont>int RTX_Change_TaskPrio ( int taskID, int priority,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; int *error );<efont> |
 @depr  rtx08A.htm | RTX_Task_Priority
 @parm  int  | taskID  | Task handle returned from
        <linkto>rtx01.htm<linkmid>RTX_Create_Task<linktail> or
        <linkto>rtx11.htm<linkmid>RTX_Create_Task_Without_Run<linktail>.<nl>
        Set to zero for current task.
 @parm  int  | priority  | Task priority in range 2...127
        where priority 2 is high and 127 is low.
 @parm  int  | error  | Output Parameter:<s2> Pointer to error variable
 @rdesc 0, success.<nl>
        non-zero --<gt>   Variable error contains <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm
        The calling tasks' priority can be adjusted by setting the
        <cfont>taskID<efont> parameter to zero.<s2> The
        <linkto>../../rtxtask.htm<linkmid>AMXK<linktail> kernel
        task's priority cannot be changed.<nl>
        <nl>
        An out of range <code>priority<codee> value will be limited to
        range 2..127 inside this function.<s2> (An exception is the
        value 0x5ABC for which no operation will be performed.)
 @Also  rtx04.htm |  RTX_Get_TaskID |
        rtx20.htm |  RTX_Disable_Task_Scheduling  |
        rtx08A.htm | RTX_Task_Priority
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x08<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
*/
int RTX_Change_TaskPrio(int taskID, int priority, int *error)
{
    _CX = priority ;
    _BX = taskID ;
    _AH = RTX_CHANGE_PRIO ;
    asm { int RTOSVECT  } ;
    *error = _AX;

    return _DX;
}
#endif

/*************************************************************************/
//  Task Priority
/*************************************************************************/
#ifdef _rtx08A_
/*
 @doc DOC_rtx08A_
 ---------------------------------------------------------------
 RTX Task Priority
 ---------------------------------------------------------------
 @clib  RTX_Task_Priority | Read out existing and/or set a
     task's priority. |
        <cfont>int RTX_Task_Priority ( int taskID, int priority);<efont> |
 @parm  int  | taskID  | Task handle returned from
        <linkto>rtx01.htm<linkmid>RTX_Create_Task<linktail> or
        <linkto>rtx11.htm<linkmid>RTX_Create_Task_Without_Run<linktail>,<nl>
        or set to zero to indicate the current task.
 @parm  int  | priority  | Task priority in range 2...127
        where priority 2 is high and 127 is low,
        or set to <cfont>PRIORITY_READ_ONLY<efont> (=0x5ABC) to make no change
        to the task priority and only read out the existing task priority.
 @rdesc non-negative, success:<s2> Existing task priority (prior to any change)<nl>
        negative, failure:<s2>  <linkto>../../rtxerrs.htm<linkmid>error<linktail> code,
        such as -1 for "Invalid task ID".
 @comm
        Set the <cfont>priority<efont> parameter to <cfont>PRIORITY_READ_ONLY<efont>
        if you only want to read out the task's priority without making any
        change.<nl>
        <nl>
        The calling tasks' priority can be read out or adjusted by setting the
        <cfont>taskID<efont> parameter to zero.<s2> The
        <linkto>../../rtxtask.htm<linkmid>AMXK<linktail> kernel
        task's priority cannot be changed.<nl>
        <nl>
        An out of range <code>priority<codee> value will be limited to
        range 2..127 inside this function.
 @Also  rtx04.htm |  RTX_Get_TaskID |
        rtx20.htm |  RTX_Disable_Task_Scheduling  |
        rtx08.htm | RTX_Change_TaskPrio
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x08<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
*/
int RTX_Task_Priority(int taskID, int priority)
{
    _CX = priority ;
    _BX = taskID ;
    _AH = RTX_CHANGE_PRIO ;
    asm { int RTOSVECT  } ;
    if (_DX == 0)
    {
        _AX = _CX ;         // Return priority reading.
    }
    return _AX;
}
#endif

/*************************************************************************/
// access file system
/*************************************************************************/
#ifdef _rtx09_
/*
 @doc DOC_rtx09_
 ---------------------------------------------------------------
 RTX access file system
 ---------------------------------------------------------------
 @clib  RTX_Access_Filesystem | Reserve file access context space
       for the calling task. |
        <cfont>int RTX_Access_Filesystem ( void );<efont> |
 @parm  int  |  | -- none --
 @rdesc 0, success<nl>
        -1 --<gt> Failure (Too many tasks with file access)
 @comm   This API is deprecated.<s2> (However, it may still have some
       diagnostic value to determine why file accesses are failing
       or could be used to acquire the file access context space
       ahead of time to assure the task's future file accesses
       will succeed.)<nl>
       <nl>
       It is no longer necessary that
       a task use this API to gain access to the file system.<s2>
       A task is automatically granted file system access when the
       file system API is used, provided that the system has not
       ran out of file access context space.<nl>
       <nl>
       The file system supports registration of up to 15 tasks
       (35 tasks on SC1x3/SC2x) at a time.<s2>  Each DOS program's main task
       is registered with the file system regardless of whether
       or not that program uses the file system.<s2> A task's reservation
       on the file system access context space remains in effect until that
       task is deleted from the system.<s2> The DOS program main tasks
       are deleted when the program terminates (or
       <linkto>../../dosemu.htm#0x210x31<linkmid>terminates and stays resident<linktail>).
       <nl><nl>
       Once a successful call to this API has been made, any further
       calls perform no operation (at most one context slot is assigned
       per task).<nl>
       <nl>
       If this API returns a failure indication, then the number of tasks
       registered with the file system has reached the limit and this
       calling task is consequently not being granted access to the
       file system.<nl>
       <nl>
       The number of tasks signed into file system can be seen in
       the <linkto>../../command.htm#MEM<linkmid>MEM<linktail> command's
       console output.

 @Also  rtx01.htm |  RTX_Create_Task | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x09<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
*/
int RTX_Access_Filesystem (void)
{
    _AH = RTX_ACCESS_FILESYSTEM ;
    asm { int RTOSVECT  } ;

    return _AX ;
}

#endif



/*************************************************************************/
//Get state of a task, using the task monitoring mode
/*************************************************************************/
#ifdef _rtx0A_
/*
 @doc DOC_rtx0A_
 ---------------------------------------------------------------
 RTX Get state of a task
 ---------------------------------------------------------------
 @clib  RTX_Get_Task_State | Get status information
             for a task specified by name. |
        <cfont>int RTX_Get_Task_State ( const char far *taskname,<nl>
        <tab><tab><tab><tab><tab><tab> Task_StateData far *taskdata,<nl>
        <tab><tab><tab><tab><tab><tab> int *error );<efont> |
 @parm  int * | taskname  | Input parameter, pointer to 4 character
        unique name tag of the task whose state information is desired.
 @parm  int * | taskdata  | Output parameter, pointer to a
        <code>Task_StateData<codee>
        <linkto>../../rtxstruc.htm#Task_StateData<linkmid>type<linktail>
        structure, allocated by the user which will receive data.
 @parm  int * | error  | Output parameter, pointer to 16 bit word to
        receive error code indicator:  0 on success, else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @rdesc -1 ==<gt> Failure, error code was output to <code>error<codee><s2>
        In this case error code 0 means that <linkto>rtx0c.htm<linkmid>Task Monitoring<linktail>
        is not enabled.<nl>
        Other ==<gt> Task ID<nl>
 @comm  The task monitoring mode must be enabled in order to obtain the
        <code>taskCount<codee> member.<nl>
        <nl>
        When only the task's state is needed, the alternative
        <linkto>rtx12.htm<linkmid>RTX_Get_Task_State_Ext()<linktail> function can
        be used, which executes faster.
 @Also  rtx12.htm |  RTX_Get_Task_State_Ext |
        rtx0C.htm |  RTX_Start_Task_Monitor | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x0A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Get_Task_State (const char     far * taskname,
                        Task_StateData far * taskdata,
                        int            * error)
{
    int return_status ;
    int error_code = 0 ;
    asm {les    DI,taskname} ;
    asm {push DS } ;
    asm {lds    SI,taskdata} ;
    _AH = RTX_GET_TASK_STATE ;
    asm { int RTOSVECT  } ;
    asm { pop DS } ;
    return_status = _AX ;       // Task ID (if found)
    if (_DX != 0)
    {
        error_code = return_status ;
        return_status = _DX ;
    }
    *error = error_code ;
    return return_status ;
}
#endif

/*************************************************************************/
// Get state of a task, without using task monitoring mode
/*************************************************************************/
#ifdef _rtx12_
/*
 @doc DOC_rtx12_
 ---------------------------------------------------------------
 RTX Get state of a task without using task monitoring mode
 ---------------------------------------------------------------
 @clib  RTX_Get_Task_State_Ext | Get state of a task specified by name. |
        <cfont>int RTX_Get_Task_State_Ext ( const char far *taskname,<nl>
        <tab><tab><tab><tab><tab><tab><tab> unsigned int far *taskstate,<nl>
        <tab><tab><tab><tab><tab><tab><tab> int *error );<efont> |
 @parm  int * | taskname  | Input parameter:<s2>Pointer to 4 character
        unique name tag of the task whose state information is desired.
 @parm  int * | taskstate  | Output parameter:<s2>  Pointer to 16 bit  word
        which will receive task state bit field defined below.
 @parm  int * | error  | Output parameter:<s2>Pointer to 16 bit word to
        receive error code indicator:  0 on success, else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @rdesc -1 ==<gt> Failure, error code was output to <code>error<codee><nl>
        Other ==<gt> Task ID<nl>
 @comm  The <code>taskstate<codee> bit field is coded as follows:<nl>
        <ul>
         B0: timer wait (used with other bits)<nl>
         B1: trigger wait (i.e. idle)<nl>
         B2: semaphore wait<nl>
         B3: event group wait<nl>
         B4: message exchange wait<nl>
         B5: message send wait<nl>
         B6: suspended (waiting for resume)<nl>
         B7: waiting for wakeup<nl>
        <nl>
        B8 - B15 internal use only<nl>
        <ule>
 @Also  rtx0A.htm |  RTX_Get_Task_State |
        rtx13.htm | RTX_Count_Resources | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @related  | ../../command.htm#MEM | MEM | shell command
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x12<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.01 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Get_Task_State_Ext (const char   far * taskname,
                            unsigned int far * taskstate,
                            int          * error)
{
    int return_status ;

    *error=0;
    asm {les  DI,taskname} ;
    _AH = RTX_GET_TASK_STATE_EXT ;
    asm { int RTOSVECT  } ;
    return_status = _AX ;

    if (_DX != 0)
    {
        *error = return_status ;
        return (int)_DX ;
    }
    _CX =_BX;      //must bx at cx, because of following assigment
    *taskstate    = _CX ;
    return return_status ;
}
#endif

/*************************************************************************/
// Get count of RTX resources available and used
/*************************************************************************/
#ifdef _rtx13_
/*
 @doc DOC_rtx13_
 ---------------------------------------------------------------
 Get count of RTX resources available and used
 ---------------------------------------------------------------
 @clib  RTX_Count_Resources | This diagnostic routine reads out the
       number of RTX resources available and optionally obtains detailed
       data about the resources that are in use. |
        <cfont>int RTX_Count_Resources (RTX_COUNTS  far *counts,<nl>
        <tab><tab><tab><tab><tab><tab> void<tab><s2>  far *details,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned int<tab> list_size,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned int<tab>filter );<efont> |
 @parm  int * | counts  | Output parameter:<s2>Pointer to an
         <linkto>../../rtxstruc.htm#RTX_COUNTS<linkmid>RTX_COUNTS<linktail>
            data structure that will be filled by this API.
 @parm  int * | details  | Optional Output parameter:<s2>   Pointer to
            a buffer which will receive objects which can be referenced
            with the
            <linkto>../../rtxstruc.htm#RTX_DETAILS<linkmid>RTX_DETAILS<linktail>
             union of structure pointers.<s2> This API will report various
             details for each RTX object to this buffer.<s2> This parameter
             can be set to NULL if no detailed RTX object data is desired.<nl>
 @parm  int | list_size  | Number of bytes in buffer at
          <code>details<codee>.<s2> If either this value
          is zero or <code>details<codee> is NULL, then no
          <code>RTX_DETAILS<codee> reporting is done.<nl>
 @parm  int | filter  | Optional output listing filter.<s2> This bit field
          selects which type RTX objects are listed in detailed report at
          <code>details<codee>.<s2> Set this to zero to report all object
          types.
 @rdesc        <hangpara 20:30>
        -1:<s2> Pointer <code>counts<codee> was not valid.<paraend>
       <hangpara 20:30>
       <gt>= 0:<s2> Number of
       <linkto>../../rtxstruc.htm#RTX_DETAILS<linkmid>RTX_DETAILS<linktail>
       structures output to array at <code>details<codee>.<s2> If this
       count is lower than the <code>nReport_Cnt<codee> member of the
       <linkto>../../rtxstruc.htm#RTX_COUNTS<linkmid>RTX_COUNTS<linktail>
       output to <code>counts<codee> then the report was not complete
       due to insufficient buffer space (<code>list_size<codee> less
       than <code>nReport_Bytes<codee> member of <code>RTX_COUNTS<codee>).
       <paraend>

 @comm
       The primary purpose for this API is to allow the user to determine
       the number of RTX resources that are available.<s2> For this limited
       purpose, only the
       <linkto>../../rtxstruc.htm#RTX_COUNTS<linkmid>RTX_COUNTS<linktail>
       data structure is required at the location referenced by
       the <code>counts<codee> parameter.<s2> The
       <code>details<codee> parameter can be set to NULL or
       <code>list_size<codee> parameter set to zero to indicate that no
       <linkto>../../rtxstruc.htm#RTX_DETAILS<linkmid>RTX_DETAILS<linktail>
       reporting is desired.<nl>
       <nl>
       When more detailed information about the various RTX objects in
       use is desired, an array of
       <linkto>../../rtxstruc.htm#RTX_DETAILS<linkmid>RTX_DETAILS<linktail> unions
       can be provided by the caller at location specified by the
       <code>details<codee> pointer.<s2> The number of bytes space
       available in this buffer is specified in the <code>list_size<codee>
       argument.<s2> This API will then report details for as many of
       the selected RTX objects as will fit into this buffer space.<nl>
       <nl>
       The report <code>filter<codee> parameter allows you to focus the detailed
       reporting on particular types of RTX objects.<s2>  This can
       simplify your memory management problem by reducing the size of
       the <code>RTX_DETAILS<codee> array at <code>details<codee> required
       to report all the objects of the type you are interested in.<s2> Bits
       set to one in this bit field inhibit the reporting of the
       RTX object type associated with that bit.<s2>  The following
       filter masks are defined in RTXAPI.H header file for this purpose:
       <ul><nl>
       <hangpara 20:30>
          RTX_FILT_SEM  -  Enables semaphore detail reporting<paraend>
       <hangpara 20:30>
          RTX_FILT_TIMER  -  Enables timer detail reporting<paraend>
       <hangpara 20:30>
          RTX_FILT_EVENT_GROUP  -  Enables Event Group detail reporting<paraend>
       <hangpara 20:30>
          RTX_FILT_MSGXCHG  -  Enables Message Exchange detail reporting<paraend>
       <hangpara 20:30>
          RTX_FILT_TASK  -  Enables task detail reporting<paraend>
          <paraend>
       <ule>
       Each of these mask has all bits set except for one.<s2> These masks
       can be combined with the bit wise AND operation to
       report more than one object type.<s2> For example:<nl>
       <nl>
       <tab><code>RTX_FILT_SEM & RTX_FILT_EVENT_GROUP<codee><nl>
       <nl>
       for the <code>filter<codee> argument would report both semaphore
       and Event Group objects.<nl>
       <nl>
       One possible strategy for allocating the <code>details<codee> buffer
       memory would be to first call this API with <code>list_size<codee> set
       to zero only to discover how large a buffer will be required to collect
       the desired detailed information.<s2>  The number of buffer bytes required
       is reported by the API in the <code>nReport_Bytes<codee> member of the
       <linkto>../../rtxstruc.htm#RTX_COUNTS<linkmid>RTX_COUNTS<linktail> data
       structure.<s2> This reported count is influenced by what ever
       reporting <code>filter<codee> you had specified.<nl>
       <nl>
       Inside this API, the RTX data is collected with the
       <linkto>rtx20.htm<linkmid>task switching<linktail>
       locked.<s2> Interrupts are enabled after inhibiting task switching.<s2>
       The interrupt mask is restored to the state on entry prior to
       re-enabling the task switching on return.<s2> Nevertheless, a task
       switch can occur at the moment task switching is re-enabled here,
       thereby defeating any interrupt mask set by the caller.<nl>

 @Also  rtx13A.htm | RTX_Wait_Queue |
        rtx0A.htm |  RTX_Get_Task_State | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x13<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V0.91 | V1.00
 @target_clib V2.02
*/
int RTX_Count_Resources (RTX_COUNTS  far *counts,
                         void        far *details,
                         unsigned int     list_size,
                         unsigned int     filter)
{
    asm {les  DI,counts} ;
    _BX = FP_SEG(details) ;
    _SI = FP_OFF(details) ;
    _CX = list_size ;
    _DX = filter ;
    _AH = RTX_COUNT_RESOURCES ;
    asm { int RTOSVECT  } ;

    return _AX ;

}   /* End RTX_Count_Resources() */
#endif

/*************************************************************************/
// Read out list of tasks awaiting an RTX object
/*************************************************************************/
#ifdef _rtx13A_
/*
 @doc DOC_rtx13A_
 ---------------------------------------------------------------
 Read out list of tasks awaiting an RTX object
 ---------------------------------------------------------------
 @clib  RTX_Wait_Queue | This diagnostic routine reads out the
    list of tasks waiting at a specified RTX semaphore, Event Group
    or Message Exchange. |
        <cfont>int RTX_Wait_Queue ( unsigned int handle,<nl>
        <tab><tab><tab><tab><tab> void<tab><s2>  far *details,<nl>
        <tab><tab><tab><tab><tab> unsigned int<tab> list_size,<nl>
        <tab><tab><tab><tab><tab> unsigned int<tab>filter );<efont> |
 @parm  int * | handle  | Input parameter:<s2> RTX object identifier
         for a semaphore, Event Group, or Message Exchange whose
         wait list is desired.
 @parm  int * | details  | Optional Output parameter:<s2>   Pointer to
            a buffer which will receive objects which can be referenced
            with the
            <linkto>../../rtxstruc.htm#RTX_DETAILS<linkmid>RTX_DETAILS<linktail>
             union of structure pointers.<s2> The first object in this
             list will apply to the RTX object specified by <code>handle<codee>.
             All subsequent reported objects will be
            <linkto>../../rtxstruc.htm#RTX_DETAIL_TASK<linkmid>RTX_DETAIL_TASK<linktail>
            type, one for each task waiting in the queue listed from first to last.<s2>
             This parameter can be set to NULL in order to receive a return
             value indicating how large the buffer should be for a subsequent
             call.<nl>
 @parm  int | list_size  | Number of bytes in buffer at
          <code>details<codee>.<s2> If either this value
          is zero or <code>details<codee> is NULL, then no
          <code>RTX_DETAILS<codee> reporting is done and the return value
          indicates with a negative value how large a buffer will be
          required for a subsequent call.<nl>
 @parm  int | filter  | Must be one of the following masks to indicate
         to what type of RTX resource the <code>handle<codee> applies:<nl>
         <ul><nl>
         RTX_FILT_SEM  - For semaphore<nl>
         RTX_FILT_EVENT_GROUP  - For an Event Group<nl>
         RTX_FILT_MSGXCHG  - For a Message Exchange<nl>
         <ule>

 @rdesc        <hangpara 20:30>
        Less than zero:<s2> Either <code>details<codee> was NULL or more than
        <code>list_size<codee> will be required for reporting the
        requested data.<s2> In this case, the negative of this
        return value is the minimum size buffer required for the
        report.<paraend>
       <hangpara 20:30>
        Equal zero:<s2> Error, most likely the <code>handle<codee>
           did not apply to an RTX resource of the type indicated
           by <code>filter<codee>.
       <paraend>
       <hangpara 20:30>
       Greater than zero:<s2> Number of
       <linkto>../../rtxstruc.htm#RTX_DETAILS<linkmid>RTX_DETAILS<linktail>
       structures output to array at <code>details<codee>.<s2> The first
       structure applies to the RTX object referenced by <code>handle<codee>.
       <s2> The subsequent entries are all
        <linkto>../../rtxstruc.htm#RTX_DETAIL_TASK<linkmid>RTX_DETAIL_TASK<linktail>
        type.<s2> The number of task waiting at the queue is equal to
        this return value minus one.
       <paraend>
 @comm
       This diagnostic API is used to determine which tasks are waiting
       in a queue at an RTX semaphore, Event Group or Message Exchange.<s2>
       The <code>filter<codee> argument must indicate to which type RTX resource
       the <code>handle<codee> argument applies.<nl>
       <nl>
       Inside this API, the RTX data is collected with the
       <linkto>rtx20.htm<linkmid>task switching<linktail>
       locked.<s2> Interrupts are enabled after inhibiting task switching.<s2>
       The interrupt mask is restored to the state on entry prior to
       re-enabling the task switching on return.<s2> Nevertheless, a task
       switch can occur at the moment task switching is re-enabled here,
       thereby defeating any interrupt mask set by the caller.<nl>
 @Also  rtx13.htm |  RTX_Count_Resources |
        rtx0A.htm |  RTX_Get_Task_State | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x13<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V0.91 | V1.00
 @target_clib V2.02
*/
int RTX_Wait_Queue (unsigned int handle,
                    void        far *details,
                    unsigned int     list_size,
                    unsigned int     filter)
{
    _ES = 0 ;
    _DI = handle ;
    _BX = FP_SEG(details) ;
    _SI = FP_OFF(details) ;
    _CX = list_size ;
    _DX = filter ;
    _AH = RTX_COUNT_RESOURCES ;
    asm { int RTOSVECT  } ;

    return _AX ;

}   /* End RTX_Wait_Queue() */
#endif


/*************************************************************************/
// Get task  list
/*************************************************************************/
#ifdef _rtx0B_
/*
 @doc DOC_rtx0B_
 ---------------------------------------------------------------
 RTX Get task  list
 ---------------------------------------------------------------
 @clib  RTX_Get_Task_List | Get list of current tasks in system. |
        <cfont>int RTX_Get_Task_List ( TaskList far *tasklist, int length );<efont> |
 @parm  int * | tasklist  | Output parameter:<s2>Pointer to an array of
        <code>TaskList<codee>
        <linkto>../../rtxstruc.htm#TaskList<linkmid>type<linktail>
        structures allocated by user to be filled by this function
 @parm  int  | length  | Length of the list, number of data structures
        in array.
 @rdesc Number of tasks output to <code>tasklist<codee> array
 @comm  The caller must allocate sufficient buffer space at
        <code>tasklist<codee> to
        allow all tasks to be reported, including those
        <linkto>../../rtxtask.htm<linkmid>created<linktail> by the
        system in order to receive a complete report.
 @Also  rtx0A.htm | RTX_Get_Task_State |
        rtx13.htm | RTX_Count_Resources | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x0B<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Get_Task_List (TaskList far *tasklist, int length)
{
    _CX = length;
    asm { LES DI,tasklist }
    _AH = RTX_GET_TASK_LIST;
    asm { int RTOSVECT  } ;
    return _BX ;                // return list length
}
#endif

/*************************************************************************/
// Start task monitoring
/*************************************************************************/
#ifdef _rtx0C_
/*
 @doc DOC_rtx0C_
 ---------------------------------------------------------------
 RTX Start task monitoring
 ---------------------------------------------------------------
 @clib  RTX_Start_Task_Monitor | Install task monitor. |
        <cfont>void RTX_Start_Task_Monitor ( void );<efont> |
 @parm  int * |   | -- none --
 @rdesc -- none --
 @comm  The 1000 Hz system clock interrupt is intercepted to perform
        task monitoring.
 @Also  rtx0D.htm |  RTX_Stop_Task_Monitor | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x0C<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void RTX_Start_Task_Monitor(void)
{
    _AH = RTX_START_TASK_MONITOR;
    asm { int RTOSVECT  } ;
}
#endif


/*************************************************************************/
// Stop task monitoring
/*************************************************************************/
#ifdef _rtx0D_
/*
 @doc DOC_rtx0D_
 ---------------------------------------------------------------
 RTX Stop task monitoring
 ---------------------------------------------------------------
 @clib  RTX_Stop_Task_Monitor | Disable task monitoring. |
        <cfont>void RTX_Stop_Task_Monitor ( void );<efont> |
 @parm  int * |   | -- none --
 @rdesc -- none --
 @comm  This function restores the system's original
        1000 Hz interrupt handler, removing the task timing
        function installed by
        <linkto>rtx0C.htm<linkmid>RTX_Start_Task_Monitor<linktail>.
 @Also  rtx0C.htm |  RTX_Start_Task_Monitor | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x0D<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void RTX_Stop_Task_Monitor(void)
{
    _AH = RTX_STOP_TASK_MONITOR;
    asm { int RTOSVECT  } ;
}
#endif


/*************************************************************************/
// Suspend a  task
/*************************************************************************/
#ifdef _rtx0E_
/*
 @doc DOC_rtx0E_
 ---------------------------------------------------------------
 RTX Suspend task
 ---------------------------------------------------------------
 @clib  RTX_Suspend_Task | Suspend the execution of a task until
        <linkto>rtx0F.htm<linkmid>RTX_Resume_Task<linktail>
        is called to resume the task. |
        <cfont>int RTX_Suspend_Task ( int taskID );<efont> |
 @parm  int  | taskID  | Task ID of task to be suspended.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code,
        invalid task ID.
 @Also  rtx0F.htm | RTX_Resume_Task |
        rtx07.htm | RTX_End_Execution | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x0E<linkmid>documentation<linktail>
        for more details.
*/
int RTX_Suspend_Task(int taskID)
{
    _BX = taskID ;
    _AH = RTX_SUSPEND_TASK ;
    asm { int RTOSVECT  } ;
    return _AX ;                // Return error code
}
#endif

/*************************************************************************/
// Resume a task
/*************************************************************************/
#ifdef _rtx0F_
/*
 @doc DOC_rtx0F_
 ---------------------------------------------------------------
 RTX Resume task
 ---------------------------------------------------------------
 @clib  RTX_Resume_Task | Enable the execution of a suspended task |
        <cfont>int RTX_Resume_Task ( int taskID );<efont> |
 @parm  int  | taskID  | Task ID of task to be resumed.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code,
        invalid task ID.
 @Also  rtx0E.htm |  RTX_Suspend_Task | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x0F<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Resume_Task(int taskID)
{
    _BX = taskID ;
    _AH = RTX_RESUME_TASK ;
    asm { int RTOSVECT  } ;
    return _AX ;                // Return error code
}
#endif


/*************************************************************************/
// Restart a  task, killed with call 0x02
/*************************************************************************/
#ifdef _rtx10_
/*
 @doc DOC_rtx10_
 ---------------------------------------------------------------
 RTX Restart task
 ---------------------------------------------------------------
 @clib  RTX_Restart_Task | Start a newly created task or restart a killed task. |
        <cfont>int RTX_Restart_Task ( int taskID );<efont> |
 @parm  int | taskID  | Task handle returned from
        <linkto>rtx01.htm<linkmid>RTX_Create_Task<linktail> or
        <linkto>rtx11.htm<linkmid>RTX_Create_Task_Without_Run<linktail>.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code, invalid task ID.
 @comm   This function increments a task trigger counter within the specified
        task's control block.<s2>  This trigger counter is then decremented each
        time the system starts this task.<s2> When a task is at its starting
        gate and this trigger counter is zero (the initial condition after a
        task has been created), the task awaits execution with the "trigger
        wait" status bit in the
        <linkto>../../rtxstruc.htm#Task_StateData<linkmid>taskState<linktail>
        bit field set.<nl>
        <nl>
        The <code>RTX_Trigger_Task<codee> alias macro provides an alternative
        name for this function.  (This alternate name will be used instead in
        the C-libraries on future Beck @CHIP-RTOS systems.)
 @Also  rtx11.htm | RTX_Create_Task_Without_Run |
        rtx02.htm | RTX_Kill_Task  | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x10<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Restart_Task(int taskID)
{
    _BX = taskID ;
    _AH = RTX_RESTART_TASK ;
    asm { int RTOSVECT  } ;
    return _AX ;                // Return error code
}
#endif


/*************************************************************************/
// Disable Task Sheduling
/*************************************************************************/
#ifdef _rtx20_
/*
 @doc DOC_rtx20_
 ---------------------------------------------------------------
 RTX Disable Task Sheduling
 ---------------------------------------------------------------
 @clib  RTX_Disable_Task_Scheduling | Disable task switching. |
        <cfont>void RTX_Disable_Task_Scheduling ( void );<efont> |
 @parm  int * |   | -- none --
 @rdesc -- none --
 @comm   This function locks the processor
        to the current task, preventing further task switching until either
        <linkto>rtx21.htm<linkmid>RTX_Enable_Task_Scheduling<linktail>
        or a sleep API function is called.<s2> Entering any sleep
        API defeats the task lock.<s2> In this case the task lock condition
        is released until the task resumes execution.<s2>  During the sleep,
        the system automatically releases the lock condition to allow other
        tasks to execute.<nl>
        <nl>
        During the task lock condition, interrupts still execute provided
        that the user leaves interrupts enabled.<s2> Installed
        <linkto>rtx30.htm<linkmid>Timer<linktail>
        procedures will not be executed.<nl>
        <nl>
        This call must be followed by a call to
        <linkto>rtx21.htm<linkmid>RTX_Enable_Task_Scheduling<linktail>
        as soon as possible to re-enable the task switching.<s2>
        If this period exceeds a hundred milliseconds then the watchdog
        should be triggered (using the Hardware API
        <linkto>../HW/hal91.htm<linkmid>hal_refresh_watchdog<linktail> function)
        by the user until the task switching is re-enabled.<nl>
        <nl>
        Note that this is implemented as a spin lock, such that if for some
        reason the task calls here N times then N calls to
        <linkto>rtx21.htm<linkmid>RTX_Enable_Task_Scheduling<linktail>
        are required to unwind the spin lock and re-enable the task switching.
 @Also  rtx21.htm | RTX_Enable_Task_Scheduling |
        rtx08.htm | RTX_Change_TaskPrio | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x20<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00
*/
void RTX_Disable_Task_Scheduling(void)
{
    _AH = RTX_DISABLE_TASK_SCHEDULING ;
    asm { int RTOSVECT } ;
}
#endif


/*************************************************************************/
// Enable Task Sheduling
/*************************************************************************/
#ifdef _rtx21_
/*
 @doc DOC_rtx21_
 ---------------------------------------------------------------
 RTX Enable Task Sheduling
 ---------------------------------------------------------------
 @clib  RTX_Enable_Task_Scheduling | Re-enable task switching. |
        <cfont>void RTX_Enable_Task_Scheduling ( void );<efont> |
 @parm  int * |   | -- none --
 @rdesc -- none --
 @comm  This function must be called following use of the
        <linkto>rtx20.htm<linkmid>RTX_Disable_Task_Scheduling<linktail>
        function.
 @Also  rtx20.htm |  RTX_Disable_Task_Scheduling | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x21<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | V1.00
*/
void RTX_Enable_Task_Scheduling(void)
{
    _AH = RTX_ENABLE_TASK_SCHEDULING ;
    asm { int RTOSVECT } ;
}
#endif


/*************************************************************************/
/*************************************************************************/
//Semaphore functions
/*************************************************************************/
/*************************************************************************/

/*************************************************************************/
// Create a semaphore
/*************************************************************************/
#ifdef _rtx14_
/*
 @doc DOC_rtx14_
 ---------------------------------------------------------------
 RTX Create semaphore
 ---------------------------------------------------------------
 @clib  RTX_Create_Sem | Create either a counting or resource
        <linkto>../../rtxover.htm#Semaphore<linkmid>semaphore<linktail>. |
        <cfont>int RTX_Create_Sem ( int far *semID, const char  far *name,<nl>
        <tab><tab><tab><tab><tab> int initvalue );<efont> |
 @parm  int * | semID  | Output Parameter:<s2>pointer to where semaphore
        ID will be written.
 @parm  int * | name  | Input Parameter:<s2>pointer to a four character name
        for the new semaphore.<s2> This string need not be zero terminated,
        but must contain four bytes.
 @parm  int | initvalue  | New semaphore's initial value.<s2>  Set this to -1
        to create a resource semaphore.<s2>  For counting semaphore's set
        this to some non-negative number representing the number of resources
        initially available on this new semaphore.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The semaphore name is only relevant if the
        <linkto>rtx1C.htm<linkmid>RTX_Find_Sem<linktail> service will be used.<s2>
        Otherwise, setting this field to all zeros can avoid namespace conflicts with
        other semaphores which do use the name lookup service.
 @Also  rtx15.htm | RTX_Delete_Sem |
        rtx1C.htm | RTX_Find_Sem   | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x14<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Create_Sem (int far * semID, const char  far * name, int initvalue)
{
    _CX = initvalue ;
    _BX = FP_SEG (semID) ;
    _SI = FP_OFF (semID) ;
    asm { LES  DI,name } ;
    _AH = RTX_CREATE_SEM ;
    asm { int RTOSVECT } ;
    return _AX ;                // Return error code
}
#endif

/*************************************************************************/
// Delete a  semaphore
/*************************************************************************/
#ifdef _rtx15_
/*
 @doc DOC_rtx15_
 ---------------------------------------------------------------
 RTX Delete semaphore
 ---------------------------------------------------------------
 @clib  RTX_Delete_Sem | Delete a semaphore, removing it from system. |
        <cfont>int RTX_Delete_Sem ( int semID );<efont> |
 @parm  int | semID  | The semaphore ID of a resource or counting semaphore
        acquired by a call to <linkto>rtx14.htm<linkmid>RTX_Create_Sem<linktail>.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  You must be absolutely certain that no other task, ISP or Timer Procedure
        is in any way  using or about to use the semaphore.  Failure to observe
        this restriction may lead to unexpected and unpredictable faults.
 @Also  rtx14.htm |  RTX_Create_Sem | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x15<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Delete_Sem (int semID)
{
    _BX = semID ;
    _AH = RTX_DELETE_SEM ;
    asm { int RTOSVECT } ;
    return _AX ;                // Return error code
}
#endif


/*************************************************************************/
// Free a  resource semaphore
/*************************************************************************/
#ifdef _rtx16_
/*
 @doc DOC_rtx16_
 ---------------------------------------------------------------
 RTX Free resource semaphore
 ---------------------------------------------------------------
 @clib  RTX_Free_Sem | Unconditionally free a resource semaphore.<s2>  The
        resource's usage count is set to zero and the resource is  freed. |
        <cfont>int RTX_Free_Sem ( int semID );<efont> |
 @parm  int | semID  | The semaphore ID of a resource semaphore
        acquired by a call to <linkto>rtx14.htm<linkmid>RTX_Create_Sem<linktail>.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The resource will immediately be given to the task (if any) which is
        waiting at the head of this semaphore's wait queue.<s2> Task rescheduling
        occurs immediately if necessary.<nl>
        <nl>
        This function is similar to
        <linkto>rtx18.htm<linkmid>RTX_Release_Sem<linktail>.<s2>  The
        RTX_Release_Sem function unwinds the usage count from nested calls to
        <linkto>rtx19.htm<linkmid>RTX_Reserve_Sem<linktail>  one count per call.<s2>
        This RTX_Free_Sem function clears the count, immediately erasing the affect
        of several nested calls to RTX_Reserve_Sem.
 @Also  rtx18.htm |  RTX_Release_Sem |
        rtx19.htm |  RTX_Reserve_Sem | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x16<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Free_Sem(int semID)
{
    _BX = semID ;
    _AH = RTX_FREE_RES ;
    asm { int RTOSVECT } ;
    return _AX ;                // Return error code
}
#endif

/*************************************************************************/
// Get a counting semaphore
/*************************************************************************/
#ifdef _rtx17_
/*
 @doc DOC_rtx17_
 ---------------------------------------------------------------
 RTX Get a counting semaphore
 ---------------------------------------------------------------
 @clib  RTX_Get_Sem | Attempt to access a semaphore, without waiting. |
        <cfont>int RTX_Get_Sem ( int semID );<efont> |
 @parm  int | semID  | The semaphore ID of a counting or resource 
        type semaphore
        acquired by a call to <linkto>rtx14.htm<linkmid>RTX_Create_Sem<linktail>.
 @rdesc 0 on success (semaphore granted) else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  This call returns with an error if the semaphore is not available.<s2>
        For counting semaphores, available means that the semaphore's count
        was non-zero.<s2> For resource semaphores, available means that
        the semaphore "in use" count was either zero or the calling task
        is the current owner.<nl>
        <nl>
        This API will decrement an available counting semaphore's
        count value.  For resource semaphores, it will increment the
        "in use" count if the semaphore was available.<nl>
        <nl>
         <bold>Note:><bolde> <s2> On RTOS versions prior to
         SC1x version 1.27 and SC1x3/SC2x version 1.41, this function was 
         restricted to counting semaphores.<s2> This restriction has been
         removed.<nl>
 @Also  rtx1A.htm |  RTX_Signal_Sem |
        rtx1B.htm |  RTX_Wait_Sem   |
        rtx18.htm |  RTX_Release_Sem
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x17<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.27 | V1.27 | V1.27 | V1.41 | V1.41
*/
int RTX_Get_Sem(int semID)
{
    _BX = semID ;
    _AH = RTX_GET_SEM ;
    asm { int RTOSVECT } ;
    return _AX ;                // Return error code
}
#endif


/*************************************************************************/
// Release a resource semaphore
/*************************************************************************/
#ifdef _rtx18_
/*
 @doc DOC_rtx18_
 ---------------------------------------------------------------
 RTX Release a resource semaphore
 ---------------------------------------------------------------
 @clib  RTX_Release_Sem | Release a resource semaphore. |
        <cfont>int RTX_Release_Sem ( int semID );<efont> |
 @parm  int | semID  | The semaphore ID of a resource semaphore
        acquired by a call to <linkto>rtx14.htm<linkmid>RTX_Create_Sem<linktail>.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The resource's usage count is decremented by one for each  call to this
        function.<s2>  The resource is not freed until the usage count becomes zero.<nl>
        <nl>
        Once freed, the  resource will immediately be given to the task (if any)
        which is waiting at the head of this semaphore's wait queue.<s2>  Task
        rescheduling occurs immediately if necessary.
 @Also  rtx16.htm |  RTX_Free_Sem |
        rtx19.htm |  RTX_Reserve_Sem  | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x18<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Release_Sem(int semID)
{
    _BX = semID ;
    _AH = RTX_RELEASE_SEM ;
    asm { int RTOSVECT } ;
    return _AX ;                // Return error code
}

#endif

/*************************************************************************/
// Reserve a resource semaphore (optional timeout)
/*************************************************************************/
#ifdef _rtx19_
/*
 @doc DOC_rtx19_
 ---------------------------------------------------------------
 RTX Reserve a resource semaphore
 ---------------------------------------------------------------
 @clib  RTX_Reserve_Sem | Reserve a resource semaphore.<s2> If current task
        is already the owner of this semaphore then the semaphore's usage
        count is incremented by one and the function returns immediately
        with  success. |
        <cfont>int RTX_Reserve_Sem ( int semID, long far *time_ms );<efont> |
 @parm  int | semID  | The semaphore ID of a resource semaphore
        acquired by a call to <linkto>rtx14.htm<linkmid>RTX_Create_Sem<linktail>.
 @parm  int | time_ms  | Pointer for ms to wait: Zero -<gt> Wait forever for semaphore<nl>
        Positive value -<gt> Maximum number of milliseconds to wait for resource<nl>
        Negative value -<gt> Polling mode, return immediately.<s2> If semaphore
               was not available the return value will be the -27 time-out
               indication.<nl>
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The calling task will be suspended to wait for the resource if the
        semaphore is owned by some other task.<nl>
        <nl>
        When the resource is finally available for use by the caller, the
        procedure will return with 0.<nl>
        <nl>
        Upon first acquiring ownership of the resource, the resouce's usage count
        is set to one.<nl>
        <nl>
        It is permissible for a task to call <code>RTX_Reserve_Sem<codee> even
        if the calling task already owns the resource.<s2>  The resource  usage count
        is incremented by one for each subsequent call by the resource owner.<nl>
        <nl>
        This usage count is down counted by 
        <linkto>rtx18.htm<linkmid>RTX_Release_Sem<linktail> and cleared by
        <linkto>rtx16.htm<linkmid>RTX_Free_Sem<linktail>.<s2> When the count
        reaches zero the task no longer owns the semaphore.<nl>
        <nl>
        The wait priority used here is 20.<s2> (See the
        <linkto>rtx1E.htm<linkmid>RTX_Wait_Sem_Priority<linktail> 
        alternative API for explanation of wait priority.)
        <nl>
 @Also  rtx18.htm | RTX_Release_Sem |
        rtx16.htm | RTX_Free_Sem    |
        rtx1E.htm | RTX_Wait_Sem_Priority

 @Also  rtx17.htm |  RTX_Get_Sem |
         |     |
         |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x19<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Reserve_Sem(int semID, long   far  * time_ms)
{
    _BX = semID ;
    _ES = FP_SEG(time_ms) ;
    _DI = FP_OFF(time_ms);
    _AH = RTX_RESERVE_RES ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
// Signal a  counting semaphore
/*************************************************************************/
#ifdef _rtx1A_
/*
 @doc DOC_rtx1A_
 ---------------------------------------------------------------
 RTX Signal a counting semaphore
 ---------------------------------------------------------------
 @clib  RTX_Signal_Sem | Signal a counting semaphore. |
        <cfont>int RTX_Signal_Sem ( int semID );<efont> |
 @parm  int | semID  | The semaphore ID of a counting semaphore
        acquired by a call to <linkto>rtx14.htm<linkmid>RTX_Create_Sem<linktail>.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The resource will immediately be given to the task (if any) which is
        waiting at the head of this semaphore's wait queue.<s2> Task
        rescheduling occurs immediately if necessary.<nl>
        <nl>
        This method is used to release access to a counting semaphore
        after a task has acquired the semaphore through a
        <linkto>rtx17.htm<linkmid>RTX_Get_Sem<linktail> or
        <linkto>rtx1B.htm<linkmid>RTX_Wait_Sem<linktail> call.
 @Also  rtx17.htm |  RTX_Get_Sem  |
        rtx1B.htm |  RTX_Wait_Sem | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x1A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Signal_Sem(int semID)
{
    _BX = semID ;
    _AH = RTX_SIGNAL_SEM ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif




/*************************************************************************/
// Wait on a  counting semaphore (optional timeout)
/*************************************************************************/
#ifdef _rtx1B_
/*
 @doc DOC_rtx1B_
 ---------------------------------------------------------------
 RTX Wait on a  counting semaphore
 ---------------------------------------------------------------
 @clib  RTX_Wait_Sem | Wait on a  semaphore. |
        <cfont>int RTX_Wait_Sem ( int semID, long far *time_ms );<efont> |
 @parm  int | semID  | The semaphore ID of a semaphore
        acquired by a call to <linkto>rtx14.htm<linkmid>RTX_Create_Sem<linktail>.
 @parm  int | time_ms  | Pointer for ms to wait: Zero -<gt> Wait forever for semaphore<nl>
        Positive value -<gt> Maximum number of milliseconds to wait for resource<nl>
        Negative value -<gt> Polling mode, return immediately.<s2> If semaphore
               was not available the return value will be the -27 time-out
               indication.<nl>
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  This call waits for a defined time on a semaphore and returns with an
        error if the semaphore is not available within this time period.<nl>
        <nl>
        This  API may be used for either counting or resource type semaphores.<nl>
        <nl>
        The wait priority used here is fixed at 20.<s2> (See the
        <linkto>rtx1E.htm<linkmid>RTX_Wait_Sem_Priority<linktail> 
        alternative API for explanation of wait priority.)
        <nl>
 @Also  rtx17.htm |  RTX_Get_Sem |
        rtx1A.htm |  RTX_Signal_Sem |
        rtx1E.htm |  RTX_Wait_Sem_Priority
 @Also  rtx18.htm |  RTX_Release_Sem |
        rtx1A.htm |  RTX_Signal_Sem |
         |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x1B<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Wait_Sem(int semID, long  far  *time_ms)
{
    _BX = semID ;
    _ES = FP_SEG(time_ms) ;
    _DI = FP_OFF(time_ms) ;
    _AH = RTX_WAIT_SEM ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
// Find an semaphore, specified by 4 char name tag
/*************************************************************************/
#ifdef _rtx1C_
/*
 @doc DOC_rtx1C_
 ---------------------------------------------------------------
 RTX Find an semaphore
 ---------------------------------------------------------------
 @clib  RTX_Find_Sem | Find a semaphore by name. |
        <cfont>int RTX_Find_Sem ( int far *ID, const char far *name );<efont> |
 @parm  int | ID  | Output parameter: Pointer to semaphore ID
 @parm  int | name  | Input parameter: Pointer to the four character name
        of the semaphore to search for.
 @rdesc zero -<gt> Semaphore found<nl>
        non-zero -<gt>  Return <code>error<codee> code.
 @comm  The four character name string need not be zero terminated.<s2>However,
        it must contain four characters to be matched against the four character
        name provided when semaphore was created.
 @Also  rtx14.htm |  RTX_Create_Sem | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x1C<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Find_Sem(int far *ID, const char far *name)
{
    int the_id ;

    *ID = 0;
    asm { LES   DI, name } ;
    _AH = RTX_FIND_SEM ;
    asm { int RTOSVECT  } ;
    the_id = _AX ;
    if (_DX == 0)
    {
        *ID = the_id ;  // Semaphore found
        return 0;
    }
    return the_id ;  // Semaphore not found return error code
}

#endif

/*************************************************************************/
// Go to sleep for a defined time with RTI resolution
/*************************************************************************/
#ifdef _rtx1D_
/*
 @doc DOC_rtx1D_
 ---------------------------------------------------------------
 RTX Sleep Fine
 ---------------------------------------------------------------
 @clib  RTX_Sleep_Fine | Go to sleep for a specified number of
        Real-Time Interrupts
        (<linkto>../../rtirate.htm<linkmid>RTI<linktail>).  |
        <cfont>int RTX_Sleep_Fine ( unsigned int time_rti ); <efont> |
 @parm  int | time_rti | Sleep time in RTI ticks
 @rdesc 0 on success else <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The  <linkto>rtx06.htm<linkmid>RTX_Wakeup<linktail> function can wake
        up a sleeping task before its sleep timer has expired.<nl>
        <nl>
        If the task has an outstanding wake request pending when it calls here,
        the task will continue execution immediately without waiting.
 @Also  rtx05.htm |  RTX_Sleep_Request |
        rtx06.htm | RTX_Wakeup  |
        rtx00.htm | RTX_Sleep_Time
 @Also  rtx1DA.htm |  RTX_Sleep_Long |
        |   |
        |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x00<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    1.20  | 1.20  | 1.20  | V1.05 | V1.00
 @target_clib V2.04
*/
int RTX_Sleep_Fine(unsigned int time_rti)
{
    _DX = 0 ;                   // MSH of 32 bit delay time
    _BX = time_rti ;
    _AH   = RTX_SLEEP_FINE ;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif

/*************************************************************************/
// Go to sleep for a long time with RTI resolution
/*************************************************************************/
#ifdef _rtx1DA_
/*
 @doc DOC_rtx1DA_
 ---------------------------------------------------------------
 RTX Sleep long time with RTI resolution
 ---------------------------------------------------------------
 @clib  RTX_Sleep_Long | Go to sleep for a large number of
         Real-Time Interrupts.
        (<linkto>../../rtirate.htm<linkmid>RTI<linktail>).  |
        <cfont>int RTX_Sleep_Long ( long time_rti ); <efont> |
 @parm  int | time_rti | 31 bit sleep time in RTI ticks.<s2>
     This value is not valid if negative and the function will
     return immediately.
 @rdesc 0 on success else <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The  <linkto>rtx06.htm<linkmid>RTX_Wakeup<linktail> function can wake
        up a sleeping task before its sleep timer has expired.<nl>
        <nl>
        If the task has an outstanding wake request pending when it calls here,
        the task will continue execution immediately without waiting.<nl>
 @Also  rtx05.htm |  RTX_Sleep_Request |
        rtx06.htm | RTX_Wakeup  |
        rtx00.htm | RTX_Sleep_Time
 @Also  rtx1D.htm |  RTX_Sleep_Fine |
        |   |
        |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x1D<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    1.20  | 1.20  | 1.20  | V1.05 | V1.00
 @target_clib V2.04
*/
int RTX_Sleep_Long(long time_rti)
{
    _DX = FP_SEG((void *)time_rti) ;  // MSH of 32 bit delay time
    _BX = FP_OFF((void *)time_rti) ;  // LSH of 32 bit delay time
    _AH   = RTX_SLEEP_FINE ;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif

/*************************************************************************/
// Wait on a  counting semaphore (optional timeout)
/*************************************************************************/
#ifdef _rtx1E_
/*
 @doc DOC_rtx1E_
 ---------------------------------------------------------------
 RTX Wait on a semaphore with specified priority
 ---------------------------------------------------------------
 @clib  RTX_Wait_Sem_Priority | Wait with a specified
    priority on a semaphore. |
        <cfont>int RTX_Wait_Sem_Priority ( int semID,<nl>
        <tab><tab><tab><tab><tab><tab><tab>long time_ms,<nl>
        <tab><tab><tab><tab><tab><tab><tab>unsigned int wait_priority);
        <efont> |
 @parm  int | semID  | The semaphore ID of a semaphore
        acquired by a call to <linkto>rtx14.htm<linkmid>RTX_Create_Sem<linktail>.
 @parm  int | time_ms  | Maximum number of milliseconds to wait:<nl>
        <ul><nl>
            Zero -<gt> Wait forever for semaphore<nl>
        Positive value -<gt> Maximum number of milliseconds to wait for resource<nl>
        Negative value -<gt> Polling mode, return immediately.<s2> If semaphore
               was not available the return value will be the -27 time-out
               indication.<nl>
        <ule>
 @parm  int | wait_priority  | The priority at which the caller wishes to wait
          (0 = highest).<s2><s2> (Note that this priority has no connection
          to task priorities.)<s2> To wait in FIFO order, either have
          all callers use the same value here or use the alternative
          functions <linkto>rtx1B.htm<linkmid>RTX_Wait_Sem()<linktail> or
          <linkto>rtx19.htm<linkmid>RTX_Reserve_Sem()<linktail>.
          <nl>
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  This function may be used with either counting or resource type
        semaphores.<nl>
        <nl>
        This call waits for up to a specified time on a semaphore
        and returns with an error if the semaphore is still not
        available within this time limit.<s2>
        Otherwise the caller is granted the semaphore.<nl>
        <nl>
        When more than one task is waiting for the semaphore, the task
        which called with the lowest <cfont>wait_priority<efont>
        number (highest priority) will be granted the semaphore before
        other waiting tasks.<s2> Tasks with matching
        <cfont>wait_priority<efont> wait in FIFO order.<nl>
 @Also  rtx1B.htm |  RTX_Wait_Sem |
        rtx17.htm |  RTX_Get_Sem |
        rtx1A.htm |  RTX_Signal_Sem
 @Also  rtx19.htm |  RTX_Reserve_Sem |
        rtx18.htm | RTX_Release_Sem |
        rtx16.htm | RTX_Free_Sem
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x1E<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.22 | V1.22 | V1.22 | V1.11 | V1.00
 @target_clib V2.08
*/
int RTX_Wait_Sem_Priority (int          semID,
                           long         time_ms,
                           unsigned int wait_priority)
{
    // time_ms is no pointer, but we force this point of view for
    //  a moment here so that the compiler's FP_SEG/FP_OFF can
    //  be used to access the two halves of the long.
    _ES = FP_SEG((void far *)time_ms) ;
    _BX = FP_OFF((void far *)time_ms) ;
    _DX = wait_priority ;
    _CX = semID ;
    _AH = RTX_WAIT_SEM_PRIO ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif


/*************************************************************************/
/*************************************************************************/
//Time/Date functions
/*************************************************************************/
/*************************************************************************/

/*************************************************************************/
// Get system time and date
/*************************************************************************/
/*
 @doc DOC_rtxdyn00_
 ---------------------------------------------------------------
 Get system time and date
 ---------------------------------------------------------------
 @clib  RTX_Get_TimeDate_us | Get system time and date with
        high resolution. |
        <cfont>int RTX_Get_TimeDate_us ( TimeDateFineS far *td );<efont> |
 @parm  int | td  | Output parameter,  pointer to TimeDateFineS
        <linkto>../../rtxstruc.htm#TimeDateFineS<linkmid>type<linktail>
        allocated by user and filled by this function.
 @rdesc 0: Location at <code>td<codee> contains system date and time
 @comm   This function requires around 185 microseconds
        execution time.  The time mark read occurs within 18 microseconds
        of the time at which this API was called, assuming that no
        interrupts were serviced in the meantime.<nl>
        <nl>
        This API may be called from within any form of 
        Interrupt Service routine, although due to its rather long
        execution time this may not be a good idea.<nl>
        <nl>
        Inside this API the interrupts are masked for short periods 
        of time and then restored to the their masking state on entry.<nl>

 @Also  rtxdyn01.htm |  RTX_Set_TimeDate_us |
        rtx2A.htm |  RTX_Get_System_Ticks |
        rtx2B.htm |  RTX_Get_RTI_Ticks
 @Also  rtxtf2.htm |  RTX_GetFineTick |
        rtxtf3.htm |  RTX_GetTick_us |
        rtx2AA.htm | RTX_GetTickCount
 @Also  rtx28.htm |  RTX_Get_TimeDate |
         |   |
         | 
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt
        to install a dynamic link into the RTOS.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x27<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
*/


/*
 @doc DOC_rtxdyn01_
 ---------------------------------------------------------------
 Set system time and date
 ---------------------------------------------------------------
 @clib  RTX_Set_TimeDate_us | Set system time and date with
        high resolution. |
        <cfont>int RTX_Set_TimeDate_us ( const TimeDateFineS far *td );<efont> |
 @parm  int | td  | Input parameter,  pointer to TimeDateFineS
        <linkto>../../rtxstruc.htm#TimeDateFineS<linkmid>type<linktail>
        containing time/date information set by user.
 @rdesc 0:
 @comm  The Day Of Week field (<code>.dow<codee> ) in TimeDateFineS
        need not be set by caller.<s2> This API function computes this
        field based on the other member data.<nl>
        <nl>
        The microsecond resolution exceeds the accuracy with which
        this API can actually set the time and date due to the speed
        of the software.  This function requires around 280 microseconds
        execution time.  The time mark to which the specified time and
        date are assigned is read within 20 microseconds of the time at
        which this API was called, assuming that no interrupts were
        serviced in the meantime.<nl>
        <nl>
        This API may be called from within any form of 
        Interrupt Service routine, although due to its long
        execution time this may not be appropriate for your
        particular application.<nl>
        <nl>
        Inside this API the interrupts are masked for short periods 
        of time and then restored to the their masking state on entry.<nl>

 @Also  rtxdyn00.htm |  RTX_Get_TimeDate_us |
        rtx2A.htm |  RTX_Get_System_Ticks |
        rtx2B.htm |  RTX_Get_RTI_Ticks
 @Also  rtxtf2.htm |  RTX_GetFineTick |
        rtxtf3.htm |  RTX_GetTick_us |
        rtx2AA.htm | RTX_GetTickCount
 @Also  rtx29.htm |  RTX_Set_TimeDate |
         |   |
         | 
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt
        to install a dynamic link into the RTOS.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x27<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
*/


/*************************************************************************/
// Get system time and date
/*************************************************************************/
#ifdef _rtx28_
/*
 @doc DOC_rtx28_
 ---------------------------------------------------------------
 Get system time and date
 ---------------------------------------------------------------
 @clib  RTX_Get_TimeDate | Get system time and date. |
        <cfont>int RTX_Get_TimeDate ( TimeDate_Structure far *td );<efont> |
 @parm  int | td  | Output parameter,  pointer to TimeDate_Structure
        <linkto>../../rtxstruc.htm#TimeDate_Structure<linkmid>type<linktail>
        allocated by user and filled by this function.
 @rdesc 0: Location at <code>td<codee> contains system date and time
 @Also  rtx29.htm |  RTX_Set_TimeDate |
        rtx2A.htm |  RTX_Get_System_Ticks |
        rtx2B.htm |  RTX_Get_RTI_Ticks
 @Also  rtxtf2.htm |  RTX_GetFineTick |
        rtxtf3.htm |  RTX_GetTick_us |
        rtx2AA.htm | RTX_GetTickCount
 @Also  rtxdyn00.htm |  RTX_Get_TimeDate_us |
         |   |
         |  
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x28<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Get_TimeDate(TimeDate_Structure  far  * td)
{
    _BX = FP_SEG (td) ;
    _SI = FP_OFF (td) ;
    _AH = RTX_GET_TIMEDATE ;
    asm { int RTOSVECT } ;
    return _DX;
}
#endif


/*************************************************************************/
// Set system time and date
/*************************************************************************/
#ifdef _rtx29_
/*
 @doc DOC_rtx29_
 ---------------------------------------------------------------
 Set system time and date
 ---------------------------------------------------------------
 @clib  RTX_Set_TimeDate | Set system time and date. |
        <cfont>int RTX_Set_TimeDate ( const TimeDate_Structure far *td );<efont> |
 @parm  int | td  | Input parameter,  pointer to TimeDate_Structure
        <linkto>../../rtxstruc.htm#TimeDate_Structure<linkmid>type<linktail>
        containing new time/date.
 @rdesc 0: Success
 @comm  The Day Of Week field (<code>.dow<codee> ) in TimeDate_Structure
        need not be set by caller.<s2> This API function computes this
        field based on the other member data.<nl>
        <nl>
        <bold>Note:<bolde><s2>  This function performs no validity check on
        date/time data supplied by user.
 @Also  rtx28.htm |  RTX_Get_TimeDate | 
        rtxdyn01.htm | RTX_Set_TimeDate_us |
        |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x29<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Set_TimeDate(const TimeDate_Structure  far  * td)
{
    _BX = FP_SEG (td) ;
    _SI = FP_OFF (td) ;
    _AH = RTX_SET_TIMEDATE ;
    asm { int RTOSVECT } ;
    return _DX;
}
#endif

/*************************************************************************/
// Get tick count of system clock
/*************************************************************************/
#ifdef _rtx2A_
/*
 @doc DOC_rtx2A_
 ---------------------------------------------------------------
 Get tick count of system clock
 ---------------------------------------------------------------
 @clib  RTX_Get_System_Ticks | Get tick count of system clock, in
        milliseconds. |
        <cfont>void RTX_Get_System_Ticks ( unsigned long far *ticks );<efont> |
 @parm  int | ticks | Output parameter: System time in milliseconds.
 @rdesc -- none --
 @comm  This 32 bit up count rolls over to zero each 2**32 milliseconds,
        which is approximately each 1193 hours of continuous operation
        (= 41.71 days).<nl>
        <nl>
        The alternate C-library API
        <linkto>rtx2AA.htm<linkmid>RTX_GetTickCount<linktail> may provide
        a more comfortable access to the same value.<nl>
        <nl>
        For real-time code, see discussion within the
        <linkto>rtx2B.htm<linkmid>RTX_Get_RTI_Ticks<linktail> documentation
        concerning use of the
        <linkto>rtxtf1.htm#pRti_Tick<linkmid>_pRti_Tick<linktail>
        direct access pointer with in-line code.
 @commtarget SC1x3/SC2x | If the system's real-time interrupt has been
        <linkto>../../config.htm#TIMER_RTI<linkmid>configured<linktail>
        for <linkto>../../rtirate.htm<linkmid>rates<linktail> above 1000 Hz,
        the count here will differ from that
        returned by the <linkto>rtx2B.htm<linkmid>RTX_Get_RTI_Ticks<linktail>
        API.
 @Also  rtx28.htm |  RTX_Get_TimeDate |
        rtx2B.htm |  RTX_Get_RTI_Ticks |
        rtx2AA.htm | RTX_GetTickCount
 @Also  rtxtf2.htm |  RTX_GetFineTick |
        rtxtf3.htm |  RTX_GetTick_us |
         |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x2A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void RTX_Get_System_Ticks(unsigned long far * ticks)
{
    _BX = FP_SEG(ticks) ;
    _SI = FP_OFF(ticks) ;
    _AH = RTX_GET_TICKS ;
    asm { int RTOSVECT } ;
}
#endif

/*************************************************************************/
// Return tick count of system clock
/*************************************************************************/
#ifdef _rtx2AA_
/*
 @doc DOC_rtx2AA_
 ---------------------------------------------------------------
 Return tick count of system clock
 ---------------------------------------------------------------
 @clib  RTX_GetTickCount | Get tick count of system clock, in
        milliseconds. |
        <cfont>unsigned long RTX_GetTickCount (void);<efont> |
 @rdesc System time in milliseconds
 @comm  This 32 bit up count rolls over to zero each each 2**32 real-time
        interrupts, which is approximately each 1193 hours of continuous
        operation (= 41.71 days).<nl>
        <nl>
        For real-time code, see discussion within the
        <linkto>rtx2B.htm<linkmid>RTX_Get_RTI_Ticks<linktail> documentation
        concerning use of the
        <linkto>rtxtf1.htm#pRti_Tick<linkmid>_pRti_Tick<linktail>
        direct access pointer with in-line code.
 @commtarget SC1x3/SC2x | If the system's real-time interrupt has been
        <linkto>../../config.htm#TIMER_RTI<linkmid>configured<linktail>
        for <linkto>../../rtirate.htm<linkmid>rates<linktail> above
        1000 Hz, the count here will differ from that
        returned by the <linkto>rtx2B.htm<linkmid>RTX_Get_RTI_Ticks<linktail>
        API.
 @Also  rtx28.htm |  RTX_Get_TimeDate |
        rtx2B.htm |  RTX_Get_RTI_Ticks |
        rtx2A.htm |  RTX_Get_System_Ticks
 @Also  rtxtf2.htm |  RTX_GetFineTick |
        rtxtf3.htm |  RTX_GetTick_us |
         |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x2A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
 @target_clib V2.04
*/
// Version note: New in library (7.3.2006), but we us an old RTOS API.

unsigned long RTX_GetTickCount (void)
{
    unsigned long ticks ;
    _BX = FP_SEG(&ticks) ;
    _SI = FP_OFF(&ticks) ;
    _AH = RTX_GET_TICKS ;
    asm { int RTOSVECT } ;
    return ticks ;
}
#endif


/*************************************************************************/
// Get RTI tick count
/*************************************************************************/
#ifdef _rtx2B_
/*
 @doc DOC_rtx2B_
 ---------------------------------------------------------------
 Get RTI tick count
 ---------------------------------------------------------------
 @clib  RTX_Get_RTI_Ticks | Get system's Real-Time Interrupt (RTI) count. |
        <cfont>unsigned long RTX_Get_RTI_Ticks (void);<efont> |
 @rdesc Real-Time interrupt count
 @comm  This 32 bit up count rolls over to zero each 2**32
        real-time interrupts,
        which is approximately each 1193 hours of continuous operation
        (= 41.71 days) when operating at 1 kHz
        <linkto>../../rtirate.htm<linkmid>RTI<linktail> rate.<nl>
        <nl>
        A faster way to access the system's RTI up counter is to
        read the long word referenced by the
        <linkto>rtxtf1.htm#pRti_Tick<linkmid>_pRti_Tick<linktail>.<s2>
        This alternate approach using inline code should be considered,
        especially when system time is required from within
        time-critical code such as Interrupt Service Routines.<s2>
        Keep in mind that you must momentarily mask interrupts
        around the 32 bit read from this location in order to assure
        consistent data.<s2> Also do not forget to call
        <linkto>rtxtf1.htm<linkmid>RTX_FineTickInit<linktail>
        once at the start of your program so that this pointer
        will be initialized.
 @commtarget SC1x |  For SC1x program's, this function is mapped to
    the <linkto>rtx2AA.htm<linkmid>RTX_GetTickCount<linktail> API,
    which is equivalent for the fixed 1 kHz RTI rate.<s2> This allows
    common source code to be used for the two system types.
 @Also  rtx28.htm |  RTX_Get_TimeDate |
        rtx2A.htm |  RTX_Get_System_Ticks |
        rtx2BA.htm | RTX_Get_RTI_Rate
 @Also  rtx2AA.htm |  RTX_GetTickCount |
        rtx2A.htm |  RTX_Get_System_Ticks |
        rtxtf1.htm#pRti_Tick |  _pRti_Tick
 @Also rtxtf2.htm |  RTX_GetFineTick |
        rtxtf3.htm | RTX_GetTick_us |
        |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x2B<linkmid>documentation<linktail>
        for more details.

 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V1.05 | V1.00
 @target_clib V2.04
*/
unsigned long RTX_Get_RTI_Ticks(void)
{
    _AH = RTX_RTI_COUNT ;
    asm { int RTOSVECT } ;
    // Count returned from SWI in DX:AX
    return (unsigned long)MK_FP(_DX, _AX) ;
}
#endif

/*************************************************************************/
//  Prepare for RTX_GetFineTick() use
/*************************************************************************/
#ifdef _rtxtf1_
/*
 @doc DOC_rtxtf1_
 ---------------------------------------------------------------
 Initialize RTI tick pointer needed for RTX_GetFineTick()
 ---------------------------------------------------------------
 @clib  RTX_FineTickInit | Initialize data required by
      the <linkto>rtxtf2.htm<linkmid>RTX_GetFineTick<linktail>
      and <linkto>rtxtf3.htm<linkmid>RTX_GetTick_us<linktail>
      API. |
        <cfont>void RTX_FineTickInit (void);<efont> |
 @rdesc -- none --
 @comm  This function is implicitly called by the
     <linkto>rtxtf2.htm<linkmid>RTX_GetFineTick<linktail>
      and <linkto>rtxtf3.htm<linkmid>RTX_GetTick_us<linktail>
      API if it has not already been called explicitly by the
      user.<nl>
      <nl>
      Interrupts are enabled within the @Chip-RTOS API
      call made here.<s2>  Consequently, it may be advisable
      to call this function from your application program's initialization
      area to avoid this action during your real-time operation.<s2>
      After a single call here, this one-shot function performs no
      operation on subsequent calls since its job is already done
      (unless the
      <linkto>../BIOS/bios218.htm<linkmid>power mode<linktail> has been adjusted).<nl>
      <nl>
      Some global constants are initialized by this API.<s2>
      This data is used internally by the other
      C-library functions, but may also be of general use to the
      application.<s2> (The names given these have been preceded
      with an underscore to avoid name space conflicts.)<s2>
      These constants are listed here.<nl>
      <nl>
      <linktag pRti_Tick>
      <bold>unsigned long far<s2>  *_pRti_Tick ;<bolde><nl>
        <ul><nl>
          This pointer references the 32 bit Real-Time Interrupt
          up counter internal to the @Chip-RTOS.<s2><bold><i>This location
          should never be written to from outside the @Chip-RTOS!<bolde><ie><s2>
          Note that for reliable reads, interrupts must be momentarily
          masked if both 16 bit halves are sampled.<nl>
        <ule><nl>
      <linktag RTI_kHz>
      <bold>unsigned int<s2> _RTI_kHz ;<bolde><nl>
        <ul><nl>
        The Real-Time Interrupt
        <linkto>../../rtirate.htm<linkmid>rate<linktail>
        in kHz.<s2>(For SC1x systems this value will always be 1.)
        <ule><nl>
      <linktag us_per_RTI>
      <bold>unsigned int<s2> _us_per_RTI ;<bolde><nl>
        <ul><nl>
        Number of microseconds per Real-Time Interrupt.<s2>
        (For SC1x systems this value will always be 1000.)
        <ule><nl>
      <linktag Timer2_Limit>
      <bold>unsigned int<s2> _Timer2_Limit ;<bolde><nl>
        <ul><nl>
        Hardware TIMER2 ticks per Real-Time Interrupt.
        <ule><nl>
      <linktag Timer2Tick_per_us>
      <bold>unsigned int<s2>  _Timer2Tick_per_us ;<bolde><nl>
        <ul><nl>
        Number of hardware TIMER2 ticks per microsecond.
        <ule><nl>
 @commtarget SC1x3/SC2x | For some selected Real-Time Interrupt rates,
        the  <cfont>_us_per_RTI<efont> and <cfont>_Timer2Tick_per_us<efont>
        values computed here will not be accurate.<s2>  This is the case
        for any
        <linkto>../../config.htm#TIMER_RTI<linkmid>RTI<linktail>
        rates which do not divide 1000 an integral number of times,
        e.g. 15 kHz.<s2> Consequently the
        <linkto>rtxtf3.htm<linkmid>RTX_GetTick_us<linktail> API
        should not be used for such configurations, since the computation
        done within that API relies on the accuracy of these constants.<nl>
 @Also  rtxtf2.htm |  RTX_GetFineTick |
        rtxtf3.htm |  RTX_GetTick_us |
         |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.<s2>
        Refer to this RTOS API function's
        <linkto>../../dosemu.htm#0x210x50<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/

unsigned long far  *_pRti_Tick ;
unsigned int        _RTI_kHz ;
unsigned int        _us_per_RTI ;
unsigned int        _Timer2_Limit ;
unsigned int        _Timer2Tick_per_us ;

void RTX_FineTickInit (void)
{
    if (_Timer2_Limit != (unsigned int) inport(T2CMPA))    // Need initialization?
    {
        _AH = 0x50 ;                    // Debugger support service index
        asm { int 0x21 } ;              // DOS interrupt
        _RTI_kHz = _AH + 1 ;
        // SI:DI contains far pointer to RTX timing data structure.
        //  First four bytes here are the idle loop up count DWORD
        //  Next four bytes are the RTI_Count DWORD we are interested in.
        _pRti_Tick = (DWORD far *)MK_FP(_SI,_DI + 4) ;
        _us_per_RTI = 1000 / _RTI_kHz ;
        _Timer2_Limit = inport(T2CMPA) ;
        // [ticks/us]      = [ticks/RTI]   / [us/RTI]
        _Timer2Tick_per_us = _Timer2_Limit / _us_per_RTI ;
    }
}
#endif


/*************************************************************************/
// Return fine tick count of system clock
/*************************************************************************/
#ifdef _rtxtf2_
/*
 @doc DOC_rtxtf2_
 ---------------------------------------------------------------
 Return high resolution timer information
 ---------------------------------------------------------------
 @clib  RTX_GetFineTick | Get real-time interrupt count and hardware
        TIMER2 up count. |
        <cfont>void RTX_GetFineTick (RTX_FINE_TICK *report);<efont> |
 @parm  int | report  | Output parameter,  pointer to a
        <code>RTX_FINE_TICK<codee> structure which will receive the
        timing information.<s2>  This structure consists of a 32 bit
        <code>Rti_Count<codee> union allowing WORD wise access to the
        32 bit Real-Time Interrupt count, followed by a 16 bit TIMER2
        reading.<s2> See type definition below in comments.
 @rdesc -- none --
 @comm  This procedure's main purpose in life is to support the more
      user friendly <linkto>rtxtf3.htm<linkmid>RTX_GetTick_us<linktail>
      API.<s2> However some real-time appplications may be interested
      in using this function directly to avoid the additional computation
      overhead added by the conversion to microseconds of the data
      collected here.<s2> For example if an Interrupt Service
      Routine (ISR) needs to know precisely what time it is then it might
      be a wiser design decision to buffer the raw data collected by this
      API for later off-line processing rather than hanging around waiting
      for a conversion to microseconds within the ISR.<s2>
      (On the other hand, the conversion to microseconds has a data
      reduction aspect to it.)<nl>
      <nl>
      If the <linkto>rtxtf1.htm<linkmid>RTX_FineTickInit<linktail>
      API has not yet been called, then this call will be made
      one time to obtain the <code>_pRti_Tick<codee> internal data
      <linkto>rtxtf1.htm#pRti_Tick<linkmid>pointer<linktail>
      that is required here.<s2>  (This initialization function is also called if the 
      <linkto>../BIOS/bios218.htm<linkmid>low power mode<linktail>
      of operation has been changed.)<s2>  Making this additional API call is
      time consuming (slightly) and results in the interrupts being
      enabled.<s2> Therefore calling
      <linkto>rtxtf1.htm<linkmid>RTX_FineTickInit<linktail> prior to
      using this API may be advisable.<nl>
      <nl>
      Once this initialization has been handled, this API is
      well suited for real-time applications.<s2>  It becomes
      both re-entrant and respects the interrupt masking applied
      by the caller.<s2>  Consequently calling this API from inside
      hardware interrupts is no problem.<s2> These interrupt service
      routines do not need to be
      <linkto>../../hardware.htm#0xA10x84<linkmid>registered<linktail>
      with the RTX.<s2> No further calls into the @Chip-RTOS
      are necessary since both the @Chip-RTOS 32 bit RTI up
      counter (via the pointer) and the TIMER2 hardware count are
      sampled here directly.<nl>
      <nl>
       The <code>_RTI_kHz<codee> global
       <linkto>rtxtf1.htm#RTI_kHz<linkmid>constant<linktail> can be inspected
       to determine the <linkto>../../rtirate.htm<linkmid>RTI<linktail>
       rate in effect (always 1 for SC1x systems).<nl>
       <nl>
       The data returned by this API is output to the following structure
       type.
 @raw
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
 @Also  rtxtf1.htm |  RTX_FineTickInit |
        rtxtf3.htm |  RTX_GetTick_us |
         |
 @Also  rtx2B.htm |  RTX_Get_RTI_Ticks |
        rtx2AA.htm |  RTX_GetTickCount |
         |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  After <linkto>rtxtf1.htm<linkmid>RTX_FineTickInit<linktail>
        has been invoked a single time, this library function
        makes no entry into the RTOS.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/

void RTX_GetFineTick (RTX_FINE_TICK *report)
{
    WORD interrupt_status ;
    // This test will also detect a change to low power mode operation change.
    if (_Timer2_Limit != (unsigned int) inport(T2CMPA))    // Need initialization?
    {
        RTX_FineTickInit() ;
    }

    //********************
    SAVE_AND_MASK ;                     // Enter critical section
    //********************
    report->Timer2_Count = inport(T2CNT) ;
    interrupt_status     = inport(INTSTS) ;  // For clock carry test

    report->Rti_Count.Full = *_pRti_Tick ;  // Read @Chip-RTOS up counter

    // Check if timer interrupt is pending here.
    if (interrupt_status & TMR2_BIT)    // Timer tick interrupt pending?
    {
        report->Rti_Count.Full++ ;                  // Carry into MSH.
        report->Timer2_Count  = inport(T2CNT) ;     // Assure after the carry
    }
    //********************
    RESTORE_MASK ;                      // Exit critical section
    //********************
}
#endif

/*************************************************************************/
// Return system clock microseconds
/*************************************************************************/
#ifdef _rtxtf3_
/*
 @doc DOC_rtxtf3_
 ---------------------------------------------------------------
 Return system clock microseconds
 ---------------------------------------------------------------
 @clib  RTX_GetTick_us | Get system time resolved to microseconds. |
        <cfont>unsigned long RTX_GetTick_us (void);<efont> |
 @rdesc System time in microseconds
 @comm  This function converts the high resolution system time data
       collected by the <linkto>rtxtf2.htm<linkmid>RTX_GetFineTick<linktail>
       API to microseconds and returns this
       unsigned long 32 bit count value.<nl>
       <nl>
       Note that this count rolls over to zero after each 2**32 microseconds
       of operation, which is about 71.582 minutes.<nl>
       <nl>
      If the <linkto>rtxtf1.htm<linkmid>RTX_FineTickInit<linktail>
      API has not been called, then this call will be made here one
      time.<s2> (This initialization function is also called if the 
      <linkto>../BIOS/bios218.htm<linkmid>lower power mode<linktail>
      of operation has been changed.)<s2>
      Making this additional API call is time consuming and
      results in the interrupts being enabled.<s2> Therefore calling
      <linkto>rtxtf1.htm<linkmid>RTX_FineTickInit<linktail> prior to
      using this API may be advisable for time critical applications.<nl>
      <nl>
      Once this initialization has been handled by the
      <linkto>rtxtf1.htm<linkmid>RTX_FineTickInit<linktail> API,
      this <code>RTX_GetTick_us()<codee> API function is then suitable
      for use within an Interrupt Service Routine.<s2> Interrupts are masked
      here and then restored to their state on entry.<s2> Note that no call
      into the @Chip-RTOS API is required by this API following
      the initialization step.<nl>
      <nl>
       Refer to <linkto>rtxtf2.htm<linkmid>RTX_GetFineTick<linktail>
       description for more details.
 @commtarget SC1x3/SC2x |
     <bold>CAUTION:<bolde><nl>
     <nl>
       If the system's real-time interrupt has been
        <linkto>../../config.htm#TIMER_RTI<linkmid>configured<linktail>
        for kHz <linkto>../../rtirate.htm<linkmid>rates<linktail>
        which do not divide into 1000 an integral number of
        times, then this API is inaccurate due to fixed point arithmetic
        truncation problems and therefore should not be used.<s2> The problem
        arises with the <code>_us_per_RTI<codee>
        <linkto>rtxtf1.htm#us_per_RTI<linkmid>constant<linktail> used here,
        computed as:<nl>
        <ul><nl>
            <code>_us_per_RTI = 1000 / _RTI_kHz<codee><nl>
        <ule><nl>
        So for RTI rates like 15 kHz this integer arithmetic truncates
        and the results from this API are not accurate.<nl>
        <nl>
        The following RTI settings allow this API to function:<nl>
        <ul><nl>
        [1, 2, 4, 5, 8, 10, 20, 25, 40, 50]<nl>
        <ule><nl>
        Any RTI settings from the following set will cause this
        API to <bold><i>not work properly<ie><bolde>:<nl>
        <ul><nl>
        [3, 6, 12, 15, 16, 24, 30, 32, 48]<nl>
        <ule><nl>
 @Also  rtxtf1.htm |  RTX_FineTickInit |
        rtxtf2.htm |  RTX_GetFineTick |
         |
 @Also  rtx2B.htm |  RTX_Get_RTI_Ticks |
        rtx2AA.htm |  RTX_GetTickCount |
         |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  After <linkto>rtxtf1.htm<linkmid>RTX_FineTickInit<linktail>
        has been invoked a single time, this library function
        makes no entry into the RTOS.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/

unsigned long RTX_GetTick_us (void)
{
    RTX_FINE_TICK report ;

    RTX_GetFineTick (&report) ;

    // [us] = [RTI] * [us/RTI]
    return  report.Rti_Count.Full * _us_per_RTI
          + report.Timer2_Count / _Timer2Tick_per_us ;
}
#endif


/*************************************************************************/
// Get RTI ticks per millisecond rate
/*************************************************************************/
#ifdef _rtx2BA_
/*
 @doc DOC_rtx2BA_
 ---------------------------------------------------------------
 Get RTI rate
 ---------------------------------------------------------------
 @clib  RTX_Get_RTI_Rate | Get system's Real-Time Interrupt
         (<linkto>../../rtirate.htm<linkmid>RTI<linktail>)
         rate in kHz. |
        <cfont>unsigned int RTX_Get_RTI_Rate (void);<efont> |
 @rdesc Real-Time interrupt rate in kHz
 @commtarget SC1x | For SC1x systems which always operate at 1 kHz
        RTI rate, this API replaced by a macro in the library
        header file defined as a fixed value of '1'.
 @commtarget SC1x3/SC2x | On SC1x3/SC2x systems the RTI rate can
        be configured with the
        <linkto>../../config.htm#TIMER_RTI<linkmid>CHIP.INI<linktail>
         for rates above 1 kHz.<s2>
        This function reads out the configured setting.
 @Also  rtx2B.htm |  RTX_Get_RTI_Ticks |
        | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x2B<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version     n/a  |  n/a  |  n/a  | V1.05 | V1.00
 @target_clib V2.04
*/
unsigned int RTX_Get_RTI_Rate (void)
{
    _AH = RTX_RTI_COUNT ;
    asm { int RTOSVECT } ;
    return _CX ;
}
#endif

/*************************************************************************/
// Install high resolution timer procedure
/*************************************************************************/
#ifdef _rtx2F_
/*
 @doc DOC_rtx2F_
 ---------------------------------------------------------------
 Install high resolution timer procedure
 ---------------------------------------------------------------
 @clib  RTX_Fine_Timer | Install a high resolution timer callback procedure
        that will be periodically executed by the kernel. |
        <cfont>int RTX_Fine_Timer (<nl>
        <tab><tab><tab> const TimerProc_Structure far *TProcPtr );<efont> |
 @parm  int | TProcPtr  | Input parameter,  pointer to a
        <code>TimerProc_Structure<codee>
        <linkto>../../rtxstruc.htm#TimerProc_Structure<linkmid>type<linktail>.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @commtarget SC1x | For SC1x systems which always operate at 1 kHz
        RTI rate, this API is mapped to the
        <linkto>rtx30.htm<linkmid>RTX_Install_Timer<linktail> API by
        a macro defined in the library header file.
 @commtarget SC1x3/SC2x | A timer ID is output to the 16 bit location referenced by
        <code>timerID<codee>
        <linkto>../../rtxstruc.htm#TimerID<linkmid>member<linktail>
        of your <code>TimerProc_Structure<codee>.<nl>
        <nl>
        Alternate method <linkto>rtx2FA.htm<linkmid>RTX_Fine_TimerP<linktail>
        allows the timer installation to be performed based on direct
        parameters.<nl>
        <nl>
        You must call either the <linkto>rtx32.htm<linkmid>RTX_Start_Timer<linktail>,
        <linkto>rtx34.htm<linkmid>RTX_Timer_Delay<linktail> or
        <linkto>rtx34A.htm<linkmid>RTX_Timer_Delay_RTI<linktail>
        API function to get the kernel to start calling your new timer procedure.<nl>
        <nl>
        <bold>Important:<bolde><s2>Timer procedures are executed on the stack
        of the kernel task at a high priority, so they should be as short as
        possible.<s2>  Avoid calling time consuming functions.<nl>
 @Also  rtx2FA.htm | RTX_Fine_TimerP |
        rtx32.htm  | RTX_Start_Timer    |
        rtx31.htm  | RTX_Remove_Timer
 @Also  rtx30.htm  | RTX_Install_Timer |
        | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x2F<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.05 | V1.00
 @target_clib V2.04
*/
int RTX_Fine_Timer (const TimerProc_Structure far * TProcPtr)
{
    asm { LES   DI,TProcPtr } ;
    _AH = RTX_TIMER_FINE ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
// Alternate Install timer procedure
/*************************************************************************/
#ifdef _rtx2FA_
/*
 @doc DOC_rtx2FA_
 ---------------------------------------------------------------
 Install high resolution timer procedure
 ---------------------------------------------------------------
 @clib  RTX_Fine_TimerP | Install a high resolution timer
        callback procedure
        that will be periodically executed by the kernel. |
        <cfont>int RTX_Fine_TimerP ( unsigned int far *timerID,<nl>
        <tab><tab><tab><tab><tab><tab> RTX_TIMER_CALLBACK proc,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned long lParam,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned long name,<nl>
        <tab><tab><tab><tab><tab><tab> long rti_ticks );<efont> |
 @parm  int | timerID  | Output parameter, pointer to location
        to receive new timer ID.
 @parm  int | proc  | Far vector to timer callback procedure.
 @parm  int | lParam  | Any 32 bit value you would like to see
        again on each entry into the timer procedure.
 @parm  int | name  | Provisional 4 character timer name (little
        endian order), not of any use in current implementation.
 @parm  int | rti_ticks  | Interval between calls
        to timer procedure in Real-Time Interrupt
        (<linkto>../../rtirate.htm<linkmid>RTI<linktail>)
        ticks.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @commtarget SC1x | For SC1x systems which always operate at 1 kHz
        RTI rate, this API is mapped to the
        <linkto>rtx30A.htm<linkmid>RTX_Install_TimerP<linktail> API by
        a macro defined in the library header file.
 @commtarget SC1x3/SC2x | The RTX_TIMER_CALLBACK prototype has the form:<nl><nl>
        <tab><code>void huge RTX_TIMER_CALLBACK(<nl>
        <tab><tab>unsigned int timer_id,
        unsigned long lParam )<codee><nl>
        <nl>
        The timer callback procedure's input parameters may be ignored and
        the function declared with void parameters.<s2>The <code>timer_id<codee>
        parameter is a copy of the timer ID output by this function.<s2>The
        <code>lParam<codee> input parameter is a copy of the <code>lParam<codee>
        parameter you supplied to <code>RTX_Fine_TimerP<codee>.<nl>
        <nl>
        You must call either the <linkto>rtx32.htm<linkmid>RTX_Start_Timer<linktail>,
        <linkto>rtx34.htm<linkmid>RTX_Timer_Delay<linktail> or
        <linkto>rtx34A.htm<linkmid>RTX_Timer_Delay_RTI<linktail>
        API function to get the kernel to start calling your new timer procedure.<nl>
        <nl>
        <bold>Important:<bolde><s2>Timer procedures are executed on the stack
        of the kernel task at a high priority, so they should be as short as
        possible.<s2>  Avoid calling time consuming functions.<nl>
 @Also  rtx2F.htm |  RTX_Fine_Timer |
        rtx32.htm |  RTX_Start_Timer   |
        rtx31.htm |  RTX_Remove_Timer
 @Also  rtx30A.htm  | RTX_Install_TimerP |
        | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x2F<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.05 | V1.00
 @target_clib V2.04
*/
int RTX_Fine_TimerP (unsigned int  far  *timerID,
                     RTX_TIMER_CALLBACK  proc,
                     unsigned long       lParam,
                     unsigned long       name,
                     long                rti_ticks)
{
    _ES = _SS ;
    asm { LEA  DI,timerID } ;   // Now ES:DI = &timerID = &TimerProc_Structure.
    _AH = RTX_TIMER_FINE ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif


/*************************************************************************/
// Install timer procedure
/*************************************************************************/
#ifdef _rtx30_
/*
 @doc DOC_rtx30_
 ---------------------------------------------------------------
 Install timer procedure
 ---------------------------------------------------------------
 @clib  RTX_Install_Timer | Install a timer callback procedure
        that will be periodically executed by the kernel. |
        <cfont>int RTX_Install_Timer (<nl>
        <tab><tab><tab> const TimerProc_Structure far *TProcPtr );<efont> |
 @parm  int | TProcPtr  | Input parameter,  pointer to a
        <code>TimerProc_Structure<codee>
        <linkto>../../rtxstruc.htm#TimerProc_Structure<linkmid>type<linktail>.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  A timer ID is output to the 16 bit location referenced by
        <code>timerID<codee>
        <linkto>../../rtxstruc.htm#TimerID<linkmid>member<linktail>
        of your <code>TimerProc_Structure<codee>.<nl>
        <nl>
        Alternate method <linkto>rtx30A.htm<linkmid>RTX_Install_TimerP<linktail>
        allows the timer installation to be performed based on direct
        parameters.<nl>
        <nl>
        You must call either the <linkto>rtx32.htm<linkmid>RTX_Start_Timer<linktail>,
        <linkto>rtx34.htm<linkmid>RTX_Timer_Delay<linktail> or
        <linkto>rtx34A.htm<linkmid>RTX_Timer_Delay_RTI<linktail>
        API function to get the kernel to start calling your new timer procedure.<nl>
        <nl>
        <bold>Important:<bolde><s2>Timer procedures are executed on the stack
        of the kernel task at a high priority, so they should be as short as
        possible.<s2>  Avoid calling time consuming functions.<nl>
 @Also  rtx30A.htm | RTX_Install_TimerP |
        rtx32.htm  | RTX_Start_Timer    |
        rtx31.htm  | RTX_Remove_Timer
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x30<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Install_Timer (const TimerProc_Structure far * TProcPtr)
{
    asm { LES   DI,TProcPtr } ;
    _AH = RTX_INSTALL_TIMER ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
// Alternate Install timer procedure
/*************************************************************************/
#ifdef _rtx30A_
/*
 @doc DOC_rtx30A_
 ---------------------------------------------------------------
 Install timer procedure
 ---------------------------------------------------------------
 @clib  RTX_Install_TimerP | Install a timer callback procedure
        that will be periodically executed by the kernel. |
        <cfont>int RTX_Install_TimerP ( unsigned int far *timerID,<nl>
        <tab><tab><tab><tab><tab><tab> RTX_TIMER_CALLBACK proc,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned long lParam,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned long name,<nl>
        <tab><tab><tab><tab><tab><tab> long interval );<efont> |
 @parm  int | timerID  | Output parameter, pointer to location
        to receive new timer ID.
 @parm  int | proc  | Far vector to timer callback procedure.
 @parm  int | lParam  | Any 32 bit value you would like to see
        again on each entry into the timer procedure.
 @parm  int | name  | Provisional 4 character timer name (little
        endian order), not of any use in current implementation.
 @parm  int | interval  | Milliseconds interval between calls
        to timer procedure.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The RTX_TIMER_CALLBACK prototype has the form:<nl><nl>
        <tab><code>void huge RTX_TIMER_CALLBACK(<nl>
        <tab><tab>unsigned int timer_id,
        unsigned long lParam )<codee><nl>
        <nl>
        The timer callback procedure's input parameters may be ignored and
        the function declared with void parameters.<s2>The <code>timer_id<codee>
        parameter is a copy of the timer ID output by this function.<s2>The
        <code>lParam<codee> input parameter is a copy of the <code>lParam<codee>
        parameter you supplied to <code>RTX_Install_TimerP<codee>.<nl>
        <nl>
        You must call either the <linkto>rtx32.htm<linkmid>RTX_Start_Timer<linktail>,
        <linkto>rtx34.htm<linkmid>RTX_Timer_Delay<linktail> or
        <linkto>rtx34A.htm<linkmid>RTX_Timer_Delay_RTI<linktail>
        API function to get the kernel to start calling your new timer procedure.<nl>
        <nl>
        <bold>Important:<bolde><s2>Timer procedures are executed on the stack
        of the kernel task at a high priority, so they should be as short as
        possible.<s2>  Avoid calling time consuming functions.<nl>
 @Also  rtx30.htm |  RTX_Install_Timer |
        rtx32.htm |  RTX_Start_Timer   |
        rtx31.htm |  RTX_Remove_Timer
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x30<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Install_TimerP (unsigned int  far  *timerID,
                        RTX_TIMER_CALLBACK  proc,
                        unsigned long       lParam,
                        unsigned long       name,
                        long                interval)
{
    _ES = _SS ;
    asm { LEA  DI,timerID } ;   // Now ES:DI = &timerID = &TimerProc_Structure.
    _AH = RTX_INSTALL_TIMER ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif


/*************************************************************************/
// Remove timer procedure
/*************************************************************************/
#ifdef _rtx31_
/*
 @doc DOC_rtx31_
 ---------------------------------------------------------------
 Remove timer procedure
 ---------------------------------------------------------------
 @clib  RTX_Remove_Timer | Stop execution and remove a timer procedure. |
        <cfont>int RTX_Remove_Timer ( unsigned int timerID );<efont> |
 @parm  int | timerID  | The timer ID output from
        <linkto>rtx30.htm<linkmid>RTX_Install_Timer<linktail>.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @Also  rtx30.htm |  RTX_Install_Timer |
        rtx32.htm |  RTX_Start_Timer   | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x31<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Remove_Timer(unsigned int timerID)
{
    _BX = timerID ;
    _AH = RTX_REMOVE_TIMER ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
// Start periodic execution of timer procedure
/*************************************************************************/
#ifdef _rtx32_
/*
 @doc DOC_rtx32_
 ---------------------------------------------------------------
 Start periodic execution of timer procedure
 ---------------------------------------------------------------
 @clib  RTX_Start_Timer | Start periodic execution of timer procedure. |
        <cfont>int RTX_Start_Timer ( unsigned int timerID );<efont> |
 @parm  int | timerID  | The timer ID output from
        <linkto>rtx30.htm<linkmid>RTX_Install_Timer<linktail>.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code
        (invalid timer ID).
 @Also  rtx34.htm |  RTX_Timer_Delay |
        rtx30.htm |  RTX_Install_Timer |
        rtx33.htm |  RTX_Stop_Timer
 @Also  rtx34A.htm | RTX_Timer_Delay_RTI |
        | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x32<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Start_Timer(unsigned int timerID)
{
    _BX = timerID ;
    _AH = RTX_START_TIMER ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
// Stop periodic execution of timer procedure
/*************************************************************************/
#ifdef _rtx33_
/*
 @doc DOC_rtx33_
 ---------------------------------------------------------------
 Stop periodic execution of timer procedure
 ---------------------------------------------------------------
 @clib  RTX_Stop_Timer | Stop execution of timer procedure. |
        <cfont>int RTX_Stop_Timer ( unsigned int timerID );<efont> |
 @parm  int | timerID  | The timer ID output from
        <linkto>rtx30.htm<linkmid>RTX_Install_Timer<linktail>.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @Also  rtx34.htm |  RTX_Timer_Delay |
        rtx30.htm |  RTX_Install_Timer |
        rtx32.htm |  RTX_Start_Timer
 @Also  rtx34A.htm | RTX_Timer_Delay_RTI |
        | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x33<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Stop_Timer(unsigned int timerID)
{
    _BX = timerID ;
    _AH = RTX_STOP_TIMER ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
// Set timer delay interval in milliseconds
/*************************************************************************/
#ifdef _rtx34_
/*
 @doc DOC_rtx34_
 ---------------------------------------------------------------
 Set timer delay interval in milliseconds
 ---------------------------------------------------------------
 @clib  RTX_Timer_Delay | Set timer delay interval in milliseconds. |
        <cfont>int RTX_Timer_Delay ( unsigned int timerID<nl>
        <tab><tab><tab><tab><tab> long delay_ms);<efont> |
 @parm  int | timerID  | The timer ID output from
        <linkto>rtx30.htm<linkmid>RTX_Install_Timer<linktail>.
 @parm  int | delay_ms  | Delay period in milliseconds.<s2>
     If this value is zero the timer is deactivated.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm This function can be used on periodic timers to set the
        interval to the next call, thereby providing a phase control.<nl>
        <nl>
        For non-periodic timers this function can be called with
        varying delay values.<nl>
        <nl>
        When 'delay_ms' is set to '1', this function is identical
        to the <linkto>rtx32.htm<linkmid>RTX_Start_Timer<linktail>
        function (assuming 1 kHz RTI operation).<nl>
        <nl>
       When 'delay_ms' is set to '0', this function is identical to
       the <linkto>rtx33.htm<linkmid>RTX_Stop_Timer<linktail> function.<nl>

 @Also  rtx30.htm |  RTX_Install_Timer |
        rtx32.htm |  RTX_Start_Timer   |
        rtx33.htm |  RTX_Stop_Timer
 @Also  rtx34A.htm |  RTX_Timer_Delay_RTI |
         | |  |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x34<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/
int RTX_Timer_Delay(unsigned int timerID, long delay_ms)
{
    _DX = timerID ;
    _CX = 0 ;               // Boolean FALSE for milliseconds, not RTI.
    _ES = FP_SEG((void far *)delay_ms) ;
    _BX = FP_OFF((void far *)delay_ms) ;
    _AH = RTX_TIMER_DELAY ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
// Set timer delay interval in RTI ticks
/*************************************************************************/
#ifdef _rtx34A_
/*
 @doc DOC_rtx34A_
 ---------------------------------------------------------------
 Set timer delay interval in RTI ticks
 ---------------------------------------------------------------
 @clib  RTX_Timer_Delay_RTI | Set timer delay interval in units
             of Real-Time Interrupt (RTI) ticks. |
        <cfont>int RTX_Timer_Delay_RTI ( unsigned int timerID<nl>
        <tab><tab><tab><tab><tab><tab><s1> long rti_ticks);<efont> |
 @parm  int | timerID  | The timer ID output from
        <linkto>rtx30.htm<linkmid>RTX_Install_Timer<linktail>.
 @parm  int | rti_ticks  | Number of
     <linkto>../../rtirate.htm<linkmid>RTI<linktail>
     ticks for timer delay period.<s2>
     If this value is zero the timer is deactivated.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @commtarget SC1x |
        For SC1x systems this API is identical to the
        <linkto>rtx34.htm<linkmid>RTX_Timer_Delay<linktail> API.<nl>
 @commtarget SC1x3/SC2x |
        This function can be used on periodic timers to set the
        interval to the next call, thereby providing a phase control.<nl>
        <nl>
        For non-periodic timers this function can be called with
        varying delay values.<nl>
        <nl>
        When 'rti_ticks' is set to '1', this function is identical
        to the <linkto>rtx32.htm<linkmid>RTX_Start_Timer<linktail>
        function.<nl>
        <nl>
       When 'rti_ticks' is set to '0', this function is identical to
       the <linkto>rtx33.htm<linkmid>RTX_Stop_Timer<linktail> function.<nl>

 @Also  rtx30.htm |  RTX_Install_Timer |
        rtx32.htm |  RTX_Start_Timer   |
        rtx33.htm |  RTX_Stop_Timer
 @Also  rtx34.htm |  RTX_Timer_Delay |
         | |  |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x34<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.20 | V1.20 | V1.20 | V1.05 | V1.00
 @target_clib V2.04
*/
int RTX_Timer_Delay_RTI(unsigned int timerID, long rti_ticks)
{
    _DX = timerID ;
    _CX = 1 ;               // Boolean TRUE for raw RTI ticks.
    _ES = FP_SEG((void far *)rti_ticks) ;
    _BX = FP_OFF((void far *)rti_ticks) ;
    _AH = RTX_TIMER_DELAY ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
#ifdef _rtx35_
/*
 @doc DOC_rtx35_
 ---------------------------------------------------------------
 Install RTI Hook callback
 ---------------------------------------------------------------
 @clib  RTX_Install_RTI_Hook | This function installs a callback function
    which executes periodically within the 1000 Hz (default rate)
    Real-Time Interrupt (RTI). |
        <cfont>void RTX_Install_RTI_Hook (<nl>
        <tab><tab><tab><tab> RTI_HOOK vector,<nl>
        <tab><tab><tab><tab> unsigned char delay<efont><s2>) |
 @parm   int | vector  | Far pointer to callback procedure to be invoked
    from within 1000 Hz RTI.<s2>  Set this argument to NULL to remove
    a callback.<nl>
    <ul><nl>
    <code>typedef unsigned char huge (far * <bold>RTI_HOOK<bolde>)
        (void) ;<codee><nl>
    <ule>

 @parm   int | delay  | Number of 1000 Hz RTI before first call.<s2>
    Set to 1 for callback on very next RTI.<s2> Set to 0 for 256 RTI later.
 @rdesc  -- none --
 @comm
    External interrupts are masked and then restored to their state on
    entry.<nl>
    <nl>
    The term 'tick' used here refers to a 1 millisecond period
    when the system timer RTI is operated at its default rate
    of 1000 Hz.<s2> Note that this RTI rate can be configured to
    higher rates with the
    <linkto>../../config.htm#TIMER_RTI<linkmid>[TIMER] RTI<linktail>
    setting in the CHIP.INI, in which case tick time will be
    under 1 millisecond.<nl>
    <nl>
    The callback function is free to use any register except for the
    DS and DI registers.<s2> <bold>These two registers must be
    preserved.<bolde><nl>
    <nl>
    This API was provided for applications which require
    a precise and variable timing for high frequency front end
    hardware sampling, for example.<nl>
    <nl>
    The least significant byte of the callback’s return value
    (AL register) will be used as the delay count in milliseconds
    to the next callback.<s2>  Examples (assuming 1000Hz RTI):<nl>
    <ul><nl>
    <li>Return 1 to execute again on very next RTI, 1 millisecond later.<nl>
    <li>Return zero for a delay of 256 milliseconds.<nl>
    <li>Return 5 to execute at a 200 Hz rate.<nl>
    <ule><nl>
    The system supports only a single RTI hook.<s2>  Installing a second
    overwrites the first.<s2>  A callback can be removed by installing a
    NULL callback vector.<nl>
    <nl>
    Unlike with the RTX  <linkto>rtx30.htm<linkmid>timer<linktail>
    callback functions, which execute after
    a task switch to the kernel task, this RTI hook executes directly
    in the context of the interrupt.<s2>  No task switch occurs prior
    to the callback and execution proceeds on the stack of what ever task
    was interrupted.<s2>  Consequently the callback should be conservative
    with its stack space usage.<nl>
    <nl>
    This interrupt has been registered with the RTX kernel, so the user is
    free to use the task triggering RTX API functions from within
    the callback such as:<nl>
    <ul><nl>
           <linkto>rtx06.htm<linkmid>RTX_Wakeup_Task<linktail><nl>
           <linkto>rtx0F.htm<linkmid>RTX_Resume_Task<linktail><nl>
           <linkto>rtx1A.htm<linkmid>RTX_Signal_Sem<linktail><nl>
           <linkto>rtx42.htm<linkmid>RTX_Signal_Events<linktail><nl>
           <linkto>rtx52.htm<linkmid>RTX_Send_Msg<linktail><nl>
    <ule><nl>
    However any time consuming activity must be avoided and it is not
    legal to call any RTOS API which could block or result in current
    task being suspended.<s2>  As a rough guideline, the dwell within
    this callback should be held to under 50 us.<s2>  Either very carefully
    written C code, or assembly code is recommended here.<nl>
    <nl>
    As true for any installed callback function, it is essential
    that an application program remove its RTI hook callback
    (<cfont>vector<efont> set to zero) before program termination.<nl>
 @Also  rtx30.htm | RTX_Install_Timer |
        | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x35<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.11 | V1.00
 @target_clib V2.08
*/

void RTX_Install_RTI_Hook (RTI_HOOK vector, unsigned char delay)
{
    asm { LES  BX,vector } ;    // ES:BX = vector
    _CL = delay ;
    _AH = RTX_SET_RTI_HOOK ;
    asm { int RTOSVECT  } ;
}

#endif

/*************************************************************************/
// Create event group
/*************************************************************************/
#ifdef _rtx40_
/*
 @doc DOC_rtx40_
 ---------------------------------------------------------------
 Create event group
 ---------------------------------------------------------------
 @clib  RTX_Create_EventGroup | Create an event group. |
        <cfont>int RTX_Create_EventGroup ( unsigned int far *id_ptr,<nl>
        <tab><tab><tab><tab><tab><tab><tab>const char far *name, <nl>
        <tab><tab><tab><tab><tab><tab><tab>unsigned int init_value );<efont> |
 @parm  int | id_ptr  | Output parameter, pointer to where event group ID
        will be put by this function if successful.
 @parm  int | name  | Input parameter, 4 character name for new event group
        (need not be zero terminated, but must be 4 bytes).
 @parm  int | init_value  | Initial value of the 16 event flags of the group.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code
        (no free event group available).
 @comm  Each event group includes 16 event flags.<s2> Each event group has
        a unique ID.<s2>  You can provide a unique 4 character tag to identify
        the event group, for use with the
        <linkto>rtx46.htm<linkmid>RTX_Find_EventGroup<linktail> function.
 @Also  rtx41.htm |  RTX_Delete_EventGroup |
        rtx46.htm |  RTX_Find_EventGroup   |
        rtx43.htm |  RTX_Wait_For_Event
 @Also  rtx42.htm |  RTX_Signal_Events |
        rtx44.htm |  RTX_Get_EventGroup_State    |
        rtx45.htm |  RTX_Get_Saved_Events
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x40<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Create_EventGroup (unsigned int far *id_ptr,
                           const char   far *name,
                           unsigned int init_value)
{
    _BX = init_value ;
    asm { LES  DI,id_ptr } ;
    asm { PUSH DS } ;
    asm { LDS  SI, name } ;
    _AH = RTX_CREATE_EVENTGROUP ;
    asm { int RTOSVECT } ;
    asm { pop DS } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
// Delete an event group
/*************************************************************************/
#ifdef _rtx41_
/*
 @doc DOC_rtx41_
 ---------------------------------------------------------------
 Delete an event group
 ---------------------------------------------------------------
 @clib  RTX_Delete_EventGroup | Delete an event group. |
        <cfont>int RTX_Delete_EventGroup ( int id );<efont> |
 @parm  int | id  | Event group ID produced by
        <linkto>rtx40.htm<linkmid>RTX_Create_EventGroup<linktail>
        call.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code
        (event group still in use or invalid group ID).
 @comm  You should not delete an event group which is in use by another task
        or timer procedure.
 @Also  rtx40.htm |  RTX_Create_EventGroup | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x41<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Delete_EventGroup (unsigned int id)
{
    _BX = id ;
    _AH = RTX_DELETE_EVENTGROUP ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
// Signal events group
/*************************************************************************/
#ifdef _rtx42_
/*
 @doc DOC_rtx42_
 ---------------------------------------------------------------
 Signal events group
 ---------------------------------------------------------------
 @clib  RTX_Signal_Events | Signal that one or more events in a group have
        occurred by setting the event flags.<s2> If any tasks are waiting
        on these events, the Event Manager will now wake them up. |
        <cfont>int RTX_Signal_Events ( unsigned int id,<nl>
        <tab><tab><tab><tab><tab><tab>unsigned int event_mask,<nl>
        <tab><tab><tab><tab><tab><tab>unsigned int event_value );<efont> |
 @parm  int | id  | Event group ID produced by
        <linkto>rtx40.htm<linkmid>RTX_Create_EventGroup<linktail>
        call.
 @parm  int | event_mask  | 16-Bit mask identifying the flags of
        interest in the group
 @parm  int | event_value  | Event value for the 16 event flag/bits.<s2>
        Only the bits marked '1' in the event_mask are relevant here.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  This function modifies the event group bits marked by ones in the
        <code>event_mask<codee> to either '1' or '0' based on the values
        of the corresponding bits in the <code>event_value<codee> parameter.<nl>
        <nl>
        Event group bits which are zero in the <code>event_mask<codee> are
        unaffected.<nl>
        <nl>
        Note that "event occurred" condition can be either a bit '1' or '0'.<s2>
        This is application defined and is specified by the <code>value<codee>
        supplied to the <linkto>rtx43.htm<linkmid>RTX_Wait_For_Event<linktail>
        call.
 @Also  rtx40.htm  |  RTX_Create_EventGroup |
        rtx43.htm  |  RTX_Wait_For_Event   |
        rtx44.htm  |  RTX_Get_EventGroup_State
 @Also  rtx43A.htm |  RTX_Wait_For_EventP | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x42<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Signal_Events (unsigned int id,
                       unsigned int event_mask,
                       unsigned int event_value)
{
    _BX = id ;
    _CX = event_mask ;
    _DX = event_value ;
    _AH = RTX_SIGNAL_EVENTS ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif


/*************************************************************************/
// Wait for events
/*************************************************************************/
#ifdef _rtx43_
/*
 @doc DOC_rtx43_
 ---------------------------------------------------------------
 Wait for events
 ---------------------------------------------------------------
 @clib  RTX_Wait_For_Event | The calling task waits until the Event Manager
        wakes it up (the event has occurred) or the specified timeout is
        reached. |
        <cfont>int RTX_Wait_For_Event ( unsigned int id,<nl>
        <tab><tab><tab><tab><tab><tab> RTX_Wait_Event far *event_ptr );<efont> |
 @parm  int | id  | Event group ID produced by
        <linkto>rtx40.htm<linkmid>RTX_Create_EventGroup<linktail>
        call.
 @parm  int | event_ptr  | Pointer to  RTX_Wait_Event
        <linkto>../../rtxstruc.htm#RTX_Wait_Event<linkmid>structure<linktail>
        filled in by caller.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  Note that the Event Manager's wakeup mechanism is level sensitive
        (not edge triggered).<s2>  Consequently, a task may want to acknowledge
        an event bit level after a wakeup by negating the flag using the
        <linkto>rtx42.htm<linkmid>RTX_Signal_Events<linktail> function
        following a wakeup.<nl>
        <nl>
        The alternative <linkto>rtx43A.htm<linkmid>RTX_Wait_For_EventP<linktail>
        function is identical to this function, except for parameter passing
        method.<nl>
        <nl>
        The <linkto>rtx45.htm<linkmid>RTX_Get_Saved_Events<linktail>
        function can be used to pick up the event states.<nl>
 @Also  rtx40.htm  |  RTX_Create_EventGroup |
        rtx42.htm  |  RTX_Signal_Events   |
        rtx44.htm  |  RTX_Get_EventGroup_State
 @Also  rtx43A.htm |  RTX_Wait_For_EventP | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x43<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Wait_For_Event (unsigned int id, const RTX_Wait_Event far * event_ptr)
{
    _BX = id ;
    asm { LES  DI,event_ptr } ;   // Now ES:DI = &RTX_Wait_Event struct.
    _AH = RTX_WAIT_EVENTS ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
// Wait for events (Alternate method)
/*************************************************************************/
#ifdef _rtx43A_
/*
 @doc DOC_rtx43A_
 ---------------------------------------------------------------
 Wait for events using explicit parameters
 ---------------------------------------------------------------
 @clib  RTX_Wait_For_EventP | The calling task waits until the Event Manager
        wakes it up (the event has occurred) or the specified timeout is
        reached. |
        <cfont>int RTX_Wait_For_EventP ( unsigned int id, unsigned int mask,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; unsigned int value, int match,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; long timeout );<efont> |
 @parm  int | id  | Event group ID produced by
        <linkto>rtx40.htm<linkmid>RTX_Create_EventGroup<linktail>
        call.
 @parm  int | mask  | 16-Bit mask identifying the flags of interest in the group
 @parm  int | value  | Event value for the 16 event flag/bits.<s2> Only the bits
        marked '1' in the  mask  are relevant here.
 @parm  int | match  | =0 (OR): only one flag must match with value<nl>
        !=0 (AND): all flags must match with value
 @parm  int | timeout  |
        Positive value  -<gt> wait up to this number of milliseconds for an event match<nl>
        Zero            -<gt> wait forever for an event match<nl>
        Negative value  -<gt> No wait, return immediately
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  Note that the Event Manager's wakeup mechanism is level sensitive
        (not edge triggered).<s2>  Consequently, a task may want to acknowledge
        an event bit level after a wakeup by negating the flag using the
        <linkto>rtx42.htm<linkmid>RTX_Signal_Events<linktail> function
        following a wakeup.<nl>
        <nl>
        The function is identical to
        <linkto>rtx43.htm<linkmid>RTX_Wait_For_Event<linktail>,
        except for manner of parameter passing.<nl>
        <nl>
        The <linkto>rtx45.htm<linkmid>RTX_Get_Saved_Events<linktail>
        function can be used to pick up the event states.<nl>
 @Also  rtx40.htm |  RTX_Create_EventGroup |
        rtx42.htm |  RTX_Signal_Events   |
        rtx44.htm |  RTX_Get_EventGroup_State
 @Also  rtx43.htm |  RTX_Wait_For_Event | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x43<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Wait_For_EventP (unsigned int id,    unsigned int mask,
                         unsigned int value, int match, long timeout)
{
    _BX = id ;
    _ES = _SS ;
    asm { LEA  DI,mask } ;   // Now ES:DI = &mask = &RTX_Wait_Event struct.
    _AH = RTX_WAIT_EVENTS ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif


/*************************************************************************/
//Read current events on a group
/*************************************************************************/
#ifdef _rtx44_
/*
 @doc DOC_rtx44_
 ---------------------------------------------------------------
 Read current events on a group
 ---------------------------------------------------------------
 @clib  RTX_Get_EventGroup_State | Read current events on a group. |
        <cfont>int RTX_Get_EventGroup_State ( unsigned int id,<nl>
        <tab><tab><tab><tab><tab><tab><tab><s2> unsigned int far *event );<efont> |
 @parm  int | id  | Event group ID produced by
        <linkto>rtx40.htm<linkmid>RTX_Create_EventGroup<linktail>
        call.
 @parm  int | event  | Output parameter,  pointer to 16 bit location
        to receive the current state of the event flags.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code
        (invalid group ID).
 @comm  This function may be used by any program thread to acess the
        event group's current flag values.
 @Also  rtx40.htm |  RTX_Create_EventGroup |
        rtx42.htm |  RTX_Signal_Events   |
        rtx45.htm |  RTX_Get_Saved_Events
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x44<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Get_EventGroup_State (unsigned int id, unsigned int far * event)
{
    _BX = id ;
    asm { LES  DI, event } ;
    _AH = RTX_GET_EVENTGROUP_STATE ;
    asm { int RTOSVECT } ;
    return _AX ;                        // Return error code
}
#endif

/*************************************************************************/
// Get the saved event flags/bits
/*************************************************************************/
#ifdef _rtx45_
/*
 @doc DOC_rtx45_
 ---------------------------------------------------------------
 Get the saved event flags/bits
 ---------------------------------------------------------------
 @clib  RTX_Get_Saved_Events | Return the state of the 16 event flags
        as they were at the time the calling task most recently completed a
        <code>RTX_Wait_For_Event<codee> (or <code>RTX_Wait_For_EventP<codee>)
        call.  |
        <cfont>int RTX_Get_Saved_Events ( unsigned int far *Event );<efont> |
 @parm  int | Event  | Output parameter: Saved events.
 @rdesc 0: Success.
 @comm  This function accesses the event flags stored for this specific program
        thread.<s2>The event group was specified at the time of the
        <code>RTX_Wait_For_Event<codee> call.<nl>
        <nl>
        Use the
        <linkto>rtx44.htm<linkmid>RTX_Get_EventGroup_State<linktail> function
        to read current event group flag states.
 @Also  rtx40.htm |  RTX_Create_EventGroup |
        rtx42.htm |  RTX_Signal_Events   |
        rtx43.htm |  RTX_Wait_For_Event
 @Also  rtx43A.htm |  RTX_Wait_For_EventP |
        rtx44.htm |  RTX_Get_EventGroup_State |  |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x45<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Get_Saved_Events(unsigned int far *Event)
{
    _AH = RTX_GET_EVENT_FLAGS ;
    asm { int RTOSVECT } ;
    *Event = _AX ;  // events
    return _DX ;
}
#endif

/*************************************************************************/
// Find an event group, specified by 4 char name tag
/*************************************************************************/
#ifdef _rtx46_
/*
 @doc DOC_rtx46_
 ---------------------------------------------------------------
 Find an event group
 ---------------------------------------------------------------
 @clib  RTX_Find_EventGroup | Find an event group by specified name tag
        and return the unique event group ID. |
        <cfont>int RTX_Find_EventGroup ( unsigned int far *id_ptr,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; const char far *name );<efont> |
 @parm  int | id_ptr  | Output parameter, pointer to where to
        put the event group ID if found.
 @parm  int | name  | Input parameter, pointer to 4 character
        name of event group to look for.<nl>
        <nl>
        This name does not  need to be zero terminated, but must
        contain 4 bytes.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  If more than one event group exists with the specified name,
        this function will return the ID of one of these event groups.
        <s2>Which event group is returned is indeterminant when the
        name is not unique.
 @Also  rtx40.htm |  RTX_Create_EventGroup | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x46<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Find_EventGroup (unsigned int far * id_ptr, const char far * name)
{
    int error_code ;
    unsigned int the_id = 0 ;
    asm { LES  DI, name } ;
    _AH = RTX_FIND_EVENTGROUP ;
    asm { int RTOSVECT } ;
    error_code = _AX ;
    if (_DX == 0)
    {
        the_id = error_code ;        // Shuffle, _AX held event.
        error_code = 0 ;
    }
    *id_ptr = the_id ;
    return error_code ;
}
#endif


/*************************************************************************/
// Create message exchange
/*************************************************************************/
#ifdef _rtx50_
/*
 @doc DOC_rtx50_
 ---------------------------------------------------------------
 Create message exchange
 ---------------------------------------------------------------
 @clib  RTX_Create_Msg | A message exchange must be created by an application
        before it can be used.<s2> The Message Exchange Manager outputs a 16-bit
        unique ID to the caller from this call.<s2> You can provide a unique
        4 character tag to identify the message exchange. |
        <cfont>int RTX_Create_Msg ( RTX_Msg far *msg_ptr );<efont> |
 @parm  int | msg_ptr  | Input/Output parameter, pointer to a
        <code>RTX_Msg<codee>
        <linkto>../../rtxstruc.htm#RTX_Msg<linkmid>structure<linktail>.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  The caller must to fill in portions of the RTX_Msg structure
        prior to calling.<s2> The new message exchange's ID (handle)
        is returned in this structure.
 @Also  rtx51.htm |  RTX_Delete_Msg |
        rtx55.htm |  RTX_Find_Msg   |
        rtx52.htm |  RTX_Send_Msg
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x50<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Create_Msg (RTX_Msg far * msg_ptr)
{
    asm { LES  DI, msg_ptr } ;
    _AH = RTX_CREATE_MSG ;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif

/*************************************************************************/
// Delete a message exchange
/*************************************************************************/
#ifdef _rtx51_
/*
 @doc DOC_rtx51_
 ---------------------------------------------------------------
 RTX Delete Message Exchange
 ---------------------------------------------------------------
 @clib  RTX_Delete_Msg | Delete a message exchange. |
        <cfont>int RTX_Delete_Msg ( unsigned int id );<efont> |
 @parm  int | id  | The message exchange ID output on
        call to <linkto>rtx50.htm<linkmid>RTX_Create_Msg<linktail>.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code
        message exchange still in use or invalid ID).
 @Also  rtx50.htm |  RTX_Create_Msg | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x51<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Delete_Msg (unsigned int id)
{
    _BX = id ;
    _AH = RTX_DELETE_MSG ;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif



/*************************************************************************/
// Send a message to a message exchange
/*************************************************************************/
#ifdef _rtx52_
/*
 @doc DOC_rtx52_
 ---------------------------------------------------------------
 RTX Send Message
 ---------------------------------------------------------------
 @clib  RTX_Send_Msg | Send provided message to a specified message
        exchange. |
        <cfont>int RTX_Send_Msg ( unsigned int id, int prio,<nl>
        <tab><tab><tab><tab>&nbsp;&nbsp; const void far *msg );<efont> |
 @parm  int | id  | The message exchange ID output on
        call to <linkto>rtx50.htm<linkmid>RTX_Create_Msg<linktail>.
 @parm  int | prio  | Message priority (mailbox) 0 - 3 where 0 is
        highest priority
 @parm  int | msg  | Pointer to a 12 byte message to be sent
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  If one or more tasks are waiting at the exchange for a message,
        the message will be immediately given to the task waiting at the head
        of the exchange's wait queue.<s2>  A task switch occurs immediately if
        called for based on task priorities.<nl>
        <nl>
        The format of the 12 byte message being sent is defined by the application
        program.<nl>
        <nl>
        Messages will be reported in message priority order, and from each priority
        queue in FIFO order.<nl>
 @Also  rtx53.htm  |  RTX_Get_Msg        |
        rtx54.htm  |  RTX_Wait_For_Msg   |
        rtx54A.htm |  RTX_Wait_For_MsgP
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x52<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Send_Msg (unsigned int id, int prio, const void far * msg)
{
    _BX = id ;
    _CX = prio ;
    asm { LES   DI, msg } ;
    _AH = RTX_SEND_MSG ;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif



/*************************************************************************/
// Get a message from a message exchange, no wait
/*************************************************************************/
#ifdef _rtx53_
/*
 @doc DOC_rtx53_
 ---------------------------------------------------------------
 RTX Get Message
 ---------------------------------------------------------------
 @clib  RTX_Get_Msg | Get message without waiting (polling) from a
        specified message exchange. |
        <cfont>int RTX_Get_Msg ( unsigned int id, void far *msg );<efont> |
 @parm  int | id  | The message exchange ID output on
        call to <linkto>rtx50.htm<linkmid>RTX_Create_Msg<linktail>.
 @parm  int | msg  | Output parameter:<s2> Pointer to a 12 byte user
        buffer for storing the message (if any).
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  This function returns immediately with return value -28 if no
        message is available.<nl>
        <nl>
        The format of the 12 byte message being sent is defined by
        the application program.<nl>
        <nl>
        When more than one message is available at the message exchange, the
        oldest (FIFO order) message from the highest priority message
        queue will be reported.
 @Also  rtx52.htm  |  RTX_Send_Msg       |
        rtx54.htm  |  RTX_Wait_For_Msg   |
        rtx54A.htm |  RTX_Wait_For_MsgP
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x53<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Get_Msg (unsigned int id, void far * msg)
{
    _BX = id ;
    asm { LES   DI, msg } ;
    _AH = RTX_GET_MSG ;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif



/*************************************************************************/
// Wait for a message, optional timeout
/*************************************************************************/
#ifdef _rtx54_
/*
 @doc DOC_rtx54_
 ---------------------------------------------------------------
 RTX Wait for a message
 ---------------------------------------------------------------
 @clib  RTX_Wait_For_Msg | This function parks the calling task
        on the specified message exchange message queue.<s2> The Message
        Exchange Manager will then wake up this task when either a message
        is available or a specified wait period timeout expires. |
        <cfont>int RTX_Wait_For_Msg ( RTX_Wait_Msg far *msg_ptr );<efont> |
 @parm  int | msg_ptr  | Input parameter:<s2>  pointer to a
        <code>RTX_Wait_Msg<codee>
        <linkto>../../rtxstruc.htm#RTX_Wait_Msg<linkmid>structure<linktail>
        containing parameters.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code,
        invalid ID or -28: no message available.
 @comm  This procedure is identical to
        <linkto>rtx54A.htm<linkmid>RTX_Wait_For_MsgP<linktail>, except for
        method of parameter passing.<nl>
        <nl>
        The format of the 12 byte message received is defined by the
        application program.<nl>
        <nl>
        When more than one message is available at the message exchange, the
        oldest (FIFO order) message from the highest priority message
        queue will be reported.<s2> Note that message priority and the
        wait priority,<nl>
        <nl>
        <tab><code>msg_ptr-<gt>prio<codee>,<nl>
        <nl>
        are independent and unrelated concepts.
 @Also  rtx52.htm  |  RTX_Send_Msg |
        rtx53.htm  |  RTX_Get_Msg |
        rtx54A.htm |  RTX_Wait_For_MsgP
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x54<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Wait_For_Msg (const RTX_Wait_Msg far * msg_ptr)
{
    asm { LES   DI, msg_ptr } ;
    _AH = RTX_WAIT_MSG ;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif

/*************************************************************************/
// Wait for a message, optional timeout (Direct parameters method)
/*************************************************************************/
#ifdef _rtx54A_
/*
 @doc DOC_rtx54A_
 ---------------------------------------------------------------
 RTX Wait for a message (Alternate Method)
 ---------------------------------------------------------------
 @clib  RTX_Wait_For_MsgP | This function parks the calling task
        on the specified message exchange message queue.<s2> The Message
        Exchange Manager will then wake up this task when either a message
        is available or a specified wait period timeout expires. |
        <cfont>int RTX_Wait_For_MsgP ( unsigned int msgID, unsigned int prio,<nl>
        <tab><tab><tab><tab><tab><tab>void far *msg, long timeout );<efont> |
 @parm  int | msgID  | The message exchange ID output on
        call to <linkto>rtx50.htm<linkmid>RTX_Create_Msg<linktail>.
 @parm  int | msg  | Pointer to a 12 byte user buffer for storing the
        message (if any)
 @parm  int | timeout  | Maximum time (milliseconds) to wait for a message:<nl>
        timeout == 0  -<gt>  Wait forever<nl>
        timeout <lt> 0  -<gt>  invalid (must be <gt>= 0)
 @parm  int | prio  | priority for wait (0-0xFFFF),  0=highest.<s2> Specify here
        the priority of the calling task's access to the messages.<s2> To wait
        in FIFO order, have all callers use the same value here.<s2>  A task
        can cut in line ahead of other waiting tasks by setting this field
        to a higher priority (lower number) than used by the other tasks.
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code,
        invalid ID or -28: no message available.
 @comm  This procedure is identical to
        <linkto>rtx54.htm<linkmid>RTX_Wait_For_Msg<linktail>, except for
        method of parameter passing.<nl>
        <nl>
        The format of the 12 byte message received is defined by the
        application program.<nl>
        <nl>
        When more than one message is available at the message exchange, the
        oldest (FIFO order) message from the highest priority message
        queue will be reported.<s2> Note that message priority and the
        wait priority,<nl>
        <nl>
        <tab><code>msg_ptr-<gt>prio<codee>,<nl>
        <nl>
        are independent and unrelated concepts.
 @Also  rtx52.htm |  RTX_Send_Msg |
        rtx53.htm |  RTX_Get_Msg |
        rtx54.htm |  RTX_Wait_For_Msg
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x54<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Wait_For_MsgP (unsigned int msgID, unsigned int prio,
                       void far *msg, long timeout)
{
    _ES = _SS ;
    asm { LEA  DI,msgID } ;   // Now ES:DI = &msgID = &RTX_Wait_Msg struct.
    _AH = RTX_WAIT_MSG ;
    asm { int RTOSVECT  } ;
    return _AX ;                // return error code
}
#endif

/*************************************************************************/
// Find an message exchange, specified by 4 char name tag
/*************************************************************************/
#ifdef _rtx55_
/*
 @doc DOC_rtx55_
 ---------------------------------------------------------------
 RTX Find Message
 ---------------------------------------------------------------
 @clib  RTX_Find_Msg | Find a message exchange, specified by 4 character
        name tag. |
        <cfont>int RTX_Find_Msg ( unsigned int far *id_ptr,<nl>
        <tab><tab><tab><tab><s3>const char far *name);<efont> |
 @parm  int | id_ptr  | Output parameter, pointer to location in callers memory
        which will receive the Message exchange ID if a message exchange with
        specified name is found.
 @parm  int | name  | Input parameter, pointer to 4 character name of message
        exchange to look for.<s2> (This string need not be zero terminated,
        but must be four bytes.)
 @rdesc 0 on success else
        <linkto>../../rtxerrs.htm<linkmid>error<linktail> code.
 @comm  If more than one message exchange was created with the same tag,
        you will get back the message exchange ID of one with this tag, but
        which one is not certain.
 @Also  rtx50.htm |  RTX_Create_Msg | | | |
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x55<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int RTX_Find_Msg (unsigned int far * id_ptr, const char far * name)
{
    unsigned int the_id = 0 ;
    int error_code ;
    asm { LES   DI, name } ;
    _AH = RTX_FIND_MSG ;
    asm { int RTOSVECT  } ;
    error_code = _AX ;
    if (_DX == 0)
    {
        the_id = error_code ;       // Shuffle, ID was in _AX.
        error_code = 0 ;
    }
    *id_ptr = the_id ;
    return error_code ;
}
#endif

/*
 @doc DOC_rtxdyn02_
 ---------------------------------------------------------------
 Post global publication
 ---------------------------------------------------------------
 @clib  RTX_Publish | Post a tagged entry in the global data registry. |
        <cfont>int far RTX_Publish ( const void *data, const char *nameTag );<efont> |
 @parm  int | data  | Pointer to global data to store
         under provided name tag.<s2>
         Set to NULL to remove an existing entry by this name tag.<s2>
         Alternatively, the <code>SYSTEM_PUBLIC_OBJ(size)<codee> macro can be 
         used here to allocate a new global data object owned by the system (See below).
 @parm  int | nameTag  | A zero terminated ASCII string 
        (23 characters maximum length) to use as a unique identifier for 
        the data. 
 @rdesc Zero on success, else <linkto>../../rtxerrs.htm<linkmid>error<linktail> code:<nl>
        <nl><ul>
        <hangpara 20:30>
          RTX_EC_LOW_MEMORY  (-9) - <s2> Memory allocation failed. <paraend>
        <hangpara 20:30>
          RTX_EC_NAME_NOT_FOUND  (-57) - <s2>  An attempt to delete an entry 
          (i.e. data parameter was NULL) failed due to no entry with
          this name tag was found. <paraend>
        <hangpara 20:30>
          RTX_EC_CALL_ILLEGAL (-58) - <s2>  Illegal call made from inside an 
          <linkto>../HW/hal84A.htm<linkmid>ISR<linktail>.
        (This API may only be called at task level.) <paraend>
        <hangpara 20:30>
          RTX_EC_NAME_IN_USE  (-59) - <s2>  Attempt to install data
          failed due to that the provided name tag is already in use
          by some previously published data. <paraend>

 @comm  This API allows you to record a pointer that will be held inside
         the <chiprtos> with an associated name tag.<s2> This pointer can then 
         be <linkto>rtxdyn03.htm<linkmid>retrieved<linktail> by name from
         this registry by any program, thereby 
         providing a form of communication between programs.<nl>
         <nl>
        The <code>data<codee> parameter has been declared
        <code>const<codee> assuming other programs treat this object as
        read-only memory.<s2>  However programs are free to 
        cast the return value from 
        <linkto>rtxdyn03.htm<linkmid>RTX_GetPublication()<linktail>
        as they please.<nl>
        <nl>
        A named publication can later be removed by calling this API with
        the name of the item to be removed and a NULL <cfont>data<efont> 
        argument.<s2> When a task is
        <linkto>rtx03.htm<linkmid>deleted<linktail> from the system, 
        any global data entries which that task had installed will 
        automatically be removed from the registry unless that data entry
        was  installed using the <code>SYSTEM_PUBLIC_OBJ<codee> macro
        technique explained below under the heading "System Global Data".<nl>
        <nl>
        The name tag match is done in a case sensitive manner.<s2> The maximum
        name length is 23 characters, not counting the terminating zero.<s2> Any
        characters after this length will be ignored.<s2>
        The system makes a copy of the <code>nameTag<codee> string, so this string need
        not persist in your program after this API returns.<nl>
        <nl>
        The <linkto>../../command.htm#MEM<linkmid>MEM<linktail> console 
        command will list to the console the pointer, name tag
        and owner for each entry in the global data registry.<nl>
        <nl>
        <bold>System Global Data<bolde><nl>
        <nl>
        As mentioned above, when a task is removed from the system any 
        global data registry entries made by that task will be automatically 
        removed from the system's global data registry.<s2>  An exception to this
        rule is when the <bold><code>SYSTEM_PUBLIC_OBJ<codee><bolde> macro is
        used for the <code>data<codee> argument.<nl>
        <nl>
        In this case, the location of the global data object to be shared
        is not specified by the <code>data<codee> argument.<s2>  Instead, this
        argument specifies the size of an object which the system should
        allocate for this new shared data object.<s2>  The object's size may
        range up to 0xFFC0 bytes.<s2>  The size is passed to this API in the
        offset portion of the far <code>data<codee> pointer, as should be
        evident by inspecting the <code>SYSTEM_PUBLIC_OBJ<codee> macro.<s2>
        The segment portion of the <code>data<codee> far pointer must be zero
        in order to trigger an allocation of the new shared data object
        by this API.<nl>
        <nl>
        The usage of the <code>SYSTEM_PUBLIC_OBJ<codee> macro would look
        something like as follows:<nl>
        <nl><ul><code>
        void *shared_data = NULL ;<nl>
        if (RTX_Publish( SYSTEM_PUBLIC_OBJ( sizeof(struct MyStructType)), "MyName")<nl>
        <tab> == 0)<nl>
        {<nl>
        <tab> shared_data = (struct MyStructType *)<nl>
        <tab> <tab>  <tab> RTX_GetPublication( "MyName" ) ;<nl>
        }<nl>
        <codee><ule>
        <nl>
        This newly allocated object will be initialized to all zero bytes 
        by the system.<s2> A pointer to this new object will then be stored
        in the registry under the specified name.<s2> 
        The user will need to follow a successful call to this API with
        a call to <linkto>rtxdyn03.htm<linkmid>RTX_GetPublication()<linktail>
        to discover where the new tagged object resides.<nl>
        <nl>
        This new registry entry will be marked as owned by the system 
        (specifically, the MTSK task) instead of the calling task.<s2>
        This will cause the registry entry and its referenced object
        in the system heap memory to persists until it is explicitly
        removed by some application program using this API function 
        with a NULL <code>data<codee> argument, or a system reset.<nl>
        <nl>
        <bold>Peer to Peer Example:<bolde><nl>
        <nl>
        When two programs want to share data and it is not clear which 
        will be executing first, the while loop in example code below
        could be used to either install public data or retrieve the
        peer's public data for read/write access.<nl>
        <nl>
        This while loop in the example attempts to cover for race conditions
        where the peer program has made an exit between the 
        <code>RTX_Publish()<codee> attempt and the 
        <code>RTX_GetPublication()<codee> call.<s2> In this case both API's
        would fail on their first attempt.<s2> But note that the issue of programs
        closing after clients have gained access to their public data can
        still lead to problems.<s2> This would leave the client program with
        a reference to system memory which no longer is allocated (or has been
        reassigned to a subsequent program or system usage).<s2> Defining the
        shared objects with the <code>SYSTEM_PUBLIC_OBJ<codee> macro, as was
        discussed above is one way around this data persistence problem.<nl>
        <nl>
        <code>RTX_Publish()<codee> and 
        <linkto>rtxdyn03.htm<linkmid>RTX_GetPublication()<linktail> are
        fully reentrant, so only one program will win a race to post
        data under the same name.<nl>
        <nl>
   @raw
<code>
struct SharedDataT   // Only for an example
{
    int data ;  
    // ... and more user defined contents can go here ...
} ;

struct SharedDataT *negotiatePublics(struct SharedDataT *myData,
                                     const char         *nameTag)
{
    while(1)
    {
        RTX_EC error = RTX_Publish(myData, nameTag) ;
        if (error == 0)
        {
            break ;             // We got here first.
        }
        else if (error == RTX_EC_NAME_IN_USE)
        {
            // Our peer program has already published.
            struct SharedDataT *peerData = (struct SharedDataT *)
                RTX_GetPublication(nameTag) ;
            if (peerData != NULL)
            {
                myData = peerData ;
                break ;
            }
            // Reach here under race condition, peer removed their data.
            // Will loop for another go.
        }
        else 
        {
            printf("RTX_Publish() unepected error %d\r\n", error) ;
            myData = NULL ;     // Failure.
            break ;
        }
    }
    return myData ;
}
        <codee>

 @Also  rtxdyn03.htm |  RTX_GetPublication |
        rtx50.htm |  RTX_Create_Msg |
         |  
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt
        to install a dynamic link into the RTOS.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x27<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
*/

/*
 @doc DOC_rtxdyn03_
 ---------------------------------------------------------------
 Get global publication
 ---------------------------------------------------------------
 @clib  RTX_GetPublication | Get a tagged entry from the global data registry. |
        <cfont>const void far * far RTX_GetPublication(const char far *nameTag);<efont> |
 @parm  int | nameTag  | Name of the desired public data
         (zero terminated ASCII string). . 
 @rdesc NULL if not found, else a far data pointer stored under this 
        name by a <linkto>rtxdyn02.htm<linkmid>RTX_Publish()<linktail> call. 

 @comm  Data posted for global access (usually by some other program) 
        can be accessed by name tag with this API.<s2> The <chiprtos>
        maintains a registry of such tagged data that has been posted
        by application programs.<nl>
        <nl>
    The content of the object referenced by the far pointer 
    returned from this API is application defined.<nl>
    <nl>
    This API's return value is declared as a pointer to an 
    opaque read-only object (<code>const<codee>).<s2>  This can be cast to
    a non-constant object pointer when your design calls
    for read/write access to the registered global object by
    a client program.<nl>
    <nl>
    The name tag match is done in a case sensitive manner.<s2>
    Only up to 23 characters before a terminating NIL character
    are significant.<s2> Any following the first 23 characters 
    will be ignored (effective name truncated).<nl>


 @Also  rtxdyn02.htm |  RTX_Publish |
        rtx50.htm |  RTX_Create_Msg |
         |  
 @related RTX API<s2> | ../../rtxover.htm | Overview |
 @rtos  This library function invokes a RTOS software interrupt
        to install a dynamic link into the RTOS.
        Refer to this RTOS API function's
        <linkto>../../rtxapi.htm#0xAD0x27<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.35 | V1.35
*/


/*************************************************************************/
//end rtos.c
/*************************************************************************/

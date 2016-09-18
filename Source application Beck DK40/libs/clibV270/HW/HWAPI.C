/****************************************************************************
* (C) 1999-2007 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module    : HWAPI.C
* Function  : HW API library
* ---------------------------------------------------------------------------

$Header: HWAPI.C, 63, 12.11.2008 12:51:02, Andre Pribil$

*****************************************************************************/

/***************************************************************************/
// Includes
/***************************************************************************/
#include <dos.h>
#include <config.h>
#include "common.h"
#include "hwapi.h"
#include "hw_priv.h"

/*
 @doc DOC_INDEX
 ---------------------------------------------------------------
 Hardware API Table of Contents
 ---------------------------------------------------------------
 @clibidx  <tab><cfont>#include <InBraces HWAPI\.H><efont> |
    <tab><linkto>#PFE<linkmid>PFE<linktail><tab>
    <linkto>#HAL<linkmid>HAL<linktail><tab>
 
 Here are the API functions for access to the IPC@CHIP®'s hardware.
 
 @textlinkpara  Hardware API | ../../hdwlayer.htm | Layer  | Model
    
 @libcat1x  PFE | - Pin Function Enabler  | pfe80 |
    pfe_enable_bus | Enable data bus |
 @libcat1x  PFE | - Pin Function Enabler  | pfe81 |
    pfe_enable_adr | Enable non-multiplexed address bus |
 @libcat1x  PFE | - Pin Function Enabler  | pfe82 |
    pfe_enable_pio | Enable programmable I/O pins |
 @libcat1x  PFE | - Pin Function Enabler  | pfe82r |
    pfe_get_pio_state | Get programmable PIO pins state |
 @libcat1x  PFE | - Pin Function Enabler  | pfe82rA |
    pfe_get_pio_state2 | Get programmable PIO pins state (PIO16-31)|
 @libcat1x  PFE | - Pin Function Enabler  | pfe83 |
    pfe_enable_pcs | Enable programmable chip selects |
 @libcat1x  PFE | - Pin Function Enabler  | pfe84 |
    pfe_enable_int | Enable external interrupt requests |
 @libcat1x  PFE | - Pin Function Enabler  | pfe85 |
    pfe_enable_timer | Enable external timer inputs/outputs  |
 @libcat1x  PFE | - Pin Function Enabler  | pfe86 |
    pfe_set_edge_level_intr_mode | Set edge/level interrupt mode |
 @libcat1x  PFE | - Pin Function Enabler  | pfe87 |
    pfe_enable_pwd | Enable PWD mode |
 @libcat1x  PFE | - Pin Function Enabler  | pfe88 |
    pfe_enable_external_dma | Enable external DMA  |
 @libcat1x  PFE | - Pin Function Enabler  | pfe89 |
    pfe_enable_int_cascade_mode | Enable INT0/INTA cascade mode  |
 @libcat1x  PFE | - Pin Function Enabler  | pfe8A |
    pfe_set_wait_states | Set wait states for PCS0-3 |
 @libcat1x  PFE | - Pin Function Enabler  | pfe8B |
    pfe_set_wait_states2 | Set wait states for PCS5-6, respectively PCS4-7 |
 @libcat1x  PFE | - Pin Function Enabler  | pfe8C |
    pfe_set_wait_states_ucs | Set wait states for UCS |
 @libcat1x  PFE | - Pin Function Enabler  | pfe8D |
    pfe_enable_bus_signals | Enable bus signals (ARDY, HOLD, WRL/WRH, A0/BHE) |
 @libcat1x  PFE | - Pin Function Enabler  | pfe90 |
    pfe_get_vectors | Get Hardware API function pointers |


 @libcat2x  HAL | - Hardware Abstraction Layer  | hal80 |
        hal_read_bus | <nl><depr> Read data bus  | <tab>-- Data Bus I/O --<nl>
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal81 |
        hal_write_bus | <depr> Write data bus  |
 @libcat2x  HAL | - Hardware Abstraction Layer  | halA0 |
        hal_readblock_bus | <depr> Block read data bus |
 @libcat2x  HAL | - Hardware Abstraction Layer  | halA1 |
        hal_writeblock_bus | <depr> Block write data bus |


 @libcat2x  HAL | - Hardware Abstraction Layer  | hal82 |
        hal_read_pios | <nl>Read programmable I/O pins   | <tab>-- PIO --<nl>
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal82A |
        hal_read_pios2 | Read programmable I/O pins   |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal83 |
        hal_write_pios |  Write programmable I/O pins |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal83A |
        hal_write_pios2 |  Write programmable I/O pins |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal8C |
        hal_read_pio | Read specific I/O pin   |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal8D |
        hal_write_pio |  Write to specific I/O pin |


 @libcat2x  HAL | - Hardware Abstraction Layer  | hal84 |
        hal_install_isr | <nl>Install Interrupt Service Routine  | <tab>-- Interrupts --<nl>
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal84A |
        hal_install_rtx_isr | Install RTX Interrupt Service Routine  |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal8E |
        hal_give_eoi | Issue EOI to interrupt controller   |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal92 |
        hal_mask_int | Mask/Unmask Interrupts |


 @libcat2x  HAL | - Hardware Abstraction Layer  | hal85 |
        hal_init_timer | <nl>Initialize timer settings  |  <tab>-- Timer Operation --<nl>
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal8F |
        hal_init_timer_ext | Initialize timer settings Ext  |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal86 |
        hal_start_timer | Start timer  |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal87 |
        hal_stop_timer | Stop timer   |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal88 |
        hal_read_timer_count | Read timer count  |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal89 |
        hal_write_timer_count |Write timer count |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal8B |
        hal_set_duty_cycle_waveform | Set timer duty cycle waveform  |


 @libcat2x  HAL | - Hardware Abstraction Layer  | hal90 |
        hal_set_watchdog_mode | <nl>Get/Set watchdog mode  | <tab>-- Watchdog --<nl>
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal91 |
        hal_refresh_watchdog | Refresh watchdog  |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal94 |
        hal_watchdog_manager_sign_on | Sign on to watchdog manager  |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal95 |
        hal_watchdog_manager_refresh | Refresh watchdog manager  |
 @libcat2x  HAL | - Hardware Abstraction Layer  | hal96 |
        hal_watchdog_manager_sign_off | Sign off from watchdog manager  |


 @libcat2x  HAL | - Hardware Abstraction Layer  | halB0 |
        hal_start_dma | <nl>Start DMA mode  | <tab>-- DMA Control --<nl>
 @libcat2x  HAL | - Hardware Abstraction Layer  | halB1 |
        hal_stop_dma | Stop DMA transfer   |
 @libcat2x  HAL | - Hardware Abstraction Layer  | halB2 |
        hal_get_dma_info | Get DMA info    |


 @libcat2x  HAL | - Hardware Abstraction Layer  | halC0 |
        hal_init_non_volatile_data | <nl>Initialize/Restore non-volatile data  | <tab>-- Non-Volatile Data --<nl>
 @libcat2x  HAL | - Hardware Abstraction Layer  | halC1 |
        hal_save_non_volatile_data | Save non-volatile data    |
 @libcat2x  HAL | - Hardware Abstraction Layer  | halC2 |
        hal_get_reboot_reason | Get reboot reason  |
 @libcat2x  HAL | - Hardware Abstraction Layer  | halC3 |
        hal_install_pfaildone_callback | Install PowerfailDone callback |


 @libcat2x  HAL | - Hardware Abstraction Layer  | hal8A |
        hal_get_frequencies | <nl>Get frequencies  | <tab>-- other functions --<nl>

*/

/***************************************************************************/
// Enable bus
/***************************************************************************/
#ifdef _pfe80_
/*
 @doc DOC_pfe80_
 ---------------------------------------------------------------
 PFE Enable bus
 ---------------------------------------------------------------
 @clib  pfe_enable_bus |
        Initialize data bus I/O mask and ALE usage.
        The I/O mask defines which data bits on the bus are inputs and which
        are outputs. The mask bit for bi-directional data bus lines (read/write)
        should be set to '1'. |
        <cfont>
        void pfe_enable_bus ( unsigned short mask, unsigned char ale );
        <efont> |
 @parm_sc1x unsigned short | mask  | Data bus mask<nl>
         Bit 0 = 0: Data bus bit 0 is input, 1: is output<nl>
         Bit 1 = 0: Data bus bit 1 is input, 1: is output<nl>
         :<nl>
         :<nl>
         Bit 7 = 0: Data bus bit 7 is input, 1: is output<nl>
         Bit 8..15 not used (for future extensions)<ule>
 @parm_sc1x3 unsigned short | mask  | Data bus mask<nl>
         Bit 0 = 0: Data bus bit 0 is input, 1: is output<nl>
         Bit 1 = 0: Data bus bit 1 is input, 1: is output<nl>
         :<nl>
         :<nl>
         Bit 15 = 0: Data bus bit 15 is input, 1: is output<ule>
 @parm_sc1x  unsigned char | ale  | 0: Disable ALE,<s2> 1: Enable ALE
 @parm_sc1x3 unsigned char | ale  | Don't care
 @rdesc -- none --.
 @commtarget SC1x | Pins used:<nl>
            <tab>ALE, AD[0..7], RD#, WR#<nl>
        Excluded pins:<nl>
            <tab>if ALE is used, then PCS0# is not available.
 @commtarget SC1x3 | Pins used:<nl>
            <tab>A[0..22], D[0..15], RD#, WR#<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x80<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | n/a
*/
void pfe_enable_bus (unsigned short mask, unsigned char ale)
{
  // Enable bus mask
  asm mov ah, PFE_ENABLE_DATA_BUS
  asm mov al, ale
  asm mov dx, mask
  asm int PFE_INT
}
#endif

/***************************************************************************/
// Enable non multplexed address bus
/***************************************************************************/
#ifdef _pfe81_
/*
 @doc DOC_pfe81_
 ---------------------------------------------------------------
 PFE Enable non multiplexed address bus
 ---------------------------------------------------------------
 @clib  pfe_enable_adr |
        The IPC@CHIP&reg; has non-multiplexed address bit outputs,
        e.g. A0 on SC1x or A23 on SC1x3. The enabling of one of these pins is done here. |
        <cfont>void pfe_enable_adr ( unsigned char adr );<efont> |
 @parm_sc1x  unsigned char  | adr | 0:  Enables A0<nl>
                                           1:  Enables A1<nl>
                                           2:  Enables A2<nl>
 @parm_sc1x3 unsigned char  | adr | 23: Enables A23<nl>
 @rdesc  -- none --.
 @commtarget SC1x |  Used pins:<nl>
            <tab>A[0..2], AD[0..7], RD#, WR#<nl>
        Excluded pins:<nl>
            <tab>If A0 is enabled then PCS1#, TMRIN0, PIO4 are not available<nl>
            <tab>If A1 is enabled then PCS[5..6]#, TMRIN1, TMROUT1,
            PIO3 are not available<nl>
            <tab>If A2 is enabled then PCS[5..6]#, PIO2 are not available.<nl>
 @commtarget SC1x3 |  Used pins:<nl>
            <tab>A23<nl>
        Excluded pins:<nl>
            <tab>If A23 is enabled then PIO26 is not available<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x81<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | n/a
*/
#undef pfe_enable_adr // Maintain original name

void pfe_enable_adr (unsigned char adr)
{
  //enable non multiplexed io-bus
  asm mov cl, adr
  asm mov dx, 1
  asm shl dx, cl    ;//dx = 1<<adr
  asm mov ah, PFE_ENABLE_NON_MULTI_ADDR_BUS;
  asm int PFE_INT
}
#endif

#ifdef _pfe81e_
void pfe_enable_adr_sc123 (unsigned char adr)
{
  //enable non multiplexed io-bus
  if (adr!=23) return;
  asm mov dx, 0x8000
  asm mov ah, PFE_ENABLE_NON_MULTI_ADDR_BUS;
  asm int PFE_INT
}
#endif


/***************************************************************************/
// Enable programmable pio pins
/***************************************************************************/
#ifdef _pfe82_
/*
 @doc DOC_pfe82_
 ---------------------------------------------------------------
 PFE Enable programmable pio pins
 ---------------------------------------------------------------
 @clib  pfe_enable_pio |
        Enable used programmable I/O pins. Define which pins are
        inputs and which are outputs. This function can be called
        several times for definition of different PIO pins.
        With repeated selection of the same pin, the definition made
        last is valid. The selection of a PIO pin can be cancelled
        by calling the appropriate PFE function that causes the
        respective PIO pin to be used for another purpose (e.g. function
        <linkto>pfe83.htm<linkmid>pfe_enable_pcs<linktail> for PIO2). |
        <cfont>void pfe_enable_pio ( unsigned short pio,
                                     unsigned char  mode );<efont> |
 @parm_sc1x  unsigned short  | pio  | PIO pin number, [0..13]
 @parm_sc1x3 unsigned short  | pio  | PIO pin number, [0..24, 26..31]
 @parm_sc2x  unsigned short  | pio  | PIO pin number, [0..2, 9..13, 18..23, 27..28, 31]
 @parm_sc1x  unsigned char   | mode | Mode<ul>
         1 = Input without pullup/pulldown<nl>
         2 = Input with pullup (not PIO13)<nl>
         3 = Input with pulldown (only for PIO3 and PIO13)<nl>
         4 = Output init value = High<nl>
         5 = Output init value = Low<ule>
 @parm_sc1x3 unsigned char   | mode | Mode<ul>
         1,2 = Input with pullup<nl>
         4 = Output init value = High<nl>
         5 = Output init value = Low<ule>
 @parm_sc2x unsigned char   | mode | Mode<ul>
         1,2,3 = Input with pullup/down (PIO1/PIO2=pulldown, all other=pullup)<nl>
         4 = Output init value = High<nl>
         5 = Output init value = Low<ule>
 @rdesc  -- none --.
 @comm Used pins:<nl>
            <tab>PIO[0..x]<nl>
        Excluded pins:<nl>
            <tab>All other functionality on the selected PIO pin.
 @Also  hal8C.htm |  hal_read_pio |
        hal8D.htm |  hal_write_pio |
        ../I2C/i2c80.htm |  I2C_init
 @Also  hal82.htm |  hal_read_pios  |
        hal83.htm |  hal_write_pios |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x82<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
#undef pfe_enable_pio // Maintain original name

void pfe_enable_pio (unsigned short pio, unsigned char mode)
{
  pio = 1 << pio;

  // Enable programmable pios
  asm mov ah, PFE_ENABLE_PIO;
  asm mov al, mode
  asm mov dx, pio
  asm int PFE_INT
}
#endif

#ifdef _pfe82e_
void pfe_enable_pio_sc123 (unsigned short pio, unsigned char mode)
{
  if (pio>15)
  {
    pio -= 16;
    mode +=10;
  }

  pio = 1 << pio;

  // Enable programmable pios
  asm mov ah, PFE_ENABLE_PIO;
  asm mov al, mode
  asm mov dx, pio
  asm int PFE_INT
}
#endif


/***************************************************************************/
// Get programmable pio pins state
/***************************************************************************/
#ifdef _pfe82r_
/*
 @doc DOC_pfe82r_
 ---------------------------------------------------------------
 PFE get pio state
 ---------------------------------------------------------------
 @clib  pfe_get_pio_state | Get programmable PIO pins state. |
        <cfont>void pfe_get_pio_state ( unsigned int far * wPio,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned int far * wInp,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned int far * wOut );<efont> |
 @parm_sc1x unsigned int far * | wPio  | Output parameter:<ul>
         Bit 0 = 1: PIO0 is PIO<nl>
         Bit 1 = 1: PIO1 is PIO<nl>
         :<nl>
         Bit 13 = 1: PIO13 is PIO<nl>
         Bit 14..15 not used (for future extensions)<nl><ule>
 @parm_sc1x3 unsigned int far * | wPio  | Output parameter:<ul>
         Bit 0 = 1: PIO0 is PIO<nl>
         Bit 1 = 1: PIO1 is PIO<nl>
         :<nl>
         :<nl>
         Bit 15 = 1: PIO15 is PIO<nl><ule>
 @parm_sc2x unsigned int far * | wPio  | Output parameter:<ul>
         Bit 0 = 1: PIO0 is PIO<nl>
         Bit 1 = 1: PIO1 is PIO<nl>
         Bit 2 = 1: PIO2 is PIO<nl>
         Bit 9 = 1: PIO9 is PIO<nl>
         Bit 10 = 1: PIO10 is PIO<nl>
         Bit 11 = 1: PIO11 is PIO<nl>
         Bit 12 = 1: PIO12 is PIO<nl>
         Bit 13 = 1: PIO13 is PIO<nl><ule>

 @parm_sc1x unsigned int far * | wInp  | Output parameter:<ul>
          Bit 0 = 1: PIO0 is input<nl>
          Bit 1 = 1: PIO1 is input<nl>
          :<nl>
          Bit 13 = 1: PIO13 is input<nl>
          Bit 14..15 not used (for future extensions)<nl><ule>
 @parm_sc1x3 unsigned int far * | wInp  | Output parameter:<ul>
          Bit 0 = 1: PIO0 is input<nl>
          Bit 1 = 1: PIO1 is input<nl>
          :<nl>
          Bit 15 = 1: PIO15 is input<nl><ule>
 @parm_sc2x unsigned int far * | wInp  | Output parameter:<ul>
          Bit 0 = 1: PIO0 is input<nl>
          Bit 1 = 1: PIO1 is input<nl>
          Bit 2 = 1: PIO2 is input<nl>
          Bit 9 = 1: PIO9 is input<nl>
          Bit 10 = 1: PIO10 is input<nl>
          Bit 11 = 1: PIO11 is input<nl>
          Bit 12 = 1: PIO12 is input<nl>
          Bit 13 = 1: PIO13 is input<nl><ule>

 @parm_sc1x unsigned int far *  | wOut  | Output parameter:<ul>
          Bit 0 = 1: PIO0 is output<nl>
          Bit 1 = 1: PIO1 is output<nl>
          :<nl>
          Bit 13 = 1: PIO13 is output<nl>
          Bit 14..15 not used (for future extensions)<nl><ule>
 @parm_sc1x3 unsigned int far *  | wOut  | Output parameter:<ul>
          Bit 0 = 1: PIO0 is output<nl>
          Bit 1 = 1: PIO1 is output<nl>
          :<nl>
          Bit 15 = 1: PIO15 is output<nl><ule>
 @parm_sc2x unsigned int far *  | wOut  | Output parameter:<ul>
          Bit 0 = 1: PIO0 is output<nl>
          Bit 1 = 1: PIO1 is output<nl>
          Bit 2 = 1: PIO2 is output<nl>
          Bit 9 = 1: PIO9 is output<nl>
          Bit 10 = 1: PIO10 is output<nl>
          Bit 11 = 1: PIO11 is output<nl>
          Bit 12 = 1: PIO12 is output<nl>
          Bit 13 = 1: PIO13 is output<nl><ule>

 @rdesc  -- none --.
 @comm  The value output to <code>wPio<codee> has bits set to one to indicate
        PIO is configured as an I/O pin.<nl>
        <nl>
        The value output to <code>wInp<codee> has bits set to one to indicate
        PIO which are configured as inputs.<nl>
        <nl>
        The value output to <code>wOut<codee> has bits set to one to indicate
        PIO which are configured as outputs.<nl>
 @Also  hal8C.htm |  hal_read_pio |
        hal8D.htm |  hal_write_pio | |
 @Also  hal8C.htm |  hal_read_pio |
        hal8D.htm |  hal_write_pio |
        pfe82rA.htm | pfe_get_pio_state2
 @Also  hal82.htm |  hal_read_pios  |
        hal83.htm |  hal_write_pios | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x82<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void pfe_get_pio_state (unsigned int far *wPio,
                        unsigned int far *wInp,
                        unsigned int far *wOut)
{
  unsigned short p, i, o;

  asm mov ah, PFE_ENABLE_PIO;
  asm mov al, 0
  asm int PFE_INT
  asm mov p, AX
  asm mov i, dx
  asm mov o, CX

  *wPio = p;
  *wInp = i & p ;
  *wOut = o & p ;
}
#endif

/***************************************************************************/
// Get programmable pio pins state (PIO16-31)
/***************************************************************************/
#ifdef _pfe82rA_
/*
 @doc DOC_pfe82rA_
 ---------------------------------------------------------------
 PFE get pio state (PIO16-31)
 ---------------------------------------------------------------
 @clib  pfe_get_pio_state2 | Get programmable PIO pins state (PIOs 16-31). |
        <cfont>void pfe_get_pio_state2 ( unsigned int far * wPio,<nl>
        <tab><tab><tab><tab><tab><tab><s2>unsigned int far * wInp,<nl>
        <tab><tab><tab><tab><tab><tab><s2>unsigned int far * wOut );<efont> |
 @parm_sc1x3  unsigned int far * | wPio  | Output parameter:<ul>
         Bit 0 = 1: PIO16 is PIO<nl>
         Bit 1 = 1: PIO17 is PIO<nl>
         :<nl>
         Bit 15 = 1: PIO31 is PIO<nl><ule>
 @parm_sc2x  unsigned int far * | wPio  | Output parameter:<ul>
         Bit 2 = 1: PIO18 is PIO<nl>
         Bit 3 = 1: PIO19 is PIO<nl>
         Bit 4 = 1: PIO20 is PIO<nl>
         Bit 5 = 1: PIO21 is PIO<nl>
         Bit 6 = 1: PIO22 is PIO<nl>
         Bit 7 = 1: PIO23 is PIO<nl>
         Bit 11 = 1: PIO27 is PIO<nl>
         Bit 12 = 1: PIO28 is PIO<nl>
         Bit 15 = 1: PIO31 is PIO<nl><ule>

 @parm_sc1x3  unsigned int far * | wInp  | Output parameter:<ul>
          Bit 0 = 1: PIO16 is input<nl>
          Bit 1 = 1: PIO17 is input<nl>
          :<nl>
          Bit 15 = 1: PIO31 is input<nl><ule>
 @parm_sc2x  unsigned int far * | wInp  | Output parameter:<ul>
          Bit 2 = 1: PIO18 is input<nl>
          Bit 3 = 1: PIO19 is input<nl>
          Bit 4 = 1: PIO20 is input<nl>
          Bit 5 = 1: PIO21 is input<nl>
          Bit 6 = 1: PIO22 is input<nl>
          Bit 7 = 1: PIO23 is input<nl>
          Bit 11 = 1: PIO27 is input<nl>
          Bit 12 = 1: PIO28 is input<nl>
          Bit 15 = 1: PIO31 is input<nl><ule>

 @parm_sc1x3  unsigned int far *  | wOut  | Output parameter:<ul>
          Bit 0 = 1: PIO16 is output<nl>
          Bit 1 = 1: PIO17 is output<nl>
          :<nl>
          Bit 15 = 1: PIO31 is output<nl><ule>
 @parm_sc2x  unsigned int far *  | wOut  | Output parameter:<ul>
          Bit 2 = 1: PIO18 is output<nl>
          Bit 3 = 1: PIO19 is output<nl>
          Bit 4 = 1: PIO20 is output<nl>
          Bit 5 = 1: PIO21 is output<nl>
          Bit 6 = 1: PIO22 is output<nl>
          Bit 7 = 1: PIO23 is output<nl>
          Bit 11 = 1: PIO27 is output<nl>
          Bit 12 = 1: PIO28 is output<nl>
          Bit 15 = 1: PIO31 is output<nl><ule>

 @rdesc  -- none --.
 @comm  The value output to <code>wPio<codee> has bits set to one to indicate
        PIO is configured as an I/O pin.<nl>
        <nl>
        The value output to <code>wInp<codee> has bits set to one to indicate
        PIO which are configured as inputs.<nl>
        <nl>
        The value output to <code>wOut<codee> has bits set to one to indicate
        PIO which are configured as outputs.<nl>
 @Also  hal8C.htm |  hal_read_pio |
        hal8D.htm |  hal_write_pio |
        pfe82r.htm | pfe_get_pio_state
 @Also  hal82.htm |  hal_read_pios  |
        hal83.htm |  hal_write_pios | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x82<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00
*/
void pfe_get_pio_state2 (unsigned int far *wPio,
                         unsigned int far *wInp,
                         unsigned int far *wOut)
{
  unsigned short p, i, o;

  asm mov ah, PFE_ENABLE_PIO;
  asm mov al, 10
  asm int PFE_INT
  asm mov p, AX
  asm mov i, dx
  asm mov o, CX

  *wPio = p;
  *wInp = i & p ;
  *wOut = o & p ;
}
#endif

/***************************************************************************/
// Enable programmable chip selects
/***************************************************************************/
#ifdef _pfe83_
/*
 @doc DOC_pfe83_
 ---------------------------------------------------------------
 PFE Enable Programmable Chip Selects
 ---------------------------------------------------------------
 @clib  pfe_enable_pcs | Enable chip selects PCSx# |
        <cfont>void pfe_enable_pcs ( unsigned char pcs );<efont> |
 @parm_sc1x unsigned char | pcs | Chip select number:<ul>
            0: Enable PCS0#, active when I/O address between 000h..0FFh<nl>
            1: Enable PCS1#, active when I/O address between 100h..1FFh<nl>
            2: Enable PCS2#, active when I/O address between 200h..2FFh<nl>
            3: Enable PCS3#, active when I/O address between 300h..3FFh<nl>
            4:  N/A<nl>
            5: Enable PCS5#, active when I/O address between 500h..5FFh<nl>
            6: Enable PCS6#, active when I/O address between 600h..6FFh<nl>
            <ule>
 @parm_sc1x3 unsigned char | pcs | Chip select number:<ul>
            0: don't care (PCS0# is no PIO), PCS0# is active when I/O address between 000h..1FFh<nl>
            1: don't care (PCS1# is no PIO), PCS1# is active when I/O address between 200h..3FFh<nl>
            2: don't care (PCS2# is no PIO), PCS2# is active when I/O address between 400h..5FFh<nl>
            3: don't care (PCS3# is no PIO), PCS3# is active when I/O address between 600h..7FFh<nl>
            4: Enable PCS4#, active when I/O address between 800h..9FFh<nl>
            5: Enable PCS5#, active when I/O address between A00h..BFFh<nl>
            6: Enable PCS6#, active when I/O address between C00h..DFFh<nl>
            7: Enable PCS7#, active when I/O address between E00h..FFFh<nl>
            <ule>
 @rdesc   -- none --.
 @commtarget SC1x | Used pins:<nl>
            <tab>PCS[0..3]#, PCS[5..6]#<nl>
        Excluded pins:<nl>
            <tab>if PCS0#: ALE (multiplexed address / data bus)<nl>
            <tab>if PCS1#: A0, PIO4, TMRIN0, SPI<nl>
            <tab>if PCS2#: PIO6, INT2, INTA#, PWD, SPI, hw flow control serial port 1,<nl>
            <tab><tab>cascaded interrupt controller<nl>
            <tab>if PCS3#: PIO5, INT4, SPI, hw flow control serial port 1<nl>
            <tab>if PCS5#: A[1..2], PIO3, TMROUT1, TMRIN1<nl>
            <tab>if PCS6#: A[1..2], PIO2
 @commtarget SC1x3 | Used pins:<nl>
            <tab>PCS[0..7]#<nl><nl>
        Excluded pins:<nl>
            <tab>If PCS4#: PIO4<nl>
            <tab>If PCS5#: PIO3<nl>
            <tab>If PCS6#: PIO2<nl>
            <tab>If PCS7#: PIO5
 @Also  pfe8A.htm |  pfe_set_wait_states |  |  |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x83<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | n/a
*/
void pfe_enable_pcs (unsigned char pcs)
{
  // Enable programmable chip selects
  asm mov ah, PFE_ENABLE_PCS;
  asm mov dx, 1
  asm mov cl, pcs
  asm shl dx, cl    ;//dx = 1<<pcs
  asm int PFE_INT
}
#endif

/***************************************************************************/
// Enable interrupts
/***************************************************************************/
#ifdef _pfe84_
/*
 @doc DOC_pfe84_
 ---------------------------------------------------------------
 PFE Enable interrupts
 ---------------------------------------------------------------
 @clib  pfe_enable_int | Enable external interrupt requests INTx |
        <cfont>void pfe_enable_int ( unsigned char irq );<efont>  |
 @parm_sc1x unsigned char | irq  | External Interrupt number:<ul>
          0:<s2> Enable INT0<nl>
          1:<s2> N/A<nl>
          2:<s2> Enable INT2<nl>
          3:<s2> Enable INT3<nl>
          4:<s2> Enable INT4<nl>
          5:<s2> Enable INT5<nl>
          6:<s2> Enable INT6<nl><ule>
 @parm_sc1x3_sc2x unsigned char | irq  | External Interrupt number:<ul>
          0:<s2> N/A<nl>
          1:<s2> Enable INT1<nl>
          2:<s2> N/A<nl>
          3:<s2> Enable INT3<nl>
          4:<s2> N/A<nl>
          5:<s2> Enable INT5<nl>
          6-14:<s2> N/A<nl>
          15:<s2> Enable PFI<nl><ule>
 @rdesc  -- none --.
 @commtarget SC1x | Used pins:<nl>
            <tab>INT0, INT[2..6]<nl>
            <nl>
        Excluded pins:<nl>
            <tab>if INT0:<s2> PIO13, TMROUT0, cascaded interrupt controller<nl>
            <tab>if INT2:<s2> PIO6, PCS2#, INTA#, PWD, SPI, hw flow control serial port 1<nl>
            <tab>if INT3:<s2> PIO12, serial port 1<nl>
            <tab>if INT4:<s2> PIO5, PCS3#, SPI, hw flow control serial port 1<nl>
            <tab>if INT5:<s2> PIO1, DRQ0, default I2C-Bus pins, SPI<nl>
            <tab>if INT6:<s2> PIO0, DRQ1, default I2C-Bus pins, SPI
 @commtarget SC1x3 | Used pins:<nl>
            <tab>INT1, INT3, INT5, PFI<nl>
            <nl>
        Excluded pins:<nl>
            <tab>if INT5: PIO30<nl>
            <tab>if PFI: PIO9
 @commtarget SC2x | Used pins:<nl>
            <tab>INT1, INT3, INT5, PFI<nl>
            <nl>
        Excluded pins:<nl>
            <tab>if INT5: PIO0 / TMRIN1<nl>
            <tab>if INT3: PIO1 / TMROUT1<nl>
            <tab>if INT1: PIO2<nl>
            <tab>if PFI: PIO9<nl>

 @Also  pfe86.htm  | pfe_set_edge_level_intr_mode |
        hal84.htm  | hal_install_isr |
        hal84A.htm | hal_install_rtx_isr

  
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x84<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void pfe_enable_int (unsigned char irq)
{
  // Enable interrupts
  asm mov ah, PFE_ENABLE_EXTERNAL_IRQ;
  asm mov dx, 1
  asm mov cl, irq
  asm shl dx, cl    ;//dx= 1<<irq
  asm int PFE_INT
}
#endif

/***************************************************************************/
// Enable timer
/***************************************************************************/
#ifdef _pfe85_
/*
 @doc DOC_pfe85_
 ---------------------------------------------------------------
 PFE Enable timer
 ---------------------------------------------------------------
 @clib  pfe_enable_timer |
        Enable external timer inputs (TMRIN0, TMRIN1) or timer outputs
        (TMROUT0, TMROUT1).<s2> If on a given timer the external input is selected,
        then that timer's external output is not available and vice-versa. |
        <cfont>void pfe_enable_timer ( unsigned short mode );<efont> |
 @parm unsigned short | mode | Mode<ul><code>
        Bit 0..1<s1> = 10 Enable TMRIN0<nl>
            <tab8><s1>  = 11 Enable TMROUT0<nl>
        Bit 2..3<s1> = 10 Enable TMRIN1<nl>
            <tab8><s1>  = 11 Enable TMROUT1<nl>
        Bit 4..15 = don't care<codee><ule>
 @rdesc   -- none --.
 @comm Used pins:<ul>
            TMRIN[0..1], TMROUT[0..1]<ule>
 @commtarget SC1x |
        Excluded pins:<ul>
            if TMRIN0: <s2>A0, PCS1#, PIO4, TMROUT0<nl>
            if TMRIN1: <s2>A[1..2], PCS5#, TMROUT1<nl>
            if TMROUT0: <s2>PIO13, INT0, cascaded interrupt controller, TMRIN0<nl>
            if TMROUT1: <s2>A[1..2], PCS5#, TMRIN1, PIO3<ule>
 @commtarget SC1x3 |
        Excluded pins:<ul>
            if TMRIN0: <s2>PIO11<nl>
            if TMRIN1: <s2>PIO0<nl>
            if TMROUT0: <s2>PIO10<nl>
            if TMROUT1: <s2>PIO1<ule>
 @commtarget SC2x |
        Excluded pins:<ul>
            if TMRIN0: <s2>PIO11<nl>
            if TMRIN1: <s2>PIO0 / INT5<nl>
            if TMROUT0: <s2>PIO10<nl>
            if TMROUT1: <s2>PIO1 / INT3<ule>

 @Also  hal85.htm |  hal_init_timer |  |  |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x85<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void pfe_enable_timer (unsigned short mode)
{
  // Enable timer
  asm mov ah, PFE_ENABLE_EXTERNAL_TIMER;
  asm mov dx, mode
  asm int PFE_INT
}
#endif

/***************************************************************************/
// Set Edge Level Interrupt Mode
/***************************************************************************/
#ifdef _pfe86_
/*
 @doc DOC_pfe86_
 ---------------------------------------------------------------
 PFE Set Edge Level Interrupt Mode
 ---------------------------------------------------------------
 @clib  pfe_set_edge_level_intr_mode |
        Set edge/level interrupt mode for INTx. |
        <cfont>void pfe_set_edge_level_intr_mode ( unsigned char mode,<nl>
        <tab><tab><tab><tab><tab><tab><tab><tab><tab>unsigned short mask );<efont> |
 @parm   unsigned char | mode  | 1 = level-sensitive interrupt<nl>
                                 0 = edge-triggered interrupt
 @parm_sc1x unsigned short | mask  | Bits set to designate interrupts affected:<ul>
                     Bit 0 = INT0<nl>
                     Bit 1 = don't care<nl>
                     Bit 2 = INT2<nl>
                     Bit 3 = INT3<nl>
                     Bit 4 = INT4<nl>
                     Bit 5..15 = don't care<ule>
 @parm_sc1x3_sc2x unsigned short | mask  | Bits set to designate interrupts affected:<ul>
                     Bit 0 = don't care<nl>
                     Bit 1 = INT1<nl>
                     Bit 2 = don't care<nl>
                     Bit 3 = INT3<nl>
                     Bit 4 = don't care<nl>
                     Bit 5 = INT5#<nl>
                     Bit 6..15 = don't care<ule>
 @rdesc   -- none --.
 @commtarget SC1x | Default for all interrupts is edge-triggered mode.<s2>
        In each case (edge or level) the interrupt pins must remain high
        until they are acknowledged.<nl><nl>
        Level-sensitive mode for INT5 / INT6 is not supported.<s2>The INT5 / INT6
        interrupts operate only in edge-triggered mode.<nl>
        <nl>
        In level-sensitive mode all interrupt lines are active high.<nl>
        In edge-triggered mode all interrupt lines act on the low-to-high transition.
 @commtarget SC1x3/SC2x | Default for INT3 interrupt is level-triggered mode.<s2>
        Default for INT1 and INT5# interrupts is edge-triggered mode.<s2>
        In each case (edge or level) the interrupt pins must remain active
        until they are acknowledged.<nl><nl>
        Edge-sensitive mode for INT3 is not allowed if the USB controller is used,
        because the INT3 interrupt is shared with the USB interrupt.<nl>
        <nl>
        In level-sensitive mode all interrupt lines except INT5# are active high.
        INT5# is active low.<nl>
        In edge-triggered mode all interrupt lines except INT5# act on the low-to-high transition.
        INT5# acts on the high-to-low transition.
 @Also  pfe84.htm |  pfe_enable_int |   |   |   |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x86<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void pfe_set_edge_level_intr_mode(unsigned char mode, unsigned short mask)
{
  // set edge level interrupt mode
  asm mov ah, PFE_SET_EDGE_LEVEL_INTR_MODE;
  asm mov al, mode
  asm mov dx, mask
  asm int PFE_INT
}
#endif


/***************************************************************************/
// Enable Pwd Mode
/***************************************************************************/
#ifdef _pfe87_
/*
 @doc DOC_pfe87_
 ---------------------------------------------------------------
 PFE Enable Pwd Mode
 ---------------------------------------------------------------
 @clib  pfe_enable_pwd | Enable Pulse Width Demodulation (PWD) |
        <cfont>void pfe_enable_pwd ( void );<efont> |
 @parm   void  |   | -- none --
 @rdesc   -- none --.
 @comm  In PWD mode, TMRIN0, TMRIN1, INT2 and INT4 are configured internal to the
        chip to support the detection of rising (INT2) and falling (INT4) edges on the PWD
        input pin and to enable either TIMER0 when the signal is high or TIMER1 when
        the signal is low.<s2> The INT4, TMRIN0 and TMRIN1 pins are not used in PWD mode
        and so are available for use as PIO's.<nl>
        <nl>
        The ISR for the INT2 and the INT4 interrupts should examine the current count of
        the associated timer, TIMER1 for INT2 and TIMER0 for INT4, in order to determinate
        the pulse width.<s2> The ISR should then reset the timer count in preparation for the
        next pulse.<nl>
        <nl>
        Overflow conditions, where the pulse width is greater than the maximum count of the
        timer, can be detected by monitoring the MaxCount bit in the associated timer or by
        setting the timer to generated interrupt requests.<nl>
        <nl>
        Used pins:<nl>
        <tab>PWD<nl>
        <nl>
        Excluded pins:<nl>
        <tab>TMRIN0, TMRIN1, TMROUT0, TMROUT1, INT4, INT2<nl>
        <tab>PCS2#, INTA#, PIO6, hw flow control serial port 1
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x87<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | n/a   | n/a
*/
void pfe_enable_pwd(void)
{
  // enable pwd
  asm mov ah, PFE_ENABLE_PWD;
  asm int PFE_INT
}
#endif

/***************************************************************************/
// Enable External Dma
/***************************************************************************/
#ifdef _pfe88_
/*
 @doc DOC_pfe88_
 ---------------------------------------------------------------
 PFE Enable External DMA
 ---------------------------------------------------------------
 @clib  pfe_enable_external_dma | Enables DRQ pin to start DMA transfer. |
        <cfont>int pfe_enable_external_dma ( unsigned char  channel );<efont> |
 @parm_sc1x  unsigned char | channel | DRQ channel:<nl>
         0 = DRQ0<nl>
         1 = DRQ1<nl>
 @parm_sc1x3 unsigned char | channel | DRQ channel:<nl>
         0 = DRQ0<nl>
         1 = DRQ1<nl>
         2 = DRQ2<nl>
         3 = DRQ3<nl>
 @rdesc 0:<s2> no error<nl>
       -1:<s2> invalid DRQ channel<nl>
       -2:<s2> DMA channel is used for serial interface<nl>
 @comm  For using external DMA you have to disable the serial DMA mode.<s2> Do this with
        a <linkto>../../config.htm#SERIAL_EXT_DMA<linkmid>CHIP.INI entry<linktail>.<s2>
        COM uses DRQ1, EXT uses DRQ0.<nl>
 @commtarget SC1x | Used pins:<ul>
            DRQ[0..1]<ule>
            <nl>
        Excluded pins:<ul>
            If DRQ0: PIO1, INT5, default I²C-Bus pins, SPI<nl>
            If DRQ1: PIO0, INT6, default I²C-Bus pins, SPI<ule>
 @commtarget SC1x3 | Used pins:<ul>
            DRQ[0..3]<ule><nl>
        Excluded pins:<ul>
            If DRQ0: PIO12<nl>
            If DRQ1: PIO29<nl>
            If DRQ2: PIO7<nl>
            If DRQ3: PIO8<ule>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x88<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | n/a
*/
int pfe_enable_external_dma( unsigned char channel)
{
  // enable pwd
  asm mov ah, PFE_ENABLE_EXTERNAL_DMA;
  asm mov al, channel
  asm int PFE_INT
  return _AX ;
}
#endif


/***************************************************************************/
// Enable INT0/INTA cascade mode
/***************************************************************************/
#ifdef _pfe89_
/*
 @doc DOC_pfe89_
 ---------------------------------------------------------------
 PFE: Enable INT0/INTA cascade mode
 ---------------------------------------------------------------
 @clib  pfe_enable_int_cascade_mode | Enable INT0 / INTA cascade mode |
        <cfont>void pfe_enable_int_cascade_mode ( void );<efont> |
 @parm   void  |   | -- none --
 @rdesc   -- none --.
 @comm
        To install a service interrupt routine in cascade mode, the
        <linkto>hal84.htm<linkmid>hal_install_isr<linktail> function can not be
        used, because
        the cascaded interrupt controller supply the interrupt type over the bus.
        Install a normal interrupt routine with <code>setvect<codee> for the
        vector you use and at the end of this function give an EOI to the
        cascaded controller and to
        the internal interrupt controller with
        <linkto>hal8E.htm<linkmid>hal_give_eoi<linktail> (INT0).<nl>
        <nl>
        Used pins:<nl>
            <tab>INT0, INTA#<nl>
            <nl>
        Excluded pins:<nl>
            <tab>PIO13, TMROUT0, INT0 in normal mode, PIO6, PCS2#, PWD, SPI,
            hw flow control serial port 1<nl>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x89<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | n/a   | n/a
*/
void pfe_enable_int_cascade_mode(void)
{
  // enable int0/inta cascade mode
  asm mov ah, PFE_ENABLE_INT_CASCADE_MODE;
  asm int PFE_INT
}
#endif

/***************************************************************************/
// Set wait states for PCS0-3
/***************************************************************************/
#ifdef _pfe8A_
/*
  For The DOCLIST.EXE tool --> BeckCLib.LST

 #DOCLIST:PFE_WAIT_STATES   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_0_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_1_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_3_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_5_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_6_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_9_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_15_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_24_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_41_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_74_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_123_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_157_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_175_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_201_WAIT   CLIB\HW\pfe8A.htm
 #DOCLIST:PFE_255_WAIT   CLIB\HW\pfe8A.htm

 @doc DOC_pfe8A_
 ---------------------------------------------------------------
 PFE: Set wait states for PCS0-3
 ---------------------------------------------------------------
 @clib  pfe_set_wait_states |
        Set wait states for programmable chip selects PCS0#-PCS3# |
        <cfont>void pfe_set_wait_states ( PFE_WAIT_STATES wait_states );<efont> |
 @parm_sc11_sc13 int  | wait_states  | Enumerator specifies desired number of wait states:<nl>
   <nl>
   <code>typedef enum {<ul>
    PFE_0_WAIT = 0x0,<nl>
    PFE_1_WAIT = 0x1,<nl>
    PFE_2_WAIT = 0x2,<nl>
    PFE_3_WAIT = 0x3,<nl>
    PFE_5_WAIT = 0x8,<nl>
    PFE_7_WAIT = 0x9,<nl>
    PFE_9_WAIT = 0xA,<nl>
    PFE_15_WAIT = 0xB<nl>
    PFE_24_WAIT  = 0x10,<nl>
    PFE_41_WAIT  = 0x11,<nl>
    PFE_74_WAIT  = 0x12,<nl>
    PFE_123_WAIT = 0x13,<nl>
    PFE_157_WAIT = 0x18,<nl>
    PFE_175_WAIT = 0x19,<nl>
    PFE_201_WAIT = 0x1A,<nl>
    PFE_255_WAIT = 0x1B<ule>
 } PFE_WAIT_STATES ; <codee>

 @parm_sc12_sc1x3 int  | wait_states  | Enumerator specifies desired number of wait states:<nl>
   <nl>
   <code>typedef enum {<ul>
    PFE_0_WAIT = 0x0,<nl>
    PFE_1_WAIT = 0x1,<nl>
    PFE_2_WAIT = 0x2,<nl>
    PFE_3_WAIT = 0x3,<nl>
    PFE_5_WAIT = 0x8,<nl>
    PFE_7_WAIT = 0x9,<nl>
    PFE_9_WAIT = 0xA,<nl>
    PFE_15_WAIT = 0xB<ule>
 } PFE_WAIT_STATES ; <codee>

 @rdesc   -- none --.
 @comm  Set wait states for programmable chip selects PCS0#-PCS3#.<nl><nl>
        One wait state is defined as "1/clock rate".<nl>
        <i>Example:<ie> The SC12 runs at 20 MHz. So one wait state has a duration
        of 50 ns on SC12.
 @commtarget SC12/SC1x3 |
        Default for SC12/SC123/SC143 PCS0#-PCS3# is 15 wait states.<nl>
        Only 0-15 waitstates can be inserted.
 @commtarget SC11/SC13 |
        Default for SC11/SC13 PCS0#-PCS3# is 41 wait states.<nl>
 @Also  pfe83.htm | pfe_enable_pcs |
        pfe8B.htm | pfe_set_wait_states2  |   |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x8A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.03 | V1.00 | V1.00 | V0.90 | n/a
*/
void pfe_set_wait_states (PFE_WAIT_STATES wait_states)
{
  _AL = (unsigned char) wait_states ;
  asm mov ah, PFE_SET_WAIT_STATES ;
  asm int PFE_INT
}
#endif


/***************************************************************************/
// Set wait states for PCS5-6 or PCS4-7
/***************************************************************************/
#ifdef _pfe8B_
/*
 @doc DOC_pfe8B_
 ---------------------------------------------------------------
 PFE: Set wait states for PCS5-6 or PCS4-7
 ---------------------------------------------------------------
 @clib  pfe_set_wait_states2 |
        Set wait states for programmable chip selects PCS5#-PCS6#, respectively PCS4#-7# |
        <cfont>SC11/SC13:void pfe_set_wait_states2 ( PFE_WAIT_STATES wait_states );<nl>
               SC1x3:<tab>void pfe_set_wait_states2 ( PFE_WAIT_STATES2 wait_states );<efont>  |
 @parm_sc11_sc13   int  | wait_states  | Enumerator specifies desired number of wait states:<nl>
    <nl>
   <code>typedef enum {<ul>
    PFE_0_WAIT = 0x00,<nl>
    PFE_1_WAIT = 0x01,<nl>
    PFE_2_WAIT = 0x02,<nl>
    PFE_3_WAIT = 0x03,<nl>
    PFE_5_WAIT = 0x08,<nl>
    PFE_7_WAIT = 0x09,<nl>
    PFE_9_WAIT = 0x0A,<nl>
    PFE_15_WAIT = 0x0B,<nl>
    PFE_24_WAIT  = 0x10,<nl>
    PFE_41_WAIT  = 0x11,<nl>
    PFE_74_WAIT  = 0x12,<nl>
    PFE_123_WAIT = 0x13,<nl>
    PFE_157_WAIT = 0x18,<nl>
    PFE_175_WAIT = 0x19,<nl>
    PFE_201_WAIT = 0x1A,<nl>
    PFE_255_WAIT = 0x1B<ule>
 } PFE_WAIT_STATES ; <codee>
 @parm_sc1x3 int  | wait_states  | Enumerator specifies desired number of wait states:<nl>
    <nl>
   <code>typedef enum {<ul>
    PFE_0_WAIT2 = 0x00,<nl>
    PFE_1_WAIT2 = 0x01,<nl>
    PFE_2_WAIT2 = 0x02,<nl>
    PFE_3_WAIT2 = 0x03,<nl>
    PFE_4_WAIT2 = 0x08,<nl>
    PFE_5_WAIT2 = 0x09,<nl>
    PFE_6_WAIT2 = 0x0A,<nl>
    PFE_7_WAIT2 = 0x0B,<nl>
    PFE_8_WAIT2 = 0x10,<nl>
    PFE_9_WAIT2 = 0x11,<nl>
    PFE_10_WAIT2= 0x12,<nl>
    PFE_11_WAIT2= 0x13,<nl>
    PFE_12_WAIT2= 0x18,<nl>
    PFE_13_WAIT2= 0x19,<nl>
    PFE_14_WAIT2= 0x1A,<nl>
    PFE_15_WAIT2= 0x1B,<ule>
 } PFE_WAIT_STATES2 ; <codee>

 @rdesc   -- none --.
 @commtarget SC11/SC13 |
        Set wait states for programmable chip selects PCS5#-PCS6#.<nl>
        Default for SC11/SC13 PCS5#-PCS6# is 15 wait states.<nl><nl>
        One wait state is defined as "1/clock rate".<nl>
        <i>Example:<ie> The SC13 runs at 40 MHz. So one wait state has a duration
        of 25 ns on SC13.
 @commtarget SC1x3 |
        Set wait states for programmable chip selects PCS4#-PCS7#.<nl>
        Default for SC123/SC143 PCS4#-PCS7# is 15 wait states.<nl>
 @Also  pfe83.htm | pfe_enable_pcs |
        pfe8A.htm | pfe_set_wait_states  |   |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x8B<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | V1.00 | V1.00 | V0.90 | n/a
*/
void pfe_set_wait_states2 (PFE_WAIT_STATES wait_states)
{
  _AL = (unsigned char) wait_states ;
  asm mov ah, PFE_SET_WAIT_STATES2 ;
  asm int PFE_INT
}
#endif


/***************************************************************************/
// Set wait states for UCS
/***************************************************************************/
#ifdef _pfe8C_
/*
  For The DOCLIST.EXE tool --> BeckCLib.LST

 #DOCLIST:PFE_WAIT_STATES2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_0_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_1_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_2_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_3_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_4_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_5_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_6_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_7_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_8_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_9_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_10_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_11_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_12_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_13_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_14_WAIT2   CLIB\HW\pfe8C.htm
 #DOCLIST:PFE_15_WAIT2   CLIB\HW\pfe8C.htm

 @doc DOC_pfe8C_
 ---------------------------------------------------------------
 PFE: Set wait states for UCS
 ---------------------------------------------------------------
 @clib  pfe_set_wait_states_ucs |
        Set wait states for external memory chip select UCS# |
        <cfont>void pfe_set_wait_states_ucs ( PFE_WAIT_STATES2 wait_states );<efont> |
 @parm   int  | wait_states  | Enumerator specifies desired number of wait states:<nl>
    <nl>
   <code>typedef enum {<ul>
    PFE_0_WAIT2 = 0x00,<nl>
    PFE_1_WAIT2 = 0x01,<nl>
    PFE_2_WAIT2 = 0x02,<nl>
    PFE_3_WAIT2 = 0x03,<nl>
    PFE_4_WAIT2 = 0x08,<nl>
    PFE_5_WAIT2 = 0x09,<nl>
    PFE_6_WAIT2 = 0x0A,<nl>
    PFE_7_WAIT2 = 0x0B,<nl>
    PFE_8_WAIT2 = 0x10,<nl>
    PFE_9_WAIT2 = 0x11,<nl>
    PFE_10_WAIT2= 0x12,<nl>
    PFE_11_WAIT2= 0x13,<nl>
    PFE_12_WAIT2= 0x18,<nl>
    PFE_13_WAIT2= 0x19,<nl>
    PFE_14_WAIT2= 0x1A,<nl>
    PFE_15_WAIT2= 0x1B,<ule>
 } PFE_WAIT_STATES2 ; <codee>
 @rdesc   -- none --.
 @comm  Set wait states for external memory chip select UCS#.<nl>
        Default for SC123/SC143 UCS# is 9 wait states.<nl><nl>
        One wait state is defined as "1/clock rate".<nl>
        <i>Example:<ie> The SC1x3 runs at 96 MHz. So one wait state has a duration
        of 10,4166 ns.
 @Also  pfe83.htm |  pfe_enable_pcs |   |   |   |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x8C<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | n/a
*/
void pfe_set_wait_states_ucs (PFE_WAIT_STATES2 wait_states)
{
  _AL = (unsigned char) wait_states ;
  asm mov ah, PFE_SET_WAIT_STATES_UCS ;
  asm int PFE_INT
}
#endif


/*
  For The DOCLIST.EXE tool --> BeckCLib.LST

 #DOCLIST:PFE_SIGNAL_ARDY     CLIB\HW\pfe8D.htm
 #DOCLIST:PFE_SIGNAL_HOLD     CLIB\HW\pfe8D.htm
 #DOCLIST:PFE_SIGNAL_WRL_WRH  CLIB\HW\pfe8D.htm
 #DOCLIST:PFE_SIGNAL_A0_BHE   CLIB\HW\pfe8D.htm
 #DOCLIST:PFE_SIGNAL_ARDY     CLIB\HW\pfe8D.htm
 #DOCLIST:PFE_BUS_SIGNALS     CLIB\HW\pfe8D.htm
*/

/***************************************************************************/
// Enable bus signals
/***************************************************************************/
#ifdef _pfe8D_
/*
 @doc DOC_pfe8D_
 ---------------------------------------------------------------
 PFE: Enable bus signals
 ---------------------------------------------------------------
 @clib  pfe_enable_bus_signals |
        Activate the bus signals ARDY, HOLD, WRL/WRH and A0/BHE |
        <cfont>void pfe_enable_bus_signals ( PFE_BUS_SIGNALS signals );<efont> |
 @parm   PFE_BUS_SIGNALS  | signals  | Signal mask:<nl>
    <nl>
   <code>typedef enum {<ul>
    PFE_SIGNAL_ARDY = 0x01,<nl>
    PFE_SIGNAL_HOLD = 0x02,<nl>
    PFE_SIGNAL_WRL_WRH = 0x04,<nl>
    PFE_SIGNAL_A0_BHE = 0x08<nl>
 } PFE_BUS_SIGNALS ; <codee>
 @rdesc   -- none --.
 @comm Used pins:<ul>
        ARDY, HOLD<ule><nl>
       Excluded pins:<ul>
        If ARDY: PIO6<nl>
        If HOLD: PIO17<nl>
        If WRL/WRH: A0/BHE<nl>
        If A0/BHE: WRL/WRH<ule>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x8D<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.07 | n/a

 @target_clib V2.06
*/
void pfe_enable_bus_signals (PFE_BUS_SIGNALS signals)
{
  _BX = (unsigned int) signals;
  asm mov ah, PFE_ENABLE_BUS_SIGNALS;
  asm int PFE_INT
}
#endif

/***************************************************************************/
// Get function vectors
/***************************************************************************/
/*
  For The DOCLIST.EXE tool --> BeckCLib.LST

 #DOCLIST:HWAPI_VECTORS_    CLIB\HW\pfe90.htm
 #DOCLIST:HWAPI_VECTORS     CLIB\HW\pfe90.htm
 #DOCLIST:WRITE_PIOS        CLIB\HW\pfe90.htm
 #DOCLIST:READ_PIOS         CLIB\HW\pfe90.htm
*/
#ifdef _pfe90_
/*
 @doc DOC_pfe90_
 ---------------------------------------------------------------
 PFE: Get Hardware API Function Pointers
 ---------------------------------------------------------------
 @clib  pfe_get_vectors |
        Get the Function Pointers of Hardware API functions.
        So the functions can be called direct (without software interrupt).
        This is much faster. |
        <cfont>void pfe_get_vectors ( HWAPI_VECTORS far *vectors );<efont> |
 @parm   int  | vectors  | Enumerator specifies desired number of wait states:<nl>
   <nl>
   <code>struct HWAPI_VECTORS_<nl>
   {<ul>
    int         size;<nl>
    READ_PIOS   readPios;<nl>
    WRITE_PIOS  writePios;<ule>
   }<nl>
   HWAPI_VECTORS ; <codee><nl>
    <nl>
    where<nl>
    <nl>
    <code>
    typedef void (far *WRITE_PIOS)  (unsigned short value) ;<nl>
    typedef unsigned short (far *READ_PIOS) (void) ;<nl>
    <codee>
 @rdesc   -- none --.
 @comm
        The <code>size<codee> element of the <code>HWAPI_VECTORS<codee>
        structure is set to 2 within this library API interface function.<s2>The
        two output vectors will be placed in the <code>writePios<codee>
        and <code>readPios<codee> elements.<nl>
        <nl>
        The prototypes for the two indirectly accessed API functions
        are<nl>
        <nl>
        <code>void writePios (unsigned short value) ;<codee><nl>
        <code>unsigned short readPios (void) ;<codee><nl>
        <nl>
        where input parameter <code>value<codee> and return value
        from <code>readPios<codee> both have format:
        <nl><ul>
        B0..B13:  PIO value<nl>
        B14...B15:  -- not used --<nl>
        <ule>

 @Also  hal8C.htm |  hal_read_pio |
        hal8D.htm |  hal_write_pio |  |
 @Also  hal82.htm |  hal_read_pios  |
        hal83.htm |  hal_write_pios |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA20x90<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.03 | V1.00 | V1.00 | n/a   | n/a
*/
void pfe_get_vectors (HWAPI_VECTORS far *vectors)
{
    vectors->size = sizeof( HWAPI_VECTORS ) ;
    _ES = FP_SEG(vectors) ;
    _DI = FP_OFF(vectors) ;
    asm mov ah, PFE_GET_VECTORS ;
    asm int PFE_INT
}
#endif


/***************************************************************************/
// Read databus
/***************************************************************************/
#ifdef _hal80_
/*
 @doc DOC_hal80_
 ---------------------------------------------------------------
 HAL: Read Data Bus
 ---------------------------------------------------------------
 @clib  hal_read_bus |
        Read single byte from data bus.<s2> The result is combined with wAND and
        wXOR parameters.<s2> To read the data bus without change, set wAND=0xFFFF
        and wXOR=0x0000. |
        For SC1x:<nl>
        <cfont><ul>unsigned char hal_read_bus ( unsigned short adr,<nl>
        <tab><tab><tab><tab><tab><tab><tab> unsigned short wAND,<nl>
        <tab><tab><tab><tab><tab><tab><tab> unsigned short wXOR );<ule><efont>
        For SC1x3:<nl>
        <cfont><ul>unsigned short hal_read_bus ( unsigned short adr,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp; unsigned short wAND,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp; unsigned short wXOR );<ule><efont> |
 @depr_external Use inport or inportb function from dos.h instead!
 @parm   unsigned short | adr  | I/O Address
 @parm   unsigned short  | wAND  | Result mask
 @parm   unsigned short  | wXOR  | Bit Inverter
 @rdesc_sc1x
         8 Bit data in AX, AX = (databus & wAND) ^ wXOR
 @rdesc_sc1x3
        16 Bit data in AX, AX = (databus & wAND) ^ wXOR
 @comm   & = bit wise AND<nl>
         ^ = bit wise XOR
 @Also  halA0.htm |  hal_readblock_bus |
        hal81.htm |  hal_write_bus |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x80<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | n/a
*/
#undef hal_read_bus

unsigned char hal_read_bus (unsigned short adr, unsigned short wAND, unsigned short wXOR)
{
  // read data bus
  asm mov ah, HAL_READ_DATA_BUS;
  asm mov DI, adr
  asm mov BX, wAND
  asm mov CX, wXOR
  asm int HAL_INT
  return _AX ;
}
#endif

#ifdef _hal80A_
unsigned short hal_read_bus_sc123 (unsigned short adr, unsigned short wAND, unsigned short wXOR)
{
  // read data bus
  asm mov ah, HAL_READ_DATA_BUS;
  asm mov DI, adr
  asm mov BX, wAND
  asm mov CX, wXOR
  asm int HAL_INT
  return _AX ;
}
#endif

/***************************************************************************/
// Write databus
/***************************************************************************/
#ifdef _hal81_
/*
 @doc DOC_hal81_
 ---------------------------------------------------------------
 HAL: Write Data Bus
 ---------------------------------------------------------------
 @clib  hal_write_bus |
        Write single byte to data bus.<s2> The provided parameters are combined as
        follows to form the output byte value:<nl>
        <nl>
        <tab><tab><cfont>output value = (data & wAND) ^ wXOR<efont><nl>
        <nl>
        To write the value to the address without modification, set wAND=0xFFFF
        and wXOR=0x0000. |
        For SC1x:<nl>
        <cfont><ul>void hal_write_bus ( unsigned short adr, unsigned char value,<nl>
        <tab><tab><tab><tab><tab> unsigned short wAND,unsigned short wXOR );<ule><efont>
        For SC1x3:<nl>
        <cfont><ul>void hal_write_bus ( unsigned short adr, unsigned short value,<nl>
        <tab><tab><tab><tab><tab> unsigned short wAND,unsigned short wXOR );<ule><efont>  |
 @depr_external Use outport or outportb function from dos.h instead!
 @parm   unsigned short | adr  | I/O Address
 @parm   unsigned char  | value | Value to be output
 @parm   unsigned short | wAND  | Mask applied to output
 @parm   unsigned short | wXOR  | Output bit inverter
 @rdesc  -- none --.
 @comm  & = bit wise AND<nl>
        ^ = bit wise XOR<nl>
        <ule>
 @Also  halA1.htm |  hal_writeblock_bus |
        hal80.htm |  hal_read_bus |   |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x81<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | n/a
*/
#undef hal_write_bus

void hal_write_bus (unsigned short adr, unsigned char value,
                    unsigned short wAND, unsigned short wXOR)
{
  // write data bus
  asm mov ah, HAL_WRITE_DATA_BUS;
  asm mov DI, adr
  asm mov dh, 0
  asm mov dl, value
  asm mov BX, wAND
  asm mov CX, wXOR
  asm int HAL_INT
}
#endif

#ifdef _hal81A_
void hal_write_bus_sc123 (unsigned short adr, unsigned short value,
                          unsigned short wAND, unsigned short wXOR)
{
  // write data bus
  asm mov ah, HAL_WRITE_DATA_BUS;
  asm mov DI, adr
  asm mov dh, 0
  asm mov dx, value
  asm mov BX, wAND
  asm mov CX, wXOR
  asm int HAL_INT
}
#endif


/***************************************************************************/
// Read pios
/***************************************************************************/
#ifdef _hal82_
/*
 @doc DOC_hal82_
 ---------------------------------------------------------------
 HAL: Read Programmable I/O Pins
 ---------------------------------------------------------------
 @clib  hal_read_pios |
        Read the programmable I/O pins. The result is combined with the
        <code>wAND<codee> and <code>wXOR<codee> parameters.<s2> To read the PIO pins
        without modification, set <code>wAND=0xFFFF<codee> and
        <code>wXOR=0x0000<codee>.<s2> To read only the input pins, set
        <code>wAND<codee> = <code>wInp<codee> value output from the
        <linkto>pfe82r.htm<linkmid>pfe_get_pio_state<linktail> function. |

        <cfont>unsigned short hal_read_pios ( unsigned short wAND,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; unsigned short wXOR );<efont> |
 @parm   unsigned short | wAND  | mask
 @parm   unsigned short | wXOR  | bit inverter
 @rdesc_sc1x   (PIO[0..13] & wAND) ^ wXOR<nl>
 @rdesc_sc1x3  (PIO[0..15] & wAND) ^ wXOR<nl>
 @rdesc_sc2x   (PIO[0..2, 9..13] & wAND) ^ wXOR<nl>
 @comm  & = bit wise AND<nl>
        ^ = bit wise XOR<nl>
        <ule>
 @Also   hal8C.htm |  hal_read_pio |
         hal83.htm |  hal_write_pios |
         pfe82r.htm | pfe_get_pio_state
 @Also   pfe82.htm | pfe_enable_pio |  |  |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x82<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned short hal_read_pios (unsigned short wAND, unsigned short wXOR)
{
  // read pios
  asm mov ah, HAL_READ_PIO
  asm mov BX, wAND
  asm mov CX, wXOR
  asm int HAL_INT
  return _AX ;
}
#endif


/***************************************************************************/
// Read pios (PIO16-31)
/***************************************************************************/
#ifdef _hal82A_
/*
 @doc DOC_hal82A_
 ---------------------------------------------------------------
 HAL: Read Programmable I/O Pins (PIO16-31)
 ---------------------------------------------------------------
 @clib  hal_read_pios2 |
        Read the programmable I/O pins. The result is combined with the
        <code>wAND<codee> and <code>wXOR<codee> parameters.<s2> To read the PIO pins
        without modification, set <code>wAND=0xFFFF<codee> and
        <code>wXOR=0x0000<codee>.<s2> To read only the input pins, set
        <code>wAND<codee> = <code>wInp<codee> value output from the
        <linkto>pfe82r.htm<linkmid>pfe_get_pio_state2<linktail> function. |

        <cfont>unsigned short hal_read_pios2 ( unsigned short wAND,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp;&nbsp; unsigned short wXOR );<efont> |
 @parm   unsigned short | wAND  | mask
 @parm   unsigned short | wXOR  | bit inverter
 @rdesc_sc1x3 (PIO[16..24, 26..31] & wAND) ^ wXOR<nl>
 @rdesc_sc2x  (PIO[18..23, 27..28, 31] & wAND) ^ wXOR<nl>
 @comm  & = bit wise AND<nl>
        ^ = bit wise XOR<nl>
        <ule>
 @Also   hal8C.htm |  hal_read_pio |
         hal83A.htm |  hal_write_pios2 |
         pfe82rA.htm | pfe_get_pio_state2
 @Also   pfe82.htm | pfe_enable_pio |  |  |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x82<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V0.90 | V1.00
*/
unsigned short hal_read_pios2 (unsigned short wAND, unsigned short wXOR)
{
  // read pios
  asm mov ah, HAL_READ_PIO
  asm mov SI, wAND
  asm mov DI, wXOR
  asm int HAL_INT
  return _DX ;
}
#endif

/***************************************************************************/
// Write pios
/***************************************************************************/
#ifdef _hal83_
/*
 @doc DOC_hal83_
 ---------------------------------------------------------------
 HAL: Write Programmable I/O Pins
 ---------------------------------------------------------------
 @clib  hal_write_pios |
        Write to the programmable I/O pins.<s2> Before the value is written,
        the value is combined with the wAND and wXOR parameters as:<nl>
        <nl>
        <tab>SC1x:<tab> PIO[0..13] = (data & wAND) ^ wXOR<nl>
        <tab>SC1x3:<tab>PIO[0..15] = (data & wAND) ^ wXOR<nl>
        <tab>SC2x:<tab> PIO[0..2, 9..13] = (data & wAND) ^ wXOR<nl>
        <nl>
        To write value to the programmable I/O pins without change,
        set wAND=0xFFFF and wXOR=0x0000.<nl>
        <nl>
        Only PIO pins that are defined as outputs can be written. |
        <cfont>void hal_write_pios ( unsigned short value,<nl>
        <tab><tab><tab><tab><tab>&nbsp; unsigned short wAND,<nl>
        <tab><tab><tab><tab><tab>&nbsp; unsigned short wXOR );<efont> |
 @parm   unsigned short | value | output data
 @parm   unsigned short | wAND  | mask
 @parm   unsigned short | wXOR  | bit inverter
 @rdesc   -- none --.
 @comm  & = bit wise AND<nl>
        ^ = bit wise XOR<nl>
        <ule>
 @Also  hal8D.htm | hal_write_pio |
        hal82.htm | hal_read_pios |
        pfe82.htm | pfe_enable_pio
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x83<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V1.07 | V1.00
*/
void hal_write_pios (unsigned short value,
                     unsigned short wAND,
                     unsigned short wXOR)
{
  // write pios
  asm mov ah, HAL_WRITE_PIO
  asm mov dx, value
  asm mov BX, wAND
  asm mov CX, wXOR
  asm int HAL_INT
}
#endif

/***************************************************************************/
// Write pios (PIO16-31)
/***************************************************************************/
#ifdef _hal83A_
/*
 @doc DOC_hal83A_
 ---------------------------------------------------------------
 HAL: Write Programmable I/O Pins (PIO16-31)
 ---------------------------------------------------------------
 @clib  hal_write_pios2 |
        Write to the programmable I/O pins.<s2> Before the value is written,
        the value is combined with the wAND and wXOR parameters as:<nl>
        <nl>
        <tab>SC1x3:<tab>PIO[16..24, 26..31] = (data & wAND) ^ wXOR<nl>
        <tab>SC2x:<tab> PIO[18..23, 27..28, 31] = (data & wAND) ^ wXOR<nl>
        <nl>
        To write value to the programmable I/O pins without change,
        set wAND=0xFFFF and wXOR=0x0000.<nl>
        <nl>
        Only PIO pins that are defined as outputs can be written. |
        <cfont>void hal_write_pios2 ( unsigned short value,<nl>
        <tab><tab><tab><tab><tab>&nbsp;&nbsp; unsigned short wAND,<nl>
        <tab><tab><tab><tab><tab>&nbsp;&nbsp; unsigned short wXOR );<efont> |
 @parm   unsigned short | value | output data
 @parm   unsigned short | wAND  | mask
 @parm   unsigned short | wXOR  | bit inverter
 @rdesc   -- none --.
 @comm  & = bit wise AND<nl>
        ^ = bit wise XOR<nl>
        <ule>
 @Also  hal8D.htm | hal_write_pio |
        hal82A.htm | hal_read_pios2 |
        pfe82.htm | pfe_enable_pio
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x83<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    n/a   | n/a   | n/a   | V1.07 | V1.00
*/
void hal_write_pios2 (unsigned short value,
                      unsigned short wAND,
                      unsigned short wXOR)
{
  // write pios
  asm mov ah, HAL_WRITE_PIO2
  asm mov dx, value
  asm mov BX, wAND
  asm mov CX, wXOR
  asm int HAL_INT
}
#endif

/***************************************************************************/
// Install ISR
/***************************************************************************/
/*
  For The DOCLIST.EXE tool --> BeckCLib.LST

 #DOCLIST:InterruptHandler    CLIB\HW\hal84.htm
*/

#ifdef _hal84_
/*
 @doc DOC_hal84_
 ---------------------------------------------------------------
 HAL: Install Interrupt Service Routine
 ---------------------------------------------------------------
 @clib  hal_install_isr | Install Interrupt Service Routine. |
        <cfont>InterruptHandler hal_install_isr ( unsigned short irq,
        <tab><tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; unsigned short count,
        <tab><tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp;  InterruptHandler handler );<efont> |
 @parm_sc1x unsigned short | irq  | HAL interrupt number from following list:<ul>
          0 = INT0 (external)<nl>
          1 = <i>(*) Network controller (internal)<ie><nl>
          2 = INT2 (external)<nl>
          3 = INT3 (external)<nl>
          4 = INT4 (external)<nl>
          5 = INT5 (external) / DMA Interrupt Channel 0 (if DMA is used)<nl>
          6 = INT6 (external) / DMA Interrupt Channel 1 (if DMA is used)<nl>
          7 = reserved<nl>
          8 = Timer0 (internal)<nl>
          9 = Timer1 (internal)<nl>
          10 = <i>(*) Timer 1ms (internal)<ie><nl>
          11 = <i>(*) Serial port 0 (internal)<ie><nl>
          12 = <i>(*) Serial port 1 (internal)<ie><nl>
          13 = <i>(*) DMA Interrupt Channel 2 (internal, not on SC12)<ie><nl>
          14 = <i>(*) DMA Interrupt Channel 3 (internal, not on SC12)<ie><nl>
          15 = NMI Powerfail Interrupt (internal/external)<nl><nl>
          (*) = used internally by @CHIP-RTOS, not available for user interrupt service functions <ule>
 @parm_sc1x3 unsigned short | irq  | HAL interrupt number from following list:<ul>
          0 = <i>(*) Network controller 0 (internal)<ie><nl>
          1 = INT1 (external)<nl>
          2 = SPI controller (internal)<nl>
          3 = INT3 (external) / <i>(*) USB controller (internal)<ie><nl>
          4 = <i>(*) Serial port 2 (internal)<ie><nl>
          5 = DMA Interrupt Channel 0<nl>
          6 = DMA Interrupt Channel 1<nl>
          7 = INT5 (external) / <i>(*) Serial port 3 (internal)<ie><nl>
          8 = Timer0 (internal)<nl>
          9 = Timer1 (internal)<nl>
          10 = <i>(*) Timer 1ms (internal)<ie><nl>
          11 = <i>(*) Serial port 0 (internal)<ie><nl>
          12 = <i>(*) Serial port 1 (internal)<ie><nl>
          13 = DMA Interrupt Channel 2<nl>
          14 = DMA Interrupt Channel 3<nl>
          15 = PFI Powerfail Interrupt (internal/external)<nl>
          16 = <i>(*) CAN0 controller (internal) / (*) CAN1 controller (internal)<ie><nl>
          17 = I2C controller (internal)<nl>
          18 = Network controller 1 (internal)<nl><nl>
          (*) = used internally by @CHIP-RTOS, not available for user interrupt service functions <ule>
 @parm_sc2x unsigned short | irq  | HAL interrupt number from following list:<ul>
          0 = <i>(*) Network controller 0 (internal)<ie><nl>
          1 = INT1 (external)<nl>
          2 = SPI controller (internal)<nl>
          3 = INT3 (external) / <i>(*) USB controller (internal)<ie><nl>
          4 = <i>(*) Serial port 2 (internal)<ie><nl>
          5 = <i>(*) DMA Interrupt Channel 0<ie><nl>
          6 = <i>(*) DMA Interrupt Channel 1<ie><nl>
          7 = INT5 (external) / <i>(*) Serial port 3 (internal)<ie><nl>
          8 = Timer0 (internal)<nl>
          9 = Timer1 (internal)<nl>
          10 = <i>(*) Timer 1ms (internal)<ie><nl>
          11 = <i>(*) Serial port 0 (internal)<ie><nl>
          12 = <i>(*) Serial port 1 (internal)<ie><nl>
          13 = <i>(*) DMA Interrupt Channel 2<ie><nl>
          14 = <i>(*) DMA Interrupt Channel 3<ie><nl>
          15 = PFI Powerfail Interrupt (internal/external)<nl>
          16 = <i>(*) CAN0 controller (internal) / (*) CAN1 controller (internal)<ie><nl>
          17 = I2C controller (internal)<nl>
          18 = <i>(*) Network controller 1 (internal)<ie><nl><nl>
          (*) = used internally by @CHIP-RTOS, not available for user interrupt service functions <ule>

 @parm  unsigned short | count  | Number of interrupts generated before new
        user interrupt service routine is called.<nl>
         count = 0 disables the user ISR (same as a NULL in handler)
 @parm   int  | handler  | far pointer to user  interrupt service routine<nl>
         <tab>if pointer is NULL user ISR is disabled
 @rdesc   Far pointer to old ISR handler
 @comm  The user-defined ISR is called from a system ISR with the interrupt
        identifier number in the BX CPU register, thus allowing for a single user ISR to
        handle multiple interrupt sources.<s2> The user ISR can be declared in either
        of the following forms:<nl>
        <ul><nl><cfont>
         void huge My_ISR(void) ;<tab>   // More efficient form<nl>
         <nl>
         void interrupt My_ISR(void) ;<tab> // Tolerated form<nl>
        <efont><ule><nl>
        The more efficient <cfont>huge<efont> procedures are recommended.<s2>
        The user ISR function must preserve only the DS and BP registers, so
        there is no requirement for the full register save/restore provided by the
        <cfont>interrupt<efont> declarations.<nl>
        <nl>
        Any required EOI signal is issued by the system ISR which calls your user ISR
        function.<s2>This EOI is issued after your function returns.
        <nl><nl>
        The <code>InterruptHandler<codee> vector type is defined as:<ul><nl>
        <code>
        typedef void huge (far *InterruptHandler)(void);<codee><ule>
 @Also  hal84A.htm | hal_install_rtx_isr |
        pfe84.htm | pfe_enable_int |
        ../RTX/rtx35.htm |  RTX_Install_RTI_Hook
 @Also  halC1.htm  | hal_save_non_volatile_data |
          |  |
          | 
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x84<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
InterruptHandler hal_install_isr (unsigned short irq,
                                  unsigned short count,
                                  InterruptHandler handler)
{
  InterruptHandler oldhandler;

  // install isr
  asm les bx, handler  ;// es = FP_SEG(handler);  bx = FP_OFF(handler);
  asm mov ah, HAL_INSTALL_ISR;
  asm mov dx, irq
  asm mov CX, count
  asm int HAL_INT

  oldhandler = (InterruptHandler) MK_FP(_ES, _BX);

  return oldhandler;
}
#endif


/***************************************************************************/
// Install RTX ISR
/***************************************************************************/
#ifdef _hal84A_
/*
 @doc DOC_hal84A_
 ---------------------------------------------------------------
 HAL: Install RTX Interrupt Service Routine
 ---------------------------------------------------------------
 @clib  hal_install_rtx_isr | Install RTX Interrupt Service Routine |
        <cfont>InterruptHandler hal_install_rtx_isr ( unsigned short irq,<nl>
        <tab><tab><tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; unsigned short count,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; InterruptHandler handler );<efont> |
 @parm_sc1x unsigned short | irq  | HAL interrupt number from following list:<ul>
          0 = INT0 (external)<nl>
          1 = <i>(*) Network controller (internal)<ie><nl>
          2 = INT2 (external)<nl>
          3 = INT3 (external)<nl>
          4 = INT4 (external)<nl>
          5 = INT5 (external) / DMA Interrupt Channel 0 (if DMA is used)<nl>
          6 = INT6 (external) / DMA Interrupt Channel 1 (if DMA is used)<nl>
          7 = reserved<nl>
          8 = Timer0 (internal)<nl>
          9 = Timer1 (internal)<nl>
          10 = <i>(*) Timer 1ms (internal)<ie><nl>
          11 = <i>(*) Serial port 0 (internal)<ie><nl>
          12 = <i>(*) Serial port 1 (internal)<ie><nl>
          13 = <i>(*) DMA Interrupt Channel 2 (internal, not on SC12)<ie><nl>
          14 = <i>(*) DMA Interrupt Channel 3 (internal, not on SC12)<ie><nl>
          15 = NMI Powerfail Interrupt (internal/external)<nl><nl>
          (*) = used internally by @CHIP-RTOS, not available for user interrupt service functions <ule>
 @parm_sc1x3 unsigned short | irq  | HAL interrupt number from following list:<ul>
          0 = <i>(*) Network controller 0 (internal)<ie><nl>
          1 = INT1 (external)<nl>
          2 = SPI controller (internal)<nl>
          3 = INT3 (external) / <i>(*) USB controller (internal)<ie><nl>
          4 = <i>(*) Serial port 2 (internal)<ie><nl>
          5 = DMA Interrupt Channel 0<nl>
          6 = DMA Interrupt Channel 1<nl>
          7 = INT5 (external) / <i>(*) Serial port 3 (internal)<ie><nl>
          8 = Timer0 (internal)<nl>
          9 = Timer1 (internal)<nl>
          10 = <i>(*) Timer 1ms (internal)<ie><nl>
          11 = <i>(*) Serial port 0 (internal)<ie><nl>
          12 = <i>(*) Serial port 1 (internal)<ie><nl>
          13 = DMA Interrupt Channel 2<nl>
          14 = DMA Interrupt Channel 3<nl>
          15 = PFI Powerfail Interrupt (internal/external)<nl>
          16 = <i>(*) CAN0 controller (internal) / (*) CAN1 controller (internal)<ie><nl>
          17 = I2C controller (internal)<nl>
          18 = Network controller 1 (internal)<nl><nl>
          (*) = used internally by @CHIP-RTOS, not available for user interrupt service functions <ule>
 @parm_sc2x unsigned short | irq  | HAL interrupt number from following list:<ul>
          0 = <i>(*) Network controller 0 (internal)<ie><nl>
          1 = INT1 (external)<nl>
          2 = SPI controller (internal)<nl>
          3 = INT3 (external) / <i>(*) USB controller (internal)<ie><nl>
          4 = <i>(*) Serial port 2 (internal)<ie><nl>
          5 = <i>(*) DMA Interrupt Channel 0<ie><nl>
          6 = <i>(*) DMA Interrupt Channel 1<ie><nl>
          7 = INT5 (external) / <i>(*) Serial port 3 (internal)<ie><nl>
          8 = Timer0 (internal)<nl>
          9 = Timer1 (internal)<nl>
          10 = <i>(*) Timer 1ms (internal)<ie><nl>
          11 = <i>(*) Serial port 0 (internal)<ie><nl>
          12 = <i>(*) Serial port 1 (internal)<ie><nl>
          13 = <i>(*) DMA Interrupt Channel 2<ie><nl>
          14 = <i>(*) DMA Interrupt Channel 3<ie><nl>
          15 = PFI Powerfail Interrupt (internal/external)<nl>
          16 = <i>(*) CAN0 controller (internal) / (*) CAN1 controller (internal)<ie><nl>
          17 = I2C controller (internal)<nl>
          18 = <i>(*) Network controller 1 (internal)<ie><nl><nl>
          (*) = used internally by @CHIP-RTOS, not available for user interrupt service functions <ule>

 @parm   unsigned short | count  | Number of interrupts generated before new
         user interrupt service routine is called.<nl>
         count = 0 disables the user ISR (same as a NULL in handler)
 @parm   int  | handler  | far pointer to user  interrupt service routine<nl>
         <tab>if pointer is NULL user ISR is disabled
 @rdesc   Far pointer to old ISR handler
 @comm  The user-defined ISR is called from a system ISR with the interrupt
        identifier number in the BX CPU register, thus allowing for a single user ISR to
        handle multiple interrupt sources.<s2> The user ISR can be declared in either
        of the following forms:<nl>
        <ul><nl><cfont>
         void huge My_ISR(void) ;<tab>   // More efficient form<nl>
         <nl>
         void interrupt My_ISR(void) ;<tab> // Tolerated form<nl>
        <efont><ule><nl>
        The more efficient <cfont>huge<efont> procedures are recommended.<s2>
        The user ISR function must preserve only the DS and BP registers, so
        there is no requirement for the full register save/restore provided by the
        <cfont>interrupt<efont> declarations.<nl>
        <nl>
        Any required EOI signal is issued by the system ISR which calls your user ISR
        function.<s2>This EOI is issued after your function returns.
        <nl><nl>
         RTX ISR: If you install a RTX ISR you can use the follwing RTX calls in your ISR:<nl>
         <ul><nl>
           <linkto>../RTX/rtx10.htm<linkmid>RTX_Restart_Task<linktail><nl>
           <linkto>../RTX/rtx06.htm<linkmid>RTX_Wakeup<linktail><nl>
           <linkto>../RTX/rtx1A.htm<linkmid>RTX_Signal_Sem<linktail><nl>
           <linkto>../RTX/rtx42.htm<linkmid>RTX_Signal_Events<linktail><nl>
           <linkto>../RTX/rtx52.htm<linkmid>RTX_Send_Msg<linktail><nl>
           <linkto>../RTX/rtx32.htm<linkmid>RTX_Start_Timer<linktail><nl>
           <linkto>../RTX/rtx33.htm<linkmid>RTX_Stop_Timer<linktail><nl>
           <linkto>../RTX/rtx31.htm<linkmid>RTX_Remove_Timer<linktail><nl>
           <ule><nl>
         <bold>Important Notes:<bolde><nl>
         <nl><ul>
         The RTX ISR is slower than a normal ISR.<ule>
         <nl>
         The <code>InterruptHandler<codee> vector type is defined as:<ul><nl>
         <code>
         typedef void huge (far *InterruptHandler)(void);<codee><ule>
 @commtarget SC1x |
         Using RTX ISR are not recommended for INT5 or INT6 if DMA is used by the
         <linkto>../../fossil.htm<linkmid>Fossil<linktail>
         serial ports interface, because the slower RTX ISR could
         result in UART receiver character loss.<s2> <nl>
         <nl>
         If you are using a RTX ISR for timer0, timer1, INT5 or INT6 there must not exist
         a normal ISR on the system which enables the interrupts during its execution!<nl><nl>
         Do not install a RTX ISR for the powerfail interrupt!<nl><nl>
         <bold>Also important<bolde>:<s2> The NMI function of the multifunction
         pin 17 (RESET/NMI/LINK_LED) of the IPC@CHIP&reg; SC11/SC12/SC13 is for
         power fail purposes only.<s2>
         It is not possible to use NMI as a "normal" interrupt pin like INT0 for
         generating interrupts.<s2>
         It can only be used as described in the IPC@CHIP&reg; hardware documentation.
 @commtarget SC1x3 |
         INT1 and network controller 1 share the same interrupt. Due to this fact,
         the installed user interrupt service routines for INT1 and network controller 1 must
         be of same type. If the network controller 1 is used both ISRs must be of type RTX ISR.
 @Also  hal84.htm  | hal_install_isr |
        pfe84.htm | pfe_enable_int |
        ../RTX/rtx35.htm |  RTX_Install_RTI_Hook
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x84<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
InterruptHandler hal_install_rtx_isr (unsigned short irq,
                                      unsigned short count,
                                      InterruptHandler handler)
{
  InterruptHandler oldhandler;

  // install isr
  asm les bx, handler  ;// es = FP_SEG(handler);  bx = FP_OFF(handler);
  asm mov ah, HAL_INSTALL_ISR;
  asm mov dx, irq
  asm or  dh, 0x80    ; //rtx isr
  asm mov CX, count
  asm int HAL_INT

  oldhandler = (InterruptHandler) MK_FP(_ES, _BX);

  return oldhandler;
}
#endif


/***************************************************************************/
// Init timer
/***************************************************************************/
#ifdef _hal85_
/*
 @doc DOC_hal85_
 ---------------------------------------------------------------
 HAL: Initialize Timer Settings
 ---------------------------------------------------------------
 @clib  hal_init_timer | Initialize timer settings |
        <cfont>void hal_init_timer ( unsigned char timer,<nl>
        <tab><tab><tab><tab><tab>&nbsp; unsigned short mode,<nl>
        <tab><tab><tab><tab><tab>&nbsp; unsigned short divider );<efont> |
 @parm  unsigned char  | timer  | Timer<nl>
                 <tab>0=Timer0 / 1=Timer1
 @parm  unsigned short | mode  | Timer mode:<ul>
    Bit 0: 0=run single time / 1=run continuous<nl>
    Bit 1: 0=disable timer interrupt / 1=enable timer interrupt<nl>
    Bit 2: 0=use internal clock / 1=use TMRIN pin as external clock<nl>
    Bit 3..15: not used<ule>
 @parm  unsigned short | divider  | Clock divider (maximum count value)<nl>
 @rdesc   -- none --.
 @comm
        Initialize the timer settings of timer0 or timer1.<nl>
        <nl>
        The clock divider value serves as a comparator for the associated timer
        count.<s2> The timer count is a 16 bit value that is incremented by the processor
        internal clock (see <linkto>hal8A.htm<linkmid>hal_get_frequencies<linktail>
        function) or can also be configured to increment based on the TMRIN0
        or TMRIN1 external signals (see PFE
        <linkto>pfe85.htm<linkmid>pfe_enable_timer<linktail>).<s2>
        The TMROUT0 und TMROUT1 signals can be used to generate waveforms
        of various duty cycles.<s2> The default is a 50% duty cycle waveform<s2>
        (Change waveform with HAL
        <linkto>hal8B.htm<linkmid>hal_set_duty_cycle_waveform<linktail> function).<nl>
         <nl>
        Note that TMRIN pin and TMROUT pin can not be used at the same time.<nl>
  @commtarget SC1x |
        If the clock divider value is set to 0000h, the timer will count from 0000h
        to FFFFh (maximum divider).<s2> When the timer reaches the clock divider
        value, it resets to 0 during the same clock cycle.<s2> The timer count
        never dwells equals to the clock divider value (except for special case
        when divider value is set to 0000h).<nl>
  @commtarget SC1x3/SC2x |
         When the timer reaches the clock divider value, it
         resets to 0 during the same clock cycle.<s2> The timer count never dwells equal to
         the clock divider value (except for special case
         when divider value is set to 0000h).<nl>
         <nl>
         If the clock divider value is set to 0000h, the timer will not count.<s2> This
         divider value should not be used.
  @comm  When the timer is configured to run in single time mode, the timer
        clears the count and then halts on reaching the maximum count (clock
        divider value).<nl>
        <nl>
        If the timer interrupt is enabled, the interrupt request is generated
        when the count equals the clock divider value.<s2> Use HAL
        <linkto>hal84.htm<linkmid>hal_install_isr<linktail> function
        to install your interrupt service routine.<nl>
        <nl>
        If "use internal clock" is selected the associated TMRIN pin serves
        as a gate.<s2> A "high" on the TMRIN pin keeps the timer counting.<s2>
        A "low" holds the timer value.
 @Also hal8F.htm |  hal_init_timer_ext |
       hal86.htm |  hal_start_timer  |
       hal88.htm |  hal_read_timer_count
 @Also hal89.htm | hal_write_timer_count | | | |

 @devnote The timer output frequency is dependent on the internal processor clock.<nl>
       For compatibility with future versions of @Chip, please use the HAL
       <linkto>hal8A.htm<linkmid>hal_get_frequencies<linktail> to compute the
       correct clock divider value.<nl><nl>
       Available examples<ul>
            1. TimerIn example, timerin.c<nl>
            2. TimerOut example, timerout.c<ule>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x85<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void hal_init_timer (unsigned char timer,
                     unsigned short mode,
                     unsigned short divider)
{
  // install isr
  asm mov ah, HAL_INIT_TIMER;
  asm mov al, timer
  asm mov dx, mode
  asm mov CX, divider
  asm int HAL_INT
}
#endif


/***************************************************************************/
// Init timer Extended
/***************************************************************************/
#ifdef _hal8F_
/*
 @doc DOC_hal8F_
 ---------------------------------------------------------------
 HAL: Initialize Timer Settings Ext
 ---------------------------------------------------------------
 @clib  hal_init_timer_ext | Initialize timer settings Extended |
        <cfont>void hal_init_timer_ext ( unsigned char timer,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; unsigned short mode );<efont> |
 @parm   unsigned char  | timer  | Timer<nl>
                 <tab>0=Timer0 / 1=Timer1
 @parm   unsigned short  | mode  | Timer mode:<ul>
    Bit 0..2: must be 0<nl>
    Bit 3: 0=disable prescale t2 / 1=enable prescale t2<nl>
    Bit 4: 0=disable retrigger   / 1=enable retrigger<nl>
    Bit 5..15: must be 0<ule>
 @rdesc   -- none --.
 @comm This function must be called after the Initialize Timer Settings
       <linkto>hal85.htm<linkmid>hal_init_timer<linktail> function call!<nl>
       <nl>
       The <cfont>mode<efont> control bits have the following affect:<nl>
       <nl>
       <hangpara 30:30>
       <bold>Prescale T2:<bolde><s2> If the Prescale feature is enabled, the timer
       (specified by argument <cfont>timer<efont>) will use the Timer2 output
       for its time base.<s2> If the <linkto>../../config.htm#TIMER_RTI<linkmid>RTI rate<linktail>
       is not changed by the user it will provide a 1000 Hz timer clock rate.<s2>
       (Timer2 is used internally by the @CHIP-RTOS as the Real-Time Interrupt (RTI),
       which defaults to a one millisecond interval timer.)<s2>
       If the Prescale feature is disabled, then the value returned from the
       <linkto>hal8A.htm<linkmid>hal_get_frequencies<linktail> function
       indicates the timer's time base.<paraend>
 @commtarget SC1x | <hangpara 30:30>
       <bold>Retrigger:<bolde><s2> If the retrigger setting is enabled, then a 0 to 1 edge
       transition on TMRIN0 or TMRIN1 resets the respective counter to zero.<s2>
       When retrigger setting is disabled, a High input on TMRIN0 or TMRIN1 enables
       counting and a Low input holds the current timer value.
       <paraend>
 @commtarget SC1x3/SC2x | <hangpara 30:30>
       <bold>Retrigger:<bolde><s2> If the retrigger setting is enabled, then a 0 to 1 edge
       transition on TMRIN0 or TMRIN1 resets the respective counter to zero.
       If the input remains High, the timer starts counting on the following clock transitions.
       If the input goes again Low, the timer stops counting.<s2>
       When retrigger setting is disabled, a High input on TMRIN0 or TMRIN1 enables
       counting and a Low input holds the current timer value.
       <paraend>

 @Also  hal85.htm |  hal_init_timer  |
        hal86.htm |  hal_start_timer |
        hal88.htm |  hal_read_timer_count
 @Also  hal89.htm |  hal_write_timer_count | | | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x8F<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void hal_init_timer_ext (unsigned char timer,
                         unsigned short mode)
{
  // install isr
  asm mov ah, HAL_INIT_TIMER_EXT;
  asm mov al, timer
  asm mov dx, mode
  asm int HAL_INT
}
#endif


/***************************************************************************/
// Start timer
/***************************************************************************/
#ifdef _hal86_
/*
 @doc DOC_hal86_
 ---------------------------------------------------------------
 HAL: Start Timer
 ---------------------------------------------------------------
 @clib  hal_start_timer | Start timer |
        <cfont>void hal_start_timer ( unsigned char timer );<efont> |
 @parm  unsigned char  | timer  | Which timer:<nl>
                 <tab>0 = Timer0 / 1 = Timer1
 @rdesc   -- none --.
 @comm
        Enable the specified timer to up count.
 @Also  hal85.htm |  hal_init_timer |
        hal87.htm |  hal_stop_timer |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x86<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void hal_start_timer (unsigned char timer)
{
  // start timer
  asm mov ah, HAL_START_TIMER;
  asm mov al, timer
  asm int HAL_INT
}
#endif

/***************************************************************************/
// Stop timer
/***************************************************************************/
#ifdef _hal87_
/*
 @doc DOC_hal87_
 ---------------------------------------------------------------
 HAL: Stop timer
 ---------------------------------------------------------------
 @clib  hal_stop_timer | Stop timer |
        <cfont>void hal_stop_timer ( unsigned char timer );<efont> |
 @parm  unsigned char | timer  | Which timer:<nl>
                 <tab>0 = Timer0 / 1 = Timer1
 @rdesc   -- none --.
 @comm
        Stop the specified timer's counting.
 @Also  hal85.htm |  hal_init_timer |
        hal86.htm |  hal_start_timer |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x87<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void hal_stop_timer (unsigned char timer)
{
  // stop timer
  asm mov ah, HAL_STOP_TIMER;
  asm mov al, timer
  asm int HAL_INT
}
#endif

/***************************************************************************/
// Read timer count
/***************************************************************************/
#ifdef _hal88_
/*
 @doc DOC_hal88_
 ---------------------------------------------------------------
 HAL: Read Timer Count
 ---------------------------------------------------------------
 @clib  hal_read_timer_count | Read timer count |
        <cfont>unsigned short hal_read_timer_count ( unsigned char timer,<nl>
        <tab><tab><tab><tab><tab><tab><tab>&nbsp; unsigned short far * maxcount );<efont> |
 @parm  unsigned char | timer  | Which timer:<nl>
                 <tab>0 = Timer0 / 1 = Timer1
 @parm  int  | maxcount  | Optional output parameter.<nl>
        If this pointer is not NULL, then a Boolean is output:<ul>
        0 -<gt> Maximum count not reached<nl>
        1 -<gt> Maximum count reached<ule>
        Set to NULL if not interested in maximum count.
 @rdesc  Current count of the associated timer
 @comm
        Read the timer count.<nl>
        <nl>
        Return value contains the current count of the associated timer.<s2>
        The count is incremented by the processor internal clock (see HAL
        <linkto>hal8A.htm<linkmid>hal_get_frequencies<linktail> function),
        unless the timer is configured for external clocking (then
        it is clocked by the TMRIN0 and TMRIN1 inputs, see
        <linkto>pfe85.htm<linkmid>pfe_enable_timer<linktail> function).
 @Also  hal85.htm |  hal_init_timer |
        hal87.htm |  hal_stop_timer |
        hal89.htm | hal_write_timer_count
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x88<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned short hal_read_timer_count (unsigned char timer,
                                     unsigned short far *maxcount)
{
  unsigned short retval, count;

  // read count
  asm mov ah, HAL_READ_TIMER_COUNT;
  asm mov al, timer
  asm int HAL_INT
  asm mov count, dx
  asm mov retval, AX

  if (maxcount != 0)        // Valid pointer?
  {
    *maxcount = count;
  }
  return retval;
}
#endif

/***************************************************************************/
// Write timer count
/***************************************************************************/
#ifdef _hal89_
/*
 @doc DOC_hal89_
 ---------------------------------------------------------------
 HAL: Write Timer Count
 ---------------------------------------------------------------
 @clib  hal_write_timer_count | Write timer count |
        <cfont>void hal_write_timer_count ( unsigned char timer,<nl>
        <tab><tab><tab><tab><tab><tab><tab> unsigned short counter );<efont> |
 @parm   int  | timer  | Which timer:<nl>
                 <tab>0 = Timer0 / 1 = Timer1
 @parm   int  | counter  | Value to write to 16 bit counter
 @rdesc   -- none --.
 @comm
        Preset the specified timer's count register to provided value.<nl>
        <nl>
        The timer count can be written at any time, regardless of whether
        the corresponding timer is running.
 @Also  hal85.htm |  hal_init_timer |
        hal87.htm |  hal_stop_timer |
        hal88.htm | hal_read_timer_count
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x89<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void hal_write_timer_count (unsigned char timer, unsigned short counter)
{
  // write count
  asm mov ah, HAL_WRITE_TIMER_COUNT;
  asm mov al, timer
  asm mov dx, counter
  asm int HAL_INT
}
#endif


/***************************************************************************/
// Get Frequencies
/***************************************************************************/
/*
  For The DOCLIST.EXE tool --> BeckCLib.LST

 #DOCLIST:GET_FRQ_PROCESSOR   CLIB\HW\pfe8A.htm
 #DOCLIST:GET_FRQ_TIMER       CLIB\HW\pfe8A.htm
 #DOCLIST:GET_FRQ_MAX_BAUD    CLIB\HW\pfe8A.htm
 #DOCLIST:GET_FRQ_PWD         CLIB\HW\pfe8A.htm
 #DOCLIST:GET_FRQ_TIMERBASE   CLIB\HW\pfe8A.htm
 */

#ifdef _hal8A_
/*
 @doc DOC_hal8A_
 ---------------------------------------------------------------
 HAL: Get Frequencies
 ---------------------------------------------------------------
 @clib  hal_get_frequencies | Get the specified system frequency. |
        <cfont>unsigned long hal_get_frequencies (<nl>
        <tab><tab><tab><tab><tab><tab> HW_FREQ_SELECTOR freq_select );<efont> |
 @parm_sc1x int  | freq_select  | Enumerator, which frequency to get:<ul>
          GET_FRQ_PROCESSOR = 0:<s2> Return processor frequency<nl>
          GET_FRQ_TIMER     = 1:<s2> Return maximum TMROUT square wave frequency<nl>
          GET_FRQ_MAX_BAUD  = 2:<s2> Return maximum baud rate<nl>
          GET_FRQ_PWD       = 3:<s2> PWD timer frequency<nl>
          GET_FRQ_TIMERBASE = 3:<s2> Return timer base frequency<ule>
 @parm_sc1x3_sc2x int  | freq_select  | Enumerator, which frequency to get:<ul>
          GET_FRQ_PROCESSOR = 0:<s2> Return processor frequency<nl>
          GET_FRQ_TIMER     = 1:<s2> Return maximum TMROUT square wave frequency<nl>
          GET_FRQ_MAX_BAUD  = 2:<s2> Return maximum baud rate<nl>
          GET_FRQ_TIMERBASE = 3:<s2> Return timer base frequency<ule>
 @rdesc   frequency [Hz].
 @comm  Use the timer base frequency to compute the correct timer clock divider
        value, where:<nl>
        <nl><ul><code>
            Timer frequency = timer base frequency / clock divider<ule><codee><nl>
        Use the maximum TMROUT sqare wave frequency to compute the correct timer clock divider
        value for the TMROUT, where:<nl>
        <nl><ul><code>
            TMROUT frequency = maximum TMROUT sqare wave frequency / clock divider<ule><codee>
        <nl>Use the maximum baud rate to select the correct baud rate divisor
        for the specific processor.<s2> The <cfont>baud_divider<efont> argument
        to Fossil <i>Extended line control initialization<ie>
        <linkto>../fossil/fos81.htm<linkmid>fossil_set_extctrl<linktail> function
        can be calculated based on the following equation.<nl>
        <nl><ul><code>
                 baud_divider = maximum baud rate / desired baud rate<ule><codee>
 @Also  hal85.htm |  hal_init_timer |
        ../fossil/fos81.htm | fossil_set_extctrl  |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x8A<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned long hal_get_frequencies(HW_FREQ_SELECTOR freq_select )
{
  unsigned long frequency ;

  // get frequencies
  _AL = (unsigned char) freq_select ;
  asm mov ah, HAL_GET_FREQUENCIES;
  asm int HAL_INT

  asm mov WORD PTR frequency+2, dx
  asm mov WORD PTR frequency, AX

  return frequency ;
}
#endif


/***************************************************************************/
// Set Duty Cycle Waveform
/***************************************************************************/
#ifdef _hal8B_
/*
 @doc DOC_hal8B_
 ---------------------------------------------------------------
 HAL: Set Timer Duty Cycle Waveform
 ---------------------------------------------------------------
 @clib  hal_set_duty_cycle_waveform | Set timer duty cycle waveform |
        <cfont>void hal_set_duty_cycle_waveform ( unsigned char timer,<nl>
        <tab><tab><tab><tab><tab><tab><tab><tab>&nbsp;&nbsp; short mode,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; unsigned short clock_divider );<efont> |
 @parm   int  | timer  | Which timer:<nl>
                 <tab>0 = Timer0 / 1 = Timer1
 @parm   int  | mode  | 0=disable duty cycle<nl>
            1=enable duty cycle
 @parm   int  | clock_divider  | Alternate clock divider
        (if <code>mode<codee> = 1)
 @rdesc   -- none --.
 @comm
        Set the duty cycle waveform of specified timer.<nl>
        <nl>
        Use this function to modify the timer waveform behavior.<s2>
        For example a 50% duty cycle waveform can be generated by specifying
        here an <i>alternate clock divider<ie> value in
        <code>clock_divider<codee> that is the same value as was used for
        the main <i>clock divider<ie> value set in the Timer
        Initialization <linkto>hal85.htm<linkmid>hal_init_timer<linktail>
        function call.<nl>
        <nl>
        Please note that the timer frequency will change if you use this
        function.<s2>If you disable the duty cycle, the timer output will
        no longer generate a rectangle signal.<s2> When duty cycle mode
        is disabled, the TMROUT pin switches low for only one clock cycle
        after the maximum count is reached.
 @Also  hal85.htm |  hal_init_timer |  |  |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x8B<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void hal_set_duty_cycle_waveform( unsigned char timer,
                                  short mode,
                                  unsigned short clock_divider )
{
  // ser dury cycle waveform
  asm mov ah, HAL_SET_DUTY_CYCLE_WAVEFORM;
  asm mov al, timer
  asm mov dx, mode
  asm mov CX, clock_divider
  asm int HAL_INT
}
#endif

/***************************************************************************/
// Read single pio
/***************************************************************************/
#ifdef _hal8C_
/*
 @doc DOC_hal8C_
 ---------------------------------------------------------------
 HAL: Read Specific I/O Pin
 ---------------------------------------------------------------
 @clib  hal_read_pio | Read specific I/O pin. |
        <cfont>unsigned char hal_read_pio ( unsigned char pio );<efont> |
 @parm_sc1x  unsigned char | pio | IPC@CHIP&reg; PIO No. [0..13]
 @parm_sc1x3 unsigned char | pio | IPC@CHIP&reg; PIO No. [0..24, 26..31]
 @parm_sc2x  unsigned char | pio | IPC@CHIP&reg; PIO No. [0..2, 9..13, 18..23, 27..28, 31]
 @rdesc 0 PIO pin is low, 1 PIO pin is high
 @comm  Read specified programmable I/O pin.
 @Also  hal8D.htm |  hal_write_pio |
        hal82.htm |  hal_read_pios |
        pfe82.htm | pfe_enable_pio
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x8C<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned char hal_read_pio (unsigned char pio)
{
  asm mov ah, HAL_READ_SPECIFIC_PIO
  asm mov al, pio
  asm int HAL_INT

  if (_AX) return 1;
  else     return 0;
}
#endif

/***************************************************************************/
// Write single pio
/***************************************************************************/
#ifdef _hal8D_
/*
 @doc DOC_hal8D_
 ---------------------------------------------------------------
 HAL: Write to Specific I/O Pin
 ---------------------------------------------------------------
 @clib  hal_write_pio | Write to specific I/O pin. |
        <cfont>void hal_write_pio ( unsigned char pio, unsigned short value );<efont> |
 @parm_sc1x  unsigned char | pio | IPC@CHIP&reg; PIO No. [0..13]
 @parm_sc1x3 unsigned char | pio | IPC@CHIP&reg; PIO No. [0..24, 26..31]
 @parm_sc2x  unsigned char | pio | IPC@CHIP&reg; PIO No. [0..2, 9..13, 18..23, 27..28, 31]
 @parm  unsigned short | value | 0 ==<gt> set PIO to low<nl>
                         non-zero ==<gt> set PIO to high
 @rdesc   -- none --.
 @comm  Write to a specified programmable I/O pin.<s2>
        Only PIO pins that are defined as outputs can be written.
 @Also  hal8C.htm |  hal_read_pio |
        hal83.htm |  hal_write_pios |
        pfe82.htm | pfe_enable_pio
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x8D<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void hal_write_pio (unsigned char pio, unsigned short value)
{
  asm mov ah, HAL_WRITE_SPECIFIC_PIO
  asm mov al, pio
  asm mov dx, value
  asm int HAL_INT
}
#endif


/***************************************************************************/
// Give End of Interrupt (EOI)
/***************************************************************************/
#ifdef _hal8E_
/*
 @doc DOC_hal8E_
 ---------------------------------------------------------------
 HAL: Give EOI
 ---------------------------------------------------------------
 @clib  hal_give_eoi | Give EOI to interrupt controller. |
        <cfont>void hal_give_eoi ( unsigned char intr_no );<efont> |
 @parm  unsigned char | intr_no | Type (0=INT0 ... 4=INT4)
 @rdesc -- none --.
 @comm  Give End-Of-Interrupt for INT0-INT4.<nl>
        <nl>
        When installing a interrupt service routine through HW API, it's not
        neccessay to call this function, because the HW API does it for you.<nl>
        <nl>
        This function is provided for writing own interrupt service routines
        without the HAL
        <linkto>hal84.htm<linkmid>hal_install_isr<linktail> function.<s2>
        Especially when using cascaded mode of the interrupt controller
        with INT0/INTA, this function is needed for generating an EOI for INT0.

 @Also  pfe89.htm |  pfe_enable_int_cascade_mode |   |   |   |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x8E<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | n/a   | V1.00
*/
void hal_give_eoi( unsigned char intr_no )
{
  // give EOI
  asm mov ah, HAL_GIVE_EOI;
  asm mov al, intr_no
  asm int HAL_INT
}
#endif

/***************************************************************************/
// Set watchdog mode
/***************************************************************************/
#ifdef _hal90_
/*
 @doc DOC_hal90_
 ---------------------------------------------------------------
 HAL: Get/Set Watchdog Mode
 ---------------------------------------------------------------
 @clib  hal_set_watchdog_mode | Get/Set watchdog mode. |
        <cfont>unsigned char hal_set_watchdog_mode ( unsigned char mode );<efont> |
 @parm  unsigned char | mode  |
            HAL_WATCHDOG_MODE_GET = 0: Only get mode<nl>
            HAL_WATCHDOG_MODE_USER = 2: Watchdog will be triggered by user program<nl>
            HAL_WATCHDOG_MODE_RTOS = 3: Watchdog will be triggered by @CHIP-RTOS (default)<nl>
            HAL_WATCHDOG_MODE_MANAGER = 4: Watchdog will be triggered by watchdog manager (SC1x3/SC2x only)
 @rdesc  Watchdog mode:<ul>
            HAL_WATCHDOG_MODE_USER = 2: Watchdog will be triggered by user program<nl>
            HAL_WATCHDOG_MODE_RTOS = 3: Watchdog will be triggered by @CHIP-RTOS (default)<nl>
            HAL_WATCHDOG_MODE_MANAGER = 4: Watchdog will be triggered by watchdog manager (SC1x3/SC2x only)<ule>
 @comm  Get or set the watchdog mode.<nl>
        <nl>
        If you select the <i>User Program<ie> mode, you must cyclically
        call the HAL <linkto>hal91.htm<linkmid>hal_refresh_watchdog<linktail>
        function before the watchdog timeout period (see below) expires.<nl>
        In @CHIP-RTOS mode, the @CHIP-RTOS performs the watchdog
        strobing provided that the system's timer interrupt is allowed to
        execute. Beware that excessive interrupt masking periods can lead
        to system resets.<nl>
        If you select the <i>Manager<ie> mode, the manager will refresh
        the watchdog every 200 ms provided that all tasks that have signed
        on to the manager have refreshed the manager in time. If one task fails
        to refresh the manager in time, the manager will stop to refresh the
        hardware watchdog. Note that from that point it will still take the
        watchdog timeout period (see below) before the watchdog hardware resets
        the system.
 @commtarget SC1x |  The watchdog timeout period on SC11/SC12/SC13 is 800 ms.
 @commtarget SC1x3/SC2x | The watchdog timeout period on SC1x3/SC2x is 699 ms.

 @Also  hal91.htm | hal_refresh_watchdog |  |  |  |
 @Also  hal94.htm | hal_watchdog_manager_sign_on |  |  |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x90<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
unsigned char hal_set_watchdog_mode (unsigned char mode)
{
  // set watchdog mode
  asm mov ah, HAL_GET_SET_WATCHDOG_MODE;
  asm mov al, mode
  asm int HAL_INT
  return _AX ;
}
#endif

/***************************************************************************/
// Refresh watchdog
/***************************************************************************/
#ifdef _hal91_
/*
 @doc DOC_hal91_
 ---------------------------------------------------------------
 HAL: Refresh Watchdog
 ---------------------------------------------------------------
 @clib  hal_refresh_watchdog | Refresh watchdog. |
        <cfont>void hal_refresh_watchdog ( void );<efont> |
 @parm   void  |  | -- none --
 @rdesc  -- none --.
 @commtarget SC1x | Strobe the hardware watchdog to reset its 800 ms timeout period.<nl>
        <nl>
        If the watchdog is in <i>User Program<ie> mode, this function must be
        called at least every 800 ms to prevent a CPU reset due to watchdog
        timeout.
 @commtarget SC1x3/SC2x | Strobe the hardware watchdog to reset its 699 ms timeout period.<nl>
        <nl>
        If the watchdog is in <i>User Program<ie> mode, this function must be
        called at least every 699 ms to prevent a CPU reset due to watchdog
        timeout.
 @Also  hal90.htm |  hal_set_watchdog_mode |  |   |   |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x91<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void hal_refresh_watchdog (void)
{
  // refresh watchdog
  asm mov ah, HAL_REFRESH_WATCHDOG;
  asm int HAL_INT
}
#endif


/***************************************************************************/
// Sign on to watchdog manager
/***************************************************************************/
#ifdef _hal94_
/*
  @doc DOC_hal94_
  ---------------------------------------------------------------
  HAL: Sign on to watchdog manager
  ---------------------------------------------------------------
  @clib         hal_watchdog_manager_sign_on | Sign on to watchdog manager |
                <cfont>int hal_watchdog_manager_sign_on(unsigned long period);<efont> |
  @parm         unsigned | period | Period of time (in ms) in which the calling process
                                    guarantees to refresh the watchdog manager again.
                                    The maximum period is 6553400 ((USHRT_MAX - 1) * 100).
  @rdesc        >= 0 - Handle to be used with other watchdog manager functions<nl>
                -1 - Too many processes have already signed on to the watchdog manager<nl>
                -2 - Period is too high
  @comm         Signs on a process to the watchdog manager. If the watchdog mode
                is HAL_WATCHDOG_MODE_MANAGER, the watchdog manager will refresh
                the hardware watchdog, but only if all processes that have signed
                on have refreshed the watchdog manager in time.
  @Also         hal90.htm | hal_set_watchdog_mode |  |  |  |
  @Also         hal95.htm | hal_watchdog_manager_refresh |  |  |  |
  @Also         hal96.htm | hal_watchdog_manager_sign_off |  |  |  |
  @rtos         This library function invokes a RTOS software interrupt.
                Refer to this RTOS API function's
                <linkto>../../hardware.htm#0xA10x94<linkmid>documentation<linktail>
                for more details.
  @target       SC12  | SC13 | SC11 | SC1x3 | SC2x
  @version      n/a   | n/a  | n/a  | V1.50 | V1.50
  @target_clib  V2.22
*/
int _cdecl hal_watchdog_manager_sign_on(unsigned long period)
{
  _DX = FP_SEG((void *)period);
  _CX = FP_OFF((void *)period);
  _AH = HAL_WATCHDOG_MANAGER_SIGN_ON;
  asm int HAL_INT
  return _AX;
}
#endif


/***************************************************************************/
// Refresh watchdog manager
/***************************************************************************/
#ifdef _hal95_
/*
  @doc DOC_hal95_
  ---------------------------------------------------------------
  HAL: Refresh watchdog manager
  ---------------------------------------------------------------
  @clib         hal_watchdog_manager_refresh | Refresh watchdog manager |
                <cfont>int hal_watchdog_manager_refresh(unsigned handle, unsigned long period);<efont> |
  @parm         unsigned | handle | Watchdog manager handle
  @parm         unsigned | period | Period of time (in ms) in which the calling
                                    process guarantees to refresh the watchdog manager again.
                                    The maximum period is 6553400 ((USHRT_MAX - 1) * 100).
  @rdesc        0 - Success<nl>
                -1 - Illegal handle<nl>
                -2 - Period is too high
  @Also         hal94.htm | hal_watchdog_manager_sign_on |  |  |  |
  @Also         hal96.htm | hal_watchdog_manager_sign_off |  |  |  |
  @rtos         This library function invokes a RTOS software interrupt.
                Refer to this RTOS API function's
                <linkto>../../hardware.htm#0xA10x95<linkmid>documentation<linktail>
                for more details.
  @target       SC12  | SC13 | SC11 | SC1x3 | SC2x
  @version      n/a   | n/a  | n/a  | V1.50 | V1.50
  @target_clib  V2.22
*/
int _cdecl hal_watchdog_manager_refresh(unsigned handle,
                                        unsigned long period)
{
  _DX = FP_SEG((void *)period);
  _CX = FP_OFF((void *)period);
  _BX = handle;
  _AH = HAL_WATCHDOG_MANAGER_REFRESH;
  asm int HAL_INT
  return _AX;
}
#endif


/***************************************************************************/
// Sign off from watchdog manager
/***************************************************************************/
#ifdef _hal96_
/*
  @doc DOC_hal96_
  ---------------------------------------------------------------
  HAL: Sign off from watchdog manager
  ---------------------------------------------------------------
  @clib         hal_watchdog_manager_sign_off | Sign off from watchdog manager |
                <cfont>int hal_watchdog_manager_sign_off(unsigned handle);<efont> |
  @parm         unsigned | handle | Watchdog manager handle
  @rdesc        0 - Success<nl>
                -1 - Illegal handle
  @Also         hal94.htm | hal_watchdog_manager_sign_on |  |  |  |
  @Also         hal95.htm | hal_watchdog_manager_refresh |  |  |  |
  @rtos         This library function invokes a RTOS software interrupt.
                Refer to this RTOS API function's
                <linkto>../../hardware.htm#0xA10x96<linkmid>documentation<linktail>
                for more details.
  @target       SC12  | SC13 | SC11 | SC1x3 | SC2x
  @version      n/a   | n/a  | n/a  | V1.50 | V1.50
  @target_clib  V2.22
*/
int _cdecl hal_watchdog_manager_sign_off(unsigned handle)
{
  _BX = handle;
  _AH = HAL_WATCHDOG_MANAGER_SIGN_OFF;
  asm int HAL_INT
  return _AX;
}
#endif


/***************************************************************************/
// Mask/Unmask Interrupt
/***************************************************************************/
#ifdef _hal92_
/*
 @doc DOC_hal92_
 ---------------------------------------------------------------
 HAL: Mask/Unmask Interrupt
 ---------------------------------------------------------------
 @clib  hal_mask_int | Mask and Unmask an external Interrupt Request. |
        <cfont>void hal_mask_int ( unsigned short irq, unsigned char mask );<efont> |
 @parm_sc1x  unsigned short | irq | HAL interrupt number from following list:<ul>
                     0 = INT0 (external)<nl>
                     1 = Network controller (internal)<nl>
                     2 = INT2 (external)<nl>
                     3 = INT3 (external)<nl>
                     4 = INT4 (external)<nl>
                     5 = INT5 (external) / DMA Interrupt Channel 0 (if DMA is used)<nl>
                     6 = INT6 (external) / DMA Interrupt Channel 1 (if DMA is used)<nl>
                     7 = reserved<nl>
                     8 = Timer0 (internal)<nl>
                     9 = Timer1 (internal)<nl>
                     10 = Timer 1ms (internal)<nl>
                     11 = Serial port 0 (internal)<nl>
                     12 = Serial port 1 (internal)<nl>
                     13 = DMA Interrupt Channel 2 (internal, not on SC12)<nl>
                     14 = DMA Interrupt Channel 3 (internal, not on SC12)<nl>
                     15 = NMI (Not maskable!)<nl>
 @parm_sc1x3_sc2x unsigned short | irq | HAL interrupt number from following list:<ul>
                     0 = Network controller 0 (internal)<nl>
                     1 = INT1 (external) / Network controller 1 (internal)<nl>
                     2 = SPI controller (internal) / I2C controller (internal)<nl>
                     3 = INT3 (external) / USB controller (internal)<nl>
                     4 = Serial port 2 (internal)<nl>
                     5 = DMA Interrupt Channel 0<nl>
                     6 = DMA Interrupt Channel 1<nl>
                     7 = INT5 (external) / Serial port 3 (internal)<nl>
                     8 = Timer0 (internal)<nl>
                     9 = Timer1 (internal)<nl>
                     10 = Timer 1ms (internal)<nl>
                     11 = Serial port 0 (internal)<nl>
                     12 = Serial port 1 (internal)<nl>
                     13 = DMA Interrupt Channel 2<nl>
                     14 = DMA Interrupt Channel 3<nl>
                     15 = NMI (Not maskable)<nl>
                     16 = CAN0 controller (internal) / CAN1 controller (internal)<nl>
 @parm   unsigned char  | mask | 1: Mask IRQ<nl> 0: Unmask IRQ
 @rdesc  -- none --.
 @commtarget SC1x |
     Some interrupts share the same mask bit.<s2> If you mask one of them,
     the other interrupts which are assigned to the same bit are also
     masked.<s2> Here are the groups which are masked together:<nl><nl>
            <ul>
            Timer0, Timer1, Timer 1ms<nl>
            DMA0, INT5<nl>
            DMA1, INT6<nl>
            <ule>
 @commtarget SC1x3/SC2x |
     Some interrupts share the same mask bit.<s2> If you mask one of them,
     the other interrupts which are assigned to the same bit are also
     masked.<s2> Here are the groups which are masked together:<nl><nl>
            <ul>
            Timer0, Timer1, Timer 1ms<nl>
            INT1 / Network controller 1<nl>
            SPI controller / I2C controller<nl>
            INT3 / USB controller<nl>
            INT5 / Serial port 2<nl>
            CAN0 controller / CAN1 controller<nl>
            <ule>
 @comm
     <bold>CAUTION:<bolde><nl>
     <ul>
     Masking any of the three timer interrupts will suspend the @CHIP-RTOS
     1000 Hz real-time interrupt, essential for system operation.<s2>
     Consequently this mask period should be very brief, if used at all.
     <ule>
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10x92<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.10 | V1.00 | V1.00 | V0.90 | V1.00
*/
void hal_mask_int (unsigned short irq, unsigned char mask)
{
  // refresh watchdog
  asm mov ah, HAL_MASK_INT;
  asm mov al, mask
  asm mov dx, irq
  asm int HAL_INT
}
#endif


/***************************************************************************/
// Read block from databus
/***************************************************************************/
#ifdef _halA0_
/*
 @doc DOC_halA0_
 ---------------------------------------------------------------
 HAL: Block Read Data Bus
 ---------------------------------------------------------------
 @clib  hal_readblock_bus | Block read data bus. |
        <cfont>void hal_readblock_bus ( unsigned short adr0, unsigned short adr1,<nl>
        <tab><tab><tab><tab><tab><tab> unsigned char far *buf, unsigned short cnt );<efont> |
 @depr_external Use inport or inportb function from dos.h instead!
 @parm   unsigned short | adr0  | First address
 @parm   unsigned short  | adr1  | Second address
 @parm   unsigned char far *  | buf  | Output parameter: destination buffer
 @parm   unsigned short  | cnt  | Number of bytes to read into <code>buf<codee>
 @rdesc   -- none --.
 @comm  IF <code>adr0<codee> != <code>adr1<codee>, this function will
        alternate reads between the two addresses until <code>cnt<codee>
        bytes are read, starting at first address.<s2>
        Set <code>adr0<codee> == <code>adr1<codee> if you want to read
        from only a single address.
 @Also  halA1.htm |  hal_writeblock_bus |
        hal80.htm |  hal_read_bus |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10xA0<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | n/a   | n/a
*/
void hal_readblock_bus (unsigned short adr0, unsigned short adr1,
                        unsigned char far *buf, unsigned short cnt)
{
  // read data bus
  _ES = FP_SEG(buf);
  _BX = FP_OFF(buf);
  asm mov ah, HAL_BLOCK_READ_DATA_BUS;
  asm mov DI, adr0
  asm mov SI, adr1
  asm mov CX, cnt
  asm int HAL_INT
}
#endif

/***************************************************************************/
// Write block to databus
/***************************************************************************/
#ifdef _halA1_
/*
 @doc DOC_halA1_
 ---------------------------------------------------------------
 HAL:  Block Write Data Bus
 ---------------------------------------------------------------
 @clib  hal_writeblock_bus | Block write data bus. |
        <cfont>void hal_writeblock_bus ( unsigned short adr0, unsigned short adr1,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; const unsigned char far *buf,<nl>
        <tab><tab><tab><tab><tab><tab>&nbsp; unsigned short cnt );<efont> |
 @depr_external Use outport or outportb function from dos.h instead!
 @parm   unsigned short | adr0  | First address
 @parm   unsigned short | adr1  | Second address
 @parm   unsigned char far * | buf  | Input parameter: data source buffer
 @parm   unsigned short | cnt  | Number of bytes to output from <code>buf<codee>
 @rdesc   -- none --.
 @comm
        IF <code>adr0<codee> != <code>adr1<codee>, this function will
        alternate between writes to the first and second address, starting
        at first address.<nl>
        <nl>
        Set <code>adr0<codee> == <code>adr1<codee> if you want all data
        written to a single address.
 @Also  halA0.htm |  hal_readblock_bus |
        hal81.htm |  hal_write_bus | |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10xA1<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | n/a   | n/a
*/
void hal_writeblock_bus (unsigned short adr0, unsigned short adr1,
                         const unsigned char far *buf, unsigned short cnt)
{
  // write data bus
  _ES = FP_SEG(buf);
  _BX = FP_OFF(buf);
  asm mov ah, HAL_BLOCK_WRITE_DATA_BUS;
  asm mov DI, adr0
  asm mov SI, adr1
  asm mov CX, cnt
  asm int HAL_INT
}
#endif


/***************************************************************************/
//  DMA Control Data Structure
/***************************************************************************/
/*
  For The DOCLIST.EXE tool --> BeckCLib.LST

 #DOCLIST:Dma_Info_      CLIB\HW\dmaInfo.htm
 #DOCLIST:Dma_Info       CLIB\HW\dmaInfo.htm

 @doc DOC_dmaInfo_
 ---------------------------------------------------------------
 HAL: DMA Info
 ---------------------------------------------------------------
 @cstruc  Dma_Info data structure | DMA Info data structure |
        <cfont>typedef struct Dma_Info_<nl>
        {<efont> |
        <cfont>
        <tab>unsigned <cfont>count<efont>;<nl>
        <nl>
        <tab>union<nl>
        <tab>{<nl>
        <tab><tab>void far *mem;<nl>
        <tab><tab>unsigned int io;<nl>
        <tab>}<nl>
        <tab>src;<nl>
        <nl>
        <tab>union<nl>
        <tab>{<nl>
        <tab><tab>void far *mem;<nl>
        <tab><tab>unsigned int io;<nl>
        <tab>}<nl>
        <tab>dest;<nl>
        <nl>
        <tab>unsigned ctrl_reg;<nl> |
        }  Dma_Info ;
        <efont>
        <nl>
        <nl>
 @element   int  | count  | DMA counter (bytes which have to be transfered)
 @element   int  | src  | Data source
 @element   int  | dest  | Data destination
 @element   int  | ctrl_reg  | <linktag CTRL_REG>Control Register:<ul>
        Bit 0:  1=Priority for the channel / 0=Priority for the other channel<nl>
        Bit 1:  1=Source synchronized / 0=No source synchronization<nl>
        Bit 2:  1=Destination synchronized / 0=No destination synchronization<nl>
        Bit 3:  1=Use interrupt at end of transfer / 0=do not use an interrupt<nl>
        Bit 4:  must be set to '1'<nl>
        Bit 5:  1=Source address increment / 0=No increment of source address<nl>
        Bit 6:  1=Source address decrement / 0=No decrement of source Address<nl>
        Bit 7:  1=Source is in memory space / 0=Source is in IO space<nl>
        Bit 8:  1=Destination address increment /
                0=No increment of destination address<nl>
        Bit 9:  1=Destination address decrement / 0=No decrement of destination address<nl>
        Bit 10: 1=Destination is in memory space / 0=Destination is in IO space<nl>
        Bit 11: 1=Word Transfer / 0=Byte Transfer<nl>
 @comm  The source and destination pointers are either far pointers to memory
        or a 16 bit I/O address.<s2>If <code>ctrl_reg<codee> bit 7
        (<code>DMA_SRCMEM<codee>) is set
        then <code>src<codee> is a far memory pointer, otherwise it is a
        16 bit I/O address.<s2>Likewise if <code>ctrl_reg<codee> bit 10
        (<code>DMA_DESTMEM<codee>) is set
        then <code>dest<codee> is a far memory pointer, otherwise it is a
        16 bit I/O address.
 @Also  halB0.htm |  hal_start_dma |
        halB2.htm |  hal_get_dma_info |  |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | n/a
*/

/***************************************************************************/
// Start DMA
/***************************************************************************/
#ifdef _halB0_
/*
 @doc DOC_halB0_
 ---------------------------------------------------------------
 HAL: Start DMA Mode
 ---------------------------------------------------------------
 @clib  hal_start_dma | Start DMA mode. |
        <cfont>int hal_start_dma ( unsigned char channel,<nl>
        <tab><tab><tab><tab><tab>const Dma_Info * dmaInfo );<efont> |
 @parm_sc1x unsigned char | channel  | DMA channel:<ul>
                     0 = DRQ0<nl>
                     1 = DRQ1<ule>
 @parm_sc1x3 unsigned char | channel  | DMA channel:<ul>
                     0 = DRQ0<nl>
                     1 = DRQ1<nl>
                     2 = DRQ2<nl>
                     3 = DRQ3<ule>
 @parm  int  | dmaInfo  | Pointer to
        <linkto>dmaInfo.htm<linkmid>Dma_Info<linktail> data structure
         containing DMA setup information.
 @rdesc 0:<s2> Success<nl>
          -1:<s2> Invalid DMA channel<nl>
          -2:<s2> DMA channel used for serial interface<nl>
 @comm  This function configures the specified DMA channel based on the
        contents of the provided <code>dmaInfo<codee>
        <linkto>dmaInfo.htm<linkmid>structure<linktail>.<s2>  Then the
        DMA channel is activated.
 @Also  halB1.htm |  hal_stop_dma |
        halB2.htm |  hal_get_dma_info |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10xB0<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | n/a
*/
int hal_start_dma( unsigned char channel, const Dma_Info *dmaInfo )
{
  unsigned long src;
  unsigned long dest;

  // read Source Address
  if ( dmaInfo->ctrl_reg & DMA_SRCMEM )
  {
      // Form linear address based on segmented address
    src  = ((unsigned long)FP_SEG(dmaInfo->src.mem) << SEG_SHIFT)
         + FP_OFF(dmaInfo->src.mem);
  }
  else
  {
    src = dmaInfo->src.io;
  }

  // read Destination Address
  if ( dmaInfo->ctrl_reg & DMA_DESTMEM )
  {
      // Form linear address based on segmented address
    dest  = ((unsigned long)FP_SEG(dmaInfo->dest.mem) << SEG_SHIFT)
          + FP_OFF(dmaInfo->dest.mem);
  }
  else
  {
    dest = dmaInfo->dest.io;
  }

  // start DMA
  _CX = dmaInfo->count;
  _DX = dmaInfo->ctrl_reg;

  asm { LEA DI,dest } ;
  asm { LEA SI,src } ;
  asm { MOV bx,SS } ;   // Now BX:SI = &src (on stack)
  asm { MOV ES,bx } ;   // Now ES:DI = &dest (on stack)
  _AL = channel;
  _AH = HAL_START_DMA;

  asm int HAL_INT

  return _AX;
}
#endif

/***************************************************************************/
// Stop DMA
/***************************************************************************/
#ifdef _halB1_
/*
 @doc DOC_halB1_
 ---------------------------------------------------------------
 HAL: Stop DMA Transfer
 ---------------------------------------------------------------
 @clib  hal_stop_dma | Stop DMA transfer. |
        <cfont>int hal_stop_dma ( unsigned char channel );<efont> |
 @parm_sc1x  unsigned char | channel  | DMA channel:<nl>
           0 = DRQ0<nl>
           1 = DRQ1<nl>
 @parm_sc1x3 unsigned char | channel  | DMA channel:<ul>
           0 = DRQ0<nl>
           1 = DRQ1<nl>
           2 = DRQ2<nl>
           3 = DRQ3<ule>
 @rdesc   0:<s2> Success<nl>
          -1:<s2> Invalid DMA channel<nl>
          -2:<s2> DMA channel used for serial interface<nl>
 @comm
      Stops a DMA transfer (disables the DMA controller).<s2> The transfer
      could be continued by first calling
      <linkto>halB2.htm<linkmid>hal_get_dma_info<linktail> to gather
      the current DMA state and then passing this state information
      to <linkto>halB0.htm<linkmid>hal_start_dma<linktail> to
      resume the transfer.
 @Also  halB0.htm |  hal_start_dma |
        halB2.htm |  hal_get_dma_info |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10xB1<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.02 | V1.00 | V1.00 | V0.90 | n/a
*/
int hal_stop_dma( unsigned char channel )
{
  asm mov ah, HAL_STOP_DMA
  asm mov al, channel
  asm int HAL_INT
  return _AX ;
}
#endif


/***************************************************************************/
// Get DMA Info
/***************************************************************************/
#ifdef _halB2_
/*
 @doc DOC_halB2_
 ---------------------------------------------------------------
 HAL: Get DMA Info
 ---------------------------------------------------------------
 @clib  hal_get_dma_info | Get DMA info. |
        <cfont>int hal_get_dma_info ( unsigned char channel,<nl>
        <tab><tab><tab><tab><tab><s3>Dma_Info * dmaInfo );<efont> |
 @parm_sc1x  unsigned char | channel  | DMA channel:<ul>
                     0 = DRQ0<nl>
                     1 = DRQ1<ule>
 @parm_sc1x3 unsigned char | channel  | DMA channel:<ul>
                     0 = DRQ0<nl>
                     1 = DRQ1<nl>
                     2 = DRQ2<nl>
                     3 = DRQ3<ule>
 @parm   int  | dmaInfo  | Output Parameter:<s2> Pointer to
        <linkto>dmaInfo.htm<linkmid>Dma_Info<linktail> data structure
         which will be set by this API with DMA state information.
 @rdesc   Existing DMA control
        <linkto>dmaInfo.htm#CTRL_REG<linkmid>register<linktail> bit field.
 @comm
        The DMA is momentarily disabled during reading of status, and then
        restored to the enable state it was at.
 @Also  halB0.htm |  hal_start_dma |
        halB1.htm |  hal_stop_dma |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10xB2<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | n/a
*/
int hal_get_dma_info( unsigned char channel, Dma_Info *dmaInfo )
{
  int dma_status ;
  unsigned long src;
  unsigned long dest;

  // Get DMA Info
  asm { LEA DI,dest } ;
  asm { LEA SI,src } ;
  asm { MOV bx,SS } ;   // Now BX:SI = &src (on stack)
  asm { MOV ES,bx } ;   // Now ES:DI = &dest (on stack)
  _AL = channel;
  _AH = HAL_GET_DMA_INFO;

  asm int HAL_INT

  dma_status = _AX ;
  dmaInfo->ctrl_reg = _DX ;
  dmaInfo->count    = _CX ;

  // read source Address
  if ( dmaInfo->ctrl_reg & DMA_SRCMEM )
  {
        // Translate linear address to a "huge" segmented address pointer.
     dmaInfo->src.mem  = MK_FP(
         (unsigned)(src >> SEG_SHIFT),     // segment part
         ((unsigned)src &  SEG_MASK)       // Offset part
                              ) ;
  }
  else dmaInfo->src.io = (unsigned)src;

  // read dest Address
  if ( dmaInfo->ctrl_reg & DMA_DESTMEM )
  {
        // Translate linear address to a "huge" segmented address pointer.
     dmaInfo->dest.mem  = MK_FP(
         (unsigned)(dest >> SEG_SHIFT),     // segment part
         ((unsigned)dest &  SEG_MASK)       // Offset part
                              ) ;
  }
  else dmaInfo->dest.io = (unsigned)dest;

  return dma_status;
}
#endif

/***************************************************************************/
//  Non Volatile Data REMOP Data Structure
/***************************************************************************/
/*
  For The DOCLIST.EXE tool --> BeckCLib.LST

 #DOCLIST:_REMOP         CLIB\HW\Remop.htm
 #DOCLIST:Remop          CLIB\HW\Remop.htm
 #DOCLIST:REMOP_ENTRY    CLIB\HW\Remop.htm

 @doc DOC_REMOP_
 ---------------------------------------------------------------
 HAL: Remop
 ---------------------------------------------------------------
 @cstruc  Remop data structure | Non Volatile data control. |
        <cfont>typedef struct _REMOP<nl>
        {<efont> |
        <cfont>
        <tab>unsigned entries;<nl>
        <tab>unsigned segment;<nl>
        <nl>
        <tab>struct REMOP_ENTRY<nl>
        <tab>{<nl>
        <tab><tab>unsigned offs;<nl>
        <tab><tab>unsigned size;<nl>
        <tab><tab>unsigned maxsize;<nl>
        <tab><tab>unsigned elemsize;<nl>
        <tab><tab>unsigned distance;<nl>
        <tab>}x[MAX_RETENTIVE_AREAS];<nl><nl>
        }  Remop ;<efont> |
 @element   int  | entries  | Number of entries in struct
            <code>REMOP_ENTRY x<codee>.
 @element   int  | segment  | Common segment portion of far addresses.
 @element   int  | x  | Array of REMOP_ENTRY data structures.<nl>
          <code>MAX_RETENTIVE_AREAS<codee> may be either defined by
          user's application or left at default value of 10.<nl>
          Elements of <code>x<codee> follow.
 @element   int  | x.offs  | Offset portion of far pointer.
 @element   int  | x.size  | Number of bytes.
 @element   int  | x.maxsize   | Obsolete, set to 0.
 @element   int  | x.elemsize  | Number of bytes per data element.
 @element   int  | x.distance  | Distance to next data element (must be <gt>= elemsize).
 @comm   This structure is used to inform the system where non-volatile
         data resides.<s2> Note that the referenced non-volatile data 
         must all reside in the same memory segment.
 @Also  halC0.htm |  hal_init_non_volatile_data |
        halC1.htm |  hal_save_non_volatile_data |  |
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/

/***************************************************************************/
// Init/Restore Non Volatile Data
/***************************************************************************/
#ifdef _halC0_
/*
 @doc DOC_halC0_
 ---------------------------------------------------------------
 HAL: Initialize/Restore Non-Volatile Data
 ---------------------------------------------------------------
 @clib  hal_init_non_volatile_data | Initialize/Restore non-volatile data. |
        <cfont>int hal_init_non_volatile_data ( Remop far * remop );<efont> |
 @parm   int  | remop  | Pointer to
        <linkto>remop.htm<linkmid>Remop<linktail> data structure.
 @rdesc  Success: AX = 0<nl>
         Failure: AX <lt> 0, Could not create file<nl>
 @comm
        This function initializes and restore non-volatile data.<s2>
        Use it to tell the @CHIP-RTOS where your variables are located,
        which should be saved.<s2> The function will also reload their saved
        values, if available.<nl>
 @commtarget SC1x |
        The non-volatile (remanent) data is stored in
        <code>A:\rema.bin<codee> file.
 @commtarget SC1x3/SC2x |
        The non-volatile (remanent) data is stored in a reserved
        flash memory area. The maximum size is approx. 8 KB.
 @comm  Call this function at the beginning of your program.<nl><nl>
        The <linkto>remop.htm<linkmid>Remop<linktail> structure reference
        by <code>remop<codee> must be static.<s2> (This function does not
        make a copy of the structure's content.)<nl>
        <nl>
        The total size of the non-volatile data set must match that which
        was saved.<s2>  Otherwise the data set will be zeroed.
 @Also   halC1.htm |  hal_save_non_volatile_data |
         halC2.htm |  hal_get_reboot_reason |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10xC0<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int hal_init_non_volatile_data( const Remop far *remop )
{
   asm les bx, remop
   asm mov ah, HAL_INIT_REST_NON_VOLATILE_DATA
   asm int HAL_INT
   return _AX ;
}
#endif


/***************************************************************************/
// Save Non Volatile Data
/***************************************************************************/
#ifdef _halC1_
/*
 @doc DOC_halC1_
 ---------------------------------------------------------------
 HAL: Save Non-Volatile Data
 ---------------------------------------------------------------
 @clib  hal_save_non_volatile_data | Save non-volatile data. |
        <cfont>void hal_save_non_volatile_data ( void );<efont> |
 @parm  void  |   | -- none --
 @rdesc   -- none --.
 @comm  Call this function on exit from your program and in your 
       <linkto>../../config.htm#DEVICE_PFI_ENABLE<linkmid>PFI<linktail>
        (Power Fail Interrupt) 
        <linkto>hal84.htm<linkmid>handler<linktail>.<s2> Your hardware around the
        IPC@CHIP&reg; must support the PFAIL signal, so that the IPC@CHIP&reg; can
        generate an PFI/NMI sufficiently in advance of power loss to the CPU.<nl>
 @commtarget SC1x | <bold>Reminder<bolde>:<s2> The DK40 does not support the PFAIL signal.
 @Also  halC0.htm |  hal_init_non_volatile_data | 
        hal84.htm |  hal_install_isr |
        |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10xC1<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
void hal_save_non_volatile_data(void)
{
   asm mov ah, HAL_SAVE_NON_VOLATILE_DATA
   asm int HAL_INT
}
#endif


/***************************************************************************/
// Get Reboot Reason
/***************************************************************************/
#ifdef _halC2_
/*
  For The DOCLIST.EXE tool --> BeckCLib.LST

 #DOCLIST:REBOOT_UNKNOWN        CLIB\HW\halC2.htm
 #DOCLIST:REBOOT_COMMAND        CLIB\HW\halC2.htm
 #DOCLIST:REBOOT_WATCHDOG       CLIB\HW\halC2.htm
 #DOCLIST:REBOOT_POWER_FAIL     CLIB\HW\halC2.htm

 @doc DOC_halC2_
 ---------------------------------------------------------------
 HAL: Get Reboot Reason
 ---------------------------------------------------------------
 @clib  hal_get_reboot_reason | Get reboot reason. |
        <cfont>int hal_get_reboot_reason ( void );<efont> |
 @parm   void  |   | -- none --
 @rdesc  reason:<ul>
  <nl>
    0:<s2> REBOOT_UNKNOWN<nl>
    2:<s3> REBOOT_COMMAND<nl>
    3:<s2> REBOOT_WATCHDOG<nl>
    4:<s2> REBOOT_POWER_FAIL<nl>
    <ule><nl>
    The constants referred to here are defined in
    <lt>HWAPI.H<gt> header file.
 @comm  This function only returns
        valid results if the
        <linkto>halC1.htm<linkmid>hal_save_non_volatile_data<linktail> API
        was called from the user's Non-Maskable Interrupt (NMI)
        <linkto>hal84.htm<linkmid>callback<linktail> or at program exit
        and the init/restore
        <linkto>halC0.htm<linkmid>hal_init_non_volatile_data<linktail>
        function was called following the reboot.<nl>
        <nl>
        This function may also be used from within an NMI
        <linkto>hal84.htm<linkmid>callback<linktail>
        to access the cause of the current shut down interrupt.<s2>
        In this case the reading will be either <code>REBOOT_WATCHDOG<codee>
        or <code>REBOOT_POWER_FAIL<codee>.
 @Also  halC0.htm |  hal_init_non_volatile_data |
        halC1.htm |  hal_save_non_volatile_data |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10xC2<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.00 | V1.00 | V1.00 | V0.90 | V1.00
*/
int hal_get_reboot_reason(void)
{
   asm mov ah, HAL_GET_REBOOT_REASON
   asm int HAL_INT
   return _AX ;
}
#endif

/***************************************************************************/
// Install powerfaildone callback
/***************************************************************************/
#ifdef _halC3_
/*
 @doc DOC_halC3_
 ---------------------------------------------------------------
 HAL: Install powerfaildone callback
 ---------------------------------------------------------------
 @clib  hal_install_pfaildone_callback | Install powerfaildone callback. |
        <cfont>void hal_install_pfaildone_callback (InterruptHandler pfaildone_callback);<efont>|
 @parm  InterruptHandler | pfaildone_callback  | Pointer to callback function.
 @rdesc none
 @comm  Install a callback for the event "Powerfail is Done".<s2>
        The callback is executed after all Powerfail actions
        are finished.<s2>
        This means that the user non-volatile data has been
        written and the file sytem closed.<nl>
        <nl>
        The user can toggle a PIO inside this callback and measure the
        time from Powerfail (PFI/NMI) to this event.<nl>
        <nl>
        The time to close the file system depends on the number of open
        files and on which drive these files are located
        (speed of the drive).
 @Also  halC0.htm |  hal_init_non_volatile_data |
        halC1.htm |  hal_save_non_volatile_data |  |
 @rtos  This library function invokes a RTOS software interrupt.
        Refer to this RTOS API function's
        <linkto>../../hardware.htm#0xA10xC3<linkmid>documentation<linktail>
        for more details.
 @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
 @version    V1.21 | V1.21 | V1.21 | V1.10 | V1.00
*/
void hal_install_pfaildone_callback (InterruptHandler pfaildone_callback)
{
   asm les di, pfaildone_callback
   asm mov ah, HAL_INSTALL_PFAILDONE_CALLBACK
   asm int HAL_INT
}
#endif


/****************************************************************************
* (C) 1999-2005 by BECK IPC GmbH
*
*  BECK IPC GmbH
*  Germany
*  
*  http://www.beck-ipc.com
*
* ---------------------------------------------------------------------------
* Module    : HWAPI.H
* Function  : Definitions and prototypes for HW API library
* ---------------------------------------------------------------------------

$Header: HWAPI.H, 29, 28.08.2007 16:14:31, Andre Pribil$

*****************************************************************************/


#ifndef HWAPI_H
#define HWAPI_H

#include <target.h>

#ifdef CLIB_CUSTOMER_SPECIFIC
// Supply some optional patches for customer specific library.
// (For standard Beck library, this file does not exists.)
#include <HWAPI_EXT.H>
#endif

/***************************************************************************/
// Typedefs
/***************************************************************************/
#ifdef _MSC_VER
typedef void (_far _loadds *InterruptHandler)(void);
#else
typedef void huge (far *InterruptHandler)(void);
#endif

/***************************************************************************/
// Defines
/***************************************************************************/
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


/***************************************************************************/
// General definitions
/***************************************************************************/
#define DIRECT_IO


#define PIO_I      1
#define PIO_IPU    2
#define PIO_IPD    3
#define PIO_O1     4
#define PIO_O0     5

#define A0         0
#define A1         1
#define A2         2

#ifdef DIRECT_IO
 #define hal_inportb(x)      inportb(x)
 #define hal_outportb(x,y)   outportb(x,y)
#else
 #define hal_inportb(x)      hal_read_bus(x,0xFFFF,0x0000)
 #define hal_outportb(x,y)   hal_write_bus(x,y,0xFFFF,0x0000)
#endif

#define hal_inportb_block    hal_readblock_bus
#define hal_outportb_block   hal_writeblock_bus


// DMA Control registers Bits
#define DMA_PRIO      (1<<0)
#define DMA_SYNCSRC   (1<<1)
#define DMA_SYNCDEST  (1<<2)
#define DMA_DOINTR    (1<<3)
#define DMA_SRCINC    (1<<5)
#define DMA_SRCDEC    (1<<6)
#define DMA_SRCIO     (0)     /* Bit 7  equal to null */
#define DMA_SRCMEM    (1<<7)
#define DMA_DESTINC   (1<<8)
#define DMA_DESTDEC   (1<<9)
#define DMA_DESTIO    (0)     /* Bit 10 equal to null */
#define DMA_DESTMEM   (1<<10)
#define DMA_WORDTRANS (1<<11)

// DMA channels
#define DMA_CH0       0
#define DMA_CH1       1


#define REBOOT_UNKNOWN      (0)
#define REBOOT_COMMAND      (2)
#define REBOOT_WATCHDOG     (3)
#define REBOOT_POWER_FAIL   (4)


/***************************************************************************/
// Datatypes
/***************************************************************************/

// DMA Info Struct
typedef struct Dma_Info_
{
   unsigned count;
   union
   {
     void   far  *mem;
     unsigned  io;
   } src;

   union
   {
     void   far  *mem;
     unsigned  io;
   } dest;

   unsigned ctrl_reg;
} Dma_Info;

// Non Valotile Data
#ifndef MAX_RETENTIVE_AREAS
 /*!!!! Has to be passed for the user application !!!!*/
 #define MAX_RETENTIVE_AREAS 10
#endif
typedef struct _REMOP
{
    unsigned entries; // number of entries in struct REMOP_ENTRY x[]
    unsigned segment; // common segment address

    struct REMOP_ENTRY
    {
        unsigned offs;      // offset address
        unsigned size;      // number of bytes (must be <= maxsize)
        unsigned maxsize;   // maximal number of bytes
        unsigned elemsize;  // number of bytes per data element
        unsigned distance;  // distance to next data element (must be >= elemsize)
    }x[MAX_RETENTIVE_AREAS];
} Remop;

typedef enum
{
  HAL_WATCHDOG_MODE_GET     = 0,
  HAL_WATCHDOG_MODE_USER    = 2,
  HAL_WATCHDOG_MODE_RTOS    = 3,
  HAL_WATCHDOG_MODE_MANAGER = 4
} HalWatchdogMode;



/***************************************************************************/
// Prototyps
/***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

// ********** PFE Functiuons **************************
void _cdecl pfe_enable_bus               (unsigned short mask, unsigned char ale);

#ifdef SC123
#define pfe_enable_adr   pfe_enable_adr_sc123 // Select an alternate C-library function
void _cdecl pfe_enable_adr_sc123         (unsigned char adr);
#else
void _cdecl pfe_enable_adr               (unsigned char adr);
#endif

void _cdecl pfe_enable_pcs               (unsigned char pcs);
void _cdecl pfe_enable_int               (unsigned char irq);
void _cdecl pfe_enable_timer             (unsigned short mode);
#if (defined SC123) || (defined SC23)
#define pfe_enable_pio   pfe_enable_pio_sc123 // Select an alternate C-library function
void _cdecl pfe_enable_pio_sc123         (unsigned short pio, unsigned char mode);
#else
void _cdecl pfe_enable_pio               (unsigned short pio, unsigned char mode);
#endif

void _cdecl pfe_get_pio_state            (unsigned int far *wPio,
                                          unsigned int far *wInp,
                                          unsigned int far *wOut);
void _cdecl pfe_get_pio_state2           (unsigned int far *wPio,
                                          unsigned int far *wInp,
                                          unsigned int far *wOut);
void _cdecl pfe_set_edge_level_intr_mode (unsigned char mode, unsigned short mask);
void _cdecl pfe_enable_pwd               (void);
int  _cdecl pfe_enable_external_dma      (unsigned char channel);
void _cdecl pfe_enable_int_cascade_mode  (void);

typedef enum {
    PFE_0_WAIT   = 0x00,
    PFE_1_WAIT   = 0x01,
    PFE_2_WAIT   = 0x02,
    PFE_3_WAIT   = 0x03,
    PFE_5_WAIT   = 0x08,
    PFE_7_WAIT   = 0x09,
    PFE_9_WAIT   = 0x0A,
    PFE_15_WAIT  = 0x0B,
    PFE_24_WAIT  = 0x10,
    PFE_41_WAIT  = 0x11,
    PFE_74_WAIT  = 0x12,
    PFE_123_WAIT = 0x13,
    PFE_157_WAIT = 0x18,
    PFE_175_WAIT = 0x19,
    PFE_201_WAIT = 0x1A,
    PFE_255_WAIT = 0x1B
 } PFE_WAIT_STATES ;

typedef enum {
    PFE_0_WAIT2 = 0x00,
    PFE_1_WAIT2 = 0x01,
    PFE_2_WAIT2 = 0x02,
    PFE_3_WAIT2 = 0x03,
    PFE_4_WAIT2 = 0x08,
    PFE_5_WAIT2 = 0x09,
    PFE_6_WAIT2 = 0x0A,
    PFE_7_WAIT2 = 0x0B,
    PFE_8_WAIT2 = 0x10,
    PFE_9_WAIT2 = 0x11,
    PFE_10_WAIT2= 0x12,
    PFE_11_WAIT2= 0x13,
    PFE_12_WAIT2= 0x18,
    PFE_13_WAIT2= 0x19,
    PFE_14_WAIT2= 0x1A,
    PFE_15_WAIT2= 0x1B,
 } PFE_WAIT_STATES2 ;

void _cdecl pfe_set_wait_states     (PFE_WAIT_STATES  wait_states) ;
#ifdef SC123
void _cdecl pfe_set_wait_states2    (PFE_WAIT_STATES2 wait_states) ;
#else
void _cdecl pfe_set_wait_states2    (PFE_WAIT_STATES  wait_states) ;
#endif
void _cdecl pfe_set_wait_states_ucs (PFE_WAIT_STATES2 wait_states) ;

typedef enum {
    PFE_SIGNAL_ARDY    = 0x01,
    PFE_SIGNAL_HOLD    = 0x02,
    PFE_SIGNAL_WRL_WRH = 0x04,
    PFE_SIGNAL_A0_BHE  = 0x08
} PFE_BUS_SIGNALS ;

void _cdecl pfe_enable_bus_signals  (PFE_BUS_SIGNALS  signals);

typedef void _cdecl (far *WRITE_PIOS)  (unsigned short value) ;
typedef unsigned short _cdecl (far *READ_PIOS) (void) ;

typedef struct HWAPI_VECTORS_
{
    int         size;        // number of function entries
    READ_PIOS   readPios;
    WRITE_PIOS  writePios;
} HWAPI_VECTORS ;

void _cdecl pfe_get_vectors (HWAPI_VECTORS far *vectors) ;

// ************ HAL functions ************************
#ifdef SC123
#define hal_read_bus   hal_read_bus_sc123  // Select an alternate C-library function
#define hal_write_bus  hal_write_bus_sc123 // Select an alternate C-library function
unsigned short _cdecl hal_read_bus_sc123  (unsigned short adr,
                                           unsigned short wAND,
                                           unsigned short wXOR);
void _cdecl hal_write_bus_sc123     (unsigned short adr, unsigned short value,
                                     unsigned short wAND, unsigned short wXOR);
#else
unsigned char _cdecl hal_read_bus   (unsigned short adr,
                                     unsigned short wAND,
                                     unsigned short wXOR);
void _cdecl hal_write_bus           (unsigned short adr, unsigned char value,
                                     unsigned short wAND, unsigned short wXOR);
#endif

void _cdecl hal_readblock_bus       (unsigned short adr0, unsigned short adr1,
                                     unsigned char far *buf, short unsigned cnt);
void _cdecl hal_writeblock_bus      (unsigned short adr0, unsigned short adr1,
                                     const unsigned char far *buf, short unsigned cnt);
unsigned short _cdecl hal_read_pios (unsigned short wAND, unsigned short wXOR);
unsigned short _cdecl hal_read_pios2(unsigned short wAND, unsigned short wXOR);
void _cdecl hal_write_pios          (unsigned short value, unsigned short wAND,
                                     unsigned short wXOR);
void _cdecl hal_write_pios2         (unsigned short value, unsigned short wAND,
                                     unsigned short wXOR);
unsigned char _cdecl hal_read_pio   (unsigned char pio);
void _cdecl hal_write_pio           (unsigned char pio, unsigned short value);

#ifndef hal_install_isr     // Not overriden by a library extension function?
InterruptHandler _cdecl hal_install_isr (unsigned short irq,
                                         unsigned short count,
                                         InterruptHandler handler);
#endif  // hal_install_isr

InterruptHandler _cdecl hal_install_rtx_isr (unsigned short irq,
                                             unsigned short count,
                                             InterruptHandler handler);
void _cdecl hal_mask_int            (unsigned short irq, unsigned char mask);
void _cdecl hal_init_timer          (unsigned char timer,
                                     unsigned short mode,
                                     unsigned short divider);
void _cdecl hal_init_timer_ext      (unsigned char timer,
                                     unsigned short mode);
void _cdecl hal_start_timer         (unsigned char timer);
void _cdecl hal_stop_timer          (unsigned char timer);
unsigned short _cdecl hal_read_timer_count (unsigned char timer,
                                            unsigned short far *maxcount);
void _cdecl hal_write_timer_count   (unsigned char timer, unsigned short counter);
unsigned char _cdecl hal_set_watchdog_mode (unsigned char mode);
void _cdecl hal_refresh_watchdog    (void);
int _cdecl hal_watchdog_manager_sign_on(unsigned long period);
int _cdecl hal_watchdog_manager_refresh(unsigned handle,
                                        unsigned long period);
int _cdecl hal_watchdog_manager_sign_off(unsigned handle);

typedef enum {
   GET_FRQ_PROCESSOR = 0,
   GET_FRQ_TIMER     = 1,
   GET_FRQ_MAX_BAUD  = 2,
   GET_FRQ_PWD       = 3,
   GET_FRQ_TIMERBASE = 3
} HW_FREQ_SELECTOR ;

unsigned long _cdecl hal_get_frequencies( HW_FREQ_SELECTOR freq_select );

void _cdecl hal_set_duty_cycle_waveform( unsigned char timer,
                                         short mode,
                                         unsigned short clock_divider );
void _cdecl hal_give_eoi     (unsigned char intr_no);

int  _cdecl hal_start_dma    (unsigned char channel, const Dma_Info *dmaInfo );
int  _cdecl hal_stop_dma     (unsigned char channel );
int  _cdecl hal_get_dma_info (unsigned char channel, Dma_Info *dmaInfo );

int  _cdecl hal_init_non_volatile_data (const Remop far *remop);
void _cdecl hal_save_non_volatile_data (void);
int  _cdecl hal_get_reboot_reason      (void);
void _cdecl hal_install_pfaildone_callback (InterruptHandler pfaildone_callback);

#ifdef __cplusplus
}
#endif

#endif  // HWAPI_H


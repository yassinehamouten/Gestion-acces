/******************************************************************************
*
* (c) 2006-2007 by BECK IPC GmbH
* http://www.beck-ipc.com
*
*******************************************************************************
*
* Module:             usb_api.c
* Function:           USB-CLIB-API
*******************************************************************************
*
* $Header: c:\prjPib\IPC@CHIP\CLib\USB\usb_api.c, 31, 27.01.2009 09:50:04, Jan Schatz$
*
******************************************************************************/



#include <dos.h>
#include <common.h>
#include <usb_api.h>



/******************************************************************************
* Constants
******************************************************************************/
#define USB_SWI  0xBF



/******************************************************************************
* General Autoduck documentation
*
* Description of functions, parameters, return values, comments etc. are copied
* from software interrupt documentation found in RTOS-directory in
* .\usb\usb_swi.c.
******************************************************************************/
/*
  Note: The DOCLIST.EXE tool used by the C-Library HTML build process reacts
        to the token "#DOCLIST:" when it appears as the first non-white space
        on a line.  The tool transfers the text which follows into the
        BeckCLib.LST file that is used for the context sensitive help.

  Note: The *USB indicates that any names that start with USB and do not match
        any other name in our list should lead to the HTML page stated after the
        *USB.

  Note: Only newer versions of Paradigm Beck Edition support anchors in URLs.
        That's why there's always a version with (first) and without anchor.


  #DOCLIST:*USB clib\usb\lib_index.htm
  #DOCLIST:UsbEventStatus usbstruc.htm#UsbEventStatus
  #DOCLIST:UsbEventStatus usbstruc.htm  
  #DOCLIST:USB_EVENT_RECEIVED usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_RECEIVED usbstruc.htm
  #DOCLIST:USB_EVENT_SENT usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_SENT usbstruc.htm
  #DOCLIST:USB_EVENT_RESET usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_RESET usbstruc.htm
  #DOCLIST:USB_EVENT_SETUP usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_SETUP usbstruc.htm
  #DOCLIST:USB_EVENT_SUSPEND usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_SUSPEND usbstruc.htm
  #DOCLIST:USB_EVENT_RESUME usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_RESUME usbstruc.htm
  #DOCLIST:USB_EVENT_SOF usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_SOF usbstruc.htm
  #DOCLIST:USB_EVENT_ATTACH usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ATTACH usbstruc.htm
  #DOCLIST:USB_EVENT_DETACH usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_DETACH usbstruc.htm
  #DOCLIST:USB_EVENT_RELEASE usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_RELEASE usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_BIT_STUFF usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_BIT_STUFF usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_DMA usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_DMA usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_TURNAROUND usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_TURNAROUND usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_DATA_FIELD usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_DATA_FIELD usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_CRC16 usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_CRC16 usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_CRC5 usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_CRC5 usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_PID usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_PID usbstruc.htm
  #DOCLIST:USB_EVENT_NAK usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_NAK usbstruc.htm
  #DOCLIST:USB_EVENT_STALL usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_STALL usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_DATA_OVERRUN usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_DATA_OVERRUN usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_DATA_TOGGLE usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_DATA_TOGGLE usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_SOF_LOST usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_SOF_LOST usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_SOF_BANDWIDTH usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_SOF_BANDWIDTH usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_ATTACH usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_ATTACH usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_LOST_EVENT usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_LOST_EVENT usbstruc.htm
  #DOCLIST:USB_EVENT_ERROR_BANDWIDTH usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_ERROR_BANDWIDTH usbstruc.htm
  #DOCLIST:USB_EVENT_INVALID usbstruc.htm#UsbEventStatus
  #DOCLIST:USB_EVENT_INVALID usbstruc.htm
  #DOCLIST:UsbCallback usbstruc.htm#UsbCallback
  #DOCLIST:UsbCallback usbstruc.htm
  #DOCLIST:UsbInit usbstruc.htm#UsbInit
  #DOCLIST:UsbInit usbstruc.htm
  #DOCLIST:UsbDevice usbstruc.htm#UsbDevice
  #DOCLIST:UsbDevice usbstruc.htm
  #DOCLIST:UsbConfig usbstruc.htm#UsbConfig
  #DOCLIST:UsbConfig usbstruc.htm
  #DOCLIST:UsbInterface usbstruc.htm#UsbInterface
  #DOCLIST:UsbInterface usbstruc.htm
  #DOCLIST:UsbEp usbstruc.htm#UsbEp
  #DOCLIST:UsbEp usbstruc.htm
  #DOCLIST:USB_ERROR_NO usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_NO usbstruc.htm
  #DOCLIST:USB_ERROR_ILLEGAL_ARGUMENT usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_ILLEGAL_ARGUMENT usbstruc.htm
  #DOCLIST:USB_ERROR_OUT_OF_MEMORY usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_OUT_OF_MEMORY usbstruc.htm
  #DOCLIST:USB_ERROR_RESOURCE_LACK usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_RESOURCE_LACK usbstruc.htm
  #DOCLIST:USB_ERROR_QUEUE_MAXIMUM usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_QUEUE_MAXIMUM usbstruc.htm
  #DOCLIST:USB_ERROR_FEATURE_DISABLED usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_FEATURE_DISABLED usbstruc.htm
  #DOCLIST:USB_ERROR_OUT_OF_INTERFACES usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_OUT_OF_INTERFACES usbstruc.htm
  #DOCLIST:USB_ERROR_OUT_OF_ENDPOINTS usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_OUT_OF_ENDPOINTS usbstruc.htm
  #DOCLIST:USB_ERROR_RESET_SETUP usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_RESET_SETUP usbstruc.htm
  #DOCLIST:USB_ERROR_UNKNOWN_SERVICE usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_UNKNOWN_SERVICE usbstruc.htm
  #DOCLIST:USB_ERROR_PROTOCOL usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_PROTOCOL usbstruc.htm
  #DOCLIST:USB_ERROR_BUSY usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_BUSY usbstruc.htm
  #DOCLIST:USB_ERROR_OUT_OF_DEVICES usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_OUT_OF_DEVICES usbstruc.htm
  #DOCLIST:USB_ERROR_TIMEOUT usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_TIMEOUT usbstruc.htm
  #DOCLIST:USB_ERROR_QUEUE_EMPTY usbstruc.htm#UsbError
  #DOCLIST:USB_ERROR_QUEUE_EMPTY usbstruc.htm

  
  @doc DOC_INDEX

  @clibidx  <tab><cfont>#include <InBraces USB_API\.H><efont> |
            This documentation describes the CLIB
            API of the IPC@CHIP&reg; RTOS dual-mode USB-driver. The SC1x3/SC2x
            disposes of a USB-controller that is compliant with the
            <linkto>http://www.beck-ipc.com/usbspec11<linkmid>USB specification version 1.1<linktail>.<nl>
            Though the USB-API hides much of the complexity of the USB, one should
            fly over the specification to get a grasp of how USB works.<nl>
            We also recommend to take notice of the
            <linkto>http://www.usb.org/developers/docs/EH_MR_rev1.pdf<linkmid>Requirements
            and Recommendations for USB Products with Embedded
            Hosts and/or Multiple Receptacles<linktail>.
            <nl>
            <nl>
            The USB-driver can be used in Device mode to implement a USB device
            (resp. function) which will then be connected to e.g. a PC-Host; or
            it can be used in Host mode. In this case USB devices can be
            connected to the IPC@CHIP&reg; handled by device-specific drivers that
            use the USB-API.<nl>
            The RTOS USB-driver can operate in only one mode at a time. To
            implement a USB Function (Device) using this API, an additional
            circuit is needed, which manages attach- and speed-detection. A
            diagram is included in the hardware manual of the SC1x3/SC2x
            showing how to prepare your hardware to operate in both modes.
            Any PIO can be used to control this circuit. The API switches the
            PIO as needed.
            <nl>
            <nl>
            Please note that there's no Hub support in Host mode and that
            there are some restrictions regarding data structures handled by
            the RTOS USB-driver necessary to keep the driver small and fast.
            These mainly concern Configurations, Interfaces and Alternate
            Settings. These restrictions should not constrain you much when
            implementing a USB-device and most devices connected to an IPC@CHIP&reg;
            operating in Host mode will fulfil the conditions too.
            <ul>
              <li>There can only be one Configuration. (It is uncommon to use
                  more than one Configuration though the specification allows
                  it.)
              <li>There can be at most 10 Interfaces.
              <li>Each interface can have maximal 12 alternate settings.
              <li>Alternate settings in Device mode can only be used to alter
                  the maximum packet size and the polling interval of its
                  assigned endpoints. It is impossible to change e.g. the
                  number of assigned endpoints. This would also be very
                  uncommon.
                  In Host mode a device may also have a different number of
                  endpoints and different transfer types in Alternate Settings.
            <ule><nl>

 <tab><linkto>#Common<linkmid>Common<linktail>
 <tab><linkto>#Device<linkmid>Device mode only<linktail>
 <tab><linkto>#Host<linkmid>Host mode only<linktail>
 

  @textlinkpara  USB API | ../../usbstruc.htm | Data Structures  |

  @libcat1  Common | usb01 | usbSend |
            Send data |
  @libcat1  Common | usb02 | usbFreeReceiveBuffer |
            Hand a receive buffer back to the driver |
  @libcat1  Common | usb03 | usbWakeup |
            Wake up suspended nodes |
  @libcat1  Common | usb04 | usbSofNotify |
            Enable/disable notification of SOF events |

  @libcat2  Device mode only | usb10 | usbDeviceInit |
            Initialise driver for Device mode |
  @libcat2  Device mode only | usb11 | usbDeviceDeinit  |
            Deinitialise Device mode driver |
  @libcat2  Device mode only | usb12 | usbDeviceRegisterInterface  |
            Register an interface |
  @libcat2  Device mode only | usb13 | usbDeviceRegisterAltSetting  |
            Register an Alternate Setting |
  @libcat2  Device mode only | usb14 | usbDeviceGetEps  |
            Get numbers of endpoints associated with an interface |
  @libcat2  Device mode only | usb15 | usbDeviceConfigEp  |
            Configure an endpoint |
  @libcat2  Device mode only | usb16 | usbDeviceAddSpecificDesc  |
            Add a class- or verndor-specific descriptor |
  @libcat2  Device mode only | usb17 | usbDeviceStart  |
            Start the Device mode driver |
  @libcat2  Device mode only | usb18 | usbDeviceStop  |
            Stop the Device mode driver |
  @libcat2  Device mode only | usb19 | usbDeviceStallEp  |
            Set STALL condition for an endpoint |
  @libcat2  Device mode only | usb1A | usbDeviceEnableEp  |
            Enable/disable OUT direction of an endpoint |

  @libcat3  Host mode only | usb20 | usbHostInit |
            Initialise driver for Host mode |
  @libcat3  Host mode only | usb21 | usbHostDeinit |
            Deinitialise Host mode driver |
  @libcat3  Host mode only | usb22 | usbHostIssueToken |
            Issue token |
  @libcat3  Host mode only | usb23 | usbHostClearQueue |
            Clear an endpoint's queues |
  @libcat3  Host mode only | usb24 | usbHostReserveEp0 |
            Reserve endpoint 0 |
  @libcat3  Host mode only | usb25 | usbHostReleaseEp0 |
            Release endpoint 0 |
  @libcat3  Host mode only | usb26 | usbHostGetDeviceInfo |
            Get Device information |
  @libcat3  Host mode only | usb27 | usbHostGetConfigInfo |
            Get Configuration information |
  @libcat3  Host mode only | usb28 | usbHostGetInterfaceInfo |
            Get Interface information |
  @libcat3  Host mode only | usb29 | usbHostGetEpInfo |
            Get Endpoint information |
  @libcat3  Host mode only | usb2A | usbHostGetString |
            Get string |
  @libcat3  Host mode only | usb2B | usbHostGetStatus |
            Get status |
  @libcat3  Host mode only | usb2C | usbHostSetClearFeature |
            Set/clear feature |
  @libcat3  Host mode only | usb2D | usbHostSetInterface |
            Set interface |
*/



/******************************************************************************
* usbSend()
******************************************************************************/
#ifdef _usb01_
/*
  @doc DOC_usb01_

  @clib  usbSend |
         Enqueues a send request to an endpoint's TX queue. In Device mode
         the data will be transmitted when the Host issues an IN token. In
         Host mode the data will be transmitted when a SETUP or OUT token is
         issued using <linkto>usb22.htm<linkmid>usbHostIssueToken<linktail>.
         When the request has been completed the
         <linkto>../../usbstruc.htm#UsbCallback<linkmid>callback<linktail>-function
         will be called with a status of
         <cfont>USB_EVENT_SENT<efont>. |
         UsbError usbSend( unsigned char address,   <nl> |
                           unsigned char epNumber,  <nl>
                           void far *buffer,        <nl>
                           unsigned length,         <nl>
                           UsbBool less );

  @parm unsigned char | address |
        Host mode: Address of the device that is to receive the data<nl>
        Device mode: Must always be 0x00
  @parm unsigned char | epNumber |
        Number of the enpoint via which the data is to be sent
  @parm void far * | buffer |
        Data to be sent
  @parm unsigned int | length | Length of data to be sent
  @parm UsbBool | less | Host mode: Must always be FALSE<nl>
                       Device mode: Set this parameter to TRUE if the host
                       demanded more data than is to be sent. This does only
                       apply to control endpoints.

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm
  The buffer that is used for sending must be allocated by the application
  and be available while the USB-driver processes the send-request. After
  it has completed the callback-function will be called with an
  <cfont>USB_EVENT_SENT<efont> event (or maybe an error event). After that
  the buffer can be released.

  @related C-library function | usb15.htm | usbDeviceConfigEp |
  @related C-library function | usb22.htm | usbHostIssueToken |
  @related C-library function | usb23.htm | usbHostClearQueue |
  @related C-library function | usb24.htm | usbHostReserveEp0 |
  @related C-library function | usb25.htm | usbHostReleaseEp0 |
  @related Type | ../../usbstruc.htm#UsbCallback | UsbCallback |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x01<linkmid>USB_SERVICE_SEND<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
UsbError far usbSend(
                      unsigned char address,
                      unsigned char epNumber,
                      void far *buffer,
                      unsigned length,
                      UsbBool less )
{
  _CL = epNumber;
  _ES = FP_SEG( buffer );
  _BX = FP_OFF( buffer );
  _DX = length;
  _CH = less;

  _AL = address;
  _AH = USB_SERVICE_SEND;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbFreeReceiveBuffer()
******************************************************************************/
#ifdef _usb02_
/*
  @doc DOC_usb02_

  @clib  usbFreeReceiveBuffer |
         Frees a receive buffer. The RTOS USB-driver manages a bunch of
         receive buffers internally. Each time data is received on any
         endpoint, it is put into one of these buffers and the buffer is
         handed to a user driver along with a callback event.<nl>
         To enable the reuse of the buffer, this function has to be called as
         soon as possible. |
         void usbFreeReceiveBuffer( void far *buffer ); |

  @parm void far * | buffer | Pointer to the receive buffer that is to be freed

  @rdesc None

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x02<linkmid>USB_SERVICE_FREE_RECEIVE_BUFFER<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
void far usbFreeReceiveBuffer(
                               void far *buffer )
{
  _ES = FP_SEG( buffer );
  _BX = FP_OFF( buffer );

  _AH = USB_SERVICE_FREE_RECEIVE_BUFFER;

  asm int USB_SWI;
}
#endif



/******************************************************************************
* usbWakeup()
******************************************************************************/
#ifdef _usb03_
/*
  @doc DOC_usb03_

  @clib  usbWakeup |
         ends a resume signal to the bus to wakeup suspended nodes |
         UsbError usbWakeup( void ); |

  @parm int |  | None

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm
  As well hosts as devices may perform resume signaling. But the
  Remote Wakeup Feature of devices may be disabled. In this case a call to
  this function will fail in Device mode.

  @related C-library function | usb2C.htm | usbHostSetClearFeature |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x03<linkmid>USB_SERVICE_WAKEUP<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
UsbError far usbWakeup(
                        void )
{
  _AH = USB_SERVICE_WAKEUP;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbSofNotify()
******************************************************************************/
#ifdef _usb04_
/*
  @doc DOC_usb04_

  @clib  usbSofNotify |
         Use this function to enable or disable the forwarding of SOF events
         to your application. By default the event
         <linkto>../../usbstruc.htm#UsbEventStatus<linkmid>USB_EVENT_SOF<linktail>
         is not notified. |
         UsbError usbSofNotify( unsigned char driverId, <nl> |
                                UsbBool enable );

  @parm unsigned char | driverId | Host mode: ID of the user driver<nl>
                                   Device mode: Must always be 0x00
  @parm UsbBool | enable | Indicates whether to enable (TRUE) or disable (FALSE)
                           the notification of SOF events

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @related Type | ../../usbstruc.htm#UsbCallback | UsbCallback |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x04<linkmid>USB_SERVICE_SOF_NOTIFY<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbSofNotify(
                           unsigned char driverId,
                           UsbBool enable )
{
  _BL = enable;
  _AL = driverId;
  _AH = USB_SERVICE_SOF_NOTIFY;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbDeviceInit()
* Note: Here the parameter documentation is not copied from the resp. SWI
* function but from the documentation of the structure UsbInit which is used
* with the software interrupt.
******************************************************************************/
#ifdef _usb10_
/*
  @doc DOC_usb10_

  @clib  usbDeviceInit |
         Initialises the USB driver in Device mode and registers a
         <linkto>../../usbstruc.htm#UsbCallback<linkmid>callback<linktail>-function
         that will be called to notify the user driver of events like completed
         transactions.<nl>
         Also sets sundry strings that describe the device.<nl>
         Only one user program can use the USB driver in Device mode. |
         UsbError usbDeviceInit( UsbCallback callback,              <nl> |
                                 unsigned char classCode,           <nl>
                                 unsigned char subClassCode,        <nl>
                                 unsigned char protocolCode,        <nl>
                                 unsigned short vendorId,           <nl>
                                 unsigned short productId,          <nl>
                                 unsigned short versionBcd,         <nl>
                                 char far *manufacturerString,      <nl>
                                 char far *productString,           <nl>
                                 char far *serialNumberString,      <nl>
                                 char far *configString,            <nl>
                                 UsbBool selfPowered,               <nl>
                                 unsigned char maxPowerConsumption  <nl>
                                 unsigned char pioNumber );

  @parm UsbCallback | callback | Pointer to the callback-function that the
        USB-driver will call to notifiy the application of certain events.
  @parm unsigned char | classCode | Class code of the device
  @parm unsigned char | subClassCode | Subclass code of the device
  @parm unsigned char | protocolCode | Protocol code of the device
  @parm unsigned short | vendorId | Vendor ID of the device. The vendor ID identifies
        the vendor of a device. It is assigned by the
        <linkto>http://www.usb.org/developers<linkmid>USB Implementers Forum <linktail>.
  @parm unsigned short | productId | Product code of the device. The several devices
        of a vendor are differed by their product ID. The vendor is free to
        assign any product ID.
  @parm unsigned short | versionBcd | Release version of the device in BCD-format.
        This is used to distinguish several releases of the same product.
  @parm char far * | manufacturerString | Pointer to manufacturer string (e.g.
        "Beck IPC GmbH")
  @parm char far * | productString | Pointer to product string (e.g. "IPC@CHIP 
        SC123")
  @parm char far * | serialNumberString | Pointer to serial-number string (e.g.
        "123456-ABCDE")
  @parm char far * | configString | Pointer to configuration string
  @parm UsbBool | selfPowered | TRUE, if the device is self-powered
  @parm unsigned char | maxPowerConsumption | Maximum current that the device
        may draw from the bus. Given in steps of 2mA.
  @parm unsigned | pioNumber | Number of PIO to be used to control attach- and
        speed-detection circuit; Refer to SC1x3 hardware manual.<s2> On SC2x
        this circuit is integrated at the chip and hardwired to PIO 26.

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm
  The Host uses classCode, subClassCode and protocolCode to find an appropriate
  standard driver for the device. If classCode is 0xFF - which means that the
  device uses a vendor-specific protocol - the host uses vendor and product ID
  to find a driver. <nl>
  classCode, subClassCode and protocolCode may also be set with interfaces. In
  this case the values here should be 0x00.<nl>
  <nl>
  manufacturerString, productString, serialNumberString and configString are
  human readable strings describing the device. The host may show these to the
  user. The maximum length of a string is USB_SPEC_MAX_STRING_LENGTH characters.
  If the string is longer it will be cut. Note that they have to be static,
  since the driver will not copy their content but only hold a pointer. If a
  string shall not be used, set the pointer to NULL.<nl>

  @related C-library function | usb11.htm | usbDeviceDeinit |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x10<linkmid>USB_SERVICE_DEVICE_INIT<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
UsbError far usbDeviceInit(
                            UsbCallback callback,
                            unsigned char classCode,
                            unsigned char subClassCode,
                            unsigned char protocolCode,
                            unsigned short vendorId,
                            unsigned short productId,
                            unsigned short versionBcd,
                            char far *manufacturerString,
                            char far *productString,
                            char far *serialNumberString,
                            char far *configString,
                            UsbBool selfPowered,
                            unsigned char maxPowerConsumption,
                            unsigned char pioNumber )
{
  UsbInit initStructure;


  initStructure.callback = callback;
  initStructure.classCode = classCode;
  initStructure.subClassCode = subClassCode;
  initStructure.protocolCode = protocolCode;
  initStructure.vendorId = vendorId;
  initStructure.productId = productId;
  initStructure.versionBcd = versionBcd;
  initStructure.manufacturerString = manufacturerString;
  initStructure.productString = productString;
  initStructure.serialNumberString = serialNumberString;
  initStructure.configString = configString;
  initStructure.selfPowered = selfPowered;
  initStructure.maxPowerConsumption = maxPowerConsumption;
  initStructure.pioNumber = pioNumber;

  _ES = FP_SEG( &initStructure );
  _BX = FP_OFF( &initStructure );

  _AH = USB_SERVICE_DEVICE_INIT;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbDeviceDeinit()
******************************************************************************/
#ifdef _usb11_
/*
  @doc DOC_usb11_

  @clib  usbDeviceDeinit |
         This function deinitialises the USB-driver in Device mode. |
         void far usbDeviceDeinit( void ); |

  @parm int |  | None

  @rdesc None

  @comm
  If the USB-driver has already been started, stop it first.

  @related C-library function | usb10.htm | usbDeviceInit |
  @related C-library function | usb18.htm | usbDeviceStop |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x11<linkmid>USB_SERVICE_DEVICE_DEINIT<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
void far usbDeviceDeinit(
                          void )
{
  _AH = USB_SERVICE_DEVICE_DEINIT;

  asm int USB_SWI;
}
#endif



/******************************************************************************
* usbDeviceRegisterInterface()
******************************************************************************/
#ifdef _usb12_
/*
  @doc DOC_usb12_

  @clib  usbDeviceRegisterInterface |
         This function registers a new interface. |
         int usbDeviceRegisterInterface(
                                         unsigned char nEp,           <nl> |
                                         unsigned char classCode,     <nl>
                                         unsigned char subClassCode,  <nl>
                                         unsigned char protocolCode,  <nl>
                                         char far *interfaceString );

  @parm unsigned char | nEp | Number of endpoints to associate with the interface
  @parm unsigned char | classCode | Class code of this interface
  @parm unsigned char | subClassCode | Subclass code of this interface
  @parm unsigned char | protocolCode | Protocol code of this interface
  @parm char far * | interfaceString | Human readable string describing this
        interface, must be static for the USB-driver will not copy it. The
        string can have a maximum length of USB_SPEC_MAX_STRING_LENGTH characters.
        If no string is needed, set this to NULL.

  @rdesc ID of the newly registered interface or
         <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm
  For further information on Class, Subclass and Protocol code see the
  description of <linkto>usb10.htm<linkmid>usbDeviceInit<linktail>.<nl>
  Use the function <linkto>usb14.htm<linkmid>usbDeviceGetEps<linktail>
  to get the numbers of the endpoints that are assigned to the interface.

  @related C-library function | usb10.htm | usbDeviceInit |
  @related C-library function | usb13.htm | usbDeviceRegisterAltSetting |
  @related C-library function | usb14.htm | usbDeviceGetEps |
  @related C-library function | usb16.htm | usbDeviceAddSpecificDesc |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x12<linkmid>USB_SERVICE_DEVICE_REGISTER_INTERFACE<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
int far usbDeviceRegisterInterface(
                                    unsigned char nEp,
                                    unsigned char classCode,
                                    unsigned char subClassCode,
                                    unsigned char protocolCode,
                                    char far *interfaceString )
{
  _CL = classCode;
  _DL = subClassCode;
  _CH = protocolCode;
  _ES = FP_SEG( interfaceString );
  _BX = FP_OFF( interfaceString );

  _AL = nEp;
  _AH = USB_SERVICE_DEVICE_REGISTER_INTERFACE;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbDeviceRegisterAltSetting()
******************************************************************************/
#ifdef _usb13_
/*
  @doc DOC_usb13_

  @clib  usbDeviceRegisterAltSetting |
         This function registers a new alterate setting to a given interface. |
         int usbDeviceRegisterAltSetting( unsigned char interfaceId ); |

  @parm unsigned char | interfaceId | ID of the interface to that the alternate
        settings is to be registered

  @rdesc ID of the new alternate setting or
         <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @related C-library function | usb12.htm | usbDeviceRegisterInterface |
  @related C-library function | usb15.htm | usbDeviceConfigEp |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x13<linkmid>USB_SERVICE_DEVICE_REGISTER_ALT_SETTING<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
int far usbDeviceRegisterAltSetting(
                                     unsigned char interfaceId )
{
  _AL = interfaceId;
  _AH = USB_SERVICE_DEVICE_REGISTER_ALT_SETTING;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbDeviceGetEps()
******************************************************************************/
#ifdef _usb14_
/*
  @doc DOC_usb14_

  @clib  usbDeviceGetEps |
         This function gets the numbers of the endpoints that have been
         associated with an interface. The numbers are returned in a bitmap
         field. Each bit that is set to "1" marks an assigned endpoint. If
         e.g. Bit 1 is set, endpoint 1 is assigned to the interface.<nl>
         By default both the IN and OUT endpoint at the resp. endpoint number
         are reserved to the interface. You decide which direction actually
         to assign to the interface when configuring the endpoints. You may
         even use both directions if both have the same transfer type. |
         UsbError usbDeviceGetEps( unsigned char interfaceId,  <nl> |
                                   unsigned far *epBitmap );

  @parm unsigned char | interfaceId | ID of the interface whose endpoints are to
        be gotten
  @parm unsigned far * | epBitmap | Result parameter: Bitmap indicating which
        ndpoints belong to the given interface.

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm
  Endpoint 0 never can be assigned to an interface but every interface can
  use it.

  @related C-library function | usb12.htm | usbDeviceRegisterInterface |
  @related C-library function | usb15.htm | usbDeviceConfigEp |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x14<linkmid>USB_SERVICE_DEVICE_GET_EPS<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
UsbError far usbDeviceGetEps(
                              unsigned char interfaceId,
                              unsigned short far *epBitmap )
{
  _ES = FP_SEG( epBitmap );
  _BX = FP_OFF( epBitmap );

  _AL = interfaceId;
  _AH = USB_SERVICE_DEVICE_GET_EPS;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbDeviceConfigEp()
******************************************************************************/
#ifdef _usb15_
/*
  @doc DOC_usb15_

  @clib  usbDeviceConfigEp |
         This function can be used to configure an endpoint. Transfer type and
         the transfer direction can be configured once for each endpoint. The
         maximum packet size and the polling interval can be configured for
         each alternate setting of the interface that the endpoint is
         associated to. |
         int usbDeviceConfigEp( unsigned char interfaceId,     <nl> |
                                unsigned char altSettingId,    <nl>
                                unsigned char epNumber,        <nl>
                                unsigned char transferType,    <nl>
                                UsbBool in,                    <nl>
                                unsigned short maxPacketSize,  <nl>
                                unsigned char interval );

  @parm unsigned char | interfaceId | ID of the interface the endpoint is
        associated to
  @parm unsigned char | altSettingId | ID of the alternate setting to the given
        interface
  @parm unsigned char | epNumber | Number of the endpoint that is to be configured
  @parm unsigned char | transferType | Transfer type; possible values are:<ul>
          <li><cfont>USB_SPEC_TRANSFER_TYPE_CONTROL<efont>
          <li><cfont>USB_SPEC_TRANSFER_TYPE_ISOCHRONOUS<efont>
          <li><cfont>USB_SPEC_TRANSFER_TYPE_BULK<efont>
          <li><cfont>USB_SPEC_TRANSFER_TYPE_INTERRUPT<efont><ule>
        The symbolic names are defined in USB_SPEC.H.
  @parm UsbBool | in | TRUE, if this is an IN-endpoint, which means that data
        is transfered from the device to the host. This parameter is ignored
        for control-endpoints.
  @parm unsigned short | maxPacketSize | Maximum size of packets sent/received
        through this endpoint; Please note that the packet size may also be
        limited by the USB specification and by the capabilities of the
        controller.
  @parm unsigned char | interval | Polling interval for interrupt and isochronous
        endpoints; given in 2ms steps.

  @rdesc Maximum packet size set (respecting the USB specification and the
         capabilities of the controller) or
         <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @related C-library function | usb12.htm | usbDeviceRegisterInterface |
  @related C-library function | usb13.htm | usbDeviceRegisterAltSetting |
  @related C-library function | usb14.htm | usbDeviceGetEps |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x15<linkmid>USB_SERVICE_DEVICE_CONFIG_EP<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
int far usbDeviceConfigEp(
                           unsigned char interfaceId,
                           unsigned char altSettingId,
                           unsigned char epNumber,
                           unsigned char transferType,
                           UsbBool in,
                           unsigned short maxPacketSize,
                           unsigned char interval )
{
  _BL = altSettingId;
  _CL = epNumber;
  _BH = transferType;
  _CH = in;
  _DX = maxPacketSize;
  _ES = interval;

  _AL = interfaceId;
  _AH = USB_SERVICE_DEVICE_CONFIG_EP;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbDeviceAddSpecificDesc()
******************************************************************************/
#ifdef _usb16_
/*
  @doc DOC_usb16_

  @clib  usbDeviceAddSpecificDesc |
         This function can be used to add class- oder vendor-specific
         descriptors to the Configuration, to an interface or an endpoint.
         A buffer has to be allocated by the application into which the
         descriptor is written. Several descriptors can be written in this
         single buffer, but only one buffer can be added to each entity.
         The buffer must be available during the whole program execution
         because the RTOS USB-driver will not copy it. The specific
         descriptors will be concatenated to the resp. standard descriptors. |
         UsbError usbDeviceAddSpecificDesc( unsigned char descriptorType,      <nl> |
                                            unsigned char idNumber,            <nl>
                                            char far *descriptor,              <nl>
                                            unsigned char descriptorLength );

  @parm unsigned char | descriptorType | Type of entity to which the specific
        descriptor is to be added. These are possible values:<ul>
          <li><cfont>USB_SPEC_DESCRIPTOR_TYPE_CONFIG<efont>
          <li><cfont>USB_SPEC_DESCRIPTOR_TYPE_INTERFACE<efont>
          <li><cfont>USB_SPEC_DESCRIPTOR_TYPE_EP<efont><ule>
        The symbolic names are defined in USB_SPEC.H.
  @parm unsigned char | idNumber | ID/number of entity to which the specific
        descriptor is to be added. If the descriptor type is <cfont>
        USB_SPEC_DESCRIPTOR_TYPE_EP<efont> this is the endpoint number. If
        descriptor type is <cfont>USB_SPEC_DESCRIPTOR_TYPE_INTERFACE<efont>
        this is the index of the interface. If descriptor type is <cfont>
        USB_SPEC_DESCRIPTOR_TYPE_CONFIG<efont> this parameter should be 0.
  @parm char far * | descriptor | Pointer to the buffer containing the descriptor(s)
  @parm unsigned char | descriptorLength | Length of the descriptor(s) in bytes

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm If a specific descriptor is added to an interface it is added to all
        alternate settings.

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x06<linkmid>USB_SERVICE_DEVICE_ADD_SPECIFIC_DESC<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
UsbError far usbDeviceAddSpecificDesc(
                                       unsigned char descriptorType,
                                       unsigned char idNumber,
                                       char far *descriptor,
                                       unsigned char descriptorLength )
{
  _CL = idNumber;
  _ES = FP_SEG( descriptor );
  _BX = FP_OFF( descriptor );
  _DL = descriptorLength;

  _AL = descriptorType;
  _AH = USB_SERVICE_DEVICE_ADD_SPECIFIC_DESC;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbDeviceStart()
******************************************************************************/
#ifdef _usb17_
/*
  @doc DOC_usb17_

  @clib  usbDeviceStart |
         This function will start the Device mode USB-driver and enable the
         attach- and speed-detection circuit via the configured PIO pin. |
         void usbDeviceStart( void ); |

  @parm int |  | None

  @rdesc None

  @related C-library function | usb18.htm | usbDeviceStop |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x17<linkmid>USB_SERVICE_DEVICE_START<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
void far usbDeviceStart(
                         void )
{
  _AH = USB_SERVICE_DEVICE_START;

  asm int USB_SWI;
}
#endif



/******************************************************************************
* usbDeviceStop()
******************************************************************************/
#ifdef _usb18_
/*
  @doc DOC_usb18_

  @clib  usbDeviceStop |
         This function will stop the Device mode USB-driver and disable
         the attach- and speed-detection circuit via the configured PIO pin. |
         void usbDeviceStop( void ); |

  @parm int |  | None

  @rdesc None

  @related C-library function | usb17.htm | usbDeviceStart |
  @related C-library function | usb11.htm | usbDeviceDeinit |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x18<linkmid>USB_SERVICE_DEVICE_STOP<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
void far usbDeviceStop(
                        void )
{
  _AH = USB_SERVICE_DEVICE_STOP;

  asm int USB_SWI;
}
#endif



/******************************************************************************
* usbDeviceStallEp()
******************************************************************************/
#ifdef _usb19_
/*
  @doc DOC_usb19_

  @clib  usbDeviceStallEp |
         This function will set the STALL condition for an endpoint. The
         USB controller will reject all arriving packets and send requests
         on this endpoint and return a STALL handshake. A distinction between
         the IN and OUT direction is not possible. Both directions will be
         stalled.<nl>
         Host intervention is needed to reset the condition. |
         UsbError usbDeviceStallEp( unsigned char epNumber ); |

  @parm unsigned char | epNumber | Number of endpoint that is to be stalled

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @related C-library function | usb2C.htm | usbHostSetClearFeature |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x19<linkmid>USB_SERVICE_DEVICE_STALL_EP<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V0.90 | V1.00

  @target_clib V2.01
*/
UsbError far usbDeviceStallEp(
                               unsigned char epNumber )
{
  _AH = USB_SERVICE_DEVICE_STALL_EP;
  _AL = epNumber;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbDeviceEnableEp()
******************************************************************************/
#ifdef _usb1A_
/*
  @doc DOC_usb1A_

  @clib  usbDeviceEnableEp |
         This function enables or disables communication in the OUT direction
         (Host to Device) of an endpoint. When the Host tries to send data on
         a disabled endpoint a NAK handshake will be returned (except for
         ISOCHRONOUS endpoints).<nl>
         <nl>
         By default all configured endpoints are enabled after the Device has
         been started.<nl>
         <nl>
         Note that this function will not stop reception immediately. At least
         two more packets can be received, because respective requests have
         already been handed to the controller hardware. Some more data may
         already have been received, but still be pending in a software queue
         inside the RTOS. |
         UsbError usbDeviceEnableEp( unsigned char epNumber<nl> |
                                     UsbBool enable );

  @parm unsigned char | epNumber | Number of endpoint that is to be
        enabled/disabled
  @parm UsbBool | enable | Indicates whether the endpoint is to be enabled
        (TRUE) or disabled (FALSE)

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>
  
  @comm If the device is permanent unable to receive data, the endopint should
        be stalled.<nl>
        <nl>
        To achieve sending of a NAK handshake in the IN direction (Device to
        Host) of an endpoint, simply stop sending on this endpoint. If the Host
        then tries to receive data on that endpoint, a NAK handshake is returned
        automatically.

  @related C-library function | usb19.htm | usbDeviceStallEp |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x1A<linkmid>USB_SERVICE_DEVICE_ENABLE_EP<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12 | SC13 | SC11 | SC1x3 | SC2x
  @version    n/a  | n/a  | n/a  | V1.20 | V1.20

  @target_clib V2.13
*/
UsbError far usbDeviceEnableEp(
                                unsigned char epNumber,
                                UsbBool enable )
{
  _AH = USB_SERVICE_DEVICE_ENABLE_EP;
  _AL = epNumber;
  _BL = enable;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbHostInit()
******************************************************************************/
#ifdef _usb20_
/*
  @doc DOC_usb20_

  @clib  usbHostInit |
         This function registers a user driver and initialises the RTOS USB-driver
         for Host mode if no other user driver has already done this. There can be
         several user drivers loaded in Host mode. Each driver registers a
         <linkto>../../usbstruc.htm#UsbCallback<linkmid>callback<linktail>-function
         which is called when an event (e.g. completed transaction) appears on a
         device that the driver is assigned to.
         User drivers are assigned to Interfaces which allows a device with two
         different functions and thus two different Interfaces to be handled by two
         different drivers. The criteria for the assignment of user drivers to
         Interfaces are the codes handed to this function. |
         int usbHostInit( UsbCallback callback,              <nl> |
                          unsigned char classCode,           <nl>
                          unsigned char subClassCode,        <nl>
                          unsigned char protocolCode,        <nl>
                          unsigned short vendorId,           <nl>
                          unsigned short productId,          <nl>
                          unsigned short versionBcd );

  @parm UsbCallback | callback | Callback function
  @parm unsigned char | classCode | Class code
  @parm unsigned char | subClassCode | Subclass code
  @parm unsigned char | protocolCode | Protocol code<nl>
        If the user driver can handle devices of one of the Device Classes,
        these arguements identify the class, subclass and protocol. If the user
        driver handles vendor-specific protocols, set these arguments to 0.
  @parm unsigned short | vendorId | Vendor ID
  @parm unsigned short | productId | Product ID
  @parm unsigned short | versionBcd | Product version in BCD code<nl>
        If the user driver handles devices using a vendor-specific protocol,
        these arguements identify the Vendor and Product ID of the resp. device
        as well as the maximum product version that the driver can handle. If
        the user driver can handle devices of one of the Device Classes, set
        these arguments to 0.

  @rdesc Assigned driver ID or <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>.
         The driver ID will be needed for other API functions.

  @comm This function must not be called from within the callback-function.

  @related C-library function | usb21.htm | usbHostDeinit |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x20<linkmid>USB_SERVICE_HOST_INIT<linktail>
         offered by RTOS USB
         Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
int far usbHostInit(
                     UsbCallback callback,
                     unsigned char classCode,
                     unsigned char subClassCode,
                     unsigned char protocolCode,
                     unsigned short vendorId,
                     unsigned short productId,
                     unsigned short versionBcd )
{
  _ES = FP_SEG( callback );
  _BX = FP_OFF( callback );
  _DI = versionBcd;
  _SI = productId;
  _DX = vendorId;
  _CL = subClassCode;
  _CH = protocolCode;
  _AL = classCode;
  _AH = USB_SERVICE_HOST_INIT;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbHostDeinit()
******************************************************************************/
#ifdef _usb21_
/*
  @doc DOC_usb21_

  @clib  usbHostDeinit |
         This function unregisters a user driver and deinitialises the USB driver
         if there are no more user drivers registered. |
         void usbHostDeinit( unsigned char driverId );  |

  @parm unsigned char | driverId | ID of the user driver that is to be unregistered

  @rdesc None

  @comm This function must not be called from within the callback-function.

  @related C-library function | usb20.htm | usbHostInit |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x21<linkmid>USB_SERVICE_HOST_DEINIT<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
void far usbHostDeinit(
                        unsigned char driverId )
{
  _AL = driverId;
  _AH = USB_SERVICE_HOST_DEINIT;

  asm int USB_SWI;

  return;
}
#endif



/******************************************************************************
* usbHostIssueToken()
******************************************************************************/
#ifdef _usb22_
/*
  @doc DOC_usb22_

  @clib  usbHostIssueToken |
         Issues an IN, OUT or SETUP token on a given endpoint. This is needed in
         Host mode to initiate a data transfer. To receive a packet from a
         device, an IN token has to be issued to tell the device to start
         sending. To send a packet to a device an OUT or SETUP token has to be
         issued after callingb <linkto>usb01.htm<linkmid>usbSend<linktail> to
         tell the RTOS USB-driver to start transmission. |
         UsbError usbHostIssueToken( unsigned char address,   <nl> |
                                     unsigned char epNumber,  <nl>
                                     unsigned char token );

  @parm unsigned char | address | Address of the device that is to receive the token
  @parm unsigned char | epNumber | Number of the endpoint that is to receive the token
  @parm unsigned char | token | Token that is to be sent; must be one of the
        following:<ul>
          <li><cfont>USB_SPEC_PID_IN<efont>
          <li><cfont>USB_SPEC_PID_OUT<efont>
          <li><cfont>USB_SPEC_PID_SETUP<efont><ule>
        The symbolic names are defined in USB_SPEC.H.

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm This function must not be called from within the callback-function.

  @related C-library function | usb01.htm | usbSend |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x20<linkmid>USB_SERVICE_HOST_ISSUE_TOKEN<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbHostIssueToken(
                                unsigned char address,
                                unsigned char epNumber,
                                unsigned char token )
{
  _BL = epNumber;
  _BH = token;
  _AL = address;
  _AH = USB_SERVICE_HOST_ISSUE_TOKEN;

  asm int USB_SWI;

  return _AX;

}
#endif



/******************************************************************************
* usbHostClearQueue()
******************************************************************************/
#ifdef _usb23_
/*
  @doc DOC_usb23_

  @clib  usbHostClearQueue |
         This function clears the send and token queue of a given endpoint. It
         can be used to reset an endpoint when an error occured.<nl>
         Buffers associated with send requests cleared by this function will
         later be handed back to the user driver via an event with the status
         <linkto>../../usbstruc.htm#UsbEventStatus<linkmid>USB_EVENT_RELEASE<linktail>.<nl>
         Note that queue entries already passed to the USB controller cannot be
         removed. |
         UsbError usbHostClearQueue( unsigned char address,   <nl> |
                                     unsigned char epNumber,  <nl>
                                     UsbBool in );

  @parm unsigned char | address | Address of the resp. device
  @parm unsigned char | epNumber | Number of the endpoint whose queues are to be
        cleared
  @parm UsbBool | in | States that the IN direction of the endpoint is to be
        cleared; set to FALSE for OUT or CONTROL endpints

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm This function must not be called from within the callback-function.

  @related C-library function | usb01.htm | usbSend |
  @related C-library function | usb22.htm | usbHostIssueToken |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x23<linkmid>USB_SERVICE_HOST_CLEAR_QUEUE<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbHostClearQueue(
                                unsigned char address,
                                unsigned char epNumber,
                                UsbBool in )
{
  _BL = epNumber;
  _BH = in;
  _AL = address;
  _AH = USB_SERVICE_HOST_CLEAR_QUEUE;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbHostReserveEp0()
******************************************************************************/
#ifdef _usb24_
/*
  @doc DOC_usb24_

  @clib  usbHostReserveEp0 |
         Reserves endpoint 0 of a device for a user driver. Since it might happen
         that several user drivers share one device, access to endpoint 0 of the
         device has to be synchronised. A user driver must not use (i.e. send or
         issue tokens) endpoint 0 before reserving it.<nl>
         The endpoint has to be released again using the
         <linkto>usb25.htm<linkmid>usbHostReleaseEp0<linktail>. |
         UsbError usbHostReserveEp0( unsigned char driverId,  <nl> |
                                     unsigned char address );

  @parm unsigned char | driverId | ID of the user driver
  @parm unsigned char | address | Address of the resp. device

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm This function must not be called from within the callback-function.

  @related C-library function | usb25.htm | usbHostReleaseEp |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x24<linkmid>USB_SERVICE_HOST_RESERVE_EP0<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbHostReserveEp0(
                                unsigned char driverId,
                                unsigned char address )
{
  _BL = address;
  _AL = driverId;
  _AH = USB_SERVICE_HOST_RESERVE_EP0;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbHostReleaseEp0()
******************************************************************************/
#ifdef _usb25_
/*
  @doc DOC_usb25_

  @clib  usbHostReleaseEp0 |
         Releases endpoint 0 of a device after it was reserved using
         <linkto>usb24.htm<linkmid>usbHostReserveEp0<linktail>. |
         UsbError usbHostReleaseEp0( unsigned char driverId,   <nl> |
                                     unsigned char address );  <nl>

  @parm unsigned char | driverId | ID of the user driver that has reserved the endpoint
  @parm unsigned char | address | Address of the resp. device

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm This function must not be called from within the callback-function.

  @related C-library function | usb24.htm | usbHostReserveEp0 |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x25<linkmid>USB_SERVICE_HOST_RELEASE_EP0<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbHostReleaseEp0(
                                unsigned char driverId,
                                unsigned char address )
{
  _BL = address;
  _AL = driverId;
  _AH = USB_SERVICE_HOST_RELEASE_EP0;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbHostGetDeviceInfo()
******************************************************************************/
#ifdef _usb26_
/*
  @doc DOC_usb26_

  @clib  usbHostGetDeviceInfo |
         Returns information from the Device Descriptor of a given device |
         UsbError usbHostGetDeviceInfo( unsigned char address,  <nl> |
                                        UsbDevice far *info,        <nl>
                                        unsigned char size );

  @parm unsigned char | address | Address of the resp. device
  @parm UsbDevice far * | info | Result parameter: Pointer to a structure of the type
        <linkto>../../usbstruc.htm#UsbDevice<linkmid>UsbDevice<linktail> which
        is to be filled with the information
  @parm unsigned char | size | Size of the handed structure in bytes

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm This function must not be called from within the callback-function.

  @related C-library function | usb27.htm | usbHostGetConfigInfo |
  @related C-library function | usb28.htm | usbHostGetInterfaceInfo |
  @related C-library function | usb29.htm | usbHostGetEpInfo |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x26<linkmid>USB_SERVICE_HOST_GET_DEVICE_INFO<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbHostGetDeviceInfo(
                                   unsigned char address,
                                   UsbDevice far *info,
                                   unsigned char size )
{
  _ES = FP_SEG( info );
  _BX = FP_OFF( info );
  _CL = size;
  _AL = address;
  _AH = USB_SERVICE_HOST_GET_DEVICE_INFO;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbHostGetConfigInfo()
******************************************************************************/
#ifdef _usb27_
/*
  @doc DOC_usb27_

  @clib  usbHostGetConfigInfo |
         Returns information from the Configuration Descriptor of a given device |
         UsbError usbHostGetConfigInfo( unsigned char address,  <nl> |
                                        UsbConfig far *info,        <nl>
                                        unsigned char size );

  @parm unsigned char | address | Address of the resp. device
  @parm UsbConfig far * | info | Result parameter: Pointer to a structure of the type
        <linkto>../../usbstruc.htm#UsbConfig<linkmid>UsbConfig<linktail> which
        is to be filled with the information
  @parm unsigned char | size | Size of the handed structure in bytes

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm This function must not be called from within the callback-function.

  @related C-library function | usb26.htm | usbHostGetDeviceInfo |
  @related C-library function | usb28.htm | usbHostGetInterfaceInfo |
  @related C-library function | usb29.htm | usbHostGetEpInfo |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x27<linkmid>USB_SERVICE_HOST_GET_CONFIG_INFO<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbHostGetConfigInfo(
                                   unsigned char address,
                                   UsbConfig far *info,
                                   unsigned char size )
{
  _ES = FP_SEG( info );
  _BX = FP_OFF( info );
  _CL = size;
  _AL = address;
  _AH = USB_SERVICE_HOST_GET_CONFIG_INFO;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbHostGetInterfaceInfo()
******************************************************************************/
#ifdef _usb28_
/*
  @doc DOC_usb28_

  @clib  usbHostGetInterfaceInfo |
         Returns information from the Interface Descriptor of a given interface |
         UsbError usbHostGetInterfaceInfo( unsigned char address,       <nl> |
                                           unsigned char interfaceId,   <nl>
                                           unsigned char altSettingId,  <nl>
                                           UsbInterface far *info,      <nl>
                                           unsigned char size );

  @parm unsigned char | address | Address of the resp. device
  @parm unsigned char | interfaceId | ID of the resp. Interface
  @parm unsigned char | altSettingId | ID of the resp. Alternate Setting
  @parm UsbInterface far * | info | Result parameter: Pointer to a structure of the
        type <linkto>../../usbstruc.htm#UsbInterface<linkmid>UsbInterface<linktail>
        which is to be filled with the information
  @parm unsigned char | size | Size of the handed structure in bytes

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm This function must not be called from within the callback-function.

  @related C-library function | usb26.htm | usbHostGetDeviceInfo |
  @related C-library function | usb27.htm | usbHostGetConfigInfo |
  @related C-library function | usb29.htm | usbHostGetEpInfo |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x28<linkmid>USB_SERVICE_HOST_GET_INTERFACE_INFO<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbHostGetInterfaceInfo(
                                      unsigned char address,
                                      unsigned char interfaceId,
                                      unsigned char altSettingId,
                                      UsbInterface far *info,
                                      unsigned char size )
{
  _ES = FP_SEG( info );
  _BX = FP_OFF( info );
  _DL = size;
  _CL = interfaceId;
  _CH = altSettingId;
  _AL = address;
  _AH = USB_SERVICE_HOST_GET_INTERFACE_INFO;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbHostGetEpInfo()
******************************************************************************/
#ifdef _usb29_
/*
  @doc DOC_usb29_

  @clib  usbHostGetEpInfo |
         Returns information from the Endpoint Descriptor of a given endpoint |
         UsbError usbHostGetEpInfo( unsigned char address,       <nl> |
                                    unsigned char altSettingId,  <nl>
                                    unsigned char epNumber,      <nl>
                                    UsbBool in,                  <nl>
                                    UsbEp far *info,             <nl>
                                    unsigned char size );

  @parm unsigned char | address | Address of the resp. device
  @parm unsigned char | altSettingId | ID of the resp. alternate setting
  @parm unsigned char | epNumber | Number of the resp. endpoint
  @parm UsbBool | in | Indicates that information on an IN endpoint is desired;
        always set to FALSE for control-endpoints
  @parm UsbEp far * | info | Result parameter: Pointer to a structure of the type
        <linkto>../../usbstruc.htm#UsbEp<linkmid>UsbEp<linktail> which is to be
        filled with the information
  @parm unsigned char | size | Size of the handed structure in bytes

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm This function must not be called from within the callback-function.

  @related C-library function | usb26.htm | usbHostGetDeviceInfo |
  @related C-library function | usb27.htm | usbHostGetConfigInfo |
  @related C-library function | usb28.htm | usbHostGetInterfaceInfo |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x29<linkmid>USB_SERVICE_HOST_GET_EP_INFO<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbHostGetEpInfo(
                               unsigned char address,
                               unsigned char altSettingId,
                               unsigned char epNumber,
                               UsbBool in,
                               UsbEp far *info,
                               unsigned char size )
{
  _ES = FP_SEG( info );
  _BX = FP_OFF( info );
  _DL = in;
  _DH = size;
  _CL = altSettingId;
  _CH = epNumber;
  _AL = address;
  _AH = USB_SERVICE_HOST_GET_EP_INFO;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbHostGetString()
******************************************************************************/
#ifdef _usb2A_
/*
  @doc DOC_usb2A_

  @clib  usbHostGetString |
         Retrieves a string from a given device |
         UsbError usbHostGetString( unsigned char driverId,  <nl> |
                                    unsigned char address,   <nl>
                                    unsigned char stringId,  <nl>
                                    char far *string );

  @parm unsigned char | driverId | ID of the user driver
  @parm unsigned char | address | Address of the resp. device
  @parm unsigned char | stringId | ID of the string that is desired
  @parm char far * | string | Pointer to a buffer where the string is to be stored;
        Must be large enough to store a string consisting of <cfont>
        USB_SPEC_MAX_STRING_LENGTH<efont> characters plus trailing zero-byte

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm  This function reserves endpoint 0 of the resp. device for the user
         driver that calls it before using the endpoint and it releases it
         again afterwards.<nl>
         Note that this function may take up to 2000 ms to complete, because
         it waits that long for data to arrive from the device.<nl>
         This function must not be called from within the callback-function.

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x2A<linkmid>USB_SERVICE_HOST_GET_STRING<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbHostGetString(
                               unsigned char driverId,
                               unsigned char address,
                               unsigned char stringId,
                               char far *string )
{
  _ES = FP_SEG( string );
  _BX = FP_OFF( string );
  _CL = address;
  _CH = stringId;
  _AL = driverId;
  _AH = USB_SERVICE_HOST_GET_STRING;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbHostGetStatus()
******************************************************************************/
#ifdef _usb2B_
/*
  @doc DOC_usb2B_

  @clib  usbHostGetStatus |
         Retrieves status information from a given device using the GetStatus
         Standard Device Request |
         UsbError usbHostGetStatus( unsigned char driverId,    <nl> |
                                    unsigned char address,     <nl>
                                    unsigned char receiver,    <nl>
                                    unsigned char index,       <nl>
                                    unsigned short far *status );

  @parm unsigned char | driverId | ID of the user driver
  @parm unsigned char | address | Address of the resp. device
  @parm unsigned char | receiver | Receiver of the GetStatus request; this
        parameter decides whether the status of the device, an interface, an
        endpoint or a user- defined structure is to be retrieved; must be one of
        the following:<ul>
          <li><cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_DEVICE<efont>
          <li><cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_INTERFACE<efont>
          <li><cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_ENDPOINT<efont>
          <li><cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_OTHER<efont><ule>
        The symbolic names are defined in USB_SPEC.H.
  @parm unsigned char | index | Index of the resp. structure. The value of this
        parameter depends on the value of the receiver parameter.<nl>
        If the receiver is <cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_DEVICE<efont>,
        the index must always be 0.<nl>
        If the receiver is <cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_INTERFACE<efont>,
        the index must contain the ID of the resp. interface.<nl>
        If the receiver is <cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_ENDPOINT<efont>,
        the index parameter must contain the number of the resp. endpoint.
        If it is an IN endpoint, bit 7 has to be set additionally. (e.g. IN
        endpoint 1 =<gt> 0x81).<nl>
        If the receiver is <cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_OTHER<efont>,
        the value of the index parameter is device-specific.<nl>
  @parm unsigned short far * | status | Pointer to an <cfont>unsigned short<efont>
        variable where the status is to be stored.

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm  This function reserves endpoint 0 of the resp. device for the user
         driver that calls it before using the endpoint and it releases it
         again afterwards.<nl>
         Note that this function may take up to 2000 ms to complete, because
         it waits that long for data to arrive from the device.<nl>
         This function must not be called from within the callback-function.

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x2B<linkmid>USB_SERVICE_HOST_GET_STATUS<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbHostGetStatus(
                               unsigned char driverId,
                               unsigned char address,
                               unsigned char receiver,
                               unsigned char index,
                               unsigned short far *status )
{
  _ES = FP_SEG( status );
  _BX = FP_OFF( status );
  _DL = index;
  _CL = address;
  _CH = receiver;
  _AL = driverId;
  _AH = USB_SERVICE_HOST_GET_STATUS;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbHostSetClearFeature()
******************************************************************************/
#ifdef _usb2C_
/*
  @doc DOC_usb2C_

  @clib  usbHostSetClearFeature |
         Sets or clears a feature of a given device by sending a SetFeature or
         ClearFeature Standard Device Request |
         UsbError usbHostSetClearFeature( unsigned char driverId,  <nl> |
                                          unsigned char address,   <nl>
                                          unsigned char receiver,  <nl>
                                          unsigned char index,     <nl>
                                          unsigned char feature,   <nl>
                                          UsbBool setFeature );

  @parm unsigned char | driverId | ID of the user driver
  @parm unsigned char | address | Address of the resp. device
  @parm unsigned char | receiver | Receiver of the SetFeature or GetFeature request;
        this parameter decides whether a feature of the device, an interface,
        an endpoint or a user- defined structure is to be set/cleared; must
        be one of the following:<ul>
          <li><cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_DEVICE<efont>
          <li><cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_INTERFACE<efont>
          <li><cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_ENDPOINT<efont>
          <li><cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_OTHER<efont><ule>
        The symbolic names are defined in USB_SPEC.H.
  @parm unsigned char | index | Index of the resp. structure. The value of this
        parameter depends on the value of the receiver parameter.<nl>
        If the receiver is <cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_DEVICE<efont>,
        the index must always be 0.<nl>
        If the receiver is <cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_INTERFACE<efont>,
        the index must contain the ID of the resp. interface.<nl>
        If the receiver is <cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_ENDPOINT<efont>,
        the index parameter must contain the number of the resp. endpoint.
        If it is an IN endpoint, bit 7 has to be set additionally. (e.g. IN
        endpoint 1 =<gt> 0x81).<nl>
        If the receiver is <cfont>USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_OTHER<efont>,
        the value of the index parameter is device-specific.<nl>
  @parm unsigned char | feature | Identifies the feature that is to be set/cleared.
        Actually the feature <cfont>USB_SPEC_FEATURE_REMOTE_WAKEUP<efont> is
        defined for devices and <cfont>USB_SPEC_FEATURE_STALL<efont> for
        endpoints.<nl>
        The symbolic names are defined in USB_SPEC.H.
  @parm UsbBool | setFeature | If this parameter is TRUE the feature will be set,
        otherwise it will be cleared.

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm  This function reserves endpoint 0 of the resp. device for the user
         driver that calls it before using the endpoint and it releases it
         again afterwards.<nl>
         Note that this function may take up to 2000 ms to complete, because
         it waits that long for data to arrive from the device.<nl>
         This function must not be called from within the callback-function.

  @related C-library function | usb03.htm | usbWakeup |
  @related C-library function | usb19.htm | usbDeviceStallEp |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x2C<linkmid>USB_SERVICE_HOST_SET_CLEAR_FEATURE<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbHostSetClearFeature(
                                     unsigned char driverId,
                                     unsigned char address,
                                     unsigned char receiver,
                                     unsigned char index,
                                     unsigned char feature,
                                     UsbBool setFeature )
{
  _DL = setFeature;
  _CL = index;
  _CH = feature;
  _BL = address;
  _BH = receiver;
  _AL = driverId;
  _AH = USB_SERVICE_HOST_SET_CLEAR_FEATURE;

  asm int USB_SWI;

  return _AX;
}
#endif



/******************************************************************************
* usbHostSetInterface()
******************************************************************************/
#ifdef _usb2D_
/*
  @doc DOC_usb2D_

  @clib  usbHostSetInterface |
         Sets one of the alternate settings of a given interface as the current
         one by sending a SetInterface Standard Device Request |
         UsbError usbHostSetInterface( unsigned char driverId,        <nl> |
                                       unsigned char address,         <nl>
                                       unsigned char interfaceId,     <nl>
                                       unsigned char altSettingId );

  @parm unsigned char | driverId | ID of the user driver
  @parm unsigned char | address | Address of the resp. device
  @parm unsigned char | interfaceId | ID of the resp. interface
  @parm unsigned char | altSettingId | ID of the alternate setting that is to be activated

  @rdesc <linkto>../../usbstruc.htm#UsbError<linkmid>Error code<linktail>

  @comm  This function reserves endpoint 0 of the resp. device for the user
         driver that calls it before using the endpoint and it releases it
         again afterwards.<nl>
         Note that this function may take up to 2000 ms to complete, because
         it waits that long for data to arrive from the device.<nl>
         This function must not be called from within the callback-function.

  @related C-library function | usb27.htm | usbHostGetConfigInfo |
  @related C-library function | usb28.htm | usbHostGetInterfaceInfo |

  @rtos  This library function uses a dynamic link to reach the function
         <linkto>../../usbswi.htm#0xBF0x2D<linkmid>USB_SERVICE_HOST_SET_INTERFACE<linktail>
         offered by RTOS USB Software Interrupt.

  @target     SC12  | SC13  | SC11  | SC1x3 | SC2x
  @version    n/a   | n/a   | n/a   | V1.06 | V1.00

  @target_clib V2.05
*/
UsbError far usbHostSetInterface(
                                  unsigned char driverId,
                                  unsigned char address,
                                  unsigned char interfaceId,
                                  unsigned char altSettingId )
{
  _CL = altSettingId;
  _BL = address;
  _BH = interfaceId;
  _AL = driverId;
  _AH = USB_SERVICE_HOST_SET_INTERFACE;

  asm int USB_SWI;

  return _AX;
}
#endif



// End of file


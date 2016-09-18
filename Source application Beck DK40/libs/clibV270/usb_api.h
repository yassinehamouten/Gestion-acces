/*******************************************************************************
*
* (c) 2006 by BECK IPC GmbH
* http://www.beck-ipc.com
*
********************************************************************************
*
* Module:     usb_api.h
* Function:   See usb_api.c
*
********************************************************************************
*
* $Header: c:\prjPib\IPC@CHIP\CLib\usb_api.h, 15, 27.01.2009 09:50:05, Jan Schatz$
*
*******************************************************************************/



#ifndef USB_API_H
#define USB_API_H



/*******************************************************************************
* Type UsbBool
*******************************************************************************/
#ifndef UsbBool
  #define UsbBool  unsigned char
#endif
#ifndef FALSE
  #define FALSE  0
#endif
#ifndef TRUE
  #define TRUE   ( !FALSE )
#endif



/*******************************************************************************
* Service numbers
*
* These are the values that have to be written to the AH register when calling
* the software interrupt. They correspond to the C-functions below.
*******************************************************************************/
#define USB_SERVICE_DYNAMIC_LINK                 0x00
#define USB_SERVICE_SEND                         0x01
#define USB_SERVICE_FREE_RECEIVE_BUFFER          0x02
#define USB_SERVICE_WAKEUP                       0x03
#define USB_SERVICE_SOF_NOTIFY                   0x04

#define USB_SERVICE_DEVICE_INIT                  0x10
#define USB_SERVICE_DEVICE_DEINIT                0x11
#define USB_SERVICE_DEVICE_REGISTER_INTERFACE    0x12
#define USB_SERVICE_DEVICE_REGISTER_ALT_SETTING  0x13
#define USB_SERVICE_DEVICE_GET_EPS               0x14
#define USB_SERVICE_DEVICE_CONFIG_EP             0x15
#define USB_SERVICE_DEVICE_ADD_SPECIFIC_DESC     0x16
#define USB_SERVICE_DEVICE_START                 0x17
#define USB_SERVICE_DEVICE_STOP                  0x18
#define USB_SERVICE_DEVICE_STALL_EP              0x19
#define USB_SERVICE_DEVICE_ENABLE_EP             0x1A

#define USB_SERVICE_HOST_INIT                    0x20
#define USB_SERVICE_HOST_DEINIT                  0x21
#define USB_SERVICE_HOST_ISSUE_TOKEN             0x22
#define USB_SERVICE_HOST_CLEAR_QUEUE             0x23
#define USB_SERVICE_HOST_RESERVE_EP0             0x24
#define USB_SERVICE_HOST_RELEASE_EP0             0x25
#define USB_SERVICE_HOST_GET_DEVICE_INFO         0x26
#define USB_SERVICE_HOST_GET_CONFIG_INFO         0x27
#define USB_SERVICE_HOST_GET_INTERFACE_INFO      0x28
#define USB_SERVICE_HOST_GET_EP_INFO             0x29
#define USB_SERVICE_HOST_GET_STRING              0x2A
#define USB_SERVICE_HOST_GET_STATUS              0x2B
#define USB_SERVICE_HOST_SET_CLEAR_FEATURE       0x2C
#define USB_SERVICE_HOST_SET_INTERFACE           0X2D



/*******************************************************************************
* Definition of types
*******************************************************************************/
// Error codes
typedef enum
{
  USB_ERROR_NO                =  0,   // No error occured
  USB_ERROR_ILLEGAL_ARGUMENT  = -1,   // An argument with an invalid value was
                                      // passed
  USB_ERROR_OUT_OF_MEMORY     = -2,   // The USBD could not allocate enough
                                      // memory for the requested operation.
  USB_ERROR_RESOURCE_LACK     = -3,   // Lack of some kind of internally managed
                                      // resource such as tasks, semaphores,
                                      // buffers, etc.
  USB_ERROR_QUEUE_MAXIMUM     = -4,   // A request could not be enqueued due to
                                      // the resp. queue having reached its
                                      // maximum.
  USB_ERROR_FEATURE_DISABLED  = -5,   // The requested feature is not enabled
  USB_ERROR_OUT_OF_INTERFACES = -6,   // There were not enough free interfaces/
                                      // alternative settings left
  USB_ERROR_OUT_OF_ENDPOINTS  = -7,   // There were not enough free endpoints left
  USB_ERROR_RESET_SETUP       = -8,   // A reset occured or a setup token has
                                      // been received on the resp. endpoint
                                      // but the event has not yet been notified.
                                      // The requested action cannot be performed
                                      // in this situation.
  USB_ERROR_UNKNOWN_SERVICE   = -9,   // The software interrupt was triggered
                                      // with an unknown service number.
  USB_ERROR_PROTOCOL          = -10,  // The USB-Protocol was violated or
                                      // the protocol indicated an error.
  USB_ERROR_BUSY              = -11,  // A resource is temporarily not available
                                      // but might be available again later
  USB_ERROR_OUT_OF_DEVICES    = -12,  // This error code is currently not used
                                      // on SC1x3/SC2x.
  USB_ERROR_TIMEOUT           = -13,  // This error code is currently not used
                                      // on SC1x3/SC2x.
  USB_ERROR_QUEUE_EMPTY       = -14   // This error code is currently not used
                                      // on SC1x3/SC2x.
} UsbError;



// This enum indicates the event that occured regarding callbacks
typedef enum
{
  // Data has been received.
  // The address parameters holds the address of the device from which data was
  // received in Host mode - 0 in Device mode.
  // epNumber indicates the endpoint on which data was received.
  // buffer holds the received data.
  // length holds the number of bytes stored in buffer.
  // After processing the data the function usbFreeReceiveBuffer() has to be
  // called to free the buffer containing the data.
  USB_EVENT_RECEIVED = 0,


  // Data has been successfully sent.
  // address holds the address of the device to which data was sent in Host
  // mode - 0 in Device mode.
  // epNumber indicates the endpoint on which data was sent.
  // buffer holds the sent data.
  // length holds the number of bytes stored in buffer.
  USB_EVENT_SENT = 1,

  // The device has been reset. (Device mode only)
  // All other callback parameters are 0.
  USB_EVENT_RESET = 2,

  // A setup token has been received. (Device mode only)
  // epNumber indicates on which endpoint a Setup token has been received.
  // All other callback parameters are 0.
  // Processing of a previous control-transaction must be stopped. The received
  // data will be notified in a seperate USB_EVENT_RECEIVED-event.
  USB_EVENT_SETUP = 3,

  // The device has been suspended, i.e. there has been no activity on the bus
  // for 3 ms. (Device mode only)
  // This event can be used to save power by shutting e.g. down peripherals.
  // All other callback parameters are 0.
  USB_EVENT_SUSPEND = 4,

  // The node has been woken up from suspension.
  // All other callback parameters are 0.
  USB_EVENT_RESUME = 5,

  // A Start-Of-Frame token has been issued, indicating the beginning of a new
  // 1-ms frame.
  // All other callback parameters are 0.
  USB_EVENT_SOF = 13,

  // A new device has been attached. (Host mode only) This event is only notified
  // to a user driver if it can handle the resp. device.
  // address holds the address of the new device.
  // All other callback parameters are 0.
  USB_EVENT_ATTACH = 14,

  // A device has been detached. (Host mode only) This event is only notified
  // to a user driver if it can handle the resp. device.
  // - address holds the address of the device.
  // All other callback parameters are 0.
  USB_EVENT_DETACH = 15,

  // This event is used to hand a send buffer back to a user driver in Host mode.
  // The user driver passed this buffer to the USB driver along with a send request
  // but then cleared the send queue for any reason.
  // buffer holds the pointer to the resp. user driver buffer.
  // All other callback parameters are 0.
  USB_EVENT_RELEASE = 16,


  // ----------------------------------------
  // Error events
  // The follwoing events indicate error conditions. If nothing else is stated,
  // the callback parameter address indicates the device with which an error
  // occured in Host mode or 0 in Device mode, epNumber indicates the resp.
  // endpoint and length indicates whether the error occured while receiving or
  // sending as a boolean value (TRUE = sending, FALSE = receiving).

  // Indicates that a bit stuff error was detected in the data stream on the bus.
  // The resp. packet was rejected. The Host should repeat it.
  USB_EVENT_ERROR_BIT_STUFF = 6,

  // Fatal! There was a problem regarding DMA data transport between memory and
  // the USB controller hardware. Data may be lost.
  USB_EVENT_ERROR_DMA = 7,

  // A bus turnaround timeout occured. This means that too much time elapsed
  // between two phases of a data transfer. This is likely to happen if
  // the USB cable is too long.
  USB_EVENT_ERROR_TURNAROUND = 8,

  // Indicates that a data field did not consist of an integral number of bytes.
  // The resp. packet was rejected. The Host should repeat it.
  USB_EVENT_ERROR_DATA_FIELD = 9,

  // Indicates a checksum error. The resp. packet was rejected. The host should
  // repeat it.
  // In Host mode USB_EVENT_ERROR_CRC5 indicates an internal timing error. This
  // should not happen.
  USB_EVENT_ERROR_CRC16 = 10,
  USB_EVENT_ERROR_CRC5 = 11,

  // A PID check field didn't match. This is similar to a checksum error. The
  // resp. packet was rejected. The Host should repeat it.
  USB_EVENT_ERROR_PID = 12,

  // A transaction on an INTERRUPT endpoint has been NAKed by the device.
  // (Host mode only)
  USB_EVENT_NAK = 17,

  // The device returned a STALL handshake on the given endpoint. (Host mode only)
  USB_EVENT_STALL = 18,

  // This event is currently not used on SC1x3/SC2x.
  USB_EVENT_ERROR_DATA_OVERRUN = 25,

  // A data packet arrived with a wrong DATA PID. All other callback parameters
  // match the description for the USBEVENT_RECEIVED event. It is up to the
  // user driver to decide whether to use or discard the package.
  USB_EVENT_ERROR_DATA_TOGGLE = 19,

  // The three following error events do not relate to a special device or endpoint.
  // All callback parameters, except for the status, will be set to 0.

  // This event indicates a SOF token (see USB_EVENT_SOF), but it also indicates
  // that a SOF token has been lost.
  USB_EVENT_ERROR_SOF_LOST = 20,

  // This event indicates a SOF token (see USB_EVENT_SOF), but it also indicates
  // that not all transactions of the last frame had been completed. These
  // transactions and the appropriate data are lost. (Host mode only)
  USB_EVENT_ERROR_SOF_BANDWIDTH = 21,

  // A newly attached device could not be configured correctly. (Host mode only)
  // The user driver cannot determine what kind of device had been attached.
  USB_EVENT_ERROR_ATTACH = 22,

  // Fatal! An overrun occured in the ring queue used to manage events and
  // events have been lost.
  USB_EVENT_ERROR_LOST_EVENT = 23,

  // This event is currently not used on SC1x3/SC2x.
  USB_EVENT_ERROR_BANDWIDTH = 24,


  // ----------------------------------------
  // This event is used internally only.
  USB_EVENT_INVALID = -1
} UsbEventStatus;



// Callback functions will be used to notify events like resets or completed
// transactions.
typedef void huge ( far *UsbCallback )( unsigned epNumber,      // Endpoint that the
                                                                // event occured on.
                                                                // 0 if not applicable
                                        UsbEventStatus status,  // Indicates the type of
                                                                // event that happened.
                                        void far *buffer,       // If a transmission
                                        unsigned length,        // completed these
                                                                // variables hold
                                                                // the resp. data and
                                                                // its length.
                                        unsigned address );     // Address of the
                                                                // resp. device,
                                                                // 0 in device
                                                                // mode




// This structure is used with the software interrupt service USB_SERVICE_INIT.
// Since the service expects that much parameters and there are not enough
// registers, a variable of this structure is used to hand the parameters to the
// software interrupt.
// The fields correspond to the parameters of usbDeviceInit().
typedef struct UsbInit_
{
  UsbCallback callback;
  unsigned char classCode;
  unsigned char subClassCode;
  unsigned char protocolCode;
  unsigned short vendorId;
  unsigned short productId;
  unsigned short versionBcd;
  char far *manufacturerString;
  char far *productString;
  char far *serialNumberString;
  char far *configString;
  UsbBool selfPowered;
  unsigned char maxPowerConsumption;
  unsigned char pioNumber;
} UsbInit;



// This structure is used with the result parameter of the API function
// usbHostGetDeviceInfo(). Fields mainly relate to a Device Descriptor found
// in section 9.6.1 of the USB 1.1 specification.
typedef struct UsbDevice_
{
  unsigned short usbVersion;
  unsigned char classCode;
  unsigned char subClassCode;
  unsigned char protocolCode;
  unsigned char maxPacketSizeEp0;
  unsigned short vendorId;
  unsigned short productId;
  unsigned short version;
  unsigned char manufacturerStringIndex;
  unsigned char productStringIndex;
  unsigned char serialNumberStringIndex;
  unsigned char nConfiguration;  // Reserved: 1
} UsbDevice;



// This structure is used with the result parameter of the API function
// usbHostGetConfigInfo(). Fields mainly relate to a Configuration Descriptor found
// in section 9.6.2 of the USB 1.1 specification.
typedef struct UsbConfig_
{
  unsigned char nInterface;
  unsigned char stringIndex;
  UsbBool selfPowered;
  UsbBool remoteWakeup;
  unsigned char maxPowerConsumption;
  char far *specificDesc;
  unsigned short specificDescLength;
} UsbConfig;



// This structure is used with the result parameter of the API function
// usbHostGetInterfaceInfo(). Fields mainly relate to an Interface Descriptor found
// in section 9.6.3 of the USB 1.1 specification.
typedef struct UsbInterface_
{
  unsigned char nAltSetting;
  unsigned char nEp;
  unsigned long epBitmap;
  unsigned char classCode;
  unsigned char subClassCode;
  unsigned char protocolCode;
  unsigned char stringIndex;
  char far *specificDesc;
  unsigned short specificDescLength;
} UsbInterface;

                                                       

// This structure is used with the result parameter of the API function
// usbHostGetEpInfo(). Fields mainly relate to an Endpoint Descriptor found
// in section 9.6.4 of the USB 1.1 specification.
typedef struct UsbEp_
{
  unsigned char transferType;
  unsigned short maxPacketSize;
  unsigned char interval;
  char far *specificDesc;
  unsigned short specificDescLength;
} UsbEp;

                                                       

/*******************************************************************************
* Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif



//------------------------------------------------------------------------------
// Prototypes of functions for both device and host mode
UsbError far _cdecl usbSend(
                            unsigned char address,
                            unsigned char epNumber,
                            void far *buffer,
                            unsigned length,
                            UsbBool less );

void far _cdecl usbFreeReceiveBuffer(
                                     void far *buffer );
UsbError far _cdecl usbWakeup(
                              void );
UsbError huge _cdecl usbSofNotify(
                                  unsigned char driverId,
                                  UsbBool enable );



//------------------------------------------------------------------------------
// Prototypes of functions for device mode only
UsbError far _cdecl usbDeviceInit(
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
                                  unsigned char pioNumber );
void far _cdecl usbDeviceDeinit(
                                void );
int far _cdecl usbDeviceRegisterInterface(
                                          unsigned char nEp,
                                          unsigned char classCode,
                                          unsigned char subClassCode,
                                          unsigned char protocolCode,
                                          char far *interfaceString );
int far _cdecl usbDeviceRegisterAltSetting(
                                           unsigned char interfaceId );
UsbError far _cdecl usbDeviceGetEps(
                                    unsigned char interfaceId,
                                    unsigned short far *epBitmap );
int far _cdecl usbDeviceConfigEp(
                                 unsigned char interfaceId,
                                 unsigned char altSettingId,
                                 unsigned char epNumber,
                                 unsigned char transferType,
                                 UsbBool in,
                                 unsigned short maxPacketSize,
                                 unsigned char interval );
UsbError far _cdecl usbDeviceAddSpecificDesc(
                                             unsigned char descriptorType,
                                             unsigned char idNumber,
                                             char far *descriptor,
                                             unsigned char descriptorLength );
void far _cdecl usbDeviceStart(
                               void );
void far _cdecl usbDeviceStop(
                              void );
UsbError far _cdecl usbDeviceStallEp(
                                     unsigned char epNumber );
UsbError far _cdecl usbDeviceEnableEp(
                                      unsigned char epNumber,
                                      UsbBool enable );



//------------------------------------------------------------------------------
// Prototypes of functions for host mode only
int far _cdecl usbHostInit(
                           UsbCallback callback,
                           unsigned char classCode,
                           unsigned char subClassCode,
                           unsigned char protocolCode,
                           unsigned short vendorId,
                           unsigned short productId,
                           unsigned short versionBcd );
void far _cdecl usbHostDeinit(
                              unsigned char driverId );
UsbError far _cdecl usbHostIssueToken(
                                      unsigned char address,
                                      unsigned char epNumber,
                                      unsigned char token );
UsbError far _cdecl usbHostClearQueue(
                                      unsigned char address,
                                      unsigned char epNumber,
                                      UsbBool in );
UsbError far _cdecl usbHostReserveEp0(
                                      unsigned char driverId,
                                      unsigned char address );
UsbError far _cdecl usbHostReleaseEp0(
                                      unsigned char driverId,
                                      unsigned char address );
UsbError far _cdecl usbHostGetDeviceInfo(
                                         unsigned char address,
                                         UsbDevice far *info,
                                         unsigned char size );
UsbError far _cdecl usbHostGetConfigInfo(
                                         unsigned char address,
                                         UsbConfig far *info,
                                         unsigned char size );
UsbError far _cdecl usbHostGetInterfaceInfo(
                                            unsigned char address,
                                            unsigned char interfaceId,
                                            unsigned char altSettingId,
                                            UsbInterface far *info,
                                            unsigned char size );
UsbError far _cdecl usbHostGetEpInfo(
                                     unsigned char address,
                                     unsigned char altSettingId,
                                     unsigned char epNumber,
                                     UsbBool in,
                                     UsbEp far *info,
                                     unsigned char size );
UsbError far _cdecl usbHostGetString(
                                     unsigned char driverId,
                                     unsigned char address,
                                     unsigned char stringId,
                                     char far *string );
UsbError far _cdecl usbHostGetStatus(
                                     unsigned char driverId,
                                     unsigned char address,
                                     unsigned char receiver,
                                     unsigned char index,
                                     unsigned short far *status );
UsbError far _cdecl usbHostSetClearFeature(
                                           unsigned char driverId,
                                           unsigned char address,
                                           unsigned char receiver,
                                           unsigned char index,
                                           unsigned char feature,
                                           UsbBool setFeature );
UsbError far _cdecl usbHostSetInterface(
                                        unsigned char driverId,
                                        unsigned char address,
                                        unsigned char interfaceId,
                                        unsigned char altSettingId );
                                   
                                   
                                   
#ifdef __cplusplus
}
#endif



#endif
// End of file


/******************************************************************************
*
* (c) 2006 by BECK IPC GmbH
* http://www.beck-ipc.com
*
*******************************************************************************
*
* Module:     usb_spec.h
* Function:   Constants and data structures from the USB specification 1.1.
*
*******************************************************************************
*
* $Header: c:\prjPib\IPC@CHIP\CLib\usb_spec.h, 7, 27.01.2009 09:13:04, Jan Schatz$
*
******************************************************************************/



#ifndef USB_SPEC_H
#define USB_SPEC_H



/******************************************************************************
* PID Tokens
* Refer to chapter 8.3.1 of the specification.
******************************************************************************/
#define USB_SPEC_PID_OUT    0x01U
#define USB_SPEC_PID_IN     0x09U
#define USB_SPEC_PID_SOF    0x05U
#define USB_SPEC_PID_SETUP  0x0DU
#define USB_SPEC_PID_DATA0  0x03U
#define USB_SPEC_PID_DATA1  0x0BU
#define USB_SPEC_PID_ACK    0x02U
#define USB_SPEC_PID_NAK    0x0AU
#define USB_SPEC_PID_STALL  0x0EU
#define USB_SPEC_PID_PRE    0x0CU



/******************************************************************************
* Standard device requests
* Refer to chapter 9.4 of the specification.
******************************************************************************/
// Request type
#define USB_SPEC_DEVICE_REQUEST_TYPE_HOST_TO_DEVICE      0x00U
#define USB_SPEC_DEVICE_REQUEST_TYPE_DEVICE_TO_HOST      0x80U
#define USB_SPEC_DEVICE_REQUEST_TYPE_STANDARD            0x00U
#define USB_SPEC_DEVICE_REQUEST_TYPE_CLASS_SPECIFIC      0x20U
#define USB_SPEC_DEVICE_REQUEST_TYPE_VENDOR_SPECIFIC     0x40U
#define USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_DEVICE     0x00U
#define USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_INTERFACE  0x01U
#define USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_ENDPOINT   0x02U
#define USB_SPEC_DEVICE_REQUEST_TYPE_RECEIVER_OTHER      0x03U


// Device request codes
#define USB_SPEC_DEVICE_REQUEST_GET_STATUS               0x00U
#define USB_SPEC_DEVICE_REQUEST_CLEAR_FEATURE            0x01U
#define USB_SPEC_DEVICE_REQUEST_SET_FEATURE              0x03U
#define USB_SPEC_DEVICE_REQUEST_SET_ADDRESS              0x05U
#define USB_SPEC_DEVICE_REQUEST_GET_DESCRIPTOR           0x06U
#define USB_SPEC_DEVICE_REQUEST_SET_DESCRIPTOR           0x07U
#define USB_SPEC_DEVICE_REQUEST_GET_CONFIGURATION        0x08U
#define USB_SPEC_DEVICE_REQUEST_SET_CONFIGURATION        0x09U
#define USB_SPEC_DEVICE_REQUEST_GET_INTERFACE            0x0AU
#define USB_SPEC_DEVICE_REQUEST_SET_INTERFACE            0x0BU
#define USB_SPEC_DEVICE_REQUEST_SYNC_FRAME               0x0CU


// (Maximum) size of data transferred during the data stage of a device request
#define USB_SPEC_DEVICE_REQUEST_GET_STATUS_DATA_SIZE     2U
#define USB_SPEC_DEVICE_REQUEST_GET_CONFIG_DATA_SIZE     1U
#define USB_SPEC_DEVICE_REQUEST_GET_INTERFACE_DATA_SIZE  1U



/******************************************************************************
* Constants regarding descriptors
* Refer to chapter 9.6 of the specification.
******************************************************************************/
#define USB_SPEC_DESCRIPTOR_TYPE_DEVICE       0x01U
#define USB_SPEC_DESCRIPTOR_TYPE_CONFIG       0x02U
#define USB_SPEC_DESCRIPTOR_TYPE_STRING       0x03U
#define USB_SPEC_DESCRIPTOR_TYPE_INTERFACE    0x04U
#define USB_SPEC_DESCRIPTOR_TYPE_EP           0x05U

#define USB_SPEC_DESCRIPTOR_SIZE_DEVICE       18U
#define USB_SPEC_DESCRIPTOR_SIZE_CONFIG       9U
#define USB_SPEC_DESCRIPTOR_SIZE_STRING       2U  // + the string itself
#define USB_SPEC_DESCRIPTOR_SIZE_INTERFACE    9U
#define USB_SPEC_DESCRIPTOR_SIZE_EP           7U
#define USB_SPEC_DESC_SIZE_MIN                2U  // Minimum descriptor size

#define USB_SPEC_VERSION                      0x0110U  // 1.1 (BCD)

#define USB_SPEC_EP_ADDRESS_IN                0x80U  // If the following mask is
                                                     // set in an endpoint
                                                     // descriptor's address field,
                                                     // it is an IN endpoint.

// Strings
#define USB_SPEC_MAX_STRING_LENGTH            126U  // ( 255 - 2 ) / 2
// Language descriptor for  english
#define USB_SPEC_STRING_LANGUAGE              0x0409U



// Power management
#define USB_SPEC_CONFIG_POWER_BUS             0x80U
#define USB_SPEC_CONFIG_POWER_SELF            0x40U
#define USB_SPEC_CONFIG_POWER_REMOTE          0x20U
#define USB_SPEC_CONFIG_POWER_FACTOR          2U  // Factor to covert configuration
                                                  // descriptor's bMaxPower field
                                                  // into mV



// Transfer types
#define USB_SPEC_TRANSFER_TYPE_CONTROL        0x00U
#define USB_SPEC_TRANSFER_TYPE_ISOCHRONOUS    0x01U
#define USB_SPEC_TRANSFER_TYPE_BULK           0x02U
#define USB_SPEC_TRANSFER_TYPE_INTERRUPT      0x03U
#define USB_SPEC_TRANSFER_TYPE_MASK           0x03U

// Maximum maximum packet sizes for the different transfer types
#define USB_SPEC_MAX_PACKET_SIZE_CONTROL      64U
#define USB_SPEC_MAX_PACKET_SIZE_ISOCHRONOUS  1023U
#define USB_SPEC_MAX_PACKET_SIZE_BULK         64U
#define USB_SPEC_MAX_PACKET_SIZE_INTERRUPT    64U



/******************************************************************************
* Feature selectors
* Refer to chapter 9.4 of the specification.
******************************************************************************/
#define USB_SPEC_FEATURE_STALL              0x00U
#define USB_SPEC_FEATURE_REMOTE_WAKEUP      0x01U



/******************************************************************************
* Constants regarding timing
* Refer to chapter 7.1.7.1 of the specification.
******************************************************************************/
#define USB_SPEC_TIME_DEBOUNCE              150U  // 100 ms + tolerance
#define USB_SPEC_TIME_RESET                 60U   // 10 ms + tolerance
#define USB_SPEC_TIME_RESET_RECOVERY        60U   // 10 ms + tolerance



/******************************************************************************
* Miscellaneous
******************************************************************************/
#define USB_SPEC_N_EP                 16U         // Number of endpoints per device
#define USB_SPEC_MIN_MAX_PACKET_SIZE  8U          // Minimum "maximum packet size"
#define USB_SPEC_BITRATE_FS           12000000UL  // Full speed bit rate
#define USB_SPEC_BITRATE_LS           1500000UL   // Low speed bit rate
#define USB_SPEC_BIT_STUFFING_FREQ    6U          // Number of bits after which a
#define USB_SPEC_MAX_FRAME_NUMBER     0x7FFU      // Highest possible USB frame number
#define USB_SPEC_FRAME_NUMBER_MASK    0x7FFU      // Frame number mask



/******************************************************************************
* Standard device request
* Refer to chapter 9.3 of the specification.
******************************************************************************/
typedef struct UsbSpecDeviceRequest_
{
  unsigned char requestType;
  unsigned char request;
  unsigned short value;
  unsigned short index;
  unsigned short length;
} UsbSpecDeviceRequest;



/******************************************************************************
* Device descriptor
* Refer to chapter 9.6.1 of the specification.
******************************************************************************/
typedef struct UsbSpecDeviceDesc_
{
  unsigned char length;
  unsigned char descType;
  unsigned short usbVersion;
  unsigned char deviceClass;
  unsigned char deviceSubClass;
  unsigned char deviceProtocol;
  unsigned char maxPacketSizeEp0;
  unsigned short vendorId;
  unsigned short productId;
  unsigned short deviceVersion;
  unsigned char manufacturerStringIndex;
  unsigned char productStringIndex;
  unsigned char serialNumberStringIndex;
  unsigned char nConfigurations;
} UsbSpecDeviceDesc;



/******************************************************************************
* Configuration descriptor
* Refer to chapter 9.6.2 of the specification.
******************************************************************************/
typedef struct UsbSpecConfigDesc_
{
  unsigned char length;
  unsigned char descType;
  unsigned short totalLength;
  unsigned char nInterfaces;
  unsigned char index;
  unsigned char stringIndex;
  unsigned char attributes;
  unsigned char maxPower;
} UsbSpecConfigDesc;



/******************************************************************************
* Interface descriptor
* Refer to chapter 9.6.3 of the specification.
******************************************************************************/
typedef struct UsbSpecInterfaceDesc_
{
  unsigned char length;
  unsigned char descType;
  unsigned char index;
  unsigned char alternateSetting;
  unsigned char nEp;
  unsigned char interfaceClass;
  unsigned char interfaceSubClass;
  unsigned char interfaceProtocol;
  unsigned char stringIndex;
} UsbSpecInterfaceDesc;



/******************************************************************************
* Endpoint descriptor
* Refer to chapter 9.6.4 of the specification.
******************************************************************************/
typedef struct UsbSpecEpDesc_
{
  unsigned char length;
  unsigned char descType;
  unsigned char epAddr;
  unsigned char attributes;
  unsigned short maxPacketSize;
  unsigned char interval;
} UsbSpecEpDesc;



/******************************************************************************
* Device states
* Refer to chapter 9.1 of the specification
******************************************************************************/
typedef enum
{
  // USB_SPEC_DEVICE_STATE_ATTACHED,
  USB_SPEC_DEVICE_STATE_POWERED,
  USB_SPEC_DEVICE_STATE_DEFAULT,
  USB_SPEC_DEVICE_STATE_ADDRESS,
  USB_SPEC_DEVICE_STATE_CONFIGURED
  // USB_SPEC_DEVICE_STATE_SUSPENDED
} UsbSpecDeviceState;



#endif
// End of file


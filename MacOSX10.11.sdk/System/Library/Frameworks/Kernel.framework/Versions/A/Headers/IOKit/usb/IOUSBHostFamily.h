//
//  IOUSBHostFamily.h
//  IOUSBHostFamily
//
//  Created by Dan Wilson on 1/14/15.
//
//

#ifndef IOUSBHostFamily_IOUSBHostFamily_h
#define IOUSBHostFamily_IOUSBHostFamily_h

#include <IOKit/usb/StandardUSB.h>

#pragma mark Typedefs

typedef uint16_t tUSBHostDeviceAddress;

#pragma mark General enumerations

#ifdef __cplusplus
using namespace StandardUSB;
#endif

enum tEndpointDirection
{
    kEndpointDirectionOut       = (kEndpointDescriptorDirectionOut >> kEndpointDescriptorDirectionPhase),
    kEndpointDirectionIn        = (kEndpointDescriptorDirectionIn >> kEndpointDescriptorDirectionPhase),
    kEndpointDirectionUnknown   = 2
};

typedef enum tEndpointDirection tEndpointDirection;

enum tEndpointType
{
    kEndpointTypeControl        = (kEndpointDescriptorTransferTypeControl >> kEndpointDescriptorTransferTypePhase),
    kEndpointTypeIsochronous    = (kEndpointDescriptorTransferTypeIsochronous >> kEndpointDescriptorTransferTypePhase),
    kEndpointTypeBulk           = (kEndpointDescriptorTransferTypeBulk >> kEndpointDescriptorTransferTypePhase),
    kEndpointTypeInterrupt      = (kEndpointDescriptorTransferTypeInterrupt >> kEndpointDescriptorTransferTypePhase)
};

typedef enum tEndpointType tEndpointType;

enum tDeviceRequestDirection
{
    kRequestDirectionOut            = (kDeviceRequestDirectionOut >> kDeviceRequestDirectionPhase),
    kRequestDirectionIn             = (kDeviceRequestDirectionIn >> kDeviceRequestDirectionPhase)
};

typedef enum tDeviceRequestDirection tDeviceRequestDirection;

enum tDeviceRequestType
{
    kRequestTypeStandard            = (kDeviceRequestTypeStandard >> kDeviceRequestTypePhase),
    kRequestTypeClass               = (kDeviceRequestTypeClass >> kDeviceRequestTypePhase),
    kRequestTypeVendor              = (kDeviceRequestTypeVendor >> kDeviceRequestTypePhase)
};

typedef enum tDeviceRequestType tDeviceRequestType;

enum tDeviceRequestRecipient
{
    kRequestRecipientDevice         = (kDeviceRequestRecipientDevice >> kDeviceRequestRecipientPhase),
    kRequestRecipientInterface      = (kDeviceRequestRecipientInterface >> kDeviceRequestRecipientPhase),
    kRequestRecipientEndpoint       = (kDeviceRequestRecipientEndpoint >> kDeviceRequestRecipientPhase),
    kRequestRecipientOther          = (kDeviceRequestRecipientOther >> kDeviceRequestRecipientPhase)
};

typedef enum tDeviceRequestRecipient tDeviceRequestRecipient;

inline uint8_t makeDeviceRequestbmRequestType(tDeviceRequestDirection direction, tDeviceRequestType type, tDeviceRequestRecipient recipient)
{
    return   ((direction << kDeviceRequestDirectionPhase) & kDeviceRequestDirectionMask)
            | ((type << kDeviceRequestTypePhase) & kDeviceRequestTypeMask)
            | ((recipient << kDeviceRequestRecipientPhase) & kDeviceRequestRecipientMask);
}

enum
{
    kUSBHostVendorSpecificClass             = 255,
    kUSBHostMaxDevices                      = 128,           // The largest number of devices permitted on USB 2.0 buses
    kUSBHostMaxPipes                        = 32,            // The largest number of endpoints permitted on USB devices
    kUSBHostMaxCountFullSpeedIsochronous    = 1023,       // max size (bytes) of any one Isoc frame for 1 FS endpoint
    kUSBHostVendorIDAppleComputer           = 0x05AC
};

/*!
 * @brief Connection speeds used internally by IOUSBHostFamily
 */
enum
{
    kUSBHostConnectionSpeedLow   = 0,
    kUSBHostConnectionSpeedFull  = 1,
    kUSBHostConnectionSpeedHigh  = 2,
    kUSBHostConnectionSpeedSuper = 3,
    kUSBHostConnectionSpeedCount = 4
};

/*!
 @define IOUSBHostFamily message codes
 @discussion Messages specific to the IOUSBHostFamily
 */

// The two most significant bits of the error and message code are used to indicate a USB subgroup.
#define iokit_usblegacy_group    (0 << StandardUSBBitRangePhase(12, 13))
#define iokit_usbhost_group      (1 << StandardUSBBitRangePhase(12, 13))
#define iokit_usb_codemask       StandardUSBBitRange(0, 11)

#define iokit_usbhost_msg(message) ((uint32_t)(iokit_family_msg(sub_iokit_usb, iokit_usbhost_group | (message & iokit_usb_codemask))))

#define kUSBHostMessageConfigurationSet               iokit_usbhost_msg(0x00)    // 0xe0005000  IOUSBHostDevice -> clients upon a setConfiguration call.
#define kUSBHostMessageRenegotiateCurrent             iokit_usbhost_msg(0x01)    // 0xe0005001  Request clients to renegotiate bus current allocations

#define kUSBHostMessageUpdateIdlePolicy               iokit_usbhost_msg(0x100)   // 0xe0005100  Internal use only.  IOUSBHostInterface -> IOUSBHostDevice to update its idle policy.
#define kUSBHostMessageRemoteWake                     iokit_usbhost_msg(0x101)   // 0xe0005101  Internal use only.  AppleUSBHostPort -> IOUSBHostDevice upon a remote wake event.
#define kUSBHostMessageDeviceSuspend                  iokit_usbhost_msg(0x102)   // 0xe0005102  Internal use only.  IOUSBHostDevice -> clients upon a suspend event.
#define kUSBHostMessageDeviceResume                   iokit_usbhost_msg(0x103)   // 0xe0005103  Internal use only.  IOUSBHostDevice -> clients upon a resume event.
#define kUSBHostMessageControllerPortsCreated         iokit_usbhost_msg(0x104)   // 0xe0005104  Internal use only.  AppleUSBHostController -> clients after all ports have been created.
#define kUSBHostMessageDeviceConnected                iokit_usbhost_msg(0x105)   // 0xe0005105  Apple Internal use only.  AppleUSBRemovablePort -> clients after a connect.
#define kUSBHostMessageDeviceDisconnected             iokit_usbhost_msg(0x106)   // 0xe0005106  Apple Internal use only.  AppleUSBRemovablePort -> clients after a disconnect.

/*!
 @defined IOUSBHostFamily error codes
 @discussion  Errors specific to the IOUSBHostFamily.  Note that the iokit_usb_err(x) translates to 0xe0004xxx, where xxx is the value in parenthesis as a hex number.
 */
#define iokit_usbhost_err(message) ((IOReturn)(iokit_family_err(sub_iokit_usb, iokit_usbhost_group | (message & iokit_usb_codemask))))

#define kUSBHostReturnPipeStalled   iokit_usbhost_err(0x0)  // 0xe0005000  Pipe has issued a STALL handshake.  Use clearStall to clear this condition.
#define kUSBHostReturnNoPower       iokit_usbhost_err(0x1)  // 0xe0005001  A setConfiguration call was not able to succeed because all configurations require more power than is available.

/*!
 * @brief Port types returned by IOUSBHostDevice::getPortStatus
 *
 * @constant kUSBHostPortTypeStandard A general-purpose USB port.
 * @constant kUSBHostPortTypeCaptive The attached device cannot be physically disconnected from the port.
 * @constant kUSBHostPortTypeInternal The attached device cannot be physically disconnected from the host machine.
 * @constant kUSBHostPortTypeAccessory The attached device may require authentication before function drivers can access it.
 * @constant kUSBHostPortTypeCount The number of entries in this enum.
 */
enum tUSBHostPortType
{
    kUSBHostPortTypeStandard = 0,
    kUSBHostPortTypeCaptive,
    kUSBHostPortTypeInternal,
    kUSBHostPortTypeAccessory,
    kUSBHostPortTypeCount
};

/*!
 * @brief Connection speeds returned by IOUSBHostDevice::getPortStatus
 * @discussion This enumeration matches the default speed ID mappings defined in XHCI 1.0 Table 147.
 *
 * @constant kUSBHostPortConnectionSpeedNone No device is connected
 * @constant kUSBHostPortConnectionSpeedFull A full-speed (12 Mb/s) device is connected
 * @constant kUSBHostPortConnectionSpeedLow A low-speed (1.5 Mb/s) device is connected
 * @constant kUSBHostPortConnectionSpeedHigh A high-speed (480 Mb/s) device is connected)
 * @constant kUSBHostPortConnectionSpeedSuper A superspeed (5 Gb/s) device is connected)
 */
enum tUSBHostConnectionSpeed
{
    kUSBHostPortConnectionSpeedNone  = 0,
    kUSBHostPortConnectionSpeedFull  = 1,
    kUSBHostPortConnectionSpeedLow   = 2,
    kUSBHostPortConnectionSpeedHigh  = 3,
    kUSBHostPortConnectionSpeedSuper = 4,
    kUSBHostPortConnectionSpeedCount = 5
};

/*!
 * @brief Values returned by IOUSBHostDevice::getPortStatus
 *
 * @constant kUSBHostPortStatusPortTypeMask The mask for bits representing the port type.
 * @constant kUSBHostPortStatusPortTypeStandard A general-purpose USB port.
 * @constant kUSBHostPortStatusPortTypeCaptive The attached device cannot be physically disconnected from the port.
 * @constant kUSBHostPortStatusPortTypeInternal The attached device cannot be physically disconnected from the host machine.
 * @constant kUSBHostPortStatusPortTypeAccessory The attached device may require authentication before function drivers can access it.
 * @constant kUSBHostPortStatusConnectedSpeedMask The mask for bits representing the connection state.
 * @constant kUSBHostPortStatusConnectedSpeedNone The port does not have a connected device.
 * @constant kUSBHostPortStatusConnectedSpeedFull The port has a full-speed device connected.
 * @constant kUSBHostPortStatusConnectedSpeedLow The port has a low-speed device connected.
 * @constant kUSBHostPortStatusConnectedSpeedHigh The port has a high-speed device connected.
 * @constant kUSBHostPortStatusConnectedSpeedSuper The port has a superspeed device connected.
 * @constant kUSBHostPortStatusResetting The port is currently resetting the link.
 * @constant kUSBHostPortStatusEnabled The port is enabled and packets are permitted to reach the device.  Not valid unless kUSBHostPortStatusConnectedSpeedMask is nonzero.
 * @constant kUSBHostPortStatusSuspended The port is suspended.  Not valid unless kUSBHostPortStatusConnectedSpeedMask is nonzero.
 * @constant kUSBHostPortStatusOvercurrent The port is in the overcurrent condition.
 * @constant kUSBHostPortStatusTestMode The port is in test mode.
 */
enum tUSBHostPortStatus
{
    kUSBHostPortStatusPortTypeMask          = StandardUSBBitRange(0, 3),
    kUSBHostPortStatusPortTypePhase         = StandardUSBBitRangePhase(0, 3),
    kUSBHostPortStatusPortTypeStandard      = (kUSBHostPortTypeStandard << StandardUSBBitRangePhase(0, 3)),
    kUSBHostPortStatusPortTypeCaptive       = (kUSBHostPortTypeCaptive << StandardUSBBitRangePhase(0, 3)),
    kUSBHostPortStatusPortTypeInternal      = (kUSBHostPortTypeInternal << StandardUSBBitRangePhase(0, 3)),
    kUSBHostPortStatusPortTypeAccessory     = (kUSBHostPortTypeAccessory << StandardUSBBitRangePhase(0, 3)),
    kUSBHostPortStatusPortTypeReserved      = StandardUSBBitRange(4, 7),
    kUSBHostPortStatusConnectedSpeedMask    = StandardUSBBitRange(8, 10),
    kUSBHostPortStatusConnectedSpeedPhase   = StandardUSBBitRangePhase(8, 10),
    kUSBHostPortStatusConnectedSpeedNone    = (kUSBHostPortConnectionSpeedNone << StandardUSBBitRangePhase(8, 10)),
    kUSBHostPortStatusConnectedSpeedFull    = (kUSBHostPortConnectionSpeedFull << StandardUSBBitRangePhase(8, 10)),
    kUSBHostPortStatusConnectedSpeedLow     = (kUSBHostPortConnectionSpeedLow << StandardUSBBitRangePhase(8, 10)),
    kUSBHostPortStatusConnectedSpeedHigh    = (kUSBHostPortConnectionSpeedHigh << StandardUSBBitRangePhase(8, 10)),
    kUSBHostPortStatusConnectedSpeedSuper   = (kUSBHostPortConnectionSpeedSuper << StandardUSBBitRangePhase(8, 10)),
    kUSBHostPortStatusResetting             = StandardUSBBit(11),
    kUSBHostPortStatusEnabled               = StandardUSBBit(12),
    kUSBHostPortStatusSuspended             = StandardUSBBit(13),
    kUSBHostPortStatusOvercurrent           = StandardUSBBit(14),
    kUSBHostPortStatusTestMode              = StandardUSBBit(15)
};

/*!
 @enum Default control request timeout values in milliseconds
 @discussion default values used for data and completion timeouts.
 */
enum
{
#if USB_COMPLIANCE_MODE
    kUSBHostSetAddressTimeout                      = 50,    // USB 2.0 9.2.6.3
    kUSBHostStandardRequestNoDataTimeout           = 500,   // USB 2.0 9.2.6.4
    kUSBHostStandardRequestCompletionTimeout       = 5000,  // USB 2.0 9.2.6.4
    kUSBHostStandardRequestSimpleCompletionTimeout = 50,    // USB 2.0 9.2.6.4 Standard request with no data stage
    kUSBHostClassRequestNoDataTimeout              = 500,   // USB 2.0 9.2.6.5
    kUSBHostClassRequestCompletionTimeout          = 5000,  // USB 2.0 9.2.6.5
    kUSBHostVendorRequestNoDataTimeout             = 0,
    kUSBHostVendorRequestCompletionTimeout         = 5000,
#else
    // More tolerant timeout values for noncompliant devices
    kUSBHostSetAddressTimeout                      = 1000,
    kUSBHostStandardRequestNoDataTimeout           = 0,
    kUSBHostStandardRequestCompletionTimeout       = 5000,
    kUSBHostStandardRequestSimpleCompletionTimeout = 1000,
    kUSBHostClassRequestNoDataTimeout              = 0,
    kUSBHostClassRequestCompletionTimeout          = 5000,
    kUSBHostVendorRequestNoDataTimeout             = 0,
    kUSBHostVendorRequestCompletionTimeout         = 5000,
#endif
    kUSBHostDefaultControlNoDataTimeoutMS          = 0,
    kUSBHostDefaultControlCompletionTimeoutMS      = 5000
};

#pragma mark Registry property names

#define kUSBHostMatchingPropertySpeed                           "USBSpeed"
#define kUSBHostMatchingPropertyPortType                        "USBPortType"

#define kUSBHostMatchingPropertyVendorID                        "idVendor"
#define kUSBHostMatchingPropertyProductID                       "idProduct"
#define kUSBHostMatchingPropertyProductIDMask                   "idProductMask"
#define kUSBHostMatchingPropertyProductIDArray                  "idProductArray"
#define kUSBHostMatchingPropertyDeviceClass                     "bDeviceClass"
#define kUSBHostMatchingPropertyDeviceSubClass                  "bDeviceSubClass"
#define kUSBHostMatchingPropertyDeviceProtocol                  "bDeviceProtocol"
#define kUSBHostMatchingPropertyDeviceReleaseNumber             "bcdDevice"
#define kUSBHostMatchingPropertyConfigurationValue              "bConfigurationValue"
#define kUSBHostMatchingPropertyInterfaceClass                  "bInterfaceClass"
#define kUSBHostMatchingPropertyInterfaceSubClass               "bInterfaceSubClass"
#define kUSBHostMatchingPropertyInterfaceProtocol               "bInterfaceProtocol"
#define kUSBHostMatchingPropertyInterfaceNumber                 "bInterfaceNumber"

#define kUSBHostPropertyLocationID                              "locationID"
#define kUSBHostPropertyDataToggleResetOverride                 "kUSBDataToggleResetOverride"
#define kUSBHostPropertyDebugOptions                            "kUSBDebugOptions"
#define kUSBHostPropertyWakePowerSupply                         "kUSBWakePowerSupply"
#define kUSBHostPropertySleepPowerSupply                        "kUSBSleepPowerSupply"
#define kUSBHostPropertyWakePortCurrentLimit                    "kUSBWakePortCurrentLimit"
#define kUSBHostPropertySleepPortCurrentLimit                   "kUSBSleepPortCurrentLimit"
#define kUSBHostPropertyFailedRemoteWake                        "kUSBFailedRemoteWake"

#if TARGET_OS_EMBEDDED
// Only define these properties on embedded platforms because the legacy IOUSBLib code still uses them
#define kUSBHostDevicePropertyAddress                           "kUSBAddress"
#define kUSBHostDevicePropertyManufacturerStringIndex           "iManufacturer"
#define kUSBHostDevicePropertySerialNumberStringIndex           "iSerialNumber"
#define kUSBHostDevicePropertyProductStringIndex                "iProduct"
#define kUSBHostDevicePropertyProductString                     "kUSBProductString"
#define kUSBHostDevicePropertyNumConfigs                        "bNumConfigurations"
#define kUSBHostDevicePropertyMaxPacketSize                     "bMaxPacketSize0"
#define kUSBHostDevicePropertyStandardVersion                   "bcdUSB"
#endif
#define kUSBHostDevicePropertyVendorString                      "kUSBVendorString"
#define kUSBHostDevicePropertySerialNumberString                "kUSBSerialNumberString"
#define kUSBHostDevicePropertyContainerID                       "kUSBContainerID"
#define kUSBHostDevicePropertyFailedRequestedPower              "kUSBFailedRequestedPower"
#define kUSBHostDevicePropertyResumeRecoveryTime                "kUSBResumeRecoveryTime"
#define kUSBHostDevicePropertyPreferredConfiguration            "kUSBPreferredConfiguration"
#define kUSBHostDevicePropertyCurrentConfiguration              "kUSBCurrentConfiguration"
#define kUSBHostDevicePropertyRemoteWakeOverride                "kUSBRemoteWakeOverride"
#define kUSBHostDevicePropertyConfigurationDescriptorOverride   "kUSBConfigurationDescriptorOverride"
#define kUSBHostDevicePropertyConfigurationCurrentOverride      "kUSBConfigurationCurrentOverride"
#define kUSBHostDevicePropertyResetDurationOverride             "kUSBResetDurationOverride"

#if TARGET_OS_EMBEDDED
#define kUSBHostInterfacePropertyStringIndex                    "iInterface"
#define kUSBHostInterfacePropertyString                         "kUSBString"
#define kUSBHostInterfacePropertyNumEndpoints                   "bNumEndpoints"
#endif
#define kUSBHostInterfacePropertyAlternateSetting               "bAlternateSetting"

#define kUSBHostPortPropertyRemovable                           "removable"
#define kUSBHostPortPropertyTestMode                            "kUSBTestMode"
#define kUSBHostPortPropertyBusCurrentAllocation                "kUSBBusCurrentAllocation"
#define kUSBHostPortPropertyConnectable                         "UsbConnectable"
#define kUSBHostPortPropertyConnectorType                       "UsbConnector"
#define kUSBHostPortPropertyMux                                 "UsbMux"

#define kUSBHostHubPropertyPowerSupply                          "kUSBHubPowerSupply"                    // OSNumber mA available for downstream ports, 0 for bus-powered
#define kUSBHostHubPropertyIdlePolicy                           "kUSBHubIdlePolicy"                     // OSNumber ms to be used as device idle policy
#define kUSBHostHubPropertyStartupDelay                         "kUSBHubStartupDelay"                   // OSNumber ms delay before creating downstream ports
#define kUSBHostHubPropertyPortSequenceDelay                    "kUSBHubPortSequenceDelay"              // OSNumber ms delay between port creation

#define kUSBHostControllerPropertyIsochronousRequiresContiguous "kUSBIsochronousRequiresContiguous"
#define kUSBHostControllerPropertyDebugError                    "kUSBDebugError"
#define kUSBHostControllerPropertySleepSupported                "kUSBSleepSupported"
#define kUSBHostControllerPropertyMuxEnabled                    "kUSBMuxEnabled"

#define kUSBHostPortPropertyExternalDeviceResetController       "kUSBHostPortExternalDeviceResetController"
#define kUSBHostPortPropertyExternalDevicePowerController       "kUSBHostPortExternalDevicePowerController"

#define kUSBHostPortPropertyCardReader                          "kUSBHostPortPropertyCardReader"

#define kUSBHostPortPropertyOffset                              "kUSBHostPortPropertyOffset"

#pragma mark APCI enumerations

// UPC definitions from ACPI Rev 4.0
typedef enum
{
    kUSBHostPortNotConnectable = 0,                 // Port is not connectable
    kUSBHostPortConnectable    = 1                  // Port is connectable either user visible or invisible
} tUSBHostPortConnectable;

typedef enum
{
    kUSBHostConnectorTypeA              = 0x00,
    kUSBHostConnectorTypeMiniAB         = 0x01,
    kUSBHostConnectorTypeExpressCard    = 0x02,
    kUSBHostConnectorTypeUSB3A          = 0x03,
    kUSBHostConnectorTypeUSB3B          = 0x04,
    kUSBHostConnectorTypeUSB3MicroB     = 0x05,
    kUSBHostConnectorTypeUSB3MicroAB    = 0x06,
    kUSBHostConnectorTypeUSB3PowerB     = 0x07,
    kUSBHostConnectorTypeUnknown        = 0xFE,
    kUSBHostConnectorTypeProprietary    = 0xFF
} tUSBHostConnectorType;

#if !TARGET_OS_EMBEDDED

#ifndef kACPIDevicePathKey
#define kACPIDevicePathKey          "acpi-path"
#endif

#ifndef kACPIInterruptTypeValid
#define kACPIInterruptTypeValid     (1 << 1)
#endif

// ACPI methods
#define kUSBHostACPIPropertyXHCICompanion   "XHCN"      // The number of the companion XHCI controller, used for multiplexed ports
#define kUSBHostACPIPropertyMultiplexor     "MUXS"      // The ACPI method name for the port multiplexor

// _UPC
// _EJD

#define kSDControllerGPIOResetACPIMethod                "SRST"
#define kSDControllerGPIOPowerACPIMethod                "SPWR"
#define kSDPortConnectionBehaviorACPIMethod             "SBHV"
#define kSDControllerGPIOResetPropertyKey               "GPIO_RESET"
#define kSDControllerCaptiveUSB3ReaderKey               "U3SD"
#define kGetBehaviorACPIMethod                          "GBHV"
#define kGPEACPIString                                  "_GPE"
#define kRDYForGPIOTest                                 "RDYG"
#define kReconfiguredCount                              "RCFG"

#endif

#endif

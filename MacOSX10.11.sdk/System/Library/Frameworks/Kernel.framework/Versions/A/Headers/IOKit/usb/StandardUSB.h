//
//  StandardUSB.h
//  IOUSBHostFamily
//
//  Created by Dan Wilson on 12/11/13.
//
//

#ifndef IOUSBHostFamily_StandardUSB_h
#define IOUSBHostFamily_StandardUSB_h

#include <IOKit/IOTypes.h>
#include <libkern/OSByteOrder.h>
#include <IOKit/IOReturn.h>

#pragma mark Platform endianness and bitmask macros

#define USBToHost16 OSSwapLittleToHostInt16
#define HostToUSB16 OSSwapHostToLittleInt16

#define USBToHost32 OSSwapLittleToHostInt32
#define HostToUSB32 OSSwapHostToLittleInt32

#define USBToHost64 OSSwapLittleToHostInt64
#define HostToUSB64 OSSwapHostToLittleInt64

#define StandardUSBBit(bit)                     ((uint32_t)(1) << bit)
#define StandardUSBBitRange(start, end)         (~(((uint32_t)(1) << start) - 1) & ((1 << end) | ((1 << end) - 1)))
#define StandardUSBBitRange64(start, end)       (~(((uint64_t)(1) << start) - 1) & ((1 << end) | ((1 << end) - 1)))
#define StandardUSBBitRangePhase(start, end)    (start)

#ifdef __cplusplus

#pragma mark StandardUSB namespace
namespace StandardUSB
{
    
#endif // __cplusplus
    
#pragma mark Descriptor definitions
    // USB 2.0 Table 9-5
    // USB 3.0 Table 9-6
    enum tDescriptorType
    {
        kDescriptorTypeDevice = 1,
        kDescriptorTypeConfiguration = 2,
        kDescriptorTypeString = 3,
        kDescriptorTypeInterface = 4,
        kDescriptorTypeEndpoint = 5,
        kDescriptorTypeDeviceQualifier = 6,
        kDescriptorTypeOtherSpeedConfiguration = 7,
        kDescriptorTypeInterfacePower = 8,
        kDescriptorTypeOTG = 9,
        kDescriptorTypeDebug = 10,
        kDescriptorTypeInterfaceAssociation = 11,
        kDescriptorTypeBOS = 15,
        kDescriptorTypeDeviceCapability = 16,
        kDescriptorTypeHub = 41,
        kDescriptorTypeSuperSpeedHub = 42,
        kDescriptorTypeSuperSpeedUSBEndpointCompanion = 48
    };
    
    typedef enum tDescriptorType tDescriptorType;
    
    enum tDescriptorSize
    {
        kDescriptorSize = 2,
        kDescriptorSizeDevice = 18,
        kDescriptorSizeConfiguration = 9,
        kDescriptorSizeInterface = 9,
        kDescriptorSizeEndpoint = 7,
        kDescriptorSizeDeviceQualifier = 10,
        kDescriptorSizeInterfaceAssociation = 8,
        kDescriptorSizeBOS = 5,
        kDescriptorSizeDeviceCapability = 3,
        kDescriptorSizeUSB20ExtensionCapability = 7,
        kDescriptorSizeSuperSpeedUSBDeviceCapability = 10,
        kDescriptorSizeContainerIDCapability = 20,
        kDescriptorSizeHubMinimum = 9,
        kDescriptorSizeHubMaximum = 21,
        kDescriptorSizeSuperSpeedHub = 12,
        kDescriptorSizeSuperSpeedUSBEndpointCompanion = 6,
        kDescriptorSizeLargestStandard = kDescriptorSizeHubMaximum
    };
    
    typedef enum tDescriptorSize tDescriptorSize;
    
    // USB 2.0 9.5: Descriptors
    struct Descriptor
    {
        uint8_t bLength;
        uint8_t bDescriptorType;
    } __attribute__((packed));
    
    typedef struct Descriptor Descriptor;
    
    
#ifdef __cplusplus
    // USB 2.0 9.6.1: Device
    struct DeviceDescriptor : public Descriptor
    {
#else
    struct DeviceDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint16_t    bcdUSB;
        uint8_t     bDeviceClass;
        uint8_t     bDeviceSubClass;
        uint8_t     bDeviceProtocol;
        uint8_t     bMaxPacketSize0;
        uint16_t    idVendor;
        uint16_t    idProduct;
        uint16_t    bcdDevice;
        uint8_t     iManufacturer;
        uint8_t     iProduct;
        uint8_t     iSerialNumber;
        uint8_t     bNumConfigurations;
    } __attribute__((packed));
        
    typedef struct DeviceDescriptor DeviceDescriptor;
        
    
#ifdef __cplusplus
    // USB 2.0 9.6.2: Device Qualifier
    struct DeviceQualifierDescriptor : public Descriptor
    {
#else
    struct DeviceQualifierDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint16_t    bcdUSB;
        uint8_t     bDeviceClass;
        uint8_t     bDeviceSubClass;
        uint8_t     bDeviceProtocol;
        uint8_t     bMaxPacketSize0;
        uint8_t     bNumConfigurations;
        uint8_t     bReserved;
    } __attribute__((packed));
    
    typedef struct DeviceQualifierDescriptor DeviceQualifierDescriptor;
        
        
#ifdef __cplusplus
    // USB 2.0 9.6.3: Configuration
    struct ConfigurationDescriptor : public Descriptor
    {
#else
    struct ConfigurationDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint16_t    wTotalLength;
        uint8_t     bNumInterfaces;
        uint8_t     bConfigurationValue;
        uint8_t     iConfiguration;
        uint8_t     bmAttributes;
        uint8_t     bMaxPower;
    } __attribute__((packed));
    
    typedef struct ConfigurationDescriptor ConfigurationDescriptor;
        
    
    enum
    {
        kConfigurationDescriptorAttributeRemoteWakeCapable  = StandardUSBBit(5),
        kConfigurationDescriptorAttributeSelfPowered        = StandardUSBBit(6)
    };
    
        
#ifdef __cplusplus
    // USB 2.0 9.6.5: Interface
    struct InterfaceDescriptor : public Descriptor
    {
#else
    struct InterfaceDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint8_t     bInterfaceNumber;
        uint8_t     bAlternateSetting;
        uint8_t     bNumEndpoints;
        uint8_t     bInterfaceClass;
        uint8_t     bInterfaceSubClass;
        uint8_t     bInterfaceProtocol;
        uint8_t     iInterface;
    } __attribute__((packed));
    
    typedef struct InterfaceDescriptor InterfaceDescriptor;
        
    
#ifdef __cplusplus
    // USB 2.0 9.6.6: Endpoint
    struct EndpointDescriptor : public Descriptor
    {
#else
    struct EndpointDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint8_t     bEndpointAddress;
        uint8_t     bmAttributes;
        uint16_t    wMaxPacketSize;
        uint8_t     bInterval;
    } __attribute__((packed));
        
    typedef struct EndpointDescriptor EndpointDescriptor;
    
    enum
    {
        kEndpointDescriptorNumber                  = StandardUSBBitRange(0, 3),
        kEndpointDescriptorEndpointAddressReserved = StandardUSBBitRange(4, 6),
        kEndpointDescriptorDirection               = StandardUSBBit(7),
        kEndpointDescriptorDirectionPhase          = StandardUSBBitRangePhase(7, 7),
        kEndpointDescriptorDirectionOut            = 0,
        kEndpointDescriptorDirectionIn             = StandardUSBBit(7),
        
        kEndpointDescriptorTransferType                    = StandardUSBBitRange(0, 1),
        kEndpointDescriptorTransferTypePhase               = StandardUSBBitRangePhase(0, 1),
        kEndpointDescriptorTransferTypeControl             = (0 << StandardUSBBitRangePhase(0, 1)),
        kEndpointDescriptorTransferTypeIsochronous         = (1 << StandardUSBBitRangePhase(0, 1)),
        kEndpointDescriptorTransferTypeBulk                = (2 << StandardUSBBitRangePhase(0, 1)),
        kEndpointDescriptorTransferTypeInterrupt           = (3 << StandardUSBBitRangePhase(0, 1)),
        kEndpointDescriptorSynchronizationType             = StandardUSBBitRange(2, 3),
        kEndpointDescriptorSynchronizationTypeNone         = (0 << StandardUSBBitRangePhase(2, 3)),
        kEndpointDescriptorSynchronizationTypeAsynchronous = (1 << StandardUSBBitRangePhase(2, 3)),
        kEndpointDescriptorSynchronizationTypeAdaptive     = (2 << StandardUSBBitRangePhase(2, 3)),
        kEndpointDescriptorSynchronizationTypeSynchronous  = (3 << StandardUSBBitRangePhase(2, 3)),
        kEndpointDescriptorUsageType                       = StandardUSBBitRange(4, 5),
        kEndpointDescriptorUsageTypeInterruptPeriodic      = (0 << StandardUSBBitRangePhase(4, 5)),
        kEndpointDescriptorUsageTypeInterruptNotification  = (1 << StandardUSBBitRangePhase(4, 5)),
        kEndpointDescriptorUsageTypeInterruptReserved1     = (2 << StandardUSBBitRangePhase(4, 5)),
        kEndpointDescriptorUsageTypeInterruptReserved2     = (3 << StandardUSBBitRangePhase(4, 5)),
        kEndpointDescriptorUsageTypeIsocData               = (0 << StandardUSBBitRangePhase(4, 5)),
        kEndpointDescriptorUsageTypeIsocFeedback           = (1 << StandardUSBBitRangePhase(4, 5)),
        kEndpointDescriptorUsageTypeIsocImplicit           = (2 << StandardUSBBitRangePhase(4, 5)),
        kEndpointDescriptorUsageTypeIsocReserved           = (3 << StandardUSBBitRangePhase(4, 5)),
        
        kEndpointDescriptorPacketSize          = StandardUSBBitRange(0, 10),
        kEndpointDescriptorPacketSizePhase     = StandardUSBBitRangePhase(0, 10),
        kEndpointDescriptorPacketSizeMult      = StandardUSBBitRange(11, 12),
        kEndpointDescriptorPacketSizeMultPhase = StandardUSBBitRangePhase(11, 12),
        kEndpointDescriptorReserved            = StandardUSBBitRange(13, 15),
        kEndpointDescriptorReservedPhase       = StandardUSBBitRangePhase(13, 15)
    };
    
    // USB Language Identifiers 1.0
    enum tLanguageID
    {
        kLanguageIDEnglishUS = 0x0409
    };
    
    typedef enum tLanguageID tLanguageID;
        
        
#ifdef __cplusplus
    // USB 2.0 9.6.7: String
    struct StringDescriptor : public Descriptor
    {
#else
    struct StringDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint8_t     bString[1];
    } __attribute__((packed));
        
    typedef struct StringDescriptor StringDescriptor;
    
    
    // USB 3.0 Table 9-13
    enum tDeviceCapabilityType
    {
        kDeviceCapabilityTypeWireless       = 1,
        kDeviceCapabilityTypeUSB20Extension = 2,
        kDeviceCapabilityTypeSuperSpeed     = 3,
        kDeviceCapabilityTypeContainerID    = 4
    };
    
    typedef enum tDeviceCapabilityType tDeviceCapabilityType;
        
    
#ifdef __cplusplus
    // USB 3.0 9.6.2: Binary Device Object Store (BOS)
    struct BOSDescriptor : public Descriptor
    {
#else
    struct BOSDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint16_t    wTotalLength;
        uint8_t     bNumDeviceCaps;
    } __attribute__((packed));
        
    typedef struct BOSDescriptor BOSDescriptor;
        
        
#ifdef __cplusplus
    // USB 3.0 9.6.2: Binary Device Object Store (BOS)
    struct DeviceCapabilityDescriptor : public Descriptor
    {
#else
    struct DeviceCapabilityDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint8_t     bDevCapabilityType;
    } __attribute__((packed));
        
    typedef struct DeviceCapabilityDescriptor DeviceCapabilityDescriptor;
        
    
#ifdef __cplusplus
    // USB 3.0 9.6.2.1: USB 2.0 Extension
    struct USB20ExtensionCapabilityDescriptor : public DeviceCapabilityDescriptor
    {
#else
    struct USB20ExtensionCapabilityDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint32_t    bmAttributes;
    } __attribute__((packed));
        
    typedef struct USB20ExtensionCapabilityDescriptor USB20ExtensionCapabilityDescriptor;
        
    
    enum
    {
        kUSB20ExtensionCapabilityLPM = StandardUSBBit(1)
    };
    
        
#ifdef __cplusplus
    // USB 3.0 9.6.2.2: SuperSpeed USB Device Capability
    struct SuperSpeedUSBDeviceCapabilityDescriptor : public DeviceCapabilityDescriptor
    {
#else
    struct SuperSpeedUSBDeviceCapabilityDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint8_t     bmAttributes;
        uint16_t    wSpeedsSupported;
        uint8_t     bFunctionalitySupport;
        uint8_t     bU1DevExitLat;
        uint16_t    bU2DevExitLat;
    } __attribute__((packed));
        
    typedef struct SuperSpeedUSBDeviceCapabilityDescriptor SuperSpeedUSBDeviceCapabilityDescriptor;
        
    
    enum
    {
        kSuperSpeedDeviceCapabilityLTM = StandardUSBBit(1),
        
        kSuperSpeedDeviceCapabilityLowSpeed  = StandardUSBBit(0),
        kSuperSpeedDeviceCapabilityFullSpeed = StandardUSBBit(1),
        kSuperSpeedDeviceCapabilityHighSpeed = StandardUSBBit(2),
        kSuperSpeedDeviceCapability5Gb       = StandardUSBBit(3),
        
        kSuperSpeedDeviceCapabilitySupportLowSpeed  = 0,
        kSuperSpeedDeviceCapabilitySupportFullSpeed = 1,
        kSuperSpeedDeviceCapabilitySupportHighSpeed = 2,
        kSuperSpeedDeviceCapabilitySupport5Gb       = 3,
        
        kSuperSpeedDeviceCapabilityU1DevExitLatMax = 0xa,
        kSuperSpeedDeviceCapabilityU2DevExitLatMax = 0x7ff
    };
    
        
#ifdef __cplusplus
    // USB 3.0 9.6.2.3: Container ID
    struct ContainerIDCapabilityDescriptor : public DeviceCapabilityDescriptor
    {
#else
    struct ContainerIDCapabilityDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint8_t  bReserved;
        uint32_t containerID[4];
    } __attribute__((packed));
        
    typedef struct ContainerIDCapabilityDescriptor ContainerIDCapabilityDescriptor;
        
    
#ifdef __cplusplus
    // USB 3.0 9.6.4: Interface Association
    struct InterfaceAssociationDescriptor: public Descriptor
    {
#else
    struct InterfaceAssociationDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint8_t     bFirstInterface;
        uint8_t     bInterfaceCount;
        uint8_t     bFunctionClass;
        uint8_t     bFunctionSubClass;
        uint8_t     bFunctionProtocol;
        uint8_t     iFunction;
    } __attribute__((packed));
        
    typedef struct InterfaceAssociationDescriptor InterfaceAssociationDescriptor;
        
    
#ifdef __cplusplus
    // USB 3.0 9.6.7: SuperSpeed Endpoint Companion
    struct SuperSpeedEndpointCompanionDescriptor : public Descriptor
    {
#else
    struct SuperSpeedEndpointCompanionDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint8_t  bMaxBurst;
        uint8_t  bmAttributes;
        uint16_t wBytesPerInterval;
    } __attribute__((packed));
        
    typedef struct SuperSpeedEndpointCompanionDescriptor SuperSpeedEndpointCompanionDescriptor;
        
    
    enum
    {
        kSuperSpeedEndpointCompanionDescriptorMaxBurst      = StandardUSBBitRange(0, 4),
        kSuperSpeedEndpointCompanionDescriptorMaxBurstPhase = StandardUSBBitRangePhase(0, 4),
        
        kSuperSpeedEndpointCompanionDescriptorBulkMaxStreams      = StandardUSBBitRange(0, 4),
        kSuperSpeedEndpointCompanionDescriptorBulkMaxStreamsPhase = StandardUSBBitRangePhase(0, 4),
        kSuperSpeedEndpointCompanionDescriptorBulkReserved        = StandardUSBBitRange(5, 7),
        kSuperSpeedEndpointCompanionDescriptorBulkReservedPhase   = StandardUSBBitRangePhase(5, 7),
        kSuperSpeedEndpointCompanionDescriptorIsocMult            = StandardUSBBitRange(0, 1),
        kSuperSpeedEndpointCompanionDescriptorIsocMultPhase       = StandardUSBBitRangePhase(0, 1),
        kSuperSpeedEndpointCompanionDescriptorIsocReserved        = StandardUSBBitRange(2, 7),
        kSuperSpeedEndpointCompanionDescriptorIsocReservedPhase   = StandardUSBBitRangePhase(2, 7)
    };
    
        
#ifdef __cplusplus
    // USB 2.0 11.23.2.1: Hub Descriptor
    struct HubDescriptor : public Descriptor
    {
#else
    struct HubDescriptor
    {
        uint8_t  bLength;
        uint8_t  bDescriptorType;
#endif
        uint8_t  bNumberPorts;
        uint16_t wHubCharacteristics;
        uint8_t  bPowerOnToPowerGood;
        uint8_t  bHubControllerCurrent;
        uint8_t  deviceRemovable[2];    // Technically variable size
        uint8_t  reserved[2];           // Unused
    } __attribute__((packed));
        
    typedef struct HubDescriptor HubDescriptor;
        
    
#ifdef __cplusplus
    // USB 3.0 10.13.2.1: SuperSpeed Hub Descriptor
    struct SuperSpeedHubDescriptor : public Descriptor
    {
#else
    struct SuperSpeedHubDescriptor
    {
        uint8_t  bLength;
        uint8_t  bDescriptorType;
#endif
        uint8_t  bNumberPorts;
        uint16_t wHubCharacteristics;
        uint8_t  bPowerOnToPowerGood;
        uint8_t  bHubControllerCurrent;
        uint8_t  bHubDecodeLatency;
        uint16_t wHubDelay;
        uint16_t deviceRemovable;
    } __attribute__((packed));
        
    typedef struct SuperSpeedHubDescriptor SuperSpeedHubDescriptor;
        
    
    enum
    {
        kSuperSpeedHubCharacteristicsPowerSwitchingMask       = StandardUSBBitRange(0, 1),
        kSuperSpeedHubCharacteristicsPowerSwitchingGanged     = (0 << StandardUSBBitRangePhase(0, 1)),
        kSuperSpeedHubCharacteristicsPowerSwitchingIndividual = (1 << StandardUSBBitRangePhase(0, 1)),
        kSuperSpeedHubCharacteristicsCompoundDevice           = StandardUSBBit(2),
        kSuperSpeedHubCharacteristicsOverCurrentMask          = StandardUSBBitRange(3, 4),
        kSuperSpeedHubCharacteristicsOverCurrentGlobal        = (0 << StandardUSBBitRangePhase(3, 4)),
        kSuperSpeedHubCharacteristicsOverCurrentIndividual    = (1 << StandardUSBBitRangePhase(3, 4)),
        kSuperSpeedHubCharacteristicsReserved                 = StandardUSBBitRange(5, 15),
        
        kSuperSpeedHubDecodeLatencyMax = 10,
        kSuperSpeedHubDelayMax         = 400
    };
    
#ifdef __cplusplus
#pragma mark Descriptor list parsing
    const Descriptor* getNextDescriptor(const ConfigurationDescriptor* configurationDescriptor, const Descriptor* currentDescriptor);
    const Descriptor* getNextDescriptorWithType(const ConfigurationDescriptor* configurationDescriptor, const Descriptor* currentDescriptor, const uint8_t type);
    const Descriptor* getNextAssociatedDescriptor(const ConfigurationDescriptor* configurationDescriptor, const Descriptor* parentDescriptor, const Descriptor* currentDescriptor);
    const Descriptor* getNextAssociatedDescriptorWithType(const ConfigurationDescriptor* configurationDescriptor, const Descriptor* parentDescriptor, const Descriptor* currentDescriptor, const uint8_t type);
    const InterfaceAssociationDescriptor* getNextInterfaceAssociationDescriptor(const ConfigurationDescriptor* configurationDescriptor, const Descriptor* currentDescriptor);
    const InterfaceDescriptor* getNextInterfaceDescriptor(const ConfigurationDescriptor* configurationDescriptor, const Descriptor* currentDescriptor);
    const EndpointDescriptor* getNextEndpointDescriptor(const ConfigurationDescriptor* configurationDescriptor, const InterfaceDescriptor* interfaceDescriptor, const Descriptor* currentDescriptor);
    
    const DeviceCapabilityDescriptor* getNextCapabilityDescriptor(const BOSDescriptor* bosDescriptor, const DeviceCapabilityDescriptor* currentDescriptor);
    const DeviceCapabilityDescriptor* getNextCapabilityDescriptorWithType(const BOSDescriptor* bosDescriptor, const DeviceCapabilityDescriptor* currentDescriptor, const uint8_t type);
    const USB20ExtensionCapabilityDescriptor* getUSB20ExtensionDeviceCapabilityDescriptor(const BOSDescriptor* bosDescriptor);
    const SuperSpeedUSBDeviceCapabilityDescriptor* getSuperSpeedDeviceCapabilityDescriptor(const BOSDescriptor* bosDescriptor);
    const ContainerIDCapabilityDescriptor* getContainerIDDescriptor(const BOSDescriptor* bosDescriptor);
    
#pragma mark Device descriptor parsing
    bool validateDeviceDescriptor(uint32_t usbDeviceSpeed, const DeviceDescriptor* descriptor);
    
#pragma mark Endpoint descriptor parsing
    uint8_t getEndpointDirection(const EndpointDescriptor* descriptor);
    uint8_t getEndpointAddress(const EndpointDescriptor* descriptor);
    uint8_t getEndpointNumber(const EndpointDescriptor* descriptor);
    uint8_t getEndpointType(const EndpointDescriptor* descriptor);
    bool validateEndpointMaxPacketSize(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor);
    uint16_t getEndpointMaxPacketSize(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor);
    bool validateEndpointBurstSize(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor, const SuperSpeedEndpointCompanionDescriptor* companionDescriptor);
    uint16_t getEndpointBurstSize(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor, const SuperSpeedEndpointCompanionDescriptor* companionDescriptor);
    bool validateEndpointInterval(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor);
    uint32_t getEndpointIntervalEncodedMicroframes(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor);
    uint32_t getEndpointIntervalMicroframes(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor);
    uint32_t getEndpointIntervalFrames(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor);
    uint32_t getEndpointMaxStreamsEncoded(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor, const SuperSpeedEndpointCompanionDescriptor* companionDescriptor);
    uint32_t getEndpointMaxStreams(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor, const SuperSpeedEndpointCompanionDescriptor* companionDescriptor);
    uint32_t getConfigurationMaxPowerMilliAmps(uint32_t usbDeviceSpeed, const ConfigurationDescriptor* descriptor);
    bool validateEndpointDescriptor(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor, const SuperSpeedEndpointCompanionDescriptor* companionDescriptor);
    
#pragma mark String descriptor parsing
    /*!
     * @brief Convert a USB string descriptor to a UTF8 character string
     *
     * @discussion This method uses utf8_encodestr with appropriate options to convert a USB string descriptor to a UTF8 string.
     *
     * @param stringDescriptor Descriptor to convert
     *
     * @param stringBuffer Buffer to write the UTF8 string to
     *
     * @param length Reference to size_t.  As input it is the size stringBuffer.  As output it is the number of character written to stringBuffer.
     *
     * @return IOReturn result code.  kIOReturnSuccess if any portion of the string could be converted and placed in stringBuffer.  kIOReturnError if the
     * string descriptor contains characters that cannot be converted to UTF8
     */
    IOReturn stringDescriptorToUTF8(const StringDescriptor* stringDescriptor, char* stringBuffer, size_t& length);
    
#pragma mark Capability descriptor parsing
    bool validateDeviceCapabilityDescriptors(const BOSDescriptor* bosDescriptor);
        
#endif // __cplusplus
    
#pragma mark Device requests
    // USB 2.0 9.3: USB Device Requests
    struct DeviceRequest
    {
        uint8_t     bmRequestType;
        uint8_t     bRequest;
        uint16_t    wValue;
        uint16_t    wIndex;
        uint16_t    wLength;
    } __attribute__((packed));
        
    typedef struct DeviceRequest DeviceRequest;
    
    enum
    {
        kDeviceRequestSize              = 8,
        kDeviceRequestDirectionMask     = StandardUSBBit(7),
        kDeviceRequestDirectionPhase    = StandardUSBBitRangePhase(7, 7),
        kDeviceRequestDirectionOut      = (0 << kDeviceRequestDirectionPhase),
        kDeviceRequestDirectionIn       = (1 << kDeviceRequestDirectionPhase),
        kDeviceRequestTypeMask          = StandardUSBBitRange(5, 6),
        kDeviceRequestTypePhase         = StandardUSBBitRangePhase(5, 6),
        kDeviceRequestTypeStandard      = (0 << kDeviceRequestTypePhase),
        kDeviceRequestTypeClass         = (1 << kDeviceRequestTypePhase),
        kDeviceRequestTypeVendor        = (2 << kDeviceRequestTypePhase),
        kDeviceRequestRecipientMask     = StandardUSBBitRange(0, 4),
        kDeviceRequestRecipientPhase    = StandardUSBBitRangePhase(0, 4),
        kDeviceRequestRecipientDevice   = (0 << kDeviceRequestRecipientPhase),
        kDeviceRequestRecipientInterface= (1 << kDeviceRequestRecipientPhase),
        kDeviceRequestRecipientEndpoint = (2 << kDeviceRequestRecipientPhase),
        kDeviceRequestRecipientOther    = (3 << kDeviceRequestRecipientPhase),
    };
    
    // USB 2.0 9.4: Standard Device Requests
    // USB 3.0 9.4: Standard Device Requests
    enum
    {
        kDeviceRequestGetStatus             = 0,
        kDeviceRequestClearFeature          = 1,
        kDeviceRequestGetState              = 2,
        kDeviceRequestSetFeature            = 3,
        kDeviceRequestSetAddress            = 5,
        kDeviceRequestGetDescriptor         = 6,
        kDeviceRequestSetDescriptor         = 7,
        kDeviceRequestGetConfiguration      = 8,
        kDeviceRequestSetConfiguration      = 9,
        kDeviceRequestGetInterface          = 10,
        kDeviceRequestSetInterface          = 11,
        kDeviceRequestSynchFrame            = 12,
        kDeviceRequestSetSel                = 48,
        kDeviceRequestSetIsochronousDelay   = 49
    };
    
    // USB 2.0 9.4.5: Get Status
    // USB 3.0 9.4.5: Get Status
    enum
    {
        kDeviceStatusSelfPowered            = StandardUSBBit(0),
        kDeviceStatusRemoteWakeEnable       = StandardUSBBit(1),
        kDeviceStatusU1Enable               = StandardUSBBit(2),
        kDeviceStatusU2Enable               = StandardUSBBit(3),
        kDeviceStatusLTMEnable              = StandardUSBBit(4),
        
        kInterfaceStatusRemoteWakeCapable   = StandardUSBBit(0),
        kInterfaceStatusRemoteWakeEnable    = StandardUSBBit(1),
        
        kEndpointStatusHalt                 = StandardUSBBit(0)
    };
    
    // USB 2.0 Table 9-6: Standard Feature Selectors
    // USB 3.0 Table 9-7: Standard Feature Selectors
    enum
    {
        kDeviceFeatureSelectorRemoteWakeup  = 1,
        kDeviceFeatureSelectorTestMode      = 2,
        kDeviceFeatureSelectorU1Enable      = 48,
        kDeviceFeatureSelectorU2Enable      = 49,
        kDeviceFeatureSelectorLTMEnable     = 50,
        
        kInterfaceFeatureSelectorSuspend    = 0,
        
        kEndpointFeatureSelectorStall       = 0,
    };
    
    // USB 3.0 Table 9-8: Suspend Options
    enum
    {
        kInterfaceSuspendLowPower           = StandardUSBBit(0),
        kInterfaceSuspendRemoteWakeEnable   = StandardUSBBit(1)
    };
        
#ifdef __cplusplus
}


namespace StandardUSB20
{
    enum tBusCurrent
    {
        kBusCurrentMinimum = 100,
        kBusCurrentDefault = 500
    };
}

namespace StandardUSB30
{
    enum tBusCurrent
    {
        kBusCurrentMinimum = 150,
        kBusCurrentDefault = 900
    };

    // USB 3.0 Table 6-21
    enum tResetTimeout
    {
        kResetMinimumTimeout                    = 80,
        kResetTypicalTimeout                    = 100,
        kResetMaximumTimeout                    = 120,
        kResetMaximumWithMarginTimeout          = 150
    };

    // USB 3.0 Table 7-12
    enum tLinkStateTimeout
    {
        kLinkStateSSInactiveQuietTimeout        = 12,
        kLinkStateRxDetectQuietTimeout          = 12,
        kLinkStatePollingLFPSTimeout            = 360,
        kLinkStatePollingActiveTimeout          = 12,
        kLinkStatePollingConfigurationTimeout   = 12,
        kLinkStatePollingIdleTimeout            = 2,
        kLinkStateU0RecoveryTimeout             = 1,
        kLinkStateU0LTimeout                    = 0,        // 10 microseconds
        kLinkStateU1NoLFPSResponseTimeout       = 2,
        kLinkStateU1PingTimeout                 = 300,
        kLinkStateU2NoLFPSResponseTimeout       = 2,
        kLinKStateU2RxDetectDelay               = 100,
        kLinkStateU3NoLFPSResponseTimeout       = 10,
        kLinkStateU3WakeupRetryDelay            = 100,
        kLinkStateU3RxDetectDelay               = 100,
        kLinkStateRecoveryActiveTimeout         = 12,
        kLinkStateRecoveryConfigurationTimeout  = 6,
        kLinkStateRecoveryIdleTimeout           = 2,
        kLinkStateLoopbackExitTimeout           = 2,
        kLinkStateHotResetActiveTimeout         = 12,
        kLinkStateHotResetExistTimeout          = 2,

        // USB 3.0 7.5.4
        kLinkStatePollingDeadline               = (kLinkStatePollingLFPSTimeout + 1 + kLinkStatePollingActiveTimeout + kLinkStatePollingConfigurationTimeout + kLinkStatePollingIdleTimeout),

        // USB 3.0 7.5.9 and 7.5.10
        kLinkStateSSResumeDeadline              = (kLinkStateU3NoLFPSResponseTimeout + kLinkStateRecoveryActiveTimeout + kLinkStateRecoveryConfigurationTimeout + kLinkStateRecoveryIdleTimeout),
    };
}
#endif // __cplusplus

#endif

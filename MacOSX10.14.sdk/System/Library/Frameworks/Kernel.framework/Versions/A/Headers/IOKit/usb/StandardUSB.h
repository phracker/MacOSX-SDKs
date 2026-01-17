/*
 * Copyright (c) 1998-2016 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

/*! @header     StandardUSB.h
    @brief      StandardUSB defines structures and constants to reflect the USB specification
 */

#ifndef IOUSBHostFamily_StandardUSB_h
#define IOUSBHostFamily_StandardUSB_h

#include <IOKit/IOTypes.h>
#include <IOKit/IOReturn.h>
#include <libkern/OSByteOrder.h>

#pragma mark Platform endianness and bitmask macros

#define USBToHost16 OSSwapLittleToHostInt16
#define HostToUSB16 OSSwapHostToLittleInt16

#define USBToHost32 OSSwapLittleToHostInt32
#define HostToUSB32 OSSwapHostToLittleInt32

#define USBToHost64 OSSwapLittleToHostInt64
#define HostToUSB64 OSSwapHostToLittleInt64

#define StandardUSBBit(bit)                     ((uint32_t)(1) << bit)
#define StandardUSBBitRange(start, end)         (~(((uint32_t)(1) << start) - 1) & (((uint32_t)(1) << end) | (((uint32_t)(1) << end) - 1)))
#define StandardUSBBitRange64(start, end)       (~(((uint64_t)(1) << start) - 1) & (((uint64_t)(1) << end) | (((uint64_t)(1) << end) - 1)))
#define StandardUSBBitRangePhase(start, end)    (start)

#define kUSB30Bitrate5Gbps  ( 5 * 1000 * 1000 * 1000ULL)
#define kUSB30Bitrate10Gbps (10 * 1000 * 1000 * 1000ULL)

#ifdef __cplusplus

#pragma mark StandardUSB namespace
namespace StandardUSB
{
    
#endif // __cplusplus
    
#pragma mark Descriptor definitions
    /*!
     * @enum        tDescriptorType
     * @namespace   StandardUSB
     * @brief       Descriptor types defined by USB 2.0 Table 9-5 and USB 3.0 Table 9-6
     */
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
        kDescriptorTypeSuperSpeedUSBEndpointCompanion = 48,
        kDescriptorTypeSuperSpeedPlusIsochronousEndpointCompanion = 49
    };
    
    typedef enum tDescriptorType tDescriptorType;

    /*!
     * @enum        tDescriptorSize
     * @namespace   StandardUSB
     * @brief       Size in bytes for descriptor structures
     */
    enum tDescriptorSize
    {
        kDescriptorSize = 2,
        kDescriptorSizeDevice = 18,
        kDescriptorSizeConfiguration = 9,
        kDescriptorSizeInterface = 9,
        kDescriptorSizeEndpoint = 7,
        kDescriptorSizeStringMinimum = kDescriptorSize,
        kDescriptorSizeStringMaximum = 255,
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
        kDescriptorSizeSuperSpeedPlusIsochronousEndpointCompanion = 8,
        kDescriptorSizeBillboardDeviceMinimum = 44,
        kDescriptorSizeBillboardDeviceMaximum = 256,
        kDescriptorSizePlatformECIDCapability = 28
    };
    
    typedef enum tDescriptorSize tDescriptorSize;

    /*!
     * @struct      Descriptor
     * @namespace   StandardUSB
     * @brief       Base descriptor defined by USB 2.0 9.5
     * @discussion  StandardUSB.h declares structs to represent a variety of USB standard descriptors.  Each of thes structs is derived from the Descriptor base struct, and can therefore be passed to methods accepting a Descriptor pointer without explicit casting.  For the C language, each struct is defined independently to include the bLength and bDescriptorType fields expected for all USB descriptors.
     */
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
    
    
    enum tDeviceCapabilityType
    {
        // USB 3.0 Table 9-13
        kDeviceCapabilityTypeWireless               = 1,
        kDeviceCapabilityTypeUSB20Extension         = 2,
        kDeviceCapabilityTypeSuperSpeed             = 3,
        kDeviceCapabilityTypeContainerID            = 4,
        
        // USB 3.1 Table 9-14
        kDeviceCapabilityTypePlatform               = 5,
        kDeviceCapabilityTypePowerDelivery          = 6,
        kDeviceCapabilityTypeBatteryInfo            = 7,
        kDeviceCapabilityTypePdConsumerPort         = 8,
        kDeviceCapabilityTypePdProviderPort         = 9,
        kDeviceCapabilityTypeSuperSpeedPlus         = 10,
        kDeviceCapabilityTypePrecisionMeasurement   = 11,
        kDeviceCapabilityTypeWirelessExt            = 12,
        kDeviceCapabilityTypeBillboard              = 13,
        kDeviceCapabilityTypeBillboardAltMode       = 15
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
        uint8_t     bDevCapabilityType;
#endif
        uint32_t    bmAttributes;
    } __attribute__((packed));
        
    typedef struct USB20ExtensionCapabilityDescriptor USB20ExtensionCapabilityDescriptor;
        
    
    enum
    {
        kUSB20ExtensionCapabilityLPM = StandardUSBBit(1),
        
        // From USB 2.0 ECN Errata for Link Power Management.
        kUSB20ExtensionCapabilityBESLSupport    = StandardUSBBit(2),
        kUSB20ExtensionCapabilityBESLValid      = StandardUSBBit(3),
        kUSB20ExtensionCapabilityBESLDValid     = StandardUSBBit(4),
        kUSB20ExtensionCapabilityBESL           = StandardUSBBitRange( 8, 11),
        kUSB20ExtensionCapabilityBESLPhase      = StandardUSBBitRangePhase( 8, 11),
        kUSB20ExtensionCapabilityBESLD          = StandardUSBBitRange(12, 15),
        kUSB20ExtensionCapabilityBESLDPhase     = StandardUSBBitRangePhase(12, 15)
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
        uint8_t     bDevCapabilityType;
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
    // USB 3.1 9.6.2.5: SuperSpeedPlus USB Device Capability
    struct SuperSpeedPlusUSBDeviceCapabilityDescriptor : public DeviceCapabilityDescriptor
    {
#else
    struct SuperSpeedPlusUSBDeviceCapabilityDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
        uint8_t     bDevCapabilityType;
#endif
        uint8_t     bReserved;
        uint32_t    bmAttributes;
        uint16_t    wFunctionalitySupport;
        uint16_t    wReserved;
        uint32_t    bmSublinkSpeedAttr[1];
        
    } __attribute__((packed));

    typedef struct SuperSpeedPlusUSBDeviceCapabilityDescriptor SuperSpeedPlusUSBDeviceCapabilityDescriptor;
    
    enum
    {
        //bmAttributes
        kSuperSpeedPlusDeviceCapabilitySublinkSpeedAttrCount = StandardUSBBitRange(0, 4),
        kSuperSpeedPlusDeviceCapabilitySublinkSpeedAttrCountPhase = StandardUSBBitRangePhase(0, 4),
        
        kSuperSpeedPlusDeviceCapabilitySublinkSpeedIdCount = StandardUSBBitRange(5, 8),
        kSuperSpeedPlusDeviceCapabilitySublinkSpeedIdCountPhase = StandardUSBBitRangePhase(5, 8),
        
        //wFunctionalitySupport
        kSuperSpeedPlusDeviceCapabilitySublinkMinSpeedId = StandardUSBBitRange(0, 3),
        kSuperSpeedPlusDeviceCapabilitySublinkMinSpeedIdPhase = StandardUSBBitRangePhase(0, 3),
        
        kSuperSpeedPlusDeviceCapabilityReserved = StandardUSBBitRange(4, 7),
        kSuperSpeedPlusDeviceCapabilityReservedPhase = StandardUSBBitRangePhase(4, 7),
        
        kSuperSpeedPlusDeviceCapabilityMinRxLaneCount = StandardUSBBitRange(8, 11),
        kSuperSpeedPlusDeviceCapabilityMinRxLaneCountPhase = StandardUSBBitRangePhase(8, 11),
        
        kSuperSpeedPlusDeviceCapabilityMinTxLaneCount = StandardUSBBitRange(12, 15),
        kSuperSpeedPlusDeviceCapabilityMinTxLaneCountPhase = StandardUSBBitRangePhase(12, 15),
        
        //bmSublinkSpeedAttr
        kSuperSpeedPlusDeviceCapabilitySublinkSpeedId = StandardUSBBitRange(0, 3),
        kSuperSpeedPlusDeviceCapabilitySublinkSpeedIdPhase = StandardUSBBitRangePhase(0, 3),
        
        kSuperSpeedPlusDeviceCapabilitySublinkLSE      = StandardUSBBitRange(4, 5),
        kSuperSpeedPlusDeviceCapabilitySublinkLSEPhase = StandardUSBBitRangePhase(4, 5),
        kSuperSpeedPlusDeviceCapabilitySublinkLSEBits  = (0 << kSuperSpeedPlusDeviceCapabilitySublinkLSEPhase),
        kSuperSpeedPlusDeviceCapabilitySublinkLSEKbits = (1 << kSuperSpeedPlusDeviceCapabilitySublinkLSEPhase),
        kSuperSpeedPlusDeviceCapabilitySublinkLSEMbits = (2 << kSuperSpeedPlusDeviceCapabilitySublinkLSEPhase),
        kSuperSpeedPlusDeviceCapabilitySublinkLSEGbits = (3 << kSuperSpeedPlusDeviceCapabilitySublinkLSEPhase),
        
        kSuperSpeedPlusDeviceCapabilitySublinkType = StandardUSBBitRange(6, 7),
        kSuperSpeedPlusDeviceCapabilitySublinkTypePhase = StandardUSBBitRangePhase(6, 7),
        
        kSuperSpeedPlusDeviceCapabilitySublinkSymmetry = StandardUSBBit(6),
        kSuperSpeedPlusDeviceCapabilitySublinkSymmetryPhase = StandardUSBBitRangePhase(6, 6),
        kSuperSpeedPlusDeviceCapabilitySublinkSymmetric  = (0 << kSuperSpeedPlusDeviceCapabilitySublinkSymmetryPhase),
        kSuperSpeedPlusDeviceCapabilitySublinkAsymmetric = (1 << kSuperSpeedPlusDeviceCapabilitySublinkSymmetryPhase),
        
        kSuperSpeedPlusDeviceCapabilitySublinkDirection = StandardUSBBit(7),
        kSuperSpeedPlusDeviceCapabilitySublinkDirectionPhase = StandardUSBBitRangePhase(7, 7),
        kSuperSpeedPlusDeviceCapabilitySublinkDirectionRx = (0 << kSuperSpeedPlusDeviceCapabilitySublinkDirectionPhase),
        kSuperSpeedPlusDeviceCapabilitySublinkDirectionTx = (1 << kSuperSpeedPlusDeviceCapabilitySublinkDirectionPhase),
        
        kSuperSpeedPlusDeviceCapabilitySublinkReserved = StandardUSBBitRange(8, 13),
        kSuperSpeedPlusDeviceCapabilitySublinkReservedPhase = StandardUSBBitRangePhase(8, 13),
        
        kSuperSpeedPlusDeviceCapabilitySublinkProtocol = StandardUSBBitRange(14, 15),
        kSuperSpeedPlusDeviceCapabilitySublinkProtocolPhase = StandardUSBBitRangePhase(14, 15),
        
        kSuperSpeedPlusDeviceCapabilitySublinkSpeedMantissa = StandardUSBBitRange(16, 31),
        kSuperSpeedPlusDeviceCapabilitySublinkSpeedMantissaPhase = StandardUSBBitRangePhase(16, 31),
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
        uint8_t     bDevCapabilityType;
#endif
        uint8_t  bReserved;
        uint32_t containerID[4];
    } __attribute__((packed));
        
    typedef struct ContainerIDCapabilityDescriptor ContainerIDCapabilityDescriptor;

#ifdef __cplusplus
    // USB 3.1 9.6.2.4: Platform Descriptor
    struct PlatformCapabilityDescriptor : public DeviceCapabilityDescriptor
    {
#else
    struct PlatformCapabilityDescriptor
    {
        uint8_t   bLength;
        uint8_t   bDescriptorType;
        uint8_t   bDevCapabilityType;
#endif
        uint8_t   bReserved;
        uuid_t    PlatformCapabilityUUID;
    }__attribute__((packed));

    typedef struct PlatformCapabilityDescriptor PlatformCapabilityDescriptor;

    // USB Billboard 3.1.6.2: Billboard Capability Descriptor V1.2
    struct BillboardAltModeCapabilityCompatibility
    {
        uint16_t  wSVID;
        uint32_t  dwAlternateMode;
        uint8_t   iAlternateModeString;
    }__attribute__((packed));

    typedef struct BillboardAltModeCapabilityCompatibility BillboardAltModeCapabilityCompatibility;

    // USB Billboard 3.1.6.2: Billboard Capability Descriptor V1.1 and 1.21+
    struct BillboardAltModeCapability
    {
        uint16_t  wSVID;
        uint8_t   bAlternateMode;
        uint8_t   iAlternateModeString;
    }__attribute__((packed));

    typedef struct BillboardAltModeCapability BillboardAltModeCapability;

#ifdef __cplusplus
    // USB Billboard 3.1.6.2: Billboard Capability Descriptor
    struct BillboardCapabilityDescriptor : public DeviceCapabilityDescriptor
    {
#else
    struct BillboardCapabilityDescriptor
    {
        uint8_t  bLength;
        uint8_t  bDescriptorType;
        uint8_t  bDevCapabilityType;
#endif
        uint8_t  iAddtionalInfoURL;
        uint8_t  bNumberOfAlternateModes;
        uint8_t  bPreferredAlternateMode;
        uint16_t VCONNPower;
        uint8_t  bmConfigured[32];
        uint16_t bcdVersion;
        uint8_t  bAdditonalFailureInfo;
        uint8_t  bReserved;
        uint8_t  altModeCapabilities[];
    }__attribute__((packed));

    typedef struct BillboardCapabilityDescriptor BillboardCapabilityDescriptor;

#ifdef __cplusplus
    // USB Billboard 3.1.6.3: Billboard Capability Descriptor V1.21
    struct BillboardAltModeCapabilityDescriptor : public DeviceCapabilityDescriptor
    {
#else
    struct BillboardAltModeCapabilityDescriptor
    {
        uint8_t   bLength;
        uint8_t   bDescriptorType;
        uint8_t   bDevCapabilityType;
#endif
        uint8_t   bIndex;
        uint16_t  dwAlternateModeVdo;
    }__attribute__((packed));

    typedef struct BillboardAltModeCapabilityDescriptor BillboardAltModeCapabilityDescriptor;

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
    // USB 3.1 9.6.7: SuperSpeed Endpoint Companion
    struct SuperSpeedEndpointCompanionDescriptor : public Descriptor
    {
#else
    struct SuperSpeedEndpointCompanionDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint8_t     bMaxBurst;
        uint8_t     bmAttributes;
        uint16_t    wBytesPerInterval;
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
        kSuperSpeedEndpointCompanionDescriptorIsocReserved        = StandardUSBBitRange(2, 6),
        kSuperSpeedEndpointCompanionDescriptorIsocReservedPhase   = StandardUSBBitRangePhase(2, 6),
        kSuperSpeedEndpointCompanionDescriptorSSPIsocCompanion    = StandardUSBBit(7)
    };


#ifdef __cplusplus
    // USB 3.1 9.6.8: SuperSpeedPlus Isochronous Endpoint Companion
    struct SuperSpeedPlusIsochronousEndpointCompanionDescriptor : public Descriptor
    {
#else
    struct SuperSpeedPlusIsochronousEndpointCompanionDescriptor
    {
        uint8_t     bLength;
        uint8_t     bDescriptorType;
#endif
        uint16_t    wReserved;
        uint32_t    dwBytesPerInterval;
    } __attribute__((packed));

    typedef struct SuperSpeedPlusIsochronousEndpointCompanionDescriptor SuperSpeedPlusIsochronousEndpointCompanionDescriptor;

        
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
    /*!
     * @brief       Get the next descriptor in a configuration descriptor
     * @discussion  This method will advance currentDescriptor by its bLength, and validate that the new descriptor fits withing the bounds of configurationDescriptor.  Using NULL for currentDescriptor will return the first descriptor after the configuration descriptor.
     * @param       configurationDescriptor Configuration descriptor that contains the descriptors to iterate through
     * @param       currentDescriptor A descriptor pointer within the bounds of configurationDescriptor, or NULL
     * @return      Descriptor pointer, or NULL if no descriptor can be returned
     */
    const Descriptor* getNextDescriptor(const ConfigurationDescriptor* configurationDescriptor, const Descriptor* currentDescriptor);

    /*!
     * @brief       Find the next descriptor matching a given type within a configuration descriptor
     * @discussion  This method uses getNextDescriptor, and further validates that the returned descriptor's bDescriptorType field matches the type parameter.
     * @param       configurationDescriptor Configuration descriptor that contains the descriptors to iterate through
     * @param       currentDescriptor A descriptor pointer within the bounds of configurationDescriptor, or NULL
     * @param       type tDescriptorType representing the descriptor type to find
     * @return      Descriptor pointer, or NULL if no matching descriptor can be found
     */
    const Descriptor* getNextDescriptorWithType(const ConfigurationDescriptor* configurationDescriptor, const Descriptor* currentDescriptor, const uint8_t type);

    /*!
     * @brief       Get the next descriptor in a configuration descriptor that belongs to another container descriptor
     * @discussion  This method uses getNextDescriptor, but will return NULL if another descriptor is found whose bDescriptorType field matches the value used for parentDescriptor's bDescriptorType.  Using NULL for currentDescriptor will return the first descriptor after parentDescriptor.
     * @param       configurationDescriptor Configuration descriptor that contains the descriptors to iterate through
     * @param       parentDescriptor A descriptor pointer within the bounds of configurationDescriptor
     * @param       currentDescriptor A descriptor pointer within the bounds of configurationDescriptor, or NULL
     * @return      Descriptor pointer, or NULL if no descriptor can be returned
     */
    const Descriptor* getNextAssociatedDescriptor(const ConfigurationDescriptor* configurationDescriptor, const Descriptor* parentDescriptor, const Descriptor* currentDescriptor);

    /*!
     * @brief       Find the next descriptor matching a given type within a configuration descriptor that belongs to another container descriptor
     * @discussion  This method uses getNextAssociatedDescriptor, and further validates that the returned descriptor's bDescriptorType field matches the type passed parameter.
     * @param       configurationDescriptor Configuration descriptor that contains the descriptors to iterate through
     * @param       parentDescriptor A descriptor pointer within the bounds of configurationDescriptor
     * @param       currentDescriptor A descriptor pointer within the bounds of configurationDescriptor, or NULL
     * @param       type tDescriptorType representing the descriptor type to find
     * @return      Descriptor pointer, or NULL if no matching descriptor can be found
     */
    const Descriptor* getNextAssociatedDescriptorWithType(const ConfigurationDescriptor* configurationDescriptor, const Descriptor* parentDescriptor, const Descriptor* currentDescriptor, const uint8_t type);

    /*!
     * @brief       Find the next interface association descriptor in a configuration descriptor
     * @discussion  This method uses getNextDescriptorWithType to fetch the next interface association descriptor
     * @param       configurationDescriptor Configuration descriptor that contains the descriptors to iterate through
     * @param       currentDescriptor A descriptor pointer within the bounds of configurationDescriptor, or NULL
     * @return      InterfaceAssociationDescriptor pointer, or NULL if no matching descriptor can be found
     */
    const InterfaceAssociationDescriptor* getNextInterfaceAssociationDescriptor(const ConfigurationDescriptor* configurationDescriptor, const Descriptor* currentDescriptor);
    
    /*!
     * @brief       Find the next interface descriptor in a configuration descriptor
     * @discussion  This method uses getNextDescriptorWithType to fetch the next interface descriptor
     * @param       configurationDescriptor Configuration descriptor that contains the descriptors to iterate through
     * @param       currentDescriptor A descriptor pointer within the bounds of configurationDescriptor, or NULL
     * @return      InterfaceDescriptor pointer, or NULL if no matching descriptor can be found
     */
    const InterfaceDescriptor* getNextInterfaceDescriptor(const ConfigurationDescriptor* configurationDescriptor, const Descriptor* currentDescriptor);
        
    /*!
     * @brief       Find the next endpoint descriptor associated with an interface descriptor
     * @discussion  This method uses getNextAssociatedDescriptorWithType to fetch the next endpoint descriptor associated with a specific interface descriptor
     * @param       configurationDescriptor Configuration descriptor that contains the descriptors to iterate through
     * @param       interfaceDescriptor An interface descriptor within the bounds of configurationDescriptor
     * @param       currentDescriptor A descriptor pointer within the bounds of configurationDescriptor, or NULL
     * @return      EndpointDescriptor pointer, or NULL if no matching descriptor can be found
     */
    const EndpointDescriptor* getNextEndpointDescriptor(const ConfigurationDescriptor* configurationDescriptor, const InterfaceDescriptor* interfaceDescriptor, const Descriptor* currentDescriptor);
    
    /*!
     * @brief       Get the next device capability descriptor in a BOS descriptor
     * @discussion  This method will advance currentDescriptor by its bLength, and validate that the new descriptor fits withing the bounds of bosDescriptor.  Using NULL for currentDescriptor will return the first descriptor after the BOS descriptor.
     * @param       bosDescriptor BOS descriptor that contains the descriptors to iterate through
     * @param       currentDescriptor A descriptor pointer within the bounds of bosDescriptor, or NULL
     * @return      DeviceCapabilityDescriptor pointer, or NULL if no descriptor can be returned
     */
    const DeviceCapabilityDescriptor* getNextCapabilityDescriptor(const BOSDescriptor* bosDescriptor, const DeviceCapabilityDescriptor* currentDescriptor);
    
    /*!
     * @brief       Find the next descriptor matching a given type within a BOS descriptor
     * @discussion  This method uses getNextCapabilityDescriptor, and further validates that the returned descriptor's bDevCapabilityType field matches the type parameter.
     * @param       bosDescriptor BOS descriptor that contains the descriptors to iterate through
     * @param       currentDescriptor A descriptor pointer within the bounds of bosDescriptor, or NULL
     * @param       type tDeviceCapabilityType representing the descriptor type to find
     * @return      DeviceCapabilityDescriptor pointer, or NULL if no matching descriptor can be found
     */
    const DeviceCapabilityDescriptor* getNextCapabilityDescriptorWithType(const BOSDescriptor* bosDescriptor, const DeviceCapabilityDescriptor* currentDescriptor, const uint8_t type);
        
    /*!
     * @brief       Find the first USB20ExtensionCapabilityDescriptor in a BOS descriptor
     * @discussion  This method uses getNextCapabilityDescriptorWithType to fetch the first USB20ExtensionCapabilityDescriptor
     * @param       bosDescriptor BOS descriptor that contains the descriptors to iterate through
     * @return      USB20ExtensionCapabilityDescriptor pointer, or NULL if no matching descriptor can be found
     */
    const USB20ExtensionCapabilityDescriptor* getUSB20ExtensionDeviceCapabilityDescriptor(const BOSDescriptor* bosDescriptor);

    /*!
     * @brief       Find the first SuperSpeedUSBDeviceCapabilityDescriptor in a BOS descriptor
     * @discussion  This method uses getNextCapabilityDescriptorWithType to fetch the first SuperSpeedUSBDeviceCapabilityDescriptor
     * @param       bosDescriptor BOS descriptor that contains the descriptors to iterate through
     * @return      SuperSpeedUSBDeviceCapabilityDescriptor pointer, or NULL if no matching descriptor can be found
     */
    const SuperSpeedUSBDeviceCapabilityDescriptor* getSuperSpeedDeviceCapabilityDescriptor(const BOSDescriptor* bosDescriptor);

    /*!
     * @brief       Find the first SuperSpeedPlusUSBDeviceCapabilityDescriptor in a BOS descriptor
     * @discussion  This method uses getNextCapabilityDescriptorWithType to fetch the first SuperSpeedPlusUSBDeviceCapabilityDescriptor
     * @param       bosDescriptor BOS descriptor that contains the descriptors to iterate through
     * @return      SuperSpeedPlusUSBDeviceCapabilityDescriptor pointer, or NULL if no matching descriptor can be found
     */
    const SuperSpeedPlusUSBDeviceCapabilityDescriptor* getSuperSpeedPlusDeviceCapabilityDescriptor(const BOSDescriptor* bosDescriptor);

    /*!
     * @brief       Find the first ContainerIDCapabilityDescriptor in a BOS descriptor
     * @discussion  This method uses getNextCapabilityDescriptorWithType to fetch the first ContainerIDCapabilityDescriptor
     * @param       bosDescriptor BOS descriptor that contains the descriptors to iterate through
     * @return      ContainerIDCapabilityDescriptor pointer, or NULL if no matching descriptor can be found
     */
    const ContainerIDCapabilityDescriptor* getContainerIDDescriptor(const BOSDescriptor* bosDescriptor);

    /*!
     * @brief       Find the first PlatformCapabilityDescriptor in a BOS descriptor
     * @discussion  This method uses getNextCapabilityDescriptorWithType to fetch the first PlatformCapabilityDescriptor
     * @param       bosDescriptor BOS descriptor that contains the descriptors to iterate through
     * @return      PlatformCapabilityDescriptor pointer, or NULL if no matching descriptor can be found
     */
    const PlatformCapabilityDescriptor* getPlatformCapabilityDescriptor(const BOSDescriptor* bosDescriptor);
        
    /*!
     * @brief       Find the first BillboardCapabilityDescriptor in a BOS descriptor
     * @discussion  This method uses getNextCapabilityDescriptorWithType to fetch the first BillboardCapabilityDescriptor
     * @param       bosDescriptor BOS descriptor that contains the descriptors to iterate through
     * @return      BillboardCapabilityDescriptor pointer, or NULL if no matching descriptor can be found
     */
    const BillboardCapabilityDescriptor* getBillboardDescriptor(const BOSDescriptor* bosDescriptor);


#pragma mark Device descriptor parsing
    /*!
     * @brief       Validate the contents of a device descriptor
     * @discussion  This method parses a device descriptor and validates its contents.  If repairable validation errors are encountered, the descriptor passed in may be modified.
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The descriptor to validate
     * @return      bool true if the descriptor passed validation, false if it did not
     */
    bool validateDeviceDescriptor(uint32_t usbDeviceSpeed, const DeviceDescriptor* descriptor);
    
#pragma mark Endpoint descriptor parsing
    /*!
     * @brief       Extract the direction of an endpoint from an endpoint descriptor
     * @discussion  This method parses an endpoint descriptor to determine its transfer direction
     * @param       descriptor The descriptor to parse
     * @return      tEndpointDirection indicating the direction found.  Control endpoints return tEndpointDirection.
     */
    uint8_t getEndpointDirection(const EndpointDescriptor* descriptor);
        
    /*!
     * @brief       Extract the direction and number of an endpoint from an endpoint descriptor
     * @discussion  This method parses an endpoint descriptor to determine its address
     * @param       descriptor The descriptor to parse
     * @return      uint8_t representing direction and endpoint number
     */
    uint8_t getEndpointAddress(const EndpointDescriptor* descriptor);
    
    /*!
     * @brief       Extract the number of an endpoint from an endpoint descriptor
     * @discussion  This method parses an endpoint descriptor to determine its number, excluding direction
     * @param       descriptor The descriptor to parse
     * @return      uint8_t representing endpoint number
     */
    uint8_t getEndpointNumber(const EndpointDescriptor* descriptor);
        
    /*!
     * @brief       Extract the type of an endpoint from an endpoint descriptor
     * @discussion  This method parses an endpoint descriptor to determine its type
     * @param       descriptor The descriptor to parse
     * @return      tEndpointType indicating the type found.
     */
    uint8_t getEndpointType(const EndpointDescriptor* descriptor);
        
    /*!
     * @brief       Validate the max packet size of an endpoint descriptor
     * @discussion  This method parses an endpoint descriptor and validates the max packet size.  If repairable validation errors are encountered, the descriptor passed in may be modified.
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The descriptor to validate
     * @return      bool true if the descriptor passed validation, false if it did not
     */
    bool validateEndpointMaxPacketSize(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor);
        
    /*!
     * @brief       Extract the max packet size from an endpoint descriptor
     * @discussion  This method parses an endpoint descriptor to determine its max packet size, which does not take into account mult or burst factors.
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The descriptor to parse
     * @return      uint16_t The max packet size in bytes
     */
    uint16_t getEndpointMaxPacketSize(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor);
        
    /*!
     * @brief       Validate the burst size of endpoint descriptors
     * @discussion  This method parses endpoint descriptors and validates the burst size.  If repairable validation errors are encountered, the descriptors passed in may be modified.
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to validate
     * @param       companionDescriptor The SuperSpeedEndpointCompanionDescriptor to validate, or NULL
     * @return      bool true if the descriptor passed validation, false if it did not
     */
    bool validateEndpointBurstSize(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor, const SuperSpeedEndpointCompanionDescriptor* companionDescriptor);
        
    /*!
     * @brief       Validate the burst size of endpoint descriptors
     * @discussion  This method parses endpoint descriptors and validates the burst size.  If repairable validation errors are encountered, the descriptors passed in may be modified.
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to validate
     * @param       companionDescriptor The SuperSpeedEndpointCompanionDescriptor to validate, or NULL
     * @param       sspCompanionDescriptor The SuperSpeedPlusIsochronousEndpointCompanionDescriptor to validate, or NULL
     * @return      bool true if the descriptor passed validation, false if it did not
     */
    bool validateEndpointBurstSize(uint32_t usbDeviceSpeed,
                                   const EndpointDescriptor* descriptor,
                                   const SuperSpeedEndpointCompanionDescriptor* companionDescriptor,
                                   const SuperSpeedPlusIsochronousEndpointCompanionDescriptor* sspCompanionDescriptor);
    
    /*!
     * @brief       Extract the burst size from endpoint descriptors
     * @discussion  This method parses endpoint descriptors to determine burst size, which includes mult and burst factors as applicable.
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to parse
     * @param       companionDescriptor The SuperSpeedEndpointCompanionDescriptor to parse, or NULL
     * @return      uint16_t The burst size in bytes
     */
    uint16_t getEndpointBurstSize(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor, const SuperSpeedEndpointCompanionDescriptor* companionDescriptor);
        
    /*!
     * @brief       Extract the burst size from endpoint descriptors
     * @discussion  This method parses endpoint descriptors to determine burst size, which includes mult and burst factors as applicable.  SuperSpeed Plus isochronous endpoints will return the dwBytesPerInterval field from the SuperSpeedPlusIsochronousEndpointCompanionDescriptor parameter.
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to parse
     * @param       companionDescriptor The SuperSpeedEndpointCompanionDescriptor to parse, or NULL
     * @param       sspCompanionDescriptor The SuperSpeedPlusIsochronousEndpointCompanionDescriptor to parse, or NULL
     * @return      uint32_t The burst size in bytes
     */
    uint32_t getEndpointBurstSize32(uint32_t usbDeviceSpeed,
                                    const EndpointDescriptor* descriptor,
                                    const SuperSpeedEndpointCompanionDescriptor* companionDescriptor = NULL,
                                    const SuperSpeedPlusIsochronousEndpointCompanionDescriptor* sspCompanionDescriptor = NULL);
        
    /*!
     * @brief       Extract the mult count from endpoint descriptors
     * @discussion  This method parses endpoint descriptors to determine mult
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to parse
     * @param       companionDescriptor The SuperSpeedEndpointCompanionDescriptor to parse, or NULL
     * @param       sspCompanionDescriptor The SuperSpeedPlusIsochronousEndpointCompanionDescriptor to parse, or NULL
     * @return      uint8_t The mult count
     */
    uint8_t getEndpointMult(uint32_t usbDeviceSpeed,
                            const EndpointDescriptor* descriptor,
                            const SuperSpeedEndpointCompanionDescriptor* companionDescriptor = NULL,
                            const SuperSpeedPlusIsochronousEndpointCompanionDescriptor* sspCompanionDescriptor = NULL);
        
    /*!
     * @brief       Validate the interval of an endpoint descriptor
     * @discussion  This method parses an endpoint descriptor and validates the interval.  If repairable validation errors are encountered, the descriptor passed in may be modified.
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to validate
     * @return      bool true if the descriptor passed validation, false if it did not
     */
    bool validateEndpointInterval(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor);
        
    /*!
     * @brief       Extract the interval of an endpoint descriptor
     * @discussion  This method parses an endpoint descriptor and returns the service interval as n in (2^(n-1)) microframes
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to parse
     * @return      uint32_t Encoded endpoint interval
     */
    uint32_t getEndpointIntervalEncodedMicroframes(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor);

    /*!
     * @brief       Extract the interval of an endpoint descriptor
     * @discussion  This method parses an endpoint descriptor and returns the service interval in microframes
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to parse
     * @return      uint32_t Endpoint interval in microframes
     */
    uint32_t getEndpointIntervalMicroframes(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor);
        
    /*!
     * @brief       Extract the interval of an endpoint descriptor
     * @discussion  This method parses an endpoint descriptor and returns the service interval in frames
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to parse
     * @return      uint32_t Endpoint interval in frames
     */
    uint32_t getEndpointIntervalFrames(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor);
        
    /*!
     * @brief       Extract the number of streams supported by an endpoint
     * @discussion  This method parses endpoint descriptors and returns the number of streams supported as n in (2^n)
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to parse
     * @param       companionDescriptor The SuperSpeedEndpointCompanionDescriptor to parse
     * @return      uint32_t Encoded number of streams
     */
    uint32_t getEndpointMaxStreamsEncoded(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor, const SuperSpeedEndpointCompanionDescriptor* companionDescriptor);

    /*!
     * @brief       Extract the number of streams supported by an endpoint
     * @discussion  This method parses endpoint descriptors and returns the number of streams supported
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to parse
     * @param       companionDescriptor The SuperSpeedEndpointCompanionDescriptor to parse
     * @return      uint32_t Number of streams
     */
    uint32_t getEndpointMaxStreams(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor, const SuperSpeedEndpointCompanionDescriptor* companionDescriptor);
        
    /*!
     * @brief       Extract the maximum bus current required by a configuration descriptor
     * @discussion  This method parses a configuration descriptor and returns the number of milliamps required to power the device
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The ConfigurationDescriptor to parse
     * @return      uint32_t milliamps required
     */
    uint32_t getConfigurationMaxPowerMilliAmps(uint32_t usbDeviceSpeed, const ConfigurationDescriptor* descriptor);
        
    /*!
     * @brief       Validate the contents of an endpoint descriptor
     * @discussion  This method parses an endpoint descriptor and validates its contents.  If repairable validation errors are encountered, the descriptor passed in may be modified.
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to validate
     * @param       companionDescriptor The SuperSpeedEndpointCompanionDescriptor to validate, or NULL
     * @return      bool true if the descriptor passed validation, false if it did not
     */
    bool validateEndpointDescriptor(uint32_t usbDeviceSpeed, const EndpointDescriptor* descriptor, const SuperSpeedEndpointCompanionDescriptor* companionDescriptor);
        
    /*!
     * @brief       Validate the contents of an endpoint descriptor
     * @discussion  This method parses an endpoint descriptor and validates its contents.  If repairable validation errors are encountered, the descriptor passed in may be modified.
     * @param       usbDeviceSpeed The operational speed of the device
     * @param       descriptor The EndpointDescriptor to validate
     * @param       companionDescriptor The SuperSpeedEndpointCompanionDescriptor to validate, or NULL
     * @param       sspCompanionDescriptor The SuperSpeedPlusIsochronousEndpointCompanionDescriptor to validate, or NULL
     * @return      bool true if the descriptor passed validation, false if it did not
     */
    bool validateEndpointDescriptor(uint32_t usbDeviceSpeed,
                                    const EndpointDescriptor* descriptor,
                                    const SuperSpeedEndpointCompanionDescriptor* companionDescriptor,
                                    const SuperSpeedPlusIsochronousEndpointCompanionDescriptor* sspCompanionDescriptor);
    
#pragma mark String descriptor parsing
    /*!
     * @brief       Convert a USB string descriptor to a UTF8 character string
     * @discussion  This method uses utf8_encodestr with appropriate options to convert a USB string descriptor to a UTF8 string.
     * @param       stringDescriptor Descriptor to convert
     * @param       stringBuffer Buffer to write the UTF8 string to
     * @param       length Reference to size_t.  As input it is the size stringBuffer.  As output it is the number of character written to stringBuffer.
     * @return      IOReturn result code.  kIOReturnSuccess if any portion of the string could be converted and placed in stringBuffer.  kIOReturnError if the string descriptor cannot be converted to UTF8.
     */
    IOReturn stringDescriptorToUTF8(const StringDescriptor* stringDescriptor, char* stringBuffer, size_t& length);
    
#pragma mark Capability descriptor parsing
    /*!
     * @brief       Validate the contents of a BOS descriptor
     * @discussion  This method parses a BOS descriptor and validates its contents, as well as the contents of its associated device capability descriptors.  If repairable validation errors are encountered, the descriptor passed in may be modified.
     * @param       bosDescriptor The BOSDescriptor to validate
     * @return      bool true if the descriptor passed validation, false if it did not
     */
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
        
    // USB 3.0 9.4.12: Set SEL Standard Device Request
    struct DeviceRequestSetSELData
    {
        uint8_t     u1Sel;              // Time in μs for U1 System Exit Latency
        uint8_t     u1Pel;              // Time in μs for U1 Device to Host Exit Latency
        uint16_t    u2Sel;              // Time in μs for U2 System Exit Latency
        uint16_t    u2Pel;              // Time in μs for U2 Device to Host Exit Latency
    } __attribute__((packed));
        
    typedef struct DeviceRequestSetSELData DeviceRequestSetSELData;
    
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
        
    // USB 3.0 Table 10-16: Hub Parameters
    enum
    {
        kHubPort2PortExitLatencyNs          = 1000,
        kHubDelayNs                         = 400
    };
        
    // USB 3.0 Table 8-33: Timing Parameters
    enum
    {
        kPingResponseTimeNs                 = 400
    };

    enum tBusVoltage
    {
        kBusVoltageDefault                  = 5
    };
        
#ifdef __cplusplus
}


namespace StandardUSB20
{
#pragma mark BESL & HIRD Encodings

    /*!
     * @brief       BESL Encodings from Table X-X1 in USB 2.0 ECN Errata for Link Power Management
     * @discussion  This method converts the Best Effort Service Latency Index value used in the USB 2.0 Extension descriptor to Nanoseconds.
     * @param       beslIndex The BESL Index value used in the USB 2.0 Extension descriptor
     * @param       beslNs Reference to uint32_t.  As output, it is the converted BESL value in Nanoseconds
     * @return      result code.  kIOReturnSuccess if the conversion was successful. kIOReturnBadArgument if the input beslIndex is invalid.
     */
    IOReturn convertBESLIndexToNs(uint32_t beslIndex, uint32_t& beslNs);

    /*!
     * @brief       BESL Encodings from Table X-X1 in USB 2.0 ECN Errata for Link Power Management
     * @discussion  This method does the opposite of convertBESLIndexToUs. It converts the BESL value in Nanoseconds to Index.
     * @param       beslNs The converted BESL value in Nanoseconds
     * @param       beslIndex Reference to uint32_t. As output, it is the BESL Index value converted from Nanoseconds.
     * @return      result code.  kIOReturnSuccess if the conversion was successful. kIOReturnBadArgument if the input beslNs is invalid.
     */
    IOReturn convertBESLNsToIndex(uint32_t beslNs, uint32_t &beslIndex);

    enum tBusCurrent
    {
        kBusCurrentMinimum       = 100,
        kBusCurrentDefault       = 500,
        kBusCurrentMaxPowerUnits = 2

    };
}

namespace StandardUSB30
{
    enum tBusCurrent
    {
        kBusCurrentMinimum       = 150,
        kBusCurrentDefault       = 900,
        kBusCurrentMaxPowerUnits = 8
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
    
    // USB 3.1 Table 8-18
    enum tDeviceNotificationType
    {
        kDeviceNotificationTypeFunctionWake             = 1,
        kDeviceNotificationTypeLatencyTolerance         = 2,
        kDeviceNotificationTypeBusIntervalAdjustment    = 3,
        kDeviceNotificationTypeHostRoleRequest          = 4,
        kDeviceNotificationTypeSublinkSpeed             = 5
    };
    
    // USB 3.1 Table 8-36
    enum tTimingParameters
    {
        kTimingParameterBELTDefaultNs = 1 * 1000 * 1000,
        kTimingParameterBELTMinNs     =      125 * 1000
    };
    
    // USB 3.1 Table 10-12 Port Status Type Codes
    enum tHubPortStatusCode
    {
        tHubPortStatusCodeStandard = 0,
        tHubPortStatusCodePD       = 1,
        tHubPortStatusCodeExt      = 2,
        tHubPortStatusCodeCount    = 3
    };
    
    // USB 3.1 10.16.2.6 Get Port Status
    struct tHubPortStatusExt
    {
        uint16_t wPortStatus;
        uint16_t wPortChange;
        uint32_t dwExtPortStatus;
    } __attribute__((packed));
    
    // USB 3.1 Table 10-11.  Note, offsets are specific to dwExtPortStatus
    enum tHubExtStatus
    {
        kHubExtStatusRxSublinkSpeedID      = StandardUSBBitRange(0, 3),
        kHubExtStatusRxSublinkSpeedIDPhase = StandardUSBBitRangePhase(0,3),
        
        kHubExtStatusTxSublinkSpeedID      = StandardUSBBitRange(4, 7),
        kHubExtStatusTxSublinkSpeedIDPhase = StandardUSBBitRangePhase(4, 7),
        
        kHubExtStatusRxLaneCount      = StandardUSBBitRange(8, 11),
        kHubExtStatusRxLaneCountPhase = StandardUSBBitRangePhase(8, 11),
        
        kHubExtStatusTxLaneCount      = StandardUSBBitRange(12, 15),
        kHubExtStatusTxLaneCountPhase = StandardUSBBitRangePhase(12, 15)
    };
}
#endif // __cplusplus

#endif

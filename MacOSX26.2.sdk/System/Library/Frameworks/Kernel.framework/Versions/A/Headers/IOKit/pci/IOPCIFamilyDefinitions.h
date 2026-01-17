/*
 * Copyright (c) 2018-2021 Apple Inc. All rights reserved.
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

#ifndef IOPCIDefinitions_h
#define IOPCIDefinitions_h

#include <TargetConditionals.h>
#include <os/availability.h>
#if TARGET_OS_DRIVERKIT
#include <stdint.h>
#include <stddef.h>
#include <sys/_types/_uuid_t.h>
#include <DriverKit/IOTypes.h>
#include <DriverKit/IOLib.h>
#else
#include <IOKit/IOTypes.h>
#include <libkern/OSByteOrder.h>
#endif

// IOPCIDevice matching property names
#define kIOPCIMatchKey                  "IOPCIMatch"
#define kIOPCIPrimaryMatchKey           "IOPCIPrimaryMatch"
#define kIOPCISecondaryMatchKey         "IOPCISecondaryMatch"
#define kIOPCIClassMatchKey             "IOPCIClassMatch"

// pci express capabilities
#define kIOPCIExpressCapabilitiesKey     "IOPCIExpressCapabilities"
// pci express link status
#define kIOPCIExpressLinkStatusKey       "IOPCIExpressLinkStatus"
// pci express link capabilities
#define kIOPCIExpressLinkCapabilitiesKey "IOPCIExpressLinkCapabilities"
// pci express device capabilities
#define kIOPCIExpressDeviceCapabilitiesKey "IOPCIExpressDeviceCapabilities"
// pci express slot status
#define kIOPCIExpressSlotStatusKey       "IOPCIExpressSlotStatus"
// pci express slot capabilities
#define kIOPCIExpressSlotCapabilitiesKey "IOPCIExpressSlotCapabilities"
// pci express root capabilities
#define kIOPCIExpressRootCapabilitiesKey "IOPCIExpressRootCapabilities"
// pci express device capabilities 2
#define kIOPCIExpressDeviceCapabilities2Key "IOPCIExpressDeviceCapabilities2"
// pci express link capabilities 2
#define kIOPCIExpressLinkCapabilities2Key "IOPCIExpressLinkCapabilities2"
// pci express slot capabilities 2
#define kIOPCIExpressSlotCapabilities2Key "IOPCIExpressSlotCapabilities2"

// Power Management Capabilities Register
#define kIOPCIPowerManagementCapabilitiesKey "IOPCIPowerManagementCapabilities"
// MSI Message Control Register
#define kIOPCIMSIMessageControlKey "IOPCIMSIMessageControl"
// MSI-X Message Control Register
#define kIOPCIMSIXMessageControlKey "IOPCIMSIXMessageControl"
// ACS Capability Register
#define kIOPCIACSCapabilitiesKey "IOPCIACSCapabilities"
// L1PM Substates Capabilities Register
#define kIOPCIL1PMCapabilitiesKey "IOPCIL1PMCapabilities"
// AER Capabilities and Control Register
#define kIOPCIAERCapabilitiesKey "IOPCIAERCapabilities"
// FPB Capability Register
#define kIOPCIFPBCapabilitiesKey "IOPCIFPBCapabilities"
// PTM Capability Register
#define kIOPCIPTMCapabilitiesKey "IOPCIPTMCapabilities"

#define kIOPCIDeviceMemoryArrayKey       "IODeviceMemory"

// base address of the device's memory map
#define kIOPCIDeviceMemoryMapBase        "IOPCIDeviceMemoryMapBase"
// size of device memory map
#define kIOPCIDeviceMemoryMapSize        "IOPCIDeviceMemoryMapSize"
// mapper page size
#define kIOPCIDeviceMapperPageSize       "IOPCIDeviceMapperPageSize"

// IOPCIDevice matching property names
#define kIOPCITunnelCompatibleKey       "IOPCITunnelCompatible"
#define kIOPCITunnelledKey              "IOPCITunnelled"
#define kIOPCITunnelL1EnableKey         "IOPCITunnelL1Enable"

#define kIOPCITunnelRootDeviceModelIDKey  "IOPCITunnelRootDeviceModelID"
#define kIOPCITunnelRootDeviceVendorIDKey "IOPCITunnelRootDeviceVendorID"

#define kIOPCIPauseCompatibleKey        "IOPCIPauseCompatible"

// Properties that can be set on the IOPCIDevice
// property to control PCI default config space save on sleep.
// If false, config space will not be save/restored on power state transitions
#define kIOPMPCIConfigSpaceVolatileKey  "IOPMPCIConfigSpaceVolatile"
// property to disable express link on sleep
#define kIOPMPCISleepLinkDisableKey     "IOPMPCISleepLinkDisable"
// property to issue a secondary bus reset on sleep
#define kIOPMPCISleepResetKey           "IOPMPCISleepReset"
// property to provide bitmask for link train while scanning
#define kIOPCIRetrainLinkMaskKey        "IOPCIRetrainLinkMask"
// property to issue a link retrain while on wake
#define kIOPCIRetrainLinkKey            "IOPCIRetrainLink"
// property to check if endpoint is present on bridge
#define kIOPCIEndpointPrsnt             "IOPCIEndpointPrsnt"
// property to change the wait time for link up from spec default
#define kIOPCIWaitForLinkUpKey          "wait-for-link-up"
// property to override the dext crash reset type
#define kIOPCIDeviceCrashResetType "IOPCIDeviceCrashResetType"

// property to route driverkit memory accesses through the kernel
#define kIOPCIKernelMemoryAccess          "IOPCIKernelMemoryAccess"

/*  bits getInterruptType result */
enum
{
    kIOInterruptTypePCIMessaged  = 0x00010000,
    kIOInterruptTypePCIMessagedX = 0x00020000
};

/* Definitions of PCI Config Registers */
enum
{
    kIOPCIConfigurationOffsetVendorID          = 0x00,
    kIOPCIConfigurationOffsetDeviceID          = 0x02,
    kIOPCIConfigurationOffsetCommand           = 0x04,
    kIOPCIConfigurationOffsetStatus            = 0x06,
    kIOPCIConfigurationOffsetRevisionID        = 0x08,
    kIOPCIConfigurationOffsetClassCode         = 0x09,
    kIOPCIConfigurationOffsetCacheLineSize     = 0x0C,
    kIOPCIConfigurationOffsetLatencyTimer      = 0x0D,
    kIOPCIConfigurationOffsetHeaderType        = 0x0E,
    kIOPCIConfigurationOffsetBIST              = 0x0F,
    kIOPCIConfigurationOffsetBaseAddress0      = 0x10,
    kIOPCIConfigurationOffsetBaseAddress1      = 0x14,
    kIOPCIConfigurationOffsetBaseAddress2      = 0x18,
    kIOPCIConfigurationOffsetBaseAddress3      = 0x1C,
    kIOPCIConfigurationOffsetBaseAddress4      = 0x20,
    kIOPCIConfigurationOffsetBaseAddress5      = 0x24,
    kIOPCIConfigurationOffsetCardBusCISPtr     = 0x28,
    kIOPCIConfigurationOffsetSubSystemVendorID = 0x2C,
    kIOPCIConfigurationOffsetSubSystemID       = 0x2E,
    kIOPCIConfigurationOffsetExpansionROMBase  = 0x30,
    kIOPCIConfigurationOffsetCapabilitiesPtr   = 0x34,
    kIOPCIConfigurationOffsetInterruptLine     = 0x3C,
    kIOPCIConfigurationOffsetInterruptPin      = 0x3D,
    kIOPCIConfigurationOffsetMinimumGrant      = 0x3E,
    kIOPCIConfigurationOffsetMaximumLatency    = 0x3F
};

/* Definitions of Capabilities PCI Config Register */
enum
{
    kIOPCICapabilityIDOffset   = 0x00,
    kIOPCINextCapabilityOffset = 0x01,

    kIOPCICapabilityIDPowerManagement     = 0x01,
    kIOPCICapabilityIDAGP                 = 0x02,
    kIOPCICapabilityIDVitalProductData    = 0x03,
    kIOPCICapabilityIDSlotID              = 0x04,
    kIOPCICapabilityIDMSI                 = 0x05,
    kIOPCICapabilityIDCPCIHotswap         = 0x06,
    kIOPCICapabilityIDPCIX                = 0x07,
    kIOPCICapabilityIDLDT                 = 0x08,
    kIOPCICapabilityIDVendorSpecific      = 0x09,
    kIOPCICapabilityIDDebugPort           = 0x0a,
    kIOPCICapabilityIDCPCIResourceControl = 0x0b,
    kIOPCICapabilityIDHotplug             = 0x0c,
    kIOPCICapabilityIDAGP8                = 0x0e,
    kIOPCICapabilityIDSecure              = 0x0f,
    kIOPCICapabilityIDPCIExpress          = 0x10,
    kIOPCICapabilityIDMSIX                = 0x11,
    kIOPCICapabilityIDSATAConfiguration   = 0x12,
    kIOPCICapabilityIDAF                  = 0x13,
    kIOPCICapabilityIDEnhancedAllocation  = 0x14,
    kIOPCICapabilityIDFPB                 = 0x15,

#if defined(__LP64__)
    kIOPCIExpressCapabilityIDErrorReporting            = -0x01U,
    kIOPCIExpressCapabilityIDVirtualChannel            = -0x02U,
    kIOPCIExpressCapabilityIDDeviceSerialNumber        = -0x03U,
    kIOPCIExpressCapabilityIDPowerBudget               = -0x04U,
    kIOPCIExpressCapabilityIDRCLinkDeclaration         = -0x05U,
    kIOPCIExpressCapabilityIDRCInternalLinkCtrl        = -0x06U,
    kIOPCIExpressCapabilityIDRCECEndpointAssociation   = -0x07U,
    kIOPCIExpressCapabilityIDMFVC                      = -0x08U,
    kIOPCIExpressCapabilityIDVC_MFVCPresent            = -0x09U,
    kIOPCIExpressCapabilityIDRootComplexRegBlock       = -0x0AU,
    kIOPCIExpressCapabilityIDVSEC                      = -0x0BU,
    kIOPCIExpressCapabilityIDCAC                       = -0x0CU,
    kIOPCIExpressCapabilityIDAccessControlServices     = -0x0DU,
    kIOPCIExpressCapabilityIDAlternativeRoutingID      = -0x0EU,
    kIOPCIExpressCapabilityIDATS                       = -0x0FU,
    kIOPCIExpressCapabilityIDSRIOV                     = -0x10U,
    kIOPCIExpressCapabilityIDMRIOV                     = -0x11U,
    kIOPCIExpressCapabilityIDMulticast                 = -0x12U,
    kIOPCIExpressCapabilityIDPRI                       = -0x13U,
    kIOPCIExpressCapabilityIDAMD                       = -0x14U,
    kIOPCIExpressCapabilityIDResizableBAR              = -0x15U,
    kIOPCIExpressCapabilityIDDPA                       = -0x16U,
    kIOPCIExpressCapabilityIDTPHRequester              = -0x17U,
    kIOPCIExpressCapabilityIDLatencyTolerenceReporting = -0x18U,
    kIOPCIExpressCapabilityIDSPCIe                     = -0x19U,
    kIOPCIExpressCapabilityIDPMUX                      = -0x1AU,
    kIOPCIExpressCapabilityIDPASID                     = -0x1BU,
    kIOPCIExpressCapabilityIDLNR                       = -0x1CU,
    kIOPCIExpressCapabilityIDDPC                       = -0x1DU,
    kIOPCIExpressCapabilityIDL1PMSubstates             = -0x1EU,
    kIOPCIExpressCapabilityIDPrecisionTimeManagement   = -0x1FU,
    kIOPCIExpressCapabilityIDMPCIe                     = -0x20U,
    kIOPCIExpressCapabilityIDFRSQueueing               = -0x21U,
    kIOPCIExpressCapabilityIDReadinessTimeReporting    = -0x22U,
    kIOPCIExpressCapabilityIDDVSEC                     = -0x23U,
    kIOPCIExpressCapabilityIDVFResizableBAR            = -0x24U,
    kIOPCIExpressCapabilityIDDataLinkFeature           = -0x25U,
    kIOPCIExpressCapabilityIDPL16GTs                   = -0x26U,
    kIOPCIExpressCapabilityIDLaneMarginingRx           = -0x27U,
    kIOPCIExpressCapabilityIDHierarchyID               = -0x28U,
    kIOPCIExpressCapabilityIDNPEM                      = -0x29U,
    kIOPCIExpressCapabilityIDPL32GTs                   = -0x2AU,
    kIOPCIExpressCapabilityIDAlternateProtocol         = -0x2BU,
    kIOPCIExpressCapabilityIDSFI                       = -0x2CU,
#else  /* defined(__LP64__) */
    kIOPCIExpressCapabilityIDErrorReporting            = -0x01UL,
    kIOPCIExpressCapabilityIDVirtualChannel            = -0x02UL,
    kIOPCIExpressCapabilityIDDeviceSerialNumber        = -0x03UL,
    kIOPCIExpressCapabilityIDPowerBudget               = -0x04UL,
    kIOPCIExpressCapabilityIDRCLinkDeclaration         = -0x05UL,
    kIOPCIExpressCapabilityIDRCInternalLinkCtrl        = -0x06UL,
    kIOPCIExpressCapabilityIDRCECEndpointAssociation   = -0x07UL,
    kIOPCIExpressCapabilityIDMFVC                      = -0x08UL,
    kIOPCIExpressCapabilityIDVC_MFVCPresent            = -0x09UL,
    kIOPCIExpressCapabilityIDRootComplexRegBlock       = -0x0AUL,
    kIOPCIExpressCapabilityIDVSEC                      = -0x0BUL,
    kIOPCIExpressCapabilityIDCAC                       = -0x0CUL,
    kIOPCIExpressCapabilityIDAccessControlServices     = -0x0DUL,
    kIOPCIExpressCapabilityIDAlternativeRoutingID      = -0x0EUL,
    kIOPCIExpressCapabilityIDATS                       = -0x0FUL,
    kIOPCIExpressCapabilityIDSRIOV                     = -0x10UL,
    kIOPCIExpressCapabilityIDMRIOV                     = -0x11UL,
    kIOPCIExpressCapabilityIDMulticast                 = -0x12UL,
    kIOPCIExpressCapabilityIDPRI                       = -0x13UL,
    kIOPCIExpressCapabilityIDAMD                       = -0x14UL,
    kIOPCIExpressCapabilityIDResizableBAR              = -0x15UL,
    kIOPCIExpressCapabilityIDDPA                       = -0x16UL,
    kIOPCIExpressCapabilityIDTPHRequester              = -0x17UL,
    kIOPCIExpressCapabilityIDLatencyTolerenceReporting = -0x18UL,
    kIOPCIExpressCapabilityIDSPCIe                     = -0x19UL,
    kIOPCIExpressCapabilityIDPMUX                      = -0x1AUL,
    kIOPCIExpressCapabilityIDPASID                     = -0x1BUL,
    kIOPCIExpressCapabilityIDLNR                       = -0x1CUL,
    kIOPCIExpressCapabilityIDDPC                       = -0x1DUL,
    kIOPCIExpressCapabilityIDL1PMSubstates             = -0x1EUL,
    kIOPCIExpressCapabilityIDPrecisionTimeManagement   = -0x1FUL,
    kIOPCIExpressCapabilityIDMPCIe                     = -0x20UL,
    kIOPCIExpressCapabilityIDFRSQueueing               = -0x21UL,
    kIOPCIExpressCapabilityIDReadinessTimeReporting    = -0x22UL,
    kIOPCIExpressCapabilityIDDVSEC                     = -0x23UL,
    kIOPCIExpressCapabilityIDVFResizableBAR            = -0x24UL,
    kIOPCIExpressCapabilityIDDataLinkFeature           = -0x25UL,
    kIOPCIExpressCapabilityIDPL16GTs                   = -0x26UL,
    kIOPCIExpressCapabilityIDLaneMarginingRx           = -0x27UL,
    kIOPCIExpressCapabilityIDHierarchyID               = -0x28UL,
    kIOPCIExpressCapabilityIDNPEM                      = -0x29UL,
    kIOPCIExpressCapabilityIDPL32GTs                   = -0x2AUL,
    kIOPCIExpressCapabilityIDAlternateProtocol         = -0x2BUL,
    kIOPCIExpressCapabilityIDSFI                       = -0x2CUL,
#endif /* !defined(__LP64__) */
};

/* Command register definitions */
enum
{
    kIOPCICommandIOSpace          = 0x0001,
    kIOPCICommandMemorySpace      = 0x0002,
    kIOPCICommandBusLead          = 0x0004,
    kIOPCICommandBusMaster        API_DEPRECATED_WITH_REPLACEMENT("kIOPCICommandBusLead", macos(10.0, 12.4), ios(1.0, 15.4), watchos(1.0, 8.5), tvos(1.0, 15.4)) = kIOPCICommandBusLead,
    kIOPCICommandSpecialCycles    = 0x0008,
    kIOPCICommandMemWrInvalidate  = 0x0010,
    kIOPCICommandPaletteSnoop     = 0x0020,
    kIOPCICommandParityError      = 0x0040,
    kIOPCICommandAddressStepping  = 0x0080,
    kIOPCICommandSERR             = 0x0100,
    kIOPCICommandFastBack2Back    = 0x0200,
    kIOPCICommandInterruptDisable = 0x0400
};

/* Status register definitions */
enum
{
    kIOPCIStatusInterrupt          = 0x0008,
    kIOPCIStatusCapabilities       = 0x0010,
    kIOPCIStatusPCI66              = 0x0020,
    kIOPCIStatusUDF                = 0x0040,
    kIOPCIStatusFastBack2Back      = 0x0080,
    kIOPCIStatusDevSel0            = 0x0000,
    kIOPCIStatusDevSel1            = 0x0200,
    kIOPCIStatusDevSel2            = 0x0400,
    kIOPCIStatusDevSel3            = 0x0600,
    kIOPCIStatusTargetAbortCapable = 0x0800,
    kIOPCIStatusTargetAbortActive  = 0x1000,
    kIOPCIStatusLeadAbortActive    = 0x2000,
    kIOPCIStatusMasterAbortActive  API_DEPRECATED_WITH_REPLACEMENT("kIOPCIStatusLeadAbortActive", macos(10.0, 12.4), ios(1.0, 15.4), watchos(1.0, 8.5), tvos(1.0, 15.4)) = kIOPCIStatusLeadAbortActive,
    kIOPCIStatusSERRActive         = 0x4000,
    kIOPCIStatusParityErrActive    = 0x8000
};

enum
{
    kPCI2PCIOffsetPrimaryBus          = 0x18,
    kPCI2PCIOffsetSecondaryBus        = 0x19,
    kPCI2PCIOffsetSubordinateBus      = 0x1a,
    kPCI2PCIOffsetSecondaryLT         = 0x1b,
    kPCI2PCIOffsetIORange             = 0x1c,
    kPCI2PCIOffsetMemoryRange         = 0x20,
    kPCI2PCIOffsetPrefetchMemoryRange = 0x24,
    kPCI2PCIOffsetPrefetchUpperBase   = 0x28,
    kPCI2PCIOffsetPrefetchUpperLimit  = 0x2c,
    kPCI2PCIOffsetUpperIORange        = 0x30,
    kPCI2PCIOffsetBridgeControl       = 0x3e
};

// constants which are part of the PCI Bus Power Management Spec.
enum
{
    // capabilities bits in the 16 bit capabilities register
    kPCIPMCPMESupportFromD3Cold = 0x8000,
    kPCIPMCPMESupportFromD3Hot  = 0x4000,
    kPCIPMCPMESupportFromD2     = 0x2000,
    kPCIPMCPMESupportFromD1     = 0x1000,
    kPCIPMCPMESupportFromD0     = 0x0800,
    kPCIPMCD2Support            = 0x0400,
    kPCIPMCD1Support            = 0x0200,

    kPCIPMCD3Support = 0x0001
};

enum
{
    // bits in the power management control/status register
    kPCIPMCSPMEStatus      = 0x8000,
    kPCIPMCSPMEEnable      = 0x0100,
    kPCIPMCSPowerStateMask = 0x0003,
    kPCIPMCSPowerStateD3   = 0x0003,
    kPCIPMCSPowerStateD2   = 0x0002,
    kPCIPMCSPowerStateD1   = 0x0001,
    kPCIPMCSPowerStateD0   = 0x0000,

    kPCIPMCSDefaultEnableBits = (~(IOOptionBits)0),

    kPCIPMCSPMEDisableInS3 = 0x00010000,
    kPCIPMCSPMEWakeReason  = 0x00020000
};

enum
{
    kIOPCISlotCapabilitiesBitAttentionButtonPresent            = (1 << 0),
    kIOPCISlotCapabilitiesBitPowerControllerPresent            = (1 << 1),
    kIOPCISlotCapabilitiesBitMRLSensorPresent                  = (1 << 2),
    kIOPCISlotCapabilitiesBitAttentionIndicatorPresent         = (1 << 3),
    kIOPCISlotCapabilitiesBitPowerIndicatorPresent             = (1 << 4),
    kIOPCISlotCapabilitiesBitHotPlugSurprise                   = (1 << 5),
    kIOPCISlotCapabilitiesBitHotPlugCapable                    = (1 << 6),
    kIOPCISlotCapabilitiesBitElectromechanicalInterlockPresent = (1 << 17),
    kIOPCISlotCapabilitiesBitNoCommandCompletedSupport         = (1 << 18)
};

enum
{
	kIOPCISlotStatusAttentionButtonPressed          = (1 << 0),
	kIOPCISlotStatusPowerFaultDetected              = (1 << 1),
	kIOPCISlotStatusMRLSensorChanged                = (1 << 2),
	kIOPCISlotStatusPresenceDetectChanged           = (1 << 3),
	kIOPCISlotStatusCommandCompleted                = (1 << 4),
	kIOPCISlotStatusMRLSensorState                  = (1 << 5),
	kIOPCISlotStatusPresenceDetectState             = (1 << 6),
	kIOPCISlotStatusElectromechanicalInterlockState = (1 << 7),
	kIOPCISlotStatusDataLinkLayerStateChanged       = (1 << 8),
};

// PCIe error bits
enum
{
    kIOPCIAERCapCapHeaderOffset       = 0x0,
    kIOPCIAERCapUncErrStatusOffset    = 0x4,
    kIOPCIAERCapUncErrMaskOffset      = 0x8,
    kIOPCIAERCapUncErrSeverityOffset  = 0xC,
    kIOPCIAERCapCorErrStatusOffset    = 0x10,
    kIOPCIAERCapCorErrMaskOffset      = 0x14,
    kIOPCIAERCapCapControlOffset      = 0x18,
    kIOPCIAERCapHdrLogDW0Offset       = 0x1C,
    kIOPCIAERCapHdrLogDW1Offset       = 0x20,
    kIOPCIAERCapHdrLogDW2Offset       = 0x24,
    kIOPCIAERCapHdrLogDW3Offset       = 0x28,
    kIOPCIAERCapRootErrCmdOffset      = 0x2C,
    kIOPCIAERCapRootErrStatusOffset   = 0x30,
    kIOPCIAERCapErrSourceIDOffset     = 0x34,
    kIOPCIAERCapTLPPrefixLogDW0Offset = 0x38,
    kIOPCIAERCapTLPPrefixLogDW1Offset = 0x3C,
    kIOPCIAERCapTLPPrefixLogDW2Offset = 0x40,
    kIOPCIAERCapTLPPrefixLogDW3Offset = 0x44,
};

enum
{
    kIOPCIUncorrectableErrorBitDataLinkProtocol     = 4,
    kIOPCIUncorrectableErrorBitSurpriseDown         = 5,
    kIOPCIUncorrectableErrorBitPoisonedTLP          = 12,
    kIOPCIUncorrectableErrorBitFlowControlProtocol  = 13,
    kIOPCIUncorrectableErrorBitCompletionTimeout    = 14,
    kIOPCIUncorrectableErrorBitCompleterAbort       = 15,
    kIOPCIUncorrectableErrorBitUnexpectedCompletion = 16,
    kIOPCIUncorrectableErrorBitReceiverOverflow     = 17,
    kIOPCIUncorrectableErrorBitMalformedTLP         = 18,
    kIOPCIUncorrectableErrorBitECRC                 = 19,
    kIOPCIUncorrectableErrorBitUnsupportedRequest   = 20,

    kIOPCIUncorrectableErrorBitACSViolation          = 21,
    kIOPCIUncorrectableErrorBitInternal              = 22,
    kIOPCIUncorrectableErrorBitMCBlockedTLP          = 23,
    kIOPCIUncorrectableErrorBitAtomicOpEgressBlocked = 24,
    kIOPCIUncorrectableErrorBitTLPPrefixBlocked      = 25
};

enum
{
    kIOPCICorrectableErrorBitReceiver           = 0,
    kIOPCICorrectableErrorBitBadTLP             = 6,
    kIOPCICorrectableErrorBitBadDLLP            = 7,
    kIOPCICorrectableErrorBitReplayNumRollover  = 8,
    kIOPCICorrectableErrorBitReplayTimerTimeout = 12,
    kIOPCICorrectableErrorBitAdvisoryNonFatal   = 13,
    kIOPCICorrectableErrorBitCorrectedInternal  = 14,
    kIOPCICorrectableErrorBitHeaderLogOverflow  = 15,
};

typedef enum tIOPCILinkSpeed
{
    kIOPCILinkSpeed_2_5_GTs = 1, // Gen 1
    kIOPCILinkSpeed_5_GTs,       // Gen 2
    kIOPCILinkSpeed_8_GTs,       // Gen 3
    kIOPCILinkSpeed_16_GTs,      // Gen 4
    kIOPCILinkSpeed_32_GTs,      // Gen 5
} tIOPCILinkSpeed;

/*!  @enum       tIOPCIDeviceResetTypes
 *   @constant   kIOPCIDeviceResetTypeHotReset Issues a hot reset to the device without power being removed from the device.
 *               This will issue a hot reset from its upstream bridge by setting the secondary bus reset bit in the bridge's control
 *               register.
 *   @constant   kIOPCIDeviceResetTypeWarmReset Issues a warm reset to the device without power being removed from the device, if a platform
 *               specific function exists.
 *   @constant   kIOPCIDeviceResetTypeWarmResetDisable Performs the first half of a warm reset (e.g. assert PERST#), if a platform
 *               specific function exists. Upon completion, the device is unusable until the caller requests reset with type
 *               kIOPCIDeviceResetTypeWarmResetEnable.
 *
 *               This type facilitates the generation of a cold reset, i.e. by removing power before using kIOPCIDeviceResetTypeWarmResetDisable
 *               and re-applying it before using kIOPCIDeviceResetTypeWarmResetEnable.
 *   @constant   kIOPCIDeviceResetTypeWarmResetEnable Completes the warm reset operation initiated with type kIOPCIDeviceResetTypeWarmResetDisable
 *               (e.g. deassert PERST#). See kIOPCIDeviceResetTypeWarmResetDisable for more details.
 *   @constant   kIOPCIDeviceResetTypeFunctionReset Issues a function-level reset, if supported.
 */
typedef enum tIOPCIDeviceResetTypes
{
    kIOPCIDeviceResetTypeHotReset         = 0x00000001,
    kIOPCIDeviceResetTypeWarmReset        = 0x00000002,
    kIOPCIDeviceResetTypeWarmResetDisable = 0x00000004,
    kIOPCIDeviceResetTypeWarmResetEnable  = 0x00000008,
    kIOPCIDeviceResetTypeFunctionReset    = 0x00000010,
} tIOPCIDeviceResetTypes;

/*!  @enum       tIOPCIDeviceResetOptions
 *   @constant   kIOPCIDeviceResetOptionNone      No options selected
 *   @constant   kIOPCIDeviceResetOptionTerminate Terminate the IOPCIDevice(s) that were reset and re-probe the bus. This will stop
 *               any attached client drivers. Devices with reset-initiated personality changes should use this option.
 *
 *               This option causes the reset function to initiate the asynchronous termination process, but not block on its completion.
 */
typedef enum tIOPCIDeviceResetOptions
{
    kIOPCIDeviceResetOptionNone      = 0x00000000,
    kIOPCIDeviceResetOptionTerminate = 0x00000001,
} tIOPCIDeviceResetOptions;

enum tIOPCILinkControlASPMBits
{
    kIOPCILinkControlASPMBitsDisabled = 0,
    kIOPCILinkControlASPMBitsL0s      = (1 << 0),
    kIOPCILinkControlASPMBitsL1       = (1 << 1),
    kIOPCILinkControlASPMBitsL0sL1    = kIOPCILinkControlASPMBitsL0s | kIOPCILinkControlASPMBitsL1
};

/*!  @enum       tIOPCIAccessOptions
 *   @brief      Options passed to memory space accessor functions
 *   @constant   kIOPCIAccessLatencyTolerantHint Hint to host software that this PCIe access is not in a performance critical section,
 *               and host software is permitted to offload the access to a DMA engine in order to free the CPU for other work to
 *               optimize overall system performance. Use of this hint may increase the latency of the memory space accessor function.
 */
typedef enum tIOPCIAccessOptions
{
    kIOPCIAccessLatencyTolerantHint = (1 << 0),
} tIOPCIAccessOptions;

#endif /* IOPCIDefinitions_h */

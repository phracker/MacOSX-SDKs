/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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
/*
 * Copyright (c) 1999 Apple Computer, Inc.  All rights reserved.
 *
 * Common symbol definitions for IOKit.
 *
 * HISTORY
 *
 */


#ifndef _IOKIT_IOKITKEYS_H
#define _IOKIT_IOKITKEYS_H

// properties found in the registry root
#define kIOKitBuildVersionKey           "IOKitBuildVersion"
#define kIOKitDiagnosticsKey            "IOKitDiagnostics"
// a dictionary keyed by plane name
#define kIORegistryPlanesKey            "IORegistryPlanes"
#define kIOCatalogueKey                 "IOCatalogue"

// registry plane names
#define kIOServicePlane                 "IOService"
#define kIOPowerPlane                   "IOPower"
#define kIODeviceTreePlane              "IODeviceTree"
#define kIOAudioPlane                   "IOAudio"
#define kIOFireWirePlane                "IOFireWire"
#define kIOUSBPlane                     "IOUSB"

// registry ID number
#define kIORegistryEntryIDKey           "IORegistryEntryID"
// property name to get array of property names
#define kIORegistryEntryPropertyKeysKey "IORegistryEntryPropertyKeys"

// IOService class name
#define kIOServiceClass                 "IOService"

// IOResources class name
#define kIOResourcesClass               "IOResources"

// IOService driver probing property names
#define kIOClassKey                     "IOClass"
#define kIOProbeScoreKey                "IOProbeScore"
#define kIOKitDebugKey                  "IOKitDebug"

// Properties to be supported as API
#define kIOSupportedPropertiesKey       "IOSupportedProperties"
// Properties writable by dexts
#define kIOUserServicePropertiesKey     "IOUserServiceProperties"


// IOService matching property names
#define kIOProviderClassKey             "IOProviderClass"
#define kIONameMatchKey                 "IONameMatch"
#define kIOPropertyMatchKey             "IOPropertyMatch"
#define kIOPropertyExistsMatchKey       "IOPropertyExistsMatch"
#define kIOPathMatchKey                 "IOPathMatch"
#define kIOLocationMatchKey             "IOLocationMatch"
#define kIOParentMatchKey               "IOParentMatch"
#define kIOResourceMatchKey             "IOResourceMatch"
#define kIOResourceMatchedKey           "IOResourceMatched"
#define kIOMatchedServiceCountKey       "IOMatchedServiceCountMatch"

#define kIONameMatchedKey               "IONameMatched"

#define kIOMatchCategoryKey             "IOMatchCategory"
#define kIODefaultMatchCategoryKey      "IODefaultMatchCategory"

#define kIOMatchedPersonalityKey        "IOMatchedPersonality"
#define kIORematchPersonalityKey        "IORematchPersonality"
#define kIORematchCountKey              "IORematchCount"
#define kIODEXTMatchCountKey            "IODEXTMatchCount"

// Entitlements to check against dext process
// Property is an array, one or more of which may match, of:
//   an array of entitlement strings, all must be present
// Any array can be a single string.
#define kIOServiceDEXTEntitlementsKey   "IOServiceDEXTEntitlements"

// Entitlement required to open dext connection
#define kIODriverKitEntitlementKey      "com.apple.developer.driverkit"

// Entitlements required to open dext IOUserClient
// Property is an array of strings containing CFBundleIdentifiers of service being opened
#define kIODriverKitUserClientEntitlementsKey "com.apple.developer.driverkit.userclient-access"

// Allows the entitled process to open a user client connection to any dext that has specific entitlements
// Property is an array of strings containing entitlements, one of which needs to be present
// in the dext providing the user client being opened
#define kIODriverKitRequiredEntitlementsKey "com.apple.private.driverkit.driver-access"

// Entitlement of a dext that allows any task to open one of its IOUserClients
#define kIODriverKitUserClientEntitlementAllowAnyKey "com.apple.developer.driverkit.allow-any-userclient-access"

#define kIODriverKitUserClientEntitlementAdministratorKey "com.apple.developer.driverkit.administrator"

// Other DriverKit entitlements
#define kIODriverKitUSBTransportEntitlementKey "com.apple.developer.driverkit.transport.usb"
#define kIODriverKitHIDTransportEntitlementKey "com.apple.developer.driverkit.transport.hid"
#define kIODriverKitHIDFamilyDeviceEntitlementKey "com.apple.developer.driverkit.family.hid.device"
#define kIODriverKitHIDFamilyEventServiceEntitlementKey "com.apple.developer.driverkit.family.hid.eventservice"
#define kIODriverKitTransportBuiltinEntitlementKey "com.apple.developer.driverkit.builtin"

// Entitlement required to read nvram root-only properties as non-root user
#define kIONVRAMReadAccessKey           "com.apple.private.iokit.nvram-read-access"
// Entitlement required to write nvram properties as non-root user
#define kIONVRAMWriteAccessKey           "com.apple.private.iokit.nvram-write-access"
// Entitlement required to set properties on the IOResources object as non-root user
#define kIOResourcesSetPropertyKey       "com.apple.private.iokit.ioresources.setproperty"
// Entitlement required to read/write to the system nvram region
#define kIONVRAMSystemAllowKey           "com.apple.private.iokit.system-nvram-allow"

// When possible, defer matching of this driver until kextd has started.
#define kIOMatchDeferKey                                "IOMatchDefer"

// Published after processor_start() has been called on all CPUs at boot time.
#define kIOAllCPUInitializedKey                         "IOAllCPUInitialized"

// IOService default user client class, for loadable user clients
#define kIOUserClientClassKey           "IOUserClientClass"

// key to find IOMappers
#define kIOMapperIDKey                          "IOMapperID"


#define kIOUserClientCrossEndianKey             "IOUserClientCrossEndian"
#define kIOUserClientCrossEndianCompatibleKey   "IOUserClientCrossEndianCompatible"
#define kIOUserClientSharedInstanceKey          "IOUserClientSharedInstance"
#define kIOUserClientDefaultLockingKey                  "IOUserClientDefaultLocking"
// diagnostic string describing the creating task
#define kIOUserClientCreatorKey         "IOUserClientCreator"
// the expected cdhash value of the userspace driver executable
#define kIOUserServerCDHashKey          "IOUserServerCDHash"

#define kIOUserUserClientKey                    "IOUserUserClient"

#define kIOUserServerOneProcessKey      "IOUserServerOneProcess"


// IOService notification types
#define kIOPublishNotification          "IOServicePublish"
#define kIOFirstPublishNotification     "IOServiceFirstPublish"
#define kIOMatchedNotification          "IOServiceMatched"
#define kIOFirstMatchNotification       "IOServiceFirstMatch"
#define kIOTerminatedNotification       "IOServiceTerminate"
#define kIOWillTerminateNotification    "IOServiceWillTerminate"

// IOService interest notification types
#define kIOGeneralInterest              "IOGeneralInterest"
#define kIOBusyInterest                 "IOBusyInterest"
#define kIOAppPowerStateInterest        "IOAppPowerStateInterest"
#define kIOPriorityPowerStateInterest   "IOPriorityPowerStateInterest"

#define kIOPlatformDeviceMessageKey     "IOPlatformDeviceMessage"

// IOService interest notification types
#define kIOCFPlugInTypesKey             "IOCFPlugInTypes"

#define kIOCompatibilityMatchKey            "IOCompatibilityMatch"
#define kIOCompatibilityPropertiesKey   "IOCompatibilityProperties"
#define kIOPathKey                                      "IOPath"


// properties found in services that implement command pooling
#define kIOCommandPoolSizeKey           "IOCommandPoolSize"             // (OSNumber)

// properties found in services that implement priority
#define kIOMaximumPriorityCountKey      "IOMaximumPriorityCount"        // (OSNumber)

// properties found in services that have transfer constraints
#define kIOMaximumBlockCountReadKey             "IOMaximumBlockCountRead"             // (OSNumber)
#define kIOMaximumBlockCountWriteKey            "IOMaximumBlockCountWrite"            // (OSNumber)
#define kIOMaximumByteCountReadKey              "IOMaximumByteCountRead"              // (OSNumber)
#define kIOMaximumByteCountWriteKey             "IOMaximumByteCountWrite"             // (OSNumber)
#define kIOMaximumSegmentCountReadKey           "IOMaximumSegmentCountRead"           // (OSNumber)
#define kIOMaximumSegmentCountWriteKey          "IOMaximumSegmentCountWrite"          // (OSNumber)
#define kIOMaximumSegmentByteCountReadKey       "IOMaximumSegmentByteCountRead"       // (OSNumber)
#define kIOMaximumSegmentByteCountWriteKey      "IOMaximumSegmentByteCountWrite"      // (OSNumber)
#define kIOMinimumSegmentAlignmentByteCountKey  "IOMinimumSegmentAlignmentByteCount"  // (OSNumber)
#define kIOMaximumSegmentAddressableBitCountKey "IOMaximumSegmentAddressableBitCount" // (OSNumber)
#define kIOMinimumSaturationByteCountKey        "IOMinimumSaturationByteCount"        // (OSNumber)
#define kIOMaximumSwapWriteKey                  "IOMaximumSwapWrite"                  // (OSNumber)

// properties found in services that wish to describe an icon
//
// IOIcon =
// {
//     CFBundleIdentifier   = "com.example.driver.example";
//     IOBundleResourceFile = "example.icns";
// };
//
// where IOBundleResourceFile is the filename of the resource

#define kIOIconKey               "IOIcon"               // (OSDictionary)
#define kIOBundleResourceFileKey "IOBundleResourceFile" // (OSString)

#define kIOBusBadgeKey           "IOBusBadge"           // (OSDictionary)
#define kIODeviceIconKey         "IODeviceIcon"         // (OSDictionary)

// property of root that describes the machine's serial number as a string
#define kIOPlatformSerialNumberKey      "IOPlatformSerialNumber"        // (OSString)

// property of root that describes the machine's UUID as a string
#define kIOPlatformUUIDKey      "IOPlatformUUID"        // (OSString)

// IODTNVRAM property keys
#define kIONVRAMBootArgsKey             "boot-args"
#define kIONVRAMDeletePropertyKey       "IONVRAM-DELETE-PROPERTY"
#define kIONVRAMSyncNowPropertyKey      "IONVRAM-SYNCNOW-PROPERTY"
#define kIONVRAMActivateCSRConfigPropertyKey    "IONVRAM-ARMCSR-PROPERTY"
#define kIODTNVRAMPanicInfoKey          "aapl,panic-info"

// keys for complex boot information
#define kIOBootDeviceKey          "IOBootDevice"                // dict | array of dicts
#define kIOBootDevicePathKey      "IOBootDevicePath"    // arch-neutral OSString
#define kIOBootDeviceSizeKey      "IOBootDeviceSize"    // OSNumber of bytes

// keys for OS Version information
#define kOSBuildVersionKey              "OS Build Version"

//
#define kIOStateNotificationItemCreateKey                               "com.apple.iokit.statenotification.create"
#define kIOStateNotificationItemSetKey                                  "com.apple.iokit.statenotification.set"
#define kIOStateNotificationItemCopyKey                                 "com.apple.iokit.statenotification.copy"

#define kIOStateNotificationNameKey                                             "com.apple.iokit.statenotification.name"
#define kIOStateNotificationEntitlementSetKey           "com.apple.iokit.statenotification.entitlement-set"
#define kIOStateNotificationEntitlementGetKey           "com.apple.iokit.statenotification.entitlement-get"

//
#define kIOSystemStateClamshellKey      "com.apple.iokit.pm.clamshell"

#define kIOSystemStateSleepDescriptionKey                               "com.apple.iokit.pm.sleepdescription"
#define kIOSystemStateSleepDescriptionReasonKey                 "com.apple.iokit.pm.sleepreason"
#define kIOSystemStateSleepDescriptionHibernateStateKey      "com.apple.iokit.pm.hibernatestate"

#define kIOSystemStateHaltDescriptionKey                               "com.apple.iokit.pm.haltdescription"
#define kIOSystemStateHaltDescriptionHaltStateKey      "com.apple.iokit.pm.haltstate"

#define kIOSystemStatePowerSourceDescriptionKey                               "com.apple.iokit.pm.powersourcedescription"
#define kIOSystemStatePowerSourceDescriptionACAttachedKey      "com.apple.iokit.pm.acattached"

#endif /* ! _IOKIT_IOKITKEYS_H */

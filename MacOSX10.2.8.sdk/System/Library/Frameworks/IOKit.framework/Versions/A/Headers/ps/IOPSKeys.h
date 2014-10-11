/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 *** UPS Power Management claimed ***
 * If a third-party app manages UPS power it should set this key in the SCDynamicStore.
 * Set it with a value of kCFBooleanTrue.
 * If this key is not set, OS X will provide a minimal default UPS Power Management
 * implementation that includes clean shutdown if the attached UPS falls below 20%
 * remaining battery power.
 * It should be used with the State: prefix, as in "State:/IOKit/UPSPowerManagementClaimed"
 */
#define kIOPSUPSManagementClaimed       "/IOKit/UPSPowerManagementClaimed"


/*
 * UPS settings keys
 * These define the power level (units are %) to take action like warning the user
 * or shutting down.
 */
#define kIOPSLowWarnLevelKey           "Low Warn Level"
#define kIOPSDeadWarnLevelKey          "Shutdown Level"


/*
 *** SCDynamicStore keys ***
 * kIOPSDynamicStorePath should be used with the "State:" prefix, as in "State:/IOKit/PowerSources"
 */
#define kIOPSDynamicStorePath          "/IOKit/PowerSources"


/*
 * Power Source data keys
 * These keys specify the values in a dictionary of PowerSource details.
 * Use these keys in conjunction with the dictionary returned by 
 * IOPSGetPowerSourceDescription()
 */ 
// Type CFString, value is kIOPSACPowerValue or kIOPSBatteryPowerValue
#define kIOPSPowerSourceStateKey       "Power Source State"

// Type CFNumber (signed integer), units are %
#define kIOPSCurrentCapacityKey        "Current Capacity"

// Type CFNumber (signed integer), units are %
#define kIOPSMaxCapacityKey            "Max Capacity"

// Type CFNumber (signed integer), units are minutes
// Only valid if the value of kIOPSIsChargingKey is false.
// -1 indicates "Still Calulating"
#define kIOPSTimeToEmptyKey            "Time to Empty"

// Type CFNumber (signed integer), units are minutes. 
// Only valid if the value of kIOPSIsChargingKey is true.
// -1 indicates "Still Calulating"
#define kIOPSTimeToFullChargeKey       "Time to Full Charge"

// Type CFBoolean - kCFBooleanTrue or kCFBooleanFalse
#define kIOPSIsChargingKey             "Is Charging"

// Type CFBoolean - kCFBooleanTrue or kCFBooleanFalse
#define kIOPSIsPresentKey              "Is Present"

// Type CFNumber (signed integer) - units are mV
#define kIOPSVoltageKey                "Voltage"

// Type CFNumber (signed integer) - units are mA
#define kIOPSCurrentKey                "Current"

// Type CFStringRef
#define kIOPSNameKey                   "Name"

// Type CFStringRef - value is one of the transport types below
#define kIOPSTransportTypeKey          "Transport Type"


/*
 * Transport types
 */
#define kIOPSSerialTransportType       "Serial"
#define kIOPSUSBTransportType          "USB"
#define kIOPSNetworkTransportType      "Ethernet"
#define kIOPSInternalType              "Internal"

/*
 * PS state 
 */
#define kIOPSOffLineValue              "Off Line"
#define kIOPSACPowerValue              "AC Power"
#define kIOPSBatteryPowerValue         "Battery Power"


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

/*!
    @header IOPSKeys.h
    
    IOPSKeys.h defines C strings for use accessing power source data in IOPowerSource
    CFDictionaries, as returned by IOPSGetPowerSourceDescription()<br>
    Note that all of these C strings must be converted to CFStrings before use. You can wrap
    them with the CFSTR() macro, or create a CFStringRef (that you must later CFRelease()) using CFStringCreateWithCString()
 */  
#ifndef _IOPSKEYS_H_
#define _IOPSKEYS_H_

/*!
 @define kIOPSUPSManagementClaimed
 @abstract Claims UPS management for a third-party driver.
 @discussion kIOPSUPSManagementClaimed Obsolete. Do not use.
 */
#define kIOPSUPSManagementClaimed       "/IOKit/UPSPowerManagementClaimed"


/*!
    @define kIOPSLowWarnLevelKey 
    @abstract Key for the "Warning" UPS low power trigger-level. Default is 50%.
*/
#define kIOPSLowWarnLevelKey           "Low Warn Level"

/*!
    @define kIOPSDeadWarnLevelKey 
    @abstract Key for the "Shutdown System" low power trigger-level. Default is 20%.
*/
#define kIOPSDeadWarnLevelKey          "Shutdown Level"


/*!
    @define kIOPSDynamicStorePath
    @abstract This is only used for internal bookkeeping, and should be ignored.
 */
#define kIOPSDynamicStorePath          "/IOKit/PowerSources"


/*
 * Power Source Commands
 * These keys specify UPS-specific commands.
 */ 


/*!
    @define kIOPSCommandDelayedRemovePowerKey
    @abstract Command to give a UPS when it should remove power from its AC plugs in a specified amount of time
        <br>The matching argumnet should be a CFNumber of kCFNumberIntType specifying when the UPS should
        <br>remove power from its AC power ports.
*/
#define kIOPSCommandDelayedRemovePowerKey     "Delayed Remove Power"

/*!
    @define kIOPSCommandEnableAudibleAlarmKey
    @abstract Command to give a UPS when it should either enable or disable the audible alarm.
        <br>The matching argumnet should be a CFBooleanRef where kCFBooleanTrue enables the alarm and 
        <br>kCFBooleanFalse diables the alarm
*/
#define kIOPSCommandEnableAudibleAlarmKey     "Enable Audible Alarm"

/*!
    @define kIOPSCommandStartupDelayKey
    @abstract Tell UPS how long it should wait for 
        <br>The matching argumnet should be a CFNumber of kCFNumberIntType specifying when the UPS should
        <br>remove power from its AC power ports.
*/
#define kIOPSCommandStartupDelayKey           "Startup Delay"


/*
 * Power Source data keys
 * These keys specify the values in a dictionary of PowerSource details.
 * Use these keys in conjunction with the dictionary returned by 
 * IOPSGetPowerSourceDescription()
 */ 

/*!
    @define kIOPSPowerSourceID
    @abstract CFNumber key uniquely identifying a UPS attached to the system.
        <br>Type CFNumber, kCFNumberIntType, uniquely identifying an attached UPS.
*/
#define kIOPSPowerSourceIDKey          "Power Source ID"

 
/*!
    @define kIOPSPowerSourceStateKey
    @abstract CFDictionary key for the current source of power.
        <br>Type CFString, value is kIOPSACPowerValue, kIOPSBatteryPowerValue, or kIOPSOffLineValue.
*/
#define kIOPSPowerSourceStateKey       "Power Source State"

/*!
    @define kIOPSCurrentCapacityKey
    @abstract CFDictionary key for the current power source's capacity.
        <br>Type CFNumber (signed integer), units are relative to "Max Capacity"
*/
#define kIOPSCurrentCapacityKey        "Current Capacity"

/*!
    @define kIOPSMaxCapacityKey
    @abstract CFDictionary key for the current power source's maximum or "Full Charge Capacity"
        <br>Type CFNumber (signed integer), units are %
*/
#define kIOPSMaxCapacityKey            "Max Capacity"

/*!
    @define kIOPSMaxCapacityKey
    @abstract CFDictionary key for the current power source's design capacity
        <br>Type CFNumber (signed integer), units are %
*/
#define kIOPSDesignCapacityKey          "DesignCapacity"

/*!
    @define kIOPSTimeToEmptyKey
    @abstract CFDictionary key for the current power source's time remaining until empty.
        Only valid if the power source is running off its own power. That's when the 
        kIOPSPowerSourceStateKey has value kIOPSBatteryPowerValue, 
        and the value of kIOPSIsChargingKey is kCFBooleanFalse.
        <br>Type CFNumber (signed integer), units are minutes
        <br>A value of -1 indicates "Still Calculating the Time", otherwise estimated minutes left on the battery.
*/

#define kIOPSTimeToEmptyKey            "Time to Empty"

/*!
    @define kIOPSTimeToFullChargeKey
    @abstract CFDictionary key for the current power source's time remaining until empty.
        Only valid if the value of kIOPSIsChargingKey is kCFBooleanTrue.
        <br>Type CFNumber (signed integer), units are minutes
        <br>A value of -1 indicates "Still Calculating the Time", otherwise estimated minutes until fully charged.
*/
#define kIOPSTimeToFullChargeKey       "Time to Full Charge"

/*!
    @define kIOPSIsChargingKey
    @abstract CFDictionary key for the current power source's charging state
        <br>Type CFBoolean - kCFBooleanTrue or kCFBooleanFalse
*/
#define kIOPSIsChargingKey             "Is Charging"

/*!
    @define kIOPSIsPresentKey
    @abstract CFDictionary key for the current power source's presence. 
    <br>For instance, a PowerBook with the capacity for two batteries but 
        with only one present would show two power source dictionaries, 
        but kIOPSIsPresentKey would have the value kCFBooleanFalse in one of them.
    <br>Type CFBoolean - kCFBooleanTrue or kCFBooleanFalse
*/
#define kIOPSIsPresentKey              "Is Present"

/*!
    @define kIOPSVoltageKey
    @abstract CFDictionary key for the current power source's electrical voltage.
    <br>Type CFNumber (signed integer) - units are mV
*/
#define kIOPSVoltageKey                "Voltage"

/*!
    @define kIOPSCurrentKey
    @abstract CFDictionary key for the current power source's electrical current.
    <br>Type CFNumber (signed integer) - units are mA
*/
#define kIOPSCurrentKey                "Current"

/*!
    @define kIOPSNameKey
    @abstract CFDictionary key for the current power source's name.
    <br>Type CFStringRef
*/
#define kIOPSNameKey                   "Name"

/*!
    @define kIOPSTransportTypeKey
    @abstract CFDictionary key for the current power source's transport type.
    <br>Type CFStringRef. Valid transport types are kIOPSSerialTransportType, 
    kIOPSUSBTransportType, kIOPSNetworkTransportType, or kIOPSInternalType.
*/
#define kIOPSTransportTypeKey          "Transport Type"

/*!
    @define kIOPSVendorDataKey
    @abstract CFDictionary key for arbitrary vendor data. The value should be a 
    <br>CFDictionary 
    kIOPSUSBTransportType, kIOPSNetworkTransportType, or kIOPSInternalType.
*/
#define kIOPSVendorDataKey          "Vendor Specific Data"

/*!
    @define kIOPSBatteryHealthKey
    @abstract CFDictionary key for the current power source's "health" estimate
        <br>Type CFStringRef
*/
#define kIOPSBatteryHealthKey       "BatteryHealth"

/*!
    @define kIOPSBatteryHealthConfidenceKey
    @abstract CFDictionary key for our confidence in the accuracy of our 
        power source's "health" estimate
        <br>Type CFStringRef
*/
#define kIOPSHealthConfidenceKey    "HealthConfidence"


/*!
    @define kIOPSMaxErrKey
    @abstract CFDictionary key for the current power source's percentage error
        in capacity reporting.
        <br>Type CFNumberRef, non-negative integer
*/
#define kIOPSMaxErrKey              "MaxErr"

/*
 * Transport types
 */
/*!
    @define kIOPSSerialTransportType
    @abstract Value for key kIOPSTransportTypeKey. Indicates the power source is a UPS attached over a serial connection.
*/
#define kIOPSSerialTransportType       "Serial"
/*!
    @define kIOPSUSBTransportType
    @abstract Value for key kIOPSTransportTypeKey. Indicates the power source is a UPS attached over a USB connection.
*/
#define kIOPSUSBTransportType          "USB"
/*!
    @define kIOPSNetworkTransportType
    @abstract Value for key kIOPSTransportTypeKey. Indicates the power source is a UPS attached over a network connection (and it may be managing several computers).
*/
#define kIOPSNetworkTransportType      "Ethernet"
/*!
    @define kIOPSInternalType
    @abstract Value for key kIOPSTransportTypeKey. Indicates the power source is an internal battery.
*/
#define kIOPSInternalType              "Internal"

/*
 * PS state 
 */
/*!
    @define kIOPSOffLineValue
    @abstract Value for key kIOPSPowerSourceStateKey. Power source is off-line or no longer connected.
*/
#define kIOPSOffLineValue              "Off Line"
/*!
    @define kIOPSACPowerValue
    @abstract Value for key kIOPSPowerSourceStateKey. Power source is connected to external or AC power, and is not draining the internal battery.
*/
#define kIOPSACPowerValue              "AC Power"
/*!
    @define kIOPSBatteryPowerValue
    @abstract Value for key kIOPSPowerSourceStateKey. Power source is currently using the internal battery.
*/
#define kIOPSBatteryPowerValue         "Battery Power"

/*
 * Battery Health & Confidence values
 */
/*!
    @define kIOPSPoorValue
    @abstract Value for key kIOPSBatteryHealthKey & kIOPMPSHealthConfidenceKey.
*/
#define kIOPSPoorValue                  "Poor"
/*!
    @define kIOPSFairValue
    @abstract Value for key kIOPSBatteryHealthKey & kIOPMPSHealthConfidenceKey.
*/
#define kIOPSFairValue                  "Fair"
/*!
    @define kIOPSGoodValue
    @abstract Value for key kIOPSBatteryHealthKey & kIOPMPSHealthConfidenceKey.
*/
#define kIOPSGoodValue                  "Good"

#endif

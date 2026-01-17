/*
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2020 Apple Computer, Inc.  All Rights Reserved.
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_HID_IOHIDKEYS_H_
#define _IOKIT_HID_IOHIDKEYS_H_

#include <sys/cdefs.h>
#include <IOKit/hidsystem/IOHIDParameter.h>
#include <IOKit/IOReturn.h>
#include <IOKit/IOMessage.h>
#include <IOKit/hid/IOHIDProperties.h>
#include <IOKit/hid/IOHIDDeviceTypes.h>
#include <IOKit/hid/IOHIDDeviceKeys.h>

__BEGIN_DECLS

/* The following keys are used to search the IORegistry for HID related services
*/

/* This is used to find HID Devices in the IORegistry */
#define kIOHIDDeviceKey                     "IOHIDDevice"

/*!
    @defined HID Device Property Keys
    @abstract Keys that represent properties of a particular device.
    @discussion Keys that represent properties of a particular device.  Can be added
        to your matching dictionary when refining searches for HID devices.
        <br><br>
        <b>Please note:</b><br>
        kIOHIDPrimaryUsageKey and kIOHIDPrimaryUsagePageKey are no longer 
        rich enough to describe a device's capabilities.  Take, for example, a
        device that describes both a keyboard and a mouse in the same descriptor.  
        The previous behavior was to only describe the keyboard behavior with the 
        primary usage and usage page.   Needless to say, this would sometimes cause 
        a program interested in mice to skip this device when matching.  
        <br>
        Thus we have added 3 
        additional keys:
        <ul>
            <li>kIOHIDDeviceUsageKey</li>
            <li>kIOHIDDeviceUsagePageKey</li>
            <li>kIOHIDDeviceUsagePairsKey</li>
        </ul>
        kIOHIDDeviceUsagePairsKey is used to represent an array of dictionaries containing 
        key/value pairs referenced by kIOHIDDeviceUsageKey and kIOHIDDeviceUsagePageKey.  
        These usage pairs describe all application type collections (behaviors) defined 
        by the device.
        <br><br>
        An application interested in only matching on one criteria would only add the 
        kIOHIDDeviceUsageKey and kIOHIDDeviceUsagePageKey keys to the matching dictionary.
        If it is interested in a device that has multiple behaviors, the application would
        instead add an array or dictionaries referenced by kIOHIDDeviceUsagePairsKey to his 
        matching dictionary.
*/
#define kIOHIDVendorIDSourceKey             "VendorIDSource"
#define kIOHIDStandardTypeKey               "StandardType"
#define kIOHIDSampleIntervalKey             "SampleInterval"
#define kIOHIDResetKey                      "Reset"
#define kIOHIDKeyboardLanguageKey           "KeyboardLanguage"
#define kIOHIDAltHandlerIdKey               "alt_handler_id"
#define kIOHIDDisplayIntegratedKey          "DisplayIntegrated"
#define kIOHIDProductIDMaskKey              "ProductIDMask"
#define kIOHIDProductIDArrayKey             "ProductIDArray"
#define kIOHIDPowerOnDelayNSKey             "HIDPowerOnDelayNS"
#define kIOHIDCategoryKey                   "Category"
#define kIOHIDMaxResponseLatencyKey         "MaxResponseLatency"
#define kIOHIDUniqueIDKey                   "UniqueID"
#define kIOHIDModelNumberKey                "ModelNumber"


#define kIOHIDTransportUSBValue                 "USB"
#define kIOHIDTransportBluetoothValue           "Bluetooth"
#define kIOHIDTransportBluetoothLowEnergyValue  "BluetoothLowEnergy"
#define kIOHIDTransportAIDBValue                "AID"
#define kIOHIDTransportI2CValue                 "I2C"
#define kIOHIDTransportSPIValue                 "SPI"
#define kIOHIDTransportSerialValue              "Serial"
#define kIOHIDTransportIAPValue                 "iAP"
#define kIOHIDTransportAirPlayValue             "AirPlay"
#define kIOHIDTransportSPUValue                 "SPU"
#define kIOHIDTransportBTAACPValue              "BT-AACP"
#define kIOHIDTransportFIFOValue                "FIFO"
#define kIOHIDTransportVirtualValue             "Virtual"
#define kIOHIDTransportInductiveInBandValue     "Inductive In-Band"


#define kIOHIDCategoryAutomotiveValue       "Automotive"

/*!
    @define kIOHIDElementKey
    @abstract Keys that represents an element property.
    @discussion Property for a HID Device or element dictionary.
        Elements can be hierarchical, so they can contain other elements.
*/
#define kIOHIDElementKey                    "Elements"

/*!
    @defined HID Element Dictionary Keys
    @abstract Keys that represent properties of a particular elements.
    @discussion These keys can also be added to a matching dictionary 
        when searching for elements via copyMatchingElements.  
*/
#define kIOHIDElementCookieKey                      "ElementCookie"
#define kIOHIDElementTypeKey                        "Type"
#define kIOHIDElementCollectionTypeKey              "CollectionType"
#define kIOHIDElementUsageKey                       "Usage"
#define kIOHIDElementUsagePageKey                   "UsagePage"
#define kIOHIDElementMinKey                         "Min"
#define kIOHIDElementMaxKey                         "Max"
#define kIOHIDElementScaledMinKey                   "ScaledMin"
#define kIOHIDElementScaledMaxKey                   "ScaledMax"
#define kIOHIDElementSizeKey                        "Size"
#define kIOHIDElementReportSizeKey                  "ReportSize"
#define kIOHIDElementReportCountKey                 "ReportCount"
#define kIOHIDElementReportIDKey                    "ReportID"
#define kIOHIDElementIsArrayKey                     "IsArray"
#define kIOHIDElementIsRelativeKey                  "IsRelative"
#define kIOHIDElementIsWrappingKey                  "IsWrapping"
#define kIOHIDElementIsNonLinearKey                 "IsNonLinear"
#define kIOHIDElementHasPreferredStateKey           "HasPreferredState"
#define kIOHIDElementHasNullStateKey                "HasNullState"
#define kIOHIDElementFlagsKey                       "Flags"
#define kIOHIDElementUnitKey                        "Unit"
#define kIOHIDElementUnitExponentKey                "UnitExponent"
#define kIOHIDElementNameKey                        "Name"
#define kIOHIDElementValueLocationKey               "ValueLocation"
#define kIOHIDElementDuplicateIndexKey              "DuplicateIndex"
#define kIOHIDElementParentCollectionKey            "ParentCollection"
#define kIOHIDElementVariableSizeKey                "VariableSize"

#ifndef __ppc__
    #define kIOHIDElementVendorSpecificKey          "VendorSpecific"
#else
    #define kIOHIDElementVendorSpecificKey          "VendorSpecifc"
#endif

/*!
    @defined HID Element Match Keys
    @abstract Keys used for matching particular elements.
    @discussion These keys should only be used with a matching  
        dictionary when searching for elements via copyMatchingElements.  
*/
#define kIOHIDElementCookieMinKey           "ElementCookieMin"
#define kIOHIDElementCookieMaxKey           "ElementCookieMax"
#define kIOHIDElementUsageMinKey            "UsageMin"
#define kIOHIDElementUsageMaxKey            "UsageMax"

/*!
    @defined kIOHIDElementCalibrationMinKey
    @abstract The minimum bounds for a calibrated value.  
*/
#define kIOHIDElementCalibrationMinKey              "CalibrationMin"

/*!
    @defined kIOHIDElementCalibrationMaxKey
    @abstract The maximum bounds for a calibrated value.  
*/
#define kIOHIDElementCalibrationMaxKey              "CalibrationMax"

/*!
    @defined kIOHIDElementCalibrationSaturationMinKey
    @abstract The minimum tolerance to be used when calibrating a logical element value. 
    @discussion The saturation property is used to allow for slight differences in the minimum and maximum value returned by an element. 
*/
#define kIOHIDElementCalibrationSaturationMinKey    "CalibrationSaturationMin"

/*!
    @defined kIOHIDElementCalibrationSaturationMaxKey
    @abstract The maximum tolerance to be used when calibrating a logical element value.  
    @discussion The saturation property is used to allow for slight differences in the minimum and maximum value returned by an element. 
*/
#define kIOHIDElementCalibrationSaturationMaxKey    "CalibrationSaturationMax"

/*!
    @defined kIOHIDElementCalibrationDeadZoneMinKey
    @abstract The minimum bounds near the midpoint of a logical value in which the value is ignored.  
    @discussion The dead zone property is used to allow for slight differences in the idle value returned by an element. 
*/
#define kIOHIDElementCalibrationDeadZoneMinKey      "CalibrationDeadZoneMin"

/*!
    @defined kIOHIDElementCalibrationDeadZoneMinKey
    @abstract The maximum bounds near the midpoint of a logical value in which the value is ignored.  
    @discussion The dead zone property is used to allow for slight differences in the idle value returned by an element. 
*/
#define kIOHIDElementCalibrationDeadZoneMaxKey      "CalibrationDeadZoneMax"

/*!
    @defined kIOHIDElementCalibrationGranularityKey
    @abstract The scale or level of detail returned in a calibrated element value.  
    @discussion Values are rounded off such that if granularity=0.1, values after calibration are 0, 0.1, 0.2, 0.3, etc.
*/
#define kIOHIDElementCalibrationGranularityKey      "CalibrationGranularity"

/*!
    @defined kIOHIDKeyboardSupportsEscKey
    @abstract Describe if keyboard device supports esc key.
    @discussion Keyboard devices having full HID keyboard descriptor can specify if esc key is actually supported or not. For new macs with TouchBar this is ideal scenario where keyboard descriptor by default specifies presence of esc key but through given property client can check if key is present or not
 */
#define kIOHIDKeyboardSupportsEscKey                 "HIDKeyboardSupportsEscKey"

/*!
    @defined kIOHIDKeyboardSupportsDoNotDisturbKey
    @abstract Describe if keyboard device supports a do not disturb key.
    @discussion Keyboards reporting this usage are capable of triggering the do not disturb mode, it does not guarantee that the keyboard will have a button available to the user to use.
 */
#define kIOHIDKeyboardSupportsDoNotDisturbKey                 "HIDKeyboardSupportsDoNotDisturbKey"

/*!
  @typedef IOHIDOptionsType
  @abstract Options for opening a device via IOHIDLib.
  @constant kIOHIDOptionsTypeNone Default option.
  @constant kIOHIDOptionsTypeSeizeDevice Used to open exclusive
    communication with the device.  This will prevent the system
    and other clients from receiving events from the device.
  @constant kIOHIDOptionsTypeMaskPrivate Mask for reserved internal usage values.
*/
enum {
    kIOHIDOptionsTypeNone     = 0x00,
    kIOHIDOptionsTypeSeizeDevice = 0x01,
    kIOHIDOptionsTypeMaskPrivate = 0xff0000,
};
typedef uint32_t IOHIDOptionsType;


/*!
  @typedef IOHIDQueueOptionsType
  @abstract Options for creating a queue via IOHIDLib.
  @constant kIOHIDQueueOptionsTypeNone Default option.
  @constant kIOHIDQueueOptionsTypeEnqueueAll Force the IOHIDQueue
    to enqueue all events, relative or absolute, regardless of change.
*/
enum {
    kIOHIDQueueOptionsTypeNone              = 0x00,
    kIOHIDQueueOptionsTypeEnqueueAll        = 0x01
};
typedef uint32_t IOHIDQueueOptionsType;

/*!
  @typedef IOHIDStandardType
  @abstract Type to define what industrial standard the device is referencing.
  @constant kIOHIDStandardTypeANSI ANSI.
  @constant kIOHIDStandardTypeISO ISO.
  @constant kIOHIDStandardTypeJIS JIS.
  @constant kIOHIDStandardTypeUnspecified.
*/
enum {
    kIOHIDStandardTypeANSI                = 0x0,
    kIOHIDStandardTypeISO                 = 0x1,
    kIOHIDStandardTypeJIS                 = 0x2,
    kIOHIDStandardTypeUnspecified         = 0xFFFFFFFF,
};
typedef uint32_t IOHIDStandardType;

/*!
  @typedef kIOHIDDigitizerGestureCharacterStateKey
  @abstract Type to define what physical layout the device is referencing.
  @constant kIOHIDKeyboardPhysicalLayoutTypeUnknown Unknown.
  @constant kIOHIDKeyboardPhysicalLayoutType101 ANSI.
  @constant kIOHIDKeyboardPhysicalLayoutType103 Korean.
  @constant kIOHIDKeyboardPhysicalLayoutType102 ISO.
  @constant kIOHIDKeyboardPhysicalLayoutType104 ABNT Brazil.
  @constant kIOHIDKeyboardPhysicalLayoutType106 JIS.
  @constant kIOHIDKeyboardPhysicalLayoutTypeVendor Vendor specific layout.
*/
enum {
    kIOHIDKeyboardPhysicalLayoutTypeUnknown  = 0x0,
    kIOHIDKeyboardPhysicalLayoutType101      = 0x1,
    kIOHIDKeyboardPhysicalLayoutType103      = 0x2,
    kIOHIDKeyboardPhysicalLayoutType102      = 0x3,
    kIOHIDKeyboardPhysicalLayoutType104      = 0x4,
    kIOHIDKeyboardPhysicalLayoutType106      = 0x5,
    kIOHIDKeyboardPhysicalLayoutTypeVendor   = 0x6,
};
typedef uint32_t IOHIDKeyboardPhysicalLayoutType;

#define kIOHIDDigitizerGestureCharacterStateKey "DigitizerCharacterGestureState"

/* 
 * kIOHIDSystemButtonPressedDuringDarkBoot - Used to message that a wake button was pressed during dark boot
 */
#define kIOHIDSystemButtonPressedDuringDarkBoot     iokit_family_msg(sub_iokit_hidsystem, 7)

/*!
 @defined IOHIDKeyboard Keys
 @abstract Keys that represent parameters of keyboards.
 @discussion Legacy IOHIDKeyboard keys, formerly in IOHIDPrivateKeys. See IOHIDServiceKeys.h for the new keys.
 */
#define kIOHIDKeyboardCapsLockDelay         "CapsLockDelay"
#define kIOHIDKeyboardEjectDelay            "EjectDelay"

/*!
    @defined kFnFunctionUsageMapKey
    @abstract top row key remapping for consumer usages
    @discussion string of comma separated uint64_t value representing (usagePage<<32) | usage pairs
 
 */
#define kFnFunctionUsageMapKey      "FnFunctionUsageMap"

/*!
    @defined kFnKeyboardUsageMapKey
    @abstract top row key remapping for consumer usages
    @discussion string of comma separated uint64_t value representing (usagePage<<32) | usage pairs
 
 */
#define kFnKeyboardUsageMapKey      "FnKeyboardUsageMap"

#define kNumLockKeyboardUsageMapKey "NumLockKeyboardUsageMap"

#define kKeyboardUsageMapKey        "KeyboardUsageMap"

/*!
 @defined kIOHIDDeviceOpenedByEventSystemKey
 @abstract Property set when corresponding event service object opened by HID event system
 @discussion boolean value
 
 */
#define  kIOHIDDeviceOpenedByEventSystemKey "DeviceOpenedByEventSystem"

/*!
 * @define kIOHIDDeviceSuspendKey
 *
 * @abstract
 * Boolean property set on a user space IOHIDDeviceRef to suspend report delivery
 * to registered callbacks.
 *
 * @discussion
 * When set to true, the callbacks registered via the following API will not be invoked:
 *     IOHIDDeviceRegisterInputReportCallback
 *     IOHIDDeviceRegisterInputReportWithTimeStampCallback
 *     IOHIDDeviceRegisterInputValueCallback
 * To resume report delivery, this property should be set to false.
 */
#define kIOHIDDeviceSuspendKey              "IOHIDDeviceSuspend"

/*!
 * @define     kIOHIDMaxReportBufferCountKey
 * @abstract   Number property published for an IOHIDDevice that contains the
 *             report buffer count.
 * @discussion IOHIDLibUserClient connections to an IOHIDDevice created
 *             using IOKit/hid/IOHIDDevice.h/IOHIDDeviceCreate have a report
 *             buffer, where reports can be enqueued and dispatched in quick succession.
 *             A report buffer count can be published to help determine the
 *             correct queue size that will be able to handle incoming report
 *             rates. The queue size is determined by report buffer count
 *             multiplied by the report buffer's entry size, this total size is
 *             limited to 131072 bytes. This property can be set in the
 *             IOHIDDevice's IOKit property table, or on the individual
 *             IOHIDLibUserClient connection using IOHIDDeviceSetProperty.
 *             (See kIOHIDReportBufferEntrySizeKey).
 */
#define kIOHIDMaxReportBufferCountKey "MaxReportBufferCount"

/*!
 * @define     kIOHIDReportBufferEntrySizeKey
 * @abstract   Number property published on an IOHIDDevice that contains
 *             the report buffer's entry size.
 * @discussion This key describes the entry size of the reports (in bytes)
 *             in the report buffer between an IOHIDLibUserClient and its
 *             associated IOHIDDevice. The queue size is determined by the
 *             report buffer's report count multiplied by the entry size. The
 *             buffer entry size is currently limited to 8167 bytes, exceeding
 *             this value will result in a minimum queue size. This property
 *             can be set in the IOHIDDevice's IOKit property table, or on the individual
 *             IOHIDLibUserClient connection using IOHIDDeviceSetProperty.
 *             (See kIOHIDMaxReportBufferCountKey).
 */
#define kIOHIDReportBufferEntrySizeKey "ReportBufferEntrySize"

/*!
    @defined    kIOHIDSensorPropertyReportIntervalKey
    @abstract   Property to get or set the Report Interval in us of supported sensor devices
    @discussion Corresponds to kHIDUsage_Snsr_Property_ReportInterval in a sensor device's
                descriptor.
 */
#define kIOHIDSensorPropertyReportIntervalKey   kIOHIDReportIntervalKey

/*!
    @defined    kIOHIDSensorPropertySampleIntervalKey
    @abstract   Property to get or set the Sample Interval in us of supported sensor devices
    @discussion Corresponds to kHIDUsage_Snsr_Property_SamplingRate in a sensor device's
                descriptor.
 */
#define kIOHIDSensorPropertySampleIntervalKey   kIOHIDSampleIntervalKey

/*!
    @defined    kIOHIDSensorPropertyBatchIntervalKey
    @abstract   Property to get or set the Batch Interval / Report Latency in us of supported sensor devices
    @discussion Corresponds to kHIDUsage_Snsr_Property_ReportLatency in a sensor device's
                descriptor.
 */
#define kIOHIDSensorPropertyBatchIntervalKey    kIOHIDBatchIntervalKey

/*!
    @defined    kIOHIDSensorPropertyReportLatencyKey
    @abstract   Alias of kIOHIDSensorPropertyBatchIntervalKey
 */
#define kIOHIDSensorPropertyReportLatencyKey    kIOHIDSensorPropertyBatchIntervalKey

/*!
    @defined    kIOHIDSensorPropertyMaxFIFOEventsKey
    @abstract   Property to get or set the maximum FIFO event queue size of supported sensor devices
    @discussion Corresponds to kHIDUsage_Snsr_Property_MaxFIFOEvents in a sensor device's
                descriptor.
 */
#define kIOHIDSensorPropertyMaxFIFOEventsKey    "MaxFIFOEvents"

/*!
   @defined    kIOHIDDigitizerSurfaceSwitchKey
   @abstract   Property to turn on / of surface digitizer contact reporting
   @discussion To allow for better power management, a host may wish to indicate what it would like a touchpad digitizer to not report surface digitizer contacts by clearing this
                flag. By default, upon cold‐boot/power cycle, touchpads that support reporting surface
                contacts shall do so by default.
*/

#define kIOHIDDigitizerSurfaceSwitchKey "DigitizerSurfaceSwitch"

/*!
     @defined    kIOHIDKeyboardLayoutValueKey
     @abstract   Property to report the value read from the device used to determine the keyboard layout
     @discussion Property value if set represents the raw value recieved from the device.
                    Supported usages and their value's meaning:
                        * Usage: kHIDPage_Consumer/kHIDUsage_Csmr_KeyboardPhysicalLayout
                            - 0: Unknown Layout - kIOHIDStandardTypeUnspecified
                            - 1: 101 (e.g. US) - kIOHIDStandardTypeANSI
                            - 2: 103 (Korea) - kIOHIDStandardTypeUnspecified
                            - 3: 102 (e.g. German) - kIOHIDStandardTypeISO
                            - 4: 104 (e.g. ABNT Brazil) - kIOHIDStandardTypeUnspecified
                            - 5: 106 (DOS/V Japan) - kIOHIDStandardTypeJIS
                            - 6: Vendor-specific - kIOHIDStandardTypeUnspecified
 */
#define kIOHIDKeyboardLayoutValueKey "HIDKeyboardLayoutValue"

/*!
     @defined    kIOHIDPointerAccelerationAlgorithmKey
     @abstract   Property to determine if the pointer acceleration algorithm should be overridden.
     @discussion Property value if set represents desired acceleration algorithm for pointer events.
                 See kIOHIDAccelerationAlgorithmType for supported values.
 */
#define kIOHIDPointerAccelerationAlgorithmKey "HIDPointerAccelerationAlgorithm"

/*!
     @defined    kIOHIDScrollAccelerationAlgorithmKey
     @abstract   Property to determine if the scroll acceleration algorithm should be overridden.
     @discussion Property value if set represents desired acceleration algorithm for scroll events.
                 See kIOHIDAccelerationAlgorithmType for supported values.
 */
#define kIOHIDScrollAccelerationAlgorithmKey  "HIDScrollAccelerationAlgorithm"


/*!
  @typedef IOHIDAccelerationAlgorithmType
  @abstract Type to define what acceleration algorithm should be used.
  @constant kIOHIDAccelerationAlgorithmTypeTable Apple Acceleration Tables, not recommended.
  @constant kIOHIDAccelerationAlgorithmTypeParametric Acceleration Curves, defined by a set of points.
  @constant kIOHIDAccelerationAlgorithmTypeDefault Use the default acceleration algorithm resolution.
*/
enum {
    kIOHIDAccelerationAlgorithmTypeTable,
    kIOHIDAccelerationAlgorithmTypeParametric,
    kIOHIDAccelerationAlgorithmTypeDefault,
};
typedef uint8_t IOHIDAccelerationAlgorithmType;


/*!
     @defined    kIOHIDPointerAccelerationMinimumKey
     @abstract   Property set the minimum pointer acceleration when linear acceleration is used.
     @discussion Property value is expected to be in 16.16 fixed point floating number when sent to
                 clients and converted as needed.
 */
#define kIOHIDPointerAccelerationMinimumKey  "HIDPointerAccelerationMinimum"

/*!
 * @define kIOHIDPrimaryTrackpadCanBeDisabledKey
 * @abstract
 * Data property that determines whether primary trackpad can be disabled.
 */
#define kIOHIDPrimaryTrackpadCanBeDisabledKey "PrimaryTrackpadCanBeDisabled"

/*!
     @defined    kIOHIDKeyboardFunctionKeyCountKey
     @abstract   Property which provides the number of available function keys
     @discussion For keyboards with a function key row, the number of available function keys will likely need to be 
                    published within the system for consumers to enable functionality that is  dependent on the
                    number of available keys.
 */
#define kIOHIDKeyboardFunctionKeyCountKey "HIDKeyboardFunctionKeyCount"

__END_DECLS

#endif /* !_IOKIT_HID_IOHIDKEYS_H_ */

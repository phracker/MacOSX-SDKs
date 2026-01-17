/*
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
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

__BEGIN_DECLS

/* The following keys are used to search the IORegistry for HID related services
*/

/* This is used to find HID Devices in the IORegistry */
#define kIOHIDDeviceKey                     "IOHIDDevice"

/*!
    @defined HID Device Property Keys
    @abstract Keys that represent properties of a paticular device.
    @discussion Keys that represent properties of a paticular device.  Can be added
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
        An application intersted in only matching on one criteria would only add the 
        kIOHIDDeviceUsageKey and kIOHIDDeviceUsagePageKey keys to the matching dictionary.
        If it is interested in a device that has multiple behaviors, the application would
        instead add an array or dictionaries referenced by kIOHIDDeviceUsagePairsKey to his 
        matching dictionary.
*/
#define kIOHIDTransportKey                  "Transport"
#define kIOHIDVendorIDKey                   "VendorID"
#define kIOHIDVendorIDSourceKey             "VendorIDSource"
#define kIOHIDProductIDKey                  "ProductID"
#define kIOHIDVersionNumberKey              "VersionNumber"
#define kIOHIDManufacturerKey               "Manufacturer"
#define kIOHIDProductKey                    "Product"
#define kIOHIDSerialNumberKey               "SerialNumber"
#define kIOHIDCountryCodeKey                "CountryCode"
#define kIOHIDStandardTypeKey               "StandardType"
#define kIOHIDLocationIDKey                 "LocationID"
#define kIOHIDDeviceUsageKey                "DeviceUsage"
#define kIOHIDDeviceUsagePageKey            "DeviceUsagePage"
#define kIOHIDDeviceUsagePairsKey           "DeviceUsagePairs"
#define kIOHIDPrimaryUsageKey               "PrimaryUsage"
#define kIOHIDPrimaryUsagePageKey           "PrimaryUsagePage"
#define kIOHIDMaxInputReportSizeKey         "MaxInputReportSize"
#define kIOHIDMaxOutputReportSizeKey        "MaxOutputReportSize"
#define kIOHIDMaxFeatureReportSizeKey       "MaxFeatureReportSize"
#define kIOHIDReportIntervalKey             "ReportInterval"
#define kIOHIDSampleIntervalKey             "SampleInterval"
#define kIOHIDReportDescriptorKey           "ReportDescriptor"
#define kIOHIDResetKey                      "Reset"
#define kIOHIDKeyboardLanguageKey           "KeyboardLanguage"
#define kIOHIDAltHandlerIdKey               "alt_handler_id"
#define kIOHIDBuiltInKey                    "Built-In"
#define kIOHIDDisplayIntegratedKey          "DisplayIntegrated"
#define kIOHIDProductIDMaskKey				"ProductIDMask"
#define kIOHIDProductIDArrayKey				"ProductIDArray"
#define kIOHIDPowerOnDelayNSKey             "HIDPowerOnDelayNS"

/*!
    @define kIOHIDElementKey
    @abstract Keys that represents an element property.
    @discussion Property for a HID Device or element dictionary.
        Elements can be heirarchical, so they can contain other elements.
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
    @abstract The mininum tolerance to be used when calibrating a logical element value. 
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
    @typedef IOHIDElementCookie
    @abstract Abstract data type used as a unique identifier for an element.
*/
#ifdef __LP64__
    typedef uint32_t IOHIDElementCookie;
#else
    typedef void * IOHIDElementCookie;
#endif

/*!
  @typedef IOHIDElementType
  @abstract Describes different types of HID elements.
  @discussion Used by the IOHIDFamily to identify the type of
  element processed.  Represented by the key kIOHIDElementTypeKey in the 
    dictionary describing the element.
  @constant kIOHIDElementTypeInput_Misc
    Misc input data field or varying size.
  @constant kIOHIDElementTypeInput_Button 
    One bit input data field.
  @constant kIOHIDElementTypeInput_Axis 
    Input data field used to represent an axis.
  @constant kIOHIDElementTypeInput_ScanCodes
    Input data field used to represent a scan code or usage selector.
  @constant kIOHIDElementTypeOutput
    Used to represent an output data field in a report.
  @constant kIOHIDElementTypeFeature
    Describes input and output elements not intended for 
    consumption by the end user.
  @constant kIOHIDElementTypeCollection
    Element used to identify a relationship between two or more elements.
*/
enum IOHIDElementType {
	kIOHIDElementTypeInput_Misc        = 1,
	kIOHIDElementTypeInput_Button      = 2,
	kIOHIDElementTypeInput_Axis        = 3,
	kIOHIDElementTypeInput_ScanCodes   = 4,
	kIOHIDElementTypeOutput            = 129,
	kIOHIDElementTypeFeature           = 257,
	kIOHIDElementTypeCollection        = 513
};
typedef enum IOHIDElementType IOHIDElementType;

/*!
  @typedef IOHIDElementCollectionType
  @abstract Describes different types of HID collections.
  @discussion Collections identify a relationship between two or more
    elements.
  @constant kIOHIDElementCollectionTypePhysical   
    Used for a set of data items that represent data points 
    collected at one geometric point.
  @constant kIOHIDElementCollectionTypeApplication 
    Identifies item groups serving different purposes in a single device.
  @constant kIOHIDElementCollectionTypeLogical
    Used when a set of data items form a composite data structure.
  @constant kIOHIDElementCollectionTypeReport 
    Wraps all the fields in a report.
  @constant kIOHIDElementCollectionTypeNamedArray 
    Contains an array of selector usages.
  @constant kIOHIDElementCollectionTypeUsageSwitch 
    Modifies the meaning of the usage it contains.
  @constant kIOHIDElementCollectionTypeUsageModifier 
    Modifies the meaning of the usage attached to the encompassing collection.
*/
enum IOHIDElementCollectionType{
	kIOHIDElementCollectionTypePhysical	= 0x00,
	kIOHIDElementCollectionTypeApplication,
    kIOHIDElementCollectionTypeLogical,
    kIOHIDElementCollectionTypeReport,
    kIOHIDElementCollectionTypeNamedArray,
    kIOHIDElementCollectionTypeUsageSwitch,
    kIOHIDElementCollectionTypeUsageModifier
};
typedef enum IOHIDElementCollectionType IOHIDElementCollectionType;


/*!
  @typedef IOHIDReportType
  @abstract Describes different type of HID reports.
  @discussion Used by the IOHIDFamily to identify the type of
    report being processed.
  @constant kIOHIDReportTypeInput Input report.
  @constant kIOHIDReportTypeOutput Output report.
  @constant kIOHIDReportTypeFeature Feature report.
*/
enum IOHIDReportType{
    kIOHIDReportTypeInput = 0,
    kIOHIDReportTypeOutput,
    kIOHIDReportTypeFeature,
    kIOHIDReportTypeCount
};
typedef enum IOHIDReportType IOHIDReportType;

/*!
  @typedef IOHIDOptionsType
  @abstract Options for opening a device via IOHIDLib.
  @constant kIOHIDOptionsTypeNone Default option.
  @constant kIOHIDOptionsTypeSeizeDevice Used to open exclusive
    communication with the device.  This will prevent the system
    and other clients from receiving events from the device.
*/
enum {
    kIOHIDOptionsTypeNone	 = 0x00,
    kIOHIDOptionsTypeSeizeDevice = 0x01
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
    kIOHIDQueueOptionsTypeNone	 = 0x00,
    kIOHIDQueueOptionsTypeEnqueueAll = 0x01
};
typedef uint32_t IOHIDQueueOptionsType;


enum {
    kIOHIDElementFlagsConstantMask        = 0x0001,
    kIOHIDElementFlagsVariableMask        = 0x0002,
    kIOHIDElementFlagsRelativeMask        = 0x0004,
    kIOHIDElementFlagsWrapMask            = 0x0008,
    kIOHIDElementFlagsNonLinearMask       = 0x0010,
    kIOHIDElementFlagsNoPreferredMask     = 0x0020,
    kIOHIDElementFlagsNullStateMask       = 0x0040,
    kIOHIDElementFlagsVolativeMask        = 0x0080,
    kIOHIDElementFlagsBufferedByteMask    = 0x0100
};
typedef uint32_t IOHIDElementFlags;

/*!
  @typedef IOHIDStandardType
  @abstract Type to define what industrial standard the device is referencing.
  @constant kIOHIDStandardTypeANSI ANSI.
  @constant kIOHIDStandardTypeISO ISO.
  @constant kIOHIDStandardTypeJIS JIS.
*/
enum {
    kIOHIDStandardTypeANSI                = 0,
    kIOHIDStandardTypeISO                 = 1,
    kIOHIDStandardTypeJIS                 = 2
};
typedef uint32_t IOHIDStandardType;

/*!
 @typedef IOHIDValueScaleType
 @abstract Describes different types of scaling that can be performed on element values.
 @constant kIOHIDValueScaleTypeCalibrated Type for value that is scaled with respect to the calibration properties.
 @constant kIOHIDValueScaleTypePhysical Type for value that is scaled with respect to the physical min and physical max of the element.
 */
enum {
    kIOHIDValueScaleTypeCalibrated,
    kIOHIDValueScaleTypePhysical
};
typedef uint32_t IOHIDValueScaleType;

/*!
 @typedef IOHIDValueOptions
 @abstract Describes options for gathering element values.
 @constant kIOHIDValueOptionsFlagSimpleRelative Compares against previous value
 */
enum {
    kIOHIDValueOptionsFlagRelativeSimple = (1<<0)
};
typedef uint32_t IOHIDValueOptions;



__END_DECLS

#endif /* !_IOKIT_HID_IOHIDKEYS_H_ */

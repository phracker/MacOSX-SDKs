/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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

#ifndef _IOKIT_HID_IOHIDKEYS_H_
#define _IOKIT_HID_IOHIDKEYS_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

/* The following keys are used to search the IORegistry for HID related services
*/

/* This is used to find HID Devices in the IORegistry */
#define kIOHIDDeviceKey                     "IOHIDDevice"

/* These are properties for a HID Device */
#define kIOHIDTransportKey                  "Transport"
#define kIOHIDVendorIDKey                   "VendorID"
#define kIOHIDProductIDKey                  "ProductID"
#define kIOHIDVersionNumberKey              "VersionNumber"
#define kIOHIDManufacturerKey               "Manufacturer"
#define kIOHIDProductKey                    "Product"
#define kIOHIDSerialNumberKey               "SerialNumber"
#define kIOHIDLocationIDKey                 "LocationID"
#define kIOHIDPrimaryUsageKey               "PrimaryUsage"
#define kIOHIDPrimaryUsagePageKey           "PrimaryUsagePage"

/* These are properties for a HID Device or element dictionaries */
/* Elements can be heirarchical, so they can contain other elements */
#define kIOHIDElementKey                    "Elements"

/* These are properties for an element dictionary */
#define kIOHIDElementCookieKey              "ElementCookie"
#define kIOHIDElementTypeKey                "Type"
#define kIOHIDElementCollectionTypeKey      "CollectionType"
#define kIOHIDElementUsageKey               "Usage"
#define kIOHIDElementUsagePageKey           "UsagePage"
#define kIOHIDElementMinKey                 "Min"
#define kIOHIDElementMaxKey                 "Max"
#define kIOHIDElementScaledMinKey           "ScaledMin"
#define kIOHIDElementScaledMaxKey           "ScaledMax"
#define kIOHIDElementSizeKey                "Size"
#define kIOHIDElementIsRelativeKey          "IsRelative"
#define kIOHIDElementIsWrappingKey          "IsWrapping"
#define kIOHIDElementIsNonLinearKey         "IsNonLinear"
#define kIOHIDElementHasPreferredStateKey   "HasPreferredState"
#define kIOHIDElementHasNullStateKey        "HasNullState"
#define kIOHIDElementVendorSpecificKey      "VendorSpecifc"
#define kIOHIDElementUnitKey                "Unit"
#define kIOHIDElementUnitExponentKey        "UnitExponent"
#define kIOHIDElementNameKey                "Name"
#define kIOHIDElementValueLocationKey       "ValueLocation"

typedef void * IOHIDElementCookie;

enum IOHIDElementType
{
	kIOHIDElementTypeInput_Misc        = 1,
	kIOHIDElementTypeInput_Button      = 2,
	kIOHIDElementTypeInput_Axis        = 3,
	kIOHIDElementTypeInput_ScanCodes   = 4,
	kIOHIDElementTypeOutput            = 129,
	kIOHIDElementTypeFeature           = 257,
	kIOHIDElementTypeCollection        = 513
};
typedef enum IOHIDElementType IOHIDElementType;

enum IOHIDReportType
{
    kIOHIDReportTypeInput = 0,
    kIOHIDReportTypeOutput,
    kIOHIDReportTypeFeature,
    kIOHIDReportTypeCount
};
typedef enum IOHIDReportType IOHIDReportType;

__END_DECLS

#endif /* !_IOKIT_HID_IOHIDKEYS_H_ */

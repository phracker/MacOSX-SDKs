/*
 * Copyright (c) 1998-2001 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.2 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.  
 * Please see the License for the specific language governing rights and 
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * Constants that both OS9 and OSX want to define, and whose values are
 * specified by the USB Standard.
 * Put in a seperate file so they can be included if the OS9 include file isn't already
 * included.
*/
#ifndef _USBSPEC_H
#define _USBSPEC_H

#ifdef __cplusplus
extern "C" {
#endif

enum {
	kUSBControl		= 0,
	kUSBIsoc		= 1,
	kUSBBulk		= 2,
	kUSBInterrupt		= 3,
	kUSBAnyType		= 0xFF
};

/* endpoint type */

enum {
	kUSBOut			= 0,
	kUSBIn			= 1,
	kUSBNone		= 2,
	kUSBAnyDirn		= 3
};

/*USBDirection*/

enum {
	kUSBStandard		= 0,
	kUSBClass		= 1,
	kUSBVendor		= 2
};

/*USBRqType*/

enum {
	kUSBDevice		= 0,
	kUSBInterface		= 1,
	kUSBEndpoint		= 2,
	kUSBOther		= 3
};

/*USBRqRecipient*/

enum {
	kUSBRqGetStatus		= 0,
	kUSBRqClearFeature	= 1,
	kUSBRqGetState		= 2,
	kUSBRqSetFeature	= 3,
	kUSBRqReserved2		= 4,
	kUSBRqSetAddress	= 5,
	kUSBRqGetDescriptor	= 6,
	kUSBRqSetDescriptor	= 7,
	kUSBRqGetConfig		= 8,
	kUSBRqSetConfig		= 9,
	kUSBRqGetInterface	= 10,
	kUSBRqSetInterface	= 11,
	kUSBRqSyncFrame		= 12
};

/*USBRequest*/


enum {
        kUSBAnyDesc		= 0,	// Wildcard for searches
	kUSBDeviceDesc		= 1,
	kUSBConfDesc		= 2,
	kUSBStringDesc		= 3,
	kUSBInterfaceDesc	= 4,
	kUSBEndpointDesc	= 5,
	kUSBHIDDesc		= 0x21,
	kUSBReportDesc		= 0x22,
	kUSBPhysicalDesc	= 0x23,
	kUSBHUBDesc		= 0x29
};

// feature selectors
enum {
        kUSBFeatureEndpointStall = 0,
        kUSBFeatureDeviceRemoteWakeup = 1
}; 

/* descriptorType */

enum {
	kUSB100mAAvailable	= 50,
	kUSB500mAAvailable	= 250,
	kUSB100mA		= 50,
	kUSBAtrBusPowered	= 0x80,
	kUSBAtrSelfPowered	= 0x40,
	kUSBAtrRemoteWakeup	= 0x20
};


enum {
	kUSBRel10		= 0x0100
};


enum {
    kHIDRqGetReport		= 1,
    kHIDRqGetIdle		= 2,
    kHIDRqGetProtocol		= 3,
    kHIDRqSetReport		= 9,
    kHIDRqSetIdle		= 10,
    kHIDRqSetProtocol		= 11
};


enum {
    kHIDRtInputReport		= 1,
    kHIDRtOutputReport		= 2,
    kHIDRtFeatureReport		= 3
};


enum {
    kHIDBootProtocolValue	= 0,
    kHIDReportProtocolValue	= 1
};


enum {
    kHIDKeyboardInterfaceProtocol = 1,
    kHIDMouseInterfaceProtocol	= 2
};


enum {
    kUSBCapsLockKey		= 0x39,
    kUSBNumLockKey		= 0x53,
    kUSBScrollLockKey		= 0x47
};

/* deviceClass */

enum {
    kUSBCompositeClass          = 0,
    kUSBAudioClass              = 1,
    kUSBCommClass               = 2,
    kUSBHIDClass                = 3,
    kUSBDisplayClass            = 4,
    kUSBPrintingClass           = 7,
    kUSBMassStorageClass        = 8,
    kUSBHubClass                = 9,
    kUSBDataClass               = 10,
    kUSBVendorSpecificClass     = 0xFF
};

/* deviceSubClass */

enum {
    kUSBCompositeSubClass       = 0,
    kUSBHubSubClass             = 0
};

// USB property names taken from the field names in various descriptors

// device descriptor
#define kUSBDeviceClass			"bDeviceClass"
#define kUSBDeviceSubClass		"bDeviceSubClass"
#define kUSBDeviceProtocol		"bDeviceProtocol"
#define kUSBDeviceMaxPacketSize		"bMaxPacketSize0"
#define kUSBVendorID			"idVendor"		// good name
#define kUSBVendorName			kUSBVendorID		// bad name - keep for backward compatibility
#define kUSBProductID			"idProduct"		// good name
#define kUSBProductName			kUSBProductID		// bad name - keep for backward compatibility
#define kUSBDeviceReleaseNumber		"bcdDevice"
#define kUSBManufacturerStringIndex	"iManufacturer"
#define kUSBProductStringIndex		"iProduct"
#define kUSBSerialNumberStringIndex	"iSerialNumber"
#define kUSBDeviceNumConfigs		"bNumConfigurations"

// interface descriptor
#define kUSBInterfaceNumber		"bInterfaceNumber"
#define kUSBAlternateSetting		"bAlternateSetting"
#define kUSBNumEndpoints		"bNumEndpoints"
#define kUSBInterfaceClass		"bInterfaceClass"
#define kUSBInterfaceSubClass		"bInterfaceSubClass"
#define kUSBInterfaceProtocol		"bInterfaceProtocol"
#define kUSBInterfaceStringIndex	"iInterface"

// from the config descriptor
#define kUSBConfigurationValue		"bConfigurationValue"

#ifdef __cplusplus
}       
#endif

#endif /* _USBSPEC_H */

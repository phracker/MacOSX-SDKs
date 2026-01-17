/*
 * Copyright (c) 1998-2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
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

#ifndef _USBHUB_H
#define _USBHUB_H

#include <IOKit/usb/USB.h>
#include <IOKit/usb/USBSpec.h>

    /*!
    @header     USBHub.h
     @abstract  Constants and definitions used with Hub devices.
     @discussion    
     */

    /*!
    @enum Hub Descriptor Type
    @discussion
    */
enum {
    kUSBHubDescriptorType       = 0x29
};

    /*!
    @enum HubFeatures
    @discussion Used with SET_FEATURE to set hub and port features
    */
enum {
                            
    kUSBHubLocalPowerChangeFeature      = 0,    /* Hub features */
    kUSBHubOverCurrentChangeFeature     = 1,

    kUSBHubPortConnectionFeature        = 0,    /* port features */
    kUSBHubPortEnableFeature            = 1,
    kUSBHubPortSuspendFeature           = 2,
    kUSBHubPortOverCurrentFeature       = 3,
    kUSBHubPortResetFeature             = 4,
    kUSBHubPortPowerFeature             = 8,
    kUSBHubPortLowSpeedFeature          = 9,
    kUSBHubPortConnectionChangeFeature  = 16,
    kUSBHubPortEnableChangeFeature      = 17,
    kUSBHubPortSuspendChangeFeature     = 18,
    kUSBHubPortOverCurrentChangeFeature = 19,
    kUSBHubPortResetChangeFeature       = 20,
    kUSBHubPortTestFeature				= 21,
	kUSBHubPortIndicatorFeature			= 22
};

    /*!
    @enum HubPortStatus
    @discussion Used to decode the Port Status and Change 
    */
enum {
    kHubPortConnection		= 0x0001,
    kHubPortEnabled		= 0x0002,
    kHubPortSuspend		= 0x0004,
    kHubPortOverCurrent		= 0x0008,
    kHubPortBeingReset		= 0x0010,
    kHubPortPower		= 0x0100,
    kHubPortLowSpeed		= 0x0200,
    kHubPortHighSpeed		= 0x0400,
    kHubPortTestMode		= 0x0800,
    kHubPortIndicator		= 0x1000,

    // these are the bits which cause the hub port state machine to keep moving
    kHubPortStateChangeMask		= kHubPortConnection | kHubPortEnabled | kHubPortSuspend | kHubPortOverCurrent | kHubPortBeingReset
};


    /*!
    @enum HubStatus
    @discussion Used to decode the Hub Status and Change 
    */
enum {
    kHubLocalPowerStatus        = 1,
    kHubOverCurrentIndicator    = 2,
    kHubLocalPowerStatusChange  = 1,
    kHubOverCurrentIndicatorChange  = 2
};

    /*!
    @enum HubCharacteristics
    @discussion 
    */
enum {
    kPerPortSwitchingBit    = (1 << 0),
    kNoPowerSwitchingBit    = (1 << 1),
    kCompoundDeviceBit      = (1 << 2),
    kPerPortOverCurrentBit  = (1 << 3),
    kNoOverCurrentBit       = (1 << 4),
	
	kHubPortIndicatorBit	= 7,
	kHubPortIndicatorMask	= 0x0080
};

/*!
@enum PowerSwitching
 @discussion 
 */
enum {
	kHubSupportsGangPower	= 0,
	kHubSupportsIndividualPortPower = 1,
	kHubPortSetPowerOff		= 0,
	kHubPortSetPowerOn		= 1
};

/*!
@enum PortIndicatorSelectors
 @discussion 
 */
enum {
	kHubPortIndicatorAutomatic	= 0,
	kHubPortIndicatorAmber,
	kHubPortIndicatorGreen,
	kHubPortIndicatorOff
};


/*!
@enum Hub Device Requests
@discussion  Encoding of the hub specific standard requests
<tt>
<pre><b>
Request          bmRequestType bRequest       wValue  wIndex wLength Data</b>
ClearHubFeature  0010 0000B    CLEAR_FEATURE  Feature Zero    Zero   None
ClearPortFeature 0010 0011B                   Feature Port    Zero   None

GetBusState      1010 0011B    GET_STATE      Zero    Port    One    Port Bus State

GetHubDescriptor 1010 0000B    GET_DESCRIPTOR Type    Zero    Length Descriptor

GetHubStatus     1010 0000B    GET_STATUS     Zero    Zero    Four   Hub Status
GetPortStatus    1010 0011B                   Zero    Port    Four   Port Status

SetHubDescriptor 0010 0000B    SET_DESCRIPTOR Type    Zero    Length Descriptor

SetHubFeature    0010 0000B    SET_FEATURE    Feature Zero    Zero   None
SetPortFeature   0010 0011B                   Feature Port    Zero   None
</pre>
</tt>
    */
enum {
    kClearHubFeature  = EncodeRequest(kUSBRqClearFeature,  kUSBOut, kUSBClass, kUSBDevice),
    kClearPortFeature = EncodeRequest(kUSBRqClearFeature,  kUSBOut, kUSBClass, kUSBOther),
    kGetPortState     = EncodeRequest(kUSBRqGetState,      kUSBIn,  kUSBClass, kUSBOther),
    kGetHubDescriptor = EncodeRequest(kUSBRqGetDescriptor, kUSBIn,  kUSBClass, kUSBDevice),
    kGetHubStatus     = EncodeRequest(kUSBRqGetStatus,     kUSBIn,  kUSBClass, kUSBDevice),
    kGetPortStatus    = EncodeRequest(kUSBRqGetStatus,     kUSBIn,  kUSBClass, kUSBOther),
    kSetHubDescriptor = EncodeRequest(kUSBRqGetDescriptor, kUSBOut, kUSBClass, kUSBDevice),
    kSetHubFeature    = EncodeRequest(kUSBRqSetFeature,    kUSBOut, kUSBClass, kUSBDevice),
    kSetPortFeature   = EncodeRequest(kUSBRqSetFeature,    kUSBOut, kUSBClass, kUSBOther)
};


/*!
    @typedef IOUSBHubDescriptor
    @discussion USB Hub Descriptor.  See the USB HID Specification at <a href="http://www.usb.org"TARGET="_blank">http://www.usb.org</a>.
*/
struct IOUSBHubDescriptor {
    UInt8   length;
    UInt8   hubType;
    UInt8   numPorts;
    UInt16  characteristics __attribute__((packed));
    UInt8   powerOnToGood;  /* Port settling time, in 2ms */
    UInt8   hubCurrent;
    /* These are received packed, will have to be unpacked */
    UInt8   removablePortFlags[8];
    UInt8   pwrCtlPortFlags[8];
};

typedef struct IOUSBHubDescriptor IOUSBHubDescriptor;

/*!
    @typedef IOUSBHubStatus
    @discussion Used to get the port status and change flags using GetPortStatus()
*/
struct IOUSBHubStatus {
    UInt16          statusFlags;
    UInt16          changeFlags;
};
typedef struct IOUSBHubStatus   IOUSBHubStatus;
typedef IOUSBHubStatus *    IOUSBHubStatusPtr;

typedef struct IOUSBHubStatus   IOUSBHubPortStatus;


/*!
    @typedef IOUSBHubPortReEnumerateParam
    @discussion Used to specify the port that needs to be reenumerated
*/
typedef struct IOUSBHubPortReEnumerateParam IOUSBHubPortReEnumerateParam;

struct IOUSBHubPortReEnumerateParam {
    UInt32   portNumber;
    UInt32   options;
};

typedef struct IOUSBHubPortClearTTParam IOUSBHubPortClearTTParam;

struct IOUSBHubPortClearTTParam {
    UInt32	 portNumber;
    UInt32	 options;
#if 0
    UInt8 	 deviceAddress;  <<0
	UInt8	 endpointNum;    <<8
	UInt8 	 endpointType;	 <<16 // As split transaction. 00 Control, 10 Bulk
	UInt8 	 IN;		 <<24 // Direction, 1 = IN, 0 = OUT
#endif
};

#endif /* _USBHUB_H */

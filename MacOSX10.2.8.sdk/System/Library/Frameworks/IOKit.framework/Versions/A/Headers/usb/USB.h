/*
 * Copyright (c) 1998-2002 Apple Computer, Inc. All rights reserved.
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
#ifndef _USB_H
#define _USB_H

#if KERNEL
#include <libkern/OSByteOrder.h>
#include <IOKit/IOMemoryDescriptor.h>
#else
#include <architecture/byte_order.h>
#endif

#include <IOKit/IOTypes.h>

#if !defined(__USB__)
#    include <IOKit/usb/USBSpec.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if KERNEL
#define USBToHostWord OSSwapLittleToHostInt16
#define HostToUSBWord OSSwapHostToLittleInt16
#define USBToHostLong OSSwapLittleToHostInt32
#define HostToUSBLong OSSwapHostToLittleInt32
#else
#define USBToHostWord NXSwapLittleShortToHost
#define HostToUSBWord NXSwapHostShortToLittle
#define USBToHostLong NXSwapLittleLongToHost
#define HostToUSBLong NXSwapHostLongToLittle
#endif

enum {
    kUSBDeviceIDShift = 7,
    kUSBMaxDevices = 128,
    kUSBMaxDevice = kUSBMaxDevices-1,
    kUSBDeviceIDMask = 0x7f,

    kUSBPipeIDMask = 0xf,
    kUSBMaxPipes = 32,	// In and Out pipes can have same pipe number.

    kUSBInterfaceIDShift = 8,
    kUSBMaxInterfaces = 1 << kUSBInterfaceIDShift,
    kUSBInterfaceIDMask = kUSBMaxInterfaces-1,

    kUSBEndPtShift = 7,
    kUSBDeviceMask = ((1 << kUSBEndPtShift) -1),

    kUSBNoPipeIdx = -1
};

enum {
    kUSBRqDirnShift = 7,
    kUSBRqDirnMask = 1,

    kUSBRqTypeShift = 5,
    kUSBRqTypeMask = 3,

    kUSBRqRecipientMask = 0X1F
};

#define USBmakebmRequestType(direction, type, recipient)		\
    ((direction & kUSBRqDirnMask) << kUSBRqDirnShift) |			\
    ((type & kUSBRqTypeMask) << kUSBRqTypeShift) |			\
    (recipient & kUSBRqRecipientMask)

enum {
    kUSBMaxIsocFrameReqCount = 1023 // max size (bytes) of any one Isoc frame
};

#define EncodeRequest(request, direction, type, recipient)		\
    (((UInt16)request << 8) +	    					\
              ((UInt16)recipient +					\
                        ((UInt16)type << kUSBRqTypeShift) +		\
                        ((UInt16)direction << kUSBRqDirnShift)))


enum {
/*
Standard Requests

bmRequestType bRequest      wValue  wIndex    wLength Data
00000000B CLEAR_FEATURE     Feature Zero       Zero   None (device)
00000001B                   Feature Interface  Zero   None (Interface)
00000010B                   Feature Endpoint   Zero   None (Endpoint)

10000000B GET_CONFIGURATION Zero    Zero       One    Configuration
10000000B GET_DESCRIPTOR    Type    LangID     Length Descriptor
10000001B GET_INTERFACE     Zero    Interface  One    Alternate

10000000B GET_STATUS        Zero    Zero       Two    status (device)
10000001B                   Zero    Interface  Two    status (Interface)
10000010B                   Zero    Endpoint   Two    status (Endpoint)

00000000B SET_ADDRESS       Address Zero       Zero   None
00000000B SET_CONFIGURATION Configuration Zero Zero   None
00000000B SET_DESCRIPTOR    Type   LangID      Length Descriptor

00000000B SET_FEATURE       Feature Zero       Zero   None (device)
00000001B                   Feature Interface  Zero   None (Interface)
00000010B                   Feature Endpoint   Zero   None (Endpoint)

00000001B SET_INTERFACE   Alternate Interface  Zero   None
10000010B SYNCH_FRAME       Zero    Endpoint   Two    Frame Number
*/
kClearDeviceFeature
    = EncodeRequest(kUSBRqClearFeature,  kUSBOut, kUSBStandard, kUSBDevice),
kClearInterfaceFeature
    = EncodeRequest(kUSBRqClearFeature,  kUSBOut, kUSBStandard, kUSBInterface),
kClearEndpointFeature
    = EncodeRequest(kUSBRqClearFeature,  kUSBOut, kUSBStandard, kUSBEndpoint),
kGetConfiguration
    = EncodeRequest(kUSBRqGetConfig,     kUSBIn,  kUSBStandard, kUSBDevice),
kGetDescriptor
    = EncodeRequest(kUSBRqGetDescriptor, kUSBIn,  kUSBStandard, kUSBDevice),
kGetInterface
    = EncodeRequest(kUSBRqGetInterface,  kUSBIn,  kUSBStandard, kUSBInterface),
kGetDeviceStatus
    = EncodeRequest(kUSBRqGetStatus,     kUSBIn,  kUSBStandard, kUSBDevice),
kGetInterfaceStatus
    = EncodeRequest(kUSBRqGetStatus,     kUSBIn,  kUSBStandard, kUSBInterface),
kGetEndpointStatus
    = EncodeRequest(kUSBRqGetStatus,     kUSBIn,  kUSBStandard, kUSBEndpoint),
kSetAddress
    = EncodeRequest(kUSBRqSetAddress,    kUSBOut, kUSBStandard, kUSBDevice),
kSetConfiguration
    = EncodeRequest(kUSBRqSetConfig,     kUSBOut, kUSBStandard, kUSBDevice),
kSetDescriptor
    = EncodeRequest(kUSBRqSetDescriptor, kUSBOut, kUSBStandard, kUSBDevice),
kSetDeviceFeature
    = EncodeRequest(kUSBRqSetFeature,    kUSBOut, kUSBStandard, kUSBDevice),
kSetInterfaceFeature
    = EncodeRequest(kUSBRqSetFeature,    kUSBOut, kUSBStandard, kUSBInterface),
kSetEndpointFeature
    = EncodeRequest(kUSBRqSetFeature,    kUSBOut, kUSBStandard, kUSBEndpoint),
kSetInterface
    = EncodeRequest(kUSBRqSetInterface,  kUSBOut, kUSBStandard, kUSBInterface),
kSyncFrame
    = EncodeRequest(kUSBRqSyncFrame,     kUSBIn,  kUSBStandard, kUSBEndpoint),

};

// TYPES

typedef UInt16 USBDeviceAddress;


/*!
    @typedef IOUSBIsocFrame
    Structure used to encode information about each isoc frame
    @param frStatus Returns status associated with the frame
    @param frReqCount Input specifiying how many bytes to read or write
    @param frActCount Actual # of bytes transferred
*/
typedef struct IOUSBIsocFrame {
    IOReturn                        frStatus;
    UInt16                          frReqCount;
    UInt16                          frActCount;
} IOUSBIsocFrame;


/*!
    @typedef                         
    Structure used to encode information about each isoc frame that is processed
    at hardware interrupt time
    @param frStatus Returns status associated with the frame
    @param frReqCount Input specifiying how many bytes to read or write
    @param frActCount Actual # of bytes transferred
    @param frTimeStamp Time stamp that indicates time when frame was procesed
*/
struct IOUSBLowLatencyIsocFrame {
    IOReturn                        frStatus;
    UInt16                          frReqCount;
    UInt16                          frActCount;
    AbsoluteTime		    frTimeStamp;
};

typedef struct IOUSBLowLatencyIsocFrame IOUSBLowLatencyIsocFrame;

/*!
    @typedef IOUSBCompletionAction
    Function called when USB I/O completes
    @param target The target specified in the IOUSBCompletion struct.
    @param parameter The parameter specified in the IOUSBCompletion struct.
    @param status Completion status
    @param bufferSizeRemaining bytes left to be transferred
*/
typedef void (*IOUSBCompletionAction)(
                void *			target,
                void *			parameter,
                IOReturn		status,
                UInt32			bufferSizeRemaining);

typedef void (*IOUSBIsocCompletionAction)(
                void *			target,
                void *			parameter,
                IOReturn		status,
                IOUSBIsocFrame		*pFrames);

typedef void (*IOUSBLowLatencyIsocCompletionAction)(
                void *				target,
                void *				parameter,
                IOReturn			status,
                IOUSBLowLatencyIsocFrame	*pFrames);

/*!
    @typedef IOUSBCompletion
    Struct spefifying action to perform when a USB I/O completes
    @param target The target to pass to the action function.
    @param action The function to call.
    @param parameter The parameter to pass to the action function.
    @param bufferSizeRemaining bytes left to be transferred
*/
typedef struct IOUSBCompletion {
    void * 			target;
    IOUSBCompletionAction	action;
    void *			parameter;
} IOUSBCompletion;

typedef struct IOUSBIsocCompletion {
    void * 			target;
    IOUSBIsocCompletionAction	action;
    void *			parameter;
} IOUSBIsocCompletion;

typedef struct IOUSBLowLatencyIsocCompletion {
    void * 				target;
    IOUSBLowLatencyIsocCompletionAction	action;
    void *				parameter;
} IOUSBLowLatencyIsocCompletion;


/* ************* USB Family error codes ************* */

#define	iokit_usb_err(return) (sys_iokit|sub_iokit_usb|return)
#define kIOUSBUnknownPipeErr		iokit_usb_err(97) // 0x61  Pipe ref not recognised
#define kIOUSBTooManyPipesErr		iokit_usb_err(96) // 0x60  Too many pipes
#define kIOUSBNoAsyncPortErr		iokit_usb_err(95) // 0x5f  no async port
#define kIOUSBNotEnoughPipesErr 	iokit_usb_err(94) // 0x5e  not enough pipes in interface
#define kIOUSBNotEnoughPowerErr 	iokit_usb_err(93) // 0x5d  not enough power for selected configuration
#define kIOUSBEndpointNotFound		iokit_usb_err(87) // 0x57  Not found
#define kIOUSBConfigNotFound		iokit_usb_err(86) // 0x56  Not found
#define kIOUSBTransactionTimeout	iokit_usb_err(81) // 0x51  time out
#define kIOUSBTransactionReturned	iokit_usb_err(80) // 0x50  The transaction has been returned to the caller
#define kIOUSBPipeStalled		iokit_usb_err(79) // 0x4f  Pipe has stalled, error needs to be cleared
#define kIOUSBInterfaceNotFound		iokit_usb_err(78) // 0x4e  Interface ref not recognized
#define kIOUSBLowLatencyBufferNotPreviouslyAllocated	iokit_usb_err(77) // 0x4d  Attempted to use user land low latency isoc calls w/out calling PrepareBuffer first
#define kIOUSBLowLatencyFrameListNotPreviouslyAllocated	iokit_usb_err(76) // 0x4c  Attempted to use user land low latency isoc calls w/out calling PrepareBuffer first

// USB Hardware Errors
// These errors are returned by the OHCI controller.  The # in parenthesis (xx) corresponds to the OHCI Completion Code.
// For the following Completion codes, we return a generic IOKit error instead of a USB specific error.  
//
// Completion Code   	Error Returned		Description
//     9		kIOReturnUnderrun	(Data Underrun) EP returned less data than max packet size
//     8		kIOReturnOverrun	(Data Overrun) Packet too large or more data than buffer
//     5		kIOReturnNotResponding  Device Not responding
//     4		kIOUSBPipeStalled	Endpoint returned a STALL PID
//
#define kIOUSBLinkErr		iokit_usb_err(16)	// 
#define kIOUSBNotSent2Err	iokit_usb_err(15) 	// Transaction not sent
#define kIOUSBNotSent1Err	iokit_usb_err(14) 	// Transaction not sent
#define kIOUSBBufferUnderrunErr	iokit_usb_err(13)	// Buffer Underrun (Host hardware failure on data out, PCI busy?)
#define kIOUSBBufferOverrunErr	iokit_usb_err(12)	// Buffer Overrun (Host hardware failure on data out, PCI busy?)
#define kIOUSBReserved2Err	iokit_usb_err(11)	// Reserved
#define kIOUSBReserved1Err	iokit_usb_err(10)	// Reserved
#define kIOUSBWrongPIDErr	iokit_usb_err(7)	// Pipe stall, Bad or wrong PID
#define kIOUSBPIDCheckErr	iokit_usb_err(6)	// Pipe stall, PID CRC error
#define kIOUSBDataToggleErr	iokit_usb_err(3)	// Pipe stall, Bad data toggle
#define kIOUSBBitstufErr	iokit_usb_err(2)	// Pipe stall, bitstuffing
#define kIOUSBCRCErr		iokit_usb_err(1)	// Pipe stall, bad CRC

/* ************* USB Family Messages ************* */

#define iokit_usb_msg(message) 			(UInt32)(sys_iokit|sub_iokit_usb|message)
#define kIOUSBMessageHubResetPort      		iokit_usb_msg(1)
#define kIOUSBMessageHubSuspendPort		iokit_usb_msg(2)
#define kIOUSBMessageHubResumePort      	iokit_usb_msg(3)
#define kIOUSBMessageHubIsDeviceConnected	iokit_usb_msg(4)
#define kIOUSBMessageHubIsPortEnabled		iokit_usb_msg(5)
#define kIOUSBMessageHubReEnumeratePort		iokit_usb_msg(6)
#define kIOUSBMessagePortHasBeenReset		iokit_usb_msg(10)
#define kIOUSBMessagePortHasBeenResumed		iokit_usb_msg(11)

/* ************* types ************* */

struct IOUSBMouseData {
    UInt16 				buttons;
    SInt16 				XDelta;
    SInt16 				YDelta;
};
typedef struct IOUSBMouseData		IOUSBMouseData;
typedef IOUSBMouseData *		IOUSBMouseDataPtr;

struct IOUSBKeyboardData {
    UInt16 				keycount;
    UInt16 				usbkeycode[32];
};
typedef struct IOUSBKeyboardData	IOUSBKeyboardData;
typedef IOUSBKeyboardData *		IOUSBKeyboardDataPtr;

union IOUSBHIDData {
    IOUSBKeyboardData 			kbd;
    IOUSBMouseData 			mouse;
};
typedef union IOUSBHIDData		IOUSBHIDData;
typedef IOUSBHIDData *			IOUSBHIDDataPtr;

struct IOUSBDeviceDescriptor {
	UInt8 			bLength;
	UInt8 			bDescriptorType;
	UInt16 			bcdUSB;
	UInt8 			bDeviceClass;
	UInt8 			bDeviceSubClass;
	UInt8 			bDeviceProtocol;
	UInt8 			bMaxPacketSize0;
	UInt16 			idVendor;
	UInt16 			idProduct;
	UInt16 			bcdDevice;
	UInt8 			iManufacturer;
	UInt8 			iProduct;
	UInt8 			iSerialNumber;
	UInt8 			bNumConfigurations;
};
typedef struct IOUSBDeviceDescriptor		IOUSBDeviceDescriptor;
typedef IOUSBDeviceDescriptor *			IOUSBDeviceDescriptorPtr;

struct IOUSBDescriptorHeader {
	UInt8 			bLength;
	UInt8 			bDescriptorType;
};
typedef struct IOUSBDescriptorHeader		IOUSBDescriptorHeader;
typedef IOUSBDescriptorHeader *			IOUSBDescriptorHeaderPtr;

struct IOUSBConfigurationDescriptor {
	UInt8 			bLength;
	UInt8 			bDescriptorType;
	UInt16 			wTotalLength;
	UInt8 			bNumInterfaces;
	UInt8 			bConfigurationValue;
	UInt8 			iConfiguration;
	UInt8 			bmAttributes;
	UInt8 			MaxPower;
};
typedef struct IOUSBConfigurationDescriptor 	IOUSBConfigurationDescriptor;
typedef IOUSBConfigurationDescriptor *		IOUSBConfigurationDescriptorPtr;

struct IOUSBConfigurationDescHeader {
	UInt8 			bLength;
	UInt8 			bDescriptorType;
	UInt16 			wTotalLength;
};
typedef struct IOUSBConfigurationDescHeader 	IOUSBConfigurationDescHeader;
typedef IOUSBConfigurationDescHeader *		IOUSBConfigurationDescHeaderPtr;

struct IOUSBInterfaceDescriptor {
	UInt8 			bLength;
	UInt8 			bDescriptorType;
	UInt8 			bInterfaceNumber;
	UInt8 			bAlternateSetting;
	UInt8 			bNumEndpoints;
	UInt8 			bInterfaceClass;
	UInt8 			bInterfaceSubClass;
	UInt8 			bInterfaceProtocol;
	UInt8 			iInterface;
};
typedef struct IOUSBInterfaceDescriptor	IOUSBInterfaceDescriptor;
typedef IOUSBInterfaceDescriptor *	IOUSBInterfaceDescriptorPtr;

struct IOUSBEndpointDescriptor {
	UInt8 			bLength;
	UInt8 			bDescriptorType;
	UInt8 			bEndpointAddress;
	UInt8 			bmAttributes;
	UInt16 			wMaxPacketSize;	
	UInt8 			bInterval;
};
typedef struct IOUSBEndpointDescriptor	IOUSBEndpointDescriptor;
typedef IOUSBEndpointDescriptor *	IOUSBEndpointDescriptorPtr;

struct IOUSBHIDDescriptor {
	UInt8 			descLen;
	UInt8 			descType;
	UInt16 			descVersNum;
	UInt8 			hidCountryCode;
	UInt8 			hidNumDescriptors;
	UInt8 			hidDescriptorType;
        /* can't make this a single 16bit value or the compiler will add a filler byte*/
	UInt8 			hidDescriptorLengthLo;
	UInt8 			hidDescriptorLengthHi;
};
typedef struct IOUSBHIDDescriptor	IOUSBHIDDescriptor;
typedef IOUSBHIDDescriptor *IOUSBHIDDescriptorPtr;

struct IOUSBHIDReportDesc {
	UInt8 			hidDescriptorType;
    	/* can't make this a single 16bit value or the compiler will add a filler byte*/
	UInt8 			hidDescriptorLengthLo;	
	UInt8 			hidDescriptorLengthHi;
};
typedef struct IOUSBHIDReportDesc	IOUSBHIDReportDesc;
typedef IOUSBHIDReportDesc *		IOUSBHIDReportDescPtr;

#pragma pack(1)
struct IOUSBDeviceQualifierDescriptor
{
	UInt8 			bLength;
	UInt8 			bDescriptorType;
	UInt16 			bcdUSB;
	UInt8 			bDeviceClass;
	UInt8 			bDeviceSubClass;
	UInt8 			bDeviceProtocol;
	UInt8 			bMaxPacketSize0;
	UInt8 			bNumConfigurations;
	UInt8 			bReserved;
};
typedef struct IOUSBDeviceQualifierDescriptor	IOUSBDeviceQualifierDescriptor;
typedef IOUSBDeviceQualifierDescriptor *	IOUSBDeviceQualifierDescriptorPtr;

struct IOUSBDFUDescriptor 
{
        UInt8 			bLength;
        UInt8 			bDescriptorType;
        UInt8 			bmAttributes;
        UInt16 			wDetachTimeout;
        UInt16 			wTransferSize;
};
typedef struct 	IOUSBDFUDescriptor 		IOUSBDFUDescriptor;
typedef 		IOUSBDFUDescriptor *	IOUSBDFUDescriptorPtr;

#pragma options align=reset

typedef UInt16				USBStatus;
typedef USBStatus *			USBStatusPtr;

enum {
    kIOUSBAnyClass	= 0xFFFF,
    kIOUSBAnySubClass	= 0xFFFF,
    kIOUSBAnyProtocol	= 0xFFFF,
    kIOUSBAnyVendor	= 0xFFFF,
    kIOUSBAnyProduct	= 0xFFFF
};
typedef struct IOUSBMatch {
    UInt16	usbClass;
    UInt16	usbSubClass;
    UInt16	usbProtocol;
    UInt16	usbVendor;
    UInt16	usbProduct;
} IOUSBMatch;

/*!
    @typedef IOUSBFindEndpointRequest
    Struct used to find endpoints of an interface
    type and direction are used to match endpoints,
    type, direction, maxPacketSize and interval are updated
    with the properties of the found endpoint.
    @field type Type of endpoint: kUSBControl, kUSBIsoc, kUSBBulk, kUSBInterrupt, kUSBAnyType
    @field direction Direction of endpoint: kUSBOut, kUSBIn, kUSBAnyDirn
    @field maxPacketSize maximum packet size of endpoint.
    @field interval Polling interval in mSec for endpoint.
*/
typedef struct {
	UInt8 type;		// kUSBAnyType = don't care
	UInt8 direction;	// kUSBAnyDirn = don't care
        UInt16 maxPacketSize;
        UInt8 interval;
} IOUSBFindEndpointRequest;

/*
 * Stuff for IOUserClient
 */

/*!
    @struct IOUSBDevRequest
    parameter block for control requests, using a simple pointer
    for the data to be transferred.
    @field rdDirection Direction of data part of request: kUSBIn or kUSBOut
    @field rqType Request type: kUSBStandard, kUSBClass or kUSBVendor
    @field rqRecipient Target of the request: kUSBDevice, kUSBInterface,
	kUSBEndpoint or kUSBOther
    @field bRequest Request code
    @field wValue 16 bit parameter for request, host endianess
    @field wIndex 16 bit parameter for request, host endianess
    @field wLength Length of data part of request, 16 bits, host endianess
    @field pData Pointer to data for request - data returned in bus endianess
    @field wLenDone Set by standard completion routine to number of data bytes
	actually transferred
*/
typedef struct {
    UInt8   	bmRequestType;
    UInt8 	bRequest;
    UInt16 	wValue;
    UInt16 	wIndex;
    UInt16	wLength;
    void * 	pData;		// data pointer
    UInt32	wLenDone;	// # bytes transferred
} IOUSBDevRequest;
typedef IOUSBDevRequest * IOUSBDeviceRequestPtr;

// This is the same structure as above, with two extra fields to specify timeout values
typedef struct {
    UInt8   	bmRequestType;
    UInt8 	bRequest;
    UInt16 	wValue;
    UInt16 	wIndex;
    UInt16	wLength;
    void * 	pData;		// data pointer
    UInt32	wLenDone;	// # bytes transferred
    UInt32	noDataTimeout;
    UInt32	completionTimeout;
} IOUSBDevRequestTO;

enum
{
    kUSBDefaultControlNoDataTimeoutMS = 5000,
    kUSBDefaultControlCompletionTimeoutMS = 0
};

typedef struct
{
    UInt32	pipeRef;
    void	*buf;
    UInt32	size;
    UInt32	noDataTimeout;
    UInt32	completionTimeout;
} IOUSBBulkPipeReq;


#if KERNEL
/*!
    @struct IOUSBDevRequestDesc
    parameter block for control requests, using a memory descriptor
    for the data to be transferred
    @field rdDirection Direction of data part of request: kUSBIn or kUSBOut
    @field rqType Request type: kUSBStandard, kUSBClass or kUSBVendor
    @field rqRecipient Target of the request: kUSBDevice, kUSBInterface,
        kUSBEndpoint or kUSBOther
    @field bRequest Request code
    @field wValue 16 bit parameter for request, host endianess
    @field wIndex 16 bit parameter for request, host endianess
    @field wLength Length of data part of request, 16 bits, host endianess
    @field pData Pointer to memory descriptor for data for request - data returned in bus endianess
    @field wLenDone Set by standard completion routine to number of data bytes
     actually transferred
*/
typedef struct {
    UInt8   	bmRequestType;
    UInt8 	bRequest;
    UInt16 	wValue;
    UInt16 	wIndex;
    UInt16	wLength;
    IOMemoryDescriptor *pData;	// data pointer
    UInt32	wLenDone;	// # bytes transferred
} IOUSBDevRequestDesc;


enum {
    // IOOptionBits for IOServiceOpen
    kIOUSBInterfaceOpenAlt	= 0x00010000
};

#endif

// use a structure because there's a limit of 6 total arguments
// to a user client method.
typedef struct {
    UInt8   	bmRequestType;
    UInt8 	bRequest;
    UInt16 	wValue;
    UInt16 	wIndex;
    UInt16	wLength;
    void * 	pData;		// data pointer
    UInt32	wLenDone;	// # bytes transferred
    UInt8	pipeRef;
} IOUSBDevReqOOL;

typedef struct {
    UInt8   	bmRequestType;
    UInt8 	bRequest;
    UInt16 	wValue;
    UInt16 	wIndex;
    UInt16	wLength;
    void * 	pData;		// data pointer
    UInt32	wLenDone;	// # bytes transferred
    UInt8	pipeRef;
    UInt32	noDataTimeout;
    UInt32	completionTimeout;
} IOUSBDevReqOOLTO;

// Structure to request isochronous transfer
//
typedef struct {
    UInt32 		fPipe;
    void 		*fBuffer;
    UInt32 		fBufSize;
    UInt64 		fStartFrame;
    UInt32 		fNumFrames;
    IOUSBIsocFrame 	*fFrameCounts;
} IOUSBIsocStruct;

// Structure to request low latency isochronous transfer
//
struct IOUSBLowLatencyIsocStruct {
    UInt32 			fPipe;
    UInt32 			fBufSize;
    UInt64 			fStartFrame;
    UInt32 			fNumFrames;
    UInt32			fUpdateFrequency;
    UInt32			fDataBufferCookie;
    UInt32			fDataBufferOffset;
    UInt32			fFrameListBufferCookie;
    UInt32			fFrameListBufferOffset;
};

typedef struct IOUSBLowLatencyIsocStruct IOUSBLowLatencyIsocStruct;

// Structure to return frame number, and time frame register was read.
//
typedef struct {
    UInt64	 frame;
    AbsoluteTime timeStamp;
} IOUSBGetFrameStruct;


typedef struct {
    UInt16	bInterfaceClass;		// requested class
    UInt16 	bInterfaceSubClass;		// requested subclass
    UInt16 	bInterfaceProtocol;		// requested protocol
    UInt16	bAlternateSetting;		// requested alt setting
} IOUSBFindInterfaceRequest;

enum {
        kIOUSBFindInterfaceDontCare		= 0xFFFF
        };

enum {
	kIOUSBVendorIDAppleComputer		= 0x05AC	/* Assigned by USB-if*/
        };

enum {
        kUSBDeviceSpeedLow		= 0,		// low speed device
        kUSBDeviceSpeedFull		= 1,		// full speed device
        kUSBDeviceSpeedHigh		= 2		// high speed device
        };

enum {
    kUSBFullSpeedMicrosecondsInFrame		= 1000,		// full speed device
    kUSBHighSpeedMicrosecondsInFrame		= 125		// high speed device
};

enum {
        kUSBLowLatencyIsochTransferKey	= 'llit'	// Set frStatus field of first frame in isoch transfer to designate as low latency
    };
    
typedef struct LowLatencyUserBufferInfo LowLatencyUserBufferInfo;

struct LowLatencyUserBufferInfo {
    UInt32			cookie;
    void *			bufferAddress;
    IOByteCount			bufferSize;
    UInt32			bufferType;
    Boolean			isPrepared;
    LowLatencyUserBufferInfo *	nextBuffer;
};

typedef enum {
    kUSBLowLatencyWriteBuffer 		= 0,
    kUSBLowLatencyReadBuffer		= 1,
    kUSBLowLatencyFrameListBuffer	= 2
} USBLowLatencyBufferType;

// USB User Notification Types
enum {
    kUSBNoUserNotificationType			= 0,
    kUSBNotEnoughPowerNotificationType		= 1,
    kUSBIndividualOverCurrentNotificationType	= 2,
    kUSBGangOverCurrentNotificationType		= 3
};

// misc. properties which are useful
#define	kUSBDevicePropertySpeed			"Device Speed"
#define kUSBDevicePropertyBusPowerAvailable 	"Bus Power Available"
#define kUSBDevicePropertyAddress		"USB Address"
#define kUSBDevicePropertyLocationID		"locationID"

#ifdef __cplusplus
}       
#endif

#endif /* _USB_H */

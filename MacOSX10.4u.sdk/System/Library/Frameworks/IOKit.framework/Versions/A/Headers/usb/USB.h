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

    /*!
    @header		USB.h
     @abstract	Public Interfaces to the USB implementation in Mac OS X.
     @discussion	This header file contains definitions and structures that are used in the different USB API's in Mac OS X, both in the kernel and in the user space.
     */

#if KERNEL
    /*!
    @defined Kernel Endian conversion definitions
     @discussion The USB API's use a convention of specifying parameters in the host order.  The USB spec specifies that multi-byte items should be
     formatted in little endian order.  The following macros allow one to translate multi-byte values from Host order to USB order and vice versa.  There are separate macros for
     in-kernel use and for user space use.
     */
#define USBToHostWord OSSwapLittleToHostInt16
#define HostToUSBWord OSSwapHostToLittleInt16
#define USBToHostLong OSSwapLittleToHostInt32
#define HostToUSBLong OSSwapHostToLittleInt32
#else
    /*!
    @defined User Space Endian conversion definitions
     @discussion The USB API's use a convention of specifying parameters in the host order.  The USB spec specifies that multi-byte items should be
     formatted in little endian order.  The following macros allow one to translate multi-byte values from Host order to USB order and vice versa.  There are separate macros for
     in-kernel use and for user space use.
     */
#define USBToHostWord NXSwapLittleShortToHost
#define HostToUSBWord NXSwapHostShortToLittle
#define USBToHostLong NXSwapLittleLongToHost
#define HostToUSBLong NXSwapHostLongToLittle
#endif

    /*!
    @enum Miscellaneous Constants
    @discussion 
    */
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

/*!
@enum bRequest Shifts and Masks 
@discussion These are used to create the macro to encode the bRequest filed of a Device Request
*/
enum {
    kUSBRqDirnShift = 7,
    kUSBRqDirnMask = 1,

    kUSBRqTypeShift = 5,
    kUSBRqTypeMask = 3,

    kUSBRqRecipientMask = 0X1F
};

/*!
@defined USBmakebmRequestType 
@discussion Macro to encode the bRequest field of a Device Request.  It is used when constructing an IOUSBDevRequest.
*/
#define USBmakebmRequestType(direction, type, recipient)		\
    ((direction & kUSBRqDirnMask) << kUSBRqDirnShift) |			\
    ((type & kUSBRqTypeMask) << kUSBRqTypeShift) |			\
    (recipient & kUSBRqRecipientMask)

/*!
@enum kUSBMaxIsocFrameReqCount 
@discussion Maximum size in bytes allowed for one Isochronous frame
*/
enum {
    kUSBMaxFSIsocEndpointReqCount = 1023,	// max size (bytes) of any one Isoc frame for 1 FS endpoint
	kUSBMaxHSIsocEndpointReqCount = 3072,	// max size (bytes) of any one Isoc frame for 1 HS endpoint
	kUSBMaxHSIsocFrameCount = 7168			// max size (bytes) of all Isoc transfers in a HS frame
};

/*!
@defined EncodeRequest 
@discussion Macro that encodes the bRequest and bRequestType fields of a IOUSBDevRequest into a single value.  It is useful when one needs
to know what type of request the IOUSBDevRequest encodes and simplifies comparisons.
*/
#define EncodeRequest(request, direction, type, recipient)		\
    (((UInt16)request << 8) +	    					\
              ((UInt16)recipient +					\
                        ((UInt16)type << kUSBRqTypeShift) +		\
                        ((UInt16)direction << kUSBRqDirnShift)))


/*!
@enum Standard Device Requests
@discussion Encoding of the standard device requests.
<tt>
<pre><b>
bmRequestType bRequest          wValue        wIndex     wLength Data</b>
00000000B     CLEAR_FEATURE     Feature       Zero       Zero    None (device)
00000001B                       Feature       Interface  Zero    None (Interface)
00000010B                       Feature       Endpoint   Zero    None (Endpoint)

10000000B     GET_CONFIGURATION Zero          Zero       One     Configuration
10000000B     GET_DESCRIPTOR    Type          LangID     Length  Descriptor
10000001B     GET_INTERFACE     Zero          Interface  One     Alternate

10000000B     GET_STATUS        Zero          Zero       Two     status (device)
10000001B                       Zero          Interface  Two     status (Interface)
10000010B                       Zero          Endpoint   Two     status (Endpoint)

00000000B     SET_ADDRESS       Address       Zero       Zero    None
00000000B     SET_CONFIGURATION Configuration Zero       Zero    None
00000000B     SET_DESCRIPTOR    Type          LangID     Length  Descriptor

00000000B     SET_FEATURE       Feature       Zero       Zero    None (device)
00000001B                       Feature       Interface  Zero    None (Interface)
00000010B                       Feature       Endpoint   Zero    None (Endpoint)

00000001B     SET_INTERFACE     Alternate     Interface  Zero    None
10000010B     SYNCH_FRAME       Zero          Endpoint   Two     Frame Number
</pre>
</tt>
*/
enum {
    kClearDeviceFeature     = EncodeRequest(kUSBRqClearFeature,  kUSBOut, kUSBStandard, kUSBDevice),
    kClearInterfaceFeature  = EncodeRequest(kUSBRqClearFeature,  kUSBOut, kUSBStandard, kUSBInterface),
    kClearEndpointFeature   = EncodeRequest(kUSBRqClearFeature,  kUSBOut, kUSBStandard, kUSBEndpoint),
    kGetConfiguration       = EncodeRequest(kUSBRqGetConfig,     kUSBIn,  kUSBStandard, kUSBDevice),
    kGetDescriptor          = EncodeRequest(kUSBRqGetDescriptor, kUSBIn,  kUSBStandard, kUSBDevice),
    kGetInterface           = EncodeRequest(kUSBRqGetInterface,  kUSBIn,  kUSBStandard, kUSBInterface),
    kGetDeviceStatus        = EncodeRequest(kUSBRqGetStatus,     kUSBIn,  kUSBStandard, kUSBDevice),
    kGetInterfaceStatus     = EncodeRequest(kUSBRqGetStatus,     kUSBIn,  kUSBStandard, kUSBInterface),
    kGetEndpointStatus      = EncodeRequest(kUSBRqGetStatus,     kUSBIn,  kUSBStandard, kUSBEndpoint),
    kSetAddress             = EncodeRequest(kUSBRqSetAddress,    kUSBOut, kUSBStandard, kUSBDevice),
    kSetConfiguration       = EncodeRequest(kUSBRqSetConfig,     kUSBOut, kUSBStandard, kUSBDevice),
    kSetDescriptor          = EncodeRequest(kUSBRqSetDescriptor, kUSBOut, kUSBStandard, kUSBDevice),
    kSetDeviceFeature       = EncodeRequest(kUSBRqSetFeature,    kUSBOut, kUSBStandard, kUSBDevice),
    kSetInterfaceFeature    = EncodeRequest(kUSBRqSetFeature,    kUSBOut, kUSBStandard, kUSBInterface),
    kSetEndpointFeature     = EncodeRequest(kUSBRqSetFeature,    kUSBOut, kUSBStandard, kUSBEndpoint),
    kSetInterface           = EncodeRequest(kUSBRqSetInterface,  kUSBOut, kUSBStandard, kUSBInterface),
    kSyncFrame              = EncodeRequest(kUSBRqSyncFrame,     kUSBIn,  kUSBStandard, kUSBEndpoint),
};

/*!
@defined kCallInterfaceOpenWithGate
 @discussion If the USB Device has this property, drivers for any of its interfaces will have their handleOpen method called while holding the workloop gate.
 */
#define kCallInterfaceOpenWithGate	"kCallInterfaceOpenWithGate"

// TYPES

typedef UInt16 USBDeviceAddress;


/*!
    @typedef IOUSBIsocFrame
    @discussion Structure used to encode information about each isoc frame.
    @param frStatus Returns status associated with the frame.
    @param frReqCount Input specifiying how many bytes to read or write.
    @param frActCount Actual # of bytes transferred.
*/
typedef struct IOUSBIsocFrame {
    IOReturn                        frStatus;
    UInt16                          frReqCount;
    UInt16                          frActCount;
} IOUSBIsocFrame;


/*!
    @typedef IOUSBLowLatencyIsocFrame
    @discussion    Structure used to encode information about each isoc frame that is processed
    at hardware interrupt time (low latency).
    @param frStatus Returns status associated with the frame.
    @param frReqCount Input specifiying how many bytes to read or write.
    @param frActCount Actual # of bytes transferred.
    @param frTimeStamp Time stamp that indicates time when frame was procesed.
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
 @discussion Function called when USB I/O completes.
 @param target The target specified in the IOUSBCompletion struct.
 @param parameter The parameter specified in the IOUSBCompletion struct.
 @param status Completion status.
 @param bufferSizeRemaining Bytes left to be transferred.
 */
typedef void (*IOUSBCompletionAction)(
                                      void *			target,
                                      void *			parameter,
                                      IOReturn		status,
                                      UInt32			bufferSizeRemaining);

/*!
@typedef IOUSBCompletionActionWithTimeStamp
 @discussion Function called when USB I/O completes.
 @param target The target specified in the IOUSBCompletion struct.
 @param parameter The parameter specified in the IOUSBCompletion struct.
 @param status Completion status.
 @param bufferSizeRemaining Bytes left to be transferred.
 @param timeStamp Time at which the transaction was processed.
 */
typedef void (*IOUSBCompletionActionWithTimeStamp)(
                                      void *		target,
                                      void *		parameter,
                                      IOReturn		status,
                                      UInt32		bufferSizeRemaining,
                                      AbsoluteTime	timeStamp);

/*!
    @typedef IOUSBIsocCompletionAction
    @discussion Function called when Isochronous USB I/O completes.
    @param target The target specified in the IOUSBIsocCompletionn struct.
    @param parameter The parameter specified in the IOUSBIsocCompletion struct.
    @param status Completion status.
    @param pFrames Pointer to the frame list containing the status for each frame transferred.
*/
typedef void (*IOUSBIsocCompletionAction)(
                void *			target,
                void *			parameter,
                IOReturn		status,
                IOUSBIsocFrame		*pFrames);

/*!
    @typedef IOUSBLowLatencyIsocCompletionAction
    @discussion Function called when Low Latency Isochronous USB I/O completes.
    @param target The target specified in the IOUSBLowLatencyIsocCompletion struct.
    @param parameter The parameter specified in the IOUSBLowLatencyIsocCompletion struct.
    @param status Completion status.
    @param pFrames Pointer to the low latency frame list containing the status for each frame transferred.
*/
typedef void (*IOUSBLowLatencyIsocCompletionAction)(
                void *				target,
                void *				parameter,
                IOReturn			status,
                IOUSBLowLatencyIsocFrame	*pFrames);

/*!
@typedef IOUSBCompletion
 @discussion Struct specifying action to perform when a USB I/O completes.
 @param target The target to pass to the action function.
 @param action The function to call.
 @param parameter The parameter to pass to the action function.
 */
typedef struct IOUSBCompletion {
    void * 			target;
    IOUSBCompletionAction	action;
    void *			parameter;
} IOUSBCompletion;

/*!
@typedef IOUSBCompletionWithTimeStamp
 @discussion Struct specifying action to perform when a USB I/O completes.
 @param target The target to pass to the action function.
 @param action The function to call.
 @param parameter The parameter to pass to the action function.
 */
typedef struct IOUSBCompletionWithTimeStamp {
    void * 				target;
    IOUSBCompletionActionWithTimeStamp	action;
    void *				parameter;
} IOUSBCompletionWithTimeStamp;

/*!
    @typedef IOUSBIsocCompletion
    @discussion Struct specifying action to perform when an Isochronous USB I/O completes.
    @param target The target to pass to the action function.
    @param action The function to call.
    @param parameter The parameter to pass to the action function.
*/
typedef struct IOUSBIsocCompletion {
    void * 			target;
    IOUSBIsocCompletionAction	action;
    void *			parameter;
} IOUSBIsocCompletion;

/*!
    @typedef IOUSBLowLatencyIsocCompletion
    @discussion Struct specifying action to perform when an Low Latency Isochronous USB I/O completes.
    @param target The target to pass to the action function.
    @param action The function to call.
    @param parameter The parameter to pass to the action function.
*/
typedef struct IOUSBLowLatencyIsocCompletion {
    void * 				target;
    IOUSBLowLatencyIsocCompletionAction	action;
    void *				parameter;
} IOUSBLowLatencyIsocCompletion;


/*!
@defined IOUSBFamily error codes
@discussion  Errors specific to the IOUSBFamily.  Note that the iokit_usb_err(x) translates to 0xe0004xxx, where xxx is the value in parenthesis as a hex number.
*/
#define	iokit_usb_err(return)       (sys_iokit|sub_iokit_usb|return)
#define kIOUSBUnknownPipeErr        iokit_usb_err(97)  // 0xe0004061  Pipe ref not recognized
#define kIOUSBTooManyPipesErr       iokit_usb_err(96)  // 0xe0004060  Too many pipes
#define kIOUSBNoAsyncPortErr        iokit_usb_err(95)  // 0xe000405f  no async port
#define kIOUSBNotEnoughPipesErr     iokit_usb_err(94)  // 0xe000405e  not enough pipes in interface
#define kIOUSBNotEnoughPowerErr     iokit_usb_err(93)  // 0xe000405d  not enough power for selected configuration
#define kIOUSBEndpointNotFound      iokit_usb_err(87)  // 0xe0004057  Endpoint Not found
#define kIOUSBConfigNotFound        iokit_usb_err(86)  // 0xe0004056  Configuration Not found
#define kIOUSBTransactionTimeout    iokit_usb_err(81)  // 0xe0004051  Transaction timed out
#define kIOUSBTransactionReturned   iokit_usb_err(80)  // 0xe0004050  The transaction has been returned to the caller
#define kIOUSBPipeStalled           iokit_usb_err(79)  // 0xe000404f  Pipe has stalled, error needs to be cleared
#define kIOUSBInterfaceNotFound     iokit_usb_err(78)  // 0xe000404e  Interface ref not recognized
#define kIOUSBLowLatencyBufferNotPreviouslyAllocated        iokit_usb_err(77)  // 0xe000404d  Attempted to use user land low latency isoc calls w/out calling PrepareBuffer (on the data buffer) first 
#define kIOUSBLowLatencyFrameListNotPreviouslyAllocated     iokit_usb_err(76)  // 0xe000404c  Attempted to use user land low latency isoc calls w/out calling PrepareBuffer (on the frame list) first
#define kIOUSBHighSpeedSplitError     iokit_usb_err(75) // 0xe000404b Error to hub on high speed bus trying to do split transaction
#define kIOUSBSyncRequestOnWLThread	iokit_usb_err(74)	// 0xe000404a  A synchronous USB request was made on the workloop thread (from a callback?).  Only async requests are permitted in that case
#define kIOUSBDeviceNotHighSpeed	iokit_usb_err(73)	// 0xe0004049  The device is not a high speed device, so the EHCI driver returns an error

/*!
@defined IOUSBFamily hardware error codes
@discussion These errors are returned by the OHCI controller.  The # in parenthesis (xx) corresponds to the OHCI Completion Code.
For the following Completion codes, we return a generic IOKit error instead of a USB specific error.  
<tt>
<pre>
Completion Code         Error Returned              Description
9                       kIOReturnUnderrun           (Data Underrun) EP returned less data than max packet size
8                       kIOReturnOverrun            (Data Overrun) Packet too large or more data than buffer
5                       kIOReturnNotResponding      Device Not responding
4                       kIOUSBPipeStalled           Endpoint returned a STALL PID
</pre>
</tt>
*/
#define kIOUSBLinkErr           iokit_usb_err(16)  // 0xe0004010
#define kIOUSBNotSent2Err       iokit_usb_err(15)  // 0xe000400f Transaction not sent
#define kIOUSBNotSent1Err       iokit_usb_err(14)  // 0xe000400e Transaction not sent
#define kIOUSBBufferUnderrunErr iokit_usb_err(13)  // 0xe000400d Buffer Underrun (Host hardware failure on data out, PCI busy?)
#define kIOUSBBufferOverrunErr  iokit_usb_err(12)  // 0xe000400c Buffer Overrun (Host hardware failure on data out, PCI busy?)
#define kIOUSBReserved2Err      iokit_usb_err(11)  // 0xe000400b Reserved
#define kIOUSBReserved1Err      iokit_usb_err(10)  // 0xe000400a Reserved
#define kIOUSBWrongPIDErr       iokit_usb_err(7)   // 0xe0004007 Pipe stall, Bad or wrong PID
#define kIOUSBPIDCheckErr       iokit_usb_err(6)   // 0xe0004006 Pipe stall, PID CRC error
#define kIOUSBDataToggleErr     iokit_usb_err(3)   // 0xe0004003 Pipe stall, Bad data toggle
#define kIOUSBBitstufErr        iokit_usb_err(2)   // 0xe0004002 Pipe stall, bitstuffing
#define kIOUSBCRCErr            iokit_usb_err(1)   // 0xe0004001 Pipe stall, bad CRC

/*!
@defined IOUSBFamily message codes
@discussion  Messages specific to the IOUSBFamily.  Note that the iokit_usb_msg(x) translates to 0xe0004xxx, where xxx is the value in parenthesis as a hex number.
*/
#define iokit_usb_msg(message)						(UInt32)(sys_iokit|sub_iokit_usb|message)
#define kIOUSBMessageHubResetPort					iokit_usb_msg(1)   // 0xe00004001  Message sent to a hub to reset a particular port
#define kIOUSBMessageHubSuspendPort					iokit_usb_msg(2)   // 0xe00004002  Message sent to a hub to suspend a particular port
#define kIOUSBMessageHubResumePort					iokit_usb_msg(3)   // 0xe00004003  Message sent to a hub to resume a particular port
#define kIOUSBMessageHubIsDeviceConnected			iokit_usb_msg(4)   // 0xe00004004  Message sent to a hub to inquire whether a particular port has a device connected or not
#define kIOUSBMessageHubIsPortEnabled				iokit_usb_msg(5)   // 0xe00004005  Message sent to a hub to inquire whether a particular port is enabled or not
#define kIOUSBMessageHubReEnumeratePort				iokit_usb_msg(6)   // 0xe00004006  Message sent to a hub to reenumerate the device attached to a particular port
#define kIOUSBMessagePortHasBeenReset				iokit_usb_msg(10)  // 0xe0000400a  Message sent to a device indicating that the port it is attached to has been reset
#define kIOUSBMessagePortHasBeenResumed				iokit_usb_msg(11)  // 0xe0000400b  Message sent to a device indicating that the port it is attached to has been resumed
#define kIOUSBMessageHubPortClearTT					iokit_usb_msg(12)  // 0xe0000400c  Message sent to a hub to clear the transaction translator
#define kIOUSBMessagePortHasBeenSuspended			iokit_usb_msg(13)  // 0xe0000400d  Message sent to a device indicating that the port it is attached to has been suspended
#define kIOUSBMessageFromThirdParty					iokit_usb_msg(14)  // 0xe0000400e  Message sent from a third party.  Uses IOUSBThirdPartyParam to encode the sender's ID
#define kIOUSBMessagePortWasNotSuspended			iokit_usb_msg(15)  // 0xe0000400f  Message indicating that the hub driver received a resume request for a port that was not suspended
#define kIOUSBMessageExpressCardCantWake			iokit_usb_msg(16)  // 0xe00004010  Message from a driver to a bus that an express card will disconnect on sleep and thus shouldn't wake
#define kIOUSBMessageCompositeDriverReconfigured    iokit_usb_msg(17)  // 0xe00004011  Message from the composite driver indicating that it has finished re-configuring the device after a reset
#define kIOUSBMessageRequestExtraPower				iokit_usb_msg(18)  // 0xe00004012  Message indicating a desire to have more power than the 500ma normally available

// Obsolete
//
struct IOUSBMouseData {
    UInt16 				buttons;
    SInt16 				XDelta;
    SInt16 				YDelta;
};
typedef struct IOUSBMouseData		IOUSBMouseData;
typedef IOUSBMouseData *		IOUSBMouseDataPtr;

// Obsolete
//
struct IOUSBKeyboardData {
    UInt16 				keycount;
    UInt16 				usbkeycode[32];
};
typedef struct IOUSBKeyboardData	IOUSBKeyboardData;
typedef IOUSBKeyboardData *		IOUSBKeyboardDataPtr;

// Obsolete
//
union IOUSBHIDData {
    IOUSBKeyboardData 			kbd;
    IOUSBMouseData 			mouse;
};
typedef union IOUSBHIDData		IOUSBHIDData;
typedef IOUSBHIDData *			IOUSBHIDDataPtr;

/*!
    @typedef IOUSBDeviceDescriptor
    @discussion Descriptor for a USB Device.  See the USB Specification at <a href="http://www.usb.org"TARGET="_blank">http://www.usb.org</a>.
*/
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

/*!
    @typedef IOUSBDescriptorHeader
    @discussion Standard header used for all USB descriptors.  Used to read the length of a descriptor so that we can allocate storage for the whole descriptor later on.
*/
struct IOUSBDescriptorHeader {
	UInt8 			bLength;
	UInt8 			bDescriptorType;
};
typedef struct IOUSBDescriptorHeader		IOUSBDescriptorHeader;
typedef IOUSBDescriptorHeader *			IOUSBDescriptorHeaderPtr;

/*!
    @typedef IOUSBConfigurationDescriptor
    @discussion Standard USB Configuration Descriptor.  It is variable length, so this only specifies the known fields.  We use the wTotalLength field to read the whole descriptor.
    See the USB Specification at <a href="http://www.usb.org"TARGET="_blank">http://www.usb.org</a>.
*/
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

/*!
    @typedef IOUSBConfigurationDescHeader
    @discussion Header of a IOUSBConfigurationDescriptor.  Used to get the total length of the descriptor.
*/
struct IOUSBConfigurationDescHeader {
	UInt8 			bLength;
	UInt8 			bDescriptorType;
	UInt16 			wTotalLength;
};
typedef struct IOUSBConfigurationDescHeader 	IOUSBConfigurationDescHeader;
typedef IOUSBConfigurationDescHeader *		IOUSBConfigurationDescHeaderPtr;

/*!
    @typedef IOUSBInterfaceDescriptor
    @discussion Descriptor for a USB Interface.  See the USB Specification at <a href="http://www.usb.org"TARGET="_blank">http://www.usb.org</a>.
*/
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

/*!
    @typedef IOUSBEndpointDescriptor
    @discussion Descriptor for a USB Endpoint.  See the USB Specification at <a href="http://www.usb.org"TARGET="_blank">http://www.usb.org</a>.
*/
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

enum{addPacketShift = 11};  // Bits for additional packets in maxPacketField. (Table 9-13)
#define mungeMaxPacketSize(w) ((w>1024)?(((w>>(addPacketShift))+1)*(w&((1<<addPacketShift)-1))):w)

/*!
    @typedef IOUSBHIDDescriptor
    @discussion USB HID Descriptor.  See the USB HID Specification at <a href="http://www.usb.org"TARGET="_blank">http://www.usb.org</a>.  (This structure
    should have used the #pragma pack(1) compiler directive to get byte alignment.
*/
struct IOUSBHIDDescriptor {
	UInt8 			descLen;
	UInt8 			descType;
	UInt16 			descVersNum;
	UInt8 			hidCountryCode;
	UInt8 			hidNumDescriptors;
	UInt8 			hidDescriptorType;
	UInt8 			hidDescriptorLengthLo;
	UInt8 			hidDescriptorLengthHi;
};
typedef struct IOUSBHIDDescriptor	IOUSBHIDDescriptor;
typedef IOUSBHIDDescriptor *IOUSBHIDDescriptorPtr;

/*!
    @typedef IOUSBHIDReportDesc
    @discussion USB HID Report Descriptor header.  See the USB HID Specification at <a href="http://www.usb.org"TARGET="_blank">http://www.usb.org</a>.  (This structure
    should have used the #pragma pack(1) compiler directive to get byte alignment.
*/
struct IOUSBHIDReportDesc {
	UInt8 			hidDescriptorType;
	UInt8 			hidDescriptorLengthLo;	
	UInt8 			hidDescriptorLengthHi;
};
typedef struct IOUSBHIDReportDesc	IOUSBHIDReportDesc;
typedef IOUSBHIDReportDesc *		IOUSBHIDReportDescPtr;

/*!
    @typedef IOUSBDeviceQualifierDescriptor
    @discussion USB Device Qualifier Descriptor.  See the USB Specification at <a href="http://www.usb.org"TARGET="_blank">http://www.usb.org</a>.
*/
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
#pragma options align=reset

/*!
    @typedef IOUSBDFUDescriptor
    @discussion USB Device Firmware Update Descriptor.  See the USB Device Firmware Update Specification at <a href="http://www.usb.org"TARGET="_blank">http://www.usb.org</a>.
*/
#pragma pack(1)
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

/*!
@typedef IOUSBInterfaceAssociationDescriptor
 @discussion USB Inerface Association Descriptor.  ECN to the USB 2.0 Spec.  See the USB Specification at <a href="http://www.usb.org"TARGET="_blank">http://www.usb.org</a>.
 */
#pragma pack(1)
struct IOUSBInterfaceAssociationDescriptor
{
    UInt8 			bLength;
    UInt8 			bDescriptorType;
    UInt8 			bFirstInterface;
    UInt8 			bInterfaceCount;
    UInt8 			bFunctionClass;
    UInt8 			bFunctionSubClass;
    UInt8 			bFunctionProtocol;
    UInt8			iFunction;
};
typedef struct IOUSBInterfaceAssociationDescriptor	IOUSBInterfaceAssociationDescriptor;
typedef IOUSBInterfaceAssociationDescriptor *	IOUSBInterfaceAssociationDescriptorPtr;
#pragma options align=reset

/*!
    @typedef USBStatus
    @discussion Type used to get a DeviceStatus as a single quantity.
*/
typedef UInt16				USBStatus;
typedef USBStatus *			USBStatusPtr;

// These constants are obsolete
//
enum {
    kIOUSBAnyClass	= 0xFFFF,
    kIOUSBAnySubClass	= 0xFFFF,
    kIOUSBAnyProtocol	= 0xFFFF,
    kIOUSBAnyVendor	= 0xFFFF,
    kIOUSBAnyProduct	= 0xFFFF
};

// This structure are obsolete
//
typedef struct IOUSBMatch {
    UInt16	usbClass;
    UInt16	usbSubClass;
    UInt16	usbProtocol;
    UInt16	usbVendor;
    UInt16	usbProduct;
} IOUSBMatch;

/*!
    @typedef IOUSBFindEndpointRequest
    @discussion Struct used to find endpoints of an interface
    type and direction are used to match endpoints,
    type, direction, maxPacketSize and interval are updated
    with the properties of the found endpoint.
    @field type Type of endpoint: kUSBControl, kUSBIsoc, kUSBBulk, kUSBInterrupt, kUSBAnyType.  If kUSBAnyType is specified, this field is treated as a don't care.
    @field direction Direction of endpoint: kUSBOut, kUSBIn, kUSBAnyDirn.   If kUSBAnyDirn is specified, this field is treated as a don't care.
    @field maxPacketSize maximum packet size of endpoint.
    @field interval Polling interval in mSec for endpoint.
*/
typedef struct {
	UInt8 type;	
	UInt8 direction;
    UInt16 maxPacketSize;
    UInt8 interval;
} IOUSBFindEndpointRequest;

/*!
    @struct IOUSBDevRequest
    @discussion Parameter block for control requests, using a simple pointer
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
    UInt8       bmRequestType;
    UInt8       bRequest;
    UInt16      wValue;
    UInt16      wIndex;
    UInt16      wLength;
    void *      pData;
    UInt32      wLenDone;
} IOUSBDevRequest;
typedef IOUSBDevRequest * IOUSBDeviceRequestPtr;

/*!
    @struct IOUSBDevRequestTO
    @discussion Parameter block for control requests with timeouts, using a simple pointer
    for the data to be transferred.  Same as a IOUSBDevRequest except for the two extra timeout fields.
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
	@field noDataTimeout Specifies a time value in milliseconds. Once the request is queued on the bus, if no data is transferred in this amount of time, the request will be aborted and returned.
	@field completionTimeout Specifies a time value in milliseconds. Once the request is queued on the bus, if the entire request is not completed in this amount of time, the request will be aborted and returned 
*/
typedef struct {
    UInt8       bmRequestType;
    UInt8       bRequest;
    UInt16      wValue;
    UInt16      wIndex;
    UInt16      wLength;
    void *      pData;
    UInt32      wLenDone;
    UInt32      noDataTimeout;
    UInt32      completionTimeout;
} IOUSBDevRequestTO;

/*!
    @enum Default timeout values
    @discussion default values used for data and completion timeouts.
*/
enum
{
    kUSBDefaultControlNoDataTimeoutMS = 5000,
    kUSBDefaultControlCompletionTimeoutMS = 0
};

// Internal structure to pass parameters between IOUSBLib and UserClient
//
typedef struct
{
    UInt32      pipeRef;
    void *      buf;
    UInt32      size;
    UInt32      noDataTimeout;
    UInt32      completionTimeout;
} IOUSBBulkPipeReq;


#if KERNEL
/*!
    @struct IOUSBDevRequestDesc
    @discussion Parameter block for control requests, using a memory descriptor
    for the data to be transferred.  Only available in the kernel.
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
    UInt8                   bmRequestType;
    UInt8                   bRequest;
    UInt16                  wValue;
    UInt16                  wIndex;
    UInt16                  wLength;
    IOMemoryDescriptor *    pData;
    UInt32                  wLenDone;
} IOUSBDevRequestDesc;


/*!
    @enum IOOptionBits
    @discussion Parameter passed to an IOService::open() call.
    @constant kIOUSBInterfaceOpenAlt Open the alternate interface specified when creating the interface.
*/
enum {
    kIOUSBInterfaceOpenAlt	= 0x00010000
};

#endif

// Internal structure to pass parameters between IOUSBLib and UserClient
//
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

// Internal structure to pass parameters between IOUSBLib and UserClient
//
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

// Internal structure to pass parameters between IOUSBLib and UserClient
//
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

// Internal structure to pass parameters between IOUSBLib and UserClient
//
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


/*!
    @struct IOUSBGetFrameStruct
    @discussion Structure used from user space to return the frame number and a timestamp on when the frame register was read.
    @field frame frame number
    @field timeStamp  AbsoluteTime when the frame was updated
*/
typedef struct {
    UInt64	 frame;
    AbsoluteTime timeStamp;
} IOUSBGetFrameStruct;


/*!
    @struct IOUSBFindInterfaceRequest
    @discussion Structure used with FindNextInterface.
*/
typedef struct {
    UInt16	bInterfaceClass;		// requested class
    UInt16 	bInterfaceSubClass;		// requested subclass
    UInt16 	bInterfaceProtocol;		// requested protocol
    UInt16	bAlternateSetting;		// requested alt setting
} IOUSBFindInterfaceRequest;

/*!
    @enum kIOUSBFindInterfaceDontCare
    @discussion Constant that can be used for the fields of IOUSBFindInterfaceRequest to specify that they should not be matched. 
*/
enum {
        kIOUSBFindInterfaceDontCare		= 0xFFFF
        };

/*!
    @enum kIOUSBFindInterfaceDontCare
    @discussion USB Vendor ID for Apple Computer, Inc. 
*/
enum {
	kIOUSBVendorIDAppleComputer		= 0x05AC
        };

/*!
    @enum USBDeviceSpeed
    @discussion Returns the speed of a particular USB device. 
    @constant	kUSBDeviceSpeedLow	The device a low speed device.
    @constant	kUSBDeviceSpeedFull	The device a full speed device.
    @constant	kUSBDeviceSpeedHigh	The device a high speed device.
*/
enum {
        kUSBDeviceSpeedLow		= 0,
        kUSBDeviceSpeedFull		= 1,
        kUSBDeviceSpeedHigh		= 2
        };

/*!
    @enum MicrosecondsInFrame
    @discussion Returns the number of microseconds in a USB frame. 
    @constant	kUSBFullSpeedMicrosecondsInFrame	The device is attached to a bus running at full speed (1 ms / frame).
    @constant	kUSBHighSpeedMicrosecondsInFrame	The device is attached to a bus running at high speed (125 microseconds / frame).
*/
enum {
    kUSBFullSpeedMicrosecondsInFrame		= 1000,	
    kUSBHighSpeedMicrosecondsInFrame		= 125
};

//  During low latency transfers, the stack will set the frStatus for each frame to this value.  A client can check that to see if the transfer has completed.  We set the frStatus to a 
//  valid return code when the transfer completes.
//
enum {
        kUSBLowLatencyIsochTransferKey	= 'llit'	// Set frStatus field of first frame in isoch transfer to designate as low latency
    };
    
// This structure is DEPRECATED.  See the LowLatencyUserBufferInfoV2  
//
typedef struct LowLatencyUserBufferInfo LowLatencyUserBufferInfo;

struct LowLatencyUserBufferInfo {
    UInt32				cookie;
    void *				bufferAddress;
    IOByteCount			bufferSize;
    UInt32				bufferType;
    Boolean				isPrepared;
    LowLatencyUserBufferInfo *	nextBuffer;
};

// This structure is used to pass information for the low latency calls between user space and the kernel.  
//
typedef struct LowLatencyUserBufferInfoV2 LowLatencyUserBufferInfoV2;

struct LowLatencyUserBufferInfoV2 
{
    UInt32							cookie;
    void *							bufferAddress;
    IOByteCount						bufferSize;
    UInt32							bufferType;
    Boolean							isPrepared;
	void *							mappedUHCIAddress;
    LowLatencyUserBufferInfoV2 *	nextBuffer;
};


/*!
    @enum USBLowLatencyBufferType
    @discussion Used to specify what kind of buffer to create when calling LowLatencyCreateBuffer(). 
    @constant	kUSBLowLatencyWriteBuffer	The buffer will be used to write data out to a device.
    @constant	kUSBLowLatencyReadBuffer	The buffer will be used to read data from a device.
    @constant	kUSBLowLatencyFrameListBuffer	The buffer will be used for a low latency isoch frame list.
*/
typedef enum {
    kUSBLowLatencyWriteBuffer 		= 0,
    kUSBLowLatencyReadBuffer		= 1,
    kUSBLowLatencyFrameListBuffer	= 2
} USBLowLatencyBufferType;

// USB User Notification Types
//
enum {
    kUSBNoUserNotificationType			= 0,
    kUSBNotEnoughPowerNotificationType		= 1,
    kUSBIndividualOverCurrentNotificationType	= 2,
    kUSBGangOverCurrentNotificationType		= 3
};

/*!
    @defined Property Definitions
    @discussion Useful property names in USB land. 
*/
#define kUSBDevicePropertySpeed                 "Device Speed"
#define kUSBDevicePropertyBusPowerAvailable     "Bus Power Available"
#define kUSBDevicePropertyAddress               "USB Address"
#define kUSBDevicePropertyLocationID            "locationID"
#define kUSBProductIDMask						"idProductMask"
#define kUSBPreferredConfiguration				"Preferred Configuration"
#define kUSBSuspendPort							"kSuspendPort"
#define kUSBExpressCardCantWake					"ExpressCardCantWake"
#define kUSBControllerNeedsContiguousMemoryForIsoch	"Need contiguous memory for isoch"
/*!
@enum USBReEnumerateOptions
 @discussion Options used when calling ReEnumerateDevice. 
 @constant	kUSBAddExtraResetTimeBit	Setting this bit will cause the Hub driver to wait 100ms before addressing the device after the reset following the re-enumeration.
 */
typedef enum {
    kUSBAddExtraResetTimeBit 		= 31,
    kUSBAddExtraResetTimeMask		= ( 1 << kUSBAddExtraResetTimeBit)
} USBReEnumerateOptions;


#ifdef __cplusplus
}       
#endif

#endif /* _USB_H */

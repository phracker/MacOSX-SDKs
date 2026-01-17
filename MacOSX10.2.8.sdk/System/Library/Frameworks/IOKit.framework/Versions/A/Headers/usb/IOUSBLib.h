/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved. 
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
#ifndef _IOUSBLIB_H
#define _IOUSBLIB_H

#include <IOKit/usb/USB.h>
#include <IOKit/IOKitLib.h>

#include <CoreFoundation/CFRunLoop.h>
#include <CoreFoundation/CFPlugIn.h>
#if COREFOUNDATION_CFPLUGINCOM_SEPARATE
#include <CoreFoundation/CFPlugInCOM.h>
#endif

#include <sys/cdefs.h>

__BEGIN_DECLS

// 9dc7b780-9ec0-11d4-a54f-000a27052861
#define kIOUSBDeviceUserClientTypeID CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0x9d, 0xc7, 0xb7, 0x80, 0x9e, 0xc0, 0x11, 0xD4,			\
    0xa5, 0x4f, 0x00, 0x0a, 0x27, 0x05, 0x28, 0x61)

// 2d9786c6-9ef3-11d4-ad51-000a27052861
#define kIOUSBInterfaceUserClientTypeID CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0x2d, 0x97, 0x86, 0xc6, 0x9e, 0xf3, 0x11, 0xD4,			\
    0xad, 0x51, 0x00, 0x0a, 0x27, 0x05, 0x28, 0x61)

// 4547a8aa-9ef3-11d4-a9bd-000a27052861
#define kIOUSBFactoryID CFUUIDGetConstantUUIDWithBytes(NULL,		\
    0x45, 0x47, 0xa8, 0xaa, 0x9e, 0xf3, 0x11, 0xD4,			\
    0xa9, 0xbd, 0x00, 0x0a, 0x27, 0x05, 0x28, 0x61)

// 5c8187d0-9ef3-11d4-8b45-000a27052861
#define kIOUSBDeviceInterfaceID CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0x5c, 0x81, 0x87, 0xd0, 0x9e, 0xf3, 0x11, 0xD4,			\
    0x8b, 0x45, 0x00, 0x0a, 0x27, 0x05, 0x28, 0x61)

// 73c97ae8-9ef3-11d4-b1d0-000a27052861
#define kIOUSBInterfaceInterfaceID CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0x73, 0xc9, 0x7a, 0xe8, 0x9e, 0xf3, 0x11, 0xD4,			\
    0xb1, 0xd0, 0x00, 0x0a, 0x27, 0x05, 0x28, 0x61)

// 152FC496-4891-11D5-9D52-000A27801E86
#define kIOUSBDeviceInterfaceID182 CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0x15, 0x2f, 0xc4, 0x96, 0x48, 0x91, 0x11, 0xD5,			\
    0x9d, 0x52, 0x00, 0x0a, 0x27, 0x80, 0x1e, 0x86)

// 3C9EE1EB-2402-11B2-8E7E-000A27801E86
#define kIOUSBDeviceInterfaceID187 CFUUIDGetConstantUUIDWithBytes(NULL, \
    0x3C, 0x9E, 0xE1, 0xEB, 0x24, 0x02, 0x11, 0xB2, 			\
    0x8E, 0x7E, 0x00, 0x0A, 0x27, 0x80, 0x1E, 0x86)

// C809B8D8-0884-11D7-BB96-0003933E3E3E
#define kIOUSBDeviceInterfaceID197 CFUUIDGetConstantUUIDWithBytes(NULL, \
    0xC8, 0x09, 0xB8, 0xD8, 0x08, 0x84, 0x11, 0xD7, 			\
    0xBB, 0x96, 0x00, 0x03, 0x93, 0x3E, 0x3E, 0x3E)


// 4923AC4C-4896-11D5-9208-000A27801E86
#define kIOUSBInterfaceInterfaceID182 CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0x49, 0x23, 0xac, 0x4c, 0x48, 0x96, 0x11, 0xD5,				\
    0x92, 0x08, 0x00, 0x0a, 0x27, 0x80, 0x1e, 0x86)

// 1C438356-74C4-11D5-92E6-000A27801E86
#define kIOUSBInterfaceInterfaceID183 CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0x1c, 0x43, 0x83, 0x56, 0x74, 0xc4, 0x11, 0xD5,				\
    0x92, 0xe6, 0x00, 0x0a, 0x27, 0x80, 0x1e, 0x86)

// 8FDB8455-74A6-11D6-97B1-003065D3608E
#define kIOUSBInterfaceInterfaceID190 CFUUIDGetConstantUUIDWithBytes(NULL,	\
    0x8f, 0xdb, 0x84, 0x55, 0x74, 0xa6, 0x11, 0xD6,				\
    0x97, 0xb1, 0x00, 0x30, 0x65, 0xd3, 0x60, 0x8e)

// 6C798A6E-D6E9-11D6-ADD6-0003933E3E3E
#define kIOUSBInterfaceInterfaceID192 CFUUIDGetConstantUUIDWithBytes(NULL, 	\
    0x6C, 0x79, 0x8A, 0x6E, 0xD6, 0xE9, 0x11, 0xD6, 				\
    0xAD, 0xD6, 0x00, 0x03, 0x93, 0x3E, 0x3E, 0x3E)

// C63D3C92-0884-11D7-9692-0003933E3E3E
#define kIOUSBInterfaceInterfaceID197 CFUUIDGetConstantUUIDWithBytes(NULL, 	\
    0xC6, 0x3D, 0x3C, 0x92, 0x08, 0x84, 0x11, 0xD7,				\
    0x96, 0x92, 0x00, 0x03, 0x93, 0x3E, 0x3E, 0x3E)
//
// DeviceInterface Functions available in version 1.8 (10.0) and 1.8.1 (10.0.1) of Mac OS X
//
#define IOUSBDEVICE_FUNCS_180	\
    IOReturn (*CreateDeviceAsyncEventSource)(void *self, CFRunLoopSourceRef *source); \
    CFRunLoopSourceRef (*GetDeviceAsyncEventSource)(void *self); \
    IOReturn (*CreateDeviceAsyncPort)(void *self, mach_port_t *port); \
    mach_port_t (*GetDeviceAsyncPort)(void *self); \
    IOReturn (*USBDeviceOpen)(void *self); \
    IOReturn (*USBDeviceClose)(void *self); \
    IOReturn (*GetDeviceClass)(void *self, UInt8 *devClass); \
    IOReturn (*GetDeviceSubClass)(void *self, UInt8 *devSubClass); \
    IOReturn (*GetDeviceProtocol)(void *self, UInt8 *devProtocol); \
    IOReturn (*GetDeviceVendor)(void *self, UInt16 *devVendor); \
    IOReturn (*GetDeviceProduct)(void *self, UInt16 *devProduct); \
    IOReturn (*GetDeviceReleaseNumber)(void *self, UInt16 *devRelNum); \
    IOReturn (*GetDeviceAddress)(void *self, USBDeviceAddress *addr); \
    IOReturn (*GetDeviceBusPowerAvailable)(void *self, UInt32 *powerAvailable); \
    IOReturn (*GetDeviceSpeed)(void *self, UInt8 *devSpeed); \
    IOReturn (*GetNumberOfConfigurations)(void *self, UInt8 *numConfig); \
    IOReturn (*GetLocationID)(void *self, UInt32 *locationID); \
    IOReturn (*GetConfigurationDescriptorPtr)(void *self, UInt8 configIndex, IOUSBConfigurationDescriptorPtr *desc); \
    IOReturn (*GetConfiguration)(void *self, UInt8 *configNum); \
    IOReturn (*SetConfiguration)(void *self, UInt8 configNum); \
    IOReturn (*GetBusFrameNumber)(void *self, UInt64 *frame, AbsoluteTime *atTime); \
    IOReturn (*ResetDevice)(void *self); \
    IOReturn (*DeviceRequest)(void *self, IOUSBDevRequest *req); \
    IOReturn (*DeviceRequestAsync)(void *self, IOUSBDevRequest *req, IOAsyncCallback1 callback, void *refCon); \
    IOReturn (*CreateInterfaceIterator)(void *self, IOUSBFindInterfaceRequest *req, io_iterator_t *iter)
//-----------------------------------------------------------------------------------------
// END OF DeviceInterface Functions available in version 1.8 (10.0) and 1.8.1 (10.0.1) of Mac OS X
//-----------------------------------------------------------------------------------------
//
// DeviceInterface Functions available in version 1.8.2 Mac OS X
//
#define IOUSBDEVICE_FUNCS_182 \
    IOReturn (*USBDeviceOpenSeize)(void *self); \
    IOReturn (*DeviceRequestTO)(void *self, IOUSBDevRequestTO *req); \
    IOReturn (*DeviceRequestAsyncTO)(void *self, IOUSBDevRequestTO *req, IOAsyncCallback1 callback, void *refCon); \
    IOReturn (*USBDeviceSuspend)(void *self, Boolean suspend); \
    IOReturn (*USBDeviceAbortPipeZero)(void *self); \
    IOReturn (*USBGetManufacturerStringIndex)(void *self, UInt8 *msi); \
    IOReturn (*USBGetProductStringIndex)(void *self, UInt8 *psi); \
    IOReturn (*USBGetSerialNumberStringIndex)(void *self, UInt8 *snsi)

//-----------------------------------------------------------------------------------------
// END OF DeviceInterface Functions available in version 1.8.2 (10.1) of Mac OS X
//-----------------------------------------------------------------------------------------
//
// DeviceInterface Functions available in version 1.8.7 Mac OS X
//
#define IOUSBDEVICE_FUNCS_187 \
IOReturn (*USBDeviceReEnumerate)(void *self, UInt32 options)

//-----------------------------------------------------------------------------------------
// END OF DeviceInterface Functions available in version 1.8.7 (10.1.X) of Mac OS X
//-----------------------------------------------------------------------------------------
// DeviceInterface Functions available in version 1.9.7 Mac OS X
//
#define IOUSBDEVICE_FUNCS_197 \
IOReturn (*GetBusMicroFrameNumber)(void *self, UInt64 *microFrame, AbsoluteTime *atTime); \
IOReturn (*GetIOUSBLibVersion)(void *self, NumVersion *ioUSBLibVersion, NumVersion *usbFamilyVersion)

//-----------------------------------------------------------------------------------------
// END OF DeviceInterface Functions available in version 1.9.7
//-----------------------------------------------------------------------------------------

typedef struct IOUSBDeviceStruct {
    IUNKNOWN_C_GUTS;
    IOUSBDEVICE_FUNCS_180;
} IOUSBDeviceInterface;


typedef struct IOUSBDeviceStruct182 {
    IUNKNOWN_C_GUTS;
    IOUSBDEVICE_FUNCS_180;
    IOUSBDEVICE_FUNCS_182;
} IOUSBDeviceInterface182;


typedef struct IOUSBDeviceStruct187 {
    IUNKNOWN_C_GUTS;
    IOUSBDEVICE_FUNCS_180;
    IOUSBDEVICE_FUNCS_182;
    IOUSBDEVICE_FUNCS_187;
} IOUSBDeviceInterface187;

typedef struct IOUSBDeviceStruct197 {
    IUNKNOWN_C_GUTS;
    IOUSBDEVICE_FUNCS_180;
    IOUSBDEVICE_FUNCS_182;
    IOUSBDEVICE_FUNCS_187;
    IOUSBDEVICE_FUNCS_197;
} IOUSBDeviceInterface197;


//
// InterfaceInterface Functions available in version 1.8 (10.0) and 1.8.1 (10.0.1) of Mac OS X
//
#define IOUSBINTERFACE_FUNCS_180 \
    IOReturn (*CreateInterfaceAsyncEventSource)(void *self, CFRunLoopSourceRef *source); \
    CFRunLoopSourceRef (*GetInterfaceAsyncEventSource)(void *self); \
    IOReturn (*CreateInterfaceAsyncPort)(void *self, mach_port_t *port); \
    mach_port_t (*GetInterfaceAsyncPort)(void *self); \
    IOReturn (*USBInterfaceOpen)(void *self); \
    IOReturn (*USBInterfaceClose)(void *self); \
    IOReturn (*GetInterfaceClass)(void *self, UInt8 *intfClass); \
    IOReturn (*GetInterfaceSubClass)(void *self, UInt8 *intfSubClass); \
    IOReturn (*GetInterfaceProtocol)(void *self, UInt8 *intfProtocol); \
    IOReturn (*GetDeviceVendor)(void *self, UInt16 *devVendor); \
    IOReturn (*GetDeviceProduct)(void *self, UInt16 *devProduct); \
    IOReturn (*GetDeviceReleaseNumber)(void *self, UInt16 *devRelNum); \
    IOReturn (*GetConfigurationValue)(void *self, UInt8 *configVal); \
    IOReturn (*GetInterfaceNumber)(void *self, UInt8 *intfNumber); \
    IOReturn (*GetAlternateSetting)(void *self, UInt8 *intfAltSetting); \
    IOReturn (*GetNumEndpoints)(void *self, UInt8 *intfNumEndpoints); \
    IOReturn (*GetLocationID)(void *self, UInt32 *locationID); \
    IOReturn (*GetDevice)(void *self, io_service_t *device); \
    IOReturn (*SetAlternateInterface)(void *self, UInt8 alternateSetting); \
    IOReturn (*GetBusFrameNumber)(void *self, UInt64 *frame, AbsoluteTime *atTime); \
    IOReturn (*ControlRequest)(void *self, UInt8 pipeRef, IOUSBDevRequest *req); \
    IOReturn (*ControlRequestAsync)(void *self, UInt8 pipeRef, IOUSBDevRequest *req, IOAsyncCallback1 callback, void *refCon); \
    IOReturn (*GetPipeProperties)(void *self, UInt8 pipeRef, UInt8 *direction, UInt8 *number, UInt8 *transferType, UInt16 *maxPacketSize, UInt8 *interval); \
    IOReturn (*GetPipeStatus)(void *self, UInt8 pipeRef); \
    IOReturn (*AbortPipe)(void *self, UInt8 pipeRef); \
    IOReturn (*ResetPipe)(void *self, UInt8 pipeRef); \
    IOReturn (*ClearPipeStall)(void *self, UInt8 pipeRef); \
    IOReturn (*ReadPipe)(void *self, UInt8 pipeRef, void *buf, UInt32 *size); \
    IOReturn (*WritePipe)(void *self, UInt8 pipeRef, void *buf, UInt32 size); \
    IOReturn (*ReadPipeAsync)(void *self, UInt8 pipeRef, void *buf, UInt32 size, IOAsyncCallback1 callback, void *refcon); \
    IOReturn (*WritePipeAsync)(void *self, UInt8 pipeRef, void *buf, UInt32 size, IOAsyncCallback1 callback, void *refcon); \
    IOReturn (*ReadIsochPipeAsync)(void *self, UInt8 pipeRef, void *buf, UInt64 frameStart, UInt32 numFrames, IOUSBIsocFrame *frameList, \
                                  IOAsyncCallback1 callback, void *refcon); \
    IOReturn (*WriteIsochPipeAsync)(void *self, UInt8 pipeRef, void *buf, UInt64 frameStart, UInt32 numFrames, IOUSBIsocFrame *frameList, \
                                  IOAsyncCallback1 callback, void *refcon)

//-----------------------------------------------------------------------------------------
// END OF InterfaceInterface Functions available in version 1.8 (10.0) and 1.8.1 (10.0.1) of Mac OS X
//-----------------------------------------------------------------------------------------
//
// InterfaceInterface Functions available in version 1.8.2 Mac OS X
//
#define IOUSBINTERFACE_FUNCS_182 \
    IOReturn (*ControlRequestTO)(void *self, UInt8 pipeRef, IOUSBDevRequestTO *req); \
    IOReturn (*ControlRequestAsyncTO)(void *self, UInt8 pipeRef, IOUSBDevRequestTO *req, IOAsyncCallback1 callback, void *refCon); \
    IOReturn (*ReadPipeTO)(void *self, UInt8 pipeRef, void *buf, UInt32 *size, UInt32 noDataTimeout, UInt32 completionTimeout); \
    IOReturn (*WritePipeTO)(void *self, UInt8 pipeRef, void *buf, UInt32 size, UInt32 noDataTimeout, UInt32 completionTimeout); \
    IOReturn (*ReadPipeAsyncTO)(void *self, UInt8 pipeRef, void *buf, UInt32 size, UInt32 noDataTimeout, UInt32 completionTimeout, IOAsyncCallback1 callback, void *refcon); \
    IOReturn (*WritePipeAsyncTO)(void *self, UInt8 pipeRef, void *buf, UInt32 size, UInt32 noDataTimeout, UInt32 completionTimeout, IOAsyncCallback1 callback, void *refcon); \
    IOReturn (*USBInterfaceGetStringIndex)(void *self, UInt8 *si)
//-----------------------------------------------------------------------------------------
// END OF InterfaceInterface Functions available in version 1.8.2 Mac OS X
//-----------------------------------------------------------------------------------------
//
// InterfaceInterface Functions available in version 1.8.3 Mac OS X
//
#define IOUSBINTERFACE_FUNCS_183 \
    IOReturn (*USBInterfaceOpenSeize)(void *self)
//-----------------------------------------------------------------------------------------
// END OF InterfaceInterface Functions available in version 1.8.3 Mac OS X
//-----------------------------------------------------------------------------------------
//
// InterfaceInterface Functions available in version 1.9.0 Mac OS X
//
#define IOUSBINTERFACE_FUNCS_190 \
    IOReturn (*ClearPipeStallBothEnds)(void *self, UInt8 pipeRef); \
    IOReturn (*SetPipePolicy)(void *self, UInt8 pipeRef, UInt16 maxPacketSize, UInt8 maxInterval); \
    IOReturn (*GetBandwidthAvailable)(void *self, UInt32 *bandwidth); \
    IOReturn (*GetEndpointProperties)(void *self, UInt8 alternateSetting, UInt8 endpointNumber, UInt8 direction, UInt8 *transferType, UInt16 *maxPacketSize, UInt8 *interval)
//-----------------------------------------------------------------------------------------
// END OF InterfaceInterface Functions available in version 1.9.0 Mac OS X
//-----------------------------------------------------------------------------------------
// InterfaceInterface Functions available in version 1.9.2 Mac OS X
//
#define IOUSBINTERFACE_FUNCS_192 \
IOReturn (*LowLatencyReadIsochPipeAsync)(void *self, UInt8 pipeRef, void *buf, UInt64 frameStart, UInt32 numFrames, UInt32 updateFrequency, IOUSBLowLatencyIsocFrame *frameList, \
                                         IOAsyncCallback1 callback, void *refcon); \
IOReturn (*LowLatencyWriteIsochPipeAsync)(void *self, UInt8 pipeRef, void *buf, UInt64 frameStart, UInt32 numFrames, UInt32 updateFrequency, IOUSBLowLatencyIsocFrame *frameList, \
                                          IOAsyncCallback1 callback, void *refcon); \
IOReturn (*LowLatencyCreateBuffer)(void * self, void **buffer, IOByteCount size, UInt32 bufferType); \
IOReturn (*LowLatencyDestroyBuffer) (void * self, void * buffer )
//-----------------------------------------------------------------------------------------
// END OF InterfaceInterface Functions available in version 1.9.2 Mac OS X
//-----------------------------------------------------------------------------------------
// InterfaceInterface Functions available in version 1.9.7 Mac OS X
//
#define IOUSBINTERFACE_FUNCS_197 \
IOReturn (*GetBusMicroFrameNumber)(void *self, UInt64 *microFrame, AbsoluteTime *atTime); \
IOReturn (*GetFrameListTime)(void *self, UInt32 *microsecondsInFrame); \
IOReturn (*GetIOUSBLibVersion)(void *self, NumVersion *ioUSBLibVersion, NumVersion *usbFamilyVersion)

//-----------------------------------------------------------------------------------------
// END OF InterfaceInterface Functions available in version 1.9.7 Mac OS X
//-----------------------------------------------------------------------------------------

typedef struct IOUSBInterfaceStruct {
    IUNKNOWN_C_GUTS;
    IOUSBINTERFACE_FUNCS_180;
} IOUSBInterfaceInterface;

typedef struct IOUSBInterfaceStruct182 {
    IUNKNOWN_C_GUTS;
    IOUSBINTERFACE_FUNCS_180;
    IOUSBINTERFACE_FUNCS_182;
} IOUSBInterfaceInterface182;

typedef struct IOUSBInterfaceStruct183 {
    IUNKNOWN_C_GUTS;
    IOUSBINTERFACE_FUNCS_180;
    IOUSBINTERFACE_FUNCS_182;
    IOUSBINTERFACE_FUNCS_183;
} IOUSBInterfaceInterface183;

typedef struct IOUSBInterfaceStruct190 {
    IUNKNOWN_C_GUTS;
    IOUSBINTERFACE_FUNCS_180;
    IOUSBINTERFACE_FUNCS_182;
    IOUSBINTERFACE_FUNCS_183;
    IOUSBINTERFACE_FUNCS_190;
} IOUSBInterfaceInterface190;

typedef struct IOUSBInterfaceStruct192 {
    IUNKNOWN_C_GUTS;
    IOUSBINTERFACE_FUNCS_180;
    IOUSBINTERFACE_FUNCS_182;
    IOUSBINTERFACE_FUNCS_183;
    IOUSBINTERFACE_FUNCS_190;
    IOUSBINTERFACE_FUNCS_192;
} IOUSBInterfaceInterface192;

typedef struct IOUSBInterfaceStruct197 {
    IUNKNOWN_C_GUTS;
    IOUSBINTERFACE_FUNCS_180;
    IOUSBINTERFACE_FUNCS_182;
    IOUSBINTERFACE_FUNCS_183;
    IOUSBINTERFACE_FUNCS_190;
    IOUSBINTERFACE_FUNCS_192;
    IOUSBINTERFACE_FUNCS_197;
} IOUSBInterfaceInterface197;

#define kIOUSBDeviceClassName		"IOUSBDevice"
#define kIOUSBInterfaceClassName	"IOUSBInterface"

__END_DECLS

#endif /* ! _IOUSBLIB_H */

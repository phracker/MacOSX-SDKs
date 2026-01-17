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
#ifndef _IOKIT_IOUSBCOMMAND_H
#define _IOKIT_IOUSBCOMMAND_H

#include <IOKit/IOCommand.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/usb/USB.h>

/*
 * USB Command
 * This is the command block for a USB command to be queued on the
 * Command Gate of the WorkLoop.  Although the actual work of creating
 * the command and enqueueing it is done for them via the deviceRequest,
 * read, and write methods, this is the primary way that devices will get
 * work done.
 * Note: This is private to IOUSBController and should be moved to a
 * private header.
 */

typedef enum {
    DEVICE_REQUEST,	// Device request using pointer
    READ,
    WRITE,
    CREATE_EP,
    DELETE_EP,
    DEVICE_REQUEST_DESC	// Device request using descriptor
} usbCommand;



class IOUSBCommand : public IOCommand
{
    OSDeclareAbstractStructors(IOUSBCommand)

protected:
    usbCommand			_selector;
    IOUSBDeviceRequestPtr	_request;
    USBDeviceAddress		_address;
    UInt8			_endpoint;
    UInt8			_direction;
    UInt8			_type;
    bool			_bufferRounding;
    IOMemoryDescriptor 		*_buffer;
    IOUSBCompletion		_uslCompletion;
    IOUSBCompletion		_clientCompletion;
    UInt32			_dataRemaining;		// For Control transfers
    UInt8			_stage;			// For Control transfers
    IOReturn			_status;
    IOMemoryDescriptor 		*_origBuffer;
    IOUSBCompletion		_disjointCompletion;
    IOByteCount			_dblBufLength;
    UInt32			_noDataTimeout;
    UInt32			_completionTimeout;
    UInt32			_UIMScratch[10];
    
    struct ExpansionData { /* */ };
    ExpansionData * 		_expansionData;
    
public:

    // static constructor
    static inline IOUSBCommand *NewCommand(void) {return new IOUSBCommand;}

    // accessor methods
    inline void SetSelector(usbCommand sel) {_selector = sel;}
    inline void SetRequest(IOUSBDeviceRequestPtr req) {_request = req;}
    inline void SetAddress(USBDeviceAddress addr) {_address = addr;}
    inline void SetEndpoint(UInt8 ep) {_endpoint = ep;}
    inline void SetDirection(UInt8 dir) {_direction = dir;}
    inline void SetType(UInt8 type) {_type = type;}
    inline void SetBufferRounding(bool br) { _bufferRounding = br;}
    inline void SetBuffer(IOMemoryDescriptor *buf) {_buffer = buf;}
    inline void SetUSLCompletion(IOUSBCompletion completion) {_uslCompletion = completion;}
    inline void SetClientCompletion(IOUSBCompletion completion) {_clientCompletion = completion;}
    inline void SetDataRemaining(UInt32 dr) {_dataRemaining = dr;}
    inline void SetStage(UInt8 stage) {_stage = stage;}
    inline void SetStatus(IOReturn stat) {_status = stat;}
    inline void SetOrigBuffer(IOMemoryDescriptor *buf) {_origBuffer = buf;}
    inline void SetDisjointCompletion(IOUSBCompletion completion) {_disjointCompletion = completion;}
    inline void SetDblBufLength(IOByteCount len) {_dblBufLength = len;}
    inline void SetNoDataTimeout(UInt32 to) {_noDataTimeout = to;}
    inline void SetCompletionTimeout(UInt32 to) {_completionTimeout = to;}
    inline void SetUIMScratch(UInt32 index, UInt32 value) { if (index < 10) _UIMScratch[index] = value;}
    
    inline usbCommand GetSelector(void) {return _selector;}
    inline IOUSBDeviceRequestPtr GetRequest(void) {return _request;}
    inline USBDeviceAddress GetAddress(void) {return _address;}
    inline UInt8 GetEndpoint(void) {return _endpoint;}
    inline UInt8 GetDirection(void) {return _direction;}
    inline UInt8 GetType(void) {return _type;}
    inline bool GetBufferRounding(void) {return _bufferRounding;}
    inline IOMemoryDescriptor* GetBuffer(void) {return _buffer;}
    inline IOUSBCompletion GetUSLCompletion(void) {return _uslCompletion;}
    inline IOUSBCompletion GetClientCompletion(void) {return _clientCompletion;}
    inline UInt32 GetDataRemaining(void) {return _dataRemaining;}
    inline UInt8 GetStage(void) {return _stage;}
    inline IOReturn GetStatus(void) {return _status;}
    inline IOMemoryDescriptor *GetOrigBuffer(void) {return _origBuffer;}
    inline IOUSBCompletion GetDisjointCompletion(void) {return _disjointCompletion;}
    inline IOByteCount GetDblBufLength(void) {return _dblBufLength;}
    inline UInt32 GetNoDataTimeout(void) {return _noDataTimeout;}
    inline UInt32 GetCompletionTimeout(void) {return _completionTimeout;}
    inline UInt32 GetUIMScratch(UInt32 index) {return (index < 10) ? _UIMScratch[index] : 0; }
};


class IOUSBIsocCommand : public IOCommand
{
    OSDeclareAbstractStructors(IOUSBIsocCommand)

protected:
    usbCommand			_selector;
    USBDeviceAddress		_address;
    UInt8			_endpoint;
    UInt8			_direction;
    IOMemoryDescriptor 		*_buffer;
    IOUSBIsocCompletion		_completion;
    UInt64			_startFrame;
    UInt32			_numFrames;
    IOUSBIsocFrame *		_frameList;
    IOReturn			_status;
    
    struct ExpansionData { /* */ };
    ExpansionData * 		_expansionData;

public:
    // static constructor
    static inline IOUSBIsocCommand *NewCommand(void) {return new IOUSBIsocCommand;}
    
    // accessor methods
    inline void SetSelector(usbCommand sel) {_selector = sel;}
    inline void SetAddress(USBDeviceAddress addr) {_address = addr;}
    inline void SetEndpoint(UInt8 ep) {_endpoint = ep;}
    inline void SetDirection(UInt8 dir) {_direction = dir;}
    inline void SetBuffer(IOMemoryDescriptor *buf) {_buffer = buf;}
    inline void SetCompletion(IOUSBIsocCompletion completion) {_completion = completion;}
    inline void SetStartFrame(UInt64 sf) {_startFrame = sf;}
    inline void SetNumFrames(UInt32 nf) {_numFrames = nf;}
    inline void SetFrameList(IOUSBIsocFrame *fl) {_frameList = fl;}
    inline void SetStatus(IOReturn stat) {_status = stat;}
    
    inline usbCommand GetSelector(void) {return _selector;}
    inline USBDeviceAddress GetAddress(void) {return _address;}
    inline UInt8 GetEndpoint(void) {return _endpoint;}
    inline UInt8 GetDirection(void) {return _direction;}
    inline IOMemoryDescriptor* GetBuffer(void) {return _buffer;}
    inline IOUSBIsocCompletion GetCompletion(void) {return _completion;}
    inline UInt64 GetStartFrame(void) {return _startFrame;}
    inline UInt32 GetNumFrames(void) {return _numFrames;}
    inline IOUSBIsocFrame* GetFrameList(void) {return _frameList;}
};


#endif


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
    
    struct ExpansionData
    {
        IOByteCount		_reqCount;
	IOMemoryDescriptor	*_requestMemoryDescriptor;
	IOMemoryDescriptor	*_bufferMemoryDescriptor;
	bool			_multiTransferTransaction;
	bool			_finalTransferInTransaction;
    };
    ExpansionData * 		_expansionData;
    
    // we override these OSObject method in order to allocate and release our expansion data
    virtual bool init();
    virtual void free();

public:

    // static constructor
    static IOUSBCommand *NewCommand(void);

    // accessor methods
    //
    void  			SetSelector(usbCommand sel);
    void  			SetRequest(IOUSBDeviceRequestPtr req);
    void  			SetAddress(USBDeviceAddress addr);
    void  			SetEndpoint(UInt8 ep);
    void  			SetDirection(UInt8 dir);
    void  			SetType(UInt8 type);
    void  			SetBufferRounding(bool br);
    void  			SetBuffer(IOMemoryDescriptor *buf);
    void  			SetUSLCompletion(IOUSBCompletion completion);
    void  			SetClientCompletion(IOUSBCompletion completion);
    void  			SetDataRemaining(UInt32 dr);
    void  			SetStage(UInt8 stage);
    void 			SetStatus(IOReturn stat);
    void 			SetOrigBuffer(IOMemoryDescriptor *buf);
    void 			SetDisjointCompletion(IOUSBCompletion completion);
    void 			SetDblBufLength(IOByteCount len);
    void 			SetNoDataTimeout(UInt32 to);
    void 			SetCompletionTimeout(UInt32 to);
    void 			SetUIMScratch(UInt32 index, UInt32 value);
    void 			SetReqCount(IOByteCount reqCount);
    void			SetRequestMemoryDescriptor(IOMemoryDescriptor *requestMemoryDescriptor);
    void			SetBufferMemoryDescriptor(IOMemoryDescriptor *bufferMemoryDescriptor);
    void			SetMultiTransferTransaction(bool);
    void			SetFinalTransferInTransaction(bool);
    usbCommand 			GetSelector(void);
    IOUSBDeviceRequestPtr 	GetRequest(void);
    USBDeviceAddress 		GetAddress(void);
    UInt8 			GetEndpoint(void);
    UInt8 			GetDirection(void);
    UInt8 			GetType(void);
    bool 			GetBufferRounding(void);
    IOMemoryDescriptor * 	GetBuffer(void);
    IOUSBCompletion 		GetUSLCompletion(void);
    IOUSBCompletion 		GetClientCompletion(void);
    UInt32 			GetDataRemaining(void);
    UInt8 			GetStage(void);
    IOReturn 			GetStatus(void);
    IOMemoryDescriptor *	GetOrigBuffer(void);
    IOUSBCompletion 		GetDisjointCompletion(void);
    IOByteCount 		GetDblBufLength(void);
    UInt32 			GetNoDataTimeout(void);
    UInt32 			GetCompletionTimeout(void);
    UInt32 			GetUIMScratch(UInt32 index);
    IOByteCount 		GetReqCount(void);
    IOMemoryDescriptor *	GetRequestMemoryDescriptor(void);
    IOMemoryDescriptor *	GetBufferMemoryDescriptor(void);
    bool			GetMultiTransferTransaction(void);
    bool			GetFinalTransferInTransaction(void);
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
    
    struct ExpansionData { 
    UInt32			_updateFrequency;
    };
    ExpansionData * 		_expansionData;

    // we override these OSObject method in order to allocate and release our expansion data
    virtual bool init();
    virtual void free();

public:
    // static constructor
    static IOUSBIsocCommand *NewCommand(void);
    
    // accessor methods
    void 		SetSelector(usbCommand sel) 		{_selector = sel;}
    void 		SetAddress(USBDeviceAddress addr) 	{_address = addr;}
    void 		SetEndpoint(UInt8 ep) 			{_endpoint = ep;}
    void 		SetDirection(UInt8 dir) 		{_direction = dir;}
    void 		SetBuffer(IOMemoryDescriptor *buf) 	{_buffer = buf;}
    void 		SetCompletion(IOUSBIsocCompletion completion) {_completion = completion;}
    void 		SetStartFrame(UInt64 sf) 		{_startFrame = sf;}
    void 		SetNumFrames(UInt32 nf) 		{_numFrames = nf;}
    void 		SetFrameList(IOUSBIsocFrame *fl) 	{_frameList = fl;}
    void 		SetStatus(IOReturn stat) 		{_status = stat;}
    void		SetUpdateFrequency( UInt32 fr) 		{ _expansionData->_updateFrequency = fr;}
    
    usbCommand 		GetSelector(void) 	{return _selector;}
    USBDeviceAddress 	GetAddress(void) 	{return _address;}
    UInt8 		GetEndpoint(void) 	{return _endpoint;}
    UInt8 		GetDirection(void) 	{return _direction;}
    IOMemoryDescriptor* GetBuffer(void) 	{return _buffer;}
    IOUSBIsocCompletion GetCompletion(void) 	{return _completion;}
    UInt64 		GetStartFrame(void) 	{return _startFrame;}
    UInt32 		GetNumFrames(void) 	{return _numFrames;}
    IOUSBIsocFrame* 	GetFrameList(void) 	{return _frameList;}
    UInt32		GetUpdateFrequency(void){return _expansionData->_updateFrequency; };
};


#endif


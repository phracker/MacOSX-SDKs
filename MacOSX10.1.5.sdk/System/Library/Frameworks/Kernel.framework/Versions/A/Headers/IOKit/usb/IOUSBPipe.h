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
#ifndef _IOKIT_IOUSBPIPE_H
#define _IOKIT_IOUSBPIPE_H

#include <IOKit/IOService.h>
#include <IOKit/IOMemoryDescriptor.h>

#include <IOKit/usb/USB.h>
#include <IOKit/usb/IOUSBController.h>

/*!
    @class IOUSBPipe
    @abstract The object representing an open pipe for a device.
*/
class IOUSBPipe : public OSObject
{
    OSDeclareDefaultStructors(IOUSBPipe)

protected:

    const IOUSBEndpointDescriptor *	_descriptor;
    IOUSBController::Endpoint		_endpoint;	// tidied up version of descriptor
    IOUSBController *			_controller;
    USBDeviceAddress			_address;
    UInt8 				_status;	// stalled, active

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

    virtual void free();

public:

    virtual bool InitToEndpoint(const IOUSBEndpointDescriptor *endpoint, UInt8 speed,
                                USBDeviceAddress address, IOUSBController * controller);
    static IOUSBPipe *ToEndpoint(const IOUSBEndpointDescriptor *endpoint, UInt8 speed,
                                 USBDeviceAddress address, IOUSBController * controller);

    // Controlling pipe state
    /*!
        @function status
	Get the current state of the pipe (kIOUSBPipeStalled if stalled or 0 if active).
    */
    virtual UInt8 GetStatus(void) { return(_status); }
    /*!
        @function abort
	abort a pipe, causing all outstanding I/O to complete
	with return code kIOReturnAborted
    */
    virtual IOReturn Abort(void);
    /*!
        @function reset
        reset a pipe, causing all outstanding I/O to complete
        with return code kIOReturnAborted, and clear any stall.
    */
    virtual IOReturn Reset(void);
    /*!
        @function clearStall
        clear any stall.
    */
    virtual IOReturn ClearStall(void);

    //
    // Transferring Data
    //
    
    // Transfer data over Bulk or Interrupt pipes.
    /*!
        @function read
        Read from an interrupt or bulk endpoint
        @param buffer place to put the transferred data
        @param completion describes action to take when buffer has been filled
        @param bytesRead returns total bytes read for synchronous reads
    */
    virtual IOReturn Read(IOMemoryDescriptor *	buffer,
                          IOUSBCompletion *	completion = 0,
			  IOByteCount *		bytesRead = 0);

    /*!
        @function write
        Write to an interrupt or bulk endpoint
        @param buffer place to get the transferred data
        @param completion describes action to take when buffer has been emptied
    */
    virtual IOReturn Write(IOMemoryDescriptor *	buffer,
                           IOUSBCompletion *	completion = 0);

    // Transfer data over Isochronous pipes
    /*!
        @function read
        Read from an isochronous endpoint
        @param buffer place to put the transferred data
        @param frameStart USB frame number of the frame to start transfer
	@param numFrames Number of frames to transfer
	@param frameList Bytes to transfer and result for each frame
        @param completion describes action to take when buffer has been filled
    */
    virtual IOReturn Read(IOMemoryDescriptor *	buffer,
                          UInt64 frameStart, UInt32 numFrames, IOUSBIsocFrame *frameList,
                          IOUSBIsocCompletion *	completion = 0);
    /*!
        @function write
        Write to an isochronous endpoint
        @param buffer place to get the transferred data
        @param frameStart USB frame number of the frame to start transfer
        @param numFrames Number of frames to transfer
        @param frameList Bytes to transfer and result for each frame
        @param completion describes action to take when buffer has been emptied
    */
    virtual IOReturn Write(IOMemoryDescriptor *	buffer,
                           UInt64 frameStart, UInt32 numFrames, IOUSBIsocFrame *frameList,
                           IOUSBIsocCompletion * completion = 0);

    /*!
        @function controlRequest
        Make a control request
        There are two versions of this method, one uses a simple void *
        to point to the data portion of the transfer, the other uses an
        IOMemoryDescriptor to point to the data.
        @param request parameter block for the control request
        @param completion describes action to take when the request has been executed
    */
    // Do a control request over a Control pipe, using a memory descriptor
    virtual IOReturn ControlRequest(IOUSBDevRequestDesc	*request,
                                    IOUSBCompletion	*completion = 0);

    // Do a control request over a Control pipe, using a simple buffer
    virtual IOReturn ControlRequest(IOUSBDevRequest	*request,
                                    IOUSBCompletion	*completion = 0);

/*
 *  Accessors
 */
    /*!
        @function endpoint
        returns a pointer to the Endpoint structure for the pipe.
    */
    virtual const IOUSBController::Endpoint *	GetEndpoint() { return(&_endpoint); }
    /*!
        @function endpointDescriptor
        returns the endpoint descriptor for the pipe.
    */
    virtual const IOUSBEndpointDescriptor *	GetEndpointDescriptor() { return(_descriptor); }
    /*!
        @function direction
        returns the direction of the pipe:kUSBOut/kUSBIn for a bulk or interrupt pipe,
	kUSBAnyDirn for a control pipe.
    */
    virtual UInt8 GetDirection() { return(_endpoint.direction); }
    /*!
        @function type
        returns the pipe type: kUSBControl, kUSBBulk or kUSBInterrupt.
    */
    virtual UInt8 GetType() { return(_endpoint.transferType); }
    /*!
        @function endpointNumber
        returns the endpoint number in the device that the pipe is connected to.
    */
    virtual UInt8 GetEndpointNumber() { return(_endpoint.number); }
    virtual USBDeviceAddress GetAddress() { return(_address); }
    virtual UInt16 GetMaxPacketSize() { return _endpoint.maxPacketSize; }
    virtual UInt8 GetInterval() { return (_endpoint.interval); }

    // Transfer data over Bulk pipes with timeouts.
    OSMetaClassDeclareReservedUsed(IOUSBPipe,  0);
    /*!
        @function read
        Read from an interrupt or bulk endpoint
        @param buffer place to put the transferred data
        @param completion describes action to take when buffer has been filled
        @param bytesRead returns total bytes read for synchronous reads
    */
    virtual IOReturn Read(IOMemoryDescriptor *	buffer,
			  UInt32		noDataTimeout,
			  UInt32		completionTimeout,
                          IOUSBCompletion *	completion = 0,
			  IOByteCount *		bytesRead = 0);

    OSMetaClassDeclareReservedUsed(IOUSBPipe,  1);
    /*!
        @function write
        Write to an interrupt or bulk endpoint
        @param buffer place to get the transferred data
        @param completion describes action to take when buffer has been emptied
    */
    virtual IOReturn Write(IOMemoryDescriptor *	buffer,
			   UInt32		noDataTimeout,
			   UInt32		completionTimeout,
                           IOUSBCompletion *	completion = 0);

    OSMetaClassDeclareReservedUsed(IOUSBPipe,  2);
    /*!
        @function controlRequest
        Make a control request
        There are two versions of this method, one uses a simple void *
        to point to the data portion of the transfer, the other uses an
        IOMemoryDescriptor to point to the data.
        @param request parameter block for the control request
        @param completion describes action to take when the request has been executed
    */
    // Do a control request over a Control pipe, using a memory descriptor
    virtual IOReturn ControlRequest(IOUSBDevRequestDesc	*request,
				    UInt32		noDataTimeout,
				    UInt32		completionTimeout,
                                    IOUSBCompletion	*completion = 0);

    OSMetaClassDeclareReservedUsed(IOUSBPipe,  3);
    // Do a control request over a Control pipe, using a simple buffer
    virtual IOReturn ControlRequest(IOUSBDevRequest	*request,
				    UInt32		noDataTimeout,
				    UInt32		completionTimeout,
                                    IOUSBCompletion	*completion = 0);

    OSMetaClassDeclareReservedUnused(IOUSBPipe,  4);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  5);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  6);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  7);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  8);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  9);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  10);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  11);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  12);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  13);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  14);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  15);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  16);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  17);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  18);
    OSMetaClassDeclareReservedUnused(IOUSBPipe,  19);

};

#endif /* _IOKIT_IOUSBPIPE_H */

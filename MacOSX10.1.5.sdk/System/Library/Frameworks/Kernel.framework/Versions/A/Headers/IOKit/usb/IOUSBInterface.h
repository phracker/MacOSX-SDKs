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
#ifndef _IOKIT_IOUSBINTERFACE_H
#define _IOKIT_IOUSBINTERFACE_H

#include <IOKit/IOService.h>
#include <libkern/c++/OSData.h>

#include <IOKit/usb/USB.h>
#include <IOKit/usb/IOUSBNub.h>
#include <IOKit/usb/IOUSBDevice.h>

/*!
    @class IOUSBInterface
    @abstract The object representing an interface of a device on the USB bus.
    @discussion This class provides functionality to find the pipes of an interface and
	to read the descriptors associated with an interface. When an interface is open()ed,
	all its pipes are created
*/
class IOUSBInterface : public IOUSBNub
{
    OSDeclareDefaultStructors(IOUSBInterface)

protected:
    IOUSBPipe * 			_pipeList[kUSBMaxPipes];
    const IOUSBConfigurationDescriptor *_configDesc;
    const IOUSBInterfaceDescriptor *	_interfaceDesc;
    IOUSBDevice *			_device;

    // these variable are the parsed interface descriptor
    UInt8				_bInterfaceNumber;
    UInt8				_bAlternateSetting;
    UInt8				_bNumEndpoints;
    UInt8				_bInterfaceClass;
    UInt8				_bInterfaceSubClass;
    UInt8				_bInterfaceProtocol;
    UInt8				_iInterface;

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

    // private methods
    virtual void 	ClosePipes(void);	// close all pipes (except pipe zero)
    virtual IOReturn	CreatePipes(void);	// open all pipes in the current interface/alt interface
    virtual void	SetProperties(void);	// update my property table with the correct properties		

public:
    static IOUSBInterface *withDescriptors(const IOUSBConfigurationDescriptor *cfDesc, const IOUSBInterfaceDescriptor *ifDesc);
    virtual bool 	init(	const IOUSBConfigurationDescriptor *cfDesc,
                                const IOUSBInterfaceDescriptor *ifDesc);
    virtual bool 	attach(IOService *provider);
    virtual bool 	start( IOService * provider );
    virtual bool 	finalize(IOOptionBits options);
    virtual void 	stop(IOService *  provider);
    virtual IOReturn 	message( UInt32 type, IOService * provider,  void * argument = 0 );

    /*!
        @function FindNextAltInterface
        return alternate interface descriptor satisfying the requirements specified in request, or NULL if there aren't any.
        request is updated with the properties of the returned interface.
        @param current interface descriptor to start searching from, NULL to start at alternate interface 0.
        @param request specifies what properties an interface must have to match.
        @result Pointer to a matching interface descriptor, or NULL if none match.
    */
    virtual const IOUSBInterfaceDescriptor *FindNextAltInterface(const IOUSBInterfaceDescriptor *current,
                                                                 IOUSBFindInterfaceRequest *request);

    /*!
	@function FindNextPipe
	Find a pipe of the interface that matches the requirements, either
	starting from the beginning of the interface's pipe list or from a specified
	pipe.
	@param current Pipe to start searching from, NULL to start from beginning of list.
	@param request Requirements for pipe to match, updated with the found pipe's
	properties.
	@result Pointer to the pipe, or NULL if no pipe matches the request.
    */
    virtual IOUSBPipe *FindNextPipe(IOUSBPipe *current, IOUSBFindEndpointRequest *request);

    /*!
        @function FindNextAssociatedDescriptor
        Find the next descriptor of the requested type associated with the interface.
	@param current Descriptor to start searching from, NULL to start from beginning of list.
	@param type Descriptor type to search for, or kUSBAnyDesc to return any descriptor type.
	@result Pointer to the descriptor, or NULL if no matching descriptors found.
    */
    virtual const IOUSBDescriptorHeader * FindNextAssociatedDescriptor(const void *current, UInt8 type);

    /*!
        @function SetAlternateInterface
        Select the specified alternate interface.
        @param forClient The client requesting the alternate setting. This client must have the interface open in order to perform the request.
	@param alternateSetting Alternate setting (from the alternate interface's interface descriptor).
        @result exclusive access error if the interface is not open. otherwise the result of the transaction
    */
    virtual IOReturn SetAlternateInterface(IOService *forClient, UInt16 alternateSetting);

    /* handleOpen / handleClose, overriden to open/close all the pipes */
    virtual bool handleOpen( 	IOService *	   forClient,
                                IOOptionBits	   options = 0,
                                void *		   arg = 0 );

    virtual bool open( 	IOService *	   forClient,
                                IOOptionBits	   options = 0,
                                void *		   arg = 0 );

    virtual void handleClose(  	IOService *	   forClient,
                                IOOptionBits	   options = 0 );

    /*!
        @function GetPipeObj
	returns a handle to the pipe at the corresponding index
        @param index value from zero to kUSBMaxPipes-1
	@result The pipe.
    */
    virtual IOUSBPipe *GetPipeObj(UInt8 index) { return (index < kUSBMaxPipes) ? _pipeList[index] : NULL ; }
    /*!
        @function GetConfigValue
	returns the device configuration value for the interface
	@result The device configuration value.
    */
    virtual UInt8 GetConfigValue() { return _configDesc->bConfigurationValue; }
    /*!
        @function GetDevice
        returns the device the interface is part of.
	@result Pointer to the device.
    */
    virtual IOUSBDevice *GetDevice() { return _device; }
    /*!
        @function GetInterfaceNumber
        returns the zero based value identifying the index in the array of concurrent
        interfaces supported by the current configuration
        @result the interface index
    */
    virtual UInt8 GetInterfaceNumber() { return _bInterfaceNumber; }
    /*!
        @function GetAlternateSetting
        returns value used to select alternate setting for the interface
        identified by GetInterfaceNumber
        @result the alternate setting
    */
    virtual UInt8 GetAlternateSetting() { return _bAlternateSetting; }
    /*!
        @function GetNumEndpoints
        returns the number of endpoints used by this interface (excluding
        device endpoint zero. If the value is zero, this interface only
        uses endpoint zero.
        @result the number of endpoints
    */
    virtual UInt8 GetNumEndpoints() { return _bNumEndpoints; }
    /*!
        @function GetInterfaceClass
        returns the class code for this interface (assigned by the USB)
        a value of zero is reserved
        if the value is FFh, the interface class is vendor-specific
        all other values are reserved for assignment by the USB
        @result the interface class
    */
    virtual UInt8 GetInterfaceClass() { return _bInterfaceClass; }
    /*!
        @function GetInterfaceSubClass
        returns the subclass code (assigned by the USB).
        These codes are qualified by the value returned by GetInterfaceClass
        @result the interface subclass
    */
    virtual UInt8 GetInterfaceSubClass() { return _bInterfaceSubClass; }
    /*!
        @function GetInterfaceProtocol
        returns the protocol code (assigned by the USB).
        @result the interface index
    */
    virtual UInt8 GetInterfaceProtocol() { return _bInterfaceProtocol; }
    /*!
        @function GetInterfaceStringIndex
        returns the index of the string descriptor describing the interface
        @result the string index
    */
    virtual UInt8 GetInterfaceStringIndex() { return _iInterface; }
    
    /*!
	@function DeviceRequest
        @abstract execute a device request
        @param request The parameter block to send to the device
	@completion Function to call when request completes. If omitted then deviceRequest()
	executes synchronously, blocking until the request is complete.
    */
    virtual IOReturn DeviceRequest(IOUSBDevRequest *request, IOUSBCompletion *completion = 0) 
        { return _device->DeviceRequest(request, completion); }

    // Same but with a memory descriptor
    virtual IOReturn DeviceRequest(IOUSBDevRequestDesc *request, IOUSBCompletion *completion = 0)
        { return _device->DeviceRequest(request, completion); }

    virtual bool matchPropertyTable(OSDictionary * table, SInt32 *score);

    OSMetaClassDeclareReservedUnused(IOUSBInterface,  0);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  1);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  2);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  3);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  4);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  5);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  6);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  7);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  8);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  9);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  10);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  11);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  12);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  13);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  14);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  15);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  16);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  17);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  18);
    OSMetaClassDeclareReservedUnused(IOUSBInterface,  19);
};

#endif /* _IOKIT_IOUSBINTERFACE_H */

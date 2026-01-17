/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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
/*
 *
 *	IOFWAddressSpace.h
 *
 * Classes which describe addresses in the local node which are accessable to other nodes
 * via firewire asynchronous read/write/lock requests.
 */
#ifndef _IOKIT_IOFWADDRESSSPACE_H
#define _IOKIT_IOFWADDRESSSPACE_H

#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/firewire/IOFWRegs.h>

class IOFireWireDevice;
class IOFireWireBus;
class IOFireWireController;

typedef void * IOFWRequestRefCon;

/*
 * Callback called when a write request packet is received for
 * a 'virtual' firewire address.
 * device is the node originating the request
 * speed is the FireWire speed of the request, update it if you need to control
 * the speed of the reply, otherwise the response will be the same speed.
 * addr is the address the device is requesting to write to
 * len is the number of bytes to write
 * buf contains the packet data
 * requestRefcon refcon Can be queried for extra info about the request,
 * using IOFireWireController::isLockRequest(), isQuadRequest()
 * return:
	kFWResponseComplete			= 0,	// OK!
	kFWResponseConflictError	= 4,	// Resource conflict, may retry
	kFWResponseDataError		= 5,	// Data not available
	kFWResponseTypeError		= 6,	// Operation not supported
	kFWResponseAddressError		= 7		// Address not valid in target device
 */
typedef UInt32 (*FWWriteCallback)(void *refcon, UInt16 nodeID, IOFWSpeed &speed,
                                  FWAddress addr, UInt32 len, const void *buf, IOFWRequestRefCon requestRefcon);

/*
 * Callback called when a read request packet is received for
 * a 'virtual' firewire address.
 * nodeID is the node originating the request
 * speed is the FireWire speed of the request, update it if you need to control
 * the speed of the reply, otherwise the response will be the same speed.
 * addr is the address the device is requesting to write to
 * len is the number of bytes to write
 * buf on return points to a memory descriptor containing the packet data
 * offset on return points to the offset into *buf of the packet data
 * requestRefcon refcon to pass back if sending a delayed response. Also can be queried for extra info about the request
 * return:
    kFWResponsePending			= -1,	// Pseudo response, real response sent later.
	kFWResponseComplete			= 0,	// OK!
	kFWResponseConflictError	= 4,	// Resource conflict, may retry
	kFWResponseDataError		= 5,	// Data not available
	kFWResponseTypeError		= 6,	// Operation not supported
	kFWResponseAddressError		= 7		// Address not valid in target device
 *
 * A return of kFWResponsePending should be followed at some later time by a call to
 * IOFireWireController::asyncReadResponse
 */
typedef UInt32 (*FWReadCallback)(void *refcon, UInt16 nodeID, IOFWSpeed &speed,
                                FWAddress addr, UInt32 len, IOMemoryDescriptor **buf,
                                 IOByteCount * offset, IOFWRequestRefCon requestRefcon);
/*
 * Base class for FireWire address space objects
 */
class IOFWAddressSpace : public OSObject
{
    OSDeclareAbstractStructors(IOFWAddressSpace)

protected:
    IOFireWireController *fControl;

/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;

    virtual bool init(IOFireWireBus *bus);
    
public:
    virtual UInt32 doRead(UInt16 nodeID, IOFWSpeed &speed, FWAddress addr, UInt32 len, 
					IOMemoryDescriptor **buf, IOByteCount * offset,
                          IOFWRequestRefCon refcon) = 0;
    virtual UInt32 doWrite(UInt16 nodeID, IOFWSpeed &speed, FWAddress addr, UInt32 len,
                           const void *buf, IOFWRequestRefCon refcon) = 0;
    virtual UInt32 doLock(UInt16 nodeID, IOFWSpeed &speed, FWAddress addr, UInt32 inlen,
                          const UInt32 *newVal, UInt32 &outLen, UInt32 *oldVal,
                          UInt32 extType, IOFWRequestRefCon refcon);
    
    virtual IOReturn activate();
    virtual void deactivate();
    
    // returns number of bytes starting at addr in this space (0 if not in it)
    virtual UInt32 contains(FWAddress addr);
    
private:
    OSMetaClassDeclareReservedUsed(IOFWAddressSpace, 0);
    OSMetaClassDeclareReservedUnused(IOFWAddressSpace, 1);
    
};

/*
 * Direct physical memory <-> FireWire address.
 * Accesses to these addresses may be handled automatically by the
 * hardware without notification.
 *
 * The 64 bit FireWire address of (32 bit) physical addr xxxx:xxxx is hostNode:0000:xxxx:xxxx
 */
class IOFWPhysicalAddressSpace : public IOFWAddressSpace
{
    OSDeclareDefaultStructors(IOFWPhysicalAddressSpace)

protected:
    IOMemoryDescriptor *fMem;
    vm_size_t		fLen;
    virtual	void 					free();

public:
    virtual bool initWithDesc(IOFireWireBus *bus,
                                        IOMemoryDescriptor *mem);

    virtual UInt32 doRead(UInt16 nodeID, IOFWSpeed &speed, FWAddress addr, UInt32 len, 
					IOMemoryDescriptor **buf, IOByteCount * offset,
                          IOFWRequestRefCon refcon);
    virtual UInt32 doWrite(UInt16 nodeID, IOFWSpeed &speed, FWAddress addr, UInt32 len,
                           const void *buf, IOFWRequestRefCon refcon);
};

/*
 * Pseudo firewire addresses usually represent emulated registers of some kind.
 * Accesses to these addresses will result in the owner being notified.
 * 
 * Virtual addresses should not have zero as the top 16 bits of the 48 bit local address,
 * since that may look like a physical address to hardware (eg. OHCI).
 * if reader is NULL then reads will not be allowed.
 * if writer is NULL then writes will not be allowed.
 * if either is NULL then lock requests will not be allowed.
 * refcon is passed back as the first argument of read and write callbacks.
 */
class IOFWPseudoAddressSpace : public IOFWAddressSpace
{
    OSDeclareDefaultStructors(IOFWPseudoAddressSpace)

protected:
    IOMemoryDescriptor*	fDesc;
    void *				fRefCon;
    FWReadCallback		fReader;
    FWWriteCallback		fWriter;
    FWAddress			fBase;
    UInt32				fLen;

/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;

    static	OSData *	allocatedAddresses;
    
    virtual	void 					free();
    static 	UInt32 					simpleReader(
											void*					refcon,
											UInt16 					nodeID,
											IOFWSpeed &				speed,
											FWAddress 				addr,
											UInt32 					len,
											IOMemoryDescriptor**	buf,
											IOByteCount* 			offset,
                                            IOFWRequestRefCon		reqrefcon);
    
    static 	UInt32 					simpleWriter(
											void*					refcon,
											UInt16 					nodeID,
											IOFWSpeed&				speed,
											FWAddress 				addr,
											UInt32 					len,
											const void*				buf,
                                            IOFWRequestRefCon		reqrefcon);

    // Get a unique address range
    IOReturn						allocateAddress(
											FWAddress*				addr,
											UInt32 					len);
    // free address
    void							freeAddress(
											FWAddress 				addr,
											UInt32 					len);

public:
    static IOFWPseudoAddressSpace*	readWrite(
											FWAddress 				addr,
											UInt32 					len, 
											FWReadCallback 			reader,
											FWWriteCallback 		writer,
											void*					refcon);

    // make an address space object to handle read-only memory (eg. the local ROM)
    // Handles everything itself
    static IOFWPseudoAddressSpace*	simpleRead(
                                            IOFireWireBus*			bus,
			                                FWAddress*				addr,
											UInt32 					len,
											const void*				data);

    // make an address space object to handle fixed read-only memory (eg. the local ROM)
    // Handles everything itself
    static IOFWPseudoAddressSpace*	simpleReadFixed(
                                            IOFireWireBus*			bus,
			                                FWAddress 				addr,
											UInt32 					len,
											const void*				data);

    // make an address space object to handle r/w memory
    // Handles everything itself
    static IOFWPseudoAddressSpace*	simpleRW(
                                            IOFireWireBus*			bus,
                                			FWAddress*				addr,
											UInt32 					len,
											void *					data);
    static IOFWPseudoAddressSpace*	simpleRW(
                                            IOFireWireBus*			bus,
                                			FWAddress*				addr,
											IOMemoryDescriptor *	data);
    virtual bool 					initAll(
                                            IOFireWireBus*			bus,
                							FWAddress*				addr,
											UInt32 					len, 
											FWReadCallback 			reader,
											FWWriteCallback 		writer,
											void*					refcon);
    virtual bool 					initFixed(
                                            IOFireWireBus*			bus,
							                FWAddress 				addr,
											UInt32 					len,
                							FWReadCallback 			reader,
											FWWriteCallback 		writer,
											void*					refcon);
    virtual UInt32 					doRead(
											UInt16 					nodeID, 
											IOFWSpeed &				speed, 
											FWAddress 				addr, 
											UInt32 					len,
                               				IOMemoryDescriptor **	buf, 
											IOByteCount * 			offset,
                                            IOFWRequestRefCon		reqrefcon);
    virtual UInt32 					doWrite(
											UInt16 					nodeID,
											IOFWSpeed&				speed,
											FWAddress 				addr,
											UInt32 					len, 
											const void*				buf,
                                            IOFWRequestRefCon		reqrefcon);

    virtual UInt32					contains(FWAddress addr);
    
private:
    OSMetaClassDeclareReservedUnused(IOFWPseudoAddressSpace, 0);
    OSMetaClassDeclareReservedUnused(IOFWPseudoAddressSpace, 1);
    
};

#endif /* _IOKIT_IOFWADDRESSSPACE */

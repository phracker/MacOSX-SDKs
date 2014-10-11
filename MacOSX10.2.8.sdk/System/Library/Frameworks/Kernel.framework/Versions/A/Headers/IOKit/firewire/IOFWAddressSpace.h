/*
 * Copyright (c) 1998-2002 Apple Computer, Inc. All rights reserved.
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
#include <IOKit/firewire/IOFireWireFamilyCommon.h>

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

class IOFWAddressSpace;

#pragma mark -

/*! 
	@class IOFWAddressSpaceAux
*/

class IOFWAddressSpaceAux : public OSObject
{
    OSDeclareDefaultStructors(IOFWAddressSpaceAux)

	friend class IOFWAddressSpace;
	
protected:
	
	IOFWAddressSpace * 		fPrimary;
	IOFireWireController *	fControl;
	
	OSSet *					fTrustedNodeSet;
    OSIterator *			fTrustedNodeSetIterator;
	
	/*! 
		@struct ExpansionData
		@discussion This structure will be used to expand the capablilties of the class in the future.
    */  
	  
    struct ExpansionData { };

	/*! 
		@var reserved
		Reserved for future use.  (Internal use only)  
	*/
    
	ExpansionData * reserved;

    virtual bool init( IOFWAddressSpace * primary );
	virtual	void free();

	virtual bool isTrustedNode( UInt16 nodeID );
	virtual void addTrustedNode( IOFireWireDevice * device );
	virtual void removeTrustedNode( IOFireWireDevice * device );
	virtual void removeAllTrustedNodes( void );
	
private:
    OSMetaClassDeclareReservedUnused(IOFWAddressSpaceAux, 0);
    OSMetaClassDeclareReservedUnused(IOFWAddressSpaceAux, 1);
    OSMetaClassDeclareReservedUnused(IOFWAddressSpaceAux, 2);
    OSMetaClassDeclareReservedUnused(IOFWAddressSpaceAux, 3);
    OSMetaClassDeclareReservedUnused(IOFWAddressSpaceAux, 4);
    OSMetaClassDeclareReservedUnused(IOFWAddressSpaceAux, 5);
    OSMetaClassDeclareReservedUnused(IOFWAddressSpaceAux, 6);
    OSMetaClassDeclareReservedUnused(IOFWAddressSpaceAux, 7);
    OSMetaClassDeclareReservedUnused(IOFWAddressSpaceAux, 8);
    OSMetaClassDeclareReservedUnused(IOFWAddressSpaceAux, 9);
	
};

#pragma mark -

/*
 * Base class for FireWire address space objects
 */
 
/*! 
	@class IOFWAddressSpace
*/

class IOFWAddressSpace : public OSObject
{
    OSDeclareAbstractStructors(IOFWAddressSpace)

	friend class IOFWAddressSpaceAux;
	
protected:
    
	IOFireWireController *fControl;

	/*!
		@struct ExpansionData
		@discussion This structure will be used to expand the capablilties of the class in the future.
    */  
	  
    struct ExpansionData 
	{ 
		IOFWAddressSpaceAux * fAuxiliary; 
	};

	/*! 
		@var reserved
		Reserved for future use.  (Internal use only)  
	*/
	
    ExpansionData * fIOFWAddressSpaceExpansion;

    virtual bool init(IOFireWireBus *bus);
	virtual	void free();
  
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

	inline bool isTrustedNode( UInt16 nodeID ) 
		{ return fIOFWAddressSpaceExpansion->fAuxiliary->isTrustedNode( nodeID ); }

	inline void addTrustedNode( IOFireWireDevice * device )
		{ fIOFWAddressSpaceExpansion->fAuxiliary->addTrustedNode( device ); }
	
	inline void removeTrustedNode( IOFireWireDevice * device )
		{ fIOFWAddressSpaceExpansion->fAuxiliary->removeTrustedNode( device ); }
		
	inline void removeAllTrustedNodes( void )
		{ fIOFWAddressSpaceExpansion->fAuxiliary->removeAllTrustedNodes(); }
		
protected:
	
	virtual IOFWAddressSpaceAux * createAuxiliary( void );
    
private:
    OSMetaClassDeclareReservedUsed(IOFWAddressSpace, 0);
    OSMetaClassDeclareReservedUsed(IOFWAddressSpace, 1);
    
};

// the physical and psuedo address space classes used to be defined here
// for backwards compatibility, we pull them in now.  the ifdefs surrounding
// the content of the header files ensures we do not multiply include a header.

#include <IOKit/firewire/IOFWPseudoAddressSpace.h>
#include <IOKit/firewire/IOFWPhysicalAddressSpace.h>

#endif /* _IOKIT_IOFWADDRESSSPACE */

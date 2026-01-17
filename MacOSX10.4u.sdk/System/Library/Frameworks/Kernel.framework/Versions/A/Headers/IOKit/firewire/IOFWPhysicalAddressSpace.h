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
 
#ifndef _IOKIT_IOFWPHYSICALADDRESSSPACE_H
#define _IOKIT_IOFWPHYSICALADDRESSSPACE_H

#include <IOKit/firewire/IOFWAddressSpace.h>
#include <IOKit/IODMACommand.h>

/*
 * Direct physical memory <-> FireWire address.
 * Accesses to these addresses may be handled automatically by the
 * hardware without notification.
 *
 * The 64 bit FireWire address of (32 bit) physical addr xxxx:xxxx is hostNode:0000:xxxx:xxxx
 */

class IOFWPhysicalAddressSpace;

struct FWSegment
{
	FWAddress	address;
	UInt32		length;
};

#pragma mark -

/*! 
	@class IOFWPhysicalAddressSpaceAux
*/

class IOFWPhysicalAddressSpaceAux : public IOFWAddressSpaceAux
{
    OSDeclareDefaultStructors(IOFWPhysicalAddressSpaceAux)

	friend class IOFWAddressSpace;
	friend class IOFWPhysicalAddressSpace;
	
protected:
	
	/*! 
		@struct ExpansionData
		@discussion This structure will be used to expand the capablilties of the class in the future.
    */  
	  
    struct ExpansionData { };

	/*! 
		@var reserved
		Reserved for future use.  (Internal use only)  
	*/
    
	ExpansionData *reserved;
	
	IODMACommand *	fDMACommand;
	bool			fDMACommandPrepared;
	
public:
    virtual bool init( IOFWAddressSpace * primary );
	virtual	void free();

	void setDMACommand( IODMACommand * dma_command );
	IODMACommand * getDMACommand( void ); 
	UInt64 getPhysicalSegment( UInt64 offset, UInt64 * length );
	
	IOReturn prepare( void );
	IOReturn synchronize( IOOptionBits options );
	IOReturn complete( void );

	bool isPrepared( void );

	IOReturn getSegments( UInt64 * offset, FWSegment * fw_segments, UInt32 * num_segments );
	
private:
    OSMetaClassDeclareReservedUnused(IOFWPhysicalAddressSpaceAux, 0);
    OSMetaClassDeclareReservedUnused(IOFWPhysicalAddressSpaceAux, 1);
    OSMetaClassDeclareReservedUnused(IOFWPhysicalAddressSpaceAux, 2);
    OSMetaClassDeclareReservedUnused(IOFWPhysicalAddressSpaceAux, 3);
    OSMetaClassDeclareReservedUnused(IOFWPhysicalAddressSpaceAux, 4);
    OSMetaClassDeclareReservedUnused(IOFWPhysicalAddressSpaceAux, 5);
    OSMetaClassDeclareReservedUnused(IOFWPhysicalAddressSpaceAux, 6);
    OSMetaClassDeclareReservedUnused(IOFWPhysicalAddressSpaceAux, 7);
    OSMetaClassDeclareReservedUnused(IOFWPhysicalAddressSpaceAux, 8);
    OSMetaClassDeclareReservedUnused(IOFWPhysicalAddressSpaceAux, 9);
	
};

#pragma mark -

class IOFWPhysicalAddressSpace : public IOFWAddressSpace
{
    OSDeclareDefaultStructors(IOFWPhysicalAddressSpace)

	friend class IOFWPhysicalAddressSpaceAux;

protected:
    
	IOMemoryDescriptor *	fMem;	// unused
    vm_size_t				fLen;	// unused
	
    virtual	void 					free();

public:
	virtual bool init( IOFireWireBus * bus );
    virtual bool initWithDesc(IOFireWireBus *bus,
                                        IOMemoryDescriptor *mem);

    virtual UInt32 doRead(UInt16 nodeID, IOFWSpeed &speed, FWAddress addr, UInt32 len, 
					IOMemoryDescriptor **buf, IOByteCount * offset,
                          IOFWRequestRefCon refcon);
    virtual UInt32 doWrite(UInt16 nodeID, IOFWSpeed &speed, FWAddress addr, UInt32 len,
                           const void *buf, IOFWRequestRefCon refcon);

	IOMemoryDescriptor * getMemoryDescriptor( void );

	IOReturn setMemoryDescriptor( IOMemoryDescriptor * descriptor );

	UInt64 getLength( void );

	inline void setDMACommand( IODMACommand * dma_command )
		{ ((IOFWPhysicalAddressSpaceAux*)fIOFWAddressSpaceExpansion->fAuxiliary)->setDMACommand( dma_command ); };
		
	inline IODMACommand * getDMACommand( void )
		{ return ((IOFWPhysicalAddressSpaceAux*)fIOFWAddressSpaceExpansion->fAuxiliary)->getDMACommand(); };

	virtual bool initWithDMACommand( IOFireWireBus * control, IODMACommand * command );
	
	inline IOReturn prepare( void )
		{ return ((IOFWPhysicalAddressSpaceAux*)fIOFWAddressSpaceExpansion->fAuxiliary)->prepare(); };

	inline IOReturn synchronize( IOOptionBits options )
		{ return ((IOFWPhysicalAddressSpaceAux*)fIOFWAddressSpaceExpansion->fAuxiliary)->synchronize( options ); };
		 
	inline IOReturn complete( void )
		{ return ((IOFWPhysicalAddressSpaceAux*)fIOFWAddressSpaceExpansion->fAuxiliary)->complete(); };

	inline bool isPrepared( void )
		{ return ((IOFWPhysicalAddressSpaceAux*)fIOFWAddressSpaceExpansion->fAuxiliary)->isPrepared(); };

	inline IOReturn getSegments( UInt64 * offset, FWSegment * fw_segments, UInt32 * num_segments )
		{ return ((IOFWPhysicalAddressSpaceAux*)fIOFWAddressSpaceExpansion->fAuxiliary)->getSegments( offset, fw_segments, num_segments ); };

	IOReturn checkMemoryInRange( IOMemoryDescriptor * memory );
		
protected:

	UInt64 getPhysicalSegment( UInt64 offset, UInt64 * length )
		{ return ((IOFWPhysicalAddressSpaceAux*)fIOFWAddressSpaceExpansion->fAuxiliary)->getPhysicalSegment( offset, length); };
			
	virtual IOFWAddressSpaceAux * createAuxiliary( void );
    	
};

#endif

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
 *	IOFireWireUnit.h
 *
 *
 */
#ifndef _IOKIT_IOFIREWIREUNIT_H
#define _IOKIT_IOFIREWIREUNIT_H

// public
#include <IOKit/firewire/IOFireWireNub.h>

class IOFireWireDevice;
class IOFireWireUnit;

#pragma mark -

/*! 
	@class IOFireWireUnitAux
*/

class IOFireWireUnitAux : public IOFireWireNubAux
{
    OSDeclareDefaultStructors(IOFireWireUnitAux)

	friend class IOFireWireUnit;
	
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
    
	ExpansionData * reserved;

    virtual bool init( IOFireWireUnit * primary );
	virtual	void free();

	virtual bool isPhysicalAccessEnabled( void );

	virtual IOFWSimpleContiguousPhysicalAddressSpace * createSimpleContiguousPhysicalAddressSpace( vm_size_t size, IODirection direction );
		
    virtual IOFWSimplePhysicalAddressSpace * createSimplePhysicalAddressSpace( vm_size_t size, IODirection direction );
	
private:
    OSMetaClassDeclareReservedUnused(IOFireWireUnitAux, 0);
    OSMetaClassDeclareReservedUnused(IOFireWireUnitAux, 1);
    OSMetaClassDeclareReservedUnused(IOFireWireUnitAux, 2);
    OSMetaClassDeclareReservedUnused(IOFireWireUnitAux, 3);
	
};

#pragma mark -

/*! @class IOFireWireUnit
*/
class IOFireWireUnit : public IOFireWireNub
{
    OSDeclareDefaultStructors(IOFireWireUnit)

	friend class IOFireWireUnitAux;
	friend class IOFireWireDevice;

protected:
    IOFireWireDevice *fDevice;	// The device unit is part of

/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;

/*------------------Methods provided to FireWire device clients-----------------------*/
public:

    virtual bool init(OSDictionary *propTable, IOConfigDirectory *directory);
    
    /*
     * Standard nub initialization
     */
    virtual bool attach(IOService * provider );
	virtual void free();

    /*
     * Matching language support
     * Match on the following properties of the unit:
     * Vendor_ID
     * GUID
     * Unit_Spec_ID
     * Unit_SW_Version
     */
    virtual bool matchPropertyTable(OSDictionary * table);


    virtual IOReturn message( UInt32 type, IOService * provider, void * argument );

    // Override handleOpen() and handleClose() to pass on to device
    virtual bool handleOpen( 	IOService *	  forClient,
                                IOOptionBits	  options,
                                void *		  arg );

    virtual void handleClose(   IOService *	  forClient,
                                IOOptionBits	  options );
    
    virtual void setNodeFlags( UInt32 flags );
	virtual void clearNodeFlags( UInt32 flags );
    virtual UInt32 getNodeFlags( void );

	virtual IOReturn setConfigDirectory( IOConfigDirectory *directory );

    /*
     * Create local FireWire address spaces for the device to access
     */
    virtual IOFWPhysicalAddressSpace *createPhysicalAddressSpace(IOMemoryDescriptor *mem);
    virtual IOFWPseudoAddressSpace *createPseudoAddressSpace(FWAddress *addr, UInt32 len,
                    FWReadCallback reader, FWWriteCallback writer, void *refcon);

protected:
	
	virtual IOFireWireNubAux * createAuxiliary( void );

public:
	void setMaxSpeed( IOFWSpeed speed );

protected:
	void terminateUnit( void );
	static void terminateUnitThreadFunc( void * refcon );

private:
    OSMetaClassDeclareReservedUnused(IOFireWireUnit, 0);
    OSMetaClassDeclareReservedUnused(IOFireWireUnit, 1);

};

#endif /* ! _IOKIT_IOFIREWIREDEVICE_H */

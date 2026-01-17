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
 *	IOFireWireDevice.h
 *
 *
 */
#ifndef _IOKIT_IOFIREWIREDEVICE_H
#define _IOKIT_IOFIREWIREDEVICE_H

#include <IOKit/firewire/IOFireWireNub.h>

class IOFireWireROMCache;

struct IOFWNodeScan;
struct RomScan;

class IOFireWireDevice;

#pragma mark -

/*! 
	@class IOFireWireDeviceAux
*/

class IOFireWireDeviceAux : public IOFireWireNubAux
{
    OSDeclareDefaultStructors(IOFireWireDeviceAux)

	friend class IOFireWireDevice;
	
protected:
	
	UInt32		fUnitCount;
	IOFWSpeed	fMaxSpeed;
	
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

    virtual bool init( IOFireWireDevice * primary );
	virtual	void free();

	virtual bool isTerminated( void );
	virtual void setTerminationState( TerminationState state );
	void setMaxSpeed( IOFWSpeed speed );
	
	void setUnitCount( UInt32 count );
	UInt32 getUnitCount( void );

	bool isPhysicalAccessEnabled( void );

	virtual IOFWSimpleContiguousPhysicalAddressSpace * createSimpleContiguousPhysicalAddressSpace( vm_size_t size, IODirection direction );
		
    virtual IOFWSimplePhysicalAddressSpace * createSimplePhysicalAddressSpace( vm_size_t size, IODirection direction );
		
private:
    OSMetaClassDeclareReservedUnused(IOFireWireDeviceAux, 0);
    OSMetaClassDeclareReservedUnused(IOFireWireDeviceAux, 1);
    OSMetaClassDeclareReservedUnused(IOFireWireDeviceAux, 2);
    OSMetaClassDeclareReservedUnused(IOFireWireDeviceAux, 3);	
};

#pragma mark -
/*! @class IOFireWireDevice
*/
class IOFireWireDevice : public IOFireWireNub
{
    OSDeclareDefaultStructors(IOFireWireDevice)

    friend class IOFireWireController;
	friend class IOFireWireDeviceAux;

/*------------------Useful info about device (also available in the registry)--------*/
protected:

	enum RegistrationState
	{
		kDeviceRegistered,
		kDeviceNeedsRegisterService,
		kDeviceNotRegistered
	};
	
    IOFireWireROMCache * fDeviceROM;
    bool		fOpenFromDevice;
    UInt32		fOpenFromUnitCount;
    UInt32		fROMGeneration;
    IORecursiveLock *fROMLock;
    RegistrationState	fRegistrationState;
	UInt32		fROMReadRetry;
	
/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;

    static	void readROMDirGlue(void *refcon, IOReturn status,
                               IOFireWireNub *device, IOFWCommand *fwCmd);
    static	void readROMThreadFunc(void *arg);
    static	void terminateDevice(void *arg);
    
    void	processROM(RomScan *romScan);
    
    virtual void free();
    
/*-----------Methods provided to FireWire device clients-------------*/
public:

    virtual IOReturn message( UInt32 type, IOService * provider, void * argument );

    virtual bool handleOpen( IOService * forClient, IOOptionBits options, void * arg );
    virtual void handleClose( IOService * forClient, IOOptionBits options );
    virtual bool handleIsOpen( const IOService * forClient ) const;
    
    virtual IOReturn cacheROM(OSData *rom, UInt32 offset, const UInt32 *&romBase);
    virtual const UInt32 * getROMBase();
    
    // Called after init or bus reset to update nodeID and ROM
    virtual void setNodeROM(UInt32 generation, UInt16 localNodeID,
		const IOFWNodeScan *info);

    /*
     * Matching language support
     * Match on the following properties of the device:
     * Vendor_ID
     * GUID
     */
    virtual bool matchPropertyTable(OSDictionary * table);

    /*
     * Standard nub initialization
     */
    virtual bool init(OSDictionary * propTable, const IOFWNodeScan *scan);
    virtual bool attach(IOService * provider );

    /*
     * Override to clean up fDirectory etc. that otherwise results in mutual
     * retain()s and hence memory leaks
     */
    virtual bool finalize( IOOptionBits options );

    virtual void setNodeFlags( UInt32 flags );
	virtual void clearNodeFlags( UInt32 flags );
    virtual UInt32 getNodeFlags( void );
	virtual IOReturn configureNode( void );

    /*
     * Create local FireWire address spaces for the device to access
     */
    virtual IOFWPhysicalAddressSpace *createPhysicalAddressSpace(IOMemoryDescriptor *mem);
    virtual IOFWPseudoAddressSpace *createPseudoAddressSpace(FWAddress *addr, UInt32 len,
                    FWReadCallback reader, FWWriteCallback writer, void *refcon);

protected:
	virtual IOReturn readRootDirectory( IOConfigDirectory * directory, OSDictionary * propTable );
	virtual IOReturn processRootDirectory( OSDictionary * propTable );
	virtual IOReturn readUnitDirectories( IOConfigDirectory * directory, OSSet * unitInfo );
	virtual IOReturn processUnitDirectories( OSSet * unitSet );
    
	virtual void setRegistrationState( RegistrationState fRegistrationState );
	
	virtual void preprocessDirectories( OSDictionary * rootPropTable, OSSet * unitSet );
	
	virtual void configurePhysicalFilter( void );

protected:
	virtual IOFireWireNubAux * createAuxiliary( void );

public:
	inline bool isTerminated( void )
		{ return ((IOFireWireDeviceAux*)fAuxiliary)->isTerminated(); }
		
	inline void setMaxSpeed( IOFWSpeed speed )
		{ ((IOFireWireDeviceAux*)fAuxiliary)->setMaxSpeed( speed ); }		

protected:
	inline void setUnitCount( UInt32 count )
		{ ((IOFireWireDeviceAux*)fAuxiliary)->setUnitCount( count ); }		

public:
	inline UInt32 getUnitCount( void )
		{ return ((IOFireWireDeviceAux*)fAuxiliary)->getUnitCount(); }		
	
private:
    OSMetaClassDeclareReservedUnused(IOFireWireDevice, 0);
    OSMetaClassDeclareReservedUnused(IOFireWireDevice, 1);

};

#endif /* ! _IOKIT_IOFIREWIREDEVICE_H */

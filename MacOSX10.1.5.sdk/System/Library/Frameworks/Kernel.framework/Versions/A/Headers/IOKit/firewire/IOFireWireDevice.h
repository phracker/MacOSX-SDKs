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
 *	IOFireWireDevice.h
 *
 *
 */
#ifndef _IOKIT_IOFIREWIREDEVICE_H
#define _IOKIT_IOFIREWIREDEVICE_H

#include <IOKit/firewire/IOFireWireNub.h>

struct IOFWNodeScan;
struct RomScan;

class IOFireWireDevice : public IOFireWireNub
{
    OSDeclareDefaultStructors(IOFireWireDevice)

/*------------------Useful info about device (also available in the registry)--------*/
protected:

    OSData *	fDeviceROM;
    bool		fOpenFromDevice;
    UInt32		fOpenFromUnitCount;
    UInt32		fROMGeneration;
    IORecursiveLock *fROMLock;
    
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
    
private:
    OSMetaClassDeclareReservedUnused(IOFireWireDevice, 0);
    OSMetaClassDeclareReservedUnused(IOFireWireDevice, 1);

};

#endif /* ! _IOKIT_IOFIREWIREDEVICE_H */

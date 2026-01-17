/*
 * Copyright (c) 2001 Apple Computer, Inc. All rights reserved.
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
 *	IOFireWirePCRSpace.h
 *
 * Class to multiplex access to the FCP request address.
 */
#ifndef _IOKIT_IOFIREWIREAVCREQUESTSPACE_H
#define _IOKIT_IOFIREWIREAVCREQUESTSPACE_H

#include <IOKit/firewire/IOFWAddressSpace.h>

class IOFireWireBus;

/*!
    @class IOFireWireAVCRequestSpace
    @abstract object to multiplex users of the FCP request register
*/
class IOFireWireAVCRequestSpace : public IOFWPseudoAddressSpace
{
    OSDeclareDefaultStructors(IOFireWireAVCRequestSpace)
    
protected:
    
    UInt8 fUnitAddr;

/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;
    
    // Override to check cts, subunit type and id
    virtual UInt32 doWrite(UInt16 nodeID, IOFWSpeed &speed, FWAddress addr, UInt32 len,
                           const void *buf, IOFWRequestRefCon refcon);

public:
/*!
    @function init
    @abstract initializes the IOFireWireAVCRequestSpace object
    @param bus FireWire bus.
    @param subUnitType AVC subunit type to receive requests for.
    @param subUnitID AVC subunit ID to receive requests for.
    @param refcon arbitrary value passed back as first argument of writer.
    @param writer callback function when a write to the FCP request register matches the specified AVC subunit.
*/
    virtual bool init(IOFireWireBus * bus, UInt32 subUnitType, UInt32 subUnitID, FWWriteCallback writer, void * refcon);
    
/*!
    @function withSubUnit
    @abstract creates a IOFireWireAVCRequestSpace object
    @param bus FireWire bus.
    @param subUnitType AVC subunit type to receive requests for.
    @param subUnitID AVC subunit ID to receive requests for.
    @param writer callback function when a write to the FCP request register matches the specified AVC subunit.
    @param refcon arbitrary value passed back as first argument of writer.
*/
    static IOFireWireAVCRequestSpace * withSubUnit(IOFireWireBus * bus,
                UInt32 subUnitType, UInt32 subUnitID, FWWriteCallback writer, void * refcon);
    
private:
    OSMetaClassDeclareReservedUnused(IOFireWireAVCRequestSpace, 0);
    OSMetaClassDeclareReservedUnused(IOFireWireAVCRequestSpace, 1);
    OSMetaClassDeclareReservedUnused(IOFireWireAVCRequestSpace, 2);
    OSMetaClassDeclareReservedUnused(IOFireWireAVCRequestSpace, 3);

};

#endif /* _IOKIT_IOFIREWIREAVCREQUESTSPACE_H */

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
 *	IOFireWireNub.h
 *
 *
 * 	Note: IOFWCommand(s) are allocated by methods in this class. 
 *            The remaining methods to setup and submit IOFWCommands are defined in
 *            IOFWCommand.h
 */
#ifndef _IOKIT_IOFIREWIRENUB_H
#define _IOKIT_IOFIREWIRENUB_H

#include <IOKit/IOService.h>
#include <IOKit/firewire/IOFWCommand.h>
#include <IOKit/firewire/IOFWAddressSpace.h>
class IOFireWireController;
class IOFireWireBus;
class IOConfigDirectory;

class IOFireWireNub : public IOService
{
    OSDeclareAbstractStructors(IOFireWireNub)

    friend class IOFireWireController;
    
/*------------------Useful info about device (also available in the registry)--------*/
protected:
    int			fDeviceSpeed;	// Max supported by device
    int			fCommsSpeed;	// Max speed this node can communicate with device
    UInt16		fNodeID;	// Current node ID (could change after bus reset!)
    UInt16		fLocalNodeID;	// ID of the local node (could change after bus reset!)
    UInt32		fGeneration;	// ID Of bus topology that fNodeID is valid for.
    CSRNodeUniqueID	fUniqueID;	// Device's globally unique ID (never changes)
    mach_timespec_t	fAsyncTimeout;	// Guesstimate of how long to wait for response
					// from device when making async requests
					// Different values for quad/block transfers?
					// OS8 FW has 40/100 mSec.

    int			fMaxReadPackLog;
    int			fMaxWritePackLog;
    int			fMaxReadROMPackLog;

    IOFireWireController *fControl;        
    IOConfigDirectory	*fDirectory;

    UInt32		fNodeFlags;
    
/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;

    virtual void free();
    
    // Create an IOUserClient object to handle communication with User task
    virtual IOReturn newUserClient( task_t		owningTask,
                                    void * 		security_id,
                                    UInt32  		type,
                                    IOUserClient **	handler );

/*------------------Methods provided to FireWire device clients-----------------------*/
public:

    // Get nodeID and bus generation info
    IOReturn getNodeIDGeneration(UInt32 &generation, UInt16 &nodeID, UInt16 &localID) const
    { generation = fGeneration; nodeID = fNodeID; localID = fLocalNodeID; return kIOReturnSuccess;};
    IOReturn getNodeIDGeneration(UInt32 &generation, UInt16 &nodeID) const
    { generation = fGeneration; nodeID = fNodeID; return kIOReturnSuccess;};
    
    // How fast can this system talk to the node?
    virtual IOFWSpeed FWSpeed() const;

    // How fast can this node talk to another node?
    virtual IOFWSpeed FWSpeed(const IOFireWireNub *dst) const;

    // How big (as a power of two) can packets sent to/received from the node be?
    virtual int maxPackLog(bool forSend) const;

    // How big (as a power of two) can packets sent to/received from a specified address in the node be?
    virtual int maxPackLog(bool forSend, FWAddress address) const;
   
    // How big (as a power of two) can packets sent from this node to dst node/received from dst be?
    virtual int maxPackLog(bool forSend, const IOFireWireNub *dst) const;

    // Set maximum packet size nub can handle
    virtual void setMaxPackLog(bool forSend, bool forROM, int maxPackLog);
    
    /*
     * Create various FireWire commands to send to the device
     */
    virtual IOFWReadCommand 	*createReadCommand(FWAddress devAddress, IOMemoryDescriptor *hostMem,
				FWDeviceCallback completion=NULL, void *refcon=NULL,
 				bool failOnReset=false);
    virtual IOFWReadQuadCommand *createReadQuadCommand(FWAddress devAddress, UInt32 *quads, int numQuads,
				FWDeviceCallback completion=NULL, void *refcon=NULL,
 				bool failOnReset=false);

    virtual IOFWWriteCommand 	*createWriteCommand(FWAddress devAddress, IOMemoryDescriptor *hostMem,
				FWDeviceCallback completion=NULL, void *refcon=NULL,
 				bool failOnReset=false);
    virtual IOFWWriteQuadCommand *createWriteQuadCommand(FWAddress devAddress, UInt32 *quads, int numQuads,
				FWDeviceCallback completion=NULL, void *refcon=NULL,
 				bool failOnReset=false);

    // size is 1 for 32 bit compare, 2 for 64 bit.
    virtual IOFWCompareAndSwapCommand 	*createCompareAndSwapCommand(FWAddress devAddress,
				const UInt32 *cmpVal, const UInt32 *newVal, int size,
				FWDeviceCallback completion=NULL, void *refcon=NULL,
 				bool failOnReset=false);
    /*
     * Create local FireWire address spaces for the device to access
     */
    virtual IOFWPhysicalAddressSpace *createPhysicalAddressSpace(IOMemoryDescriptor *mem);
    virtual IOFWPseudoAddressSpace *createPseudoAddressSpace(FWAddress *addr, UInt32 len,
                    FWReadCallback reader, FWWriteCallback writer, void *refcon);

    /*
     * Get Config directory for nub
     * Device nub directory is root directory, Unit nub directory is Unit directory.
     */
    virtual IOReturn getConfigDirectory(IOConfigDirectory *&dir);

    /*
     * Get bus for nub
     */
    IOFireWireBus * getBus() const
        { return (IOFireWireBus *)fControl; };

    IOFireWireController * getController() const
        { return fControl; };

    const CSRNodeUniqueID &getUniqueID() const
        { return fUniqueID; };

    /*
     * Standard nub initialization
     */
    virtual bool init(OSDictionary * propTable);

    virtual void setNodeFlags( UInt32 flags );
    virtual UInt32 getNodeFlags( void );
    
private:
    OSMetaClassDeclareReservedUnused(IOFireWireNub, 0);
    OSMetaClassDeclareReservedUnused(IOFireWireNub, 1);
    OSMetaClassDeclareReservedUnused(IOFireWireNub, 2);
    OSMetaClassDeclareReservedUnused(IOFireWireNub, 3);

};

#endif /* ! _IOKIT_IOFIREWIRENUB_H */

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
 * Copyright (c) 2000 Apple Computer, Inc.  All rights reserved.
 *
 * HISTORY
 *
 */


#ifndef _IOKIT_IOFireWireLink_H
#define _IOKIT_IOFireWireLink_H
#include <IOKit/IOService.h>
#include <IOKit/firewire/IOFireWireController.h>

enum
{
	kIOFWAllPhysicalFilters = 64
};

struct IOFWNodeScan;

class IOFireWireLink : public IOService
{
    OSDeclareAbstractStructors(IOFireWireLink)

protected:

    IOFireWireController *fControl;
    IOFWWorkLoop *	fWorkLoop;

/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;

    // calls to protected methods of controller
    void processBusReset()
    { fControl->processBusReset(); };
    void processSelfIDs(UInt32 *IDs, int numIDs, UInt32 *ownIDs, int numOwnIDs)
    { fControl->processSelfIDs(IDs, numIDs, ownIDs, numOwnIDs); };
    void processRcvPacket(UInt32 *data, int numQuads)
        { fControl->processRcvPacket(data, numQuads); };

    virtual IOFireWireController * createController();
	virtual IOFWWorkLoop* createWorkLoop();

    
    // Public methods are usually only called from the firewire controller object.
public:

    // Create a device nub
    virtual IOFireWireDevice *createDeviceNub(CSRNodeUniqueID guid, const IOFWNodeScan *deviceInfo);

    // Set power state
    virtual IOReturn setLinkPowerState ( unsigned long powerStateOrdinal) = 0;

    // Bus management stuff
    virtual IOReturn setContender(bool state) = 0;
    virtual IOReturn setRootHoldOff(bool state) = 0;
    virtual IOReturn setCycleMaster(bool state) = 0;
    
    virtual IODCLProgram *createDCLProgram(bool talking, DCLCommandStruct *opcodes,
            IOFireWireController::DCLTaskInfo *info, UInt32 startEvent, UInt32 startState, UInt32 startMask) = 0;

    // Send a PHY packet
    virtual IOReturn sendPHYPacket(UInt32 quad) = 0;
 
    // Check for hardware interrupts (typically from a timeout call)
    virtual void handleInterrupts(int count) = 0;

    virtual IOReturn resetBus() = 0;
    virtual IOReturn asyncRead(UInt16 nodeID, UInt16 addrHi, UInt32 addrLo, 
				int speed, int label, int size, IOFWAsyncCommand *cmd) = 0;
    virtual IOReturn asyncReadQuadResponse(UInt16 nodeID, int speed, 
					int label, int rcode, UInt32 data) = 0;
    virtual IOReturn asyncReadResponse(UInt16 nodeID, int speed,
                                       int label, int rcode, IOMemoryDescriptor *buf,
				       IOByteCount offset, int len) = 0;

    virtual IOReturn asyncWrite(UInt16 nodeID, UInt16 addrHi, UInt32 addrLo,
		int speed, int label, IOMemoryDescriptor *buf, IOByteCount offset,
		int size, IOFWAsyncCommand *cmd) = 0;
    virtual IOReturn asyncWrite(UInt16 nodeID, UInt16 addrHi, UInt32 addrLo,
                                int speed, int label, void *data, int size, IOFWAsyncCommand *cmd) = 0;
    virtual IOReturn asyncWriteResponse(UInt16 nodeID, int speed, 
					int label, int rcode, UInt16 addrHi) = 0;

    virtual IOReturn asyncLock(UInt16 nodeID, UInt16 addrHi, UInt32 addrLo, 
			int speed, int label, int type, void *data, int size, IOFWAsyncCommand *cmd) = 0;
    virtual IOReturn asyncLockResponse(UInt16 nodeID, int speed, 
				int label, int rcode, int type, void *data, int len) = 0;

    // Try to fix whatever might have caused the other device to not respond
    virtual IOReturn handleAsyncTimeout(IOFWAsyncCommand *cmd) = 0;

    // Local ConfigROM changed
    // Bus will be reset (via resetBus()) if this returns kIOReturnSuccess
    virtual IOReturn updateROM(const OSData *rom) = 0;
    
    // Read Cycle time register. safe to call at any time.
    virtual IOReturn getCycleTime(UInt32 &cycleTime) = 0;
    virtual IOReturn getBusCycleTime(UInt32 &busTime, UInt32 &cycleTime) = 0;
    virtual IOReturn setBusTime(UInt32 busTime) = 0;

    virtual CSRNodeUniqueID getGUID() = 0;
    virtual UInt32 getBusCharacteristics() = 0;
    virtual UInt32 getMaxSendLog() = 0;
    virtual UInt16 getNodeID() = 0;

    virtual IOFireWireController * getController() const;
    
    // Implement IOService::getWorkLoop
    virtual IOWorkLoop *getWorkLoop() const;
    
    // FireWire wants an IOFWWorkLoop
    virtual IOFWWorkLoop *getFireWireWorkLoop() const;
    
    virtual void setNodeIDPhysicalFilter( UInt16 nodeID, bool state ) =0;

private:
    OSMetaClassDeclareReservedUnused(IOFireWireLink, 0);
    OSMetaClassDeclareReservedUnused(IOFireWireLink, 1);
    OSMetaClassDeclareReservedUnused(IOFireWireLink, 2);
    OSMetaClassDeclareReservedUnused(IOFireWireLink, 3);
    OSMetaClassDeclareReservedUnused(IOFireWireLink, 4);
    OSMetaClassDeclareReservedUnused(IOFireWireLink, 5);
    OSMetaClassDeclareReservedUnused(IOFireWireLink, 6);
    OSMetaClassDeclareReservedUnused(IOFireWireLink, 7);
    OSMetaClassDeclareReservedUnused(IOFireWireLink, 8);
	
};

#endif /* ! _IOKIT_IOFireWireLink_H */


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
 * Copyright (c) 1999 Apple Computer, Inc.  All rights reserved.
 *
 * HISTORY
 *
 */


#ifndef _IOKIT_IOFIREWIREBUS_H
#define _IOKIT_IOFIREWIREBUS_H

#include <IOKit/IOService.h>
#include <IOKit/firewire/IOFWIsochChannel.h>
#include <IOKit/firewire/IOFWRegs.h>
#include <IOKit/firewire/IOFWCommand.h>
#include <IOKit/firewire/IOFWAddressSpace.h>

extern const OSSymbol *gFireWireROM;
extern const OSSymbol *gFireWireNodeID;
extern const OSSymbol *gFireWireSelfIDs;
extern const OSSymbol *gFireWireSpeed;
extern const OSSymbol *gFireWireUnit_Spec_ID;
extern const OSSymbol *gFireWireUnit_SW_Version;
extern const OSSymbol *gFireWireVendor_ID;
extern const OSSymbol *gFireWire_GUID;
extern const OSSymbol *gFireWireVendor_Name;
extern const OSSymbol *gFireWireProduct_Name;

class IOFWIsochPort;
class IOFWLocalIsochPort;
struct DCLCommandStruct;

class IOFireWireBus : public IOService
{
    OSDeclareAbstractStructors(IOFireWireBus)

public:

static const IORegistryPlane * gIOFireWirePlane;

    typedef void (CallUserProc)(void *refcon, void * userProc, void * dclCommand);
    typedef struct _DCLTaskInfo {
        task_t fTask;	// Task DCL addresses are valid in
        vm_address_t fDCLBaseAddr;
        UInt32 fDCLSize;	// In bytes
        vm_address_t fDataBaseAddr;
        UInt32 fDataSize;
        CallUserProc *fCallUser; // Routine to handle DCLCallCommandProcs
        void *fCallRefCon;	// Refcon for user call
    } DCLTaskInfo;

    // Create an Isochronous Channel object
    virtual IOFWIsochChannel *createIsochChannel(
        bool doIRM, UInt32 bandwidth, IOFWSpeed prefSpeed,
        FWIsochChannelForceStopNotificationProc stopProc=NULL,
        void *stopRefCon=NULL) = 0;
 
   // Create a local isochronous port to run the given DCL program
    virtual IOFWLocalIsochPort *createLocalIsochPort(bool talking,
        DCLCommandStruct *opcodes, DCLTaskInfo *info = 0,
        UInt32 startEvent = 0, UInt32 startState = 0, UInt32 startMask = 0) = 0;

    virtual IOReturn getCycleTime(UInt32 &cycleTime) = 0;
    virtual IOReturn getBusCycleTime(UInt32 &busTime, UInt32 &cycleTime) = 0;

    // Methods to manipulate the local Config ROM
    virtual IOReturn AddUnitDirectory(IOLocalConfigDirectory *unitDir) = 0;
    virtual IOReturn RemoveUnitDirectory(IOLocalConfigDirectory *unitDir) = 0;

    // Cause a bus reset
    virtual IOReturn resetBus() = 0;

    // Convert a firewire nodeID into the IOFireWireDevice for it
    virtual IOFireWireDevice * nodeIDtoDevice(UInt32 generation, UInt16 nodeID) = 0;

    // Execute specified function on workloop after specified delay
    // Returned command is for delay, call it's cancel() function to cancel timeout.
    virtual IOFWDelayCommand * createDelayedCmd(UInt32 uSecDelay, FWBusCallback func, void *refcon) = 0;

    virtual IOFWPhysicalAddressSpace *createPhysicalAddressSpace(IOMemoryDescriptor *mem) = 0;
    virtual IOFWPseudoAddressSpace *createPseudoAddressSpace(FWAddress *addr, UInt32 len,
                                FWReadCallback reader, FWWriteCallback writer, void *refcon) = 0;


    // Extract info about the async request
    virtual bool isLockRequest(IOFWRequestRefCon refcon) = 0;
    virtual bool isQuadRequest(IOFWRequestRefCon refcon) = 0;
    virtual UInt32 getExtendedTCode(IOFWRequestRefCon refcon) = 0;

    // How big (as a power of two) can packets sent to/received from the node be?
    virtual int maxPackLog(bool forSend, UInt16 nodeAddress) const = 0;

    // How big (as a power of two) can packets sent from A to B be?
    virtual int maxPackLog(UInt16 nodeA, UInt16 nodeB) const = 0;

    // Force given node to be root (via root holdoff Phy packet)
    virtual IOReturn makeRoot(UInt32 generation, UInt16 nodeID) = 0;

    // Create address space at fixed address in initial register space
    virtual IOFWPseudoAddressSpace *createInitialAddressSpace(UInt32 addressLo, UInt32 len,
                                FWReadCallback reader, FWWriteCallback writer, void *refcon) = 0;

    // Get address space object for given address, if any
    virtual IOFWAddressSpace *getAddressSpace(FWAddress address) = 0;
    
private:
    OSMetaClassDeclareReservedUsed(IOFireWireBus, 0);
    OSMetaClassDeclareReservedUsed(IOFireWireBus, 1);
    OSMetaClassDeclareReservedUnused(IOFireWireBus, 2);
    OSMetaClassDeclareReservedUnused(IOFireWireBus, 3);
    OSMetaClassDeclareReservedUnused(IOFireWireBus, 4);
    OSMetaClassDeclareReservedUnused(IOFireWireBus, 5);
    OSMetaClassDeclareReservedUnused(IOFireWireBus, 6);
    OSMetaClassDeclareReservedUnused(IOFireWireBus, 7);

};

#endif /* ! _IOKIT_IOFIREWIREBUS_H */


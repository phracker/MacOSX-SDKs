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


#ifndef _IOKIT_IOFIREWIRECONTROLLER_H
#define _IOKIT_IOFIREWIRECONTROLLER_H

#include <IOKit/IOEventSource.h>
#include <IOKit/firewire/IOFWWorkLoop.h>
#include <IOKit/firewire/IOFireWireBus.h>

class OSData;
class IOWorkLoop;
class IOEventSource;
class IOFWQEventSource;
class IOTimerEventSource;
class IOMemoryDescriptor;
class IOFireWireController;
class IOFWAddressSpace;
class IOFireWireNub;
class IOFireWireDevice;
class IOFireWireUnit;
class IODCLProgram;
class IOLocalConfigDirectory;
class IOFireWireLink;

struct AsyncPendingTrans {
    IOFWAsyncCommand *	fHandler;
    int			fTCode;
    bool		fInUse;
};

struct IOFWNodeScan {
    IOFireWireController *	fControl;
    FWAddress			fAddr;
    UInt32			fBuf[5];	// Enough for bus info block
    UInt32 *			fSelfIDs;
    int				fNumSelfIDs;
    int				fROMSize;
    int				fRead;
    IOFWReadQuadCommand *	fCmd;
};

class IOFWQEventSource : public IOEventSource
{
    OSDeclareDefaultStructors(IOFWQEventSource)

protected:
    IOFWCmdQ *fQueue;
    virtual bool checkForWork();

public:
    bool init(IOFireWireController *owner);
    inline void signalWorkAvailable()	{IOEventSource::signalWorkAvailable();};
    inline void openGate()		{IOEventSource::openGate();};
    inline void closeGate()		{IOEventSource::closeGate();};
};


#define kMaxPendingTransfers kFWAsynchTTotal

class IOFireWireController : public IOFireWireBus
{
    OSDeclareAbstractStructors(IOFireWireController)

protected:
    enum busState {
        kAsleep = 0,		// Link off, zzzzzz
        kWaitingSelfIDs,	// Bus has been reset, no selfIDs yet
        kWaitingScan,		// Got selfIDs, waiting a bit before hitting lame devices
        kScanning,			// Reading node ROMs
        kWaitingPrune,		// Read all ROMs, pausing before pruning missing devices
        kPendingReset,		// Running, but we're about to issue a bus reset
        kRunning			// Normal happy state
    };
    
    struct timeoutQ: public IOFWCmdQ
    {
        IOTimerEventSource *fTimer;
        virtual void headChanged(IOFWCommand *oldHead);
        void busReset();
    };
    struct pendingQ: public IOFWCmdQ
    {
        IOFWQEventSource *fSource;
        virtual void headChanged(IOFWCommand *oldHead);
    };

    friend class IOFireWireLink;
    friend class IOFWAddressSpace;
    
    IOFireWireLink *		fFWIM;
    IOFWWorkLoop *	fWorkLoop;
    IOTimerEventSource *fTimer;
    OSSet *		fLocalAddresses;	// Collection of local adress spaces
    OSIterator *	fSpaceIterator;		// Iterator over local addr spaces

    OSSet *		fAllocatedChannels;	// Need to be informed of bus resets
    OSIterator *	fAllocChannelIterator;	// Iterator over channels

    // Bus management variables (although we aren't a FireWire Bus Manager...)
    AbsoluteTime	fResetTime;		// Time of last reset
    UInt32		fBusGeneration;		// ID of current bus topology.
    UInt16		fLocalNodeID;		// ID of local node, ie. this computer
    UInt16		fRootNodeID;		// ID of root, ie. highest node id in use.
    UInt16		fIRMNodeID;		// ID of Isochronous resource manager, or kFWBadNodeID
    bool		fBusMgr;		// true if at least one node is bus manager capable
    IORegistryEntry * 	fNodes[kFWMaxNodesPerBus];	// FireWire nodes on this bus
    UInt32 *	 	fNodeIDs[kFWMaxNodesPerBus+1];	// Pointer to SelfID list for each node
							// +1 so we know how many selfIDs the last node has
    UInt32		fGapCount;		// What we think the gap count should be
    UInt8		fSpeedCodes[(kFWMaxNodesPerBus+1)*kFWMaxNodesPerBus];
						// Max speed between two nodes
    busState	fBusState;		// Which state are we in?
    int			fNumROMReads;		// Number of device ROMs we are still reading
    // SelfIDs
    int			fNumSelfIDs;		// Total number of SelfID packets
    UInt32		fSelfIDs[kMaxSelfIDs*kFWMaxNodesPerBus];

    // The local device's Config ROM
    UInt32 		fROMHeader[5];		// More or less fixed header and bus info block
    IOLocalConfigDirectory *fRootDir;		// Local Config ROM root directory.

    // log base 2 of maximum packet size the FWIM can send/receive
    // Normally calculated from bus info block.
    int	fMaxSendLog;
    int fMaxRecvLog;
    
    IOFWAddressSpace *	fROMAddrSpace;
    IOMemoryDescriptor *fBadReadResponse;	// Send back easily identified bad data to out of range addrs. 

    // Array for outstanding requests (up to 64)
    AsyncPendingTrans	fTrans[kMaxPendingTransfers];
    int			fLastTrans;

    // queue for executing commands that may timeout
    timeoutQ		fTimeoutQ;

    // queue for commands that can't execute yet
    pendingQ		fPendingQ;

    // queue for async commands interrupted by bus reset
    IOFWCmdQ		fAfterResetHandledQ;
    
    // Command to change bus state after a delay.
    IOFWDelayCommand *	fDelayedStateChangeCmd;
    bool fDelayedStateChangeCmdNeedAbort;
    
/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;

    static void clockTick(OSObject *, IOTimerEventSource *);
    static void readROMGlue(void *refcon, IOReturn status,
			IOFireWireNub *device, IOFWCommand *fwCmd);
    static void delayedStateChange(void *refcon, IOReturn status,
                                    IOFireWireBus *bus, IOFWBusCommand *fwCmd);

    virtual void processBusReset();
    virtual void processSelfIDs(UInt32 *IDs, int numIDs, UInt32 *ownIDs, int numOwnIDs);
    virtual void processTimeout(IOTimerEventSource *src);
    virtual void processRcvPacket(UInt32 *data, int numQuads);
    virtual void processWriteRequest(UInt16 sourceID, UInt32 tlabel,
				UInt32 *hdr, void *buf, int len);
    virtual void processLockRequest(UInt16 sourceID, UInt32 tlabel,
				UInt32 *hdr, void *buf, int len);

    // Process read from a local address, return rcode
    virtual UInt32 doReadSpace(UInt16 nodeID, IOFWSpeed &speed, FWAddress addr, UInt32 len,
                                      IOMemoryDescriptor **buf, IOByteCount * offset,
                                      IOFWRequestRefCon refcon);

    // Process write to a local address, return rcode
    virtual UInt32 doWriteSpace(UInt16 nodeID, IOFWSpeed &speed, FWAddress addr, UInt32 len,
                                const void *buf, IOFWRequestRefCon refcon);

    // Process lock to a local address, return rcode
    UInt32 doLockSpace(UInt16 nodeID, IOFWSpeed &speed, FWAddress addr, UInt32 inlen,
                                             const UInt32 *newVal, UInt32 &outLen, UInt32 *oldVal,
                                             UInt32 extType, IOFWRequestRefCon refcon);
    
    virtual void updatePlane();
    virtual void startBusScan();

    // Called when all devices on bus have been examined
    virtual void finishedBusScan();
    
    virtual void buildTopology(bool doFWPlane);

    virtual void readDeviceROM(IOFWNodeScan *refCon, IOReturn status);

    virtual IOReturn UpdateROM();
    virtual IOReturn allocAddress(IOFWAddressSpace *space);
    virtual void freeAddress(IOFWAddressSpace *space);

public:

    // Initialization
    virtual bool init(IOFireWireLink *fwim);
    virtual bool start(IOService *provider);
    virtual void stop( IOService * provider );
    virtual bool finalize( IOOptionBits options );
    virtual bool requestTerminate( IOService * provider, IOOptionBits options );

    // Power management
    virtual IOReturn setPowerState ( unsigned long powerStateOrdinal, IOService* whatDevice );

    // Implement IOService::getWorkLoop
    virtual IOWorkLoop *getWorkLoop() const;

    // Allocate struct for tracking a transaction
    virtual AsyncPendingTrans *allocTrans(IOFWAsyncCommand *cmd=NULL);
    virtual void freeTrans(AsyncPendingTrans *trans);

    // Really public methods

    virtual IOReturn getCycleTime(UInt32 &cycleTime);
    virtual IOReturn getBusCycleTime(UInt32 &busTime, UInt32 &cycleTime);
    
    // Methods to manipulate the local Config ROM
    virtual IOReturn AddUnitDirectory(IOLocalConfigDirectory *unitDir);
    virtual IOReturn RemoveUnitDirectory(IOLocalConfigDirectory *unitDir);

    // Cause a bus reset
    virtual IOReturn resetBus();

    // Send async request packets
    virtual IOReturn asyncRead(UInt32 generation, UInt16 nodeID, UInt16 addrHi, UInt32 addrLo,
                                int speed, int label, int size, IOFWAsyncCommand *cmd);

    virtual IOReturn asyncWrite(UInt32 generation, UInt16 nodeID, UInt16 addrHi, UInt32 addrLo,
                int speed, int label, IOMemoryDescriptor *buf, IOByteCount offset,
                int size, IOFWAsyncCommand *cmd);
    virtual IOReturn asyncWrite(UInt32 generation, UInt16 nodeID, UInt16 addrHi, UInt32 addrLo,
                                int speed, int label, void *data, int size, IOFWAsyncCommand *cmd);

    virtual IOReturn asyncLock(UInt32 generation, UInt16 nodeID, UInt16 addrHi, UInt32 addrLo,
                        int speed, int label, int type, void *data, int size, IOFWAsyncCommand *cmd);


    // Send async read response packets
    // useful for pseudo address spaces that require servicing outside the FireWire work loop.
    virtual IOReturn asyncReadResponse(UInt32 generation, UInt16 nodeID, int speed,
                                       IOMemoryDescriptor *buf, IOByteCount offset, int len,
                                       IOFWRequestRefCon refcon);

    // Try to fix whatever might have caused the other device to not respond
    virtual IOReturn handleAsyncTimeout(IOFWAsyncCommand *cmd);

    // Convert a firewire nodeID into the IOFireWireDevice for it
    virtual IOFireWireDevice * nodeIDtoDevice(UInt32 generation, UInt16 nodeID);

    // Add/remove a channel from the list informed of bus resets
    virtual void addAllocatedChannel(IOFWIsochChannel *channel);
    virtual void removeAllocatedChannel(IOFWIsochChannel *channel);

    // Create an Isochronous Channel object
    // doIRM = true => allocate channel and bandwith in Isochronous Resource Manager
    // packetSize packet size (in bytes), used to calculate bandwidth needed.
    virtual IOFWIsochChannel *createIsochChannel(
	bool doIRM, UInt32 packetSize, IOFWSpeed prefSpeed,
	FWIsochChannelForceStopNotificationProc stopProc=NULL,
	void *stopRefCon=NULL);

    // Create a local isochronous port to run the given DCL program
    // if task is 0, the DCL program is for the kernel task,
    // otherwise all DCL pointers are valid in the specified task.
    // opcodes is also pointer valid in the specified task.
    virtual IOFWLocalIsochPort *createLocalIsochPort(bool talking,
        DCLCommandStruct *opcodes, DCLTaskInfo *info = 0,
	UInt32 startEvent = 0, UInt32 startState = 0, UInt32 startMask = 0);

    // Execute specified function on workloop after specified delay
    // Returned command is for delay, call it's cancel() function to cancel timeout.
    virtual IOFWDelayCommand * createDelayedCmd(UInt32 uSecDelay, FWBusCallback func, void *refcon);

    virtual IOFWPhysicalAddressSpace *createPhysicalAddressSpace(IOMemoryDescriptor *mem);
    virtual IOFWPseudoAddressSpace *createPseudoAddressSpace(FWAddress *addr, UInt32 len,
                                FWReadCallback reader, FWWriteCallback writer, void *refcon);


    // Extract info about the async request 
    virtual bool isLockRequest(IOFWRequestRefCon refcon);
    virtual bool isQuadRequest(IOFWRequestRefCon refcon);
    virtual UInt32 getExtendedTCode(IOFWRequestRefCon refcon);
    
    // Inline accessors for protected member variables
    IOFWCmdQ &getTimeoutQ() { return fTimeoutQ; };
    IOFWCmdQ &getPendingQ() { return fPendingQ; };
    IOFWCmdQ &getAfterResetHandledQ() { return fAfterResetHandledQ; };
    IOFireWireLink * getLink() const { return fFWIM; };

    IOLocalConfigDirectory *getRootDir() const { return fRootDir;};
    bool checkGeneration(UInt32 gen) const {return gen == fBusGeneration;};
    UInt32 getGeneration() const {return fBusGeneration;};
    UInt16 getLocalNodeID() const {
        return fLocalNodeID;
    };
    IOReturn getIRMNodeID(UInt32 &generation, UInt16 &id) const
        {generation = fBusGeneration; id = fIRMNodeID; return kIOReturnSuccess;};
    
    const AbsoluteTime * getResetTime() const {return &fResetTime;};

    IOFWSpeed FWSpeed(UInt16 nodeAddress) const
	{return (IOFWSpeed)fSpeedCodes[(kFWMaxNodesPerBus+1)*(nodeAddress & 63)+(fLocalNodeID & 63)];};
    IOFWSpeed FWSpeed(UInt16 nodeA, UInt16 nodeB) const
      {return (IOFWSpeed)fSpeedCodes[(kFWMaxNodesPerBus+1)*(nodeA & 63)+(nodeB & 63)];};

    // How big (as a power of two) can packets sent to/received from the node be?
    virtual int maxPackLog(bool forSend, UInt16 nodeAddress) const;

    // How big (as a power of two) can packets sent from A to B be?
    virtual int maxPackLog(UInt16 nodeA, UInt16 nodeB) const;

   // Force given node to be root (via root holdoff Phy packet)
    virtual IOReturn makeRoot(UInt32 generation, UInt16 nodeID) ;

    virtual IOFWPseudoAddressSpace *createInitialAddressSpace(UInt32 addressLo, UInt32 len,
                                FWReadCallback reader, FWWriteCallback writer, void *refcon);
    
    virtual IOFWAddressSpace *getAddressSpace(FWAddress address);
    
    // Are we currently scanning the bus?
    bool scanningBus() const
        {return fBusState == kWaitingSelfIDs || fBusState == kWaitingScan || fBusState == kScanning;};

    inline void openGate()		{fPendingQ.fSource->openGate();};
    inline void closeGate()		{fPendingQ.fSource->closeGate();};
    
private:
    OSMetaClassDeclareReservedUnused(IOFireWireController, 0);
    OSMetaClassDeclareReservedUnused(IOFireWireController, 1);
    OSMetaClassDeclareReservedUnused(IOFireWireController, 2);
    OSMetaClassDeclareReservedUnused(IOFireWireController, 3);
    OSMetaClassDeclareReservedUnused(IOFireWireController, 4);
    OSMetaClassDeclareReservedUnused(IOFireWireController, 5);
    OSMetaClassDeclareReservedUnused(IOFireWireController, 6);
    OSMetaClassDeclareReservedUnused(IOFireWireController, 7);
    OSMetaClassDeclareReservedUnused(IOFireWireController, 8);

};

#endif /* ! _IOKIT_IOFIREWIRECONTROLLER_H */


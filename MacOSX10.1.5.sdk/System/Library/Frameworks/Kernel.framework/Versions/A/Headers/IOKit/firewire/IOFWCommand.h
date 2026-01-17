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
 *	IOFWCommand.h
 *
 */
#ifndef _IOKIT_IOFWCOMMAND_H
#define _IOKIT_IOFWCOMMAND_H

#include <IOKit/IOCommand.h>
#include <IOKit/IOLib.h>

#include <IOKit/firewire/IOFWRegs.h>

class IOMemoryDescriptor;
class IOSyncer;
class IOFireWireBus;
class IOFireWireController;
class IOFireWireNub;
class IOFWAddressSpace;	// Description of chunk of local FW address space
class IOFWCommand;
class IOFWBusCommand;
class IOCommandGate;
struct AsyncPendingTrans;

// Callback when device command completes asynchronously
typedef void (*FWDeviceCallback)(void *refcon, IOReturn status, IOFireWireNub *device, IOFWCommand *fwCmd);

// Callback when bus command completes asynchronously
typedef void (*FWBusCallback)(void *refcon, IOReturn status, IOFireWireBus *bus, IOFWBusCommand *fwCmd);

// Struct for head of command queue
/*!
    @struct IOFWCmdQ
    @abstract Structure for head of a queue of IOFWCommands
    @field fHead Points to the head of the queue, or NULL if queue is empty
    @field fTail Points to the tail of the queue, or NULL if queue is empty
    @function headChanged called when head command is changed, or the command
 	itself changes state.
*/

struct IOFWCmdQ
{
    IOFWCommand *fHead;
    IOFWCommand *fTail;
    bool executeQueue(bool all);
    virtual void headChanged(IOFWCommand *oldHead);
};

/*
 * Base class for FireWire commands
 */
class IOFWCommand : public IOCommand
{
    OSDeclareAbstractStructors(IOFWCommand)

protected:
    IOReturn		fStatus;
    IOFireWireController *fControl;
    IOFWCommand *	fQueuePrev;
    IOFWCommand *	fQueueNext;
    IOFWCmdQ *		fQueue;
    UInt32			fTimeout;	// How long (in microsecs) after execute() to timeout
    AbsoluteTime	fDeadline;	// Time after which this command has timed out.
    IOSyncer *		fSyncWakeup;
    UInt8			fSync;
    UInt8			fCancelOnReset;
    UInt8			spare[2];
    
/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;

    virtual IOReturn	complete(IOReturn status);
    virtual void	updateTimer();
    virtual IOReturn	startExecution();
    
    /*	
     *	Execute the FWCommand immediately
     *	must be called with the workloop gate closed
     */
    virtual IOReturn	execute() = 0;

public:

    virtual bool	initWithController(IOFireWireController *control);
    IOReturn		getStatus() const { return fStatus; };
    
    /*	
     *	Submit the FWCommand.
     *	if queue is false the command's execute()
     *	method will be called on the caller's thread, otherwise
     *	the command wil be queued for execution on the work loop thread.
     */                          
    virtual IOReturn 	submit(bool queue = false);

    /*
     * Cancel command, causes it to complete with given status
     */
    virtual IOReturn	cancel(IOReturn reason);

    /*!
        @function setHead
        inserts a command at the head of a queue.
        @param queue queue command is being added to
    */
    virtual void setHead(IOFWCmdQ &queue);
    /*!
        @function insertAfter
        inserts a command after the specified one.
        @param prev command to insert after
        @param queue queue command is being added to
    */
    virtual void insertAfter(IOFWCommand &prev);

    /*!
        @function removeFromQ
        Removes command from current queue.
    */
    virtual void removeFromQ();

    IOFWCommand *getPrevious() const
	{ return fQueuePrev; };
    IOFWCommand *getNext() const
        { return fQueueNext; };
    const AbsoluteTime &getDeadline() const
	{ return fDeadline; };

    bool cancelOnReset() const
    { return fCancelOnReset; };

    bool Busy() const
        { return fStatus == kIOReturnBusy || fStatus == kIOFireWirePending;};
        
    friend class IOFWCmdQ;

private:
    OSMetaClassDeclareReservedUnused(IOFWCommand, 0);
    OSMetaClassDeclareReservedUnused(IOFWCommand, 1);

};

/*
 * Bus control commands
 */
class IOFWBusCommand : public IOFWCommand
{
    OSDeclareAbstractStructors(IOFWBusCommand)

protected:
    FWBusCallback	fComplete;
    void *		fRefCon;

/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;

    virtual IOReturn	complete(IOReturn status);

    virtual bool	initWithController(IOFireWireController *control,
				FWBusCallback completion=NULL, void *refcon=NULL);
    virtual IOReturn	reinit(FWBusCallback completion, void *refcon);

private:
    OSMetaClassDeclareReservedUnused(IOFWBusCommand, 0);

};

/*
 * Command to execute some code after a specified delay (in microseconds)
 * All it does is timeout after the specified delay, hence calling the completion
 * callback.
 */
class IOFWDelayCommand : public IOFWBusCommand
{
    OSDeclareDefaultStructors(IOFWDelayCommand)

/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;

protected:
    virtual IOReturn	execute();

public:
    virtual bool	initWithDelay(IOFireWireController *control, UInt32 uSecs,
                                FWBusCallback completion, void *refcon);
    virtual IOReturn	reinit(UInt32 uSecs, FWBusCallback completion, void *refcon);

private:
    OSMetaClassDeclareReservedUnused(IOFWDelayCommand, 0);

};

/*
 * Send an async request to a device
 */
class IOFWUserReadQuadletCommand ;
class IOFWUserWriteCommand ;
class IOFWAsyncCommand : public IOFWCommand
{
	// temporary for debugging:
	friend class IOFWUserReadQuadletCommand ;
	friend class IOFWUserWriteCommand ;

    OSDeclareAbstractStructors(IOFWAsyncCommand)

protected:
    IOFireWireNub *	fDevice;
    FWDeviceCallback	fComplete;
    void *		fRefCon;
    IOMemoryDescriptor *fMemDesc;
    AsyncPendingTrans *	fTrans;
    UInt32		fAddressHi;
    UInt32		fAddressLo;
    IOByteCount		fBytesTransferred;
    int			fSize;
    int			fSpeed;
    int			fMaxPack;
    int			fCurRetries;
    int			fMaxRetries;
    UInt32		fGeneration;	// bus topology fNodeID is valid for.
    UInt16		fNodeID;
    bool		fFailOnReset;
    bool		fWrite;

/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;

    virtual IOReturn	complete(IOReturn status);
    virtual bool	initAll(IOFireWireNub *device, FWAddress devAddress,
				IOMemoryDescriptor *hostMem,
				FWDeviceCallback completion, void *refcon, bool failOnReset);
    virtual bool	initAll(IOFireWireController *control,
                                UInt32 generation, FWAddress devAddress,
                                IOMemoryDescriptor *hostMem,
                                FWDeviceCallback completion, void *refcon);
    virtual IOReturn	reinit(FWAddress devAddress, IOMemoryDescriptor *hostMem,
				FWDeviceCallback completion, void *refcon, bool failOnReset);
    virtual IOReturn	reinit(UInt32 generation, FWAddress devAddress, IOMemoryDescriptor *hostMem,
                                FWDeviceCallback completion, void *refcon);

public:
	// Utility for setting generation on newly created command
	virtual void	setGeneration(UInt32 generation)
	{ fGeneration = generation; }

    // To be called by IOFireWireController and derived classes.
    virtual void 	gotPacket(int rcode, const void* data, int size) = 0;
    virtual void	gotAck(int ackCode);

    // update nodeID/generation after bus reset, from the device object
    IOReturn		updateGeneration();
    // explicitly update nodeID/generation after bus reset
    IOReturn		updateNodeID(UInt32 generation, UInt16 nodeID);
    
    // Generally useful stuff
    IOByteCount		getBytesTransferred() const
    { return fBytesTransferred; };

    FWAddress		getAddress() const
    { return FWAddress(fAddressHi, fAddressLo, fNodeID); }

    bool		failOnReset() const
    { return fFailOnReset; }
    
    IOFireWireNub *	getDevice() const
    { return fDevice; }
    
    /*!
        @function setMaxPacket
        Sets the maximum size for block transfers used by the command.
        The command is initialized to use the maximum packet size calculated from the device's
        PHY speed, bus info block and the bus topology.
        Call this method before calling submit().
        @param maxBytes Maximum packet size in bytes. If the maxsize is 4 then quadlet transfers will be used.
    */
    IOReturn	setMaxPacket(UInt32 maxBytes)
    {
        if(fStatus == kIOReturnBusy || fStatus == kIOFireWirePending)
            return fStatus;
        fMaxPack = maxBytes;
        return kIOReturnSuccess;
    }

private:
    OSMetaClassDeclareReservedUnused(IOFWAsyncCommand, 0);
    OSMetaClassDeclareReservedUnused(IOFWAsyncCommand, 1);
    OSMetaClassDeclareReservedUnused(IOFWAsyncCommand, 2);
    OSMetaClassDeclareReservedUnused(IOFWAsyncCommand, 3);

};

/*
 * Concrete async requests - read, write and hordes of read/modify/write
 */
class IOFWReadCommand : public IOFWAsyncCommand
{
    OSDeclareDefaultStructors(IOFWReadCommand)

protected:
    virtual void 	gotPacket(int rcode, const void* data, int size);

    virtual IOReturn	execute();

public:
    virtual bool	initAll(IOFireWireNub *device, FWAddress devAddress,
				IOMemoryDescriptor *hostMem,
				FWDeviceCallback completion, void *refcon, bool failOnReset);
    virtual bool	initAll(IOFireWireController *control,
                                UInt32 generation, FWAddress devAddress,
                                IOMemoryDescriptor *hostMem,
                                FWDeviceCallback completion, void *refcon);
    virtual IOReturn	reinit(FWAddress devAddress, IOMemoryDescriptor *hostMem,
				FWDeviceCallback completion=NULL, void *refcon=NULL,
				bool failOnReset=false);
    virtual IOReturn	reinit(UInt32 generation, FWAddress devAddress, IOMemoryDescriptor *hostMem,
                                FWDeviceCallback completion=NULL, void *refcon=NULL);

private:
    OSMetaClassDeclareReservedUnused(IOFWReadCommand, 0);
    OSMetaClassDeclareReservedUnused(IOFWReadCommand, 1);
};

    /*!
        @class IOFWReadQuadCommand
        @discussion An easier to use version of IOFWReadCommand for use when the data to be transferred
        is an integer number of quads.
        Note that block read requests will be used for transfers greater than one quad unless setMaxPacket(4)
        is called.
    */
class IOFWReadQuadCommand : public IOFWAsyncCommand
{
    OSDeclareDefaultStructors(IOFWReadQuadCommand)

protected:

    UInt32 *	fQuads;

    virtual void 	gotPacket(int rcode, const void* data, int size);

    virtual IOReturn	execute();

public:
    virtual bool	initAll(IOFireWireNub *device, FWAddress devAddress,
				UInt32 *quads, int numQuads,
				FWDeviceCallback completion, void *refcon, bool failOnReset);

    virtual bool	initAll(IOFireWireController *control,
                                UInt32 generation, FWAddress devAddress,
                                UInt32 *quads, int numQuads,
                                FWDeviceCallback completion, void *refcon);
    
    virtual IOReturn	reinit(FWAddress devAddress, UInt32 *quads, int numQuads,
				FWDeviceCallback completion=NULL, void *refcon=NULL,
				bool failOnReset=false);

    virtual IOReturn	reinit(UInt32 generation, FWAddress devAddress, UInt32 *quads, int numQuads,
                                FWDeviceCallback completion=NULL, void *refcon=NULL);

    
private:
    OSMetaClassDeclareReservedUnused(IOFWReadQuadCommand, 0);
    OSMetaClassDeclareReservedUnused(IOFWReadQuadCommand, 1);
};

class IOFWWriteCommand : public IOFWAsyncCommand
{
    OSDeclareDefaultStructors(IOFWWriteCommand)
    virtual IOReturn	execute();

protected:

    int			fPackSize;

    virtual void 	gotPacket(int rcode, const void* data, int size);

public:
    virtual bool	initAll(IOFireWireNub *device, FWAddress devAddress,
				IOMemoryDescriptor *hostMem,
				FWDeviceCallback completion, void *refcon, bool failOnReset);
    virtual bool	initAll(IOFireWireController *control,
                                UInt32 generation, FWAddress devAddress,
                                IOMemoryDescriptor *hostMem,
                                FWDeviceCallback completion, void *refcon);
    virtual IOReturn	reinit(FWAddress devAddress, IOMemoryDescriptor *hostMem,
				FWDeviceCallback completion=NULL, void *refcon=NULL,
				bool failOnReset=false);
    virtual IOReturn	reinit(UInt32 generation, FWAddress devAddress, IOMemoryDescriptor *hostMem,
                                FWDeviceCallback completion=NULL, void *refcon=NULL);
    
private:
    OSMetaClassDeclareReservedUnused(IOFWWriteCommand, 0);
    OSMetaClassDeclareReservedUnused(IOFWWriteCommand, 1);
};

    /*!
        @class IOFWWriteQuadCommand
        @discussion An easier to use version of IOFWWriteCommand for use when the data to be transferred
        is small and an integer number of quads.
        Note that block read requests will be used for transfers greater than one quad unless setMaxPacket(4)
        is called.
        kMaxWriteQuads is the largest legal number of quads that this object can be asked to transfer
        (the data is copied into an internal buffer in init() and reinit()).
    */
class IOFWWriteQuadCommand : public IOFWAsyncCommand
{
    OSDeclareDefaultStructors(IOFWWriteQuadCommand)

public:
    enum {
        kMaxWriteQuads = 8
    };
    
protected:

    UInt32	fQuads[kMaxWriteQuads];
    UInt32 *	fQPtr;
    int		fPackSize;

    virtual void 	gotPacket(int rcode, const void* data, int size);

    virtual IOReturn	execute();

public:
    virtual bool	initAll(IOFireWireNub *device, FWAddress devAddress,
				UInt32 *quads, int numQuads,
				FWDeviceCallback completion, void *refcon, bool failOnReset);
    virtual bool	initAll(IOFireWireController *control,
                                UInt32 generation, FWAddress devAddress,
                                UInt32 *quads, int numQuads,
                                FWDeviceCallback completion, void *refcon);

    virtual IOReturn	reinit(FWAddress devAddress, UInt32 *quads, int numQuads,
				FWDeviceCallback completion=NULL, void *refcon=NULL,
				bool failOnReset=false);
    virtual IOReturn	reinit(UInt32 generation, FWAddress devAddress, UInt32 *quads, int numQuads,
                                FWDeviceCallback completion=NULL, void *refcon=NULL);

    
private:
    OSMetaClassDeclareReservedUnused(IOFWWriteQuadCommand, 0);
    OSMetaClassDeclareReservedUnused(IOFWWriteQuadCommand, 1);
};


/*
 * May need more parameters for some of these,
 * and/or derive from a base Lock transaction command
 */
class IOFWCompareAndSwapCommand : public IOFWAsyncCommand
{
    OSDeclareDefaultStructors(IOFWCompareAndSwapCommand)

protected:
    UInt32 fInputVals[4];
    UInt32 fOldVal[2];

/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;

    virtual void 	gotPacket(int rcode, const void* data, int size);

    virtual IOReturn	execute();

public:
    // Compare to cmpVal, and if equal replace with newVal.
    // Size = 1 for 32 bit operation (one quad), 2 for 64 bit (two quads)
    virtual bool	initAll(IOFireWireNub *device, FWAddress devAddress,
				const UInt32 *cmpVal, const UInt32 *newVal, int size,
				FWDeviceCallback completion, void *refcon, bool failOnReset);
    virtual bool	initAll(IOFireWireController *control,
                                UInt32 generation, FWAddress devAddress,
                                const UInt32 *cmpVal, const UInt32 *newVal, int size,
                                FWDeviceCallback completion, void *refcon);

    virtual IOReturn	reinit(FWAddress devAddress, const UInt32 *cmpVal, const UInt32 *newVal, int size,
                                FWDeviceCallback completion=NULL, void *refcon=NULL, bool failOnReset=false);
    virtual IOReturn	reinit(UInt32 generation, FWAddress devAddress,
                                const UInt32 *cmpVal, const UInt32 *newVal, int size,
                                FWDeviceCallback completion=NULL, void *refcon=NULL);

    // sets oldVal to the old value returned by the device, and
    // returns true if it was the expected value, ie. the lock succeeded
    virtual bool	locked(UInt32 *oldVal);
    
private:
    OSMetaClassDeclareReservedUnused(IOFWCompareAndSwapCommand, 0);
    OSMetaClassDeclareReservedUnused(IOFWCompareAndSwapCommand, 1);
    OSMetaClassDeclareReservedUnused(IOFWCompareAndSwapCommand, 2);
    OSMetaClassDeclareReservedUnused(IOFWCompareAndSwapCommand, 3);

};

#endif /* _IOKIT_IOFWCOMMAND_H */

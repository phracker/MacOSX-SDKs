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
 * Copyright (c) 1998-2000 Apple Computer, Inc.  All rights reserved. 
 *
 * HISTORY
 *
 */


#ifndef _IOKIT_IOPCIBRIDGE_H
#define _IOKIT_IOPCIBRIDGE_H

#include <IOKit/IOService.h>
#include <IOKit/IODeviceMemory.h>
#include <IOKit/IOFilterInterruptEventSource.h>
#include <IOKit/pci/IOAGPDevice.h>


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

typedef uint64_t IOPCIScalar;

struct IOPCIRange
{
    IOPCIScalar         start;
    IOPCIScalar         size;
    IOPCIScalar         alignment;
    UInt32              type;
    UInt32              flags;
    struct IOPCIRange * next;
    struct IOPCIRange * nextSubRange;
    struct IOPCIRange * subRange;
};

enum {
    kIOPCIResourceTypeMemory = 0,
    kIOPCIResourceTypePrefetchMemory,
    kIOPCIResourceTypeIO,
    kIOPCIResourceTypeBusNumber,
    kIOPCIResourceTypeCount
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*!
    @class IOPCIBridge
    @abstract   Base class for all PCI bridge drivers.
*/
class IOPCIConfigurator;
class IOPCIDevice;

class IOPCIBridge : public IOService
{
    friend class IOPCIDevice;
    friend class IOPCIConfigurator;

    OSDeclareAbstractStructors(IOPCIBridge)

private:
    static void initialize(void);
    IORegistryEntry * findMatching( OSIterator * in, IOPCIAddressSpace space );
    virtual bool isDTNub( IOPCIDevice * nub );
    bool checkProperties( IOPCIDevice * entry );

    void removeDevice( IOPCIDevice * device, IOOptionBits options = 0 );
    IOReturn restoreMachineState( IOOptionBits options = 0);
    IOReturn _restoreDeviceState( IOPCIDevice * device, IOOptionBits options );
    IOReturn resolveLegacyInterrupts( IOService * provider, IOPCIDevice * nub );
    IOReturn resolveMSIInterrupts   ( IOService * provider, IOPCIDevice * nub );

protected:
    static void nvLocation( IORegistryEntry * entry,
			    UInt8 * busNum, UInt8 * deviceNum, UInt8 * functionNum );
    static SInt32 compareAddressCell( UInt32 cellCount, UInt32 cleft[], UInt32 cright[] );

    IORangeAllocator *	bridgeMemoryRanges;
    IORangeAllocator *	bridgeIORanges;

/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the IOPCIBridge in the future.
*/    
    struct ExpansionData
    {
	friend class IOPCIConfigurator;
        IORangeAllocator * cardBusMemoryRanges;
	IOPCIRange *       rangeLists[kIOPCIResourceTypeCount];
    };

/*! @var reserved
    Reserved for future use.  (Internal use only)  
*/
    ExpansionData *reserved;

protected:
public:
    virtual void probeBus( IOService * provider, UInt8 busNum );

    virtual UInt8 firstBusNum( void );
    virtual UInt8 lastBusNum( void );

    virtual void spaceFromProperties( OSDictionary * propTable,
					IOPCIAddressSpace * space );
    virtual OSDictionary * constructProperties( IOPCIAddressSpace space );

    virtual IOPCIDevice * createNub( OSDictionary * from );

    virtual bool initializeNub( IOPCIDevice * nub, OSDictionary * from );

    virtual bool publishNub( IOPCIDevice * nub, UInt32 index );

    virtual bool addBridgeMemoryRange( IOPhysicalAddress start,
				 	IOPhysicalLength length, bool host );

    virtual bool addBridgeIORange( IOByteCount start, IOByteCount length );

    virtual bool constructRange( IOPCIAddressSpace * flags,
                                 IOPhysicalAddress phys, IOPhysicalLength len,
                                 OSArray * array );

    virtual bool matchNubWithPropertyTable( IOService * nub,
					    OSDictionary * propertyTable,
                                            SInt32 * score );

    virtual bool compareNubName( const IOService * nub, OSString * name,
				 OSString ** matched = 0 ) const;

    virtual bool pciMatchNub( IOPCIDevice * nub,
                                OSDictionary * table, SInt32 * score);

    virtual bool matchKeys( IOPCIDevice * nub, const char * keys,
				UInt32 defaultMask, UInt8 regNum );

    virtual IOReturn getNubResources( IOService * nub );

    virtual IOReturn getNubAddressing( IOPCIDevice * nub );

    virtual IOReturn getDTNubAddressing( IOPCIDevice * nub );

public:
    virtual void free( void );

    virtual bool start( IOService * provider );

    virtual bool configure( IOService * provider );

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    virtual IODeviceMemory * ioDeviceMemory( void ) = 0;

    virtual UInt32 configRead32( IOPCIAddressSpace space, UInt8 offset ) = 0;
    virtual void configWrite32( IOPCIAddressSpace space,
					UInt8 offset, UInt32 data ) = 0;
    virtual UInt16 configRead16( IOPCIAddressSpace space, UInt8 offset ) = 0;
    virtual void configWrite16( IOPCIAddressSpace space,
					UInt8 offset, UInt16 data ) = 0;
    virtual UInt8 configRead8( IOPCIAddressSpace space, UInt8 offset ) = 0;
    virtual void configWrite8( IOPCIAddressSpace space,
					UInt8 offset, UInt8 data ) = 0;

    virtual IOPCIAddressSpace getBridgeSpace( void ) = 0;

    virtual UInt32 findPCICapability( IOPCIAddressSpace space,
                                      UInt8 capabilityID, UInt8 * offset = 0 );

    virtual IOReturn setDevicePowerState( IOPCIDevice * device,
                                          unsigned long whatToDo );
    virtual IOReturn saveDeviceState( IOPCIDevice * device,
                                      IOOptionBits options = 0 );
    virtual IOReturn restoreDeviceState( IOPCIDevice * device,
                                         IOOptionBits options = 0 );

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    virtual IOReturn createAGPSpace( IOAGPDevice * master,
				     IOOptionBits options,
				     IOPhysicalAddress * address, 
				     IOPhysicalLength * length );

    virtual IOReturn destroyAGPSpace( IOAGPDevice * master );

    virtual IORangeAllocator * getAGPRangeAllocator( IOAGPDevice * master );

    virtual IOOptionBits getAGPStatus( IOAGPDevice * master,
				       IOOptionBits options = 0 );
    virtual IOReturn resetAGPDevice( IOAGPDevice * master,
                                     IOOptionBits options = 0 );

    virtual IOReturn getAGPSpace( IOAGPDevice * master,
                                  IOPhysicalAddress * address, 
				  IOPhysicalLength * length );

    virtual IOReturn commitAGPMemory( IOAGPDevice * master, 
				      IOMemoryDescriptor * memory,
				      IOByteCount agpOffset,
				      IOOptionBits options );

    virtual IOReturn releaseAGPMemory(  IOAGPDevice * master, 
				      	IOMemoryDescriptor * memory, 
					IOByteCount agpOffset,
					IOOptionBits options );

protected:
    OSMetaClassDeclareReservedUsed(IOPCIBridge, 0);
    virtual bool addBridgePrefetchableMemoryRange( IOPhysicalAddress start,
                                                   IOPhysicalLength length,
                                                   bool host );

    OSMetaClassDeclareReservedUsed(IOPCIBridge, 1);
    virtual UInt32 extendedFindPCICapability( IOPCIAddressSpace space,
					      UInt32 capabilityID, IOByteCount * offset = 0 );

    // Unused Padding
    OSMetaClassDeclareReservedUnused(IOPCIBridge,  2);
    OSMetaClassDeclareReservedUnused(IOPCIBridge,  3);
    OSMetaClassDeclareReservedUnused(IOPCIBridge,  4);
    OSMetaClassDeclareReservedUnused(IOPCIBridge,  5);
    OSMetaClassDeclareReservedUnused(IOPCIBridge,  6);
    OSMetaClassDeclareReservedUnused(IOPCIBridge,  7);
    OSMetaClassDeclareReservedUnused(IOPCIBridge,  8);
    OSMetaClassDeclareReservedUnused(IOPCIBridge,  9);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 10);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 11);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 12);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 13);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 14);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 15);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 16);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 17);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 18);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 19);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 20);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 21);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 22);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 23);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 24);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 25);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 26);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 27);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 28);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 29);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 30);
    OSMetaClassDeclareReservedUnused(IOPCIBridge, 31);



};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define kIOPCIBridgeRegs (32)
/*!
    @class IOPCI2PCIBridge
    @abstract Base class for all PCI-to-PCI bridge drivers.
*/

class IOPCI2PCIBridge : public IOPCIBridge
{
    OSDeclareDefaultStructors(IOPCI2PCIBridge)

private:

    IOPCIDevice * bridgeDevice;
    UInt32        bridgeState[kIOPCIBridgeRegs];

protected:
/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the IOWorkLoop in the future.
    */    
    struct ExpansionData
    {
    // /hotp
	IOByteCount		    xpressCapability;
	IOFilterInterruptEventSource *    bridgeInterruptSource;
	IOWorkLoop *		    workLoop;
	uint32_t		    hotplugCount;
	uint8_t			    presence;
	uint8_t			    waitingLinkEnable;
	uint8_t			    hotplugFirstBus;
	uint8_t			    hotplugLastBus;
	uint8_t			    interruptEnablePending;
	uint8_t			    __reserved[3];
    // hotp/
    };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;
public:

    virtual UInt8 firstBusNum( void );
    virtual UInt8 lastBusNum( void );

public:
    virtual void free();

    virtual bool serializeProperties( OSSerialize * serialize ) const;

    virtual IOService * probe(	IOService * 	provider,
                                SInt32 *	score );

    virtual bool start( IOService * provider );

    virtual bool configure( IOService * provider );

    virtual void probeBus( IOService * provider, UInt8 busNum );

    virtual IOReturn requestProbe( IOOptionBits options );

    virtual void saveBridgeState( void );

    virtual void restoreBridgeState( void );

    IOReturn setPowerState( unsigned long powerState,
			    IOService * whatDevice );

    virtual bool publishNub( IOPCIDevice * nub, UInt32 index );

    virtual IODeviceMemory * ioDeviceMemory( void );

    virtual IOPCIAddressSpace getBridgeSpace( void );

    virtual UInt32 configRead32( IOPCIAddressSpace space, UInt8 offset );
    virtual void configWrite32( IOPCIAddressSpace space,
					UInt8 offset, UInt32 data );
    virtual UInt16 configRead16( IOPCIAddressSpace space, UInt8 offset );
    virtual void configWrite16( IOPCIAddressSpace space,
					UInt8 offset, UInt16 data );
    virtual UInt8 configRead8( IOPCIAddressSpace space, UInt8 offset );
    virtual void configWrite8( IOPCIAddressSpace space,
					UInt8 offset, UInt8 data );

    // Unused Padding
    OSMetaClassDeclareReservedUnused(IOPCI2PCIBridge,  0);
    OSMetaClassDeclareReservedUnused(IOPCI2PCIBridge,  1);
    OSMetaClassDeclareReservedUnused(IOPCI2PCIBridge,  2);
    OSMetaClassDeclareReservedUnused(IOPCI2PCIBridge,  3);
    OSMetaClassDeclareReservedUnused(IOPCI2PCIBridge,  4);
    OSMetaClassDeclareReservedUnused(IOPCI2PCIBridge,  5);
    OSMetaClassDeclareReservedUnused(IOPCI2PCIBridge,  6);
    OSMetaClassDeclareReservedUnused(IOPCI2PCIBridge,  7);
    OSMetaClassDeclareReservedUnused(IOPCI2PCIBridge,  8);

protected:
    bool filterInterrupt( IOFilterInterruptEventSource * source);
			    
    void handleInterrupt( IOInterruptEventSource * source,
			     int                      count );

};

#endif /* ! _IOKIT_IOPCIBRIDGE_H */

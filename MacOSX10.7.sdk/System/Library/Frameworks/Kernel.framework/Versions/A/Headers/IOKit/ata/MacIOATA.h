/*
 * Copyright (c) 1998-2008 Apple Inc. All rights reserved.
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

#if defined(__ppc__)
 
 
#ifndef _DRV_MACIO_ATA_H
#define _DRV_MACIO_ATA_H

#include <libkern/c++/OSObject.h>
#include <IOKit/IOTypes.h>
#include "IOATAController.h"
#include <IOKit/ppc/IODBDMA.h>
#include <IOKit/IOMemoryCursor.h>

#include <IOKit/IOInterruptEventSource.h>


/*! @class MacIOATA
    @abstract The base class for MAC-IO ata controller family. .
    @discussion class defining the portions of MacIO ATA cells which are shared
	in common between Heathrow and Key Largo ATA Cells.
	These controllers share a common register file layout, interrupt 
	source format and all use DBDMA engines. These are different from 
	other ATA controllers, such as most PCI-IDE and PC-Card ATA ports.
 	Each cell type has some distinctive features that must be implemented
	by a specific driver subclass. As much common code as possible is 
	presented in this superclass.

*/

class MacIOATA : public IOATAController
{
    OSDeclareDefaultStructors(MacIOATA);

public:

	/*--- Overrides from IOATAController ---*/
	virtual bool init(OSDictionary * properties);
    virtual bool start( IOService* provider );
	virtual IOReturn message (UInt32 type, IOService* provider, void* argument = 0);

protected:

	// The DMA states: not in use, in use and running with additional passes needed,
	// in use on final pass, transfer complete, and failure
	enum ATADMAState 
	{
		kATADMAInactive,
		kATADMAStarting,
		kATADMAActive,
		kATADMAStatus,
		kATADMAComplete,
		kATADMAError
	};



	// the address of the timing register in the controller
	volatile UInt32* _timingConfigReg;
	// the timing values to use for each device.
	UInt32	_timingConfig[2];  
	
	// semaphore for DMA state
	UInt32	_dmaState;
	
	// indicates whether a DMA interrupt is expected
	UInt32 _dmaIntExpected;
	
	// pointer to the DMA control register address.
	volatile IODBDMAChannelRegisters* _dmaControlReg;
	
	// mappings to the controller and DMA engine registers
	// we have to free these when we go away.
	IOMemoryMap* _baseAddressMap;
	IOMemoryMap* _dmaBaseMap;
	
	// the DBDMA memory cursor
	IODBDMAMemoryCursor*	_DMACursor;
	
	// the DBDMA descriptor table
	IODBDMADescriptor* _descriptors;
	IOPhysicalAddress	_descriptorsPhysical;
	
	// interrupt event sources
	IOInterruptEventSource* _devIntSrc;
	IOInterruptEventSource* _dmaIntSrc;
	
	// flag indicating device and dma engine interrupts need 
	// re-synchronization.
	
	bool	_resyncInterrupts;
/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of the IOWorkLoop in the future.
    */
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData *reserved;
	
	// overriden to allow synchronization of DMA vs. device interrupts.
	virtual IOReturn handleDeviceInterrupt(void);
	// overriden here to allow for reporting of DMA errs
	virtual IOReturn asyncStatus(void);
	
	// overriden here to allow for clean up of DMA resynch flag on timeout.
	virtual void handleTimeout(void);


	// called by the superclass::start method in order to 
	// find and enable access to the ATA task file.
	virtual bool configureTFPointers(void);

	// allocate memory for the DMA descriptors.
	virtual bool allocDMAChannel(void);
	
	// fill CC with stop commands.
	virtual void initATADMAChains (IODBDMADescriptor* descPtr);
	
	// setup the CC with IO commands
	virtual IOReturn createChannelCommands(void);
	
	// deallocate memory for the DMA engine
	virtual bool freeDMAChannel(void);
	
	// connect the device (drive) interrupt to our workloop
	virtual bool createDeviceInterrupt(void);

	// connect the DMA interrupt to our workloop.
	virtual bool createDMAInterrupt(void);


	// override from IOATAController
	// activate the DMA engine as per the current command
	virtual IOReturn startDMA( void );

	// override from IOATAController
	// safely halt the DMA engine  regardless of state
	virtual IOReturn stopDMA( void );

	// handle the interrupt processing
	virtual void processDMAInterrupt (void);
	
	// activate the DMA engine
	virtual void activateDMAEngine(void);
	
	// shutdown the DMA engine
	virtual void stopDMAEngine(void);
	
	// safely suspend the DMA engine
	virtual void shutDownATADMA (void);
	
	// check the command chain after run to update byte counts
	// and check for errors
	virtual bool scanATADMAChain (IOByteCount* byteCount);


	// c to c++ glue code.
	static void deviceInterruptOccurred(OSObject*, IOInterruptEventSource *, int count);
	static void dmaInterruptOccurred(OSObject*, IOInterruptEventSource *, int count);

	// overrides
	virtual void free();

	// media bay specific code
	bool	isMediaBay;
	bool	isBusOnline;
	
	virtual IOReturn executeCommand(IOATADevice* nub, IOATABusCommand* command);
	virtual IOReturn handleQueueFlush( void );
	virtual bool checkTimeout( void );
	static void cleanUpAction(OSObject * owner, void*, void*, void*, void*);
	virtual void cleanUpBus(void);
	virtual IOReturn handleBusReset(void);
	// end media bay specific.

private:
    OSMetaClassDeclareReservedUnused(MacIOATA, 0);
    OSMetaClassDeclareReservedUnused(MacIOATA, 1);
    OSMetaClassDeclareReservedUnused(MacIOATA, 2);
    OSMetaClassDeclareReservedUnused(MacIOATA, 3);
    OSMetaClassDeclareReservedUnused(MacIOATA, 4);
    OSMetaClassDeclareReservedUnused(MacIOATA, 5);
    OSMetaClassDeclareReservedUnused(MacIOATA, 6);
    OSMetaClassDeclareReservedUnused(MacIOATA, 7);
    OSMetaClassDeclareReservedUnused(MacIOATA, 8);
    OSMetaClassDeclareReservedUnused(MacIOATA, 9);
    OSMetaClassDeclareReservedUnused(MacIOATA, 10);
    OSMetaClassDeclareReservedUnused(MacIOATA, 11);
    OSMetaClassDeclareReservedUnused(MacIOATA, 12);
    OSMetaClassDeclareReservedUnused(MacIOATA, 13);
    OSMetaClassDeclareReservedUnused(MacIOATA, 14);
    OSMetaClassDeclareReservedUnused(MacIOATA, 15);
    OSMetaClassDeclareReservedUnused(MacIOATA, 16);
    OSMetaClassDeclareReservedUnused(MacIOATA, 17);
    OSMetaClassDeclareReservedUnused(MacIOATA, 18);
    OSMetaClassDeclareReservedUnused(MacIOATA, 19);
    OSMetaClassDeclareReservedUnused(MacIOATA, 20);

};

#endif // _DRV_MACIO_ATA_H


#endif // defined(ppc)

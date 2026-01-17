/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */


#ifndef _IOKIT_IOPCCARDBRIDGE_H
#define _IOKIT_IOPCCARDBRIDGE_H

/*! @header IOPCCardBridge
    @abstract An IOPCI2PCIBridge based class for supporting PCI Cardbus controllers.
    @discussion

The IOPCCardBridge and IOPCCardInterruptController classes are still under development and subject to change.  They should not be subclassed at this time.  Methods in the IOPCCardBridge class should not be called unless they are also part of the superclass IOPCI2PCIBridge.

 */

#include <libkern/OSByteOrder.h>
#include <libkern/c++/OSContainers.h>

#include <IOKit/assert.h>
#include <IOKit/system.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>

#include <IOKit/IODeviceMemory.h>
#include <IOKit/IODeviceTreeSupport.h>
#include <IOKit/IOInterruptEventSource.h>
#include <IOKit/IOPlatformExpert.h>
#include <IOKit/IOMessage.h>
#include <IOKit/IOWorkLoop.h>

#include <IOKit/pci/IOPCIBridge.h>
#include <IOKit/pci/IOPCIDevice.h>

#define kIOPCCardVersionOneMatchKey		"VersionOneInfo"
#define kIOPCCardFunctionNameMatchKey		"FunctionName"
#define kIOPCCardFunctionIDMatchKey		"FunctionID"
#define kIOPCCardVendorIDMatchKey		"VendorID"
#define kIOPCCardDeviceIDMatchKey		"DeviceID"
#define kIOPCCardFunctionExtensionMatchKey	"FunctionExtension"
#define kIOPCCardMemoryDeviceNameMatchKey	"MemoryDeviceName"

// used to syncronize CS calls thru the work loop
extern IOWorkLoop *		gIOPCCardWorkLoop;
extern void *			gCardServicesGate;

// extra calls into the command gate
// anything >= 0 is assumed to be a CS call
#define kCSGateProbeBridge 	(-1)
#define kCSGateTimerCallout 	(-2)
#define kCSGateSetBridgePower 	(-3)

// this should be unique across the entire system
#define sub_iokit_pccard	err_sub(21)
#define kIOPCCardCSEventMessage iokit_family_msg(sub_iokit_pccard, 1)

// back up all of config space
#define kIOPCCardBridgeRegCount (0x100 / sizeof(UInt32))

typedef struct interrupt_handler {
    unsigned int	socket;
    unsigned int	irq;
    int 		(*top_handler)(int);
    int 		(*bottom_handler)(int);
    int 		(*enable_functional)(int);
    int 		(*disable_functional)(int);
    const char*		name;
    IOInterruptEventSource *interruptSource;
    struct interrupt_handler *	next;
} interrupt_handler_t;

class IOPCCardInterruptController;
class IOPCCardEjectController;

class IOPCCardBridge : public IOPCI2PCIBridge
{
    OSDeclareDefaultStructors(IOPCCardBridge)

private:
    IOMemoryMap *		cardBusRegisterMap;
    IOPCIDevice *		bridgeDevice;

    IOPCCardInterruptController * interruptController;
    OSSymbol * 			interruptControllerName;
    IOInterruptEventSource *	interruptSource;
    interrupt_handler_t *	interruptHandlers;

    bool			pciExpansionChassis;		// OF has already scanned and configured
								// this card and its subordinates
    bool			bridgeStateSaved;
    UInt32			bridgeConfig[kIOPCCardBridgeRegCount];	// backup of config space registers

    struct ExpansionData 	{ };
    ExpansionData *		reserved;

protected:
    static  void		metaInit(void);
    virtual void		free();

    virtual UInt8		firstBusNum(void);
    virtual UInt8		lastBusNum(void);
    virtual void		probeBus(IOService * provider, UInt8 busNum);	// noop
    virtual IOReturn		getNubResources(IOService * nub);

    virtual bool 		getModuleParameters(void);
    virtual bool		getOFConfigurationSettings(OSArray **ioRanges, OSArray **memRanges);
    virtual bool 		getConfigurationSettings(void);
    virtual bool 		configureBridgeRanges(void);
    virtual bool 		configureInterruptController(void);

    virtual bool 		initializeSocketServices(void);
    virtual bool 		initializeDriverServices(void);

    virtual OSDictionary *	constructPCCard16Properties(IOPCCard16Device * nub);
    virtual OSDictionary *	constructCardBusProperties(IOPCIAddressSpace space);
    virtual void           	constructCardBusCISProperties(IOCardBusDevice * nub);
    virtual void           	addNubInterruptProperties(OSDictionary * propTable);
    virtual bool	   	publishPCCard16Nub(IOPCCard16Device * nub, UInt32 socketIndex, UInt32 functionIndex);
    virtual bool	   	publishCardBusNub(IOCardBusDevice * nub, UInt32 socketIndex, UInt32 functionIndex);
    static bool			releaseBridgeRanges(IOService * nub);

    static int			cardEventHandler(cs_event_t event, int priority, event_callback_args_t * args);
    static void			cardRemovalHandler(u_long sn);
    static int			cardServicesGate(IOService *, void * func, void * arg1, void * arg2, void * arg3);
    
    virtual void		interruptDispatcher(void);
    virtual IOReturn		setBridgePowerState(unsigned long powerState, IOService * whatDevice);

public:
    // don't use these (these are called internally from the card services C code)

    virtual IOPCCard16Device *	createPCCard16Nub(UInt8 socket, UInt8 function);
    virtual IOCardBusDevice *	createCardBusNub(UInt8 socket, UInt8 function);
    
    virtual bool 		addCSCInterruptHandler(unsigned int socket, unsigned int irq, 
						       int (*top_handler)(int), int (*bottom_handler)(int), 
						       int (*enable_functional)(int), int (*disable_functional)(int),
						       const char * name);
    virtual bool		removeCSCInterruptHandler(unsigned int socket);
    
public:
    virtual IOService *		probe(IOService * provider, SInt32 * score);
    virtual bool		start(IOService * provider);
    virtual bool		configure(IOService * provider);
    virtual void		stop(IOService * provider);

    virtual IOReturn		setPowerState(unsigned long powerState,
					      IOService * whatDevice);
    virtual void		saveBridgeState(void);
    virtual void		restoreBridgeState(void);
					      
    virtual int			configureSocket(IOService * nub, config_req_t * configuration);
    virtual int			unconfigureSocket(IOService * nub);

    virtual IOWorkLoop *	getWorkLoop() const;

    static int			requestCardEjection(IOService * bridgeDevice);

    OSMetaClassDeclareReservedUnused(IOPCCardBridge,  0);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge,  1);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge,  2);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge,  3);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge,  4);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge,  5);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge,  6);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge,  7);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge,  8);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge,  9);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 10);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 11);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 12);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 13);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 14);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 15);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 16);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 17);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 18);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 19);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 20);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 21);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 22);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 23);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 24);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 25);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 26);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 27);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 28);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 29);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 30);
    OSMetaClassDeclareReservedUnused(IOPCCardBridge, 31);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class IOPCCardInterruptController : public IOInterruptController
{
    OSDeclareDefaultStructors(IOPCCardInterruptController);
  
private:
    IOPCIDevice *		bridgeDevice;
    unsigned long		registeredEvents;
    unsigned long		pendingEvents;

    interrupt_handler_t *	interruptHandlers;
    
    struct ExpansionData 	{ };
    ExpansionData *		reserved;

public:
    virtual IOReturn		initInterruptController(IOService * provider);
  
    virtual IOInterruptAction	getInterruptHandlerAddress(void);
    virtual IOReturn		handleInterrupt(void * refCon, IOService * nub, int source);
  
    virtual bool		vectorCanBeShared(long vectorNumber, IOInterruptVector * vector);
    virtual int			getVectorType(long vectorNumber, IOInterruptVector * vector);
    virtual void		disableVectorHard(long vectorNumber, IOInterruptVector * vector);
    virtual void		enableVector(long vectorNumber, IOInterruptVector * vector);
    virtual void		causeVector(long vectorNumber, IOInterruptVector * vector);

    virtual IOReturn		getInterruptType(int source, int * interruptType);

    virtual bool		updateCSCInterruptHandlers(interrupt_handler_t * handlers);
    
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController,  0);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController,  1);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController,  2);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController,  3);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController,  4);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController,  5);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController,  6);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController,  7);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController,  8);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController,  9);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController, 10);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController, 11);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController, 12);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController, 13);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController, 14);
    OSMetaClassDeclareReservedUnused(IOPCCardInterruptController, 15);
};

#endif /* ! _IOKIT_IOPCCARDBRIDGE_H */



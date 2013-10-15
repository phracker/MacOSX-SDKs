/*
* Copyright (c) 2007-2008 Apple Inc. All rights reserved.
*
* @APPLE_LICENSE_HEADER_START@
* 
* The contents of this file constitute Original Code as defined in and
* are subject to the Apple Public Source License Version 1.2 (the
* "License").  You may not use this file except in compliance with the
* License.  Please obtain a copy of the License at
* http://www.apple.com/publicsource and read it before using this file.
* 
* This Original Code and all software distributed under the License are
* distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
* EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
* INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.  
* Please see the License for the specific language governing rights and 
* limitations under the License.
* 
* @APPLE_LICENSE_HEADER_END@
*/

#ifndef _IOKIT_IOUSBCONTROLLERV3_H
#define _IOKIT_IOUSBCONTROLLERV3_H

#include <IOKit/pci/IOPCIDevice.h>
#include <IOKit/pwr_mgt/RootDomain.h>

#include <IOKit/usb/IOUSBControllerV2.h>
#include <IOKit/usb/IOUSBHubDevice.h>

// Constants that define the different power states in the setPowerState call
enum
{
    kUSBPowerStateOff				= 0,				// controller is reset, nothing is attached
    kUSBPowerStateRestart			= 1,				// same as OFF
    kUSBPowerStateSleep				= 2,				// controller is suspended, preparing to lose main power
    kUSBPowerStateLowPower			= 3,				// controller is suspended, power remains on
    kUSBPowerStateOn				= 4,				// up and running
	kUSBNumberBusPowerStates		= 5
};

#define kUSBPowerStateStable		-1

enum
{
    kUSBBusStateReset				= 0,				// bus is in RESET
    kUSBBusStateSuspended			= 1,				// bus is in SUSPEND mode
    kUSBBusStateRunning				= 2					// bus is operational
};


// Root Hub things
typedef struct IOUSBRootHubInterruptTransaction 
{
    IOMemoryDescriptor *		buf;
    UInt32						bufLen;
    IOUSBCompletion				completion;
} IOUSBRootHubInterruptTransaction;

enum 
{
	  kIOUSBMaxRootHubTransactions  = 2
};



/*!
 @class IOUSBControllerV3
 @abstract subclass of the IOUSBControllerV2 to provide support for new USB Power Management techniques.
 @discussion With Leopard, we are providing more information to USB Device Drivers in the IOPower
 tree to allow for more efficient Power Management. This controller class encapulates many of the changes
 needed for that, without disturbing third party subclasses of IOUSBController or IOUSBControllerV2
 */

class IOUSBControllerV3 : public IOUSBControllerV2
{	
		OSDeclareAbstractStructors(IOUSBControllerV3)

	protected:
		// static variable shared by all instances
		static uint32_t *				_gHibernateState;

	
		UInt8							_myBusState;					// kUSBBusStateReset, kUSBBusStateSuspended, kUSBBusStateRunning
		bool							_wakingFromHibernation;			// True while the Hibernation Wake thread is active
		bool							_needToAckPowerDown;			// True while we are changing power state due to shutdown/restart
		bool							_onCardBus;						// OBSOLETE
		bool							_controllerAvailable;			// true if we can talk to the controller
		SInt32							_powerStateChangingTo;			// a power state that we are in the process of changing to, or -1 if we are stable
		bool							_poweringDown;					// true is the controller is powering down because of a systemWillPowerDown message
		bool							_restarting;					// true is the controller is restarting because of a systemWillPowerDown message
		unsigned long					_myPowerState;					// my current state (since getPowerState doesn't always change in time)
		IOUSBControllerV3				*_ehciController;				// set if I am a companion controller
		unsigned long					_numPowerStates;				// how many power states do I support (defaults to kUSBNumDefaultPowerStates)
		IOPMPowerState					*_myPowerStates;				// my power state array (allocated on the fly)
		IOPCIDevice						*_device;						// my PCI device

		// root hub support
	    IOTimerEventSource					*_rootHubTimer;				// timer which fires at the rate of the root hub interrupt endpoint
		UInt8								_rootHubPollingRate;		// Obsolete -- we need to have it be a uint32_t
		UInt8								_rootHubNumPorts;			// number of root hub ports - should be 15 or fewer!
		UInt16								_rootHubStatusChangedBitmap;	// support up to 15 ports for status changes
		bool								_rootHubTimerActive;		// UNUSED
		IOUSBRootHubInterruptTransaction	_outstandingRHTrans[4];		// Transactions for the Root Hub.  We need 2, one for the current transaction and one for the next.  This is declared as 4 for binary compatibility

		struct V3ExpansionData { 
			uint32_t				_rootHubPollingRate32;
			bool					_rootHubTransactionWasAborted;
			IOPMDriverAssertionID	_externalUSBDeviceAssertionID;		// power manager assertion that we have an external USB device
			SInt32					_externalDeviceCount;				// the count of external devices in this controller - changed through the WL gate
			UInt32					_inCheckPowerModeSleeping;			// The CheckPowerModeGated
			bool					_onThunderbolt;						// T if this controller is on a Thunderbolt bus
			uint32_t				_thunderboltModelID;				// the model ID of the thunderbolt device in which this controller resides
		};
		V3ExpansionData *_v3ExpansionData;

		// IOKit methods
		virtual bool					init( OSDictionary *  propTable );
		virtual bool					start( IOService *  provider );
		virtual void					stop( IOService * provider );
		virtual unsigned long			maxCapabilityForDomainState ( IOPMPowerFlags domainState );
		virtual unsigned long			initialPowerStateForDomainState ( IOPMPowerFlags domainState );
		virtual IOReturn				powerStateWillChangeTo ( IOPMPowerFlags capabilities, unsigned long stateNumber, IOService* whatDevice);
		virtual IOReturn				setPowerState( unsigned long powerStateOrdinal, IOService* whatDevice );
		virtual IOReturn				powerStateDidChangeTo ( IOPMPowerFlags capabilities, unsigned long stateNumber, IOService* whatDevice);
		virtual void					powerChangeDone ( unsigned long fromState);
		virtual void					systemWillShutdown( IOOptionBits specifier );
		virtual bool					willTerminate(IOService * provider, IOOptionBits options);
		virtual bool					didTerminate( IOService * provider, IOOptionBits options, bool * defer );

		virtual void					free(void);
	
		// IOUSBController methods
		// we override these to deal with methods attempting to go through the workloop while we are in sleep
		virtual IOReturn 		AcquireDeviceZero( void );
		virtual void			ReleaseDeviceZero( void );
		virtual IOReturn 		DeviceRequest(IOUSBDevRequest *request,  IOUSBCompletion *completion, USBDeviceAddress address, UInt8 epNum, UInt32 noDataTimeout, UInt32 completionTimeout);
		virtual IOReturn 		DeviceRequest(IOUSBDevRequestDesc *request,  IOUSBCompletion *completion, USBDeviceAddress address, UInt8 epNum, UInt32 noDataTimeout, UInt32 completionTimeout);
		virtual IOReturn 		ClosePipe(USBDeviceAddress address, Endpoint *endpoint);
		virtual IOReturn 		AbortPipe(USBDeviceAddress address, Endpoint *endpoint);
		virtual IOReturn 		ResetPipe(USBDeviceAddress address, Endpoint *endpoint);
		virtual IOReturn 		ClearPipeStall(USBDeviceAddress address, Endpoint *endpoint);
		virtual IOReturn 		Read(IOMemoryDescriptor *buffer, USBDeviceAddress address, Endpoint *endpoint, IOUSBCompletion *completion, UInt32 noDataTimeout, UInt32 completionTimeout, IOByteCount reqCount);
		virtual IOReturn 		Write(IOMemoryDescriptor *buffer, USBDeviceAddress address, Endpoint *endpoint, IOUSBCompletion *completion, UInt32 noDataTimeout, UInt32 completionTimeout, IOByteCount reqCount);
		virtual IOReturn		IsocIO(IOMemoryDescriptor *buffer, UInt64 frameStart, UInt32 numFrames, IOUSBIsocFrame *frameList, USBDeviceAddress address, Endpoint *endpoint, IOUSBIsocCompletion *completion );
		virtual IOReturn		IsocIO(IOMemoryDescriptor *buffer, UInt64 frameStart, UInt32 numFrames, IOUSBLowLatencyIsocFrame *frameList, USBDeviceAddress address, Endpoint *endpoint, IOUSBLowLatencyIsocCompletion *completion, UInt32 updateFrequency );	

		// we override this one to add some stuff which requires the _device iVar
		virtual UInt32			GetErrataBits(UInt16 vendorID, UInt16 deviceID, UInt16 revisionID );    
	
		// IOUSBControllerV2 methods
		// we override these to deal with methods attempting to go through the workloop while we are in sleep
		virtual IOReturn 		OpenPipe(USBDeviceAddress address, UInt8 speed, Endpoint *endpoint);
		virtual IOReturn		AddHSHub(USBDeviceAddress highSpeedHub, UInt32 flags);
		virtual IOReturn		RemoveHSHub(USBDeviceAddress highSpeedHub);
		virtual IOReturn		SetTestMode(UInt32 mode, UInt32 port);
		virtual IOReturn		ReadV2(IOMemoryDescriptor *buffer, USBDeviceAddress	address, Endpoint *endpoint, IOUSBCompletionWithTimeStamp *completion, UInt32 noDataTimeout, UInt32	completionTimeout, IOByteCount reqCount);
	
		// IOUSBControllerV3 methods
	
		// these are called through the workloop
		static IOReturn					DoEnableAddressEndpoints(OSObject *owner, void *arg0, void *arg1, void *arg2, void *arg3 );
		static IOReturn					DoEnableAllEndpoints(OSObject *owner, void *arg0, void *arg1, void *arg2, void *arg3 );
		static IOReturn					GatedPowerChange(OSObject *owner, void *arg0, void *arg1, void *arg2, void *arg3 );
		static IOReturn					ChangeExternalDeviceCount(OSObject *owner, void *arg0, void *arg1, void *arg2, void *arg3 );

		// also on the workloop
	    static void						RootHubTimerFired(OSObject *owner, IOTimerEventSource *sender);
	
		// subclassable methods
		virtual IOReturn				CheckForEHCIController(IOService *provider);
		virtual	IOReturn				AllocatePowerStateArray(void);
		virtual	IOReturn				InitForPM(void);
		virtual IOReturn				CheckPowerModeBeforeGatedCall(char *fromStr);
		virtual IOReturn				EnableAllEndpoints(bool enable);
		virtual IOReturn				EnableBusMastering(bool enable);
		virtual IOReturn				EnsureUsability(void);
		virtual IOReturn				CheckForRootHubChanges(void);
		virtual IOReturn				RootHubQueueInterruptRead(IOMemoryDescriptor *buf, UInt32 bufLen, IOUSBCompletion completion);
		virtual IOReturn				RootHubAbortInterruptRead(void);
		virtual IOReturn				RootHubStartTimer(UInt8 pollingRate);			// Obsolete see RootHubStartTimer32
		virtual IOReturn				RootHubStopTimer(void);
	
		// these methods have a default implementation using some of the virtual methods below
		virtual	void					ControllerOff(void);
		virtual	void					ControllerRestart(void);
		virtual	void					ControllerSleep(void);
		virtual	void					ControllerDoze(void);
		virtual	void					ControllerOn(void);

		// these methods are pure virtual, and need to be implemented in the subclass driver
		virtual	IOReturn				ResetControllerState(void) = 0;
		virtual IOReturn				RestartControllerFromReset(void) = 0;
		virtual	IOReturn				SaveControllerStateForSleep(void) = 0;
		virtual	IOReturn				RestoreControllerStateFromSleep(void) = 0;
		virtual IOReturn				DozeController(void) = 0;
		virtual IOReturn				WakeControllerFromDoze(void) = 0;
		virtual IOReturn				UIMEnableAddressEndpoints(USBDeviceAddress address, bool enable) = 0;
		virtual IOReturn				UIMEnableAllEndpoints(bool enable) = 0;
		virtual IOReturn				EnableInterruptsFromController(bool enable) = 0;
	
	public:
	
		// public methods
		virtual IOReturn				EnableAddressEndpoints(USBDeviceAddress address, bool enable);
		virtual bool					IsControllerAvailable(void);
		virtual IOReturn				HandlePowerChange(unsigned long powerStateOrdinal);
		virtual	UInt32					AllocateExtraRootHubPortPower(UInt32 extraPowerRequested);		// DEPRECATED
		virtual	void					ReturnExtraRootHubPortPower(UInt32 extraPowerReturned);			// DEPRECATED
	
	OSMetaClassDeclareReservedUsed(IOUSBControllerV3,  0);
	virtual IOReturn				RootHubStartTimer32(uint32_t pollingRate);
	
	OSMetaClassDeclareReservedUsed(IOUSBControllerV3,  1);
	virtual IOReturn				CheckPMAssertions(IOUSBDevice *forDevice, bool deviceBeingAdded);
	
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  2);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  3);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  4);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  5);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  6);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  7);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  8);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  9);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  10);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  11);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  12);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  13);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  14);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  15);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  16);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  17);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  18);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  19);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  20);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  21);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  22);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  23);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  24);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  25);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  26);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  27);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  28);
	OSMetaClassDeclareReservedUnused(IOUSBControllerV3,  29);
	
	protected:
	
		void							FixupNECControllerConfigRegisters(void);
};

#endif		// _IOKIT_IOUSBCONTROLLERV3_H

/*
 * Copyright (c) 2007 Apple Inc. All rights reserved.
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

#ifndef __OPEN_SOURCE__
/*
 *
 *	$Log: IOUSBHubPolicyMaker.h,v $
 *	Revision 1.7  2007/08/17 22:41:11  nano
 *	Bring in branch that fixes <rdar://problem/5414582> USB not honoring Resume recovery time (hub driver) and adds extra time for iPods
 *	
 *	Revision 1.6.30.1  2007/08/16 19:14:02  nano
 *	ResumeRecovery additions.
 *	
 *	Revision 1.6  2007/08/01 16:10:18  rhoads
 *	roll in extra power changes
 *	
 *	Revision 1.5.12.1  2007/07/27 16:49:10  rhoads
 *	merge the extra current stuff into Leopard, and add extra sleep current for self powered hubs
 *	
 *	Revision 1.5  2007/07/20 22:31:22  rhoads
 *	roll in branch300-3-2
 *	
 *	Revision 1.4.40.1  2007/07/18 18:44:24  rhoads
 *	this is the 300.3.2g version plus some quieter logs
 *	
 *	Revision 1.4.34.2  2007/07/17 06:30:35  rhoads
 *	more hub chain fixes
 *	
 *	Revision 1.4.34.1  2007/07/16 16:45:00  rhoads
 *	more power management and termination tweaks
 *	
 *	Revision 1.4  2007/05/18 01:59:12  rhoads
 *	roll in 5112084 and 5204170
 *	
 *	Revision 1.3.2.1  2007/05/15 18:23:48  rhoads
 *	some initial power state bug fixes
 *	
 *	Revision 1.3  2007/05/10 22:25:35  rhoads
 *	roll in branch 5113395 - the last major piece of the new power architecture
 *	
 *	Revision 1.2.64.4  2007/04/13 22:34:59  rhoads
 *	fix restart and shutdown
 *	
 *	Revision 1.2.64.3  2007/04/11 23:56:23  rhoads
 *	first mostly working dozing hub
 *	
 *	Revision 1.2.64.2  2007/04/10 02:09:09  rhoads
 *	got UHCI almost working
 *	
 *	Revision 1.2.64.1  2007/04/05 02:57:50  rhoads
 *	move power management out of AppleUSBHub and into IOUSBHubPolicyMaker
 *	
 *	Revision 1.2  2007/01/20 00:47:01  rhoads
 *	roll in Hub Policy Maker changes
 *	
 *	Revision 1.1.2.4  2007/01/18 22:51:08  rhoads
 *	add some padding
 *	
 *	Revision 1.1.2.3  2007/01/15 19:58:07  rhoads
 *	saving more changes
 *	
 *	Revision 1.1.2.2  2007/01/09 23:55:36  rhoads
 *	working version
 *	
 *	Revision 1.1.2.1  2007/01/09 21:57:02  rhoads
 *	commit some stuff to try to fix a permissions issue
 *	
 *	
 */
#endif
#ifndef _IOKIT_IOUSBHUBPOLICYMAKER_H
#define _IOKIT_IOUSBHUBPOLICYMAKER_H

#include	<IOKit/IOService.h>
#include	<IOKit/usb/IOUSBController.h>
#include	<IOKit/usb/IOUSBHubDevice.h>


enum {
	kIOUSBHubPowerStateOff		= 0,				// losing power
	kIOUSBHubPowerStateRestart	= 1,				// reseting bus, but may maintain power
	kIOUSBHubPowerStateSleep	= 2,				// upstream port and all downstream ports suspended (from the top)
	kIOUSBHubPowerStateLowPower	= 3,				// upstream port and all downstream ports suspended (from the bottom)
	kIOUSBHubPowerStateOn		= 4,				// upstream port and at least one downstream port on
	kIOUSBHubNumberPowerStates	= 5
};

enum {
	kHubResumeRecoveryTime	=	10,								// 10 ms to recover after I resume myself
	kPortResumeRecoveryTime =	10								// 10 ms to recover another device
};

#define kIOUSBHubPowerStateStable	-1

class IOUSBHubPolicyMaker : public IOService
{
	OSDeclareAbstractStructors(IOUSBHubPolicyMaker)

protected:
    IOUSBControllerV2 *					_bus;
    IOUSBHubDevice *					_device;					// our provider
    IOUSBHubDevice *					_parentHubDevice;			// for non root hub drivers, this is the hub device that my hub device is connected to
    bool								_isRootHub;					// this is a root hub
	bool								_dozeEnabled;				// true if the controller has been enabled to go into doze mode
	bool								_dontAllowLowPower;			// If true, we will not allow the hub to go into low power mode.
	bool								_dontAllowSleepPower;		// If true, we will not allow extra sleep power for a self powered hub.
	SInt32								_powerStateChangingTo;		// a power state if we are changing to one, or -1 if we are stable
	unsigned long						_myPowerState;				// my current state (since getPowerState doesn't always change in time)
	UInt32								_extraPower;				// how much extra power we might be able to get from our parent hub
	UInt32								_extraPowerRemaining;		// how many milliamps we can still give to any one port
	UInt32								_hubResumeRecoveryTime;		// # of ms that we will wait before issuing any transactions on our port (nominally 10ms)
    struct ExpansionData 
	{ 
	};
    ExpansionData			*_expansionData;

public:
	// IOService methods
    virtual bool			start(IOService * provider);
	virtual IOReturn		powerStateWillChangeTo ( IOPMPowerFlags capabilities, unsigned long stateNumber, IOService* whatDevice);
	virtual unsigned long	powerStateForDomainState ( IOPMPowerFlags domainState );
	virtual IOReturn		setPowerState ( unsigned long powerStateOrdinal, IOService* whatDevice );
	virtual IOReturn		powerStateDidChangeTo ( IOPMPowerFlags capabilities, unsigned long stateNumber, IOService* whatDevice);
	virtual unsigned long	maxCapabilityForDomainState ( IOPMPowerFlags domainState );
	virtual void			powerChangeDone ( unsigned long fromState );

	// public methods which MAY be implemented in subclass
	virtual IOReturn				EnsureUsability(void);

	// new power stuff
	void				AllocateExtraPower();
	IOReturn			GetExtraPortPower(UInt32 portNum, UInt32 *extraPower);
	IOReturn			ReturnExtraPortPower(UInt32 portNum, UInt32 extraPower);
    
	// virtual methods to be implemented in the controlling driver subclass
	virtual bool			ConfigureHubDriver(void) = 0;
	virtual IOReturn		HubPowerChange(unsigned long powerStateOrdinal) = 0;

    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  0);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  1);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  2);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  3);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  4);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  5);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  6);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  7);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  8);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  9);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  10);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  11);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  12);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  13);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  14);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  15);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  16);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  17);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  18);
    OSMetaClassDeclareReservedUnused(IOUSBHubPolicyMaker,  19);
};

#endif _IOKIT_IOUSBHUBPOLICYMAKER_H

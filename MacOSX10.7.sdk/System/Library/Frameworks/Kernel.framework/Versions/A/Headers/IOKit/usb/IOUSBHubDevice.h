/*
 * Copyright (c) 2006 Apple Computer, Inc. All rights reserved.
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
 *	$Log: IOUSBHubDevice.h,v $
 *	Revision 1.13  2010/09/03 18:55:56  nano
 *	Bring in fix for 8001699 to TOT
 *
 *	Revision 1.12.86.2  2010/09/01 15:03:52  nano
 *	Renamed a method to be more generic
 *
 *	Revision 1.12.86.1  2010/08/31 22:37:53  nano
 *	Implement messages that allow us to send general interest notifications for devices to release and reclaim extra current
 *
 *	Revision 1.12.4.1  2010/06/01 16:51:29  nano
 *	Safekeeping of some work to send extra current messages
 *
 *	Revision 1.12  2010/05/20 17:44:23  nano
 *	Bring in fixes from PR-7481369 to TOT
 *
 *	Revision 1.11.214.4  2010/05/14 21:48:44  nano
 *	finish work with allocating/deallocating power thru gate
 *
 *	Revision 1.11.214.3  2010/05/14 20:52:31  nano
 *	Allocate/release the extra current through the gate
 *
 *	Revision 1.11.214.2  2010/05/10 19:56:57  nano
 *	Continue with implementation of sleep current budgeting
 *
 *	Revision 1.11.214.1  2010/05/08 03:35:48  nano
 *	Initial work on budgeting sleep current
 *
 *	Revision 1.11  2009/09/12 03:42:16  rhoads
 *	merge in the changes for the 390.3.4b QL
 *
 *	Revision 1.10.52.1  2009/09/10 18:50:52  nano
 *	<rdar://problem/7134800> Task: Extra Current support for Ibex Peak RMHs -- look for a property that tells us to ask our USB plane parent for the extra current.  This will allow the RMH to pass on the request to it's parent.
 *	
 *	Revision 1.10  2009/05/07 19:43:09  nano
 *	Move our SnowLeopard branch to TOT
 *	
 *	Revision 1.6.102.3  2008/06/16 22:02:16  nano
 *	Bring in changes from Foxound 320.2.19
 *	

 *	Revision 1.6.102.2  2008/04/22 22:38:01  nano
 *	Bring in changes from Foxhound-320.2.9
 *	
 *	Revision 1.8.62.2  2008/06/06 21:08:44  nano
 *	Enable dynamic allocation of power for M89, so we don't reserve it if there isn't a high power device attached
 *	
 *	Revision 1.8.62.1  2008/06/06 04:14:32  nano
 *	Fix SleepCurrent allocation so it will work with hub devices and root hub devices as well as consolidating it across all controllers
 *	
 *	Revision 1.8  2008/04/17 16:56:57  nano
 *	Bring in branches for rdar://5867990 & rdar://5768343
 *	
 *	Revision 1.7.4.1  2008/04/17 15:54:07  nano
 *	Merged PR-5768343 into this branch and fixed a couple of issues
 *	
 *	Revision 1.7.2.1  2008/04/16 00:48:49  ferg
 *	Bug #: 5768343
 *	Add support for hubs with high-power downstream port capability.  This is
 *	controlled by the properties "AAPL,current-available" and "AAPL,current-extra".
 *	
 *	Revision 1.7  2008/04/14 16:08:38  nano
 *	Add new APIs for high power and for GetDeviceInformation.
 *	
 *	Revision 1.6.144.1  2008/04/11 22:25:44  nano
 *	Initial work on new user-client APIs and new IOUSBDevice APIs to return port state information and manage extra power requests, as well as groundwork for calling the policy maker directly from the IOUSBDevice
 *	
 *	Revision 1.6  2007/08/01 16:10:18  rhoads
 *	roll in extra power changes
 *	
 *	Revision 1.5.118.1  2007/07/27 16:49:10  rhoads
 *	merge the extra current stuff into Leopard, and add extra sleep current for self powered hubs
 *	
 *	Revision 1.5  2007/01/20 00:47:01  rhoads
 *	roll in Hub Policy Maker changes
 *	
 *	Revision 1.4  2006/12/22 23:05:46  rhoads
 *	roll in branches 4364835 and 4277683-2
 *	
 *	Revision 1.3.20.3  2007/01/15 19:58:07  rhoads
 *	saving more changes
 *	
 *	Revision 1.3.20.2  2007/01/09 21:55:53  rhoads
 *	commit some stuff to try to fix a permissions issue
 *	
 *	Revision 1.3.20.1  2006/12/18 19:13:56  rhoads
 *	re-integrate the old branch into TOT
 *	
 *	Revision 1.3.12.4  2006/12/18 17:33:48  rhoads
 *	looking good except for sleep/wake
 *	
 *	Revision 1.3.12.3  2006/12/08 05:42:40  rhoads
 *	mostly working
 *	
 *	Revision 1.3.12.2  2006/11/14 22:37:06  rhoads
 *	more changes with the root hubs
 *	
 *	Revision 1.3.12.1  2006/11/07 16:55:52  rhoads
 *	change to get the IOUSBHubDevice nubs into the IOPower tree
 *	
 *	Revision 1.3  2006/10/06 04:42:02  rhoads
 *	roll in branches 4727961, 4758404, 4759810, 4760274, and 4762769
 *	
 *	Revision 1.2.4.2  2006/10/04 23:01:24  rhoads
 *	better naming
 *	
 *	Revision 1.2.4.1  2006/10/04 16:03:57  rhoads
 *	better IOUSBHubDevice design
 *	
 */
#endif


#ifndef _IOKIT_IOUSBHUBDEVICE_H
#define _IOKIT_IOUSBHUBDEVICE_H

#include <IOKit/usb/IOUSBDevice.h>						// our superclass

// forward refeference. we don't include the header file because it would cause a circular reference
class IOUSBHubPolicyMaker;

enum {
	kIOUSBHubDeviceIsRootHub			=	0x0001,
	kIOUSBHubDeviceIsOnHighSpeedBus		=	0x0002,
	kIOUSBHubDeviceCanSleep				=	0x0004
};

/*!
    @class IOUSBHubDevice
    @abstract New in MAC OS X 10.5. The IOKit object representing a hub device on the USB bus. It is a subclass of IOUSBDevice.
    @discussion With the exception of the IOUSBRootHubDevice objects representing the root hubs, every IOUSBDevice
	will have an IOUSBHubDevice as its parent in the IOUSB plane. USB KEXT drivers will have the ability to 
	query this device for characteristics of the hub into which they are connected. This class will also give a dive driver
	the abilty to get an IOService* pointing to the hub driver itself, which can then be used as the parent in the power plane.
*/

class IOUSBHubDevice : public IOUSBDevice
{
	friend class IOUSBHubPolicyMaker;
	friend class AppleUSBHub;
	friend class IOUSBController;								// for the "can sleep" characteristic
	
private:
    OSDeclareDefaultStructors(IOUSBHubDevice)

	UInt32					_myCharacteristics;					// bitmap of my characteristics
	IOUSBHubPolicyMaker		*_myPolicyMaker;					// pointer to the policy maker in the IOPower tree for this hub

    struct ExpansionData 
	{ 
		UInt32					_maxPortCurrent;				// maximum current in milliamps per downstream port
		UInt32					_totalExtraCurrent;				// total amount of current above the spec'ed current per port available (during normal operation)
		UInt32					_totalSleepCurrent;				// total amount of current that can be drawn during sleep
		UInt32					_canRequestExtraPower;			// If 0, this hub does not support requesting extra power from its parent, non-zero:  how much power we need to request in order to give out _extraPowerForPorts
		UInt32					_extraPowerForPorts;			// Of the power requested from our parent, how much can we parcel out -- the rest is consumed by voltage drop thru the cable
		UInt32					_extraPowerAllocated;			// Amount of power that we actually got from our parent
		bool					_requestFromParent;				// True if we are to request the extra power from our parent, without modifying the request.  Used for RMHs
		UInt32					_maxPortSleepCurrent;			// Maximum current per port during sleep
		UInt32					_extraSleepPowerAllocated;		// Amount of sleep power that we actually got from our parent
		UInt32					_canRequestExtraSleepPower;		// If 0, this hub does not support requesting extra sleep power from its parent, non-zero:  how much power we need to request in order to give out _extraPowerForPorts
		UInt32					_standardPortSleepCurrent;		// Standard current that can be drawn in sleep -- usually 1 USB load
	};
    ExpansionData			*_expansionData;
	
protected:
	// IOUSBHubDevice methods which will be used by the hub driver (which is also the Policy Maker)
	virtual	void			SetPolicyMaker(IOUSBHubPolicyMaker *policyMaker);
	virtual void			SetHubCharacteristics(UInt32);
	virtual bool			InitializeCharacteristics(void);					// used at start
	
	// these are called through the workloop
	static IOReturn			GatedRequestExtraPower(OSObject *target, void *arg0, void *arg1, void *arg2, void *arg3);
	static IOReturn			GatedReturnExtraPower(OSObject *target, void *arg0, void *arg1, void *arg2, void *arg3);
	static IOReturn			GatedRequestSleepPower(OSObject *target, void *arg0, void *arg1, void *arg2, void *arg3);
	static IOReturn			GatedReturnSleepPower(OSObject *target, void *arg0, void *arg1, void *arg2, void *arg3);

	// a non static but non-virtual function
	IOReturn				RequestExtraPower(uint64_t requestedPower, uint64_t *powerAllocated);
	IOReturn				RequestSleepPower(uint64_t requestedPower, uint64_t *powerAllocated);
	IOReturn				ReturnExtraPower(uint64_t returnedPower);
	IOReturn				ReturnSleepPower(uint64_t returnedPower);

public:
	// static constructor
    static IOUSBHubDevice	*NewHubDevice(void);

	// IOKit methods
    virtual bool			init();
	virtual bool			start( IOService * provider );
    virtual void			stop( IOService *provider );
    virtual void			free();
	
	// public IOUSBHubDevice methods

	void					SetTotalSleepCurrent(UInt32 sleepCurrent);
	UInt32					GetTotalSleepCurrent();
	
    /*!
	 @function GetPolicyMaker
	 returns a pointer to the policy maker for the hub, which can be used as the power plane parent.
	 @result returns an IOUSBHubPolicyMaker* pointing to the policy maker for this hub. returns NULL is no policy maker is active on the hub device.
	 */
	virtual IOUSBHubPolicyMaker *GetPolicyMaker(void);
	
    /*!
	@function GetHubCharacteristics
	returns characteristics of the hub device which might be useful for the driver of a device connected to the hub.
		kIOUSBHubDeviceIsRootHub indicates that the hub is a root hub
		kIOUSBHubDeviceIsOnHighSpeedBus indicates that the hub is running on a High Speed bus. If this bit is set and kIOUSBHubDeviceIsHighSpeed is clear, then this is a Classic Speed hub running on a High Speed bus, which means that Split Transactions will be used to communicate with downstream devices.

	@result returns a bitmap of characteristics
    */
	virtual	UInt32			GetHubCharacteristics();
	
    /*!
	@function GetMaxProvidedPower
	returns the maximum amount of power available on any downstream port of this hub
	@result the power is returned in milliamps - usually 100ma or 500 ma.
    */
	virtual UInt32			GetMaxProvidedPower();

    /*!
	@function RequestProvidedPower
	requests power from the hub device
	@param requestedPower - the amount of power requested in milliamps (usually 100ma or 500 ma)
	@result the amount of power allocated for this driver in milliamps (usually 100ma or 500 ma)
    */
	virtual UInt32			RequestProvidedPower(UInt32 requestedPower);

	virtual UInt32			RequestExtraPower(UInt32 requestedPower);

	virtual void			ReturnExtraPower(UInt32 returnedPower);
	
    OSMetaClassDeclareReservedUsed(IOUSBHubDevice,  0);
	
	virtual void			InitializeExtraPower(UInt32 maxPortCurrent, UInt32 totalExtraCurrent);
	
    OSMetaClassDeclareReservedUsed(IOUSBHubDevice,  1);
	virtual UInt32			RequestSleepPower(UInt32 requestedPower);

    OSMetaClassDeclareReservedUsed(IOUSBHubDevice,  2);
	virtual void			ReturnSleepPower(UInt32 returnedPower);

    OSMetaClassDeclareReservedUsed(IOUSBHubDevice,  3);
	virtual void			SetSleepCurrent(UInt32 sleepCurrent);
	
    OSMetaClassDeclareReservedUsed(IOUSBHubDevice,  4);
	virtual	UInt32			GetSleepCurrent();
	
    OSMetaClassDeclareReservedUsed(IOUSBHubDevice,  5);
	
	virtual void			InitializeExtraPower(UInt32 maxPortCurrent, UInt32 totalExtraCurrent, UInt32 maxPortCurrentInSleep, UInt32 totalExtraCurrentInSleep);
	
    OSMetaClassDeclareReservedUsed(IOUSBHubDevice,  6);
	virtual void			SendExtraPowerMessage(UInt32 type, UInt32 returnedPower);

    OSMetaClassDeclareReservedUnused(IOUSBHubDevice,  7);
    OSMetaClassDeclareReservedUnused(IOUSBHubDevice,  8);
    OSMetaClassDeclareReservedUnused(IOUSBHubDevice,  9);
    OSMetaClassDeclareReservedUnused(IOUSBHubDevice,  10);
    OSMetaClassDeclareReservedUnused(IOUSBHubDevice,  11);
    OSMetaClassDeclareReservedUnused(IOUSBHubDevice,  12);
    OSMetaClassDeclareReservedUnused(IOUSBHubDevice,  13);
    OSMetaClassDeclareReservedUnused(IOUSBHubDevice,  14);
    OSMetaClassDeclareReservedUnused(IOUSBHubDevice,  15);
};

#endif /* _IOKIT_IOUSBROOTHUBDEVICE_H */


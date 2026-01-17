/*
     File:       CoreMIDI/MIDIDriver.h
 
     Contains:   MIDI Services driver interfaces
 
 	Copyright:  (c) 2000-2008 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/

#ifndef __MIDIDriver_h__
#define __MIDIDriver_h__

#include <CoreFoundation/CFPlugIn.h>
#if COREFOUNDATION_CFPLUGINCOM_SEPARATE
#include <CoreFoundation/CFPlugInCOM.h>
#endif
#include <CoreFoundation/CFRunLoop.h>
#include <CoreMIDI/CoreMIDI.h>

/*!
	@header MIDIDriver.h
	
	This is the header file for Mac OS X's MIDI driver interface.
	
	<h2>About MIDI drivers</h2>
	MIDI drivers are CFPlugIns, installed into the following places:
<pre>
    /System/Library/Extensions      -- not recommended for non-Apple drivers, but
                                    necessary for compatibility with CoreMIDI 1.0
    
    /Library/Audio/MIDI Drivers     -- starting with CoreMIDI 1.1
    
    ~/Library/Audio/MIDI Drivers    -- starting with CoreMIDI 1.1
</pre>
	Refer to the CFPlugIn documentation for more information about plug-ins.
	
	<h2>Driver bundle/plug-in properties</h2>
	A driver's bundle settings should include settings resembling the following:
<pre>
    Bundle settings:
        CFBundleIdentifier              String          com.mycompany.midi.driver.mydevice
            (note that this will be the driver's persistent ID in MIDISetup's)
        CFPlugInDynamicRegistration     String          NO
        CFPlugInFactories               Dictionary      1 key/value pair
            [your new factory UUID]     String          [your factory function name]
        CFPlugInTypes                   Dictionary      1 key/value pair
            ECDE9574-0FE4-11D4-BB1A-0050E4CEA526        Array       1 object
                (this is kMIDIDriverTypeID)
                0                       String          [your new factory UUID]
    Build settings:
        WRAPPER_EXTENSION               plugin
</pre>
	
	<h2>Driver access to the CoreMIDI API</h2>
	Drivers have access to most of the CoreMIDI API.  Starting in Mac OS X 10.6,
	drivers should link with CoreMIDI.framework. In previous versions of Mac OS X,
	drivers should link with CoreMIDIServer.framework, <b>not</b> CoreMIDI.framework.
	
	On Mac OS X versions prior to 10.6, MIDI driver plugins linked against the
	CoreMIDIServer framework in order to access the CoreMIDI API. Drivers which
	are to run on earlier OS versions should be built 32-bit fat (ppc and i386)
	and link against CoreMIDIServer. Drivers which are to run on Mac OS X 10.6
	and later should be built for x86_64 and link against the CoreMIDI
	framework. Drivers which are to run on all versions of Mac OS X should be
	build 3-way fat (ppc, i386, and x86_64), with the ppc and i386 slices
	linking against CoreMIDIServer, and the x86_64 slice linking against
	CoreMIDI.

	Unlike applications, drivers communicate with the server directly, not 
	through Mach messaging.  This necessitates some limitations on the contexts from 
	which a driver may call the server.
	
	The MIDI I/O functions MIDISend and MIDIReceived may be called from any thread.
	
	All other CoreMIDI functions must only be called from the server's main thread, which is the
	thread on which the driver is created and from which all calls to the driver other than
	Send() are made.
*/

typedef struct MIDIDriverInterface		MIDIDriverInterface;

/*!
	@typedef		MIDIDriverRef
	
	@discussion		Points to a pointer to a MIDIDriverInterface, a CFPlugIn
					structure (defined in MIDIDriver.h) containing function
					pointers for the driver's methods.  Only the MIDIServer
					may call a driver's methods.
*/
typedef MIDIDriverInterface **			MIDIDriverRef;

/*!
	@typedef		MIDIDeviceListRef
	
	@discussion		A MIDIDeviceListRef is a list of MIDIDeviceRef's.  The devices are
					not owned by the list (i.e., disposing the list does not dispose
					the devices it references).
*/
#if __LP64__
typedef MIDIObjectRef MIDIDeviceListRef;
#else
typedef struct OpaqueMIDIDeviceList*    MIDIDeviceListRef;
#endif

/*!
	@interface		MIDIDriverInterface
	
	@abstract		The COM-style interface to a MIDI driver.
	
	@discussion
		This is the function table interface to a MIDI driver.  Both version 1 and 2 drivers use
		this same table of function pointers (except as noted).

		Drivers which support both the version 1 and version 2 interfaces can tell which version
		of the server is running by checking to see whether kMIDIDriverInterface2ID or
		kMIDIDriverInterfaceID is passed to the factory function.  If the version 1 interface is
		requested, the driver should behave as if it is a version 1 driver.
*/
struct MIDIDriverInterface
{
	IUNKNOWN_C_GUTS;

	/*!
		@function FindDevices
		@discussion
			This is only called for version 1 drivers.  The server is requesting that the driver
			detect the devices which are present.  For each device present, the driver should
			create a MIDIDeviceRef with entities, using MIDIDeviceCreate and
			MIDIDeviceAddEntity, and add the device to the supplied MIDIDeviceListRef, using
			MIDIDeviceListAddDevice.

			The driver should not retain any references to the created devices and entities.
	*/	
	OSStatus	(*FindDevices)(MIDIDriverRef self, MIDIDeviceListRef devList);

	/*!
		@function Start
		@discussion
			The server is telling the driver to begin MIDI I/O.

			The provided device list contains the devices which were previously located by
			FindDevices (in the case of a version 1 driver), or the devices which are owned by
			this driver and are currently in the current MIDISetup (for version 2 drivers).

			The provided devices may or may not still be present.  A version 1 driver should
			attempt to use as many of the devices as are actually present.

			A version 2 driver may make calls such as MIDISetupAddDevice, MIDIDeviceAddEntity,
			MIDIDeviceRemoveEntity to dynamically modify the system's current state. For devices
			in the provided device list which are not present, the driver should set their
			kMIDIPropertyOffline property to 1.  A version 2 driver may also set up
			notifications when the IORegistry changes, to detect connection and disconnection of
			devices it wishes to control.  At these times also, the driver may change the
			devices' kMIDIPropertyOffline, and dynamically modify the system's current state to
			reflect the devices which are present.  When passing a CFRunLoopRef to IOKit for
			notification purposes, the driver must use the server's main runloop, which is
			obtained with CFRunLoopGetCurrent().

			The driver will probably want to iterate through the destination endpoints and
			assign their driver refCons, so as to identify multiple destinations when Send() is
			called.

			The provided device list remains owned by the system and can be assumed to contain
			only devices owned by this driver.  The driver may retain references to the devices
			in this list and any it creates while running.
	*/					
	OSStatus	(*Start)(MIDIDriverRef self, MIDIDeviceListRef devList);

	/*!
		@function Stop
		@discussion
			The server is telling the driver to terminate MIDI I/O.  All I/O operations that
			were begun in Start, or as a result of a subsequent IOKit notification, should be
			terminated.
	*/
	OSStatus	(*Stop)(MIDIDriverRef self);
	
	/*!
		@function Configure
		@discussion
			not currently used
	*/
	OSStatus	(*Configure)(MIDIDriverRef self, MIDIDeviceRef device);

	/*!
		@function Send
		@discussion
			Send a MIDIPacketList to the destination endpoint whose refCons are being passed as
			arguments.
	*/
	OSStatus	(*Send)(MIDIDriverRef self, const MIDIPacketList *pktlist, void *destRefCon1, void *destRefCon2);
	
	/*!
		@function EnableSource
		@discussion
			A client has opened or closed a connection, and now the server is telling the driver
			that input from a particular source either does or does not have any listeners in
			the system.  The driver may use this information to decide whether to pass messages
			from the source to the server, and it may even be able to tell the source hardware
			not to generate incoming MIDI I/O for that source.
	*/
	OSStatus	(*EnableSource)(MIDIDriverRef self, MIDIEndpointRef src, Boolean enabled);
	
	/*!
		@function Flush
		@discussion
			Only for version 2 drivers (new for CoreMIDI 1.1).

			Drivers which support schedule-ahead, when receiving this message, should unschedule
			all pending output to the specified destination.  If the destination is null, the
			driver should unschedule all pending output to all destinations.
	*/
	OSStatus	(*Flush)(MIDIDriverRef self, MIDIEndpointRef dest, void *destRefCon1, void *destRefCon2);

	/*!
		@function Monitor		
		@discussion
			Only for version 2 drivers (new for CoreMIDI 1.1).

			Some specialized drivers (e.g. a MIDI monitor display) may wish to intercept and
			look at all outgoing MIDI messages.  After a driver calls
			MIDIDriverEnableMonitoring(true) on itself, this function is called with the
			outgoing MIDI packets for all destinations in the system.  The Monitor function
			cannot rely on the MIDI events arriving in order, due to MIDIServer's schedule-ahead
			facilities.
	*/
	OSStatus	(*Monitor)(MIDIDriverRef self, MIDIEndpointRef dest, const MIDIPacketList *pktlist);
};


//  -----------------------------------------------------------------------------
/*!
	@define			kMIDIDriverTypeID
	
	@abstract		The UUID for MIDI driver plugins.
	
	@discussion		kMIDIDriverTypeID should be entered into your driver's bundle settings
					as follows:
					
<pre>
CFPlugInTypes                   Dictionary      1 key/value pair
	ECDE9574-0FE4-11D4-BB1A-0050E4CEA526        Array       1 object
		(this is kMIDIDriverTypeID)
		0                       String          [your new factory UUID]
</pre>
*/
#define kMIDIDriverTypeID \
	CFUUIDGetConstantUUIDWithBytes(NULL, 0xEC, 0xDE, 0x95, 0x74, 0x0F, 0xE4, 0x11, 0xD4, 0xBB, 0x1A, 0x00, 0x50, 0xE4, 0xCE, 0xA5, 0x26)
/* ECDE9574-0FE4-11D4-BB1A-0050E4CEA526 */


/*!
	@define			kMIDIDriverInterfaceID
	
	@abstract		The UUID for version 1 of the MIDI driver interface.
	
	@discussion		See the description of the MIDIDriverInterface structure for
					information about different versions of the MIDI driver interface.
*/
#define kMIDIDriverInterfaceID \
	CFUUIDGetConstantUUIDWithBytes(NULL, 0x49, 0xDF, 0xCA, 0x9E, 0x0F, 0xE5, 0x11, 0xD4, 0x95, 0x0D, 0x00, 0x50, 0xE4, 0xCE, 0xA5, 0x26)
/* 49DFCA9E-0FE5-11D4-950D-0050E4CEA526 */

/*!
	@define			kMIDIDriverInterface2ID
	
	@abstract		The UUID for version 2 of the MIDI driver interface.
	
	@discussion		See the description of the MIDIDriverInterface structure for
					information about different versions of the MIDI driver interface.
					
					The version 2 driver interface is available beginning with CoreMIDI 1.1.
*/
#define kMIDIDriverInterface2ID \
	CFUUIDGetConstantUUIDWithBytes(NULL, 0x43, 0xC9, 0x8C, 0x3C, 0x30, 0x6C, 0x11, 0xD5, 0xAF, 0x73, 0x00, 0x30, 0x65, 0xA8, 0x30, 0x1E)
/* 43C98C3C-306C-11D5-AF73-003065A8301E */

/*!
	@constant		kMIDIDriverPropertyUsesSerial
	
	@discussion		This constant, "MIDIDriverUsesSerial", when defined to "YES" in a driver's 
					bundle, tells MIDIServer that the driver uses serial ports and is eligible to
					have serial ports assigned to it.
					
					When a serial driver's Start() method is called, it should use
					MIDIGetSerialPortOwner to discover which serial ports it has
					been assigned to use, and only use those ports.
					
					New for CoreMIDI 1.1.
*/
extern const CFStringRef kMIDIDriverPropertyUsesSerial		__OSX_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_NA);


#ifdef __cplusplus
extern "C" {
#endif

// ___________________________________________________________________________________________
//	MIDIDevice
// ___________________________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceCreate

	@discussion		Drivers call this function to create new MIDIDevice objects
					corresponding to the hardware that is present.
					
					Non-drivers may call this function as of CoreMIDI 1.1, to
					create external devices.
	
	@param			owner
						The driver creating the device.  NULL if a non-driver.
	@param			name
						The name of the new device.
	@param			manufacturer
						The name of the device's manufacturer.
	@param			model
						The device's model name.
	@param			outDevice
						On successful return, points to the newly-created device.
	@result			An OSStatus result code.
*/
extern OSStatus		MIDIDeviceCreate(MIDIDriverRef owner, 
							CFStringRef name, CFStringRef manufacturer, 
							CFStringRef model, MIDIDeviceRef *outDevice)
																__OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*!
	@function		MIDIDeviceDispose

	@discussion		Drivers may call this function to dispose MIDIDevice objects
					which have not yet been added to the system via MIDISetupAddDevice.
					Once a device has been added to the system with MIDISetupAddDevice,
					the driver must not use this call to destroy it; it must
					use MIDISetupRemoveDevice to do so.
					
					Non-drivers do not have access to this function; they must call
					MIDISetupAddDevice and MIDISetupRemoveDevice.
	
	@param			device
						The device to be disposed.
	@result			An OSStatus result code.
*/
extern OSStatus		MIDIDeviceDispose(MIDIDeviceRef device)		__OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

// ___________________________________________________________________________________________
//	MIDIDeviceList
// ___________________________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceListGetNumberOfDevices

	@discussion		Returns the number of devices in a device list.
	
	@param			devList
						The device list.
	@result			The number of devices in the list, or 0 if an error occurred.
*/
extern ItemCount		MIDIDeviceListGetNumberOfDevices(MIDIDeviceListRef devList)
																__OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceListGetDevice

	@discussion		Return one of the devices in a device list.
	
	@param			devList
						The device list.
	@param			deviceIndex0
						The index (0...MIDIDeviceListGetNumberOfDevices()-1) of the device
						to return.
	@result			A reference to a device, or NULL if an error occurred.
*/
extern MIDIDeviceRef	MIDIDeviceListGetDevice(MIDIDeviceListRef devList, ItemCount index0)
																__OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceListAddDevice

	@discussion		Add a device to a device list.
	
	@param			devList
						The device list.
	@param			dev
						The device to add to the list.
	@result			An OSStatus result code.
*/
extern OSStatus		MIDIDeviceListAddDevice(MIDIDeviceListRef devList, MIDIDeviceRef dev)
																__OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDeviceListDispose

	@discussion		Dispose a device list, but not the contained devices.
	
	@param			devList
						The device list to be disposed.
	@result			An OSStatus result code.
*/
extern OSStatus		MIDIDeviceListDispose(MIDIDeviceListRef devList)
																__OSX_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_NA);


// ___________________________________________________________________________________________
//	MIDIEndpoint
// ___________________________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIEndpointSetRefCons

	@discussion		Drivers need an efficient way to translate from a MIDIEndpoint (source or
					destination) to their own internal data structures corresponding to
					that endpoint.  This function provides a way for the driver to
					assign its own refCons to endpoints.
					
					These refCons are passed back to the driver in its Send() and Flush()
					methods.
					
					RefCons are not persistent (i.e. they are not saved as part of a 
					MIDISetup).  They need to be re-initialized in each call to Start().
					
					A typical use is to use one refCon to refer to a device, and a second
					to refer to a port on the device.
	
	@param			endpt
						The endpoint whose refCons are to be set
	@param			ref1
						The first refCon.
	@param			ref2
						The second refCon.
	@result			An OSStatus result code.
*/
extern OSStatus		MIDIEndpointSetRefCons(MIDIEndpointRef endpt,
					void *ref1, void *ref2)					__OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIEndpointGetRefCons

	@discussion		Obtain the refCons assigned to the endpoints 
	
	@param			endpt
						The endpoint whose refCons are to be return
	@param			ref1
						On exit, the first refCon.
	@param			ref2
						On exit, the second refCon.
	@result			An OSStatus result code.
*/
extern OSStatus		MIDIEndpointGetRefCons(MIDIEndpointRef endpt, 
					void **ref1, void **ref2)				__OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

// ___________________________________________________________________________________________

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetDriverIORunLoop

	@discussion		Drivers typically need to receive asynchronous I/O completion callbacks
					on a high-priority thread.  To save drivers from the trouble of 
					creating their own threads for this purpose, and to make efficient
					use of system resources, the MIDIServer provides a thread which
					drivers may use.
					
					Drivers should do as little work as possible in this thread; typically,
					just dequeueing and encoding output packets, and decoding input packets
					into MIDIPacketLists to be passed to MIDIReceived.
	
					This is a realtime-priority thread and shouldn't be used for anything other 
					than I/O.  For lower-priority tasks, drivers can use the runloop which 
					was current when they were constructed.

	@result			The CFRunLoopRef of the server's driver I/O thread.
*/
extern CFRunLoopRef	MIDIGetDriverIORunLoop()				__OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIGetDriverDeviceList

	@discussion		Returns the list of devices which are in the current MIDISetup
					and which were created/owned by the specified driver.
	
					The returned device list should be disposed (using MIDIDeviceListDispose)
					by the caller.
					
	@param			driver
						The driver whose devices are to be returned.

	@result			The requested device list.
*/
extern MIDIDeviceListRef	MIDIGetDriverDeviceList(MIDIDriverRef driver)
															__OSX_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_NA);

//  -----------------------------------------------------------------------------
/*!
	@function		MIDIDriverEnableMonitoring

	@discussion		A driver may make this call to have MIDIServer pass it every outgoing MIDI
					packet, to all destinations in the system (not just those controlled by
					itself).
					
	@param			driver
						The driver whose Monitor function is to be enabled.
	@param			enabled
						true to enable monitoring, false to disable it.

	@result			An OSStatus result code.
*/
extern OSStatus			MIDIDriverEnableMonitoring(MIDIDriverRef driver, Boolean enabled)
															__OSX_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_NA);


#ifdef __cplusplus
}
#endif


#endif // __MIDIDriver_h__

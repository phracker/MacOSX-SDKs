/*
     File:       DiscRecording/DRCoreBurn.h
 
     Contains:   Burn object interfaces for DiscRecording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef _H_DRCoreBurn
#define _H_DRCoreBurn

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef _H_DRCoreObject
#include <DiscRecording/DRCoreObject.h>
#endif

#ifndef _H_DRCoreTrack
#include <DiscRecording/DRCoreTrack.h>
#endif

#ifndef _H_DRCoreDevice
#include <DiscRecording/DRCoreDevice.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
	@typedef DRBurnRef
	This is the type of a reference to DRBurn instances.
*/
typedef struct __DRBurn*		DRBurnRef;

/*!
	@function	DRBurnGetTypeID
	@abstract	Returns the type identifier of all DRBurn instances.
	@result		A Core Foundation type ID.
*/
extern
CFTypeID DRBurnGetTypeID()
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRBurnCreate
	@abstract	Creates a new burn.
	@param		device		A reference to the device to burn to. If this parameter is not a 
							valid DRDevice, the behavior is undefined.
	@result		A reference to a new DRBurn.
*/
extern
DRBurnRef DRBurnCreate(DRDeviceRef device)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRBurnWriteLayout
	@abstract	Writes the specified track layout to disc.
	@discussion	The object passed into this function describes the layout of the disc.
				There are three possible layout configurations:
				<ul>
				<li>For a multi-session burn, the layout must be a valid CFArray containing 
				 multiple CFArrays, each of which contains one or more valid DRTrack objects.</li>
				 <li>For a single-session, multi-track burn, the layout must be a valid CFArray 
				 containing one or more valid DRTrack objects.</li>
				 <li>For a single-session, single-track burn, the layout must be a valid
				 DRTrack object.</li>
				 </ul>
				 If either of these configurations are not met or the values contained in the
				 array(s) are not valid DRTrack objects, the behavior is undefined.
	@param		burn	The burn that should be started. If this parameter 
						is not a valid DRBurn, the behavior is undefined. 
	@param		layout	An object describing the layout of the data on disc. If this parameter 
						is not a valid CFArray of homogeneous objects or a valid DRTrack, 
						the behavior is undefined
*/
extern
OSStatus DRBurnWriteLayout(DRBurnRef burn, CFTypeRef layout)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRBurnAbort
	@abstract	Stop the burn.
	@discussion	Aborting a burn may cause a CD to be unusable depending on the amount of data
				that has been written to disc. If nothing has been written then the disc can be
				reused for a different burn. If all data has been written to disc (and a
				verification is being performed, for example) then the disc will be usable
				and the data will be intact (unless the verification would have failed. had it 
				completed). Otherwise, the disc becomes a coaster.
				
				If the burn has not started or has already completed, this function does nothing.
	@param		burn	The burn that should be stopped. If this parameter 
						is not a valid DRBurn, the behavior is undefined. 
*/
extern
void DRBurnAbort(DRBurnRef burn)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRBurnCopyStatus
	@abstract	Obtain the progress/status of the burn.
	@discussion	Returns a CFDictionary containing the progress/status of the burn. This dictionary
				will contain the state, percentage complete and any errors reported.
	@result		A reference to a CFDictionary containing the state and progress of the burn as well as
				any errors reported. The dictionary reference is implicitly retained by the caller.
				This is the same dictionary sent to observers of kDRBurnStatusChangedNotification.
*/
extern
CFDictionaryRef DRBurnCopyStatus(DRBurnRef burn)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const kDRBurnStatusChangedNotification
	@discussion	The notification sent when a DRBurnRef has updated status.
*/
extern const CFStringRef	kDRBurnStatusChangedNotification
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRBurnGetDevice
	@abstract	Returns a reference to the device associated with a burn.
	@param		burn	The burn to get the device for. If this parameter 
						is not a valid DRBurn, the behavior is undefined. 
	@result		A reference of type DRDeviceRef to the device associated with the 
				specified burn. The caller does not implicitly retain the reference,
				and is not responsible for releasing it.
*/
extern
DRDeviceRef DRBurnGetDevice(DRBurnRef burn)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRBurnSetProperties
	@abstract	Sets the properties of the burn.
	@param		burn		The burn to set the properties of. If this parameter 
							is not a valid DRBurn, the behavior is undefined. 
	@param		properties	A CFDictionaryRef containing the burn properties. If this
							parameter is not a valid CFDictionaryRef the behavior is undefined.
*/
extern
void DRBurnSetProperties(DRBurnRef burn, CFDictionaryRef properties)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRBurnGetProperties
	@abstract	Returns properties of the burn.
	@param		burn		A reference of type DRBurnRef to the burn. If this parameter 
							is NULL, the behavior is undefined.
	@result		A reference of type CFDictionaryRef to a dictionary containing the properties 
				of the specified burn. The caller does not implicitly retain the reference,
				and is not responsible for releasing it.
*/
extern
CFDictionaryRef DRBurnGetProperties(DRBurnRef burn)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#pragma mark Burn Properties

/*!
	@const          kDRBurnRequestedSpeedKey         
	@discussion 	The property list key whose value is a CFNumber containing the 
					speed at which the burn should run, expressed as a float value 
					in kilobytes per second. If this key is not present, the speed
					defaultS to kDRDeviceBurnSpeedMax.

					The speed at which a burn runs is dependent on a number of
					factors, these include the speed of the bus the drive is
					connected to, the speed of the media, and how fast data can
					be produced. Any of these can limit the speed at which the
					burn actually runs. For example, a drive might be able to
					burn at 16x, but if it is connected over USB, the maximum
					throughput to that device is at most 2x. On some faster
					drives, there may also be a minimum speed (such as 4x) so
					attempting to set the speed to 1x will not necessarily limit
					the burn speed to 1x.
*/
extern const CFStringRef kDRBurnRequestedSpeedKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBurnAppendableKey
	@discussion	This key points to a CFBoolean containing a flag indicating 
				if the disc will still be appendable after the burn.
				If this key is not present, the burn will default to a value 
				of <tt>false</tt> and the disc will be marked as not appendable.
*/
extern const CFStringRef kDRBurnAppendableKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBurnVerifyDiscKey
	@discussion	This key points to a CFBoolean containing a flag indicating 
				if the disc will be verified after being burned.
				If this key is not present, the burn will default to a value 
				of <tt>true</tt> and the disc will be verified.
*/
extern const CFStringRef kDRBurnVerifyDiscKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBurnCompletionActionKey
	@discussion	This key points to a CFString containing a one of the completion
				actions possible for the disc handling.
				If this key is not present, the burn will default to a value 
				of <tt>kDRBurnCompletionActionEject</tt> and the disc will 
				be ejected.
*/
extern const CFStringRef kDRBurnCompletionActionKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! 
	@const			kDRBurnCompletionActionEject	
	@discussion		A CFString indicating that the burn object should eject the disc from the drive
					when the burn completes.
*/
extern const CFStringRef	kDRBurnCompletionActionEject
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! 
	@const			kDRBurnCompletionActionMount	
	@discussion		A CFString indicating that the burn object should mount the disc on the desktop 
					when the burn completes.
*/
extern const CFStringRef	kDRBurnCompletionActionMount
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBurnUnderrunProtectionKey
	@discussion	This key points to a CFBoolean containing a flag indicating 
				if burn underrun protection will be on or off for devices which
				support it.
				
				Usually burn underrun protection is by default turned on for 
				those drives which support it. Clients typically only need to 
				set this to explicitly disable it.
				
				If this key is not present, the burn will default to a value 
				of <tt>true</tt> and burn underrun protection will enabled (if possible) 
*/
extern const CFStringRef kDRBurnUnderrunProtectionKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBurnTestingKey
	@discussion	This key points to a CFBoolean containing a flag indicating 
				if the burn will be a test or not.
				
				When this is set and DRBurnWriteLayout is called for the burn object this 
				is set on, the entire burn process proceeds as if data would be 
				written to the disc, but the laser is not turned on to full power, so
				the disc is not modified.
				
				If this key is not present, the burn will default to a value 
				of <tt>false</tt> and a normal burn will occur. 
*/
extern const CFStringRef kDRBurnTestingKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRSynchronousBehaviorKey
	@discussion	This key points to a CFBoolean containing a flag indicating 
				if burn operations will behave synchronously.  If this key is
				not present, it will default to a value of <tt>false</tt> and
				burn operations will behave asynchronously.
				
				Synchronous operations do not post status notifications, and
				will not return until they are completed.  Status can still
				be queried at any time, and will remain valid even after the
				burn operation has finished.
*/
extern const CFStringRef kDRSynchronousBehaviorKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#ifdef __cplusplus
}
#endif

#endif /* _H_DRCoreBurn */

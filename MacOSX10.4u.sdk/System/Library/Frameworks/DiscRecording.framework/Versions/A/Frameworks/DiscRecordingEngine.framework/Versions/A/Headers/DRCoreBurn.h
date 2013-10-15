/*
     File:       DiscRecordingEngine/DRCoreBurn.h
 
     Contains:   Burn object interfaces for Disc Recording.
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002-2003 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*!	@header 	
	@abstract		Burn object interfaces for Disc Recording.

	@discussion		
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
#include <DiscRecordingEngine/DRCoreObject.h>
#endif

#ifndef _H_DRCoreTrack
#include <DiscRecordingEngine/DRCoreTrack.h>
#endif

#ifndef _H_DRCoreDevice
#include <DiscRecordingEngine/DRCoreDevice.h>
#endif

#ifndef __AVAILABILITYMACROS__
#include <AvailabilityMacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
	@typedef DRBurnRef
	A reference to DRBurn instances.
*/
typedef struct __DRBurn*		DRBurnRef;

/*!
	@function	DRBurnGetTypeID
	@abstract	Obtains the type identifier of all DRBurn objects.
	@result		A Core Foundation type identifier.
*/
extern
CFTypeID DRBurnGetTypeID()
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRBurnCreate
	@abstract	Creates a new burn.
	@param		device		A reference to the device to burn to. If this parameter is not a 
							valid DRDevice, the behavior is undefined.
	@result		Returns reference to a new DRBurn instance.
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
				<li>For a multisession burn, the layout must be a valid CFArray object containing 
				 multiple CFArrays, each of which contains one or more valid DRTrack objects.</li>
				 <li>For a single-session, multitrack burn, the layout must be a valid CFArray object
				 containing one or more valid DRTrack objects.</li>
				 <li>For a single-session, single-track burn, the layout must be a valid
				 DRTrack object.</li>
				 </ul>
				 If either of these configurations are not met or the values contained in the
				 array(s) are not valid DRTrack objects, the behavior is undefined.
	@param		burn	The burn that should be started. If this parameter 
						is not a valid DRBurn object, the behavior is undefined. 
	@param		layout	An object describing the layout of the data on disc. The most common layout 
						consists of a CFArray object whose elements are DRTrack objects. The other layout
						options are a lone DRTrack object, and a CFArray of homogeneous CFArrays of 
						DRTracks. If  the layout is not one of these kinds, or if any of the objects is 
						not valid, this function's behavior is undefined.
	@result		An error code indicating if the burn could begin.
*/
extern
OSStatus DRBurnWriteLayout(DRBurnRef burn, CFTypeRef layout)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRBurnAbort
	@abstract	Stops the burn.
	@discussion	Aborting a burn may make CD unusable depending on the amount of data
				written. If nothing has been written then the disc can be
				reused as a blank. If all the data has been written (and a
				verification is in progress, for example) then the disc will be usable
				and the data will be intact, unless the verification would have failed. 
				Otherwise, the disc will be unusable.
				
				If the burn has not started or has already completed, this function does nothing.
	@param		burn	The burn that should be stopped. If this parameter 
						does not contain a valid DRBurn object, the behavior is undefined. 
*/
extern
void DRBurnAbort(DRBurnRef burn)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRBurnCopyStatus
	@abstract	Obtains the progress and status of the burn.
	@discussion	Returns a CFDictionary object containing the progress and status of the burn. 
				This dictionary will contain the state, percentage complete, and any errors reported.
	@param		burn	The burn for which status is wanted. If this parameter is not a valid
				DRBurn object, the behavior is undefined.
	@result		Returns a reference to a CFDictionary object. The reference is implicitly retained 
				by the caller. This is the same dictionary sent to observers of the 
				@link kDRBurnStatusChangedNotification kDRBurnStatusChangedNotification @/link notification.
*/
extern
CFDictionaryRef DRBurnCopyStatus(DRBurnRef burn)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRBurnGetDevice
	@abstract	Obtains a reference to the device associated with a burn.
	@param		burn	The burn for which to get the device reference. If this parameter 
						is not a valid DRBurn object, the behavior is undefined. 
	@result		Returns a reference of type @link DRDeviceRef DRDeviceRef @/link. The caller does not implicitly retain the reference
				and is not responsible for releasing it.
*/
extern
DRDeviceRef DRBurnGetDevice(DRBurnRef burn)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*!
	@function	DRBurnSetProperties
	@abstract	Sets the properties of the burn.
	@param		burn		The burn for which to set the properties. If this parameter 
							is not a valid DRBurn object, the behavior is undefined. 
	@param		properties	A reference to a CFDictionary object. If this
							parameter does not reference a valid CFDictionary object the 
							behavior is undefined.
*/
extern
void DRBurnSetProperties(DRBurnRef burn, CFDictionaryRef properties)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	DRBurnGetProperties
	@abstract	Obtains properties of the burn.
	@param		burn		The burn for which to get properties. If this parameter 
							is NULL the behavior is undefined.
	@result		Returns a reference to a CFDictionary object. The caller does not implicitly retain 
				the reference and is not responsible for releasing it.
*/
extern
CFDictionaryRef DRBurnGetProperties(DRBurnRef burn)
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#pragma mark Notifications
/* ---------------------------------- */
/* Notifications */
/*!
	@const			kDRBurnStatusChangedNotification
	@discussion		The notification sent when a DRBurn object has updated status.
*/
extern const CFStringRef	kDRBurnStatusChangedNotification
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



#pragma mark Burn Properties
/* ---------------------------------- */
/* Burn properties.  All burn properties are optional; if no value is
	set for any property the burn engine chooses a reasonable default behavior. */
/*!
	@const          kDRBurnRequestedSpeedKey
	@abstract		The requested speed of the burn.
	@discussion 	This burn property key corresponds to a CFNumber object containing the speed at 
					which the burn should run, expressed as a floating point value in kilobytes per 
					second where 1 kilobyte = 1,000 bytes. If this key is not present, the requested 
					maximum burn speed defaults to @link kDRDeviceBurnSpeedMax kDRDeviceBurnSpeedMax @/link.
					
					The speed at which the burn will run depends on several factors including the 
					speed of the bus to which the drive is connected, the data rate capacity of the,  
					disc, the sustained rate at which data can be produced, and the limit your 
					application sets in the @link kDRMaxBurnSpeedKey kDRMaxBurnSpeedKey @/link track property keys. For example, a 16x 
					drive connected over USB 1.0 results in a maximum sustainable throughput to the 
					drive of just 2x due to the bandwidth limitation of the bus.
					
					Some faster drives have a minimum burn speed. In the case of a drive whose minimum 
					speed is 4x, for example, requesting a 1x burn will result in an actual burn speed 
					of 4x.
*/
extern const CFStringRef kDRBurnRequestedSpeedKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBurnAppendableKey
	@abstract	Flag indicating whether or not the disc should remain appendable after the burn.
	@discussion	This burn property key corresponds to a CFBoolean object containing a flag indicating 
				if the disc should still be appendable after the burn.
				If this key is not present, the burn will default to a value 
				of <tt>false</tt> and the disc will be closed.
				
				Most CD formats do not allow unclosed discs, and many types of CD readers will 
				not work with discs that are left appendable. Don't change the value of this 
				key unless you understand the consequences.
*/
extern const CFStringRef kDRBurnAppendableKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBurnOverwriteDiscKey
	@abstract	Flag indicating whether the disc should be appended to or overwritten.
	@discussion	This burn property key corresponds to a CFBoolean object containing a flag indicating 
				if the disc will be overwritten from block zero for the burn.
				If this key is not present, the burn will default to a value 
				of <tt>false</tt> and the disc will be appended.
				
				Overwriting requires the media either be blank or erasable,
				and is functionally equivalent to an erase followed by a burn.
*/
extern const CFStringRef kDRBurnOverwriteDiscKey
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRBurnVerifyDiscKey
	@abstract	Flag indicating whether the disc will be verified after the burn.
	@discussion	This burn property key corresponds to a CFBoolean object containing a flag indicating 
				if the disc will be verified after being burned.
				If this key is not present, the burn will default to a value 
				of <tt>true</tt> and the disc will be verified.
				
				Verification requires each DRTrack object to specify its
				verification method by way of the kDRVerificationTypeKey key in the track
				properties dictionary.  If none of the DRTrack objects in the burn have specified
				a verification method, verification will not occur.
*/
extern const CFStringRef kDRBurnVerifyDiscKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBurnCompletionActionKey
	@abstract	The action to take upon burn completion, with a default of eject.
	@discussion	This burn property key corresponds to a CFString object containing one of the available completion
				actions for disc handling.
				
				If this key is not present, the burn will default to a value 
				of @link kDRBurnCompletionActionEject kDRBurnCompletionActionEject @/link and the disc will 
				be ejected.
*/
extern const CFStringRef kDRBurnCompletionActionKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBurnUnderrunProtectionKey
	@abstract	Flag indicating whether burn underrun protection will be on or off.
	@discussion	This burn property key corresponds to a CFBoolean object containing a flag indicating 
				whether burn underrun protection will be on or off, for devices which
				support it.
				
				Burn underrun protection is on by default for drives which support it. 
				Clients do need to set this value except to explicitly disable underrun
				protection.
				
				If this key is not present, the burn will default to a value 
				of <tt>true</tt> and burn underrun protection will enabled, if the drive
				supports it.
*/
extern const CFStringRef kDRBurnUnderrunProtectionKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBurnTestingKey
	@abstract	Flag indicating whether to perform a test or normal burn.
	@discussion	This burn property key corresponds to a CFBoolean object containing a flag indicating 
				whether the burn will be a test or not.
				
				If testing is set and your application calls the DRBurnWriteLayout 
				function, the burn process proceeds as if data would be written to 
				the disc--but the laser is not turned on to full power so the disc is not 
				modified.

                If this key is not present or the selected burning device does not support test burning,
		        the burn will default to a value of <tt>false</tt> and a normal burn will occur.
*/
extern const CFStringRef kDRBurnTestingKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRSynchronousBehaviorKey
	@abstract	Flag indicating whether to burn synchronously or asynchronously.
	@discussion	This burn property key corresponds to a CFBoolean object containing a flag indicating 
				if burn operations will behave synchronously.  If this key is
				not present, it will default to a value of <tt>false</tt> and
				burn operations will behave asynchronously.
				
				Synchronous operations do not post status notifications and
				do not return until they are completed.  Status can 
				be queried at any time using the @link DRBurnCopyStatus DRBurnCopyStatus @/link function, and will 
				remain valid even after the burn operation has finished.
*/
extern const CFStringRef kDRSynchronousBehaviorKey
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@const		kDRBurnFailureActionKey
	@abstract	The action to take upon burn failure, with a default of eject.
	@discussion	This burn property key corresponds to a CFString object containing one of the available failure
				actions for disc handling.
				
				If this key is not present, the burn will default to a value 
				of @link kDRBurnFailureActionEject kDRBurnFailureActionEject @/link and the disc will 
				be ejected.
*/
extern const CFStringRef kDRBurnFailureActionKey
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRMediaCatalogNumberKey
	@abstract	The Media Catalog Number (MCN) to write to disc.
	@discussion	This burn property key corresponds to a CFData object containing exactly 13 bytes of data
				to be written to the disc as the Media Catalog Number (MCN).
				If this key is not present it will default to all zeroes,
				indicating that an MCN is not supplied.
				
				This value is the standard UPC/EAN product number, and should conform to the
				specifications of the UCC and EAN.  See <a href="http://www.ean-int.org">http://www.ean-int.org</a> and
				<a href="http://www.uc-council.org">http://www.uc-council.org</a> for more information.
*/				
extern const CFStringRef kDRMediaCatalogNumberKey
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		DRBurnDoubleLayerL0DataZoneBlocksKey
	@discussion	This burn property key corresponds to a CFNumber containing the number of blocks desired
				for the layer 0 data zone on a double layer writable disc.
				
				The size of the layer 0 data zone dictates where the transition point is from layer 0 to
				layer 1. If this key is present, the data zone size will be set prior to the start of the
				burn using the value for this key. If it is not present, the default layer 0 data zone will 
				be used (half the available blocks on an empty disc).
				
				The transition point can be specified two ways. If the value specified in this key is
				greater than 1.0, then it will designate an absolute block number for the transition point. In
				this case, the block number should be a multiple of 16 and at least 40000h per specification. If
				the value is less than 1.0, it will specify the percentage of the burn that should reside on
				layer 0. A typical value is 0.5, designating half the burn for each layer. A value of 0.0 or 1.0
				will not change the layer 0 transition point.
*/				
extern const CFStringRef kDRBurnDoubleLayerL0DataZoneBlocksKey
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@const		kDRBurnStrategyKey
	@abstract	One or more suggested burn strategies.
	@discussion	This burn property key corresponds to a CFString object, or to a CFArray object containing
				CFString objects, indicating the suggested burn strategy or strategies.  
				If this key is not present, the burn engine picks an appropriate burn 
				strategy automatically--so most clients do not need to specify a burn strategy.
				
				When more than one strategy is suggested, the burn engine attempts to
				use the first strategy in the list which is available.  A burn strategy
				will never be used if it cannot write the required data. For example, the 
				track-at-once (TAO) strategy cannot write CD-Text.
				
				This presence of this key alone is just a suggestion--if the burn
				engine cannot fulfill the request it will burn using whatever
				strategy is available.  To convert the suggestion into a requirement, add the
				@link kDRBurnStrategyIsRequiredKey kDRBurnStrategyIsRequiredKey @/link key with a value of <tt>true</tt>.
				
				Before using this key you should ensure that the device
				supports the strategy or strategies requested. Do this by checking the
				burn strategy keys in the device's write capabilities dictionary.
*/
extern const CFStringRef kDRBurnStrategyKey
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRBurnStrategyIsRequiredKey
	@abstract	Flag indicating whether to attempt to enforce the specified burn strategies.
	@discussion	This burn property key corresponds to a CFBoolean object indicating whether the burn
				strategy or strategies listed for the @link kDRBurnStrategyKey kDRBurnStrategyKey @/link key are
				the only ones allowed.  If this key is not present, the burn will 
				behave as though the key were <tt>false</tt>.
				
				If this key's value is set to <tt>true</tt> and the device does
				not support any of the suggested burn strategies, the burn
				will fail with a return value of @link //apple_ref/c/econst/kDRDeviceBurnStrategyNotAvailableErr kDRDeviceBurnStrategyNotAvailableErr @/link.
				
				If this key's value is set to <tt>false</tt> and the device does
				not support any of the suggested burn strategies, the engine
				will choose an alternate burn strategy. The burn strategy
				used will provide an equivalent disc.
*/
extern const CFStringRef kDRBurnStrategyIsRequiredKey
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRCDTextKey
	@discussion	This burn property key corresponds to a @link //apple_ref/c/tdef/DRCDTextBlockRef DRCDTextBlockRef @/link object, or to an array of @link //apple_ref/c/tdef/DRCDTextBlockRef DRCDTextBlockRef @/link
				objects, containing the CD-Text information for the disc.  If this key
				is not present, the burn will not write CD-Text.
				
				Before using this key you should ensure that the device
				supports CD-Text by checking the value of the @link //apple_ref/c/data/kDRDeviceCanWriteCDTextKey kDRDeviceCanWriteCDTextKey @/link
				key in the device's write capabilities dictionary.
				
				If this value is set to <tt>true</tt> and the device does
				not support writing CD-Text, the burn will fail with a value of
				@link //apple_ref/c/econst/kDRDeviceCantWriteCDTextErr kDRDeviceCantWriteCDTextErr @/link.  
*/
extern const CFStringRef kDRCDTextKey
AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* ---------------------------------- */
/* Completion actions */
/*! 
	@const			kDRBurnCompletionActionEject
	@abstract		A CFString object indicating that the drive should eject the disc 
					when the burn completes.
*/
extern const CFStringRef	kDRBurnCompletionActionEject
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! 
	@const			kDRBurnCompletionActionMount	
	@abstract		A CFString object indicating that the Disc Recording engine should mount the 
					disc on the desktop when the burn completes.
*/
extern const CFStringRef	kDRBurnCompletionActionMount
AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* ---------------------------------- */
/* Failure actions */
/*! 
	@const			kDRBurnFailureActionEject	
	@abstract		A CFString object indicating that the drive should eject the disc 
					if the burn fails.
*/
extern const CFStringRef	kDRBurnFailureActionEject
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*! 
	@const			kDRBurnFailureActionNone	
	@abstract		A CFString object indicating that the drive should do nothing with the disc 
					if the burn fails.
*/
extern const CFStringRef	kDRBurnFailureActionNone
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* ---------------------------------- */
/* Burn strategies */
/*!
	@const		kDRBurnStrategyCDTAO
	@abstract	A CFString object representing the track-at-once (TAO) burn strategy for CD.
*/
extern const CFStringRef kDRBurnStrategyCDTAO
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRBurnStrategyCDSAO
	@abstract	A CFString object representing the session-at-once (SAO) burn strategy for CD.
*/
extern const CFStringRef kDRBurnStrategyCDSAO
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRBurnStrategyCDRaw
	@abstract	A CFString object representing the CD raw mode burn strategy used for CD.
	
	@discussion	A raw mode burn writes client-defined lead-in, program area, and lead-out data to CD media 
				in a single pass. It supports options such as single-pass writing of a multisession 
				disc. The Multi-Media Command Set (MMC) standard name for this strategy is "raw" but it 
				is often called disc-at-once (DAO).
*/
extern const CFStringRef kDRBurnStrategyCDRaw
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@const		kDRBurnStrategyDVDDAO
	@abstract	A CFString object representing the disc-at-once (DAO) burn strategy for DVD.
	
	@discussion	This strategy applies only to DVDs. It is not valid when burning to CD media.
*/
extern const CFStringRef kDRBurnStrategyDVDDAO
AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


#ifdef __cplusplus
}
#endif

#endif /* _H_DRCoreBurn */

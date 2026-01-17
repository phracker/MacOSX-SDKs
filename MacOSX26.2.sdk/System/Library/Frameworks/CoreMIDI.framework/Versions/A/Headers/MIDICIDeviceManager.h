/*
 File:		CoreMIDI/MIDICIDeviceManager.h

 Contains:	API for MIDI Capability Inquiry (MIDI-CI) Device Manager

 Copyright:	(c) 2024 by Apple Inc., all rights reserved.

 Bugs?:		For bug reports, consult the following page on the World Wide Web:

 http://feedbackassistant.apple.com/
 */

#if !defined(MIDICIDeviceManager_h)
#define MIDICIDeviceManager_h

/*!
	@header MIDICIDeviceManager.h

	This is the header file for MIDI-CI Device manager system services.

	API Overview
	------------
	The singleton object MIDICIDeviceManager maintains a local copy of the system-wide MIDI-CI device
	cache. Various notifications can be observed from the shared MIDICIDeviceManager object which are
	posted when changes to the cache are made by the MIDI server. (Note that in environments where virtual
	MIDI endpoint creation is not allowed (for example, on iOS, if your app doesn't list 'audio' in UIBackgroundModes), 	notifications will only be posted when the client process is not suspended.)

	Implementation overview
	-----------------------
	To investigate the local copy of the MIDI-CI Device cache, retrieve the local instance of the UMPCI manager
	object and examine the manager's properties.

	This API is not realtime-safe. The local cache is updated on the client process main thread and all interaction with
	the manager should be done on the main thread.

	Please visit http://www.midi.org/specifications for more information on MIDI 2.0 and UMP.
*/

#import <CoreMIDI/MIDIUMPCI.h>
#import <CoreMIDI/MIDIUMPCIProfile.h>

// This API requires the modern Objective-C runtime.
#if defined(__OBJC2__)
#import <Foundation/Foundation.h>
#import <stdint.h>

NS_ASSUME_NONNULL_BEGIN

@class MIDICIDevice;

#pragma mark MIDICIDeviceManager Notifications

/*!
	@constant		MIDICIDeviceWasAddedNotification
	@brief			A notification posted when a MIDI-CI Device has been added to the subsystem.

	@discussion		The userInfo dictionary will contain a MIDICIDeviceObjectKey with the
					MIDI-CI Device which has been added to the subsystem.
*/
OS_EXPORT NSNotificationName const MIDICIDeviceWasAddedNotification MIDI_AVAILABLE_UMP1_1 NS_SWIFT_NAME(MIDICIDeviceManager.deviceWasAddedNotification);

/*!
	@constant		MIDICIDeviceWasRemovedNotification
	@brief			A notification posted when a MIDI-CI Device has been removed or has had its MUID invalidated.

	@discussion		Any previously discovered MIDICIDevice that fails to respond to a discovery message
					will be removed. The userInfo dictionary will contain a MIDICIDeviceObjectKey with the
					MIDI-CI Device which has been removed or has had its MUID invalidated.
*/
OS_EXPORT NSNotificationName const MIDICIDeviceWasRemovedNotification MIDI_AVAILABLE_UMP1_1 NS_SWIFT_NAME(MIDICIDeviceManager.deviceWasRemovedNotification);

/*!
	@constant		MIDICIProfileWasUpdatedNotification
	@brief			A notification posted when a MIDI-CI Device has been enabled/disabled or updated.

	@discussion		The userInfo dictionary will contain a MIDICIDeviceObjectKey and
					MIDICIProfileObjectKey with the MIDICIDevice and MIDI-CI Profile which
					was recently enabled or disabled.
*/
OS_EXPORT NSNotificationName const MIDICIProfileWasUpdatedNotification MIDI_AVAILABLE_UMP1_1 NS_SWIFT_NAME(MIDICIDeviceManager.profileWasUpdatedNotification);

/*!
	@constant		MIDICIProfileWasRemovedNotification
	@brief			A notification posted when a MIDI-CI Device has been removed.

	@discussion 	The userInfo dictionary will contain a MIDICIDeviceObjectKey and
					MIDICIProfileObjectKey with the MIDICIDevice and MIDI-CI Profile which
					has been removed.
*/
OS_EXPORT NSNotificationName const MIDICIProfileWasRemovedNotification MIDI_AVAILABLE_UMP1_1 NS_SWIFT_NAME(MIDICIDeviceManager.profileWasRemovedNotification);

#pragma mark Keys for NSNotification userInfo dictionaries

typedef NSString* const MIDICIDeviceManagerDictionaryKey NS_TYPED_ENUM NS_SWIFT_NAME(MIDICIDeviceManager.DictionaryKey);

/*!
	@constant		MIDICIDeviceObjectKey
	@brief			Value is an MIDIUMPEndpoint.
*/
OS_EXPORT MIDICIDeviceManagerDictionaryKey MIDICIDeviceObjectKey MIDI_AVAILABLE_UMP1_1 NS_SWIFT_NAME(MIDICIDeviceManagerDictionaryKey.deviceObject);

/*!
	@constant		MIDICIProfileObjectKey
	@brief			Value is an MIDIUMPCIProfile
*/
OS_EXPORT MIDICIDeviceManagerDictionaryKey MIDICIProfileObjectKey MIDI_AVAILABLE_UMP1_1 NS_SWIFT_NAME(MIDICIDeviceManagerDictionaryKey.profileObject);

#pragma mark MIDICIDeviceManager

/*!
	@class		MIDICIDeviceManager
	@brief		A singleton object that performs system-wide MIDI-CI Device bookkeeping.

	@discussion	MIDICIDeviceManager is used to retrieve information about MIDI-CI devices that
				to MIDI-CI Discovery.
*/
MIDI_AVAILABLE_UMP1_1
@interface MIDICIDeviceManager : NSObject

/*!
	@property   sharedInstance
	@brief		Retrieve the shared MIDI-CI device manager for the client process.

	@discussion	After the first access of the property, the client process may observe notifications which are
				posted when the system-wide cache changes. In environments where virtual MIDI endpoint
				creation is not allowed, callbacks are only invoked when the process is not suspended.
				However, any suspended process will receive an updated copy of the cache when it
				resumes its running state.
 */
@property (class, nonatomic, readonly) MIDICIDeviceManager* sharedInstance NS_SWIFT_NAME(shared);

/*!
	@property	discoveredCIDevices
	@brief		A list of MIDICIDevices that responded to the last MIDI-CI discovery request.
 */
@property (nonatomic, readonly, copy) NSArray<MIDICIDevice*>* discoveredCIDevices;

@end

NS_ASSUME_NONNULL_END

#endif
#endif

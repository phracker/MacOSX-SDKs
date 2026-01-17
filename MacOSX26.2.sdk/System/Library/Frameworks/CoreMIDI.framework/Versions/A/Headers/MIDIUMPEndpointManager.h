/*
 File:		CoreMIDI/MIDIUMPEndpointManager.h

 Contains:	API for MIDI Universal MIDI Packet (UMP) Endpoint and MIDI
			Capability Inquiry (MIDI-CI) Device Manager

 Copyright:  (c) 2024 by Apple Inc., all rights reserved.

 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:

 http://feedbackassistant.apple.com/
 */

#if !defined(MIDIUMPEndpointManager_h)
#define MIDIUMPEndpointManager_h

/*!
	@header MIDIUMPEndpointManager.h

	This is the header file for UMP Endpoint and MIDI-CI device manager (UMPCI manager)  system
	services.

	API Overview
	------------
	The singleton object MIDIUMPEndpointManager maintains a local copy of the system-wide MIDI 2.0 UMP
	Endpoint cache. Various notifications can be observed from the UMPCI manager object when
	changes to the cache occur. (Note that in environments where virtual MIDI endpoint creation is not
	allowed (for example, on iOS, if your app doesn't list 'audio' in UIBackgroundModes), notifications will only
	be posted when the client process is not suspended.)

	Implementation overview
	-----------------------
	To investigate the local copy of the UMPCI cache, retrieve the local instance of the UMPCI manager
	object and examine the manager's properties. Function Blocks with MIDI-CI support, or MIDI-CI devices,
	are listed separately for convenience.

	To investigate the local copy of the MIDI-CI Device cache, retrieve the local instance of the UMPCI manager
	object and examine the manager's properties.

	This API is not realtime-safe. The local cache is updated on the client process main thread and all interaction with
	the manager should be done on the main thread.

	Please visit http://www.midi.org/specifications for more information on MIDI 2.0 and UMP.
*/

#import <CoreMIDI/MIDIUMPCI.h>

// This API requires the modern Objective-C runtime.
#if defined(__OBJC2__)
#import <Foundation/Foundation.h>
#import <stdint.h>

NS_ASSUME_NONNULL_BEGIN

@class MIDIUMPFunctionBlock;
@class MIDICIDevice;
@class MIDIUMPEndpoint;

#pragma mark MIDIUMPEndpointManager Notifications

/*!
	@constant   MIDIUMPEndpointWasAddedNotification
	@brief		A notification posted when a MIDI UMP Endpoint has been added to the subsystem.

	@discussion	The MIDIUMPEndpoint sent in userInfo is the endpoint which was recently discovered.
*/
OS_EXPORT NSNotificationName const MIDIUMPEndpointWasAddedNotification MIDI_AVAILABLE_UMP1_1 NS_SWIFT_NAME(MIDIUMPEndpointManager.endpointWasAddedNotification);

/*!
	@constant   MIDIUMPEndpointWasRemovedNotification
	@brief		A notification posted when a MIDI UMP Endpoint has been removed from the subsystem.

	@discussion	Any MIDIUMPEndpoint sent with this notification is no longer available to the system. Any
				attempt to perform I/O with its source or destination may fail, as the MIDIEndpointRef
				associated with the UMP endpoint may no longer be valid. If this notification is posted,
				any resources related to communication with this UMP endpoint may be safely
				disposed.
*/
OS_EXPORT NSNotificationName const MIDIUMPEndpointWasRemovedNotification MIDI_AVAILABLE_UMP1_1 NS_SWIFT_NAME(MIDIUMPEndpointManager.endpointWasRemovedNotification);

/*!
	@constant   MIDIUMPEndpointWasUpdatedNotification
	@brief		A notification posted when an UMP endpoint updates its stream configuration or changes the
				state of one of its Function Blocks.

	@discussion	If this notification is posted, an Endpoint Info Notification was sent from the UMP endpoint in userInfo.
*/
OS_EXPORT NSNotificationName const MIDIUMPEndpointWasUpdatedNotification MIDI_AVAILABLE_UMP1_1 NS_SWIFT_NAME(MIDIUMPEndpointManager.endpointWasUpdatedNotification);

/*!
	@constant      MIDIUMPFunctionBlockWasUpdatedNotification
	@brief         A notification posted when a Function Block is updated.

	@discussion    If this notification is posted, the supplied Function Block in userInfo has had a change to its
				   enabled state, Group configuration, UI hint, MIDI 1.0 status, etc..
*/
OS_EXPORT NSNotificationName const MIDIUMPFunctionBlockWasUpdatedNotification MIDI_AVAILABLE_UMP1_1 NS_SWIFT_NAME(MIDIUMPEndpointManager.functionBlockWasUpdatedNotification);

#pragma mark Keys for NSNotification userInfo dictionaries

typedef NSString* const MIDIUMPEndpointManagerDictionaryKey NS_TYPED_ENUM NS_SWIFT_NAME(MIDIUMPEndpointManager.DictionaryKey);
/*!
	@constant      MIDIUMPEndpointObjectKey
	@brief         Value is a MIDIUMPEndpoint
*/
OS_EXPORT MIDIUMPEndpointManagerDictionaryKey MIDIUMPEndpointObjectKey MIDI_AVAILABLE_UMP1_1 NS_SWIFT_NAME(MIDIUMPEndpointManagerDictionaryKey.endpointObject);
/*!
	@constant      MIDIUMPFunctionBlockObjectKey
	@brief         Value is a MIDIUMPFunctionBlock
*/
OS_EXPORT MIDIUMPEndpointManagerDictionaryKey MIDIUMPFunctionBlockObjectKey MIDI_AVAILABLE_UMP1_1 NS_SWIFT_NAME(MIDIUMPEndpointManagerDictionaryKey.functionBlockObject);

#pragma mark MIDIUMPEndpointManager

/*!
	@class		MIDIUMPEndpointManager
	@brief		A singleton object that performs system-wide UMP Endpoint bookkeeping.

	@discussion	MIDIUMPEndpointManager is used to retrieve information about UMP Endpoint
				pairs detected by or explicitly declared to the MIDI UMP subsystem.
*/
MIDI_AVAILABLE_UMP1_1
@interface MIDIUMPEndpointManager : NSObject

/*!
	@property   sharedInstance
	@brief		Retrieve the shared UMP Endpoint manager for the client process.

	@discussion	After first access to this property, the client process may begin observing notifications
				which are posted when the system-wide cache changes.
 */
@property (class, nonatomic, readonly) MIDIUMPEndpointManager* sharedInstance NS_SWIFT_NAME(shared);

/*!
	@property	UMPEndpoints
	@brief		A  list of UMP endpoints discovered using UMP endpoint discovery.
 */
@property (nonatomic, readonly, copy) NSArray<MIDIUMPEndpoint*>* UMPEndpoints;

@end

NS_ASSUME_NONNULL_END

#endif
#endif

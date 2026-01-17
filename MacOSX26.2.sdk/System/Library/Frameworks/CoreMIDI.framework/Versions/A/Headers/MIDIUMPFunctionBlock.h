/*
 File:       CoreMIDI/MIDIUMPFunctionBlock.h

 Contains:   API for MIDI 2.0 Function Blocks.

 Copyright:  (c) 2024 by Apple Inc., all rights reserved.

 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:

 http://feedbackassistant.apple.com/
 */

#if !defined(MIDIUMPFunctionBlock_h)
#define MIDIUMPFunctionBlock_h

/*!
	@header MIDIUMPFunctionBlock.h

	This is the header file for MIDI 2.0 Function Block API support, including MIDI Capability
	Inquiry (MIDI-CI).

	API Overview
	------------
	The MIDI server automatically discovers UMP Endpoints, Function Blocks, and performs MIDI-CI
	Discovery. When a client process retrieves the process instance of the UMP and MIDI-CI (UMPCI)
	manager, a copy of the system-wide MIDI 2.0 cache is created using objects that describe the MIDI 2.0
	subsystem.

	A UMP Endpoint (MIDIUMPEndpoint) may declare up to 32 Function Blocks, represented as
	MIDIUMPFunctionBlock objects in the local copy of the system-wide cache. If the Function Block
	properties indicate that the Function Block supports MIDI-CI,  any MIDI-CI-related Function Block
	properties are also populated with the results of MIDI-CI Discovery.

	MIDIUMPMutableFunctionBlock is the client-created counterpart to MIDIUMPFunctionBlock. It is used
	in the following generalized steps:
		1. 	Initialize a new mutable Function Block object, indicating whether there is MIDI-CI support.
			MIDI-CI can only be supported on bidirectional Function Blocks.
		2. 	If the Function Block supports MIDI-CI, add any additional Capbilities and configure the
			appropriate message callbacks.
		3. 	Associate the mutable Function Block object with a mutable UMP Endpoint object
			(MIDIUMPMutableEndpoint).
		4.	Enable the mutable UMP Endpoint object so that the Function Block and its MIDI-CI
			configuration (if any) become part of the MIDI 2.0 system-wide cache.
		5.	Active client processes with a UMPCI Manager instance receive an updated copy of the
			system-wide cache containing an immutable object copy of the mutable Function Block
			object associated with an immutable object copy of the UMP Endpoint object.

	Mutable Function Block objects may only be created in environments where virtual MIDI endpoint creation
	is allowed (for example, on iOS, if your app doesn't list 'audio' in UIBackgroundModes).

	Implementation overview
	-----------------------
	To view the UMP Endpoints and Function Blocks discovered by the MIDI server, retrieve the local process
	instance of the UMPCI manager and view the discovered UMP Endpoints and their associated Function
	Blocks. The UMPCI manager maintains a separate list of Function Blocks that support MIDI-CI.

	If a Function Block supports MIDI-CI, an instance method can be used to retrieve the MIDICIDevice view of
	the Function Block. This linked MIDICIDevice instance is also part of (and discoverable via) the MIDI-CI
	device manager's cache.

	Please visit http://www.midi.org/specifications for more information on MIDI 2.0, Universal
	MIDI Packet and MIDI Capability Inquiry..
*/

#import <CoreMIDI/MIDIUMPCI.h>
#import <CoreMIDI/MIDIUMPEndpoint.h>

// This API requires the modern Objective-C runtime.
#if defined(__OBJC2__)
#import <Foundation/Foundation.h>
#import <stdint.h>

#define MIDI_AVAILABLE_UMP1_1 API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos)

NS_ASSUME_NONNULL_BEGIN

@class MIDICIDevice;

#pragma mark MIDIUMPFunctionBlock

/*!
	@class		MIDIUMPFunctionBlock
	@brief  	An object representing a Function Block.

	@discussion	A Function Block encapsulates one or more UMP groups with a single function, allowing
				agents communicating with that UMP Endpoint to route and process UMP traffic
				properly. Unless the owning MIDIUMPEndpoint has a static Function Block configuration,
				any Function Block metadata may change in response to a configuration change in the
				owning UMP endpoint.
*/
MIDI_AVAILABLE_UMP1_1
@interface MIDIUMPFunctionBlock : NSObject

///	@property 	name
///	@brief		A string containing the Function Block's name.
@property (nonatomic, readonly) NSString* name;

///	@property 	functionBlockID
///	@brief		The device-unique ID for this Function Block.
@property (nonatomic, readonly) MIDIUMPFunctionBlockID functionBlockID;

///	@property	direction
///	@brief		The direction of the Function Block: input, output, or bidirectional.
@property (nonatomic, readonly) MIDIUMPFunctionBlockDirection direction;

///	@property	firstGroup
///	@brief		The first Group spanned by this Function Block.
@property (nonatomic, readonly) MIDIUMPGroupNumber firstGroup;

///	@property	totalGroupsSpanned
///	@brief		The total number of groups spanned by this Function Block.
@property (nonatomic, readonly) MIDIUInteger7 totalGroupsSpanned;

///	@property	maxSysEx8Streams
///	@brief		The maximum number of simultaneous Sysex8 streams.
@property (nonatomic, readonly) UInt8 maxSysEx8Streams;

///	@property	MIDI1Info
///	@brief		MIDI 1.0 speed information.
@property (nonatomic, readonly) MIDIUMPFunctionBlockMIDI1Info MIDI1Info;

///	@property	UIHint
///	@brief		A hint for UI about the primary usage of this Function Block.
@property (nonatomic, readonly) MIDIUMPFunctionBlockUIHint UIHint;

/// @property 	UMPEndpoint
/// @brief		The UMP Endpoint to which this Function Block is registered.
///
/// @discussion If the function block does not belong to an endpoint this property will be nil.
@property (nonatomic, readonly, weak, nullable) MIDIUMPEndpoint* UMPEndpoint;

/// @property     MIDICIDevice
/// @brief        Retrieve the MIDICIDevice class interface if the Function Block supports MIDI-CI.
///
/// @discussion   If a Function Block was created as a MIDICIDevice object, this property will
///               provide an in-place MIDICIDevice interface that may be used with MIDI-CI API. If the
///               device was not created as a MIDICIDevice, this method returns nil.
@property (nonatomic, readonly, weak, nullable) MIDICIDevice* midiCIDevice;

///	@property	isEnabled
///	@brief		The enable state of this Function Block.
@property (nonatomic, readonly) BOOL isEnabled;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif
#endif

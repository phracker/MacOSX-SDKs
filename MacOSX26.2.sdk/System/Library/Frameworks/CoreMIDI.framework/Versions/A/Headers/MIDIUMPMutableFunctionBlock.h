/*
 File:       CoreMIDI/MIDIUMPMutableFunctionBlock.h

 Contains:   API for MIDI 2.0 Function Blocks.

 Copyright:  (c) 2024 by Apple Inc., all rights reserved.

 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:

 http://feedbackassistant.apple.com/
 */

#if !defined(MIDIUMPMutableFunctionBlock_h)
#define MIDIUMPMutableFunctionBlock_h

/*!
	@header MIDIUMPMutableFunctionBlock.h

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
#import <CoreMIDI/MIDIUMPFunctionBlock.h>

// This API requires the modern Objective-C runtime.
#if defined(__OBJC2__)
#import <Foundation/Foundation.h>
#import <stdint.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark MIDIUMPMutableFunctionBlock

/*!
	@class		MIDIUMPMutableFunctionBlock
	@brief  	A mutable Function Block object created by the client process.

	@discussion	A Function Block created with this API may be used in the Function Block configuration
				of a client-created MIDIUMPMutableEndpoint.

				This API is not realtime-safe, all interaction with the function block should be done on the
				main thread.
*/
MIDI_AVAILABLE_UMP1_1
@interface MIDIUMPMutableFunctionBlock : MIDIUMPFunctionBlock

/// @property 	UMPEndpoint
/// @brief		The UMP Endpoint to which this Function Block is registered.
@property (nonatomic, readonly, weak, nullable) MIDIUMPMutableEndpoint* UMPEndpoint;

- (instancetype)init NS_UNAVAILABLE;

/*!
	@method		initWithName:direction:firstGroup:totalGroupsSpanned:maxSysEx8Streams:MIDI1Info:UIHint:isEnabled:
	@brief		The initializer for constructing a Function Block.

	@param		name					The Function Block name.
	@param		direction				The directionality of the Function Block.
	@param		firstGroup				The first UMP Group supported by the Function Block.
	@param		totalGroupsSpanned		The number of UMP groups spanned by the Function Block.
	@param		maxSysEx8Streams		The maximum number of simultaneous Sysex8 streams.
	@param		MIDI1Info				The MIDI 1.0 speed information for the Function Block.
	@param		UIHint					A UI hint for the Function Block.
	@param		isEnabled				The enable state of the Function Block.

	@discussion	This operation will fail if virtual MIDI endpoint creation is not allowed
				(for example, on iOS, if your app doesn't list 'audio' in UIBackgroundModes).
 */
- (instancetype _Nullable)initWithName:(NSString*)name
							 direction:(MIDIUMPFunctionBlockDirection)direction
							firstGroup:(MIDIUMPGroupNumber)firstGroup
					totalGroupsSpanned:(MIDIUInteger7)totalGroupsSpanned
					  maxSysEx8Streams:(MIDIUInteger7)maxSysEx8Streams
							 MIDI1Info:(MIDIUMPFunctionBlockMIDI1Info)MIDI1Info
								UIHint:(MIDIUMPFunctionBlockUIHint)UIHint
							 isEnabled:(BOOL)isEnabled;

/*!
	@method		setEnabled:error:
	@brief		Set whether this Function Block is enabled or disabled.

	@param		isEnabled		The new state of the Function Block.
	@param		error			The out-error used if an error occurred.

	@return     YES for success. NO in the event of a failure, in which case the error is returned in error.

	@discussion	If a Function Block is registered to UMP Endpoint as part of a static configuration,
				the state must always be enabled and may not change. If registered to a UMP Endpoint,
				changes to the Function Block state are propagated to the system-wide cache.
 */
- (BOOL)setEnabled:(BOOL)isEnabled
			 error:(NSError* _Nullable*)error;

/*!
	@method       setName:error:
	@brief        Set the function block name.

	@param        name                      A string representing the name of the function block.
	@param        error                    The out-error used if an error occurs.

	@return       YES for success. NO in the event of a failure, in which case the error is returned in error.

	@discussion   The Function Block name string. Updating the name of a Function Block will cause the
				  updated name to be propagated to all local copies of the system-wide cache.
 */
- (BOOL)setName:(nonnull NSString*)name
		  error:(NSError* _Nullable*)error;

/*!
	@method       reconfigureWithFirstGroup:direction:MIDI1Info:UIHint:error
	@brief        Reconfigure a Function Block.

	@param    firstGroup            The new first Group to use for the Function Block..
	@param    direction              The direction of the Function Block: input, output, or bidirectional.
	@param    MIDI1Info              MIDI 1.0 speed information.
	@param    UIHint                     A hint for UI about the primary usage of this Function Block.

	@discussion    If a mutable Function Block has not been registered to a CI device or was registered in
				a non-static Function Block configuration, the first Group can be changed if the final
				Group spanned by the Function Block is valid after the Function Block has been
				relocated.
				Returns YES if the first Group of the Function Block was changed.
 */
- (BOOL)reconfigureWithFirstGroup:(MIDIUMPGroupNumber)firstGroup
						direction:(MIDIUMPFunctionBlockDirection)direction
						MIDI1Info:(MIDIUMPFunctionBlockMIDI1Info)MIDI1Info
						   UIHint:(MIDIUMPFunctionBlockUIHint)UIHint
							error:(NSError* _Nullable*)error NS_SWIFT_NAME(reconfigure(firstGroup:direction:MIDI1Info:UIHint:));

@end

NS_ASSUME_NONNULL_END

#endif
#endif

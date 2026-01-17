/*
 File:		CoreMIDI/MIDIUMPCIProfile.h

 Contains:	API for MIDI Capability Inquiry (MIDI-CI) Profile Configuration.

 Copyright:	(c) 2024 by Apple Inc., all rights reserved.

 Bugs?:		For bug reports, consult the following page on the World Wide Web:

 http://feedbackassistant.apple.com/
 */

#if !defined(MIDIUMPCIProfile_h)
#define MIDIUMPCIProfile_h

/*!
	@header MIDIUMPCIProfile.h

	This is the header file for MIDI-CI Profile Configuration API.

	API Overview
	------------
	The MIDI server automatically discovers UMP Endpoints, Function Blocks, and performs MIDI-CI
	Discovery. When a client process retrieves the process instance of the UMP and MIDI-CI (UMPCI)
	manager, a copy of the system-wide MIDI 2.0 cache is created using objects that describe the MIDI 2.0
	subsystem.

	Any discovered MIDI-CI device with the Profile Configuration Capability will have its Profile configuration
	cached as CI Profile Objects (MIDIUMPCIProfile). The objects can then be manipulated to perform
	common Profile operations.

	Implementation overview
	-----------------------
	To view the MIDI-CI devices discovered by the MIDI server, retrieve the local process instance of the
	MIDI-CI device manager (MIDICIDeviceManager) and retrieve a copy of the discovered device Array.
	Any CI devices with the Profile Capability may have its Profiles investigated in the 'ciProfiles' property.

	Profiles are enabled or disabled, and a request to Set Profile On or Set Profile Off either using a mutable
	CI device or via the MIDI server's MUID may issued via API. The result of a Set Profile On/Off request is
	received on the local MIDI-CI device manager instance via a notification. In
	environments where virtual MIDI endpoint creation is not allowed, notification is only posted when the
	process is not suspended.

	This API is not realtime-safe.

	Please visit http://www.midi.org/specifications for more information on MIDI 2.0, Universal
	MIDI Packet, and MIDI Capability Inquiry.
*/

#import <CoreMIDI/MIDIUMPCI.h>

// This API requires the modern Objective-C runtime.
#if defined(__OBJC2__)
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MIDICIDevice;
@class MIDICIMutableDevice;

#pragma mark MIDIUMPCIProfile

@class MIDIUMPCIProfile;

/*!
	@class		MIDIUMPCIProfile
	@brief		An object representing Capability Inquiry Profile on a MIDICIDevice.

	@discussion	MIDI-CI profiles describe a mapping of MIDI messages to specific sounds and synthesis
				behaviors, e.g. General MIDI, a drawbar organ, etc. A MIDI-CI Profile may be a standard
				registered Profile or vendor-specific.

				A MIDI-CI Profile ID consists of 5 bytes.
				===============================================================
								Standard Profile			Vendor-Specific Profile
				Profile ID Byte 1:	0x7E Standard Profile		Manufacturer SysEx ID 1 Profile
				Profile ID Byte 2:	Profile Bank			Manufacturer SysEx ID 2 Profile
				Profile ID Byte 3:	Profile Number			Manufacturer SysEx ID 3 Profile
				Profile ID Byte 4:	Profile Version			Manufacturer-specific Info
				Profile ID Byte 5:	Profile Level			Manufacturer-specific Info

				MIDI-CI Profiles have the following generalized types:

				Profile Type		Source		Channels		Channel Range
				============		==========	===========	========================
				Single-channel 		0x00~0x0F 	1			1 channel (1 to 16) of a Group
				Group			0x7E			16			All channels of a Group
				Function Block		0x7F			16 per Group 	All channels of a Function Block
				Multi-channel		0x00~0x0F	2 or more		Profile-specific

				MIDIUMPCIProfile objects may only be registered to a single CI device, and any number
				of MIDIUMPCIProfile objects containg the same profile ID may be registered to CI
				devices in the MIDI 2.0 subsystem.
*/

MIDICI1_2
@interface MIDIUMPCIProfile : NSObject

///	@property 	name
///	@brief		The name of the MIDI-CI proifle.
@property (nonatomic, readonly) NSString* name;

///	@property 	profileID
///	@brief		C struct representation of MIDI-CI Profile ID.
@property (nonatomic, readonly) MIDICIProfileID profileID;

///	@property	profileType
///	@brief		The type of MIDI-CI Profile, i.e., single-channel, multichannel, Group, or Function Block.
@property (nonatomic, readonly) MIDICIProfileType profileType;

///	@property	groupOffset
///	@brief		For Group profiles defined on Function Blocks, the value to be added to the lowest
/// 			Function Block UMP Group for messaging (e.g., a Group Profile defined on the second
/// 			Group of a Function Block has a groupOffset of 1).
@property (nonatomic, readonly) MIDIUMPGroupNumber groupOffset;

///	@property	firstChannel
///	@brief		The first channel number supported on the Profile.
@property (nonatomic, readonly) MIDIChannelNumber firstChannel;

///	@property	enabledChannelCount
///	@brief		The number of channels currently enabled on the Profile. When the profile is disabled,
///				this value is set to 0.
@property (nonatomic, readonly) MIDIUInteger14 enabledChannelCount;

///	@property	totalChannelCount
///	@brief		The total number of channels supported by the Profile.
@property (nonatomic, readonly) MIDIUInteger14 totalChannelCount;

///	@property	isEnabled
///	@brief		The enable state of the Profile.
@property (nonatomic, readonly) BOOL isEnabled;

- (instancetype)init NS_UNAVAILABLE;

/*!
	@method		setProfileState:enabledChannelCount:error:
	@brief		Issue a Set Profile On or Set Profile Off request on this profile using the MIDI server's
				MUID.

	@param		isEnabled			YES if setting the Profile to on.
	@param		enabledChannelCount	The requsted number of channels to be enabled when
									the Profile is enabled. This field is only used when isOn
									is set to YES and the profile can enable a variable number
									of channels. Otherwise, it is ignored.
	@param		error				The out-error used if an error occurred.

	@discussion	The result of this operation, if any, is received via the profile notification
				posted by the MIDICIDeviceManager.
				Returns YES if the request is valid and the request was dispatched.
 */
- (BOOL)setProfileState:(BOOL)isEnabled
	enabledChannelCount:(MIDIUInteger14)enabledChannelCount
				  error:(NSError* _Nullable*)error;

@end

NS_ASSUME_NONNULL_END

#endif
#endif

/*
 File:       CoreMIDI/MIDIUMPEndpoint.h

 Contains:   API for MIDI Universal MIDI Packet (UMP) endpoints

 Copyright:  (c) 2024 by Apple Inc., all rights reserved.

 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:

 http://feedbackassistant.apple.com/
 */

#if !defined(MIDIUMPEndpoint_h)
#define MIDIUMPEndpoint_h

/*!
	@header MIDIUMPEndpoint.h

	This is the header file for Univeral MIDI Packet (UMP) endpoint system services.

	API Overview
	------------
	MIDI 2.0 is inherently bidirectional, and an endpoint that communicates using the Universal MIDI Packet
	(UMP) format (a UMP Endpoint) must be capable of acting as a source of and destination for UMP data.
	The MIDIUMPEndpoint class defines an explicit relationship between a UMP-native MIDI source and a
	UMP-native MIDI destination and encapsulates its stream configuration.

	A MIDIUMPEndpoint is a local cached object copied from the system-wide UMP Endpoint cache into the
	client process instance of the UMP Endpoint manager (MIDIUMPEndpointManager). Any UMP Endpoint
	may declare up to 32 Function Blocks, cached as MIDIUMPFunctionBlock objects registered to a
	MIDIUMPEndpoint. These Function Blocks may also be used as MIDI-CI devices.

	Implementation overview
	-----------------------
	To view the MIDIUMPEndpoint objects discovered by the MIDI server, retrieve the local process instance
	of the UMP Endpoint manager (MIDIUMPEndpointManager) and retrieve a copy of the UMP Endpoint
	Array. Any additional UMP Endpoint information and Function Blocks may be investigated in the discovered
	Capabilities that are cached by the server can be viewed by investigating the CI device properties and by
	using the associated API.

	The singleton object MIDIUMPEndpointManager maintains a local copy of the UMP Endpoint cache and
	may also be used to observe notifications which are posted in response to common UMP subsystem
	cache updates.

	Please visit http://www.midi.org/specifications for more information on MIDI 2.0 and UMP.
*/

#import <CoreMIDI/MIDIUMPCI.h>

// This API requires the modern Objective-C runtime.
#if defined(__OBJC2__)
#import <Foundation/Foundation.h>
#import <stdint.h>

NS_ASSUME_NONNULL_BEGIN

@class MIDIUMPFunctionBlock;
@class MIDIUMPMutableFunctionBlock;
@class MIDIUMPEndpoint;
@class MIDIUMPMutableEndpoint;

#pragma mark MIDI2DeviceInfo

/*!
	@class		MIDI2DeviceInfo
	@brief		An NSObject containing basic information about a MIDI 2.0 device. Used by
				MIDIUMPEndpointPair and MIDICIDevice.
*/
MIDI_AVAILABLE_UMP1_1
@interface MIDI2DeviceInfo : NSObject

///	@property	manufacturerID
///	@brief		The MIDI System Exclusive ID of the device manufacturer, up to 3-Bytes.
///	@discussion One-byte SysEx IDs use only the least significant byte (e.g., Apple's System Exclusive ID, 0x11).
@property (nonatomic, readonly) MIDI2DeviceManufacturer manufacturerID;

///	@property	family
///	@brief		The family of models to which the device belongs, up to 14 bits.
@property (nonatomic, readonly) MIDIUInteger14 family;

///	@property	modelNumber
///	@brief		The specific model from the device manufacturer, up to 14 bits.
@property (nonatomic, readonly) MIDIUInteger14 modelNumber;

///	@property	revisionLevel
///	@brief		The version number of a device model number.
@property (nonatomic, readonly) MIDI2DeviceRevisionLevel revisionLevel;

- (instancetype)init NS_UNAVAILABLE;

/*!
	@method		initWithManufacturerID:family:modelNumber:revisionLevel:
	@brief		The initializer for constructing the MIDI2DeviceInfo object.

	@param		manufacturerID	The 3-Byte manufacturer System Exclusive ID.
	@param		family			The 14-bit device family.
	@param		modelNumber		The 14-bit model number.
	@param		revisionLevel	The 4-Byte revision level.

	@discussion	Provided values for family or modelNumber must be within their expected
				bit range. For example, if modelNumber is outside of the range of a 14-bit number.
 */
- (instancetype)initWithManufacturerID:(MIDI2DeviceManufacturer)manufacturerID
								family:(MIDIUInteger14)family
						   modelNumber:(MIDIUInteger14)modelNumber
						 revisionLevel:(MIDI2DeviceRevisionLevel)revisionLevel;

@end

/*!
	@enum		MIDIUMPProtocolOptions
	@brief		The UMP protocols that can be supported by a UMP endpoint.

	@constant	kMIDIUMPSupportedProtocolMIDI1
					Support for MIDI 1.0 in Universal Packets, or MIDI-1UP.

	@constant	kMIDIUMPSupportedProtocolMIDI2
					Support for MIDI 2.0 protocol.
 */
typedef CF_OPTIONS(MIDIUInteger4, MIDIUMPProtocolOptions) {
	kMIDIUMPProtocolOptionsMIDI1 CF_SWIFT_NAME(midi1) = 1,
		kMIDIUMPProtocolOptionsMIDI2 CF_SWIFT_NAME(midi2) = 1 << 1
	};

/*!
	@class		MIDIUMPEndpoint
	@brief		An object representating a UMP Endpoint.

	@discussion	MIDIUMPEndpoint encapsulates a MIDI source and MIDI destination as a
				bidirectional MIDI 2.0 communication node along with any associated stream
				configuration metadata.

				It is not necessary to create a MIDIUMPEndpoint or other MIDI endpoint in order to
				use UMP natively. Any standard MIDI endpoint created with a specified MIDIProtocolID
				is assumed to use all 16 UMP groups for the same unspecified function and to neither
				transmit nor receive jitter-reduction timestamps.
*/
MIDI_AVAILABLE_UMP1_1
@interface MIDIUMPEndpoint : NSObject

///	@property	name
///	@brief		The UTF-8 encoded name of the UMP endpoint.
///
/// @discussion The name shall not be any longer than 98 bytes of UTF-8 Text.
@property (nonatomic, readonly) NSString* name;

///	@property	MIDIProtocol
///	@brief		The MIDI protocol currently used by the UMP endpoint.
@property (nonatomic, readonly) MIDIProtocolID MIDIProtocol;

///	@property	supportedMIDIProtocols
///	@brief		All protocols the UMP endpoint is capable of using for communication.
@property (nonatomic, readonly) MIDIUMPProtocolOptions supportedMIDIProtocols;

///	@property	MIDIDestination
///	@brief		The MIDI destination for the UMP endpoint.
@property (nonatomic, readonly) MIDIEndpointRef MIDIDestination;

///	@property	MIDISource
///	@brief		The MIDI source for the UMP endpoint.
@property (nonatomic, readonly) MIDIEndpointRef MIDISource;

///	@property	deviceInfo
///	@brief		The MIDI 2.0 Device identity information associated with the device.
@property (nonatomic, readonly) MIDI2DeviceInfo* deviceInfo;

///	@property	productInstanceID
///	@brief		Serial number (or similar value) uniquely identifying this manufacturer/family/model,
///				up to 42 bytes of ASCII Text in the ordinal range 32-126.
@property (nonatomic, readonly) NSString* productInstanceID;

///	@property	hasStaticFunctionBlocks
///	@brief		Indicates if the Function Block state will never change once discovered.
@property (nonatomic, readonly) BOOL hasStaticFunctionBlocks;

///	@property	hasJRTSReceiveCapability
///	@brief		Jitter-reduction timestamp receive capability.
@property (nonatomic, readonly) BOOL hasJRTSReceiveCapability;

///	@property	hasJRTSTransmitCapability
///	@brief		Jitter-reduction timestamp transmit capability
@property (nonatomic, readonly) BOOL hasJRTSTransmitCapability;

///	@property	endpointType
///	@brief		Indicates the type of UMP Endpoint, if known.
@property (nonatomic, readonly) MIDIUMPCIObjectBackingType endpointType;

///	@property	functionBlocks
///	@brief		The Function Blocks associated with the UMP endpoint, if any.
@property (nonatomic, copy) NSArray<MIDIUMPFunctionBlock*>* functionBlocks;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif
#endif

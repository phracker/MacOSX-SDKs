/*
 File:		CoreMIDI/MIDICIDevice.h

 Contains:	API for discovered MIDI Capability Inquiry (MIDI-CI) devices.

 Copyright:	(c) 2024 by Apple Inc., all rights reserved.

 Bugs?:		For bug reports, consult the following page on
 the World Wide Web:

 http://feedbackassistant.apple.com/
 */

#if !defined(MIDICIDevice_h)
#define MIDICIDevice_h

/*!
	@header MIDICIDevice.h

	This is the header file for MIDI-CI device support.

	API Overview
	------------
	The MIDI server automatically discovers Universal MIDI Packet (UMP) Endpoints (MIDIUMPEndpoint)
	and Function Blocks (MIDIUMPFunctionBlock), and it performs MIDI-CI Discovery. When a client process
	retrieves the process instance of the MIDI-CI device manager (MIDICIDeviceManager), the manager
	makes a copy of the system-wide MIDI-CI device cache. Each Responder to a MIDI-CI Discovery request
	is enumerated as a MIDICIDevice object. UMP-native MIDI-CI Devices are typically Function Blocks on
	a UMP Endpoint.

	MIDICIDevice is a UMP-native MIDI 2.0 API, and CI device objects are always associated with enabled,
	bidirectional Function Blocks. If a discovered UMP Endpoint does not explictly declare any Function
	Blocks, it will be assigned an implicit bidirectional Function Block spanning all 16 UMP Groups. In this
	API, MIDICIDevice always extends the Capabilities of a Function Block, explicit or implicit.

	Legacy MIDI 1.0 CI devices are also discovered by the MIDI server. Since the server automatically
	converts UMP to legacy MIDI 1.0 protocol prior to delivery whenever necessary, the MIDI 1.0 source and
	destination pair is treated as a UMP Endpoint with a bidirectional Function Block spanning only Group 0.
	The actual type of MIDI-CI device, if known, is indicated in the object's MIDICIDeviceType.

	Implementation overview
	-----------------------
	To view the MIDI-CI devices discovered by the MIDI server, retrieve the local process instance of the
	MIDI-CI device manager (MIDICIDeviceManager) and retrieve a copy of the discovered device Array.
	Any discovered Capabilities that are cached by the server can be viewed by investigating the CI device
	properties and by using the associated API.

	Please visit http://www.midi.org/specifications for more information on MIDI 2.0, Universal
	MIDI Packet and MIDI Capability Inquiry..
*/

#import <CoreMIDI/MIDIUMPCI.h>
#import <CoreMIDI/MIDIUMPEndpoint.h>
#import <CoreMIDI/MIDIUMPFunctionBlock.h>

// This API requires the modern Objective-C runtime.
#if defined(__OBJC2__)
#import <Foundation/Foundation.h>
#import <stdint.h>

NS_ASSUME_NONNULL_BEGIN

@class MIDIUMPCIProfile;

#pragma mark MIDICIDevice

/*!
	@class		MIDICIDevice
	@brief  	An object representing a MIDI-CI Device.

	@discussion	The client instance MIDICIDeviceManager maintains a list of discovered CI devices.
				MIDICIDevice objects are not constructible via API.
*/
MIDI_AVAILABLE_UMP1_1
@interface MIDICIDevice : NSObject

/// @property   deviceInfo
/// @brief      The basic information describing the CI device.
@property (nonatomic, readonly) MIDI2DeviceInfo* deviceInfo;

///	@property	MUID
///	@brief		The MIDI unique identifier (MUID) assigned to the CI device.
@property (nonatomic, readonly) MIDICIMUID MUID;

///	@property	supportsProtocolNegotiation
///	@brief		MIDI-CI Protocol Negotiation capability.
@property (nonatomic, readonly) BOOL supportsProtocolNegotiation;

///	@property	supportsProfileConfiguration
///	@brief		MIDI-CI Profile Configuration capability.
@property (nonatomic, readonly) BOOL supportsProfileConfiguration;

///	@property	supportsPropertyExchange
///	@brief		MIDI-CI Property Exchange capability.
@property (nonatomic, readonly) BOOL supportsPropertyExchange;

///	@property	supportsProcessInquiry
///	@brief		MIDI-CI Process Inquiry capability.
@property (nonatomic, readonly) BOOL supportsProcessInquiry;

///	@property 	maxSysExSize
///	@brief		The maximum receivable MIDI System Exclusive size for this CI device.
@property (nonatomic, readonly) NSUInteger maxSysExSize;

///	@property 	maxPropertyExchangeRequests
///	@brief		The maximum number of simultaneous Property Exchange requests, if supported.
@property (nonatomic, readonly) NSUInteger maxPropertyExchangeRequests;

///	@property 	deviceType
///	@brief		The type of MIDI-CI device.
@property (nonatomic, readonly) MIDICIDeviceType deviceType;

///	@property	profiles
///	@brief		The MIDI-CI Profiles that are registered to the  Function Block.
@property (nonatomic, readonly) NSArray<MIDIUMPCIProfile*>* profiles;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif
#endif

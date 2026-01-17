/*
	File:   	CoreMIDI/MIDIUMPCI.h

	Contains:	Constants, structures, and helper functions for Universal MIDI
				Packet (UMP) and MIDI Capability Inquiry (MIDI-CI).

	Copyright:  (c) 2024 by Apple Inc., all rights reserved.

	Bugs?:  	For bug reports, consult the following page on
				the World Wide Web:

					http://feedbackassistant.apple.com/

*/

#ifndef CoreMIDI_MIDIUMPCI_h
#define CoreMIDI_MIDIUMPCI_h

#include <CoreFoundation/CFBase.h>
#include <CoreMIDI/MIDIMessages.h>
#include <CoreMIDI/MIDIServices.h>
#import <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MIDICI1_0 API_AVAILABLE(macos(10.14), ios(12.0)) API_UNAVAILABLE(watchos, tvos)
#define MIDICI1_1 API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos)
#define MIDICI1_2 API_AVAILABLE(macos(15.0), ios(18.0)) API_UNAVAILABLE(watchos, tvos)

#define MIDICI1_0_AVAILABILITY API_AVAILABLE(macos(10.14), ios(12.0)) API_UNAVAILABLE(watchos, tvos)
#define MIDICI1_1_AVAILABILITY API_AVAILABLE(macos(11.0), ios(14.0)) API_UNAVAILABLE(watchos, tvos)


#define MIDICI1_0_DEPRECATED API_DEPRECATED("No longer supported for CoreMIDI", macos(10.14, 15.0), ios(12.0, 18.0)) API_UNAVAILABLE(watchos, tvos)
#define MIDICI1_1_DEPRECATED API_DEPRECATED("No longer supported for CoreMIDI", macos(11.0, 15.0), ios(14.0, 18.0)) API_UNAVAILABLE(watchos, tvos)

#define MIDI_AVAILABLE_UMP1_1 API_AVAILABLE(macos(15.0), ios(18.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos)

	typedef struct
	{
		Byte sysExIDByte[3]; // 1-byte SysEx IDs are padded with trailing zeroes
	} MIDI2DeviceManufacturer;

	typedef struct
	{
		Byte revisionLevel[4];
	} MIDI2DeviceRevisionLevel;

	/*!
		@typedef	MIDICICategoryOptions

		@discussion	MIDI Capability category supported (bitmap: D6 D5 D4 D3 D2 D1 D0)
					Bit	Category	Sub-ID Range	Description
					D0			0x00~0x0F	Reserved - No Messages Defined Yet
					D1			0x10~0x1F	Protocol Negotiation (Deprecated)
					D2			0x20~0x2F	Profile Configuration Supported
					D3			0x30~0x3F	Property Exchange Supported
					D4			0x40~0x4F	Process Inquiry Supported
					D5			0x50~0x5F	Reserved - No Messages Defined Yet
					D6			0x60~0x6F	Reserved - No Messages Defined Yet

					e.g., a MIDICIDevice supporting Profile Configuration and Property Exchange has
					category 0xC.
	 */
	typedef CF_OPTIONS(MIDIUInteger7, MIDICICategoryOptions) {
		kMIDICICategoryOptionsProtocolNegotiation = (1UL << 1),
		kMIDICICategoryOptionsProfileConfigurationSupported = (1UL << 2),
		kMIDICICategoryOptionsPropertyExchangeSupported = (1UL << 3),
		kMIDICICategoryOptionsProcessInquirySupported = (1UL << 4),
	};

	/*!
		@typedef	MIDIUMPFunctionBlockID
		@brief		The device-unique Function Block ID.
	 */
	typedef MIDIUInteger7 MIDIUMPFunctionBlockID;

	typedef CF_ENUM(UInt8, MIDICIDeviceType) {
		kMIDICIDeviceTypeUnknown = 0,
		kMIDICIDeviceTypeLegacyMIDI1,
		kMIDICIDeviceTypeVirtual,
		kMIDICIDeviceTypeUSBMIDI CF_SWIFT_NAME(usbMIDI)
		};


//=============================================================================
#pragma mark MIDI-CI Message Types

	/*!
		@enum 		MIDICIProfileMessageType
		@brief		MIDI-CI Profile message sub-ID values.
	 */
	typedef CF_ENUM(MIDIUInteger7, MIDICIProfileMessageType) {
		kMIDICIProfileMessageTypeProfileInquiry = 0x20,
		kMIDICIProfileMessageTypeReplyToProfileInquiry = 0x21,
		kMIDICIProfileMessageTypeSetProfileOn = 0x22,
		kMIDICIProfileMessageTypeSetProfileOff = 0x23,
		kMIDICIProfileMessageTypeProfileEnabledReport = 0x24,
		kMIDICIProfileMessageTypeProfileDisabledReport = 0x25,
		kMIDICIProfileMessageTypeProfileAdded = 0x26,
		kMIDICIProfileMessageTypeProfileRemoved = 0x27,
		kMIDICIProfileMessageTypeDetailsInquiry = 0x28,
		kMIDICIProfileMessageTypeReplyToDetailsInquiry = 0x29,
		kMIDICIProfileMessageTypeProfileSpecificData = 0x2F
	};

	/*!
		@enum		MIDICIPropertyExchangeMessageType
		@brief		MIDI-CI Property Exchange Message sub-ID values.
	 */
	typedef CF_ENUM(MIDIUInteger7, MIDICIPropertyExchangeMessageType) {
		kMIDICIPropertyExchangeMessageTypeInquiryPropertyExchangeCapabilities = 0x30,
		kMIDICIPropertyExchangeMessageTypeReplyToPropertyExchangeCapabilities = 0x31,
		kMIDICIPropertyExchangeMessageTypeInquiryHasPropertyData_Reserved = 0x32,
		kMIDICIPropertyExchangeMessageTypeInquiryReplyToHasPropertyData_Reserved = 0x33,
		kMIDICIPropertyExchangeMessageTypeInquiryGetPropertyData = 0x34,
		kMIDICIPropertyExchangeMessageTypeReplyToGetProperty = 0x35,
		kMIDICIPropertyExchangeMessageTypeInquirySetPropertyData = 0x36,
		kMIDICIPropertyExchangeMessageTypeReplyToSetPropertyData = 0x37,
		kMIDICIPropertyExchangeMessageTypeSubscription = 0x38,
		kMIDICIPropertyExchangeMessageTypeReplyToSubscription = 0x39,
		kMIDICIPropertyExchangeMessageTypeNotify = 0x3F
	};

	/*!
		@enum		MIDICIProcessInquiryMessageType
		@brief		MIDI-CI Process Inquiry sub-ID values.
	 */
	typedef CF_ENUM(MIDIUInteger7, MIDICIProcessInquiryMessageType) {
		kMIDICIProcessInquiryMessageTypeInquiryProcessInquiryCapabilities = 0x40,
		kMIDICIProcessInquiryMessageTypeReplyToProcessInquiryCapabilities = 0x41,
		kMIDICIProcessInquiryMessageTypeInquiryMIDIMessageReport = 0x42,
		kMIDICIProcessInquiryMessageTypeReplyToMIDIMessageReport = 0x43,
		kMIDICIProcessInquiryMessageTypeEndOfMIDIMessageReport = 0x44
	};

	/*!
		@enum		MIDICIManagementMessageType
		@brief		MIDI-CI Management sub-ID values.
	 */
	typedef CF_ENUM(MIDIUInteger7, MIDICIManagementMessageType) {
		kMIDICIManagementMessageTypeDiscovery = 0x70,
		kMIDICIManagementMessageTypeReplyToDiscovery = 0x71,
		kMIDICIManagementMessageTypeInquiryEndpointInformation = 0x72,
		kMIDICIManagementMessageTypeReplyToEndpointInformation = 0x73,
		kMIDICIManagementMessageTypeMIDICIACK CF_SWIFT_NAME(midiCIACK) = 0x7D,
			kMIDICIManagementMessageTypeInvalidateMUID = 0x7E,
			kMIDICIManagementMessageTypeMIDICINAK CF_SWIFT_NAME(midiNAK) = 0x7F
		};


	/*!
		@enum		MIDICIProfileType
		@brief		MIDI-CI Profile variants.
	 */
	typedef CF_ENUM(UInt8, MIDICIProfileType) {
		kMIDICIProfileTypeSingleChannel = 1,
		kMIDICIProfileTypeGroup = 2,
		kMIDICIProfileTypeFunctionBlock = 3,
		kMIDICIProfileTypeMultichannel = 4
	};

	/*!
		@enum       MIDIUMPCIObjectBackingType
		@brief      The underlying transport / backing device type variants.
	 */
	typedef CF_ENUM(UInt8, MIDIUMPCIObjectBackingType) {
		kMIDIUMPCIObjectBackingTypeUnknown = 0,
		kMIDIUMPCIObjectBackingTypeVirtual,
		kMIDIUMPCIObjectBackingTypeDriverDevice,
		kMIDIUMPCIObjectBackingTypeUSBMIDI CF_SWIFT_NAME(usbMIDI)
		};

//=============================================================================
#pragma mark MIDI-CI Profile Constants and Structures

	/*!
		@struct		MIDICIProfileIDStandard
		@brief		A C-style struct containing a standard profile ID.
	 */
	typedef struct
	{
		MIDIUInteger7 profileIDByte1;
		MIDIUInteger7 profileBank;
		MIDIUInteger7 profileNumber;
		MIDIUInteger7 profileVersion;
		MIDIUInteger7 profileLevel;
	} MIDICIProfileIDStandard;

	/*!
		@struct		MIDICIProfileIDManufacturerSpecific
		@brief		A C-style struct containing a Manufacturer Specific profile ID.

	 */
	typedef struct
	{
		MIDIUInteger7 sysExID1;
		MIDIUInteger7 sysExID2;
		MIDIUInteger7 sysExID3;
		MIDIUInteger7 info1;
		MIDIUInteger7 info2;
	} MIDICIProfileIDManufacturerSpecific;

	/*!
		@struct		MIDICIProfileID
		@brief		A C-style struct containing the profile ID.

		@discussion	There are two general types of Profiles -- standard defined Profiles and
					manufacturer-specific Profiles.
	 */
	typedef union
	{
		MIDICIProfileIDStandard standard;
		MIDICIProfileIDManufacturerSpecific manufacturerSpecific;
	} MIDICIProfileID;

//=============================================================================
#pragma mark MIDI-CI Property Exchange Constants

	/*!
		@typedef	MIDICIPropertyExchangeRequestID
		@brief		The request ID associated with a Property Exchange request.

		@discussion	As the respose context of a Property Exchange message is assumed to be known
					by the initiator, the requestID of each request is included with the response such
					that it can be correlated with the initial request.
	 */
	typedef UInt8 MIDICIPropertyExchangeRequestID CF_TYPED_EXTENSIBLE_ENUM;

	/*!
		@constant    kMIDICIPropertyExchangeBadRequestID
		@brief        Returned when MIDI-CI Property Messages were not dispatched due to an error.
	 */
	static MIDICIPropertyExchangeRequestID kMIDICIPropertyExchangeBadRequestID = 0xFF;

#ifdef __cplusplus
}
#endif

#endif // CoreMIDI_MIDIUMPCI_h

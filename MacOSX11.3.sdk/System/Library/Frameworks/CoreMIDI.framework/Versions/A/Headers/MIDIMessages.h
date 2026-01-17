/*
 	File:   	CoreMIDI/MIDIMessages.h
 
 	Contains:   Constants, structures, and helper functions for Universal MIDI Packet and MIDI 2.0 messages.
 
 	Copyright:  (c) 2018-2020 by Apple Inc., all rights reserved.
 
 	Bugs?:  	For bug reports, consult the following page on
 				the World Wide Web:
 
 					http://feedbackassistant.apple.com/
 
*/

#ifndef CoreMIDI_MIDIMessage_h
#define CoreMIDI_MIDIMessage_h

#include <CoreFoundation/CFBase.h>

//==================================================================================================
#pragma mark -
#pragma mark MIDI message constants

// MIDI Universal Packet message type nibbles.
typedef CF_ENUM(unsigned int, MIDIMessageType) {
	kMIDIMessageTypeUtility	        =   0x0,	// 1 word
	kMIDIMessageTypeSystem          =   0x1,	// 1 word
	kMIDIMessageTypeChannelVoice1   =   0x2,	// 1 word - MIDI 1.0
	kMIDIMessageTypeSysEx           =   0x3,	// 2 words (Data, but primarily SysEx)
	kMIDIMessageTypeChannelVoice2   =   0x4,	// 2 words - MIDI 2.0
	kMIDIMessageTypeData128         =   0x5		// 4 words
	
	// Sizes of undefined message types:
	// 6: 1 word
	// 7: 1 word
	// 8: 2 words
	// 9: 2 words
	// A: 2 words
	// B: 3 words
	// C: 3 words
	// D: 4 words
	// E: 4 words
	// F: 4 words
};

// kMIDIMessageTypeChannelVoice1 / kMIDIMessageTypeChannelVoice2 status nibbles.
typedef CF_ENUM(unsigned int, MIDICVStatus) {
	// MIDI 1.0
	kMIDICVStatusNoteOff			=	0x8,
	kMIDICVStatusNoteOn				=	0x9,
	kMIDICVStatusPolyPressure		=	0xA,
	kMIDICVStatusControlChange		=	0xB,
	kMIDICVStatusProgramChange		=	0xC,
	kMIDICVStatusChannelPressure	=	0xD,
	kMIDICVStatusPitchBend			=	0xE,

	// MIDI 2.0
	kMIDICVStatusRegisteredPNC			= 	0x0, // Per-Note Controller
	kMIDICVStatusAssignablePNC			=	0x1,
	kMIDICVStatusRegisteredControl		=	0x2, // Registered Parameter Number (RPN)
	kMIDICVStatusAssignableControl		=	0x3, // Non-Registered Parameter Number (NRPN)
	kMIDICVStatusRelRegisteredControl	= 	0x4, // Relative
	kMIDICVStatusRelAssignableControl	=	0x5, // Relative
	kMIDICVStatusPerNotePitchBend		=	0x6,
	kMIDICVStatusPerNoteMgmt			=	0xF
};

// kMIDIMessageTypeSystem status bytes.
typedef CF_ENUM(unsigned int, MIDISystemStatus) {
	// MIDI 1.0 only
	kMIDIStatusStartOfExclusive		= 0xF0,
	kMIDIStatusEndOfExclusive		= 0xF7,
	
	// MIDI 1.0 and 2.0
	kMIDIStatusMTC					= 0xF1,
	kMIDIStatusSongPosPointer		= 0xF2,
	kMIDIStatusSongSelect			= 0xF3,
	kMIDIStatusTuneRequest			= 0xF6,
	
	kMIDIStatusTimingClock			= 0xF8,
	kMIDIStatusStart				= 0xFA,
	kMIDIStatusContinue				= 0xFB,
	kMIDIStatusStop					= 0xFC,
	kMIDIStatusActiveSending		= 0xFE,
	kMIDIStatusSystemReset			= 0xFF
};

// kMIDIMessageTypeSysEx / Data (MT=3) message status nibbles.
typedef CF_ENUM(unsigned int, MIDISysExStatus) {
	kMIDISysExStatusComplete        = 0x0,
	kMIDISysExStatusStart           = 0x1,
	kMIDISysExStatusContinue        = 0x2,
	kMIDISysExStatusEnd             = 0x3
};

// MIDI 2.0 Note On/Off Message Attribute Types
enum {
	kMIDINoteAttributeNone					= 0x0,	// no attribute data
	kMIDINoteAttributeManufacturerSpecific	= 0x1,	// Manufacturer-specific = unknown
	kMIDINoteAttributeProfileSpecific		= 0x2,	// MIDI-CI profile-specific data
	kMIDINoteAttributePitch					= 0x3	// Pitch 7.9
};


//==================================================================================================
#pragma mark -
#pragma mark Universal MIDI Packet structs

#pragma pack(push, 4)

typedef UInt32 MIDIMessage_32;

typedef struct MIDIMessage_64 {
	UInt32 word0;
	UInt32 word1;
} MIDIMessage_64;

typedef struct MIDIMessage_96 {
	UInt32 word0;
	UInt32 word1;
	UInt32 word2;
} MIDIMessage_96;

typedef struct MIDIMessage_128 {
	UInt32 word0;
	UInt32 word1;
	UInt32 word2;
	UInt32 word3;
} MIDIMessage_128;

#pragma pack(pop)

//==================================================================================================
#pragma mark -
#pragma mark Univerval MIDI Packet message helper functions

CF_INLINE MIDIMessageType MIDIMessageTypeForUPWord(const UInt32 word) { return (MIDIMessageType)(word >> 28 & 0x7F); }

/*
	MIDI 1.0 Universal MIDI Packet (MIDI-1UP) Channel Voice Message generalized structure
	
	Word0: [aaaa][bbbb][cccc][dddd][0eeeeeee][0fffffff]
	
	a: Universal MIDI Packet Message Type (0x2 for all voice messages)
	b: Channel group number
	c: MIDI status
	d: MIDI channel
	e: MIDI note number
	f: Velocity
	
	The following set of functions will correctly construct voice channel messages as MIDI-1UP.
*/

CF_INLINE MIDIMessage_32 MIDI1UPChannelVoiceMessage(UInt8 group, UInt8 status, UInt8 channel, UInt8 data1, UInt8 data2) {
    return (MIDIMessage_32)( (UInt32)((kMIDIMessageTypeChannelVoice1 << 4) | (group & 0xF)) << 24 | (UInt32)(status << 4 | (channel & 0xF)) << 16 | (UInt32)(data1 & 0x7F) << 8 | (UInt32)(data2 & 0x7F));
}

CF_INLINE MIDIMessage_32 MIDI1UPNoteOff(UInt8 group, UInt8 channel, UInt8 noteNumber, UInt8 velocity) {
    return MIDI1UPChannelVoiceMessage(group, kMIDICVStatusNoteOff, channel, noteNumber, velocity);
}

CF_INLINE MIDIMessage_32 MIDI1UPNoteOn(UInt8 group, UInt8 channel, UInt8 noteNumber, UInt8 velocity) {
    return MIDI1UPChannelVoiceMessage(group, kMIDICVStatusNoteOn, channel, noteNumber, velocity);
}

CF_INLINE MIDIMessage_32 MIDI1UPControlChange(UInt8 group, UInt8 channel, UInt8 index, UInt8 data) {
    return MIDI1UPChannelVoiceMessage(group, kMIDICVStatusControlChange, channel, index, data);
}

CF_INLINE MIDIMessage_32 MIDI1UPPitchBend(UInt8 group, UInt8 channel, UInt8 lsb, UInt8 msb) {
    return MIDI1UPChannelVoiceMessage(group, kMIDICVStatusPitchBend, channel, lsb, msb);
}

CF_INLINE MIDIMessage_32 MIDI1UPSystemCommon(UInt8 group, UInt8 status, UInt8 byte1, UInt8 byte2) {
    return (MIDIMessage_32)((UInt32)((kMIDIMessageTypeSystem << 4) | (group & 0xF)) << 24 | (UInt32)(status) << 16 | (UInt32)(byte1 & 0x7F) << 8 | (UInt32)(byte2 & 0x7F));
}

//==================================================================================================
#pragma mark -
#pragma mark MIDI 2.0 Message helper functions

/*
	MIDI 2.0 Channel Voice Message generalized structure
	
	Word0: [aaaa][bbbb][cccc][dddd][eeeeeeeeeeeeeeee]
	Word1: [nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn]
	
	a: Message Type (type 1 for all voice messages)
	b: Channel group number
	c: MIDI status
	d: MIDI channel
	e: "Index" -- the contents of this field vary based on message type
	n: Data payload
	
	The following set of functions will correctly construct voice channel messages as two 32-bit words.
*/

CF_INLINE MIDIMessage_64 MIDI2ChannelVoiceMessage(UInt8 group, UInt8 status, UInt8 channel, UInt16 index, UInt32 value) {
	return (MIDIMessage_64){ (UInt32)((group & 0xF) | 0x40) << 24 | (UInt32)((channel & 0xF) | (UInt8)(status) << 4) << 16 | (UInt32)(index), value};
}

CF_INLINE MIDIMessage_64 MIDI2NoteOn(UInt8 group, UInt8 channel, UInt8 noteNumber, UInt8 attributeType, UInt16 attributeData, UInt16 velocity) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusNoteOn, channel, (UInt16)(noteNumber) << 8 | (UInt16)(attributeType), (UInt32)(velocity) << 16 | (UInt32)(attributeData));
}

CF_INLINE MIDIMessage_64 MIDI2NoteOff(UInt8 group, UInt8 channel, UInt8 noteNumber, UInt8 attributeType, UInt16 attributeData, UInt16 velocity) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusNoteOff, channel, (UInt16)(noteNumber) << 8 | (UInt16)(attributeType), (UInt32)(velocity) << 16 | (UInt32)(attributeData));
}

CF_INLINE MIDIMessage_64 MIDI2PolyPressure(UInt8 group, UInt8 channel, UInt8 noteNumber, UInt32 value) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusPolyPressure, channel, (UInt16)(noteNumber) << 8, value);
}

CF_INLINE MIDIMessage_64 MIDI2RegisteredPNC(UInt8 group, UInt8 channel, UInt8 noteNumber, UInt8 index, UInt32 value) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusRegisteredPNC, channel, (UInt16)(noteNumber) << 8 | (UInt16)(index), value);
}

CF_INLINE MIDIMessage_64 MIDI2AssignablePNC(UInt8 group, UInt8 channel, UInt8 noteNumber, UInt8 index, UInt32 value) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusAssignablePNC, channel, (UInt16)(noteNumber) << 8 | (UInt16)(index), value);
}

CF_INLINE MIDIMessage_64 MIDI2PerNoteManagment(UInt8 group, UInt8 channel, UInt8 noteNumber, bool detachPNCs, bool resetPNCsToDefault) {
	UInt16 option_flags = (UInt16)(detachPNCs ? 1 : 0) << 1 | (UInt16)(resetPNCsToDefault ? 1: 0);
    return MIDI2ChannelVoiceMessage(group, kMIDICVStatusPerNoteMgmt, channel, (UInt16)(noteNumber) << 8 | option_flags, 0);
}

CF_INLINE MIDIMessage_64 MIDI2ControlChange(UInt8 group, UInt8 channel, UInt8 index, UInt32 value) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusControlChange, channel, (UInt16)(index) << 8, value);
}

CF_INLINE MIDIMessage_64 MIDI2RegisteredControl(UInt8 group, UInt8 channel, UInt8 bank, UInt8 index, UInt32 value) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusRegisteredControl, channel, (UInt16)(bank) << 8 | (UInt16)(index), value);
}

CF_INLINE MIDIMessage_64 MIDI2AssignableControl(UInt8 group, UInt8 channel, UInt8 bank, UInt8 index, UInt32 value) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusAssignableControl, channel, (UInt16)(bank) << 8 | (UInt16)(index), value);
}

CF_INLINE MIDIMessage_64 MIDI2RelRegisteredControl(UInt8 group, UInt8 channel, UInt8 bank, UInt8 index, UInt32 value) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusRelRegisteredControl, channel, (UInt16)(bank) << 8 | (UInt16)(index), value);
}

CF_INLINE MIDIMessage_64 MIDI2RelAssignableControl(UInt8 group, UInt8 channel, UInt8 bank, UInt8 index, UInt32 value) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusRelAssignableControl, channel, (UInt16)(bank) << 8 | (UInt16)(index), value);
}

CF_INLINE MIDIMessage_64 MIDI2ProgramChange(UInt8 group, UInt8 channel, bool bankIsValid, UInt8 program, UInt8 bank_msb, UInt8 bank_lsb) {
	UInt16 option_flags = (UInt16)(bankIsValid ? 1 : 0);
	UInt32 value = ((UInt32)(program) << 24) | ((UInt32)(bank_msb) << 8) | ((UInt32)(bank_lsb));
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusProgramChange, channel, option_flags, value);
}

CF_INLINE MIDIMessage_64 MIDI2ChannelPressure(UInt8 group, UInt8 channel, UInt32 value) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusChannelPressure, channel, 0, value);
}

CF_INLINE MIDIMessage_64 MIDI2PitchBend(UInt8 group, UInt8 channel, UInt32 value) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusPitchBend, channel, 0, value);
}

CF_INLINE MIDIMessage_64 MIDI2PerNotePitchBend(UInt8 group, UInt8 channel, UInt8 noteNumber, UInt32 value) {
	return MIDI2ChannelVoiceMessage(group, kMIDICVStatusPerNotePitchBend, channel, (UInt16)(noteNumber) << 8, value);
}

#endif // CoreMIDI_MIDIMessage_h

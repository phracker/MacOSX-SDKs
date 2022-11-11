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
#include <CoreMIDI/MIDIServices.h>

#ifdef __cplusplus
extern "C" {
#endif


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
	kMIDIMessageTypeData128         =   0x5,	// 4 words
	kMIDIMessageTypeUnknownF		=	0xF
	
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
	kMIDIStatusActiveSensing		= kMIDIStatusActiveSending,
	kMIDIStatusSystemReset			= 0xFF
};

// kMIDIMessageTypeSysEx / kMIDIMessageTypeData128 status nibbles.
typedef CF_ENUM(unsigned int, MIDISysExStatus) {
	kMIDISysExStatusComplete        = 0x0,
	kMIDISysExStatusStart           = 0x1,
	kMIDISysExStatusContinue        = 0x2,
	kMIDISysExStatusEnd             = 0x3,

	// MIDI 2.0
	kMIDISysExStatusMixedDataSetHeader	= 0x8,
	kMIDISysExStatusMixedDataSetPayload	= 0x9
};

// kMIDIMessageTypeUtility status nibbles.
typedef CF_ENUM(unsigned int, MIDIUtilityStatus) {
	kMIDIUtilityStatusNOOP						= 0x0,
	kMIDIUtilityStatusJitterReductionClock		= 0x1,
	kMIDIUtilityStatusJitterReductionTimestamp	= 0x2
};

// MIDI 2.0 Note On/Off Message Attribute Types
typedef CF_ENUM(UInt8, MIDINoteAttribute) {
	kMIDINoteAttributeNone					= 0x0,	// no attribute data
	kMIDINoteAttributeManufacturerSpecific	= 0x1,	// Manufacturer-specific = unknown
	kMIDINoteAttributeProfileSpecific		= 0x2,	// MIDI-CI profile-specific data
	kMIDINoteAttributePitch					= 0x3	// Pitch 7.9
};

// MIDI 2.0 Program Change Options
typedef CF_OPTIONS(UInt8, MIDIProgramChangeOptions) {
    kMIDIProgramChangeBankValid = 0x1
};

// MIDI 2.0 Per Note Management Options
typedef CF_OPTIONS(UInt8, MIDIPerNoteManagementOptions) {
    kMIDIPerNoteManagementReset = 0x1,
    kMIDIPerNoteManagementDetach = 0x2
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

CF_INLINE MIDIMessage_64 MIDI1UPSysEx(UInt8 group, UInt8 status, UInt8 bytesUsed, UInt8 byte1, UInt8 byte2, UInt8 byte3, UInt8 byte4, UInt8 byte5, UInt8 byte6) {
    MIDIMessage_64 sysExOut = {};
    sysExOut.word0 = (UInt32)((kMIDIMessageTypeSysEx << 4) | (group & 0xF)) << 24 | (UInt32)((status << 4) | (bytesUsed)) << 16 | (UInt32)(byte1 & 0x7F) << 8 | (UInt32)(byte2 & 0x7F);
    sysExOut.word1 = (UInt32)(byte3 & 0x7F) << 24 | (UInt32)(byte4 & 0x7F) << 16 | (UInt32)(byte5 & 0x7F) << 8 | (UInt32)(byte6 & 0x7F);
    return sysExOut;
}

CF_INLINE MIDIMessage_64 MIDI1UPSysExArray(UInt8 group, UInt8 status, const Byte *begin, const Byte *end)
{
    Byte arrayCopy[6] = {};
    int numberOfBytes = end <= begin ? 0 : end - begin;
    for (int i = 0; i < numberOfBytes; ++i)
        arrayCopy[i] = *(begin + i);
    return MIDI1UPSysEx(group, status, numberOfBytes, arrayCopy[0], arrayCopy[1], arrayCopy[2], arrayCopy[3], arrayCopy[4], arrayCopy[5]);
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

//==================================================================================================
#pragma mark -
#pragma mark UMP message helper functions for reading

/*!
    @struct    MIDIUniversalMessage
    @abstract  A representation of all possible messages stored in a Universal MIDI packet.
*/
typedef struct MIDIUniversalMessage {
	MIDIMessageType  type;    //!< determines which variant in the union is active
	UInt8            group;   //!< 4 bit MIDI group
	UInt8            reserved[3];

	union {
		struct {
			MIDIUtilityStatus status;  //!< determines which variant is active
			union {
				UInt16 jitterReductionClock;      //!< active when status is kMIDIUtilityStatusJitterReductionClock
				UInt16 jitterReductionTimestamp;  //!< active when status is kMIDIUtilityStatusJitterReductionTimestamp
			};
		} utility;   //!< active when type is kMIDIMessageTypeUtility

		struct {
			MIDISystemStatus status;  //!< determines which variant is active
			union {
				UInt8  timeCode;             //!< active when status is kMIDIStatusMTC
				UInt16 songPositionPointer;  //!< active when status is kMIDIStatusSongPosPointer
				UInt8  songSelect;           //!< active when status is kMIDIStatusSongSelect
			};
		} system;   //!< active when type is kMIDIMessageTypeSystem

		struct {
			MIDICVStatus  status;   //!< determines which variant is active
			UInt8         channel;  //!< MIDI channel 0-15
			UInt8         reserved[3];
			union {
				struct {
					UInt8 number;    //!< 7 bit note number
					UInt8 velocity;  //!< 7 bit note velocity
				} note;   //!< active when status is kMIDICVStatusNoteOff or kMIDICVStatusNoteOn

				struct
				{
					UInt8 noteNumber;  //!< 7 bit note number
					UInt8 pressure;    //!< 7 bit poly pressure data
				} polyPressure;   //!< active when status is kMIDICVStatusPolyPressure

				struct {
					UInt8 index;  //!< 7 bit index of control parameter
					UInt8 data;   //!< 7 bit value for control parameter
				} controlChange;  //!< active when status is kMIDICVStatusControlChange

				UInt8  program;          //!< 7 bit program nr, active when status is kMIDICVStatusProgramChange
				UInt8  channelPressure;  //!< 7 bit channel pressure, active when status is kMIDICVStatusChannelPressure
				UInt16 pitchBend;        //!< 7 bit pitch bend active when status is kMIDICVStatusPitchBend
			};
		} channelVoice1;   //!< active when type is kMIDIMessageTypeChannelVoice1

		struct {
			MIDISysExStatus status;
			UInt8           channel;  //!< MIDI channel 0-15
			UInt8           data[6];  //!< SysEx data, 7 bit values
			UInt8           reserved;
		} sysEx;   //!< active when type is kMIDIMessageTypeSysEx

		struct {
			MIDICVStatus  status;   //!< determines which variant is active
			UInt8         channel;  //!< MIDI channel
			UInt8         reserved[3];
			union {
				struct {
					UInt8                 number;         //!< 7 bit note number
					MIDINoteAttribute     attributeType;  //!< attribute type
					UInt16                velocity;       //!< note velocity
					UInt16                attribute;      //!< attribute data
				} note;    //!< active when status is kMIDICVStatusNoteOff or kMIDICVStatusNoteOn

				struct
				{
					UInt8  noteNumber;  //!< 7 bit note number
					UInt8  reserved;
					UInt32 pressure;    //!< pressure value
				} polyPressure;         //!< active when status is kMIDICVStatusPolyPressure

				struct {
					UInt8  index;     //!< 7 bit controller number
					UInt8  reserved;
					UInt32 data;      //!< controller value
				} controlChange;      //!< active when status is kMIDICVStatusControlChange

				struct {
					MIDIProgramChangeOptions options;
					UInt8   program;     //!< 7 bit program number
					UInt8   reserved[2];
					UInt16  bank;        //!< 14 bit bank
				} programChange;         //!< active when status is kMIDICVStatusProgramChange

				struct {
					UInt32 data;         //!< channel pressure data
					UInt8  reserved[2];
				} channelPressure;       //!< active when status is kMIDICVStatusChannelPressure

				struct {
					UInt32 data;         //!< pitch bend data
					UInt8  reserved[2];
				} pitchBend;             //!< active when status is kMIDICVStatusPitchBend

				struct {
					UInt8  noteNumber;   //!< 7 bit note number
					UInt8  index;        //!< 7 bit controller number
					UInt32 data;         //!< controller data
				} perNoteController;     //!< active when status is kMIDICVStatusRegisteredPNC or kMIDICVStatusAssignablePNC

				struct {
					UInt8  bank;    //!< 7 bit bank
					UInt8  index;   //!< 7 bit controller number
					UInt32 data;    //!< controller data
				} controller;       //!< active when status is any of kMIDICVStatusRegisteredControl, kMIDICVStatusAssignableControl, kMIDICVStatusRelRegisteredControl, or kMIDICVStatusRelAssignableControl

				struct {
					UInt8  noteNumber;   //!< 7 bit note number
					UInt8  reserved;
					UInt32 bend;         //!< per note pitch bend value
				} perNotePitchBend;      //!< active when status is kMIDICVStatusPerNotePitchBend

				struct {
					UInt8 note;         //!< 7 bit note number
					MIDIPerNoteManagementOptions options;
					UInt8 reserved[4];
				} perNoteManagement;    //!< active when status is kMIDICVStatusPerNoteMgmt
			};
		} channelVoice2;  //!< active when type is kMIDIMessageTypeChannelVoice2

		struct {
			MIDISysExStatus status;    //!< determines which variant is active
			union {
				struct {
					UInt8 byteCount;   //!< byte count of data including stream ID (1-14 bytes)
					UInt8 streamID;
					UInt8 data[13];
					UInt8 reserved;
				} sysex8;   //!< active when status any of kMIDISysExStatusComplete, kMIDISysExStatusStart, kMIDISysExStatusContinue, or kMIDISysExStatusEnd

				struct {
					UInt8 mdsID;      //!< mixed data set ID
					UInt8 data[14];
					UInt8 reserved;
				} mixedDataSet;   //!< active when status is kMIDISysExStatusMixedDataSetHeader or kMIDISysExStatusMixedDataSetPayload
			};
		} data128;   //!< active when type is kMIDIMessageTypeData128

		struct {
			UInt32 words[4];  //!< up to four 32 bit words
		} unknown;            //!< active when type is kMIDIMessageTypeUnknownF
	};
} MIDIUniversalMessage;


/*!
	@typedef	MIDIEventVisitor

	@abstract	A callback function which receives a single MIDIUniversalMessage.

	@discussion
		This callback function is called by MIDIEventListForEachEvent on every UMP
		that has been parsed from a MIDIEventList. From the provided `MIDIUniversalMessage`
		the MIDI information can be accessed, e.g.:
		```
		void myMIDIMessageVisitor(void* context, MIDITimeStamp timeStamp, MIDIUniversalMessage message) {
			switch (message.type) {
			case kMIDIMessageTypeSystem:
				...
			case kMIDIMessageTypeChannelVoice2:
				switch (message.channelVoice2.status) {
				case kMIDICVStatusNoteOff:
					// access message.channelVoice2.note.number, etc.
					...
				case kMIDICVStatusNoteOn:
					...
				case kMIDICVStatusPerNotePitchBend:
					...
				}
			}
		}
		```

	@param		context
		A context provided by the client via call to MIDIEventListForEachEvent.

	@param		timeStamp
		The timestamp of the current UMP.

	@param		message
		A filled MIDIUniversalMessage struct that has been parsed from a single UMP.
*/
typedef void (*MIDIEventVisitor)(void* context, MIDITimeStamp timeStamp, MIDIUniversalMessage message);

/*!
	@typedef		MIDIEventListForEachEvent
	@abstract		Parses UMPs from a MIDIEventList.
	@discussion
		MIDIEventListForEachEvent iterates over all UMPs in the provided MIDIEventList.
		It parses each UMP and fills a MIDIUniversalMessage struct. It calls the provided
		visitor on each of these UMPs. In case of an unknown UMP the raw UMP words will be provided.

	@param			evtlist
						The MIDIEventList which is to be parsed.

	@param			visitor
						The visitor that is called on each UMP in evtlist.

	@param			visitorContext
						A context for the visitor that is passed to it when being called.

*/
extern void MIDIEventListForEachEvent(
	const MIDIEventList* evtlist, MIDIEventVisitor visitor, void* visitorContext)
									API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));


#ifdef __cplusplus
}
#endif

#endif // CoreMIDI_MIDIMessage_h

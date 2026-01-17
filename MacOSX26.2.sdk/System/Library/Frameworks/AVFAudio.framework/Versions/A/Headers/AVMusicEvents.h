/*==================================================================================================
 File:       AVMusicEvents.h
 
 Contains:   API for events associated with an AVMusicTrack and AVAudioSequencer
 
 Copyright:  (c) 2021 by Apple, Inc., all rights reserved.
 
 Bugs?:      For bug reports, consult the following page on
 the World Wide Web:
 
 http://developer.apple.com/bugreporter/
 
 ==================================================================================================*/

#import <Foundation/Foundation.h>
#import <AVFAudio/AVAudioTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!	@class AVMusicEvent
	@abstract
		The base class for all events associated with an AVMusicTrack.
	@discussion
		This class is provided to allow enumeration of the heterogenous events contained within an AVMusicTrack.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVMusicEvent : NSObject
@end

/*!	@class AVMIDINoteEvent
	@abstract
		The event class representing MIDI note-on/off messages.
	@param channel
		The MIDI channel for the note.  Range: 0-15.
	@param key
		The MIDI key number for the note.  Range: 0-127.
	@param velocity
		The MIDI velocity for the note.  Range: 0-127 (see discussion).
	@param duration
		The duration of this note event in AVMusicTimeStamp beats.  Range: Any non-negative number.
	@discussion
		The AVAudioSequencer will automatically send a MIDI note-off after the note duration has passed.
		To send an explicit note-off event, create an AVMIDINoteEvent with its velocity set to zero.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVMIDINoteEvent : AVMusicEvent

/*!	@method initWithChannel:key:velocity:duration
	@abstract
		Initialize the event with a MIDI channel, key number, velocity and duration.
	@param channel
		The MIDI channel.  Range: 0-15.
	@param key
		The MIDI key number.  Range: 0-127.
	@param velocity
		The MIDI velocity.  Range: 0-127 with zero indicating a note-off event.
	@param duration
		The duration in beats for this note.  Range: Any non-negative number.
 */
- (instancetype)initWithChannel:(UInt32)channel key:(UInt32)keyNum velocity:(UInt32)velocity duration:(AVMusicTimeStamp)duration;

/*!	@property channel
		The MIDI channel for the event.  Range: 0-15.
 */
@property (readwrite) UInt32 channel;

/*!	@property key
		The MIDI key number for the event.  Range: 0-127.
 */
@property (readwrite) UInt32 key;

/*!	@property velocity
		The MIDI velocity for the event.  Range: 0-127.
 */
@property (readwrite) UInt32 velocity;

/*!	@property duration
		The duration of the event in AVMusicTimeStamp beats.  Range: Any non-negative number.
 */
@property (readwrite) AVMusicTimeStamp duration;

@end

/*!	@class AVMIDIChannelEvent
	@abstract
		The event base class for all MIDI messages which operate on a single MIDI channel.
*/
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVMIDIChannelEvent : AVMusicEvent

/*!	@property channel
		The MIDI channel for the event.  Range: 0-15.
 */
@property (readwrite)UInt32 channel;

@end

/*! @enum AVMIDIControlChangeMessageType
	@abstract
		Types of MIDI control change events.  See the General MIDI Specification for details.
 */
typedef NS_ENUM(NSInteger, AVMIDIControlChangeMessageType)
{
	AVMIDIControlChangeMessageTypeBankSelect			= 0,
	AVMIDIControlChangeMessageTypeModWheel			= 1,
	AVMIDIControlChangeMessageTypeBreath				= 2,
	AVMIDIControlChangeMessageTypeFoot				= 4,
	AVMIDIControlChangeMessageTypePortamentoTime		= 5,
	AVMIDIControlChangeMessageTypeDataEntry			= 6,
	AVMIDIControlChangeMessageTypeVolume				= 7,
	AVMIDIControlChangeMessageTypeBalance				= 8,
	AVMIDIControlChangeMessageTypePan					= 10,
	AVMIDIControlChangeMessageTypeExpression			= 11,
	
	// these events have value (0-63) == off, (64-127) == on
	AVMIDIControlChangeMessageTypeSustain				= 64,
	AVMIDIControlChangeMessageTypePortamento			= 65,
	AVMIDIControlChangeMessageTypeSostenuto			= 66,
	AVMIDIControlChangeMessageTypeSoft				= 67,
	AVMIDIControlChangeMessageTypeLegatoPedal			= 68,
	AVMIDIControlChangeMessageTypeHold2Pedal			= 69,

	AVMIDIControlChangeMessageTypeFilterResonance		= 71,
	AVMIDIControlChangeMessageTypeReleaseTime			= 72,
	AVMIDIControlChangeMessageTypeAttackTime			= 73,
	AVMIDIControlChangeMessageTypeBrightness			= 74,
	AVMIDIControlChangeMessageTypeDecayTime			= 75,
	AVMIDIControlChangeMessageTypeVibratoRate			= 76,
	AVMIDIControlChangeMessageTypeVibratoDepth		= 77,
	AVMIDIControlChangeMessageTypeVibratoDelay		= 78,
	
	AVMIDIControlChangeMessageTypeReverbLevel			= 91,
	AVMIDIControlChangeMessageTypeChorusLevel			= 93,
	AVMIDIControlChangeMessageTypeRPN_LSB				= 100,
	AVMIDIControlChangeMessageTypeRPN_MSB				= 101,
	AVMIDIControlChangeMessageTypeAllSoundOff			= 120,
	AVMIDIControlChangeMessageTypeResetAllControllers	= 121,
	AVMIDIControlChangeMessageTypeAllNotesOff			= 123,
	AVMIDIControlChangeMessageTypeOmniModeOff			= 124,
	AVMIDIControlChangeMessageTypeOmniModeOn			= 125,
	AVMIDIControlChangeMessageTypeMonoModeOn			= 126,
	AVMIDIControlChangeMessageTypeMonoModeOff			= 127
} API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

/*!	@class AVMIDIControlChangeEvent
	@abstract
		The event class representing MIDI control change messages.
*/
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVMIDIControlChangeEvent : AVMIDIChannelEvent

/*!	@method initWithChannel:messageType:value
	@abstract
		Initialize the event with a channel, a control change type, and a control value.
	@param channel
		The MIDI channel for the control change.  Range: 0-15.
	@param messageType
		The AVMIDIControlChangeMessageType indicating which MIDI control change message to send.
	@param value
		The value for this control change.  Range: Depends on the type (see the General MIDI specification).
 */
- (instancetype)initWithChannel:(UInt32)channel messageType:(AVMIDIControlChangeMessageType)messageType value:(UInt32)value;

/*!	@property messageType
		The type of control change message, specified as an AVMIDIControlChangeMessageType.
 */
@property (readonly)AVMIDIControlChangeMessageType messageType;

/*!	@property value
		The value of the control change event.  The range of this value depends on the type (see the General MIDI specification).
 */
@property (readonly)UInt32 value;

@end

/*!	@class AVMIDIPolyPressureEvent
	@abstract
		The event class representing MIDI "poly" or "key" pressure messages.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVMIDIPolyPressureEvent : AVMIDIChannelEvent

/*!	@method initWithChannel:key:pressure
	@abstract
		Initialize the event with a channel, a MIDI key number, and a key pressure value.
	@param channel
		The MIDI channel for the message.  Range: 0-15.
	@param key
		The MIDI key number to which the pressure should be applied.
	@param pressure
		The poly pressure value.
*/
- (instancetype)initWithChannel:(UInt32)channel key:(UInt32)key pressure:(UInt32)pressure;

/*!	@property key
		The MIDI key number.
 */
@property (readwrite)UInt32 key;

/*!	@property pressure
		The poly pressure value for the requested key.
 */
@property (readwrite)UInt32 pressure;

@end

/*!	@class AVMIDIProgramChangeEvent
	@abstract
		The event class representing MIDI program or patch change messages.
	@discussion
		The effect of these messages will depend on the containing AVMusicTrack's destinationAudioUnit.
*/
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVMIDIProgramChangeEvent : AVMIDIChannelEvent

/*!	@method initWithChannel:programNumber:
	@abstract
		Initialize the event with a channel and a program number.
	@param channel
		The MIDI channel for the message.  Range: 0-15.
	@param programNumber
		The program number to be sent.  Range: 0-127.
	@discussion
		Per the General MIDI specification, the actual instrument that is chosen will depend on optional
		AVMIDIControlChangeMessageTypeBankSelect events sent prior to this program change.
*/
- (instancetype)initWithChannel:(UInt32)channel programNumber:(UInt32)programNumber;

/*!	@property programNumber
		The MIDI program number.  Range: 0-127.
 */
@property (readwrite)UInt32 programNumber;

@end

/*!	@class AVMIDIChannelPressureEvent
	@abstract
		The event class representing MIDI channel pressure messages.
	@discussion
		The effect of these messages will depend on the containing AVMusicTrack's destinationAudioUnit
		and the capabilities of the destination's currently-loaded instrument.
*/
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVMIDIChannelPressureEvent : AVMIDIChannelEvent

/*!	@method initWithChannel:pressure:
	@abstract
		Initialize the event with a channel and a pressure value.
	@param channel
		The MIDI channel for the message.  Range: 0-15.
	@param pressure
		The MIDI channel pressure.  Range: 0-127.
 */
- (instancetype)initWithChannel:(UInt32)channel pressure:(UInt32)pressure;

/*!	@property pressure
		The MIDI channel pressure.
 */
@property (readwrite)UInt32 pressure;

@end

/*!	@class AVMIDIPitchBendEvent
	@abstract
		The event class representing MIDI pitch bend messages.
	@discussion
		The effect of these messages will depend on the AVMusicTrack's destinationAudioUnit
		and the capabilities of the destination's currently-loaded instrument.
*/
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVMIDIPitchBendEvent : AVMIDIChannelEvent

/*!	@method initWithChannel:value:
	@abstract
		Initialize the event with a channel and a pitch bend value.
	@param channel
		The MIDI channel for the message.  Range: 0-15.
	@param value
		The pitch bend value.  Range: 0-16383 (midpoint 8192).
 */
- (instancetype)initWithChannel:(UInt32)channel value:(UInt32)value;

/*!	@property value
		The value of the pitch bend event.  Range: 0-16383 (midpoint 8192).
 */
@property (readwrite)UInt32 value;

@end

/*!	@class AVMIDISysexEvent
	@abstract
		The event class representing MIDI system exclusive messages.
	@discussion
		The size and contents of an AVMIDISysexEvent cannot be modified once created.
*/
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVMIDISysexEvent : AVMusicEvent

/*!	@method initWithData:
	@abstract
		Initialize the event with an NSData.
	@param data
		An NSData object containing the raw contents of the system exclusive event.
 */
- (instancetype)initWithData:(NSData *)data;

/*!	@property sizeInBytes
		The size of the raw data associated with this system exclusive event.
 */
@property (readonly)UInt32 sizeInBytes;

@end

/*!	@enum AVMIDIMetaEventType
	@abstract
		Constants which indicate which type of MIDI Meta-Event to create.
 */
typedef NS_ENUM(NSInteger, AVMIDIMetaEventType)
{
	AVMIDIMetaEventTypeSequenceNumber		= 0x00,
	AVMIDIMetaEventTypeText					= 0x01,
	AVMIDIMetaEventTypeCopyright			= 0x02,
	AVMIDIMetaEventTypeTrackName			= 0x03,
	AVMIDIMetaEventTypeInstrument			= 0x04,
	AVMIDIMetaEventTypeLyric				= 0x05,
	AVMIDIMetaEventTypeMarker				= 0x06,
	AVMIDIMetaEventTypeCuePoint				= 0x07,
	AVMIDIMetaEventTypeMidiChannel			= 0x20,
	AVMIDIMetaEventTypeMidiPort				= 0x21,
	AVMIDIMetaEventTypeEndOfTrack			= 0x2f,
	AVMIDIMetaEventTypeTempo				= 0x51,
	AVMIDIMetaEventTypeSmpteOffset			= 0x54,
	AVMIDIMetaEventTypeTimeSignature		= 0x58,
	AVMIDIMetaEventTypeKeySignature			= 0x59,
	AVMIDIMetaEventTypeProprietaryEvent		= 0x7f
} API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

/*!	@class AVMIDIMetaEvent
	@abstract
		The event class representing MIDI Meta-Event messages.
	@discussion
		The size and contents of an AVMIDIMetaEvent cannot be modified once created.
 
		Events with AVMIDIMetaEventType AVMIDIMetaEventTypeTempo, AVMIDIMetaEventTypeSmpteOffset,
		or AVMIDIMetaEventTypeTimeSignature can only be added to a sequence's tempo track.
 
		The class does not verify that the content matches the MIDI specification.
*/
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVMIDIMetaEvent : AVMusicEvent

/*!	@method initWithType:data
	@abstract
		Initialize the event with a MIDI Meta-Event type and an NSData.
	@param type
		A AVMIDIMetaEventType indicating which type of Meta-Event.
	@param data
		An NSData object containing the raw contents of the Meta-Event.
 */
- (instancetype)initWithType:(AVMIDIMetaEventType)type data:(NSData *)data;

/*!	@property type
		The type of Meta-Event, specified as an AVMIDIMetaEventType.
 */
@property (readonly) AVMIDIMetaEventType type;

@end

/*!	@class AVMusicUserEvent
	@abstract
		The event class representing custom user messages.
	@discussion
		When a scheduled AVMusicUserEvent is reached during playback of a AVMusicTrack, the track's
		user callback block will be called if it has been set.  The event's NSData will be provided as
		an argument to that block.
		The size and contents of an AVMusicUserEvent cannot be modified once created.
*/
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVMusicUserEvent : AVMusicEvent

/*!	@method initWithData:
	@abstract
		Initialize the event with an NSData.
	@param data
		An NSData object containing the contents to be returned via the AVMusicTrack's user callback.
 */
- (instancetype)initWithData:(NSData *)data;

/*!	@property sizeInBytes
		The size of the data associated with this user event.
 */
@property (readonly)UInt32 sizeInBytes;

@end

/*! @constant AVExtendedNoteOnEventDefaultInstrument
	@abstract
		A constant representing the default instrument ID to use for an AVExtendedNoteOnEvent.  This indicates to the
		system to use the instrument currently loaded on the channel referenced by the groupID.  This is the only
		supported value at this time.
 */

extern UInt32 const AVExtendedNoteOnEventDefaultInstrument API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);

/*!	@class AVExtendedNoteOnEvent
	@abstract
		The event class representing a custom extension of a MIDI note-on.
	@discussion
		Using an AVExtendedNoteOnEvent allows an application to trigger a specialized note-on event on one of several
		Apple audio units which support it.  The floating point note and velocity numbers allow optional fractional control
		of the note's run-time properties which are modulated by those inputs.  In addition, it supports the possibility
		of an audio unit with more than the standard 16 MIDI channels.
*/
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVExtendedNoteOnEvent : AVMusicEvent

/*!	@method initWithMIDINote:velocity:groupID:duration
	@abstract
		Initialize the event with a midi note, velocity, instrument and group ID, and a duration.
	@param midiNote
		The MIDI velocity represented as a floating point.  Range: Destination-dependent, usually 0.0 - 127.0.
	@param velocity
		The MIDI velocity represented as a floating point.  Range: Destination-dependent, usually 0.0 - 127.0.
	@param groupID
		An index indicating the AudioUnitElement within the Group Scope which should handle this event (see AudioUnitElement).
		This normally maps to a channel within the audio unit.
		Range: normally between 0 and 15, but may be higher if the AVMusicTrack's destinationAudioUnit supports more channels.
	@param duration
		The duration of this event in AVMusicTimeStamp beats.  Range:  Any nonnegative number.
 */
- (instancetype)initWithMIDINote:(float)midiNote
						velocity:(float)velocity
						 groupID:(UInt32)groupID
						duration:(AVMusicTimeStamp)duration;

/*!	@method initWithMIDINote:velocity:instrumentID:groupID:duration
	@abstract
		Initialize the event with a midi note, velocity, instrument and group ID, and a duration.
	@discussion
		This initializer is identical to initWithMIDINote:velocity:groupID:duration with the addition of
		an instrumentID parameter which will allow for the possibility of an externally-created custom instrument.
		If this initializer is used, instrumentID should be set to AVExtendedNoteOnEventDefaultInstrument for now.
 */

- (instancetype)initWithMIDINote:(float)midiNote
						velocity:(float)velocity
					instrumentID:(UInt32)instrumentID
						 groupID:(UInt32)groupID
						duration:(AVMusicTimeStamp)duration;

/*!	@property midiNote
		The MIDI note number represented as a floating point.  If the instrument within the AVMusicTrack's
		destinationAudioUnit supports fractional values, this may be used to generate arbitrary
		macro- and micro-tunings.  Range: Destination-dependent, usually 0.0 - 127.0.
 */
@property (readwrite)float midiNote;

/*!	@property velocity
		The MIDI velocity represented as a floating point.  If the instrument within the AVMusicTrack's
		destinationAudioUnit supports fractional values, this may be used to generate very precise changes
		in gain, etc.  Range: Destination-dependent, usually 0.0 - 127.0.
 */
@property (readwrite)float velocity;

/*!	@property instrumentID
		This should be set to AVExtendedNoteOnEventDefaultInstrument.
 */
@property (readwrite)UInt32 instrumentID;

/*!	@property groupID
		This represents the audio unit channel (i.e., Group Scope) which should handle this event.
		Range: normally between 0 and 15, but may be higher if the AVMusicTrack's destinationAudioUnit
		supports more channels.
 */
@property (readwrite)UInt32 groupID;

/*!	@property duration
		The duration of this event in AVMusicTimeStamp beats.  Range:  Any nonnegative number.
 */
@property (readwrite)AVMusicTimeStamp duration;

@end

/*!	@class AVParameterEvent
	@abstract
		The event class representing a parameter set/change event on the AVMusicTrack's destinationAudioUnit.
	@discussion
		AVParameterEvents make it possible to schedule and/or automate parameter changes on the audio unit
		that has been configured as the destination for the AVMusicTrack containing this event.
 
		When the track is played as part of a sequence, the destination audio unit will receive set-parameter
		messages whose values change smoothly along a linear ramp between each event's beat location.
 
		If an AVParameterEvent is added to an empty, non-automation track, the track becomes an automation track.
*/
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVParameterEvent : AVMusicEvent

/*!	@method initWithParameterID:scope:element:value
	@abstract
		Initialize the event with the parameter ID, scope, element, and value for the parameter to be set.
	@param parameterID
		The ID of the parameter (see AudioUnitParameterID).
	@param scope
		The audio unit scope for the parameter (see AudioUnitScope).
	@param element
		The element index within the scope (see AudioUnitElement).
	@param value
		The value of the parameter to be set.  Range:  Dependent on parameter.
*/
- (instancetype) initWithParameterID:(UInt32)parameterID
							   scope:(UInt32)scope
							 element:(UInt32)element
							   value:(float)value;


/*!	@property parameterID
		The ID of the parameter (see AudioUnitParameterID).
 */
@property (readwrite)UInt32 parameterID;

/*!	@property scope
		The audio unit scope for the parameter (see AudioUnitScope).
 */
@property (readwrite)UInt32 scope;

/*!	@property element
		The element index within the scope (see AudioUnitElement).
 */
@property (readwrite)UInt32 element;

/*!	@property value
		The value of the parameter to be set.  Range:  Dependent on parameter.
*/
@property (readwrite)float value;

@end

/*!	@class AVAUPresetEvent
	@abstract
		The event class representing a preset load and change on the AVMusicTrack's destinationAudioUnit.
	@discussion
		AVAUPresetEvents make it possible to schedule and/or automate preset changes on the audio unit
		that has been configured as the destination for the AVMusicTrack containing this event.
*/

API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVAUPresetEvent : AVMusicEvent

/*!	@method initWithScope:element:dictionary
	@abstract
		Initialize the event with the scope, element, and dictionary for the preset.
	@param scope
		The audio unit scope for the parameter (see AudioUnitScope).  This should always be set to Global.
	@param element
		The element index within the scope (see AudioUnitElement).  This should usually be set to 0.
	@param presetDictionary
		An NSDictionary containing the preset.  The audio unit will expect this to be a dictionary
		structured as an appropriate audio unit preset.
	@discussion
		The dictionary passed to this initializer will be copied and is not editable once the event is
		created.
		
*/
- (instancetype) initWithScope:(UInt32)scope
					   element:(UInt32)element
				  dictionary:(NSDictionary *)presetDictionary;

/*!	@property scope
		The audio unit scope for the parameter (see AudioUnitScope).  This should always be set to Global.
 */
@property (readwrite)UInt32 scope;

/*!	@property element
		The element index within the scope (see AudioUnitElement).  This should usually be set to 0.
 */
@property (readwrite)UInt32 element;

/*!	@property presetDictionary
		An NSDictionary containing the preset.
 */
@property (readonly,copy)NSDictionary *presetDictionary;

@end

/*!	@class AVExtendedTempoEvent
	@abstract
		The event class representing a tempo change to a specific beats-per-minute value.
	@discussion
		This event provides a way to specify a tempo change that is less cumbersome than using
		tempo meta-events.
*/
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos)
@interface AVExtendedTempoEvent : AVMusicEvent

/*!	@method initWithTempo:
	@abstract
		Initialize the event tempo.
	@param tempo
		The new tempo in beats-per-minute.  Range:  Any positive value.
		The new tempo will begin at the timestamp for this event.
 */
- (instancetype)initWithTempo:(double)tempo;

/*!	@property tempo
		The new tempo in beats-per-minute.  Range:  Any positive value.
 */
@property (readwrite)double tempo;

@end

NS_ASSUME_NONNULL_END

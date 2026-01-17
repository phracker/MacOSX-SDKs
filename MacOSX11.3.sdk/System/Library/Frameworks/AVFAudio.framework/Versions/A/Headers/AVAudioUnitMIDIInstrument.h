/*
	File:		AVAudioUnitMIDIInstrument.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioUnit.h>
#import <AVFAudio/AVAudioMixing.h>

#if defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101100
	#define AVAudioUnitMIDIInstrument_MixingConformance <AVAudioMixing>
#elif defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 90000
	#define AVAudioUnitMIDIInstrument_MixingConformance <AVAudioMixing>
#else
	#define AVAudioUnitMIDIInstrument_MixingConformance
#endif


NS_ASSUME_NONNULL_BEGIN

/*!
 @class AVAudioUnitMIDIInstrument
 @abstract Base class for sample synthesizers.
 @discussion
    This base class represents audio units of type kAudioUnitType_MusicDevice or kAudioUnitType_RemoteInstrument. This can be used in a chain
    that processes realtime input (live) and has general concept of music events i.e. notes.
 */
API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVAudioUnitMIDIInstrument : AVAudioUnit AVAudioUnitMIDIInstrument_MixingConformance

#if AVAUDIOUNIT_HAVE_AUDIOUNIT
/*! @method initWithAudioComponentDescription:
 @abstract initialize the node with the component description
 @param description
    audio component description structure that describes the audio component of type kAudioUnitType_MusicDevice
    or kAudioUnitType_RemoteInstrument.
 */
- (instancetype)initWithAudioComponentDescription:(AudioComponentDescription)description;
#endif

/*! @method startNote:withVelocity:onChannel:
 @abstract sends a MIDI Note On event to the instrument
 @param note
    the note number (key) to play.
    Range: 0 -> 127
 @param velocity
    specifies the volume with which the note is played.
    Range: 0 -> 127
 @param channel
    the channel number to which the event is sent
	Range: 0 -> 15
 */
- (void)startNote:(uint8_t)note withVelocity:(uint8_t)velocity onChannel:(uint8_t)channel;

/*! @method stopNote:onChannel:
 @abstract sends a MIDI Note Off event to the instrument
 @param note
    the note number (key) to stop
    Range: 0 -> 127
 @param channel
    the channel number to which the event is sent.
	Range: 0 -> 15
 
 */
- (void)stopNote:(uint8_t)note onChannel:(uint8_t)channel;

/*! @method sendController:withValue:onChannel:
 @abstract send a MIDI controller event to the instrument.
 @param controller
    a standard MIDI controller number. 
    Range: 0 -> 127
 @param  value
    value for the controller. 
    Range: 0 -> 127
 @param channel
    the channel number to which the event is sent.
	Range: 0 -> 15

 */
- (void)sendController:(uint8_t)controller withValue:(uint8_t)value onChannel:(uint8_t)channel;

/*! @method sendPitchBend:onChannel:
 @abstract sends MIDI Pitch Bend event to the instrument.
 @param pitchbend
    value of the pitchbend
    Range: 0 -> 16383
 @param channel
    the channel number to which the event is sent.
	Range: 0 -> 15

 */
- (void)sendPitchBend:(uint16_t)pitchbend onChannel:(uint8_t)channel;

/*! @method sendPressure:onChannel:
 @abstract sends MIDI channel pressure event to the instrument.
 @param pressure 
    value of the pressure.
    Range: 0 -> 127
 @param channel
    the channel number to which the event is sent.
	Range: 0 -> 15

 */
- (void)sendPressure:(uint8_t)pressure onChannel:(uint8_t)channel;

/*! @method sendPressureForKey:withValue:onChannel:
 @abstract sends MIDI Polyphonic key pressure event to the instrument
 @param key
    the key (note) number to which the pressure event applies
    Range: 0 -> 127
 @param value
    value of the pressure
    Range: 0 -> 127
 @param channel
    the channel number to which the event is sent.
	Range: 0 -> 15

 */
- (void)sendPressureForKey:(uint8_t)key withValue:(uint8_t)value onChannel:(uint8_t)channel;

/*! @method sendProgramChange:onChannel:
 @abstract sends MIDI Program Change event to the instrument
 @param program
    the program number.
    Range: 0 -> 127
 @param channel
    the channel number to which the event is sent.
	Range: 0 -> 15
 @discussion
    the instrument will be loaded from the bank that has been previous set by MIDI Bank Select
    controller messages (0 and 31). If none has been set, bank 0 will be used. 
 */
- (void)sendProgramChange:(uint8_t)program onChannel:(uint8_t)channel;

/*! @method sendProgramChange:bankMSB:bankLSB:onChannel:
 @abstract sends a MIDI Program Change and Bank Select events to the instrument
 @param program
    specifies the program (preset) number within the bank to load.
    Range: 0 -> 127
 @param bankMSB
    specifies the most significant byte value for the bank to select.
    Range: 0 -> 127
 @param bankLSB
    specifies the least significant byte value for the bank to select.
    Range: 0 -> 127
 @param channel
    the channel number to which the event is sent.
	Range: 0 -> 15
 */
- (void)sendProgramChange:(uint8_t)program bankMSB:(uint8_t)bankMSB bankLSB:(uint8_t)bankLSB onChannel:(uint8_t)channel;

/*! @method sendMIDIEvent:data1:data2:
 @abstract sends a MIDI event which contains two data bytes to the instrument.
 @param midiStatus
    the STATUS value of the MIDI event
 @param data1
    the first data byte of the MIDI event
 @param data2
    the second data byte of the MIDI event.
  */
- (void)sendMIDIEvent:(uint8_t)midiStatus data1:(uint8_t)data1 data2:(uint8_t)data2;

/*! @method sendMIDIEvent:data1:
 @abstract sends a MIDI event which contains one data byte to the instrument.
 @param midiStatus
    the STATUS value of the MIDI event
 @param data1
    the first data byte of the MIDI event
 */
- (void)sendMIDIEvent:(uint8_t)midiStatus data1:(uint8_t)data1;

/*! @method sendMIDISysExEvent:
 @abstract sends a MIDI System Exclusive event to the instrument.
 @param midiData
    a NSData object containing the complete SysEx data including start(F0) and termination(F7) bytes.
 
 */
- (void)sendMIDISysExEvent:(NSData *)midiData;

@end

NS_ASSUME_NONNULL_END

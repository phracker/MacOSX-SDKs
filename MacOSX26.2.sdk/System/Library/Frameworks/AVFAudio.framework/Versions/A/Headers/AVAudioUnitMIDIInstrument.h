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

/// Base class for MIDI instruments.
API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVAudioUnitMIDIInstrument : AVAudioUnit AVAudioUnitMIDIInstrument_MixingConformance

#if AVAUDIOUNIT_HAVE_AUDIOUNIT
/**
 Initialize the node with the component description for an AUv2 Audio Unit.

 - Parameter description: audio component description structure that describes the audio component of type kAudioUnitType_MusicDevice
   or kAudioUnitType_RemoteInstrument.

 - note: To load AUv3 audio units (or any audio unit asynchronously), use the class
 method ``AVAudioUnit/instantiateWithComponentDescription:options:completionHandler:`` instead.
*/
- (instancetype)initWithAudioComponentDescription:(AudioComponentDescription)description;
#endif
/**
 Sends a MIDI Note On event to the instrument

 - Parameters:
   - note: the note number (key) to play. Range: 0 -> 127
   - velocity: specifies the volume with which the note is played. Range: 0 -> 127
   - channel: the channel number to which the event is sent. Range: 0 -> 15
*/
- (void)startNote:(uint8_t)note withVelocity:(uint8_t)velocity onChannel:(uint8_t)channel;
/**
 Sends a MIDI Note Off event to the instrument

 - Parameters:
   - note: the note number (key) to stop. Range: 0 -> 127
   - channel: the channel number to which the event is sent. Range: 0 -> 15
*/
- (void)stopNote:(uint8_t)note onChannel:(uint8_t)channel;
/**
 Sends a MIDI controller event to the instrument.

 - Parameters:
   - controller: a standard MIDI controller number. Range: 0 -> 127
   - value: value for the controller. Range: 0 -> 127
   - channel: the channel number to which the event is sent. Range: 0 -> 15
*/
- (void)sendController:(uint8_t)controller withValue:(uint8_t)value onChannel:(uint8_t)channel;
/**
 Sends a MIDI controller event to the instrument.

 - Parameters:
   - controller: a standard MIDI controller number. Range: 0 -> 127
   - value: value for the controller. Range: 0 -> 127
   - channel: the channel number to which the event is sent. Range: 0 -> 15
*/
- (void)sendPitchBend:(uint16_t)pitchbend onChannel:(uint8_t)channel;
/**
 Sends MIDI channel pressure event to the instrument.

 - Parameters:
   - pressure: value of the pressure. Range: 0 -> 127
   - channel: the channel number to which the event is sent. Range: 0 -> 15
*/
- (void)sendPressure:(uint8_t)pressure onChannel:(uint8_t)channel;
/**
 Sends MIDI Polyphonic key pressure event to the instrument

 - Parameters:
   - key: the key (note) number to which the pressure event applies. Range: 0 -> 127
   - value: value of the pressure. Range: 0 -> 127
   - channel: the channel number to which the event is sent. Range: 0 -> 15so
*/
- (void)sendPressureForKey:(uint8_t)key withValue:(uint8_t)value onChannel:(uint8_t)channel;
/**
 Sends MIDI Program Change event to the instrument

   The instrument will be loaded from the bank that has been previous set by MIDI Bank Select
   controller messages (0 and 31). If none has been set, bank 0 will be used.
 - Parameters:
   - program: the program number. Range: 0 -> 127
   - channel: the channel number to which the event is sent. Range: 0 -> 15
*/
- (void)sendProgramChange:(uint8_t)program onChannel:(uint8_t)channel;
/**
 Sends a MIDI Program Change and Bank Select events to the instrument

 - Parameters:
   - program: specifies the program (preset) number within the bank to load. Range: 0 -> 127
   - bankMSB: specifies the most significant byte value for the bank to select. Range: 0 -> 127
   - bankLSB: specifies the least significant byte value for the bank to select. Range: 0 -> 127
   - channel: the channel number to which the event is sent. Range: 0 -> 15
*/
- (void)sendProgramChange:(uint8_t)program bankMSB:(uint8_t)bankMSB bankLSB:(uint8_t)bankLSB onChannel:(uint8_t)channel;
/**
 Sends a MIDI event which contains two data bytes to the instrument.

 - Parameters:
   - midiStatus: the STATUS value of the MIDI event
   - data1: the first data byte of the MIDI event
   - data2: the second data byte of the MIDI event.
*/
- (void)sendMIDIEvent:(uint8_t)midiStatus data1:(uint8_t)data1 data2:(uint8_t)data2;
/**
 Sends a MIDI event which contains one data byte to the instrument.

 - Parameters:
   - midiStatus: the STATUS value of the MIDI event
   - data1: the first data byte of the MIDI event
*/
- (void)sendMIDIEvent:(uint8_t)midiStatus data1:(uint8_t)data1;
/**
 Sends a MIDI System Exclusive event to the instrument.

 - Parameters:
   - midiData: a NSData object containing the complete SysEx data including start(F0) and termination(F7) bytes.
*/
- (void)sendMIDISysExEvent:(NSData *)midiData;

#if AVAUDIOUNIT_HAVE_AUDIOUNIT
/**
Sends a MIDI event list to the instrument.

 - Parameters:
   - eventList: the MIDIEventList
*/
- (void)sendMIDIEventList:(const struct MIDIEventList *)eventList API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0)) API_UNAVAILABLE(watchos);
#endif

@end

NS_ASSUME_NONNULL_END

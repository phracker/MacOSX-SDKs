/*
     File:       AudioUnitProperties.h
 
     Contains:   Property constants for AudioUnits
 
     Version:    Technology: System 9, X
                 Release:    Mac OS X Public Beta
 
     Copyright:  (c) 2000 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __AudioUnitProperties
#define __AudioUnitProperties

#include <AudioUnit/AudioUnit.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Properties
// Apple reserves property values from 0 -> 63999
// Developers are free to use property IDs above this range at their own discretion

enum
{
// Applicable to all AudioUnits in general	(0 -> 999)
	kAudioUnitProperty_ClassInfo				= 0,
	kAudioUnitProperty_MakeConnection			= 1,
	kAudioUnitProperty_SampleRate				= 2,		// value is Float64
	kAudioUnitProperty_ParameterList			= 3,
	kAudioUnitProperty_ParameterInfo			= 4,
	kAudioUnitProperty_FastDispatch				= 5,
	kAudioUnitProperty_CPULoad					= 6,		// value Float32 (0->1) -> AUGraph uses this to tell AU what the current CPU load of a unit's graph is
	kAudioUnitProperty_SetInputCallback			= 7,		// value is AudioUnitInputCallback; scope is input, element number is the input number
	kAudioUnitProperty_StreamFormat				= 8,	
	kAudioUnitProperty_SRCAlgorithm				= 9,		// value is OSType - manufacturer of the sample rate converter AU to use
	kAudioUnitProperty_ReverbRoomType			= 10,
	kAudioUnitProperty_BusCount					= 11,
	kAudioUnitProperty_Latency					= 12,

	
// Applicable to MusicDevices				(1000 -> 1999)
	kMusicDeviceProperty_InstrumentCount 		= 1000,
	kMusicDeviceProperty_InstrumentName			= 1001,
	kMusicDeviceProperty_GroupOutputBus			= 1002,
	kMusicDeviceProperty_SoundBankFSSpec		= 1003,
	kMusicDeviceProperty_InstrumentNumber 		= 1004,
	kMusicDeviceProperty_UsesInternalReverb		= 1005,
	
// Applicable to "output" AudioUnits		(2000 -> 2999)
	kAudioOutputUnitProperty_CurrentDevice		= 2000		// value is AudioDeviceID
															// will work for HAL and default output components
};

enum {
	kAudioUnitSRCAlgorithm_Polyphase			= 'poly',
	kAudioUnitSRCAlgorithm_MediumQuality		= 'csrc'
};

enum {
	kReverbRoomType_SmallRoom = 0,
	kReverbRoomType_MediumRoom = 1,
	kReverbRoomType_LargeRoom = 2,
	kReverbRoomType_MediumHall = 3,
	kReverbRoomType_LargeHall = 4,
	kReverbRoomType_Plate = 8
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// General AudioUnit properties:
//		Unless otherwise stated, assume that the "inScope" parameter is kAudioUnitScope_Global
//		and the "inElement" parameter is ignored.
//
//		kAudioUnitProperty_ClassInfo				(void* points to AudioUnit-defined internal state)
//
//		kAudioUnitProperty_MakeConnection			(AudioUnitConnection*)
//			pass in kAudioUnitScope_Input for the AudioUnitScope
//			pass in the input number for AudioUnitElement (redundantly stored in AudioUnitConnection)
//
//		kAudioUnitProperty_SampleRate				(Float64*)
//
//		kAudioUnitProperty_ParameterList			(AudioUnitParameterID*)
//			pass in kAudioUnitScope_Global for the AudioUnitScope
//			gives you a list of AudioUnitParameterIDs from which you may query info using
//			kAudioUnitProperty_ParameterInfo
//			
//		kAudioUnitProperty_ParameterInfo			(AudioUnitParameterInfo*)
//			pass in AudioUnitParameterID for the AudioUnitElement
//
//		kAudioUnitProperty_StreamFormat				(AudioStreamBasicDescription*)
//			pass in kAudioUnitScope_Input or kAudioUnitScope_Output for the AudioUnitScope
//			pass in the input or output number (zero-based) for the AudioUnitElement
//
//		kAudioUnitProperty_ThreadPriority			(UInt32*)
//			pass in thread priority in UInt32
//
//		kAudioUnitProperty_ReverbRoomType			(Uint32*)
//			pass in one of the kReverbRoomType enum values (above) as UInt32
//
//		kAudioUnitProperty_BusCount					(UInt32*)
//			scope is either   kAudioUnitScope_Input or kAudioUnitScope_Output
//			to determine number of input or output busses
//			the number of busses is returned as UInt32
//
//		kAudioUnitProperty_Latency					(Float64*)
//			input to output latency in seconds.  AudioUnits which use delay or reverb
//			or similar should report zero latency since the delay is part of the desired effect.
//			Look-ahead compressors/limiters, pitch-shifters, phase-vocoders, buffering AudioUnits, etc.
//			may report a true latency.... 

				


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MusicDevice properties:
//
//		kMusicDeviceProperty_InstrumentCount		(UInt32* pointing to count )
//
//		kMusicDeviceProperty_InstrumentName			(formatted as char*)
//			pass in MusicDeviceInstrumentID for inElement			
//
//		kMusicDeviceProperty_GroupOutputBus			(UInt32* pointing to bus number )
//			pass in MusicDeviceGroupID for the AudioUnitElement			
//			pass in kAudioUnitScope_Group for the AudioUnitScope
//
//		kMusicDeviceProperty_InstrumentNumber		(MusicDeviceInstrumentID*)
//			pass in the instrument "index" in the inElement argument.  This "index" is zero-based and must be less
//			than the number of instruments (determined using the  kMusicDeviceProperty_InstrumentCount property).
//			The value passed back will be a MusicDeviceInstrumentID.  This MusicDeviceInstrumentID may then be used
//			with the kMusicDeviceProperty_InstrumentName property, or in any of the MusicDevice calls which take
//			a MusicDeviceInstrumentID argument.
//
//		kMusicDeviceProperty_UsesInternalReverb		(UInt32*)
//			The DLS/SoundFont MusicDevice uses an internal reverb by default and has one output bus (bus0 is dry+wet)
//			pass in a value of 0 to configure the synth to output reverb send on output bus 0 (dry output is bus 1)
//				This way it's possible to use an alternate reverb external to the MusicDevice
//			pass in a value of 1 (this is default) for internal reverb
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Output device AudioUnits
//
//		kAudioUnitProperty_GetMicroseconds			(Int32* pointing to microseconds value)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


struct AudioUnitConnection
{
	AudioUnit	sourceAudioUnit;
	UInt32		sourceOutputNumber;
	UInt32		destInputNumber;
};

// This defines a callback function which renders audio into an input of an AudioUnit
struct AudioUnitInputCallback
{
	AudioUnitRenderCallback		inputProc;
	void *						inputProcRefCon;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Parameters

// assume kAudioUnitParameterUnit_Generic if not found in this enum
enum
{
	kAudioUnitParameterUnit_Generic				= 0,	/* untyped value generally between 0.0 and 1.0 */
	kAudioUnitParameterUnit_Indexed				= 1,	/* takes an integer value (good for menu selections) */
	kAudioUnitParameterUnit_Boolean				= 2,	/* 0.0 means FALSE, non-zero means TRUE */
	kAudioUnitParameterUnit_Percent				= 3,	/* usually from 0 -> 100, sometimes -50 -> +50 */
	kAudioUnitParameterUnit_Seconds				= 4,	/* absolute or relative time */
	kAudioUnitParameterUnit_SampleFrames		= 5,	/* one sample frame equals (1.0/sampleRate) seconds */
	kAudioUnitParameterUnit_Phase				= 6,	/* -180 to 180 degrees */
	kAudioUnitParameterUnit_Rate				= 7,	/* rate multiplier, for playback speed, etc. (e.g. 2.0 == twice as fast) */
	kAudioUnitParameterUnit_Hertz				= 8,	/* absolute frequency/pitch in cycles/second */
	kAudioUnitParameterUnit_Cents				= 9,	/* unit of relative pitch */
	kAudioUnitParameterUnit_RelativeSemiTones	= 10,	/* useful for coarse detuning */
	kAudioUnitParameterUnit_MIDINoteNumber		= 11,	/* absolute pitch as defined in the MIDI spec (exact freq may depend on tuning table) */
	kAudioUnitParameterUnit_MIDIController		= 12,	/* a generic MIDI controller value from 0 -> 127 */
	kAudioUnitParameterUnit_Decibels			= 13,	/* logarithmic relative gain */
	kAudioUnitParameterUnit_LinearGain			= 14,	/* linear relative gain */
	kAudioUnitParameterUnit_Degrees				= 15,	/* -180 to 180 degrees, similar to phase but more general (good for 3D coord system) */
	kAudioUnitParameterUnit_EqualPowerCrossfade = 16,	/* 0.0 -> 1.0, crossfade mix two sources according to sqrt(x) and sqrt(1.0 - x) */
	kAudioUnitParameterUnit_MixerFaderCurve1	= 17,	/* 0.0 -> 1.0, pow(x, 3.0) -> linear gain to simulate a reasonable mixer channel fader response */
	kAudioUnitParameterUnit_Pan					= 18	/* standard left to right mixer pan */
};

typedef UInt32		AudioUnitParameterUnit;

// if the "unit" field contains a value not in the enum above, then assume kAudioUnitParameterUnit_Generic
struct AudioUnitParameterInfo
{
	char 					name[64];
	AudioUnitParameterUnit	unit;				// unit type (Hertz, Decibels, etc. -- see enum )		
	Float32					minValue;			// minimum legal value
	Float32					maxValue;			// maximum legal value
	Float32					defaultValue;		// initial value when AudioUnit is first initialized or reset
	UInt32					flags;				// read-only attributes, etc.
};

// flags for AudioUnitParameterInfo
enum
{
	kAudioUnitParameterFlag_Global		= (1L << 0),	//	parameter scope is global
	kAudioUnitParameterFlag_Input		= (1L << 1),	//	parameter scope is input
	kAudioUnitParameterFlag_Output		= (1L << 2),	//	parameter scope is output
	kAudioUnitParameterFlag_Group		= (1L << 3),	//	parameter scope is group
	
	kAudioUnitParameterFlag_IsReadable	= (1L << 30),
	kAudioUnitParameterFlag_IsWritable	= (1L << 31)
};


#endif // __AudioUnitProperties

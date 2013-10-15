/*
     File:       AudioUnitParameters.h
 
     Contains:   Parameter constants for Apple AudioUnits
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __AudioUnitParameters
#define __AudioUnitParameters

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following specifies the equivalent parameterID's for the Group Scope for the standard
MIDI Controllers. The list is not exhaustive, but represents a recommended set of 
parameters in Group Scope (and their corresponding MIDI messages) that should be supported

ParameterID ranges on the Group Scope from 0 < 512 are reserved for usage when Mapping MIDI 
controllers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
enum {
	kAUGroupParameterID_Volume					= 7,	// value 0 < 128
	kAUGroupParameterID_Sustain					= 64, 	// value 0-63 (off), 64-127 (on)
	kAUGroupParameterID_AllNotesOff				= 123,	// value ignored
	kAUGroupParameterID_ModWheel				= 1,	// value 0 < 128
	kAUGroupParameterID_PitchBend				= 0xE0,	// value -8192 - 8191
	kAUGroupParameterID_AllSoundOff				= 120,	// value ignored
	kAUGroupParameterID_ResetAllControllers		= 121,	// value ignored
	kAUGroupParameterID_Pan						= 10,	// value 0 < 128
	kAUGroupParameterID_Foot					= 4,	// value 0 < 128
	kAUGroupParameterID_ChannelPressure			= 0xD0,	// value 0 < 128
	kAUGroupParameterID_KeyPressure				= 0xA0,	// values 0 < 128
	kAUGroupParameterID_Expression				= 11,	// value 0 < 128
	kAUGroupParameterID_DataEntry				= 6,	// value 0 < 128

	kAUGroupParameterID_Volume_LSB				= kAUGroupParameterID_Volume + 32,		// value 0 < 128
	kAUGroupParameterID_ModWheel_LSB			= kAUGroupParameterID_ModWheel + 32,	// value 0 < 128
	kAUGroupParameterID_Pan_LSB					= kAUGroupParameterID_Pan + 32,			// value 0 < 128
	kAUGroupParameterID_Foot_LSB				= kAUGroupParameterID_Foot + 32,		// value 0 < 128
	kAUGroupParameterID_Expression_LSB			= kAUGroupParameterID_Expression + 32,	// value 0 < 128
	kAUGroupParameterID_DataEntry_LSB			= kAUGroupParameterID_DataEntry + 32,	// value 0 < 128
	
	kAUGroupParameterID_KeyPressure_FirstKey	= 256,	// value 0 < 128
	kAUGroupParameterID_KeyPressure_LastKey		= 383	// value 0 < 128
};	


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A special note on kAUGroupParameterID_KeyPressure (Polyphonic Aftertouch)
	Publish this (0xA0) to say you support polyphonic key pressure.
	Polyphonic key pressure is not a single control; it is a control for each of the 128
		MIDI key numbers.
	The key pressure values pairs actualy values are to be get or set in the following parameter range
		ParameterID: 256-383
		Thus to set/get the value of Poly Key pressure add kAUGroupParameterID_KeyPressure_FirstKey (256)
		to the MIDI key number - this becomes the parameter ID
		The pressure Value is 0 < 128
	Thus to get/set by key value you take the MIDI key number (0 - 127) and add/subtract to/from:
		kAUGroupParameterID_KeyPressure_FirstKey
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following file specifies the parameter IDs for the various audio units that apple ships,
allowing code to directly interact with these parameters without first discovering them
through the AUParameterInfo mechanism (see AudioUnitProperties.h)

Each parameter listed below is preceeded by a comment that indicates:
    // Scope, UnitOfMeasurement, minValue, maxValue, defaultValue
    
See AudioUnitProperties for additional information that a parameter may report

When displaying to the user information about a parameter an application SHOULD ALWAYS
get the parameter information from the AudioUnit itself
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


// Effects units
// Some parameters of effects units are dependent on the sample rate of the audio unit
// (ie. the maximum value is typically the Nyquist limit, or half the sample rate)

// Parameters for the BandpassFilter Unit
enum {
		// Global, Hz, 20->(SampleRate/2), 5000
	kBandpassParam_CenterFrequency 			= 0,

		// Global, Cents, 100->12000, 600
	kBandpassParam_Bandwidth 				= 1
};

// Some parameters for the AUGraphicEQ Unit
enum {
		// Global, Indexed, currently either 10 or 31
	kGraphicEQParam_NumberOfBands 			= 10000
};

// Parameters of the AUHipass Unit
enum {
		// Global, Hz, 10->(SampleRate/2), 6900
	kHipassParam_CutoffFrequency 			= 0,
		
		// Global, dB, -20->40, 0
	kHipassParam_Resonance					= 1
};

// Parameters of the AULowpass Unit
enum {
		// Global, Hz, 10->(SampleRate/2), 6900
	kLowPassParam_CutoffFrequency 			= 0,
		
		// Global, dB, -20->40, 0
	kLowPassParam_Resonance 				= 1
};

// Parameters of the AUHighShelfFilter
enum {
		// Global, Hz, 10000->(SampleRate/2), 10000
	kHighShelfParam_CutOffFrequency 		= 0,
		
		// Global, dB, -40->40, 0
	kHighShelfParam_Gain 					= 1
};

// Parameters of the AULowShelfFilter
enum {
		// Global, Hz, 10->200, 80
	kAULowShelfParam_CutoffFrequency = 0,
		
		// Global, dB, -40->40, 0
	kAULowShelfParam_Gain = 1
};

// Parameters of the AUParametricEQ
enum {
		// Global, Hz, 20->(SampleRate/2), 2000
    kParametricEQParam_CenterFreq = 0,
		
		// Global, Hz, 0.1->20, 1.0
    kParametricEQParam_Q = 1,
		
		// Global, dB, -20->20, 0
    kParametricEQParam_Gain = 2
};

// Parameters of the AUMatrixReverb
enum {
		// Global, EqPow CrossFade, 0->100, 100
	kReverbParam_DryWetMix 							= 0,
		
		// Global, EqPow CrossFade, 0->100, 50
	kReverbParam_SmallLargeMix						= 1,
		
		// Global, Secs, 0.005->0.020, 0.06
	kReverbParam_SmallSize							= 2,
		
		// Global, Secs, 0.4->10.0, 3.07
	kReverbParam_LargeSize							= 3,
		
		// Global, Secs, 0.001->0.03, 0.025
	kReverbParam_PreDelay							= 4,
		
		// Global, Secs, 0.001->0.1, 0.035
	kReverbParam_LargeDelay							= 5,
		
		// Global, Genr, 0->1, 0.28
	kReverbParam_SmallDensity						= 6,
		
		// Global, Genr, 0->1, 0.82
	kReverbParam_LargeDensity						= 7,
		
		// Global, Genr, 0->1, 0.3
	kReverbParam_LargeDelayRange					= 8,
		
		// Global, Genr, 0.1->1, 0.96
	kReverbParam_SmallBrightness					= 9,
		
		// Global, Genr, 0.1->1, 0.49
	kReverbParam_LargeBrightness					= 10,

		// Global, Genr, 0->1 0.5
	kReverbParam_SmallDelayRange					= 11,

		// Global, Hz, 0.001->2.0, 1.0
	kReverbParam_ModulationRate						= 12,

		// Global, Genr, 0.0 -> 1.0, 0.2
	kReverbParam_ModulationDepth					= 13
};

// Parameters for the Delay Unit
enum {
		// Global, EqPow Crossfade, 0->100, 50
	kDelayParam_WetDryMix 				= 0,
		
		// Global, Secs, 0->2, 1
	kDelayParam_DelayTime				= 1,
		
		// Global, Percent, -100->100, 50
	kDelayParam_Feedback 				= 2,
		
		// Global, Hz, 10->(SampleRate/2), 15000
	kDelayParam_LopassCutoff	 		= 3
};

// Parameters for the AUPeakLimiter
enum {
		// Global, Secs, 0.001->0.03, 0.012
	kLimiterParam_AttackTime 			= 0,
		
		// Global, Secs, 0.001->0.06, 0.024
	kLimiterParam_DecayTime 			= 1,
		
		// Global, dB, -40->40, 0
	kLimiterParam_PreGain 				= 2
};


// Parameters for the AUDynamicsProcessor
enum {
		// Global, dB, -40->20, -20
	kDynamicsProcessorParam_Threshold 			= 0,
		
		// Global, rate, 0.1->40.0, 5
	kDynamicsProcessorParam_HeadRoom	 		= 1,
		
		// Global, rate, 1->50.0, 2
	kDynamicsProcessorParam_ExpansionRatio		= 2,
		
		// Global, dB
	kDynamicsProcessorParam_ExpansionThreshold	= 3,
		
		// Global, secs, 0.0001->0.2, 0.001
	kDynamicsProcessorParam_AttackTime 			= 4,
		
		// Global, secs, 0.01->3, 0.05
	kDynamicsProcessorParam_ReleaseTime 		= 5,
		
		// Global, dB, -40->40, 0
	kDynamicsProcessorParam_MasterGain 			= 6,
	
		// Global, dB, read-only parameter
	kDynamicsProcessorParam_CompressionAmount 	= 1000
};


// Parameters for the AUMultibandCompressor
enum {
	kMultibandCompressorParam_Pregain 			= 0,
	kMultibandCompressorParam_Postgain 			= 1,
	kMultibandCompressorParam_Crossover1 		= 2,
	kMultibandCompressorParam_Crossover2 		= 3,
	kMultibandCompressorParam_Crossover3 		= 4,
	kMultibandCompressorParam_Threshold1 		= 5,
	kMultibandCompressorParam_Threshold2 		= 6,
	kMultibandCompressorParam_Threshold3 		= 7,
	kMultibandCompressorParam_Threshold4 		= 8,
	kMultibandCompressorParam_Headroom1 		= 9,
	kMultibandCompressorParam_Headroom2 		= 10,
	kMultibandCompressorParam_Headroom3 		= 11,
	kMultibandCompressorParam_Headroom4 		= 12,
	kMultibandCompressorParam_AttackTime 		= 13,
	kMultibandCompressorParam_ReleaseTime 		= 14,
	kMultibandCompressorParam_EQ1 				= 15,
	kMultibandCompressorParam_EQ2 				= 16,
	kMultibandCompressorParam_EQ3 				= 17,
	kMultibandCompressorParam_EQ4 				= 18,
	
	// read-only parameters
	kMultibandCompressorParam_CompressionAmount1 = 1000,
	kMultibandCompressorParam_CompressionAmount2 = 2000,
	kMultibandCompressorParam_CompressionAmount3 = 3000,
	kMultibandCompressorParam_CompressionAmount4 = 4000
};

// Parameters for the AUVarispeed
enum {
	kVarispeedParam_PlaybackRate				= 0,
	kVarispeedParam_PlaybackCents				= 1
};

// Parameters for AUTimePitch, AUOfflineTimePitch, AUPitch
enum {
	kTimePitchParam_Rate						= 0,
	kTimePitchParam_Pitch						= 1,
	kTimePitchParam_EffectBlend					= 2		// only for AUPitch
};

// Parameters for AUFilter
enum
{
	kMultibandFilter_LowFilterType  = 0,
	kMultibandFilter_LowFrequency   = 1,
	kMultibandFilter_LowGain		= 2,

	kMultibandFilter_CenterFreq1	= 3,
	kMultibandFilter_CenterGain1	= 4,
	kMultibandFilter_Bandwidth1		= 5,
	
	kMultibandFilter_CenterFreq2	= 6,
	kMultibandFilter_CenterGain2	= 7,
	kMultibandFilter_Bandwidth2		= 8,
	
	kMultibandFilter_CenterFreq3	= 9,
	kMultibandFilter_CenterGain3	= 10,
	kMultibandFilter_Bandwidth3		= 11,

	kMultibandFilter_HighFilterType	= 12,
	kMultibandFilter_HighFrequency  = 13,
	kMultibandFilter_HighGain		= 14
};

// Mixer Units
// Parameters for the 3DMixer AudioUnit
enum {
        // Input, Degrees, -180->180, 0
    k3DMixerParam_Azimuth		= 0,
        
		// Input, Degrees, -90->90, 0
    k3DMixerParam_Elevation		= 1,
        
		// Input, Metres, 0->10000, 1
    k3DMixerParam_Distance		= 2,
        
		// Input/Output, dB, -120->20, 0
    k3DMixerParam_Gain			= 3,
	
		// Input, rate scaler	0.5 -> 2.0
    k3DMixerParam_PlaybackRate	= 4,
	
		// read-only
	k3DMixerParam_PreAveragePower	= 1000,
	k3DMixerParam_PrePeakHoldLevel	= 2000,
	k3DMixerParam_PostAveragePower	= 3000,
	k3DMixerParam_PostPeakHoldLevel	= 4000
};

// Parameters for the Stereo Mixer AudioUnit
enum {
		// Input/Output, Mixer Fader Curve, 0->1, 1
	kStereoMixerParam_Volume 	= 0,
		
		// Input, Pan, 0->1, 0.5
	kStereoMixerParam_Pan		= 1,
	
		// read-only
	kStereoMixerParam_PreAveragePower	= 1000,
	kStereoMixerParam_PrePeakHoldLevel	= 2000,
	kStereoMixerParam_PostAveragePower	= 3000,
	kStereoMixerParam_PostPeakHoldLevel	= 4000
};

// Parameters for the Matrix Mixer AudioUnit
enum {
	kMatrixMixerParam_Volume 	= 0,
	kMatrixMixerParam_Enable 	= 1,
	
		// read-only
	// these report level in dB, as do the other mixers
	kMatrixMixerParam_PreAveragePower	= 1000,
	kMatrixMixerParam_PrePeakHoldLevel	= 2000,
	kMatrixMixerParam_PostAveragePower	= 3000,
	kMatrixMixerParam_PostPeakHoldLevel	= 4000,

	// these report linear levels - for "expert" use only.
	kMatrixMixerParam_PreAveragePowerLinear			= 5000,
	kMatrixMixerParam_PrePeakHoldLevelLinear		= 6000,
	kMatrixMixerParam_PostAveragePowerLinear		= 7000,
	kMatrixMixerParam_PostPeakHoldLevelLinear		= 8000
};

// Parameters for AUNetReceive
enum {
	kAUNetReceiveParam_Status = 0,
	kAUNetReceiveParam_NumParameters = 1
};

// Parameters for AUNetSend
enum {
	kAUNetSendParam_Status = 0,
	kAUNetSendParam_NumParameters = 1
};


// Status values for AUNetSend and AUNetReceive
enum {
	kAUNetStatus_NotConnected = 0,
	kAUNetStatus_Connected = 1,
	kAUNetStatus_Overflow = 2,
	kAUNetStatus_Underflow = 3,
	kAUNetStatus_Connecting = 4,
	kAUNetStatus_Listening = 5
};


// Output Units
// Parameters for the HAL Output Unit (and Default and System Output units)
enum {
		// Global, LinearGain, 0->1, 1
	kHALOutputParam_Volume 		= 14 
};

// Music Device
// Parameters for the DLSMusicDevice Unit - defined and reported in the global scope
enum {
		// Global, Cents, -1200, 1200, 0
	kMusicDeviceParam_Tuning 	= 0,

		// Global, dB, -120->40, 0
	kMusicDeviceParam_Volume	= 1,

		// Global, dB, -120->40, 0
	kMusicDeviceParam_ReverbVolume	= 2
};
// The DLS music device does NOT currently report parameters in the GroupScope
// but a parameter value can be set (not retrieved) that corresponds to 
// controller values that are defined by the MIDI specification in Group scope.
// This includes the specified MIDI Controller values (e.g. Volume, Mod Wheel, etc)
// as well as the MIDI status messages (such as PitchWheel 0xE0, ChannelPressure 0xD0 - make sure
// you pass in zero for the "channel part" when using these as parameterID - to distinguish this 
// from 0-127 values for midi controllers that will take up the first byte) and the MIDI RPN control messages.
// Remember, the elementID represents the group or channel number... You can use of course, MusicDeviceMIDIEvent to
// send a MIDI formatted control command to the device.

// Using AudioUnitParameterSet with this protocol is done as follows:
//	scope == kAudioUnitScope_Group
//	element == groupID -> in MIDI equivalent to channel number 0->15, 
//			but this is not a limitation of the MusicDevice and values greater than 15 can be specified
//	paramID == midi controller value (0->127), (status bytes corresponding to pitch bend, channel pressure)
//	value == typically the range associated with the corresponding MIDI message	(7 bit, 0->127)
//			pitch bend is specified as a 14 bit value
	
// See MusicDevice.h for more comments about using the extended control semantics of this component.	
#endif //__AudioUnitParameters

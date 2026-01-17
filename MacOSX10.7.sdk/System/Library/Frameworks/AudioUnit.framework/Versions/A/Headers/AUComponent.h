/*
	File:		AUComponent.h

	Contains:	AudioUnit Interfaces

	Copyright:	© 2002-2008 by Apple, Inc., all rights reserved.

	Bugs?:		For bug reports, consult the following page on
				the World Wide Web:

					http://developer.apple.com/bugreporter/
*/

#ifndef __AUCOMPONENT__
#define __AUCOMPONENT__

//================================================================================================
#pragma mark Overview

/*!
    @header AUComponent
	
	@discussion
	This file defines the collection of API calls for an audio unit. An audio unit is a plugin 
	that can be loaded into an application's process and used to process or generate audio. An 
	audio unit is an AudioComponent type and so
	the AudioComponent APIs are used to find specific types of audio units, open and close them.
	
	Audio units use a general notion of description to specify an unique instance. The Type is the 
	general category of an audio unit. The SubType is an unique identifier specified by the 
	Manufacturer (provider) of the audio unit. The IDs that are used for Type are specified by 
	Apple, the Manufacturer ID should be specified by an unique identifier
	(as registered with apple). See AudioComponentDescription.
	
	Audio unit types are of the following (see below for more information)

		kAudioUnitType_Output					= 'auou',
		kAudioUnitType_MusicDevice				= 'aumu',
		kAudioUnitType_MusicEffect				= 'aumf',
		kAudioUnitType_FormatConverter			= 'aufc',	
		kAudioUnitType_Effect					= 'aufx',	
		kAudioUnitType_Mixer					= 'aumx',
		kAudioUnitType_Panner					= 'aupn',
		kAudioUnitType_OfflineEffect			= 'auol',
		kAudioUnitType_Generator				= 'augn',

	An audio unit's general operations are:
		Open an audio unit (AudioComponentInstanceNew)
		Configure it based on the context - AudioUnitSetProperty
		Initialise the audio unit (AudioUnitInitialize)
			- at this point the audio unit is in a state where it can render audio
		Render audio (AudioUnitRender)
		
	An important part of a render operation for an audio unit is to manipulate the various controls 
	that the unit provides to change the render effects; for instance to change the decay time of 
	a reverb, the cut off frequency of a filter, etc. These are called parameters, and 
	AudioUnitGetParameter and AudioUnitSetParameter are used to interact with these.
	
	If any reconfiguration of the audio unit is required, then:
		uninitialise (AudioUnitUninitialise)
		Configure it based on the context - AudioUnitSetProperty
		Initialise the audio unit (AudioUnitInitialize)

	Once the host is finished with an audio unit, it closes it:
		Dispose audio unit (AudioComponentInstanceDispose)
	
	Audio units can be used programmatically (for instance a mixers could be used to render audio 
	for a game, a generator to play audio files, etc), or they can be hosted in Digital 
	Audio Workstation (DAW) applications such as Logic, Garage Band. In the DAW case, it is common 
	for an audio unit to provide a custom view to allow the user to interact with what can be 
	complex DSP operations that the audio unit performs. The view is retrieved from an audio unit 
	through AudioUnitGetProperty and then the host instantiates it 
	(see <AudioUnit/AUCocoaUIView.h>)
*/



#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AudioComponent.h>
	#include <CoreAudio/CoreAudioTypes.h>
#else
	#include <AudioComponent.h>
	#include <CoreAudioTypes.h>
#endif

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_IMPORT
#pragma import on
#endif

#if !__LP64__
	#if PRAGMA_STRUCT_ALIGN
		#pragma options align=mac68k
	#elif PRAGMA_STRUCT_PACKPUSH
		#pragma pack(push, 2)
	#elif PRAGMA_STRUCT_PACK
		#pragma pack(2)
	#endif
#endif

//================================================================================================
#pragma mark -
#pragma mark Audio Unit Types
/*!
	@typedef			AudioUnit
	@discussion			An audio unit is of type AudioComponentInstance as defined in 
						AudioComponent.h
*/
typedef AudioComponentInstance AudioUnit;


/*!
    @enum           Audio Unit Types
    @abstract		different types of audio units
	@discussion		Audio unit's are classified into different types, where those types perform 
					different roles and functions.
					There are some general categories of functionality that apply across different 
					types of audio units:
					(1) Real-time usage
						The audio unit will complete its operations in less time that is 
						represented by the render buffer. All audio units with the exception of 
						the OfflineEffect should meet this criteria
					(2) Real-time I/O
						Will request the same amount of audio input as it is being asked to 
						produce for output. Effects, Panners, Mixers and MusicDevices are required 
						to adhere to this restriction. FormatConverter's can with some constraints
						be used in this situation (for instance, sample rate conversion, float-int),
						but the host of the audio unit is responsible for insuring this.
					(3) UI versus Programmatic usage
						UI usage covers the case of using an audio unit in a Digital Audio 
						Workstation (DAW) with appropriate UI (for example a filter in Garage Band 
						or Logic). Effects, Panners, MusicDevices are all expected to be usable 
						within this context. 
						Programmatic usage is where an audio unit is used by a host app as part of
						a general signal processing chain.
						For instance, a mixer audio unit can be used to take several different 
						audio sources in a game and mix them together. Mixers, Output units are 
						for programmatic usage. FormatConverter and Generator types are generally
						programmatic audio units, but if they can be used in a UI situation, they 
						specify a custom view. The app can then use that to decide that, with 
						appropriate constraints, the audio unit could be presented in a DAW type 
						application. For instance, the AUConverter audio unit from apple can do 
						sample rate conversion, etc, but has not general utility for a user in a 
						DAW app. Apple's Varispeed or AUTimePitch audio units can be used to change
						the playback rate and pitch and so could be used to good affect by a user 
						in a DAW type environment, as well as just providing this general 
						functionality to any program.
					
	@constant		kAudioUnitType_Output
					An output unit can be used as the head of an AUGraph. Apple provides a number 
					of output units that interface directly with an audio device
					
	@constant		kAudioUnitType_MusicDevice
					Used to describe software musical instruments such as samplers and 
					synthesisers. They respond to MIDI and create notes, which are then controlled
					through parameters or MIDI control messages. See <AudioUnit/MusicDevice.h>
										
	@constant		kAudioUnitType_MusicEffect
					Is an effect that is also able to respond directly to MIDI control messages, 
					typically through the mapping of these MIDI messages to different parameters 
					of the effect's DSP algorithm.
					
	@constant		kAudioUnitType_FormatConverter
					A format converter is a general category for audio units that can change the 
					format (for instance, sample rate conversion) from an input to an output, as 
					well as other, non-I/O type manipulations (like a deferred render or varispeed 
					type of operation). As such, a format converter can ask for as much or as 
					little audio input to produce a given output. They are still expected to
					complete their rendering within the time represented by the output buffer. 
					For format converters that have some utility as an "audio effect or processor", 
					it is quite common to provide an offline version of this audio unit as well. 
					For instance, Apple ships a format converter (for use in a "real-time" like 
					situation) and an offline version (for processing audio files) of the Time 
					Pitch and Varispeed audio units.
					
	@constant		kAudioUnitType_Effect
					An audio unit that will process some x number of audio input samples to produce 
					x number of audio output samples. The common case for an effect is to have a 
					single input to a single output, though some effects take side-chain inputs as 
					well. Effects can be run in "offline" contexts (such as processing a file), but 
					they are expected to run in real-time. A delay unit or reverb is a good 
					example of this.
					
	@constant		kAudioUnitType_Mixer
					An audio unit that takes some number of inputs, mixing them to provide 1 or 
					more audio outputs. A stere mixer (mono and stereo inputs to produce one 
					stereo output) is an example of this.
					
	@constant		kAudioUnitType_Panner
					A panner is a specialised effect that will pan a single audio input to a single
					output. Panner units are required to support a collection of standardised 
					parameters that specify the panning coordinates (aside from whatever custom 
					parameters the panner may provide). A surround panner is an example of this
					
	@constant		kAudioUnitType_Generator
					A generator will have no audio input, but will just produce audio output. In 
					some ways it is similar to a MusicDevice, except that a generator provides no 
					MIDI input, or notion of "notes". A tone generator is a good example of this.
					
	@constant		kAudioUnitType_OfflineEffect
					An offline effect is used to process data from a file and is also used to 
					publish a capability that cannot be run in real-time. For instance, the process
					of normalisation requires seeing the entire audio input before the scalar to 
					apply in the normalisation process can be estimated. As such, offline effects 
					also have a notion of a priming stage that can be performed before the actual 
					rendering/processing phase is executed.
*/
enum
{
	kAudioUnitType_Output					= 'auou',
	kAudioUnitType_MusicDevice				= 'aumu',
	kAudioUnitType_MusicEffect				= 'aumf',
	kAudioUnitType_FormatConverter			= 'aufc',
	kAudioUnitType_Effect					= 'aufx',
	kAudioUnitType_Mixer					= 'aumx',
	kAudioUnitType_Panner					= 'aupn',
	kAudioUnitType_Generator				= 'augn',
	kAudioUnitType_OfflineEffect			= 'auol'
};

//================================================================================================
#pragma mark -
#pragma mark Apple Audio Units
/*!
    @enum           Apple audio unit manufacturer ID.
    @discussion		the unique ID used to identifier audio units provided by Apple, Inc.
*/
enum {
	kAudioUnitManufacturer_Apple			= 'appl'
};
	
/*!
	@enum			Apple output audio unit sub types 
	@discussion		These are the subtypes for the various output units that apple ships. Output 
					units add an additional notion of Start and Stop
					see <AudioUnit/AudioOutputUnit.h>

	@constant		kAudioUnitSubType_GenericOutput
					A generic output unit provides the start/stop API, and provides the basic 
					services to convert Linear PCM formats.


	@constant		kAudioUnitSubType_HALOutput			
						- desktop only
					The audio unit that interfaces to any audio device. The user specifies which 
					audio device to track. The audio unit can do input from the device as well as 
					output to the device. Bus 0 is used for the output side, bus 1 is used
					to get audio input from the device.
					
	@constant		kAudioUnitSubType_DefaultOutput		
						- desktop only
					A specialisation of AUHAL that is used to track the user's selection of the 
					default device as set in the Sound Prefs
					
	@constant		kAudioUnitSubType_SystemOutput		
						- desktop only
					A specialisation of AUHAL that is used to track the user's selection of the 
					device to use for sound effects, alerts
					and other UI sounds.

	@constant		kAudioUnitSubType_RemoteIO			
						- iPhone only
					The audio unit that interfaces to the audio I/O pathways of the iPhone. The 
					audio unit can do input as well as output. Bus 0 is used for the output side, 
					bus 1 is used to get audio input.
	@constant		kAudioUnitSubType_VoiceProcessingIO
						- Available on the desktop and with iPhone 3.0 or greater
					This audio unit can do input as well as output. Bus 0 is used for the output 
					side, bus 1 is used to get audio input (thus, on the iPhone, it works in a 
					very similar way to the Remote I/O). This audio unit does signal processing on 
					the incoming audio (taking out any of the audio that is played from the device 
					at a given time from the incoming audio).
*/
enum {
	kAudioUnitSubType_GenericOutput			= 'genr',
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_HALOutput				= 'ahal',
	kAudioUnitSubType_DefaultOutput			= 'def ',
	kAudioUnitSubType_SystemOutput			= 'sys ',
#else
	kAudioUnitSubType_RemoteIO				= 'rioc',
#endif
	kAudioUnitSubType_VoiceProcessingIO		= 'vpio'
};

/*!
	@enum			Apple music instrument audio unit sub types 

	@constant		kAudioUnitSubType_DLSSynth			
						- desktop only
					A multi-timbral music device that can use sample banks in either DLS or 
					SoundFont formats. It fully supports GM-MIDI and the basic extensions of 
					GS-MIDI
	@constant		kAudioUnitSubType_Sampler			
						- desktop only
					A mono-timbral music device which is a sampler synthesizer and supports full 
					interactive editing of all state.
*/
#if !TARGET_OS_IPHONE
enum {
	kAudioUnitSubType_DLSSynth				= 'dls ',
	kAudioUnitSubType_Sampler				= 'samp'
};
#endif

/*!
	@enum			Apple converter audio unit sub types 
	@discussion		These are the subtypes for the various converter units that apple ships. 
					Except for AUConverter, which is available on both desktop and iPhone, these 
					audio units are only available on the desktop.

	@constant		kAudioUnitSubType_AUConverter
					An audio unit that uses an AudioConverter to do Linear PCM conversions (sample 
					rate, bit depth, interleaving).

	@constant		kAudioUnitSubType_TimePitch
						- desktop only
					An audio unit that can be used to have independent control of both playback 
					rate and pitch. It provides a generic view, so can be used in both a UI and 
					programmatic context. It also comes in an Offline version so can be used to 
					process audio files.
					
	@constant		kAudioUnitSubType_Varispeed
						- desktop only
					An audio unit that can be used to control playback rate (as the rate is faster, 
					the pitch is higher). It provides a generic view, so can be used in both a UI 
					and programmatic context. It also comes in an Offline version so can be used 
					to process audio files.
					
	@constant		kAudioUnitSubType_DeferredRenderer
						- desktop only
					An audio unit that is used to get its input from a separate thread than the 
					thread that its render method is called. It thus allows an application to 
					introduce multiple threads into a rendering graph. There is a buffer sized 
					delay introduced between the input and output
					
	@constant		kAudioUnitSubType_Splitter
						- desktop only
					An audio unit that provides 2 output buses and 1 input bus. The audio unit 
					splits (duplicates) the input signal to the two output buses
					
	@constant		kAudioUnitSubType_Merger
						- desktop only
					An audio unit that provides 2 input buses and 2 output bus. The audio unit 
					merges the two inputs to the single output

	@constant		kAudioUnitSubType_NewTimePitch
					An audio unit that provides good quality time stretching and pitch shifting 
					while still being very fast.

	@constant		kAudioUnitSubType_AUiPodTime
						- iPhone only
					An audio unit that provides simple (and limited) control over playback rate 
					and time.
*/
enum{
	kAudioUnitSubType_AUConverter			= 'conv',
	
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_NewTimePitch			= 'nutp',
	kAudioUnitSubType_TimePitch				= 'tmpt',
	kAudioUnitSubType_Varispeed				= 'vari',
	kAudioUnitSubType_DeferredRenderer		= 'defr',
	kAudioUnitSubType_Splitter				= 'splt',
	kAudioUnitSubType_Merger				= 'merg',
	kAudioUnitSubType_RoundTripAAC			= 'raac'
#else
	kAudioUnitSubType_AUiPodTime			= 'iptm'
#endif
};

/*!
	@enum			Apple effect audio unit sub types 
	@discussion		These are the subtypes for the various effect units that apple ships

	@constant		kAudioUnitSubType_Delay					
						- desktop only
					A delay audio unit
					
	@constant		kAudioUnitSubType_LowPassFilter			
						- desktop only
					A filter that passes frequencies below a specified cut-off frequency
					
	@constant		kAudioUnitSubType_HighPassFilter		
						- desktop only
					A filter that passes frequencies above a specified cut-off frequency
					
	@constant		kAudioUnitSubType_BandPassFilter		
						- desktop only
					A filter that passes frequencies between a low and high cut-off frequency.
					
	@constant		kAudioUnitSubType_HighShelfFilter		
						- desktop only
					A filter that can be used to implement a "treble" control
					
	@constant		kAudioUnitSubType_LowShelfFilter		
						- desktop only
					A filter that can be used to implement a "bass" control

	@constant		kAudioUnitSubType_ParametricEQ			
						- desktop only
					A parametric EQ filter
					
	@constant		kAudioUnitSubType_GraphicEQ				
						- desktop only
					A 10 or 31 band Graphic EQ
					
	@constant		kAudioUnitSubType_PeakLimiter			
						- desktop only
					A peak limiter
					
	@constant		kAudioUnitSubType_DynamicsProcessor		
						- desktop only
					A dynamics compressor/expander
					
	@constant		kAudioUnitSubType_MultiBandCompressor	
						- desktop only
					A 4 band compressor/expander
					
	@constant		kAudioUnitSubType_MatrixReverb			
						- desktop only
					A reverb that can be used to simulate various and different spaces
					
	@constant		kAudioUnitSubType_SampleDelay			
						- desktop only
					A delay that is used to delay the input a specified number of samples until 
					the output
					
	@constant		kAudioUnitSubType_Pitch					
						- desktop only
					An audio unit used to change the pitch
					
	@constant		kAudioUnitSubType_AUFilter				
						- desktop only
					A filter unit that combines 5 different filters (low, 3 mids, high)
					
	@constant		kAudioUnitSubType_NetSend				
						- desktop only
					An audio unit that is used in conjunction with _NetReceive to send audio 
					across the network (or between different applications)
					
	@constant		kAudioUnitSubType_Distortion			
						- desktop only
					A distortion audio unit 
					
	@constant		kAudioUnitSubType_RogerBeep				
						- desktop only
					An audio unit that can be used to emit a short tone in gaps between speech 
					- similar to the tones used in a walkie-talkie
					
	@constant		kAudioUnitSubType_AUiPodEQ				
						- iPhone only
					A graphic EQ
*/
enum {
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_Delay					= 'dely',
	kAudioUnitSubType_LowPassFilter			= 'lpas',
	kAudioUnitSubType_HighPassFilter		= 'hpas',
	kAudioUnitSubType_BandPassFilter		= 'bpas',
	kAudioUnitSubType_HighShelfFilter		= 'hshf',
	kAudioUnitSubType_LowShelfFilter		= 'lshf',
	kAudioUnitSubType_ParametricEQ			= 'pmeq',
	kAudioUnitSubType_GraphicEQ				= 'greq',
	kAudioUnitSubType_PeakLimiter			= 'lmtr',
	kAudioUnitSubType_DynamicsProcessor		= 'dcmp',
	kAudioUnitSubType_MultiBandCompressor	= 'mcmp',
	kAudioUnitSubType_MatrixReverb			= 'mrev',
	kAudioUnitSubType_SampleDelay			= 'sdly',
	kAudioUnitSubType_Pitch					= 'tmpt',
	kAudioUnitSubType_AUFilter				= 'filt',
	kAudioUnitSubType_NetSend				= 'nsnd',
	kAudioUnitSubType_Distortion			= 'dist',
	kAudioUnitSubType_RogerBeep				= 'rogr',
	kAudioUnitSubType_BoostClip				= 'pbcl',
	kAudioUnitSubType_Volume				= 'volu',
#else
	kAudioUnitSubType_AUiPodEQ				= 'ipeq',
#endif
};

/*!
	@enum			Apple mixer audio unit sub types 
	@discussion		These are the subtypes for the various mixer units that apple ships

	@constant		kAudioUnitSubType_MultiChannelMixer
					Can have any number of inputs, with any number of channels on any input to one 
					output bus with any number of channels on  the desktop. On iPhone the output 
					number of channels is 2.
				
	@constant		kAudioUnitSubType_StereoMixer
						- desktop only
					Inputs can be mono or stereo. Single stereo output
					
	@constant		kAudioUnitSubType_3DMixer
						- desktop only
					Inputs can be mono, in which case they can be panned around using 3D 
					coordinates and parameters. 
					Stereo inputs are passed directly through to the output.
					4 channel "ambisonic" inputs will be rendered to the output configuration
					A single output of 2, 4, 5, 6, 7 or 8 channels.
					
	@constant		kAudioUnitSubType_MatrixMixer
						- desktop only
					Any number of input and output buses with any number of channels on any bus. 
					The mix is presented as a matrix of channels that can be controlled through 
					input volume per channel, "cross-point" volume (a given input channel to a 
					given output channel), output volume per channel and a global volume across 
					the whole matrix

	@constant		kAudioUnitSubType_AU3DMixerEmbedded
						- iPhone only
					A scaled-down version of the AU3DMixer that presents a stereo output, mono or 
					stereo inputs
*/
enum {
	kAudioUnitSubType_MultiChannelMixer		= 'mcmx',
#if !TARGET_OS_IPHONE
	kAudioUnitSubType_StereoMixer			= 'smxr',
	kAudioUnitSubType_3DMixer				= '3dmx',
	kAudioUnitSubType_MatrixMixer			= 'mxmx'
#else
	kAudioUnitSubType_AU3DMixerEmbedded		= '3dem'
#endif
};

/*!
	@enum			Apple panner audio unit sub types 
	@discussion		These are the subtypes for the various panner units that apple ships

	@constant		kAudioUnitSubType_SphericalHeadPanner
						- desktop only
					A panner unit that uses the spherical head model to pan to a stereo output
					
	@constant		kAudioUnitSubType_VectorPanner
						- desktop only
					A panner unit that uses a moving pan between the two closes, adjacent channels 
					in a 3D space to a
					surround output
					
	@constant		kAudioUnitSubType_SoundFieldPanner
						- desktop only
					A panner unit that uses a sound-field notion to pan to a surround output
					
	@constant		kAudioUnitSubType_HRTFPanner
						- desktop only
					A panner unit that uses a generic "HRTF" model to pan to a stereo output
*/
#if !TARGET_OS_IPHONE
enum {
	kAudioUnitSubType_SphericalHeadPanner	= 'sphr',
	kAudioUnitSubType_VectorPanner			= 'vbas',
	kAudioUnitSubType_SoundFieldPanner		= 'ambi',
	kAudioUnitSubType_HRTFPanner			= 'hrtf'
};
#endif

/*!
	@enum			Apple generator audio unit sub types 
	@discussion		These are the subtypes for the various generator units that apple ships

	@constant		kAudioUnitSubType_ScheduledSoundPlayer
						- desktop only
					A generator unit that can be used to schedule slices of audio to be played at 
					a specified time. The audio is scheduled using the time stamps for the render 
					operation, and can be scheduled from any thread.
					
	@constant		kAudioUnitSubType_AudioFilePlayer
						- desktop only
					A generator unit that is used to play a file. It presents a custom UI so can 
					be used in a UI context as well
					
	@constant		kAudioUnitSubType_NetReceive
						- desktop only
					A generator unit that is paired with _NetSend to receive the audio that unit 
					sends. It presents a custom UI so can be used in a UI context as well
*/
#if !TARGET_OS_IPHONE
enum {
	kAudioUnitSubType_ScheduledSoundPlayer	= 'sspl',
	kAudioUnitSubType_AudioFilePlayer		= 'afpl',
	kAudioUnitSubType_NetReceive			= 'nrcv'
};
#endif


//================================================================================================
#pragma mark -
#pragma mark Audio Unit Constants and typedefs
/*!
	@enum			AudioUnitRenderActionFlags
	@discussion		These flags can be set in a callback from an audio unit during an audio unit 
					render operation from either the RenderNotify Proc or the render input 
					callback.

	@constant		kAudioUnitRenderAction_PreRender
					Called on a render notification Proc - which is called either before or after 
					the render operation of the audio unit. If this flag is set, the proc is being 
					called before the render operation is performed.
					
	@constant		kAudioUnitRenderAction_PostRender
					Called on a render notification Proc - which is called either before or after 
					the render operation of the audio unit. If this flag is set, the proc is being 
					called after the render operation is completed.

	@constant		kAudioUnitRenderAction_OutputIsSilence
					This flag can be set in a render input callback (or in the audio unit's render 
					operation itself) and is used to indicate that the render buffer contains only 
					silence. It can then be used by the caller as a hint to whether the buffer 
					needs to be processed or not.
					
	@constant		kAudioOfflineUnitRenderAction_Preflight
					This is used with offline audio units (of type 'auol'). It is used when an 
					offline unit is being preflighted, which is performed prior to the actual 
					offline rendering actions are performed. It is used for those cases where the 
					offline process needs it (for example, with an offline unit that normalises an 
					audio file, it needs to see all of the audio data first before it can perform 
					its normalisation)
					
	@constant		kAudioOfflineUnitRenderAction_Render
					Once an offline unit has been successfully preflighted, it is then put into 
					its render mode. So this flag is set to indicate to the audio unit that it is 
					now in that state and that it should perform its processing on the input data.
					
	@constant		kAudioOfflineUnitRenderAction_Complete
					This flag is set when an offline unit has completed either its preflight or 
					performed render operations
					
	@constant		kAudioUnitRenderAction_PostRenderError
					If this flag is set on the post-render call an error was returned by the 
					AUs render operation. In this case, the error can be retrieved through the 
					lastRenderError property and the audio data in ioData handed to the post-render 
					notification will be invalid.
	@constant		kAudioUnitRenderAction_DoNotCheckRenderArgs
					If this flag is set, then checks that are done on the arguments provided to render 
					are not performed. This can be useful to use to save computation time in
					situations where you are sure you are providing the correct arguments
					and structures to the various render calls
*/
enum
{
	kAudioUnitRenderAction_PreRender			= (1 << 2),
	kAudioUnitRenderAction_PostRender			= (1 << 3),
	kAudioUnitRenderAction_OutputIsSilence		= (1 << 4),
	kAudioOfflineUnitRenderAction_Preflight		= (1 << 5),
	kAudioOfflineUnitRenderAction_Render		= (1 << 6),
	kAudioOfflineUnitRenderAction_Complete		= (1 << 7),
	kAudioUnitRenderAction_PostRenderError		= (1 << 8),
	kAudioUnitRenderAction_DoNotCheckRenderArgs	= (1 << 9)
};
typedef UInt32							AudioUnitRenderActionFlags;

/*!
	@enum			Audio unit errors
	@discussion		These are the various errors that can be returned by AudioUnit... API calls

	@constant		kAudioUnitErr_InvalidProperty
					The property is not supported
	@constant		kAudioUnitErr_InvalidParameter
					The parameter is not supported
	@constant		kAudioUnitErr_InvalidElement
					The specified element is not valid
	@constant		kAudioUnitErr_NoConnection
					There is no connection (generally an audio unit is asked to render but it has 
					not input from which to gather data)
	@constant		kAudioUnitErr_FailedInitialization
					The audio unit is unable to be initialised
	@constant		kAudioUnitErr_TooManyFramesToProcess
					When an audio unit is initialised it has a value which specifies the max 
					number of frames it will be asked to render at any given time. If an audio 
					unit is asked to render more than this, this error is returned.
	@constant		kAudioUnitErr_InvalidFile
					If an audio unit uses external files as a data source, this error is returned 
					if a file is invalid (Apple's DLS synth returns this error)
	@constant		kAudioUnitErr_FormatNotSupported
					Returned if an input or output format is not supported
	@constant		kAudioUnitErr_Uninitialized
					Returned if an operation requires an audio unit to be initialised and it is 
					not.
	@constant		kAudioUnitErr_InvalidScope
					The specified scope is invalid
	@constant		kAudioUnitErr_PropertyNotWritable
					The property cannot be written
	@constant		kAudioUnitErr_CannotDoInCurrentContext
					Returned when an audio unit is in a state where it can't perform the requested 
					action now - but it could later. Its usually used to guard a render operation 
					when a reconfiguration of its internal state is being performed.
	@constant		kAudioUnitErr_InvalidPropertyValue
					The property is valid, but the value of the property being provided is not
	@constant		kAudioUnitErr_PropertyNotInUse
					Returned when a property is valid, but it hasn't been set to a valid value at 
					this time.	
	@constant		kAudioUnitErr_Initialized
					Indicates the operation cannot be performed because the audio unit is 
					initialized.
	@constant		kAudioUnitErr_InvalidOfflineRender
					Used to indicate that the offline render operation is invalid. For instance,
					when the audio unit needs to be pre-flighted, 
					but it hasn't been.
	@constant		kAudioUnitErr_Unauthorized
					Returned by either Open or Initialise, this error is used to indicate that the 
					audio unit is not authorised, that it cannot be used. A host can then present 
					a UI to notify the user the audio unit is not able to be used in its current 
					state.
*/
enum
{
	kAudioUnitErr_InvalidProperty			= -10879,
	kAudioUnitErr_InvalidParameter			= -10878,
	kAudioUnitErr_InvalidElement			= -10877,
	kAudioUnitErr_NoConnection				= -10876,
	kAudioUnitErr_FailedInitialization		= -10875,
	kAudioUnitErr_TooManyFramesToProcess	= -10874,
	kAudioUnitErr_InvalidFile				= -10871,
	kAudioUnitErr_FormatNotSupported		= -10868,
	kAudioUnitErr_Uninitialized				= -10867,
	kAudioUnitErr_InvalidScope				= -10866,
	kAudioUnitErr_PropertyNotWritable		= -10865,
	kAudioUnitErr_CannotDoInCurrentContext	= -10863,
	kAudioUnitErr_InvalidPropertyValue		= -10851,
	kAudioUnitErr_PropertyNotInUse			= -10850,
	kAudioUnitErr_Initialized				= -10849,
	kAudioUnitErr_InvalidOfflineRender		= -10848,
	kAudioUnitErr_Unauthorized				= -10847
};

/*!
	@typedef			AudioUnitPropertyID
	@discussion			Type used for audio unit properties. 
						Properties are used to describe the state of an audio unit (for instance, 
						the input or output audio format)
*/
typedef UInt32							AudioUnitPropertyID;
/*!
	@typedef			AudioUnitScope
	@discussion			Type used for audio unit scopes. Apple reserves the 0 < 1024 range for 
						audio unit scope identifiers.  
						Scopes are used to delineate a major attribute of an audio unit 
						(for instance, global, input, output)
*/
typedef UInt32							AudioUnitScope;
/*!
	@typedef			AudioUnitElement
	@discussion			Type used for audio unit elements.
						Scopes can have one or more member, and a member of a scope is 
						addressed / described by its element
						For instance, input bus 1 is input scope, element 1
*/
typedef UInt32							AudioUnitElement;
/*!
	@typedef			AudioUnitParameterID
	@discussion			Type used for audio unit parameters. 
						Parameters are typically used to control and set render state 
						(for instance, filter cut-off frequency)
*/
typedef UInt32							AudioUnitParameterID;
/*!
	@typedef			AudioUnitParameterValue
	@discussion			Type used for audio unit parameter values. 
						The value of a given parameter is specified using this type 
						(typically a Float32)
*/
typedef	Float32							AudioUnitParameterValue;


/*!
	@enum			AUParameterEventType
	@discussion		The type of a parameter event (see AudioUnitScheduleParameter)

	@constant		kParameterEvent_Immediate
					The parameter event describes an immediate change to the parameter value to 
					the new value
	@constant		kParameterEvent_Ramped
					The parameter event describes a change to the parameter value that should
					be applied over the specified period of time
*/
enum
{
	kParameterEvent_Immediate	= 1,
	kParameterEvent_Ramped		= 2
};
typedef UInt32							AUParameterEventType;

/*!
	@struct			AudioUnitParameterEvent
	@discussion		A parameter event describes a change to a parameter's value, where the type of 
					the event describes how that change is to be applied (see AUParameterEventType). 
					A parameter is uniquely defined through the triplet of scope, element and 
					parameterID.
					
					See AudioUnitScheduleParameters

	@field			scope	
					The scope for the parameter
	@field			element
					The element for the parameter
	@field			parameter
					The parameterID for the parameter
	
	@field			eventType
					The event type. This field further defines how the union described by 
					eventValues is to be interpreted.
	
	@field			eventValues
					If the parameter event type is _Immediate, then the immediate struct of this 
					union should be used.
					If the parameter event type is _Ramped, then the ramp struct of this union 
					should be used.
					
*/
struct AudioUnitParameterEvent
{
	AudioUnitScope			scope;
	AudioUnitElement		element;
	AudioUnitParameterID	parameter;
	
	AUParameterEventType	eventType;
	
	union
	{
		struct
		{
			SInt32						startBufferOffset;
			UInt32						durationInFrames;
			AudioUnitParameterValue		startValue;
			AudioUnitParameterValue		endValue;
		}					ramp;
		
		struct
		{
			UInt32						bufferOffset;
			AudioUnitParameterValue		value;
		}					immediate;		

	}						eventValues;
};
typedef struct AudioUnitParameterEvent	AudioUnitParameterEvent;

/*!
	@struct			AudioUnitParameter
	@discussion		An audio unit parameter is defined by the triplet of audio unit scope, element 
					and parameterID. This struct is used with the functions in AudioUnitUtilities.h 
					to deal with audio unit parameters, but is included in this header file for 
					completeness

	@field			mAudioUnit
					The audio unit instance which the specified parameter applies too
	@field			mParameterID
					The parameterID for the parameter
	@field			mScope	
					The scope for the parameter
	@field			mElement
					The element for the parameter
*/
struct AudioUnitParameter
{
	AudioUnit				mAudioUnit;
	AudioUnitParameterID	mParameterID;
	AudioUnitScope			mScope;
	AudioUnitElement		mElement;
};
typedef struct AudioUnitParameter	AudioUnitParameter;

/*!
	@struct			AudioUnitProperty
	@discussion		An audio unit property is defined by the triplet of audio unit scope, element
					and propertyID. This struct is used with the functions in AudioUnitUtilities.h 
					to deal with audio unit properties, but is included in this header file for 
					completeness

	@field			mAudioUnit
					The audio unit instance which the specified property applies too
	@field			mPropertyID
					The propertyID for the property
	@field			mScope	
					The scope for the property
	@field			mElement
					The element for the property
*/
struct AudioUnitProperty
{
	AudioUnit				mAudioUnit;
	AudioUnitPropertyID		mPropertyID;
	AudioUnitScope			mScope;
	AudioUnitElement		mElement;
};
typedef struct AudioUnitProperty	AudioUnitProperty;


/*!
	@typedef		AURenderCallback
	@discussion		This is the prototype for a function callback Proc that is used both with the 
					AudioUnit render notification API and the render input callback. See 
					kAudioUnitProperty_SetRenderCallback property or AudioUnitAddRenderNotify.
					This callback is part of the process of a call to AudioUnitRender. As a 
					notification it is called either before or after the audio unit's render 
					operations. As a render input callback, it is called to provide input data for
					the particular input bus the callback is attached too.
	
	@param			inRefCon
					The client data that is provided either with the AURenderCallbackStruct or as 
					specified with the Add API call
	@param			ioActionFlags
					Flags used to describe more about the context of this call (pre or post in the 
					notify case for instance) 
	@param			inTimeStamp
					The times stamp associated with this call of audio unit render
	@param			inBusNumber
					The bus number associated with this call of audio unit render
	@param			inNumberFrames
					The number of sample frames that will be represented in the audio data in the 
					provided ioData parameter
	@param			ioData
					The AudioBufferList that will be used to contain the rendered or provided 
					audio data. These buffers will be aligned to 16 byte boundaries (which is 
					normally what malloc will return).
*/
typedef OSStatus
(*AURenderCallback)(	void *							inRefCon,
						AudioUnitRenderActionFlags *	ioActionFlags,
						const AudioTimeStamp *			inTimeStamp,
						UInt32							inBusNumber,
						UInt32							inNumberFrames,
						AudioBufferList *				ioData);

/*!
	@typedef		AudioUnitPropertyListenerProc
	@discussion		This is the prototype for a function callback Proc that is registered with an 
					audio unit to notify the caller of any changes to a value of an audio unit 
					property. See AudioUnitAddPropertyListener
	
	@param			inRefCon
					The client data that is provided with the add property listener registration
	@param			inUnit
					The audio unit upon which the specified property value has changed
	@param			inID
					The property whose value has changed
	@param			inScope
					The scope of the property whose value has changed
	@param			inElement
					The element ID on the scope of the property whose value has changed
*/
typedef void
(*AudioUnitPropertyListenerProc)(	void *				inRefCon,
									AudioUnit			inUnit,
									AudioUnitPropertyID	inID,
									AudioUnitScope		inScope,
									AudioUnitElement	inElement);

/*!
	@typedef		AUInputSamplesInOutputCallback
	@discussion		This is the prototype for a function callback Proc that is registered with an 
					audio unit to notify the caller of for the user of a varispeed or AUTimePitch 
					audio unit where it is not clear what input sample is represented in the 
					rendered output samples.
	
	@param			inRefCon
					The client data that is provided with the add property listener registration
	@param			inOutputTimeStamp
					The time stamp that corresponds to the first sample of audio data produced in 
					AudioUnitRender (its output data)
	@param			inInputSample
					The sample number of the input that is represented in the first sample of that 
					output time stamp
	@param			inNumberInputSamples
					The number of input samples that are represented in an output buffer
*/
typedef void
(*AUInputSamplesInOutputCallback)(	void *						inRefCon,
									const AudioTimeStamp *		inOutputTimeStamp,
									Float64						inInputSample,
									Float64						inNumberInputSamples);

//================================================================================================
#pragma mark -
#pragma mark Functions

/*!
	@function		AudioUnitInitialize
	@abstract		initialize an audio unit
	@discussion		Upon success, the audio unit has been successfully initialised. This means 
					that the formats for input and output are valid and can be supported and it 
					has based its allocations on the max number of frames that it is able to 
					render at any given time. Once initialised, it is in a state where it can be 
					asked to render.
					
					In common practice major state of an audio unit (such as its I/O formats, 
					memory allocations) cannot be changed while an audio unit is inialized.
	
	@param			inUnit
					The audio unit to initialise
	@result			noErr, or an error representing the reasons why the audio unit was not able 
					to be initialised successfully
*/
extern OSStatus
AudioUnitInitialize(				AudioUnit				inUnit)						
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
	@function		AudioUnitUninitialize
	@abstract		uninitialize and audio unit
	@discussion		Once an audio unit has been initialised, to change its state in response to 
					some kind of environmental change, the audio unit should be uninitialised. 
					This will have the effect of the audio unit de-allocating its resources.
					The caller can then reconfigure the audio unit to match the new environment 
					(for instance, the sample rate to process audio is different than it was) and 
					then re-initialise the audio unit when those changes have been applied.
	
	@param			inUnit
					The audio unit to uninitialise
	@result			noErr, or an error representing the reasons why the audio unit was not able 
					to be initialised successfully. Typically this call won't return an error 
					unless the audio unit in question is no longer valid.
*/
extern OSStatus
AudioUnitUninitialize(				AudioUnit				inUnit)						
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);


/*!
	@function		AudioUnitGetPropertyInfo
	@abstract		retrieves information about a specified property
	@discussion		The API can be used to retrieve both the size of the property, and whether it 
					is writable or not. In order to get a general answer on the capability of an 
					audio unit, this function should be called before the audio unit
					is initialized (as some properties are writable when the audio unit is 
					initialized, and others not)

	@param			inUnit
					the audio unit
	@param			inID
					the property identifier
	@param			inScope
					the scope of the property
	@param			inElement
					the element of the scope
	@param			outDataSize
					if not null, then will retrieve the maximum size for the property. if null, 
					then it is ignored
	@param			outWritable	
					if not null, then will retrieve whether the property can be written or not. 
					if null, then it is ignored
	
	@result			noErr, or various audio unit errors related to properties
*/
extern OSStatus
AudioUnitGetPropertyInfo(			AudioUnit				inUnit,
									AudioUnitPropertyID 	inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									UInt32 *				outDataSize,
									Boolean *				outWritable)			
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
	@function		AudioUnitGetProperty
	@abstract		retrieves the value of a specified property
	@discussion		The API can is used to retrieve the value of the property. Property values for 
					audio units are always passed by reference
					
	@param			inUnit
					the audio unit
	@param			inID
					the property identifier
	@param			inScope
					the scope of the property
	@param			inElement
					the element of the scope
	@param			outData
					used to retrieve the value of the property. It should point to memory at least 
					as large as the value
					described by ioDataSize 
	@param			ioDataSize	
					on input contains the size of the data pointed to by outData, on output, the 
					size of the data that was returned.

	@result			noErr, or various audio unit errors related to properties
*/
extern OSStatus
AudioUnitGetProperty(				AudioUnit				inUnit,
									AudioUnitPropertyID		inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									void *					outData,
									UInt32 *				ioDataSize)				
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
	@function		AudioUnitSetProperty
	@abstract		sets the value of a specified property
	@discussion		The API can is used to set the value of the property. Property values for 
					audio units are always passed by reference
					
	@param			inUnit
					the audio unit
	@param			inID
					the property identifier
	@param			inScope
					the scope of the property
	@param			inElement
					the element of the scope
	@param			inData
					if not null, then is the new value for the property that will be set. If null, 
					then inDataSize should be zero, and the call is then used to remove a 
					previously set value for a property. This removal is only valid for
					some properties, as most properties will always have a default value if not 
					set.
	@param			inDataSize	
					the size of the data being provided in inData

	@result			noErr, or various audio unit errors related to properties
*/
extern OSStatus
AudioUnitSetProperty(				AudioUnit				inUnit,
									AudioUnitPropertyID		inID,
									AudioUnitScope			inScope,
									AudioUnitElement		inElement,
									const void *			inData,
									UInt32					inDataSize)				
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
	@function		AudioUnitAddPropertyListener
	@abstract		registration call to receive notifications for when a property changes
	@discussion		When an audio unit property value changes, a notification callback can be 
					called by the audio unit to  inform interested parties that this event has 
					occurred. The notification is defined by the tuple of inProc and 
					inProcUserData as paired to the specified property ID, so the previously 
					defined AudioUnitRemovePropertyListener is deprecated because it didn't allow 
					for the provision of the inProcUserData to remove a given listener (so, 
					you should use AudioUnitRemovePropertyListenerWithUserData).
					
	@param			inUnit
					the audio unit
	@param			inID
					the property identifier
	@param			inProc
					the procedure to call when the property changes (on any scope or element)
	@param			inProcUserData
					the user data to provide with the callback

	@result			noErr, or various audio unit errors related to properties
*/
extern OSStatus
AudioUnitAddPropertyListener(		AudioUnit						inUnit,
									AudioUnitPropertyID				inID,
									AudioUnitPropertyListenerProc	inProc,
									void *							inProcUserData)   
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
	@function		AudioUnitRemovePropertyListenerWithUserData
	@abstract		remove a previously registered property listener
	@discussion		Removes a previously registered property listener as specified by the inProc 
					and inProcUser data as paired to the property identifier
					
	@param			inUnit
					the audio unit
	@param			inID
					the property identifier
	@param			inProc
					the procedure previously registered
	@param			inProcUserData
					the user data paired with the provided inProc

	@result			noErr, or various audio unit errors related to properties
*/
extern OSStatus
AudioUnitRemovePropertyListenerWithUserData(
									AudioUnit						inUnit,
									AudioUnitPropertyID				inID,
									AudioUnitPropertyListenerProc	inProc,
									void *							inProcUserData)	
												__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_2_0);

/*!
	@function		AudioUnitAddRenderNotify
	@abstract		a notification callback to call when an audio unit is asked to render
	@discussion		allows an application to register a callback with an audio unit for whenever 
					the audio unit is asked to render. The callback is called both before the 
					audio unit performs its render operations (the render flag's pre-render bit 
					is set) and after the audio unit has completed its render operations (the 
					render flag's post-render bit is set). On post-render, the audio buffer list 
					(ioData) will contain valid audio data that was rendered by the audio unit.
					
					The inProc and inProcUserData are treated as a tuple entity, so when wanting 
					to remove one, both the inProc and its inProcUserData must be specified
					
	@param			inUnit
					the audio unit
	@param			inProc
					an AURenderCallback proc
	@param			inProcUserData
					the user data that will be provided with the proc when it is called

	@result			noErr, or an audio unit error code
*/
extern OSStatus
AudioUnitAddRenderNotify(			AudioUnit				inUnit,
									AURenderCallback		inProc,
									void *					inProcUserData)			
												__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

/*!
	@function		AudioUnitRemoveRenderNotify
	@abstract		remove a previously registered render notification proc
	
	@param			inUnit
					the audio unit
	@param			inProc
					an AURenderCallback proc
	@param			inProcUserData
					the user data that was provided with the proc when it was previously 
					registered

	@result			noErr, or an audio unit error code
*/
extern OSStatus
AudioUnitRemoveRenderNotify(		AudioUnit				inUnit,
									AURenderCallback		inProc,
									void *					inProcUserData)			
												__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

/*!
	@function		AudioUnitGetParameter
	@abstract		Get the value of a parameter
	@discussion		Get the value of a parameter as specified by its ID, scope and element. 
	
	@param			inUnit
					the audio unit
	@param			inID
					the parameter ID
	@param			inScope
					the scope for the parameter
	@param			inElement
					the element on the scope for the parameter
	@param			outValue
					Must be non-null, and upon success will contain the current value for the 
					specified parameter
	
	@result			noErr, or an audio unit error code (such as InvalidParameter)
*/
extern OSStatus
AudioUnitGetParameter(				AudioUnit					inUnit,
									AudioUnitParameterID		inID,
									AudioUnitScope				inScope,
									AudioUnitElement			inElement,
									AudioUnitParameterValue *	outValue)			
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
	@function		AudioUnitSetParameter
	@abstract		Set the value of a parameter
	@discussion		Set the value of a parameter as specified by its ID, scope and element. 
					Parameter IDs are consistent across all of the elements in a scope - so for a 
					mixer, the "input volume" parameter can be applied on any input, and the 
					particular input is specified by the elementID.
	
	@param			inUnit
					the audio unit
	@param			inID
					the parameter ID
	@param			inScope
					the scope for the parameter
	@param			inElement
					the element on the scope for the parameter
	@param			inValue
					the new value for the parameter.
	@param			inBufferOffsetInFrames
					generally should be set to zero - see AudioUnitScheduleParameters
	
	@result			noErr, or an audio unit error code (such as InvalidParameter)
*/
extern OSStatus
AudioUnitSetParameter(				AudioUnit					inUnit,
									AudioUnitParameterID		inID,
									AudioUnitScope				inScope,
									AudioUnitElement			inElement,
									AudioUnitParameterValue		inValue,
									UInt32						inBufferOffsetInFrames) 
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);

/*!
	@function		AudioUnitScheduleParameters
	@abstract		Schedule changes to the value of a parameter
	@discussion		This API is used to schedule intra-buffer changes to the value of a parameter 
					(immediate) or to ramp a parameter from a start value to an end value for a 
					specified number of samples (ramp)
					
					The API allows for the scheduling of multiple parameter events with the one 
					call. All of the parameter events must apply to the current (and only apply to 
					the current) audio unit render call, so the events are scheduled as a part of 
					the pre-render notification callback.
					
					When scheduling an immediate parameter event, the new value at the specified 
					sample buffer offset is provided
					
					When scheduling a ramped parameter, the ramp is scheduled each audio unit 
					render for the duration of the ramp. Each schedule of the the new audio unit 
					render specifies the progress of the ramp.
					
					Parameters that can have events scheduled to them will indicate this through 
					their parameter info struct
					
	@param			inUnit
					the audio unit
	@param			inParameterEvent
					a pointer to an array of parameter event structs
	@param			inNumParamEvents
					the number of parameter event structs pointed to by inParameterEvent
	
	@result			noErr, or an audio unit error code (such as InvalidParameter)
*/
extern OSStatus
AudioUnitScheduleParameters(		AudioUnit						inUnit,
									const AudioUnitParameterEvent *	inParameterEvent,
									UInt32							inNumParamEvents) 
												__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

/*!
	@function		AudioUnitRender
	@abstract		the render operation where ioData will contain the results of the audio unit's
					render operations
	@discussion		an audio unit will render the amount of audio data described by 
					inNumberOfFrames and the results of that render will be contained within 
					ioData. The caller should provide audio time stamps where at least the sample 
					time is valid and it is incrementing sequentially from its previous call 
					(so, the next time stamp will be the current time stamp + inNumberFrames) 
					If the sample time is not incrementing sequentially, the audio unit will infer
					that there is some discontinuity with the timeline it is rendering for
	
					The caller must provide a valid ioData AudioBufferList that matches the 
					expected topology for the current audio format for the given bus. The buffer 
					list can be of two variants:
					(1) If the mData pointers are non-null then the audio unit will render its 
					output into those buffers. These buffers should be aligned to 16 byte 
					boundaries (which is normally what malloc will return).
					(2) If the mData pointers are null, then the audio unit can provide pointers 
					to its own buffers. In this case the audio unit is required to keep those
					buffers valid for the duration of the calling thread's I/O cycle
					 
	@param			inUnit
					the audio unit
	@param			ioActionFlags
					any appropriate action flags for the render operation
	@param			inTimeStamp
					the time stamp that applies to this particular render operation. when 
					rendering for multiple output buses the time stamp will generally be the same 
					for each output bus, so the audio unit is able to determine without doubt that 
					this the same render operation
	@param			inOutputBusNumber
					the output bus to render for
	@param			inNumberFrames
					the number of sample frames to render
	@param			ioData
					the audio buffer list that the audio unit is to render into.
	
	@result			noErr, or an audio unit render error
*/
extern OSStatus
AudioUnitRender(					AudioUnit						inUnit,
									AudioUnitRenderActionFlags *	ioActionFlags,
									const AudioTimeStamp *			inTimeStamp,
									UInt32							inOutputBusNumber,
									UInt32							inNumberFrames,
									AudioBufferList *				ioData)			
												__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

extern OSStatus
AudioUnitProcess (					AudioUnit						inUnit, 
									AudioUnitRenderActionFlags *	ioActionFlags, 
									const AudioTimeStamp *			inTimeStamp, 
									UInt32							inNumberFrames, 
									AudioBufferList *				ioData)
												__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_NA);

extern OSStatus
AudioUnitProcessMultiple(			AudioUnit						inUnit, 
									AudioUnitRenderActionFlags *	ioActionFlags, 
									const AudioTimeStamp *			inTimeStamp, 
									UInt32							inNumberFrames,
									UInt32							inNumberInputBufferLists,
									const AudioBufferList **		inInputBufferLists,
									UInt32							inNumberOutputBufferLists,
									AudioBufferList **				ioOutputBufferLists)
												__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_NA);
	
/*!
	@function		AudioUnitReset
	@abstract		reset an audio unit's render state
	@discussion		This call will clear any render state of an audio unit. For instance, with a 
					delay or reverb type of audio unit reset will clear any of the delay lines 
					maintained within the audio unit. Typically, this call is made when an
					audio unit was previously rendering, and was taken out of the render chain 
					(say, the track it is in was muted) and is being added back in (unmuted). 
					The host should reset the audio unit before adding it back so that it doesn't 
					produce audio from its delay lines that is no longer valid.
					
					The call should only clear memory, it should NOT allocate or free memory 
					resources (this is done in the Initialize calls).
	
	@param			inUnit
					the audio unit
	@param			inScope
					the scope - typically this is set to GlobalScope
	@param			inElement
					the element - typically this is set to 0
	
	@result			noErr, or an audio unit error
*/
extern OSStatus
AudioUnitReset(						AudioUnit			inUnit,
									AudioUnitScope		inScope,
									AudioUnitElement	inElement)					
												__OSX_AVAILABLE_STARTING(__MAC_10_0,__IPHONE_2_0);


/*!
	@enum			AudioUnitRange
	@discussion		the range of selectors that are used to dispatch through to the various audio 
					unit API

	@constant		kAudioUnitRange
	@constant		kAudioUnitInitializeSelect
	@constant		kAudioUnitUninitializeSelect
	@constant		kAudioUnitGetPropertyInfoSelect
	@constant		kAudioUnitGetPropertySelect
	@constant		kAudioUnitSetPropertySelect
	@constant		kAudioUnitAddPropertyListenerSelect
	@constant		kAudioUnitRemovePropertyListenerSelect
	@constant		kAudioUnitRemovePropertyListenerWithUserDataSelect
	@constant		kAudioUnitAddRenderNotifySelect
	@constant		kAudioUnitRemoveRenderNotifySelect
	@constant		kAudioUnitGetParameterSelect
	@constant		kAudioUnitSetParameterSelect
	@constant		kAudioUnitScheduleParametersSelect
	@constant		kAudioUnitRenderSelect
	@constant		kAudioUnitResetSelect
	@constant		kAudioUnitComplexRenderSelect
	@constant		kAudioUnitProcessSelect
	@constant		kAudioUnitProcessMultipleSelect
*/
enum
{
	kAudioUnitRange							= 0x0000,	// range of selectors for audio units
	kAudioUnitInitializeSelect				= 0x0001,
	kAudioUnitUninitializeSelect			= 0x0002,
	kAudioUnitGetPropertyInfoSelect			= 0x0003,
	kAudioUnitGetPropertySelect				= 0x0004,
	kAudioUnitSetPropertySelect				= 0x0005,
	kAudioUnitAddPropertyListenerSelect		= 0x000A,
	kAudioUnitRemovePropertyListenerSelect	= 0x000B,
	kAudioUnitRemovePropertyListenerWithUserDataSelect = 0x0012,
	kAudioUnitAddRenderNotifySelect			= 0x000F,
	kAudioUnitRemoveRenderNotifySelect		= 0x0010,
	kAudioUnitGetParameterSelect			= 0x0006,
	kAudioUnitSetParameterSelect			= 0x0007,
	kAudioUnitScheduleParametersSelect		= 0x0011,
	kAudioUnitRenderSelect					= 0x000E,
	kAudioUnitResetSelect					= 0x0009,
	kAudioUnitComplexRenderSelect			= 0x0013,
	kAudioUnitProcessSelect					= 0x0014,
	kAudioUnitProcessMultipleSelect			= 0x0015
};

//================================================================================================
#pragma mark -
#pragma mark Dispatch function prototypes

typedef OSStatus	
(*AudioUnitInitializeProc) (void *self);

typedef OSStatus	
(*AudioUnitUninitializeProc) (void *self);

typedef OSStatus	
(*AudioUnitGetPropertyInfoProc) (void *self, AudioUnitPropertyID prop, AudioUnitScope scope, 
									AudioUnitElement elem, UInt32 *outDataSize, Boolean *outWritable);

typedef OSStatus	
(*AudioUnitGetPropertyProc) (void *self, AudioUnitPropertyID inID, AudioUnitScope inScope, 
									AudioUnitElement inElement, void *outData, UInt32 *ioDataSize);

typedef OSStatus	
(*AudioUnitSetPropertyProc) (void *self, AudioUnitPropertyID inID, AudioUnitScope inScope, 
									AudioUnitElement inElement, const void *inData, UInt32 inDataSize);

typedef OSStatus	
(*AudioUnitAddPropertyListenerProc) (void *self, AudioUnitPropertyID prop, 
									AudioUnitPropertyListenerProc proc, void *userData);

typedef OSStatus	
(*AudioUnitRemovePropertyListenerProc) (void *self, AudioUnitPropertyID prop, 
									AudioUnitPropertyListenerProc proc);

typedef OSStatus	
(*AudioUnitRemovePropertyListenerWithUserDataProc) (void *self, AudioUnitPropertyID prop, 
									AudioUnitPropertyListenerProc proc, void *userData);

typedef OSStatus	
(*AudioUnitAddRenderNotifyProc) (void *self, AURenderCallback proc, void *userData);

typedef OSStatus	
(*AudioUnitRemoveRenderNotifyProc) (void *self, AURenderCallback proc, void *userData);

typedef OSStatus	
(*AudioUnitScheduleParametersProc) (void *self, const AudioUnitParameterEvent *events, UInt32 numEvents);

typedef OSStatus	
(*AudioUnitResetProc) (void *self, AudioUnitScope		inScope, AudioUnitElement	inElement);

typedef OSStatus	
(*AudioUnitComplexRenderProc) (void *self, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, 
									UInt32 inOutputBusNumber, UInt32 inNumberOfPackets, UInt32 *outNumberOfPackets, 
									AudioStreamPacketDescription *outPacketDescriptions, AudioBufferList *ioData, 
									void *outMetadata, UInt32 *outMetadataByteSize);

typedef OSStatus	
(*AudioUnitProcessProc) (void *self, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, 
									UInt32 inNumberFrames, AudioBufferList *ioData);

typedef OSStatus	
(*AudioUnitProcessMultipleProc) (void *self, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, 
									UInt32 inNumberFrames, UInt32 inNumberInputBufferLists, const AudioBufferList **inInputBufferLists,
									UInt32 inNumberOutputBufferLists, AudioBufferList **ioOutputBufferLists);
	


/*!
	@typedef		AudioUnitGetParameterProc
	@discussion		This proc can be exported through the FastDispatch property. A host can
					then retrieve this Proc using that property and thus make a direct
					call into your audio unit bypassing the component dispatch glue which
					can add considerable overhead and is desirable to avoid.
					
					The arguments are the same as are provided to the corresponding API call
	
	@param			inComponentStorage
					For a component manager component, this is the component instance storage 
					pointer
	@param			inID
	@param			inScope
	@param			inElement
	@param			outValue
*/
typedef OSStatus
(*AudioUnitGetParameterProc)(	void *						inComponentStorage,
								AudioUnitParameterID		inID,
								AudioUnitScope				inScope,
								AudioUnitElement			inElement,
								AudioUnitParameterValue *	outValue);
								
/*!
	@typedef		AudioUnitSetParameterProc
	@discussion		This proc can be exported through the FastDispatch property. A host can
					then retrieve this Proc using that property and thus make a direct
					call into your audio unit bypassing the component dispatch glue which
					can add considerable overhead and is desirable to avoid.
					
					The arguments are the same as are provided to the corresponding API call
	
	@param			inComponentStorage
					For a component manager component, this is the component instance storage 
					pointer
	@param			inID
	@param			inScope
	@param			inElement
	@param			inValue
	@param			inBufferOffsetInFrames
*/
typedef OSStatus
(*AudioUnitSetParameterProc)(	void *						inComponentStorage,
								AudioUnitParameterID		inID,
								AudioUnitScope				inScope,
								AudioUnitElement			inElement,
								AudioUnitParameterValue		inValue,
								UInt32						inBufferOffsetInFrames);
								
/*!
	@typedef		AudioUnitRenderProc
	@discussion		This proc can be exported through the FastDispatch property. A host can
					then retrieve this Proc using that property and thus make a direct
					call into your audio unit bypassing the component dispatch glue which
					can add considerable overhead and is desirable to avoid.
					
					The arguments are the same as are provided to the corresponding API call
	
	@param			inComponentStorage
					For a component manager component, this is the component instance storage 
					pointer
	@param			ioActionFlags
	@param			inTimeStamp
	@param			inOutputBusNumber
	@param			inNumberFrames
	@param			ioData
*/
typedef OSStatus
(*AudioUnitRenderProc)(			void *							inComponentStorage,
								AudioUnitRenderActionFlags *	ioActionFlags,
								const AudioTimeStamp *			inTimeStamp,
								UInt32							inOutputBusNumber,
								UInt32							inNumberFrames,
								AudioBufferList *				ioData);



//================================================================================================
#pragma mark -
#pragma mark Deprecated
/*!
	@enum			deprecated - Audio unit errors
	@discussion		These are the various errors that can be returned by AudioUnit... API calls

	@constant		kAudioUnitErr_IllegalInstrument
					Apple's DLS synth returns this error if information about a particular 
					instrument patch is requested, but is not valid.
	@constant		kAudioUnitErr_InstrumentTypeNotFound
					Apple's DLS synth returns this error if information about a particular 
					instrument patch is requested, but is not valid.
	@constant		kAudioUnitErr_UnknownFileType
					If an audio unit uses external files as a data source, this error is returned
					if a file is invalid (Apple's DLS synth returns this error)
	@constant		kAudioUnitErr_FileNotSpecified
					If an audio unit uses external files as a data source, this error is returned
					if a file hasn't been set on it 
					(Apple's DLS synth returns this error)
*/
enum {
	kAudioUnitErr_IllegalInstrument			= -10873,
	kAudioUnitErr_InstrumentTypeNotFound	= -10872,
	kAudioUnitErr_UnknownFileType			= -10870,
	kAudioUnitErr_FileNotSpecified			= -10869
};

#if !__LP64__ && !TARGET_OS_IPHONE
// this call is deprecated and replaced by AudioUnitRemovePropertyListenerWithUserData
// this allows apps to use the same function pointer more than once
// you provide the same function ptr and user data as provided when you add a property listener
extern OSStatus
AudioUnitRemovePropertyListener(	AudioUnit						inUnit,
									AudioUnitPropertyID				inID,
									AudioUnitPropertyListenerProc	inProc)			
				__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);
#endif


#if !__LP64__
	#if PRAGMA_STRUCT_ALIGN
		#pragma options align=reset
	#elif PRAGMA_STRUCT_PACKPUSH
		#pragma pack(pop)
	#elif PRAGMA_STRUCT_PACK
		#pragma pack()
	#endif
#endif

#ifdef PRAGMA_IMPORT_OFF
#pragma import off
#elif PRAGMA_IMPORT
#pragma import reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AUCOMPONENT__ */


/*!
	@file		AudioUnit.h
 	@framework	AudioUnit.framework
 	@copyright	(c) 2002-2015 Apple, Inc. All rights reserved.

	@brief		Umbrella header for AudioUnit framework.
*/

#ifndef _AudioUnit_AudioUnit_h
#define _AudioUnit_AudioUnit_h

#include <TargetConditionals.h>
#define AUDIO_UNIT_VERSION 1070

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AudioComponent.h>
	#include <AudioUnit/AUComponent.h>
	#include <AudioUnit/AudioOutputUnit.h>
	#include <AudioUnit/AudioUnitProperties.h>
	#include <AudioUnit/AudioUnitParameters.h>
	#include <AudioUnit/MusicDevice.h>

	#if __OBJC2__
		#import <AudioUnit/AUAudioUnit.h>
		#import <AudioUnit/AUAudioUnitImplementation.h>
		#import <AudioUnit/AUParameters.h>
	#endif

		#include <AudioUnit/AudioCodec.h>
		#include <AudioUnit/AUCocoaUIView.h>

#else
	#include <AudioComponent.h>
	#include <AUComponent.h>
	#include <AudioOutputUnit.h>
	#include <AudioUnitProperties.h>
	#include <AudioUnitParameters.h>
	#include <AudioCodec.h>
	#include <MusicDevice.h>
#endif

/*!	@mainpage

	@section section_intro			Introduction

	The AudioUnit framework contains a set of related API's dealing with:
	
	- Audio components, providing various types of plug-in functionality.
	- Audio Units, audio processing plug-ins.
	- Audio codecs, plug-ins which decode and encode compressed audio.
	
	@section section_component		Audio Components
	
	See AudioComponent.h for API's to find and use audio components, as well as information
	on how audio components are packaged and built.
	
	In addition, `<AVFoundation/AVAudioUnitComponent.h>` provides a higher-level interface for
	finding audio unit components.
	
	See @ref AUExtensionPackaging and AUAudioUnitImplementation.h for information on creating
	version 3 audio units.
	
	@section section_audiounit		Audio Units
*/

#endif /* _AudioUnit_AudioUnit_h */


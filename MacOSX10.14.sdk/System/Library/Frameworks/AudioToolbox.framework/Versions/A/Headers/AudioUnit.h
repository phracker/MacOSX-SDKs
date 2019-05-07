/*!
	@file		AudioUnit.h
 	@framework	AudioToolbox.framework
 	@copyright	(c) 2002-2015 Apple, Inc. All rights reserved.

	@brief		Former umbrella header for AudioUnit framework; now part of AudioToolbox.
*/

#ifndef _AudioToolbox_AudioUnit_h
#define _AudioToolbox_AudioUnit_h

#include <TargetConditionals.h>
#define AUDIO_UNIT_VERSION 1070

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioToolbox/AudioComponent.h>
	#include <AudioToolbox/AUComponent.h>
	#include <AudioToolbox/AudioOutputUnit.h>
	#include <AudioToolbox/AudioUnitProperties.h>
	#include <AudioToolbox/AudioUnitParameters.h>
	#include <AudioToolbox/MusicDevice.h>

	#ifdef __OBJC2__
		#import <AudioToolbox/AUAudioUnit.h>
		#import <AudioToolbox/AUAudioUnitImplementation.h>
		#import <AudioToolbox/AUParameters.h>
	#endif

		#include <AudioToolbox/AudioCodec.h>

#else
	#include <AudioComponent.h>
	#include <AUComponent.h>
	#include <AudioOutputUnit.h>
	#include <AudioUnitProperties.h>
	#include <AudioUnitParameters.h>
	#include <AudioCodec.h>
	#include <MusicDevice.h>
#endif

#endif /* _AudioToolbox_AudioUnit_h */

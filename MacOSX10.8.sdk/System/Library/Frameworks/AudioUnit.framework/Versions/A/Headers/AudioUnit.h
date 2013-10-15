/*
     File:      AudioUnit/AudioUnit.h
 
     Contains:  Umbrella include for AudioUnit definitions
 
     Copyright: (c) 2002-2008 by Apple, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/

#ifndef __AUDIOUNIT__
#define __AUDIOUNIT__

#include <TargetConditionals.h>
#define AUDIO_UNIT_VERSION 1070

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AudioComponent.h>
	#include <AudioUnit/AUComponent.h>
	#include <AudioUnit/AudioOutputUnit.h>
	#include <AudioUnit/AudioUnitProperties.h>
	#include <AudioUnit/AudioUnitParameters.h>
	#include <AudioUnit/MusicDevice.h>

	#if !TARGET_OS_IPHONE	
		#include <AudioUnit/AudioCodec.h>
	#endif

#else
	#include <AudioComponent.h>
	#include <AUComponent.h>
	#include <AudioOutputUnit.h>
	#include <AudioUnitProperties.h>
	#include <AudioUnitParameters.h>
	#include <AudioCodec.h>
	#include <MusicDevice.h>

#endif

#endif /* __AUDIOUNIT__ */


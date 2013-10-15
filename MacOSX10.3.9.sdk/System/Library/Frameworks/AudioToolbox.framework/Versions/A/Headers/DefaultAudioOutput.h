/*=============================================================================
	DefaultAudioOutput.h
	
	Public interface to the default audio output AudioUnit.
	
	Copyright (c) 2000 Apple Computer, Inc.  All Rights Reserved
=============================================================================*/

#ifndef __DefaultAudioOutput_h__
#define __DefaultAudioOutput_h__

#include <AvailabilityMacros.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AudioUnit.h>
#else
	#include <AudioUnit.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Open an instance of the default audio output unit (it can be closed with CloseComponent).
extern OSStatus	OpenDefaultAudioOutput(AudioUnit *outUnit)		AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;

extern OSStatus	OpenSystemSoundAudioOutput(AudioUnit *outUnit)	AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER DEPRECATED_IN_MAC_OS_X_VERSION_10_3_AND_LATER;
				// for system sounds like alerts, modems, etc.

#ifdef __cplusplus
}
#endif

#endif // __DefaultAudioOutput_h__

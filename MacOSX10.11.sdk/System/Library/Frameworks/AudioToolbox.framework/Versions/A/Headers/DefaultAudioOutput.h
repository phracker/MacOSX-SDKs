/*!
	@file		DefaultAudioOutput.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2000-2015 by Apple, Inc., all rights reserved.
	@abstract	Deprecated.
*/

#ifndef AudioToolbox_DefaultAudioOutput_h
#define AudioToolbox_DefaultAudioOutput_h

#if !__LP64__

#include <Availability.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AudioUnit.h>
#else
	#include <AudioUnit.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Open an instance of the default audio output unit (it can be closed with CloseComponent).
extern OSStatus	OpenDefaultAudioOutput(AudioUnit *outUnit)		__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0,__MAC_10_3, __IPHONE_NA, __IPHONE_NA);

extern OSStatus	OpenSystemSoundAudioOutput(AudioUnit *outUnit)	__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_1,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);
				// for system sounds like alerts, modems, etc.

#ifdef __cplusplus
}
#endif

#endif // !__LP64__

#endif // AudioToolbox_DefaultAudioOutput_h

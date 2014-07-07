/*=============================================================================
	DefaultAudioOutput.h
	
	Public interface to the default audio output AudioUnit.
	
	Copyright (c) 2000 Apple Computer, Inc.  All Rights Reserved
=============================================================================*/

#ifndef __DefaultAudioOutput_h__
#define __DefaultAudioOutput_h__

#include <AudioUnit/AudioOutputUnit.h>

// open an instance of a default audio output unit (it can be closed with CloseComponent)
#ifdef __cplusplus
extern "C" {
#endif

extern OSStatus	OpenDefaultAudioOutput(AudioUnit *outUnit);

extern OSStatus	OpenSystemSoundAudioOutput(AudioUnit *outUnit);
				// for system sounds like alerts, modems, etc.

#ifdef __cplusplus
}
#endif

#endif // __DefaultAudioOutput_h__

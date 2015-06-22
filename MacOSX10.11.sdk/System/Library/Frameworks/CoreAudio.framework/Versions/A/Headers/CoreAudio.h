/*==================================================================================================
     File:       CoreAudio/CoreAudio.h

     Contains:   umbrella header for the CoreAudio APIs

     Copyright:  (c) 1985-2010 by Apple, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

==================================================================================================*/
#if !defined(CoreAudio_CoreAudio_h)
#define CoreAudio_CoreAudio_h

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreAudio/CoreAudioTypes.h>
	#include <CoreAudio/AudioHardware.h>
	#include <CoreAudio/HostTime.h>
#else
	#include <CoreAudioTypes.h>
	#include <AudioHardware.h>
	#include <HostTime.h>
#endif

#endif

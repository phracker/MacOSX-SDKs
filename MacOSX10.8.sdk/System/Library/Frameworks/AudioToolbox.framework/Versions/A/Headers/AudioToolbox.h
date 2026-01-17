/*
     File:       AudioToolbox/AudioToolbox.h
 
     Contains:  Umbrella include for AudioToolbox headers.
				Also includes CAShow that allows you to print
				internal state of an object.
  
     Copyright:  (c) 2002 - 2008 by Apple, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#define AUDIO_TOOLBOX_VERSION 1060

#include <Availability.h>
#include <TargetConditionals.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioToolbox/AudioFile.h>
	#include <AudioToolbox/AudioFileStream.h>
	#include <AudioToolbox/AudioFormat.h>
	#include <AudioToolbox/AudioQueue.h>
	#include <AudioToolbox/AudioServices.h>
	#include <AudioToolbox/AUGraph.h>
	#include <AudioToolbox/AudioConverter.h>
	#include <AudioToolbox/ExtendedAudioFile.h>
	#include <AudioToolbox/MusicPlayer.h>
	#include <AudioToolbox/CAFFile.h>
	#if !TARGET_OS_IPHONE
		#include <AudioToolbox/AudioFileComponent.h>
		#include <AudioToolbox/AudioUnitUtilities.h>
		#include <AudioToolbox/AUMIDIController.h>
		#include <AudioToolbox/CoreAudioClock.h>
	#endif
#else
	#include <AudioConverter.h>
	#include <AudioFile.h>
	#include <AudioFileComponent.h>
	#include <AudioFileStream.h>
	#include <AudioFormat.h>
	#include <AudioQueue.h>
	#include <AudioUnitUtilities.h>
	#include <AUGraph.h>
	#include <AUMIDIController.h>
	#include <CAFFile.h>
	#include <CoreAudioClock.h>
	#include <ExtendedAudioFile.h>
	#include <MusicPlayer.h>
	#include <AudioServices.h>
#endif

#ifndef __AudioToolbox_H
#define __AudioToolbox_H

#if defined(__cplusplus)
extern "C"
{
#endif

// prints out the internal state of an object to stdio
extern void CAShow (void* inObject) 
											__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

#include <stdio.h>

// prints out the internal state of an object to the supplied FILE
extern void CAShowFile (void* inObject, FILE* inFile) 
											__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

#if !TARGET_OS_IPHONE
// this will return the name of a sound bank from a sound bank file
// the name should be released by the caller
struct FSRef;
extern OSStatus GetNameFromSoundBank (const struct FSRef *inSoundBankRef, CFStringRef *outName)
											__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);

extern OSStatus 
CopyNameFromSoundBank (CFURLRef inURL, CFStringRef *outName) 
											__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_NA);
#endif

#if defined(__cplusplus)
}
#endif

#endif // __AudioToolbox_H

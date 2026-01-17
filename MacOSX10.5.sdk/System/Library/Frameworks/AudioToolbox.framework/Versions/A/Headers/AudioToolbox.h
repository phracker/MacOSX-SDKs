/*
     File:       AudioToolbox/AudioToolbox.h
 
     Contains:  Umbrella include for AudioToolbox headers.
				Also includes CAShow that allows you to print
				internal state of an object.
 
     Version:    Technology: Mac OS X
 
     Copyright:  (c) 2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#include <TargetConditionals.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioToolbox/AudioConverter.h>
	#include <AudioToolbox/AudioFile.h>
	#include <AudioToolbox/AudioFileComponent.h>
	#include <AudioToolbox/AudioFileStream.h>
	#include <AudioToolbox/AudioFormat.h>
	#include <AudioToolbox/AudioQueue.h>
	#include <AudioToolbox/AudioUnitUtilities.h>
	#include <AudioToolbox/AUGraph.h>
	#include <AudioToolbox/AUMIDIController.h>
	#include <AudioToolbox/CAFFile.h>
	#include <AudioToolbox/CoreAudioClock.h>
	#include <AudioToolbox/ExtendedAudioFile.h>
	#include <AudioToolbox/MusicPlayer.h>
	#include <AudioToolbox/AudioServices.h>
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
extern void CAShow (void* inObject);

#include <stdio.h>

// prints out the internal state of an object to the supplied FILE
extern void CAShowFile (void* inObject, FILE* inFile);

// this will return the name of a sound bank from a sound bank file
// the name should be released by the caller
struct FSRef;
extern OSStatus GetNameFromSoundBank (const struct FSRef *inSoundBankRef, CFStringRef *outName)
																AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER
																DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

extern OSStatus 
CopyNameFromSoundBank (CFURLRef inURL, CFStringRef *outName) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#if defined(__cplusplus)
}
#endif

#endif // __AudioToolbox_H

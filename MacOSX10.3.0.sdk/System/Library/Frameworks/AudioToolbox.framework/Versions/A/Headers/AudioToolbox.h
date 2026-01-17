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

#include <AudioToolbox/AudioConverter.h>
#include <AudioToolbox/AudioFile.h>
#include <AudioToolbox/AudioFormat.h>
#include <AudioToolbox/AudioUnitUtilities.h>
#include <AudioToolbox/AUGraph.h>
#include <AudioToolbox/AUMIDIController.h>
#include <AudioToolbox/DefaultAudioOutput.h>
#include <AudioToolbox/MusicPlayer.h>

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
extern OSStatus GetNameFromSoundBank(const FSRef *inSoundBankRef, CFStringRef *outName);

#if defined(__cplusplus)
}
#endif

#endif // __AudioToolbox_H

/*!
	@file		AudioToolbox.h
	@framework	AudioToolbox.framework
	@copyright	(c) 2002-2015 by Apple, Inc., all rights reserved.
	@abstract	Umbrella header for AudioToolbox framework.
*/

#ifndef AudioToolbox_AudioToolbox_h
#define AudioToolbox_AudioToolbox_h

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
		#include <AudioToolbox/AudioFileComponent.h>
		#include <AudioToolbox/AudioUnitUtilities.h>
		#include <AudioToolbox/AUMIDIController.h>
		#include <AudioToolbox/CoreAudioClock.h>
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

#include <stdio.h>

CF_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
extern "C"
{
#endif

// prints out the internal state of an object to stdio
extern void CAShow (void* inObject) 
											__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);

// prints out the internal state of an object to the supplied FILE
extern void CAShowFile (void* inObject, FILE* inFile) 
											__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);
	
// this will return the name of a sound bank from a sound bank file
// the name should be released by the caller
struct FSRef;
extern OSStatus GetNameFromSoundBank (const struct FSRef *inSoundBankRef, CFStringRef __nullable * __nonnull outName)
											__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_5, __IPHONE_NA, __IPHONE_NA);

/*!
    @function		CopyNameFromSoundBank
	 
    @discussion		This will return the name of a sound bank from a DLS or SF2 bank.
					The name should be released by the caller.

    @param			inURL
						The URL for the sound bank.
    @param			outName
						A pointer to a CFStringRef to be created and returned by the function.
    @result			returns noErr if successful.
*/

extern OSStatus
CopyNameFromSoundBank (CFURLRef inURL, CFStringRef __nullable * __nonnull outName)
											__OSX_AVAILABLE_STARTING(__MAC_10_5,__IPHONE_7_0);

/*!
    @function		CopyInstrumentInfoFromSoundBank
	 
    @discussion		This will return a CFArray of CFDictionaries, one per instrument found in the DLS or SF2 bank.
					Each dictionary will contain four items accessed via CFStringRef versions of the keys kInstrumentInfoKey_MSB,
 					kInstrumentInfoKey_LSB, kInstrumentInfoKey_Program, and kInstrumentInfoKey_Name.
 						MSB: An NSNumberRef for the most-significant byte of the bank number.  GM melodic banks will return 120 (0x78).
 							 GM percussion banks will return 121 (0x79).  Custom banks will return their literal value.
						LSB: An NSNumberRef for the least-significant byte of the bank number.  All GM banks will return
							 the bank variation number (0-127).
 						Program Number: An NSNumberRef for the program number (0-127) of an instrument within a particular bank.
 						Name: A CFStringRef containing the name of the instrument.
 
					Using these MSB, LSB, and Program values will guarantee that the correct instrument is loaded by the DLS synth
					or Sampler Audio Unit.
					The CFArray should be released by the caller.

    @param			inURL
	 					The URL for the sound bank.
    @param			outInstrumentInfo
						A pointer to a CFArrayRef to be created and returned by the function.
    @result			returns noErr if successful.
*/

extern OSStatus CopyInstrumentInfoFromSoundBank (CFURLRef inURL, CFArrayRef __nullable * __nonnull outInstrumentInfo)
														__OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_7_0);
	
#define kInstrumentInfoKey_Name		"name"
#define kInstrumentInfoKey_MSB		"MSB"
#define kInstrumentInfoKey_LSB		"LSB"
#define kInstrumentInfoKey_Program	"program"

#if defined(__cplusplus)
}
#endif

CF_ASSUME_NONNULL_END

#endif // AudioToolbox_AudioToolbox_h

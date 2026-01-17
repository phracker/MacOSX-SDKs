/*==================================================================================================
	 File:       CoreAudio/AudioHardwareTapping.h

	 Contains:   API for communicating with audio hardware.

	 Copyright:  (c) 1985-2020 by Apple, Inc., all rights reserved.

	 Bugs?:      For bug reports, consult the following page on
				 the World Wide Web:

					 http://developer.apple.com/bugreporter/

==================================================================================================*/

#ifdef __OBJC__

#ifndef AudioHardwareTapping_h
#define AudioHardwareTapping_h

#include <Availability.h>
#include <CoreAudio/AudioHardware.h>

@class CATapDescription;

#if defined(__cplusplus)
extern "C"
{
#endif

//==================================================================================================
#pragma mark Tap Functions

/*!
    @function       AudioHardwareCreateProcessTap
    @abstract       This routine creates a new Tap using the provided description.
    @param          inDescription
                    The CATapDescription that specifies how to build the Tap.
    @param          outTapID
					The AudioObjectID of the newly created Tap.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
AudioHardwareCreateProcessTap(CATapDescription* inDescription,
							  AudioObjectID*  outTapID)                                     API_AVAILABLE(macos(14.2)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
    @function       AudioHardwareDestroyProcessTap
    @abstract       This routine destroys the given Tap.
    @param          inTapID
                    The AudioObjectID of the Tap to destroy.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
AudioHardwareDestroyProcessTap(AudioObjectID inTapID)                                       API_AVAILABLE(macos(14.2)) API_UNAVAILABLE(ios, watchos, tvos);

#if defined(__cplusplus)
}
#endif

#endif /* AudioHardwareTapping_h */

#endif // __OBJC__


/*
	File:  CMAudioClock.h
 
	Framework:  CoreMedia
 
	Copyright © 2006-2018 Apple Inc. All rights reserved.
 
*/

#ifndef __CMAUDIOCLOCK__
#define __CMAUDIOCLOCK__

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMSync.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)

/*!
	@function	CMAudioClockCreate
	@abstract	Creates a clock that advances at the same rate as audio output.
	@discussion
		This clock will not drift from audio output, but may drift from CMClockGetHostTimeClock().
		When audio output is completely stopped, the clock continues to advance, tracking CMClockGetHostTimeClock() 
		until audio output starts up again.
		This clock is suitable for use as AVPlayer.masterClock when synchronizing video-only playback 
		with audio played through other APIs or objects.
	@param	allocator
		A CFAllocator to use to allocate the clock.  
		Pass kCFAllocatorDefault or NULL to use the default allocator.
	@param	clockOut
		Points to a CMClockRef to receive the newly created clock.
		The caller is responsible for calling CFRelease to release this clock.
*/
CM_EXPORT OSStatus
CMAudioClockCreate(
		CM_NULLABLE CFAllocatorRef allocator,
		CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CMClockRef * CM_NONNULL clockOut)
			API_AVAILABLE(ios(6.0))
			API_UNAVAILABLE(macosx);

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif

#endif // __CMAUDIOCLOCK__

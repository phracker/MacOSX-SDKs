/*
	File:  CMAudioDeviceClock.h
 
	Framework:  CoreMedia
 
	Copyright © 2006-2018 Apple Inc. All rights reserved.
 
*/

#ifndef __CMAUDIODEVICECLOCK__
#define __CMAUDIODEVICECLOCK__

#include <CoreMedia/CMBase.h>
#if !TARGET_OS_IPHONE

#include <CoreMedia/CMSync.h>

#include <CoreAudio/CoreAudio.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)

/*!
	@function	CMAudioDeviceClockCreate
	@abstract	Creates a clock that tracks playback through a particular CoreAudio device.
	@discussion
		When the device is stopped, the clock continues to tick, tracking HostTime until
		the device starts up again.
		Pass NULL for deviceUID to create a clock that tracks the default device.
		deviceUID must be NULL on iOS.
*/
CM_EXPORT OSStatus
CMAudioDeviceClockCreate(
		CFAllocatorRef CM_NULLABLE allocator,
		CFStringRef	CM_NULLABLE deviceUID,
		CM_RETURNS_RETAINED_PARAMETER CMClockRef CM_NULLABLE * CM_NONNULL clockOut)
			API_AVAILABLE(macos(10.8), macCatalyst(12.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@function	CMAudioDeviceClockCreateFromAudioDeviceID
	@abstract	Creates a clock that tracks playback through a particular CoreAudio device.
*/
CM_EXPORT OSStatus
CMAudioDeviceClockCreateFromAudioDeviceID(
		CFAllocatorRef CM_NULLABLE allocator,
		AudioDeviceID deviceID,
		CM_RETURNS_RETAINED_PARAMETER CMClockRef CM_NULLABLE * CM_NONNULL clockOut)
			API_AVAILABLE(macos(10.8), macCatalyst(12.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	CMAudioDeviceClockSetAudioDeviceUID
	@abstract	Changes the CoreAudio device the clock is tracking.
	@discussion
		Pass NULL for deviceUID to make the clock track the default device.
*/
CM_EXPORT OSStatus
CMAudioDeviceClockSetAudioDeviceUID(
		CMClockRef CM_NONNULL clock,
		CFStringRef CM_NULLABLE deviceUID)
			API_AVAILABLE(macos(10.8), macCatalyst(12.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@function	CMAudioDeviceClockSetAudioDeviceUID
	@abstract	Changes the CoreAudio device the clock is tracking.
*/
CM_EXPORT OSStatus
CMAudioDeviceClockSetAudioDeviceID(
		CMClockRef CM_NONNULL clock,
		AudioDeviceID deviceID)
			API_AVAILABLE(macos(10.8), macCatalyst(12.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

/*!
	@function	CMAudioDeviceClockGetAudioDevice
	@abstract	Queries which CoreAudio device the clock is tracking.
	@discussion
		If a non-NULL deviceUID has been set, CMAudioDeviceClockGetAudioDevice returns the set UID, its associated ID,
		and *trackingDefaultDeviceOut == false.
		If a deviceID has been set directly, CMAudioDeviceClockGetAudioDevice returns NULL UID, the set device ID,
		and *trackingDefaultDeviceOut == false.
		If a NULL deviceUID has been set (which means "track the default device"), CMAudioDeviceClockGetAudioDevice
		returns NULL UID, the ID of the current default device, and *trackingDefaultDeviceOut == true.
*/
CM_EXPORT OSStatus CMAudioDeviceClockGetAudioDevice(
		CMClockRef CM_NONNULL clock,
		CM_RETURNS_NOT_RETAINED_PARAMETER CFStringRef CM_NULLABLE * CM_NULLABLE deviceUIDOut,	// may be NULL
		AudioDeviceID * CM_NULLABLE deviceIDOut,			// may be NULL
		Boolean * CM_NULLABLE trackingDefaultDeviceOut)	// may be NULL
			API_AVAILABLE(macos(10.8), macCatalyst(12.0)) API_UNAVAILABLE(ios, tvos, watchos, visionos);

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif

#endif // !TARGET_OS_IPHONE

#endif // __CMAUDIODEVICECLOCK__

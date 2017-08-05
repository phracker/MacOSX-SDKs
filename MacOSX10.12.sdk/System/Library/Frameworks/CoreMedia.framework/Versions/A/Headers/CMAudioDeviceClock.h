/*
	File:  CMAudioDeviceClock.h
 
	Framework:  CoreMedia
 
	Copyright © 2006-2015 Apple Inc. All rights reserved.
 
*/

#ifndef __CMAUDIODEVICECLOCK__
#define __CMAUDIODEVICECLOCK__

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMSync.h>

#if ! TARGET_OS_IPHONE
#include <CoreAudio/CoreAudio.h>
#endif // ! TARGET_OS_IPHONE

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
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);

#if ! TARGET_OS_IPHONE
/*!
	@function	CMAudioDeviceClockCreateFromAudioDeviceID
	@abstract	Creates a clock that tracks playback through a particular CoreAudio device.
*/
CM_EXPORT OSStatus
CMAudioDeviceClockCreateFromAudioDeviceID(
		CFAllocatorRef CM_NULLABLE allocator,
		AudioDeviceID deviceID,
		CM_RETURNS_RETAINED_PARAMETER CMClockRef CM_NULLABLE * CM_NONNULL clockOut)
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);

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
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);

/*!
	@function	CMAudioDeviceClockSetAudioDeviceUID
	@abstract	Changes the CoreAudio device the clock is tracking.
*/
CM_EXPORT OSStatus
CMAudioDeviceClockSetAudioDeviceID(
		CMClockRef CM_NONNULL clock,
		AudioDeviceID deviceID)
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);

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
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_NA);

#endif // ! TARGET_OS_IPHONE

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif

#endif // __CMAUDIODEVICECLOCK__

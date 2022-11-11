/*
	File:  CMSync.h
 
	Framework:  CoreMedia
 
	Copyright © 2006-2021 Apple Inc. All rights reserved.
 
*/

#ifndef __CMSYNC__
#define __CMSYNC__

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMTime.h>
#include <dispatch/dispatch.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 4)

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@typedef	CMClock
	@abstract	A timing source object.
	@discussion
		A clock represents a source of time information: generally, a piece of hardware that measures the passage of time.
		One example of a clock is the host time clock, accessible via CMClockGetHostTimeClock().  
		It measures time using the CPU system clock, which on Mac OS X is mach_absolute_time().
		Every audio device can also be considered a clock since the audio samples that it outputs or inputs each have a 
		defined duration (eg, 1/48000 of a second for 48 kHz audio).
		
		CMClocks are read-only: they cannot be stopped or started, and the current time cannot be set.
		A CMClock has one primary function, CMClockGetTime, which tells what time it is now.  
		Additionally, the CMSync infrastructure monitors relative drift between CMClocks.
*/

typedef struct CM_BRIDGED_TYPE(id) OpaqueCMClock* CMClockRef API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0)); // a CF type; use CFRetain and CFRelease

/*!
	@typedef	CMTimebase
	@abstract	Models a timeline under application control.
	@discussion
		A timebase represents a timeline that clients can control by setting the rate and time.
		Each timebase has either a source clock or a source timebase (previously referred to as a master clock or master timebase).
		The rate of the timebase is expressed relative to its source.
		When a timebase has rate 0.0, its time is fixed and does not change as its source's time changes.
		When a timebase has rate 1.0, its time increases one second as its source's time increases by one second.
		When a timebase has rate 2.0, its time increases two seconds as its source's time increases by one second.
		When a timebase has rate -1.0, its time decreases one second as its source's time increases by one second.
		
		If a timebase has a source timebase, the source timebase's rate is a factor in determining the timebase's effective rate.
		In fact, a timebase's effective rate is defined as the product of its rate, its source timebase's rate,
		its source timebase's source timebase's rate, and so on up to the ultimate source clock.  This is the rate at which
		the timebase's time changes relative to the ultimate source clock.
*/

typedef struct CM_BRIDGED_TYPE(id) OpaqueCMTimebase* CMTimebaseRef API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0)); // a CF type; use CFRetain and CFRelease

typedef CM_BRIDGED_TYPE(id) CFTypeRef CMClockOrTimebaseRef API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0)); // used in argument lists and function results to indicate that either may be passed

#ifndef CMTIMEBASE_USE_SOURCE_TERMINOLOGY
#if (__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ >= __MAC_12_0) || (__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= __IPHONE_15_0) || (__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__ >= __TVOS_15_0) || (__ENVIRONMENT_WATCH_OS_VERSION_MIN_REQUIRED__ >= __WATCHOS_8_0) || 0
#define CMTIMEBASE_USE_SOURCE_TERMINOLOGY 1 // When using the SDK that includes this header file, apps may adopt the newer terminology and continue to deploy to prior OS versions.
#else
#define CMTIMEBASE_USE_SOURCE_TERMINOLOGY 0 // Prior to 2021, the source clock or source timebase was referred to as a master clock or master timebase.
#endif
#endif


// CMClock error codes
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMClockError_MissingRequiredParameter	= -12745,
	kCMClockError_InvalidParameter			= -12746,
	kCMClockError_AllocationFailed			= -12747,
	kCMClockError_UnsupportedOperation		= -12756,
} API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

// CMTimebase error codes
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMTimebaseError_MissingRequiredParameter	= -12748,
	kCMTimebaseError_InvalidParameter			= -12749,
	kCMTimebaseError_AllocationFailed			= -12750,
	kCMTimebaseError_TimerIntervalTooShort		= -12751,
	kCMTimebaseError_ReadOnly					= -12757,
} API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

// CMSync error codes
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMSyncError_MissingRequiredParameter	= -12752,
	kCMSyncError_InvalidParameter			= -12753,
	kCMSyncError_AllocationFailed			= -12754,
	kCMSyncError_RateMustBeNonZero			= -12755,
} API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMClockGetTypeID
	@abstract	Returns the CFTypeID for CMClock.
*/
CM_EXPORT CFTypeID
CMClockGetTypeID( void )
	API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMClockGetHostTimeClock
	@abstract	Returns a reference to the singleton clock logically identified with host time.
	@discussion
		On Mac OS X, the host time clock uses mach_absolute_time but returns a value 
		with a large integer timescale (eg, nanoseconds).
*/
CM_EXPORT CMClockRef CM_NONNULL
CMClockGetHostTimeClock( void )
	API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMClockConvertHostTimeToSystemUnits
	@abstract	Converts a host time from CMTime to the host time's native units.
	@discussion
		This function performs a scale conversion, not a clock conversion.
		It can be more accurate than CMTimeConvertScale because the system units may 
		have a non-integer timescale.
		On Mac OS X, this function converts to the units of mach_absolute_time.
*/
CM_EXPORT uint64_t
CMClockConvertHostTimeToSystemUnits( CMTime hostTime )
	API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMClockMakeHostTimeFromSystemUnits
	@abstract	Converts a host time from native units to CMTime.
	@discussion
		The returned value will have a large integer timescale (eg, nanoseconds).
		This function handles situations where host time's native units use a 
		non-integer timescale.
		On Mac OS X, this function converts from the units of mach_absolute_time.
*/
CM_EXPORT CMTime
CMClockMakeHostTimeFromSystemUnits( uint64_t hostTime )
	API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));
		
/*!
	@function	CMClockGetTime
	@abstract	Retrieves the current time from a clock.
*/
CM_EXPORT CMTime
CMClockGetTime(
		CMClockRef CM_NONNULL clock )
	API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMClockGetAnchorTime
	@abstract	Retrieves the current time from a clock and also the matching time from the clock's reference clock.
	@discussion	To make practical use of this, you may need to know what the clock's reference clock is.
*/
CM_EXPORT OSStatus
CMClockGetAnchorTime(
		CMClockRef CM_NONNULL clock,
		CMTime * CM_NONNULL clockTimeOut,
		CMTime * CM_NONNULL referenceClockTimeOut )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMClockMightDrift
	@abstract	Indicates whether it is possible for two clocks to drift relative to each other.
*/
CM_EXPORT Boolean
CMClockMightDrift(
		CMClockRef CM_NONNULL clock,
		CMClockRef CM_NONNULL otherClock )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMClockInvalidate
	@abstract	Makes the clock stop functioning.
	@discussion
		After invalidation, the clock will return errors from all APIs.
		This should only be called by the "owner" of the clock, who knows (for example) that some piece of hardware
		has gone away, and the clock will no longer work (and might even crash).
*/
CM_EXPORT void
CMClockInvalidate(
		CMClockRef CM_NONNULL clock )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));
		

/*!
	@function	CMTimebaseGetTypeID
	@abstract	Returns the CFTypeID for CMTimebase.
*/
CM_EXPORT CFTypeID
CMTimebaseGetTypeID( void )
	API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	CMTimebaseCreateWithSourceClock
	@abstract	Creates a timebase driven by the given clock.
	@discussion
		The timebase will initially have rate zero and time zero.
		Pass CMClockGetHostTimeClock() for sourceClock to have the host time clock drive this timebase.
*/
#if CMTIMEBASE_USE_SOURCE_TERMINOLOGY
CM_EXPORT OSStatus
CMTimebaseCreateWithSourceClock(
		CFAllocatorRef CM_NULLABLE allocator,
		CMClockRef CM_NONNULL sourceClock,
		CM_RETURNS_RETAINED_PARAMETER CMTimebaseRef CM_NULLABLE * CM_NONNULL timebaseOut )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

static inline OSStatus
CMTimebaseCreateWithMasterClock(
		CFAllocatorRef CM_NULLABLE allocator,
		CMClockRef CM_NONNULL masterClock,
		CM_RETURNS_RETAINED_PARAMETER CMTimebaseRef CM_NULLABLE * CM_NONNULL timebaseOut )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCreateWithSourceClock", macos(10.8,10.10), ios(6.0,8.0), tvos(9.0,9.0), watchos(6.0,6.0))
{
	return CMTimebaseCreateWithSourceClock(allocator, masterClock, timebaseOut);
}
#else
CM_EXPORT OSStatus
CMTimebaseCreateWithMasterClock(
		CFAllocatorRef CM_NULLABLE allocator,
		CMClockRef CM_NONNULL masterClock,
		CM_RETURNS_RETAINED_PARAMETER CMTimebaseRef CM_NULLABLE * CM_NONNULL timebaseOut )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCreateWithSourceClock", macos(10.8,10.10), ios(6.0,8.0), tvos(9.0,9.0), watchos(6.0,6.0));
static inline OSStatus
CMTimebaseCreateWithSourceClock(
		CFAllocatorRef CM_NULLABLE allocator,
		CMClockRef CM_NONNULL sourceClock,
		CM_RETURNS_RETAINED_PARAMETER CMTimebaseRef CM_NULLABLE * CM_NONNULL timebaseOut )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0))
{
	return CMTimebaseCreateWithMasterClock(allocator, sourceClock, timebaseOut);
}
#endif

/*!
	@function	CMTimebaseCreateWithSourceTimebase
	@abstract	Creates a timebase driven by the given source timebase.
	@discussion
		The timebase will initially have rate zero and time zero.
*/
#if CMTIMEBASE_USE_SOURCE_TERMINOLOGY
CM_EXPORT OSStatus
CMTimebaseCreateWithSourceTimebase(
		CFAllocatorRef CM_NULLABLE allocator,
		CMTimebaseRef CM_NONNULL sourceTimebase,
		CM_RETURNS_RETAINED_PARAMETER CMTimebaseRef CM_NULLABLE * CM_NONNULL timebaseOut )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

static inline OSStatus
CMTimebaseCreateWithMasterTimebase(
		CFAllocatorRef CM_NULLABLE allocator,
		CMTimebaseRef CM_NONNULL masterTimebase,
		CM_RETURNS_RETAINED_PARAMETER CMTimebaseRef CM_NULLABLE * CM_NONNULL timebaseOut )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCreateWithSourceTimebase", macos(10.8,10.10), ios(6.0,8.0), tvos(9.0,9.0), watchos(6.0,6.0))
{
	return CMTimebaseCreateWithSourceTimebase(allocator, masterTimebase, timebaseOut);
}
#else
CM_EXPORT OSStatus
CMTimebaseCreateWithMasterTimebase(
		CFAllocatorRef CM_NULLABLE allocator,
		CMTimebaseRef CM_NONNULL masterTimebase,
		CM_RETURNS_RETAINED_PARAMETER CMTimebaseRef CM_NULLABLE * CM_NONNULL timebaseOut )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCreateWithSourceTimebase", macos(10.8,10.10), ios(6.0,8.0), tvos(9.0,9.0), watchos(6.0,6.0));
static inline OSStatus
CMTimebaseCreateWithSourceTimebase(
		CFAllocatorRef CM_NULLABLE allocator,
		CMTimebaseRef CM_NONNULL sourceTimebase,
		CM_RETURNS_RETAINED_PARAMETER CMTimebaseRef CM_NULLABLE * CM_NONNULL timebaseOut )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0))
{
	return CMTimebaseCreateWithMasterTimebase(allocator, sourceTimebase, timebaseOut);
}
#endif

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	CMTimebaseCopySourceTimebase
	@abstract	Returns the immediate source timebase of a timebase.
	@discussion
		Returns NULL if the timebase actually has a source clock instead of a source timebase.
*/
#if CMTIMEBASE_USE_SOURCE_TERMINOLOGY
CM_EXPORT CMTimebaseRef CM_NULLABLE
CMTimebaseCopySourceTimebase(
		CMTimebaseRef CM_NONNULL timebase )
			API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));
static inline CMTimebaseRef CM_NULLABLE
CMTimebaseCopyMasterTimebase(
		CMTimebaseRef CM_NONNULL timebase )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCopySourceTimebase", macos(10.11,10.11), ios(9.0,9.0), tvos(9.0,9.0), watchos(6.0,6.0))
{
	return CMTimebaseCopySourceTimebase(timebase);
}
#else
CM_EXPORT CMTimebaseRef CM_NULLABLE
CMTimebaseCopyMasterTimebase(
		CMTimebaseRef CM_NONNULL timebase )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCopySourceTimebase", macos(10.11,10.11), ios(9.0,9.0), tvos(9.0,9.0), watchos(6.0,6.0));
static inline CMTimebaseRef CM_NULLABLE
CMTimebaseCopySourceTimebase(
		CMTimebaseRef CM_NONNULL timebase )
			API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0))
{
	return CMTimebaseCopyMasterTimebase(timebase);
}
#endif

/*!
	@function	CMTimebaseCopySourceClock
	@abstract	Returns the immediate source clock of a timebase.
	@discussion
		Returns NULL if the timebase actually has a source timebase instead of a source clock.
*/
#if CMTIMEBASE_USE_SOURCE_TERMINOLOGY
CM_EXPORT CMClockRef CM_NULLABLE
CMTimebaseCopySourceClock(
		CMTimebaseRef CM_NONNULL timebase )
			API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));
static inline CMClockRef CM_NULLABLE
CMTimebaseCopyMasterClock(
		CMTimebaseRef CM_NONNULL timebase )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCopySourceClock", macos(10.11,10.11), ios(9.0,9.0), tvos(9.0,9.0), watchos(6.0,6.0))
{
	return CMTimebaseCopySourceClock(timebase);
}
#else
CM_EXPORT CMClockRef CM_NULLABLE
CMTimebaseCopyMasterClock(
		CMTimebaseRef CM_NONNULL timebase )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCopySourceClock", macos(10.11,10.11), ios(9.0,9.0), tvos(9.0,9.0), watchos(6.0,6.0));
static inline CMClockRef CM_NULLABLE
CMTimebaseCopySourceClock(
		CMTimebaseRef CM_NONNULL timebase )
			API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0))
{
	return CMTimebaseCopyMasterClock(timebase);
}
#endif

/*!
	@function	CMTimebaseCopySource
	@abstract	Returns the immediate source (either timebase or clock) of a timebase.
	@discussion
		Only returns NULL if there was an error (such as timebase == NULL).
*/
#if CMTIMEBASE_USE_SOURCE_TERMINOLOGY
CM_EXPORT CMClockOrTimebaseRef CM_NONNULL
CMTimebaseCopySource(
		CMTimebaseRef CM_NONNULL timebase )
			API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));
static inline CMClockOrTimebaseRef CM_NONNULL
CMTimebaseCopyMaster(
		CMTimebaseRef CM_NONNULL timebase )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCopySource", macos(10.11,10.11), ios(9.0,9.0), tvos(9.0,9.0), watchos(6.0,6.0))
{
	return CMTimebaseCopySource(timebase);
}
#else
CM_EXPORT CMClockOrTimebaseRef CM_NONNULL
CMTimebaseCopyMaster(
		CMTimebaseRef CM_NONNULL timebase )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCopySource", macos(10.11,10.11), ios(9.0,9.0), tvos(9.0,9.0), watchos(6.0,6.0));
static inline CMClockOrTimebaseRef CM_NONNULL
CMTimebaseCopySource(
		CMTimebaseRef CM_NONNULL timebase )
			API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0))
{
	return CMTimebaseCopyMaster(timebase);
}
#endif

/*!
	@function	CMTimebaseCopyUltimateSourceClock
	@abstract	Returns the source clock that is the source of all of a timebase's source timebases.
*/
#if CMTIMEBASE_USE_SOURCE_TERMINOLOGY
CM_EXPORT CMClockRef CM_NONNULL
CMTimebaseCopyUltimateSourceClock(
		CMTimebaseRef CM_NONNULL timebase )
			API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0));
static inline CMClockRef CM_NONNULL
CMTimebaseCopyUltimateMasterClock(
		CMTimebaseRef CM_NONNULL timebase )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCopyUltimateSourceClock", macos(10.11,10.11), ios(9.0,9.0), tvos(9.0,9.0), watchos(6.0,6.0))
{
	return CMTimebaseCopyUltimateSourceClock(timebase);
}
#else
CM_EXPORT CMClockRef CM_NONNULL
CMTimebaseCopyUltimateMasterClock(
		CMTimebaseRef CM_NONNULL timebase )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCopyUltimateSourceClock", macos(10.11,10.11), ios(9.0,9.0), tvos(9.0,9.0), watchos(6.0,6.0));
static inline CMClockRef CM_NONNULL
CMTimebaseCopyUltimateSourceClock(
		CMTimebaseRef CM_NONNULL timebase )
			API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(6.0))
{
	return CMTimebaseCopyUltimateMasterClock(timebase);
}
#endif

/*!
	@function	CMTimebaseGetMasterTimebase
	@abstract	Returns the immediate source timebase of a timebase.
	@discussion
		Returns NULL if the timebase actually has a source clock instead of a source timebase.
		Please use CMTimebaseCopySourceTimebase instead.
*/
CM_EXPORT CMTimebaseRef CM_NULLABLE
CMTimebaseGetMasterTimebase(
		CMTimebaseRef CM_NONNULL timebase )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCopySourceTimebase", macos(10.8, 10.11), ios(6.0, 9.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos);

/*!
	@function	CMTimebaseGetMasterClock
	@abstract	Returns the immediate source clock of a timebase.
	@discussion
		Returns NULL if the timebase actually has a source timebase instead of a source clock.
		Please use CMTimebaseCopySourceClock instead.
*/
CM_EXPORT CMClockRef CM_NULLABLE
CMTimebaseGetMasterClock(
		CMTimebaseRef CM_NONNULL timebase )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCopySourceClock", macos(10.8, 10.11), ios(6.0, 9.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos);

/*!
	@function	CMTimebaseGetMaster
	@abstract	Returns the immediate source (either timebase or clock) of a timebase.
	@discussion
		Only returns NULL if there was an error (such as timebase == NULL).
		Example of use: time = CMSyncGetTime(CMTimebaseGetMaster(timebase));
		Please use CMTimebaseCopySource instead.
*/
CM_EXPORT CMClockOrTimebaseRef CM_NULLABLE
CMTimebaseGetMaster(
		CMTimebaseRef CM_NONNULL timebase )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCopySource", macos(10.8, 10.11), ios(6.0, 9.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos);

/*!
	@function	CMTimebaseGetUltimateMasterClock
	@abstract	Returns the source clock that is the source of all of a timebase's source timebases.
	@discussion
		Please use CMTimebaseCopyUltimateSourceClock instead.
*/
CM_EXPORT CMClockRef CM_NULLABLE
CMTimebaseGetUltimateMasterClock(
		CMTimebaseRef CM_NONNULL timebase )
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseCopyUltimateSourceClock", macos(10.8, 10.11), ios(6.0, 9.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos);

/*!
	@function	CMTimebaseSetSourceClock
	@abstract
		Sets the source clock of a timebase.
	@discussion
		The timebase will stop receiving timing information from its current source clock or source
		timebase, and will begin receiving timing information from the new source clock.  Prior to
		the change a kCMTimebaseNotification_SourceWillChange will be posted.  When
		the change has completed, a kCMTimebaseNotification_SourceDidChange notification
		will be posted.
*/
#if CMTIMEBASE_USE_SOURCE_TERMINOLOGY
CM_EXPORT OSStatus CMTimebaseSetSourceClock(
		CMTimebaseRef CM_NONNULL timebase,
		CMClockRef CM_NONNULL newSourceClock)
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));
static inline OSStatus CMTimebaseSetMasterClock(
		CMTimebaseRef CM_NONNULL timebase,
		CMClockRef CM_NONNULL newMasterClock)
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseSetSourceClock", macos(10.8,10.10), ios(6.0,8.0), tvos(9.0,9.0), watchos(6.0,6.0))
{
	return CMTimebaseSetSourceClock(timebase, newMasterClock);
}
#else
CM_EXPORT OSStatus CMTimebaseSetMasterClock(
		CMTimebaseRef CM_NONNULL timebase,
		CMClockRef CM_NONNULL newMasterClock)
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseSetSourceClock", macos(10.8,10.10), ios(6.0,8.0), tvos(9.0,9.0), watchos(6.0,6.0));
static inline OSStatus CMTimebaseSetSourceClock(
		CMTimebaseRef CM_NONNULL timebase,
		CMClockRef CM_NONNULL newSourceClock)
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0))
{
	return CMTimebaseSetMasterClock(timebase, newSourceClock);
}
#endif

/*!
	@function	CMTimebaseSetSourceTimebase
	@abstract
		Sets the source timebase of a timebase.
	@discussion
		The timebase will stop receiving timing information from its current source clock or source
		timebase, and will begin receiving timing information from the new source timebase.  Prior to
		the change a kCMTimebaseNotification_SourceWillChange will be posted.  When
		the change has completed, a kCMTimebaseNotification_SourceDidChange notification
		will be posted.
*/
#if CMTIMEBASE_USE_SOURCE_TERMINOLOGY
CM_EXPORT OSStatus CMTimebaseSetSourceTimebase(
		CMTimebaseRef CM_NONNULL timebase,
		CMTimebaseRef CM_NONNULL newSourceTimebase)
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));
static inline OSStatus CMTimebaseSetMasterTimebase(
		CMTimebaseRef CM_NONNULL timebase,
		CMTimebaseRef CM_NONNULL newMasterTimebase)
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseSetSourceTimebase", macos(10.8,10.10), ios(6.0,8.0), tvos(9.0,9.0), watchos(6.0,6.0))
{
	return CMTimebaseSetSourceTimebase(timebase, newMasterTimebase);
}
#else
CM_EXPORT OSStatus CMTimebaseSetMasterTimebase(
		CMTimebaseRef CM_NONNULL timebase,
		CMTimebaseRef CM_NONNULL newMasterTimebase)
			API_DEPRECATED_WITH_REPLACEMENT("CMTimebaseSetSourceTimebase", macos(10.8,10.10), ios(6.0,8.0), tvos(9.0,9.0), watchos(6.0,6.0));
static inline OSStatus CMTimebaseSetSourceTimebase(
		CMTimebaseRef CM_NONNULL timebase,
		CMTimebaseRef CM_NONNULL newSourceTimebase)
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0))
{
	return CMTimebaseSetMasterTimebase(timebase, newSourceTimebase);
}
#endif

/*!
	@function	CMTimebaseGetTime
	@abstract	Retrieves the current time from a timebase.
*/
CM_EXPORT CMTime
CMTimebaseGetTime(
		CMTimebaseRef CM_NONNULL timebase )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseGetTimeWithTimeScale
	@abstract	Retrieves the current time from a timebase in the specified timescale.
*/
CM_EXPORT CMTime
CMTimebaseGetTimeWithTimeScale( 
		CMTimebaseRef CM_NONNULL timebase,
		CMTimeScale timescale,
		CMTimeRoundingMethod method)
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseSetTime
	@abstract	Sets the current time of a timebase.  
*/
CM_EXPORT OSStatus 
CMTimebaseSetTime( 
		CMTimebaseRef CM_NONNULL timebase,
		CMTime time )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseSetAnchorTime
	@abstract	Sets the time of a timebase at a particular source time.
	@discussion
		CMTimebaseGetTime's results will be interpolated from that anchor time.
		CMTimebaseSetTime(timebase, time) is equivalent to calling
			CMClockOrTimebaseRef source = CMTimebaseCopySource(timebase);
			CMTimebaseSetAnchorTime(timebase, time, CMSyncGetTime(source));
			CFRelease(source).
*/
CM_EXPORT OSStatus
CMTimebaseSetAnchorTime(
		CMTimebaseRef CM_NONNULL timebase,
		CMTime timebaseTime,
		CMTime immediateSourceTime)
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseGetRate
	@abstract	Retrieves the current rate of a timebase.  
	@discussion
		This is the rate relative to its immediate source clock or timebase.  
		For example, if a timebase is running at twice the rate of its source, its rate is 2.0.
*/
CM_EXPORT Float64 
CMTimebaseGetRate( 
		CMTimebaseRef CM_NONNULL timebase )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseGetTimeAndRate
	@abstract	Retrieves the current time and rate of a timebase.
	@discussion
		You can use this function to take a consistent snapshot of the two values,
		avoiding possible inconsistencies due to external changes between retrieval of time and rate.
*/
CM_EXPORT OSStatus 
CMTimebaseGetTimeAndRate( 
		CMTimebaseRef CM_NONNULL timebase,
		CMTime * CM_NULLABLE timeOut,
		Float64 * CM_NULLABLE rateOut )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseSetRate
	@abstract	Sets the rate of a timebase.
*/
CM_EXPORT OSStatus 
CMTimebaseSetRate( 
		CMTimebaseRef CM_NONNULL timebase,
		Float64 rate )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));
		
/*!
	@function	CMTimebaseSetRateAndAnchorTime
	@abstract	Sets the time of a timebase at a particular source time, and changes the rate at exactly that time.
	@discussion
		CMTimebaseGetTime's results will be interpolated from that anchor time as though the timebase 
		has been running at the requested rate since that time.
		CMTimebaseSetRate(timebase, rate) is approximately equivalent to calling
			CMClockOrTimebaseRef source = CMTimebaseCopySource(timebase);
			CMTimebaseSetRateAndAnchorTime(timebase, rate, CMTimebaseGetTime(timebase), CMSyncGetTime(source)),
			CFRelease(source);
		except that CMTimebaseSetRate will not generate a TimeJumped notification, and
		CMTimebaseSetRateAndAnchorTime will.
*/
CM_EXPORT OSStatus
CMTimebaseSetRateAndAnchorTime(
		CMTimebaseRef CM_NONNULL timebase,
		Float64 rate,
		CMTime timebaseTime,
		CMTime immediateSourceTime)
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseGetEffectiveRate
	@abstract	Gets the effective rate of a timebase (which combines its rate with the rates of all its source timebases).
	@discussion
		Calling CMTimebaseGetEffectiveRate(timebase) is equivalent to calling
			CMClockRef clock = CMTimebaseCopyUltimateSourceClock(timebase);
			CMSyncGetRelativeRate(timebase, clock).
			CFRelease(clock);
*/
CM_EXPORT Float64
CMTimebaseGetEffectiveRate(
		CMTimebaseRef CM_NONNULL timebase )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseAddTimer
	@abstract
		Adds the timer to the list of timers managed by the timebase. 
	@discussion
		The timer must be a repeating run loop timer (with a very long interval at
		least as long as kCMTimebaseVeryLongCFTimeInterval), attached to a runloop.  
		The timebase will retain the timer, and will maintain its "NextFireDate" 
		according to the CMTime set using CMTimebaseSetTimerNextFireTime.
		Until the first call to CMTimebaseSetTimerNextFireTime, the "NextFireDate" 
		will be set far, far in the future. The runloop that timer is attached to must be
		passed in and the timebase will retain that runloop. The retained runloop will be
		used to call CFRunLoopWakeUp() any time the timebase modifies the timer's fire date.
*/
CM_EXPORT OSStatus
CMTimebaseAddTimer( 
		CMTimebaseRef CM_NONNULL timebase,
		CFRunLoopTimerRef CM_NONNULL timer,
		CFRunLoopRef CM_NONNULL runloop )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

#define kCMTimebaseVeryLongCFTimeInterval	(CFTimeInterval)(256.0 * 365.0 * 24.0 * 60.0 * 60.0)	// quite a while
#define kCMTimebaseFarFutureCFAbsoluteTime	((CFAbsoluteTime)kCMTimebaseVeryLongCFTimeInterval)		// quite a while from 2001

/*!
	@function	CMTimebaseRemoveTimer
	@abstract
		Removes the timer from the list of timers managed by the timebase. 
	@discussion
		The timebase will no longer maintain the timer's "NextFireDate".
		If the timer is invalidated, the timebase will eventually remove it 
		from its list and release it even if this function is not called.
*/
CM_EXPORT OSStatus
CMTimebaseRemoveTimer( 
		CMTimebaseRef CM_NONNULL timebase,
		CFRunLoopTimerRef CM_NONNULL timer )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseSetTimerNextFireTime
	@abstract
		Sets the CMTime on the timebase's timeline at which the timer should next be fired.
	@discussion
		The timer must be on the list of timers managed by the timebase.
		The timebase will continue to update the timer's "NextFireDate" according to time jumps 
		and effective rate changes.
		If fireTime is not numeric, or if the timebase is not moving, the "NextFireDate"
		will be set to a date far, far in the future.
		<BR>
		IMPORTANT NOTE: Due to the way that CFRunLoopTimers are implemented, if a timer passes 
		through a state in which it is due to fire, it may fire even if its rescheduled before 
		the runloop runs again.  Clients should take care to avoid temporarily scheduling timers 
		in the past.  For example, set the timebase's rate or time before you set the timer's 
		next fire time, if you are doing both at once.  (If setting the timebase's rate or time
		might put the timer's fire time in the past, you may need to set the fire time to 
		kCMTimeInvalid across the timebase change.)
*/
CM_EXPORT OSStatus
CMTimebaseSetTimerNextFireTime( 
		CMTimebaseRef CM_NONNULL timebase,
		CFRunLoopTimerRef CM_NONNULL timer,
		CMTime fireTime,
		uint32_t flags ) // reserved, pass zero
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseSetTimerToFireImmediately
	@abstract
		Sets the timer to fire immediately once, overriding any previous CMTimebaseSetTimerNextFireTime call.
	@discussion
		The timer must be on the list of timers managed by the timebase.
		This is equivalent to calling 
			CFRunLoopTimerSetNextFireDate( timer, CFAbsoluteTimeGetCurrent() );
		except that the timebase gets to know that it shouldn't interfere.
*/
CM_EXPORT OSStatus
CMTimebaseSetTimerToFireImmediately( 
		CMTimebaseRef CM_NONNULL timebase,
		CFRunLoopTimerRef CM_NONNULL timer )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));


/*!
	@function	CMTimebaseAddTimerDispatchSource
	@abstract
		Adds the timer dispatch source to the list of timers managed by the timebase. 
	@discussion
		The timer source must have been created by calling
		dispatch_source_create( DISPATCH_SOURCE_TYPE_TIMER, 0, 0, some_dispatch_queue )
		and should have had an event handler associated with it via
		dispatch_source_set_event_handler( timerSource, some_handler_block )
		or dispatch_source_set_event_handler_f( timerSource, some_handler_function ).
		Don't forget to call dispatch_resume( timerSource ) as dispatch sources are 
		created suspended.
		
		The timebase will retain the timer source, and will maintain its start time
		according to the CMTime set using CMTimebaseSetTimerDispatchSourceNextFireTime.
		Until the first call to CMTimebaseSetTimerDispatchSourceNextFireTime, the start time 
		will be set to DISPATCH_TIME_FOREVER.
*/
CM_EXPORT OSStatus
CMTimebaseAddTimerDispatchSource( 
		CMTimebaseRef CM_NONNULL timebase,
		dispatch_source_t CM_NONNULL timerSource )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));


/*!
	@function	CMTimebaseRemoveTimerDispatchSource
	@abstract
		Removes the timer dispatch source from the list of timers managed by the timebase. 
	@discussion
		The timebase will no longer maintain the timer source's start time.
		If the timer source is cancelled, the timebase will eventually remove it 
		from its list and release it even if this function is not called.
*/
CM_EXPORT OSStatus
CMTimebaseRemoveTimerDispatchSource( 
		CMTimebaseRef CM_NONNULL timebase,
		dispatch_source_t CM_NONNULL timerSource )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseSetTimerDispatchSourceNextFireTime
	@abstract
		Sets the CMTime on the timebase's timeline at which the timer dispatch source should next be fired.
	@discussion
		The timer source must be on the list of timers managed by the timebase.
		The timebase will continue to update the timer dispatch source's start time 
		according to time jumps and effective rate changes.
		If fireTime is not numeric, or if the timebase is not moving, the start time
		will be set to DISPATCH_TIME_FOREVER.
		<BR>
		IMPORTANT NOTE: Due to the way that timer dispatch sources are implemented, if a timer passes 
		through a state in which it is due to fire, it may fire even if its rescheduled before 
		the event handler is run.  Clients should take care to avoid temporarily scheduling timers 
		in the past.  For example, set the timebase's rate or time before you set the timer's 
		next fire time, if you are doing both at once.  (If setting the timebase's rate or time
		might put the timer's fire time in the past, you may need to set the fire time to 
		kCMTimeInvalid across the timebase change.)
*/
CM_EXPORT OSStatus
CMTimebaseSetTimerDispatchSourceNextFireTime( 
		CMTimebaseRef CM_NONNULL timebase,
		dispatch_source_t CM_NONNULL timerSource,
		CMTime fireTime,
		uint32_t flags ) // reserved, pass zero
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseSetTimerDispatchSourceToFireImmediately
	@abstract
		Sets the timer dispatch source to fire immediately once, overriding any previous
		CMTimebaseSetTimerDispatchSourceNextFireTime call.
	@discussion
		The timer source must be on the list of timers managed by the timebase.
		This is equivalent to calling 
			dispatch_source_set_timer( timerSource, DISPATCH_TIME_NOW, 0, 0 );
		except that the timebase gets to know that it shouldn't interfere.
*/
CM_EXPORT OSStatus
CMTimebaseSetTimerDispatchSourceToFireImmediately( 
		CMTimebaseRef CM_NONNULL timebase,
		dispatch_source_t CM_NONNULL timerSource )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));



/*!
	@function	CMSyncGetRelativeRate
	@abstract	Queries the relative rate of one timebase or clock relative to another timebase or clock.
	@discussion
		If both have a common source, this calculation is performed purely based on the rates in the common tree 
		rooted in that source.  
		If they have different source clocks (or are both clocks), this calculation takes into account the measured
		drift between the two clocks, using host time as a pivot.
		The rate of a moving timebase relative to a stopped timebase is a NaN.
		Calling CMTimebaseGetEffectiveRate(timebase) is equivalent to calling
			CMClockRef clock = CMTimebaseCopyUltimateSourceClock(timebase);
			CMSyncGetRelativeRate(timebase, clock).
			CFRelease(clock);
*/
CM_EXPORT Float64 
CMSyncGetRelativeRate( 
		CMClockOrTimebaseRef CM_NONNULL ofClockOrTimebase,
		CMClockOrTimebaseRef CM_NONNULL relativeToClockOrTimebase )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));
		
/*!
	@function	CMSyncGetRelativeRateAndAnchorTime
	@abstract	Queries the relative rate of one timebase or clock relative to another timebase or clock and the times of each timebase or clock at which the relative rate went into effect.
	@discussion
		If both have a common source, this calculation is performed purely based on the rates in the common tree
		rooted in that source.  
		If they have different source clocks (or are both clocks), this calculation takes into account the measured
		drift between the two clocks, using host time as a pivot.
		The rate of a moving timebase relative to a stopped timebase is a NaN.
*/
CM_EXPORT OSStatus
CMSyncGetRelativeRateAndAnchorTime( 
		CMClockOrTimebaseRef CM_NONNULL ofClockOrTimebase,
		CMClockOrTimebaseRef CM_NONNULL relativeToClockOrTimebase,
		Float64* CM_NULLABLE outRelativeRate,
		CMTime* CM_NULLABLE outOfClockOrTimebaseAnchorTime,
		CMTime* CM_NULLABLE outRelativeToClockOrTimebaseAnchorTime)
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMSyncConvertTime
	@abstract	Converts a time from one timebase or clock to another timebase or clock.
	@discussion
		If both have a common source, this calculation is performed purely based on the mathematical rates and offsets 
		in the common tree rooted in that source.  
		If they have different source clocks (or are both clocks), this calculation also compensates
		for measured drift between the clocks.
		To convert to or from host time, pass CMClockGetHostTimeClock() as the appropriate argument.
*/
CM_EXPORT CMTime
CMSyncConvertTime(
		CMTime time, 
		CMClockOrTimebaseRef CM_NONNULL fromClockOrTimebase,
		CMClockOrTimebaseRef CM_NONNULL toClockOrTimebase )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMSyncMightDrift
	@abstract	Reports whether it is possible for one timebase/clock to drift relative to the other.
	@discussion
		A timebase can drift relative to another if their ultimate source clocks that can drift relative
		to each other.
*/
CM_EXPORT Boolean
CMSyncMightDrift(
		CMClockOrTimebaseRef CM_NONNULL clockOrTimebase1,
		CMClockOrTimebaseRef CM_NONNULL clockOrTimebase2 )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));
		
/*!
	@function	CMSyncGetTime
	@abstract	A helper function to get time from a clock or timebase.
	@discussion
		CMSyncGetTime simply calls either CMClockGetTime or CMTimebaseGetTime, as appropriate.
		It comes in handy for things like:
			CMClockOrTimebaseRef source = CMTimebaseCopySource(timebase);
			CMSyncGetTime(source);
			CFRelease(source);
*/
CM_EXPORT CMTime
CMSyncGetTime(
		CMClockOrTimebaseRef CM_NONNULL clockOrTimebase )
			API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

/*!
	@function	CMTimebaseNotificationBarrier
	@abstract	Requests that the timebase wait until it is not posting any notifications.
*/
CM_EXPORT OSStatus	CMTimebaseNotificationBarrier(CMTimebaseRef CM_NONNULL timebase )
						API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));
	
CM_ASSUME_NONNULL_BEGIN

// Posted by a timebase after a change in effective rate.  
CM_EXPORT const CFStringRef kCMTimebaseNotification_EffectiveRateChanged
								API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

// Posted by a timebase after a discontinuous time jump.
CM_EXPORT const CFStringRef kCMTimebaseNotification_TimeJumped
								API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(6.0));

// Payload key for the time at which a change in effective rate or a discontinuous time jump occurred.
CM_EXPORT const CFStringRef kCMTimebaseNotificationKey_EventTime
								API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(6.0));

CM_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif

#endif // __CMSYNC__

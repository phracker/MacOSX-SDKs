/*==================================================================================================
     File:       CoreAudio/HostTime.h

     Contains:   Routines for accessing the host's time base

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2005 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

==================================================================================================*/
#if !defined(__HostTime_h__)
#define __HostTime_h__

//==================================================================================================
#pragma mark    Theory of Operation

/*!
    @header HostTime
    This collection of functions provides access to the host's time base. It also provides
    discriptive information about the time base and translations to and from nanoseconds.
*/

//==================================================================================================
#pragma mark    Includes

#include <AvailabilityMacros.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
    #include <CoreAudio/CoreAudioTypes.h>
#else
    #include <CoreAudioTypes.h>
#endif

//==================================================================================================

#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint off
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

//==================================================================================================
#pragma mark    Functions

/*!
    @functiongroup  HostTime
*/

/*!
    @function       AudioGetCurrentHostTime
    @abstract       Gets the current host time.
    @result         A UInt64 containing the current host time.
*/
extern UInt64
AudioGetCurrentHostTime()                                                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*!
    @function       AudioGetHostClockFrequency
    @abstract       Gets the number of ticks per second in the host time base.
    @result         A Float64 containing the number of ticks per second in the host time base.
*/
extern Float64
AudioGetHostClockFrequency()                                                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*!
    @function       AudioGetHostClockMinimumTimeDelta
    @abstract       Gets the smallest number of ticks that two succeeding values will ever differ.
                    by.
    @result         A UInt32 containing the smallest number of ticks that two succeeding values will
                    ever differ.
*/
extern UInt32
AudioGetHostClockMinimumTimeDelta()                                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*!
    @function       AudioConvertHostTimeToNanos
    @abstract       Convert the given host time into a time in nanoseconds.
    @param          inHostTime
                        A UInt64 containing the host time to convert.
    @result         A UInt64 containining the converted host time.
*/
extern UInt64
AudioConvertHostTimeToNanos(UInt64 inHostTime)                                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*!
    @function       AudioConvertNanosToHostTime
    @abstract       Convert the given nanosecond time into a host time.
    @param          inNanos
                        A UInt64 containing the nanosecond time to convert.
    @result         A UInt64 containining the converted nanosecond time.
*/
extern UInt64
AudioConvertNanosToHostTime(UInt64 inNanos)                                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

//==================================================================================================

#if defined(__cplusplus)
}
#endif

#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
#endif

#endif  //  __HostTime_h__

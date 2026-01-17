/*
     File:       CoreAudio/HostTime.h

     Contains:   Routines for accessing the host's time base

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2001 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/
#if !defined(__HostTime_h__)
#define __HostTime_h__

//=============================================================================
//	Includes
//=============================================================================

#include <CoreAudio/CoreAudioTypes.h>

#if defined(__cplusplus)
extern "C"
{
#endif

//-----------------------------------------------------------------------------
//	AudioGetCurrentHostTime
//
//	Retrieve the current host time value.
//-----------------------------------------------------------------------------

extern UInt64	AudioGetCurrentHostTime();

//-----------------------------------------------------------------------------
//	AudioGetHostClockFrequency
//
//	Retrieve the number of ticks per second of the host clock.
//-----------------------------------------------------------------------------

extern Float64	AudioGetHostClockFrequency();

//-----------------------------------------------------------------------------
//	AudioGetHostClockMinimumTimeDelta
//
//	Retrieve the smallest number of ticks difference between two succeeding
//	values of the host clock. For instance, if this value is 5 and
//	the first value of the host clock is X then the next time after X
//	will be at greater than or equal X+5.
//-----------------------------------------------------------------------------

extern UInt32	AudioGetHostClockMinimumTimeDelta();

//-----------------------------------------------------------------------------
//	AudioConvertHostTimeToNanos
//
//	Convert the given host time to a time in Nanoseconds.
//-----------------------------------------------------------------------------

extern UInt64	AudioConvertHostTimeToNanos(UInt64 inHostTime);

//-----------------------------------------------------------------------------
//	AudioConvertNanosToHostTime
//
//	Convert the given Nanoseconds time to a time in the host clock's
//	time base.
//-----------------------------------------------------------------------------

extern UInt64	AudioConvertNanosToHostTime(UInt64 inNanos);

#if defined(__cplusplus)
}
#endif

#endif

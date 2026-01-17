/*
     File:       CarbonCore/UTCUtils.h
 
     Contains:   Interface for UTC to Local Time conversion and 64 Bit Clock routines
 
     Version:    CarbonCore-861.39~1
 
     Copyright:  © 1999-2008 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __UTCUTILS__
#define __UTCUTILS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

/* Options for Set & Get DateTime Routines */
enum {
  kUTCDefaultOptions            = 0
};

/* 64 Bit Clock Typedefs */
struct UTCDateTime {
  UInt16              highSeconds;
  UInt32              lowSeconds;
  UInt16              fraction;
};
typedef struct UTCDateTime              UTCDateTime;
typedef UTCDateTime *                   UTCDateTimePtr;
typedef UTCDateTimePtr *                UTCDateTimeHandle;
struct LocalDateTime {
  UInt16              highSeconds;
  UInt32              lowSeconds;
  UInt16              fraction;
};
typedef struct LocalDateTime            LocalDateTime;
typedef LocalDateTime *                 LocalDateTimePtr;
typedef LocalDateTimePtr *              LocalDateTimeHandle;
/* Classic 32 bit clock conversion routines */
#if !__LP64__
/*
 *  ConvertLocalTimeToUTC()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use
 *    UCConvertUTCDateTimeToCFAbsoluteTime/CFTimeZoneGetSecondsFromGMT
 *    instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    UCConvertUTCDateTimeToCFAbsoluteTime and
 *    CFTimeZoneGetSecondsFromGMT instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in UTCUtils 1.0 and later
 */
extern OSStatus 
ConvertLocalTimeToUTC(
  UInt32    localSeconds,
  UInt32 *  utcSeconds)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  ConvertUTCToLocalTime()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use
 *    UCConvertUTCDateTimeToCFAbsoluteTime/CFTimeZoneGetSecondsFromGMT
 *    instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    UCConvertUTCDateTimeToCFAbsoluteTime and
 *    CFTimeZoneGetSecondsFromGMT instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in UTCUtils 1.0 and later
 */
extern OSStatus 
ConvertUTCToLocalTime(
  UInt32    utcSeconds,
  UInt32 *  localSeconds)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* 64 bit clock conversion routines */
/*
 *  ConvertUTCToLocalDateTime()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use
 *    UCConvertUTCDateTimeToCFAbsoluteTime/CFTimeZoneGetSecondsFromGMT
 *    instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    UCConvertUTCDateTimeToCFAbsoluteTime and
 *    CFTimeZoneGetSecondsFromGMT instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in UTCUtils 1.0 and later
 */
extern OSStatus 
ConvertUTCToLocalDateTime(
  const UTCDateTime *  utcDateTime,
  LocalDateTime *      localDateTime)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  ConvertLocalToUTCDateTime()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use
 *    UCConvertUTCDateTimeToCFAbsoluteTime/CFTimeZoneGetSecondsFromGMT
 *    instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    UCConvertUTCDateTimeToCFAbsoluteTime and
 *    CFTimeZoneGetSecondsFromGMT instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in UTCUtils 1.0 and later
 */
extern OSStatus 
ConvertLocalToUTCDateTime(
  const LocalDateTime *  localDateTime,
  UTCDateTime *          utcDateTime)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/* Getter and Setter Clock routines using 64 Bit values */
/*
 *  GetUTCDateTime()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFAbsoluteTimeGetCurrent instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFAbsoluteTimeGetCurrent instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in UTCUtils 1.0 and later
 */
extern OSStatus 
GetUTCDateTime(
  UTCDateTime *  utcDateTime,
  OptionBits     options)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  SetUTCDateTime()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use settimeofday (2) instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Setting the time requires
 *    root privileges. If you must, use settimeofday (2)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in UTCUtils 1.0 and later
 */
extern OSStatus 
SetUTCDateTime(
  const UTCDateTime *  utcDateTime,
  OptionBits           options)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  GetLocalDateTime()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFAbsoluteTimeGetCurrent/CFTimeZoneGetSecondsFromGMT instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFAbsoluteTimeGetCurrent and CFTimeZoneGetSecondsFromGMT instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in UTCUtils 1.0 and later
 */
extern OSStatus 
GetLocalDateTime(
  LocalDateTime *  localDateTime,
  OptionBits       options)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  SetLocalDateTime()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    it without replacement
 *  
 *  Discussion:
 *    This function is no longer recommended. There is no replacement.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in UTCUtils 1.0 and later
 */
extern OSStatus 
SetLocalDateTime(
  const LocalDateTime *  localDateTime,
  OptionBits             options)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


#endif  /* !__LP64__ */


#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __UTCUTILS__ */


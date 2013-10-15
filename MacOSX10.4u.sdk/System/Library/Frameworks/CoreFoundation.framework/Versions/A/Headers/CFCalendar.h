/*	CFCalendar.h
	Copyright (c) 2004-2005, Apple, Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFCALENDAR__)
#define __COREFOUNDATION_CFCALENDAR__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFLocale.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFTimeZone.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct __CFCalendar * CFCalendarRef;

CF_EXPORT
CFTypeID CFCalendarGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
CFCalendarRef CFCalendarCopyCurrent(void) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
CFCalendarRef CFCalendarCreateWithIdentifier(CFAllocatorRef allocator, CFStringRef identifier) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
	// Create a calendar.  The identifiers are the kCF*Calendar
	// constants in CFLocale.h.

CF_EXPORT
CFStringRef CFCalendarGetIdentifier(CFCalendarRef calendar) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
	// Returns the calendar's identifier.

CF_EXPORT
CFLocaleRef CFCalendarCopyLocale(CFCalendarRef calendar) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
void CFCalendarSetLocale(CFCalendarRef calendar, CFLocaleRef locale) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
CFTimeZoneRef CFCalendarCopyTimeZone(CFCalendarRef calendar) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
void CFCalendarSetTimeZone(CFCalendarRef calendar, CFTimeZoneRef tz) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
CFIndex CFCalendarGetFirstWeekday(CFCalendarRef calendar) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
void CFCalendarSetFirstWeekday(CFCalendarRef calendar, CFIndex wkdy) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
CFIndex CFCalendarGetMinimumDaysInFirstWeek(CFCalendarRef calendar) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
void CFCalendarSetMinimumDaysInFirstWeek(CFCalendarRef calendar, CFIndex mwd) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


typedef enum {
	kCFCalendarUnitEra = (1 << 1),
	kCFCalendarUnitYear = (1 << 2),
	kCFCalendarUnitMonth = (1 << 3),
	kCFCalendarUnitDay = (1 << 4),
	kCFCalendarUnitHour = (1 << 5),
	kCFCalendarUnitMinute = (1 << 6),
	kCFCalendarUnitSecond = (1 << 7),
	kCFCalendarUnitWeek = (1 << 8),
	kCFCalendarUnitWeekday = (1 << 9),
	kCFCalendarUnitWeekdayOrdinal = (1 << 10)
} CFCalendarUnit;

CF_EXPORT
CFRange CFCalendarGetMinimumRangeOfUnit(CFCalendarRef calendar, CFCalendarUnit unit) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
CFRange CFCalendarGetMaximumRangeOfUnit(CFCalendarRef calendar, CFCalendarUnit unit) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
CFRange CFCalendarGetRangeOfUnit(CFCalendarRef calendar, CFCalendarUnit smallerUnit, CFCalendarUnit biggerUnit, CFAbsoluteTime at) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
CFIndex CFCalendarGetOrdinalityOfUnit(CFCalendarRef calendar, CFCalendarUnit smallerUnit, CFCalendarUnit biggerUnit, CFAbsoluteTime at) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


CF_EXPORT
Boolean CFCalendarComposeAbsoluteTime(CFCalendarRef calendar, /* out */ CFAbsoluteTime *at, const unsigned char *componentDesc, ...) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
Boolean CFCalendarDecomposeAbsoluteTime(CFCalendarRef calendar, CFAbsoluteTime at, const unsigned char *componentDesc, ...) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


enum {
    kCFCalendarComponentsWrap = (1 << 0)  // option for adding
};

CF_EXPORT
Boolean CFCalendarAddComponents(CFCalendarRef calendar, /* inout */ CFAbsoluteTime *at, CFOptionFlags options, const unsigned char *componentDesc, ...) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
Boolean CFCalendarGetComponentDifference(CFCalendarRef calendar, CFAbsoluteTime startingAT, CFAbsoluteTime resultAT, CFOptionFlags options, const unsigned char *componentDesc, ...) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


#if defined(__cplusplus)
}
#endif

#endif

#endif /* ! __COREFOUNDATION_CFCALENDAR__ */


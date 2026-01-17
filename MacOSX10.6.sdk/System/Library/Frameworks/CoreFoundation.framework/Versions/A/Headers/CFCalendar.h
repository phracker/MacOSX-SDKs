/*	CFCalendar.h
	Copyright (c) 2004-2009, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFCALENDAR__)
#define __COREFOUNDATION_CFCALENDAR__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFLocale.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFTimeZone.h>

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

CF_EXTERN_C_BEGIN

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


enum {
	kCFCalendarUnitEra = (1UL << 1),
	kCFCalendarUnitYear = (1UL << 2),
	kCFCalendarUnitMonth = (1UL << 3),
	kCFCalendarUnitDay = (1UL << 4),
	kCFCalendarUnitHour = (1UL << 5),
	kCFCalendarUnitMinute = (1UL << 6),
	kCFCalendarUnitSecond = (1UL << 7),
	kCFCalendarUnitWeek = (1UL << 8),
	kCFCalendarUnitWeekday = (1UL << 9),
	kCFCalendarUnitWeekdayOrdinal = (1UL << 10),
#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED
	kCFCalendarUnitQuarter = (1UL << 11),
#endif
};
typedef CFOptionFlags CFCalendarUnit;

CF_EXPORT
CFRange CFCalendarGetMinimumRangeOfUnit(CFCalendarRef calendar, CFCalendarUnit unit) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
CFRange CFCalendarGetMaximumRangeOfUnit(CFCalendarRef calendar, CFCalendarUnit unit) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
CFRange CFCalendarGetRangeOfUnit(CFCalendarRef calendar, CFCalendarUnit smallerUnit, CFCalendarUnit biggerUnit, CFAbsoluteTime at) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
CFIndex CFCalendarGetOrdinalityOfUnit(CFCalendarRef calendar, CFCalendarUnit smallerUnit, CFCalendarUnit biggerUnit, CFAbsoluteTime at) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
Boolean CFCalendarGetTimeRangeOfUnit(CFCalendarRef calendar, CFCalendarUnit unit, CFAbsoluteTime at, CFAbsoluteTime *startp, CFTimeInterval *tip) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

CF_EXPORT
Boolean CFCalendarComposeAbsoluteTime(CFCalendarRef calendar, /* out */ CFAbsoluteTime *at, const char *componentDesc, ...) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
Boolean CFCalendarDecomposeAbsoluteTime(CFCalendarRef calendar, CFAbsoluteTime at, const char *componentDesc, ...) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


enum {
    kCFCalendarComponentsWrap = (1UL << 0)  // option for adding
};

CF_EXPORT
Boolean CFCalendarAddComponents(CFCalendarRef calendar, /* inout */ CFAbsoluteTime *at, CFOptionFlags options, const char *componentDesc, ...) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CF_EXPORT
Boolean CFCalendarGetComponentDifference(CFCalendarRef calendar, CFAbsoluteTime startingAT, CFAbsoluteTime resultAT, CFOptionFlags options, const char *componentDesc, ...) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


CF_EXTERN_C_END

#endif

#endif /* ! __COREFOUNDATION_CFCALENDAR__ */


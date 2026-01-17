//
//  EventKitDefines.h
//  EventKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define EVENTKIT_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define EVENTKIT_EXTERN	        extern __attribute__((visibility ("default")))
#endif

#define EVENTKIT_CLASS_AVAILABLE(_macIntro, _iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(_macIntro, _iphoneIntro)


// an NSDate with no fractional seconds will use a tagged pointer, which is much more efficient to create/store
#define EK_LOSE_FRACTIONAL_SECONDS(date) ({__typeof__(date) __datevalue = (date); (__datevalue ? [NSDate dateWithTimeIntervalSinceReferenceDate:floor([__datevalue timeIntervalSinceReferenceDate])] : nil); })

#define DATE_COMPONENTS (NSEraCalendarUnit | NSYearCalendarUnit | NSMonthCalendarUnit | NSDayCalendarUnit)
#define DATETIME_COMPONENTS (DATE_COMPONENTS | NSHourCalendarUnit | NSMinuteCalendarUnit | NSSecondCalendarUnit)

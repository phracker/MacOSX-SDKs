//
//  EventKitDefines.h
//  EventKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#define EVENTKIT_EXTERN		extern "C" __attribute__((visibility ("default")))
#else
#define EVENTKIT_EXTERN	        extern __attribute__((visibility ("default")))
#endif

#define EVENTKIT_CLASS_AVAILABLE(_macIntro, _iphoneIntro) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(_macIntro, _iphoneIntro)


static inline void NS_DEPRECATED_MAC(10_8, 10_10) EK_LOSE_FRACTIONAL_SECONDS_DO_NOT_USE (void) { ; }
// an NSDate with no fractional seconds will use a tagged pointer, which is much more efficient to create/store
#define EK_LOSE_FRACTIONAL_SECONDS(date) ({EK_LOSE_FRACTIONAL_SECONDS_DO_NOT_USE(); __typeof__(date) __datevalue = (date); (__datevalue ? [NSDate dateWithTimeIntervalSinceReferenceDate:floor([__datevalue timeIntervalSinceReferenceDate])] : nil); })

static inline void NS_DEPRECATED_MAC(10_8, 10_10) DATE_COMPONENTS_DO_NOT_USE (void) { ; }
#define DATE_COMPONENTS ({DATE_COMPONENTS_DO_NOT_USE(); (NSCalendarUnitEra | NSCalendarUnitYear | NSCalendarUnitMonth | NSCalendarUnitDay); })

static inline void NS_DEPRECATED_MAC(10_8, 10_10) DATETIME_COMPONENTS_DO_NOT_USE (void) { ; }
#define DATETIME_COMPONENTS ({DATETIME_COMPONENTS_DO_NOT_USE(); (DATE_COMPONENTS | NSCalendarUnitHour | NSCalendarUnitMinute | NSCalendarUnitSecond); })

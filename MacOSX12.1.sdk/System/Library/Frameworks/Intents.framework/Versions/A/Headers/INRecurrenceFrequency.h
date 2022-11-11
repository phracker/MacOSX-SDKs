//
//  INRecurrenceFrequency.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#ifndef INRecurrenceFrequency_h
#define INRecurrenceFrequency_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INRecurrenceFrequency) {
    INRecurrenceFrequencyUnknown = 0,
    INRecurrenceFrequencyMinute,
    INRecurrenceFrequencyHourly,
    INRecurrenceFrequencyDaily,
    INRecurrenceFrequencyWeekly,
    INRecurrenceFrequencyMonthly,
    INRecurrenceFrequencyYearly,
} API_AVAILABLE(ios(11.0), macos(10.13), watchos(4.0)) API_UNAVAILABLE(tvos);

#endif // INRecurrenceFrequency_h

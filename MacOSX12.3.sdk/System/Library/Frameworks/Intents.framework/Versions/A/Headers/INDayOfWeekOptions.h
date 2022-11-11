//
//  INDayOfWeekOptions.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INDayOfWeekOptions_h
#define INDayOfWeekOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INDayOfWeekOptions) {
    INDayOfWeekOptionMonday = (1UL << 0),
    INDayOfWeekOptionTuesday = (1UL << 1),
    INDayOfWeekOptionWednesday = (1UL << 2),
    INDayOfWeekOptionThursday = (1UL << 3),
    INDayOfWeekOptionFriday = (1UL << 4),
    INDayOfWeekOptionSaturday = (1UL << 5),
    INDayOfWeekOptionSunday = (1UL << 6),
} API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);

#endif // INDayOfWeekOptions_h

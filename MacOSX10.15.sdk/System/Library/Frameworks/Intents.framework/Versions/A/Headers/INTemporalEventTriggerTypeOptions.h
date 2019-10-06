//
//  INTemporalEventTriggerTypeOptions.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef INTemporalEventTriggerTypeOptions_h
#define INTemporalEventTriggerTypeOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INTemporalEventTriggerTypeOptions) {
    INTemporalEventTriggerTypeOptionNotScheduled = (1UL << 0),
    INTemporalEventTriggerTypeOptionScheduledNonRecurring = (1UL << 1),
    INTemporalEventTriggerTypeOptionScheduledRecurring = (1UL << 2),
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macosx);

#endif // INTemporalEventTriggerTypeOptions_h

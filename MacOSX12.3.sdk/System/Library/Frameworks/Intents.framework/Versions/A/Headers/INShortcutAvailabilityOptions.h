//
//  INShortcutAvailabilityOptions.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INShortcutAvailabilityOptions_h
#define INShortcutAvailabilityOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INShortcutAvailabilityOptions) {
    INShortcutAvailabilityOptionSleepMindfulness = (1UL << 0),
    INShortcutAvailabilityOptionSleepJournaling = (1UL << 1),
    INShortcutAvailabilityOptionSleepMusic = (1UL << 2),
    INShortcutAvailabilityOptionSleepPodcasts = (1UL << 3),
    INShortcutAvailabilityOptionSleepReading = (1UL << 4),
    INShortcutAvailabilityOptionSleepWrapUpYourDay = (1UL << 5),
    INShortcutAvailabilityOptionSleepYogaAndStretching = (1UL << 6),
} API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);

#endif // INShortcutAvailabilityOptions_h

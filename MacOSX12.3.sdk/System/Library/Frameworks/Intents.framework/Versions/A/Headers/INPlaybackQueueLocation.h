//
//  INPlaybackQueueLocation.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INPlaybackQueueLocation_h
#define INPlaybackQueueLocation_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INPlaybackQueueLocation) {
    INPlaybackQueueLocationUnknown = 0,
    INPlaybackQueueLocationNow,
    INPlaybackQueueLocationNext,
    INPlaybackQueueLocationLater,
} API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0)) API_UNAVAILABLE(macos);

#endif // INPlaybackQueueLocation_h

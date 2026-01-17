//
//  INTaskPriority.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#ifndef INTaskPriority_h
#define INTaskPriority_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INTaskPriority) {
    INTaskPriorityUnknown = 0,
    INTaskPriorityNotFlagged,
    INTaskPriorityFlagged,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos, tvos);

#endif // INTaskPriority_h

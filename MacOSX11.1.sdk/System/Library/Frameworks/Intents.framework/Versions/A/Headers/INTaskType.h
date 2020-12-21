//
//  INTaskType.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#ifndef INTaskType_h
#define INTaskType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INTaskType) {
    INTaskTypeUnknown = 0,
    INTaskTypeNotCompletable,
    INTaskTypeCompletable,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos, tvos);

#endif // INTaskType_h

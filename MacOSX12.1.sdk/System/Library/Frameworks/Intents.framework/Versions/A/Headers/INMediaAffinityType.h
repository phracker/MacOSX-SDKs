//
//  INMediaAffinityType.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#ifndef INMediaAffinityType_h
#define INMediaAffinityType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INMediaAffinityType) {
    INMediaAffinityTypeUnknown = 0,
    INMediaAffinityTypeLike,
    INMediaAffinityTypeDislike,
} API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0)) API_UNAVAILABLE(macos);

#endif // INMediaAffinityType_h

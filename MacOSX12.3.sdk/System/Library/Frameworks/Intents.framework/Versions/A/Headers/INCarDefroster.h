//
//  INCarDefroster.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INCarDefroster_h
#define INCarDefroster_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCarDefroster) {
    INCarDefrosterUnknown = 0,
    INCarDefrosterFront,
    INCarDefrosterRear,
    INCarDefrosterAll,
} API_DEPRECATED("INCarDefroster is deprecated. There is no replacement.", ios(10.0, 15.0)) API_UNAVAILABLE(macos, watchos, tvos);

#endif // INCarDefroster_h

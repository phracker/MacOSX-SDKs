//
//  INRelativeReference.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#ifndef INRelativeReference_h
#define INRelativeReference_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INRelativeReference) {
    INRelativeReferenceUnknown = 0,
    INRelativeReferenceNext,
    INRelativeReferencePrevious,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

#endif // INRelativeReference_h

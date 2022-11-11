//
//  INMediaReference.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INMediaReference_h
#define INMediaReference_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INMediaReference) {
    INMediaReferenceUnknown = 0,
    INMediaReferenceCurrentlyPlaying,
    INMediaReferenceMy API_AVAILABLE(ios(14.5), watchos(7.3), tvos(14.5)) API_UNAVAILABLE(macos),
} API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0)) API_UNAVAILABLE(macos);

#endif // INMediaReference_h

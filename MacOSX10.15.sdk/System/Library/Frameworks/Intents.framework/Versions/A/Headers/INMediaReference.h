//
//  INMediaReference.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef INMediaReference_h
#define INMediaReference_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INMediaReference) {
    INMediaReferenceUnknown = 0,
    INMediaReferenceCurrentlyPlaying,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macosx);

#endif // INMediaReference_h

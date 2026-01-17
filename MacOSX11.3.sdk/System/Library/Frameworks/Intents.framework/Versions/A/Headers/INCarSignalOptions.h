//
//  INCarSignalOptions.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#ifndef INCarSignalOptions_h
#define INCarSignalOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INCarSignalOptions) {
    INCarSignalOptionAudible = (1UL << 0),
    INCarSignalOptionVisible = (1UL << 1),
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

#endif // INCarSignalOptions_h

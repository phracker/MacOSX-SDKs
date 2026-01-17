//
//  INMediaDestinationType.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#ifndef INMediaDestinationType_h
#define INMediaDestinationType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INMediaDestinationType) {
    INMediaDestinationTypeUnknown = 0,
    INMediaDestinationTypeLibrary,
    INMediaDestinationTypePlaylist,
} API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0)) API_UNAVAILABLE(macos);

#endif // INMediaDestinationType_h

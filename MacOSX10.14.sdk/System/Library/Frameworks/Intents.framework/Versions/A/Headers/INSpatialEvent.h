//
//  INSpatialEvent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INSpatialEvent_h
#define INSpatialEvent_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INSpatialEvent) {
    INSpatialEventUnknown = 0,
    INSpatialEventArrive,
    INSpatialEventDepart,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INSpatialEvent_h

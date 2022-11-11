//
//  INCarAirCirculationMode.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#ifndef INCarAirCirculationMode_h
#define INCarAirCirculationMode_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCarAirCirculationMode) {
    INCarAirCirculationModeUnknown = 0,
    INCarAirCirculationModeFreshAir,
    INCarAirCirculationModeRecirculateAir,
} API_DEPRECATED("INCarAirCirculationMode is deprecated. There is no replacement.", ios(10.0, 15.0)) API_UNAVAILABLE(macos, watchos, tvos);

#endif // INCarAirCirculationMode_h

//
//  INCarAirCirculationMode.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#ifndef INCarAirCirculationMode_h
#define INCarAirCirculationMode_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCarAirCirculationMode) {
    INCarAirCirculationModeUnknown = 0,
    INCarAirCirculationModeFreshAir,
    INCarAirCirculationModeRecirculateAir,
} API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

#endif // INCarAirCirculationMode_h

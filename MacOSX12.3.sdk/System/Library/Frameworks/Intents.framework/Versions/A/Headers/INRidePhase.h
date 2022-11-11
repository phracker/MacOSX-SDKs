//
//  INRidePhase.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INRidePhase_h
#define INRidePhase_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INRidePhase) {
    INRidePhaseUnknown = 0,
    INRidePhaseReceived,
    INRidePhaseConfirmed,
    INRidePhaseOngoing,
    INRidePhaseCompleted,
    INRidePhaseApproachingPickup,
    INRidePhasePickup,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

#endif // INRidePhase_h

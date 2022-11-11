//
//  INReservationActionType.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INReservationActionType_h
#define INReservationActionType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INReservationActionType) {
    INReservationActionTypeUnknown = 0,
    INReservationActionTypeCheckIn,
} API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0)) API_UNAVAILABLE(tvos);

#endif // INReservationActionType_h

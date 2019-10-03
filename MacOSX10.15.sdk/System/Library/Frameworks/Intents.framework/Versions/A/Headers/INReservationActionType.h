//
//  INReservationActionType.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef INReservationActionType_h
#define INReservationActionType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INReservationActionType) {
    INReservationActionTypeUnknown = 0,
    INReservationActionTypeCheckIn,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macosx);

#endif // INReservationActionType_h

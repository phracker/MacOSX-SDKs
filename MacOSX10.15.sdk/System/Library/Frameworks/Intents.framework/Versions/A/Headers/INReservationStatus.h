//
//  INReservationStatus.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef INReservationStatus_h
#define INReservationStatus_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INReservationStatus) {
    INReservationStatusUnknown = 0,
    INReservationStatusCanceled,
    INReservationStatusPending,
    INReservationStatusHold,
    INReservationStatusConfirmed,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macosx);

#endif // INReservationStatus_h

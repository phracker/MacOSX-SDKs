//
//  INFlightReservation.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/INReservation.h>

@class INFlight;
@class INSeat;
@class INReservationAction;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macosx)
@interface INFlightReservation : INReservation <NSCopying, NSSecureCoding>

- (instancetype)initWithItemReference:(INSpeakableString *)itemReference
                    reservationNumber:(nullable NSString *)reservationNumber
                          bookingTime:(nullable NSDate *)bookingTime
                    reservationStatus:(INReservationStatus)reservationStatus
                reservationHolderName:(nullable NSString *)reservationHolderName
                              actions:(nullable NSArray<INReservationAction *> *)actions
                         reservedSeat:(nullable INSeat *)reservedSeat
                               flight:(INFlight *)flight NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSeat *reservedSeat;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INFlight *flight;

@end

NS_ASSUME_NONNULL_END

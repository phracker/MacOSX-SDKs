//
//  INFlightReservation.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/INReservation.h>

@class INFlight;
@class INSeat;
@class INReservationAction;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INFlightReservation : INReservation <NSCopying, NSSecureCoding>

- (instancetype)initWithItemReference:(INSpeakableString *)itemReference
                    reservationNumber:(nullable NSString *)reservationNumber
                          bookingTime:(nullable NSDate *)bookingTime
                    reservationStatus:(INReservationStatus)reservationStatus
                reservationHolderName:(nullable NSString *)reservationHolderName
                              actions:(nullable NSArray<INReservationAction *> *)actions
                                  URL:(nullable NSURL *)URL
                         reservedSeat:(nullable INSeat *)reservedSeat
                               flight:(INFlight *)flight NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(14.0), watchos(7.0));

- (instancetype)initWithItemReference:(INSpeakableString *)itemReference
                    reservationNumber:(nullable NSString *)reservationNumber
                          bookingTime:(nullable NSDate *)bookingTime
                    reservationStatus:(INReservationStatus)reservationStatus
                reservationHolderName:(nullable NSString *)reservationHolderName
                              actions:(nullable NSArray<INReservationAction *> *)actions
                         reservedSeat:(nullable INSeat *)reservedSeat
                               flight:(INFlight *)flight;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSeat *reservedSeat;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INFlight *flight;

@end

NS_ASSUME_NONNULL_END

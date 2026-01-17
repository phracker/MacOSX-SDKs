//
//  INBusReservation.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/INReservation.h>

@class INBusTrip;
@class INReservation;
@class INSeat;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), macos(11.0), watchos(7.0))
API_UNAVAILABLE(tvos)
@interface INBusReservation : INReservation <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithItemReference:(INSpeakableString *)itemReference
                    reservationNumber:(nullable NSString *)reservationNumber
                          bookingTime:(nullable NSDate *)bookingTime
                    reservationStatus:(INReservationStatus)reservationStatus
                reservationHolderName:(nullable NSString *)reservationHolderName
                              actions:(nullable NSArray<INReservationAction *> *)actions
                                  URL:(nullable NSURL *)URL
                         reservedSeat:(nullable INSeat *)reservedSeat
                              busTrip:(nullable INBusTrip *)busTrip NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSeat *reservedSeat;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INBusTrip *busTrip;

@end

NS_ASSUME_NONNULL_END

//
//  INRestaurantReservation.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/INReservation.h>

@class CLPlacemark;
@class INDateComponentsRange;
@class INSpeakableString;
@class INReservationAction;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INRestaurantReservation : INReservation <NSCopying, NSSecureCoding>

- (instancetype)initWithItemReference:(INSpeakableString *)itemReference
                    reservationNumber:(nullable NSString *)reservationNumber
                          bookingTime:(nullable NSDate *)bookingTime
                    reservationStatus:(INReservationStatus)reservationStatus
                reservationHolderName:(nullable NSString *)reservationHolderName
                              actions:(nullable NSArray<INReservationAction *> *)actions
                                  URL:(nullable NSURL *)URL
                  reservationDuration:(INDateComponentsRange *)reservationDuration
                            partySize:(nullable NSNumber *)partySize
                   restaurantLocation:(CLPlacemark *)restaurantLocation NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(14.0), watchos(7.0));

- (instancetype)initWithItemReference:(INSpeakableString *)itemReference
                    reservationNumber:(nullable NSString *)reservationNumber
                          bookingTime:(nullable NSDate *)bookingTime
                    reservationStatus:(INReservationStatus)reservationStatus
                reservationHolderName:(nullable NSString *)reservationHolderName
                              actions:(nullable NSArray<INReservationAction *> *)actions
                  reservationDuration:(INDateComponentsRange *)reservationDuration
                            partySize:(nullable NSNumber *)partySize
                   restaurantLocation:(CLPlacemark *)restaurantLocation NS_REFINED_FOR_SWIFT;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INDateComponentsRange *reservationDuration;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *partySize NS_REFINED_FOR_SWIFT;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CLPlacemark *restaurantLocation;

@end

NS_ASSUME_NONNULL_END

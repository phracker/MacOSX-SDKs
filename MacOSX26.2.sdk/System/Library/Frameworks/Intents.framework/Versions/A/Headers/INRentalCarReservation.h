//
//  INRentalCarReservation.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/INReservation.h>

@class CLPlacemark;
@class INDateComponentsRange;
@class INRentalCar;
@class INReservation;
@class INReservationAction;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INRentalCarReservation : INReservation <NSCopying, NSSecureCoding>

- (instancetype)initWithItemReference:(INSpeakableString *)itemReference
                    reservationNumber:(nullable NSString *)reservationNumber
                          bookingTime:(nullable NSDate *)bookingTime
                    reservationStatus:(INReservationStatus)reservationStatus
                reservationHolderName:(nullable NSString *)reservationHolderName
                              actions:(nullable NSArray<INReservationAction *> *)actions
                                  URL:(nullable NSURL *)URL
                            rentalCar:(INRentalCar *)rentalCar
                       rentalDuration:(INDateComponentsRange *)rentalDuration
                       pickupLocation:(nullable CLPlacemark *)pickupLocation
                      dropOffLocation:(nullable CLPlacemark *)dropOffLocation NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(14.0), watchos(7.0));

- (instancetype)initWithItemReference:(INSpeakableString *)itemReference
                    reservationNumber:(nullable NSString *)reservationNumber
                          bookingTime:(nullable NSDate *)bookingTime
                    reservationStatus:(INReservationStatus)reservationStatus
                reservationHolderName:(nullable NSString *)reservationHolderName
                              actions:(nullable NSArray<INReservationAction *> *)actions
                            rentalCar:(INRentalCar *)rentalCar
                       rentalDuration:(INDateComponentsRange *)rentalDuration
                       pickupLocation:(nullable CLPlacemark *)pickupLocation
                      dropOffLocation:(nullable CLPlacemark *)dropOffLocation;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INRentalCar *rentalCar;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INDateComponentsRange *rentalDuration;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *pickupLocation;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *dropOffLocation;

@end

NS_ASSUME_NONNULL_END

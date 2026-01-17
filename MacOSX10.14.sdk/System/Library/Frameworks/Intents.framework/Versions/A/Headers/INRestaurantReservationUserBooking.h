//
//  INRestaurantReservationUserBooking.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>
#import <Intents/INRestaurantReservationBooking.h>
#import <Intents/INRestaurantGuest.h>
#import <Intents/INRestaurantOffer.h>

typedef NS_ENUM (NSUInteger, INRestaurantReservationUserBookingStatus) {
    INRestaurantReservationUserBookingStatusPending,
    INRestaurantReservationUserBookingStatusConfirmed,
    INRestaurantReservationUserBookingStatusDenied
};

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
NS_ASSUME_NONNULL_BEGIN
@interface INRestaurantReservationUserBooking : INRestaurantReservationBooking <NSCopying>

- (instancetype)initWithRestaurant:(INRestaurant *)restaurant bookingDate:(NSDate *)bookingDate partySize:(NSUInteger)partySize bookingIdentifier:(NSString *)bookingIdentifier guest:(INRestaurantGuest *)guest status:(INRestaurantReservationUserBookingStatus)status dateStatusModified:(NSDate *)dateStatusModified;

@property (copy, NS_NONATOMIC_IOSONLY) INRestaurantGuest *guest;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *advisementText; // a string representing restaurant specific information related to the reservation: things like late policies, parking instructions, or specials
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantOffer *selectedOffer; // an offer, if any, attached to the booking
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *guestProvidedSpecialRequestText; // any user-specified special request text submitted with the reservation
@property (NS_NONATOMIC_IOSONLY) INRestaurantReservationUserBookingStatus status; // an enum indicating whether a booking was denied, pending, or confirmed
@property (copy, NS_NONATOMIC_IOSONLY) NSDate *dateStatusModified; // date indicating when the status was updated to its current value

@end
NS_ASSUME_NONNULL_END

//
//  INGetAvailableRestaurantReservationBookingsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResponse.h>
#import <Intents/INRestaurantReservationBooking.h>
#import <Intents/INTermsAndConditions.h>

typedef NS_ENUM(NSInteger, INGetAvailableRestaurantReservationBookingsIntentCode) {
    INGetAvailableRestaurantReservationBookingsIntentCodeSuccess,
    INGetAvailableRestaurantReservationBookingsIntentCodeFailure,
    INGetAvailableRestaurantReservationBookingsIntentCodeFailureRequestUnsatisfiable,
    INGetAvailableRestaurantReservationBookingsIntentCodeFailureRequestUnspecified
};

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetAvailableRestaurantReservationBookingsIntentResponse : INIntentResponse

- (instancetype)initWithAvailableBookings:(NSArray<INRestaurantReservationBooking *> *)availableBookings code:(INGetAvailableRestaurantReservationBookingsIntentCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetAvailableRestaurantReservationBookingsIntentCode code;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *localizedRestaurantDescriptionText; // An optional string to be displayed in UI that allows the vendor to specify details or history about the restaurant.
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *localizedBookingAdvisementText; // An optional string to be displayed in UI that allows the vendor to detail things like specials or incentives.
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INTermsAndConditions *termsAndConditions; // An optional object allowing the vendor to display terms of use for its service
@property (readonly, NS_NONATOMIC_IOSONLY) NSArray<INRestaurantReservationBooking *> *availableBookings;

@end
NS_ASSUME_NONNULL_END

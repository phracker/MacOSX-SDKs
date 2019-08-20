//
//  INGetAvailableRestaurantReservationBookingDefaultsIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResponse.h>
#import <Intents/INImage.h>

typedef NS_ENUM(NSInteger, INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCode) {
    INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCodeSuccess,
    INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCodeFailure,
    INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCodeUnspecified
};

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetAvailableRestaurantReservationBookingDefaultsIntentResponse : INIntentResponse

@property (readonly, NS_NONATOMIC_IOSONLY) NSUInteger defaultPartySize; // default party size for an available bookings request
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSDate *defaultBookingDate; // default booking time for an available bookings request
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *maximumPartySize;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *minimumPartySize;
@property (copy, NS_NONATOMIC_IOSONLY) INImage *providerImage;

- (instancetype)initWithDefaultPartySize:(NSUInteger)defaultPartySize defaultBookingDate:(NSDate *)defaultBookingDate code:(INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetAvailableRestaurantReservationBookingDefaultsIntentResponseCode code;

@end
NS_ASSUME_NONNULL_END

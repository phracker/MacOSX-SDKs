//
//  INBookRestaurantReservationIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResponse.h>
#import <Intents/INRestaurantReservationUserBooking.h>

typedef NS_ENUM(NSInteger, INBookRestaurantReservationIntentCode) {
    INBookRestaurantReservationIntentCodeSuccess = 0,
    INBookRestaurantReservationIntentCodeDenied,
    INBookRestaurantReservationIntentCodeFailure,
    INBookRestaurantReservationIntentCodeFailureRequiringAppLaunch,
    INBookRestaurantReservationIntentCodeFailureRequiringAppLaunchMustVerifyCredentials,
    INBookRestaurantReservationIntentCodeFailureRequiringAppLaunchServiceTemporarilyUnavailable
};

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INBookRestaurantReservationIntentResponse : INIntentResponse

- (instancetype)initWithCode:(INBookRestaurantReservationIntentCode)code userActivity:(nullable NSUserActivity *)userActivity;

@property (readonly, NS_NONATOMIC_IOSONLY) INBookRestaurantReservationIntentCode code;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantReservationUserBooking *userBooking; // the userBooking that has been confirmed

@end
NS_ASSUME_NONNULL_END

//
//  INGetRestaurantGuestIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResponse.h>
#import <Intents/INRestaurantGuest.h>
#import <Intents/INRestaurantGuestDisplayPreferences.h>

typedef NS_ENUM(NSInteger, INGetRestaurantGuestIntentResponseCode) {
    INGetRestaurantGuestIntentResponseCodeSuccess,
    INGetRestaurantGuestIntentResponseCodeFailure,
};

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetRestaurantGuestIntentResponse : INIntentResponse

- (instancetype)initWithCode:(INGetRestaurantGuestIntentResponseCode)code userActivity:(nullable NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantGuest *guest;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurantGuestDisplayPreferences *guestDisplayPreferences;

@property (readonly, NS_NONATOMIC_IOSONLY) INGetRestaurantGuestIntentResponseCode code;

@end
NS_ASSUME_NONNULL_END

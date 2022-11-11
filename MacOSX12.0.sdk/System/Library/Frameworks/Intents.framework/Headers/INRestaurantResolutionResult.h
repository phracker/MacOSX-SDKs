//
//  INRestaurantResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//
//  This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
//  http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntentResolutionResult.h>

@class INRestaurant;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macos, watchos, tvos)
@interface INRestaurantResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to proceed, with a given restaurant. The resolvedRestaurant can be different than the original restaurant. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedRestaurant:(INRestaurant *)resolvedRestaurant NS_SWIFT_NAME(success(with:));

// This resolution result is to disambiguate between the provided restaurants.
+ (instancetype)disambiguationWithRestaurantsToDisambiguate:(NSArray<INRestaurant *> *)restaurantsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to confirm if this is the restaurant with which the user wants to continue.
+ (instancetype)confirmationRequiredWithRestaurantToConfirm:(nullable INRestaurant *)restaurantToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

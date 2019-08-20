//
//  INGetUserCurrentRestaurantReservationBookingsIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>
#import <Intents/INRestaurant.h>
#import <Intents/INRestaurantResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetUserCurrentRestaurantReservationBookingsIntent : INIntent <NSCopying>

- (instancetype)initWithRestaurant:(nullable INRestaurant *)restaurant
             reservationIdentifier:(nullable NSString *)reservationIdentifier
            maximumNumberOfResults:(nullable NSNumber *)maximumNumberOfResults
     earliestBookingDateForResults:(nullable NSDate *)earliestBookingDateForResults API_AVAILABLE(ios(11.0));

@property (copy, nullable, NS_NONATOMIC_IOSONLY) INRestaurant *restaurant; // optional filter to just reservations at restaurant
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSString *reservationIdentifier; // optional filter to reservation with exact ID

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *maximumNumberOfResults; // if the caller has a preferred maximum number of results, one can optionally be specified. a nil here leaves it up to the extension
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *earliestBookingDateForResults; // specifies the earliest booking date desired for results, including dates in the past

@end

@class INGetUserCurrentRestaurantReservationBookingsIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@protocol INGetUserCurrentRestaurantReservationBookingsIntentHandling <NSObject>

/*!
 @abstract Handling method - Execute the task represented by the INGetUserCurrentRestaurantReservationBookingsIntent that's passed in
 @discussion This method is called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  intent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INGetUserCurrentRestaurantReservationBookingsIntentResponse
 
 */

- (void)handleGetUserCurrentRestaurantReservationBookings:(INGetUserCurrentRestaurantReservationBookingsIntent *)intent completion:(void (^)(INGetUserCurrentRestaurantReservationBookingsIntentResponse *response))completion NS_SWIFT_NAME(handle(getUserCurrentRestaurantReservationBookings:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  intent The input intent
 @param  completion The response block contains an INGetUserCurrentRestaurantReservationBookingsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INGetUserCurrentRestaurantReservationBookingsIntentResponse
 
 */

- (void)confirmGetUserCurrentRestaurantReservationBookings:(INGetUserCurrentRestaurantReservationBookingsIntent *)intent completion:(void (^)(INGetUserCurrentRestaurantReservationBookingsIntentResponse *response))completion NS_SWIFT_NAME(confirm(getUserCurrentRestaurantReservationBookings:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.
 
 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved
 
 @see INGetUserCurrentRestaurantReservationBookingsIntentResponse
 
 */

- (void)resolveRestaurantForGetUserCurrentRestaurantReservationBookings:(INGetUserCurrentRestaurantReservationBookingsIntent *)intent withCompletion:(void(^)(INRestaurantResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRestaurant(for:completion:));

@end

NS_ASSUME_NONNULL_END

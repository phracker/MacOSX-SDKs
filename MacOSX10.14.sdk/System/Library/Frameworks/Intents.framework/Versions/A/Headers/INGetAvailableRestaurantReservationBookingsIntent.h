//
//  INGetAvailableRestaurantReservationBookingsIntent.h
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
#import <Intents/INIntegerResolutionResult.h>
#import <Intents/INDateComponentsResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetAvailableRestaurantReservationBookingsIntent : INIntent <NSCopying>

- (instancetype)initWithRestaurant:(INRestaurant *)restaurant
                         partySize:(NSUInteger)partySize
    preferredBookingDateComponents:(nullable NSDateComponents *)preferredBookingDateComponents
            maximumNumberOfResults:(nullable NSNumber *)maximumNumberOfResults
     earliestBookingDateForResults:(nullable NSDate *)earliestBookingDateForResults
       latestBookingDateForResults:(nullable NSDate *)latestBookingDateForResults API_AVAILABLE(ios(11.0));

@property (copy, NS_NONATOMIC_IOSONLY) INRestaurant *restaurant;
@property (NS_NONATOMIC_IOSONLY) NSUInteger partySize;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *preferredBookingDateComponents;

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *maximumNumberOfResults; // if the caller has a preferred maximum number of results, one can optionally be specified. a nil here leaves it up to the extension

@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *earliestBookingDateForResults;
@property (copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *latestBookingDateForResults;

@end

@class INGetAvailableRestaurantReservationBookingsIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@protocol INGetAvailableRestaurantReservationBookingsIntentHandling <NSObject>

/*!
 @abstract Handling method - Execute the task represented by the INGetAvailableRestaurantReservationBookingsIntent that's passed in
 @discussion This method is called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  intent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INGetAvailableRestaurantReservationBookingsIntentResponse
 
 */

- (void)handleGetAvailableRestaurantReservationBookings:(INGetAvailableRestaurantReservationBookingsIntent *)intent completion:(void (^)(INGetAvailableRestaurantReservationBookingsIntentResponse *response))completion NS_SWIFT_NAME(handle(getAvailableRestaurantReservationBookings:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  intent The input intent
 @param  completion The response block contains an INGetAvailableRestaurantReservationBookingDefaultsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INGetAvailableRestaurantReservationBookingsIntentResponse
 
 */

- (void)confirmGetAvailableRestaurantReservationBookings:(INGetAvailableRestaurantReservationBookingsIntent *)intent completion:(void (^)(INGetAvailableRestaurantReservationBookingsIntentResponse *response))completion NS_SWIFT_NAME(confirm(getAvailableRestaurantReservationBookings:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion These methods are called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.
 
 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved
 
 @see INGetAvailableRestaurantReservationBookingsIntentResponse
 
 */

- (void)resolveRestaurantForGetAvailableRestaurantReservationBookings:(INGetAvailableRestaurantReservationBookingsIntent *)intent withCompletion:(void(^)(INRestaurantResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveRestaurant(for:completion:));
- (void)resolvePartySizeForGetAvailableRestaurantReservationBookings:(INGetAvailableRestaurantReservationBookingsIntent *)intent withCompletion:(void(^)(INIntegerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePartySize(for:completion:));
- (void)resolvePreferredBookingDateComponentsForGetAvailableRestaurantReservationBookings:(INGetAvailableRestaurantReservationBookingsIntent *)intent withCompletion:(void(^)(INDateComponentsResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePreferredBookingDateComponents(for:completion:));

@end

NS_ASSUME_NONNULL_END

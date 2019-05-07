//
//  INGetRestaurantGuestIntent.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//
// This API requires you to work with Apple Maps before your application can use it. For information on how to get started, please go to MapsConnect.
//
// http://mapsconnect.apple.com/info/extensions

#import <Intents/INIntent.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@interface INGetRestaurantGuestIntent : INIntent

@end

@class INGetRestaurantGuestIntentResponse;

API_AVAILABLE(ios(10.0))
API_UNAVAILABLE(macosx, watchos)
@protocol INGetRestaurantGuestIntentHandling <NSObject>

/*!
 @abstract Handling method - Execute the task represented by the INGetRestaurantGuestIntent that's passed in
 @discussion This method is called to actually execute the intent, the app must return a response for this intent and an NSUserActivity capturing the state that the app must be restored to at the end of handling this intent
 
 @param  intent The input intent
 @param  completion The response handling block to invoke with the response to handling the intent.
 
 @see  INGetRestaurantGuestIntentResponse
 
 */
- (void)handleGetRestaurantGuest:(INGetRestaurantGuestIntent *)intent completion:(void (^)(INGetRestaurantGuestIntentResponse *response))completion NS_SWIFT_NAME(handle(getRestaurantGuest:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion These methods are called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.
 
 @param  guestIntent The input intent
 @param  completion The response block contains an INGetRestaurantGuestIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INGetRestaurantGuestIntentResponse
 
 */

- (void)confirmGetRestaurantGuest:(INGetRestaurantGuestIntent *)guestIntent completion:(void (^)(INGetRestaurantGuestIntentResponse *response))completion NS_SWIFT_NAME(confirm(getRestaurantGuest:completion:));

@end
NS_ASSUME_NONNULL_END

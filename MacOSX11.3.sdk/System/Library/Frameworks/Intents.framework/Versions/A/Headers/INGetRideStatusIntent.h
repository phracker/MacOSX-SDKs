//
//  INGetRideStatusIntent.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INGetRideStatusIntent : INIntent

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

@class INGetRideStatusIntentResponse;

@protocol INGetRideStatusIntentResponseObserver;

/*!
 @abstract Protocol to declare support for handling an INGetRideStatusIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@protocol INGetRideStatusIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INGetRideStatusIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INGetRideStatusIntentResponse containing the details of the result of having executed the intent

 @see  INGetRideStatusIntentResponse
 */

- (void)handleGetRideStatus:(INGetRideStatusIntent *)intent
                 completion:(void (^)(INGetRideStatusIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

- (void)startSendingUpdatesForGetRideStatus:(INGetRideStatusIntent *)intent
                                 toObserver:(id<INGetRideStatusIntentResponseObserver>)observer NS_SWIFT_NAME(startSendingUpdates(for:to:));

- (void)stopSendingUpdatesForGetRideStatus:(INGetRideStatusIntent *)intent NS_SWIFT_NAME(stopSendingUpdates(for:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INGetRideStatusIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INGetRideStatusIntentResponse
 */

- (void)confirmGetRideStatus:(INGetRideStatusIntent *)intent
                  completion:(void (^)(INGetRideStatusIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

@end

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@protocol INGetRideStatusIntentResponseObserver <NSObject>

- (void)getRideStatusResponseDidUpdate:(INGetRideStatusIntentResponse *)response NS_SWIFT_NAME(didUpdate(getRideStatus:));

@end

NS_ASSUME_NONNULL_END

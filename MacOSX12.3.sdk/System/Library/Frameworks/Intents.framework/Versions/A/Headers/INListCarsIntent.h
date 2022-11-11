//
//  INListCarsIntent.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), watchos(7.0))
API_UNAVAILABLE(macos, tvos)
@interface INListCarsIntent : INIntent

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

@class INListCarsIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INListCarsIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(14.0), watchos(7.0))
API_UNAVAILABLE(macos, tvos)
@protocol INListCarsIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INListCarsIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INListCarsIntentResponse containing the details of the result of having executed the intent

 @see  INListCarsIntentResponse
 */

- (void)handleListCars:(INListCarsIntent *)intent
            completion:(void (^)(INListCarsIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INListCarsIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INListCarsIntentResponse
 */

- (void)confirmListCars:(INListCarsIntent *)intent
             completion:(void (^)(INListCarsIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

@end

NS_ASSUME_NONNULL_END

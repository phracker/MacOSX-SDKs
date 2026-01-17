//
//  INCancelRideIntent.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0))
API_UNAVAILABLE(watchos, macos)
@interface INCancelRideIntent : INIntent

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithRideIdentifier:(NSString *)rideIdentifier NS_DESIGNATED_INITIALIZER;
// Specifies the identifier of the ride to cancel.
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *rideIdentifier;

@end

@class INCancelRideIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INCancelRideIntent. By implementing this protocol, a class can provide logic for confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to confirm and handle the intent. The handling method is always called last, after confirming the intent.
 */

API_AVAILABLE(ios(11.0))
API_UNAVAILABLE(watchos, macos)
@protocol INCancelRideIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INCancelRideIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.
 
 @param  intent The input intent
 @param  completion The response handling block takes a INCancelRideIntentResponse containing the details of the result of having executed the intent
 
 @see  INCancelRideIntentResponse
 */

- (void)handleCancelRide:(INCancelRideIntent *)intent
              completion:(void (^)(INCancelRideIntentResponse *response))completion NS_SWIFT_NAME(handle(cancelRide:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system may not use the cancel ride intent.
 
 @param  intent The input intent
 @param  completion The response block contains an INCancelRideIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INCancelRideIntentResponse
 
 */

- (void)confirmCancelRide:(INCancelRideIntent *)intent
               completion:(void (^)(INCancelRideIntentResponse *response))completion NS_SWIFT_NAME(confirm(cancelRide:completion:));

@end

NS_ASSUME_NONNULL_END

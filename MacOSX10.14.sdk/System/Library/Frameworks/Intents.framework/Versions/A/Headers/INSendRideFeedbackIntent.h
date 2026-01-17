//
//  INSendRideFeedbackIntent.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>

@class INSendRideFeedbackIntentResponse, INCurrencyAmount;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0))
API_UNAVAILABLE(watchos, macos)
@interface INSendRideFeedbackIntent : INIntent

- (id)init NS_UNAVAILABLE;

- (instancetype)initWithRideIdentifier:(NSString *)rideIdentifier NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *rideIdentifier; // Specifies the identifier of the ride to send feedback for.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *rating; // Will be between 0 and 10 inclusive.
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) INCurrencyAmount *tip;

@end

/*!
 @abstract Protocol to declare support for handling an INSendRideFeedbackIntent. By implementing this protocol, a class can provide logic for confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The handling method is always called last, after confirming the intent.
 */

API_AVAILABLE(ios(11.0))
API_UNAVAILABLE(watchos, macos)
@protocol INSendRideFeedbackIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSendRideFeedbackIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.
 
 @param  sendRideFeedbackintent The input intent
 @param  completion The response handling block takes a INSendRideFeedbackIntentResponse containing the details of the result of having executed the intent
 
 @see  INSendRideFeedbackIntentResponse
 */

- (void)handleSendRideFeedback:(INSendRideFeedbackIntent *)sendRideFeedbackintent
                    completion:(void (^)(INSendRideFeedbackIntentResponse *response))completion NS_SWIFT_NAME(handle(sendRideFeedback:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will not allow calling of the handle method.
 
 @param  sendRideFeedbackIntent The input intent
 @param  completion The response block contains an INSendRideFeedbackIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.
 
 @see INSendRideFeedbackIntentResponse
 
 */

- (void)confirmSendRideFeedback:(INSendRideFeedbackIntent *)sendRideFeedbackIntent
                     completion:(void (^)(INSendRideFeedbackIntentResponse *response))completion NS_SWIFT_NAME(confirm(sendRideFeedback:completion:));

@end

NS_ASSUME_NONNULL_END

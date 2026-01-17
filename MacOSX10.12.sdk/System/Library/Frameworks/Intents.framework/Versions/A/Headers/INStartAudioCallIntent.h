//
//  INStartAudioCallIntent.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INPerson;
@class INPersonResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macosx(10.12), ios(10.0))
@interface INStartAudioCallIntent : INIntent

- (instancetype)initWithContacts:(nullable NSArray<INPerson *> *)contacts NS_DESIGNATED_INITIALIZER;

// Recipients of the audio call.
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INPerson *> *contacts;

@end

@class INStartAudioCallIntentResponse;

/*!
 @brief Protocol to declare support for handling an INStartAudioCallIntent 
 @abstract By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(macosx(10.12), ios(10.0))
@protocol INStartAudioCallIntentHandling <NSObject>

@required

/*!
 @brief handling method

 @abstract Execute the task represented by the INStartAudioCallIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  startAudioCallIntent The input intent
 @param  completion The response handling block takes a INStartAudioCallIntentResponse containing the details of the result of having executed the intent

 @see  INStartAudioCallIntentResponse
 */

- (void)handleStartAudioCall:(INStartAudioCallIntent *)intent
                  completion:(void (^)(INStartAudioCallIntentResponse *response))completion NS_SWIFT_NAME(handle(startAudioCall:completion:));

@optional

/*!
 @brief Confirmation method
 @abstract Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  startAudioCallIntent The input intent
 @param  completion The response block contains an INStartAudioCallIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INStartAudioCallIntentResponse

 */

- (void)confirmStartAudioCall:(INStartAudioCallIntent *)intent
                   completion:(void (^)(INStartAudioCallIntentResponse *response))completion NS_SWIFT_NAME(confirm(startAudioCall:completion:));

/*!
 @brief Resolution methods
 @abstract Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  startAudioCallIntent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult

 */

- (void)resolveContactsForStartAudioCall:(INStartAudioCallIntent *)intent
                          withCompletion:(void (^)(NSArray<INPersonResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveContacts(forStartAudioCall:with:));

@end

NS_ASSUME_NONNULL_END

//
//  INActivateCarSignalIntent.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarSignalOptions.h>

@class INCarSignalOptionsResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INActivateCarSignalIntent : INIntent

- (instancetype)initWithCarName:(nullable INSpeakableString *)carName
                        signals:(INCarSignalOptions)signals NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *carName;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarSignalOptions signals;

@end

@class INActivateCarSignalIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INActivateCarSignalIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@protocol INActivateCarSignalIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INActivateCarSignalIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INActivateCarSignalIntentResponse containing the details of the result of having executed the intent

 @see  INActivateCarSignalIntentResponse
 */

- (void)handleActivateCarSignal:(INActivateCarSignalIntent *)intent
                     completion:(void (^)(INActivateCarSignalIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INActivateCarSignalIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INActivateCarSignalIntentResponse
 */

- (void)confirmActivateCarSignal:(INActivateCarSignalIntent *)intent
                      completion:(void (^)(INActivateCarSignalIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveCarNameForActivateCarSignal:(INActivateCarSignalIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCarName(for:with:));

- (void)resolveSignalsForActivateCarSignal:(INActivateCarSignalIntent *)intent
                    withCompletion:(void (^)(INCarSignalOptionsResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveSignals(for:with:));

@end

NS_ASSUME_NONNULL_END

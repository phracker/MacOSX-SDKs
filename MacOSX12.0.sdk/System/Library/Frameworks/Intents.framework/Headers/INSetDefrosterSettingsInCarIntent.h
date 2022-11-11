//
//  INSetDefrosterSettingsInCarIntent.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCarDefroster.h>

@class INBooleanResolutionResult;
@class INCarDefrosterResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INSetDefrosterSettingsInCarIntent is deprecated. There is no replacement.", ios(10.0, 15.0))
API_UNAVAILABLE(macos, watchos, tvos)
@interface INSetDefrosterSettingsInCarIntent : INIntent

- (instancetype)initWithEnable:(nullable NSNumber *)enable
                     defroster:(INCarDefroster)defroster
                       carName:(nullable INSpeakableString *)carName NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(12.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *enable NS_REFINED_FOR_SWIFT;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INCarDefroster defroster;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *carName API_AVAILABLE(ios(12.0));

@end

@class INSetDefrosterSettingsInCarIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetDefrosterSettingsInCarIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_DEPRECATED("INSetDefrosterSettingsInCarIntentHandling is deprecated. There is no replacement.", ios(10.0, 15.0))
API_UNAVAILABLE(macos, watchos, tvos)
@protocol INSetDefrosterSettingsInCarIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetDefrosterSettingsInCarIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetDefrosterSettingsInCarIntentResponse containing the details of the result of having executed the intent

 @see  INSetDefrosterSettingsInCarIntentResponse
 */

- (void)handleSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                             completion:(void (^)(INSetDefrosterSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetDefrosterSettingsInCarIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetDefrosterSettingsInCarIntentResponse
 */

- (void)confirmSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                              completion:(void (^)(INSetDefrosterSettingsInCarIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveEnableForSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                                   withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveEnable(for:with:));

- (void)resolveDefrosterForSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                                      withCompletion:(void (^)(INCarDefrosterResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveDefroster(for:with:));

- (void)resolveCarNameForSetDefrosterSettingsInCar:(INSetDefrosterSettingsInCarIntent *)intent
                                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCarName(for:with:)) API_AVAILABLE(ios(12.0));

@end

NS_ASSUME_NONNULL_END

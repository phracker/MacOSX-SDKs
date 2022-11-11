//
//  INSetCarLockStatusIntent.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INBooleanResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INSetCarLockStatusIntent : INIntent

- (instancetype)initWithLocked:(nullable NSNumber *)locked
                       carName:(nullable INSpeakableString *)carName NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *locked NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *carName;

@end

@class INSetCarLockStatusIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetCarLockStatusIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(10.3), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@protocol INSetCarLockStatusIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetCarLockStatusIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetCarLockStatusIntentResponse containing the details of the result of having executed the intent

 @see  INSetCarLockStatusIntentResponse
 */

- (void)handleSetCarLockStatus:(INSetCarLockStatusIntent *)intent
                    completion:(void (^)(INSetCarLockStatusIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetCarLockStatusIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetCarLockStatusIntentResponse
 */

- (void)confirmSetCarLockStatus:(INSetCarLockStatusIntent *)intent
                     completion:(void (^)(INSetCarLockStatusIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveLockedForSetCarLockStatus:(INSetCarLockStatusIntent *)intent
                          withCompletion:(void (^)(INBooleanResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveLocked(for:with:));

- (void)resolveCarNameForSetCarLockStatus:(INSetCarLockStatusIntent *)intent
                           withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveCarName(for:with:));

@end

NS_ASSUME_NONNULL_END

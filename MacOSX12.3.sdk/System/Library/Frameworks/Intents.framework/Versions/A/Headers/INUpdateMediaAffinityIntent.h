//
//  INUpdateMediaAffinityIntent.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INMediaAffinityType.h>

@class INMediaAffinityTypeResolutionResult;
@class INMediaItem;
@class INMediaItemResolutionResult;
@class INMediaSearch;
@class INUpdateMediaAffinityMediaItemResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0))
API_UNAVAILABLE(macos)
@interface INUpdateMediaAffinityIntent : INIntent

- (instancetype)initWithMediaItems:(nullable NSArray<INMediaItem *> *)mediaItems
                       mediaSearch:(nullable INMediaSearch *)mediaSearch
                      affinityType:(INMediaAffinityType)affinityType NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INMediaItem *> *mediaItems;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INMediaSearch *mediaSearch;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INMediaAffinityType affinityType;

@end

@class INUpdateMediaAffinityIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INUpdateMediaAffinityIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0))
API_UNAVAILABLE(macos)
@protocol INUpdateMediaAffinityIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INUpdateMediaAffinityIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INUpdateMediaAffinityIntentResponse containing the details of the result of having executed the intent

 @see  INUpdateMediaAffinityIntentResponse
 */

- (void)handleUpdateMediaAffinity:(INUpdateMediaAffinityIntent *)intent
                       completion:(void (^)(INUpdateMediaAffinityIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INUpdateMediaAffinityIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INUpdateMediaAffinityIntentResponse
 */

- (void)confirmUpdateMediaAffinity:(INUpdateMediaAffinityIntent *)intent
                        completion:(void (^)(INUpdateMediaAffinityIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveMediaItemsForUpdateMediaAffinity:(INUpdateMediaAffinityIntent *)intent
                                 withCompletion:(void (^)(NSArray<INUpdateMediaAffinityMediaItemResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveMediaItems(for:with:));

- (void)resolveAffinityTypeForUpdateMediaAffinity:(INUpdateMediaAffinityIntent *)intent
                                   withCompletion:(void (^)(INMediaAffinityTypeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveAffinityType(for:with:));

@end

NS_ASSUME_NONNULL_END

//
//  INSetTaskAttributeIntent.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INTaskPriority.h>
#import <Intents/INTaskStatus.h>

@class INSetTaskAttributeTemporalEventTriggerResolutionResult;
@class INSpatialEventTrigger;
@class INSpatialEventTriggerResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INTask;
@class INTaskPriorityResolutionResult;
@class INTaskResolutionResult;
@class INTaskStatusResolutionResult;
@class INTemporalEventTrigger;
@class INTemporalEventTriggerResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INSetTaskAttributeIntent : INIntent

- (instancetype)initWithTargetTask:(nullable INTask *)targetTask
                         taskTitle:(nullable INSpeakableString *)taskTitle
                            status:(INTaskStatus)status
                          priority:(INTaskPriority)priority
               spatialEventTrigger:(nullable INSpatialEventTrigger *)spatialEventTrigger
              temporalEventTrigger:(nullable INTemporalEventTrigger *)temporalEventTrigger NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(13.0), watchos(6.0), macosx(10.15));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INTask *targetTask;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *taskTitle API_AVAILABLE(ios(13.0), watchos(6.0));

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INTaskStatus status;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INTaskPriority priority API_AVAILABLE(ios(13.0), watchos(6.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpatialEventTrigger *spatialEventTrigger;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INTemporalEventTrigger *temporalEventTrigger;

@end

@class INSetTaskAttributeIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSetTaskAttributeIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@protocol INSetTaskAttributeIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSetTaskAttributeIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSetTaskAttributeIntentResponse containing the details of the result of having executed the intent

 @see  INSetTaskAttributeIntentResponse
 */

- (void)handleSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                    completion:(void (^)(INSetTaskAttributeIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSetTaskAttributeIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSetTaskAttributeIntentResponse
 */

- (void)confirmSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                     completion:(void (^)(INSetTaskAttributeIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveTargetTaskForSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                              withCompletion:(void (^)(INTaskResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTargetTask(for:with:));

- (void)resolveTaskTitleForSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                             withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTaskTitle(for:with:)) API_AVAILABLE(ios(13.0), watchos(6.0));

- (void)resolveStatusForSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                          withCompletion:(void (^)(INTaskStatusResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveStatus(for:with:));

- (void)resolvePriorityForSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                            withCompletion:(void (^)(INTaskPriorityResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePriority(for:with:)) API_AVAILABLE(ios(13.0), watchos(6.0));

- (void)resolveSpatialEventTriggerForSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                                       withCompletion:(void (^)(INSpatialEventTriggerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveSpatialEventTrigger(for:with:));

- (void)resolveTemporalEventTriggerForSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                                        withCompletion:(void (^)(INTemporalEventTriggerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTemporalEventTrigger(for:with:)) API_DEPRECATED("resolveTemporalEventTriggerForSetTaskAttribute:withCompletion: is deprecated. Use resolveTemporalEventTriggerForSetTaskAttribute:completion: instead", ios(11.0, 13.0), watchos(4.0, 6.0));

- (void)resolveTemporalEventTriggerForSetTaskAttribute:(INSetTaskAttributeIntent *)intent
                                            completion:(void (^)(INSetTaskAttributeTemporalEventTriggerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTemporalEventTrigger(for:with:)) API_AVAILABLE(ios(13.0), watchos(6.0));

@end

NS_ASSUME_NONNULL_END

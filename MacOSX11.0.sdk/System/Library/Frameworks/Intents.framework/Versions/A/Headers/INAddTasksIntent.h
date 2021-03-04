//
//  INAddTasksIntent.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

#import <Intents/INTaskPriority.h>

@class INAddTasksTargetTaskListResolutionResult;
@class INAddTasksTemporalEventTriggerResolutionResult;
@class INSpatialEventTrigger;
@class INSpatialEventTriggerResolutionResult;
@class INSpeakableString;
@class INSpeakableStringResolutionResult;
@class INTaskList;
@class INTaskListResolutionResult;
@class INTaskPriorityResolutionResult;
@class INTemporalEventTrigger;
@class INTemporalEventTriggerResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INAddTasksIntent : INIntent

- (instancetype)initWithTargetTaskList:(nullable INTaskList *)targetTaskList
                            taskTitles:(nullable NSArray<INSpeakableString *> *)taskTitles
                   spatialEventTrigger:(nullable INSpatialEventTrigger *)spatialEventTrigger
                  temporalEventTrigger:(nullable INTemporalEventTrigger *)temporalEventTrigger
                              priority:(INTaskPriority)priority NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(13.0), watchos(6.0));

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INTaskList *targetTaskList;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INSpeakableString *> *taskTitles;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpatialEventTrigger *spatialEventTrigger;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INTemporalEventTrigger *temporalEventTrigger;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INTaskPriority priority API_AVAILABLE(ios(13.0), watchos(6.0));

@end

@class INAddTasksIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INAddTasksIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@protocol INAddTasksIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INAddTasksIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INAddTasksIntentResponse containing the details of the result of having executed the intent

 @see  INAddTasksIntentResponse
 */

- (void)handleAddTasks:(INAddTasksIntent *)intent
            completion:(void (^)(INAddTasksIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INAddTasksIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INAddTasksIntentResponse
 */

- (void)confirmAddTasks:(INAddTasksIntent *)intent
             completion:(void (^)(INAddTasksIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveTargetTaskListForAddTasks:(INAddTasksIntent *)intent
                    withCompletion:(void (^)(INTaskListResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTargetTaskList(for:with:)) API_DEPRECATED("resolveTargetTaskListForAddTasks:withCompletion: is deprecated. Use resolveTargetTaskListForAddTasks:completion: instead", ios(11.0, 13.0), watchos(4.0, 6.0));

- (void)resolveTargetTaskListForAddTasks:(INAddTasksIntent *)intent
                    completion:(void (^)(INAddTasksTargetTaskListResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTargetTaskList(for:with:)) API_AVAILABLE(ios(13.0), watchos(6.0));

- (void)resolveTaskTitlesForAddTasks:(INAddTasksIntent *)intent
                    withCompletion:(void (^)(NSArray<INSpeakableStringResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveTaskTitles(for:with:));

- (void)resolveSpatialEventTriggerForAddTasks:(INAddTasksIntent *)intent
                    withCompletion:(void (^)(INSpatialEventTriggerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveSpatialEventTrigger(for:with:));

- (void)resolveTemporalEventTriggerForAddTasks:(INAddTasksIntent *)intent
                    withCompletion:(void (^)(INTemporalEventTriggerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTemporalEventTrigger(for:with:)) API_DEPRECATED("resolveTemporalEventTriggerForAddTasks:withCompletion: is deprecated. Use resolveTemporalEventTriggerForAddTasks:completion: instead", ios(11.0, 13.0), watchos(4.0, 6.0));

- (void)resolveTemporalEventTriggerForAddTasks:(INAddTasksIntent *)intent
                    completion:(void (^)(INAddTasksTemporalEventTriggerResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTemporalEventTrigger(for:with:)) API_AVAILABLE(ios(13.0), watchos(6.0));

- (void)resolvePriorityForAddTasks:(INAddTasksIntent *)intent
                    withCompletion:(void (^)(INTaskPriorityResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolvePriority(for:with:)) API_AVAILABLE(ios(13.0), watchos(6.0));

@end

NS_ASSUME_NONNULL_END

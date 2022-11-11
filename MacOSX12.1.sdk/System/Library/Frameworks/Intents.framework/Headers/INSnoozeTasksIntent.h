//
//  INSnoozeTasksIntent.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INDateComponentsRange;
@class INDateComponentsRangeResolutionResult;
@class INSnoozeTasksTaskResolutionResult;
@class INTask;
@class INTaskResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macos, tvos)
@interface INSnoozeTasksIntent : INIntent

- (instancetype)initWithTasks:(nullable NSArray<INTask *> *)tasks
              nextTriggerTime:(nullable INDateComponentsRange *)nextTriggerTime
                          all:(nullable NSNumber *)all NS_DESIGNATED_INITIALIZER NS_REFINED_FOR_SWIFT;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INTask *> *tasks;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *nextTriggerTime;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSNumber *all NS_REFINED_FOR_SWIFT;

@end

@class INSnoozeTasksIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INSnoozeTasksIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macos, tvos)
@protocol INSnoozeTasksIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INSnoozeTasksIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INSnoozeTasksIntentResponse containing the details of the result of having executed the intent

 @see  INSnoozeTasksIntentResponse
 */

- (void)handleSnoozeTasks:(INSnoozeTasksIntent *)intent
               completion:(void (^)(INSnoozeTasksIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INSnoozeTasksIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INSnoozeTasksIntentResponse
 */

- (void)confirmSnoozeTasks:(INSnoozeTasksIntent *)intent
                completion:(void (^)(INSnoozeTasksIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveTasksForSnoozeTasks:(INSnoozeTasksIntent *)intent
                    withCompletion:(void (^)(NSArray<INSnoozeTasksTaskResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveTasks(for:with:));

- (void)resolveNextTriggerTimeForSnoozeTasks:(INSnoozeTasksIntent *)intent
                              withCompletion:(void (^)(INDateComponentsRangeResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveNextTriggerTime(for:with:));

@end

NS_ASSUME_NONNULL_END

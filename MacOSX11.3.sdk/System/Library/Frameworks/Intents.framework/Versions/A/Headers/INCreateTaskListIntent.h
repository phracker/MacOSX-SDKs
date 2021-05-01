//
//  INCreateTaskListIntent.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>
#import <Intents/INIntentResolutionResult.h>

@class INSpeakableString;
@class INSpeakableStringResolutionResult;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INCreateTaskListIntent : INIntent

- (instancetype)initWithTitle:(nullable INSpeakableString *)title
                   taskTitles:(nullable NSArray<INSpeakableString *> *)taskTitles
                    groupName:(nullable INSpeakableString *)groupName NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *title;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INSpeakableString *> *taskTitles;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INSpeakableString *groupName;

@end

@class INCreateTaskListIntentResponse;

/*!
 @abstract Protocol to declare support for handling an INCreateTaskListIntent. By implementing this protocol, a class can provide logic for resolving, confirming and handling the intent.
 @discussion The minimum requirement for an implementing class is that it should be able to handle the intent. The resolution and confirmation methods are optional. The handling method is always called last, after resolving and confirming the intent.
 */

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@protocol INCreateTaskListIntentHandling <NSObject>

@required

/*!
 @abstract Handling method - Execute the task represented by the INCreateTaskListIntent that's passed in
 @discussion Called to actually execute the intent. The app must return a response for this intent.

 @param  intent The input intent
 @param  completion The response handling block takes a INCreateTaskListIntentResponse containing the details of the result of having executed the intent

 @see  INCreateTaskListIntentResponse
 */

- (void)handleCreateTaskList:(INCreateTaskListIntent *)intent
                  completion:(void (^)(INCreateTaskListIntentResponse *response))completion NS_SWIFT_NAME(handle(intent:completion:));

@optional

/*!
 @abstract Confirmation method - Validate that this intent is ready for the next step (i.e. handling)
 @discussion Called prior to asking the app to handle the intent. The app should return a response object that contains additional information about the intent, which may be relevant for the system to show the user prior to handling. If unimplemented, the system will assume the intent is valid following resolution, and will assume there is no additional information relevant to this intent.

 @param  intent The input intent
 @param  completion The response block contains an INCreateTaskListIntentResponse containing additional details about the intent that may be relevant for the system to show the user prior to handling.

 @see INCreateTaskListIntentResponse
 */

- (void)confirmCreateTaskList:(INCreateTaskListIntent *)intent
                   completion:(void (^)(INCreateTaskListIntentResponse *response))completion NS_SWIFT_NAME(confirm(intent:completion:));

/*!
 @abstract Resolution methods - Determine if this intent is ready for the next step (confirmation)
 @discussion Called to make sure the app extension is capable of handling this intent in its current form. This method is for validating if the intent needs any further fleshing out.

 @param  intent The input intent
 @param  completion The response block contains an INIntentResolutionResult for the parameter being resolved

 @see INIntentResolutionResult
 */

- (void)resolveTitleForCreateTaskList:(INCreateTaskListIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveTitle(for:with:));

- (void)resolveTaskTitlesForCreateTaskList:(INCreateTaskListIntent *)intent
                    withCompletion:(void (^)(NSArray<INSpeakableStringResolutionResult *> *resolutionResults))completion NS_SWIFT_NAME(resolveTaskTitles(for:with:));

- (void)resolveGroupNameForCreateTaskList:(INCreateTaskListIntent *)intent
                    withCompletion:(void (^)(INSpeakableStringResolutionResult *resolutionResult))completion NS_SWIFT_NAME(resolveGroupName(for:with:));

@end

NS_ASSUME_NONNULL_END

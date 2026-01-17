//
//  BGTaskScheduler.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <BackgroundTasks/BGDefines.h>

@class BGTaskScheduler;
@class BGTaskRequest;
@class BGTask;

NS_ASSUME_NONNULL_BEGIN

BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
NSErrorDomain const BGTaskSchedulerErrorDomain;

/*!
 @enum BGTaskSchedulerErrorCode
 @constant BGTaskSchedulerErrorCodeUnavailable Background task scheduling functionality is not available for this app/extension. Background App Refresh may have been disabled in Settings.
 @constant BGTaskSchedulerErrorCodeTooManyPendingTaskRequests The task request could not be submitted because there are too many pending task requests of this type. Cancel some existing task requests before trying again.
 @constant BGTaskSchedulerErrorCodeNotPermitted The task request could not be submitted because the appropriate background mode is not included in the UIBackgroundModes array, or its identifier was not present in the BGTaskSchedulerPermittedIdentifiers array in the app's Info.plist.
 */
typedef NS_ERROR_ENUM(BGTaskSchedulerErrorDomain, BGTaskSchedulerErrorCode) {
    BGTaskSchedulerErrorCodeUnavailable = 1,
    BGTaskSchedulerErrorCodeTooManyPendingTaskRequests = 2,
    BGTaskSchedulerErrorCodeNotPermitted = 3,
} API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos);

/*!
 @class BGTaskScheduler
 @abstract The object you use to schedule deferrable work to be done in the background.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGTaskScheduler : NSObject
- (instancetype)init NS_UNAVAILABLE; //Use the shared scheduler object instead
+ (instancetype)new NS_UNAVAILABLE; //Use the shared scheduler object instead

@property (class, readonly, strong) __kindof BGTaskScheduler *sharedScheduler;

/*!
 @abstract Register a handler to be called for tasks that launch the app.
 @param identifier The identifier for the task that will be handled by the provided launch handler.
 @param queue The queue on which the launch handler and the expiration handler for the task will be called. The queue should be serial to ensure consistent ordering. If you pass nil, handlers will be called on a background queue.
 @param launchHandler The block that will be called when the app is launched for the specified task. The block has no return value and takes a single parameter, task, a BGTask object. Assign an expiration handler to the task's expirationHandler property and call setTaskCompletedWithSuccess: when the background work is complete.
 @discussion You must register launch handlers before your application finishes launching. Attempting to register a handler after launch or multiple handlers for the same identifier is an error. Although you may submit task requests from some extensions, only the host app will be launched to handle background work.
 @return YES if the handler was registered, or NO if it was not because the provided identifier was not present in the BGTaskSchedulerPermittedIdentifiers array in the app's Info.plist.
 */
- (BOOL)registerForTaskWithIdentifier:(NSString *)identifier usingQueue:(nullable dispatch_queue_t)queue launchHandler:(void (^)(__kindof BGTask *task))launchHandler NS_EXTENSION_UNAVAILABLE("Only the host application may register launch handlers");

/*!
 @abstract Submit a request to be launched in the background to perform work.
 @param taskRequest The task request object representing the parameters of the background task to be scheduled.
 @param error If an error occurs, upon return contains an error object that indicates why the request was rejected.
 @discussion Submitting a task request with the same identifier as an existing request will replace that request.
 @return YES if the request was successfully submitted, NO if there was an error
 */
- (BOOL)submitTaskRequest:(BGTaskRequest *)taskRequest error:(NSError * _Nullable *)error;

/*!
 @abstract Cancel a previously submitted task request.
 @param identifier The identifier of the previously submitted task request to cancel.
 */
- (void)cancelTaskRequestWithIdentifier:(NSString *)identifier;

/*!
 @abstract Cancel all previously submitted task requests.
 */
- (void)cancelAllTaskRequests;

/*!
 @abstract Returns a list of all task requests that have been submitted but not yet completed.
 @param completionHandler A block for processing task requests. This block may be executed on a background thread. The block has no return value and takes a single parameter, taskRequests, which is an array of BGTaskRequest objects. If there are no pending requests, this array is empty. The task request objects returned are copies and changing their property values will have no immediate effect. To modify the parameters of a pending task request, submit it again to the scheduler with submitTaskRequest:error:.
 */
- (void)getPendingTaskRequestsWithCompletionHandler:(void (^)(NSArray<BGTaskRequest *> *taskRequests))completionHandler;

@end

NS_ASSUME_NONNULL_END

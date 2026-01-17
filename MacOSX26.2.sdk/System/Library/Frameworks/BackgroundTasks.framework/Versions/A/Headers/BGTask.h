//
//  BGTask.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <BackgroundTasks/BGDefines.h>

NS_ASSUME_NONNULL_BEGIN

/// An abstract class representing a task that’s run while the app is in the
/// background.
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos)
@interface BGTask : NSObject

/// The string identifier of the task.
///
/// The identifier is the same as the one used to register the launch handler in
/// ``BGTaskScheduler/registerForTaskWithIdentifier:usingQueue:launchHandler:``.
@property (copy, readonly) NSString *identifier;

/// A handler called shortly before the task’s background time expires.
///
/// There is a limit to how long your app has to perform its background work, and your work may need to be interrupted
/// if system conditions change. Assign a handler to this property to cancel any ongoing tasks, perform any needed
/// cleanup, and then call setTaskCompletedWithSuccess: to signal completion to the system and allow your app to be
/// suspended. This property is cleared after it is called by the system or when ``BGTask/setTaskCompletedWithSuccess:``
/// is called. This is to mitigate the impact of a retain cycle created by referencing the BGTask instance inside this
/// block.
///
/// The handler may be called before the background process uses the full amount of its allocated time.
///
/// - Parameters:
///     - expirationHandler: The expiration handler takes no arguments and has no return value. Use the handler to
///     cancel any ongoing work and to do any required cleanup in as short a time as possible.
///
/// - Note: The manager sets the value `expirationHandler` to `nil` after the handler completes.
/// - Warning: Not setting an expiration handler results in the system marking your task as complete and unsuccessful instead of sending a warning.
@property (nullable, strong) void (^expirationHandler)(void);

- (instancetype)init NS_UNAVAILABLE; // Subclasses of this abstract type are created by the system and cannot be directly instantiated
+ (instancetype)new NS_UNAVAILABLE; // Subclasses of this abstract type are created by the system and cannot be directly instantiated

/// Inform the background task scheduler that the task is complete.
///
/// Call this method as soon as the background work associated with this task is complete. The system provides your app
/// with a limited amount of time to finish the task. If you do not call setTaskCompletedWithSuccess: on the task, the
/// system continues to run in the background until all the available time is consumed, wasting battery power. The
/// system suspends the app as soon as all background tasks are complete.
///
/// - Parameters:
///     - success: A `Boolean` indicating if the task completed successfully or not. If the task was unsuccessful, you
///     may request the system to try again later by submitting a new task request to the scheduler before calling this
///     method.
///
/// - Important: If you don’t set an expiration handler, the system will mark your task as complete and unsuccessful
/// instead of sending a warning.
/// - Warning: Not calling ``BGTask/setTaskCompletedWithSuccess:`` before the time for the task expires may result in
/// the system killing your app.
- (void)setTaskCompletedWithSuccess:(BOOL)success;

@end

#pragma mark -

/// A time-consuming processing task that runs while the app is in the
/// background.
///
/// Use processing tasks for long data updates, processing data, and app
/// maintenance. Although processing tasks can run for minutes, the system can
/// interrupt the process. Add an expiration handler by setting
/// ``BGTask/expirationHandler`` for any required cleanup.
///
/// Executing processing tasks requires setting the `processing`
/// <doc://com.apple.documentation/documentation/bundleresources/information_property_list/uibackgroundmodes>
/// capability. For information on setting this capability, see
/// ``BGTaskScheduler``.
///
/// Processing tasks run only when the device is idle. The system terminates any
/// background processing tasks running when the user starts using the device.
/// Background refresh tasks are not affected.
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos)
@interface BGProcessingTask : BGTask

@end

#pragma mark -

/// A task meant to perform processing on behalf of health research studies.
///
/// Health research tasks may only be used by applications entitled to perform
/// studies and user's have opted in to the relevant study. These apps must have the
/// `com.apple.developer.backgroundtasks.healthresearch` entitlement.
BG_EXTERN API_AVAILABLE(ios(17.0), tvos(32.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos)
@interface BGHealthResearchTask : BGProcessingTask

@end

#pragma mark -

/// An object representing a short task typically used to refresh content that’s
/// run while the app is in the background.
///
/// Use app refresh tasks for updating your app with small bits of information,
/// such as the latest stock values.
///
/// Executing app refresh tasks requires setting the `fetch`
/// <doc://com.apple.documentation/documentation/bundleresources/information_property_list/uibackgroundmodes>
/// capability. For information on setting this capability, see
/// ``BGTaskScheduler``.
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos)
@interface BGAppRefreshTask : BGTask

@end

#pragma mark -

/// A task meant to perform processing on behalf of a user initiated request.
///
/// Continued processing tasks will present UI while in progress to provide awareness to the user.
/// ``BGContinuedProcessingTask``s _must_ report progress via the ``NSProgressReporting`` protocol conformance during
/// runtime and are subject to expiration based on changing system conditions and user input. Tasks that appear stalled
/// may be forcibly expired by the scheduler to preserve system resources.
BG_EXTERN API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, tvos, visionos, watchos, macCatalyst)
@interface BGContinuedProcessingTask : BGTask<NSProgressReporting>

/// The localized title displayed to the user.
@property (copy, readonly) NSString *title;

/// The localized subtitle displayed to the user.
@property (copy, readonly) NSString *subtitle;

/// Update the title and subtitle displayed in the live activity displayed to the user.
///
/// - Parameters:
///   - title: The localized title displayed to the user.
///   - subtitle: The localized subtitle displayed to the user.
- (void)updateTitle:(NSString *)title
           subtitle:(NSString *)subtitle;

@end

NS_ASSUME_NONNULL_END

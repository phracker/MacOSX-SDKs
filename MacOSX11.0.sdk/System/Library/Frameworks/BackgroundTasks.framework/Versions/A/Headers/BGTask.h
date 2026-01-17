//
//  BGTask.h
//  BackgroundTasks
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <BackgroundTasks/BGDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract An abstract class that represents the background work for which the app was launched to handle.
 @discussion Subclasses of this type are created by the system and should not be directly instantiated.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGTask : NSObject

/*!
 @abstract The identifier associated with the request used to schedule this background work.
*/
@property (copy, readonly) NSString *identifier;

/*!
 @abstract Called by the system shortly before your app's background time expires.
 @discussion There is a limit to how long your app has to perform its background work, and your work may need to be interrupted if system conditions change. Assign a handler to this property to cancel any ongoing tasks, perform any needed cleanup, and then call setTaskCompletedWithSuccess: to signal completion to the system and allow your app to be suspended.
This property is cleared after it is called by the system or when setTaskCompletedWithSuccess: is called. This is to mitigate the impact of a retain cycle created by referencing the BGTask instance inside this block.
 */
@property (nullable, strong) void (^expirationHandler)(void);

- (instancetype)init NS_UNAVAILABLE; // Subclasses of this abstract type are created by the system and cannot be directly instantiated
- (instancetype)new NS_UNAVAILABLE; // Subclasses of this abstract type are created by the system and cannot be directly instantiated

/*!
 @abstract Marks this task as complete.
 @discussion Call this method as soon as the background work associated with this task is complete. The system provides your app with a limited amount of time to finish the task. If you do not call setTaskCompletedWithSuccess: on the task, the system continues to run in the background until all the available time is consumed, wasting battery power.
 The system suspends the app as soon as all background tasks are complete.
 @param success Whether the task was completed successfully. If the task was unsuccessful, you may request the system to try again later by submitting a new task request to the scheduler before calling this method.
 */
- (void)setTaskCompletedWithSuccess:(BOOL)success;

@end

/*!
 @abstract A background task used to perform deferrable processing.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGProcessingTask : BGTask

@end

/*!
 @abstract A background task used to update your app's contents in the background.
 */
BG_EXTERN API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos)
@interface BGAppRefreshTask : BGTask

@end

NS_ASSUME_NONNULL_END

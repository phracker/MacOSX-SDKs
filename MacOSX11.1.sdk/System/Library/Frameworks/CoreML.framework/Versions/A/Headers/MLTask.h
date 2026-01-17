//
//  MLTask.h
//  CoreML
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * All possible states an MLTask can be in.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(14.0))
typedef NS_ENUM(NSInteger, MLTaskState) {
    MLTaskStateSuspended = 1,
    MLTaskStateRunning = 2,
    MLTaskStateCancelling = 3,
    MLTaskStateCompleted = 4,
    MLTaskStateFailed = 5,
};

/*!
 * Class that abstracts state transitions and basic task controls.
 */
ML_EXPORT
API_AVAILABLE(macos(10.15), ios(13.0), tvos(14.0))
@interface MLTask : NSObject

// Unique identifier for the task.
@property (readonly, copy, nonatomic) NSString *taskIdentifier;

// Represents the current state of task.
@property (readonly, assign, atomic) MLTaskState state;

// Indicates error if the task failed for any reason.
@property (readonly, copy, atomic, nullable) NSError *error;

// When called, resumes the task and changes state to "Running".
- (void)resume;

// When called, starts cancelling the task and changes the state to "Cancelling".
- (void)cancel;

// cannot construct MLTask without parameters.
- (instancetype)init NS_UNAVAILABLE;

// cannot construct MLTask without parameters.
+ (id)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END


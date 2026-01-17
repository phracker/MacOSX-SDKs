//
//  MXAppExitMetric.h
//  MetricKit
//
//  Copyright (c) 2020 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <MetricKit/MXMetric.h>
#import <os/availability.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@class         MXForegroundExitData
@abstract      A class that encapsulates cumulative application exit metrics when the application is on screen.
@discussion    Foreground exits are user visible terminations that, when unexpected, interrupt usage.
@discussion    Not all foreground exits are unexpected. See the documentation for each exit reason for more information.
*/
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXForegroundExitData : NSObject <NSSecureCoding>

/*!
@property      cumulativeNormalAppExitCount
@abstract      Cumulative number of times the application exited normally, or was gracefully terminated by the system.
*/
@property (readonly) NSUInteger cumulativeNormalAppExitCount;

/*!
@property      cumulativeMemoryResourceLimitExitCount
@abstract      Cumulative number of times the application was terminated for exceeding a memory consumption limit.
*/
@property (readonly) NSUInteger cumulativeMemoryResourceLimitExitCount;


/*!
@property      cumulativeBadAccessExitCount
@abstract      Cumulative number of times the application was terminated for attempting to access invalid memory, or attempting to access memory in a manner not allowed by the memory's protection level (e.g. writing to read-only memory).
*/
@property (readonly) NSUInteger cumulativeBadAccessExitCount;

/*!
@property      cumulativeAbnormalExitCount
@abstract      Cumulative number of times the application exited abnormally.
@discussion    The most common causes of crashes with this exception type are uncaught Objective-C/C++ exceptions and calls to abort().
*/
@property (readonly) NSUInteger cumulativeAbnormalExitCount;

/*!
@property      cumulativeIllegalInstructionExitCount
@abstract      Cumulative number of times the application terminated for attempting to execute an illegal or undefined instruction.
@discussion    The process may have attempted to jump to an invalid address via a misconfigured function pointer.
*/
@property (readonly) NSUInteger cumulativeIllegalInstructionExitCount;


/*!
@property      cumulativeAppWatchdogExitCount
@abstract      Cumulative number of times the application was terminated because a watchdog timeout occured.
@discussion    These can occur when the application took too long to launch, terminate, or respond to system events.
*/
@property (readonly) NSUInteger cumulativeAppWatchdogExitCount;

@end

/*!
@class         MXBackgroundExitData
@abstract      A class that encapsulates cumulative application exit metrics when the application is off screen.
@discussion    Background exits are terminations that, when unexpected, can impact performance metrics, such as launch time.
@discussion    Not all background exits are unexpected. See the documentation for each exit reason for more information.
*/
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXBackgroundExitData : NSObject <NSSecureCoding>

/*!
@property      cumulativeNormalAppExitCount
@abstract      Cumulative number of times the application exited normally, or was gracefully terminated by the system.
*/
@property (readonly) NSUInteger cumulativeNormalAppExitCount;

/*!
@property      cumulativeMemoryResourceLimitExitCount
@abstract      Cumulative number of times the application was terminated for exceeding a memory consumption limit.
*/
@property (readonly) NSUInteger cumulativeMemoryResourceLimitExitCount;

/*!
@property      cumulativeCPUResourceLimitExitCount
@abstract      Cumulative number of times the application was terminated for exceeding a CPU consumption limit.
*/
@property (readonly) NSUInteger cumulativeCPUResourceLimitExitCount;

/*!
@property      cumulativeMemoryPressureExitCount
@abstract      Cumulative number of times the application exited due to memory pressure on the system.
*/
@property (readonly) NSUInteger cumulativeMemoryPressureExitCount;

/*!
@property      cumulativeBadAccessExitCount
@abstract      Cumulative number of times the application was terminated for attempting to access invalid memory, or attempting to access memory in a manner not allowed by the memory's protection level (e.g. writing to read-only memory).
*/
 @property (readonly) NSUInteger cumulativeBadAccessExitCount;

/*!
@property      cumulativeAbnormalExitCount
@abstract      Cumulative number of times the application exited abnormally.
@discussion    The most common causes of crashes with this exception type are uncaught Objective-C/C++ exceptions and calls to abort().
*/
@property (readonly) NSUInteger cumulativeAbnormalExitCount;

/*!
@property      cumulativeIllegalInstructionExitCount
@abstract      Cumulative number of times the application terminated for attempting to execute an illegal or undefined instruction.
@discussion    The process may have attempted to jump to an invalid address via a misconfigured function pointer.
*/
@property (readonly) NSUInteger cumulativeIllegalInstructionExitCount;


/*!
@property      cumulativeAppWatchdogExitCount
@abstract      Cumulative number of times the application was terminated because a watchdog timeout occured.
@discussion    These can occur when the application took too long to launch, terminate, or respond to system events.
*/
@property (readonly) NSUInteger cumulativeAppWatchdogExitCount;

/*!
@property      cumulativeSuspendedWithLockedFileExitCount
@abstract      Cumulative number of times the application was terminated because it became suspended while holding onto file locks or sqlite database locks.
@discussion    If your application is performing operations on a locked file or sqlite database at suspension time, it must request additional background execution time to complete those operations and relinquish the lock before suspending.
*/
@property (readonly) NSUInteger cumulativeSuspendedWithLockedFileExitCount;

/*!
@property      cumulativeBackgroundTaskAssertionTimeoutExitCount
@abstract      Cumulative number of times the application was terminated for exceeding the alotted time limit associated with a background tasks.
@discussion    If your application begins a background task, you must call endBackgroundTask() to signal completion of the task to prevent your application from being terminated. You can do this in the expiration handler of the task, but it must be done immediately.
*/
@property (readonly) NSUInteger cumulativeBackgroundTaskAssertionTimeoutExitCount;


@end

/*!
@class         MXAppExitMetric
@abstract      A class that encapsulates application exit metrics for both on screen and off screen exits.
@discussion    Application exits can be expected, such as when the application is killed in the app switcher by the user, or unexpected, such as when a runtime error occurs.
@discussion    Minimizing unexpected exits and maximizing expected exits can improve performance and reliability of your application.
*/
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXAppExitMetric : MXMetric

/*!
@property      foregroundExitData
@abstract      Cumulative foreground exit data.
@discussion    This includes application exit data when the application was on screen and visible to the user.
*/
@property (readonly, strong, nonnull) MXForegroundExitData *foregroundExitData;

/*!
@property      backgroundExitData
@abstract      Cumulative background exit data.
@discussion    This includes application exit data when the application was off screen and not visible to the user.
*/
@property (readonly, strong, nonnull) MXBackgroundExitData *backgroundExitData;

@end

NS_ASSUME_NONNULL_END

//
//  MXError.h
//  MetricKit
//
//  Copyright (c) 2022 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>

/*!
    @const      MXErrorDomain
    @abstract   Error domain for NSError values stemming from the MetricKit Framework API.
    @discussion This error domain is used as the domain for all NSError instances stemming from the MetricKit Framework.
*/
extern NSErrorDomain const MXErrorDomain API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos, watchos);

/*!
    @enum       MXErrorCode
    @abstract   Error codes for NSError values stemming from the MetricKit Framework.
    @discussion These error codes are used as the codes for all NSError instances stemmming from the MetricKit Framework.
 
    @constant   MXErrorLaunchTaskInvalidID           The passed-in task ID is a null value or exceeds the max 128 character length.
    @constant   MXErrorLaunchTaskMaxCount            Exceeded the max number of tasks.
    @constant   MXErrorLaunchTaskPastDeadline        The start call was made too late, see @discussion.
    @constant   MXErrorLaunchTaskDuplicated          A task with the same ID has already been started.
    @constant   MXErrorLaunchTaskUnknown             The task hasn't been started or has already been finished.
    @constant   MXErrorLaunchTaskInternalFailure     Internal failures happened inside of MetricKit.
*/
typedef NS_ERROR_ENUM(MXErrorDomain, MXErrorCode) {
    MXErrorLaunchTaskInvalidID,
    MXErrorLaunchTaskMaxCount,
    MXErrorLaunchTaskPastDeadline,
    MXErrorLaunchTaskDuplicated,
    MXErrorLaunchTaskUnknown,
    MXErrorLaunchTaskInternalFailure
} API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos, watchos);

//
//  INDeleteTasksTaskListResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INTaskListResolutionResult.h>

typedef NS_ENUM(NSInteger, INDeleteTasksTaskListUnsupportedReason) {
    INDeleteTasksTaskListUnsupportedReasonNoTaskListFound = 1,
} API_DEPRECATED("INDeleteTasksTaskListUnsupportedReason is deprecated. There is no replacement.", ios(13.0, 15.0), watchos(6.0, 8.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INDeleteTasksTaskListResolutionResult is deprecated. There is no replacement.", ios(13.0, 15.0), watchos(6.0, 8.0))
API_UNAVAILABLE(macos, tvos)
@interface INDeleteTasksTaskListResolutionResult : INTaskListResolutionResult

+ (instancetype)unsupportedForReason:(INDeleteTasksTaskListUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithTaskListResolutionResult:(INTaskListResolutionResult *)taskListResolutionResult;

@end

NS_ASSUME_NONNULL_END

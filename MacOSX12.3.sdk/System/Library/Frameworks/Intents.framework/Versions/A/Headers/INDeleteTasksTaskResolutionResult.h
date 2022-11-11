//
//  INDeleteTasksTaskResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INTaskResolutionResult.h>

typedef NS_ENUM(NSInteger, INDeleteTasksTaskUnsupportedReason) {
    INDeleteTasksTaskUnsupportedReasonNoTasksFound = 1,
    INDeleteTasksTaskUnsupportedReasonNoTasksInApp,
} API_DEPRECATED("INDeleteTasksTaskUnsupportedReason is deprecated. There is no replacement.", ios(13.0, 15.0), watchos(6.0, 8.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INDeleteTasksTaskResolutionResult is deprecated. There is no replacement.", ios(13.0, 15.0), watchos(6.0, 8.0))
API_UNAVAILABLE(macos, tvos)
@interface INDeleteTasksTaskResolutionResult : INTaskResolutionResult

+ (instancetype)unsupportedForReason:(INDeleteTasksTaskUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithTaskResolutionResult:(INTaskResolutionResult *)taskResolutionResult;

@end

NS_ASSUME_NONNULL_END

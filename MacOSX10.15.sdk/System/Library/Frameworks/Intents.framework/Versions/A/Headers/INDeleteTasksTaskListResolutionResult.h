//
//  INDeleteTasksTaskListResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Intents/INTaskListResolutionResult.h>

typedef NS_ENUM(NSInteger, INDeleteTasksTaskListUnsupportedReason) {
    INDeleteTasksTaskListUnsupportedReasonNoTaskListFound = 1,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macosx)
@interface INDeleteTasksTaskListResolutionResult : INTaskListResolutionResult

+ (instancetype)unsupportedForReason:(INDeleteTasksTaskListUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithTaskListResolutionResult:(INTaskListResolutionResult *)taskListResolutionResult;

@end

NS_ASSUME_NONNULL_END

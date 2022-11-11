//
//  INStartCallCallRecordToCallBackResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INCallRecordResolutionResult.h>

typedef NS_ENUM(NSInteger, INStartCallCallRecordToCallBackUnsupportedReason) {
    INStartCallCallRecordToCallBackUnsupportedReasonNoMatchingCall = 1,
} API_AVAILABLE(ios(14.0), macos(12.0), watchos(7.0)) API_UNAVAILABLE(tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), macos(12.0), watchos(7.0))
API_UNAVAILABLE(tvos)
@interface INStartCallCallRecordToCallBackResolutionResult : INCallRecordResolutionResult

+ (instancetype)unsupportedForReason:(INStartCallCallRecordToCallBackUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithCallRecordResolutionResult:(INCallRecordResolutionResult *)callRecordResolutionResult;

@end

NS_ASSUME_NONNULL_END

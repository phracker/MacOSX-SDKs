//
//  INStartCallContactResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INPersonResolutionResult.h>

typedef NS_ENUM(NSInteger, INStartCallContactUnsupportedReason) {
    INStartCallContactUnsupportedReasonNoContactFound = 1,
    INStartCallContactUnsupportedReasonMultipleContactsUnsupported,
    INStartCallContactUnsupportedReasonNoHandleForLabel,
    INStartCallContactUnsupportedReasonInvalidHandle,
    INStartCallContactUnsupportedReasonUnsupportedMmiUssd,
    INStartCallContactUnsupportedReasonNoCallHistoryForRedial API_DEPRECATED("", ios(13.0, 14.0), watchos(6.0, 7.0)) API_UNAVAILABLE(macos),
    INStartCallContactUnsupportedReasonNoUsableHandleForRedial,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macos, tvos)
@interface INStartCallContactResolutionResult : INPersonResolutionResult

+ (instancetype)unsupportedForReason:(INStartCallContactUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithPersonResolutionResult:(INPersonResolutionResult *)personResolutionResult;

@end

NS_ASSUME_NONNULL_END

//
//  INStartCallContactResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Intents/INPersonResolutionResult.h>

typedef NS_ENUM(NSInteger, INStartCallContactUnsupportedReason) {
    INStartCallContactUnsupportedReasonNoContactFound = 1,
    INStartCallContactUnsupportedReasonMultipleContactsUnsupported,
    INStartCallContactUnsupportedReasonNoHandleForLabel,
    INStartCallContactUnsupportedReasonInvalidHandle,
    INStartCallContactUnsupportedReasonUnsupportedMmiUssd,
    INStartCallContactUnsupportedReasonNoCallHistoryForRedial,
    INStartCallContactUnsupportedReasonNoUsableHandleForRedial,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macosx)
@interface INStartCallContactResolutionResult : INPersonResolutionResult

+ (instancetype)unsupportedForReason:(INStartCallContactUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithPersonResolutionResult:(INPersonResolutionResult *)personResolutionResult;

@end

NS_ASSUME_NONNULL_END

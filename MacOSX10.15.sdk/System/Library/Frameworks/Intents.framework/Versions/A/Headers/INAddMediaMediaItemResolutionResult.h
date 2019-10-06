//
//  INAddMediaMediaItemResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Intents/INMediaItemResolutionResult.h>

typedef NS_ENUM(NSInteger, INAddMediaMediaItemUnsupportedReason) {
    INAddMediaMediaItemUnsupportedReasonLoginRequired = 1,
    INAddMediaMediaItemUnsupportedReasonSubscriptionRequired,
    INAddMediaMediaItemUnsupportedReasonUnsupportedMediaType,
    INAddMediaMediaItemUnsupportedReasonExplicitContentSettings,
    INAddMediaMediaItemUnsupportedReasonCellularDataSettings,
    INAddMediaMediaItemUnsupportedReasonRestrictedContent,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macosx);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macosx)
@interface INAddMediaMediaItemResolutionResult : INMediaItemResolutionResult

+ (instancetype)unsupportedForReason:(INAddMediaMediaItemUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithMediaItemResolutionResult:(INMediaItemResolutionResult *)mediaItemResolutionResult;

@end

NS_ASSUME_NONNULL_END

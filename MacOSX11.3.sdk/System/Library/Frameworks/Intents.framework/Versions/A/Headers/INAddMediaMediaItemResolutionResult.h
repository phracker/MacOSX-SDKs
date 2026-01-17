//
//  INAddMediaMediaItemResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INMediaItemResolutionResult.h>

typedef NS_ENUM(NSInteger, INAddMediaMediaItemUnsupportedReason) {
    INAddMediaMediaItemUnsupportedReasonLoginRequired = 1,
    INAddMediaMediaItemUnsupportedReasonSubscriptionRequired,
    INAddMediaMediaItemUnsupportedReasonUnsupportedMediaType,
    INAddMediaMediaItemUnsupportedReasonExplicitContentSettings,
    INAddMediaMediaItemUnsupportedReasonCellularDataSettings,
    INAddMediaMediaItemUnsupportedReasonRestrictedContent,
    INAddMediaMediaItemUnsupportedReasonServiceUnavailable API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos),
    INAddMediaMediaItemUnsupportedReasonRegionRestriction API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos),
} API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0))
API_UNAVAILABLE(macos)
@interface INAddMediaMediaItemResolutionResult : INMediaItemResolutionResult

// Convenience method to return multiple success resolution results for an array of INMediaItems
+ (NSArray<INAddMediaMediaItemResolutionResult *> *)successesWithResolvedMediaItems:(NSArray<INMediaItem *> *)resolvedMediaItems NS_SWIFT_NAME(successes(with:));

+ (instancetype)unsupportedForReason:(INAddMediaMediaItemUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithMediaItemResolutionResult:(INMediaItemResolutionResult *)mediaItemResolutionResult;

@end

NS_ASSUME_NONNULL_END

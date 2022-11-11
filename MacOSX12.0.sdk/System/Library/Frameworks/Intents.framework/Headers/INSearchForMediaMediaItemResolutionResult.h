//
//  INSearchForMediaMediaItemResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INMediaItemResolutionResult.h>

typedef NS_ENUM(NSInteger, INSearchForMediaMediaItemUnsupportedReason) {
    INSearchForMediaMediaItemUnsupportedReasonLoginRequired = 1,
    INSearchForMediaMediaItemUnsupportedReasonSubscriptionRequired,
    INSearchForMediaMediaItemUnsupportedReasonUnsupportedMediaType,
    INSearchForMediaMediaItemUnsupportedReasonExplicitContentSettings,
    INSearchForMediaMediaItemUnsupportedReasonCellularDataSettings,
    INSearchForMediaMediaItemUnsupportedReasonRestrictedContent,
    INSearchForMediaMediaItemUnsupportedReasonServiceUnavailable API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos),
    INSearchForMediaMediaItemUnsupportedReasonRegionRestriction API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos),
} API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0)) API_UNAVAILABLE(macos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0))
API_UNAVAILABLE(macos)
@interface INSearchForMediaMediaItemResolutionResult : INMediaItemResolutionResult

// Convenience method to return multiple success resolution results for an array of INMediaItems
+ (NSArray<INSearchForMediaMediaItemResolutionResult *> *)successesWithResolvedMediaItems:(NSArray<INMediaItem *> *)resolvedMediaItems NS_SWIFT_NAME(successes(with:));

+ (instancetype)unsupportedForReason:(INSearchForMediaMediaItemUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithMediaItemResolutionResult:(INMediaItemResolutionResult *)mediaItemResolutionResult;

@end

NS_ASSUME_NONNULL_END

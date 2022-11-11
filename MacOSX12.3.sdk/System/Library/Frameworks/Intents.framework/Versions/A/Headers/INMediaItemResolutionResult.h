//
//  INMediaItemResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INMediaItem;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0), tvos(14.0))
API_UNAVAILABLE(macos)
@interface INMediaItemResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INMediaItem. The resolvedMediaItem can be different than the original INMediaItem. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedMediaItem:(INMediaItem *)resolvedMediaItem NS_SWIFT_NAME(success(with:));

// Convenience method to return multiple success resolution results for an array of INMediaItems
+ (NSArray<__kindof INMediaItemResolutionResult *> *)successesWithResolvedMediaItems:(NSArray<INMediaItem *> *)resolvedMediaItems NS_SWIFT_NAME(successes(with:));

// This resolution result is to ask Siri to disambiguate between the provided INMediaItem.
+ (instancetype)disambiguationWithMediaItemsToDisambiguate:(NSArray<INMediaItem *> *)mediaItemsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the mediaItem with which the user wants to continue.
+ (instancetype)confirmationRequiredWithMediaItemToConfirm:(nullable INMediaItem *)mediaItemToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

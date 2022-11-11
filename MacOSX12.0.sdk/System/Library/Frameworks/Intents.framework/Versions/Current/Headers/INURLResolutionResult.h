//
//  INURLResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INURLResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given url. The resolvedURL can be different than the original url. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedURL:(NSURL *)resolvedURL NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided urls.
+ (instancetype)disambiguationWithURLsToDisambiguate:(NSArray<NSURL *> *)urlsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the url with which the user wants to continue.
+ (instancetype)confirmationRequiredWithURLToConfirm:(nullable NSURL *)urlToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

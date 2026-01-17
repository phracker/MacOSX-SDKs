//
//  INEnumResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INEnumResolutionResult : INIntentResolutionResult

+ (instancetype)successWithResolvedValue:(NSInteger)resolvedValue NS_REFINED_FOR_SWIFT;

+ (instancetype)confirmationRequiredWithValueToConfirm:(NSInteger)valueToConfirm NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

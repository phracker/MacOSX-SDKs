//
//  INEnumResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macosx)
@interface INEnumResolutionResult : INIntentResolutionResult

+ (instancetype)successWithResolvedValue:(NSInteger)resolvedValue NS_REFINED_FOR_SWIFT;

+ (instancetype)confirmationRequiredWithValueToConfirm:(NSInteger)valueToConfirm NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

//
//  INDoubleResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INDoubleResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given number. The resolvedValue can be different than the original number. This allows app extensions to apply business logic constraints. For example, the extension could precisely control rounding the value.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedValue:(double)resolvedValue NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the double value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithValueToConfirm:(nullable NSNumber *)valueToConfirm NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

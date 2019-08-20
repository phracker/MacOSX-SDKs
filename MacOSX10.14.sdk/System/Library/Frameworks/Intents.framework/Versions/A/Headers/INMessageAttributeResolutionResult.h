//
//  INMessageAttributeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INMessageAttribute.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macosx)
@interface INMessageAttributeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INMessageAttribute. The resolvedValue can be different than the original INMessageAttribute. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedMessageAttribute:(INMessageAttribute)resolvedMessageAttribute NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INMessageAttribute)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedMessageAttribute:", ios(10.0, 11.0), watchos(3.2, 4.0));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithMessageAttributeToConfirm:(INMessageAttribute)messageAttributeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INMessageAttribute)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithMessageAttributeToConfirm:", ios(10.0, 11.0), watchos(3.2, 4.0));

@end

NS_ASSUME_NONNULL_END

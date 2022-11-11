//
//  INVisualCodeTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INVisualCodeType.h>

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("INVisualCodeTypeResolutionResult is deprecated. There is no replacement.", ios(11.0, 15.0), watchos(4.0, 8.0))
API_UNAVAILABLE(macos, tvos)
@interface INVisualCodeTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INVisualCodeType. The resolvedValue can be different than the original INVisualCodeType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedVisualCodeType:(INVisualCodeType)resolvedVisualCodeType NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithVisualCodeTypeToConfirm:(INVisualCodeType)visualCodeTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

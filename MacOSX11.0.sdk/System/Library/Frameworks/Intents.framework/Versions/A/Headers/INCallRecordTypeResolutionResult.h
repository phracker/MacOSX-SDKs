//
//  INCallRecordTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCallRecordType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INCallRecordTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCallRecordType. The resolvedValue can be different than the original INCallRecordType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCallRecordType:(INCallRecordType)resolvedCallRecordType NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INCallRecordType)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedCallRecordType:", ios(11.0, 11.0), watchos(4.0, 4.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCallRecordTypeToConfirm:(INCallRecordType)callRecordTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INCallRecordType)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithCallRecordTypeToConfirm:", ios(11.0, 11.0), watchos(4.0, 4.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END

//
//  INLengthResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2018 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INLengthResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given length. The resolvedLength can be different than the original length. This allows app extensions to apply business logic constraints to the length. For example, constraining it to a maximum or minimum value.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedLength:(NSMeasurement<NSUnitLength *> *)resolvedLength NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided lengths.
+ (instancetype)disambiguationWithLengthsToDisambiguate:(NSArray<NSMeasurement<NSUnitLength *> *> *)lengthsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the length with which the user wants to continue.
+ (instancetype)confirmationRequiredWithLengthToConfirm:(nullable NSMeasurement<NSUnitLength *> *)lengthToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

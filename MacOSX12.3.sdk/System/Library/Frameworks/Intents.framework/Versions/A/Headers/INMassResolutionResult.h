//
//  INMassResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INMassResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given mass. The resolvedMass can be different than the original mass. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedMass:(NSMeasurement<NSUnitMass *> *)resolvedMass NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided mass.
+ (instancetype)disambiguationWithMassToDisambiguate:(NSArray<NSMeasurement<NSUnitMass *> *> *)massToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the mass with which the user wants to continue.
+ (instancetype)confirmationRequiredWithMassToConfirm:(nullable NSMeasurement<NSUnitMass *> *)massToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

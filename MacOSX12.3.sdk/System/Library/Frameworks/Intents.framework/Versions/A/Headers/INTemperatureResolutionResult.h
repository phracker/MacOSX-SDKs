//
//  INTemperatureResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), macos(11.0), watchos(3.2))
API_UNAVAILABLE(tvos)
@interface INTemperatureResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given temperature. The resolvedTemperature can be different than the original temperature. This allows app extensions to apply business logic constraints to the temperature. For example, constraining it to a maximum or minimum value.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedTemperature:(NSMeasurement<NSUnitTemperature *> *)resolvedTemperature NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided temperatures.
+ (instancetype)disambiguationWithTemperaturesToDisambiguate:(NSArray<NSMeasurement<NSUnitTemperature *> *> *)temperaturesToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the temperature with which the user wants to continue.
+ (instancetype)confirmationRequiredWithTemperatureToConfirm:(nullable NSMeasurement<NSUnitTemperature *> *)temperatureToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

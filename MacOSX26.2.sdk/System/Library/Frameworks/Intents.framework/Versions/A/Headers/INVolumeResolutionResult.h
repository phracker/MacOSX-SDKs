//
//  INVolumeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INVolumeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given volume. The resolvedVolume can be different than the original volume. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedVolume:(NSMeasurement<NSUnitVolume *> *)resolvedVolume NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided volume.
+ (instancetype)disambiguationWithVolumeToDisambiguate:(NSArray<NSMeasurement<NSUnitVolume *> *> *)volumeToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the volume with which the user wants to continue.
+ (instancetype)confirmationRequiredWithVolumeToConfirm:(nullable NSMeasurement<NSUnitVolume *> *)volumeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

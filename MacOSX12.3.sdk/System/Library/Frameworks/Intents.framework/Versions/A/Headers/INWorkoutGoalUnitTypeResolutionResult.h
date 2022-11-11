//
//  INWorkoutGoalUnitTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INWorkoutGoalUnitType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2))
API_UNAVAILABLE(macos, tvos)
@interface INWorkoutGoalUnitTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INWorkoutGoalUnitType. The resolvedValue can be different than the original INWorkoutGoalUnitType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedWorkoutGoalUnitType:(INWorkoutGoalUnitType)resolvedWorkoutGoalUnitType NS_SWIFT_NAME(success(with:));

+ (instancetype)successWithResolvedValue:(INWorkoutGoalUnitType)resolvedValue NS_SWIFT_UNAVAILABLE("Please use 'success(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+successWithResolvedWorkoutGoalUnitType:", ios(10.0, 11.0), watchos(3.2, 4.0)) API_UNAVAILABLE(macos, tvos);

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithWorkoutGoalUnitTypeToConfirm:(INWorkoutGoalUnitType)workoutGoalUnitTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

+ (instancetype)confirmationRequiredWithValueToConfirm:(INWorkoutGoalUnitType)valueToConfirm NS_SWIFT_UNAVAILABLE("Please use 'confirmationRequired(with:)' instead.") API_DEPRECATED_WITH_REPLACEMENT("+confirmationRequiredWithWorkoutGoalUnitTypeToConfirm:", ios(10.0, 11.0), watchos(3.2, 4.0)) API_UNAVAILABLE(macos, tvos);

@end

NS_ASSUME_NONNULL_END

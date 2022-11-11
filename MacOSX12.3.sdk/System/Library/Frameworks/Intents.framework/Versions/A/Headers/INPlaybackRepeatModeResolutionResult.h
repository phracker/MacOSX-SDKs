//
//  INPlaybackRepeatModeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INPlaybackRepeatMode.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(12.0), watchos(5.0), tvos(14.0))
API_UNAVAILABLE(macos)
@interface INPlaybackRepeatModeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INPlaybackRepeatMode. The resolvedValue can be different than the original INPlaybackRepeatMode. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedPlaybackRepeatMode:(INPlaybackRepeatMode)resolvedPlaybackRepeatMode NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithPlaybackRepeatModeToConfirm:(INPlaybackRepeatMode)playbackRepeatModeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

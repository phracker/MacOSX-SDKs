//
//  INTaskResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INTask;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INTaskResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INTask. The resolvedTask can be different than the original INTask. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedTask:(INTask *)resolvedTask NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INTask.
+ (instancetype)disambiguationWithTasksToDisambiguate:(NSArray<INTask *> *)tasksToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the task with which the user wants to continue.
+ (instancetype)confirmationRequiredWithTaskToConfirm:(nullable INTask *)taskToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

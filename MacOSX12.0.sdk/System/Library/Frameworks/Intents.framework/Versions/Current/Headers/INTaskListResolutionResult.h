//
//  INTaskListResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INTaskList;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INTaskListResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INTaskList. The resolvedTaskList can be different than the original INTaskList. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedTaskList:(INTaskList *)resolvedTaskList NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INTaskList.
+ (instancetype)disambiguationWithTaskListsToDisambiguate:(NSArray<INTaskList *> *)taskListsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the taskList with which the user wants to continue.
+ (instancetype)confirmationRequiredWithTaskListToConfirm:(nullable INTaskList *)taskListToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

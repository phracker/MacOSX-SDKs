//
//  INNotebookItemTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INNotebookItemType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INNotebookItemTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INNotebookItemType. The resolvedValue can be different than the original INNotebookItemType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedNotebookItemType:(INNotebookItemType)resolvedNotebookItemType NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided values.
+ (instancetype)disambiguationWithNotebookItemTypesToDisambiguate:(NSArray<NSNumber *> *)notebookItemTypesToDisambiguate NS_REFINED_FOR_SWIFT;

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithNotebookItemTypeToConfirm:(INNotebookItemType)notebookItemTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

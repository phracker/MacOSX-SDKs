//
//  INCallRecordTypeOptionsResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INCallRecordTypeOptions.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), macos(12.0), watchos(4.0))
API_UNAVAILABLE(tvos)
@interface INCallRecordTypeOptionsResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCallRecordTypeOptions. The resolvedValue can be different than the original INCallRecordTypeOptions. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCallRecordTypeOptions:(INCallRecordTypeOptions)resolvedCallRecordTypeOptions NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCallRecordTypeOptionsToConfirm:(INCallRecordTypeOptions)callRecordTypeOptionsToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

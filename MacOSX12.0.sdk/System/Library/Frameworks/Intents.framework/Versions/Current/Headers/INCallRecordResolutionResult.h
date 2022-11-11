//
//  INCallRecordResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INCallRecord;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), macos(12.0), watchos(4.0))
API_UNAVAILABLE(tvos)
@interface INCallRecordResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INCallRecord. The resolvedCallRecord can be different than the original INCallRecord. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedCallRecord:(INCallRecord *)resolvedCallRecord NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INCallRecord.
+ (instancetype)disambiguationWithCallRecordsToDisambiguate:(NSArray<INCallRecord *> *)callRecordsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the callRecord with which the user wants to continue.
+ (instancetype)confirmationRequiredWithCallRecordToConfirm:(nullable INCallRecord *)callRecordToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

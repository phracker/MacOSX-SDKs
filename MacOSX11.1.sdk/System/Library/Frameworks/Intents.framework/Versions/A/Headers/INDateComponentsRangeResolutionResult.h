//
//  INDateComponentsRangeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos)
@interface INDateComponentsRangeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INDateComponentsRange. The resolvedDateComponentsRange can be different than the original INDateComponentsRange. This allows app extensions to pick a suitable range.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedDateComponentsRange:(INDateComponentsRange *)resolvedDateComponentsRange NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided date components ranges.
+ (instancetype)disambiguationWithDateComponentsRangesToDisambiguate:(NSArray<INDateComponentsRange *> *)dateComponentsRangesToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the date components range with which the user wants to continue.
+ (instancetype)confirmationRequiredWithDateComponentsRangeToConfirm:(nullable INDateComponentsRange *)dateComponentsRangeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

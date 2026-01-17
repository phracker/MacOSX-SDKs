//
//  INTimeIntervalResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INTimeIntervalResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed with a given value. The resolvedValue need not be identical to the input value. If the app extension wants to continue with a 'nil' value, it must use +notRequired.
+ (instancetype)successWithResolvedTimeInterval:(NSTimeInterval)resolvedTimeInterval NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the time interval value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithTimeIntervalToConfirm:(NSTimeInterval)timeIntervalToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

//
//  INObjectResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

@class INObject;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INObjectResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INObject. The resolvedObject can be different than the original INObject. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedObject:(INObject *)resolvedObject NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to disambiguate between the provided INObject.
+ (instancetype)disambiguationWithObjectsToDisambiguate:(NSArray<INObject *> *)objectsToDisambiguate NS_SWIFT_NAME(disambiguation(with:));

// This resolution result is to ask Siri to confirm if this is the object with which the user wants to continue.
+ (instancetype)confirmationRequiredWithObjectToConfirm:(nullable INObject *)objectToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

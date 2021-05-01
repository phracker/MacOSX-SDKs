//
//  INOutgoingMessageTypeResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentResolutionResult.h>

#import <Intents/INOutgoingMessageType.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), watchos(7.0))
API_UNAVAILABLE(macos, tvos)
@interface INOutgoingMessageTypeResolutionResult : INIntentResolutionResult

// This resolution result is for when the app extension wants to tell Siri to proceed, with a given INOutgoingMessageType. The resolvedValue can be different than the original INOutgoingMessageType. This allows app extensions to apply business logic constraints.
// Use +notRequired to continue with a 'nil' value.
+ (instancetype)successWithResolvedOutgoingMessageType:(INOutgoingMessageType)resolvedOutgoingMessageType NS_SWIFT_NAME(success(with:));

// This resolution result is to ask Siri to confirm if this is the value with which the user wants to continue.
+ (instancetype)confirmationRequiredWithOutgoingMessageTypeToConfirm:(INOutgoingMessageType)outgoingMessageTypeToConfirm NS_SWIFT_NAME(confirmationRequired(with:));

@end

NS_ASSUME_NONNULL_END

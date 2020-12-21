//
//  INSendMessageRecipientResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INPersonResolutionResult.h>

typedef NS_ENUM(NSInteger, INSendMessageRecipientUnsupportedReason) {
    INSendMessageRecipientUnsupportedReasonNoAccount = 1,
    INSendMessageRecipientUnsupportedReasonOffline,
    INSendMessageRecipientUnsupportedReasonMessagingServiceNotEnabledForRecipient,
    INSendMessageRecipientUnsupportedReasonNoValidHandle API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos),
    INSendMessageRecipientUnsupportedReasonRequestedHandleInvalid API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos),
    INSendMessageRecipientUnsupportedReasonNoHandleForLabel API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macos),
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos, tvos);

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INSendMessageRecipientResolutionResult : INPersonResolutionResult

+ (instancetype)unsupportedForReason:(INSendMessageRecipientUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithPersonResolutionResult:(INPersonResolutionResult *)personResolutionResult;

@end

NS_ASSUME_NONNULL_END

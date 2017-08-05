//
//  INSendMessageRecipientResolutionResult.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Intents/INPersonResolutionResult.h>

typedef NS_ENUM(NSInteger, INSendMessageRecipientUnsupportedReason) {
    INSendMessageRecipientUnsupportedReasonNoAccount = 1,
    INSendMessageRecipientUnsupportedReasonOffline,
    INSendMessageRecipientUnsupportedReasonMessagingServiceNotEnabledForRecipient,
} API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13));

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0), macosx(10.13))
@interface INSendMessageRecipientResolutionResult : INPersonResolutionResult

+ (instancetype)unsupportedForReason:(INSendMessageRecipientUnsupportedReason)reason NS_SWIFT_NAME(unsupported(forReason:));

- (instancetype)initWithPersonResolutionResult:(INPersonResolutionResult *)personResolutionResult;

@end

NS_ASSUME_NONNULL_END

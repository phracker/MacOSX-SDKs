//
//  INSendMessageIntentDonationMetadata.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Intents/INIntentDonationMetadata.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.0), macos(12.0), watchos(8.0))
API_UNAVAILABLE(tvos)
@interface INSendMessageIntentDonationMetadata : INIntentDonationMetadata

@property (NS_NONATOMIC_IOSONLY) BOOL mentionsCurrentUser;

@property (NS_NONATOMIC_IOSONLY, getter=isReplyToCurrentUser) BOOL replyToCurrentUser;

@property (NS_NONATOMIC_IOSONLY) BOOL notifyRecipientAnyway;

@property (NS_NONATOMIC_IOSONLY) NSUInteger recipientCount;

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

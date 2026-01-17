//
//  MEMessage.h
//  MailKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MEEmailAddress;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MEMessageState) {
    MEMessageStateReceived = 0,
    MEMessageStateDraft = 1,
    MEMessageStateSending = 2,
} API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos, macCatalyst) API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSInteger, MEMessageEncryptionState) {
    MEMessageEncryptionStateUnknown = 0,
    MEMessageEncryptionStateNotEncrypted = 1,
    MEMessageEncryptionStateEncrypted = 2,
} API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos);

/// @brief Contains information about a mail message on which actions can be performed.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos)
@interface MEMessage : NSObject <NSSecureCoding>

/// @brief The state of the mail message.
@property (nonatomic, readonly, assign) MEMessageState state;

/// @brief The encryption state of the mail message.
@property (nonatomic, readonly, assign) MEMessageEncryptionState encryptionState;

/// @brief The subject of the mail message.
@property (nonatomic, readonly, copy) NSString *subject;

/// @brief Message sender's email address.
@property (nonatomic, readonly, copy) MEEmailAddress *fromAddress;

/// @brief Recipient email addresses in the "To" address field of the message.
@property (nonatomic, readonly, copy) NSArray<MEEmailAddress *> *toAddresses;

/// @brief Recipient email addresses in the "Cc" address field of the message.
@property (nonatomic, readonly, copy) NSArray<MEEmailAddress *> *ccAddresses;

/// @brief Recipient email addresses in the "Bcc" address field of the message.
@property (nonatomic, readonly, copy) NSArray<MEEmailAddress *> *bccAddresses;

/// @brief Recipient email addresses in the "Reply-To" field of the message.
@property (nonatomic, readonly, copy) NSArray<MEEmailAddress *> *replyToAddresses;

/// @brief An array containing all recipients of the message.
@property (nonatomic, readonly, copy) NSArray<MEEmailAddress *> *allRecipientAddresses;

/// @brief The date the mail message was sent. Optionally set by the by the sender.
@property (nonatomic, nullable, readonly, copy) NSDate *dateSent NS_REFINED_FOR_SWIFT;

/// @brief The date the mail message was received. Only present if the message has been received.
@property (nonatomic, nullable, readonly, copy) NSDate *dateReceived NS_REFINED_FOR_SWIFT;

/// @brief The headers for the message. Might only be a subset if the full body has not been downloaded.
@property (nonatomic, nullable, readonly, copy) NSDictionary<NSString *, NSArray<NSString *> *> *headers;

/// @brief The full raw RFC822 message data if it has been downloaded and the extension has permissions to access.
@property (nonatomic, nullable, readonly, copy) NSData *rawData;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

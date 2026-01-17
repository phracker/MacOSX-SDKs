//
//  MEOutgoingMessageEncodingStatus.h
//  MailKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <MailKit/MEEmailAddress.h>

NS_ASSUME_NONNULL_BEGIN

/// @brief Contains information about any security measures that will be applied to a mail message when it is sent or any errrors that occurred while verifying security status.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos)
@interface MEOutgoingMessageEncodingStatus : NSObject <NSSecureCoding>

/// @brief Whether or not the message can be signed.
@property (nonatomic, readonly, assign) BOOL canSign;

/// @brief Whether or not the message can be encrypted.
@property (nonatomic, readonly, assign) BOOL canEncrypt;

/// @brief Any error that occurred while verifying the security status for the outgoing mail message.
@property (nonatomic, nullable, readonly, copy) NSError *securityError;

/// @brief A list of any recipients for which the message should be encrypted but an error occurred. This could include missing the public key for the recipient.
@property (nonatomic, readonly, copy) NSArray<MEEmailAddress *> *addressesFailingEncryption;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCanSign:(BOOL)canSign canEncrypt:(BOOL)canEncrypt securityError:(nullable NSError *)securityError addressesFailingEncryption:(NSArray<MEEmailAddress *> *)addressesFailingEncryption;

@end

NS_ASSUME_NONNULL_END

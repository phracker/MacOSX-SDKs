//
//  MEMessageEncodingResult.h
//  MailKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <MailKit/MEEncodedOutgoingMessage.h>

NS_ASSUME_NONNULL_BEGIN

/// @brief Contains information about an outging mail message after any security measures have been applied.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos)
@interface MEMessageEncodingResult : NSObject <NSSecureCoding>

/// @brief The encoded message. Nil if no need to encode or an error occured while encoding
@property (NS_NONATOMIC_IOSONLY, nullable, readonly, copy) MEEncodedOutgoingMessage *encodedMessage;

/// @brief Any error that occured while attempting to sign the outgoing message.
@property (NS_NONATOMIC_IOSONLY, nullable, readonly, copy) NSError *signingError;

/// @brief Any error that occured while attempting to encrypt the outgoing message.
@property (NS_NONATOMIC_IOSONLY, nullable, readonly, copy) NSError *encryptionError;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithEncodedMessage:(nullable MEEncodedOutgoingMessage *)encodedMessage signingError:(nullable NSError *)signingError encryptionError:(nullable NSError *)encryptionError NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

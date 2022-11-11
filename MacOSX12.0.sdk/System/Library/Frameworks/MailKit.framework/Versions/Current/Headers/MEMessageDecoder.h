//
//  MEMessageDecoder.h
//  MailKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <MailKit/MEDecodedMessage.h>

@class MEExtensionViewController;
@class MEMessageSigner;

NS_ASSUME_NONNULL_BEGIN

/// @brief Methods in this protocol can be used by a mail app extension to decode messages.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst)
@protocol MEMessageDecoder <NSObject>
/// @brief This is invoked while a message is being decoded. The returned value should be an @c MEDecodedMessage if the extension is needed for decoding the message. The returned @c MEDecodedMessage  should be created with unencrypted MIME data. The @c MEMessageSecurityInformation property on the @c MEDecodedMessage should contain any signing or encryption information about the decoded message. If the extension is not needed for decoding the message it should return quickly with @c nil.
/// @param data - The original data for the message.
- (nullable MEDecodedMessage *)decodedMessageForMessageData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END

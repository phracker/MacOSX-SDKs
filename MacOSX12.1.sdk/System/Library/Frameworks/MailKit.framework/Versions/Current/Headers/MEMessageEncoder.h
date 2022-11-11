//
//  MEMessageEncoder.h
//  MailKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MEComposeContext;
@class MEMessage;
@class MEMessageEncodingResult;
@class MEOutgoingMessageEncodingStatus;

NS_ASSUME_NONNULL_BEGIN

/// @brief Methods in this protocol can be used by a mail app extension to encode messages.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst)
@protocol MEMessageEncoder <NSObject>

/// @brief This is invoked while a message is being composed. This will be be invoked each time the sending address or the list of recipients changes. The supplied @c message will contain the email address of the sender, the recipient email addresses, and
///  the message data being sent.  The completion handler should be called with the current encoding status of the message indicating whether the message is able to be signed, encrypted, both or neither. The result will also contain any error that occured, including a list of any recipients whose encryption keys are expected and missing.
/// @param message - The outgoing message to apply any security mechanisms on.
/// @param composeContext - @c MEComposeContext instance which corresponds to the @c message being composed.
- (void)getEncodingStatusForMessage:(MEMessage *)message composeContext:(MEComposeContext *)composeContext completionHandler:(void (^)(MEOutgoingMessageEncodingStatus *status))completionHandler;

/// @brief This is invoked when an outgoing message is sent. The supplied @c message will contain the email address of the sender, the recipient email addresses, and
///  the message data being sent. The completion handler should be called with the @c result of applying any encoding if needed based on @c shouldSign and @c shouldEncrypt. If the @c result is not encrypted or signed and does not have  any errors, it is assumed the message did not need a signature or encryption applied. In this case the @c data for the result will be ignored.
/// @param message - The outgoing message to apply any security mechanisms on.
/// @param composeContext - @c MEComposeContext instance which corresponds to the @c message being composed.
- (void)encodeMessage:(MEMessage *)message composeContext:(MEComposeContext *)composeContext completionHandler:(void (^)(MEMessageEncodingResult *result))completionHandler;

@end

NS_ASSUME_NONNULL_END


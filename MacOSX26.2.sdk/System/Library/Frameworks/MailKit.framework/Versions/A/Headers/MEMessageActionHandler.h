//
//  MEMessageActionHandler.h
//  MailKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

@class MEMessage;
@class MEMessageAction;
@class MEMessageActionDecision;

NS_ASSUME_NONNULL_BEGIN

/// @brief Methods in this protocol can be used by a mail app extension to perform actions on messages as they are downloaded.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos)
@protocol MEMessageActionHandler <NSObject>

/// @brief This is invoked when a message is downloaded. The action set in the completion handler will be performed on the message. Depending on if the full body of the
/// message has been downloaded the @c MEMessage provided might have the full body data. If the full body is not present the @c decision property can be set to
/// @c MEMessageActionDecision.invokeAgainWithBody and this method will be invoked again once the full body is available.
/// @param message - The message for which the action will be performed. Might or might not contain the full message body data.
- (void)decideActionForMessage:(MEMessage *)message completionHandler:(void (^)(MEMessageActionDecision * _Nullable decision))completionHandler NS_SWIFT_NAME(decideAction(for:completionHandler:));


@optional

/// @brief Provide additional headers that the extension requires to perform an action. Mail will fetch these additional headers before invoking @c -[MEMessageActionHandler @c decideActionForMessage:completionHandler:].
/// For example, extensions can return the headers that were set in @c -[MEComposeSessionHandler @c additionalHeadersForSession:]
/// @return An array of header keys. Mail will normalize the headers to lower case before fetching them from the mail server.
@property (readonly, copy) NSArray<NSString *> *requiredHeaders;

@end

NS_ASSUME_NONNULL_END

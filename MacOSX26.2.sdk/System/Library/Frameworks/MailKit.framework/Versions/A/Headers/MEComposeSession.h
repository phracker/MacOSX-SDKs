//
//  MEComposeSession.h
//  MailKit
//
//  Copyright © 2020 Apple Inc. All rights reserved
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MEAddressAnnotation;
@class MEComposeContext;
@class MEEmailAddress;
@class MEExtensionViewController;
@class MEMessage;

/// @brief An instance of this class is associated with the lifecycle of a single mail compose window. This object associates the actions performed by the user in a mail compose window to a unique session. An instance of this class is passed to the methods in @c MEComposeSessionHandler.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos)
@interface MEComposeSession : NSObject <NSSecureCoding>

+ (instancetype)new NS_UNAVAILABLE; 
- (instancetype)init NS_UNAVAILABLE;

/// @brief A unique identifier for the session.
@property (nonatomic, readonly, strong) NSUUID *sessionID;

/// @brief An instance of @c MEMessage that represents properties of the mail message that author is composing in this @c MEComposeSession
@property (nonatomic, readonly, strong) MEMessage *mailMessage;

/// @brief An instance of @c MEComposeContext that provides additional information about the compose session.
@property (nonatomic, readonly, strong) MEComposeContext *composeContext;

/// @brief Requests Mail to refresh compose session with new information that the extension has.
/// @discussion Extensions can use this call this method to regenerate @c MEAddressAnnotation instances to replace those that were previously generated for this session. This will result in invocations to @c -[MEComposeSessionHandler @c session:annotateAddressesWithCompletionHandler:].
- (void)reloadSession;

@end

/// @brief Error domain and codes for extensions to report errors before message is delivered.
extern NSErrorDomain const MEComposeSessionErrorDomain API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos);

typedef NS_ERROR_ENUM(MEComposeSessionErrorDomain, MEComposeSessionErrorCode) {
    MEComposeSessionErrorCodeInvalidRecipients = 0,
    MEComposeSessionErrorCodeInvalidHeaders = 1,
    MEComposeSessionErrorCodeInvalidBody = 2,
} API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos);

/// @brief Methods in this protocol can be used by a mail app extension to keep track of new messages composed by the user and to make changes to the recipeint email address tokens.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos)
NS_SWIFT_UI_ACTOR
@protocol MEComposeSessionHandler <NSObject>

/// @brief This is invoked when a new message compose window is created.
/// @param session - @c MEComposeSession instance that is tied to the compose window that is opened.
- (void)mailComposeSessionDidBegin:(MEComposeSession *)session;

/// @brief This is invoked when a message compose window is closed.
/// @param session - @c MEComposeSession instance that is tied to the compose window that was closed.
- (void)mailComposeSessionDidEnd:(MEComposeSession *)session;

#if !TARGET_OS_WATCH
/// @brief A view controller to be presented in Mail compose window.
/// @discussion Mail will call this method when user clicks on the extension's button.
- (MEExtensionViewController *)viewControllerForSession:(MEComposeSession *)session;
#endif

@optional

/// @brief Delegate method to annotate mail addresses.
/// @discussion Mail will call this method based on user's input in To, Cc or Bcc fields.
- (void)session:(MEComposeSession *)session annotateAddressesWithCompletionHandler:(void (^)(NSDictionary<MEEmailAddress *, MEAddressAnnotation *> *emailAddressAnnotationMap))completionHandler NS_SWIFT_NAME(annotateAddressesForSession(_:completion:));

/// @brief Validate if the message is ready to be delivered to recipients.
/// @discussion Mail will call this method when user clicks on the send message button. Extensions can provide an error from the @c MEComposeSessionErrorDomain  error domain to indicate why message validation has failed.
- (void)session:(MEComposeSession *)session canSendMessageWithCompletionHandler:(void (^)(NSError * _Nullable error))completion NS_SWIFT_NAME(allowMessageSendForSession(_:completion:));

/// @brief Set Additional headers on outgoing mail message.
/// @discussion Mail will call this method to request additional headers to be set on the @c MEMessage that user is composing as part of this @c MEComposeSession. Keys in this dictionary will be normalized to lowercase before they are set on the message.
- (NSDictionary<NSString *, NSArray<NSString *> *> *)additionalHeadersForSession:(MEComposeSession *)session;

@end

NS_ASSUME_NONNULL_END

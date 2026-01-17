//
//  MEMessageSecurityHandler.h
//  MailKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <MailKit/MEMessageDecoder.h>
#import <MailKit/MEMessageEncoder.h>

NS_ASSUME_NONNULL_BEGIN

/// @brief Error domain and codes for extensions to report errors before message is delivered.
extern NSErrorDomain const MEMessageSecurityErrorDomain API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos);

typedef NS_ERROR_ENUM(MEMessageSecurityErrorDomain, MEMessageSecurityErrorCode) {
    MEMessageSecurityEncodingError = 0,
    MEMessageSecurityDecodingError = 1,
} API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos);

API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos)
NS_SWIFT_UI_ACTOR
@protocol MEMessageSecurityHandler <MEMessageEncoder, MEMessageDecoder>

#if !TARGET_OS_WATCH
/// @brief Invoked by Mail to request a subclass of @c MEExtensionViewController. Extensions can maintain any additional state in their subclasses and associate it with  @c messsageComposeSession instance.
- (nullable MEExtensionViewController *)extensionViewControllerForMessageSigners:(NSArray<MEMessageSigner *> *)messageSigners NS_SWIFT_NAME(extensionViewController(signers:));

/// @brief Invoked by Mail to request a subclass of @c MEExtensionViewController when the user clicks a banner or on the extensions icon in the message header view.
- (nullable MEExtensionViewController *)extensionViewControllerForMessageContext:(NSData *)context NS_SWIFT_NAME(extensionViewController(messageContext:));

/// @brief Invoked when the primary action for the message banner is clicked. The extension can provide an optional view controller to render any additional information.
- (void)primaryActionClickedForMessageContext:(NSData *)context completionHandler:(void (^)(MEExtensionViewController * _Nullable result))completionHandler;
#endif

@end

NS_ASSUME_NONNULL_END

//
//  MEExtension.h
//  MailKit
//
//  Copyright © 2021 Apple Inc. All rights reserved
//
//

#import <Foundation/Foundation.h>

@class MEComposeSession;
@protocol MEComposeSessionHandler;
@protocol MEContentBlocker;
@protocol MEMessageActionHandler;
@protocol MEMessageSecurityHandler;

NS_ASSUME_NONNULL_BEGIN

/// @brief A protocol which must be adopted by the class set as extension's `NSExtensionPrincipalClass`.
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, macCatalyst) API_UNAVAILABLE(tvos)
NS_SWIFT_UI_ACTOR
@protocol MEExtension <NSObject>

@optional
/// @brief A factory method for returning an instance of @c MEComposeSessionHandler
/// @param session An instance of @c MEComposeSession that represents a mail compose window.
- (id<MEComposeSessionHandler>)handlerForComposeSession:(MEComposeSession *)session;

/// @brief A factory method for returning an instance of @c MEMessageActionHandler
- (id<MEMessageActionHandler>)handlerForMessageActions;

/// @brief A factory method for returning an instance of @c MEContentBlocker
- (id<MEContentBlocker>)handlerForContentBlocker;

/// @brief A factory method for returning an instance of @c MEMessageSecurityHandler
- (id<MEMessageSecurityHandler>)handlerForMessageSecurity;

@end

NS_ASSUME_NONNULL_END



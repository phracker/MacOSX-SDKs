// Copyright © 2023 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// An object used to evaluate navigation events in an authentication session. When the session navigates
/// to a matching URL, it will pass the URL to the session completion handler.
API_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4), visionos(1.1))
NS_SWIFT_NAME(ASWebAuthenticationSession.Callback)
AS_SWIFT_SENDABLE
@interface ASWebAuthenticationSessionCallback : NSObject

/// Creates a callback object that matches against URLs with the given custom scheme.
/// @param customScheme The custom scheme that the app expects in the callback URL.
+ (instancetype)callbackWithCustomScheme:(NSString *)customScheme NS_SWIFT_NAME(customScheme(_:));

/// Creates a callback object that matches against HTTPS URLs with the given host and path.
/// @param host The host that the app expects in the callback URL. The host must be associated with the
/// app using associated web credentials domains.
/// @param path The path that the app expects in the callback URL.
+ (instancetype)callbackWithHTTPSHost:(NSString *)host path:(NSString *)path NS_SWIFT_NAME(https(host:path:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Check whether a given main-frame navigation URL matches the callback expected by the client app. Handles all URL-based callback strategies, including custom schemes and HTTPS navigations.
/// This is mainly meant for web browsers adopting the ASWebAuthenticationWebBrowser API, but may also be useful for other apps for debugging purposes.
/// @param url The URL to check.
- (BOOL)matchesURL:(NSURL *)url;

@end

NS_ASSUME_NONNULL_END

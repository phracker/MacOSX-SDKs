//
//  MSServiceAccount.h
//  MediaSetup
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, macosx, watchos)
/// Account details for accessing a streaming media service.
@interface MSServiceAccount : NSObject

/// Creates a new account.
///
/// - Parameters:
///   - serviceName: The name of the streaming media service.
///
///   - accountName: The user’s display name in the streaming media service.
- (instancetype)initWithServiceName:(NSString *)serviceName accountName:(NSString *)accountName NS_DESIGNATED_INITIALIZER;

/// The localized name of the streaming media service.
@property (nonatomic, copy, readonly) NSString *serviceName;

/// The user’s display name, email address, or other identifier in a streaming media service.
@property (nonatomic, copy, readonly) NSString *accountName;

/// A user identifier for the token request.
///
/// The Media Setup framework uses the ``MSServiceAccount/clientID`` to create a
/// token request. You can choose the identifier format, but the identifier must
/// be unique to the current account. You can provide a new identifier each time
/// the user begins the home setup.
@property (nonatomic, copy, readwrite, nullable) NSString *clientID;

/// A string that authenticates the user’s setup request.
///
/// The Media Setup framework uses the `clientSecret` to create a token request.
/// Hashed passwords are acceptable, but plaintext passwords aren't.
@property (nonatomic, copy, readwrite, nullable) NSString *clientSecret;

/// The path to access the configuration endpoint of your streaming media
/// service for the home.
///
/// The device retrieves the configuration with the OAuth 2.0 Bearer token.
@property (nonatomic, copy, readwrite, nullable) NSURL *configurationURL;

/// A URL that provides a token for the user’s HomePod speakers.
///
/// The authorization token URL is an OAuth 2.0 token service endpoint that provides a
/// Bearer Token for retrieving configuration.
@property (nonatomic, copy, readwrite, nullable) NSURL *authorizationTokenURL;

/// A list of permissions for the token request.
///
/// The authorization scope is an optional OAuth 2.0 scope parameter the system provides
/// when requesting a token.
@property (nonatomic, copy, readwrite, nullable) NSString *authorizationScope;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

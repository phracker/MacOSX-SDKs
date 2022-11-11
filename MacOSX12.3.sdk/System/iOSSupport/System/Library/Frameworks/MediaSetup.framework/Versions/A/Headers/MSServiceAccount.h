//
//  MSServiceAccount.h
//  MediaSetup
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, macosx, watchos)
@interface MSServiceAccount : NSObject

- (instancetype)initWithServiceName:(NSString *)serviceName accountName:(NSString *)accountName NS_DESIGNATED_INITIALIZER;

@property (nonatomic, copy, readonly) NSString *serviceName;
@property (nonatomic, copy, readonly) NSString *accountName;

/// clientID is used to create a HTTP Basic auth for a token request and should be unique for an account, though it can also be unique per registration.
@property (nonatomic, copy, readwrite, nullable) NSString *clientID;

/// clientSecret is used to create a HTTP Basic auth for a token request and is a freeform string that may be a hash, but not a plaintext password
@property (nonatomic, copy, readwrite, nullable) NSString *clientSecret;

/// configurationURL is a URL to the configuration endpoint of the CloudExtension instance servicing this account. The configuration is retrieved with the Oauth2 Bearer token.
@property (nonatomic, copy, readwrite, nullable) NSURL *configurationURL;

/// authorizationTokenURL is an OAuth 2.0 token service endpoint that can provide a Bearer token for retrieving configuration.
@property (nonatomic, copy, readwrite, nullable) NSURL *authorizationTokenURL;

/// authorizationScope is an optional OAuth 2.0 scope parameter provided when requesting a token.
@property (nonatomic, copy, readwrite, nullable) NSString *authorizationScope;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

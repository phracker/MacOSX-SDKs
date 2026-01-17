//
//  ASAuthorizationSingleSignOnProvider.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASFoundation.h>
#import <AuthenticationServices/ASAuthorizationProvider.h>
#import <AuthenticationServices/ASAuthorizationSingleSignOnRequest.h>

NS_ASSUME_NONNULL_BEGIN

AS_EXTERN API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(tvos, watchos)
@interface ASAuthorizationSingleSignOnProvider : NSObject <ASAuthorizationProvider>

/*! @abstract To get the right extension the identity provider main URL has to be provided. The URL is even part of the extension using assosiated domains mechanism or can be configured by MDM profile.
 */
+ (instancetype)authorizationProviderWithIdentityProviderURL:(NSURL *)url NS_SWIFT_NAME(init(identityProvider:));

- (ASAuthorizationSingleSignOnRequest *)createRequest;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly) NSURL *url;

/*! @abstract Returns YES if the configured provider is capable of performing authorization within a given configuration.
 */
@property (nonatomic, readonly, assign) BOOL canPerformAuthorization;

@end

NS_ASSUME_NONNULL_END

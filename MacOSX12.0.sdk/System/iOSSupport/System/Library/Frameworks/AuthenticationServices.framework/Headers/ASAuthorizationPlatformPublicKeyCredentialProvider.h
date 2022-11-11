// Copyright © 2020 Apple Inc. All rights reserved.

#import <AuthenticationServices/ASAuthorizationProvider.h>
#import <Foundation/Foundation.h>

@class ASAuthorizationPlatformPublicKeyCredentialAssertionRequest;
@class ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(watchos)
@interface ASAuthorizationPlatformPublicKeyCredentialProvider : NSObject <ASAuthorizationProvider>

- (instancetype)initWithRelyingPartyIdentifier:(NSString *)relyingPartyIdentifier NS_DESIGNATED_INITIALIZER;

/*! @abstract Create a request to register a new platform credential.
    @param challenge The challenge to sign.
    @param name The user name for the new credential.
    @param userID An identifier to be stored alongside the credential, which will be returned with the credential when it is used to authenticate.
 */
- (ASAuthorizationPlatformPublicKeyCredentialRegistrationRequest *)createCredentialRegistrationRequestWithChallenge:(NSData *)challenge name:(NSString *)name userID:(NSData *)userID NS_SWIFT_NAME(createCredentialRegistrationRequest(challenge:name:userID:));

/*! @abstract Create a request to authenticate using an existing credential.
    @param challenge The challenge to sign.
 */
- (ASAuthorizationPlatformPublicKeyCredentialAssertionRequest *)createCredentialAssertionRequestWithChallenge:(NSData *)challenge NS_SWIFT_NAME(createCredentialAssertionRequest(challenge:));

/*! @abstract The Relying Party identifier used for all requests created by this object.
 */
@property (nonatomic, readonly, copy) NSString *relyingPartyIdentifier;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

//
//  ASPasskeyRegistrationCredential.h
//  AuthenticationServices Framework
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <AuthenticationServices/ASAuthorizationCredential.h>
#import <AuthenticationServices/ASFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ASPasskeyRegistrationCredentialExtensionOutput;

/*! @class This class encapsulates a passkey registration response created by a credential provider extension.
 */
AS_EXTERN API_AVAILABLE(ios(17.0), macos(14.0)) API_UNAVAILABLE(tvos, watchos)
@interface ASPasskeyRegistrationCredential : NSObject <ASAuthorizationCredential>

/*! @abstract Initializes an ASPasskeyRegistrationCredential object.
 @param relyingParty The relying party identifier associated with this passkey.
 @param clientDataHash The JSON encoded client data for this registration result.
 @param credentialID The unique identifier for this passkey.
 @param attestationObject The attestation object for this passkey registration result.
 */
- (instancetype)initWithRelyingParty:(NSString *)relyingParty clientDataHash:(NSData *)clientDataHash credentialID:(NSData *)credentialID attestationObject:(NSData *)attestationObject;

/*! @abstract Initializes an ASPasskeyRegistrationCredential object.
 @param relyingParty The relying party identifier associated with this passkey.
 @param clientDataHash The JSON encoded client data for this registration result.
 @param credentialID The unique identifier for this passkey.
 @param attestationObject The attestation object for this passkey registration result.
 @param extensionOutput The output of WebAuthn extensions processed by the credential provider.
 */
- (instancetype)initWithRelyingParty:(NSString *)relyingParty clientDataHash:(NSData *)clientDataHash credentialID:(NSData *)credentialID attestationObject:(NSData *)attestationObject extensionOutput:(nullable ASPasskeyRegistrationCredentialExtensionOutput *)extensionOutput NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

/*! @abstract Creates and initializes an ASPasskeyRegistrationCredential object.
 @param relyingParty The relying party identifier associated with this passkey.
 @param clientDataHash The JSON encoded client data for this registration result.
 @param credentialID The unique identifier for this passkey.
 @param attestationObject The attestation object for this passkey registration result.
 */
+ (instancetype)credentialWithRelyingParty:(NSString *)relyingParty clientDataHash:(NSData *)clientDataHash credentialID:(NSData *)credentialID attestationObject:(NSData *)attestationObject;

/*! @abstract The relying party identifier associated with this passkey.
 */
@property (nonatomic, readonly) NSString *relyingParty;

/*! @abstract The hash of the client data for this registration result.
 */
@property (nonatomic, readonly) NSData *clientDataHash;

/*! @abstract The raw credential identifier of this passkey.
 */
@property (nonatomic, readonly) NSData *credentialID;

/*! @abstract The attestation object for this passkey registration result.
 */
@property (nonatomic, readonly) NSData *attestationObject;

/*! @abstract The outputs for WebAuthn extensions processed by the credential provider.
 */
@property (nonatomic, copy, nullable) ASPasskeyRegistrationCredentialExtensionOutput *extensionOutput NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(18.0), macos(15.0), visionos(2.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END

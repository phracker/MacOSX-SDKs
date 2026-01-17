//
//  ASAuthorizationProviderExtensionLoginManager.h
//  AuthenticationServices Framework
//
//  Copyright © 2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Security/Security.h>

@class ASAuthorizationProviderExtensionLoginConfiguration;
@class ASAuthorizationProviderExtensionUserLoginConfiguration;
typedef NS_ENUM(NSInteger, ASAuthorizationProviderExtensionAuthenticationMethod);

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, ASAuthorizationProviderExtensionKeyType)
{
    /// The user's device signing key.
    ASAuthorizationProviderExtensionKeyTypeUserDeviceSigning = 1,
    /// The user's device encryption key.
    ASAuthorizationProviderExtensionKeyTypeUserDeviceEncryption = 2,
    /// The user's Secure Enclave backed key.
    ASAuthorizationProviderExtensionKeyTypeUserSecureEnclaveKey = 3,
    /// The shared device signing key.
    ASAuthorizationProviderExtensionKeyTypeSharedDeviceSigning API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos) = 4,
    /// The shared device encryption key.
    ASAuthorizationProviderExtensionKeyTypeSharedDeviceEncryption API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos) = 5,
    /// The currentdevice signing key.
    ASAuthorizationProviderExtensionKeyTypeCurrentDeviceSigning API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos) = 10,
    /// The current device encryption key.
    ASAuthorizationProviderExtensionKeyTypeCurrentDeviceEncryption API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos) = 11,
    // The SmartCard for the user.
    ASAuthorizationProviderExtensionKeyTypeUserSmartCard API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos) = 20,
} API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos);

API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface ASAuthorizationProviderExtensionLoginManager : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// @abstract Returns YES if the current device completed registration.
@property (readonly, getter=isDeviceRegistered) BOOL deviceRegistered;

/// @abstract Returns YES if current user completed registration.
@property (readonly, getter=isUserRegistered) BOOL userRegistered;

/// @abstract Returns the device registration token from the MDM profile.
@property (nonatomic, nullable, readonly, copy) NSString *registrationToken;


/// @abstract Returns the authentication method used for the device.
@property (nonatomic, readonly) ASAuthorizationProviderExtensionAuthenticationMethod authenticationMethod API_AVAILABLE(macos(26.0)) API_UNAVAILABLE(ios, watchos, tvos);



/// @abstract Returns the extension data from the MDM profile.
@property (nonatomic, readonly, copy) NSDictionary *extensionData API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);


/// @abstract The user name to use when authenticating with the identity provider.
@property (nonatomic, nullable, copy) NSString *loginUserName API_DEPRECATED_WITH_REPLACEMENT("userLoginConfiguration.loginUserName", macos(13.0, 14.0));


/// @abstract Retrieves the current user login configuration for the extension.
@property (nonatomic, copy, nullable, readonly) ASAuthorizationProviderExtensionUserLoginConfiguration *userLoginConfiguration API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/// Saves or replaces the user login configration.
/// @param userLoginConfiguration The user login configration to use.
/// @param error The error when there are validation errors or nil.
- (BOOL)saveUserLoginConfiguration:(ASAuthorizationProviderExtensionUserLoginConfiguration *)userLoginConfiguration error:(NSError * _Nullable * _Nullable) error API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);


/// @abstract Retrieves or sets the current SSO tokens response for the current user and extension.
@property (nonatomic, copy, nullable) NSDictionary *ssoTokens;

/// @abstract Retrieves or sets the current login configuration for the extension.
@property (nonatomic, copy, nullable, readonly) ASAuthorizationProviderExtensionLoginConfiguration *loginConfiguration;

/// Saves or replaces the login configration.
/// @param loginConfiguration The login configration to use.
/// @param error The error when there are validation errors or nil.
- (BOOL)saveLoginConfiguration:(ASAuthorizationProviderExtensionLoginConfiguration *)loginConfiguration error:(NSError * _Nullable * _Nullable)error;

/// @abstract Saves the provided certificate for the key type.
/// @param certificate The certificate to save.
/// @param keyType The key type for the certificate.
- (void)saveCertificate:(SecCertificateRef)certificate keyType:(ASAuthorizationProviderExtensionKeyType)keyType NS_SWIFT_NAME(saveCertificate(_:keyType:));

/// @abstract Retrieves the key for the specified platform SSO key type.
/// @param keyType The key type to retrieve.
- (nullable SecKeyRef)copyKeyForKeyType:(ASAuthorizationProviderExtensionKeyType)keyType NS_SWIFT_NAME(key(for:)) CF_RETURNS_RETAINED;

/// @abstract Retrieves the identity for the specified platform SSO key type.
/// @param keyType The key type to retrieve.
- (nullable SecIdentityRef)copyIdentityForKeyType:(ASAuthorizationProviderExtensionKeyType)keyType NS_SWIFT_NAME(identity(for:)) CF_RETURNS_RETAINED;


/// @abstract Generates a new key for the specified platform SSO key type using the strongest supported key strength returning the new key.  Nil is returned if there is an error generating the new key.
/// @param keyType The key type to retrieve.
- (nullable SecKeyRef)beginKeyRotationForKeyType:(ASAuthorizationProviderExtensionKeyType)keyType API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos) NS_SWIFT_NAME(beginKeyRotation(_:)) CF_RETURNS_RETAINED;

/// @abstract Completes rotation for the key to replace the previous key.
/// @param keyType The key type to retrieve.
- (void)completeKeyRotationForKeyType:(ASAuthorizationProviderExtensionKeyType)keyType API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos) NS_SWIFT_NAME(completeKeyRotation(_:));


/// @abstract Requests AppSSOAgent reauthenticate the current user for the current extension.  This is used when the tokens are revoked, or expired and need to be requested again.
- (void)userNeedsReauthenticationWithCompletion:(void(^)(NSError * _Nullable error))completion;

/// @abstract Requests that the device registration be run again to repair it.
- (void)deviceRegistrationsNeedsRepair;

/// @abstract Requests that user registration be run again for the current user to repair it.
- (void)userRegistrationsNeedsRepair;


/// @abstract Requests that the decryption keys are repaired.
- (void)decryptionKeysNeedRepair API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);


/// @abstract Creates new Encryption, Signing, and Secure Enclave keys for the user.  The old keys will be destroyed.
- (void)resetKeys;


/// @abstract Creates new Encryption, and Signing keys for the device or user.  The old keys will be destroyed.
- (void)resetDeviceKeys API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/// @abstract Creates new Encryption, Signing, and Secure Enclave keys for the user.  The old keys will be destroyed.
- (void)resetUserSecureEnclaveKey API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);



/*!
 @abstract Provides a new or cached attestation for the specified key type.
 @param keyType The key type for the attestation.
 @param clientDataHash A SHA256 hash of a unique, single-use data block that embeds a challenge from your server.
 @param completion A closure that the method calls upon completion with the following parameters:
 *  * attestationCertificates An array of certificates that verify the validity of the key associated with the keyType. Send this to your server for processing.
 *  * error A DCError instance that indicates the reason for failure, or nil on success.
 */
- (void)attestKey:(ASAuthorizationProviderExtensionKeyType)keyType clientDataHash:(NSData *)clientDataHash completion:(void (^)(NSArray * _Nullable attestationCertificates, NSError * _Nullable error))completion NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.4)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract Provides a new or cached attestation for the specified pending key type.
 @param keyType The pending key type for the attestation.
 @param clientDataHash A SHA256 hash of a unique, single-use data block that embeds a challenge from your server.
 @param completion A closure that the method calls upon completion with the following parameters:
 *  * attestationCertificates An array of certificates that verify the validity of the pending key associated with the keyType. Send this to your server for processing.
 *  * error A DCError instance that indicates the reason for failure, or nil on success.
 */
- (void)attestPendingKey:(ASAuthorizationProviderExtensionKeyType)keyType clientDataHash:(NSData *)clientDataHash completion:(void (^)(NSArray * _Nullable attestationCertificates, NSError * _Nullable error))completion NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.4)) API_UNAVAILABLE(ios, watchos, tvos);


/*! @abstract Asks authorization service to show extension view controller for registration. If the controller cannot be shown an error is returned.  This is only valid during registration.
*/
- (void)presentRegistrationViewControllerWithCompletion:(void(^)(NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END

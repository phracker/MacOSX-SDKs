// Copyright © 2021 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

@class ASAuthorizationProviderExtensionLoginManager;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface ASAuthorizationProviderExtensionKerberosMapping : NSObject

/*!
 @abstract The keypath in the response JSON that uses this set of mappings.
 @discussion If the response tokens from login contain this keypath, then the mapping in this class will be used to create a Kerberos ticket. The expected response is a JSON dictionary with the supplied key names.
 */
@property (nonatomic, nullable, copy) NSString *ticketKeyPath;

/*!
 @abstract The key name that contains the base64 encoded kerberos AS-REP string.
 */
@property (nonatomic, nullable, copy) NSString *messageBufferKeyName;

/*!
 @abstract The key name that contains the Kerberos Realm string.
 */
@property (nonatomic, nullable, copy) NSString *realmKeyName;

/*!
 @abstract The key name that contains the Kerberos service name string.
 */
@property (nonatomic, nullable, copy) NSString *serviceNameKeyName;

/*!
 @abstract The key name that contains the Kerberos client name string.
 */
@property (nonatomic, nullable, copy) NSString *clientNameKeyName;

/*!
 @abstract The key name that contains the Kerberos session key type number.
 @discussion The value for this key should be the correct encryption type per RFC3962, section 7 for the session key.
 */
@property (nonatomic, nullable, copy) NSString *encryptionKeyTypeKeyName;

/*!
 @abstract The key name that contains the Kerberos session key.
 */
@property (nonatomic, nullable, copy) NSString *sessionKeyKeyName;

@end

API_AVAILABLE(macos(13.3)) API_UNAVAILABLE(ios, watchos, tvos)
typedef NS_ENUM(NSInteger, ASAuthorizationProviderExtensionFederationType)
{
    ASAuthorizationProviderExtensionFederationTypeNone = 0,
    ASAuthorizationProviderExtensionFederationTypeWSTrust = 1,
    ASAuthorizationProviderExtensionFederationTypeDynamicWSTrust = 2,
}  NS_SWIFT_NAME(ASAuthorizationProviderExtensionLoginConfiguration.FederationType);


API_UNAVAILABLE(macos) API_UNAVAILABLE(ios, watchos, tvos);
typedef NS_OPTIONS(NSUInteger, ASAuthorizationProviderExtensionUserSecureEnclaveKeyBiometricPolicy) {
    // No options.
    ASAuthorizationProviderExtensionUserSecureEnclaveKeyBiometricPolicyNone = 0,
    // Current Touch ID or Watch is required.
    ASAuthorizationProviderExtensionUserSecureEnclaveKeyBiometricPolicyTouchIDOrWatchCurrentSet = 1 << 0,
    // Any Touch ID or Watch is required.
    ASAuthorizationProviderExtensionUserSecureEnclaveKeyBiometricPolicyTouchIDOrWatchAny = 1 << 1,
    // Reuse Touch ID for unlock.
    ASAuthorizationProviderExtensionUserSecureEnclaveKeyBiometricPolicyReuseDuringUnlock = 1 << 2,
    // If Touch ID is cancelled, fails or is not setup, then prompt for idp password.
    ASAuthorizationProviderExtensionUserSecureEnclaveKeyBiometricPolicyPasswordFallback = 1 << 3,
} NS_SWIFT_NAME(ASAuthorizationProviderExtensionLoginConfiguration.UserSecureEnclaveKeyBiometricPolicy);



typedef NSNumber * ASAuthorizationProviderExtensionEncryptionAlgorithm API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos) NS_TYPED_EXTENSIBLE_ENUM;

/// A encryption algorithm that uses NIST P-256 elliptic curve key agreement, ConcatKDF key derivation
/// with a 256-bit digest, and the Advanced Encryption Standard cipher in Galois/Counter Mode with a key length of 256 bits.
AS_EXTERN ASAuthorizationProviderExtensionEncryptionAlgorithm const ASAuthorizationProviderExtensionEncryptionAlgorithmECDHE_A256GCM API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos) NS_SWIFT_NAME(ecdhe_A256GCM);

/// A cipher suite for HPKE that uses NIST P-256 elliptic curve key agreement, SHA-2 key derivation
/// with a 256-bit digest, and the Advanced Encryption Standard cipher in Galois/Counter Mode with a key length of 256 bits.
AS_EXTERN ASAuthorizationProviderExtensionEncryptionAlgorithm const ASAuthorizationProviderExtensionEncryptionAlgorithmHPKE_P256_SHA256_AES_GCM_256  API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos) NS_SWIFT_NAME(hpke_P256_SHA256_AES_GCM_256);

/// A cipher suite that you use for HPKE using NIST P-384 elliptic curve key agreement, SHA-2 key derivation
/// with a 384-bit digest, and the Advanced Encryption Standard cipher in Galois/Counter Mode with a key length of 256 bits.
AS_EXTERN ASAuthorizationProviderExtensionEncryptionAlgorithm const ASAuthorizationProviderExtensionEncryptionAlgorithmHPKE_P384_SHA384_AES_GCM_256  API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos) NS_SWIFT_NAME(hpke_P384_SHA384_AES_GCM_256);

/// A cipher suite for HPKE that uses X25519 elliptic curve key agreement, SHA-2 key derivation
/// with a 256-bit digest, and the ChaCha20 stream cipher with the Poly1305 message authentication code.
AS_EXTERN ASAuthorizationProviderExtensionEncryptionAlgorithm const ASAuthorizationProviderExtensionEncryptionAlgorithmHPKE_Curve25519_SHA256_ChachaPoly  API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos) NS_SWIFT_NAME(hpke_Curve25519_SHA256_ChachaPoly);

typedef NSNumber * ASAuthorizationProviderExtensionSigningAlgorithm API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos) NS_TYPED_EXTENSIBLE_ENUM;

// Use the ES256 signing algorithm per RFC 7518.
AS_EXTERN ASAuthorizationProviderExtensionSigningAlgorithm const ASAuthorizationProviderExtensionSigningAlgorithmES256 API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos) NS_SWIFT_NAME(es256);
// Use the ES384 signing algorithm per RFC 7518.
AS_EXTERN ASAuthorizationProviderExtensionSigningAlgorithm const ASAuthorizationProviderExtensionSigningAlgorithmES384 API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos) NS_SWIFT_NAME(es384);
// Use the Ed25519 signing algorithm per RFC 8032.
AS_EXTERN ASAuthorizationProviderExtensionSigningAlgorithm const ASAuthorizationProviderExtensionSigningAlgorithmEd25519 API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos) NS_SWIFT_NAME(ed25519);


API_AVAILABLE(macos(13.0)) API_UNAVAILABLE(ios, watchos, tvos)
@interface ASAuthorizationProviderExtensionLoginConfiguration : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Initializes an ASAuthorizationProviderExtensionLoginConfiguration class with the required values.
 @param clientID The client_id for the Apple platform SSO login at the identity provider.
 @param issuer The issuer for the requests, used to validate responses.
 @param tokenEndpointURL The token endpoint at the idP for login.
 @param jwksEndpointURL The JWKS URL at the idP for validating tokens.
 @param audience The audience used for signed assertions.  This should be the tenent at the idP.
 @return An instance of a ASAuthorizationProviderExtensionLoginConfiguration.
 */
- (instancetype)initWithClientID:(NSString *)clientID issuer:(NSString *)issuer tokenEndpointURL:(NSURL *)tokenEndpointURL jwksEndpointURL:(NSURL *)jwksEndpointURL audience:(nullable NSString *)audience;

/*!
 @abstract Creates a login configuration using the OpenID configuration.
 @param openIDConfigurationURL The base URL to load the .well-known/openid-configuration.
 @param clientID The client_id for the Apple platform SSO login at the identity provider.
 @param issuer The issuer for the requests, used to validate responses.
 @param completion The completion called when it is complete or the error.
 */
+ (void)configurationWithOpenIDConfigurationURL:(NSURL *)openIDConfigurationURL clientID:(NSString *)clientID issuer:(nullable NSString *)issuer completion:(void (^)(ASAuthorizationProviderExtensionLoginConfiguration * _Nullable loginConfiguration, NSError * _Nullable error))completion NS_SWIFT_NAME(configuration(openIDConfigurationURL:clientID:issuer:completion:));

/*!
 @abstract Predicate string used to identify invalid credential errors.
 @discussion If there is an HTTP 400 or HTTP 401 error when authenticating, this predicate will be used on the response body JSON to determine if the error is due to an invalid password or something else.  If nil, then only an HTTP 401 will be used for an invalid credential.
 */
@property (nonatomic, nullable, copy) NSString *invalidCredentialPredicate;

/*!
 @abstract The display name for the account.  Used for notifications and login prompts.
 */
@property (nonatomic, nullable, copy) NSString *accountDisplayName;

/*!
 @abstract The login client_id.
 */
@property (nonatomic, readonly, copy) NSString *clientID;

/*!
 @abstract The issuer for validation.
 */
@property (nonatomic, readonly, copy) NSString *issuer;

/*!
 @abstract The audience for validation and requests.
 */
@property (nonatomic, copy) NSString *audience;

/*!
 @abstract Token Endpoint URL for login request.
 */
@property (nonatomic, copy) NSURL *tokenEndpointURL;

/*!
 @abstract JWKS Endpoint URL for keys.
 */
@property (nonatomic, copy) NSURL *jwksEndpointURL;


/*!
 @abstract The root certificates to use for trust evaluation of jwks keys.
 @discussion if set, certificates will be required in jwks responses and evaluated using the supplied certificates.  If the jwks certificates are missing or fail trust evaluation the login will fail.
 */
@property (nonatomic, copy) NSArray *jwksTrustedRootCertificates NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The device context for storing device meta data.
 */
@property (nonatomic, nullable, copy) NSData *deviceContext API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);




/*!
 @abstract The biometric policy for User Secure Enclave Key authentication.
 */
@property (nonatomic) ASAuthorizationProviderExtensionUserSecureEnclaveKeyBiometricPolicy userSecureEnclaveKeyBiometricPolicy API_AVAILABLE(macos(14.4)) API_UNAVAILABLE(ios, watchos, tvos);


#pragma mark - Server Nonce

/*!
 @abstract Nonce Endpoint URL, defaults to token tokenEndpointURL.
 */
@property (nonatomic, copy) NSURL *nonceEndpointURL;

/*!
 @abstract The keypath in the nonce response that contains the nonce value.
 */
@property (nonatomic, copy) NSString *nonceResponseKeypath;

/*!
 @abstract The name of the server nonce claim when included in authentication requests.
 */
@property (nonatomic, copy) NSString *serverNonceClaimName;

/*!
 @abstract Custom values added to the server nonce POST request body.
 */
@property (nonatomic, copy) NSArray<NSURLQueryItem *> *customNonceRequestValues;

#pragma mark - Embedded Assertions

/*!
 @abstract Sets custom claims to be added to the embedded assertion request header.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomAssertionRequestHeaderClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable)error;

/*!
 @abstract Sets custom claims to be added to the embedded assertion request body.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomAssertionRequestBodyClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable)error;

#pragma mark - Login Request

/*!
 @abstract Additional login scopes.
 */
@property (nonatomic, copy) NSString *additionalScopes;


/*!
 @abstract Additional authorization scopes.
 */
@property (nonatomic, nullable, copy) NSString *additionalAuthorizationScopes API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);


/*!
 @abstract If true and there is a refresh token for the user in the SSO tokens, it will be included in the login request.
 */
@property (nonatomic) BOOL includePreviousRefreshTokenInLoginRequest;

/*!
 @abstract The claim name for the previous SSO token value in the login request.
 */
@property (nonatomic, copy) NSString *previousRefreshTokenClaimName;


/*!
 @abstract The request parameter name for the JWT.  The default is "assertion".
 */
@property (nonatomic, nullable, copy) NSString *customRequestJWTParameterName API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);


/*!
 @abstract Custom values added to the login POST request body.
 */
@property (nonatomic, copy) NSArray<NSURLQueryItem *> *customLoginRequestValues;

/*!
 @abstract Sets custom claims to be added to the login request header.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomLoginRequestHeaderClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable) error;

/*!
 @abstract Sets custom claims to be added to the login request body.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomLoginRequestBodyClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable) error;


/*!
 @abstract The claim name for the user unique identifier in the id token. Defaults to "sub".
 */
@property (nonatomic, nullable, copy) NSString *uniqueIdentifierClaimName API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The claim name for group membership request.
 */
@property (nonatomic, nullable, copy) NSString *groupRequestClaimName API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The claim name for group responses in the id_token.
 */
@property (nonatomic, nullable, copy) NSString *groupResponseClaimName API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);


/*!
 @abstract The Kerberos ticket mappings to use.
 */
@property (nonatomic, copy) NSArray<ASAuthorizationProviderExtensionKerberosMapping *> *kerberosTicketMappings;


#pragma mark - Refresh Request

/*!
 @abstract Token Refresh Endpoint URL for login request.  Defaults to the tokenEndpointURL.
 */
@property (nonatomic, nullable, copy) NSURL *refreshEndpointURL API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract Custom values added to the refresh POST request body.
 */
@property (nonatomic, copy) NSArray<NSURLQueryItem *> *customRefreshRequestValues API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract Sets custom claims to be added to the refresh request header.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomRefreshRequestHeaderClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable)error API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract Sets custom claims to be added to the refresh request bode.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomRefreshRequestBodyClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable)error API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);


// MARK: - Federation

/*!
 @abstract The federation method to use.
 */
@property (nonatomic) ASAuthorizationProviderExtensionFederationType federationType API_AVAILABLE(macos(13.3)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The URN to request when performing a federated login.
 */
@property (nonatomic, nullable, copy) NSString *federationRequestURN API_AVAILABLE(macos(13.3)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The federation MEX URL to use.  This can be overwritten when using dynamic federation.
 */
@property (nonatomic, nullable, copy) NSURL *federationMEXURL API_AVAILABLE(macos(13.3)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The URL to use when performing dynamic federation.
 */
@property (nonatomic, nullable, copy) NSURL *federationUserPreauthenticationURL API_AVAILABLE(macos(13.3)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The claim in the preauthentication response that contains the MEX URL.
 */
@property (nonatomic, nullable, copy) NSString *federationMEXURLKeypath API_AVAILABLE(macos(13.3)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The predicate to apply to the preauthentication response to perform federation or not.
 */
@property (nonatomic, nullable, copy) NSString *federationPredicate API_AVAILABLE(macos(13.3)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The custom query string values to add when making the preauthenticaion request.
 */
@property (nonatomic, copy) NSArray<NSURLQueryItem *> *customFederationUserPreauthenticationRequestValues API_AVAILABLE(macos(13.3)) API_UNAVAILABLE(ios, watchos, tvos);


// MARK: - Request Encryption

/*!
 @abstract The public key to use for encrypting the embedded login assertion.
 @discussion Only applies to password authentication.  If set, the password will encrypted in an embedded assertion instead of the login request itself.
 */
@property (nonatomic, nullable, assign) SecKeyRef loginRequestEncryptionPublicKey API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The APV prefix used for encrypted embedded login assertions.
 */
@property (nonatomic, nullable, copy) NSData *loginRequestEncryptionAPVPrefix API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);


/*!
 @abstract The encryption algorithm to use for the embedded login assertion.
 */
@property (nonatomic, copy) ASAuthorizationProviderExtensionEncryptionAlgorithm loginRequestEncryptionAlgorithm API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The PreSharedKey to be used for HKPE for embedded login assertions. Setting this value will change the mode to PSK if the loginRequestHPKEPreSharedKeyID is also set. Must be at least 32 bytes.
 */
@property (nonatomic, copy, nullable) NSData *loginRequestHPKEPreSharedKey API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract  The PreSharedKey Id to be used for HPKE PSK for embedded login assertions.  This is required if the loginRequestHPKEPreSharedKey is set.
 */
@property (nonatomic, copy, nullable) NSData *loginRequestHPKEPreSharedKeyID API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos);


// MARK: - Key Exchange

/*!
 @abstract The url endpoint for key service, defaults to token tokenEndpointURL.
 */
@property (nonatomic, nullable, copy) NSURL *keyEndpointURL API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract Custom values added to the key exchange POST request body.
 */
@property (nonatomic, copy) NSArray<NSURLQueryItem *> *customKeyExchangeRequestValues API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract Sets custom claims to be added to the key exchange request header.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomKeyExchangeRequestHeaderClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable)error API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract Sets custom claims to be added to the key exchange request body.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomKeyExchangeRequestBodyClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable)error API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract Custom values added to the key request POST request body.
 */
@property (nonatomic, copy) NSArray<NSURLQueryItem *> *customKeyRequestValues API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract Sets custom claims to be added to the key request header.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomKeyRequestHeaderClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable)error API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract Sets custom claims to be added to the key request body.
 @param claims The claims to be added. It must serialize as valid JSON to be accepted.
 @param error Nil or an NSError indicating why the claims were rejected.
 @returns YES when successful and NO when claims are rejected.
 */
- (BOOL)setCustomKeyRequestBodyClaims:(NSDictionary<NSString *, id> *)claims returningError:(NSError * _Nullable * _Nullable)error API_AVAILABLE(macos(14.0)) API_UNAVAILABLE(ios, watchos, tvos);



#pragma mark - HPKE

/*!
 @abstract The PreSharedKey to be used for HKPE. Setting this value will change the mode to PSK or AuthPSK if the hpkeAuthPublicKey is also set. Must be at least 32 bytes.
 */
@property (nonatomic, copy, nullable) NSData *hpkePreSharedKey API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The PreSharedKey Id to be used for HPKE PSK or AuthPSK mode.  This is requred if the hpkePreSharedKey is set.
 */
@property (nonatomic, copy, nullable) NSData *hpkePreSharedKeyID API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos);

/*!
 @abstract The Authentication public key to be used for HPKE.  Setting this value with changet the mode to Auth or AuthPSK if the hpkePreSharedKey is also set.  This public key is used to authenticate HPKE responses.
 */
@property (nonatomic, nullable) SecKeyRef hpkeAuthPublicKey API_AVAILABLE(macos(15.0)) API_UNAVAILABLE(ios, watchos, tvos);


@end

NS_ASSUME_NONNULL_END

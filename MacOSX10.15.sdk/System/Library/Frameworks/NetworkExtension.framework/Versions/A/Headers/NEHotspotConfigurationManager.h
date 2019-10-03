/*
 * Copyright © 2017-2019 Apple Inc.
 * All rights reserved.
 */

/*!
 * @file NEHotspotConfigurationManager.h
 *
 * @discussion
 *   The NEHotspotConfigurationManager interface allows an application to
 *   configure Wi-Fi networks.
 *   An application can use NEHotspotConfiguration API to configure
 *   Open, WEP, WPA/WPA2 Personal, WPA/WPA2 Enterprise and Hotspot 2.0 Wi-Fi networks.
 *
 *   An application that needs access to the NEHotspotConfiguration API must have
 *   the “com.apple.developer.networking.HotspotConfiguration” entitlement.
 *
 *
 * @ignorefuncmacro NS_OPTIONS
 * @ignorefuncmacro NS_ENUM
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#if defined(__cplusplus)
#define NEHSCFG_EXPORT extern "C"
#else
#define NEHSCFG_EXPORT extern
#endif

/*!
 * @typedef NEHotspotConfigurationEAPType
 * @abstract EAP Type.
 * @const NEHotspotConfigurationEAPTypeTLS EAP-TLS.
 * @const NEHotspotConfigurationEAPTypeTTLS TTLS.
 * @const NEHotspotConfigurationEAPTypePEAP PEAP.
 * @const NEHotspotConfigurationEAPTypeFAST EAP-FAST.
 */
typedef NS_ENUM(NSInteger, NEHotspotConfigurationEAPType) {
	NEHotspotConfigurationEAPTypeEAPTLS = 13,
	NEHotspotConfigurationEAPTypeEAPTTLS = 21,
	NEHotspotConfigurationEAPTypeEAPPEAP = 25,
	NEHotspotConfigurationEAPTypeEAPFAST = 43
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos) NS_SWIFT_NAME(NEHotspotEAPSettings.EAPType);

/*!
 * @typedef NEHotspotConfigurationEAPTTLSInnerAuthenticationType
 * @abstract TTLS Inner Authentication Type.
 * @const NEHotspotConfigurationEAPTTLSInnerAuthenticationPAP PAP.
 * @const NEHotspotConfigurationEAPTTLSInnerAuthenticationCHAP CHAP.
 * @const NEHotspotConfigurationEAPTTLSInnerAuthenticationMSCHAP MSCHAP.
 * @const NEHotspotConfigurationEAPTTLSInnerAuthenticationMSCHAPv2 MSCHAPv2.
 * @const NEHotspotConfigurationEAPTTLSInnerAuthenticationEAP EAP (Default).
 */
typedef NS_ENUM(NSInteger, NEHotspotConfigurationTTLSInnerAuthenticationType) {
	NEHotspotConfigurationEAPTTLSInnerAuthenticationPAP = 0,
	NEHotspotConfigurationEAPTTLSInnerAuthenticationCHAP = 1,
	NEHotspotConfigurationEAPTTLSInnerAuthenticationMSCHAP = 2,
	NEHotspotConfigurationEAPTTLSInnerAuthenticationMSCHAPv2 = 3,
	NEHotspotConfigurationEAPTTLSInnerAuthenticationEAP = 4
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos) NS_SWIFT_NAME(NEHotspotEAPSettings.TTLSInnerAuthenticationType);

/*!
 * @typedef NEHotspotConfigurationEAPTLSVersion
 * @abstract TLS version to use during TLS handshke.
 * @const NEHotspotConfigurationEAPTLSVersion_1_0 TLS version 1.0.
 * @const NEHotspotConfigurationEAPTLSVersion_1_1 TLS version 1.1.
 * @const NEHotspotConfigurationEAPTLSVersion_1_1 TLS version 1.2 (Default).
 */
typedef NS_ENUM(NSInteger, NEHotspotConfigurationEAPTLSVersion) {
	NEHotspotConfigurationEAPTLSVersion_1_0 = 0,
	NEHotspotConfigurationEAPTLSVersion_1_1 = 1,
	NEHotspotConfigurationEAPTLSVersion_1_2 = 2,
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos) NS_SWIFT_NAME(NEHotspotEAPSettings.TLSVersion);

/*!
 * @interface NEHotspotHS20Settings
 * @discussion
 *   NEHotspotHS20Settings class provides a set of properties that are required
 *   to discover and negotiate Hotspot 2.0 Wi-Fi networks.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEHotspotHS20Settings : NSObject <NSCopying,NSSecureCoding>

/*!
 * @property domainName
 * @discussion Domain Name of Legacy Hotspot or Hotspot 2.0 Wi-Fi Network.
 *   This Domain Name is used for Wi-Fi Hotspot 2.0 negotiation.
 */
@property (nonnull, readonly) NSString *domainName API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property roamingEnabled
 * @discussion If set to YES, allows connection to networks of roaming service
 *   providers. Defaults to NO.
 */
@property (getter=isRoamingEnabled) BOOL roamingEnabled API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property roamingConsortiumOIs
 * @discussion Array of Roaming Consortium Organization Identifiers used
 *   for Wi-Fi Hotspot 2.0 negotiation.
 */
@property (copy) NSArray<NSString *> *roamingConsortiumOIs API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property naiRealmNames
 * @discussion Array of Network Access Identifier Realm names used for
 *   Wi-Fi Hotspot 2.0 negotiation.
 */
@property (copy) NSArray<NSString *> *naiRealmNames API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property MCCAndMNCs
 * @discussion Array of Mobile Country Code (MCC)/Mobile Network Code (MNC)
 *   pairs used for Wi-Fi Hotspot 2.0 negotiation. Each string must contain
 *   exactly six digits.
 */
@property (copy) NSArray<NSString *> *MCCAndMNCs API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithDomainName:roamingEnabled
 * @discussion
 *   A designated initializer to instantiate a new NEHotspotHSSettings object.
 *   This initializer is used to configure Legacy Hotspot or HS2.0 Wi-Fi Networks.
 *
 * @param domainName The domain name of HS2.0 Wi-Fi Network
 * @param roamingEnabled If YES, allows connections to networks of roaming service providers.
 */
- (instancetype)initWithDomainName:(NSString *)domainName
						   roamingEnabled:(BOOL)roamingEnabled API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

/*!
 * @interface NEHotspotEAPSettings
 * @discussion
 *   NEHotspotEAPSettings class provides a set of properties that are required
 *   to configure a WPA/WPA2 Enterprise or Hotspot 2.0 Wi-Fi networks.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEHotspotEAPSettings : NSObject <NSCopying,NSSecureCoding>

/*!
 * @property supportedEAPTypes
 * @discussion Array of supported EAP Types. Refer to NEHotspotConfigurationEAPType
 *   for valid values.
 */
@property (copy) NSArray<NSNumber *> *supportedEAPTypes API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property username
 * @discussion A UTF-8 encoded string containing username component of the user authentication
 *   credentials. Length of this property must be between 1 and 253 characters.
 */
@property (copy) NSString *username API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property outerIdentity
 * @discussion Identity string to be used in EAP-Response/Identity of the outer phase. This key is only
 *   relevant to TTLS, PEAP, and EAP-FAST.
 */
@property (copy) NSString *outerIdentity API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property ttlsInnerAuthentication
 * @discussion Specifies the inner authentication used by the TTLS module.
 *   Possible values are PAP, CHAP, MSCHAP, MSCHAPv2, and EAP. Defaults to EAP.
 */
@property NEHotspotConfigurationTTLSInnerAuthenticationType ttlsInnerAuthenticationType API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property password
 * @discussion The password component of the 802.1X authentication credential.
 *   Length of this property must be between 1 and 64 characters.
 */
@property (copy) NSString *password API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property trustedServerNames
 * @discussion Array of server certificate common names that will be used to verify server's certificate.
 *   The string could have wildcards to specify the name, such as "*.mycompany.net". If a server presents
 *   a certificate with DNSName or Common Name that isn't in this list, it won't be trusted.
 */
@property (copy) NSArray<NSString *> *trustedServerNames API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property isTLSClientCertificateRequired
 * @discussion If YES, supports two-factor authentication for EAP-TTLS, PEAP, or EAP-FAST.
 *   If NO, allows for zero-factor authentication for EAP-TLS. The default is YES for EAP-TLS,
 *   and NO for other EAP types.
 */
@property (getter=isTLSClientCertificateRequired) BOOL tlsClientCertificateRequired API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property preferredTLSVersion
 * @discussion TLS version to use during the TLS handshake.
 *   Default value is NEHotspotConfigurationEAPTLSVersion_1_2.
 */
@property NEHotspotConfigurationEAPTLSVersion preferredTLSVersion API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method setIdentity
 * @discussion Setter to configure the EAP peer identity. The application needs to store
 * this identity in keychain access group "$(TeamIdentifierPrefix)com.apple.networkextensionsharing".
 * The API uses SecItemCopyMatching to obtain persistent reference for this identity from application's
 * keychain and uses that at the time of EAP authentication.
 * This property is mandatory when EAP-TLS is desired or tlsClientCertificateRequired is set to YES.
 *
 * @param identity The identity of the EAP Peer. This is a SecIdentityRef object that contains
 * a SecKeyRef object and an associated SecCertificateRef object.
 * @result returns NO if the parameter is not an object of SecIdentityRef type or if the persistent reference
 * is not found in the application's keychain else returns YES.
 *
 */
- (BOOL) setIdentity:(SecIdentityRef) identity API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method setTrustedServerCertificates
 * @discussion Setter to configure an array of trusted server certificates used for trust evaluation of
 * the server certificate.
 *
 * @param certificates Each value in the array is a SecCertificateRef object. Application needs to store
 * the certificates in keychain access group "$(TeamIdentifierPrefix)com.apple.networkextensionsharing".
 * The API uses SecItemCopyMatching to obtain persistent reference for each certificate from application's
 * keychain and uses that at the time os EAP authentication.
 * Number of elements in the array cannot be more than 10.
 *
 * @result returns NO if any element in the array is not an object of type SecCertificateRef or if API
 * fails to find persistent reference for each element from the application's keychain else return YES.
 */
- (BOOL) setTrustedServerCertificates:(NSArray *) certificates API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

/*!
 * @interface NEHotspotConfiguration
 * @discussion
 *   The NEHotspotConfiguration class represents set of properties that are required
 *   to configure a Wi-Fi Network.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEHotspotConfiguration : NSObject <NSCopying,NSSecureCoding>

/*!
 * @property SSID
 * @discussion SSID of the Wi-Fi Network.
 */
@property (readonly) NSString * SSID API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property SSIDPrefix
 * @discussion Prefix string of SSID of the Wi-Fi Network.
 */
@property (readonly) NSString * SSIDPrefix API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property joinOnce
 * @discussion if set to YES the configuration will not be persisted. Default is NO.
 */
@property BOOL joinOnce API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property lifeTimeInDays
 * @discussion The lifetime of the configuration in days. The configuration is stored for the
 *   number of days specified by this property. The minimum value is 1 day and maximum value is 365 days.
 *   A configuration does not get deleted automatically if this property is not set or set to an invalid value.
 *   This property does not apply to Enterprise and HS2.0 networks.
 */
@property (copy) NSNumber * lifeTimeInDays API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @property hidden
 * @discussion if set to YES the system will perform active scan of the SSID. Default is NO.
 */
@property BOOL hidden API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithSSID:
 * @discussion
 *   A designated initializer to instantiate a new NEHotspotConfiguration object.
 *   This initializer is used to configure open Wi-Fi Networks.
 *
 * @param SSID The SSID of the Open Wi-Fi Network.
 *   Length of SSID must be between 1 and 32 characters.
 */
- (instancetype)initWithSSID:(NSString *)SSID API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithSSID:passphrase:isWEP
 * @discussion
 *   A designated initializer to instantiate a new NEHotspotConfiguration object.
 *   This initializer is used configure either WEP or WPA/WPA2 Personal Wi-Fi Networks.
 *
 * @param SSID The SSID of the WEP or WPA/WPA2 Personal Wi-Fi Network
 * @param passphrase The passphrase credential.
 *   For WPA/WPA2 Personal networks: between 8 and 63 characters.
 *   For Static WEP(64bit)  : 10 Hex Digits
 *   For Static WEP(128bit) : 26 Hex Digits
 * @param isWEP YES specifies WEP Wi-Fi Network else WPA/WPA2 Personal Wi-Fi Network
 */
- (instancetype)initWithSSID:(NSString *)SSID
					  passphrase:(NSString *)passphrase isWEP:(BOOL)isWEP API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithSSID:eapSettings
 * @discussion
 *   A designated initializer to instantiate a new NEHotspotConfiguration object.
 *   This initializer is used configure WPA/WPA2 Enterprise Wi-Fi Networks.
 *
 * @param SSID The SSID of WPA/WPA2 Enterprise Wi-Fi Network
 * @param eapSettings EAP configuration
 */
- (instancetype)initWithSSID:(NSString *)SSID
					  eapSettings:(NEHotspotEAPSettings *)eapSettings API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithHS20Settings:eapSettings
 * @discussion
 *   A designated initializer to instantiate a new NEHotspotConfiguration object.
 *   This initializer is used configure HS2.0 Wi-Fi Networks.
 *
 * @param hs20Settings Hotspot 2.0 configuration
 * @param eapSettings EAP configuration
 */
- (instancetype)initWithHS20Settings:(NEHotspotHS20Settings *)hs20Settings
						eapSettings:(NEHotspotEAPSettings *)eapSettings API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithSSIDPrefix:
 * @discussion
 *   A designated initializer to instantiate a new NEHotspotConfiguration object.
 *   This initializer is used to configure open Wi-Fi Networks.
 *
 * @param SSIDPrefix The prefix string of SSID of the Open Wi-Fi Network.
 *   Length of SSIDPrefix must be between 3 and 32 characters.
 */
- (instancetype)initWithSSIDPrefix:(NSString *)SSIDPrefix API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method initWithSSIDPrefix:passphrase:isWEP
 * @discussion
 *   A designated initializer to instantiate a new NEHotspotConfiguration object.
 *   This initializer is used configure either WEP or WPA/WPA2 Personal Wi-Fi Networks.
 *
 * @param SSIDPrefix The prefix string of SSID of the WEP or WPA/WPA2 Personal Wi-Fi Network.
 * 	Length of SSIDPrefix must be between 3 and 32 characters.
 * @param passphrase The passphrase credential.
 *   For WPA/WPA2 Personal networks: between 8 and 63 characters.
 *   For Static WEP(64bit)  : 10 Hex Digits
 *   For Static WEP(128bit) : 26 Hex Digits
 * @param isWEP YES specifies WEP Wi-Fi Network else WPA/WPA2 Personal Wi-Fi Network
 */
- (instancetype)initWithSSIDPrefix:(NSString *)SSIDPrefix
				  passphrase:(NSString *)passphrase isWEP:(BOOL)isWEP API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

/*! @const NEHotspotConfigurationErrorDomain The Hotspot Configuration error domain */
NEHSCFG_EXPORT NSString * const NEHotspotConfigurationErrorDomain API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @typedef NEHotspotConfigurationError
 * @abstract Hotspot Configuration error codes
 * @const NEHotspotConfigurationErrorInvalid The Wi-Fi configuration is invalid
 * @const NEHotspotConfigurationErrorInvalidSSID The given SSID string is invalid.
 * @const NEHotspotConfigurationErrorInvalidWPAPassphrase The given WPA/WPA2 Personal passphrase is invalid.
 * @const NEHotspotConfigurationErrorInvalidWEPPassphrase The given WEP passphrase is invalid.
 * @const NEHotspotConfigurationErrorInvalidEAPSettings  Invalid EAP Settings.
 * @const NEHotspotConfigurationErrorInvalidHS20Settings Invalid Hotspot 2.0 Settings.
 * @const NEHotspotConfigurationErrorInvalidHS20DomainName The given Hotspot 2.0 domain name is invalid.
 * @const NEHotspotConfigurationErrorUserDenied Failed to get the user's approval to add a new configuration.
 * @const NEHotspotConfigurationErrorInternal An internal error was encountered.
 * @const NEHotspotConfigurationErrorPending Previous request by the calling application is pending.
 * @const NEHotspotConfigurationErrorSystemConfiguration The calling application cannot modify the System(MDM/Carrier) configuration.
 * @const NEHotspotConfigurationErrorUnknown An unknown configuration error occurred.
 * @const NEHotspotConfigurationErrorJoinOnceNotSupported JoinOnce option is not support for EAP configuration.
 * @const NEHotspotConfigurationErrorAlreadyAssociated Wi-Fi is already associated.
 * @const NEHotspotConfigurationErrorApplicationIsNotInForeground The application is not in the foreground.
 * @const NEHotspotConfigurationErrorInvalidSSIDPrefix The given SSID Prefix string is invalid.
 */
typedef NS_ENUM(NSInteger, NEHotspotConfigurationError) {
	NEHotspotConfigurationErrorInvalid 				= 0,
	NEHotspotConfigurationErrorInvalidSSID 				= 1,
	NEHotspotConfigurationErrorInvalidWPAPassphrase 		= 2,
	NEHotspotConfigurationErrorInvalidWEPPassphrase 		= 3,
	NEHotspotConfigurationErrorInvalidEAPSettings 			= 4,
	NEHotspotConfigurationErrorInvalidHS20Settings 			= 5,
	NEHotspotConfigurationErrorInvalidHS20DomainName 		= 6,
	NEHotspotConfigurationErrorUserDenied 				= 7,
	NEHotspotConfigurationErrorInternal 				= 8,
	NEHotspotConfigurationErrorPending 				= 9,
	NEHotspotConfigurationErrorSystemConfiguration 			= 10,
	NEHotspotConfigurationErrorUnknown 				= 11,
	NEHotspotConfigurationErrorJoinOnceNotSupported 		= 12,
	NEHotspotConfigurationErrorAlreadyAssociated 			= 13,
	NEHotspotConfigurationErrorApplicationIsNotInForeground 	= 14,
	NEHotspotConfigurationErrorInvalidSSIDPrefix 				= 15
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @interface NEHotspotConfigurationManager
 * @discussion
 *   The NEHotspotConfigurationManager class allows an application to
 *   Add/Update/Remove Wi-Fi Network Configuraton.
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface NEHotspotConfigurationManager : NSObject

@property (class, readonly, strong) NEHotspotConfigurationManager *sharedManager;

/*!
 * @method applyConfiguration:
 * @discussion This function adds or updates a Wi-Fi network configuration.
 * @param configuration NEHotspotConfiguration object containing the Wi-Fi network configuration.
 * @param completionHandler A block that will be called when add/update operation is completed.
 *   This could be nil if application does not intend to receive the result.
 *   The NSError passed to this block will be nil if the configuration is successfully stored, non-nil otherwise.
 *   If the configuration is found invalid or API encounters some other error then completionHandler is called
 *   with instance of NSError containing appropriate error code. This API attempts to join the Wi-Fi network
 *   if the configuration is successfully added or updated and the network is found nearby.
 *
 */
- (void)applyConfiguration:(NEHotspotConfiguration *)configuration
						completionHandler:(void (^ __nullable)(NSError * __nullable error))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method removeConfigurationForSSID:
 * @discussion This function removes Wi-Fi configuration.
 *   If the joinOnce property was set to YES, invoking this method will disassociate from the Wi-Fi network
 *   after the configuration is removed.
 * @param SSID Wi-Fi SSID for which the configuration is to be deleted.
 */
- (void)removeConfigurationForSSID:(NSString *)SSID API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

/*!
 * @method removeConfigurationForNetworkName:
 * @discussion This function removes Wi-Fi configuration.
 * @param domainName HS2.0 domainName for which the configuration is to be deleted.
 */
- (void)removeConfigurationForHS20DomainName:(NSString *)domainName API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);


/*!
 * @method getConfiguredSSIDsWithCompletionHandler:
 * @discussion This function returns array of SSIDs and HS2.0 Domain Names that the calling application has configured.
 *   It returns nil if there are no networks configurred by the calling application.
 */
- (void)getConfiguredSSIDsWithCompletionHandler:(void (^)(NSArray<NSString *> *))completionHandler API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos);

@end

NS_ASSUME_NONNULL_END

//
//  TKTokenConfiguration.h
//  Copyright © 2018 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CryptoTokenKit/TKTokenKeychainItem.h>

NS_ASSUME_NONNULL_BEGIN

@class TKToken;
@class TKTokenDriver;
@class TKTokenDriverConfiguration;
@class TKTokenConfiguration;

/// Holds configuration of one class of tokens
API_AVAILABLE(macos(10.15), ios(14.0), tvos(14.0), watchos(7.0))
NS_SWIFT_NAME(TKTokenDriver.Configuration)
@interface TKTokenDriverConfiguration : NSObject

/// Contains dictionary of token class configurations keyed by TKTokenDriverClassID of token driver.
///
/// Hosting application of token extension will contain the list of configurations for hosted token extensions. All other callers will get an empty array. This means that only token's hosting application can actually modify token's configuration. Typically, hosting application will contain only one token extension, therefore this dictionary will have one element.
@property (class, nonatomic, readonly) NSDictionary<TKTokenDriverClassID, TKTokenDriverConfiguration *> *driverConfigurations;

/// ClassID of the token configuration. ClassID is taken from @p com.apple.ctk.class-id token extension attribute.
@property (nonatomic, readonly) TKTokenDriverClassID classID;

/// Dictionary of all currently configured tokens for this token class, keyed by instanceID.
@property (nonatomic, readonly, copy) NSDictionary<TKTokenInstanceID, TKTokenConfiguration *> *tokenConfigurations;

/// Creates new configuration object for token with specified instanceID and adds it into tokenConfigurations dictionary. If configuration with specified instanceID already exists, it is replaced with new empty configuration.
- (TKTokenConfiguration *)addTokenConfigurationForTokenInstanceID:(TKTokenInstanceID)instanceID
NS_SWIFT_NAME(addTokenConfiguration(for:));

/// Removes configuration with specified tokenID. Does nothing if no such token configuration exists.
- (void)removeTokenConfigurationForTokenInstanceID:(TKTokenInstanceID)instanceID
NS_SWIFT_NAME(removeTokenConfiguration(for:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// Holds configuration of one token identified by unique token's instanceID
API_AVAILABLE(macos(10.15), ios(14.0), tvos(14.0), watchos(7.0))
NS_SWIFT_NAME(TKToken.Configuration)
@interface TKTokenConfiguration : NSObject

/// Unique, persistent identifier of this token, always created by specific token implementation. Typically implemented by some kind of serial number of the target hardware, for example SmartCard serial number.
@property (nonatomic, readonly) TKTokenInstanceID instanceID;

/// Additional configuration available for token instance.
///
/// Token implementation and its hosting application can use this data for specifying any additional configuration for the token. System does not interpret this data in any way. For example, network-based HSM can store here (using Codable or other serialization mechanisms) target network address, access credentials and the list of identities accessible in the HSM.
@property (nonatomic, readwrite, nullable, copy) NSData *configurationData;

/// All keychain items of this token.
@property (nonatomic, readwrite, copy) NSArray<__kindof TKTokenKeychainItem *> *keychainItems;

/// Returns keychain item key with specified objectID.  Fills error with TKTokenErrorCodeObjectNotFound if no such key exists.
- (nullable TKTokenKeychainKey *)keyForObjectID:(TKTokenObjectID)objectID error:(NSError **)error
NS_SWIFT_NAME(key(for:));

/// Returns certificate with specified objectID.  Fills error with TKTokenErrorCodeObjectNotFound if no such certificate exists.
- (nullable TKTokenKeychainCertificate *)certificateForObjectID:(TKTokenObjectID)objectID error:(NSError **)error
NS_SWIFT_NAME(certificate(for:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

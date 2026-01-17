#if !__has_include(<PassKitCore/PKAddIdentityDocumentConfiguration.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKAddIdentityDocumentConfiguration.h
//    PassKit
//
//  Copyright © 2023 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <PassKit/PKAddSecureElementPassConfiguration.h>


typedef NS_ENUM(NSInteger, PKAddIdentityDocumentType) {
    PKAddIdentityDocumentTypeIDCard NS_SWIFT_NAME(idCard),
    PKAddIdentityDocumentTypeMDL NS_SWIFT_NAME(mDL),
    PKAddIdentityDocumentTypePhotoID
}; API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos);

API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKIdentityDocumentMetadata: NSObject

- (null_unspecified instancetype)init NS_UNAVAILABLE;
+ (null_unspecified instancetype)new NS_UNAVAILABLE;

/// credentialIdentifier: A unique identifier for provisioning credential data.
@property (nonatomic, strong, readonly, nonnull) NSString *credentialIdentifier;
/// sharingInstanceIdentifier: A unique identifier that refers to an instance of sharing of credentials to a user's device initiated from another user, device, or web.
@property (nonatomic, strong, readonly, nonnull) NSString *sharingInstanceIdentifier;
/// cardTemplateIdentifier: Identifier referencing a card template registered by developers in web portal - identifies a combination of cardProfileIdentifier, cardConfigurationIdentifier, and cardArtBundleName.
/// Returns empty string if no identifier is set.
@property (nonatomic, strong, readonly, nonnull) NSString *cardTemplateIdentifier;
/// cardConfigurationIdentifier: Identifier referencing a card configuration registered by developers.
/// Returns empty string if no identifier is set.
@property (nonatomic, strong, readonly, nonnull) NSString *cardConfigurationIdentifier;
/// serverEnvironmentIdentifier: Identifier referencing the target server environment Apple Pay servers should reach out to to provision this pass.
/// If not present, the default Apply Pay server environment will be used and an empty string will be returned.
@property (nonatomic, strong, nonnull) NSString *serverEnvironmentIdentifier;
///  issuingCountryCode: identifies the issuing country of the identity document
@property (nonatomic, strong, readonly, nonnull) NSString *issuingCountryCode API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos);
///identityDocumentType: identifies the type of the identity document
@property(nonatomic, readonly) PKAddIdentityDocumentType documentType API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos);

@end

API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKAddIdentityDocumentMetadata: PKIdentityDocumentMetadata

/// Initialize with parameters configured by issuer's server to indicate the specific product instance to provision.
/// - Properties:
///   - provisioningCredentialIdentifier: Identifies this user's instance for provisioning.
///   - sharingInstanceIdentifier: A short lived token to prevent replay-ability.
///   - cardTemplateIdentifier: An identifier for a legacy product on our Apple Pay servers.
///   - preview: Object containing information to represent the pass to provision in our UI.
///   - issuingCountryCode:  identifies the issuing country of the identity document
///   - identityDocumentType: identifies the type of the identity document
///   - preview: Object containing information to represent the pass to provision in our UI.
- (nonnull instancetype)initWithProvisioningCredentialIdentifier:(NSString * _Nonnull)credentialIdentifier
                                       sharingInstanceIdentifier:(NSString * _Nonnull)sharingInstanceIdentifier
                                          cardTemplateIdentifier:(NSString * _Nonnull)templateIdentifier
                                              issuingCountryCode:(NSString * _Nonnull)issuingCountryCode
                                                    documentType:(PKAddIdentityDocumentType)documentType
                                                         preview:(PKAddPassMetadataPreview * _Nonnull)preview;
// Display Properties

/// preview: A preview object containing the necessary information to represent the pass during provisioning.
@property (nonatomic, strong, readonly, nonnull) PKAddPassMetadataPreview *preview;

@end


API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKJapanIndividualNumberCardMetadata: PKIdentityDocumentMetadata

/// Initialize with parameters configured by issuer's server to indicate the specific product instance to provision.
/// - Properties:
///   - provisioningCredentialIdentifier: Identifies this user's instance for provisioning.
///   - sharingInstanceIdentifier: A short lived token to prevent replay-ability.
///   - cardTemplateIdentifier: An identifier for a legacy product on our Apple Pay servers.
///   - preview: Object containing information to represent the pass to provision in our UI.
- (nonnull instancetype)initWithProvisioningCredentialIdentifier:(NSString * _Nonnull)credentialIdentifier
                                       sharingInstanceIdentifier:(NSString * _Nonnull)sharingInstanceIdentifier
                                          cardTemplateIdentifier:(NSString * _Nonnull)templateIdentifier
                                                         preview:(PKAddPassMetadataPreview * _Nonnull)preview;

/// Initialize with parameters configured by issuer's server to indicate the specific product instance to provision.
/// - Properties:
///   - provisioningCredentialIdentifier: Identifies this user's instance for provisioning.
///   - sharingInstanceIdentifier: A short lived token to prevent replay-ability.
///   - cardConfigurationIdentifier: An identifier for a product on our Apple Pay servers.
///   - preview: Object containing information to represent the pass to provision in our UI.
- (nonnull instancetype)initWithProvisioningCredentialIdentifier:(NSString * _Nonnull)credentialIdentifier
                                       sharingInstanceIdentifier:(NSString * _Nonnull)sharingInstanceIdentifier
                                     cardConfigurationIdentifier:(NSString * _Nonnull)cardConfigurationIdentifier
                                                         preview:(PKAddPassMetadataPreview * _Nonnull)preview;

// Configuration Properties

/// Raw authentication password used to protect authentication functionality.
/// If configured in the pass, this functionality allows users to present their identity credentials to external parties.
@property (nonatomic, copy, nullable) NSString *authenticationPassword;

/// Raw signing password used to protect signing functionality.
/// If configured in the pass, this functionality allows users to digitally sign with external parties or print officially signed documents.
@property (nonatomic, copy, nullable) NSString *signingPassword;

// Display Properties

/// preview: A preview object containing the necessary information to represent the pass during provisioning.
@property (nonatomic, strong, readwrite, nonnull) PKAddPassMetadataPreview *preview;

@end

API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKAddIdentityDocumentConfiguration : PKAddSecureElementPassConfiguration

/// Initialize identity document configuration with corresponding identity document metadata.
/// - Parameters:
///   - metadata: Set of configured metadata defining the required information to add the corresponding pass to Wallet.
///   - completion: Returns the identity document configuration if successful, otherwise returns an error.
+ (void)configurationForMetadata:(PKIdentityDocumentMetadata * _Nonnull)metadata
                      completion:(void(^_Nonnull)(PKAddIdentityDocumentConfiguration * _Nullable credentialConfiguration, NSError * _Nullable error))completion
NS_SWIFT_NAME(forMetadata(_:completion:));

/// metadata: Set of configured metadata defining the required information to add the corresponding pass to Wallet.
@property (nonatomic, strong, readonly, nonnull) PKIdentityDocumentMetadata *metadata;

@end


#else
#import <TargetConditionals.h>
#import <PassKitCore/PKAddIdentityDocumentConfiguration.h>
#endif
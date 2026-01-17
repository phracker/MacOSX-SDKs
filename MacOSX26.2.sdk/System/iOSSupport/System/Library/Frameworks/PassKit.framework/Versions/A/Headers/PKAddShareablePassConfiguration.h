#if !__has_include(<PassKitCore/PKAddShareablePassConfiguration.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKAddShareablePassConfiguration.h
//    PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <PassKit/PKAddSecureElementPassConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NAME(PKShareablePassMetadata.Preview)
@interface PKShareablePassMetadataPreview : PKAddPassMetadataPreview

- (instancetype)initWithTemplateIdentifier:(NSString *)templateIdentifier;

+ (instancetype)previewWithTemplateIdentifier:(NSString *)templateIdentifier;

@property (nonatomic, strong, nullable) NSString *ownerDisplayName;
@property (nonatomic, strong, readonly, nullable) NSString *provisioningTemplateIdentifier;

@end


API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKShareablePassMetadata : NSObject

- (nullable instancetype)initWithProvisioningCredentialIdentifier:(NSString *)credentialIdentifier
                                      cardConfigurationIdentifier:(NSString *)cardConfigurationIdentifier
                                        sharingInstanceIdentifier:(NSString *)sharingInstanceIdentifier
                                               passThumbnailImage:(CGImageRef)passThumbnailImage
                                                 ownerDisplayName:(NSString *)ownerDisplayName
                                             localizedDescription:(NSString *)localizedDescription
API_DEPRECATED("Use initWithProvisioningCredentialIdentifier:sharingInstanceIdentifier:cardConfigurationIdentifier:passPreviewMetadata:", ios(14.0, 16.0));

- (instancetype)initWithProvisioningCredentialIdentifier:(NSString *)credentialIdentifier
                               sharingInstanceIdentifier:(NSString *)sharingInstanceIdentifier
                                      passThumbnailImage:(CGImageRef)passThumbnailImage
                                        ownerDisplayName:(NSString *)ownerDisplayName
                                    localizedDescription:(NSString *)localizedDescription
                                             accountHash:(NSString *)accountHash
                                      templateIdentifier:(NSString *)templateIdentifier
                                  relyingPartyIdentifier:(NSString *)relyingPartyIdentifier
                      requiresUnifiedAccessCapableDevice:(BOOL)requiresUnifiedAccessCapableDevice
API_DEPRECATED("Use initWithProvisioningCredentialIdentifier:sharingInstanceIdentifier:cardTemplateIdentifier:passPreviewMetadata:", ios(15.0, 16.0));

- (instancetype)initWithProvisioningCredentialIdentifier:(NSString *)credentialIdentifier
                               sharingInstanceIdentifier:(NSString *)sharingInstanceIdentifier
                                  cardTemplateIdentifier:(NSString *)templateIdentifier
                                                 preview:(PKShareablePassMetadataPreview *)preview
API_AVAILABLE(ios(16.0))
API_UNAVAILABLE(watchos, tvos);

- (instancetype)initWithProvisioningCredentialIdentifier:(NSString *)credentialIdentifier
                               sharingInstanceIdentifier:(NSString *)sharingInstanceIdentifier
                             cardConfigurationIdentifier:(NSString *)templateIdentifier
                                                 preview:(PKShareablePassMetadataPreview *)preview
API_AVAILABLE(ios(16.0))
API_UNAVAILABLE(watchos, tvos);

// Pass Configuration Properties

// A unique identifier for provisioning credential data.
@property (nonatomic, strong, readonly) NSString *credentialIdentifier;
// A unique identifier that refers to an instance of sharing of credentials to a user's device initiated from another user, device, or web.
@property (nonatomic, strong, readonly) NSString *sharingInstanceIdentifier;
// Identifier referencing a card template registered in portal - identifies a combination of cardProfileIdentifier, cardConfigurationIdentifier, and cardArtBundleName.
@property (nonatomic, strong, readonly) NSString *templateIdentifier API_DEPRECATED_WITH_REPLACEMENT("cardTemplateIdentifier", ios(15.0, 16.0));
// Identifier referencing a card template registered in portal - identifies a combination of cardProfileIdentifier, cardConfigurationIdentifier, and cardArtBundleName.
@property (nonatomic, strong, readonly) NSString *cardTemplateIdentifier API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos);
@property (nonatomic, strong, readonly) NSString *cardConfigurationIdentifier;
// Specify that the passes to provision require a unified access capable device.
// This is primarily used when provisioning a pass that uses an ISO18013-5 payload.
@property (nonatomic, assign) BOOL requiresUnifiedAccessCapableDevice API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);

// Identifier referencing the target server environment Apple Pay servers should reach
// out to to provision this pass.
@property (nonatomic, strong) NSString *serverEnvironmentIdentifier API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos);

// Display Properties

@property (nonatomic, strong, readonly) PKShareablePassMetadataPreview *preview API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos, tvos);

@property (nonatomic, readonly) CGImageRef passThumbnailImage CF_RETURNS_NOT_RETAINED API_DEPRECATED_WITH_REPLACEMENT("preview.passThumbnailImage", ios(14.0, 16.0), watchos(8.0, 9.0));
@property (nonatomic, strong, readonly) NSString *localizedDescription API_DEPRECATED_WITH_REPLACEMENT("preview.localizedDescription", ios(14.0, 16.0), watchos(8.0, 9.0));
@property (nonatomic, strong, readonly) NSString *ownerDisplayName API_DEPRECATED_WITH_REPLACEMENT("preview.ownerDisplayName", ios(14.0, 16.0), watchos(8.0, 9.0));

// FIDO Properties

// An identifier representing an entity that uses a FIDO protocol to directly authenticate users.
@property (nonatomic, strong) NSString *accountHash API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);
// Unique accountHash representing the external account in partner's system. This value needs to be the same for all the provisionings pointing to the same user account.
@property (nonatomic, strong) NSString *relyingPartyIdentifier API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos);

@end


typedef NS_ENUM(NSUInteger, PKAddShareablePassConfigurationPrimaryAction) {
    PKAddShareablePassConfigurationPrimaryActionAdd,
    PKAddShareablePassConfigurationPrimaryActionShare
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos);

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKAddShareablePassConfiguration : PKAddSecureElementPassConfiguration

+ (void)configurationForPassMetadata:(NSArray<PKShareablePassMetadata *> *)passMetadata
        provisioningPolicyIdentifier:(NSString *)provisioningPolicyIdentifier
                       primaryAction:(PKAddShareablePassConfigurationPrimaryAction)action
                          completion:(void(^)(PKAddShareablePassConfiguration * _Nullable shareableCredentialConfiguration, NSError * _Nullable error))completion
NS_SWIFT_NAME(forPassMetaData(_:provisioningPolicyIdentifier:action:completion:))
API_DEPRECATED("Use configurationForPassMetadata:primaryAction:completion:", ios(14.0, 16.0), watchos(7.0, 9.0));

+ (void)configurationForPassMetadata:(NSArray<PKShareablePassMetadata *> *)passMetadata
                       primaryAction:(PKAddShareablePassConfigurationPrimaryAction)action
                          completion:(void(^)(PKAddShareablePassConfiguration * _Nullable shareableCredentialConfiguration, NSError * _Nullable error))completion
NS_SWIFT_NAME(forPassMetadata(_:action:completion:))
API_AVAILABLE(ios(16.0))
API_UNAVAILABLE(watchos, tvos);

@property (nonatomic, readonly) PKAddShareablePassConfigurationPrimaryAction primaryAction;
@property (nonatomic, strong, readonly) NSArray<PKShareablePassMetadata *> *credentialsMetadata;
@property (nonatomic, strong, readonly) NSString *provisioningPolicyIdentifier API_DEPRECATED("provisioningPolicyIdentifier has been deprecated. You can stop setting this property in the init with no repercussions.", ios(14.0, 16.0), watchos(7.0, 9.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <TargetConditionals.h>
#import <PassKitCore/PKAddShareablePassConfiguration.h>
#endif
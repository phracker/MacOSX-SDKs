//
//  PKAddShareablePassConfiguration.h
//  PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGImage.h>

#import <PassKit/PKAddSecureElementPassConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKShareablePassMetadata : NSObject

- (nullable instancetype)initWithProvisioningCredentialIdentifier:(NSString *)credentialIdentifier
                                      cardConfigurationIdentifier:(NSString *)cardConfigurationIdentifier
                                        sharingInstanceIdentifier:(NSString *)sharingInstanceIdentifier
                                               passThumbnailImage:(CGImageRef)passThumbnailImage
                                                 ownerDisplayName:(NSString *)ownerDisplayName
                                             localizedDescription:(NSString *)localizedDescription;

@property (nonatomic, strong, readonly) NSString *credentialIdentifier;
@property (nonatomic, strong, readonly) NSString *cardConfigurationIdentifier;
@property (nonatomic, strong, readonly) NSString *sharingInstanceIdentifier;

@property (nonatomic, readonly) CGImageRef passThumbnailImage CF_RETURNS_NOT_RETAINED;

@property (nonatomic, strong, readonly) NSString *localizedDescription;
@property (nonatomic, strong, readonly) NSString *ownerDisplayName;

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
                          completion:(void(^)(PKAddShareablePassConfiguration * _Nullable shareableCredentialConfiguration, NSError * _Nullable error))completion NS_SWIFT_NAME(forPassMetaData(_:provisioningPolicyIdentifier:action:completion:));

@property (nonatomic, readonly) PKAddShareablePassConfigurationPrimaryAction primaryAction;
@property (nonatomic, strong, readonly) NSArray<PKShareablePassMetadata *> *credentialsMetadata;
@property (nonatomic, strong, readonly) NSString *provisioningPolicyIdentifier;

@end

NS_ASSUME_NONNULL_END

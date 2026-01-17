#if !__has_include(<PassKitCore/PKAddSecureElementPassConfiguration.h>) || PK_USE_PUBLIC_PASSKIT
//
//  PKAddSecureElementPassConfiguration.h
//    PassKit
//
//  Copyright © 2020 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGImage.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos, tvos)
@interface PKAddPassMetadataPreview: NSObject

/// Initializer preview object to represent the pass being added to Wallet.which requires a CGImage of the pass's card art and a localized description.
/// - Properties:
///   - passThumbnail: CGImage representing the card artwork of the pass to be presented during provisioning.
///   - localizedDescription: Localized description of the pass.
- (nonnull instancetype)initWithPassThumbnail:(CGImageRef)passThumbnail
                         localizedDescription:(NSString *)description;

+ (instancetype)previewWithPassThumbnail:(CGImageRef)passThumbnail
                    localizedDescription:(NSString *)description;

- (null_unspecified instancetype)init NS_UNAVAILABLE;
+ (null_unspecified instancetype)new NS_UNAVAILABLE;

/// CGImage representing the pass in our provisioning UI.
@property (nonatomic, assign, readonly, nullable) CGImageRef passThumbnailImage CF_RETURNS_NOT_RETAINED;

/// Localized description of the pass to be referenced during provisioning.
@property (nonatomic, strong, readonly, nullable) NSString *localizedDescription;

@end

API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos)
@interface PKAddSecureElementPassConfiguration : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, copy, nullable) NSString *issuerIdentifier;
@property (nonatomic, copy, nullable) NSString *localizedDescription;

@end

NS_ASSUME_NONNULL_END


#else
#import <TargetConditionals.h>
#import <PassKitCore/PKAddSecureElementPassConfiguration.h>
#endif
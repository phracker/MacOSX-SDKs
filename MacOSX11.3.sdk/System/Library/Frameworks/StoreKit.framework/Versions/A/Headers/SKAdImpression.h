//
//  SKAdImpression.h
//  StoreKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXTERN_CLASS API_AVAILABLE(ios(14.5)) API_UNAVAILABLE(macos, watchos) __TVOS_PROHIBITED @interface SKAdImpression : NSObject

/// The App Store item identifier for the source app.
@property (nonatomic, strong) NSNumber *sourceAppStoreItemIdentifier;

/// The App Store item identifier for the app being advertised.
@property (nonatomic, strong) NSNumber *advertisedAppStoreItemIdentifier;

/// The identifier for the ad network.
@property (nonatomic, strong) NSString *adNetworkIdentifier;

/// The ad campaign identifier.
@property (nonatomic, strong) NSNumber *adCampaignIdentifier;

/// The nonce used to generate the signature.
@property (nonatomic, strong) NSString *adImpressionIdentifier;

/// The type of ad being presented.
@property (nonatomic, strong, nullable) NSString *adType;

/// The description of the ad.
@property (nonatomic, strong, nullable) NSString *adDescription;

/// Name of entity that purchased the ad being presented.
@property (nonatomic, strong, nullable) NSString *adPurchaserName;

/// The timestamp of the start and end call.
@property (nonatomic, strong) NSNumber *timestamp;

/// The signature of the impression.
@property (nonatomic, strong) NSString *signature;

/// The version of SKAdNetwork being used.
@property (nonatomic, strong) NSString *version;

@end

NS_ASSUME_NONNULL_END

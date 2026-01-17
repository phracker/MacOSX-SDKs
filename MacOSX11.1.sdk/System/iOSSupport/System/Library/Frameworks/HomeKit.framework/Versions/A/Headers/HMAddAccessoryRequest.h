//
//  HMAddAccessoryRequest.h
//  HomeKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAccessory;
@class HMAccessoryCategory;
@class HMAccessoryOwnershipToken;
@class HMAccessorySetupPayload;
@class HMHome;

HM_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos, macCatalyst)
@interface HMAddAccessoryRequest : NSObject

/*!
 * @brief Home that the accessory is to be added to.
 */
@property (nonatomic, readonly, strong) HMHome *home;

/*!
 * @brief Name of the accessory to be added.
 */
@property (nonatomic, readonly) NSString *accessoryName;

/*!
 * @brief The category of the accessory to be added.
 */
@property (nonatomic, strong, readonly) HMAccessoryCategory *accessoryCategory;

/*!
 * @brief Indication if the setup URL needs to be updated for this request. If this is true,
 *        payloadWithURL:ownershipToken: must be used to create the HMAccessorySetupPayload.
 */
@property (nonatomic, assign, readonly) BOOL requiresSetupPayloadURL;

/*!
 * @brief Indication if the ownership token needs to be updated for this request.
 */
@property (nonatomic, assign, readonly) BOOL requiresOwnershipToken API_DEPRECATED("No longer supported", ios(13.0, 13.0));

/*!
 * @brief Creates an accessory setup payload with ownership token
 *
 * @param ownershipToken The token proving ownership of the accessory being added to the home.
 *
 * @return Returns an accessory setup payload object if successful or nil on error.
 *
 * @discussion This method may fail if this request requires a setup payload URL.
 */
- (nullable HMAccessorySetupPayload *)payloadWithOwnershipToken:(HMAccessoryOwnershipToken *)ownershipToken NS_SWIFT_NAME(makePayload(ownershipToken:));

/*!
 * @brief Creates an accessory setup payload with URL and ownership token
 *
 * @param setupPayloadURL The HomeKit setup payload for the accessory being added to the home.
 *
 * @param ownershipToken The token proving ownership of the accessory being added to the home.
 *
 * @return Returns an accessory setup payload object if successful or nil on error.
 *
 * @discussion This method may fail if the setup payload URL is not a valid payload URL.
 */
- (nullable HMAccessorySetupPayload *)payloadWithURL:(NSURL *)setupPayloadURL ownershipToken:(HMAccessoryOwnershipToken *)ownershipToken NS_SWIFT_NAME(makePayload(url:ownershipToken:));

@end

NS_ASSUME_NONNULL_END

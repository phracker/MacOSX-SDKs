//
//  HMAccessorySetupRequest.h
//  HomeKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class HMAccessorySetupPayload;

HM_EXTERN API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(macos, macCatalyst)
@interface HMAccessorySetupRequest : NSObject <NSCopying>

/*!
 *  @abstract   The payload to use for accessory setup
 *  @note       When this is non-nil, the following entitlement is required:
 *                  com.apple.developer.homekit.allow-setup-payload
 */
@property (nullable, copy) HMAccessorySetupPayload *payload;

/*!
 *  @abstract   The -[HMHome uniqueIdentifier] that corresponds to the HMHome that the accessory should be
 *              added to when being set up. If nil, then the user will be prompted to choose a home
 */
@property (nullable, copy) NSUUID *homeUniqueIdentifier;

/*!
 *  @abstract   The -[HMRoom uniqueIdentifier] that corresponds to the existing HMRoom that should be
 *              suggested when the user is prompted to choose a room to add the accessory to. If nil, then any
 *              room may be suggested
 *  @note       This value will be ignored if homeUniqueIdentifier is nil
 */
@property (nullable, copy) NSUUID *suggestedRoomUniqueIdentifier;

/*!
 *  @abstract   The name that will be suggested when the user is prompted to name the accessory being set up.
 *              If nil, then the suggested name will be taken from the accessory itself
 *  @note       If an accessory bridge is being set up, then this value only applies to the accessory bridge
 *              and not any accessories behind the bridge
 */
@property (nullable, copy) NSString *suggestedAccessoryName;

@end

NS_ASSUME_NONNULL_END

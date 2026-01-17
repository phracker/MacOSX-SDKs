//
//  HMAccessorySetupPayload.h
//  HomeKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

HM_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos, macCatalyst)
@interface HMAccessoryOwnershipToken : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @brief Creates a new accessory ownership token to add an accessory to the home.
 *
 * @param data Data to be sent to prove ownership of this accessory.
 *
 * @discussion This initializer may return nil if the data provided is not a valid ownership token
 *             (e.g. if it's too short or determined to be insufficient for some other reason).
 *
 * @return Returns an ownership token object.
 */
- (nullable instancetype)initWithData:(NSData *)data;

@end

HM_EXTERN API_AVAILABLE(ios(11.3)) API_UNAVAILABLE(macos, watchos, tvos, macCatalyst)
@interface HMAccessorySetupPayload : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 * @brief Creates a new accessory setup payload to add an accessory to the home.
 *
 * @param setupPayloadURL The HomeKit setup payload for the accessory being added to the home.
 *
 * @return Returns an accessory setup payload object if successful or nil on error.
 */
- (nullable instancetype)initWithURL:(nullable NSURL *)setupPayloadURL;

/*!
 * @brief Creates a new accessory setup payload to add an accessory to the home.
 *
 * @param setupPayloadURL The HomeKit setup payload URL for the accessory being added to the home.`
 *
 * @param ownershipToken The token proving ownership of the accessory being added to the home.
 *
 * @return Returns an accessory setup payload object if successful or nil on error.
 */
- (nullable instancetype)initWithURL:(NSURL *)setupPayloadURL ownershipToken:(nullable HMAccessoryOwnershipToken *)ownershipToken API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(macos, watchos, tvos) NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

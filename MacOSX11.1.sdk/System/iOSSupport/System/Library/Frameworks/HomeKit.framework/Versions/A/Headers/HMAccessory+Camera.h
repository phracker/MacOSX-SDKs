//
//  HMAccessory+Camera.h
//  HomeKit
//
//  Copyright © 2015-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMAccessory.h>

@class HMCameraProfile;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract Category implementing methods related to camera profile.
 */
@interface HMAccessory(Camera)

/*!
 * @brief Returns array of camera profiles implemented by the accessory.
 *
 * @discussion An accessory can contain one or more cameras. Each camera is represented as a 
 *             an HMCameraProfile object. If the accessory does not contain a camera, this property
 *             will be nil.
 */
@property(readonly, copy, nonatomic, nullable) NSArray<HMCameraProfile *> *cameraProfiles API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos);

@end

NS_ASSUME_NONNULL_END

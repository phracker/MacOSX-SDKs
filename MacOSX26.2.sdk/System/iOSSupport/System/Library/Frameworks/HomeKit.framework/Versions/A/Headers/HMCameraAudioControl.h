//
//  HMCameraAudioControl.h
//  HomeKit
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <HomeKit/HMCameraControl.h>
#import <HomeKit/HMDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class HMCharacteristic;

HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMCameraAudioControl : HMCameraControl

- (instancetype)init NS_UNAVAILABLE;

/*!
 * Characteristic corresponding to mute setting on the camera.
 */
@property (nullable, nonatomic, readonly, strong) HMCharacteristic *mute;

/*!
 * Characteristic corresponding to volume setting on the camera.
 */
@property (nullable, nonatomic, readonly, strong) HMCharacteristic *volume;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

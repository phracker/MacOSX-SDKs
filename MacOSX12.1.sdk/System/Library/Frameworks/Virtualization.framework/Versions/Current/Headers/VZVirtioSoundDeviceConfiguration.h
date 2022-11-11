//
//  VZVirtioSoundDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2020-2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZAudioDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class VZVirtioSoundDeviceStreamConfiguration;

/*!
 @abstract Virtio Sound Device Configuration.
 @discussion The device exposes a source or destination of sound.
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZVirtioSoundDeviceConfiguration : VZAudioDeviceConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
 @abstract List of audio streams exposed by this device. Empty by default.
*/
@property (copy) NSArray<VZVirtioSoundDeviceStreamConfiguration *> *streams;

@end

NS_ASSUME_NONNULL_END

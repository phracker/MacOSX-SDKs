//
//  VZVirtioSoundDeviceStreamConfiguration.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZAudioDeviceConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Virtio Sound Device Stream Configuration.
 @discussion A PCM stream of audio data.
    VZVirtioSoundDeviceStreamConfiguration should not be instantiated directly.
    One of its subclasses like VZVirtioSoundDeviceInputStreamConfiguration or VZVirtioSoundDeviceOutputStreamConfiguration should be used instead.
 
 @see VZVirtioSoundDeviceInputStreamConfiguration
 @see VZVirtioSoundDeviceOutputStreamConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZVirtioSoundDeviceStreamConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

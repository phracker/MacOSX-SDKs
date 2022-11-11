//
//  VZAudioDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2020-2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for an audio device configuration.
 @discussion
    VZAudioDeviceConfiguration should not be instantiated directly.
    The subclass VZVirtioSoundDeviceConfiguration should be used instead.

 @see VZVirtioSoundDeviceConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZAudioDeviceConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

//
//  VZHostAudioInputStreamSource.h
//  Virtualization
//
//  Copyright © 2021-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZAudioInputStreamSource.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Host audio input stream source provides audio from the host system's default input device.
 @discussion
    Host input data comes from the same device that AudioQueueNewInput uses.

 @see VZVirtioSoundDeviceInputStreamConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZHostAudioInputStreamSource : VZAudioInputStreamSource

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

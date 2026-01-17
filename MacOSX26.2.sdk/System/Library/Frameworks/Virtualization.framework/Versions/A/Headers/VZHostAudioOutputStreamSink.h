//
//  VZHostAudioOutputStreamSink.h
//  Virtualization
//
//  Copyright © 2021-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZAudioOutputStreamSink.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Host audio output stream sink plays audio to the host system's default output device.
 @discussion
    Host output data goes to the same device that AudioQueueNewOutput uses.

 @see VZVirtioSoundDeviceOutputStreamConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZHostAudioOutputStreamSink : VZAudioOutputStreamSink

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

//
//  VZVirtioSoundDeviceOutputStreamConfiguration.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZVirtioSoundDeviceStreamConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class VZAudioOutputStreamSink;

/*!
 @abstract Virtio Sound Device Output Stream Configuration.
 @discussion A PCM stream of output audio data, such as to a speaker.
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZVirtioSoundDeviceOutputStreamConfiguration : VZVirtioSoundDeviceStreamConfiguration

/*!
 @abstract Initialize the input stream configuration.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Audio Stream Sink. Defines how the audio data produced by the guest is handled on the host. The default is nil.
 @discussion Not specifying a Sink will have a default handler that swallows the audio.
 @see VZAudioOutputStreamSink
*/
@property (nullable, strong) VZAudioOutputStreamSink *sink;

@end

NS_ASSUME_NONNULL_END

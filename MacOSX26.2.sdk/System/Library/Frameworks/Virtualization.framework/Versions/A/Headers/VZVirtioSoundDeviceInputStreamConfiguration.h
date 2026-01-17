//
//  VZVirtioSoundDeviceInputStreamConfiguration.h
//  Virtualization
//
//  Copyright © 2021-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZVirtioSoundDeviceStreamConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class VZAudioInputStreamSource;

/*!
 @abstract Virtio Sound Device Input Stream Configuration.
 @discussion A PCM stream of input audio data, such as from a microphone.
 */
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZVirtioSoundDeviceInputStreamConfiguration : VZVirtioSoundDeviceStreamConfiguration

/*!
 @abstract Initialize the input stream configuration.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
 @abstract Audio Stream Source. Defines how the audio data is supplied on the host for the guest. The default is nil.
 @discussion Not specifying a Source will have a default handler that produces audio silence.
 @see VZAudioInputStreamSource
*/
@property (nullable, strong) VZAudioInputStreamSource *source;

@end

NS_ASSUME_NONNULL_END

//
//  AVAudioSourceNode.h
//  AVFAudio
//
//  Copyright © 2018 Apple. All rights reserved.
//

#if __OBJC2__

#import <AVFAudio/AVAudioNode.h>
#import <AVFAudio/AVAudioMixing.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAudioFormat;

/*! @typedef AVAudioSourceNodeRenderBlock
    @abstract Block to supply audio data to AVAudioSourceNode
    @param isSilence
        The client may use this flag to indicate that the buffer it vends contains only silence.
        The receiver of the buffer can then use the flag as a hint as to whether the buffer needs
        to be processed or not.
        Note that because the flag is only a hint, when setting the silence flag, the originator of
        a buffer must also ensure that it contains silence (zeroes).
    @param timestamp
        The HAL time at which the audio data will be rendered. If there is a sample rate conversion
        or time compression/expansion downstream, the sample time will not be valid.
    @param frameCount
        The number of sample frames of audio data requested.
    @param outputData
        The output data.

        The caller must supply valid buffers in outputData's mBuffers' mData and mDataByteSize.
        mDataByteSize must be consistent with frameCount. This block may provide output in those
        specified buffers, or it may replace the mData pointers with pointers to memory which it
        owns and guarantees will remain valid until the next render cycle.
    @return
        An OSStatus result code. If an error is returned, the audio data should be assumed to be
        invalid.
 */
typedef OSStatus (^AVAudioSourceNodeRenderBlock)(BOOL *isSilence, const AudioTimeStamp *timestamp, AVAudioFrameCount frameCount, AudioBufferList *outputData) API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0)) ;

/*!
    @class AVAudioSourceNode
    @abstract AVAudioSourceNode wraps a client provided block to supply audio.
    @discussion
        With AVAudioSourceNode the client can supply audio data for rendering through an
        AVAudioSourceNodeRenderBlock block.
        This is similar to setting the input callback on an Audio Unit with the
        kAudioUnitProperty_SetRenderCallback property.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0)) 
@interface AVAudioSourceNode : AVAudioNode <AVAudioMixing>

- (instancetype)init NS_UNAVAILABLE;

/*! @method initWithRenderBlock:
    @abstract Create a node with a render block.
    @param block
        The block to supply audio data to the output.
    @discussion
        The block can be called on realtime or non-realtime threads depending on the engine’s
        operating mode and it is the client's responsibility to handle it in a thread-safe manner.

        The audio format for the output bus will be set from the connection format when connecting
        to another node.

        The audio format for the block will be set to the node's output format. If node is
        reconnected with a different output format, the audio format for the block will also change.
 */
- (instancetype)initWithRenderBlock:(AVAudioSourceNodeRenderBlock)block NS_DESIGNATED_INITIALIZER;

/*! @method initWithFormat:renderBlock:
    @abstract Create a node with a render block.
    @param format
        The format of the PCM audio data that will be supplied by the block.
    @param block
        The block to supply audio data to the output.
    @discussion
        The block can be called on realtime or non-realtime threads depending on the engine’s
        operating mode and it is the client's responsibility to handle it in a thread-safe manner.

        The audio format for the output bus will be set from the connection format when connecting
        to another node.

        AVAudioSourceNode supports different audio formats for the block and output, but only
        Linear PCM conversions are supported (sample rate, bit depth, interleaving).
 */
- (instancetype)initWithFormat:(AVAudioFormat*)format renderBlock:(AVAudioSourceNodeRenderBlock)block NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

#endif

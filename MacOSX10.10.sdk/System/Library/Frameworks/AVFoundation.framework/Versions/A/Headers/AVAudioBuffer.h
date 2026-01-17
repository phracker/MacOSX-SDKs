/*
	File:		AVAudioBuffer.h
	Framework:	AVFoundation
	
	Copyright (c) 2014 Apple Inc. All Rights Reserved.
*/

#import <AVFoundation/AVAudioTypes.h>

@class AVAudioFormat;

/*!
	@class AVAudioBuffer
	@abstract A buffer of audio data, with a format.
	@discussion
		AVAudioBuffer represents a buffer of audio data and its format.
*/

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioBuffer : NSObject <NSCopying, NSMutableCopying> {
@protected
	void *_impl;
}

/*!
	@property format
	@abstract The format of the audio in the buffer.
*/
@property (nonatomic, readonly) AVAudioFormat *format;

/*!	@property audioBufferList
	@abstract The buffer's underlying AudioBufferList.
	@discussion
		For compatibility with lower-level CoreAudio and AudioToolbox API's, this method accesses
		the buffer implementation's internal AudioBufferList. The buffer list structure must
		not be modified, though you may modify buffer contents.
		
		The mDataByteSize fields of this AudioBufferList express the buffer's current frameLength.
*/
@property (nonatomic, readonly) const AudioBufferList *audioBufferList;

/*!	@property mutableAudioBufferList
	@abstract A mutable version of the buffer's underlying AudioBufferList.
	@discussion
		Some lower-level CoreAudio and AudioToolbox API's require a mutable AudioBufferList,
		for example, AudioConverterConvertComplexBuffer.
		
		The mDataByteSize fields of this AudioBufferList express the buffer's current frameCapacity.
		If they are altered, you should modify the buffer's frameLength to match.
*/
@property (nonatomic, readonly) AudioBufferList *mutableAudioBufferList;

@end

// -------------------------------------------------------------------------------------------------

/*!
	@class AVAudioPCMBuffer
	@abstract A subclass of AVAudioBuffer for use with PCM audio formats.
	@discussion
		AVAudioPCMBuffer provides a number of methods useful for manipulating buffers of
		audio in PCM format.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioPCMBuffer : AVAudioBuffer

/*!	@method initWithPCMFormat:frameCapacity:
	@abstract Initialize a buffer that is to contain PCM audio samples.
	@param format
		The format of the PCM audio to be contained in the buffer.
	@param frameCapacity
		The capacity of the buffer in PCM sample frames.
	@discussion
		nil is returned if the format is not PCM.
*/
- (instancetype)initWithPCMFormat:(AVAudioFormat *)format frameCapacity:(AVAudioFrameCount)frameCapacity;

/*! @property frameCapacity
	@abstract
		The buffer's capacity, in audio sample frames.
*/
@property (nonatomic, readonly) AVAudioFrameCount frameCapacity;

/*!	@property frameLength
	@abstract The current number of valid sample frames in the buffer.
	@discussion
		You may modify the length of the buffer as part of an operation that modifies its contents.
		The length must be less than or equal to the frameCapacity. Modifying frameLength will update
		the mDataByteSize in each of the underlying AudioBufferList's AudioBuffer's correspondingly,
		and vice versa. Note that in the case of deinterleaved formats, mDataByteSize will refers
		the size of one channel's worth of audio samples.
*/
@property (nonatomic) AVAudioFrameCount frameLength;

/*!	@property stride
	@abstract The buffer's number of interleaved channels.
	@discussion
		Useful in conjunction with floatChannelData etc.
*/
@property (nonatomic, readonly) NSUInteger stride;

/*! @property floatChannelData
	@abstract Access the buffer's float audio samples.
	@discussion
		floatChannelData returns pointers to the buffer's audio samples if the buffer's format is
		32-bit float, or nil if it is another format.
	
		The returned pointer is to format.channelCount pointers to float. Each of these pointers
		is to "frameLength" valid samples, which are spaced by "stride" samples.
		
		If format.interleaved is false (as with the standard deinterleaved float format), then 
		the pointers will be to separate chunks of memory. "stride" is 1.
		
		If format.interleaved is true, then the pointers will refer into the same chunk of interleaved
		samples, each offset by 1 frame. "stride" is the number of interleaved channels.
*/
@property (nonatomic, readonly) float * const *floatChannelData;

/*!	@property int16ChannelData
	@abstract Access the buffer's int16_t audio samples.
	@discussion
		int16ChannelData returns the buffer's audio samples if the buffer's format has 2-byte
		integer samples, or nil if it is another format.
		
		See the discussion of floatChannelData.
*/
@property (nonatomic, readonly) int16_t * const *int16ChannelData;

/*!	@property int32ChannelData
	@abstract Access the buffer's int32_t audio samples.
	@discussion
		int32ChannelData returns the buffer's audio samples if the buffer's format has 4-byte
		integer samples, or nil if it is another format.
		
		See the discussion of floatChannelData.
*/
@property (nonatomic, readonly) int32_t * const *int32ChannelData;

@end

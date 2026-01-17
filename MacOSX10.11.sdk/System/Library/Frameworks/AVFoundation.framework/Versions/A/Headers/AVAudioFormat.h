/*
	File:		AVAudioFormat.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFoundation/AVAudioTypes.h>
#import <AVFoundation/AVAudioChannelLayout.h>
#import <CoreMedia/CMFormatDescription.h>

NS_ASSUME_NONNULL_BEGIN

/*!	
	@enum		AVAudioCommonFormat
	@constant	AVAudioOtherFormat
					A format other than one of the common ones below.
	@constant	AVAudioPCMFormatFloat32
					Native-endian floats (this is the standard format).
	@constant	AVAudioPCMFormatFloat64
					Native-endian doubles.
	@constant	AVAudioPCMFormatInt16
					Signed 16-bit native-endian integers.
	@constant	AVAudioPCMFormatInt32
					Signed 32-bit native-endian integers.
*/
typedef NS_ENUM(NSUInteger, AVAudioCommonFormat) {
	AVAudioOtherFormat = 0,
	AVAudioPCMFormatFloat32 = 1,
	AVAudioPCMFormatFloat64 = 2,
	AVAudioPCMFormatInt16 = 3,
	AVAudioPCMFormatInt32 = 4
} NS_ENUM_AVAILABLE(10_10, 8_0);


/*! @class AVAudioFormat
	@abstract A representation of an audio format.
	@discussion
		AVAudioFormat wraps a Core Audio AudioStreamBasicDescription struct, with convenience
		initializers and accessors for common formats, including Core Audio's standard deinterleaved
		32-bit floating point.
	
		Instances of this class are immutable.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioFormat : NSObject <NSSecureCoding> {
@private
	AudioStreamBasicDescription _asbd;
	AVAudioChannelLayout *_layout;
	AVAudioCommonFormat _commonFormat;
	void * _reserved;
}


/*! @method initWithStreamDescription:
	@abstract Initialize from an AudioStreamBasicDescription.
	@param asbd
		the AudioStreamBasicDescription
	@discussion
		If the format specifies more than 2 channels, this method fails (returns nil).
*/
- (instancetype)initWithStreamDescription:(const AudioStreamBasicDescription *)asbd;

/*! @method initWithStreamDescription:channelLayout:
	@abstract Initialize from an AudioStreamBasicDescription and optional channel layout.
	@param asbd
		the AudioStreamBasicDescription
	@param layout
		the channel layout. Can be nil only if asbd specifies 1 or 2 channels.
	@discussion
		If the format specifies more than 2 channels, this method fails (returns nil) unless layout
		is non-nil.
*/
- (instancetype)initWithStreamDescription:(const AudioStreamBasicDescription *)asbd channelLayout:(AVAudioChannelLayout * __nullable)layout;

/*! @method initStandardFormatWithSampleRate:channels:
	@abstract Initialize to deinterleaved float with the specified sample rate and channel count.
	@param sampleRate
		the sample rate
	@param channels
		the channel count
	@discussion
		If the format specifies more than 2 channels, this method fails (returns nil).
*/
- (instancetype)initStandardFormatWithSampleRate:(double)sampleRate channels:(AVAudioChannelCount)channels;

/*! @method initStandardFormatWithSampleRate:channelLayout:
	@abstract Initialize to deinterleaved float with the specified sample rate and channel layout.
	@param sampleRate
		the sample rate
	@param layout
		the channel layout. must not be nil.
*/
- (instancetype)initStandardFormatWithSampleRate:(double)sampleRate channelLayout:(AVAudioChannelLayout *)layout;

/*! @method initWithCommonFormat:sampleRate:channels:interleaved:
	@abstract Initialize to float with the specified sample rate, channel count and interleavedness.
	@param format
		the common format type
	@param sampleRate
		the sample rate
	@param channels
		the channel count
	@param interleaved
		true if interleaved
	@discussion
		If the format specifies more than 2 channels, this method fails (returns nil).
*/
- (instancetype)initWithCommonFormat:(AVAudioCommonFormat)format sampleRate:(double)sampleRate channels:(AVAudioChannelCount)channels interleaved:(BOOL)interleaved;

/*! @method initWithCommonFormat:sampleRate:interleaved:channelLayout:
	@abstract Initialize to float with the specified sample rate, channel layout and interleavedness.
	@param format
		the common format type
	@param sampleRate
		the sample rate
	@param interleaved
		true if interleaved
	@param layout
		the channel layout. must not be nil.
*/
- (instancetype)initWithCommonFormat:(AVAudioCommonFormat)format sampleRate:(double)sampleRate interleaved:(BOOL)interleaved channelLayout:(AVAudioChannelLayout *)layout;

/*! @method initWithSettings:
	@abstract Initialize using a settings dictionary.
	@discussion
		See AVAudioSettings.h. Note that many settings dictionary elements pertain to encoder
		settings, not the basic format, and will be ignored.
*/
- (instancetype)initWithSettings:(NSDictionary<NSString *, id> *)settings;

/*!
 	@method initWithCMAudioFormatDescription:
 	@abstract initialize from a CMAudioFormatDescriptionRef.
 	@param formatDescription
 		the CMAudioFormatDescriptionRef.
 	@discussion
 		If formatDescription is invalid, this method fails (returns nil).
 */
- (instancetype)initWithCMAudioFormatDescription:(CMAudioFormatDescriptionRef)formatDescription NS_AVAILABLE(10_11, 9_0);


/*!	@method isEqual:
	@abstract Determine whether another format is functionally equivalent.
	@param object
		the format to compare against
	@discussion
		For PCM, interleavedness is ignored for mono. Differences in the AudioStreamBasicDescription
		alignment and packedness are ignored when they are not significant (e.g. with 1 channel, 2
		bytes per frame and 16 bits per channel, neither alignment, the format is implicitly packed
		and can be interpreted as either high- or low-aligned.)
		For AVAudioChannelLayout, a layout with standard mono/stereo tag is considered to be 
		equivalent to a nil layout. Otherwise, the layouts are compared for equality.
*/
- (BOOL)isEqual:(id)object;

/*!	@property standard
	@abstract Describes whether the format is deinterleaved native-endian float.
*/
@property (nonatomic, readonly, getter=isStandard) BOOL standard;

/*!	@property commonFormat
	@abstract An `AVAudioCommonFormat` identifying the format
*/
@property (nonatomic, readonly) AVAudioCommonFormat commonFormat;

/*! @property channelCount
	@abstract The number of channels of audio data.
*/
@property (nonatomic, readonly) AVAudioChannelCount channelCount;

/*! @property sampleRate
	@abstract A sampling rate in Hertz.
*/
@property (nonatomic, readonly) double sampleRate;

/*!	@property interleaved
	@abstract Describes whether the samples are interleaved.
	@discussion
		For non-PCM formats, the value is undefined.
*/
@property (nonatomic, readonly, getter=isInterleaved) BOOL interleaved;

/*!	@property streamDescription
	@abstract Returns the AudioStreamBasicDescription, for use with lower-level audio API's.
*/
@property (nonatomic, readonly) const AudioStreamBasicDescription *streamDescription;

/*!	@property channelLayout
	@abstract The underlying AVAudioChannelLayout, if any.
	@discussion
		Only formats with more than 2 channels are required to have channel layouts.
*/
@property (nonatomic, readonly, nullable) const AVAudioChannelLayout *channelLayout;

/*!	@property settings
	@abstract Returns the format represented as a dictionary with keys from AVAudioSettings.h.
*/
@property (nonatomic, readonly) NSDictionary<NSString *, id> *settings;

/*!
	 @property formatDescription
	 @abstract Converts to a CMAudioFormatDescriptionRef, for use with Core Media API's.
 */
@property (nonatomic, readonly) CMAudioFormatDescriptionRef formatDescription NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

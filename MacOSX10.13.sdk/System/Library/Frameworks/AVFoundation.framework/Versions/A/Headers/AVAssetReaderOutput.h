/*
    File:  AVAssetReaderOutput.h

	Framework:  AVFoundation
 
    Copyright 2010-2017 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVVideoComposition.h>
#import <AVFoundation/AVAudioProcessingSettings.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMSampleBuffer.h>

@class AVAssetTrack;
@class AVAudioMixInputParameters;
@class AVAudioMix;
@class AVVideoComposition;
@class AVAssetReaderOutputInternal;

NS_ASSUME_NONNULL_BEGIN

/*!
 @class AVAssetReaderOutput
 @abstract
	AVAssetReaderOutput is an abstract class that defines an interface for reading a single collection of samples of a common media type from an AVAssetReader.
 
 @discussion
	Clients can read the media data of an asset by adding one or more concrete instances of AVAssetReaderOutput to an AVAssetReader using the -[AVAssetReader addOutput:] method.
	
	IMPORTANT PERFORMANCE NOTE: Make sure to set the alwaysCopiesSampleData property to NO if you do not need to modify the sample data in-place, to avoid unnecessary and inefficient copying.
 */
NS_CLASS_AVAILABLE(10_7, 4_1)
@interface AVAssetReaderOutput : NSObject
{
@private
	AVAssetReaderOutputInternal	*_internal;
}

/*!
 @property mediaType
 @abstract
	The media type of the samples that can be read from the receiver.

 @discussion
	The value of this property is one of the media type strings defined in AVMediaFormat.h.
 */
@property (nonatomic, readonly) NSString *mediaType;

/*!
 @property alwaysCopiesSampleData
 @abstract
	Indicates whether or not the data in buffers gets copied before being vended to the client.
 
 @discussion
	When the value of this property is YES, the AVAssetReaderOutput will always vend a buffer with copied data to the client.  Data in such buffers can be freely modified by the client. When the value of this property is NO, the buffers vended to the client may not be copied.  Such buffers may still be referenced by other entities. The result of modifying a buffer whose data hasn't been copied is undefined.  Requesting buffers whose data hasn't been copied when possible can lead to performance improvements.
 
	The default value is YES.
 */
@property (nonatomic) BOOL alwaysCopiesSampleData NS_AVAILABLE(10_8, 5_0);

/*!
 @method copyNextSampleBuffer
 @abstract
	Copies the next sample buffer for the output synchronously.

 @result
	A CMSampleBuffer object referencing the output sample buffer.

 @discussion
	The client is responsible for calling CFRelease on the returned CMSampleBuffer object when finished with it. This method will return NULL if there are no more sample buffers available for the receiver within the time range specified by its AVAssetReader's timeRange property, or if there is an error that prevents the AVAssetReader from reading more media data. When this method returns NULL, clients should check the value of the associated AVAssetReader's status property to determine why no more samples could be read.
 */
- (nullable CMSampleBufferRef)copyNextSampleBuffer CF_RETURNS_RETAINED;

@end


@interface AVAssetReaderOutput (AVAssetReaderOutputRandomAccess)

/*!
 @property supportsRandomAccess
 @abstract
	Indicates whether the asset reader output supports reconfiguration of the time ranges to read.
 
 @discussion
	When the value of this property is YES, the time ranges read by the asset reader output can be reconfigured during reading using the -resetForReadingTimeRanges: method.  This also prevents the attached AVAssetReader from progressing to AVAssetReaderStatusCompleted until -markConfigurationAsFinal has been invoked.
 
	The default value is NO, which means that the asset reader output may not be reconfigured once reading has begin.  When the value of this property is NO, AVAssetReader may be able to read media data more efficiently, particularly when multiple asset reader outputs are attached.
 
	This property may not be set after -startReading has been called on the attached asset reader.
 */
@property (nonatomic) BOOL supportsRandomAccess NS_AVAILABLE(10_10, 8_0);

/*!
 @method resetForReadingTimeRanges:
 @abstract
	Starts reading over with a new set of time ranges.
 
 @param timeRanges
	An NSArray of NSValue objects, each representing a single CMTimeRange structure
 
 @discussion
	This method may only be used if supportsRandomAccess has been set to YES and may not be called after -markConfigurationAsFinal has been invoked.
 
	This method is often used in conjunction with AVAssetWriter multi-pass (see AVAssetWriterInput category AVAssetWriterInputMultiPass).  In this usage, the caller will invoke -copyNextSampleBuffer until that method returns NULL and then ask the AVAssetWriterInput for a set of time ranges from which it thinks media data should be re-encoded.  These time ranges are then given to this method to set up the asset reader output for the next pass.
 
	The time ranges set here override the time range set on AVAssetReader.timeRange.  Just as with that property, for each time range in the array the intersection of that time range and CMTimeRangeMake(kCMTimeZero, asset.duration) will take effect.  If the start times of each time range in the array are not strictly increasing or if two or more time ranges in the array overlap, an NSInvalidArgumentException will be raised.  It is an error to include a time range with a non-numeric start time or duration (see CMTIME_IS_NUMERIC), unless the duration is kCMTimePositiveInfinity.
 
	If this method is invoked after the status of the attached AVAssetReader has become AVAssetReaderStatusFailed or AVAssetReaderStatusCancelled, no change in status will occur and the result of the next call to -copyNextSampleBuffer will be NULL.
 
	If this method is invoked before all media data has been read (i.e. -copyNextSampleBuffer has not yet returned NULL), an exception will be thrown.  This method may not be called before -startReading has been invoked on the attached asset reader.
 */
- (void)resetForReadingTimeRanges:(NSArray<NSValue *> *)timeRanges NS_AVAILABLE(10_10, 8_0);

/*!
 @method markConfigurationAsFinal
 @abstract
	Informs the receiver that no more reconfiguration of time ranges is necessary and allows the attached AVAssetReader to advance to AVAssetReaderStatusCompleted.
 
 @discussion
	When the value of supportsRandomAccess is YES, the attached asset reader will not advance to AVAssetReaderStatusCompleted until this method is called.
 
	When the destination of media data vended by the receiver is an AVAssetWriterInput configured for multi-pass encoding, a convenient time to invoke this method is after the asset writer input indicates that no more passes will be performed.
 
	Once this method has been called, further invocations of -resetForReadingTimeRanges: are disallowed.
 */
- (void)markConfigurationAsFinal NS_AVAILABLE(10_10, 8_0);

@end

@class AVAssetReaderTrackOutputInternal;

/*!
 @class AVAssetReaderTrackOutput
 @abstract
	AVAssetReaderTrackOutput is a concrete subclass of AVAssetReaderOutput that defines an interface for reading media data from a single AVAssetTrack of an AVAssetReader's AVAsset.
 
 @discussion
	Clients can read the media data of an asset track by adding an instance of AVAssetReaderTrackOutput to an AVAssetReader using the -[AVAssetReader addOutput:] method. The track's media samples can either be read in the format in which they are stored in the asset, or they can be converted to a different format.
 */
NS_CLASS_AVAILABLE(10_7, 4_1)
@interface AVAssetReaderTrackOutput : AVAssetReaderOutput
{
@private
	AVAssetReaderTrackOutputInternal	*_trackOutputInternal;
}
AV_INIT_UNAVAILABLE

/*!
 @method assetReaderTrackOutputWithTrack:outputSettings:
 @abstract
	Returns an instance of AVAssetReaderTrackOutput for reading from the specified track and supplying media data according to the specified output settings.

 @param track
	The AVAssetTrack from which the resulting AVAssetReaderTrackOutput should read sample buffers.
 @param outputSettings
	An NSDictionary of output settings to be used for sample output.  See AVAudioSettings.h for available output settings for audio tracks or AVVideoSettings.h for available output settings for video tracks and also for more information about how to construct an output settings dictionary.
 @result
	An instance of AVAssetReaderTrackOutput.

 @discussion
	The track must be one of the tracks contained by the target AVAssetReader's asset.
	
	A value of nil for outputSettings configures the output to vend samples in their original format as stored by the specified track.  Initialization will fail if the output settings cannot be used with the specified track.
	
	AVAssetReaderTrackOutput can only produce uncompressed output.  For audio output settings, this means that AVFormatIDKey must be kAudioFormatLinearPCM.  For video output settings, this means that the dictionary must follow the rules for uncompressed video output, as laid out in AVVideoSettings.h.  AVAssetReaderTrackOutput does not support the AVAudioSettings.h key AVSampleRateConverterAudioQualityKey or the following AVVideoSettings.h keys:
 
		AVVideoCleanApertureKey
		AVVideoPixelAspectRatioKey
		AVVideoScalingModeKey
	
	When constructing video output settings the choice of pixel format will affect the performance and quality of the decompression. For optimal performance when decompressing video the requested pixel format should be one that the decoder supports natively to avoid unnecessary conversions. Below are some recommendations:

	For H.264 use kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange, or kCVPixelFormatType_420YpCbCr8BiPlanarFullRange if the video is known to be full range.  For JPEG on iOS, use kCVPixelFormatType_420YpCbCr8BiPlanarFullRange.

	For other codecs on OSX, kCVPixelFormatType_422YpCbCr8 is the preferred pixel format for video and is generally the most performant when decoding. If you need to work in the RGB domain then kCVPixelFormatType_32BGRA is recommended on iOS and kCVPixelFormatType_32ARGB is recommended on OSX.
 
	ProRes encoded media can contain up to 12bits/ch. If your source is ProRes encoded and you wish to preserve more than 8bits/ch during decompression then use one of the following pixel formats: kCVPixelFormatType_4444AYpCbCr16, kCVPixelFormatType_422YpCbCr16, kCVPixelFormatType_422YpCbCr10, or kCVPixelFormatType_64ARGB.  AVAssetReader does not support scaling with any of these high bit depth pixel formats. If you use them then do not specify kCVPixelBufferWidthKey or kCVPixelBufferHeightKey in your outputSettings dictionary. If you plan to append these sample buffers to an AVAssetWriterInput then note that only the ProRes encoders support these pixel formats.

	ProRes 4444 encoded media can contain a mathematically lossless alpha channel. To preserve the alpha channel during decompression use a pixel format with an alpha component such as kCVPixelFormatType_4444AYpCbCr16 or kCVPixelFormatType_64ARGB. To test whether your source contains an alpha channel check that the track's format description has kCMFormatDescriptionExtension_Depth and that its value is 32.
 */
+ (instancetype)assetReaderTrackOutputWithTrack:(AVAssetTrack *)track outputSettings:(nullable NSDictionary<NSString *, id> *)outputSettings;

/*!
 @method initWithTrack:outputSettings:
 @abstract
	Returns an instance of AVAssetReaderTrackOutput for reading from the specified track and supplying media data according to the specified output settings.

 @param track
	The AVAssetTrack from which the resulting AVAssetReaderTrackOutput should read sample buffers.
 @param outputSettings
	An NSDictionary of output settings to be used for sample output.  See AVAudioSettings.h for available output settings for audio tracks or AVVideoSettings.h for available output settings for video tracks and also for more information about how to construct an output settings dictionary.
 @result
	An instance of AVAssetReaderTrackOutput.

 @discussion
	The track must be one of the tracks contained by the target AVAssetReader's asset.
	
	A value of nil for outputSettings configures the output to vend samples in their original format as stored by the specified track.  Initialization will fail if the output settings cannot be used with the specified track.
	
	AVAssetReaderTrackOutput can only produce uncompressed output.  For audio output settings, this means that AVFormatIDKey must be kAudioFormatLinearPCM.  For video output settings, this means that the dictionary must follow the rules for uncompressed video output, as laid out in AVVideoSettings.h.  AVAssetReaderTrackOutput does not support the AVAudioSettings.h key AVSampleRateConverterAudioQualityKey or the following AVVideoSettings.h keys:
 
		AVVideoCleanApertureKey
		AVVideoPixelAspectRatioKey
		AVVideoScalingModeKey

	When constructing video output settings the choice of pixel format will affect the performance and quality of the decompression. For optimal performance when decompressing video the requested pixel format should be one that the decoder supports natively to avoid unnecessary conversions. Below are some recommendations:

	For H.264 use kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange, or kCVPixelFormatType_420YpCbCr8BiPlanarFullRange if the video is known to be full range.  For JPEG on iOS, use kCVPixelFormatType_420YpCbCr8BiPlanarFullRange.

	For other codecs on OSX, kCVPixelFormatType_422YpCbCr8 is the preferred pixel format for video and is generally the most performant when decoding. If you need to work in the RGB domain then kCVPixelFormatType_32BGRA is recommended on iOS and kCVPixelFormatType_32ARGB is recommended on OSX.
 
	ProRes encoded media can contain up to 12bits/ch. If your source is ProRes encoded and you wish to preserve more than 8bits/ch during decompression then use one of the following pixel formats: kCVPixelFormatType_4444AYpCbCr16, kCVPixelFormatType_422YpCbCr16, kCVPixelFormatType_422YpCbCr10, or kCVPixelFormatType_64ARGB.  AVAssetReader does not support scaling with any of these high bit depth pixel formats. If you use them then do not specify kCVPixelBufferWidthKey or kCVPixelBufferHeightKey in your outputSettings dictionary. If you plan to append these sample buffers to an AVAssetWriterInput then note that only the ProRes encoders support these pixel formats.

	ProRes 4444 encoded media can contain a mathematically lossless alpha channel. To preserve the alpha channel during decompression use a pixel format with an alpha component such as kCVPixelFormatType_4444AYpCbCr16 or kCVPixelFormatType_64ARGB.  To test whether your source contains an alpha channel check that the track's format description has kCMFormatDescriptionExtension_Depth and that its value is 32.
 */
- (instancetype)initWithTrack:(AVAssetTrack *)track outputSettings:(nullable NSDictionary<NSString *, id> *)outputSettings NS_DESIGNATED_INITIALIZER;

/*!
 @property track
 @abstract
	The track from which the receiver reads sample buffers.

 @discussion
	The value of this property is an AVAssetTrack owned by the target AVAssetReader's asset.
 */
@property (nonatomic, readonly) AVAssetTrack *track;

/*!
 @property outputSettings
 @abstract
	The output settings used by the receiver.

 @discussion
	The value of this property is an NSDictionary that contains values for keys as specified by either AVAudioSettings.h for audio tracks or AVVideoSettings.h for video tracks.  A value of nil indicates that the receiver will vend samples in their original format as stored in the target track.
 */ 
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *outputSettings;

/*!
 @property audioTimePitchAlgorithm
 @abstract
	Indicates the processing algorithm used to manage audio pitch for scaled audio edits.
 
 @discussion
	Constants for various time pitch algorithms, e.g. AVAudioTimePitchAlgorithmSpectral, are defined in AVAudioProcessingSettings.h.  An NSInvalidArgumentException will be raised if this property is set to a value other than the constants defined in that file.
 
	The default value is AVAudioTimePitchAlgorithmSpectral.
 */
@property (nonatomic, copy) AVAudioTimePitchAlgorithm audioTimePitchAlgorithm NS_AVAILABLE(10_9, 7_0);

@end


@class AVAssetReaderAudioMixOutputInternal;

/*!
 @class AVAssetReaderAudioMixOutput
 @abstract
	AVAssetReaderAudioMixOutput is a concrete subclass of AVAssetReaderOutput that defines an interface for reading audio samples that result from mixing the audio from one or more AVAssetTracks of an AVAssetReader's AVAsset.
 
 @discussion
	Clients can read the audio data mixed from one or more asset tracks by adding an instance of AVAssetReaderAudioMixOutput to an AVAssetReader using the -[AVAssetReader addOutput:] method.
 */
NS_CLASS_AVAILABLE(10_7, 4_1)
@interface AVAssetReaderAudioMixOutput : AVAssetReaderOutput
{
@private
	AVAssetReaderAudioMixOutputInternal	*_audioMixOutputInternal;
}
AV_INIT_UNAVAILABLE

/*!
 @method assetReaderAudioMixOutputWithAudioTracks:audioSettings:
 @abstract
	Returns an instance of AVAssetReaderAudioMixOutput for reading mixed audio from the specified audio tracks, with optional audio settings.

 @param tracks
	An NSArray of AVAssetTrack objects from which the created object should read sample buffers to be mixed.
 @param audioSettings
	An NSDictionary of audio settings to be used for audio output.
 @result
	An instance of AVAssetReaderAudioMixOutput.

 @discussion
	Each track must be one of the tracks owned by the target AVAssetReader's asset and must be of media type AVMediaTypeAudio.
	
	The audio settings dictionary must contain values for keys in AVAudioSettings.h (linear PCM only). A value of nil configures the output to return samples in a convenient uncompressed format, with sample rate and other properties determined according to the properties of the specified audio tracks. Initialization will fail if the audio settings cannot be used with the specified tracks.  AVSampleRateConverterAudioQualityKey is not supported.
 */
+ (instancetype)assetReaderAudioMixOutputWithAudioTracks:(NSArray<AVAssetTrack *> *)audioTracks audioSettings:(nullable NSDictionary<NSString *, id> *)audioSettings;

/*!
 @method initWithAudioTracks:audioSettings:
 @abstract
	Creates an instance of AVAssetReaderAudioMixOutput for reading mixed audio from the specified audio tracks, with optional audio settings.

 @param tracks
	An NSArray of AVAssetTrack objects from which the created object should read sample buffers to be mixed.
 @param audioSettings
	An NSDictionary of audio settings to be used for audio output.
 @result
	An instance of AVAssetReaderAudioMixOutput.

 @discussion
	Each track must be one of the tracks owned by the target AVAssetReader's asset and must be of media type AVMediaTypeAudio.
	
	The audio settings dictionary must contain values for keys in AVAudioSettings.h (linear PCM only). A value of nil configures the output to return samples in a convenient uncompressed format, with sample rate and other properties determined according to the properties of the specified audio tracks. Initialization will fail if the audio settings cannot be used with the specified tracks.  AVSampleRateConverterAudioQualityKey is not supported.
 */
- (instancetype)initWithAudioTracks:(NSArray<AVAssetTrack *> *)audioTracks audioSettings:(nullable NSDictionary<NSString *, id> *)audioSettings NS_DESIGNATED_INITIALIZER;

/*!
 @property audioTracks
 @abstract
	The tracks from which the receiver reads mixed audio.

 @discussion
	The value of this property is an NSArray of AVAssetTracks owned by the target AVAssetReader's asset.
 */
@property (nonatomic, readonly) NSArray<AVAssetTrack *> *audioTracks;

/*!
 @property audioSettings
 @abstract
	The audio settings used by the receiver.

 @discussion
	The value of this property is an NSDictionary that contains values for keys from AVAudioSettings.h (linear PCM only).  A value of nil indicates that the receiver will return audio samples in a convenient uncompressed format, with sample rate and other properties determined according to the properties of the receiver's audio tracks.
 */ 
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *audioSettings;

/*!
 @property audioMix
 @abstract
	The audio mix used by the receiver.

 @discussion
	The value of this property is an AVAudioMix that can be used to specify how the volume of audio samples read from each source track will change over the timeline of the source asset.
 
	This property cannot be set after reading has started.
 */
@property (nonatomic, copy, nullable) AVAudioMix *audioMix;

/*!
 @property audioTimePitchAlgorithm
 @abstract
	Indicates the processing algorithm used to manage audio pitch for scaled audio edits.
 
 @discussion
	Constants for various time pitch algorithms, e.g. AVAudioTimePitchAlgorithmSpectral, are defined in AVAudioProcessingSettings.h.  An NSInvalidArgumentException will be raised if this property is set to a value other than the constants defined in that file.
 
	The default value is AVAudioTimePitchAlgorithmSpectral.
 */
@property (nonatomic, copy) AVAudioTimePitchAlgorithm audioTimePitchAlgorithm NS_AVAILABLE(10_9, 7_0);

@end


@class AVAssetReaderVideoCompositionOutputInternal;

/*!
 @class AVAssetReaderVideoCompositionOutput
 @abstract
	AVAssetReaderVideoCompositionOutput is a concrete subclass of AVAssetReaderOutput that defines an interface for reading video frames that have been composited together from the frames in one or more AVAssetTracks of an AVAssetReader's AVAsset.
 
 @discussion
	Clients can read the video frames composited from one or more asset tracks by adding an instance of AVAssetReaderVideoCompositionOutput to an AVAssetReader using the -[AVAssetReader addOutput:] method.
 */
NS_CLASS_AVAILABLE(10_7, 4_1)
@interface AVAssetReaderVideoCompositionOutput : AVAssetReaderOutput
{
@private
	AVAssetReaderVideoCompositionOutputInternal	*_videoCompositionOutputInternal;
}
AV_INIT_UNAVAILABLE

/*!
 @method assetReaderVideoCompositionOutputWithVideoTracks:videoSettings:
 @abstract
	Creates an instance of AVAssetReaderVideoCompositionOutput for reading composited video from the specified video tracks and supplying media data according to the specified video settings.

 @param tracks
	An NSArray of AVAssetTrack objects from which the resulting AVAssetReaderVideoCompositionOutput should read video frames for compositing.
 @param videoSettings
	An NSDictionary of video settings to be used for video output.  See AVVideoSettings.h for more information about how to construct a video settings dictionary.
 @result
	An instance of AVAssetReaderVideoCompositionOutput.

 @discussion
	Each track must be one of the tracks owned by the target AVAssetReader's asset and must be of media type AVMediaTypeVideo.
 	
	A value of nil for videoSettings configures the output to return samples in a convenient uncompressed format, with properties determined according to the properties of the specified video tracks.  Initialization will fail if the video settings cannot be used with the specified tracks.
	
	AVAssetReaderVideoCompositionOutput can only produce uncompressed output.  This means that the video settings dictionary must follow the rules for uncompressed video output, as laid out in AVVideoSettings.h.  In addition, the following keys are not supported:

		AVVideoCleanApertureKey
		AVVideoPixelAspectRatioKey
		AVVideoScalingModeKey
 */
+ (instancetype)assetReaderVideoCompositionOutputWithVideoTracks:(NSArray<AVAssetTrack *> *)videoTracks videoSettings:(nullable NSDictionary<NSString *, id> *)videoSettings;

/*!
 @method initWithVideoTracks:videoSettings:
 @abstract
	Creates an instance of AVAssetReaderVideoCompositionOutput for reading composited video from the specified video tracks and supplying media data according to the specified video settings.

 @param tracks
	An NSArray of AVAssetTrack objects from which the resulting AVAssetReaderVideoCompositionOutput should read video frames for compositing.
 @param videoSettings
	An NSDictionary of video settings to be used for video output.  See AVVideoSettings.h for more information about how to construct a video settings dictionary.
 @result An instance of AVAssetReaderVideoCompositionOutput.

 @discussion
	Each track must be one of the tracks owned by the target AVAssetReader's asset and must be of media type AVMediaTypeVideo.
 	
	A value of nil for videoSettings configures the output to return samples in a convenient uncompressed format, with properties determined according to the properties of the specified video tracks.  Initialization will fail if the video settings cannot be used with the specified tracks.
	
	AVAssetReaderVideoCompositionOutput can only produce uncompressed output.  This means that the video settings dictionary must follow the rules for uncompressed video output, as laid out in AVVideoSettings.h.  In addition, the following keys are not supported:
 
		AVVideoCleanApertureKey
		AVVideoPixelAspectRatioKey
		AVVideoScalingModeKey
 */
- (instancetype)initWithVideoTracks:(NSArray<AVAssetTrack *> *)videoTracks videoSettings:(nullable NSDictionary<NSString *, id> *)videoSettings NS_DESIGNATED_INITIALIZER;

/*!
 @property videoTracks
 @abstract
	The tracks from which the receiver reads composited video.

 @discussion
	The value of this property is an NSArray of AVAssetTracks owned by the target AVAssetReader's asset.
 */
@property (nonatomic, readonly) NSArray<AVAssetTrack *> *videoTracks;

/*!
 @property videoSettings
 @abstract
	The video settings used by the receiver.

 @discussion
	The value of this property is an NSDictionary that contains values for keys as specified by AVVideoSettings.h.  A value of nil indicates that the receiver will return video frames in a convenient uncompressed format, with properties determined according to the properties of the receiver's video tracks.
 */ 
@property (nonatomic, readonly, nullable) NSDictionary<NSString *, id> *videoSettings;

/*!
 @property videoComposition
 @abstract
	The composition of video used by the receiver.

 @discussion
	The value of this property is an AVVideoComposition that can be used to specify the visual arrangement of video frames read from each source track over the timeline of the source asset.
 
	This property cannot be set after reading has started.
 */
@property (nonatomic, copy, nullable) AVVideoComposition *videoComposition;

/*!
 @property customVideoCompositor
 @abstract
 	Indicates the custom video compositor instance used by the receiver.

 @discussion
 	This property is nil if there is no video compositor, or if the internal video compositor is in use.
 */
@property (nonatomic, readonly, nullable) id <AVVideoCompositing> customVideoCompositor NS_AVAILABLE(10_9, 7_0);

@end


@class AVTimedMetadataGroup;
@class AVAssetReaderOutputMetadataAdaptorInternal;

/*!
 @class AVAssetReaderOutputMetadataAdaptor
 @abstract
	Defines an interface for reading metadata, packaged as instances of AVTimedMetadataGroup, from a single AVAssetReaderTrackOutput object.
 */

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAssetReaderOutputMetadataAdaptor : NSObject
{
@private
	AVAssetReaderOutputMetadataAdaptorInternal *_internal;
}
AV_INIT_UNAVAILABLE

/*!
 @method assetReaderOutputMetadataAdaptorWithAssetReaderTrackOutput:
 @abstract
	Creates a new timed metadata group adaptor for retrieving timed metadata group objects from an asset reader output.

 @param	assetReaderOutput
	An instance of AVAssetReaderTrackOutput that vends sample buffers containing metadata, e.g. an AVAssetReaderTrackOutput object initialized with a track of media type AVMediaTypeMetadata and nil outputSettings.
 @result
	An instance of AVAssetReaderOutputMetadataAdaptor

 @discussion
	It is an error to create a timed metadata group adaptor with an asset reader output that does not vend metadata.  It is also an error to create a timed metadata group adaptor with an asset reader output whose asset reader has already started reading, or an asset reader output that already has been used to initialize another timed metadata group adaptor.
	
	Clients should not mix calls to -[AVAssetReaderTrackOutput copyNextSampleBuffer] and -[AVAssetReaderOutputMetadataAdaptor nextTimedMetadataGroup].  Once an AVAssetReaderTrackOutput instance has been used to initialize an AVAssetReaderOutputMetadataAdaptor, calling -copyNextSampleBuffer on that instance will result in an exception being thrown.
 */
+ (instancetype)assetReaderOutputMetadataAdaptorWithAssetReaderTrackOutput:(AVAssetReaderTrackOutput *)trackOutput;

/*!
 @method initWithAssetReaderTrackOutput:
 @abstract
	Creates a new timed metadata group adaptor for retrieving timed metadata group objects from an asset reader output.

 @param	assetReaderOutput
	An instance of AVAssetReaderTrackOutput that vends sample buffers containing metadata, e.g. an AVAssetReaderTrackOutput object initialized with a track of media type AVMediaTypeMetadata and nil outputSettings.
 @result
	An instance of AVAssetReaderOutputMetadataAdaptor

 @discussion
	It is an error to create a timed metadata group adaptor with an asset reader output that does not vend metadata.  It is also an error to create a timed metadata group adaptor with an asset reader output whose asset reader has already started reading, or an asset reader output that already has been used to initialize another timed metadata group adaptor.
	
	Clients should not mix calls to -[AVAssetReaderTrackOutput copyNextSampleBuffer] and -[AVAssetReaderOutputMetadataAdaptor nextTimedMetadataGroup].  Once an AVAssetReaderTrackOutput instance has been used to initialize an AVAssetReaderOutputMetadataAdaptor, calling -copyNextSampleBuffer on that instance will result in an exception being thrown.
 */
- (instancetype)initWithAssetReaderTrackOutput:(AVAssetReaderTrackOutput *)trackOutput NS_DESIGNATED_INITIALIZER;

/*!
 @property assetReaderTrackOutput
 @abstract
	The asset reader track output from which the receiver pulls timed metadata groups.
 */
@property (nonatomic, readonly) AVAssetReaderTrackOutput *assetReaderTrackOutput;

/*!
 @method nextTimedMetadataGroup
 @abstract
	Returns the next timed metadata group for the asset reader output, synchronously.
	
 @result
	An instance of AVTimedMetadataGroup, representing the next logical segment of metadata coming from the source asset reader output.
	
 @discussion
	This method will return nil when all timed metadata groups have been read from the asset reader output, or if there is an error that prevents the timed metadata group adaptor from reading more timed metadata groups.  When this method returns nil, clients should check the value of the associated AVAssetReader's status property to determine why no more samples could be read.
	
	Unlike -[AVAssetReaderTrackOutput copyNextSampleBuffer], this method returns an autoreleased object.
 
	Before calling this method, you must ensure that the output which underlies the receiver is attached to an AVAssetReader via a prior call to -addOutput: and that -startReading has been called on the asset reader.
 */
- (nullable AVTimedMetadataGroup *)nextTimedMetadataGroup;

@end

@class AVAssetReaderSampleReferenceOutputInternal;

/*!
 @class AVAssetReaderSampleReferenceOutput
 @abstract
	AVAssetReaderSampleReferenceOutput is a concrete subclass of AVAssetReaderOutput that defines an interface for reading sample references from a single AVAssetTrack of an AVAssetReader's AVAsset.
 @discussion
	Clients can extract information about the location (file URL and offset) of samples in a track by adding an instance of AVAssetReaderSampleReferenceOutput to an AVAssetReader using the -[AVAssetReader addOutput:] method. No actual sample data can be extracted using this class. The location of the sample data is described by the kCMSampleBufferAttachmentKey_SampleReferenceURL and kCMSampleBufferAttachmentKey_SampleReferenceByteOffset attachments on the extracted sample buffers. More information about sample buffers describing sample references can be found in the CMSampleBuffer documentation.
 
	Sample buffers extracted using this class can also be appended to an AVAssetWriterInput to create movie tracks that are not self-contained and reference data in the original file instead.  Currently, only instances of AVAssetWriter configured to write files of type AVFileTypeQuickTimeMovie can be used to write tracks that are not self-contained.
 
	Since no sample data is ever returned by instances of AVAssetReaderSampleReferenceOutput, the value of the alwaysCopiesSampleData property is ignored.
 */

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAssetReaderSampleReferenceOutput : AVAssetReaderOutput
{
@private
	AVAssetReaderSampleReferenceOutputInternal	*_sampleReferenceOutputInternal;
}
AV_INIT_UNAVAILABLE

/*!
 @method assetReaderSampleReferenceOutputWithTrack:
 @abstract
	Returns an instance of AVAssetReaderSampleReferenceOutput for supplying sample references.
 
 @param track
	The AVAssetTrack for which the resulting AVAssetReaderSampleReferenceOutput should provide sample references.
 @result
	An instance of AVAssetReaderSampleReferenceOutput.
 
 @discussion
	The track must be one of the tracks contained by the target AVAssetReader's asset.
 */
+ (instancetype)assetReaderSampleReferenceOutputWithTrack:(AVAssetTrack *)track;

/*!
 @method initWithTrack:
 @abstract
	Returns an instance of AVAssetReaderSampleReferenceOutput for supplying sample references.
 
 @param track
	The AVAssetTrack for which the resulting AVAssetReaderSampleReferenceOutput should provide sample references.
 @result
	An instance of AVAssetReaderTrackOutput.
 
 @discussion
	The track must be one of the tracks contained by the target AVAssetReader's asset.
  */
- (instancetype)initWithTrack:(AVAssetTrack *)track NS_DESIGNATED_INITIALIZER;

/*!
 @property track
 @abstract
	The track from which the receiver extracts sample references.
 
 @discussion
	The value of this property is an AVAssetTrack owned by the target AVAssetReader's asset.
 */
@property (nonatomic, readonly) AVAssetTrack *track;

@end

NS_ASSUME_NONNULL_END

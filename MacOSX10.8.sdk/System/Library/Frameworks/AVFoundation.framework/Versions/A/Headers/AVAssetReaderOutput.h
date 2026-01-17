/*
    File:  AVAssetReaderOutput.h

	Framework:  AVFoundation
 
    Copyright 2010-2012 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVVideoComposition.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMSampleBuffer.h>

@class AVAssetTrack;
@class AVAudioMixInputParameters;
@class AVAudioMix;
@class AVVideoComposition;

@class AVAssetReaderOutputInternal;

/*!
 @class AVAssetReaderOutput
 @abstract
	AVAssetReaderOutput is an abstract class that defines an interface for reading a single collection of samples of a common media type from an AVAssetReader.
 
 @discussion
	Clients can read the media data of an asset by adding one or more concrete instances of AVAssetReaderOutput to an AVAssetReader using the -[AVAssetReader addOutput:] method.
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
	When this property is YES, the AVAssetReaderOutput will always vend a buffer with copied data to the client.  Data in such buffers can be freely modified by the client. When this property is NO, the buffers vended to the client may not be copied.  Such buffers may still be referenced by other entities. The result of modifying a buffer whose data hasn't been copied is undefined.  Requesting buffers whose data hasn't been copied when possible can lead to performance improvements.
 
	Default is YES
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
- (CMSampleBufferRef)copyNextSampleBuffer;

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
	
	AVAssetReaderTrackOutput can only produce uncompressed output.  For audio output settings, this means that AVFormatIDKey must be kAudioFormatLinearPCM.  For video output settings, this means that the dictionary must follow the rules for uncompressed video output, as laid out in AVVideoSettings.h.  AVAssetReaderTrackOutput does not support the AVAudioSettings.h key AVSampleRateConverterAudioQualityKey or the AVVideoSettings.h key AVVideoScalingModeKey.
	
	When constructing video output settings the choice of pixel format will affect the performance and quality of the decompression. Below are some recommendations.
	
	iOS:
	For optimal performance when decompressing video the requested pixel format should be one that the decoder supports natively to avoid unnecessary conversions. For H.264 use either kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange, or kCVPixelFormatType_420YpCbCr8BiPlanarFullRange if the video is known to be full range. If you need to work in the RGB domain then kCVPixelFormatType_32BGRA is recommended.
	
	Mac OS X:
	kCVPixelFormatType_422YpCbCr8 is the preferred pixel format for video and is generally the most performant when decoding. If you need to work in the RGB domain then kCVPixelFormatType_32ARGB is recommended.
 
	ProRes encoded media can contain up to 12bits/ch. If your source is ProRes encoded and you wish to preserve more than 8bits/ch during decompression then use one of the following pixel formats: kCVPixelFormatType_4444AYpCbCr16, kCVPixelFormatType_422YpCbCr16, kCVPixelFormatType_422YpCbCr10, or kCVPixelFormatType_64ARGB.  AVAssetReader does not support scaling with any of these high bit depth pixel formats. If you use them then do not specify kCVPixelBufferWidthKey or kCVPixelBufferHeightKey in your outputSettings dictionary. If you plan to append these sample buffers to an AVAssetWriterInput then note that only the ProRes encoders support these pixel formats.

	ProRes 4444 encoded media can contain a mathematically lossless alpha channel. To preserve the alpha channel during decompression use a pixel format with an alpha component such as kCVPixelFormatType_4444AYpCbCr16 or kCVPixelFormatType_64ARGB. To test whether your source contains an alpha channel check that the track's format description has kCMFormatDescriptionExtension_Depth and that its value is 32.
 */
+ (AVAssetReaderTrackOutput *)assetReaderTrackOutputWithTrack:(AVAssetTrack *)track outputSettings:(NSDictionary *)outputSettings;

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
	
	AVAssetReaderTrackOutput can only produce uncompressed output.  For audio output settings, this means that AVFormatIDKey must be kAudioFormatLinearPCM.  For video output settings, this means that the dictionary must follow the rules for uncompressed video output, as laid out in AVVideoSettings.h.  AVAssetReaderTrackOutput does not support the AVAudioSettings.h key AVSampleRateConverterAudioQualityKey or the AVVideoSettings.h key AVVideoScalingModeKey.
	
	When constructing video output settings the choice of pixel format will affect the performance and quality of the decompression. Below are some recommendations.
	
	iOS:
	For optimal performance when decompressing video the requested pixel format should be one that the decoder supports natively to avoid unnecessary conversions. For H.264 use either kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange, or kCVPixelFormatType_420YpCbCr8BiPlanarFullRange if the video is known to be full range. If you need to work in the RGB domain then kCVPixelFormatType_32BGRA is recommended.
	
	Mac OS X:
	kCVPixelFormatType_422YpCbCr8 is the preferred pixel format for video and is generally the most performant when decoding.  If you need to work in the RGB domain then kCVPixelFormatType_32ARGB is recommended.
 
	ProRes encoded media can contain up to 12bits/ch. If your source is ProRes encoded and you wish to preserve more than 8bits/ch during decompression then use one of the following pixel formats: kCVPixelFormatType_4444AYpCbCr16, kCVPixelFormatType_422YpCbCr16, kCVPixelFormatType_422YpCbCr10, or kCVPixelFormatType_64ARGB.  AVAssetReader does not support scaling with any of these high bit depth pixel formats. If you use them then do not specify kCVPixelBufferWidthKey or kCVPixelBufferHeightKey in your outputSettings dictionary. If you plan to append these sample buffers to an AVAssetWriterInput then note that only the ProRes encoders support these pixel formats.

	ProRes 4444 encoded media can contain a mathematically lossless alpha channel. To preserve the alpha channel during decompression use a pixel format with an alpha component such as kCVPixelFormatType_4444AYpCbCr16 or kCVPixelFormatType_64ARGB.  To test whether your source contains an alpha channel check that the track's format description has kCMFormatDescriptionExtension_Depth and that its value is 32.
 */
- (id)initWithTrack:(AVAssetTrack *)track outputSettings:(NSDictionary *)outputSettings;

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
@property (nonatomic, readonly) NSDictionary *outputSettings;

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
+ (AVAssetReaderAudioMixOutput *)assetReaderAudioMixOutputWithAudioTracks:(NSArray *)audioTracks audioSettings:(NSDictionary *)audioSettings;

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
- (id)initWithAudioTracks:(NSArray *)audioTracks audioSettings:(NSDictionary *)audioSettings;

/*!
 @property audioTracks
 @abstract
	The tracks from which the receiver reads mixed audio.

 @discussion
	The value of this property is an NSArray of AVAssetTracks owned by the target AVAssetReader's asset.
 */
@property (nonatomic, readonly) NSArray *audioTracks;

/*!
 @property audioSettings
 @abstract
	The audio settings used by the receiver.

 @discussion
	The value of this property is an NSDictionary that contains values for keys from AVAudioSettings.h (linear PCM only).  A value of nil indicates that the receiver will return audio samples in a convenient uncompressed format, with sample rate and other properties determined according to the properties of the receiver's audio tracks.
 */ 
@property (nonatomic, readonly) NSDictionary *audioSettings;

/*!
 @property audioMix
 @abstract
	The audio mix used by the receiver.

 @discussion
	The value of this property is an AVAudioMix that can be used to specify how the volume of audio samples read from each source track will change over the timeline of the source asset.
 
	This property cannot be set after reading has started.
 */
@property (nonatomic, copy) AVAudioMix *audioMix;

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
	
	AVAssetReaderVideoCompositionOutput can only produce uncompressed output.  This means that the video settings dictionary must follow the rules for uncompressed video output, as laid out in AVVideoSettings.h.  AVVideoScalingModeKey is not supported.
 */
+ (AVAssetReaderVideoCompositionOutput *)assetReaderVideoCompositionOutputWithVideoTracks:(NSArray *)videoTracks videoSettings:(NSDictionary *)videoSettings;

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
	
	AVAssetReaderVideoCompositionOutput can only produce uncompressed output.  This means that the video settings dictionary must follow the rules for uncompressed video output, as laid out in AVVideoSettings.h.  AVVideoScalingModeKey is not supported.
 */
- (id)initWithVideoTracks:(NSArray *)videoTracks videoSettings:(NSDictionary *)videoSettings;

/*!
 @property videoTracks
 @abstract
	The tracks from which the receiver reads composited video.

 @discussion
	The value of this property is an NSArray of AVAssetTracks owned by the target AVAssetReader's asset.
 */
@property (nonatomic, readonly) NSArray *videoTracks;

/*!
 @property videoSettings
 @abstract
	The video settings used by the receiver.

 @discussion
	The value of this property is an NSDictionary that contains values for keys as specified by AVVideoSettings.h.  A value of nil indicates that the receiver will return video frames in a convenient uncompressed format, with properties determined according to the properties of the receiver's video tracks.
 */ 
@property (nonatomic, readonly) NSDictionary *videoSettings;

/*!
 @property videoComposition
 @abstract
	The composition of video used by the receiver.

 @discussion
	The value of this property is an AVVideoComposition that can be used to specify the visual arrangement of video frames read from each source track over the timeline of the source asset.
 
	This property cannot be set after reading has started.
 */
@property (nonatomic, copy) AVVideoComposition *videoComposition;

@end

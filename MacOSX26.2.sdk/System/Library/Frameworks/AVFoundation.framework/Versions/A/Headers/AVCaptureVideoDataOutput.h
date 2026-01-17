#if !__has_include(<AVFCapture/AVCaptureVideoDataOutput.h>)
/*
    File:  AVCaptureVideoDataOutput.h
 
    Framework:  AVFoundation
 
    Copyright 2010-2022 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureOutputBase.h>
#import <AVFoundation/AVVideoSettings.h>
#import <CoreMedia/CMSampleBuffer.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark AVCaptureVideoDataOutput

@class AVMetadataItem;
@class AVCaptureVideoDataOutputInternal;
@protocol AVCaptureVideoDataOutputSampleBufferDelegate;

/*!
 @class AVCaptureVideoDataOutput
 @abstract
    AVCaptureVideoDataOutput is a concrete subclass of AVCaptureOutput that can be used to process uncompressed or compressed frames from the video being captured.
 
 @discussion
    Instances of AVCaptureVideoDataOutput produce video frames suitable for processing using other media APIs. Applications can access the frames with the captureOutput:didOutputSampleBuffer:fromConnection: delegate method.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface AVCaptureVideoDataOutput : AVCaptureOutput
{
@private
    AVCaptureVideoDataOutputInternal *_internal;
}

- (instancetype)init;

+ (instancetype)new;

/*!
 @method setSampleBufferDelegate:queue:
 @abstract
    Sets the receiver's delegate that will accept captured buffers and dispatch queue on which the delegate will be called.
 
 @param sampleBufferDelegate
    An object conforming to the AVCaptureVideoDataOutputSampleBufferDelegate protocol that will receive sample buffers after they are captured.
 @param sampleBufferCallbackQueue
    A dispatch queue on which all sample buffer delegate methods will be called.
 
 @discussion
    When a new video sample buffer is captured it will be vended to the sample buffer delegate using the captureOutput:didOutputSampleBuffer:fromConnection: delegate method. All delegate methods will be called on the specified dispatch queue. If the queue is blocked when new frames are captured, those frames will be automatically dropped at a time determined by the value of the alwaysDiscardsLateVideoFrames property. This allows clients to process existing frames on the same queue without having to manage the potential memory usage increases that would otherwise occur when that processing is unable to keep up with the rate of incoming frames. If their frame processing is consistently unable to keep up with the rate of incoming frames, clients should consider using the minFrameDuration property, which will generally yield better performance characteristics and more consistent frame rates than frame dropping alone.
 
    Clients that need to minimize the chances of frames being dropped should specify a queue on which a sufficiently small amount of processing is being done outside of receiving sample buffers. However, if such clients migrate extra processing to another queue, they are responsible for ensuring that memory usage does not grow without bound from frames that have not been processed.
 
    A serial dispatch queue must be used to guarantee that video frames will be delivered in order. The sampleBufferCallbackQueue parameter may not be NULL, except when setting the sampleBufferDelegate to nil otherwise -setSampleBufferDelegate:queue: throws an NSInvalidArgumentException.
 */
- (void)setSampleBufferDelegate:(nullable id<AVCaptureVideoDataOutputSampleBufferDelegate>)sampleBufferDelegate queue:(nullable dispatch_queue_t)sampleBufferCallbackQueue;

/*!
 @property sampleBufferDelegate
 @abstract
    The receiver's delegate.
 
 @discussion
    The value of this property is an object conforming to the AVCaptureVideoDataOutputSampleBufferDelegate protocol that will receive sample buffers after they are captured. The delegate is set using the setSampleBufferDelegate:queue: method.
 */
@property(nonatomic, readonly, nullable) id<AVCaptureVideoDataOutputSampleBufferDelegate> sampleBufferDelegate;

/*!
 @property sampleBufferCallbackQueue
 @abstract
    The dispatch queue on which all sample buffer delegate methods will be called.
 
 @discussion
    The value of this property is a dispatch_queue_t. The queue is set using the setSampleBufferDelegate:queue: method.
 */
@property(nonatomic, readonly, nullable) dispatch_queue_t sampleBufferCallbackQueue;

/*!
 @property videoSettings
 @abstract
    Specifies the settings used to decode or re-encode video before it is output by the receiver.
 
 @discussion
    See AVVideoSettings.h for more information on how to construct a video settings dictionary. To receive samples in their device native format, set this property to an empty dictionary (i.e. [NSDictionary dictionary]). To receive samples in a default uncompressed format, set this property to nil. Note that after this property is set to nil, subsequent querying of this property will yield a non-nil dictionary reflecting the settings used by the AVCaptureSession's current sessionPreset.
 
    On iOS versions prior to iOS 16.0, the only supported key is kCVPixelBufferPixelFormatTypeKey. Use -availableVideoCVPixelFormatTypes for the list of supported pixel formats. For apps linked on or after iOS 16.0, kCVPixelBufferPixelFormatTypeKey, kCVPixelBufferWidthKey, and kCVPixelBufferHeightKey are supported. The width and height must match the videoOrientation specified on the output's AVCaptureConnection or an NSInvalidArgumentException is thrown. The aspect ratio of width and height must match the aspect ratio of the source's activeFormat (corrected for the connection's videoOrientation) or an NSInvalidArgumentException is thrown. If width or height exceeds the source's activeFormat's width or height, an NSInvalidArgumentException is thrown. Changing width and height when deliversPreviewSizedOutputBuffers is set to YES is not supported and throws an NSInvalidArgumentException.
 */
@property(nonatomic, copy, null_resettable) NSDictionary<NSString *, id> *videoSettings;

/*!
 @method recommendedVideoSettingsForAssetWriterWithOutputFileType:
 @abstract
    Specifies the recommended settings for use with an AVAssetWriterInput.
 
 @param outputFileType
    Specifies the UTI of the file type to be written (see AVMediaFormat.h for a list of file format UTIs).
 @result
    A fully populated dictionary of keys and values that are compatible with AVAssetWriter.
 
 @discussion
    The value of this property is an NSDictionary containing values for compression settings keys defined in AVVideoSettings.h. This dictionary is suitable for use as the "outputSettings" parameter when creating an AVAssetWriterInput, such as,
 
       [AVAssetWriterInput assetWriterInputWithMediaType:AVMediaTypeVideo outputSettings:outputSettings sourceFormatHint:hint];
 
    The dictionary returned contains all necessary keys and values needed by AVAssetWriter (see AVAssetWriterInput.h, -initWithMediaType:outputSettings: for a more in depth discussion). For QuickTime movie and ISO file types, the recommended video settings will produce output comparable to that of AVCaptureMovieFileOutput.
 
    Note that the dictionary of settings is dependent on the current configuration of the receiver's AVCaptureSession and its inputs. The settings dictionary may change if the session's configuration changes. As such, you should configure your session first, then query the recommended video settings. As of iOS 8.3, movies produced with these settings successfully import into the iOS camera roll and sync to and from like devices via iTunes.
 */
- (nullable NSDictionary<NSString *, id> *)recommendedVideoSettingsForAssetWriterWithOutputFileType:(AVFileType)outputFileType API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

/*!
 @method availableVideoCodecTypesForAssetWriterWithOutputFileType:
 @abstract
    Specifies the available video codecs for use with AVAssetWriter and a given file type.
 
 @param outputFileType
    Specifies the UTI of the file type to be written (see AVMediaFormat.h for a list of file format UTIs).
 @result
    An array of video codecs; see AVVideoSettings.h for a full list.
 
 @discussion
    This method allows you to query the available video codecs that may be used when specifying an AVVideoCodecKey in -recommendedVideoSettingsForVideoCodecType:assetWriterOutputFileType:. When specifying an outputFileType of AVFileTypeQuickTimeMovie, video codecs are ordered identically to -[AVCaptureMovieFileOutput availableVideoCodecTypes].
 */
- (NSArray<AVVideoCodecType> *)availableVideoCodecTypesForAssetWriterWithOutputFileType:(AVFileType)outputFileType API_AVAILABLE(macos(10.15), ios(11.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

/*!
 @method recommendedVideoSettingsForVideoCodecType:assetWriterOutputFileType:
 @abstract
    Specifies the recommended settings for a particular video codec type, to be used with an AVAssetWriterInput.
 
 @param videoCodecType
    Specifies the desired AVVideoCodecKey to be used for compression (see AVVideoSettings.h).
 @param outputFileType
    Specifies the UTI of the file type to be written (see AVMediaFormat.h for a list of file format UTIs).
 @result
    A fully populated dictionary of keys and values that are compatible with AVAssetWriter.
 
 @discussion
    The value of this property is an NSDictionary containing values for compression settings keys defined in AVVideoSettings.h. This dictionary is suitable for use as the "outputSettings" parameter when creating an AVAssetWriterInput, such as,
        
       [AVAssetWriterInput assetWriterInputWithMediaType:AVMediaTypeVideo outputSettings:outputSettings sourceFormatHint:hint];
 
    The dictionary returned contains all necessary keys and values needed by AVAssetWriter (see AVAssetWriterInput.h, -initWithMediaType:outputSettings: for a more in depth discussion). For QuickTime movie and ISO file types, the recommended video settings will produce output comparable to that of AVCaptureMovieFileOutput.
 
    The videoCodecType string provided must be present in the availableVideoCodecTypesForAssetWriterWithOutputFileType: array, or an NSInvalidArgumentException is thrown. 
 
    Note that the dictionary of settings is dependent on the current configuration of the receiver's AVCaptureSession and its inputs. The settings dictionary may change if the session's configuration changes. As such, you should configure your session first, then query the recommended video settings. As of iOS 8.3, movies produced with these settings successfully import into the iOS camera roll and sync to and from like devices via iTunes.
 */
- (nullable NSDictionary<NSString *, id> *)recommendedVideoSettingsForVideoCodecType:(AVVideoCodecType)videoCodecType assetWriterOutputFileType:(AVFileType)outputFileType API_AVAILABLE(macos(10.15), ios(11.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

/*!
 @method recommendedVideoSettingsForVideoCodecType:assetWriterOutputFileType:outputFileURL:
 @abstract
	Specifies the recommended settings for a particular video codec type with output file URL, to be used with an AVAssetWriterInput.

 @param videoCodecType
	Specifies the desired AVVideoCodecKey to be used for compression (see AVVideoSettings.h).
 @param outputFileType
	Specifies the UTI of the file type to be written (see AVMediaFormat.h for a list of file format UTIs).
 @param outputFileURL
	Specifies the output URL of the file to be written.

	If you wish to capture onto an external storage device get an externalStorageDevice of type AVExternalStorageDevice (as defined in AVExternalStorageDevice.h):
		[AVExternalStorageDeviceDiscoverySession sharedSession] externalStorageDevices]

	Then use [externalStorageDevice nextAvailableURLsWithPathExtensions:pathExtensions error:&error] to get the output file URL.

 @result
	A fully populated dictionary of keys and values that are compatible with AVAssetWriter.

 @discussion
	The value of this property is an NSDictionary containing values for compression settings keys defined in AVVideoSettings.h. This dictionary is suitable for use as the "outputSettings" parameter when creating an AVAssetWriterInput, such as,

	   [AVAssetWriterInput assetWriterInputWithMediaType:AVMediaTypeVideo outputSettings:outputSettings sourceFormatHint:hint];

	The dictionary returned contains all necessary keys and values needed by AVAssetWriter (see AVAssetWriterInput.h, -initWithMediaType:outputSettings: for a more in depth discussion). For QuickTime movie and ISO file types, the recommended video settings will produce output comparable to that of AVCaptureMovieFileOutput.

	The videoCodecType string provided must be present in the availableVideoCodecTypesForAssetWriterWithOutputFileType: array, or an NSInvalidArgumentException is thrown.

	Note that the dictionary of settings is dependent on the current configuration of the receiver's AVCaptureSession and its inputs. The settings dictionary may change if the session's configuration changes. As such, you should configure your session first, then query the recommended video settings. As of iOS 8.3, movies produced with these settings successfully import into the iOS camera roll and sync to and from like devices via iTunes.
 */
- (nullable NSDictionary<NSString *, id> *)recommendedVideoSettingsForVideoCodecType:(AVVideoCodecType)videoCodecType assetWriterOutputFileType:(AVFileType)outputFileType outputFileURL:(nullable NSURL *)outputFileURL API_AVAILABLE(macos(14.0), ios(17.0), macCatalyst(17.0), tvos(17.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Recommends movie-level metadata for a particular video codec type and output file type, to be used with an asset writer input.
///
/// - Parameter videoCodecType: The desired ``AVVideoCodecKey`` to be used for compression (see <doc://com.apple.documentation/documentation/avfoundation/video-settings>).
/// - Parameter outputFileType: Specifies the UTI of the file type to be written (see <doc://com.apple.documentation/documentation/avfoundation/avfiletype>).
/// - Returns: A fully populated array of ``AVMetadataItem`` objects compatible with ``AVAssetWriter``.
///
/// The value of this property is an array of ``AVMetadataItem`` objects representing the collection of top-level metadata to be written in each output file. This array is suitable to use as the ``AVAssetWriter/metadata`` property before you have called ``AVAssetWriter/startWriting``. For more details see <doc://com.apple.documentation/documentation/avfoundation/avassetwriter/startwriting()>.
///
/// The ``videoCodecType`` string you provide must be present in ``availableVideoCodecTypesForAssetWriterWithOutputFileType:`` array, or an `NSInvalidArgumentException` is thrown.
///
/// For clients writing files using a ProRes Raw codec type, white balance must be locked (call ``AVCaptureDevice/setWhiteBalanceModeLockedWithDeviceWhiteBalanceGains:completionHandler:``) before querying this property, or an `NSIvalidArgumentException` is thrown.
///
/// - Note: The array of metadata is dependent on the current configuration of the receiver's ``AVCaptureSession`` and its inputs. The array may change when the session's configuration changes. As such, you should configure and start your session first, then query this method.
- (nullable NSArray<AVMetadataItem *> *)recommendedMovieMetadataForVideoCodecType:(AVVideoCodecType)videoCodecType assetWriterOutputFileType:(AVFileType)outputFileType API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// Indicates the recommended media timescale for the video track.
///
/// - Returns: The recommended media timescale based on the active capture session's inputs. It is never less than 600. It may or may not be a multiple of 600.
@property(nonatomic, readonly) CMTimeScale recommendedMediaTimeScaleForAssetWriter API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/*!
 @property availableVideoCVPixelFormatTypes
 @abstract
    Indicates the supported video pixel formats that can be specified in videoSettings.
 
 @discussion
    The value of this property is an NSArray of NSNumbers that can be used as values for the kCVPixelBufferPixelFormatTypeKey in the receiver's videoSettings property. The formats are listed in an unspecified order. This list can may change if the activeFormat of the AVCaptureDevice connected to the receiver changes.
 */
@property(nonatomic, readonly) NSArray<NSNumber *> *availableVideoCVPixelFormatTypes API_AVAILABLE(ios(5.0), macCatalyst(14.0), tvos(17.0), visionos(1.0));

/*!
 @property availableVideoCodecTypes
 @abstract
    Indicates the supported video codec formats that can be specified in videoSettings.
 
 @discussion
    The value of this property is an NSArray of AVVideoCodecTypes that can be used as values for the AVVideoCodecKey in the receiver's videoSettings property.
 */
@property(nonatomic, readonly) NSArray<AVVideoCodecType> *availableVideoCodecTypes API_AVAILABLE(ios(5.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(visionos);

/*!
 @property minFrameDuration
 @abstract
    Specifies the minimum time interval between which the receiver should output consecutive video frames.
 
 @discussion
    The value of this property is a CMTime specifying the minimum duration of each video frame output by the receiver, placing a lower bound on the amount of time that should separate consecutive frames. This is equivalent to the inverse of the maximum frame rate. A value of kCMTimeZero or kCMTimeInvalid indicates an unlimited maximum frame rate. The default value is kCMTimeInvalid. As of iOS 5.0, minFrameDuration is deprecated. Use AVCaptureConnection's videoMinFrameDuration property instead.
 */
@property(nonatomic) CMTime minFrameDuration API_DEPRECATED("Use AVCaptureConnection's videoMinFrameDuration property instead.", ios(4.0, 5.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(tvos);

/*!
 @property alwaysDiscardsLateVideoFrames
 @abstract
    Specifies whether the receiver should always discard any video frame that is not processed before the next frame is captured.
 
 @discussion
    When the value of this property is YES, the receiver will immediately discard frames that are captured while the dispatch queue handling existing frames is blocked in the captureOutput:didOutputSampleBuffer:fromConnection: delegate method. When the value of this property is NO, delegates will be allowed more time to process old frames before new frames are discarded, but application memory usage may increase significantly as a result. The default value is YES.
 */
@property(nonatomic) BOOL alwaysDiscardsLateVideoFrames;

/*!
 @property automaticallyConfiguresOutputBufferDimensions
 @abstract
    Indicates whether the receiver automatically configures the size of output buffers.
 
 @discussion
    Default value is YES. In most configurations, AVCaptureVideoDataOutput delivers full-resolution buffers, that is, buffers with the same dimensions as the source AVCaptureDevice's activeFormat's videoDimensions. When this property is set to YES, the receiver is free to configure the dimensions of the buffers delivered to -captureOutput:didOutputSampleBuffer:fromConnection:, such that they are a smaller preview size (roughly the size of the screen). For instance, when the AVCaptureSession's sessionPreset is set to AVCaptureSessionPresetPhoto, it is assumed that video data output buffers are being delivered as a preview proxy. Likewise, if an AVCapturePhotoOutput is present in the session with livePhotoCaptureEnabled, it is assumed that video data output is being used for photo preview, and thus preview-sized buffers are a better choice than full-res buffers. You can query deliversPreviewSizedOutputBuffers to find out whether automatic configuration of output buffer dimensions is currently downscaling buffers to a preview size. You can also query the videoSettings property to find out the exact width and height being delivered. If you wish to manually set deliversPreviewSizedOutputBuffers, you must first set automaticallyConfiguresOutputBufferDimensions to NO.
 */
@property(nonatomic) BOOL automaticallyConfiguresOutputBufferDimensions API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/*!
 @property deliversPreviewSizedOutputBuffers
 @abstract
    Indicates whether the receiver is currently configured to deliver preview sized buffers.
 
 @discussion
    If you wish to manually set deliversPreviewSizedOutputBuffers, you must first set automaticallyConfiguresOutputBufferDimensions to NO. When deliversPreviewSizedOutputBuffers is set to YES, auto focus, exposure, and white balance changes are quicker. AVCaptureVideoDataOutput assumes that the buffers are being used for on-screen preview rather than recording.

    When AVCaptureDevice.activeFormat supports ProRes Raw video, setting deliversPreviewSizedOutputBuffers gives out buffers with 422 format that can be used for proxy video recording.
 */
@property(nonatomic) BOOL deliversPreviewSizedOutputBuffers API_AVAILABLE(ios(13.0), macCatalyst(14.0), tvos(17.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/// Indicates whether the receiver should prepare the cellular radio for imminent network activity.
///
/// Apps that scan video data output buffers for information that will result in network activity (such as detecting a QRCode containing a URL) should set this property `true` to allow the cellular radio to prepare for an imminent network request. Enabling this property requires a lengthy reconfiguration of the capture render pipeline, so you should set this property to `true` before calling ``AVCaptureSession/startRunning``.
///
/// Using this API requires your app to adopt the entitlement `com.apple.developer.avfoundation.video-data-output-prepares-cellular-radio-for-machine-readable-code-scanning`.
@property BOOL preparesCellularRadioForNetworkConnection API_AVAILABLE(ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(macos, visionos) API_UNAVAILABLE(watchos);

/// Indicates whether the receiver should preserve dynamic HDR metadata as an attachment on the output sample buffer's underlying pixel buffer.
///
/// Set this property to `true` if you wish to use ``AVCaptureVideoDataOutput`` with ``AVAssetWriter`` to record HDR movies. You must also set ``kVTCompressionPropertyKey_PreserveDynamicHDRMetadata`` to `true` in the compression settings you pass to your ``AVAssetWriterInput``. These compression settings are represented under the ``AVVideoCompressionPropertiesKey`` sub-dictionary of your top-level AVVideoSettings (see <doc://com.apple.documentation/documentation/avfoundation/video-settings>). When you set this key to `true`, performance improves, as the encoder is able to skip HDR metadata calculation for every frame. The default value is `false`.
@property BOOL preservesDynamicHDRMetadata API_AVAILABLE(ios(26.0), macCatalyst(26.0), tvos(26.0), macos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

@end


/*!
 @protocol AVCaptureVideoDataOutputSampleBufferDelegate
 @abstract
    Defines an interface for delegates of AVCaptureVideoDataOutput to receive captured video sample buffers and be notified of late sample buffers that were dropped.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol AVCaptureVideoDataOutputSampleBufferDelegate <NSObject>

@optional

/*!
 @method captureOutput:didOutputSampleBuffer:fromConnection:
 @abstract
    Called whenever an AVCaptureVideoDataOutput instance outputs a new video frame.
 
 @param output
    The AVCaptureVideoDataOutput instance that output the frame.
 @param sampleBuffer
    A CMSampleBuffer object containing the video frame data and additional information about the frame, such as its format and presentation time.
 @param connection
    The AVCaptureConnection from which the video was received.
 
 @discussion
    Delegates receive this message whenever the output captures and outputs a new video frame, decoding or re-encoding it as specified by its videoSettings property. Delegates can use the provided video frame in conjunction with other APIs for further processing. This method will be called on the dispatch queue specified by the output's sampleBufferCallbackQueue property. This method is called periodically, so it must be efficient to prevent capture performance problems, including dropped frames.
 
    Clients that need to reference the CMSampleBuffer object outside of the scope of this method must CFRetain it and then CFRelease it when they are finished with it.
 
    Note that to maintain optimal performance, some sample buffers directly reference pools of memory that may need to be reused by the device system and other capture inputs. This is frequently the case for uncompressed device native capture where memory blocks are copied as little as possible. If multiple sample buffers reference such pools of memory for too long, inputs will no longer be able to copy new samples into memory and those samples will be dropped. If your application is causing samples to be dropped by retaining the provided CMSampleBuffer objects for too long, but it needs access to the sample data for a long period of time, consider copying the data into a new buffer and then calling CFRelease on the sample buffer if it was previously retained so that the memory it references can be reused.
 */
- (void)captureOutput:(AVCaptureOutput *)output didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection;

/*!
 @method captureOutput:didDropSampleBuffer:fromConnection:
 @abstract
    Called once for each frame that is discarded.
 
 @param output
    The AVCaptureVideoDataOutput instance that dropped the frame.
 @param sampleBuffer
    A CMSampleBuffer object containing information about the dropped frame, such as its format and presentation time. This sample buffer will contain none of the original video data.
 @param connection
    The AVCaptureConnection from which the dropped video frame was received.
 
 @discussion
    Delegates receive this message whenever a video frame is dropped. This method is called once for each dropped frame. The CMSampleBuffer object passed to this delegate method will contain metadata about the dropped video frame, such as its duration and presentation time stamp, but will contain no actual video data. On iOS, Included in the sample buffer attachments is the kCMSampleBufferAttachmentKey_DroppedFrameReason, which indicates why the frame was dropped. This method will be called on the dispatch queue specified by the output's sampleBufferCallbackQueue property. Because this method will be called on the same dispatch queue that is responsible for outputting video frames, it must be efficient to prevent further capture performance problems, such as additional dropped video frames.
 */
- (void)captureOutput:(AVCaptureOutput *)output didDropSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection API_AVAILABLE(ios(6.0), macCatalyst(14.0), tvos(17.0), visionos(1.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureVideoDataOutput.h>
#endif

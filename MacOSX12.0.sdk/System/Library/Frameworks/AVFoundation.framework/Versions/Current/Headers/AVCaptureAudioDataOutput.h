#if !__has_include(<AVFCapture/AVCaptureAudioDataOutput.h>)
/*
    File:  AVCaptureAudioDataOutput.h
 
    Framework:  AVFoundation
 
    Copyright 2010-2021 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureOutputBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <CoreMedia/CMSampleBuffer.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark AVCaptureAudioDataOutput

@class AVCaptureAudioDataOutputInternal;
@protocol AVCaptureAudioDataOutputSampleBufferDelegate;

/*!
 @class AVCaptureAudioDataOutput
 @abstract
    AVCaptureAudioDataOutput is a concrete subclass of AVCaptureOutput that can be used to process uncompressed or compressed samples from the audio being captured.
 
 @discussion
    Instances of AVCaptureAudioDataOutput produce audio sample buffers suitable for processing using other media APIs. Applications can access the sample buffers with the captureOutput:didOutputSampleBuffer:fromConnection: delegate method.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureAudioDataOutput : AVCaptureOutput
{
@private
    AVCaptureAudioDataOutputInternal *_internal;
}

- (instancetype)init;

+ (instancetype)new;

/*!
 @method setSampleBufferDelegate:queue:
 @abstract
    Sets the receiver's delegate that will accept captured buffers and dispatch queue on which the delegate will be called.
 
 @param sampleBufferDelegate
    An object conforming to the AVCaptureAudioDataOutputSampleBufferDelegate protocol that will receive sample buffers after they are captured.
 @param sampleBufferCallbackQueue
    A dispatch queue on which all sample buffer delegate methods will be called.
 
 @discussion
    When a new audio sample buffer is captured it will be vended to the sample buffer delegate using the captureOutput:didOutputSampleBuffer:fromConnection: delegate method. All delegate methods will be called on the specified dispatch queue. If the queue is blocked when new samples are captured, those samples will be automatically dropped when they become sufficiently late. This allows clients to process existing samples on the same queue without having to manage the potential memory usage increases that would otherwise occur when that processing is unable to keep up with the rate of incoming samples.
 
    Clients that need to minimize the chances of samples being dropped should specify a queue on which a sufficiently small amount of processing is being done outside of receiving sample buffers. However, if such clients migrate extra processing to another queue, they are responsible for ensuring that memory usage does not grow without bound from samples that have not been processed.
 
    A serial dispatch queue must be used to guarantee that audio samples will be delivered in order. The sampleBufferCallbackQueue parameter may not be NULL, except when setting sampleBufferDelegate to nil.
 */
- (void)setSampleBufferDelegate:(nullable id<AVCaptureAudioDataOutputSampleBufferDelegate>)sampleBufferDelegate queue:(nullable dispatch_queue_t)sampleBufferCallbackQueue;

/*!
 @property sampleBufferDelegate
 @abstract
    The receiver's delegate.
 
 @discussion
    The value of this property is an object conforming to the AVCaptureAudioDataOutputSampleBufferDelegate protocol that will receive sample buffers after they are captured. The delegate is set using the setSampleBufferDelegate:queue: method.
 */
@property(nonatomic, readonly, nullable) id<AVCaptureAudioDataOutputSampleBufferDelegate> sampleBufferDelegate;

/*!
 @property sampleBufferCallbackQueue
 @abstract
    The dispatch queue on which all sample buffer delegate methods will be called.
 
 @discussion
    The value of this property is a dispatch_queue_t. The queue is set using the setSampleBufferDelegate:queue: method.
 */
@property(nonatomic, readonly, nullable) dispatch_queue_t sampleBufferCallbackQueue;

/*!
 @property audioSettings
 @abstract
    Specifies the settings used to decode or re-encode audio before it is output by the receiver.
 
 @discussion
    The value of this property is an NSDictionary containing values for audio settings keys defined in AVAudioSettings.h. When audioSettings is set to nil, the AVCaptureAudioDataOutput vends samples in their device native format.
 */
@property(nonatomic, copy, null_resettable) NSDictionary<NSString *, id> *audioSettings API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

/*!
 @method recommendedAudioSettingsForAssetWriterWithOutputFileType:
 @abstract
    Specifies the recommended settings for use with an AVAssetWriterInput.
 
 @param outputFileType
    Specifies the UTI of the file type to be written (see AVMediaFormat.h for a list of file format UTIs).
 @result
    A fully populated dictionary of keys and values that are compatible with AVAssetWriter.
 
 @discussion
    The value of this property is an NSDictionary containing values for compression settings keys defined in AVAudioSettings.h. This dictionary is suitable for use as the "outputSettings" parameter when creating an AVAssetWriterInput, such as,
 
       [AVAssetWriterInput assetWriterInputWithMediaType:AVMediaTypeAudio outputSettings:outputSettings sourceFormatHint:hint];
 
    The dictionary returned contains all necessary keys and values needed by AVAssetWriter (see AVAssetWriterInput.h, -initWithMediaType:outputSettings: for a more in depth discussion). For QuickTime movie and ISO files, the recommended audio settings will always produce output comparable to that of AVCaptureMovieFileOutput.
 
    Note that the dictionary of settings is dependent on the current configuration of the receiver's AVCaptureSession and its inputs. The settings dictionary may change if the session's configuration changes. As such, you should configure your session first, then query the recommended audio settings.
 */
- (nullable NSDictionary<NSString *, id> *)recommendedAudioSettingsForAssetWriterWithOutputFileType:(AVFileType)outputFileType API_AVAILABLE(macos(10.15), ios(7.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

@end


/*!
 @protocol AVCaptureAudioDataOutputSampleBufferDelegate
 @abstract
    Defines an interface for delegates of AVCaptureAudioDataOutput to receive captured audio sample buffers.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@protocol AVCaptureAudioDataOutputSampleBufferDelegate <NSObject>

@optional

/*!
 @method captureOutput:didOutputSampleBuffer:fromConnection:
 @abstract
    Called whenever an AVCaptureAudioDataOutput instance outputs a new audio sample buffer.
 
 @param output
    The AVCaptureAudioDataOutput instance that output the samples.
 @param sampleBuffer
    A CMSampleBuffer object containing the audio samples and additional information about them, such as their format and presentation time.
 @param connection
    The AVCaptureConnection from which the audio was received.
 
 @discussion
    Delegates receive this message whenever the output captures and outputs new audio samples, decoding or re-encoding as specified by the audioSettings property. Delegates can use the provided sample buffer in conjunction with other APIs for further processing. This method will be called on the dispatch queue specified by the output's sampleBufferCallbackQueue property. This method is called periodically, so it must be efficient to prevent capture performance problems, including dropped audio samples.
 
    Clients that need to reference the CMSampleBuffer object outside of the scope of this method must CFRetain it and then CFRelease it when they are finished with it.
 */
- (void)captureOutput:(AVCaptureOutput *)output didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureAudioDataOutput.h>
#endif

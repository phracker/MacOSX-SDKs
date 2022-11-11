#if !__has_include(<AVFCapture/AVCaptureFileOutput.h>)
/*
    File:  AVCaptureFileOutput.h
 
    Framework:  AVFoundation
 
    Copyright 2010-2021 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVCaptureOutputBase.h>
#import <AVFoundation/AVVideoSettings.h>
#import <CoreMedia/CMSampleBuffer.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark AVCaptureFileOutput

@class AVCaptureFileOutputInternal;
@class AVMetadataItem;
@protocol AVCaptureFileOutputDelegate;
@protocol AVCaptureFileOutputRecordingDelegate;

/*!
 @class AVCaptureFileOutput
 @abstract
    AVCaptureFileOutput is an abstract subclass of AVCaptureOutput that provides an interface for writing captured media to files.
 
 @discussion
    This abstract superclass defines the interface for outputs that record media samples to files. File outputs can start recording to a new file using the startRecordingToOutputFileURL:recordingDelegate: method. On successive invocations of this method on Mac OS X, the output file can by changed dynamically without losing media samples. A file output can stop recording using the stopRecording method. Because files are recorded in the background, applications will need to specify a delegate for each new file so that they can be notified when recorded files are finished.
 
    On Mac OS X, clients can also set a delegate on the file output itself that can be used to control recording along exact media sample boundaries using the captureOutput:didOutputSampleBuffer:fromConnection: method.
 
    The concrete subclasses of AVCaptureFileOutput are AVCaptureMovieFileOutput, which records media to a QuickTime movie file, and AVCaptureAudioFileOutput, which writes audio media to a variety of audio file formats.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureFileOutput : AVCaptureOutput
{
@private
    AVCaptureFileOutputInternal *_fileOutputInternal;
}

/*!
 @property delegate
 @abstract
    The receiver's delegate.
 
 @discussion
    The value of this property is an object conforming to the AVCaptureFileOutputDelegate protocol that will be able to monitor and control recording along exact sample boundaries.
 */
@property(nonatomic, assign, nullable) id<AVCaptureFileOutputDelegate> delegate API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

/*!
 @property outputFileURL
 @abstract
    The file URL of the file to which the receiver is currently recording incoming buffers.
 
 @discussion
    The value of this property is an NSURL object containing the file URL of the file currently being written by the receiver. Returns nil if the receiver is not recording to any file.
 */
@property(nonatomic, readonly, nullable) NSURL *outputFileURL;

/*!
 @method startRecordingToOutputFileURL:recordingDelegate:
 @abstract
    Tells the receiver to start recording to a new file, and specifies a delegate that will be notified when recording is finished.
 
 @param outputFileURL
    An NSURL object containing the URL of the output file. This method throws an NSInvalidArgumentException if the URL is not a valid file URL.
 @param delegate
    An object conforming to the AVCaptureFileOutputRecordingDelegate protocol. Clients must specify a delegate so that they can be notified when recording to the given URL is finished.
 
 @discussion
    The method sets the file URL to which the receiver is currently writing output media. If a file at the given URL already exists when capturing starts, recording to the new file will fail.
 
    Clients need not call stopRecording before calling this method while another recording is in progress. On Mac OS X, if this method is invoked while an existing output file was already being recorded, no media samples will be discarded between the old file and the new file.
 
    When recording is stopped either by calling stopRecording, by changing files using this method, or because of an error, the remaining data that needs to be included to the file will be written in the background. Therefore, clients must specify a delegate that will be notified when all data has been written to the file using the captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: method. The recording delegate can also optionally implement methods that inform it when data starts being written, when recording is paused and resumed, and when recording is about to be finished.
 
    On Mac OS X, if this method is called within the captureOutput:didOutputSampleBuffer:fromConnection: delegate method, the first samples written to the new file are guaranteed to be those contained in the sample buffer passed to that method.
 
    Note: AVCaptureAudioFileOutput does not support -startRecordingToOutputFileURL:recordingDelegate:. Use -startRecordingToOutputFileURL:outputFileType:recordingDelegate: instead.
 */
- (void)startRecordingToOutputFileURL:(NSURL *)outputFileURL recordingDelegate:(id<AVCaptureFileOutputRecordingDelegate>)delegate;

/*!
 @method stopRecording
 @abstract
    Tells the receiver to stop recording to the current file.
 
 @discussion
    Clients can call this method when they want to stop recording new samples to the current file, and do not want to continue recording to another file. Clients that want to switch from one file to another should not call this method. Instead they should simply call startRecordingToOutputFileURL:recordingDelegate: with the new file URL.
 
    When recording is stopped either by calling this method, by changing files using startRecordingToOutputFileURL:recordingDelegate:, or because of an error, the remaining data that needs to be included to the file will be written in the background. Therefore, before using the file, clients must wait until the delegate that was specified in startRecordingToOutputFileURL:recordingDelegate: is notified when all data has been written to the file using the captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: method.
 
    On Mac OS X, if this method is called within the captureOutput:didOutputSampleBuffer:fromConnection: delegate method, the last samples written to the current file are guaranteed to be those that were output immediately before those in the sample buffer passed to that method.
 */
- (void)stopRecording;

/*!
 @property recording
 @abstract
    Indicates whether the receiver is currently recording.
 
 @discussion
    The value of this property is YES when the receiver currently has a file to which it is writing new samples, NO otherwise.
 */
@property(nonatomic, readonly, getter=isRecording) BOOL recording;

/*!
 @property recordingPaused
 @abstract
    Indicates whether recording to the current output file is paused.
 
 @discussion
    This property indicates recording to the file returned by outputFileURL has been previously paused using the pauseRecording method. When a recording is paused, captured samples are not written to the output file, but new samples can be written to the same file in the future by calling resumeRecording.
 */
@property(nonatomic, readonly, getter=isRecordingPaused) BOOL recordingPaused __IOS_PROHIBITED __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
 @method pauseRecording
 @abstract
    Pauses recording to the current output file.
 
 @discussion
    This method causes the receiver to stop writing captured samples to the current output file returned by outputFileURL, but leaves the file open so that samples can be written to it in the future, when resumeRecording is called. This allows clients to record multiple media segments that are not contiguous in time to a single file.
 
    On Mac OS X, if this method is called within the captureOutput:didOutputSampleBuffer:fromConnection: delegate method, the last samples written to the current file are guaranteed to be those that were output immediately before those in the sample buffer passed to that method.
 */
- (void)pauseRecording __IOS_PROHIBITED __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
 @method resumeRecording
 @abstract
    Resumes recording to the current output file after it was previously paused using pauseRecording.
 
 @discussion
    This method causes the receiver to resume writing captured samples to the current output file returned by outputFileURL, after recording was previously paused using pauseRecording. This allows clients to record multiple media segments that are not contiguous in time to a single file.
 
    On Mac OS X, if this method is called within the captureOutput:didOutputSampleBuffer:fromConnection: delegate method, the first samples written to the current file are guaranteed to be those contained in the sample buffer passed to that method.
 */
- (void)resumeRecording __IOS_PROHIBITED __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*!
 @property recordedDuration
 @abstract
    Indicates the duration of the media recorded to the current output file.
 
 @discussion
    If recording is in progress, this property returns the total time recorded so far.
 */
@property(nonatomic, readonly) CMTime recordedDuration;

/*!
 @property recordedFileSize
 @abstract
    Indicates the size, in bytes, of the data recorded to the current output file.
 
 @discussion
    If a recording is in progress, this property returns the size in bytes of the data recorded so far.
 */
@property(nonatomic, readonly) int64_t recordedFileSize;

/*!
 @property maxRecordedDuration
 @abstract
    Specifies the maximum duration of the media that should be recorded by the receiver.
 
 @discussion
    This property specifies a hard limit on the duration of recorded files. Recording is stopped when the limit is reached and the captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: delegate method is invoked with an appropriate error. The default value of this property is kCMTimeInvalid, which indicates no limit.
 */
@property(nonatomic) CMTime maxRecordedDuration;

/*!
 @property maxRecordedFileSize
 @abstract
    Specifies the maximum size, in bytes, of the data that should be recorded by the receiver.
 
 @discussion
    This property specifies a hard limit on the data size of recorded files. Recording is stopped when the limit is reached and the captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: delegate method is invoked with an appropriate error. The default value of this property is 0, which indicates no limit.
 */
@property(nonatomic) int64_t maxRecordedFileSize;

/*!
 @property minFreeDiskSpaceLimit
 @abstract
    Specifies the minimum amount of free space, in bytes, required for recording to continue on a given volume.
 
 @discussion
    This property specifies a hard lower limit on the amount of free space that must remain on a target volume for recording to continue. Recording is stopped when the limit is reached and the captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: delegate method is invoked with an appropriate error.
 */
@property(nonatomic) int64_t minFreeDiskSpaceLimit;

@end


/*!
 @protocol AVCaptureFileOutputRecordingDelegate
 @abstract
    Defines an interface for delegates of AVCaptureFileOutput to respond to events that occur in the process of recording a single file.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@protocol AVCaptureFileOutputRecordingDelegate <NSObject>

@optional

/*!
 @method captureOutput:didStartRecordingToOutputFileAtURL:fromConnections:
 @abstract
    Informs the delegate when the output has started writing to a file.
 
 @param output
    The capture file output that started writing the file.
 @param fileURL
    The file URL of the file that is being written.
 @param connections
    An array of AVCaptureConnection objects attached to the file output that provided the data that is being written to the file.
 
 @discussion
    This method is called when the file output has started writing data to a file. If an error condition prevents any data from being written, this method may not be called. captureOutput:willFinishRecordingToOutputFileAtURL:fromConnections:error: and captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: will always be called, even if no data is written.
 
    Clients should not assume that this method will be called on a specific thread, and should also try to make this method as efficient as possible.
 */
- (void)captureOutput:(AVCaptureFileOutput *)output didStartRecordingToOutputFileAtURL:(NSURL *)fileURL fromConnections:(NSArray<AVCaptureConnection *> *)connections;

/*!
 @method captureOutput:didPauseRecordingToOutputFileAtURL:fromConnections:
 @abstract
    Called whenever the output is recording to a file and successfully pauses the recording at the request of the client.
 
 @param output
    The capture file output that has paused its file recording.
 @param fileURL
    The file URL of the file that is being written.
 @param connections
    An array of AVCaptureConnection objects attached to the file output that provided the data that is being written to the file.
 
 @discussion
    Delegates can use this method to be informed when a request to pause recording is actually respected. It is safe for delegates to change what the file output is currently doing (starting a new file, for example) from within this method. If recording to a file is stopped, either manually or due to an error, this method is not guaranteed to be called, even if a previous call to pauseRecording was made.
 
    Clients should not assume that this method will be called on a specific thread, and should also try to make this method as efficient as possible.
 */
- (void)captureOutput:(AVCaptureFileOutput *)output didPauseRecordingToOutputFileAtURL:(NSURL *)fileURL fromConnections:(NSArray<AVCaptureConnection *> *)connections API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

/*!
 @method captureOutput:didResumeRecordingToOutputFileAtURL:fromConnections:
 @abstract
    Called whenever the output, at the request of the client, successfully resumes a file recording that was paused.
 
 @param output
    The capture file output that has resumed its paused file recording.
 @param fileURL
    The file URL of the file that is being written.
 @param connections
    An array of AVCaptureConnection objects attached to the file output that provided the data that is being written to the file.
 
 @discussion
    Delegates can use this method to be informed when a request to resume recording is actually respected. It is safe for delegates to change what the file output is currently doing (starting a new file, for example) from within this method. If recording to a file is stopped, either manually or due to an error, this method is not guaranteed to be called, even if a previous call to resumeRecording was made.
 
    Clients should not assume that this method will be called on a specific thread, and should also try to make this method as efficient as possible.
 */
- (void)captureOutput:(AVCaptureFileOutput *)output didResumeRecordingToOutputFileAtURL:(NSURL *)fileURL fromConnections:(NSArray<AVCaptureConnection *> *)connections API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

/*!
 @method captureOutput:willFinishRecordingToOutputFileAtURL:fromConnections:error:
 @abstract
    Informs the delegate when the output will stop writing new samples to a file.
 
 @param output
    The capture file output that will finish writing the file.
 @param fileURL
    The file URL of the file that is being written.
 @param connections
    An array of AVCaptureConnection objects attached to the file output that provided the data that is being written to the file.
 @param error
    An error describing what caused the file to stop recording, or nil if there was no error.
 
 @discussion
    This method is called when the file output will stop recording new samples to the file at outputFileURL, either because startRecordingToOutputFileURL:recordingDelegate: or stopRecording were called, or because an error, described by the error parameter, occurred (if no error occurred, the error parameter will be nil). This method will always be called for each recording request, even if no data is successfully written to the file.
 
    Clients should not assume that this method will be called on a specific thread, and should also try to make this method as efficient as possible.
 */
- (void)captureOutput:(AVCaptureFileOutput *)output willFinishRecordingToOutputFileAtURL:(NSURL *)fileURL fromConnections:(NSArray<AVCaptureConnection *> *)connections error:(nullable NSError *)error API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

@required

/*!
 @method captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error:
 @abstract
    Informs the delegate when all pending data has been written to an output file.
 
 @param output
    The capture file output that has finished writing the file.
 @param outputFileURL
    The file URL of the file that has been written.
 @param connections
    An array of AVCaptureConnection objects attached to the file output that provided the data that was written to the file.
 @param error
    An error describing what caused the file to stop recording, or nil if there was no error.
 
 @discussion
    This method is called when the file output has finished writing all data to a file whose recording was stopped, either because startRecordingToOutputFileURL:recordingDelegate: or stopRecording were called, or because an error, described by the error parameter, occurred (if no error occurred, the error parameter will be nil). This method will always be called for each recording request, even if no data is successfully written to the file.
 
    Clients should not assume that this method will be called on a specific thread.
 
    Delegates are required to implement this method.
 */
- (void)captureOutput:(AVCaptureFileOutput *)output didFinishRecordingToOutputFileAtURL:(NSURL *)outputFileURL fromConnections:(NSArray<AVCaptureConnection *> *)connections error:(nullable NSError *)error;

@end


/*!
 @protocol AVCaptureFileOutputDelegate
 @abstract
    Defines an interface for delegates of AVCaptureFileOutput to monitor and control recordings along exact sample boundaries.
 */
API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, macCatalyst, watchos, tvos)
@protocol AVCaptureFileOutputDelegate <NSObject>

@required

/*!
 @method captureOutputShouldProvideSampleAccurateRecordingStart:
 @abstract
    Allows a client to opt in to frame accurate record-start in captureOutput:didOutputSampleBuffer:fromConnection:
 
 @param output
    The AVCaptureFileOutput instance with which the delegate is associated.
 
 @discussion
    In apps linked before Mac OS X 10.8, delegates that implement the captureOutput:didOutputSampleBuffer:fromConnection: method can ensure frame accurate start / stop of a recording by calling startRecordingToOutputFileURL:recordingDelegate: from within the callback. Frame accurate start requires the capture output to apply outputSettings when the session starts running, so it is ready to record on any given frame boundary. Compressing all the time while the session is running has power, thermal, and CPU implications. In apps linked on or after Mac OS X 10.8, delegates must implement captureOutputShouldProvideSampleAccurateRecordingStart: to indicate whether frame accurate start/stop recording is required (returning YES) or not (returning NO). The output calls this method as soon as the delegate is added, and never again. If your delegate returns NO, the capture output applies compression settings when startRecordingToOutputFileURL:recordingDelegate: is called, and disables compression settings after the recording is stopped.
 */
- (BOOL)captureOutputShouldProvideSampleAccurateRecordingStart:(AVCaptureOutput *)output API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, macCatalyst, watchos, tvos);

@optional

/*!
 @method captureOutput:didOutputSampleBuffer:fromConnection:
 @abstract
    Gives the delegate the opportunity to inspect samples as they are received by the output and optionally start and stop recording at exact times.
 
 @param output
    The capture file output that is receiving the media data.
 @param sampleBuffer
    A CMSampleBuffer object containing the sample data and additional information about the sample, such as its format and presentation time.
 @param connection
    The AVCaptureConnection object attached to the file output from which the sample data was received.
 
 @discussion
    This method is called whenever the file output receives a single sample buffer (a single video frame or audio buffer, for example) from the given connection. This gives delegates an opportunity to start and stop recording or change output files at an exact sample boundary if -captureOutputShouldProvideSampleAccurateRecordingStart: returns YES. If called from within this method, the file output's startRecordingToOutputFileURL:recordingDelegate: and resumeRecording methods are guaranteed to include the received sample buffer in the new file, whereas calls to stopRecording and pauseRecording are guaranteed to include all samples leading up to those in the current sample buffer in the existing file.
 
    Delegates can gather information particular to the samples by inspecting the CMSampleBuffer object. Sample buffers always contain a single frame of video if called from this method but may also contain multiple samples of audio. For B-frame video formats, samples are always delivered in presentation order.
 
    Clients that need to reference the CMSampleBuffer object outside of the scope of this method must CFRetain it and then CFRelease it when they are finished with it.
 
    Note that to maintain optimal performance, some sample buffers directly reference pools of memory that may need to be reused by the device system and other capture inputs. This is frequently the case for uncompressed device native capture where memory blocks are copied as little as possible. If multiple sample buffers reference such pools of memory for too long, inputs will no longer be able to copy new samples into memory and those samples will be dropped. If your application is causing samples to be dropped by retaining the provided CMSampleBuffer objects for too long, but it needs access to the sample data for a long period of time, consider copying the data into a new buffer and then calling CFRelease on the sample buffer if it was previously retained so that the memory it references can be reused.
 
    Clients should not assume that this method will be called on a specific thread. In addition, this method is called periodically, so it must be efficient to prevent capture performance problems.
 */
- (void)captureOutput:(AVCaptureFileOutput *)output didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection;

@end


#pragma mark - AVCaptureMovieFileOutput

@class AVCaptureMovieFileOutputInternal;

/*!
 @class AVCaptureMovieFileOutput
 @abstract
    AVCaptureMovieFileOutput is a concrete subclass of AVCaptureFileOutput that writes captured media to QuickTime movie files.
 
 @discussion
    AVCaptureMovieFileOutput implements the complete file recording interface declared by AVCaptureFileOutput for writing media data to QuickTime movie files. In addition, instances of AVCaptureMovieFileOutput allow clients to configure options specific to the QuickTime file format, including allowing them to write metadata collections to each file, specify media encoding options for each track (Mac OS X), and specify an interval at which movie fragments should be written.
 */
API_AVAILABLE(macos(10.7), ios(4.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos) __WATCHOS_PROHIBITED
@interface AVCaptureMovieFileOutput : AVCaptureFileOutput
{
@private
    AVCaptureMovieFileOutputInternal *_internal;
}

- (instancetype)init;

+ (instancetype)new;

/*!
 @property movieFragmentInterval
 @abstract
    Specifies the frequency with which movie fragments should be written.
 
 @discussion
    When movie fragments are used, a partially written QuickTime movie file whose writing is unexpectedly interrupted can be successfully opened and played up to multiples of the specified time interval. A value of kCMTimeInvalid indicates that movie fragments should not be used, but that only a movie atom describing all of the media in the file should be written. The default value of this property is ten seconds.
 
    Changing the value of this property will not affect the movie fragment interval of the file currently being written, if there is one.
 */
@property(nonatomic) CMTime movieFragmentInterval;

/*!
 @property metadata
 @abstract
    A collection of metadata to be written to the receiver's output files.
 
 @discussion
    The value of this property is an array of AVMetadataItem objects representing the collection of top-level metadata to be written in each output file.
 */
@property(nonatomic, copy, nullable) NSArray<AVMetadataItem *> *metadata;

/*!
 @property availableVideoCodecTypes
 @abstract
    Indicates the supported video codec formats that can be specified in setOutputSettingsForConnection:.
 
 @discussion
    The value of this property is an NSArray of AVVideoCodecTypes that can be used as values for the AVVideoCodecKey in the receiver's setOutputSettingsForConnection: dictionary. The array of available video codecs may change depending on the current session preset. The first codec in the array is used by default when recording a file.
 */
@property(nonatomic, readonly) NSArray<AVVideoCodecType> *availableVideoCodecTypes API_AVAILABLE(ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @method supportedOutputSettingsKeysForConnection:
 @abstract
    Indicates the supported keys that can be specified in setOutputSettings:forConnection:.
 
 @param connection
    The connection delivering the media to be encoded.
 
 @discussion
    Returns an NSArray of NSStrings listing the allowable keys in the receiver's setOutputSettings:forConnection: dictionary.
 */
- (NSArray<NSString *> *)supportedOutputSettingsKeysForConnection:(AVCaptureConnection *)connection API_AVAILABLE(ios(12.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos) API_UNAVAILABLE(watchos);

/*!
 @method outputSettingsForConnection:
 @abstract
    Returns the options the receiver uses to encode media from the given connection as it is being recorded.
 
 @param connection
    The connection delivering the media to be encoded.
 @result
    An NSDictionary of output settings.
 
 @discussion
    See AVAudioSettings.h for audio connections or AVVideoSettings.h for video connections for more information on the structure of an output settings dictionary. If the returned value is an empty dictionary (i.e. [NSDictionary dictionary], the format of the media from the connection will not be changed before being written to the file. If -setOutputSettings:forConnection: was called with a nil dictionary, this method returns a non-nil dictionary reflecting the settings used by the AVCaptureSession's current sessionPreset.
 */
- (NSDictionary<NSString *, id> *)outputSettingsForConnection:(AVCaptureConnection *)connection API_AVAILABLE(ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @method setOutputSettings:forConnection:
 @abstract
    Sets the options the receiver uses to encode media from the given connection as it is being recorded.
 
 @param outputSettings
    An NSDictionary of output settings.
 @param connection
    The connection delivering the media to be encoded.
 
 @discussion
    See AVAudioSettings.h for audio connections or AVVideoSettings.h for video connections for more information on how to construct an output settings dictionary. A value of an empty dictionary (i.e. [NSDictionary dictionary], means that the format of the media from the connection should not be changed before being written to the file. A value of nil means that the output format will be determined by the session preset. In this case, -outputSettingsForConnection: will return a non-nil dictionary reflecting the settings used by the AVCaptureSession's current sessionPreset.
 
    On iOS, your outputSettings dictionary may only contain keys listed in - supportedOutputSettingsKeysForConnection:. If you specify any other key, an NSInvalidArgumentException will be thrown. Further restrictions may be imposed on the AVVideoCodecTypeKey. Its value should be present in the -availableVideoCodecTypes array. If AVVideoCompressionPropertiesKey is specified, you must also specify a valid value for AVVideoCodecKey. On iOS versions prior to 12.0, the only settable key for video connections is AVVideoCodecTypeKey. On iOS 12.0 and later, video connections gain support for AVVideoCompressionPropertiesKey.
 
    On iOS, -outputSettingsForConnection: always provides a fully populated dictionary. If you call -outputSettingsForConnection: with the intent of overriding a few of the values, you must take care to exclude keys that are not supported before calling -setOutputSettings:forConnection:. When providing an AVVideoCompressionPropertiesKey sub dictionary, you may specify a sparse dictionary. AVCaptureMovieFileOutput will always fill in missing keys with default values for the current AVCaptureSession configuration.
 */
- (void)setOutputSettings:(nullable NSDictionary<NSString *, id> *)outputSettings forConnection:(AVCaptureConnection *)connection API_AVAILABLE(ios(10.0), macCatalyst(14.0)) API_UNAVAILABLE(tvos);

/*!
 @method recordsVideoOrientationAndMirroringChangesAsMetadataTrackForConnection:
 @abstract
    Returns YES if the movie file output will create a timed metadata track that records samples which reflect changes made to the given connection's videoOrientation and videoMirrored properties during recording.
 
 @param connection
    A connection delivering video media to the movie file output. This method throws an NSInvalidArgumentException if the connection does not have a mediaType of AVMediaTypeVideo or if the connection does not terminate at the movie file output.
 
 @discussion
    See setRecordsVideoOrientationAndMirroringChanges:asMetadataTrackForConnection: for details on the behavior controlled by this value. The default value returned is NO.
 */
- (BOOL)recordsVideoOrientationAndMirroringChangesAsMetadataTrackForConnection:(AVCaptureConnection *)connection API_AVAILABLE(ios(9.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @method setRecordsVideoOrientationAndMirroringChanges:asMetadataTrackForConnection:
 @abstract
    Controls whether or not the movie file output will create a timed metadata track that records samples which reflect changes made to the given connection's videoOrientation and videoMirrored properties during recording.
 
 @param doRecordChanges
    If YES, the movie file output will create a timed metadata track that records samples which reflect changes made to the given connection's videoOrientation and videoMirrored properties during recording.
 @param connection
    A connection delivering video media to the movie file output. This method throws an NSInvalidArgumentException if the connection does not have a mediaType of AVMediaTypeVideo or if the connection does not terminate at the movie file output.
 
 @discussion
    When a recording is started the current state of a video capture connection's videoOrientation and videoMirrored properties are used to build the display matrix for the created video track. The movie file format allows only one display matrix per track, which means that any changes made during a recording to the videoOrientation and videoMirrored properties are not captured. For example, a user starts a recording with their device in the portrait orientation, and then partway through the recording changes the device to a landscape orientation. The landscape orientation requires a different display matrix, but only the initial display matrix (the portrait display matrix) is recorded for the video track.
 
    By invoking this method the client application directs the movie file output to create an additional track in the captured movie. This track is a timed metadata track that is associated with the video track, and contains one or more samples that contain a Video Orientation value (as defined by EXIF and TIFF specifications, which is enumerated by CGImagePropertyOrientation in <ImageIO/CGImageProperties.h>). The value represents the display matrix corresponding to the AVCaptureConnection's videoOrientation and videoMirrored properties when applied to the input source. The initial sample written to the timed metadata track represents video track's display matrix. During recording additional samples will be written to the timed metadata track whenever the client application changes the video connection's videoOrienation or videoMirrored properties. Using the above example, when the client application detects the user changing the device from portrait to landscape orientation, it updates the video connection's videoOrientation property, thus causing the movie file output to add a new sample to the timed metadata track.
 
    After capture, playback and editing applications can use the timed metadata track to enhance their user's experience. For example, when playing back the captured movie, a playback engine can use the samples to adjust the display of the video samples to keep the video properly oriented. Another example is an editing application that uses the sample the sample times to suggest cut points for breaking the captured movie into separate clips, where each clip is properly oriented.
 
    The default behavior is to not create the timed metadata track.
 
    The doRecordChanges value is only observed at the start of recording. Changes to the value will not have any effect until the next recording is started.
 */
- (void)setRecordsVideoOrientationAndMirroringChanges:(BOOL)doRecordChanges asMetadataTrackForConnection:(AVCaptureConnection *)connection API_AVAILABLE(ios(9.0), macCatalyst(14.0)) API_UNAVAILABLE(macos, tvos);

/*!
 @property primaryConstituentDeviceSwitchingBehaviorForRecordingEnabled
 @abstract
    Enable or disable a constituent device selection behavior when recording.
 
 @discussion
    This property enables a camera selection behavior to be applied when recording a movie. Once recording starts, the specified behavior and conditions take effect. Once recording stops the camera selection will change back to the primaryConstituentDeviceSwitchingBehavior specified by the AVCaptureDevice. By default, this property is set to YES when connected to an AVCaptureDevice that supports constituent device switching.
 */
@property(nonatomic, getter=isPrimaryConstituentDeviceSwitchingBehaviorForRecordingEnabled) BOOL primaryConstituentDeviceSwitchingBehaviorForRecordingEnabled API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @method setPrimaryConstituentDeviceSwitchingBehaviorForRecording:restrictedSwitchingBehaviorConditions:
 @abstract
    When primaryConstituentDeviceSwitchingBehaviorForRecordingEnabled is set to YES, this method controls the switching behavior and conditions, while a movie file is being recorded.
 
 @discussion
    This controls the camera selection behavior used while recording a movie, when enabled through primaryConstituentDeviceSwitchingBehaviorForRecordingEnabled. Setting the switching behavior to anything other than AVCapturePrimaryConstituentDeviceSwitchingBehaviorUnsupported when connected to an AVCaptureDevice that does not suport constituent device selection throws an NSInvalidArgumentException. Setting restrictedSwitchingBehaviorConditions to something other than AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditionNone while setting switchingBehavior to something other than AVCapturePrimaryConstituentDeviceSwitchingBehaviorRestricted throws an NSInvalidArgumentException exception.
 */
- (void)setPrimaryConstituentDeviceSwitchingBehaviorForRecording:(AVCapturePrimaryConstituentDeviceSwitchingBehavior)switchingBehavior restrictedSwitchingBehaviorConditions:(AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions)restrictedSwitchingBehaviorConditions API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property primaryConstituentDeviceSwitchingBehaviorForRecording
 @abstract
    The primaryConstituentDeviceSwitchingBehavior as set by -[AVCaptureMovieFileOutput setPrimaryConstituentDeviceSwitchingBehaviorForRecording:restrictedSwitchingBehaviorConditions:].
 
 @discussion
    By default, this property is set to AVCapturePrimaryConstituentDeviceSwitchingBehaviorRestricted. This property is key-value observable.
 */
@property(nonatomic, readonly) AVCapturePrimaryConstituentDeviceSwitchingBehavior primaryConstituentDeviceSwitchingBehaviorForRecording API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

/*!
 @property primaryConstituentDeviceRestrictedSwitchingBehaviorConditionsForRecording
 @abstract
    The primaryConstituentDeviceRestrictedSwitchingBehaviorConditions as set by -[AVCaptureMovieFileOutput setPrimaryConstituentDeviceSwitchingBehaviorForRecording:restrictedSwitchingBehaviorConditions:].
 
 @discussion
    By default, this property is set to AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorCondition{VideoZoomChanged | FocusModeChanged | ExposureModeChanged}. This property is key-value observable.
 */
@property(nonatomic, readonly) AVCapturePrimaryConstituentDeviceRestrictedSwitchingBehaviorConditions primaryConstituentDeviceRestrictedSwitchingBehaviorConditionsForRecording API_AVAILABLE(macos(12.0), ios(15.0), macCatalyst(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

@end


#pragma mark - AVCaptureAudioFileOutput

@class AVCaptureAudioFileOutputInternal;

/*!
 @class AVCaptureAudioFileOutput
 @abstract
    AVCaptureAudioFileOutput is a concrete subclass of AVCaptureFileOutput that writes captured audio to any audio file type supported by CoreAudio.
 
 @discussion
    AVCaptureAudioFileOutput implements the complete file recording interface declared by AVCaptureFileOutput for writing media data to audio files. In addition, instances of AVCaptureAudioFileOutput allow clients to configure options specific to the audio file formats, including allowing them to write metadata collections to each file and specify audio encoding options.
 */
API_AVAILABLE(macos(10.7)) API_UNAVAILABLE(ios, macCatalyst, watchos, tvos)
@interface AVCaptureAudioFileOutput : AVCaptureFileOutput
{
@private
    AVCaptureAudioFileOutputInternal *_internal;
}

- (instancetype)init;

+ (instancetype)new;

/*!
 @method availableOutputFileTypes
 @abstract
    Provides the file types AVCaptureAudioFileOutput can write.
 
 @result
    An NSArray of UTIs identifying the file types the AVCaptureAudioFileOutput class can write.
 */
+ (NSArray<AVFileType> *)availableOutputFileTypes;

/*!
 @method startRecordingToOutputFileURL:outputFileType:recordingDelegate:
 @abstract
    Tells the receiver to start recording to a new file of the specified format, and specifies a delegate that will be notified when recording is finished.
 
 @param outputFileURL
    An NSURL object containing the URL of the output file. This method throws an NSInvalidArgumentException if the URL is not a valid file URL.
 @param fileType
    A UTI indicating the format of the file to be written.
 @param delegate
    An object conforming to the AVCaptureFileOutputRecordingDelegate protocol. Clients must specify a delegate so that they can be notified when recording to the given URL is finished.
 
 @discussion
    The method sets the file URL to which the receiver is currently writing output media. If a file at the given URL already exists when capturing starts, recording to the new file will fail.
 
    The fileType argument is a UTI corresponding to the audio file format that should be written. UTIs for common audio file types are declared in AVMediaFormat.h.
 
    Clients need not call stopRecording before calling this method while another recording is in progress. If this method is invoked while an existing output file was already being recorded, no media samples will be discarded between the old file and the new file.
 
    When recording is stopped either by calling stopRecording, by changing files using this method, or because of an error, the remaining data that needs to be included to the file will be written in the background. Therefore, clients must specify a delegate that will be notified when all data has been written to the file using the captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: method. The recording delegate can also optionally implement methods that inform it when data starts being written, when recording is paused and resumed, and when recording is about to be finished.
 
    On Mac OS X, if this method is called within the captureOutput:didOutputSampleBuffer:fromConnection: delegate method, the first samples written to the new file are guaranteed to be those contained in the sample buffer passed to that method.
 */
- (void)startRecordingToOutputFileURL:(NSURL *)outputFileURL outputFileType:(AVFileType)fileType recordingDelegate:(id<AVCaptureFileOutputRecordingDelegate>)delegate;

/*!
 @property metadata
 @abstract
    A collection of metadata to be written to the receiver's output files.
 
 @discussion
    The value of this property is an array of AVMetadataItem objects representing the collection of top-level metadata to be written in each output file. Only ID3 v2.2, v2.3, or v2.4 style metadata items are supported.
 */
@property(nonatomic, copy) NSArray<AVMetadataItem *> *metadata;

/*!
 @property audioSettings
 @abstract
    Specifies the options the receiver uses to re-encode audio as it is being recorded.
 
 @discussion
    The output settings dictionary can contain values for keys from AVAudioSettings.h. A value of nil indicates that the format of the audio should not be changed before being written to the file.
 */
@property(nonatomic, copy, nullable) NSDictionary<NSString *, id> *audioSettings;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVCaptureFileOutput.h>
#endif

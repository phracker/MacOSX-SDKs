/*
    File:  AVCaptureOutput.h
 	
 	Framework:  AVFoundation
 
	Copyright 2010-2012 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVCaptureSession.h>
#import <CoreMedia/CMSampleBuffer.h>
#import <QuartzCore/CALayer.h>
#import <dispatch/dispatch.h>

@class AVCaptureOutputInternal;

/*!
 @class AVCaptureOutput
 @abstract
    AVCaptureOutput is an abstract class that defines an interface for an output destination of an AVCaptureSession.
 
 @discussion
    AVCaptureOutput provides an abstract interface for connecting capture output destinations, such as files and video
    previews, to an AVCaptureSession.

    An AVCaptureOutput can have multiple connections represented by AVCaptureConnection objects, one for each stream of
    media that it receives from an AVCaptureInput. An AVCaptureOutput does not have any connections when it is first
    created. When an output is added to an AVCaptureSession, connections are created that map media data from that
    session's inputs to its outputs.

    Concrete AVCaptureOutput instances can be added to an AVCaptureSession using the -[AVCaptureSession addOutput:] and
    -[AVCaptureSession addOutputWithNoConnections:] methods.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCaptureOutput : NSObject
{
@private
    AVCaptureOutputInternal *_outputInternal;
}

/*!
 @property connections
 @abstract
    The connections that describe the flow of media data to the receiver from AVCaptureInputs.

 @discussion
    The value of this property is an NSArray of AVCaptureConnection objects, each describing the mapping between the
    receiver and the AVCaptureInputPorts of one or more AVCaptureInputs.
*/
@property(nonatomic, readonly) NSArray *connections;

/*!
 @property connectionWithMediaType:
 @abstract
    Returns the first connection in the connections array with an inputPort of the specified mediaType.

 @param mediaType
    An AVMediaType constant from AVMediaFormat.h, e.g. AVMediaTypeVideo.

 @discussion
    This convenience method returns the first AVCaptureConnection in the receiver's
    connections array that has an AVCaptureInputPort of the specified mediaType.  If no
    connection with the specified mediaType is found, nil is returned.
*/
- (AVCaptureConnection *)connectionWithMediaType:(NSString *)mediaType NS_AVAILABLE(10_7, 5_0);

@end


@class AVCaptureVideoDataOutputInternal;
@protocol AVCaptureVideoDataOutputSampleBufferDelegate;

/*!
 @class AVCaptureVideoDataOutput
 @abstract
    AVCaptureVideoDataOutput is a concrete subclass of AVCaptureOutput that can be used to process uncompressed or
    compressed frames from the video being captured.

 @discussion
    Instances of AVCaptureVideoDataOutput produce video frames suitable for processing using other media APIs.
    Applications can access the frames with the captureOutput:didOutputSampleBuffer:fromConnection: delegate method.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCaptureVideoDataOutput : AVCaptureOutput 
{
@private
	AVCaptureVideoDataOutputInternal *_internal;
}

/*!
 @method setSampleBufferDelegate:queue:
 @abstract
    Sets the receiver's delegate that will accept captured buffers and dispatch queue on which the delegate will be
    called.

 @param sampleBufferDelegate
    An object conforming to the AVCaptureVideoDataOutputSampleBufferDelegate protocol that will receive sample buffers
    after they are captured.
 @param sampleBufferCallbackQueue
    A dispatch queue on which all sample buffer delegate methods will be called.

 @discussion
    When a new video sample buffer is captured it will be vended to the sample buffer delegate using the
    captureOutput:didOutputSampleBuffer:fromConnection: delegate method. All delegate methods will be called on the
    specified dispatch queue. If the queue is blocked when new frames are captured, those frames will be automatically
    dropped at a time determined by the value of the alwaysDiscardsLateVideoFrames property. This allows clients to
    process existing frames on the same queue without having to manage the potential memory usage increases that would
    otherwise occur when that processing is unable to keep up with the rate of incoming frames. If their frame processing
    is consistently unable to keep up with the rate of incoming frames, clients should consider using the
    minFrameDuration property, which will generally yield better performance characteristics and more consistent frame
    rates than frame dropping alone.

    Clients that need to minimize the chances of frames being dropped should specify a queue on which a sufficiently
    small amount of processing is being done outside of receiving sample buffers. However, if such clients migrate extra
    processing to another queue, they are responsible for ensuring that memory usage does not grow without bound from
    frames that have not been processed.

    A serial dispatch queue must be used to guarantee that video frames will be delivered in order.
    The sampleBufferCallbackQueue parameter may not be NULL, except when setting the sampleBufferDelegate
    to nil.
*/
- (void)setSampleBufferDelegate:(id<AVCaptureVideoDataOutputSampleBufferDelegate>)sampleBufferDelegate queue:(dispatch_queue_t)sampleBufferCallbackQueue;

/*!
 @property sampleBufferDelegate
 @abstract
    The receiver's delegate.

 @discussion
    The value of this property is an object conforming to the AVCaptureVideoDataOutputSampleBufferDelegate protocol that
    will receive sample buffers after they are captured. The delegate is set using the setSampleBufferDelegate:queue:
    method.
*/
@property(nonatomic, readonly) id<AVCaptureVideoDataOutputSampleBufferDelegate> sampleBufferDelegate;

/*!
 @property sampleBufferCallbackQueue
 @abstract
    The dispatch queue on which all sample buffer delegate methods will be called.

 @discussion
    The value of this property is a dispatch_queue_t. The queue is set using the setSampleBufferDelegate:queue: method.
*/
@property(nonatomic, readonly) dispatch_queue_t sampleBufferCallbackQueue;

/*!
 @property videoSettings
 @abstract
    Specifies the settings used to decode or re-encode video before it is output by the receiver.

 @discussion
    See AVVideoSettings.h for more information on how to construct a video settings dictionary.  To receive samples in their 
    device native format, set this property to an empty dictionary (i.e. [NSDictionary dictionary]).  To receive samples in
    a default uncompressed format, set this property to nil.  Note that after this property is set to nil, subsequent
    querying of this property will yield a non-nil dictionary reflecting the settings used by the AVCaptureSession's current 
    sessionPreset.
*/
@property(nonatomic, copy) NSDictionary *videoSettings;

/*!
 @property availableVideoCVPixelFormatTypes
 @abstract
    Indicates the supported video pixel formats that can be specified in videoSettings.

 @discussion
    The value of this property is an NSArray of NSNumbers that can be used as values for the 
    kCVPixelBufferPixelFormatTypeKey in the receiver's videoSettings property.  The first
    format in the returned list is the most efficient output format.
*/
@property(nonatomic, readonly) NSArray *availableVideoCVPixelFormatTypes NS_AVAILABLE(10_7, 5_0);

/*!
 @property availableVideoCodecTypes
 @abstract
    Indicates the supported video codec formats that can be specified in videoSettings.

 @discussion
    The value of this property is an NSArray of NSStrings that can be used as values for the 
    AVVideoCodecKey in the receiver's videoSettings property.
*/
@property(nonatomic, readonly) NSArray *availableVideoCodecTypes NS_AVAILABLE(10_7, 5_0);

/*!
 @property minFrameDuration
 @abstract
    Specifies the minimum time interval between which the receiver should output consecutive video frames.

 @discussion
    The value of this property is a CMTime specifying the minimum duration of each video frame output by the receiver,
    placing a lower bound on the amount of time that should separate consecutive frames. This is equivalent to the
    inverse of the maximum frame rate. A value of kCMTimeZero or kCMTimeInvalid indicates an unlimited maximum frame
    rate. The default value is kCMTimeInvalid.  As of iOS 5.0, minFrameDuration is deprecated.  Use AVCaptureConnection's
    videoMinFrameDuration property instead.
*/
@property(nonatomic) CMTime minFrameDuration NS_DEPRECATED_IOS(4_0, 5_0);

/*!
 @property alwaysDiscardsLateVideoFrames
 @abstract
    Specifies whether the receiver should always discard any video frame that is not processed before the next frame is
    captured.

 @discussion
    When the value of this property is YES, the receiver will immediately discard frames that are captured while the
    dispatch queue handling existing frames is blocked in the captureOutput:didOutputSampleBuffer:fromConnection:
    delegate method. When the value of this property is NO, delegates will be allowed more time to process old frames
    before new frames are discarded, but application memory usage may increase significantly as a result. The default
    value is YES.
*/
@property(nonatomic) BOOL alwaysDiscardsLateVideoFrames;

@end

/*!
 @protocol AVCaptureVideoDataOutputSampleBufferDelegate
 @abstract
    Defines an interface for delegates of AVCaptureVideoDataOutput to receive captured video sample buffers and be
    notified of late sample buffers that were dropped.
*/
@protocol AVCaptureVideoDataOutputSampleBufferDelegate <NSObject>

@optional

/*!
 @method captureOutput:didOutputSampleBuffer:fromConnection:
 @abstract
    Called whenever an AVCaptureVideoDataOutput instance outputs a new video frame.

 @param captureOutput
    The AVCaptureVideoDataOutput instance that output the frame.
 @param sampleBuffer
    A CMSampleBuffer object containing the video frame data and additional information about the frame, such as its
    format and presentation time.
 @param connection
    The AVCaptureConnection from which the video was received.

 @discussion
    Delegates receive this message whenever the output captures and outputs a new video frame, decoding or re-encoding it
    as specified by its videoSettings property. Delegates can use the provided video frame in conjunction with other APIs
    for further processing. This method will be called on the dispatch queue specified by the output's
    sampleBufferCallbackQueue property. This method is called periodically, so it must be efficient to prevent capture
    performance problems, including dropped frames.

    Clients that need to reference the CMSampleBuffer object outside of the scope of this method must CFRetain it and
    then CFRelease it when they are finished with it.

    Note that to maintain optimal performance, some sample buffers directly reference pools of memory that may need to be
    reused by the device system and other capture inputs. This is frequently the case for uncompressed device native
    capture where memory blocks are copied as little as possible. If multiple sample buffers reference such pools of
    memory for too long, inputs will no longer be able to copy new samples into memory and those samples will be dropped.
    If your application is causing samples to be dropped by retaining the provided CMSampleBuffer objects for too long,
    but it needs access to the sample data for a long period of time, consider copying the data into a new buffer and
    then calling CFRelease on the sample buffer if it was previously retained so that the memory it references can be
    reused.
*/
- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/*!
 @method captureOutput:didDropSampleBuffer:fromConnection:
 @abstract
    Called once for each frame that is discarded.

 @param captureOutput
    The AVCaptureVideoDataOutput instance that dropped the frame.
 @param sampleBuffer
    A CMSampleBuffer object containing information about the dropped frame, such as its format and presentation time.
    This sample buffer will contain none of the original video data.
 @param connection
    The AVCaptureConnection from which the dropped video frame was received.

 @discussion
    Delegates receive this message whenever a late video frame is dropped. This method is called once 
    for each dropped frame. The CMSampleBuffer object passed to this delegate method will contain metadata 
    about the dropped video frame, such as its duration and presentation time stamp, but will contain no 
    actual video data. This method will be called on the dispatch queue specified by the output's
    sampleBufferCallbackQueue property. Because this method will be called on the same dispatch queue that is responsible
    for outputting video frames, it must be efficient to prevent further capture performance problems, such as additional
    dropped video frames.
*/
- (void)captureOutput:(AVCaptureOutput *)captureOutput didDropSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection NS_AVAILABLE(10_7, NA);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@end


@class AVCaptureAudioDataOutputInternal;
@protocol AVCaptureAudioDataOutputSampleBufferDelegate;

/*!
 @class AVCaptureAudioDataOutput
 @abstract
    AVCaptureAudioDataOutput is a concrete subclass of AVCaptureOutput that can be used to process uncompressed or
    compressed samples from the audio being captured.
 
 @discussion
    Instances of AVCaptureAudioDataOutput produce audio sample buffers suitable for processing using other media APIs.
    Applications can access the sample buffers with the captureOutput:didOutputSampleBuffer:fromConnection: delegate
    method.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCaptureAudioDataOutput : AVCaptureOutput 
{
@private
	AVCaptureAudioDataOutputInternal *_internal;
}

/*!
 @method setSampleBufferDelegate:queue:
 @abstract
    Sets the receiver's delegate that will accept captured buffers and dispatch queue on which the delegate will be
    called.

 @param sampleBufferDelegate
    An object conforming to the AVCaptureAudioDataOutputSampleBufferDelegate protocol that will receive sample buffers
    after they are captured.
 @param sampleBufferCallbackQueue
    A dispatch queue on which all sample buffer delegate methods will be called.

 @discussion
    When a new audio sample buffer is captured it will be vended to the sample buffer delegate using the
    captureOutput:didOutputSampleBuffer:fromConnection: delegate method. All delegate methods will be called on the
    specified dispatch queue. If the queue is blocked when new samples are captured, those samples will be automatically
    dropped when they become sufficiently late. This allows clients to process existing samples on the same queue without
    having to manage the potential memory usage increases that would otherwise occur when that processing is unable to
    keep up with the rate of incoming samples.

    Clients that need to minimize the chances of samples being dropped should specify a queue on which a sufficiently
    small amount of processing is being done outside of receiving sample buffers. However, if such clients migrate extra
    processing to another queue, they are responsible for ensuring that memory usage does not grow without bound from
    samples that have not been processed.

    A serial dispatch queue must be used to guarantee that audio samples will be delivered in order.
    The sampleBufferCallbackQueue parameter may not be NULL, except when setting sampleBufferDelegate to nil.
*/
- (void)setSampleBufferDelegate:(id<AVCaptureAudioDataOutputSampleBufferDelegate>)sampleBufferDelegate queue:(dispatch_queue_t)sampleBufferCallbackQueue;

/*!
 @property sampleBufferDelegate
 @abstract
    The receiver's delegate.

 @discussion
    The value of this property is an object conforming to the AVCaptureAudioDataOutputSampleBufferDelegate protocol that
    will receive sample buffers after they are captured. The delegate is set using the setSampleBufferDelegate:queue:
    method.
*/
@property(nonatomic, readonly) id<AVCaptureAudioDataOutputSampleBufferDelegate> sampleBufferDelegate;

/*!
 @property sampleBufferCallbackQueue
 @abstract
    The dispatch queue on which all sample buffer delegate methods will be called.

 @discussion
    The value of this property is a dispatch_queue_t. The queue is set using the setSampleBufferDelegate:queue: method.
*/
@property(nonatomic, readonly) dispatch_queue_t sampleBufferCallbackQueue;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/*!
 @property	 audioSettings
 @abstract
    Specifies the settings used to decode or re-encode audio before it is output by the receiver.

 @discussion
    The value of this property is an NSDictionary containing values for audio settings keys defined 
    in AVAudioSettings.h.  When audioSettings is set to nil, the AVCaptureAudioDataOutput vends samples
    in their device native format.
*/
@property(nonatomic, copy) NSDictionary *audioSettings NS_AVAILABLE(10_7, NA);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@end

/*!
 @protocol AVCaptureAudioDataOutputSampleBufferDelegate
 @abstract
    Defines an interface for delegates of AVCaptureAudioDataOutput to receive captured audio sample buffers.
*/
@protocol AVCaptureAudioDataOutputSampleBufferDelegate <NSObject>

@optional

/*!
 @method captureOutput:didOutputSampleBuffer:fromConnection:
 @abstract
    Called whenever an AVCaptureAudioDataOutput instance outputs a new audio sample buffer.

 @param captureOutput
    The AVCaptureAudioDataOutput instance that output the samples.
 @param sampleBuffer
    A CMSampleBuffer object containing the audio samples and additional information about them, such as their format and
    presentation time.
 @param connection
    The AVCaptureConnection from which the audio was received.

 @discussion
    Delegates receive this message whenever the output captures and outputs new audio samples, decoding or re-encoding
    as specified by the audioSettings property. Delegates can use the provided sample buffer in conjunction with other
    APIs for further processing. This method will be called on the dispatch queue specified by the output's
    sampleBufferCallbackQueue property. This method is called periodically, so it must be efficient to prevent capture
    performance problems, including dropped audio samples.

    Clients that need to reference the CMSampleBuffer object outside of the scope of this method must CFRetain it and
    then CFRelease it when they are finished with it.
*/
- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection;

@end


@class AVCaptureFileOutputInternal;
@protocol AVCaptureFileOutputRecordingDelegate;
@protocol AVCaptureFileOutputDelegate;

/*!
 @class AVCaptureFileOutput
 @abstract
    AVCaptureFileOutput is an abstract subclass of AVCaptureOutput that provides an interface for writing captured media
    to files.
 
 @discussion
    This abstract superclass defines the interface for outputs that record media samples to files. File outputs can start
    recording to a new file using the startRecordingToOutputFileURL:recordingDelegate: method. On successive invocations of this method on
    Mac OS X, the output file can by changed dynamically without losing media samples. A file output can stop recording
    using the stopRecording method. Because files are recorded in the background, applications will need to specify a
    delegate for each new file so that they can be notified when recorded files are finished.

    On Mac OS X, clients can also set a delegate on the file output itself that can be used to control recording along
    exact media sample boundaries using the captureOutput:didOutputSampleBuffer:fromConnection: method.

    The concrete subclasses of AVCaptureFileOutput are AVCaptureMovieFileOutput, which records media to a QuickTime movie
    file, and AVCaptureAudioFileOutput, which writes audio media to a variety of audio file formats.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCaptureFileOutput : AVCaptureOutput 
{
@private
	AVCaptureFileOutputInternal *_fileOutputInternal;
}

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/*!
 @property delegate
 @abstract
    The receiver's delegate.

 @discussion
    The value of this property is an object conforming to the AVCaptureFileOutputDelegate protocol that will be able to
    monitor and control recording along exact sample boundaries.
*/
@property(nonatomic, assign) id<AVCaptureFileOutputDelegate> delegate NS_AVAILABLE(10_7, NA);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/*!
 @property outputFileURL
 @abstract
    The file URL of the file to which the receiver is currently recording incoming buffers.

 @discussion
    The value of this property is an NSURL object containing the file URL of the file currently being written by the
    receiver. Returns nil if the receiver is not recording to any file.
*/
@property(nonatomic, readonly) NSURL *outputFileURL;

/*!
 @method startRecordingToOutputFileURL:recordingDelegate:
 @abstract
    Tells the receiver to start recording to a new file, and specifies a delegate that will be notified when recording is
    finished.
 
 @param outputFileURL
    An NSURL object containing the URL of the output file. This method throws an NSInvalidArgumentException if the URL is
    not a valid file URL.
 @param delegate
    An object conforming to the AVCaptureFileOutputRecordingDelegate protocol. Clients must specify a delegate so that
    they can be notified when recording to the given URL is finished.

 @discussion
    The method sets the file URL to which the receiver is currently writing output media. If a file at the given URL
    already exists when capturing starts, recording to the new file will fail.

    Clients need not call stopRecording before calling this method while another recording is in progress. On Mac OS X,
    if this method is invoked while an existing output file was already being recorded, no media samples will be
    discarded between the old file and the new file.

    When recording is stopped either by calling stopRecording, by changing files using this method, or because of an
    error, the remaining data that needs to be included to the file will be written in the background. Therefore, clients
    must specify a delegate that will be notified when all data has been written to the file using the
    captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: method. The recording delegate can also
    optionally implement methods that inform it when data starts being written, when recording is paused and resumed, and
    when recording is about to be finished.

    On Mac OS X, if this method is called within the captureOutput:didOutputSampleBuffer:fromConnection: delegate method,
    the first samples written to the new file are guaranteed to be those contained in the sample buffer passed to that
    method.

    Note: AVCaptureAudioFileOutput does not support -startRecordingToOutputFileURL:recordingDelegate:.  Use
    -startRecordingToOutputFileURL:outputFileType:recordingDelegate: instead.
*/
- (void)startRecordingToOutputFileURL:(NSURL*)outputFileURL recordingDelegate:(id<AVCaptureFileOutputRecordingDelegate>)delegate;

/*!
 @method stopRecording
 @abstract
    Tells the receiver to stop recording to the current file.

 @discussion
    Clients can call this method when they want to stop recording new samples to the current file, and do not want to
    continue recording to another file. Clients that want to switch from one file to another should not call this method.
    Instead they should simply call startRecordingToOutputFileURL:recordingDelegate: with the new file URL.

    When recording is stopped either by calling this method, by changing files using
    startRecordingToOutputFileURL:recordingDelegate:, or because of an error, the remaining data that needs to be
    included to the file will be written in the background. Therefore, before using the file, clients must wait until the
    delegate that was specified in startRecordingToOutputFileURL:recordingDelegate: is notified when all data has been
    written to the file using the captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: method.

    On Mac OS X, if this method is called within the captureOutput:didOutputSampleBuffer:fromConnection: delegate method,
    the last samples written to the current file are guaranteed to be those that were output immediately before those in
    the sample buffer passed to that method.
*/
- (void)stopRecording;

/*!
 @property recording
 @abstract
    Indicates whether the receiver is currently recording.

 @discussion
    The value of this property is YES when the receiver currently has a file to which it is writing new samples, NO
    otherwise.
*/
@property(nonatomic, readonly, getter=isRecording) BOOL recording;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/*!
 @property recordingPaused
 @abstract
    Indicates whether recording to the current output file is paused.

 @discussion
    This property indicates recording to the file returned by outputFileURL has been previously paused using the
    pauseRecording method. When a recording is paused, captured samples are not written to the output file, but new
    samples can be written to the same file in the future by calling resumeRecording.
*/
@property(nonatomic, readonly, getter=isRecordingPaused) BOOL recordingPaused NS_AVAILABLE(10_7, NA);

/*!
 @method pauseRecording
 @abstract
    Pauses recording to the current output file.

 @discussion
    This method causes the receiver to stop writing captured samples to the current output file returned by
    outputFileURL, but leaves the file open so that samples can be written to it in the future, when resumeRecording is
    called. This allows clients to record multiple media segments that are not contiguous in time to a single file.

    On Mac OS X, if this method is called within the captureOutput:didOutputSampleBuffer:fromConnection: delegate method,
    the last samples written to the current file are guaranteed to be those that were output immediately before those in
    the sample buffer passed to that method. 
*/
- (void)pauseRecording NS_AVAILABLE(10_7, NA);

/*!
 @method resumeRecording
 @abstract
    Resumes recording to the current output file after it was previously paused using pauseRecording.

 @discussion
    This method causes the receiver to resume writing captured samples to the current output file returned by
    outputFileURL, after recording was previously paused using pauseRecording. This allows clients to record multiple
    media segments that are not contiguous in time to a single file. 

    On Mac OS X, if this method is called within the captureOutput:didOutputSampleBuffer:fromConnection: delegate method,
    the first samples written to the current file are guaranteed to be those contained in the sample buffer passed to
    that method.
*/
- (void)resumeRecording NS_AVAILABLE(10_7, NA);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

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
    This property specifies a hard limit on the duration of recorded files. Recording is stopped when the limit is
    reached and the captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: delegate method is invoked
    with an appropriate error. The default value of this property is kCMTimeInvalid, which indicates no limit.
*/
@property(nonatomic) CMTime maxRecordedDuration;

/*!
 @property maxRecordedFileSize
 @abstract
    Specifies the maximum size, in bytes, of the data that should be recorded by the receiver.
 
 @discussion
    This property specifies a hard limit on the data size of recorded files. Recording is stopped when the limit is
    reached and the captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: delegate method is invoked
    with an appropriate error. The default value of this property is 0, which indicates no limit.
*/
@property(nonatomic) int64_t maxRecordedFileSize;

/*!
 @property minFreeDiskSpaceLimit
 @abstract
    Specifies the minimum amount of free space, in bytes, required for recording to continue on a given volume.

 @discussion
    This property specifies a hard lower limit on the amount of free space that must remain on a target volume for
    recording to continue. Recording is stopped when the limit is reached and the
    captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: delegate method is invoked with an
    appropriate error.
*/
@property(nonatomic) int64_t minFreeDiskSpaceLimit;

@end

/*!
 @protocol AVCaptureFileOutputRecordingDelegate
 @abstract
    Defines an interface for delegates of AVCaptureFileOutput to respond to events that occur in the process of recording
    a single file.
*/
@protocol AVCaptureFileOutputRecordingDelegate <NSObject>

@optional

/*!
 @method captureOutput:didStartRecordingToOutputFileAtURL:fromConnections:
 @abstract
    Informs the delegate when the output has started writing to a file.

 @param captureOutput
    The capture file output that started writing the file.
 @param fileURL
    The file URL of the file that is being written.
 @param connections
    An array of AVCaptureConnection objects attached to the file output that provided the data that is being written to
    the file.

 @discussion
    This method is called when the file output has started writing data to a file. If an error condition prevents any
    data from being written, this method may not be called.
    captureOutput:willFinishRecordingToOutputFileAtURL:fromConnections:error: and
    captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: will always be called, even if no data is
    written.

    Clients should not assume that this method will be called on a specific thread, and should also try to make this
    method as efficient as possible.
*/
- (void)captureOutput:(AVCaptureFileOutput *)captureOutput didStartRecordingToOutputFileAtURL:(NSURL *)fileURL fromConnections:(NSArray *)connections;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/*!
 @method captureOutput:didPauseRecordingToOutputFileAtURL:fromConnections:
 @abstract
    Called whenever the output is recording to a file and successfully pauses the recording at the request of the client.

 @param captureOutput
    The capture file output that has paused its file recording.
 @param fileURL
    The file URL of the file that is being written.
 @param connections
    An array of AVCaptureConnection objects attached to the file output that provided the data that is being written to
    the file.

 @discussion
    Delegates can use this method to be informed when a request to pause recording is actually respected. It is safe for
    delegates to change what the file output is currently doing (starting a new file, for example) from within this
    method. If recording to a file is stopped, either manually or due to an error, this method is not guaranteed to be
    called, even if a previous call to pauseRecording was made.

    Clients should not assume that this method will be called on a specific thread, and should also try to make this
    method as efficient as possible.
*/
- (void)captureOutput:(AVCaptureFileOutput *)captureOutput didPauseRecordingToOutputFileAtURL:(NSURL *)fileURL fromConnections:(NSArray *)connections NS_AVAILABLE(10_7, NA);

/*!
 @method captureOutput:didResumeRecordingToOutputFileAtURL:fromConnections:
 @abstract
    Called whenever the output, at the request of the client, successfully resumes a file recording that was paused.

 @param captureOutput
    The capture file output that has resumed its paused file recording.
 @param fileURL
    The file URL of the file that is being written.
 @param connections
    An array of AVCaptureConnection objects attached to the file output that provided the data that is being written to
    the file.

 @discussion
    Delegates can use this method to be informed when a request to resume recording is actually respected. It is safe for
    delegates to change what the file output is currently doing (starting a new file, for example) from within this
    method. If recording to a file is stopped, either manually or due to an error, this method is not guaranteed to be
    called, even if a previous call to resumeRecording was made.

    Clients should not assume that this method will be called on a specific thread, and should also try to make this
    method as efficient as possible.
*/
- (void)captureOutput:(AVCaptureFileOutput *)captureOutput didResumeRecordingToOutputFileAtURL:(NSURL *)fileURL fromConnections:(NSArray *)connections NS_AVAILABLE(10_7, NA);

/*!
 @method captureOutput:willFinishRecordingToOutputFileAtURL:fromConnections:error:
 @abstract
    Informs the delegate when the output will stop writing new samples to a file.

 @param captureOutput
    The capture file output that will finish writing the file.
 @param fileURL
    The file URL of the file that is being written.
 @param connections
    An array of AVCaptureConnection objects attached to the file output that provided the data that is being written to
    the file.
 @param error
    An error describing what caused the file to stop recording, or nil if there was no error.

 @discussion
    This method is called when the file output will stop recording new samples to the file at outputFileURL, either
    because startRecordingToOutputFileURL:recordingDelegate: or stopRecording were called, or because an error, described
    by the error parameter, occurred (if no error occurred, the error parameter will be nil). This method will always be
    called for each recording request, even if no data is successfully written to the file.

    Clients should not assume that this method will be called on a specific thread, and should also try to make this
    method as efficient as possible.
*/
- (void)captureOutput:(AVCaptureFileOutput *)captureOutput willFinishRecordingToOutputFileAtURL:(NSURL *)fileURL fromConnections:(NSArray *)connections error:(NSError *)error NS_AVAILABLE(10_7, NA);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@required

/*!
 @method captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error:
 @abstract
    Informs the delegate when all pending data has been written to an output file.

 @param captureOutput
    The capture file output that has finished writing the file.
 @param fileURL
    The file URL of the file that has been written.
 @param connections
    An array of AVCaptureConnection objects attached to the file output that provided the data that was written to the
    file.
 @param error
    An error describing what caused the file to stop recording, or nil if there was no error.

 @discussion
    This method is called when the file output has finished writing all data to a file whose recording was stopped,
    either because startRecordingToOutputFileURL:recordingDelegate: or stopRecording were called, or because an error,
    described by the error parameter, occurred (if no error occurred, the error parameter will be nil).  This method will
    always be called for each recording request, even if no data is successfully written to the file.

    Clients should not assume that this method will be called on a specific thread.

    Delegates are required to implement this method.
*/
- (void)captureOutput:(AVCaptureFileOutput *)captureOutput didFinishRecordingToOutputFileAtURL:(NSURL *)outputFileURL fromConnections:(NSArray *)connections error:(NSError *)error;

@end

/*!
 @protocol AVCaptureFileOutputDelegate
 @abstract
    Defines an interface for delegates of AVCaptureFileOutput to monitor and control recordings along exact sample
    boundaries.
*/
@protocol AVCaptureFileOutputDelegate <NSObject>

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@required

/*!
 @method captureOutputShouldProvideSampleAccurateRecordingStart:
 @abstract
    Allows a client to opt in to frame accurate record-start in captureOutput:didOutputSampleBuffer:fromConnection:

 @param captureOutput
    The AVCaptureFileOutput instance with which the delegate is associated.

 @discussion
    In apps linked before Mac OS X 10.8, delegates that implement the captureOutput:didOutputSampleBuffer:fromConnection: 
    method can ensure frame accurate start / stop of a recording by calling startRecordingToOutputFileURL:recordingDelegate:
    from within the callback.  Frame accurate start requires the capture output to apply outputSettings
    when the session starts running, so it is ready to record on any given frame boundary.  Compressing
    all the time while the session is running has power, thermal, and CPU implications.  In apps linked on or after
    Mac OS X 10.8, delegates must implement captureOutputShouldProvideSampleAccurateRecordingStart: to indicate
    whether frame accurate start/stop recording is required (returning YES) or not (returning NO).
    The output calls this method as soon as the delegate is added, and never again.  If your delegate returns
    NO, the capture output applies compression settings when startRecordingToOutputFileURL:recordingDelegate: is called, 
    and disables compression settings after the recording is stopped.
*/
- (BOOL)captureOutputShouldProvideSampleAccurateRecordingStart:(AVCaptureOutput *)captureOutput NS_AVAILABLE(10_8, NA);

@optional

/*!
 @method captureOutput:didOutputSampleBuffer:fromConnection:
 @abstract
    Gives the delegate the opportunity to inspect samples as they are received by the output and optionally start and
    stop recording at exact times.

 @param captureOutput
    The capture file output that is receiving the media data.
 @param sampleBuffer
    A CMSampleBuffer object containing the sample data and additional information about the sample, such as its format
    and presentation time.
 @param connection
    The AVCaptureConnection object attached to the file output from which the sample data was received.

 @discussion
    This method is called whenever the file output receives a single sample buffer (a single video frame or audio buffer,
    for example) from the given connection. This gives delegates an opportunity to start and stop recording or change
    output files at an exact sample boundary if -captureOutputShouldProvideSampleAccurateRecordingStart: returns YES. 
    If called from within this method, the file output’s startRecordingToOutputFileURL:recordingDelegate: and 
    resumeRecording methods are guaranteed to include the received sample buffer in the new file, whereas calls to 
    stopRecording and pauseRecording are guaranteed to include all samples leading up to those in the current sample 
    buffer in the existing file.

    Delegates can gather information particular to the samples by inspecting the CMSampleBuffer object. Sample buffers
    always contain a single frame of video if called from this method but may also contain multiple samples of audio. For
    B-frame video formats, samples are always delivered in presentation order.

    Clients that need to reference the CMSampleBuffer object outside of the scope of this method must CFRetain it and
    then CFRelease it when they are finished with it.

    Note that to maintain optimal performance, some sample buffers directly reference pools of memory that may need to be
    reused by the device system and other capture inputs. This is frequently the case for uncompressed device native
    capture where memory blocks are copied as little as possible. If multiple sample buffers reference such pools of
    memory for too long, inputs will no longer be able to copy new samples into memory and those samples will be dropped.
    If your application is causing samples to be dropped by retaining the provided CMSampleBuffer objects for too long,
    but it needs access to the sample data for a long period of time, consider copying the data into a new buffer and
    then calling CFRelease on the sample buffer if it was previously retained so that the memory it references can be
    reused. 
 
    Clients should not assume that this method will be called on a specific thread. In addition, this method is called
    periodically, so it must be efficient to prevent capture performance problems.
*/
- (void)captureOutput:(AVCaptureFileOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection NS_AVAILABLE(10_7, NA);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@end


@class AVCaptureMovieFileOutputInternal;

/*!
 @class AVCaptureMovieFileOutput
 @abstract
    AVCaptureMovieFileOutput is a concrete subclass of AVCaptureFileOutput that writes captured media to QuickTime movie
    files.

 @discussion
    AVCaptureMovieFileOutput implements the complete file recording interface declared by AVCaptureFileOutput for writing
    media data to QuickTime movie files. In addition, instances of AVCaptureMovieFileOutput allow clients to configure
    options specific to the QuickTime file format, including allowing them to write metadata collections to each file,
    specify media encoding options for each track (Mac OS X), and specify an interval at which movie fragments should be written.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCaptureMovieFileOutput : AVCaptureFileOutput
{
@private
	AVCaptureMovieFileOutputInternal *_internal;
}

/*!
 @property movieFragmentInterval
 @abstract
    Specifies the frequency with which movie fragments should be written.

 @discussion
    When movie fragments are used, a partially written QuickTime movie file whose writing is unexpectedly interrupted can
    be successfully opened and played up to multiples of the specified time interval. A value of kCMTimeInvalid indicates
    that movie fragments should not be used, but that only a movie atom describing all of the media in the file should be
    written. The default value of this property is ten seconds.

    Changing the value of this property will not affect the movie fragment interval of the file currently being written,
    if there is one.
*/
@property(nonatomic) CMTime movieFragmentInterval;

/*!
 @property metadata
 @abstract
    A collection of metadata to be written to the receiver's output files.

 @discussion
    The value of this property is an array of AVMetadataItem objects representing the collection of top-level metadata to
    be written in each output file.
*/
@property(nonatomic, copy) NSArray *metadata;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

/*!
 @method outputSettingsForConnection:
 @abstract
    Returns the options the receiver uses to re-encode media from the given connection as it is being recorded.

 @param connection
    The connection delivering the media to be re-encoded.
 @result
    An NSDictionary of output settings.

 @discussion
    See AVAudioSettings.h for audio connections or AVVideoSettings.h for video connections for more information on
    how to construct an output settings dictionary.  If the returned value is an empty dictionary (i.e. [NSDictionary
    dictionary], the format of the media from the connection will not be changed before being written to the file.  If
    -setOutputSettings:forConnection: was called with a nil dictionary, this method returns a non-nil dictionary reflecting
    the settings used by the AVCaptureSession's current sessionPreset.
*/
- (NSDictionary *)outputSettingsForConnection:(AVCaptureConnection *)connection NS_AVAILABLE(10_7, NA);

/*!
 @method setOutputSettings:forConnection:
 @abstract
    Sets the options the receiver uses to re-encode media from the given connection as it is being recorded.

 @param outputSettings
    An NSDictionary of output settings.
 @param connection
    The connection delivering the media to be re-encoded.

 @discussion
    See AVAudioSettings.h for audio connections or AVVideoSettings.h for video connections for more information on
    how to construct an output settings dictionary.  A value of an empty dictionary (i.e. [NSDictionary dictionary], means
    that the format of the media from the connection should not be changed before being written to the file.  A value of
    nil means that the output format will be determined by the session preset.  In this case, -outputSettingsForConnection:
    will return a non-nil dictionary reflecting the settings used by the AVCaptureSession's current sessionPreset.
*/
- (void)setOutputSettings:(NSDictionary *)outputSettings forConnection:(AVCaptureConnection *)connection NS_AVAILABLE(10_7, NA);

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@end


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@class AVCaptureAudioFileOutputInternal;

/*!
 @class AVCaptureAudioFileOutput
 @abstract
    AVCaptureAudioFileOutput is a concrete subclass of AVCaptureFileOutput that writes captured audio to any audio file
    type supported by CoreAudio.
 
 @discussion
    AVCaptureAudioFileOutput implements the complete file recording interface declared by AVCaptureFileOutput for writing
    media data to audio files. In addition, instances of AVCaptureAudioFileOutput allow clients to configure options
    specific to the audio file formats, including allowing them to write metadata collections to each file and specify
    audio encoding options.
*/
NS_CLASS_AVAILABLE(10_7, NA)
@interface AVCaptureAudioFileOutput : AVCaptureFileOutput
{
@private
	AVCaptureAudioFileOutputInternal *_internal;
}

/*!
 @method availableOutputFileTypes
 @abstract		
    Provides the file types AVCaptureAudioFileOutput can write.
 @result
    An NSArray of UTIs identifying the file types the AVCaptureAudioFileOutput class can write.
*/
+ (NSArray *) availableOutputFileTypes;

/*!
 @method startRecordingToOutputFileURL:outputFileType:recordingDelegate:
 @abstract
    Tells the receiver to start recording to a new file of the specified format, and specifies a delegate that will be
    notified when recording is finished.

 @param outputFileURL
    An NSURL object containing the URL of the output file. This method throws an NSInvalidArgumentException if the URL is
    not a valid file URL.
 @param fileType
    A UTI indicating the format of the file to be written.
 @param delegate
    An object conforming to the AVCaptureFileOutputRecordingDelegate protocol. Clients must specify a delegate so that they
    can be notified when recording to the given URL is finished.

 @discussion
    The method sets the file URL to which the receiver is currently writing output media. If a file at the given URL
    already exists when capturing starts, recording to the new file will fail.

    The fileType argument is a UTI corresponding to the audio file format that should be written. UTIs for common 
    audio file types are declared in AVMediaFormat.h.

    Clients need not call stopRecording before calling this method while another recording is in progress. If this method
    is invoked while an existing output file was already being recorded, no media samples will be discarded between the
    old file and the new file.

    When recording is stopped either by calling stopRecording, by changing files using this method, or because of an
    error, the remaining data that needs to be included to the file will be written in the background. Therefore, clients
    must specify a delegate that will be notified when all data has been written to the file using the
    captureOutput:didFinishRecordingToOutputFileAtURL:fromConnections:error: method. The recording delegate can also
    optionally implement methods that inform it when data starts being written, when recording is paused and resumed, and
    when recording is about to be finished.

    On Mac OS X, if this method is called within the captureOutput:didOutputSampleBuffer:fromConnection: delegate method,
    the first samples written to the new file are guaranteed to be those contained in the sample buffer passed to that
    method.
*/
- (void)startRecordingToOutputFileURL:(NSURL*)outputFileURL outputFileType:(NSString *)fileType recordingDelegate:(id<AVCaptureFileOutputRecordingDelegate>)delegate;

/*!
 @property metadata
 @abstract
    A collection of metadata to be written to the receiver's output files.

 @discussion
    The value of this property is an array of AVMetadataItem objects representing the collection of top-level metadata to
    be written in each output file. Only ID3 v2.2, v2.3, or v2.4 style metadata items are supported.
*/
@property(nonatomic, copy) NSArray *metadata; 

/*!
 @property audioSettings
 @abstract
    Specifies the options the receiver uses to re-encode audio as it is being recorded.

 @discussion
    The output settings dictionary can contain values for keys from AVAudioSettings.h. A value of nil indicates that the
    format of the audio should not be changed before being written to the file.
*/
@property(nonatomic, copy) NSDictionary *audioSettings;

@end

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))


@class AVCaptureStillImageOutputInternal;

/*!
 @class AVCaptureStillImageOutput
 @abstract
    AVCaptureStillImageOutput is a concrete subclass of AVCaptureOutput that can be used to capture high-quality still
    images with accompanying metadata.

 @discussion
    Instances of AVCaptureStillImageOutput can be used to capture, on demand, high quality snapshots from a realtime
    capture source. Clients can request a still image for the current time using the
    captureStillImageAsynchronouslyFromConnection:completionHandler: method. Clients can also configure still image
    outputs to produce still images in specific image formats.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCaptureStillImageOutput : AVCaptureOutput 
{
@private
	AVCaptureStillImageOutputInternal *_internal;
}

/*!
 @property outputSettings
 @abstract
    Specifies the options the receiver uses to encode still images before they are delivered.

 @discussion
    See AVVideoSettings.h for more information on how to construct an output settings dictionary.

    On iOS, the only currently supported keys are AVVideoCodecKey and kCVPixelBufferPixelFormatTypeKey. 
    Use -availableImageDataCVPixelFormatTypes and -availableImageDataCodecTypes to determine what 
    codec keys and pixel formats are supported.
*/
@property(nonatomic, copy) NSDictionary *outputSettings;

/*!
 @property availableImageDataCVPixelFormatTypes
 @abstract
    Indicates the supported image pixel formats that can be specified in outputSettings.

 @discussion
    The value of this property is an NSArray of NSNumbers that can be used as values for the 
    kCVPixelBufferPixelFormatTypeKey in the receiver's outputSettings property.  The first
    format in the returned list is the most efficient output format.
*/
@property(nonatomic, readonly) NSArray *availableImageDataCVPixelFormatTypes;

/*!
 @property availableImageDataCodecTypes
 @abstract
    Indicates the supported image codec formats that can be specified in outputSettings.

 @discussion
    The value of this property is an NSArray of NSStrings that can be used as values for the 
    AVVideoCodecKey in the receiver's outputSettings property.
*/
@property(nonatomic, readonly) NSArray *availableImageDataCodecTypes;

/*!
 @property capturingStillImage
 @abstract
    A boolean value that becomes true when a still image is being captured.

 @discussion
    The value of this property is a BOOL that becomes true when a still image is being
    captured, and false when no still image capture is underway.  This property is
    key-value observable.
*/
@property(readonly, getter=isCapturingStillImage) BOOL capturingStillImage NS_AVAILABLE(10_8, 5_0);

/*!
 @method captureStillImageAsynchronouslyFromConnection:completionHandler:
 @abstract
    Initiates an asynchronous still image capture, returning the result to a completion handler.

 @param connection
    The AVCaptureConnection object from which to capture the still image.
 @param handler
    A block that will be called when the still image capture is complete. The block will be passed a CMSampleBuffer
    object containing the image data or an NSError object if an image could not be captured.

 @discussion
    This method will return immediately after it is invoked, later calling the provided completion handler block when
    image data is ready. If the request could not be completed, the error parameter will contain an NSError object
    describing the failure.

    Attachments to the image data sample buffer may contain metadata appropriate to the image data format. For instance,
    a sample buffer containing JPEG data may carry a kCGImagePropertyExifDictionary as an attachment. See
    <ImageIO/CGImageProperties.h> for a list of keys and value types.

    Clients should not assume that the completion handler will be called on a specific thread.
*/
- (void)captureStillImageAsynchronouslyFromConnection:(AVCaptureConnection *)connection completionHandler:(void (^)(CMSampleBufferRef imageDataSampleBuffer, NSError *error))handler;

/*!
 @method jpegStillImageNSDataRepresentation:
 @abstract
    Converts the still image data and metadata attachments in a JPEG sample buffer to an NSData representation.

 @param jpegSampleBuffer
    The sample buffer carrying JPEG image data, optionally with Exif metadata sample buffer attachments.
    This method throws an NSInvalidArgumentException if jpegSampleBuffer is NULL or not in the JPEG format.

 @discussion
    This method returns an NSData representation of a JPEG still image sample buffer, merging the image data and
    Exif metadata sample buffer attachments without recompressing the image.
    The returned NSData is suitable for writing to disk.
*/
+ (NSData *)jpegStillImageNSDataRepresentation:(CMSampleBufferRef)jpegSampleBuffer;

@end


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@class AVCaptureAudioPreviewOutputInternal;

/*!
 @class AVCaptureAudioPreviewOutput
 @abstract
    AVCaptureAudioPreviewOutput is a concrete subclass of AVCaptureOutput that can be used to preview the audio being
    captured.
 
 @discussion
    Instances of AVCaptureAudioPreviewOutput have an associated Core Audio output device that can be used to play audio
    being captured by the capture session. The unique ID of a Core Audio device can be obtained from its
    kAudioDevicePropertyDeviceUID property.
*/
NS_CLASS_AVAILABLE(10_7, NA)
@interface AVCaptureAudioPreviewOutput : AVCaptureOutput 
{
@private
	AVCaptureAudioPreviewOutputInternal *_internal;
}

/*!
 @property outputDeviceUniqueID
 @abstract
    Specifies the unique ID of the Core Audio output device being used to play preview audio.

 @discussion
    The value of this property is an NSString containing the unique ID of the Core Audio device to be used for output, or
    nil if the default system output should be used
*/
@property(nonatomic, copy) NSString *outputDeviceUniqueID;

/*!
 @property volume
 @abstract
    Specifies the preview volume of the output.

 @discussion
    The value of this property is the preview volume of the receiver, where 1.0 is the maximum volume and 0.0 is muted. 
*/
@property(nonatomic) float volume;

@end

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

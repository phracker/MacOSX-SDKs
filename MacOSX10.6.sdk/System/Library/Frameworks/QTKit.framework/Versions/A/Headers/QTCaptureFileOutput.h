/*
	File:		QTCaptureFileOutput.h

	Copyright:	(c)2008-2010 by Apple Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

#import <QTKit/QTCaptureOutput.h>
#import <QTKit/QTTime.h>

enum {
    QTCaptureFileOutputBufferDestinationNewFile	= 1,
    QTCaptureFileOutputBufferDestinationOldFile	= 2
};
typedef NSUInteger QTCaptureFileOutputBufferDestination;

@class QTCaptureConnection;
@class QTCompressionOptions;
@class QTSampleBuffer;

@class QTCaptureFileOutputInternal;

@interface QTCaptureFileOutput : QTCaptureOutput {
@private
	QTCaptureFileOutputInternal	*_fileOutputInternal;
	
	id __weak					_delegate;

	long						_reserved4;
	long						_reserved5;
	long						_reserved6;
}

// This method returns the file URL of the file to which the receiver is currently recording incoming buffers. If no file is being recorded, this method returns nil.
- (NSURL *)outputFileURL;

// These methods set the file to which the receiver should currently record incoming buffers, stopping recording on the exisitng output file if there is one, and overwriting the  file at the specified URL if it exists. To tell the output to stop recording to any file, applications can pass nil as the file URL. Whenever the output file is changed, any pending recording for the previous file is finished in the background. Applications must implement the captureOutput:didFinishRecordingToOutputFileAtURL:forConnections:dueToError: delegate method to be notified when the file is finished. If specified, the buffer destination determines whether the buffer currently in flight should be included in the old file or the new file.
- (void)recordToOutputFileURL:(NSURL *)url;	// calls recordToOutputFileURL:bufferDestination: with a buffer destination of QTCaptureFileOutputBufferDestinationNewFile
- (void)recordToOutputFileURL:(NSURL *)url bufferDestination:(QTCaptureFileOutputBufferDestination)bufferDestination;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3

/*!
    @method isRecordingPaused
    @abstract Returns whether recording to the current output file is paused.
    @discussion This method returns whether recording to the file returned by outputFileURL has been previously paused using the pauseRecording method.
    When a recording is paused, captured samples are not written to the output file, but new samples can be written to the same file in the future by
    calling resumeRecording. The value of this method is key value observable using the key @"recordingPaused".
    @result Returns YES if recording to the current output file is paused and returns NO otherwise.
*/
- (BOOL)isRecordingPaused;

/*!
    @method pauseRecording
    @abstract Pauses recording to the current output file.
    @discussion This method causes the receiver to stop writing captured samples to the current output file returned by outputFileURL, but leaves the
     file open so that samples can be written to it in the future, when resumeRecording is called. This allows clients to record multiple media
    segments that are not contiguous in time to a single file. When clients stop recording or change files using
    recordToOutputFileURL:bufferDestination: or recording automatically stops due to an error condition while recording is paused, the output file
    will be finished and closed normally without requiring a matching call to resumeRecording. When there is no current output file, or when
    recording is already paused, this method does nothing. This method can be called within the captureOutput:didOutputSampleBuffer:fromConnection:
    delegate method to pause recording after an exact media sample.
*/
- (void)pauseRecording;

/*!
    @method resumeRecording
    @abstract Resumes recording to the current output file after it was previously paused using pauseRecording.
    @discussion This method causes the receiver to resume writing captured samples to the current output file returned by outputFileURL, after
    recording was previously paused using pauseRecording. This allows clients to record multiple media segments that are not contiguous in time to a
    single file. When there is no current output file, or when recording is not paused, this method does nothing. This method can be called within
    the captureOutput:didOutputSampleBuffer:fromConnection: delegate method to resume recording at an exact media sample.
*/
- (void)resumeRecording;

#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3 */

- (QTCompressionOptions *)compressionOptionsForConnection:(QTCaptureConnection *)connection;
- (void)setCompressionOptions:(QTCompressionOptions *)compressionOptions forConnection:(QTCaptureConnection *)connection;

/*!
    @method maximumVideoSize
    @abstract Returns the maximum dimensions within which the receiver will record video.
    @discussion This method returns the maximum limit on the dimensions of video that the receiver records to a file previously set by
    setMaximumVideoSize:. When a size is set, all video recorded by the receiver will be no larger than the specified size, while still preserving
    the original aspect ratio of the content. A value of NSZeroSize indicates that there should be no limit. If this is set to a value other than
    NSZeroSize, device native compressed video, such as DV video, will be decompressed so that it can be resized. By default, there is no limit on
    the maximum recorded video size.
    @result An NSSize specifying the maximum dimensions at which the receiver should record video. Returns NSZeroSize if there is no limit.
*/
- (NSSize)maximumVideoSize;

/*!
    @method setMaximumVideoSize:
    @abstract Sets the maximum dimensions within which the receiver should record video.
    @discussion This method sets the maximum limit on the dimensions of video that the receiver records to a file. When a size is set, all video
    recorded by the receiver will be no larger than the specified size, while still preserving the original aspect ratio of the content. A value of
    NSZeroSize indicates that there should be no limit. If this is set to a value other than NSZeroSize, device native compressed video, such as DV
    video, will be decompressed so that it can be resized. By default, there is no limit on the maximum recorded video size.
    @param maximumVideoSize An NSSize specifying the maximum dimensions at which the receiver should record video. A value of NSZeroSize indicates
    that there should be no limit.
*/
- (void)setMaximumVideoSize:(NSSize)maximumVideoSize;

/*!
    @method minimumVideoFrameInterval
    @abstract Returns the minimum time interval between which the receiver will record consecutive video frames.
    @discussion This method returns the minimum amount of time that should seperate consecutive frames recorded by the receiver. This is equivalent
    to the inverse of the maximum frame rate. A value of 0 indicates an unlimited maximum frame rate. If this is set to a value other than 0, device
    native compressed video, such as DV video, will be decompressed so that its frame rate can be adjusted. The default value is 0.
    @result An NSTimeInterval specifying the minimum interval between video frames. Returns 0 if there is no frame rate limit set.
*/
- (NSTimeInterval)minimumVideoFrameInterval;

/*!
    @method setMinimumVideoFrameInterval:
    @abstract Sets the minimum time interval between which the receiver should record consecutive video frames.
    @discussion This method sets the minimum amount of time that should seperate consecutive frames recorded by the receiver. This is equivalent to
    the inverse of the maximum frame rate. A value of 0 indicates an unlimited maximum frame rate. If this is set to a value other than 0, device
    native compressed video, such as DV video, will be decompressed so that its frame rate can be adjusted. The default value is 0.
    @param minimumVideoFrameInterval An NSTimeInterval specifying the minimum interval between video frames. A value of 0 indicates that there should
    be no frame rate limit.
*/
- (void)setMinimumVideoFrameInterval:(NSTimeInterval)minimumVideoFrameInterval;

// These methods return the total duration and file size recorded to the current output file
- (QTTime)recordedDuration;
- (UInt64)recordedFileSize;

// These methods set a soft limit on the length of recorded files. Delegates can determine what to do when the limit is reached by implementing the captureOutput:shouldChangeOutputFileAtURL:forConnections:dueToError: method. By default, the current output file is set to nil when the limit is reached.
- (QTTime)maximumRecordedDuration;
- (void)setMaximumRecordedDuration:(QTTime)maximumRecordedDuration;
- (UInt64)maximumRecordedFileSize;
- (void)setMaximumRecordedFileSize:(UInt64)maximumRecordedFileSize;

- (id)delegate;
- (void)setDelegate:(id)delegate;

@end

@interface NSObject (QTCaptureFileOutput_Delegate)

// This method is called every time the recorder output receives a new sample buffer. When called within this method, recordToOutputFileURL: and recordToOutputFileURL:bufferDestination:, are all guaranteed to occur on the given sample buffer. Delegates should not expect this method to be called on the main thread. In addition, since this method is called frequently, it must be efficient.
- (void)captureOutput:(QTCaptureFileOutput *)captureOutput didOutputSampleBuffer:(QTSampleBuffer *)sampleBuffer fromConnection:(QTCaptureConnection *)connection;

// These methods are called when the output starts recording to a new file.
- (void)captureOutput:(QTCaptureFileOutput *)captureOutput willStartRecordingToOutputFileAtURL:(NSURL *)fileURL forConnections:(NSArray *)connections;
- (void)captureOutput:(QTCaptureFileOutput *)captureOutput didStartRecordingToOutputFileAtURL:(NSURL *)fileURL forConnections:(NSArray *)connections;

// This method is called when the file recorder reaches a soft limit, i.e. the set maximum file size or duration. If the delegate returns NO, the file writer will continue writing the same file. If the delegate returns YES and doesn't set a new output file, captureOutput:mustChangeOutputFileAtURL:forConnections:dueToError: will be called. If the delegate returns YES and sets a new output file, recording will continue on the new file.
- (BOOL)captureOutput:(QTCaptureFileOutput *)captureOutput shouldChangeOutputFileAtURL:(NSURL *)outputFileURL forConnections:(NSArray *)connections dueToError:(NSError *)error;

// This method is called when the file writer reaches a hard limit, such as space running out on the current disk, or the stream format of the incoming media changing. If the delegate does nothing, the current output file will be set to nil. If the delegate sets a new output file (on a different disk in the case of hitting a disk space limit) recording will continue on the new file.
- (void)captureOutput:(QTCaptureFileOutput *)captureOutput mustChangeOutputFileAtURL:(NSURL *)outputFileURL forConnections:(NSArray *)connections dueToError:(NSError *)error;

// This method is called whenever a file will be finished, either because recordToFile:/recordToFile:bufferDestination: was called. or an error forced the file to be finished. If the file was forced to be finished due to an error, the error is described in the error parameter. Otherwise, the error parameter equals nil.
- (void)captureOutput:(QTCaptureFileOutput *)captureOutput willFinishRecordingToOutputFileAtURL:(NSURL *)outputFileURL forConnections:(NSArray *)connections dueToError:(NSError *)error;

// This method is called whenever a file is finished successfully. If the file was forced to be finished due to an error (including errors that resulted in either of the above two methods being called), the error is described in the error parameter. Otherwise, the error parameter equals nil.
- (void)captureOutput:(QTCaptureFileOutput *)captureOutput didFinishRecordingToOutputFileAtURL:(NSURL *)outputFileURL forConnections:(NSArray *)connections dueToError:(NSError *)error;

/*!
	@method captureOutput:didPauseRecordingToOutputFileAtURL:forConnections:
	@abstract This method is called whenever the output is recording to a file and successfully pauses the recording at the request of the client.
	@discussion Delegates can use this method to be informed when a request to pause recording is actually respected.  It is safe for delegates to
	change what the file output is currently doing (starting a new file for example) from within this method. Clients should not assume that this
	method will be called on the main thread, and should also try to make this method as efficient as possible. If recording to a file is stopped,
	either manually or due to an error, this method is not guaranteed to be called, even if a previous call to pauseRecording was made.
	@param captureOutput The capture file output that has paused its file recording.
	@param fileURL The file URL of the file that is being written.
	@param connections An array of QTCaptureConnection objects owned by the file output that provided the data that is being written to the file.
*/
- (void)captureOutput:(QTCaptureFileOutput *)captureOutput didPauseRecordingToOutputFileAtURL:(NSURL *)fileURL forConnections:(NSArray *)connections;

/*!
	@method captureOutput:didResumeRecordingToOutputFileAtURL:forConnections:
	@abstract This method is called whenever the output, at the request of the client, successfully resumes a file recording that was paused.
	@discussion Delegates can use this method to be informed when a request to resume a paused recording is actually respected.  It is safe for
	delegates to change what the file output is currently doing (starting a new file for example) from within this method. Clients should not assume
	that this method will be called on the main thread, and should also try to make this method as efficient as possible. If recording to a file is
	stopped, either manually or due to an error, this method is not guaranteed to be called, even if a previous call to resumeRecording was made.
	@param captureOutput The capture file output that has resumed its paused file recording.
	@param fileURL The file URL of the file that is being written.
	@param connections An array of QTCaptureConnection objects owned by the file output that provided the data that is being written to the file.
*/
- (void)captureOutput:(QTCaptureFileOutput *)captureOutput didResumeRecordingToOutputFileAtURL:(NSURL *)fileURL forConnections:(NSArray *)connections;

@end

#endif	/* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

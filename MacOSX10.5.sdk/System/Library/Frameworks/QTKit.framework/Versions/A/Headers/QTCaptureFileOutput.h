/*
	File:		QTCaptureFileOutput.h

	Copyright:	(c)2007 by Apple Inc., all rights reserved.

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
#if __LP64__
	int32_t						_delegateProxy;
#else
	QTCaptureFileOutputInternal	*_fileOutputInternal;
#endif
	
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

- (QTCompressionOptions *)compressionOptionsForConnection:(QTCaptureConnection *)connection;
- (void)setCompressionOptions:(QTCompressionOptions *)compressionOptions forConnection:(QTCaptureConnection *)connection;

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

@interface NSObject (QTCaptureFileOutputDelegate)

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

@end

#endif	/* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

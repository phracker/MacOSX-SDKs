/*
	File:		QTCaptureDecompressedAudioOutput.h
 
	Copyright:	(c)2008-2010 by Apple Inc., all rights reserved.

 */

#import <Foundation/Foundation.h>
#import <QTKit/QTCaptureOutput.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

@class QTCaptureDecompressedAudioOutputInternal;

@class QTCaptureConnection;
@class QTSampleBuffer;

/*!
    @class QTCaptureDecompressedAudioOutput

    @abstract An QTCaptureDecompressedAudioOutput object is an output destination for QTCaptureSession that can be used to process audio sample buffers from
    the audio being captured.
 
    @discussion This class represents an output destination for a QTCaptureSession object that can be used to process audio sample buffers from the
    audio being captured. Instances of QTCaptureDecompressedAudioOutput produce audio sample buffers suitable for custom high-quality realtime processing.
    Applications can access the audio sample buffers via the captureOutput:didOutputAudioSampleBuffer:fromConnection: delegate method. Clients can
    also create subclasses of QTCaptureDecompressedAudioOutput to add custom capturing behavior.
*/
@interface QTCaptureDecompressedAudioOutput : QTCaptureOutput {
@private
	QTCaptureDecompressedAudioOutputInternal    *_internal;
	id                                          _delegate;

	long                                        _reserved4;
	long                                        _reserved5;
	long                                        _reserved6;
}

/*!
    @method delegate
    @abstract Returns the receiver’s delegate..
*/
- (id)delegate;

/*!
    @method setDelegate:
    @abstract Sets the receiver’s delegate..
*/
- (void)setDelegate:(id)delegate;

/*!
    @method outputAudioSampleBuffer:fromConnection:
    @abstract Called whenever the receiver outputs a new audio sample buffer.
    @discussion This method should not be invoked directly. Subclasses can override this method to provide custom processing behavior for each sample
    buffer. The default implementation calls the delegate’s captureOutput:didOutputAudioSampleBuffer:fromConnection: method. Subclasses should not
    assume that this method will be called on the main thread. In addition, this method is called periodically, so it must be efficient to prevent
    capture performance problems.
    @param sampleBuffer A sample buffer containing the audio data and additional information about the buffer, such as its presentation time.
    @param connection The connection from which the audio was received.
*/
- (void)outputAudioSampleBuffer:(QTSampleBuffer *)sampleBuffer fromConnection:(QTCaptureConnection *)connection;

@end

@interface NSObject	(QTCaptureDecompressedAudioOutput_Delegate)

/*!
    @method captureOutput:didOutputAudioSampleBuffer:fromConnection:
    @abstract This method is called whenever the audio data output outputs a new audio sample buffer.
    @discussion Delegates receive this message whenever the output produces a new audio sample buffer. Delegates can use the provided sample buffer
    for custom processing of captured audio. Delegates should not assume that this method will be called on the main thread. In addition, this method
    is called periodically, so it must be efficient to prevent capture performance problems.
    @param captureOutput The QTCaptureDecompressedAudioOutput instance that output the frame.
    @param sampleBuffer A sample buffer containing the audio data and additional information about the buffer, such as its presentation time.
    @param connection The connection from which the audio was received.
*/
- (void)captureOutput:(QTCaptureOutput *)captureOutput didOutputAudioSampleBuffer:(QTSampleBuffer *)sampleBuffer fromConnection:(QTCaptureConnection *)connection;

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

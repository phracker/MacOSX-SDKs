/*
	File:		QTCaptureDecompressedVideoOutput.h
 
	Copyright:	(c)2008-2012 by Apple Inc., all rights reserved.

*/

/*
  QTKit has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.  In order to transition your 
  project from QTKit to AVFoundation please refer to:
  "Technical Note TN2300 Transitioning QTKit code to AV Foundation".
*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

#import <QTKit/QTCaptureOutput.h>
#import <QuartzCore/QuartzCore.h>

@class QTCaptureDecompressedVideoOutputInternal;

@class QTCaptureConnection;
@class QTSampleBuffer;

/*!
    @class QTCaptureDecompressedVideoOutput

    @abstract An QTCaptureDecompressedVideoOutput object is an output destination for QTCaptureSession that can be used to process decompressed
    frames from the video being captured.

    @discussion This class represents an output destination for a QTCaptureSession object that can be used to process decompressed frames from the
    video being captured. Instances of QTCaptureDecompressedVideoOutput produce decompressed video frames suitable for high-quality processing.
    Because instances maintain maximum frame quality and avoid dropping frames, using this output may result in reduced performance while capturing.
    Applications that need to process decompressed frames but can tolerate dropped frames or drops in decompression quality should use
    QTCaptureVideoPreviewOutput instead. Applications can access the decompressed frames via the
    captureOutput:didOutputVideoFrame:withSampleBuffer:fromConnection: delegate method. Clients can also create subclasses of
    QTCaptureDecompressedVideoOutput to add custom capturing behavior.
*/
@interface QTCaptureDecompressedVideoOutput : QTCaptureOutput {
@private
	QTCaptureDecompressedVideoOutputInternal	*_internal;
	id											_delegate;

	long										_reserved4;
	long										_reserved5;
	long										_reserved6;
}

/*!
    @method pixelBufferAttributes
    @abstract Returns the Core Video pixel buffer attributes previously set by setPixelBufferAttributes: that determine what kind of pixel buffers
    are output by the receiver.
    @discussion This method returns the pixel buffer attributes set by setPixelBufferAttributes: that clients can use to customize the size and pixel
    format of the video frames output by the receiver. When the dictionary is non-nil, the receiver will attempt to output pixel buffers using the
    attributes specified in the dictionary. A non-nil dictionary also guarantees that the output CVImageBuffer is a CVPixelBuffer. When the value for
    kCVPixelBufferPixelFormatTypeKey is set to an NSNumber, all image buffers output by the receiver will be in that format. When the value is an
    NSArray, image buffers output by the receiver will be in the most optimal format specified in that array. If the captured images are not in the
    one of the specified pixel formats, then a format conversion will be performed. If the dictionary is NIL or there is no value for the
    kCVPixelBufferPixelFormatTypeKey, then the receiver will output images in the most efficient possible format given the input. For example, if the
    source is an iSight producing component Y'CbCr 8-bit 4:2:2 video then Y'CbCr 8-bit 4:2:2 will be used as the output format in order to avoid any
    conversions. The default value for the returned dictionary is nil.
    @result A dictionary containing pixel buffer attributes for buffers output by the reciever. The keys in the dictionary are described in
    CoreVideo/CVPixelBuffer.h. If the return value is nil, then the receiver outputs buffers using the fastest possible pixel buffer attributes.
*/
- (NSDictionary *)pixelBufferAttributes AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
    @method setPixelBufferAttributes:
    @abstract Sets the CoreVideo pixel buffer attributes that determine what kind of pixel buffers are output by the receiver.
    @discussion This method sets the pixel buffer attributes that clients can use to customize the size and pixel format of the video frames output
    by the receiver. When the dictionary is non-nil, the receiver will attempt to output pixel buffers using the attributes specified in the
    dictionary. A non-nil dictionary also guarantees that the output CVImageBuffer is a CVPixelBuffer. When the value for
    kCVPixelBufferPixelFormatTypeKey is set to an NSNumber, all image buffers output by the receiver will be in that format. When the value is an
    NSArray, image buffers output by the receiver will be in the most optimal format specified in that array. If the captured images are not in the
    one of the specified pixel formats, then a format conversion will be performed. If the dictionary is NIL or there is no value for the
    kCVPixelBufferPixelFormatTypeKey, then the receiver will output images in the most efficient possible format given the input. For example, if the
    source is an iSight producing component Y'CbCr 8-bit 4:2:2 video then Y'CbCr 8-bit 4:2:2 will be used as the output format in order to avoid any
    conversions.
    @param pixelBufferAttributes A dictionary containing pixel buffer attributes for buffers that will be output by the reciever. The keys in the
    dictionary are described in CoreVideo/CVPixelBuffer.h. If the dictionary is NIL, then the receiver outputs buffers using the fastest possible
    pixel buffer attributes..
*/
- (void)setPixelBufferAttributes:(NSDictionary *)pixelBufferAttributes AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3

/*!
    @method minimumVideoFrameInterval
    @abstract Returns the minimum time interval between which the receiver will output consecutive video frames.
    @discussion This method returns the minimum amount of time that should seperate consecutive frames output by the receiver. This is equivalent to
    the inverse of the maximum frame rate. A value of 0 indicates an unlimited maximum frame rate. The default value is 0.
    @result An NSTimeInterval specifying the minimum interval between video frames. Returns 0 if there is no frame rate limit set.
*/
- (NSTimeInterval)minimumVideoFrameInterval AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
    @method setMinimumVideoFrameInterval:
    @abstract Sets the minimum time interval between which the receiver should output consecutive video frames.
    @discussion This method sets the minimum amount of time that should seperate consecutive frames output by the receiver. This is equivalent to the
    inverse of the maximum frame rate. A value of 0 indicates an unlimited maximum frame rate. The default value is 0.
    @param minimumVideoFrameInterval An NSTimeInterval specifying the minimum interval between video frames. A value of 0 indicates that there should
    be no frame rate limit.
*/
- (void)setMinimumVideoFrameInterval:(NSTimeInterval)minimumVideoFrameInterval AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
 @method automaticallyDropsLateVideoFrames
 @abstract Returns whether the receiver discards video frames that are output before earlier frames have been processed.
 @discussion If this method returns YES, the receiver will discard frames that are queued up while the thread handling existing frames is
 blocked in the outputVideoFrame:withSampleBuffer:fromConnection: or the captureOutput:didOutputVideoFrame:withSampleBuffer:fromConnection:
 delegate method. The delegate method captureOutput:didDropVideoFrameWithSampleBuffer:fromConnection: will be called for each frame that is
 dropped. The default value is NO.
 @result This method returns YES if the receiver drops late video frames and returns NO otherwise.
 */
- (BOOL)automaticallyDropsLateVideoFrames AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
 @method setAutomaticallyDropsLateVideoFrames:
 @abstract Sets whether the receiver discards video frames that are output before earlier frames have been processed.
 @discussion Setting this to YES will cause the receiver to discard frames that are queued up while the thread handling existing frames is
 blocked in the outputVideoFrame:withSampleBuffer:fromConnection: or the captureOutput:didOutputVideoFrame:withSampleBuffer:fromConnection:
 delegate method. The delegate method captureOutput:didDropVideoFrameWithSampleBuffer:fromConnection: will be called for each frame that is
 dropped. The default value is NO.
 @param automaticallyDropsLateVideoFrames Whether the receiver should drop late video frames
 */
- (void)setAutomaticallyDropsLateVideoFrames:(BOOL)automaticallyDropsLateVideoFrames AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3 */

/*!
    @method delegate
    @abstract Returns the receiverÕs delegate..
*/
- (id)delegate AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
    @method setDelegate:
    @abstract Sets the receiverÕs delegate..
*/
- (void)setDelegate:(id)delegate AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

/*!
    @method outputVideoFrame:withSampleBuffer:fromConnection:
    @abstract Called whenever the receiver outputs a new video frame.
    @discussion This method should not be invoked directly. Subclasses can override this method to provide custom processing behavior for each frame.
    The default implementation calls the delegateÕs captureOutput:didOutputVideoFrame:withSampleBuffer:fromConnection: method. Subclasses should not
    assume that this method will be called on the main thread. In addition, this method is called periodically, so it must be efficient to prevent
    capture performance problems.
    @param videoFrame A Core Video image buffer containing the decompressed frame.
    @param sampleBuffer A sample buffer containing additional information about the frame, such as its presentation time.
    @param connection The connection from which the video was received.
*/
- (void)outputVideoFrame:(CVImageBufferRef)videoFrame withSampleBuffer:(QTSampleBuffer *)sampleBuffer fromConnection:(QTCaptureConnection *)connection AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

@interface NSObject	(QTCaptureDecompressedVideoOutput_Delegate)

/*!
    @method captureOutput:didOutputVideoFrame:withSampleBuffer:fromConnection:
    @abstract This method is called whenever the decompressed video video output outputs a new video frame.
    @discussion Delegates receive this message whenever the output decompresses and outputs a new video frame. Delegates can use the provided video
    frame for a custom preview or for further image processing. Delegates should not assume that this method will be called on the main thread. In
    addition, this method is called periodically, so it must be efficient to prevent capture performance problems.
    @param captureOutput The QTCaptureDecompressedVideoOutput instance that output the frame.
    @param videoFrame A Core Video image buffer containing the decompressed frame.
    @param sampleBuffer A sample buffer containing additional information about the frame, such as its presentation time..
    @param connection The connection from which the video was received.
*/
- (void)captureOutput:(QTCaptureOutput *)captureOutput didOutputVideoFrame:(CVImageBufferRef)videoFrame withSampleBuffer:(QTSampleBuffer *)sampleBuffer fromConnection:(QTCaptureConnection *)connection AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3
/*!
    @method captureOutput:didDropVideoFrameWithSampleBuffer:fromConnection:
    @abstract This method is called once for each frame that is dropped when automaticallyDropsLateVideoFrames is set to YES.
    @discussion When automaticallyDropsLateVideoFrames is set to YES, this method is called whenever a late video frame is dropped. This method is
    called once for each dropped frame and may be called before the call to the outputVideoFrame:withSampleBuffer:fromConnection: or the
    captureOutput:didOutputVideoFrame:withSampleBuffer:fromConnection: delegate method during which those frames were dropped returns. The
    QTSampleBuffer object passed to this delegate method will contain metadata about the dropped video frame, such as its duration and presentation
    time stamp, but will contain no actual video data. Delegates should not assume that this method will be called on the main thread. Because this
    method may be called on the same thread that is responsible for outputting video frames, it must be efficient to prevent further capture
    performance problems, such as additional dropped video frames.
    @param captureOutput The QTCaptureDecompressedVideoOutput instance that dropped the late video frame.
    @param sampleBuffer A QTSampleBuffer instance contaaining metadata about the dropped frame, such as its duration and presentation time stamp.
    This sample buffer will contain none of the original video data, therefpre its bytesForAllSamples method will return NULL.
    @param connection The connection from which the dropped video frame was received.
*/
- (void)captureOutput:(QTCaptureOutput *)captureOutput didDropVideoFrameWithSampleBuffer:(QTSampleBuffer *)sampleBuffer fromConnection:(QTCaptureConnection *)connection AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3 */

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

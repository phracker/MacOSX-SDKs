/*
	File:		QTCaptureDecompressedVideoOutput.h
 
	Copyright:	(c)2007 by Apple Inc., all rights reserved.

 */

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

#import <QTKit/QTCaptureOutput.h>
#import <QuartzCore/QuartzCore.h>

@class QTCaptureConnection;
@class QTSampleBuffer;
@class QTCaptureDecompressedVideoOutputInternal;

@interface QTCaptureDecompressedVideoOutput : QTCaptureOutput {
@private
#if __LP64__
	int32_t										_delegateProxy;
#endif
#if !__LP64__
	QTCaptureDecompressedVideoOutputInternal	*_internal;
#endif	
	id											_delegate;

	long										_reserved4;
	long										_reserved5;
	long										_reserved6;
}
	
- (NSDictionary *)pixelBufferAttributes;
- (void)setPixelBufferAttributes:(NSDictionary *)pixelBufferAttributes;
	
- (id)delegate;
- (void)setDelegate:(id)delegate;

#if !__LP64__
// To be overridden by subclasses - do not invoke directly
- (void)outputVideoFrame:(CVImageBufferRef)videoFrame withSampleBuffer:(QTSampleBuffer *)sampleBuffer fromConnection:(QTCaptureConnection *)connection;
#endif

@end

@interface NSObject	(QTCaptureDecompressedVideoOutputDelegate)

- (void)captureOutput:(QTCaptureOutput *)captureOutput didOutputVideoFrame:(CVImageBufferRef)videoFrame withSampleBuffer:(QTSampleBuffer *)sampleBuffer fromConnection:(QTCaptureConnection *)connection;

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

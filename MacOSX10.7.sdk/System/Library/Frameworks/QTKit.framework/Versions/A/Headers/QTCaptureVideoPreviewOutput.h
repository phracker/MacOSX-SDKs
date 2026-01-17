/*
	File:		QTCaptureVideoPreviewOutput.h
 
	Copyright:	(c)2007-2010 by Apple Inc., all rights reserved.

 */

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

#import <QTKit/QTCaptureOutput.h>
#if !__LP64__
	#include <QuickTime/QuickTime.h>
#endif
#import <QuartzCore/QuartzCore.h>

@class QTCaptureVideoPreviewOutputInternal;

@class QTCaptureConnection;
@class QTSampleBuffer;

@interface QTCaptureVideoPreviewOutput : QTCaptureOutput {
@private
	QTCaptureVideoPreviewOutputInternal	*_internal;
	__weak id							_delegate;

	long								_reserved4;
}

- (NSDictionary *)pixelBufferAttributes;
- (void)setPixelBufferAttributes:(NSDictionary *)pixelBufferAttributes;	

#if !__LP64__
- (QTVisualContextRef)visualContextForConnection:(QTCaptureConnection *)connection;
- (void)setVisualContext:(QTVisualContextRef)visualContext forConnection:(QTCaptureConnection *)connection;
#endif

- (id)delegate;
- (void)setDelegate:(id)delegate;

// To be overridden by subclasses - do not invoke directly
- (void)outputVideoFrame:(CVImageBufferRef)videoFrame withSampleBuffer:(QTSampleBuffer *)sampleBuffer fromConnection:(QTCaptureConnection *)connection;

@end

@interface NSObject	(QTCaptureVideoPreviewOutput_Delegate)

- (void)captureOutput:(QTCaptureOutput *)captureOutput didOutputVideoFrame:(CVImageBufferRef)videoFrame withSampleBuffer:(QTSampleBuffer *)sampleBuffer fromConnection:(QTCaptureConnection *)connection;

@end

#endif	/* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

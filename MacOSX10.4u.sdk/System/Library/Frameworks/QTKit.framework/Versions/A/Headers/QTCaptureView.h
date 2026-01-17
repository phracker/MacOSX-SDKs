/*
	File:		QTCaptureView.h

	Copyright:	(c)2007 by Apple Inc., all rights reserved.

*/

#import <Cocoa/Cocoa.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

@class QTCaptureSession;
@class QTCaptureConnection;

@class QTCaptureViewInternal;

@class CIImage;

@interface QTCaptureView : NSView {
@private
#if __LP64__
	int32_t							_proxy;
	int32_t							_delegateProxy;
#endif
	QTCaptureViewInternal			*_internal;

	long							_reserved1;
	long							_reserved2;
	long							_reserved3;
}

- (QTCaptureSession *)captureSession;
- (void)setCaptureSession:(QTCaptureSession *)captureSession;

// If there are multiple video connections that can be previewed, these methods determine which the view will display.
- (NSArray *)availableVideoPreviewConnections;
- (QTCaptureConnection *)videoPreviewConnection;
- (void)setVideoPreviewConnection:(QTCaptureConnection *)videoPreviewConnection;

- (NSColor *)fillColor;
- (void)setFillColor:(NSColor *)fillColor;
- (BOOL)preservesAspectRatio;
- (void)setPreservesAspectRatio:(BOOL)preservesAspectRatio;

- (NSRect)previewBounds;	// Subclasses can override this method to provide custom preview bounds

- (id)delegate;
- (void)setDelegate:(id)delegate;

@end

@interface NSObject (QTCaptureViewDelegate)
- (CIImage *)view:(QTCaptureView *)view willDisplayImage:(CIImage *)image;
@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

/*
	File:		QTCaptureLayer.h
 
	Copyright:	(c)2007 by Apple Computer, Inc., all rights reserved.
 
*/
#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

#import <QuartzCore/QuartzCore.h>

@class QTCaptureSession;

@interface QTCaptureLayer : CALayer								// QTCaptureLayer is a layer that renders a capture session within a layer hierarchy
{
@private
	struct QTCaptureLayerPrivate *	_captureLayerPriv;
}

+ (id)layerWithSession:(QTCaptureSession *)session;
- (id)initWithSession:(QTCaptureSession *)session;				// the designated initializer

- (void)setSession:(QTCaptureSession *)session;
- (QTCaptureSession *)session;

@end
#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5) */

/*
	File:		QTCaptureLayer.h
 
	Copyright:	(c)2007-2010 by Apple Inc., all rights reserved.
 
*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

#import <QuartzCore/QuartzCore.h>

@class QTCaptureSession;
@class QTCaptureLayerPrivate;

@interface QTCaptureLayer : CALayer								// QTCaptureLayer is a layer that renders a capture session within a layer hierarchy
{
@private
	QTCaptureLayerPrivate	*_captureLayerPriv;
}

+ (id)layerWithSession:(QTCaptureSession *)session;
- (id)initWithSession:(QTCaptureSession *)session;				// the designated initializer

- (void)setSession:(QTCaptureSession *)session;
- (QTCaptureSession *)session;

@end
#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5) */

/*
	File:		QTCaptureDeviceInput.h

	Copyright:	(c)2007-2010 by Apple Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

#import <QTKit/QTCaptureInput.h>

@class QTCaptureDevice;

@class QTCaptureDeviceInputInternal;

@interface QTCaptureDeviceInput : QTCaptureInput {
@private;
	QTCaptureDeviceInputInternal *_internal;
	long						_reserved4;
	long						_reserved5;
	long						_reserved6;
}

+ (id)deviceInputWithDevice:(QTCaptureDevice *)device;
- (id)initWithDevice:(QTCaptureDevice *)device;

- (QTCaptureDevice *)device;

@end

#endif	/* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

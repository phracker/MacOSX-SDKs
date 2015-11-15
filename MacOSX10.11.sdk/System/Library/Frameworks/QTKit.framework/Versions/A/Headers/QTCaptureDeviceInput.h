/*
	File:		QTCaptureDeviceInput.h

	Copyright:	(c)2007-2012 by Apple Inc., all rights reserved.

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

+ (id)deviceInputWithDevice:(QTCaptureDevice *)device AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (id)initWithDevice:(QTCaptureDevice *)device AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

- (QTCaptureDevice *)device AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

#endif	/* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

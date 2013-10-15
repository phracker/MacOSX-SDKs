/*
	File:		QTCaptureInput.h

	Copyright:	(c)2007 by Apple Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

@class QTCaptureSession;

@interface QTCaptureInput : NSObject {
@private
#if __LP64__
	int32_t						_proxy;
#else
	QTCaptureSession * __weak	_session;
#endif
	long						_reserved1;
	long						_reserved2;
	long						_reserved3;
}

- (NSArray *)connections;

@end

#endif	/* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

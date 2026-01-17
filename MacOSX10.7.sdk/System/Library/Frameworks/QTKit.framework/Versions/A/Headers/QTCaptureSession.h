/*
	File:		QTCaptureSession.h

	Copyright:	(c)2007-2010 by Apple Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

// notifications
QTKIT_EXTERN NSString * const QTCaptureSessionRuntimeErrorNotification  AVAILABLE_QTKIT_VERSION_7_2_AND_LATER;
QTKIT_EXTERN NSString * const QTCaptureSessionErrorKey                  AVAILABLE_QTKIT_VERSION_7_2_AND_LATER;

@class QTCaptureConnection;
@class QTCaptureInput;
@class QTCaptureOutput;

@class QTCaptureSessionInternal;
@class QTCaptureSessionInternalState;

@interface QTCaptureSession : NSObject {
@private
	QTCaptureSessionInternal		*_internal;
	QTCaptureSessionInternalState	*_internalState;
	long							_reserved1;
	long							_reserved2;
	long							_reserved3;
}

- (NSArray *)inputs;
- (BOOL)addInput:(QTCaptureInput *)input error:(NSError **)errorPtr;
- (void)removeInput:(QTCaptureInput *)input;

- (NSArray *)outputs;
- (BOOL)addOutput:(QTCaptureOutput *)output error:(NSError **)errorPtr;
- (void)removeOutput:(QTCaptureOutput *)output;

- (BOOL)isRunning;
- (void)startRunning;
- (void)stopRunning;

@end

#endif	/* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

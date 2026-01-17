/*
	File:		QTError.h
 
	Copyright:	(c)2007 by Apple Inc., all rights reserved.
 
*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2

QTKIT_EXTERN NSString * const QTKitErrorDomain							AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

QTKIT_EXTERN NSString * const QTErrorCaptureInputKey					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTErrorCaptureOutputKey					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTErrorDeviceKey							AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTErrorExcludingDeviceKey					AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
QTKIT_EXTERN NSString * const QTErrorRecordingSuccesfullyFinishedKey	AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

enum {
	QTErrorUnknown									= -1,
	QTErrorIncompatibleInput						= 1002,
	QTErrorIncompatibleOutput						= 1003,
	QTErrorInvalidInputsOrOutputs					= 1100,
	QTErrorDeviceAlreadyUsedbyAnotherSession		= 1101,
	QTErrorNoDataCaptured							= 1200,
	QTErrorSessionConfigurationChanged				= 1201,
	QTErrorDiskFull									= 1202,
	QTErrorDeviceWasDisconnected					= 1203,
	QTErrorMediaChanged								= 1204,
	QTErrorMaximumDurationReached					= 1205,
	QTErrorMaximumFileSizeReached					= 1206,
	QTErrorMediaDiscontinuity						= 1207,
	QTErrorDeviceNotConnected						= 1300,
	QTErrorDeviceInUseByAnotherApplication			= 1301,
	QTErrorDeviceExcludedByAnotherDevice			= 1302,
};

#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */

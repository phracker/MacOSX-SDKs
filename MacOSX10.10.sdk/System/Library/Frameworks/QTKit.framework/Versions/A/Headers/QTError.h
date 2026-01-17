/*
	File:		QTError.h
 
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

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2

QTKIT_EXTERN NSString * const QTKitErrorDomain							AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

QTKIT_EXTERN NSString * const QTErrorCaptureInputKey					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTErrorCaptureOutputKey					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTErrorDeviceKey							AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTErrorExcludingDeviceKey					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
QTKIT_EXTERN NSString * const QTErrorTimeKey							AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;  // NSValue interpreted as QTTime
QTKIT_EXTERN NSString * const QTErrorFileSizeKey						AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;  // NSNumber interpreted as file size in bytes
QTKIT_EXTERN NSString * const QTErrorRecordingSuccesfullyFinishedKey	AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7;
QTKIT_EXTERN NSString * const QTErrorRecordingSuccessfullyFinishedKey	AVAILABLE_QTKIT_VERSION_7_7_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

enum {
	QTErrorUnknown                                      = -1,
	QTErrorIncompatibleInput                            = 1002,
	QTErrorIncompatibleOutput                           = 1003,
	QTErrorInvalidInputsOrOutputs                       = 1100,
	QTErrorDeviceAlreadyUsedbyAnotherSession            = 1101,
	QTErrorNoDataCaptured                               = 1200,
	QTErrorSessionConfigurationChanged                  = 1201,
	QTErrorDiskFull                                     = 1202,
	QTErrorDeviceWasDisconnected                        = 1203,
	QTErrorMediaChanged                                 = 1204,
	QTErrorMaximumDurationReached                       = 1205,
	QTErrorMaximumFileSizeReached                       = 1206,
	QTErrorMediaDiscontinuity                           = 1207,
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3
    QTErrorMaximumNumberOfSamplesForFileFormatReached   = 1208,
#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3 */
	QTErrorDeviceNotConnected                           = 1300,
	QTErrorDeviceInUseByAnotherApplication              = 1301,
	QTErrorDeviceExcludedByAnotherDevice                = 1302,
	QTErrorInvalidDestinationFileTypeForExport			= 1501,
	QTErrorInvalidSourceFileTypeForExport				= 1502,
	QTErrorExportExecutionFailed						= 1503,
	QTErrorExportInsufficientSpaceOnDevice				= 1504,
	QTErrorExportNoSuchDirectoryOrFile					= 1505,
	QTErrorExportIOError								= 1506,
};

#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */

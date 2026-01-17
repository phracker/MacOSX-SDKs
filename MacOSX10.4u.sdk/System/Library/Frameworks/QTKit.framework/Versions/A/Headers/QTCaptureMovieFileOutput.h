/*
	File:		QTCaptureMovieFileOutput.h

	Copyright:	(c)2007 by Apple Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4)

#import <QTKit/QTCaptureFileOutput.h>

/* This is a concrete subclass of QTCaptureFileOutput. See QTCaptureFileOutput.h for complete method declarations. */

@class QTCaptureMovieFileOutputInternal;

@interface QTCaptureMovieFileOutput : QTCaptureFileOutput {
@private
#if !__LP64__
	QTCaptureMovieFileOutputInternal		*_internal;
#endif
	long									_reserved8;
}

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

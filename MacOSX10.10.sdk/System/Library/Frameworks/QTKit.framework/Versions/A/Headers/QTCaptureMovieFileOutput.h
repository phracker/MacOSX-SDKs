/*
	File:		QTCaptureMovieFileOutput.h

	Copyright:	(c)2008-2012 by Apple Inc., all rights reserved.

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

#import <QTKit/QTCaptureFileOutput.h>

/* This is a concrete subclass of QTCaptureFileOutput. See QTCaptureFileOutput.h for complete method declarations. */

@class QTCaptureMovieFileOutputInternal;

@interface QTCaptureMovieFileOutput : QTCaptureFileOutput {
@private
	QTCaptureMovieFileOutputInternal		*_internal;
	long									_reserved8;
}

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4) */

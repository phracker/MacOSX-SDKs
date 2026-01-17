/*
	File:		QTMovieLayer.h

	Copyright:	(c)2005-2012 by Apple Inc., all rights reserved.

*/

/*
  QTKit has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.  In order to transition your 
  project from QTKit to AVFoundation please refer to:
  "Technical Note TN2300 Transitioning QTKit code to AV Foundation".
*/

/* Note: do not attempt to directly modify the `contents' property of
 * an QTMovieLayer object - doing so will effectively turn it into a
 * regular CALayer. */


#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

#import <QuartzCore/QuartzCore.h>

@class QTMovie;
@class QTMovieLayerPrivate;
@class QTInfoLayer;

@interface QTMovieLayer : CALayer								// QTMovieLayer is a layer that renders a QTMovie within a layer hierarchy
{
	@private
	QTMovieLayerPrivate *	_movieLayerPriv;
}

+ (id)layerWithMovie:(QTMovie *)movie AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (id)initWithMovie:(QTMovie *)movie AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;							// the designated initializer

- (void)setMovie:(QTMovie *)movie AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;
- (QTMovie *)movie AVAILABLE_QTKIT_VERSION_7_2_AND_LATER_BUT_DEPRECATED_IN_QTKIT_VERSION_7_7_3;

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5) */

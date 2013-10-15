/*
	File:		QTMovieLayer.h

	Copyright:	(c)2005-2007 by Apple Inc., all rights reserved.

*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

#import <QuartzCore/QuartzCore.h>

@class QTMovie;

@interface QTMovieLayer : CALayer								// QTMovieLayer is a layer that renders a QTMovie within a layer hierarchy
{
@private
	struct QTMovieLayerPrivate *	_movieLayerPriv;
}

+ (id)layerWithMovie:(QTMovie *)movie;
- (id)initWithMovie:(QTMovie *)movie;							// the designated initializer

- (void)setMovie:(QTMovie *)movie;
- (QTMovie *)movie;

@end

#endif /* (QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5) */

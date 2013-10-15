/*
 *	CTFramesetter.h
 *	CoreText
 *
 *	Copyright (c) 2003-2007 Apple Inc. All rights reserved.
 *
 */

#ifndef __CTFRAMESETTER__
#define __CTFRAMESETTER__

#include <CoreText/CTFrame.h>
#include <CoreText/CTTypesetter.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* --------------------------------------------------------------------------- */
/* Framesetter Types */
/* --------------------------------------------------------------------------- */

typedef const struct __CTFramesetter * CTFramesetterRef;


/*!
	@function	CTFramesetterGetTypeID
	@abstract	Returns the CFType of the framesetter object
*/

CFTypeID CTFramesetterGetTypeID( void ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* --------------------------------------------------------------------------- */
/* Framesetter Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTFramesetterCreateWithAttributedString
	@abstract	Creates an immutable framesetter object from an attributed
				string.

	@discussion The resultant framesetter object can be used to create and
				fill text frames with the CTFramesetterCreateFrame call.

	@param		string
				The run with which you want to construct the framesetter
				object with.

	@result		This function will return a reference to a CTFramesetter if
				the call was successful. Otherwise, it will return NULL.
*/

CTFramesetterRef CTFramesetterCreateWithAttributedString(
	CFAttributedStringRef string ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* --------------------------------------------------------------------------- */
/* Frame Creation */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTFramesetterCreateFrame
	@abstract	Creates an immutable frame from a framesetter.

	@discussion This call will create a frame full of glyphs in the shape of
				the path provided by the "path" parameter. The framesetter
				will continue to fill the frame until it either runs out of
				text or it finds that text no longer fits.

	@param		framesetter
				The framesetter that will be used to create the frame.

	@param		stringRange
				The string range which the new frame will be based on. The
				string range is a range over the string that was used to
				create the framesetter. If the length portion of the range
				is set to 0, then the framesetter will continue to add lines
				until it runs out of text or space.

	@param		path
				A CGPath object that specifies the shape which the frame will
				take on.

	@param		frameAttributes
				Additional attributes that control the frame filling process
				can be specified here, or NULL if there are no such attributes.

	@result		This function will return a reference to a new CTFrame object
				if the call was successful. Otherwise, it will return NULL.
*/

CTFrameRef CTFramesetterCreateFrame(
	CTFramesetterRef framesetter,
	CFRange stringRange,
	CGPathRef path,
	CFDictionaryRef frameAttributes ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@function	CTFramesetterGetTypesetter
	@abstract	Returns the typesetter object being used by the framesetter.

	@discussion Each framesetter uses a typesetter internally to perform
				line breaking and other contextual analysis based on the
				characters in a string; this function returns the typesetter
				being used by a particular framesetter if the caller would
				like to perform other operations on that typesetter.

	@param		framesetter
				The framesetter from which a typesetter is being requested.

	@result		This function will return a reference to a CTTypesetter
				object if the call was successful. Otherwise, it will return
				NULL. The framesetter maintains a reference to the returned
				object, which should not be disposed by the caller.
*/

CTTypesetterRef CTFramesetterGetTypesetter(
	CTFramesetterRef framesetter ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


#if defined(__cplusplus)
}
#endif

#endif

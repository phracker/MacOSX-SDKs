/*
 *	CTFrame.h
 *	CoreText
 *
 *	Copyright (c) 2003-2007 Apple Inc. All rights reserved.
 *
 */
 
#ifndef __CTFRAME__
#define __CTFRAME__

#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFString.h>
#include <CoreGraphics/CGContext.h>
#include <AvailabilityMacros.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* --------------------------------------------------------------------------- */
/* Frame Types */
/* --------------------------------------------------------------------------- */

typedef const struct __CTFrame * CTFrameRef;


/*!
	@function	CTFrameGetTypeID
	@abstract	Returns the CFType of the frame object
*/

CFTypeID CTFrameGetTypeID( void ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* --------------------------------------------------------------------------- */
/* Frame Values */
/* --------------------------------------------------------------------------- */

/*!
	@enum		CTFrameProgression
	@abstract	These constants specify frame progression types.
	
	@discussion The lines of text within a frame may be stacked for either
				horizontal or vertical text. Values are enumerated for each
				stacking type supported by CTFrame. Frames created with a
				progression type specifying vertical text will rotate lines
				90 degrees counterclockwise when drawing.
	
	@constant	kCTFrameProgressionTopToBottom
				Lines are stacked top to bottom for horizontal text.
	
	@constant	kCTFrameProgressionRightToLeft
				Lines are stacked right to left for vertical text.
*/

enum
{
	kCTFrameProgressionTopToBottom = 0,
	kCTFrameProgressionRightToLeft = 1
};
typedef uint32_t CTFrameProgression;


/*!
	@const		kCTFrameProgressionAttributeName
	@abstract	Specifies progression for a frame.
	
	@discussion Value must be a CFNumberRef containing a CTFrameProgression.
				Default is kCTFrameProgressionTopToBottom. This value determines
				the line stacking behavior for a frame and does not affect the
				appearance of the glyphs within that frame.
*/

extern const CFStringRef kCTFrameProgressionAttributeName AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* --------------------------------------------------------------------------- */
/* Frame Accessors */
/* --------------------------------------------------------------------------- */

/*!
	@function	CTFrameGetStringRange
	@abstract	Returns the range of characters that were originally requested
				to fill the frame.

	@param		frame
				The frame that you want to get the character range from.

	@result		This function will return a CFRange containing the backing
				store range of characters that were originally requested
				to fill the frame. If the function call is not successful,
				then an empty range will be returned.
*/

CFRange CTFrameGetStringRange(
	CTFrameRef frame ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@function	CTFrameGetVisibleStringRange
	@abstract	Returns the range of characters that actually fit in the
				frame.

	@discussion This can be used to cascade frames, as it returns the range of
				characters that can be seen in the frame. The next frame would
				start where this frame ends.

	@param		frame
				The frame that you want to get the visible character range
				from.

	@result		This function will return a CFRange containing the backing
				store range of characters that fit into the frame. If the
				function call is not successful, or if no characters fit
				in the frame, then an empty range will be returned.
*/

CFRange CTFrameGetVisibleStringRange(
	CTFrameRef frame ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@function	CTFrameGetPath
	@abstract	Returns the path used to create the frame.

	@param		frame
				The frame that you want to obtain the path from.
*/

CGPathRef CTFrameGetPath(
	CTFrameRef frame ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@function	CTFrameGetFrameAttributes
	@abstract	Returns the frame attributes used to create the frame.

	@discussion It is possible to create a frame with an attributes dictionary
				in order to control various aspects of the framing process.
				These attributes are different from the ones that are used to
				create an attributed string.

	@param		frame
				The frame that you want to obtain the frame attributes from.

	@result		This function will return a CFDictionary containing the
				frame attributes that were used to create the frame. If the
				frame was created without any frame attributes, this function
				will return NULL.
*/

CFDictionaryRef CTFrameGetFrameAttributes(
	CTFrameRef frame ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@function	CTFrameGetLines
	@abstract	Returns an array of lines that make up the frame.

	@discussion This function will return an array of CTLine objects that are
				stored in the frame. These line objects can be accessed and
				manipulated in any way that normal line objects can be. It is
				possible that an empty frame exists. That is, a frame in which
				no lines exist. In this case, the returned array will have 0
				entries.

	@param		frame
				The frame that you want to obtain the line array from.

	@result		This function will return a CFArray object containing the
				CTLine objects that make up the frame.
*/

CFArrayRef CTFrameGetLines(
	CTFrameRef frame ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@function	CTFrameGetLineOrigins
	@abstract	Copies a range of line origins for a frame.

	@discussion	This function will copy a range of CGPoint structures. Each
				CGPoint is the origin of the corresponding line in the array of
				lines returned by CTFrameGetLines, relative to the origin of the
				frame's path. The maximum number of line origins returned by
				this function is the count of the array of lines.

	@param		frame
				The frame that you want to obtain the line origin array from.

	@param		range
				The range of line origins you wish to copy. If the length of the
				range is set to 0, then the copy operation will continue from
				the range's start index to the last line origin.

	@param		origins
				The buffer to which the origins will be copied. The buffer must
				have at least as many elements as specified by range's length.
				When using the origins to calculate measurements for a frame's
				contents, remember that line origins do not always correspond to
				line metrics; paragraph style settings can affect line origins,
				for one. The overall typographic bounds of a frame may generally
				be calculated as the difference between the top of the frame and
				the descent of the last line. This will obviously exclude any
				spacing following the last line, but such spacing has no effect
				on framesetting in the first place.
*/

void CTFrameGetLineOrigins(
	CTFrameRef frame,
	CFRange range,
	CGPoint origins[] ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*!
	@function	CTFrameDraw
	@abstract	Draws an entire frame to a context.

	@discussion This function will draw an entire frame to the context. Note
				that this call may leave the context in any state and does not
				flush it after the draw operation.

	@param		frame
				The frame that you want to draw.

	@param		context
				The context to draw the frame to.

	@result		If both the frame and the context are valid, the frame will be
				drawn in the context.
*/

void CTFrameDraw(
	CTFrameRef frame,
	CGContextRef context ) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


#if defined(__cplusplus)
}
#endif

#endif

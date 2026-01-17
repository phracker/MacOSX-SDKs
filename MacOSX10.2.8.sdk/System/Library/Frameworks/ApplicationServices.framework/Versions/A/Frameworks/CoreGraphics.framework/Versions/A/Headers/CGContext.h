/* CoreGraphics - CGContext.h
 * Copyright (c) 2000 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGCONTEXT_H_
#define CGCONTEXT_H_
#define __CGCONTEXT__

typedef struct CGContext *CGContextRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGAffineTransform.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGFont.h>
#include <CoreGraphics/CGImage.h>
#include <CoreGraphics/CGPath.h>
#include <CoreGraphics/CGPattern.h>
#include <CoreGraphics/CGPDFDocument.h>
#include <CoreGraphics/CGShading.h>
#include <CoreFoundation/CFBase.h>
#include <limits.h>
#include <stddef.h>

CG_EXTERN_C_BEGIN

/* Line join styles. */

enum CGLineJoin {
    kCGLineJoinMiter,
    kCGLineJoinRound,
    kCGLineJoinBevel
};
typedef enum CGLineJoin CGLineJoin;

/* Line cap styles. */

enum CGLineCap {
    kCGLineCapButt,
    kCGLineCapRound,
    kCGLineCapSquare
};
typedef enum CGLineCap CGLineCap;

/* Drawing modes for paths. */

enum CGPathDrawingMode {
    kCGPathFill,
    kCGPathEOFill,
    kCGPathStroke,
    kCGPathFillStroke,
    kCGPathEOFillStroke
};
typedef enum CGPathDrawingMode CGPathDrawingMode;

/* Drawing modes for text. */

enum CGTextDrawingMode {
    kCGTextFill,
    kCGTextStroke,
    kCGTextFillStroke,
    kCGTextInvisible,
    kCGTextFillClip,
    kCGTextStrokeClip,
    kCGTextFillStrokeClip,
    kCGTextClip
};
typedef enum CGTextDrawingMode CGTextDrawingMode;

/* Text encodings. */

enum CGTextEncoding {
    kCGEncodingFontSpecific,
    kCGEncodingMacRoman
};
typedef enum CGTextEncoding CGTextEncoding;

enum CGInterpolationQuality {
    kCGInterpolationDefault,		/* Let the context decide. */
    kCGInterpolationNone,		/* Never interpolate. */
    kCGInterpolationLow,		/* Fast, low quality. */
    kCGInterpolationHigh		/* Slow, high quality. */
};
typedef enum CGInterpolationQuality CGInterpolationQuality;

/* Return the CFTypeID for CGContextRefs. */

CG_EXTERN CFTypeID CGContextGetTypeID(void);

/** Graphics state functions. **/

/* Push a copy of the current graphics state onto the graphics state
 * stack. Note that the path is not considered part of the gstate, and is
 * not saved. */

CG_EXTERN void CGContextSaveGState(CGContextRef c);

/* Restore the current graphics state from the one on the top of the
 * graphics state stack, popping the graphics state stack in the
 * process. */

CG_EXTERN void CGContextRestoreGState(CGContextRef c);

/** Coordinate space transformations. **/

/* Scale the current graphics state's transformation matrix (the CTM) by
 * `(sx, sy)'. */

CG_EXTERN void CGContextScaleCTM(CGContextRef c, float sx, float sy);

/* Translate the current graphics state's transformation matrix (the CTM)
 * by `(tx, ty)'. */

CG_EXTERN void CGContextTranslateCTM(CGContextRef c, float tx, float ty);

/* Rotate the current graphics state's transformation matrix (the CTM) by
 * `angle' radians. */

CG_EXTERN void CGContextRotateCTM(CGContextRef c, float angle);

/* Concatenate the current graphics state's transformation matrix (the CTM)
 * with the affine transform `transform'. */

CG_EXTERN void CGContextConcatCTM(CGContextRef c, CGAffineTransform transform);

/* Return the current graphics state's transformation matrix. */

CG_EXTERN CGAffineTransform CGContextGetCTM(CGContextRef c);

/** Drawing attribute functions. **/

/* Set the line width in the current graphics state to `width'. */

CG_EXTERN void CGContextSetLineWidth(CGContextRef c, float width);

/* Set the line cap in the current graphics state to `cap'. */

CG_EXTERN void CGContextSetLineCap(CGContextRef c, CGLineCap cap);

/* Set the line join in the current graphics state to `join'. */

CG_EXTERN void CGContextSetLineJoin(CGContextRef c, CGLineJoin join);

/* Set the miter limit in the current graphics state to `limit'. */

CG_EXTERN void CGContextSetMiterLimit(CGContextRef c, float limit);

/* Set the line dash patttern in the current graphics state. */

CG_EXTERN void CGContextSetLineDash(CGContextRef c, float phase, const float lengths[], size_t count);

/* Set the path flatness parameter in the current graphics state to
 * `flatness'. */

CG_EXTERN void CGContextSetFlatness(CGContextRef c, float flatness);

/* Set the alpha value in the current graphics state to `alpha'. */

CG_EXTERN void CGContextSetAlpha(CGContextRef c, float alpha);

/** Path construction functions. **/

/* Note that a context has a single path in use at any time: a path is not
 * part of the graphics state. */

/* Begin a new path.  The old path is discarded. */

CG_EXTERN void CGContextBeginPath(CGContextRef c);

/* Start a new subpath at point `(x, y)' in the context's path. */

CG_EXTERN void CGContextMoveToPoint(CGContextRef c, float x, float y);

/* Append a straight line segment from the current point to `(x, y)'. */

CG_EXTERN void CGContextAddLineToPoint(CGContextRef c, float x, float y);

/* Append a cubic Bezier curve from the current point to `(x,y)', with
 * control points `(cp1x, cp1y)' and `(cp2x, cp2y)'. */

CG_EXTERN void CGContextAddCurveToPoint(CGContextRef c, float cp1x, float cp1y, float cp2x, float cp2y, float x, float y);

/* Append a quadratic curve from the current point to `(x, y)', with
 * control point `(cpx, cpy)'. */

CG_EXTERN void CGContextAddQuadCurveToPoint(CGContextRef c, float cpx, float cpy, float x, float y);

/* Close the current subpath of the context's path. */

CG_EXTERN void CGContextClosePath(CGContextRef c);

/** Path construction convenience functions. **/

/* Add a single rect to the context's path. */

CG_EXTERN void CGContextAddRect(CGContextRef c, CGRect rect);

/* Add a set of rects to the context's path. */

CG_EXTERN void CGContextAddRects(CGContextRef c, const CGRect rects[], size_t count);

/* Add a set of lines to the context's path. */

CG_EXTERN void CGContextAddLines(CGContextRef c, const CGPoint points[], size_t count);

/* Add an arc of a circle to the context's path, possibly preceded by a
 * straight line segment.  `(x, y)' is the center of the arc; `radius' is
 * its radius; `startAngle' is the angle to the first endpoint of the arc;
 * `endAngle' is the angle to the second endpoint of the arc; and
 * `clockwise' is 1 if the arc is to be drawn clockwise, 0 otherwise.
 * `startAngle' and `endAngle' are measured in radians. */

CG_EXTERN void CGContextAddArc(CGContextRef c, float x, float y, float radius, float startAngle, float endAngle, int clockwise);

/* Add an arc of a circle to the context's path, possibly preceded by a
 * straight line segment.  `radius' is the radius of the arc.  The arc is
 * tangent to the line from the current point to `(x1, y1)', and the line
 * from `(x1, y1)' to `(x2, y2)'. */

CG_EXTERN void CGContextAddArcToPoint(CGContextRef c, float x1, float y1, float x2, float y2, float radius);

/* Add `path' to the path of context.  The points in `path' are transformed
 * by the CTM of context before they are added. */

CG_EXTERN void CGContextAddPath(CGContextRef context, CGPathRef path);

/** Path information functions. **/

/* Return 1 if the context's path contains no elements, 0 otherwise. */

CG_EXTERN int CGContextIsPathEmpty(CGContextRef c);

/* Return the current point of the current subpath of the context's
 * path. */

CG_EXTERN CGPoint CGContextGetPathCurrentPoint(CGContextRef c);

/* Return the bounding box of the context's path.  The bounding box is the
 * smallest rectangle completely enclosing all points in the path,
 * including control points for Bezier and quadratic curves. */

CG_EXTERN CGRect CGContextGetPathBoundingBox(CGContextRef c);

/** Path drawing functions. **/

/* Draw the context's path using drawing mode `mode'. */

CG_EXTERN void CGContextDrawPath(CGContextRef c, CGPathDrawingMode mode);

/** Path drawing convenience functions. **/

/* Fill the context's path using the winding-number fill rule.  Any open
 * subpath of the path is implicitly closed. */

CG_EXTERN void CGContextFillPath(CGContextRef c);

/* Fill the context's path using the even-odd fill rule.  Any open subpath
 * of the path is implicitly closed. */

CG_EXTERN void CGContextEOFillPath(CGContextRef c);

/* Stroke the context's path. */

CG_EXTERN void CGContextStrokePath(CGContextRef c);

/* Fill `rect' with the current fill color. */

CG_EXTERN void CGContextFillRect(CGContextRef c, CGRect rect);

/* Fill `rects', an array of `count' CGRects, with the current fill
 * color. */

CG_EXTERN void CGContextFillRects(CGContextRef c, const CGRect rects[], size_t count);

/* Stroke `rect' with the current stroke color and the current linewidth. */

CG_EXTERN void CGContextStrokeRect(CGContextRef c, CGRect rect);

/* Stroke `rect' with the current stroke color, using `width' as the the
 * line width. */

CG_EXTERN void CGContextStrokeRectWithWidth(CGContextRef c, CGRect rect, float width);

/* Clear `rect' (that is, set the region within the rect to
 * transparent). */

CG_EXTERN void CGContextClearRect(CGContextRef c, CGRect rect);

/** Clipping functions. **/

/* Intersect the context's path with the current clip path and use the
 * resulting path as the clip path for subsequent rendering operations.
 * Use the winding-number fill rule for deciding what's inside the path. */

CG_EXTERN void CGContextClip(CGContextRef c);

/* Intersect the context's path with the current clip path and use the
 * resulting path as the clip path for subsequent rendering operations.
 * Use the even-odd fill rule for deciding what's inside the path. */

CG_EXTERN void CGContextEOClip(CGContextRef c);

/** Clipping convenience functions. **/

/* Intersect the current clipping path with `rect'.  Note that this
 * function resets the context's path to the empty path. */

CG_EXTERN void CGContextClipToRect(CGContextRef c, CGRect rect);

/* Intersect the current clipping path with the clipping region formed by
 * creating a path consisting of all rects in `rects'.  Note that this
 * function resets the context's path to the empty path. */

CG_EXTERN void CGContextClipToRects(CGContextRef c, const CGRect rects[], size_t count);

/** Colorspace functions. **/

/* Set the current fill colorspace in the context `c' to `colorspace'.  As
 * a side-effect, set the fill color to a default value appropriate for the
 * colorspace. */

CG_EXTERN void CGContextSetFillColorSpace(CGContextRef c, CGColorSpaceRef colorspace);

/* Set the current stroke colorspace in the context `c' to `colorspace'.
 * As a side-effect, set the stroke color to a default value appropriate
 * for the colorspace. */

CG_EXTERN void CGContextSetStrokeColorSpace(CGContextRef c, CGColorSpaceRef colorspace);

/** Color functions. **/

/* Set the components of the current fill color in the context `c' to the
 * values specifed by `components'.  The number of elements in `components'
 * must be one greater than the number of components in the current fill
 * colorspace (N color components + 1 alpha component).  The current fill
 * colorspace must not be a pattern colorspace. */

CG_EXTERN void CGContextSetFillColor(CGContextRef c, const float components[]);

/* Set the components of the current stroke color in the context `c' to the
 * values specifed by `components'.  The number of elements in `components'
 * must be one greater than the number of components in the current stroke
 * colorspace (N color components + 1 alpha component).  The current stroke
 * colorspace must not be a pattern colorspace. */

CG_EXTERN void CGContextSetStrokeColor(CGContextRef c, const float components[]);

/** Pattern functions. **/

/* Set the components of the current fill color in the context `c' to the
 * values specifed by `components', and set the current fill pattern to
 * `pattern'.  The number of elements in `components' must be one greater
 * than the number of components in the current fill colorspace (N color
 * components + 1 alpha component).  The current fill colorspace must be a
 * pattern colorspace. */

CG_EXTERN void CGContextSetFillPattern(CGContextRef c, CGPatternRef pattern, const float components[]);

/* Set the components of the current stroke color in the context `c' to the
 * values specifed by `components', and set the current stroke pattern to
 * `pattern'.  The number of elements in `components' must be one greater
 * than the number of components in the current stroke colorspace (N color
 * components + 1 alpha component).  The current stroke colorspace must be
 * a pattern colorspace. */

CG_EXTERN void CGContextSetStrokePattern(CGContextRef c, CGPatternRef pattern, const float components[]);

/* Set the pattern phase of context `c' to `phase'. */

CG_EXTERN void CGContextSetPatternPhase(CGContextRef c, CGSize phase);

/** Color convenience functions. **/

/* Set the current fill colorspace in the context `c' to `DeviceGray' and
 * set the components of the current fill color to `(gray, alpha)'. */

CG_EXTERN void CGContextSetGrayFillColor(CGContextRef c, float gray, float alpha);

/* Set the current stroke colorspace in the context `c' to `DeviceGray' and
 * set the components of the current stroke color to `(gray, alpha)'. */

CG_EXTERN void CGContextSetGrayStrokeColor(CGContextRef c, float gray, float alpha);

/* Set the current fill colorspace in the context `c' to `DeviceRGB' and
 * set the components of the current fill color to `(red, green, blue,
 * alpha)'. */

CG_EXTERN void CGContextSetRGBFillColor(CGContextRef c, float red, float green, float blue, float alpha);

/* Set the current stroke colorspace in the context `c' to `DeviceRGB' and
 * set the components of the current stroke color to `(red, green, blue,
 * alpha)'. */

CG_EXTERN void CGContextSetRGBStrokeColor(CGContextRef c, float red, float green, float blue, float alpha);

/* Set the current fill colorspace in the context `c' to `DeviceCMYK' and
 * set the components of the current fill color to `(cyan, magenta, yellow,
 * black, alpha)'. */

CG_EXTERN void CGContextSetCMYKFillColor(CGContextRef c, float cyan, float magenta, float yellow, float black, float alpha);

/* Set the current stroke colorspace in the context `c' to `DeviceCMYK' and
 * set the components of the current stroke color to `(cyan, magenta,
 * yellow, black, alpha)'. */

CG_EXTERN void CGContextSetCMYKStrokeColor(CGContextRef c, float cyan, float magenta, float yellow, float black, float alpha);

/** Rendering intent. **/

/* Set the current rendering intent in the context `c' to `intent'. */

CG_EXTERN void CGContextSetRenderingIntent(CGContextRef c, CGColorRenderingIntent intent);

/** Image functions. **/

/* Draw `image' in the rectangular area specified by `rect' in the context
 * `c'.  The image is scaled, if necessary, to fit into `rect'. */

CG_EXTERN void CGContextDrawImage(CGContextRef c, CGRect rect, CGImageRef image);

/* Return the interpolation quality for image rendering of the context `c'.
 * The interpolation quality is a gstate-parameter which controls the level
 * of interpolation performed when an image is interpolated (for example,
 * when scaling the image). Note that it is merely a hint to the context:
 * not all contexts support all interpolation quality levels. */

CG_EXTERN CGInterpolationQuality CGContextGetInterpolationQuality(CGContextRef c);

/* Set the interpolation quality of the context `c' to `quality'. */

CG_EXTERN void CGContextSetInterpolationQuality(CGContextRef c, CGInterpolationQuality quality);

/** Shading functions. **/

/* Fill the current clipping region of `c' with `shading'. */

CG_EXTERN void CGContextDrawShading(CGContextRef c, CGShadingRef shading);

/** Text functions. **/

/* Set the current character spacing in the context `c' to `spacing'.  The
 * character spacing is added to the displacement between the origin of one
 * character and the origin of the next. */

CG_EXTERN void CGContextSetCharacterSpacing(CGContextRef c, float spacing);

/* Set the user-space point at which text will be drawn in the context `c'
 * to `(x, y)'. */

CG_EXTERN void CGContextSetTextPosition(CGContextRef c, float x, float y);

/* Return the user-space point at which text will be drawn in the context
 * `c'. */

CG_EXTERN CGPoint CGContextGetTextPosition(CGContextRef c);

/* Set the text matrix in the context `c' to `t'. */

CG_EXTERN void CGContextSetTextMatrix(CGContextRef c, CGAffineTransform t);

/* Return the text matrix in the context `c'. */

CG_EXTERN CGAffineTransform CGContextGetTextMatrix(CGContextRef c);

/* Set the current text drawing mode in the context `c' to `mode'. */

CG_EXTERN void CGContextSetTextDrawingMode(CGContextRef c, CGTextDrawingMode mode);

/* Set the current font in the context `c' to `font'. */

CG_EXTERN void CGContextSetFont(CGContextRef c, CGFontRef font);

/* Set the current font size in the context `c' to `size'. */

CG_EXTERN void CGContextSetFontSize(CGContextRef c, float size);

/* Attempts to find the font named `name' for the context `c'.  If
 * successful, scales it to `size' units in text space.  `textEncoding'
 * specifies how to translate from bytes to glyphs. */

CG_EXTERN void CGContextSelectFont(CGContextRef c, const char *name, float size, CGTextEncoding textEncoding);

/* Draw `string', a string of `length' bytes, at the point specified by the
 * text matrix in the context `c'.  Each byte of the string is mapped
 * through the encoding vector of the current font to obtain the glyph to
 * display. */

CG_EXTERN void CGContextShowText(CGContextRef c, const char *string, size_t length);

/* Draw the glyphs pointed to by `g', an array of `count' glyphs, at the
 * point specified by the text matrix in the context `c'. */

CG_EXTERN void CGContextShowGlyphs(CGContextRef c, const CGGlyph g[], size_t count);

/** Text convenience functions. **/

/* Draw `string', a string of `length' bytes, at the point `(x, y)',
 * specified in user space, in the context `c'.  Each byte of the string is
 * mapped through the encoding vector of the current font to obtain the
 * glyph to display. */

CG_EXTERN void CGContextShowTextAtPoint(CGContextRef c, float x, float y, const char *string, size_t length);

/* Display the glyphs pointed to by `glyphs', an array of `count' glyphs,
 * at at the point `(x, y)', specified in user space, in the context
 * `c'. */

CG_EXTERN void CGContextShowGlyphsAtPoint(CGContextRef c, float x, float y, const CGGlyph glyphs[], size_t count);

/** PDF document functions. **/

/* Draw `page' in `document' in the rectangular area specified by `rect' in
 * the context `c'.  The media box of the page is scaled, if necessary, to
 * fit into `rect'. */

CG_EXTERN void CGContextDrawPDFDocument(CGContextRef c, CGRect rect, CGPDFDocumentRef document, int page);

/** Page functions. **/

/* Begin a new page. */

CG_EXTERN void CGContextBeginPage(CGContextRef c, const CGRect *mediaBox);

/* End the current page. */

CG_EXTERN void CGContextEndPage(CGContextRef c);

/** Context functions. **/

/* Equivalent to `CFRetain(c)'. */

CG_EXTERN CGContextRef CGContextRetain(CGContextRef c);

/* Equivalent to `CFRelease(c)'. */

CG_EXTERN void CGContextRelease(CGContextRef c);

/* Flush all drawing to the destination. */

CG_EXTERN void CGContextFlush(CGContextRef c);

/* Synchronized drawing. */

CG_EXTERN void CGContextSynchronize(CGContextRef c);

/** Antialiasing functions. **/

/* Turn on antialiasing if `shouldAntialias' is true; turn it off
 * otherwise.  This parameter is part of the graphics state. */

CG_EXTERN void CGContextSetShouldAntialias(CGContextRef c, bool shouldAntialias);

/** Font smoothing functions. **/

/* Turn on font smoothing if `shouldSmoothFonts' is true; turn it off
 * otherwise.  This parameter is part of the graphics state. */

CG_EXTERN void CGContextSetShouldSmoothFonts(CGContextRef c, bool shouldSmoothFonts);

CG_EXTERN_C_END

#endif	/* CGCONTEXT_H_ */

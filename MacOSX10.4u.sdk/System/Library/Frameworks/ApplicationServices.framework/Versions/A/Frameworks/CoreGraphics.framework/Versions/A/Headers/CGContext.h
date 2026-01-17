/* CoreGraphics - CGContext.h
 * Copyright (c) 2000-2003 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGCONTEXT_H_
#define CGCONTEXT_H_

typedef struct CGContext *CGContextRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGAffineTransform.h>
#include <CoreGraphics/CGColor.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGFont.h>
#include <CoreGraphics/CGImage.h>
#include <CoreGraphics/CGPath.h>
#include <CoreGraphics/CGPattern.h>
#include <CoreGraphics/CGPDFDocument.h>
#include <CoreGraphics/CGShading.h>

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

/* Interpolation quality. */

enum CGInterpolationQuality {
    kCGInterpolationDefault,		/* Let the context decide. */
    kCGInterpolationNone,		/* Never interpolate. */
    kCGInterpolationLow,		/* Faster, lower quality. */
    kCGInterpolationHigh		/* Slower, higher quality. */
};
typedef enum CGInterpolationQuality CGInterpolationQuality;

/* Blend modes. */

enum CGBlendMode {
    kCGBlendModeNormal,
    kCGBlendModeMultiply,
    kCGBlendModeScreen,
    kCGBlendModeOverlay,
    kCGBlendModeDarken,
    kCGBlendModeLighten,
    kCGBlendModeColorDodge,
    kCGBlendModeColorBurn,
    kCGBlendModeSoftLight,
    kCGBlendModeHardLight,
    kCGBlendModeDifference,
    kCGBlendModeExclusion,
    kCGBlendModeHue,
    kCGBlendModeSaturation,
    kCGBlendModeColor,
    kCGBlendModeLuminosity
};
typedef enum CGBlendMode CGBlendMode; /* Available in Mac OS X 10.4 & later. */

CG_EXTERN_C_BEGIN

/* Return the CFTypeID for CGContextRefs. */

CG_EXTERN CFTypeID CGContextGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

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

/* Set the line dash patttern in the current graphics state of `c'. */

CG_EXTERN void CGContextSetLineDash(CGContextRef c, float phase, const float lengths[], size_t count);

/* Set the path flatness parameter in the current graphics state of `c' to
 * `flatness'. */

CG_EXTERN void CGContextSetFlatness(CGContextRef c, float flatness);

/* Set the alpha value in the current graphics state of `c' to `alpha'. */

CG_EXTERN void CGContextSetAlpha(CGContextRef c, float alpha);

/* Set the blend mode of `context' to `mode'. */

CG_EXTERN void CGContextSetBlendMode(CGContextRef context, CGBlendMode mode) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

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

/* Add an ellipse inside `rect' to the current path of `context'.  See the
 * function `CGPathAddEllipseInRect' for more information on how the path
 * for the ellipse is constructed. */

CG_EXTERN void CGContextAddEllipseInRect(CGContextRef context, CGRect rect) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

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

CG_EXTERN void CGContextAddPath(CGContextRef context, CGPathRef path) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/** Path stroking. **/

/* Replace the path in context with the stroked version of the path, using
 * the parameters of `context' to calculate the stroked path.  The
 * resulting path is created such that filling it with the appropriate
 * color will produce the same results as stroking the original path. You
 * can use this path in the same way you can use the path of any context;
 * for example, you can clip to the stroked version of a path by calling
 * this function followed by a call to "CGContextClipPath". */

CG_EXTERN void CGContextReplacePathWithStrokedPath(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Path information functions. **/

/* Return true if the context's path contains no elements, false otherwise. */

CG_EXTERN bool CGContextIsPathEmpty(CGContextRef c);

/* Return the current point of the current subpath of the context's
 * path. */

CG_EXTERN CGPoint CGContextGetPathCurrentPoint(CGContextRef c);

/* Return the bounding box of the context's path.  The bounding box is the
 * smallest rectangle completely enclosing all points in the path,
 * including control points for Bezier and quadratic curves. */

CG_EXTERN CGRect CGContextGetPathBoundingBox(CGContextRef c);

/* Return true if `point' is contained in the current path of `context'.  A
 * point is contained within a context's path if it is inside the painted
 * region when the path is stroked or filled with opaque colors using the
 * path drawing mode `mode'.  `point' is specified is user space. */

CG_EXTERN bool CGContextPathContainsPoint(CGContextRef context, CGPoint point, CGPathDrawingMode mode) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

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

/* Fill an ellipse (an oval) inside `rect'. */

CG_EXTERN void CGContextFillEllipseInRect(CGContextRef context, CGRect rect) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Stroke an ellipse (an oval) inside `rect'. */

CG_EXTERN void CGContextStrokeEllipseInRect(CGContextRef context, CGRect rect) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Stroke a sequence of line segments one after another in `context'.  The
 * line segments are specified by `points', an array of `count' CGPoints.
 * This function is equivalent to
 *   CGContextBeginPath(context);
 *   for (k = 0; k < count; k += 2) {
 *       CGContextMoveToPoint(context, s[k].x, s[k].y);
 *       CGContextAddLineToPoint(context, s[k+1].x, s[k+1].y);
 *   }
 *   CGContextStrokePath(context);
 */

CG_EXTERN void CGContextStrokeLineSegments(CGContextRef c, const CGPoint points[], size_t count) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Clipping functions. **/

/* Intersect the context's path with the current clip path and use the
 * resulting path as the clip path for subsequent rendering operations.
 * Use the winding-number fill rule for deciding what's inside the path. */

CG_EXTERN void CGContextClip(CGContextRef c);

/* Intersect the context's path with the current clip path and use the
 * resulting path as the clip path for subsequent rendering operations.
 * Use the even-odd fill rule for deciding what's inside the path. */

CG_EXTERN void CGContextEOClip(CGContextRef c);

/* Add `mask' transformed to `rect' to the clipping area of `context'.  The
 * mask, which may be either an image mask or an image, is mapped into the
 * specified rectangle and intersected with the current clipping area of
 * the context.
 *
 * If `mask' is an image mask, then it clips in a manner identical to the
 * behavior if it were used with "CGContextDrawImage": it indicates an area
 * to be masked out (left unchanged) when drawing.  The source samples of
 * the image mask determine which points of the clipping area are changed,
 * acting as an "inverse alpha": if the value of a source sample in the
 * image mask is S, then the corresponding point in the current clipping
 * area will be multiplied by an alpha of (1-S).  (For example, if S is 1,
 * then the point in the clipping area becomes clear, while if S is 0, the
 * point in the clipping area is unchanged.
 *
 * If `mask' is an image, then it serves as alpha mask and is blended with
 * the current clipping area.  The source samples of mask determine which
 * points of the clipping area are changed: if the value of the source
 * sample in mask is S, then the corresponding point in the current
 * clipping area will be multiplied by an alpha of S.  (For example, if S
 * is 0, then the point in the clipping area becomes clear, while if S is
 * 1, the point in the clipping area is unchanged.
 *
 * If `mask' is an image, then it must be in the DeviceGray color space,
 * may not have alpha, and may not be masked by an image mask or masking
 * color. */

CG_EXTERN void CGContextClipToMask(CGContextRef c, CGRect rect, CGImageRef mask);

/* Return the bounding box of the clip path of `c' in user space.  The
 * bounding box is the smallest rectangle completely enclosing all points
 * in the clip. */

CG_EXTERN CGRect CGContextGetClipBoundingBox(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/** Clipping convenience functions. **/

/* Intersect the current clipping path with `rect'.  Note that this
 * function resets the context's path to the empty path. */

CG_EXTERN void CGContextClipToRect(CGContextRef c, CGRect rect);

/* Intersect the current clipping path with the clipping region formed by
 * creating a path consisting of all rects in `rects'.  Note that this
 * function resets the context's path to the empty path. */

CG_EXTERN void CGContextClipToRects(CGContextRef c, const CGRect rects[], size_t count);

/** Primitive color functions. **/

/* Set the current fill color in the context `c' to `color'. */

CG_EXTERN void CGContextSetFillColorWithColor(CGContextRef c, CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Set the current stroke color in the context `c' to `color'. */

CG_EXTERN void CGContextSetStrokeColorWithColor(CGContextRef c, CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

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

/* Set the pattern phase in the current graphics state of the context `c'
 * to `phase'. */

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

/* Set the rendering intent in the current graphics state of context `c' to
 * `intent'. */

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

/** Shadow support. **/

/* Set the shadow parameters in `context'.  `offset' specifies a
 * translation in base-space; `blur' is a non-negative number specifying
 * the amount of blur; `color' specifies the color of the shadow, which may
 * contain a non-opaque alpha value.  If `color' is NULL, it's equivalent
 * to specifying a fully transparent color.  The shadow is a gstate
 * parameter. After a shadow is specified, all objects drawn subsequently
 * will be shadowed.  To turn off shadowing, set the shadow color to a
 * fully transparent color (or pass NULL as the color), or use the standard
 * gsave/grestore mechanism. */

CG_EXTERN void CGContextSetShadowWithColor(CGContextRef context, CGSize offset, float blur, CGColorRef color) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* Equivalent to calling
 *   CGContextSetShadowWithColor(context, offset, blur, color)
 * where color is black with 1/3 alpha (i.e., RGBA = {0, 0, 0, 1.0/3.0}) in
 * the DeviceRGB colorspace. */

CG_EXTERN void CGContextSetShadow(CGContextRef context, CGSize offset, float blur) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/** Shading functions. **/

/* Fill the current clipping region of `c' with `shading'. */

CG_EXTERN void CGContextDrawShading(CGContextRef c, CGShadingRef shading) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

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

/* Set the text drawing mode in the current graphics state of the context
 * `c' to `mode'. */

CG_EXTERN void CGContextSetTextDrawingMode(CGContextRef c, CGTextDrawingMode mode);

/* Set the font in the current graphics state of the context `c' to
 * `font'. */

CG_EXTERN void CGContextSetFont(CGContextRef c, CGFontRef font);

/* Set the font size in the current graphics state of the context `c' to
 * `size'. */

CG_EXTERN void CGContextSetFontSize(CGContextRef c, float size);

/* Attempts to find the font named `name' and, if successful, sets it as
 * the font in the current graphics state of `c' and sets the font size in
 * the current graphics state to `size'. `textEncoding' specifies how to
 * translate from bytes to glyphs when displaying text. */

CG_EXTERN void CGContextSelectFont(CGContextRef c, const char *name, float size, CGTextEncoding textEncoding);

/* Draw `string', a string of `length' bytes, at the point specified by the
 * text matrix in the context `c'.  Each byte of the string is mapped
 * through the encoding vector of the current font to obtain the glyph to
 * display. */

CG_EXTERN void CGContextShowText(CGContextRef c, const char *string, size_t length);

/* Draw the glyphs pointed to by `g', an array of `count' glyphs, at the
 * point specified by the text matrix in the context `c'. */

CG_EXTERN void CGContextShowGlyphs(CGContextRef c, const CGGlyph g[], size_t count);

/* Draw `glyphs', an array of `count' CGGlyphs, at the current point
 * specified by the text matrix.  Each element of `advances' specifies the
 * offset from the previous glyph's origin to the origin of the associated
 * glyph; the advances are specified in user space. */

CG_EXTERN void CGContextShowGlyphsWithAdvances(CGContextRef c, const CGGlyph glyphs[], const CGSize advances[], size_t count) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

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

/** PDF functions. **/

/* Draw `page' in the current user space of the context `c'. */

CG_EXTERN void CGContextDrawPDFPage(CGContextRef c, CGPDFPageRef page) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* DEPRECATED; use the CGPDFPage API instead.
 * Draw `page' in `document' in the rectangular area specified by `rect' in
 * the context `c'.  The media box of the page is scaled, if necessary, to
 * fit into `rect'. */

CG_EXTERN void CGContextDrawPDFDocument(CGContextRef c, CGRect rect, CGPDFDocumentRef document, int page);

/** Output page functions. **/

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

/* Allow antialiasing in context `c' if `allowsAntialiasing' is true; don't
 * allow it otherwise. This parameter is not part of the graphics state. A
 * context will perform antialiasing if both `allowsAntialiasing' and the
 * graphics state parameter `shouldAntialias' are true. */

CG_EXTERN void CGContextSetAllowsAntialiasing(CGContextRef context, bool allowsAntialiasing) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/** Font smoothing functions. **/

/* Turn on font smoothing if `shouldSmoothFonts' is true; turn it off
 * otherwise.  This parameter is part of the graphics state. Note that this
 * doesn't guarantee that font smoothing will occur: not all destination
 * contexts support font smoothing. */

CG_EXTERN void CGContextSetShouldSmoothFonts(CGContextRef c, bool shouldSmoothFonts) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/** Transparency layer support. **/

/* Begin a transparency layer.  All subsequent drawing operations until a
 * corresponding CGContextEndTransparencyLayer are composited into a fully
 * transparent backdrop (which is treated as a separate destination buffer
 * from the context); after a call to CGContextEndTransparencyLayer, the
 * result is composited into the context using the global alpha and shadow
 * state of the context.  This operation respects the clipping region of
 * the context.  After a call to this function, all of the parameters in
 * the graphics state remain unchanged with the exception of the following:
 *   The global alpha is set to 1.
 *   The shadow is turned off.
 * Ending the transparency layer restores these parameters to the values
 * they had before CGContextBeginTransparencyLayer was called.
 * Transparency layers may be nested. */

CG_EXTERN void CGContextBeginTransparencyLayer(CGContextRef context, CFDictionaryRef auxiliaryInfo) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* End a tranparency layer. */

CG_EXTERN void CGContextEndTransparencyLayer(CGContextRef context) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/** User space to device space tranformations. **/

/* Return the affine transform mapping the user space (abstract
 * coordinates) of `context' to device space (pixels). */

CG_EXTERN CGAffineTransform CGContextGetUserSpaceToDeviceSpaceTransform(CGContextRef c) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Transform `point' from the user space of `context' to device space. */

CG_EXTERN CGPoint CGContextConvertPointToDeviceSpace(CGContextRef c, CGPoint point) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Transform `point' from device space to the user space of `context'. */

CG_EXTERN CGPoint CGContextConvertPointToUserSpace(CGContextRef c, CGPoint point) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Transform `size' from the user space of `context' to device space. */

CG_EXTERN CGSize CGContextConvertSizeToDeviceSpace(CGContextRef c, CGSize size) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Transform `size' from device space to the user space of `context'. */

CG_EXTERN CGSize CGContextConvertSizeToUserSpace(CGContextRef c, CGSize size) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Transform `rect' from the user space of `context' to device space. Since
 * affine transforms do not preserve rectangles in general, this function
 * returns the smallest rectangle which contains the transformed corner
 * points of `rect'. */

CG_EXTERN CGRect CGContextConvertRectToDeviceSpace(CGContextRef c, CGRect rect) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Transform `rect' from device space to the user space of `context'. Since
 * affine transforms do not preserve rectangles in general, this function
 * returns the smallest rectangle which contains the transformed corner
 * points of `rect'. */

CG_EXTERN CGRect CGContextConvertRectToUserSpace(CGContextRef c, CGRect rect) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGCONTEXT_H_ */

/* CoreGraphics - CGContext.h
   Copyright (c) 2000-2012 Apple Inc.
   All rights reserved. */

#ifndef CGCONTEXT_H_
#define CGCONTEXT_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CF_BRIDGED_TYPE(id) CGContext *CGContextRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGAffineTransform.h>
#include <CoreGraphics/CGColor.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGFont.h>
#include <CoreGraphics/CGGradient.h>
#include <CoreGraphics/CGImage.h>
#include <CoreGraphics/CGPath.h>
#include <CoreGraphics/CGPattern.h>
#include <CoreGraphics/CGPDFDocument.h>
#include <CoreGraphics/CGShading.h>
#include <CoreGraphics/CGToneMapping.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Drawing modes for paths. */

typedef CF_ENUM (int32_t, CGPathDrawingMode) {
  kCGPathFill,
  kCGPathEOFill,
  kCGPathStroke,
  kCGPathFillStroke,
  kCGPathEOFillStroke
};

/* Drawing modes for text. */

typedef CF_ENUM (int32_t, CGTextDrawingMode) {
  kCGTextFill,
  kCGTextStroke,
  kCGTextFillStroke,
  kCGTextInvisible,
  kCGTextFillClip,
  kCGTextStrokeClip,
  kCGTextFillStrokeClip,
  kCGTextClip
};

/* Text encodings. */

typedef CF_ENUM (int32_t, CGTextEncoding) {
  kCGEncodingFontSpecific,
  kCGEncodingMacRoman
} API_DEPRECATED("No longer supported", macos(10.0,10.9), ios(2.0,7.0));

/* Interpolation quality. */

typedef CF_ENUM (int32_t, CGInterpolationQuality) {
  kCGInterpolationDefault = 0,  /* Let the context decide. */
  kCGInterpolationNone = 1,     /* Never interpolate. */
  kCGInterpolationLow = 2,      /* Low quality, fast interpolation. */
  kCGInterpolationMedium = 4,   /* Medium quality, slower than kCGInterpolationLow. */
  kCGInterpolationHigh = 3      /* Highest quality, slower than kCGInterpolationMedium. */
};

/* Blend modes.

   The blend modes from kCGBlendModeNormal to kCGBlendModeLuminosity are
   supported in Mac OS X 10.4 and later. The Porter-Duff blend modes (from
   kCGBlendModeClear to kCGBlendModePlusLighter) are supported in Mac OS X
   10.5 and later. The names of the Porter-Duff blend modes are historical.

   Note that the Porter-Duff blend modes are not necessarily supported in
   every context. In particular, they are only guaranteed to work in
   bitmap-based contexts, such as those created by CGBitmapContextCreate. It
   is your responsibility to make sure that they do what you want when you
   use them in a CGContext. */

typedef CF_ENUM (int32_t, CGBlendMode) {
    /* Available in Mac OS X 10.4 & later. */
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
    kCGBlendModeLuminosity,

    /* Available in Mac OS X 10.5 & later. R, S, and D are, respectively,
       premultiplied result, source, and destination colors with alpha; Ra,
       Sa, and Da are the alpha components of these colors.

       The Porter-Duff "source over" mode is called `kCGBlendModeNormal':
         R = S + D*(1 - Sa)

       Note that the Porter-Duff "XOR" mode is only titularly related to the
       classical bitmap XOR operation (which is unsupported by
       CoreGraphics). */

    kCGBlendModeClear,                  /* R = 0 */
    kCGBlendModeCopy,                   /* R = S */
    kCGBlendModeSourceIn,               /* R = S*Da */
    kCGBlendModeSourceOut,              /* R = S*(1 - Da) */
    kCGBlendModeSourceAtop,             /* R = S*Da + D*(1 - Sa) */
    kCGBlendModeDestinationOver,        /* R = S*(1 - Da) + D */
    kCGBlendModeDestinationIn,          /* R = D*Sa */
    kCGBlendModeDestinationOut,         /* R = D*(1 - Sa) */
    kCGBlendModeDestinationAtop,        /* R = S*(1 - Da) + D*Sa */
    kCGBlendModeXOR,                    /* R = S*(1 - Da) + D*(1 - Sa) */
    kCGBlendModePlusDarker,             /* R = MAX(0, (1 - D) + (1 - S)) */
    kCGBlendModePlusLighter             /* R = MIN(1, S + D) */
};

/* Return the CFTypeID for CGContextRefs. */

CG_EXTERN CFTypeID CGContextGetTypeID(void)
    API_AVAILABLE(macos(10.2), ios(2.0));

/** Graphics state functions. **/

/* Push a copy of the current graphics state onto the graphics state stack.
   Note that the path is not considered part of the graphics state, and is
   not saved. */

CG_EXTERN void CGContextSaveGState(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Restore the current graphics state from the one on the top of the
   graphics state stack, popping the graphics state stack in the process. */

CG_EXTERN void CGContextRestoreGState(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/** Coordinate space transformations. **/

/* Scale the current graphics state's transformation matrix (the CTM) by
   `(sx, sy)'. */

CG_EXTERN void CGContextScaleCTM(CGContextRef cg_nullable c,
    CGFloat sx, CGFloat sy)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Translate the current graphics state's transformation matrix (the CTM) by
   `(tx, ty)'. */

CG_EXTERN void CGContextTranslateCTM(CGContextRef cg_nullable c,
    CGFloat tx, CGFloat ty)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Rotate the current graphics state's transformation matrix (the CTM) by
   `angle' radians. */

CG_EXTERN void CGContextRotateCTM(CGContextRef cg_nullable c, CGFloat angle)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Concatenate the current graphics state's transformation matrix (the CTM)
   with the affine transform `transform'. */

CG_EXTERN void CGContextConcatCTM(CGContextRef cg_nullable c,
    CGAffineTransform transform)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Return the current graphics state's transformation matrix. Returns 
   CGAffineTransformIdentity in case of inavlid context. */

CG_EXTERN CGAffineTransform CGContextGetCTM(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/** Drawing attribute functions. **/

/* Set the line width in the current graphics state to `width'. */

CG_EXTERN void CGContextSetLineWidth(CGContextRef cg_nullable c, CGFloat width)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the line cap in the current graphics state to `cap'. */

CG_EXTERN void CGContextSetLineCap(CGContextRef cg_nullable c, CGLineCap cap)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the line join in the current graphics state to `join'. */

CG_EXTERN void CGContextSetLineJoin(CGContextRef cg_nullable c, CGLineJoin join)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the miter limit in the current graphics state to `limit'. */

CG_EXTERN void CGContextSetMiterLimit(CGContextRef cg_nullable c, CGFloat limit)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the line dash patttern in the current graphics state of `c'. */

CG_EXTERN void CGContextSetLineDash(CGContextRef cg_nullable c, CGFloat phase,
    const CGFloat * __nullable lengths, size_t count)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the path flatness parameter in the current graphics state of `c' to
   `flatness'. */

CG_EXTERN void CGContextSetFlatness(CGContextRef cg_nullable c, CGFloat flatness)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the alpha value in the current graphics state of `c' to `alpha'. */

CG_EXTERN void CGContextSetAlpha(CGContextRef cg_nullable c, CGFloat alpha)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the blend mode of `context' to `mode'. */

CG_EXTERN void CGContextSetBlendMode(CGContextRef cg_nullable c, CGBlendMode mode)
    API_AVAILABLE(macos(10.4), ios(2.0));

/** Path construction functions. **/

/* Note that a context has a single path in use at any time: a path is not
   part of the graphics state. */

/* Begin a new path. The old path is discarded. */

CG_EXTERN void CGContextBeginPath(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Start a new subpath at point `(x, y)' in the context's path. */

CG_EXTERN void CGContextMoveToPoint(CGContextRef cg_nullable c,
    CGFloat x, CGFloat y)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Append a straight line segment from the current point to `(x, y)'. */

CG_EXTERN void CGContextAddLineToPoint(CGContextRef cg_nullable c,
    CGFloat x, CGFloat y)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Append a cubic Bezier curve from the current point to `(x,y)', with
   control points `(cp1x, cp1y)' and `(cp2x, cp2y)'. */

CG_EXTERN void CGContextAddCurveToPoint(CGContextRef cg_nullable c, CGFloat cp1x,
    CGFloat cp1y, CGFloat cp2x, CGFloat cp2y, CGFloat x, CGFloat y)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Append a quadratic curve from the current point to `(x, y)', with control
   point `(cpx, cpy)'. */

CG_EXTERN void CGContextAddQuadCurveToPoint(CGContextRef cg_nullable c,
    CGFloat cpx, CGFloat cpy, CGFloat x, CGFloat y)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Close the current subpath of the context's path. */

CG_EXTERN void CGContextClosePath(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/** Path construction convenience functions. **/

/* Add a single rect to the context's path. */

CG_EXTERN void CGContextAddRect(CGContextRef cg_nullable c, CGRect rect)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Add a set of rects to the context's path. */

CG_EXTERN void CGContextAddRects(CGContextRef cg_nullable c,
    const CGRect * __nullable rects, size_t count)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Add a set of lines to the context's path. */

CG_EXTERN void CGContextAddLines(CGContextRef cg_nullable c,
    const CGPoint * __nullable points, size_t count)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Add an ellipse inside `rect' to the current path of `context'. See the
   function `CGPathAddEllipseInRect' for more information on how the path
   for the ellipse is constructed. */

CG_EXTERN void CGContextAddEllipseInRect(CGContextRef cg_nullable c, CGRect rect)
    API_AVAILABLE(macos(10.4), ios(2.0));

/* Add an arc of a circle to the context's path, possibly preceded by a
   straight line segment. `(x, y)' is the center of the arc; `radius' is its
   radius; `startAngle' is the angle to the first endpoint of the arc;
   `endAngle' is the angle to the second endpoint of the arc; and
   `clockwise' is 1 if the arc is to be drawn clockwise, 0 otherwise.
   `startAngle' and `endAngle' are measured in radians. */

CG_EXTERN void CGContextAddArc(CGContextRef cg_nullable c, CGFloat x, CGFloat y,
    CGFloat radius, CGFloat startAngle, CGFloat endAngle, int clockwise)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Add an arc of a circle to the context's path, possibly preceded by a
   straight line segment. `radius' is the radius of the arc. The arc is
   tangent to the line from the current point to `(x1, y1)', and the line
   from `(x1, y1)' to `(x2, y2)'. */

CG_EXTERN void CGContextAddArcToPoint(CGContextRef cg_nullable c,
    CGFloat x1, CGFloat y1, CGFloat x2, CGFloat y2, CGFloat radius)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Add `path' to the path of context. The points in `path' are transformed
   by the CTM of context before they are added. */

CG_EXTERN void CGContextAddPath(CGContextRef cg_nullable c,
    CGPathRef cg_nullable path)
    API_AVAILABLE(macos(10.2), ios(2.0));

/** Path stroking. **/

/* Replace the path in `context' with the stroked version of the path, using
   the parameters of `context' to calculate the stroked path. The resulting
   path is created such that filling it with the appropriate color will
   produce the same results as stroking the original path. You can use this
   path in the same way you can use the path of any context; for example,
   you can clip to the stroked version of a path by calling this function
   followed by a call to "CGContextClip". */

CG_EXTERN void CGContextReplacePathWithStrokedPath(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.4), ios(2.0));

/** Path information functions. **/

/* Return true if the path of `context' contains no elements, false
   otherwise. */

CG_EXTERN bool CGContextIsPathEmpty(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Return the current point of the current subpath of the path of
   `context'. */

CG_EXTERN CGPoint CGContextGetPathCurrentPoint(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Return the bounding box of the path of `context'. The bounding box is the
   smallest rectangle completely enclosing all points in the path, including
   control points for Bezier and quadratic curves. */

CG_EXTERN CGRect CGContextGetPathBoundingBox(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Return a copy of the path of `context'. The returned path is specified in
   the current user space of `context'. */

CG_EXTERN CGPathRef __nullable CGContextCopyPath(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Return true if `point' is contained in the current path of `context'. A
   point is contained within a context's path if it is inside the painted
   region when the path is stroked or filled with opaque colors using the
   path drawing mode `mode'. `point' is specified is user space. */

CG_EXTERN bool CGContextPathContainsPoint(CGContextRef cg_nullable c,
    CGPoint point, CGPathDrawingMode mode)
    API_AVAILABLE(macos(10.4), ios(2.0));

/** Path drawing functions. **/

/* Draw the context's path using drawing mode `mode'. */

CG_EXTERN void CGContextDrawPath(CGContextRef cg_nullable c,
    CGPathDrawingMode mode)
    API_AVAILABLE(macos(10.0), ios(2.0));

/** Path drawing convenience functions. **/

/* Fill the context's path using the winding-number fill rule. Any open
   subpath of the path is implicitly closed. */

CG_EXTERN void CGContextFillPath(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Fill the context's path using the even-odd fill rule. Any open subpath of
   the path is implicitly closed. */

CG_EXTERN void CGContextEOFillPath(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Stroke the context's path. */

CG_EXTERN void CGContextStrokePath(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Fill `rect' with the current fill color. */

CG_EXTERN void CGContextFillRect(CGContextRef cg_nullable c, CGRect rect)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Fill `rects', an array of `count' CGRects, with the current fill
   color. */

CG_EXTERN void CGContextFillRects(CGContextRef cg_nullable c,
    const CGRect * __nullable rects, size_t count)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Stroke `rect' with the current stroke color and the current linewidth. */

CG_EXTERN void CGContextStrokeRect(CGContextRef cg_nullable c, CGRect rect)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Stroke `rect' with the current stroke color, using `width' as the the
   line width. */

CG_EXTERN void CGContextStrokeRectWithWidth(CGContextRef cg_nullable c,
    CGRect rect, CGFloat width)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Clear `rect' (that is, set the region within the rect to transparent). */

CG_EXTERN void CGContextClearRect(CGContextRef cg_nullable c, CGRect rect)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Fill an ellipse (an oval) inside `rect'. */

CG_EXTERN void CGContextFillEllipseInRect(CGContextRef cg_nullable c,
    CGRect rect)
    API_AVAILABLE(macos(10.4), ios(2.0));

/* Stroke an ellipse (an oval) inside `rect'. */

CG_EXTERN void CGContextStrokeEllipseInRect(CGContextRef cg_nullable c,
    CGRect rect)
    API_AVAILABLE(macos(10.4), ios(2.0));

/* Stroke a sequence of line segments one after another in `context'. The
   line segments are specified by `points', an array of `count' CGPoints.
   This function is equivalent to

     CGContextBeginPath(context);
     for (k = 0; k < count; k += 2) {
       CGContextMoveToPoint(context, s[k].x, s[k].y);
       CGContextAddLineToPoint(context, s[k+1].x, s[k+1].y);
     }
     CGContextStrokePath(context); */

CG_EXTERN void CGContextStrokeLineSegments(CGContextRef cg_nullable c,
    const CGPoint * __nullable points, size_t count)
    API_AVAILABLE(macos(10.4), ios(2.0));

/** Clipping functions. **/

/* Intersect the context's path with the current clip path and use the
   resulting path as the clip path for subsequent rendering operations. Use
   the winding-number fill rule for deciding what's inside the path. */

CG_EXTERN void CGContextClip(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Intersect the context's path with the current clip path and use the
   resulting path as the clip path for subsequent rendering operations. Use
   the even-odd fill rule for deciding what's inside the path. */

CG_EXTERN void CGContextEOClip(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Reset the current clip of `c' to the default value. */

CG_EXTERN void CGContextResetClip(CGContextRef c);

/* Add `mask' transformed to `rect' to the clipping area of `context'. The
   mask, which may be either an image mask or an image, is mapped into the
   specified rectangle and intersected with the current clipping area of the
   context.

   If `mask' is an image mask, then it clips in a manner identical to the
   behavior if it were used with "CGContextDrawImage": it indicates an area
   to be masked out (left unchanged) when drawing. The source samples of the
   image mask determine which points of the clipping area are changed,
   acting as an "inverse alpha": if the value of a source sample in the
   image mask is S, then the corresponding point in the current clipping
   area will be multiplied by an alpha of (1-S). (For example, if S is 1,
   then the point in the clipping area becomes clear, while if S is 0, the
   point in the clipping area is unchanged.

   If `mask' is an image, then it serves as alpha mask and is blended with
   the current clipping area. The source samples of mask determine which
   points of the clipping area are changed: if the value of the source
   sample in mask is S, then the corresponding point in the current clipping
   area will be multiplied by an alpha of S. (For example, if S is 0, then
   the point in the clipping area becomes clear, while if S is 1, the point
   in the clipping area is unchanged.

   If `mask' is an image, then its color space must be of kCGColorSpaceModelMonochrome
   model, may not have alpha, and may not be masked by an image mask or masking
   color. */

CG_EXTERN void CGContextClipToMask(CGContextRef cg_nullable c, CGRect rect,
    CGImageRef cg_nullable mask)
    API_AVAILABLE(macos(10.4), ios(2.0));

/* Return the bounding box of the clip path of `c' in user space. The
   bounding box is the smallest rectangle completely enclosing all points in
   the clip. */

CG_EXTERN CGRect CGContextGetClipBoundingBox(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.3), ios(2.0));

/** Clipping convenience functions. **/

/* Intersect the current clipping path with `rect'. Note that this function
   resets the context's path to the empty path. */

CG_EXTERN void CGContextClipToRect(CGContextRef cg_nullable c, CGRect rect)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Intersect the current clipping path with the clipping region formed by
   creating a path consisting of all rects in `rects'. Note that this
   function resets the context's path to the empty path. */

CG_EXTERN void CGContextClipToRects(CGContextRef cg_nullable c,
    const CGRect *  rects, size_t count)
    API_AVAILABLE(macos(10.0), ios(2.0));

/** Primitive color functions. **/

/* Set the current fill color in the context `c' to `color'. */

CG_EXTERN void CGContextSetFillColorWithColor(CGContextRef cg_nullable c,
    CGColorRef cg_nullable color)
    API_AVAILABLE(macos(10.3), ios(2.0));

/* Set the current stroke color in the context `c' to `color'. */

CG_EXTERN void CGContextSetStrokeColorWithColor(CGContextRef cg_nullable c,
    CGColorRef cg_nullable color)
    API_AVAILABLE(macos(10.3), ios(2.0));

/** Color space functions. **/

/* Set the current fill color space in `context' to `space'. As a
   side-effect, set the fill color to a default value appropriate for the
   color space. */

CG_EXTERN void CGContextSetFillColorSpace(CGContextRef cg_nullable c,
    CGColorSpaceRef cg_nullable space)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the current stroke color space in `context' to `space'. As a
   side-effect, set the stroke color to a default value appropriate for the
   color space. */

CG_EXTERN void CGContextSetStrokeColorSpace(CGContextRef cg_nullable c,
    CGColorSpaceRef cg_nullable space)
    API_AVAILABLE(macos(10.0), ios(2.0));

/** Color functions. **/

/* Set the components of the current fill color in `context' to the values
   specifed by `components'. The number of elements in `components' must be
   one greater than the number of components in the current fill color space
   (N color components + 1 alpha component). The current fill color space
   must not be a pattern color space. */

CG_EXTERN void CGContextSetFillColor(CGContextRef cg_nullable c,
    const CGFloat * cg_nullable components)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the components of the current stroke color in `context' to the values
   specifed by `components'. The number of elements in `components' must be
   one greater than the number of components in the current stroke color
   space (N color components + 1 alpha component). The current stroke color
   space must not be a pattern color space. */

CG_EXTERN void CGContextSetStrokeColor(CGContextRef cg_nullable c,
    const CGFloat * cg_nullable components)
    API_AVAILABLE(macos(10.0), ios(2.0));

/** Pattern functions. **/

/* Set the components of the current fill color in `context' to the values
   specifed by `components', and set the current fill pattern to `pattern'.
   The number of elements in `components' must be one greater than the
   number of components in the current fill color space (N color components
   + 1 alpha component). The current fill color space must be a pattern
   color space. */

CG_EXTERN void CGContextSetFillPattern(CGContextRef cg_nullable c,
    CGPatternRef cg_nullable pattern, const CGFloat * cg_nullable components)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the components of the current stroke color in `context' to the values
   specifed by `components', and set the current stroke pattern to
   `pattern'. The number of elements in `components' must be one greater
   than the number of components in the current stroke color space (N color
   components + 1 alpha component). The current stroke color space must be a
   pattern color space. */

CG_EXTERN void CGContextSetStrokePattern(CGContextRef cg_nullable c,
    CGPatternRef cg_nullable pattern, const CGFloat * cg_nullable components)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the pattern phase in the current graphics state of `context' to
   `phase'. */

CG_EXTERN void CGContextSetPatternPhase(CGContextRef cg_nullable c, CGSize phase)
    API_AVAILABLE(macos(10.0), ios(2.0));

/** Color convenience functions. **/

/* Set the current fill color space in `context' to `DeviceGray' and set the
   components of the current fill color to `(gray, alpha)'. */

CG_EXTERN void CGContextSetGrayFillColor(CGContextRef cg_nullable c,
    CGFloat gray, CGFloat alpha)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the current stroke color space in `context' to `DeviceGray' and set
   the components of the current stroke color to `(gray, alpha)'. */

CG_EXTERN void CGContextSetGrayStrokeColor(CGContextRef cg_nullable c,
    CGFloat gray, CGFloat alpha)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the current fill color space in `context' to `DeviceRGB' and set the
   components of the current fill color to `(red, green, blue, alpha)'. */

CG_EXTERN void CGContextSetRGBFillColor(CGContextRef cg_nullable c, CGFloat red,
    CGFloat green, CGFloat blue, CGFloat alpha)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the current stroke color space in `context' to `DeviceRGB' and set
   the components of the current stroke color to `(red, green, blue,
   alpha)'. */

CG_EXTERN void CGContextSetRGBStrokeColor(CGContextRef cg_nullable c,
    CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the current fill color space in `context' to `DeviceCMYK' and set the
   components of the current fill color to `(cyan, magenta, yellow, black,
   alpha)'. */

CG_EXTERN void CGContextSetCMYKFillColor(CGContextRef cg_nullable c,
    CGFloat cyan, CGFloat magenta, CGFloat yellow, CGFloat black, CGFloat alpha)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the current stroke color space in `context' to `DeviceCMYK' and set
   the components of the current stroke color to `(cyan, magenta, yellow,
   black, alpha)'. */

CG_EXTERN void CGContextSetCMYKStrokeColor(CGContextRef cg_nullable c,
    CGFloat cyan, CGFloat magenta, CGFloat yellow, CGFloat black, CGFloat alpha)
    API_AVAILABLE(macos(10.0), ios(2.0));

/** Rendering intent. **/

/* Set the rendering intent in the current graphics state of `context' to
   `intent'. */

CG_EXTERN void CGContextSetRenderingIntent(CGContextRef cg_nullable c,
    CGColorRenderingIntent intent)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set target EDR headroom on a context to be used when rendering HDR content to the context.
   The value of the 'headroom' will be adjusted as follows: (headroom < 0.0f) ? 0.0f : (headroom > 0.0f && headroom < 1.0f) ? 1.0f : headroom.
   Please note that the headroom value of 0.0f means "headroom unknown" which prevents tone mapping.
   Context 'c' needs to be a valid context. Return true on success and false on failure */

CG_EXTERN bool CGContextSetEDRTargetHeadroom(CGContextRef __nonnull c, float headroom) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));

/* Return the EDR target headroom of the context `c'. */

CG_EXTERN float CGContextGetEDRTargetHeadroom(CGContextRef c) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));

/** Image functions. **/

/* Draw `image' in the rectangular area specified by `rect' in the context
   `c'. The image is scaled, if necessary, to fit into `rect'. */

CG_EXTERN void CGContextDrawImage(CGContextRef cg_nullable c, CGRect rect,
    CGImageRef cg_nullable image)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Draw `image' tiled in the context `c'. The image is scaled to the size
   specified by `rect' in user space, positioned at the origin of `rect' in
   user space, then replicated, stepping the width of `rect' horizontally
   and the height of `rect' vertically, to fill the current clip region.
   Unlike patterns, the image is tiled in user space, so transformations
   applied to the CTM affect the final result. */

CG_EXTERN void CGContextDrawTiledImage(CGContextRef cg_nullable c, CGRect rect,
    CGImageRef cg_nullable image)
    API_AVAILABLE(macos(10.5), ios(2.0));

/* Draw `image' in the rectangular area specified by `rect' in the context
   `c' applying the specified tone mapping method and options. See CGToneMapping.h for more info. Same as in CGContextDrawImage, the image is scaled, if necessary, to fit into `rect'. */

CG_EXTERN bool CGContextDrawImageApplyingToneMapping(CGContextRef __nonnull c, CGRect r, CGImageRef image, CGToneMapping method, CFDictionaryRef __nullable options) API_AVAILABLE(macos(15.0), ios(18.0), tvos(18.0), watchos(11.0));

/* Return the CGContentToneMappingInfo for rendering HDR content in `context'. The
   content tone mapping info is a gstate parameter which defines the method and method's
   options performed when rendering HDR CGColors and CGImages.
   Note that CGContextDrawImageApplyingToneMapping (described above) will override the
   context's content tone mapping info. */

CG_EXTERN CGContentToneMappingInfo CGContextGetContentToneMappingInfo(CGContextRef __nonnull c)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/* Set the content tone mapping info of `context' to `info'. */

CG_EXTERN void CGContextSetContentToneMappingInfo(CGContextRef __nonnull c, CGContentToneMappingInfo info)
    CF_REFINED_FOR_SWIFT
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/* Return the interpolation quality for image rendering of `context'. The
   interpolation quality is a gstate parameter which controls the level of
   interpolation performed when an image is interpolated (for example, when
   scaling the image). Note that it is merely a hint to the context: not all
   contexts support all interpolation quality levels. */

CG_EXTERN CGInterpolationQuality
    CGContextGetInterpolationQuality(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the interpolation quality of `context' to `quality'. */

CG_EXTERN void CGContextSetInterpolationQuality(CGContextRef cg_nullable c,
    CGInterpolationQuality quality)
    API_AVAILABLE(macos(10.0), ios(2.0));

/** Shadow support. **/

/* Set the shadow parameters in `context'. `offset' specifies a translation
   in base-space; `blur' is a non-negative number specifying the amount of
   blur; `color' specifies the color of the shadow, which may contain a
   non-opaque alpha value. If `color' is NULL, it's equivalent to specifying
   a fully transparent color. The shadow is a gstate parameter. After a
   shadow is specified, all objects drawn subsequently will be shadowed. To
   turn off shadowing, set the shadow color to a fully transparent color (or
   pass NULL as the color), or use the standard gsave/grestore mechanism. */

CG_EXTERN void CGContextSetShadowWithColor(CGContextRef cg_nullable c,
    CGSize offset, CGFloat blur, CGColorRef __nullable color)
    API_AVAILABLE(macos(10.3), ios(2.0));

/* Equivalent to calling
     CGContextSetShadowWithColor(context, offset, blur, color)
   where color is black with 1/3 alpha (i.e., RGBA = {0, 0, 0, 1.0/3.0}) in
   the DeviceRGB color space. */

CG_EXTERN void CGContextSetShadow(CGContextRef cg_nullable c, CGSize offset,
    CGFloat blur)
    API_AVAILABLE(macos(10.3), ios(2.0));

/** Gradient and shading functions. **/

/* Fill the current clipping region of `context' with a linear gradient from
   `startPoint' to `endPoint'. The location 0 of `gradient' corresponds to
   `startPoint'; the location 1 of `gradient' corresponds to `endPoint';
   colors are linearly interpolated between these two points based on the
   values of the gradient's locations. The option flags control whether the
   gradient is drawn before the start point or after the end point. */

CG_EXTERN void CGContextDrawLinearGradient(CGContextRef cg_nullable c,
    CGGradientRef cg_nullable gradient, CGPoint startPoint, CGPoint endPoint,
    CGGradientDrawingOptions options)
    API_AVAILABLE(macos(10.5), ios(2.0));

/* Fill the current clipping region of `context' with a radial gradient
   between two circles defined by the center point and radius of each
   circle. The location 0 of `gradient' corresponds to a circle centered at
   `startCenter' with radius `startRadius'; the location 1 of `gradient'
   corresponds to a circle centered at `endCenter' with radius `endRadius';
   colors are linearly interpolated between these two circles based on the
   values of the gradient's locations. The option flags control whether the
   gradient is drawn before the start circle or after the end circle. */

CG_EXTERN void CGContextDrawRadialGradient(CGContextRef cg_nullable c,
    CGGradientRef cg_nullable gradient, CGPoint startCenter, CGFloat startRadius,
    CGPoint endCenter, CGFloat endRadius, CGGradientDrawingOptions options)
    API_AVAILABLE(macos(10.5), ios(2.0));

/* Fill the current clipping region of `context' with a conic gradient
   defined by the center point and rotation angle. The location 0 of `gradient'
   corresponds to a initial rotation angle; the location 1 of `gradient'
   corresponds to 360 degrees rotation from rotation angle; colors are linearly
   interpolated over the full angle based on the values of the gradient's
   locations. The 0 angle corresponds to positive x axis. The angle increases
   towards positive y axis. */

CG_EXTERN void CGContextDrawConicGradient(CGContextRef _Nonnull c,
    CGGradientRef _Nullable gradient, CGPoint center, CGFloat angle)
    API_AVAILABLE(macos(14.0), ios(17.0));


/* Fill the current clipping region of `context' with `shading'. */

CG_EXTERN void CGContextDrawShading(CGContextRef cg_nullable c,
    cg_nullable CGShadingRef shading)
    API_AVAILABLE(macos(10.2), ios(2.0));

/** Text functions. **/

/* Set the current character spacing in `context' to `spacing'. The
   character spacing is added to the displacement between the origin of one
   character and the origin of the next. */

CG_EXTERN void CGContextSetCharacterSpacing(CGContextRef cg_nullable c,
    CGFloat spacing)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the user-space point at which text will be drawn in the context `c'
   to `(x, y)'. */

CG_EXTERN void CGContextSetTextPosition(CGContextRef cg_nullable c,
    CGFloat x, CGFloat y)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Return the user-space point at which text will be drawn in `context'. */

CG_EXTERN CGPoint CGContextGetTextPosition(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the text matrix in the context `c' to `t'. */

CG_EXTERN void CGContextSetTextMatrix(CGContextRef cg_nullable c,
    CGAffineTransform t)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Return the text matrix in the context `c'. Returns CGAffineTransformIdentity
   if `c' is not a valid context. */

CG_EXTERN CGAffineTransform CGContextGetTextMatrix(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the text drawing mode in the current graphics state of the context
   `c' to `mode'. */

CG_EXTERN void CGContextSetTextDrawingMode(CGContextRef cg_nullable c,
    CGTextDrawingMode mode)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the font in the current graphics state of the context `c' to
   `font'. */

CG_EXTERN void CGContextSetFont(CGContextRef cg_nullable c,
    CGFontRef cg_nullable font)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Set the font size in the current graphics state of the context `c' to
   `size'. */

CG_EXTERN void CGContextSetFontSize(CGContextRef cg_nullable c, CGFloat size)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Draw `glyphs', an array of `count' CGGlyphs, at the points specified by
   `positions'. Each element of `positions' specifies the position from the
   associated glyph; the positions are specified in user space. */

CG_EXTERN void CGContextShowGlyphsAtPositions(CGContextRef cg_nullable c,
    const CGGlyph * cg_nullable glyphs, const CGPoint * cg_nullable Lpositions,
    size_t count)
    API_AVAILABLE(macos(10.5), ios(2.0));

/** PDF functions. **/

/* Draw `page' in the current user space of the context `c'. */

CG_EXTERN void CGContextDrawPDFPage(CGContextRef cg_nullable c,
    CGPDFPageRef cg_nullable page)
    API_AVAILABLE(macos(10.3), ios(2.0));

/** Output page functions. **/

/* Begin a new page. */

CG_EXTERN void CGContextBeginPage(CGContextRef cg_nullable c,
    const CGRect * __nullable mediaBox)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* End the current page. */

CG_EXTERN void CGContextEndPage(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/** Context functions. **/

/* Equivalent to `CFRetain(c)'. */

CG_EXTERN CGContextRef cg_nullable CGContextRetain(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Equivalent to `CFRelease(c)'. */

CG_EXTERN void CGContextRelease(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Flush all drawings to the destination. */

CG_EXTERN void CGContextFlush(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Synchronize drawing. */

CG_EXTERN void CGContextSynchronize(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Synchronize destination attributes with the context. */

CG_EXTERN void CGContextSynchronizeAttributes(CGContextRef c)
  CF_SWIFT_NAME(CGContext.synchronizeAttributes(self:))
  API_AVAILABLE(macos(26.0), ios(26.0));

/** Antialiasing functions. **/

/* Turn on antialiasing if `shouldAntialias' is true; turn it off otherwise.
   This parameter is part of the graphics state. */

CG_EXTERN void CGContextSetShouldAntialias(CGContextRef cg_nullable c,
    bool shouldAntialias)
    API_AVAILABLE(macos(10.0), ios(2.0));

/* Allow antialiasing in `context' if `allowsAntialiasing' is true; don't
   allow it otherwise. This parameter is not part of the graphics state. A
   context will perform antialiasing if both `allowsAntialiasing' and the
   graphics state parameter `shouldAntialias' are true. */

CG_EXTERN void CGContextSetAllowsAntialiasing(CGContextRef cg_nullable c,
    bool allowsAntialiasing)
    API_AVAILABLE(macos(10.4), ios(2.0));

/** Font display functions. **/

/* Turn on font smoothing if `shouldSmoothFonts' is true; turn it off
   otherwise. This parameter is part of the graphics state. Note that this
   doesn't guarantee that font smoothing will occur: not all destination
   contexts support font smoothing. */

CG_EXTERN void CGContextSetShouldSmoothFonts(CGContextRef cg_nullable c,
    bool shouldSmoothFonts)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* If `allowsFontSmoothing' is true, then allow font smoothing when
   displaying text in `context'; otherwise, don't allow font smoothing. This
   parameter is not part of the graphics state. Fonts will be smoothed if
   they are antialiased when drawn and if both `allowsFontSmoothing' and the
   graphics state parameter `shouldSmoothFonts' are true. */
 
CG_EXTERN void CGContextSetAllowsFontSmoothing(CGContextRef cg_nullable c,
    bool allowsFontSmoothing)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* If `shouldSubpixelPositionFonts' is true, then glyphs may be placed at
   subpixel positions (if allowed) when displaying text in `context';
   otherwise, glyphs will be forced to integer pixel boundaries. This
   parameter is part of the graphics state. */

CG_EXTERN void CGContextSetShouldSubpixelPositionFonts(
    CGContextRef cg_nullable c, bool shouldSubpixelPositionFonts)
    API_AVAILABLE(macos(10.5), ios(2.0));

/* If `allowsFontSubpixelPositioning' is true, then allow font subpixel
   positioning when displaying text in `context'; otherwise, don't allow
   subpixel positioning. This parameter is not part of the graphics state. A
   context will place glyphs at subpixel positions if fonts will be
   antialiased when drawn and if both `allowsFontSubpixelPositioning' and
   the graphics state parameter `shouldSubpixelPositionFonts' are true. */

CG_EXTERN void CGContextSetAllowsFontSubpixelPositioning(
    CGContextRef cg_nullable c, bool allowsFontSubpixelPositioning)
    API_AVAILABLE(macos(10.5), ios(2.0));

/* If `shouldSubpixelQuantizeFonts' is true, then quantize the subpixel
   positions of glyphs when displaying text in `context'; otherwise, don't
   quantize the subpixel positions. This parameter is part of the graphics
   state. */

CG_EXTERN void CGContextSetShouldSubpixelQuantizeFonts(
    CGContextRef cg_nullable c, bool shouldSubpixelQuantizeFonts)
    API_AVAILABLE(macos(10.5), ios(2.0));

/* If `allowsFontSubpixelQuantization' is true, then allow font subpixel
   quantization when displaying text in `context'; otherwise, don't allow
   subpixel quantization. This parameter is not part of the graphics state.
   A context quantizes subpixel positions if glyphs will be drawn at
   subpixel positions and `allowsFontSubpixelQuantization' and the graphics
   state parameter `shouldSubpixelQuantizeFonts' are both true. */

CG_EXTERN void CGContextSetAllowsFontSubpixelQuantization(
    CGContextRef cg_nullable c, bool allowsFontSubpixelQuantization)
    API_AVAILABLE(macos(10.5), ios(2.0));

/** Transparency layer support. **/

/* Begin a transparency layer in `context'. All subsequent drawing
   operations until a corresponding `CGContextEndTransparencyLayer' are
   composited into a fully transparent backdrop (which is treated as a
   separate destination buffer from the context). After the transparency
   layer is ended, the result is composited into the context using the
   global alpha and shadow state of the context. This operation respects the
   clipping region of the context. After a call to this function, all of the
   parameters in the graphics state remain unchanged with the exception of
   the following:
     - The global alpha is set to 1.
     - The shadow is turned off.
     - The blend mode is set to `kCGBlendModeNormal'.
   Ending the transparency layer restores these parameters to the values
   they had before `CGContextBeginTransparencyLayer' was called.
   Transparency layers may be nested. */

CG_EXTERN void CGContextBeginTransparencyLayer(CGContextRef cg_nullable c,
    CFDictionaryRef __nullable auxiliaryInfo)
    API_AVAILABLE(macos(10.3), ios(2.0));

/* Begin a transparency layer in `context'. This function is identical to
  `CGContextBeginTransparencyLayer' except that the content of the
  transparency layer will be bounded by `rect' (specified in user space). */

CG_EXTERN void CGContextBeginTransparencyLayerWithRect(
    CGContextRef cg_nullable c, CGRect rect, CFDictionaryRef __nullable auxInfo)
    API_AVAILABLE(macos(10.5), ios(2.0));

/* End a tranparency layer. */

CG_EXTERN void CGContextEndTransparencyLayer(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.3), ios(2.0));

/** User space to device space tranformations. **/

/* Return the affine transform mapping the user space (abstract coordinates)
   of `context' to device space (pixels). */

CG_EXTERN CGAffineTransform
    CGContextGetUserSpaceToDeviceSpaceTransform(CGContextRef cg_nullable c)
    API_AVAILABLE(macos(10.4), ios(2.0));

/* Transform `point' from the user space of `context' to device space. */

CG_EXTERN CGPoint CGContextConvertPointToDeviceSpace(CGContextRef cg_nullable c,
    CGPoint point)
    API_AVAILABLE(macos(10.4), ios(2.0));

/* Transform `point' from device space to the user space of `context'. */

CG_EXTERN CGPoint CGContextConvertPointToUserSpace(CGContextRef cg_nullable c,
    CGPoint point)
    API_AVAILABLE(macos(10.4), ios(2.0));

/* Transform `size' from the user space of `context' to device space. */

CG_EXTERN CGSize CGContextConvertSizeToDeviceSpace(CGContextRef cg_nullable c,
    CGSize size)
    API_AVAILABLE(macos(10.4), ios(2.0));

/* Transform `size' from device space to the user space of `context'. */

CG_EXTERN CGSize CGContextConvertSizeToUserSpace(CGContextRef cg_nullable c,
    CGSize size)
    API_AVAILABLE(macos(10.4), ios(2.0));

/* Transform `rect' from the user space of `context' to device space. Since
   affine transforms do not preserve rectangles in general, this function
   returns the smallest rectangle which contains the transformed corner
   points of `rect'. */

CG_EXTERN CGRect CGContextConvertRectToDeviceSpace(CGContextRef cg_nullable c,
    CGRect rect)
    API_AVAILABLE(macos(10.4), ios(2.0));

/* Transform `rect' from device space to the user space of `context'. Since
   affine transforms do not preserve rectangles in general, this function
   returns the smallest rectangle which contains the transformed corner
   points of `rect'. */

CG_EXTERN CGRect CGContextConvertRectToUserSpace(CGContextRef cg_nullable c,
    CGRect rect)
    API_AVAILABLE(macos(10.4), ios(2.0));

/** Deprecated functions. **/

/* DEPRECATED; use the CoreText API instead. */

CG_EXTERN void CGContextSelectFont(CGContextRef cg_nullable c,
    const char * cg_nullable name, CGFloat size, CGTextEncoding textEncoding)
    API_DEPRECATED("No longer supported", macos(10.0,10.9), ios(2.0,7.0));

/* DEPRECATED; use the CoreText API instead. */

CG_EXTERN void CGContextShowText(CGContextRef cg_nullable c,
    const char * cg_nullable string, size_t length)
    API_DEPRECATED("No longer supported", macos(10.0,10.9), ios(2.0,7.0));

/* DEPRECATED; use the CoreText API instead. */

CG_EXTERN void CGContextShowTextAtPoint(CGContextRef cg_nullable c,
    CGFloat x, CGFloat y, const char * cg_nullable string, size_t length)
    API_DEPRECATED("No longer supported", macos(10.0,10.9), ios(2.0,7.0));

/* DEPRECATED; use the CoreText API instead. */

CG_EXTERN void CGContextShowGlyphs(CGContextRef cg_nullable c,
    const CGGlyph * __nullable g, size_t count)
    API_DEPRECATED("No longer supported", macos(10.0,10.9), ios(2.0,7.0));

/* DEPRECATED; use the CoreText API instead. */

CG_EXTERN void CGContextShowGlyphsAtPoint(CGContextRef cg_nullable c, CGFloat x,
    CGFloat y, const CGGlyph * __nullable glyphs, size_t count)
    API_DEPRECATED("No longer supported", macos(10.0,10.9), ios(2.0,7.0));

/* DEPRECATED; use the CoreText API instead. */

CG_EXTERN void CGContextShowGlyphsWithAdvances(CGContextRef cg_nullable c,
    const CGGlyph * __nullable glyphs, const CGSize * __nullable advances,
    size_t count)
    API_DEPRECATED("No longer supported", macos(10.3,10.9), ios(2.0,7.0));

/* DEPRECATED; use the CGPDFPage API instead. */

CG_EXTERN void CGContextDrawPDFDocument(CGContextRef cg_nullable c, CGRect rect,
    CGPDFDocumentRef cg_nullable document, int page)
    API_DEPRECATED("No longer supported", macos(10.0,10.5)) API_UNAVAILABLE(ios, tvos, watchos);

CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGCONTEXT_H_ */

/* CoreGraphics - CGShading.h
 * Copyright (c) 2001-2002 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGSHADING_H_
#define CGSHADING_H_

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGFunction.h>
#include <CoreGraphics/CGGeometry.h>
#include <CoreFoundation/CFBase.h>

typedef struct CGShading *CGShadingRef;

CG_EXTERN_C_BEGIN

/*! @function CGShadingGetTypeID
 *   Return the CFTypeID for CGShadingRefs.
 */

CG_EXTERN CFTypeID CGShadingGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @function CGShadingCreateAxial
 *
 * Create a shading defining a color blend which varies along a linear axis
 * between two endpoints and extends indefinitely perpendicular to that
 * axis. The shading may optionally extend beyond either endpoint by
 * continuing the boundary colors indefinitely.
 *
 * @param colorspace
 *   The colorspace in which color values are expressed.
 * @param start
 *   The starting point of the axis, in the shading's target coordinate space.
 * @param end
 *   The ending point of the axis, in the shading's target coordinate space.
 * @param function
 *   A 1-in, N-out function, where N is one more (for alpha) than the
 *   number of color components in the shading's colorspace.  The input
 *   value 0 corresponds to the color at the starting point of the shading;
 *   the input value 1 corresponds to the color at the ending point of the
 *   shading.
 * @param extendStart
 *   A boolean specifying whether to extend the shading beyond the starting
 *   point of the axis.
 * @param extendEnd
 *   A boolean specifying whether to extend the shading beyond the ending
 *   point of the axis.
 */

CG_EXTERN CGShadingRef CGShadingCreateAxial(CGColorSpaceRef colorspace, CGPoint start, CGPoint end, CGFunctionRef function, bool extendStart, bool extendEnd) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @function CGShadingCreateRadial
 *
 * Create a shading defining a color blend which varies between two
 * circles.  The shading may optionally extend beyond either circle by
 * continuing the boundary colors.
 *
 * @param colorspace
 *   The colorspace in which color values are expressed.
 * @param start
 *   The center of the starting circle, in the shading's target coordinate
 *   space.
 * @param startRadius
 *   The radius of the starting circle, in the shading's target coordinate
 *   space.
 * @param end
 *   The center of the ending circle, in the shading's target coordinate
 *   space.
 * @param endRadius
 *   The radius of the ending circle, in the shading's target coordinate
 *   space.
 * @param function
 *   A 1-in, N-out function, where N is one more (for alpha) than the
 *   number of color components in the shading's colorspace.  The input
 *   value 0 corresponds to the color of the starting circle; the input
 *   value 1 corresponds to the color of the ending circle.
 * @param extendStart
 *   A boolean specifying whether to extend the shading beyond the starting
 *   circle.
 * @param extendEnd
 *   A boolean specifying whether to extend the shading beyond the ending
 *   circle.
 */

CG_EXTERN CGShadingRef CGShadingCreateRadial(CGColorSpaceRef colorspace, CGPoint start, float startRadius, CGPoint end, float endRadius, CGFunctionRef function, bool extendStart, bool extendEnd) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @function CGShadingRetain
 *
 * Equivalent to <tt>CFRetain(shading)</tt>.
 */

CG_EXTERN CGShadingRef CGShadingRetain(CGShadingRef shading) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @function CGShadingRelease
 *
 * Equivalent to <tt>CFRelease(shading)</tt>.
 */

CG_EXTERN void CGShadingRelease(CGShadingRef shading) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGSHADING_H_ */

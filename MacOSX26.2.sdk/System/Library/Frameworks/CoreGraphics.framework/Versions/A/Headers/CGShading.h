/* CoreGraphics - CGShading.h
   Copyright (c) 2001-2011 Apple Inc.
   All rights reserved. */

#ifndef CGSHADING_H_
#define CGSHADING_H_

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAvailability.h>
#include <stdint.h>

typedef struct CF_BRIDGED_TYPE(id) CGShading *CGShadingRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGColorSpace.h>
#include <CoreGraphics/CGFunction.h>
#include <CoreGraphics/CGGeometry.h>
#include <CoreFoundation/CFBase.h>

CF_IMPLICIT_BRIDGING_ENABLED

CF_ASSUME_NONNULL_BEGIN

/* Return the CFTypeID for CGShadingRefs. */

CG_EXTERN CFTypeID CGShadingGetTypeID(void)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Create a shading defining a color blend which varies along a linear axis
   between two endpoints and extends indefinitely perpendicular to that
   axis. The shading may optionally extend beyond either endpoint by
   continuing the boundary colors indefinitely. The color values are
   specified in the color space `space'. The starting point of the axis is
   `start' and the ending point of the axis is `end', both specified in the
   shading's target coordinate space. The shading function, specified by
   `function', is a 1-in, N-out function, where N is one more (for alpha)
   than the number of color components in the shading's color space. The
   input value 0 corresponds to the color at the starting point of the
   shading; the input value 1 corresponds to the color at the ending point
   of the shading. If `extendStart' is true, then the shading will extend
   beyond the starting point of the axis. If `extendEnd' is true, then the
   shading will extend beyond the ending point of the axis. The shading's
   content headroom will be based on the `space' and determined by the system. */

CG_EXTERN CGShadingRef __nullable CGShadingCreateAxial(
    CGColorSpaceRef cg_nullable space, CGPoint start, CGPoint end,
    CGFunctionRef cg_nullable function, bool extendStart, bool extendEnd)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Creates axial shading with a specified content headroom. The value of the `headroom'
   will be adjusted as follows:
   (headroom < 0.0f) ? 0.0f : (headroom > 0.0f && headroom < 1.0f) ? 1.0f : headroom.
   The `space' must support HDR (is either HDR or extended range RGB). Creating an axial
   shading wih the content headroom of 0.0 means that the headroom is unspecified, and this
   will prevent tone mapping of the axial shading content to the destination. Meaning of
   other parameters is the same as in CGShadingCreateAxial. */

CG_EXTERN CGShadingRef __nullable CGShadingCreateAxialWithContentHeadroom(
    float headroom, CGColorSpaceRef cg_nullable space, CGPoint start, CGPoint end,
    CGFunctionRef cg_nullable function, bool extendStart, bool extendEnd)
    CF_SWIFT_NAME(CGShading.init(axialHeadroom:space:start:end:function:extendStart:extendEnd:))
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/* Create a shading defining a color blend which varies between two circles.
   The shading may optionally extend beyond either circle by continuing the
   boundary colors. The color values are specified in the color space
   `space'. The starting circle has radius `startRadius' and is centered at
   `start', specified in the shading's target coordinate space. The ending
   circle has radius `endRadius' and is centered at `end', specified in the
   shading's target coordinate space. The shading function, specified by
   `function', is a 1-in, N-out function, where N is one more (for alpha)
   than the number of color components in the shading's color space. The
   input value 0 corresponds to the color of the starting circle; the input
   value 1 corresponds to the color of the ending circle. If `extendStart'
   is true, then the shading will extend beyond the starting circle. If
   `extendEnd' is true, then the shading will extend beyond the ending
   circle. The shading's content headroom will be based on the `space'
   and determined by the system. */

CG_EXTERN CGShadingRef __nullable CGShadingCreateRadial(
    CGColorSpaceRef cg_nullable space,
    CGPoint start, CGFloat startRadius, CGPoint end, CGFloat endRadius,
    CGFunctionRef cg_nullable function, bool extendStart, bool extendEnd)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Creates radial shading with a specified content headroom. The value of the `headroom'
   will be adjusted as follows:
   (headroom < 0.0f) ? 0.0f : (headroom > 0.0f && headroom < 1.0f) ? 1.0f : headroom.
   The `space' must support HDR (is either HDR or extended range RGB). Creating an radial
   shading wih the content headroom of 0.0 means that the headroom is unspecified, and this
   will prevent tone mapping of the radial shading content to the destination. Meaning of
   other parameters is the same as in CGShadingCreateRadial. */

CG_EXTERN CGShadingRef __nullable CGShadingCreateRadialWithContentHeadroom(
    float headroom, CGColorSpaceRef cg_nullable space,
    CGPoint start, CGFloat startRadius, CGPoint end, CGFloat endRadius,
    CGFunctionRef cg_nullable function, bool extendStart, bool extendEnd)
    CF_SWIFT_NAME(CGShading.init(radialHeadroom:space:start:startRadius:end:endRadius:function:extendStart:extendEnd:))
    API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

/* Equivalent to `CFRetain(shading)', except it doesn't crash (as CFRetain
   does) if `shading' is NULL. */

CG_EXTERN CGShadingRef cg_nullable CGShadingRetain(CGShadingRef cg_nullable shading)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Equivalent to `CFRelease(shading)', except it doesn't crash (as CFRelease
   does) if `shading' is NULL. */

CG_EXTERN void CGShadingRelease(CGShadingRef cg_nullable shading)
    API_AVAILABLE(macos(10.2), ios(2.0));

/* Return shading's content headroom, and return 0.0f if unknown or unspecified. */

CG_EXTERN float CGShadingGetContentHeadroom(CGShadingRef cg_nullable shading)
   CF_SWIFT_NAME(getter:CGShading.contentHeadroom(self:))
   API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));


CF_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGSHADING_H_ */

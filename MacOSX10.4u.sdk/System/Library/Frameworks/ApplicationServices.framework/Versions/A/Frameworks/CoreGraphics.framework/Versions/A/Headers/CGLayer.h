/* CoreGraphics - CGLayer.h
 * Copyright (c) 2004 Apple Computer, Inc.
 * All rights reserved.
 */

#ifndef CGLAYER_H_
#define CGLAYER_H_

typedef struct CGLayer *CGLayerRef;

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGContext.h>

CG_EXTERN_C_BEGIN

/* Create a layer of size `size' relative to the context `context'. The
 * value of `size' is specified in default user space (base space) units.
 * If `size' is NULL, then the underlying size of `context' is used. The
 * parameter `auxiliaryInfo' should be NULL; it is reserved for future
 * expansion. */

CG_EXTERN CGLayerRef CGLayerCreateWithContext(CGContextRef context, CGSize size, CFDictionaryRef auxiliaryInfo) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Equivalent to `CFRetain(layer)', except it doesn't crash (as CFRetain
 * does) if `layer' is NULL. */

CG_EXTERN CGLayerRef CGLayerRetain(CGLayerRef layer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Equivalent to `CFRelease(layer)', except it doesn't crash (as CFRelease
 * does) if `layer' is NULL. */

CG_EXTERN void CGLayerRelease(CGLayerRef layer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the size of the layer `layer'. */

CG_EXTERN CGSize CGLayerGetSize(CGLayerRef layer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the context of `layer'. */

CG_EXTERN CGContextRef CGLayerGetContext(CGLayerRef layer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Draw the contents of `layer' into `rect' of `context'. The contents are
 * scaled, if necessary, to fit into `rect'; the rectangle `rect' is in
 * user space. */

CG_EXTERN void CGContextDrawLayerInRect(CGContextRef context, CGRect rect, CGLayerRef layer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Draw the contents of `layer' at `point' in `context'.  This is
 * equivalent to calling "CGContextDrawLayerInRect" with a rectangle having
 * origin at `point' and size equal to the size of `layer'. */

CG_EXTERN void CGContextDrawLayerAtPoint(CGContextRef context, CGPoint point, CGLayerRef layer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the CFTypeID for CGLayerRefs. */

CG_EXTERN CFTypeID CGLayerGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGLAYER_H_ */

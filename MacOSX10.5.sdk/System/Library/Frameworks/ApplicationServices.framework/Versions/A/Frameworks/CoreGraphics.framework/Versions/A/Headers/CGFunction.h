/* CoreGraphics - CGFunction.h
 * Copyright (c) 1999-2005 Apple Computer, Inc. (unpublished)
 * All rights reserved.
 */

#ifndef CGFUNCTION_H_
#define CGFUNCTION_H_

/* A CGFunction is a general floating-point function evaluator which uses a
 * user-specified callback to map an arbitrary number of inputs to an
 * arbitrary number of outputs. */

typedef struct CGFunction *CGFunctionRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFBase.h>

/* This callback evaluates a function, using `in' as inputs, and places the
 * result in `out'. `info' is the info parameter passed to the CGFunction
 * creation functions. */

typedef void (*CGFunctionEvaluateCallback)(void *info, const CGFloat *in, CGFloat *out);

/* When a function is deallocated, this callback releases `info', the info
 * parameter passed to the CGFunction creation functions. */

typedef void (*CGFunctionReleaseInfoCallback)(void *info);

/* Callbacks for a CGFunction.
 *   `version' is the version number of this structure. This structure is
 *   version 0.
 *
 *   `evaluate' is the callback used to evaluate the function.
 *
 *   `releaseInfo', if non-NULL, is the callback used to release the info
 *   parameter passed to the CGFunction creation functions when the
 *   function is deallocated.
 */

struct CGFunctionCallbacks {
    unsigned int version;
    CGFunctionEvaluateCallback evaluate;
    CGFunctionReleaseInfoCallback releaseInfo;
};
typedef struct CGFunctionCallbacks CGFunctionCallbacks;

CG_EXTERN_C_BEGIN

/* Return the CFTypeID for CGFunctionRefs. */

CG_EXTERN CFTypeID CGFunctionGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Create a CGFunction using `callbacks' to evaluate the function. `info'
 * is passed to each of the callback functions. `domainDimension' is the
 * number of input values to the function; `rangeDimension' is the number
 * of output values from the function.
 *
 * `domain' is an array of 2M values, where M is the number of input
 * values. For each k from 0 to M-1, domain[2*k] must be less than or equal
 * to domain[2*k+1]. The k'th input value (in[k]) will be clipped to lie in
 * this interval, so that domain[2*k] <= in[k] <= domain[2*k+1]. If
 * `domain' is NULL, then the input values will not be clipped. However,
 * it's strongly recommended that `domain' be specified; each domain
 * interval should specify reasonable values for the minimum and maximum in
 * that dimension.
 *
 * `range' is an array of 2N values, where N is the number of output
 * values. For each k from 0 to N-1, range[2*k] must be less than or equal
 * to range[2*k+1]. The k'th output value (out[k]) will be clipped to lie
 * in this interval, so that range[2*k] <= out[k] <= range[2*k+1]. If
 * `range' is NULL, then the output values will not be clipped. However,
 * it's strongly recommended that `range' be specified; each range interval
 * should specify reasonable values for the minimum and maximum in that
 * dimension.
 *
 * The contents of the callbacks structure is copied, so, for example, a
 * pointer to a structure on the stack can be passed to this function. */

CG_EXTERN CGFunctionRef CGFunctionCreate(void *info, size_t domainDimension, const CGFloat *domain, size_t rangeDimension, const CGFloat *range, const CGFunctionCallbacks *callbacks) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Equivalent to `CFRetain(function)', except it doesn't crash (as CFRetain
 * does) if `function' is NULL. */

CG_EXTERN CGFunctionRef CGFunctionRetain(CGFunctionRef function) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Equivalent to `CFRelease(function)', except it doesn't crash (as CFRelease
 * does) if `function' is NULL. */

CG_EXTERN void CGFunctionRelease(CGFunctionRef function) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGFUNCTION_H_ */

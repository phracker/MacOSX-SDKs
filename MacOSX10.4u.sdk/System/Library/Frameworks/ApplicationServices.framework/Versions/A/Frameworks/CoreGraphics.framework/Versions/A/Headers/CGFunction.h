/* CoreGraphics - CGFunction.h
 * Copyright (c) 1999-2002 Apple Computer, Inc. (unpublished)
 * All rights reserved.
 */

#ifndef CGFUNCTION_H_
#define CGFUNCTION_H_

/*! @header CGFunction
 *   A general floating-point function evaluator, using a callback mapping
 *   an arbitrary number of float inputs to an arbitrary number of float
 *   outputs.
 */

typedef struct CGFunction *CGFunctionRef;

#include <CoreGraphics/CGBase.h>
#include <CoreFoundation/CFBase.h>

/*! @typedef CGFunctionEvaluateCallback
 *   This callback evaluates a function, using <tt>in</tt> as inputs, and
 *   places the result in <tt>out</tt>.
 *
 * @param info
 *   The info parameter passed to CGFunctionCreate.
 *
 * @param inData
 *   An array of <tt>domainDimension</tt> floats.
 *
 * @param outData
 *   An array of <tt>rangeDimension</tt> floats.
 */

typedef void (*CGFunctionEvaluateCallback)(void *info, const float *in, float *out);

/*! @typedef CGFunctionReleaseInfoCallback
 *   This callback releases the info parameter passed to the CGFunction
 *   creation functions when the function is deallocated.
 *
 * @param info
 *   The info parameter passed to CGFunctionCreate.
 */

typedef void (*CGFunctionReleaseInfoCallback)(void *info);

/*! @typedef CGFunctionCallbacks
 *   Structure containing the callbacks of a CGFunction.
 *
 * @field version
 *   The version number of the structure passed to the CGFunction creation
 *   functions. This structure is version 0.
 *
 * @field evaluate
 *   The callback used to evaluate the function.
 *
 * @field releaseInfo
 *   If non-NULL, the callback used to release the info parameter passed to
 *   the CGFunction creation functions when the function is deallocated.
 */

struct CGFunctionCallbacks {
    unsigned int version;
    CGFunctionEvaluateCallback evaluate;
    CGFunctionReleaseInfoCallback releaseInfo;
};
typedef struct CGFunctionCallbacks CGFunctionCallbacks;

CG_EXTERN_C_BEGIN

/*! @function CGFunctionGetTypeID
 *   Return the CFTypeID for CGFunctionRefs.
 */

CG_EXTERN CFTypeID CGFunctionGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @function CGFunctionCreate
 *   Create a function.
 *
 * @param info
 *   The parameter passed to the callback functions.
 *
 * @param domainDimension
 *   The number of inputs to the function.
 *
 * @param domain
 *   An array of <tt>2*domainDimension</tt> floats used to specify the
 *   valid intervals of input values.  For each <tt>k</tt> from <tt>0</tt>
 *   to <tt>domainDimension - 1</tt>, <tt>domain[2*k]</tt> must be less
 *   than or equal to <tt>domain[2*k+1]</tt>, and the <tt>k</tt>'th input
 *   value <tt>in[k]</tt> will be clipped to lie in the interval
 *   <tt>domain[2*k] <= in[k] <= domain[2*k+1]</tt>.  If this parameter is
 *   NULL, then the input values are not clipped.  However, it's strongly
 *   recommended that this parameter be specified; each domain interval
 *   should specify reasonable values for the minimum and maximum in each
 *   dimension.
 *
 * @param rangeDimension
 *   The number of outputs from the function.
 *
 * @param range
 *   An array of <tt>2*rangeDimension</tt> floats used to specify the valid
 *   intervals of output values.  For each <tt>k</tt> from <tt>0</tt> to
 *   <tt>rangeDimension - 1</tt>, <tt>range[2*k]</tt> must be less than or
 *   equal to <tt>range[2*k+1]</tt>, and the <tt>k</tt>'th output value
 *   <tt>out[k]</tt> will be clipped to lie in the interval <tt>range[2*k]
 *   <= out[k] <= range[2*k+1]</tt>.  If this parameter is NULL, then the
 *   output values are not clipped.  However, it's strongly recommended
 *   that this parameter be specified; each range interval should specify
 *   reasonable values for the minimum and maximum in each dimension.
 *
 * @param callbacks
 *   A pointer to a CGFunctionCallbacks structure.  The function uses these
 *   callbacks to evaluate values.  The contents of the callbacks structure
 *   is copied, so, for example, a pointer to a structure on the stack can
 *   be passed in.  */

CG_EXTERN CGFunctionRef CGFunctionCreate(void *info, size_t domainDimension, const float *domain, size_t rangeDimension, const float *range, const CGFunctionCallbacks *callbacks) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @function CGFunctionRetain
 *
 * Equivalent to <tt>CFRetain(function)</tt>.
 */

CG_EXTERN CGFunctionRef CGFunctionRetain(CGFunctionRef function) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*! @function CGFunctionRelease
 *
 * Equivalent to <tt>CFRelease(function)</tt>.
 */

CG_EXTERN void CGFunctionRelease(CGFunctionRef function) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

CG_EXTERN_C_END

#endif	/* CGFUNCTION_H_ */

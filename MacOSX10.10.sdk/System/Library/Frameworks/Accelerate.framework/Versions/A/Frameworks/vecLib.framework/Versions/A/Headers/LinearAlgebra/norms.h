/*  Copyright (c) 2014 Apple Inc.  All rights reserved.                       */

#ifndef __LA_NORMS_HEADER__
#define __LA_NORMS_HEADER__

#define LA_L1_NORM 1
#define LA_L2_NORM 2
#define LA_LINF_NORM 3
typedef unsigned long la_norm_t;

/*!
 @abstract
 Compute a norm of a vector or matrix.

 @discussion
 "vector" refers to the fact that this function computes the norm of its
 argument considered as a vector, and not an operator norm.  The actual
 argument may be either a vector or a matrix.  If it is not a vector or
 matrix, or if the vector_norm parameter is not a supported value, NAN is
 returned.
 */
LA_FUNCTION LA_NONNULL LA_AVAILABILITY
float la_norm_as_float(la_object_t vector, la_norm_t vector_norm);

LA_FUNCTION LA_NONNULL LA_AVAILABILITY
double la_norm_as_double(la_object_t vector, la_norm_t vector_norm);

/*!
 @abstract
 "Normalizes" a vector or matrix.
 
 @discussion
 The returned object has the same direction as the first operand, and has
 norm 1 in the specified vector norm.  If the input vector is zero, it cannot
 be meaningfully normalized and the returned object is also zero.  If the
 parameter vector is not a vector or matrix, or if the vector_norm parameter
 is not a supported value, the returned object has status
 LA_INVALID_PARAMETER_ERROR.
 */
LA_FUNCTION LA_NONNULL LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_normalized_vector(la_object_t vector, la_norm_t vector_norm);

#endif

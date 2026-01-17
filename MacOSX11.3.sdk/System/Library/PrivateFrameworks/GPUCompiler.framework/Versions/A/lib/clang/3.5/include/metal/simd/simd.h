/*  Copyright (c) 2014 Apple, Inc.  All rights reserved.
 *
 *  This header provides small vector (SIMD) and matrix types, and basic
 *  arithmetic and mathematical functions for them.  The vast majority of these
 *  operations are implemented as header inlines, as they can be performed
 *  using just a few instructions on most processors.
 *
 *  These functions are broken into two groups; vector and matrix.  This header
 *  includes all of them, but these may also be included separately.  Consult
 *  these two headers for detailed documentation of what types and operations
 *  are available.
 */

#ifndef __SIMD_HEADER__
#define __SIMD_HEADER__

#include <simd/vector_types.h>
#include <simd/matrix_types.h>
#include <simd/packed.h>

/* Metal version doesn't include <simd/vector.h> and <simd/matrix.h> 
 * since is defined in other headers.
 */
#endif

/*  Copyright (c) 2014 Apple Inc.  All rights reserved.                       */

#ifndef __LA_SPLAT_HEADER__
#define __LA_SPLAT_HEADER__

#include <vecLib/LinearAlgebra/object.h>

#if __has_feature(assume_nonnull)
////  If assume_nonnull is available, use it and use nullability qualifiers.
_Pragma("clang assume_nonnull begin")
#else
////  Otherwise, neuter the nullability qualifiers.
#define __nullable
#define __nonnull
#endif

/*
 Splat objects are a feature that is relatively unique to the LinearAlgebra
 library.

 A splat object represents a matrix or vector whose entries are all equal.
 It may be used in the place of a matrix or vector in many computational
 operations in the library.

 Splat objects are effectively dimensionless matrices.  Computational
 operations that accept them interpret them as having dimensions necessary
 to be compatibile with the other operand.  Because the dimensions of a
 splat are inferred from the other operands, a single operation cannot
 have multiple splat operands.

 A partial list of operations accepting splat operands, and the rules for the
 inferred size:

 Operation                           Inferred Dimensions
 sum(A,splat)                        (rows(A), cols(A))
 sum(splat,A)                        (rows(A), cols(A))
 difference(A,splat)                 (rows(A), cols(A))
 difference(splat,A)                 (rows(A), cols(A))
 elementwise_product(A,splat)        (rows(A), cols(A))
 elementwise_product(splat,A)        (rows(A), cols(A))
 inner_product(A,splat)              (length(A), 1)
 inner_product(splat,A)              (1, length(A))
 matrix_product(A,splat)             (cols(A), 1)
 matrix_product(splat,A)             (1, rows(A))
 */

LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_splat_from_float(float scalar_value,
                                la_attribute_t attributes);

LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_splat_from_double(double scalar_value,
                                 la_attribute_t attributes);

LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_splat_from_vector_element(la_object_t vector,
                                         la_index_t vector_index);

LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_splat_from_matrix_element(la_object_t matrix,
                                         la_index_t matrix_row,
                                         la_index_t matrix_col);

/*
 It is sometimes useful to be able to just generate a matrix or vector with
 fixed dimensions from a splat object, either because the operation you want
 to perform doesn't infer the same dimensions as you would like to use, or
 if the operation you want to perform doesn't support inferring dimensions
 at all.  For this purpose, the following functions are provided.
 
 The vector returned from la_vector_from_splat is always vector_length x 1.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_vector_from_splat(la_object_t splat,
                                 la_count_t vector_length);

LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_matrix_from_splat(la_object_t splat,
                                 la_count_t matrix_rows,
                                 la_count_t matrix_cols);

#if __has_feature(assume_nonnull)
_Pragma("clang assume_nonnull end")
#endif

#endif // __LA_SPLAT_HEADER__

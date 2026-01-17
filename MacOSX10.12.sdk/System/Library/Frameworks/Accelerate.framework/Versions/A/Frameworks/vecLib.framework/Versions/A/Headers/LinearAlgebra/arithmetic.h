/*  Copyright (c) 2014 Apple Inc.  All rights reserved.                       */

#ifndef __LA_ARITHMETIC_HEADER__
#define __LA_ARITHMETIC_HEADER__

#if __has_feature(assume_nonnull)
////  If assume_nonnull is available, use it and use nullability qualifiers.
_Pragma("clang assume_nonnull begin")
#else
////  Otherwise, neuter the nullability qualifiers.
#define __nullable
#define __nonnull
#endif

/*!
 @abstract
 Transpose a vector or matrix.

 @discussion
 Returns a matrix that is the transpose of the source vector or matrix.  If the
 source object is not a vector or matrix, the returned object will have status
 LA_INVALID_PARAMETER_ERROR.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_transpose(la_object_t matrix);

/*!
 @abstract
 Multiply a matrix or vector by a scalar given by a float.
 
 @discussion
 Returns a matrix whose entries are the product of the scalar and the 
 corresponding element of the source matrix.  If the source object is not
 a vector or matrix, the returned object will have status 
 LA_INVALID_PARAMETER_ERROR.
 
 If the scalar type of matrix is not float LA_PRECISION_MISMATCH_ERROR is 
 returned.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_scale_with_float(la_object_t matrix, float scalar);

/*!
 @abstract
 Multiply a matrix or vector by a scalar given by a double.

 @discussion
 Returns a matrix whose entries are the product of the scalar and the
 corresponding element of the source matrix.  If the source object is not
 a vector or matrix, the returned object will have status
 LA_INVALID_PARAMETER_ERROR.
 
 If the scalar type of matrix is not double LA_PRECISION_MISMATCH_ERROR is
 returned.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_scale_with_double(la_object_t matrix, double scalar);

/*!
 @abstract
 Compute the element-wise sum of two vectors or matrices.
 
 @discussion
 If either source operand is not a vector or matrix or splat, or if both
 operands are splats, the result has status LA_INVALID_PARAMETER_ERROR.
 
 The two operands must have the same dimensions.  If they do not, the result
 will have status LA_DIMENSION_MISMATCH_ERROR.  For simplicity, a vector
 of length n, a 1xn matrix, and an nx1 matrix are all treated as having the
 same dimensions.  If 1xn and nx1 or nx1 and 1xn vectors are passed, an nx1
 vector will be created, otherwise orientation matches input.
 
 The result has the same dimensions as the operands, and each element in
 the result is the sum of the corresponding elements in the source operands.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_sum(la_object_t obj_left, la_object_t obj_right);

/*!
 @abstract
 Compute the element-wise difference of two vectors or matrices.

 @discussion
 If either source operand is not a vector or matrix or splat, or if both
 operands are splats, the result has status LA_INVALID_PARAMETER_ERROR.

 The two operands must have the same dimensions.  If they do not, the result
 will have status LA_DIMENSION_MISMATCH_ERROR.  For simplicity, a vector
 of length n, a 1xn matrix, and an nx1 matrix are all treated as having the
 same dimensions.  If 1xn and nx1 or nx1 and 1xn vectors are passed, an nx1
 vector will be created, otherwise orientation matches input.

 The result has the same dimensions as the operands, and each element in
 the result is given by subtracting the corresponding element of obj_right
 from the corresponding element of obj_left.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_difference(la_object_t obj_left, la_object_t obj_right);

/*!
 @abstract
 Compute the element-wise product of two vectors or matrices.

 @discussion
 If either source operand is not a vector or matrix or splat, or if both
 operands are splats, the result has status LA_INVALID_PARAMETER_ERROR.

 The two operands must have the same dimensions.  If they do not, the result
 will have status LA_DIMENSION_MISMATCH_ERROR.  For simplicity, a vector
 of length n, a 1xn matrix, and an nx1 matrix are all treated as having the
 same dimensions.  If 1xn and nx1 or nx1 and 1xn vectors are passed, an nx1
 vector will be created, otherwise orientation matches input.

 The result has the same dimensions as the operands, and each element in
 the result is the product of the corresponding elements in the source operands.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_elementwise_product(la_object_t obj_left, la_object_t obj_right);

/*!
 @abstract
 Compute the inner product of two vectors.
 
 @discussion
 If either operand is a matrix that is not 1xn or nx1, the result has the
 status LA_INVALID_PARAMETER_ERROR.
 
 If either operand is not a vector or matrix or splat, or if both operands
 are splats, the result has the status LA_INVALID_PARAMETER_ERROR.

 If the lengths of the two operands do not match, the result has the status
 LA_DIMENSION_MISMATCH_ERROR.
 
 Otherwise the result is a 1x1 matrix containing the inner product:
 
        sum_{i=0...length} vector_left[i] * vector_right[i]
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_inner_product(la_object_t vector_left, la_object_t vector_right);

/*!
 @abstract
 Compute the outer product of two vectors.

 @discussion
 Splats are not supported by this function.  If either operand
 is a splat, the result has status LA_INVALID_PARAMETER_ERROR.

 If either operand is a matrix that is not 1xn or nx1, the result has the
 status LA_INVALID_PARAMETER_ERROR.

 If either operand is not a vector or matrix, the result has the status
 LA_INVALID_PARAMETER_ERROR.
 
 Otherwise the result is a matrix containg the outer product.  It has
 length(vector_left) rows and length(vector_right) columns.  The i,jth
 element of the matrix is vector_left[i] * vector_right[j].
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_outer_product(la_object_t vector_left, la_object_t vector_right);

/*!
 @abstract
 Compute a matrix product.

 @discussion
 Left splat operands are treated as 1 x rows(matrix_right) vectors and right 
 splat operands are treated as cols(matrix_left) x 1 vectors.
 
 For convenience, in certain situations vector operands may be implicitly
 transposed.  Specifically,
 
 If cols(matrix_left) == rows(matrix_right)
 	rows(matrix_left) x cols(matrix_right) = matrix_left * matrix_right
 Else if cols(matrix_left) == 1 and rows(matrix_left) == rows(matrix_right)
 	1 x cols(matrix_right) = transpose(matrix_left) * matrix_right
 Else if rows(matrix_right) == 1 and cols(matrix_left) == cols(matrix_right)
 	rows(matrix_left) x 1 = matrix_left * transpose(matrix_right)
 Else
  	result has the status LA_DIMENSION_MISMATCH_ERROR.

 If either operand is not a vector or matrix or splat, or if both operands
 are splats, the result has the status LA_INVALID_PARAMETER_ERROR.

 Otherwise the result is a matrix with 1 row if matrix_left is vector or splat 
 and rows(matrix_left) otherwise, and 1 column if matrix_right is vector or
 splat and cols(matrix_right) otherwise.
 
 If cols(matrix_left) == rows(matrix_right), the i,jth element of the matrix is:
 		sum_{k=0...cols(matrix_left)} matrix_left[i,k] * matrix_right[k,j]
 If cols(matrix_left) == 1 and rows(matrix_left) == rows(matrix_right), the 
    0,jth element of matrix is:
 		sum_{k=0...rows(matrix_right)} matrix_left[k,0] * matrix_right[k,j]
 If rows(matrix_right) == 1 and cols(matrix_left) == cols(matrix_right), the
 	i,0th element of matrix is:
 	sum_{k=0...cols(matrix_left)} matrix_left[i,k] * matrix_right[0,k]
 
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_matrix_product(la_object_t matrix_left,
                              la_object_t matrix_right);

#if __has_feature(assume_nonnull)
_Pragma("clang assume_nonnull end")
#endif

#endif // __LA_ARITHMETIC_HEADER__

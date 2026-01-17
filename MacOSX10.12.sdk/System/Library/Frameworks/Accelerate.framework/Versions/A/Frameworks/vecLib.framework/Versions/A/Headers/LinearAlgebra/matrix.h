/*  Copyright (c) 2014 Apple Inc.  All rights reserved.                       */

#ifndef __LA_MATRIX_HEADER__
#define __LA_MATRIX_HEADER__

#if __has_feature(assume_nonnull)
////  If assume_nonnull is available, use it and use nullability qualifiers.
_Pragma("clang assume_nonnull begin")
#else
////  Otherwise, neuter the nullability qualifiers.
#define __nullable
#define __nonnull
#endif

/*!
 @brief When creating a matrix object from existing data, these hints allow the
 user to pass useful information about the structure of the matrix.

 @discussion When creating a matrix container from an existing buffer, these
 hints allow the user to pass useful information about the traits of the
 matrix.  Increasing the amount of information known about a matrix can in some
 cases improve performance.  Consider the extreme where a matrix is a diagonal
 matrix.  When multiplying this matrix with another, if it was not known to be
 diagonal the cost would be O(N^3) but the extra information allows the cost
 to drop to O(N^2).

 In many cases, the framework can inspect the data to determine this information
 when it is not made available by hint, but for certain traits, such as
 symmetric positive definiteness, this can be a costly operation, especially if
 the user already knows the trait to be true.

 These are however hints, an incorrect hint will not break the intended
 operation, in the worst case it adds overhead.  When in doubt, it is
 recommended that rather than guessing, if no information is known, use
 LA_NO_HINT.
 */
#define LA_NO_HINT                       (0U)
#define LA_SHAPE_DIAGONAL                (1U << 0)
#define LA_SHAPE_LOWER_TRIANGULAR        (1U << 1)
#define LA_SHAPE_UPPER_TRIANGULAR        (1U << 2)
#define LA_FEATURE_SYMMETRIC             (1U << 16)
#define LA_FEATURE_POSITIVE_DEFINITE     (1U << 17)
#define LA_FEATURE_DIAGONALLY_DOMINANT   (1U << 18)
typedef unsigned long la_hint_t;

/*!
 @abstract
 Create a matrix using data from a buffer of floats.  Ownership of the buffer
 remains in control of the caller.

 @param buffer
 Pointer to float data providing the elements of the matrix.

 @param matrix_rows
 The number of rows in the matrix.

 @param matrix_cols
 The number of columns in the matrix.

 @param matrix_row_stride
 The offset in the buffer (measured in floats) between corresponding elements
 in consecutive rows of the matrix.  Must be positive.

 @param matrix_hint
 Flags describing special matrix structures.

 @param attributes
 Attributes to attach to the new la_object_t object.  Pass LA_DEFAULT_ATTRIBUTES
 to create a normal object.

 @return a new la_object_t object representing the matrix.

 @discussion
 This function creates an object representing a matrix whose entries are
 copied out of the supplied buffer of floats.  Negative or zero strides
 are not supported by this function (but note that you can reverse the
 rows or columns using the la_matrix_slice function defined below).

 This routine assumes that the elements of the matrix are stored in the buffer
 in row-major order.  If you need to work with data that is in column-major
 order, you can do that as follows:

 1. Use this routine to create a matrix object, but pass the number of
 columns in your matrix for the matrix_rows parameter and vice-versa.  For
 the matrix_row_stride parameter, pass the column stride of your matrix.

 2. Make a new matrix transpose object from the object created in step 1.  The
 resulting object represents the matrix that you want to work with.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_matrix_from_float_buffer(const float *buffer,
                                           la_count_t matrix_rows,
                                           la_count_t matrix_cols,
                                           la_count_t matrix_row_stride,
                                           la_hint_t matrix_hint,
                                           la_attribute_t attributes);

/*!
 @abstract
 Create a matrix using data from a buffer of doubles.  Ownership of the buffer
 remains in control of the caller.

 @param buffer
 Pointer to double data providing the elements of the matrix.

 @param matrix_rows
 The number of rows in the matrix.

 @param matrix_cols
 The number of columns in the matrix.

 @param matrix_row_stride
 The offset in the buffer (measured in doubles) between corresponding elements
 in consecutive rows of the matrix.  Must be positive.

 @param matrix_hint
 Flags describing special matrix structures.

 @param attributes
 Attributes to attach to the new la_object_t object.  Pass LA_DEFAULT_ATTRIBUTES
 to create a normal object.

 @return a new la_object_t object representing the matrix.

 @discussion
 This function creates an object representing a matrix whose entries are
 copied out of the supplied buffer of doubles.  Negative or zero strides
 are not supported by this function (but note that you can reverse the
 rows or columns using the la_matrix_slice function defined below).

 This routine assumes that the elements of the matrix are stored in the buffer
 in row-major order.  If you need to work with data that is in column-major
 order, you can do that as follows:

 1. Use this routine to create a matrix object, but pass the number of
 columns in your matrix for the matrix_rows parameter and vice-versa.  For
 the matrix_row_stride parameter, pass the column stride of your matrix.

 2. Make a new matrix transpose object from the object created in step 1.  The
 resulting object represents the matrix that you want to work with.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_matrix_from_double_buffer(const double *buffer,
                                            la_count_t matrix_rows,
                                            la_count_t matrix_cols,
                                            la_count_t matrix_row_stride,
                                            la_hint_t matrix_hint,
                                            la_attribute_t attributes);

/*!
 @abstract
 Create a matrix using data from a buffer of floats.  Ownership of the buffer
 is transferred from the caller to the returned object.

 @param buffer
 Pointer to float data providing the elements of the matrix.

 @param matrix_rows
 The number of rows in the matrix.

 @param matrix_cols
 The number of columns in the matrix.

 @param matrix_row_stride
 The offset in the buffer (measured in floats) between corresponding elements
 in consecutive rows of the matrix.  Must be positive.

 @param matrix_hint
 Flags describing special matrix structures.

 @param deallocator
 Callback to be used to deallocate the buffer when the returned matrix object
 is destroyed.

 @param attributes
 Attributes to attach to the new la_object_t object.  Pass LA_DEFAULT_ATTRIBUTES
 to create a normal object.

 @return a new la_object_t object representing the matrix.

 @discussion
 This function creates an object representing a matrix whose entries are
 copied out of the supplied buffer of floats.  Negative or zero strides
 are not supported by this function (but note that you can reverse the
 rows or columns using the la_matrix_slice function defined below).

 This routine assumes that the elements of the matrix are stored in the buffer
 in row-major order.  If you need to work with data that is in column-major
 order, you can do that as follows:

 1. Use this routine to create a matrix object, but pass the number of
 columns in your matrix for the matrix_rows parameter and vice-versa.  For
 the matrix_row_stride parameter, pass the column stride of your matrix.

 2. Make a new matrix transpose object from the object created in step 1.  The
 resulting object represents the matrix that you want to work with.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_matrix_from_float_buffer_nocopy(float *buffer,
                                                  la_count_t matrix_rows,
                                                  la_count_t matrix_cols,
                                                  la_count_t matrix_row_stride,
                                                  la_hint_t matrix_hint,
                                                  __nullable la_deallocator_t deallocator,
                                                  la_attribute_t attributes);

/*!
 @abstract
 Create a matrix using data from a buffer of doubles.  Ownership of the buffer
 is transferred from the caller to the returned object.

 @param buffer
 Pointer to double data providing the elements of the matrix.

 @param matrix_rows
 The number of rows in the matrix.

 @param matrix_cols
 The number of columns in the matrix.

 @param matrix_row_stride
 The offset in the buffer (measured in doubles) between corresponding elements
 in consecutive rows of the matrix.  Must be positive.

 @param matrix_hint
 Flags describing special matrix structures.

 @param deallocator
 Callback to be used to deallocate the buffer when the returned matrix object
 is destroyed.

 @param attributes
 Attributes to attach to the new la_object_t object.  Pass LA_DEFAULT_ATTRIBUTES
 to create a normal object.

 @return a new la_object_t object representing the matrix.

 @discussion
 This function creates an object representing a matrix whose entries are
 copied out of the supplied buffer of doubles.  Negative or zero strides
 are not supported by this function (but note that you can reverse
 the rows or columns using the la_matrix_slice function defined below).

 This routine assumes that the elements of the matrix are stored in the buffer
 in row-major order.  If you need to work with data that is in column-major
 order, you can do that as follows:

 1. Use this routine to create a matrix object, but pass the number of
 columns in your matrix for the matrix_rows parameter and vice-versa.  For
 the matrix_row_stride parameter, pass the column stride of your matrix.

 2. Make a new matrix transpose object from the object created in step 1.  The
 resulting object represents the matrix that you want to work with.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_matrix_from_double_buffer_nocopy(double *buffer,
                                                   la_count_t matrix_rows,
                                                   la_count_t matrix_cols,
                                                   la_count_t matrix_row_stride,
                                                   la_hint_t matrix_hint,
                                                   __nullable la_deallocator_t deallocator,
                                                   la_attribute_t attributes);

/*!
 @abstract
 Stores the elements of a matrix to a buffer.
 
 @param buffer
 Pointer to the destination buffer.
 
 @param buffer_row_stride
 Offset (measured in floats) between the destinations of corresponding elements
 of consecutive rows of the matrix.  Must be positive.
 
 @param matrix
 The matrix to store.
 
 @discussion
 The buffer must be large enough to accomodate the matrix being stored.
 Specifically, it must have sufficient space to hold
 
    buffer_row_stride*(la_matrix_rows(matrix)-1) + la_matrix_cols(matrix)
 
 float elements.
 
 This function supports storing the contents of a vector as well as a matrix.
 A vector of length n will be interpreted as a rows(matrix) x cols(matrix) by 
 this function.  If the object is a vector or matrix and does not have an error 
 status, its contents are stored to the buffer.  If it has an error status, NaNs 
 are stored to the buffer.
 
 If the object is not a matrix or vector, nothing is written to the buffer and
 LA_INVALID_PARAMETER_ERROR is returned.
 */
LA_FUNCTION LA_AVAILABILITY
la_status_t la_matrix_to_float_buffer(float *buffer,
                                            la_count_t buffer_row_stride,
                                            la_object_t matrix);

/*!
 @abstract
 Stores the elements of a matrix to a buffer.

 @param buffer
 Pointer to the destination buffer.

 @param buffer_row_stride
 Offset (measured in doubles) between the destinations of corresponding elements
 of consecutive rows of the matrix.  Must be positive.

 @param matrix
 The matrix to store.

 @discussion
 The buffer must be large enough to accomodate the matrix being stored.
 Specifically, it must have sufficient space to hold

    buffer_row_stride*(la_matrix_rows(matrix)-1) + la_matrix_cols(matrix)

 double elements.
 
 This function supports storing the contents of a vector as well as a matrix.
 A vector of length n will be interpreted as a rows(matrix) x cols(matrix) by
 this function.  If the object is a vector or matrix and does not have an error
 status, its contents are stored to the buffer.  If it has an error status, NaNs
 are stored to the buffer.

 If the object is not a matrix or vector, nothing is written to the buffer and
 LA_INVALID_PARAMETER_ERROR is returned.
 */
LA_FUNCTION LA_AVAILABILITY
la_status_t la_matrix_to_double_buffer(double *buffer,
                                             la_count_t buffer_row_stride,
                                             la_object_t matrix);

/*!
 @abstract
 Get the number of rows in a matrix.
 
 @discussion
 If the argument has an error status, zero is returned.
 If the argument is a vector, the number of rows may be 1 or length(vector) 
 depending on the orientation of the vector.
 If the argument is a matrix, the number of rows is returned.
 Otherwise, zero is returned.
 */
LA_FUNCTION LA_CONST LA_AVAILABILITY
la_count_t la_matrix_rows(la_object_t matrix);

/*!
 @abstract
 Get the number of columns in a matrix.

 @discussion
 If the argument has an error status, zero is returned.
 If the argument is a vector, the number of columns may be 1 or length(vector)
 depending on the orientation of the vector.
 If the argument is a matrix, the number of columns is returned.
 Otherwise, zero is returned.
 */
LA_FUNCTION LA_CONST LA_AVAILABILITY
la_count_t la_matrix_cols(la_object_t matrix);

/*!
 @abstract
 Create a slice of a matrix.
 
 @param matrix
 The matrix to be sliced.
 
 @param matrix_first_row
 The index of the row of the source matrix containing the first element of
 new slice matrix.
 
 @param matrix_first_col
 The index of the column of the source matrix containing the first element
 of the slice matrix.
 
 @param matrix_row_stride
 The offset in the source matrix between rows that will be consecutive in
 the slice matrix.
 
 @param matrix_col_stride
 The offset in the source matrix between columns that will be consecutve in
 the slice matrix.
 
 @param slice_rows
 The number of rows in the slice matrix.
 
 @param slice_cols
 The number of columns in the slice matrix.
 
 @return
 A new matrix with size slice_rows x slice_cols whose elements are taken
 from the source matrix.
 
 @discussion
 The result object is the slice_rows x slice_cols matrix whose i,jth entry is:
 
    matrix[matrix_first_row + i*matrix_row_stride,
           matrix_first_col + j*matrix_col_stride]
 
 Slices provide an efficient means to operate on tiles and strides.  These are
 lightweight objects that reference the storage of the matrix from which they
 originate.  In most cases, creating a slice does not require any allocation
 beyond the object representing the slice, nor require copying.  In some 
 less common cases, a copy may be required.
 
 This function supports slicing a vector (interpreted as 
 rows(matrix) x cols(matrix)) or a matrix.  If the object is not a matrix or 
 vector, the returned object will have status LA_INVALID_PARAMETER_ERROR.

 If the slice references indices that are less than zero or greater than or
 equal to the dimensions of the matrix, LA_SLICE_OUT_OF_BOUNDS_ERROR is 
 returned.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_matrix_slice(la_object_t matrix,
                                 la_index_t matrix_first_row,
                                 la_index_t matrix_first_col,
                                 la_index_t matrix_row_stride,
                                 la_index_t matrix_col_stride,
                                 la_count_t slice_rows,
                                 la_count_t slice_cols);

LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_identity_matrix(la_count_t matrix_size,
                                    la_scalar_type_t scalar_type,
                                    la_attribute_t attributes);

/*!
 @abstract
 Create a matrix with a specified diagonal provided by a vector, and zeros in
 all the other entries.
 
 @param vector
 Vector providing the data for the non-zero diagonal.
 
 @param matrix_diagonal
 The index of the non-zero diagonal.
 
 @discussion
 Creates a new matrix with entries on the specified diagonal taken from the
 vector argument, and zeros in the other entries.  The matrix is square, and
 has size length(vector) + abs(matrix_diagonal).
 
 If matrix_diagonal is zero, the main diagonal is set.  If matrix_diagonal is
 +1, the first superdiagonal is set.  If matrix_diagonal is -2, the second
 subdiagonal is set.
 
 The diagonal may be specified by a vector or by a matrix that has only one
 row or only one column.  If the provided object is not a vector or matrix,
 or is a matrix with both dimensions larger than one, the returned object
 will have status LA_INVALID_PARAMETER_ERROR.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_diagonal_matrix_from_vector(la_object_t vector,
                                            la_index_t matrix_diagonal);

/*!
 @abstract
 Creates a vector from the specified row of the matrix.
 
 @param matrix
 Matrix from which to create the row vector.
 
 @param matrix_row.
 The zero-based index of the row to create the vector from.  
 
 @return
 The resulting vector is a 1 x cols(matrix) vector.
 
 @discussion
 Creates a vector from the specified row of the matrix.  If the value for 
 matrix_row is less than zero or greater than rows(matrix)-1,
 LA_INVALID_PARAMETER_ERROR is returned.  
 
 If matrix is a splat, LA_INVALID_PARAMETER_ERROR is returned.

 Always returns a 1 x vector_length vector.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_vector_from_matrix_row(la_object_t matrix,
                                           la_count_t matrix_row);

/*!
 @abstract
 Creates a vector from the specified column of the matrix.
 
 @param matrix
 Matrix from which to create the column vector.
 
 @param matrix_col.
 The zero-based index of the column to create the vector from.
 
 @return
 The resulting vector is a rows(matrix) x 1 vector.
 
 @discussion
 Creates a vector from the specified column of the matrix.  If the value for
 matrix_col is less than zero or greater than cols(matrix)-1,
 LA_INVALID_PARAMETER_ERROR is returned.
 
 If matrix is a splat, LA_INVALID_PARAMETER_ERROR is returned.

 Always returns a vector_length x 1 vector.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_vector_from_matrix_col(la_object_t matrix,
                                           la_count_t matrix_col);

/*!
 @abstract
 Creates a vector from the specified diagonal of the matrix.
 
 @param matrix
 Matrix from which to create the vector.
 
 @param matrix_diagonal.
 The index of the diagonal to create the vector from.
 
 @return
 The resulting vector is a length x 1 vector where length is 
 min(rows(matrix),cols(matrix)-abs(matrix_diagonal)
 
 @discussion
 Creates a new vector with entries on the specified diagonal taken from the
 vector argument, and zeros in the other entries.  The matrix is square, and
 has size length(vector) + abs(matrix_diagonal).
 
 If matrix_diagonal is zero, the main diagonal is set.  If matrix_diagonal is
 +1, the first superdiagonal is set.  If matrix_diagonal is -2, the second
 subdiagonal is set.
 
 Creates a vector from the specified diagonal of the matrix.  If the value for
 matrix_diagonal is less than zero and abs(matrix_diagonal) > rows(matrix)-1,
 or if matrix_diagonal is greater than zero and matrix_diagonal > 
 cols(matrix)-1, LA_INVALID_PARAMETER_ERROR is returned.
 
 If matrix is a splat, LA_INVALID_PARAMETER_ERROR is returned.

 Always returns a vector_length x 1 vector.
 */
LA_FUNCTION LA_AVAILABILITY LA_RETURNS_RETAINED
la_object_t la_vector_from_matrix_diagonal(la_object_t matrix,
                                              la_index_t matrix_diagonal);

#if __has_feature(assume_nonnull)
_Pragma("clang assume_nonnull end")
#endif

#endif // __LA_MATRIX_HEADER__

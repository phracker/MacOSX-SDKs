/*  Copyright (c) 2014 Apple Inc.  All rights reserved.                       */

#ifndef __SPARSE_BLAS_H
#define __SPARSE_BLAS_H

/*!
 @header Sparse/BLAS.h
 @discussion

 These sparse BLAS routines provide access to sparse computation while hiding
 the details of the sparse matrix storage formats.
 
 A brief note on the naming convention used.  When an operation has two 
 operands, if both operands are sparse then _sparse_ will be in the name, but if
 one operand is sparse and the other dense, then _dense_ will be in the name.  
 For example, sparse_inner_product_sparse_float is a sparse-sparse operation and 
 sparse_inner_product_dense_float is a sparse-dense operation.  Any operation that 
 has a single matrix or vector is going to be operating on sparse structures and 
 no _dense_ or _sparse_ is added to the name.
 
 This sparse BLAS package utilizes a compressed form vector where two storage 
 arrays of the same size are used, the first to store the nonzero values of the 
 vector, the other to store the index of the nonzero values.  For example, for
 the dense vector:
 
 d = [3, 0, 0, 7, 9, 0, 4, 0, 0]
 
 the sparse vector will be stored as two arrays:
 
 s =     [3, 7, 9, 4]
 
 sindx = [0, 3, 4, 6]
 
 These two arrays hold their values as consecutive elements and are referred to
 throughout the documentation as the dense storage of the sparse vector.
 
 Indices are always assumed to be stored in ascending order. Additionally, 
 indices are assumed to be unique.  Undefined behavior if either of these 
 assumptions are not met.
 
 All indices are 0 based (the first element of a pointer is ptr[0]).
 
 Due to the variety of sparse matrix representations, the details of the storage
 format are hidden from the developer.  There are however two general flavors;
 point wise and block wise storage.
 
 With a point wise format, individual elements are stored within the matrix 
 representation. Point wise formats allow for adding single (val,i,j) values,
 collections of (val,i,j) values, or sparse vectors as a row or column.
 
 With block wise storage formats, blocks of elements are stored within the 
 matrix. Block formats allow for adding blocks of values at specified block 
 indices. For example if block sizes are constant, adding the K x L block to the 
 matrix at block location bi,bj will add values to 
 matrix[bi*K:bi*K+K-1,bj*L:bj*L-1]. With block storage formats, block sizes can 
 either be uniform throughout the matrix, or variable based on row and column 
 location.
 
 Beyond selecting a point wise or block wise format, the matrix storage format 
 is hidden from the developer.
 
 Matrix objects must be memory managed.  They are created with a create routine,
 used to completion, and then must be destroyed to release any associated
 memory.  The typical work flow is as follows:
 
 <pre>
 // Create matrix object and check for error
 sparse_matrix_float A = sparse_matrix_create_float(40,40);
 if ( !A ) { // handle error }
 
 // Insert values from existing arrays values, iIndx, and jIndx
 // Then check for error
 if ( sparse_insert_entry_float( A, 12, values, iIndx, jIndx ) ) { // handle error }
 
 // Perform computation
 float nrm = sparse_matrix_norm_float( A, SPARSE_NORM_INF );
 
 // Clean up
 sparse_matrix_destroy( A );
 </pre>
 
 Since data insertion into the internal storage is very expensive, caused by data
 movement and possible memory allocation, data insertion functions do not update
 the internal storage immediately. Rather, all data insertions are put into a pending
 queue. The internal storage is then updated automatically when required by the BLAS
 operations, or explicitly triggered by calling sparse_commit().
 
 When commit is triggered automatically by the BLAS operation, expect the operation
 to take longer time. If this is undesirable, consider calling sparse_commit() in a
 less time-sensitive code segment.

 @copyright Copyright (c) 2015 Apple Inc. All rights reserved.
 */

#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef CBLAS_H
#include <vecLib/cblas.h>
#endif

#ifndef __SPARSE_TYPES_H
#include <vecLib/Sparse/Types.h>
#endif

#pragma mark - Level 1 Routines -

  /* Level 1 Computational Routines */
/*!
 @functiongroup Level 1
 @abstract Level 1 routines consisting of vector-vector operations
 */

/*!
 @abstract
 Compute the inner product of sparse vector x with dense vector y.
 
 @param nz
 The number of nonzero entries in the sparse vector x.
 
 @param x
 Pointer to the dense storage for the values of the sparse vector x.  The
 corresponding entry in indx holds the index of the value.  Contains nz values.
 
 @param indx
 Pointer to the dense storage for the index values of the sparse vector x.  The
 corresponding entry in x holds the values of the vector.  Contains nz values.
 
 Indices are always assumed to be stored in ascending order. Additionally,
 indices are assumed to be unique.  Undefined behavior if either of these
 assumptions are not met.
 
 All indices are 0 based (the first element of a pointer is ptr[0]).
 
 @param y
 Pointer to the dense vector y.  Accessed as y[indx[0..nz-1]*incy], so dimension 
 must be compatible with largest index value in indx.  Behavior undefined if 
 this is not met.  Negative strides are supported.  Note, unlike dense BLAS 
 routines, the pointer points to the last element when stride is negative.
 
 @param incy
 Increment between valid values in the dense vector y.  Negative strides are
 supported.
 
 @result
 On exit the result of the inner product is returned.
 
 @discussion
 Compute the inner product of sparse vector x with dense vector y.  Returns zero 
 if nz is less than or equal to zero.
 
 */
float sparse_inner_product_dense_float( sparse_dimension nz,
                                     const float * __restrict x,
                                     const sparse_index * __restrict indx,
                                     const float * __restrict y,
                                     sparse_stride incy );
double sparse_inner_product_dense_double( sparse_dimension nz,
                                       const double * __restrict x,
                                       const sparse_index * __restrict indx,
                                       const double * __restrict y,
                                       sparse_stride incy );


/*!
 @abstract
 Compute the inner product of sparse vector x with sparse vector y.
 
 @param nzx
 The number of nonzero entries in the sparse vector x.
 
 @param nzy
 The number of nonzero entries in the sparse vector y.
 
 @param x
 Pointer to the dense storage for the values of the sparse vector x.  The
 corresponding entry in indx holds the index of the value.  Contains nzx values.
 
 @param indx
 Pointer to the dense storage for the index values of the sparse vector x.  The
 corresponding entry in x holds the values of the vector.  Contains nzx values.
 
 Indices are always assumed to be stored in ascending order. Additionally,
 indices are assumed to be unique.  Undefined behavior if either of these
 assumptions are not met.
 
 All indices are 0 based (the first element of a pointer is ptr[0]).
 
 @param y
 Pointer to the dense storage for the values of the sparse vector y.  The
 corresponding entry in indy holds the index of the value.  Contains nzy values.
 
 @param indy
 Pointer to the dense storage for the index values of the sparse vector y.  The
 corresponding entry in y holds the values of the vector.  Contains nzy values.
 
 Indices are always assumed to be stored in ascending order. Additionally,
 indices are assumed to be unique.  Undefined behavior if either of these
 assumptions are not met.
 
 All indices are 0 based (the first element of a pointer is ptr[0]).
 
 @result
 On exit the result of the inner product is returned.
 
 @discussion
 Compute the inner product of sparse vector x with sparse vector y.  Returns
 zero if nzx or nzy is less than or equal to zero.
 
 */
float sparse_inner_product_sparse_float( sparse_dimension nzx, sparse_dimension nzy,
                                      const float * __restrict x,
                                      const sparse_index * __restrict indx,
                                      const float * __restrict y,
                                      const sparse_index * __restrict indy );
double sparse_inner_product_sparse_double( sparse_dimension nzx, sparse_dimension nzy,
                                        const double * __restrict x,
                                        const sparse_index * __restrict indx,
                                        const double * __restrict y,
                                        const sparse_index * __restrict indy );

/*!
 @abstract
 Scales the sparse vector x by alpha and adds the result to the dense vector y.
 
 y = alpha * x + y
 
 @param nz
 The number of nonzero entries in the sparse vector x.
 
 @param alpha
 Scalar multiplier of x.
 
 @param x
 Pointer to the dense storage for the values of the sparse vector x.  The
 corresponding entry in indx holds the index of the value.  Contains nz values.
 
 @param indx
 Pointer to the dense storage for the index values of the sparse vector x.  The
 corresponding entry in x holds the values of the vector.  Contains nz values.
 
 Indices are always assumed to be stored in ascending order. Additionally,
 indices are assumed to be unique.  Undefined behavior if either of these
 assumptions are not met.
 
 All indices are 0 based (the first element of a pointer is ptr[0]).
 
 @param y
 Pointer to the dense vector y.  Accessed as y[indx[0..nz-1]*incy], so dimension
 must be compatible with largest index value in indx.  Behavior undefined if
 this is not met.  Negative strides are supported.  Note, unlike dense BLAS
 routines, the pointer points to the last element when stride is negative.
 
 @param incy
 Increment between valid values in the dense vector y.  Negative strides are
 supported.
 
 @result
 On exit y has been updated as y = alpha * x + y. If nz is less than or
 equal to zero or alpha is equal to zero, y is unchanged.
 
 @discussion
 Scales the sparse vector x by alpha and adds the result to the dense vector y.
 If alpha or nz is zero, y is unchanged.
 
 If the desired operation is y = alpha * x, then an efficient option is to 
 create the y buffer of zeros as y = calloc(sizeof(..)*ySize) and then perform
 the operation with the zero filled y.
 */
void sparse_vector_add_with_scale_dense_float( sparse_dimension nz, float alpha,
                                            const float * __restrict x,
                                            const sparse_index * __restrict indx,
                                            float * __restrict y,
                                            sparse_stride incy );
void sparse_vector_add_with_scale_dense_double( sparse_dimension nz, double alpha,
                                             const double * __restrict x,
                                             const sparse_index * __restrict indx,
                                             double * __restrict y,
                                             sparse_stride incy );

/*!
 @abstract
 Compute the specified norm of the sparse vector x.
 
 @param nz
 The number of nonzero values in the sparse vector x.
 
 @param x
 Pointer to the dense storage for the values of the sparse vector x.  The
 corresponding entry in indx holds the index of the value.  Contains nz values.
 
 @param indx
 Pointer to the dense storage for the index values of the sparse vector x.  The
 corresponding entry in x holds the values of the vector.  Contains nz values.
 
 Indices are always assumed to be stored in ascending order. Additionally,
 indices are assumed to be unique.  Undefined behavior if either of these
 assumptions are not met.
 
 All indices are 0 based (the first element of a pointer is ptr[0]).
 
 @param norm
 Specify the norm to be computed.  Must be one of SPARSE_NORM_ONE, SPARSE_NORM_TWO,
 or SPARSE_NORM_INF.  See discussion for further details.
 
 @result
 Upon success, return the requested norm.
 
 @discussion
 Compute the specified norm of the sparse vector x.  Specify one of:
 1) SPARSE_NORM_ONE : sum over i ( | x[i] | )
 2) SPARSE_NORM_TWO : sqrt( sum over i (x[i])^2 )
 3) SPARSE_NORM_INF : max over i ( | x[i] | )
 4) SPARSE_NORM_R1  : Not supported, undefined.
 
 If norm is not one of the enumerated norm types, the default value is
 SPARSE_NORM_INF.
 
 */
float sparse_vector_norm_float( sparse_dimension nz, const float * __restrict x,
                             const sparse_index * __restrict indx, sparse_norm norm );
double sparse_vector_norm_double( sparse_dimension nz, const double * __restrict x,
                               const sparse_index * __restrict indx, sparse_norm norm );



#pragma mark - Level 2 Routines -

               /* Level 2 Computational Routines */
/*!
 @functiongroup Level 2
 @abstract Level 2 routines consisting of matrix-vector operations
 */

/*!
 @abstract
 Multiplies the dense vector x by the sparse matrix A and adds the result to
 the dense vector y.
 
 y = alpha * op(A) * x + y; where op(A) is either A or the transpose of A
 
 @param transa 
 Specifies whether to perform the operation with A or the transpose of A.
 Must be one of CblasNoTrans or CblasTrans.
 
 @param alpha
 Scalar multiplier of A.
 
 @param A
 The sparse matrix.
 
 @param x
 Pointer to the dense vector x. The dimension must be the number of columns of
 the matrix A when transa is no transpose or the number of rows of the matrix A
 when transa is transpose.  Behavior undefined if this is not met.  Negative 
 strides are supported.  Note, unlike dense BLAS routines, the pointer points to 
 the last element when stride is negative. 
 
 @param incx
 Increment between valid values in the dense vector x. Negative strides are
 supported.
 
 @param y
 Pointer to the dense vector y. The dimension must be the number of rows of
 the matrix A when transa is no transpose or the number of columns of the matrix 
 A when transa is transpose.  Behavior undefined if this is not met.  Negative
 strides are supported.  Note, unlike dense BLAS routines, the pointer points to
 the last element when stride is negative.
 
 @param incy
 Increment between valid values in the dense vector y.  Negative strides are
 supported.

 @result
 On success return SPARSE_SUCCESS and y has been updated with result of the 
 operation.  Will return SPARSE_ILLEGAL_PARAMETER if transa is invalid and y will 
 be unchanged.

 @discussion
 Multiplies the dense vector x by the sparse matrix A and adds the result to
 the dense vector y (y = alpha * op(A) * x + y, where op(A) is either A
 or the transpose of A).
 
 If the desired operation is y = A * x, then an efficient option is to create
 the y buffer of zeros as y = calloc(sizeof(..)*ySize) and then perform
 the operation with the zero filled y.
 */
sparse_status sparse_matrix_vector_product_dense_float( enum CBLAS_TRANSPOSE transa,
                                                  float alpha,
                                                  sparse_matrix_float A,
                                                  const float * __restrict x,
                                                  sparse_stride incx,
                                                  float * __restrict y,
                                                  sparse_stride incy );
sparse_status sparse_matrix_vector_product_dense_double( enum CBLAS_TRANSPOSE transa,
                                                   double alpha,
                                                   sparse_matrix_double A,
                                                   const double * __restrict x,
                                                   sparse_stride incx,
                                                   double * __restrict y,
                                                   sparse_stride incy );

/*!
 @abstract
 Solve the system of equations x = alpha * T^{-1} * x for x where x is a dense
 vector and T is a triangular sparse matrix.
 
 @param transt
 Specifies whether to perform the operation with T or the transpose of T.
 Must be one of CblasNoTrans or CblasTrans.
 
 @param alpha
 Scalar multiplier of T.
 
 @param T
 The sparse triangular matrix.  Must be upper or lower triangular matrix.
 Will return SPARSE_ILLEGAL_PARAMETER if not a triangular matrix.
 
 @param x
 Pointer to the dense vector x. The dimension must match the dimension of the
 triangular matrix T. Behavior undefined if this is not met.  Negative
 strides are supported.  Note, unlike dense BLAS routines, the pointer points to
 the last element when stride is negative.  On exit holds the solution to the
 system of equations.
 
 @param incx
 Increment between valid values in the dense vector x. Negative strides are
 supported.
 
 @result
 On success, SPARSE_SUCCESS is returned and x has been updated with result of the 
 operation.  Will return SPARSE_ILLEGAL_PARAMETER if transt is invalid or if the
 matrix T is not triangular and x will be unchanged.
 
 @discussion
 Solve the system of equations x = alpha * T^{-1} * x for x where x is a dense
 vector and T is a triangular sparse matrix.  The matrix T must be an upper or
 lower triangular matrix.
 
 */
sparse_status sparse_vector_triangular_solve_dense_float( enum CBLAS_TRANSPOSE transt,
                                              float alpha, sparse_matrix_float T,
                                              float * __restrict x,
                                              sparse_stride incx );
sparse_status sparse_vector_triangular_solve_dense_double( enum CBLAS_TRANSPOSE transt,
                                               double alpha,
                                               sparse_matrix_double T,
                                               double * __restrict x,
                                               sparse_stride incx );


/*!
 @abstract
 Compute the outer product of the dense vector x and the sparse vector y and
 return a new sparse matrix in the uninitialized pointer sparse matrix pointer 
 C.  C = alpha * x * y'
 
 @param M
 The number of rows of x and the resulting matrix.
 
 @param N
 The number of columns of the resulting matrix.  The number of nonzero values 
 must be less than or equal to N.
 
 @param nz
 The number of nonzero values in the sparse vector y.  Must be less than or
 equal to N.
 
 @param alpha
 Scalar multiplier of x.
 
 @param x
 Pointer to the dense vector x.  Must be M number of elements.  Negative strides 
 are supported.  Note, unlike dense BLAS routines, the pointer points to the 
 last element when stride is negative.
 
 @param incx
 Increment between valid values in the dense vector x.  Negative strides are
 supported.
 
 @param y
 Pointer to the dense storage for the values of the sparse vector y.  The
 corresponding entry in indy holds the index of the value.  Contains nz values.
 
 @param indy
 Pointer to the dense storage for the index values of the sparse vector y.  The
 corresponding entry in y holds the values of the vector.  Contains nz values.
 
 Indices are always assumed to be stored in ascending order. Additionally,
 indices are assumed to be unique.  Undefined behavior if either of these
 assumptions are not met.
 
 All indices are 0 based (the first element of a pointer is ptr[0]).
 
 @param C
 Pointer to an uninitialized sparse matrix object.  On success a newly allocated
 sparse matrix object is returned in this pointer.  On error, this set to NULL.
 Caller is responsible for calling sparse_matrix_destroy on this matrix object.
 
 @result
 On success SPARSE_SUCCESS is returned an C is valid matrix object.  The caller is 
 responsible for cleaning up the sparse matrix object with sparse_matrix_destroy.
 Will return SPARSE_ILLEGAL_PARAMETER if nz > N, and C will be unchanged.
 
 @discussion
 Compute the outer product of the dense vector x and the sparse vector y and
 return a new sparse matrix in the uninitialized pointer sparse matrix pointer 
 C.  C = alpha * x * y'.  Caller responsible for calling sparse_matrix_destroy on 
 the returned matrix.
 
 The matrix object returned on success is a point wise based sparse matrix.
 
 */
sparse_status sparse_outer_product_dense_float( sparse_dimension M, sparse_dimension N,
                                    sparse_dimension nz, float alpha,
                                    const float * __restrict x, sparse_stride incx,
                                    const float * __restrict y,
                                    const sparse_index * __restrict indy,
                                    sparse_matrix_float * __restrict C);
sparse_status sparse_outer_product_dense_double( sparse_dimension M, sparse_dimension N,
                                     sparse_dimension nz, double alpha,
                                     const double * __restrict x,
                                     sparse_stride incx, const double * __restrict y,
                                     const sparse_index * __restrict indy,
                                     sparse_matrix_double * __restrict C);

/*!
 @abstract
 Permute the rows of the sparse matrix A based on the provided permutation
 array.
 
 @param A
 The sparse matrix.
 
 @param perm
 The permutation array.  Holds number of rows in A values indicating the
 permutation of the matrix.  The indices in perm are expected to be 0 based 
 (first element of pointer is ptr[0]).  The indices in perm are expected to
 be within bounds of the matrix.  Undefined behavior if not met.
 
 @result
 On successful return, A has been permuted and SPARSE_SUCCESS is returned.
 
 @discussion
 Permute the rows of the sparse matrix A based on the provided permutation
 array.  For each row in A, swap rows as:
 
 tmp[:] = A[i,:];
 A[i,:] = A[perm[i],:];
 A[perm[i],:] = tmp[:];
 
 */
sparse_status sparse_permute_rows_float( sparse_matrix_float A,
                             const sparse_index * __restrict perm );
sparse_status sparse_permute_rows_double( sparse_matrix_double A,
                              const sparse_index * __restrict perm );

/*!
 @abstract
 Permute the columns of the sparse matrix A based on the provided permutation
 array.
 
 @param A
 The sparse matrix.
 
 @param perm
 The permutation array.  Holds number of columns in A values indicating the
 permutation of the matrix.  The indices in perm are expected to be 0 based
 (first element of pointer is ptr[0]).  The indices in perm are expected to
 be within bounds of the matrix.  Undefined behavior if not met.
 
 @result
 On successful return, A has been permuted and SPARSE_SUCCESS is returned.
 
 @discussion
 Permute the columns of the sparse matrix A based on the provided permutation
 array.  For each column in A, swap columns as:
 
 tmp[:] = A[:,j];
 A[:,j] = A[:,perm[j]];
 A[:,perm[j]] = tmp[:];
 
 */
sparse_status sparse_permute_cols_float( sparse_matrix_float A,
                             const sparse_index * __restrict perm );
sparse_status sparse_permute_cols_double( sparse_matrix_double A,
                              const sparse_index * __restrict perm );


/*!
 @abstract
 Compute the specified elementwise norm of the sparse matrix A.  This is the 
 norm of the matrix treated as a vector, not the operator norm.
 
 @param A
 The sparse matrix.
 
 @param norm
 Specify the norm to be computed.  Must be one of SPARSE_NORM_ONE, SPARSE_NORM_TWO,
 SPARSE_NORM_INF, or SPARSE_NORM_R1.  See discussion for further details.
 
 @result
 Upon success, resulting norm is returned.
 
 @discussion
 Compute the specified norm of the sparse matrix A.  This is the norm of the
 matrix treated as a vector, not the operator norm.  Specify one of:
 1) SPARSE_NORM_ONE : sum over i,j ( | A[i,j] | )
 2) SPARSE_NORM_TWO : sqrt( sum over i,j (A[i,j])^2 )
 3) SPARSE_NORM_INF : max over i,j ( | A[i,j] | )
 4) SPARSE_NORM_R1  : sum over j ( sqrt ( sum over i ( A[i,j]^2 ) ) )
 
 If norm is not one of the enumerated norm types, the default value is
 SPARSE_NORM_INF.
 
 */
float sparse_elementwise_norm_float( sparse_matrix_float A, sparse_norm norm );
double sparse_elementwise_norm_double( sparse_matrix_double A, sparse_norm norm );

/*!
 @abstract
 Compute the specified operator norm of the sparse matrix A.  For elementwise
 norm use elementwise_norm routines.
 
 @param A
 The sparse matrix.
 
 @param norm
 Specify the norm to be computed.  Must be one of SPARSE_NORM_ONE, SPARSE_NORM_TWO,
 or SPARSE_NORM_INF.  See discussion for further details.
 
 @result
 Upon success, resulting norm is returned.
 
 @discussion
 Compute the specified norm of the sparse matrix A.  This is the norm of the
 matrix treated as an linear operator, not the elementwise norm.  Specify one of:
 1) SPARSE_NORM_ONE : max over j ( sum over i ( | A[i,j] | ) )
 2) SPARSE_NORM_TWO : Maximum singular value. This is significantly more
                      expensive to compute than the other norms.
 3) SPARSE_NORM_INF : max over i ( sum over j ( | A[i,j] | ) )
 4) SPARSE_NORM_R1  : Not supported, undefined.
 
 If norm is not one of the enumerated norm types, the default value is
 SPARSE_NORM_INF.
 
 */
float sparse_operator_norm_float( sparse_matrix_float A, sparse_norm norm );
double sparse_operator_norm_double( sparse_matrix_double A, sparse_norm norm );
    
/*!
 @abstract
 Compute the sum along the specified diagonal of the sparse matrix A.
 
 @param A
 The sparse matrix.
 
 @param offset
 Specifies the diagonal to sum.  A zero value will sum the main diagonal
 (A[i,i]), a value greater than zero will sum diagonals above the main diagonal
 (A[i,i+offset]), and a values less than zero will sum diagonals below the main
 diagonal (A[i-offset,i]).  If offset is out of the bounds of the matrix A, 0 
 is returned.
 
 @result
 On success, the resulting trace is returned.
 
 @discussion
 Compute the sum along the specified diagonal of the sparse matrix A.  The
 diagonal is specified by the parameter offset where zero is the main diagonal,
 values greater than one refer to diagonals above the main diagonal
 (A[i,i+offset]), and values less than one refer to diagonals below the main
 diagonal (A[i-offset, i]).

 If offset is out of the bounds of the matrix A, 0 is returned.
 
 */
float sparse_matrix_trace_float( sparse_matrix_float A, sparse_index offset );
double sparse_matrix_trace_double( sparse_matrix_double A, sparse_index offset );





#pragma mark - Level 3 Routines -

               /* Level 3 Computational Routines */
/*!
 @functiongroup Level 3
 @abstract Level 3 routines consisting of matrix-matrix operations
 */
/*!
 @abstract
 Multiplies the dense matrix B by the sparse matrix A and adds the result to
 the dense matrix C.
 
 C = alpha * op(A) * B + C; where op(A) is either A or the transpose of A
 
 @param order
 Specified the storage order for the dense matrices B and C. Must be one of
 CblasRowMajor or CblasColMajor.
 
 @param transa
 Specifies whether to perform the operation with A or the transpose of A.
 Must be one of CblasNoTrans or CblasTrans.
 
 @param n
 The number of columns of the matrices B and C.
 
 @param alpha
 Scalar multiplier of A.
 
 @param A
 The sparse matrix.
 
 @param B
 Pointer to the dense matrix B. The number of rows must be equal to the number
 of columns of A and the number of columns is n.  Behavior undefined if this 
 is not met. The argument ldb describes how many elements to move between one
 row (row major) or column (column major).
 
 @param ldb
 Increment in elements between rows (row major) or columns (column major) of B. 
 Must be greater than or equal to n when row major, or number of columns of 
 A when column major.
 
 @param C
 Pointer to the dense matrix C. The number of rows must be equal to the number
 of rows of A and the number of columns is n.  Behavior undefined if this
 is not met. The argument ldc describes how many elements to move between one
 row (row major) or column (column major).  C is updated with the result of the
 operation.
 
 @param ldc
 Increment in elements between rows (row major) or columns (column major) of C.
 Must be greater than or equal to n when row major, or number of rows of
 A when column major.
 
 @result
 On success, SPARSE_SUCCESS is returned and C has been updated with result of the 
 operation.  Will return SPARSE_ILLEGAL_PARAMETER if order or transa is not valid 
 or the leading dimension parameters do not meet their dimension requirements.  
 On error, C is unchanged.
 
 @discussion
 Multiplies the dense matrix B by the sparse matrix A and adds the result to
 the dense matrix C (C = alpha * op(A) * B + C, where op(A) is either A
 or the transpose of A). If A is of size M x N, then B is of size N x n and C is 
 of size M x n.
 
 If the desired operation is C = A * B, then an efficient option is to create
 the C buffer of zeros as C = calloc(sizeof(..)*rows*cols) and then perform
 the operation with the zero filled C.
 */
sparse_status sparse_matrix_product_dense_float( enum CBLAS_ORDER order,
                                           enum CBLAS_TRANSPOSE transa,
                                           sparse_dimension n, float alpha,
                                           sparse_matrix_float A,
                                           const float * __restrict B,
                                           sparse_dimension ldb,
                                           float * __restrict C,
                                           sparse_dimension ldc );
sparse_status sparse_matrix_product_dense_double( enum CBLAS_ORDER order,
                                            enum CBLAS_TRANSPOSE transa,
                                            sparse_dimension n, double alpha,
                                            sparse_matrix_double A,
                                            const double * __restrict B,
                                            sparse_dimension ldb,
                                            double * __restrict C,
                                            sparse_dimension ldc );

/*!
 @abstract
 Solve the system of equations B = alpha * T^{-1} * B for B where B is a dense
 matrix and T is a triangular sparse matrix.
 
 @param order
 Specified the storage order for the dense matrix B. Must be one of
 CblasRowMajor or CblasColMajor.
 
 @param transt
 Specifies whether to perform the operation with T or the transpose of T.
 Must be one of CblasNoTrans or CblasTrans.
 
 @param nrhs
 The number of columns of the matrix B.
 
 @param alpha
 Scalar multiplier of T.
 
 @param T
 The sparse triangular matrix.  Must be upper or lower triangular matrix.
 Will return SPARSE_ILLEGAL_PARAMETER if not a triangular matrix.
 
 @param B
 Pointer to the dense matrix B. The number of rows must be equal to the number
 of columns of T and the number of columns is nrhs.  Behavior undefined if this
 is not met. The argument ldb describes how many elements to move between one
 row (row major) or column (column major). On exit holds the solution to the
 system of equations.
 
 @param ldb
 Increment in elements between rows (row major) or columns (column major) of B.
 Must be greater than or equal to nrhs when row major, or number of columns of
 A when column major.
 
 @result
 On success, SPARSE_SUCCESS is returned and B has been updated with result of the
 operation.  Will return SPARSE_ILLEGAL_PARAMETER if either of order or trant are
 invalid or the ldb does not meet its dimension requirements.  On error
 B is unchanged.
 
 @discussion
 Solve the system of equations B = alpha * T^{-1} * B for B where B is a dense
 vector and T is a triangular sparse matrix.  If T is of size N x N, then B must
 be of size N x nrhs.  The matrix T must be an upper or lower triangular matrix.
 
 */
sparse_status sparse_matrix_triangular_solve_dense_float( enum CBLAS_ORDER order,
                                   enum CBLAS_TRANSPOSE transt,
                                   sparse_dimension nrhs, float alpha,
                                   sparse_matrix_float T,
                                   float * __restrict B, sparse_dimension ldb );
sparse_status sparse_matrix_triangular_solve_dense_double( enum CBLAS_ORDER order,
                                    enum CBLAS_TRANSPOSE transt,
                                    sparse_dimension nrhs, double alpha,
                                    sparse_matrix_double T,
                                    double * __restrict B, sparse_dimension ldb );




#pragma mark - Point Wise Sparse Matrix Routines -

               /* Point Wise Matrix Routines */
/*!
 @functiongroup Point Wise Matrix Routines
 @abstract Routines to create and insert values in a point wise sparse matrix.
 */

/*!
 @abstract
 Create a sparse matrix object that is stored in point wise format and is ready
 to receive values from the various insert routines.
 
 @param M
 The number of rows of the matrix.  Must be greater than 0.
 
 @param N
 The number of columns of the matrix.  Must be greater than 0.
 
 @result
 On success, returns a matrix object that is ready for receiving entries.  If an
 error occurs, NULL is returned.
 
 @discussion
 Create a sparse matrix object that is stored in point wise format and is ready
 to receive values from the various insert routines.  Point wise format means
 individual values are stored for a given i,j location as opposed to blocks of
 values.  For block support use the block_create routines.  See the various
 insert routines for details on inserting entries into this matrix object.
 
 The dimensions M and N must be greater than 0.  On success a valid matrix
 object is returned, otherwise NULL is returned.
 
 */
sparse_matrix_float sparse_matrix_create_float( sparse_dimension M, sparse_dimension N );
sparse_matrix_double sparse_matrix_create_double( sparse_dimension M, sparse_dimension N );

/*!
 @abstract
 Use to build a sparse matrix by inserting one scalar entry at a time.  Update
 A[i,j] = val.  A must have been created with one of sparse_matrix_create_float or
 sparse_matrix_create_double.

 @param A
 The sparse matrix.  A must have been created with one of sparse_matrix_create_float
 or sparse_matrix_create_double.  SPARSE_ILLEGAL_PARAMETER is returned if not met.
 
 @param val
 The scalar value to insert into the sparse matrix.
 
 @param i
 The row location to insert the value.  Indices are 0 based (first element of 
 pointer is ptr[0]).  Indices expected to be in the bounds of matrix dimensions,
 undefined behavior if not met.
 
 @param j
 The column location to insert the value.  Indices are 0 based (first element of
 pointer is ptr[0]).  Indices expected to be in the bounds of matrix dimensions,
 undefined behavior if not met.
 
 @result
 On successful insertion, A has been updated with the value and SPARSE_SUCCESS is
 returned.  If A creation requirements are not met, SPARSE_ILLEGAL_PARAMETER is
 returned and A is unchanged.
 
 @discussion
 Use to build a sparse matrix by inserting one scalar entry at a time.  Update
 A[i,j] = val.
 
 A must have been created with one of sparse_matrix_create_float or
 sparse_matrix_create_double.
 
 Note that matrix properties cannot be modified after value insertion begins.
 This includes properties such as specifying a triangular matrix.
 
 Insertion can be expensive, generally speaking it is best to do a batch update.
 Inserted values may be temporarily held internally within the object and only
 inserted into the sparse format when a later computation triggers a need to
 insert.
 
 */
sparse_status sparse_insert_entry_float( sparse_matrix_float A, float val,
                                   sparse_index i, sparse_index j );
sparse_status sparse_insert_entry_double( sparse_matrix_double A, double val,
                                    sparse_index i, sparse_index j );

/*!
 @abstract
 Use to build a sparse matrix by providing a list of point entries.  For each
 entry provided, update A[indx[i],jndx[i]] = val[i].  A must have been created
 with one of sparse_matrix_create_float or sparse_matrix_create_double.
 
 @param A
 The sparse matrix.  A must have been created with one of sparse_matrix_create_float
 or sparse_matrix_create_double.  SPARSE_ILLEGAL_PARAMETER is returned if not met.
 
 @param N
 The number of values to insert into A.  Each of indx, jndx and val are of size
 N.
 
 @param val
 Pointer to list of scalar values to insert into the sparse matrix.  The value
 is inserted into the location specified by the corresponding indices in indx
 and jndx.  Must hold N values.
 
 @param indx
 An array of row indices that correspond to the values in val. Must hold N
 values.
 
 Indices are assumed to be unique.  Additionally, indices are assumed to be in the
 bounds of the matrix.  Undefined behavior if any of these assumptions are not 
 met.
 
 All indices are 0 based (the first element of a pointer is ptr[0]).
 
 @param jndx
 An array of column indices that correspond to the values in val. Must hold N
 values.
 
 Indices are assumed to be unique.  Additionally, indices are assumed to be in the
 bounds of the matrix.  Undefined behavior if any of these assumptions are not
 met.
 
 All indices are 0 based (the first element of a pointer is ptr[0]).
 
 @result
 On successful insertion, A has been updated with the values and SPARSE_SUCCESS is
 returned.  If A creation requirements are not met, SPARSE_ILLEGAL_PARAMETER is
 returned and A is unchanged.
 
 @discussion
 Use to build a sparse matrix by providing a list of point entries.  For each
 entry provided, update A[indx[i],jndx[i]] = val[i].
 
 A must have been created with one of sparse_matrix_create_float or
 sparse_matrix_create_double.
 
 Note that matrix properties cannot be modified after value insertion begins.
 This includes properties such as specifying a triangular matrix.
 
 Insertion can be expensive, generally speaking it is best to do a batch update.
 Inserted values may be temporarily held internally within the object and only
 inserted into the sparse format when a later computation triggers a need to
 insert.
 
 */
sparse_status sparse_insert_entries_float( sparse_matrix_float A, sparse_dimension N,
                                     const float * __restrict val,
                                     const sparse_index * __restrict indx,
                                     const sparse_index * __restrict jndx );
sparse_status sparse_insert_entries_double( sparse_matrix_double A, sparse_dimension N,
                                      const double * __restrict val,
                                      const sparse_index * __restrict indx,
                                      const sparse_index * __restrict jndx );

/*!
 @abstract
 Use to build a sparse matrix by providing a list of point entries for a single
 column.  For each entry provided, update A[indx[i],j] = val[i].  A must have
 been created with one of sparse_matrix_create_float or sparse_matrix_create_double.
 
 @param A
 The sparse matrix.  A must have been created with one of sparse_matrix_create_float
 or sparse_matrix_create_double.  SPARSE_ILLEGAL_PARAMETER is returned if not met.
 
 @param j
 The column for value insertion.  Indices are 0 based (first element of pointer
 is ptr[0]).  Indices expected to be in the bounds of matrix dimensions,
 undefined behavior if not met.
 
 @param nz
 The number of values to insert into A.  Each of indx and val are of size
 nz.
 
 @param val
 Pointer to list of scalar values to insert into the sparse matrix.  The value
 is inserted into the location specified by the corresponding indices of indx
 and j.  Must hold nz values.
 
 @param indx
 An array of column indices that correspond to the values in val. Must hold nz
 values.
 
 Indices are always assumed to be stored in ascending order. Additionally,
 indices are assumed to be unique.  Finally, indices are assumed to be in the
 bounds of the matrix.  Undefined behavior if any of these assumptions are not
 met.
 
 All indices are 0 based (the first element of a pointer is ptr[0]).
 
 @result
 On successful insertion, A has been updated with the value and SPARSE_SUCCESS is
 returned.  If A creation requirements are not met, SPARSE_ILLEGAL_PARAMETER is
 returned and A is unchanged.
 
 @discussion
 Use to build a sparse matrix by providing a list of point entries for a single
 column.  For each entry provided, update A[indx[i],j] = val[i].  This will not
 replace the existing contents of the column, it appends new values and
 overwrites overlapping values.
 
 A must have been created with one of sparse_matrix_create_float or
 sparse_matrix_create_double.
 
 Note that matrix properties cannot be modified after value insertion begins.
 This includes properties such as specifying a triangular matrix.
 
 Insertion can be expensive, generally speaking it is best to do a batch update.
 Inserted values may be temporarily held internally within the object and only
 inserted into the sparse format when a later computation triggers a need to
 insert.
 
 */
sparse_status sparse_insert_col_float( sparse_matrix_float A, sparse_index j,
                                 sparse_dimension nz, const float * __restrict val,
                                 const sparse_index * __restrict indx );
sparse_status sparse_insert_col_double( sparse_matrix_double A, sparse_index j,
                                  sparse_dimension nz, const double * __restrict val,
                                  const sparse_index * __restrict indx );

/*!
 @abstract
 Use to build a sparse matrix by providing a list of point entries for a single
 row.  For each entry provided, update A[i,jndx[i]] = val[i].  A must have been
 created with one of sparse_matrix_create_float or sparse_matrix_create_double.
 
 @param A
 The sparse matrix.  A must have been created with one of sparse_matrix_create_float
 or sparse_matrix_create_double.  SPARSE_ILLEGAL_PARAMETER is returned if not met.
 
 @param i
 The row for value insertion.  Indices are 0 based (first element of pointer is
 ptr[0]).  Indices expected to be in the bounds of matrix dimensions,
 undefined behavior if not met.
 
 @param nz
 The number of values to insert into A.  Each of jndx and val are of size
 nz.
 
 @param val
 Pointer to list of scalar values to insert into the sparse matrix.  The value
 is inserted into the location specified by the corresponding indices of i and
 jndx.  Must hold nz values.
 
 @param jndx
 An array of column indices that correspond to the values in val. Must hold nz
 values.
 
 Indices are always assumed to be stored in ascending order. Additionally,
 indices are assumed to be unique.  Finally, indices are assumed to be in the
 bounds of the matrix.  Undefined behavior if any of these assumptions are not
 met.
 
 All indices are 0 based (the first element of a pointer is ptr[0]).
 
 @result
 On successful insertion, A has been updated with the value and SPARSE_SUCCESS is
 returned.  If A creation requirements are not met, SPARSE_ILLEGAL_PARAMETER is
 returned and A is unchanged.
 
 @discussion
 Use to build a sparse matrix by providing a list of point entries for a single
 row.  For each entry provided, update A[i,jndx[i]] = val[i].  This will not
 replace the existing contents of the row, it appends new values and
 overwrites overlapping values.
 
 A must have been created with one of sparse_matrix_create_float or
 sparse_matrix_create_double.
 
 Note that matrix properties cannot be modified after value insertion begins.
 This includes properties such as specifying a triangular matrix.
 
 Insertion can be expensive, generally speaking it is best to do a batch update.
 Inserted values may be temporarily held internally within the object and only
 inserted into the sparse format when a later computation triggers a need to
 insert.
 
 */
sparse_status sparse_insert_row_float( sparse_matrix_float A, sparse_index i,
                                 sparse_dimension nz, const float * __restrict val,
                                 const sparse_index * __restrict jndx );
sparse_status sparse_insert_row_double( sparse_matrix_double A, sparse_index i,
                                  sparse_dimension nz, const double * __restrict val,
                                  const sparse_index * __restrict jndx );


/*!
 @abstract
 Extract the first nz values of the row begining at A[row,column_start] for the
 sparse matrix A.  A must have been created with one of sparse_matrix_create_float 
 or sparse_matrix_create_double.
 
 @param A
 The sparse matrix.  A must have been created with one of 
 sparse_matrix_create_float or sparse_matrix_create_double.  SPARSE_ILLEGAL_PARAMETER is 
 returned if not met.
 
 @param row
 The row for value extraction.  Indices are 0 based (first element of pointer is
 ptr[0]).  Indices expected to be in the bounds of matrix dimensions,
 undefined behavior if not met.
 
 @param column_start
 The index of the column to start extraction.  Indices are 0 based (first 
 element of pointer is ptr[0]).  Indices expected to be in the bounds of matrix 
 dimensions, undefined behavior if not met.
 
 @param column_end
 On return, holds the column index of the next nonzero value.  If there is no
 next nonzero value (because all of them have been copied into the sparse
 vector), it holds the number of columns in the matrix.
 Indices are 0 based (first element of pointer is ptr[0]).
 Indices expected to be in the bounds of matrix dimensions, undefined behavior 
 if not met.
 
 @param nz
 The number of values to extract from A.  Each of jndx and val are of size
 nz.
 
 @param val
 Pointer to array to hold the values extracted from the sparse matrix.  The
 value is extracted from the location specified by the corresponding indices of 
 row and jndx.  Must be of size nz elements.  If less than nz nonzero values are
 found, then the last nz - actual_nonzero_count elements of val are untouched.
 
 @param jndx
 An array to hold the extracted column indices that correspond to the values in 
 val. Note that these indices are relative to the matrix row and not the
 starting column index specified by column_start.  Returned indices are 0 based 
 (first element of pointer is ptr[0]).  Must be of size nz elements.
 
 @result
 On success val and jndx have been updated with the nonzero values of the row'th
 row, column_end holds the column index of the next nonzero value, and
 the number of nonzero values written are returned.  If A creation requirements 
 are not met, SPARSE_ILLEGAL_PARAMETER is returned and val and jndx are unchanged.
 
 @discussion
 Extract the first nz values of the row begining at A[row,column_start] for the
 sparse matrix A.  The number of nonzero values extracted is limited by nz, and
 the number of nonzero's written to jndx and val are returned.  Additionally, 
 the column index of the next nonzero value is returned in column_end.
 For example if nz is returned, not all nonzero values have been extracted,
 and a second extract can start from column_end.
 
 A must have been created with one of sparse_matrix_create_float or
 sparse_matrix_create_double.
 
 */
sparse_status sparse_extract_sparse_row_float( sparse_matrix_float A, sparse_index row,
                                  sparse_index column_start, sparse_index *column_end,
                                  sparse_dimension nz, float * __restrict val,
                                  sparse_index * __restrict jndx );
sparse_status sparse_extract_sparse_row_double( sparse_matrix_double A, sparse_index row,
                                  sparse_index column_start, sparse_index *column_end,
                                  sparse_dimension nz, double * __restrict val,
                                  sparse_index * __restrict jndx );

/*!
 @abstract
 Extract the first nz values of the column begining at A[row_start,column] for 
 the sparse matrix A.  A must have been created with one of 
 sparse_matrix_create_float or sparse_matrix_create_double.
 
 @param A
 The sparse matrix.  A must have been created with one of 
 sparse_matrix_create_float or sparse_matrix_create_double.  SPARSE_ILLEGAL_PARAMETER is 
 returned if not met.
 
 @param column
 The column for value extraction.  Indices are 0 based (first element of pointer 
 is ptr[0]).  Indices expected to be in the bounds of matrix dimensions,
 undefined behavior if not met.
 
 @param row_start
 The index of the row to start extraction.  Indices are 0 based (first
 element of pointer is ptr[0]).  Indices expected to be in the bounds of matrix 
 dimensions, undefined behavior if not met.
 
 @param row_end
 On return, holds the row index of the next nonzero value.  If there is no
 next nonzero value (because all of them have been copied into the sparse
 vector), it holds the number of rows in the matrix.
 Indices are 0 based (first element of pointer is ptr[0]).
 Indices expected to be in the bounds of matrix dimensions, undefined behavior 
 if not met.
 
 @param nz
 The number of values to extract from A.  Each of indx and val are of size
 nz.
 
 @param val
 Pointer to array to hold the values extracted from the sparse matrix.  The
 value is extracted from the location specified by the corresponding indices of 
 column and indx.  Must be of size nz elements.  If less than nz nonzero values 
 are found, then the last nz - actual_nonzero_count elements of val are 
 untouched.
 
 @param indx
 An array to hold the extracted row indices that correspond to the values in
 val. Note that these indices are relative to the matrix column and not the
 starting row index specified by row_start.  Returned indices are 0 based
 (first element of pointer is ptr[0]).  Must be of size nz elements.
 
 @result
 On success val and indx have been updated with the nonzero values of the 
 column'th column, row_end holds the row index of the next nonzero value,
 and the number of nonzero values written are returned.  If A creation
 requirements are not met, SPARSE_ILLEGAL_PARAMETER is returned and val and indx 
 are unchanged.
 
 @discussion
 Extract the first nz values of the column begining at A[column,row_start] for 
 the sparse matrix A.  The number of nonzero values extracted is limited by nz, 
 and the number of nonzero's written to indx and val are returned.  
 Additionally, the row index of the next nonzero value is returned in
 row_end.  For example if nz is returned, not all nonzero values have been
 extracted, and a second extract can start from row_end.
 
 A must have been created with one of sparse_matrix_create_float or
 sparse_matrix_create_double.
 
 */
sparse_status sparse_extract_sparse_column_float( sparse_matrix_float A,
                                            sparse_index column,
                                            sparse_index row_start,
                                            sparse_index *row_end,
                                            sparse_dimension nz,
                                            float * __restrict val,
                                            sparse_index * __restrict indx );
sparse_status sparse_extract_sparse_column_double( sparse_matrix_double A,
                                             sparse_index column,
                                             sparse_index row_start,
                                             sparse_index *row_end,
                                             sparse_dimension nz,
                                             double * __restrict val,
                                             sparse_index * __restrict indx );



#pragma mark - Block Wise Matrix Routines -

				/* Block Wise Matrix Routines */
/*!
 @functiongroup Block Wise Matrix Routines
 @abstract Routines to create and insert values in a block wise sparse matrix.
 */

 /*!
 @abstract
 Create a sparse matrix object that is stored in block-entry format and is ready
 to receive values from the various block insert routines.  Blocks are of fixed
 dimension k x l.
 
 @param Mb
 The number of rows in terms of blocks of the matrix.  There are a total of
 Mb * k rows in the matrix.  Must be greater than 0.
 
 @param Nb
 The number of columns in terms of blocks of the matrix.  There are a total of
 Nb * l columns in the matrix.  Must be greater than 0.
 
 @param k
 The row dimension of a block in the sparse matrix.  Must be greater than 0.
 
 @param l
 The column dimension of a block in the sparse matrix.  Must be greater than 0.
 
 @result
 On success, returns a matrix object that is ready for receiving entries.  If an
 error occurs, NULL is returned.
 
 @discussion
 Create a sparse matrix object that is stored in block-entry format and is ready
 to receive values from the various block insert routines.  Blocks are are of
 fixed dimensions k x l.  Block-entry format means blocks of dense regions will 
 be stored at block indices i,j.  For point wise format use non block version of
 create. See the various insert routines for details on inserting values into
 this matrix object.
 
 The dimensions Mb, Nb, k, and l must be greater than 0.  On success a valid 
 matrix object is returned, otherwise NULL is returned.
  
 */
sparse_matrix_float sparse_matrix_block_create_float( sparse_dimension Mb,
                                                sparse_dimension Nb,
                                                sparse_dimension k,
                                                sparse_dimension l );
sparse_matrix_double sparse_matrix_block_create_double( sparse_dimension Mb,
                                                  sparse_dimension Nb,
                                                  sparse_dimension k,
                                                  sparse_dimension l );

/*!
 @abstract
 Create a sparse matrix object that is stored in block-entry format and is ready
 to receive values from the various block insert routines.  Blocks are of 
 variable dimensions where the i,j'th block has dimensions K[i] x L[j].
 
 @param Mb
 The number of rows in terms of blocks of the matrix.  Must be greater than 0.
 
 @param Nb
 The number of columns in terms of blocks of the matrix.  Must be greater 
 than 0.
 
 @param K
 Array containing row dimensions of the blocks.  The i'th row in terms of blocks
 will have a dimension K[i].  K is expected to hold Mb elements.  All values of
 K are expected to be greater than 0.
 
 @param L
 Array containing column dimensions of the blocks.  The j'th column in terms of 
 blocks will have a dimension L[j].  L is expected to hold Nb elements.  All 
 values of L are expected to be greater than 0.
 
 @result
 On success, returns a matrix object that is ready for receiving entries.  If an
 error occurs, NULL is returned.
 
 @discussion
 Create a sparse matrix object that is stored in block-entry format and is ready
 to receive values from the various block insert routines.  Blocks are are of
 variable dimension where the i,j'th block index has a dimension K[i] x L[j].  
 Block-entry format means blocks of dense regions will be stored at block 
 indices i,j.  For point wise format use non block version of create. See the 
 various insert routines for details on inserting values into this matrix
 object.
 
 The dimensions Mb, Nb and all values in K and L must be greater than 0.  On 
 success a valid matrix object is returned, otherwise NULL is returned.
 
 */
sparse_matrix_float sparse_matrix_variable_block_create_float( sparse_dimension Mb,
                                                         sparse_dimension Nb,
                                                         const sparse_dimension *K,
                                                         const sparse_dimension *L );
sparse_matrix_double sparse_matrix_variable_block_create_double( sparse_dimension Mb,
                                                           sparse_dimension Nb,
                                                           const sparse_dimension *K,
                                                           const sparse_dimension *L );
/*!
 @abstract
 Use to build a sparse matrix by providing a dense block for entry at block
 location A[bi,bj].  Block size is determined at object creation time.  A must
 have been created with one of sparse_matrix_block_create_float,
 sparse_matrix_block_create_double, sparse_matrix_variable_block_create_float, or
 sparse_matrix_variable_block_create_double.
 
 @param A
 The sparse matrix.  A must have been created with one of 
 sparse_matrix_block_create_float, sparse_matrix_block_create_double, 
 sparse_matrix_variable_block_create_float, or 
 sparse_matrix_variable_block_create_double.  SPARSE_ILLEGAL_PARAMETER is returned if 
 not met.  A holds block dimensions (fixed or variable) set with matrix object 
 creation routine.
 
 @param val
 Pointer to block to be inserted at block index location A[bi,bj].  The block is
 of dimension k x l where k and l are set for bi,bj at object creation time.  
 The strides between elements for rows and columns are provided in row_stride 
 and col_stride.
 
 @param row_stride
 The row stride in number of elements to move from one row to the next for the
 block val.
 
 @param col_stride
 The column stride in number of elements to move from one column to the next for
 the block val.
 
 @param bi
 The block row index where val is to be inserted.  Indexing is zero based, the
 first block is located at 0,0.  Index is assumed to be within the bounds of the
 matrix object, undefined behavior if not met.
 
 @param bj
 The block column index where val is to be inserted.  Indexing is zero based, the
 first block is located at 0,0.  Index is assumed to be within the bounds of the
 matrix object, undefined behavior if not met.
 
 @result
 On successful insertion, A has been updated with the value and SPARSE_SUCCESS is
 returned.  If A creation requirements are not met, SPARSE_ILLEGAL_PARAMETER is
 returned and A is unchanged.
 
 @discussion
 Use to build a sparse matrix by providing a dense block for entry at block
 location A[bi,bj].  Block size is determined at object creation time.  Given a
 block dimension of k x l and for location bi,bj, update as:
 A[bi,bj][i,j] = val[i*row_stride + j*col_stride] for each i in k and each j in
 l.  
 
 A must have been created with one of sparse_matrix_block_create_float,
 sparse_matrix_block_create_double, sparse_matrix_variable_block_create_float, or
 sparse_matrix_variable_block_create_double.
 
 Note that matrix properties cannot be modified after value insertion begins.
 This includes properties such as specifying a triangular matrix.
 
 Insertion can be expensive, generally speaking it is best to do a batch update.
 Inserted values may be temporarily held internally within the object and only
 inserted into the sparse format when a later computation triggers a need to
 insert.
 
 */
sparse_status sparse_insert_block_float( sparse_matrix_float A,
                                   const float * __restrict val,
                                   sparse_dimension row_stride,
                                   sparse_dimension col_stride,
                                   sparse_index bi, sparse_index bj );
sparse_status sparse_insert_block_double( sparse_matrix_double A,
                                    const double * __restrict val,
                                    sparse_dimension row_stride,
                                    sparse_dimension col_stride,
                                    sparse_index bi, sparse_index bj );


/*!
 @abstract
 Extract the bi,bj'th block from the sparse matrix A.  A must have been created
 with one of sparse_matrix_block_create_float, sparse_matrix_block_create_double, 
 sparse_matrix_variable_block_create_float, or 
 sparse_matrix_variable_block_create_double.
 
 @param A
 The sparse matrix.  A must have been created with one of
 sparse_matrix_block_create_float, sparse_matrix_block_create_double,
 sparse_matrix_variable_block_create_float, or
 sparse_matrix_variable_block_create_double.  SPARSE_ILLEGAL_PARAMETER is returned if
 not met.  A holds block dimensions (fixed or variable) set with matrix object
 creation routine.
 
 @param bi
 The block row index for value extraction.  Indices are 0 based (first block of 
 matrix is A[0,0]).  Indices expected to be in the bounds of matrix dimensions,
 undefined behavior if not met.
 
 @param bj
 The block column index for value extraction.  Indices are 0 based (first block 
 of matrix is A[0,0]).  Indices expected to be in the bounds of matrix 
 dimensions, undefined behavior if not met.
 
 @param row_stride
 The row stride in number of elements to move from one row to the next for the
 block val.
 
 @param col_stride
 The column stride in number of elements to move from one column to the next for
 the block val.
 
 @param val
 Pointer to dense block to place the extracted values.  Expected to be of size
 K x L where K x L is the block size for the matrix object at block index bi,bj.
 This dimensions is set at matrix object creation time.
 
 @result
 On success SPARSE_SUCCESS is return and val has been updated with the block from
 block index bi,bj. If A creation requirements are not met, 
 SPARSE_ILLEGAL_PARAMETER is returned and val is unchanged.
 
 @discussion
 Extract the bi,bj'th block from the sparse matrix A.  
 
 A must have been created with one of sparse_matrix_block_create_float, 
 sparse_matrix_block_create_double, sparse_matrix_variable_block_create_float, or
 sparse_matrix_variable_block_create_double.
 
 */
sparse_status sparse_extract_block_float( sparse_matrix_float A, sparse_index bi,
                                    sparse_index bj, sparse_dimension row_stride,
                                    sparse_dimension col_stride,
                                    float * __restrict val );
sparse_status sparse_extract_block_double( sparse_matrix_double A, sparse_index bi,
                                     sparse_index bj, sparse_dimension row_stride,
                                     sparse_dimension col_stride,
                                     double * __restrict val );

/*!
 @abstract
 Return the dimension of the block for the i'th row of a sparse block matrix. 
 Returns 0 if the matrix was not created with a block create routine.
 */
long sparse_get_block_dimension_for_row( void *A, sparse_index i );

/*!
 @abstract
 Return the dimension of the block for the j'th column of a sparse block matrix.
 Returns 0 if the matrix was not created with a block create routine.
 */
long sparse_get_block_dimension_for_col( void *A, sparse_index j );



#pragma mark - General Sparse Matrix Management Routines -

			/* General Sparse Matrix Management Routines */
/*!
 @functiongroup General Sparse Matrix Management Routines
 @abstract Routines to manage and work with sparse matrix properties.
 */

/*!
 @abstract
 Force any recently added values to the matrix to be put into the internal
 sparse storage format.
 
 @param A
 The sparse matrix, which has had values recently inserted into the object.
 
 @result
 On success, A has all values inserted into the internal sparse representation.
 
 @discussion
 Force any recently added values to the matrix to be put into the internal
 sparse storage format.  Values inserted into a matrix object will may not go 
 directly into the sparse representation until needed, for example when a 
 computation occurs.  In some cases is may be beneficial to the caller to know 
 when the cost of the update will occur.  This routine allows the caller to 
 trigger adding values to the internal sparse format.
 
 Adding values to the sparse format can be costly, and batch updates to the 
 matrices are recommended.  Similarly, use of this routine may be expensive, so
 it is best to insert all values of a batch and call this routine once.
 
 */
sparse_status sparse_commit( void *A );


/*!
 @abstract
 Returns the value of the given property name.
 
 @param A
 The sparse matrix object.
 
 @param pname
 The property name to get the value of.  See matrix properties enumeration for
 options.
 
 @result
 Returns the value of the property for a valid object and property, or 0 
 otherwise.
 
 @discussion
 Returns the value of the given property name. See matrix properties enumeration
 for further property details.

 */
long sparse_get_matrix_property( void *A, sparse_matrix_property pname );

/*!
 @abstract
 Set the given property for a matrix object that has not had any values 
 inserted.
 
 @param A
 The sparse matrix object.  Note that after elements have been inserted
 properties cannot be changed.
 
 @param pname
 The property name to set true.  See matrix properties enumeration for options.
 
 @result
 Returns SPARSE_SUCCESS when property is successfully set, otherwise return
 SPARSE_CANNOT_SET_PROPERTY.
 
 @discussion
 Set the given property for the matrix object.  The matrix object must not have
 had values inserted, else SPARSE_CANNOT_SET_PROPERTY is returned and the 
 property is not set.
 
 Certain groups of properties are mutually exclusive and setting multiple values
 within a group is undefined.
 
 */
sparse_status sparse_set_matrix_property( void *A, sparse_matrix_property pname );


/*!
 @abstract
 Return the number of rows of the matrix.
 */
sparse_dimension sparse_get_matrix_number_of_rows( void *A );

/*!
 @abstract
 Return the number of columns of the matrix.
 */
sparse_dimension sparse_get_matrix_number_of_columns( void *A );

/*!
 @abstract
 Return the number of nonzero values in the matrix.
 */
long sparse_get_matrix_nonzero_count( void *A );

/*!
 @abstract
 Return the number of nonzero values for the i'th row.  If index is out of
 bounds of the matrix, 0 is returned.
 */
long sparse_get_matrix_nonzero_count_for_row( void *A, sparse_index i );

/*!
 @abstract
 Return the number of nonzero values for the j'th column.  If index is out of
 bounds of the matrix, 0 is returned.
 */
long sparse_get_matrix_nonzero_count_for_column( void *A, sparse_index j );



/*!
 @abstract
 Release any memory associated with the matrix object.
 
 @param A
 The sparse matrix object.
 
 @result
 All memory associated with the matrix object is released and returns 
 SPARSE_SUCCESS.
 
 @discussion
 Release any memory associated with the matrix object.  Upon return the object 
 is no longer valid and any use of the object is undefined.
 
 */
sparse_status sparse_matrix_destroy( void *A );




#pragma mark - Sparse Utilities -
	/* Sparse Utility Routines */
/*!
 @functiongroup Sparse Utilities
 @abstract Various utility routines for creating and working with sparse 
 structures.
 */

/*!
 @abstract
 Return the number of nonzero values in the dense vector x.
 
 @param N
 The number of elements in the dense vector x.
 
 @param x
 Pointer to the vector x.
 
 @param incx
 Increment between valid values in the dense vector x.  Negative strides are
 supported.
 
 @result
 Return the count of the nonzero values in the vector x.
 
 */
long sparse_get_vector_nonzero_count_float( sparse_dimension N,
                                         const float * __restrict x,
                                         sparse_stride incx );
long sparse_get_vector_nonzero_count_double( sparse_dimension N,
                                          const double * __restrict x,
                                          sparse_stride incx );

/*!
 @abstract
 Pack the first nz nonzero values and indices from the dense vector x and
 place them in y and indy.
 
 @param N
 The number of elements in the dense vector x.
 
 @param nz
 The number of nonzero values to collect.  If less than nz nonzero elements are
 found in the N elements of x, then the last nz - actual_nonzero_count of y and
 indy are unused.
 
 @param x
 Pointer to the dense vector x.
 
 @param incx
 Increment between valid values in the dense vector x.  Negative strides are
 supported.
 
 @param y
 The destination dense storage of nonzero values of y.  Expected to be of size
 nz elements.  On return, any nonzero values are placed in this array, if the 
 actual number of nonzero values is less than nz, then the last 
 nz - actual_nonzero_count elements are unused.
 
 @param indy
 The destination dense storage of nonzero indices of y.  Expected to be of size 
 nz elements.  On return, any nonzero indices are placed in this array, if the 
 actual number of nonzero values is less than nz, then the last 
 nz - actual_nonzero_count elements are unused.  Returned indices are 0 based 
 (the first element of a pointer is ptr[0]).
 
 @result
 On success, y and indy are updated with up to the first nz nonzero indices.  
 The number of nonzero values written is returned.
 
 @discussion
 Pack the first nz nonzero values and indices from the dense vector x and
 place them in y and indy.  If less than nz nonzero elements are found in the N 
 elements of x, then the last nz - actual_nonzero_count elements of y and indy 
 are unused.  The number of indices written can range from 0 to nz values and 
 the number written is returned.
 
 */
long sparse_pack_vector_float( sparse_dimension N, sparse_dimension nz,
                                  const float * __restrict x,
                                  sparse_stride incx, float * __restrict y,
                                  sparse_index * __restrict indy );
long sparse_pack_vector_double( sparse_dimension N, sparse_dimension nz,
                                   const double * __restrict x,
                                   sparse_stride incx, double * __restrict y,
                                   sparse_index * __restrict indy );


/*!
 @abstract
 Extract elements from the sparse vector x into the corresponding location in
 the dense vector y.  Optionally zero the unused values of y.
 
 @param N
 The number of elements in the dense vector y.
 
 @param nz
 The number of nonzero entries in the sparse vector x.
 
 @param zero
 When true, zero the elements of y which do not have nonzero values written to
 them.  When false ignore the elements of y which do not have nonzero values
 written to them.
 
 @param x
 Pointer to the dense storage for the values of the sparse vector x.  The
 corresponding entry in indx holds the index of the value.  Contains nz values.
 
 @param indx
 Pointer to the dense storage for the index values of the sparse vector x.  The
 corresponding entry in x holds the values of the vector.  Contains nz values.
 
 Indices are always assumed to be stored in ascending order. Additionally,
 indices are assumed to be unique.  Undefined behavior if either of these
 assumptions are not met.
 
 All indices are 0 based (the first element of a pointer is ptr[0]).
 
 @param y
 Pointer to the dense vector y.  Expected to be of size N*abs(incy) elements.  
 Negative strides are supported.  Note, unlike dense BLAS routines, the pointer 
 points to the last element when stride is negative. On exit, the entries 
 described by the indices in indx will be filled with the corresponding values 
 in x and all other values will be unchanged if parameter zero is false, or set 
 to zero if parameter zero is true.
 
 @param incy
 Increment between valid values in the dense vector y.  Negative strides are
 supported.
 
 @result
 On exit y has been updated with the nonzero values. If nz is less than or
 equal to zero y is unchanged.
 
 @discussion
 Extract elements from the sparse vector x into the corresponding location in
 the dense vector y.  Optionally zero the unused values of y.
 
 if (zero) for (i in 0 .. N-1) y[i*incy] = 0;
 
 for (i in 0 .. nz-1) if (indx[i] < N) y[indx[i]*incy] = x[i];
 */
void sparse_unpack_vector_float( sparse_dimension N, sparse_dimension nz, bool zero,
                               const float * __restrict x,
                               const sparse_index * __restrict indx,
                               float * __restrict y, sparse_stride incy );
void sparse_unpack_vector_double( sparse_dimension N, sparse_dimension nz, bool zero,
                                const double * __restrict x,
                                const sparse_index * __restrict indx,
                                double * __restrict y, sparse_stride incy );

#ifdef __cplusplus
}
#endif

#endif
  /* __SPARSE_BLAS_H */

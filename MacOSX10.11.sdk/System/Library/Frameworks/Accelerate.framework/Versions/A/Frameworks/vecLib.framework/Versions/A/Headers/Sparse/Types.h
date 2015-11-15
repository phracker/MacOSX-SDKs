/*  Copyright (c) 2014 Apple Inc.  All rights reserved.                       */

#ifndef __SPARSE_TYPES_H
#define __SPARSE_TYPES_H

#pragma mark - Type defines -

/*!
 @header Sparse/Types.h
 @discussion
 Types supporting Sparse BLAS routines.
 
 @copyright Copyright (c) 2014 Apple Inc. All rights reserved.
*/

#include <stdint.h>
#include <stdbool.h>

/*!
 @abstract Sparse matrix type for float.  Opaque structure
 */
typedef struct sparse_m_float* sparse_matrix_float;
/*!
 @abstract Sparse matrix type for double.  Opaque structure
 */
typedef struct sparse_m_double* sparse_matrix_double;

/*!
 @abstract The dimension type. All dimensions are positive values.
 */
typedef uint64_t sparse_dimension;

/*!
 @abstract The stride type.  Supports negative strides for the dense vectors.
 */
typedef int64_t sparse_stride;

/*!
 @abstract The index type.  All indices including those in a sparse vectors 
 index array are positive values.
 */
typedef int64_t sparse_index;

/*!
 @abstract The type reflecting the status of an operations.
 
 @constant SPARSE_SUCCESS
 Operation was a success
 
 @constant SPARSE_ILLEGAL_PARAMETER
 Operation was not completed because one or more of the arguments had an illegal
 value.
 
 @constant SPARSE_CANNOT_SET_PROPERTY
 Matrix properties can only be set before any values are inserted into the
 matrix.  This error occurs if that order is not repsected.
 
 @constant SPARSE_SYSTEM_ERROR
 An internal error has occured, such as non enough memory.
 */
typedef enum {
    SPARSE_SUCCESS = 0,
    SPARSE_ILLEGAL_PARAMETER = -1000,
    SPARSE_CANNOT_SET_PROPERTY = -1001,
    SPARSE_SYSTEM_ERROR = -1002,
} sparse_status;

/*!
 @abstract The matrix property type
 */
typedef enum {
    SPARSE_UPPER_TRIANGULAR = 1,
    SPARSE_LOWER_TRIANGULAR = 2,
    
    SPARSE_UPPER_SYMMETRIC = 4,
    SPARSE_LOWER_SYMMETRIC = 8,
} sparse_matrix_property;


/*!
 @abstract The norm specifier
 @constant SPARSE_NORM_ONE
 Matrix element wise: sum over i,j ( | A[i,j] | )
 
 Matrix operator    : max over j ( sum over i ( | A[i,j] | )
 
 Vector element wise: sum over i ( | x[i] | )
 
 @constant SPARSE_NORM_TWO
 Matrix element wise: sqrt( sum over i,j (A[i,j])^2 )
 
 Matrix operator    : Largest singular value of matrix, note that the operator
 SPARSE_NORM_TWO is significantly more expensive than other norm operations.
 
 Vector element wise: sqrt( sum over i (x[i])^2 )
 
 @constant SPARSE_NORM_INF
 Matrix element wise: max over i,j ( | A[i,j] | )
 
 Matrix operator    : max over i ( sum over j ( | A[i,j] | )
 
 Vector element wise: max over i ( | x[i] | )
 
 @constant SPARSE_NORM_R1
 Matrix element wise: sum over j ( sqrt ( sum over i ( A[i,j]^2 ) ) )
 
 Matrix operator    : Not supported. Undefined
 
 Vector element wise: Not supported. Undefined
 */
typedef enum {
    SPARSE_NORM_ONE = 171,
    SPARSE_NORM_TWO = 173,
    SPARSE_NORM_INF = 175,
    SPARSE_NORM_R1 =  179
} sparse_norm;

#endif
   /* __SPARSE_TYPES_H */

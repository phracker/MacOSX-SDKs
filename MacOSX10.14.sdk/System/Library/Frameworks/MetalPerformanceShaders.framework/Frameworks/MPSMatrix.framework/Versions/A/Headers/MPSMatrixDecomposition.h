/*!
 *  @header MPSMatrixDecomposition.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2017 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders filter base classes
 */
#ifndef MPSMatrixDecomposition_h
#define MPSMatrixDecomposition_h

#import <MPSCore/MPSKernel.h>
#import <MPSMatrix/MPSMatrixTypes.h>

/*!
 *  @typedef    MPSMatrixDecompositionStatus
 *
 *  @abstract   A value to indicate the status of a matrix decomposition.
 *
 *  @constant   MPSMatrixDecompositionStatusSuccess        The decomposition was
 *              performed successfully.
 *
 *  @constant   MPSMatrixDecompositionStatusFailure         The decomposition was
 *              not able to be completed.
 *
 *  @constant   MPSMatrixDecompositionStatusSingular       The resulting decomposition
 *              is not suitable for use in a subsequent system solve.
 *
 *  @constant   MPSMatrixDecompositionStatusNonPositiveDefinite       A
 *              non-positive-definite pivot value was calculated.
 */
#ifdef DOXYGEN
typedef enum MPSMatrixDecompositionStatus
#else
typedef NS_ENUM( int, MPSMatrixDecompositionStatus)
#endif
{
    MPSMatrixDecompositionStatusSuccess             MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))  =   0,
    MPSMatrixDecompositionStatusFailure             MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))  =  -1,
    MPSMatrixDecompositionStatusSingular            MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))  =  -2,
    MPSMatrixDecompositionStatusNonPositiveDefinite MPS_ENUM_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0))  =  -3,
}
#ifdef DOXYGEN
    MPSMatrixDecompositionStatus
#endif
;

/*!
 *  @class      MPSMatrixDecompositionLU
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A kernel for computing the LU factorization of a matrix using
 *              partial pivoting with row interchanges.
 *
 *  @discussion A MPSMatrixDecompositionLU object computes an LU factorization:
 *
 *                  P * A = L * U
 *
 *              A is a matrix for which the LU factorization is to be computed.
 *              L is a unit lower triangular matrix and U is an upper triangular
 *              matrix.  P is a permutation matrix.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSMatrixDecompositionLU : MPSMatrixUnaryKernel

/*!
 *  @abstract   Initialize an MPSMatrixDecompositionLU object on a device
 *
 *  @param      device          The device on which the kernel will execute.
 *
 *  @param      rows            The number of rows in the source matrix.
 *
 *  @param      columns         The number of columns in the source matrix.
 *
 *  @return     A valid MPSMatrixDecompositionLU object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
                                  rows: (NSUInteger) rows
                               columns: (NSUInteger) columns;

/*!
 *  @abstract   Encode a MPSMatrixDecompositionLU kernel into a command Buffer.
 *
 *  @param      commandBuffer           A valid MTLCommandBuffer to receive the encoded filter
 *
 *  @param      sourceMatrix            A valid MPSMatrix containing the source data.  Must have
 *                                      enough space to hold a rows x columns matrix.
 *
 *  @param      resultMatrix            A valid MPSMatrix to contain the result.  Must have enough
 *                                      space to hold a rows x columns matrix.
 *
 *  @param      pivotIndices            A valid MPSMatrix to contain the pivot indices. Must have enough space
 *                                      to hold an array of size 1xmin(rows, columns) values.
 *                                      Element type must be MPSDataTypeUInt32.
 *
 *  @param      status                  A MTLBuffer which indicates the resulting MPSMatrixDecompositionStatus
 *                                      value.
 *
 *  @discussion This function encodes the MPSMatrixDecompositionLU object to a valid
 *              command buffer.
 *
 *              Upon completion the array pivotIndices contains, for each index i,
 *              the row interchanged with row i.
 *
 *              If during the computation U[k, k], for some k, is determined to be
 *              exactly zero MPSMatrixDecompositionStatusSingular will be returned in the
 *              provided status buffer.  The data referenced by the MTLBuffer is not valid
 *              until the command buffer has completed execution.  If the matrix
 *              return status is not desired NULL may be provided.
 *
 *              Upon successful factorization, resultMatrix contains the resulting
 *              lower triangular factor (without the unit diagonal elements) in its
 *              strictly lower triangular region and the upper triangular factor in
 *              its upper triangular region.
 *
 *              This kernel functions either in-place, if the result matrix
 *              completely aliases the source matrix, or out-of-place.  If there
 *              is any partial overlap between input and output data the results
 *              are undefined.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                 sourceMatrix: (MPSMatrix * __nonnull) sourceMatrix
                 resultMatrix: (MPSMatrix * __nonnull) resultMatrix
                 pivotIndices: (MPSMatrix * __nonnull) pivotIndices
                       status: (__nullable id <MTLBuffer>) status
MPS_SWIFT_NAME(encode(commandBuffer:sourceMatrix:resultMatrix:pivotIndices:info:));

@end // MPSMatrixDecompositionLU

/*!
 *  @class      MPSMatrixDecompositionCholesky
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A kernel for computing the Cholesky factorization of a matrix.
 *
 *  @discussion A MPSMatrixDecompositionLU object computes one of the following
 *              factorizations of a matrix A:
 *
 *                  A = L * L**T
 *                  A = U**T * U
 *
 *              A is a symmetric positive-definite matrix for which the
 *              factorization is to be computed. L and U are lower and upper
 *              triangular matrices respectively.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSMatrixDecompositionCholesky : MPSMatrixUnaryKernel

/*!
 *  @abstract   Initialize an MPSMatrixDecompositionCholesky object on a device
 *
 *  @param      device          The device on which the kernel will execute.
 *
 *  @param      lower           A boolean value indicating if the lower triangular
 *                              part of the source matrix is stored.  If lower = YES
 *                              the lower triangular part will be used and the factor
 *                              will be written to the lower triangular part of the
 *                              result, otherwise the upper triangular part will be used
 *                              and the factor will be written to the upper triangular
 *                              part.
 *
 *  @param      order           The number of rows and columns in the source matrix.
 *
 *  @return     A valid MPSMatrixDecompositionCholesky object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
                                 lower: (BOOL) lower
                                 order: (NSUInteger) order;

/*!
 *  @abstract   Encode a MPSMatrixDecompositionCholesky kernel into a command Buffer.
 *
 *  @param      commandBuffer           A valid MTLCommandBuffer to receive the encoded filter
 *
 *  @param      sourceMatrix            A valid MPSMatrix containing the source data.  Must have
 *                                      enough space to hold a order x order matrix.
 *
 *  @param      resultMatrix            A valid MPSMatrix to contain the result.  Must have enough
 *                                      space to hold a order x order matrix.
 *
 *  @param      status                  A MTLBuffer which indicates the resulting MPSMatrixDecompositionStatus
 *                                      value.
 *
 *  @discussion This function encodes the MPSMatrixDecompositionCholesky object to a valid
 *              command buffer.
 *
 *              If during the factorization a leading minor of the matrix is found to be
 *              not positive definite, MPSMatrixDecompositionNonPositiveDefinite will be returned
 *              in the provided status buffer.  Previously computed pivots and the non positive
 *              pivot are written to the result, but the factorization does not complete.
 *              The data referenced by the MTLBuffer is not valid until the command buffer has completed
 *              execution.  If the matrix return status is not desired NULL may be provided.
 *
 *              If the return status is MPSMatrixDecompositionStatusSuccess, resultMatrix
 *              contains the resulting factors in its lower or upper triangular regions
 *              respectively.
 *
 *              This kernel functions either in-place, if the result matrix
 *              completely aliases the source matrix, or out-of-place.  If there
 *              is any partial overlap between input and output data the results
 *              are undefined.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                 sourceMatrix: (MPSMatrix * __nonnull) sourceMatrix
                 resultMatrix: (MPSMatrix * __nonnull) resultMatrix
                       status: (__nullable id <MTLBuffer>) status
MPS_SWIFT_NAME(encode(commandBuffer:sourceMatrix:resultMatrix:status:));

@end // MPSMatrixDecompositionCholesky

#endif /* MPSMatrixDecomposition_h */

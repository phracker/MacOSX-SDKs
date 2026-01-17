/*!
 *  @header MPSMatrixMultiplication.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2016 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders filter base classes
 */
#ifndef MPSMatrixMultiplication_h
#define MPSMatrixMultiplication_h

#import <MPSCore/MPSKernel.h>
#import <MPSMatrix/MPSMatrixTypes.h>

/*!
 *  @class      MPSMatrixMultiplication
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A matrix multiplication kernel.
 *
 *  @discussion A MPSMatrixMultiplication object computes:
 *
 *                  C = alpha * op(A) * op(B) + beta * C
 *
 *              A, B, and C are matrices which are represented by MPSMatrix
 *              objects. alpha and beta are scalar values (of the same data type
 *              as values of C) which are applied as shown above.  A and B may
 *              each have an optional transposition operation applied.
 *
 *              A, B, and C (also referred to in later discussions as the left input
 *              matrix, the right input matrix, and the result matrix respectively).
 *
 *              A MPSMatrixMultiplication object is initialized with the transpose
 *              operators to apply to A and B, sizes for the operation to perform,
 *              and the scalar values alpha and beta.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(10.0), tvos(10.0))
@interface MPSMatrixMultiplication : MPSKernel
/*! @property   resultMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the result matrix, at which to
 *              start writing (and reading if necessary) results.  This property is
 *              modifiable and defaults to [0, 0] at initialization time.  If a
 *              different origin is desired then this should be modified prior to
 *              encoding the kernel.  The z value must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin resultMatrixOrigin;

/*! @property   leftMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the left input matrix, at which to
 *              start reading values.  This property is modifiable and defaults to
 *              [0, 0] at initialization time.  If a different origin is desired then
 *              this should be modified prior to encoding the kernel.  The z value
 *              must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin leftMatrixOrigin;

/*! @property   rightMatrixOrigin
 *
 *  @discussion The origin, relative to [0, 0] in the right input matrix, at which to
 *              start reading values.  This property is modifiable and defaults to
 *              [0, 0] at initialization time.  If a different origin is desired then
 *              this should be modified prior to encoding the kernel.  The z value
 *              must be 0.
 */
@property (readwrite, nonatomic) MTLOrigin rightMatrixOrigin;

/*! @property   batchStart
 *
 *  @discussion The index of the first matrix in the batch.  This property is
 *              modifiable and defaults to 0 at initialization time.  If
 *              batch processing should begin at a different matrix this value
 *              should be modified prior to encoding the kernel.
 */
@property (readwrite, nonatomic) NSUInteger batchStart;

/*! @property   batchSize
 *
 *  @discussion The number of matrices in the batch to process.  This property
 *              is modifiable and by default allows all matrices available at
 *              encoding time to be processed.
 */
@property (readwrite, nonatomic) NSUInteger batchSize;

/*!
 *  @abstract   Initialize an MPSMatrixMultiplication object on a device for a given size
 *              and desired transpose and scale values.
 *
 *  @param      device          The device on which the kernel will execute.
 *
 *  @param      transposeLeft   A boolean value which indicates if the left input matrix should be
 *                              used in transposed form.  If 'YES' then op(A) = A**T, otherwise
 *                              op(A) = A.
 *
 *  @param      transposeRight  A boolean value which indicates if the right input matrix should be
 *                              used in transposed form.  If 'YES' then op(B) = B**T, otherwise
 *                              op(B) = B.
 *
 *  @param      resultRows      The number of rows in the result matrix, M in BLAS GEMM description.
 *
 *  @param      resultColumns   The number of columns in the result matrix, N in BLAS GEMM description.
 *
 *  @param      interiorColumns The number of columns of the left input matrix after the
 *                              appropriate transpose operation has been applied. K in BLAS
 *                              GEMM description.
 *
 *  @param      alpha           The scale factor to apply to the product.  Specified in double
 *                              precision.  Will be converted to the appropriate precision in the
 *                              implementation subject to rounding and/or clamping as necessary.
 *
 *  @param      beta            The scale factor to apply to the initial values of C.  Specified
 *                              in double precision.  Will be converted to the appropriate precision in the
 *                              implementation subject to rounding and/or clamping as necessary.
 *
 *  @return     A valid MPSMatrixMultiplication object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
                         transposeLeft: (BOOL) transposeLeft
                        transposeRight: (BOOL) transposeRight
                            resultRows: (NSUInteger) resultRows
                         resultColumns: (NSUInteger) resultColumns
                       interiorColumns: (NSUInteger) interiorColumns
                                 alpha: (double) alpha
                                  beta: (double) beta;

/*!
 *  @abstract   Convenience initialization for a matrix-matrix multiplication
 *              with no transpositions, unit scaling of the product, and no
 *              accumulation of the result.  The scaling factors alpha and beta
 *              are taken to be 1.0 and 0.0 respectively.
 *
 *  @param      device          The device on which the kernel will execute.
 *
 *  @param      resultRows      The number of rows in the result matrix, M in BLAS GEMM description.
 *
 *  @param      resultColumns   The number of columns in the result matrix, N in BLAS GEMM description.
 *
 *  @param      interiorColumns The number of columns of the left input matrix. K in BLAS
 *                              GEMM description.
 *
 *  @return     A valid MPSMatrixMultiplication object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
                            resultRows: (NSUInteger) resultRows
                         resultColumns: (NSUInteger) resultColumns
                       interiorColumns: (NSUInteger) interiorColumns
MPS_AVAILABLE_STARTING(macos(10.13), ios(11.0), tvos(11.0));

/*!
 @discussion Use the above initialization method instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract   Encode a MPSMatrixMultiplication object to a command buffer.
 *
 *  @param      commandBuffer   A valid MTLCommandBuffer to receive the encoded kernel.
 *
 *  @param      leftMatrix      A valid MPSMatrix object which specifies the left input matrix.
 *
 *  @param      rightMatrix     A valid MPSMatrix object which specifies the right input matrix.
 *
 *  @param      resultMatrix    A valid MPSMatrix object which specifies the addend matrix which will
 *                              also be overwritten by the result.
 *
 *  @discussion Certain constraints apply to the sizes of the matrices depending on the transposition
 *              operations and sizes requested at initialization time as well as the origins at the time
 *              this routine is called:
 *
 *              The left input matrix must be large enough to hold an array of size resultRows x interiorColumns
 *              elements beginning at leftMatrixOrigin.
 *
 *              The right input matrix must be large enough to hold an array of size interiorColumns x resultColumns
 *              elements beginning at rightMatrixOrigin.
 *
 *              The result matrix must be large enough to hold an array of size resultRows x resultColumns
 *              elements beginning at resultMatrixOrigin.
 *
 *              Each matrix within the range specified by batchStart and batchSize, which also specifies
 *              a valid set of matrices within leftMatrix, rightMatrix, and resultMatrix, will
 *              be processed.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                   leftMatrix: (MPSMatrix * __nonnull) leftMatrix
                  rightMatrix: (MPSMatrix * __nonnull) rightMatrix
                 resultMatrix: (MPSMatrix * __nonnull) resultMatrix
                    MPS_SWIFT_NAME(encode(commandBuffer:leftMatrix:rightMatrix:resultMatrix:));



@end // MPSMatrixMultiplication

/*!
 *  @class      MPSMatrixVectorMultiplication
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A matrix-vector multiplication kernel.
 *
 *  @discussion A MPSMatrixVectorMultiplication object computes:
 *
 *                  y = alpha * op(A) * x + beta * y
 *
 *              A is a matrix represented by a MPSMatrix object. alpha and beta
 *              are scalar values (of the same data type as values of y) which are
 *              applied as shown above.  A may have an optional transposition
 *              operation applied.
 *
 *              A MPSMatrixVectorMultiplication object is initialized with the transpose
 *              operator to apply to A, sizes for the operation to perform,
 *              and the scalar values alpha and beta.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSMatrixVectorMultiplication : MPSMatrixBinaryKernel

/*!
 *  @abstract   Initialize an MPSMatrixVectorMultiplication object on a device for a given size
 *              and desired transpose and scale values.
 *
 *  @param      device          The device on which the kernel will execute.
 *
 *  @param      transpose       A boolean value which indicates if the input matrix should be
 *                              used in transposed form.  if 'YES' then op(A) == A**T, otherwise
 *                              op(A) == A.
 *
 *  @param      rows            The number of rows in the input matrix op(A), and the number of elements
 *                              in the vector y.
 *
 *  @param      columns         The number of columns in the input matrix op(A), and the number of
 *                              elements in the input vector x.
 *
 *  @param      alpha           The scale factor to apply to the product.  Specified in double
 *                              precision.  Will be converted to the appropriate precision in the
 *                              implementation subject to rounding and/or clamping as necessary.
 *
 *  @param      beta            The scale factor to apply to the initial values of y.  Specified
 *                              in double precision.  Will be converted to the appropriate precision in the
 *                              implementation subject to rounding and/or clamping as necessary.
 *
 *  @return     A valid MPSMatrixVectorMultiplication object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
                             transpose: (BOOL)                  transpose
                                  rows: (NSUInteger)            rows
                               columns: (NSUInteger)            columns
                                 alpha: (double)                alpha
                                  beta: (double)                beta;

/*!
 *  @abstract   Convenience initialization for a matrix-vector multiplication
 *              with no transposition, unit scaling of the product, and no
 *              accumulation of the result.  The scaling factors alpha and beta
 *              are taken to be 1.0 and 0.0 respectively.
 *
 *  @param      device          The device on which the kernel will execute.
 *
 *  @param      rows            The number of rows in the input matrix A, and the number of elements
 *                              in the vector y.
 *
 *  @param      columns         The number of columns in the input matrix A, and the number of
 *                              elements in the input vector x.
 *
 *  @return     A valid MPSMatrixVectorMultiplication object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
                                  rows: (NSUInteger)            rows
                               columns: (NSUInteger)            columns;

/*!
 @discussion Use the above initialization method instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*!
 *  @abstract   Encode a MPSMatrixVectorMultiplication object to a command buffer.
 *
 *  @param      commandBuffer   A valid MTLCommandBuffer to receive the encoded kernel.
 *
 *  @param      inputMatrix     A valid MPSMatrix object which specifies the input matrix A.
 *
 *  @param      inputVector     A valid MPSVector object which specifies the input vector x.
 *
 *  @param      resultVector    A valid MPSVector object which specifies the addend vector which will
 *                              also be overwritten by the result.
 *
 *  @discussion The left input matrix must be large enough to hold an array of size (rows x columns)
 *              elements beginning at primarySourceMatrixOrigin.
 *
 *              The input vector must be large enough to hold an array of size (columns)
 *              elements beginning at secondarySourceMatrixOrigin.x  secondarySourceMatrixOrigin.y and
 *              secondarySourceMatrixOrigin.z must be zero.
 *
 *              The result vector must be large enough to hold an array of size (rows)
 *              elements beginning at resultMatrixOrigin.x.  resultMatrixOrigin.y and
 *              resultMatrixOrigin.z must be zero.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)  commandBuffer
                  inputMatrix: (MPSMatrix * __nonnull)     inputMatrix
                  inputVector: (MPSVector * __nonnull)     inputVector
                 resultVector: (MPSVector * __nonnull)           resultVector
                    MPS_SWIFT_NAME(encode(commandBuffer:inputMatrix:inputVector:resultVector:));

@end // MPSMatrixVectorMultiplication
#endif /* MPSMatrixMultiplication_h */

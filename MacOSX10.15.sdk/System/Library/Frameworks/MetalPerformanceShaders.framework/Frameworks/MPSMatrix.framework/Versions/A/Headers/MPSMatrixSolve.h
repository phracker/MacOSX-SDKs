/*!
 *  @header MPSMatrixSolve.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2016 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders filter base classes
 */
#ifndef MPSMatrixSolve_h
#define MPSMatrixSolve_h

#import <MPSCore/MPSKernel.h>
#import <MPSMatrix/MPSMatrixTypes.h>

/*!
 *  @class      MPSMatrixSolveTriangular
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A kernel for computing the solution of a linear system of
 *              equations using a triangular coefficient matrix.
 *
 *  @discussion A MPSMatrixSolveTriangular finds the solution matrix to the
 *              triangular system:
 *
 *                  op(A) * X = alpha * B    or    X * op(A) = alpha * B
 *
 *              Where A is either upper or lower triangular and op(A) is A**T
 *              or A.  B is the array of right hand sides for which the
 *              equations are to be solved.  X is the resulting matrix of
 *              solutions.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSMatrixSolveTriangular : MPSMatrixBinaryKernel

/*!
 *  @abstract   Initialize an MPSMatrixSolveTriangular object on a device
 *
 *  @param      device          The device on which the kernel will execute.
 *
 *  @param      right           A boolean value which indicates if the 
 *                              coefficient matrix is multiplied on the left
 *                              or right side of the solution.  NO indicates
 *                              the multiplication is on the left.
 *
 *  @param      upper           A boolean value which indicates if the source
 *                              is lower or upper triangular.  NO indicates
 *                              that the coefficient matrix is lower triangular.
 *
 *  @param      transpose       A boolean value which indicates if the source
 *                              matrix should be used in transposed form.  NO
 *                              indicates that the coefficient matrix is to be
 *                              used normally.
 *
 *  @param      unit            A boolean value which indicates if the source
 *                              matrix is unit triangular.
 *
 *  @param      order           The order of the source matrix and, if
 *                              right == NO, the number of rows in the solution
 *                              and right hand side matrices.  If right == YES
 *                              the number of columns in the solution and right
 *                              hand side matrices.
 *
 *  @param      numberOfRightHandSides  If right == NO, the number of columns in the
 *                                      solution and right hand side matrices.  The
 *                                      number of rows otherwise.
 *
 *  @param      alpha           A double precision value used to scale the right
 *                              hand sides.
 *
 *  @discussion This function initializes a MPSMatrixSolveTriangular object.  It
 *              may allocate device side memory.
 *
 *  @return     A valid MPSMatrixSolveTriangular object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
                                 right: (BOOL) right
                                 upper: (BOOL) upper
                             transpose: (BOOL) transpose
                                  unit: (BOOL) unit
                                 order: (NSUInteger) order
                numberOfRightHandSides: (NSUInteger) numberOfRightHandSides
                                 alpha: (double) alpha;

/*!
 *  @abstract   Encode a MPSMatrixSolveTriangular kernel into a command Buffer.
 *
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the
 *                                  encoded filter
 *
 *  @param      sourceMatrix        A valid MPSMatrix containing the source
 *                                  matrix.
 *
 *  @param      rightHandSideMatrix A valid MPSMatrix containing the right hand
 *                                  side values.
 *
 *  @param      solutionMatrix      A valid MPSMatrix to contain the result.
 *
 *  @discussion This function encodes the MPSMatrixSolveTriangular object to a
 *              valid command buffer.
 *
 *              rightHandSideMatrix and solutionMatrix must be large enough to
 *              hold at least order * numberOfRightHandSides values starting at
 *              secondarySourceMatrixOrigin and resultMatrixOrigin respectively.
 *
 *              sourceMatrix must be at least size order x order starting at
 *              primarySourceMatrixOrigin.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                 sourceMatrix: (MPSMatrix * __nonnull) sourceMatrix
          rightHandSideMatrix: (MPSMatrix * __nonnull) rightHandSideMatrix
               solutionMatrix: (MPSMatrix * __nonnull) solutionMatrix
MPS_SWIFT_NAME(encode(commandBuffer:sourceMatrix:rightHandSideMatrix:solutionMatrix:));

@end // MPSMatrixSolveTriangular

/*!
 *  @class      MPSMatrixSolveLU
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A kernel for computing the solution of a linear system of equations
 *              using the LU factorization resulting from a MPSMatrixDecompositionLU
 *              kernel.
 *
 *  @discussion A MPSMatrixSolveLU finds the solution matrix to the system:
 *
 *                  op(A) * X = B
 *
 *              Where op(A) is A**T or A.  B is the array of right hand sides for which
 *              the equations are to be solved.  X is the resulting matrix of solutions.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSMatrixSolveLU : MPSMatrixBinaryKernel
/*!
 *  @abstract   Initialize an MPSMatrixSolveLU object on a device
 *
 *  @param      device          The device on which the kernel will execute.
 *
 *  @param      transpose       A boolean value which indicates if the source
 *                              matrix should be used in transposed form.
 *
 *  @param      order           The order of the source matrix and the number of
 *                              rows in the solution and right hand side matrices.
 *
 *  @param      numberOfRightHandSides  The number of columns in the solution and right hand side
 *                                      matrices.
 *
 *  @return     A valid MPSMatrixSolveLU object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
                             transpose: (BOOL) transpose
                                 order: (NSUInteger) order
                numberOfRightHandSides: (NSUInteger) numberOfRightHandSides;

/*!
 *  @abstract   Encode a MPSMatrixSolveLU kernel into a command Buffer.
 *
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *
 *  @param      sourceMatrix        A valid MPSMatrix containing the source matrix in factored
 *                                  form as returned by a previous successful execution of a
 *                                  MPSMatrixDecompositionLU kernel.
 *
 *  @param      rightHandSideMatrix A valid MPSMatrix containing the right hand side values.
 *
 *  @param      pivotIndices        A valid MPSMatrix which contains the pivot indices as returned by
 *                                  a previous successful execution of a MPSMatrixDecompositionLU
 *                                  kernel.
 *
 *  @param      solutionMatrix      A valid MPSMatrix to contain the result.
 *
 *  @discussion This function encodes the MPSMatrixSolveLU object to a valid command buffer.
 *              sourceMatrix should contain the lower and upper triangular factors of A as
 *              results from a previous execution of MPSMatrixDecompositionLU.
 *
 *              pivotIndices is an array of pivots resulting from a previous execution of
 *              MPSMatrixDecompositionLU.
 *
 *              rightHandSideMatrix and solutionMatrix must be large enough to hold a matrix
 *              of size order x numberOfRightHandSides starting at secondarySourceMatrixOrigin and
 *              resultMatrixOrigin respectively.
 *
 *              sourceMatrix must be at least size order x order starting at primarySourceMatrixOrigin.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                 sourceMatrix: (MPSMatrix * __nonnull) sourceMatrix
          rightHandSideMatrix: (MPSMatrix * __nonnull) rightHandSideMatrix
                 pivotIndices: (MPSMatrix * __nonnull) pivotIndices
               solutionMatrix: (MPSMatrix * __nonnull) solutionMatrix
MPS_SWIFT_NAME(encode(commandBuffer:sourceMatrix:rightHandSideMatrix:pivotIndices:solutionMatrix:));

@end // MPSMatrixSolveLU

/*!
 *  @class      MPSMatrixSolveCholesky
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A kernel for computing the solution of a linear system of equations
 *              using the Cholesky factorization resulting from a
 *              MPSMatrixDecompositionCholesky kernel.
 *
 *  @discussion A MPSMatrixSolveCholesky finds the solution matrix to the system:
 *
 *                  A * X = B
 *
 *              Where A is symmetric positive definite.  B is the array of
 *              right hand sides for which the equations are to be solved.
 *              X is the resulting matrix of solutions.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSMatrixSolveCholesky : MPSMatrixBinaryKernel
/*!
 *  @abstract   Initialize an MPSMatrixSolveCholesky object on a device
 *
 *  @param      device          The device on which the kernel will execute.
 *
 *  @param      upper           A boolean value which indicates if the source
 *                              matrix stores the lower or upper triangular
 *                              factors.
 *
 *  @param      order           The order of the source matrix and the number of
 *                              rows in the solution and right hand side matrices.
 *
 *  @param      numberOfRightHandSides  The number of columns in the solution and right hand side
 *                                      matrices.
 *
 *  @return     A valid MPSMatrixSolveCholesky object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id<MTLDevice>) device
                                 upper: (BOOL) upper
                                 order: (NSUInteger) order
                numberOfRightHandSides: (NSUInteger) numberOfRightHandSides;

/*!
 *  @abstract   Encode a MPSMatrixSolveCholesky kernel into a command Buffer.
 *
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded filter
 *
 *  @param      sourceMatrix        A valid MPSMatrix containing the source matrix in factored
 *                                  form as returned by a previous successful execution of a
 *                                  MPSMatrixDecompositionCholesky kernel.
 *
 *  @param      rightHandSideMatrix A valid MPSMatrix containing the right hand side values.
 *
 *  @param      solutionMatrix      A valid MPSMatrix to contain the result.
 *
 *  @discussion This function encodes the MPSMatrixSolveCholesky object to a valid
 *              command buffer. sourceMatrix should contain either the lower or upper triangular
 *              factors corresponding to the factorization returned by a previous execution
 *              of MPSMatrixDecompositionCholesky.
 *
 *              rightHandSideMatrix and solutionMatrix must be large enough to hold a matrix
 *              of size order x numberOfRightHandSides starting at secondarySourceMatrixOrigin and
 *              resultMatrixOrigin respectively.
 *
 *              sourceMatrix must be at least size order x order starting at primarySourceMatrixOrigin.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                 sourceMatrix: (MPSMatrix * __nonnull) sourceMatrix
          rightHandSideMatrix: (MPSMatrix * __nonnull) rightHandSideMatrix
               solutionMatrix: (MPSMatrix * __nonnull) solutionMatrix
MPS_SWIFT_NAME(encode(commandBuffer:sourceMatrix:rightHandSideMatrix:solutionMatrix:));

@end // MPSMatrixSolveCholesky

#endif /* MPSMatrixSolve_h */

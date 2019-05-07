/*!
 *  @header MPSMatrixSum.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2017 Apple Inc. All rights reserved.
 *  @abstract MetalPerformanceShaders filter base classes
 */

#ifndef MPSMatrixSum_h
#define MPSMatrixSum_h

#include <MPSNeuralNetwork/MPSCNNNeuronType.h>
#include <MPSMatrix/MPSMatrix.h>

/*!
 *  @class      MPSMatrixSum
 *  @dependency This depends on Metal.framework
 *  @discussion MPSMatrixSum performs a pointwise summation of N MPSMatrix
 *              objects and applies an optional bias term and neuron activation
 *              function.
 *
 *              MPSMatrix A = empty matrix;
 *              for (i = 0; i < N; ++i)
 *                  A += alpha[i]*B[i];
 *
 *              if (bias)
 *                  A += broadcast(bias);
 *
 *              if (neuron)
 *                  A = applyNeuron(A);
 *
 *              Where B is the array of MPSMatrix objects, A is the destination
 *              MPSMatrix, alpha is an array of scalar values, bias is a vector
 *              which is broadcast and accumulated across each row of the intermediate
 *              result, and applyNeuron is a neuron activation function.
 *
 *              Each matrix in the array may have an independent origin.
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSMatrixSum : MPSKernel
/*
 * Use initWithDevice:count:rows:columns:transpose instead.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device NS_UNAVAILABLE;

/*! @abstract   Initialize a MPSMatrixSum kernel.
 *  @param      device                      The device on which to initialize the kernel.
 *  @param      count                       The number of matrices to be summed.
 *  @param      rows                        The number of rows to use in the input matrices.
 *  @param      columns                     The number of columns to use in the input matrices.
 *  @param      transpose                   If YES the result of the summation is to be transposed
 *                                          prior to applying the bias and activation.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                 count: (NSUInteger) count
                                  rows: (NSUInteger) rows
                               columns: (NSUInteger) columns
                             transpose: (BOOL) transpose
NS_DESIGNATED_INITIALIZER;

/*! @abstract   The number of rows to sum. */
@property (nonatomic, readonly) NSUInteger rows;

/*! @abstract   The number of columns to sum. */
@property (nonatomic, readonly) NSUInteger columns;

/*! @abstract   The number of matrices to sum. */
@property (nonatomic, readonly) NSUInteger count;

/*! @abstract   The transposition used to initialize the kernel. */
@property (nonatomic, readonly) BOOL transpose;

/*!
 *  @abstract   Specifies a neuron activation function to be used.
 *
 *  @discussion This method can be used to add a neuron activation funtion of given type with
 *              associated scalar parameters A, B, and C that are shared across all output values.
 *              Note that this method can only be used to specify neurons which are specified by three (or fewer)
 *              parameters shared across all output values (or channels, in CNN nomenclature). It is an error to call
 *              this method for neuron activation functions like MPSCNNNeuronTypePReLU,
 *              which require per-channel parameter values. An MPSMatrixSum kernel is initialized
 *              with a default neuron function of MPSCNNNeuronTypeNone.
 *
 *  @param      neuronType      Type of neuron activation function. For full list see MPSCNNNeuronType.h
 *  @param      parameterA      parameterA of neuron activation that is shared across all output values.
 *  @param      parameterB      parameterB of neuron activation that is shared across all output values.
 *  @param      parameterC      parameterC of neuron activation that is shared across all output values.
 */
-(void) setNeuronType: (MPSCNNNeuronType) neuronType
           parameterA: (float) parameterA
           parameterB: (float) parameterB
           parameterC: (float) parameterC;

/*!
 *  @abstract   Getter funtion for neuronType set using setNeuronType:parameterA:parameterB:parameterC method
 */
-(MPSCNNNeuronType) neuronType;

/*!
 @abstract      Neuron parameter A.
 */
@property (nonatomic, readonly) float neuronParameterA;

/*!
 @abstract      Neuron parameter B.
 */
@property (nonatomic, readonly) float neuronParameterB;

/*!
 @abstract      Neuron parameter C.
 */
@property (nonatomic, readonly) float neuronParameterC;

/*! @abstract   Encode the operations to the command buffer
 *  @param          buffer              The command buffer in which to encode the operation.
 *  @param          sourceMatrices      A list of matrices from which the matrix data is read.
 *  @param          resultMatrix        The result matrix.
 *  @param          scaleVector         A MPSVector of type MPSDataTypeFloat32 containing the list of
 *                                      scale factors, specified in single precision.
 *  @param          offsetVector        A MPSVector of type MPSDataTypeUInt32 containing the list of
 *                                      offsets, stored as a packed array of MPSMatrixOffset values.
 *  @param          biasVector          A MPSVector containing the bias terms to add to the result
 *                                      prior to applying the neuron function, if any.  May be nil.
 *  @param          startIndex          The starting index into the scale and offset vectors.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) buffer
               sourceMatrices: (NSArray<MPSMatrix *>*__nonnull) sourceMatrices
                 resultMatrix: (MPSMatrix * __nonnull) resultMatrix
                  scaleVector: (MPSVector * __nullable) scaleVector
                 offsetVector: (MPSVector * __nullable) offsetVector
                   biasVector: (MPSVector * __nullable) biasVector
                   startIndex: (NSUInteger) startIndex;

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSMatrixSum kernel.
 *  @param      device      The MTLDevice on which to make the MPSMatrixSum object.
 *  @return     A new MPSMatrixSum object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;
@end // MPSMatrixSum
#endif /* MPSMatrixSum_h */

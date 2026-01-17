//
//  MPSMatrixFullyConnected.h
//  MPS
//
//  Created by Justin Voo on 8/30/17.
//  Copyright © 2017 Apple. All rights reserved.
//

#ifndef MPSMatrixFullyConnected_h
#define MPSMatrixFullyConnected_h

#include <MPSNeuralNetwork/MPSCNNNeuronType.h>
#include <MPSMatrix/MPSMatrix.h>

#ifdef __cplusplus
extern "C" {
#endif
    
/*!
 *  @class      MPSMatrixFullyConnected
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   Applies a fully connected neural network layer by performing a
 *              a matrix multiplication, adding a bias vector, scaling, and applying a
 *              neuron activation function.
 *
 *  @discussion A MPSMatrixFullyConnected object computes:
 *
 *                  y = neuron(alpha * x * W + bias)
 *
 *              y is the output matrix, x and W are input matrices corresponding
 *              to a collection of input vectors and weights respectively, and bias
 *              is a vector which is broadcast and accumulated to each row
 *              of the product.  alpha is a scale factor applied to the product.
 *
 *              neuron() is a pointwise function applied to the intermediate result.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), tvos(11.0))
@interface MPSMatrixFullyConnected : MPSMatrixBinaryKernel
/*! @property   sourceNumberOfFeatureVectors
 *
 *  @discussion The number of input vectors which make up the input array.  This
 *              is equivalent to the number of rows to consider from the primary
 *              source matrix.
 *              This property is modifiable and defaults to NSUIntegerMax.  At encode
 *              time the larger of this property or the available number of inputs is
 *              used.  The value of NSUIntegerMax thus indicates that all available input
 *              rows (beginning at primarySourceMatrixOrigin.x) should be considered.
 */
@property (readwrite, nonatomic) NSUInteger sourceNumberOfFeatureVectors;

/*! @property   sourceInputFeatureChannels
 *
 *  @discussion The input size to to use in the operation.  This is equivalent to the
 *              number of columns and the number of rows in the primary (input array) and
 *              secondary (weight array) source matrices respectively.
 *              This property is modifiable and defaults to NSUIntegerMax.  At encode
 *              time the larger of this property or the available input size is used.
 *              The value of NSUIntegerMax thus indicates that all available
 *              columns in the input array (beginning at primarySourceMatrixOrigin.y) and all
 *              available rows in the weight array (beginning at secondarySourceMatrixOrigin.x)
 *              should be considered.
 *              Note: The value used in the operation will be
 *              MIN(MIN(inputMatrix.columns - primarySourceMatrixOrigin.y,
 *                      weightMatrix.rows - secondarySourceMatrixOrigin.x),
 *                  sourceInputFeatureChannels)
 */
@property (readwrite, nonatomic) NSUInteger sourceInputFeatureChannels;

/*! @property   sourceOutputFeatureChannels
 *
 *  @discussion The output size to to use in the operation.  This is equivalent to the
 *              number of columns to consider in the weight array, or the secondary source matrix.
 *              This property is modifiable and defaults to NSUIntegerMax.  At encode
 *              time the larger of this property or the available output size is used.
 *              The value of NSUIntegerMax thus indicates that all available
 *              columns in the weight array (beginning at secondarySourceMatrixOrigin.y)
 *              should be considered.
 */
@property (readwrite, nonatomic) NSUInteger sourceOutputFeatureChannels;

/*! @property   alpha
 *
 *  @discussion The scale factor to apply to the product.  Specified in double
 *              precision.  Will be converted to the appropriate precision in the
 *              implementation subject to rounding and/or clamping as necessary.
 *              Defaults to 1.0 at initialization time.
 */
@property (readwrite, nonatomic) double alpha;

/*!
 *  @abstract   Specifies a neuron activation function to be used.
 *
 *  @discussion This method can be used to add a neuron activation funtion of given type with
 *              associated scalar parameters A, B, and C that are shared across all output values.
 *              Note that this method can only be used to specify neurons which are specified by three (or fewer)
 *              parameters shared across all output values (or channels, in CNN nomenclature). It is an error to call
 *              this method for neuron activation functions like MPSCNNNeuronTypePReLU,
 *              which require per-channel parameter values. For those kind of neuron activation functions,
 *              use appropriate setter functions.  An MPSMatrixFullyConnected kernel is initialized
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
 *  @abstract   Getter funtion for neuronType set using setNeuronType:parameterA:parameterB:parameterC method
 */
-(float) neuronParameterA;

/*!
 *  @abstract   Getter funtion for neuronType set using setNeuronType:parameterA:parameterB:parameterC method
 */
-(float) neuronParameterB;

/*!
 *  @abstract   Getter funtion for neuronType set using setNeuronType:parameterA:parameterB:parameterC method
 */
-(float) neuronParameterC;

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   Encode a MPSMatrixFullyConnected object to a command buffer.
 *
 *  @param      commandBuffer   A valid MTLCommandBuffer to receive the encoded kernel.
 *
 *  @param      inputMatrix     A valid MPSMatrix object which specifies the input array.
 *
 *  @param      weightMatrix    A valid MPSMatrix object which specifies the weight array.
 *
 *  @param      biasVector      A valid MPSVector object which specifies the bias values, or
 *                              a null object to indicate that no bias is to be applied.
 *
 *  @param      resultMatrix    A valid MPSMatrix object which specifies the output array.
 *
 *  @discussion Encodes the operation to the specified command buffer.  resultMatrix
 *              must be large enough to hold a
 *                  MIN(sourceNumberOfInputs,
 *                      inputMatrix.rows - primarySourceMatrixOrigin.x)
 *                  x
 *                  MIN(sourceOutputFeatureChannels,
 *                      weightMatrix.columns - secondarySourceMatrixOrigin.y) array.
 *
 *              The bias vector must contain at least
 *                  MIN(sourceOutputFeatureChannels, weightMatrix.columns - secondarySourceMatrixOrigin.y) elements.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  inputMatrix: (MPSMatrix * __nonnull) inputMatrix
                 weightMatrix: (MPSMatrix * __nonnull) weightMatrix
                   biasVector: (MPSVector * __nullable) biasVector
                 resultMatrix: (MPSMatrix * __nonnull) resultMatrix
MPS_SWIFT_NAME(encode(commandBuffer:inputMatrix:weightMatrix:biasVector:resultMatrix:));

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSMatrixFullyConnected
 *  @param      device      The MTLDevice on which to make the MPSMatrixFullyConnected object.
 *  @return     A new MPSMatrixFullyConnected object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   Make a copy of this kernel for a new device - @see MPSKernel
 *  @param      zone        The NSZone in which to allocate the object
 *  @param      device      The device for the new MPSKernel. If nil, then use
 *                          self.device.
 *  @result     A pointer to a copy of this MPSKernel. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */
- (nonnull instancetype) copyWithZone:(nullable NSZone *)zone
                               device:(nullable id <MTLDevice>) device;

@end // MPSMatrixFullyConnected

/*!
 *  @class      MPSMatrixFullyConnectedGradient
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   Computes the gradient of the fully connected layer with respect
 *              to either the weights and bias terms or the input feature vectors.
 *
 *  @discussion An MPSMatrixFullyConnectedGradient kernel may be used to compute
 *              the gradients corresponding to a MPSMatrixFullyConnected kernel.
 *              The properties, input, and weight data must match those values
 *              used in the forward computation.
 *              This kernel does not compute the gradient of any non-identity
 *              activation function which may have been applied in the forward
 *              kernel.  Such a kernel must be expressed using both MPSMatrixFullyConnected
 *              and MPSMatrixNeuron if a gradient is to be computed.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.14), ios(12.0), tvos(12.0))
@interface MPSMatrixFullyConnectedGradient : MPSMatrixBinaryKernel
/*! @property   sourceNumberOfFeatureVectors
 *
 *  @discussion The number of input vectors which make up the input array.
 *              This is equivalent to the number of rows in both the input
 *              matrix and the source gradient matrix.
 *
 *              This value should be equal to the corresponding value in the
 *              forward fully connected kernel.
 */
@property (readwrite, nonatomic) NSUInteger sourceNumberOfFeatureVectors;

/*! @property   sourceOutputFeatureChannels
 *
 *  @discussion The number of feature channels in the output of the forward
 *              fully connected layer.
 *              This is equivalent to the number of columns in both the weight
 *              matrix and the source gradient matrix.
 *
 *              This value should be equal to the corresponding value in the
 *              forward fully connected kernel.
 */
@property (readwrite, nonatomic) NSUInteger sourceOutputFeatureChannels;

/*! @property   sourceInputFeatureChannels
 *
 *  @discussion The number of feature channels in the input to the forward
 *              fully connected layer.
 *              This is equivalent to the number of columns in the input matrix.
 *
 *              This value should be equal to the corresponding value in the
 *              forward fully connected kernel.
 */
@property (readwrite, nonatomic) NSUInteger sourceInputFeatureChannels;

/*! @property   alpha
 *
 *  @discussion Scale factor to apply to the product.  This value should be equal
 *              to the corresponding value in the forward fully connected kernel.
 */
@property (readwrite, nonatomic) double alpha;

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   Encode a MPSMatrixFullyConnectedGradient object to a command buffer and
 *              produce the gradient of the loss function with respect to the input data.
 *
 *  @param      commandBuffer               A valid MTLCommandBuffer to receive the encoded kernel.
 *
 *  @param      gradientMatrix              A valid MPSMatrix object which specifies the input gradient.
 *
 *  @param      weightMatrix                A valid MPSMatrix object which specifies the weight array.
 *
 *  @param      resultGradientForDataMatrix A valid MPSMatrix object which specifies the result gradient.
 *
 *  @discussion This operation computes the resulting gradient of the loss function with respect
 *              to the forward kernel's input data.  weightMatrix should contain the same values
 *              used to compute the result of the forward kernel.
 */
-(void) encodeGradientForDataToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                              gradientMatrix: (MPSMatrix const* __nonnull) gradientMatrix
                                weightMatrix: (MPSMatrix const* __nonnull) weightMatrix
                 resultGradientForDataMatrix: (MPSMatrix* __nonnull) resultGradientForDataMatrix;

/*!
 *  @abstract   Encode a MPSMatrixFullyConnectedGradient object to a command buffer and
 *              produce the gradient of the loss function with respect to the weight matrix
 *              and bias vector.
 *
 *  @param      commandBuffer                   A valid MTLCommandBuffer to receive the encoded kernel.
 *
 *  @param      gradientMatrix                  A valid MPSMatrix object which specifies the input gradient.
 *
 *  @param      inputMatrix                     A valid MPSMatrix object which specifies the input array.
 *
 *  @param      resultGradientForWeightMatrix   A valid MPSMatrix object which specifies the resulting gradients
 *                                              with respect to the weights.
 *
 *  @param      resultGradientForBiasVector     A valid MPSVector object which specifies the resulting gradients
 *                                              with respect to the bias terms.  If NULL these values will not be
 *                                              returned.
 *
 *  @discussion This operation computes the resulting gradient of the loss function with respect
 *              to the forward kernel's weight data.  inputMatrix should contain the same values
 *              used to compute the result of the forward kernel.
 */
-(void) encodeGradientForWeightsAndBiasToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                                        gradientMatrix: (MPSMatrix const* __nonnull) gradientMatrix
                                           inputMatrix: (MPSMatrix const* __nonnull) inputMatrix
                         resultGradientForWeightMatrix: (MPSMatrix* __nonnull) resultGradientForWeightMatrix
                           resultGradientForBiasVector: (MPSVector* __nullable) resultGradientForBiasVector;

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSMatrixFullyConnectedGradient
 *  @param      device      The MTLDevice on which to make the MPSMatrixFullyConnectedGradient object.
 *  @return     A new MPSMatrixFullyConnected object, or nil if failure.
 */
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder
                                device:(nonnull id <MTLDevice>) device NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   Make a copy of this kernel for a new device - @see MPSKernel
 *  @param      zone        The NSZone in which to allocate the object
 *  @param      device      The device for the new MPSKernel. If nil, then use
 *                          self.device.
 *  @result     A pointer to a copy of this MPSKernel. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */
- (nonnull instancetype) copyWithZone:(nullable NSZone *)zone
                               device:(nullable id <MTLDevice>) device;

@end    // MPSMatrixFullyConnectedGradient

#ifdef __cplusplus
}
#endif
#endif /* MPSMatrixFullyConnected_h */

/*!
 *  @header MPSMatrixNeuron.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 *  @abstract MPSMatrices fused with neurons
 */


#ifndef MPSMatrixNeuron_h
#define MPSMatrixNeuron_h

#include <MPSNeuralNetwork/MPSCNNNeuronType.h>
#include <MPSMatrix/MPSMatrix.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @class      MPSMatrixNeuron
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A neuron activation kernel that operates on matrices.
 *
 *  @discussion A MPSMatrixNeuron object computes:
 *
 *                  y = neuron(alpha * x + bias)
 *
 *              y is the output matrix, x is the input matrix corresponding
 *              to a collection of input vectors and bias is a vector which is broadcast
 *              and accumulated to each row of the intermediate result.
 *              alpha is a scale factor applied to the input.
 *
 *              neuron() defines the pointwise function that is applied to the intermediate result.
 *
 *              Note: This function computes the same result as MPSMatrixFullyConnected that has
 *                      unit weight matrix.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.13), ios(11.0), macCatalyst(13.0), tvos(11.0))
@interface MPSMatrixNeuron : MPSMatrixUnaryKernel

/*! @property   sourceNumberOfFeatureVectors
 *
 *  @discussion The number of input vectors which make up the input array.  This
 *              is equivalent to the number of rows to consider from the primary
 *              source matrix.
 *              This property is modifiable and defaults to NSUIntegerMax.  At encode
 *              time the larger of this property or the available number of inputs is
 *              used.  The value of NSUIntegerMax thus indicates that all available input
 *              rows (beginning at sourceMatrixOrigin.x) should be considered.
 */
@property (readwrite, nonatomic) NSUInteger sourceNumberOfFeatureVectors;

/*! @property   sourceInputFeatureChannels
 *
 *  @discussion The input size to to use in the operation.  This is equivalent to the
 *              number of columns in the primary (input array) source matrix to consider
 *              and the number of channels to produce for the output matrix.
 *              This property is modifiable and defaults to NSUIntegerMax.  At encode
 *              time the larger of this property or the available input size is used.
 *              The value of NSUIntegerMax thus indicates that all available columns in
 *              the input array (beginning at sourceMatrixOrigin.y) should be considered.
 *              Defines also the number of output feature channels.
 *              Note: The value used in the operation will be
 *              MIN(inputMatrix.columns - sourceMatrixOrigin.y, sourceInputFeatureChannels)
 */
@property (readwrite, nonatomic) NSUInteger sourceInputFeatureChannels;


/*! @property   alpha
 *
 *  @discussion The scale factor to apply to the input.  Specified in double
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
 *              use appropriate setter functions.  An MPSMatrixNeuron kernel is initialized
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

/*!
 *  @abstract   Add per output value neuron parameters A for PReLu neuron activation functions.
 *
 *  @discussion This method sets the neuron to PReLU, zeros parameters A and B and sets the per output value
 *              neuron parameters A to an array containing a unique value of A for each output value.
 *
 *              If the neuron function is f(v,a,b), it will apply
 *
 *                     resultMatrix(i, j) = f( input(i, j), A[j], B[j] )
 *                  where j in [0, sourceInputFeatureChannels]
 *
 *              See https://arxiv.org/pdf/1502.01852.pdf for details.
 *
 *              All other neuron types, where parameter A
 *              and parameter B are shared across output values must be set using
 *              -setNeuronType:parameterA:parameterB:
 *
 *  @param      A       An array containing float values for neuron parameter A.
 *                      Number of entries must be equal to MIN(inputMatrix.columns - sourceMatrixOrigin.y, sourceInputFeatureChannels)
 */
-(void) setNeuronToPReLUWithParametersA: (NSData* __nonnull) A;

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   Encode a MPSMatrixNeuron object to a command buffer.
 *
 *  @param      commandBuffer   A valid MTLCommandBuffer to receive the encoded kernel.
 *
 *  @param      inputMatrix     A valid MPSMatrix object which specifies the input array.
 *
 *  @param      biasVector      A valid MPSVector object which specifies the bias values, or
 *                              a null object to indicate that no bias is to be applied.
 *
 *  @param      resultMatrix    A valid MPSMatrix object which specifies the output array.
 *
 *  @discussion Encodes the operation to the specified command buffer.  resultMatrix
 *              must be large enough to hold a
 *                  MIN(sourceNumberOfFeatureVectors, inputMatrix.rows - sourceMatrixOrigin.x)
 *                  x
 *                  MIN(inputMatrix.columns - sourceMatrixOrigin.y, sourceInputFeatureChannels) array.
 *
 *              The bias vector must contain at least
 *                  MIN(inputMatrix.columns - sourceMatrixOrigin.y, sourceInputFeatureChannels) elements.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  inputMatrix: (MPSMatrix * __nonnull) inputMatrix
                   biasVector: (MPSVector * __nullable) biasVector
                 resultMatrix: (MPSMatrix * __nonnull) resultMatrix
MPS_SWIFT_NAME(encode(commandBuffer:inputMatrix:biasVector:resultMatrix:));

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSMatrixNeuron
 *  @param      device      The MTLDevice on which to make the MPSMatrixNeuron object.
 *  @return     A new MPSMatrixNeuron object, or nil if failure.
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


@end // MPSMatrixNeuron
    

/*!
 *  @class      MPSMatrixNeuronGradient
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A neuron gradient activation kernel that operates on matrices.
 *
 *  @discussion A MPSMatrixNeuronGradient object computes the results of backpropagating
 *              the gradients of a loss function with respect to the outputs of an
 *              MPSMatrixNeuron object.  The corresponding properties and data used by
 *              the MPSMatrixNeuronGradient object should correspond to those used by
 *              the forward MPSMatrixNeuron object for which the gradient is being computed.
 *
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface MPSMatrixNeuronGradient : MPSMatrixBinaryKernel

/*! @property   sourceNumberOfFeatureVectors
 *
 *  @discussion The number of input vectors which make up the input array.
 */
@property (readwrite, nonatomic) NSUInteger sourceNumberOfFeatureVectors;

/*! @property   sourceInputFeatureChannels
 *
 *  @discussion The number of feature channels in the input vectors.
 */
@property (readwrite, nonatomic) NSUInteger sourceInputFeatureChannels;

/*! @property   alpha
 *
 *  @discussion The scale factor to apply to the input.
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
 *              use appropriate setter functions.  An MPSMatrixNeuron kernel is initialized
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

/*!
 *  @abstract   Add per output value neuron parameters A for PReLu neuron activation functions.
 *
 *  @discussion This method sets the neuron to PReLU, zeros parameters A and B and sets the per output value
 *              neuron parameters A to an array containing a unique value of A for each output value.
 *
 *              If the neuron function is f(v,a,b), it will apply
 *
 *                     resultMatrix(i, j) = f( input(i, j), A[j], B[j] )
 *                  where j in [0, sourceInputFeatureChannels]
 *
 *              See https://arxiv.org/pdf/1502.01852.pdf for details.
 *
 *              All other neuron types, where parameter A
 *              and parameter B are shared across output values must be set using
 *              -setNeuronType:parameterA:parameterB:
 *
 *  @param      A       An array containing float values for neuron parameter A.
 *                      Number of entries must be equal to MIN(inputMatrix.columns - sourceMatrixOrigin.y, sourceInputFeatureChannels)
 */
-(void) setNeuronToPReLUWithParametersA: (NSData* __nonnull) A;

-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
NS_DESIGNATED_INITIALIZER;

/*!
 *  @abstract   Encode a MPSMatrixNeuronGradient object to a command buffer and compute
 *              its gradient with respect to its input data.
 *
 *  @param      commandBuffer               The commandBuffer on which to encode the operation.
 *
 *  @param      gradientMatrix              A matrix whose values represent the gradient of a
 *                                          loss function with respect to the results of a forward
 *                                          MPSMatrixNeuron operation.
 *
 *  @param      inputMatrix                 A matrix containing the inputs to a forward MPSMatrixNeuron
 *                                          operation for which the gradient values are to be computed.
 *
 *  @param      biasVector                  A vector containing the bias terms.
 *
 *  @param      resultGradientForDataMatrix The matrix containing the resulting gradient values.
 *
 *  @param      resultGradientForBiasVector If non-NULL the vector containing gradients for the bias
 *                                          terms.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
               gradientMatrix: (MPSMatrix * __nonnull) gradientMatrix
                  inputMatrix: (MPSMatrix * __nonnull) inputMatrix
                   biasVector: (MPSVector * __nullable) biasVector
  resultGradientForDataMatrix: (MPSMatrix * __nonnull) resultGradientForDataMatrix
  resultGradientForBiasVector: (MPSVector * __nullable) resultGradientForBiasVector;

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSMatrixNeuronGradient
 *  @param      device      The MTLDevice on which to make the MPSMatrixNeuronGradient object.
 *  @return     A new MPSMatrixNeuronGradient object, or nil if failure.
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

@end // MPSMatrixNeuronGradient

    
#ifdef __cplusplus
}
#endif
#endif /* MPSMatrixNeuron_h */

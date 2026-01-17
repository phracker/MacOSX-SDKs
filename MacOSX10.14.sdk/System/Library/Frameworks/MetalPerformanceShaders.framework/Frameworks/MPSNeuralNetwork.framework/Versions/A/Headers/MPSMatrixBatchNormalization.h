/*!
 *  @header MPSMatrixBatchNormalization.h
 *  @framework MetalPerformanceShaders.framework
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 *  @abstract Batch normalization of arrays stored as MPSMatrix objects.
 */


#ifndef MPSMatrixBatchNormalization_h
#define MPSMatrixBatchNormalization_h

#include <MPSNeuralNetwork/MPSCNNNeuronType.h>
#include <MPSMatrix/MPSMatrix.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @class      MPSMatrixBatchNormalization
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   Applies a batch normalization to a matrix.
 *
 *  @discussion A MPSMatrixBatchNormalization object computes the batch normalization
 *              of a collection of feature vectors stored in an MPSMatrix.
 *
 *              Feature vectors are stored in a row of the supplied input matrix and the
 *              normalization is performed along columns:
 *
 *                  y[i,j] = gamma[j] * (x[i,j] - mean(x[:,j])) / (variance(x[:,j]) + epsilon) + beta[j]
 *
 *              where gamma and beta are supplied weight and bias factors and epsilon is a small value added
 *              to the variance.
 *
 *              Optionally a neuron activation function may be applied to the result.
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.14), ios(12.0), tvos(12.0))
@interface MPSMatrixBatchNormalization : MPSMatrixUnaryKernel

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


/*! @property   epsilon
 *
 *  @discussion A small value to add to the variance when normalizing the inputs.  Defaults
 *              to FLT_MIN upon initialization.
 */
@property (readwrite, nonatomic) float epsilon;

/*! @property   computeStatistics
 *
 *  @discussion If YES the batch statistics will be computed prior to performing the normalization.
 *              Otherwise the provided statistics will be used.  Defaults to NO at initialization
 *              time.
 */
@property (readwrite, nonatomic) BOOL computeStatistics;

/*!
 *  @abstract   Specifies a neuron activation function to be used.
 *
 *  @discussion This method can be used to add a neuron activation funtion of given type with
 *              associated scalar parameters A, B, and C that are shared across all output values.
 *              Note that this method can only be used to specify neurons which are specified by three (or fewer)
 *              parameters shared across all output values (or channels, in CNN nomenclature). It is an error to call
 *              this method for neuron activation functions like MPSCNNNeuronTypePReLU,
 *              which require per-channel parameter values.  An MPSMatrixNeuron kernel is initialized
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
 *  @abstract   Encode a MPSMatrixBatchNormalization object to a command buffer.
 *
 *  @param      commandBuffer       A valid MTLCommandBuffer to receive the encoded kernel.
 *
 *  @param      inputMatrix         A valid MPSMatrix object which specifies the input array.
 *
 *  @param      meanVector          A valid MPSVector object containing batch mean values to be used
 *                                  to normalize the inputs if computeStatistics is NO.  If
 *                                  computeStatistics is YES the resulting batch mean values
 *                                  will be returned in this array.
 *
 *  @param      varianceVector      A valid MPSVector object containing batch variance values to be used
 *                                  to normalize the inputs if computeStatistics is NO.  If
 *                                  computeStatistics is YES the resulting batch variance values
 *                                  will be returned in this array.
 *
 *  @param      gammaVector         A valid MPSVector object which specifies the gamma terms, or
 *                                  a null object to indicate that no scaling is to be applied.
 *
 *  @param      betaVector          A valid MPSVector object which specifies the beta terms, or
 *                                  a null object to indicate that no values are to be added.
 *
 *  @param      resultMatrix        A valid MPSMatrix object which specifies the output array.
 *
 *  @discussion Encodes the operation to the specified command buffer.  resultMatrix
 *              must be large enough to hold a
 *                  MIN(sourceNumberOfFeatureVectors, inputMatrix.rows - sourceMatrixOrigin.x)
 *                  x
 *                  MIN(inputMatrix.columns - sourceMatrixOrigin.y, sourceInputFeatureChannels) array.
 *
 *              Let numChannels = MIN(inputMatrix.columns - sourceMatrixOrigin.y, sourceInputFeatureChannels)
 *
 *              The gamma, beta, mean, and variance vectors must contain at least numChannels elements.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
                  inputMatrix: (MPSMatrix * __nonnull) inputMatrix
                   meanVector: (MPSVector * __nonnull) meanVector
               varianceVector: (MPSVector * __nonnull) varianceVector
                  gammaVector: (MPSVector * __nullable) gammaVector
                   betaVector: (MPSVector * __nullable) betaVector
                 resultMatrix: (MPSMatrix * __nonnull) resultMatrix
MPS_SWIFT_NAME(encode(commandBuffer:inputMatrix:meanVector:varianceVector:gammaVector:betaVector:resultMatrix:));

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSMatrixBatchNormalization object.
 *  @param      device      The MTLDevice on which to make the MPSMatrixBatchNormalization object.
 *  @return     A new MPSMatrixBatchNormalization object, or nil if failure.
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

@end // MPSMatrixBatchNormalization
    

/*!
 *  @class      MPSMatrixBatchNormalizationGradient
 *
 *  @dependency This depends on Metal.framework.
 *
 *  @abstract   A kernel to compute the gradient of the batch normalization operation.
 *
 *  @discussion A MPSMatrixBatchNormalizationGradient object computes the results of backpropagating
 *              the gradients of a loss function with respect to the outputs of an
 *              MPSMatrixBatchNormalization object.  The corresponding properties and data used by
 *              the MPSMatrixBatchNormalizationGradient object should correspond to those used by
 *              the forward MPSMatrixBatchNormalization object for which the gradient is being computed.
 *
 *
 */
MPS_CLASS_AVAILABLE_STARTING( macos(10.14), ios(12.0), tvos(12.0))
@interface MPSMatrixBatchNormalizationGradient : MPSMatrixBinaryKernel

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

/*! @property   epsilon
 *
 *  @discussion A small term added to the variance when normalizing the input.
 */
@property (readwrite, nonatomic) float epsilon;

/*!
 *  @abstract   Specifies a neuron activation function to be used.
 *
 *  @discussion This method can be used to add a neuron activation funtion of given type with
 *              associated scalar parameters A, B, and C that are shared across all output values.
 *              Note that this method can only be used to specify neurons which are specified by three (or fewer)
 *              parameters shared across all output values (or channels, in CNN nomenclature). It is an error to call
 *              this method for neuron activation functions like MPSCNNNeuronTypePReLU,
 *              which require per-channel parameter values. An MPSMatrixBatchNormalizationGradient kernel is initialized
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
 *  @abstract   Encode a MPSMatrixBatchNormalizationGradient object to a command buffer and compute
 *              its gradient with respect to its input data.
 *
 *  @param      commandBuffer                   The commandBuffer on which to encode the operation.
 *
 *  @param      gradientMatrix                  A matrix whose values represent the gradient of a
 *                                              loss function with respect to the results of a forward
 *                                              MPSMatrixBatchNormalization operation.
 *
 *  @param      inputMatrix                     A matrix containing the inputs to a forward MPSMatrixBatchNormalization
 *                                              operation for which the gradient values are to be computed.
 *
 *  @param      meanVector                      A vector containing the batch mean values.  Should contain either the specified
 *                                              values used to compute the forward result, or the computed values resulting from
 *                                              the forward kernel execution.
 *
 *  @param      varianceVector                  A vector containing the batch variance values.  Should contain either the specified
 *                                              values used to compute the forward result, or the computed values resulting from
 *                                              the forward kernel execution.
 *
 *  @param      gammaVector                     A vector containing the gamma terms.  Should be the same values as used
 *                                              when computing the forward result.
 *
 *  @param      betaVector                      A vector containing the beta terms.  Should be the same values as used when
 *                                              computing the forward result.
 *
 *  @param      resultGradientForDataMatrix     The matrix containing the resulting gradient values.
 *
 *  @param      resultGradientForGammaVector    If non-NULL the vector containing gradients for the gamma
 *                                              terms.
 *
 *  @param      resultGradientForBetaVector     If non-NULL the vector containing gradients for the beta
 *                                              terms.
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>) commandBuffer
               gradientMatrix: (MPSMatrix * __nonnull) gradientMatrix
                  inputMatrix: (MPSMatrix * __nonnull) inputMatrix
                   meanVector: (MPSVector * __nonnull) meanVector
               varianceVector: (MPSVector * __nonnull) varianceVector
                  gammaVector: (MPSVector * __nullable) gammaVector
                   betaVector: (MPSVector * __nullable) betaVector
  resultGradientForDataMatrix: (MPSMatrix * __nonnull) resultGradientForDataMatrix
 resultGradientForGammaVector: (MPSVector * __nullable) resultGradientForGammaVector
  resultGradientForBetaVector: (MPSVector * __nullable) resultGradientForBetaVector;

/*! @abstract NSSecureCoding compatability
 *  @discussion See @ref MPSKernel#initWithCoder.
 *  @param      aDecoder    The NSCoder subclass with your serialized MPSMatrixBatchNormalizationGradient
 *  @param      device      The MTLDevice on which to make the MPSMatrixBatchNormalizationGradient object.
 *  @return     A new MPSMatrixBatchNormalizationGradient object, or nil if failure.
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

@end // MPSMatrixBatchNormalizationGradient

    
#ifdef __cplusplus
}
#endif
#endif /* MPSMatrixBatchNormalization_h */


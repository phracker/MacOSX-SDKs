//
//  MPSNNOptimizers.h
//  MPSNeuralNetwork
//
//  Created by Dhruv Saksena on 2/15/18.
//  Copyright © 2018 Apple. All rights reserved.
//


#ifndef MPSNNOptimizers_h
#define MPSNNOptimizers_h

#import <MPSCore/MPSKernel.h>
#import <MPSMatrix/MPSMatrixTypes.h>
#import <MPSNeuralNetwork/MPSCNNConvolution.h>
#import <MPSNeuralNetwork/MPSCNNBatchNormalization.h>
#import <MPSNeuralNetwork/MPSCNNInstanceNormalization.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  Regularization is a technique usually used to avoid overfitting to avoid updating the weights once they become to big.
 *  To achieve this the user adds the regularization function R(weight) to the loss of the training forward pass, and since the objective is to
 *  minimize this loss we effectively keep the weight from getting too big.
 *
 *  It can be applied to all network parameters like bias, weights, gamma and beta.
 *
 *  Link to more info on regularization:
 *  https://en.wikipedia.org/wiki/Regularization_(mathematics)
 *
 */
#if defined(DOXYGEN)
    typedef enum MPSNNRegularizationType
#else
    typedef NS_ENUM(NSUInteger, MPSNNRegularizationType)
#endif
    {
        MPSNNRegularizationTypeNone MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)) MPS_SWIFT_NAME(None) = 0,
        /*!
         *  Apply L1 regularization. L1 norm of weights, will be considered to be added to the loss to be minimized.
         *  the gradient of the regularization loss turns to be 1 scaled with regularizationScale,
         *  so we add that to the incoming gradient of value.
         */
        MPSNNRegularizationTypeL1 MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)) = 1,
        /*!
         *  Apply L2 regularization. L2 norm of weights, will be considered to be added to the loss to be minimized.
         *  the gradient of the regularization loss turns to be the original value scaled with regularizationScale,
         *  so we add that to the incoming gradient of value.
         */
        MPSNNRegularizationTypeL2 MPS_ENUM_AVAILABLE_STARTING( macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0)) = 2,
    } NS_ENUM_AVAILABLE(10_14, 12_0)
#if defined(DOXYGEN)
    MPSNNRegularizationType
#endif
    ;


/*!
 *  @class      MPSNNOptimizerDescriptor
 *  @discussion The MPSNNOptimizerDescriptor base class. Optimizers are generally used to update trainable neural network parameters.
 *              Users are usually expected to call these MPSKernels from the update methods on their Convolution or BatchNormalization data sources.
 *
 *              Before the gradient is used to update the original value, some preprocessing occurs on each gradient where it is scaled or clipped
 *              If regularization is chosen the appropriate regularization loss gradient is added to the value gradient.
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface  MPSNNOptimizerDescriptor : NSObject

/*! @property   learningRate
 *  @abstract   The learningRate at which we update values
 *  @discussion The default value is 0.001f
 */
@property (readwrite, nonatomic) float learningRate;

/*! @property   gradientRescale
 *  @abstract   The gradientRescale at which we apply to incoming gradient values
 *  @discussion The default value is 1.0
 */
@property (readwrite, nonatomic) float gradientRescale;

/*! @property   applyGradientClipping
 *  @abstract   A bool which decides if gradient will be clipped
 *  @discussion The default value is NO
 */
@property (readwrite, nonatomic) BOOL applyGradientClipping;

/*! @property   gradientClipMax
 *  @abstract   The maximum value at which incoming gradient will be clipped before rescaling, applyGradientClipping must be true
 */
@property (readwrite, nonatomic) float gradientClipMax;

/*! @property   gradientClipMin
 *  @abstract   The minimum value at which incoming gradient will be clipped before rescaling, applyGradientClipping must be true
 */
@property (readwrite, nonatomic) float gradientClipMin;

/*! @property   regularizationScale
 *  @abstract   The regularizationScale at which we apply L1 or L2 regularization, it gets ignored if regularization is None
 *  @discussion The default value is 0.0
 */
@property (readwrite, nonatomic) float regularizationScale;

/*! @property   regularizationType
 *  @abstract   The regularizationType which we apply.
 *  @discussion The default value is MPSRegularizationTypeNone
 */
@property (readwrite, nonatomic) MPSNNRegularizationType regularizationType;

/*
 *  @abstract   Initialization for the MPSNNOptimizerDescriptor object, no gradient clipping would be applied
 *
 *  @param      learningRate               The learningRate which will be applied
 *  @param      gradientRescale            The gradientRescale which will be applied
 *  @param      regularizationType         The regularizationType which will be applied
 *  @param      regularizationScale        The regularizationScale which will be applied
 *
 *  @return     A valid MPSNNOptimizerDescriptor object or nil, if failure.
 */
-(nonnull instancetype) initWithLearningRate: (float) learningRate
                             gradientRescale: (float) gradientRescale
                          regularizationType: (MPSNNRegularizationType) regularizationType
                         regularizationScale: (float) regularizationScale;


/*
 *  @abstract   Initialization for the MPSNNOptimizerDescriptor object
 *
 *  @param      learningRate               The learningRate which will be applied
 *  @param      gradientRescale            The gradientRescale which will be applied
 *  @param      applyGradientClipping      The BOOL which sets if gradientClipping would be applied to the gradient
 *  @param      gradientClipMax            The gradientClipMax which will be applied
 *  @param      gradientClipMin            The gradientClipMin which will be applied
 *  @param      regularizationType         The regularizationType which will be applied
 *  @param      regularizationScale        The regularizationScale which will be applied
 *
 *  @return     A valid MPSNNOptimizerDescriptor object or nil, if failure.
 */
-(nonnull instancetype) initWithLearningRate: (float) learningRate
                             gradientRescale: (float) gradientRescale
                       applyGradientClipping: (BOOL) applyGradientClipping
                             gradientClipMax: (float) gradientClipMax
                             gradientClipMin: (float) gradientClipMin
                          regularizationType: (MPSNNRegularizationType) regularizationType
                         regularizationScale: (float) regularizationScale;


/*
 *  @abstract   Creates a descriptor on autoreleaspool for the MPSNNOptimizerDescriptor object, no gradient clipping would be applied
 *
 *  @param      learningRate               The learningRate which will be applied
 *  @param      gradientRescale            The gradientRescale which will be applied
 *  @param      regularizationType         The regularizationType which will be applied
 *  @param      regularizationScale        The regularizationScale which will be applied
 *
 *  @return     A valid MPSNNOptimizerDescriptor object or nil, if failure.
 */
+(nonnull instancetype) optimizerDescriptorWithLearningRate: (float) learningRate
                                            gradientRescale: (float) gradientRescale
                                         regularizationType: (MPSNNRegularizationType) regularizationType
                                        regularizationScale: (float) regularizationScale;

/*
 *  @abstract   Creates a descriptor on autoreleaspool for the MPSNNOptimizerDescriptor object
 *
 *  @param      learningRate               The learningRate which will be applied
 *  @param      gradientRescale            The gradientRescale which will be applied
 *  @param      applyGradientClipping      The BOOL which sets if gradientClipping would be applied to the gradient
 *  @param      gradientClipMax            The gradientClipMax which will be applied
 *  @param      gradientClipMin            The gradientClipMin which will be applied
 *  @param      regularizationType         The regularizationType which will be applied
 *  @param      regularizationScale        The regularizationScale which will be applied
 *
 *  @return     A valid MPSNNOptimizerDescriptor object or nil, if failure.
 */
+(nonnull instancetype) optimizerDescriptorWithLearningRate: (float) learningRate
                                            gradientRescale: (float) gradientRescale
                                      applyGradientClipping: (BOOL) applyGradientClipping
                                            gradientClipMax: (float) gradientClipMax
                                            gradientClipMin: (float) gradientClipMin
                                         regularizationType: (MPSNNRegularizationType) regularizationType
                                        regularizationScale: (float) regularizationScale;

@end  /* MPSNNOptimizerDescriptor */





/*!
 *  @class      MPSNNOptimizer
 *  @discussion The MPSNNOptimizer base class, use one of the child classes, not to be directly used. Optimizers are generally used to update trainable neural network parameters.
 *              Users are usually expected to call these MPSKernels from the update methods on their Convolution or BatchNormalization data sources.
 *
 *              Before the gradient is used to update the original value, some preprocessing occurs on each gradient where it is scaled or clipped
 *              If regularization is chosen the appropriate regularization loss gradient is added to the value gradient.
 *
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface  MPSNNOptimizer : MPSKernel

/*! @property   learningRate
 *  @abstract   The learningRate at which we update values
 *  @discussion The default value is 1e-3
 */
@property (readonly, nonatomic) float learningRate;

/*! @property   gradientRescale
 *  @abstract   The gradientRescale at which we apply to incoming gradient values
 *  @discussion The default value is 1.0
 */
@property (readonly, nonatomic) float gradientRescale;

/*! @property   applyGradientClipping
 *  @abstract   A bool which decides if gradient will be clipped
 *  @discussion The default value is NO
 */
@property (readwrite, nonatomic) BOOL applyGradientClipping;

/*! @property   gradientClipMax
 *  @abstract   The maximum value at which incoming gradient will be clipped before rescaling, applyGradientClipping must be true
 */
@property (readonly, nonatomic) float gradientClipMax;

/*! @property   gradientClipMin
 *  @abstract   The minimum value at which incoming gradient will be clipped before rescaling, applyGradientClipping must be true
 */
@property (readonly, nonatomic) float gradientClipMin;

/*! @property   regularizationScale
 *  @abstract   The regularizationScale at which we apply L1 or L2 regularization, it gets ignored if regularization is None
 *  @discussion The default value is 0.0
 */
@property (readonly, nonatomic) float regularizationScale;

/*! @property   regularizationType
 *  @abstract   The regularizationType which we apply.
 *  @discussion The default value is MPSRegularizationTypeNone
 */
@property (readonly, nonatomic) MPSNNRegularizationType regularizationType;


/*
 * You must use one of the sub-classes of MPSNNOptimizer.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_UNAVAILABLE;

-(void) setLearningRate: (float) newLearningRate;

@end  /* MPSNNOptimizer */








/*!
 *  @class      MPSNNOptimizerStochasticGradientDescent
 *  @discussion The MPSNNOptimizerStochasticGradientDescent performs a gradient descent with an optional momentum Update
 *              RMSProp is also known as root mean square propagation.
 *
 *              useNestrov == NO:
 *                  m[t]     = momentumScale * m[t-1] + learningRate * g
 *                  variable = variable - m[t]
 *
 *              useNestrov == YES:
 *                  m[t]     = momentumScale * m[t-1] + g
 *                  variable = variable - (learningRate * (g + m[t] * momentumScale))
 *
 *
 *              where,
 *                g    is gradient of error wrt variable
 *                m[t] is momentum of gradients it is a state we keep updating every update iteration
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface  MPSNNOptimizerStochasticGradientDescent : MPSNNOptimizer


/*! @property   momentumScale
 *  @abstract   The momentumScale at which we update momentum for values array
 *  @discussion Default value is 0.0
 *
 */
@property (readonly, nonatomic) float momentumScale;

/*! @property   useNestrovMomentum
 *  @abstract   Nestrov momentum is considered an improvement on the usual momentum update
 *  @discussion Default value is NO
 *
 */
@property (readonly, nonatomic) BOOL useNestrovMomentum;

/*
 * Use one of the other init methods.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_UNAVAILABLE;


/*!
 *  @abstract   Convenience initialization for the momentum update
 *
 *  @param      device                     The device on which the kernel will execute.
 *  @param      learningRate               The learningRate which will be applied
 *
 *  @return     A valid MPSNNOptimizerStochasticGradientDescent object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                          learningRate: (float) learningRate;

/*!
 *  @abstract   Full initialization for the momentum update
 *
 *  @param      device                     The device on which the kernel will execute.
 *  @param      momentumScale              The momentumScale to update momentum for values array
 *  @param      useNestrovMomentum         Use the Nestrov style momentum update
 *  @param      optimizerDescriptor        The optimizerDescriptor which will have a bunch of properties to be applied
 *
 *
 *  @return     A valid MPSNNOptimizerMomentum object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                         momentumScale: (float) momentumScale
                    useNestrovMomentum: (BOOL) useNestrovMomentum
                   optimizerDescriptor: (nonnull MPSNNOptimizerDescriptor *) optimizerDescriptor;

/*!
 *  @abstract   Encode an MPSNNOptimizerStochasticGradientDescent object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      inputGradientVector        A valid MPSVector object which specifies the input vector of gradients for this update.
 *  @param      inputValuesVector          A valid MPSVector object which specifies the input vector of values to be updated.
 *  @param      inputMomentumVector        A valid MPSVector object which specifies the gradient momentum vector which will
 *                                         be updated and overwritten.
 *  @param      resultValuesVector         A valid MPSVector object which specifies the resultValues vector which will
 *                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *
 *
 *              useNestrov == NO:
 *                  m[t]     = momentumScale * m[t-1] + learningRate * g
 *                  variable = variable - m[t]
 *
 *              useNestrov == YES:
 *                  m[t]     = momentumScale * m[t-1] + g
 *                  variable = variable - (learningRate * (g + m[t] * momentumScale))
 *
 *              inputMomentumVector == nil
 *                  variable = variable - (learningRate * g)
 *
 *              where,
 *                g    is gradient of error wrt variable
 *                m[t] is momentum of gradients it is a state we keep updating every update iteration
 *
 *
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)  commandBuffer
          inputGradientVector: (nonnull MPSVector *) inputGradientVector
            inputValuesVector: (nonnull MPSVector *) inputValuesVector
          inputMomentumVector: (nullable MPSVector *) inputMomentumVector
           resultValuesVector: (nonnull MPSVector *) resultValuesVector
MPS_SWIFT_NAME(encode(commandBuffer:inputGradientVector:inputValuesVector:inputMomentumVector:resultValuesVector:));

-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)  commandBuffer
          inputGradientMatrix: (nonnull MPSMatrix *) inputGradientMatrix
            inputValuesMatrix: (nonnull MPSMatrix *) inputValuesMatrix
          inputMomentumMatrix: (nullable MPSMatrix *) inputMomentumMatrix
           resultValuesMatrix: (nonnull MPSMatrix *) resultValuesMatrix
MPS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
MPS_SWIFT_NAME(encode(commandBuffer:inputGradientMatrix:inputValuesMatrix:inputMomentumMatrix:resultValuesMatrix:));


/*!
 *  @abstract   Encode an MPSNNOptimizerStochasticGradientDescent object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      convolutionGradientState   A valid MPSCNNConvolutionGradientState object which specifies the input state with gradients for this update.
 *  @param      convolutionSourceState     A valid MPSCNNConvolutionWeightsAndBiasesState object which specifies the input state with values to be updated.
 *  @param      inputMomentumVectors       An array MPSVector object which specifies the gradient momentum vectors which will
 *                                         be updated and overwritten. The index 0 corresponds to weights, index 1 corresponds to biases, array can be of
 *                                         size 1 in which case biases won't be updated
 *  @param      resultState                A valid MPSCNNConvolutionWeightsAndBiasesState object which specifies the resultValues state which will
 *                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *
 *
 *              useNestrov == NO:
 *                  m[t]     = momentumScale * m[t-1] + learningRate * g
 *                  variable = variable - m[t]
 *
 *              useNestrov == YES:
 *                  m[t]     = momentumScale * m[t-1] + g
 *                  variable = variable - (learningRate * (g + m[t] * momentumScale))
 *
 *              inputMomentumVector == nil
 *                  variable = variable - (learningRate * g)
 *
 *              where,
 *                g    is gradient of error wrt variable
 *                m[t] is momentum of gradients it is a state we keep updating every update iteration
 *
 *
 */
-(void) encodeToCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
     convolutionGradientState: (MPSCNNConvolutionGradientState* __nonnull) convolutionGradientState
       convolutionSourceState: (MPSCNNConvolutionWeightsAndBiasesState* __nonnull) convolutionSourceState
         inputMomentumVectors: (nullable NSArray<MPSVector *>*) inputMomentumVectors
                  resultState: (nonnull MPSCNNConvolutionWeightsAndBiasesState *) resultState
MPS_SWIFT_NAME(encode(commandBuffer:convolutionGradientState:convolutionSourceState:inputMomentumVectors:resultState:));

/*!
 *  @abstract   Encode an MPSNNOptimizerStochasticGradientDescent object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer                              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      batchNormalizationState                    A valid MPSCNNBatchNormalizationState object which specifies the input state with gradients and original gamma/beta for this update.
 *  @param      inputMomentumVectors                       An array MPSVector object which specifies the gradient momentum vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to gamma, index 1 corresponds to beta, array can be of
 *                                                         size 1 in which case beta won't be updated
 *  @param      resultState                                A valid MPSCNNNormalizationGammaAndBetaState object which specifies the resultValues state which will
 *                                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *
 *
 *              useNestrov == NO:
 *                  m[t]     = momentumScale * m[t-1] + learningRate * g
 *                  variable = variable - m[t]
 *
 *              useNestrov == YES:
 *                  m[t]     = momentumScale * m[t-1] + g
 *                  variable = variable - (learningRate * (g + m[t] * momentumScale))
 *
 *              inputMomentumVector == nil
 *                  variable = variable - (learningRate * g)
 *
 *              where,
 *                g    is gradient of error wrt variable
 *                m[t] is momentum of gradients it is a state we keep updating every update iteration
 *
 *
 */
-(void) encodeToCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
      batchNormalizationState: (MPSCNNBatchNormalizationState* __nonnull) batchNormalizationState
         inputMomentumVectors: (nullable NSArray<MPSVector *>*) inputMomentumVectors
                  resultState: (nonnull MPSCNNNormalizationGammaAndBetaState *) resultState
MPS_SWIFT_NAME(encode(commandBuffer:batchNormalizationState:inputMomentumVectors:resultState:));

/*!
 *  @abstract   Encode an MPSNNOptimizerStochasticGradientDescent object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer                              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      batchNormalizationGradientState            A valid MPSCNNBatchNormalizationState object which specifies the input state with gradients for this update.
 *  @param      batchNormalizationSourceState              A valid MPSCNNBatchNormalizationState object which specifies the input state with original gamma/beta for this update.
 *  @param      inputMomentumVectors                       An array MPSVector object which specifies the gradient momentum vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to gamma, index 1 corresponds to beta, array can be of
 *                                                         size 1 in which case beta won't be updated
 *  @param      resultState                                A valid MPSCNNNormalizationGammaAndBetaState object which specifies the resultValues state which will
 *                                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *
 *
 *              useNestrov == NO:
 *                  m[t]     = momentumScale * m[t-1] + learningRate * g
 *                  variable = variable - m[t]
 *
 *              useNestrov == YES:
 *                  m[t]     = momentumScale * m[t-1] + g
 *                  variable = variable - (learningRate * (g + m[t] * momentumScale))
 *
 *              inputMomentumVector == nil
 *                  variable = variable - (learningRate * g)
 *
 *              where,
 *                g    is gradient of error wrt variable
 *                m[t] is momentum of gradients it is a state we keep updating every update iteration
 *
 *
 */
-(void)            encodeToCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
         batchNormalizationGradientState: (MPSCNNBatchNormalizationState* __nonnull) batchNormalizationGradientState
           batchNormalizationSourceState: (MPSCNNBatchNormalizationState* __nonnull) batchNormalizationSourceState
                    inputMomentumVectors: (nullable NSArray<MPSVector *>*) inputMomentumVectors
                             resultState: (nonnull MPSCNNNormalizationGammaAndBetaState *) resultState
MPS_SWIFT_NAME(encode(commandBuffer:batchNormalizationGradientState:batchNormalizationSourceState:inputMomentumVectors:resultState:));




@end  /* MPSNNOptimizerStochasticGradientDescent */









/*!
 *  @class      MPSNNOptimizerRMSProp
 *  @discussion The MPSNNOptimizerRMSProp performs an RMSProp Update
 *              RMSProp is also known as root mean square propagation.
 *
 *              s[t]     = decay * s[t-1] + (1 - decay) * (g ^ 2)
 *              variable = variable - learningRate * g / (sqrt(s[t]) + epsilon)
 *
 *              where,
 *                g    is gradient of error wrt variable
 *                s[t] is weighted sum of squares of gradients
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface  MPSNNOptimizerRMSProp : MPSNNOptimizer


/*! @property   decay
 *  @abstract   The decay at which we update sumOfSquares
 *  @discussion Default value is 0.9
 *
 */
@property (readonly, nonatomic) double decay;

/*! @property   epsilon
 *  @abstract   The epsilon at which we update values
 *  @discussion This value is usually used to ensure to avoid divide by 0, default value is 1e-8
 *
 */
@property (readonly, nonatomic) float epsilon;

/*
 * Use one of the other init methods.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_UNAVAILABLE;


/*!
 *  @abstract   Convenience initialization for the RMSProp update
 *
 *  @param      device                     The device on which the kernel will execute.
 *  @param      learningRate               The learningRate which will be applied
 *
 *  @return     A valid MPSNNOptimizerRMSProp object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                          learningRate: (float) learningRate;

/*!
 *  @abstract   Full initialization for the rmsProp update
 *
 *  @param      device                     The device on which the kernel will execute.
 *  @param      decay                      The decay to update sumOfSquares
 *  @param      epsilon                    The epsilon which will be applied
 *  @param      optimizerDescriptor        The optimizerDescriptor which will have a bunch of properties to be applied
 *
 *
 *  @return     A valid MPSNNOptimizerRMSProp object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                 decay: (double) decay
                               epsilon: (float) epsilon
                   optimizerDescriptor: (nonnull MPSNNOptimizerDescriptor *) optimizerDescriptor;

/*!
 *  @abstract   Encode an MPSNNOptimizerRMSProp object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      inputGradientVector        A valid MPSVector object which specifies the input vector of gradients for this update.
 *  @param      inputValuesVector          A valid MPSVector object which specifies the input vector of values to be updated.
 *  @param      inputSumOfSquaresVector    A valid MPSVector object which specifies the gradient velocity vector which will
 *                                         be updated and overwritten.
 *  @param      resultValuesVector         A valid MPSVector object which specifies the resultValues vector which will
 *                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *
 *
 *              s[t]     = decay * s[t-1] + (1 - decay) * (g ^ 2)
 *              variable = variable - learningRate * g / (sqrt(s[t]) + epsilon)
 *
 *              where,
 *                g    is gradient of error wrt variable
 *                s[t] is weighted sum of squares of gradients
 *
 *
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)  commandBuffer
          inputGradientVector: (nonnull MPSVector *) inputGradientVector
            inputValuesVector: (nonnull MPSVector *) inputValuesVector
      inputSumOfSquaresVector: (nonnull MPSVector *) inputSumOfSquaresVector
           resultValuesVector: (nonnull MPSVector *) resultValuesVector
MPS_SWIFT_NAME(encode(commandBuffer:inputGradientVector:inputValuesVector:inputSumOfSquaresVector:resultValuesVector:));

-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)  commandBuffer
          inputGradientMatrix: (nonnull MPSMatrix *) inputGradientMatrix
            inputValuesMatrix: (nonnull MPSMatrix *) inputValuesMatrix
      inputSumOfSquaresMatrix: (nonnull MPSMatrix *) inputSumOfSquaresMatrix
           resultValuesMatrix: (nonnull MPSMatrix *) resultValuesMatrix
MPS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
MPS_SWIFT_NAME(encode(commandBuffer:inputGradientMatrix:inputValuesMatrix:inputSumOfSquaresMatrix:resultValuesMatrix:));



/*!
 *  @abstract   Encode an MPSNNOptimizerRMSProp object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      convolutionGradientState   A valid MPSCNNConvolutionGradientState object which specifies the input state with gradients for this update.
 *  @param      convolutionSourceState     A valid MPSCNNConvolutionWeightsAndBiasesState object which specifies the input state with values to be updated.
 *  @param      inputSumOfSquaresVectors   An array MPSVector object which specifies the gradient sumOfSquares vectors which will
 *                                         be updated and overwritten. The index 0 corresponds to weights, index 1 corresponds to biases, array can be of
 *                                         size 1 in which case biases won't be updated
 *  @param      resultState                A valid MPSCNNConvolutionWeightsAndBiasesState object which specifies the resultValues state which will
 *                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *
 *
 *              s[t]     = decay * s[t-1] + (1 - decay) * (g ^ 2)
 *              variable = variable - learningRate * g / (sqrt(s[t]) + epsilon)
 *
 *              where,
 *                g    is gradient of error wrt variable
 *                s[t] is weighted sum of squares of gradients
 *
 *
 */
-(void) encodeToCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
     convolutionGradientState: (MPSCNNConvolutionGradientState* __nonnull) convolutionGradientState
       convolutionSourceState: (MPSCNNConvolutionWeightsAndBiasesState* __nonnull) convolutionSourceState
     inputSumOfSquaresVectors: (nullable NSArray<MPSVector *>*) inputSumOfSquaresVectors
                  resultState: (nonnull MPSCNNConvolutionWeightsAndBiasesState *) resultState
MPS_SWIFT_NAME(encode(commandBuffer:convolutionGradientState:convolutionSourceState:inputSumOfSquaresVectors:resultState:));

/*!
 *  @abstract   Encode an MPSNNOptimizerRMSProp object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer                              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      batchNormalizationState                    A valid MPSCNNBatchNormalizationState object which specifies the input state with gradients and original gamma/beta for this update.
 *  @param      inputSumOfSquaresVectors                   An array MPSVector object which specifies the gradient sumOfSquares vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to gamma, index 1 corresponds to beta, array can be of
 *                                                         size 1 in which case beta won't be updated
 *  @param      resultState                                A valid MPSCNNNormalizationGammaAndBetaState object which specifies the resultValues state which will
 *                                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *
 *
 *              s[t]     = decay * s[t-1] + (1 - decay) * (g ^ 2)
 *              variable = variable - learningRate * g / (sqrt(s[t]) + epsilon)
 *
 *              where,
 *                g    is gradient of error wrt variable
 *                s[t] is weighted sum of squares of gradients
 *
 *
 */
-(void) encodeToCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
      batchNormalizationState: (MPSCNNBatchNormalizationState* __nonnull) batchNormalizationState
     inputSumOfSquaresVectors: (nullable NSArray<MPSVector *>*) inputSumOfSquaresVectors
                  resultState: (nonnull MPSCNNNormalizationGammaAndBetaState *) resultState
MPS_SWIFT_NAME(encode(commandBuffer:batchNormalizationState:inputSumOfSquaresVectors:resultState:));

/*!
 *  @abstract   Encode an MPSNNOptimizerRMSProp object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer                              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      batchNormalizationGradientState            A valid MPSCNNBatchNormalizationState object which specifies the input state with gradients for this update.
 *  @param      batchNormalizationSourceState              A valid MPSCNNBatchNormalizationState object which specifies the input state with original gamma/beta for this update.
 *  @param      inputSumOfSquaresVectors                   An array MPSVector object which specifies the gradient sumOfSquares vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to gamma, index 1 corresponds to beta, array can be of
 *                                                         size 1 in which case beta won't be updated
 *  @param      resultState                                A valid MPSCNNNormalizationGammaAndBetaState object which specifies the resultValues state which will
 *                                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *
 *
 *              s[t]     = decay * s[t-1] + (1 - decay) * (g ^ 2)
 *              variable = variable - learningRate * g / (sqrt(s[t]) + epsilon)
 *
 *              where,
 *                g    is gradient of error wrt variable
 *                s[t] is weighted sum of squares of gradients
 *
 *
 */
-(void)            encodeToCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
         batchNormalizationGradientState: (MPSCNNBatchNormalizationState* __nonnull) batchNormalizationGradientState
           batchNormalizationSourceState: (MPSCNNBatchNormalizationState* __nonnull) batchNormalizationSourceState
                inputSumOfSquaresVectors: (nullable NSArray<MPSVector *>*) inputSumOfSquaresVectors
                             resultState: (nonnull MPSCNNNormalizationGammaAndBetaState *) resultState
MPS_SWIFT_NAME(encode(commandBuffer:batchNormalizationGradientState:batchNormalizationSourceState:inputSumOfSquaresVectors:resultState:));

@end  /* MPSNNOptimizerRMSProp */









/*!
 *  @class      MPSNNOptimizerAdam
 *  @discussion The MPSNNOptimizerAdam performs an Adam Update
 *
 *              Initialization time
 *              m[0] = 0 (Initialize initial 1st moment vector aka momentum, user is responsible for this)
 *              v[0] = 0 (Initialize initial 2nd moment vector aka velocity, user is responsible for this)
 *              t    = 0 (Initialize timestep)
 *
 *              https://arxiv.org/abs/1412.6980
 *
 *              At update time:
 *              t = t + 1
 *              lr[t] = learningRate * sqrt(1 - beta2^t) / (1 - beta1^t)
 *
 *              m[t]     = beta1 * m[t-1] + (1 - beta1) * g
 *              v[t]     = beta2 * v[t-1] + (1 - beta2) * (g ^ 2)
 *              variable = variable - lr[t] * m[t] / (sqrt(v[t]) + epsilon)
 *
 *              where,
 *                g    is gradient of error wrt variable
 *                v[t] is velocity
 *                m[t] is momentum
 *
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface  MPSNNOptimizerAdam : MPSNNOptimizer

/*! @property   beta1
 *  @abstract   The beta1 at which we update values
 *  @discussion Default value is 0.9
 *
 */
@property (readonly, nonatomic) double beta1;

/*! @property   beta2
 *  @abstract   The beta2 at which we update values
 *  @discussion Default value is 0.999
 *
 */
@property (readonly, nonatomic) double beta2;

/*! @property   epsilon
 *  @abstract   The epsilon at which we update values
 *  @discussion This value is usually used to ensure to avoid divide by 0, default value is 1e-8
 *
 */
@property (readonly, nonatomic) float epsilon;

/*! @property   timeStep
 *  @abstract   Current timeStep for the update, number of times update has occurred
 *
 */
@property (readwrite, nonatomic) NSUInteger timeStep;

/*
 * Use one of the other init methods.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device     NS_UNAVAILABLE;


/*!
 *  @abstract   Convenience initialization for the adam update
 *
 *  @param      device                     The device on which the kernel will execute.
 *  @param      learningRate               The learningRate at which we will update values
 *
 *  @return     A valid MPSNNOptimizerAdam object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                          learningRate: (float) learningRate;

/*!
 *  @abstract   Full initialization for the adam update
 *
 *  @param      device                     The device on which the kernel will execute.
 *  @param      beta1                      The beta1 to update values
 *  @param      beta2                      The beta2 to update values
 *  @param      epsilon                    The epsilon at which we update values
 *  @param      timeStep                   The timeStep at which values will start updating
 *  @param      optimizerDescriptor        The optimizerDescriptor which will have a bunch of properties to be applied
 *
 *
 *  @return     A valid MPSNNOptimizerAdam object or nil, if failure.
 */
-(nonnull instancetype) initWithDevice: (nonnull id <MTLDevice>) device
                                 beta1: (double) beta1
                                 beta2: (double) beta2
                               epsilon: (float) epsilon
                              timeStep: (NSUInteger) timeStep
                   optimizerDescriptor: (nonnull MPSNNOptimizerDescriptor *) optimizerDescriptor;


/*!
 *  @abstract   Encode an MPSNNOptimizerAdam object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer          A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      inputGradientVector    A valid MPSVector object which specifies the input vector of gradients for this update.
 *  @param      inputValuesVector      A valid MPSVector object which specifies the input vector of values to be updated.
 *  @param      inputMomentumVector    A valid MPSVector object which specifies the gradient momentum vector which will
 *                                     be updated and overwritten.
 *  @param      inputVelocityVector    A valid MPSVector object which specifies the gradient velocity vector which will
 *                                     be updated and overwritten.
 *  @param      resultValuesVector     A valid MPSVector object which specifies the resultValues vector which will
 *                                     be updated and overwritten.
 *
 *  @discussion The following operations would be applied
 *
 *              t = t + 1
 *              lr[t] = learningRate * sqrt(1 - beta2^t) / (1 - beta1^t)
 *
 *              m[t]     = beta1 * m[t-1] + (1 - beta1) * g
 *              v[t]     = beta2 * v[t-1] + (1 - beta2) * (g ^ 2)
 *              variable = variable - lr[t] * m[t] / (sqrt(v[t]) + epsilon)
 *
 *
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)  commandBuffer
          inputGradientVector: (nonnull MPSVector *) inputGradientVector
            inputValuesVector: (nonnull MPSVector *) inputValuesVector
          inputMomentumVector: (nonnull MPSVector *) inputMomentumVector
          inputVelocityVector: (nonnull MPSVector *) inputVelocityVector
           resultValuesVector: (nonnull MPSVector *) resultValuesVector
MPS_SWIFT_NAME(encode(commandBuffer:inputGradientVector:inputValuesVector:inputMomentumVector:inputVelocityVector:resultValuesVector:));

-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)  commandBuffer
          inputGradientMatrix: (nonnull MPSMatrix *) inputGradientMatrix
            inputValuesMatrix: (nonnull MPSMatrix *) inputValuesMatrix
          inputMomentumMatrix: (nonnull MPSMatrix *) inputMomentumMatrix
          inputVelocityMatrix: (nonnull MPSMatrix *) inputVelocityMatrix
           resultValuesMatrix: (nonnull MPSMatrix *) resultValuesMatrix
MPS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
MPS_SWIFT_NAME(encode(commandBuffer:inputGradientMatrix:inputValuesMatrix:inputMomentumMatrix:inputVelocityMatrix:resultValuesMatrix:));


/*!
 *  @abstract   Encode an AMSGrad variant of MPSNNOptimizerAdam object to a command buffer to perform out of place update
 *  @param      commandBuffer          A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      inputGradientVector    A valid MPSVector object which specifies the input vector of gradients for this update.
 *  @param      inputValuesVector      A valid MPSVector object which specifies the input vector of values to be updated.
 *  @param      inputMomentumVector    A valid MPSVector object which specifies the gradient momentum vector which will
 *                                     be updated and overwritten.
 *  @param      inputVelocityVector    A valid MPSVector object which specifies the gradient velocity vector which will
 *                                     be updated and overwritten.
 *  @param      maximumVelocityVector  A valid MPSVector object which specifies the maximum velocity vector which will
 *                                     be updated and overwritten. May be nil, if nil then normal Adam optimizer behaviour is followed.
 *  @param      resultValuesVector     A valid MPSCNNConvolutionWeightsAndBiasesState object which specifies the resultValues state which will
 *                                     be updated and overwritten.
 *
 *  @discussion The following operations would be applied
 *              At update time:
 *              t = t + 1
 *              lr[t] = learningRate * sqrt(1 - beta2^t) / (1 - beta1^t)
 *
 *              m[t]     = beta1 * m[t-1] + (1 - beta1) * g
 *              v[t]     = beta2 * v[t-1] + (1 - beta2) * (g ^ 2)
 *              maxVel[t] = max(maxVel[t-1],v[t])
 *              variable = variable - lr[t] * m[t] / (sqrt(maxVel[t]) + epsilon)
 *
 */
-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)  commandBuffer
          inputGradientVector: (nonnull MPSVector *) inputGradientVector
            inputValuesVector: (nonnull MPSVector *) inputValuesVector
          inputMomentumVector: (nonnull MPSVector *) inputMomentumVector
          inputVelocityVector: (nonnull MPSVector *) inputVelocityVector
        maximumVelocityVector: (nullable MPSVector *) maximumVelocityVector
           resultValuesVector: (nonnull MPSVector *) resultValuesVector
MPS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
MPS_SWIFT_NAME(encode(commandBuffer:inputGradientVector:inputValuesVector:inputMomentumVector:inputVelocityVector:maximumVelocityVector:resultValuesVector:));

-(void) encodeToCommandBuffer: (nonnull id <MTLCommandBuffer>)  commandBuffer
          inputGradientMatrix: (nonnull MPSMatrix *) inputGradientMatrix
            inputValuesMatrix: (nonnull MPSMatrix *) inputValuesMatrix
          inputMomentumMatrix: (nonnull MPSMatrix *) inputMomentumMatrix
          inputVelocityMatrix: (nonnull MPSMatrix *) inputVelocityMatrix
        maximumVelocityMatrix: (nullable MPSMatrix *) maximumVelocityMatrix
           resultValuesMatrix: (nonnull MPSMatrix *) resultValuesMatrix
MPS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
MPS_SWIFT_NAME(encode(commandBuffer:inputGradientMatrix:inputValuesMatrix:inputMomentumMatrix:inputVelocityMatrix:maximumVelocityMatrix:resultValuesMatrix:));


/*!
 *  @abstract   Encode an MPSNNOptimizerAdam object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      convolutionGradientState   A valid MPSCNNConvolutionGradientState object which specifies the input state with gradients for this update.
 *  @param      convolutionSourceState     A valid MPSCNNConvolutionWeightsAndBiasesState object which specifies the input state with values to be updated.
 *  @param      inputMomentumVectors       An array MPSVector object which specifies the gradient momentum vectors which will
 *                                         be updated and overwritten. The index 0 corresponds to weights, index 1 corresponds to biases, array can be of
 *                                         size 1 in which case biases won't be updated
 *  @param      inputVelocityVectors       An array MPSVector object which specifies the gradient velocity vectors which will
 *                                         be updated and overwritten. The index 0 corresponds to weights, index 1 corresponds to biases, array can be of
 *                                         size 1 in which case biases won't be updated
 *  @param      resultState                A valid MPSCNNConvolutionWeightsAndBiasesState object which specifies the resultValues state which will
 *                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *
 *              t = t + 1
 *              lr[t] = learningRate * sqrt(1 - beta2^t) / (1 - beta1^t)
 *
 *              m[t]     = beta1 * m[t-1] + (1 - beta1) * g
 *              v[t]     = beta2 * v[t-1] + (1 - beta2) * (g ^ 2)
 *              variable = variable - lr[t] * m[t] / (sqrt(v[t]) + epsilon)
 *
 *
 */
-(void) encodeToCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
     convolutionGradientState: (MPSCNNConvolutionGradientState* __nonnull) convolutionGradientState
       convolutionSourceState: (MPSCNNConvolutionWeightsAndBiasesState* __nonnull) convolutionSourceState
         inputMomentumVectors: (nullable NSArray<MPSVector *>*) inputMomentumVectors
         inputVelocityVectors: (nullable NSArray<MPSVector *>*) inputVelocityVectors
                  resultState: (nonnull MPSCNNConvolutionWeightsAndBiasesState *) resultState
MPS_SWIFT_NAME(encode(commandBuffer:convolutionGradientState:convolutionSourceState:inputMomentumVectors:inputVelocityVectors:resultState:));

/*!
 *  @abstract   Encode an AMSGrad variant of MPSNNOptimizerAdam object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      convolutionGradientState   A valid MPSCNNConvolutionGradientState object which specifies the input state with gradients for this update.
 *  @param      convolutionSourceState     A valid MPSCNNConvolutionWeightsAndBiasesState object which specifies the input state with values to be updated.
 *  @param      inputMomentumVectors       An array MPSVector object which specifies the gradient momentum vectors which will
 *                                         be updated and overwritten. The index 0 corresponds to weights, index 1 corresponds to biases, array can be of
 *                                         size 1 in which case biases won't be updated
 *  @param      inputVelocityVectors       An array MPSVector object which specifies the gradient velocity vectors which will
 *                                         be updated and overwritten. The index 0 corresponds to weights, index 1 corresponds to biases, array can be of
 *                                         size 1 in which case biases won't be updated
 *  @param      maximumVelocityVectors     An array MPSVector object which specifies the maximum velocity vectors which will
 *                                         be updated and overwritten. The index 0 corresponds to weights, index 1 corresponds to biases, array can be of
 *                                         size 1 in which case biases won't be updated. May be nil, if nil then normal Adam optimizer behaviour is followed.
 *  @param      resultState                A valid MPSCNNConvolutionWeightsAndBiasesState object which specifies the resultValues state which will
 *                                         be updated and overwritten.
 *
 *  @discussion The following operations would be applied
 *              At update time:
 *              t = t + 1
 *              lr[t] = learningRate * sqrt(1 - beta2^t) / (1 - beta1^t)
 *
 *              m[t]     = beta1 * m[t-1] + (1 - beta1) * g
 *              v[t]     = beta2 * v[t-1] + (1 - beta2) * (g ^ 2)
 *              maxVel[t] = max(maxVel[t-1],v[t])
 *              variable = variable - lr[t] * m[t] / (sqrt(maxVel[t]) + epsilon)
 *
 */

-(void) encodeToCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
     convolutionGradientState: (MPSCNNConvolutionGradientState* __nonnull) convolutionGradientState
       convolutionSourceState: (MPSCNNConvolutionWeightsAndBiasesState* __nonnull) convolutionSourceState
         inputMomentumVectors: (nonnull NSArray<MPSVector *>*) inputMomentumVectors
         inputVelocityVectors: (nonnull NSArray<MPSVector *>*) inputVelocityVectors
       maximumVelocityVectors: (nullable NSArray<MPSVector *>*) maximumVelocityVectors
                  resultState: (nonnull MPSCNNConvolutionWeightsAndBiasesState *) resultState
MPS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
MPS_SWIFT_NAME(encode(commandBuffer:convolutionGradientState:convolutionSourceState:inputMomentumVectors:inputVelocityVectors:maximumVelocityVectors:resultState:));


/*!
 *  @abstract   Encode an MPSNNOptimizerAdam object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer                              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      batchNormalizationState                    A valid MPSCNNBatchNormalizationState object which specifies the input state with gradients and original gamma/beta for this update.
 *  @param      inputMomentumVectors                       An array MPSVector object which specifies the gradient momentum vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to gamma, index 1 corresponds to beta, array can be of
 *                                                         size 1 in which case beta won't be updated
 *  @param      inputVelocityVectors                       An array MPSVector object which specifies the gradient velocity vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to gamma, index 1 corresponds to beta, array can be of
 *                                                         size 1 in which case beta won't be updated
 *  @param      resultState                                A valid MPSCNNNormalizationGammaAndBetaState object which specifies the resultValues state which will
 *                                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *
 *              t = t + 1
 *              lr[t] = learningRate * sqrt(1 - beta2^t) / (1 - beta1^t)
 *
 *              m[t]     = beta1 * m[t-1] + (1 - beta1) * g
 *              v[t]     = beta2 * v[t-1] + (1 - beta2) * (g ^ 2)
 *              variable = variable - lr[t] * m[t] / (sqrt(v[t]) + epsilon)
 *
 *
 */
-(void) encodeToCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
      batchNormalizationState: (MPSCNNBatchNormalizationState* __nonnull) batchNormalizationState
         inputMomentumVectors: (nullable NSArray<MPSVector *>*) inputMomentumVectors
         inputVelocityVectors: (nullable NSArray<MPSVector *>*) inputVelocityVectors
                  resultState: (nonnull MPSCNNNormalizationGammaAndBetaState *) resultState
MPS_SWIFT_NAME(encode(commandBuffer:batchNormalizationState:inputMomentumVectors:inputVelocityVectors:resultState:));

/*!
 *  @abstract   Encode an AMSGrad variant of  MPSNNOptimizerAdam object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer                              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      batchNormalizationState                    A valid MPSCNNBatchNormalizationState object which specifies the input state with gradients and original gamma/beta for this update.
 *  @param      inputMomentumVectors                       An array MPSVector object which specifies the gradient momentum vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to gamma, index 1 corresponds to beta, array can be of
 *                                                         size 1 in which case beta won't be updated
 *  @param      inputVelocityVectors                       An array MPSVector object which specifies the gradient velocity vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to gamma, index 1 corresponds to beta, array can be of
 *                                                         size 1 in which case beta won't be updated
 *  @param      maximumVelocityVectors                     An array MPSVector object which specifies the maximum velocity vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to weights, index 1 corresponds to biases, array can be of
 *                                                         size 1 in which case biases won't be updated. May be nil, if nil then normal Adam optimizer behaviour is followed.
 *  @param      resultState                                A valid MPSCNNNormalizationGammaAndBetaState object which specifies the resultValues state which will
 *                                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *              At update time:
 *              t = t + 1
 *              lr[t] = learningRate * sqrt(1 - beta2^t) / (1 - beta1^t)
 *
 *              m[t]     = beta1 * m[t-1] + (1 - beta1) * g
 *              v[t]     = beta2 * v[t-1] + (1 - beta2) * (g ^ 2)
 *              maxVel[t] = max(maxVel[t-1],v[t])
 *              variable = variable - lr[t] * m[t] / (sqrt(maxVel[t]) + epsilon)
 */

-(void) encodeToCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
      batchNormalizationState: (MPSCNNBatchNormalizationState* __nonnull) batchNormalizationState
         inputMomentumVectors: (nonnull NSArray<MPSVector *>*) inputMomentumVectors
         inputVelocityVectors: (nonnull NSArray<MPSVector *>*) inputVelocityVectors
       maximumVelocityVectors: (nullable NSArray<MPSVector *>*) maximumVelocityVectors
                  resultState: (nonnull MPSCNNNormalizationGammaAndBetaState *) resultState
MPS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
MPS_SWIFT_NAME(encode(commandBuffer:batchNormalizationState:inputMomentumVectors:inputVelocityVectors:maximumVelocityVectors:resultState:));

/*!
 *  @abstract   Encode an MPSNNOptimizerAdam object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer                              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      batchNormalizationGradientState            A valid MPSCNNBatchNormalizationState object which specifies the input state with gradients for this update.
 *  @param      batchNormalizationSourceState              A valid MPSCNNBatchNormalizationState object which specifies the input state with original gamma/beta for this update.
 *  @param      inputMomentumVectors                       An array MPSVector object which specifies the gradient momentum vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to gamma, index 1 corresponds to beta, array can be of
 *                                                         size 1 in which case beta won't be updated
 *  @param      inputVelocityVectors                       An array MPSVector object which specifies the gradient velocity vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to gamma, index 1 corresponds to beta, array can be of
 *                                                         size 1 in which case beta won't be updated
 *  @param      resultState                                A valid MPSCNNNormalizationGammaAndBetaState object which specifies the resultValues state which will
 *                                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *
 *              t = t + 1
 *              lr[t] = learningRate * sqrt(1 - beta2^t) / (1 - beta1^t)
 *
 *              m[t]     = beta1 * m[t-1] + (1 - beta1) * g
 *              v[t]     = beta2 * v[t-1] + (1 - beta2) * (g ^ 2)
 *              variable = variable - lr[t] * m[t] / (sqrt(v[t]) + epsilon)
 *
 *
 */
-(void)             encodeToCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
          batchNormalizationGradientState: (MPSCNNBatchNormalizationState* __nonnull) batchNormalizationGradientState
            batchNormalizationSourceState: (MPSCNNBatchNormalizationState* __nonnull) batchNormalizationSourceState
                     inputMomentumVectors: (nullable NSArray<MPSVector *>*) inputMomentumVectors
                     inputVelocityVectors: (nullable NSArray<MPSVector *>*) inputVelocityVectors
                              resultState: (nonnull MPSCNNNormalizationGammaAndBetaState *) resultState
MPS_SWIFT_NAME(encode(commandBuffer:batchNormalizationGradientState:batchNormalizationSourceState:inputMomentumVectors:inputVelocityVectors:resultState:));

/*!
 *  @abstract   Encode an AMSGrad variant of MPSNNOptimizerAdam object to a command buffer to perform out of place update
 *
 *  @param      commandBuffer                              A valid MTLCommandBuffer to receive the encoded kernel.
 *  @param      batchNormalizationGradientState            A valid MPSCNNBatchNormalizationState object which specifies the input state with gradients for this update.
 *  @param      batchNormalizationSourceState              A valid MPSCNNBatchNormalizationState object which specifies the input state with original gamma/beta for this update.
 *  @param      inputMomentumVectors                       An array MPSVector object which specifies the gradient momentum vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to gamma, index 1 corresponds to beta, array can be of
 *                                                         size 1 in which case beta won't be updated
 *  @param      inputVelocityVectors                       An array MPSVector object which specifies the gradient velocity vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to gamma, index 1 corresponds to beta, array can be of
 *                                                         size 1 in which case beta won't be updated
 *  @param      maximumVelocityVectors                     An array MPSVector object which specifies the maximum velocity vectors which will
 *                                                         be updated and overwritten. The index 0 corresponds to weights, index 1 corresponds to biases, array can be of
 *                                                         size 1 in which case biases won't be updated. May be nil, if nil then normal Adam optimizer behaviour is followed.
 *  @param      resultState                                A valid MPSCNNNormalizationGammaAndBetaState object which specifies the resultValues state which will
 *                                                         be updated and overwritten.
 *
 *
 *  @discussion The following operations would be applied
 *              At update time:
 *              t = t + 1
 *              lr[t] = learningRate * sqrt(1 - beta2^t) / (1 - beta1^t)
 *
 *              m[t]     = beta1 * m[t-1] + (1 - beta1) * g
 *              v[t]     = beta2 * v[t-1] + (1 - beta2) * (g ^ 2)
 *              maxVel[t] = max(maxVel[t-1],v[t])
 *              variable = variable - lr[t] * m[t] / (sqrt(maxVel[t]) + epsilon)
 *
 */

-(void)             encodeToCommandBuffer: (__nonnull id<MTLCommandBuffer>) commandBuffer
          batchNormalizationGradientState: (MPSCNNBatchNormalizationState* __nonnull) batchNormalizationGradientState
            batchNormalizationSourceState: (MPSCNNBatchNormalizationState* __nonnull) batchNormalizationSourceState
                     inputMomentumVectors: (nonnull NSArray<MPSVector *>*) inputMomentumVectors
                     inputVelocityVectors: (nonnull NSArray<MPSVector *>*) inputVelocityVectors
                   maximumVelocityVectors: (nullable NSArray<MPSVector *>*) maximumVelocityVectors
                              resultState: (nonnull MPSCNNNormalizationGammaAndBetaState *) resultState
MPS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
MPS_SWIFT_NAME(encode(commandBuffer:batchNormalizationGradientState:batchNormalizationSourceState:inputMomentumVectors:inputVelocityVectors:maximumVelocityVectors:resultState:));


@end  /* MPSNNOptimizerAdam */





#ifdef __cplusplus
}
#endif

#endif /* MPSNNOptimizers_h */

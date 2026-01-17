//
//  MLCTypes.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MLCompute/MLCDefines.h>

#ifndef MLComputeTypes_h
#define MLComputeTypes_h

#ifdef __cplusplus
extern "C" {
#endif

@class MLCTensor;

/*! @abstract A callback completion handler you execute when a graph finishes execution.
 */
typedef void (^MLCGraphCompletionHandler)(MLCTensor __autoreleasing * _Nullable resultTensor,
                                          NSError * _Nullable error,
                                          NSTimeInterval executionTime);

#pragma mark - General Types

/*!
 *  @enum      MLCDataType
 *  @abstract  A tensor data type.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCDataType) {
    MLCDataTypeInvalid NS_SWIFT_UNAVAILABLE("") = 0,
    /*! The 32-bit floating-point data type.
     */
    MLCDataTypeFloat32 = 1,
    /*! The Boolean data type.
     */
    MLCDataTypeBoolean = 4,
    /*! The 64-bit integer data type.
     */
    MLCDataTypeInt64   = 5,
    /*! The 32-bit integer data type.
     */
    MLCDataTypeInt32   = 7,

    // Must be last
    MLCDataTypeCount   NS_SWIFT_UNAVAILABLE(""), // holds the number of MLCDataTypes
};

/*!
 *  @enum      MLCRandomInitializerType
 *  @abstract  An initializer type you use to create a tensor with random data.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCRandomInitializerType) {
    MLCRandomInitializerTypeInvalid       NS_SWIFT_UNAVAILABLE("") = 0,
    /*! The uniform random initializer type.
     */
    MLCRandomInitializerTypeUniform       = 1,
    /*! The glorot uniform random initializer type.
     */
    MLCRandomInitializerTypeGlorotUniform = 2,
    /*! The Xavier random initializer type.
     */
    MLCRandomInitializerTypeXavier        = 3,

    // Must be last
    MLCRandomInitializerTypeCount         NS_SWIFT_UNAVAILABLE(""), // holds the number of MLCRandomInitializerType
};

/*!
 *  @enum       MLCDeviceType
 *  @abstract   A device type for execution of a neural network.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCDeviceType) {
    /*! The CPU device type.
     */
    MLCDeviceTypeCPU NS_SWIFT_NAME(cpu) = 0,
    /*! The GPU device type.  When selected, the framework will use a GPU.
     */
    MLCDeviceTypeGPU NS_SWIFT_NAME(gpu) = 1,
    /*! The any device type.  When selected, the framework will automatically use the appropriate devices to achieve the best
     *  performance.
     */
    MLCDeviceTypeAny = 2,

    // Must be last
    MLCDeviceTypeCount  NS_SWIFT_UNAVAILABLE(""), // holds the number of MLCDeviceType
};

/*!
 *  @enum       MLCGraphCompilationOptions
 *  @abstract   A bitmask that specifies the options you use when compiling a graph.
 *  @discussion This is passed as an argument to the compileWithOptions method avalable on MLCTrainingGraph and MLCInferenceGraph
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_OPTIONS(uint64_t, MLCGraphCompilationOptions) {
    /*! No graph compilation options.
     */
    MLCGraphCompilationOptionsNone                 = 0x00,
    /*! The option to debug layers during graph compilation.
     *
     *  @discussion Include this option to disable various optimizations such as layer fusion, and ensure the framework synchronizes
     *      the resulting forward and gradients tensors host memory with device memory, for layers marked as debuggable.
     */
    MLCGraphCompilationOptionsDebugLayers          = 0x01,
    /*! The option to disable layer fusion during graph compilation.
     *
     *  @discussion Include this option to disable fusion of layers, which is an important optimization that helps performance and
     *      memory footprint.
     *  */
    MLCGraphCompilationOptionsDisableLayerFusion   = 0x02,
    /*! The option to link graphs during graph compilation.
     *
     *  @discussion Include this option when you link together one or more sub-graphs when executing the forward, gradient, and
     *      optimizer update. For example, if the full computation graph includes a layer that the framework doesn’t support, you’ll
     *      need to create multiple sub-graphs and link them together using \p MLCGraphCompilationOptionsLinkGraphs. When doing so,
     *      include this option when you call \p -compileWithOptions: for graphs you want to link together.
     */
    MLCGraphCompilationOptionsLinkGraphs           = 0x04,
    /*! The option to compute all gradients during graph compilation.
     *
     *  @discussion Include this option to compute gradients for layers with or without parameters that only take input tensors.
     *      For example, if the first layer of a graph is a convolution layer, the framework only computes the gradients for weights
     *      and biases associated with the convolution layer, but not the gradients for the input. Include this option if you want to
     *      compute all gradients for the input.
     */
    MLCGraphCompilationOptionsComputeAllGradients  = 0x08,
};

/*!
 *  @enum       MLCExecutionOptions
 *  @abstract   A bitmask that specifies the options you’ll use when executing a graph.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_OPTIONS(uint64_t, MLCExecutionOptions) {
    MLCExecutionOptionsNone = 0x00,
    /*! The option to skip writing input data to device memory.
     *
     *  @discussion this option to prevent writing the input tensors to device memory associated with these tensors when the framework
     *      executes the graph.
     */
    MLCExecutionOptionsSkipWritingInputDataToDevice = 0x01,

    /*! The option to execute the graph synchronously.
     *
     *  @discussion Include this option to wait until execution of the graph on specified device finishes before returning from the
     *      \p execute method.
     */
    MLCExecutionOptionsSynchronous = 0x02,

    /*! The option to return profiling information in the callback before returning from execution.
     *
     *  @discussion Inlcude this option to return profliling information in the graph execute completion handler callback, including
     *      device execution time.
     */
    MLCExecutionOptionsProfiling = 0x04,

    /*! The option to execute the forward pass for inference only.
     *
     *  @discussion If you include this option and execute a training graph using one of the \p execute methods, such as
     *  \p -executeWithInputsData:lossLabelsData:lossLabelWeightsData:batchSize:options:completionHandler: , the framework only
     *      executes the forward pass of the training graph, and it executes that forward pass for inference only.
     *
     *      If you include this option and execute a training graph using one of the executeForward methods, such as
     *      \p -executeForwardWithBatchSize:options:completionHandler:), the framework executes the forward pass for inference only.
     */
    MLCExecutionOptionsForwardForInference = 0x08
};

#pragma mark - Layers

/*!
 *  @enum       MLCArithmeticOperation
 *  @abstract   The list of supported arithmetic operations.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCArithmeticOperation) {
    /*! An operation that calculates the elementwise sum of its two inputs.
     */
    MLCArithmeticOperationAdd      = 0,
    /*! An operation that calculates the elementwise difference of its two inputs.
     */
    MLCArithmeticOperationSubtract = 1,
    /*! An operation that calculates the elementwise product of its two inputs.
     */
    MLCArithmeticOperationMultiply = 2,
    /*! An operation that calculates the elementwise division of its two inputs.
     */
    MLCArithmeticOperationDivide   = 3,
    /*! An operation that calculates the elementwise floor of its two inputs.
     */
    MLCArithmeticOperationFloor    = 4,
    /*! An operation that calculates the elementwise round of its inputs.
     */
    MLCArithmeticOperationRound    = 5,
    /*! An operation that calculates the elementwise ceiling of its inputs.
     */
    MLCArithmeticOperationCeil     = 6,
    /*! An operation that calculates the elementwise square root of its inputs.
     */
    MLCArithmeticOperationSqrt     = 7,
    /*! An operation that calculates the elementwise reciprocal of the square root of its inputs.
     */
    MLCArithmeticOperationRsqrt    = 8,
    /*! An operation that calculates the elementwise sine of its inputs.
     */
    MLCArithmeticOperationSin      = 9,
    /*! An operation that calculates the elementwise cosine of its inputs.
     */
    MLCArithmeticOperationCos      = 10,
    /*! An operation that calculates the elementwise tangent of its inputs.
     */
    MLCArithmeticOperationTan      = 11,
    /*! An operation that calculates the elementwise inverse sine of its inputs.
     */
    MLCArithmeticOperationAsin     = 12,
    /*! An operation that calculates the elementwise inverse cosine of its inputs.
     */
    MLCArithmeticOperationAcos     = 13,
    /*! An operation that calculates the elementwise inverse tangent of its inputs.
     */
    MLCArithmeticOperationAtan     = 14,
    /*! An operation that calculates the elementwise hyperbolic sine of its inputs.
     */
    MLCArithmeticOperationSinh     = 15,
    /*! An operation that calculates the elementwise hyperbolic cosine of its inputs.
     */
    MLCArithmeticOperationCosh     = 16,
    /*! An operation that calculates the elementwise hyperbolic tangent of its inputs.
     */
    MLCArithmeticOperationTanh     = 17,
    /*! An operation that calculates the elementwise inverse hyperbolic sine of its inputs.
     */
    MLCArithmeticOperationAsinh    = 18,
    /*! An operation that calculates the elementwise inverse hyperbolic cosine of its inputs.
     */
    MLCArithmeticOperationAcosh    = 19,
    /*! An operation that calculates the elementwise inverse hyperbolic tangent of its inputs.
     */
    MLCArithmeticOperationAtanh    = 20,
    /*! An operation that calculates the elementwise first input raised to the power of its second input.
     */
    MLCArithmeticOperationPow      = 21,
    /*! An operation that calculates the elementwise result of e raised to the power of its input.
     */
    MLCArithmeticOperationExp      = 22,
    /*! An operation that calculates the elementwise result of 2 raised to the power of its input.
     */
    MLCArithmeticOperationExp2     = 23,
    /*! An operation that calculates the elementwise natural logarithm of its input.
     */
    MLCArithmeticOperationLog      = 24,
    /*! An operation that calculates the elementwise base 2 logarithm of its input.
     */
    MLCArithmeticOperationLog2     = 25,
    /*! An operation that calculates the elementwise product of its two inputs.  Returns 0 if y in x * y is zero, even if x is NaN or INF
     */
    MLCArithmeticOperationMultiplyNoNaN     MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5)) = 26,
    /*! An operations that calculates the elementwise division of its two inputs.  Returns 0 if the denominator is 0.
     */
    MLCArithmeticOperationDivideNoNaN       MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5)) = 27,
    /*! An operation that calculates the elementwise min of two inputs.
     */
    MLCArithmeticOperationMin               MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5)) = 28,
    /*! An operations that calculates the elementwise max of two inputs.
     */
    MLCArithmeticOperationMax               MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5)) = 29,

    // Must be last
    MLCArithmeticOperationCount    NS_SWIFT_UNAVAILABLE(""),
};

/*!
 *  @enum       MLCLossType
 *  @abstract   A loss function.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCLossType) {
    /*! The mean absolute error loss.
     */
    MLCLossTypeMeanAbsoluteError       = 0,
    /*! The mean squared error loss.
     */
    MLCLossTypeMeanSquaredError        = 1,
    /*! The softmax cross entropy loss.
     */
    MLCLossTypeSoftmaxCrossEntropy     = 2,
    /*! The sigmoid cross entropy loss.
     */
    MLCLossTypeSigmoidCrossEntropy     = 3,
    /*! The categorical cross entropy loss.
     */
    MLCLossTypeCategoricalCrossEntropy = 4,
    /*! The hinge loss.
     */
    MLCLossTypeHinge                   = 5,
    /*! The Huber loss.
     */
    MLCLossTypeHuber                   = 6,
    /*! The cosine distance loss.
     */
    MLCLossTypeCosineDistance          = 7,
    /*! The log loss.
     */
    MLCLossTypeLog                     = 8,

    // Must be last
    MLCLossTypeCount                   NS_SWIFT_UNAVAILABLE("")   // Holds the number of MLCLossTypes
};

/*!
 * @enum       MLCActivationType
 * @abstract   An activation type that you specify for an activation descriptor.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCActivationType) {
    /*! The identity activation type.
     */
    MLCActivationTypeNone                                               = 0,
    /*! The ReLU activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = x >= 0 ? x : a * x
     *  \endcode
     */
    MLCActivationTypeReLU                 NS_SWIFT_NAME(relu)           = 1,
    /*! The linear activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = a * x + b
     *  \endcode
     */
    MLCActivationTypeLinear                                             = 2,
    /*! The sigmoid activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = 1 / (1 + e⁻ˣ)
     *  \endcode
     */
    MLCActivationTypeSigmoid                                            = 3,
    /*! The hard sigmoid activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = clamp((x * a) + b, 0, 1)
     *  \endcode
     */
    MLCActivationTypeHardSigmoid                                        = 4,
    /*! The hyperbolic tangent (TanH) activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = a * tanh(b * x)
     *  \endcode
     */
    MLCActivationTypeTanh                                               = 5,
    /*! The absolute activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = fabs(x)
     *  \endcode
     */
    MLCActivationTypeAbsolute                                           = 6,
    /*! The parametric soft plus activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = a * log(1 + e^(b * x))
     *  \endcode
     */
    MLCActivationTypeSoftPlus                                           = 7,
    /*! The parametric soft sign activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = x / (1 + abs(x))
     *  \endcod
     */
    MLCActivationTypeSoftSign                                           = 8,
    /*! The parametric ELU activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = x >= 0 ? x : a * (exp(x) - 1)
     *  \endcode
     */
    MLCActivationTypeELU                  NS_SWIFT_NAME(elu)            = 9,
    /*! The ReLUN activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = min((x >= 0 ? x : a * x), b)
     *  \endcode
     */
    MLCActivationTypeReLUN                NS_SWIFT_NAME(relun)          = 10,
    /*! The log sigmoid activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = log(1 / (1 + exp(-x)))
     *  \endcode
     */
    MLCActivationTypeLogSigmoid                                         = 11,
    /*! The SELU activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = scale * (max(0, x) + min(0, α * (exp(x) − 1)))
     *  \endcode
     *  where:
     *  \code
     *  α = 1.6732632423543772848170429916717
     *  scale = 1.0507009873554804934193349852946
     *  \endcode
     */
    MLCActivationTypeSELU                 NS_SWIFT_NAME(selu)           = 12,
    /*! The CELU activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = max(0, x) + min(0, a * (exp(x / a) − 1))
     *  \endcode
     */
    MLCActivationTypeCELU                 NS_SWIFT_NAME(celu)           = 13,
    /*! The hard shrink activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = x, if x > a or x < −a, else 0
     *  \endcode
     */
    MLCActivationTypeHardShrink                                         = 14,
    /*! The soft shrink activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = x - a, if x > a, x + a, if x < −a, else 0
     *  \endcode
     */
    MLCActivationTypeSoftShrink                                         = 15,
    /*! The hyperbolic tangent (TanH) shrink activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = x - tanh(x)
     *  \endcode
     */
    MLCActivationTypeTanhShrink                                         = 16,
    /*! The threshold activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = x, if x > a, else b
     *  \endcode
     */
    MLCActivationTypeThreshold                                          = 17,
    /*! The GELU activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = x * CDF(x)
     *  \endcode
     */
    MLCActivationTypeGELU                 NS_SWIFT_NAME(gelu)           = 18,
    /*! The hardswish activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = 0, if x <= -3
     *  f(x) = x, if x >= +3
     *  f(x) = x * (x + 3)/6, otherwise
     *  \endcode
     */
    MLCActivationTypeHardSwish            NS_SWIFT_NAME(hardSwish) MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5))     = 19,
    /*! The clamp activation type.
     *  @discussion This activation type implements the following function:
     *  \code
     *  f(x) = min(max(x, a), b)
     *  \endcode
     */
    MLCActivationTypeClamp                MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5))     = 20,

    // Must be last
    MLCActivationTypeCount                NS_SWIFT_UNAVAILABLE(""),
};

/*!
 * @enum       MLCConvolutionType
 * @abstract   A convolution type that you specify for a convolution descriptor.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCConvolutionType) {
    /*! The standard convolution type.
     */
    MLCConvolutionTypeStandard   = 0,
    /*! The transposed convolution type.
     */
    MLCConvolutionTypeTransposed = 1,
    /*! The depthwise convolution type.
     */
    MLCConvolutionTypeDepthwise  = 2,
};

/*!
 * @enum       MLCPaddingPolicy
 * @abstract   A padding policy that you specify for a convolution or pooling layer.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCPaddingPolicy) {
    /*! The "same" padding policy.
     */
    MLCPaddingPolicySame           = 0,
    /*! The "valid" padding policy.
     */
    MLCPaddingPolicyValid          = 1,
    /*! The choice to use explicitly specified padding sizes.
     */
    MLCPaddingPolicyUsePaddingSize = 2,
} NS_REFINED_FOR_SWIFT;

/*!
 *  @enum       MLCPaddingType
 *  @abstract   A padding type that you specify for a padding layer.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCPaddingType) {
    /*! The zero padding type.
     */
    MLCPaddingTypeZero      = 0,
    /*! The reflect padding type.
     */
    MLCPaddingTypeReflect   = 1,
    /*! The symmetric padding type.
     */
    MLCPaddingTypeSymmetric = 2,
    /*! The constant padding type.
     */
    MLCPaddingTypeConstant  = 3,
};

/*!
 *  @enum       MLCPoolingType
 *  @abstract   A pooling function type for a pooling layer.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCPoolingType) {
    /*! The max pooling type.
     */
    MLCPoolingTypeMax     = 1,
    /*! The average pooling type.
     */
    MLCPoolingTypeAverage = 2,
    /*! The L2-norm pooling type.
     */
    MLCPoolingTypeL2Norm  = 3,

    // Must be last
    MLCPoolingTypeCount   NS_SWIFT_UNAVAILABLE(""),
} NS_REFINED_FOR_SWIFT;

/*!
 *  @enum       MLCReductionType
 *  @abstract   A reduction operation type.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCReductionType) {
    /*! No reduction.
     */
    MLCReductionTypeNone                 = 0,
    /*! The sum reduction.
     */
    MLCReductionTypeSum                  = 1,
    /*! The mean reduction.
     */
    MLCReductionTypeMean                 = 2,
    /*! The max reduction.
     */
    MLCReductionTypeMax                  = 3,
    /*! The min reduction.
     */
    MLCReductionTypeMin                  = 4,
    /*! The argmax reduction.
     */
    MLCReductionTypeArgMax               = 5,
    /*! The argmin reduction.
     */
    MLCReductionTypeArgMin               = 6,
    /*! The L1norm reduction.
     */
    MLCReductionTypeL1Norm    MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5)) = 7,
    /*! Any(X) = X_0 || X_1 || ... X_n
     */
    MLCReductionTypeAny       MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5)) = 8,
    /*! Alf(X) = X_0 && X_1 && ... X_n
     */
    MLCReductionTypeAll       MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5)) = 9,
    
    MLCReductionTypeCount                NS_SWIFT_UNAVAILABLE(""),
};

/*!
 *  @enum       MLCRegularizationType
 *  @abstract
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCRegularizationType) {
    /*! No regularization.
     */
    MLCRegularizationTypeNone                   = 0,
    /*! The L1 regularization.
     */
    MLCRegularizationTypeL1   NS_SWIFT_NAME(l1) = 1,
    /*! The L2 regularization.
     */
    MLCRegularizationTypeL2   NS_SWIFT_NAME(l2) = 2,
};

/*!
 *  @enum       MLCSampleMode
 *  @abstract   A sampling mode for an upsample layer.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCSampleMode) {
    /*! The nearest sample mode.
     */
    MLCSampleModeNearest = 0,
    /*! The linear sample mode.
     */
    MLCSampleModeLinear  = 1,
};

/*!
 *  @enum       MLCSoftmaxOperation
 *  @abstract   A softmax operation.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(int32_t, MLCSoftmaxOperation) {
    /*! The standard softmax operation.
     */
    MLCSoftmaxOperationSoftmax    = 0,
    /*! The log softmax operation.
     */
    MLCSoftmaxOperationLogSoftmax = 1,
};

/*!
 * @enum       MLCLSTMResultMode
 * @abstract   A result mode for an LSTM layer.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
typedef NS_ENUM(uint64_t, MLCLSTMResultMode) {
    /*! The output result mode. When selected for an LSTM layer, the layer will produce a single result tensor representing the final output of the LSTM.
     */
    MLCLSTMResultModeOutput = 0,
    /*! The output and states result mode. When selected for an LSTM layer, the layer will produce three result tensors representing the final output of
     *  the LSTM, the last hidden state, and the cell state, respectively.
     */
    MLCLSTMResultModeOutputAndStates = 1,
};

/*!
 *  @enum       MLCComparisonOperation
 *  @abstract   A comparison operation.
 */
MLCOMPUTE_ENUM_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5))
typedef NS_ENUM(int32_t, MLCComparisonOperation) {
    MLCComparisonOperationEqual          = 0,
    MLCComparisonOperationNotEqual       = 1,
    MLCComparisonOperationLess           = 2,
    MLCComparisonOperationGreater        = 3,
    MLCComparisonOperationLessOrEqual    = 4,
    MLCComparisonOperationGreaterOrEqual = 5,
    MLCComparisonOperationLogicalAND     = 6,
    MLCComparisonOperationLogicalOR      = 7,
    MLCComparisonOperationLogicalNOT     = 8,
    MLCComparisonOperationLogicalNAND    = 9,
    MLCComparisonOperationLogicalNOR     = 10,
    MLCComparisonOperationLogicalXOR     = 11,

    // Must be last
    MLCComparisonOperationCount          NS_SWIFT_UNAVAILABLE(""),
};


NS_ASSUME_NONNULL_BEGIN
/*! @abstract Returns a textual description of the activation type, suitable for debugging.
 */
NSString *MLCActivationTypeDebugDescription(MLCActivationType activationType) NS_SWIFT_NAME(getter:MLCActivationType.debugDescription(self:));
/*! @abstract Returns a textual description of the arithmetic operation, suitable for debugging.
 */
NSString *MLCArithmeticOperationDebugDescription(MLCArithmeticOperation operation) NS_SWIFT_NAME(getter:MLCArithmeticOperation.debugDescription(self:));
/*! @abstract Returns a textual description of the padding policy, suitable for debugging.
 */
NSString *MLCPaddingPolicyDebugDescription(MLCPaddingPolicy paddingPolicy) NS_REFINED_FOR_SWIFT;
/*! @abstract Returns a textual description of the loss type, suitable for debugging.
 */
NSString *MLCLossTypeDebugDescription(MLCLossType lossType) NS_SWIFT_NAME(getter:MLCLossType.debugDescription(self:));
/*! @abstract Returns a textual description of the reduction type, suitable for debugging.
 */
NSString *MLCReductionTypeDebugDescription(MLCReductionType reductionType) NS_SWIFT_NAME(getter:MLCReductionType.debugDescription(self:));
/*! @abstract Returns a textual description of the padding type, suitable for debugging.
 */
NSString *MLCPaddingTypeDebugDescription(MLCPaddingType paddingType) NS_SWIFT_NAME(getter:MLCPaddingType.debugDescription(self:));
/*! @abstract Returns a textual description of the convolution type, suitable for debugging.
 */
NSString *MLCConvolutionTypeDebugDescription(MLCConvolutionType convolutionType) NS_SWIFT_NAME(getter:MLCConvolutionType.debugDescription(self:));
/*! @abstract Returns a textual description of the pooling type, suitable for debugging.
 */
NSString *MLCPoolingTypeDebugDescription(MLCPoolingType poolingType) NS_REFINED_FOR_SWIFT;
/*! @abstract Returns a textual description of the softmax operation, suitable for debugging.
 */
NSString *MLCSoftmaxOperationDebugDescription(MLCSoftmaxOperation operation) NS_SWIFT_NAME(getter:MLCSoftmaxOperation.debugDescription(self:));
/*! @abstract Returns a textual description of the sample mode, suitable for debugging.
 */
NSString *MLCSampleModeDebugDescription(MLCSampleMode mode) NS_SWIFT_NAME(getter:MLCSampleMode.debugDescription(self:));
/*! @abstract Returns a textual description of the LSTM result mode, suitable for debugging.
 */
NSString *MLCLSTMResultModeDebugDescription(MLCLSTMResultMode mode)
    NS_SWIFT_NAME(getter:MLCLSTMResultMode.debugDescription(self:));
/*! @abstract Returns a textual description of the compare operation, suitable for debugging.
 */
NSString *MLCComparisonOperationDebugDescription(MLCComparisonOperation operation)
    NS_SWIFT_NAME(getter:MLCComparisonOperation.debugDescription(self:)) MLCOMPUTE_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5));

NS_ASSUME_NONNULL_END

#ifdef __cplusplus
}
#endif

#endif /* MLComputeTypes_h */

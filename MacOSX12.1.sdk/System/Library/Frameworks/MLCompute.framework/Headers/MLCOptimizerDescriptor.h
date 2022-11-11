//
//  MLCOptimizerDescriptor.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCOptimizerDescriptor
    @discussion The MLCOptimizerDescriptor specifies an optimizer descriptor.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface  MLCOptimizerDescriptor : NSObject <NSCopying>

/*! @property   learningRate
    @abstract   The learning rate
 */
@property (readonly, nonatomic) float learningRate;

/*! @property   gradientRescale
    @abstract   The rescale value applied to gradients during optimizer update
 */
@property (readonly, nonatomic) float gradientRescale;

/*! @property   appliesGradientClipping
    @abstract   Whether gradient clipping should be applied or not.
    @discussion The default is false
 */
@property (readonly, nonatomic) BOOL appliesGradientClipping;

/*! @property   gradientClipMax
    @abstract   The maximum gradient value if gradient clipping is enabled before gradient is rescaled.
 */
@property (readonly, nonatomic) float gradientClipMax;

/*! @property   gradientClipMin
    @abstract   The minimum gradient value if gradient clipping is enabled before gradient is rescaled.
 */
@property (readonly, nonatomic) float gradientClipMin;

/*! @property   regularizationScale
    @abstract   The regularization scale.
 */
@property (readonly, nonatomic) float regularizationScale;

/*! @property   regularizationType
    @abstract   The regularization type.
 */
@property (readonly, nonatomic) MLCRegularizationType regularizationType;

/*! @property   gradientClippingType
    @abstract   The type of clipping applied to gradient
 */
@property (readonly, nonatomic) MLCGradientClippingType gradientClippingType
    MLCOMPUTE_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*! @property   maximumClippingNorm
    @abstract   The maximum clipping value
 */
@property (readonly, nonatomic) float maximumClippingNorm
    MLCOMPUTE_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*! @property   customGlobalNorm
    @abstract   Used only with MLCGradientClippingTypeByGlobalNorm. If non zero, this norm will be used in place of global norm.
 */
@property (readonly, nonatomic) float customGlobalNorm
    MLCOMPUTE_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

/*! @abstract   Create a MLCOptimizerDescriptor object
    @param      learningRate                    The learning rate
    @param      gradientRescale              The gradient rescale value
    @param      regularizationType       The regularization type
    @param      regularizationScale     The regularization scale
    @return     A new MLCOptimizerDescriptor object.
 */
+ (instancetype)descriptorWithLearningRate:(float)learningRate
                           gradientRescale:(float)gradientRescale
                        regularizationType:(MLCRegularizationType)regularizationType
                       regularizationScale:(float)regularizationScale;

/*! @abstract   Create a MLCOptimizerDescriptor object
    @param      learningRate                      The learning rate
    @param      gradientRescale                The gradient rescale value
    @param      appliesGradientClipping   Whether to apply gradient clipping
    @param      gradientClipMax                The maximum gradient value to be used with gradient clipping
    @param      gradientClipMin                The minimum gradient value to be used with gradient clipping
    @param      regularizationType          The regularization type
    @param      regularizationScale        The regularization scale
    @return     A new MLCOptimizerDescriptor object.
 */
+ (instancetype)descriptorWithLearningRate:(float)learningRate
                           gradientRescale:(float)gradientRescale
                   appliesGradientClipping:(BOOL)appliesGradientClipping
                           gradientClipMax:(float)gradientClipMax
                           gradientClipMin:(float)gradientClipMin
                        regularizationType:(MLCRegularizationType)regularizationType
                       regularizationScale:(float)regularizationScale;

/*! @abstract   Create an MLCOptimizerDescriptor object
    @param      learningRate                            The learning rate
    @param      gradientRescale                      The gradient rescale value
    @param      appliesGradientClipping    Whether to apply gradient clipping
    @param      gradientClippingType           The type of clipping applied to gradients
    @param      gradientClipMax                      The maximum gradient value to be used with gradient clipping
    @param      gradientClipMin                      The minimum gradient value to be used with gradient clipping
    @param      maximumClippingNorm             The maximum norm to be used with gradient clipping
    @param      customGlobalNorm                    If non-zero, the norm to be used instead of calculating the global norm
    @param      regularizationType               The regularization type
    @param      regularizationScale             The regularization scale
    @return     A new MLCOptimizerDescriptor object.
 */
+ (instancetype)descriptorWithLearningRate:(float)learningRate
                           gradientRescale:(float)gradientRescale
                   appliesGradientClipping:(BOOL)appliesGradientClipping
                      gradientClippingType:(MLCGradientClippingType)gradientClippingType
                           gradientClipMax:(float)gradientClipMax
                           gradientClipMin:(float)gradientClipMin
                       maximumClippingNorm:(float)maximumClippingNorm
                          customGlobalNorm:(float)customGlobalNorm
                        regularizationType:(MLCRegularizationType)regularizationType
                       regularizationScale:(float)regularizationScale
MLCOMPUTE_AVAILABLE_STARTING(macos(12.0), ios(15.0), tvos(15.0));

@end


NS_ASSUME_NONNULL_END


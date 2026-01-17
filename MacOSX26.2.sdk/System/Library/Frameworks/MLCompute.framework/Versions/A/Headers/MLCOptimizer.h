//
//  MLCOptimizer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>

@class MLCDevice;
@class MLCDeviceOptimizer;
@class MLCOptimizerDescriptor;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCOptimizer
    @discussion The MLCOptimizer specifies a base optimizer.
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface  MLCOptimizer : NSObject<NSCopying>

/*! @property   learningRate
    @abstract   The learning rate.  This property is 'readwrite' so that callers can implement a 'decay' during training
 */
@property (readwrite, nonatomic) float learningRate;

/*! @property   gradientRescale
    @abstract   The rescale value applied to gradients during optimizer update
 */
@property (readonly, nonatomic) float gradientRescale;

/*! @property   appliesGradientClipping
    @abstract   Whether gradient clipping should be applied or not.
 */
@property (readwrite, nonatomic) BOOL appliesGradientClipping;

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


+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

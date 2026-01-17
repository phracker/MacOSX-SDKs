//
//  MLCSGDOptimizer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <MLCompute/MLCompute.h>

@class MLCDevice;
@class MLCOptimizerDescriptor;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCSGDOptimizer
    @discussion The MLCSGDOptimizer specifies a stochastic gradient descent optimizer.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface  MLCSGDOptimizer : MLCOptimizer<NSCopying>

/*! @property   momentumScale
    @abstract   The momentum factor.  A hyper-parameter.
    @discussion The default is 0.0.
 */
@property (readonly, nonatomic) float momentumScale;

/*! @property   usesNesterovMomentum
    @abstract   A boolean that specifies whether to apply nesterov momentum or not.
    @discussion The default is false.
 */
@property (readonly, nonatomic) BOOL usesNesterovMomentum;

/*! @abstract   Create an MLCSGDOptimizer object with defaults
    @return     A new MLCSGDOptimizer object.
 */
+ (instancetype)optimizerWithDescriptor:(MLCOptimizerDescriptor *)optimizerDescriptor;

/*! @abstract   Create an MLCSGDOptimizer object
    @param      optimizerDescriptor    The optimizer descriptor object
    @param      momentumScale                 The momentum scale
    @param      usesNesterovMomentum      A boolean to enable / disable nesterov momentum
    @return     A new MLCSGDOptimizer object.
 */
+ (instancetype)optimizerWithDescriptor:(MLCOptimizerDescriptor *)optimizerDescriptor
                          momentumScale:(float)momentumScale
                    usesNesterovMomentum:(BOOL)usesNesterovMomentum;

@end

NS_ASSUME_NONNULL_END

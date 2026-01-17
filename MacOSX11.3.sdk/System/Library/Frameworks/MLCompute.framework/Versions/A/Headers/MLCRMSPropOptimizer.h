//
//  MLCRMSPropOptimizer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <MLCompute/MLCompute.h>

@class MLCDevice;
@class MLCOptimizerDescriptor;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCRMSPropOptimizer
    @discussion The MLCRMSPropOptimizer specifies the RMSProp optimizer.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0))
@interface  MLCRMSPropOptimizer : MLCOptimizer<NSCopying>

/*! @property   momentumScale
    @abstract   The momentum factor.  A hyper-parameter.
    @discussion The default is 0.0.
 */
@property (readonly, nonatomic) float momentumScale;

/*! @property   alpha
    @abstract   The smoothing constant.
    @discussion The default is 0.99.
 */
@property (readonly, nonatomic) float alpha;

/*! @property   epsilon
    @abstract   A term added to improve numerical stability.
    @discussion The default is 1e-8.
 */
@property (readonly, nonatomic) float epsilon;

/*! @property   isCentered
    @abstract   If True, compute the centered RMSProp, the gradient is normalized by an estimation of its variance.  
    @discussion The default is false.
 */
@property (readonly, nonatomic) BOOL isCentered;

/*! @abstract   Create a MLCRMSPropOptimizer object with defaults
    @return     A new MLCRMSPropOptimizer object.
 */
+ (instancetype)optimizerWithDescriptor:(MLCOptimizerDescriptor *)optimizerDescriptor;

/*! @abstract   Create a MLCRMSPropOptimizer object
    @param      optimizerDescriptor    The optimizer descriptor object
    @param      momentumScale                 The momentum scale
    @param      alpha                                   The smoothing constant value
    @param      epsilon                              The epsilon value to use to improve numerical stability
    @param      isCentered                            A boolean to specify whether to compute the centered RMSProp or not
    @return     A new MLCRMSPropOptimizer object.
*/
+ (instancetype)optimizerWithDescriptor:(MLCOptimizerDescriptor *)optimizerDescriptor
                          momentumScale:(float)momentumScale
                                  alpha:(float)alpha
                                epsilon:(float)epsilon
                             isCentered:(BOOL)isCentered;

@end

NS_ASSUME_NONNULL_END

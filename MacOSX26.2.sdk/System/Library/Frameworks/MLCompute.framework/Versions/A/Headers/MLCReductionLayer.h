//
//  MLCReductionLayer.m
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <MLCompute/MLCTypes.h>
#import <MLCompute/MLCLayer.h>

@class MLCDevice;
@class MLCTensor;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCReductionLayer
    @abstract   Reduce tensor values across a given dimension to a scalar value.
    @discussion The layer is used to perform reductionType operation on a given dimension.
                Result of this layer is a tensor of the same shape as source tensor,
                except for the given dimension which is set to 1.
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCReductionLayer : MLCLayer

/*! @property   reductionType
    @abstract   The reduction type
 */
@property (readonly, nonatomic) MLCReductionType reductionType;

/*! @property   dimension
    @abstract   The dimension over which to perform the reduction operation
 */
@property (readonly, nonatomic) NSUInteger dimension;

/*! @property   dimensions
    @abstract   The dimensions over which to perform the reduction operation
 */
@property (readonly, nonatomic) NSArray<NSNumber *> *dimensions
    MLCOMPUTE_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5))
    NS_REFINED_FOR_SWIFT;

/*! @abstract Create a reduction layer.
    @param    reductionType        The reduction type.
    @param    dimension          The reduction dimension.
    @return   A new reduction layer.
 */
+ (instancetype _Nullable)layerWithReductionType:(MLCReductionType)reductionType
                                       dimension:(NSUInteger)dimension;

/*! @abstract Create a reduction layer.
    @param    reductionType        The reduction type.
    @param    dimensions               The list of dimensions to reduce over
    @return   A new reduction layer.
 */
+ (instancetype _Nullable)layerWithReductionType:(MLCReductionType)reductionType
                                      dimensions:(NSArray<NSNumber *> *)dimensions
    MLCOMPUTE_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5))
    NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

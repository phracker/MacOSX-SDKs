//
//  MLCMatMulLayer.h
//  MLCompute
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MLCompute/MLCLayer.h>
#import <MLCompute/MLCMatMulDescriptor.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCMatMulLayer
    @abstract   A batched matrix multiplication layer
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCMatMulLayer : MLCLayer

/*! @property   descriptor
    @abstract   The matrix multiplication descriptor
 */
@property (readonly, nonatomic, copy) MLCMatMulDescriptor *descriptor;

/*! @abstract Create a matrix multiply layer
    @param    descriptor A matrix multiply descriptor
    @return   A new layer for matrix multiplication.
 */
+ (instancetype _Nullable)layerWithDescriptor:(MLCMatMulDescriptor *)descriptor;

@end

NS_ASSUME_NONNULL_END


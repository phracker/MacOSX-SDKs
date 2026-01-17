//
//  MLCComparisonLayer.m
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>
#import <MLCompute/MLCLayer.h>

@class MLCDevice;
@class MLCTensor;

NS_ASSUME_NONNULL_BEGIN

/*! @abstract   Compare layer.
 *  @discussion The layer is used to perform element-wise comparison of two tensor. Returns a
 *              tensor with the shape equal to the largest shape of operands and filled
 *              with Boolean values result[i] = op1[i] ? op2[i], where ? corresponds to the
 *              given \p MLCComparisonOperation.
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.3, 14.5, 14.5)
@interface MLCComparisonLayer : MLCLayer

@property (readonly, nonatomic) MLCComparisonOperation operation;

/*!
 @abstract Create a comparison layer.
 @return   A new compare layer.
 */
+ (instancetype)layerWithOperation:(MLCComparisonOperation)operation;

@end

NS_ASSUME_NONNULL_END

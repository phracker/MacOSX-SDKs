//
//  MLCSelectionLayer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MLCompute/MLCLayer.h>

NS_ASSUME_NONNULL_BEGIN

/*! @abstract   Selection layer is used to select elements from two tensors
 *  @discussion The selection layer takes a condition tensor which acts as a mask that chooses whether the corresponding element / row
 *              in the output should be taken from tensor x (if the element in condition is true) or tensor y (if it is false).
 *              The order of source tensors of the layer must be condition tensor, tensor x, and tensor y.
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5))
@interface MLCSelectionLayer : MLCLayer

/*!
 @abstract Create a select layer
 @return   A new layer for selecting elements between two tensors.
 */
+ (instancetype)layer NS_SWIFT_NAME(init());


@end

NS_ASSUME_NONNULL_END


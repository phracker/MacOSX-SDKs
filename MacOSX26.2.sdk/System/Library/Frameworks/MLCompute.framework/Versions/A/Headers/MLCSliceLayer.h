//
//  MLCSliceLayer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MLCompute/MLCLayer.h>
#import <MLCompute/MLCMatMulDescriptor.h>

NS_ASSUME_NONNULL_BEGIN

/*! @abstract   Slice layer is used to slice a given source.
 *  @discussion Slicing should not decrease the tensor dimension.
 *              The start, end and stride vectors must have the same number of dimension as the source tensor.
 *              Only positive stride is supported. 
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCSliceLayer : MLCLayer

/*! @property   start
    @abstract   A vector of length equal to that of source. The element at index i specifies the beginning of slice in dimension i.
 */
@property (readonly, nonatomic, copy) NSArray<NSNumber *> *start NS_REFINED_FOR_SWIFT;

/*! @property   end
    @abstract   A vector of length equal to that of source. The element at index i specifies the end of slice in dimension i.
 */
@property (readonly, nonatomic, copy) NSArray<NSNumber *> *end NS_REFINED_FOR_SWIFT;

/*! @property   stride
    @abstract   A vector of length equal to that of source. The element at index i specifies the stride of slice in dimension i.
 */
@property (readonly, nonatomic, copy, nullable) NSArray<NSNumber *> *stride NS_REFINED_FOR_SWIFT;

/*!
 @abstract Create a slice layer
 @param    stride If set to nil, it will be set to 1.
 @return   A new layer for slicing tensors.
 */
+ (instancetype _Nullable)sliceLayerWithStart:(NSArray<NSNumber *> *)start
                                          end:(NSArray<NSNumber *> *)end
                                       stride:(NSArray<NSNumber *> * _Nullable)stride
   NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

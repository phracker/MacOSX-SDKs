//
//  MLCTransposeLayer.h
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

/*! @class      MLCTransposeLayer
    @abstract   A transpose layer
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCTransposeLayer : MLCLayer

/*! @property   dimensions
    @abstract   Permutes the dimensions according to 'dimensions'.
    @discussion The returned tensor's dimension i will correspond to dimensions[i].
 */
@property (readonly, nonatomic, copy) NSArray<NSNumber *> *dimensions NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a transpose layer
    @param      dimensions NSArray<NSNumber *> representing the desired ordering of dimensions
                The dimensions array specifies the input axis source for each output axis, such that the
                K'th element in the dimensions array specifies the input axis source for the K'th axis in the
                output.  The batch dimension which is typically axis 0 cannot be transposed.
    @return     A new transpose layer.
 */
+ (instancetype _Nullable)layerWithDimensions:(NSArray<NSNumber *> *)dimensions NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

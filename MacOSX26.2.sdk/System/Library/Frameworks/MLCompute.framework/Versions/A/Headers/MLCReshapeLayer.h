//
//  MLCReshapeLayer.h
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

/*! @class      MLCReshapeLayer
    @abstract   A reshape layer.
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCReshapeLayer : MLCLayer

/*! @property   shape
    @abstract   The target shape.
 */
@property (readonly, nonatomic, copy) NSArray<NSNumber *> *shape
    MLCOMPUTE_AVAILABLE_STARTING(macos(11.3), ios(14.5), tvos(14.5))
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Creates a reshape layer with the shape you specify.
 *  @param      shape An array that contains the sizes of each dimension.
 *  @return     A new reshape layer.
 */
+ (instancetype _Nullable)layerWithShape:(NSArray<NSNumber *> *)shape NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

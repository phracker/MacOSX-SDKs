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
    @abstract   A reshape layer
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCReshapeLayer : MLCLayer

/*! @abstract   Create a reshape layer
 *  @param      shape NSArray<NSNumber *> representing the shape of result tensor 
 *  @return     A new reshape layer.
 */
+ (instancetype _Nullable)layerWithShape:(NSArray<NSNumber *> *)shape NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

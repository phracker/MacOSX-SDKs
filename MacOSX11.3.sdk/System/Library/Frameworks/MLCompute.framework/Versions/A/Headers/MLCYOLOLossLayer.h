//
//  MLCYOLOLossLayer.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>
#import <MLCompute/MLCLayer.h>
#import <MLCompute/MLCLossLayer.h>
#import <MLCompute/MLCYOLOLossDescriptor.h>

@class MLCDevice;
@class MLCTensor;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCYOLOLossLayer
    @abstract   A YOLO loss layer
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCYOLOLossLayer : MLCLossLayer

/*! @property   yoloLossDescriptor
    @abstract   The YOLO loss descriptor
 */
@property (readonly, nonatomic, copy) MLCYOLOLossDescriptor *yoloLossDescriptor;

/*! @abstract   Create a YOLO loss layer
 *  @param      lossDescriptor          The loss descriptor
 *  @return     A new YOLO loss layer.
 */
+ (instancetype)layerWithDescriptor:(MLCYOLOLossDescriptor *)lossDescriptor;

@end

NS_ASSUME_NONNULL_END

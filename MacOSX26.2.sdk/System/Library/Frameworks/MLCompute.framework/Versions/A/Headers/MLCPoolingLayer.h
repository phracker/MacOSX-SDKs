//
//  MLCPoolingLayer
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>
#import <MLCompute/MLCLayer.h>

@class MLCDevice;
@class MLCPoolingDescriptor;
@class MLCTensor;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCPoolingLayer
    @abstract   A pooling layer
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCPoolingLayer : MLCLayer

/*! @property   descriptor
    @abstract   The pooling descriptor
 */
@property (readonly, nonatomic, copy) MLCPoolingDescriptor *descriptor;

/*! @abstract   Create a pooling layer
    @param      descriptor  The pooling descriptor
    @return     A new pooling layer
 */
+ (instancetype)layerWithDescriptor:(MLCPoolingDescriptor *)descriptor;

@end



NS_ASSUME_NONNULL_END

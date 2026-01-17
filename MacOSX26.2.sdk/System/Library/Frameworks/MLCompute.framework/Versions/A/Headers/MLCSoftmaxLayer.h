//
//  MLCSoftmaxLayer.h
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

/*! @class      MLCSoftmaxLayer
    @abstract   A softmax layer
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCSoftmaxLayer : MLCLayer

/*! @property   operation
    @abstract   The softmax operation.  Supported values are softmax and log softmax.
 */
@property (readonly, nonatomic) MLCSoftmaxOperation operation;

/*! @property   dimension
    @abstract   The  dimension over which softmax operation should be performed
 */
@property (readonly, nonatomic) NSUInteger dimension;

/*! @abstract   Create a softmax layer
    @param      operation  The softmax operation
    @return     A new softmax layer
 */
+ (instancetype)layerWithOperation:(MLCSoftmaxOperation)operation;

/*! @abstract   Create a softmax layer
    @param      operation  The softmax operation
    @param      dimension  The  dimension over which softmax operation should be performed
    @return     A new softmax layer
 */
+ (instancetype)layerWithOperation:(MLCSoftmaxOperation)operation
                         dimension:(NSUInteger)dimension;

@end

NS_ASSUME_NONNULL_END

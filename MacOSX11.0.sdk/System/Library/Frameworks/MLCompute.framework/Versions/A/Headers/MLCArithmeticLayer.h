//
//  MLCArithmeticLayer.h
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

/*! @class      MLCArithmeticLayer
    @abstract   An arithmetic layer
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCArithmeticLayer : MLCLayer

/*! @property   operation
    @abstract   The arithmetic operation.
 */
@property (readonly, nonatomic) MLCArithmeticOperation operation;

/*! @abstract   Create an arithmetic layer
    @param      operation    The arithmetic operation
    @return     A new arithmetic layer
 */
+ (instancetype)layerWithOperation:(MLCArithmeticOperation)operation;

@end

NS_ASSUME_NONNULL_END


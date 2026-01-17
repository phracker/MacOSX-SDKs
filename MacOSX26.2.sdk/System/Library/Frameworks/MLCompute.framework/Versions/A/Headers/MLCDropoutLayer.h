//
//  MLCDropoutLayer.h
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

/*! @class      MLCDropoutLayer
    @abstract   A dropout layer
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCDropoutLayer : MLCLayer

/*! @property   rate
    @abstract   The probability that each element is dropped
 */
@property (readonly, nonatomic) float rate;

/*! @property   seed
    @abstract   The initial seed used to generate random numbers
 */
@property (readonly, nonatomic) NSUInteger seed;

/*! @abstract   Create a dropout layer
    @param      rate  A scalar float value. The probability that each element is dropped.
    @param      seed  The seed used to generate random numbers.
    @return     A new dropout layer
 */
+ (instancetype)layerWithRate:(float)rate
                         seed:(NSUInteger)seed;

@end

NS_ASSUME_NONNULL_END



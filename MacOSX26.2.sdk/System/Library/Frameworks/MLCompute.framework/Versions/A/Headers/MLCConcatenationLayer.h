//
//  MLCConcatenationLayer.h
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


/*! @class      MLCConcatenationLayer
    @abstract   A concatenation layer
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCConcatenationLayer : MLCLayer

/*! @property   dimension
    @abstract   The dimension (or axis) along which to concatenate tensors
    @discussion The default value is 1 (which typically represents features channels)
 */
@property (readonly, nonatomic) NSUInteger dimension;

/*! @abstract   Create a concatenation layer
    @return     A new concatenation layer
 */
+ (instancetype)layer
    NS_SWIFT_NAME(init());

/*! @abstract   Create a concatenation layer
    @param      dimension  The concatenation dimension
    @return     A new concatenation layer
 */
+ (instancetype)layerWithDimension:(NSUInteger)dimension;

@end

NS_ASSUME_NONNULL_END

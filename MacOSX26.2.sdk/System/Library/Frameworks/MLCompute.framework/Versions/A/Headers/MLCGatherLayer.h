//
//  MLCGatherLayer.h
//  MLCompute
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <MLCompute/MLCDefines.h>
#import <MLCompute/MLCTypes.h>
#import <MLCompute/MLCLayer.h>

@class MLCTensor;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCGatherLayer
    @abstract   A gather layer
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.3, 14.5, 14.5)
@interface MLCGatherLayer : MLCLayer

/*! @property   dimension
    @abstract   The dimension along which to index
 */
@property (readonly, nonatomic) NSUInteger dimension;

/*! @abstract   Create a gather layer
    @param      dimension  The dimension along which to index
    @return     A new gather layer
 */
+ (instancetype)layerWithDimension:(NSUInteger)dimension;

@end

NS_ASSUME_NONNULL_END




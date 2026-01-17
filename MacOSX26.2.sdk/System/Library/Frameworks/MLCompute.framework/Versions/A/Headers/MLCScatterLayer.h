//
//  MLCScatterLayer.h
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

/*! @class      MLCScatterLayer
    @abstract   A scatter layer
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.3, 14.5, 14.5)
@interface MLCScatterLayer : MLCLayer

/*! @property   dimension
    @abstract   The dimension along which to index
 */
@property (readonly, nonatomic) NSUInteger dimension;

/*! @property   reductionType
    @abstract   The reduction type applied for all values in source tensor that are scattered to a specific location in the result tensor.
                Must be: MLCReductionTypeNone or MLCReductionTypeSum. 
 */
@property (readonly, nonatomic) MLCReductionType reductionType;

/*! @abstract   Create a scatter layer
    @param      dimension  The dimension along which to index
    @param      reductionType  The reduction type to use
    @return     A new scatter layer
 */
+ (instancetype _Nullable)layerWithDimension:(NSUInteger)dimension
                               reductionType:(MLCReductionType)reductionType;

@end

NS_ASSUME_NONNULL_END





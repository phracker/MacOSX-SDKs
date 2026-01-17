//
//  MLCPaddingLayer.h
//  MLCompute
//
// Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MLCompute/MLCTypes.h>
#import <MLCompute/MLCLayer.h>

@class MLCDevice;

NS_ASSUME_NONNULL_BEGIN

/*! @class      MLCPaddingLayer
    @abstract   A padding layer
 */
MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(11.0, 14.0, 14.0)
@interface MLCPaddingLayer : MLCLayer<NSCopying>

/*! @property   paddingType
    @abstract   The padding type i.e. constant, zero, reflect or symmetric
 */
@property(readonly, nonatomic) MLCPaddingType paddingType;

/*! @property   paddingLeft
    @abstract   The left padding size
 */
@property(readonly, nonatomic) NSUInteger paddingLeft;

/*! @property   paddingRight
    @abstract   The right padding size
 */
@property(readonly, nonatomic) NSUInteger paddingRight;

/*! @property   paddingTop
    @abstract   The top padding size
 */
@property(readonly, nonatomic) NSUInteger paddingTop;

/*! @property   paddingBottom
    @abstract   The bottom padding size
 */
@property(readonly, nonatomic) NSUInteger paddingBottom;

/*! @property   constantValue
    @abstract   The constant value to use if padding type is constant.
 */
@property(readonly, nonatomic) float constantValue;

/*! @abstract   Create a padding layer with reflection padding
    @param      padding  The padding sizes.
    @return     A new padding layer
 */
+ (instancetype)layerWithReflectionPadding:(NSArray<NSNumber *> *)padding
   NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a padding layer with symmetric padding
    @param      padding  The padding sizes.
    @return     A new padding layer
 */
+ (instancetype)layerWithSymmetricPadding:(NSArray<NSNumber *> *)padding
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a padding layer with zero padding
    @param      padding  The padding sizes.
    @return     A new padding layer
 */
+ (instancetype)layerWithZeroPadding:(NSArray<NSNumber *> *)padding
    NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a padding layer with constant padding
    @param      padding                 The padding sizes.
    @param      constantValue   The constant value to pad the source tensor.
    @return     A new padding layer
 */
+ (instancetype)layerWithConstantPadding:(NSArray<NSNumber *> *)padding
                           constantValue:(float)constantValue
    NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

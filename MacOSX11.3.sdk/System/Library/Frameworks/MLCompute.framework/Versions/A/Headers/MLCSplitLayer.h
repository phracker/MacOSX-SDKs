//
//  MLCSplitLayer.h
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

/*! @class      MLCSplitLayer
    @abstract   A split layer
 */
MLCOMPUTE_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MLCSplitLayer : MLCLayer

/*! @property   dimension
    @abstract   The dimension (or axis) along which to split tensor
 */
@property(readonly, nonatomic) NSUInteger dimension;

/*! @property   splitCount
    @abstract   The number of splits.
    @discussion The tensor will be split into equally sized chunks.  The last chunk may be smaller in size.
 */
@property(readonly, nonatomic) NSUInteger splitCount;

/*! @property   splitSectionLengths
    @abstract   Lengths of each split section.
    @discussion The tensor will be split into chunks along dimensions with sizes given in \p splitSectionLengths .
 */
@property(readonly, nonatomic, nullable, copy) NSArray<NSNumber *> *splitSectionLengths NS_REFINED_FOR_SWIFT;

/*! @abstract   Create a split layer
    @param      splitCount  The number of splits.
    @param      dimension   The dimension along which the tensor should be split.
    @return     A new split layer
*/
+ (instancetype)layerWithSplitCount:(NSUInteger)splitCount
                          dimension:(NSUInteger)dimension;

/*! @abstract   Create a split layer
    @param      splitSectionLengths   Lengths of each split section.
    @param      dimension             The dimension along which the tensor should be split.
    @return     A new split layer
*/
+ (instancetype)layerWithSplitSectionLengths:(NSArray<NSNumber *> *)splitSectionLengths
                                   dimension:(NSUInteger)dimension
    NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END

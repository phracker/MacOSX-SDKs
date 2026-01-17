//
//  SCNMorpher.h
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNMorpher
 @abstract SCNMorpher controls the deformation of morphed geometries
 */

typedef NS_ENUM(NSInteger, SCNMorpherCalculationMode) {
    SCNMorpherCalculationModeNormalized, // (1 - w0 - w1 - ...) * BaseMesh + w0 * Target0 + w1 * Target1 + ...
    SCNMorpherCalculationModeAdditive    // BaseMesh + w0 * Target0 + w1 * Target1 + ...
};

NS_CLASS_AVAILABLE(10_9, 8_0)
@interface SCNMorpher : NSObject <SCNAnimatable, NSSecureCoding>

/*!
 @property targets
 @abstract Specifies the morph targets as an array of SCNGeometry.
 @discussion The target geometries must have the same number of entries in their geometry sources and the same topology as the base geometry.
 */
@property(nonatomic, copy) NSArray<SCNGeometry *> *targets;

/*!
 @method setWeight:forTargetAtIndex:
 @abstract Sets the weight for the target at the specified index. Animatable implicitly or explicitly with the keyPath "weights[index]".
 */
- (void)setWeight:(CGFloat)weight forTargetAtIndex:(NSUInteger)targetIndex;

/*!
 @method weightForTargetAtIndex:
 @abstract Retrieves the weight for the target at the specified index.
 */
- (CGFloat)weightForTargetAtIndex:(NSUInteger)targetIndex;

/*!
 @property calculationMode
 @abstract Specifies how the morph result is calculated by the receiver. Defaults to SCNMorpherCalculationModeNormalized.
 */
@property(nonatomic) SCNMorpherCalculationMode calculationMode;

@end

NS_ASSUME_NONNULL_END

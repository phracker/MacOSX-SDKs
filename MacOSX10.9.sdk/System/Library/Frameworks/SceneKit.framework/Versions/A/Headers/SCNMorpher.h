//
//  SCNMorpher.h
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>

/*!
 @class SCNMorpher
 @abstract SCNMorpher controls the deformation of morphed geometries
 */

typedef NS_ENUM(NSInteger, SCNMorpherCalculationMode) {
    SCNMorpherCalculationModeNormalized, // (1 - w1 - w2 - ...) * BaseMesh + w1 * Target1 + w2 * Target2 + ...
    SCNMorpherCalculationModeAdditive    // BaseMesh + w1 * Target1 + w2 * Target2 + ...
};

SCENEKIT_CLASS_AVAILABLE(10_9, NA)
@interface SCNMorpher : NSObject <SCNAnimatable> {
@private
	id _reserved;
}

/*!
 @property targets
 @abstract Specifies the morph targets as an array of SCNGeometry.
 @discussion The target geometries must have the same number of entries in their geometry sources and the same topology as the base geometry.
 */
@property(nonatomic, copy) NSArray *targets;

/*!
 @method setWeight:forTargetAtIndex:
 @abstract Sets the weight for the target at the specified index. Animatable implicitly or explicitly with the keyPath "weight[index]".
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

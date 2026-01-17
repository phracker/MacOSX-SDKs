//
//  SCNSkinner.h
//
//  Copyright (c) 2013-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class SCNSkinner
 @abstract SCNSkinner controls the deformation of skinned geometries */

NS_CLASS_AVAILABLE(10_9, 8_0)
@interface SCNSkinner : NSObject <NSSecureCoding>

/*!
 @property skeleton
 @abstract Specifies the skeleton of the receiver.
 @discussion When setting a new skeleton, the new skeleton must have the same hierarchy of joints.
 */
@property(nonatomic, retain, nullable) SCNNode *skeleton;

/*!
 @method skinnerWithBaseGeometry:bones:boneInverseBindTransforms:boneWeights:boneIndices:
 @abstract Creates and initialize a skinner instance with the specified parameters.
 @param baseGeometry Specifies the base geometry used by the skinner
 @param bones Specifies the array of bones.
 @param boneInverseBindTransforms The inverse of the bone’s bind-space transformation matrix at the time the bind shape was bound to this bone.
 @param boneWeights A buffer of weights. This contains the weights of every influence of every vertex. The number of influence per vertex is controlled by the number of component in the geometry source.
 @param boneIndices A buffer of bone indexes. This buffer contains the corresponding index in the bones array for every weight in the weights buffer.
 */
+ (instancetype)skinnerWithBaseGeometry:(nullable SCNGeometry *)baseGeometry bones:(NSArray<SCNNode *> *)bones boneInverseBindTransforms:(nullable NSArray<NSValue *> *)boneInverseBindTransforms boneWeights:(SCNGeometrySource *)boneWeights boneIndices:(SCNGeometrySource *)boneIndices NS_AVAILABLE(10_10, 8_0);

/*!
 @property baseGeometry
 @abstract Specifies the base geometry of the receiver.
 @discussion Updating this will change the geometry of all the nodes sharing the skinner.
 Access the node's geometry if you want to update this specific skinner properties (materials for example).
 Access this property if you want a whole new geometry (which will necessarily be shared among the skinner instances), with
 different sources, for instance.
 */
@property(retain, nonatomic, nullable) SCNGeometry *baseGeometry NS_AVAILABLE(10_9, 8_0);

/*!
 @property baseGeometryBindTransform
 @abstract Specifies the transform of the baseGeometry at the time when the mesh was bound to a skeleton. This transforms the baseGeometry from object space to a space on which the skinning then applies.
 */
@property(nonatomic) SCNMatrix4 baseGeometryBindTransform NS_AVAILABLE(10_10, 8_0);

/*!
 @property boneInverseBindTransforms
 @abstract The inverse of the bone’s bind-space transformation matrix at the time the bind shape was bound to this bone.
 @discussion boneInverseBindTransforms is an array of SCNMatrix4 wrapped into instances of NSValue.
 */
@property(readonly, nonatomic, nullable) NSArray<NSValue *> *boneInverseBindTransforms NS_AVAILABLE(10_10, 8_0);

/*!
 @property bones
 @abstract The bones of the skinner.
 */
@property(readonly, nonatomic) NSArray<SCNNode *> *bones NS_AVAILABLE(10_10, 8_0);

/*!
 @property boneWeights
 @abstract The bone weights of the receiver.
 */
@property(readonly, nonatomic) SCNGeometrySource *boneWeights NS_AVAILABLE(10_10, 8_0);

/*!
 @property boneIndices
 @abstract The bone indices of the receiver.
 */
@property(readonly, nonatomic) SCNGeometrySource *boneIndices NS_AVAILABLE(10_10, 8_0);

@end

NS_ASSUME_NONNULL_END

//
//  SCNSkinner.h
//  SceneKit
//
//  Copyright © 2013-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNGeometry;
@class SCNGeometrySource;

/*!
 @class SCNSkinner
 @abstract SCNSkinner controls the deformation of skinned geometries */

SCN_EXPORT API_AVAILABLE(macos(10.9))
@interface SCNSkinner : NSObject <NSSecureCoding>

/*!
 @property skeleton
 @abstract Specifies the skeleton of the receiver.
 @discussion When setting a new skeleton, the new skeleton must have the same hierarchy of joints.
 */
@property(nonatomic, weak, nullable) SCNNode *skeleton;

/*!
 @method skinnerWithBaseGeometry:bones:boneInverseBindTransforms:boneWeights:boneIndices:
 @abstract Creates and initialize a skinner instance with the specified parameters.
 @param baseGeometry Specifies the base geometry used by the skinner
 @param bones Specifies the array of bones.
 @param boneInverseBindTransforms The inverse of the bone’s bind-space transformation matrix at the time the bind shape was bound to this bone.
 @param boneWeights A buffer of weights. This contains the weights of every influence of every vertex. The number of influence per vertex is controlled by the number of component in the geometry source.
 @param boneIndices A buffer of bone indexes. This buffer contains the corresponding index in the bones array for every weight in the weights buffer.
 */
+ (instancetype)skinnerWithBaseGeometry:(nullable SCNGeometry *)baseGeometry bones:(NSArray<SCNNode *> *)bones boneInverseBindTransforms:(nullable NSArray<NSValue *> *)boneInverseBindTransforms boneWeights:(SCNGeometrySource *)boneWeights boneIndices:(SCNGeometrySource *)boneIndices API_AVAILABLE(macos(10.10));

/*!
 @property baseGeometry
 @abstract Specifies the base geometry of the receiver.
 @discussion Updating this will change the geometry of all the nodes sharing the skinner.
 Access the node's geometry if you want to update this specific skinner properties (materials for example).
 Access this property if you want a whole new geometry (which will necessarily be shared among the skinner instances), with
 different sources, for instance.
 */
@property(retain, nonatomic, nullable) SCNGeometry *baseGeometry API_AVAILABLE(macos(10.9));

/*!
 @property baseGeometryBindTransform
 @abstract Specifies the transform of the baseGeometry at the time when the mesh was bound to a skeleton. This transforms the baseGeometry from object space to a space on which the skinning then applies.
 */
@property(nonatomic) SCNMatrix4 baseGeometryBindTransform API_AVAILABLE(macos(10.10));

/*!
 @property boneInverseBindTransforms
 @abstract The inverse of the bone’s bind-space transformation matrix at the time the bind shape was bound to this bone.
 @discussion boneInverseBindTransforms is an array of SCNMatrix4 wrapped into instances of NSValue.
 */
@property(readonly, nonatomic, nullable) NSArray<NSValue *> *boneInverseBindTransforms API_AVAILABLE(macos(10.10));

/*!
 @property bones
 @abstract The bones of the skinner.
 */
@property(readonly, nonatomic) NSArray<SCNNode *> *bones API_AVAILABLE(macos(10.10));

/*!
 @property boneWeights
 @abstract The bone weights of the receiver.
 */
@property(readonly, nonatomic) SCNGeometrySource *boneWeights API_AVAILABLE(macos(10.10));

/*!
 @property boneIndices
 @abstract The bone indices of the receiver.
 */
@property(readonly, nonatomic) SCNGeometrySource *boneIndices API_AVAILABLE(macos(10.10));

@end

NS_ASSUME_NONNULL_END

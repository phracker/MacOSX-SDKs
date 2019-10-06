//
//  SCNHitTest.h
//  SceneKit
//
//  Copyright © 2012-2019 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/*! @enum SCNHitTestSearchMode
 @abstract hit test modes
 */
typedef NS_ENUM(NSInteger, SCNHitTestSearchMode) {
    SCNHitTestSearchModeClosest = 0, // The closest object found.
    SCNHitTestSearchModeAll     = 1, // All found objects sorted from nearest to farthest.
    SCNHitTestSearchModeAny     = 2  // The first object found. This object is not necessarily the nearest.
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*! @group Hit-test options */

typedef NSString * SCNHitTestOption NS_STRING_ENUM;
SCN_EXPORT SCNHitTestOption const SCNHitTestClipToZRangeKey;                                                                        // If set to YES ignores the objects clipped by the zNear/zFar range of the current point of view. Defaults to YES.
SCN_EXPORT SCNHitTestOption const SCNHitTestBackFaceCullingKey;                                                                     // If set to YES ignores the faces not facing to the camera. Defaults to YES.
SCN_EXPORT SCNHitTestOption const SCNHitTestBoundingBoxOnlyKey;                                                                     // If set to YES only tests the bounding boxes of the 3D objects. Defaults to NO.
SCN_EXPORT SCNHitTestOption const SCNHitTestIgnoreChildNodesKey;                                                                    // Determines whether the child nodes are ignored. Defaults to NO.
SCN_EXPORT SCNHitTestOption const SCNHitTestRootNodeKey;                                                                            // Specifies the root node to use for the hit test. Defaults to the root node of the scene.
SCN_EXPORT SCNHitTestOption const SCNHitTestIgnoreHiddenNodesKey  API_AVAILABLE(macos(10.9));                                       // Determines whether hidden nodes should be ignored. Defaults to YES.
SCN_EXPORT SCNHitTestOption const SCNHitTestOptionCategoryBitMask API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));               // Determines the node categories to test. Defaults to all bits set.
SCN_EXPORT SCNHitTestOption const SCNHitTestOptionSearchMode      API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)); // Determines whether the search should be exhaustive. Defaults to SCNHitTestSearchModeClosest.
SCN_EXPORT SCNHitTestOption const SCNHitTestOptionIgnoreLightArea API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0)); // Determines whether the shape of an area light should not be taken into account. Defaults to YES.

SCN_EXPORT SCNHitTestOption const SCNHitTestFirstFoundOnlyKey;                                                                      // Deprecated, use SCNHitTestSearchModeAny for the SCNHitTestOptionSearchMode option instead
SCN_EXPORT SCNHitTestOption const SCNHitTestSortResultsKey;                                                                         // Deprecated, use SCNHitTestSearchModeAll for the SCNHitTestOptionSearchMode option instead

#define SCNHitTestOptionFirstFoundOnly    SCNHitTestFirstFoundOnlyKey
#define SCNHitTestOptionSortResults       SCNHitTestSortResultsKey
#define SCNHitTestOptionClipToZRange      SCNHitTestClipToZRangeKey
#define SCNHitTestOptionBackFaceCulling   SCNHitTestBackFaceCullingKey
#define SCNHitTestOptionBoundingBoxOnly   SCNHitTestBoundingBoxOnlyKey
#define SCNHitTestOptionIgnoreChildNodes  SCNHitTestIgnoreChildNodesKey
#define SCNHitTestOptionRootNode          SCNHitTestRootNodeKey
#define SCNHitTestOptionIgnoreHiddenNodes SCNHitTestIgnoreHiddenNodesKey

/*! @class SCNHitTestResult
 @abstract Results returned by the hit-test methods.
 */

SCN_EXPORT
@interface SCNHitTestResult : NSObject

/*! The hit node. */
@property(nonatomic, readonly) SCNNode *node;

/*! Index of the hit geometry element. */
@property(nonatomic, readonly) NSInteger geometryIndex;

/*! Index of the hit primitive of the geometry element. */
@property(nonatomic, readonly) NSInteger faceIndex;

/*! Intersection point in the node's local coordinate system. */
@property(nonatomic, readonly) SCNVector3 localCoordinates;

/*! Intersection point in the world coordinate system. */
@property(nonatomic, readonly) SCNVector3 worldCoordinates;

/*! Intersection normal in the node's local coordinate system. */
@property(nonatomic, readonly) SCNVector3 localNormal;

/*! Intersection normal in the world coordinate system. */
@property(nonatomic, readonly) SCNVector3 worldNormal;

/*! World transform of the hit node. */
@property(nonatomic, readonly) SCNMatrix4 modelTransform;

/*! The hit bone. Only available if the node hit has a SCNSkinner attached. */
@property(nonatomic, readonly, nullable) SCNNode *boneNode API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @method textureCoordinatesWithMappingChannel:
 @abstract Returns the texture coordinates at the point of intersection, for a given mapping channel.
 @param channel The texture coordinates source index of the geometry to use. The channel must exists on the geometry otherwise {0,0} will be returned.
 */
- (CGPoint)textureCoordinatesWithMappingChannel:(NSInteger)channel;

@end

@interface SCNHitTestResult (SIMD)

@property(nonatomic, readonly) simd_float3 simdLocalCoordinates API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));
@property(nonatomic, readonly) simd_float3 simdWorldCoordinates API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));
@property(nonatomic, readonly) simd_float3 simdLocalNormal API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));
@property(nonatomic, readonly) simd_float3 simdWorldNormal API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));
@property(nonatomic, readonly) simd_float4x4 simdModelTransform API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

@end

NS_ASSUME_NONNULL_END

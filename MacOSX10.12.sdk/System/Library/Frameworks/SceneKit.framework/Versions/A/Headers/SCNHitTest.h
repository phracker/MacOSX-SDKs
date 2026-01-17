//
//  SCNHitTest.h
//
//  Copyright (c) 2012-2016 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;

/*! @group Hit-test options */

#if defined(SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH) && SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH >= 3
typedef NSString * SCNHitTestOption NS_STRING_ENUM;
#else
typedef NSString * SCNHitTestOption;
#endif

FOUNDATION_EXTERN SCNHitTestOption const SCNHitTestFirstFoundOnlyKey;                                                         // If set to YES, returns the first object found. This object is not necessarily the nearest. Defaults to NO.
FOUNDATION_EXTERN SCNHitTestOption const SCNHitTestSortResultsKey;                                                            // Determines whether the results should be sorted. If set to YES sorts nearest objects first. Defaults to YES.
FOUNDATION_EXTERN SCNHitTestOption const SCNHitTestClipToZRangeKey;                                                           // If set to YES ignores the objects clipped by the zNear/zFar range of the current point of view. Defaults to YES.
FOUNDATION_EXTERN SCNHitTestOption const SCNHitTestBackFaceCullingKey;                                                        // If set to YES ignores the faces not facing to the camera. Defaults to YES.
FOUNDATION_EXTERN SCNHitTestOption const SCNHitTestBoundingBoxOnlyKey;                                                        // If set to YES only tests the bounding boxes of the 3D objects. Defaults to NO.
FOUNDATION_EXTERN SCNHitTestOption const SCNHitTestIgnoreChildNodesKey;                                                       // Determines whether the child nodes are ignored. Defaults to NO.
FOUNDATION_EXTERN SCNHitTestOption const SCNHitTestRootNodeKey;                                                               // Specifies the root node to use for the hit test. Defaults to the root node of the scene.
FOUNDATION_EXTERN SCNHitTestOption const SCNHitTestIgnoreHiddenNodesKey  API_AVAILABLE(macosx(10.9));                         // Determines whether hidden nodes should be ignored. Defaults to YES.
FOUNDATION_EXTERN SCNHitTestOption const SCNHitTestOptionCategoryBitMask API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0)); // Determines the node categories to test. Defaults to all bits set.

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

@interface SCNHitTestResult : NSObject

/*! The node hit. */
@property(nonatomic, readonly) SCNNode *node;

/*! Index of the geometry hit. */
@property(nonatomic, readonly) NSInteger geometryIndex;

/*! Index of the face hit. */
@property(nonatomic, readonly) NSInteger faceIndex;

/*! Intersection point in the node local coordinate system. */
@property(nonatomic, readonly) SCNVector3 localCoordinates;

/*! Intersection point in the world coordinate system. */
@property(nonatomic, readonly) SCNVector3 worldCoordinates;

/*! Intersection normal in the node local coordinate system. */
@property(nonatomic, readonly) SCNVector3 localNormal;

/*! Intersection normal in the world coordinate system. */
@property(nonatomic, readonly) SCNVector3 worldNormal;

/*! World transform of the node intersected. */
@property(nonatomic, readonly) SCNMatrix4 modelTransform;

/*! The bone node hit. Only available if the node hit has a SCNSkinner attached. */
@property(nonatomic, readonly) SCNNode *boneNode API_AVAILABLE(macosx(10.12), ios(10.0), tvos(10.0));

/*!
 @method textureCoordinatesWithMappingChannel:
 @abstract Returns the texture coordinates at the point of intersection, for a given mapping channel.
 @param channel The texture coordinates source index of the geometry to use. The channel must exists on the geometry otherwise {0,0} will be returned.
 */
- (CGPoint)textureCoordinatesWithMappingChannel:(NSInteger)channel;

@end

NS_ASSUME_NONNULL_END

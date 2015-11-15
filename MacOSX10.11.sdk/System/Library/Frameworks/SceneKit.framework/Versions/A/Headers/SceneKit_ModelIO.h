//
//  SceneKit_ModelIO.h
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.
//

@class MDLAsset, MDLObject, MDLMesh, MDLSubmesh, MDLMaterial, MDLLight, MDLCamera;


NS_ASSUME_NONNULL_BEGIN

/*! 
 @header SceneKit_ModelIO.h
 @abstract Bridge with the ModelIO framework
 */

/* ModelIO to SceneKit */
@interface SCNScene (SCNModelIOBridge)
+ (instancetype)sceneWithMDLAsset:(MDLAsset *)mdlAsset NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNNode (SCNModelIOBridge)
+ (instancetype)nodeWithMDLObject:(MDLObject *)mdlObject NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNGeometry (SCNModelIOBridge)
+ (instancetype)geometryWithMDLMesh:(MDLMesh *)mdlMesh NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNGeometryElement (SCNModelIOBridge)
+ (instancetype)geometryElementWithMDLSubmesh:(MDLSubmesh *)mdlSubMesh NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNMaterial (SCNModelIOBridge)
+ (instancetype)materialWithMDLMaterial:(MDLMaterial *)mdlMaterial NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNLight (SCNModelIOBridge)
+ (instancetype)lightWithMDLLight:(MDLLight *)mdlLight NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNCamera (SCNModelIOBridge)
+ (instancetype)cameraWithMDLCamera:(MDLCamera *)mdlCamera NS_AVAILABLE(10_11, 9_0);
@end

NS_ASSUME_NONNULL_END


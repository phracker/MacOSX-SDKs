//
//  ModelIO.h
//  SceneKit
//
//  Copyright © 2015-2018 Apple Inc. All rights reserved.
//

#import <ModelIO/ModelIO.h>

#import <SceneKit/SCNNode.h>
#import <SceneKit/SCNScene.h>
#import <SceneKit/SCNLight.h>
#import <SceneKit/SCNCamera.h>
#import <SceneKit/SCNGeometry.h>
#import <SceneKit/SCNMaterial.h>

NS_ASSUME_NONNULL_BEGIN

/*! 
 @header ModelIO.h
 @abstract Bridge with the Model I/O framework
 */

@interface SCNScene (SCNModelIO)
+ (instancetype)sceneWithMDLAsset:(MDLAsset *)mdlAsset API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLAsset (SCNModelIO)
+ (instancetype)assetWithSCNScene:(SCNScene *)scnScene API_AVAILABLE(macos(10.11), ios(9.0));
+ (instancetype)assetWithSCNScene:(SCNScene *)scnScene bufferAllocator:(nullable id <MDLMeshBufferAllocator>)bufferAllocator API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));
@end

@interface SCNNode (SCNModelIO)
+ (instancetype)nodeWithMDLObject:(MDLObject *)mdlObject API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLObject (SCNModelIO)
+ (instancetype)objectWithSCNNode:(SCNNode *)scnNode API_AVAILABLE(macos(10.11), ios(9.0));
+ (instancetype)objectWithSCNNode:(SCNNode *)scnNode bufferAllocator:(nullable id <MDLMeshBufferAllocator>)bufferAllocator API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));
@end

@interface SCNGeometry (SCNModelIO)
+ (instancetype)geometryWithMDLMesh:(MDLMesh *)mdlMesh API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLMesh (SCNModelIO)
+ (instancetype)meshWithSCNGeometry:(SCNGeometry *)scnGeometry API_AVAILABLE(macos(10.11), ios(9.0));
+ (instancetype)meshWithSCNGeometry:(SCNGeometry *)scnGeometry bufferAllocator:(nullable id <MDLMeshBufferAllocator>)bufferAllocator API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));
@end

@interface SCNGeometryElement (SCNModelIO)
+ (instancetype)geometryElementWithMDLSubmesh:(MDLSubmesh *)mdlSubMesh API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLSubmesh (SCNModelIO)
+ (instancetype)submeshWithSCNGeometryElement:(SCNGeometryElement *)scnGeometryElement API_AVAILABLE(macos(10.11), ios(9.0));
+ (instancetype)submeshWithSCNGeometryElement:(SCNGeometryElement *)scnGeometryElement bufferAllocator:(nullable id <MDLMeshBufferAllocator>)bufferAllocator API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));
@end

@interface SCNMaterial (SCNModelIO)
+ (instancetype)materialWithMDLMaterial:(MDLMaterial *)mdlMaterial API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLMaterial (SCNModelIO)
+ (instancetype)materialWithSCNMaterial:(SCNMaterial *)scnMaterial API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface SCNLight (SCNModelIO)
+ (instancetype)lightWithMDLLight:(MDLLight *)mdlLight API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLLight (SCNModelIO)
+ (instancetype)lightWithSCNLight:(SCNLight *)scnLight API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface SCNCamera (SCNModelIO)
+ (instancetype)cameraWithMDLCamera:(MDLCamera *)mdlCamera API_AVAILABLE(macos(10.11), ios(9.0));
@end

@interface MDLCamera (SCNModelIO)
+ (instancetype)cameraWithSCNCamera:(SCNCamera *)scnCamera API_AVAILABLE(macos(10.11), ios(9.0));
@end

NS_ASSUME_NONNULL_END

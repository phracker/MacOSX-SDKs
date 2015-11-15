//
//  ModelIO.h
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <ModelIO/ModelIO.h>

NS_ASSUME_NONNULL_BEGIN

/*! 
 @header ModelIO.h
 @abstract Bridge with the Model I/O framework
 */

@interface SCNScene (SCNModelIO)
+ (instancetype)sceneWithMDLAsset:(MDLAsset *)mdlAsset NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLAsset (SCNModelIO)
+ (instancetype)assetWithSCNScene:(SCNScene *)scnScene NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNNode (SCNModelIO)
+ (instancetype)nodeWithMDLObject:(MDLObject *)mdlObject NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLObject (SCNModelIO)
+ (instancetype)objectWithSCNNode:(SCNNode *)scnNode NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNGeometry (SCNModelIO)
+ (instancetype)geometryWithMDLMesh:(MDLMesh *)mdlMesh NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLMesh (SCNModelIO)
+ (instancetype)meshWithSCNGeometry:(SCNGeometry *)scnGeometry NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNGeometryElement (SCNModelIO)
+ (instancetype)geometryElementWithMDLSubmesh:(MDLSubmesh *)mdlSubMesh NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLSubmesh (SCNModelIO)
+ (instancetype)submeshWithSCNGeometryElement:(SCNGeometryElement *)scnGeometryElement NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNMaterial (SCNModelIO)
+ (instancetype)materialWithMDLMaterial:(MDLMaterial *)mdlMaterial NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLMaterial (SCNModelIO)
+ (instancetype)materialWithSCNMaterial:(SCNMaterial *)scnMaterial NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNLight (SCNModelIO)
+ (instancetype)lightWithMDLLight:(MDLLight *)mdlLight NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLLight (SCNModelIO)
+ (instancetype)lightWithSCNLight:(SCNLight *)scnLight NS_AVAILABLE(10_11, 9_0);
@end

@interface SCNCamera (SCNModelIO)
+ (instancetype)cameraWithMDLCamera:(MDLCamera *)mdlCamera NS_AVAILABLE(10_11, 9_0);
@end

@interface MDLCamera (SCNModelIO)
+ (instancetype)cameraWithSCNCamera:(SCNCamera *)scnCamera NS_AVAILABLE(10_11, 9_0);
@end

NS_ASSUME_NONNULL_END

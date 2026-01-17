//
//  ARSCNFaceGeometry.h
//  ARKit
//
//  Copyright © 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>

@protocol MTLDevice;
@class ARFaceGeometry;

NS_ASSUME_NONNULL_BEGIN

/**
 A SceneKit geometry representing a face.
 */
API_AVAILABLE(ios(11.0))
@interface ARSCNFaceGeometry : SCNGeometry

/**
 Creates a new face geometry using a Metal device.
 
 @param device A Metal device.
 @return A new face geometry.
 */
+ (nullable instancetype)faceGeometryWithDevice:(id<MTLDevice>)device;

/**
 Creates a new face geometry using a Metal device.
 
 @discussion By default the regions between the eye lids as well as the region
 between the lips are not covered by geometry. For using the face geometry as an
 occlusion geometry set \p fillMesh to YES. This will fill
 in additional geometry into the gaps between the eye lids as well as into the
 gap between the lips.
 @param fillMesh Whether to fill in additional geometry into the
 gaps between the eye lids as well as into the gap between the lips.
 
 @return A new face geometry.
 */
+ (nullable instancetype)faceGeometryWithDevice:(id<MTLDevice>)device
                              fillMesh:(BOOL)fillMesh;

/**
 Updates the geometry with the vertices of a face geometry.
 
 @param faceGeometry A face geometry.
 */
- (void)updateFromFaceGeometry:(ARFaceGeometry *)faceGeometry;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

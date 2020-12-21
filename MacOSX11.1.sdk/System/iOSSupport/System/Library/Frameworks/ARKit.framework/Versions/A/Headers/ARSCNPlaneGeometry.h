//
//  ARSCNPlaneGeometry.h
//  ARKit
//
//  Copyright © 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNGeometry.h>

@protocol MTLDevice;
@class ARPlaneGeometry;

NS_ASSUME_NONNULL_BEGIN

/**
 A SceneKit geometry representing a plane.
 */
API_AVAILABLE(ios(11.3))
@interface ARSCNPlaneGeometry : SCNGeometry

/**
 Creates a new plane geometry using a Metal device.
 
 @param device A Metal device.
 @return A new plane geometry.
 */
+ (nullable instancetype)planeGeometryWithDevice:(id<MTLDevice>)device;

/**
 Updates the geometry with the vertices of a plane geometry.
 
 @param planeGeometry A plane geometry.
 */
- (void)updateFromPlaneGeometry:(ARPlaneGeometry *)planeGeometry;

@end

NS_ASSUME_NONNULL_END

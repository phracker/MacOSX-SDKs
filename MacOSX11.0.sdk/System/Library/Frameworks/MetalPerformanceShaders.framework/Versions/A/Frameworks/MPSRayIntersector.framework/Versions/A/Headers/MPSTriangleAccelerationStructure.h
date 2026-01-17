/*!
 *  @header MPSTriangleAccelerationStructure.h
 *  @framework MPSRayIntersector
 *  @description  MPSRayIntersector triangle acceleration structure interface.
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef MPSTriangleAccelerationStructure_h
#define MPSTriangleAccelerationStructure_h

#import <MPSRayIntersector/MPSPolygonAccelerationStructure.h>

/**
 * @brief An acceleration structure built over triangles
 *
 * @discussion See MPSPolygonAccelerationStructure for more information
 */
MPS_CLASS_AVAILABLE_STARTING(macos(10.14), ios(12.0), macCatalyst(13.0), tvos(12.0))
@interface MPSTriangleAccelerationStructure : MPSPolygonAccelerationStructure

/**
 * @brief Number of triangles. Changes to this property require rebuilding the acceleration
 * structure.
 *
 * Note that this property is an alias for the polygonCount property.
 */
@property (nonatomic) NSUInteger triangleCount;

@end

#endif

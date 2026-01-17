/*!
 *  @header MPSQuadrilateralAccelerationStructure.h
 *  @framework MPSRayIntersector
 *  @description  MPSRayIntersector quadrilateral acceleration structure interface.
 *
 *  @copyright Copyright (c) 2018 Apple Inc. All rights reserved.
 */

#ifndef MPSQuadrilateralAccelerationStructure_h
#define MPSQuadrilateralAccelerationStructure_h

#import <MPSRayIntersector/MPSPolygonAccelerationStructure.h>

/**
 * @brief An acceleration structure built over quadrilaterals
 *
 * @discussion See MPSPolygonAccelerationStructure for more information
 */
MPS_AVAILABLE_STARTING_BUT_DEPRECATED("Use Metal ray tracing API instead", macos(10.15, 14.0), ios(13.0, 17.0), macCatalyst(13.0, 17.0), tvos(13.0, 17.0))
@interface MPSQuadrilateralAccelerationStructure : MPSPolygonAccelerationStructure

/**
 * @brief Number of quads. Changes to this property require rebuilding the acceleration
 * structure. This is an alias for the polygonCount property.
 */
@property (nonatomic) NSUInteger quadrilateralCount;

@end

#endif

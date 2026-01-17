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
MPS_CLASS_AVAILABLE_STARTING(macos(10.15), ios(13.0), macCatalyst(13.0), tvos(13.0))
@interface MPSQuadrilateralAccelerationStructure : MPSPolygonAccelerationStructure

/**
 * @brief Number of quads. Changes to this property require rebuilding the acceleration
 * structure. This is an alias for the polygonCount property.
 */
@property (nonatomic) NSUInteger quadrilateralCount;

@end

#endif

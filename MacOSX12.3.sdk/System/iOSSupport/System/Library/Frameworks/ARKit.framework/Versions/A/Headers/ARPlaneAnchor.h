//
//  ARPlaneAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

#define AR_PLANE_ANCHOR_PROTOCOLS

NS_ASSUME_NONNULL_BEGIN

@class ARPlaneGeometry;

/**
 A value describing the alignment of a plane anchor.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARPlaneAnchorAlignment) {
    /** A plane that is horizontal with respect to gravity. */
    ARPlaneAnchorAlignmentHorizontal,
    
    /** A plane that is vertical with respect to gravity. */
    ARPlaneAnchorAlignmentVertical API_AVAILABLE(ios(11.3))
} NS_SWIFT_NAME(ARPlaneAnchor.Alignment);

/**
 A value describing the classification status of a plane anchor.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, ARPlaneClassificationStatus) {
    /** Plane classification is currently unavailable. */
    ARPlaneClassificationStatusNotAvailable = 0,
    /** ARKit has not yet determined the classification of this plane. */
    ARPlaneClassificationStatusUndetermined,
    /** ARKit is confident the plane is not any of the known classes. */
    ARPlaneClassificationStatusUnknown,
    /** ARKit has a classification for the plane it is confident in. */
    ARPlaneClassificationStatusKnown
} NS_REFINED_FOR_SWIFT;

/**
 A value describing the classification of a plane anchor.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, ARPlaneClassification) {
    /** The classification is not any of the known classes. */
    ARPlaneClassificationNone = 0,
    ARPlaneClassificationWall,
    ARPlaneClassificationFloor,
    ARPlaneClassificationCeiling,
    ARPlaneClassificationTable,
    ARPlaneClassificationSeat,
    ARPlaneClassificationWindow,
    ARPlaneClassificationDoor
} NS_REFINED_FOR_SWIFT;

/**
 An anchor representing a planar surface in the world.
 @discussion Planes are defined in the X and Z direction, where Y is the surface’s normal.
 */
API_AVAILABLE(ios(11.0))
@interface ARPlaneAnchor : ARAnchor AR_PLANE_ANCHOR_PROTOCOLS

/**
 Determines whether plane classification is supported on this device.
 */
@property (class, nonatomic, readonly, getter=isClassificationSupported) BOOL classificationSupported API_AVAILABLE(ios(12.0));

/**
 The alignment of the plane.
 */
@property (nonatomic, readonly) ARPlaneAnchorAlignment alignment;

/**
 The center of the plane in the anchor’s coordinate space.
 */
@property (nonatomic, readonly) simd_float3 center;

/**
 The extent of the plane in the anchor’s coordinate space.
 */
@property (nonatomic, readonly) simd_float3 extent;

/**
 Geometry of the plane in the anchor's coordinate space.
 */
@property (nonatomic, strong, readonly) ARPlaneGeometry *geometry API_AVAILABLE(ios(11.3));

/**
 Classification status of the plane.
 */
@property (nonatomic, assign, readonly) ARPlaneClassificationStatus classificationStatus API_AVAILABLE(ios(12.0)) NS_REFINED_FOR_SWIFT;

/**
 Classification of the plane.
 */
@property (nonatomic, assign, readonly) ARPlaneClassification classification API_AVAILABLE(ios(12.0)) NS_REFINED_FOR_SWIFT;

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

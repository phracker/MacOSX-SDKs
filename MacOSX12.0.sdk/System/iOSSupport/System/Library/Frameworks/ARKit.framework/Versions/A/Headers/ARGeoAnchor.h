//
//  ARGeoAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>
#import <ARKit/ARGeoTrackingTypes.h>
#import <CoreLocation/CoreLocation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An anchor representing a geographical location in the world.
 @discussion The anchor's transform will be automatically updated by the session based on location and heading.
 The session needs to be configured with ARGeoTrackingConfiguration.
 */
API_AVAILABLE(ios(14.0))
@interface ARGeoAnchor : ARAnchor <ARTrackable>

/**
 The coordinate where this anchor will be placed.
 
 @discussion The anchor's transform will be automatically updated by the session when ARGeoTrackingConfiguration is set.
 */
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

/**
 The distance to mean sea level, in meters (negative values indicate it's below sea level).
 
 @discussion Only valid when altitudeSource is not ARAltitudeSourceUnknown.
 */
@property (nonatomic, readonly, assign) CLLocationDistance altitude NS_REFINED_FOR_SWIFT;

/**
 The source of altitude information. If the user did not provide the altitude, ARKit populates this property to indicate the expected accuracy depending on the available altitude data.
 */
@property (nonatomic, readonly, assign) ARAltitudeSource altitudeSource;

/**
 Initializes a new ARGeoAnchor with the given coordinates.
 
 @discussion ARKit will query the ground level altitude during runtime, and populate the altitude as soon as that information becomes available.
 @param coordinate Coordinates.
 */
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate NS_REFINED_FOR_SWIFT;

/**
 Initializes a new ARGeoAnchor with the given coordinates and altitude.

 @param coordinate Coordinates.
 @param altitude Altitude in meters.
 */
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate altitude:(CLLocationDistance)altitude NS_REFINED_FOR_SWIFT;

/**
 Initializes a new named ARGeoAnchor with the given coordinates.

 @discussion ARKit will query the ground level altitude during runtime, and populate the altitude as soon as that information becomes available.
 @param name Name of the anchor.
 @param coordinate Coordinates.
 */
- (instancetype)initWithName:(NSString *)name coordinate:(CLLocationCoordinate2D)coordinate NS_REFINED_FOR_SWIFT;

/**
 Initializes a new named ARGeoAnchor with the given coordinates and altitude.

 @param name Name of the anchor.
 @param coordinate Coordinates.
 @param altitude Altitude in meters.
 */
- (instancetype)initWithName:(NSString *)name coordinate:(CLLocationCoordinate2D)coordinate altitude:(CLLocationDistance)altitude;

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END


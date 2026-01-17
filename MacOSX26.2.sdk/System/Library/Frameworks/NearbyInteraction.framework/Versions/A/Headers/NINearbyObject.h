//
//  NINearbyObject.h
//  NearbyInteraction
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NearbyInteraction/NIExport.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

@class NIDiscoveryToken;

/** A sentinel value indicating that a distance measurement could not be produced */
API_AVAILABLE(ios(14.0), watchos(7.3)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT float NINearbyObjectDistanceNotAvailable NS_SWIFT_UNAVAILABLE("Use optional value semantics");

/** A sentinel value indicating that a direction measurement could not be produced */
API_AVAILABLE(ios(14.0), watchos(7.3)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT simd_float3 NINearbyObjectDirectionNotAvailable NS_SWIFT_UNAVAILABLE("Use optional value semantics");

/** A sentinel value indicating that an angle could not be produced */
API_AVAILABLE(ios(16.0), watchos(9.0)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT float NINearbyObjectAngleNotAvailable NS_SWIFT_UNAVAILABLE("Use optional value semantics");

API_AVAILABLE(ios(16.0), watchos(9.0)) API_UNAVAILABLE(macos, tvos)
typedef NS_ENUM(NSInteger, NINearbyObjectVerticalDirectionEstimate) {
    NINearbyObjectVerticalDirectionEstimateUnknown = 0,

    /** Represents the nearby object is approximately equal */
    NINearbyObjectVerticalDirectionEstimateSame = 1,

    /** Represents the nearby object is above the current device */
    NINearbyObjectVerticalDirectionEstimateAbove = 2,

    /** Represents the nearby object  is below the current device */
    NINearbyObjectVerticalDirectionEstimateBelow = 3,

    /** Represents the nearby object  is above or below the current device - i.e. not the same level */
    NINearbyObjectVerticalDirectionEstimateAboveOrBelow = 4,
} NS_SWIFT_NAME(NINearbyObject.VerticalDirectionEstimate);

/**
 A nearby object with distance and direction measurements.
*/
API_AVAILABLE(ios(14.0), watchos(7.3)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT
@interface NINearbyObject : NSObject <NSCopying, NSSecureCoding>

/**
 Nearby interaction discovery token
 @discussion This discovery token will be equal to the token provided in the configuration with which the session was run.
 */
@property (nonatomic, readonly, copy) NIDiscoveryToken *discoveryToken;

/**
 Distance to the nearby object in meters. If not available in this update, the value of this property will be equal to NINearbyObjectDistanceNotAvailable in Objective C, or nil in Swift.
 */
@property (nonatomic, readonly) float distance NS_REFINED_FOR_SWIFT;

/**
 Unit vector representing the relative direction in the reference frame.
 @discussion (x,y,z) representing a point on the unit sphere in the direction of the nearby object.
 If not available in this update, the value of this property will be equal to NINearbyObjectDirectionNotAvailable in Objective C, or nil in Swift.
*/
@property (nonatomic, readonly) simd_float3 direction NS_REFINED_FOR_SWIFT;

/**
An indication of the positional relationship to the nearby object in the vertical dimension.
*/
@property (nonatomic, readonly) NINearbyObjectVerticalDirectionEstimate verticalDirectionEstimate API_AVAILABLE(ios(16.0), watchos(9.0)) API_UNAVAILABLE(macos, tvos);

/**
An angle in radians indicating the azimuthal direction to the nearby object.
@discussion when unavailable, the value will be set to `NINearbyObjectAngleNotAvailable`.
*/
@property (nonatomic, readonly) float horizontalAngle NS_REFINED_FOR_SWIFT API_AVAILABLE(ios(16.0), watchos(9.0)) API_UNAVAILABLE(macos, tvos);


/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end



NS_ASSUME_NONNULL_END

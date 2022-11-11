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

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end



NS_ASSUME_NONNULL_END

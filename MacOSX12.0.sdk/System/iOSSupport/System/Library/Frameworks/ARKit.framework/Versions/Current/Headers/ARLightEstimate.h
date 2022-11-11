//
//  ARLightEstimate.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A light estimate representing the light in the scene.
 */
API_AVAILABLE(ios(11.0))
@interface ARLightEstimate : NSObject

/**
 Ambient intensity of the lighting.
 
 @discussion In a well lit environment, this value is close to 1000. It typically ranges from 0 (very dark) to around 2000 (very bright).
 */
@property (nonatomic, readonly) CGFloat ambientIntensity;

/**
 The ambient color temperature of the lighting.

 @discussion This specifies the ambient color temperature of the lighting in Kelvin (6500 corresponds to pure white).
*/
@property (nonatomic, readonly) CGFloat ambientColorTemperature;

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A directional light estimate representing the light intensity and direction in the scene.
 */
API_AVAILABLE(ios(11.0))
@interface ARDirectionalLightEstimate : ARLightEstimate

/**
 Second degree spherical harmonics coefficients representing the intensity of light.
 
 @discussion The data is an array of 27 32-bit floating-point values, containing three non-interleaved data sets
 corresponding to the red, green, and blue sets of coefficients.
 */
@property (nonatomic, copy, readonly) NSData *sphericalHarmonicsCoefficients;

/**
 The primary direction of light.
 */
@property (nonatomic, readonly) simd_float3 primaryLightDirection;

/**
 The intensity of light in the primary direction.
 */
@property (nonatomic, readonly) CGFloat primaryLightIntensity;

@end

NS_ASSUME_NONNULL_END

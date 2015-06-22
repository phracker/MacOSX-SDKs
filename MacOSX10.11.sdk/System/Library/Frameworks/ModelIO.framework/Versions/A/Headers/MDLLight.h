/*!
 @header MDLLight.h
 @framework ModelIO
 @abstract Structures for describing lights for rendering
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ModelIO/ModelIOExports.h>
#import <ModelIO/MDLTransform.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, MDLLightType) {
    MDLLightTypeUnknown = 0,
    MDLLightTypeAmbient,
    MDLLightTypeDirectional,
    MDLLightTypeSpot,
    MDLLightTypePoint,
    MDLLightTypeLinear,
    MDLLightTypeDiscArea,
    MDLLightTypeRectangularArea,
    MDLLightTypeSuperElliptical,
    MDLLightTypePhotometric,
    MDLLightTypeProbe,
    MDLLightTypeEnvironment
};

@class MDLColorSpec;
@class MDLTexture;

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLLight : MDLObject

/** A utility function that returns the radiance of the light for the given
    direction vector.

    @discussion vector is assumed to be in the light's local space, pointing
                to the light's origin.
  */
- (CGColorRef)evaluatedColorFromVector:(vector_float3)vector;

@property (nonatomic, readonly) MDLLightType lightType;

@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLPhysicallyPlausibleLight : MDLLight

/**
 Light color specified by color temperature, in degrees Kelvin
 @discussion default color is 6500K, cool daylight.
 Setting the color property will override the cgColor property
 */
- (void)setColorByTemperature:(float)temperature;

@property (nonatomic) CGColorRef color;

// default light intensity is 1000 lumens
@property (nonatomic, readwrite) float lumens;

// 90 means down the light axis to perpendicular is spanned (lightType will be MDLLightSpot)
// 180 means down the light axis to up the light axis is spanned (lightType will be MDLLightPoint)
// default is 22.5 degrees
@property (nonatomic, readwrite) float innerConeAngle;

@property (nonatomic, readwrite) float outerConeAngle;

@property (nonatomic, readwrite) float attenuationStartDistance;

@property (nonatomic, readwrite) float attenuationEndDistance;

@property (nonatomic, readwrite) float attenuationFalloffExponent;


@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLAreaLight : MDLPhysicallyPlausibleLight

@property (nonatomic, readwrite) float areaRadius;

@property (nonatomic, readwrite) vector_float2 superEllipticPower;

@property (nonatomic, readwrite) float aspect;

@end


NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLPhotometricLight : MDLLight

// Init with an IES profile file, generate a light web of specified width and height
- (nullable instancetype)initWithIESProfile:(NSURL*)URL;

// angle spanned by width for which data is available.
// 90 means one quadrant is given, with 0 being up, 4 way symmetry
// 180 means two quadrants are given, 2 way symmetry
// 360 means the entire span is given
@property (nonatomic, readonly) float horizontalAngle;

// a coneSpans x horizontalSpans array of floating point values indicating light intensity
// in candelas for each direction spanned by the angles
// The cone angle spanned is in the coneAngle property
// If the cone angle is 90, the lightType will be MDLLightSpot
// If the cone angle is 360, the lightType will be MDLLightPoint
@property (nonatomic, nullable, retain, readonly) NSData *lightWeb;

@property (nonatomic, readonly) NSUInteger coneSpans;

@property (nonatomic, readonly) NSUInteger horizontalSpans;

@property (nonatomic, readonly) float IESConeAngle;

@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLLightProbe : MDLLight

-(instancetype)initWithReflectiveTexture:(nullable MDLTexture*)reflectiveTexture
                       irradianceTexture:(nullable MDLTexture*)irradianceTexture;

-(void)generateSphericalHarmonicsFromIrradiance:(NSUInteger)sphericalHarmonicsLevel;

@property (nonatomic, retain, nullable, readonly) MDLTexture *reflectiveTexture;
@property (nonatomic, retain, nullable, readonly) MDLTexture *irradianceTexture;
@property (nonatomic, readonly) NSUInteger sphericalHarmonicsLevel;
@property (nonatomic, copy, nullable, readonly) NSData *sphericalHarmonicsCoefficients;

@end


@interface MDLLightProbe (MDLLightBaking)

+ (nullable MDLLightProbe *)lightProbeWithTextureSize:(NSInteger)textureSize
                                          forLocation:(MDLTransform *)transform
                                     lightsToConsider:(NSArray<MDLLight*>*)lightsToConsider
                                    objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                                    reflectiveCubemap:(nullable MDLTexture*)reflectiveCubemap
                                    irradianceCubemap:(nullable MDLTexture*)irradianceCubemap;

@end


NS_ASSUME_NONNULL_END

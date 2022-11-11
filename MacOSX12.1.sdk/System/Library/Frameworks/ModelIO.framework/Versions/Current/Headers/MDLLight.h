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

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLLight : MDLObject

/** A utility function that returns the irradiance from the light at a given point.
    @discussion point is world space
    @property colorSpace name, as defined in CGColorSpace.h. Default is 
              kCGColorSpaceSRGB
  */
- (CGColorRef)irradianceAtPoint:(vector_float3)point;
- (CGColorRef)irradianceAtPoint:(vector_float3)point colorSpace:(CGColorSpaceRef)colorSpace;

@property (nonatomic, readwrite) MDLLightType lightType;
@property (nonatomic, copy, readwrite) NSString *colorSpace;

@end

/*!
 @class MDLPhysicallyPlausibleLight
 @abstract A light with characteristics representing plausible real world lights
 
 @property color The color of the light.
 @property lumens The brightness of the light.
 @property innerConeAngle Within this cone, light is at maximum brightness. Units are degrees.
 @property outerConeAngle Between the inner cone angle and the outer, light 
           quadratically attenuates to zero.
 @property attenuationStartDistance. Within the attenuation start distance, the
           light is maximally bright.
 @property attenuationEndDistance. Beyond this distance, there is no light.
 */

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLPhysicallyPlausibleLight : MDLLight

/**
 Light color specified by color temperature, in degrees Kelvin
 @discussion default color is 6500K, cool daylight.
 */
- (void)setColorByTemperature:(float)temperature;

@property (nullable, nonatomic) CGColorRef color;

// default light intensity is 1000 lumens
@property (nonatomic, readwrite) float lumens;

// 90 means down the light axis to perpendicular is spanned (lightType will be MDLLightSpot)
// 180 means down the light axis to up the light axis is spanned (lightType will be MDLLightPoint)
// default is 22.5 degrees
@property (nonatomic, readwrite) float innerConeAngle;
@property (nonatomic, readwrite) float outerConeAngle;
@property (nonatomic, readwrite) float attenuationStartDistance;
@property (nonatomic, readwrite) float attenuationEndDistance;

@end

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLAreaLight : MDLPhysicallyPlausibleLight

@property (nonatomic, readwrite) float areaRadius;
@property (nonatomic, readwrite) vector_float2 superEllipticPower;
@property (nonatomic, readwrite) float aspect;

@end

/*!
 @class MDLPhotometricLight
 @abstract A light created from measurements at various angles.
 
 @property lightCubeMap A cube map that can be sampled at various directions to
           learn the intensity of the light in that direction.
 @property sphericalHarmonicsLevel The value generateSphericalHarmonicsFromLight: 
           used to calculate the spherical harmonics coefficients
 @property sphericalHarmonicsCoefficients The spherical harmonic coefficiencts
           calculated by generateSphericalHarmonicsFromLight:
*/

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLPhotometricLight : MDLPhysicallyPlausibleLight

// Init with an IES profile file, generate a light web of specified width and height
- (nullable instancetype)initWithIESProfile:(NSURL*)URL;

-(void)generateSphericalHarmonicsFromLight:(NSUInteger)sphericalHarmonicsLevel;

-(void)generateCubemapFromLight:(NSUInteger)textureSize;

/*!
 @method generateTexture
 @abstract
 Generate an IES compliant MDLTexture
 1D when the number of horizontal angles is one and the innerConeAngle is < 180
 2D when the previous statement fails and innerConeAngle < 89
 3D in all other cases
 the parameter textureSize is the size in pixels of the texture image. For a size of N,
 1D generates an Nx1 image, 2D generates an NxN image, 3D generates an Nx(N*6) image (i.e. cubemap).
 */
-(MDLTexture*)generateTexture:(NSUInteger)textureSize API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

@property (nonatomic, retain, nullable, readonly) MDLTexture *lightCubeMap;

@property (nonatomic, readonly) NSUInteger sphericalHarmonicsLevel;

@property (nonatomic, copy, nullable, readonly) NSData *sphericalHarmonicsCoefficients;

@end

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
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

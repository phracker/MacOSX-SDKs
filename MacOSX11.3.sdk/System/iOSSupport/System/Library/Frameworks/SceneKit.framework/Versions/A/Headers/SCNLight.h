//
//  SCNLight.h
//  SceneKit
//
//  Copyright © 2012-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNMaterialProperty;

/*!
 @group Light Types
 @abstract Describes the various light types available.
 */

typedef NSString * SCNLightType NS_STRING_ENUM;
SCN_EXPORT SCNLightType const SCNLightTypeAmbient;                                                                // Ambient light
SCN_EXPORT SCNLightType const SCNLightTypeOmni;                                                                   // Omnidirectional light
SCN_EXPORT SCNLightType const SCNLightTypeDirectional;                                                            // Directional light
SCN_EXPORT SCNLightType const SCNLightTypeSpot;                                                                   // Spot light
SCN_EXPORT SCNLightType const SCNLightTypeIES   API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));               // IES light
SCN_EXPORT SCNLightType const SCNLightTypeProbe API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));               // Light probe
SCN_EXPORT SCNLightType const SCNLightTypeArea  API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0)); // Area light

/*! @enum SCNShadowMode
 @abstract The different modes available to compute shadows.
 @discussion When the shadow mode is set to SCNShadowModeForward, shadows are computed while computing the lighting. In this mode only the alpha component of the shadow color is used to alter the lighting contribution.
 When the shadow mode is set to SCNShadowModeDeferred shadows are applied as a post process. Shadows are blend over the final image and can therefor be of any arbitrary color. However it is most of the time less efficient than SCNShadowModeForward, except when a scene has a lot of overdraw.
 When the shadow mode is set to SCNShadowModeModulated the light doesn't illuminate the scene anymore, it only casts shadows. Therefore setting the light color has no effect. In this mode gobos act as a shadow projector: the gobo image is modulated with the shadow receiver's fragments. The typical usage is to use an image of a radial gradient (black to white) that is projected under a character (and use the categoryBitMask of the light and nodes to exclude the character from the shadow receiver).
 */
typedef NS_ENUM(NSInteger, SCNShadowMode) {
    SCNShadowModeForward   = 0,
    SCNShadowModeDeferred  = 1,
    SCNShadowModeModulated = 2
} API_AVAILABLE(macos(10.10));

typedef NS_ENUM(NSInteger, SCNLightProbeType) {
    SCNLightProbeTypeIrradiance  = 0, // Probe type that was existing before macOS 10.15. Bakes and stores spherical harmonics.
    SCNLightProbeTypeRadiance    = 1  // Probe that captures radiance (reflections) in its `probeExtents`. Either captured or provided as a cube texture using the `probeEnvironment` property.
} API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

typedef NS_ENUM(NSInteger, SCNLightProbeUpdateType) {
    SCNLightProbeUpdateTypeNever         = 0, // Probe that isn't automatically updated (for instance when baked using the Xcode's SceneKit scene editor or when `probeEnvironment` is specified)
    SCNLightProbeUpdateTypeRealtime      = 1  // Probe that is automatically updated by SceneKit at every frame
} API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

typedef NS_ENUM(NSInteger, SCNLightAreaType) {
    SCNLightAreaTypeRectangle = 1,
    SCNLightAreaTypePolygon   = 4
} API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @class SCNLight
 @abstract SCNLight represents a light that can be attached to a SCNNode. 
 */

SCN_EXPORT
@interface SCNLight : NSObject <SCNAnimatable, NSCopying, NSSecureCoding>

/*! 
 @method light
 @abstract Creates and returns a light instance.
 */
+ (instancetype)light;

/*! 
 @property type
 @abstract Specifies the receiver's type.
 @discussion Defaults to SCNLightTypeOmni on iOS 8 and later, and on macOS 10.10 and later (otherwise defaults to SCNLightTypeAmbient).
 */
@property(nonatomic, copy) SCNLightType type;

/*! 
 @property color
 @abstract Specifies the receiver's color (NSColor or CGColorRef). Animatable. Defaults to white.
 @discussion The initial value is a NSColor. The renderer multiplies the light's color is by the color derived from the light's temperature.
 */
@property(nonatomic, retain) id color;

/*!
 @property temperature
 @abstract Specifies the receiver's temperature.
 @discussion This specifies the temperature of the light in Kelvin. The renderer multiplies the light's color by the color derived from the light's temperature. Defaults to 6500 (pure white). Animatable.
 */
@property(nonatomic) CGFloat temperature API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property intensity
 @abstract Specifies the receiver's intensity.
 @discussion This intensity is used to modulate the light color. When used with a physically-based material, this corresponds to the luminous flux of the light, expressed in lumens (lm). Defaults to 1000. Animatable.
 */
@property(nonatomic) CGFloat intensity API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy, nullable) NSString *name;


#pragma mark - Shadow

/*! 
 @property castsShadow
 @abstract Determines whether the receiver casts a shadow. Defaults to NO.
 @discussion Shadows are only supported by spot and directional lights.
 */
@property(nonatomic) BOOL castsShadow;

/*! 
 @property shadowColor
 @abstract Specifies the color (CGColorRef or NSColor) of the shadow casted by the receiver. Defaults to black. Animatable.
 @discussion On iOS 9 or earlier and macOS 10.11 or earlier, this defaults to black 50% transparent.
 */
@property(nonatomic, retain) id shadowColor;

/*!
 @property shadowRadius
 @abstract Specifies the sample radius used to render the receiver’s shadow. Default value is 3.0. Animatable.
 */
@property(nonatomic) CGFloat shadowRadius;

/*!
 @property shadowMapSize
 @abstract Specifies the size of the shadow map.
 @discussion The larger the shadow map is the more precise the shadows are but the slower the computation is. If set to {0,0} the size of the shadow map is automatically chosen. Defaults to {0,0}.
 */
@property(nonatomic) CGSize shadowMapSize API_AVAILABLE(macos(10.10));

/*!
 @property shadowSampleCount
 @abstract Specifies the number of sample per fragment to compute the shadow map. Defaults to 0.
 @discussion On macOS 10.11 or earlier, the shadowSampleCount defaults to 16. On iOS 9 or earlier it defaults to 1.0.
 On macOS 10.12, iOS 10 and greater, when the shadowSampleCount is set to 0, a default sample count is chosen depending on the platform.
 */
@property(nonatomic) NSUInteger shadowSampleCount API_AVAILABLE(macos(10.10));

/*!
 @property shadowMode
 @abstract Specified the mode to use to cast shadows. See above for the available modes and their description. Defaults to SCNShadowModeForward.
 */
@property(nonatomic) SCNShadowMode shadowMode API_AVAILABLE(macos(10.10));

/*!
 @property shadowBias
 @abstract Specifies the correction to apply to the shadow map to correct acne artefacts. It is multiplied by an implementation-specific value to create a constant depth offset. Defaults to 1.0
 */
@property(nonatomic) CGFloat shadowBias API_AVAILABLE(macos(10.10));

/*!
 @property automaticallyAdjustsShadowProjection
 @abstract Specifies if the shadow map projection should be done automatically or manually by the user. Defaults to YES.
 */
@property(nonatomic) BOOL automaticallyAdjustsShadowProjection API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property maximumShadowDistance
 @abstract Specifies the maximum distance from the viewpoint from which the shadows for the receiver light won't be computed. Defaults to 100.0.
 */
@property(nonatomic) CGFloat maximumShadowDistance API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property forcesBackFaceCasters
 @abstract Render only back faces of the shadow caster when enabled. Defaults to NO.
 This is a behavior change from previous releases.
 */
@property(nonatomic) BOOL forcesBackFaceCasters API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property sampleDistributedShadowMaps
 @abstract Use the sample distribution of the main rendering to better fit the shadow frusta. Defaults to NO.
 */
@property(nonatomic) BOOL sampleDistributedShadowMaps API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property shadowCascadeCount
 @abstract Specifies the number of distinct shadow maps that will be computed for the receiver light. Defaults to 1. Maximum is 4.
 */
@property(nonatomic) NSUInteger shadowCascadeCount API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property shadowCascadeSplittingFactor
 @abstract Specifies a factor to interpolate between linear splitting (0) and logarithmic splitting (1). Defaults to 0.15.
 */
@property(nonatomic) CGFloat shadowCascadeSplittingFactor API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));


#pragma mark - Light projection settings for shadows

/*!
 @property orthographicScale
 @abstract Specifies the orthographic scale used to render from the directional light into the shadow map. Defaults to 1.
 @discussion This is only applicable for directional lights.
 */
@property(nonatomic) CGFloat orthographicScale API_AVAILABLE(macos(10.10));

/*!
 @property zNear
 @abstract Specifies the minimal distance between the light and the surface to cast shadow on. If a surface is closer to the light than this minimal distance, then the surface won't be shadowed. The near value must be different than zero. Animatable. Defaults to 1.
 */
@property(nonatomic) CGFloat zNear API_AVAILABLE(macos(10.10));

/*!
 @property zFar
 @abstract Specifies the maximal distance between the light and a visible surface to cast shadow on. If a surface is further from the light than this maximal distance, then the surface won't be shadowed. Animatable. Defaults to 100.
 */
@property(nonatomic) CGFloat zFar API_AVAILABLE(macos(10.10));


#pragma mark - Attenuation

/*!
 @property attenuationStartDistance
 @abstract The distance at which the attenuation starts (Omni or Spot light types only). Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat attenuationStartDistance API_AVAILABLE(macos(10.10));

/*!
 @property attenuationEndDistance
 @abstract The distance at which the attenuation ends (Omni or Spot light types only). Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat attenuationEndDistance API_AVAILABLE(macos(10.10));

/*!
 @property attenuationFalloffExponent
 @abstract Specifies the attenuation between the start and end attenuation distances. 0 means a constant attenuation, 1 a linear attenuation and 2 a quadratic attenuation, but any positive value will work (Omni or Spot light types only). Animatable. Defaults to 2.
 */
@property(nonatomic) CGFloat attenuationFalloffExponent API_AVAILABLE(macos(10.10));


#pragma mark - Spot light parameters

/*!
 @property spotInnerAngle
 @abstract The angle in degrees between the spot direction and the lit element below which the lighting is at full strength. Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat spotInnerAngle API_AVAILABLE(macos(10.10));

/*!
 @property spotOuterAngle
 @abstract The angle in degrees between the spot direction and the lit element after which the lighting is at zero strength. Animatable. Defaults to 45 degrees.
 */
@property(nonatomic) CGFloat spotOuterAngle API_AVAILABLE(macos(10.10));


#pragma mark - IES light parameters

/*!
 @property IESProfileURL
 @abstract Specifies the IES file from which the shape, direction, and intensity of illumination is determined. Defaults to nil.
 */
@property(nonatomic, retain, nullable) NSURL *IESProfileURL API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));


#pragma mark - Light probes parameters

/*!
 @property sphericalHarmonicsCoefficients
 @abstract The receiver's spherical harmonics coefficients.
 @discussion Currently spherical harmonics are only supported by light probes (SCNLightTypeProbe). The data is an array of 27 32-bit floating-point values, containing three non-interleaved data sets corresponding to the red, green, and blue sets of coefficients.
 */
@property(nonatomic, copy, readonly) NSData *sphericalHarmonicsCoefficients API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

// Type of the probe. Defaults to SCNLightProbeTypeIrradiance.
@property(nonatomic) SCNLightProbeType probeType API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

// Update type of the probe. Defaults to SCNLightProbeUpdateTypeNever.
@property(nonatomic) SCNLightProbeUpdateType probeUpdateType API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

// Dimensions of the reflection probe, in local space. Used when `parallaxCorrectionEnabled` is YES.
@property(nonatomic) simd_float3 probeExtents API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

// Position from which the reflection is shooted, in local space.
@property(nonatomic) simd_float3 probeOffset API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

// Whether parallax correction is enabled for the reflection probe. Defaults to NO.
@property(nonatomic) BOOL parallaxCorrectionEnabled API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

// Size of the parallax correction box, has a factor of probeExtents. Defaults to (1, 1, 1).
@property(nonatomic) simd_float3 parallaxExtentsFactor API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

// Center offset of the parallax correction box, relative to `probeExtents`. Defaults to (0, 0, 0).
@property(nonatomic) simd_float3 parallaxCenterOffset API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

// Only applies to a probe of type SCNLightProbeTypeRadiance.
@property(nonatomic, readonly, nullable) SCNMaterialProperty *probeEnvironment API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));


#pragma mark - Area light parameters

/*!
 @property areaType
 @abstract Determines the shape of a light of type SCNLightTypeArea. Defaults to SCNLightAreaTypeRectangle.
 */
@property(nonatomic) SCNLightAreaType areaType API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property areaExtents
 @abstract Determines the extents of a light of type SCNLightTypeArea. Defaults to (1.0, 1.0, 1.0).
 @discussion The extents are interpreted differently for each type of area light
             SCNLightAreaTypeLine      : areaExtents.x   = (width)
             SCNLightAreaTypeRectangle : areaExtents.xy  = (width, height)
             SCNLightAreaTypePolygon   : ignored (see `areaPolygonVertices`)
 */
@property(nonatomic) simd_float3 areaExtents API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property areaPolygonVertices
 @abstract Determines the shape of light of an area light of type SCNLightAreaTypePolygon. Defaults nil.
 @discussion An array of CGPoint values corresponding to the coordinates of the polygon's vertices in the XY plane.
 */
@property(nonatomic, copy, nullable) NSArray<NSValue *> *areaPolygonVertices API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property drawsArea
 @abstract Determines whether the shape of a light of type SCNLightTypeArea is drawn in the scene. Defaults to YES.
 */
@property(nonatomic) BOOL drawsArea API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property doubleSided
 @abstract Determines whether a light of type SCNLightTypeArea is double-sided. Defaults NO.
 @discussion Area lights of type SCNLightAreaTypeRectangle or SCNLightAreaTypePolygon emit light along the -Z axis. When set to YES, they also emit light along the +Z axis.
 */
@property(nonatomic) BOOL doubleSided API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));


#pragma mark - Other

/*!
 @property gobo
 @abstract Specifies the gobo (or "cookie") of the light, used to control the shape of emitted light.
 @discussion Gobos are only supported by spot lights.
 */
@property(nonatomic, readonly, nullable) SCNMaterialProperty *gobo API_AVAILABLE(macos(10.9));

/*!
 @property categoryBitMask
 @abstract Determines the node categories that will be lit by the receiver. Defaults to all bit set.
 */
@property(nonatomic) NSUInteger categoryBitMask API_AVAILABLE(macos(10.10));

@end

NS_ASSUME_NONNULL_END

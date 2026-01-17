//
//  SCNLight.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
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

/*!
 @class SCNLight
 @abstract SCNLight represents a light that can be attached to a SCNNode. 
 */

SCN_EXPORT
@interface SCNLight : NSObject <SCNAnimatable, SCNTechniqueSupport, NSCopying, NSSecureCoding>

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
 @abstract Specified the mode to use to cast shadows. See above for the available modes and their description. Defaults to SCNShadowModeDefered on 10.9 and before, defaults to SCNShadowModeForward otherwise.
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


#pragma mark - Other

/*!
 @property gobo
 @abstract Specifies the gobo (or "cookie") of the light, used to control the shape of emitted light. Defaults to nil.
 @discussion Gobos are only supported by spot lights.
 */
@property(nonatomic, readonly, nullable) SCNMaterialProperty *gobo API_AVAILABLE(macos(10.9));

/*!
 @property categoryBitMask
 @abstract Determines the node categories that will be lit by the receiver. Defaults to all bit set.
 */
@property(nonatomic) NSUInteger categoryBitMask API_AVAILABLE(macos(10.10));


#pragma mark - Deprecated

/*!
 @method attributeForKey:
 @param key The key for which to return the corresponding attribute.
 @abstract Returns the attribute for the specified key. The valid keys are described in the "Light Attributes" constants.
 */
- (nullable id)attributeForKey:(NSString *)key API_DEPRECATED("Use SCNLight properties instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
 @method setAttribute:forKey:
 @param attribute The attribute for the property identified by key.
 @param key The name of a property.
 @abstract Set the specified attribute for the specified key. The valid keys are described in the "Light Attributes" constants.
 */
- (void)setAttribute:(nullable id)attribute forKey:(NSString *)key API_DEPRECATED("Use SCNLight properties instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos);

@end

/*!
 @group Light Attributes
 @abstract Attributes affecting the lighting computations.
 @discussion These keys are deprecated in 10.10. Please use the properties of SCNLight instead.
 */
/*! @constant SCNLightAttenuationStartKey The distance at which the attenuation starts (Omni or Spot light types only). Animatable as "attenuationStart". Defaults to 0. */
SCN_EXPORT NSString * const SCNLightAttenuationStartKey API_DEPRECATED("Use SCNLight.attenuationStartDistance instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos);

/*! @constant SCNLightAttenuationEndKey The distance at which the attenuation ends (Omni or Spot light types only). Animatable as "attenuationEnd". Defaults to 0. */
SCN_EXPORT NSString * const SCNLightAttenuationEndKey API_DEPRECATED("Use SCNLight.attenuationEndDistance instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos);

/*! @constant SCNLightAttenuationFalloffExponentKey Controls the attenuation between the start and end attenuation distances. 0 means a constant attenuation, 1 a linear attenuation and 2 a quadratic attenuation, but any positive value will work (Omni or Spot light types only). Animatable as "attenuationFalloffExponent". Defaults to 2. */
SCN_EXPORT NSString * const SCNLightAttenuationFalloffExponentKey API_DEPRECATED("Use SCNLight.attenuationFalloffExponent instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos);

/*! @constant SCNLightSpotInnerAngleKey The angle in degrees between the spot direction and the lit element below which the lighting is at full strength. Animatable as "spotInnerAngle". Defaults to 0. */
SCN_EXPORT NSString * const SCNLightSpotInnerAngleKey API_DEPRECATED("Use SCNLight.spotInnerAngle instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos);

/*! @constant SCNLightSpotOuterAngleKey The angle in degrees between the spot direction and the lit element after which the lighting is at zero strength. Animatable as "spotOuterAngle". Defaults to 45 degrees. */
SCN_EXPORT NSString * const SCNLightSpotOuterAngleKey API_DEPRECATED("Use SCNLight.spotOuterAngle instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos);

/*! @constant SCNLightShadowNearClippingKey Specifies the minimal distance between the light and the surface to cast shadow on. If a surface is closer to the light than this minimal distance, then the surface won't be shadowed. The near value must be different than zero. Animatable as "zNear". Defaults to 1. */
SCN_EXPORT NSString * const SCNLightShadowNearClippingKey API_DEPRECATED("Use SCNLight.zNear instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos);

/*! @constant SCNLightShadowFarClippingKey Specifies the maximal distance between the light and a visible surface to cast shadow on. If a surface is further from the light than this maximal distance, then the surface won't be shadowed. Animatable as "zFar". Defaults to 100. */
SCN_EXPORT NSString * const SCNLightShadowFarClippingKey API_DEPRECATED("Use SCNLight.zFar instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos);


NS_ASSUME_NONNULL_END

//
//  SCNLight.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @group Light Types
 @abstract Describes the various light types available.
 */

/*! @constant SCNLightTypeAmbient Ambient light */
SCN_EXTERN NSString * const SCNLightTypeAmbient;
/*! @constant SCNLightTypeOmni Omnidirectional light */
SCN_EXTERN NSString * const SCNLightTypeOmni;
/*! @constant SCNLightTypeDirectional Directional light */
SCN_EXTERN NSString * const SCNLightTypeDirectional;
/*! @constant SCNLightTypeSpot Spot light */
SCN_EXTERN NSString * const SCNLightTypeSpot;


/*! @enum SCNShadowMode
 @abstract The different modes available to compute shadows.
 @discussion When the shadow mode is set to SCNShadowModeForward, shadows are computed while computing the lighting. In this mode only the alpha component of the shadow color is used to alter the lighting contribution.
 When the shadow mode is set to SCNShadowModeDeferred shadows are applied as a post process. Shadows are blend over the final image and can therefor be of any arbitrary color. However it is most of the time less effiscient as SCNShadowModeForward, except when a scene has a lot of overdraw.
 When the shadow mode is set to SCNShadowModeModulated the light doesn't illuminate the scene anymore, it only casts shadows. Therefor setting the light color has no effect. In this mode gobos act as a shadow projector: the gobo image is modulated with the shadow receiver's fragments. The typical usage is to use an image of a radial gradient (black to white) that is projected under a character (and use the categoryBitMask of the light and nodes to exclude the character from the shadow receiver).
 */
typedef NS_ENUM(NSInteger, SCNShadowMode) {
    SCNShadowModeForward   = 0,
    SCNShadowModeDeferred  = 1,
    SCNShadowModeModulated = 2
} NS_ENUM_AVAILABLE(10_10, 8_0);

/*!
 @class SCNLight
 @abstract SCNLight represents a light that can be attached to a SCNNode. 
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNLight : NSObject <SCNAnimatable, SCNTechniqueSupport, NSCopying, NSSecureCoding>

/*! 
 @method light
 @abstract Creates and returns a light instance.
 */
+ (instancetype)light;

/*! 
 @property type
 @abstract Specifies the receiver's type.
 @discussion A light type can be one of the "Light Types" constants. Defaults to SCNLightTypeOmni on iOS 8 and later, and on OSX 10.10 and later (otherwise defaults to SCNLightTypeAmbient).
 */
@property(nonatomic, copy) NSString *type;

/*! 
 @property color
 @abstract Specifies the receiver's color (NSColor or CGColorRef). Animatable. Defaults to white.
 @discussion The initial value is a NSColor.
 */
@property(nonatomic, retain) id color;

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
 @abstract Specifies the color (CGColorRef or NSColor) of the shadow casted by the receiver. Default is 50% transparent black. Animatable.
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
@property(nonatomic) CGSize shadowMapSize NS_AVAILABLE(10_10, 8_0);

/*!
 @property shadowSampleCount
 @abstract Specifies the number of sample per fragment to compute the shadow map. Defaults to 16.
 */
@property(nonatomic) NSUInteger shadowSampleCount NS_AVAILABLE(10_10, 8_0);

/*!
 @property shadowMode
 @abstract Specified the mode to use to cast shadows. See above for the available modes and their description. Defaults to SCNShadowModeDefered on 10.9 and before, defaults to SCNShadowModeForward otherwise.
 */
@property(nonatomic) SCNShadowMode shadowMode NS_AVAILABLE(10_10, 8_0);

/*!
 @property shadowBias
 @abstrat Specifies the correction to apply to the shadow map to correct acne artefacts. It is multiplied by an implementation-specific value to create a constant depth offset. Defaults to 1.0
 */
@property(nonatomic) CGFloat shadowBias NS_AVAILABLE(10_10, 8_0);


#pragma mark - Light projection settings for shadows

/*!
 @property orthographicScale
 @abstract Specifies the orthographic scale used to render from the directional light into the shadow map. Defaults to 1.
 @discussion This is only applicable for directional lights.
 */
@property(nonatomic) CGFloat orthographicScale NS_AVAILABLE(10_10, 8_0);

/*!
 @property zNear
 @abstract Specifies the minimal distance between the light and the surface to cast shadow on.  If a surface is closer to the light than this minimal distance, then the surface won't be shadowed. The near value must be different than zero. Animatable. Defaults to 1.
 */
@property(nonatomic) CGFloat zNear NS_AVAILABLE(10_10, 8_0);

/*!
 @property zFar
 @abstract Specifies the maximal distance between the light and a visible surface to cast shadow on. If a surface is further from the light than this maximal distance, then the surface won't be shadowed. Animatable. Defaults to 100.
 */
@property(nonatomic) CGFloat zFar NS_AVAILABLE(10_10, 8_0);


#pragma mark - Attenuation

/*!
 @property attenuationStartDistance
 @abstract The distance at which the attenuation starts (Omni or Spot light types only). Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat attenuationStartDistance NS_AVAILABLE(10_10, 8_0);

/*!
 @property attenuationEndDistance
 @abstract The distance at which the attenuation ends (Omni or Spot light types only). Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat attenuationEndDistance NS_AVAILABLE(10_10, 8_0);

/*!
 @property attenuationFalloffExponent
 @abstract Specifies the attenuation between the start and end attenuation distances. 0 means a constant attenuation, 1 a linear attenuation and 2 a quadratic attenuation, but any positive value will work (Omni or Spot light types only). Animatable. Defaults to 2.
 */
@property(nonatomic) CGFloat attenuationFalloffExponent NS_AVAILABLE(10_10, 8_0);


#pragma mark - Spot parameters

/*!
 @property spotInnerAngle
 @abstract The angle in degrees between the spot direction and the lit element below which the lighting is at full strength. Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat spotInnerAngle  NS_AVAILABLE(10_10, 8_0);

/*!
 @property spotOuterAngle
 @abstract The angle in degrees between the spot direction and the lit element after which the lighting is at zero strength. Animatable. Defaults to 45 degrees.
 */
@property(nonatomic) CGFloat spotOuterAngle  NS_AVAILABLE(10_10, 8_0);


#pragma mark - Other

/*!
 @property gobo
 @abstract Specifies the gobo (or "cookie") of the light, used to control the shape of emitted light. Defaults to nil.
 @discussion Gobos are only supported by spot lights.
 */
@property(nonatomic, readonly, nullable) SCNMaterialProperty *gobo NS_AVAILABLE(10_9, 8_0);

/*!
 @property categoryBitMask
 @abstract Determines the node categories that will be lit by the receiver. Defaults to all bit set.
 */
@property(nonatomic) NSUInteger categoryBitMask NS_AVAILABLE(10_10, 8_0);

#pragma mark - Deprecated

/*!
 @method attributeForKey:
 @param key The key for which to return the corresponding attribute.
 @abstract Returns the attribute for the specified key. The valid keys are described in the "Light Attributes" constants.
 */
- (nullable id)attributeForKey:(NSString *)key NS_DEPRECATED(10_8, 10_10, NA, NA);

/*!
 @method setAttribute:forKey:
 @param attribute The attribute for the property identified by key.
 @param key The name of a property.
 @abstract Set the specified attribute for the specified key. The valid keys are described in the "Light Attributes" constants.
 */
- (void)setAttribute:(nullable id)attribute forKey:(NSString *)key NS_DEPRECATED(10_8, 10_10, NA, NA);

@end

/*!
 @group Light Attributes
 @abstract Attributes affecting the lighting computations.
 @discussion These keys are deprecated in 10.10. Please use the properties of SCNLight instead.
 */
/*! @constant SCNLightAttenuationStartKey The distance at which the attenuation starts (Omni or Spot light types only). Animatable as "attenuationStart". Defaults to 0. */
SCN_EXTERN NSString * const SCNLightAttenuationStartKey NS_DEPRECATED(10_8, 10_10, NA, NA);

/*! @constant SCNLightAttenuationEndKey The distance at which the attenuation ends (Omni or Spot light types only). Animatable as "attenuationEnd". Defaults to 0. */
SCN_EXTERN NSString * const SCNLightAttenuationEndKey NS_DEPRECATED(10_8, 10_10, NA, NA);

/*! @constant SCNLightAttenuationFalloffExponentKey Controls the attenuation between the start and end attenuation distances. 0 means a constant attenuation, 1 a linear attenuation and 2 a quadratic attenuation, but any positive value will work (Omni or Spot light types only). Animatable as "attenuationFalloffExponent". Defaults to 2. */
SCN_EXTERN NSString * const SCNLightAttenuationFalloffExponentKey NS_DEPRECATED(10_8, 10_10, NA, NA);

/*! @constant SCNLightSpotInnerAngleKey The angle in degrees between the spot direction and the lit element below which the lighting is at full strength. Animatable as "spotInnerAngle". Defaults to 0. */
SCN_EXTERN NSString * const SCNLightSpotInnerAngleKey NS_DEPRECATED(10_8, 10_10, NA, NA);

/*! @constant SCNLightSpotOuterAngleKey The angle in degrees between the spot direction and the lit element after which the lighting is at zero strength. Animatable as "spotOuterAngle". Defaults to 45 degrees. */
SCN_EXTERN NSString * const SCNLightSpotOuterAngleKey NS_DEPRECATED(10_8, 10_10, NA, NA);

/*! @constant SCNLightShadowNearClippingKey Specifies the minimal distance between the light and the surface to cast shadow on.  If a surface is closer to the light than this minimal distance, then the surface won't be shadowed. The near value must be different than zero. Animatable as "zNear". Defaults to 1. */
SCN_EXTERN NSString * const SCNLightShadowNearClippingKey NS_DEPRECATED(10_8, 10_10, NA, NA);

/*! @constant SCNLightShadowFarClippingKey Specifies the maximal distance between the light and a visible surface to cast shadow on. If a surface is further from the light than this maximal distance, then the surface won't be shadowed. Animatable as "zFar". Defaults to 100. */
SCN_EXTERN NSString * const SCNLightShadowFarClippingKey NS_DEPRECATED(10_8, 10_10, NA, NA);


NS_ASSUME_NONNULL_END

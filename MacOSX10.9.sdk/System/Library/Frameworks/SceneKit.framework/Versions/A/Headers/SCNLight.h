//
//  SCNLight.h
//
//  Copyright (c) 2012-2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>



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

/*!
 @group Light Attributes
 @abstract Attributes affecting the lighting computations.
 */
/*! @constant SCNLightAttenuationStartKey The distance at which the attenuation starts (Omni or Spot light types only). Animatable as "attenuationStart". Defaults to 0. */
SCN_EXTERN NSString * const SCNLightAttenuationStartKey;

/*! @constant SCNLightAttenuationEndKey The distance at which the attenuation ends (Omni or Spot light types only). Animatable as "attenuationEnd". Defaults to 0. */
SCN_EXTERN NSString * const SCNLightAttenuationEndKey;

/*! @constant SCNLightAttenuationFalloffExponentKey Controls the attenuation between the start and end attenuation distances. 0 means a constant attenuation, 1 a linear attenuation and 2 a quadratic attenuation, but any positive value will work (Omni or Spot light types only). Animatable as "attenuationFalloffExponent". Defaults to 2. */
SCN_EXTERN NSString * const SCNLightAttenuationFalloffExponentKey;

/*! @constant SCNLightSpotInnerAngleKey The angle in degrees between the spot direction and the lit element below which the lighting is at full strength. Animatable as "spotInnerAngle". Defaults to 0. */
SCN_EXTERN NSString * const SCNLightSpotInnerAngleKey;

/*! @constant SCNLightSpotOuterAngleKey The angle in degrees between the spot direction and the lit element after which the lighting is at zero strength. Animatable as "spotOuterAngle". Defaults to 45 degrees. */
SCN_EXTERN NSString * const SCNLightSpotOuterAngleKey;

/*! @constant SCNLightShadowNearClippingKey Specifies the minimal distance between the light and the surface to cast shadow on.  If a surface is closer to the light than this minimal distance, then the surface won't be shadowed. The near value must be different than zero. Animatable as "zNear". Defaults to 1. */
SCN_EXTERN NSString * const SCNLightShadowNearClippingKey;

/*! @constant SCNLightShadowFarClippingKey Specifies the maximal distance between the light and a visible surface to cast shadow on. If a surface is further from the light than this maximal distance, then the surface won't be shadowed. Animatable as "zFar". Defaults to 100. */
SCN_EXTERN NSString * const SCNLightShadowFarClippingKey;

/*!
 @class SCNLight
 @abstract SCNLight represents a light that can be attached to a SCNNode. 
 */

SCENEKIT_CLASS_AVAILABLE(10_8, NA)
@interface SCNLight : NSObject <SCNAnimatable, NSCopying>
{
@private
	id _reserved;
}

/*! 
 @method light
 @abstract Creates and returns a light instance.
 */
+ (instancetype)light;

/*! 
 @property type
 @abstract Specifies the receiver's type.
 @discussion A light type can be one of the "Light Types" constants. Defaults to SCNLightTypeAmbient.
 */
@property(nonatomic, copy) NSString *type;

/*! 
 @property color
 @abstract Specifies the receiver's color (NSColor or CGColorRef). Animatable. Defaults to white.
 @discussion The initial value is a NSColor.
 */
@property(nonatomic, retain) id color;

/*! 
 @method attributeForKey:
 @param key The key for which to return the corresponding attribute.
 @abstract Returns the attribute for the specified key. The valid keys are described in the "Light Attributes" constants.
 */
- (id)attributeForKey:(NSString *)key;

/*! 
 @method setAttribute:forKey:
 @param attribute The attribute for the property identified by key. 
 @param key The name of a property.
 @abstract Set the specified attribute for the specified key. The valid keys are described in the "Light Attributes" constants.
 */
- (void)setAttribute:(id)attribute forKey:(NSString *)key;

/*! 
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy) NSString *name;

/*! 
 @property castsShadow
 @abstract Determines whether the receiver casts a shadow. Defaults to NO.
 @discussion Shadows are only supported by spot lights.
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
 @property gobo
 @abstract Specifies the gobo (or "cookie") of the light, used to control the shape of emitted light. Defaults to nil.
 @discussion Gobos are only supported by spot lights.
 */
@property(nonatomic, readonly) SCNMaterialProperty *gobo SCENEKIT_AVAILABLE(10_9, NA);

@end


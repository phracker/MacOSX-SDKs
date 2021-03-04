//
//  SceneKitDeprecated.h
//  SceneKit
//
//  Copyright © 2012-2018 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @group Light Attributes
 @abstract Attributes affecting the lighting computations.
 @discussion These keys are deprecated in 10.10. Please use the properties of SCNLight instead.
 */
/*! @constant SCNLightAttenuationStartKey The distance at which the attenuation starts (Omni or Spot light types only). Animatable as "attenuationStart". Defaults to 0. */
SCN_EXPORT NSString * const SCNLightAttenuationStartKey API_DEPRECATED("Use SCNLight.attenuationStartDistance instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*! @constant SCNLightAttenuationEndKey The distance at which the attenuation ends (Omni or Spot light types only). Animatable as "attenuationEnd". Defaults to 0. */
SCN_EXPORT NSString * const SCNLightAttenuationEndKey API_DEPRECATED("Use SCNLight.attenuationEndDistance instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*! @constant SCNLightAttenuationFalloffExponentKey Controls the attenuation between the start and end attenuation distances. 0 means a constant attenuation, 1 a linear attenuation and 2 a quadratic attenuation, but any positive value will work (Omni or Spot light types only). Animatable as "attenuationFalloffExponent". Defaults to 2. */
SCN_EXPORT NSString * const SCNLightAttenuationFalloffExponentKey API_DEPRECATED("Use SCNLight.attenuationFalloffExponent instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*! @constant SCNLightSpotInnerAngleKey The angle in degrees between the spot direction and the lit element below which the lighting is at full strength. Animatable as "spotInnerAngle". Defaults to 0. */
SCN_EXPORT NSString * const SCNLightSpotInnerAngleKey API_DEPRECATED("Use SCNLight.spotInnerAngle instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*! @constant SCNLightSpotOuterAngleKey The angle in degrees between the spot direction and the lit element after which the lighting is at zero strength. Animatable as "spotOuterAngle". Defaults to 45 degrees. */
SCN_EXPORT NSString * const SCNLightSpotOuterAngleKey API_DEPRECATED("Use SCNLight.spotOuterAngle instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*! @constant SCNLightShadowNearClippingKey Specifies the minimal distance between the light and the surface to cast shadow on. If a surface is closer to the light than this minimal distance, then the surface won't be shadowed. The near value must be different than zero. Animatable as "zNear". Defaults to 1. */
SCN_EXPORT NSString * const SCNLightShadowNearClippingKey API_DEPRECATED("Use SCNLight.zNear instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*! @constant SCNLightShadowFarClippingKey Specifies the maximal distance between the light and a visible surface to cast shadow on. If a surface is further from the light than this maximal distance, then the surface won't be shadowed. Animatable as "zFar". Defaults to 100. */
SCN_EXPORT NSString * const SCNLightShadowFarClippingKey API_DEPRECATED("Use SCNLight.zFar instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);


@interface SCNLight (SCNDeprecated) <SCNTechniqueSupport>

/*!
 @method attributeForKey:
 @param key The key for which to return the corresponding attribute.
 @abstract Returns the attribute for the specified key. The valid keys are described in the "Light Attributes" constants.
 */
- (nullable id)attributeForKey:(NSString *)key API_DEPRECATED("Use SCNLight properties instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
 @method setAttribute:forKey:
 @param attribute The attribute for the property identified by key.
 @param key The name of a property.
 @abstract Set the specified attribute for the specified key. The valid keys are described in the "Light Attributes" constants.
 */
- (void)setAttribute:(nullable id)attribute forKey:(NSString *)key API_DEPRECATED("Use SCNLight properties instead", macos(10.8, 10.10)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);
@end


@interface SCNCamera (SCNDeprecated)

/*!
 @property focalBlurRadius
 @abstract Determines the receiver's focal radius. Animatable.
 @discussion Determines the maximum amount of blur for objects out of focus. Defaults to 0.
 */
@property(nonatomic) CGFloat focalBlurRadius API_DEPRECATED("Use fStop instead", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property xFov
 @abstract Determines the receiver's field of view on the X axis (in degree). Animatable.
 @discussion When both xFov and yFov are null an yFov of 60° is used. When both are set, the one that best fits the renderer's aspect ratio is used. When only one is set, it is used. Defaults to 0.
 */
@property(nonatomic) double xFov API_DEPRECATED("Use -[SCNCamera fieldOfView] or -[SCNCamera focalLength] instead", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property yFov
 @abstract Determines the receiver's field of view on the Y axis (in degree). Animatable.
 @discussion When both xFov and yFov are null an yFov of 60° is used. When both are set, the one that best fits the renderer's aspect ratio is used. When only one is set, it is used. Defaults to 0.
 */
@property(nonatomic) double yFov API_DEPRECATED("Use -[SCNCamera fieldOfView] or -[SCNCamera focalLength] instead", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property aperture
 @abstract Determines the receiver's aperture. Animatable.
 @discussion Defaults to 1/8.0.
 */
@property(nonatomic) CGFloat aperture API_DEPRECATED("Use -[SCNCamera fStop] instead with fStop = sensorHeight / aperture.", macos(10.8, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property focalSize
 @abstract Determines the receiver's focal size. Animatable.
 @discussion Determines the size of the area around focalDistance where the objects are in focus. Defaults to 0.
 */
@property(nonatomic) CGFloat focalSize API_DEPRECATED_WITH_REPLACEMENT("-focusDistance", macos(10.9, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

/*!
 @property focalDistance
 @abstract Determines the receiver's focal distance. Animatable.
 @discussion When non zero, the focal distance determines how the camera focuses the objects in the 3d scene. Defaults to 10.0 prior to macOS 10.13, iOS 11, tvOS 11 and watchOS 4. Defaults to 2.5 otherwise.
 */
@property(nonatomic) CGFloat focalDistance API_DEPRECATED_WITH_REPLACEMENT("-focusDistance", macos(10.9, 10.13), ios(8.0, 11.0), tvos(9.0, 11.0), watchos(3.0, 4.0));

@end


@interface SCNRenderer (SCNDeprecated)

// Deprecated
/*!
 @method render
 @abstract renders the receiver's scene at the current system time.
 @discussion This method only work if the receiver was allocated with an OpenGL context and it is deprecated (use renderAtTime: instead). Use renderAtTime:withEncoder:pass:commandQueue: to render with Metal.
 */
- (void)render API_DEPRECATED_WITH_REPLACEMENT("-renderAtTime:withEncoder:pass:commandQueue:", macos(10.8, 10.11), ios(8.0, 9.0)) API_UNAVAILABLE(watchos, tvos, macCatalyst);

@end


@interface SCNMaterialProperty (SCNDeprecated)

/*!
 @property borderColor
 @abstract Determines the receiver's border color (CGColorRef or NSColor). Animatable.
 @discussion The border color is ignored on iOS and is always considered as clear color (0,0,0,0) when the texture has an alpha channel and opaque back (0,0,0,1) otherwise.
 */
@property(nonatomic, retain, nullable) id borderColor API_DEPRECATED("Deprecated", macos(10.8, 10.12), ios(8.0, 10.0)) API_UNAVAILABLE(watchos, tvos, macCatalyst);

@end

NS_ASSUME_NONNULL_END

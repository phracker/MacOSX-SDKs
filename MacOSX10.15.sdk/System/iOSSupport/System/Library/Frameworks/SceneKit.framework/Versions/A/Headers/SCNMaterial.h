//
//  SCNMaterial.h
//  SceneKit
//
//  Copyright © 2012-2019 Apple Inc. All rights reserved.
//

#import <SceneKit/SceneKitTypes.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNShadable.h>

NS_ASSUME_NONNULL_BEGIN

/*
 Constants for lightingModel
 
 For every lighting model, the final color is computed as follows:
   finalColor = (<emission> + color + <reflective>) * <multiply>
 where
   <emission> — The 'emission' property of the SCNMaterial instance
   <reflective> — The 'reflective' property of the SCNMaterial instance
   <multiply> — The 'multiply' property of the SCNMaterial instance
 and
   color - The 'color' term depends on the lighting models described below
 
 SCNLightingModelPhong:
   Produces a specularly shaded surface where the specular reflection is shaded according the Phong BRDF approximation.
   The reflected color is calculated as:
     color = <ambient> * al + <diffuse> * max(N ⋅ L, 0) + <specular> * pow(max(R ⋅ E, 0), <shininess>)
   where
     al — Sum of all ambient lights currently active (visible) in the scene
     N — Normal vector
     L — Light vector
     E — Eye vector
     R — Perfect reflection vector (reflect (L around N))
   and
     <ambient> — The 'ambient' property of the SCNMaterial instance
     <diffuse> — The 'diffuse' property of the SCNMaterial instance
     <specular> — The 'specular' property of the SCNMaterial instance
     <shininess> — The 'shininess' property of the SCNMaterial instance
 
 SCNLightingModelBlinn:
   Produces a specularly shaded surface with a Blinn BRDF approximation.
   The reflected color is calculated as:
     color = <ambient> * al + <diffuse> * max(N ⋅ L, 0) + <specular> * pow(max(H ⋅ N, 0), <shininess>)
   where
     al — Sum of all ambient lights currently active (visible) in the scene
     N — Normal vector
     L — Light vector
     E — Eye vector
     H — Half-angle vector, calculated as halfway between the unit Eye and Light vectors, using the equation H = normalize(E + L)
   and
     <ambient> — The 'ambient' property of the SCNMaterial instance
     <diffuse> — The 'diffuse' property of the SCNMaterial instance
     <specular> — The 'specular' property of the SCNMaterial instance
     <shininess> — The 'shininess' property of the SCNMaterial instance
 
 SCNLightingModelLambert:
   Produces a diffuse shaded surface with no specular reflection.
   The result is based on Lambert’s Law, which states that when light hits a rough surface, the light is reflected in all directions equally.
   The reflected color is calculated as:
     color = <ambient> * al + <diffuse> * max(N ⋅ L, 0)
   where
     al — Sum of all ambient lights currently active (visible) in the scene
     N — Normal vector
     L — Light vector
   and
     <ambient> — The 'ambient' property of the SCNMaterial instance
     <diffuse> — The 'diffuse' property of the SCNMaterial instance
 
 SCNLightingModelConstant:
   Produces a constantly shaded surface that is independent of lighting.
   The reflected color is calculated as:
     color = <ambient> * al + <diffuse>
   where
     al — Sum of all ambient lights currently active (visible) in the scene
   and
     <ambient> — The 'ambient' property of the SCNMaterial instance
     <diffuse> — The 'diffuse' property of the SCNMaterial instance

 SCNLightingModelShadowOnly:
    Produces a shaded surface that only renders received shadows.
    Use this lighting model in combination with a multiply blend mode to compose shadows over the background.
    The typical use case is to use on a plane that receive shadows in a AR application.
    The shadow intensity can be adjusted using the alpha of the lights's shadow color.
 */

typedef NSString * SCNLightingModel NS_STRING_ENUM;
SCN_EXPORT SCNLightingModel const SCNLightingModelPhong;
SCN_EXPORT SCNLightingModel const SCNLightingModelBlinn;
SCN_EXPORT SCNLightingModel const SCNLightingModelLambert;
SCN_EXPORT SCNLightingModel const SCNLightingModelConstant;
SCN_EXPORT SCNLightingModel const SCNLightingModelPhysicallyBased API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));
SCN_EXPORT SCNLightingModel const SCNLightingModelShadowOnly API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

typedef NS_ENUM(NSUInteger, SCNFillMode) {
    SCNFillModeFill  = 0,
    SCNFillModeLines = 1
} API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

typedef NS_ENUM(NSInteger, SCNCullMode) {
	SCNCullModeBack  = 0,
	SCNCullModeFront = 1
};

#define SCNCullBack  SCNCullModeBack
#define SCNCullFront SCNCullModeFront

typedef NS_ENUM(NSInteger, SCNTransparencyMode) {
    SCNTransparencyModeAOne                                                                         = 0, // Takes the transparency information from the alpha channel. The value 1.0 is opaque.
    SCNTransparencyModeRGBZero                                                                      = 1, // Ignores the alpha channel and takes the transparency information from the luminance of the red, green, and blue channels. The value 0.0 is opaque.
    SCNTransparencyModeSingleLayer API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 2, // Ensures that one layer of transparency is draw correctly.
    SCNTransparencyModeDualLayer   API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 3, // Ensures that two layers of transparency are ordered and drawn correctly. This should be used for transparent convex objects like cubes and spheres, when you want to see both front and back faces.
    SCNTransparencyModeDefault     API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = SCNTransparencyModeAOne
};

/*! 
 @enum SCNBlendMode
 @abstract  Blend modes that SCNMaterial uses to compose with the framebuffer to produce blended colors.
 */
typedef NS_ENUM(NSInteger, SCNBlendMode) {
    SCNBlendModeAlpha                                                                     = 0, // Blends the source and destination colors by adding the source multiplied by source alpha and the destination multiplied by one minus source alpha.
    SCNBlendModeAdd                                                                       = 1, // Blends the source and destination colors by adding them up.
    SCNBlendModeSubtract                                                                  = 2, // Blends the source and destination colors by subtracting the source from the destination.
    SCNBlendModeMultiply                                                                  = 3, // Blends the source and destination colors by multiplying them.
    SCNBlendModeScreen                                                                    = 4, // Blends the source and destination colors by multiplying one minus the source with the destination and adding the source.
    SCNBlendModeReplace                                                                   = 5, // Replaces the destination with the source (ignores alpha).
    SCNBlendModeMax      API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0)) = 6  // Max the destination with the source (ignores alpha).
} API_AVAILABLE(macos(10.11), ios(9.0));

@class SCNMaterialProperty;
@class SCNProgram;
@protocol SCNProgramDelegate;
@protocol SCNShadable;

/*!
 @class SCNMaterial
 @abstract A SCNMaterial determines how a geometry is rendered. It encapsulates the colors and textures that define the appearance of 3d geometries.
 */

SCN_EXPORT
@interface SCNMaterial : NSObject <SCNAnimatable, SCNShadable, NSCopying, NSSecureCoding>

/*! 
 @method material
 @abstract Creates and initialize a material instance.
 */
+ (instancetype)material;

/*! 
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy, nullable) NSString *name;

// MARK: - Material Properties

/*! 
 @property diffuse
 @abstract Specifies the receiver's diffuse property.
 @discussion The diffuse property specifies the amount of light diffusely reflected from the surface. The diffuse light is reflected equally in all directions and is therefore independent of the point of view.
 */
@property(nonatomic, readonly) SCNMaterialProperty *diffuse;

/*! 
 @property ambient
 @abstract Specifies the receiver's ambient property.
 @discussion The ambient property specifies the amount of ambient light to reflect. This property has no visual impact on scenes that have no ambient light. Setting the ambient has no effect if locksAmbientWithDiffuse is set to YES.
 */
@property(nonatomic, readonly) SCNMaterialProperty *ambient;

/*! 
 @property specular
 @abstract Specifies the receiver's specular property.
 @discussion The specular property specifies the amount of light to reflect in a mirror-like manner. The specular intensity increases when the point of view lines up with the direction of the reflected light.
 */
@property(nonatomic, readonly) SCNMaterialProperty *specular;

/*! 
 @property emission
 @abstract The emission property specifies the amount of light the material emits. This emission does not light up other surfaces in the scene.
 */
@property(nonatomic, readonly) SCNMaterialProperty *emission;

/*! 
 @property transparent
 @abstract The transparent property specifies the transparent areas of the material.
 */
@property(nonatomic, readonly) SCNMaterialProperty *transparent;

/*! 
 @property reflective
 @abstract The reflective property specifies the reflectivity of the surface. The surface will not actually reflect other objects in the scene. This property may be used as a sphere mapping to reflect a precomputed environment.
 */
@property(nonatomic, readonly) SCNMaterialProperty *reflective;

/*! 
 @property multiply
 @abstract The multiply property specifies a color or an image used to multiply the output fragments with. The computed fragments are multiplied with the multiply value to produce the final fragments. This property may be used for shadow maps, to fade out or tint 3d objects.
 */
@property(nonatomic, readonly) SCNMaterialProperty *multiply;

/*! 
 @property normal
 @abstract The normal property specifies the surface orientation. 
 @discussion When an image is set on the normal property the material is automatically lit per pixel. Setting a color has no effect.
 */
@property(nonatomic, readonly) SCNMaterialProperty *normal;

/*!
 @property displacement
 @abstract The displacement property specifies how vertex are translated in tangent space.
 @discussion Pass a grayscale image for a simple 'elevation' or rgb image for a vector displacement.
 */
@property(nonatomic, readonly) SCNMaterialProperty *displacement API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property ambientOcclusion
 @abstract The ambientOcclusion property specifies the ambient occlusion of the surface. The ambient occlusion is multiplied with the ambient light, then the result is added to the lighting contribution. This property has no visual impact on scenes that have no ambient light. When an ambient occlusion map is set, the ambient property is ignored.
 */
@property(nonatomic, readonly) SCNMaterialProperty *ambientOcclusion API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property selfIllumination
 @abstract The selfIllumination property specifies a texture or a color that is added to the lighting contribution of the surface. When a selfIllumination is set, the emission property is ignored.
 */
@property(nonatomic, readonly) SCNMaterialProperty *selfIllumination API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @property metalness
 @abstract The metalness property specifies how metallic the material's surface appears. Lower values (darker colors) cause the material to appear more like a dielectric surface. Higher values (brighter colors) cause the surface to appear more metallic. This property is only used when 'lightingModelName' is 'SCNLightingModelPhysicallyBased'.
 */
@property(nonatomic, readonly) SCNMaterialProperty *metalness API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property roughness
 @abstract The roughness property specifies the apparent smoothness of the surface. Lower values (darker colors) cause the material to appear shiny, with well-defined specular highlights. Higher values (brighter colors) cause specular highlights to spread out and the diffuse property of the material to become more retroreflective. This property is only used when 'lightingModelName' is 'SCNLightingModelPhysicallyBased'.
 */
@property(nonatomic, readonly) SCNMaterialProperty *roughness API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));

/*!
 @property clearCoat
 @abstract The clearCoat property specifies color and intensity of the coat layer.
 */
@property(nonatomic, readonly) SCNMaterialProperty *clearCoat API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property clearCoatRoughness
 @abstract The clearCoat property specifies color and intensity of the coat roughness.
 */
@property(nonatomic, readonly) SCNMaterialProperty *clearCoatRoughness API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property clearCoatNormal
 @abstract The clearCoatNormal property specifies color and intensity of the optional coat normal map.
 */
@property(nonatomic, readonly) SCNMaterialProperty *clearCoatNormal API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));


// MARK: -

/*! 
 @property shininess
 @abstract Specifies the receiver's shininess value. Defaults to 1.0. Animatable.
 */
@property(nonatomic) CGFloat shininess;

/*! 
 @property transparency
 @abstract Specifies the receiver's transparency value. Defaults to 1.0. Animatable.
 @discussion The color of the transparent property is multiplied by this property. The result is then used to produce the final transparency according to the rule defined by the transparencyMode property.
 */
@property(nonatomic) CGFloat transparency;

/*!
 @property lightingModelName
 @abstract Determines the receiver's lighting model. See above for the list of lighting models. Defaults to SCNLightingModelBlinn.
 */
@property(nonatomic, copy) SCNLightingModel lightingModelName;

/*! 
 @property litPerPixel
 @abstract Determines whether the receiver is lit per pixel. Defaults to YES. Animatable.
 */
@property(nonatomic, getter=isLitPerPixel) BOOL litPerPixel;

/*! 
 @property doubleSided
 @abstract Determines whether the receiver is double sided. Defaults to NO. Animatable.
 */
@property(nonatomic, getter=isDoubleSided) BOOL doubleSided;

/*!
 @property fillMode
 @abstract Determines of to how to rasterize the receiver's primitives. Defaults to SCNFillModeFill.
 */
@property(nonatomic) SCNFillMode fillMode API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*! 
 @property cullMode
 @abstract Determines the culling mode of the receiver. Defaults to SCNCullBack. Animatable.
 */
@property(nonatomic) SCNCullMode cullMode;

/*! 
 @property transparencyMode
 @abstract Determines the transparency mode of the receiver. See above for the transparency modes. Defaults to SCNTransparencyModeDefault.
 */
@property(nonatomic) SCNTransparencyMode transparencyMode;

/*! 
 @property locksAmbientWithDiffuse
 @abstract Makes the ambient property automatically match the diffuse property. Defaults to YES. Animatable.
 */
@property(nonatomic) BOOL locksAmbientWithDiffuse;

/*! 
 @property writeToDepthBuffer
 @abstract Determines whether the receiver writes to the depth buffer when rendered. Defaults to YES.
 */
@property(nonatomic) BOOL writesToDepthBuffer;

/*!
 @abstract Determines whether the receiver writes to the color buffer when rendered. Defaults to SCNColorMaskAll.
 */
@property(nonatomic) SCNColorMask colorBufferWriteMask API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property readsFromDepthBuffer
 @abstract Determines whether the receiver reads from the depth buffer when rendered. Defaults to YES.
 */
@property(nonatomic) BOOL readsFromDepthBuffer API_AVAILABLE(macos(10.9));

/*!
 @property fresnelExponent
 @abstract Specifies the receiver's fresnel exponent value. Defaults to 0.0. Animatable.
 @discussion The effect of the reflectivity property is modulated by this property. The fresnelExponent changes the exponent of the reflectance. The bigger the exponent, the more concentrated the reflection is around the edges.
 */
@property(nonatomic) CGFloat fresnelExponent API_AVAILABLE(macos(10.9));

/*!
 @property blendMode
 @abstract Specifies the receiver's blend mode. Defaults to SCNBlendModeAlpha.
 */
@property(nonatomic) SCNBlendMode blendMode API_AVAILABLE(macos(10.11), ios(9.0));

@end
    
NS_ASSUME_NONNULL_END

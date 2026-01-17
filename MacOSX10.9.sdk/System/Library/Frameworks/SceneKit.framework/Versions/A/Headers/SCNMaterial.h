//
//  SCNMaterial.h
//
//  Copyright (c) 2012-2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNShadable.h>

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
     color = <ambient> * al + <diffuse> * max(N . L, 0) + <specular> * pow(max(R . E, 0), <shininess>)
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
     color = <ambient> * al + <diffuse> * max(N . L, 0) + <specular> * pow(max(H . N, 0), <shininess>)
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
     color = <ambient> * al + <diffuse> * max(N . L, 0)
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
 */

SCN_EXTERN NSString * const SCNLightingModelPhong;
SCN_EXTERN NSString * const SCNLightingModelBlinn;
SCN_EXTERN NSString * const SCNLightingModelLambert;
SCN_EXTERN NSString * const SCNLightingModelConstant;

//key for setSemantic:forSymbol:options: options
SCN_EXTERN NSString * const SCNProgramMappingChannelKey;  /* This key is optional and may be used in association with the SCNGeometrySourceSemanticTexcoord semantic. It allows to associates a mapping channel from the geometry to a symbol from the program source code. The mapping channel allows to plug programs that work with multiple texture coordinates. The associated value must be a NSNumber(integer) greater than zero. */

//face culling modes
typedef NS_ENUM(NSInteger, SCNCullMode) {
	SCNCullBack  = 0,
	SCNCullFront = 1,
};

//transparency modes
typedef NS_ENUM(NSInteger, SCNTransparencyMode) {
	SCNTransparencyModeAOne    = 0, 
	SCNTransparencyModeRGBZero = 1, 
};

@class SCNMaterialProperty;
@class SCNProgram;
@protocol SCNProgramDelegate;
@protocol SCNShadable;

/*!
 @class SCNMaterial
 @abstract A SCNMaterial determines how a geometry is rendered. It encapsulates the colors and textures that define the appearance of 3d geometries.
 */

SCENEKIT_CLASS_AVAILABLE(10_8, NA)
@interface SCNMaterial : NSObject <SCNAnimatable, SCNShadable, NSCopying>
{	
@private
	id _reserved;
}

/*! 
 @method material
 @abstract Creates and initialize a material instance.
 */
+ (instancetype)material;

/*! 
 @property name
 @abstract Determines the name of the receiver.
 */
@property(nonatomic, copy) NSString *name;

/*! 
 @property diffuse
 @abstract Specifies the receiver's diffuse property.
 @discussion The diffuse property specifies the amount of light diffusely reflected from the surface. The diffuse light is reflected equally in all directions and is therefore independent of the point of view.
 */
@property(nonatomic, readonly) SCNMaterialProperty *diffuse;

/*! 
 @property ambient
 @abstract Specifies the receiver's ambient property.
 @discussion The ambient property specifies the amount of ambient light to reflect. This property has no visual impact on scenes that have no ambient light.
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
@property(nonatomic, copy) NSString *lightingModelName;

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
 @property cullMode
 @abstract Determines the culling mode of the receiver. Defaults to SCNCullBack. Animatable.
 */
@property(nonatomic) SCNCullMode cullMode;

/*! 
 @property transparencyMode
 @abstract Determines the transparency mode of the receiver. See above for the transparency modes. Defaults to SCNTransparencyModeAOne.
 @discussion SCNTransparencyModeAOne takes the transparency information from the color's alpha channel. The value 1.0 is opaque. 
 SCNTransparencyModeRGBZero takes the transparency information from the color's red, green, and blue channels. The value 0.0 is opaque, with each channel modulated independently. With SCNTransparencyModeRGBZero, the alpha value of the transparent property is ignored.
 */
@property(nonatomic) SCNTransparencyMode transparencyMode;

/*! 
 @property locksAmbientWithDiffuse
 @abstract Makes the ambient property automatically match the diffuse property. Defaults to NO. Animatable.
 */
@property(nonatomic) BOOL locksAmbientWithDiffuse;

/*! 
 @property writeToDepthBuffer
 @abstract Determines whether the receiver writes to the depth buffer when rendered. Defaults to YES.
 */
@property(nonatomic) BOOL writesToDepthBuffer;

/*!
 @property readsFromDepthBuffer
 @abstract Determines whether the receiver reads from the depth buffer when rendered. Defaults to YES.
 */
@property(nonatomic) BOOL readsFromDepthBuffer SCENEKIT_AVAILABLE(10_9, NA);

/*!
 @property fresnelExponent
 @abstract Specifies the receiver's fresnel exponent value. Defaults to 0.0. Animatable.
 @discussion The effect of the reflectivity property is modulated by this property. The fresnelExponent changes the exponent of the reflectance. The bigger the exponent, the more concentrated the reflection is around the edges.
 */
@property(nonatomic) CGFloat fresnelExponent SCENEKIT_AVAILABLE(10_9, NA);


@end


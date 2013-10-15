//
//  SCNMaterial.h
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>


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

SCENEKIT_EXTERN NSString *const SCNLightingModelPhong SCENEKIT_AVAILABLE(10_7, NA);
SCENEKIT_EXTERN NSString *const SCNLightingModelBlinn SCENEKIT_AVAILABLE(10_7, NA);
SCENEKIT_EXTERN NSString *const SCNLightingModelLambert SCENEKIT_AVAILABLE(10_7, NA);
SCENEKIT_EXTERN NSString *const SCNLightingModelConstant SCENEKIT_AVAILABLE(10_7, NA);

//key for setSemantic:forSymbol:options: options
SCENEKIT_EXTERN NSString *const SCNProgramMappingChannelKey SCENEKIT_AVAILABLE(10_7, NA);  /* This key is optional and may be used in association with the SCNGeometrySourceSemanticTexcoord semantic. It allows to associates a mapping channel from the geometry to a symbol from the program source code. The mapping channel allows to plug programs that work with multiple texture coordinates. The associated value must be a NSNumber(integer) greater than zero. */

//face culling modes
typedef enum
{
	SCNCullBack  = 0,
	SCNCullFront = 1,
} SCNCullMode;

//transparency modes
typedef enum
{
	SCNTransparencyModeAOne    = 0, 
	SCNTransparencyModeRGBZero = 1, 
} SCNTransparencyMode;

@class SCNMaterialProperty;
@class SCNProgram;
@protocol SCNProgramDelegate;

/*!
 @class SCNMaterial
 @abstract A SCNMaterial determines how a geometry is rendered. It encapsulates the colors and textures that define the appearance of 3d geometries.
 */

SCENEKIT_AVAILABLE(10_7, NA)
@interface SCNMaterial : NSObject <SCNAnimatable, NSCopying>
{	
@private
	id _reserved;
}

/*! 
 @method material
 @abstract Creates and initialize a material instance.
 */
+ (SCNMaterial *)material;

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
 @abstract Determines the transparency mode of the receiver. See above for the transparency modes. Default to SCNTransparencyModeAOne.
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
 @property program
 @abstract Specifies a custom program used to render this material.
 */
@property(nonatomic, retain) SCNProgram *program;

@end

/*! @class SCNProgram
    @abstract A SCNProgram lets you specify custom shaders to use when rendering materials.
 */

SCENEKIT_AVAILABLE(10_7, NA)
@interface SCNProgram : NSObject <NSCopying>
{	
@private
	id _reserved;
}

/*! 
 @method program
 @abstract Creates and initialize a program instance.
 */
+ (SCNProgram *) program;

/*! 
 @property vertexShader
 @abstract Determines the receiver's vertex shader.
 */
@property(nonatomic, copy) NSString *vertexShader;

/*! 
 @property fragmentShader
 @abstract Determines the receiver's fragment shader.
 */
@property(nonatomic, copy) NSString *fragmentShader;

/*! 
 @method		setSemantic:forSymbol:
 @abstract		Associates a SceneKit semantic to a symbol. 
 @param			semantic from SceneKit engine to be used.
 @param			symbol from program source code.
 @param        options an optional dictionary. See the available keys above.
 @discussion	Associates semantics handled by SceneKit runtime to a symbol from the program.
				supported semantics for program attributes are: SCNGeometrySourceSemanticVertex,SCNGeometrySourceSemanticNormal,SCNGeometrySourceSemanticColor,SCNGeometrySourceSemanticTexcoord 
				and the following for program uniforms: SCNModelViewProjectionTransform,SCNModelViewTransform,SCNModelTransform,SCNViewTransform,SCNProjectionTransform,SCNNormalTransform
 */
- (void)setSemantic:(NSString*)semantic forSymbol:(NSString*)symbol options:(NSDictionary *)options;

/*! 
 @method semanticForSymbol:
 @abstract retrieves the SceneKit runtime semantic associated to a symbol from the program source code.
 @param symbol from program source code
 */ 
- (NSString*)semanticForSymbol:(NSString*)symbol;

/*! 
 @property delegate
 @abstract Determines the receiver's delegate
 */
@property(nonatomic, assign) id <SCNProgramDelegate> delegate;

@end

/*!
 @protocol SCNProgramDelegate
 @abstract The SCNProgramDelegate protocol declares the methods that an instance of SCNProgram invokes to delegate the binding of parameters.
 */
@protocol SCNProgramDelegate <NSObject>

@optional
/*! 
 @method program:withID:bindValueForSymbol:atLocation:renderer:
 @abstract Invoked on the delegate to let it bind program values and/or also bind associated graphics resources (such as textures).
 @param program The program to bind values for.
 @param symbol The name of the symbol to bind a value for.
 @param location The location of the symbol within the program object to be modified.
 @param programID The program object.
 @param renderer The renderer that is currently rendering the scene.
 */
- (BOOL)program:(SCNProgram*)program bindValueForSymbol:(NSString*)symbol atLocation:(unsigned int)location programID:(unsigned int)programID renderer:(SCNRenderer*)renderer;

/*! 
 @method program:withID:bindValueForSymbol:atLocation:renderer:
 @abstract Invoked on the delegate to let it unbind program values and/or also unbind associated graphic resources (such as textures).
 @param program The program to unbind values for.
 @param symbol The name of the symbol to unbind a value for.
 @param location The location of the symbol within the program object to be modified.
 @param programID The program object.
 @param renderer The renderer that is currently rendering the scene.
 */
- (void)program:(SCNProgram*)program unbindValueForSymbol:(NSString*)symbol atLocation:(unsigned int)location programID:(unsigned int)programID renderer:(SCNRenderer*)renderer;

/*! 
 @method handleError
 @abstract Invoked on the delegate whenever a compilation error occurs.
 @discussion Error domain is SCNErrorDomain.
 @param program The program that generated a compilation error.
 @param error The compilation error.
 */
- (void)program:(SCNProgram*)program handleError:(NSError*)error;

/*! 
 @method programIsOpaque
 @abstract The delegate should implement this mehod and return NO if the fragments generated by the program are not opaque.
 @param program The queried program.
 */
- (BOOL)programIsOpaque:(SCNProgram*)program;

@end

/*!
 @header MDLMaterial.h
 @framework ModelIO
 @abstract Structures for describing rendering material properties
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */


#pragma once

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <simd/simd.h>
#import <ModelIO/ModelIOExports.h>
#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLTransform.h>
#import <ModelIO/MDLAssetResolver.h>

NS_ASSUME_NONNULL_BEGIN

@class MDLTexture;

/**
 MDLMaterialSemantic
 
 @summary The material semantics are identifiers for material properties 
            formally identified by one of the standard material descriptors.
 
 @discussion When files containing material properties are loaded and translated 
             by ModelIO, an appropriate standard material descriptor will be 
             chosen, and any properties translated from the loaded file can be 
             retrieved using one of these semantics.
 
 MDLMaterialSemanticBaseColor
    The inherent color of a surface to be used as a modulator during shading. 
    Default is 50% gray
 
 MDLMaterialSemanticSubsurface,
    The degree to which light scatters under the surface of a material
 
 MDLMaterialSemanticMetallic
    A blend between a material behaving as a dielectric material at zero, and a 
    metal at one.
 
 MDLMaterialSemanticSpecular
    Specular response to incident light
 
 MDLMaterialSemanticSpecularExponent
    Power of the specular exponent in the case that a Blinn/Phong BSDF is in use.
 
 MDLMaterialSemanticSpecularTint
    At zero, the specular highlight will use the hue, saturation, and intensity 
    of incoming light to color the specular response; at one, the material's 
    base color, and the light's intensity will be used.
 
 MDLMaterialSemanticRoughness
    Controls diffuse and specular response. A value of zero is smooth and shiny. 
    At one, a diffuse material will retroreflect, and the specular highlight 
    will be very spread out.
 
 MDLMaterialSemanticAnisotropic
    The degree to which the specular highlight is elongated in the direction of 
    the local tangent basis. A mesh that does not have a tangent basis will not 
    respond to this parameter.
 
 MDLMaterialSemanticAnisotropicRotation
    The degree to which the anisotropy is rotated relative to the direction of the
    local tangent basis. Values from zero to one are mapped to zero to two PI.
 
 MDLMaterialSemanticSheen
    A specular tint that appears at glancing angles on an object
 
 MDLMaterialSemanticSheenTint
    At zero, the specular highlight will use the hue, saturation, and intensity 
    of incoming light to color the specular response; at one, the material's 
    base color, and the light's intensity will be used.
 
 MDLMaterialSemanticClearcoat
    A second specular highlight, much like the gloss that results from a clear 
    coat on an automotive finish
 
 MDLMaterialSemanticClearcoatGloss
    The glossiness of the clear coat highlight.

 MDLMaterialSemanticEmission
    A value that is to be emitted as radiance by a surface
 
 MDLMaterialSemanticBump
    A value that perturbs surface normals according to the local gradient of 
    the property
 
 MDLMaterialSemanticOpacity
    The opacity of the surface
 
 MDLMaterialSemanticInterfaceIndexOfRefraction
    n1 in Schlick's equation, typically 1.0 for air
 
 MDLMaterialSemanticMaterialIndexOfRefraction
    n2 in Schlick's equation

 MDLMaterialSemanticObjectSpaceNormal
    A value that perturbs surface normals in object space
 
 MDLMaterialSemanticTangentSpaceNormal
    A value that perturbs surface normals in a local tangent space

 MDLMaterialSemanticDisplacement
    Displacement of a surface relative to surface normal
 
 MDLMaterialSemanticDisplacementScale
    Scaling factor for displacement
 
 MDLMaterialSemanticAmbientOcclusion
    Ambient occlusion describes the accessibility of the surface to the 
    surrounding radiant environment and is typically used to attenuate it. It is 
    not intended to attenuate direct illumination sources.
 
 MDLMaterialSemanticAmbientOcclusionScale
    The degree to which the ambient occlusion values are applied
 
 MDLMaterialSemanticUserDefined = 0x8000
    Properties with this value are created when material properties are 
    translated for which no known semantic applies.
    Semantics defined at greater than this value are available to be user defined.
    The first value is also used to indicate

 */

typedef NS_ENUM(NSUInteger, MDLMaterialSemantic) {
    MDLMaterialSemanticBaseColor = 0,
    MDLMaterialSemanticSubsurface,
    MDLMaterialSemanticMetallic,
    MDLMaterialSemanticSpecular,
    MDLMaterialSemanticSpecularExponent,
    MDLMaterialSemanticSpecularTint,
    MDLMaterialSemanticRoughness,
    MDLMaterialSemanticAnisotropic,
    MDLMaterialSemanticAnisotropicRotation,
    MDLMaterialSemanticSheen,
    MDLMaterialSemanticSheenTint,
    MDLMaterialSemanticClearcoat,
    MDLMaterialSemanticClearcoatGloss,

    MDLMaterialSemanticEmission,
    MDLMaterialSemanticBump,
    MDLMaterialSemanticOpacity,
    MDLMaterialSemanticInterfaceIndexOfRefraction,
    MDLMaterialSemanticMaterialIndexOfRefraction,
    MDLMaterialSemanticObjectSpaceNormal,
    MDLMaterialSemanticTangentSpaceNormal,
    MDLMaterialSemanticDisplacement,
    MDLMaterialSemanticDisplacementScale,
    MDLMaterialSemanticAmbientOcclusion,
    MDLMaterialSemanticAmbientOcclusionScale,
    
    MDLMaterialSemanticNone = 0x8000,
    MDLMaterialSemanticUserDefined = 0x8001
};

typedef NS_ENUM(NSUInteger, MDLMaterialPropertyType) {
    MDLMaterialPropertyTypeNone = 0, // default resulting from [MDLMaterialProperty init]
    MDLMaterialPropertyTypeString,
    MDLMaterialPropertyTypeURL,
    MDLMaterialPropertyTypeTexture,
    MDLMaterialPropertyTypeColor,
    MDLMaterialPropertyTypeFloat,
    MDLMaterialPropertyTypeFloat2,
    MDLMaterialPropertyTypeFloat3,
    MDLMaterialPropertyTypeFloat4,
    MDLMaterialPropertyTypeMatrix44
};

/**
 Texture filtering
 */

typedef NS_ENUM(NSUInteger, MDLMaterialTextureWrapMode) {
    MDLMaterialTextureWrapModeClamp,
    MDLMaterialTextureWrapModeRepeat,
    MDLMaterialTextureWrapModeMirror,
};

typedef NS_ENUM(NSUInteger, MDLMaterialTextureFilterMode) {
    MDLMaterialTextureFilterModeNearest,
    MDLMaterialTextureFilterModeLinear,
};

typedef NS_ENUM(NSUInteger, MDLMaterialMipMapFilterMode) {
    MDLMaterialMipMapFilterModeNearest,
    MDLMaterialMipMapFilterModeLinear,
};

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLTextureFilter : NSObject
@property (nonatomic, assign) MDLMaterialTextureWrapMode sWrapMode;
@property (nonatomic, assign) MDLMaterialTextureWrapMode tWrapMode;
@property (nonatomic, assign) MDLMaterialTextureWrapMode rWrapMode;
@property (nonatomic, assign) MDLMaterialTextureFilterMode minFilter;
@property (nonatomic, assign) MDLMaterialTextureFilterMode magFilter;
@property (nonatomic, assign) MDLMaterialMipMapFilterMode mipFilter;
@end

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLTextureSampler : NSObject

@property (nonatomic, retain, nullable) MDLTexture *texture;
@property (nonatomic, retain, nullable) MDLTextureFilter *hardwareFilter;
@property (nonatomic, retain, nullable) MDLTransform *transform;

@end


/**
 If a color is encoded in a floatN property, it is to be interpreted as 
 a Rec 709 color.
 */

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLMaterialProperty : NSObject<MDLNamed, NSCopying>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic float:(float)value;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic float2:(vector_float2)value;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic float3:(vector_float3)value;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic float4:(vector_float4)value;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic matrix4x4:(matrix_float4x4)value;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic URL:(nullable NSURL*)URL;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic string:(nullable NSString *)string;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic textureSampler:(nullable MDLTextureSampler*)textureSampler;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic color:(CGColorRef)color;

- (void)setProperties:(MDLMaterialProperty *)property;

@property (nonatomic, assign) MDLMaterialSemantic semantic;
@property (nonatomic, assign) MDLMaterialPropertyType type;

/** @see MDLNamed */
@property (nonatomic, copy) NSString *name;

@property (nonatomic, copy, nullable) NSString *stringValue;
@property (nonatomic, copy, nullable) NSURL *URLValue;
@property (nonatomic, retain, nullable) MDLTextureSampler *textureSamplerValue;
@property (nullable, nonatomic) CGColorRef color;
@property (nonatomic, assign) float floatValue;
@property (nonatomic, assign) vector_float2 float2Value;
@property (nonatomic, assign) vector_float3 float3Value;
@property (nonatomic, assign) vector_float4 float4Value;
@property (nonatomic, assign) matrix_float4x4 matrix4x4;
@property (nonatomic, assign) float luminance;

@end

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0))
MDL_EXPORT
@interface MDLMaterialPropertyConnection : NSObject<MDLNamed>

- (instancetype)init NS_UNAVAILABLE;

/** Connects the output to the input */
- (instancetype)initWithOutput:(MDLMaterialProperty*)output
                         input:(MDLMaterialProperty*)input;

@property (nonatomic, weak, readonly) MDLMaterialProperty *output;
@property (nonatomic, weak, readonly) MDLMaterialProperty *input;

@end

API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0))
MDL_EXPORT
@interface MDLMaterialPropertyNode : NSObject<MDLNamed>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithInputs:(NSArray<MDLMaterialProperty*>*)inputs
                       outputs:(NSArray<MDLMaterialProperty*>*)outputs
            evaluationFunction:(void(^)(MDLMaterialPropertyNode*))function;

@property (nonatomic, copy) void(^evaluationFunction)(MDLMaterialPropertyNode*);

@property (nonatomic, readonly) NSArray<MDLMaterialProperty*> *inputs;
@property (nonatomic, readonly) NSArray<MDLMaterialProperty*> *outputs;

@end

/**
 @discussion inputs and outputs will contain all of the inputs and outputs
             external to the graph, which are all the inputs and outputs not
             internally connected to something
 */
API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0))
MDL_EXPORT
@interface MDLMaterialPropertyGraph : MDLMaterialPropertyNode

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithNodes:(NSArray<MDLMaterialPropertyNode*>*)nodes
                  connections:(NSArray<MDLMaterialPropertyConnection*>*)connections;

- (void)evaluate;

@property (nonatomic, readonly) NSArray<MDLMaterialPropertyNode*> *nodes;
@property (nonatomic, readonly) NSArray<MDLMaterialPropertyConnection*> *connections;

@end

/**
 The base scattering function is Lambertian, with a Blinn-Phong specular response.
 Specular power for Blinn-Phong can be derived from the roughness property using 
 an approximation.
 */

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLScatteringFunction : NSObject<MDLNamed>

/** @see MDLNamed */
@property (nonatomic, copy) NSString *name;

@property (nonatomic, readonly, retain) MDLMaterialProperty *baseColor;
@property (nonatomic, readonly, retain) MDLMaterialProperty *emission;
@property (nonatomic, readonly, retain) MDLMaterialProperty *specular;
@property (nonatomic, readonly, retain) MDLMaterialProperty *materialIndexOfRefraction;
@property (nonatomic, readonly, retain) MDLMaterialProperty *interfaceIndexOfRefraction;
@property (nonatomic, readonly, retain) MDLMaterialProperty *normal;
@property (nonatomic, readonly, retain) MDLMaterialProperty *ambientOcclusion;
@property (nonatomic, readonly, retain) MDLMaterialProperty *ambientOcclusionScale;

@end

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLPhysicallyPlausibleScatteringFunction : MDLScatteringFunction

@property (nonatomic, readonly) NSInteger version; // currently 1

@property (nonatomic, readonly, retain) MDLMaterialProperty *subsurface;           // diffuse shape
@property (nonatomic, readonly, retain) MDLMaterialProperty *metallic;             // 0 = dielectric, 1 = metallic
@property (nonatomic, readonly, retain) MDLMaterialProperty *specularAmount;       // specular value
@property (nonatomic, readonly, retain) MDLMaterialProperty *specularTint;         // bias towards surface color
@property (nonatomic, readonly, retain) MDLMaterialProperty *roughness;            // diffuse and specular response
@property (nonatomic, readonly, retain) MDLMaterialProperty *anisotropic;          // shape of specular highlight
@property (nonatomic, readonly, retain) MDLMaterialProperty *anisotropicRotation;  // shape of specular highlight
@property (nonatomic, readonly, retain) MDLMaterialProperty *sheen;                // like velvet
@property (nonatomic, readonly, retain) MDLMaterialProperty *sheenTint;            // bias towards surface color
@property (nonatomic, readonly, retain) MDLMaterialProperty *clearcoat;            // like clear acrylic on a car
@property (nonatomic, readonly, retain) MDLMaterialProperty *clearcoatGloss;       // 0 = satin, 1 = glossy

@end

typedef NS_ENUM(NSUInteger, MDLMaterialFace) {
    MDLMaterialFaceFront = 0,
    MDLMaterialFaceBack,
    MDLMaterialFaceDoubleSided
};

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0))
MDL_EXPORT
@interface MDLMaterial : NSObject<MDLNamed, NSFastEnumeration>

- (instancetype)initWithName:(NSString*)name scatteringFunction:(MDLScatteringFunction*)scatteringFunction;

- (void)setProperty:(MDLMaterialProperty*)property;
- (void)removeProperty:(MDLMaterialProperty*)property;

- (nullable MDLMaterialProperty*)propertyNamed:(NSString*)name;

// Returns the first occurence of the property that matches the semantic.
// Not recommended to use when there are multiple properties with same semantic.
- (nullable MDLMaterialProperty*)propertyWithSemantic:(MDLMaterialSemantic)semantic;

// Returns the complete list of properties that match the semantic (e.g. Kd & Kd_map)
- (NSArray<MDLMaterialProperty *> *)propertiesWithSemantic:(MDLMaterialSemantic)semantic API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
- (void)removeAllProperties;

// Iterates all material properties. If they are string values, they are resolved into
// valid paths as NSURL values.
// @param resolver If non-nil, the resolver can be invoked to convert stringValues
//                 to NSURLs for loading.
- (void)resolveTexturesWithResolver:(id<MDLAssetResolver>)resolver API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

// Iterates all material properties. If they are string values or NSURL values, and
// can be resolved as textures, then the string and NSURL values will be replaced by
// MDLTextureSampler values. The transforms on the samplers will be identity, the
// wrap modes will be clamp, and the filter modes will be linear.
// @param resolver If non-nil, the resolver can be invoked to convert stringValues
//                 to NSURLs for loading.
- (void)loadTexturesUsingResolver:(id<MDLAssetResolver>)resolver API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));

@property (nonatomic, readonly, retain) MDLScatteringFunction *scatteringFunction;

/** @see MDLNamed */
@property (nonatomic, copy) NSString *name;

// If a property is not found by propertyForKey and baseMaterial is not nil,
// propertyForKey will invoke propertyForKey on baseMaterial.
// All other selectors disregard baseMaterial.
@property (nonatomic, retain, nullable) MDLMaterial *baseMaterial;

- (nullable MDLMaterialProperty *)objectAtIndexedSubscript:(NSUInteger)idx;
- (nullable MDLMaterialProperty *)objectForKeyedSubscript:(NSString*)name;
@property (nonatomic, readonly) NSUInteger count;

// Default is MDLMaterialFaceFront
@property (nonatomic) MDLMaterialFace materialFace;

@end

NS_ASSUME_NONNULL_END

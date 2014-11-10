//
//  GLKEffectPropertyLight.h
//  GLKEffects
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <GLKit/GLKEffectProperty.h>
#import <GLKit/GLKEffectPropertyTransform.h>

typedef NS_ENUM(GLint, GLKLightingType)
{
    GLKLightingTypePerVertex,
    GLKLightingTypePerPixel
} NS_ENUM_AVAILABLE(10_8, 5_0);

/*
 GLKEffectPropertyLight

 GLKEffectPropertyLight provides a single directional or spot light for an GLKEffect
 in accordance with the OpenGL ES 1.1 specification.

 Per the OpenGL ES 1.1 specification, light position and directions are transformed
 by the modelview matrix.  Accordingly, GLKEffectPropertyLight has a transform property.
 If light transformation is required the transform property must be explicitly set
 for light properties.

 In order for lighting calculations to function properly, clients of GLKEffectPropertyLight
 must enable the vertex attribute array GLKVertexAttribNormal to provide normals for
 lighting calculations. The normals are always normalized.

 The default values for GLKEffectPropertyLight properties are as follows:

    { 0, 0, 1, 0},  // position
    { 0, 0, 0, 1},  // ambient color
    { 1, 1, 1, 1},  // diffuse color
    { 1, 1, 1, 1},  // specular color
    { 0, 0, -1},    // spot direction
    0,              // spot exponent
    180,            // spot cutoff
    1,              // constant attenuation
    0,              // linear attenuation
    0,              // quadratic attenuation

 Note that, as with OpenGL ES 1.1 differentiation between a directional and spot light
 pivots on the value specified for _spotCutoff.  A _spotCutoff of 180.0, the default
 value, indicates a directional light while values less than 180.0 indicates a 
 spot light.
*/
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GLKEffectPropertyLight : GLKEffectProperty 
{
    @private
    
    // Light parameters
    GLboolean   _enabled;
    GLKVector4  _position;
    GLKVector4  _ambientColor, _diffuseColor, _specularColor;
    GLKVector3  _spotDirection;
    GLfloat     _spotExponent, _spotCutoff;
    GLfloat     _constantAttenuation, _linearAttenuation, _quadraticAttenuation;

    // Transform for independent transformation of light position and direction
    GLKEffectPropertyTransform *_transform;
}

// Properties                                                                                              // Default Value
@property (nonatomic, assign) GLboolean    enabled;                                                        // GL_TRUE
@property (nonatomic, assign) GLKVector4   position;                                                       // { 0.0, 0.0, 0.0, 1.0 }
@property (nonatomic, assign) GLKVector4   ambientColor;                                                   // { 0.0, 0.0, 0.0, 1.0 }
@property (nonatomic, assign) GLKVector4   diffuseColor;                                                   // { 1.0, 1.0, 1.0, 1.0 }
@property (nonatomic, assign) GLKVector4   specularColor;                                                  // { 1.0, 1.0, 1.0, 1.0 }
@property (nonatomic, assign) GLKVector3   spotDirection;                                                  // { 0.0, 0.0, -1.0 }
@property (nonatomic, assign) GLfloat      spotExponent;                                                   // 0.0
@property (nonatomic, assign) GLfloat      spotCutoff;                                                     // 180.0
@property (nonatomic, assign) GLfloat      constantAttenuation, linearAttenuation, quadraticAttenuation;   // 1.0, 0.0, 0.0

@property (nonatomic, retain) GLKEffectPropertyTransform *transform;                                       // All identity matrices

@end

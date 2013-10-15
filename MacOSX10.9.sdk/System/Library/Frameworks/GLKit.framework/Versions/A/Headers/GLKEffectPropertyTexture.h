//
//  GLKEffectPropertyTexture.h
//  GLKEffects
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <GLKit/GLKEffectProperty.h>

// Texture target
typedef NS_ENUM(GLenum, GLKTextureTarget)
{
    GLKTextureTarget2D = GL_TEXTURE_2D,
    GLKTextureTargetCubeMap = GL_TEXTURE_CUBE_MAP,
    GLKTextureTargetCt = 2
} NS_ENUM_AVAILABLE(10_8, 5_0);

// Texture env mode
typedef NS_ENUM(GLint, GLKTextureEnvMode)
{
    GLKTextureEnvModeReplace,
    GLKTextureEnvModeModulate,
    GLKTextureEnvModeDecal
} NS_ENUM_AVAILABLE(10_8, 5_0);


// GLKEffectPropertyTexture
//
// GLKEffectPropertyTexture simply contains properties to configure GL texture rendering.
//
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GLKEffectPropertyTexture : GLKEffectProperty
{
    // Texture Enabled
    GLboolean           _enabled;

    // Texture Name
    GLuint              _name;

    // Texture Target 2D or Cube Map
    GLKTextureTarget    _target;

    // Texture Env Mode Replace, Modulate or Decal
    GLKTextureEnvMode   _envMode;
}

// Properties                                                  // Default Value
@property (nonatomic, assign) GLboolean            enabled;    // Is this texture enabled
@property (nonatomic, assign) GLuint               name;       // Texture name from glGenTextures()
@property (nonatomic, assign) GLKTextureTarget     target;     // GLKTextureTarget2D
@property (nonatomic, assign) GLKTextureEnvMode    envMode;    // GLKTextureEnvModeModulate

@end

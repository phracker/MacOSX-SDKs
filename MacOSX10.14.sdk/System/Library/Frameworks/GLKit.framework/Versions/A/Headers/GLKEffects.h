//
//  GLKEffects.h
//  GLKEffects
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <GLKit/GLKNamedEffect.h>
#import <GLKit/GLKBaseEffect.h>
#import <GLKit/GLKReflectionMapEffect.h>
#import <GLKit/GLKSkyboxEffect.h>

// Named vertex attributes for mapping GLKEffects logic to client vertex attrib enables
typedef NS_ENUM(GLint, GLKVertexAttrib)
{
    GLKVertexAttribPosition,
    GLKVertexAttribNormal,
    GLKVertexAttribColor,
    GLKVertexAttribTexCoord0,
    GLKVertexAttribTexCoord1
} NS_ENUM_AVAILABLE(10_8, 5_0);

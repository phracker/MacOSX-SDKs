//
//  GLKBaseEffect.h
//  GLKit
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <GLKit/GLKitBase.h>

#if TARGET_OS_IPHONE
#import <OpenGLES/gltypes.h>
#else // !TARGET_OS_IPHONE
#import <OpenGL/gltypes.h>
#endif // !TARGET_OS_IPHONE

#import <GLKit/GLKNamedEffect.h>
#import <GLKit/GLKEffectPropertyTransform.h>
#import <GLKit/GLKEffectPropertyLight.h>
#import <GLKit/GLKEffectPropertyMaterial.h>
#import <GLKit/GLKEffectPropertyTexture.h>
#import <GLKit/GLKEffectPropertyFog.h>

/*
 GLKBaseEffect 

 GLKBaseEffect is designed to simplify visual effects common to many OpenGL applications today.  
 For iOS, GLKBaseEffect requires at least OpenGL ES 2.0 and for OS X, GLKBaseEffect requires
 at least an OpenGL Core Profile.  An appropriate context must be created and made current prior
 to instantiating and initializing GLKBaseEffect objects.

 GLKBaseEffect is designed to freely interoperate with custom OpenGL code.  It is also
 designed to minimally impact OpenGL state settings.  During initialization of a GLKBaseEffect
 object and its properties, OpenGL state settings are preserved.
 
 GLKBaseEffect is program based and, with the binding of its underlying GLSL program, it modifies 
 GL_CURRENT_PROGRAM state setting implicitly when -[GLKBaseEffect prepareToDraw] is called.  For 
 performance reasons GL_CURRENT_PROGRAM is not saved and restored by GLKBaseEffect so clients of 
 this class must set/save/restore the GL_CURRENT_PROGRAM before and/or after a call to 
 -[GLKBaseEffect prepareToDraw] as is applicable for their application.

 If texturing properties have been specified and are enabled, GLKBaseEffect will also modify
 the OpenGL state element GL_TEXTURE_BINDING_2D.  This state must also be handled in the manner
 described for GL_CURRENT_PROGRAM above.

 GLKBaseEffect uses named vertex attributes so client applications can refer to the following
 vertex attribute names when configuring/enabling/binding the vertex attribute data to be used with 
 GLKBaseEffect:

      GLKVertexAttribPosition      0
      GLKVertexAttribNormal        1
      GLKVertexAttribColor         2
      GLKVertexAttribTexCoord0     3
      GLKVertexAttribTexCoord1     4

      Note that normals for GLKVertexAttribNormal are always normalized.

 The (4) canonical steps to use GLKBaseEffect are:

      (1) Allocate and initialize an instance of GLKBaseEffect

      directionalLightEffect = [[GLKBaseEffect alloc] init];

      (2) Set the desired properties on the effect

      // Configure light0
      directionalLightEffect.light0.position = lightPosition;
      directionalLightEffect.light0.diffuseColor = diffuseColor;
      directionalLightEffect.light0.ambientColor = ambientColor;

      // Configure material
      directionalLightEffect.material.diffuseColor = materialDiffuseColor;
      directionalLightEffect.material.ambientColor = materialAmbientColor;
      directionalLightEffect.material.specularColor = materialSpecularColor;
      directionalLightEffect.material.shininess = 10.0;

      (3) Initialize vertex attribute / vertex array state preferrably with a vertex array object
          for the model or scene to be drawn.

      glGenVertexArraysOES(1, &vaoName);
      glBindVertexArrayOES(vaoName);

      // Create and initialize VBO for each vertex attribute
      // The example below shows an example of setup up the position vertex attribute.
      // Repeat the steps below for each additional desired attribute: normal, color, texCoord0, texCoord1.
      
      glGenBuffers(1, &positionVBO);
      glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
      glBufferData(GL_ARRAY_BUFFER, vboSize, dataBufPtr, GL_STATIC_DRAW);
      glVertexAttribPointer(GLKVertexAttribPosition, size, type, normalize, stride, NULL);
      glEnableVertexAttribArray(GLKVertexAttribPosition);

      ... repeat the steps above for other desired vertex attributes

      glBindVertexArrayOES(0);   // unbind the VAO we created above

      (4) For each frame drawn:  Update properties that change per frame.  Synchronize the changed effect state
          by calling -[GLKBaseEffect prepareToDraw].  Draw the model with the effect

      directionalLightEffect.transform.modelviewMatrix = modelviewMatrix;
      [directionalLightEffect prepareToDraw];
      glBindVertexArrayOES(vaoName);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, vertCt);
*/

@class GLKEffectPropertyTexture;

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GLKBaseEffect : NSObject <GLKNamedEffect>
{
    @protected
    
    // Switches to turn effect features on and off
    GLboolean                           _colorMaterialEnabled;
    GLboolean                           _fogEnabled;
    
    // Modelview, projection, texture and derived matrices for transformation
    GLKEffectPropertyTransform          *_transform;

    // Lights
    GLKLightingType                     _lightingType;
    GLKEffectPropertyLight              *_light0, *_light1, *_light2;

    // Material for lighting
    GLKEffectPropertyMaterial           *_material;

    // GL Texture Names
    GLKEffectPropertyTexture            *_texture2d0, *_texture2d1;

    // Texture ordering array
    NSArray                             *_textureOrder;
    
    // Constant color (fixed color value to supplant the use of the "color" named vertex attrib array)
    GLKVector4                          _constantColor;

    // Fog
    GLKEffectPropertyFog                *_fog;
    
    // Label for effect
    NSString                            *_label;
}

// Sync all effect changes for consistent state when drawing
- (void) prepareToDraw;


// Properties                                                                                         // Default Value

@property (nonatomic, assign)         GLboolean                          colorMaterialEnabled;        // GL_FALSE
@property (nonatomic, assign)         GLboolean                          lightModelTwoSided;          // GL_FALSE
@property (nonatomic, assign)         GLboolean                          useConstantColor;            // GL_TRUE

@property (nonatomic, readonly)       GLKEffectPropertyTransform         *transform;                  // Identity Matrices
@property (nonatomic, readonly)       GLKEffectPropertyLight             *light0, *light1, *light2;   // Disabled
@property (nonatomic, assign)         GLKLightingType                    lightingType;                // GLKLightingTypePerVertex
@property (nonatomic, assign)         GLKVector4                         lightModelAmbientColor;      // { 0.2, 0.2, 0.2, 1.0 }
@property (nonatomic, readonly)       GLKEffectPropertyMaterial          *material;                   // Default material state
@property (nonatomic, readonly)       GLKEffectPropertyTexture           *texture2d0, *texture2d1;    // Disabled
@property (nullable, nonatomic, copy) NSArray<GLKEffectPropertyTexture*> *textureOrder;               // texture2d0, texture2d1
@property (nonatomic, assign)         GLKVector4                         constantColor;               // { 1.0, 1.0, 1.0, 1.0 }
@property (nonatomic, readonly)       GLKEffectPropertyFog               *fog;                        // Disabled
@property (nullable, nonatomic, copy) NSString                           *label;                      // @"GLKBaseEffect"

@end
NS_ASSUME_NONNULL_END

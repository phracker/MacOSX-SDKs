//
//  GLKReflectionMapEffect.h
//  GLKit
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <GLKit/GLKBaseEffect.h>

/*
 GLKReflectionMapEffect

 GLKReflectionMapEffect is a subclass of GLKBaseEffect.  It is expected that GLKBaseEffect 
 functionality will be used in combination with GLKReflectionMapEffect.

 GLKReflectionMapEffect implements common reflection mapping functionality as is used by many of
 todays games and simulations.  A reflection or environment map can be thought of as a texture
 mapped polyhedral or spherical mesh that encloses a 3D model.  When the model is rendered
 surface normals from the model are used to calculate reflection vectors which intersect
 the environment map at some location.  The environment map texture color at this location
 is used to impart a modulated environment map color on the model giving the appearance that
 the shiny model is reflecting its surroundings to the viewer.

 The polyhedral shape used for GLKReflectionMapEffect is a cube.

 Because reflection mapping relies on surface normals to compute the intersection between
 reflected rays and the environment map the GLKVertexAttribNormal array must be enabled
 in order for GLKReflectionMapEffect to work properly. The normals are always normalized.

 GLKReflectionMapEffect requires at least an OpenGL ES 2.0 context on iOS and an OpenGL Core
 Profile context on OS X. This context must be initialized and made current prior to creating
 or initializing GLKReflectionMapEffect instances.  No OpenGL context state settings are
 modified when a GLKReflectionMapEffect instance is created or its properties set.  When
 -[GLKReflectionMapEffect prepareToDraw] is called it modifies the following state:

      GL_CURRENT_PROGRAM
      GL_TEXTURE_BINDING_CUBE_MAP

 For performance reasons GLKReflectionMapEffect does not restore any of these state settings.
 It is up to the client application to save/restore/set these state elements as they choose.

 A cube mapped texture name must be provided to GLKReflectionMapEffect to provide it texture
 data for the 6 faces of the environment map.

 GLKReflectionMapEffect reflection vectors are computed in eye space per section 2.11.4 of the
 OpenGL 2.1 desktop specification for the GL_REFLECTION_MAP texgen mode.  Typical reflection
 mapping uses an environment map with a fixed position (e.g. the sky in a real world rendering)
 and will accurately map the reflection map on the model regardless of the modelview transformation.
 To achieve this effect decompose the modelview matrix into its model and view components
 (i.e. the transforms on the object are the model and the transforms on the view are the camera).
 Then undo the viewing transform by inverting the viewing matrix - call this Vinv.  Now, starting
 with Vinv, treat it as the canonical normal matrix by applying an inverse transpose to it and
 choosing the upper 3x3 elements of the result.  inverseTranspose(Vinv) simplifies to Vtranspose.
 To apply this result to GLKReflectionMapEffect set its matrix property as follows:

      reflectionMapEffect.matrix = GLKMatrix4GetMatrix3(Vtranspose);

 to get correct, view-angle independent reflection mapping.


 The following (5) steps are required to use GLKReflectionMapEffect:

      (1) Allocate and initialize an instance of GLKReflectionMapEffect
      
      reflectionMapEffect = [[GLKReflectionMapEffect alloc] init];
   
      (2) Initialize vertex attribute / vertex array state preferrably with a vertex array object
          for the model or scene to be drawn.
   
      glGenVertexArraysOES(1, &vaoName);
      glBindVertexArrayOES(vaoName);

      // Create and initialize VBO for each vertex attribute
      // The example below shows an example of setup up the position and normal vertex attributes.
      // Specifying and binding a GLKVertexAttribNormal array attribute is required for GLKReflectionMapEffect
      // to work properly. The normals are always normalized.

      glGenBuffers(1, &positionVBO);
      glBindBuffer(positionVBO);
      glBufferData(GL_ARRAY_BUFFER, vboSize, dataBufPtr, GL_STATIC_DRAW);
      glVertexAttribPointer(GLKVertexAttribPosition, size, type, normalize, stride, NULL);

      glGenBuffers(1, &normalVBO);
      glBindBuffer(normalVBO);
      glBufferData(GL_ARRAY_BUFFER, vboSize, dataBufPtr, GL_STATIC_DRAW);
      glVertexAttribPointer(GLKVertexAttribNormal, size, type, normalize, stride, NULL);

      ... repeat the steps above for other desired vertex attributes

      glBindVertexArrayOES(0);   // unbind the VAO we created above

      (3) Create a cube map texture for the reflection map

      glGenTextures(1, &textureCubeMap);
      glBindTexture(GL_TEXTURE_CUBE_MAP, textureCubeMap);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      
      GLenum cubeMapBase = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
      
      for(face = 0; face < 6; face++)
          glTexImage2D(cubeMapBase + face, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, faceData[face]);

      (4) Set the textureCubeMap property to our new GL cube map and turn on reflection mapping

      reflectionMapEffect.enable = GL_TRUE;
      reflectionMapEffect.textureCubeMap = textureCubeMap;     // created in step (2) above

      (5) For each frame drawn:  Update properties that change per frame.  Synchronize the changed effect state
          by calling -[GLKReflectionMapEffect prepareToDraw].  Draw the model with the effect

      reflectionMapEffect.transform.modelviewMatrix = modelviewMatrix;
      [reflectionMapEffect prepareToDraw];
      glBindVertexArrayOES(vaoName);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, vertCt);
*/

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GLKReflectionMapEffect : GLKBaseEffect <GLKNamedEffect>
{
    @private

    // Cube map GL texture name
    GLKEffectPropertyTexture        *_textureCubeMap;
    
    // Reflection map matrix
    GLKMatrix3                      _matrix;
}


// Sync all effect changes for consistent state when drawing
- (void) prepareToDraw;

// Properties                                                                           // Default Value
@property (nonatomic, readonly) GLKEffectPropertyTexture           *textureCubeMap;     // GL Texture Name == 0
@property (nonatomic, assign)   GLKMatrix3                         matrix;              // Identity

@end
NS_ASSUME_NONNULL_END

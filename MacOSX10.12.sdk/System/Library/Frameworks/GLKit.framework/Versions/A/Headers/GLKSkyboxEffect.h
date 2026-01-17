//
//  GLKSkyboxEffect.h
//  GLKit
//
//  Copyright 2011-2012 Apple Inc. All rights reserved.
//

#import <GLKit/GLKBaseEffect.h>

/*
 GLKSkyboxEffect

 GLKSkyboxEffect implements common skybox functionality as is used by many of todays games
 and simulations.  A skybox is a textured cube that encloses the boundaries of the object
 space of a 3D graphics application or game.  It provides a visual horizon in all camera
 directions within 3D object space.

 GLKSkyboxEffect requires at least an OpenGL ES 2.0 context on iOS and an OpenGL Core
 Profile context on OS X. This context must be initialized and made current prior to creating
 or initializing GLKSkyboxEffect instances.  No OpenGL context state settings are
 modified when a GLKSkyboxEffect instance is created or its properties set.  When
 -[GLKSkyboxEffect prepareToDraw] is called it modifies the following state:

      GL_CURRENT_PROGRAM
      GL_TEXTURE_BINDING_CUBE_MAP
      GL_VERTEX_ARRAY_BINDING_OES
      GL_ARRAY_BUFFER_BINDING
      GL_VERTEX_ATTRIB_ARRAY_ENABLED (GLKVertexAttribPosition)

 For performance reasons GLKSkyboxEffect does not restore any of these state settings.
 It is up to the client application to save/restore/set these state elements as they choose.

 A cube mapped texture name must be provided to GLKSkyboxEffect to provide it texture
 data for the 6 faces of the skybox cube.  Care must be taken when preparing the 
 cubemap texture to prevent seams from appearing at the interfaces between adjacent
 faces.

 Unlike other named effects, GLKSkyboxEffect provides a -draw method and requires no ancillary
 vertex attribute setup because the class maintains the simple, unambiguous geometry data
 required to draw the skybox internally.


 The following (4) steps are required to use GLKSkyboxEffect:

      (1) Allocate and initialize an instance of GLKSkyboxEffect
      
      skybox = [[GLKSkyboxEffect alloc] init];

      (2) Create a cube map texture for the skybox

      glGenTextures(1, &cubeMapName);
      glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapName);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      
      GLenum cubeMapBase = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
      
      for(face = 0; face < 6; face++)
          glTexImage2D(cubeMapBase + face, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, faceData[face]);

      (3) Configure the skybox effect transform, location, size, and texture properties

      skybox.center = center;
      skybox.xSize = xSize;
      skybox.ySize = ySize;
      skybox.zSize = zSize;
      skybox.textureCubeMap = cubeMapName;     // created in step (2) above

      (4) For each frame drawn:  Update properties that change per frame.  Synchronize the changed effect state
          by calling -[GLKSkyboxEffect prepareToDraw].  Draw the the skybox.

      skybox.transform.modelviewMatrix = modelviewMatrix;
      [skybox prepareToDraw];
      [skybox draw];
*/

NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GLKSkyboxEffect : NSObject <GLKNamedEffect>
{
    @private
    
    // Center of the skybox in object/world coordinates
    GLKVector3                      _center;                       // 3 element vector of GLfloats
    
    // Dimensions of our skybox.  X extents, for example, are (center[0] - xSize / 2.0) & (center[0] + xSize / 2.0)
    GLfloat                         _xSize, _ySize, _zSize;
    
    // Cube map GL texture name
    GLKEffectPropertyTexture        *_textureCubeMap;
    
    // Skybox Transform
    GLKEffectPropertyTransform      *_transform;
    
    // Label for effect
    NSString                        *_label;
}


// Sync all effect changes for consistent state when drawing
- (void) prepareToDraw;

// Draw skybox
- (void) draw;

// Properties                                                                           // Default Value
@property (nonatomic, assign)         GLKVector3                 center;                // { 0.0, 0.0, 0.0 }
@property (nonatomic, assign)         GLfloat                    xSize, ySize, zSize;   // 1.0, 1.0, 1.0
@property (nonatomic, readonly)       GLKEffectPropertyTexture   *textureCubeMap;       // name == 0, target == GL_TEXTURE_CUBE_MAP
@property (nonatomic, readonly)       GLKEffectPropertyTransform *transform;            // Identity for all matrices
@property (nullable, nonatomic, copy) NSString                   *label;                // nil
@end
NS_ASSUME_NONNULL_END

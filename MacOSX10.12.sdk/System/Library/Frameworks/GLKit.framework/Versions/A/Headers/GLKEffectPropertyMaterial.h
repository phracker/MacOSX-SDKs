//
//  GLKEffectPropertyMaterial.h
//  GLKEffects
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <GLKit/GLKEffectProperty.h>

/*
 GLKEffectPropertyMaterial

 GLKEffectPropertyMaterial encapsulates material properties for an GLKEffect in
 accordance with the specification and lighting behavior of OpenGL ES 1.1.
*/
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GLKEffectPropertyMaterial : GLKEffectProperty
{    
    @private
    
    // Material parameters
    GLKVector4      _ambientColor, _diffuseColor, _specularColor, _emissiveColor;
    GLfloat         _shininess;
}

// Properties                                                          // Default Values
@property (nonatomic, assign) GLKVector4       ambientColor;           // { 0.2, 0.2, 0.2, 1.0}
@property (nonatomic, assign) GLKVector4       diffuseColor;           // { 0.8, 0.8, 0.8, 1.0}
@property (nonatomic, assign) GLKVector4       specularColor;          // { 0.0, 0.0, 0.0, 1.0}
@property (nonatomic, assign) GLKVector4       emissiveColor;          // { 0.0, 0.0, 0.0, 1.0}
@property (nonatomic, assign) GLfloat          shininess;              // 0.0

@end
NS_ASSUME_NONNULL_END
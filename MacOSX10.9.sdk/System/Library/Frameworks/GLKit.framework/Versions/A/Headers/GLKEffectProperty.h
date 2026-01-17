//
//  GLKEffectProperty.h
//  GLKEffects
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <OpenGLES/ES2/gl.h>
#else // !TARGET_OS_IPHONE
#import <OpenGL/gl3.h>
#endif // !TARGET_OS_IPHONE

#import <GLKit/GLKMath.h>


/*
 GLKEffectProperty

 GLKEffectProperties are objects that allow piecewise characterization of NamedEffects.
 Examples of GLKEffectProperty classes are GLKEffectPropertyTransform and GLKEffectPropertyTexture.
 GLKBaseEffect, for instance, has obj-c properties "transform" and "texture2d0" of the aforementioned
 types respectively.  By specifying proper parameters on these two properties along with the
 proper OpenGL vertex array object configuration, a, for instance, textured, rotated quad can
 be drawn.

 GLKEffectProperty is an abstract class.  Instantiation of this class via its -init method will
 result in an error.  GLKEffectProperty maintains a few instance variables that are shared by
 its descendants.

 All descendants of GLKEffectProperty are concrete, mutable classes.
 */

typedef struct GLKEffectPropertyPrv *GLKEffectPropertyPrvPtr;

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface GLKEffectProperty : NSObject 
{
    @protected
    
    GLint                   _location;         // Shader location
    GLchar                  *_nameString;      // Shader location name
    
    GLKEffectPropertyPrvPtr _prv;
}

@end

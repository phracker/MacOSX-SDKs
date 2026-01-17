/**
 @header
 
 SKShader defines the custom fragment shader which can be set on a supported Sprite Kit node.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKUniform.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, 8_0)
SK_EXPORT @interface SKShader : NSObject <NSCopying, NSCoding>

/**
 Create a custom shader with source code.
 
 @param source the source code for the custom fragment shader.
 */
- (instancetype)initWithSource:(NSString *)source;

/**
 Create a custom shader with source code and uniforms.
 
 @param source the source code for the custom fragment shader.
 @param uniforms the array of uniforms supplied to this shader
 */
- (instancetype)initWithSource:(NSString *)source uniforms:(NSArray<SKUniform*> *)uniforms;

+ (instancetype)shader;
+ (instancetype)shaderWithSource:(NSString *)source;
+ (instancetype)shaderWithSource:(NSString *)source uniforms:(NSArray<SKUniform*> *)uniforms;

/**
 Loads a shader source file named 'name' from the main bundle. This is simpler yet functionally equivalent to the following code
 
 [SKShader shaderWithSource:[NSString stringWithContentsOfFile:[[NSBundle mainBundle] pathForResource:name ofType:@"fsh"]
                   encoding:NSUTF8StringEncoding
                      error:NULL]];
 
 Though error handling is encapsulated and the encoding flexible.
 */
+ (instancetype)shaderWithFileNamed:(NSString *)name;

/**
 Shader source must define the 'main' method of the fragment shader
 
 Your shader must assign a premultipled fragment value to 'gl_FragColor'
 
 The following implicit uniforms are available:
 
    1. sampler2D u_texture  (the primary texuture attached the the sprite)
 
 The following varyings are available:
 
    1. vec2 v_tex_coord  (normalized texture coordiantes for the primary texture)
    2. vec4 v_color_mix  (premultiplied color value based on color & alpha)
 
 
 The following functions are available:
 
    1. vec4 SKDefaultShading()  (returns the fragment value that would have been output if no shader was used)
 
 
 
 Sample shader source that produces the same result are SpriteKit's normal rendering:
 
 "void main() { gl_FragColor = SKDefaultShading(); }"
 
 */

@property (copy, nullable) NSString *source;


/**
 You may define additional uniforms to be used in your shader here.
 There is no need to declare them in you source, just use them by name.
 
 All uniforms declared must be used within the source.
 */
@property (copy) NSArray<SKUniform*> *uniforms;

- (void)addUniform:(SKUniform *)uniform;
- (nullable SKUniform *)uniformNamed:(NSString *)name;
- (void)removeUniformNamed:(NSString *)name;

@end

NS_ASSUME_NONNULL_END
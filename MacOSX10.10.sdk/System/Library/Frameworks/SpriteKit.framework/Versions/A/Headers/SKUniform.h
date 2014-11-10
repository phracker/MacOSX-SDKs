/**
 @header
 
 Uniform defines the type and data associated with a custom fragment shader, SKShader.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKTexture.h>
#import <GLKit/GLKMath.h>

typedef NS_ENUM(NSInteger, SKUniformType) {
    SKUniformTypeNone               =    0,
    SKUniformTypeFloat              =    1,
    SKUniformTypeFloatVector2       =    2,
    SKUniformTypeFloatVector3       =    3,
    SKUniformTypeFloatVector4       =    4,
    SKUniformTypeFloatMatrix2       =    5,
    SKUniformTypeFloatMatrix3       =    6,
    SKUniformTypeFloatMatrix4       =    7,
    SKUniformTypeTexture            =    8,
} NS_ENUM_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
SK_EXPORT @interface SKUniform : NSObject <NSCopying, NSCoding>

/**
 Create a shader uniform with a given name.
 
 @param name the name of the shader uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name;

/**
 Create a shader uniform with a given name, and texture data
 
 @param name the name of the shader uniform.
 @param texture the texture data associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name texture:(SKTexture*)texture;

/**
 Create a shader uniform with a given name, and a float value
 
 @param name the name of the shader uniform.
 @param value the floating point value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name float:(float)value;

/**
 Create a shader uniform with a given name, and a float vector2 value
 
 @param name the name of the shader uniform.
 @param value the float vector2 value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name floatVector2:(GLKVector2)value;

/**
 Create a shader uniform with a given name, and a float vector3 value
 
 @param name the name of the shader uniform.
 @param value the float vector3 value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name floatVector3:(GLKVector3)value;

/**
 Create a shader uniform with a given name, and a float vector4 value
 
 @param name the name of the shader uniform.
 @param value the float vector4 value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name floatVector4:(GLKVector4)value;

/**
 Create a shader uniform with a given name, and a 2x2 matrix value
 
 @param name the name of the shader uniform.
 @param value the 2x2 matrix value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name floatMatrix2:(GLKMatrix2)value;

/**
 Create a shader uniform with a given name, and a 3x3 matrix value
 
 @param name the name of the shader uniform.
 @param value the 3x3 matrix value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name floatMatrix3:(GLKMatrix3)value;

/**
 Create a shader uniform with a given name, and a 4x4 matrix value
 
 @param name the name of the shader uniform.
 @param value the 4x4 matrix value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name floatMatrix4:(GLKMatrix4)value;

/* The name by which this uniform will be refernced in a shader */
@property (readonly) NSString *name;

/* Once created, a uniform is locked to a specific type, you may only access the property of this type */
@property (readonly) SKUniformType uniformType;

/* Access to the texture data associated with the current uniform */
@property SKTexture *textureValue;

/* Access to the float value associated with the current uniform */
@property float floatValue;
/* Access to the float vector 2 value associated with the current uniform */
@property GLKVector2 floatVector2Value;
/* Access to the float vector 3 value associated with the current uniform */
@property GLKVector3 floatVector3Value;
/* Access to the float vector 4 value associated with the current uniform */
@property GLKVector4 floatVector4Value;

/* Access to the 2x2 matrix value associated with the current uniform */
@property GLKMatrix2 floatMatrix2Value;
/* Access to the 3x3 matrix value associated with the current uniform */
@property GLKMatrix3 floatMatrix3Value;
/* Access to the 4x4 matrix value associated with the current uniform */
@property GLKMatrix4 floatMatrix4Value;


- (instancetype)initWithName:(NSString *)name;

- (instancetype)initWithName:(NSString *)name texture:(SKTexture*)texture;

- (instancetype)initWithName:(NSString *)name float:(float)value;
- (instancetype)initWithName:(NSString *)name floatVector2:(GLKVector2)value;
- (instancetype)initWithName:(NSString *)name floatVector3:(GLKVector3)value;
- (instancetype)initWithName:(NSString *)name floatVector4:(GLKVector4)value;

- (instancetype)initWithName:(NSString *)name floatMatrix2:(GLKMatrix2)value;
- (instancetype)initWithName:(NSString *)name floatMatrix3:(GLKMatrix3)value;
- (instancetype)initWithName:(NSString *)name floatMatrix4:(GLKMatrix4)value;

@end

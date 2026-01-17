/**
 @header
 
 Uniform defines the type and data associated with a custom fragment shader, SKShader.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKTexture.h>
#import <simd/simd.h>

#if !TARGET_OS_MACCATALYST && __has_include(<GLKit/GLKMath.h>)
#import <GLKit/GLKMath.h>
#endif

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


NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_10, 8_0)
SK_EXPORT @interface SKUniform : NSObject <NSCopying, NSSecureCoding>

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
+ (instancetype)uniformWithName:(NSString *)name texture:(nullable SKTexture*)texture;

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
+ (instancetype)uniformWithName:(NSString *)name vectorFloat2:(vector_float2)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/**
 Create a shader uniform with a given name, and a float vector3 value
 
 @param name the name of the shader uniform.
 @param value the float vector3 value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name vectorFloat3:(vector_float3)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/**
 Create a shader uniform with a given name, and a float vector4 value
 
 @param name the name of the shader uniform.
 @param value the float vector4 value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name vectorFloat4:(vector_float4)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/**
 Create a shader uniform with a given name, and a 2x2 matrix value
 
 @param name the name of the shader uniform.
 @param value the 2x2 matrix value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name matrixFloat2x2:(matrix_float2x2)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/**
 Create a shader uniform with a given name, and a 3x3 matrix value
 
 @param name the name of the shader uniform.
 @param value the 3x3 matrix value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name matrixFloat3x3:(matrix_float3x3)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/**
 Create a shader uniform with a given name, and a 4x4 matrix value
 
 @param name the name of the shader uniform.
 @param value the 4x4 matrix value associated with this uniform.
 */
+ (instancetype)uniformWithName:(NSString *)name matrixFloat4x4:(matrix_float4x4)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

/* The name by which this uniform will be referenced in a shader */
@property (nonatomic, readonly) NSString *name;

/* Once created, a uniform is locked to a specific type, you may only access the property of this type */
@property (nonatomic, readonly) SKUniformType uniformType;

/* Access to the texture data associated with the current uniform */
@property (nonatomic, retain, nullable) SKTexture *textureValue;

/* Access to the value associated with the uniform */
@property (nonatomic) float floatValue;
@property (nonatomic) vector_float2 vectorFloat2Value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
@property (nonatomic) vector_float3 vectorFloat3Value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
@property (nonatomic) vector_float4 vectorFloat4Value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
@property (nonatomic) matrix_float2x2 matrixFloat2x2Value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
@property (nonatomic) matrix_float3x3 matrixFloat3x3Value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
@property (nonatomic) matrix_float4x4 matrixFloat4x4Value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

- (instancetype)initWithName:(NSString *)name;
- (instancetype)initWithName:(NSString *)name texture:(nullable SKTexture*)texture;
- (instancetype)initWithName:(NSString *)name float:(float)value;
- (instancetype)initWithName:(NSString *)name vectorFloat2:(vector_float2)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (instancetype)initWithName:(NSString *)name vectorFloat3:(vector_float3)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (instancetype)initWithName:(NSString *)name vectorFloat4:(vector_float4)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (instancetype)initWithName:(NSString *)name matrixFloat2x2:(matrix_float2x2)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (instancetype)initWithName:(NSString *)name matrixFloat3x3:(matrix_float3x3)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));
- (instancetype)initWithName:(NSString *)name matrixFloat4x4:(matrix_float4x4)value API_AVAILABLE(ios(10.0), tvos(10.0), watchos(3.0), macos(10.12));

#if !TARGET_OS_MACCATALYST && __has_include(<GLKit/GLKMath.h>)
@property GLKVector2 floatVector2Value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
@property GLKVector3 floatVector3Value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
@property GLKVector4 floatVector4Value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
@property GLKMatrix2 floatMatrix2Value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
@property GLKMatrix3 floatMatrix3Value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
@property GLKMatrix4 floatMatrix4Value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);

+ (instancetype)uniformWithName:(NSString *)name floatVector2:(GLKVector2)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
+ (instancetype)uniformWithName:(NSString *)name floatVector3:(GLKVector3)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
+ (instancetype)uniformWithName:(NSString *)name floatVector4:(GLKVector4)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
+ (instancetype)uniformWithName:(NSString *)name floatMatrix2:(GLKMatrix2)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
+ (instancetype)uniformWithName:(NSString *)name floatMatrix3:(GLKMatrix3)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
+ (instancetype)uniformWithName:(NSString *)name floatMatrix4:(GLKMatrix4)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);

- (instancetype)initWithName:(NSString *)name floatVector2:(GLKVector2)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
- (instancetype)initWithName:(NSString *)name floatVector3:(GLKVector3)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
- (instancetype)initWithName:(NSString *)name floatVector4:(GLKVector4)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
- (instancetype)initWithName:(NSString *)name floatMatrix2:(GLKMatrix2)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
- (instancetype)initWithName:(NSString *)name floatMatrix3:(GLKMatrix3)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
- (instancetype)initWithName:(NSString *)name floatMatrix4:(GLKMatrix4)value NS_DEPRECATED(10_8, 10_12, 7_0, 10_0);
#endif

@end

NS_ASSUME_NONNULL_END

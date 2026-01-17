/**
 @header
 
 SKAttributes can be used to provide a per-node value to be
 used with SKShaders.
 
 @copyright 2015 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, SKAttributeType) {
    SKAttributeTypeNone                 =    0,
    
    SKAttributeTypeFloat                =    1,
    SKAttributeTypeVectorFloat2         =    2,
    SKAttributeTypeVectorFloat3         =    3,
    SKAttributeTypeVectorFloat4         =    4,
    
    SKAttributeTypeHalfFloat            =    5,
    SKAttributeTypeVectorHalfFloat2     =    6,
    SKAttributeTypeVectorHalfFloat3     =    7,
    SKAttributeTypeVectorHalfFloat4     =    8,
    
} NS_ENUM_AVAILABLE(10_11, 9_0);

NS_CLASS_AVAILABLE(10_11, 9_0)
SK_EXPORT @interface SKAttribute : NSObject <NSCoding>

+ (instancetype)attributeWithName:(NSString*)name type:(SKAttributeType)type;
- (instancetype)initWithName:(NSString*)name type:(SKAttributeType)type NS_DESIGNATED_INITIALIZER;

@property (readonly, nonatomic) NSString *name;
@property (readonly, nonatomic) SKAttributeType type;

@end



NS_CLASS_AVAILABLE(10_11, 9_0)
SK_EXPORT @interface SKAttributeValue : NSObject <NSCoding>

+ (instancetype)valueWithFloat:(float)value;
+ (instancetype)valueWithVectorFloat2:(vector_float2)value;
+ (instancetype)valueWithVectorFloat3:(vector_float3)value;
+ (instancetype)valueWithVectorFloat4:(vector_float4)value;

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@property (nonatomic) float floatValue;
@property (nonatomic) vector_float2 vectorFloat2Value;
@property (nonatomic) vector_float3 vectorFloat3Value;
@property (nonatomic) vector_float4 vectorFloat4Value;

@end

NS_ASSUME_NONNULL_END

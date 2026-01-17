//
//  SKTileDefinition.h
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SpriteKitBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Adjust the rotation of the tile definition image, in 90 degree increments.
 */
typedef NS_ENUM(NSUInteger, SKTileDefinitionRotation) {
    SKTileDefinitionRotation0 = 0,
    SKTileDefinitionRotation90,
    SKTileDefinitionRotation180,
    SKTileDefinitionRotation270
} NS_ENUM_AVAILABLE(10_12, 10_0);

/**
 A tile definition contains the information needed to represent a single type of tile within a tile map.
 */
SK_EXPORT NS_AVAILABLE(10_12, 10_0) @interface SKTileDefinition : NSObject <NSCopying, NSSecureCoding>

/**
 Create a tile definition with an SKTexture, and set its size to the SKTexture's width/height.
 @param texture the texture to reference for size and content
 */
+ (instancetype)tileDefinitionWithTexture:(SKTexture *)texture;

/**
 Create a tile definition with an SKTexture and the specified size.
 @param texture the texture to reference for content
 @param size the size of the tile in points
 */
+ (instancetype)tileDefinitionWithTexture:(SKTexture *)texture size:(CGSize)size;

/**
 Create a tile definition with an SKTexture and the specified size.
 @param texture the texture to reference for content
 @param normalTexture the normal texture to use for generating normals for lighting
 @param size the size of the tile in points
 */
+ (instancetype)tileDefinitionWithTexture:(SKTexture *)texture normalTexture:(SKTexture *)normalTexture size:(CGSize)size;

/**
 Create an animated tile definition with an array of SKTextures, the specified size, and the length of time each texture should be displayed for in the animation.
 @param textures the textures to reference for animated content
 @param size the size of the tile in points
 @param timePerFrame the duration, in seconds, that each texture in the textures array is displayed before switching to the next texture in the sequence
 */
+ (instancetype)tileDefinitionWithTextures:(NSArray<SKTexture *> *)textures size:(CGSize)size timePerFrame:(CGFloat)timePerFrame;

/**
 Create an animated tile definition with an array of SKTextures, the specified size, and the length of time each texture should be displayed for in the animation.
 @param textures the textures to reference for animated content
 @param normalTextures the normal textures to use for generating normals for lighting
 @param size the size of the tile in points
 @param timePerFrame the duration, in seconds, that each texture in the textures array is displayed before switching to the next texture in the sequence
 */
+ (instancetype)tileDefinitionWithTextures:(NSArray<SKTexture *> *)textures normalTextures:(NSArray<SKTexture *> *)normalTextures size:(CGSize)size timePerFrame:(CGFloat)timePerFrame;

/**
 Initilize a tile definition with an SKTexture, and set its size to the SKTexture's width/height.
 @param texture the texture to reference for size and content
 */
- (instancetype)initWithTexture:(SKTexture *)texture;

/**
 Initilize a tile definition with an SKTexture and the specified size.
 @param texture the texture to reference for content
 @param size the size of the tile in points
 */
- (instancetype)initWithTexture:(SKTexture *)texture size:(CGSize)size;

/**
 Initilize a tile definition with an SKTexture and the specified size.
 @param texture the texture to reference for content
 @param normalTexture the normal texture to use for generating normals for lighting
 @param size the size of the tile in points
 */
- (instancetype)initWithTexture:(SKTexture *)texture normalTexture:(SKTexture *)normalTexture size:(CGSize)size;

/**
 Initilize an animated tile definition with an array of SKTextures, the specified size, and the length of time each texture should be displayed for in the animation.
 @param textures the textures to reference for animated content
 @param size the size of the tile in points
 @param timePerFrame the duration, in seconds, that each texture in the textures array is displayed before switching to the next texture in the sequence
 */
- (instancetype)initWithTextures:(NSArray<SKTexture *>*)textures size:(CGSize)size timePerFrame:(CGFloat)timePerFrame;

/**
 Initilize an animated tile definition with an array of SKTextures, the specified size, and the length of time each texture should be displayed for in the animation.
 @param textures the textures to reference for animated content
 @param normalTextures the normal textures to use for generating normals for lighting
 @param size the size of the tile in points
 @param timePerFrame the duration, in seconds, that each texture in the textures array is displayed before switching to the next texture in the sequence
 */
- (instancetype)initWithTextures:(NSArray<SKTexture *>*)textures normalTextures:(NSArray<SKTexture *> *)normalTextures size:(CGSize)size timePerFrame:(CGFloat)timePerFrame;

/**
 The textures used to draw the tile. Non-animated tiles use only one texture. When more than one texture is present, the tile will swap through them in sequence, showing each for the duration specified in the timePerFrame property. After displaying the last texture in the array, the sequence is repeated from the first texture.
 */
@property (nonatomic, copy) NSArray<SKTexture *> *textures;

/**
 The textures to use for generating normals that lights use to light this tile. These will only be used if the tile is lit by at least one light. Each normal texture corresponds to a texture in the textures property.
 */
@property (nonatomic, copy) NSArray<SKTexture *> *normalTextures;

/**
 An optional dictionary that can be used to store your own data for each tile definition. Defaults to nil.
 */
@property (nonatomic, retain, nullable) NSMutableDictionary *userData;

/**
 Client-assignable name for the tile definition. Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The size of the tile in points.
 */
@property (nonatomic) CGSize size;

/**
 The duration, in seconds, that each texture in the textures array is displayed before switching to the next texture in the sequence. Only used when there is more than one texture available.
 */
@property (nonatomic) CGFloat timePerFrame;

/**
 This value is used to determine how likely this tile definition is to be chosen for placement when a SKTileGroupRule has mulitple tile definitions assigned to it. A higher value relative to the other definitions assigned to the rule make it more likely for this definition to be selected; lower values make it less likely. Defaults to 1. When set to 0, the definition will never be chosen as long as there is at least one other definition with a placementWeight above 0.
 */
@property (nonatomic) NSUInteger placementWeight;

/**
 The rotation of the tile definition's images can be set in 90 degree increments. Defaults to SKTileDefinitionRotation0.
 */
@property (nonatomic) SKTileDefinitionRotation rotation;

/**
 When set to YES, the tile definition's images will be flipped vertically (i.e., the top of the image becomes the bottom). Defaults to NO.
 */
@property (nonatomic) BOOL flipVertically;

/**
 When set to YES, the tile definition's images will be flipped horizontally (i.e., the left of the image becomes the right). Defaults to NO.
 */
@property (nonatomic) BOOL flipHorizontally;

@end

NS_ASSUME_NONNULL_END



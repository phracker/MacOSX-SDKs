//
//  SKTileMapNode.h
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <SpriteKit/SKNode.h>
#import <SpriteKit/SKShader.h>
#import <SpriteKit/SpriteKitBase.h>

#import <SpriteKit/SKTileSet.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A SpriteKit node used to render a 2D array of textured sprites. Uses SKTileSet to determine what textures it can use to render. Separate tile map nodes can be layered on top of one another to achieve various effects, such as parallax scrolling.
 */
SK_EXPORT NS_AVAILABLE(10_12, 10_0) @interface SKTileMapNode : SKNode <NSCopying, NSCoding>

/**
 Create a tile map node with the specified tile set and dimensions. The tiles of the map will be empty, equivalent to the nil tile definition/group.
 @param tileSet the tile set that is used to render the tiles
 @param columns the number of columns in the map that can hold tiles
 @param rows the number of rows in the map that can hold tiles
 @param tileSize the size of each tile in points
 */
+ (instancetype)tileMapNodeWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize;

/**
 Create a tile map node with the specified tile set and dimensions, and fill it with the specified tile group.
 @param tileSet the tile set that is used to render the tiles
 @param columns the number of columns in the map that can hold tiles
 @param rows the number of rows in the map that can hold tiles
 @param tileSize the size of each tile in points
 @param tileGroup the tile group we wish to fill the tile map with
 */
+ (instancetype)tileMapNodeWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize fillWithTileGroup:(SKTileGroup *)tileGroup;

/**
 Create a tile map node with the specified tile set and dimensions, and fill it with a specific layout of tile groups that belong to the provided tile set. The tileGroupLayout array should match the dimensions of the tile map (i.e., the number of elements should be equal to columns * rows). Index 0 of the array maps to column 0, row 0 of the tile map. Index 1 is column 1, row 0, and so on, wrapping around to the next row once the index passes the number of columns in the tile map. If the array has fewer elements than the number of tiles in the map, the remaining tiles are initialized with the nil tile group. If the array has more elements than the number of tiles in the map, the extra tile groups are ignored.
 @param tileSet the tile set that is used to render the tiles
 @param columns the number of columns in the map that can hold tiles
 @param rows the number of rows in the map that can hold tiles
 @param tileSize the size of each tile in points
 @param tileGroupLayout an array of tile groups that we want to use to fill the tile map
 */
+ (instancetype)tileMapNodeWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize tileGroupLayout:(NSArray<SKTileGroup *> *)tileGroupLayout;

/**
 Initialize a tile map node with the specified tile set and dimensions. The tiles of the map will be empty, equivalent to the nil tile definition/group.
 @param tileSet the tile set that is used to render the tiles
 @param columns the number of columns in the map that can hold tiles
 @param rows the number of rows in the map that can hold tiles
 @param tileSize the size of each tile in points
 */
- (instancetype)initWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize;

/**
 Initialize a tile map node with the specified tile set and dimensions, and fill it with the specified tile group.
 @param tileSet the tile set that is used to render the tiles
 @param columns the number of columns in the map that can hold tiles
 @param rows the number of rows in the map that can hold tiles
 @param tileSize the size of each tile in points
 @param tileGroup the tile group we wish to fill the tile map with
 */
- (instancetype)initWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize fillWithTileGroup:(SKTileGroup *)tileGroup;

/**
 Initialize a tile map node with the specified tile set and dimensions, and fill it with a specific layout of tile groups that belong to the provided tile set. The tileGroupLayout array should match the dimensions of the tile map (i.e., the number of elements should be equal to columns * rows). Index 0 of the array maps to column 0, row 0 of the tile map. Index 1 is column 1, row 0, and so on, wrapping around to the next row once the index passes the number of columns in the tile map. If the array has fewer elements than the number of tiles in the map, the remaining tiles are initialized with the nil tile group. If the array has more elements than the number of tiles in the map, the extra tile groups are ignored.
 @param tileSet the tile set that is used to render the tiles
 @param columns the number of columns in the map that can hold tiles
 @param rows the number of rows in the map that can hold tiles
 @param tileSize the size of each tile in points
 @param tileGroupLayout an array of tile groups that we want to use to fill the tile map
 */
- (instancetype)initWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize tileGroupLayout:(NSArray<SKTileGroup *> *)tileGroupLayout;

/**
 The number of columns in the tile map.
 */
@property (nonatomic) NSUInteger numberOfColumns;

/**
 The number of rows in the tile map.
 */
@property (nonatomic) NSUInteger numberOfRows;

/**
 The size of each tile in the map.
 */
@property (nonatomic) CGSize tileSize;

/**
 The size of the tile map. This is dependent on the tileSize, the number of columns and rows in the map, and the tile set type.
 */
@property (nonatomic, readonly) CGSize mapSize;

/**
 The tile set being used by this tile map.
 */
@property (nonatomic) SKTileSet *tileSet;

/**
 Controls the blending between the texture and the tile map color. The valid interval of values is from 0.0 up to and including 1.0. A value above or below that interval is clamped to the minimum (0.0) if below or the maximum (1.0) if above.
 */
@property (nonatomic) CGFloat colorBlendFactor;

/**
 Base color for the tile map (If no texture is present, the color still is drawn).
 */
@property (nonatomic, retain) SKColor *color;

/**
 Sets the blend mode to use when composing the tile map with the final framebuffer.
 @see SKNode.SKBlendMode
 */
@property (nonatomic) SKBlendMode blendMode;

/**
 Used to choose the location in the tile map that maps to its 'position' in the parent's coordinate space. The valid interval for each input is from 0.0 up to and including 1.0.
 */
@property (nonatomic) CGPoint anchorPoint;

/**
 A property that determines whether the tile map is rendered using a custom shader.
 */
@property (nonatomic, retain, nullable) SKShader *shader;

/**
 Optional dictionary of SKAttributeValues
 Attributes can be used with custom SKShaders.
 */
@property (nonatomic, nonnull, copy) NSDictionary<NSString *, SKAttributeValue *> *attributeValues;

- (nullable SKAttributeValue*)valueForAttributeNamed:(nonnull NSString *)key;
- (void)setValue:(SKAttributeValue*)value forAttributeNamed:(nonnull NSString *)key NS_SWIFT_NAME(setValue(_:forAttribute:));

/**
 Bitmask to indicate being lit by a set of lights using overlapping lighting categories.

 A light whose category is set to a value that masks to non-zero using this mask will
 apply light to this sprite.

 When used together with a normal texture, complex lighting effects can be used.
 */
@property (nonatomic) uint32_t lightingBitMask;

@property (nonatomic) BOOL enableAutomapping;

/**
 Fill the entire tile map with the provided tile group.
 @param tileGroup the tile group that will be used to fill the map
 */
- (void)fillWithTileGroup:(nullable SKTileGroup *)tileGroup;

/**
 Look up the tile definition at the specified tile index.
 @param column the column index of the tile
 @param row the row index of the tile
 */
- (nullable SKTileDefinition *)tileDefinitionAtColumn:(NSUInteger)column row:(NSUInteger)row;

/**
 Look up the tile group at the specified tile index.
 @param column the column index of the tile
 @param row the row index of the tile
 */
- (nullable SKTileGroup *)tileGroupAtColumn:(NSUInteger)column row:(NSUInteger)row;

/**
 Set the tile group at the specified tile index. When automapping is enabled, the appropriate tile definitions will automatically be selected and placed, possibly modifying neighboring tiles. When automapping is disabled, it will simply place the default center tile definition for the group, and will not modify any of the neihboring tiles.
 @param tileGroup the tile group we want to place in the map
 @param column the column index of the tile
 @param row the row index of the tile
 */
- (void)setTileGroup:(nullable SKTileGroup *)tileGroup forColumn:(NSUInteger)column row:(NSUInteger)row;

/**
 Set the tile group and tile defintion at the specified tile index. When automapping is enabled, it will attempt to resolve the surrounding tiles to allow the specified tile definition to be placed. When automapping is disabled, it will simply place the tile definition and not modify any of the neighboring tiles.
 @param tileGroup the tile group we want to place in the map
 @param tileDefinition the tile definition we want to place in the map
 @param column the column index of the tile
 @param row the row index of the tile
 */
- (void)setTileGroup:(SKTileGroup *)tileGroup andTileDefinition:(SKTileDefinition *)tileDefinition forColumn:(NSUInteger)column row:(NSUInteger)row;

/**
 Returns the column index of the tile that lies under the specified position. Returns NSUIntegerMax if the position does not fall within the tile map.
 @param position the position we want to check against the tile map
 */
- (NSUInteger)tileColumnIndexFromPosition:(CGPoint)position;

/**
 Returns the row index of the tile that lies under the specified position. Returns NSUIntegerMax if the position does not fall within the tile map.
 @param position the position we want to check against the tile map
 */
- (NSUInteger)tileRowIndexFromPosition:(CGPoint)position;

/**
 Returns the position of the center of the tile at the specified column and row.
 @param column the column index of the tile
 @param row the row index of the tile
 */
- (CGPoint)centerOfTileAtColumn:(NSUInteger)column row:(NSUInteger)row;

@end

NS_ASSUME_NONNULL_END

//
//  SKTileSet.h
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <SpriteKit/SKTileDefinition.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The tile set type is used to describe how the tiles will be arranged in a tile map.
 
 @enum SKTileSetTypeGrid Specifies that the tiles will be axis-alligned rectangles that are placed in rows and columns at right angles to one another. This is the default type.
 @enum SKTileSetTypeIsometric Specifies that the tiles will be rectangles that are rotated and scaled to give the appearance of 3/4 perspective.
 @enum SKTileSetTypeHexagonalFlat Specifies that the tiles will be flat bottomed hexagons.
 @enum SKTileSetTypeHexagonalPointy Specifies that the tiles will be "pointy" bottomed hexagons.
*/
typedef NS_ENUM(NSUInteger, SKTileSetType) {
    SKTileSetTypeGrid,
    SKTileSetTypeIsometric,
    SKTileSetTypeHexagonalFlat,
    SKTileSetTypeHexagonalPointy,
} NS_ENUM_AVAILABLE(10_12, 10_0);

/**
 The adjacency mask is used to specify which neighboring tiles need to be filled in for a rule to go into effect.
 */
typedef NS_OPTIONS(NSUInteger, SKTileAdjacencyMask) {
    
    SKTileAdjacencyUp         = 1 << 0, // The above neighboring tile
    SKTileAdjacencyUpperRight = 1 << 1, // The neighboring tile to the upper right
    SKTileAdjacencyRight      = 1 << 2, // The neighboring tile to the right
    SKTileAdjacencyLowerRight = 1 << 3, // The neighboring tile to the lower right
    SKTileAdjacencyDown       = 1 << 4, // The below neighboring tile
    SKTileAdjacencyLowerLeft  = 1 << 5, // The neighboring tile to the lower left
    SKTileAdjacencyLeft       = 1 << 6, // The neighboring tile to the left
    SKTileAdjacencyUpperLeft  = 1 << 7, // The neighboring tile to the upper left
    
    SKTileAdjacencyAll = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft,
    
    SKTileHexFlatAdjacencyUp         = 1 << 0,
    SKTileHexFlatAdjacencyUpperRight = 1 << 1,
    SKTileHexFlatAdjacencyLowerRight = 1 << 2,
    SKTileHexFlatAdjacencyDown       = 1 << 3,
    SKTileHexFlatAdjacencyLowerLeft  = 1 << 4,
    SKTileHexFlatAdjacencyUpperLeft  = 1 << 5,
    
    SKTileHexFlatAdjacencyAll = SKTileHexFlatAdjacencyUp | SKTileHexFlatAdjacencyUpperRight | SKTileHexFlatAdjacencyLowerRight | SKTileHexFlatAdjacencyDown | SKTileHexFlatAdjacencyLowerLeft | SKTileHexFlatAdjacencyUpperLeft,
    
    SKTileHexPointyAdjacencyUpperLeft  = 1 << 0,
    SKTileHexPointyAdjacencyUpperRight = 1 << 1,
    SKTileHexPointyAdjacencyRight      = 1 << 2,
    SKTileHexPointyAdjacencyLowerRight = 1 << 3,
    SKTileHexPointyAdjacencyLowerLeft  = 1 << 4,
    SKTileHexPointyAdjacencyLeft       = 1 << 5,
    
    SKTileHexPointyAdjacencyAdd = SKTileHexPointyAdjacencyUpperLeft | SKTileHexPointyAdjacencyUpperRight | SKTileHexPointyAdjacencyRight | SKTileHexPointyAdjacencyLowerRight | SKTileHexPointyAdjacencyLowerLeft | SKTileHexPointyAdjacencyLeft,
    
    // The enumerators below are pre-defined values for common tile configurations
    
    // Pre-defined values for an upwards-facing edge tile.
    SKTileAdjacencyUpEdge = SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft,
    
    // Pre-defined values for an upper right-facing edge tile.
    SKTileAdjacencyUpperRightEdge = SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft,
    
    // Pre-defined values for a right-facing edge tile.
    SKTileAdjacencyRightEdge = SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft | SKTileAdjacencyUp,
    
    // Pre-defined values for a lower right-facing edge tile.
    SKTileAdjacencyLowerRightEdge = SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft | SKTileAdjacencyUp,
    
    // Pre-defined values for a downwards-facing edge tile.
    SKTileAdjacencyDownEdge = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight | SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft,
    
    // Pre-defined values for a lower left-facing edge tile.
    SKTileAdjacencyLowerLeftEdge = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight,
    
    // Pre-defined values for a left-facing edge tile.
    SKTileAdjacencyLeftEdge = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown,
    
    // Pre-defined values for a upper left-facing edge tile.
    SKTileAdjacencyUpperLeftEdge = SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown,
    
    // Pre-defined values for an upper right-facing corner tile.
    SKTileAdjacencyUpperRightCorner = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown | SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft,
    
    // Pre-defined values for a lower right-facing corner tile.
    SKTileAdjacencyLowerRightCorner = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft,
    
    // Pre-defined values for a lower left-facing corner tile.
    SKTileAdjacencyLowerLeftCorner = SKTileAdjacencyUp | SKTileAdjacencyRight | SKTileAdjacencyLowerRight | SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft,
    
    // Pre-defined values for an upper left-facing corner tile.
    SKTileAdjacencyUpperLeftCorner = SKTileAdjacencyUp | SKTileAdjacencyUpperRight | SKTileAdjacencyRight | SKTileAdjacencyDown | SKTileAdjacencyLowerLeft | SKTileAdjacencyLeft | SKTileAdjacencyUpperLeft,
} NS_ENUM_AVAILABLE(10_12, 10_0);

@class SKTileGroup, SKTileGroupRule;

/**
 A tile set contains all of the tile definitions that are available for use in a tile map. In addition, it also contains tile groups, which define collections of related tile definitions and the rules that govern their placement.
 */
SK_EXPORT NS_AVAILABLE(10_12, 10_0) @interface SKTileSet : NSObject <NSCopying, NSCoding>

/**
 Create a tile set with the specified tile groups.
 @param tileGroups the tile groups that will be available for use with this set
 */
+ (instancetype)tileSetWithTileGroups:(NSArray<SKTileGroup *> *)tileGroups;

/**
 Create a tile set with the specified tile groups and tile set type.
 @param tileGroups the tile groups that will be available for use with this set
 @param tileSetType the type of tile set this will be
 */
+ (instancetype)tileSetWithTileGroups:(NSArray<SKTileGroup *> *)tileGroups tileSetType:(SKTileSetType)tileSetType;

/**
 Initilize a tile set with the specified tile groups.
 @param tileGroups the tile groups that will be available for use with this set
 */
- (instancetype)initWithTileGroups:(NSArray<SKTileGroup *> *)tileGroups;

/**
 Initilize a tile set with the specified tile groups and tile set type.
 @param tileGroups the tile groups that will be available for use with this set
 @param tileSetType the type of tile set this will be
 */
- (instancetype)initWithTileGroups:(NSArray<SKTileGroup *> *)tileGroups tileSetType:(SKTileSetType)tileSetType;

/**
 Gets the tile set with the specified name from the SpriteKit resource bundle. Returns nil if a tile set with a matching name cannot be found.
 @param name the name of the tile set to search for
 */
+ (nullable instancetype)tileSetNamed:(NSString *)name;

/**
 Creates a tile set from the specified tile set file. Returns nil if the URL doesn't point to a valid tile set file.
 @param name the URL of the tile set file
 */
+ (nullable instancetype)tileSetFromURL:(NSURL *)url;

/**
 The tile groups that this set provides for use.
 */
@property (nonatomic, copy) NSArray<SKTileGroup *> *tileGroups;

/**
 Client-assignable name for the tile set. Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSString *name;

/**
 The tile set type specifies how the tiles in the set will be arranged when placed in a tile map. Defaults to SKTileSetTypeGrid.
 */
@property (nonatomic) SKTileSetType type;

@property (nonatomic, nullable) SKTileGroup *defaultTileGroup;

/**
 The default tile size is the value an SKTileMapNode will use for it's tiles when the tile set is assigned to it.
 */
@property (nonatomic) CGSize defaultTileSize;

@end

/**
 A tile group encapsulates a collection of related tile definitions that are designed to be pieced together within a tile map. How those tiles are pieced together is governed by the set of rules. When a tile group is placed in a tile map, the map evaluates the rules to determine which tiles should be placed to achieve the desired outcome.
 */
SK_EXPORT NS_AVAILABLE(10_12, 10_0) @interface SKTileGroup : NSObject <NSCopying, NSCoding>

/**
 Create a simple tile group for a single tile definition. This creates and initializes the SKTileGroupRule necessary to place the provided tile definition in a tile map.
 @param the tile definition we wish to place in a tile map
 */
+ (instancetype)tileGroupWithTileDefinition:(SKTileDefinition *)tileDefinition;

/**
 Create a tile group with the specified rules.
 @param rules the rules the group will use to determine tile placement
 */
+ (instancetype)tileGroupWithRules:(NSArray<SKTileGroupRule *> *)rules;

/**
 Create an empty tile group. Placing this in a tile map will erase the existing tile at that location.
 */
+ (instancetype)emptyTileGroup;

/**
 Initilize a simple tile group for a single tile definition. This creates and initializes the SKTileGroupRule necessary to place the provided tile definition in a tile map.
 @param the tile definition we wish to place in a tile map
 */
- (instancetype)initWithTileDefinition:(SKTileDefinition *)tileDefinition;

/**
 Initilize a tile group with the specified rules.
 @param rules the rules the group will use to determine tile placement
 */
- (instancetype)initWithRules:(NSArray<SKTileGroupRule *> *)rules;

/**
 The rules that govern which tiles are placed when this group is used, and where in the map they'll be placed.
 */
@property (nonatomic, copy) NSArray<SKTileGroupRule *> *rules;

/**
 Client-assignable name for the tile group. Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSString *name;

@end

/**
 A tile group rule defines how a certain type of tile should be placed on the map. These tiles are like puzzle pieces, and the rules define how they should be pieced together. This is accomplished by defining which neighboring spaces need to be filled with tiles that belong to the same group, and which tiles are required to be empty. The required pattern of neighboring tiles is defined using the SKTileAdjacencyMask.
 */
SK_EXPORT NS_AVAILABLE(10_12, 10_0) @interface SKTileGroupRule : NSObject <NSCopying, NSCoding>

/**
 Create a tile group rule with the specified adjacency and tile definitions.
 @param adjacency the adjacency requirements for this rule; use the mask that covers the adjacent spaces that must be filled with tiles belonging to the same group; tiles not masked out must be empty
 @param tileDefinitions the tile definitions used for this rule
 */
+ (instancetype)tileGroupRuleWithAdjacency:(SKTileAdjacencyMask)adjacency tileDefinitions:(NSArray<SKTileDefinition*>*)tileDefinitions;

/**
 Initilize a tile group rule with the specified adjacency and tile definitions.
 @param adjacency the adjacency requirements for this rule; use the mask that covers the adjacent spaces that must be filled with tiles belonging to the same group; tiles not masked out must be empty
 @param tileDefinitions the tile definitions used for this rule
 */
- (instancetype)initWithAdjacency:(SKTileAdjacencyMask)adjacency tileDefinitions:(NSArray<SKTileDefinition *> *)tileDefinitions;

/**
 The adjacency mask used by this rule. Set this to the mask that covers the adjacent spaces that must be filled with tiles belonging to the same group for this rule met.
 */
@property (nonatomic) SKTileAdjacencyMask adjacency;


/**
 The tile definitions used by this rule. If the rule is evaluated and its conditions are met, one of the tile definitions within this array will be randomly selected for placement within the tile map. Each tile definitions' placement weight is taken into consideration to determine how likely each is to be selected; tile definitions with higher placement weights will be selected more frequently than those with lower placement weights.
 */
@property (nonatomic, copy) NSArray<SKTileDefinition *> *tileDefinitions;

/**
 Client-assignable name for the tile group rule. Defaults to nil.
 */
@property (nonatomic, copy, nullable) NSString *name;

@end

NS_ASSUME_NONNULL_END

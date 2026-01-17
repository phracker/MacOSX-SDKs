/**
 @header
 
 
 SpriteKit framework category additions related to GameplayKit integration.
 
 
 @copyright 2016 Apple, Inc. All rights reserve.
 
 */

#import <SpriteKit/SpriteKit.h>

#import <GameplayKit/GKEntity.h>
#import <GameplayKit/GKNoiseMap.h>
#import <GameplayKit/GKObstacle.h>
#import <GameplayKit/GKScene.h>

NS_ASSUME_NONNULL_BEGIN

@interface SKNode (GameplayKit)

/**
 * Returns an array of GKPolygonObstacles from a group of SKSpriteNode's textures in scene space.
 *
 * @see GKObstacleGraph
 */
+ (NSArray<GKPolygonObstacle*> *)obstaclesFromSpriteTextures:(NSArray<SKNode*>*)sprites accuracy:(float)accuracy;

/**
 * Returns an array of GKPolygonObstacles from a group of SKNode's transformed bounds in scene space.
 *
 * @see GKObstacleGraph
 */
+ (NSArray<GKPolygonObstacle*> *)obstaclesFromNodeBounds:(NSArray<SKNode*>*)nodes;

/**
 * Returns an array of GKPolygonObstacles from a group of SKNode's physics bodies in scene space.
 *
 * @see GKObstacleGraph
 */
+ (NSArray<GKPolygonObstacle*> *)obstaclesFromNodePhysicsBodies:(NSArray<SKNode*>*)nodes;

/**
 * The GKEntity associated with the node via a GKSKNodeComponent.
 *
 * @see GKEntity
 */
@property (nonatomic, weak) GKEntity *entity NS_AVAILABLE(10_12, 10_0);

@end

/**
 * Adds conformance to GKSceneRootNodeType for usage as rootNode of GKScene 
 */
@interface SKScene (GameplayKit) <GKSceneRootNodeType>

@end

@interface SKTileMapNode (GameplayKit)

/**
 * Create a set of layered tile map nodes with the specified tile set and dimensions, and fill each layer based on the provided noise map. Each 
 * layer will be partially filled with a tile group using values from the noise map that fall below the corresponding values in the thresholds 
 * array. The values in the noise map range from -1 to 1, and the provided threshold values are implicitly bounded with the values -1.0 and 1.0. 
 * Each threshold value corresponds with a tile group in the tile set, starting with the first tile group in the set. If, for example, we passed 
 * in a thresholds array with the values [-0.5, 0.0, 0.5], this method would return an array of four tile maps. The first tile map would contain 
 * the first tile group (i.e., tileSet.tileGroups[0]) within tiles that fall between the threshold values -1.0 and -0.5 in the noise map. The 
 * second tile map would contain the second tile group (i.e., tileSet.tileGroups[1]) within tiles that fall between the threshold values -0.5 and 
 * 0.0 in the noise map. The third tile map would contain the third tile group (i.e., tileSet.tileGroups[2]) within tiles that fall between the 
 * threshold values 0.0 and 0.5 in the noise map. And finally, the fourth tile map would contain the fourth tile group 
 * (i.e., tileSet.tileGroups[3]) within tiles that fall between the threshold values 0.5 and 1.0.
 *
 * @param tileSet the tile set that is used to render the tiles
 * @param columns the number of columns in each map that can hold tiles
 * @param rows the number of rows in each map that can hold tiles
 * @param tileSize the size of each tile in points
 * @param noiseMap the noise map we wish to use to fill each layer
 * @param thresholds the thresholds for each tile group in the tile set
 */
+ (NSArray<SKTileMapNode *> *)tileMapNodesWithTileSet:(SKTileSet *)tileSet columns:(NSUInteger)columns rows:(NSUInteger)rows tileSize:(CGSize)tileSize fromNoiseMap:(GKNoiseMap *)noiseMap tileTypeNoiseMapThresholds:(NSArray<NSNumber *> *)thresholds;

@end


@interface SKTexture (GameplayKit)

/**
 * Create a texture from a GKNoiseMap.
 *
 * @param noiseMap the GKNoiseMap from which to create the texture.
 */
+ (instancetype)textureWithNoiseMap:(GKNoiseMap *)noiseMap NS_AVAILABLE(10_12, 10_0);

@end

NS_ASSUME_NONNULL_END

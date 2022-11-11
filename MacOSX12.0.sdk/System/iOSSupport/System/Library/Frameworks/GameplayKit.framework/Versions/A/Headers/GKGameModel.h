//
//  GKGameModel.h
//  GameplayKit
//
//  Copyright (c) 2014 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Maximum / minimum values for GKGameModel scoreForPlayer. Values must be within these ranges.
 */
static const NSInteger GKGameModelMaxScore = 1 << 24;
static const NSInteger GKGameModelMinScore = -(1 << 24);

/**
 * A protocol used to encapsulate the data needed to affect an update to a game model. 
 * Typically represents an action or move performed by a player.
 */
@protocol GKGameModelUpdate <NSObject>

/**
 * Property get/set by GKMinmaxStrategist to sort GKGameModelUpdates.
 */
@property (nonatomic, assign) NSInteger value;

@end


/**
 * A protocol used to represent an individual player within a game model.
 */
@protocol GKGameModelPlayer <NSObject>

/**
 * Identifier used by GKMinmaxStrategist differentiate players from one another.
 */
@property (nonatomic, readonly) NSInteger playerId;

@end

/**
 * A protocol for abstracting a game model for use with the GKMinmaxStrategist class. The minmax
 * strategist uses the game model class, along with GKGameModelPlayer and GKGameModelUpdate to 
 * find optimal moves in an adversarial, turn-based game.
 */
@protocol GKGameModel <NSObject, NSCopying>

/**
 * Array of instances of GKGameModelPlayers representing players within this game model. When the 
 * GKMinmaxStrategist class is used to find an optimal move for a specific player, it uses this 
 * array to rate the moves of that player’s opponent(s).
 */
@property (nonatomic, readonly, nullable) NSArray<id<GKGameModelPlayer>> *players;

/**
 * The player whose turn it is to perform an update to the game model. GKMinmaxStrategist assumes 
 * that the next call to the applyGameModelUpdate: method will perform a move on behalf of this player.
 */
@property (nonatomic, readonly, nullable) id<GKGameModelPlayer> activePlayer;

/**
 * Sets the data of another game model. All data should be copied over, and should not maintain 
 * any pointers to the copied game state. This is used by the GKMinmaxStrategist to process
 * permutations of the game without needing to apply potentially destructive updates to the 
 * primary game model.
 */
- (void)setGameModel:(id<GKGameModel>)gameModel;

/**
 * Returns an array of all the GKGameModelUpdates (i.e. actions/moves) that the active
 * player can undertake, with one instance of GKGameModelUpdate for each possible move. 
 * Returns nil if the specified player is invalid, is not a part of the game model, or 
 * if there are no valid moves available.
 */
- (nullable NSArray<id<GKGameModelUpdate>> *)gameModelUpdatesForPlayer:(id <GKGameModelPlayer>)player;

/**
 * Applies a GKGameModelUpdate to the game model, potentially resulting in a new activePlayer. 
 * GKMinmaxStrategist will call this method on a copy of the primary game model to speculate 
 * about possible future moves and their effects. It is assumed that calling this method performs 
 * a move on behalf of the player identified by the activePlayer property.
 */
- (void)applyGameModelUpdate:(id<GKGameModelUpdate>)gameModelUpdate;

@optional

/**
 * Returns the score for the specified player. A higher value indicates a better position for
 * the player than a lower value. Required by GKMinmaxStrategist to determine which
 * GKGameModelUpdate is the most advantageous for a given player. If the player is invalid, or
 * not a part of the game model, returns NSIntegerMin.
 */
- (NSInteger)scoreForPlayer:(id<GKGameModelPlayer>)player;

/**
 * Returns YES if the specified player has reached a win state, NO if otherwise. Note that NO does not
 * necessarily mean that the player has lost. Optionally used by GKMinmaxStrategist to improve move selection.
 */
- (BOOL)isWinForPlayer:(id<GKGameModelPlayer>)player;

/**
 * Returns YES if the specified player has reached a loss state, NO if otherwise. Note that NO does not
 * necessarily mean that the player has won. Optionally used by GKMinmaxStrategist to improve move selection.
 */
- (BOOL)isLossForPlayer:(id<GKGameModelPlayer>)player;

- (void)unapplyGameModelUpdate:(id<GKGameModelUpdate>)gameModelUpdate;

@end


NS_ASSUME_NONNULL_END
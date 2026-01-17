//
//  GKStrategist.h
//  GameplayKit
//
//  Copyright (c) 2015 Apple. All rights reserved.
//

#import <GameplayKit/GKGameModel.h>
#import <GameplayKit/GKRandomSource.h>

NS_ASSUME_NONNULL_BEGIN

@protocol GKStrategist <NSObject>

/**
 * The game model that we wish to select updates for.
 */
@property (nonatomic, retain, nullable) id<GKGameModel> gameModel;

/**
 * A random source to use when breaking ties between equally-strong moves when calling bestMoveForPlayer
 * or when selecting a random move when randomMoveForPlayer is called. If set to nil, bestMoveForPlayer
 * and randomMoveForPlayer will simply return the first best move available.
 */
@property (nonatomic, retain, nullable) id<GKRandom> randomSource;

- (nullable id<GKGameModelUpdate>)bestMoveForActivePlayer;

@end

NS_ASSUME_NONNULL_END
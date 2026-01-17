//
//  GKMonteCarloStrategist.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <GameplayKit/GKStrategist.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The Monte Carlo Strategist is a generic AI that selects a game model update for a given player that results
 * in the highest likelihood for that player to eventually win the game. It does this by sampling the updates available
 * to the player in question. In doing this it will select the update it knows to produce the best result so far, expanding on this
 * selection, simulating the rest of the game from that expansion, and then propogating the results (win or loss) upwards.
 * It will do this until the budget has been reached, then returning the choice it has deemed best suited for the player in question.
 */
GK_BASE_AVAILABILITY_2 @interface GKMonteCarloStrategist : NSObject <GKStrategist>

/**
 * The maximum number of samples that will be processed when searching for a move.
 */
@property (nonatomic, assign) NSUInteger budget;

/**
 * A weight that encourages exploration of less visited updates versus the continued exploitation of previously visited updates.
 */
@property (nonatomic, assign) NSUInteger explorationParameter;

@end

NS_ASSUME_NONNULL_END

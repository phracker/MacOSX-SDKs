//
//  GKSavedGameListener.h
//  Game Center
//
//  Copyright 2010-2014 Apple Inc. All rights reserved.
//

@class GKPlayer;
@class GKSavedGame;

@protocol GKSavedGameListener <NSObject>
@optional

// Called when a player’s saved game data has been modified.
- (void)player:(GKPlayer *)player didModifySavedGame:(GKSavedGame *)savedGame;

// Called when a conflict has arisen between different versions of the same saved game. This can happen when multiple devices write to the same saved game while one or more is offline. The application should determine the correct data to use, then call resolveConflictingSavedGames:withData:completionHandler:. This may require data merging or asking the user.
- (void)player:(GKPlayer *)player hasConflictingSavedGames:(NSArray *)savedGames;

@end

//
//  GKSavedGame.h
//  Game Center
//
//  Copyright 2010-2014 Apple Inc. All rights reserved.
//

#import <GameKit/GKLocalPlayer.h>
#import <GameKit/GKSavedGameListener.h>

// Class representing a saved game for the local player, or a version of a saved game when in conflict
@interface GKSavedGame : NSObject <NSCopying>

@property (atomic, readonly) NSString *name;
@property (atomic, readonly) NSString *deviceName;
@property (atomic, readonly) NSDate *modificationDate;

// Asynchronously load the data for this saved game. The completion handler is called with loaded data or an error.
- (void)loadDataWithCompletionHandler:(void(^)(NSData *data, NSError *error))handler;

@end


@interface GKLocalPlayer (GKSavedGame) <GKSavedGameListener>

// Asynchronously fetch saved games. The handler is called with an array of GKSavedGame objects or an error.
// If there is more than one saved game with the same name then a conflict exists. The application should determine the correct data to use and call resolveConflictingSavedGames:withData:completionHandler:. This may require data merging or asking the user.
- (void)fetchSavedGamesWithCompletionHandler:(void(^)(NSArray *savedGames, NSError *error))handler;

// Asynchronously save game data. If a saved game with that name already exists it is overwritten, otherwise a new one is created. The completion handler is called with the new / modified GKSavedGame or an error.
// If the saved game was in conflict then the overwritten version will be the one with the same deviceName if present, otherwise the most recent overall.
- (void)saveGameData:(NSData *)data withName:(NSString *)name completionHandler:(void(^)(GKSavedGame *savedGame, NSError *error))handler;

// Asynchronously delete saved games with the given name. The completion handler will indicate whether or not the deletion was successful.
- (void)deleteSavedGamesWithName:(NSString *)name completionHandler:(void(^)(NSError *error))handler;

// Asynchronously resolve a saved game conflict. This deletes all versions included in conflictingSavedGames and creates a new version with the given data. The completion handler is called with the newly created save and all other remaining versions or an error.
- (void)resolveConflictingSavedGames:(NSArray *)conflictingSavedGames withData:(NSData *)data completionHandler:(void(^)(NSArray *savedGames, NSError *error))handler;

@end



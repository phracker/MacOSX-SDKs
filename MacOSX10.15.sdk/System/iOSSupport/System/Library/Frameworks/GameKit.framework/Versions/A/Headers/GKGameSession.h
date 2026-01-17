//
//  GKGameSession.h
//  Game Center
//
//  Copyright 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

@class GKCloudPlayer;

typedef NS_ENUM(NSInteger, GKConnectionState) {
    GKConnectionStateNotConnected,
    GKConnectionStateConnected
};

typedef NS_ENUM(NSInteger, GKTransportType) {
    GKTransportTypeUnreliable,
    GKTransportTypeReliable
};

NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("For real-time matches, use GKMatchmakerViewController. For turn-based matches, use GKTurnBasedMatchmakerViewController.", ios(10.0, 12.0), tvos(10.0, 12.0), macosx(10.12, 10.14)) API_UNAVAILABLE(watchos)
@interface GKGameSession : NSObject
#if !__OBJC2__
{
    NSString *_identifier;
    NSString *_title;
    GKCloudPlayer *_owner;
    NSArray<GKCloudPlayer *> *_players;
    NSDate *_lastModifiedDate;
    GKCloudPlayer *_lastModifiedPlayer;
    NSString *_serverChangeTag;
    NSInteger _maxNumberOfConnectedPlayers;
    NSMutableDictionary<NSString*, NSArray<NSNumber*> *> *_playerStates;
}
#endif

@property (nonatomic, readonly) NSString *identifier;
@property (nonatomic, readonly) NSString *title;
@property (nonatomic, readonly) GKCloudPlayer *owner;
@property (nonatomic, readonly) NSArray<GKCloudPlayer *> *players;
@property (nonatomic, readonly) NSDate *lastModifiedDate;
@property (nonatomic, readonly) GKCloudPlayer *lastModifiedPlayer;
@property (nonatomic, readonly) NSInteger maxNumberOfConnectedPlayers;
@property (nonatomic, readonly) NSArray<GKCloudPlayer *> *badgedPlayers;

// Create a new session with the given title and maximum number of connected players. (You may pass 0 to use the system limit of 16 players.)
+ (void)createSessionInContainer:(NSString * __nullable)containerName withTitle:(NSString *)title maxConnectedPlayers:(NSInteger)maxPlayers completionHandler:(void(^)(GKGameSession * __nullable session, NSError * __nullable error))completionHandler;

// Load all sessions involving the current user.
+ (void)loadSessionsInContainer:(NSString * __nullable)containerName completionHandler:(void(^)(NSArray<GKGameSession *> * __nullable sessions, NSError * __nullable error))completionHandler;

// Load a specific session.
+ (void)loadSessionWithIdentifier:(NSString *)identifier completionHandler:(void(^)(GKGameSession * __nullable session, NSError * __nullable error))completionHandler;

// Remove a session. If called by the owner this deletes the session from the server.
+ (void)removeSessionWithIdentifier:(NSString *)identifier completionHandler:(void(^)(NSError * __nullable error))completionHandler;


// Get the URL needed to share this session.
- (void)getShareURLWithCompletionHandler:(void(^)(NSURL * __nullable url, NSError * __nullable error))completionHandler;

// Load associated persistent data.
- (void)loadDataWithCompletionHandler:(void(^)(NSData * __nullable data, NSError * __nullable error))completionHandler;

// Save new/updated persistent data. Data size is limited to 512K. The session's lastModifiedDate and lastModifiedPlayer will be updated upon completion.
// If a version conflict is detected the handler will include the version currently on the server and an error. In this case the data has not been saved. To resolve the conflict a client would call this method again, presumably after merging data or giving the user a choice on how to resolve the conflict. (Note that when calling again it is possible to get a new conflict, if another device has since written a new version.)
- (void)saveData:(NSData *)data completionHandler:(void(^)(NSData * __nullable conflictingData, NSError * __nullable error))completionHandler;


// Set your connection state. May fail if you attempt to connect but the connected player limit has already been reached or there are network problems. The session's lastModifiedDate and lastModifiedPlayer will be updated upon completion.
- (void)setConnectionState:(GKConnectionState)state completionHandler:(void(^)(NSError * __nullable error))completionHandler;

// Get the players with the given connection state.
- (NSArray<GKCloudPlayer *> *)playersWithConnectionState:(GKConnectionState)state;

// Send data to all connected players.
- (void)sendData:(NSData *)data withTransportType:(GKTransportType)transport completionHandler:(void(^)(NSError * __nullable error))completionHandler;


// Send a message to any players in the session. This uses an unreliable push mechanism. Message/data delivery is not guaranteed and may take some time to arrive. Receiving players may optionally have their application badged for this session.
- (void)sendMessageWithLocalizedFormatKey:(NSString *)key arguments:(NSArray<NSString *> *)arguments data:(NSData * __nullable)data toPlayers:(NSArray<GKCloudPlayer *> *)players badgePlayers:(BOOL)badgePlayers completionHandler:(void(^)(NSError * __nullable error))completionHandler;

// Clear application badge state for players for this session.
- (void)clearBadgeForPlayers:(NSArray<GKCloudPlayer *> *)players completionHandler:(void(^)(NSError * __nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END

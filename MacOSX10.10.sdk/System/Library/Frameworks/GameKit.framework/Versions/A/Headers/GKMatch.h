//
//  GKMatch.h
//  Game Center
//
//  Copyright 2010-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GKVoiceChat;
@class GKPlayer;
@class GKThreadsafeDictionary;

@protocol GKMatchDelegate;

typedef NS_ENUM(NSInteger, GKMatchSendDataMode) {
    GKMatchSendDataReliable,         // a.s.a.p. but requires fragmentation and reassembly for large messages, may stall if network congestion occurs
    GKMatchSendDataUnreliable        // Preferred method. Best effort and immediate, but no guarantees of delivery or order; will not stall.
};

typedef NS_ENUM(NSInteger, GKPlayerConnectionState) {
    GKPlayerStateUnknown,       // initial player state
    GKPlayerStateConnected,     // connected to the match
    GKPlayerStateDisconnected   // disconnected from the match
};


// GKMatch represents an active networking sessions between players. It handles network communications and can report player connection status. All matches are created by a GKMatchmaker.
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKMatch : NSObject

@property(nonatomic, readonly) NSArray *players NS_AVAILABLE(10_10, 8_0);    // GKPlayers in the match
@property(nonatomic, assign) id<GKMatchDelegate> delegate;
@property(nonatomic, readonly) NSUInteger expectedPlayerCount;

// Asynchronously send data to one or more GKPlayers. Returns YES if delivery started, NO if unable to start sending and error will be set.
- (BOOL)sendData:(NSData *)data toPlayers:(NSArray *)players dataMode:(GKMatchSendDataMode)mode error:(NSError **)error NS_AVAILABLE(10_10, 8_0);

// Asynchronously broadcasts data to all players. Returns YES if delivery started, NO if unable to start sending and error will be set.
- (BOOL)sendDataToAllPlayers:(NSData *)data withDataMode:(GKMatchSendDataMode)mode error:(NSError **)error;

// Disconnect the match. This will show all other players in the match that the local player has disconnected. This should be called before releasing the match instance.
- (void)disconnect;

// Join a named voice chat channel
// Will return nil if parental controls are turned on
- (GKVoiceChat *)voiceChatWithName:(NSString *)name;

// Choose the best host from among the connected players using gathered estimates for bandwidth and packet loss. This is intended for applications that wish to implement a client-server model on top of the match. The returned player ID will be nil if the best host cannot currently be determined (e.g. players are still connecting).
- (void)chooseBestHostingPlayerWithCompletionHandler:(void(^)(GKPlayer *player))completionHandler NS_AVAILABLE(10_10, 8_0);

// Auto-matching to recreate a previous peer-to-peer match that became disconnected. A new match with the same set of players will be returned by the completion handler. All players should perform this when the match has ended for auto-matching to succeed. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
// 2. Timeout
- (void)rematchWithCompletionHandler:(void(^)(GKMatch *match, NSError *error))completionHandler NS_AVAILABLE(10_9, 6_0);

@end

@protocol GKMatchDelegate <NSObject>
@optional

// The match received data sent from the player.
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data fromRemotePlayer:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0);
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data fromPlayer:(NSString *)playerID NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use match:didReceiveData:fromRemotePlayer:");

// The player state changed (eg. connected or disconnected)
- (void)match:(GKMatch *)match player:(GKPlayer *)player didChangeConnectionState:(GKPlayerConnectionState)state NS_AVAILABLE(10_8, 4_1);
- (void)match:(GKMatch *)match player:(NSString *)playerID didChangeState:(GKPlayerConnectionState)state NS_DEPRECATED(10_8, 10_8, 4_1, 8_0, "use match:player:didChangeConnectionState:");

// The match was unable to be established with any players due to an error.
- (void)match:(GKMatch *)match didFailWithError:(NSError *)error NS_AVAILABLE(10_8, 4_1);

// This method is called when the match is interrupted; if it returns YES, a new invite will be sent to attempt reconnection. This is supported only for 1v1 games
- (BOOL)match:(GKMatch *)match shouldReinviteDisconnectedPlayer:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0);
- (BOOL)match:(GKMatch *)match shouldReinvitePlayer:(NSString *)playerID NS_DEPRECATED(10_8, 10_10, 5_0, 8_0, "use shouldReinviteDisconnectedPlayer:");

@end

@interface GKMatch (Deprecated)

- (void)chooseBestHostPlayerWithCompletionHandler:(void(^)(NSString *playerID))completionHandler NS_DEPRECATED(10_9, 10_10, 6_0, 8_0, "use chooseBestHostingPlayerWithCompletionHandler:");
- (BOOL)sendData:(NSData *)data toPlayers:(NSArray *)playerIDs withDataMode:(GKMatchSendDataMode)mode error:(NSError **)error NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use sendData:toPlayers:dataMode:error:");
@property(nonatomic, readonly) NSArray *playerIDs NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use players");    // NSStrings of player identifiers in the match

@end

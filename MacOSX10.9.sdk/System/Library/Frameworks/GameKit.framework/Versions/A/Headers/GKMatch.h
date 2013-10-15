//
//  GKMatch.h
//  GameKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>

@class GKVoiceChat;

@protocol GKMatchDelegate;

enum {
    GKMatchSendDataReliable,         // a.s.a.p. but requires fragmentation and reassembly for large messages, may stall if network congestion occurs
    GKMatchSendDataUnreliable        // Preferred method. Best effort and immediate, but no guarantees of delivery or order; will not stall.
};
typedef NSInteger GKMatchSendDataMode;

enum {
    GKPlayerStateUnknown,       // initial player state
    GKPlayerStateConnected,     // connected to the match
    GKPlayerStateDisconnected   // disconnected from the match
};
typedef NSInteger GKPlayerConnectionState;

// GKMatch represents an active networking sessions between players. It handles network communications and can report player connection status. All matches are created by a GKMatchmaker.
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKMatch : NSObject
@end

@interface GKMatch (GKAdditions)
@property(readonly, NS_NONATOMIC_IOSONLY) NSArray *playerIDs;    // NSStrings of player identifiers in the match
@property(assign, NS_NONATOMIC_IOSONLY) id<GKMatchDelegate> delegate;
@property(readonly, NS_NONATOMIC_IOSONLY) NSUInteger expectedPlayerCount;

// Asynchronously send data to one or more players. Returns YES if delivery started, NO if unable to start sending and error will be set.
- (BOOL)sendData:(NSData *)data toPlayers:(NSArray *)playerIDs withDataMode:(GKMatchSendDataMode)mode error:(NSError **)error;
// Asynchronously broadcasts data to all players. Returns YES if delivery started, NO if unable to start sending and error will be set.
- (BOOL)sendDataToAllPlayers:(NSData *)data withDataMode:(GKMatchSendDataMode)mode error:(NSError **)error;

// Disconnect the match. This will show all other players in the match that the local player has disconnected. This should be called before releasing the match instance.
- (void)disconnect;

// Join a named voice chat channel
// Will return nil if parental controls are turned on
- (GKVoiceChat *)voiceChatWithName:(NSString *)name;

// Choose the best host from among the connected players using gathered estimates for bandwidth and packet loss. This is intended for applications that wish to implement a client-server model on top of the match. The returned player ID will be nil if the best host cannot currently be determined (e.g. players are still connecting).
- (void)chooseBestHostPlayerWithCompletionHandler:(void(^)(NSString *playerID))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);

// Auto-matching to recreate a previous peer-to-peer match that became disconnected. A new match with the same set of players will be returned by the completion handler. All players should perform this when the match has ended for auto-matching to succeed. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
// 2. Timeout
- (void)rematchWithCompletionHandler:(void(^)(GKMatch *match, NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);

@end

@protocol GKMatchDelegate <NSObject>
@required
// The match received data sent from the player.
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data fromPlayer:(NSString *)playerID;

@optional
// The player state changed (eg. connected or disconnected)
- (void)match:(GKMatch *)match player:(NSString *)playerID didChangeState:(GKPlayerConnectionState)state;

// The match was unable to be established with any players due to an error.
- (void)match:(GKMatch *)match didFailWithError:(NSError *)error;

// This method is called when the match is interrupted; if it returns YES, a new invite will be sent to attempt reconnection. This is supported only for 1v1 games
- (BOOL)match:(GKMatch *)match shouldReinvitePlayer:(NSString *)playerID;

@end

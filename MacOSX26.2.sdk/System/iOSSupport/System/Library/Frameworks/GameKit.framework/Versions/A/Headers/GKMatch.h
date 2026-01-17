// Copyright © Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

#import <GameKit/GKDefines.h>

@class GKVoiceChat;
@class GKPlayer;
@class GKLocalPlayer;
@class GKThreadsafeDictionary;

@protocol GKMatchDelegate;

typedef NS_ENUM(NSInteger, GKMatchSendDataMode) {
    GKMatchSendDataReliable,         /// a.s.a.p. but requires fragmentation and reassembly for large messages, may stall if network congestion occurs
    GKMatchSendDataUnreliable        /// Preferred method. Best effort and immediate, but no guarantees of delivery or order; will not stall.
} API_AVAILABLE(ios(4.0), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, GKPlayerConnectionState) {
    GKPlayerStateUnknown,       /// initial player state
    GKPlayerStateConnected,     /// connected to the match
    GKPlayerStateDisconnected   /// disconnected from the match
} API_AVAILABLE(ios(4.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));

NS_ASSUME_NONNULL_BEGIN
/// GKMatch represents an active networking sessions between players. It handles network communications and can report player connection status. All matches are created by a GKMatchmaker.
API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface GKMatch : NSObject

@property(nonatomic, readonly) NSArray<GKPlayer *> *players API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);    /// all the GKPlayers in the match
@property(nonatomic, nullable, weak) id<GKMatchDelegate> delegate;
@property(nonatomic, readonly) NSUInteger expectedPlayerCount;
@property(nonatomic, nullable, readonly) GKMatchProperties *properties API_AVAILABLE(ios(17.2), macos(14.2), tvos(17.2), visionos(1.1)) API_UNAVAILABLE(watchos);
@property(nonatomic, nullable, readonly) NSDictionary<GKPlayer *, GKMatchProperties *> *playerProperties API_AVAILABLE(ios(17.2), macos(14.2), tvos(17.2), visionos(1.1)) API_UNAVAILABLE(watchos);

/// Asynchronously send data to one or more GKPlayers. Returns YES if delivery started, NO if unable to start sending and error will be set.
- (BOOL)sendData:(NSData *)data toPlayers:(NSArray<GKPlayer *> *)players dataMode:(GKMatchSendDataMode)mode error:(NSError * __nullable * __nullable)error API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Asynchronously broadcasts data to all players. Returns YES if delivery started, NO if unable to start sending and error will be set.
- (BOOL)sendDataToAllPlayers:(NSData *)data withDataMode:(GKMatchSendDataMode)mode error:(NSError * __nullable * __nullable)error;

/// Disconnect the match. This will show all other players in the match that the local player has disconnected. This should be called before releasing the match instance.
- (void)disconnect;

/// Choose the best host from among the connected players using gathered estimates for bandwidth and packet loss. This is intended for applications that wish to implement a client-server model on top of the match. The returned player ID will be nil if the best host cannot currently be determined (e.g. players are still connecting).
- (void)chooseBestHostingPlayerWithCompletionHandler:(void(^)(GKPlayer * __nullable player))completionHandler API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Automatching to recreate a previous peer-to-peer match that became disconnected. A new match with the same set of players will be returned by the completion handler. All players should perform this when the match has ended for automatching to succeed. Error will be nil on success.
/// Possible reasons for error:
/// 1. Communications failure
/// 2. Timeout
- (void)rematchWithCompletionHandler:(void(^__nullable)(GKMatch * __nullable match, NSError * __nullable error))completionHandler API_AVAILABLE(ios(6.0), macos(10.9), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*** This method is deprecated. GKVoiceChat is no longer supported. ***/
- (nullable GKVoiceChat *)voiceChatWithName:(NSString *)name API_DEPRECATED("No longer supported", ios(4.1, 18.0), macos(10.8, 15.0), tvos(9.0, 18.0), visionos(1.0, 2.0)) API_UNAVAILABLE(watchos);

@end

API_AVAILABLE(ios(4.0), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@protocol GKMatchDelegate <NSObject>
@optional

/// The match received data sent from the player.
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data fromRemotePlayer:(GKPlayer *)player API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data forRecipient:(GKPlayer *)recipient fromRemotePlayer:(GKPlayer *)player API_AVAILABLE(ios(9.0), macos(10.11), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// The player state changed (eg. connected or disconnected)
- (void)match:(GKMatch *)match player:(GKPlayer *)player didChangeConnectionState:(GKPlayerConnectionState)state API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// The match was unable to be established with any players due to an error.
- (void)match:(GKMatch *)match didFailWithError:(nullable NSError *)error API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// This method is called when the match is interrupted; if it returns YES, a new invite will be sent to attempt reconnection. This is supported only for 1v1 games
- (BOOL)match:(GKMatch *)match shouldReinviteDisconnectedPlayer:(GKPlayer *)player API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*** These protocol methods are obsoleted. They will never be invoked and their implementation does nothing***/
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data fromPlayer:(NSString *)playerID API_DEPRECATED_WITH_REPLACEMENT("Use ``GKMatchDelegate/match(_:didReceive:fromRemotePlayer:)`` instead.", ios(4.1,8.0), macos(10.8,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);
- (void)match:(GKMatch *)match player:(NSString *)playerID didChangeState:(GKPlayerConnectionState)state API_DEPRECATED_WITH_REPLACEMENT("Use ``GKMatchDelegate/match(_:player:didChange:)-8ohgr`` instead.", ios(4.1,8.0), macos(10.8,10.8), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);
- (BOOL)match:(GKMatch *)match shouldReinvitePlayer:(NSString *)playerID API_DEPRECATED_WITH_REPLACEMENT("Use ``GKMatchDelegate/match(_:shouldReinviteDisconnectedPlayer:)`` instead.", ios(5.0,8.0), macos(10.8,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);
@end

API_UNAVAILABLE(watchos, tvos)
@interface GKMatch (Obsoleted)
/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)chooseBestHostPlayerWithCompletionHandler:(void(^)(NSString * __nullable playerID))completionHandler API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKMatch/chooseBestHostingPlayer(completionHandler:)`` method instead.", ios(6.0,8.0), macos(10.9,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);

/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (BOOL)sendData:(NSData *)data toPlayers:(NSArray<NSString *> *)playerIDs withDataMode:(GKMatchSendDataMode)mode error:(NSError **)error API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKMatch/sendData(toAllPlayers:with:)`` method instead.", ios(4.1,8.0), macos(10.8,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);

/*** This property is obsolete.  ***/
@property(nonatomic, nullable, readonly) NSArray<NSString *> *playerIDs API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKMatch/players`` property instead.", ios(4.1,8.0), macos(10.8,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);   // NSStrings of player identifiers in the match

@end
NS_ASSUME_NONNULL_END

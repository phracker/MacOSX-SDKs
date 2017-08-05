//
//  GKMatchmaker.h
//  Game Center
//
//  Copyright 2010-2017 Apple Inc. All rights reserved.
//

#include <Foundation/Foundation.h>

@class GKPlayer;
@class GKMatch;


// Possible invitee responses
typedef NS_ENUM(NSInteger, GKInviteRecipientResponse) {
    GKInviteRecipientResponseAccepted           = 0,
    GKInviteRecipientResponseDeclined           = 1,
    GKInviteRecipientResponseFailed             = 2,
    GKInviteRecipientResponseIncompatible       = 3,
    GKInviteRecipientResponseUnableToConnect    = 4,
    GKInviteRecipientResponseNoAnswer           = 5,
    
    // Old names
    GKInviteeResponseAccepted           = GKInviteRecipientResponseAccepted,
    GKInviteeResponseDeclined           = GKInviteRecipientResponseDeclined,
    GKInviteeResponseFailed             = GKInviteRecipientResponseFailed,
    GKInviteeResponseIncompatible       = GKInviteRecipientResponseIncompatible,
    GKInviteeResponseUnableToConnect    = GKInviteRecipientResponseUnableToConnect,
    GKInviteeResponseNoAnswer           = GKInviteRecipientResponseNoAnswer,
};

typedef GKInviteRecipientResponse GKInviteeResponse;

NS_ASSUME_NONNULL_BEGIN
// GKMatchRequest represents the parameters needed to create the match.
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_AVAILABLE(3_0)
@interface GKMatchRequest : NSObject

@property(assign) NSUInteger minPlayers;     // Minimum number of players for the match
@property(assign) NSUInteger maxPlayers;     // Maximum number of players for the match
@property(assign) NSUInteger playerGroup;    // The player group identifier. Matchmaking will only take place between players in the same group.
@property(assign) uint32_t playerAttributes; // optional mask that specifies the role that the local player would like to play in the game.  If this value is 0 (the default), this property is ignored. If the value is nonzero, then automatching uses the value as a mask that restricts the role the player can play in the group. Automatching with player attributes matches new players into the game so that the bitwise OR of the masks of all the players in the resulting match equals 0xFFFFFFFF.
@property(retain, nullable) NSArray<GKPlayer *> *recipients NS_AVAILABLE(10_10, 8_0);  // Array of GKPlayers to invite, or nil if none. This array can also include local guest players.
@property(retain, nullable) NSArray<NSString *> *playersToInvite NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use recipients") ; // Array of player IDs to invite, or nil if none

// Message sent to invited players, may be modified if using GKMatchmakerViewController
@property(copy, nullable)   NSString *inviteMessage NS_AVAILABLE(10_8, 6_0);

// Default number of players to use during matchmaking.  If not set we default to maxPlayers
@property(assign) NSUInteger defaultNumberOfPlayers NS_AVAILABLE(10_8, 6_0);

// An recipientResponseHandler can be set in order to receive responses from programmatically invited players.
@property(copy, nullable) void(^recipientResponseHandler)(GKPlayer *player, GKInviteRecipientResponse response) NS_AVAILABLE(10_10, 8_0);
@property(copy, nullable) void(^inviteeResponseHandler)(NSString *playerID, GKInviteeResponse response) NS_DEPRECATED(10_9, 10_10, 6_0, 8_0, "use recipientResponseHandler") ;

typedef NS_ENUM(NSUInteger, GKMatchType) {
    GKMatchTypePeerToPeer,
    GKMatchTypeHosted,
    GKMatchTypeTurnBased
};

// To determine the maximum allowed players for each type of match supported.
+ (NSUInteger)maxPlayersAllowedForMatchOfType:(GKMatchType)matchType NS_AVAILABLE(10_9, 6_0);

@end


// GKInvite represents an accepted game invite, it is used to create a GKMatchmakerViewController
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_PROHIBITED
@interface GKInvite : NSObject

@property(readonly, retain, NS_NONATOMIC_IOSONLY) GKPlayer *sender NS_AVAILABLE(10_10, 8_0);
@property(readonly, retain, NS_NONATOMIC_IOSONLY) NSString *inviter NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use sender") ;
@property(readonly, getter=isHosted, NS_NONATOMIC_IOSONLY) BOOL hosted;
@property(readonly, NS_NONATOMIC_IOSONLY) NSUInteger playerGroup NS_AVAILABLE(10_9, 6_0);      // player group from inviter's match request
@property(readonly, NS_NONATOMIC_IOSONLY) uint32_t playerAttributes NS_AVAILABLE(10_9, 6_0);   // player attributes from inviter's match request

@end

// GKInviteEventListener uses the GKLocalPlayerListener mechanism on GKLocalPlayer to listen to the two kinds of invite events that a game must respond to
@protocol GKInviteEventListener

@optional

// player:didAcceptInvite: gets called when another player accepts the invite from the local player
- (void)player:(GKPlayer *)player didAcceptInvite:(GKInvite *)invite NS_AVAILABLE(10_10, 7_0) __WATCHOS_PROHIBITED;

// didRequestMatchWithRecipients: gets called when the player chooses to play with another player from Game Center and it launches the game to start matchmaking
- (void)player:(GKPlayer *)player didRequestMatchWithRecipients:(NSArray<GKPlayer *> *)recipientPlayers NS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED;
- (void)player:(GKPlayer *)player didRequestMatchWithPlayers:(NSArray<NSString *> *)playerIDsToInvite NS_DEPRECATED_IOS(7_0, 8_0, "use player:didRequestMatchWithRecipients:") ;

@end


// GKMatchmaker is a singleton object to manage match creation from invites and auto-matching.
NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_PROHIBITED
@interface GKMatchmaker : NSObject

// The shared matchmaker
+ (GKMatchmaker *)sharedMatchmaker;

// Get a match for an accepted invite
// Possible reasons for error:
// 1. Communications failure
// 2. Invite cancelled
- (void)matchForInvite:(GKInvite *)invite completionHandler:(void(^__nullable)(GKMatch * __nullable match, NSError * __nullable error))completionHandler NS_AVAILABLE(10_9, 6_0);

// Auto-matching or invites to find a peer-to-peer match for the specified request. Error will be nil on success:
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
// 3. Timeout
// Note that the players property on the returned GKMatch instance will only contain connected players. It will initially be empty as players are connecting. Implement the GKMatchDelegate method match:player:didChangeConnectionState: to listen for updates to the GKMatch instance's players property.

- (void)findMatchForRequest:(GKMatchRequest *)request withCompletionHandler:(void(^__nullable)(GKMatch * __nullable match, NSError * __nullable error))completionHandler;

// Auto-matching or invites for host-client match request. This returns a list of player identifiers to be included in the match. Determination and communication with the host is not part of this API.
// When inviting, no player identifiers will be returned. Player responses will be reported via the inviteeResponseHandler.
// Possible reasons for error:
// 1. Communications failure
// 2. Unauthenticated player
// 3. Timeout
- (void)findPlayersForHostedRequest:(GKMatchRequest *)request withCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable players, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 8_0);

// Auto-matching or invites to add additional players to a peer-to-peer match for the specified request. Error will be nil on success:
// Possible reasons for error:
// 1. Communications failure
// 2. Timeout
- (void)addPlayersToMatch:(GKMatch *)match matchRequest:(GKMatchRequest *)matchRequest completionHandler:(void (^__nullable)(NSError * __nullable error))completionHandler;

// Cancel matchmaking and any pending invites
- (void)cancel;

// Cancel a pending invitation to a player
- (void)cancelPendingInviteToPlayer:(GKPlayer *)player NS_AVAILABLE(10_10, 8_0);

// Call this when finished with all programmatic P2P invites/matchmaking, for compatability with connected players using GKMatchmakerViewController.
- (void)finishMatchmakingForMatch:(GKMatch *)match NS_AVAILABLE(10_9, 6_0);

// Query the server for recent activity in the specified player group. A larger value indicates that a given group has seen more recent activity. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
- (void)queryPlayerGroupActivity:(NSUInteger)playerGroup withCompletionHandler:(void(^__nullable)(NSInteger activity, NSError * __nullable error))completionHandler;

// Query the server for recent activity for all the player groups of that game. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
- (void)queryActivityWithCompletionHandler:(void(^__nullable)(NSInteger activity, NSError * __nullable error))completionHandler;


// Start browsing for nearby players that can be invited to a match. The reachableHandler will be called for each player found with a compatible game. It may be called more than once for the same player if that player ever becomes unreachable (e.g. moves out of range). You should call stopBrowsingForNearbyPlayers when finished browsing.
- (void)startBrowsingForNearbyPlayersWithHandler:(void(^__nullable)(GKPlayer *player, BOOL reachable))reachableHandler NS_AVAILABLE(10_10, 8_0);

// Stop browsing for nearby players.
- (void)stopBrowsingForNearbyPlayers  NS_AVAILABLE(10_9, 6_0);

@end

@interface GKMatchmaker (GKDeprecated)

@property(nonatomic, nullable, copy) void(^inviteHandler)(GKInvite *acceptedInvite, NSArray * __nullable playerIDsToInvite) NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use registerListener on GKLocalPlayer to register an object that implements the GKInviteEventListenerProtocol instead") ;

- (void)startBrowsingForNearbyPlayersWithReachableHandler:(void(^__nullable)(NSString *playerID, BOOL reachable))reachableHandler NS_DEPRECATED(10_9, 10_10, 6_0, 8_0, "Use startBrowsingForNearbyPlayersWithHandler: instead") ;
- (void)cancelInviteToPlayer:(NSString *)playerID NS_DEPRECATED(10_9, 10_10, 6_0, 8_0, "use cancelPendingInviteToPlayer:") ;
- (void)findPlayersForHostedMatchRequest:(GKMatchRequest *)request withCompletionHandler:(void(^__nullable)(NSArray<NSString *> * __nullable playerIDs, NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use findPlayersForHostedRequest:") ;

@end
NS_ASSUME_NONNULL_END

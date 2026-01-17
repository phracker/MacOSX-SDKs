// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>

#import <GameKit/GKDefines.h>

@class GKMatch;
@class GKPlayer;

/// Possible invitee responses
typedef NS_ENUM(NSInteger, GKInviteRecipientResponse) {
    GKInviteRecipientResponseAccepted           = 0,
    GKInviteRecipientResponseDeclined           = 1,
    GKInviteRecipientResponseFailed             = 2,
    GKInviteRecipientResponseIncompatible       = 3,
    GKInviteRecipientResponseUnableToConnect    = 4,
    GKInviteRecipientResponseNoAnswer           = 5,

    // Old names
    GKInviteeResponseAccepted API_DEPRECATED_WITH_REPLACEMENT("Use ``GKInviteRecipientResponse/accepted`` instead.", ios(6.0,18.4), macos(10.8,15.4), tvos(9.0,18.4), watchos(3.0,11.4), visionos(1.0,2.4))
        = GKInviteRecipientResponseAccepted,

    GKInviteeResponseDeclined API_DEPRECATED_WITH_REPLACEMENT("Use ``GKInviteRecipientResponse/declined`` instead.", ios(6.0,18.4), macos(10.8,15.4), tvos(9.0,18.4), watchos(3.0,11.4), visionos(1.0,2.4))
        = GKInviteRecipientResponseDeclined,

    GKInviteeResponseFailed API_DEPRECATED_WITH_REPLACEMENT("Use ``GKInviteRecipientResponse/failed`` instead.", ios(6.0,18.4), macos(10.8,15.4), tvos(9.0,18.4), watchos(3.0,11.4), visionos(1.0,2.4))
        = GKInviteRecipientResponseFailed,

    GKInviteeResponseIncompatible API_DEPRECATED_WITH_REPLACEMENT("Use ``GKInviteRecipientResponse/incompatible`` instead.", ios(6.0,18.4), macos(10.8,15.4), tvos(9.0,18.4), watchos(3.0,11.4), visionos(1.0,2.4))
        = GKInviteRecipientResponseIncompatible,

    GKInviteeResponseUnableToConnect API_DEPRECATED_WITH_REPLACEMENT("Use ``GKInviteRecipientResponse/unableToConnect`` instead.", ios(6.0,18.4), macos(10.8,15.4), tvos(9.0,18.4), watchos(3.0,11.4), visionos(1.0,2.4))
        = GKInviteRecipientResponseUnableToConnect,

    GKInviteeResponseNoAnswer API_DEPRECATED_WITH_REPLACEMENT("Use ``GKInviteRecipientResponse/noAnswer`` instead.", ios(6.0,18.4), macos(10.8,15.4), tvos(9.0,18.4), watchos(3.0,11.4), visionos(1.0,2.4))
        = GKInviteRecipientResponseNoAnswer,
} API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0), watchos(3.0));

typedef GKInviteRecipientResponse GKInviteeResponse API_DEPRECATED_WITH_REPLACEMENT("Use ``GKInviteRecipientResponse`` instead.", ios(6.0,17.0), macos(10.8,14.0), tvos(9.0,17.0), watchos(3.0,10.0), visionos(1.0,1.0));

NS_ASSUME_NONNULL_BEGIN
/// GKMatchRequest represents the parameters needed to create the match.
API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0))
@interface GKMatchRequest : NSObject

/// Minimum number of players for the match
@property(assign) NSUInteger minPlayers;

/// Maximum number of players for the match
@property(assign) NSUInteger maxPlayers;

/// The player group identifier. Matchmaking will only take place between players in the same group.
@property(assign) NSUInteger playerGroup;

/// optional mask that specifies the role that the local player would like to play in the game.  If this value is 0, it will be set to 0xFFFFFFFF (the default), and this property will be ignored. If the value is nonzero, then automatching uses the value as a mask that restricts the role the player can play in the group. Automatching with player attributes matches new players into the game so that the bitwise OR of the masks of all the players in the resulting match equals 0xFFFFFFFF.
@property(assign) uint32_t playerAttributes;

/// Array of GKPlayers to invite, or nil if none. This array can also include local guest players.
@property(retain, nullable) NSArray<GKPlayer *> *recipients API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0), watchos(3.0));

/// Message sent to invited players, may be modified if using GKMatchmakerViewController
/// Will return nil if the player is underage or restricted.
@property(copy, nullable)   NSString *inviteMessage API_AVAILABLE(ios(6.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));

/// Default number of players to use during matchmaking. If not set we will default to the number that the player previously set for this game, or maxPlayers.
@property(assign) NSUInteger defaultNumberOfPlayers API_AVAILABLE(ios(6.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));

/// Whether or not a match will be created only using automatch.  If YES, then a player will not be able to
/// invite anyone (including contacts, friends, and nearby players) to the match, but rely on automatching to
/// find players for the match.  Default is NO.
@property(assign) BOOL restrictToAutomatch API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKMatchmakerViewController/matchmakingMode`` property instead.", ios(13.0, 14.0), tvos(13.0, 14.0), macos(10.15, 11.0));

/// An recipientResponseHandler can be set in order to receive responses from programmatically invited players.
@property(copy, nullable) void(^recipientResponseHandler)(GKPlayer *player, GKInviteRecipientResponse response) API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0), watchos(3.0));
@property(copy, nullable) void(^inviteeResponseHandler)(NSString *playerID, GKInviteeResponse response) API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKMatchRequest/recipientResponseHandler`` property instead.", ios(6.0,8.0), macos(10.9,10.10)) API_UNAVAILABLE(tvos);

typedef NS_ENUM(NSUInteger, GKMatchType) {
    GKMatchTypePeerToPeer,
    GKMatchTypeHosted,
    GKMatchTypeTurnBased
} API_AVAILABLE(ios(6.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));

/// To determine the maximum allowed players for each type of match supported.
+ (NSUInteger)maxPlayersAllowedForMatchOfType:(GKMatchType)matchType API_AVAILABLE(ios(6.0), macos(10.9), tvos(9.0), visionos(1.0), watchos(3.0));

@property(retain, nullable) NSArray<NSString *> *playersToInvite API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKMatchRequest/recipients`` property instead.", ios(4.1,8.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos); // Array of player IDs to invite, or nil if none

/// The name of the queue, if rule-based matchmaking is used.
@property(copy, nullable) NSString *queueName API_AVAILABLE(ios(17.2), macos(14.2), watchos(10.2), tvos(17.2), visionos(1.1));

/// The match properties, if rule-based matchmaking is used.
@property(copy, nullable) GKMatchProperties *properties API_AVAILABLE(ios(17.2), macos(14.2), watchos(10.2), tvos(17.2), visionos(1.1));

/// The recipient specific match properties, if rule-based matchmaking is used when inviting players.
@property(copy, nullable) NSDictionary<GKPlayer *, GKMatchProperties *> *recipientProperties API_AVAILABLE(ios(17.2), macos(14.2), watchos(10.2), tvos(17.2), visionos(1.1));

@end

/// GKInvite represents an accepted game invite, it is used to create a GKMatchmakerViewController
API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface GKInvite : NSObject

@property(readonly, retain, NS_NONATOMIC_IOSONLY) GKPlayer *sender API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
@property(readonly, getter=isHosted, NS_NONATOMIC_IOSONLY) BOOL hosted;
/// player group from inviter's match request
@property(readonly, NS_NONATOMIC_IOSONLY) NSUInteger playerGroup API_AVAILABLE(ios(6.0), macos(10.9), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
/// player attributes from inviter's match request
@property(readonly, NS_NONATOMIC_IOSONLY) uint32_t playerAttributes API_AVAILABLE(ios(6.0), macos(10.9), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*** This property is obsolete. ***/
@property(readonly, retain, NS_NONATOMIC_IOSONLY) NSString *inviter API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKInvite/sender`` property instead.", ios(4.1,8.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos, watchos);
@end

/// GKInviteEventListener uses the GKLocalPlayerListener mechanism on GKLocalPlayer to listen to the two kinds of invite events that a game must respond to
API_AVAILABLE(ios(7.0), macos(10.10), tvos(9.0), visionos(1.0), watchos(3.0))
@protocol GKInviteEventListener

@optional

/// player:didAcceptInvite: gets called when another player accepts the invite from the local player
- (void)player:(GKPlayer *)player didAcceptInvite:(GKInvite *)invite API_AVAILABLE(ios(7.0), macos(10.10), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// didRequestMatchWithRecipients: gets called when the player chooses to play with another player from Game Center and it launches the game to start matchmaking
- (void)player:(GKPlayer *)player didRequestMatchWithRecipients:(NSArray<GKPlayer *> *)recipientPlayers API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)player:(GKPlayer *)player didRequestMatchWithPlayers:(NSArray<NSString *> *)playerIDsToInvite API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKInviteEventListener/player(_:didRequestMatchWithRecipients:)`` method instead.", ios(7.0,8.0), macos(10.9,10.10)) API_UNAVAILABLE(tvos);
@end

API_AVAILABLE(ios(17.2), macos(14.2), tvos(17.2), visionos(1.1)) API_UNAVAILABLE(watchos)
@interface GKMatchedPlayers : NSObject

@property(nonatomic, nullable, readonly) GKMatchProperties *properties;
@property(nonatomic, readonly) NSArray<GKPlayer *> *players;
@property(nonatomic, nullable, readonly) NSDictionary<GKPlayer *, GKMatchProperties *> *playerProperties;

@end

/// GKMatchmaker is a singleton object to manage match creation from invites and automatching.
API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos)
@interface GKMatchmaker : NSObject

/// The shared matchmaker
+ (GKMatchmaker *)sharedMatchmaker;

/// Get a match for an accepted invite
/// Possible reasons for error:
/// 1. Communications failure
/// 2. Invite cancelled
- (void)matchForInvite:(GKInvite *)invite completionHandler:(void(^__nullable)(GKMatch * __nullable match, NSError * __nullable error))completionHandler API_AVAILABLE(ios(6.0), macos(10.9), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Automatching or invites to find a peer-to-peer match for the specified request. Error will be nil on success:
/// Possible reasons for error:
/// 1. Communications failure
/// 2. Unauthenticated player
/// 3. Timeout
/// Note that the players property on the returned GKMatch instance will only contain connected players. It will initially be empty as players are connecting. Implement the GKMatchDelegate method match:player:didChangeConnectionState: to listen for updates to the GKMatch instance's players property.
- (void)findMatchForRequest:(GKMatchRequest *)request withCompletionHandler:(void(^__nullable)(GKMatch * __nullable match, NSError * __nullable error))completionHandler;

/// Automatching or invites for host-client match request. This returns a list of player identifiers to be included in the match. Determination and communication with the host is not part of this API.
/// When inviting, no player identifiers will be returned. Player responses will be reported via the inviteeResponseHandler.
/// Possible reasons for error:
/// 1. Communications failure
/// 2. Unauthenticated player
/// 3. Timeout
- (void)findPlayersForHostedRequest:(GKMatchRequest *)request withCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable players, NSError * __nullable error))completionHandler API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Automatching or invites for host-client rule-based match request.
- (void)findMatchedPlayers:(GKMatchRequest *)request withCompletionHandler:(void(^)(GKMatchedPlayers * __nullable matchedPlayers, NSError * __nullable error))completionHandler API_AVAILABLE(ios(17.2), macos(14.2), tvos(17.2), visionos(1.1)) API_UNAVAILABLE(watchos);

/// Automatching or invites to add additional players to a peer-to-peer match for the specified request. Error will be nil on success:
/// Possible reasons for error:
/// 1. Communications failure
/// 2. Timeout
- (void)addPlayersToMatch:(GKMatch *)match matchRequest:(GKMatchRequest *)matchRequest completionHandler:(void (^__nullable)(NSError * __nullable error))completionHandler;

/// Cancel matchmaking and any pending invites
- (void)cancel;

/// Cancel a pending invitation to a player
- (void)cancelPendingInviteToPlayer:(GKPlayer *)player API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Call this when finished with all programmatic P2P invites/matchmaking, for compatability with connected players using GKMatchmakerViewController.
- (void)finishMatchmakingForMatch:(GKMatch *)match API_AVAILABLE(ios(6.0), macos(10.9), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Query the server for recent activity in the specified player group. A larger value indicates that a given group has seen more recent activity. Error will be nil on success.
/// Possible reasons for error:
/// 1. Communications failure
- (void)queryPlayerGroupActivity:(NSUInteger)playerGroup withCompletionHandler:(void(^__nullable)(NSInteger activity, NSError * __nullable error))completionHandler;

/// Query the server for recent activity for all the player groups of that game. Error will be nil on success.
/// Possible reasons for error:
/// 1. Communications failure
- (void)queryActivityWithCompletionHandler:(void(^__nullable)(NSInteger activity, NSError * __nullable error))completionHandler;

///  Query the server for recent activity for the specified queue.
- (void)queryQueueActivity:(NSString *)queueName withCompletionHandler:(void(^__nullable)(NSInteger activity, NSError * __nullable error))completionHandler API_AVAILABLE(ios(17.2), macos(14.2), tvos(17.2), visionos(1.1)) API_UNAVAILABLE(watchos);

/// Start browsing for nearby players that can be invited to a match. The reachableHandler will be called for each player found with a compatible game. It may be called more than once for the same player if that player ever becomes unreachable (e.g. moves out of range). You should call stopBrowsingForNearbyPlayers when finished browsing.
- (void)startBrowsingForNearbyPlayersWithHandler:(void(^__nullable)(GKPlayer *player, BOOL reachable))reachableHandler API_AVAILABLE(ios(8.0), macos(10.10), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Stop browsing for nearby players.
- (void)stopBrowsingForNearbyPlayers  API_AVAILABLE(ios(6.0), macos(10.9), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

/// Activate  a  group activity by Game Center for your game, which allows people in the FaceTime call to join the local player's game. The handler will be called for each player who joined from the activity.
- (void)startGroupActivityWithPlayerHandler:(void(^)(GKPlayer *player))handler API_AVAILABLE(ios(16.2), macos(13.1), visionos(1.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_DISABLE_ASYNC;

/// End the group activity created by Game Center for your game, which was activated by the local player.
- (void)stopGroupActivity API_AVAILABLE(ios(16.2), macos(13.1), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);

@end

@interface GKMatchmaker (GKDeprecated)

@property(nonatomic, nullable, copy) void(^inviteHandler)(GKInvite *acceptedInvite, NSArray * __nullable playerIDsToInvite) API_DEPRECATED("Use the ``GKLocalPlayer/register(_:)`` method instead.", ios(4.1,7.0), macos(10.8,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);
@end

@interface GKMatchmaker (Obsoleted)
/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)startBrowsingForNearbyPlayersWithReachableHandler:(void(^__nullable)(NSString *playerID, BOOL reachable))reachableHandler API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKMatchmaker/startBrowsingForNearbyPlayers(handler:)`` method instead.", ios(6.0,8.0), macos(10.9,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);

/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)cancelInviteToPlayer:(NSString *)playerID API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKMatchmaker/cancelPendingInvite(to:)`` method instead.", ios(6.0,8.0), macos(10.9,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);

/*** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)findPlayersForHostedMatchRequest:(GKMatchRequest *)request withCompletionHandler:(void(^__nullable)(NSArray<NSString *> * __nullable playerIDs, NSError * __nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKMatchmaker/findPlayers(forHostedRequest:withCompletionHandler:)`` method instead.", ios(4.1,8.0), macos(10.8,10.10), visionos(1.0,1.0)) API_UNAVAILABLE(tvos, watchos);
@end
NS_ASSUME_NONNULL_END

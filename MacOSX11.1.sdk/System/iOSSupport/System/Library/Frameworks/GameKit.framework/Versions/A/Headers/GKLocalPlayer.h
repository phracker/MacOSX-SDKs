//
//  GKLocalPlayer.h
//  Game Center
//
//  Copyright 2010-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKPlayer.h>
#import <GameKit/GKDefines.h>
#import <GameKit/GKEventListener.h>
#import <GameKit/GKTurnBasedMatch.h>
#import <GameKit/GKMatchmaker.h>
#import <GameKit/GKSavedGameListener.h>

#if TARGET_OS_IPHONE
@class UIViewController;
#else
@class NSViewController;
#endif

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_AVAILABLE(3_0)
@interface GKLocalPlayer : GKPlayer

/** Obtain the primary GKLocalPlayer object.
    The player is only available for offline play until logged in.
    A temporary player is created if no account is set up.
 */
@property (class, readonly, nonnull) GKLocalPlayer *local API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

@property (class, readonly, nonnull) GKLocalPlayer *localPlayer;

/// Authentication state
@property(readonly, getter=isAuthenticated, NS_NONATOMIC_IOSONLY)  BOOL authenticated;


/// Indicates if a player is under age
@property(readonly, getter=isUnderage, NS_NONATOMIC_IOSONLY)       BOOL underage;

/// A Boolean value that declares whether or not multiplayer gaming is restricted on this device.
@property(readonly, getter=isMultiplayerGamingRestricted, nonatomic) BOOL multiplayerGamingRestricted API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

/// A Boolean value that declares whether personalized communication is restricted on this device. If it is restricted, the player will not be able to read or write personalized messages on game invites, challenges, or enable voice communication in multiplayer games.  Note: this value will always be true when isUnderage is true.
@property(readonly, getter=isPersonalizedCommunicationRestricted, nonatomic) BOOL personalizedCommunicationRestricted API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0)) API_UNAVAILABLE(watchos);

#if TARGET_OS_WATCH
@property(atomic, nullable, copy) void(^authenticateHandler)(NSError * __nullable error)  __WATCHOS_AVAILABLE(3_0);
#endif

/** Asynchronously load the recent players list as an array of GKPlayer.  A recent player is someone that you have played a game with or is a legacy game center friend.  Calls completionHandler when finished. Error will be nil on success.
    Possible reasons for error:
    1. Communications problem
    2. Unauthenticated player
 */
- (void)loadRecentPlayersWithCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable recentPlayers, NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 10_0) __WATCHOS_AVAILABLE(3_0);

/** Asynchronously load the challengable friends list as an array of GKPlayer.  A challengable player is a friend player with friend level FL1 and FL2.  Calls completionHandler when finished. Error will be nil on success.
   Possible reasons for error:
   1. Communications problem
   2. Unauthenticated player
*/
- (void)loadChallengableFriendsWithCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable challengableFriends, NSError * __nullable error))completionHandler;


/** Set the default leaderboard for the current game
    Possible reasons for error:
    1. Communications problem
    2. Unauthenticated player
    3. Leaderboard not present
 */
- (void)setDefaultLeaderboardIdentifier:(NSString *)leaderboardIdentifier completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);


/** Load the default leaderboard identifier for the local player
    Possible reasons for error:
    1. Communications problem
    2. Unauthenticated player
    3. Leaderboard not present
 */
- (void)loadDefaultLeaderboardIdentifierWithCompletionHandler:(void(^__nullable)(NSString * __nullable leaderboardIdentifier, NSError * __nullable error))completionHandler NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);


/**Generates a signature allowing 3rd party server to authenticate the GKLocalPlayer
    Possible reasons for error:
    1. Communications problem
    2. Unauthenticated player
 */
- (void)fetchItemsForIdentityVerificationSignature:(void (^__nullable)(NSURL * __nullable publicKeyURL, NSData * __nullable signature, NSData * __nullable salt, uint64_t timestamp, NSError * __nullable error))completionHandler API_AVAILABLE(ios(13.5), macos(10.15.5), tvos(13.5), watchos(6.5));

@end

#if TARGET_OS_WATCH
@protocol GKLocalPlayerListener <GKChallengeListener, GKInviteEventListener, GKTurnBasedEventListener>
@end
#elif TARGET_OS_TV
@protocol GKLocalPlayerListener <GKChallengeListener, GKInviteEventListener, GKTurnBasedEventListener>
@end
#else
@protocol GKLocalPlayerListener <GKChallengeListener, GKInviteEventListener, GKTurnBasedEventListener, GKSavedGameListener>
@end
#endif

@interface GKLocalPlayer (GKLocalPlayerEvents)

/// A single listener may be registered once. Registering multiple times results in undefined behavior. The registered listener will receive callbacks for any selector it responds to.
- (void)registerListener:(id<GKLocalPlayerListener>)listener NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

- (void)unregisterListener:(id<GKLocalPlayerListener>)listener NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

- (void)unregisterAllListeners NS_AVAILABLE(10_10, 7_0) __WATCHOS_AVAILABLE(3_0);

@end

/// Notification will be posted whenever authentication status changes.
GK_EXTERN NSNotificationName GKPlayerAuthenticationDidChangeNotificationName NS_AVAILABLE(10_8, 4_1);

@interface GKLocalPlayer (Deprecated)

- (void)setDefaultLeaderboardCategoryID:(nullable NSString *)categoryID completionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 6_0, 7_0,"Use setDefaultLeaderboardIdentifier:completionHandler: instead") ;
- (void)loadDefaultLeaderboardCategoryIDWithCompletionHandler:(void(^__nullable)(NSString * __nullable categoryID, NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 6_0, 7_0,"Use loadDefaultLeaderboardIdentifierWithCompletionHandler: instead") ;
- (void)authenticateWithCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_8, 4_1, 6_0, "Set the authenticateHandler instead") ;

- (void)loadFriendPlayersWithCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable friendPlayers, NSError * __nullable error))completionHandler NS_DEPRECATED(10_10, 10_11, 8_0, 10_0);


/** Generates a signature allowing 3rd party server to authenticate the GKLocalPlayer
    Possible reasons for error:
    1. Communications problem
    2. Unauthenticated player
 */
- (void)generateIdentityVerificationSignatureWithCompletionHandler:(void (^__nullable)(NSURL * __nullable publicKeyUrl, NSData * __nullable signature, NSData * __nullable salt, uint64_t timestamp, NSError * __nullable error))completionHandler  API_DEPRECATED("API deprecated. Use fetchItemsForIdentityVerificationSignature: and the teamPlayerID value to verify a user identity.", ios(7.0, 13.5), tvos(9.0, 13.5), macosx(10.10, 10.15.5), watchos(3.0,6.5));
@end
NS_ASSUME_NONNULL_END

@interface GKLocalPlayer (Obsoleted)
/** This method is obsolete. It will never be invoked and its implementation does nothing***/
- (void)loadFriendsWithCompletionHandler:(void(^__nullable)(NSArray<NSString *> * __nullable friendIDs, NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "This is never invoked and its implementation does nothing, use loadRecentPlayersWithCompletionHandler: instead") ;

/** This property is obsolete. ***/
@property(nonatomic, readonly, nullable, retain) NSArray<NSString *> *friends NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, " This property is obsolete, Use loadFriendPlayersWithCompletionHandler: instead") ; // Array of player identifiers of friends for the local player. Not valid until loadFriendsWithCompletionHandler: has completed.
@end


#import <GameKit/GKLocalPlayer.h>

NS_ASSUME_NONNULL_BEGIN

@interface GKLocalPlayer (UI)

#if TARGET_OS_WATCH
#elif TARGET_OS_IPHONE
@property(nonatomic, nullable, copy) void(^authenticateHandler)(UIViewController * __nullable viewController, NSError * __nullable error) NS_AVAILABLE_IOS(6_0);
#else
@property(atomic, nullable, copy) void(^authenticateHandler)(NSViewController * __nullable viewController, NSError * __nullable error) NS_AVAILABLE_MAC(10_9);
#endif

@end

NS_ASSUME_NONNULL_END


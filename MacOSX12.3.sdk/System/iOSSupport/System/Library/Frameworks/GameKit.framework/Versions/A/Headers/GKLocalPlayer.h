//
//  GKLocalPlayer.h
//  Game Center
//
//  Copyright 2010-2022 Apple Inc. All rights reserved.
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
- (void)loadFriendsWithCompletionHandler:(void(^__nullable)(NSArray<NSString *> * __nullable friendIDs, NSError * __nullable error))completionHandler NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "This is never invoked and its implementation does nothing, use loadRecentPlayersWithCompletionHandler: instead")  NS_SWIFT_NAME(loadFriendsObsoleted(completionHandler:));;

/** This property is obsolete. ***/
@property(nonatomic, readonly, nullable, retain) NSArray<NSString *> *friends NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, " This property is obsolete, Use loadFriendPlayersWithCompletionHandler: instead") ; // Array of player identifiers of friends for the local player. Not valid until loadFriendsWithCompletionHandler: has completed.
@end

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSInteger, GKFriendsAuthorizationStatus) {
    // User has not yet made a choice with regards to this application.
    // A call to loadFriendsListWithHandler: in this state will result
    // into a prompt that might pause your application.
    GKFriendsAuthorizationStatusNotDetermined = 0,

    // This application is not authorized to use friend list data.  Due
    // to active restrictions on friend list data, the user cannot change
    // this status, and may not have personally denied authorization.
    // If you have previously collected data for this player's friend list,
    // You should delete the data collected on your end.
    GKFriendsAuthorizationStatusRestricted,

    // User has explicitly denied this application access to friend list data,
    // or global friend list access are disabled in Settings.
    GKFriendsAuthorizationStatusDenied,

    // User has authorized this application to access friend list data.
    // A call to loadFriends: will return the player's
    // friend list via a completion block
    GKFriendsAuthorizationStatusAuthorized,
}API_AVAILABLE(ios(14.5), macos(11.3), tvos(14.5), watchos(7.3));

@interface GKLocalPlayer (FriendsList)

/*
 *  loadFriendsAuthorizationStatus:
 *
 *  Discussion:
 *      Calling this will asynchronously load the current friend list authorization status
 *      of calling application.
 *      There may be an server call involve so there could be some slight delay
 *      in getting the authorization status via handler block.
 *      Calls handler when finished. Error will be nil on success.
 *
 *      Possible reasons for error:
 *          - Communication error with server.
 *          - NSGKFriendListUsageDescription missing from your Info.plist
 *          - User is not online
 *          - Unauthenticated player
 */
- (void)loadFriendsAuthorizationStatus:(void(^)(GKFriendsAuthorizationStatus authorizationStatus, NSError * __nullable error))completionHandler API_AVAILABLE(ios(14.5), macos(11.3), tvos(14.5), watchos(7.3));

/*
 *  loadFriends:
 *
 *  Discussion:
 *      Calling this method will asynchronously load the player Game Center's
 *      friend list scoped to the calling application.
 *      Calls handler when finished.
 *
 *      When -loadFriendsAuthorizationStatus == GKFriendsAuthorizationStatusNotDetermined or
 *      GKFriendsAuthorizationStatusRemoved, calling this method will trigger a
 *      prompt to request friend list authorization from the user.
 *
 *      When -loadFriendsAuthorizationStatus == GKFriendsAuthorizationStatusAuthorized,
 *      This method will return an array of GKPlayers which have agreed to share their
 *      friend list with the calling application based on the same bundleID.
 *
 *      The NSGKFriendListUsageDescription key must be specified in your
 *      Info.plist; otherwise, GKErrorFriendListUsageDescriptionMissing will be returned,
 *      as your app will be assumed not to support friend list.
 
 *      Possible reasons for error:
 *          - Communication error with server.
 *          - AuthorizationStatus != GKFriendsAuthorizationStatusAuthorized
 *          - NSGKFriendListUsageDescription missing from your Info.plist
 *          - User is not online
 *          - Unauthenticated player
 */
- (void)loadFriends:(void(^)(NSArray<GKPlayer *> * __nullable friends, NSError * __nullable error))completionHandler API_AVAILABLE(ios(14.5), macos(11.3), tvos(14.5), watchos(7.3));

/*
 *  loadFriendsWithIdentifiers:completionHandler:
 *
 *  Discussion:
 *      Calling this method will asynchronously return a list of GKPlayers to the provided
 *      scoped identifiers (gamePlayerID or teamPlayerID) that you can use to interact with
 *      GameKit framework.
 *      Calls handler when finished.
 *
 *      When -loadFriendsAuthorizationStatus == GKFriendsAuthorizationStatusNotDetermined or
 *      GKFriendsAuthorizationStatusRemoved, calling this method will trigger a
 *      prompt to request friend list authorization from the user.
 *
 *      This method accepts gamePlayerID or teamPlayerID, and if the identifier
 *      is valid, we will return a GKPlayer object correspond to that identifier.
 *
 *      No GKPlayer object will be returned for invalid identifiers. If all supplied
 *      identifiers are invalid, and empty array will be returned.
 *
 *      If a player's friend revoke the friend list authorization for your application,
 *      we will no longer return the GKPlayer object and you should delete the data
 *      you've collected for the player with gamePlayerID or teamPlayerID on your end.
 *
 *      Possible reasons for error:
 *          - Communication error with server.
 *          - AuthorizationStatus != GKFriendsAuthorizationStatusAuthorized
 *          - NSGKFriendListUsageDescription missing from your Info.plist
 *          - Unauthenticated player
 *          - User is not online
 */
- (void)loadFriendsWithIdentifiers:(NSArray<NSString *> *)identifiers completionHandler:(void(^)(NSArray<GKPlayer *> * __nullable friends, NSError * __nullable error))completionHandler API_AVAILABLE(ios(14.5), macos(11.3), tvos(14.5), watchos(7.3)) NS_SWIFT_NAME(loadFriends(identifiedBy:completionHandler:));
@end
NS_ASSUME_NONNULL_END


#import <GameKit/GKLocalPlayer.h>

NS_ASSUME_NONNULL_BEGIN

@interface GKLocalPlayer (UI)

#if TARGET_OS_WATCH
#elif TARGET_OS_IPHONE
@property(nonatomic, nullable, copy) void(^authenticateHandler)(UIViewController * __nullable viewController, NSError * __nullable error) NS_AVAILABLE_IOS(6_0);
#else
@property(atomic, nullable, copy) void(^authenticateHandler)(NSViewController * __nullable viewController, NSError * __nullable error) NS_AVAILABLE_MAC(10_9);
#endif

#if !TARGET_OS_WATCH && !TARGET_OS_TV
/// observable property that becomes true when the friend request view controller is displayed.  It becomes false when it is dismissed
@property (nonatomic, readonly) BOOL isPresentingFriendRequestViewController API_AVAILABLE(ios(15.0), macos(12.0)) API_UNAVAILABLE(watchos, tvos);

#if TARGET_OS_IOS && !TARGET_OS_MACCATALYST
/**
 *  presentFriendRequestCreatorFromViewController:
 *
 *  Discussion:
 *      iOS only. When invoked, a Messages sheet will be presented on the viewController passed in, using the existing flow of presentation on behalf of an application.
 *      If an error is returned, control are returned directly to the application, without presentation.
 *
 *      Possible reasons for error:
 *          - The local player user account is not allowed to add friends
 *            - The device is not allowing outgoing traffic at the time of the operation
*/
- (BOOL)presentFriendRequestCreatorFromViewController:(UIViewController *)viewController error:(NSError **)error API_AVAILABLE(ios(15.0))  API_UNAVAILABLE(macos, watchos, tvos);

#elif TARGET_OS_OSX
/**
 *  presentFriendRequestCreatorFromWindow:
 *
 *  Discussion:
 *      MacOS only. When invoked, if no error is encountered, the caller application is backgrounded and the 'Messages' application is launched/foregrounded, with a formatted friend request message.
 *      If an error occurs, controls are returned to the caller application, with an error describing the error.
 *
 *      Possible reasons for error:
 *          - The local player user account is not allowed to add friends
 *            - The device is not allowing outgoing traffic at the time of the operation
*/
- (BOOL)presentFriendRequestCreatorFromWindow:(nullable NSWindow *)window error:(NSError **)error API_AVAILABLE(macos(12.0))  API_UNAVAILABLE(ios, watchos, tvos);
#endif

#endif
@end

NS_ASSUME_NONNULL_END


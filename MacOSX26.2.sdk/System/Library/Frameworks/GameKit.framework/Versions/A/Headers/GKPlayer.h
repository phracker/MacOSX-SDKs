// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>
#import <GameKit/GKBasePlayer.h>
#import <GameKit/GKDefines.h>
#import <GameKit/GKError.h>

@class GKPlayerInternal;
@class GKGame;
@class GKLocalPlayer;
@class UIImage;

/// Deprecated methods that previously returned player IDs will return GKPlayerIDNoLongerAvailable instead.
GK_EXTERN NSString * _Nonnull const GKPlayerIDNoLongerAvailable API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0)) API_UNAVAILABLE(watchos);

API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0))
@interface GKPlayer : GKBasePlayer

///  This convenience method checks if the gamePlayerID and the teamPlayerID (scopedIDs) are persistent or unique for the instantiation of this app.
- (BOOL)scopedIDsArePersistent API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

///  This is the player's unique and persistent ID that is scoped to this application.
@property(NS_NONATOMIC_IOSONLY, readonly, nonnull, retain) NSString *gamePlayerID API_AVAILABLE(ios(12.4), macos(10.14.6), tvos(12.4)) API_UNAVAILABLE(watchos);

///  This is the player's unique and persistent ID that is scoped to the Apple Store Connect Team identifier of this application.
@property(NS_NONATOMIC_IOSONLY, readonly, nonnull, retain) NSString *teamPlayerID API_AVAILABLE(ios(12.4), macos(10.14.6), tvos(12.4)) API_UNAVAILABLE(watchos);

/// This is player's alias to be displayed. The display name may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, nonnull, NS_NONATOMIC_IOSONLY)          NSString    *displayName API_AVAILABLE(ios(6.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));

/// The alias property contains the player's nickname. When you need to display the name to the user, consider using displayName instead. The nickname is unique but not invariant: the player may change their nickname. The nickname may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, copy, nonnull, NS_NONATOMIC_IOSONLY)    NSString    *alias;

+ (nonnull instancetype)anonymousGuestPlayerWithIdentifier:(nonnull NSString *)guestIdentifier API_AVAILABLE(ios(9.0), macos(10.11), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
@property(readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *guestIdentifier API_AVAILABLE(ios(9.0), macos(10.11), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);

// This convenience method checks if you can invite the player to multiplayer game.
@property(readonly, NS_NONATOMIC_IOSONLY) BOOL isInvitable API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0)) API_UNAVAILABLE(watchos);
@end

#if !TARGET_OS_WATCH

@interface GKPlayer (UI)

// Available photo sizes.  Actual pixel dimensions will vary on different devices.
typedef NS_ENUM(NSInteger, GKPhotoSize) {
    GKPhotoSizeSmall = 0,
    GKPhotoSizeNormal,
} API_AVAILABLE(ios(5.0), macos(10.8), tvos(9.0), visionos(1.0));

#if TARGET_OS_IPHONE
/// Asynchronously load the player's photo. Error will be nil on success.
/// Possible reasons for error:
/// 1. Communications failure
- (void)loadPhotoForSize:(GKPhotoSize)size withCompletionHandler:(void(^__nullable)(UIImage * __nullable photo, NSError * __nullable error))completionHandler API_AVAILABLE(ios(5.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));
#else
/// Asynchronously load the player's photo. Error will be nil on success.
/// Possible reasons for error:
/// 1. Communications failure
- (void)loadPhotoForSize:(GKPhotoSize)size withCompletionHandler:(void(^__nullable)(NSImage * __nullable photo, NSError * __nullable error))completionHandler API_AVAILABLE(ios(5.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));
#endif

@end

#endif

/// Notification will be posted whenever the player details changes. The object of the notification will be the player.
GK_EXTERN_WEAK NSNotificationName __nonnull GKPlayerDidChangeNotificationName API_AVAILABLE(ios(4.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));

@interface GKPlayer (Deprecated)

@property(readonly, NS_NONATOMIC_IOSONLY)          BOOL         isFriend API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLocalPlayer/loadFriendPlayers(completionHandler:)`` instead.", ios(4.1,8.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos);    // True if this player is a friend of the local player
@property(readonly, nonnull, retain, NS_NONATOMIC_IOSONLY)  NSString *playerID API_DEPRECATED("Use ``GKPlayer/gamePlayerID`` or ``GKPlayer/teamPlayerID`` instead.", ios(4.1,13.0), tvos(9.0,13.0), macos(10.8,10.15));

/// Load the Game Center players for the playerIDs provided. Error will be nil on success.
/// Possible reasons for error:
/// 1. Unauthenticated local player
/// 2. Communications failure
/// 3. Invalid player identifier
+ (void)loadPlayersForIdentifiers:(nonnull NSArray<NSString *> *)identifiers withCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable players, NSError * __nullable error))completionHandler NS_SWIFT_DISABLE_ASYNC API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLocalPlayer/loadFriends(identifiedBy:completionHandler:)`` instead.", ios(4.1,14.5), tvos(9.0,14.5), macos(10.8,11.3), watchos(3.0,7.4));
@end

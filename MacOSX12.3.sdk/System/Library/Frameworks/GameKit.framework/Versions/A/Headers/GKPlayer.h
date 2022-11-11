//
//  GKPlayer.h
//  Game Center
//
//  Copyright 2010-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKBasePlayer.h>
#import <GameKit/GKDefines.h>
#import <GameKit/GKError.h>

@class GKPlayerInternal;
@class GKGame;
@class GKLocalPlayer;
@class UIImage;

/// Deprecated methods that previously returned player IDs will return GKPlayerIDNoLongerAvailable instead.
extern NSString * _Nonnull const GKPlayerIDNoLongerAvailable API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0)) API_UNAVAILABLE(watchos);

NS_CLASS_AVAILABLE(10_8, 4_1) __WATCHOS_AVAILABLE(3_0)

@interface GKPlayer : GKBasePlayer

///  This convenience method checks if the gamePlayerID and the teamPlayerID (scopedIDs) are persistent or unique for the instantiation of this app.
- (BOOL)scopedIDsArePersistent API_AVAILABLE(ios(13.0), macos(10.15), tvos(13.0)) API_UNAVAILABLE(watchos);

///  This is the player's unique and persistent ID that is scoped to this application.
@property(NS_NONATOMIC_IOSONLY, readonly, nonnull, retain) NSString *gamePlayerID API_AVAILABLE(ios(12.4), macos(10.14.6), tvos(12.4)) API_UNAVAILABLE(watchos);

///  This is the player's unique and persistent ID that is scoped to the Apple Store Connect Team identifier of this application.
@property(NS_NONATOMIC_IOSONLY, readonly, nonnull, retain) NSString *teamPlayerID API_AVAILABLE(ios(12.4), macos(10.14.6), tvos(12.4)) API_UNAVAILABLE(watchos);

/// This is player's alias to be displayed. The display name may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, nonnull, NS_NONATOMIC_IOSONLY)          NSString    *displayName NS_AVAILABLE(10_8, 6_0) __WATCHOS_AVAILABLE(3_0);

/// The alias property contains the player's nickname. When you need to display the name to the user, consider using displayName instead. The nickname is unique but not invariant: the player may change their nickname. The nickname may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, copy, nonnull, NS_NONATOMIC_IOSONLY)    NSString    *alias;

+ (nonnull instancetype)anonymousGuestPlayerWithIdentifier:(nonnull NSString *)guestIdentifier NS_AVAILABLE(10_11, 9_0) __WATCHOS_PROHIBITED;
@property(readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *guestIdentifier NS_AVAILABLE(10_11, 9_0) __WATCHOS_PROHIBITED;

// This convenience method checks if you can invite the player to multiplayer game.
@property(readonly, NS_NONATOMIC_IOSONLY) BOOL isInvitable API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0)) __WATCHOS_PROHIBITED;
@end

#import <GameKit/GKPlayer.h>

@interface GKPlayer (UI)

// Available photo sizes.  Actual pixel dimensions will vary on different devices.
typedef NS_ENUM(NSInteger, GKPhotoSize) {
    GKPhotoSizeSmall = 0,
    GKPhotoSizeNormal,
};

// Asynchronously load the player's photo. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
#if TARGET_OS_IPHONE
- (void)loadPhotoForSize:(GKPhotoSize)size withCompletionHandler:(void(^__nullable)(UIImage * __nullable photo, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 5_0);
#else
- (void)loadPhotoForSize:(GKPhotoSize)size withCompletionHandler:(void(^__nullable)(NSImage * __nullable photo, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 5_0);
#endif

@end


/// Notification will be posted whenever the player details changes. The object of the notification will be the player.
GK_EXTERN_WEAK NSNotificationName __nonnull GKPlayerDidChangeNotificationName;

@interface GKPlayer (Deprecated)

@property(readonly, NS_NONATOMIC_IOSONLY)          BOOL         isFriend NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use -[GKLocalPlayer loadFriendPlayers...]") ;    // True if this player is a friend of the local player
@property(readonly, nonnull, retain, NS_NONATOMIC_IOSONLY)  NSString *playerID API_DEPRECATED( "use the teamPlayerID property to identify a player",ios(4.1,13.0),tvos(9.0,13.0),macosx(10.8,10.15));

/// Load the Game Center players for the playerIDs provided. Error will be nil on success.
/// Possible reasons for error:
/// 1. Unauthenticated local player
/// 2. Communications failure
/// 3. Invalid player identifier
+ (void)loadPlayersForIdentifiers:(nonnull NSArray<NSString *> *)identifiers withCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable players, NSError * __nullable error))completionHandler NS_SWIFT_DISABLE_ASYNC API_DEPRECATED( "use GKLocalPlayer.loadFriendsWithIdentifiers to load a friend's GKPlayer object.",ios(4.1,14.5),tvos(9.0,14.5),macosx(10.8,11.3), watchos(3.0,7.4));
@end

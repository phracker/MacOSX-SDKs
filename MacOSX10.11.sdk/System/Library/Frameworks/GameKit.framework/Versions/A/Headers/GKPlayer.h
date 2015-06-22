//
//  GKPlayer.h
//  Game Center
//
//  Copyright 2010-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>
#import <GameKit/GKError.h>

@class GKPlayerInternal;
@class GKGame;
@class GKLocalPlayer;

NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKPlayer : NSObject

// Load the Game Center players for the playerIDs provided. Error will be nil on success.
// Possible reasons for error:
// 1. Unauthenticated local player
// 2. Communications failure
// 3. Invalid player identifier
+ (void)loadPlayersForIdentifiers:(nonnull NSArray<NSString *> *)identifiers withCompletionHandler:(void(^__nullable)(NSArray<GKPlayer *> * __nullable players, NSError * __nullable error))completionHandler;

@property(readonly, nullable, retain, NS_NONATOMIC_IOSONLY)  NSString    *playerID;

// This player's full name as displayed in the Game Center in-game UI. Use this when you need to display the player's name. The display name may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, nullable, NS_NONATOMIC_IOSONLY)          NSString    *displayName NS_AVAILABLE(10_8, 6_0);

// The alias property contains the player's nickname. When you need to display the name to the user, consider using displayName instead. The nickname is unique but not invariant: the player may change their nickname. The nickname may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, copy, nullable, NS_NONATOMIC_IOSONLY)    NSString    *alias;

+ (nonnull instancetype)anonymousGuestPlayerWithIdentifier:(nonnull NSString *)guestIdentifier NS_AVAILABLE(10_11, 9_0);
@property(readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *guestIdentifier NS_AVAILABLE(10_11, 9_0);

@end


@interface GKPlayer (UI)

// Available photo sizes.  Actual pixel dimensions will vary on different devices.
enum {
    GKPhotoSizeSmall = 0,
    GKPhotoSizeNormal,
};
typedef NSInteger GKPhotoSize;

// Asynchronously load the player's photo. Error will be nil on success.
// Possible reasons for error:
// 1. Communications failure
#if TARGET_OS_IPHONE
- (void)loadPhotoForSize:(GKPhotoSize)size withCompletionHandler:(void(^__nullable)(UIImage * __nullable photo, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 5_0);
#else
- (void)loadPhotoForSize:(GKPhotoSize)size withCompletionHandler:(void(^__nullable)(NSImage * __nullable photo, NSError * __nullable error))completionHandler NS_AVAILABLE(10_8, 5_0);
#endif

@end


// Notification will be posted whenever the player details changes. The object of the notification will be the player.
GK_EXTERN_WEAK NSString * __nonnull GKPlayerDidChangeNotificationName;

@interface GKPlayer (Deprecated)

@property(readonly, NS_NONATOMIC_IOSONLY)          BOOL         isFriend NS_DEPRECATED(10_8, 10_10, 4_1, 8_0, "use -[GKLocalPlayer loadFriendPlayers...]") ;    // True if this player is a friend of the local player

@end

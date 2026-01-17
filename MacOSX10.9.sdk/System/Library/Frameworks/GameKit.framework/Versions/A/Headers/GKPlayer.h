//
//  GKPlayer.h
//  GameKit
//
//  Copyright 2010 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>
#import <GameKit/GKError.h>

#if TARGET_OS_IPHONE
@class UIImage;
#else
@class NSImage;
#endif

NS_CLASS_AVAILABLE(10_8, 4_1)
GK_EXTERN_CLASS @interface GKPlayer : NSObject
{
@private
	id _internal;
}

// Load the players for the identifiers provided. Error will be nil on success.
// Possible reasons for error:
// 1. Unauthenticated local player
// 2. Communications failure
// 3. Invalid player identifier
+ (void)loadPlayersForIdentifiers:(NSArray *)identifiers withCompletionHandler:(void(^)(NSArray *players, NSError *error))completionHandler;

@property(readonly, retain, NS_NONATOMIC_IOSONLY)  NSString    *playerID;     // Invariant player identifier.
@property(readonly, NS_NONATOMIC_IOSONLY)          BOOL         isFriend;     // True if this player is a friend of the local player

// This player's full name as displayed in the Game Center in-game UI. Use this when you need to display the player's name. The display name may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, NS_NONATOMIC_IOSONLY)          NSString    *displayName __OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_6_0);

// The alias property contains the player's nickname. When you need to display the name to the user, consider using displayName instead. The nickname is unique but not invariant: the player may change their nickname. The nickname may be very long, so be sure to use appropriate string truncation API when drawing.
@property(readonly, copy, NS_NONATOMIC_IOSONLY)    NSString    *alias;

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
- (void)loadPhotoForSize:(GKPhotoSize)size withCompletionHandler:(void(^)(UIImage *photo, NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
#else
- (void)loadPhotoForSize:(GKPhotoSize)size withCompletionHandler:(void(^)(NSImage *photo, NSError *error))completionHandler __OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_NA);
#endif

@end

// Notification will be posted whenever the player details changes. The object of the notification will be the player.
extern NSString *GKPlayerDidChangeNotificationName;


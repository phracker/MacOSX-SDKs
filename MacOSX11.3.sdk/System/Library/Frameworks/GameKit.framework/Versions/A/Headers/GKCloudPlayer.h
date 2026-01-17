//
//  GKCloudPlayer.h
//  Game Center
//
//  Copyright 2016-2021 Apple Inc. All rights reserved.
//

#import <GameKit/GKBasePlayer.h>
NS_ASSUME_NONNULL_BEGIN

API_DEPRECATED("GKGameSession is deprecated. Use GKPlayer for both real-time and turn-based matchmaking APIs.", ios(10.0, 12.0), tvos(10.0, 12.0), macosx(10.12, 10.14)) API_UNAVAILABLE(watchos)
@interface GKCloudPlayer : GKBasePlayer
#if !__OBJC2__
{
    NSString *_identifier;
    NSString *_name;
}
#endif

/// Retrieve a player instance representing the active iCloud account for a given iCloud container. Returns nil and an error if the user is not signed in to iCloud or the container is invalid.
+ (void)getCurrentSignedInPlayerForContainer:(NSString * __nullable)containerName completionHandler:(void(^)(GKCloudPlayer *__nullable player, NSError * __nullable error))handler;

@end
NS_ASSUME_NONNULL_END

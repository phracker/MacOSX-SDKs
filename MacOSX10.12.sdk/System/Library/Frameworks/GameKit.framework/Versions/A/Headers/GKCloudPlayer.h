//
//  GKCloudPlayer.h
//  Game Center
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import <GameKit/GKBasePlayer.h>
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED

@interface GKCloudPlayer : GKBasePlayer
#if !__OBJC2__
{
    NSString *_identifier;
    NSString *_name;
}
#endif

// Retrieve a player instance representing the active iCloud account for a given iCloud container. Returns nil and an error if the user is not signed in to iCloud or the container is invalid.
+ (void)getCurrentSignedInPlayerForContainer:(NSString * __nullable)containerName completionHandler:(void(^)(GKCloudPlayer *__nullable player, NSError * __nullable error))handler;

@end
NS_ASSUME_NONNULL_END

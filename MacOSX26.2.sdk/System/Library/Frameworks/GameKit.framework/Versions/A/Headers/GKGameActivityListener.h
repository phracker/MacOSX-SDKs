// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>

#if !TARGET_OS_WATCH

#import <Foundation/Foundation.h>

@class GKGameActivity, GKPlayer;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
@protocol GKGameActivityListener

@optional

/**
 Called when a player intends to play for a specific game activity.
 A completion handler block is provided to indicate whether the activity was successfully handled.
 */
- (void)player:(GKPlayer *)player wantsToPlayGameActivity:(GKGameActivity *)activity completionHandler:(void (^)(BOOL handled))completionHandler;

@end

NS_ASSUME_NONNULL_END

#endif // #if !TARGET_OS_WATCH

// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>

#if !TARGET_OS_WATCH

#import <Foundation/Foundation.h>
#import <TargetConditionals.h>

/// Play Style of the game activity. It can be either Asynchronous or Synchronous.
typedef NS_ENUM(NSInteger, GKGameActivityPlayStyle) {
    GKGameActivityPlayStyleUnspecified = 0,
    GKGameActivityPlayStyleSynchronous = 1,
    GKGameActivityPlayStyleAsynchronous = 2
} API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos);

#endif // #if !TARGET_OS_WATCH

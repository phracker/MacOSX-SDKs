//
//  GKGameSessionEventListener.h
//  Game Center
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import "GKGameSession.h"
NS_ASSUME_NONNULL_BEGIN

@protocol GKGameSessionEventListener <NSObject>
@optional
- (void)session:(GKGameSession *)session didAddPlayer:(GKCloudPlayer *)player NS_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED;
- (void)session:(GKGameSession *)session didRemovePlayer:(GKCloudPlayer *)player NS_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED;
- (void)session:(GKGameSession *)session player:(GKCloudPlayer *)player didChangeConnectionState:(GKConnectionState)newState NS_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED;
- (void)session:(GKGameSession *)session player:(GKCloudPlayer *)player didSaveData:(NSData *)data NS_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED;
- (void)session:(GKGameSession *)session didReceiveData:(NSData *)data fromPlayer:(GKCloudPlayer *)player NS_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED;
- (void)session:(GKGameSession *)session didReceiveMessage:(NSString *)message withData:(NSData *)data fromPlayer:(GKCloudPlayer *)player NS_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED;

@end

@interface GKGameSession (GKGameSessionEventListener)
+ (void)addEventListener:(NSObject<GKGameSessionEventListener> *)listener NS_SWIFT_NAME(add(listener:)) NS_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED;
+ (void)removeEventListener:(NSObject<GKGameSessionEventListener> *)listener NS_SWIFT_NAME(remove(listener:)) NS_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED;
@end

NS_ASSUME_NONNULL_END


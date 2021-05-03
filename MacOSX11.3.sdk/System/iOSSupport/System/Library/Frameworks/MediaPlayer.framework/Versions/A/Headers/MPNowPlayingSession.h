//
//  MPNowPlayingSession.h
//  MediaPlayer
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPNowPlayingInfoCenter;
@class MPRemoteCommandCenter;
@class AVPlayer;
@protocol MPNowPlayingSessionDelegate;

MP_API(tvos(14.0)) MP_UNAVAILABLE(ios, macos, watchos)
@interface MPNowPlayingSession : NSObject

/// Creates a session associated with a given AVPlayer instance. This will assert if players is nil or empty. 
- (instancetype)initWithPlayers:(NSArray<AVPlayer *> *)players;

MP_INIT_UNAVAILABLE

/// AVPlayer instances associated with this session.
@property (nonatomic, strong, readonly) NSArray<AVPlayer *> *players;

@property (nonatomic, weak, nullable) id<MPNowPlayingSessionDelegate> delegate;

/// The now playing info center that is associated with this session.
@property (nonatomic, strong, readonly) MPNowPlayingInfoCenter *nowPlayingInfoCenter;

/// The remote command center that is associated with this session.
@property (nonatomic, strong, readonly) MPRemoteCommandCenter *remoteCommandCenter;

/// Returns a Boolean value indicating whether this session can become the App's active now playing session.
@property (nonatomic, readonly) BOOL canBecomeActive;

/// Returns a Boolean value indicating whether this session is the App's active now playing session.
@property (nonatomic, readonly, getter=isActive) BOOL active;

/// Asks the system to make this session the active now playing sessin for the App.
- (void)becomeActiveIfPossibleWithCompletion:(void (^ _Nullable)(BOOL isActive))completion;

/// Add AVPlayer instance to this session.
- (void)addPlayer:(AVPlayer *)player;

/// Remove AVPlayer instance from this session.
- (void)removePlayer:(AVPlayer *)player;

@end


MP_API(tvos(14.0)) MP_UNAVAILABLE(ios, macos, watchos)
@protocol MPNowPlayingSessionDelegate <NSObject>

@optional
/// Tells the delegate that the session has changed its active status.
- (void)nowPlayingSessionDidChangeActive:(MPNowPlayingSession *)nowPlayingSession;

/// Tells the delegate that the session has changed its can become active status.
- (void)nowPlayingSessionDidChangeCanBecomeActive:(MPNowPlayingSession *)nowPlayingSession;

@end

NS_ASSUME_NONNULL_END

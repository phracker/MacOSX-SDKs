//
//  MPNowPlayingSession.h
//  MediaPlayer
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTimeRange.h>

NS_ASSUME_NONNULL_BEGIN

@class MPNowPlayingInfoCenter;
@class MPRemoteCommandCenter;
@class AVPlayer;
@protocol MPNowPlayingSessionDelegate;

MP_UNAVAILABLE_BEGIN(watchos, macos)

MP_API(ios(16.0), tvos(16.0))
@interface MPAdTimeRange : NSObject <NSCopying>

/// Represents a time range where an ad break exists in the current player item.
/// This value must be in bounds of the duration of the current player item.
@property (nonatomic, assign) CMTimeRange timeRange;

MP_INIT_UNAVAILABLE

- (instancetype)initWithTimeRange:(CMTimeRange)timeRange NS_SWIFT_NAME(init(_:));

@end

MP_API(tvos(14.0), ios(16.0))
@interface MPNowPlayingSession : NSObject

/// Creates a session associated with a given AVPlayer instance. This will assert if players is nil or empty. 
- (instancetype)initWithPlayers:(NSArray<AVPlayer *> *)players;

MP_INIT_UNAVAILABLE

/// AVPlayer instances associated with this session.
@property (nonatomic, strong, readonly) NSArray<AVPlayer *> *players;

@property (nonatomic, weak, nullable) id<MPNowPlayingSessionDelegate> delegate;

/// When YES, now playing info will be automatically published, and nowPlayingInfoCenter must not be used.
///  Now playing info keys to be incorporated by automatic publishing can be set on the AVPlayerItem's nowPlayingInfo property.
@property (nonatomic, assign) BOOL automaticallyPublishesNowPlayingInfo MP_API(ios(16.0), tvos(16.0));

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


MP_API(tvos(14.0), ios(16.0))
@protocol MPNowPlayingSessionDelegate <NSObject>

@optional
/// Tells the delegate that the session has changed its active status.
- (void)nowPlayingSessionDidChangeActive:(MPNowPlayingSession *)nowPlayingSession;

/// Tells the delegate that the session has changed its can become active status.
- (void)nowPlayingSessionDidChangeCanBecomeActive:(MPNowPlayingSession *)nowPlayingSession;

@end

MP_UNAVAILABLE_END

NS_ASSUME_NONNULL_END

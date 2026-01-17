//
//  MPMediaPlayback.h
//  MediaPlayer
//
//  Copyright 2009-2010 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

MP_API(ios(3.0), tvos(14.0))
API_UNAVAILABLE(watchos, macos)
@protocol MPMediaPlayback

// Prepares the current queue for playback, interrupting any active (non-mixible) audio sessions.
// Automatically invoked when -play is called if the player is not already prepared.
- (void)prepareToPlay;

// Returns YES if prepared for playback.
@property(nonatomic, readonly) BOOL isPreparedToPlay;

// Plays items from the current queue, resuming paused playback if possible.
- (void)play;

// Pauses playback if playing.
- (void)pause;

// Ends playback. Calling -play again will start from the beginnning of the queue.
- (void)stop;

// The current playback time of the now playing item in seconds.
@property(nonatomic) NSTimeInterval currentPlaybackTime;

// The current playback rate of the now playing item. Default is 1.0 (normal speed).
// Pausing will set the rate to 0.0. Setting the rate to non-zero implies playing.
@property(nonatomic) float currentPlaybackRate;

// The seeking rate will increase the longer scanning is active.
- (void)beginSeekingForward;
- (void)beginSeekingBackward;
- (void)endSeeking;

@end

// Posted when the prepared state changes of an object conforming to the MPMediaPlayback protocol changes.
// This supersedes MPMoviePlayerContentPreloadDidFinishNotification.
MP_EXTERN NSString * const MPMediaPlaybackIsPreparedToPlayDidChangeNotification MP_DEPRECATED("Use AVPlayerViewController in AVKit.", ios(3.2, 9.0));

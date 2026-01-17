//
//  MPPlayableContentDelegate.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPPlayableContentManager, MPContentItem, MPPlayableContentManagerContext;

/// The MPPlayableContentDelegate is a protocol that allows for external media
/// players to send playback commands to an application. For instance,
/// the user could browse the application's media content (provided by the
/// MPPlayableContentDataSource) and selects a content item to play. If the media
/// player decides that it wants to play the item, it will ask the application's
/// content delegate to initiate playback.
MP_API(ios(7.1))
MP_PROHIBITED(tvos, macos, watchos)
@protocol MPPlayableContentDelegate <NSObject>
@optional

/// This method is called when a media player interface wants to play a requested
/// content item. The application should call the completion handler with an
/// appropriate error if there was an error beginning playback for the item.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager initiatePlaybackOfContentItemAtIndexPath:(NSIndexPath *)indexPath completionHandler:(void(^)(NSError * __nullable))completionHandler
    MP_API(ios(7.1))
    MP_PROHIBITED(tvos, macos, watchos);


/// This method is called when a media player interface wants the now playing
/// app to setup a playback queue for later playback. The application should
/// load content into its play queue but not start playback until a Play command is
/// received or if the playable content manager requests to play something else.
/// The app should call the provided completion handler once it is ready to play
/// something.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager initializePlaybackQueueWithCompletionHandler:(void(^)(NSError * __nullable))completionHandler
    MP_DEPRECATED("Use Intents framework for initiating playback queues.", ios(9.0, 9.3))
    MP_PROHIBITED(tvos, macos, watchos);

/// This method is called when a media player interface wants the now playing
/// app to setup a playback queue for later playback. The application should
/// load content into its play queue based on the provided content items and
/// prepare it for playback, but not start playback until a Play command is
/// received or if the playable content manager requests to play something else.
/// A nil contentItems array means that the app should prepare its queue with
/// anything it deems appropriate.
/// The app should call the provided completion handler once it is ready to play
/// something.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager initializePlaybackQueueWithContentItems:(nullable NSArray *)contentItems completionHandler:(void(^)(NSError * __nullable))completionHandler
    MP_DEPRECATED("Use Intents framework for initiating playback queues.", ios(9.3, 12.0))
    MP_PROHIBITED(tvos, macos, watchos);

/// This method is called when the content server notifies the manager that the current context has changed.
- (void)playableContentManager:(MPPlayableContentManager *)contentManager didUpdateContext:(MPPlayableContentManagerContext *)context
    MP_API(ios(8.4))
    MP_PROHIBITED(tvos, macos, watchos);

@end

NS_ASSUME_NONNULL_END

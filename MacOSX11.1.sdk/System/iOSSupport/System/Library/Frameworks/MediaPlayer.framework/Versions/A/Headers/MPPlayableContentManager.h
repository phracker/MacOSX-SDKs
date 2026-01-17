//
//  MPPlayableContentManager.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPPlayableContentDataSource.h>
#import <MediaPlayer/MPPlayableContentDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/// MPPlayableContentManager is a class that manages the interactions between a
/// media application and an external media player interface. The application
/// provides the content manager with a data source, which allows the media player
/// to browse the media content offered by the application, as well as a delegate,
/// which allows the media player to relay non-media remote playback commands to the application.
MP_DEPRECATED("Use CarPlay framework", ios(7.1, 14.0))
MP_UNAVAILABLE(tvos, macos, watchos)
@interface MPPlayableContentManager : NSObject

@property (nonatomic, weak, nullable) id<MPPlayableContentDataSource> dataSource;
@property (nonatomic, weak, nullable) id<MPPlayableContentDelegate>   delegate;
@property (nonatomic, readonly) MPPlayableContentManagerContext *context MP_DEPRECATED("Use CarPlay framework", ios(8.4, 14.0));

/// Tells the content manager which MPContentItems are currently playing based on their identifiers.
@property (nonatomic, copy) NSArray<NSString *> *nowPlayingIdentifiers MP_DEPRECATED("Use CarPlay framework", ios(10.0, 14.0));

/// Returns the application's instance of the content manager.
+ (instancetype)sharedContentManager;

/// Tells the content manager that the data source has changed and that we need to
/// reload data from the data source.
- (void)reloadData;

/// Used to begin a synchronized update to multiple MPContentItems at once.
- (void)beginUpdates;

/// Ends a synchronized update.
- (void)endUpdates;

@end

NS_ASSUME_NONNULL_END

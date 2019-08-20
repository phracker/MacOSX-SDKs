//
//  MediaPlayer.h
//  MediaPlayer
//
//  Copyright 2008-2011 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <TargetConditionals.h>

#if TARGET_OS_IPHONE
#import <MediaPlayer/MPMediaItemCollection.h>
#import <MediaPlayer/MPMediaLibrary.h>
#import <MediaPlayer/MPMediaPickerController.h>
#import <MediaPlayer/MPMediaPlaylist.h>
#import <MediaPlayer/MPMediaQuery.h>
#import <MediaPlayer/MPMediaQuerySection.h>
#import <MediaPlayer/MPMoviePlayerController.h>
#import <MediaPlayer/MPMoviePlayerViewController.h>
#import <MediaPlayer/MPMusicPlayerApplicationController.h>
#import <MediaPlayer/MPMusicPlayerController.h>
#import <MediaPlayer/MPMusicPlayerQueueDescriptor.h>
#import <MediaPlayer/MPPlayableContentDataSource.h>
#import <MediaPlayer/MPPlayableContentDelegate.h>
#import <MediaPlayer/MPPlayableContentManager.h>
#import <MediaPlayer/MPPlayableContentManagerContext.h>
#import <MediaPlayer/MPVolumeSettings.h>
#import <MediaPlayer/MPVolumeView.h>
#import <MediaPlayer/NSUserActivity+MediaPlayerAdditions.h>
#endif

#import <MediaPlayer/AVFoundation+MPNowPlayingInfoLanguageOptionAdditions.h>
#import <MediaPlayer/MPContentItem.h>
#import <MediaPlayer/MPError.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPNowPlayingInfoCenter.h>
#import <MediaPlayer/MPNowPlayingInfoLanguageOption.h>
#import <MediaPlayer/MPRemoteCommand.h>
#import <MediaPlayer/MPRemoteCommandCenter.h>
#import <MediaPlayer/MPRemoteCommandEvent.h>
#import <MediaPlayer/MPRemoteControlTypes.h>

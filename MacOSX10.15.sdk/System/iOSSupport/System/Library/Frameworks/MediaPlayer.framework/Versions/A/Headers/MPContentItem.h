//
//  MPContentItem.h
//  MobileMusicPlayer
//
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItemArtwork;

/// MPContentItem represents high-level metadata for a particular media item for
/// representation outside the client application. Examples of media items that a
/// developer might want to represent include song files, streaming audio URLs,
/// or radio stations.
MP_API(ios(7.1), tvos(7.1), macos(10.12.2))
MP_PROHIBITED(watchos)
@interface MPContentItem : NSObject

/// Designated initializer. A unique identifier is required to identify the item
/// for later use.
- (instancetype)initWithIdentifier:(NSString *)identifier NS_DESIGNATED_INITIALIZER;

/// A unique identifier for this content item. (Required)
@property (nonatomic, copy, readonly) NSString *identifier;

/// A title for this item. Usually this would be the track name, if representing
/// a song, the episode name of a podcast, etc.
@property (nonatomic, copy, nullable) NSString *title;

/// A subtitle for this item. If this were representing a song, this would
/// usually be the artist or composer.
@property (nonatomic, copy, nullable) NSString *subtitle;

/// Artwork for this item. Examples of artwork for a content item are the album
/// cover for a song, or a movie poster for a movie.
@property (nonatomic, strong, nullable) MPMediaItemArtwork *artwork;

/// Represents the current playback progress of the item.
/// 0.0 = not watched/listened/viewed, 1.0 = fully watched/listened/viewed
/// Default is -1.0 (no progress indicator shown)
@property (nonatomic, assign) float playbackProgress;

/// Represents whether this content item is streaming content, i.e. from the cloud
/// where the content is not stored locally.
@property (nonatomic, assign, getter = isStreamingContent) BOOL streamingContent MP_API(ios(10.0), tvos(10.0), macos(10.12.2));

/// Represents whether this content item is explicit content
@property (nonatomic, assign, getter = isExplicitContent) BOOL explicitContent MP_API(ios(10.0), tvos(10.0), macos(10.12.2));

/// Represents whether the content item is a container that may contain other
/// content items, e.g. an album or a playlist.
@property (nonatomic, assign, getter = isContainer) BOOL container;

/// Represents whether the content item is actionable from a playback
/// perspective. Albums are playable, for example, because selecting an album
/// for playback means the app should play each song in the album in order. An
/// example of a content item that may not be playable is a genre, since an app
/// experience typically doesn't involve selecting an entire genre for playback.
@property (nonatomic, assign, getter = isPlayable) BOOL playable;

@end

NS_ASSUME_NONNULL_END

//
//  MPMediaItem.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <MediaPlayer/MediaPlayerDefines.h>
#import <MediaPlayer/MPMediaEntity.h>

NS_ASSUME_NONNULL_BEGIN

@class NSImage, UIImage, MPMediaItemArtwork;

typedef NS_OPTIONS(NSUInteger, MPMediaType) {
    // audio
    MPMediaTypeMusic                                            = 1 << 0,
    MPMediaTypePodcast                                          = 1 << 1,
    MPMediaTypeAudioBook                                        = 1 << 2,
    MPMediaTypeAudioITunesU MP_API(ios(5.0), macos(10.12.2))    = 1 << 3,
    MPMediaTypeAnyAudio                                         = 0x00ff,
    
    // video
    MPMediaTypeMovie        MP_API(ios(5.0), macos(10.12.2))    = 1 << 8,
    MPMediaTypeTVShow       MP_API(ios(5.0), macos(10.12.2))    = 1 << 9,
    MPMediaTypeVideoPodcast MP_API(ios(5.0), macos(10.12.2))    = 1 << 10,
    MPMediaTypeMusicVideo   MP_API(ios(5.0), macos(10.12.2))    = 1 << 11,
    MPMediaTypeVideoITunesU MP_API(ios(5.0), macos(10.12.2))    = 1 << 12,
    MPMediaTypeHomeVideo    MP_API(ios(7.0), macos(10.12.2))    = 1 << 13,
    MPMediaTypeAnyVideo     MP_API(ios(5.0), macos(10.12.2))    = 0xff00,
    
    MPMediaTypeAny                                     = ~0UL
} MP_API(ios(3.0), tvos(9.0), macos(10.12.2)) MP_PROHIBITED(watchos);

// An MPMediaItem represents a single piece of media in an MPMediaLibrary.
// Media items have a unique identifier which persists across application launches.

MP_API(ios(3.0))
MP_PROHIBITED(tvos, macos, watchos)
@interface MPMediaItem : MPMediaEntity

#pragma mark - Properties

// Properties marked filterable can also be used to build MPMediaPropertyPredicates (see MPMediaQuery.h).

MP_EXTERN NSString * const MPMediaItemPropertyPersistentID MP_API(ios(4.2), macos(10.12.2));                            // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID persistentID MP_API(ios(5.0));

MP_EXTERN NSString * const MPMediaItemPropertyMediaType;                                                                // filterable
@property (nonatomic, readonly) MPMediaType mediaType MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyTitle;                                                                    // filterable
@property (nonatomic, readonly, nullable) NSString *title MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTitle;                                                               // filterable
@property (nonatomic, readonly, nullable) NSString *albumTitle MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumPersistentID MP_API(ios(4.2), macos(10.12.2));                       // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID albumPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyArtist;                                                                   // filterable
@property (nonatomic, readonly, nullable) NSString *artist MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyArtistPersistentID MP_API(ios(4.2), macos(10.12.2));                      // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID artistPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumArtist;                                                              // filterable
@property (nonatomic, readonly, nullable) NSString *albumArtist MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumArtistPersistentID MP_API(ios(4.2), macos(10.12.2));                 // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID albumArtistPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyGenre;                                                                    // filterable
@property (nonatomic, readonly, nullable) NSString *genre MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyGenrePersistentID MP_API(ios(4.2), macos(10.12.2));                       // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID genrePersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyComposer;                                                                 // filterable
@property (nonatomic, readonly, nullable) NSString *composer MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyComposerPersistentID MP_API(ios(4.2), macos(10.12.2));                    // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID composerPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyPlaybackDuration;
@property (nonatomic, readonly) NSTimeInterval playbackDuration MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTrackNumber;
@property (nonatomic, readonly) NSUInteger albumTrackNumber MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTrackCount;
@property (nonatomic, readonly) NSUInteger albumTrackCount MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyDiscNumber;
@property (nonatomic, readonly) NSUInteger discNumber MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyDiscCount;
@property (nonatomic, readonly) NSUInteger discCount MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyArtwork MP_API(ios(3.0), macos(10.13.2));
@property (nonatomic, readonly, nullable) MPMediaItemArtwork *artwork MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyIsExplicit MP_API(ios(7.0), macos(10.12.2));
@property (nonatomic, readonly, getter = isExplicitItem) BOOL explicitItem MP_API(ios(10.0));

MP_EXTERN NSString * const MPMediaItemPropertyLyrics;
@property (nonatomic, readonly, nullable) NSString *lyrics MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyIsCompilation;                                                            // filterable
@property (nonatomic, readonly, getter = isCompilation) BOOL compilation MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyReleaseDate MP_API(ios(4.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSDate *releaseDate MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyBeatsPerMinute MP_API(ios(4.0), macos(10.12.2));
@property (nonatomic, readonly) NSUInteger beatsPerMinute MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyComments MP_API(ios(4.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *comments MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyAssetURL MP_API(ios(4.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSURL *assetURL MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyIsCloudItem MP_API(ios(6.0), macos(10.12.2));                             // filterable
@property (nonatomic, readonly, getter = isCloudItem) BOOL cloudItem MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyHasProtectedAsset MP_API(ios(9.2), macos(10.12.2));                       // filterable
@property (nonatomic, readonly, getter = hasProtectedAsset) BOOL protectedAsset MP_API(ios(9.2));

MP_EXTERN NSString * const MPMediaItemPropertyPodcastTitle;                                                             // filterable
@property (nonatomic, readonly, nullable) NSString *podcastTitle MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyPodcastPersistentID MP_API(ios(4.2), macos(10.12.2));                     // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID podcastPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyPlayCount;                                                                // filterable
@property (nonatomic, readonly) NSUInteger playCount MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertySkipCount;
@property (nonatomic, readonly) NSUInteger skipCount MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyRating;
@property (nonatomic, readonly) NSUInteger rating MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyLastPlayedDate;
@property (nonatomic, readonly, nullable) NSDate *lastPlayedDate MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyUserGrouping MP_API(ios(4.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *userGrouping MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyBookmarkTime MP_API(ios(6.0), macos(10.12.2));
@property (nonatomic, readonly) NSTimeInterval bookmarkTime MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyDateAdded MP_API(ios(10.0), macos(10.12.2));
@property (nonatomic, readonly) NSDate *dateAdded MP_API(ios(10.0));

// Matches the id used by MPMusicPlayerController to enqueue store tracks
MP_EXTERN NSString * const MPMediaItemPropertyPlaybackStoreID MP_API(ios(10.3));
@property (nonatomic, readonly) NSString *playbackStoreID MP_API(ios(10.3));

@end

//-----------------------------------------------------

MP_API(ios(3.0), tvos(9.0), macos(10.12.2), watchos(5.0))
@interface MPMediaItemArtwork : NSObject

#if TARGET_OS_IPHONE

- (instancetype)initWithBoundsSize:(CGSize)boundsSize requestHandler:(UIImage *(^)(CGSize size))requestHandler NS_DESIGNATED_INITIALIZER MP_API(ios(10.0), tvos(10.0));

// Returns the artwork image for an item at a given size (in points).
- (nullable UIImage *)imageWithSize:(CGSize)size;

#else

- (instancetype)initWithBoundsSize:(CGSize)boundsSize requestHandler:(NSImage *(^)(CGSize size))requestHandler NS_DESIGNATED_INITIALIZER MP_API(ios(10.12.2));

// Returns the artwork image for an item at a given size (in points).
- (nullable NSImage *)imageWithSize:(CGSize)size MP_API(ios(10.12.2));

#endif

@property (nonatomic, readonly) CGRect bounds; // The bounds of the full size image (in points).
@property (nonatomic, readonly) CGRect imageCropRect MP_DEPRECATED("cropRect is no longer used", ios(3.0, 10.0));

#if TARGET_OS_IPHONE
- (instancetype)initWithImage:(UIImage *)image MP_DEPRECATED("Use -initWithBoundsSize:requestHandler:", ios(5.0, 10.0));
#endif

- (id)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END


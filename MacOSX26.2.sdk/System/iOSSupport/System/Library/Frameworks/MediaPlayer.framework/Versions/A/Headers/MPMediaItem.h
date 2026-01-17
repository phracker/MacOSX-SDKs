//
//  MPMediaItem.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPMediaEntity.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItemArtwork;

typedef NS_OPTIONS(NSUInteger, MPMediaType) {
    // audio
    MPMediaTypeMusic                                                                    = 1 << 0,
    MPMediaTypePodcast                                                                  = 1 << 1,
    MPMediaTypeAudioBook                                                                = 1 << 2,
    MPMediaTypeAudioITunesU MP_API(ios(5.0), tvos(9.0), watchos(5.0), macos(10.12.2))   = 1 << 3,
    MPMediaTypeAnyAudio                                                                 = 0x00ff,
    
    // video
    MPMediaTypeMovie        MP_API(ios(5.0), tvos(9.0), watchos(5.0), macos(10.12.2))   = 1 << 8,
    MPMediaTypeTVShow       MP_API(ios(5.0), tvos(9.0), watchos(5.0), macos(10.12.2))   = 1 << 9,
    MPMediaTypeVideoPodcast MP_API(ios(5.0), tvos(9.0), watchos(5.0), macos(10.12.2))   = 1 << 10,
    MPMediaTypeMusicVideo   MP_API(ios(5.0), tvos(9.0), watchos(5.0), macos(10.12.2))   = 1 << 11,
    MPMediaTypeVideoITunesU MP_API(ios(5.0), tvos(9.0), watchos(5.0), macos(10.12.2))   = 1 << 12,
    MPMediaTypeHomeVideo    MP_API(ios(7.0), tvos(9.0), watchos(5.0), macos(10.12.2))   = 1 << 13,
    MPMediaTypeAnyVideo     MP_API(ios(5.0), tvos(9.0), watchos(5.0), macos(10.12.2))   = 0xff00,
    
    MPMediaTypeAny                                                                      = ~0UL
} MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));

// An MPMediaItem represents a single piece of media in an MPMediaLibrary.
// Media items have a unique identifier which persists across application launches.

MP_API(ios(3.0), tvos(14.0))
API_UNAVAILABLE(watchos, macos)
@interface MPMediaItem : MPMediaEntity

#pragma mark - Properties

// Properties marked filterable can also be used to build MPMediaPropertyPredicates (see MPMediaQuery.h).

MP_EXTERN NSString * const MPMediaItemPropertyPersistentID                                                              // filterable
    MP_API(ios(4.2), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) MPMediaEntityPersistentID persistentID MP_API(ios(5.0));

MP_EXTERN NSString * const MPMediaItemPropertyMediaType                                                                 // filterable
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) MPMediaType mediaType MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyTitle                                                                     // filterable
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *title MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTitle
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));                                                          // filterable
@property (nonatomic, readonly, nullable) NSString *albumTitle MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumPersistentID                                                         // filterable
    MP_API(ios(4.2), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) MPMediaEntityPersistentID albumPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyArtist                                                                    // filterable
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *artist MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyArtistPersistentID                                                        // filterable
    MP_API(ios(4.2), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) MPMediaEntityPersistentID artistPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumArtist                                                               // filterable
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *albumArtist MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumArtistPersistentID                                                   // filterable
    MP_API(ios(4.2), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) MPMediaEntityPersistentID albumArtistPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyGenre                                                                     // filterable
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *genre MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyGenrePersistentID                                                         // filterable
    MP_API(ios(4.2), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) MPMediaEntityPersistentID genrePersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyComposer                                                                  // filterable
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *composer MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyComposerPersistentID                                                      // filterable
    MP_API(ios(4.2), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) MPMediaEntityPersistentID composerPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyPlaybackDuration
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) NSTimeInterval playbackDuration MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTrackNumber
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) NSUInteger albumTrackNumber MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTrackCount
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) NSUInteger albumTrackCount MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyDiscNumber
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) NSUInteger discNumber MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyDiscCount
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) NSUInteger discCount MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyArtwork
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.13.2));
@property (nonatomic, readonly, nullable) MPMediaItemArtwork *artwork MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyIsExplicit
    MP_API(ios(7.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, getter = isExplicitItem) BOOL explicitItem MP_API(ios(10.0));

MP_EXTERN NSString * const MPMediaItemPropertyLyrics
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *lyrics MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyIsCompilation                                                             // filterable
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, getter = isCompilation) BOOL compilation MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyReleaseDate
    MP_API(ios(4.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSDate *releaseDate MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyBeatsPerMinute
    MP_API(ios(4.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) NSUInteger beatsPerMinute MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyComments
    MP_API(ios(4.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *comments MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyAssetURL
    MP_API(ios(4.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSURL *assetURL MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyIsCloudItem                                                               // filterable
    MP_API(ios(6.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, getter = isCloudItem) BOOL cloudItem MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyHasProtectedAsset                                                         // filterable
    MP_API(ios(9.2), tvos(9.2), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, getter = hasProtectedAsset) BOOL protectedAsset MP_API(ios(9.2));

MP_EXTERN NSString * const MPMediaItemPropertyPodcastTitle                                                              // filterable
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *podcastTitle MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyPodcastPersistentID                                                       // filterable
    MP_API(ios(4.2), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) MPMediaEntityPersistentID podcastPersistentID MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyPlayCount                                                                 // filterable
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) NSUInteger playCount MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertySkipCount
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) NSUInteger skipCount MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyRating
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) NSUInteger rating MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyLastPlayedDate
    MP_API(ios(3.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSDate *lastPlayedDate MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyUserGrouping
    MP_API(ios(4.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly, nullable) NSString *userGrouping MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaItemPropertyBookmarkTime
    MP_API(ios(6.0), tvos(9.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) NSTimeInterval bookmarkTime MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaItemPropertyDateAdded
    MP_API(ios(10.0), tvos(10.0), watchos(5.0), macos(10.12.2));
@property (nonatomic, readonly) NSDate *dateAdded MP_API(ios(10.0));

// Matches the id used by MPMusicPlayerController to enqueue store tracks
MP_EXTERN NSString * const MPMediaItemPropertyPlaybackStoreID
    MP_API(ios(10.3), tvos(10.3), watchos(5.0), macos(10.13));
@property (nonatomic, readonly) NSString *playbackStoreID MP_API(ios(10.3));

MP_EXTERN NSString * const MPMediaItemPropertyIsPreorder
    MP_API(ios(14.5), tvos(14.5), watchos(7.3), macos(11.3));
@property (nonatomic, readonly, getter=isPreorder) BOOL preorder MP_API(ios(10.3));

@end

//-----------------------------------------------------

#if TARGET_OS_OSX
@class NSImage;
#else
@class UIImage;
#endif

MP_API(ios(3.0), tvos(9.0), macos(10.12.2), watchos(5.0))
@interface MPMediaItemArtwork : NSObject

MP_INIT_UNAVAILABLE

#if TARGET_OS_IPHONE

- (instancetype)initWithBoundsSize:(CGSize)boundsSize requestHandler:(UIImage *(^)(CGSize size))requestHandler
    MP_API(ios(10.0), tvos(10.0), watchos(5.0))
    NS_DESIGNATED_INITIALIZER;

// Returns the artwork image for an item at a given size (in points).
- (nullable UIImage *)imageWithSize:(CGSize)size;

#else

- (instancetype)initWithBoundsSize:(CGSize)boundsSize requestHandler:(NSImage *(^)(CGSize size))requestHandler
    MP_API(macos(10.12.2))
    NS_DESIGNATED_INITIALIZER;

// Returns the artwork image for an item at a given size (in points).
- (nullable NSImage *)imageWithSize:(CGSize)size
    MP_API(macos(10.12.2));

#endif

@property (nonatomic, readonly) CGRect bounds; // The bounds of the full size image (in points).

// MARK: - Deprecated

@property (nonatomic, readonly) CGRect imageCropRect MP_DEPRECATED("cropRect is no longer used", ios(3.0, 10.0));

#if TARGET_OS_IPHONE
- (instancetype)initWithImage:(UIImage *)image MP_DEPRECATED("Use -initWithBoundsSize:requestHandler:", ios(5.0, 10.0));
#endif

@end

//-----------------------------------------------------

/// An animated image, such as an animated music album cover art, for a media item.
///
/// A single instance of animated artwork is comprised of two assets: an artwork video asset, and a
/// preview image which should match the first frame of the artwork video. The preview image may be
/// used when displaying the animated artwork whilst the video becomes available.
///
/// Both the preview image and artwork video can be fetched asynchronously and will only be
/// requested when required at point of display. Aim to provide preview images as quickly as
/// possible once requested, and ideally synchronously.
///
/// Video asset `URL`s you provide must be local file `URL`s. You should make the associated assets
/// available locally before providing them via the relevant handler, for example by fetching the
/// associated video asset over the network. The `URL`s should remain valid for the lifetime of the
/// ``MPMediaItemAnimatedArtwork``, once provided.
///
/// ``MPMediaItemAnimatedArtwork`` should not be subclassed.
MP_FINAL_CLASS
MP_API(ios(19.0), tvos(19.0), macos(16.0), watchos(12.0), visionos(3.0))
@interface MPMediaItemAnimatedArtwork : NSObject

MP_INIT_UNAVAILABLE

#if TARGET_OS_IPHONE

/// Creates an animated artwork.
///
/// - Parameters:
///   - artworkID: A unique identifier for this animated artwork. This identifier should encapsulate
///   the identity of both the preview frame and video asset. If you change either, you should
///   provide an ``MPMediaItemAnimatedArtwork`` with an updated `artworkID`.
///   - previewImageRequestHandler: A handler to return a preview image for this artwork, for the
///   requested `CGSize` in pixels. Once requested, you should pass the preview image to the
///   provided completion handler, or you can pass `nil` if the preview image cannot be resolved
///   for any reason. You can call the completion handler on an arbitrary queue, however it must
///   only be called once. The `UIImage` you provide should ideally have a size equal to the
///   requested `CGSize`, however an image of the same aspect ratio is acceptable. Images that
///   diverge significantly from the requested aspect ratio may be rejected by the system. Aim to
///   provide preview images quickly and ideally synchronously, and if possible you should preload
///   these images in order to reduce perceived latency when displaying animated artwork to the
///   user.
///   - videoAssetFileURLRequestHandler: A handler to return a file `URL` for the artwork video
///   asset for this artwork, for the requested `CGSize` in pixels. Once requested, you should pass
///   the `URL` to the provided completion handler, or you can pass `nil` if the artwork video asset
///   cannot be resolved for any reason. You can call the completion handler on an arbitrary queue,
///   however it must only be called once. The `URL` you provide must reference a local asset,
///   ideally with a size equal to the requested `CGSize`, however an asset with the same aspect
///   ratio is acceptable. Assets that diverge significantly from the requested aspect ratio may be
///   rejected by the system. The video assets you provide should loop cleanly, and should be
///   available relatively quickly from this handler (particularly when re-fetched). It’s advised
///   that assets are cached for subsequent fetches.
- (instancetype)initWithArtworkID:(NSString *)artworkID
       previewImageRequestHandler:(void (^)(CGSize size, void (^completion)(UIImage * _Nullable image)))previewImageRequestHandler
  videoAssetFileURLRequestHandler:(void (^)(CGSize size, void (^completion)(NSURL * _Nullable url)))videoAssetFileURLRequestHandler MP_API(ios(19.0), tvos(19.0), watchos(12.0), visionos(3.0)) NS_DESIGNATED_INITIALIZER;

#else

/// Creates an animated artwork.
///
/// - Parameters:
///   - artworkID: A unique identifier for this animated artwork. This identifier should encapsulate
///   the identity of both the preview frame and video asset. If you change either, you should
///   provide an ``MPMediaItemAnimatedArtwork`` with an updated `artworkID`.
///   - previewImageRequestHandler: A handler to return a preview image for this artwork, for the
///   requested `CGSize` in pixels. Once requested, you should pass the preview image to the
///   provided completion handler, or you can pass `nil` if the preview image cannot be resolved
///   for any reason. You can call the completion handler on an arbitrary queue, however it must
///   only be called once. The `NSImage` you provide should ideally have a size equal to the
///   requested `CGSize`, however an image of the same aspect ratio is acceptable. Images that
///   diverge significantly from the requested aspect ratio may be rejected by the system. Aim to
///   provide preview images quickly and ideally synchronously, and if possible you should preload
///   these images in order to reduce perceived latency when displaying animated artwork to the
///   user.
///   - videoAssetFileURLRequestHandler: A handler to return a file `URL` for the artwork video
///   asset for this artwork, for the requested `CGSize` in pixels. Once requested, you should pass
///   the `URL` to the provided completion handler, or you can pass `nil` if the artwork video asset
///   cannot be resolved for any reason. You can call the completion handler on an arbitrary queue,
///   however it must only be called once. The `URL` you provide must reference a local asset,
///   ideally with a size equal to the requested `CGSize`, however an asset with the same aspect
///   ratio is acceptable. Assets that diverge significantly from the requested aspect ratio may be
///   rejected by the system. The video assets you provide should loop cleanly, and should be
///   available relatively quickly from this handler (particularly when re-fetched). It’s advised
///   that assets are cached for subsequent fetches.
- (instancetype)initWithArtworkID:(NSString *)artworkID
       previewImageRequestHandler:(void (^)(CGSize size, void (^completion)(NSImage * _Nullable image)))previewImageRequestHandler
  videoAssetFileURLRequestHandler:(void (^)(CGSize size, void (^completion)(NSURL * _Nullable url)))videoAssetFileURLRequestHandler MP_API(macos(16.0)) NS_DESIGNATED_INITIALIZER;

#endif

@end

NS_ASSUME_NONNULL_END


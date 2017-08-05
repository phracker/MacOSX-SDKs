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
    MPMediaTypeMusic                                        = 1 << 0,
    MPMediaTypePodcast                                      = 1 << 1,
    MPMediaTypeAudioBook                                    = 1 << 2,
    MPMediaTypeAudioITunesU NS_ENUM_AVAILABLE(10_12_2, 5_0) = 1 << 3,
    MPMediaTypeAnyAudio                                     = 0x00ff,
    
    // video (available in iOS 5.0)
    MPMediaTypeMovie        NS_ENUM_AVAILABLE(10_12_2, 5_0) = 1 << 8,
    MPMediaTypeTVShow       NS_ENUM_AVAILABLE(10_12_2, 5_0) = 1 << 9,
    MPMediaTypeVideoPodcast NS_ENUM_AVAILABLE(10_12_2, 5_0) = 1 << 10,
    MPMediaTypeMusicVideo   NS_ENUM_AVAILABLE(10_12_2, 5_0) = 1 << 11,
    MPMediaTypeVideoITunesU NS_ENUM_AVAILABLE(10_12_2, 5_0) = 1 << 12,
    MPMediaTypeHomeVideo    NS_ENUM_AVAILABLE(10_12_2, 7_0) = 1 << 13,
    MPMediaTypeAnyVideo     NS_ENUM_AVAILABLE(10_12_2, 5_0) = 0xff00,
    
    MPMediaTypeAny                                     = ~0UL
} MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(3.0, 10.12.2, 3.0);

// An MPMediaItem represents a single piece of media in an MPMediaLibrary.
// Media items have a unique identifier which persists across application launches.

MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(3.0, 10.12.2, 3.0)
@interface MPMediaItem : MPMediaEntity

#pragma mark - Properties

// Properties marked filterable can also be used to build MPMediaPropertyPredicates (see MPMediaQuery.h).

MP_EXTERN NSString * const MPMediaItemPropertyPersistentID NS_AVAILABLE(10_12_2, 4_2);              // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID persistentID NS_AVAILABLE_IOS(5_0);

MP_EXTERN NSString * const MPMediaItemPropertyMediaType;                                            // filterable
@property (nonatomic, readonly) MPMediaType mediaType NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyTitle;                                                // filterable
@property (nonatomic, readonly, nullable) NSString *title NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTitle;                                           // filterable
@property (nonatomic, readonly, nullable) NSString *albumTitle NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyAlbumPersistentID NS_AVAILABLE(10_12_2, 4_2);         // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID albumPersistentID NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyArtist;                                               // filterable
@property (nonatomic, readonly, nullable) NSString *artist NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyArtistPersistentID NS_AVAILABLE(10_12_2, 4_2);        // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID artistPersistentID NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyAlbumArtist;                                          // filterable
@property (nonatomic, readonly, nullable) NSString *albumArtist NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyAlbumArtistPersistentID NS_AVAILABLE(10_12_2, 4_2);   // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID albumArtistPersistentID NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyGenre;                                                // filterable
@property (nonatomic, readonly, nullable) NSString *genre NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyGenrePersistentID NS_AVAILABLE(10_12_2, 4_2);         // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID genrePersistentID NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyComposer;                                             // filterable
@property (nonatomic, readonly, nullable) NSString *composer NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyComposerPersistentID NS_AVAILABLE(10_12_2, 4_2);      // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID composerPersistentID NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyPlaybackDuration;
@property (nonatomic, readonly) NSTimeInterval playbackDuration NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTrackNumber;
@property (nonatomic, readonly) NSUInteger albumTrackNumber NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyAlbumTrackCount;
@property (nonatomic, readonly) NSUInteger albumTrackCount NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyDiscNumber;
@property (nonatomic, readonly) NSUInteger discNumber NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyDiscCount;
@property (nonatomic, readonly) NSUInteger discCount NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyArtwork;
@property (nonatomic, readonly, nullable) MPMediaItemArtwork *artwork NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString *const MPMediaItemPropertyIsExplicit NS_AVAILABLE(10_12_2, 7_0);
@property (nonatomic, readonly, getter = isExplicitItem) BOOL explicitItem NS_AVAILABLE_IOS(10_0);

MP_EXTERN NSString * const MPMediaItemPropertyLyrics;
@property (nonatomic, readonly, nullable) NSString *lyrics NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyIsCompilation;                                       // filterable
@property (nonatomic, readonly, getter = isCompilation) BOOL compilation NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyReleaseDate NS_AVAILABLE(10_12_2, 4_0);
@property (nonatomic, readonly, nullable) NSDate *releaseDate NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyBeatsPerMinute NS_AVAILABLE(10_12_2, 4_0);
@property (nonatomic, readonly) NSUInteger beatsPerMinute NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyComments NS_AVAILABLE(10_12_2, 4_0);
@property (nonatomic, readonly, nullable) NSString *comments NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyAssetURL NS_AVAILABLE(10_12_2, 4_0);
@property (nonatomic, readonly, nullable) NSURL *assetURL NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyIsCloudItem NS_AVAILABLE(10_12_2, 6_0);                // filterable
@property (nonatomic, readonly, getter = isCloudItem) BOOL cloudItem NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyHasProtectedAsset NS_AVAILABLE(10_12_2, 9_2);          // filterable
@property (nonatomic, readonly, getter = hasProtectedAsset) BOOL protectedAsset NS_AVAILABLE_IOS(9_2);

MP_EXTERN NSString * const MPMediaItemPropertyPodcastTitle;                                          // filterable
@property (nonatomic, readonly, nullable) NSString *podcastTitle NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyPodcastPersistentID NS_AVAILABLE(10_12_2, 4_2);        // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID podcastPersistentID NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyPlayCount;                                             // filterable
@property (nonatomic, readonly) NSUInteger playCount NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertySkipCount;
@property (nonatomic, readonly) NSUInteger skipCount NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyRating;
@property (nonatomic, readonly) NSUInteger rating NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyLastPlayedDate;
@property (nonatomic, readonly, nullable) NSDate *lastPlayedDate NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyUserGrouping NS_AVAILABLE(10_12_2, 4_0);
@property (nonatomic, readonly, nullable) NSString *userGrouping NS_AVAILABLE_IOS(8_0);

MP_EXTERN NSString * const MPMediaItemPropertyBookmarkTime NS_AVAILABLE(10_12_2, 6_0);
@property (nonatomic, readonly) NSTimeInterval bookmarkTime NS_AVAILABLE_IOS(7_0);

MP_EXTERN NSString * const MPMediaItemPropertyDateAdded NS_AVAILABLE(10_12_2, 10_0);
@property (nonatomic, readonly) NSDate *dateAdded NS_AVAILABLE_IOS(10_0);

@end

//-----------------------------------------------------

MP_API(ios(3.0), tvos(3.0), macos(10.12.2))
@interface MPMediaItemArtwork : NSObject

#if TARGET_OS_IPHONE

- (instancetype)initWithBoundsSize:(CGSize)boundsSize requestHandler:(UIImage *(^)(CGSize size))requestHandler NS_DESIGNATED_INITIALIZER NS_AVAILABLE_IOS(10_0);

// Returns the artwork image for an item at a given size (in points).
- (nullable UIImage *)imageWithSize:(CGSize)size;

#else

- (instancetype)initWithBoundsSize:(CGSize)boundsSize requestHandler:(NSImage *(^)(CGSize size))requestHandler NS_DESIGNATED_INITIALIZER NS_AVAILABLE_MAC(10_12_2);

// Returns the artwork image for an item at a given size (in points).
- (nullable NSImage *)imageWithSize:(CGSize)size NS_AVAILABLE_MAC(10_12_2);

#endif

@property (nonatomic, readonly) CGRect bounds; // The bounds of the full size image (in points).
@property (nonatomic, readonly) CGRect imageCropRect NS_DEPRECATED_IOS(3_0, 10_0);

#if TARGET_OS_IPHONE
- (instancetype)initWithImage:(UIImage *)image NS_DEPRECATED_IOS(5_0, 10_0);
#endif

- (id)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

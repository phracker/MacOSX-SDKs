/*!
	@file		ITLibMediaItem.h
	@copyright	© 2012-2020 Apple Inc.
 */

#import <iTunesLibrary/ITLibMediaEntity.h>
#import <iTunesLibrary/ITLibDefines.h>

NS_ASSUME_NONNULL_BEGIN

// Forward declaration.
@class ITLibAlbum;

// Forward declaration.
@class ITLibArtist;

// Forward declaration.
@class ITLibMediaItemVideoInfo;

// Forward declaration.
@class ITLibArtwork;

/*!
	@enum		ITLibMediaItemMediaKind	
    @abstract	These constants specify the possible media kinds of a iTunes media item.
    @constant	ITLibMediaItemMediaKindUnknown 
					The media item kind is unknown.
	@constant	ITLibMediaItemMediaKindSong
					The media item is a song.
	@constant	ITLibMediaItemMediaKindMovie
					The media item is a movie.
	@constant	ITLibMediaItemMediaKindPodcast
					The media item is an audio or video podcast.
	@constant	ITLibMediaItemMediaKindAudiobook
					The media item is an audiobook.
	@constant	ITLibMediaItemMediaKindPDFBooklet 
					The media item is an unwrapped PDF file that is part of a Music album.
	@constant	ITLibMediaItemMediaKindMusicVideo
					The media item is a music video.
	@constant	ITLibMediaItemMediaKindTVShow
					The media item is a TV show.
    @constant   ITLibMediaItemMediaKindInteractiveBooklet
					The media item is a QuickTime movie with embedded flash (deprecated)
	@constant	ITLibMediaItemMediaKindHomeVideo
					The media item is a non-iTunes Store movie.
	@constant	ITLibMediaItemMediaKindRingtone
					The media item is an iOS ringtone.
    @constant   ITLibMediaItemMediaKindDigitalBooklet 
					The media item is an iTunes Extra or an iTunes LP.
    @constant   ITLibMediaItemMediaKindIOSApplication 
					The media item is an iPhone or iPod touch application.
    @constant   ITLibMediaItemMediaKindVoiceMemo 
					The media item is a voice memo recorded on iPod/iPhone.
	@constant	ITLibMediaItemMediaKindiTunesU
					The media item is an iTunesU audio of video file.
	@constant	ITLibMediaItemMediaKindBook
					The media item is an EPUB or iBooks Author book.
    @constant   ITLibMediaItemMediaKindPDFBook Generic PDF files. 
					The media item is a PDF treated as Books in the UI unless overridden by the user.
    @constant   ITLibMediaItemMediaKindAlertTone 
					The media item is an audio tone on an iOS device which is not a protected ringtone.
 */
typedef NS_ENUM( NSUInteger, ITLibMediaItemMediaKind )
{
    ITLibMediaItemMediaKindUnknown				= 1,
    ITLibMediaItemMediaKindSong					= 2,
    ITLibMediaItemMediaKindMovie				= 3,
    ITLibMediaItemMediaKindPodcast				= 4,
    ITLibMediaItemMediaKindAudiobook			= 5,
    ITLibMediaItemMediaKindPDFBooklet			= 6,
    ITLibMediaItemMediaKindMusicVideo			= 7,
    ITLibMediaItemMediaKindTVShow				= 8,
    ITLibMediaItemMediaKindInteractiveBooklet	= 9,
    ITLibMediaItemMediaKindHomeVideo			= 12,
    ITLibMediaItemMediaKindRingtone             = 14,
    ITLibMediaItemMediaKindDigitalBooklet		= 15,
    ITLibMediaItemMediaKindIOSApplication       = 16,
    ITLibMediaItemMediaKindVoiceMemo			= 17,
    ITLibMediaItemMediaKindiTunesU              = 18,
    ITLibMediaItemMediaKindBook                 = 19,
    ITLibMediaItemMediaKindPDFBook              = 20,
    ITLibMediaItemMediaKindAlertTone			= 21

} API_UNAVAILABLE(ios);

/*!
	@enum		ITLibMediaItemLyricsContentRating
	@abstract	These constants specify the possible ratings of media item lyrics.
	@constant   ITLibMediaItemLyricsContentRatingNone 
					No rating information for the media item lyrics.
	@constant   ITLibMediaItemLyricsContentRatingExplicit 
					The media item lyrics contain explicit language.
	@constant   ITLibMediaItemLyricsContentRatingClean 
					The media item lyrics do not contain explicit language.
 */
typedef NS_ENUM( NSUInteger, ITLibMediaItemLyricsContentRating )
{
    ITLibMediaItemLyricsContentRatingNone = 0,
    ITLibMediaItemLyricsContentRatingExplicit = 1,
    ITLibMediaItemLyricsContentRatingClean = 2

} API_UNAVAILABLE(ios);

/*!
	@enum		ITLibMediaItemLocationType
	@abstract   These constants specify the location type of a media item.
	@constant   ITLibMediaItemLocationTypeUnknown 
					The media item location type is not known.
	@constant   ITLibMediaItemLocationTypeFile 
					The media item location refers to a local file.
	@constant   ITLibMediaItemLocationTypeURL 
					The media item location refers to a URL (for example, a podcast).
	@constant   ITLibMediaItemLocationTypeRemote 
					The media item location refers to a remote file.
 */
typedef NS_ENUM( NSUInteger, ITLibMediaItemLocationType )
{
    ITLibMediaItemLocationTypeUnknown = 0,
    ITLibMediaItemLocationTypeFile = 1,
    ITLibMediaItemLocationTypeURL = 2,
    ITLibMediaItemLocationTypeRemote = 3

} API_UNAVAILABLE(ios);

/*!
	@enum		ITLibMediaItemPlayStatus
	@abstract   These constants specify the "blue dot" play status of this media item.
	@constant   ITLibMediaItemPlayStatusNone
					The item has been played (see playCount) or the play status is not tracked for this type of media item.
	@constant   ITLibMediaItemPlayStatusPartiallyPlayed
					The media item has been partially played.
	@constant   ITLibMediaItemPlayStatusUnplayed
					The media item has not been played.  Note that the user can also set this state manually.
 */
typedef NS_ENUM( NSUInteger, ITLibMediaItemPlayStatus )
{
    ITLibMediaItemPlayStatusNone = 0,
    ITLibMediaItemPlayStatusPartiallyPlayed = 1,
    ITLibMediaItemPlayStatusUnplayed= 2,

} API_UNAVAILABLE(ios);

@class ITLibMediaItemData;

/*!
	@abstract A media item represents a single piece of media (such as a song, a video, a podcast, etc) in the iTunes library. 
			  A media item has an overall unique identifier, accessed using the persistentID property. The media item
			  metadata may be accessed through its individual properties or via the ITLibMediaEntity general property accessor
			  methods.
 */
API_UNAVAILABLE(ios)
ITLIB_EXPORT @interface ITLibMediaItem : ITLibMediaEntity
{
	ITLibMediaItemData * _data;
}

/*! @abstract The title of this media item. May be empty. */
@property (readonly, nonatomic, copy) NSString* title;

/*! @abstract The title of this media item that should be used for sorting purposes.  If nil, use the title field. */
@property (readonly, nonatomic, copy, nullable) NSString* sortTitle;

/*! @abstract The artist associated with this media item. */
@property (readonly, nonatomic, retain, nullable) ITLibArtist* artist;

/*! @abstract The name of the composer associated with this media item.  May be empty. */
@property (readonly, nonatomic, copy) NSString* composer;

/*! @abstract The name of the composer associated with this media item that should be used for sorting purposes. If nil, use the composer field. */
@property (readonly, nonatomic, copy, nullable) NSString* sortComposer;

/*! @abstract The rating of this media item. */
@property (readonly, nonatomic, assign) NSInteger rating;

/*! @abstract Whether this media item's rating is computed. */
@property (readonly, nonatomic, assign, getter = isRatingComputed) BOOL ratingComputed;

/*! @abstract If non-zero, the actual time playback for this media item will start instead of 0:00 (in milliseconds). */
@property (readonly, nonatomic, assign) NSUInteger startTime;

/*! @abstract If non-zero, the actual time playback for this media item will stop vs. the total time (in milliseconds). */
@property (readonly, nonatomic, assign) NSUInteger stopTime;

/*! @abstract The album where this media item belongs. */
@property (readonly, nonatomic, retain) ITLibAlbum* album;

/*! @abstract The genre associated with this media item. May be empty. */
@property (readonly, nonatomic, copy) NSString* genre;

/*! @abstract This media item's file kind (ex. MPEG audio file). */
@property (readonly, nonatomic, copy, nullable) NSString* kind;

/*! @abstract This media item's media kind. */
@property (readonly, nonatomic, assign) ITLibMediaItemMediaKind mediaKind;

/*! @abstract The size in bytes of this media item on disk. */
@property (readonly, nonatomic, assign) unsigned long long fileSize;

/*! @abstract The size in bytes of this media item on disk. (deprecated: use fileSize instead) */
@property (readonly, nonatomic, assign) NSUInteger size DEPRECATED_ATTRIBUTE;

/*! @abstract The length of this media item in milliseconds. */
@property (readonly, nonatomic, assign) NSUInteger totalTime;

/*! @abstract The position of this media item within its album. */
@property (readonly, nonatomic, assign) NSUInteger trackNumber;

/*! @abstract The podcast category of this media item (implies this media item is a podcast). */
@property (readonly, nonatomic, copy, nullable) NSString* category;

/*! @abstract Any podcast description of with this media item (implies this media item is a podcast). */
@property (readonly, nonatomic, copy, nullable) NSString* description;

/*! @abstract The content rating of this media item's lyrics. */
@property (readonly, nonatomic, assign) ITLibMediaItemLyricsContentRating lyricsContentRating;

/*! @abstract The extended content rating of this media item. */
@property (readonly, nonatomic, copy, nullable) NSString* contentRating;

/*! @abstract The date and time this media item was last modified. */
@property (readonly, nonatomic, retain, nullable) NSDate* modifiedDate;

/*! @abstract The date and media item this media item was added to the iTunes database. */
@property (readonly, nonatomic, retain, nullable) NSDate* addedDate;

/*! @abstract The bitrate of this media item in kbps. */
@property (readonly, nonatomic, assign) NSUInteger bitrate;

/*! @abstract The sample rate of this media item in samples per second. */
@property (readonly, nonatomic, assign) NSUInteger sampleRate;

/*! @abstract The BPM (beats per minute) of this media item. */
@property (readonly, nonatomic, assign) NSUInteger beatsPerMinute;

/*! @abstract The number of times this media item has been played in iTunes. */
@property (readonly, nonatomic, assign) NSUInteger playCount;

/*! @abstract The date and time this media item was last played in iTunes, or nil if this media item has not been played. */
@property (readonly, nonatomic, retain, nullable) NSDate* lastPlayedDate;

/*! @abstract The play status for this media.  Represents partially played and unplayed states for videos and podcasts. Other media kinds always return "none". */
@property (readonly, nonatomic, assign) ITLibMediaItemPlayStatus playStatus WEAK_IMPORT_ATTRIBUTE;	// added in 12.4

/*! @abstract The location of this media item on disk. */
@property (readonly, nonatomic, retain, nullable) NSURL* location;

/*! @abstract Whether this media item has artwork. */
@property (readonly, nonatomic, assign, getter=hasArtworkAvailable) BOOL artworkAvailable;

/*! @abstract Whether this media item has artwork. */
@property (readonly, nonatomic, retain, nullable) ITLibArtwork* artwork;

/*! @abstract Any comments associated with this media item. */
@property (readonly, nonatomic, copy, nullable) NSString* comments;

/*! @abstract Whether this media item was purchased. */
@property (readonly, nonatomic, assign, getter=isPurchased) BOOL purchased;

/*! @abstract Whether this media item is iTunes Match or iTunes in the Cloud. */
@property (readonly, nonatomic, assign, getter=isCloud) BOOL cloud;

/*! @abstract Whether this media item is DRM protected. */
@property (readonly, nonatomic, assign, getter=isDRMProtected) BOOL drmProtected;

/*! @abstract Whether this media item is a video media item (video podcast, movie, etc). */
@property (readonly, nonatomic, assign, getter=isVideo) BOOL video;

/*! @abstract The video information of this media item (implies this media item is a video media item). */
@property (readonly, nonatomic, retain, nullable) ITLibMediaItemVideoInfo* videoInfo;

/*! @abstract The date this media item was released. */
@property (readonly, nonatomic, retain, nullable) NSDate* releaseDate;

/*! @abstract The year when this media item was released. */
@property (readonly, nonatomic, assign) NSUInteger year;

/*! @abstract The type of the file this media item refers to. */
@property (readonly, nonatomic, assign) NSUInteger fileType DEPRECATED_ATTRIBUTE;

/*! @abstract The number of times this media item has been skiped. */
@property (readonly, nonatomic, assign) NSUInteger skipCount;

/*! @abstract The date and time when this media item was last skipped. */
@property (readonly, nonatomic, retain, nullable) NSDate* skipDate;

/*! @abstract The voice-over language of this media item */
@property (readonly, nonatomic, copy, nullable) NSString* voiceOverLanguage;

/*! @abstract The volume adjustment used for this media item if any. */
@property (readonly, nonatomic, assign) NSInteger volumeAdjustment;

/*! @abstract The volume normalization energy applied to this media item. */
@property (readonly, nonatomic, assign) NSUInteger volumeNormalizationEnergy;

/*! @abstract Whether the user has disabled this media item. */
@property (readonly, nonatomic, assign, getter = isUserDisabled) BOOL userDisabled;

/*! @abstract The grouping of this media item. */
@property (readonly, nonatomic, copy, nullable) NSString* grouping;

/*! @abstract The type of this media item with respect to its location. */
@property (readonly, nonatomic, assign) ITLibMediaItemLocationType locationType;

@end

ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyAlbumTitle;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertySortAlbumTitle;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyAlbumArtist;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyAlbumRating;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyAlbumRatingComputed;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertySortAlbumArtist;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyAlbumIsGapless;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyAlbumIsCompilation;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyAlbumDiscCount;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyAlbumDiscNumber;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyAlbumTrackCount;

ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyArtistName;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertySortArtistName;

ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyVideoIsHD;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyVideoWidth;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyVideoHeight;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyVideoSeries;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyVideoSortSeries;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyVideoSeason;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyVideoEpisode;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyVideoEpisodeOrder;

ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyHasArtwork;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyBitRate;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyBeatsPerMinute;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyCategory;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyComments;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyComposer;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertySortComposer;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyContentRating;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyLyricsContentRating;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyAddedDate;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyModifiedDate;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyDescription;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyIsUserDisabled;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyFileType DEPRECATED_ATTRIBUTE;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyGenre;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyGrouping;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyIsVideo;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyKind;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyTitle;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertySortTitle;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyVolumeNormalizationEnergy;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyPlayCount;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyLastPlayDate;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyPlayStatus;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyIsDRMProtected;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyIsPurchased;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyMovementCount;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyMovementName;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyMovementNumber;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyRating;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyRatingComputed;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyReleaseDate;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertySampleRate;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertySize;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyFileSize;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyUserSkipCount;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertySkipDate;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyStartTime;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyStopTime;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyTotalTime;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyTrackNumber;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyLocationType;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyVoiceOverLanguage;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyVolumeAdjustment;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyWork;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyYear;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyMediaKind;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyLocation;
ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaItemPropertyArtwork;

NS_ASSUME_NONNULL_END

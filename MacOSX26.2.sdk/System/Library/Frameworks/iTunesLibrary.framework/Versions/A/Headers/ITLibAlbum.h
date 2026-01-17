/*!
	@header		ITLibAlbum.h
	@copyright	© 2012-2016 Apple Inc.
 */

#import <Foundation/Foundation.h>
#import <iTunesLibrary/ITLibDefines.h>

NS_ASSUME_NONNULL_BEGIN

// Forward declaration.
@class ITLibArtist;

/*! @abstract The ITLibAlbum class represents an album where a given media item (ITLibMediaItem) is contained. */
API_UNAVAILABLE(ios)
ITLIB_EXPORT @interface ITLibAlbum : NSObject
{
	NSString* _title;
	NSString* _sortTitle;
	BOOL _compilation;
	NSUInteger _discCount;
	NSUInteger _discNumber;
	NSInteger _rating; 
	BOOL _ratingComputed;
	BOOL _gapless;
	NSUInteger _trackCount;
	NSString* _albumArtist;
	NSString* _sortAlbumArtist;
	NSNumber* _persistentID;
}

/*! @abstract The name of this album. */
@property (readonly, nonatomic, copy, nullable) NSString* title;

/*! @abstract The name of this that should be used for sorting purposes. */
@property (readonly, nonatomic, copy, nullable) NSString* sortTitle;

/*! @abstract Whether this album is a compilation. */
@property (readonly, nonatomic, assign, getter = isCompilation) BOOL compilation;

/*! @abstract Deprecated. Will be removed in future versions. */
@property (readonly, nonatomic, retain, nullable) ITLibArtist* artist DEPRECATED_ATTRIBUTE;

/*! @abstract The number of discs in this album. */
@property (readonly, nonatomic, assign) NSUInteger discCount;

/*! @abstract The index (i.e. 1, 2, 3, etc.) of the disc this album refers to within a compilation. */
@property (readonly, nonatomic, assign) NSUInteger discNumber;

/*! @abstract The rating of this track's album. */
@property (readonly, nonatomic, assign) NSInteger rating; 

/*! @abstract The rating of this track's album. */
@property (readonly, nonatomic, assign, getter = isRatingComputed) BOOL ratingComputed;

/*! @abstract Whether this track's album is gapless. */
@property (readonly, nonatomic, assign, getter = isGapless) BOOL gapless;

/*! @abstract Number of tracks in this album. */
@property (readonly, nonatomic, assign) NSUInteger trackCount;

/*! @abstract The artist associated with this album. */
@property (readonly, nonatomic, copy, nullable) NSString* albumArtist;

/*! @abstract The artist associated with this album. This field should be used when sorting. */
@property (readonly, nonatomic, copy, nullable) NSString* sortAlbumArtist;

/*! @abstract The unique identifier of this album. */
@property (readonly, nonatomic, retain) NSNumber* persistentID;

@end

NS_ASSUME_NONNULL_END

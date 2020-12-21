/*!
	@file		ITLibMediaItemVideoInfo.h
	@copyright	© 2012-2016 Apple Inc.
 */

#import <Foundation/Foundation.h>
#import <iTunesLibrary/ITLibDefines.h>

/*! @abstract The ITLibMediaItemVideoInfo class encapsulates the video information of a video media item. */
API_UNAVAILABLE(ios)
ITLIB_EXPORT @interface ITLibMediaItemVideoInfo : NSObject
{
	NSString*	_series;
	NSString*	_sortSeries;
	NSUInteger	_season;
	NSString*	_episode;
	NSInteger	_episodeOrder;
	BOOL		_hd;
	NSUInteger	_videoWidth;
	NSUInteger	_videoHeight;
}

/*! @abstract The name of TV series the video is associated with (implies track is a TV show). */
@property (readonly, nonatomic, copy, nullable) NSString* series;

/*! @abstract The name of the TV series the video is associated with that should be used for when sorting (implies the track is a TV show). */
@property (readonly, nonatomic, copy, nullable) NSString* sortSeries;

/*! @abstract The name of TV season the video is associated with (implies the track is a TV show). */
@property (readonly, nonatomic, assign) NSUInteger season;

/*! @abstract The TV episode the video is associated with (implies the track is a TV show). */
@property (readonly, nonatomic, copy, nullable) NSString* episode;

/*! @abstract The TV episode order the video is associated with (implies the track is a TV show). */
@property (readonly, nonatomic, assign) NSInteger episodeOrder;

/*! @abstract Whether the video is high definition. */
@property (readonly, nonatomic, assign, getter=isHD) BOOL hd;

/*! @abstract The width of the video. */
@property (readonly, nonatomic, assign) NSUInteger videoWidth;

/*! @abstract The height of the video. */
@property (readonly, nonatomic, assign) NSUInteger videoHeight;

@end

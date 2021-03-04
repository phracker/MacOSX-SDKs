/*!
	@header		ITLibArtist.h
	@copyright	@ 2012-2016 Apple Inc.
 */

#import <Foundation/Foundation.h>
#import <iTunesLibrary/ITLibDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*! The ITLibArtist class represents an artist, such as the performer of a song. */
API_UNAVAILABLE(ios)
ITLIB_EXPORT @interface ITLibArtist : NSObject
{
	NSString* _name;
	NSString* _sortName;
	NSNumber* _persistentID;
}

/*! @abstract The name of this artist. */
@property (readonly, nonatomic, copy, nullable) NSString* name;

/*! @abstract The name of this artist that should be used for sorting purposes. */
@property (readonly, nonatomic, copy, nullable) NSString* sortName;

/*! @abstract The unique identifier of this artist. */
@property (readonly, nonatomic, retain) NSNumber* persistentID;

@end

NS_ASSUME_NONNULL_END

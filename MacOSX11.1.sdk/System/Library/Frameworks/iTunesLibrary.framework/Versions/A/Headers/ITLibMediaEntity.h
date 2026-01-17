/*!
	@file		ITLibMediaEntity.h
	@copyright	© 2012-2019 Apple Inc.
 */

#import <Foundation/Foundation.h>
#import <iTunesLibrary/ITLibDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
	@abstract	The ITLibMediaEntity class serves as the abstract superclass for ITLibMediaItem and ITLibPlaylist instances.
				As the superclass, ITLibMediaEntity defines methods used by those subclasses.
 */
API_UNAVAILABLE(ios)
ITLIB_EXPORT @interface ITLibMediaEntity : NSObject
{
	NSMutableDictionary *	_fields;
	NSNumber *				_persistentID;
}

/*! @abstract The unique identifier of this media entity. */
@property (readonly, nonatomic, retain) NSNumber* persistentID;

/*!
	@abstract Gets the value for a specified media property key.
	@discusion The media property keys you can use with this property are listed in this document 
			   and in Media Item Property Keys and Playlist Property Keys.
	@param property The media property key that you want the corresponding value of.
	@return The value for the media property key.
 */
- (nullable id) valueForProperty:(NSString *)property;

/*!
	@abstract Executes a provided block with the fetched values for the given item properties.
	@discussion Use this method to get property values in a batch fashion. 
				In some cases, enumerating over a set of property keys can be more efficient 
				than fetching each individual property with valueForProperty:.
				The media property keys you can use with this property are listed in this document 
				and in Media Item Property Keys and Playlist Property Keys.
	@param properties A set of keys for the properties that will be enumerated, or nil to enumerate all properties.
	@param block A block object that executes for each property in the properties set.
 */
- (void) enumerateValuesForProperties:(NSSet<NSString *> * _Nullable) properties usingBlock: (void (^)(NSString *property, id value, BOOL *stop)) block;

/*!
	@abstract Executes a provided block with the fetched values for all properties in the entity except for the provided set.
	@discussion Use this method to get property values in a batch fashion. 
				In some cases, enumerating over a set of property keys can be more efficient 
				than fetching each individual property with valueForProperty:.
				The media property keys you can use with this property are listed in this document 
				and in Media Item Property Keys and Playlist Property Keys.
	@param properties A set of property keys that should NOT be enumerated, or nil to enumerate all properties.
	@param block A block object that executes for each property except for the ones in the properties set.
 */
- (void) enumerateValuesExceptForProperties:(NSSet<NSString *> * _Nullable) properties usingBlock: (void (^)(NSString *property, id value, BOOL *stop)) block;

@end

ITLIB_EXPORT ITLIB_EXTERN NSString * const ITLibMediaEntityPropertyPersistentID;

NS_ASSUME_NONNULL_END

/*!
	@file		ITLibrary.h
	@copyright	© 2012-2016 Apple Inc.
*/

#import <Foundation/Foundation.h>
#import <iTunesLibrary/ITLibDefines.h>

NS_ASSUME_NONNULL_BEGIN

// Forward declaration.
@class ITLibMediaItem;

// Forward declaration.
@class ITLibPlaylist;

// Forward declaration.
@class ITLibArtwork;

// Forward declaration.
@class ITLibLibraryData;

/*!
    @enum           ITLibExportFeature
    @abstract       These constants describe the features supported by a given iTunes library.
    @constant       ITLibExportFeatureNone
                        No features are supported
*/
typedef NS_ENUM( NSUInteger, ITLibExportFeature )
{
    ITLibExportFeatureNone = 0

} API_UNAVAILABLE(ios);

/*!
 @enum           ITLibInitOptions
 @abstract       These constants describe the options that can be passed supported by a given iTunes library.
 @constant       ITLibExportFeatureNone
 No features are supported
 */
typedef NS_ENUM( NSUInteger, ITLibInitOptions )
{
	ITLibInitOptionNone = 0,
	
	/*! ITLibrary will be initialized but no iTunes library data will be loaded. Data will be lazy-loaded upon request. */
	ITLibInitOptionLazyLoadData = 1

} API_UNAVAILABLE(ios);

/*! 
	@abstract A class representing an iTunes library whose metadata is being queried.
*/
API_UNAVAILABLE(ios)
ITLIB_EXPORT @interface ITLibrary : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*! @abstract The version of iTunes being accessed. */
@property (nonatomic, readonly, copy) NSString* applicationVersion;

/*! @abstract A bitwise OR combination of the features of this library. */
@property (nonatomic, readonly, assign) ITLibExportFeature features;

/*! @abstract The major version number of this API. */
@property (nonatomic, readonly, assign) NSUInteger apiMajorVersion;

/*! @abstract The minor version number of this API. */
@property (nonatomic, readonly, assign) NSUInteger apiMinorVersion;

/*! @abstract The location of the iTunes music folder. */
@property (nonatomic, readonly, copy, nullable) NSURL* mediaFolderLocation ITLIB_AVAILABLE(12.5.2);

/*! @abstract The location of the iTunes music folder. Replaced by mediaFolderLocation. */
@property (nonatomic, readonly, copy, nullable) NSURL* musicFolderLocation;

/*! @abstract Whether to show content rating labels. */
@property (nonatomic, readonly, assign, getter = shouldShowContentRating) BOOL showContentRating;

/*! @abstract All media items in the library. */
@property (nonatomic, readonly, retain) NSArray<ITLibMediaItem *> * allMediaItems;

/*! @abstract All playlists in the library. */
@property (nonatomic, readonly, retain) NSArray<ITLibPlaylist *> * allPlaylists;

/*!
	@abstract Creates and initializes an instance of ITLibrary which can be used to retrieve media entities.
	@discussion Upon initialization of the ITLibrary class, the default iTunes database for the current user will be read and parsed. 
				At this point all media entities will be cached in memory until the time the object is deallocated.
	@param requestedAPIVersion The version of the iTunesLibrary API that the application is requesting, provide "1.0" if unknown.
	@param error A pointer to a variable that will receive an NSError if this method fails. May be nil if caller does not care about error.
	@return An ITLibrary instance, or nil if this method fails.
 */
+ (nullable instancetype)libraryWithAPIVersion:(NSString*)requestedAPIVersion error:(NSError **)error;

/*!
	@abstract Creates and initializes an instance of ITLibrary which can be used to retrieve media entities.
 	@discussion Unless the ITLibInitOptionLazyLoadData option is specified, the default iTunes database for the current user will be
 				read and parsed upon initialization of the ITLibrary class, and all media entities will be cached in memory.
	@param requestedAPIVersion The version of the iTunesLibrary API that the application is requesting, provide "1.0" if unknown.
 	@param options Options that change the initialization behavior.
	@param error A pointer to a variable that will receive an NSError if this method fails. May be nil if caller does not care about error.
	@return An ITLibrary instance, or nil if this method fails.
 */
+ (nullable instancetype)libraryWithAPIVersion:(NSString*)requestedAPIVersion options:(ITLibInitOptions)options error:(NSError **)error API_AVAILABLE(macos(10.14));

/*!
	@abstract Initializes an instance of ITLibrary which can be used to retrieve media entities.
	@discussion Upon initialization of the ITLibrary class, the default iTunes database for the current user will be read and parsed. 
				At this point all media entities will be cached in memory until the time the object is deallocated.
	@param requestedAPIVersion The version of the iTunesLibrary API that the application is requesting, provide "1.0" if unknown.
	@param error A pointer to a variable that will receive an NSError if this method fails. May be nil if caller does not care about error.
	@return An ITLibrary instance, or nil if this method fails.
 */
- (nullable instancetype)initWithAPIVersion:(NSString*)requestedAPIVersion error:(NSError **)error;

/*!
	@abstract Initializes an instance of ITLibrary which can be used to retrieve media entities.
	@discussion Unless the ITLibInitOptionLazyLoadData option is specified, the default iTunes database for the current user will be
 				read and parsed upon initialization of the ITLibrary class, and all media entities will be cached in memory.
	@param requestedAPIVersion The version of the iTunesLibrary API that the application is requesting, provide "1.0" if unknown.
 	@param options Options that change the initialization behavior.
	@param error A pointer to a variable that will receive an NSError if this method fails. May be nil if caller does not care about error.
	@return An ITLibrary instance, or nil if this method fails.
 */
- (nullable instancetype)initWithAPIVersion:(NSString*)requestedAPIVersion options:(ITLibInitOptions)options error:(NSError **)error API_AVAILABLE(macos(10.14)) NS_DESIGNATED_INITIALIZER;

/*! 
	@abstract Retrieves the artwork from a media file. 
	@param mediaFileURL The URL of the media file whose artwork should be extracted.
	@return A ITLibArtwork instance represeting the media file artwork, or nil if the artwork was not found or could not be extracted.
 */
- (nullable ITLibArtwork*)artworkForMediaFile:(NSURL*)mediaFileURL;

/*!
	@abstract Refreshes the data used by the framework.
	@return YES if the data was reloaded, false if an error occurred.
 */
- (BOOL)reloadData;

/*!
 	@abstract Unloads the data used by the framework.
 */
- (void)unloadData API_AVAILABLE(macos(10.14));

@end

NS_ASSUME_NONNULL_END

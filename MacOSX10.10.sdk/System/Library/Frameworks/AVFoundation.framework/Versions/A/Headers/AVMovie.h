/*
	File:			AVMovie.h

	Framework:		AVFoundation
 
	Copyright 2006-2014 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>

#import <AVFoundation/AVAsset.h>
#import <AVFoundation/AVMovieTrack.h>

/*!
    @class			AVMovie

    @abstract		AVMovie represents the audiovisual containers in a file that conforms to the QuickTime movie file format or to one of the related ISO base media file formats (such as MPEG-4).

	@discussion     Generally you do not need to use AVMovie to open and play QuickTime movie files or ISO base media files. Instead you can use AVURLAsset.
 
*/

// Keys for options dictionary for use with various AVMovie initialization methods

/*!
  @constant		AVMovieReferenceRestrictionsKey
  @abstract
	Indicates the restrictions used by the movie when resolving references to external media data. The value of this key is an NSNumber wrapping an AVAssetReferenceRestrictions enum value or the logical combination of multiple such values. See AVAsset.h for the declaration of the AVAssetReferenceRestrictions enum.
  @discussion
	Some movies can contain references to media data stored outside the movie's container, for example in another file. This key can be used to specify a policy to use when these references are encountered. If a movie contains one or more references of a type that is forbidden by the reference restrictions, loading of movie properties will fail. In addition, such a movie cannot be used with other AVFoundation modules, such as AVPlayerItem or AVAssetExportSession.
*/
AVF_EXPORT NSString *const AVMovieReferenceRestrictionsKey NS_AVAILABLE(10_10, TBD);


@class AVMovieInternal;

#pragma mark --- AVMovie ---
NS_CLASS_AVAILABLE(10_10, TBD)
@interface AVMovie : AVAsset
{
@private
	AVMovieInternal *_movie;
}

/*!
	@method			movieTypes
	@abstract		Provides the file types the AVMovie class understands.
	@result			An NSArray of UTIs identifying the file types the AVMovie class understands.
*/
+ (NSArray *)movieTypes;

/*!
	@method			movieWithURL:options:
	@abstract		Creates an AVMovie object from a movie header stored in a QuickTime movie file or ISO base media file.
	@param			URL
					An NSURL object that specifies a file containing a movie header.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMovie object. Currently no keys are defined.
	@result			An AVMovie object
*/
+ (instancetype)movieWithURL:(NSURL *)URL options:(NSDictionary *)options;

/*!
	@method			initWithURL:options:
	@abstract		Creates an AVMovie object from a movie header stored in a QuickTime movie file or ISO base media file.
	@param			URL
					An NSURL object that specifies a file containing a movie header.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMovie object. Currently no keys are defined.
	@result			An AVMovie object
*/
- (instancetype)initWithURL:(NSURL *)URL options:(NSDictionary *)options;

/*!
	@property       URL
	@abstract       The URL with which the instance of AVMovie was initialized; may be nil.
*/
@property (nonatomic, readonly) NSURL *URL;

/*!
	@property       tracks
	@abstract       The tracks in a movie.
	@discussion     The value of this property is an array of tracks the movie contains; the tracks are of type AVMovieTrack.
*/
@property (nonatomic, readonly) NSArray *tracks;

/*!
	@property       canContainMovieFragments
	@abstract       Indicates whether the movie file is capable of being extended by fragments.
	@discussion     The value of this property is YES if an 'mvex' box is present in the 'moov' box. The 'mvex' box is necessary in order to signal the possible presence of later 'moof' boxes.
*/
@property (nonatomic, readonly) BOOL canContainMovieFragments;

@end


#pragma mark --- AVFragmentedMovie ---
/*!
	@class			AVFragmentedMovie
 
	@abstract		A subclass of AVMovie for handling fragmented movie files. An AVFragmentedMovie is capable of changing the values of certain of its properties and those of its tracks, if it's associated with an instance of AVFragmentedMovieMinder when one or more movie fragments are appended to the movie file.
*/

/*!
 @constant       AVFragmentedMovieDurationDidChangeNotification
 @abstract       Posted when the duration of an AVFragmentedMovie changes while it's being minded by an AVFragmentedMovieMinder, but only for changes that occur after the status of the value of @"duration" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVFragmentedMovieDurationDidChangeNotification NS_AVAILABLE(10_10, TBD);

/*!
 @constant       AVFragmentedMovieWasDefragmentedNotification
 @abstract       Posted when the movie file on disk is defragmented while an AVFragmentedMovie is being minded by an AVFragmentedMovieMinder, but only if the defragmentation occurs after the status of the value of @"canContainMovieFragments" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVFragmentedMovieWasDefragmentedNotification NS_AVAILABLE(10_10, TBD);

@class AVFragmentedMovieInternal;

NS_CLASS_AVAILABLE(10_10, TBD)
@interface AVFragmentedMovie : AVMovie
{
	AVFragmentedMovieInternal	*_fragmentedMovie;
}

/*!
	@property       tracks
	@abstract       The tracks in a movie.
	@discussion     The value of this property is an array of tracks the movie contains; the tracks are of type AVFragmentedMovieTrack.
*/
@property (nonatomic, readonly) NSArray *tracks;

@end

#pragma mark --- AVFragmentedMovieMinder ---
/*!
	@class			AVFragmentedMovieMinder
	@abstract		A class that periodically checks whether additional movie fragments have been appended to fragmented movie files.
*/

@class AVFragmentedMovieMinderInternal;

NS_CLASS_AVAILABLE(10_10, TBD)
@interface AVFragmentedMovieMinder : NSObject
{
@private
	AVFragmentedMovieMinderInternal	*_fragmentedMovieMinder;
}

/*!
	@method			fragmentedMovieMinderWithMovie:mindingInterval:
	@abstract       Creates an AVFragmentedMovieMinder, adds the specified movie to it, and sets the mindingInterval to the specified value.
	@param			movie
					An instance of AVFragmentedMovie to add to the AVFragmentedMovieMinder
	@param			mindingInterval
					The initial minding interval of the AVFragmentedMovieMinder.
	@result			A new instance of AVFragmentedMovieMinder.
*/
+ (instancetype)fragmentedMovieMinderWithMovie:(AVFragmentedMovie *)movie mindingInterval:(NSTimeInterval)mindingInterval;

/*!
	@method			initWithMovie:mindingInterval:
	@abstract       Creates an AVFragmentedMovieMinder, adds the specified movie to it, and sets the mindingInterval to the specified value.
	@param			movie
					An instance of AVFragmentedMovie to add to the AVFragmentedMovieMinder
	@param			mindingInterval
					The initial minding interval of the AVFragmentedMovieMinder.
	@result			A new instance of AVFragmentedMovieMinder.
*/
- (instancetype)initWithMovie:(AVFragmentedMovie *)movie mindingInterval:(NSTimeInterval)mindingInterval;

/*!
	@property       mindingInterval
	@abstract       An NSTimeInterval indicating how often a check for additional movie fragments should be performed. The default interval is 10.0.
*/
@property (nonatomic) NSTimeInterval mindingInterval;

/*!
	@property       movies
	@abstract       An NSArray of the AVFragmentedMovie objects being minded.
*/
@property (nonatomic, readonly) NSArray *movies;

/*!
	@method			addFragmentedMovie:
	@abstract		Adds a fragmented movie to the array of movies being minded.
	@param			movie
					The fragmented movie to add to the minder.
*/
- (void)addFragmentedMovie:(AVFragmentedMovie *)movie;

/*!
	@method			removeFragmentedMovie:
	@abstract		Removes a fragmented movie from the array of movies being minded.
	@param			movie
					The fragmented movie to remove from the minder.
*/
- (void)removeFragmentedMovie:(AVFragmentedMovie *)movie;

@end

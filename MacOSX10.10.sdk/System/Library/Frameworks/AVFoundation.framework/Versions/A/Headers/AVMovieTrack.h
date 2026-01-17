/*
	File:			AVMovieTrack.h

	Framework:		AVFoundation
 
	Copyright 2006-2014 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>

#import <AVFoundation/AVAssetTrack.h>
#import <AVFoundation/AVMovie.h>

/*!
    @class			AVMovieTrack

    @abstract		AVMovieTrack represents the tracks of audiovisual containers in a file that conforms to the QuickTime movie file format or to one of the related ISO base media file formats (such as MPEG-4).
*/

@class AVMovieTrackInternal;
@class AVMediaDataStorage;

#pragma mark --- AVMovieTrack ---
NS_CLASS_AVAILABLE(10_10, TBD)
@interface AVMovieTrack : AVAssetTrack {
    AVMovieTrackInternal    *_movieTrackInternal;
}

@end


/*!
	@class			AVFragmentedMovieTrack
	@abstract		A subclass of AVMovieTrack for handling tracks of fragmented movie files. An AVFragmentedMovieTrack is capable of changing the values of certain of its properties, if its parent movie is associated with an instance of AVFragmentedMovieMinder when one or more movie fragments are appended to the movie file.
*/

/*!
 @constant       AVFragmentedMovieTrackTimeRangeDidChangeNotification
 @abstract       Posted when the timeRange of an AVFragmentedMovieTrack changes while the associated instance of AVFragmentedMovie is being minded by an AVFragmentedMovieMinder, but only for changes that occur after the status of the value of @"timeRange" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVFragmentedMovieTrackTimeRangeDidChangeNotification NS_AVAILABLE(10_10, TBD);

/*!
 @constant       AVFragmentedMovieTrackSegmentsDidChangeNotification
 @abstract       Posted when the array of segments of an AVFragmentedMovieTrack changes while the associated instance of AVFragmentedMovie is being minded by an AVFragmentedMovieMinder, but only for changes that occur after the status of the value of @"segments" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVFragmentedMovieTrackSegmentsDidChangeNotification NS_AVAILABLE(10_10, TBD);

/*!
 @constant       AVFragmentedMovieTrackTotalSampleDataLengthDidChangeNotification
 @abstract       Posted when the totalSampleDataLength of an AVFragmentedMovieTrack movie changes while the associated instance of AVFragmentedMovie is being minded by an AVFragmentedMovieMinder, but only for changes that occur after the status of the value of @"totalSampleDataLength" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVFragmentedMovieTrackTotalSampleDataLengthDidChangeNotification NS_AVAILABLE(10_10, TBD);

@class AVFragmentedMovieTrackInternal;

#pragma mark --- AVFragmentedMovieTrack ---
NS_CLASS_AVAILABLE(10_10, TBD)
@interface AVFragmentedMovieTrack : AVMovieTrack
{
	AVFragmentedMovieTrackInternal	*_fragmentedMovieTrack;
}

@end




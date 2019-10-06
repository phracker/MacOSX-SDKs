/*
	File:  AVCompositionTrackSegment.h

	Framework:  AVFoundation
 
	Copyright 2010-2015 Apple Inc. All rights reserved.

*/

/*!
	@class			AVCompositionTrackSegment

	@abstract		AVCompositionTrackSegment represents a segment of an AVCompositionTrack, comprising
					a URL, and track identifier, and a time mapping from the source track to the composition
					track.
	
	@discussion		This class is most useful for clients that want to save the low-level representation of
					a composition to storage formats of their choosing and reconstitute them from storage.	
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAssetTrackSegment.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTimeRange.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCompositionTrackSegmentInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0))
@interface AVCompositionTrackSegment : AVAssetTrackSegment
{
@private
	AVCompositionTrackSegmentInternal	*_priv;
}

/*!
	@method			compositionTrackSegmentWithURL:trackID:sourceTimeRange:targetTimeRange:
	@abstract		Returns an instance of AVCompositionTrackSegment that presents a portion of a file referenced by URL.
	@param			URL
					An instance of NSURL that references the container file to be presented by the AVCompositionTrackSegment.
	@param			trackID
					The track identifier that specifies the track of the container file to be presented by the AVCompositionTrackSegment.
	@param			sourceTimeRange
					The timeRange of the track of the container file to be presented by the AVCompositionTrackSegment.
	@param			targetTimeRange
					The timeRange of the composition track during which the AVCompositionTrackSegment is to be presented.
	@result			An instance of AVCompositionTrackSegment.
	@discussion		To specify that the segment be played at the asset's normal rate, set source.duration == target.duration in the timeMapping.
					Otherwise, the segment will be played at a rate equal to the ratio source.duration / target.duration.
*/
+ (instancetype)compositionTrackSegmentWithURL:(NSURL *)URL trackID:(CMPersistentTrackID)trackID sourceTimeRange:(CMTimeRange)sourceTimeRange targetTimeRange:(CMTimeRange)targetTimeRange;

/*!
	@method			compositionTrackSegmentWithTimeRange:
	@abstract		Returns an instance of AVCompositionTrackSegment that presents an empty track segment.
	@param			timeRange
					The timeRange of the empty AVCompositionTrackSegment.
	@result			An instance of AVCompositionTrackSegment.
*/
+ (instancetype)compositionTrackSegmentWithTimeRange:(CMTimeRange)timeRange;

/*!
	@method			initWithURL:trackID:sourceTimeRange:targetTimeRange:
	@abstract		Initializes an instance of AVCompositionTrackSegment that presents a portion of a file referenced by URL.
	@param			URL
					An instance of NSURL that references the container file to be presented by the AVCompositionTrackSegment.
	@param			trackID
					The track identifier that specifies the track of the container file to be presented by the AVCompositionTrackSegment.
	@param			sourceTimeRange
					The timeRange of the track of the container file to be presented by the AVCompositionTrackSegment.
	@param			targetTimeRange
					The timeRange of the composition track during which the AVCompositionTrackSegment is to be presented.
	@result			An instance of AVCompositionTrackSegment.
	@discussion		To specify that the segment be played at the asset's normal rate, set source.duration == target.duration in the timeMapping.
					Otherwise, the segment will be played at a rate equal to the ratio source.duration / target.duration.
*/
- (instancetype)initWithURL:(NSURL *)URL trackID:(CMPersistentTrackID)trackID sourceTimeRange:(CMTimeRange)sourceTimeRange targetTimeRange:(CMTimeRange)targetTimeRange NS_DESIGNATED_INITIALIZER;

/*!
	@method			initWithTimeRange:
	@abstract		Initializes an instance of AVCompositionTrackSegment that presents an empty track segment.
	@param			timeRange
					The timeRange of the empty AVCompositionTrackSegment.
	@result			An instance of AVCompositionTrackSegment.
*/
- (instancetype)initWithTimeRange:(CMTimeRange)timeRange NS_DESIGNATED_INITIALIZER;

/* indicates whether the AVCompositionTrackSegment is an empty segment;
   an empty segment has a valid target time range but nil sourceURL and kCMTimeInvalid source start time; all other fields are undefined */
@property (nonatomic, readonly, getter=isEmpty) BOOL empty;

/* indicates the container file of the media presented by the AVCompositionTrackSegment */
@property (nonatomic, readonly, nullable) NSURL *sourceURL;

/* indicates the track of the container file of the media presented by the AVCompositionTrackSegment */
@property (nonatomic, readonly) CMPersistentTrackID sourceTrackID;

@end

NS_ASSUME_NONNULL_END

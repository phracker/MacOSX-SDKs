/*
	File:  AVComposition.h

	Framework:  AVFoundation
 
	Copyright 2010-2013 Apple Inc. All rights reserved.

*/

/*!
    @class			AVComposition

    @abstract		An AVComposition combines media data from multiple local file-based sources in a custom temporal arrangement,
    				in order to present or process media data from multiple sources together. All local file-based audiovisual 
    				assets are eligible to be combined, regardless of container type.
	
	@discussion		At its top-level, AVComposition is a collection of tracks, each presenting media of a specific media type,
					e.g. audio or video, according to a timeline. Each track is represented by an instance of AVCompositionTrack.

					Each track is comprised of an array of track segments, each of which present a portion of the media data
					stored in a source container, specified by URL, a track identifier, and a time mapping, as represented by
					an instance of AVCompositionTrackSegment.
					The URL specifies the source container, and the track identifier indicates the track of the source container
					to be presented.
					The time mapping specifies the temporal range of the source track that's to be presented and also specifies
					the temporal range of its presentation in the composition track. If the durations of the source and destination
					ranges of the time mapping are the same, the media data for the segment will be presented at its natural rate.
					Otherwise, the segment will be presented at a rate equal to the ratio source.duration / target.duration.
					
					The track segments of a track are available via AVCompositionTrack's trackSegment property, an array of
					AVCompositionTrackSegment. The collection of tracks with media type information for each, and each with its
					array of track segments (URL, track identifier, and time mapping), form a complete low-level representation
					of a composition.
					This representation can be written out by clients in any convenient form, and subsequently the
					composition can be reconstituted by instantiating a new AVMutableComposition with AVMutableCompositionTracks
					of the appropriate media type, each with its trackSegment property set according to the stored array of
					URL, track identifier, and time mapping.
					
					A higher-level interface for constructing compositions is also presented by AVMutableComposition
					and AVMutableCompositionTrack, offering insertion, removal, and scaling operations without direct
					manipulation of the trackSegment arrays of composition tracks. This interface makes use of higher-level
					constructs such as AVAsset and AVAssetTrack, allowing the client to make use of the same references to
					candidate sources that it would have created in order to inspect or preview them prior to inclusion
					in a composition.

					Implementation note: to make an immutable snapshot of a mutable composition for playback or inspection --
					
					// myMutableComposition is a mutable composition; the client wants to inspect and play it in its current state
					AVComposition *immutableSnapshotOfMyComposition = [myMutableComposition copy];
				
					// inspect and play at will, e.g.
					AVPlayerItem *playerItemForSnapshottedComposition = [[AVPlayerItem alloc] initWithAsset:immutableSnapshotOfMyComposition];
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVAsset.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>

@class AVCompositionTrack;
@class AVMutableCompositionTrack;
@class AVCompositionInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVComposition : AVAsset <NSMutableCopying>
{
@private
	AVCompositionInternal	*_priv;
}

/* provides the array of AVCompositionTracks contained by the composition */
@property (nonatomic, readonly) NSArray *tracks;

/*	indicates the authored size of the visual portion of the composition */
@property (nonatomic, readonly) CGSize naturalSize;

@end


@class AVAssetTrack;
@class AVMutableCompositionTrack;
@class AVMutableCompositionInternal;


NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVMutableComposition : AVComposition
{
@private
    AVMutableCompositionInternal    *_mutablePriv;
}

/* provides the array of AVMutableCompositionTracks contained by the composition */
@property (nonatomic, readonly) NSArray *tracks;

/* Indicates the authored size of the visual portion of the asset.
   If not set, the default behavior is to provide the size of the composition's first video track.
   Set to CGSizeZero to revert to default behavior. */
@property (nonatomic) CGSize naturalSize;

/*!
	@method			composition
	@abstract		Returns an empty AVMutableComposition.
*/
+ (AVMutableComposition *)composition;

@end

    
@interface AVMutableComposition (AVMutableCompositionCompositionLevelEditing)

/*!
	@method			insertTimeRange:ofAsset:atTime:error:
	@abstract		Inserts all the tracks of a timeRange of an asset into a composition.
	@param			timeRange
					Specifies the timeRange of the asset to be inserted.
	@param			asset
					Specifies the asset that contains the tracks that are to be inserted. Only instances of AVURLAsset are supported.
	@param			startTime
					Specifies the time at which the inserted tracks are to be presented by the composition.
	@param			outError
					Describes failures that may be reported to the user, e.g. the asset
					that was selected for insertion in the composition is restricted by copy-protection.
	@result			A BOOL value indicating the success of the insertion.
	@discussion	
		You provide a reference to an AVAsset and the timeRange within it that you want to insert.  
		You specify the start time in the destination composition at which the timeRange should be inserted.
		
		This method may add new tracks to ensure that all tracks of the asset are represented 
		in the inserted timeRange.
		
		Note that the media data for the inserted timeRange will be presented at its natural duration and rate. It can be
		scaled to a different duration and presented at a different rate via -scaleTimeRange:toDuration:.
		
		Existing content at the specified startTime will be pushed out by the duration of timeRange. 
*/
- (BOOL)insertTimeRange:(CMTimeRange)timeRange ofAsset:(AVAsset *)asset atTime:(CMTime)startTime error:(NSError **)outError;

/*!
	@method			insertEmptyTimeRange:
	@abstract		Adds or extends an empty timeRange within all tracks of the composition.
	@param			timeRange
					Specifies the empty timeRange to be inserted.
	@discussion	
		If you insert an empty timeRange into the composition, any media that was presented
		during that interval prior to the insertion will be presented instead immediately
		afterward. You can use this method to reserve an interval in which you want a subsequently
		created track to present its media.
*/
- (void)insertEmptyTimeRange:(CMTimeRange)timeRange;

/*!
	@method			removeTimeRange:
	@abstract		Removes a specified timeRange from all tracks of the composition.
	@param			timeRange
					Specifies the timeRange to be removed.
	@discussion
		Removal of a time range does not cause any existing tracks to be removed from the composition, 
		even if removing timeRange results in an empty track.
		Instead, it removes or truncates track segments that intersect with the timeRange.

		After removing, existing content after timeRange will be pulled in.
*/
- (void)removeTimeRange:(CMTimeRange)timeRange;

/*!
	@method			scaleTimeRange:toDuration:
	@abstract		Changes the duration of a timeRange of all tracks.
	@param			timeRange
					Specifies the timeRange of the composition to be scaled.
	@param			duration
					Specifies the new duration of the timeRange.
	@discussion
		Each trackSegment affected by the scaling operation will be presented at a rate equal to
		source.duration / target.duration of its resulting timeMapping.
*/
- (void)scaleTimeRange:(CMTimeRange)timeRange toDuration:(CMTime)duration;

@end


@interface AVMutableComposition (AVMutableCompositionTrackLevelEditing)

/*!
	@method			addMutableTrackWithMediaType:preferredTrackID:
	@abstract		Adds an empty track to a mutable composition.
	@param			mediaType
					The media type of the new track.
	@param			preferredTrackID
					Specifies the preferred track ID for the new track.
					The preferred track ID will be used for the new track provided that it is not currently in use and 
					has not previously been used.
					If you do not need to specify a preferred track ID, pass kCMPersistentTrackID_Invalid.
					If the specified preferred track ID is not available, or kCMPersistentTrackID_Invalid was passed in,
					a unique track ID will be generated.
	@result			An instance of AVMutableCompositionTrack representing the new track.
    				Its actual trackID is available via its @"trackID" key.
*/
- (AVMutableCompositionTrack *)addMutableTrackWithMediaType:(NSString *)mediaType preferredTrackID:(CMPersistentTrackID)preferredTrackID;

/*!
	@method			removeTrack:
	@abstract		Removes a track of a mutable composition.
	@param			track
					A reference to the AVCompositionTrack to be removed.
	@discussion
		If you retain a reference to the removed track, note that its @"composition" key will have the value nil, and
		the values of its other properties are undefined.
*/
- (void)removeTrack:(AVCompositionTrack *)track;

/*!
	@method			mutableTrackCompatibleWithTrack:
	@abstract		Provides a reference to a track of a mutable composition into which any timeRange of an AVAssetTrack
					can be inserted (via -[AVMutableCompositionTrack insertTimeRange:ofTrack:atTime:error:]).
	@param			track
					A reference to the AVAssetTrack from which a timeRange may be inserted.
	@result			An AVMutableCompositionTrack that can accommodate the insertion.
					If no such track is available, the result is nil. A new track of the same mediaType
					as the AVAssetTrack can be created via -addMutableTrackWithMediaType:preferredTrackID:,
					and this new track will be compatible.
	@discussion		Similar to -[AVAsset compatibleTrackForCompositionTrack:].
		For best performance, the number of tracks of a composition should be kept to a minimum, corresponding to the
		number for which media data must be presented in parallel. If media data of the same type is to be presented
		serially, even from multiple assets, a single track of that media type should be used. This method,
		-mutableTrackCompatibleWithTrack:, can help the client to identify an existing target track for an insertion.
*/
- (AVMutableCompositionTrack *)mutableTrackCompatibleWithTrack:(AVAssetTrack *)track;

@end

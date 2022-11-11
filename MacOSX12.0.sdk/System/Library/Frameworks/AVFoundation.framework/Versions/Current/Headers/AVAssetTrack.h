#if !__has_include(<AVFCore/AVAssetTrack.h>)
/*
	File:  AVAssetTrack.h

	Framework:  AVFoundation
 
	Copyright 2010-2021 Apple Inc. All rights reserved.

*/

/*!
	@class		AVAssetTrack
 
	@abstract	An AVAssetTrack object provides provides the track-level inspection interface for all assets.
 
	@discussion
		AVAssetTrack adopts the AVAsynchronousKeyValueLoading protocol. Methods in the protocol should be used to access a track's properties without blocking the current thread. To cancel load requests for all keys of AVAssetTrack one must message the parent AVAsset object (for example, [track.asset cancelLoading]).
 
		For clients who want to examine a subset of the metadata or other parts of the track, asynchronous methods like -loadMetadataForFormat:completionHandler: can be used to load this information without blocking. When using these asynchronous methods, it is not necessary to load the associated property beforehand. Swift clients can also use the load(:) method to load properties in a type safe manner.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>
#import <AVFoundation/AVAsset.h>
#import <AVFoundation/AVAssetTrackSegment.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVMetadataFormat.h>
#import <CoreMedia/CMTimeRange.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAssetTrackInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0))
@interface AVAssetTrack : NSObject <NSCopying, AVAsynchronousKeyValueLoading>
{
@private
	AVAssetTrackInternal     *_track;
}
AV_INIT_UNAVAILABLE

/* provides a reference to the AVAsset of which the AVAssetTrack is a part  */
@property (nonatomic, readonly, weak) AVAsset *asset;

/* indicates the persistent unique identifier for this track of the asset  */
@property (nonatomic, readonly) CMPersistentTrackID trackID;

/* Note that cancellation of loading requests for all keys of AVAssetTrack must be made on the parent AVAsset, e.g. [[track.asset] cancelLoading] */

@end


@interface AVAssetTrack (AVAssetTrackBasicPropertiesAndCharacteristics)

/* indicates the media type for this track, e.g. AVMediaTypeVideo, AVMediaTypeAudio, etc., as defined in AVMediaFormat.h. */
@property (nonatomic, readonly) AVMediaType mediaType;

/* provides an array of CMFormatDescriptions
   each of which indicates the format of media samples referenced by the track;
   a track that presents uniform media, e.g. encoded according to the same encoding settings,
   will provide an array with a count of 1 */
@property (nonatomic, readonly) NSArray *formatDescriptions;

/* Indicates whether the receiver is playable in the current environment; if YES, an AVPlayerItemTrack of an AVPlayerItem initialized with the receiver's asset can be enabled for playback.  */
@property (nonatomic, readonly, getter=isPlayable) BOOL playable API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

/* Indicates whether the receiver is decodable in the current environment; if YES, the track can be decoded even though decoding may be too slow for real time playback.  */
@property (nonatomic, readonly, getter=isDecodable) BOOL decodable API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/* indicates whether the track is enabled according to state stored in its container or construct;
   note that its presentation state can be changed from this default via AVPlayerItemTrack */
@property (nonatomic, readonly, getter=isEnabled) BOOL enabled;

/* indicates whether the track references sample data only within its storage container */
@property (nonatomic, readonly, getter=isSelfContained) BOOL selfContained;

/* indicates the total number of bytes of sample data required by the track */
@property (nonatomic, readonly) long long totalSampleDataLength;

/*!
	@method			hasMediaCharacteristic:
	@abstract		Reports whether the track references media with the specified media characteristic.
	@param			mediaCharacteristic
					The media characteristic of interest, e.g. AVMediaCharacteristicVisual, AVMediaCharacteristicAudible, AVMediaCharacteristicLegible, etc.,
					as defined above.
	@result			YES if the track references media with the specified characteristic, otherwise NO.
*/
- (BOOL)hasMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic;

@end


@interface AVAssetTrack (AVAssetTrackTemporalProperties)

/* Indicates the timeRange of the track within the overall timeline of the asset;
   a track with CMTIME_COMPARE_INLINE(timeRange.start, >, kCMTimeZero) will initially present an empty interval. */
@property (nonatomic, readonly) CMTimeRange timeRange;

/*	indicates a timescale in which time values for the track can be operated upon without extraneous numerical conversion  */
@property (nonatomic, readonly) CMTimeScale naturalTimeScale;

/* indicates the estimated data rate of the media data referenced by the track, in units of bits per second */
@property (nonatomic, readonly) float estimatedDataRate;

@end


@interface AVAssetTrack (AVAssetTrackLanguageProperties)

/* indicates the language associated with the track, as an ISO 639-2/T language code;
   may be nil if no language is indicated */
@property (nonatomic, readonly, nullable) NSString *languageCode;

/* indicates the language tag associated with the track, as an IETF BCP 47 (RFC 4646) language identifier;
   may be nil if no language tag is indicated */
@property (nonatomic, readonly, nullable) NSString *extendedLanguageTag;

@end


@interface AVAssetTrack (AVAssetTrackPropertiesForVisualCharacteristic)

/* indicates the natural dimensions of the media data referenced by the track as a CGSize */
@property (nonatomic, readonly) CGSize naturalSize;

/* indicates the transform specified in the track's storage container as the preferred transformation of the visual media data for display purposes;
   its value is often but not always CGAffineTransformIdentity */
@property (nonatomic, readonly) CGAffineTransform preferredTransform;

@end


@interface AVAssetTrack (AVAssetTrackPropertiesForAudibleCharacteristic)

/* indicates the volume specified in the track's storage container as the preferred volume of the audible media data */
@property (nonatomic, readonly) float preferredVolume;

/* indicates whether this audio track has dependencies (e.g. kAudioFormatMPEGD_USAC) */
@property (nonatomic, readonly) BOOL hasAudioSampleDependencies API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

@end


@interface AVAssetTrack (AVAssetTrackPropertiesForFrameBasedCharacteristic)

/*!
	@property		nominalFrameRate
	@abstract		For tracks that carry a full frame per media sample, indicates the frame rate of the track in units of frames per second.
	@discussion		For field-based video tracks that carry one field per media sample, the value of this property is the field rate, not the frame rate.
*/
@property (nonatomic, readonly) float nominalFrameRate;

/* indicates the minimum duration of the track's frames; the value will be kCMTimeInvalid if the minimum frame duration is not known or cannot be calculated */
@property (nonatomic, readonly) CMTime minFrameDuration API_AVAILABLE(macos(10.10), ios(7.0), tvos(9.0), watchos(1.0));

/*!
	@property       requiresFrameReordering
	@abstract       Indicates whether samples in the track may have different values for their presentation and decode timestamps.
*/
@property (nonatomic, readonly) BOOL requiresFrameReordering API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));

@end


@interface AVAssetTrack (AVAssetTrackSegments)

/* Provides an array of AVAssetTrackSegments with time mappings from the timeline of the track's media samples to the timeline of the track.
   Empty edits, i.e. timeRanges for which no media data is available to be presented, have a value of AVAssetTrackSegment.empty equal to YES. */
@property (nonatomic, copy, readonly) NSArray<AVAssetTrackSegment *> *segments;

/*!
	@method			segmentForTrackTime:
	@abstract		Supplies the AVAssetTrackSegment from the segments array with a target timeRange that either contains the specified track time or is the closest to it among the target timeRanges of the track's segments.
	@param			trackTime
					The trackTime for which an AVAssetTrackSegment is requested.
	@result			An AVAssetTrackSegment.
	@discussion		If the trackTime does not map to a sample presentation time (e.g. it's outside the track's timeRange), the segment closest in time to the specified trackTime is returned. 
*/
- (nullable AVAssetTrackSegment *)segmentForTrackTime:(CMTime)trackTime;

/*!
	@method			loadSegmentForTrackTime:completionHandler:
	@abstract		Loads the AVAssetTrackSegment from the segments array with a target timeRange that either contains the specified track time or is the closest to it among the target timeRanges of the track's segments.
	@param			trackTime
					The trackTime for which an AVAssetTrackSegment is requested.
	@param			completionHandler
					A block that is invoked when loading is complete, vending an AVAssetTrackSegment or an error.
	@discussion		If the trackTime does not map to a sample presentation time (e.g. it's outside the track's timeRange), the segment closest in time to the specified trackTime is returned.
*/
- (void)loadSegmentForTrackTime:(CMTime)trackTime completionHandler:(void (^)(AVAssetTrackSegment * _Nullable_result, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/*!
	@method			samplePresentationTimeForTrackTime:
	@abstract		Maps the specified trackTime through the appropriate time mapping and returns the resulting sample presentation time.
	@param			trackTime
					The trackTime for which a sample presentation time is requested.
	@result			A CMTime; will be invalid if the trackTime is out of range
*/
- (CMTime)samplePresentationTimeForTrackTime:(CMTime)trackTime;

/*!
	@method			loadSamplePresentationTimeForTrackTime:completionHandler:
	@abstract		Maps the specified trackTime through the appropriate time mapping and loads the resulting sample presentation time.
	@param			trackTime
					The trackTime for which a sample presentation time is requested.
	@param			completionHandler
					A block that is invoked when loading is complete, vending a CMTime (which will be invalid if the trackTime is out of range) or an error.
*/
- (void)loadSamplePresentationTimeForTrackTime:(CMTime)trackTime completionHandler:(void (^)(CMTime, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

@end


@interface AVAssetTrack (AVAssetTrackMetadataReading)

// high-level access to selected metadata of common interest

/* provides access to an array of AVMetadataItems for each common metadata key for which a value is available */
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *commonMetadata;

/* Provides access to an array of AVMetadataItems for all metadata identifiers for which a value is available; items can be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:] and according to identifier via +[AVMetadataItem metadataItemsFromArray:filteredByIdentifier:].
*/
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *metadata API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));

/* provides an NSArray of NSStrings, each representing a format of metadata that's available for the track (e.g. QuickTime userdata, etc.)
   Metadata formats are defined in AVMetadataItem.h. */
@property (nonatomic, readonly) NSArray<AVMetadataFormat> *availableMetadataFormats;

/*!
	@method			metadataForFormat:
	@abstract		Provides an NSArray of AVMetadataItems, one for each metadata item in the container of the specified format.
	@param			format
					The metadata format for which items are requested.
	@result			An NSArray containing AVMetadataItems.
	@discussion		Becomes callable without blocking when the key @"availableMetadataFormats" has been loaded
*/
- (NSArray<AVMetadataItem *> *)metadataForFormat:(AVMetadataFormat)format;

/*!
	@method			loadMetadataForFormat:completionHandler:
	@abstract		Loads an NSArray of AVMetadataItems, one for each metadata item in the container of the specified format.
	@param			format
					The metadata format for which items are requested.
	@param			completionHandler
					A block that is invoked when loading is complete, vending the array of metadata items (which may be empty if there is no metadata of the specified format) or an error.
*/
- (void)loadMetadataForFormat:(AVMetadataFormat)format completionHandler:(void (^)(NSArray<AVMetadataItem *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

@end


@interface AVAssetTrack (AVAssetTrackTrackAssociations)

/*!
 @typedef AVTrackAssociationType
 @abstract
    The type of a track association.
*/
typedef NSString * AVTrackAssociationType NS_STRING_ENUM;

/*
 @constant		AVTrackAssociationTypeAudioFallback
 @abstract		Indicates an association between an audio track with another audio track that contains the same content but is typically encoded in a different format that's more widely supported, used to nominate a track that should be used in place of an unsupported track.
 
 @discussion
	Associations of type AVTrackAssociationTypeAudioFallback are supported only between audio tracks.  This association is not symmetric; when used with -[AVAssetWriterInput addTrackAssociationWithTrackOfInput:type:], the receiver should be an instance of AVAssetWriterInput with a corresponding track that has content that's less widely supported, and the input parameter should be an instance of AVAssetWriterInput with a corresponding track that has content that's more widely supported.
	
	Example: Using AVTrackAssociationTypeAudioFallback, a stereo audio track with media subtype kAudioFormatMPEG4AAC could be nominated as the "fallback" for an audio track encoding the same source material but with media subtype kAudioFormatAC3 and a 5.1 channel layout.  This would ensure that all clients are capable of playing back some form of the audio.

 */
AVF_EXPORT AVTrackAssociationType const AVTrackAssociationTypeAudioFallback API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*
 @constant		AVTrackAssociationTypeChapterList
 @abstract		Indicates an association between a track with another track that contains chapter information.  The track containing chapter information may be a text track, a video track, or a timed metadata track.
 
 @discussion
	This association is not symmetric; when used with -[AVAssetWriterInput addTrackAssociationWithTrackOfInput:type:], the receiver should be an instance of AVAssetWriterInput with a corresponding track that has renderable content while the input parameter should be an instance of AVAssetWriterInput with a corresponding track that contains chapter metadata.
 */
AVF_EXPORT AVTrackAssociationType const AVTrackAssociationTypeChapterList API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*
 @constant		AVTrackAssociationTypeForcedSubtitlesOnly
 @abstract		Indicates an association between a subtitle track typically containing both forced and non-forced subtitles with another subtitle track that contains only forced subtitles, for use when the user indicates that only essential subtitles should be displayed.  When such an association is established, the forced subtitles in both tracks are expected to present the same content in the same language but may have different timing.
 
 @discussion
	Associations of type AVTrackAssociationTypeForcedSubtitlesOnly are supported only between subtitle tracks.  This association is not symmetric; when used with -[AVAssetWriterInput addTrackAssociationWithTrackOfInput:type:], the receiver should be an instance of AVAssetWriterInput with a corresponding subtitle track that contains non-forced subtitles, and the input parameter should be an instance of AVAssetWriterInput with a corresponding subtitle track that contains forced subtitles only.
 */
AVF_EXPORT AVTrackAssociationType const AVTrackAssociationTypeForcedSubtitlesOnly API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*
 @constant		AVTrackAssociationTypeSelectionFollower
 @abstract		Indicates an association between a pair of tracks that specifies that, when the first of the pair is selected, the second of the pair should be considered an appropriate default for selection also.  Example: a subtitle track in the same language as an audio track may be associated with that audio track using AVTrackAssociationTypeSelectionFollower, to indicate that selection of the subtitle track, in the absence of a directive for subtitle selection from the user, can "follow" the selection of the audio track.
 
 @discussion
	This association is not symmetric; when used with -[AVAssetWriterInput addTrackAssociationWithTrackOfInput:type:], the input parameter should be an instance of AVAssetWriterInput whose selection may depend on the selection of the receiver.  In the example above, the receiver would be the instance of AVAssetWriterInput corresponding with the audio track and the input parameter would be the instance of AVAssetWriterInput corresponding with the subtitle track.
 */
AVF_EXPORT AVTrackAssociationType const AVTrackAssociationTypeSelectionFollower API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*
 @constant		AVTrackAssociationTypeTimecode
 @abstract		Indicates an association between a track with another track that contains timecode information.  The track containing timecode information should be a timecode track.
 
 @discussion
	This association is not symmetric; when used with -[AVAssetWriterInput addTrackAssociationWithTrackOfInput:type:], the receiver should be an instance of AVAssetWriterInput with a corresponding track that may be a video track or an audio track while the input parameter should be an instance of AVAssetWriterInput with a corresponding timecode track.
 */
AVF_EXPORT AVTrackAssociationType const AVTrackAssociationTypeTimecode API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*
@constant		AVTrackAssociationTypeMetadataReferent
@abstract		Indicates an association between a metadata track and the track that's described or annotated via the contents of the metadata track.

@discussion
	This track association is optional for AVAssetTracks with the mediaType AVMediaTypeMetadata. When a metadata track lacks this track association, its contents are assumed to describe or annotate the asset as a whole.
	This association is not symmetric; when used with -[AVAssetWriterInput addTrackAssociationWithTrackOfInput:type:], the receiver should be an instance of AVAssetWriterInput with mediaType AVMediaTypeMetadata while the input parameter should be an instance of AVAssetWriterInput that's used to create the track to which the contents of the receiver's corresponding metadata track refer.
*/
AVF_EXPORT AVTrackAssociationType const AVTrackAssociationTypeMetadataReferent API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));

/* Provides an NSArray of NSStrings, each representing a type of track association that the receiver has with one or more of the other tracks of the asset (e.g. AVTrackAssociationTypeChapterList, AVTrackAssociationTypeTimecode, etc.).
   Track association types are defined immediately above. */
@property (nonatomic, readonly) NSArray<AVTrackAssociationType> *availableTrackAssociationTypes API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
	@method			associatedTracksOfType:
	@abstract		Provides an NSArray of AVAssetTracks, one for each track associated with the receiver with the specified type of track association.
	@param			trackAssociationType
					The type of track association for which associated tracks are requested.
	@result			An NSArray containing AVAssetTracks; may be empty if there is no associated tracks of the specified type.
	@discussion		Becomes callable without blocking when the key @"availableTrackAssociationTypes" has been loaded.
*/
- (NSArray<AVAssetTrack *> *)associatedTracksOfType:(AVTrackAssociationType)trackAssociationType API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

/*!
	@method			loadAssociatedTracksOfType:completionHandler:
	@abstract		Provides an NSArray of AVAssetTracks, one for each track associated with the receiver with the specified type of track association.
	@param			trackAssociationType
					The type of track association for which associated tracks are requested.
	@param			completionHandler
					A block that is invoked when loading is comlete, vending an array of tracks (which may be empty if there is no associated tracks of the specified type) or an error.
`*/
- (void)loadAssociatedTracksOfType:(AVTrackAssociationType)trackAssociationType completionHandler:(void (^)(NSArray<AVAssetTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

@end


@class AVSampleCursor;

@interface AVAssetTrack (AVAssetTrackSampleCursorProvision)

/* Indicates whether the receiver can provide instances of AVSampleCursor for traversing its media samples and discovering information about them. */
@property (nonatomic, readonly) BOOL canProvideSampleCursors API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
	@method			makeSampleCursorWithPresentationTimeStamp:
	@abstract		Creates an instance of AVSampleCursor and positions it at or near the specified presentation timestamp.
	@param			presentationTimeStamp
					The desired initial presentation timestamp of the returned AVSampleCursor.
	@result			An instance of AVSampleCursor.
	@discussion		If the receiver's asset has a value of YES for providesPreciseDurationAndTiming, the sample cursor will be accurately positioned at the receiver's last media sample with presentation timestamp less than or equal to the desired timestamp, or, if there are no such samples, the first sample in presentation order.
					If the receiver's asset has a value of NO for providesPreciseDurationAndTiming, and it is prohibitively expensive to locate the precise sample at the desired timestamp, the sample cursor may be approximately positioned.
 					This method will return nil if there are no samples in the track.
*/
- (nullable AVSampleCursor *)makeSampleCursorWithPresentationTimeStamp:(CMTime)presentationTimeStamp API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
	@method			makeSampleCursorAtFirstSampleInDecodeOrder:
	@abstract		Creates an instance of AVSampleCursor and positions it at the receiver's first media sample in decode order.
	@result			An instance of AVSampleCursor.
	@discussion		This method will return nil if there are no samples in the track.
*/
- (nullable AVSampleCursor *)makeSampleCursorAtFirstSampleInDecodeOrder API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
	@method			makeSampleCursorAtLastSampleInDecodeOrder:
	@abstract		Creates an instance of AVSampleCursor and positions it at the receiver's last media sample in decode order.
	@result			An instance of AVSampleCursor.
	@discussion		This method will return nil if there are no samples in the track.
*/
- (nullable AVSampleCursor *)makeSampleCursorAtLastSampleInDecodeOrder API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos);

@end

#pragma mark --- AVAssetTrack change notifications ---

/*
	AVAssetTrack change notifications are posted by instances of mutable subclasses, AVMutableCompositionTrack and AVMutableMovieTrack.
	Some of the notifications are also posted by instances of dynamic subclasses, AVFragmentedAssetTrack and AVFragmentedMovieTrack, but these are capable of changing only in well-defined ways and only under specific conditions that you control. 
*/

/*!
 @constant       AVAssetTrackTimeRangeDidChangeNotification
 @abstract       Posted when the timeRange of an AVFragmentedAssetTrack changes while the associated instance of AVFragmentedAsset is being minded by an AVFragmentedAssetMinder, but only for changes that occur after the status of the value of @"timeRange" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVAssetTrackTimeRangeDidChangeNotification API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

/*!
 @constant       AVAssetTrackSegmentsDidChangeNotification
 @abstract       Posted when the array of segments of an AVFragmentedAssetTrack changes while the associated instance of AVFragmentedAsset is being minded by an AVFragmentedAssetMinder, but only for changes that occur after the status of the value of @"segments" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVAssetTrackSegmentsDidChangeNotification API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

/*!
 @constant       AVAssetTrackTrackAssociationsDidChangeNotification
 @abstract       Posted when the collection of track associations of an AVAssetTrack changes, but only for changes that occur after the status of the value of @"availableTrackAssociationTypes" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVAssetTrackTrackAssociationsDidChangeNotification API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

#pragma mark --- AVFragmentedAssetTrack ---
/*!
	@class			AVFragmentedAssetTrack
	@abstract		A subclass of AVAssetTrack for handling tracks of fragmented assets. An AVFragmentedAssetTrack is capable of changing the values of certain of its properties, if its parent asset is associated with an instance of AVFragmentedAssetMinder when one or more fragments are appended to the underlying media resource.
	@discussion		While its parent asset is associated with an AVFragmentedAssetMinder, AVFragmentedAssetTrack posts AVAssetTrackTimeRangeDidChangeNotification and AVAssetTrackSegmentsDidChangeNotification whenever new fragments are detected, as appropriate.
*/

@class AVFragmentedAssetTrackInternal;

API_AVAILABLE(macos(10.11), ios(12.0), tvos(12.0), watchos(6.0))
@interface AVFragmentedAssetTrack : AVAssetTrack
{
@private
	AVFragmentedAssetTrackInternal	*_fragmentedAssetTrack __attribute__((unused));
}

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAssetTrack.h>
#endif

#if !__has_include(<AVFCore/AVComposition.h>)
/*
	File:  AVComposition.h

	Framework:  AVFoundation
 
	Copyright 2010-2022 Apple Inc. All rights reserved.

*/

/*!
    @class          AVComposition

    @abstract       An AVComposition combines media data from multiple local file-based sources in a custom temporal arrangement, in order to present or process media data from multiple sources together. All local file-based audiovisual assets are eligible to be combined, regardless of container type.

    @discussion
      At its top-level, AVComposition is a collection of tracks, each presenting media of a specific media type, e.g. audio or video, according to a timeline. Each track is represented by an instance of AVCompositionTrack.

      Each track is comprised of an array of track segments, each of which present a portion of the media data stored in a source container, specified by URL, a track identifier, and a time mapping, as represented by an instance of AVCompositionTrackSegment.

      The URL specifies the source container, and the track identifier indicates the track of the source container to be presented.

      The time mapping specifies the temporal range of the source track that's to be presented and also specifies the temporal range of its presentation in the composition track. If the durations of the source and destination ranges of the time mapping are the same, the media data for the segment will be presented at its natural rate. Otherwise, the segment will be presented at a rate equal to the ratio source.duration / target.duration.

      The track segments of a track are available via AVCompositionTrack's trackSegment property, an array of AVCompositionTrackSegment. The collection of tracks with media type information for each, and each with its array of track segments (URL, track identifier, and time mapping), form a complete low-level representation of a composition.

      This representation can be written out by clients in any convenient form, and subsequently the composition can be reconstituted by instantiating a new AVMutableComposition with AVMutableCompositionTracks of the appropriate media type, each with its trackSegment property set according to the stored array of URL, track identifier, and time mapping.

      A higher-level interface for constructing compositions is also presented by AVMutableComposition and AVMutableCompositionTrack, offering insertion, removal, and scaling operations without direct manipulation of the trackSegment arrays of composition tracks. This interface makes use of higher-level constructs such as AVAsset and AVAssetTrack, allowing the client to make use of the same references to candidate sources that it would have created in order to inspect or preview them prior to inclusion in a composition.

      Immutable Snapshots

        To make an immutable snapshot of a mutable composition for playback or inspection:

            // myMutableComposition is a mutable composition; the client wants to inspect and play it in its current state
            AVComposition *immutableSnapshotOfMyComposition = [myMutableComposition copy];

            // inspect and play at will, e.g.
            AVPlayerItem *playerItemForSnapshottedComposition = [[AVPlayerItem alloc] initWithAsset:immutableSnapshotOfMyComposition];

      Compositing Of Video Tracks

        During playback or other processing, such as export, without the use of an AVVideoComposition only the first enabled video track will be processed. Other video tracks are effectively ignored. To control the compositing of multiple enabled video tracks, you must create and configure an instance of AVVideoComposition and set it as the value of the videoComposition property of the AVFoundation object you're using to control processing, such as an AVPlayerItem or AVAssetExportSession.

      Mixing Of Audio Tracks

        During playback or other processing, without the use of an AVAudioMix all of the asset's enabled audio tracks are mixed together at equal levels. To control the mixing of enabled audio tracks, you must create and configure an instance of AVAudioMix and set it as the value of the audioMix property of the AVFoundation object you're using to control processing, such as an AVPlayerItem or AVAssetExportSession.
*/

#import <AVFoundation/AVAsset.h>
#import <AVFoundation/AVCompositionTrack.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>

NS_ASSUME_NONNULL_BEGIN

@class AVCompositionInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVComposition : AVAsset <NSMutableCopying>
{
@private
    AVCompositionInternal    *_priv;
}

/*!
    @property       tracks
    @abstract       Provides the array of AVCompositionTracks contained by the composition.
*/
@property (nonatomic, readonly) NSArray<AVCompositionTrack *> *tracks;

/*!
    @property       naturalSize
    @abstract       Indicates the authored size of the visual portion of the composition.
*/
@property (nonatomic, readonly) CGSize naturalSize;

/*!
    @property       URLAssetInitializationOptions
    @abstract       Specifies the initialization options for the creation of AVURLAssets by the receiver, e.g. AVURLAssetPreferPreciseDurationAndTimingKey. The default behavior for creation of AVURLAssets by an AVComposition is equivalent to the behavior of +[AVURLAsset URLAssetWithURL:options:] when specifying no initialization options.
    @discussion
      AVCompositions create AVURLAssets internally for URLs specified by AVCompositionTrackSegments of AVCompositionTracks, as needed, whenever AVCompositionTrackSegments were originally added to a track via -[AVMutableCompositionTrack setSegments:] rather than by inserting timeranges of already existing AVAssets or AVAssetTracks.
      The value of URLAssetInitializationOptions can be specified at the time an AVMutableComposition is created via +compositionWithURLAssetInitializationOptions:.
 */
@property (nonatomic, readonly, copy) NSDictionary<NSString *, id> *URLAssetInitializationOptions API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

@end

@interface AVComposition (AVCompositionTrackInspection)

/*!
    @method         trackWithTrackID:
    @abstract       Provides an instance of AVCompositionTrack that represents the track of the specified trackID.
    @param          trackID
                    The trackID of the requested AVCompositionTrack.
    @result         An instance of AVCompositionTrack; may be nil if no track of the specified trackID is available.
    @discussion
      Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (nullable AVCompositionTrack *)trackWithTrackID:(CMPersistentTrackID)trackID;

/*!
	@method		loadTrackWithTrackID:completionHandler:
	@abstract	Loads an instance of AVCompositionTrack that represents the track of the specified trackID.
	@param		trackID
				The trackID of the requested AVCompositionTrack.
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded track (which may be nil if no track of the specified trackID is available) or an error.
*/
- (void)loadTrackWithTrackID:(CMPersistentTrackID)trackID completionHandler:(void (^ NS_SWIFT_SENDABLE)(AVCompositionTrack * _Nullable_result, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
    @method         tracksWithMediaType:
    @abstract       Provides an array of AVCompositionTracks of the asset that present media of the specified media type.
    @param          mediaType
                    The media type according to which the receiver filters its AVCompositionTracks. (Media types are defined in AVMediaFormat.h)
    @result         An NSArray of AVCompositionTracks; may be empty if no tracks of the specified media type are available.
    @discussion
      Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVCompositionTrack *> *)tracksWithMediaType:(AVMediaType)mediaType;

/*!
	@method		loadTracksWithMediaType:completionHandler:
	@abstract	Loads an array of AVCompositionTracks of the asset that present media of the specified media type.
	@param		mediaType
				The media type according to which AVAsset filters its AVCompositionTracks. (Media types are defined in AVMediaFormat.h.)
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks of the specified media type are available) or an error.
*/
- (void)loadTracksWithMediaType:(AVMediaType)mediaType completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSArray<AVCompositionTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
    @method         tracksWithMediaCharacteristic:
    @abstract       Provides an array of AVCompositionTracks of the asset that present media with the specified characteristic.
    @param          mediaCharacteristic
                    The media characteristic according to which the receiver filters its AVCompositionTracks. (Media characteristics are defined in AVMediaFormat.h)
    @result         An NSArray of AVCompositionTracks; may be empty if no tracks with the specified characteristic are available.
    @discussion
      Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVCompositionTrack *> *)tracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic;

/*!
	@method		loadTracksWithMediaCharacteristic:completionHandler:
	@abstract	Loads an array of AVCompositionTracks of the asset that present media with the specified characteristic.
	@param		mediaCharacteristic
				The media characteristic according to which AVAsset filters its AVCompositionTracks. (Media characteristics are defined in AVMediaFormat.h.)
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks with the specified characteristic are available) or an error.
*/
- (void)loadTracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSArray<AVCompositionTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

@end


@class AVMutableCompositionInternal;

NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVMutableComposition : AVComposition
{
@private
    AVMutableCompositionInternal    *_mutablePriv __attribute__((unused));
}

/*!
    @property       tracks
    @abstract       Provides the array of AVMutableCompositionTracks contained by the composition.
*/
@property (nonatomic, readonly) NSArray<AVMutableCompositionTrack *> *tracks;

/*!
    @property       naturalSize
    @abstract       Indicates the authored size of the visual portion of the asset.
    @discussion
      If not set, the value is the size of the composition's first video track. Set to CGSizeZero to revert to default behavior.
*/
@property (nonatomic) CGSize naturalSize;

/*!
    @method         composition
    @abstract       Returns an empty AVMutableComposition.
*/
+ (instancetype)composition;

/*!
    @method         compositionWithURLAssetInitializationOptions:
    @abstract       Returns an empty AVMutableComposition.
    @param          URLAssetInitializationOptions
                    Specifies the initialization options that the receiver should use when creating AVURLAssets internally, e.g. AVURLAssetPreferPreciseDurationAndTimingKey. The default behavior for creation of AVURLAssets by an AVMutableComposition is equivalent to the behavior of +[AVURLAsset URLAssetWithURL:options:] when specifying no initialization options.
    @discussion
      AVMutableCompositions create AVURLAssets internally for URLs specified by AVCompositionTrackSegments of AVMutableCompositionTracks, as needed, whenever AVCompositionTrackSegments are added to tracks via -[AVMutableCompositionTrack setSegments:] rather than by inserting timeranges of already existing AVAssets or AVAssetTracks.
 */
+ (instancetype)compositionWithURLAssetInitializationOptions:(nullable NSDictionary<NSString *, id> *)URLAssetInitializationOptions API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

@end


@interface AVMutableComposition (AVMutableCompositionCompositionLevelEditing)

/*!
    @method         insertTimeRange:ofAsset:atTime:error:
    @abstract       Inserts all the tracks of a timeRange of an asset into a composition.
    @param          timeRange
                    Specifies the timeRange of the asset to be inserted.
    @param          asset
                    Specifies the asset that contains the tracks that are to be inserted. Only instances of AVURLAsset and AVComposition are supported (AVComposition starting in macOS 10.10 and iOS 8.0). The asset should have its tracks loaded, and the tracks should have their formatDescriptions loaded before invoking this method to avoid blocking.
    @param          startTime
                    Specifies the time at which the inserted tracks are to be presented by the composition.
    @param          outError
                    Describes failures that may be reported to the user, e.g. the asset that was selected for insertion in the composition is restricted by copy-protection.
    @result         A BOOL value indicating the success of the insertion.
    @discussion
      You provide a reference to an AVAsset and the timeRange within it that you want to insert. You specify the start time in the destination composition at which the timeRange should be inserted.
      This method may add new tracks to ensure that all tracks of the asset are represented in the inserted timeRange.
      Note that the media data for the inserted timeRange will be presented at its natural duration and rate. It can be scaled to a different duration and presented at a different rate via -scaleTimeRange:toDuration:.
      Existing content at the specified startTime will be pushed out by the duration of timeRange.
      Note that this operation only inserts one or more track segments into affected AVMutableCompositionTracks; it does not affect the values of other track properties, either to match the corresponding values of tracks in the source asset or for any other purpose.
*/
- (BOOL)insertTimeRange:(CMTimeRange)timeRange ofAsset:(AVAsset *)asset atTime:(CMTime)startTime error:(NSError * _Nullable * _Nullable)outError API_DEPRECATED_WITH_REPLACEMENT("insertTimeRange:ofAsset:atTime:completionHandler:", macos(10.7, 15.0), ios(4.0, 18.0), tvos(9.0, 18.0), watchos(1.0, 11.0), visionos(1.0, 2.0));

/*!
	@method         insertTimeRange:ofAsset:atTime:completionHandler:
	@abstract       Inserts all the tracks of a timeRange of an asset into a composition.
	@param          timeRange
					Specifies the timeRange of the asset to be inserted.
	@param          asset
					Specifies the asset that contains the tracks that are to be inserted. Only instances of AVURLAsset and AVComposition are supported (AVComposition starting in macOS 10.10 and iOS 8.0).
	@param          startTime
					Specifies the time at which the inserted tracks are to be presented by the composition.
	@param          completionHandler
					A block that is invoked when the insertion is complete.  If the error parameter is non-nil, it describes a failure that may be reported to the user, e.g. the asset that was selected for insertion in the composition is restricted by copy-protection.
	@discussion
	  You provide a reference to an AVAsset and the timeRange within it that you want to insert. You specify the start time in the destination composition at which the timeRange should be inserted.
	  This method may add new tracks to ensure that all tracks of the asset are represented in the inserted timeRange.
	  Note that the media data for the inserted timeRange will be presented at its natural duration and rate. It can be scaled to a different duration and presented at a different rate via -scaleTimeRange:toDuration:.
	  Existing content at the specified startTime will be pushed out by the duration of timeRange.
	  Note that this operation only inserts one or more track segments into affected AVMutableCompositionTracks; it does not affect the values of other track properties, either to match the corresponding values of tracks in the source asset or for any other purpose.
*/
- (void)insertTimeRange:(CMTimeRange)timeRange ofAsset:(AVAsset *)asset atTime:(CMTime)startTime completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSError * _Nullable error))completionHandler AVF_DEPRECATED_FOR_SWIFT_ONLY("Use insertTimeRange(_:of:at:isolation:) async instead", macos(13.0, 15.0), ios(16.0, 18.0), tvos(16.0, 18.0), watchos(9.0, 11.0), visionos(1.0, 2.0)) NS_SWIFT_DISABLE_ASYNC;

/*!
    @method         insertEmptyTimeRange:
    @abstract       Adds or extends an empty timeRange within all tracks of the composition.
    @param          timeRange
                    Specifies the empty timeRange to be inserted.
    @discussion
     If you insert an empty timeRange into the composition, any media that was presented during that interval prior to the insertion will be presented instead immediately afterward. You can use this method to reserve an interval in which you want a subsequently created track to present its media.
      Note that you cannot add empty time ranges to the end of a composition.
*/
- (void)insertEmptyTimeRange:(CMTimeRange)timeRange;

/*!
    @method         removeTimeRange:
    @abstract       Removes a specified timeRange from all tracks of the composition.
    @param          timeRange
                    Specifies the timeRange to be removed.
    @discussion
      Removal of a time range does not cause any existing tracks to be removed from the composition, even if removing timeRange results in an empty track. Instead, it removes or truncates track segments that intersect with the timeRange.

      After removing, existing content after timeRange will be pulled in.
*/
- (void)removeTimeRange:(CMTimeRange)timeRange;

/*!
    @method         scaleTimeRange:toDuration:
    @abstract       Changes the duration of a timeRange of all tracks.
    @param          timeRange
                    Specifies the timeRange of the composition to be scaled.
    @param          duration
                    Specifies the new duration of the timeRange.
    @discussion
      Each trackSegment affected by the scaling operation will be presented at a rate equal to source.duration / target.duration of its resulting timeMapping.
*/
- (void)scaleTimeRange:(CMTimeRange)timeRange toDuration:(CMTime)duration;

@end


@interface AVMutableComposition (AVMutableCompositionTrackLevelEditing)

/*!
    @method         addMutableTrackWithMediaType:preferredTrackID:
    @abstract       Adds an empty track to a mutable composition.
    @param          mediaType
                    The media type of the new track.
    @param          preferredTrackID
                    Specifies the preferred track ID for the new track. If you do not need to specify a preferred track ID, pass kCMPersistentTrackID_Invalid. Otherwise the preferred track ID will be used for the new track, provided that it is not currently in use and has not previously been used.
    @result         An instance of AVMutableCompositionTrack representing the new track. Its actual trackID is available via its @"trackID" key.
    @discussion
      If the specified preferred track ID is not available, or kCMPersistentTrackID_Invalid was passed in, a unique track ID will be generated.
*/
- (nullable AVMutableCompositionTrack *)addMutableTrackWithMediaType:(AVMediaType)mediaType preferredTrackID:(CMPersistentTrackID)preferredTrackID;

/*!
    @method         removeTrack:
    @abstract       Removes a track of a mutable composition.
    @param          track
                    A reference to the AVCompositionTrack to be removed.
    @discussion
      If you retain a reference to the removed track, note that its @"composition" key will have the value nil, and the values of its other properties are undefined.
*/
- (void)removeTrack:(AVCompositionTrack *)track;

/*!
    @method         mutableTrackCompatibleWithTrack:
    @abstract       Provides a reference to a track of a mutable composition into which any timeRange of an AVAssetTrack can be inserted (via -[AVMutableCompositionTrack insertTimeRange:ofTrack:atTime:error:]).
    @param          track
                    A reference to the AVAssetTrack from which a timeRange may be inserted.
    @result         An AVMutableCompositionTrack that can accommodate the insertion, or, if no such track is available, nil.
    @discussion
      If a compatible track is desired but the result of this method is nil, a new track of the same mediaType as the AVAssetTrack can be created via -addMutableTrackWithMediaType:preferredTrackID:, and this new track will be compatible.

      For best performance, the number of tracks of a composition should be kept to a minimum, corresponding to the number for which media data must be presented in parallel. If media data of the same type is to be presented serially, even from multiple assets, a single track of that media type should be used. This method, -mutableTrackCompatibleWithTrack:, can help the client to identify an existing target track for an insertion.

      Similar to -[AVAsset compatibleTrackForCompositionTrack:].
*/
- (nullable AVMutableCompositionTrack *)mutableTrackCompatibleWithTrack:(AVAssetTrack *)track;

@end

@interface AVMutableComposition (AVMutableCompositionTrackInspection)

/*!
    @method         trackWithTrackID:
    @abstract       Provides an instance of AVMutableCompositionTrack that represents the track of the specified trackID.
    @param          trackID
                    The trackID of the requested AVMutableCompositionTrack.
    @result         An instance of AVMutableCompositionTrack; may be nil if no track of the specified trackID is available.
    @discussion
      Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (nullable AVMutableCompositionTrack *)trackWithTrackID:(CMPersistentTrackID)trackID;

/*!
	@method		loadTrackWithTrackID:completionHandler:
	@abstract	Loads an instance of AVMutableCompositionTrack that represents the track of the specified trackID.
	@param		trackID
				The trackID of the requested AVMutableCompositionTrack.
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded track (which may be nil if no track of the specified trackID is available) or an error.
*/
- (void)loadTrackWithTrackID:(CMPersistentTrackID)trackID completionHandler:(void (^ NS_SWIFT_SENDABLE)(AVMutableCompositionTrack * _Nullable_result, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
    @method         tracksWithMediaType:
    @abstract       Provides an array of AVMutableCompositionTracks of the asset that present media of the specified media type.
    @param          mediaType
                    The media type according to which the receiver filters its AVMutableCompositionTracks. (Media types are defined in AVMediaFormat.h)
    @result         An NSArray of AVMutableCompositionTracks; may be empty if no tracks of the specified media type are available.
    @discussion
      Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVMutableCompositionTrack *> *)tracksWithMediaType:(AVMediaType)mediaType;

/*!
	@method		loadTracksWithMediaType:completionHandler:
	@abstract	Loads an array of AVMutableCompositionTracks of the asset that present media of the specified media type.
	@param		mediaType
				The media type according to which AVAsset filters its AVMutableCompositionTracks. (Media types are defined in AVMediaFormat.h.)
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks of the specified media type are available) or an error.
*/
- (void)loadTracksWithMediaType:(AVMediaType)mediaType completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSArray<AVMutableCompositionTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
    @method         tracksWithMediaCharacteristic:
    @abstract       Provides an array of AVMutableCompositionTracks of the asset that present media with the specified characteristic.
    @param          mediaCharacteristic
                    The media characteristic according to which the receiver filters its AVMutableCompositionTracks. (Media characteristics are defined in AVMediaFormat.h)
    @result         An NSArray of AVMutableCompositionTracks; may be empty if no tracks with the specified characteristic are available.
    @discussion
      Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVMutableCompositionTrack *> *)tracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic;

/*!
	@method		loadTracksWithMediaCharacteristic:completionHandler:
	@abstract	Loads an array of AVMutableCompositionTracks of the asset that present media with the specified characteristic.
	@param		mediaCharacteristic
				The media characteristic according to which AVAsset filters its AVMutableCompositionTracks. (Media characteristics are defined in AVMediaFormat.h.)
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks with the specified characteristic are available) or an error.
*/
- (void)loadTracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSArray<AVMutableCompositionTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

@end

/*!
 @category AVComposition (SynchronousAssetInterface)
 @abstract Redeclarations of async-only AVAsset interfaces to allow synchronous usage in the synchronous subclass.
 @discussion
	See AVAsset's interface for more information about these interfaces.
 */
@interface AVComposition (SynchronousAssetInterface)

- (NSArray<AVMetadataItem *> *)metadataForFormat:(AVMetadataFormat)format;
- (NSArray<AVTimedMetadataGroup *> *)chapterMetadataGroupsWithTitleLocale:(NSLocale *)locale containingItemsWithCommonKeys:(nullable NSArray<AVMetadataKey> *)commonKeys;
- (NSArray<AVTimedMetadataGroup *> *)chapterMetadataGroupsBestMatchingPreferredLanguages:(NSArray<NSString *> *)preferredLanguages;
- (nullable AVMediaSelectionGroup *)mediaSelectionGroupForMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic;
- (CMPersistentTrackID)unusedTrackID;

#if __swift__
@property (nonatomic, readonly) CMTime duration;
@property (nonatomic, readonly) float preferredRate;
@property (nonatomic, readonly) float preferredVolume;
@property (nonatomic, readonly) CGAffineTransform preferredTransform;
@property (nonatomic, readonly) AVDisplayCriteria *preferredDisplayCriteria API_AVAILABLE(tvos(11.2)) API_UNAVAILABLE(ios, visionos) API_UNAVAILABLE(macos, watchos);
@property (nonatomic, readonly) CMTime minimumTimeOffsetFromLive API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0), visionos(1.0));
@property (nonatomic, readonly) BOOL providesPreciseDurationAndTiming;
@property (nonatomic, readonly) NSArray<AVAssetTrackGroup *> *trackGroups API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));
@property (nonatomic, readonly, nullable) AVMetadataItem *creationDate API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0), visionos(1.0));
@property (nonatomic, readonly, nullable) NSString *lyrics;
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *commonMetadata;
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *metadata API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));
@property (nonatomic, readonly) NSArray<AVMetadataFormat> *availableMetadataFormats;
@property (readonly) NSArray<NSLocale *> *availableChapterLocales API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
@property (nonatomic, readonly) NSArray<AVMediaCharacteristic> *availableMediaCharacteristicsWithMediaSelectionOptions API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0), visionos(1.0));;
@property (nonatomic, readonly) AVMediaSelection *preferredMediaSelection API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));
@property (nonatomic, readonly) NSArray<AVMediaSelection *> *allMediaSelections API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0), visionos(1.0));
@property (nonatomic, readonly) BOOL hasProtectedContent API_AVAILABLE(macos(10.7), ios(4.2), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) BOOL canContainFragments API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) BOOL containsFragments API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly) CMTime overallDurationHint API_AVAILABLE(macos(10.12.2), ios(10.2), tvos(10.2), watchos(3.2), visionos(1.0));
@property (nonatomic, readonly, getter=isPlayable) BOOL playable API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
@property (nonatomic, readonly, getter=isExportable) BOOL exportable API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly, getter=isReadable) BOOL readable API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
@property (nonatomic, readonly, getter=isComposable) BOOL composable API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0), visionos(1.0));
@property (nonatomic, readonly, getter=isCompatibleWithSavedPhotosAlbum) BOOL compatibleWithSavedPhotosAlbum API_AVAILABLE(ios(5.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(macos, watchos);
@property (nonatomic, readonly, getter=isCompatibleWithAirPlayVideo) BOOL compatibleWithAirPlayVideo API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), visionos(1.0)) API_UNAVAILABLE(watchos);
#endif // __swift__

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVComposition.h>
#endif

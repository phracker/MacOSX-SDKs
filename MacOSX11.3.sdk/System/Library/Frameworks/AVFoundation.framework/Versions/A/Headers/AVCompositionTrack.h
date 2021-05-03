#if !__has_include(<AVFCore/AVCompositionTrack.h>)
/*
	File:  AVCompositionTrack.h

	Framework:  AVFoundation
 
	Copyright 2010-2019 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAssetTrack.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>
#import <CoreMedia/CMFormatDescription.h>

NS_ASSUME_NONNULL_BEGIN

@class AVAsset;
@class AVComposition;
@class AVCompositionTrackFormatDescriptionReplacement;

/*!
    @class          AVCompositionTrack

    @abstract       AVCompositionTrack offers the low-level representation of tracks of AVCompositions, comprising a media type, a track identifier, and an array of AVCompositionTrackSegments, each comprising a URL, and track identifier, and a time mapping.
*/

@class AVCompositionTrackInternal;
@class AVCompositionTrackSegment;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0))
@interface AVCompositionTrack : AVAssetTrack
{
@private
    AVCompositionTrackInternal    *_priv;
}

/*!
    @property       segments
    @abstract       Provides read-only access to the array of track segments, each an instance of AVCompositionTrackSegment.
    @discussion
      Note that timeMapping.target.start of the first AVCompositionTrackSegment must be kCMTimeZero, and the timeMapping.target.start of each subsequent AVCompositionTrackSegment must equal CMTimeRangeGetEnd(the previous AVCompositionTrackSegment's timeMapping.target).
      Use -validateTrackSegments:error: to perform a test to ensure that an array of AVCompositionTrackSegments conforms to this rule.
*/
@property (nonatomic, readonly, copy) NSArray<AVCompositionTrackSegment *> *segments;

/*!
	@method			segmentForTrackTime:
	@abstract		Supplies the AVCompositionTrackSegment from the segments array with a target timeRange that either contains the specified track time or is the closest to it among the target timeRanges of the track's segments.
	@param			trackTime
					The trackTime for which an AVCompositionTrackSegment is requested.
	@result			An AVCompositionTrackSegment.
	@discussion		If the trackTime does not map to a sample presentation time (e.g. it's outside the track's timeRange), the segment closest in time to the specified trackTime is returned. 
 */
- (nullable AVCompositionTrackSegment *)segmentForTrackTime:(CMTime)trackTime;

/*!
	@property		formatDescriptionReplacements
	@abstract		An array of AVCompositionTrackFormatDescriptionReplacement objects indicating original format descriptions and their replacements.
	@discussion     The value of this property is an array of AVCompositionTrackFormatDescriptionReplacement objects, each of which specifies an original format description together with its replacement format description (as specified by a previous call to -replaceFormatDescription:withFormatDescription:). Only format descriptions that are to be replaced will occur as the originalFormatDescription elements in the AVCompositionTrackFormatDescriptionReplacement objects in this array.
*/
@property (readonly) NSArray <AVCompositionTrackFormatDescriptionReplacement *> *formatDescriptionReplacements API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

@end


/*!
    @class          AVMutableCompositionTrack

    @abstract       AVMutableCompositionTrack provides a convenient interface for insertions, removals, and scaling of track segments without direct manipulation of their low-level representation.
*/

@class AVMutableCompositionTrackInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0))
@interface AVMutableCompositionTrack : AVCompositionTrack
{
@private
    AVMutableCompositionTrackInternal    *_mutablePriv __attribute__((unused));
}

/*!
 @property       enabled
 @abstract       Specifies whether the track is enabled or disabled.  Default is YES.
 */
@property (nonatomic, getter=isEnabled) BOOL enabled API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

/*!
    @property       naturalTimeScale
    @abstract       Indicates a timescale in which time values for the track can be operated upon without extraneous numerical conversion.
    @discussion
      If not set, the value is the naturalTimeScale of the first non-empty edit, or 600 if there are no non-empty edits.
      Set to 0 to revert to default behavior.
*/
@property (nonatomic) CMTimeScale naturalTimeScale;

/*!
    @property       languageCode
    @abstract       Indicates the language associated with the track, as an ISO 639-2/T language code.
    @discussion
      The default value is nil.
*/
@property (nonatomic, copy, nullable) NSString *languageCode;

/*!
    @property       extendedLanguageTag
    @abstract       Indicates the language tag associated with the track, as an IETF BCP 47 (RFC 4646) language identifier.
    @discussion
      The default value is nil.
*/
@property (nonatomic, copy, nullable) NSString *extendedLanguageTag;

/*!
    @property       preferredTransform
    @abstract       The preferred transformation of the visual media data for display purposes.
    @discussion
      The default value is CGAffineTransformIdentity.
*/
@property (nonatomic) CGAffineTransform preferredTransform;

/*!
    @property       preferredVolume
    @abstract       The preferred volume of the audible media data.
    @discussion
      The default value is 1.0.
*/
@property (nonatomic) float preferredVolume;

/*!
    @property       segments
    @abstract       Provides read/write access to the array of track segments, each an instance of AVCompositionTrackSegment.
    @discussion
      Note that timeMapping.target.start of the first AVCompositionTrackSegment must be kCMTimeZero, and the timeMapping.target.start of each subsequent AVCompositionTrackSegment must equal CMTimeRangeGetEnd(the previous AVCompositionTrackSegment's timeMapping.target).
      Use -validateTrackSegments:error: to perform a test to ensure that an array of AVCompositionTrackSegments conforms to this rule.
*/
@property (nonatomic, copy, null_resettable) NSArray<AVCompositionTrackSegment *> *segments;

/*!
    @method         insertTimeRange:ofTrack:atTime:error:
    @abstract       Inserts a timeRange of a source track into a track of a composition.
    @param          timeRange
                    Specifies the timeRange of the track to be inserted.
    @param          track
                    Specifies the source track to be inserted. Only AVAssetTracks of AVURLAssets and AVCompositions are supported (AVCompositions starting in MacOS X 10.10 and iOS 8.0).
    @param          startTime
                    Specifies the time at which the inserted track is to be presented by the composition track. You may pass kCMTimeInvalid for startTime to indicate that the timeRange should be appended to the end of the track.
    @param          error
                    Describes failures that may be reported to the user, e.g. the asset that was selected for insertion in the composition is restricted by copy-protection.
    @result         A BOOL value indicating the success of the insertion.
    @discussion
      You provide a reference to an AVAssetTrack and the timeRange within it that you want to insert. You specify the start time in the target composition track at which the timeRange should be inserted.

      Note that the inserted track timeRange will be presented at its natural duration and rate. It can be scaled to a different duration (and presented at a different rate) via -scaleTimeRange:toDuration:.
*/
- (BOOL)insertTimeRange:(CMTimeRange)timeRange ofTrack:(AVAssetTrack *)track atTime:(CMTime)startTime error:(NSError * _Nullable * _Nullable)outError;

/*!
    @method         insertTimeRanges:ofTracks:atTime:error:
    @abstract       Inserts the timeRanges of multiple source tracks into a track of a composition.
    @param          timeRanges
                    Specifies the timeRanges to be inserted. An NSArray of NSValues containing CMTimeRange. (See +[NSValue valueWithCMTimeRange:] in AVTime.h.)
    @param          tracks
                    Specifies the source tracks to be inserted. Only AVAssetTracks of AVURLAssets and AVCompositions are supported (AVCompositions starting in MacOS X 10.10 and iOS 8.0).
    @param          startTime
                    Specifies the time at which the inserted tracks are to be presented by the composition track. You may pass kCMTimeInvalid for startTime to indicate that the timeRanges should be appended to the end of the track.
    @param          error
                    Describes failures that may be reported to the user, e.g. the asset that was selected for insertion in the composition is restricted by copy-protection.
    @result         A BOOL value indicating the success of the insertion.
    @discussion
      This method is equivalent to (but more efficient than) calling -insertTimeRange:ofTrack:atTime:error: for each timeRange/track pair. If this method returns an error, none of the time ranges will be inserted into the composition track. To specify an empty time range, pass NSNull for the track and a time range of starting at kCMTimeInvalid with a duration of the desired empty edit.
*/
- (BOOL)insertTimeRanges:(NSArray<NSValue *> *)timeRanges ofTracks:(NSArray<AVAssetTrack *> *)tracks atTime:(CMTime)startTime error:(NSError * _Nullable * _Nullable)outError API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

/*!
    @method         insertEmptyTimeRange:
    @abstract       Adds or extends an empty timeRange within the composition track.
    @param          timeRange
                    Specifies the empty timeRange to be inserted.
    @discussion
      If you insert an empty timeRange into the track, any media that was presented during that interval prior to the insertion will be presented instead immediately afterward.
      The exact meaning of the term "empty timeRange" depends upon the mediaType of the track. For example, an empty timeRange in a sound track presents silence.
      Note that you cannot add empty time ranges to the end of a composition track.
*/
- (void)insertEmptyTimeRange:(CMTimeRange)timeRange;

/*!
    @method         removeTimeRange:
    @abstract       Removes a specified timeRange from the track.
    @param          timeRange
                    Specifies the timeRange to be removed.
    @discussion
      Removal of a timeRange does not cause the track to be removed from the composition. Instead it removes or truncates track segments that intersect with the timeRange.
*/
- (void)removeTimeRange:(CMTimeRange)timeRange;

/*!
    @method         scaleTimeRange:toDuration:
    @abstract       Changes the duration of a timeRange of the track.
    @param          timeRange
                    Specifies the timeRange of the track to be scaled.
    @param          duration
                    Specifies the new duration of the timeRange.
    @discussion
      Each trackSegment affected by the scaling operation will be presented at a rate equal to source.duration / target.duration of its resulting timeMapping.
*/
- (void)scaleTimeRange:(CMTimeRange)timeRange toDuration:(CMTime)duration;

/*!
    @method         validateTrackSegments:error:
    @abstract       Tests an array of AVCompositionTrackSegments to determine whether they conform to the timing rules noted above (see the property key @"trackSegments").
    @param          trackSegments
                    The array of AVCompositionTrackSegments to be validated.
    @param          error
                    If validation fais, returns information about the failure.
    @result         YES if validation suceeds, otherwise NO.
    @discussion
      The array is tested for suitability for setting as the value of the trackSegments property. If a portion of an existing trackSegments array is to be modified, the modification can be made via an instance of NSMutableArray, and the resulting array can be tested via -validateTrackSegments:error:.
*/
- (BOOL)validateTrackSegments:(NSArray<AVCompositionTrackSegment *> *)trackSegments error:(NSError * _Nullable * _Nullable)outError;

/*!
	@method			addTrackAssociationToTrack:type:
	@abstract		Establishes a track association of a specific type between two tracks.
	@param			compositionTrack
					An AVCompositionTrack object that is to be associated with the receiver.
	@param			trackAssociationType
					The type of track association to add between the receiver and the specified compositionTrack (for instance, AVTrackAssociationTypeChapterList).
*/
- (void)addTrackAssociationToTrack:(AVCompositionTrack *)compositionTrack type:(AVTrackAssociationType)trackAssociationType API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/*!
	@method			removeTrackAssociationToTrack:type:
	@abstract		Removes a track association of a specific type between two tracks.
	@param			compositionTrack
					An AVCompositionTrack object that is associated with the receiver.
	@param			trackAssociationType
					The type of track association to remove between the receiver and the specified compositionTrack (for instance, AVTrackAssociationTypeChapterList).
*/
- (void)removeTrackAssociationToTrack:(AVCompositionTrack *)compositionTrack type:(AVTrackAssociationType)trackAssociationType API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

@end

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@interface AVCompositionTrackFormatDescriptionReplacement : NSObject <NSSecureCoding>

/*!
    @property       originalFormatDescription
    @abstract       The original format description.
*/
@property (readonly) CMFormatDescriptionRef originalFormatDescription;

/*!
    @property       replacementFormatDescription
    @abstract       The replacement format description.
*/
@property (readonly) CMFormatDescriptionRef replacementFormatDescription;

@end

@interface AVMutableCompositionTrack (AVMutableCompositionTrackFormatDescriptionReplacement)
/*!
	@method			replaceFormatDescription:withFormatDescription:
	@abstract		Replaces one of the receiver's format descriptions with another format description or cancels a previous replacement.
	@param			originalFormatDescription
					A CMFormatDescription occurring in the underlying asset track.
	@param			replacementFormatDescription
					A CMFormatDescription to replace the specified format description or NULL to indicate that a previous replacement of originalFormatDescription should be cancelled.
	@discussion     You can use this method to make surgical changes to a track's format descriptions, such as adding format description extensions to a format description or changing the audio channel layout of an audio track. You should note that a format description can have extensions of type kCMFormatDescriptionExtension_VerbatimSampleDescription and kCMFormatDescriptionExtension_VerbatimISOSampleEntry; if you modify a copy of a format description, you should delete those extensions from the copy or your changes might be ignored. Also note that format description replacements are not transferred when performing editing operations on AVMutableCompositionTrack objects; for instance, inserting a range of a composition track into another composition track does not transfer any replacement format descriptions.
*/
- (void)replaceFormatDescription:(CMFormatDescriptionRef)originalFormatDescription withFormatDescription:(nullable CMFormatDescriptionRef)replacementFormatDescription API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVCompositionTrack.h>
#endif

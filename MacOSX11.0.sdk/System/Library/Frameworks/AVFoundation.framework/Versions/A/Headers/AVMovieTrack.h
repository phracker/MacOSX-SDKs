#if !__has_include(<AVFCore/AVMovieTrack.h>)
/*
	File:			AVMovieTrack.h

	Framework:		AVFoundation
 
	Copyright 2009-2019 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>

#import <AVFoundation/AVAssetTrack.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>
#import <CoreMedia/CMSampleBuffer.h>

/*!
    @class			AVMovieTrack

    @abstract		AVMovieTrack represents the tracks of audiovisual containers in a file that conforms to the QuickTime movie file format or to one of the related ISO base media file formats (such as MPEG-4).
*/

NS_ASSUME_NONNULL_BEGIN

@class AVMovieTrackInternal;
@class AVMediaDataStorage;
@class AVMetadataItem;

#pragma mark --- AVMovieTrack ---
API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos)
@interface AVMovieTrack : AVAssetTrack {
@private
    AVMovieTrackInternal    *_movieTrackInternal __attribute__((unused));
}

/*!
	@property       mediaPresentationTimeRange
	@abstract       A CMTimeRange indicating the range of presentation times for the track's media.
*/
@property (nonatomic, readonly) CMTimeRange mediaPresentationTimeRange API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos);

/*!
	@property       mediaDecodeTimeRange
	@abstract       A CMTimeRange indicating the range of decode times for the track's media.
*/
@property (nonatomic, readonly) CMTimeRange mediaDecodeTimeRange API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos);

/*!
	@property       alternateGroupID
	@abstract       An integer indicating the track as a member of a particular alternate group.
*/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wavailability"
@property (nonatomic, readonly) NSInteger alternateGroupID API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos);
#pragma clang diagnostic pop

@end

@interface AVMovieTrack (AVMovieTrackMediaDataStorage)

/*!
	@property       mediaDataStorage
	@abstract       The storage container for media data added to a track.
	@discussion     The value of this property is an AVMediaDataStorage object that indicates the location at which media data inserted or appended to the track will be written.
*/
@property (nonatomic, readonly, copy, nullable) AVMediaDataStorage *mediaDataStorage API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos);

@end


/*!
	@class			AVMutableMovieTrack

	@abstract		AVMutableMovieTrack provides the track-level editing interface of an AVMutableMovie. Media can be inserted into a movie track and other editing operations performed via an instance of this class.
*/

@class AVMutableMovieTrackInternal;

#pragma mark --- AVMutableMovieTrack ---
API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos)
@interface AVMutableMovieTrack : AVMovieTrack {
@private
    AVMutableMovieTrackInternal    *_mutableMovieTrackInternal;
}

/*!
	@property       mediaDataStorage
	@abstract       The storage container for media data added to a track.
	@discussion     The value of this property is an AVMediaDataStorage object that indicates the location at which media data inserted or appended to the track will be written.
*/
@property (nonatomic, copy, nullable) AVMediaDataStorage *mediaDataStorage;

/*!
	@property       sampleReferenceBaseURL
	@abstract       For file types that support writing sample references, such as QuickTime Movie files, specifies the base URL that sample references are relative to; may be nil.
	@discussion     If the value of this property can be resolved as an absolute URL, the sample locations written to the file when appending sample references to this track will be relative to this URL. The URL must point to a location contained by any common parent directory of the locations that will be referenced. For example, setting the sampleReferenceBaseURL property to "file:///Users/johnappleseed/Movies/" and appending sample buffers that refer to "file:///Users/johnappleseed/Movies/data/movie1.mov" will cause the sample reference "data/movie1.mov" to be written to the movie file.
 
		If the value of the property cannot be resolved as an absolute URL or if it points to a location that is not contained by any common parent directory of the locations that will be referenced, the location will be written unmodified.
 
		The default value is nil, which means that the location will be written unmodified.
*/
@property (nonatomic, copy, nullable) NSURL *sampleReferenceBaseURL;

/*!
	@property       enabled
	@abstract       A BOOL value indicating whether the track is enabled by default for presentation.
*/
@property (nonatomic, getter=isEnabled) BOOL enabled;

/*!
	@property       alternateGroupID
	@abstract       An integer indicating the track as a member of a particular alternate group.
*/
@property (nonatomic) NSInteger alternateGroupID;

/*!
	@property       modified
	@abstract       Whether a track has been modified.
	@discussion     The value of this property is a BOOL that indicates whether the AVMutableMovieTrack object has been modified since it was created, was last written, or had its modified state cleared via a call to setModified:NO.
*/
@property (nonatomic, getter=isModified) BOOL modified;

/*!
	@property       hasProtectedContent
	@abstract       Whether a track contains protected content.
	@discussion     The value of this property is a BOOL that indicates whether the track contains protected content.
 */
@property (nonatomic, readonly) BOOL hasProtectedContent;

/*!
	@property       timescale
	@abstract       For file types that contain a 'moov' atom, such as QuickTime Movie files, specifies the time scale of the track's media.
	@discussion		The default media time scale is 0.
 
					This property should be set on a new empty track before any edits are performed on the track.
*/
@property (nonatomic, readwrite) CMTimeScale timescale;

@end


@interface AVMutableMovieTrack (AVMutableMovieTrackLanguageProperties)

/*!
	@property       languageCode
	@abstract       The language associated with the track.
	@discussion     The value of this property is an ISO 639-2/T language code indicating the language associated with the track; may be nil if no language is indicated.
*/
@property (nonatomic, copy, nullable) NSString *languageCode;

/*!
	@property       extendedLanguageTag
	@abstract       The language tag associated with the track.
	@discussion     The value of this property is an IETF BCP 47 (RFC 4646) language identifier indicating the language tag associated with the track; may be nil if no language tag is indicated.
*/
@property (nonatomic, copy, nullable) NSString *extendedLanguageTag;

@end


@interface AVMutableMovieTrack (AVMutableMovieTrackVisualProperties)

/*!
	@property       naturalSize
	@abstract       A CGSize indicating the dimensions at which the visual media data of the track should be displayed.
*/
@property (nonatomic) CGSize naturalSize;

/*!
	@property       preferredTransform
	@abstract       A CGAffineTransform indicating the transform specified in the track's storage container as the preferred transformation of the visual media data for display purposes; the value is often but not always CGAffineTransformIdentity.
*/
@property (nonatomic) CGAffineTransform preferredTransform;

/*!
	@property       layer
	@abstract       The layer level of the visual media data of the track.
*/
@property (nonatomic) NSInteger layer;

/*!
	@property       cleanApertureDimensions
	@abstract       A CGSize indicating the clean aperture dimensions of the track.
*/
@property (nonatomic) CGSize cleanApertureDimensions;

/*!
	@property       productionApertureDimensions
	@abstract       A CGSize indicating the production aperture dimensions of the track.
*/
@property (nonatomic) CGSize productionApertureDimensions;

/*!
	@property       encodedPixelsDimensions
	@abstract       A CGSize indicating the dimensions encoded pixels dimensions of the track.
*/
@property (nonatomic) CGSize encodedPixelsDimensions;

@end


@interface AVMutableMovieTrack (AVMutableMovieTrackAudibleProperties)

/*!
	@property       preferredVolume
	@abstract       The preferred volume of the audible media data of the track; often but not always 1.0.
*/
@property (nonatomic) float preferredVolume;

@end


@interface AVMutableMovieTrack (AVMutableMovieTrackChunkProperties)

/*!
	@category		AVMutableMovieTrack(AVMutableMovieTrackChunkProperties)
 
	@discussion		Sample data in a movie file is stored in a series of "chunks". A chunk contains one or more samples, which may have different sizes from one another.
					The collection of samples into chunks is intended to allow optimized access to the sample data during operations such as movie playback. 
 
					You can change the default chunk size in a movie file by adjusting the chunk properties of a movie track prior to writing the track's sample data 
					to a media storage container. A larger chunk size can result in fewer reads from the storage container, at the potential expense of a larger memory footprint.
 
					The preferredMediaChunkSize property restricts the size of the chunks to a maximum number of bytes, and the preferredMediaChunkDuration property restricts
					the size of the chunks to a maximum duration. Note that these settings are not mutually exclusive: a chunk ends when either the preferred chunk size or the preferred chunk duration is reached.
*/

/*!
	@property       preferredMediaChunkSize
	@abstract       For file types that support media chunk sizes, the maximum size (in bytes) to be used for each chunk of sample data written to the file.
	@discussion		The total size of the samples in a chunk will be no larger than this preferred chunk size, or the size of a single sample if the sample is larger than this preferred chunk size.
 
					The default media chunk size is 1024 * 1024 bytes. It is an error to set a negative chunk size.
*/
@property (nonatomic) NSInteger preferredMediaChunkSize;

/*!
	@property		preferredMediaChunkDuration
	@abstract		For file types that support media chunk durations, the maximum duration to be used for each chunk of sample data written to the file.
 
	@discussion		The total duration of the samples in a chunk will be no greater than this preferred chunk duration, or the duration of a single sample if the sample's duration is greater than this preferred chunk duration.
 
					The default media chunk duration is 1.0 second. It is an error to set a chunk duration that is negative or non-numeric.
 */
@property (nonatomic) CMTime preferredMediaChunkDuration;

/*!
	@property		preferredMediaChunkAlignment
	@abstract		For file types that support media chunk alignment, the boundary for media chunk alignment (in bytes).
 
	@discussion		The default value is 0, which means that no padding should be used to achieve chunk alignment. It is an error to set a negative value for chunk alignment.
*/
@property (nonatomic) NSInteger preferredMediaChunkAlignment;

@end


@interface AVMutableMovieTrack (AVMutableMovieTrackTrackLevelEditing)

/*!
	@method			insertTimeRange:ofTrack:atTime:copySampleData:error:
	@abstract		Inserts a portion of an AVAssetTrack object into the target movie.
	@param			timeRange
					The time range from the track from which media is to be inserted.
	@param			track
					An AVAssetTrack object indicating the source of the inserted media. Only AVAssetTracks of AVURLAssets and AVCompositions are supported.
					Must not be nil.
	@param			startTime
					The time in the target track at which the media is to be inserted.
	@param			copySampleData
                    A BOOL value that indicates whether sample data is to be copied from the source to the destination during edits.
					If YES, the sample data is written to the file specified by the track property mediaDataStorage if non-nil,
					or else by the movie property defaultMediaDataStorage if non-nil; if both are nil, the method will fail and return NO.
					If NO, sample data will not be written and sample references to the samples in their original container will be added
					as necessary. Note that in this case, this method will fail if the original samples are fragmented.
	@param			outError
					If the insertion fails, describes the nature of the failure.
	@result			A BOOL value that indicates the success of the insertion.

*/
- (BOOL)insertTimeRange:(CMTimeRange)timeRange ofTrack:(AVAssetTrack *)track atTime:(CMTime)startTime copySampleData:(BOOL)copySampleData error:(NSError * _Nullable * _Nullable)outError;

/*!
	@method			insertEmptyTimeRange:
	@abstract		Adds an empty time range to the target track.
	@param			timeRange
					The time range to be made empty. Note that you cannot add empty time ranges to the end of a track.
*/
- (void)insertEmptyTimeRange:(CMTimeRange)timeRange;

/*!
	@method			removeTimeRange:
	@abstract		Removes a specified time range from a track.
	@param			timeRange
					The time range to be removed.
*/
- (void)removeTimeRange:(CMTimeRange)timeRange;

/*!
	@method			scaleTimeRange:toDuration:
	@abstract		Changes the duration of a time range of a track.
	@param			timeRange
					The time range to be scaled.
	@param			duration
					The new duration of the time range.
*/
- (void)scaleTimeRange:(CMTimeRange)timeRange toDuration:(CMTime)duration;

@end


@interface AVMutableMovieTrack (AVMutableMovieTrackMetadataEditing)

/*!
	@property       metadata
	@abstract       A collection of metadata stored by the track.
	@discussion     The value of this property is an array of AVMetadataItem objects representing the collection of metadata stored by the track.
*/
@property (nonatomic, copy) NSArray<AVMetadataItem *> *metadata;

@end


@interface AVMutableMovieTrack (AVMutableMovieTrackTrackAssociations)

/*!
	@method			addTrackAssociationToTrack:type:
	@abstract		Establishes a track association of a specific type between two tracks.
	@param			movieTrack
					An AVMovieTrack object that is to be associated with the receiver.
	@param			trackAssociationType
					The type of track association to add between the receiver and the specified movieTrack (for instance, AVTrackAssociationTypeChapterList).
*/
- (void)addTrackAssociationToTrack:(AVMovieTrack *)movieTrack type:(AVTrackAssociationType)trackAssociationType;

/*!
	@method			removeTrackAssociationToTrack:type:
	@abstract		Removes a track association of a specific type between two tracks.
	@param			movieTrack
					An AVMovieTrack object that is associated with the receiver.
	@param			trackAssociationType
					The type of track association to remove between the receiver and the specified movieTrack (for instance, AVTrackAssociationTypeChapterList).
*/
- (void)removeTrackAssociationToTrack:(AVMovieTrack *)movieTrack type:(AVTrackAssociationType)trackAssociationType;

@end

@interface AVMutableMovieTrack (AVMutableMovieTrackFormatDescriptions)

/*!
	@method			replaceFormatDescription:withFormatDescription:
	@abstract		Replaces one of the receiver's format descriptions with another format description
	@param			formatDescription
					A CMFormatDescription occurring in the array returned by the -formatDescriptions method.
	@param			newFormatDescription
					A CMFormatDescription to replace the specified format description.
	@discussion     You can use this method to make surgical changes to a track's format descriptions, such as adding format description extensions to a format description or changing the audio channel layout of an audio track. You should note that a format description can have extensions of type kCMFormatDescriptionExtension_VerbatimSampleDescription and kCMFormatDescriptionExtension_VerbatimISOSampleEntry; if you modify a copy of a format description, you should delete those extensions from the copy or your changes might be ignored.
 
					An NSInvalidArgumentException will be thrown if the media type of the new format description does not match the media type of the receiver.
*/
- (void)replaceFormatDescription:(CMFormatDescriptionRef)formatDescription withFormatDescription:(CMFormatDescriptionRef)newFormatDescription API_AVAILABLE(macos(10.13), ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos);

@end


@interface AVMutableMovieTrack (AVMutableMovieTrackSampleLevelEditing)

/*!
	@method			appendSampleBuffer:decodeTime:presentationTime:error:
	@abstract		Appends sample data to a media file and adds sample references for the added data to a track's media sample tables.
	@param			sampleBuffer
					The CMSampleBuffer to be appended; this may be obtained from an instance of AVAssetReader.
	@param			outDecodeTime
					A pointer to a CMTime structure to receive the decode time in the media of the first sample appended from the sample buffer. Pass NULL if you do not need this information.
	@param			outPresentationTime
					A pointer to a CMTime structure to receive the presentation time in the media of the first sample appended from the sample buffer. Pass NULL if you do not need this information.
	@param			outError
					If the appending fails, describes the nature of the failure. For example, if the device containing the track's media data storage is full, AVErrorDiskFull is returned.
	@result			A BOOL value indicating the success of the operation.
	@discussion
                    If the sample buffer carries sample data, the sample data is written to the container specified by the track property mediaDataStorage if non-nil,
                    or else by the movie property defaultMediaDataStorage if non-nil, and sample references will be appended to the track's media.
                    If both media data storage properties are nil, the method will fail and return NO.
                    If the sample buffer carries sample references only, sample data will not be written and sample references to the samples in their
                    original container will be appended to the track's media as necessary.

                    Note regarding sample timing: in a track's media, the first sample's decode timestamp must always be zero.
                    For an audio track, each sample buffer's duration is used as the sample decode duration.
                    For other track types, difference between a sample's decode timestamp and the following 
                    sample's decode timestamp is used as the first sample's decode duration, so as to preserve the relative timing.
                    
                    Note that this method does not modify the track's sourceTimeMappings but only appends sample references and sample data to the track's media.  
                    To make the new samples appear in the track's timeline, invoke -insertMediaTimeRange:intoTimeRange:.
                    You can retrieve the mediaPresentationTimeRange property before and after appending a sequence of samples,
                    using CMTimeRangeGetEnd on each to calculate the media TimeRange for -insertMediaTimeRange:intoTimeRange:.

                    It's safe for multiple threads to call this method on different tracks at once.
*/
- (BOOL)appendSampleBuffer:(CMSampleBufferRef)sampleBuffer decodeTime:(nullable CMTime *)outDecodeTime presentationTime:(nullable CMTime *)outPresentationTime error:(NSError * _Nullable * _Nullable)outError API_AVAILABLE(macos(10.12), ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos);

/*!
	@method			insertMediaTimeRange:intoTimeRange:
	@abstract		Inserts a reference to a media time range into a track.
	@param			mediaTimeRange
					The presentation time range of the media to be inserted.
	@param			trackTimeRange
					The time range of the track into which the media is to be inserted.
    @result			A BOOL value indicating the success of the operation.
	@discussion
                    Use this method after you have appended samples or sample references to a track's media.
                    
                    To specify that the media time range be played at its natural rate, pass mediaTimeRange.duration == trackTimeRange.duration;
                    otherwise, the ratio between these is used to determine the playback rate.
                    
                    Pass kCMTimeInvalid for trackTimeRange.start to indicate that the segment should be appended to the end of the track.
*/
- (BOOL)insertMediaTimeRange:(CMTimeRange)mediaTimeRange intoTimeRange:(CMTimeRange)trackTimeRange API_AVAILABLE(macos(10.12), ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos);

@end


#pragma mark --- AVFragmentedMovieTrack ---
/*!
	@class			AVFragmentedMovieTrack
	@abstract		A subclass of AVMovieTrack for handling tracks of fragmented movie files. An AVFragmentedMovieTrack is capable of changing the values of certain of its properties, if its parent movie is associated with an instance of AVFragmentedMovieMinder when one or more movie fragments are appended to the movie file.
*/

/*!
 @constant       AVFragmentedMovieTrackTimeRangeDidChangeNotification
 @abstract       Posted when the timeRange of an AVFragmentedMovieTrack changes while the associated instance of AVFragmentedMovie is being minded by an AVFragmentedMovieMinder, but only for changes that occur after the status of the value of @"timeRange" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVFragmentedMovieTrackTimeRangeDidChangeNotification API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos);

/*!
 @constant       AVFragmentedMovieTrackSegmentsDidChangeNotification
 @abstract       Posted when the array of segments of an AVFragmentedMovieTrack changes while the associated instance of AVFragmentedMovie is being minded by an AVFragmentedMovieMinder, but only for changes that occur after the status of the value of @"segments" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVFragmentedMovieTrackSegmentsDidChangeNotification API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos);

/*!
 @constant       AVFragmentedMovieTrackTotalSampleDataLengthDidChangeNotification
 @discussion     This notification name has been deprecated. Use either AVFragmentedMovieTrackTimeRangeDidChangeNotification or AVFragmentedMovieTrackSegmentsDidChangeNotification instead; in either case, you can assume that timing changes to fragmented tracks result in changes to the total length of the sample data used by the track.
*/
AVF_EXPORT NSString *const AVFragmentedMovieTrackTotalSampleDataLengthDidChangeNotification API_DEPRECATED("Upon receipt of either AVFragmentedMovieTrackTimeRangeDidChangeNotification or AVFragmentedMovieTrackSegmentsDidChangeNotification, you can assume that the sender's totalSampleDataLength has changed.", macos(10.10, 10.11)) API_UNAVAILABLE(ios, tvos, watchos);

@class AVFragmentedMovieTrackInternal;

API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0)) API_UNAVAILABLE(tvos)
@interface AVFragmentedMovieTrack : AVMovieTrack
{
@private
	AVFragmentedMovieTrackInternal	*_fragmentedMovieTrack __attribute__((unused));
}

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVMovieTrack.h>
#endif

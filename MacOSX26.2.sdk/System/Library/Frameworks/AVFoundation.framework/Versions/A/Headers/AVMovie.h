#if !__has_include(<AVFCore/AVMovie.h>)
/*
	File:			AVMovie.h

	Framework:		AVFoundation
 
	Copyright 2009-2023 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>

#import <AVFoundation/AVAsset.h>
#import <AVFoundation/AVMovieTrack.h>

NS_ASSUME_NONNULL_BEGIN

/*!
    @class			AVMovie

    @abstract		AVMovie represents the audiovisual containers in a file that conforms to the QuickTime movie file format or to one of the related ISO base media file formats (such as MPEG-4).

	@discussion     AVMovie supports operations involving the format-specific portions of the QuickTime Movie model that are not supported by AVAsset. For instance, you can retrieve the movie header from an existing QuickTime movie file. You can also use AVMovie to write a movie header into a new file, thereby creating a reference movie.
  
                    A mutable subclass of AVMovie, AVMutableMovie, provides methods that support the familiar Movie editing model; for instance, you can use AVMutableMovie to copy media data from one track and paste that data into another track. You can also use AVMutableMovie to establish track references from one track to another (for example, to set one track as a chapter track of another track). If you want to perform editing operations on individual tracks, you can use the associated classes AVMovieTrack and AVMutableMovieTrack.
 
                    You need to use AVMovie and AVMutableMovie only when operating on format-specific features of a QuickTime or ISO base media file. You generally do not need to use these classes just to open and play QuickTime movie files or ISO base media files. Instead, you can use the classes AVURLAsset and AVPlayerItem. If however you already have an AVMutableMovie and want to play it or inspect it, you can make an immutable snapshot of the AVMutableMovie like this:
 
			 // myMutableMovie is of type AVMutableMovie; the client wants to inspect and play it in its current state
			 AVMovie *immutableSnapshotOfMyMovie = [myMutableMovie copy];
			 AVPlayerItem *playerItemForSnapshotOfMovie = [[AVPlayerItem alloc] initWithAsset:immutableSnapshotOfMyMovie]; 
 
 					When performing media insertions, AVMutableMovie interleaves the media data from the tracks in the source asset in order to create movie files that are optimized for playback. It's possible, however, that performing a series of media insertions may result in a movie file that is not optimally interleaved. You can create a well-interleaved, self-contained, fast-start movie file from an instance of AVMutableMovie by passing that instance to an AVAssetExportSession using the export preset AVAssetExportPresetPassthrough and setting the setShouldOptimizeForNetworkUse property to YES.

					AVMovie conforms to NSMutableCopying, but creating a mutable copy of a movie can cause its properties to be loaded synchronously.  This can cause the calling thread to block while synchronous I/O is performed.  To avoid the worst side-effects of blocking, such as user interface hangs, avoid making a mutable copy from the main thread or from a thread owned by Swift's concurrency thread pool.

*/

// Keys for options dictionary for use with various AVMovie initialization methods

/*!
  @constant		AVMovieReferenceRestrictionsKey
  @abstract
	Indicates the restrictions used by the movie when resolving references to external media data. The value of this key is an NSNumber wrapping an AVAssetReferenceRestrictions enum value or the logical combination of multiple such values. See AVAsset.h for the declaration of the AVAssetReferenceRestrictions enum.
  @discussion
	Some movies can contain references to media data stored outside the movie's container, for example in another file. This key can be used to specify a policy to use when these references are encountered. If a movie contains one or more references of a type that is forbidden by the reference restrictions, loading of movie properties will fail. In addition, such a movie cannot be used with other AVFoundation modules, such as AVPlayerItem or AVAssetExportSession.
*/
AVF_EXPORT NSString *const AVMovieReferenceRestrictionsKey API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

@class AVMovieInternal;
@class AVMediaDataStorage;
@class AVMetadataItem;

#pragma mark --- AVMovie ---
API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVMovie : AVAsset <NSCopying, NSMutableCopying>
{
@private
	AVMovieInternal *_movie;
}

/*!
	@method			movieTypes
	@abstract		Provides the file types the AVMovie class understands.
	@result			An NSArray of UTIs identifying the file types the AVMovie class understands.
*/
+ (NSArray<AVFileType> *)movieTypes;

/*!
	@method			movieWithURL:options:
	@abstract		Creates an AVMovie object from a movie header stored in a QuickTime movie file or ISO base media file.
	@param			URL
					An NSURL object that specifies a file containing a movie header.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMovie object.
	@result			An AVMovie object
	@discussion     By default, the defaultMediaDataStorage property will be nil and each associated AVMovieTrack's mediaDataStorage property will be nil.
                    If you want to create an AVMutableMovie from a file and then append sample buffers to any of its tracks, you must first set one of these properties 
                    to indicate where the sample data should be written.
*/
+ (instancetype)movieWithURL:(NSURL *)URL options:(nullable NSDictionary<NSString *, id> *)options;

/*!
	@method			initWithURL:options:
	@abstract		Creates an AVMovie object from a movie header stored in a QuickTime movie file or ISO base media file.
	@param			URL
					An NSURL object that specifies a file containing a movie header.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMovie object.
	@result			An AVMovie object
	@discussion     By default, the defaultMediaDataStorage property will be nil and each associated AVMovieTrack's mediaDataStorage property will be nil.
                    If you want to create an AVMutableMovie from a file and then append sample buffers to any of its tracks, you must first set one of these properties 
                    to indicate where the sample data should be written.
*/
- (instancetype)initWithURL:(NSURL *)URL options:(nullable NSDictionary<NSString *, id> *)options NS_DESIGNATED_INITIALIZER;

/*!
	@method			movieWithData:options:
	@abstract		Creates an AVMovie object from a movie header stored in an NSData object.
	@param			data
					An NSData object containing a movie header.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMovie object.
	@result			An AVMovie object
	@discussion     You can use this method to operate on movie headers that are not stored in files; this might include movie headers on the pasteboard (which do not contain media data). In general you should avoid loading an entire movie file with its media data into an instance of NSData! By default, the defaultMediaDataStorage property will be nil and each associated AVMovieTrack's mediaDataStorage property will be nil.
                    If you want to create an AVMutableMovie from an NSData object and then append sample buffers to any of its tracks, you must first set one of these properties to indicate where the sample data should be written.
*/
+ (instancetype)movieWithData:(NSData *)data options:(nullable NSDictionary<NSString *, id> *)options API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

/*!
	@method			initWithData:options:
	@abstract		Creates an AVMovie object from a movie header stored in an NSData object.
	@param			data
					An NSData object containing a movie header.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMovie object.
	@result			An AVMovie object
	@discussion     You can use this method to operate on movie headers that are not stored in files. In general you should avoid loading an entire movie file with its media data into an instance of NSData!
 
                    By default, the defaultMediaDataStorage property will be nil and each associated AVMovieTrack's mediaDataStorage property will be nil. If you want to create an AVMutableMovie from an NSData object and then append sample buffers to any of its tracks, you must first set one of these properties to indicate where the sample data should be written.
*/
- (instancetype)initWithData:(NSData *)data options:(nullable NSDictionary<NSString *, id> *)options NS_DESIGNATED_INITIALIZER API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

#pragma mark --- Keys for initialization options dictionary ---
/*!
	@constant		AVMovieShouldSupportAliasDataReferencesKey
	@abstract		Indicates whether alias data references in the movie should be parsed and resolved.
	@discussion
		Default is NO. Although the majority of QuickTime movie files contain all of the media data they require, some contain references to media stored in other files. While AVFoundation and CoreMedia typically employ a URL reference for this purpose, older implementations such as QuickTime 7 have commonly employed a Macintosh alias instead, as documented in the QuickTime File Format specification. If your application must work with legacy QuickTime movie files containing alias-based references to media data stored in other files, the use of this AVMovie initialization option is appropriate. AVMovie and AVMutableMovie do not create movies using alias data references to external media files.
 
	If you provide a value for AVMovieReferenceRestrictionsKey, restrictions will be observed for resolved alias references just as they are for URL references.
 
	For more details about alias resolution, consult documentation of the bookmark-related interfaces of NSURL.
*/
AVF_EXPORT NSString *const AVMovieShouldSupportAliasDataReferencesKey API_AVAILABLE(macos(10.12), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

/*!
	@property       URL
	@abstract       The URL with which the instance of AVMovie was initialized; may be nil.
*/
@property (nonatomic, readonly, nullable) NSURL *URL;

/*!
	@property       data
	@abstract       The data block with which the instance of AVMovie was initialized; may be nil.
*/
@property (nonatomic, readonly, nullable) NSData *data API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

/*!
	@property       defaultMediaDataStorage
	@abstract       The default storage container for media data added to a movie.
	@discussion     The value of this property is an AVMediaDataStorage object that indicates where sample data that is added to a movie should be written by default.
*/
@property (nonatomic, readonly, nullable) AVMediaDataStorage *defaultMediaDataStorage API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

/*!
	@property       tracks
	@abstract       The tracks in a movie.
	@discussion     The value of this property is an array of tracks the movie contains; the tracks are of type AVMovieTrack.
*/
@property (nonatomic, readonly) NSArray<AVMovieTrack *> *tracks;

/*!
	@property       canContainMovieFragments
	@abstract       Indicates whether the movie file is capable of being extended by fragments.
	@discussion     The value of this property is YES if an 'mvex' box is present in the 'moov' box. The 'mvex' box is necessary in order to signal the possible presence of later 'moof' boxes.
*/
@property (nonatomic, readonly) BOOL canContainMovieFragments;

/*!
	@property       containsMovieFragments
	@abstract       Indicates whether the movie file is extended by at least one movie fragment.
	@discussion     The value of this property is YES if canContainMovieFragments is YES and at least one 'moof' box is present after the 'moov' box.
*/
@property (nonatomic, readonly) BOOL containsMovieFragments API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

@end

/*!
	@enum			AVMovieWritingOptions
	@abstract		These options can be passed into writeMovieHeaderToURL:fileType:options:error: to control the writing of a movie header to a destination URL.
	@constant		AVMovieWritingAddMovieHeaderToDestination
					Writing the movie header will remove any existing movie header in the destination file and add a new movie header, preserving any other data in the file. If the destination file was empty, a file type box will be written at the beginning of the file.
	@constant		AVMovieWritingTruncateDestinationToMovieHeaderOnly
					If set, writing the movie header will truncate all existing data in the destination file and write a new movie header, thereby creating a pure reference movie file. A file type box will be written at the beginning of the file.
	@discussion     You would not want to use the AVMovieWritingTruncateDestinationToMovieHeaderOnly option if you had written sample data to the destination file using (for example) -[AVMutableMovie insertTimeRange:ofAsset:atTime:copySampleData:error:] with copySampleData set to YES, since that data would be lost.
 */
typedef NS_OPTIONS(NSUInteger, AVMovieWritingOptions) {
	AVMovieWritingAddMovieHeaderToDestination =					0,
	AVMovieWritingTruncateDestinationToMovieHeaderOnly =		(1UL << 0)
} API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVMovie (AVMovieMovieHeaderSupport)

/*!
	@method			movieHeaderWithFileType:error:
	@abstract		Creates an NSData object containing the movie header of the AVMovie object.
	@param			fileType
					A UTI indicating the specific file format of the movie header (e.g. AVFileTypeQuickTimeMovie for a QuickTime movie).
	@param			outError
					If an error occurs reading the movie header, describes the nature of the failure.
	@result			An NSData object.
	@discussion     The movie header will be a pure reference movie, with no base URL, suitable for use on the pasteboard.
*/
- (nullable NSData *)movieHeaderWithFileType:(AVFileType)fileType error:(NSError * _Nullable * _Nullable)outError API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

/*!
	@method			writeMovieHeaderToURL:fileType:options:error:
	@abstract		Writes the movie header to a destination URL.
	@param			URL
					An NSURL object indicating where to write the movie header.
	@param			fileType
					A UTI indicating the specific file format (e.g. AVFileTypeQuickTimeMovie for a QuickTime movie).
	@param			options
                    An NSUInteger whose bits specify options for the writing of the movie header. See AVMovieWritingOptions above.
	@param			outError
					If an error occurs writing the movie header, describes the nature of the failure.
	@discussion		Note that modifications to instances of AVMutableMovie, to their constituent AVMutableMovieTracks, or to their collections of metadata are committed to storage when their movie headers are written.
*/
- (BOOL)writeMovieHeaderToURL:(NSURL *)URL fileType:(AVFileType)fileType options:(AVMovieWritingOptions)options error:(NSError * _Nullable * _Nullable)outError API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

/*!
	@method			isCompatibleWithFileType:
	@abstract		Indicates whether a movie header for the AVMovie object can be created for the specified file type.
	@param			fileType
					A UTI indicating a movie file format (e.g. AVFileTypeQuickTimeMovie for a QuickTime movie).
	@discussion     This method returns a BOOL that indicates whether a movie header of the specified type can be created for the receiver. For example, this method returns NO if the movie contains tracks whose media types or media subtypes are not allowed by the specified file type.
*/
- (BOOL)isCompatibleWithFileType:(AVFileType)fileType API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

@end

API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVMovie (AVMovieTrackInspection)

/*!
  @method		trackWithTrackID:
  @abstract		Provides an instance of AVMovieTrack that represents the track of the specified trackID.
  @param		trackID
				The trackID of the requested AVMovieTrack.
  @result		An instance of AVMovieTrack; may be nil if no track of the specified trackID is available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (nullable AVMovieTrack *)trackWithTrackID:(CMPersistentTrackID)trackID
#if __swift__
API_DEPRECATED("Use loadTrack(withTrackID:) instead", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0)) API_UNAVAILABLE(visionos);
#else
API_DEPRECATED("Use loadTrackWithTrackID:completionHandler: instead", macos(10.7, 15.0), ios(4.0, 18.0), tvos(9.0, 18.0), watchos(1.0, 11.0)) API_UNAVAILABLE(visionos);
#endif

/*!
	@method		loadTrackWithTrackID:completionHandler:
	@abstract	Loads an instance of AVMovieTrack that represents the track of the specified trackID.
	@param		trackID
				The trackID of the requested AVMovieTrack.
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded track (which may be nil if no track of the specified trackID is available) or an error.
*/
- (void)loadTrackWithTrackID:(CMPersistentTrackID)trackID completionHandler:(void (^ NS_SWIFT_SENDABLE)(AVMovieTrack * _Nullable_result, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
  @method		tracksWithMediaType:
  @abstract		Provides an array of AVMovieTracks of the asset that present media of the specified media type.
  @param		mediaType
				The media type according to which the receiver filters its AVMovieTracks. (Media types are defined in AVMediaFormat.h)
  @result		An NSArray of AVMovieTracks; may be empty if no tracks of the specified media type are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVMovieTrack *> *)tracksWithMediaType:(AVMediaType)mediaType
#if __swift__
API_DEPRECATED("Use loadTracks(withMediaType:) instead", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0)) API_UNAVAILABLE(visionos);
#else
API_DEPRECATED("Use loadTracksWithMediaType:completionHandler: instead", macos(10.7, 15.0), ios(4.0, 18.0), tvos(9.0, 18.0), watchos(1.0, 11.0)) API_UNAVAILABLE(visionos);
#endif

/*!
	@method		loadTracksWithMediaType:completionHandler:
	@abstract	Loads an array of AVMovieTracks of the asset that present media of the specified media type.
	@param		mediaType
				The media type according to which AVAsset filters its AVMovieTracks. (Media types are defined in AVMediaFormat.h.)
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks of the specified media type are available) or an error.
*/
- (void)loadTracksWithMediaType:(AVMediaType)mediaType completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSArray<AVMovieTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
  @method		tracksWithMediaCharacteristic:
  @abstract		Provides an array of AVMovieTracks of the asset that present media with the specified characteristic.
  @param		mediaCharacteristic
				The media characteristic according to which the receiver filters its AVMovieTracks. (Media characteristics are defined in AVMediaFormat.h)
  @result		An NSArray of AVMovieTracks; may be empty if no tracks with the specified characteristic are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVMovieTrack *> *)tracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic
#if __swift__
API_DEPRECATED("Use loadTracks(withMediaCharacteristic:) instead", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0)) API_UNAVAILABLE(visionos);
#else
API_DEPRECATED("Use loadTracksWithMediaCharacteristic:completionHandler: instead", macos(10.7, 15.0), ios(4.0, 18.0), tvos(9.0, 18.0), watchos(1.0, 11.0)) API_UNAVAILABLE(visionos);
#endif

/*!
	@method		loadTracksWithMediaCharacteristic:completionHandler:
	@abstract	Loads an array of AVMovieTracks of the asset that present media with the specified characteristic.
	@param		mediaCharacteristic
				The media characteristic according to which AVAsset filters its AVMovieTracks. (Media characteristics are defined in AVMediaFormat.h.)
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks with the specified characteristic are available) or an error.
*/
- (void)loadTracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSArray<AVMovieTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

@end


@class AVAsset;
@class AVMovieTrack;
@class AVMutableMovieTrack;
@class AVMutableMovieInternal;

#pragma mark --- AVMutableMovie ---
/*!
    @class			AVMutableMovie

    @abstract       AVMutableMovie adds to its immutable superclass, AVMovie, several categories of methods for editing QuickTime movie files, e.g. inserting and removing time ranges of media, adding and removing tracks, and modifying the metadata collections stored therein.

	@discussion     By default, after creating an AVMutableMovie the defaultMediaDataStorage property will be nil and each associated AVMutableMovieTrack's mediaDataStorage property will be nil. If you want to create an AVMutableMovie from a file and then append sample buffers to any of its tracks, you must first set one of these properties to indicate where the sample data should be written.
*/

NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVMutableMovie : AVMovie
{
@private
    AVMutableMovieInternal *_mutableMovieInternal;
}

/*!
	@method			movieWithURL:options:error:
	@abstract		Creates an AVMutableMovie object from a movie header stored in a QuickTime movie file or ISO base media file.
	@param			URL
					An NSURL object that specifies a file containing a movie header.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMutableMovie object.
	@param			outError
					If an error occurs creating a movie, describes the nature of the failure.
	@result			An AVMutableMovie object
	@discussion     By default, the defaultMediaDataStorage property will be nil and each associated AVMutableMovieTrack's mediaDataStorage property will be nil.
                    If you want to create an AVMutableMovie from a file and then append sample buffers to any of its tracks, you must first set one of these properties 
                    to indicate where the sample data should be written.
*/
+ (nullable instancetype)movieWithURL:(NSURL *)URL options:(nullable NSDictionary<NSString *, id> *)options error:(NSError * _Nullable * _Nullable)outError;

/*!
	@method			initWithURL:options:error:
	@abstract		Creates an AVMutableMovie object from a movie header stored in a QuickTime movie file or ISO base media file.
	@param			URL
					An NSURL object that specifies a file containing a movie header.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMutableMovie object.
	@param			outError
					If an error occurs creating a movie, describes the nature of the failure.
	@result			An AVMutableMovie object
	@discussion     By default, the defaultMediaDataStorage property will be nil and each associated AVMutableMovieTrack's mediaDataStorage property will be nil.
                    If you want to create an AVMutableMovie from a file and then append sample buffers to any of its tracks, you must first set one of these properties 
                    to indicate where the sample data should be written.
*/
- (nullable instancetype)initWithURL:(NSURL *)URL options:(nullable NSDictionary<NSString *, id> *)options error:(NSError * _Nullable * _Nullable)outError NS_DESIGNATED_INITIALIZER;

/*!
	@method			movieWithData:options:error:
	@abstract		Creates an AVMutableMovie object from a movie header stored in an NSData object.
	@param			data
					An NSData object containing a movie header.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMutableMovie object.
	@param			outError
					If an error occurs creating a movie, describes the nature of the failure.
	@result			An AVMutableMovie object
	@discussion     You can use this method to operate on movie headers that are not stored in files. In general you should avoid loading an entire movie file with its media data into an instance of NSData!
 
                    By default, the defaultMediaDataStorage property will be nil and each associated AVMutableMovieTrack's mediaDataStorage property will be nil. If you want to create an AVMutableMovie from an NSData object and then append sample buffers to any of its tracks, you must first set one of these properties to indicate where the sample data should be written.
*/
+ (nullable instancetype)movieWithData:(NSData *)data options:(nullable NSDictionary<NSString *, id> *)options error:(NSError * _Nullable * _Nullable)outError API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

/*!
	@method			initWithData:options:error:
	@abstract		Creates an AVMutableMovie object from a movie header stored in an NSData object.
	@param			data
					An NSData object containing a movie header.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMutableMovie object.
	@param			outError
					If an error occurs creating a movie, describes the nature of the failure.
	@result			An AVMutableMovie object
	@discussion     You can use this method to operate on movie headers that are not stored in files. In general you should avoid loading an entire movie file with its media data into an instance of NSData!
 
                    By default, the defaultMediaDataStorage property will be nil and each associated AVMutableMovieTrack's mediaDataStorage property will be nil. If you want to create an AVMutableMovie from an NSData object and then append sample buffers to any of its tracks, you must first set one of these properties to indicate where the sample data should be written.
*/
- (nullable instancetype)initWithData:(NSData *)data options:(nullable NSDictionary<NSString *, id> *)options error:(NSError * _Nullable * _Nullable)outError NS_DESIGNATED_INITIALIZER;

/*!
	@method			movieWithSettingsFromMovie:options:error:
	@abstract		Creates an AVMutableMovie object without tracks (and therefore without media).
	@param			movie
					If you wish to transfer settings from an existing movie (including movie userdata and metadata, preferred rate, preferred volume, etc.), pass a reference to an AVMovie object representing that movie. Otherwise pass nil. The userdata and metadata from the source movie may need to be converted if the format of that movie differs from fileType; you may wish to inspect the userdata or metadata of the receiver to ensure that important data was copied.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMutableMovie object. Pass nil for default initialization behavior.
	@param			outError
					If an error occurs creating a movie, describes the nature of the failure.
	@result			An AVMutableMovie object
	@discussion
                    By default, the defaultMediaDataStorage property will be nil and each associated AVMovieTrack's mediaDataStorage property will be nil.
                    If you want to create an AVMutableMovie from an NSData object and then append sample buffers to any of its tracks, you must first set one of these properties to indicate where the sample data should be written.
*/
+ (nullable instancetype)movieWithSettingsFromMovie:(nullable AVMovie *)movie options:(nullable NSDictionary<NSString *, id> *)options error:(NSError * _Nullable * _Nullable)outError;

/*!
	@method			initWithSettingsFromMovie:options:error:
	@abstract		Creates an AVMutableMovie object without tracks (and therefore without media).
	@param			movie
					If you wish to transfer settings from an existing movie (including movie userdata and metadata, preferred rate, preferred volume, etc.), pass a reference to an AVMovie object representing that movie. Otherwise pass nil. The userdata and metadata from the source movie may need to be converted if the format of that movie differs from fileType; you may wish to inspect the userdata or metadata of the receiver to ensure that important data was copied.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMutableMovie object. Pass nil for default initialization behavior.
	@param			outError
					If an error occurs creating a movie, describes the nature of the failure.
	@result			An AVMutableMovie object
	@discussion
                    By default, the defaultMediaDataStorage property will be nil and each associated AVMovieTrack's mediaDataStorage property will be nil.
                    If you want to create an AVMutableMovie from an NSData object and then append sample buffers to any of its tracks, you must first set one of these properties to indicate where the sample data should be written.
*/
- (nullable instancetype)initWithSettingsFromMovie:(nullable AVMovie *)movie options:(nullable NSDictionary<NSString *, id> *)options error:(NSError * _Nullable * _Nullable)outError NS_DESIGNATED_INITIALIZER;

/*!
	@property       preferredRate
	@abstract       The natural rate at which the movie is to be played; often but not always 1.0.
*/
@property (nonatomic) float preferredRate;

/*!
	@property       preferredVolume
	@abstract       The preferred volume of the audible media data of the movie; often but not always 1.0.
*/
@property (nonatomic) float preferredVolume;

/*!
	@property       preferredTransform
	@abstract       A CGAffineTransform indicating the transform specified in the movie's storage container as the preferred transformation of the visual media data for display purposes; the value is often but not always CGAffineTransformIdentity.
*/
@property (nonatomic) CGAffineTransform preferredTransform;

/*!
	@property       timescale
	@abstract       For file types that contain a 'moov' atom, such as QuickTime Movie files, specifies the time scale of the movie.
	@discussion		The default movie time scale is 600. In certain cases, you may want to set this to a different value. For instance, a movie that
					contains a single audio track should typically have the movie time scale set to the media time scale of that track.
 
					This property should be set on a new empty movie before any edits are performed on the movie.
*/
@property (nonatomic, readwrite) CMTimeScale timescale;

/*!
	@property       tracks
	@abstract       The tracks in a mutable movie.
	@discussion     The value of this property is an array of tracks the mutable movie contains; the tracks are of type AVMutableMovieTrack.
*/
@property (nonatomic, readonly) NSArray<AVMutableMovieTrack *> *tracks;

@end

API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVMutableMovie (AVMutableMovieMovieLevelEditing)

/*!
	@property       modified
	@abstract       Whether a movie has been modified.
	@discussion     The value of this property is a BOOL that indicates whether the AVMutableMovie object has been modified since it was created, was last written, or had its modified state cleared via a call to setModified:NO.
*/
@property (nonatomic, getter=isModified) BOOL modified;

/*!
	@property       defaultMediaDataStorage
	@abstract       The default storage container for media data added to a movie.
	@discussion     The value of this property is an AVMediaDataStorage object that indicates where sample data that is added to a movie should be written, for any track for whose mediaDataStorage property is nil.
*/
@property (nonatomic, copy, nullable) AVMediaDataStorage *defaultMediaDataStorage;

/*!
	@property		interleavingPeriod
	@abstract		A CMTime that indicates the duration for interleaving runs of samples of each track.
	@discussion		The default interleaving period is 0.5 seconds.
 */
@property (nonatomic) CMTime interleavingPeriod;

/*!
	@method			insertTimeRange:ofAsset:atTime:copySampleData:error:
	@abstract		Inserts all the tracks of a timeRange of an asset into a movie.
	@param			timeRange
					The time range of the asset to be inserted.
	@param			asset
					An AVAsset object indicating the source of the inserted media. Only instances of AVURLAsset and AVComposition are supported.
					Must not be nil.
	@param			startTime
					The time in the target movie at which the media is to be inserted.
	@param			copySampleData
                    A BOOL value that indicates whether sample data is to be copied from the source to the destination during edits.
					If YES, the sample data is written to the location specified by the track property mediaDataStorage if non-nil,
					or else by the movie property defaultMediaDataStorage if non-nil; if both are nil, the method will fail and return NO.
					If NO, sample data will not be written and sample references to the samples in their original container will be added as necessary. 
					Note that in this case, this method will fail if the source AVAsset is not able to provide sample reference information for the original container.
	@param			outError
					If the insertion fails, an NSError object that describes the nature of the failure.
	@result			A BOOL value that indicates the success of the insertion.
	@discussion		This method may add new tracks to the target movie to ensure that all tracks of the asset are represented in the inserted timeRange.
					Existing content at the specified startTime will be pushed out by the duration of timeRange.
					Note that metadata will not be automatically copied.
*/
- (BOOL)insertTimeRange:(CMTimeRange)timeRange ofAsset:(AVAsset *)asset atTime:(CMTime)startTime copySampleData:(BOOL)copySampleData error:(NSError * _Nullable * _Nullable)outError;

/*!
	@method			insertEmptyTimeRange:
	@abstract		Adds an empty time range to the target movie.
	@param			timeRange
					The time range to be made empty. Note that you cannot add empty time ranges to the end of a movie.
*/
- (void)insertEmptyTimeRange:(CMTimeRange)timeRange;

/*!
	@method			removeTimeRange:
	@abstract		Removes a specified time range from a movie.
	@param			timeRange
					The time range to be removed.
*/
- (void)removeTimeRange:(CMTimeRange)timeRange;

/*!
	@method			scaleTimeRange:toDuration:
	@abstract		Changes the duration of a time range of a movie.
	@param			timeRange
					The time range to be scaled.
	@param			duration
					The new duration of the time range.
*/
- (void)scaleTimeRange:(CMTimeRange)timeRange toDuration:(CMTime)duration;

@end


API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVMutableMovie (AVMutableMovieTrackLevelEditing)

/*!
	@method			mutableTrackCompatibleWithTrack:
	@abstract		Provides a reference to a track of a mutable movie into which any time range of an AVAssetTrack
					can be inserted (via -[AVMutableMovieTrack insertTimeRange:ofTrack:atTime:copySampleData:error:]).
	@param			track
					A reference to the AVAssetTrack from which a time range may be inserted.
	@result			An AVMutableMovieTrack that can accommodate the insertion.
					If no such track is available, the result is nil. A new track of the same media type
					as the AVAssetTrack can be created via -addMutableTrackWithMediaType:copySettingsFromTrack:options:,
					and this new track will be compatible.
	@discussion		For best performance, the number of tracks in a movie should be kept to a minimum, corresponding to the
					number for which media data must be presented in parallel. If media data of the same type is to be presented
					serially, even from multiple assets, a single track of that media type should be used. This method,
					-mutableTrackCompatibleWithTrack:, can help the client to identify an existing target track for an insertion.
*/
- (nullable AVMutableMovieTrack *)mutableTrackCompatibleWithTrack:(AVAssetTrack *)track;

/*!
	@method			addMutableTrackWithMediaType:copySettingsFromTrack:options:
	@abstract		Adds an empty track to the target movie.
	@param			mediaType
					The media type of the new track (e.g. AVMediaTypeVideo for a video track).
	@param			track
					If you wish to transfer settings from an existing track, including width, height, preferred volume, etc., pass a reference to an AVAssetTrack representing that track. Otherwise pass nil.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the new AVMutableMovieTrack object. Pass nil for default initialization behavior.
	@result			An AVMutableMovieTrack object
	@discussion		The trackID of the newly added track is a property of the returned instance of AVMutableMovieTrack.
					This method throws an exception if media type is not equal to the track's media type, or if any option is invalid.
					Note that metadata will not be automatically copied.
*/
- (nullable AVMutableMovieTrack *)addMutableTrackWithMediaType:(AVMediaType)mediaType copySettingsFromTrack:(nullable AVAssetTrack *)track options:(nullable NSDictionary<NSString *, id> *)options;

/*!
	@method			addMutableTracksCopyingSettingsFromTracks:options:
	@abstract		Adds one or more empty tracks to the target movie, copying track settings from the source tracks.
	@param			existingTracks
					An array of AVAssetTrack objects.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the new AVMutableMovieTrack objects. Pass nil for default initialization behavior.
	@result			An array of AVMutableMovieTrack objects; the index of a track in this array is the same as the index of its source track in the existingTracks array.
    @discussion		This method creates one or more empty tracks in the target movie and configures those tracks with settings (such as track userdata and metadata, width, height, and preferred volume) copied from the source tracks in the existingTracks array. Also, properties involving pairs of tracks (such as track references) are copied from the source tracks to the target tracks.
					This method throws an exception if any option is invalid.
*/
- (NSArray<AVMutableMovieTrack *> *)addMutableTracksCopyingSettingsFromTracks:(NSArray<AVAssetTrack *> *)existingTracks options:(nullable NSDictionary<NSString *, id> *)options;

/*!
	@method			removeTrack:
	@abstract		Removes a track from the target movie.
	@param			track
					The track to be removed.
*/
- (void)removeTrack:(AVMovieTrack *)track;

@end


API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVMutableMovie (AVMutableMovieMetadataEditing)

/*!
	@property       metadata
	@abstract       A collection of metadata stored by the movie.
	@discussion     The value of this property is an array of AVMetadataItem objects representing the collection of metadata stored by the movie.
*/
@property (nonatomic, copy) NSArray<AVMetadataItem *> *metadata;

@end

API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVMutableMovie (AVMutableMovieTrackInspection)

/*!
  @method		trackWithTrackID:
  @abstract		Provides an instance of AVMutableMovieTrack that represents the track of the specified trackID.
  @param		trackID
				The trackID of the requested AVMutableMovieTrack.
  @result		An instance of AVMutableMovieTrack; may be nil if no track of the specified trackID is available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (nullable AVMutableMovieTrack *)trackWithTrackID:(CMPersistentTrackID)trackID;

/*!
	@method		loadTrackWithTrackID:completionHandler:
	@abstract	Loads an instance of AVMutableMovieTrack that represents the track of the specified trackID.
	@param		trackID
				The trackID of the requested AVMutableMovieTrack.
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded track (which may be nil if no track of the specified trackID is available) or an error.
*/
- (void)loadTrackWithTrackID:(CMPersistentTrackID)trackID completionHandler:(void (^ NS_SWIFT_SENDABLE)(AVMutableMovieTrack * _Nullable_result, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
  @method		tracksWithMediaType:
  @abstract		Provides an array of AVMutableMovieTracks of the asset that present media of the specified media type.
  @param		mediaType
				The media type according to which the receiver filters its AVMutableMovieTracks. (Media types are defined in AVMediaFormat.h)
  @result		An NSArray of AVMutableMovieTracks; may be empty if no tracks of the specified media type are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVMutableMovieTrack *> *)tracksWithMediaType:(AVMediaType)mediaType;

/*!
	@method		loadTracksWithMediaType:completionHandler:
	@abstract	Loads an array of AVMutableMovieTracks of the asset that present media of the specified media type.
	@param		mediaType
				The media type according to which AVAsset filters its AVMutableMovieTracks. (Media types are defined in AVMediaFormat.h.)
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks of the specified media type are available) or an error.
*/
- (void)loadTracksWithMediaType:(AVMediaType)mediaType completionHandler:(void ( NS_SWIFT_SENDABLE^)(NSArray<AVMutableMovieTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
  @method		tracksWithMediaCharacteristic:
  @abstract		Provides an array of AVMutableMovieTracks of the asset that present media with the specified characteristic.
  @param		mediaCharacteristic
				The media characteristic according to which the receiver filters its AVMutableMovieTracks. (Media characteristics are defined in AVMediaFormat.h)
  @result		An NSArray of AVMutableMovieTracks; may be empty if no tracks with the specified characteristic are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVMutableMovieTrack *> *)tracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic;

/*!
	@method		loadTracksWithMediaCharacteristic:completionHandler:
	@abstract	Loads an array of AVMutableMovieTracks of the asset that present media with the specified characteristic.
	@param		mediaCharacteristic
				The media characteristic according to which AVAsset filters its AVMutableMovieTracks. (Media characteristics are defined in AVMediaFormat.h.)
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks with the specified characteristic are available) or an error.
*/
- (void)loadTracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSArray<AVMutableMovieTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

@end


#pragma mark --- AVMediaDataStorage ---
@class AVMediaDataStorageInternal;

/*!
 @class         AVMediaDataStorage
 @abstract      Media sample data storage file.
 @discussion    Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVMediaDataStorage : NSObject {
@private
	AVMediaDataStorageInternal			*_mediaDataStorageInternal;
}
AV_INIT_UNAVAILABLE

/*!
	@method			initWithURL:options:
	@abstract		Creates an AVMediaDataStorage object associated with a file URL.
	@param			URL
					An NSURL object that specifies a file where sample data that is added to a movie or track should be written.
	@param			options
					An NSDictionary object that contains keys for specifying options for the initialization of the AVMediaDataStorage object. Currently no keys are defined.
	@result			An AVMediaDataStorage object
*/
- (instancetype)initWithURL:(NSURL *)URL options:(nullable NSDictionary<NSString *, id> *)options NS_DESIGNATED_INITIALIZER;

/*!
	@method			URL
	@abstract       The URL from which the receiver was initialized; may be nil.
*/
- (nullable NSURL *)URL;

@end


#pragma mark --- AVFragmentedMovie ---
/*!
	@class			AVFragmentedMovie
 
	@abstract		A subclass of AVMovie for handling fragmented movie files. An AVFragmentedMovie is capable of changing the values of certain of its properties and those of its tracks, if it's associated with an instance of AVFragmentedMovieMinder when one or more movie fragments are appended to the movie file.
 
	@discussion		Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/

/*!
 @constant       AVFragmentedMovieContainsMovieFragmentsDidChangeNotification
 @abstract       Posted after the value of @"containsMovieFragments" has already been loaded and the AVFragmentedMovie is added to an AVFragmentedMovieMinder, either when 1) movie fragments are detected in the movie file on disk after it had previously contained none or when 2) no movie fragments are detected in the movie file on disk after it had previously contained one or more.
*/
AVF_EXPORT NSString *const AVFragmentedMovieContainsMovieFragmentsDidChangeNotification API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

/*!
 @constant       AVFragmentedMovieDurationDidChangeNotification
 @abstract       Posted when the duration of an AVFragmentedMovie changes while it's being minded by an AVFragmentedMovieMinder, but only for changes that occur after the status of the value of @"duration" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVFragmentedMovieDurationDidChangeNotification API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

/*!
 @constant       AVFragmentedMovieWasDefragmentedNotification
 @abstract       Posted when the movie file on disk is defragmented while an AVFragmentedMovie is being minded by an AVFragmentedMovieMinder, but only if the defragmentation occurs after the status of the value of @"canContainMovieFragments" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVFragmentedMovieWasDefragmentedNotification API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos);

@class AVFragmentedMovieInternal;

NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVFragmentedMovie : AVMovie <AVFragmentMinding>
{
@private
}

/*!
	@property       tracks
	@abstract       The tracks in a movie.
	@discussion     The value of this property is an array of tracks the movie contains; the tracks are of type AVFragmentedMovieTrack.
*/
@property (nonatomic, readonly) NSArray<AVFragmentedMovieTrack *> *tracks;

@end

API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVFragmentedMovie (AVFragmentedMovieTrackInspection)

/*!
  @method		trackWithTrackID:
  @abstract		Provides an instance of AVFragmentedMovieTrack that represents the track of the specified trackID.
  @param		trackID
				The trackID of the requested AVFragmentedMovieTrack.
  @result		An instance of AVFragmentedMovieTrack; may be nil if no track of the specified trackID is available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (nullable AVFragmentedMovieTrack *)trackWithTrackID:(CMPersistentTrackID)trackID
#if __swift__
API_DEPRECATED("Use loadTrack(withTrackID:) instead", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0)) API_UNAVAILABLE(visionos);
#else
API_DEPRECATED("Use loadTrackWithTrackID:completionHandler: instead", macos(10.7, 15.0), ios(4.0, 18.0), tvos(9.0, 18.0), watchos(1.0, 11.0)) API_UNAVAILABLE(visionos);
#endif

/*!
	@method		loadTrackWithTrackID:completionHandler:
	@abstract	Loads an instance of AVFragmentedMovieTrack that represents the track of the specified trackID.
	@param		trackID
				The trackID of the requested AVFragmentedMovieTrack.
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded track (which may be nil if no track of the specified trackID is available) or an error.
*/
- (void)loadTrackWithTrackID:(CMPersistentTrackID)trackID completionHandler:(void (^ NS_SWIFT_SENDABLE)(AVFragmentedMovieTrack * _Nullable_result, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
  @method		tracksWithMediaType:
  @abstract		Provides an array of AVFragmentedMovieTracks of the asset that present media of the specified media type.
  @param		mediaType
				The media type according to which the receiver filters its AVFragmentedMovieTracks. (Media types are defined in AVMediaFormat.h)
  @result		An NSArray of AVFragmentedMovieTracks; may be empty if no tracks of the specified media type are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVFragmentedMovieTrack *> *)tracksWithMediaType:(AVMediaType)mediaType
#if __swift__
API_DEPRECATED("Use loadTracks(withMediaType:) instead", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0)) API_UNAVAILABLE(visionos);
#else
API_DEPRECATED("Use loadTracksWithMediaType:completionHandler: instead", macos(10.7, 15.0), ios(4.0, 18.0), tvos(9.0, 18.0), watchos(1.0, 11.0)) API_UNAVAILABLE(visionos);
#endif

/*!
	@method		loadTracksWithMediaType:completionHandler:
	@abstract	Loads an array of AVFragmentedMovieTracks of the asset that present media of the specified media type.
	@param		mediaType
				The media type according to which AVAsset filters its AVFragmentedMovieTracks. (Media types are defined in AVMediaFormat.h.)
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks of the specified media type are available) or an error.
*/
- (void)loadTracksWithMediaType:(AVMediaType)mediaType completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSArray<AVFragmentedMovieTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/*!
  @method		tracksWithMediaCharacteristic:
  @abstract		Provides an array of AVFragmentedMovieTracks of the asset that present media with the specified characteristic.
  @param		mediaCharacteristic
				The media characteristic according to which the receiver filters its AVFragmentedMovieTracks. (Media characteristics are defined in AVMediaFormat.h)
  @result		An NSArray of AVFragmentedMovieTracks; may be empty if no tracks with the specified characteristic are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVFragmentedMovieTrack *> *)tracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic
#if __swift__
API_DEPRECATED("Use loadTracks(withMediaCharacteristic:) instead", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0)) API_UNAVAILABLE(visionos);
#else
API_DEPRECATED("loadTracksWithMediaCharacteristic:completionHandler:", macos(10.7, 15.0), ios(4.0, 18.0), tvos(9.0, 18.0), watchos(1.0, 11.0)) API_UNAVAILABLE(visionos);
#endif

/*!
	@method		loadTracksWithMediaCharacteristic:completionHandler:
	@abstract	Loads an array of AVFragmentedMovieTracks of the asset that present media with the specified characteristic.
	@param		mediaCharacteristic
				The media characteristic according to which AVAsset filters its AVFragmentedMovieTracks. (Media characteristics are defined in AVMediaFormat.h.)
	@param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks with the specified characteristic are available) or an error.
*/
- (void)loadTracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic completionHandler:(void (^ NS_SWIFT_SENDABLE)(NSArray<AVFragmentedMovieTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

@end

#pragma mark --- AVFragmentedMovieMinder ---
/*!
	@class			AVFragmentedMovieMinder
	@abstract		A class that periodically checks whether additional movie fragments have been appended to fragmented movie files.
	@discussion		AVFragmentedMovieMinder is identical to AVFragmentedAssetMinder except that it's capable of minding only assets of class AVFragmentedMovie.
*/
NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(10.10), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVFragmentedMovieMinder : AVFragmentedAssetMinder

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
- (instancetype)initWithMovie:(AVFragmentedMovie *)movie mindingInterval:(NSTimeInterval)mindingInterval NS_DESIGNATED_INITIALIZER;

/*!
	@property       mindingInterval
	@abstract       An NSTimeInterval indicating how often a check for additional movie fragments should be performed. The default interval is 10.0.
*/
@property (nonatomic) NSTimeInterval mindingInterval;

/*!
	@property       movies
	@abstract       An NSArray of the AVFragmentedMovie objects being minded.
*/
@property (nonatomic, readonly) NSArray<AVFragmentedMovie *> *movies;

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

/*!
 @category AVMutableMovie (SynchronousAssetInterface)
 @abstract Redeclarations of async-only AVAsset interfaces to allow synchronous usage in the synchronous subclass.
 @discussion
	See AVAsset's interface for more information about these interfaces.
 */
API_AVAILABLE(macos(10.11), ios(13.0), watchos(6.0), visionos(1.0)) API_UNAVAILABLE(tvos)
@interface AVMutableMovie (SynchronousAssetInterface)

- (NSArray<AVMetadataItem *> *)metadataForFormat:(AVMetadataFormat)format;
- (NSArray<AVTimedMetadataGroup *> *)chapterMetadataGroupsWithTitleLocale:(NSLocale *)locale containingItemsWithCommonKeys:(nullable NSArray<AVMetadataKey> *)commonKeys;
- (NSArray<AVTimedMetadataGroup *> *)chapterMetadataGroupsBestMatchingPreferredLanguages:(NSArray<NSString *> *)preferredLanguages;
- (nullable AVMediaSelectionGroup *)mediaSelectionGroupForMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic;
- (CMPersistentTrackID)unusedTrackID;

#if __swift__
@property (nonatomic, readonly) CMTime duration;
@property (nonatomic, readonly) CMTime minimumTimeOffsetFromLive API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0), visionos(1.0));
@property (nonatomic, readonly) BOOL providesPreciseDurationAndTiming;
@property (nonatomic, readonly) NSArray<AVAssetTrackGroup *> *trackGroups API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));
@property (nonatomic, readonly, nullable) AVMetadataItem *creationDate API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0), visionos(1.0));
@property (nonatomic, readonly, nullable) NSString *lyrics;
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *commonMetadata;
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
#import <AVFCore/AVMovie.h>
#endif

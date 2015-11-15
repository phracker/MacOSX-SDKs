/*
	File:  AVAsset.h

	Framework:  AVFoundation
 
	Copyright 2010-2015 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>

#import <CoreGraphics/CGAffineTransform.h>

#import <CoreMedia/CMTime.h>

#pragma mark --- AVAsset ---
/*!
  @class		AVAsset

  @abstract
	An AVAsset is an abstract class that defines AVFoundation's model for timed audiovisual media.

	Each asset contains a collection of tracks that are intended to be presented or processed together, each of a uniform media type, including but not limited to audio, video, text, closed captions, and subtitles.

  @discussion
	AVAssets are often instantiated via its concrete subclass AVURLAsset with NSURLs that refer to audiovisual media resources, such as streams (including HTTP live streams), QuickTime movie files, MP3 files, and files of other types.

	They can also be instantiated using other concrete subclasses that extend the basic model for audiovisual media in useful ways, as AVComposition does for temporal editing.

	Properties of assets as a whole are defined by AVAsset. Additionally, references to instances of AVAssetTracks representing tracks of the collection can be obtained, so that each of these can be examined independently.
					
	Because of the nature of timed audiovisual media, upon successful initialization of an AVAsset some or all of the values for its keys may not be immediately available. The value of any key can be requested at any time, and AVAsset will always return its value synchronously, although it may have to block the calling thread in order to do so.

	In order to avoid blocking, clients can register their interest in particular keys and to become notified when their values become available. For further details, see AVAsynchronousKeyValueLoading.h.

	On iOS, it is particularly important to avoid blocking.  To preserve responsiveness, a synchronous request that blocks for too long (eg, a property request on an asset on a slow HTTP server) may lead to media services being reset.

	To play an instance of AVAsset, initialize an instance of AVPlayerItem with it, use the AVPlayerItem to set up its presentation state (such as whether only a limited timeRange of the asset should be played, etc.), and provide the AVPlayerItem to an AVPlayer according to whether the items is to be played by itself or together with a collection of other items. Full details available in AVPlayerItem.h and AVPlayer.h.
					
	AVAssets can also be inserted into AVMutableCompositions in order to assemble audiovisual constructs from one or more source assets.

*/

NS_ASSUME_NONNULL_BEGIN

@class AVAssetTrack;
@class AVFragmentedAssetTrack;
@class AVMetadataItem;
@class AVMediaSelection;
@class AVCompositionTrack;

@class AVAssetInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVAsset : NSObject <NSCopying, AVAsynchronousKeyValueLoading>
{
@private
	AVAssetInternal *_asset;
}

/*!
  @method		assetWithURL:
  @abstract		Returns an instance of AVAsset for inspection of a media resource.
  @param		URL
				An instance of NSURL that references a media resource.
  @result		An instance of AVAsset.
  @discussion	Returns a newly allocated instance of a subclass of AVAsset initialized with the specified URL.
*/
+ (instancetype)assetWithURL:(NSURL *)URL;

/*	Indicates the duration of the asset. If @"providesPreciseDurationAndTiming" is NO, a best-available estimate of the duration is returned. The degree of precision preferred for timing-related properties can be set at initialization time for assets initialized with URLs. See AVURLAssetPreferPreciseDurationAndTimingKey for AVURLAsset below.
*/
@property (nonatomic, readonly) CMTime duration;

/*	indicates the natural rate at which the asset is to be played; often but not always 1.0
*/
@property (nonatomic, readonly) float preferredRate;

/*	indicates the preferred volume at which the audible media of an asset is to be played; often but not always 1.0
*/
@property (nonatomic, readonly) float preferredVolume;

/*	indicates the preferred transform to apply to the visual content of the asset for presentation or processing; the value is often but not always the identity transform
*/
@property (nonatomic, readonly) CGAffineTransform preferredTransform;

/*	The following property is deprecated. Instead, use the naturalSize and preferredTransform, as appropriate, of the receiver's video tracks. See -tracksWithMediaType: below.
*/
@property (nonatomic, readonly) CGSize naturalSize NS_DEPRECATED(10_7, 10_8, 4_0, 5_0);

@end


@interface AVAsset (AVAssetAsynchronousLoading)

/*	Indicates that the asset provides precise timing. See @"duration" above and AVURLAssetPreferPreciseDurationAndTimingKey below.
*/
@property (nonatomic, readonly) BOOL providesPreciseDurationAndTiming;

/*!
  @method		cancelLoading
  @abstract		Cancels the loading of all values for all observers.
  @discussion	Deallocation or finalization of an instance of AVAsset will implicitly cancel loading if any loading requests are still outstanding.
*/
- (void)cancelLoading;

@end


@interface AVAsset (AVAssetReferenceRestrictions)

/*!
  @enum			AVAssetReferenceRestrictions
  @abstract		These constants can be passed in to AVURLAssetReferenceRestrictionsKey to control the resolution of references to external media data.
 
  @constant		AVAssetReferenceRestrictionForbidNone
	Indicates that all types of references should be followed.
  @constant		AVAssetReferenceRestrictionForbidRemoteReferenceToLocal
	Indicates that references from a remote asset (e.g. referenced via http URL) to local media data (e.g. stored in a local file) should not be followed.
  @constant		AVAssetReferenceRestrictionForbidLocalReferenceToRemote
	Indicates that references from a local asset to remote media data should not be followed.
  @constant		AVAssetReferenceRestrictionForbidCrossSiteReference
	Indicates that references from a remote asset to remote media data stored at a different site should not be followed.
  @constant		AVAssetReferenceRestrictionForbidLocalReferenceToLocal
	Indicates that references from a local asset to local media data stored outside the asset's container file should not be followed.
  @constant		AVAssetReferenceRestrictionForbidAll
	Indicates that only references to media data stored within the asset's container file should be allowed.
*/
typedef NS_OPTIONS(NSUInteger, AVAssetReferenceRestrictions) {
	AVAssetReferenceRestrictionForbidNone = 0UL,
	AVAssetReferenceRestrictionForbidRemoteReferenceToLocal = (1UL << 0),
	AVAssetReferenceRestrictionForbidLocalReferenceToRemote = (1UL << 1),
	AVAssetReferenceRestrictionForbidCrossSiteReference = (1UL << 2),
	AVAssetReferenceRestrictionForbidLocalReferenceToLocal = (1UL << 3),
	AVAssetReferenceRestrictionForbidAll = 0xFFFFUL,
};

/*!
  @property		referenceRestrictions
  @abstract		Indicates the reference restrictions being used by the receiver.
  @discussion
	For AVURLAsset, this property reflects the value passed in for AVURLAssetReferenceRestrictionsKey, if any. See AVURLAssetReferenceRestrictionsKey below for a full discussion of reference restrictions. The default value for this property is AVAssetReferenceRestrictionForbidNone.
*/
@property (nonatomic, readonly) AVAssetReferenceRestrictions referenceRestrictions NS_AVAILABLE(10_7, 5_0);

@end


@class AVAssetTrackGroup;

@interface AVAsset (AVAssetTrackInspection)

/*!
  @property		tracks
  @abstract		Provides the array of AVAssetTracks contained by the asset
*/
@property (nonatomic, readonly) NSArray<AVAssetTrack *> *tracks;

/*!
  @method		trackWithTrackID:
  @abstract		Provides an instance of AVAssetTrack that represents the track of the specified trackID.
  @param		trackID
				The trackID of the requested AVAssetTrack.
  @result		An instance of AVAssetTrack; may be nil if no track of the specified trackID is available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (nullable AVAssetTrack *)trackWithTrackID:(CMPersistentTrackID)trackID;

/*!
  @method		tracksWithMediaType:
  @abstract		Provides an array of AVAssetTracks of the asset that present media of the specified media type.
  @param		mediaType
				The media type according to which AVAsset filters its AVAssetTracks. (Media types are defined in AVMediaFormat.h.)
  @result		An NSArray of AVAssetTracks; may be empty if no tracks of the specified media type are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVAssetTrack *> *)tracksWithMediaType:(NSString *)mediaType;

/*!
  @method		tracksWithMediaCharacteristic:
  @abstract		Provides an array of AVAssetTracks of the asset that present media with the specified characteristic.
  @param		mediaCharacteristic
				The media characteristic according to which AVAsset filters its AVAssetTracks. (Media characteristics are defined in AVMediaFormat.h.)
  @result		An NSArray of AVAssetTracks; may be empty if no tracks with the specified characteristic are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVAssetTrack *> *)tracksWithMediaCharacteristic:(NSString *)mediaCharacteristic;

/*!
 @property trackGroups
 @abstract
	All track groups in the receiver.
 
 @discussion
	The value of this property is an NSArray of AVAssetTrackGroups, each representing a different grouping of tracks in the receiver.
 */
@property (nonatomic, readonly) NSArray<AVAssetTrackGroup *> *trackGroups NS_AVAILABLE(10_9, 7_0);

@end


@interface AVAsset (AVAssetMetadataReading)

// high-level access to selected metadata of common interest

/* Indicates the creation date of the asset as an AVMetadataItem. May be nil. If a creation date has been stored by the asset in a form that can be converted to an NSDate, the dateValue property of the AVMetadataItem will provide an instance of NSDate. Otherwise the creation date is available only as a string value, via -[AVMetadataItem stringValue].
*/
@property (nonatomic, readonly, nullable) AVMetadataItem *creationDate NS_AVAILABLE(10_8, 5_0);

/* Provides access to the lyrics of the asset suitable for the current locale.
*/
@property (nonatomic, readonly, nullable) NSString *lyrics;

/* Provides access to an array of AVMetadataItems for each common metadata key for which a value is available; items can be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:] and according to identifier via +[AVMetadataItem metadataItemsFromArray:filteredByIdentifier:].
*/
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *commonMetadata;

/* Provides access to an array of AVMetadataItems for all metadata identifiers for which a value is available; items can be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:] and according to identifier via +[AVMetadataItem metadataItemsFromArray:filteredByIdentifier:].
*/
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *metadata NS_AVAILABLE(10_10, 8_0);

/* Provides an NSArray of NSStrings, each representing a metadata format that's available to the asset (e.g. ID3, iTunes metadata, etc.). Metadata formats are defined in AVMetadataFormat.h.
*/
@property (nonatomic, readonly) NSArray<NSString *> *availableMetadataFormats;

/*!
  @method		metadataForFormat:
  @abstract		Provides an NSArray of AVMetadataItems, one for each metadata item in the container of the specified format; can subsequently be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:], according to locale via +[AVMetadataItem metadataItemsFromArray:withLocale:], or according to key via +[AVMetadataItem metadataItemsFromArray:withKey:keySpace:].
  @param		format
				The metadata format for which items are requested.
  @result		An NSArray containing AVMetadataItems; may be empty if there is no metadata of the specified format.
  @discussion	Becomes callable without blocking when the key @"availableMetadataFormats" has been loaded
*/
- (NSArray<AVMetadataItem *> *)metadataForFormat:(NSString *)format;

@end


@class AVTimedMetadataGroup;

@interface AVAsset (AVAssetChapterInspection)

/* array of NSLocale
*/
@property (readonly) NSArray<NSLocale *> *availableChapterLocales NS_AVAILABLE(10_7, 4_3);

/*!
  @method		chapterMetadataGroupsWithTitleLocale:containingMetadataItemsWithCommonKeys:
  @abstract		Provides an array of chapters.
  @param		locale
				Locale of the metadata items carrying chapter titles to be returned (supports the IETF BCP 47 specification).
  @param		commonKeys
				Array of common keys of AVMetadataItem to be included; can be nil. 
				AVMetadataCommonKeyArtwork is the only supported key for now.
  @result		An NSArray of AVTimedMetadataGroup.
  @discussion	
	This method returns an array of AVTimedMetadataGroup objects. Each object in the array always contains an AVMetadataItem representing the chapter title; the timeRange property of the AVTimedMetadataGroup object is equal to the time range of the chapter title item.

	An AVMetadataItem with the specified common key will be added to an existing AVTimedMetadataGroup object if the time range (timestamp and duration) of the metadata item and the metadata group overlaps. The locale of items not carrying chapter titles need not match the specified locale parameter.
 
	Further filtering of the metadata items in AVTimedMetadataGroups according to language can be accomplished using +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:]; filtering of the metadata items according to locale can be accomplished using +[AVMetadataItem metadataItemsFromArray:withLocale:].
*/
- (NSArray<AVTimedMetadataGroup *> *)chapterMetadataGroupsWithTitleLocale:(NSLocale *)locale containingItemsWithCommonKeys:(nullable NSArray<NSString *> *)commonKeys NS_AVAILABLE(10_7, 4_3);

/*!
 @method		chapterMetadataGroupsBestMatchingPreferredLanguages:
 @abstract		Tests, in order of preference, for a match between language identifiers in the specified array of preferred languages and the available chapter locales, and returns the array of chapters corresponding to the first match that's found.
 @param			preferredLanguages
 An array of language identifiers in order of preference, each of which is an IETF BCP 47 (RFC 4646) language identifier. Use +[NSLocale preferredLanguages] to obtain the user's list of preferred languages.
 @result		An NSArray of AVTimedMetadataGroup.
 @discussion	
 Safe to call without blocking when the AVAsset key availableChapterLocales has status AVKeyValueStatusLoaded.
 
 Returns an array of AVTimedMetadataGroup objects. Each object in the array always contains an AVMetadataItem representing the chapter title; the timeRange property of the AVTimedMetadataGroup object is equal to the time range of the chapter title item.
 
 All of the available chapter metadata is included in the metadata groups, including items with the common key AVMetadataCommonKeyArtwork, if such items are present. Items not carrying chapter titles will be added to an existing AVTimedMetadataGroup object if the time range (timestamp and duration) of the metadata item and that of the metadata group overlaps. The locale of such items need not match the locale of the chapter titles.
 
 Further filtering of the metadata items in AVTimedMetadataGroups according to language can be accomplished using +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:]; filtering of the metadata items according to locale can be accomplished using +[AVMetadataItem metadataItemsFromArray:withLocale:].
.
*/
- (NSArray<AVTimedMetadataGroup *> *)chapterMetadataGroupsBestMatchingPreferredLanguages:(NSArray<NSString *> *)preferredLanguages NS_AVAILABLE(10_8, 6_0);


@end


@class AVMediaSelectionGroup;

@interface AVAsset (AVAssetMediaSelection)

/* Provides an NSArray of NSStrings, each NSString indicating a media characteristic for which a media selection option is available.
*/
@property (nonatomic, readonly) NSArray<NSString *> *availableMediaCharacteristicsWithMediaSelectionOptions NS_AVAILABLE(10_8, 5_0);

/*!
  @method		mediaSelectionGroupForMediaCharacteristic:
  @abstract		Provides an instance of AVMediaSelectionGroup that contains one or more options with the specified media characteristic.
  @param		mediaCharacteristic
	A media characteristic for which you wish to obtain the available media selection options. AVMediaCharacteristicAudible, AVMediaCharacteristicLegible, and AVMediaCharacteristicVisual are currently supported.

	Pass AVMediaCharacteristicAudible to obtain the group of available options for audio media in various languages and for various purposes, such as descriptive audio.
	Pass AVMediaCharacteristicLegible to obtain the group of available options for subtitles in various languages and for various purposes.
	Pass AVMediaCharacteristicVisual to obtain the group of available options for video media.
  @result		An instance of AVMediaSelectionGroup. May be nil.
  @discussion
	Becomes callable without blocking when the key @"availableMediaCharacteristicsWithMediaSelectionOptions" has been loaded.

	If the asset has no AVMediaSelectionGroup containing options with the specified media characteristic, the return value will be nil.
	
	Filtering of the options in the returned AVMediaSelectionGroup according to playability, locale, and additional media characteristics can be accomplished using the category AVMediaSelectionOptionFiltering defined on AVMediaSelectionGroup.
*/
- (nullable AVMediaSelectionGroup *)mediaSelectionGroupForMediaCharacteristic:(NSString *)mediaCharacteristic NS_AVAILABLE(10_8, 5_0);

/*!
  @property		preferredMediaSelection
  @abstract		Provides an instance of AVMediaSelection with default selections for each of the receiver's media selection groups.
*/
@property (nonatomic, readonly) AVMediaSelection *preferredMediaSelection NS_AVAILABLE(10_11, 9_0);

@end


@interface AVAsset (AVAssetProtectedContent)

/* Indicates whether or not the asset has protected content.
*/
@property (nonatomic, readonly) BOOL hasProtectedContent NS_AVAILABLE(10_7, 4_2);

@end


@interface AVAsset (AVAssetFragments)

/*!
  @property		canContainFragments
  @abstract		Indicates whether the asset is capable of being extended by fragments.
  @discussion	For QuickTime movie files and MPEG-4 files, the value of canContainFragments is YES if an 'mvex' box is present in the 'moov' box. For those types, the 'mvex' box signals the possible presence of later 'moof' boxes.
*/

@property (nonatomic, readonly) BOOL canContainFragments NS_AVAILABLE(10_11, 9_0);

/*!
  @property		containsFragments
  @abstract		Indicates whether the asset is extended by at least one movie fragment.
  @discussion	For QuickTime movie files and MPEG-4 files, the value of this property is YES if canContainFragments is YES and at least one 'moof' box is present after the 'moov' box.
*/
@property (nonatomic, readonly) BOOL containsFragments NS_AVAILABLE(10_11, 9_0);

@end


@interface AVAsset (AVAssetUsability)

/* indicates whether an AVPlayerItem can be initialized with the receiver or with its URL
*/
@property (nonatomic, readonly, getter=isPlayable) BOOL playable NS_AVAILABLE(10_7, 4_3);

/* indicates whether an AVAssetExportSession can be used with the receiver for export
*/
@property (nonatomic, readonly, getter=isExportable) BOOL exportable NS_AVAILABLE(10_7, 4_3);

/* indicates whether an AVAssetReader can be used with the receiver for extracting media data
*/
@property (nonatomic, readonly, getter=isReadable) BOOL readable NS_AVAILABLE(10_7, 4_3);

/* indicates whether the receiver can be used to build an AVMutableComposition
*/
@property (nonatomic, readonly, getter=isComposable) BOOL composable NS_AVAILABLE(10_7, 4_3);

#if TARGET_OS_IPHONE

/* indicates whether the receiver can be written to the saved photos album
*/
@property (nonatomic, readonly, getter=isCompatibleWithSavedPhotosAlbum) BOOL compatibleWithSavedPhotosAlbum NS_AVAILABLE_IOS(5_0);

#endif	// TARGET_OS_IPHONE

/*!
  @property		compatibleWithAirPlayVideo
  @abstract		Indicates whether the asset is compatible with AirPlay Video.
  @discussion	YES if an AVPlayerItem initialized with the receiver can be played by an external device via AirPlay Video.
 */
@property (nonatomic, readonly, getter=isCompatibleWithAirPlayVideo) BOOL compatibleWithAirPlayVideo NS_AVAILABLE(10_11, 9_0);

@end


#pragma mark --- AVURLAsset ---
// Keys for options dictionary for use with -[AVURLAsset initWithURL:options:]

/*!
  @constant		AVURLAssetPreferPreciseDurationAndTimingKey
  @abstract
	Indicates whether the asset should be prepared to indicate a precise duration and provide precise random access by time.
	The value for this key is a boolean NSNumber.
  @discussion
	If nil is passed as the value of the options parameter to -[AVURLAsset initWithURL:options:], or if a dictionary that lacks a value for the key AVURLAssetPreferPreciseDurationAndTimingKey is passed instead, a default value of NO is assumed. If the asset is intended to be played only, because AVPlayer will support approximate random access by time when full precision isn't available, the default value of NO will suffice.
	Pass YES if longer loading times are acceptable in cases in which precise timing is required. If the asset is intended to be inserted into an AVMutableComposition, precise random access is typically desirable and the value of YES is recommended.
	Note that such precision may require additional parsing of the resource in advance of operations that make use of any portion of it, depending on the specifics of its container format. Many container formats provide sufficient summary information for precise timing and do not require additional parsing to prepare for it; QuickTime movie files and MPEG-4 files are examples of such formats. Other formats do not provide sufficient summary information, and precise random access for them is possible only after a preliminary examination of a file's contents.
	If you pass YES for an asset that you intend to play via an instance of AVPlayerItem and you are prepared for playback to commence before the value of -[AVPlayerItem duration] becomes available, you can omit the key @"duration" from the array of AVAsset keys you pass to -[AVPlayerItem initWithAsset:automaticallyLoadedAssetKeys:] in order to prevent AVPlayerItem from automatically loading the value of duration while the item becomes ready to play.
	If precise duration and timing is not possible for the timed media resource referenced by the asset's URL, AVAsset.providesPreciseDurationAndTiming will be NO even if precise timing is requested via the use of this key.
					
*/
AVF_EXPORT NSString *const AVURLAssetPreferPreciseDurationAndTimingKey NS_AVAILABLE(10_7, 4_0);

/*!
  @constant		AVURLAssetReferenceRestrictionsKey
  @abstract
	Indicates the restrictions used by the asset when resolving references to external media data. The value of this key is an NSNumber wrapping an AVAssetReferenceRestrictions enum value or the logical combination of multiple such values.
  @discussion
	Some assets can contain references to media data stored outside the asset's container file, for example in another file. This key can be used to specify a policy to use when these references are encountered. If an asset contains one or more references of a type that is forbidden by the reference restrictions, loading of asset properties will fail. In addition, such an asset cannot be used with other AVFoundation modules, such as AVPlayerItem or AVAssetExportSession.
*/
AVF_EXPORT NSString *const AVURLAssetReferenceRestrictionsKey NS_AVAILABLE(10_7, 5_0);

/*!
 @constant		AVURLAssetHTTPCookiesKey
 @abstract
	HTTP cookies that the AVURLAsset may send with HTTP requests
	Standard cross-site policy still applies: cookies will only be sent to domains to which they apply.
 @discussion
	By default, an AVURLAsset will only have access to cookies in the client's default cookie storage 
	that apply to the AVURLAsset's URL.  You can supplement the cookies available to the asset
	via use of this initialization option 
	
	HTTP cookies do not apply to non-HTTP(S) URLS.
	In HLS, many HTTP requests (e.g., media, crypt key, variant index) might be issued to different paths or hosts.
	In both of these cases, HTTP requests will be missing any cookies that do not apply to the AVURLAsset's URL.  
	This init option allows the AVURLAsset to use additional HTTP cookies for those HTTP(S) requests.
 */
AVF_EXPORT NSString *const AVURLAssetHTTPCookiesKey NS_AVAILABLE_IOS(8_0);

/*!
  @class		AVURLAsset

  @abstract		AVURLAsset provides access to the AVAsset model for timed audiovisual media referenced by URL.

  @discussion
	Note that although instances of AVURLAsset are immutable, values for its keys may not be immediately available without blocking. See the discussion of the class AVAsset above regarding the availability of values for keys and the use of AVAsynchronousKeyValueLoading.

	Once an AVURLAsset's value for a key is available, it will not change.  AVPlayerItem provides access to information that can change dynamically during playback; see AVPlayerItem.duration and AVPlayerItem.tracks.

	AVURLAssets can be initialized with NSURLs that refer to audiovisual media resources, such as streams (including HTTP live streams), QuickTime movie files, MP3 files, and files of other types.
*/
@class AVURLAssetInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVURLAsset : AVAsset
{
@private
	AVURLAssetInternal *_URLAsset;
}
AV_INIT_UNAVAILABLE

/*!
  @method		audiovisualTypes
  @abstract		Provides the file types the AVURLAsset class understands.
  @result		An NSArray of UTIs identifying the file types the AVURLAsset class understands.
*/
+ (NSArray<NSString *> *)audiovisualTypes NS_AVAILABLE(10_7, 5_0);

/*!
  @method		audiovisualMIMETypes
  @abstract		Provides the MIME types the AVURLAsset class understands.
  @result		An NSArray of NSStrings containing MIME types the AVURLAsset class understands.
*/
+ (NSArray<NSString *> *)audiovisualMIMETypes NS_AVAILABLE(10_7, 5_0);

/*!
  @method		isPlayableExtendedMIMEType:
  @abstract		Returns YES if asset is playable with the codec(s) and container type specified in extendedMIMEType. Returns NO otherwise.
  @param		extendedMIMEType
  @result		YES or NO.
*/
+ (BOOL)isPlayableExtendedMIMEType: (NSString *)extendedMIMEType NS_AVAILABLE(10_7, 5_0);

/*!
  @method		URLAssetWithURL:options:
  @abstract		Returns an instance of AVURLAsset for inspection of a media resource.
  @param		URL
				An instance of NSURL that references a media resource.
  @param		options
				An instance of NSDictionary that contains keys for specifying options for the initialization of the AVURLAsset. See AVURLAssetPreferPreciseDurationAndTimingKey and AVURLAssetReferenceRestrictionsKey above.
  @result		An instance of AVURLAsset.
*/
+ (instancetype)URLAssetWithURL:(NSURL *)URL options:(nullable NSDictionary<NSString *, id> *)options;

/*!
  @method		initWithURL:options:
  @abstract		Initializes an instance of AVURLAsset for inspection of a media resource.
  @param		URL
				An instance of NSURL that references a media resource.
  @param		options
				An instance of NSDictionary that contains keys for specifying options for the initialization of the AVURLAsset. See AVURLAssetPreferPreciseDurationAndTimingKey and AVURLAssetReferenceRestrictionsKey above.
  @result		An instance of AVURLAsset.
*/
- (instancetype)initWithURL:(NSURL *)URL options:(nullable NSDictionary<NSString *, id> *)options NS_DESIGNATED_INITIALIZER;

/* indicates the URL with which the instance of AVURLAsset was initialized
*/
@property (nonatomic, readonly, copy) NSURL *URL;

@end


@class AVAssetResourceLoader;

@interface AVURLAsset (AVURLAssetURLHandling)

/*!
 @property resourceLoader
 @abstract
    Provides access to an instance of AVAssetResourceLoader, which offers limited control over the handling of URLs that may be loaded in the course of performing operations on the asset, such as playback.
    The loading of file URLs cannot be mediated via use of AVAssetResourceLoader.
    Note that copies of an AVAsset will vend the same instance of AVAssetResourceLoader.
*/
@property (nonatomic, readonly) AVAssetResourceLoader *resourceLoader NS_AVAILABLE(10_9, 6_0);

@end


@interface AVURLAsset (AVAssetCompositionUtility )

/*!
  @method		compatibleTrackForCompositionTrack:
  @abstract		Provides a reference to an AVAssetTrack of the target from which any timeRange
				can be inserted into a mutable composition track (via -[AVMutableCompositionTrack insertTimeRange:ofTrack:atTime:error:]).
  @param		compositionTrack
				The composition track for which a compatible AVAssetTrack is requested.
  @result		an instance of AVAssetTrack
  @discussion
	Finds a track of the target with content that can be accommodated by the specified composition track.
	The logical complement of -[AVMutableComposition mutableTrackCompatibleWithTrack:].
*/
- (nullable AVAssetTrack *)compatibleTrackForCompositionTrack:(AVCompositionTrack *)compositionTrack;

@end

#pragma mark --- AVAsset change notifications ---

/*
	AVAsset change notifications are posted by instances of mutable subclasses, AVMutableComposition and AVMutableMovie.
	Some of the notifications are also posted by instances of dynamic subclasses, AVFragmentedAsset and AVFragmentedMovie, but these are capable of changing only in well-defined ways and only under specific conditions that you control. 
*/

/*!
 @constant       AVAssetDurationDidChangeNotification
 @abstract       Posted when the duration of an AVFragmentedAsset changes while it's being minded by an AVFragmentedAssetMinder, but only for changes that occur after the status of the value of @"duration" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVAssetDurationDidChangeNotification NS_AVAILABLE(10_11, 9_0);

/*!
 @constant       AVAssetContainsFragmentsDidChangeNotification
 @abstract       Posted after the value of @"containsFragments" has already been loaded and the AVFragmentedAsset is added to an AVFragmentedAssetMinder, either when 1) fragments are detected in the asset on disk after it had previously contained none or when 2) no fragments are detected in the asset on disk after it had previously contained one or more.
*/
AVF_EXPORT NSString *const AVAssetContainsFragmentsDidChangeNotification NS_AVAILABLE_MAC(10_11);

/*!
 @constant       AVAssetWasDefragmentedNotification
 @abstract       Posted when the asset on disk is defragmented while an AVFragmentedAsset is being minded by an AVFragmentedAssetMinder, but only if the defragmentation occurs after the status of the value of @"canContainFragments" has reached AVKeyValueStatusLoaded.
 @discussion     After this notification is posted, the value of the asset properties canContainFragments and containsFragments will both be NO.
*/
AVF_EXPORT NSString *const AVAssetWasDefragmentedNotification NS_AVAILABLE_MAC(10_11);

/*!
 @constant       AVAssetChapterMetadataGroupsDidChangeNotification
 @abstract       Posted when the collection of arrays of timed metadata groups representing chapters of an AVAsset change and when any of the contents of the timed metadata groups change, but only for changes that occur after the status of the value of @"availableChapterLocales" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVAssetChapterMetadataGroupsDidChangeNotification NS_AVAILABLE(10_11, 9_0);
/*!

 @constant       AVAssetMediaSelectionGroupsDidChangeNotification
 @abstract       Posted when the collection of media selection groups provided by an AVAsset changes and when any of the contents of its media selection groups change, but only for changes that occur after the status of the value of @"availableMediaCharacteristicsWithMediaSelectionOptions" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVAssetMediaSelectionGroupsDidChangeNotification NS_AVAILABLE(10_11, 9_0);

#pragma mark --- AVFragmentedAsset ---
/*!
	@class			AVFragmentedAsset
 
	@abstract		A subclass of AVURLAsset that represents media resources that can be extended in total duration without modifying previously existing data structures.
	Such media resources include QuickTime movie files and MPEG-4 files that indicate, via an 'mvex' box in their 'moov' box, that they accommodate additional fragments. Media resources of other types may also be supported. To check whether a given instance of AVFragmentedAsset can be used to monitor the addition of fragments, check the value of the AVURLAsset property canContainFragments.
	An AVFragmentedAsset is capable of changing the values of certain of its properties and those of its tracks, while an operation that appends fragments to the underlying media resource in in progress, if the AVFragmentedAsset is associated with an instance of AVFragmentedAssetMinder.
	@discussion		While associated with an AVFragmentedAssetMinder, AVFragmentedAssetTrack posts AVAssetDurationDidChangeNotification and whenever new fragments are detected, as appropriate. It may also post AVAssetContainsFragmentsDidChangeNotification and AVAssetWasDefragmentedNotification, as discussed in documentation of those notifications.
*/

@protocol AVFragmentMinding

/*!
  @property		associatedWithFragmentMinder
  @abstract		Indicates whether an AVAsset that supports fragment minding is currently associated with an AVAssetFragmentMinder.
  @discussion	AVAssets that support fragment minding post change notifications only while associated with an AVAssetFragmentMinder.
*/
@property (nonatomic, readonly, getter=isAssociatedWithFragmentMinder) BOOL associatedWithFragmentMinder NS_AVAILABLE_MAC(10_11);

@end

@class AVFragmentedAssetInternal;

NS_CLASS_AVAILABLE_MAC(10_11)
@interface AVFragmentedAsset : AVURLAsset <AVFragmentMinding>
{
@private
	AVFragmentedAssetInternal	*_fragmentedAsset;
}

/*!
  @method		fragmentedAssetWithURL:options:
  @abstract		Returns an instance of AVFragmentedAsset for inspection of a fragmented media resource.
  @param		URL
				An instance of NSURL that references a media resource.
  @param		options
				An instance of NSDictionary that contains keys for specifying options for the initialization of the AVFragmentedAsset. See AVURLAssetPreferPreciseDurationAndTimingKey and AVURLAssetReferenceRestrictionsKey above.
  @result		An instance of AVFragmentedAsset.
*/
+ (instancetype)fragmentedAssetWithURL:(NSURL *)URL options:(nullable NSDictionary<NSString *, id> *)options;

/*!
	@property       tracks
	@abstract       The tracks in an asset.
	@discussion     The value of this property is an array of tracks the asset contains; the tracks are of type AVFragmentedAssetTrack.
*/
@property (nonatomic, readonly) NSArray<AVFragmentedAssetTrack *> *tracks;

@end

@interface AVFragmentedAsset (AVFragmentedAssetTrackInspection)

/*!
  @method		trackWithTrackID:
  @abstract		Provides an instance of AVFragmentedAssetTrack that represents the track of the specified trackID.
  @param		trackID
				The trackID of the requested AVFragmentedAssetTrack.
  @result		An instance of AVFragmentedAssetTrack; may be nil if no track of the specified trackID is available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (nullable AVFragmentedAssetTrack *)trackWithTrackID:(CMPersistentTrackID)trackID;

/*!
  @method		tracksWithMediaType:
  @abstract		Provides an array of AVFragmentedAssetTracks of the asset that present media of the specified media type.
  @param		mediaType
				The media type according to which the receiver filters its AVFragmentedAssetTracks. (Media types are defined in AVMediaFormat.h)
  @result		An NSArray of AVFragmentedAssetTracks; may be empty if no tracks of the specified media type are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVFragmentedAssetTrack *> *)tracksWithMediaType:(NSString *)mediaType;

/*!
  @method		tracksWithMediaCharacteristic:
  @abstract		Provides an array of AVFragmentedAssetTracks of the asset that present media with the specified characteristic.
  @param		mediaCharacteristic
				The media characteristic according to which the receiver filters its AVFragmentedAssetTracks. (Media characteristics are defined in AVMediaFormat.h)
  @result		An NSArray of AVFragmentedAssetTracks; may be empty if no tracks with the specified characteristic are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVFragmentedAssetTrack *> *)tracksWithMediaCharacteristic:(NSString *)mediaCharacteristic;

@end

#pragma mark --- AVFragmentedAssetMinder ---
/*!
	@class			AVFragmentedAssetMinder
	@abstract		A class that periodically checks whether additional fragments have been appended to fragmented assets.
*/

@class AVFragmentedAssetMinderInternal;

NS_CLASS_AVAILABLE_MAC(10_11)
@interface AVFragmentedAssetMinder : NSObject
{
@private
	AVFragmentedAssetMinderInternal	*_fragmentedAssetMinder;
}

/*!
	@method			fragmentedAssetMinderWithAsset:mindingInterval:
	@abstract       Creates an AVFragmentedAssetMinder, adds the specified asset to it, and sets the mindingInterval to the specified value.
	@param			asset
					An instance of AVFragmentedAsset to add to the AVFragmentedAssetMinder
	@param			mindingInterval
					The initial minding interval of the AVFragmentedAssetMinder.
	@result			A new instance of AVFragmentedAssetMinder.
*/
+ (instancetype)fragmentedAssetMinderWithAsset:(AVAsset<AVFragmentMinding> *)asset mindingInterval:(NSTimeInterval)mindingInterval;

/*!
	@property       mindingInterval
	@abstract       An NSTimeInterval indicating how often a check for additional fragments should be performed. The default interval is 10.0.
*/
@property (nonatomic) NSTimeInterval mindingInterval;

/*!
	@property       assets
	@abstract       An NSArray of the AVFragmentedAsset objects being minded.
*/
@property (nonatomic, readonly) NSArray<AVAsset<AVFragmentMinding> *> *assets;

/*!
	@method			addFragmentedAsset:
	@abstract		Adds a fragmented asset to the array of assets being minded.
	@param			asset
					The fragmented asset to add to the minder.
*/
- (void)addFragmentedAsset:(AVAsset<AVFragmentMinding> *)asset;

/*!
	@method			removeFragmentedAsset:
	@abstract		Removes a fragmented asset from the array of assets being minded.
	@param			asset
					The fragmented asset to remove from the minder.
*/
- (void)removeFragmentedAsset:(AVAsset<AVFragmentMinding> *)asset;

@end

NS_ASSUME_NONNULL_END

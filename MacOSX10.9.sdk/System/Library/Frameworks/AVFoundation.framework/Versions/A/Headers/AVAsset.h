/*
	File:  AVAsset.h

	Framework:  AVFoundation
 
	Copyright 2010-2013 Apple Inc. All rights reserved.

*/

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

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>

#if TARGET_OS_IPHONE
#import <CoreGraphics/CGAffineTransform.h>
#else // ! TARGET_OS_IPHONE
#import <ApplicationServices/../Frameworks/CoreGraphics.framework/Headers/CGAffineTransform.h>
#endif // ! TARGET_OS_IPHONE

#import <CoreMedia/CMTime.h>

@class AVAssetTrack;
@class AVMetadataItem;
@class AVCompositionTrack;

@class AVAssetInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVAsset : NSObject <NSCopying, AVAsynchronousKeyValueLoading>
{
@private
	AVAssetInternal *_assetInternal;
}

/*!
  @method		assetWithURL:
  @abstract		Returns an instance of AVAsset for inspection of a media resource.
  @param		URL
				An instance of NSURL that references a media resource.
  @result		An instance of AVAsset.
  @discussion	Returns a newly allocated instance of a subclass of AVAsset initialized with the specified URL.
*/
+ (id)assetWithURL:(NSURL *)URL;

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
enum {
	AVAssetReferenceRestrictionForbidNone = 0UL,
	AVAssetReferenceRestrictionForbidRemoteReferenceToLocal = (1UL << 0),
	AVAssetReferenceRestrictionForbidLocalReferenceToRemote = (1UL << 1),
	AVAssetReferenceRestrictionForbidCrossSiteReference = (1UL << 2),
	AVAssetReferenceRestrictionForbidLocalReferenceToLocal = (1UL << 3),
	AVAssetReferenceRestrictionForbidAll = 0xFFFFUL,
};
typedef NSUInteger AVAssetReferenceRestrictions;

/*!
  @property		referenceRestrictions
  @abstract		Indicates the reference restrictions being used by the receiver.
  @discussion
	For AVURLAsset, this property reflects the value passed in for AVURLAssetReferenceRestrictionsKey, if any. See AVURLAssetReferenceRestrictionsKey below for a full discussion of reference restrictions. The default value for this property is AVAssetReferenceRestrictionForbidNone.
*/
@property (nonatomic, readonly) AVAssetReferenceRestrictions referenceRestrictions NS_AVAILABLE(10_7, 5_0);

@end


@interface AVAsset (AVAssetTrackInspection)

/* provides the array of AVAssetTracks contained by the asset
*/
@property (nonatomic, readonly) NSArray *tracks;

/*!
  @method		trackWithTrackID:
  @abstract		Provides an instance of AVAssetTrack that represents the track of the specified trackID.
  @param		trackID
				The trackID of the requested AVAssetTrack.
  @result		An instance of AVAssetTrack; may be nil if no track of the specified trackID is available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (AVAssetTrack *)trackWithTrackID:(CMPersistentTrackID)trackID;

/*!
  @method		tracksWithMediaType:
  @abstract		Provides an array of AVAssetTracks of the asset that present media of the specified media type.
  @param		mediaType
				The media type according to which AVAsset filters its AVAssetTracks. (Media types are defined in AVMediaFormat.h.)
  @result		An NSArray of AVAssetTracks; may be empty if no tracks of the specified media type are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray *)tracksWithMediaType:(NSString *)mediaType;

/*!
  @method		tracksWithMediaCharacteristic:
  @abstract		Provides an array of AVAssetTracks of the asset that present media with the specified characteristic.
  @param		mediaCharacteristic
				The media characteristic according to which AVAsset filters its AVAssetTracks. (Media characteristics are defined in AVMediaFormat.h.)
  @result		An NSArray of AVAssetTracks; may be empty if no tracks with the specified characteristic are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray *)tracksWithMediaCharacteristic:(NSString *)mediaCharacteristic;

/*!
 @property trackGroups
 @abstract
	All track groups in the receiver.
 
 @discussion
	The value of this property is an NSArray of AVAssetTrackGroups, each representing a different grouping of tracks in the receiver.
 */
@property (nonatomic, readonly) NSArray *trackGroups NS_AVAILABLE(10_9, 7_0);

@end


@interface AVAsset (AVAssetMetadataReading)

// high-level access to selected metadata of common interest

/* Indicates the creation date of the asset as an AVMetadataItem. May be nil. If a creation date has been stored by the asset in a form that can be converted to an NSDate, the dateValue property of the AVMetadataItem will provide an instance of NSDate. Otherwise the creation date is available only as a string value, via -[AVMetadataItem stringValue].
*/
@property (nonatomic, readonly) AVMetadataItem *creationDate NS_AVAILABLE(10_8, 5_0);

/* Provides access to the lyrics of the asset suitable for the current locale.
*/
@property (nonatomic, readonly) NSString *lyrics;

/* Provides access to an array of AVMetadataItems for each common metadata key for which a value is available; can be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:], according to locale via +[AVMetadataItem metadataItemsFromArray:withLocale:], or according to key via +[AVMetadataItem metadataItemsFromArray:withKey:keySpace:].
*/
@property (nonatomic, readonly) NSArray *commonMetadata;

/* Provides an NSArray of NSStrings, each representing a metadata format that's available to the asset (e.g. ID3, iTunes metadata, etc.). Metadata formats are defined in AVMetadataFormat.h.
*/
@property (nonatomic, readonly) NSArray *availableMetadataFormats;

/*!
  @method		metadataForFormat:
  @abstract		Provides an NSArray of AVMetadataItems, one for each metadata item in the container of the specified format; can subsequently be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:], according to locale via +[AVMetadataItem metadataItemsFromArray:withLocale:], or according to key via +[AVMetadataItem metadataItemsFromArray:withKey:keySpace:].
  @param		format
				The metadata format for which items are requested.
  @result		An NSArray containing AVMetadataItems; may be empty if there is no metadata of the specified format.
  @discussion	Becomes callable without blocking when the key @"availableMetadataFormats" has been loaded
*/
- (NSArray *)metadataForFormat:(NSString *)format;

@end


@interface AVAsset (AVAssetChapterInspection)

/* array of NSLocale
*/
@property (readonly) NSArray *availableChapterLocales NS_AVAILABLE(10_7, 4_3);

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
- (NSArray *)chapterMetadataGroupsWithTitleLocale:(NSLocale *)locale containingItemsWithCommonKeys:(NSArray *)commonKeys NS_AVAILABLE(10_7, 4_3);

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
- (NSArray *)chapterMetadataGroupsBestMatchingPreferredLanguages:(NSArray *)preferredLanguages NS_AVAILABLE(10_8, 6_0);


@end


@class AVMediaSelectionGroup;

@interface AVAsset (AVAssetMediaSelection)

/* Provides an NSArray of NSStrings, each NSString indicating a media characteristic for which a media selection option is available.
*/
@property (nonatomic, readonly) NSArray *availableMediaCharacteristicsWithMediaSelectionOptions NS_AVAILABLE(10_8, 5_0);

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
- (AVMediaSelectionGroup *)mediaSelectionGroupForMediaCharacteristic:(NSString *)mediaCharacteristic NS_AVAILABLE(10_8, 5_0);

@end


@interface AVAsset (AVAssetProtectedContent)

/* Indicates whether or not the asset has protected content.
*/
@property (nonatomic, readonly) BOOL hasProtectedContent NS_AVAILABLE(10_7, 4_2);

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

/* indicates whether the receiver can be used within a segment of an AVCompositionTrack
*/
@property (nonatomic, readonly, getter=isComposable) BOOL composable NS_AVAILABLE(10_7, 4_3);

#if TARGET_OS_IPHONE

/* indicates whether the receiver can be written to the saved photos album
*/
@property (nonatomic, readonly, getter=isCompatibleWithSavedPhotosAlbum) BOOL compatibleWithSavedPhotosAlbum NS_AVAILABLE_IOS(5_0);

#endif	// TARGET_OS_IPHONE


@end


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
	AVURLAssetInternal *_asset;
}

/*!
  @method		audiovisualTypes
  @abstract		Provides the file types the AVURLAsset class understands.
  @result		An NSArray of UTIs identifying the file types the AVURLAsset class understands.
*/
+ (NSArray *)audiovisualTypes NS_AVAILABLE(10_7, 5_0);

/*!
  @method		audiovisualMIMETypes
  @abstract		Provides the MIME types the AVURLAsset class understands.
  @result		An NSArray of NSStrings containing MIME types the AVURLAsset class understands.
*/
+ (NSArray *)audiovisualMIMETypes NS_AVAILABLE(10_7, 5_0);

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
+ (AVURLAsset *)URLAssetWithURL:(NSURL *)URL options:(NSDictionary *)options;

/*!
  @method		initWithURL:options:
  @abstract		Initializes an instance of AVURLAsset for inspection of a media resource.
  @param		URL
				An instance of NSURL that references a media resource.
  @param		options
				An instance of NSDictionary that contains keys for specifying options for the initialization of the AVURLAsset. See AVURLAssetPreferPreciseDurationAndTimingKey and AVURLAssetReferenceRestrictionsKey above.
  @result		An instance of AVURLAsset.
*/
- (id)initWithURL:(NSURL *)URL options:(NSDictionary *)options;

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
- (AVAssetTrack *)compatibleTrackForCompositionTrack:(AVCompositionTrack *)compositionTrack;

@end

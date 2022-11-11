#if !__has_include(<AVFCore/AVAsset.h>)
/*
	File:  AVAsset.h

	Framework:  AVFoundation
 
	Copyright 2010-2021 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>
#import <AVFoundation/AVContentKeySession.h>
#import <AVFoundation/AVMediaFormat.h>
#import <AVFoundation/AVMetadataFormat.h>
#import <AVFoundation/AVAssetVariant.h>

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

	In order to avoid blocking, clients can register their interest in particular keys and to become notified when their values become available. For further details, see AVAsynchronousKeyValueLoading.h. For clients who want to examine a subset of the tracks, metadata, and other parts of the asset, asynchronous methods like -loadTracksWithMediaType:completionHandler: can be used to load this information without blocking. When using these asynchronous methods, it is not necessary to load the associated property beforehand. Swift clients can also use the load(:) method to load properties in a type safe manner.

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
@class AVDisplayCriteria;
@class AVAssetInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0))
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
@property (nonatomic, readonly) CGSize naturalSize API_DEPRECATED("Use the naturalSize and preferredTransform, as appropriate, of the receiver's video tracks. See -tracksWithMediaType:", macos(10.7, 10.8), ios(4.0, 5.0), tvos(9.0, 9.0)) API_UNAVAILABLE(watchos);

/*!
 @property	preferredDisplayCriteria
 @abstract	Guides to a display mode that is optimal for playing this particular asset.
 */
@property (nonatomic, readonly) AVDisplayCriteria *preferredDisplayCriteria API_AVAILABLE(tvos(11.2)) API_UNAVAILABLE(ios) API_UNAVAILABLE(macos, watchos);

/*!
 @property		minimumTimeOffsetFromLive
 @abstract		Indicates how close to the latest content in a live stream playback can be sustained.
 @discussion	For non-live assets this value is kCMTimeInvalid.
 */
@property (nonatomic, readonly) CMTime minimumTimeOffsetFromLive API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

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
	
	AVAssetReferenceRestrictionDefaultPolicy = AVAssetReferenceRestrictionForbidLocalReferenceToRemote
};

/*!
  @property		referenceRestrictions
  @abstract		Indicates the reference restrictions being used by the receiver.
  @discussion
	For AVURLAsset, this property reflects the value passed in for AVURLAssetReferenceRestrictionsKey, if any. See AVURLAssetReferenceRestrictionsKey below for a full discussion of reference restrictions. The default value for this property is AVAssetReferenceRestrictionForbidLocalReferenceToRemote.
*/
@property (nonatomic, readonly) AVAssetReferenceRestrictions referenceRestrictions API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0)) API_UNAVAILABLE(watchos);

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
  @method		loadTrackWithTrackID:completionHandler:
  @abstract		Loads an instance of AVAssetTrack that represents the track of the specified trackID.
  @param		trackID
				The trackID of the requested AVAssetTrack.
  @param		completionHandler
				A block that is called when the loading is finished, with either the loaded track (which may be nil if no track of the specified trackID is available) or an error.
*/
- (void)loadTrackWithTrackID:(CMPersistentTrackID)trackID completionHandler:(void (^)(AVAssetTrack * _Nullable_result, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/*!
  @method		tracksWithMediaType:
  @abstract		Provides an array of AVAssetTracks of the asset that present media of the specified media type.
  @param		mediaType
				The media type according to which AVAsset filters its AVAssetTracks. (Media types are defined in AVMediaFormat.h.)
  @result		An NSArray of AVAssetTracks; may be empty if no tracks of the specified media type are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVAssetTrack *> *)tracksWithMediaType:(AVMediaType)mediaType;

/*!
  @method		loadTracksWithMediaType:completionHandler:
  @abstract		Loads an array of AVAssetTracks of the asset that present media of the specified media type.
  @param		mediaType
				The media type according to which AVAsset filters its AVAssetTracks. (Media types are defined in AVMediaFormat.h.)
  @param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks of the specified media type are available) or an error.
*/
- (void)loadTracksWithMediaType:(AVMediaType)mediaType completionHandler:(void (^)(NSArray<AVAssetTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/*!
  @method		tracksWithMediaCharacteristic:
  @abstract		Provides an array of AVAssetTracks of the asset that present media with the specified characteristic.
  @param		mediaCharacteristic
				The media characteristic according to which AVAsset filters its AVAssetTracks. (Media characteristics are defined in AVMediaFormat.h.)
  @result		An NSArray of AVAssetTracks; may be empty if no tracks with the specified characteristic are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVAssetTrack *> *)tracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic;

/*!
  @method		loadTracksWithMediaCharacteristic:completionHandler:
  @abstract		Loads an array of AVAssetTracks of the asset that present media with the specified characteristic.
  @param		mediaCharacteristic
				The media characteristic according to which AVAsset filters its AVAssetTracks. (Media characteristics are defined in AVMediaFormat.h.)
  @param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks with the specified characteristic are available) or an error.
*/
- (void)loadTracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic completionHandler:(void (^)(NSArray<AVAssetTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/*!
 @property trackGroups
 @abstract
	All track groups in the receiver.
 
 @discussion
	The value of this property is an NSArray of AVAssetTrackGroups, each representing a different grouping of tracks in the receiver.
 */
@property (nonatomic, readonly) NSArray<AVAssetTrackGroup *> *trackGroups API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0));

@end


@interface AVAsset (AVAssetMetadataReading)

// high-level access to selected metadata of common interest

/* Indicates the creation date of the asset as an AVMetadataItem. May be nil. If a creation date has been stored by the asset in a form that can be converted to an NSDate, the dateValue property of the AVMetadataItem will provide an instance of NSDate. Otherwise the creation date is available only as a string value, via -[AVMetadataItem stringValue].
*/
@property (nonatomic, readonly, nullable) AVMetadataItem *creationDate API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

/* Provides access to the lyrics of the asset suitable for the current locale.
*/
@property (nonatomic, readonly, nullable) NSString *lyrics;

/* Provides access to an array of AVMetadataItems for each common metadata key for which a value is available; items can be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:] and according to identifier via +[AVMetadataItem metadataItemsFromArray:filteredByIdentifier:].
*/
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *commonMetadata;

/* Provides access to an array of AVMetadataItems for all metadata identifiers for which a value is available; items can be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:] and according to identifier via +[AVMetadataItem metadataItemsFromArray:filteredByIdentifier:].
*/
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *metadata API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0));

/* Provides an NSArray of NSStrings, each representing a metadata format that's available to the asset (e.g. ID3, iTunes metadata, etc.). Metadata formats are defined in AVMetadataFormat.h.
*/
@property (nonatomic, readonly) NSArray<AVMetadataFormat> *availableMetadataFormats;

/*!
  @method		metadataForFormat:
  @abstract		Provides an NSArray of AVMetadataItems, one for each metadata item in the container of the specified format; can subsequently be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:], according to locale via +[AVMetadataItem metadataItemsFromArray:withLocale:], or according to key via +[AVMetadataItem metadataItemsFromArray:withKey:keySpace:].
  @param		format
				The metadata format for which items are requested.
  @result		An NSArray containing AVMetadataItems; may be empty if there is no metadata of the specified format.
  @discussion	Becomes callable without blocking when the key @"availableMetadataFormats" has been loaded
*/
- (NSArray<AVMetadataItem *> *)metadataForFormat:(AVMetadataFormat)format;

/*!
  @method		loadMetadataForFormat:completionHandler:
  @abstract		Loads an NSArray of AVMetadataItems, one for each metadata item in the container of the specified format; can subsequently be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:], according to locale via +[AVMetadataItem metadataItemsFromArray:withLocale:], or according to key via +[AVMetadataItem metadataItemsFromArray:withKey:keySpace:].
  @param		format
				The metadata format for which items are requested.
  @param		completionHandler
				A block that is invoked when loading is complete, vending the array of metadata items (which may be empty if there is no metadata of the specified format) or an error.
*/
- (void)loadMetadataForFormat:(AVMetadataFormat)format completionHandler:(void (^)(NSArray<AVMetadataItem *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

@end


@class AVTimedMetadataGroup;

@interface AVAsset (AVAssetChapterInspection)

/* array of NSLocale
*/
@property (readonly) NSArray<NSLocale *> *availableChapterLocales API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0));

/*!
  @method		chapterMetadataGroupsWithTitleLocale:containingItemsWithCommonKeys:
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
- (NSArray<AVTimedMetadataGroup *> *)chapterMetadataGroupsWithTitleLocale:(NSLocale *)locale containingItemsWithCommonKeys:(nullable NSArray<AVMetadataKey> *)commonKeys API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0));

/*!
  @method		loadChapterMetadataGroupsWithTitleLocale:containingItemsWithCommonKeys:completionHandler:
  @abstract		Loads an array of chapters.
  @param		locale
				Locale of the metadata items carrying chapter titles to be returned (supports the IETF BCP 47 specification).
  @param		commonKeys
				Array of common keys of AVMetadataItem to be included; if no common keys are required, send an empty list.
				AVMetadataCommonKeyArtwork is the only supported key for now.
  @param		completionHandler
				A block that is invoked when loading is complete, vending the array of timed metadata groups or an error.
  @discussion
	This method vends an array of AVTimedMetadataGroup objects. Each object in the array always contains an AVMetadataItem representing the chapter title; the timeRange property of the AVTimedMetadataGroup object is equal to the time range of the chapter title item.

	An AVMetadataItem with the specified common key will be added to an existing AVTimedMetadataGroup object if the time range (timestamp and duration) of the metadata item and the metadata group overlaps. The locale of items not carrying chapter titles need not match the specified locale parameter.
 
	Further filtering of the metadata items in AVTimedMetadataGroups according to language can be accomplished using +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:]; filtering of the metadata items according to locale can be accomplished using +[AVMetadataItem metadataItemsFromArray:withLocale:].
*/
- (void)loadChapterMetadataGroupsWithTitleLocale:(NSLocale *)locale containingItemsWithCommonKeys:(NSArray<AVMetadataKey> *)commonKeys completionHandler:(void (^)(NSArray<AVTimedMetadataGroup *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

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
- (NSArray<AVTimedMetadataGroup *> *)chapterMetadataGroupsBestMatchingPreferredLanguages:(NSArray<NSString *> *)preferredLanguages API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0));

/*!
 @method		loadChapterMetadataGroupsBestMatchingPreferredLanguages:completionHandler:
 @abstract		Tests, in order of preference, for a match between language identifiers in the specified array of preferred languages and the available chapter locales, and loads the array of chapters corresponding to the first match that's found.
 @param			preferredLanguages
 An array of language identifiers in order of preference, each of which is an IETF BCP 47 (RFC 4646) language identifier. Use +[NSLocale preferredLanguages] to obtain the user's list of preferred languages.
 @param			completionHandler
 A block that is invoked when loading is complete, vending the array of timed metadata groups or an error.
 @discussion
 Returns an array of AVTimedMetadataGroup objects. Each object in the array always contains an AVMetadataItem representing the chapter title; the timeRange property of the AVTimedMetadataGroup object is equal to the time range of the chapter title item.
 
 All of the available chapter metadata is included in the metadata groups, including items with the common key AVMetadataCommonKeyArtwork, if such items are present. Items not carrying chapter titles will be added to an existing AVTimedMetadataGroup object if the time range (timestamp and duration) of the metadata item and that of the metadata group overlaps. The locale of such items need not match the locale of the chapter titles.
 
 Further filtering of the metadata items in AVTimedMetadataGroups according to language can be accomplished using +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:]; filtering of the metadata items according to locale can be accomplished using +[AVMetadataItem metadataItemsFromArray:withLocale:].
*/
- (void)loadChapterMetadataGroupsBestMatchingPreferredLanguages:(NSArray<NSString *> *)preferredLanguages completionHandler:(void (^)(NSArray<AVTimedMetadataGroup *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

@end


@class AVMediaSelectionGroup;

@interface AVAsset (AVAssetMediaSelection)

/* Provides an NSArray of NSStrings, each NSString indicating a media characteristic for which a media selection option is available.
*/
@property (nonatomic, readonly) NSArray<AVMediaCharacteristic> *availableMediaCharacteristicsWithMediaSelectionOptions API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

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
- (nullable AVMediaSelectionGroup *)mediaSelectionGroupForMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0));

/*!
  @method		loadMediaSelectionGroupForMediaCharacteristic:completionHandler:
  @abstract		Loads an instance of AVMediaSelectionGroup that contains one or more options with the specified media characteristic.
  @param		mediaCharacteristic
	A media characteristic for which you wish to obtain the available media selection options. AVMediaCharacteristicAudible, AVMediaCharacteristicLegible, and AVMediaCharacteristicVisual are currently supported.

	Pass AVMediaCharacteristicAudible to obtain the group of available options for audio media in various languages and for various purposes, such as descriptive audio.
	Pass AVMediaCharacteristicLegible to obtain the group of available options for subtitles in various languages and for various purposes.
	Pass AVMediaCharacteristicVisual to obtain the group of available options for video media.
  @param		completionHandler
	A block that is invoked when loading is complete, vending an instance of AVMediaSelectionGroup (which may be nil) or an error.
  @discussion
	If the asset has no AVMediaSelectionGroup containing options with the specified media characteristic, the return value will be nil.
	
	Filtering of the options in the returned AVMediaSelectionGroup according to playability, locale, and additional media characteristics can be accomplished using the category AVMediaSelectionOptionFiltering defined on AVMediaSelectionGroup.
*/
- (void)loadMediaSelectionGroupForMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic completionHandler:(void (^)(AVMediaSelectionGroup * _Nullable_result, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));
/*!
  @property		preferredMediaSelection
  @abstract		Provides an instance of AVMediaSelection with default selections for each of the receiver's media selection groups.
*/
@property (nonatomic, readonly) AVMediaSelection *preferredMediaSelection API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

/*!
  @property		allMediaSelections
  @abstract		Provides an array of all permutations of AVMediaSelection for this asset.
*/
@property (nonatomic, readonly) NSArray <AVMediaSelection *> *allMediaSelections API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

@end


@interface AVAsset (AVAssetProtectedContent)

/*!
  @property		hasProtectedContent
  @abstract		Indicates whether or not the asset has protected content.
  @discussion	Assets containing protected content may not be playable without successful authorization, even if the value of the "playable" property is YES.  See the properties in the AVAssetUsability category for details on how such an asset may be used.  On OS X, clients can use the interfaces in AVPlayerItemProtectedContentAdditions.h to request authorization to play the asset.
*/
@property (nonatomic, readonly) BOOL hasProtectedContent API_AVAILABLE(macos(10.7), ios(4.2), tvos(9.0)) API_UNAVAILABLE(watchos);

@end


@interface AVAsset (AVAssetFragments)

/*!
  @property		canContainFragments
  @abstract		Indicates whether the asset is capable of being extended by fragments.
  @discussion	For QuickTime movie files and MPEG-4 files, the value of canContainFragments is YES if an 'mvex' box is present in the 'moov' box. For those types, the 'mvex' box signals the possible presence of later 'moof' boxes.
*/

@property (nonatomic, readonly) BOOL canContainFragments API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
  @property		containsFragments
  @abstract		Indicates whether the asset is extended by at least one fragment.
  @discussion	For QuickTime movie files and MPEG-4 files, the value of this property is YES if canContainFragments is YES and at least one 'moof' box is present after the 'moov' box.
*/
@property (nonatomic, readonly) BOOL containsFragments API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);

/*!
  @property		overallDurationHint
  @abstract		Indicates the total duration of fragments that either exist now or may be appended in the future in order to extend the duration of the asset.
  @discussion	For QuickTime movie files and MPEG-4 files, the value of this property is obtained from the 'mehd' box of the 'mvex' box, if present. If no total fragment duration hint is available, the value of this property is kCMTimeInvalid.
*/
@property (nonatomic, readonly) CMTime overallDurationHint API_AVAILABLE(macos(10.12.2), ios(10.2), tvos(10.2), watchos(3.2));

@end


@interface AVAsset (AVAssetUsability)

/*!
 @property		playable
 @abstract		Indicates whether an AVPlayer can play the contents of the asset in a manner that meets user expectations.
 @discussion	A client can attempt playback when playable is NO, this however may lead to a substandard playback experience.
*/
@property (nonatomic, readonly, getter=isPlayable) BOOL playable API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0));

/* indicates whether an AVAssetExportSession can be used with the receiver for export
*/
@property (nonatomic, readonly, getter=isExportable) BOOL exportable API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0)) API_UNAVAILABLE(watchos);

/* indicates whether an AVAssetReader can be used with the receiver for extracting media data
*/
@property (nonatomic, readonly, getter=isReadable) BOOL readable API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0)) API_UNAVAILABLE(watchos);

/* indicates whether the receiver can be used to build an AVMutableComposition
*/
@property (nonatomic, readonly, getter=isComposable) BOOL composable API_AVAILABLE(macos(10.7), ios(4.3), tvos(9.0), watchos(1.0));

/* indicates whether the receiver can be written to the saved photos album
*/
@property (nonatomic, readonly, getter=isCompatibleWithSavedPhotosAlbum) BOOL compatibleWithSavedPhotosAlbum API_AVAILABLE(ios(5.0), tvos(9.0)) API_UNAVAILABLE(macos, watchos);

/*!
  @property		compatibleWithAirPlayVideo
  @abstract		Indicates whether the asset is compatible with AirPlay Video.
  @discussion	YES if an AVPlayerItem initialized with the receiver can be played by an external device via AirPlay Video.
 */
@property (nonatomic, readonly, getter=isCompatibleWithAirPlayVideo) BOOL compatibleWithAirPlayVideo API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0)) API_UNAVAILABLE(watchos);


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
AVF_EXPORT NSString *const AVURLAssetPreferPreciseDurationAndTimingKey API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0));

/*!
  @constant		AVURLAssetReferenceRestrictionsKey
  @abstract
	Indicates the restrictions used by the asset when resolving references to external media data. The value of this key is an NSNumber wrapping an AVAssetReferenceRestrictions enum value or the logical combination of multiple such values.
  @discussion
	Some assets can contain references to media data stored outside the asset's container file, for example in another file. This key can be used to specify a policy to use when these references are encountered. If an asset contains one or more references of a type that is forbidden by the reference restrictions, loading of asset properties will fail. In addition, such an asset cannot be used with other AVFoundation modules, such as AVPlayerItem or AVAssetExportSession.
*/
AVF_EXPORT NSString *const AVURLAssetReferenceRestrictionsKey API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0)) API_UNAVAILABLE(watchos);

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
AVF_EXPORT NSString *const AVURLAssetHTTPCookiesKey API_AVAILABLE(macos(10.15), ios(8.0), tvos(9.0), watchos(1.0));

/*!
 @constant		AVURLAssetAllowsCellularAccessKey
 @abstract		Indicates whether network requests on behalf of this asset are allowed to use the cellular interface.
 @discussion
 	Default is YES.
*/
AVF_EXPORT NSString *const AVURLAssetAllowsCellularAccessKey API_AVAILABLE(macos(10.15), ios(10.0), tvos(10.0), watchos(3.0));

/*!
 @constant		AVURLAssetAllowsExpensiveNetworkAccessKey
 @abstract		Indicates whether network requests on behalf of this asset are allowed to use the expensive interface (e.g. cellular, tethered, constrained).
 @discussion
 	Default is YES.
 */
AVF_EXPORT NSString *const AVURLAssetAllowsExpensiveNetworkAccessKey API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @constant		AVURLAssetAllowsConstrainedNetworkAccessKey
 @abstract		Indicates whether network requests on behalf of this asset are allowed to use the constrained interface (e.g. interfaces marked as being in data saver mode).
 @discussion
 	Default is YES.
 */
AVF_EXPORT NSString *const AVURLAssetAllowsConstrainedNetworkAccessKey API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @constant		AVURLAssetShouldSupportAliasDataReferencesKey
 @abstract		Indicates whether alias data references in the asset should be parsed and resolved.
 @discussion
 	Default is NO. Although the majority of QuickTime movie files contain all of the media data they require, some contain references to media stored in other files. While AVFoundation and CoreMedia typically employ a URL reference for this purpose, older implementations such as QuickTime 7 have commonly employed a Macintosh alias instead, as documented in the QuickTime File Format specification. If your application must work with legacy QuickTime movie files containing alias-based references to media data stored in other files, the use of this AVURLAsset initialization option is appropriate.
 
	If you provide a value for AVURLAssetReferenceRestrictionsKey, restrictions will be observed for resolved alias references just as they are for URL references.
 
	For more details about alias resolution, consult documentation of the bookmark-related interfaces of NSURL.
 */
AVF_EXPORT NSString *const AVURLAssetShouldSupportAliasDataReferencesKey API_AVAILABLE(macos(10.10)) API_UNAVAILABLE(ios, tvos, watchos);

/*!
  @constant		AVURLAssetURLRequestAttributionKey
  @abstract
	Specifies the attribution of the URLs requested by this asset.
  @discussion
	Value is an NSNumber whose value is an NSURLRequestAttribution (see NSURLRequest.h).
	Default value is NSURLRequestAttributionDeveloper.
	All NSURLRequests issed on behalf of this AVURLAsset will be attributed with this value and follow the App Privacy Policy accordingly.
*/
AVF_EXPORT NSString *const AVURLAssetURLRequestAttributionKey API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));


/*!
  @class		AVURLAsset

  @abstract		AVURLAsset provides access to the AVAsset model for timed audiovisual media referenced by URL.

  @discussion
	Note that although instances of AVURLAsset are immutable, values for its keys may not be immediately available without blocking. See the discussion of the class AVAsset above regarding the availability of values for keys and the use of AVAsynchronousKeyValueLoading.

	Once an AVURLAsset's value for a key is available, it will not change.  AVPlayerItem provides access to information that can change dynamically during playback; see AVPlayerItem.duration and AVPlayerItem.tracks.

	AVURLAssets can be initialized with NSURLs that refer to audiovisual media resources, such as streams (including HTTP live streams), QuickTime movie files, MP3 files, and files of other types.
*/
@class AVURLAssetInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0))
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
+ (NSArray<AVFileType> *)audiovisualTypes API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0));

/*!
  @method		audiovisualMIMETypes
  @abstract		Provides the MIME types the AVURLAsset class understands.
  @result		An NSArray of NSStrings containing MIME types the AVURLAsset class understands.
*/
+ (NSArray<NSString *> *)audiovisualMIMETypes API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0));

/*!
  @method		isPlayableExtendedMIMEType:
  @abstract		Returns YES if asset is playable with the codec(s) and container type specified in extendedMIMEType. Returns NO otherwise.
  @param		extendedMIMEType
  @result		YES or NO.
*/
+ (BOOL)isPlayableExtendedMIMEType: (NSString *)extendedMIMEType API_AVAILABLE(macos(10.7), ios(5.0), tvos(9.0), watchos(1.0));

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
@property (nonatomic, readonly) AVAssetResourceLoader *resourceLoader API_AVAILABLE(macos(10.9), ios(6.0), tvos(9.0)) API_UNAVAILABLE(watchos);

@end

@class AVAssetCache;

@interface AVURLAsset (AVURLAssetCache)

/*!
 @property	assetCache
 @abstract	Provides access to an instance of AVAssetCache to use for inspection of locally cached media data. Will be nil if an asset has not been configured to store or access media data from disk.
*/
@property (nonatomic, readonly, nullable) AVAssetCache *assetCache API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

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

/*!
  @method		findCompatibleTrackForCompositionTrack:completionHandler:
  @abstract		Loads a reference to an AVAssetTrack of the target from which any timeRange
				can be inserted into a mutable composition track (via -[AVMutableCompositionTrack insertTimeRange:ofTrack:atTime:error:]).
  @param		compositionTrack
				The composition track for which a compatible AVAssetTrack is requested.
  @param		completionHandler
				A block that is invoked when loading is complete, vending an instance of AVAssetTrack or an error.
  @discussion
	Finds a track of the target with content that can be accommodated by the specified composition track.
	The logical complement of -[AVMutableComposition mutableTrackCompatibleWithTrack:].
*/
- (void)findCompatibleTrackForCompositionTrack:(AVCompositionTrack *)compositionTrack completionHandler:(void (^)(AVAssetTrack * _Nullable_result, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

@end

@interface AVURLAsset (AVAssetVariantInspection)

/*!
 @property		variants
 @abstract		Provides an array of AVAssetVariants contained in the asset
 @discussion	Some variants may not be playable according to the current device configuration.
*/
@property (nonatomic, readonly) NSArray<AVAssetVariant *> *variants API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

@end

/*!
 @category		AVURLAssetNSItemProvider
 @discussion
	AVURLAssets can be shared through any interface that supports passing NSItemProviders. Note that only AVURLAssets with file URLs can be added to NSItemProviders. Attempting to share assets with non file URLs will result in an error.
 
	AVURLAssets can be retrieved from NSItemProviders by directly requesting an AVURLAsset through -[NSItemProvider loadObjectOfClass:completionHandler:]. Requesting data representations of AVURLAssets is not supported. File representations of AVURLAssets will be sent without copying the underlying media and the receiver will be extended readonly sandbox access to the sender's original URL until the AVURLAsset is deallocated. Use of NSFileCoordinator and NSFilePresenter is recommended for both the sender and receive to coordinate possible changes in the file's state once sharing has been completed.
*/
@interface AVURLAsset (AVURLAssetNSItemProvider) <NSItemProviderReading, NSItemProviderWriting>
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
AVF_EXPORT NSString *const AVAssetDurationDidChangeNotification API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

/*!
 @constant       AVAssetContainsFragmentsDidChangeNotification
 @abstract       Posted after the value of @"containsFragments" has already been loaded and the AVFragmentedAsset is added to an AVFragmentedAssetMinder, either when 1) fragments are detected in the asset on disk after it had previously contained none or when 2) no fragments are detected in the asset on disk after it had previously contained one or more.
*/
AVF_EXPORT NSString *const AVAssetContainsFragmentsDidChangeNotification API_AVAILABLE(macos(10.11), ios(12.0), tvos(12.0)) API_UNAVAILABLE(watchos);

/*!
 @constant       AVAssetWasDefragmentedNotification
 @abstract       Posted when the asset on disk is defragmented while an AVFragmentedAsset is being minded by an AVFragmentedAssetMinder, but only if the defragmentation occurs after the status of the value of @"canContainFragments" has reached AVKeyValueStatusLoaded.
 @discussion     After this notification is posted, the value of the asset properties canContainFragments and containsFragments will both be NO.
*/
AVF_EXPORT NSString *const AVAssetWasDefragmentedNotification API_AVAILABLE(macos(10.11), ios(12.0), tvos(12.0)) API_UNAVAILABLE(watchos);

/*!
 @constant       AVAssetChapterMetadataGroupsDidChangeNotification
 @abstract       Posted when the collection of arrays of timed metadata groups representing chapters of an AVAsset change and when any of the contents of the timed metadata groups change, but only for changes that occur after the status of the value of @"availableChapterLocales" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVAssetChapterMetadataGroupsDidChangeNotification API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));
/*!

 @constant       AVAssetMediaSelectionGroupsDidChangeNotification
 @abstract       Posted when the collection of media selection groups provided by an AVAsset changes and when any of the contents of its media selection groups change, but only for changes that occur after the status of the value of @"availableMediaCharacteristicsWithMediaSelectionOptions" has reached AVKeyValueStatusLoaded.
*/
AVF_EXPORT NSString *const AVAssetMediaSelectionGroupsDidChangeNotification API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0));

#pragma mark --- AVFragmentedAsset ---
/*!
	@class			AVFragmentedAsset
 
	@abstract		A subclass of AVURLAsset that represents media resources that can be extended in total duration without modifying previously existing data structures.
	Such media resources include QuickTime movie files and MPEG-4 files that indicate, via an 'mvex' box in their 'moov' box, that they accommodate additional fragments. Media resources of other types may also be supported. To check whether a given instance of AVFragmentedAsset can be used to monitor the addition of fragments, check the value of the AVURLAsset property canContainFragments.
	An AVFragmentedAsset is capable of changing the values of certain of its properties and those of its tracks, while an operation that appends fragments to the underlying media resource in in progress, if the AVFragmentedAsset is associated with an instance of AVFragmentedAssetMinder.
	@discussion		While associated with an AVFragmentedAssetMinder, AVFragmentedAsset posts AVAssetDurationDidChangeNotification whenever new fragments are detected, as appropriate. It may also post AVAssetContainsFragmentsDidChangeNotification and AVAssetWasDefragmentedNotification, as discussed in documentation of those notifications.
*/

@protocol AVFragmentMinding

/*!
  @property		associatedWithFragmentMinder
  @abstract		Indicates whether an AVAsset that supports fragment minding is currently associated with a fragment minder, e.g. an instance of AVFragmentedAssetMinder.
  @discussion	AVAssets that support fragment minding post change notifications only while associated with a fragment minder.
*/
@property (nonatomic, readonly, getter=isAssociatedWithFragmentMinder) BOOL associatedWithFragmentMinder API_AVAILABLE(macos(10.11), ios(12.0), tvos(12.0), watchos(6.0));

@end

@class AVFragmentedAssetInternal;

API_AVAILABLE(macos(10.11), ios(12.0), tvos(12.0), watchos(6.0))
@interface AVFragmentedAsset : AVURLAsset <AVFragmentMinding>
{
@private
	AVFragmentedAssetInternal	*_fragmentedAsset __attribute__((unused));
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
  @method		loadTrackWithTrackID:completionHandler:
  @abstract		Loads an instance of AVFragmentedAssetTrack that represents the track of the specified trackID.
  @param		trackID
				The trackID of the requested AVFragmentedAssetTrack.
  @param		completionHandler
				A block that is called when the loading is finished, with either the loaded track (which may be nil if no track of the specified trackID is available) or an error.
*/
- (void)loadTrackWithTrackID:(CMPersistentTrackID)trackID completionHandler:(void (^)(AVFragmentedAssetTrack * _Nullable_result, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/*!
  @method		tracksWithMediaType:
  @abstract		Provides an array of AVFragmentedAssetTracks of the asset that present media of the specified media type.
  @param		mediaType
				The media type according to which the receiver filters its AVFragmentedAssetTracks. (Media types are defined in AVMediaFormat.h)
  @result		An NSArray of AVFragmentedAssetTracks; may be empty if no tracks of the specified media type are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVFragmentedAssetTrack *> *)tracksWithMediaType:(AVMediaType)mediaType;

/*!
  @method		loadTracksWithMediaType:completionHandler:
  @abstract		Loads an array of AVFragmentedAssetTracks of the asset that present media of the specified media type.
  @param		mediaType
				The media type according to which AVAsset filters its AVFragmentedAssetTracks. (Media types are defined in AVMediaFormat.h.)
  @param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks of the specified media type are available) or an error.
*/
- (void)loadTracksWithMediaType:(AVMediaType)mediaType completionHandler:(void (^)(NSArray<AVFragmentedAssetTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/*!
  @method		tracksWithMediaCharacteristic:
  @abstract		Provides an array of AVFragmentedAssetTracks of the asset that present media with the specified characteristic.
  @param		mediaCharacteristic
				The media characteristic according to which the receiver filters its AVFragmentedAssetTracks. (Media characteristics are defined in AVMediaFormat.h)
  @result		An NSArray of AVFragmentedAssetTracks; may be empty if no tracks with the specified characteristic are available.
  @discussion	Becomes callable without blocking when the key @"tracks" has been loaded
*/
- (NSArray<AVFragmentedAssetTrack *> *)tracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic;

/*!
  @method		loadTracksWithMediaCharacteristic:completionHandler:
  @abstract		Loads an array of AVFragmentedAssetTracks of the asset that present media with the specified characteristic.
  @param		mediaCharacteristic
				The media characteristic according to which AVAsset filters its AVFragmentedAssetTracks. (Media characteristics are defined in AVMediaFormat.h.)
  @param		completionHandler
				A block that is called when the loading is finished, with either the loaded tracks (which may be empty if no tracks with the specified characteristic are available) or an error.
*/
- (void)loadTracksWithMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic completionHandler:(void (^)(NSArray<AVFragmentedAssetTrack *> * _Nullable, NSError * _Nullable))completionHandler API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

@end

#pragma mark --- AVFragmentedAssetMinder ---
/*!
	@class			AVFragmentedAssetMinder
	@abstract		A class that periodically checks whether additional fragments have been appended to fragmented assets.
*/

@class AVFragmentedAssetMinderInternal;

API_AVAILABLE(macos(10.11), ios(12.0), tvos(12.0), watchos(6.0))
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
	@method			initWithAsset:mindingInterval:
	@abstract       Creates an AVFragmentedAssetMinder, adds the specified asset to it, and sets the mindingInterval to the specified value.
	@param			asset
					An instance of AVFragmentedAsset to add to the AVFragmentedAssetMinder
	@param			mindingInterval
					The initial minding interval of the AVFragmentedAssetMinder.
	@result			A new instance of AVFragmentedAssetMinder.
*/
- (instancetype)initWithAsset:(AVAsset<AVFragmentMinding> *)asset mindingInterval:(NSTimeInterval)mindingInterval;

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

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVURLAsset (AVURLAssetContentKeyEligibility) <AVContentKeyRecipient>

/*!
	@property 		mayRequireContentKeysForMediaDataProcessing
	@abstract		Allows AVURLAsset to be added as a content key recipient to an AVContentKeySession.
*/
@property (nonatomic, readonly) BOOL mayRequireContentKeysForMediaDataProcessing API_AVAILABLE(macos(10.12.4), ios(10.3), tvos(10.2), watchos(3.3));

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVAsset.h>
#endif

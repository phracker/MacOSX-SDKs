/*
	File:  AVMediaSelectionGroup.h

	Framework:  AVFoundation
 
	Copyright 2011-2015 Apple Inc. All rights reserved.

*/

/*!
 @class			AVMediaSelectionGroup

 @abstract		AVMediaSelectionGroup provides a collection of mutually exclusive options for the presentation of media within an asset.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVMediaSelectionOption;
@class AVMediaSelectionGroupInternal;

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface AVMediaSelectionGroup : NSObject <NSCopying> {
@private
	AVMediaSelectionGroupInternal	*_mediaSelectionGroup;
}

/*!
 @property		options
 @abstract		A collection of mutually exclusive media selection options.
 @discussion	An NSArray of AVMediaSelectionOption*.
*/
@property (nonatomic, readonly) NSArray<AVMediaSelectionOption *> *options;

/*!
 @property		defaultOption
 @abstract		Indicates the default option in the group, i.e. the option that's intended for use in the absence of a specific end-user selection or preference.
 @discussion
	Can be nil, indicating that without a specific end-user selection or preference, no option in the group is intended to be selected.
*/
@property (nonatomic, readonly, nullable) AVMediaSelectionOption *defaultOption NS_AVAILABLE(10_10, 8_0);

/*!
 @property		allowsEmptySelection
 @abstract		Indicates whether it's possible to present none of the options in the group when an associated AVPlayerItem is played.
 @discussion
	If allowsEmptySelection is YES, all of the available media options in the group can be deselected by passing nil
	as the specified AVMediaSelectionOption to -[AVPlayerItem selectMediaOption:inMediaSelectionGroup:].
*/
@property (nonatomic, readonly) BOOL allowsEmptySelection;

/*!
  @method		mediaSelectionOptionWithPropertyList:
  @abstract		Returns the instance of AVMediaSelectionOption with properties that match the specified property list.
  @param		plist
  				A property list previously obtained from an option in the group via -[AVMediaSelectionOption propertyList].
  @result		If the specified properties match those of an option in the group, an instance of AVMediaSelectionOption. Otherwise nil.
*/
- (nullable AVMediaSelectionOption *)mediaSelectionOptionWithPropertyList:(id)plist;

@end


/*!
  @category		AVMediaSelectionOptionFiltering
  @abstract		Filtering of media selection options.
  @discussion
	The AVMediaSelectionOptionFiltering category is provided for convenience in filtering the media selection options in a group
	according to playability, locale, and media characteristics.
	Note that it's possible to implement additional filtering behaviors by using -[NSArray indexesOfObjectsPassingTest:].
*/
@interface AVMediaSelectionGroup (AVMediaSelectionOptionFiltering)

/*!
  @method		playableMediaSelectionOptionsFromArray:
  @abstract		Filters an array of AVMediaSelectionOptions according to whether they are playable.
  @param		mediaSelectionOptions
  				An array of AVMediaSelectionOption to be filtered according to whether they are playable.
  @result		An instance of NSArray containing the media selection options of the specified NSArray that are playable.
*/
+ (NSArray<AVMediaSelectionOption *> *)playableMediaSelectionOptionsFromArray:(NSArray<AVMediaSelectionOption *> *)mediaSelectionOptions;

/*!
 @method		mediaSelectionOptionsFromArray:filteredAndSortedAccordingToPreferredLanguages:
 @abstract		Filters an array of AVMediaSelectionOptions according to whether their locales match any language identifier in the specified array of preferred languages. The returned array is sorted according to the order of preference of the language each matches.
 @param			mediaSelectionOptions
				An array of AVMediaSelectionOptions to be filtered and sorted.
 @param			preferredLanguages
				An array of language identifiers in order of preference, each of which is an IETF BCP 47 (RFC 4646) language identifier. Use +[NSLocale preferredLanguages] to obtain the user's list of preferred languages.
 @result		An instance of NSArray containing media selection options of the specified NSArray that match a preferred language, sorted according to the order of preference of the language each matches.
*/
+ (NSArray<AVMediaSelectionOption *> *)mediaSelectionOptionsFromArray:(NSArray<AVMediaSelectionOption *> *)mediaSelectionOptions filteredAndSortedAccordingToPreferredLanguages:(NSArray<NSString *> *)preferredLanguages NS_AVAILABLE(10_8, 6_0);

/*!
  @method		mediaSelectionOptionsFromArray:withLocale:
  @abstract		Filters an array of AVMediaSelectionOptions according to locale.
  @param		mediaSelectionOptions
				An array of AVMediaSelectionOption to be filtered by locale.
  @param		locale
  				The NSLocale that must be matched for a media selection option to be copied to the output array.
  @result		An instance of NSArray containing the media selection options of the specified NSArray that match the specified locale.
*/
+ (NSArray<AVMediaSelectionOption *> *)mediaSelectionOptionsFromArray:(NSArray<AVMediaSelectionOption *> *)mediaSelectionOptions withLocale:(NSLocale *)locale;

/*!
  @method		mediaSelectionOptionsFromArray:withMediaCharacteristics:
  @abstract		Filters an array of AVMediaSelectionOptions according to one or more media characteristics.
  @param		mediaSelectionOptions
  				An array of AVMediaSelectionOptions to be filtered by media characteristic.
  @param		mediaCharacteristics
  				The media characteristics that must be matched for a media selection option to be copied to the output array.
  @result		An instance of NSArray containing the media selection options of the specified NSArray that match the specified
				media characteristics.
*/
+ (NSArray<AVMediaSelectionOption *> *)mediaSelectionOptionsFromArray:(NSArray<AVMediaSelectionOption *> *)mediaSelectionOptions withMediaCharacteristics:(NSArray<NSString *> *)mediaCharacteristics;

/*!
  @method		mediaSelectionOptionsFromArray:withoutMediaCharacteristics:
  @abstract		Filters an array of AVMediaSelectionOptions according to whether they lack one or more media characteristics.
  @param		mediaSelectionOptions
  				An array of AVMediaSelectionOptions to be filtered by media characteristic.
  @param		mediaCharacteristics
  				The media characteristics that must not be present for a media selection option to be copied to the output array.
  @result		An instance of NSArray containing the media selection options of the specified NSArray that lack the specified
				media characteristics.
*/
+ (NSArray<AVMediaSelectionOption *> *)mediaSelectionOptionsFromArray:(NSArray<AVMediaSelectionOption *> *)mediaSelectionOptions withoutMediaCharacteristics:(NSArray<NSString *> *)mediaCharacteristics;

@end


/*!
 @class			AVMediaSelectionOption

 @abstract		AVMediaSelectionOption represents a specific option for the presentation of media within a group of options.

*/

@class AVMediaSelectionOptionInternal;
@class AVMetadataItem;

NS_CLASS_AVAILABLE(10_8, 5_0)
@interface AVMediaSelectionOption : NSObject <NSCopying> {
@private
	AVMediaSelectionOptionInternal	*_mediaSelectionOption;
}

/*!
 @property		mediaType
 @abstract		The media type of the media data, e.g. AVMediaTypeAudio, AVMediaTypeSubtitle, etc.
*/
@property (nonatomic, readonly) NSString *mediaType;

/*!
 @property		mediaSubTypes
 @abstract		The mediaSubTypes of the media data associated with the option. 
 @discussion
	An NSArray of NSNumbers carrying four character codes (of type FourCharCode) as defined in CoreAudioTypes.h for audio media and in CMFormatDescription.h for video media.
	Also see CMFormatDescriptionGetMediaSubType in CMFormatDescription.h for more information about media subtypes.
	
	Note that if no information is available about the encoding of the media presented when a media option is selected, the value of mediaSubTypes will be an empty array. This can occur, for example, with streaming media. In these cases the value of mediaSubTypes should simply not be used as a criteria for selection.
*/
@property (nonatomic, readonly) NSArray<NSNumber *> *mediaSubTypes;

/*!
  @method		hasMediaCharacteristic:
  @abstract		Reports whether the media selection option includes media with the specified media characteristic.
  @param		mediaCharacteristic
  				The media characteristic of interest, e.g. AVMediaCharacteristicVisual, AVMediaCharacteristicAudible, AVMediaCharacteristicLegible, etc.
  @result		YES if the media selection option includes media with the specified characteristic, otherwise NO.
*/
- (BOOL)hasMediaCharacteristic:(NSString *)mediaCharacteristic;

/*!
 @property		playable
 @abstract		Indicates whether a media selection option is playable.
 @discussion	If the media data associated with the option cannot be decoded or otherwise rendered, playable is NO.
*/
@property (nonatomic, readonly, getter=isPlayable) BOOL playable;

/*!
 @property		extendedLanguageTag
 @abstract		Indicates the RFC 4646 language tag associated with the option. May be nil.
 */
@property (nonatomic, readonly, nullable) NSString *extendedLanguageTag NS_AVAILABLE(10_9, 7_0);

/*!
 @property		locale
 @abstract		Indicates the locale for which the media option was authored.
 @discussion
 	Use -[NSLocale objectForKey:NSLocaleLanguageCode] to obtain the language code of the locale. See NSLocale.h for additional information.
*/
@property (nonatomic, readonly, nullable) NSLocale *locale;

/*!
 @property		commonMetadata
 @abstract		Provides an array of AVMetadataItems for each common metadata key for which a value is available.
 @discussion
   The array of AVMetadataItems can be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:], according to locale via +[AVMetadataItem metadataItemsFromArray:withLocale:],
   or according to key via +[AVMetadataItem metadataItemsFromArray:withKey:keySpace:].
   Example: to obtain the name (or title) of a media selection option in any of the user's preferred languages.

	NSString *title = nil;
	NSArray *titles = [AVMetadataItem metadataItemsFromArray:[mediaSelectionOption commonMetadata] withKey:AVMetadataCommonKeyTitle keySpace:AVMetadataKeySpaceCommon];
	if ([titles count] > 0)
	{
		// Try to get a title that matches one of the user's preferred languages.
		NSArray *titlesForPreferredLanguages = [AVMetadataItem metadataItemsFromArray:titles filteredAndSortedAccordingToPreferredLanguages:[NSLocale preferredLanguages]];
		if ([titlesForPreferredLanguages count] > 0)
		{
			title = [[titlesForPreferredLanguages objectAtIndex:0] stringValue];
		}
		
		// No matches in any of the preferred languages. Just use the primary title metadata we find.
		if (title == nil)
		{
			title = [[titles objectAtIndex:0] stringValue];
		}
	}

*/
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *commonMetadata;

/*!
 @property		availableMetadataFormats
 @abstract		Provides an NSArray of NSStrings, each representing a metadata format that contains metadata associated with the option (e.g. ID3, iTunes metadata, etc.).
 @discussion
   Metadata formats are defined in AVMetadataFormat.h.
*/
@property (nonatomic, readonly) NSArray<NSString *> *availableMetadataFormats;

/*!
  @method		metadataForFormat:
  @abstract		Provides an NSArray of AVMetadataItems, one for each metadata item in the container of the specified format.
  @param		format
  				The metadata format for which items are requested.
  @result		An NSArray containing AVMetadataItems.
*/
- (NSArray<AVMetadataItem *> *)metadataForFormat:(NSString *)format;

/*!
  @method		associatedMediaSelectionOptionInMediaSelectionGroup
  @abstract		If a media selection option in another group is associated with the specified option, returns a reference to the associated option.
  @param		mediaSelectionGroup
  				A media selection group in which an associated option is to be sought.
  @result		An instance of AVMediaSelectionOption.
 @discussion
   Audible media selection options often have associated legible media selection options; in particular, audible options are typically associated with forced-only subtitle options with the same locale. See AVMediaCharacteristicContainsOnlyForcedSubtitles in AVMediaFormat.h for a discussion of forced-only subtitles.
*/
- (nullable AVMediaSelectionOption *)associatedMediaSelectionOptionInMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup;

/*!
  @method		propertyList
  @abstract		Returns a serializable property list that can be used to obtain an instance of AVMediaSelectionOption representing the same option as the receiver via -[AVMediaSelectionGroup mediaSelectionOptionWithPropertyList:].
  @result		A serializable property list that's sufficient to identify the option within its group. For serialization utilities, see NSPropertyList.h.
*/
- (id)propertyList;

/*!
  @method		displayNameWithLocale
  @abstract		Provides an NSString suitable for display.
  @param		locale
  				Localize manufactured portions of the string using the specificed locale.
  @discussion
   May use this option's common metadata, media characteristics and locale properties in addition to the provided locale to formulate an NSString intended for display. Will only consider common metadata with the specified locale.
*/
- (NSString *)displayNameWithLocale:(NSLocale *)locale NS_AVAILABLE(10_9, 7_0);

/*!
  @property		displayName
  @abstract		Provides an NSString suitable for display using the current system locale.
  @discussion
   May use this option's common metadata, media characteristics and locale properties in addition to the current system locale to formulate an NSString intended for display.
   In the event that common metadata is not available in the specified locale, displayName will fall back to considering locales with the multilingual ("mul") then undetermined ("und") locale identifiers.
   For a display name strictly with the specified locale use displayNameWithLocale: instead.
*/
@property (nonatomic, readonly) NSString *displayName NS_AVAILABLE(10_9, 7_0);

@end

NS_ASSUME_NONNULL_END

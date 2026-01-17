#if !__has_include(<AVFCore/AVMediaSelectionGroup.h>)
/*
	File:  AVMediaSelectionGroup.h

	Framework:  AVFoundation
 
	Copyright 2011-2017 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AVMediaSelectionOption;
@class AVMediaSelectionGroupInternal;
@class AVCustomMediaSelectionScheme;
@class AVMediaPresentationSelector;
@class AVMediaPresentationSetting;

/// AVMediaSelectionGroup provides a collection of mutually exclusive options for the presentation of media within an asset.
API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVMediaSelectionGroup : NSObject <NSCopying> {
@private
	AVMediaSelectionGroupInternal	*_mediaSelectionGroup;
}

/// A collection of mutually exclusive media selection options.
/// 
/// An NSArray of AVMediaSelectionOption*.
@property (nonatomic, readonly) NSArray<AVMediaSelectionOption *> *options;

/// Indicates the default option in the group, i.e. the option that's intended for use in the absence of a specific end-user selection or preference.
/// 
/// Can be nil, indicating that without a specific end-user selection or preference, no option in the group is intended to be selected.
@property (nonatomic, readonly, nullable) AVMediaSelectionOption *defaultOption API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Indicates whether it's possible to present none of the options in the group when an associated AVPlayerItem is played.
/// 
/// If allowsEmptySelection is YES, all of the available media options in the group can be deselected by passing nil
/// as the specified AVMediaSelectionOption to -[AVPlayerItem selectMediaOption:inMediaSelectionGroup:].
@property (nonatomic, readonly) BOOL allowsEmptySelection;

/// Returns the instance of AVMediaSelectionOption with properties that match the specified property list.
/// 
/// - Parameter plist: A property list previously obtained from an option in the group via -[AVMediaSelectionOption propertyList].
/// 
/// - Returns: If the specified properties match those of an option in the group, an instance of AVMediaSelectionOption. Otherwise nil.
- (nullable AVMediaSelectionOption *)mediaSelectionOptionWithPropertyList:(id)plist;

@end

/// Filtering of media selection options.
/// 
/// The AVMediaSelectionOptionFiltering category is provided for convenience in filtering the media selection options in a group
/// according to playability, locale, and media characteristics.
/// Note that it's possible to implement additional filtering behaviors by using -[NSArray indexesOfObjectsPassingTest:].
@interface AVMediaSelectionGroup (AVMediaSelectionOptionFiltering)

/// Filters an array of AVMediaSelectionOptions according to whether they are playable.
/// 
/// - Parameter mediaSelectionOptions: An array of AVMediaSelectionOption to be filtered according to whether they are playable.
/// 
/// - Returns: An instance of NSArray containing the media selection options of the specified NSArray that are playable.
+ (NSArray<AVMediaSelectionOption *> *)playableMediaSelectionOptionsFromArray:(NSArray<AVMediaSelectionOption *> *)mediaSelectionOptions;

/// Filters an array of AVMediaSelectionOptions according to whether their locales match any language identifier in the specified array of preferred languages. The returned array is sorted according to the order of preference of the language each matches.
/// 
/// - Parameter mediaSelectionOptions: An array of AVMediaSelectionOptions to be filtered and sorted.
/// - Parameter preferredLanguages: An array of language identifiers in order of preference, each of which is an IETF BCP 47 (RFC 4646) language identifier. If your goal is to provide the best match for the end user's preferred languages without consideration of your app's available localizations, pass [NSLocale preferredLanguages] as the value of preferredLanguages. However, if you want to filter the available choices in order to obtain the best match among the localizations that are available for your app, pass [NSBundle preferredLocalizationsFromArray:[[NSBundle mainBundle] localizations] forPreferences:[NSLocale preferredLanguages]] instead. The latter choice is normally more appropriate for strings intended for display as part of the app's UI.
/// 
/// - Returns: An instance of NSArray containing media selection options of the specified NSArray that match a preferred language, sorted according to the order of preference of the language each matches.
+ (NSArray<AVMediaSelectionOption *> *)mediaSelectionOptionsFromArray:(NSArray<AVMediaSelectionOption *> *)mediaSelectionOptions filteredAndSortedAccordingToPreferredLanguages:(NSArray<NSString *> *)preferredLanguages API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Filters an array of AVMediaSelectionOptions according to locale.
/// 
/// - Parameter mediaSelectionOptions: An array of AVMediaSelectionOption to be filtered by locale.
/// - Parameter locale: The NSLocale that must be matched for a media selection option to be copied to the output array.
/// 
/// - Returns: An instance of NSArray containing the media selection options of the specified NSArray that match the specified locale.
+ (NSArray<AVMediaSelectionOption *> *)mediaSelectionOptionsFromArray:(NSArray<AVMediaSelectionOption *> *)mediaSelectionOptions withLocale:(NSLocale *)locale;

/// Filters an array of AVMediaSelectionOptions according to one or more media characteristics.
/// 
/// - Parameter mediaSelectionOptions: An array of AVMediaSelectionOptions to be filtered by media characteristic.
/// - Parameter mediaCharacteristics: The media characteristics that must be matched for a media selection option to be copied to the output array.
/// 
/// - Returns: An instance of NSArray containing the media selection options of the specified NSArray that match the specified
/// 				media characteristics.
+ (NSArray<AVMediaSelectionOption *> *)mediaSelectionOptionsFromArray:(NSArray<AVMediaSelectionOption *> *)mediaSelectionOptions withMediaCharacteristics:(NSArray<AVMediaCharacteristic> *)mediaCharacteristics;

/// Filters an array of AVMediaSelectionOptions according to whether they lack one or more media characteristics.
/// 
/// - Parameter mediaSelectionOptions: An array of AVMediaSelectionOptions to be filtered by media characteristic.
/// - Parameter mediaCharacteristics: The media characteristics that must not be present for a media selection option to be copied to the output array.
/// 
/// - Returns: An instance of NSArray containing the media selection options of the specified NSArray that lack the specified
/// 				media characteristics.
+ (NSArray<AVMediaSelectionOption *> *)mediaSelectionOptionsFromArray:(NSArray<AVMediaSelectionOption *> *)mediaSelectionOptions withoutMediaCharacteristics:(NSArray<AVMediaCharacteristic> *)mediaCharacteristics;

@end

@class AVMediaSelectionOptionInternal;
@class AVMetadataItem;

/// AVMediaSelectionOption represents a specific option for the presentation of media within a group of options.
API_AVAILABLE(macos(10.8), ios(5.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVMediaSelectionOption : NSObject <NSCopying> {
@private
	AVMediaSelectionOptionInternal	*_mediaSelectionOption;
}

/// The media type of the media data, e.g. AVMediaTypeAudio, AVMediaTypeSubtitle, etc.
@property (nonatomic, readonly) AVMediaType mediaType;

/// The mediaSubTypes of the media data associated with the option.
/// 
/// An NSArray of NSNumbers carrying four character codes (of type FourCharCode) as defined in CoreAudioTypes.h for audio media and in CMFormatDescription.h for video media.
/// Also see CMFormatDescriptionGetMediaSubType in CMFormatDescription.h for more information about media subtypes.
/// 
/// Note that if no information is available about the encoding of the media presented when a media option is selected, the value of mediaSubTypes will be an empty array. This can occur, for example, with streaming media. In these cases the value of mediaSubTypes should simply not be used as a criteria for selection.
@property (nonatomic, readonly) NSArray<NSNumber *> *mediaSubTypes;

/// Reports whether the media selection option includes media with the specified media characteristic.
/// 
/// - Parameter mediaCharacteristic: The media characteristic of interest, e.g. AVMediaCharacteristicVisual, AVMediaCharacteristicAudible, AVMediaCharacteristicLegible, etc.
/// 
/// - Returns: YES if the media selection option includes media with the specified characteristic, otherwise NO.
- (BOOL)hasMediaCharacteristic:(AVMediaCharacteristic)mediaCharacteristic;

/// Indicates whether a media selection option is playable.
/// 
/// If the media data associated with the option cannot be decoded or otherwise rendered, playable is NO.
@property (nonatomic, readonly, getter=isPlayable) BOOL playable;

/// Indicates the RFC 4646 language tag associated with the option. May be nil.
@property (nonatomic, readonly, nullable) NSString *extendedLanguageTag API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Indicates the locale for which the media option was authored.
/// 
/// Use -[NSLocale objectForKey:NSLocaleLanguageCode] to obtain the language code of the locale. See NSLocale.h for additional information.
@property (nonatomic, readonly, nullable) NSLocale *locale;

/// Provides an array of AVMetadataItems for each common metadata key for which a value is available.
/// 
/// The array of AVMetadataItems can be filtered according to language via +[AVMetadataItem metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:], according to locale via +[AVMetadataItem metadataItemsFromArray:withLocale:],
/// or according to key via +[AVMetadataItem metadataItemsFromArray:withKey:keySpace:].
/// Example: to obtain the name (or title) of a media selection option in any of the user's preferred languages.
/// ```objc
/// NSString *title = nil;
/// NSArray *titles = [AVMetadataItem metadataItemsFromArray:[mediaSelectionOption commonMetadata] withKey:AVMetadataCommonKeyTitle keySpace:AVMetadataKeySpaceCommon];
/// if ([titles count] > 0)
/// {
/// 	// Try to get a title that matches one of the user's preferred languages.
/// 	NSArray *titlesForPreferredLanguages = [AVMetadataItem metadataItemsFromArray:titles filteredAndSortedAccordingToPreferredLanguages:[NSLocale preferredLanguages]];
/// 	if ([titlesForPreferredLanguages count] > 0)
/// 	{
/// 		title = [[titlesForPreferredLanguages objectAtIndex:0] stringValue];
/// 	}
/// 
/// 	// No matches in any of the preferred languages. Just use the primary title metadata we find.
/// 	if (title == nil)
/// 	{
/// 		title = [[titles objectAtIndex:0] stringValue];
/// 	}
/// }
/// ```
@property (nonatomic, readonly) NSArray<AVMetadataItem *> *commonMetadata;

/// Provides an NSArray of NSStrings, each representing a metadata format that contains metadata associated with the option (e.g. ID3, iTunes metadata, etc.).
/// 
/// Metadata formats are defined in AVMetadataFormat.h.
@property (nonatomic, readonly) NSArray<NSString *> *availableMetadataFormats;

/// Provides an NSArray of AVMetadataItems, one for each metadata item in the container of the specified format.
/// 
/// - Parameter format: The metadata format for which items are requested.
/// 
/// - Returns: An NSArray containing AVMetadataItems.
- (NSArray<AVMetadataItem *> *)metadataForFormat:(NSString *)format;

/// If a media selection option in another group is associated with the specified option, returns a reference to the associated option.
/// 
/// Audible media selection options often have associated legible media selection options; in particular, audible options are typically associated with forced-only subtitle options with the same locale. See AVMediaCharacteristicContainsOnlyForcedSubtitles in AVMediaFormat.h for a discussion of forced-only subtitles.
/// 
/// - Parameter mediaSelectionGroup: A media selection group in which an associated option is to be sought.
/// 
/// - Returns: An instance of AVMediaSelectionOption.
- (nullable AVMediaSelectionOption *)associatedMediaSelectionOptionInMediaSelectionGroup:(AVMediaSelectionGroup *)mediaSelectionGroup;

/// Returns a serializable property list that can be used to obtain an instance of AVMediaSelectionOption representing the same option as the receiver via -[AVMediaSelectionGroup mediaSelectionOptionWithPropertyList:].
/// 
/// - Returns: A serializable property list that's sufficient to identify the option within its group. For serialization utilities, see NSPropertyList.h.
- (id)propertyList;

/// Provides an NSString suitable for display.
/// 
/// May use this option's common metadata, media characteristics and locale properties in addition to the provided locale to formulate an NSString intended for display. Will only consider common metadata with the specified locale.
/// 
/// - Parameter locale: Localize manufactured portions of the string using the specificed locale.
- (NSString *)displayNameWithLocale:(NSLocale *)locale API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));

/// Provides an NSString suitable for display using the current system locale.
/// 
/// May use this option's common metadata, media characteristics and locale properties in addition to the current system locale to formulate an NSString intended for display.
/// In the event that common metadata is not available in the specified locale, displayName will fall back to considering locales with the multilingual ("mul") then undetermined ("und") locale identifiers.
/// For a display name strictly with the specified locale use displayNameWithLocale: instead.
@property (nonatomic, readonly) NSString *displayName API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));

@end

@interface AVMediaSelectionGroup (AVMediaSelectionGroupCustomMediaSelectionScheme)

/// For content that has been authored with the express intent of offering an alternative selection interface for AVMediaSelectionOptions, AVCustomMediaSelectionScheme provides a collection of custom settings for controlling the presentation of the media.
@property (readonly, nonatomic, nullable) AVCustomMediaSelectionScheme *customMediaSelectionScheme API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

@end

/// For content that has been authored with the express intent of offering an alternative selection interface for AVMediaSelectionOptions, AVCustomMediaSelectionScheme provides a collection of custom settings for controlling the presentation of the media.
/// 
/// Each selectable setting is associated with a media characteristic that one or more of the AVMediaSelectionOptions in the AVMediaSelectionGroup possesses. By selecting a setting in a user interface based on an AVCustomMediaSelectionScheme, users are essentially indicating a preference for the media characteristic of the selected setting. Selection of a specific AVMediaSelectionOption in the AVMediaSelectionGroup is then derived from the user's indicated preferences. Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))
@interface AVCustomMediaSelectionScheme : NSObject <NSCopying>

/// Indicates whether an alternative selection interface should provide a menu of language choices.
@property (readonly) BOOL shouldOfferLanguageSelection;

/// Provides available language choices.
/// 
/// Each string in the array is intended to be interpreted as a BCP 47 language tag.
@property (readonly) NSArray <NSString *> *availableLanguages;

/// Provides custom settings.
@property (readonly) NSArray <AVMediaPresentationSelector *> *selectors;

/// Provides an array of media presentation settings that can be effective at the same time as the specified language and settings for other selectors of the receiver.
/// 
/// If the content is authored to provide a collection of AVMediaSelectionOptions that include one or more with all of the combinations of media characteristics of the specified AVMediaPresentationSettings together with all of the settings of the specified AVMediaPresentationSelector, this method will return all of the settings for that selector. However, if one or more of the available combinations are not possessed by any of the AVMediaSelectionOptions, it will return fewer.
/// 
/// - Parameter selector: The AVMediaPresentationSelector for which complementary settings are requested.
/// - Parameter language: A BCP 47 language tag chosen among the availableLanguages of the receiver. If no language setting pertains, can be nil.
/// - Parameter settings: A collection of AVMediaPresentationSettings provided by selectors of the receiver other than the specified selector. Because no two AVMediaPresentationSettings of the same AVMediaPresentationSelector are complementary, an empty array will be returned if you specify more than one setting for any selector.
- (NSArray <AVMediaPresentationSetting *> *)mediaPresentationSettingsForSelector:(AVMediaPresentationSelector *)selector complementaryToLanguage:(nullable NSString *)language settings:(NSArray <AVMediaPresentationSetting *> *)settings;

@end

/// For content that has been authored with the express intent of offering an alternative selection interface for AVMediaSelectionOptions, AVMediaPresentationSelector represents a collection of mutually exclusive settings.
/// 
/// Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))
@interface AVMediaPresentationSelector : NSObject <NSCopying>

/// Provides the authored identifier for the selector.
@property (readonly) NSString *identifier;

/// Returns the display name for the selector that best matches the specified locale identifier.
- (NSString *)displayNameForLocaleIdentifier:(NSString *)localeIdentifier;

/// Provides selectable mutually exclusive settings for the selector.
@property (readonly) NSArray <AVMediaPresentationSetting *> *settings;

@end

/// For content that has been authored with the express intent of offering an alternative selection interface for AVMediaSelectionOptions, AVMediaPresentationSetting represents a selectable setting for controlling the presentation of the media.
/// 
/// Each selectable setting is associated with a media characteristic that one or more of the AVMediaSelectionOptions in the AVMediaSelectionGroup possesses. By selecting a setting in a user interface that offers AVMediaPresentationSettings, users are essentially indicating a preference for the media characteristic of the selected setting. Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))
@interface AVMediaPresentationSetting : NSObject <NSCopying>

/// Provides the media characteristic that corresponds to the selectable setting.
@property (readonly) AVMediaCharacteristic mediaCharacteristic;

/// Returns the display name for the selectable setting that best matches the specified locale identifier.
- (NSString *)displayNameForLocaleIdentifier:(NSString *)localeIdentifier;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVMediaSelectionGroup.h>
#endif

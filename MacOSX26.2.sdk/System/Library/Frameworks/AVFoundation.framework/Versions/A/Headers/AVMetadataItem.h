#if !__has_include(<AVFCore/AVMetadataItem.h>)
/*
    File:  AVMetadataItem.h

	Framework:  AVFoundation
 
	Copyright 2010-2023 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <AVFoundation/AVMetadataFormat.h>
#import <AVFoundation/AVMetadataIdentifiers.h>
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>

#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@class AVMetadataItemFilter;
@class AVMutableMetadataItem;

/*!
 @class			AVMetadataItem
 @abstract		AVMetadataItem represents an item of metadata associated with an audiovisual asset or with one of its tracks.
 @discussion		'
	AVMetadataItems have keys that accord with the specification of the container format from which they're drawn. Full details of the metadata formats, metadata keys, and metadata keyspaces supported by AVFoundation are available among the defines in AVMetadataFormat.h.
	
	Note that arrays of AVMetadataItems vended by AVAsset and other classes are "lazy", similar to array-based keys that support key-value observing, meaning that you can obtain objects from those arrays without incurring overhead for items you don't ultimately inspect.
 
	AVMetadataItem conforms to NSMutableCopying, but for some "lazy" instances of AVMetadataItem, creating a mutable copy can cause properties to load synchronously.  This can cause the calling thread to block while synchronous I/O is performed.  To avoid the possiblity of blocking, which should be avoided on the main thread or when running on one of Swift's concurrency threads, ensure that the `value` and `extraAttributes` properties are loaded prior to making a mutable copy.  This can be done using the methods of AVAsynchronousKeyValueLoading, either to synchronously check whether loading has already occurred or to asynchronously load the property values.

	You can filter arrays of AVMetadataItems by locale or by key and keySpace via the category AVMetadataItemArrayFiltering defined below.
*/

@class AVMetadataItemInternal;

API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVMetadataItem : NSObject <AVAsynchronousKeyValueLoading, NSCopying, NSMutableCopying>
{
	AVMetadataItemInternal	*_priv;
}

/* Indicates the identifier of the metadata item. Publicly defined identifiers are declared in AVMetadataIdentifiers.h. */
@property (nonatomic, readonly, copy, nullable) AVMetadataIdentifier identifier API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/* indicates the IETF BCP 47 (RFC 4646) language identifier of the metadata item; may be nil if no language tag information is available */
@property (nonatomic, readonly, copy, nullable) NSString *extendedLanguageTag API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/* indicates the locale of the metadata item; may be nil if no locale information is available for the metadata item */
@property (nonatomic, readonly, copy, nullable) NSLocale *locale;

/* indicates the timestamp of the metadata item. */
@property (nonatomic, readonly) CMTime time;

/* indicates the duration of the metadata item */
@property (nonatomic, readonly) CMTime duration API_AVAILABLE(macos(10.7), ios(4.2), tvos(9.0), watchos(1.0), visionos(1.0));

/* indicates the data type of the metadata item's value.  Publicly defined data types are declared in <CoreMedia/CMMetadata.h> */
@property (nonatomic, readonly, copy, nullable) NSString *dataType API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/* provides the value of the metadata item */
@property (nonatomic, readonly, copy, nullable) id<NSObject, NSCopying> value AVF_DEPRECATED_FOR_SWIFT_ONLY("Use load(.value) instead", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0), visionos(1.0, 1.0));

/* provides a dictionary of the additional attributes */
@property (nonatomic, readonly, copy, nullable) NSDictionary<AVMetadataExtraAttributeKey, id> *extraAttributes AVF_DEPRECATED_FOR_SWIFT_ONLY("Use load(.extraAttributes) instead", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0), visionos(1.0, 1.0));

@end


@interface AVMetadataItem (AVMetadataItemDateRepresentation)

/* indicates the start date of the timed metadata; nil if no date is indicated */
@property (nonatomic, readonly, copy, nullable) NSDate *startDate API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

@end


@interface AVMetadataItem (AVMetadataItemTypeCoercion)

/* provides the value of the metadata item as a string; will be nil if the value cannot be represented as a string */
@property (nonatomic, readonly, nullable) NSString *stringValue AVF_DEPRECATED_FOR_SWIFT_ONLY("Use load(.stringValue) instead", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0), visionos(1.0, 1.0));

/* provides the value of the metadata item as an NSNumber. If the metadata item's value can't be coerced to a number, @"numberValue" will be nil. */
@property (nonatomic, readonly, nullable) NSNumber *numberValue AVF_DEPRECATED_FOR_SWIFT_ONLY("Use load(.numberValue) instead", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0), visionos(1.0, 1.0));

/* provides the value of the metadata item as an NSDate. If the metadata item's value can't be coerced to a date, @"dateValue" will be nil. */
@property (nonatomic, readonly, nullable) NSDate *dateValue AVF_DEPRECATED_FOR_SWIFT_ONLY("Use load(.dateValue) instead", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0), visionos(1.0, 1.0));

/* provides the raw bytes of the value of the metadata item */
@property (nonatomic, readonly, nullable) NSData *dataValue AVF_DEPRECATED_FOR_SWIFT_ONLY("Use load(.dataValue) instead", macos(10.7, 13.0), ios(4.0, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0), visionos(1.0, 1.0));

@end


@interface AVMetadataItem (AVAsynchronousKeyValueLoading)

/* The following two methods of the AVAsynchronousKeyValueLoading protocol are re-declared here so that they can be annotated with availability information. See AVAsynchronousKeyValueLoading.h for documentation. */

- (AVKeyValueStatus)statusOfValueForKey:(NSString *)key error:(NSError * _Nullable * _Nullable)outError
#if __swift__
API_DEPRECATED("Use status(of:) instead", macos(10.7, 13.0), ios(4.2, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0)) API_UNAVAILABLE(visionos);
#else
API_AVAILABLE(macos(10.7), ios(4.2), tvos(9.0), watchos(1.0), visionos(1.0));
#endif

- (void)loadValuesAsynchronouslyForKeys:(NSArray<NSString *> *)keys completionHandler:(nullable void (^ NS_SWIFT_SENDABLE)(void))handler
#if __swift__
API_DEPRECATED("Use load(_:) instead.  For non-deprecated properties that do not have an AVAsyncProperty equivalent, continue to query these properties synchronously", macos(10.7, 13.0), ios(4.2, 16.0), tvos(9.0, 16.0), watchos(1.0, 9.0)) API_UNAVAILABLE(visionos);
#else
API_AVAILABLE(macos(10.7), ios(4.2), tvos(9.0), watchos(1.0), visionos(1.0));
#endif

@end


@interface AVMetadataItem (AVMetadataItemArrayFiltering)

/*!
 @method		metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:
 @abstract		Filters an array of AVMetadataItems according to whether their locales match any language identifier in the specified array of preferred languages. The returned array is sorted according to the order of preference of the language each matches.
 @param			metadataItems
				An array of AVMetadataItems to be filtered and sorted.
 @param			preferredLanguages
				An array of language identifiers in order of preference, each of which is an IETF BCP 47 (RFC 4646) language identifier. If your goal is to provide the best match for the end user's preferred languages without consideration of your app's available localizations, pass [NSLocale preferredLanguages] as the value of preferredLanguages. However, if you want to filter the available choices in order to obtain the best match among the localizations that are available for your app, pass [NSBundle preferredLocalizationsFromArray:[[NSBundle mainBundle] localizations] forPreferences:[NSLocale preferredLanguages]] instead. The latter choice is normally more appropriate for strings intended for display as part of the app's UI.
 @result		An instance of NSArray containing metadata items of the specified NSArray that match a preferred language, sorted according to the order of preference of the language each matches.
*/
+ (NSArray<AVMetadataItem *> *)metadataItemsFromArray:(NSArray<AVMetadataItem *> *)metadataItems filteredAndSortedAccordingToPreferredLanguages:(NSArray<NSString *> *)preferredLanguages API_AVAILABLE(macos(10.8), ios(6.0), tvos(9.0), watchos(1.0), visionos(1.0));

/*!
	@method			metadataItemsFromArray:filteredByIdentifier:
	@abstract			Filters an array of AVMetadataItems according to identifier.
	@param			metadataItems
	An array of AVMetadataItems to be filtered by identifier.
	@param			identifier
	The identifier that must be matched for a metadata item to be copied to the output array. Items are considered a match not only when their identifiers are equal to the specified identifier, and also when their identifiers conform to the specified identifier.
	@result			An instance of NSArray containing the metadata items of the target NSArray that match the specified identifier.
*/
+ (NSArray<AVMetadataItem *> *)metadataItemsFromArray:(NSArray<AVMetadataItem *> *)metadataItems filteredByIdentifier:(AVMetadataIdentifier)identifier API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/*!
	@method			metadataItemsFromArray:filteredByMetadataItemFilter:
	@abstract		Filters an array of AVMetadataItems using the supplied AVMetadataItemFilter.
	@param			metadataItems
					An array of AVMetadataItems to be filtered.
	@param			metadataItemFilter
					The AVMetadataItemFilter object for filtering the metadataItems.
	@result			An instance of NSArray containing the metadata items of the target NSArray that have not been removed by metadataItemFilter.
*/
+ (NSArray<AVMetadataItem *> *)metadataItemsFromArray:(NSArray<AVMetadataItem *> *)metadataItems filteredByMetadataItemFilter:(AVMetadataItemFilter *)metadataItemFilter API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0));

@end

@interface AVMetadataItem (AVMetadataItemKeyAndKeyspace)

/*!
	@method			identifierForKey:keySpace:
	@abstract		Provides the metadata identifier that's equivalent to a key and keySpace.
	@param			key
					The metadata key.
	@param			keySpace
					The metadata keySpace.
	@result			A metadata identifier equivalent to the given key and keySpace, or nil if no identifier can be constructed from the given key and keySpace.
	@discussion
		Metadata keys that are not instances of NSString, NSNumber, or NSData cannot be converted to metadata identifiers; they also cannot be written to media resources via AVAssetExportSession or AVAssetWriter.  Metadata item keySpaces must be a string of one to four printable ASCII characters.
 
		For custom identifiers, the keySpace AVMetadataKeySpaceQuickTimeMetadata is recommended.  This keySpace defines its key values to be expressed as reverse-DNS strings, which allows third parties to define their own keys in a well established way that avoids collisions.
*/
+ (nullable AVMetadataIdentifier)identifierForKey:(id)key keySpace:(AVMetadataKeySpace)keySpace API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/* provides the metadata keySpace indicated by the identifier  */
+ (nullable AVMetadataKeySpace)keySpaceForIdentifier:(AVMetadataIdentifier)identifier API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/* provides the metadata key indicated by the identifier  */
+ (nullable id)keyForIdentifier:(AVMetadataIdentifier)identifier API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/* indicates the key of the metadata item */
@property (nonatomic, readonly, copy, nullable) id<NSObject, NSCopying> key;

/* indicates the common key of the metadata item */
@property (nonatomic, readonly, copy, nullable) AVMetadataKey commonKey;

/* indicates the keyspace of the metadata item's key; this will typically
 be the default keyspace for the metadata container in which the metadata item is stored */
@property (nonatomic, readonly, copy, nullable) AVMetadataKeySpace keySpace;

@end

/*!
    @class			AVMutableMetadataItem

    @abstract		AVMutableMetadataItem provides support for building collections of metadata to be written
    				to asset files via AVAssetExportSession, AVAssetWriter or AVAssetWriterInput.
    
	@discussion		Can be initialized from an existing AVMetadataItem or with a one or more of the basic properties
					of a metadata item: a key, a keySpace, a locale, and a value.
*/

@class AVMutableMetadataItemInternal;

NS_SWIFT_NONSENDABLE
API_AVAILABLE(macos(10.7), ios(4.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVMutableMetadataItem : AVMetadataItem
{
	AVMutableMetadataItemInternal	*_mutablePriv;
}

/* Indicates the identifier of the metadata item. Publicly defined identifiers are declared in AVMetadataIdentifiers.h.  This property throws an exception if identifier is not of the form \"<keySpace>/<key>\". */
@property (nonatomic, readwrite, copy, nullable) AVMetadataIdentifier identifier API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/* indicates the IETF BCP 47 (RFC 4646) language identifier of the metadata item; may be nil if no language tag information is available */
@property (nonatomic, readwrite, copy, nullable) NSString *extendedLanguageTag API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/* indicates the locale of the metadata item; may be nil if no locale information is available for the metadata item */
@property (nonatomic, readwrite, copy, nullable) NSLocale *locale;

/* indicates the timestamp of the metadata item. */
@property (nonatomic, readwrite) CMTime time;

/* indicates the duration of the metadata item */
@property (nonatomic, readwrite) CMTime duration API_AVAILABLE(macos(10.7), ios(4.2), tvos(9.0), watchos(1.0), visionos(1.0));

/* indicates the data type of the metadata item's value.  Publicly defined data types are declared in <CoreMedia/CMMetadata.h> */
@property (nonatomic, readwrite, copy, nullable) NSString *dataType API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0), watchos(1.0), visionos(1.0));

/* provides the value of the metadata item */
@property (nonatomic, readwrite, copy, nullable) id<NSObject, NSCopying> value;

/* Provides a dictionary of the additional attributes. Extra attributes of metadata items are related to specifics of their carriage in their container format. Keys for extra attributes are declared in AVMetadataFormat.h. */
@property (nonatomic, readwrite, copy, nullable) NSDictionary<AVMetadataExtraAttributeKey, id> *extraAttributes;

/*!
	@method			metadataItem
	@abstract		Returns an instance of AVMutableMetadataItem.
*/
+ (AVMutableMetadataItem *)metadataItem;

@end

@interface AVMutableMetadataItem (AVMutableMetadataItemDateRepresentation)

/* indicates the start date of the timed metadata; nil if no date is indicated */
@property (nonatomic, readwrite, copy, nullable) NSDate *startDate API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

@end

@interface AVMutableMetadataItem (AVMutableMetadataItemKeyAndKeyspace)

/* Indicates the keyspace of the metadata item's key; this will typically be the default keyspace for the metadata container in which the metadata item is stored. */
@property (nonatomic, readwrite, copy, nullable) AVMetadataKeySpace keySpace;

/* Indicates the key of the metadata item. Metadata item keys that are not instances NSString, NSNumber, or NSData cannot be converted to metadata identifiers; they also cannot be written to media resources via AVAssetExportSession or AVAssetWriter. */
@property (nonatomic, readwrite, copy, nullable) id<NSObject, NSCopying> key;

@end

@class AVMetadataItemValueRequest;

@interface AVMetadataItem (AVMetadataItemLazyValueLoading)

/*!
	@method			metadataItemWithPropertiesOfMetadataItem:valueLoadingHandler:
	@abstract		Creates an instance of AVMutableMetadataItem with a value that you do not wish to load unless required, e.g. a large image value that needn't be loaded into memory until another module wants to display it.
	@param			metadataItem
					An instance of AVMetadataItem with the identifier, extendedLanguageTag, and other property values that you want the newly created instance of AVMetadataItem to share. The value of metadataItem is ignored.
	@param			handler
					A block that loads the value of the metadata item.
	@result			An instance of AVMetadataItem.
	@discussion
 		This method is intended for the creation of metadata items for optional display purposes, when there is no immediate need to load specific metadata values. For example, see the interface for navigation markers as consumed by AVPlayerViewController. It's not intended for the creation of metadata items with values that are required immediately, such as metadata items that are provided for impending serialization operations (e.g. via -[AVAssetExportSession setMetadata:] and other similar methods defined on AVAssetWriter and AVAssetWriterInput). 
		When -loadValuesAsynchronouslyForKeys:completionHandler: is invoked on an AVMetadataItem created via +metadataItemWithPropertiesOfMetadataItem:valueLoadingHandler: and @"value" is among the keys for which loading is requested, the block you provide as the value loading handler will be executed on an arbitrary dispatch queue, off the main thread. The handler can perform I/O and other necessary operations to obtain the value. If loading of the value succeeds, provide the value by invoking -[AVMetadataItemValueRequest respondWithValue:]. If loading of the value fails, provide an instance of NSError that describes the failure by invoking -[AVMetadataItemValueRequest respondWithError:].
*/
+ (AVMetadataItem *)metadataItemWithPropertiesOfMetadataItem:(AVMetadataItem *)metadataItem valueLoadingHandler:(void (^ NS_SWIFT_SENDABLE)(AVMetadataItemValueRequest *valueRequest))handler API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0));

@end

@class AVMetadataItemValueRequestInternal;

API_AVAILABLE(macos(10.11), ios(9.0), tvos(9.0), watchos(2.0), visionos(1.0))
@interface AVMetadataItemValueRequest : NSObject {
@private
	AVMetadataItemValueRequestInternal	*_valueRequest;
}

/* Indicates the AVMetadataItem for which a value is being loaded. */
@property (readonly, weak) AVMetadataItem *metadataItem;

/*!
	@method			respondWithValue:
	@abstract		Allows you to respond to an AVMetadataItemValueRequest by providing a value.
	@param			value
					The value of the AVMetadataItem.
*/
- (void)respondWithValue:(id<NSObject, NSCopying>)value;

/*!
	@method			respondWithError:
	@abstract		Allows you to respond to an AVMetadataItemValueRequest in the case of failure.
	@param			error
					An instance of NSError that describes a failure encountered while loading the value of an AVMetadataItem.
*/
- (void)respondWithError:(NSError *)error;

@end

/*!
    @class			AVMetadataItemFilter

    @abstract		AVMetadataItemFilter is a tool used to filter AVMetadataItems.
    
	@discussion		Instances of AVMetadataItemFilter are used to filter AVMetadataItems.  They are opaque, unmodifiable objects, created via AVMetadataItemFilter class methods.
*/

@class AVMetadataItemFilterInternal;

/*!
 @class         AVMetadataItemFilter
 @abstract      Filters selected information from a metadata item.
 @discussion    Subclasses of this type that are used from Swift must fulfill the requirements of a Sendable type.
*/
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0), visionos(1.0))
@interface AVMetadataItemFilter : NSObject {
@private
	AVMetadataItemFilterInternal	*_itemFilterInternal __attribute__((unused));
}

/* Provides an instance of an AVMetadataItemFilter useful for sharing assets.  Removes many user-identifying metadata items, such as location information, leaving only playback-, copyright- and commercial-related metadata (such as the purchaser's Apple ID), along with metadata either derivable from the media itself or necessary for its proper behavior.  */
+ (AVMetadataItemFilter *)metadataItemFilterForSharing;

@end

@interface AVMetadataItem (AVMetadataItemArrayFilteringDeprecable)

/*!
 @method			metadataItemsFromArray:withLocale:
 @discussion		Instead, use metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:.
 */
+ (NSArray<AVMetadataItem *> *)metadataItemsFromArray:(NSArray<AVMetadataItem *> *)metadataItems withLocale:(NSLocale *)locale;

/*!
 @method			metadataItemsFromArray:withKey:keySpace:
 @discussion		Instead, use metadataItemsFromArray:filteredByIdentifier:.
 */
+ (NSArray<AVMetadataItem *> *)metadataItemsFromArray:(NSArray<AVMetadataItem *> *)metadataItems withKey:(nullable id)key keySpace:(nullable AVMetadataKeySpace)keySpace;

@end

/*!
 @category AVMutableMetadataItem (SynchronousMetadataItemInterface)
 @abstract Redeclarations of async-only AVMetadataItem interfaces to allow synchronous usage in the mutable subclass.
 @discussion
	See AVMetadataItem's interface for more information about these interfaces.
 */
@interface AVMutableMetadataItem (SynchronousMetadataItemInterface)

#if __swift__
@property (nonatomic, readonly, nullable) NSString *stringValue;
@property (nonatomic, readonly, nullable) NSNumber *numberValue;
@property (nonatomic, readonly, nullable) NSDate *dateValue;
@property (nonatomic, readonly, nullable) NSData *dataValue;
#endif // __swift__

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCore/AVMetadataItem.h>
#endif

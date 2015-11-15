/*
    File:  AVMetadataItem.h

	Framework:  AVFoundation
 
	Copyright 2010-2015 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMTime.h>
#import <AVFoundation/AVMetadataFormat.h>
#import <AVFoundation/AVAsynchronousKeyValueLoading.h>

#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@class AVMetadataItemFilter;

/*!
    @class			AVMetadataItem

    @abstract		AVMetadataItem represents an item of metadata associated with an audiovisual asset or with
    				one of its tracks.
    
	@discussion		AVMetadataItems have keys that accord with the specification of the container format from
					which they're drawn. Full details of the metadata formats, metadata keys, and metadata keyspaces
					supported by AVFoundation are available among the defines in AVMetadataFormat.h.
	
					Note that arrays of AVMetadataItems vended by AVAsset and other classes are "lazy", similar
					to array-based keys that support key-value observing, meaning that you can obtain
					objects from those arrays without incurring overhead for items you don't ultimately inspect.
					
					You can filter arrays of AVMetadataItems by locale or by key and keySpace via the category
					AVMetadataItemArrayFiltering defined below.
*/

@class AVMetadataItemInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVMetadataItem : NSObject <AVAsynchronousKeyValueLoading, NSCopying, NSMutableCopying>
{
	AVMetadataItemInternal	*_priv;
}

/* Indicates the identifier of the metadata item. Publicly defined identifiers are declared in AVMetadataIdentifiers.h. */
@property (nonatomic, readonly, copy, nullable) NSString *identifier NS_AVAILABLE(10_10, 8_0);

/* indicates the IETF BCP 47 (RFC 4646) language identifier of the metadata item; may be nil if no language tag information is available */
@property (nonatomic, readonly, copy, nullable) NSString *extendedLanguageTag NS_AVAILABLE(10_10, 8_0);

/* indicates the locale of the metadata item; may be nil if no locale information is available for the metadata item */
@property (nonatomic, readonly, copy, nullable) NSLocale *locale;

/* indicates the timestamp of the metadata item. */
@property (nonatomic, readonly) CMTime time;

/* indicates the duration of the metadata item */
@property (nonatomic, readonly) CMTime duration NS_AVAILABLE(10_7, 4_2);

/* indicates the data type of the metadata item's value.  Publicly defined data types are declared in <CoreMedia/CMMetadata.h> */
@property (nonatomic, readonly, copy, nullable) NSString *dataType NS_AVAILABLE(10_10, 8_0);

/* provides the value of the metadata item */
@property (nonatomic, readonly, copy, nullable) id<NSObject, NSCopying> value;

/* provides a dictionary of the additional attributes */
@property (nonatomic, readonly, copy, nullable) NSDictionary<NSString *, id> *extraAttributes;

@end


@interface AVMetadataItem (AVMetadataItemDateRepresentation)

/* indicates the start date of the timed metadata; nil if no date is indicated */
@property (nonatomic, readonly, copy, nullable) NSDate *startDate NS_AVAILABLE(10_11, 9_0);

@end


@interface AVMetadataItem (AVMetadataItemTypeCoercion)

/* provides the value of the metadata item as a string; will be nil if the value cannot be represented as a string */
@property (nonatomic, readonly, nullable) NSString *stringValue;

/* provides the value of the metadata item as an NSNumber. If the metadata item's value can't be coerced to a number, @"numberValue" will be nil. */
@property (nonatomic, readonly, nullable) NSNumber *numberValue;

/* provides the value of the metadata item as an NSDate. If the metadata item's value can't be coerced to a date, @"dateValue" will be nil. */
@property (nonatomic, readonly, nullable) NSDate *dateValue;

/* provides the raw bytes of the value of the metadata item */
@property (nonatomic, readonly, nullable) NSData *dataValue;

@end


@interface AVMetadataItem (AVAsynchronousKeyValueLoading)

/* The following two methods of the AVAsynchronousKeyValueLoading protocol are re-declared here so that they can be annotated with availability information. See AVAsynchronousKeyValueLoading.h for documentation. */

- (AVKeyValueStatus)statusOfValueForKey:(NSString *)key error:(NSError * __nullable * __nullable)outError NS_AVAILABLE(10_7, 4_2);

- (void)loadValuesAsynchronouslyForKeys:(NSArray<NSString *> *)keys completionHandler:(nullable void (^)(void))handler NS_AVAILABLE(10_7, 4_2);

@end


@interface AVMetadataItem (AVMetadataItemArrayFiltering)

/*!
 @method		metadataItemsFromArray:filteredAndSortedAccordingToPreferredLanguages:
 @abstract		Filters an array of AVMetadataItems according to whether their locales match any language identifier in the specified array of preferred languages. The returned array is sorted according to the order of preference of the language each matches.
 @param			metadataItems
				An array of AVMetadataItems to be filtered and sorted.
 @param			preferredLanguages
				An array of language identifiers in order of preference, each of which is an IETF BCP 47 (RFC 4646) language identifier. Use +[NSLocale preferredLanguages] to obtain the user's list of preferred languages.
 @result		An instance of NSArray containing metadata items of the specified NSArray that match a preferred language, sorted according to the order of preference of the language each matches.
*/
+ (NSArray<AVMetadataItem *> *)metadataItemsFromArray:(NSArray<AVMetadataItem *> *)metadataItems filteredAndSortedAccordingToPreferredLanguages:(NSArray<NSString *> *)preferredLanguages NS_AVAILABLE(10_8, 6_0);

/*!
	@method			metadataItemsFromArray:filteredByIdentifier:
	@abstract			Filters an array of AVMetadataItems according to identifier.
	@param			metadataItems
	An array of AVMetadataItems to be filtered by identifier.
	@param			identifier
	The identifier that must be matched for a metadata item to be copied to the output array. Items are considered a match not only when their identifiers are equal to the specified identifier, and also when their identifiers conform to the specified identifier.
	@result			An instance of NSArray containing the metadata items of the target NSArray that match the specified identifier.
*/
+ (NSArray<AVMetadataItem *> *)metadataItemsFromArray:(NSArray<AVMetadataItem *> *)metadataItems filteredByIdentifier:(NSString *)identifier NS_AVAILABLE(10_10, 8_0);

/*!
	@method			metadataItemsFromArray:filteredByMetadataItemFilter:
	@abstract		Filters an array of AVMetadataItems using the supplied AVMetadataItemFilter.
	@param			metadataItems
					An array of AVMetadataItems to be filtered.
	@param			metadataItemFilter
					The AVMetadataItemFilter object for filtering the metadataItems.
	@result			An instance of NSArray containing the metadata items of the target NSArray that have not been removed by metadataItemFilter.
*/
+ (NSArray<AVMetadataItem *> *)metadataItemsFromArray:(NSArray<AVMetadataItem *> *)metadataItems filteredByMetadataItemFilter:(AVMetadataItemFilter *)metadataItemFilter NS_AVAILABLE(10_9, 7_0);

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
+ (nullable NSString *)identifierForKey:(id)key keySpace:(NSString *)keySpace NS_AVAILABLE(10_10, 8_0);

/* provides the metadata keySpace indicated by the identifier  */
+ (nullable NSString *)keySpaceForIdentifier:(NSString *)identifier NS_AVAILABLE(10_10, 8_0);

/* provides the metadata key indicated by the identifier  */
+ (nullable id)keyForIdentifier:(NSString *)identifier NS_AVAILABLE(10_10, 8_0);

/* indicates the key of the metadata item */
@property (nonatomic, readonly, copy, nullable) id<NSObject, NSCopying> key;

/* indicates the common key of the metadata item */
@property (nonatomic, readonly, copy, nullable) NSString *commonKey;

/* indicates the keyspace of the metadata item's key; this will typically
 be the default keyspace for the metadata container in which the metadata item is stored */
@property (nonatomic, readonly, copy, nullable) NSString *keySpace;

@end

/*!
    @class			AVMutableMetadataItem

    @abstract		AVMutableMetadataItem provides support for building collections of metadata to be written
    				to asset files via AVAssetExportSession, AVAssetWriter or AVAssetWriterInput.
    
	@discussion		Can be initialized from an existing AVMetadataItem or with a one or more of the basic properties
					of a metadata item: a key, a keySpace, a locale, and a value.
*/

@class AVMutableMetadataItemInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVMutableMetadataItem : AVMetadataItem
{
	AVMutableMetadataItemInternal	*_mutablePriv;
}

/* Indicates the identifier of the metadata item. Publicly defined identifiers are declared in AVMetadataIdentifiers.h. */
@property (nonatomic, readwrite, copy, nullable) NSString *identifier NS_AVAILABLE(10_10, 8_0);

/* indicates the IETF BCP 47 (RFC 4646) language identifier of the metadata item; may be nil if no language tag information is available */
@property (nonatomic, readwrite, copy, nullable) NSString *extendedLanguageTag NS_AVAILABLE(10_10, 8_0);

/* indicates the locale of the metadata item; may be nil if no locale information is available for the metadata item */
@property (nonatomic, readwrite, copy, nullable) NSLocale *locale;

/* indicates the timestamp of the metadata item. */
@property (nonatomic, readwrite) CMTime time;

/* indicates the duration of the metadata item */
@property (nonatomic, readwrite) CMTime duration NS_AVAILABLE(10_7, 4_2);

/* indicates the data type of the metadata item's value.  Publicly defined data types are declared in <CoreMedia/CMMetadata.h> */
@property (nonatomic, readwrite, copy, nullable) NSString *dataType NS_AVAILABLE(10_10, 8_0);

/* provides the value of the metadata item */
@property (nonatomic, readwrite, copy, nullable) id<NSObject, NSCopying> value;

/* Provides a dictionary of the additional attributes. Extra attributes of metadata items are related to specifics of their carriage in their container format. Keys for extra attributes are declared in AVMetadataFormat.h. */
@property (nonatomic, readwrite, copy, nullable) NSDictionary<NSString *, id> *extraAttributes;

/*!
	@method			metadataItem
	@abstract		Returns an instance of AVMutableMetadataItem.
*/
+ (AVMutableMetadataItem *)metadataItem;

@end

@interface AVMutableMetadataItem (AVMutableMetadataItemDateRepresentation)

/* indicates the start date of the timed metadata; nil if no date is indicated */
@property (nonatomic, readwrite, copy, nullable) NSDate *startDate NS_AVAILABLE(10_11, 9_0);

@end

@interface AVMutableMetadataItem (AVMutableMetadataItemKeyAndKeyspace)

/* Indicates the keyspace of the metadata item's key; this will typically be the default keyspace for the metadata container in which the metadata item is stored. */
@property (nonatomic, readwrite, copy, nullable) NSString *keySpace;

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
+ (AVMetadataItem *)metadataItemWithPropertiesOfMetadataItem:(AVMetadataItem *)metadataItem valueLoadingHandler:(void (^)(AVMetadataItemValueRequest *valueRequest))handler NS_AVAILABLE(10_11, 9_0);

@end

@class AVMetadataItemValueRequestInternal;

NS_CLASS_AVAILABLE(10_11, 9_0)
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

NS_CLASS_AVAILABLE(10_9, 7_0)
@interface AVMetadataItemFilter : NSObject {
@private
	AVMetadataItemFilterInternal	*_itemFilterInternal;
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
+ (NSArray<AVMetadataItem *> *)metadataItemsFromArray:(NSArray<AVMetadataItem *> *)metadataItems withKey:(nullable id)key keySpace:(nullable NSString *)keySpace;

@end

NS_ASSUME_NONNULL_END

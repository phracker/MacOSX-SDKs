/*
	NSPasteboardItem.h
	Application Kit
	Copyright (c) 2008-2024, Apple Inc.
	All rights reserved.
*/


#import <Foundation/NSArray.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSPasteboard.h>
#import <CoreFoundation/CFBase.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@class NSPasteboard;
@protocol NSPasteboardItemDataProvider;

/* An NSPasteboard can contain multiple items.  Any object that implements the NSPasteboardWriting and NSPasteboardReading protocols can be written and read on the pasteboard directly.  This allows common pasteboard classes such as URLs, colors, images, strings, attributed strings, and sounds to be written and read without an intermediary object.  The custom classes of an application can also implement these protocols for use with the pasteboard.

Sometimes, however, an application needs more fine-grained access to the types and data of a particular pasteboard item, or in the case of a delegate or subclass, needs a way to inspect and change what has already been put on the pasteboard.  In these cases, it is appropriate to use pasteboard items.

There are three main uses for an NSPasteboardItem:
    1. Providing data on the pasteboard: create one or more pasteboard items, set data or data providers for types, and write to the pasteboard
    2. Customizing data already on the pasteboard: as a delegate or subclass, retrieve the pasteboard items currently on the pasteboard, Read the existing types and data and set new data and data providers for types as needed.
    3. Retrieving data from the pasteboard: Retrieve the pasteboard items from the pasteboard.  Read the data for types.

A pasteboard item can be associated with a single pasteboard.  When you create a pasteboard item, it can be written to any pasteboard.  When you pass in a pasteboard item to -writeObjects:, that pasteboard item becomes bound to the pasteboard it was written to.  When you retrieve pasteboard items using -pasteboardItems or -readObjectsForClasses:options:, the returned pasteboard items are associated with the messaged pasteboard.  Passing a pasteboard item that is aready associated with a pasteboard into -writeObjects: causes an exception to be raised.

Pasteboard items are intended to be used during a single pasteboard interaction, not held onto and used repeatedly.  A pasteboard item is only valid until the owner of the pasteboard changes.  If a pasteboard item is stale because the pasteboard owner has changed, it will return nil or NO values from its methods.

The pasteboard item API is very similar to the NSPasteboard API for a single item.  One important difference is that NSPasteboardItem expects strings which are valid UTI strings.  If a type is specified that is not a valid UTI string, the method call will fail.  Similarly, all reported types are UTIs.  As of 10.6, NSPasteboard.h declares a number of NSPasteboardType constants which can be used to provide the correct UTI for common pasteboard types.

*/

API_AVAILABLE(macos(10.6))
@interface NSPasteboardItem : NSObject <NSPasteboardWriting, NSPasteboardReading>
/* Returns an array of UTI strings of the data types supported by the receiver.
*/
@property (readonly, copy) NSArray<NSPasteboardType> *types;

/* Given an array of types, will return the first type contained in the pasteboard item, according to the sender's ordering of types.  It will check for UTI conformance of the requested types, preferring an exact match to conformance.
*/
- (nullable NSPasteboardType)availableTypeFromArray:(NSArray<NSPasteboardType> *)types;

/* Promises the types and registers the data provider to be messaged to provide the data for that type when requested.
*/
- (BOOL)setDataProvider:(id<NSPasteboardItemDataProvider>)dataProvider forTypes:(NSArray<NSPasteboardType> *)types;

/* Sets a value for the provided UTI type string.
*/
- (BOOL)setData:(NSData *)data forType:(NSPasteboardType)type;
- (BOOL)setString:(NSString *)string forType:(NSPasteboardType)type;
- (BOOL)setPropertyList:(id)propertyList forType:(NSPasteboardType)type;

/* Returns a value for the provided UTI type string.
*/
- (nullable NSData *)dataForType:(NSPasteboardType)type;
- (nullable NSString *)stringForType:(NSPasteboardType)type;
- (nullable id)propertyListForType:(NSPasteboardType)type;


/* Detection / Metadata */

/// Determines whether this pasteboard item matches the specified patterns, without notifying the person using the app.
///
/// This method only gives an indication of whether a pasteboard item matches a particular pattern and doesn’t allow the app to access the item's contents. As a result, the system doesn’t notify the person using the app about reading the contents of the pasteboard.
///
/// The following example shows how to use this method to find email and postal addresses in each item on the pasteboard:
///
/// ```obj-c
/// NSArray<NSPasteboardItem*> *items = NSPasteboard.generalPasteboard.pasteboardItems;
/// __block NSUInteger idx = 0;
/// for (NSPasteboardItem *item in items) {
///     NSUInteger itemIndex = idx++;
///     [item
///      detectPatternsForPatterns:[NSSet setWithArray:@[NSPasteboardDetectionPatternEmailAddress,
///                                                      NSPasteboardDetectionPatternPostalAddress]]
///      completionHandler:^(NSSet<NSPasteboardDetectionPattern> *matchedPatterns, NSError *error) {
///         if (error) {
///             NSLog(@"Item %lu: Error: %@", itemIndex, error);
///             return;
///         }
///         BOOL matchedEmail = [matchedPatterns containsObject:NSPasteboardDetectionPatternEmailAddress];
///         BOOL matchedPostal = [matchedPatterns containsObject: NSPasteboardDetectionPatternPostalAddress];
///         if (matchedEmail) {
///             NSLog(@"Item %lu - Email address(es) detected", itemIndex);
///         }
///         if (matchedPostal) {
///             NSLog(@"Item %lu - Postal address(es) detected", itemIndex);
///         }
///         if (!matchedEmail && !matchedPostal) {
///             NSLog(@"Item %lu - Matched neither email nor postal addresses.", itemIndex);
///         }
///     }];
/// }
/// ```
///
/// - Parameters:
///   - patterns: The patterns to detect on the pasteboard item.
///   - completionHandler: A block that the system invokes after detecting patterns on the pasteboard item. The block receives either a set with the patterns the system finds on the pasteboard item or an error if detection fails.
- (void)detectPatternsForPatterns:(NSSet<NSPasteboardDetectionPattern> *)patterns
                completionHandler:(void(^)(NSSet<NSPasteboardDetectionPattern> * _Nullable detectedPatterns,
                                           NSError * _Nullable error))completionHandler NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.4));

/// Determines whether this pasteboard item matches the specified patterns, reading the contents if it finds a match.
/// 
/// For details about the types returned for each pattern, see ``NSPasteboardDetectionPattern``.
///
/// The following example shows how to use this method to find web URLs and web search terms in each item on the pasteboard:
///
/// ```obj-c
/// NSArray<NSPasteboardItem*> *items = NSPasteboard.generalPasteboard.pasteboardItems;
/// __block NSUInteger idx = 0;
/// for (NSPasteboardItem *item in items) {
///     NSUInteger itemIndex = idx++;
///     [item
///      detectValuesForPatterns:[NSSet setWithArray:@[NSPasteboardDetectionPatternProbableWebSearch,
///                                                    NSPasteboardDetectionPatternProbableWebURL]]
///      completionHandler:^(NSDictionary<NSPasteboardDetectionPattern, id> *patternValues, NSError *error) {
///         if (error) {
///             NSLog(@"Item %lu: Error: %@", itemIndex, error);
///             return;
///         }
///         NSString *searchString = (NSString*)patternValues[NSPasteboardDetectionPatternProbableWebSearch];
///         NSString *urlString = (NSString*)patternValues[NSPasteboardDetectionPatternProbableWebURL] ;
///         if (searchString != nil) {
///             NSLog(@"Item %lu - Web search retrieved: %@", itemIndex, searchString);
///         }
///         if (urlString != nil) {
///             NSLog(@"Item %lu - Web URL retrieved: %@", itemIndex, urlString);
///         }
///         if (searchString == nil && urlString == nil) {
///             NSLog(@"Item %lu - No web patterns retrieved.", itemIndex);
///         }
///     }];
/// }
/// ```
///
///  > Important: If the system finds a match when calling this method, the system informs the person using the app that the app is trying to read the contents of the pasteboard. If the person denies access to the pasteboard, the completion handler receives an error.
///
/// - Parameters:
///   - patterns: The patterns to detect on the pasteboard item.
///   - completionHandler: A block the system invokes after detecting patterns on the pasteboard item. The block returns either a dictionary with the patterns the system finds on the pasteboard item or an error if detection fails. The dictionary keys specify the matched patterns, and the values specify the corresponding content of the pasteboard.
- (void)detectValuesForPatterns:(NSSet<NSPasteboardDetectionPattern> *)patterns
              completionHandler:(void(^)(NSDictionary<NSPasteboardDetectionPattern, id> * _Nullable detectedValues,
                                         NSError * _Nullable error))completionHandler NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.4));

/// Determines available metadata from the specified metadata types for this pasteboard item, without notifying the person using the app.
///
/// This method only gives access to limited types of metadata and doesn’t allow the app to access the contents. As a result, the system doesn’t notify the person using the app about reading the contents of the pasteboard.
///
/// For details about the metadata returned for each type, see ``NSPasteboardMetadataType``.
///
/// The following example shows how to iterate over each pasteboard item and, if the item is a URL that points to a file, get its content type with this method:
///
/// ```obj-c
/// NSArray<NSPasteboardItem*> *items = NSPasteboard.generalPasteboard.pasteboardItems;
/// __block NSUInteger idx = 0;
/// for (NSPasteboardItem *item in items) {
///     NSUInteger itemIndex = idx++;
///     [item
///      detectMetadataForTypes:[NSSet setWithArray:@[NSPasteboardMetadataTypeContentType]]
///      completionHandler:^(NSDictionary<NSPasteboardMetadataType, id> *metadata, NSError *error) {
///         if (error) {
///             NSLog(@"Item %lu - Error: %@", itemIndex, error);
///             return;
///         }
///         UTType *contentType = (UTType*)metadata[NSPasteboardMetadataTypeContentType];
///         if (contentType) {
///             NSLog(@"Item %lu - Content type is: %@", itemIndex, contentType.identifier);
///         } else {
///             NSLog(@"Item %lu - Couldn't get content type", itemIndex);
///         }
///     }];
/// }
/// ```
///
/// - Parameters:
///   - types: The metadata types to detect on the pasteboard item.
///   - completionHandler: A block the system invokes after detecting metadata on the pasteboard item. The block receives either a dictionary with the metadata types the system finds on the pasteboard item or an error if detection fails. The dictionary keys specify the matched metadata types, and the values specify the corresponding metadata.
- (void)detectMetadataForTypes:(NSSet<NSPasteboardMetadataType> *)types
             completionHandler:(void(^)(NSDictionary<NSPasteboardMetadataType, id> * _Nullable detectedMetadata,
                                        NSError * _Nullable error))completionHandler NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.4));

@end



@protocol NSPasteboardItemDataProvider <NSObject>
/* Implemented by the data provider of a pasteboard item, to provide the data for a particular UTI type.
*/
@required
- (void)pasteboard:(nullable NSPasteboard *)pasteboard item:(NSPasteboardItem *)item provideDataForType:(NSPasteboardType)type NS_SWIFT_NONISOLATED;

/* One data provider can provide data for more than one pasteboard item.  This method is called when the pasteboard no longer needs the data provider for any of its pasteboard items.  This can be either because the data provider has fulfilled all promises, or because ownership of the pasteboard has changed.
*/
@optional
- (void)pasteboardFinishedWithDataProvider:(NSPasteboard *)pasteboard NS_SWIFT_NONISOLATED;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)


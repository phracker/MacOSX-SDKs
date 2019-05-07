/*
	NSPasteboard.h
	Application Kit
	Copyright (c) 1994-2018, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSString.h>
#import <Foundation/NSURL.h>
#import <CoreFoundation/CFBase.h>

NS_ASSUME_NONNULL_BEGIN

@class NSData, NSFileWrapper, NSMutableDictionary, NSPasteboard;
@protocol NSPasteboardWriting;
/* Standard Pasteboard Types */

typedef NSString * NSPasteboardType NS_TYPED_EXTENSIBLE_ENUM;
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeString	 		NS_AVAILABLE_MAC(10_6); // Replaces NSStringPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypePDF			NS_AVAILABLE_MAC(10_6); // Replaces NSPDFPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeTIFF	 		NS_AVAILABLE_MAC(10_6); // Replaces NSTIFFPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypePNG	 		NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeRTF	 		NS_AVAILABLE_MAC(10_6); // Replaces NSRTFPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeRTFD	 		NS_AVAILABLE_MAC(10_6); // Replaces NSRTFDPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeHTML	 		NS_AVAILABLE_MAC(10_6); // Replaces NSHTMLPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeTabularText 		NS_AVAILABLE_MAC(10_6); // Replaces NSTabularTextPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeFont 			NS_AVAILABLE_MAC(10_6); // Replaces NSFontPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeRuler 			NS_AVAILABLE_MAC(10_6); // Replaces NSRulerPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeColor 			NS_AVAILABLE_MAC(10_6); // Replaces NSColorPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeSound 			NS_AVAILABLE_MAC(10_6); // Replaces NSSoundPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeMultipleTextSelection 	NS_AVAILABLE_MAC(10_6); // Replaces NSMultipleTextSelectionPboardType
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeTextFinderOptions		NS_AVAILABLE_MAC(10_7); // Replaces NSPasteboardTypeFindPanelSearchOptions
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeURL                        NS_AVAILABLE_MAC(10_13); // Equivalent to kUTTypeURL
APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeFileURL                    NS_AVAILABLE_MAC(10_13); // Equivalent to kUTTypeFileURL


/* Standard Pasteboard Names */

typedef NSString * NSPasteboardName NS_TYPED_EXTENSIBLE_ENUM;
APPKIT_EXTERN NSPasteboardName NSPasteboardNameGeneral NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSPasteboardName NSPasteboardNameFont NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSPasteboardName NSPasteboardNameRuler NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSPasteboardName NSPasteboardNameFind NS_AVAILABLE_MAC(10_13);
APPKIT_EXTERN NSPasteboardName NSPasteboardNameDrag NS_AVAILABLE_MAC(10_13);

/* Options for prepareForNewContentsWithOptions: */

typedef NS_OPTIONS(NSUInteger, NSPasteboardContentsOptions) {
    NSPasteboardContentsCurrentHostOnly = 1 << 0, // Specifies that the pasteboard contents should not be available to other devices
} NS_ENUM_AVAILABLE_MAC(10_12);


/* Pasteboard Reading Options
 These options can be used for both the -readObjectsForClasses:options: and -canReadObjectForClasses:options: methods, unless otherwise specified.  The currently available options allow for customization of how NSURLs are read from the pasteboard.
 */
typedef NSString * NSPasteboardReadingOptionKey NS_TYPED_ENUM;
/* Option for reading NSURLs to restrict the results to file URLs only.  The value for this key is an NSNumber with a boolean value.
 */
APPKIT_EXTERN NSPasteboardReadingOptionKey const NSPasteboardURLReadingFileURLsOnlyKey NS_AVAILABLE_MAC(10_6);
/* Option for reading NSURLs to restrict the results to URLs with contents that conform to any of the provided UTI types.  If the content type of a URL cannot be determined, it will not be considered to match.  The value for this key is an array of UTI type strings.
 */
APPKIT_EXTERN NSPasteboardReadingOptionKey const NSPasteboardURLReadingContentsConformToTypesKey NS_AVAILABLE_MAC(10_6);


/* An NSPasteboard can contain multiple items.  Any object that implements the NSPasteboardWriting and NSPasteboardReading protocols can be written and read on the pasteboard directly.  This allows common pasteboard classes such as URLs, colors, images, strings, attributed strings, and sounds to be written and read without an intermediary object.  The custom classes of an application can also implement these protocols for use with the pasteboard.
*/

@class NSPasteboardItem;

@interface NSPasteboard : NSObject
{
    @private
    id			_pboard APPKIT_IVAR;
    int			_gen APPKIT_IVAR;
    id			_owners APPKIT_IVAR;
    CFIndex		_cachedTypeNameChangeCount APPKIT_IVAR;
    id			_cachedTypeNames APPKIT_IVAR;
    NSMutableDictionary *_promiseTypeNamesByIdentifier APPKIT_IVAR;
    id			_support APPKIT_IVAR;	
    id			_pasteboardItems APPKIT_IVAR;
    void *		_reserved[3] __unused APPKIT_IVAR;
}

@property (class, readonly, strong) NSPasteboard *generalPasteboard;
+ (NSPasteboard *)pasteboardWithName:(NSPasteboardName)name;
+ (NSPasteboard *)pasteboardWithUniqueName;

@property (readonly, copy) NSPasteboardName name;

@property (readonly) NSInteger changeCount;

- (oneway void)releaseGlobally;

/* Prepares the pasteboard for new contents, clearing the existing contents of the pasteboard. This is the first step in providing data on the pasteboard. Any options specified will persist until prepareForNewContentsWithOptions: or clearContents is called. Returns the change count of the pasteboard.
 */
- (NSInteger)prepareForNewContentsWithOptions:(NSPasteboardContentsOptions)options NS_AVAILABLE_MAC(10_12);

/* Prepares the pasteboard for new contents, clearing the existing contents of the pasteboard.  This is equivalent to calling prepareForNewContentsWithOptions: with no options.  Returns the change count of the pasteboard.
*/
- (NSInteger)clearContents NS_AVAILABLE_MAC(10_6);


/* Writes the data of an array of objects that implement the NSPasteboardWriting protocol (including NSPasteboardItem instances).  Returns NO if the items were not successfully added to the pasteboard.
*/
- (BOOL)writeObjects:(NSArray<id<NSPasteboardWriting>> *)objects NS_AVAILABLE_MAC(10_6);


/* Classes in the provided array must implement the NSPasteboardReading protocol.  Cocoa classes that implement this protocol include NSImage, NSString, NSURL, NSColor, NSAttributedString, and NSPasteboardItem.  For every item on the pasteboard, each class in the provided array will be queried for the types it can read using -readableTypesForPasteboard:.  An instance will be created of the first class found in the provided array whose readable types match a conforming type contained in that pasteboard item.  Any instances that could be created from pasteboard item data is returned to the caller.  Additional options, such as restricting the search to file URLs with particular content types, can be specified with an options dictionary.  See the comments for the option keys for a full description.  Returns nil if there is an error in retrieving the requested items from the pasteboard or if no objects of the specified types can be created.

Example: there are five items on the pasteboard, two contain TIFF data, two contain RTF data, one contains a private data type.  Calling -readObjectsForClasses: with just the NSImage class, will return an array containing two image objects.  Calling with just the NSAttributedString class, will return an array containing two attributed strings.  Calling with both classes will return two image objects and two attributed strings.  Note that in the above examples, the count of objects returned is less than the number of items on the pasteboard.  Only objects of the requested classes are returned.  You can always ensure to receive one object per item on the pasteboard by including the NSPasteboardItem class in the array of classes.  In this example, an array containing the NSImage, NSAttributedString, and NSSPasteboardItem classes will return an array with two images, two attributed strings, and one pasteboard item containing the private data type.
*/
- (nullable NSArray *)readObjectsForClasses:(NSArray<Class> *)classArray options:(nullable NSDictionary<NSPasteboardReadingOptionKey, id> *)options NS_AVAILABLE_MAC(10_6);


/* Returns all pasteboard items.  Returns nil if there is an error retrieving pasteboard items.
*/
@property (nullable, readonly, copy) NSArray<NSPasteboardItem *> *pasteboardItems NS_AVAILABLE_MAC(10_6);


/* The index of the provided pasteboard item in the pasteboard.  If the pasteboard item has not been added to any pasteboard, or is owned by another pasteboard, returns the value NSNotFound.  An item's index in the pasteboard is useful for a pasteboard item data provider that has promised data for multiple items, to be able to easily match the pasteboard item to an array of source data from which to derive the promised data.
*/
- (NSUInteger)indexOfPasteboardItem:(NSPasteboardItem *)pasteboardItem NS_AVAILABLE_MAC(10_6);


/* Method to validate whether the pasteboard contains at least one item that conforms to the specified UTIs.
*/
- (BOOL)canReadItemWithDataConformingToTypes:(NSArray<NSString *> *)types NS_AVAILABLE_MAC(10_6);


/* Method to validate whether at least one instance of any of the provided classes can be created with data on the pasteboard.  Classes in the provided array must implement the NSPasteboardReading protocol.  Additional options, such as restricting the search to file URLs, or URLs particular content types, can be specified with an options dictionary.  See the comments for the reading option keys for a full description.
*/
- (BOOL)canReadObjectForClasses:(NSArray<Class> *)classArray options:(nullable NSDictionary<NSPasteboardReadingOptionKey, id> *)options NS_AVAILABLE_MAC(10_6);


/* The following methods all operate on what is conceptually the first item on the pasteboard.  They accept UTIs and pboard type strings.  In a future release they may take only UTIs.
*/

/* This method is the equivalent of calling -clearContents, implicitly writing the first pasteboard item, and then calling -addTypes:owner: to promise types for the first pasteboard item.  In general, this method should not be used with -writeObjects: since -writeObjects: will always write additional items to the pasteboard, and will not affect items already on the pasteboard, including the item implicitly created by this method.
*/
- (NSInteger)declareTypes:(NSArray<NSPasteboardType> *)newTypes owner:(nullable id)newOwner;

/* This method adds promises for the specified types to the first pasteboard item.  If the data for those types is provided immediately, the owner can be nil.  If the data for the added types will be provided lazily when requested from the pasteboard, an owner object must be provided that implements the -pasteboard:provideDataForType: method of the NSPasteboardOwner informal protocol.
*/
- (NSInteger)addTypes:(NSArray<NSPasteboardType> *)newTypes owner:(nullable id)newOwner;

/* These methods provide information about the types available from the entire pasteboard.
*/
@property (nullable, readonly, copy) NSArray<NSPasteboardType> *types;
- (nullable NSPasteboardType)availableTypeFromArray:(NSArray<NSPasteboardType> *)types;

/* These methods set data for the specified type on the first pasteboard item.
*/
- (BOOL)setData:(nullable NSData *)data forType:(NSPasteboardType)dataType;
- (BOOL)setPropertyList:(id)plist forType:(NSPasteboardType)dataType;
- (BOOL)setString:(NSString *)string forType:(NSPasteboardType)dataType;

/* These methods return a best representation of all items on the pasteboard for the requested type.  For almost all data types, this simply means returning the data for the first item on the pasteboard that contains that type.  For standard text data types such as string, RTF, and RTFD, the text data from each item will be returned as one combined result separated by newlines.
*/
- (nullable NSData *)dataForType:(NSPasteboardType)dataType;
- (nullable id)propertyListForType:(NSPasteboardType)dataType;
- (nullable NSString *)stringForType:(NSPasteboardType)dataType;


@end


@interface NSPasteboard(FilterServices)
+ (NSArray<NSPasteboardType> *)typesFilterableTo:(NSPasteboardType)type;

+ (NSPasteboard *)pasteboardByFilteringFile:(NSString *)filename;
+ (NSPasteboard *)pasteboardByFilteringData:(NSData *)data ofType:(NSPasteboardType)type;
+ (NSPasteboard *)pasteboardByFilteringTypesInPasteboard:(NSPasteboard *)pboard;
@end


@protocol NSPasteboardTypeOwner <NSObject>
- (void)pasteboard:(NSPasteboard *)sender provideDataForType:(NSPasteboardType)type;
@optional
- (void)pasteboardChangedOwner:(NSPasteboard *)sender;
@end

#if __swift__ < 40200
@interface NSObject(NSPasteboardOwner)
- (void)pasteboard:(NSPasteboard *)sender provideDataForType:(NSPasteboardType)type NS_DEPRECATED_MAC(10_0, API_TO_BE_DEPRECATED, "This is now a method of the NSPasteboardTypeOwner protocol.");
- (void)pasteboardChangedOwner:(NSPasteboard *)sender NS_DEPRECATED_MAC(10_0, API_TO_BE_DEPRECATED, "This is now an optional method of the NSPasteboardTypeOwner protocol.");
@end
#endif


/*** NSPasteboardWriting and NSPasteboardReading Protocols ***/


/* The NSPasteboardWriting protocol enables instances of a class to be used with the -writeObjects: method of NSPasteboard.  The Cocoa framework classes NSString, NSAttributedString, NSURL, NSColor, NSSound, NSImage, and NSPasteboardItem implement this protocol.  The protocol can also be implemented by custom application classes for use with -writeObjects:
 */
typedef NS_OPTIONS(NSUInteger, NSPasteboardWritingOptions) {
    NSPasteboardWritingPromised = 1 << 9, // Data for a type with this option will be promised, not immediately written
} NS_ENUM_AVAILABLE_MAC(10_6);


@protocol NSPasteboardWriting <NSObject>

@required
/* Returns an array of UTI strings of data types the receiver can write to the pasteboard.  By default, data for the first returned type is put onto the pasteboard immediately, with the remaining types being promised.  To change the default behavior, implement -writingOptionsForType:pasteboard: and return NSPasteboardWritingPromised to lazily provided data for types, return no option to provide the data for that type immediately.  Use the pasteboard argument to provide different types based on the pasteboard name, if desired.  Do not perform other pasteboard operations in the method implementation.
 */
- (NSArray<NSPasteboardType> *)writableTypesForPasteboard:(NSPasteboard *)pasteboard;


@optional
/* Returns options for writing data of a type to a pasteboard.  Use the pasteboard argument to provide different options based on the pasteboard name, if desired.  Do not perform other pasteboard operations in the method implementation.
 */
- (NSPasteboardWritingOptions)writingOptionsForType:(NSPasteboardType)type pasteboard:(NSPasteboard *)pasteboard;


@required
/* Returns the appropriate property list object for the provided type.  This will commonly be the NSData for that data type.  However, if this method returns either a string, or any other property-list type, the pasteboard will automatically convert these items to the correct NSData format required for the pasteboard.
 */
- (nullable id)pasteboardPropertyListForType:(NSPasteboardType)type;

@end



/* The NSPasteboardReading protocol enables instances of a class to be created from pasteboard data by using the -readObjectsForClasses:options: method of NSPasteboard.  The Cocoa framework classes NSString, NSAttributedString, NSURL, NSColor, NSSound, NSImage, and NSPasteboardItem implement this protocol.  The protocol can also be implemented by custom application classes for use with -readObjectsForClasses:options:
 */


/*  NSPasteboardReadingOptions specify how data is read from the pasteboard.  You can specify only one option from this list.  If you do not specify an option, the default NSPasteboardReadingAsData is used.  The first three options specify how and if pasteboard data should be pre-processed by the pasteboard before being passed to -initWithPasteboardPropertyList:ofType.  The fourth option, NSPasteboardReadingAsKeyedArchive, should be used when the data on the pasteboard is a keyed archive of this class.  Using this option, a keyed unarchiver will be used and -initWithCoder: will be called to initialize the new instance.
 */
typedef NS_OPTIONS(NSUInteger, NSPasteboardReadingOptions) {
    NSPasteboardReadingAsData           = 0,	  // Reads data from the pasteboard as-is and returns it as an NSData
    NSPasteboardReadingAsString         = 1 << 0, // Reads data from the pasteboard and converts it to an NSString
    NSPasteboardReadingAsPropertyList   = 1 << 1, // Reads data from the pasteboard and un-serializes it as a property list
    NSPasteboardReadingAsKeyedArchive   = 1 << 2, // Reads data from the pasteboard and uses initWithCoder: to create the object
} NS_ENUM_AVAILABLE_MAC(10_6);


@protocol NSPasteboardReading <NSObject>

/* Returns an array of data types as UTI strings that the receiver can read from the pasteboard and be initialized from.  By default, the NSData for the type is provided to -initWithPasteboardPropertyList:ofType:.  By implementing -readingOptionsForType:pasteboard: and specifying a different option, the NSData for that type can be automatically converted to an NSString or property list object before being passed to -readingOptionsForType:pasteboard:.  Use the pasteboard argument to provide different types based on the pasteboard name, if desired.  Do not perform other pasteboard operations in the method implementation.
 */
@required
+ (NSArray<NSPasteboardType> *)readableTypesForPasteboard:(NSPasteboard *)pasteboard;


@optional
/* Returns options for reading data of a type from a pasteboard.  Use the pasteboard argument to provide different options based on the pasteboard name, if desired.  Do not perform other pasteboard operations in the method implementation.
 */
+ (NSPasteboardReadingOptions)readingOptionsForType:(NSPasteboardType)type pasteboard:(NSPasteboard *)pasteboard;


/* Initializes an instance with a property list object and a type string.  By default, the property list object is the NSData for that type on the pasteboard.  By specifying an NSPasteboardReading option for a type, the data on the pasteboard can be retrieved and automatically converted to a string or property list instead.  This method is considered optional because if there is a single type returned from +readableTypesForPasteboard, and that type uses the NSPasteboardReadingAsKeyedArchive reading option, then initWithCoder: will be called to initialize a new instance from the keyed archive.
 */
@optional
- (nullable id)initWithPasteboardPropertyList:(id)propertyList ofType:(NSPasteboardType)type;

@end

/*** NSURL Pasteboard Support ***/

/* The recommended approach for writing URLs to the pasteboard is as follows:

    NSArray *arrayOfURLs; // assume this exists
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard]; // get pasteboard
    [pasteboard clearContents]; // clear pasteboard to take ownership
    [pasteboard writeObjects:arrayOfURLs]; // write the URLs
    
    The recommended approach for reading URLs is as follows:
    
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard]; // get pasteboard
    NSArray *classArray = [NSArray arrayWithObject:[NSURL class]]; // types of objects you are looking for
    NSArray *arrayOfURLs = [pasteboard readObjectsForClasses:classArray options:nil]; // read objects of those classes
    
    To read only file URLs, use the NSPasteboardURLReadingFileURLsOnlyKey option in a dictionary provided to -readObjectsForClasses:options:.
    NSDictionary *options = [NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES] forKey:NSPasteboardURLReadingFileURLsOnlyKey];
    
    To read only URLs with particular content types, use the NSPasteboardURLReadingContentsConformToTypesKey option in a dictionary provided to -readObjectsForClasses:options:.  In the sample below, only URLs whose content types are images will be returned.
    NSDictionary *options = [NSDictionary dictionaryWithObject:[NSImage imageTypes] forKey:NSPasteboardURLReadingContentsConformToTypesKey];
    
    To read only file URLs with particular content types, combine the two options.

*/

@interface NSURL(NSPasteboardSupport) <NSPasteboardWriting, NSPasteboardReading>
+ (nullable NSURL *)URLFromPasteboard:(NSPasteboard *)pasteBoard;
- (void)writeToPasteboard:(NSPasteboard *)pasteBoard;
@end


/*** NSString Pasteboard Support ***/

@interface NSString(NSPasteboardSupport) <NSPasteboardWriting, NSPasteboardReading>
@end


/*** File Contents ***/

/* The file contents pboard type allowed you to synthesize a pboard type for a file's contents based on the file's extension.  Using the UTI of a file to represent its contents now replaces this functionality.*/

@interface NSPasteboard(NSFileContents)
- (BOOL)writeFileContents:(NSString *)filename;
- (nullable NSString *)readFileContentsType:(nullable NSPasteboardType)type toFile:(NSString *)filename;

- (BOOL)writeFileWrapper:(NSFileWrapper *)wrapper;
- (nullable NSFileWrapper *)readFileWrapper;

@end

APPKIT_EXTERN NSPasteboardType NSFileContentsPboardType;

APPKIT_EXTERN NSPasteboardType __nullable NSCreateFilenamePboardType(NSString *fileType);
APPKIT_EXTERN NSPasteboardType __nullable NSCreateFileContentsPboardType(NSString *fileType);
APPKIT_EXTERN NSString * __nullable NSGetFileType(NSPasteboardType pboardType);
APPKIT_EXTERN NSArray<NSString *> * __nullable NSGetFileTypes(NSArray<NSPasteboardType> *pboardTypes);


/*** Deprecated ***/

APPKIT_EXTERN NSPasteboardType NSStringPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypeString", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSFilenamesPboardType NS_DEPRECATED_MAC(10_0, 10_14, "Create multiple pasteboard items with NSPasteboardTypeFileURL or kUTTypeFileURL instead");
APPKIT_EXTERN NSPasteboardType NSTIFFPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypeTIFF", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSRTFPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypeRTF", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSTabularTextPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypeTabularText", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSFontPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypeFont", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSRulerPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypeRuler", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSColorPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypeColor", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSRTFDPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypeRTFD", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSHTMLPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypeHTML", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSURLPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypeURL", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSPDFPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypePDF", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSMultipleTextSelectionPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypeMultipleTextSelection", 10_5, 10_14);

APPKIT_EXTERN NSPasteboardType NSPostScriptPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("@\"com.adobe.encapsulated-postscript\"", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSVCardPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("kUTTypeVCard", 10_0, 10_14);
APPKIT_EXTERN NSPasteboardType NSInkTextPboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("kUTTypeInkText", 10_0, 10_14);

// HFS Promise type for dragging only
APPKIT_EXTERN NSPasteboardType NSFilesPromisePboardType NS_DEPRECATED_WITH_REPLACEMENT_MAC("kPasteboardTypeFileURLPromise", 10_0, 10_14);

APPKIT_EXTERN NSPasteboardType const NSPasteboardTypeFindPanelSearchOptions NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardTypeTextFinderOptions", 10_6, 10_14);

APPKIT_EXTERN NSPasteboardName NSGeneralPboard NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardNameGeneral", 10_0, 10_13);
APPKIT_EXTERN NSPasteboardName NSFontPboard NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardNameFont", 10_0, 10_13);
APPKIT_EXTERN NSPasteboardName NSRulerPboard NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardNameRuler", 10_0, 10_13);
APPKIT_EXTERN NSPasteboardName NSFindPboard NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardNameFind", 10_0, 10_13);
APPKIT_EXTERN NSPasteboardName NSDragPboard NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSPasteboardNameDrag", 10_0, 10_13);

/* NSPICTPboardType is deprecated in SnowLeopard.  The PICT format was formally deprecated in Tiger along with QuickDraw.  Applications should not be explicitly providing or looking for PICT data on the pasteboard.

To aid in this deprecation, if PICT is the only image type on the pasteboard, as is sometimes the case when copying images from 32-bit Carbon applications, a translated image type will be automatically reported and provided by NSPasteboard.  The translated type is added to the types array ahead of PICT so that the deprecated PICT format is not the preferred format.  In addition, when an application provides image data to NSPasteboard, the Carbon Pasteboard Manager will automatically make a PICT translation available to 32-bit Carbon applications.

Although NSPICTPboardType and its UTI equivalent kUTTypePICT will appear in a pasteboard's type array retrieved from the existing NSPasteboard API, it may cease to be reported in future releases.
*/
APPKIT_EXTERN NSPasteboardType NSPICTPboardType NS_DEPRECATED_MAC(10_0, 10_6);

NS_ASSUME_NONNULL_END




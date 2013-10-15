/*
	NSPasteboard.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSURL.h>
#import <CoreFoundation/CFBase.h>

@class NSArray, NSData, NSFileWrapper, NSMutableDictionary;

/* standard Pasteboard types */

APPKIT_EXTERN NSString *NSStringPboardType;
APPKIT_EXTERN NSString *NSFilenamesPboardType;
APPKIT_EXTERN NSString *NSPostScriptPboardType;
APPKIT_EXTERN NSString *NSTIFFPboardType;
APPKIT_EXTERN NSString *NSRTFPboardType;
APPKIT_EXTERN NSString *NSTabularTextPboardType;
APPKIT_EXTERN NSString *NSFontPboardType;
APPKIT_EXTERN NSString *NSRulerPboardType;
APPKIT_EXTERN NSString *NSFileContentsPboardType;
APPKIT_EXTERN NSString *NSColorPboardType;
APPKIT_EXTERN NSString *NSRTFDPboardType;
APPKIT_EXTERN NSString *NSHTMLPboardType;
APPKIT_EXTERN NSString *NSPICTPboardType;
APPKIT_EXTERN NSString *NSURLPboardType;
APPKIT_EXTERN NSString *NSPDFPboardType;
APPKIT_EXTERN NSString *NSVCardPboardType AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
APPKIT_EXTERN NSString *NSFilesPromisePboardType AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER; // HFS Promise type for dragging only
APPKIT_EXTERN NSString *NSInkTextPboardType AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSMultipleTextSelectionPboardType   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* standard Pasteboard names */

APPKIT_EXTERN NSString *NSGeneralPboard;
APPKIT_EXTERN NSString *NSFontPboard;
APPKIT_EXTERN NSString *NSRulerPboard;
APPKIT_EXTERN NSString *NSFindPboard;
APPKIT_EXTERN NSString *NSDragPboard;


APPKIT_EXTERN NSString *NSCreateFilenamePboardType(NSString *fileType);
APPKIT_EXTERN NSString *NSCreateFileContentsPboardType(NSString *fileType);
APPKIT_EXTERN NSString *NSGetFileType(NSString *pboardType);
APPKIT_EXTERN NSArray *NSGetFileTypes(NSArray *pboardTypes);


@interface NSPasteboard : NSObject
{
    @private
    id			_pboard;
    int			_gen;
    id			_owners;
    CFIndex		_cachedTypeNameChangeCount;
    NSArray *		_cachedTypeNames;
    NSMutableDictionary *_promiseTypeNamesByIdentifier;
    id			_support;	
    void *		_reserved[4];
}

+ (NSPasteboard *)generalPasteboard;
+ (NSPasteboard *)pasteboardWithName:(NSString *)name;
+ (NSPasteboard *)pasteboardWithUniqueName;

+ (NSArray *)typesFilterableTo:(NSString *)type;

+ (NSPasteboard *)pasteboardByFilteringFile:(NSString *)filename;
+ (NSPasteboard *)pasteboardByFilteringData:(NSData *)data ofType:(NSString *)type;
+ (NSPasteboard *)pasteboardByFilteringTypesInPasteboard:(NSPasteboard *)pboard;

- (NSString *)name;

- (void)releaseGlobally;

- (NSInteger)declareTypes:(NSArray *)newTypes owner:(id)newOwner;
- (NSInteger)addTypes:(NSArray *)newTypes owner:(id)newOwner;
- (NSInteger)changeCount;

- (NSArray *)types;
- (NSString *)availableTypeFromArray:(NSArray *)types;

- (BOOL)setData:(NSData *)data forType:(NSString *)dataType;
- (NSData *)dataForType:(NSString *)dataType;

- (BOOL)setPropertyList:(id)plist forType:(NSString *)dataType;
- (id)propertyListForType:(NSString *)dataType;

- (BOOL)setString:(NSString *)string forType:(NSString *)dataType;
- (NSString *)stringForType:(NSString *)dataType;

@end

@interface NSPasteboard(NSFileContents)
- (BOOL)writeFileContents:(NSString *)filename;
- (NSString *)readFileContentsType:(NSString *)type toFile:(NSString *)filename;

- (BOOL)writeFileWrapper:(NSFileWrapper *)wrapper;
- (NSFileWrapper *)readFileWrapper;

@end

@interface NSURL(NSPasteboardSupport)
+ (NSURL *)URLFromPasteboard:(NSPasteboard *)pasteBoard;
- (void)writeToPasteboard:(NSPasteboard *)pasteBoard;
@end

@interface NSObject(NSPasteboardOwner)
- (void)pasteboard:(NSPasteboard *)sender provideDataForType:(NSString *)type;
- (void)pasteboardChangedOwner:(NSPasteboard *)sender;
@end


/*
	NSPasteboard.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSURL.h>
#import <AppKit/AppKitDefines.h>

@class NSArray, NSData, NSFileWrapper;

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
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
APPKIT_EXTERN NSString *NSVCardPboardType;
// HFS Promise type for dragging only
APPKIT_EXTERN NSString *NSFilesPromisePboardType;
#endif

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
    void *		_pboard;
    int			_gen;
    void *		_owners;
    void *		_reserved[8];
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

- (int)declareTypes:(NSArray *)newTypes owner:(id)newOwner;
- (int)addTypes:(NSArray *)newTypes owner:(id)newOwner;
- (int)changeCount;

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


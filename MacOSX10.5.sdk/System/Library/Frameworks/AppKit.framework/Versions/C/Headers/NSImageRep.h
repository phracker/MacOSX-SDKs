/*
	NSImageRep.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>

@class NSArray, NSPasteboard, NSURL;

/* NSImageRepMatchesDevice indicates the value is variable, depending on the output device. It can be passed in (or received back) as the value of bitsPerSample, pixelsWide, and pixelsHigh.
*/
enum {
    NSImageRepMatchesDevice = 0
};

@interface NSImageRep : NSObject <NSCopying, NSCoding> {
    /*All instance variables are private*/
    struct __repFlags {
	unsigned int hasAlpha:1;
	unsigned int isOpaque:1;
        unsigned int cacheParamsComputed:1;
        unsigned int cacheAlphaComputed:1;
        unsigned int loadState:2;
        unsigned int keepCacheWindow:1;
        unsigned int reserved:1;
        unsigned int bitsPerSample:8;
	unsigned int gsaved:16;
    } _repFlags;
    NSString *_colorSpaceName;
    NSSize _size;
    int _pixelsWide;
    int _pixelsHigh;
}

/* Drawing methods. drawAtPoint: and drawInRect: go through draw after modifying the CTM.
*/
- (BOOL)draw;
- (BOOL)drawAtPoint:(NSPoint)point;
- (BOOL)drawInRect:(NSRect)rect;

/* Methods to return info about the image. NSImageRep provides storage for all of these; however, it's illegal to set them in some subclasses.
*/
- (void)setSize:(NSSize)aSize;
- (NSSize)size;
- (void)setAlpha:(BOOL)flag;
- (BOOL)hasAlpha;
- (void)setOpaque:(BOOL)flag;
- (BOOL)isOpaque;
- (void)setColorSpaceName:(NSString *)string;
- (NSString *)colorSpaceName;
- (void)setBitsPerSample:(NSInteger)anInt;
- (NSInteger)bitsPerSample;
- (void)setPixelsWide:(NSInteger)anInt;
- (NSInteger)pixelsWide;
- (void)setPixelsHigh:(NSInteger)anInt;
- (NSInteger)pixelsHigh;

/* The rest of the methods all deal with subclassers which can read/write data in files or pasteboards. 
*/

/* Registry management: Subclasses which deal with file & pasteboard types should register themselves. These classes should also implement imageUnfilteredFileTypes, imageUnfilteredPasteboardTypes, initWithData:, canInitWithData:, imageRepWithData:, and, if they have the ability to read multiple images from a file, imageRepsWithData:. These last three should not do any filtering; all filtering is automatic.
*/
+ (void)registerImageRepClass:(Class)imageRepClass;
+ (void)unregisterImageRepClass:(Class)imageRepClass;
+ (NSArray *)registeredImageRepClasses;
+ (Class)imageRepClassForFileType:(NSString *)type;
+ (Class)imageRepClassForPasteboardType:(NSString *)type;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
+ (Class)imageRepClassForType:(NSString *)type;
#endif
+ (Class)imageRepClassForData:(NSData *)data;
	
/* Should be overridden by subclassers to load an unfiltered image. 
*/
+ (BOOL)canInitWithData:(NSData *)data;

/* Implemented by subclassers to indicate what data types they can deal with.
*/
+ (NSArray *)imageUnfilteredFileTypes;
+ (NSArray *)imageUnfilteredPasteboardTypes;

/* These expand the unfiltered lists returned by imageUnfilteredFileTypes and imageUnfilteredPasteboardTypes.
*/
+ (NSArray *)imageFileTypes;
+ (NSArray *)imagePasteboardTypes;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Implemented by subclassers to indicate what UTI-identified data types they can deal with.
*/
+ (NSArray *)imageUnfilteredTypes;

/* This expands the unfiltered list returned by imageUnfilteredTypes.
*/
+ (NSArray *)imageTypes;

#endif

/* Convenience method: Checks to see if any of the types on the pasteboard can be understood by a registered imagerep class after filtering or if the pasteboard contains a filename that can be understood by a registered imagerep class after filtering. If sent to a subclass, does this for just the types understood by the subclass.
*/
+ (BOOL)canInitWithPasteboard:(NSPasteboard *)pasteboard;

/* Convenience methods: Checks to see if the provided file or pasteboard types can be understood by a registered imagerep class after filtering; if so, calls imageRepsWithData: or imageRepWithData:. If sent to a subclass, does this just for the types understood by that subclass.
*/
+ (NSArray *)imageRepsWithContentsOfFile:(NSString *)filename;
+ (id)imageRepWithContentsOfFile:(NSString *)filename;
+ (NSArray *)imageRepsWithContentsOfURL:(NSURL *)url;
+ (id)imageRepWithContentsOfURL:(NSURL *)url;
+ (NSArray *)imageRepsWithPasteboard:(NSPasteboard *)pasteboard;
+ (id)imageRepWithPasteboard:(NSPasteboard *)pasteboard;

@end

/* Notifications */
#define NSImageRepRegistryChangedNotification NSImageRepRegistryDidChangeNotification /* obsolete name */
APPKIT_EXTERN NSString *NSImageRepRegistryDidChangeNotification;


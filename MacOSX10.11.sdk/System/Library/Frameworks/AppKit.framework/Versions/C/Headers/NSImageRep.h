/*
	NSImageRep.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSGraphics.h>
#import <ApplicationServices/ApplicationServices.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPasteboard, NSGraphicsContext, NSURL;

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
        unsigned int cacheParamsComputed:1 __attribute__((deprecated));
        unsigned int cacheAlphaComputed:1 __attribute__((deprecated));
        unsigned int loadState:2;
        unsigned int keepCacheWindow:1 __attribute__((deprecated));
        unsigned int reserved:1;
        unsigned int bitsPerSample:8;
	unsigned int gsaved:16;
    } _repFlags;
    NSString *_colorSpaceName;
    NSSize _size;
    int _pixelsWide;
    int _pixelsHigh;
}

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/* Drawing methods. draw is the only primitive.  
*/
- (BOOL)draw;
- (BOOL)drawAtPoint:(NSPoint)point;
- (BOOL)drawInRect:(NSRect)rect;
- (BOOL)drawInRect:(NSRect)dstSpacePortionRect fromRect:(NSRect)srcSpacePortionRect operation:(NSCompositingOperation)op fraction:(CGFloat)requestedAlpha respectFlipped:(BOOL)respectContextIsFlipped hints:(nullable NSDictionary<NSString *, id> *)hints NS_AVAILABLE_MAC(10_6);

/* Methods to return info about the image. NSImageRep provides storage for all of these; however, it's illegal to set them in some subclasses.
*/
@property NSSize size;
@property (getter=hasAlpha) BOOL alpha;
@property (getter=isOpaque) BOOL opaque;
@property (copy) NSString *colorSpaceName;
@property NSInteger bitsPerSample;
@property NSInteger pixelsWide;
@property NSInteger pixelsHigh;

/* The rest of the methods all deal with subclassers which can read/write data in files or pasteboards. 
*/

/* Registry management: Subclasses which deal with file & pasteboard types should register themselves. These classes should also implement imageUnfilteredFileTypes, imageUnfilteredPasteboardTypes, initWithData:, canInitWithData:, imageRepWithData:, and, if they have the ability to read multiple images from a file, imageRepsWithData:. These last three should not do any filtering; all filtering is automatic.
*/
+ (void)registerImageRepClass:(Class)imageRepClass;
+ (void)unregisterImageRepClass:(Class)imageRepClass;
+ (NSArray<Class> *)registeredImageRepClasses;
+ (nullable Class)imageRepClassForFileType:(NSString *)type NS_DEPRECATED_MAC(10_0, 10_10, "Use +imageRepClassForType: instead");
+ (nullable Class)imageRepClassForPasteboardType:(NSString *)type NS_DEPRECATED_MAC(10_0, 10_10, "Use +imageRepClassForType: instead");
+ (nullable Class)imageRepClassForType:(NSString *)type NS_AVAILABLE_MAC(10_5);
+ (nullable Class)imageRepClassForData:(NSData *)data;
	
/* Should be overridden by subclassers to load an unfiltered image. 
*/
+ (BOOL)canInitWithData:(NSData *)data;

/* Implemented by subclassers to indicate what data types they can deal with.
*/
+ (NSArray<NSString *> *)imageUnfilteredFileTypes NS_DEPRECATED_MAC(10_0, 10_10, "Use +imageUnfilteredTypes instead");
+ (NSArray<NSString *> *)imageUnfilteredPasteboardTypes NS_DEPRECATED_MAC(10_0, 10_10, "Use +imageUnfilteredTypes instead");

/* These expand the unfiltered lists returned by imageUnfilteredFileTypes and imageUnfilteredPasteboardTypes.
*/
+ (NSArray<NSString *> *)imageFileTypes NS_DEPRECATED_MAC(10_0, 10_10, "Use +imageTypes instead");
+ (NSArray<NSString *> *)imagePasteboardTypes NS_DEPRECATED_MAC(10_0, 10_10, "Use +imageTypes instead");


/* Implemented by subclassers to indicate what UTI-identified data types they can deal with.
*/
+ (NSArray<NSString *> *)imageUnfilteredTypes NS_AVAILABLE_MAC(10_5);

/* This expands the unfiltered list returned by imageUnfilteredTypes.
*/
+ (NSArray<NSString *> *)imageTypes NS_AVAILABLE_MAC(10_5);


/* Convenience method: Checks to see if any of the types on the pasteboard can be understood by a registered imagerep class after filtering or if the pasteboard contains a filename that can be understood by a registered imagerep class after filtering. If sent to a subclass, does this for just the types understood by the subclass.
*/
+ (BOOL)canInitWithPasteboard:(NSPasteboard *)pasteboard;

/* Convenience methods: Checks to see if the provided file or pasteboard types can be understood by a registered imagerep class after filtering; if so, calls imageRepsWithData: or imageRepWithData:. If sent to a subclass, does this just for the types understood by that subclass.
*/
+ (nullable NSArray<NSImageRep *> *)imageRepsWithContentsOfFile:(NSString *)filename;
+ (nullable NSImageRep *)imageRepWithContentsOfFile:(NSString *)filename;
+ (nullable NSArray<NSImageRep *> *)imageRepsWithContentsOfURL:(NSURL *)url;
+ (nullable NSImageRep *)imageRepWithContentsOfURL:(NSURL *)url;
+ (nullable NSArray<NSImageRep *> *)imageRepsWithPasteboard:(NSPasteboard *)pasteboard;
+ (nullable NSImageRep *)imageRepWithPasteboard:(NSPasteboard *)pasteboard;

/* The parameters have the same meaning and behavior as in -[NSImage CGImageForProposedRect:context:hints:].
 
 This method is intended to be overridden or called, though the primary caller is NSImage.  At the NSImageRep level, it creates a CGImage by drawing the receiver into a new context.  The passed context and hints are used as a model for the new context.  If [self draw] returns NO, this method returns NULL.
 
 If your image rep subclass naturally uses a CGImage that it can return, override this method and return it.
 
 You should not need to take care to cache within an implementation of this method.  This main caller of this method is typically NSImage, and NSImage will hold onto the resulting CGImage if appropriate.
 
 The CGImageRef returned is guaranteed to live as long as the current autorelease pool.  The caller should not release the CGImage.  This is the standard Cocoa convention, but people may not realize that it applies to CFTypes.
 */
- (nullable CGImageRef)CGImageForProposedRect:(nullable NSRect *)proposedDestRect context:(nullable NSGraphicsContext *)context hints:(nullable NSDictionary<NSString *, id> *)hints NS_AVAILABLE_MAC(10_6) CF_RETURNS_NOT_RETAINED;

@end

/* Notifications */
#define NSImageRepRegistryChangedNotification NSImageRepRegistryDidChangeNotification /* obsolete name */
APPKIT_EXTERN NSString *NSImageRepRegistryDidChangeNotification;

NS_ASSUME_NONNULL_END


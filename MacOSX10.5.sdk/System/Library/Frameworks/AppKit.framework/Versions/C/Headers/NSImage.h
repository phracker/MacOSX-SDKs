/*
	NSImage.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSBundle.h>
#import <AppKit/NSGraphics.h>
#import <AppKit/NSBitmapImageRep.h>
#import <ApplicationServices/ApplicationServices.h>

@class NSArray, NSColor, NSImageRep, NSPasteboard, NSURL;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2

enum {
    NSImageLoadStatusCompleted,
    NSImageLoadStatusCancelled,
    NSImageLoadStatusInvalidData,
    NSImageLoadStatusUnexpectedEOF,
    NSImageLoadStatusReadError
};
typedef NSUInteger NSImageLoadStatus;

enum {
    NSImageCacheDefault,    // unspecified. use image rep's default
    NSImageCacheAlways,     // always generate a cache when drawing
    NSImageCacheBySize,     // cache if cache size is smaller than original data
    NSImageCacheNever       // never cache, always draw direct
};
typedef NSUInteger NSImageCacheMode;

#endif

@class _NSImageAuxiliary;

@interface NSImage : NSObject <NSCopying, NSCoding> {
    /*All instance variables are private*/
    NSString *_name;
    NSSize _size;
    struct __imageFlags {
	unsigned int scalable:1;
	unsigned int dataRetained:1;
	unsigned int uniqueWindow:1;
	unsigned int sizeWasExplicitlySet:1;
	unsigned int builtIn:1;
	unsigned int needsToExpand:1;
	unsigned int useEPSOnResolutionMismatch:1;
	unsigned int colorMatchPreferred:1;
	unsigned int multipleResolutionMatching:1;
	unsigned int subImage:1;
	unsigned int archiveByName:1;
	unsigned int unboundedCacheDepth:1;
        unsigned int flipped:1;
        unsigned int aliased:1;
	unsigned int dirtied:1;
        unsigned int cacheMode:2;
        unsigned int sampleMode:2;
        unsigned int focusedWhilePrinting:1;
        unsigned int imageEffectsRequested:1;
        unsigned int isTemplate:1;
        unsigned int failedToExpand:1;
        unsigned int reserved1:9;
    } _flags;
    id _reps;
    _NSImageAuxiliary *_imageAuxiliary;
}

+ (id)imageNamed:(NSString *)name;	/* If this finds & creates the image, only name is saved when archived */

- (id)initWithSize:(NSSize)aSize;
- (id)initWithData:(NSData *)data;			/* When archived, saves contents */
- (id)initWithContentsOfFile:(NSString *)fileName;	/* When archived, saves contents */
- (id)initWithContentsOfURL:(NSURL *)url;               /* When archived, saves contents */
- (id)initByReferencingFile:(NSString *)fileName;	/* When archived, saves fileName */
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (id)initByReferencingURL:(NSURL *)url;		/* When archived, saves url, supports progressive loading */
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (id)initWithIconRef:(IconRef)iconRef;
#endif
- (id)initWithPasteboard:(NSPasteboard *)pasteboard;

- (void)setSize:(NSSize)aSize;
- (NSSize)size;
- (BOOL)setName:(NSString *)string;
- (NSString *)name;
- (void)setScalesWhenResized:(BOOL)flag;
- (BOOL)scalesWhenResized;
- (void)setDataRetained:(BOOL)flag;
- (BOOL)isDataRetained;
- (void)setCachedSeparately:(BOOL)flag;
- (BOOL)isCachedSeparately;
- (void)setCacheDepthMatchesImageDepth:(BOOL)flag;
- (BOOL)cacheDepthMatchesImageDepth;
- (void)setBackgroundColor:(NSColor *)aColor;
- (NSColor *)backgroundColor;
- (void)setUsesEPSOnResolutionMismatch:(BOOL)flag;
- (BOOL)usesEPSOnResolutionMismatch;
- (void)setPrefersColorMatch:(BOOL)flag;
- (BOOL)prefersColorMatch;
- (void)setMatchesOnMultipleResolution:(BOOL)flag;
- (BOOL)matchesOnMultipleResolution;
- (void)dissolveToPoint:(NSPoint)point fraction:(CGFloat)aFloat;
- (void)dissolveToPoint:(NSPoint)point fromRect:(NSRect)rect fraction:(CGFloat)aFloat;
- (void)compositeToPoint:(NSPoint)point operation:(NSCompositingOperation)op;
- (void)compositeToPoint:(NSPoint)point fromRect:(NSRect)rect operation:(NSCompositingOperation)op;
- (void)compositeToPoint:(NSPoint)point operation:(NSCompositingOperation)op fraction:(CGFloat)delta;
- (void)compositeToPoint:(NSPoint)point fromRect:(NSRect)rect operation:(NSCompositingOperation)op fraction:(CGFloat)delta;
- (void)drawAtPoint:(NSPoint)point fromRect:(NSRect)fromRect operation:(NSCompositingOperation)op fraction:(CGFloat)delta;
- (void)drawInRect:(NSRect)rect fromRect:(NSRect)fromRect operation:(NSCompositingOperation)op fraction:(CGFloat)delta;
- (BOOL)drawRepresentation:(NSImageRep *)imageRep inRect:(NSRect)rect;
- (void)recache;
- (NSData *)TIFFRepresentation;
- (NSData *)TIFFRepresentationUsingCompression:(NSTIFFCompression)comp factor:(float)aFloat;

- (NSArray *)representations;
- (void)addRepresentations:(NSArray *)imageReps;
- (void)addRepresentation:(NSImageRep *)imageRep;
- (void)removeRepresentation:(NSImageRep *)imageRep;

- (BOOL)isValid;
- (void)lockFocus;
- (void)lockFocusOnRepresentation:(NSImageRep *)imageRepresentation;
- (void)unlockFocus;

- (NSImageRep *)bestRepresentationForDevice:(NSDictionary *)deviceDescription;

- (void)setDelegate:(id)anObject;
- (id)delegate;

/* These return union of all the types registered with NSImageRep.
*/
+ (NSArray *)imageUnfilteredFileTypes;
+ (NSArray *)imageUnfilteredPasteboardTypes;
+ (NSArray *)imageFileTypes;
+ (NSArray *)imagePasteboardTypes;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
+ (NSArray *)imageTypes;
+ (NSArray *)imageUnfilteredTypes;
#endif

+ (BOOL)canInitWithPasteboard:(NSPasteboard *)pasteboard;

- (void)setFlipped:(BOOL)flag;
- (BOOL)isFlipped;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (void)cancelIncrementalLoad;

-(void)setCacheMode:(NSImageCacheMode)mode;
-(NSImageCacheMode)cacheMode;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/* The alignmentRect of an image is metadata that a client may use to help determine layout. The bottom of the rect gives the baseline of the image. The other edges give similar information in other directions.
 
 A 20x20 image of a phone icon with a glow might specify an alignmentRect of {{2,2},{16,16}} that excludes the glow. NSButtonCell can take advantage of the alignmentRect to place the image in the same visual location as an 16x16 phone icon without the glow. A 5x5 star that should render high when aligned with text might specify a rect of {{0,-7},{5,12}}.
 
 The alignmentRect of an image has no effect on methods such as drawInRect:fromRect:operation:Fraction: or drawAtPoint:fromRect:operation:fraction:. It is the client's responsibility to take the alignmentRect into account where applicable.
 
 The default alignmentRect of an image is {{0,0},imageSize}. The rect is adjusted when setSize: is called. 
 */
- (NSRect)alignmentRect;
- (void)setAlignmentRect:(NSRect)rect;

/* The 'template' property is metadata that allows clients to be smarter about image processing.  An image should be marked as a template if it is basic glpyh-like black and white art that is intended to be processed into derived images for use on screen.
 
 NSButtonCell applies effects to images based on the state of the button.  For example, images are shaded darker when the button is pressed.  If a template image is set on a cell, the cell can apply more sophisticated effects.  For example, it may be processed into an image that looks engraved when drawn into a cell whose interiorBackgroundStyle is NSBackgroundStyleRaised, like on a textured button.
 */
- (BOOL)isTemplate;
- (void)setTemplate:(BOOL)isTemplate;
#endif

@end

@interface NSObject(NSImageDelegate)
- (NSImage *)imageDidNotDraw:(id)sender inRect:(NSRect)aRect;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (void)image:(NSImage*)image willLoadRepresentation:(NSImageRep*)rep;
- (void)image:(NSImage*)image didLoadRepresentationHeader:(NSImageRep*)rep;
- (void)image:(NSImage*)image didLoadPartOfRepresentation:(NSImageRep*)rep withValidRows:(NSInteger)rows; 
- (void)image:(NSImage*)image didLoadRepresentation:(NSImageRep*)rep withStatus:(NSImageLoadStatus)status;
#endif
@end

@interface NSBundle(NSBundleImageExtension)
- (NSString *)pathForImageResource:(NSString *)name;	/* May return nil if no file found */
@end


#pragma mark -
#pragma mark Standard Images

/* Standard images.  
 
 Most images are named by a specific function or situation where they are intended to be used.  In some cases, the artwork may be more generic than the name.  For example, the image for NSImageNameInvalidDataFreestandingTemplate is an arrow in 10.5.  Please do not use an image outside of the function for which it is intended - the artwork can change between releases.  The invalid data image could change to a yellow exclamation-point-in-triangle  icon.  If there is no image available for the situation you're interested in, please file a bug and use your own custom art in the meantime.
 
 The size of an image is also not guaranteed to be the same (or maintain the same aspect ratio) between releases, so you should explcitly size the image appropriately for your use.

 Constants that end in the word "Template" name black and clear images that return YES for isTemplate.  These images can be processed into variants appropriate for different situations.  For example, these images can invert in a selected table view row.  See -[NSImage setTemplate:] for more comments.  These images are inappropriate for display without further processing, but NSCell and its subclasses will perform the processing.
 
 Some images also contain the word "Freestanding".  This indicates that an image is appropriate for use as a borderless button - it doesn't need any extra bezel artwork behind it.  For example, Safari uses NSImageNameStopProgressTemplate as the stop button in a button on its toolbar, while it uses NSImageNameStopProgressFreestandingTemplate in the downloads window where it appears inline with a progress indicator.
  
 The string value of each symbol is the same as the constant name without the "ImageName" part.  For example, NSImageNameBonjour is @"NSBonjour".  This is documented so that images can be used by name in Interface Builder.     
 
 */
APPKIT_EXTERN NSString *const NSImageNameQuickLookTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameBluetoothTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameIChatTheaterTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameSlideshowTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*  This image is appropriate on an 'action' button.  An action button is a popup that has the same contents as the contextual menu for a related control.
 */
APPKIT_EXTERN NSString *const NSImageNameActionTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; 

/*  This image can be used as a badge for a 'smart' item.  In 10.5, this and the 'action' image are both gears.  Please avoid using a gear for other situations, and if you do, use custom art.
 */
APPKIT_EXTERN NSString *const NSImageNameSmartBadgeTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* These images are intended for use in a segmented control for switching view interfaces for another part of the window.
 */
APPKIT_EXTERN NSString *const NSImageNameIconViewTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameListViewTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameColumnViewTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameFlowViewTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

APPKIT_EXTERN NSString *const NSImageNamePathTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Place this image to the right of invalid data.  For example, use it if the user tries to commit a form when it's missing a required name field.
 */
APPKIT_EXTERN NSString *const NSImageNameInvalidDataFreestandingTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameLockLockedTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameLockUnlockedTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Use these images for "go forward" or "go back" functions, as seen in Safari's toolbar.  See also the right and left facing triangle images.
 */
APPKIT_EXTERN NSString *const NSImageNameGoRightTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; 
APPKIT_EXTERN NSString *const NSImageNameGoLeftTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER; 

/* Prefer the "GoLeft" and "GoRight" images for situations where they apply.  These generic triangles aren't endorsed for any particular use, but you can use them if you don't have any better art.
 */
APPKIT_EXTERN NSString *const NSImageNameRightFacingTriangleTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameLeftFacingTriangleTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

APPKIT_EXTERN NSString *const NSImageNameAddTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameRemoveTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameRevealFreestandingTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameFollowLinkFreestandingTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameEnterFullScreenTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameExitFullScreenTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameStopProgressTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameStopProgressFreestandingTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameRefreshTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameRefreshFreestandingTemplate AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

APPKIT_EXTERN NSString *const NSImageNameBonjour AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameDotMac AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameComputer AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameFolderBurnable AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameFolderSmart AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameNetwork AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* This image is appropriate as a drag image for multiple items.
 */
APPKIT_EXTERN NSString *const NSImageNameMultipleDocuments AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* These images are intended for use in toolbars in preference windows.
 */
APPKIT_EXTERN NSString *const NSImageNameUserAccounts AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNamePreferencesGeneral AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameAdvanced AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* These images are intended for use in other toolbars.
 */
APPKIT_EXTERN NSString *const NSImageNameInfo AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameFontPanel AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameColorPanel AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* These images are appropriate for use in sharing or permissions interfaces.
 */
APPKIT_EXTERN NSString *const NSImageNameUser AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameUserGroup AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
APPKIT_EXTERN NSString *const NSImageNameEveryone AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;  

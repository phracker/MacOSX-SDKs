/*
	NSGraphics.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSGeometry.h> 
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColor, NSView;

/*=== CONSTANTS ===*/
/* operation types for composite operators */
/* Constants moved from dpsOpenStep.h */
typedef NS_ENUM(NSUInteger, NSCompositingOperation) {
    /* Porter-Duff compositing operations */
    /* http://www.w3.org/TR/2014/CR-compositing-1-20140220/#porterduffcompositingoperators */
    NSCompositeClear,		
    NSCompositeCopy,		
    NSCompositeSourceOver,	
    NSCompositeSourceIn,	
    NSCompositeSourceOut,	
    NSCompositeSourceAtop,	
    NSCompositeDestinationOver,	
    NSCompositeDestinationIn,	
    NSCompositeDestinationOut,	
    NSCompositeDestinationAtop,	
    NSCompositeXOR,		
    NSCompositePlusDarker,
    NSCompositeHighlight	NS_DEPRECATED_MAC(10_0, 10_0, "Use NSCompositeSourceOver instead"),
    NSCompositePlusLighter,
    
    /* Separable blend-modes */
    /* http://www.w3.org/TR/2014/CR-compositing-1-20140220/#blendingseparable */
    NSCompositeMultiply		NS_AVAILABLE_MAC(10_10),
    NSCompositeScreen		NS_AVAILABLE_MAC(10_10),
    NSCompositeOverlay		NS_AVAILABLE_MAC(10_10),
    NSCompositeDarken		NS_AVAILABLE_MAC(10_10),
    NSCompositeLighten		NS_AVAILABLE_MAC(10_10),
    NSCompositeColorDodge	NS_AVAILABLE_MAC(10_10),
    NSCompositeColorBurn	NS_AVAILABLE_MAC(10_10),
    NSCompositeSoftLight	NS_AVAILABLE_MAC(10_10),
    NSCompositeHardLight	NS_AVAILABLE_MAC(10_10),
    NSCompositeDifference	NS_AVAILABLE_MAC(10_10),
    NSCompositeExclusion	NS_AVAILABLE_MAC(10_10),
    
    /* Non-separable blend-modes */
    /* http://www.w3.org/TR/2014/CR-compositing-1-20140220/#blendingnonseparable */
    NSCompositeHue		NS_AVAILABLE_MAC(10_10),
    NSCompositeSaturation	NS_AVAILABLE_MAC(10_10),
    NSCompositeColor		NS_AVAILABLE_MAC(10_10),
    NSCompositeLuminosity	NS_AVAILABLE_MAC(10_10),
};


/* types of window backing store */
typedef NS_ENUM(NSUInteger, NSBackingStoreType) {
    NSBackingStoreRetained	 = 0,
    NSBackingStoreNonretained	 = 1,
    NSBackingStoreBuffered	 = 2
};

/* ways to order windows */
typedef NS_ENUM(NSInteger, NSWindowOrderingMode) {
    NSWindowAbove		 =  1,
    NSWindowBelow		 = -1,
    NSWindowOut			 =  0
};

/* order in which to draw focus ring - above or below graphic or just draw ring */
typedef NS_ENUM(NSUInteger, NSFocusRingPlacement) {
    NSFocusRingOnly	 = 0,
    NSFocusRingBelow	 = 1,
    NSFocusRingAbove	 = 2
};

/* used by NSView and NSCell to configure if and how the control should draw its focus ring */
typedef NS_ENUM(NSUInteger, NSFocusRingType) {
    NSFocusRingTypeDefault = 0,
    NSFocusRingTypeNone = 1,
    NSFocusRingTypeExterior = 2
};


// values interchangeable with CGColorRenderingIntent values
typedef NS_ENUM(NSInteger, NSColorRenderingIntent) {
    NSColorRenderingIntentDefault, //  = kCGRenderingIntentDefault,
    NSColorRenderingIntentAbsoluteColorimetric, //  = kCGRenderingIntentAbsoluteColorimetric,
    NSColorRenderingIntentRelativeColorimetric, //  = kCGRenderingIntentRelativeColorimetric,
    NSColorRenderingIntentPerceptual, // = kCGRenderingIntentPerceptual,
    NSColorRenderingIntentSaturation // = kCGRenderingIntentSaturation
} NS_ENUM_AVAILABLE_MAC(10_5);


/* Predefined colorspace names.
*/
APPKIT_EXTERN NSString *NSCalibratedWhiteColorSpace;	/* 1.0 == white */
APPKIT_EXTERN NSString *NSCalibratedRGBColorSpace;
APPKIT_EXTERN NSString *NSDeviceWhiteColorSpace;	/* 1.0 == white */
APPKIT_EXTERN NSString *NSDeviceRGBColorSpace;
APPKIT_EXTERN NSString *NSDeviceCMYKColorSpace;
APPKIT_EXTERN NSString *NSNamedColorSpace;		/* Used for "catalog" colors */
APPKIT_EXTERN NSString *NSPatternColorSpace;
APPKIT_EXTERN NSString *NSCustomColorSpace;		/* Used to indicate a custom gstate in images */

/* Prefer colorspaces where 1.0 means white.
 */
APPKIT_EXTERN NSString *NSCalibratedBlackColorSpace     /* 1.0 == black */ NS_DEPRECATED_MAC(10_0, 10_6);	
APPKIT_EXTERN NSString *NSDeviceBlackColorSpace 	/* 1.0 == black */ NS_DEPRECATED_MAC(10_0, 10_6);


/* NSWindowDepth defines the values used in setting window depth limits. "0" indicates default depth. Window depths should not be made persistent as they will not be the same across systems. Use the functions NSBitsPerSampleFromDepth(), NSColorSpaceFromDepth(), NSBitsPerPixelFromDepth(), and NSPlanarFromDepth() to extract info from an NSWindowDepth 

On Mac OS X 10.5 and earlier, use NSBestDepth() to compute window depths. NSBestDepth() will try to accomodate all the parameters (match or better); if there are multiple matches, it gives the closest, with matching colorSpace first, then bps, then planar, then bpp. bpp is "bits per pixel"; 0 indicates default (same as the number of bits per plane, either bps or bps * NSNumberOfColorComponents()); other values maybe used as hints to provide backing stores of different configuration; for instance, 8 bit color. exactMatch is optional and indicates whether all the parameters matched exactly.

On Mac OS X 10.6 and later, you can pass one of the explicit bit depths below to -[NSWindow setDepthLimit:].  NSWindowDepthTwentyfourBitRGB is the default.
*/
enum {
    NSWindowDepthTwentyfourBitRGB = 0x208,
    NSWindowDepthSixtyfourBitRGB = 0x210,
    NSWindowDepthOnehundredtwentyeightBitRGB = 0x220
} NS_ENUM_AVAILABLE_MAC(10_6);

typedef int NSWindowDepth;

APPKIT_EXTERN NSWindowDepth NSBestDepth (NSString *colorSpace, NSInteger bps, NSInteger bpp, BOOL planar, BOOL * __nullable exactMatch);
APPKIT_EXTERN BOOL NSPlanarFromDepth (NSWindowDepth depth);
APPKIT_EXTERN NSString * __nullable NSColorSpaceFromDepth (NSWindowDepth depth);
APPKIT_EXTERN NSInteger NSBitsPerSampleFromDepth(NSWindowDepth depth);
APPKIT_EXTERN NSInteger NSBitsPerPixelFromDepth(NSWindowDepth depth);
APPKIT_EXTERN NSInteger NSNumberOfColorComponents(NSString *colorSpaceName);
APPKIT_EXTERN const NSWindowDepth *NSAvailableWindowDepths (void); /* 0 terminated */


/* Standard gray values for the 2-bit deep grayscale colorspace.
*/
APPKIT_EXTERN const CGFloat NSWhite;
APPKIT_EXTERN const CGFloat NSLightGray;
APPKIT_EXTERN const CGFloat NSDarkGray;
APPKIT_EXTERN const CGFloat NSBlack;


/* Keys for deviceDescription dictionaries.
*/
APPKIT_EXTERN NSString *NSDeviceResolution;		/* NSValue containing NSSize, basically dpi */
APPKIT_EXTERN NSString *NSDeviceColorSpaceName;	/* NSString */
APPKIT_EXTERN NSString *NSDeviceBitsPerSample;		/* NSValue containing int */
APPKIT_EXTERN NSString *NSDeviceIsScreen;		/* "YES" or not there */
APPKIT_EXTERN NSString *NSDeviceIsPrinter;		/* "YES" or not there */
APPKIT_EXTERN NSString *NSDeviceSize;			/* NSValue containing NSSize */


/* Graphics functions
*/
APPKIT_EXTERN void NSRectFill(NSRect aRect);
APPKIT_EXTERN void NSRectFillList(const NSRect *rects, NSInteger count);
APPKIT_EXTERN void NSRectFillListWithGrays(const NSRect *rects, const CGFloat *grays, NSInteger num);
APPKIT_EXTERN void NSRectFillListWithColors(const NSRect *rects,  NSColor * const __nonnull * __nonnull colors, NSInteger num);
APPKIT_EXTERN void NSRectFillUsingOperation(NSRect aRect, NSCompositingOperation op);
APPKIT_EXTERN void NSRectFillListUsingOperation(const NSRect *rects, NSInteger count, NSCompositingOperation op);
APPKIT_EXTERN void NSRectFillListWithColorsUsingOperation(const NSRect *rects, NSColor * const __nonnull * __nonnull colors, NSInteger num, NSCompositingOperation op);
APPKIT_EXTERN void NSFrameRect(NSRect aRect);
APPKIT_EXTERN void NSFrameRectWithWidth(NSRect aRect, CGFloat frameWidth);
APPKIT_EXTERN void NSFrameRectWithWidthUsingOperation(NSRect aRect, CGFloat frameWidth, NSCompositingOperation op);
APPKIT_EXTERN void NSRectClip(NSRect aRect);
APPKIT_EXTERN void NSRectClipList(const NSRect *rects, NSInteger count);
APPKIT_EXTERN NSRect NSDrawTiledRects(NSRect boundsRect, NSRect clipRect, const NSRectEdge *sides, const CGFloat *grays, NSInteger count);
APPKIT_EXTERN void NSDrawGrayBezel(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDrawGroove(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDrawWhiteBezel(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDrawButton(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSEraseRect(NSRect aRect);
APPKIT_EXTERN NSColor * __nullable NSReadPixel(NSPoint passedPoint);
APPKIT_EXTERN void NSDrawBitmap(NSRect rect, NSInteger width, NSInteger height, NSInteger bps, NSInteger spp, NSInteger bpp, NSInteger bpr, BOOL isPlanar, BOOL hasAlpha, NSString *colorSpaceName, const unsigned char *const __nullable data[5]);

APPKIT_EXTERN void NSHighlightRect(NSRect aRect) NS_DEPRECATED_MAC(10_0, 10_0);
APPKIT_EXTERN void NSBeep(void);

/* gets performance stats about window server memory usage */
APPKIT_EXTERN NSInteger NSGetWindowServerMemory(NSInteger context, NSInteger *virtualMemory, NSInteger *windowBackingMemory,   NSString * __nonnull * __nonnull windowDumpString); // Deprecated; doesn't return anything useful (as of 10.0)

APPKIT_EXTERN NSRect NSDrawColorTiledRects(NSRect boundsRect, NSRect clipRect, const NSRectEdge *sides, NSColor * __nonnull * __nonnull colors, NSInteger count);
APPKIT_EXTERN void NSDrawDarkBezel(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDrawLightBezel(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDottedFrameRect(NSRect aRect);

APPKIT_EXTERN void NSDrawWindowBackground(NSRect aRect);
APPKIT_EXTERN void NSSetFocusRingStyle(NSFocusRingPlacement placement);

/* Disable and reenable screen updates.  
** NSDisableScreenUpdates prevents drawing for all windows belonging to the calling  
** process from being flushed to the screen.  This function permits operations on 
** multiple windows to appear atomic to the user, and is particularly useful for parent
** and child windows.  Note that this function should be used with care for short 
** operations only as the system will only allow updates to be disabled for a short 
** time (currently one second) before automatically reenabling updates.
** NSEnableScreenUpdates reenables drawing that was previously disabled by 
** NSDisableScreenUpdates.  Multiple calls stack.
*/
APPKIT_EXTERN void NSDisableScreenUpdates(void);
APPKIT_EXTERN void NSEnableScreenUpdates(void);


/* Runs one of the standard system animation effects (display and sound).
** 'centerLocation' represents the center, in screen coordinates, to show the effect.
** 'size' specifies how big the effect should be.  Use NSZeroSize to get the default size.
** 'animationDelegate' is optionally, an object that wants to know when the effect has completed.
** 'didEndSelector' will be invoked in the animationDelegate when the animation has completed.
**  
** The didEndSelector should have the following signature:
** 	- (void)animationEffectDidEnd:(void *)contextInfo;
*/

typedef NS_ENUM(NSUInteger, NSAnimationEffect) {
	// The default effect used to indicate removal of an item from a collection, 
	// such as toolbar (indicates removal, without destroying the underlying data).
	NSAnimationEffectDisappearingItemDefault = 0,

	// An effect showing a puff of smoke.
	NSAnimationEffectPoof = 10
};

APPKIT_EXTERN void NSShowAnimationEffect(NSAnimationEffect animationEffect, NSPoint centerLocation, NSSize size, __nullable id animationDelegate, __nullable SEL didEndSelector, void * __nullable contextInfo);

/* NSCountWindows, NSWindowList, NSCountWindowsForContext, and NSWindowListForContext are deprecated on Mac OS 10.6 and later.  Use +[NSWindow windowNumbersWithOptions:] instead */
APPKIT_EXTERN void NSCountWindows(NSInteger *count) NS_DEPRECATED_MAC(10_0, 10_6, "Use +[Window windowNumbersWithOptions:] instead");
APPKIT_EXTERN void NSWindowList(NSInteger size, NSInteger list[]) NS_DEPRECATED_MAC(10_0, 10_6, "Use +[Window windowNumbersWithOptions:] instead");
APPKIT_EXTERN void NSCountWindowsForContext(NSInteger context, NSInteger *count) NS_DEPRECATED_MAC(10_0, 10_6, "Use +[Window windowNumbersWithOptions:] instead");
APPKIT_EXTERN void NSWindowListForContext(NSInteger context, NSInteger size, NSInteger list[]) NS_DEPRECATED_MAC(10_0, 10_6, "Use +[Window windowNumbersWithOptions:] instead");
/* This method does nothing, and is deprecated */
APPKIT_EXTERN void NSCopyBits(NSInteger srcGState, NSRect srcRect, NSPoint destPoint) NS_DEPRECATED_MAC(10_0, 10_10);

NS_ASSUME_NONNULL_END

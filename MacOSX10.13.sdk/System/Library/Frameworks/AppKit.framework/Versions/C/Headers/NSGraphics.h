/*
	NSGraphics.h
	Application Kit
	Copyright (c) 1994-2017, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSGeometry.h> 
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSColor, NSView;

/* Operation types for composite operators */
typedef NS_ENUM(NSUInteger, NSCompositingOperation) {
    /* Porter-Duff compositing operations */
    /* http://www.w3.org/TR/2014/CR-compositing-1-20140220/#porterduffcompositingoperators */
    NSCompositingOperationClear,
    NSCompositingOperationCopy,
    NSCompositingOperationSourceOver,
    NSCompositingOperationSourceIn,
    NSCompositingOperationSourceOut,
    NSCompositingOperationSourceAtop,
    NSCompositingOperationDestinationOver,
    NSCompositingOperationDestinationIn,
    NSCompositingOperationDestinationOut,
    NSCompositingOperationDestinationAtop,
    NSCompositingOperationXOR,
    NSCompositingOperationPlusDarker,
    NSCompositingOperationHighlight NS_DEPRECATED_MAC(10_0, 10_0, "Use NSCompositingOperationSourceOver instead"),
    NSCompositingOperationPlusLighter,
    
    /* Separable blend-modes */
    /* http://www.w3.org/TR/2014/CR-compositing-1-20140220/#blendingseparable */
    NSCompositingOperationMultiply	NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationScreen	NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationOverlay	NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationDarken	NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationLighten	NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationColorDodge	NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationColorBurn	NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationSoftLight	NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationHardLight	NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationDifference	NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationExclusion	NS_AVAILABLE_MAC(10_10),
    
    /* Non-separable blend-modes */
    /* http://www.w3.org/TR/2014/CR-compositing-1-20140220/#blendingnonseparable */
    NSCompositingOperationHue		NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationSaturation	NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationColor		NS_AVAILABLE_MAC(10_10),
    NSCompositingOperationLuminosity	NS_AVAILABLE_MAC(10_10),
};


static const NSCompositingOperation NSCompositeClear NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationClear", 10.0, 10.12) = NSCompositingOperationClear;
static const NSCompositingOperation NSCompositeCopy NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationCopy", 10.0, 10.12) = NSCompositingOperationCopy;
static const NSCompositingOperation NSCompositeSourceOver NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationSourceOver", 10.0, 10.12) = NSCompositingOperationSourceOver;
static const NSCompositingOperation NSCompositeSourceIn NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationSourceIn", 10.0, 10.12) = NSCompositingOperationSourceIn;
static const NSCompositingOperation NSCompositeSourceOut NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationSourceOut", 10.0, 10.12) = NSCompositingOperationSourceOut;
static const NSCompositingOperation NSCompositeSourceAtop NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationSourceAtop", 10.0, 10.12) = NSCompositingOperationSourceAtop;
static const NSCompositingOperation NSCompositeDestinationOver NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationDestinationOver", 10.0, 10.12) = NSCompositingOperationDestinationOver;
static const NSCompositingOperation NSCompositeDestinationIn NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationDestinationIn", 10.0, 10.12) = NSCompositingOperationDestinationIn;
static const NSCompositingOperation NSCompositeDestinationOut NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationDestinationOut", 10.0, 10.12) = NSCompositingOperationDestinationOut;
static const NSCompositingOperation NSCompositeDestinationAtop NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationDestinationAtop", 10.0, 10.12) = NSCompositingOperationDestinationAtop;
static const NSCompositingOperation NSCompositeXOR NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationXOR", 10.0, 10.12) = NSCompositingOperationXOR;
static const NSCompositingOperation NSCompositePlusDarker NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationPlusDarker", 10.0, 10.12) = NSCompositingOperationPlusDarker;
static const NSCompositingOperation NSCompositeHighlight NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationSourceOver", 10.0, 10.0) = NSCompositingOperationHighlight;
static const NSCompositingOperation NSCompositePlusLighter NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationPlusLighter", 10.0, 10.12) = NSCompositingOperationPlusLighter;
static const NSCompositingOperation NSCompositeMultiply	NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationMultiply", 10.0, 10.12) = NSCompositingOperationMultiply;
static const NSCompositingOperation NSCompositeScreen NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationScreen", 10.0, 10.12) = NSCompositingOperationScreen;
static const NSCompositingOperation NSCompositeOverlay NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationOverlay", 10.0, 10.12) = NSCompositingOperationOverlay;
static const NSCompositingOperation NSCompositeDarken NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationDarken", 10.0, 10.12) = NSCompositingOperationDarken;
static const NSCompositingOperation NSCompositeLighten NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationLighten", 10.0, 10.12) = NSCompositingOperationLighten;
static const NSCompositingOperation NSCompositeColorDodge NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationColorDodge", 10.0, 10.12) = NSCompositingOperationColorDodge;
static const NSCompositingOperation NSCompositeColorBurn NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationColorBurn", 10.0, 10.12) = NSCompositingOperationColorBurn;
static const NSCompositingOperation NSCompositeSoftLight NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationSoftLight", 10.0, 10.12) = NSCompositingOperationSoftLight;
static const NSCompositingOperation NSCompositeHardLight NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationHardLight", 10.0, 10.12) = NSCompositingOperationHardLight;
static const NSCompositingOperation NSCompositeDifference NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationDifference", 10.0, 10.12) = NSCompositingOperationDifference;
static const NSCompositingOperation NSCompositeExclusion NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationExclusion", 10.0, 10.12) = NSCompositingOperationExclusion;

static const NSCompositingOperation NSCompositeHue NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationHue", 10.0, 10.12) = NSCompositingOperationHue;
static const NSCompositingOperation NSCompositeSaturation NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationSaturation", 10.0, 10.12) = NSCompositingOperationSaturation;
static const NSCompositingOperation NSCompositeColor NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationColor", 10.0, 10.12) = NSCompositingOperationColor;
static const NSCompositingOperation NSCompositeLuminosity NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSCompositingOperationLuminosity", 10.0, 10.12) = NSCompositingOperationLuminosity;




/* Types of window backing stores.
 */
typedef NS_ENUM(NSUInteger, NSBackingStoreType) {
    /* NSBackingStoreRetained and NSBackingStoreNonretained have effectively been synonyms of NSBackingStoreBuffered since OS X Mountain Lion.  Please switch to the equivalent NSBackingStoreBuffered.
     */
    NSBackingStoreRetained NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBackingStoreBuffered", 10.0, 10.13) = 0,
    NSBackingStoreNonretained NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSBackingStoreBuffered", 10.0, 10.13) = 1,
    NSBackingStoreBuffered = 2,
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


typedef NSString * NSColorSpaceName NS_STRING_ENUM;
/* Predefined colorspace names.
*/
APPKIT_EXTERN NSColorSpaceName NSCalibratedWhiteColorSpace;	/* 1.0 == white */
APPKIT_EXTERN NSColorSpaceName NSCalibratedRGBColorSpace;
APPKIT_EXTERN NSColorSpaceName NSDeviceWhiteColorSpace;	/* 1.0 == white */
APPKIT_EXTERN NSColorSpaceName NSDeviceRGBColorSpace;
APPKIT_EXTERN NSColorSpaceName NSDeviceCMYKColorSpace;
APPKIT_EXTERN NSColorSpaceName NSNamedColorSpace;		/* Used for "catalog" colors */
APPKIT_EXTERN NSColorSpaceName NSPatternColorSpace;
APPKIT_EXTERN NSColorSpaceName NSCustomColorSpace;		/* Used to indicate a custom gstate in images */

/* Prefer colorspaces where 1.0 means white.
 */
APPKIT_EXTERN NSColorSpaceName NSCalibratedBlackColorSpace     /* 1.0 == black */ NS_DEPRECATED_MAC(10_0, 10_6);
APPKIT_EXTERN NSColorSpaceName NSDeviceBlackColorSpace 	/* 1.0 == black */ NS_DEPRECATED_MAC(10_0, 10_6);


/* NSWindowDepth defines the values used in setting window depth limits. "0" indicates default depth. Window depths should not be made persistent as they will not be the same across systems. Use the functions NSBitsPerSampleFromDepth(), NSColorSpaceFromDepth(), NSBitsPerPixelFromDepth(), and NSPlanarFromDepth() to extract info from an NSWindowDepth 

On Mac OS X 10.5 and earlier, use NSBestDepth() to compute window depths. NSBestDepth() will try to accomodate all the parameters (match or better); if there are multiple matches, it gives the closest, with matching colorSpace first, then bps, then planar, then bpp. bpp is "bits per pixel"; 0 indicates default (same as the number of bits per plane, either bps or bps * NSNumberOfColorComponents()); other values maybe used as hints to provide backing stores of different configuration; for instance, 8 bit color. exactMatch is optional and indicates whether all the parameters matched exactly.

On Mac OS X 10.6 and later, you can pass one of the explicit bit depths below to -[NSWindow setDepthLimit:].  NSWindowDepthTwentyfourBitRGB is the default.
*/
typedef NS_ENUM(int32_t, NSWindowDepth) {
    NSWindowDepthTwentyfourBitRGB = 0x208,
    NSWindowDepthSixtyfourBitRGB = 0x210,
    NSWindowDepthOnehundredtwentyeightBitRGB = 0x220
} NS_ENUM_AVAILABLE_MAC(10_6);

APPKIT_EXTERN NSWindowDepth NSBestDepth (NSColorSpaceName colorSpace, NSInteger bps, NSInteger bpp, BOOL planar, BOOL * __nullable exactMatch);
APPKIT_EXTERN BOOL NSPlanarFromDepth (NSWindowDepth depth);
APPKIT_EXTERN NSColorSpaceName __nullable NSColorSpaceFromDepth (NSWindowDepth depth);
APPKIT_EXTERN NSInteger NSBitsPerSampleFromDepth(NSWindowDepth depth);
APPKIT_EXTERN NSInteger NSBitsPerPixelFromDepth(NSWindowDepth depth);
APPKIT_EXTERN NSInteger NSNumberOfColorComponents(NSColorSpaceName colorSpaceName);
APPKIT_EXTERN const NSWindowDepth *NSAvailableWindowDepths (void); /* 0 terminated */


/* Standard gray values for the 2-bit deep grayscale colorspace.
*/
APPKIT_EXTERN const CGFloat NSWhite;
APPKIT_EXTERN const CGFloat NSLightGray;
APPKIT_EXTERN const CGFloat NSDarkGray;
APPKIT_EXTERN const CGFloat NSBlack;

/* Approximate color gamut for use by NSScreen and NSWindow
 */
typedef NS_ENUM(NSInteger, NSDisplayGamut) {
    NSDisplayGamutSRGB = 1,
    NSDisplayGamutP3 
} NS_ENUM_AVAILABLE_MAC(10_12);

/* Keys for deviceDescription dictionaries.
*/
typedef NSString * NSDeviceDescriptionKey NS_EXTENSIBLE_STRING_ENUM;
APPKIT_EXTERN NSDeviceDescriptionKey NSDeviceResolution;		/* NSValue containing NSSize, basically dpi */
APPKIT_EXTERN NSDeviceDescriptionKey NSDeviceColorSpaceName;	/* NSString */
APPKIT_EXTERN NSDeviceDescriptionKey NSDeviceBitsPerSample;		/* NSValue containing int */
APPKIT_EXTERN NSDeviceDescriptionKey NSDeviceIsScreen;		/* "YES" or not there */
APPKIT_EXTERN NSDeviceDescriptionKey NSDeviceIsPrinter;		/* "YES" or not there */
APPKIT_EXTERN NSDeviceDescriptionKey NSDeviceSize;			/* NSValue containing NSSize */


/* Graphics functions
*/
APPKIT_EXTERN void NSRectFill(NSRect rect);
APPKIT_EXTERN void NSRectFillList(const NSRect *rects, NSInteger count);
APPKIT_EXTERN void NSRectFillListWithGrays(const NSRect *rects, const CGFloat *grays, NSInteger num);
APPKIT_EXTERN void NSRectFillListWithColors(const NSRect *rects,  NSColor * const __nonnull * __nonnull colors, NSInteger num);
APPKIT_EXTERN void NSRectFillUsingOperation(NSRect rect, NSCompositingOperation op);
APPKIT_EXTERN void NSRectFillListUsingOperation(const NSRect *rects, NSInteger count, NSCompositingOperation op);
APPKIT_EXTERN void NSRectFillListWithColorsUsingOperation(const NSRect *rects, NSColor * const __nonnull * __nonnull colors, NSInteger num, NSCompositingOperation op);
APPKIT_EXTERN void NSFrameRect(NSRect rect);
APPKIT_EXTERN void NSFrameRectWithWidth(NSRect rect, CGFloat frameWidth);
APPKIT_EXTERN void NSFrameRectWithWidthUsingOperation(NSRect rect, CGFloat frameWidth, NSCompositingOperation op);
APPKIT_EXTERN void NSRectClip(NSRect rect);
APPKIT_EXTERN void NSRectClipList(const NSRect *rects, NSInteger count);
APPKIT_EXTERN NSRect NSDrawTiledRects(NSRect boundsRect, NSRect clipRect, const NSRectEdge *sides, const CGFloat *grays, NSInteger count);
APPKIT_EXTERN void NSDrawGrayBezel(NSRect rect, NSRect clipRect);
APPKIT_EXTERN void NSDrawGroove(NSRect rect, NSRect clipRect);
APPKIT_EXTERN void NSDrawWhiteBezel(NSRect rect, NSRect clipRect);
APPKIT_EXTERN void NSDrawButton(NSRect rect, NSRect clipRect);
APPKIT_EXTERN void NSEraseRect(NSRect rect);
APPKIT_EXTERN NSColor * __nullable NSReadPixel(NSPoint passedPoint);
APPKIT_EXTERN void NSDrawBitmap(NSRect rect, NSInteger width, NSInteger height, NSInteger bps, NSInteger spp, NSInteger bpp, NSInteger bpr, BOOL isPlanar, BOOL hasAlpha, NSColorSpaceName colorSpaceName, const unsigned char *const __nullable data[__nonnull 5]);

APPKIT_EXTERN void NSHighlightRect(NSRect rect) NS_DEPRECATED_MAC(10_0, 10_0);
APPKIT_EXTERN void NSBeep(void);

/* gets performance stats about window server memory usage */
APPKIT_EXTERN NSInteger NSGetWindowServerMemory(NSInteger context, NSInteger *virtualMemory, NSInteger *windowBackingMemory,   NSString * __nonnull * __nonnull windowDumpString); // Deprecated; doesn't return anything useful (as of 10.0)

APPKIT_EXTERN NSRect NSDrawColorTiledRects(NSRect boundsRect, NSRect clipRect, const NSRectEdge *sides, NSColor * __nonnull * __nonnull colors, NSInteger count);
APPKIT_EXTERN void NSDrawDarkBezel(NSRect rect, NSRect clipRect);
APPKIT_EXTERN void NSDrawLightBezel(NSRect rect, NSRect clipRect);
APPKIT_EXTERN void NSDottedFrameRect(NSRect rect);

APPKIT_EXTERN void NSDrawWindowBackground(NSRect rect);
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
APPKIT_EXTERN void NSCountWindows(NSInteger *count) NS_DEPRECATED_MAC(10_0, 10_6, "Use +[NSWindow windowNumbersWithOptions:] instead");
APPKIT_EXTERN void NSWindowList(NSInteger size, NSInteger list[__nonnull]) NS_DEPRECATED_MAC(10_0, 10_6, "Use +[NSWindow windowNumbersWithOptions:] instead");
APPKIT_EXTERN void NSCountWindowsForContext(NSInteger context, NSInteger *count) NS_DEPRECATED_MAC(10_0, 10_6, "Use +[NSWindow windowNumbersWithOptions:] instead");
APPKIT_EXTERN void NSWindowListForContext(NSInteger context, NSInteger size, NSInteger list[__nonnull]) NS_DEPRECATED_MAC(10_0, 10_6, "Use +[NSWindow windowNumbersWithOptions:] instead");
/* This method does nothing, and is deprecated */
APPKIT_EXTERN void NSCopyBits(NSInteger srcGState, NSRect srcRect, NSPoint destPoint) NS_DEPRECATED_MAC(10_0, 10_10);

NS_ASSUME_NONNULL_END

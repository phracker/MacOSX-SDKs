/*
	NSGraphics.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSGeometry.h> 
#import <AppKit/AppKitDefines.h>

@class NSColor, NSView;

/*=== CONSTANTS ===*/
/* operation types for composite operators */
/* Constants moved from dpsOpenStep.h */
typedef enum _NSCompositingOperation {
    NSCompositeClear		= 0,
    NSCompositeCopy		= 1,
    NSCompositeSourceOver	= 2,
    NSCompositeSourceIn		= 3,
    NSCompositeSourceOut	= 4,
    NSCompositeSourceAtop	= 5,
    NSCompositeDestinationOver	= 6,
    NSCompositeDestinationIn	= 7,
    NSCompositeDestinationOut	= 8,
    NSCompositeDestinationAtop	= 9,
    NSCompositeXOR		= 10,
    NSCompositePlusDarker	= 11,
    NSCompositeHighlight	= 12,
    NSCompositePlusLighter	= 13
} NSCompositingOperation;

/* types of window backing store */
typedef enum _NSBackingStoreType {
    NSBackingStoreRetained	 = 0,
    NSBackingStoreNonretained	 = 1,
    NSBackingStoreBuffered	 = 2
} NSBackingStoreType;

/* ways to order windows */
typedef enum _NSWindowOrderingMode {
    NSWindowAbove		 =  1,
    NSWindowBelow		 = -1,
    NSWindowOut			 =  0
} NSWindowOrderingMode;

/* order in which to draw focus ring - above or below graphic or just draw ring */
typedef enum {
    NSFocusRingOnly	 = 0,
    NSFocusRingBelow	 = 1,
    NSFocusRingAbove	 = 2
} NSFocusRingPlacement;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
/* used by NSView and NSCell to configure if and how the control should draw its focus ring */ 
typedef enum _NSFocusRingType {
    NSFocusRingTypeDefault = 0,
    NSFocusRingTypeNone = 1,
    NSFocusRingTypeExterior = 2
} NSFocusRingType;
#endif

/* Predefined colorspace names.
*/
APPKIT_EXTERN NSString *NSCalibratedWhiteColorSpace;	/* 1.0 == white */
APPKIT_EXTERN NSString *NSCalibratedBlackColorSpace;	/* 1.0 == black */
APPKIT_EXTERN NSString *NSCalibratedRGBColorSpace;
APPKIT_EXTERN NSString *NSDeviceWhiteColorSpace;	/* 1.0 == white */
APPKIT_EXTERN NSString *NSDeviceBlackColorSpace;	/* 1.0 == black */
APPKIT_EXTERN NSString *NSDeviceRGBColorSpace;
APPKIT_EXTERN NSString *NSDeviceCMYKColorSpace;
APPKIT_EXTERN NSString *NSNamedColorSpace;		/* Used for "catalog" colors */
APPKIT_EXTERN NSString *NSPatternColorSpace;
APPKIT_EXTERN NSString *NSCustomColorSpace;		/* Used to indicate a custom gstate in images */


/* NSWindowDepth defines the values used in setting window depth limits. "0" indicates default depth. Window depths should not be made persistent as they will not be the same across systems. Use the functions NSBPSFromDepth(), NSColorSpaceFromDepth(), NSBitsPerPixelFromDepth(), and NSPlanarFromDepth() to extract info from an NSWindowDepth. Use NSBestDepth() to compute window depths. NSBestDepth() will try to accomodate all the parameters (match or better); if there are multiple matches, it gives the closest, with matching colorSpace first, then bps, then planar, then bpp. bpp is "bits per pixel"; 0 indicates default (same as the number of bits per plane, either bps or bps * NSNumberOfColorComponents()); other values maybe used as hints to provide backing stores of different configuration; for instance, 8 bit color. exactMatch is optional and indicates whether all the parameters matched exactly.
*/
typedef int NSWindowDepth;
APPKIT_EXTERN NSWindowDepth NSBestDepth (NSString *colorSpace, int bps, int bpp, BOOL planar, BOOL *exactMatch);
APPKIT_EXTERN BOOL NSPlanarFromDepth (NSWindowDepth depth);
APPKIT_EXTERN NSString *NSColorSpaceFromDepth (NSWindowDepth depth);
APPKIT_EXTERN int NSBitsPerSampleFromDepth (NSWindowDepth depth);
APPKIT_EXTERN int NSBitsPerPixelFromDepth (NSWindowDepth depth);
APPKIT_EXTERN int NSNumberOfColorComponents (NSString *colorSpaceName);
APPKIT_EXTERN const NSWindowDepth *NSAvailableWindowDepths (void); /* 0 terminated */


/* Standard gray values for the 2-bit deep grayscale colorspace.
*/
APPKIT_EXTERN const float NSWhite;
APPKIT_EXTERN const float NSLightGray;
APPKIT_EXTERN const float NSDarkGray;
APPKIT_EXTERN const float NSBlack;


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
APPKIT_EXTERN void NSRectFillList(const NSRect *rects, int count);
APPKIT_EXTERN void NSRectFillListWithGrays(const NSRect *rects, const float *grays, int num);
APPKIT_EXTERN void NSRectFillListWithColors(const NSRect *rects, NSColor **colors, int num);
APPKIT_EXTERN void NSRectFillUsingOperation(NSRect aRect, NSCompositingOperation op);
APPKIT_EXTERN void NSRectFillListUsingOperation(const NSRect *rects, int count, NSCompositingOperation op);
APPKIT_EXTERN void NSRectFillListWithColorsUsingOperation(const NSRect *rects, NSColor **colors, int num, NSCompositingOperation op);
APPKIT_EXTERN void NSFrameRect(NSRect aRect);
APPKIT_EXTERN void NSFrameRectWithWidth(NSRect aRect, float frameWidth);
APPKIT_EXTERN void NSFrameRectWithWidthUsingOperation(NSRect aRect, float frameWidth, NSCompositingOperation op);
APPKIT_EXTERN void NSRectClip(NSRect aRect);
APPKIT_EXTERN void NSRectClipList(const NSRect *rects, int count);
APPKIT_EXTERN NSRect NSDrawTiledRects(NSRect boundsRect, NSRect clipRect, const NSRectEdge *sides, const float *grays, int count);
APPKIT_EXTERN void NSDrawGrayBezel(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDrawGroove(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDrawWhiteBezel(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDrawButton(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSEraseRect(NSRect aRect);
APPKIT_EXTERN NSColor *NSReadPixel(NSPoint passedPoint);
APPKIT_EXTERN void NSDrawBitmap(NSRect rect, int width, int height, int bps, int spp, int bpp, int bpr, BOOL isPlanar, BOOL hasAlpha, NSString *colorSpaceName, const unsigned char *const data[5]);
APPKIT_EXTERN void NSCopyBits(int srcGState, NSRect srcRect, NSPoint destPoint);
APPKIT_EXTERN void NSHighlightRect(NSRect aRect);
APPKIT_EXTERN void NSBeep(void);
APPKIT_EXTERN void NSCountWindows(int *count);
APPKIT_EXTERN void NSWindowList(int size, int list[]);
APPKIT_EXTERN void NSCountWindowsForContext(int context, int *count);
APPKIT_EXTERN void NSWindowListForContext(int context, int size, int list[]);

/* gets performance stats about window server memory usage */
APPKIT_EXTERN int NSGetWindowServerMemory(int context, int *virtualMemory, int *windowBackingMemory, NSString **windowDumpString);

APPKIT_EXTERN NSRect NSDrawColorTiledRects(NSRect boundsRect, NSRect clipRect, const NSRectEdge *sides, NSColor **colors, int count);
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
APPKIT_EXTERN void NSDisableScreenUpdates(void)	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN void NSEnableScreenUpdates(void)	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

/* Runs one of the standard system animation effects (display and sound).
** 'centerLocation' represents the center, in screen coordinates, to show the effect.
** 'size' specifies how big the effect should be.  Use NSZeroSize to get the default size.
** 'animationDelegate' is optionally, an object that wants to know when the effect has completed.
** 'didEndSelector' will be invoked in the animationDelegate when the animation has completed.
**  
** The didEndSelector should have the following signature:
** 	- (void)animationEffectDidEnd:(void *)contextInfo;
*/

typedef enum _NSAnimationEffect {
	// The default effect used to indicate removal of an item from a collection, 
	// such as toolbar (indicates removal, without destroying the underlying data).
	NSAnimationEffectDisappearingItemDefault = 0,

	// An effect showing a puff of smoke.
	NSAnimationEffectPoof = 10
} NSAnimationEffect;

APPKIT_EXTERN void NSShowAnimationEffect(NSAnimationEffect animationEffect, NSPoint centerLocation, NSSize size, id animationDelegate, SEL didEndSelector, void *contextInfo) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#endif

/*
 *  CGDirectDisplay.h
 *  CoreGraphics
 *
 *  Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 */
#ifndef __CGDIRECT_DISPLAY_H__
#define __CGDIRECT_DISPLAY_H__ 1

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGGeometry.h>
#include <CoreGraphics/CGError.h>
#include <CoreGraphics/CGContext.h>
#include <CoreFoundation/CoreFoundation.h>
#include <stdint.h>
#include <AvailabilityMacros.h>
/*
 * The following construct is present to avoid problems with some Apple tools.
 * API in this module is not available in Mac OS Classic variations!
 */
#ifndef __MACOS_CLASSIC__
#include <mach/boolean.h>
#else
typedef int boolean_t;
#endif

CG_EXTERN_C_BEGIN

typedef uint32_t CGDirectDisplayID;
typedef struct _CGDirectPaletteRef * CGDirectPaletteRef;
typedef uint32_t CGDisplayCount;
typedef uint32_t CGTableCount;
typedef int32_t	CGDisplayCoord;
typedef uint8_t CGByteValue;
typedef uint32_t CGOpenGLDisplayMask;
typedef uint32_t CGBeamPosition;
typedef int32_t CGMouseDelta;
typedef double CGRefreshRate;
typedef uint32_t CGCaptureOptions;

typedef CGError CGDisplayErr;
#define CGDisplayNoErr kCGErrorSuccess


#define kCGNullDirectDisplay ((CGDirectDisplayID)0)

/* Returns the display ID of the current main display */
CG_EXTERN CGDirectDisplayID CGMainDisplayID(void) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#define kCGDirectMainDisplay CGMainDisplayID()

/*
 * Mechanisms used to find screen IDs
 * An array length (maxDisplays) and array of CGDirectDisplayIDs are passed in.
 * Up to maxDisplays of the array are filled in with the displays meeting the
 * specified criteria.  The actual number of displays filled in is returned in
 * dspyCnt.
 *
 * If the dspys array is NULL, maxDisplays is ignored, and *dspyCnt is filled
 * in with the number of displays meeting the function's requirements.
 */
CG_EXTERN CGDisplayErr CGGetDisplaysWithPoint(CGPoint point,
                             CGDisplayCount maxDisplays,
                             CGDirectDisplayID * dspys,
                             CGDisplayCount * dspyCnt) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

CG_EXTERN CGDisplayErr CGGetDisplaysWithRect(CGRect rect,
                            CGDisplayCount maxDisplays,
                            CGDirectDisplayID * dspys,
                            CGDisplayCount * dspyCnt) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

CG_EXTERN CGDisplayErr CGGetDisplaysWithOpenGLDisplayMask(CGOpenGLDisplayMask mask,
                            CGDisplayCount maxDisplays,
                            CGDirectDisplayID * dspys,
                            CGDisplayCount * dspyCnt) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
                            
/*
 * Get lists of displays.  Use this to determine display IDs
 *
 * If the activeDspys array is NULL, maxDisplays is ignored, and *dspyCnt is filled
 * in with the number of displays meeting the function's requirements.
 *
 * The first display returned in the list is the main display,
 * the one with the menu bar.
 * When mirroring, this will be the largest drawable display in the mirror,
 * set, or if all are the same size, the one with the deepest pixel depth.
 */
CG_EXTERN CGDisplayErr CGGetActiveDisplayList(CGDisplayCount maxDisplays,
                             CGDirectDisplayID * activeDspys,
                             CGDisplayCount * dspyCnt) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * With hardware mirroring, a display may be on-line,
 * but not necessarily active, or drawable.
 * Programs which manipulate display settings such as the
 * palette or gamma tables need access to all displays in use,
 * including hardware mirrors which are not drawable.
 */
CG_EXTERN CGDisplayErr CGGetOnlineDisplayList(CGDisplayCount maxDisplays,
                                    CGDirectDisplayID * onlineDspys,
                                    CGDisplayCount * dspyCnt) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Map a display to an OpenGL display mask; returns 0 on invalid display */
CG_EXTERN CGOpenGLDisplayMask CGDisplayIDToOpenGLDisplayMask(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Map an OpenGL display mask to a display.
 * Returns kCGNullDirectDisplay if a bit doesn't
 * match a display.
 * Passing in multiple bits results in an arbitrary match. 
 */
CG_EXTERN CGDirectDisplayID  CGOpenGLDisplayMaskToDisplayID(CGOpenGLDisplayMask mask) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* Return screen size and origin in global coords; Empty rect if display is invalid */
CG_EXTERN CGRect CGDisplayBounds(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

CG_EXTERN size_t CGDisplayPixelsWide(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CG_EXTERN size_t CGDisplayPixelsHigh(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Display mode selection
 * Display modes are represented as CFDictionaries
 * All dictionaries and arrays returned via these mechanisms are
 * owned by the framework and should not be released.  The framework
 * will not release them out from under your application.
 *
 * Values associated with the following keys are CFNumber types.
 * With CFNumberGetValue(), use kCFNumberLongType for best results.
 * kCGDisplayRefreshRate encodes a double value, so to get the fractional
 * refresh rate use kCFNumberDoubleType.
 */
 
/*
 * Keys used in mode dictionaries.  Source C strings shown won't change.
 * Some CFM environments cannot import data variables, and so
 * the definitions are provided directly.
 *
 * These keys are used only within the scope of the mode dictionaries,
 * so further uniquing, as by prefix, of the source string is not needed.
 */
#define kCGDisplayWidth				CFSTR("Width")
#define kCGDisplayHeight			CFSTR("Height")
#define kCGDisplayMode				CFSTR("Mode")
#define kCGDisplayBitsPerPixel			CFSTR("BitsPerPixel")
#define kCGDisplayBitsPerSample			CFSTR("BitsPerSample")
#define kCGDisplaySamplesPerPixel		CFSTR("SamplesPerPixel")
#define kCGDisplayRefreshRate			CFSTR("RefreshRate")
#define kCGDisplayModeUsableForDesktopGUI	CFSTR("UsableForDesktopGUI")
#define kCGDisplayIOFlags			CFSTR("IOFlags")
#define kCGDisplayBytesPerRow			CFSTR("kCGDisplayBytesPerRow")
#define kCGIODisplayModeID          CFSTR("IODisplayModeID")

/*
 * Keys to describe optional properties of display modes.
 *
 * The key will only be present if the property applies,
 * and will be associated with a value of kCFBooleanTrue.
 * Keys not relevant to a particular display mode will not
 * appear in the mode dictionary.
 *
 * These strings must remain unchanged in future releases, of course.
 */

/* Set if display mode doesn't need a confirmation dialog to be set */
#define kCGDisplayModeIsSafeForHardware		CFSTR("kCGDisplayModeIsSafeForHardware")

/* The following keys reflect interesting bits of the IOKit display mode flags */
#define kCGDisplayModeIsInterlaced		CFSTR("kCGDisplayModeIsInterlaced") 
#define kCGDisplayModeIsStretched		CFSTR("kCGDisplayModeIsStretched")
#define kCGDisplayModeIsTelevisionOutput	CFSTR("kCGDisplayModeIsTelevisionOutput" )


/*
 * Return a CFArray of CFDictionaries describing all display modes.
 * Returns NULL if the display is invalid.
 */
CG_EXTERN CFArrayRef CGDisplayAvailableModes(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
/*
 * Try to find a display mode of specified depth with dimensions equal or greater than
 * specified.
 * If no depth match is found, try for the next larger depth with dimensions equal or greater
 * than specified.  If no luck, then just return the current mode.
 *
 * exactmatch, if not NULL, is set to 'true' if an exact match in width, height, and depth is found,
 * and 'false' otherwise.
 *
 * CGDisplayBestModeForParametersAndRefreshRateWithProperty searches the list, looking for
 * display modes with the specified property.  The property should be one of:
 *	kCGDisplayModeIsSafeForHardware;
 *	kCGDisplayModeIsInterlaced;
 *	kCGDisplayModeIsStretched;
 *	kCGDisplayModeIsTelevisionOutput
 *	
 * Returns NULL if display is invalid.
 */
CG_EXTERN CFDictionaryRef CGDisplayBestModeForParameters(CGDirectDisplayID display, size_t bitsPerPixel, size_t width, size_t height, boolean_t * exactMatch) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

CG_EXTERN CFDictionaryRef CGDisplayBestModeForParametersAndRefreshRate(CGDirectDisplayID display, size_t bitsPerPixel, size_t width, size_t height, CGRefreshRate refresh, boolean_t * exactMatch) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

CG_EXTERN CFDictionaryRef CGDisplayBestModeForParametersAndRefreshRateWithProperty(CGDirectDisplayID display, size_t bitsPerPixel, size_t width, size_t height, CGRefreshRate refresh, CFStringRef property, boolean_t * exactMatch) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*
 * Return a CFDictionary describing the current display mode.
 * Returns NULL if display is invalid.
 */
CG_EXTERN CFDictionaryRef CGDisplayCurrentMode(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
/*
 * Switch display mode.  Note that after switching, 
 * display parameters and addresses may change.
 * The selected display mode persists for the life of the program, and automatically
 * reverts to the permanent setting made by Preferences when the program terminates.
 * The mode dictionary passed in must be a dictionary vended by other CGDirectDisplay
 * APIs such as CGDisplayBestModeForParameters() and CGDisplayAvailableModes().
 *
 * The mode dictionary passed in must be a dictionary vended by other CGDirectDisplay
 * APIs such as CGDisplayBestModeForParameters() and CGDisplayAvailableModes().
 *
 * When changing display modes of displays in a mirroring set, other displays in
 * the mirroring set will be set to a display mode capable of mirroring the bounds
 * of the largest display being explicitly set. 
 */
CG_EXTERN CGDisplayErr CGDisplaySwitchToMode(CGDirectDisplayID display, CFDictionaryRef mode) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/* Query parameters for current mode */
CG_EXTERN size_t CGDisplayBitsPerPixel(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CG_EXTERN size_t CGDisplayBitsPerSample(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CG_EXTERN size_t CGDisplaySamplesPerPixel(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CG_EXTERN size_t CGDisplayBytesPerRow(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Set a display gamma/transfer function from a formula specifying
 * min and max values and a gamma for each channel.
 * Gamma values must be greater than 0.0.
 * To get an antigamma of 1.6, one would specify a value of (1.0 / 1.6)
 * Min values must be greater than or equal to 0.0 and less than 1.0.
 * Max values must be greater than 0.0 and less than or equal to 1.0.
 * Out of range values, or Max greater than or equal to Min result
 * in a kCGSRangeCheck error.
 *
 * Values are computed by sampling a function for a range of indices from 0 through 1:
 *	value = Min + ((Max - Min) * pow(index, Gamma))
 * The resulting values are converted to a machine specific format
 * and loaded into hardware.
 */
typedef float CGGammaValue;
                                              
CG_EXTERN CGDisplayErr CGSetDisplayTransferByFormula(CGDirectDisplayID display,
                                    CGGammaValue redMin,
                                    CGGammaValue redMax,
                                    CGGammaValue redGamma,
                                    CGGammaValue greenMin,
                                    CGGammaValue greenMax,
                                    CGGammaValue greenGamma,
                                    CGGammaValue blueMin,
                                    CGGammaValue blueMax,
                                    CGGammaValue blueGamma) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
                                              
CG_EXTERN CGDisplayErr CGGetDisplayTransferByFormula(CGDirectDisplayID display,
                                    CGGammaValue *redMin,
                                    CGGammaValue *redMax,
                                    CGGammaValue *redGamma,
                                    CGGammaValue *greenMin,
                                    CGGammaValue *greenMax,
                                    CGGammaValue *greenGamma,
                                    CGGammaValue *blueMin,
                                    CGGammaValue *blueMax,
                                    CGGammaValue *blueGamma) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
/*
 * Returns the capacity, or nunber of entries, in the camma table for the specified
 * display.  If 'display' is invalid, returns 0.
 */
CG_EXTERN CGTableCount CGDisplayGammaTableCapacity(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 * Set a display gamma/transfer function using tables of data for each channel.
 * Values within each table should have values in the range of 0.0 through 1.0.
 * The same table may be passed in for red, green, and blue channels. 'tableSize'
 * indicates the number of entries in each table.
 * The tables are interpolated as needed to generate the number of samples needed
 * by hardware.
 */
CG_EXTERN CGDisplayErr CGSetDisplayTransferByTable(CGDirectDisplayID display,
                                  CGTableCount tableSize,
                                  const CGGammaValue  *redTable,
                                  const CGGammaValue  *greenTable,
                                  const CGGammaValue  *blueTable) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Get transfer tables.  Capacity should contain the number of samples each
 * array can hold, and *sampleCount is filled in with the number of samples
 * actually copied in.
 */
CG_EXTERN CGDisplayErr CGGetDisplayTransferByTable(CGDirectDisplayID display,
                                  CGTableCount capacity,
                                  CGGammaValue  *redTable,
                                  CGGammaValue  *greenTable,
                                  CGGammaValue  *blueTable,
                                  CGTableCount *sampleCount) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/* As a convenience, allow setting of the gamma table by byte values */
CG_EXTERN CGDisplayErr CGSetDisplayTransferByByteTable(CGDirectDisplayID display,
                                      CGTableCount tableSize,
                                      const CGByteValue  *redTable,
                                      const CGByteValue  *greenTable,
                                      const CGByteValue  *blueTable) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/* Restore gamma tables of system displays to the user's ColorSync specified values */
CG_EXTERN void CGDisplayRestoreColorSyncSettings(void) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Options used with CGDisplayCaptureWithOptions and CGCaptureAllDisplaysWithOptions
 */
enum {
    kCGCaptureNoOptions = 0,	/* Default behavior */
    kCGCaptureNoFill = (1 << 0)	/* Disables fill with black on display capture */
};

/* Display capture and release */
CG_EXTERN boolean_t CGDisplayIsCaptured(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CG_EXTERN CGDisplayErr CGDisplayCapture(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CG_EXTERN CGDisplayErr CGDisplayCaptureWithOptions(CGDirectDisplayID display, CGCaptureOptions options) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
CG_EXTERN CGDisplayErr CGDisplayRelease(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Capture all displays; this has the nice effect of providing an immersive
 * environment, and preventing other apps from trying to adjust themselves
 * to display changes only needed by your app.
 */
CG_EXTERN CGDisplayErr CGCaptureAllDisplays(void) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
CG_EXTERN CGDisplayErr CGCaptureAllDisplaysWithOptions(CGCaptureOptions options) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 * Release all captured displays, and restore the display modes to the
 * user's preferences.  May be used in conjunction with CGDisplayCapture()
 * or CGCaptureAllDisplays().
 */
CG_EXTERN CGDisplayErr CGReleaseAllDisplays(void) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Returns CoreGraphics raw shield window ID or NULL if not shielded
 * This value may be used with drawing surface APIs.
 */
CG_EXTERN uint32_t CGShieldingWindowID(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Returns the window level used for the shield window.
 * This value may be used with Cocoa windows to position the
 * Cocoa window in the same window level as the shield window.
 */
CG_EXTERN int32_t CGShieldingWindowLevel(void) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Returns base address of display or NULL for an invalid display.
 * If the display has not been captured, the returned address may refer
 * to read-only memory.
 */
CG_EXTERN void * CGDisplayBaseAddress(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;
/*
 * return address for X,Y in global coordinates;
 *	(0,0) represents the upper left corner of the main display.
 * returns NULL for an invalid display or out of bounds coordinates
 * If the display has not been captured, the returned address may refer
 * to read-only memory.
 */
CG_EXTERN void * CGDisplayAddressForPosition(CGDirectDisplayID display, CGDisplayCoord x, CGDisplayCoord y) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/* Mouse Cursor controls */
CG_EXTERN CGDisplayErr CGDisplayHideCursor(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;	/* increments hide cursor count */
CG_EXTERN CGDisplayErr CGDisplayShowCursor(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;	/* decrements hide cursor count  */

/*
 * Move the cursor to the specified point relative to the display origin
 * (the upper left corner of the display).  Returns CGDisplayNoErr on success.
 * No events are generated as a result of this move.
 * Points that would lie outside the desktop are clipped to the desktop.
 */
CG_EXTERN CGDisplayErr CGDisplayMoveCursorToPoint(CGDirectDisplayID display, CGPoint point) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Report the mouse position change associated with the last mouse move event
 * recieved by this application.
 */
CG_EXTERN void CGGetLastMouseDelta( CGMouseDelta * deltaX, CGMouseDelta * deltaY ) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Palette controls (8 bit pseudocolor only) */

/*
 * Returns TRUE if the current display mode supports palettes.
 * Display must not be a hardware mirror of another, and should
 * have a depth of 8 bits per pixel for this to return TRUE.
 */
CG_EXTERN boolean_t CGDisplayCanSetPalette(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Set a palette.  The current gamma function is applied to the palette
 * elements before being loaded into hardware.  The display must not be
 * a hardware mirror of another, and should have a depth of 8 bits per pixel.
 * Setting the palette on the active, or primary display in a hardware
 * mirroring set affects all displays in that set.
 */
CG_EXTERN CGDisplayErr CGDisplaySetPalette(CGDirectDisplayID display, const CGDirectPaletteRef palette) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Wait until the beam position is outside the range specified by upperScanLine and lowerScanLine.
 * Note that if upperScanLine and lowerScanLine encompass the entire display height,
 * the function returns an error.
 * lowerScanLine must be greater than or equal to upperScanLine.
 *
 * Some display systems may not conventional video vertical and horizontal sweep in painting.
 * These displays report a kCGDisplayRefreshRate of 0 in the CFDictionaryRef returned by
 * CGDisplayCurrentMode().  On such displays, this function returns at once.
 *
 * Some drivers may not implement support for this mechanism.
 * On such displays, this function returns at once.
 *
 * Returns CGDisplayNoErr on success, and an error if display or upperScanLine and
 * lowerScanLine are invalid.
 *
 * The app should set the values of upperScanLine and lowerScanLine to allow enough lead time
 * for the drawing operation to complete.  A common strategy is to wait for the beam to pass
 * the bottom of the drawing area, allowing almost a full vertical sweep period to perform drawing.
 * To do this, set upperScanLine to 0, and set lowerScanLine to the bottom of the bounding box:
 *	lowerScanLine = (CGBeamPosition)(cgrect.origin.y + cgrect.size.height);
 *
 * IOKit may implement this as a spin-loop on the beam position call used for CGDisplayBeamPosition().
 * On such system the function is CPU bound, and subject to all the usual scheduling pre-emption.
 * In particular, attempting to wait for the beam to hit a specific scanline may be an exercise in frustration.
 *
 * These functions are advisary in nature, and depend on IOKit and hardware specific drivers to implement
 * support. If you need extremely precise timing, or access to vertical blanking interrupts,
 * you should consider writing a device driver to tie into hardware-specific capabilities.
 */
CG_EXTERN CGDisplayErr CGDisplayWaitForBeamPositionOutsideLines( CGDirectDisplayID display,
                                                       CGBeamPosition upperScanLine,
                                                       CGBeamPosition lowerScanLine ) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Returns the current beam position on the display.  If display is invalid,
 * or the display does not implement conventional video vertical and horizontal
 * sweep in painting, or the driver does not implement this functionality, 0 is returned.
 */
CG_EXTERN CGBeamPosition CGDisplayBeamPosition( CGDirectDisplayID display ) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 * Obtain a CGContextRef suitable for drawing to a captured display.
 *
 * Returns a drawing context suitable for use on the display device.
 * The context is owned by the device, and should not be released by
 * the caller.
 *
 * The context remains valid while the display is captured, and the
 * display configuration is unchanged.  Releasing the captured display
 * or reconfiguring the display invalidates the drawing context.
 *
 * An application may register a display reconfiguration callback to determine
 * when the display configuration is changing via CGRegisterDisplayReconfigurationProc().
 * 
 * After a display configuration change, or on capturing a display, call this
 * function to obtain a current drawing context.
 *
 * If the display has not been captured, this function returns NULL.
 */
CG_EXTERN CGContextRef CGDisplayGetDrawingContext(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CG_EXTERN_C_END

#endif /* __CGDIRECT_DISPLAY_H__ */

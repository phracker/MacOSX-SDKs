/*
 *  CGDisplayConfiguration.h
 *  CoreGraphics
 *
 *  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 */
#ifndef __CGDISPLAY_CONFIGURATION_H__
#define __CGDISPLAY_CONFIGURATION_H__ 1

#include <IOKit/IOKitLib.h>
#include <CoreGraphics/CGDirectDisplay.h>
#include <AvailabilityMacros.h>

CG_EXTERN_C_BEGIN
/*
 * Display reconfiguration process.
 * Call CGBeginDisplayConfiguration to start.
 * Make all desired changes, for all displays.
 * Commit the changes using CGPerformDisplayConfiguration(), or cancel with
 * CGCancelDisplayConfiguration()
 *
 * The resulting layout will be adjusted so as to remove gaps or overlaps from
 * the requested layout, if needed.
 */
typedef struct _CGDisplayConfigRef * CGDisplayConfigRef;

/* Get a new CGDisplayConfigRef */
CGError CGBeginDisplayConfiguration(CGDisplayConfigRef *pConfigRef);

/*
 * Set the origin point for a display
 *
 * Note that setting the origin of a display which is mirroring
 * another display will remove that display from any mirroring set.
 *
 * Any display whose origin is not explicitly set in a reconfiguration
 * will be repositioned to a location as close as possible to it's
 * current location without overlapping or leaving a gap between displays.
 *
 * The actual position a display is placed at will be as close as possible
 * to the requested location without overlapping or leaving a gap between
 * displays.
 */
CGError CGConfigureDisplayOrigin(CGDisplayConfigRef configRef,
                                 CGDirectDisplayID display,
                                 CGDisplayCoord x,
                                 CGDisplayCoord y);

/*
 * Set the display mode
 *
 * The mode dictionary passed in must be a dictionary vended by other CGDirectDisplay
 * APIs such as CGDisplayBestModeForParameters() and CGDisplayAvailableModes().
 *
 * When changing display modes of displays in a mirroring set, other displays in
 * the mirroring set whose mode is not explicitly changed will be set to a display
 * mode capable of mirroring the bounds of the largest display being explicitly set. 
 */
CGError CGConfigureDisplayMode(CGDisplayConfigRef configRef,
                                CGDirectDisplayID display,
                                CFDictionaryRef mode);

/*
 * Enable or disable stereo operation.
 *
 * Note that the system normally detects the presence of a stereo window,
 * and will automatically switch a display containing a stereo window to
 * stereo operation.  This function provides a mechanism to force a display
 * to stereo operation, and to set options (blue line sync signal) when in
 * stereo operation.
 *
 * Returns kCGErrorSuccess on success.
 * Returns kCGErrorRangeCheck if the display does not support
 * the stereo operation settings requested.
 *
 * On success, the display resolution, mirroring mode, and
 * available display modes may change, due to hardware-specific
 * capabilities and limitations.
 * Please check settings to verify that they are appropriate for
 * your application.
 *
 * When in stereo operation, a display may need to generate a special stereo
 * sync signal as part of the video output.  The sync signal consists of a blue
 * line which occupies the first 25% of the last scanline for the left eye view,
 * and the first 75% of the last scanline for the right eye view.  The remainder
 * of the scanline is black.   It may be set using the forceBlueLine option.
 */
CGError CGConfigureDisplayStereoOperation(CGDisplayConfigRef configRef, CGDirectDisplayID display, boolean_t stereo, boolean_t forceBlueLine);

/*
 * Make a display a mirror of masterDisplay.
 *
 * Use a CGDirectDisplayID of kCGNullDirectDisplay for the masterDisplay to disable
 * mirroring.
 * Use a CGDirectDisplayID of CGMainDisplayID() for the masterDisplay to mirror
 * the main display.
 *
 * Mirroring requests will be filled with hardware mirroring when possible,
 * at the device driver's choice.  Displays will be matted as appropriate,
 * using either hardware or software matte generation, again at the device driver's choice.
 *
 * Note that when hardware mirroring is in effect, the device driver may bind the hardware
 * accelerator, drawing engine, and 3D engine to any one of the displays in the hardware
 * mirroring set.  That display will become the active display for drawing purposes in that
 * hardware mirroring set.  Use CGDisplayPrimaryDisplay() to determine the correct display
 * device to process drawing operations in a hardware mirroring set.
 *
 * An app that uses CGGetActiveDisplayList() to determine the proper displays to draw to
 * (All Carbon and Cocoa apps using windows and/or DrawSprocket fall into this class)
 * will automatically get the correct behavior.
 */
CGError CGConfigureDisplayMirrorOfDisplay(CGDisplayConfigRef configRef,
                                                     CGDirectDisplayID display,
                                                     CGDirectDisplayID masterDisplay);

/* Cancel a reconfiguration operation, discarding the configRef */
CGError CGCancelDisplayConfiguration(CGDisplayConfigRef configRef);

/*
 * Perform the requested reconfigurations and discard the configRef
 *
 * A configuration change can apply for the life of an app, the life of a login session, or
 * permanently. If a request is made to make a change permanent, and the change
 * cannot be supported by the Aqua UI (resolution and pixel depth constraints apply),
 * then the configuration  change is demoted to lasting the session.
 *
 * A permanent configuration change also becomes the current session's
 * configuration.
 *
 * When the system reverts confgurations at app termination, the
 * configuration always reverts to the session or permanent configuration setting.
 *
 * When the system reverts confgurations at session termination, the
 * configuration always reverts to the permanent configuration setting.
 *
 * This operation may fail if:
 *     An unsupported display mode is requested
 *     Another app is running in full-screen mode
 *
 */
enum {
    kCGConfigureForAppOnly = 0,
    kCGConfigureForSession = 1,
    kCGConfigurePermanently = 2
};
typedef u_int32_t CGConfigureOption;

CGError CGCompleteDisplayConfiguration( CGDisplayConfigRef configRef, CGConfigureOption option );

/* Restore the permanent display configuration from the user's display preferences settings */
void CGRestorePermanentDisplayConfiguration(void);

/*
 * Applications may want to register for notifications of display changes.
 *
 * Display changes are reported via a callback mechanism.
 *
 * Callbacks are invoked when the app is listening for events,
 * on the event processing thread, or from within the display
 * reconfiguration function when in the program that is driving the
 * reconfiguration.
 *
 * Callbacks should avoid attempting to change display configurations,
 * and should not raise exceptions or perform a non-local return such as
 * calling longjmp().
 *
 * Before display reconfiguration, a callback fires to inform
 * applications of a pending configuration change. The callback runs
 * once for each on-line display.  The flags passed in are set to
 * kCGDisplayBeginConfigurationFlag.  This callback does not
 * carry other per-display information, as details of how a
 * reconfiguration affects a particular device rely on device-specific
 * behaviors which may not be exposed by a device driver.
 *
 * After display reconfiguration, at the time the callback function
 * is invoked, all display state reported by CoreGraphics, QuickDraw,
 * and the Carbon Display Manager API will be up to date.  This callback
 * runs after the Carbon Display Manager notification callbacks.
 * The callback runs once for each added, removed, and currently
 * on-line display.  Note that in the case of removed displays, calls into
 * the CoreGraphics API with the removed display ID will fail.
 */

enum {
    kCGDisplayBeginConfigurationFlag = (1 << 0), /* Set in pre-reconfiguration callback */
    kCGDisplayMovedFlag              = (1 << 1), /* post-reconfiguration callback flag */
    kCGDisplaySetMainFlag            = (1 << 2), /* post-reconfiguration callback flag */
    kCGDisplaySetModeFlag            = (1 << 3), /* post-reconfiguration callback flag */
    kCGDisplayAddFlag                = (1 << 4), /* post-reconfiguration callback flag */
    kCGDisplayRemoveFlag             = (1 << 5), /* post-reconfiguration callback flag */
    kCGDisplayEnabledFlag            = (1 << 8), /* post-reconfiguration callback flag */
    kCGDisplayDisabledFlag           = (1 << 9), /* post-reconfiguration callback flag */
    kCGDisplayMirrorFlag             = (1 << 10),/* post-reconfiguration callback flag */
    kCGDisplayUnMirrorFlag           = (1 << 11) /* post-reconfiguration callback flag */
};
typedef u_int32_t CGDisplayChangeSummaryFlags;

typedef void(*CGDisplayReconfigurationCallBack)(CGDirectDisplayID display,
                                                CGDisplayChangeSummaryFlags flags,
                                                void *userInfo);

/*
 * Register and remove a display reconfiguration callback procedure
 * The userInfo argument is passed back to the callback procedure each time
 * it is invoked.
 */
CGError CGDisplayRegisterReconfigurationCallback(CGDisplayReconfigurationCallBack proc, void *userInfo) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
CGError CGDisplayRemoveReconfigurationCallback(CGDisplayReconfigurationCallBack proc, void *userInfo) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 * Specialized configuration changes should be done outside of the
 * scope of a CGBeginDisplayConfiguration/CGCompleteDisplayConfiguration
 * pair, as they may alter things such as the available display modes
 * which a normal reconfiguration sequence might assume are invariant.
 */
/*
 * Enable or disable stereo operation.
 *
 * Note that the system normally detects the presence of a stereo window,
 * and will automatically switch a display containing a stereo window to
 * stereo operation.  This function provides a mechanism to force a display
 * to stereo operation, and to set options (blue line sync signal) when in
 * stereo operation.
 *
 * Returns kCGErrorSuccess on success.
 * Returns kCGErrorRangeCheck if the display does not support
 * the stereo operation settings requested.
 *
 * On success, the display resolution, mirroring mode, and
 * available display modes may change, due to hardware-specific
 * capabilities and limitations.
 * Please check settings to verify that they are appropriate for
 * your application.
 *
 * When in stereo operation, a display may need to generate a special stereo
 * sync signal as part of the video output.  The sync signal consists of a blue
 * line which occupies the first 25% of the last scanline for the left eye view,
 * and the first 75% of the last scanline for the right eye view.  The remainder
 * of the scanline is black.   It may be set using the forceBlueLine option.
 *
 * A configuration change can apply for the life of an app, the life of a login session, or
 * permanently. If a request is made to make a change permanent, and the change
 * cannot be supported by the Aqua UI (resolution and pixel depth constraints apply),
 * then the configuration  change is demoted to lasting the session.
 *
 * A permanent configuration change also becomes the current session's
 * configuration.
 *
 * When the system reverts configurations at app termination, the
 * configuration always reverts to the session or permanent configuration setting.
 *
 * When the system reverts configurations at session termination, the
 * configuration always reverts to the permanent configuration setting.
 */
CGError CGDisplaySetStereoOperation(CGDirectDisplayID display, boolean_t stereo, boolean_t forceBlueLine, CGConfigureOption option);

/*
 * These APIs allow applications and higher level frameworks
 * such as DrawSprocket to determine interesting properties
 * of displays, such as if a display is built-in, if a display
 * is the main display, if a display is being mirrored, which
 * display in a hardware mirror set is bound to the graphics
 * accelerator (important for games!) and so on.
 *
 * An app that uses CGGetActiveDisplayList() to determine the
 * proper displays to draw to (All Carbon and Cocoa apps using
 * windows and/or DrawSprocket fall into this class) will
 * automatically get the correct behavior without using these APIs.
 * These APIs are primarily of interest to specialized applications
 * such as movie players, integrated TV/video graphics utilities,
 * and similar specialized applications.
 */

/* True if the display is connected, awake, and drawable */
boolean_t CGDisplayIsActive(CGDirectDisplayID display);

/* True if the display is asleep and therefore not drawable */
boolean_t CGDisplayIsAsleep(CGDirectDisplayID display);

/*
 * True if the display is valid, with a monitor connected
 * (support for hot plugging of monitors)
 */
boolean_t CGDisplayIsOnline(CGDirectDisplayID display);

/* True if the display is the current main display */
boolean_t CGDisplayIsMain(CGDirectDisplayID display);

/* True if the display is built in, such as the internal display in portables */
boolean_t CGDisplayIsBuiltin(CGDirectDisplayID display);

/* True if the display is in a mirroring set */
boolean_t CGDisplayIsInMirrorSet(CGDirectDisplayID display);

/* True if the display is always in a mirroring set, and cannot be unmirrored */
boolean_t CGDisplayIsAlwaysInMirrorSet(CGDirectDisplayID display);

/* True if the display is in a hardware mirroring set */
boolean_t CGDisplayIsInHWMirrorSet(CGDirectDisplayID display);

/* Returns display being mirrored, or kCGNullDirectDisplay if master or unmirrored */
CGDirectDisplayID CGDisplayMirrorsDisplay(CGDirectDisplayID display);

/* True if the display is using OpenGL acceleration */
boolean_t CGDisplayUsesOpenGLAcceleration(CGDirectDisplayID display);

/* True if the display is running in a stereo graphics mode */
boolean_t CGDisplayIsStereo(CGDirectDisplayID display);


/*
 * Returns the display bound to the hardware accelerator in a HW mirror set,
 * or 'display' if software mirrored or unmirrored
 */
CGDirectDisplayID CGDisplayPrimaryDisplay(CGDirectDisplayID display);

/*
 * Returns the logical unit, vendor ID, vendor model number,
 * and serial number for a display
 */
uint32_t CGDisplayUnitNumber(CGDirectDisplayID display);
uint32_t CGDisplayVendorNumber(CGDirectDisplayID display);
uint32_t CGDisplayModelNumber(CGDirectDisplayID display);
uint32_t CGDisplaySerialNumber(CGDirectDisplayID display);

/* Returns the IOKit service port for a display device */
io_service_t CGDisplayIOServicePort(CGDirectDisplayID display);

/*
 * Returns the size of the specified display in millimeters.
 *
 * If 'display' is not a valid display ID, the size returned has a width and height of 0.
 *
 * If EDID data for the display device is not available, the size is estimated based on
 * the device width and height in pixels from CGDisplayBounds(), with an assumed resolution
 * of 2.835 pixels/mm, or 72 DPI, a reasonable guess for displays predating EDID support.
 */
CGSize CGDisplayScreenSize(CGDirectDisplayID display) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CG_EXTERN_C_END

#endif /* __CGDISPLAY_CONFIGURATION_H__ */

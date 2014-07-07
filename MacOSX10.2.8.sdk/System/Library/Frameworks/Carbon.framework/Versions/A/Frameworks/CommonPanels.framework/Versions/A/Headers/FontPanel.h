/*
     File:       CommonPanels/FontPanel.h
 
     Contains:   Carbon Font Panel package Interfaces.
 
     Version:    CommonPanels-61~261
 
     Copyright:  © 2002 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __FONTPANEL__
#define __FONTPANEL__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __CARBON__
#include <Carbon/Carbon.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Font Panel-Related Events
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
 *  Discussion:
 *    Event classes
 */
enum {

  /*
   * Events related to font selection or handling.
   */
  kEventClassFont               = 'font'
};


/*
 *  Summary:
 *    Common command IDs
 */
enum {

  /*
   * The state of the Font Panel should be toggled, displaying it or
   * hiding it as necessary. If the user closes the Font Panel directly
   * from the window, the application will receive a
   * kEventFontPanelClosed event.
   */
  kHICommandShowHideFontPanel   = 'shfp'
};

/* Font Events */

/*
 *  Summary:
 *    Font events (kEventClassFont)
 *  
 *  Discussion:
 *    When the user closes the Font Panel, a kEventWindowClosed event
 *    will be detected by the Carbon event handler installed by the
 *    system. The system then notifies the application that the Font
 *    Panel has closed by posting a Carbon Event Manager event. This
 *    allows the application to update any menu items or other controls
 *    whose state may have to change because the Font Panel has closed.
 *    kEventWindowClosed has no parameters. When the user selects an
 *    item in the Font Panel, the system will send a
 *    kEventFontSelection event to the event target specified when the
 *    application called SetFontPanelInfo(). kEventFontSelection will
 *    contain parameters reflecting the current Font Panel selection in
 *    all supported formats. Font events are available after Mac OS X
 *    10.2 in the Carbon framework.
 */
enum {

  /*
   * The Font Panel has been closed. The application should update its
   * corresponding UI element (e.g., a menu item) accordingly.
   */
  kEventFontPanelClosed         = 1,

  /*
   * The user has specified font settings in the Font Panel. The
   * application can obtain these settings from the event, in which
   * they are stored as parameters. Not all parameters are guaranteed
   * to be present; the application should check for all those which it
   * recognizes and apply the ones found as appropriate to the target
   * text.
   */
  kEventFontSelection           = 2
};

/*
    Parameters for font events:

    kEventFontPanelClosed
        None.
        
    kEventFontSelection
        -->     kEventParamATSUFontID               typeATSUFontID
        -->     kEventParamATSUFontSize             typeATSUSize
        -->     kEventParamFMFontFamily             typeFMFontFamily
        -->     kEventParamFMFontSize               typeFMFontSize
        -->     kEventParamFontColor                typeFontColor
*/
enum {
  typeATSUFontID                = typeUInt32, /* ATSUI font ID.*/
  typeATSUSize                  = typeFixed, /* ATSUI font size.*/
  typeFMFontFamily              = typeSInt16, /* Font family reference.*/
  typeFMFontStyle               = typeSInt16, /* Quickdraw font style*/
  typeFMFontSize                = typeSInt16, /* Integer font size.*/
  typeFontColor                 = typeRGBColor, /* Font color spec (optional).*/
  kEventParamATSUFontID         = 'auid', /* typeATSUFontID*/
  kEventParamATSUFontSize       = 'ausz', /* typeATSUSize*/
  kEventParamFMFontFamily       = 'fmfm', /* typeFMFontFamily*/
  kEventParamFMFontStyle        = 'fmst', /* typeFMFontStyle*/
  kEventParamFMFontSize         = 'fmsz', /* typeFMFontSize*/
  kEventParamFontColor          = 'fclr' /* typeFontColor*/
};


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Other Font Panel Constants
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
Error codes (Font Panel codes in range [-8880,-8899]).
*/
enum {
  fontPanelShowErr              = -8880, /* Can't display the Font Panel.*/
  fontPanelSelectionStyleErr    = -8881, /* Bad font selection style info.*/
  fontPanelFontSelectionQDStyleVersionErr = -8882 /* Unsupported record version.*/
};

/*
Type of font information passed in SetFontPanelInfo(). If the client is
sending ATSUI style data, it specifies kFontSelectionATSUIType; if it is
sending Quickdraw style data, it specifies kFontSelectionQDType.
*/
enum {
  kFontSelectionATSUIType       = 'astl', /* Use ATSUIStyle collection.*/
  kFontSelectionQDType          = 'qstl' /* Use FontSelectionQDStyle record.*/
};

/*
Supported versions of the FontSelectionQDStyle record. Clients should always set
the <version> field to one of these values.
*/
enum {
  kFontSelectionQDStyleVersionZero = 0
};


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Font Panel Types
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
Record specifying the font information to be specified in the Font
Panel. This record is used if the client is sending Quickdraw style data
(i.e., it specified kFontSelectionQDType in SetFontPanelInfo()).
*/
struct FontSelectionQDStyle {
  UInt32              version;                /* Version number of struct.*/
  FMFontFamilyInstance  instance;             /* Font instance data.*/
  FMFontSize          size;                   /* Size of font in points.*/
  Boolean             hasColor;               /* true if color info supplied.*/
  UInt8               reserved;               /* Filler byte.*/
  RGBColor            color;                  /* Color specification for font.*/
};
typedef struct FontSelectionQDStyle     FontSelectionQDStyle;
typedef FontSelectionQDStyle *          FontSelectionQDStylePtr;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Font Panel Functions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
 *  FPIsFontPanelVisible()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
FPIsFontPanelVisible(void)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  FPShowHideFontPanel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FPShowHideFontPanel(void)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SetFontInfoForSelection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetFontInfoForSelection(
  OSType        iStyleType,
  UInt32        iNumStyles,
  void *        iStyles,
  HIObjectRef   iFPEventTarget)                               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __FONTPANEL__ */


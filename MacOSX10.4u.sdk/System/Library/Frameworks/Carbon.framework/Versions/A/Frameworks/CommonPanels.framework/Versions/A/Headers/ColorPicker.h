/*
     File:       CommonPanels/ColorPicker.h
 
     Contains:   Color Picker package Interfaces.
 
     Version:    CommonPanels-73.2~861
 
     Copyright:  © 1987-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __COLORPICKER__
#define __COLORPICKER__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

enum {
                                        /*Maximum small fract value, as long*/
  kMaximumSmallFract            = 0x0000FFFF
};

enum {
  kDefaultColorPickerWidth      = 383,
  kDefaultColorPickerHeight     = 238
};

typedef SInt16 DialogPlacementSpec;
enum {
  kAtSpecifiedOrigin            = 0,
  kDeepestColorScreen           = 1,
  kCenterOnMainScreen           = 2
};


/* These are for the flags field in the structs below (for example ColorPickerInfo). */
enum {
  kColorPickerDialogIsMoveable  = 1,
  kColorPickerDialogIsModal     = 2,
  kColorPickerCanModifyPalette  = 4,
  kColorPickerCanAnimatePalette = 8,
  kColorPickerAppIsColorSyncAware = 16,
  kColorPickerInSystemDialog    = 32,
  kColorPickerInApplicationDialog = 64,
  kColorPickerInPickerDialog    = 128,
  kColorPickerDetachedFromChoices = 256,
  kColorPickerCallColorProcLive = 512
};


#if OLDROUTINENAMES
enum {
                                        /*Maximum small fract value, as long*/
  MaxSmallFract                 = 0x0000FFFF
};

enum {
  kDefaultWidth                 = 383,
  kDefaultHeight                = 238
};

/* These are for the flags field in the structs below (for example ColorPickerInfo). */
enum {
  DialogIsMoveable              = 1,
  DialogIsModal                 = 2,
  CanModifyPalette              = 4,
  CanAnimatePalette             = 8,
  AppIsColorSyncAware           = 16,
  InSystemDialog                = 32,
  InApplicationDialog           = 64,
  InPickerDialog                = 128,
  DetachedFromChoices           = 256,
  CallColorProcLive             = 512
};

#endif  /* OLDROUTINENAMES */

/* A SmallFract value is just the fractional part of a Fixed number,
which is the low order word.  SmallFracts are used to save room,
and to be compatible with Quickdraw's RGBColor.  They can be
assigned directly to and from INTEGERs. */
/* Unsigned fraction between 0 and 1 */
typedef unsigned short                  SmallFract;
/* For developmental simplicity in switching between the HLS and HSV
models, HLS is reordered into HSL. Thus both models start with
hue and saturation values; value/lightness/brightness is last. */

struct HSVColor {
  SmallFract          hue;                    /*Fraction of circle, red at 0*/
  SmallFract          saturation;             /*0-1, 0 for gray, 1 for pure color*/
  SmallFract          value;                  /*0-1, 0 for black, 1 for max intensity*/
};
typedef struct HSVColor                 HSVColor;
struct HSLColor {
  SmallFract          hue;                    /*Fraction of circle, red at 0*/
  SmallFract          saturation;             /*0-1, 0 for gray, 1 for pure color*/
  SmallFract          lightness;              /*0-1, 0 for black, 1 for white*/
};
typedef struct HSLColor                 HSLColor;
struct CMYColor {
  SmallFract          cyan;
  SmallFract          magenta;
  SmallFract          yellow;
};
typedef struct CMYColor                 CMYColor;
struct PMColor {
  CMProfileHandle     profile;
  CMColor             color;
};
typedef struct PMColor                  PMColor;
typedef PMColor *                       PMColorPtr;
struct NPMColor {
  CMProfileRef        profile;
  CMColor             color;
};
typedef struct NPMColor                 NPMColor;
typedef NPMColor *                      NPMColorPtr;
typedef struct OpaquePicker*            Picker;
typedef Picker picker;
struct PickerMenuItemInfo {
  short               editMenuID;
  short               cutItem;
  short               copyItem;
  short               pasteItem;
  short               clearItem;
  short               undoItem;
};
typedef struct PickerMenuItemInfo       PickerMenuItemInfo;
/* Structs related to deprecated API's have been pulled from this file. */
/* Those structs necessary for developers writing their own color pickers... */
/* have been moved to ColorPickerComponents.h. */

typedef CALLBACK_API( void , ColorChangedProcPtr )(long userData, PMColor *newColor);
typedef CALLBACK_API( void , NColorChangedProcPtr )(long userData, NPMColor *newColor);
typedef CALLBACK_API( Boolean , UserEventProcPtr )(EventRecord * event);
typedef STACK_UPP_TYPE(ColorChangedProcPtr)                     ColorChangedUPP;
typedef STACK_UPP_TYPE(NColorChangedProcPtr)                    NColorChangedUPP;
typedef STACK_UPP_TYPE(UserEventProcPtr)                        UserEventUPP;
struct ColorPickerInfo {
  PMColor             theColor;
  CMProfileHandle     dstProfile;
  UInt32              flags;
  DialogPlacementSpec  placeWhere;
  Point               dialogOrigin;
  OSType              pickerType;
  UserEventUPP        eventProc;
  ColorChangedUPP     colorProc;
  UInt32              colorProcData;
  Str255              prompt;
  PickerMenuItemInfo  mInfo;
  Boolean             newColorChosen;
  SInt8               filler;
};
typedef struct ColorPickerInfo          ColorPickerInfo;
struct NColorPickerInfo {
  NPMColor            theColor;
  CMProfileRef        dstProfile;
  UInt32              flags;
  DialogPlacementSpec  placeWhere;
  Point               dialogOrigin;
  OSType              pickerType;
  UserEventUPP        eventProc;
  NColorChangedUPP    colorProc;
  UInt32              colorProcData;
  Str255              prompt;
  PickerMenuItemInfo  mInfo;
  Boolean             newColorChosen;
  UInt8               reserved;               /*Must be 0*/
};
typedef struct NColorPickerInfo         NColorPickerInfo;

/*  Below are the color conversion routines.*/
/*
 *  Fix2SmallFract()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SmallFract 
Fix2SmallFract(Fixed f)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SmallFract2Fix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Fixed 
SmallFract2Fix(SmallFract s)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CMY2RGB()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
CMY2RGB(
  const CMYColor *  cColor,
  RGBColor *        rColor)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RGB2CMY()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RGB2CMY(
  const RGBColor *  rColor,
  CMYColor *        cColor)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HSL2RGB()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HSL2RGB(
  const HSLColor *  hColor,
  RGBColor *        rColor)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RGB2HSL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RGB2HSL(
  const RGBColor *  rColor,
  HSLColor *        hColor)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HSV2RGB()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HSV2RGB(
  const HSVColor *  hColor,
  RGBColor *        rColor)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RGB2HSV()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
RGB2HSV(
  const RGBColor *  rColor,
  HSVColor *        hColor)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*  GetColor() works with or without the Color Picker extension.*/
/*
 *  GetColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
GetColor(
  Point              where,
  ConstStr255Param   prompt,
  const RGBColor *   inColor,
  RGBColor *         outColor)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*  PickColor() requires the Color Picker extension (version 2.0 or greater).*/
/*
 *  PickColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorPickerLib 2.0 and later
 */
extern OSErr 
PickColor(ColorPickerInfo * theColorInfo)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*  NPickColor() requires the Color Picker extension (version 2.1 or greater).*/
/*
 *  NPickColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ColorPickerLib 2.1 and later
 */
extern OSErr 
NPickColor(NColorPickerInfo * theColorInfo)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* A suite of mid-level API calls have been deprecated.  Likely you never...  */
/* used them anyway.  They were removed from this file and should not be... */
/* used in the future as they are not gauranteed to be supported. */
/*
 *  NewColorChangedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ColorChangedUPP
NewColorChangedUPP(ColorChangedProcPtr userRoutine)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewNColorChangedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern NColorChangedUPP
NewNColorChangedUPP(NColorChangedProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewUserEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern UserEventUPP
NewUserEventUPP(UserEventProcPtr userRoutine)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeColorChangedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeColorChangedUPP(ColorChangedUPP userUPP)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeNColorChangedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeNColorChangedUPP(NColorChangedUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeUserEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeUserEventUPP(UserEventUPP userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeColorChangedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeColorChangedUPP(
  long             userData,
  PMColor *        newColor,
  ColorChangedUPP  userUPP)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeNColorChangedUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeNColorChangedUPP(
  long              userData,
  NPMColor *        newColor,
  NColorChangedUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeUserEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeUserEventUPP(
  EventRecord *  event,
  UserEventUPP   userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __COLORPICKER__ */


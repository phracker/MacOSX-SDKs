/*
     File:       HIToolbox/ControlDefinitions.h
 
     Contains:   Definitions of controls provided by the Control Manager
 
     Version:    HIToolbox-227.3~63
 
     Copyright:  © 1999-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CONTROLDEFINITIONS__
#define __CONTROLDEFINITIONS__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __APPEARANCE__
#include <HIToolbox/Appearance.h>
#endif

#ifndef __CARBONEVENTS__
#include <HIToolbox/CarbonEvents.h>
#endif

#ifndef __CONTROLS__
#include <HIToolbox/Controls.h>
#endif

#ifndef __LISTS__
#include <HIToolbox/Lists.h>
#endif

#ifndef __MACHELP__
#include <HIToolbox/MacHelp.h>
#endif

#ifndef __MENUS__
#include <HIToolbox/Menus.h>
#endif





#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k


/*
 *  ControlDefinitions.h
 *  
 *  Discussion:
 *    System software supplies a variety of controls for your
 *    applications to use. They are described herein.
 */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Resource Types                                                                                    */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

enum {
  kControlTabListResType        = 'tab#', /* used for tab control (Appearance 1.0 and later)*/
  kControlListDescResType       = 'ldes' /* used for list box control (Appearance 1.0 and later)*/
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Check Box Values                                                                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kControlCheckBoxUncheckedValue = 0,
  kControlCheckBoxCheckedValue  = 1,
  kControlCheckBoxMixedValue    = 2
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Radio Button Values                                                               */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kControlRadioButtonUncheckedValue = 0,
  kControlRadioButtonCheckedValue = 1,
  kControlRadioButtonMixedValue = 2
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Pop-Up Menu Control Constants                                                     */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Variant codes for the System 7 pop-up menu*/
enum {
  popupFixedWidth               = 1 << 0,
  popupVariableWidth            = 1 << 1,
  popupUseAddResMenu            = 1 << 2,
  popupUseWFont                 = 1 << 3
};

/* Menu label styles for the System 7 pop-up menu*/
enum {
  popupTitleBold                = 1 << 8,
  popupTitleItalic              = 1 << 9,
  popupTitleUnderline           = 1 << 10,
  popupTitleOutline             = 1 << 11,
  popupTitleShadow              = 1 << 12,
  popupTitleCondense            = 1 << 13,
  popupTitleExtend              = 1 << 14,
  popupTitleNoStyle             = 1 << 15
};

/* Menu label justifications for the System 7 pop-up menu*/
enum {
  popupTitleLeftJust            = 0x00000000,
  popupTitleCenterJust          = 0x00000001,
  popupTitleRightJust           = 0x000000FF
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ PopUp Menu Private Data Structure                                                                 */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
#if !OPAQUE_TOOLBOX_STRUCTS
struct PopupPrivateData {
  MenuRef             mHandle;
  SInt16              mID;
};
typedef struct PopupPrivateData         PopupPrivateData;
typedef PopupPrivateData *              PopupPrivateDataPtr;
typedef PopupPrivateDataPtr *           PopupPrivateDataHandle;
#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Definition IDÕs                                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Standard System 7 procIDs*/

enum {
  pushButProc                   = 0,
  checkBoxProc                  = 1,
  radioButProc                  = 2,
  scrollBarProc                 = 16,
  popupMenuProc                 = 1008
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Part Codes                                                                */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kControlLabelPart             = 1,
  kControlMenuPart              = 2,
  kControlTrianglePart          = 4,
  kControlEditTextPart          = 5,    /* Appearance 1.0 and later*/
  kControlPicturePart           = 6,    /* Appearance 1.0 and later*/
  kControlIconPart              = 7,    /* Appearance 1.0 and later*/
  kControlClockPart             = 8,    /* Appearance 1.0 and later*/
  kControlListBoxPart           = 24,   /* Appearance 1.0 and later*/
  kControlListBoxDoubleClickPart = 25,  /* Appearance 1.0 and later*/
  kControlImageWellPart         = 26,   /* Appearance 1.0 and later*/
  kControlRadioGroupPart        = 27,   /* Appearance 1.0.2 and later*/
  kControlButtonPart            = 10,
  kControlCheckBoxPart          = 11,
  kControlRadioButtonPart       = 11,
  kControlUpButtonPart          = kAppearancePartUpButton,
  kControlDownButtonPart        = kAppearancePartDownButton,
  kControlPageUpPart            = kAppearancePartPageUpArea,
  kControlPageDownPart          = kAppearancePartPageDownArea,
  kControlClockHourDayPart      = 9,    /* Appearance 1.1 and later*/
  kControlClockMinuteMonthPart  = 10,   /* Appearance 1.1 and later*/
  kControlClockSecondYearPart   = 11,   /* Appearance 1.1 and later*/
  kControlClockAMPMPart         = 12,   /* Appearance 1.1 and later*/
  kControlDataBrowserPart       = 24,   /* CarbonLib 1.0 and later*/
  kControlDataBrowserDraggedPart = 25   /* CarbonLib 1.0 and later*/
};



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Types and IDÕs available only with Appearance 1.0 and later                               */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ BEVEL BUTTON INTERFACE (CDEF 2)                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  Bevel buttons allow you to control the content type (pict/icon/etc.), the behavior  */
/* (pushbutton/toggle/sticky), and the bevel size. You also have the option of          */
/*  attaching a menu to it. When a menu is present, you can specify which way the       */
/*  popup arrow is facing (down or right).                                              */
/*                                                                                      */
/*  This is all made possible by overloading the Min, Max, and Value parameters for the */
/*  control, as well as adjusting the variant. Here's the breakdown of what goes where: */
/*                                                                                      */
/*  Parameter                   What Goes Here                                          */
/*  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ         ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ    */
/*  Min                         Hi Byte = Behavior, Lo Byte = content type.             */
/*  Max                         ResID for resource-based content types.                 */
/*  Value                       MenuID to attach, 0 = no menu, please.                  */
/*                                                                                      */
/*  The variant is broken down into two halfs. The low 2 bits control the bevel type.   */
/*  Bit 2 controls the popup arrow direction (if a menu is present) and bit 3 controls  */
/*  whether or not to use the control's owning window's font.                           */
/*                                                                                      */
/*  Constants for all you need to put this together are below. The values for behaviors */
/*  are set up so that you can simply add them to the content type and pass them into   */
/*  the Min parameter of NewControl.                                                    */
/*                                                                                      */
/*  An example call:                                                                    */
/*                                                                                      */
/*  control = NewControl( window, &bounds, "\p", true, 0, kControlContentIconSuiteRes + */
/*                          kBehaviorToggles, myIconSuiteID, bevelButtonSmallBevelProc, */
/*                          0L );                                                       */
/*                                                                                      */
/*  Attaching a menu:                                                                   */
/*                                                                                      */
/*  control = NewControl( window, &bounds, "\p", true, kMyMenuID,                       */
/*          kControlContentIconSuiteRes, myIconSuiteID, bevelButtonSmallBevelProc +     */
/*          kBevelButtonMenuOnRight, 0L );                                              */
/*                                                                                      */
/*  This will attach menu ID kMyMenuID to the button, with the popup arrow facing right.*/
/*  This also puts the menu up to the right of the button. You can also specify that a  */
/*  menu can have multiple items checked at once by adding kBehaviorMultiValueMenus     */
/*  into the Min parameter. If you do use multivalue menus, the GetBevelButtonMenuValue */
/*  helper function will return the last item chosen from the menu, whether or not it   */
/*  was checked.                                                                        */
/*                                                                                      */
/*  NOTE:   Bevel buttons with menus actually have *two* values. The value of the       */
/*          button (on/off), and the value of the menu. The menu value can be gotten    */
/*          with the GetBevelButtonMenuValue helper function.                           */
/*                                                                                      */
/*  Handle-based Content                                                                */
/*  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ                                                                */
/*  You can create your control and then set the content to an existing handle to an    */
/*  icon suite, etc. using the macros below. Please keep in mind that resource-based    */
/*  content is owned by the control, handle-based content is owned by you. The CDEF will*/
/*  not try to dispose of handle-based content. If you are changing the content type of */
/*  the button on the fly, you must make sure that if you are replacing a handle-       */
/*  based content with a resource-based content to properly dispose of the handle,      */
/*  else a memory leak will ensue.                                                      */
/*                                                                                      */
/*  Textual Content                                                                     */
/*  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ                                                                */
/*  Please note that if a bevel button gets its textual content from the title          */
/*  of the control. To alter the textual content of a bevel button, use the             */
/*  SetControlTitle[WithCFString] API.                                                  */
/*                                                                                      */
/* Bevel Button Proc IDs */
enum {
  kControlBevelButtonSmallBevelProc = 32,
  kControlBevelButtonNormalBevelProc = 33,
  kControlBevelButtonLargeBevelProc = 34
};

/* Add these variant codes to kBevelButtonSmallBevelProc to change the type of button */
enum {
  kControlBevelButtonSmallBevelVariant = 0,
  kControlBevelButtonNormalBevelVariant = (1 << 0),
  kControlBevelButtonLargeBevelVariant = (1 << 1),
  kControlBevelButtonMenuOnRightVariant = (1 << 2)
};

/* Bevel Thicknesses */
typedef UInt16 ControlBevelThickness;
enum {
  kControlBevelButtonSmallBevel = 0,
  kControlBevelButtonNormalBevel = 1,
  kControlBevelButtonLargeBevel = 2
};

/* Behaviors of bevel buttons. These are set up so you can add  */
/* them together with the content types.                        */
enum {
  kControlBehaviorPushbutton    = 0,
  kControlBehaviorToggles       = 0x0100,
  kControlBehaviorSticky        = 0x0200,
  kControlBehaviorSingleValueMenu = 0,
  kControlBehaviorMultiValueMenu = 0x4000, /* only makes sense when a menu is attached.*/
  kControlBehaviorOffsetContents = 0x8000
};

/* Behaviors for 1.0.1 or later */
enum {
  kControlBehaviorCommandMenu   = 0x2000 /* menu holds commands, not choices. Overrides multi-value bit.*/
};

typedef UInt16                          ControlBevelButtonBehavior;
typedef UInt16                          ControlBevelButtonMenuBehavior;
/* Bevel Button Menu Placements */
typedef UInt16 ControlBevelButtonMenuPlacement;
enum {
  kControlBevelButtonMenuOnBottom = 0,
  kControlBevelButtonMenuOnRight = (1 << 2)
};

/* Control Kind Tag */
enum {
  kControlKindBevelButton       = 'bevl'
};

/* The HIObject class ID for the HIBevelButton class. */
#define kHIBevelButtonClassID           CFSTR("com.apple.HIBevelButton")
/* Creation API: Carbon Only */
/*
 *  CreateBevelButtonControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateBevelButtonControl(
  WindowRef                         window,
  const Rect *                      boundsRect,
  CFStringRef                       title,
  ControlBevelThickness             thickness,
  ControlBevelButtonBehavior        behavior,
  ControlButtonContentInfoPtr       info,
  SInt16                            menuID,
  ControlBevelButtonMenuBehavior    menuBehavior,
  ControlBevelButtonMenuPlacement   menuPlacement,
  ControlRef *                      outControl)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/* Graphic Alignments */
typedef SInt16 ControlButtonGraphicAlignment;
enum {
  kControlBevelButtonAlignSysDirection = -1, /* only left or right*/
  kControlBevelButtonAlignCenter = 0,
  kControlBevelButtonAlignLeft  = 1,
  kControlBevelButtonAlignRight = 2,
  kControlBevelButtonAlignTop   = 3,
  kControlBevelButtonAlignBottom = 4,
  kControlBevelButtonAlignTopLeft = 5,
  kControlBevelButtonAlignBottomLeft = 6,
  kControlBevelButtonAlignTopRight = 7,
  kControlBevelButtonAlignBottomRight = 8
};

/* Text Alignments */
typedef SInt16 ControlButtonTextAlignment;
enum {
  kControlBevelButtonAlignTextSysDirection = teFlushDefault,
  kControlBevelButtonAlignTextCenter = teCenter,
  kControlBevelButtonAlignTextFlushRight = teFlushRight,
  kControlBevelButtonAlignTextFlushLeft = teFlushLeft
};

/* Text Placements */
typedef SInt16 ControlButtonTextPlacement;
enum {
  kControlBevelButtonPlaceSysDirection = -1, /* if graphic on right, then on left*/
  kControlBevelButtonPlaceNormally = 0,
  kControlBevelButtonPlaceToRightOfGraphic = 1,
  kControlBevelButtonPlaceToLeftOfGraphic = 2,
  kControlBevelButtonPlaceBelowGraphic = 3,
  kControlBevelButtonPlaceAboveGraphic = 4
};


/* Data tags supported by the bevel button controls */
enum {
  kControlBevelButtonContentTag = 'cont', /* ButtonContentInfo*/
  kControlBevelButtonTransformTag = 'tran', /* IconTransformType*/
  kControlBevelButtonTextAlignTag = 'tali', /* ButtonTextAlignment*/
  kControlBevelButtonTextOffsetTag = 'toff', /* SInt16*/
  kControlBevelButtonGraphicAlignTag = 'gali', /* ButtonGraphicAlignment*/
  kControlBevelButtonGraphicOffsetTag = 'goff', /* Point*/
  kControlBevelButtonTextPlaceTag = 'tplc', /* ButtonTextPlacement*/
  kControlBevelButtonMenuValueTag = 'mval', /* SInt16*/
  kControlBevelButtonMenuHandleTag = 'mhnd', /* MenuRef*/
  kControlBevelButtonMenuRefTag = 'mhnd', /* MenuRef*/
  kControlBevelButtonCenterPopupGlyphTag = 'pglc' /* Boolean: true = center, false = bottom right*/
};

/* These are tags in 1.0.1 or later */
enum {
  kControlBevelButtonLastMenuTag = 'lmnu', /* SInt16: menuID of last menu item selected from*/
  kControlBevelButtonMenuDelayTag = 'mdly' /* SInt32: ticks to delay before menu appears*/
};

/* tags available with Appearance 1.1 or later */
enum {
                                        /* Boolean: True = if an icon of the ideal size for*/
                                        /* the button isn't available, scale a larger or*/
                                        /* smaller icon to the ideal size. False = don't*/
                                        /* scale; draw a smaller icon or clip a larger icon.*/
                                        /* Default is false. Only applies to IconSuites and*/
  kControlBevelButtonScaleIconTag = 'scal' /* IconRefs.*/
};

/* tags available in Mac OS X and later */
enum {
  kControlBevelButtonOwnedMenuRefTag = 'omrf', /* MenuRef (control will dispose)*/
  kControlBevelButtonKindTag    = 'bebk' /* ThemeButtonKind ( kTheme[Small,Medium,Large,Rounded]BevelButton )*/
};


/*
 *  Summary:
 *    Tags available with Mac OS X 10.3 or later
 */
enum {

  /*
   * Passed data is an Boolean.  Gets or sets whether or not the
   * associated menu is a multi-value menu or not.  True means that the
   * menu can have multiple selections.
   */
  kControlBevelButtonIsMultiValueMenuTag = 'mult'
};

/* Helper routines are available only thru the shared library/glue. */
/*
 *  GetBevelButtonMenuValue()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetBevelButtonMenuValue(
  ControlRef   inButton,
  SInt16 *     outValue)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetBevelButtonMenuValue()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetBevelButtonMenuValue(
  ControlRef   inButton,
  SInt16       inValue)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetBevelButtonMenuHandle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetBevelButtonMenuHandle(
  ControlRef    inButton,
  MenuHandle *  outHandle)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#define GetBevelButtonMenuRef GetBevelButtonMenuHandle
/*
 *  GetBevelButtonContentInfo()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetBevelButtonContentInfo(
  ControlRef                    inButton,
  ControlButtonContentInfoPtr   outContent)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetBevelButtonContentInfo()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetBevelButtonContentInfo(
  ControlRef                    inButton,
  ControlButtonContentInfoPtr   inContent)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetBevelButtonTransform()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetBevelButtonTransform(
  ControlRef          inButton,
  IconTransformType   transform)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetBevelButtonGraphicAlignment()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetBevelButtonGraphicAlignment(
  ControlRef                      inButton,
  ControlButtonGraphicAlignment   inAlign,
  SInt16                          inHOffset,
  SInt16                          inVOffset)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetBevelButtonTextAlignment()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetBevelButtonTextAlignment(
  ControlRef                   inButton,
  ControlButtonTextAlignment   inAlign,
  SInt16                       inHOffset)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetBevelButtonTextPlacement()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetBevelButtonTextPlacement(
  ControlRef                   inButton,
  ControlButtonTextPlacement   inWhere)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ SLIDER (CDEF 3)                                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  There are several variants that control the behavior of the slider control. Any     */
/*  combination of the following three constants can be added to the basic CDEF ID      */
/*  (kSliderProc).                                                                      */
/*                                                                                      */
/*  Variants:                                                                           */
/*                                                                                      */
/*      kSliderLiveFeedback     Slider does not use "ghosted" indicator when tracking.  */
/*                              ActionProc is called (set via SetControlAction) as the  */
/*                              indicator is dragged. The value is updated so that the  */
/*                              actionproc can adjust some other property based on the  */
/*                              value each time the action proc is called. If no action */
/*                              proc is installed, it reverts to the ghost indicator.   */
/*                                                                                      */
/*      kSliderHasTickMarks     Slider is drawn with 'tick marks'. The control          */
/*                              rectangle must be large enough to accomidate the tick   */
/*                              marks.                                                  */
/*                                                                                      */
/*      kSliderReverseDirection Slider thumb points in opposite direction than normal.  */
/*                              If the slider is vertical, the thumb will point to the  */
/*                              left, if the slider is horizontal, the thumb will point */
/*                              upwards.                                                */
/*                                                                                      */
/*      kSliderNonDirectional   This option overrides the kSliderReverseDirection and   */
/*                              kSliderHasTickMarks variants. It creates an indicator   */
/*                              which is rectangular and doesn't point in any direction */
/*                              like the normal indicator does.                         */
/*                                                                                      */
/*                                                                                      */
/*  Mac OS X has a "Scroll to here" option in the General pane of System Preferences    */
/*  which allows users to click in the page up/down regions of a slider and have the    */
/*  thumb/indicator jump directly to the clicked position, which alters the value of    */
/*  the slider and moves any associated content appropriately. As long as the mouse     */
/*  button is held down, the click is treated as though the user had clicked in the     */
/*  thumb/indicator in the first place.                                                 */
/*                                                                                      */
/*  If you want the sliders in your application to work with the "Scroll to here"       */
/*  option, you must do the following:                                                  */
/*                                                                                      */
/*  1. Create live-tracking sliders, not sliders that show a "ghost" thumb when you     */
/*  click on it. You can request live-tracking sliders by passing true in the           */
/*  liveTracking parameter to CreateSliderControl. If you create sliders with           */
/*  NewControl, use the kControlSliderLiveFeedback variant.                             */
/*                                                                                      */
/*  2. Write an appropriate ControlActionProc and associate it with your slider via     */
/*  the SetControlAction API. This allows your application to update its content        */
/*  appropriately when the live-tracking slider is clicked.                             */
/*                                                                                      */
/*  3. When calling HandleControlClick or TrackControl, pass -1 in the action proc      */
/*  parameter. This is a request for the Control Manager to use the action proc you     */
/*  associated with your control in step 2. If you rely on the standard window event    */
/*  handler to do your control tracking, this step is handled for you automatically.    */
/*                                                                                      */
/* Slider proc ID and variants */
enum {
  kControlSliderProc            = 48,
  kControlSliderLiveFeedback    = (1 << 0),
  kControlSliderHasTickMarks    = (1 << 1),
  kControlSliderReverseDirection = (1 << 2),
  kControlSliderNonDirectional  = (1 << 3)
};

/* Slider Orientation */
typedef UInt16 ControlSliderOrientation;
enum {
  kControlSliderPointsDownOrRight = 0,
  kControlSliderPointsUpOrLeft  = 1,
  kControlSliderDoesNotPoint    = 2
};

/* Control Kind Tag */
enum {
  kControlKindSlider            = 'sldr'
};

/* The HIObject class ID for the HISlider class. */
#define kHISliderClassID                CFSTR("com.apple.HISlider")
/* Creation API: Carbon Only */
/*
 *  CreateSliderControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateSliderControl(
  WindowRef                  window,
  const Rect *               boundsRect,
  SInt32                     value,
  SInt32                     minimum,
  SInt32                     maximum,
  ControlSliderOrientation   orientation,
  UInt16                     numTickMarks,
  Boolean                    liveTracking,
  ControlActionUPP           liveTrackingProc,
  ControlRef *               outControl)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ DISCLOSURE TRIANGLE (CDEF 4)                                                      */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  This control can be used as either left or right facing. It can also handle its own */
/*  tracking if you wish. This means that when the 'autotoggle' variant is used, if the */
/*  user clicks the control, it's state will change automatically from open to closed   */
/*  and vice-versa depending on its initial state. After a successful call to Track-    */
/*  Control, you can just check the current value to see what state it was switched to. */
/* Triangle proc IDs */
enum {
  kControlTriangleProc          = 64,
  kControlTriangleLeftFacingProc = 65,
  kControlTriangleAutoToggleProc = 66,
  kControlTriangleLeftFacingAutoToggleProc = 67
};

typedef UInt16 ControlDisclosureTriangleOrientation;
enum {
  kControlDisclosureTrianglePointDefault = 0, /* points right on a left-to-right script system (Mac OS X and later or CarbonLib 1.5 and later only)*/
  kControlDisclosureTrianglePointRight = 1,
  kControlDisclosureTrianglePointLeft = 2
};

/* Control Kind Tag */
enum {
  kControlKindDisclosureTriangle = 'dist'
};

/* The HIObject class ID for the HIDisclosureTriangle class. */
#define kHIDisclosureTriangleClassID    CFSTR("com.apple.HIDisclosureTriangle")
/*
 *  CreateDisclosureTriangleControl()
 *  
 *  Summary:
 *    Creates a Disclosure Triangle control at a specific position in
 *    the specified window.
 *  
 *  Discussion:
 *    Disclosure Triangles are small controls that give the user a way
 *    to toggle the visibility of information or other user interface.
 *    When information is in a hidden state, a Disclosure Triangle is
 *    considered "closed" and should point to the right (or sometimes
 *    to the left). When the user clicks on it, the Disclosure Triangle
 *    rotates downwards into the "open" state. The application should
 *    repond by revealing the appropriate information or interface. On
 *    Mac OS X, a root control will be created for the window if one
 *    does not already exist. If a root control exists for the window,
 *    the Disclosure Triangle control will be embedded into it.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The WindowRef into which the Disclosure Triangle will be
 *      created.
 *    
 *    inBoundsRect:
 *      The desired position (in coordinates local to the window's
 *      port) for the Disclosure Triangle.
 *    
 *    inOrientation:
 *      The direction the Disclosure Triangle should point when it is
 *      "closed". Passing kControlDisclosureTrianglePointDefault is
 *      only legal as of Mac OS X and CarbonLib 1.5.
 *    
 *    inTitle:
 *      The title for the Disclosure Triangle. The title will only be
 *      displayed if the inDrawTitle parameter is true. Title display
 *      only works on Mac OS X.
 *    
 *    inInitialValue:
 *      The starting value determines whether the Disclosure Triangle
 *      is initially in its "open" or "closed" state. The value 0
 *      represents the "closed" state and 1 represents the "open" state.
 *    
 *    inDrawTitle:
 *      A Boolean indicating whether the Disclosure Triangle should
 *      draw its title next to the widget. Title display only works on
 *      Mac OS X.
 *    
 *    inAutoToggles:
 *      A Boolean indicating whether the Disclosure Triangle should
 *      change its own value (from "open" to "closed" and vice-versa)
 *      automatically when it is clicked on.
 *    
 *    outControl:
 *      On successful output, outControl will contain a reference to
 *      the Disclosure Triangle control.
 *  
 *  Result:
 *    An OSStatus code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateDisclosureTriangleControl(
  WindowRef                              inWindow,
  const Rect *                           inBoundsRect,
  ControlDisclosureTriangleOrientation   inOrientation,
  CFStringRef                            inTitle,
  SInt32                                 inInitialValue,
  Boolean                                inDrawTitle,
  Boolean                                inAutoToggles,
  ControlRef *                           outControl)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Tagged data supported by disclosure triangles */
enum {
  kControlTriangleLastValueTag  = 'last' /* SInt16*/
};

/* Helper routines are available only thru the shared library/glue. */
/*
 *  SetDisclosureTriangleLastValue()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetDisclosureTriangleLastValue(
  ControlRef   inTabControl,
  SInt16       inValue)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ PROGRESS INDICATOR (CDEF 5)                                                       */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  This CDEF implements both determinate and indeterminate progress bars. To switch,   */
/*  just use SetControlData to set the indeterminate flag to make it indeterminate. Any */
/*  animation will automatically be handled by the toolbox on an event timer.           */
/*                                                                                      */
/*  We also use this same CDEF for Relevance bars. At this time this control does not   */
/*  idle.                                                                               */
/* Progress Bar proc IDs */
enum {
  kControlProgressBarProc       = 80,
  kControlRelevanceBarProc      = 81
};

/* Control Kind Tag */
enum {
  kControlKindProgressBar       = 'prgb',
  kControlKindRelevanceBar      = 'relb'
};

/* The HIObject class ID for the HIProgressBar class. */
#define kHIProgressBarClassID           CFSTR("com.apple.HIProgressBar")
/* Creation API: Carbon only */
/*
 *  CreateProgressBarControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateProgressBarControl(
  WindowRef     window,
  const Rect *  boundsRect,
  SInt32        value,
  SInt32        minimum,
  SInt32        maximum,
  Boolean       indeterminate,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* The HIObject class ID for the HIRelevanceBar class. */
#define kHIRelevanceBarClassID          CFSTR("com.apple.HIRelevanceBar")
/*
 *  CreateRelevanceBarControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateRelevanceBarControl(
  WindowRef     window,
  const Rect *  boundsRect,
  SInt32        value,
  SInt32        minimum,
  SInt32        maximum,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Tagged data supported by progress bars */
enum {
  kControlProgressBarIndeterminateTag = 'inde', /* Boolean*/
  kControlProgressBarAnimatingTag = 'anim' /* Boolean*/
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ LITTLE ARROWS (CDEF 6)                                                            */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  This control implements the little up and down arrows you'd see in the Memory       */
/*  control panel for adjusting the cache size.                                         */
/* Little Arrows proc IDs */
enum {
  kControlLittleArrowsProc      = 96
};

/* Control Kind Tag */
enum {
  kControlKindLittleArrows      = 'larr'
};


/*
 *  Summary:
 *    Tags available with Mac OS X 10.3 or later
 */
enum {

  /*
   * Passed data is an SInt32.  Gets or sets the increment value of the
   * control.
   */
  kControlLittleArrowsIncrementValueTag = 'incr'
};

/* The HIObject class ID for the HILittleArrows class. */
#define kHILittleArrowsClassID          CFSTR("com.apple.HILittleArrows")
/* Creation API: Carbon only */
/*
 *  CreateLittleArrowsControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateLittleArrowsControl(
  WindowRef     window,
  const Rect *  boundsRect,
  SInt32        value,
  SInt32        minimum,
  SInt32        maximum,
  SInt32        increment,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ CHASING ARROWS (CDEF 7)                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  This control will automatically animate via an event loop timer.                    */
/*                                                                                      */
/* Chasing Arrows proc IDs */
enum {
  kControlChasingArrowsProc     = 112
};

/* Control Kind Tag */
enum {
  kControlKindChasingArrows     = 'carr'
};

/* The HIObject class ID for the HIChasingArrows class. */
#define kHIChasingArrowsClassID         CFSTR("com.apple.HIChasingArrows")
/* Creation API: Carbon only */
/*
 *  CreateChasingArrowsControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateChasingArrowsControl(
  WindowRef     window,
  const Rect *  boundsRect,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Tagged data supported by the Chasing Arrows control */
enum {
  kControlChasingArrowsAnimatingTag = 'anim' /* Boolean*/
};


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ TABS (CDEF 8)                                                                     */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  Tabs use an auxiliary resource (tab#) to hold tab information such as the tab name  */
/*  and an icon suite ID for each tab.                                                  */
/*                                                                                      */
/*  The ID of the tab# resource that you wish to associate with a tab control should    */
/*  be passed in as the Value parameter of the control. If you are using GetNewControl, */
/*  then the Value slot in the CNTL resource should have the ID of the 'tab#' resource  */
/*  on creation.                                                                        */
/*                                                                                      */
/*  Passing zero in for the tab# resource tells the control not to read in a tab# res.  */
/*  You can then use SetControlMaximum to add tabs, followed by a call to SetControlData*/
/*  with the kControlTabInfoTag, passing in a pointer to a ControlTabInfoRec. This sets */
/*  the name and optionally an icon for a tab. Pass the 1-based tab index as the part   */
/*  code parameter to SetControlData to indicate the tab that you want to modify.       */
/*                                                                                      */
/*  Accessibility Notes: Those of you who wish to customize the accessibility           */
/*  information provided for individual tabs of a tabs control -- by handling various   */
/*  kEventClassAccessibility Carbon Events, by calling                                  */
/*  HIObjectSetAuxiliaryAccessibilityAttribute, etc. -- need to know how to interpret   */
/*  and/or build AXUIElementRefs that represent individual tabs. The AXUIElement        */
/*  representing an individual tab will/must be constructed using the tab control's     */
/*  ControlRef and the UInt64 identifier of the one-based index of the tab the element  */
/*  refers to. As usual, a UInt64 identifier of zero represents the tabs control as a   */
/*  whole. You must neither interpret nor create tab control elements whose identifiers */
/*  are greater than the count of tabs in the tabs control.                             */
/* Tabs proc IDs */
enum {
  kControlTabLargeProc          = 128,  /* Large tab size, north facing   */
  kControlTabSmallProc          = 129,  /* Small tab size, north facing   */
  kControlTabLargeNorthProc     = 128,  /* Large tab size, north facing   */
  kControlTabSmallNorthProc     = 129,  /* Small tab size, north facing   */
  kControlTabLargeSouthProc     = 130,  /* Large tab size, south facing   */
  kControlTabSmallSouthProc     = 131,  /* Small tab size, south facing   */
  kControlTabLargeEastProc      = 132,  /* Large tab size, east facing    */
  kControlTabSmallEastProc      = 133,  /* Small tab size, east facing    */
  kControlTabLargeWestProc      = 134,  /* Large tab size, west facing    */
  kControlTabSmallWestProc      = 135   /* Small tab size, west facing    */
};

/* Tab Directions */
typedef UInt16 ControlTabDirection;
enum {
  kControlTabDirectionNorth     = 0,
  kControlTabDirectionSouth     = 1,
  kControlTabDirectionEast      = 2,
  kControlTabDirectionWest      = 3
};

/* Tab Sizes */
typedef UInt16 ControlTabSize;
enum {
  kControlTabSizeLarge          = kControlSizeNormal,
  kControlTabSizeSmall          = kControlSizeSmall,
  kControlTabSizeMini           = kControlSizeMini
};

/* Control Tab Entry - used during creation                             */
/* Note that the client is responsible for allocating/providing         */
/* the ControlButtonContentInfo and string storage for this             */
/* structure.                                                           */
struct ControlTabEntry {
  ControlButtonContentInfo * icon;
  CFStringRef         name;
  Boolean             enabled;
};
typedef struct ControlTabEntry          ControlTabEntry;
/* Control Kind Tag */
enum {
  kControlKindTabs              = 'tabs'
};

/* The HIObject class ID for the HITabbedView class. */
#define kHITabbedViewClassID            CFSTR("com.apple.HITabbedView")
/* Creation API: Carbon only */
/*
 *  CreateTabsControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateTabsControl(
  WindowRef                window,
  const Rect *             boundsRect,
  ControlTabSize           size,
  ControlTabDirection      direction,
  UInt16                   numTabs,
  const ControlTabEntry *  tabArray,
  ControlRef *             outControl)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Tagged data supported by tabs */
enum {
  kControlTabContentRectTag     = 'rect', /* Rect*/
  kControlTabEnabledFlagTag     = 'enab', /* Boolean*/
  kControlTabFontStyleTag       = kControlFontStyleTag /* ControlFontStyleRec*/
};

/* New tags in 1.0.1 or later */
enum {
  kControlTabInfoTag            = 'tabi' /* ControlTabInfoRec*/
};

/* New tags in X 10.1 or later */
enum {
  kControlTabImageContentTag    = 'cont' /* ControlButtonContentInfo*/
};

enum {
  kControlTabInfoVersionZero    = 0,    /* ControlTabInfoRec*/
  kControlTabInfoVersionOne     = 1     /* ControlTabInfoRecV1*/
};

struct ControlTabInfoRec {
  SInt16              version;                /* version of this structure.*/
  SInt16              iconSuiteID;            /* icon suite to use. Zero indicates no icon*/
  Str255              name;                   /* name to be displayed on the tab*/
};
typedef struct ControlTabInfoRec        ControlTabInfoRec;
struct ControlTabInfoRecV1 {
  SInt16              version;                /* version of this structure. == kControlTabInfoVersionOne*/
  SInt16              iconSuiteID;            /* icon suite to use. Zero indicates no icon*/
  CFStringRef         name;                   /* name to be displayed on the tab. Will be retained so caller*/
                                              /* should always release it.*/
};
typedef struct ControlTabInfoRecV1      ControlTabInfoRecV1;
/* Helper routines are available only thru the shared library/glue. */
/*
 *  GetTabContentRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetTabContentRect(
  ControlRef   inTabControl,
  Rect *       outContentRect)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTabEnabled()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetTabEnabled(
  ControlRef   inTabControl,
  SInt16       inTabToHilite,
  Boolean      inEnabled)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ VISUAL SEPARATOR (CDEF 9)                                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  Separator lines determine their orientation (horizontal or vertical) automatically  */
/*  based on the relative height and width of their contrlRect.                         */
/* Visual separator proc IDs */
enum {
  kControlSeparatorLineProc     = 144
};

/* Control Kind Tag */
enum {
  kControlKindSeparator         = 'sepa'
};

/* The HIObject class ID for the HIVisualSeparator class. */
#define kHIVisualSeparatorClassID       CFSTR("com.apple.HIVisualSeparator")
/* Creation API: Carbon only */
/*
 *  CreateSeparatorControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateSeparatorControl(
  WindowRef     window,
  const Rect *  boundsRect,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ GROUP BOX (CDEF 10)                                                               */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  The group box CDEF can be use in several ways. It can have no title, a text title,  */
/*  a check box as the title, or a popup button as a title. There are two versions of   */
/*  group boxes, primary and secondary, which look slightly different.                  */
/* Group Box proc IDs */
enum {
  kControlGroupBoxTextTitleProc = 160,
  kControlGroupBoxCheckBoxProc  = 161,
  kControlGroupBoxPopupButtonProc = 162,
  kControlGroupBoxSecondaryTextTitleProc = 164,
  kControlGroupBoxSecondaryCheckBoxProc = 165,
  kControlGroupBoxSecondaryPopupButtonProc = 166
};

/* Control Kind Tag */
enum {
  kControlKindGroupBox          = 'grpb',
  kControlKindCheckGroupBox     = 'cgrp',
  kControlKindPopupGroupBox     = 'pgrp'
};

/* The HIObject class ID for the HIGroupBox class. */
#define kHIGroupBoxClassID              CFSTR("com.apple.HIGroupBox")
/* The HIObject class ID for the HICheckBoxGroup class. */
#define kHICheckBoxGroupClassID         CFSTR("com.apple.HICheckBoxGroup")
/* Creation APIs: Carbon only */
/*
 *  CreateGroupBoxControl()
 *  
 *  Summary:
 *    Creates a group box control.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window that should contain the control.
 *    
 *    boundsRect:
 *      The bounding box of the control.
 *    
 *    title:
 *      The title of the control.
 *    
 *    primary:
 *      Whether to create a primary or secondary group box.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateGroupBoxControl(
  WindowRef     window,
  const Rect *  boundsRect,
  CFStringRef   title,
  Boolean       primary,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CreateCheckGroupBoxControl()
 *  
 *  Summary:
 *    Creates a group box control that has a check box as its title.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window that should contain the control.
 *    
 *    boundsRect:
 *      The bounding box of the control.
 *    
 *    title:
 *      The title of the control (used as the title of the check box).
 *    
 *    initialValue:
 *      The initial value of the check box.
 *    
 *    primary:
 *      Whether to create a primary or secondary group box.
 *    
 *    autoToggle:
 *      Whether to create an auto-toggling check box. Auto-toggling
 *      check box titles are only supported on Mac OS X; this parameter
 *      must be false when used with CarbonLib.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateCheckGroupBoxControl(
  WindowRef     window,
  const Rect *  boundsRect,
  CFStringRef   title,
  SInt32        initialValue,
  Boolean       primary,
  Boolean       autoToggle,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CreatePopupGroupBoxControl()
 *  
 *  Summary:
 *    Creates a group box control that has a popup button as its title.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window that should contain the control.
 *    
 *    boundsRect:
 *      The bounding box of the control.
 *    
 *    title:
 *      The title of the control (used as the title of the popup
 *      button).
 *    
 *    primary:
 *      Whether to create a primary or secondary group box.
 *    
 *    menuID:
 *      The menu ID of the menu to be displayed by the popup button.
 *    
 *    variableWidth:
 *      Whether the popup button should have a variable-width title.
 *      Fixed-width titles are only supported by Mac OS X; this
 *      parameter must be true when used with CarbonLib.
 *    
 *    titleWidth:
 *      The width in pixels of the popup button title.
 *    
 *    titleJustification:
 *      The justification of the popup button title. Use one of the
 *      TextEdit justification constants here (teFlushDefault,
 *      teCenter, teFlushRight, or teFlushLeft).
 *    
 *    titleStyle:
 *      The QuickDraw text style of the popup button title.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreatePopupGroupBoxControl(
  WindowRef     window,
  const Rect *  boundsRect,
  CFStringRef   title,
  Boolean       primary,
  SInt16        menuID,
  Boolean       variableWidth,
  SInt16        titleWidth,
  SInt16        titleJustification,
  Style         titleStyle,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Tagged data supported by group box */
enum {
  kControlGroupBoxMenuHandleTag = 'mhan', /* MenuRef (popup title only)*/
  kControlGroupBoxMenuRefTag    = 'mhan', /* MenuRef (popup title only)*/
  kControlGroupBoxFontStyleTag  = kControlFontStyleTag /* ControlFontStyleRec*/
};

/* tags available with Appearance 1.1 or later */
enum {
  kControlGroupBoxTitleRectTag  = 'trec' /* Rect. Rectangle that the title text/control is drawn in. (get only)*/
};


/*
 *  Summary:
 *    Tags available with Mac OS X 10.3 or later
 */
enum {

  /*
   * Passed data is a Rect.  Returns the full rectangle that content is
   * drawn in (get only). This is slightly different than the content
   * region, as it also includes the frame drawn around the content.
   */
  kControlGroupBoxFrameRectTag  = 'frec'
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ IMAGE WELL (CDEF 11)                                                              */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  Image Wells allow you to control the content type (pict/icon/etc.) shown in the     */
/*  well.                                                                               */
/*                                                                                      */
/*  This is made possible by overloading the Min and Value parameters for the control.  */
/*                                                                                      */
/*  Parameter                   What Goes Here                                          */
/*  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ         ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ      */
/*  Min                         content type (see constants for bevel buttons)          */
/*  Value                       Resource ID of content type, if resource-based.         */
/*                                                                                      */
/*                                                                                      */
/*  Handle-based Content                                                                */
/*  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ                                                                */
/*  You can create your control and then set the content to an existing handle to an    */
/*  icon suite, etc. using the macros below. Please keep in mind that resource-based    */
/*  content is owned by the control, handle-based content is owned by you. The CDEF will*/
/*  not try to dispose of handle-based content. If you are changing the content type of */
/*  the button on the fly, you must make sure that if you are replacing a handle-       */
/*  based content with a resource-based content to properly dispose of the handle,      */
/*  else a memory leak will ensue.                                                      */
/*                                                                                      */
/* Image Well proc IDs */
enum {
  kControlImageWellProc         = 176
};

/* Control Kind Tag */
enum {
  kControlKindImageWell         = 'well'
};

/* The HIObject class ID for the HIImageWell class. */
#define kHIImageWellClassID             CFSTR("com.apple.HIImageWell")
/* Creation API: Carbon only */
/*
 *  CreateImageWellControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateImageWellControl(
  WindowRef                         window,
  const Rect *                      boundsRect,
  const ControlButtonContentInfo *  info,
  ControlRef *                      outControl)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Tagged data supported by image wells */
enum {
  kControlImageWellContentTag   = 'cont', /* ButtonContentInfo*/
  kControlImageWellTransformTag = 'tran', /* IconTransformType*/
  kControlImageWellIsDragDestinationTag = 'drag' /* Boolean*/
};

/* Helper routines are available only thru the shared library/glue. */
/*
 *  GetImageWellContentInfo()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetImageWellContentInfo(
  ControlRef                    inButton,
  ControlButtonContentInfoPtr   outContent)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetImageWellContentInfo()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetImageWellContentInfo(
  ControlRef                    inButton,
  ControlButtonContentInfoPtr   inContent)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetImageWellTransform()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetImageWellTransform(
  ControlRef          inButton,
  IconTransformType   inTransform)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ POPUP ARROW (CDEF 12)                                                             */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  The popup arrow CDEF is used to draw the small arrow normally associated with a     */
/*  popup control. The arrow can point in four directions, and a small or large version */
/*  can be used. This control is provided to allow clients to draw the arrow in a       */
/*  normalized fashion which will take advantage of themes automatically.               */
/*                                                                                      */
/* Popup Arrow proc IDs */
enum {
  kControlPopupArrowEastProc    = 192,
  kControlPopupArrowWestProc    = 193,
  kControlPopupArrowNorthProc   = 194,
  kControlPopupArrowSouthProc   = 195,
  kControlPopupArrowSmallEastProc = 196,
  kControlPopupArrowSmallWestProc = 197,
  kControlPopupArrowSmallNorthProc = 198,
  kControlPopupArrowSmallSouthProc = 199
};

/* Popup Arrow Orientations */
enum {
  kControlPopupArrowOrientationEast = 0,
  kControlPopupArrowOrientationWest = 1,
  kControlPopupArrowOrientationNorth = 2,
  kControlPopupArrowOrientationSouth = 3
};


typedef UInt16                          ControlPopupArrowOrientation;
/* Popup Arrow Size */
enum {
  kControlPopupArrowSizeNormal  = 0,
  kControlPopupArrowSizeSmall   = 1
};

typedef UInt16                          ControlPopupArrowSize;
/* Control Kind Tag */
enum {
  kControlKindPopupArrow        = 'parr'
};

/*
 *  CreatePopupArrowControl()
 *  
 *  Summary:
 *    Creates a popup arrow control.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window that should contain the control. May be NULL on 10.3
 *      and later.
 *    
 *    boundsRect:
 *      The bounding box of the control.
 *    
 *    orientation:
 *      The orientation of the control.
 *    
 *    size:
 *      The size of the control.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreatePopupArrowControl(
  WindowRef                      window,            /* can be NULL */
  const Rect *                   boundsRect,
  ControlPopupArrowOrientation   orientation,
  ControlPopupArrowSize          size,
  ControlRef *                   outControl)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ PLACARD (CDEF 14)                                                                 */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Placard proc IDs */
enum {
  kControlPlacardProc           = 224
};

/* Control Kind Tag */
enum {
  kControlKindPlacard           = 'plac'
};

/* The HIObject class ID for the HIPlacardView class. */
#define kHIPlacardViewClassID           CFSTR("com.apple.HIPlacardView")
/*
 *  CreatePlacardControl()
 *  
 *  Summary:
 *    Creates a placard control.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window that should contain the control. May be NULL on 10.3
 *      and later.
 *    
 *    boundsRect:
 *      The bounding box of the control.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreatePlacardControl(
  WindowRef     window,           /* can be NULL */
  const Rect *  boundsRect,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ CLOCK (CDEF 15)                                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  NOTE:   You can specify more options in the Value paramter when creating the clock. */
/*          See below.                                                                  */
/*                                                                                      */
/*  NOTE:   Under Appearance 1.1, the clock control knows and returns more part codes.  */
/*          The new clock-specific part codes are defined with the other control parts. */
/*          Besides these clock-specific parts, we also return kControlUpButtonPart     */
/*          and kControlDownButtonPart when they hit the up and down arrows.            */
/*          The new part codes give you more flexibility for focusing and hit testing.  */
/*                                                                                      */
/*          The original kControlClockPart is still valid. When hit testing, it means   */
/*          that some non-editable area of the clock's whitespace has been clicked.     */
/*          When focusing a currently unfocused clock, it changes the focus to the      */
/*          first part; it is the same as passing kControlFocusNextPart. When           */
/*          re-focusing a focused clock, it will not change the focus at all.           */
/* Clock proc IDs */
enum {
  kControlClockTimeProc         = 240,
  kControlClockTimeSecondsProc  = 241,
  kControlClockDateProc         = 242,
  kControlClockMonthYearProc    = 243
};

/* Clock Types */
typedef UInt16 ControlClockType;
enum {
  kControlClockTypeHourMinute   = 0,
  kControlClockTypeHourMinuteSecond = 1,
  kControlClockTypeMonthDayYear = 2,
  kControlClockTypeMonthYear    = 3
};

/* Clock Flags */
/*  These flags can be passed into 'value' field on creation of the control.            */
/*  Value is set to 0 after control is created.                                         */
typedef UInt32 ControlClockFlags;
enum {
  kControlClockFlagStandard     = 0,    /* editable, non-live*/
  kControlClockNoFlags          = 0,
  kControlClockFlagDisplayOnly  = 1,    /* add this to become non-editable*/
  kControlClockIsDisplayOnly    = 1,
  kControlClockFlagLive         = 2,    /* automatically shows current time on idle. only valid with display only.*/
  kControlClockIsLive           = 2
};

/* Control Kind Tag */
enum {
  kControlKindClock             = 'clck'
};

/* The HIObject class ID for the HIClock class. */
#define kHIClockViewClassID             CFSTR("com.apple.HIClock")
/* Creation API: Carbon only */
/*
 *  CreateClockControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateClockControl(
  WindowRef           window,
  const Rect *        boundsRect,
  ControlClockType    clockType,
  ControlClockFlags   clockFlags,
  ControlRef *        outControl)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Tagged data supported by clocks */
enum {
  kControlClockLongDateTag      = 'date', /* LongDateRec*/
  kControlClockFontStyleTag     = kControlFontStyleTag, /* ControlFontStyleRec*/
  kControlClockAnimatingTag     = 'anim' /* Boolean*/
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ USER PANE (CDEF 16)                                                               */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  User panes have two primary purposes: to allow easy implementation of a custom      */
/*  control by the developer, and to provide a generic container for embedding other    */
/*  controls.                                                                           */
/*                                                                                      */
/*  In Carbon, with the advent of Carbon-event-based controls, you may find it easier   */
/*  to simply write a new control from scratch than to customize a user pane control.   */
/*  The set of callbacks provided by the user pane will not be extended to support      */
/*  new Control Manager features; instead, you should just write a real control.        */
/*                                                                                      */
/*  User panes do not, by default, support embedding. If you try to embed a control     */
/*  into a user pane, you will get back errControlIsNotEmbedder. You can make a user    */
/*  pane support embedding by passing the kControlSupportsEmbedding flag in the 'value' */
/*  parameter when you create the control.                                              */
/*                                                                                      */
/*  User panes support the following overloaded control initialization options:         */
/*                                                                                      */
/*  Parameter                   What Goes Here                                          */
/*  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ         ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ      */
/*  Value                       Control feature flags                                   */

/* User Pane proc IDs */
enum {
  kControlUserPaneProc          = 256
};

/* Control Kind Tag */
enum {
  kControlKindUserPane          = 'upan'
};

/* The HIObject class ID for the HIUserPane class. */
#define kHIUserPaneClassID              CFSTR("com.apple.HIUserPane")
/* Creation API: Carbon only */
/*
 *  CreateUserPaneControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateUserPaneControl(
  WindowRef     window,
  const Rect *  boundsRect,
  UInt32        features,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Tagged data supported by user panes */
/* Currently, they are all proc ptrs for doing things like drawing and hit testing, etc. */
enum {
  kControlUserItemDrawProcTag   = 'uidp', /* UserItemUPP*/
  kControlUserPaneDrawProcTag   = 'draw', /* ControlUserPaneDrawUPP*/
  kControlUserPaneHitTestProcTag = 'hitt', /* ControlUserPaneHitTestUPP*/
  kControlUserPaneTrackingProcTag = 'trak', /* ControlUserPaneTrackingUPP*/
  kControlUserPaneIdleProcTag   = 'idle', /* ControlUserPaneIdleUPP*/
  kControlUserPaneKeyDownProcTag = 'keyd', /* ControlUserPaneKeyDownUPP*/
  kControlUserPaneActivateProcTag = 'acti', /* ControlUserPaneActivateUPP*/
  kControlUserPaneFocusProcTag  = 'foci', /* ControlUserPaneFocusUPP*/
  kControlUserPaneBackgroundProcTag = 'back' /* ControlUserPaneBackgroundUPP*/
};

typedef CALLBACK_API( void , ControlUserPaneDrawProcPtr )(ControlRef control, SInt16 part);
typedef CALLBACK_API( ControlPartCode , ControlUserPaneHitTestProcPtr )(ControlRef control, Point where);
typedef CALLBACK_API( ControlPartCode , ControlUserPaneTrackingProcPtr )(ControlRef control, Point startPt, ControlActionUPP actionProc);
typedef CALLBACK_API( void , ControlUserPaneIdleProcPtr )(ControlRef control);
typedef CALLBACK_API( ControlPartCode , ControlUserPaneKeyDownProcPtr )(ControlRef control, SInt16 keyCode, SInt16 charCode, SInt16 modifiers);
typedef CALLBACK_API( void , ControlUserPaneActivateProcPtr )(ControlRef control, Boolean activating);
typedef CALLBACK_API( ControlPartCode , ControlUserPaneFocusProcPtr )(ControlRef control, ControlFocusPart action);
typedef CALLBACK_API( void , ControlUserPaneBackgroundProcPtr )(ControlRef control, ControlBackgroundPtr info);
typedef STACK_UPP_TYPE(ControlUserPaneDrawProcPtr)              ControlUserPaneDrawUPP;
typedef STACK_UPP_TYPE(ControlUserPaneHitTestProcPtr)           ControlUserPaneHitTestUPP;
typedef STACK_UPP_TYPE(ControlUserPaneTrackingProcPtr)          ControlUserPaneTrackingUPP;
typedef STACK_UPP_TYPE(ControlUserPaneIdleProcPtr)              ControlUserPaneIdleUPP;
typedef STACK_UPP_TYPE(ControlUserPaneKeyDownProcPtr)           ControlUserPaneKeyDownUPP;
typedef STACK_UPP_TYPE(ControlUserPaneActivateProcPtr)          ControlUserPaneActivateUPP;
typedef STACK_UPP_TYPE(ControlUserPaneFocusProcPtr)             ControlUserPaneFocusUPP;
typedef STACK_UPP_TYPE(ControlUserPaneBackgroundProcPtr)        ControlUserPaneBackgroundUPP;
/*
 *  NewControlUserPaneDrawUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlUserPaneDrawUPP
NewControlUserPaneDrawUPP(ControlUserPaneDrawProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewControlUserPaneHitTestUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlUserPaneHitTestUPP
NewControlUserPaneHitTestUPP(ControlUserPaneHitTestProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewControlUserPaneTrackingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlUserPaneTrackingUPP
NewControlUserPaneTrackingUPP(ControlUserPaneTrackingProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewControlUserPaneIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlUserPaneIdleUPP
NewControlUserPaneIdleUPP(ControlUserPaneIdleProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewControlUserPaneKeyDownUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlUserPaneKeyDownUPP
NewControlUserPaneKeyDownUPP(ControlUserPaneKeyDownProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewControlUserPaneActivateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlUserPaneActivateUPP
NewControlUserPaneActivateUPP(ControlUserPaneActivateProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewControlUserPaneFocusUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlUserPaneFocusUPP
NewControlUserPaneFocusUPP(ControlUserPaneFocusProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewControlUserPaneBackgroundUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlUserPaneBackgroundUPP
NewControlUserPaneBackgroundUPP(ControlUserPaneBackgroundProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeControlUserPaneDrawUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlUserPaneDrawUPP(ControlUserPaneDrawUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeControlUserPaneHitTestUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlUserPaneHitTestUPP(ControlUserPaneHitTestUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeControlUserPaneTrackingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlUserPaneTrackingUPP(ControlUserPaneTrackingUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeControlUserPaneIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlUserPaneIdleUPP(ControlUserPaneIdleUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeControlUserPaneKeyDownUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlUserPaneKeyDownUPP(ControlUserPaneKeyDownUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeControlUserPaneActivateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlUserPaneActivateUPP(ControlUserPaneActivateUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeControlUserPaneFocusUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlUserPaneFocusUPP(ControlUserPaneFocusUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeControlUserPaneBackgroundUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlUserPaneBackgroundUPP(ControlUserPaneBackgroundUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeControlUserPaneDrawUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeControlUserPaneDrawUPP(
  ControlRef              control,
  SInt16                  part,
  ControlUserPaneDrawUPP  userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeControlUserPaneHitTestUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlPartCode
InvokeControlUserPaneHitTestUPP(
  ControlRef                 control,
  Point                      where,
  ControlUserPaneHitTestUPP  userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeControlUserPaneTrackingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlPartCode
InvokeControlUserPaneTrackingUPP(
  ControlRef                  control,
  Point                       startPt,
  ControlActionUPP            actionProc,
  ControlUserPaneTrackingUPP  userUPP)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeControlUserPaneIdleUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeControlUserPaneIdleUPP(
  ControlRef              control,
  ControlUserPaneIdleUPP  userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeControlUserPaneKeyDownUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlPartCode
InvokeControlUserPaneKeyDownUPP(
  ControlRef                 control,
  SInt16                     keyCode,
  SInt16                     charCode,
  SInt16                     modifiers,
  ControlUserPaneKeyDownUPP  userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeControlUserPaneActivateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeControlUserPaneActivateUPP(
  ControlRef                  control,
  Boolean                     activating,
  ControlUserPaneActivateUPP  userUPP)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeControlUserPaneFocusUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlPartCode
InvokeControlUserPaneFocusUPP(
  ControlRef               control,
  ControlFocusPart         action,
  ControlUserPaneFocusUPP  userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeControlUserPaneBackgroundUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeControlUserPaneBackgroundUPP(
  ControlRef                    control,
  ControlBackgroundPtr          info,
  ControlUserPaneBackgroundUPP  userUPP)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    ¥ EDIT TEXT (CDEF 17)
  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
/* Edit Text proc IDs */
enum {
  kControlEditTextProc          = 272,
  kControlEditTextPasswordProc  = 274
};

/* proc IDs available with Appearance 1.1 or later */
enum {
  kControlEditTextInlineInputProc = 276 /* Can't combine with the other variants*/
};

/* Control Kind Tag */
enum {
  kControlKindEditText          = 'etxt'
};

/*
 *  CreateEditTextControl()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use CreateEditUnicodeTextControl API instead.
 *  
 *  Summary:
 *    Creates a new edit text control.
 *  
 *  Discussion:
 *    This control is a legacy control. It is deprecated in favor of
 *    the EditUnicodeText control, which handles Unicode and draws its
 *    text using antialiasing.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window in which the control should be placed. May be NULL
 *      in 10.3 and later.
 *    
 *    boundsRect:
 *      The bounds of the control, in local coordinates of the window.
 *    
 *    text:
 *      The text of the control. May be NULL.
 *    
 *    isPassword:
 *      A Boolean indicating whether the field is to be used as a
 *      password field. Passing false indicates that the field is to
 *      display entered text normally. True means that the field will
 *      be used as a password field and any text typed into the field
 *      will be displayed only as bullets.
 *    
 *    useInlineInput:
 *      A Boolean indicating whether or not the control is to accept
 *      inline input. Pass true to to accept inline input, otherwise
 *      pass false.
 *    
 *    style:
 *      The control's font style, size, color, and so on. May be NULL.
 *    
 *    outControl:
 *      On exit, contains the new control (if noErr is returned as the
 *      result code).
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateEditTextControl(
  WindowRef                    window,
  const Rect *                 boundsRect,
  CFStringRef                  text,                 /* can be NULL */
  Boolean                      isPassword,
  Boolean                      useInlineInput,
  const ControlFontStyleRec *  style,                /* can be NULL */
  ControlRef *                 outControl)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/* Tagged data supported by edit text */
enum {
  kControlEditTextStyleTag      = kControlFontStyleTag, /* ControlFontStyleRec*/
  kControlEditTextTextTag       = 'text', /* Buffer of chars - you supply the buffer*/
  kControlEditTextTEHandleTag   = 'than', /* The TEHandle of the text edit record*/
  kControlEditTextKeyFilterTag  = kControlKeyFilterTag,
  kControlEditTextSelectionTag  = 'sele', /* ControlEditTextSelectionRec*/
  kControlEditTextPasswordTag   = 'pass', /* The clear text password text*/
  kControlEditTextCharCount     = 'chrc' /* Count of characters in the control's text*/
};

/* tags available with Appearance 1.1 or later */
enum {
  kControlEditTextKeyScriptBehaviorTag = 'kscr', /* ControlKeyScriptBehavior. Defaults to "PrefersRoman" for password fields,*/
                                        /*       or "AllowAnyScript" for non-password fields.*/
  kControlEditTextLockedTag     = 'lock', /* Boolean. Locking disables editability.*/
  kControlEditTextFixedTextTag  = 'ftxt', /* Like the normal text tag, but fixes inline input first*/
  kControlEditTextValidationProcTag = 'vali', /* ControlEditTextValidationUPP. Called when a key filter can't be: after cut, paste, etc.*/
  kControlEditTextInlinePreUpdateProcTag = 'prup', /* TSMTEPreUpdateUPP and TSMTEPostUpdateUpp. For use with inline input variant...*/
  kControlEditTextInlinePostUpdateProcTag = 'poup' /* ...The refCon parameter will contain the ControlRef.*/
};


/*
 *  Discussion:
 *    EditText ControlData tags available with MacOSX and later.
 */
enum {

  /*
   * Extract the content of the edit text field as a CFString.  Don't
   * forget that you own the returned CFStringRef and are responsible
   * for CFReleasing it.
   */
  kControlEditTextCFStringTag   = 'cfst', /* CFStringRef (Also available on CarbonLib 1.5)*/

  /*
   * Extract the content of the edit text field as a CFString, if it is
   * a password field.  Don't forget that you own the returned
   * CFStringRef and are responsible for CFReleasing it.
   */
  kControlEditTextPasswordCFStringTag = 'pwcf' /* CFStringRef*/
};




/* Structure for getting the edit text selection */
struct ControlEditTextSelectionRec {
  SInt16              selStart;
  SInt16              selEnd;
};
typedef struct ControlEditTextSelectionRec ControlEditTextSelectionRec;
typedef ControlEditTextSelectionRec *   ControlEditTextSelectionPtr;
typedef CALLBACK_API( void , ControlEditTextValidationProcPtr )(ControlRef control);
typedef STACK_UPP_TYPE(ControlEditTextValidationProcPtr)        ControlEditTextValidationUPP;
/*
 *  NewControlEditTextValidationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlEditTextValidationUPP
NewControlEditTextValidationUPP(ControlEditTextValidationProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeControlEditTextValidationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlEditTextValidationUPP(ControlEditTextValidationUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeControlEditTextValidationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeControlEditTextValidationUPP(
  ControlRef                    control,
  ControlEditTextValidationUPP  userUPP)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ STATIC TEXT (CDEF 18)                                                             */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Static Text proc IDs */
enum {
  kControlStaticTextProc        = 288
};

/* Control Kind Tag */
enum {
  kControlKindStaticText        = 'stxt'
};

/* The HIObject class ID for the HIStaticTextView class. */
#define kHIStaticTextViewClassID        CFSTR("com.apple.HIStaticTextView")
/* Creation API: Carbon only */
/*
 *  CreateStaticTextControl()
 *  
 *  Summary:
 *    Creates a new static text control.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window in which the control should be placed. May be NULL
 *      in 10.3 and later.
 *    
 *    boundsRect:
 *      The bounds of the control, in local coordinates of the window.
 *    
 *    text:
 *      The text of the control. May be NULL.
 *    
 *    style:
 *      The control's font style, size, color, and so on. May be NULL.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateStaticTextControl(
  WindowRef                    window,           /* can be NULL */
  const Rect *                 boundsRect,
  CFStringRef                  text,             /* can be NULL */
  const ControlFontStyleRec *  style,            /* can be NULL */
  ControlRef *                 outControl)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  Summary:
 *    Tagged data supported by the static text control
 */
enum {

  /*
   * Used to get or set the control's current text style. Data is of
   * type ControlFontStyleRec. Available with Appearance Manager 1.0
   * (Mac OS 8.0) and later.
   */
  kControlStaticTextStyleTag    = kControlFontStyleTag,

  /*
   * Used to get or set the control's current text. Data is an array of
   * chars. Generally you should used GetControlDataSize to determine
   * the length of the text, and allocate a buffer of that length,
   * before calling GetControlData with this selector. Deprecated in
   * Carbon in favor of kControlStaticTextCFStringTag. Available with
   * Appearance Manager 1.0 (Mac OS 8.0) and later.
   */
  kControlStaticTextTextTag     = 'text',

  /*
   * Used to get the height of the control's text. May not be used with
   * SetControlData. Data is of type SInt16. Available with Appearance
   * Manager 1.0 (Mac OS 8.0) and later.
   */
  kControlStaticTextTextHeightTag = 'thei',

  /*
   * Used to get or set the control's text truncation style. Data is of
   * type TruncCode; pass a truncation code of -1 to indication no
   * truncation. Available with Appearance Manager 1.1 (Mac OS 8.5) and
   * later. Truncation will not occur unless
   * kControlStaticTextIsMultilineTag is set to false.
   */
  kControlStaticTextTruncTag    = 'trun',

  /*
   * Used to get or set the control's current text. Data is of type
   * CFStringRef. When setting the text, the control will retain the
   * string, so you may release the string after calling
   * SetControlData; if the string is mutable, the control will make a
   * copy of the string, so any changes to the string after calling
   * SetControlData will not affect the control. When getting the text,
   * the control retains the string before returning it to you, so you
   * must release the string after you are done with it. Available in
   * CarbonLib 1.5 and Mac OS X 10.0 and later.
   */
  kControlStaticTextCFStringTag = 'cfst',

  /*
   * Used to get or set whether the control draws its text in multiple
   * lines if the text is too wide for the control bounds. If false,
   * then the control always draws the text in a single line. Data is
   * of type Boolean. Available in Mac OS X 10.1 and later.
   */
  kControlStaticTextIsMultilineTag = 'stim'
};


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ PICTURE CONTROL (CDEF 19)                                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  Value parameter should contain the ID of the picture you wish to display when       */
/*  creating controls of this type. If you don't want the control tracked at all, use   */
/*  the 'no track' variant.                                                             */
/* Picture control proc IDs */
enum {
  kControlPictureProc           = 304,
  kControlPictureNoTrackProc    = 305   /* immediately returns kControlPicturePart*/
};

/* Control Kind Tag */
enum {
  kControlKindPicture           = 'pict'
};

/*
 *  CreatePictureControl()
 *  
 *  Summary:
 *    Creates a picture control.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window that should contain the control. May be NULL on 10.3
 *      and later.
 *    
 *    boundsRect:
 *      The bounding box of the control.
 *    
 *    content:
 *      The descriptor for the picture you want the control to display.
 *    
 *    dontTrack:
 *      A Boolean value indicating whether the control should hilite
 *      when it is clicked on. False means hilite and track the mouse.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreatePictureControl(
  WindowRef                         window,           /* can be NULL */
  const Rect *                      boundsRect,
  const ControlButtonContentInfo *  content,
  Boolean                           dontTrack,
  ControlRef *                      outControl)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Tagged data supported by picture controls */
enum {
  kControlPictureHandleTag      = 'pich' /* PicHandle*/
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ ICON CONTROL (CDEF 20)                                                            */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  Value parameter should contain the ID of the ICON or cicn you wish to display when  */
/*  creating controls of this type. If you don't want the control tracked at all, use   */
/*  the 'no track' variant.                                                             */
/* Icon control proc IDs */
enum {
  kControlIconProc              = 320,
  kControlIconNoTrackProc       = 321,  /* immediately returns kControlIconPart*/
  kControlIconSuiteProc         = 322,
  kControlIconSuiteNoTrackProc  = 323   /* immediately returns kControlIconPart*/
};

enum {
                                        /* icon ref controls may have either an icon, color icon, icon suite, or icon ref.*/
                                        /* for data other than icon, you must set the data by passing a*/
                                        /* ControlButtonContentInfo to SetControlData*/
  kControlIconRefProc           = 324,
  kControlIconRefNoTrackProc    = 325   /* immediately returns kControlIconPart*/
};

/* Control Kind Tag */
enum {
  kControlKindIcon              = 'icon'
};

/* The HIObject class ID for the HIIconView class. */
#define kHIIconViewClassID              CFSTR("com.apple.HIIconView")
/*
 *  CreateIconControl()
 *  
 *  Summary:
 *    Creates an Icon control at a specific position in the specified
 *    window.
 *  
 *  Discussion:
 *    Icon controls display an icon that (optionally) hilites when
 *    clicked on. On Mac OS X, a root control will be created for the
 *    window if one does not already exist. If a root control exists
 *    for the window, the Icon control will be embedded into it.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The WindowRef into which the Icon control will be created. May
 *      be NULL on 10.3 and later.
 *    
 *    inBoundsRect:
 *      The desired position (in coordinates local to the window's
 *      port) for the Icon control.
 *    
 *    inIconContent:
 *      The descriptor for the icon you want the control to display.
 *      Mac OS X and CarbonLib 1.5 (and beyond) support all of the icon
 *      content types. Prior to CarbonLib 1.5, the only content types
 *      that are properly respected are kControlContentIconSuiteRes,
 *      kControlContentCIconRes, and kControlContentICONRes.
 *    
 *    inDontTrack:
 *      A Boolean value indicating whether the control should hilite
 *      when it is clicked on. False means hilite and track the mouse.
 *    
 *    outControl:
 *      On successful output, outControl will contain a reference to
 *      the Icon control.
 *  
 *  Result:
 *    An OSStatus code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateIconControl(
  WindowRef                         inWindow,            /* can be NULL */
  const Rect *                      inBoundsRect,
  const ControlButtonContentInfo *  inIconContent,
  Boolean                           inDontTrack,
  ControlRef *                      outControl)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Tagged data supported by icon controls */
enum {
  kControlIconTransformTag      = 'trfm', /* IconTransformType*/
  kControlIconAlignmentTag      = 'algn' /* IconAlignmentType*/
};

/* Tags available with appearance 1.1 or later */
enum {
  kControlIconResourceIDTag     = 'ires', /* SInt16 resource ID of icon to use*/
  kControlIconContentTag        = 'cont' /* accepts a ControlButtonContentInfo*/
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ WINDOW HEADER (CDEF 21)                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Window Header proc IDs */
enum {
  kControlWindowHeaderProc      = 336,  /* normal header*/
  kControlWindowListViewHeaderProc = 337 /* variant for list views - no bottom line*/
};

/* Control Kind Tag */
enum {
  kControlKindWindowHeader      = 'whed'
};


/*
 *  Summary:
 *    Tags available with Mac OS X 10.3 or later
 */
enum {

  /*
   * Passed data is a Boolean.  Set to true if the control is to draw
   * as a list header.
   */
  kControlWindowHeaderIsListHeaderTag = 'islh'
};

/* The HIObject class ID for the HIWindowHeaderView class. */
#define kHIWindowHeaderViewClassID      CFSTR("com.apple.HIWindowHeaderView")
/* Creation API: Carbon Only */
/*
 *  CreateWindowHeaderControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateWindowHeaderControl(
  WindowRef     window,
  const Rect *  boundsRect,
  Boolean       isListHeader,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ LIST BOX (CDEF 22)                                                                */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  Lists use an auxiliary resource to define their format. The resource type used is   */
/*  'ldes' and a definition for it can be found in Appearance.r. The resource ID for    */
/*  the ldes is passed in the 'value' parameter when creating the control. You may pass */
/*  zero in value. This tells the List Box control to not use a resource. The list will */
/*  be created with default values, and will use the standard LDEF (0). You can change  */
/*  the list by getting the list handle. You can set the LDEF to use by using the tag   */
/*  below (kControlListBoxLDEFTag)                                                      */
/* List Box proc IDs */
enum {
  kControlListBoxProc           = 352,
  kControlListBoxAutoSizeProc   = 353
};

/* Control Kind Tag */
enum {
  kControlKindListBox           = 'lbox'
};

/* Creation API: Carbon Only */
/*
 *  CreateListBoxControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateListBoxControl(
  WindowRef            window,
  const Rect *         boundsRect,
  Boolean              autoSize,
  SInt16               numRows,
  SInt16               numColumns,
  Boolean              horizScroll,
  Boolean              vertScroll,
  SInt16               cellHeight,
  SInt16               cellWidth,
  Boolean              hasGrowSpace,
  const ListDefSpec *  listDef,
  ControlRef *         outControl)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Tagged data supported by list box */
enum {
  kControlListBoxListHandleTag  = 'lhan', /* ListHandle*/
  kControlListBoxKeyFilterTag   = kControlKeyFilterTag, /* ControlKeyFilterUPP*/
  kControlListBoxFontStyleTag   = kControlFontStyleTag /* ControlFontStyleRec*/
};

/* New tags in 1.0.1 or later */
enum {
  kControlListBoxDoubleClickTag = 'dblc', /* Boolean. Was last click a double-click?*/
  kControlListBoxLDEFTag        = 'ldef' /* SInt16. ID of LDEF to use.*/
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ PUSH BUTTON (CDEF 23)                                                             */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  The new standard checkbox and radio button controls support a "mixed" value that    */
/*  indicates that the current setting contains a mixed set of on and off values. The   */
/*  control value used to display this indication is defined in Controls.h:             */
/*                                                                                      */
/*      kControlCheckBoxMixedValue = 2                                                  */
/*                                                                                      */
/*  Two new variants of the standard pushbutton have been added to the standard control */
/*  suite that draw a color icon next to the control title. One variant draws the icon  */
/*  on the left side, the other draws it on the right side (when the system justifica-  */
/*  tion is right to left, these are reversed).                                         */
/*                                                                                      */
/*  When either of the icon pushbuttons are created, the contrlMax field of the control */
/*  record is used to determine the ID of the 'cicn' resource drawn in the pushbutton.  */
/*                                                                                      */
/*  In addition, a push button can now be told to draw with a default outline using the */
/*  SetControlData routine with the kControlPushButtonDefaultTag below.                 */
/*                                                                                      */
/*  A push button may also be marked using the kControlPushButtonCancelTag. This has    */
/*  no visible representation, but does cause the button to play the CancelButton theme */
/*  sound instead of the regular pushbutton theme sound when pressed.                   */
/*                                                                                      */
/* Theme Push Button/Check Box/Radio Button proc IDs */
enum {
  kControlPushButtonProc        = 368,
  kControlCheckBoxProc          = 369,
  kControlRadioButtonProc       = 370,
  kControlPushButLeftIconProc   = 374,  /* Standard pushbutton with left-side icon*/
  kControlPushButRightIconProc  = 375   /* Standard pushbutton with right-side icon*/
};

/* Variants with Appearance 1.1 or later */
enum {
  kControlCheckBoxAutoToggleProc = 371,
  kControlRadioButtonAutoToggleProc = 372
};

/* Push Button Icon Alignments */
typedef UInt16 ControlPushButtonIconAlignment;
enum {
  kControlPushButtonIconOnLeft  = 6,
  kControlPushButtonIconOnRight = 7
};

/* Control Kind Tag */
enum {
  kControlKindPushButton        = 'push',
  kControlKindPushIconButton    = 'picn',
  kControlKindRadioButton       = 'rdio',
  kControlKindCheckBox          = 'cbox'
};

/* The HIObject class ID for the HIPushButton class. */
#define kHIPushButtonClassID            CFSTR("com.apple.HIPushButton")
/* The HIObject class ID for the HICheckBox class. */
#define kHICheckBoxClassID              CFSTR("com.apple.HICheckBox")
/* The HIObject class ID for the HIRadioButton class. */
#define kHIRadioButtonClassID           CFSTR("com.apple.HIRadioButton")
/* Creation APIs: Carbon Only */
/*
 *  CreatePushButtonControl()
 *  
 *  Summary:
 *    Creates a push button control.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window that should contain the control. May be NULL on 10.3
 *      and later.
 *    
 *    boundsRect:
 *      The bounds of the control, in local coordinates of the window.
 *    
 *    title:
 *      The control title. May be NULL.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreatePushButtonControl(
  WindowRef     window,
  const Rect *  boundsRect,
  CFStringRef   title,            /* can be NULL */
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CreatePushButtonWithIconControl()
 *  
 *  Summary:
 *    Creates a push button control containing an icon or other
 *    graphical content.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window that should contain the control. May be NULL on 10.3
 *      and later.
 *    
 *    boundsRect:
 *      The bounds of the control, in local coordinates of the window.
 *    
 *    title:
 *      The control title. May be NULL.
 *    
 *    icon:
 *      The control graphic content.
 *    
 *    iconAlignment:
 *      The alignment of the control graphic content.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreatePushButtonWithIconControl(
  WindowRef                        window,
  const Rect *                     boundsRect,
  CFStringRef                      title,               /* can be NULL */
  ControlButtonContentInfo *       icon,
  ControlPushButtonIconAlignment   iconAlignment,
  ControlRef *                     outControl)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  CreateRadioButtonControl()
 *  
 *  Summary:
 *    Creates a radio button control.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window that should contain the control. May be NULL on 10.3
 *      and later.
 *    
 *    boundsRect:
 *      The bounds of the control, in local coordinates of the window.
 *    
 *    title:
 *      The control title. May be NULL.
 *    
 *    initialValue:
 *      The initial value of the control. Should be zero (off), one
 *      (on), or two (mixed). The control is automatically given a
 *      minimum value of zero and a maximum value of two.
 *    
 *    autoToggle:
 *      Whether this control should have auto-toggle behavior. If true,
 *      the control will automatically toggle between on and off states
 *      when clicked. This parameter should be false if the control
 *      will be embedded into a radio group control; in that case, the
 *      radio group will handle setting the correct control value in
 *      response to a click.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateRadioButtonControl(
  WindowRef     window,
  const Rect *  boundsRect,
  CFStringRef   title,              /* can be NULL */
  SInt32        initialValue,
  Boolean       autoToggle,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CreateCheckBoxControl()
 *  
 *  Summary:
 *    Creates a checkbox control.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window that should contain the control. May be NULL on 10.3
 *      and later.
 *    
 *    boundsRect:
 *      The bounds of the control, in local coordinates of the window.
 *    
 *    title:
 *      The control title. May be NULL.
 *    
 *    initialValue:
 *      The initial value of the control. Should be zero (off), one
 *      (on), or two (mixed). The control is automatically given a
 *      minimum value of zero and a maximum value of two.
 *    
 *    autoToggle:
 *      Whether this control should have auto-toggle behavior. If true,
 *      the control will automatically toggle between on and off states
 *      when clicked.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateCheckBoxControl(
  WindowRef     window,
  const Rect *  boundsRect,
  CFStringRef   title,              /* can be NULL */
  SInt32        initialValue,
  Boolean       autoToggle,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/* Tagged data supported by standard buttons */
enum {
  kControlPushButtonDefaultTag  = 'dflt', /* default ring flag*/
  kControlPushButtonCancelTag   = 'cncl' /* cancel button flag (1.1 and later)*/
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ SCROLL BAR (CDEF 24)                                                              */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  This is the new Appearance scroll bar.                                              */
/*                                                                                      */
/*                                                                                      */
/*  Mac OS X has a "Scroll to here" option in the General pane of System Preferences    */
/*  which allows users to click in the page up/down regions of a scroll bar and have    */
/*  the thumb/indicator jump directly to the clicked position, which alters the value   */
/*  of the scroll bar and moves the scrolled content appropriately. As long as the      */
/*  mouse button is held down, the click is treated as though the user had clicked in   */
/*  the thumb/indicator in the first place.                                             */
/*                                                                                      */
/*  If you want the scroll bars in your application to work with the "Scroll to here"   */
/*  option, you must do the following:                                                  */
/*                                                                                      */
/*  1. Create live-tracking scroll bars, not scroll bars that show a "ghost" thumb      */
/*  when you click on it. You can request live-tracking scroll bars by passing true     */
/*  in the liveTracking parameter to CreateScrollBarControl. If you create scroll bars  */
/*  with NewControl, use the kControlScrollBarLiveProc.                                 */
/*                                                                                      */
/*  2. Write an appropriate ControlActionProc and associate it with your scroll bar     */
/*  via the SetControlAction API. This allows your application to update its content    */
/*  appropriately when the live-tracking scroll bar is clicked.                         */
/*                                                                                      */
/*  3. When calling HandleControlClick or TrackControl, pass -1 in the action proc      */
/*  parameter. This is a request for the Control Manager to use the action proc you     */
/*  associated with your control in step 2. If you rely on the standard window event    */
/*  handler to do your control tracking, this step is handled for you automatically.    */
/*                                                                                      */
/* Theme Scroll Bar proc IDs */
enum {
  kControlScrollBarProc         = 384,  /* normal scroll bar*/
  kControlScrollBarLiveProc     = 386   /* live scrolling variant*/
};

/* Control Kind Tag */
enum {
  kControlKindScrollBar         = 'sbar'
};

/* The HIObject class ID for the HIScrollBar class. */
#define kHIScrollBarClassID             CFSTR("com.apple.HIScrollBar")
/*
 *  CreateScrollBarControl()
 *  
 *  Summary:
 *    Creates a scroll bar control.
 *  
 *  Discussion:
 *    This creation API is available in Carbon only.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window that should contain the control. May be NULL on 10.3
 *      and later.
 *    
 *    boundsRect:
 *      The bounding box of the control.
 *    
 *    value:
 *      The initial value of the control.
 *    
 *    minimum:
 *      The minimum value of the control.
 *    
 *    maximum:
 *      The maximum value of the control.
 *    
 *    viewSize:
 *      The size of the visible area of the scroll bar content.
 *    
 *    liveTracking:
 *      A Boolean indicating whether or not live tracking is enabled
 *      for this scroll bar. If set to true and a valid
 *      liveTrackingProc is also passed in, the callback will be called
 *      repeatedly as the thumb is moved during tracking.  If set to
 *      false, a semi-transparent thumb called a "ghost thumb" will
 *      draw and no live tracking will occur.
 *    
 *    liveTrackingProc:
 *      If liveTracking is on, a ControlActionUPP callback to be called
 *      as the control live tracks.  This callback is called repeatedly
 *      as the scroll thumb is moved during tracking.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateScrollBarControl(
  WindowRef          window,
  const Rect *       boundsRect,
  SInt32             value,
  SInt32             minimum,
  SInt32             maximum,
  SInt32             viewSize,
  Boolean            liveTracking,
  ControlActionUPP   liveTrackingProc,
  ControlRef *       outControl)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* These tags are available in Mac OS X or later */
enum {
  kControlScrollBarShowsArrowsTag = 'arro' /* Boolean whether or not to draw the scroll arrows*/
};


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ POPUP BUTTON (CDEF 25)                                                            */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  This is the new Appearance Popup Button. It takes the same variants and does the    */
/*  same overloading as the previous popup menu control. There are some differences:    */
/*                                                                                      */
/*  Passing in a menu ID of -12345 causes the popup not to try and get the menu from a  */
/*  resource. Instead, you can build the menu and later stuff the MenuRef field in      */
/*  the popup data information.                                                         */
/*                                                                                      */
/*  You can pass -1 in the Max parameter to have the control calculate the width of the */
/*  title on its own instead of guessing and then tweaking to get it right. It adds the */
/*  appropriate amount of space between the title and the popup.                        */
/*                                                                                      */
/* Theme Popup Button proc IDs */
enum {
  kControlPopupButtonProc       = 400,
  kControlPopupFixedWidthVariant = 1 << 0,
  kControlPopupVariableWidthVariant = 1 << 1,
  kControlPopupUseAddResMenuVariant = 1 << 2,
  kControlPopupUseWFontVariant  = kControlUsesOwningWindowsFontVariant
};

/* Control Kind Tag */
enum {
  kControlKindPopupButton       = 'popb'
};

/* The HIObject class ID for the HIPopupButton class. */
#define kHIPopupButtonClassID           CFSTR("com.apple.HIPopupButton")
/*
 *  CreatePopupButtonControl()
 *  
 *  Summary:
 *    Creates a popup button control.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window that should contain the control. May be NULL on 10.3
 *      and later.
 *    
 *    boundsRect:
 *      The bounding box of the control.
 *    
 *    title:
 *      The title of the control.
 *    
 *    menuID:
 *      The ID of a menu that should be used by the control. A menu
 *      with this ID should be inserted into the menubar with
 *      InsertMenu(menu, kInsertHierarchicalMenu). You can also pass
 *      -12345 to have the control delay its acquisition of a menu; in
 *      this case, you can build the menu and later provide it to the
 *      control with SetControlData and kControlPopupButtonMenuRefTag
 *      or kControlPopupButtonOwnedMenuRefTag.
 *    
 *    variableWidth:
 *      Whether the width of the control is allowed to vary according
 *      to the width of the selected menu item text, or should remain
 *      fixed to the original control bounds width.
 *    
 *    titleWidth:
 *      The width of the title.
 *    
 *    titleJustification:
 *      The justification of the title.
 *    
 *    titleStyle:
 *      A QuickDraw style bitfield indicating the font style of the
 *      title.
 *    
 *    outControl:
 *      On exit, contains the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreatePopupButtonControl(
  WindowRef     window,                   /* can be NULL */
  const Rect *  boundsRect,
  CFStringRef   title,
  SInt16        menuID,
  Boolean       variableWidth,
  SInt16        titleWidth,
  SInt16        titleJustification,
  Style         titleStyle,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* These tags are available in 1.0.1 or later of Appearance */
enum {
  kControlPopupButtonMenuHandleTag = 'mhan', /* MenuRef*/
  kControlPopupButtonMenuRefTag = 'mhan', /* MenuRef*/
  kControlPopupButtonMenuIDTag  = 'mnid' /* SInt16*/
};

/* These tags are available in 1.1 or later of Appearance */
enum {
  kControlPopupButtonExtraHeightTag = 'exht', /* SInt16 - extra vertical whitespace within the button*/
  kControlPopupButtonOwnedMenuRefTag = 'omrf' /* MenuRef*/
};

/* These tags are available in Mac OS X */
enum {
  kControlPopupButtonCheckCurrentTag = 'chck' /* Boolean    - whether the popup puts a checkmark next to the current item (defaults to true)*/
};


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ RADIO GROUP (CDEF 26)                                                             */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  This control implements a radio group. It is an embedding control and can therefore */
/*  only be used when a control hierarchy is established for its owning window. You     */
/*  should only embed radio buttons within it. As radio buttons are embedded into it,   */
/*  the group sets up its value, min, and max to represent the number of embedded items.*/
/*  The current value of the control is the index of the sub-control that is the current*/
/*  'on' radio button. To get the current radio button control handle, you can use the  */
/*  control manager call GetIndSubControl, passing in the value of the radio group.     */
/*                                                                                      */
/*  Note that when creating radio buttons for use in a radio group control, you should  */
/*  not use the autoToggle version of the radio button. The radio group control will    */
/*  handling toggling the radio button values itself; auto-toggle radio buttons do not  */
/*  work properly in a radio group control on Mac OS 9.                                 */
/*                                                                                      */
/*  NOTE: This control is only available with Appearance 1.0.1.                         */
/* Radio Group Proc ID */
enum {
  kControlRadioGroupProc        = 416
};

/* Control Kind Tag */
enum {
  kControlKindRadioGroup        = 'rgrp'
};

/* The HIObject class ID for the HIRadioGroup class. */
#define kHIRadioGroupClassID            CFSTR("com.apple.HIRadioGroup")
/* Creation API: Carbon Only */
/*
 *  CreateRadioGroupControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateRadioGroupControl(
  WindowRef     window,
  const Rect *  boundsRect,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ SCROLL TEXT BOX (CDEF 27)                                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  This control implements a scrolling box of (non-editable) text. This is useful for  */
/*  credits in about boxes, etc.                                                        */
/*  The standard version of this control has a scroll bar, but the autoscrolling        */
/*  variant does not. The autoscrolling variant needs two pieces of information to      */
/*  work: delay (in ticks) before the scrolling starts, and time (in ticks) between     */
/*  scrolls. It will scroll one pixel at a time, unless changed via SetControlData.     */
/*                                                                                      */
/*  Parameter                   What Goes Here                                          */
/*  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ         ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ    */
/*  Value                       Resource ID of 'TEXT'/'styl' content.                   */
/*  Min                         Scroll start delay (in ticks)                       .   */
/*  Max                         Delay (in ticks) between scrolls.                       */
/*                                                                                      */
/*  NOTE: This control is only available with Appearance 1.1.                           */
/* Scroll Text Box Proc IDs */
enum {
  kControlScrollTextBoxProc     = 432,
  kControlScrollTextBoxAutoScrollProc = 433
};

/* Control Kind Tag */
enum {
  kControlKindScrollingTextBox  = 'stbx'
};

/* Creation API: Carbon Only */
/*
 *  CreateScrollingTextBoxControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateScrollingTextBoxControl(
  WindowRef     window,
  const Rect *  boundsRect,
  SInt16        contentResID,
  Boolean       autoScroll,
  UInt32        delayBeforeAutoScroll,
  UInt32        delayBetweenAutoScroll,
  UInt16        autoScrollAmount,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Tagged data supported by Scroll Text Box */
enum {
  kControlScrollTextBoxDelayBeforeAutoScrollTag = 'stdl', /* UInt32 (ticks until autoscrolling starts)*/
  kControlScrollTextBoxDelayBetweenAutoScrollTag = 'scdl', /* UInt32 (ticks between scrolls)*/
  kControlScrollTextBoxAutoScrollAmountTag = 'samt', /* UInt16 (pixels per scroll) -- defaults to 1*/
  kControlScrollTextBoxContentsTag = 'tres', /* SInt16 (resource ID of 'TEXT'/'styl') -- write only!*/
  kControlScrollTextBoxAnimatingTag = 'anim' /* Boolean (whether the text box should auto-scroll)*/
};


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ DISCLOSURE BUTTON                                                                 */
/*  (CDEF 30)                                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* The HIObject class ID for the HIDisclosureButton class. */
#define kHIDisclosureButtonClassID      CFSTR("com.apple.HIDisclosureButton")
/*
 *  CreateDisclosureButtonControl()
 *  
 *  Summary:
 *    Creates a new instance of the Disclosure Button Control.
 *  
 *  Discussion:
 *    CreateDisclosureButtonControl is preferred over NewControl
 *    because it allows you to specify the exact set of parameters
 *    required to create the control without overloading parameter
 *    semantics. The initial minimum of the Disclosure Button will be
 *    kControlDisclosureButtonClosed, and the maximum will be
 *    kControlDisclosureButtonDisclosed.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The WindowRef in which to create the control.
 *    
 *    inBoundsRect:
 *      The bounding rectangle for the control. The height of the
 *      control is fixed and the control will be centered vertically
 *      within the rectangle you specify.
 *    
 *    inValue:
 *      The initial value; either kControlDisclosureButtonClosed or
 *      kControlDisclosureButtonDisclosed.
 *    
 *    inAutoToggles:
 *      A boolean value indicating whether its value should change
 *      automatically after tracking the mouse.
 *    
 *    outControl:
 *      On successful exit, this will contain the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateDisclosureButtonControl(
  WindowRef     inWindow,
  const Rect *  inBoundsRect,
  SInt32        inValue,
  Boolean       inAutoToggles,
  ControlRef *  outControl)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Control Kind Tag */
enum {
  kControlKindDisclosureButton  = 'disb'
};


/*
 *  Discussion:
 *    Disclosure Button Values
 */
enum {

  /*
   * The control be drawn suggesting a closed state.
   */
  kControlDisclosureButtonClosed = 0,

  /*
   * The control will be drawn suggesting an open state.
   */
  kControlDisclosureButtonDisclosed = 1
};


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ ROUND BUTTON                                                                      */
/*  (CDEF 31)                                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

/*
 *  ControlRoundButtonSize
 *  
 *  Discussion:
 *    Button Sizes
 */
typedef SInt16 ControlRoundButtonSize;
enum {

  /*
   * A 20 pixel diameter button.
   */
  kControlRoundButtonNormalSize = kControlSizeNormal,

  /*
   * A 25 pixel diameter button.
   */
  kControlRoundButtonLargeSize  = kControlSizeLarge
};

/* Data tags supported by the round button controls */
enum {
  kControlRoundButtonContentTag = 'cont', /* ControlButtonContentInfo*/
  kControlRoundButtonSizeTag    = kControlSizeTag /* ControlRoundButtonSize*/
};

/* Control Kind Tag */
enum {
  kControlKindRoundButton       = 'rndb'
};

/* The HIObject class ID for the HIRoundButton class. */
#define kHIRoundButtonClassID           CFSTR("com.apple.HIRoundButton")
/*
 *  CreateRoundButtonControl()
 *  
 *  Summary:
 *    Creates a new instance of the Round Button Control.
 *  
 *  Discussion:
 *    CreateRoundButtonControl is preferred over NewControl because it
 *    allows you to specify the exact set of parameters required to
 *    create the control without overloading parameter semantics.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inWindow:
 *      The WindowRef in which to create the control. May be NULL in
 *      10.3 and later.
 *    
 *    inBoundsRect:
 *      The bounding rectangle for the control. The height and width of
 *      the control is fixed (specified by the ControlRoundButtonSize
 *      parameter) and the control will be centered within the
 *      rectangle you specify.
 *    
 *    inSize:
 *      The button size; either kControlRoundButtonNormalSize or
 *      kControlRoundButtonLargeSize.
 *    
 *    inContent:
 *      Any optional content displayed in the button. Currently only
 *      kControlContentIconRef is supported. May be NULL.
 *    
 *    outControl:
 *      On successful exit, this will contain the new control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateRoundButtonControl(
  WindowRef                   inWindow,           /* can be NULL */
  const Rect *                inBoundsRect,
  ControlRoundButtonSize      inSize,
  ControlButtonContentInfo *  inContent,          /* can be NULL */
  ControlRef *                outControl)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*    ¥ DATA BROWSER                                                                    */
/*     (CDEF 29)                                                                        */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  This control implements a user interface component for browsing (optionally)        */
/*  hiearchical data structures. The browser supports multiple presentation styles      */
/*  including, but not limited to:                                                      */
/*                                                                                      */
/*      kDataBrowserListView   - items and item properties in                           */
/*                               multi-column (optionally outline) format               */
/*      kDataBrowserColumnView - in-place browsing using fixed navigation columns       */
/*                                                                                      */
/*  The browser manages all view styles through a single high-level interface.          */
/*  The high-level interface makes the following assumptions:                           */
/*                                                                                      */
/*      - Items have unique 32-bit identifiers (0 is reserved)                          */
/*                                                                                      */
/*      - Items have two kinds of named and typed properties:                           */
/*           - Predefined attribute properties ( < 1024 )                               */
/*             (including some display properties)                                      */
/*           - Client-defined display properties ( >= 1024 )                            */
/*                                                                                      */
/*      - Some items are containers of other items                                      */
/*      - Items may be sorted by any property                                           */
/*                                                                                      */
/*  Because a browser doesn't know all details about the type of objects it manages,    */
/*  some implementation responsibility is best handled by its client. The client must   */
/*  provide a set of callback routines which define the item hierarchy and help to      */
/*  populate the browser with items. The client may also provide callbacks for handling */
/*  custom data types and doing low-level event management.                             */
/*                                                                                      */
/*  The API is subdivided into a "universal" set of routines that applies to all view   */
/*  styles, and a set of routines unique to each view style. kDataBrowserListView and   */
/*  kDataBrowserColumnView share an (internal) TableView abstract base class. The       */
/*  TableView formatting options and API applies to both of these view styles.          */
/*                                                                                      */
/*  NOTE: This control is only available with CarbonLib 1.1.                            */
/*                                                                                      */
/*  NOTE: This control must be created with the CreateDataBrowserControl API in         */
/*        CarbonLib 1.1 through 1.4. In Mac OS X and CarbonLib 1.5 and later, you       */
/*        may use the control's procID (29) to create the control with NewControl       */
/*        or with a 'CNTL' resource.                                                    */
/* The HIObject class ID for the HIDataBrowser class. */
#define kHIDataBrowserClassID           CFSTR("com.apple.HIDataBrowser")
/* Control Kind Tag */
enum {
  kControlKindDataBrowser       = 'datb'
};

/* Error Codes */
enum {
  errDataBrowserNotConfigured   = -4970,
  errDataBrowserItemNotFound    = -4971,
  errDataBrowserItemNotAdded    = -4975,
  errDataBrowserPropertyNotFound = -4972,
  errDataBrowserInvalidPropertyPart = -4973,
  errDataBrowserInvalidPropertyData = -4974,
  errDataBrowserPropertyNotSupported = -4979 /* Return from DataBrowserGetSetItemDataProc */
};

enum {
                                        /* Generic Control Tags */
  kControlDataBrowserIncludesFrameAndFocusTag = 'brdr', /* Boolean */
  kControlDataBrowserKeyFilterTag = kControlEditTextKeyFilterTag,
  kControlDataBrowserEditTextKeyFilterTag = kControlDataBrowserKeyFilterTag,
  kControlDataBrowserEditTextValidationProcTag = kControlEditTextValidationProcTag
};

/* Data Browser View Styles */
typedef OSType                          DataBrowserViewStyle;
enum {
  kDataBrowserNoView            = 0x3F3F3F3F, /* Error State */
  kDataBrowserListView          = 'lstv',
  kDataBrowserColumnView        = 'clmv'
};

/* Selection Flags */
typedef UInt32 DataBrowserSelectionFlags;
enum {
  kDataBrowserDragSelect        = 1 << 0, /* Å ListMgr lNoRect */
  kDataBrowserSelectOnlyOne     = 1 << 1, /* Å ListMgr lOnlyOne */
  kDataBrowserResetSelection    = 1 << 2, /* Å ListMgr lNoExtend */
  kDataBrowserCmdTogglesSelection = 1 << 3, /* Å ListMgr lUseSense */
  kDataBrowserNoDisjointSelection = 1 << 4, /* Å ListMgr lNoDisjoint */
  kDataBrowserAlwaysExtendSelection = 1 << 5, /* Å ListMgr lExtendDrag */
  kDataBrowserNeverEmptySelectionSet = 1 << 6 /* Å ListMgr lNoNilHilite */
};

/* Data Browser Sorting */
typedef UInt16 DataBrowserSortOrder;
enum {
  kDataBrowserOrderUndefined    = 0,    /* Not currently supported */
  kDataBrowserOrderIncreasing   = 1,
  kDataBrowserOrderDecreasing   = 2
};

/* Data Browser Item Management */
typedef UInt32 DataBrowserItemID;
enum {
  kDataBrowserNoItem            = 0L    /* Reserved DataBrowserItemID */
};

typedef UInt32 DataBrowserItemState;
enum {
  kDataBrowserItemNoState       = 0,
  kDataBrowserItemAnyState      = (unsigned long)(-1),
  kDataBrowserItemIsSelected    = 1 << 0,
  kDataBrowserContainerIsOpen   = 1 << 1,
  kDataBrowserItemIsDragTarget  = 1 << 2 /* During a drag operation */
};

/* Options for use with RevealDataBrowserItem */
typedef UInt8 DataBrowserRevealOptions;
enum {
  kDataBrowserRevealOnly        = 0,
  kDataBrowserRevealAndCenterInView = 1 << 0,
  kDataBrowserRevealWithoutSelecting = 1 << 1
};

/* Set operations for use with SetDataBrowserSelectedItems */
typedef UInt32 DataBrowserSetOption;
enum {
  kDataBrowserItemsAdd          = 0,    /* add specified items to existing set */
  kDataBrowserItemsAssign       = 1,    /* assign destination set to specified items */
  kDataBrowserItemsToggle       = 2,    /* toggle membership state of specified items */
  kDataBrowserItemsRemove       = 3     /* remove specified items from existing set */
};

/* Commands for use with MoveDataBrowserSelectionAnchor */
typedef UInt32 DataBrowserSelectionAnchorDirection;
enum {
  kDataBrowserSelectionAnchorUp = 0,
  kDataBrowserSelectionAnchorDown = 1,
  kDataBrowserSelectionAnchorLeft = 2,
  kDataBrowserSelectionAnchorRight = 3
};

/* Edit menu command IDs for use with Enable/ExecuteDataBrowserEditCommand */
typedef UInt32 DataBrowserEditCommand;
enum {
  kDataBrowserEditMsgUndo       = kHICommandUndo,
  kDataBrowserEditMsgRedo       = kHICommandRedo,
  kDataBrowserEditMsgCut        = kHICommandCut,
  kDataBrowserEditMsgCopy       = kHICommandCopy,
  kDataBrowserEditMsgPaste      = kHICommandPaste,
  kDataBrowserEditMsgClear      = kHICommandClear,
  kDataBrowserEditMsgSelectAll  = kHICommandSelectAll
};

/* Notifications used in DataBrowserItemNotificationProcPtr */
typedef UInt32 DataBrowserItemNotification;
enum {
  kDataBrowserItemAdded         = 1,    /* The specified item has been added to the browser */
  kDataBrowserItemRemoved       = 2,    /* The specified item has been removed from the browser */
  kDataBrowserEditStarted       = 3,    /* Starting an EditText session for specified item */
  kDataBrowserEditStopped       = 4,    /* Stopping an EditText session for specified item */
  kDataBrowserItemSelected      = 5,    /* Item has just been added to the selection set */
  kDataBrowserItemDeselected    = 6,    /* Item has just been removed from the selection set */
  kDataBrowserItemDoubleClicked = 7,
  kDataBrowserContainerOpened   = 8,    /* Container is open */
  kDataBrowserContainerClosing  = 9,    /* Container is about to close (and will real soon now, y'all) */
  kDataBrowserContainerClosed   = 10,   /* Container is closed (y'all come back now!) */
  kDataBrowserContainerSorting  = 11,   /* Container is about to be sorted (lock any volatile properties) */
  kDataBrowserContainerSorted   = 12,   /* Container has been sorted (you may release any property locks) */
  kDataBrowserUserToggledContainer = 16, /* _User_ requested container open/close state to be toggled */
  kDataBrowserTargetChanged     = 15,   /* The target has changed to the specified item */
  kDataBrowserUserStateChanged  = 13,   /* The user has reformatted the view for the target */
  kDataBrowserSelectionSetChanged = 14  /* The selection set has been modified (net result may be the same) */
};


/*
 *  DataBrowserPropertyID
 *  
 *  Discussion:
 *    Properties with values 0 through 1023 are reserved for Apple's
 *    use. Values greater than or equal to 1024 are for client use.
 */
typedef UInt32 DataBrowserPropertyID;
enum {
                                        /* Predefined attribute properties, optional & non-display unless otherwise stated */
  kDataBrowserItemNoProperty    = 0L,   /* The anti-property (no associated data) */
  kDataBrowserItemIsActiveProperty = 1L, /* Boolean typed data (defaults to true) */
  kDataBrowserItemIsSelectableProperty = 2L, /* Boolean typed data (defaults to true) */
  kDataBrowserItemIsEditableProperty = 3L, /* Boolean typed data (defaults to false, used for editable properties) */
  kDataBrowserItemIsContainerProperty = 4L, /* Boolean typed data (defaults to false) */
  kDataBrowserContainerIsOpenableProperty = 5L, /* Boolean typed data (defaults to true) */
  kDataBrowserContainerIsClosableProperty = 6L, /* Boolean typed data (defaults to true) */
  kDataBrowserContainerIsSortableProperty = 7L, /* Boolean typed data (defaults to true) */
  kDataBrowserItemSelfIdentityProperty = 8L, /* kDataBrowserIconAndTextType (display property; ColumnView only) */

  /*
   * kDataBrowserContainerAliasIDProperty is sent to your
   * DataBrowserItemDataProcPtr callback to give you a chance to follow
   * an alias or symlink that the item might represent. If the incoming
   * item is an alias to another item, you can call
   * SetDataBrowserItemDataItemID to let Data Browser know which other
   * item the incoming item points to. 
   * 
   * This is only sent from column view, and your support for it is
   * optional. It allows Data Browser to be more memory efficient with
   * its internal storage. If a given container item is an alias to an
   * item whose contents are already displayed in an existing column
   * view column, the contents can be shared between those two columns.
   */
  kDataBrowserContainerAliasIDProperty = 9L, /* DataBrowserItemID (alias/symlink an item to a container item) */

  /*
   * kDataBrowserColumnViewPreviewProperty is sent to various callbacks
   * to give you a chance to draw or track in the preview column of
   * column view. 
   * 
   * You can also pass kDataBrowserColumnViewPreviewProperty in the
   * property parameter of RevealDataBrowserItem in conjunction with
   * the appropriate DataBrowserItemID of the item whose preview is
   * being displayed when you want to make sure the preview column is
   * visible to the user. 
   * 
   * kDataBrowserColumnViewPreviewProperty is only supported in column
   * view.
   */
  kDataBrowserColumnViewPreviewProperty = 10L, /* kDataBrowserCustomType (display property; ColumnView only) */

  /*
   * kDataBrowserItemParentContainerProperty is sent to your
   * DataBrowserItemDataProcPtr callback when Data Browser needs to
   * know the parent container item for a given item. 
   * 
   * In column view, this allows the internals of SetDataBrowserTarget
   * to work. The target is the container whose contents you wish to
   * display, which is the rightmost column in column view. However,
   * unlike SetDataBrowserColumnViewPath, SetDataBrowserTarget doesn't
   * offer a way for you to communicate the DataBrowserItemIDs of the
   * rest of the column containers, so SetDataBrowserTarget needs to
   * ask for them explicitly by asking for the container's parent, then
   * the container's parent's parent, and so on. 
   * 
   * In list view, this allows you to pass a non-container to
   * SetDataBrowserTarget. In this situation, Data Browser will ask you
   * for the parent of the target so it knows which container to
   * display the contents of in the list view. 
   * 
   * In both list and column views, your DataBrowserItemDataProcPtr
   * callback might be called with
   * kDataBrowserItemParentContainerProperty at a variety of other
   * times, so you should be sure to support this property if your Data
   * Browser displays a containment hierarchy.
   */
  kDataBrowserItemParentContainerProperty = 11L /* DataBrowserItemID (the parent of the specified item, used by ColumnView) */
};

/* DataBrowser Property Types (for display properties; i.e. ListView columns) */
/*      These are primarily presentation types (or styles) although         */
/*      they also imply a particular set of primitive types or structures.  */
typedef OSType                          DataBrowserPropertyType;
enum {
                                        /* == Corresponding data type or structure == */
  kDataBrowserCustomType        = 0x3F3F3F3F, /* No associated data, custom callbacks used */
  kDataBrowserIconType          = 'icnr', /* IconRef, IconTransformType, RGBColor */
  kDataBrowserTextType          = 'text', /* CFStringRef */
  kDataBrowserDateTimeType      = 'date', /* DateTime or LongDateTime */
  kDataBrowserSliderType        = 'sldr', /* Min, Max, Value */
  kDataBrowserCheckboxType      = 'chbx', /* ThemeButtonValue */
  kDataBrowserProgressBarType   = 'prog', /* Min, Max, Value */
  kDataBrowserRelevanceRankType = 'rank', /* Min, Max, Value */
  kDataBrowserPopupMenuType     = 'menu', /* MenuRef, Value */
  kDataBrowserIconAndTextType   = 'ticn' /* IconRef, CFStringRef, etc */
};

/* DataBrowser Property Parts */
/*      Visual components of a property type.      */
/*      For use with GetDataBrowserItemPartBounds. */
typedef OSType                          DataBrowserPropertyPart;
enum {
  kDataBrowserPropertyEnclosingPart = 0L,
  kDataBrowserPropertyContentPart = '----',
  kDataBrowserPropertyDisclosurePart = 'disc',
  kDataBrowserPropertyTextPart  = kDataBrowserTextType,
  kDataBrowserPropertyIconPart  = kDataBrowserIconType,
  kDataBrowserPropertySliderPart = kDataBrowserSliderType,
  kDataBrowserPropertyCheckboxPart = kDataBrowserCheckboxType,
  kDataBrowserPropertyProgressBarPart = kDataBrowserProgressBarType,
  kDataBrowserPropertyRelevanceRankPart = kDataBrowserRelevanceRankType
};

/* Modify appearance/behavior of display properties */
typedef unsigned long                   DataBrowserPropertyFlags;
/* Low 8 bits apply to all property types */
enum {
  kDataBrowserUniversalPropertyFlagsMask = 0xFF,
  kDataBrowserPropertyIsMutable = 1 << 0,
  kDataBrowserDefaultPropertyFlags = 0 << 0,
  kDataBrowserUniversalPropertyFlags = kDataBrowserUniversalPropertyFlagsMask, /* support for an old name*/
  kDataBrowserPropertyIsEditable = kDataBrowserPropertyIsMutable /* support for an old name*/
};

/* Next 8 bits contain property-specific modifiers */

/*
 *  Summary:
 *    Data Browser Property Flags
 */
enum {
  kDataBrowserPropertyFlagsOffset = 8,
  kDataBrowserPropertyFlagsMask = 0xFF << kDataBrowserPropertyFlagsOffset,
  kDataBrowserCheckboxTriState  = 1 << kDataBrowserPropertyFlagsOffset, /* kDataBrowserCheckboxType*/
  kDataBrowserDateTimeRelative  = 1 << (kDataBrowserPropertyFlagsOffset), /* kDataBrowserDateTimeType */
  kDataBrowserDateTimeDateOnly  = 1 << (kDataBrowserPropertyFlagsOffset + 1), /* kDataBrowserDateTimeType */
  kDataBrowserDateTimeTimeOnly  = 1 << (kDataBrowserPropertyFlagsOffset + 2), /* kDataBrowserDateTimeType */
  kDataBrowserDateTimeSecondsToo = 1 << (kDataBrowserPropertyFlagsOffset + 3), /* kDataBrowserDateTimeType */
  kDataBrowserSliderPlainThumb  = kThemeThumbPlain << kDataBrowserPropertyFlagsOffset, /* kDataBrowserSliderType */
  kDataBrowserSliderUpwardThumb = kThemeThumbUpward << kDataBrowserPropertyFlagsOffset, /* kDataBrowserSliderType */
  kDataBrowserSliderDownwardThumb = kThemeThumbDownward << kDataBrowserPropertyFlagsOffset, /* kDataBrowserSliderType */
  kDataBrowserDoNotTruncateText = 3 << kDataBrowserPropertyFlagsOffset, /* kDataBrowserTextType && kDataBrowserIconAndTextType */
  kDataBrowserTruncateTextAtEnd = 2 << kDataBrowserPropertyFlagsOffset, /* kDataBrowserTextType && kDataBrowserIconAndTextType */
  kDataBrowserTruncateTextMiddle = 0 << kDataBrowserPropertyFlagsOffset, /* kDataBrowserTextType && kDataBrowserIconAndTextType */
  kDataBrowserTruncateTextAtStart = 1 << kDataBrowserPropertyFlagsOffset, /* kDataBrowserTextType && kDataBrowserIconAndTextType */

  /*
   * This flag is only for use with columns of type
   * kDataBrowserPopupMenuType. This flag indicates that the popup be
   * drawn in a sleek buttonless fashion. The text will be drawn next
   * to a popup glyph, and the whole cell will be clickable. Available
   * on 10.4 and later.
   */
  kDataBrowserPopupMenuButtonless = 1 << kDataBrowserPropertyFlagsOffset, /* kDataBrowserPopupMenuType*/
  kDataBrowserPropertyModificationFlags = kDataBrowserPropertyFlagsMask, /* support for an old name*/
  kDataBrowserRelativeDateTime  = kDataBrowserDateTimeRelative /* support for an old name*/
};

/*
   Next 8 bits contain viewStyle-specific modifiers 
   See individual ViewStyle sections below for flag definitions 
*/
enum {
  kDataBrowserViewSpecificFlagsOffset = 16,
  kDataBrowserViewSpecificFlagsMask = 0xFF << kDataBrowserViewSpecificFlagsOffset,
  kDataBrowserViewSpecificPropertyFlags = kDataBrowserViewSpecificFlagsMask /* support for an old name*/
};

/* High 8 bits are reserved for client application use */
enum {
  kDataBrowserClientPropertyFlagsOffset = 24,
  kDataBrowserClientPropertyFlagsMask = (unsigned long)(0xFF << kDataBrowserClientPropertyFlagsOffset)
};

/* Client defined property description */
struct DataBrowserPropertyDesc {
  DataBrowserPropertyID  propertyID;
  DataBrowserPropertyType  propertyType;
  DataBrowserPropertyFlags  propertyFlags;
};
typedef struct DataBrowserPropertyDesc  DataBrowserPropertyDesc;
/* Callback definition for use with ForEachDataBrowserItem */
typedef CALLBACK_API( void , DataBrowserItemProcPtr )(DataBrowserItemID item, DataBrowserItemState state, void *clientData);
typedef STACK_UPP_TYPE(DataBrowserItemProcPtr)                  DataBrowserItemUPP;
/*
 *  NewDataBrowserItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserItemUPP
NewDataBrowserItemUPP(DataBrowserItemProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDataBrowserItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserItemUPP(DataBrowserItemUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDataBrowserItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokeDataBrowserItemUPP(
  DataBrowserItemID     item,
  DataBrowserItemState  state,
  void *                clientData,
  DataBrowserItemUPP    userUPP)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/* Creation/Configuration */
/*
 *  CreateDataBrowserControl()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateDataBrowserControl(
  WindowRef              window,
  const Rect *           boundsRect,
  DataBrowserViewStyle   style,
  ControlRef *           outControl)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserViewStyle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserViewStyle(
  ControlRef              browser,
  DataBrowserViewStyle *  style)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserViewStyle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserViewStyle(
  ControlRef             browser,
  DataBrowserViewStyle   style)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  Summary:
 *    Data Browser attributes
 *  
 *  Discussion:
 *    For use with DataBrowserChangeAttributes and
 *    DataBrowserGetAttributes. Available in Mac OS X 10.4 and later.
 */
enum {

  /*
   * A constant with value zero; the lack of any attributes.
   */
  kDataBrowserAttributeNone     = 0,

  /*
   * In Column View, this Data Browser is allowed to resize the owning
   * window whenever necessary. This includes, but is not necessarily
   * limited to, situations where column resize operations need more
   * visible space in the window. If you turn this attribute on, your
   * window must tolerate being resized behind your app's back. If your
   * window needs to react to bounds changes, use a
   * kEventWindowBoundsChanged event handler. If you need to constrain
   * your window's minimum and maximum bounds, use
   * kEventWindowGetMinimum/MaximumSize handlers, the
   * SetWindowResizeLimits API, or something similar.
   */
  kDataBrowserAttributeColumnViewResizeWindow = (1 << 0),

  /*
   * In List View, this Data Browser should draw alternating row
   * background colors.
   */
  kDataBrowserAttributeListViewAlternatingRowColors = (1 << 1),

  /*
   * In List View, this Data Browser should draw a vertical line
   * between the columns.
   */
  kDataBrowserAttributeListViewDrawColumnDividers = (1 << 2)
};

/*
 *  DataBrowserChangeAttributes()
 *  
 *  Summary:
 *    Set the attributes for the given Data Browser.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inDataBrowser:
 *      The Data Browser whose attributes to change.
 *    
 *    inAttributesToSet:
 *      The attributes to set.
 *    
 *    inAttributesToClear:
 *      The attributes to clear.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DataBrowserChangeAttributes(
  ControlRef   inDataBrowser,
  OptionBits   inAttributesToSet,
  OptionBits   inAttributesToClear)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  DataBrowserGetAttributes()
 *  
 *  Summary:
 *    Returns the attributes of a given Data Browser.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inDataBrowser:
 *      The Data Browser whose attributes to query.
 *    
 *    outAttributes:
 *      On exit, will contain the attributes of the Data Browser. This
 *      parameter cannot be NULL.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DataBrowserGetAttributes(
  ControlRef    inDataBrowser,
  OptionBits *  outAttributes)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;




/*
 *  Summary:
 *    DataBrowserMetric values
 *  
 *  Discussion:
 *    For use with DataBrowserSetMetric.
 */
enum {

  /*
   * The content (icon, text, etc.) within a cell is drawn a certain
   * amount in from the left & right edges of the cell. This metric
   * governs the amount of inset.
   */
  kDataBrowserMetricCellContentInset = 1,

  /*
   * This metric controls the space between the icon and text within a
   * column of type kDataBrowserIconAndTextType.
   */
  kDataBrowserMetricIconAndTextGap = 2,

  /*
   * In List View only, this metric is similar to
   * kDataBrowserMetricCellContentInset, but it only affects the
   * disclosure column and it only affects the side of the cell that
   * displays the disclosure triangle. In other words, this metric is
   * used instead of (not in addition to)
   * DataBrowserMetricCellContentInset for one side of the disclosure
   * column.
   */
  kDataBrowserMetricDisclosureColumnEdgeInset = 3,

  /*
   * In List View only, this metric controls the amount of space
   * between the disclosure triangle and the cell's content.
   */
  kDataBrowserMetricDisclosureTriangleAndContentGap = 4,

  /*
   * In List View only, this metric controls the amount of space in the
   * disclosure column for each level of indentation in progressively
   * deeper hierarchies of disclosed items.
   */
  kDataBrowserMetricDisclosureColumnPerDepthGap = 5,
  kDataBrowserMetricLast        = kDataBrowserMetricDisclosureColumnPerDepthGap
};


typedef UInt32                          DataBrowserMetric;
/*
 *  DataBrowserSetMetric()
 *  
 *  Summary:
 *    Sets a value for a specified Data Browser metric.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inDataBrowser:
 *      The Data Browser instance whose metric is being changed.
 *    
 *    inMetric:
 *      The DataBrowserMetric whose value is being changed.
 *    
 *    inUseDefaultValue:
 *      A Boolean indicating whether you want the Data Browser instance
 *      to revert to the default value for the metric. If you pass
 *      true, inValue will be ignored and a suitable default value will
 *      be used. If you pass false, inValue will be used as the value
 *      of the metric.
 *    
 *    inValue:
 *      When you pass false for inUseDefaultValue, this parameter is
 *      the value to use for the metric.
 *  
 *  Result:
 *    An operating system status code. If the incoming ControlRef isn't
 *    a Data Browser instance, or if the incoming metric isn't known,
 *    this function will return paramErr.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DataBrowserSetMetric(
  ControlRef          inDataBrowser,
  DataBrowserMetric   inMetric,
  Boolean             inUseDefaultValue,
  float               inValue)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  DataBrowserGetMetric()
 *  
 *  Summary:
 *    Gets the value for a specified Data Browser metric.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inDataBrowser:
 *      The Data Browser instance whose metric value to get.
 *    
 *    inMetric:
 *      The DataBrowserMetric value to get.
 *    
 *    outUsingDefaultValue:
 *      On exit, this is a Boolean indicating whether the metric's
 *      value is determined by Data Browser's default values. You may
 *      pass NULL if you don't need this information.
 *    
 *    outValue:
 *      On exit, this is the value of the metric.
 *  
 *  Result:
 *    An operating system status code. If the incoming ControlRef isn't
 *    a Data Browser instance, or if the incoming metric isn't known,
 *    this function will return paramErr.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DataBrowserGetMetric(
  ControlRef          inDataBrowser,
  DataBrowserMetric   inMetric,
  Boolean *           outUsingDefaultValue,       /* can be NULL */
  float *             outValue)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/* Item Manipulation */
/* Passing NULL for "items" argument to RemoveDataBrowserItems and */
/* UpdateDataBrowserItems refers to all items in the specified container. */
/* Passing NULL for "items" argument to AddDataBrowserItems means */
/* "generate IDs starting from 1." */
/*
 *  AddDataBrowserItems()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
AddDataBrowserItems(
  ControlRef                 browser,
  DataBrowserItemID          container,
  UInt32                     numItems,
  const DataBrowserItemID *  items,                 /* can be NULL */
  DataBrowserPropertyID      preSortProperty)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RemoveDataBrowserItems()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RemoveDataBrowserItems(
  ControlRef                 browser,
  DataBrowserItemID          container,
  UInt32                     numItems,
  const DataBrowserItemID *  items,                 /* can be NULL */
  DataBrowserPropertyID      preSortProperty)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UpdateDataBrowserItems()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
UpdateDataBrowserItems(
  ControlRef                 browser,
  DataBrowserItemID          container,
  UInt32                     numItems,
  const DataBrowserItemID *  items,                 /* can be NULL */
  DataBrowserPropertyID      preSortProperty,
  DataBrowserPropertyID      propertyID)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Edit Menu Enabling and Handling */
/*
 *  EnableDataBrowserEditCommand()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
EnableDataBrowserEditCommand(
  ControlRef               browser,
  DataBrowserEditCommand   command)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ExecuteDataBrowserEditCommand()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ExecuteDataBrowserEditCommand(
  ControlRef               browser,
  DataBrowserEditCommand   command)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserSelectionAnchor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserSelectionAnchor(
  ControlRef           browser,
  DataBrowserItemID *  first,
  DataBrowserItemID *  last)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MoveDataBrowserSelectionAnchor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
MoveDataBrowserSelectionAnchor(
  ControlRef                            browser,
  DataBrowserSelectionAnchorDirection   direction,
  Boolean                               extendSelection)      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Container Manipulation */
/*
 *  OpenDataBrowserContainer()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
OpenDataBrowserContainer(
  ControlRef          browser,
  DataBrowserItemID   container)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CloseDataBrowserContainer()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CloseDataBrowserContainer(
  ControlRef          browser,
  DataBrowserItemID   container)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SortDataBrowserContainer()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SortDataBrowserContainer(
  ControlRef          browser,
  DataBrowserItemID   container,
  Boolean             sortChildren)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Aggregate Item Access and Iteration */
/*
 *  GetDataBrowserItems()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItems(
  ControlRef             browser,
  DataBrowserItemID      container,
  Boolean                recurse,
  DataBrowserItemState   state,
  Handle                 items)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemCount()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemCount(
  ControlRef             browser,
  DataBrowserItemID      container,
  Boolean                recurse,
  DataBrowserItemState   state,
  UInt32 *               numItems)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ForEachDataBrowserItem()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ForEachDataBrowserItem(
  ControlRef             browser,
  DataBrowserItemID      container,
  Boolean                recurse,
  DataBrowserItemState   state,
  DataBrowserItemUPP     callback,
  void *                 clientData)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Individual Item Access and Display */
/*
 *  IsDataBrowserItemSelected()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsDataBrowserItemSelected(
  ControlRef          browser,
  DataBrowserItemID   item)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemState()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemState(
  ControlRef              browser,
  DataBrowserItemID       item,
  DataBrowserItemState *  state)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RevealDataBrowserItem()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RevealDataBrowserItem(
  ControlRef                 browser,
  DataBrowserItemID          item,
  DataBrowserPropertyID      propertyID,
  DataBrowserRevealOptions   options)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Selection Set Manipulation */
/*
 *  SetDataBrowserSelectedItems()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserSelectedItems(
  ControlRef                 browser,
  UInt32                     numItems,
  const DataBrowserItemID *  items,
  DataBrowserSetOption       operation)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* DataBrowser Attribute Manipulation */
/* The user customizable portion of the current view style settings */
/*
 *  SetDataBrowserUserState()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserUserState(
  ControlRef        browser,
  CFDictionaryRef   stateInfo)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserUserState()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserUserState(
  ControlRef         browser,
  CFDictionaryRef *  stateInfo)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* All items are active/enabled or not */
/*
 *  SetDataBrowserActiveItems()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserActiveItems(
  ControlRef   browser,
  Boolean      active)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserActiveItems()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserActiveItems(
  ControlRef   browser,
  Boolean *    active)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Inset the scrollbars within the DataBrowser bounds */
/*
 *  SetDataBrowserScrollBarInset()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserScrollBarInset(
  ControlRef   browser,
  Rect *       insetRect)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserScrollBarInset()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserScrollBarInset(
  ControlRef   browser,
  Rect *       insetRect)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* The "user focused" item */
/* For the ListView, this means the root container */
/* For the ColumnView, this means the rightmost container column */
/*
 *  SetDataBrowserTarget()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserTarget(
  ControlRef          browser,
  DataBrowserItemID   target)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserTarget()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserTarget(
  ControlRef           browser,
  DataBrowserItemID *  target)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Current sort ordering */
/* ListView tracks this per-column */
/*
 *  SetDataBrowserSortOrder()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserSortOrder(
  ControlRef             browser,
  DataBrowserSortOrder   order)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserSortOrder()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserSortOrder(
  ControlRef              browser,
  DataBrowserSortOrder *  order)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Scrollbar values */
/*
 *  SetDataBrowserScrollPosition()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserScrollPosition(
  ControlRef   browser,
  UInt32       top,
  UInt32       left)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserScrollPosition()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserScrollPosition(
  ControlRef   browser,
  UInt32 *     top,
  UInt32 *     left)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Show/Hide each scrollbar */
/*
 *  SetDataBrowserHasScrollBars()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserHasScrollBars(
  ControlRef   browser,
  Boolean      horiz,
  Boolean      vert)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserHasScrollBars()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserHasScrollBars(
  ControlRef   browser,
  Boolean *    horiz,
  Boolean *    vert)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Property passed to sort callback (ListView sort column) */
/*
 *  SetDataBrowserSortProperty()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserSortProperty(
  ControlRef              browser,
  DataBrowserPropertyID   property)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserSortProperty()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserSortProperty(
  ControlRef               browser,
  DataBrowserPropertyID *  property)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Modify selection behavior */
/*
 *  SetDataBrowserSelectionFlags()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserSelectionFlags(
  ControlRef                  browser,
  DataBrowserSelectionFlags   selectionFlags)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserSelectionFlags()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserSelectionFlags(
  ControlRef                   browser,
  DataBrowserSelectionFlags *  selectionFlags)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Dynamically modify property appearance/behavior */
/*
 *  SetDataBrowserPropertyFlags()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserPropertyFlags(
  ControlRef                 browser,
  DataBrowserPropertyID      property,
  DataBrowserPropertyFlags   flags)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserPropertyFlags()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserPropertyFlags(
  ControlRef                  browser,
  DataBrowserPropertyID       property,
  DataBrowserPropertyFlags *  flags)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Text of current in-place edit session */
/*
 *  SetDataBrowserEditText()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserEditText(
  ControlRef    browser,
  CFStringRef   text)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CopyDataBrowserEditText()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CopyDataBrowserEditText(
  ControlRef     browser,
  CFStringRef *  text)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserEditText()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserEditText(
  ControlRef           browser,
  CFMutableStringRef   text)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Item/property currently being edited */
/*
 *  SetDataBrowserEditItem()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserEditItem(
  ControlRef              browser,
  DataBrowserItemID       item,
  DataBrowserPropertyID   property)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserEditItem()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserEditItem(
  ControlRef               browser,
  DataBrowserItemID *      item,
  DataBrowserPropertyID *  property)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Get the current bounds of a visual part of an item's property */
/*
 *  GetDataBrowserItemPartBounds()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemPartBounds(
  ControlRef                browser,
  DataBrowserItemID         item,
  DataBrowserPropertyID     property,
  DataBrowserPropertyPart   part,
  Rect *                    bounds)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* DataBrowser ItemData Accessors (used within DataBrowserItemData callback) */
typedef void *                          DataBrowserItemDataRef;
/*
 *  SetDataBrowserItemDataIcon()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataIcon(
  DataBrowserItemDataRef   itemData,
  IconRef                  theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataIcon()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataIcon(
  DataBrowserItemDataRef   itemData,
  IconRef *                theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserItemDataText()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataText(
  DataBrowserItemDataRef   itemData,
  CFStringRef              theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataText()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataText(
  DataBrowserItemDataRef   itemData,
  CFStringRef *            theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  SetDataBrowserItemDataValue()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataValue(
  DataBrowserItemDataRef   itemData,
  SInt32                   theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataValue()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataValue(
  DataBrowserItemDataRef   itemData,
  SInt32 *                 theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserItemDataMinimum()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataMinimum(
  DataBrowserItemDataRef   itemData,
  SInt32                   theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataMinimum()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataMinimum(
  DataBrowserItemDataRef   itemData,
  SInt32 *                 theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserItemDataMaximum()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataMaximum(
  DataBrowserItemDataRef   itemData,
  SInt32                   theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataMaximum()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataMaximum(
  DataBrowserItemDataRef   itemData,
  SInt32 *                 theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserItemDataBooleanValue()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataBooleanValue(
  DataBrowserItemDataRef   itemData,
  Boolean                  theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataBooleanValue()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataBooleanValue(
  DataBrowserItemDataRef   itemData,
  Boolean *                theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserItemDataMenuRef()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataMenuRef(
  DataBrowserItemDataRef   itemData,
  MenuRef                  theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataMenuRef()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataMenuRef(
  DataBrowserItemDataRef   itemData,
  MenuRef *                theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserItemDataRGBColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataRGBColor(
  DataBrowserItemDataRef   itemData,
  const RGBColor *         theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataRGBColor()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataRGBColor(
  DataBrowserItemDataRef   itemData,
  RGBColor *               theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  SetDataBrowserItemDataDrawState()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataDrawState(
  DataBrowserItemDataRef   itemData,
  ThemeDrawState           theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataDrawState()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataDrawState(
  DataBrowserItemDataRef   itemData,
  ThemeDrawState *         theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserItemDataButtonValue()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataButtonValue(
  DataBrowserItemDataRef   itemData,
  ThemeButtonValue         theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataButtonValue()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataButtonValue(
  DataBrowserItemDataRef   itemData,
  ThemeButtonValue *       theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserItemDataIconTransform()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataIconTransform(
  DataBrowserItemDataRef   itemData,
  IconTransformType        theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataIconTransform()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataIconTransform(
  DataBrowserItemDataRef   itemData,
  IconTransformType *      theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  SetDataBrowserItemDataDateTime()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataDateTime(
  DataBrowserItemDataRef   itemData,
  long                     theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataDateTime()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataDateTime(
  DataBrowserItemDataRef   itemData,
  long *                   theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserItemDataLongDateTime()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataLongDateTime(
  DataBrowserItemDataRef   itemData,
  const LongDateTime *     theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataLongDateTime()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataLongDateTime(
  DataBrowserItemDataRef   itemData,
  LongDateTime *           theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  SetDataBrowserItemDataItemID()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserItemDataItemID(
  DataBrowserItemDataRef   itemData,
  DataBrowserItemID        theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataItemID()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataItemID(
  DataBrowserItemDataRef   itemData,
  DataBrowserItemID *      theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserItemDataProperty()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserItemDataProperty(
  DataBrowserItemDataRef   itemData,
  DataBrowserPropertyID *  theData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Standard DataBrowser Callbacks */

/* Basic Item Management & Manipulation */
typedef CALLBACK_API( OSStatus , DataBrowserItemDataProcPtr )(ControlRef browser, DataBrowserItemID item, DataBrowserPropertyID property, DataBrowserItemDataRef itemData, Boolean setValue);
typedef STACK_UPP_TYPE(DataBrowserItemDataProcPtr)              DataBrowserItemDataUPP;

/* Item Comparison */
typedef CALLBACK_API( Boolean , DataBrowserItemCompareProcPtr )(ControlRef browser, DataBrowserItemID itemOne, DataBrowserItemID itemTwo, DataBrowserPropertyID sortProperty);
typedef STACK_UPP_TYPE(DataBrowserItemCompareProcPtr)           DataBrowserItemCompareUPP;

/* ItemEvent Notification */
/*  A Very Important Note about DataBrowserItemNotificationProcPtr:                                     */
/*                                                                                                      */
/*  Under all currently shipping versions of CarbonLib (eg. up through 1.3), your callback is called    */
/*  just as the prototype appears in this header. It should only be expecting three parameters because  */
/*  DataBrowser will only pass three parameters.                                                        */
/*                                                                                                      */
/*  Under Mac OS X, your callback is called with an additional parameter. If you wish to interpret      */
/*  the additional parameter, your callback should have the same prototype as the                       */
/*  DataBrowserItemNotificationWithItemProcPtr (below). You may freely take a callback with this        */
/*  prototype and pass it to NewDataBrowserItemNotificationUPP in order to generate a                   */
/*  DataBrowserItemNotificationUPP that you can use just like any other DataBrowserItemNotificationUPP. */
/*                                                                                                      */
/*  If you use this technique under CarbonLib, you will *not* receive valid data in the fourth          */
/*  parameter, and any attempt to use the invalid data will probably result in a crash.                 */
typedef CALLBACK_API( void , DataBrowserItemNotificationWithItemProcPtr )(ControlRef browser, DataBrowserItemID item, DataBrowserItemNotification message, DataBrowserItemDataRef itemData);
typedef CALLBACK_API( void , DataBrowserItemNotificationProcPtr )(ControlRef browser, DataBrowserItemID item, DataBrowserItemNotification message);
typedef STACK_UPP_TYPE(DataBrowserItemNotificationWithItemProcPtr)  DataBrowserItemNotificationWithItemUPP;
typedef STACK_UPP_TYPE(DataBrowserItemNotificationProcPtr)      DataBrowserItemNotificationUPP;


/* Drag & Drop Processing */
typedef CALLBACK_API( Boolean , DataBrowserAddDragItemProcPtr )(ControlRef browser, DragReference theDrag, DataBrowserItemID item, ItemReference *itemRef);
typedef CALLBACK_API( Boolean , DataBrowserAcceptDragProcPtr )(ControlRef browser, DragReference theDrag, DataBrowserItemID item);
typedef CALLBACK_API( Boolean , DataBrowserReceiveDragProcPtr )(ControlRef browser, DragReference theDrag, DataBrowserItemID item);
typedef CALLBACK_API( void , DataBrowserPostProcessDragProcPtr )(ControlRef browser, DragReference theDrag, OSStatus trackDragResult);
typedef STACK_UPP_TYPE(DataBrowserAddDragItemProcPtr)           DataBrowserAddDragItemUPP;
typedef STACK_UPP_TYPE(DataBrowserAcceptDragProcPtr)            DataBrowserAcceptDragUPP;
typedef STACK_UPP_TYPE(DataBrowserReceiveDragProcPtr)           DataBrowserReceiveDragUPP;
typedef STACK_UPP_TYPE(DataBrowserPostProcessDragProcPtr)       DataBrowserPostProcessDragUPP;

/* Contextual Menu Support */
typedef CALLBACK_API( void , DataBrowserGetContextualMenuProcPtr )(ControlRef browser, MenuRef *menu, UInt32 *helpType, CFStringRef *helpItemString, AEDesc *selection);
typedef CALLBACK_API( void , DataBrowserSelectContextualMenuProcPtr )(ControlRef browser, MenuRef menu, UInt32 selectionType, SInt16 menuID, MenuItemIndex menuItem);
typedef STACK_UPP_TYPE(DataBrowserGetContextualMenuProcPtr)     DataBrowserGetContextualMenuUPP;
typedef STACK_UPP_TYPE(DataBrowserSelectContextualMenuProcPtr)  DataBrowserSelectContextualMenuUPP;

/* Help Manager Support */
typedef CALLBACK_API( void , DataBrowserItemHelpContentProcPtr )(ControlRef browser, DataBrowserItemID item, DataBrowserPropertyID property, HMContentRequest inRequest, HMContentProvidedType *outContentProvided, HMHelpContentPtr ioHelpContent);
typedef STACK_UPP_TYPE(DataBrowserItemHelpContentProcPtr)       DataBrowserItemHelpContentUPP;
/*
 *  NewDataBrowserItemDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserItemDataUPP
NewDataBrowserItemDataUPP(DataBrowserItemDataProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDataBrowserItemCompareUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserItemCompareUPP
NewDataBrowserItemCompareUPP(DataBrowserItemCompareProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDataBrowserItemNotificationWithItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserItemNotificationWithItemUPP
NewDataBrowserItemNotificationWithItemUPP(DataBrowserItemNotificationWithItemProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  NewDataBrowserItemNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserItemNotificationUPP
NewDataBrowserItemNotificationUPP(DataBrowserItemNotificationProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDataBrowserAddDragItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserAddDragItemUPP
NewDataBrowserAddDragItemUPP(DataBrowserAddDragItemProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDataBrowserAcceptDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserAcceptDragUPP
NewDataBrowserAcceptDragUPP(DataBrowserAcceptDragProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDataBrowserReceiveDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserReceiveDragUPP
NewDataBrowserReceiveDragUPP(DataBrowserReceiveDragProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDataBrowserPostProcessDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserPostProcessDragUPP
NewDataBrowserPostProcessDragUPP(DataBrowserPostProcessDragProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDataBrowserGetContextualMenuUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserGetContextualMenuUPP
NewDataBrowserGetContextualMenuUPP(DataBrowserGetContextualMenuProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDataBrowserSelectContextualMenuUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserSelectContextualMenuUPP
NewDataBrowserSelectContextualMenuUPP(DataBrowserSelectContextualMenuProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDataBrowserItemHelpContentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserItemHelpContentUPP
NewDataBrowserItemHelpContentUPP(DataBrowserItemHelpContentProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDataBrowserItemDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserItemDataUPP(DataBrowserItemDataUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDataBrowserItemCompareUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserItemCompareUPP(DataBrowserItemCompareUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDataBrowserItemNotificationWithItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserItemNotificationWithItemUPP(DataBrowserItemNotificationWithItemUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  DisposeDataBrowserItemNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserItemNotificationUPP(DataBrowserItemNotificationUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDataBrowserAddDragItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserAddDragItemUPP(DataBrowserAddDragItemUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDataBrowserAcceptDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserAcceptDragUPP(DataBrowserAcceptDragUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDataBrowserReceiveDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserReceiveDragUPP(DataBrowserReceiveDragUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDataBrowserPostProcessDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserPostProcessDragUPP(DataBrowserPostProcessDragUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDataBrowserGetContextualMenuUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserGetContextualMenuUPP(DataBrowserGetContextualMenuUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDataBrowserSelectContextualMenuUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserSelectContextualMenuUPP(DataBrowserSelectContextualMenuUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDataBrowserItemHelpContentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserItemHelpContentUPP(DataBrowserItemHelpContentUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDataBrowserItemDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus
InvokeDataBrowserItemDataUPP(
  ControlRef              browser,
  DataBrowserItemID       item,
  DataBrowserPropertyID   property,
  DataBrowserItemDataRef  itemData,
  Boolean                 setValue,
  DataBrowserItemDataUPP  userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDataBrowserItemCompareUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean
InvokeDataBrowserItemCompareUPP(
  ControlRef                 browser,
  DataBrowserItemID          itemOne,
  DataBrowserItemID          itemTwo,
  DataBrowserPropertyID      sortProperty,
  DataBrowserItemCompareUPP  userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDataBrowserItemNotificationWithItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokeDataBrowserItemNotificationWithItemUPP(
  ControlRef                              browser,
  DataBrowserItemID                       item,
  DataBrowserItemNotification             message,
  DataBrowserItemDataRef                  itemData,
  DataBrowserItemNotificationWithItemUPP  userUPP)            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  InvokeDataBrowserItemNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokeDataBrowserItemNotificationUPP(
  ControlRef                      browser,
  DataBrowserItemID               item,
  DataBrowserItemNotification     message,
  DataBrowserItemNotificationUPP  userUPP)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDataBrowserAddDragItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean
InvokeDataBrowserAddDragItemUPP(
  ControlRef                 browser,
  DragReference              theDrag,
  DataBrowserItemID          item,
  ItemReference *            itemRef,
  DataBrowserAddDragItemUPP  userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDataBrowserAcceptDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean
InvokeDataBrowserAcceptDragUPP(
  ControlRef                browser,
  DragReference             theDrag,
  DataBrowserItemID         item,
  DataBrowserAcceptDragUPP  userUPP)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDataBrowserReceiveDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean
InvokeDataBrowserReceiveDragUPP(
  ControlRef                 browser,
  DragReference              theDrag,
  DataBrowserItemID          item,
  DataBrowserReceiveDragUPP  userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDataBrowserPostProcessDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokeDataBrowserPostProcessDragUPP(
  ControlRef                     browser,
  DragReference                  theDrag,
  OSStatus                       trackDragResult,
  DataBrowserPostProcessDragUPP  userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDataBrowserGetContextualMenuUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokeDataBrowserGetContextualMenuUPP(
  ControlRef                       browser,
  MenuRef *                        menu,
  UInt32 *                         helpType,
  CFStringRef *                    helpItemString,
  AEDesc *                         selection,
  DataBrowserGetContextualMenuUPP  userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDataBrowserSelectContextualMenuUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokeDataBrowserSelectContextualMenuUPP(
  ControlRef                          browser,
  MenuRef                             menu,
  UInt32                              selectionType,
  SInt16                              menuID,
  MenuItemIndex                       menuItem,
  DataBrowserSelectContextualMenuUPP  userUPP)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDataBrowserItemHelpContentUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokeDataBrowserItemHelpContentUPP(
  ControlRef                     browser,
  DataBrowserItemID              item,
  DataBrowserPropertyID          property,
  HMContentRequest               inRequest,
  HMContentProvidedType *        outContentProvided,
  HMHelpContentPtr               ioHelpContent,
  DataBrowserItemHelpContentUPP  userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/* Standard Callback (vtable) Structure */
enum {
  kDataBrowserLatestCallbacks   = 0
};

struct DataBrowserCallbacks {
  UInt32              version;                /* Use kDataBrowserLatestCallbacks */

  union {
    struct {
      DataBrowserItemDataUPP  itemDataCallback;
      DataBrowserItemCompareUPP  itemCompareCallback;
      DataBrowserItemNotificationUPP  itemNotificationCallback;

      DataBrowserAddDragItemUPP  addDragItemCallback;
      DataBrowserAcceptDragUPP  acceptDragCallback;
      DataBrowserReceiveDragUPP  receiveDragCallback;
      DataBrowserPostProcessDragUPP  postProcessDragCallback;

      DataBrowserItemHelpContentUPP  itemHelpContentCallback;
      DataBrowserGetContextualMenuUPP  getContextualMenuCallback;
      DataBrowserSelectContextualMenuUPP  selectContextualMenuCallback;
    }                       v1;
  }                       u;
};
typedef struct DataBrowserCallbacks     DataBrowserCallbacks;
/*
 *  InitDataBrowserCallbacks()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
InitDataBrowserCallbacks(DataBrowserCallbacks * callbacks)    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Macro for initializing callback structure */
#define InitializeDataBrowserCallbacks(callbacks, vers) \
{ (callbacks)->version = (vers); InitDataBrowserCallbacks(callbacks); }

/*
 *  GetDataBrowserCallbacks()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserCallbacks(
  ControlRef              browser,
  DataBrowserCallbacks *  callbacks)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserCallbacks()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserCallbacks(
  ControlRef                    browser,
  const DataBrowserCallbacks *  callbacks)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Custom Format Callbacks (kDataBrowserCustomType display properties) */

typedef unsigned long                   DataBrowserDragFlags;
typedef SInt16 DataBrowserTrackingResult;
enum {
  kDataBrowserContentHit        = 1,
  kDataBrowserNothingHit        = 0,
  kDataBrowserStopTracking      = -1
};

typedef CALLBACK_API( void , DataBrowserDrawItemProcPtr )(ControlRef browser, DataBrowserItemID item, DataBrowserPropertyID property, DataBrowserItemState itemState, const Rect *theRect, SInt16 gdDepth, Boolean colorDevice);
typedef CALLBACK_API( Boolean , DataBrowserEditItemProcPtr )(ControlRef browser, DataBrowserItemID item, DataBrowserPropertyID property, CFStringRef theString, Rect *maxEditTextRect, Boolean *shrinkToFit);
typedef CALLBACK_API( Boolean , DataBrowserHitTestProcPtr )(ControlRef browser, DataBrowserItemID itemID, DataBrowserPropertyID property, const Rect *theRect, const Rect *mouseRect);
typedef CALLBACK_API( DataBrowserTrackingResult , DataBrowserTrackingProcPtr )(ControlRef browser, DataBrowserItemID itemID, DataBrowserPropertyID property, const Rect *theRect, Point startPt, EventModifiers modifiers);
typedef CALLBACK_API( void , DataBrowserItemDragRgnProcPtr )(ControlRef browser, DataBrowserItemID itemID, DataBrowserPropertyID property, const Rect *theRect, RgnHandle dragRgn);
typedef CALLBACK_API( DataBrowserDragFlags , DataBrowserItemAcceptDragProcPtr )(ControlRef browser, DataBrowserItemID itemID, DataBrowserPropertyID property, const Rect *theRect, DragReference theDrag);
typedef CALLBACK_API( Boolean , DataBrowserItemReceiveDragProcPtr )(ControlRef browser, DataBrowserItemID itemID, DataBrowserPropertyID property, DataBrowserDragFlags dragFlags, DragReference theDrag);
typedef STACK_UPP_TYPE(DataBrowserDrawItemProcPtr)              DataBrowserDrawItemUPP;
typedef STACK_UPP_TYPE(DataBrowserEditItemProcPtr)              DataBrowserEditItemUPP;
typedef STACK_UPP_TYPE(DataBrowserHitTestProcPtr)               DataBrowserHitTestUPP;
typedef STACK_UPP_TYPE(DataBrowserTrackingProcPtr)              DataBrowserTrackingUPP;
typedef STACK_UPP_TYPE(DataBrowserItemDragRgnProcPtr)           DataBrowserItemDragRgnUPP;
typedef STACK_UPP_TYPE(DataBrowserItemAcceptDragProcPtr)        DataBrowserItemAcceptDragUPP;
typedef STACK_UPP_TYPE(DataBrowserItemReceiveDragProcPtr)       DataBrowserItemReceiveDragUPP;
/*
 *  NewDataBrowserDrawItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserDrawItemUPP
NewDataBrowserDrawItemUPP(DataBrowserDrawItemProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  NewDataBrowserEditItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserEditItemUPP
NewDataBrowserEditItemUPP(DataBrowserEditItemProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  NewDataBrowserHitTestUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserHitTestUPP
NewDataBrowserHitTestUPP(DataBrowserHitTestProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  NewDataBrowserTrackingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserTrackingUPP
NewDataBrowserTrackingUPP(DataBrowserTrackingProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  NewDataBrowserItemDragRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserItemDragRgnUPP
NewDataBrowserItemDragRgnUPP(DataBrowserItemDragRgnProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  NewDataBrowserItemAcceptDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserItemAcceptDragUPP
NewDataBrowserItemAcceptDragUPP(DataBrowserItemAcceptDragProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  NewDataBrowserItemReceiveDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserItemReceiveDragUPP
NewDataBrowserItemReceiveDragUPP(DataBrowserItemReceiveDragProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  DisposeDataBrowserDrawItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserDrawItemUPP(DataBrowserDrawItemUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  DisposeDataBrowserEditItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserEditItemUPP(DataBrowserEditItemUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  DisposeDataBrowserHitTestUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserHitTestUPP(DataBrowserHitTestUPP userUPP)   AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  DisposeDataBrowserTrackingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserTrackingUPP(DataBrowserTrackingUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  DisposeDataBrowserItemDragRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserItemDragRgnUPP(DataBrowserItemDragRgnUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  DisposeDataBrowserItemAcceptDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserItemAcceptDragUPP(DataBrowserItemAcceptDragUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  DisposeDataBrowserItemReceiveDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeDataBrowserItemReceiveDragUPP(DataBrowserItemReceiveDragUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  InvokeDataBrowserDrawItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokeDataBrowserDrawItemUPP(
  ControlRef              browser,
  DataBrowserItemID       item,
  DataBrowserPropertyID   property,
  DataBrowserItemState    itemState,
  const Rect *            theRect,
  SInt16                  gdDepth,
  Boolean                 colorDevice,
  DataBrowserDrawItemUPP  userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  InvokeDataBrowserEditItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean
InvokeDataBrowserEditItemUPP(
  ControlRef              browser,
  DataBrowserItemID       item,
  DataBrowserPropertyID   property,
  CFStringRef             theString,
  Rect *                  maxEditTextRect,
  Boolean *               shrinkToFit,
  DataBrowserEditItemUPP  userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  InvokeDataBrowserHitTestUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean
InvokeDataBrowserHitTestUPP(
  ControlRef             browser,
  DataBrowserItemID      itemID,
  DataBrowserPropertyID  property,
  const Rect *           theRect,
  const Rect *           mouseRect,
  DataBrowserHitTestUPP  userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  InvokeDataBrowserTrackingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserTrackingResult
InvokeDataBrowserTrackingUPP(
  ControlRef              browser,
  DataBrowserItemID       itemID,
  DataBrowserPropertyID   property,
  const Rect *            theRect,
  Point                   startPt,
  EventModifiers          modifiers,
  DataBrowserTrackingUPP  userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  InvokeDataBrowserItemDragRgnUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void
InvokeDataBrowserItemDragRgnUPP(
  ControlRef                 browser,
  DataBrowserItemID          itemID,
  DataBrowserPropertyID      property,
  const Rect *               theRect,
  RgnHandle                  dragRgn,
  DataBrowserItemDragRgnUPP  userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  InvokeDataBrowserItemAcceptDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern DataBrowserDragFlags
InvokeDataBrowserItemAcceptDragUPP(
  ControlRef                    browser,
  DataBrowserItemID             itemID,
  DataBrowserPropertyID         property,
  const Rect *                  theRect,
  DragReference                 theDrag,
  DataBrowserItemAcceptDragUPP  userUPP)                      AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  InvokeDataBrowserItemReceiveDragUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean
InvokeDataBrowserItemReceiveDragUPP(
  ControlRef                     browser,
  DataBrowserItemID              itemID,
  DataBrowserPropertyID          property,
  DataBrowserDragFlags           dragFlags,
  DragReference                  theDrag,
  DataBrowserItemReceiveDragUPP  userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/* Custom Callback (vtable) Structure */
enum {
  kDataBrowserLatestCustomCallbacks = 0
};

struct DataBrowserCustomCallbacks {

  UInt32              version;                /* Use kDataBrowserLatestCustomCallbacks */

  union {
    struct {
      DataBrowserDrawItemUPP  drawItemCallback;
      DataBrowserEditItemUPP  editTextCallback;
      DataBrowserHitTestUPP  hitTestCallback;
      DataBrowserTrackingUPP  trackingCallback;

      DataBrowserItemDragRgnUPP  dragRegionCallback;
      DataBrowserItemAcceptDragUPP  acceptDragCallback;
      DataBrowserItemReceiveDragUPP  receiveDragCallback;
    }                       v1;
  }                       u;
};
typedef struct DataBrowserCustomCallbacks DataBrowserCustomCallbacks;
/*
 *  InitDataBrowserCustomCallbacks()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
InitDataBrowserCustomCallbacks(DataBrowserCustomCallbacks * callbacks) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Macro for initializing custom callback structure */
#define InitializeDataBrowserCustomCallbacks(callbacks, vers) \
{ (callbacks)->version = (vers); InitDataBrowserCustomCallbacks(callbacks); }

/*
 *  GetDataBrowserCustomCallbacks()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserCustomCallbacks(
  ControlRef                    browser,
  DataBrowserCustomCallbacks *  callbacks)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserCustomCallbacks()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserCustomCallbacks(
  ControlRef                          browser,
  const DataBrowserCustomCallbacks *  callbacks)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





/* TableView Formatting */
typedef UInt32 DataBrowserTableViewHiliteStyle;
enum {
  kDataBrowserTableViewMinimalHilite = 0,
  kDataBrowserTableViewFillHilite = 1
};

typedef UInt32 DataBrowserTableViewPropertyFlags;
enum {
                                        /* kDataBrowserTableView DataBrowserPropertyFlags */
  kDataBrowserTableViewSelectionColumn = 1 << kDataBrowserViewSpecificFlagsOffset
};

/* The row and column indicies are zero-based */

typedef UInt32                          DataBrowserTableViewRowIndex;
typedef UInt32                          DataBrowserTableViewColumnIndex;
typedef DataBrowserPropertyID           DataBrowserTableViewColumnID;
typedef DataBrowserPropertyDesc         DataBrowserTableViewColumnDesc;

/* TableView API */
/* Use when setting column position */
enum {
  kDataBrowserTableViewLastColumn = -1
};

/*
 *  RemoveDataBrowserTableViewColumn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RemoveDataBrowserTableViewColumn(
  ControlRef                     browser,
  DataBrowserTableViewColumnID   column)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserTableViewColumnCount()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserTableViewColumnCount(
  ControlRef   browser,
  UInt32 *     numColumns)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  SetDataBrowserTableViewHiliteStyle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserTableViewHiliteStyle(
  ControlRef                        browser,
  DataBrowserTableViewHiliteStyle   hiliteStyle)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserTableViewHiliteStyle()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserTableViewHiliteStyle(
  ControlRef                         browser,
  DataBrowserTableViewHiliteStyle *  hiliteStyle)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  SetDataBrowserTableViewRowHeight()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserTableViewRowHeight(
  ControlRef   browser,
  UInt16       height)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserTableViewRowHeight()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserTableViewRowHeight(
  ControlRef   browser,
  UInt16 *     height)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserTableViewColumnWidth()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserTableViewColumnWidth(
  ControlRef   browser,
  UInt16       width)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserTableViewColumnWidth()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserTableViewColumnWidth(
  ControlRef   browser,
  UInt16 *     width)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserTableViewItemRowHeight()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserTableViewItemRowHeight(
  ControlRef          browser,
  DataBrowserItemID   item,
  UInt16              height)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserTableViewItemRowHeight()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserTableViewItemRowHeight(
  ControlRef          browser,
  DataBrowserItemID   item,
  UInt16 *            height)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserTableViewNamedColumnWidth()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserTableViewNamedColumnWidth(
  ControlRef                     browser,
  DataBrowserTableViewColumnID   column,
  UInt16                         width)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserTableViewNamedColumnWidth()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserTableViewNamedColumnWidth(
  ControlRef                     browser,
  DataBrowserTableViewColumnID   column,
  UInt16 *                       width)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserTableViewGeometry()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserTableViewGeometry(
  ControlRef   browser,
  Boolean      variableWidthColumns,
  Boolean      variableHeightRows)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserTableViewGeometry()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserTableViewGeometry(
  ControlRef   browser,
  Boolean *    variableWidthColumns,
  Boolean *    variableHeightRows)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  GetDataBrowserTableViewItemID()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserTableViewItemID(
  ControlRef                     browser,
  DataBrowserTableViewRowIndex   row,
  DataBrowserItemID *            item)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserTableViewItemRow()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserTableViewItemRow(
  ControlRef                     browser,
  DataBrowserItemID              item,
  DataBrowserTableViewRowIndex   row)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserTableViewItemRow()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserTableViewItemRow(
  ControlRef                      browser,
  DataBrowserItemID               item,
  DataBrowserTableViewRowIndex *  row)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserTableViewColumnPosition()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserTableViewColumnPosition(
  ControlRef                        browser,
  DataBrowserTableViewColumnID      column,
  DataBrowserTableViewColumnIndex   position)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserTableViewColumnPosition()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserTableViewColumnPosition(
  ControlRef                         browser,
  DataBrowserTableViewColumnID       column,
  DataBrowserTableViewColumnIndex *  position)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserTableViewColumnProperty()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserTableViewColumnProperty(
  ControlRef                        browser,
  DataBrowserTableViewColumnIndex   column,
  DataBrowserTableViewColumnID *    property)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





/* kDataBrowserListView Formatting */

/*
 *  Discussion:
 *    DataBrowserPropertyFlags that are specific to kDataBrowserListView
 */
enum {
  kDataBrowserListViewSelectionColumn = kDataBrowserTableViewSelectionColumn,
  kDataBrowserListViewMovableColumn = 1 << (kDataBrowserViewSpecificFlagsOffset + 1),
  kDataBrowserListViewSortableColumn = 1 << (kDataBrowserViewSpecificFlagsOffset + 2),

  /*
   * kDataBrowserListViewTypeSelectColumn marks a column as
   * type-selectable. If one or more of your list view columns are
   * marked as type-selectable, Data Browser will do type-selection for
   * you automatically. Data Browser applies the typing to the first
   * column (in the system direction) with this property flag. This
   * flag only intended for use with columns of type
   * kDataBrowserTextType, kDataBrowserIconAndTextType, and
   * kDataBrowserDateTimeType; if you set it for a column of another
   * type, the type-selection behavior is undefined. Turning on this
   * flag also causes Data Browser to gather all keyboard input via a
   * carbon event handler instead of relying on calls to
   * HandleControlKey; therefore, you will never see these keyboard
   * events come out of WaitNextEvent. Only available on 10.3 and later.
   */
  kDataBrowserListViewTypeSelectColumn = 1 << (kDataBrowserViewSpecificFlagsOffset + 3),

  /*
   * Normally the text in a header button for a column of type
   * kDataBrowserIconAndTextType is aligned as though it has an icon
   * next to it even if no icon is specified for the header button; in
   * other words, space is reserved for an icon in the header button
   * even if no icon is displayed. However, this flag indicates that
   * space should not be reserved for an icon if no icon is provided
   * for the header button. This flag allows a client to justify the
   * left edge of the text in a header button to the left edge of the
   * icon in the cells beneath it. Available on 10.4 and later.
   */
  kDataBrowserListViewNoGapForIconInHeaderButton = 1 << (kDataBrowserViewSpecificFlagsOffset + 4),
  kDataBrowserListViewDefaultColumnFlags = kDataBrowserListViewMovableColumn + kDataBrowserListViewSortableColumn
};

typedef DataBrowserPropertyFlags        DataBrowserListViewPropertyFlags;
enum {
  kDataBrowserListViewLatestHeaderDesc = 0
};

struct DataBrowserListViewHeaderDesc {
  UInt32              version;                /* Use kDataBrowserListViewLatestHeaderDesc */

  UInt16              minimumWidth;
  UInt16              maximumWidth;

  SInt16              titleOffset;
  CFStringRef         titleString;
  DataBrowserSortOrder  initialOrder;
  ControlFontStyleRec  btnFontStyle;
  ControlButtonContentInfo  btnContentInfo;
};
typedef struct DataBrowserListViewHeaderDesc DataBrowserListViewHeaderDesc;
struct DataBrowserListViewColumnDesc {
  DataBrowserTableViewColumnDesc  propertyDesc;
  DataBrowserListViewHeaderDesc  headerBtnDesc;
};
typedef struct DataBrowserListViewColumnDesc DataBrowserListViewColumnDesc;
/* kDataBrowserListView API */
enum {
  kDataBrowserListViewAppendColumn = kDataBrowserTableViewLastColumn
};

/*
 *  AutoSizeDataBrowserListViewColumns()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
AutoSizeDataBrowserListViewColumns(ControlRef browser)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddDataBrowserListViewColumn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
AddDataBrowserListViewColumn(
  ControlRef                        browser,
  DataBrowserListViewColumnDesc *   columnDesc,
  DataBrowserTableViewColumnIndex   position)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserListViewHeaderDesc()
 *  
 *  Summary:
 *    Returns information about a specified column header in a list
 *    view.
 *  
 *  Discussion:
 *    Note that this API does not correctly use CoreFoundation naming
 *    conventions. Although the API name begins with "Get", implying
 *    that you do not need to release the CFStringRef and IconRef
 *    returned by this API, in fact you do actually need to release
 *    these objects.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    browser:
 *      The data browser for which you need header information.
 *    
 *    column:
 *      The column ID for which you need header information.
 *    
 *    desc:
 *      On exit, contains header information for the specified column.
 *      You must release the CFStringRef and IconRef contained in this
 *      structure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserListViewHeaderDesc(
  ControlRef                       browser,
  DataBrowserTableViewColumnID     column,
  DataBrowserListViewHeaderDesc *  desc)                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SetDataBrowserListViewHeaderDesc()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserListViewHeaderDesc(
  ControlRef                       browser,
  DataBrowserTableViewColumnID     column,
  DataBrowserListViewHeaderDesc *  desc)                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SetDataBrowserListViewHeaderBtnHeight()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserListViewHeaderBtnHeight(
  ControlRef   browser,
  UInt16       height)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserListViewHeaderBtnHeight()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserListViewHeaderBtnHeight(
  ControlRef   browser,
  UInt16 *     height)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserListViewUsePlainBackground()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserListViewUsePlainBackground(
  ControlRef   browser,
  Boolean      usePlainBackground)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserListViewUsePlainBackground()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserListViewUsePlainBackground(
  ControlRef   browser,
  Boolean *    usePlainBackground)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserListViewDisclosureColumn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserListViewDisclosureColumn(
  ControlRef                     browser,
  DataBrowserTableViewColumnID   column,
  Boolean                        expandableRows)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserListViewDisclosureColumn()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserListViewDisclosureColumn(
  ControlRef                      browser,
  DataBrowserTableViewColumnID *  column,
  Boolean *                       expandableRows)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* kDataBrowserColumnView API */
/*
 *  GetDataBrowserColumnViewPath()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserColumnViewPath(
  ControlRef   browser,
  Handle       path)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserColumnViewPathLength()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserColumnViewPathLength(
  ControlRef   browser,
  UInt32 *     pathLength)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserColumnViewPath()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserColumnViewPath(
  ControlRef                 browser,
  UInt32                     length,
  const DataBrowserItemID *  path)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDataBrowserColumnViewDisplayType()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDataBrowserColumnViewDisplayType(
  ControlRef                browser,
  DataBrowserPropertyType   propertyType)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataBrowserColumnViewDisplayType()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDataBrowserColumnViewDisplayType(
  ControlRef                 browser,
  DataBrowserPropertyType *  propertyType)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* DataBrowser UPP macros */
/*
    Customizing Data Browser Accessibility Information
    
    Warning: The following assumes you already understand how to handle the
    Accessibility Carbon Events described in CarbonEvents.h.
    
    Data Browser automatically handles the various Accessibility Carbon
    Events to provide a large amount of Accessibility information. However,
    your application may need to override or augment the default information
    that Data Browser provides.
    
    Though it is already possible for your application to install various
    Accessibility Carbon Event handlers on a Data Browser instance, it is
    impossible to interpret the AXUIElementRefs contained in the events
    without the help of the Data Browser. A given AXUIElementRef that is
    passed to Data Browser list view in an Accessibility Carbon Event could
    represent a row, a cell, or the list view as a whole. If your
    application needs to add an attribute to only the rows in a list view,
    your application will need to ask Data Browser what any given
    AXUIElementRef represents. The AXUIElementGetDataBrowserItemInfo allows
    your application to ask that question.
    
    Additionally, your application may want to generate its own AXUIElementRefs
    that represent children of or point to various rows or cells of a Data Browser
    instance. The AXUIElementCreateWithDataBrowserAndItemInfo API allows your
    application to manufacture AXUIElementRefs that represent certain parts of a
    Data Browser so you can provide them in your Accessibility Carbon Event
    handlers.
    
    Typical Usage Scenario: You want to add an Accessibility attribute to
    all rows in a Data Browser list view.
    
        Step 1: Install the appropriate Accessibility Carbon Event handlers
        on your Data Browser instance. Call InstallEventHandler or a similar
        API to install a handler onto your Data Browser ControlRef for the
        kEventAccessibleGetAllAttributeNames,
        kEventAccessibleGetNamedAttribute, and other appropriate events.
        
        Step 2: Your handler should find out what part of the Data Browser
        is being asked for its accessibility information. Extract the
        kEventParamAccessibleObject parameter out of the Carbon Event and
        pass it to AXUIElementGetDataBrowserItemInfo. See that API
        description for more usage information and calling requirements.
        Examine the DataBrowserAccessibilityItemInfo structure that is
        filled out to determine whether it represents the part of the Data
        Browser you are interested in adding an attribute to. In this case,
        you are looking for a row, so you would make sure the item field is
        not kDataBrowserNoItem, and that the columnProperty is
        kDataBrowserItemNoProperty.
        
        Step 3: Your event handler should call CallNextEventHandler to allow
        the Data Browser to do the default handling of the event. This is
        particularly important if the AXUIElementRef did not represent a
        row, since you don't want to disrupt the Data Browser's handling of
        the event for parts other than rows.
        
        Step 4: If you determined that the part was a row in step 2, your
        handler should now do whatever custom work it deems necessary. For
        the kEventAccessibleGetAllAttributeNames, your handler would extract
        the kEventParamAccessibleAttributeNames parameter out of the event
        and add your custom attribute name to the array. For the
        kEventAccessibleGetNamedAttribute event, your handler would test the
        kEventParamAccessibleAttributeName parameter to see if it matches
        your custom attribute name; if so, your handler would put its custom
        data in the kEventParamAccessibleAttributeValue parameter. Any other
        events would be handled similarly.
        
        Step 5: Your event handler should return an appropriate result code.
        In cases where the AXUIElementRef does not represent a row or when
        the attribute name is not your custom attribute, your handler can
        return the same result code that was returned by
        CallNextEventHandler in step 3. In cases where your handler decided
        to augment or override the default handling of the event, your
        handler will typically want to return noErr. See the Carbon Event
        documentation for more details on the meanings of result codes
        returned by event handlers.
*/

/*
 *  DataBrowserAccessibilityItemInfoV0
 *  
 *  Summary:
 *    A specific description of Data Browser accessibility item
 *    information.
 *  
 *  Discussion:
 *    If you fill this structure as part of a
 *    DataBrowserAccessibilityItemInfo, you must set the
 *    DataBrowserAccessibilityItemInfo's version field to zero.
 */
struct DataBrowserAccessibilityItemInfoV0 {

  /*
   * The DataBrowserItemID of the container the AXUIElementRef
   * represents or lives within. Even kDataBrowserNoItem might be
   * meaningful, since it is the root container ID if you haven't
   * overridden it via SetDataBrowserTarget. In list view, the
   * container helps narrow down the AXUIElementRef to either a
   * disclosed child of another row, or the list as a whole. In column
   * view, the container helps narrow down the AXUIElementRef to a
   * column; also see the columnProperty description below.
   */
  DataBrowserItemID   container;

  /*
   * The DataBrowserItemID of the item the AXUIElementRef represents or
   * lives within. If item is kDataBrowserNoItem, the AXUIElementRef
   * represents just the container. In list view, the item helps narrow
   * down the AXUIElementRef to either a row, or the root container as
   * a whole. In column view, the item helps narrow down the
   * AXUIElementRef to either a cell, or a column as a whole; also see
   * the columnProperty description below.
   */
  DataBrowserItemID   item;

  /*
   * The DataBrowserPropertyID of the column the AXUIElementRef
   * represents or lives within. If columnProperty is
   * kDataBrowserItemNoProperty and item is not kDataBrowserNoItem, the
   * AXUIElementRef represents a whole row. In list view, this field
   * helps narrow down the AXUIElementRef to either a cell, or a row as
   * a whole. In column view, the columnProperty will/must always be
   * set to kDataBrowserItemNoProperty unless the AXUIElementRef
   * represents the preview column. When the AXUIElementRef represents
   * the preview column, the columnProperty will/must always be set to
   * kDataBrowserColumnViewPreviewProperty, and the other fields of
   * this structure will/must be set to zero or the equivalent constant.
   */
  DataBrowserPropertyID  columnProperty;

  /*
   * The DataBrowserPropertyPart of the sub-cell part the
   * AXUIElementRef represents. Examples include the disclosure
   * triangle in a cell, the text in a cell, and the check box in a
   * cell. If propertyPart is kDataBrowserPropertyEnclosingPart and
   * columnProperty is not kDataBrowserItemNoProperty, the
   * AXUIElementRef represents the cell as a whole. In both list view
   * and column view, this field helps narrow down the AXUIElementRef
   * to either a sub-cell part, or a cell as a whole. For column view,
   * also see the columnProperty description above.
   */
  DataBrowserPropertyPart  propertyPart;
};
typedef struct DataBrowserAccessibilityItemInfoV0 DataBrowserAccessibilityItemInfoV0;

/*
 *  DataBrowserAccessibilityItemInfoV1
 *  
 *  Summary:
 *    A specific description of Data Browser accessibility item
 *    information.
 *  
 *  Discussion:
 *    If you fill this structure as part of a
 *    DataBrowserAccessibilityItemInfo, you must set the
 *    DataBrowserAccessibilityItemInfo's version field to one. 
 *     
 *    This structure is identical to the V0 structure except for the
 *    inclusion of row and column indicies. These indicies may be
 *    useful to clients who call AXUIElementGetDataBrowserItemInfo.
 *    
 *    If your Data Browser instance allows a given item and/or
 *    container to be displayed more than once at a given point in
 *    time, you can use the row and column indicies to differentiate
 *    the particular visual occurances of that item when calling
 *    AXUIElementCreateWithDataBrowserAndItemInfo. See the additional
 *    details in the rowIndex and columnIndex discussions below.
 */
struct DataBrowserAccessibilityItemInfoV1 {

  /*
   * The DataBrowserItemID of the container the AXUIElementRef
   * represents or lives within. Even kDataBrowserNoItem might be
   * meaningful, since it is the root container ID if you haven't
   * overridden it via SetDataBrowserTarget. In list view, the
   * container helps narrow down the AXUIElementRef to either a
   * disclosed child of another row, or the list as a whole. In column
   * view, the container helps narrow down the AXUIElementRef to a
   * column; also see the columnProperty description below.
   */
  DataBrowserItemID   container;

  /*
   * The DataBrowserItemID of the item the AXUIElementRef represents or
   * lives within. If item is kDataBrowserNoItem, the AXUIElementRef
   * represents just the container. In list view, the item helps narrow
   * down the AXUIElementRef to either a row, or the root container as
   * a whole. In column view, the item helps narrow down the
   * AXUIElementRef to either a cell, or a column as a whole; also see
   * the columnProperty description below.
   */
  DataBrowserItemID   item;

  /*
   * The DataBrowserPropertyID of the column the AXUIElementRef
   * represents or lives within. If columnProperty is
   * kDataBrowserItemNoProperty and item is not kDataBrowserNoItem, the
   * AXUIElementRef represents a whole row. In list view, this field
   * helps narrow down the AXUIElementRef to either a cell, or a row as
   * a whole. In column view, the columnProperty will/must always be
   * set to kDataBrowserItemNoProperty unless the AXUIElementRef
   * represents the preview column. When the AXUIElementRef represents
   * the preview column, the columnProperty will/must always be set to
   * kDataBrowserColumnViewPreviewProperty, and the other fields of
   * this structure will/must be set to zero or the equivalent constant.
   */
  DataBrowserPropertyID  columnProperty;

  /*
   * The DataBrowserPropertyPart of the sub-cell part the
   * AXUIElementRef represents. Examples include the disclosure
   * triangle in a cell, the text in a cell, and the check box in a
   * cell. If propertyPart is kDataBrowserPropertyEnclosingPart and
   * columnProperty is not kDataBrowserItemNoProperty, the
   * AXUIElementRef represents the cell as a whole. In both list view
   * and column view, this field helps narrow down the AXUIElementRef
   * to either a sub-cell part, or a cell as a whole. For column view,
   * also see the columnProperty description above.
   */
  DataBrowserPropertyPart  propertyPart;

  /*
   * The zero-based DataBrowserTableViewRowIndex of the row specified
   * by the other parts of this structure. If the other parts of this
   * structure do not specify a row or a part thereof, this field
   * will/must be set to zero; because this field is zero based, you
   * must test the other parts this structure to see whether this field
   * is meaningful. In list view, when the other parts of this
   * structure specify an item or part thereof, this field will/must be
   * set to the row index at which the specified item can be found. In
   * column view, when the other parts of this structure specify a cell
   * or part thereof, this field will/must be set to the row index at
   * which the specified cell can be found.
   */
  DataBrowserTableViewRowIndex  rowIndex;

  /*
   * The zero-based DataBrowserTableViewColumnIndex of the column
   * specified by the other parts of this structure. If the other parts
   * of this structure do not specify a column or a part thereof, this
   * field will/must be set to zero; because this field is zero based,
   * you must test the other parts this structure to see whether this
   * field is meaningful. In list view, when the other parts of this
   * structure specify a cell or part thereof, this field will/must be
   * set to the column index at which the specified cell can be found.
   * In column view, when the other parts of this structure specify a
   * column or part thereof, this field will/must be set to the column
   * index at which the specified cell can be found.
   */
  DataBrowserTableViewColumnIndex  columnIndex;
};
typedef struct DataBrowserAccessibilityItemInfoV1 DataBrowserAccessibilityItemInfoV1;

/*
 *  DataBrowserAccessibilityItemInfo
 *  
 *  Summary:
 *    A generalized description of Data Browser accessibility item
 *    information.
 *  
 *  Discussion:
 *    Pass this structure to AXUIElementGetDataBrowserItemInfo or
 *    AXUIElementCreateWithDataBrowserAndItemInfo.
 */
struct DataBrowserAccessibilityItemInfo {

  /*
   * A UInt32 which identifies how to interpret the following union.
   * Set this field to zero if you fill out the union's data in the
   * form of a DataBrowserAccessibilityItemInfoV0 structure. Set this
   * field to one if you fill out the union's data in the form of a
   * DataBrowserAccessibilityItemInfoV1 structure.
   */
  UInt32              version;
  union {
    DataBrowserAccessibilityItemInfoV0  v0;
    DataBrowserAccessibilityItemInfoV1  v1;
  }                       u;
};
typedef struct DataBrowserAccessibilityItemInfo DataBrowserAccessibilityItemInfo;
/*
 *  AXUIElementGetDataBrowserItemInfo()
 *  
 *  Summary:
 *    Gets a description of the part of a Data Browser represented by a
 *    given AXUIElementRef.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inElement:
 *      An AXUIElementRef representing part of a Data Browser.
 *    
 *    inDataBrowser:
 *      A Data Browser ControlRef.
 *    
 *    inDesiredInfoVersion:
 *      A UInt32 indicating the the version you want the ioInfo
 *      structure passed back as. Currently, the only supported version
 *      is zero, so you must pass zero in the inDesiredInfoVersion
 *      parameter.
 *    
 *    outInfo:
 *      A DataBrowserAccessibilityItemInfo that will be filled in with
 *      a description of the part of the Data Browser that the
 *      AXUIElementRef represents.
 *  
 *  Result:
 *    An OSStatus result code. The function will return noErr if it was
 *    able to generate a description of the AXUIElementRef. If the
 *    AXUIElementRef does not represent the Data Browser you passed in,
 *    the function will return paramErr. If the AXUIElementRef
 *    represents some non-item part of the Data Browser, the function
 *    will return errDataBrowserItemNotFound.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
AXUIElementGetDataBrowserItemInfo(
  AXUIElementRef                      inElement,
  ControlRef                          inDataBrowser,
  UInt32                              inDesiredInfoVersion,
  DataBrowserAccessibilityItemInfo *  outInfo)                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  AXUIElementCreateWithDataBrowserAndItemInfo()
 *  
 *  Summary:
 *    Creates an AXUIElementRef to represent some part of a Data
 *    Browser accessibility hierarchy.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inDataBrowser:
 *      A Data Browser ControlRef.
 *    
 *    inInfo:
 *      A DataBrowserAccessibilityItemInfo describing the part of the
 *      Data Browser for which you want to create an AXUIElementRef.
 *  
 *  Result:
 *    An AXUIElementRef representing the part, or NULL if one cannot be
 *    created to represent the part you specified.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern AXUIElementRef 
AXUIElementCreateWithDataBrowserAndItemInfo(
  ControlRef                                inDataBrowser,
  const DataBrowserAccessibilityItemInfo *  inInfo)           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*---------------------------------------------------------------------------------------*/
/* EditUnicodeText Control                                                               */
/*---------------------------------------------------------------------------------------*/
/* This control is only available in Mac OS X.  It is super similar to Edit Text control */
/* Use all the same Get/Set tags.  But don't ask for the TEHandle.                       */
/*---------------------------------------------------------------------------------------*/
/* This callback supplies the functionality of the TSMTEPostUpdateProcPtr that is used */
/* in the EditText control.  A client should supply this call if they want to look at  */
/* inline text that has been fixed before it is included in the actual body text       */
/* if the new text (i.e. the text in the handle) should be included in the body text    */
/* the client should return true.  If the client wants to block the inclusion of the    */
/* text they should return false.                                                       */
typedef CALLBACK_API( Boolean , EditUnicodePostUpdateProcPtr )(UniCharArrayHandle uniText, UniCharCount uniTextLength, UniCharArrayOffset iStartOffset, UniCharArrayOffset iEndOffset, void *refcon);
typedef STACK_UPP_TYPE(EditUnicodePostUpdateProcPtr)            EditUnicodePostUpdateUPP;
/*
 *  NewEditUnicodePostUpdateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern EditUnicodePostUpdateUPP
NewEditUnicodePostUpdateUPP(EditUnicodePostUpdateProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeEditUnicodePostUpdateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void
DisposeEditUnicodePostUpdateUPP(EditUnicodePostUpdateUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeEditUnicodePostUpdateUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean
InvokeEditUnicodePostUpdateUPP(
  UniCharArrayHandle        uniText,
  UniCharCount              uniTextLength,
  UniCharArrayOffset        iStartOffset,
  UniCharArrayOffset        iEndOffset,
  void *                    refcon,
  EditUnicodePostUpdateUPP  userUPP)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

enum {
  kControlEditUnicodeTextProc   = 912,
  kControlEditUnicodeTextPasswordProc = 914
};

/* Control Kind Tag */
enum {
  kControlKindEditUnicodeText   = 'eutx'
};

/* The HIObject class ID for the HITextField class. */
#define kHITextFieldClassID             CFSTR("com.apple.HITextField")
/*
 *  CreateEditUnicodeTextControl()
 *  
 *  Summary:
 *    Creates a new edit text control.
 *  
 *  Discussion:
 *    This is the preferred edit text control. Use it instead of the
 *    EditText control. This control handles Unicode and draws its text
 *    using antialiasing, which the other control does not.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    window:
 *      The window in which the control should be placed. May be NULL
 *      in 10.3 and later.
 *    
 *    boundsRect:
 *      The bounds of the control, in local coordinates of the window.
 *    
 *    text:
 *      The text of the control. May be NULL.
 *    
 *    isPassword:
 *      A Boolean indicating whether the field is to be used as a
 *      password field. Passing false indicates that the field is to
 *      display entered text normally. True means that the field will
 *      be used as a password field and any text typed into the field
 *      will be displayed only as bullets.
 *    
 *    style:
 *      The control's font style, size, color, and so on. May be NULL.
 *    
 *    outControl:
 *      On exit, contains the new control (if noErr is returned as the
 *      result code).
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateEditUnicodeTextControl(
  WindowRef                    window,
  const Rect *                 boundsRect,
  CFStringRef                  text,             /* can be NULL */
  Boolean                      isPassword,
  const ControlFontStyleRec *  style,            /* can be NULL */
  ControlRef *                 outControl)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    The EditUnicodeText control supports these tags previously defined for the EditText control:
    
        kControlEditTextLockedTag
        kControlFontStyleTag
        kControlEditTextFixedTextTag
        kControlEditTextTextTag
        kControlEditTextKeyFilterTag
        kControlEditTextValidationProcTag
        kControlEditTextSelectionTag
        kControlEditTextKeyScriptBehaviorTag
        kControlEditTextCFStringTag
        kControlEditTextPasswordTag
        kControlEditTextPasswordCFStringTag
*/
/* Tagged data supported by EditUnicodeText control only */
enum {
  kControlEditTextSingleLineTag = 'sglc', /* data is a Boolean; indicates whether the control should always be single-line*/
  kControlEditTextInsertTextBufferTag = 'intx', /* data is an array of char; get or set the control's text as WorldScript-encoded text*/
  kControlEditTextInsertCFStringRefTag = 'incf', /* data is a CFStringRef; get or set the control's text as a CFStringRef. Caller should release CFString if getting.*/
  kControlEditUnicodeTextPostUpdateProcTag = 'upup' /* data is a UnicodePostUpdateUPP; get or set the post-update proc*/
};

#if OLDROUTINENAMES
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ OLDROUTINENAMES                                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kControlCheckboxUncheckedValue = kControlCheckBoxUncheckedValue,
  kControlCheckboxCheckedValue  = kControlCheckBoxCheckedValue,
  kControlCheckboxMixedValue    = kControlCheckBoxMixedValue
};

enum {
  inLabel                       = kControlLabelPart,
  inMenu                        = kControlMenuPart,
  inTriangle                    = kControlTrianglePart,
  inButton                      = kControlButtonPart,
  inCheckBox                    = kControlCheckBoxPart,
  inUpButton                    = kControlUpButtonPart,
  inDownButton                  = kControlDownButtonPart,
  inPageUp                      = kControlPageUpPart,
  inPageDown                    = kControlPageDownPart
};

enum {
  kInLabelControlPart           = kControlLabelPart,
  kInMenuControlPart            = kControlMenuPart,
  kInTriangleControlPart        = kControlTrianglePart,
  kInButtonControlPart          = kControlButtonPart,
  kInCheckBoxControlPart        = kControlCheckBoxPart,
  kInUpButtonControlPart        = kControlUpButtonPart,
  kInDownButtonControlPart      = kControlDownButtonPart,
  kInPageUpControlPart          = kControlPageUpPart,
  kInPageDownControlPart        = kControlPageDownPart
};


#endif  /* OLDROUTINENAMES */





#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __CONTROLDEFINITIONS__ */


/*
     File:       HIToolbox/Appearance.h
 
     Contains:   Appearance Manager Interfaces.
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1994-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __APPEARANCE__
#define __APPEARANCE__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __QUICKDRAW__
#include <QD/Quickdraw.h>
#endif

#ifndef __TEXTEDIT__
#include <HIToolbox/TextEdit.h>
#endif

#ifndef __QDOFFSCREEN__
#include <QD/QDOffscreen.h>
#endif

#ifndef __MACWINDOWS__
#include <HIToolbox/MacWindows.h>
#endif

#ifndef __CONTROLS__
#include <HIToolbox/Controls.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif

#ifndef __TEXTUTILS__
#include <CarbonCore/TextUtils.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Appearance Manager constants, etc.                                               */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Appearance Manager Apple Events (1.1 and later)              */


#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

enum {
  kAppearanceEventClass         = 'appr', /* Event Class */
  kAEAppearanceChanged          = 'thme', /* Appearance changed (e.g. platinum to hi-tech) */
  kAESystemFontChanged          = 'sysf', /* system font changed */
  kAESmallSystemFontChanged     = 'ssfn', /* small system font changed */
  kAEViewsFontChanged           = 'vfnt' /* views font changed */
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Appearance Manager file types                                                    */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeDataFileType            = 'thme', /* file type for theme files */
  kThemePlatinumFileType        = 'pltn', /* file type for platinum appearance */
  kThemeCustomThemesFileType    = 'scen', /* file type for user themes */
  kThemeSoundTrackFileType      = 'tsnd'
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Appearance Manager Supported Themes                                              */
/* Use CopyThemeIdentifier to get the current theme ID                              */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

#define kThemeAppearancePlatinum       CFSTR( "com.apple.theme.appearance.platinum" )
#define kThemeAppearanceAqua         CFSTR( "com.apple.theme.appearance.aqua" )
#define kThemeAppearanceAquaBlue     CFSTR( "com.apple.theme.appearance.aqua.blue" )
#define kThemeAppearanceAquaGraphite    CFSTR( "com.apple.theme.appearance.aqua.graphite" )

enum {
  kThemeBrushDialogBackgroundActive = 1, /* Dialogs */
  kThemeBrushDialogBackgroundInactive = 2, /* Dialogs */
  kThemeBrushAlertBackgroundActive = 3,
  kThemeBrushAlertBackgroundInactive = 4,
  kThemeBrushModelessDialogBackgroundActive = 5,
  kThemeBrushModelessDialogBackgroundInactive = 6,
  kThemeBrushUtilityWindowBackgroundActive = 7, /* Miscellaneous */
  kThemeBrushUtilityWindowBackgroundInactive = 8, /* Miscellaneous */
  kThemeBrushListViewSortColumnBackground = 9, /* Finder */
  kThemeBrushListViewBackground = 10,
  kThemeBrushIconLabelBackground = 11,
  kThemeBrushListViewSeparator  = 12,
  kThemeBrushChasingArrows      = 13,
  kThemeBrushDragHilite         = 14,
  kThemeBrushDocumentWindowBackground = 15,
  kThemeBrushFinderWindowBackground = 16
};

/* Brushes available in Appearance 1.1 or later */
enum {
  kThemeBrushScrollBarDelimiterActive = 17,
  kThemeBrushScrollBarDelimiterInactive = 18,
  kThemeBrushFocusHighlight     = 19,
  kThemeBrushPopupArrowActive   = 20,
  kThemeBrushPopupArrowPressed  = 21,
  kThemeBrushPopupArrowInactive = 22,
  kThemeBrushAppleGuideCoachmark = 23,
  kThemeBrushIconLabelBackgroundSelected = 24,
  kThemeBrushStaticAreaFill     = 25,
  kThemeBrushActiveAreaFill     = 26,
  kThemeBrushButtonFrameActive  = 27,
  kThemeBrushButtonFrameInactive = 28,
  kThemeBrushButtonFaceActive   = 29,
  kThemeBrushButtonFaceInactive = 30,
  kThemeBrushButtonFacePressed  = 31,
  kThemeBrushButtonActiveDarkShadow = 32,
  kThemeBrushButtonActiveDarkHighlight = 33,
  kThemeBrushButtonActiveLightShadow = 34,
  kThemeBrushButtonActiveLightHighlight = 35,
  kThemeBrushButtonInactiveDarkShadow = 36,
  kThemeBrushButtonInactiveDarkHighlight = 37,
  kThemeBrushButtonInactiveLightShadow = 38,
  kThemeBrushButtonInactiveLightHighlight = 39,
  kThemeBrushButtonPressedDarkShadow = 40,
  kThemeBrushButtonPressedDarkHighlight = 41,
  kThemeBrushButtonPressedLightShadow = 42,
  kThemeBrushButtonPressedLightHighlight = 43,
  kThemeBrushBevelActiveLight   = 44,
  kThemeBrushBevelActiveDark    = 45,
  kThemeBrushBevelInactiveLight = 46,
  kThemeBrushBevelInactiveDark  = 47
};

/* Brushes available in Appearance 1.1.1 or later */
enum {
  kThemeBrushNotificationWindowBackground = 48
};

/* Brushes available in Appearance X or later */
enum {
  kThemeBrushMovableModalBackground = 49,
  kThemeBrushSheetBackgroundOpaque = 50,
  kThemeBrushDrawerBackground   = 51,
  kThemeBrushToolbarBackground  = 52,
  kThemeBrushSheetBackgroundTransparent = 53
};

/* Appearance X or later theme brush compatibility synonyms */
enum {
  kThemeBrushSheetBackground    = kThemeBrushSheetBackgroundOpaque
};

/* These values are meta-brushes, specific colors that do not       */
/* change from theme to theme. You can use them instead of using    */
/* direct RGB values.                                               */
enum {
  kThemeBrushBlack              = -1,
  kThemeBrushWhite              = -2
};

typedef SInt16                          ThemeBrush;
enum {
  kThemeTextColorDialogActive   = 1,
  kThemeTextColorDialogInactive = 2,
  kThemeTextColorAlertActive    = 3,
  kThemeTextColorAlertInactive  = 4,
  kThemeTextColorModelessDialogActive = 5,
  kThemeTextColorModelessDialogInactive = 6,
  kThemeTextColorWindowHeaderActive = 7,
  kThemeTextColorWindowHeaderInactive = 8,
  kThemeTextColorPlacardActive  = 9,
  kThemeTextColorPlacardInactive = 10,
  kThemeTextColorPlacardPressed = 11,
  kThemeTextColorPushButtonActive = 12,
  kThemeTextColorPushButtonInactive = 13,
  kThemeTextColorPushButtonPressed = 14,
  kThemeTextColorBevelButtonActive = 15,
  kThemeTextColorBevelButtonInactive = 16,
  kThemeTextColorBevelButtonPressed = 17,
  kThemeTextColorPopupButtonActive = 18,
  kThemeTextColorPopupButtonInactive = 19,
  kThemeTextColorPopupButtonPressed = 20,
  kThemeTextColorIconLabel      = 21,
  kThemeTextColorListView       = 22
};

/* Text Colors available in Appearance 1.0.1 or later */
enum {
  kThemeTextColorDocumentWindowTitleActive = 23,
  kThemeTextColorDocumentWindowTitleInactive = 24,
  kThemeTextColorMovableModalWindowTitleActive = 25,
  kThemeTextColorMovableModalWindowTitleInactive = 26,
  kThemeTextColorUtilityWindowTitleActive = 27,
  kThemeTextColorUtilityWindowTitleInactive = 28,
  kThemeTextColorPopupWindowTitleActive = 29,
  kThemeTextColorPopupWindowTitleInactive = 30,
  kThemeTextColorRootMenuActive = 31,
  kThemeTextColorRootMenuSelected = 32,
  kThemeTextColorRootMenuDisabled = 33,
  kThemeTextColorMenuItemActive = 34,
  kThemeTextColorMenuItemSelected = 35,
  kThemeTextColorMenuItemDisabled = 36,
  kThemeTextColorPopupLabelActive = 37,
  kThemeTextColorPopupLabelInactive = 38
};


/* Text colors available in Appearance 1.1 or later */
enum {
  kThemeTextColorTabFrontActive = 39,
  kThemeTextColorTabNonFrontActive = 40,
  kThemeTextColorTabNonFrontPressed = 41,
  kThemeTextColorTabFrontInactive = 42,
  kThemeTextColorTabNonFrontInactive = 43,
  kThemeTextColorIconLabelSelected = 44,
  kThemeTextColorBevelButtonStickyActive = 45,
  kThemeTextColorBevelButtonStickyInactive = 46
};

/* Text colors available in Appearance 1.1.1 or later */
enum {
  kThemeTextColorNotification   = 47
};

/* These values are specific colors that do not change from             */
/* theme to theme. You can use them instead of using direct RGB values. */
enum {
  kThemeTextColorBlack          = -1,
  kThemeTextColorWhite          = -2
};

typedef SInt16                          ThemeTextColor;
/* States to draw primitives: disabled, active, and pressed (hilited) */
enum {
  kThemeStateInactive           = 0,
  kThemeStateActive             = 1,
  kThemeStatePressed            = 2,
  kThemeStateRollover           = 6,
  kThemeStateUnavailable        = 7,
  kThemeStateUnavailableInactive = 8
};

/* obsolete name */
enum {
  kThemeStateDisabled           = 0
};

enum {
  kThemeStatePressedUp          = 2,    /* draw with up pressed     (increment/decrement buttons) */
  kThemeStatePressedDown        = 3     /* draw with down pressed (increment/decrement buttons) */
};

typedef UInt32                          ThemeDrawState;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Theme cursor selectors available in Appearance 1.1 or later                      */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeArrowCursor             = 0,
  kThemeCopyArrowCursor         = 1,
  kThemeAliasArrowCursor        = 2,
  kThemeContextualMenuArrowCursor = 3,
  kThemeIBeamCursor             = 4,
  kThemeCrossCursor             = 5,
  kThemePlusCursor              = 6,
  kThemeWatchCursor             = 7,    /* Can Animate */
  kThemeClosedHandCursor        = 8,
  kThemeOpenHandCursor          = 9,
  kThemePointingHandCursor      = 10,
  kThemeCountingUpHandCursor    = 11,   /* Can Animate */
  kThemeCountingDownHandCursor  = 12,   /* Can Animate */
  kThemeCountingUpAndDownHandCursor = 13, /* Can Animate */
  kThemeSpinningCursor          = 14,   /* Can Animate */
  kThemeResizeLeftCursor        = 15,
  kThemeResizeRightCursor       = 16,
  kThemeResizeLeftRightCursor   = 17
};

typedef UInt32                          ThemeCursor;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Theme menu bar drawing states                                                    */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeMenuBarNormal           = 0,
  kThemeMenuBarSelected         = 1
};

typedef UInt16                          ThemeMenuBarState;
/* attributes */
enum {
  kThemeMenuSquareMenuBar       = (1 << 0)
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Theme menu drawing states                                                        */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeMenuActive              = 0,
  kThemeMenuSelected            = 1,
  kThemeMenuDisabled            = 3
};

typedef UInt16                          ThemeMenuState;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* MenuType: add kThemeMenuTypeInactive to menu type for DrawThemeMenuBackground if entire  */
/* menu is inactive                                                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeMenuTypePullDown        = 0,
  kThemeMenuTypePopUp           = 1,
  kThemeMenuTypeHierarchical    = 2,
  kThemeMenuTypeInactive        = 0x0100
};

typedef UInt16                          ThemeMenuType;
enum {
  kThemeMenuItemPlain           = 0,
  kThemeMenuItemHierarchical    = 1,    /* item has hierarchical arrow*/
  kThemeMenuItemScrollUpArrow   = 2,    /* for scrollable menus, indicates item is scroller*/
  kThemeMenuItemScrollDownArrow = 3,
  kThemeMenuItemAtTop           = 0x0100, /* indicates item is being drawn at top of menu*/
  kThemeMenuItemAtBottom        = 0x0200, /* indicates item is being drawn at bottom of menu*/
  kThemeMenuItemHierBackground  = 0x0400, /* item is within a hierarchical menu*/
  kThemeMenuItemPopUpBackground = 0x0800, /* item is within a popped up menu*/
  kThemeMenuItemHasIcon         = 0x8000, /* add into non-arrow type when icon present*/
  kThemeMenuItemNoBackground    = 0x4000 /* don't draw the menu background while drawing this item (Mac OS X only)*/
};

typedef UInt16                          ThemeMenuItemType;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Theme Backgrounds                                                                        */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeBackgroundTabPane       = 1,
  kThemeBackgroundPlacard       = 2,
  kThemeBackgroundWindowHeader  = 3,
  kThemeBackgroundListViewWindowHeader = 4,
  kThemeBackgroundSecondaryGroupBox = 5
};

typedef UInt32                          ThemeBackgroundKind;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Theme Collection tags for Get/SetTheme                                                   */
/*                                                                                          */
/*  X ALERT: Please note that Get/SetTheme are severely neutered under Mac OS X at present. */
/*           The first group of tags below are available to get under both 9 and X. The     */
/*           second group is 9 only. None of the tags can be used in SetTheme on X, as it   */
/*           is completely inert on X, and will return unimpErr.                            */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeNameTag                 = 'name', /* Str255*/
  kThemeVariantNameTag          = 'varn', /* Str255*/
  kThemeVariantBaseTintTag      = 'tint', /* RGBColor*/
  kThemeHighlightColorTag       = 'hcol', /* RGBColor*/
  kThemeScrollBarArrowStyleTag  = 'sbar', /* ThemeScrollBarArrowStyle*/
  kThemeScrollBarThumbStyleTag  = 'sbth', /* ThemeScrollBarThumbStyle*/
  kThemeSoundsEnabledTag        = 'snds', /* Boolean*/
  kThemeDblClickCollapseTag     = 'coll' /* Boolean*/
};

enum {
  kThemeAppearanceFileNameTag   = 'thme', /* Str255*/
  kThemeSystemFontTag           = 'lgsf', /* Str255*/
  kThemeSmallSystemFontTag      = 'smsf', /* Str255*/
  kThemeViewsFontTag            = 'vfnt', /* Str255*/
  kThemeViewsFontSizeTag        = 'vfsz', /* SInt16*/
  kThemeDesktopPatternNameTag   = 'patn', /* Str255*/
  kThemeDesktopPatternTag       = 'patt', /* <variable-length data> (flattened pattern)*/
  kThemeDesktopPictureNameTag   = 'dpnm', /* Str255*/
  kThemeDesktopPictureAliasTag  = 'dpal', /* <alias handle>*/
  kThemeDesktopPictureAlignmentTag = 'dpan', /* UInt32*/
  kThemeHighlightColorNameTag   = 'hcnm', /* Str255*/
  kThemeExamplePictureIDTag     = 'epic', /* SInt16*/
  kThemeSoundTrackNameTag       = 'sndt', /* Str255*/
  kThemeSoundMaskTag            = 'smsk', /* UInt32*/
  kThemeUserDefinedTag          = 'user', /* Boolean (this should _always_ be true if present - used by Control Panel).*/
  kThemeSmoothFontEnabledTag    = 'smoo', /* Boolean*/
  kThemeSmoothFontMinSizeTag    = 'smos' /* UInt16 (must be >= 12 and <= 24)*/
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Theme Control Settings                                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeCheckBoxClassicX        = 0,    /* check box with an 'X'*/
  kThemeCheckBoxCheckMark       = 1     /* check box with a real check mark*/
};

typedef UInt16                          ThemeCheckBoxStyle;
enum {
  kThemeScrollBarArrowsSingle   = 0,    /* single arrow on each end*/
  kThemeScrollBarArrowsLowerRight = 1   /* double arrows only on right or bottom*/
};

typedef UInt16                          ThemeScrollBarArrowStyle;
enum {
  kThemeScrollBarThumbNormal    = 0,    /* normal, classic thumb size*/
  kThemeScrollBarThumbProportional = 1  /* proportional thumbs*/
};

typedef UInt16                          ThemeScrollBarThumbStyle;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Font constants                                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeSystemFont              = 0,
  kThemeSmallSystemFont         = 1,
  kThemeSmallEmphasizedSystemFont = 2,
  kThemeViewsFont               = 3,    /* The following ID's are only available with MacOS X or CarbonLib 1.3 and later*/
  kThemeEmphasizedSystemFont    = 4,
  kThemeApplicationFont         = 5,
  kThemeLabelFont               = 6,
  kThemeMenuTitleFont           = 100,
  kThemeMenuItemFont            = 101,
  kThemeMenuItemMarkFont        = 102,
  kThemeMenuItemCmdKeyFont      = 103,
  kThemeWindowTitleFont         = 104,
  kThemePushButtonFont          = 105,
  kThemeUtilityWindowTitleFont  = 106,
  kThemeAlertHeaderFont         = 107,
  kThemeCurrentPortFont         = 200
};

/* This is the total of the PUBLIC ThemeFontIDs!*/
enum {
  kPublicThemeFontCount         = 16
};

typedef UInt16                          ThemeFontID;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Tab constants                                                                            */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeTabNonFront             = 0,
  kThemeTabNonFrontPressed      = 1,
  kThemeTabNonFrontInactive     = 2,
  kThemeTabFront                = 3,
  kThemeTabFrontInactive        = 4,
  kThemeTabNonFrontUnavailable  = 5,
  kThemeTabFrontUnavailable     = 6
};

typedef UInt16                          ThemeTabStyle;
enum {
  kThemeTabNorth                = 0,
  kThemeTabSouth                = 1,
  kThemeTabEast                 = 2,
  kThemeTabWest                 = 3
};

typedef UInt16                          ThemeTabDirection;
/* NOTE ON TAB HEIGHT                                                                       */
/* Use the kThemeSmallTabHeightMax and kThemeLargeTabHeightMax when calculating the rects   */
/* to draw tabs into. This height includes the tab frame overlap. Tabs that are not in the  */
/* front are only drawn down to where they meet the frame, as if the height was just        */
/* kThemeLargeTabHeight, for example, as opposed to the ...Max constant. Remember that for  */
/* East and West tabs, the height referred to below is actually the width.                  */
enum {
  kThemeSmallTabHeight          = 16,   /* amount small tabs protrude from frame.*/
  kThemeLargeTabHeight          = 21,   /* amount large tabs protrude from frame.*/
  kThemeTabPaneOverlap          = 3,    /* amount tabs overlap frame.*/
  kThemeSmallTabHeightMax       = 19,   /* small tab height + overlap*/
  kThemeLargeTabHeightMax       = 24    /* large tab height + overlap*/
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Track kinds                                                                              */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeMediumScrollBar         = 0,
  kThemeSmallScrollBar          = 1,
  kThemeMediumSlider            = 2,
  kThemeMediumProgressBar       = 3,
  kThemeMediumIndeterminateBar  = 4,
  kThemeRelevanceBar            = 5,
  kThemeSmallSlider             = 6,
  kThemeLargeProgressBar        = 7,
  kThemeLargeIndeterminateBar   = 8
};

typedef UInt16                          ThemeTrackKind;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Track enable states                                                                      */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
                                        /* track states */
  kThemeTrackActive             = 0,
  kThemeTrackDisabled           = 1,
  kThemeTrackNothingToScroll    = 2,
  kThemeTrackInactive           = 3
};

typedef UInt8                           ThemeTrackEnableState;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Track pressed states                                                                     */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
                                        /* press states (ignored unless track is active) */
  kThemeLeftOutsideArrowPressed = 0x01,
  kThemeLeftInsideArrowPressed  = 0x02,
  kThemeLeftTrackPressed        = 0x04,
  kThemeThumbPressed            = 0x08,
  kThemeRightTrackPressed       = 0x10,
  kThemeRightInsideArrowPressed = 0x20,
  kThemeRightOutsideArrowPressed = 0x40,
  kThemeTopOutsideArrowPressed  = kThemeLeftOutsideArrowPressed,
  kThemeTopInsideArrowPressed   = kThemeLeftInsideArrowPressed,
  kThemeTopTrackPressed         = kThemeLeftTrackPressed,
  kThemeBottomTrackPressed      = kThemeRightTrackPressed,
  kThemeBottomInsideArrowPressed = kThemeRightInsideArrowPressed,
  kThemeBottomOutsideArrowPressed = kThemeRightOutsideArrowPressed
};

typedef UInt8                           ThemeTrackPressState;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Thumb directions                                                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
                                        /* thumb direction */
  kThemeThumbPlain              = 0,
  kThemeThumbUpward             = 1,
  kThemeThumbDownward           = 2
};

typedef UInt8                           ThemeThumbDirection;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Track attributes                                                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeTrackHorizontal         = (1 << 0), /* track is drawn horizontally*/
  kThemeTrackRightToLeft        = (1 << 1), /* track progresses from right to left*/
  kThemeTrackShowThumb          = (1 << 2), /* track's thumb should be drawn*/
  kThemeTrackThumbRgnIsNotGhost = (1 << 3), /* the provided thumbRgn should be drawn opaque, not as a ghost*/
  kThemeTrackNoScrollBarArrows  = (1 << 4) /* the scroll bar doesn't have arrows*/
};

typedef UInt16                          ThemeTrackAttributes;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Track info block                                                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ScrollBarTrackInfo {
  SInt32              viewsize;               /* current view range size */
  ThemeTrackPressState  pressState;           /* pressed parts state */
};
typedef struct ScrollBarTrackInfo       ScrollBarTrackInfo;
struct SliderTrackInfo {
  ThemeThumbDirection  thumbDir;              /* thumb direction */
  ThemeTrackPressState  pressState;           /* pressed parts state */
};
typedef struct SliderTrackInfo          SliderTrackInfo;
struct ProgressTrackInfo {
  UInt8               phase;                  /* phase for indeterminate progress */
};
typedef struct ProgressTrackInfo        ProgressTrackInfo;
struct ThemeTrackDrawInfo {
  ThemeTrackKind      kind;                   /* what kind of track this info is for */
  Rect                bounds;                 /* track basis rectangle */
  SInt32              min;                    /* min track value */
  SInt32              max;                    /* max track value */
  SInt32              value;                  /* current thumb value */
  UInt32              reserved;

  ThemeTrackAttributes  attributes;           /* various track attributes */
  ThemeTrackEnableState  enableState;         /* enable state */
  UInt8               filler1;

  union {
    ScrollBarTrackInfo  scrollbar;
    SliderTrackInfo     slider;
    ProgressTrackInfo   progress;
  }                       trackInfo;
};
typedef struct ThemeTrackDrawInfo       ThemeTrackDrawInfo;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* ThemeWindowAttributes                                                                    */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeWindowHasGrow           = (1 << 0), /* can the size of the window be changed by the user? */
  kThemeWindowHasHorizontalZoom = (1 << 3), /* window can zoom only horizontally */
  kThemeWindowHasVerticalZoom   = (1 << 4), /* window can zoom only vertically */
  kThemeWindowHasFullZoom       = kThemeWindowHasHorizontalZoom + kThemeWindowHasVerticalZoom, /* window zooms in all directions */
  kThemeWindowHasCloseBox       = (1 << 5), /* window has a close box */
  kThemeWindowHasCollapseBox    = (1 << 6), /* window has a collapse box */
  kThemeWindowHasTitleText      = (1 << 7), /* window has a title/title icon */
  kThemeWindowIsCollapsed       = (1 << 8), /* window is in the collapsed state */
  kThemeWindowHasDirty          = (1 << 9)
};


typedef UInt32                          ThemeWindowAttributes;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Window Types Supported by the Appearance Manager                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeDocumentWindow          = 0,
  kThemeDialogWindow            = 1,
  kThemeMovableDialogWindow     = 2,
  kThemeAlertWindow             = 3,
  kThemeMovableAlertWindow      = 4,
  kThemePlainDialogWindow       = 5,
  kThemeShadowDialogWindow      = 6,
  kThemePopupWindow             = 7,
  kThemeUtilityWindow           = 8,
  kThemeUtilitySideWindow       = 9,
  kThemeSheetWindow             = 10
};

typedef UInt16                          ThemeWindowType;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Window Widgets Supported by the Appearance Manager                                       */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeWidgetCloseBox          = 0,
  kThemeWidgetZoomBox           = 1,
  kThemeWidgetCollapseBox       = 2,
  kThemeWidgetDirtyCloseBox     = 6
};

enum {
                                        /* Old/Obsolete name to be removed*/
  kThemeWidgetABox              = 3,
  kThemeWidgetBBox              = 4,
  kThemeWidgetBOffBox           = 5
};

typedef UInt16                          ThemeTitleBarWidget;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Popup arrow orientations                                                                 */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeArrowLeft               = 0,
  kThemeArrowDown               = 1,
  kThemeArrowRight              = 2,
  kThemeArrowUp                 = 3
};

typedef UInt16                          ThemeArrowOrientation;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Popup arrow sizes                                                                        */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeArrow3pt                = 0,
  kThemeArrow5pt                = 1,
  kThemeArrow7pt                = 2,
  kThemeArrow9pt                = 3
};

typedef UInt16                          ThemePopupArrowSize;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Grow box directions                                                                      */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeGrowLeft                = (1 << 0), /* can grow to the left */
  kThemeGrowRight               = (1 << 1), /* can grow to the right */
  kThemeGrowUp                  = (1 << 2), /* can grow up */
  kThemeGrowDown                = (1 << 3) /* can grow down */
};

typedef UInt16                          ThemeGrowDirection;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Button kinds                                                                             */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemePushButton              = 0,
  kThemeCheckBox                = 1,
  kThemeRadioButton             = 2,
  kThemeBevelButton             = 3,    /* bevel button (obsolete) */
  kThemeArrowButton             = 4,    /* popup button without text (no label). See ThemeButtonAdornment for glyphs. */
  kThemePopupButton             = 5,    /* popup button */
  kThemeDisclosureButton        = 6,
  kThemeIncDecButton            = 7,    /* increment/decrement buttons  (no label) */
  kThemeSmallBevelButton        = 8,    /* small-shadow bevel button */
  kThemeMediumBevelButton       = 3,    /* med-shadow bevel button */
  kThemeLargeBevelButton        = 9,    /* large-shadow bevel button */
  kThemeListHeaderButton        = 10,   /* sort button for top of list */
  kThemeRoundButton             = 11,   /* round button */
  kThemeLargeRoundButton        = 12,   /* large round button */
  kThemeSmallCheckBox           = 13,   /* small checkbox */
  kThemeSmallRadioButton        = 14,   /* small radio button */
  kThemeRoundedBevelButton      = 15,   /* rounded bevel button */
  kThemeNormalCheckBox          = kThemeCheckBox,
  kThemeNormalRadioButton       = kThemeRadioButton
};

typedef UInt16                          ThemeButtonKind;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Common button values                                                                     */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeButtonOff               = 0,
  kThemeButtonOn                = 1,
  kThemeButtonMixed             = 2,
  kThemeDisclosureRight         = 0,
  kThemeDisclosureDown          = 1,
  kThemeDisclosureLeft          = 2
};

typedef UInt16                          ThemeButtonValue;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Button adornment types                                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeAdornmentNone           = 0,
  kThemeAdornmentDefault        = (1 << 0), /* if set, draw default ornamentation ( for push button and generic well ) */
  kThemeAdornmentFocus          = (1 << 2), /* if set, draw focus */
  kThemeAdornmentRightToLeft    = (1 << 4), /* if set, draw right to left label */
  kThemeAdornmentDrawIndicatorOnly = (1 << 5), /* if set, don't draw or erase label ( radio, check, disclosure ) */
  kThemeAdornmentHeaderButtonLeftNeighborSelected = (1 << 6), /* if set, draw the left border of the button as selected ( list header button only ) */
  kThemeAdornmentHeaderButtonRightNeighborSelected = (1 << 7), /* if set, draw the right border of the button ( list header button only ) */
  kThemeAdornmentHeaderButtonSortUp = (1 << 8), /* if set, draw the sort indicator pointing upward ( list header button only ) */
  kThemeAdornmentHeaderMenuButton = (1 << 9), /* if set, draw as a header menu button ( list header button only ) */
  kThemeAdornmentHeaderButtonNoShadow = (1 << 10), /* if set, draw the non-shadow area of the button ( list header button only ) */
  kThemeAdornmentHeaderButtonShadowOnly = (1 << 11), /* if set, draw the only the shadow area of the button ( list header button only ) */
  kThemeAdornmentNoShadow       = kThemeAdornmentHeaderButtonNoShadow, /* old name */
  kThemeAdornmentShadowOnly     = kThemeAdornmentHeaderButtonShadowOnly, /* old name */
  kThemeAdornmentArrowLeftArrow = (1 << 6), /* If set, draw a left arrow on the arrow button */
  kThemeAdornmentArrowDownArrow = (1 << 7), /* If set, draw a down arrow on the arrow button */
  kThemeAdornmentArrowDoubleArrow = (1 << 8), /* If set, draw a double arrow on the arrow button */
  kThemeAdornmentArrowUpArrow   = (1 << 9) /* If set, draw a up arrow on the arrow button */
};

typedef UInt16                          ThemeButtonAdornment;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Button drawing info block                                                                */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ThemeButtonDrawInfo {
  ThemeDrawState      state;
  ThemeButtonValue    value;
  ThemeButtonAdornment  adornment;
};
typedef struct ThemeButtonDrawInfo      ThemeButtonDrawInfo;
typedef ThemeButtonDrawInfo *           ThemeButtonDrawInfoPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Sound Support                                                                            */
/*                                                                                          */
/*  X ALERT: Please note that none of the theme sound APIs currently function on X.         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Sound classes                                                                            */
/*                                                                                          */
/* You can use the constants below to set what sounds are active using the SetTheme API.    */
/* Use these with the kThemeSoundMask tag.                                                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeNoSounds                = 0,
  kThemeWindowSoundsMask        = (1 << 0),
  kThemeMenuSoundsMask          = (1 << 1),
  kThemeControlSoundsMask       = (1 << 2),
  kThemeFinderSoundsMask        = (1 << 3)
};


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Drag Sounds                                                                              */
/*                                                                                          */
/* Drag sounds are looped for the duration of the drag.                                     */
/*                                                                                          */
/* Call BeginThemeDragSound at the start of the drag.                                       */
/* Call EndThemeDragSound when the drag has finished.                                       */
/*                                                                                          */
/* Note that in order to maintain a consistent user experience, only one drag sound may     */
/* occur at a time.  The sound should be attached to a mouse action, start after the        */
/* mouse goes down and stop when the mouse is released.                                     */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeDragSoundNone           = 0,
  kThemeDragSoundMoveWindow     = 'wmov',
  kThemeDragSoundGrowWindow     = 'wgro',
  kThemeDragSoundMoveUtilWindow = 'umov',
  kThemeDragSoundGrowUtilWindow = 'ugro',
  kThemeDragSoundMoveDialog     = 'dmov',
  kThemeDragSoundMoveAlert      = 'amov',
  kThemeDragSoundMoveIcon       = 'imov',
  kThemeDragSoundSliderThumb    = 'slth',
  kThemeDragSoundSliderGhost    = 'slgh',
  kThemeDragSoundScrollBarThumb = 'sbth',
  kThemeDragSoundScrollBarGhost = 'sbgh',
  kThemeDragSoundScrollBarArrowDecreasing = 'sbad',
  kThemeDragSoundScrollBarArrowIncreasing = 'sbai',
  kThemeDragSoundDragging       = 'drag'
};

typedef OSType                          ThemeDragSoundKind;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* State-change sounds                                                      */
/*                                                                          */
/* State-change sounds are played asynchonously as a one-shot.              */
/*                                                                          */
/* Call PlayThemeSound to play the sound.  The sound will play              */
/* asynchronously until complete, then stop automatically.                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kThemeSoundNone               = 0,
  kThemeSoundMenuOpen           = 'mnuo', /* menu sounds */
  kThemeSoundMenuClose          = 'mnuc',
  kThemeSoundMenuItemHilite     = 'mnui',
  kThemeSoundMenuItemRelease    = 'mnus',
  kThemeSoundWindowClosePress   = 'wclp', /* window sounds */
  kThemeSoundWindowCloseEnter   = 'wcle',
  kThemeSoundWindowCloseExit    = 'wclx',
  kThemeSoundWindowCloseRelease = 'wclr',
  kThemeSoundWindowZoomPress    = 'wzmp',
  kThemeSoundWindowZoomEnter    = 'wzme',
  kThemeSoundWindowZoomExit     = 'wzmx',
  kThemeSoundWindowZoomRelease  = 'wzmr',
  kThemeSoundWindowCollapsePress = 'wcop',
  kThemeSoundWindowCollapseEnter = 'wcoe',
  kThemeSoundWindowCollapseExit = 'wcox',
  kThemeSoundWindowCollapseRelease = 'wcor',
  kThemeSoundWindowDragBoundary = 'wdbd',
  kThemeSoundUtilWinClosePress  = 'uclp', /* utility window sounds */
  kThemeSoundUtilWinCloseEnter  = 'ucle',
  kThemeSoundUtilWinCloseExit   = 'uclx',
  kThemeSoundUtilWinCloseRelease = 'uclr',
  kThemeSoundUtilWinZoomPress   = 'uzmp',
  kThemeSoundUtilWinZoomEnter   = 'uzme',
  kThemeSoundUtilWinZoomExit    = 'uzmx',
  kThemeSoundUtilWinZoomRelease = 'uzmr',
  kThemeSoundUtilWinCollapsePress = 'ucop',
  kThemeSoundUtilWinCollapseEnter = 'ucoe',
  kThemeSoundUtilWinCollapseExit = 'ucox',
  kThemeSoundUtilWinCollapseRelease = 'ucor',
  kThemeSoundUtilWinDragBoundary = 'udbd',
  kThemeSoundWindowOpen         = 'wopn', /* window close and zoom action */
  kThemeSoundWindowClose        = 'wcls',
  kThemeSoundWindowZoomIn       = 'wzmi',
  kThemeSoundWindowZoomOut      = 'wzmo',
  kThemeSoundWindowCollapseUp   = 'wcol',
  kThemeSoundWindowCollapseDown = 'wexp',
  kThemeSoundWindowActivate     = 'wact',
  kThemeSoundUtilWindowOpen     = 'uopn',
  kThemeSoundUtilWindowClose    = 'ucls',
  kThemeSoundUtilWindowZoomIn   = 'uzmi',
  kThemeSoundUtilWindowZoomOut  = 'uzmo',
  kThemeSoundUtilWindowCollapseUp = 'ucol',
  kThemeSoundUtilWindowCollapseDown = 'uexp',
  kThemeSoundUtilWindowActivate = 'uact',
  kThemeSoundDialogOpen         = 'dopn',
  kThemeSoundDialogClose        = 'dlgc',
  kThemeSoundAlertOpen          = 'aopn',
  kThemeSoundAlertClose         = 'altc',
  kThemeSoundPopupWindowOpen    = 'pwop',
  kThemeSoundPopupWindowClose   = 'pwcl',
  kThemeSoundButtonPress        = 'btnp', /* button */
  kThemeSoundButtonEnter        = 'btne',
  kThemeSoundButtonExit         = 'btnx',
  kThemeSoundButtonRelease      = 'btnr',
  kThemeSoundDefaultButtonPress = 'dbtp', /* default button */
  kThemeSoundDefaultButtonEnter = 'dbte',
  kThemeSoundDefaultButtonExit  = 'dbtx',
  kThemeSoundDefaultButtonRelease = 'dbtr',
  kThemeSoundCancelButtonPress  = 'cbtp', /* cancel button */
  kThemeSoundCancelButtonEnter  = 'cbte',
  kThemeSoundCancelButtonExit   = 'cbtx',
  kThemeSoundCancelButtonRelease = 'cbtr',
  kThemeSoundCheckboxPress      = 'chkp', /* checkboxes */
  kThemeSoundCheckboxEnter      = 'chke',
  kThemeSoundCheckboxExit       = 'chkx',
  kThemeSoundCheckboxRelease    = 'chkr',
  kThemeSoundRadioPress         = 'radp', /* radio buttons */
  kThemeSoundRadioEnter         = 'rade',
  kThemeSoundRadioExit          = 'radx',
  kThemeSoundRadioRelease       = 'radr',
  kThemeSoundScrollArrowPress   = 'sbap', /* scroll bars */
  kThemeSoundScrollArrowEnter   = 'sbae',
  kThemeSoundScrollArrowExit    = 'sbax',
  kThemeSoundScrollArrowRelease = 'sbar',
  kThemeSoundScrollEndOfTrack   = 'sbte',
  kThemeSoundScrollTrackPress   = 'sbtp',
  kThemeSoundSliderEndOfTrack   = 'slte', /* sliders */
  kThemeSoundSliderTrackPress   = 'sltp',
  kThemeSoundBalloonOpen        = 'blno', /* help balloons */
  kThemeSoundBalloonClose       = 'blnc',
  kThemeSoundBevelPress         = 'bevp', /* Bevel buttons */
  kThemeSoundBevelEnter         = 'beve',
  kThemeSoundBevelExit          = 'bevx',
  kThemeSoundBevelRelease       = 'bevr',
  kThemeSoundLittleArrowUpPress = 'laup', /* Little Arrows */
  kThemeSoundLittleArrowDnPress = 'ladp',
  kThemeSoundLittleArrowEnter   = 'lare',
  kThemeSoundLittleArrowExit    = 'larx',
  kThemeSoundLittleArrowUpRelease = 'laur',
  kThemeSoundLittleArrowDnRelease = 'ladr',
  kThemeSoundPopupPress         = 'popp', /* Popup Buttons */
  kThemeSoundPopupEnter         = 'pope',
  kThemeSoundPopupExit          = 'popx',
  kThemeSoundPopupRelease       = 'popr',
  kThemeSoundDisclosurePress    = 'dscp', /* Disclosure Buttons */
  kThemeSoundDisclosureEnter    = 'dsce',
  kThemeSoundDisclosureExit     = 'dscx',
  kThemeSoundDisclosureRelease  = 'dscr',
  kThemeSoundTabPressed         = 'tabp', /* Tabs */
  kThemeSoundTabEnter           = 'tabe',
  kThemeSoundTabExit            = 'tabx',
  kThemeSoundTabRelease         = 'tabr',
  kThemeSoundDragTargetHilite   = 'dthi', /* drag manager */
  kThemeSoundDragTargetUnhilite = 'dtuh',
  kThemeSoundDragTargetDrop     = 'dtdr',
  kThemeSoundEmptyTrash         = 'ftrs', /* finder */
  kThemeSoundSelectItem         = 'fsel',
  kThemeSoundNewItem            = 'fnew',
  kThemeSoundReceiveDrop        = 'fdrp',
  kThemeSoundCopyDone           = 'fcpd',
  kThemeSoundResolveAlias       = 'fral',
  kThemeSoundLaunchApp          = 'flap',
  kThemeSoundDiskInsert         = 'dski',
  kThemeSoundDiskEject          = 'dske',
  kThemeSoundFinderDragOnIcon   = 'fdon',
  kThemeSoundFinderDragOffIcon  = 'fdof'
};

typedef OSType                          ThemeSoundKind;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Window Metrics                                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  Window metrics are used by the Appearance manager to fill in the blanks necessary to    */
/*  draw windows. If a value is not appropriate for the type of window, be sure to fill in  */
/*  the slot in the structure with zero.    For the popupTabOffset parameter, you can pass a*/
/*  real value based on the left edge of the window. This value might be interpreted in a   */
/*  different manner when depending on the value of the popupTabPosition field. The values  */
/*  you can pass into popupTabPosition are:                                                 */
/*                                                                                          */
/*  kThemePopupTabNormalPosition                                                            */
/*      Starts the tab left edge at the position indicated by the popupTabOffset field.     */
/*                                                                                          */
/*  kThemePopupTabCenterOnWindow                                                            */
/*      tells us to ignore the offset field and instead simply center the width of the      */
/*      handle on the window.                                                               */
/*                                                                                          */
/*  kThemePopupTabCenterOnOffset                                                            */
/*      tells us to center the width of the handle around the value passed in offset.       */
/*                                                                                          */
/*  The Appearance Manager will try its best to accomodate the requested placement, but may */
/*  move the handle slightly to make it fit correctly.                                      */
/*                                                                                          */
enum {
  kThemePopupTabNormalPosition  = 0,
  kThemePopupTabCenterOnWindow  = 1,
  kThemePopupTabCenterOnOffset  = 2
};

struct ThemeWindowMetrics {
  UInt16              metricSize;             /* should be always be sizeof( ThemeWindowMetrics )*/
  SInt16              titleHeight;
  SInt16              titleWidth;
  SInt16              popupTabOffset;
  SInt16              popupTabWidth;
  UInt16              popupTabPosition;
};
typedef struct ThemeWindowMetrics       ThemeWindowMetrics;
typedef ThemeWindowMetrics *            ThemeWindowMetricsPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Theme Metrics                                                                            */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

/*
 *  Discussion:
 *    Theme metrics allow you to find out sizes of things in the
 *    current environment, such as how wide a scroll bar is, etc.
 */

  /*
   */
enum {
  kThemeMetricScrollBarWidth    = 0,

  /*
   */
  kThemeMetricSmallScrollBarWidth = 1,

  /*
   */
  kThemeMetricCheckBoxHeight    = 2,

  /*
   */
  kThemeMetricRadioButtonHeight = 3,

  /*
   */
  kThemeMetricEditTextWhitespace = 4,

  /*
   */
  kThemeMetricEditTextFrameOutset = 5,

  /*
   */
  kThemeMetricListBoxFrameOutset = 6,

  /*
   */
  kThemeMetricFocusRectOutset   = 7,

  /*
   */
  kThemeMetricImageWellThickness = 8,

  /*
   */
  kThemeMetricScrollBarOverlap  = 9,

  /*
   */
  kThemeMetricLargeTabHeight    = 10,

  /*
   */
  kThemeMetricLargeTabCapsWidth = 11,

  /*
   */
  kThemeMetricTabFrameOverlap   = 12,

  /*
   */
  kThemeMetricTabIndentOrStyle  = 13,

  /*
   */
  kThemeMetricTabOverlap        = 14,

  /*
   */
  kThemeMetricSmallTabHeight    = 15,

  /*
   */
  kThemeMetricSmallTabCapsWidth = 16,

  /*
   */
  kThemeMetricDisclosureButtonHeight = 17,

  /*
   */
  kThemeMetricRoundButtonSize   = 18,

  /*
   */
  kThemeMetricPushButtonHeight  = 19,

  /*
   */
  kThemeMetricListHeaderHeight  = 20,

  /*
   */
  kThemeMetricSmallCheckBoxHeight = 21,

  /*
   */
  kThemeMetricDisclosureButtonWidth = 22,

  /*
   */
  kThemeMetricSmallDisclosureButtonHeight = 23,

  /*
   */
  kThemeMetricSmallDisclosureButtonWidth = 24,

  /*
   */
  kThemeMetricDisclosureTriangleHeight = 25,

  /*
   */
  kThemeMetricDisclosureTriangleWidth = 26,

  /*
   */
  kThemeMetricLittleArrowsHeight = 27,

  /*
   */
  kThemeMetricLittleArrowsWidth = 28,

  /*
   */
  kThemeMetricPaneSplitterHeight = 29,

  /*
   */
  kThemeMetricPopupButtonHeight = 30,

  /*
   */
  kThemeMetricSmallPopupButtonHeight = 31,

  /*
   */
  kThemeMetricLargeProgressBarThickness = 32,

  /*
   */
  kThemeMetricPullDownHeight    = 33,

  /*
   */
  kThemeMetricSmallPullDownHeight = 34,

  /*
   */
  kThemeMetricSmallPushButtonHeight = 35,

  /*
   */
  kThemeMetricSmallRadioButtonHeight = 36,

  /*
   */
  kThemeMetricRelevanceIndicatorHeight = 37,

  /*
   */
  kThemeMetricResizeControlHeight = 38,

  /*
   */
  kThemeMetricSmallResizeControlHeight = 39,

  /*
   */
  kThemeMetricLargeRoundButtonSize = 40,

  /*
   */
  kThemeMetricHSliderHeight     = 41,

  /*
   */
  kThemeMetricHSliderTickHeight = 42,

  /*
   */
  kThemeMetricSmallHSliderHeight = 43,

  /*
   */
  kThemeMetricSmallHSliderTickHeight = 44,

  /*
   */
  kThemeMetricVSliderWidth      = 45,

  /*
   */
  kThemeMetricVSliderTickWidth  = 46,

  /*
   */
  kThemeMetricSmallVSliderWidth = 47,

  /*
   */
  kThemeMetricSmallVSliderTickWidth = 48,

  /*
   */
  kThemeMetricTitleBarControlsHeight = 49,

  /*
   */
  kThemeMetricCheckBoxWidth     = 50,

  /*
   */
  kThemeMetricSmallCheckBoxWidth = 51,

  /*
   */
  kThemeMetricRadioButtonWidth  = 52,

  /*
   */
  kThemeMetricSmallRadioButtonWidth = 53,

  /*
   */
  kThemeMetricSmallHSliderMinThumbWidth = 54,

  /*
   */
  kThemeMetricSmallVSliderMinThumbHeight = 55,

  /*
   */
  kThemeMetricSmallHSliderTickOffset = 56,

  /*
   */
  kThemeMetricSmallVSliderTickOffset = 57,

  /*
   */
  kThemeMetricNormalProgressBarThickness = 58,

  /*
   */
  kThemeMetricProgressBarShadowOutset = 59,

  /*
   */
  kThemeMetricSmallProgressBarShadowOutset = 60,

  /*
   */
  kThemeMetricPrimaryGroupBoxContentInset = 61,

  /*
   */
  kThemeMetricSecondaryGroupBoxContentInset = 62,

  /*
   * Width allocated to draw the mark character in a menu. Width
   * allocated for the mark character in a menu item when the menu has
   * kMenuAttrExcludesMarkColumn. Indent into the interior of the mark
   * column at which the mark character is drawn. Whitespace at the
   * leading edge of menu item text. Whitespace at the trailing edge of
   * menu item text. Width per indent level (set by SetMenuItemIndent)
   * of a menu item. Whitespace at the trailing edge of a menu icon (if
   * the item also has text).
   */
  kThemeMetricMenuMarkColumnWidth = 63,
  kThemeMetricMenuExcludedMarkColumnWidth = 64,
  kThemeMetricMenuMarkIndent    = 65,
  kThemeMetricMenuTextLeadingEdgeMargin = 66,
  kThemeMetricMenuTextTrailingEdgeMargin = 67,
  kThemeMetricMenuIndentWidth   = 68,
  kThemeMetricMenuIconTrailingEdgeMargin = 69
};

typedef UInt32                          ThemeMetric;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Drawing State                                                                            */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
typedef struct OpaqueThemeDrawingState*  ThemeDrawingState;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Callback procs                                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
typedef CALLBACK_API( void , ThemeTabTitleDrawProcPtr )(const Rect *bounds, ThemeTabStyle style, ThemeTabDirection direction, SInt16 depth, Boolean isColorDev, UInt32 userData);
typedef CALLBACK_API( void , ThemeEraseProcPtr )(const Rect *bounds, UInt32 eraseData, SInt16 depth, Boolean isColorDev);
typedef CALLBACK_API( void , ThemeButtonDrawProcPtr )(const Rect *bounds, ThemeButtonKind kind, const ThemeButtonDrawInfo *info, UInt32 userData, SInt16 depth, Boolean isColorDev);
typedef CALLBACK_API( void , WindowTitleDrawingProcPtr )(const Rect *bounds, SInt16 depth, Boolean colorDevice, UInt32 userData);
typedef CALLBACK_API( Boolean , ThemeIteratorProcPtr )(ConstStr255Param inFileName, SInt16 resID, Collection inThemeSettings, void *inUserData);
typedef STACK_UPP_TYPE(ThemeTabTitleDrawProcPtr)                ThemeTabTitleDrawUPP;
typedef STACK_UPP_TYPE(ThemeEraseProcPtr)                       ThemeEraseUPP;
typedef STACK_UPP_TYPE(ThemeButtonDrawProcPtr)                  ThemeButtonDrawUPP;
typedef STACK_UPP_TYPE(WindowTitleDrawingProcPtr)               WindowTitleDrawingUPP;
typedef STACK_UPP_TYPE(ThemeIteratorProcPtr)                    ThemeIteratorUPP;
/*
 *  NewThemeTabTitleDrawUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThemeTabTitleDrawUPP
NewThemeTabTitleDrawUPP(ThemeTabTitleDrawProcPtr userRoutine);

/*
 *  NewThemeEraseUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThemeEraseUPP
NewThemeEraseUPP(ThemeEraseProcPtr userRoutine);

/*
 *  NewThemeButtonDrawUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThemeButtonDrawUPP
NewThemeButtonDrawUPP(ThemeButtonDrawProcPtr userRoutine);

/*
 *  NewWindowTitleDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern WindowTitleDrawingUPP
NewWindowTitleDrawingUPP(WindowTitleDrawingProcPtr userRoutine);

/*
 *  NewThemeIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ThemeIteratorUPP
NewThemeIteratorUPP(ThemeIteratorProcPtr userRoutine);

/*
 *  DisposeThemeTabTitleDrawUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeThemeTabTitleDrawUPP(ThemeTabTitleDrawUPP userUPP);

/*
 *  DisposeThemeEraseUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeThemeEraseUPP(ThemeEraseUPP userUPP);

/*
 *  DisposeThemeButtonDrawUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeThemeButtonDrawUPP(ThemeButtonDrawUPP userUPP);

/*
 *  DisposeWindowTitleDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeWindowTitleDrawingUPP(WindowTitleDrawingUPP userUPP);

/*
 *  DisposeThemeIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeThemeIteratorUPP(ThemeIteratorUPP userUPP);

/*
 *  InvokeThemeTabTitleDrawUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeThemeTabTitleDrawUPP(
  const Rect *          bounds,
  ThemeTabStyle         style,
  ThemeTabDirection     direction,
  SInt16                depth,
  Boolean               isColorDev,
  UInt32                userData,
  ThemeTabTitleDrawUPP  userUPP);

/*
 *  InvokeThemeEraseUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeThemeEraseUPP(
  const Rect *   bounds,
  UInt32         eraseData,
  SInt16         depth,
  Boolean        isColorDev,
  ThemeEraseUPP  userUPP);

/*
 *  InvokeThemeButtonDrawUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeThemeButtonDrawUPP(
  const Rect *                 bounds,
  ThemeButtonKind              kind,
  const ThemeButtonDrawInfo *  info,
  UInt32                       userData,
  SInt16                       depth,
  Boolean                      isColorDev,
  ThemeButtonDrawUPP           userUPP);

/*
 *  InvokeWindowTitleDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeWindowTitleDrawingUPP(
  const Rect *           bounds,
  SInt16                 depth,
  Boolean                colorDevice,
  UInt32                 userData,
  WindowTitleDrawingUPP  userUPP);

/*
 *  InvokeThemeIteratorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeThemeIteratorUPP(
  ConstStr255Param  inFileName,
  SInt16            resID,
  Collection        inThemeSettings,
  void *            inUserData,
  ThemeIteratorUPP  userUPP);

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Menu Drawing callbacks                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
typedef CALLBACK_API( void , MenuTitleDrawingProcPtr )(const Rect *inBounds, SInt16 inDepth, Boolean inIsColorDevice, SInt32 inUserData);
typedef CALLBACK_API( void , MenuItemDrawingProcPtr )(const Rect *inBounds, SInt16 inDepth, Boolean inIsColorDevice, SInt32 inUserData);
typedef STACK_UPP_TYPE(MenuTitleDrawingProcPtr)                 MenuTitleDrawingUPP;
typedef STACK_UPP_TYPE(MenuItemDrawingProcPtr)                  MenuItemDrawingUPP;
/*
 *  NewMenuTitleDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MenuTitleDrawingUPP
NewMenuTitleDrawingUPP(MenuTitleDrawingProcPtr userRoutine);

/*
 *  NewMenuItemDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MenuItemDrawingUPP
NewMenuItemDrawingUPP(MenuItemDrawingProcPtr userRoutine);

/*
 *  DisposeMenuTitleDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMenuTitleDrawingUPP(MenuTitleDrawingUPP userUPP);

/*
 *  DisposeMenuItemDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMenuItemDrawingUPP(MenuItemDrawingUPP userUPP);

/*
 *  InvokeMenuTitleDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeMenuTitleDrawingUPP(
  const Rect *         inBounds,
  SInt16               inDepth,
  Boolean              inIsColorDevice,
  SInt32               inUserData,
  MenuTitleDrawingUPP  userUPP);

/*
 *  InvokeMenuItemDrawingUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeMenuItemDrawingUPP(
  const Rect *        inBounds,
  SInt16              inDepth,
  Boolean             inIsColorDevice,
  SInt32              inUserData,
  MenuItemDrawingUPP  userUPP);

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  Appearance Manager APIs                                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Registering Appearance-Savvy Applications */
/*
 *  RegisterAppearanceClient()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
RegisterAppearanceClient(void);


/*
 *  UnregisterAppearanceClient()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
UnregisterAppearanceClient(void);


/*
 *  IsAppearanceClient()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern Boolean 
IsAppearanceClient(const ProcessSerialNumber * process);


/*****************************************************************************
    NOTES ON THEME BRUSHES
    Theme brushes can be either colors or patterns, depending on the theme.
    Because of this, you should be prepared to handle the case where a brush
    is a pattern and save and restore the pnPixPat and bkPixPat fields of
    your GrafPorts when saving the fore and back colors. Also, since patterns
    in bkPixPat override the background color of the window, you should use
    BackPat to set your background pattern to a normal white pattern. This
    will ensure that you can use RGBBackColor to set your back color to white,
    call EraseRect and get the expected results.
*****************************************************************************/

/*
 *  SetThemePen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
SetThemePen(
  ThemeBrush   inBrush,
  SInt16       inDepth,
  Boolean      inIsColorDevice);


/*
 *  SetThemeBackground()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
SetThemeBackground(
  ThemeBrush   inBrush,
  SInt16       inDepth,
  Boolean      inIsColorDevice);


/*
 *  SetThemeTextColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
SetThemeTextColor(
  ThemeTextColor   inColor,
  SInt16           inDepth,
  Boolean          inIsColorDevice);


/*
 *  SetThemeWindowBackground()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
SetThemeWindowBackground(
  WindowRef    inWindow,
  ThemeBrush   inBrush,
  Boolean      inUpdate);


/* Window Placards, Headers and Frames */
/*
 *  DrawThemeWindowHeader()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeWindowHeader(
  const Rect *     inRect,
  ThemeDrawState   inState);


/*
 *  DrawThemeWindowListViewHeader()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeWindowListViewHeader(
  const Rect *     inRect,
  ThemeDrawState   inState);


/*
 *  DrawThemePlacard()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemePlacard(
  const Rect *     inRect,
  ThemeDrawState   inState);


/*
 *  DrawThemeEditTextFrame()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeEditTextFrame(
  const Rect *     inRect,
  ThemeDrawState   inState);


/*
 *  DrawThemeListBoxFrame()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeListBoxFrame(
  const Rect *     inRect,
  ThemeDrawState   inState);


/* Keyboard Focus Drawing */
/*
 *  DrawThemeFocusRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeFocusRect(
  const Rect *  inRect,
  Boolean       inHasFocus);


/* Dialog Group Boxes and Separators */
/*
 *  DrawThemePrimaryGroup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemePrimaryGroup(
  const Rect *     inRect,
  ThemeDrawState   inState);


/*
 *  DrawThemeSecondaryGroup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeSecondaryGroup(
  const Rect *     inRect,
  ThemeDrawState   inState);


/*
 *  DrawThemeSeparator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeSeparator(
  const Rect *     inRect,
  ThemeDrawState   inState);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ BEGIN APPEARANCE 1.0.1 ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* The following Appearance Manager APIs are only available */
/* in Appearance 1.0.1 or later                             */
/*
 *  DrawThemeModelessDialogFrame()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeModelessDialogFrame(
  const Rect *     inRect,
  ThemeDrawState   inState);


/*
 *  DrawThemeGenericWell()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeGenericWell(
  const Rect *     inRect,
  ThemeDrawState   inState,
  Boolean          inFillCenter);


/*
 *  DrawThemeFocusRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeFocusRegion(
  RgnHandle   inRegion,
  Boolean     inHasFocus);


/*
 *  IsThemeInColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern Boolean 
IsThemeInColor(
  SInt16    inDepth,
  Boolean   inIsColorDevice);


/* IMPORTANT: GetThemeAccentColors will only work in the platinum theme. Any other theme will */
/* most likely return an error */
/*
 *  GetThemeAccentColors()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
GetThemeAccentColors(CTabHandle * outColors);


/*
 *  DrawThemeMenuBarBackground()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeMenuBarBackground(
  const Rect *        inBounds,
  ThemeMenuBarState   inState,
  UInt32              inAttributes);


/*
 *  DrawThemeMenuTitle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeMenuTitle(
  const Rect *          inMenuBarRect,
  const Rect *          inTitleRect,
  ThemeMenuState        inState,
  UInt32                inAttributes,
  MenuTitleDrawingUPP   inTitleProc,         /* can be NULL */
  UInt32                inTitleData);



/*
 *  GetThemeMenuBarHeight()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
GetThemeMenuBarHeight(SInt16 * outHeight);


/*
 *  DrawThemeMenuBackground()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeMenuBackground(
  const Rect *    inMenuRect,
  ThemeMenuType   inMenuType);


/*
 *  GetThemeMenuBackgroundRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
GetThemeMenuBackgroundRegion(
  const Rect *    inMenuRect,
  ThemeMenuType   menuType,
  RgnHandle       region);


/*
 *  DrawThemeMenuItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeMenuItem(
  const Rect *         inMenuRect,
  const Rect *         inItemRect,
  SInt16               inVirtualMenuTop,
  SInt16               inVirtualMenuBottom,
  ThemeMenuState       inState,
  ThemeMenuItemType    inItemType,
  MenuItemDrawingUPP   inDrawProc,                /* can be NULL */
  UInt32               inUserData);


/*
 *  DrawThemeMenuSeparator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
DrawThemeMenuSeparator(const Rect * inItemRect);


/*
 *  GetThemeMenuSeparatorHeight()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
GetThemeMenuSeparatorHeight(SInt16 * outHeight);


/*
 *  GetThemeMenuItemExtra()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
GetThemeMenuItemExtra(
  ThemeMenuItemType   inItemType,
  SInt16 *            outHeight,
  SInt16 *            outWidth);


/*
 *  GetThemeMenuTitleExtra()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSStatus 
GetThemeMenuTitleExtra(
  SInt16 *  outWidth,
  Boolean   inIsSquished);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ BEGIN APPEARANCE 1.1 ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ THEME SWITCHING ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*                                                                                                  */
/*  X ALERT: Please note that Get/SetTheme are severely neutered under Mac OS X at present.         */
/*           See the note above regarding what collection tags are supported under X.               */

/*
 *  GetTheme()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetTheme(Collection ioCollection);


/*
 *  SetTheme()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
SetTheme(Collection ioCollection);


/*
 *  IterateThemes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
IterateThemes(
  ThemeIteratorUPP   inProc,
  void *             inUserData);      /* can be NULL */


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ TABS ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  DrawThemeTabPane()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeTabPane(
  const Rect *     inRect,
  ThemeDrawState   inState);


/*
 *  DrawThemeTab()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeTab(
  const Rect *           inRect,
  ThemeTabStyle          inStyle,
  ThemeTabDirection      inDirection,
  ThemeTabTitleDrawUPP   labelProc,         /* can be NULL */
  UInt32                 userData);


/*
 *  GetThemeTabRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeTabRegion(
  const Rect *        inRect,
  ThemeTabStyle       inStyle,
  ThemeTabDirection   inDirection,
  RgnHandle           ioRgn);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ CURSORS ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  SetThemeCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
SetThemeCursor(ThemeCursor inCursor);


/*
 *  SetAnimatedThemeCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
SetAnimatedThemeCursor(
  ThemeCursor   inCursor,
  UInt32        inAnimationStep);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ CONTROL STYLE SETTINGS ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  GetThemeScrollBarThumbStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeScrollBarThumbStyle(ThemeScrollBarThumbStyle * outStyle);


/*
 *  GetThemeScrollBarArrowStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeScrollBarArrowStyle(ThemeScrollBarArrowStyle * outStyle);


/*
 *  GetThemeCheckBoxStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeCheckBoxStyle(ThemeCheckBoxStyle * outStyle);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ FONTS/TEXT ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  UseThemeFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
UseThemeFont(
  ThemeFontID   inFontID,
  ScriptCode    inScript);


/*
 *  GetThemeFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeFont(
  ThemeFontID   inFontID,
  ScriptCode    inScript,
  Str255        outFontName,       /* can be NULL */
  SInt16 *      outFontSize,
  Style *       outStyle);


/*
 *  DrawThemeTextBox()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DrawThemeTextBox(
  CFStringRef      inString,
  ThemeFontID      inFontID,
  ThemeDrawState   inState,
  Boolean          inWrapToWidth,
  const Rect *     inBoundingBox,
  SInt16           inJust,
  void *           inContext);


/*
 *  TruncateThemeText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TruncateThemeText(
  CFMutableStringRef   inString,
  ThemeFontID          inFontID,
  ThemeDrawState       inState,
  SInt16               inPixelWidthLimit,
  TruncCode            inTruncWhere,
  Boolean *            outTruncated);           /* can be NULL */


/*
 *  GetThemeTextDimensions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetThemeTextDimensions(
  CFStringRef      inString,
  ThemeFontID      inFontID,
  ThemeDrawState   inState,
  Boolean          inWrapToWidth,
  Point *          ioBounds,
  SInt16 *         outBaseline);


/*
 *  GetThemeTextShadowOutset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetThemeTextShadowOutset(
  ThemeFontID      inFontID,
  ThemeDrawState   inState,
  Rect *           outOutset);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ TRACKS ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  DrawThemeTrack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeTrack(
  const ThemeTrackDrawInfo *  drawInfo,
  RgnHandle                   rgnGhost,        /* can be NULL */
  ThemeEraseUPP               eraseProc,       /* can be NULL */
  UInt32                      eraseData);


/*
 *  HitTestThemeTrack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern Boolean 
HitTestThemeTrack(
  const ThemeTrackDrawInfo *  drawInfo,
  Point                       mousePoint,
  ControlPartCode *           partHit);


/*
 *  GetThemeTrackBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeTrackBounds(
  const ThemeTrackDrawInfo *  drawInfo,
  Rect *                      bounds);


/*
 *  GetThemeTrackThumbRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeTrackThumbRgn(
  const ThemeTrackDrawInfo *  drawInfo,
  RgnHandle                   thumbRgn);


/*
 *  GetThemeTrackDragRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeTrackDragRect(
  const ThemeTrackDrawInfo *  drawInfo,
  Rect *                      dragRect);


/*
 *  DrawThemeTrackTickMarks()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeTrackTickMarks(
  const ThemeTrackDrawInfo *  drawInfo,
  ItemCount                   numTicks,
  ThemeEraseUPP               eraseProc,       /* can be NULL */
  UInt32                      eraseData);


/*
 *  GetThemeTrackThumbPositionFromOffset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeTrackThumbPositionFromOffset(
  const ThemeTrackDrawInfo *  drawInfo,
  Point                       thumbOffset,
  SInt32 *                    relativePosition);


/*
 *  GetThemeTrackThumbPositionFromRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeTrackThumbPositionFromRegion(
  const ThemeTrackDrawInfo *  drawInfo,
  RgnHandle                   thumbRgn,
  SInt32 *                    relativePosition);


/*
 *  GetThemeTrackLiveValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeTrackLiveValue(
  const ThemeTrackDrawInfo *  drawInfo,
  SInt32                      relativePosition,
  SInt32 *                    value);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ SCROLLBAR ARROWS ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  DrawThemeScrollBarArrows()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeScrollBarArrows(
  const Rect *            bounds,
  ThemeTrackEnableState   enableState,
  ThemeTrackPressState    pressState,
  Boolean                 isHoriz,
  Rect *                  trackBounds);


/*
 *  GetThemeScrollBarTrackRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeScrollBarTrackRect(
  const Rect *            bounds,
  ThemeTrackEnableState   enableState,
  ThemeTrackPressState    pressState,
  Boolean                 isHoriz,
  Rect *                  trackBounds);


/*
 *  HitTestThemeScrollBarArrows()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern Boolean 
HitTestThemeScrollBarArrows(
  const Rect *            scrollBarBounds,
  ThemeTrackEnableState   enableState,
  ThemeTrackPressState    pressState,
  Boolean                 isHoriz,
  Point                   ptHit,
  Rect *                  trackBounds,
  ControlPartCode *       partcode);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ WINDOWS ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  GetThemeWindowRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeWindowRegion(
  ThemeWindowType             flavor,
  const Rect *                contRect,
  ThemeDrawState              state,
  const ThemeWindowMetrics *  metrics,
  ThemeWindowAttributes       attributes,
  WindowRegionCode            winRegion,
  RgnHandle                   rgn);


/*
 *  DrawThemeWindowFrame()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeWindowFrame(
  ThemeWindowType             flavor,
  const Rect *                contRect,
  ThemeDrawState              state,
  const ThemeWindowMetrics *  metrics,
  ThemeWindowAttributes       attributes,
  WindowTitleDrawingUPP       titleProc,        /* can be NULL */
  UInt32                      titleData);


/*
 *  DrawThemeTitleBarWidget()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeTitleBarWidget(
  ThemeWindowType             flavor,
  const Rect *                contRect,
  ThemeDrawState              state,
  const ThemeWindowMetrics *  metrics,
  ThemeWindowAttributes       attributes,
  ThemeTitleBarWidget         widget);


/*
 *  GetThemeWindowRegionHit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern Boolean 
GetThemeWindowRegionHit(
  ThemeWindowType             flavor,
  const Rect *                inContRect,
  ThemeDrawState              state,
  const ThemeWindowMetrics *  metrics,
  ThemeWindowAttributes       inAttributes,
  Point                       inPoint,
  WindowRegionCode *          outRegionHit);


/*
 *  DrawThemeScrollBarDelimiters()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeScrollBarDelimiters(
  ThemeWindowType         flavor,
  const Rect *            inContRect,
  ThemeDrawState          state,
  ThemeWindowAttributes   attributes);



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ BUTTONS ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  DrawThemeButton()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeButton(
  const Rect *                 inBounds,
  ThemeButtonKind              inKind,
  const ThemeButtonDrawInfo *  inNewInfo,
  const ThemeButtonDrawInfo *  inPrevInfo,        /* can be NULL */
  ThemeEraseUPP                inEraseProc,       /* can be NULL */
  ThemeButtonDrawUPP           inLabelProc,       /* can be NULL */
  UInt32                       inUserData);


/*
 *  GetThemeButtonRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeButtonRegion(
  const Rect *                 inBounds,
  ThemeButtonKind              inKind,
  const ThemeButtonDrawInfo *  inNewInfo,
  RgnHandle                    outRegion);


/*
 *  GetThemeButtonContentBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeButtonContentBounds(
  const Rect *                 inBounds,
  ThemeButtonKind              inKind,
  const ThemeButtonDrawInfo *  inDrawInfo,
  Rect *                       outBounds);


/*
 *  GetThemeButtonBackgroundBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeButtonBackgroundBounds(
  const Rect *                 inBounds,
  ThemeButtonKind              inKind,
  const ThemeButtonDrawInfo *  inDrawInfo,
  Rect *                       outBounds);



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ INTERFACE SOUNDS ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*                                                                                                  */
/*  X ALERT: Please note that the sound APIs do not work on Mac OS X at present.                    */
/*
 *  PlayThemeSound()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
PlayThemeSound(ThemeSoundKind kind);


/*
 *  BeginThemeDragSound()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
BeginThemeDragSound(ThemeDragSoundKind kind);


/*
 *  EndThemeDragSound()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
EndThemeDragSound(void);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ PRIMITIVES ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  DrawThemeTickMark()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeTickMark(
  const Rect *     bounds,
  ThemeDrawState   state);


/*
 *  DrawThemeChasingArrows()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeChasingArrows(
  const Rect *     bounds,
  UInt32           index,
  ThemeDrawState   state,
  ThemeEraseUPP    eraseProc,       /* can be NULL */
  UInt32           eraseData);


/*
 *  DrawThemePopupArrow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemePopupArrow(
  const Rect *            bounds,
  ThemeArrowOrientation   orientation,
  ThemePopupArrowSize     size,
  ThemeDrawState          state,
  ThemeEraseUPP           eraseProc,         /* can be NULL */
  UInt32                  eraseData);


/*
 *  DrawThemeStandaloneGrowBox()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeStandaloneGrowBox(
  Point                origin,
  ThemeGrowDirection   growDirection,
  Boolean              isSmall,
  ThemeDrawState       state);


/*
 *  DrawThemeStandaloneNoGrowBox()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DrawThemeStandaloneNoGrowBox(
  Point                origin,
  ThemeGrowDirection   growDirection,
  Boolean              isSmall,
  ThemeDrawState       state);


/*
 *  GetThemeStandaloneGrowBoxBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeStandaloneGrowBoxBounds(
  Point                origin,
  ThemeGrowDirection   growDirection,
  Boolean              isSmall,
  Rect *               bounds);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ DRAWING STATE ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* The following routines help you save and restore the drawing state in a theme-savvy manner. With */
/* these weapons in your arsenal, there is no grafport you cannot tame. Use ThemeGetDrawingState to */
/* get the current drawing settings for the current port. It will return an opaque object for you   */
/* to pass into SetThemeDrawingState later on. When you are finished with the state, call the       */
/* DisposeThemeDrawingState routine. You can alternatively pass true into the inDisposeNow          */
/* parameter of the SetThemeDrawingState routine.  You can use this routine to copy the drawing     */
/* state from one port to another as well.                                                          */
/*                                                                                                  */
/* As of this writing (Mac OS 9.1 and Mac OS X), Get/SetThemeDrawingState will save and restore     */
/* this data in the port:                                                                           */
/*                                                                                                  */
/*      pen size                                                                                    */
/*      pen location                                                                                */
/*      pen mode                                                                                    */
/*      pen Pattern and PixPat                                                                      */
/*      background Pattern and PixPat                                                               */
/*      RGB foreground and background colors                                                        */
/*      text mode                                                                                   */
/*      pattern origin                                                                              */
/*                                                                                                  */
/* Get/SetThemeDrawingState may save and restore additional port state in the future, but you can   */
/* rely on them to always save at least this port state.                                            */
/*
 *  NormalizeThemeDrawingState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
NormalizeThemeDrawingState(void);


/*
 *  GetThemeDrawingState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeDrawingState(ThemeDrawingState * outState);


/*
 *  SetThemeDrawingState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
SetThemeDrawingState(
  ThemeDrawingState   inState,
  Boolean             inDisposeNow);


/*
 *  DisposeThemeDrawingState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
DisposeThemeDrawingState(ThemeDrawingState inState);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ MISCELLANEOUS ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* ApplyThemeBackground is used to set up the background for embedded controls  */
/* It is normally called by controls that are embedders. The standard controls  */
/* call this API to ensure a correct background for the current theme. You pass */
/* in the same rectangle you would if you were calling the drawing primitive.   */
/*
 *  ApplyThemeBackground()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
ApplyThemeBackground(
  ThemeBackgroundKind   inKind,
  const Rect *          bounds,
  ThemeDrawState        inState,
  SInt16                inDepth,
  Boolean               inColorDev);


/*
 *  SetThemeTextColorForWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
SetThemeTextColorForWindow(
  WindowRef   window,
  Boolean     isActive,
  SInt16      depth,
  Boolean     isColorDev);


/*
 *  IsValidAppearanceFileType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern Boolean 
IsValidAppearanceFileType(OSType fileType);


/*
 *  GetThemeBrushAsColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeBrushAsColor(
  ThemeBrush   inBrush,
  SInt16       inDepth,
  Boolean      inColorDev,
  RGBColor *   outColor);


/*
 *  GetThemeTextColor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.1 and later
 */
extern OSStatus 
GetThemeTextColor(
  ThemeTextColor   inColor,
  SInt16           inDepth,
  Boolean          inColorDev,
  RGBColor *       outColor);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ BEGIN CARBON ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  GetThemeMetric()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetThemeMetric(
  ThemeMetric   inMetric,
  SInt32 *      outMetric);


/*
 *  GetTextAndEncodingFromCFString()
 *  
 *  Summary:
 *    Converts the contents of a CFString to the one- or two-byte
 *    encoding that most accurately represents the original Unicode
 *    characters in the string.
 *  
 *  Discussion:
 *    Because the Macintosh toolbox has had, until Carbon, little
 *    support for Unicode, you may often find that your applications
 *    need to translate a CFString (containing Unicode characters) back
 *    to a one- or two-byte encoding of the string in order to draw,
 *    measure, or otherwise use the text in the string.
 *    GetTextAndEncodingFromCFString is a utility that may be helpful
 *    to do this, in some circumstances. The Carbon toolbox uses this
 *    API itself when translating CFStrings to Pascal strings.
 *    GetTextAndEncodingFromCFString attempts to convert the Unicode
 *    characters in the string to the closest non-Unicode
 *    representation of the string. For example, a string containing
 *    only Unicode characters that are present in the MacRoman one-byte
 *    encoding will be translated to MacRoman, and
 *    kTextEncodingMacRoman will be returned as the encoding of the
 *    text. A string containing Unicode characters that are present in
 *    the MacJapanese two-byte encoding will be translated to
 *    MacJapanese (Shift-JIS), and kTextEncodingMacJapanese will be
 *    returned as the encoding of the text.
 *    GetTextAndEncodingFromCFString is designed to be used for simple
 *    strings which contain only text from a single language. It is not
 *    designed to translate strings with multiple runs of text from
 *    different languages, and will only return the first run of such a
 *    string; for example, if you pass it a string containing a run of
 *    Roman characters followed by a run of Japanese characters, it
 *    will only return the Roman characters in the output buffer. For
 *    more complex text translation, you should call the Unicode
 *    converter directly (see ConvertFromUnicodeToTextRun, which
 *    GetTextAndEncodingFromCFString uses internally).
 *  
 *  Parameters:
 *    
 *    inString:
 *      The string to convert.
 *    
 *    outText:
 *      The output buffer in which to place the converted text.
 *    
 *    inTextMaxLength:
 *      The length in bytes of the input buffer.
 *    
 *    outTextLength:
 *      On exit, contains the length in bytes of the text that was
 *      placed into the output buffer.
 *    
 *    outEncoding:
 *      On exit, contains the encoding of the text that was placed into
 *      the output buffer.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.2.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetTextAndEncodingFromCFString(
  CFStringRef     inString,
  BytePtr         outText,
  ByteCount       inTextMaxLength,
  ByteCount *     outTextLength,
  TextEncoding *  outEncoding);          /* can be NULL */



/* Mac OS X.x/CarbonLib 1.4 and Later*/
/*
 *  CopyThemeIdentifier()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CopyThemeIdentifier(CFStringRef * outIdentifier);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Obsolete symbolic names                                                                          */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Obsolete error codes - use the new ones, s'il vous plait / kudasai */
enum {
  appearanceBadBrushIndexErr    = themeInvalidBrushErr, /* pattern index invalid */
  appearanceProcessRegisteredErr = themeProcessRegisteredErr,
  appearanceProcessNotRegisteredErr = themeProcessNotRegisteredErr,
  appearanceBadTextColorIndexErr = themeBadTextColorErr,
  appearanceThemeHasNoAccents   = themeHasNoAccentsErr,
  appearanceBadCursorIndexErr   = themeBadCursorIndexErr
};

enum {
  kThemeActiveDialogBackgroundBrush = kThemeBrushDialogBackgroundActive,
  kThemeInactiveDialogBackgroundBrush = kThemeBrushDialogBackgroundInactive,
  kThemeActiveAlertBackgroundBrush = kThemeBrushAlertBackgroundActive,
  kThemeInactiveAlertBackgroundBrush = kThemeBrushAlertBackgroundInactive,
  kThemeActiveModelessDialogBackgroundBrush = kThemeBrushModelessDialogBackgroundActive,
  kThemeInactiveModelessDialogBackgroundBrush = kThemeBrushModelessDialogBackgroundInactive,
  kThemeActiveUtilityWindowBackgroundBrush = kThemeBrushUtilityWindowBackgroundActive,
  kThemeInactiveUtilityWindowBackgroundBrush = kThemeBrushUtilityWindowBackgroundInactive,
  kThemeListViewSortColumnBackgroundBrush = kThemeBrushListViewSortColumnBackground,
  kThemeListViewBackgroundBrush = kThemeBrushListViewBackground,
  kThemeIconLabelBackgroundBrush = kThemeBrushIconLabelBackground,
  kThemeListViewSeparatorBrush  = kThemeBrushListViewSeparator,
  kThemeChasingArrowsBrush      = kThemeBrushChasingArrows,
  kThemeDragHiliteBrush         = kThemeBrushDragHilite,
  kThemeDocumentWindowBackgroundBrush = kThemeBrushDocumentWindowBackground,
  kThemeFinderWindowBackgroundBrush = kThemeBrushFinderWindowBackground
};

enum {
  kThemeActiveScrollBarDelimiterBrush = kThemeBrushScrollBarDelimiterActive,
  kThemeInactiveScrollBarDelimiterBrush = kThemeBrushScrollBarDelimiterInactive,
  kThemeFocusHighlightBrush     = kThemeBrushFocusHighlight,
  kThemeActivePopupArrowBrush   = kThemeBrushPopupArrowActive,
  kThemePressedPopupArrowBrush  = kThemeBrushPopupArrowPressed,
  kThemeInactivePopupArrowBrush = kThemeBrushPopupArrowInactive,
  kThemeAppleGuideCoachmarkBrush = kThemeBrushAppleGuideCoachmark
};

enum {
  kThemeActiveDialogTextColor   = kThemeTextColorDialogActive,
  kThemeInactiveDialogTextColor = kThemeTextColorDialogInactive,
  kThemeActiveAlertTextColor    = kThemeTextColorAlertActive,
  kThemeInactiveAlertTextColor  = kThemeTextColorAlertInactive,
  kThemeActiveModelessDialogTextColor = kThemeTextColorModelessDialogActive,
  kThemeInactiveModelessDialogTextColor = kThemeTextColorModelessDialogInactive,
  kThemeActiveWindowHeaderTextColor = kThemeTextColorWindowHeaderActive,
  kThemeInactiveWindowHeaderTextColor = kThemeTextColorWindowHeaderInactive,
  kThemeActivePlacardTextColor  = kThemeTextColorPlacardActive,
  kThemeInactivePlacardTextColor = kThemeTextColorPlacardInactive,
  kThemePressedPlacardTextColor = kThemeTextColorPlacardPressed,
  kThemeActivePushButtonTextColor = kThemeTextColorPushButtonActive,
  kThemeInactivePushButtonTextColor = kThemeTextColorPushButtonInactive,
  kThemePressedPushButtonTextColor = kThemeTextColorPushButtonPressed,
  kThemeActiveBevelButtonTextColor = kThemeTextColorBevelButtonActive,
  kThemeInactiveBevelButtonTextColor = kThemeTextColorBevelButtonInactive,
  kThemePressedBevelButtonTextColor = kThemeTextColorBevelButtonPressed,
  kThemeActivePopupButtonTextColor = kThemeTextColorPopupButtonActive,
  kThemeInactivePopupButtonTextColor = kThemeTextColorPopupButtonInactive,
  kThemePressedPopupButtonTextColor = kThemeTextColorPopupButtonPressed,
  kThemeIconLabelTextColor      = kThemeTextColorIconLabel,
  kThemeListViewTextColor       = kThemeTextColorListView
};

enum {
  kThemeActiveDocumentWindowTitleTextColor = kThemeTextColorDocumentWindowTitleActive,
  kThemeInactiveDocumentWindowTitleTextColor = kThemeTextColorDocumentWindowTitleInactive,
  kThemeActiveMovableModalWindowTitleTextColor = kThemeTextColorMovableModalWindowTitleActive,
  kThemeInactiveMovableModalWindowTitleTextColor = kThemeTextColorMovableModalWindowTitleInactive,
  kThemeActiveUtilityWindowTitleTextColor = kThemeTextColorUtilityWindowTitleActive,
  kThemeInactiveUtilityWindowTitleTextColor = kThemeTextColorUtilityWindowTitleInactive,
  kThemeActivePopupWindowTitleColor = kThemeTextColorPopupWindowTitleActive,
  kThemeInactivePopupWindowTitleColor = kThemeTextColorPopupWindowTitleInactive,
  kThemeActiveRootMenuTextColor = kThemeTextColorRootMenuActive,
  kThemeSelectedRootMenuTextColor = kThemeTextColorRootMenuSelected,
  kThemeDisabledRootMenuTextColor = kThemeTextColorRootMenuDisabled,
  kThemeActiveMenuItemTextColor = kThemeTextColorMenuItemActive,
  kThemeSelectedMenuItemTextColor = kThemeTextColorMenuItemSelected,
  kThemeDisabledMenuItemTextColor = kThemeTextColorMenuItemDisabled,
  kThemeActivePopupLabelTextColor = kThemeTextColorPopupLabelActive,
  kThemeInactivePopupLabelTextColor = kThemeTextColorPopupLabelInactive
};

enum {
  kAEThemeSwitch                = kAEAppearanceChanged /* Event ID's: Theme Switched */
};

enum {
  kThemeNoAdornment             = kThemeAdornmentNone,
  kThemeDefaultAdornment        = kThemeAdornmentDefault,
  kThemeFocusAdornment          = kThemeAdornmentFocus,
  kThemeRightToLeftAdornment    = kThemeAdornmentRightToLeft,
  kThemeDrawIndicatorOnly       = kThemeAdornmentDrawIndicatorOnly
};

enum {
  kThemeBrushPassiveAreaFill    = kThemeBrushStaticAreaFill
};

enum {
  kThemeMetricCheckBoxGlyphHeight = kThemeMetricCheckBoxHeight,
  kThemeMetricRadioButtonGlyphHeight = kThemeMetricRadioButtonHeight,
  kThemeMetricDisclosureButtonSize = kThemeMetricDisclosureButtonHeight,
  kThemeMetricBestListHeaderHeight = kThemeMetricListHeaderHeight,
  kThemeMetricSmallProgressBarThickness = kThemeMetricNormalProgressBarThickness, /* obsolete */
  kThemeMetricProgressBarThickness = kThemeMetricLargeProgressBarThickness /* obsolete */
};

enum {
  kThemeScrollBar               = kThemeMediumScrollBar,
  kThemeSlider                  = kThemeMediumSlider,
  kThemeProgressBar             = kThemeMediumProgressBar,
  kThemeIndeterminateBar        = kThemeMediumIndeterminateBar
};


#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __APPEARANCE__ */


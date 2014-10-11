/*
     File:       HIToolbox/Controls.h
 
     Contains:   Control Manager interfaces
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1985-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CONTROLS__
#define __CONTROLS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __QUICKDRAW__
#include <QD/Quickdraw.h>
#endif

#ifndef __MENUS__
#include <HIToolbox/Menus.h>
#endif

#ifndef __TEXTEDIT__
#include <HIToolbox/TextEdit.h>
#endif

#ifndef __DRAG__
#include <HIToolbox/Drag.h>
#endif

#ifndef __ICONS__
#include <HIToolbox/Icons.h>
#endif

#ifndef __COLLECTIONS__
#include <CarbonCore/Collections.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif





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

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Resource Types                                                                                    */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kControlDefProcType           = 'CDEF',
  kControlTemplateResourceType  = 'CNTL',
  kControlColorTableResourceType = 'cctb',
  kControlDefProcResourceType   = 'CDEF'
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Format of a ÔCNTLÕ resource                                                                       */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlTemplate {
  Rect                controlRect;
  SInt16              controlValue;
  Boolean             controlVisible;
  UInt8               fill;
  SInt16              controlMaximum;
  SInt16              controlMinimum;
  SInt16              controlDefProcID;
  SInt32              controlReference;
  Str255              controlTitle;
};
typedef struct ControlTemplate          ControlTemplate;
typedef ControlTemplate *               ControlTemplatePtr;
typedef ControlTemplatePtr *            ControlTemplateHandle;


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ ControlRef                                                                                        */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
#if !OPAQUE_TOOLBOX_STRUCTS
typedef struct ControlRecord            ControlRecord;
typedef ControlRecord *                 ControlPtr;
typedef ControlPtr *                    ControlRef;
#else
typedef struct OpaqueControlRef*        ControlRef;
#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

/* ControlHandle is obsolete. Use ControlRef.*/
typedef ControlRef                      ControlHandle;
typedef SInt16                          ControlPartCode;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* ¥ Control ActionProcPtr                                                                              */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
typedef CALLBACK_API( void , ControlActionProcPtr )(ControlRef theControl, ControlPartCode partCode);
typedef STACK_UPP_TYPE(ControlActionProcPtr)                    ControlActionUPP;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ ControlRecord                                                                                     */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
#if !OPAQUE_TOOLBOX_STRUCTS
struct ControlRecord {
  ControlRef          nextControl;            /* in Carbon use embedding heirarchy functions*/
  WindowRef           contrlOwner;            /* in Carbon use GetControlOwner or EmbedControl*/
  Rect                contrlRect;             /* in Carbon use Get/SetControlBounds*/
  UInt8               contrlVis;              /* in Carbon use IsControlVisible, SetControlVisibility*/
  UInt8               contrlHilite;           /* in Carbon use GetControlHilite, HiliteControl*/
  SInt16              contrlValue;            /* in Carbon use Get/SetControlValue, Get/SetControl32BitValue*/
  SInt16              contrlMin;              /* in Carbon use Get/SetControlMinimum, Get/SetControl32BitMinimum*/
  SInt16              contrlMax;              /* in Carbon use Get/SetControlMaximum, Get/SetControl32BitMaximum*/
  Handle              contrlDefProc;          /* not supported in Carbon*/
  Handle              contrlData;             /* in Carbon use Get/SetControlDataHandle*/
  ControlActionUPP    contrlAction;           /* in Carbon use Get/SetControlAction*/
  SInt32              contrlRfCon;            /* in Carbon use Get/SetControlReference*/
  Str255              contrlTitle;            /* in Carbon use Get/SetControlTitle*/
};

#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* ¥ Control ActionProcPtr : Epilogue                                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  NewControlActionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlActionUPP
NewControlActionUPP(ControlActionProcPtr userRoutine);

/*
 *  DisposeControlActionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlActionUPP(ControlActionUPP userUPP);

/*
 *  InvokeControlActionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeControlActionUPP(
  ControlRef        theControl,
  ControlPartCode   partCode,
  ControlActionUPP  userUPP);

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Color Table                                                                               */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  cFrameColor                   = 0,
  cBodyColor                    = 1,
  cTextColor                    = 2,
  cThumbColor                   = 3,
  kNumberCtlCTabEntries         = 4
};

struct CtlCTab {
  SInt32              ccSeed;
  SInt16              ccRider;
  SInt16              ctSize;
  ColorSpec           ctTable[4];
};
typedef struct CtlCTab                  CtlCTab;
typedef CtlCTab *                       CCTabPtr;
typedef CCTabPtr *                      CCTabHandle;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Auxiliary Control Record                                                                          */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
#if !OPAQUE_TOOLBOX_STRUCTS
struct AuxCtlRec {
  Handle              acNext;                 /* not supported in Carbon*/
  ControlRef          acOwner;                /* not supported in Carbon*/
  CCTabHandle         acCTable;               /* not supported in Carbon*/
  SInt16              acFlags;                /* not supported in Carbon*/
  SInt32              acReserved;             /* not supported in Carbon*/
  SInt32              acRefCon;               /* in Carbon use Get/SetControlProperty if you need more refCons*/
};
typedef struct AuxCtlRec                AuxCtlRec;
typedef AuxCtlRec *                     AuxCtlPtr;
typedef AuxCtlPtr *                     AuxCtlHandle;
#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Variants                                                                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
typedef SInt16                          ControlVariant;
enum {
  kControlNoVariant             = 0,    /* No variant*/
  kControlUsesOwningWindowsFontVariant = 1 << 3 /* Control uses owning windows font to display text*/
};


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Part Codes                                                                */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Basic part codes */
enum {
  kControlNoPart                = 0,
  kControlIndicatorPart         = 129,
  kControlDisabledPart          = 254,
  kControlInactivePart          = 255
};

/* Use this constant in Get/SetControlData when the data referred to is not         */
/* specific to a part, but rather the entire control, e.g. the list handle of a     */
/* list box control.                                                                */
enum {
  kControlEntireControl         = 0
};

/*  Meta-Parts                                                                          */
/*                                                                                      */
/*  If you haven't guessed from looking at other toolbox headers. We like the word      */
/*  'meta'. It's cool. So here's one more for you. A meta-part is a part used in a call */
/*  to the GetControlRegion API. These parts are parts that might be defined by a       */
/*  control, but should not be returned from calls like TestControl, et al. They define */
/*  a region of a control, presently the structure and the content region. The content  */
/*  region is only defined by controls that can embed other controls. It is the area    */
/*  that embedded content can live.                                                     */
/*                                                                                      */
/*  Along with these parts, you can also pass in normal part codes to get the regions   */
/*  of the parts. Not all controls fully support this at the time this was written.     */
enum {
  kControlStructureMetaPart     = -1,
  kControlContentMetaPart       = -2
};

/* focusing part codes */
enum {
  kControlFocusNoPart           = 0,    /* tells control to clear its focus*/
  kControlFocusNextPart         = -1,   /* tells control to focus on the next part*/
  kControlFocusPrevPart         = -2    /* tells control to focus on the previous part*/
};

typedef SInt16                          ControlFocusPart;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Collection Tags                                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  These are standard tags that you will find in the initial data Collection that is passed in the     */
/*  'param' parameter to the initCntl message (Carbon only).                                            */
/*                                                                                                      */
/*  All tags at ID zero in a Control's Collection are reserved for Control Manager use.                 */
/*  Custom control definitions should use other IDs.                                                    */
/*                                                                                                      */
/*  Most of these tags are interpreted when you call CreateCustomControl; the Control Manager will      */
/*  put value in the right place before calling the Control Definition with the initialization message. */
enum {
  kControlCollectionTagBounds   = 'boun', /* Rect - the bounding rectangle*/
  kControlCollectionTagValue    = 'valu', /* SInt32 - the value*/
  kControlCollectionTagMinimum  = 'min ', /* SInt32 - the minimum*/
  kControlCollectionTagMaximum  = 'max ', /* SInt32 - the maximum*/
  kControlCollectionTagViewSize = 'view', /* SInt32 - the view size*/
  kControlCollectionTagVisibility = 'visi', /* Boolean - the visible state*/
  kControlCollectionTagRefCon   = 'refc', /* SInt32 - the refCon*/
  kControlCollectionTagTitle    = 'titl', /* arbitrarily sized character array - the title*/
  kControlCollectionTagUnicodeTitle = 'uttl', /* bytes as received via CFStringCreateExternalRepresentation*/
  kControlCollectionTagIDSignature = 'idsi', /* OSType - the ControlID signature*/
  kControlCollectionTagIDID     = 'idid', /* SInt32 - the ControlID id*/
  kControlCollectionTagCommand  = 'cmd ', /* UInt32 - the command*/
  kControlCollectionTagVarCode  = 'varc' /* SInt16 - the variant*/
};

/*  The following are additional tags which are only interpreted by UnflattenControl. */
enum {
  kControlCollectionTagSubControls = 'subc' /* data for all of a control's subcontrols*/
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Image Content                                                                             */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kControlContentTextOnly       = 0,
  kControlNoContent             = 0,
  kControlContentIconSuiteRes   = 1,
  kControlContentCIconRes       = 2,
  kControlContentPictRes        = 3,
  kControlContentICONRes        = 4,
  kControlContentIconSuiteHandle = 129,
  kControlContentCIconHandle    = 130,
  kControlContentPictHandle     = 131,
  kControlContentIconRef        = 132,
  kControlContentICON           = 133
};

typedef SInt16                          ControlContentType;
struct ControlButtonContentInfo {
  ControlContentType  contentType;
  union {
    SInt16              resID;
    CIconHandle         cIconHandle;
    Handle              iconSuite;
    IconRef             iconRef;
    PicHandle           picture;
    Handle              ICONHandle;
  }                       u;
};
typedef struct ControlButtonContentInfo ControlButtonContentInfo;
typedef ControlButtonContentInfo *      ControlButtonContentInfoPtr;
typedef ControlButtonContentInfo        ControlImageContentInfo;
typedef ControlButtonContentInfo *      ControlImageContentInfoPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Key Script Behavior                                                                       */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kControlKeyScriptBehaviorAllowAnyScript = 'any ', /* leaves the current keyboard alone and allows user to change the keyboard.*/
  kControlKeyScriptBehaviorPrefersRoman = 'prmn', /* switches the keyboard to roman, but allows them to change it as desired.*/
  kControlKeyScriptBehaviorRequiresRoman = 'rrmn' /* switches the keyboard to roman and prevents the user from changing it.*/
};

typedef UInt32                          ControlKeyScriptBehavior;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Font Style                                                                                */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*    SPECIAL FONT USAGE NOTES: You can specify the font to use for many control types.
    The constants below are meta-font numbers which you can use to set a particular
    control's font usage. There are essentially two modes you can use: 1) default,
    which is essentially the same as it always has been, i.e. it uses the system font, unless
    directed to use the window font via a control variant. 2) you can specify to use
    the big or small system font in a generic manner. The Big system font is the font
    used in menus, etc. Chicago has filled that role for some time now. Small system
    font is currently Geneva 10. The meta-font number implies the size and style.

    NOTE:       Not all font attributes are used by all controls. Most, in fact, ignore
                the fore and back color (Static Text is the only one that does, for
                backwards compatibility). Also size, face, and addFontSize are ignored
                when using the meta-font numbering.
*/
/* Meta-font numbering - see note above */
enum {
  kControlFontBigSystemFont     = -1,   /* force to big system font*/
  kControlFontSmallSystemFont   = -2,   /* force to small system font*/
  kControlFontSmallBoldSystemFont = -3, /* force to small bold system font*/
  kControlFontViewSystemFont    = -4    /* force to views system font (DataBrowser control only)*/
};

/* Add these masks together to set the flags field of a ControlFontStyleRec */
/* They specify which fields to apply to the text. It is important to make  */
/* sure that you specify only the fields that you wish to set.              */
enum {
  kControlUseFontMask           = 0x0001,
  kControlUseFaceMask           = 0x0002,
  kControlUseSizeMask           = 0x0004,
  kControlUseForeColorMask      = 0x0008,
  kControlUseBackColorMask      = 0x0010,
  kControlUseModeMask           = 0x0020,
  kControlUseJustMask           = 0x0040,
  kControlUseAllMask            = 0x00FF,
  kControlAddFontSizeMask       = 0x0100
};

/* AddToMetaFont indicates that we want to start with a standard system     */
/* font, but then we'd like to add the other attributes. Normally, the meta */
/* font ignores all other flags                                             */
enum {
  kControlAddToMetaFontMask     = 0x0200 /* Available in Appearance 1.1 or later*/
};

/* UseThemeFontID indicates that the font field of the ControlFontStyleRec  */
/* should be interpreted as a ThemeFontID (see Appearance.h). In all other  */
/* ways, specifying a ThemeFontID is just like using one of the control     */
/* meta-fonts IDs.                                                          */
enum {
  kControlUseThemeFontIDMask    = 0x0080 /* Available in Mac OS X or later*/
};

struct ControlFontStyleRec {
  SInt16              flags;
  SInt16              font;
  SInt16              size;
  SInt16              style;
  SInt16              mode;
  SInt16              just;
  RGBColor            foreColor;
  RGBColor            backColor;
};
typedef struct ControlFontStyleRec      ControlFontStyleRec;
typedef ControlFontStyleRec *           ControlFontStylePtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Click Activation Results                                                                          */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  These are for use with GetControlClickActivation. The enumerated values should be pretty            */
/*  self-explanatory, but just in case:                                                                 */
/*  ¥ Activate/DoNotActivate indicates whether or not to change the owning window's z-ordering before   */
/*      processing the click. If activation is requested, you may also want to immediately redraw the   */
/*      newly exposed portion of the window.                                                            */
/*  ¥ Ignore/Handle Click indicates whether or not to call an appropriate click handling API (like      */
/*      HandleControlClick) in respose to the event.                                                    */
enum {
  kDoNotActivateAndIgnoreClick  = 0,    /* probably never used. here for completeness.*/
  kDoNotActivateAndHandleClick  = 1,    /* let the control handle the click while the window is still in the background.*/
  kActivateAndIgnoreClick       = 2,    /* control doesn't want to respond directly to the click, but window should still be brought forward.*/
  kActivateAndHandleClick       = 3     /* control wants to respond to the click, but only after the window has been activated.*/
};

typedef UInt32                          ClickActivationResult;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Common data tags for Get/SetControlData                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

/*
 *  Discussion:
 *    Get/SetControlData Common Tags
 */
enum {
  kControlFontStyleTag          = 'font',
  kControlKeyFilterTag          = 'fltr',

  /*
   * Sent with a pointer to a ControlKind record to be filled in. Only
   * valid for GetControlData.
   */
  kControlKindTag               = 'kind',

  /*
   * Sent with a pointer to a ControlSize. Only valid with explicitly
   * sizeable controls.
   */
  kControlSizeTag               = 'size'
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Feature Bits                                                                              */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
                                        /* Control feature bits - returned by GetControlFeatures */
  kControlSupportsGhosting      = 1 << 0,
  kControlSupportsEmbedding     = 1 << 1,
  kControlSupportsFocus         = 1 << 2,
  kControlWantsIdle             = 1 << 3,
  kControlWantsActivate         = 1 << 4,
  kControlHandlesTracking       = 1 << 5,
  kControlSupportsDataAccess    = 1 << 6,
  kControlHasSpecialBackground  = 1 << 7,
  kControlGetsFocusOnClick      = 1 << 8,
  kControlSupportsCalcBestRect  = 1 << 9,
  kControlSupportsLiveFeedback  = 1 << 10,
  kControlHasRadioBehavior      = 1 << 11, /* Available in Appearance 1.0.1 or later*/
  kControlSupportsDragAndDrop   = 1 << 12, /* Available in Carbon*/
  kControlAutoToggles           = 1 << 14, /* Available in Appearance 1.1 or later*/
  kControlSupportsGetRegion     = 1 << 17, /* Available in Appearance 1.1 or later*/
  kControlSupportsFlattening    = 1 << 19, /* Available in Carbon*/
  kControlSupportsSetCursor     = 1 << 20, /* Available in Carbon*/
  kControlSupportsContextualMenus = 1 << 21, /* Available in Carbon*/
  kControlSupportsClickActivation = 1 << 22, /* Available in Carbon*/
  kControlIdlesWithTimer        = 1 << 23 /* Available in Carbon - this bit indicates that the control animates automatically*/
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Messages                                                                                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  drawCntl                      = 0,
  testCntl                      = 1,
  calcCRgns                     = 2,
  initCntl                      = 3,    /* Param is Collection, result is OSStatus*/
  dispCntl                      = 4,
  posCntl                       = 5,
  thumbCntl                     = 6,
  dragCntl                      = 7,
  autoTrack                     = 8,
  calcCntlRgn                   = 10,
  calcThumbRgn                  = 11,
  drawThumbOutline              = 12,
  kControlMsgDrawGhost          = 13,
  kControlMsgCalcBestRect       = 14,   /* Calculate best fitting rectangle for control*/
  kControlMsgHandleTracking     = 15,
  kControlMsgFocus              = 16,   /* param indicates action.*/
  kControlMsgKeyDown            = 17,
  kControlMsgIdle               = 18,
  kControlMsgGetFeatures        = 19,
  kControlMsgSetData            = 20,
  kControlMsgGetData            = 21,
  kControlMsgActivate           = 22,
  kControlMsgSetUpBackground    = 23,
  kControlMsgCalcValueFromPos   = 26,
  kControlMsgTestNewMsgSupport  = 27,   /* See if this control supports new messaging*/
  kControlMsgSubValueChanged    = 25,   /* Available in Appearance 1.0.1 or later*/
  kControlMsgSubControlAdded    = 28,   /* Available in Appearance 1.0.1 or later*/
  kControlMsgSubControlRemoved  = 29,   /* Available in Appearance 1.0.1 or later*/
  kControlMsgApplyTextColor     = 30,   /* Available in Appearance 1.1 or later*/
  kControlMsgGetRegion          = 31,   /* Available in Appearance 1.1 or later*/
  kControlMsgFlatten            = 32,   /* Available in Carbon. Param is Collection.*/
  kControlMsgSetCursor          = 33,   /* Available in Carbon. Param is ControlSetCursorRec*/
  kControlMsgDragEnter          = 38,   /* Available in Carbon. Param is DragRef, result is boolean indicating acceptibility of drag.*/
  kControlMsgDragLeave          = 39,   /* Available in Carbon. As above.*/
  kControlMsgDragWithin         = 40,   /* Available in Carbon. As above.*/
  kControlMsgDragReceive        = 41,   /* Available in Carbon. Param is DragRef, result is OSStatus indicating success/failure.*/
  kControlMsgDisplayDebugInfo   = 46,   /* Available in Carbon on X.*/
  kControlMsgContextualMenuClick = 47,  /* Available in Carbon. Param is ControlContextualMenuClickRec*/
  kControlMsgGetClickActivation = 48    /* Available in Carbon. Param is ControlClickActivationRec*/
};

typedef SInt16                          ControlDefProcMessage;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Sizes                                                                     */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kControlSizeNormal            = 0,
  kControlSizeSmall             = 1,
  kControlSizeLarge             = 2,
  kControlSizeAuto              = 0xFFFF
};

typedef UInt16                          ControlSize;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Constants for drawCntl message (passed in param)                                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kDrawControlEntireControl     = 0,
  kDrawControlIndicatorOnly     = 129
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Constants for dragCntl message (passed in param)                                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kDragControlEntireControl     = 0,
  kDragControlIndicator         = 1
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Drag Constraint Structure for thumbCntl message (passed in param)                 */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct IndicatorDragConstraint {
  Rect                limitRect;
  Rect                slopRect;
  DragConstraint      axis;
};
typedef struct IndicatorDragConstraint  IndicatorDragConstraint;
typedef IndicatorDragConstraint *       IndicatorDragConstraintPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  CDEF should return as result of kControlMsgTestNewMsgSupport                        */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kControlSupportsNewMessages   = ' ok '
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  This structure is passed into a CDEF when called with the kControlMsgHandleTracking */
/*  message                                                                             */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlTrackingRec {
  Point               startPt;
  EventModifiers      modifiers;
  ControlActionUPP    action;
};
typedef struct ControlTrackingRec       ControlTrackingRec;
typedef ControlTrackingRec *            ControlTrackingPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* This structure is passed into a CDEF when called with the kControlMsgKeyDown message */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlKeyDownRec {
  EventModifiers      modifiers;
  SInt16              keyCode;
  SInt16              charCode;
};
typedef struct ControlKeyDownRec        ControlKeyDownRec;
typedef ControlKeyDownRec *             ControlKeyDownPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* This structure is passed into a CDEF when called with the kControlMsgGetData or      */
/* kControlMsgSetData message                                                           */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlDataAccessRec {
  ResType             tag;
  ResType             part;
  Size                size;
  Ptr                 dataPtr;
};
typedef struct ControlDataAccessRec     ControlDataAccessRec;
typedef ControlDataAccessRec *          ControlDataAccessPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* This structure is passed into a CDEF when called with the kControlCalcBestRect msg   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlCalcSizeRec {
  SInt16              height;
  SInt16              width;
  SInt16              baseLine;
};
typedef struct ControlCalcSizeRec       ControlCalcSizeRec;
typedef ControlCalcSizeRec *            ControlCalcSizePtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* This structure is passed into a CDEF when called with the kControlMsgSetUpBackground */
/* message is sent                                                                      */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlBackgroundRec {
  SInt16              depth;
  Boolean             colorDevice;
};
typedef struct ControlBackgroundRec     ControlBackgroundRec;
typedef ControlBackgroundRec *          ControlBackgroundPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* This structure is passed into a CDEF when called with the kControlMsgApplyTextColor  */
/* message is sent                                                                      */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlApplyTextColorRec {
  SInt16              depth;
  Boolean             colorDevice;
  Boolean             active;
};
typedef struct ControlApplyTextColorRec ControlApplyTextColorRec;
typedef ControlApplyTextColorRec *      ControlApplyTextColorPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* This structure is passed into a CDEF when called with the kControlMsgGetRegion       */
/* message is sent                                                                      */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlGetRegionRec {
  RgnHandle           region;
  ControlPartCode     part;
};
typedef struct ControlGetRegionRec      ControlGetRegionRec;
typedef ControlGetRegionRec *           ControlGetRegionPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* This structure is passed into a CDEF when the kControlMsgSetCursor message is sent   */
/* Only sent on Carbon                                                                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlSetCursorRec {
  Point               localPoint;
  EventModifiers      modifiers;
  Boolean             cursorWasSet;           /* your CDEF must set this to true if you set the cursor, or false otherwise*/
};
typedef struct ControlSetCursorRec      ControlSetCursorRec;
typedef ControlSetCursorRec *           ControlSetCursorPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* This structure is passed into a CDEF when the kControlMsgContextualMenuClick message */
/* is sent                                                                              */
/* Only sent on Carbon                                                                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlContextualMenuClickRec {
  Point               localPoint;
  Boolean             menuDisplayed;          /* your CDEF must set this to true if you displayed a menu, or false otherwise*/
};
typedef struct ControlContextualMenuClickRec ControlContextualMenuClickRec;
typedef ControlContextualMenuClickRec * ControlContextualMenuClickPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* This structure is passed into a CDEF when the kControlMsgGetClickActivation message  */
/* is sent                                                                              */
/* Only sent on Carbon                                                                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlClickActivationRec {
  Point               localPoint;
  EventModifiers      modifiers;
  ClickActivationResult  result;              /* your CDEF must pass the desired result back*/
};
typedef struct ControlClickActivationRec ControlClickActivationRec;
typedef ControlClickActivationRec *     ControlClickActivationPtr;
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ ÔCDEFÕ entrypoint                                                                 */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
typedef CALLBACK_API( SInt32 , ControlDefProcPtr )(SInt16 varCode, ControlRef theControl, ControlDefProcMessage message, SInt32 param);
typedef STACK_UPP_TYPE(ControlDefProcPtr)                       ControlDefUPP;
/*
 *  NewControlDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlDefUPP
NewControlDefUPP(ControlDefProcPtr userRoutine);

/*
 *  DisposeControlDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlDefUPP(ControlDefUPP userUPP);

/*
 *  InvokeControlDefUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SInt32
InvokeControlDefUPP(
  SInt16                 varCode,
  ControlRef             theControl,
  ControlDefProcMessage  message,
  SInt32                 param,
  ControlDefUPP          userUPP);

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  Control Key Filter                                                                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* Certain controls can have a keyfilter attached to them.                              */
/* Definition of a key filter for intercepting and possibly changing keystrokes         */
/* which are destined for a control.                                                    */
/* Key Filter Result Codes                                                          */
/* The filter proc should return one of the two constants below. If                 */
/* kKeyFilterBlockKey is returned, the key is blocked and never makes it to the     */
/* control. If kKeyFilterPassKey is returned, the control receives the keystroke.   */
enum {
  kControlKeyFilterBlockKey     = 0,
  kControlKeyFilterPassKey      = 1
};

typedef SInt16                          ControlKeyFilterResult;
typedef CALLBACK_API( ControlKeyFilterResult , ControlKeyFilterProcPtr )(ControlRef theControl, SInt16 *keyCode, SInt16 *charCode, EventModifiers *modifiers);
typedef STACK_UPP_TYPE(ControlKeyFilterProcPtr)                 ControlKeyFilterUPP;
/*
 *  NewControlKeyFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlKeyFilterUPP
NewControlKeyFilterUPP(ControlKeyFilterProcPtr userRoutine);

/*
 *  DisposeControlKeyFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlKeyFilterUPP(ControlKeyFilterUPP userUPP);

/*
 *  InvokeControlKeyFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlKeyFilterResult
InvokeControlKeyFilterUPP(
  ControlRef           theControl,
  SInt16 *             keyCode,
  SInt16 *             charCode,
  EventModifiers *     modifiers,
  ControlKeyFilterUPP  userUPP);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ DragGrayRgn Constatns                                                             */
/*                                                                                      */
/*   For DragGrayRgnUPP used in TrackControl()                                          */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  noConstraint                  = kNoConstraint,
  hAxisOnly                     = 1,
  vAxisOnly                     = 2
};

/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Creation/Deletion/Persistence                                             */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  CreateCustomControl is only available as part of Carbon                             */
enum {
  kControlDefProcPtr            = 0,    /* raw proc-ptr based access*/
  kControlDefObjectClass        = 1     /* event-based definition (Mac OS X only)*/
};

typedef UInt32                          ControlDefType;
struct ControlDefSpec {
  ControlDefType      defType;
  union {
    ControlDefUPP       defProc;
    void *              classRef;
  }                       u;
};
typedef struct ControlDefSpec           ControlDefSpec;
/*
 *  CreateCustomControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateCustomControl(
  WindowRef               owningWindow,
  const Rect *            contBounds,
  const ControlDefSpec *  def,
  Collection              initData,
  ControlRef *            outControl);


/*
 *  NewControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ControlRef 
NewControl(
  WindowRef          owningWindow,
  const Rect *       boundsRect,
  ConstStr255Param   controlTitle,
  Boolean            initiallyVisible,
  SInt16             initialValue,
  SInt16             minimumValue,
  SInt16             maximumValue,
  SInt16             procID,
  SInt32             controlReference);


/*
 *  GetNewControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ControlRef 
GetNewControl(
  SInt16      resourceID,
  WindowRef   owningWindow);


/*
 *  DisposeControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeControl(ControlRef theControl);


/*
 *  KillControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
KillControls(WindowRef theWindow);


/*
 *  FlattenControl()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  UnflattenControl()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Definition Registration                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
typedef CALLBACK_API( OSStatus , ControlCNTLToCollectionProcPtr )(const Rect *bounds, SInt16 value, Boolean visible, SInt16 max, SInt16 min, SInt16 procID, SInt32 refCon, ConstStr255Param title, Collection collection);
typedef STACK_UPP_TYPE(ControlCNTLToCollectionProcPtr)          ControlCNTLToCollectionUPP;
/*
 *  NewControlCNTLToCollectionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlCNTLToCollectionUPP
NewControlCNTLToCollectionUPP(ControlCNTLToCollectionProcPtr userRoutine);

/*
 *  DisposeControlCNTLToCollectionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlCNTLToCollectionUPP(ControlCNTLToCollectionUPP userUPP);

/*
 *  InvokeControlCNTLToCollectionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeControlCNTLToCollectionUPP(
  const Rect *                bounds,
  SInt16                      value,
  Boolean                     visible,
  SInt16                      max,
  SInt16                      min,
  SInt16                      procID,
  SInt32                      refCon,
  ConstStr255Param            title,
  Collection                  collection,
  ControlCNTLToCollectionUPP  userUPP);

/*
 *  RegisterControlDefinition()
 *  
 *  Summary:
 *    Associates or dissociates a control definition with a virtual
 *    CDEF resource ID.
 *  
 *  Discussion:
 *    In GetNewControl or NewControl on Carbon, the Control Manager
 *    needs to know how to map the procID to a ControlDefSpec. With
 *    RegisterControlDefinition, your application can inform the
 *    Control Manager which ControlDefSpec to call when it sees a
 *    request to use a 'CDEF' of a particular resource ID. Since custom
 *    control definitions receive their initialization data in a
 *    Collection passed in the 'param' parameter, you must also provide
 *    a procedure to convert the bounds, min, max, and other parameters
 *    to NewControl into a Collection. If you don't provide a
 *    conversion proc, your control will receive an empty collection
 *    when it is sent the initialization message. If you want the
 *    value, min, visibility, etc. to be given to the control, you must
 *    add the appropriate tagged data to the collection. See the
 *    Control Collection Tags above. If you want to unregister a
 *    ControlDefSpec that you have already registered, call
 *    RegisterControlDefinition with the same CDEF resource ID, but
 *    pass NULL for the inControlDef parameter. In this situation,
 *    inConversionProc is effectively ignored.
 *  
 *  Parameters:
 *    
 *    inCDEFResID:
 *      The virtual CDEF resource ID to which you'd like to associate
 *      or dissociate the control definition.
 *    
 *    inControlDef:
 *      A pointer to a ControlDefSpec which represents the control
 *      definition you want to register, or NULL if you are attempting
 *      to unregister a control definition.
 *    
 *    inConversionProc:
 *      The conversion proc which will translate the NewControl
 *      parameters into a Collection.
 *  
 *  Result:
 *    An OSStatus code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RegisterControlDefinition(
  SInt16                       inCDEFResID,
  const ControlDefSpec *       inControlDef,
  ControlCNTLToCollectionUPP   inConversionProc);




/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Visible State                                                             */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  HiliteControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HiliteControl(
  ControlRef        theControl,
  ControlPartCode   hiliteState);


/*
 *  ShowControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ShowControl(ControlRef theControl);


/*
 *  HideControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HideControl(ControlRef theControl);



/* following state routines available only with Appearance 1.0 and later*/
/*
 *  IsControlActive()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern Boolean 
IsControlActive(ControlRef inControl);


/*
 *  IsControlVisible()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern Boolean 
IsControlVisible(ControlRef inControl);


/*
 *  ActivateControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
ActivateControl(ControlRef inControl);


/*
 *  DeactivateControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
DeactivateControl(ControlRef inControl);


/*
 *  SetControlVisibility()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetControlVisibility(
  ControlRef   inControl,
  Boolean      inIsVisible,
  Boolean      inDoDraw);



/* following state routines available only on Mac OS X and later*/
/*
 *  IsControlEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsControlEnabled(ControlRef inControl);


/*
 *  EnableControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
EnableControl(ControlRef inControl);


/*
 *  DisableControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DisableControl(ControlRef inControl);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Imaging                                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  DrawControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DrawControls(WindowRef theWindow);


/*
 *  Draw1Control()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
Draw1Control(ControlRef theControl);


#define DrawOneControl(theControl) Draw1Control(theControl)

/*
 *  UpdateControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
UpdateControls(
  WindowRef   theWindow,
  RgnHandle   updateRegion);



/* following imaging routines available only with Appearance 1.0 and later*/
/*
 *  GetBestControlRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetBestControlRect(
  ControlRef   inControl,
  Rect *       outRect,
  SInt16 *     outBaseLineOffset);


/*
 *  SetControlFontStyle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetControlFontStyle(
  ControlRef                   inControl,
  const ControlFontStyleRec *  inStyle);


/*
 *  DrawControlInCurrentPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern void 
DrawControlInCurrentPort(ControlRef inControl);


/*
 *  SetUpControlBackground()
 *  
 *  Summary:
 *    Applies the proper background color for the given control to the
 *    current port.
 *  
 *  Discussion:
 *    An embedding-savvy control which erases before drawing must
 *    ensure that its background color properly matches the body color
 *    of any parent controls on top of which it draws. This routine
 *    asks the Control Manager to determine and apply the proper
 *    background color to the current port. If a ControlColorProc has
 *    been provided for the given control, the proc will be called to
 *    set up the background color. If no proc exists, or if the proc
 *    returns a value other than noErr, the Control Manager ascends the
 *    parent chain for the given control looking for a control which
 *    has a special background (see the kControlHasSpecialBackground
 *    feature bit). The first such parent is asked to set up the
 *    background color (see the kControlMsgSetUpBackground message). If
 *    no such parent exists, the Control Manager applies any ThemeBrush
 *    which has been associated with the owning window (see
 *    SetThemeWindowBackground). Available in Appearance 1.0 (Mac OS
 *    8), CarbonLib 1.0, Mac OS X, and later.
 *  
 *  Parameters:
 *    
 *    inControl:
 *      The ControlRef that wants to erase.
 *    
 *    inDepth:
 *      A short integer indicating the color depth of the device onto
 *      which drawing will take place.
 *    
 *    inIsColorDevice:
 *      A Boolean indicating whether the draw device is a color device.
 *  
 *  Result:
 *    An OSStatus code indicating success or failure. The most likely
 *    error is a controlHandleInvalidErr, resulting from a bad
 *    ControlRef. Any non-noErr result indicates that the color set up
 *    failed, and that the caller should probably give up its attempt
 *    to draw.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetUpControlBackground(
  ControlRef   inControl,
  SInt16       inDepth,
  Boolean      inIsColorDevice);


/*
 *  SetUpControlTextColor()
 *  
 *  Summary:
 *    Applies the proper text color for the given control to the
 *    current port.
 *  
 *  Discussion:
 *    An embedding-savvy control which draws text must ensure that its
 *    text color properly contrasts the background on which it draws.
 *    This routine asks the Control Manager to determine and apply the
 *    proper text color to the current port. If a ControlColorProc has
 *    been provided for the given control, the proc will be called to
 *    set up the text color. If no proc exists, or if the proc returns
 *    a value other than noErr, the Control Manager ascends the parent
 *    chain for the given control looking for a control which has a
 *    special background (see the kControlHasSpecialBackground feature
 *    bit). The first such parent is asked to set up the text color
 *    (see the kControlMsgApplyTextColor message). If no such parent
 *    exists, the Control Manager chooses a text color which contrasts
 *    any ThemeBrush which has been associated with the owning window
 *    (see SetThemeWindowBackground). Available in Appearance 1.1 (Mac
 *    OS 8.5), CarbonLib 1.0, Mac OS X, and later.
 *  
 *  Parameters:
 *    
 *    inControl:
 *      The ControlRef that wants to draw text.
 *    
 *    inDepth:
 *      A short integer indicating the color depth of the device onto
 *      which drawing will take place.
 *    
 *    inIsColorDevice:
 *      A Boolean indicating whether the draw device is a color device.
 *  
 *  Result:
 *    An OSStatus code indicating success or failure. The most likely
 *    error is a controlHandleInvalidErr, resulting from a bad
 *    ControlRef. Any non-noErr result indicates that the color set up
 *    failed, and that the caller should probably give up its attempt
 *    to draw.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern OSErr 
SetUpControlTextColor(
  ControlRef   inControl,
  SInt16       inDepth,
  Boolean      inIsColorDevice);




/*
 *  ControlColorProcPtr
 *  
 *  Discussion:
 *    Callback allowing clients to specify/override the background
 *    color and text color that a Control will use during drawing. Your
 *    procedure should make the color changes to the current port. See
 *    SetControlColorProc, SetUpControlBackground, and
 *    SetUpControlTextColor for more information. Available on Mac OS
 *    8.5, CarbonLib 1.1, Mac OS X, and later.
 *  
 *  Parameters:
 *    
 *    inControl:
 *      A reference to the Control for whom your proc is setting up
 *      colors.
 *    
 *    inMessage:
 *      A ControlDefProcMessage indicating what sort of color your
 *      procedure should set up. It will be either
 *      kControlMsgApplyTextColor or kControlMsgSetUpBackground.
 *      kControlMsgApplyTextColor is a request to set up the
 *      appropriate text color (by setting the current port's
 *      foreground color, pen information, etc.).
 *      kControlMsgSetUpBackground is a request to set up the
 *      appropriate background color (the current port's background
 *      color, pattern, etc.).
 *    
 *    inDrawDepth:
 *      A short integer indicating the bit depth of the device into
 *      which the Control is drawing. The bit depth is typically passed
 *      in as a result of someone someone trying to draw properly
 *      across multiple monitors with different bit depths. If your
 *      procedure wants to handle proper color set up based on bit
 *      depth, it should use this parameter to help decide what color
 *      to apply.
 *    
 *    inDrawInColor:
 *      A Boolean indicating whether or not the device that the Control
 *      is drawing into is a color device. The value is typically
 *      passed in as a result of someone trying to draw properly across
 *      multiple monitors which may or may not be color devices. If
 *      your procedure wants to handle proper color set up for both
 *      color and grayscale devices, it should use this parameter to
 *      help decide what color to apply.
 *  
 *  Result:
 *    An OSStatus code indicating success or failure. Returning noErr
 *    is an indication that your proc completely handled the color set
 *    up. If you return any other value, the Control Manager will fall
 *    back to the normal color set up mechanism.
 */
typedef CALLBACK_API( OSStatus , ControlColorProcPtr )(ControlRef inControl, SInt16 inMessage, SInt16 inDrawDepth, Boolean inDrawInColor);
typedef STACK_UPP_TYPE(ControlColorProcPtr)                     ControlColorUPP;
/*
 *  NewControlColorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ControlColorUPP
NewControlColorUPP(ControlColorProcPtr userRoutine);

/*
 *  DisposeControlColorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeControlColorUPP(ControlColorUPP userUPP);

/*
 *  InvokeControlColorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeControlColorUPP(
  ControlRef       inControl,
  SInt16           inMessage,
  SInt16           inDrawDepth,
  Boolean          inDrawInColor,
  ControlColorUPP  userUPP);

/*
 *  SetControlColorProc()
 *  
 *  Summary:
 *    Associates a ControlColorUPP with a given Control, thereby
 *    allowing you to bypass the embedding hierarchy-based color setup
 *    of SetUpControlBackground/SetUpControlTextColor and replace it
 *    with your own.
 *  
 *  Discussion:
 *    Before an embedded Control can erase, it calls
 *    SetUpControlBackground to have its background color set up by any
 *    parent controls. Similarly, any Control which draws text calls
 *    SetUpControlTextColor to have the appropriate text color set up.
 *    This allows certain controls (such as Tabs and Placards) to offer
 *    special backgrounds and text colors for any child controls. By
 *    default, the SetUp routines only move up the Control Manager
 *    embedding hierarchy looking for a parent which has a special
 *    background. This is fine in a plain vanilla embedding case, but
 *    many application frameworks find it troublesome; if there are
 *    interesting views between two Controls in the embedding
 *    hierarchy, the framework needs to be in charge of the background
 *    and text colors, otherwise drawing defects will occur. You can
 *    only associate a single color proc with a given ControlRef.
 *    Available on Mac OS 8.5, CarbonLib 1.1, Mac OS X, and later.
 *  
 *  Parameters:
 *    
 *    inControl:
 *      The ControlRef with whom the color proc should be associated.
 *    
 *    inProc:
 *      The color proc to associate with the ControlRef. If you pass
 *      NULL, the ControlRef will be dissociated from any previously
 *      installed color proc.
 *  
 *  Result:
 *    An OSStatus code indicating success or failure. The most likely
 *    error is a controlHandleInvalidErr resulting from a bad
 *    ControlRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern OSStatus 
SetControlColorProc(
  ControlRef        inControl,
  ControlColorUPP   inProc);



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Mousing                                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
    NOTE ON CONTROL ACTION PROCS

    When using the TrackControl() call when tracking an indicator, the actionProc parameter
    (type ControlActionUPP) should be replaced by a parameter of type DragGrayRgnUPP
    (see Quickdraw.h).

    If, however, you are using the live feedback variants of scroll bars or sliders, you
    must pass a ControlActionUPP in when tracking the indicator as well. This functionality
    is available in Appearance 1.0 or later.
*/
/*
 *  TrackControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ControlPartCode 
TrackControl(
  ControlRef         theControl,
  Point              startPoint,
  ControlActionUPP   actionProc);      /* can be NULL */


/*
 *  DragControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DragControl(
  ControlRef       theControl,
  Point            startPoint,
  const Rect *     limitRect,
  const Rect *     slopRect,
  DragConstraint   axis);


/*
 *  TestControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ControlPartCode 
TestControl(
  ControlRef   theControl,
  Point        testPoint);


/*
 *  FindControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ControlPartCode 
FindControl(
  Point         testPoint,
  WindowRef     theWindow,
  ControlRef *  theControl);


/* The following mousing routines available only with Appearance 1.0 and later  */
/*                                                                              */
/* HandleControlClick is preferable to TrackControl when running under          */
/* Appearance 1.0 as you can pass in modifiers, which some of the new controls  */
/* use, such as edit text and list boxes.                                       */
/*
 *  FindControlUnderMouse()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern ControlRef 
FindControlUnderMouse(
  Point       inWhere,
  WindowRef   inWindow,
  SInt16 *    outPart);


/*
 *  HandleControlClick()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern ControlPartCode 
HandleControlClick(
  ControlRef         inControl,
  Point              inWhere,
  EventModifiers     inModifiers,
  ControlActionUPP   inAction);         /* can be NULL */


/* Contextual Menu support in the Control Manager is only available on Carbon.  */
/* If the control didn't display a contextual menu (possibly because the point  */
/* was in a non-interesting part), the menuDisplayed output parameter will be   */
/* false. If the control did display a menu, menuDisplayed will be true.        */
/* This in on Carbon only                                                       */
/*
 *  HandleControlContextualMenuClick()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 9.0 and later
 */
extern OSStatus 
HandleControlContextualMenuClick(
  ControlRef   inControl,
  Point        inWhere,
  Boolean *    menuDisplayed);


/* Some complex controls (like Data Browser) require proper sequencing of       */
/* window activation and click processing. In some cases, the control might     */
/* want the window to be left inactive yet still handle the click, or vice-     */
/* versa. The GetControlClickActivation routine lets a control client ask the   */
/* control how it wishes to behave for a particular click.                      */
/* This in on Carbon only.                                                      */
/*
 *  GetControlClickActivation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 9.0 and later
 */
extern OSStatus 
GetControlClickActivation(
  ControlRef               inControl,
  Point                    inWhere,
  EventModifiers           inModifiers,
  ClickActivationResult *  outResult);



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Events (available only with Appearance 1.0 and later)                     */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  HandleControlKey()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern ControlPartCode 
HandleControlKey(
  ControlRef       inControl,
  SInt16           inKeyCode,
  SInt16           inCharCode,
  EventModifiers   inModifiers);


/*
 *  IdleControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern void 
IdleControls(WindowRef inWindow);




/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* ¥ Control Mouse Tracking (available with Carbon)                                     */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* The HandleControlSetCursor routine requests that a given control set the cursor to   */
/* something appropriate based on the mouse location.                                   */
/* If the control didn't want to set the cursor (because the point was in a             */
/* non-interesting part), the cursorWasSet output parameter will be false. If the       */
/* control did set the cursor, cursorWasSet will be true.                               */
/* Carbon only.                                                                         */
/*
 *  HandleControlSetCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 9.0 and later
 */
extern OSStatus 
HandleControlSetCursor(
  ControlRef       control,
  Point            localPoint,
  EventModifiers   modifiers,
  Boolean *        cursorWasSet);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Positioning                                                               */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  MoveControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
MoveControl(
  ControlRef   theControl,
  SInt16       h,
  SInt16       v);


/*
 *  SizeControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SizeControl(
  ControlRef   theControl,
  SInt16       w,
  SInt16       h);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Title                                                                     */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  SetControlTitle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetControlTitle(
  ControlRef         theControl,
  ConstStr255Param   title);


/*
 *  GetControlTitle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetControlTitle(
  ControlRef   theControl,
  Str255       title);


/*
 *  SetControlTitleWithCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetControlTitleWithCFString(
  ControlRef    inControl,
  CFStringRef   inString);


/*
 *  CopyControlTitleAsCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CopyControlTitleAsCFString(
  ControlRef     inControl,
  CFStringRef *  outString);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Value                                                                     */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  GetControlValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16 
GetControlValue(ControlRef theControl);


/*
 *  SetControlValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetControlValue(
  ControlRef   theControl,
  SInt16       newValue);


/*
 *  GetControlMinimum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16 
GetControlMinimum(ControlRef theControl);


/*
 *  SetControlMinimum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetControlMinimum(
  ControlRef   theControl,
  SInt16       newMinimum);


/*
 *  GetControlMaximum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16 
GetControlMaximum(ControlRef theControl);


/*
 *  SetControlMaximum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetControlMaximum(
  ControlRef   theControl,
  SInt16       newMaximum);



/* proportional scrolling/32-bit value support is new with Appearance 1.1*/

/*
 *  GetControlViewSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern SInt32 
GetControlViewSize(ControlRef theControl);


/*
 *  SetControlViewSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern void 
SetControlViewSize(
  ControlRef   theControl,
  SInt32       newViewSize);


/*
 *  GetControl32BitValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern SInt32 
GetControl32BitValue(ControlRef theControl);


/*
 *  SetControl32BitValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern void 
SetControl32BitValue(
  ControlRef   theControl,
  SInt32       newValue);


/*
 *  GetControl32BitMaximum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern SInt32 
GetControl32BitMaximum(ControlRef theControl);


/*
 *  SetControl32BitMaximum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern void 
SetControl32BitMaximum(
  ControlRef   theControl,
  SInt32       newMaximum);


/*
 *  GetControl32BitMinimum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern SInt32 
GetControl32BitMinimum(ControlRef theControl);


/*
 *  SetControl32BitMinimum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern void 
SetControl32BitMinimum(
  ControlRef   theControl,
  SInt32       newMinimum);


/*
    IsValidControlHandle will tell you if the handle you pass in belongs to a control
    the Control Manager knows about. It does not sanity check the data in the control.
*/

/*
 *  IsValidControlHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern Boolean 
IsValidControlHandle(ControlRef theControl);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* ¥ Control IDs                                                                        */
/* Carbon only.                                                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlID {
  OSType              signature;
  SInt32              id;
};
typedef struct ControlID                ControlID;
/*
 *  SetControlID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetControlID(
  ControlRef         inControl,
  const ControlID *  inID);


/*
 *  GetControlID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetControlID(
  ControlRef   inControl,
  ControlID *  outID);


/*
 *  GetControlByID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetControlByID(
  WindowRef          inWindow,
  const ControlID *  inID,
  ControlRef *       outControl);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* ¥ Control Command IDs                                                                    */
/* Carbon only.                                                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  SetControlCommandID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetControlCommandID(
  ControlRef   inControl,
  UInt32       inCommandID);


/*
 *  GetControlCommandID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetControlCommandID(
  ControlRef   inControl,
  UInt32 *     outCommandID);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* ¥ Control Identification                                                             */
/* Carbon only.                                                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
struct ControlKind {
  OSType              signature;
  OSType              kind;
};
typedef struct ControlKind              ControlKind;

/*
 *  Discussion:
 *    Control signature kind
 */

  /*
   * Signature of all system controls.
   */
enum {
  kControlKindSignatureApple    = 'appl'
};

/*
 *  GetControlKind()
 *  
 *  Summary:
 *    Returns the kind of the given control.
 *  
 *  Discussion:
 *    GetControlKind allows you to query the kind of any control. This
 *    function is only available in Mac OS X.
 *  
 *  Parameters:
 *    
 *    inControl:
 *      The ControlRef to find the kind of.
 *    
 *    outControlKind:
 *      On successful exit, this will contain the control signature and
 *      kind. See ControlDefinitions.h for the kinds of each system
 *      control.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetControlKind(
  ControlRef     inControl,
  ControlKind *  outControlKind);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* ¥ Properties                                                                         */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  kControlPropertyPersistent    = 0x00000001 /* whether this property gets saved when flattening the control*/
};

/*
 *  GetControlProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern OSStatus 
GetControlProperty(
  ControlRef   control,
  OSType       propertyCreator,
  OSType       propertyTag,
  UInt32       bufferSize,
  UInt32 *     actualSize,
  void *       propertyBuffer);


/*
 *  GetControlPropertySize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern OSStatus 
GetControlPropertySize(
  ControlRef   control,
  OSType       propertyCreator,
  OSType       propertyTag,
  UInt32 *     size);


/*
 *  SetControlProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern OSStatus 
SetControlProperty(
  ControlRef   control,
  OSType       propertyCreator,
  OSType       propertyTag,
  UInt32       propertySize,
  void *       propertyData);


/*
 *  RemoveControlProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern OSStatus 
RemoveControlProperty(
  ControlRef   control,
  OSType       propertyCreator,
  OSType       propertyTag);


/*
 *  GetControlPropertyAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetControlPropertyAttributes(
  ControlRef   control,
  OSType       propertyCreator,
  OSType       propertyTag,
  UInt32 *     attributes);


/*
 *  ChangeControlPropertyAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ChangeControlPropertyAttributes(
  ControlRef   control,
  OSType       propertyCreator,
  OSType       propertyTag,
  UInt32       attributesToSet,
  UInt32       attributesToClear);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Regions (Appearance 1.1 or later)                                         */
/*                                                                                      */
/*  See the discussion on meta-parts in this header for more information                */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  GetControlRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 8.5 and later
 */
extern OSStatus 
GetControlRegion(
  ControlRef        inControl,
  ControlPartCode   inPart,
  RgnHandle         outRegion);




/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Variant                                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  GetControlVariant()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ControlVariant 
GetControlVariant(ControlRef theControl);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Action                                                                    */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  SetControlAction()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetControlAction(
  ControlRef         theControl,
  ControlActionUPP   actionProc);


/*
 *  GetControlAction()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ControlActionUPP 
GetControlAction(ControlRef theControl);


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* ¥ Control Accessors                                                                  */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  SetControlReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetControlReference(
  ControlRef   theControl,
  SInt32       data);


/*
 *  GetControlReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt32 
GetControlReference(ControlRef theControl);


#if !OPAQUE_TOOLBOX_STRUCTS
/*
 *  GetAuxiliaryControlRecord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
GetAuxiliaryControlRecord(
  ControlRef      theControl,
  AuxCtlHandle *  acHndl);


#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

/*
 *  SetControlColor()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Hierarchy (Appearance 1.0 and later only)                                 */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  SendControlMessage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern SInt32 
SendControlMessage(
  ControlRef   inControl,
  SInt16       inMessage,
  void *       inParam);


/*
 *  DumpControlHierarchy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
DumpControlHierarchy(
  WindowRef       inWindow,
  const FSSpec *  inDumpFile);


/*
 *  CreateRootControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
CreateRootControl(
  WindowRef     inWindow,
  ControlRef *  outControl);      /* can be NULL */


/*
 *  GetRootControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetRootControl(
  WindowRef     inWindow,
  ControlRef *  outControl);


/*
 *  EmbedControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
EmbedControl(
  ControlRef   inControl,
  ControlRef   inContainer);


/*
 *  AutoEmbedControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
AutoEmbedControl(
  ControlRef   inControl,
  WindowRef    inWindow);


/*
 *  GetSuperControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetSuperControl(
  ControlRef    inControl,
  ControlRef *  outParent);


/*
 *  CountSubControls()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
CountSubControls(
  ControlRef   inControl,
  UInt16 *     outNumChildren);


/*
 *  GetIndexedSubControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetIndexedSubControl(
  ControlRef    inControl,
  UInt16        inIndex,
  ControlRef *  outSubControl);


/*
 *  SetControlSupervisor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetControlSupervisor(
  ControlRef   inControl,
  ControlRef   inBoss);




/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Keyboard Focus (available only with Appearance 1.0 and later)                     */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*
 *  GetKeyboardFocus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetKeyboardFocus(
  WindowRef     inWindow,
  ControlRef *  outControl);


/*
 *  SetKeyboardFocus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetKeyboardFocus(
  WindowRef          inWindow,
  ControlRef         inControl,
  ControlFocusPart   inPart);


/*
 *  AdvanceKeyboardFocus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
AdvanceKeyboardFocus(WindowRef inWindow);


/*
 *  ReverseKeyboardFocus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
ReverseKeyboardFocus(WindowRef inWindow);


/*
 *  ClearKeyboardFocus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
ClearKeyboardFocus(WindowRef inWindow);




/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Data (available only with Appearance 1.0 and later)                       */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/

/*
 *  GetControlFeatures()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetControlFeatures(
  ControlRef   inControl,
  UInt32 *     outFeatures);


/*
 *  SetControlData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SetControlData(
  ControlRef        inControl,
  ControlPartCode   inPart,
  ResType           inTagName,
  Size              inSize,
  const void *      inData);


/*
 *  GetControlData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetControlData(
  ControlRef        inControl,
  ControlPartCode   inPart,
  ResType           inTagName,
  Size              inBufferSize,
  void *            inBuffer,
  Size *            outActualSize);


/*
 *  GetControlDataSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetControlDataSize(
  ControlRef        inControl,
  ControlPartCode   inPart,
  ResType           inTagName,
  Size *            outMaxSize);



/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ Control Drag & Drop                                                               */
/*      Carbon only.                                                                    */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/* some simple redefinitions of the similar values found in the Drag header*/
enum {
  kDragTrackingEnterControl     = 2,
  kDragTrackingInControl        = 3,
  kDragTrackingLeaveControl     = 4
};

/*
 *  HandleControlDragTracking()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 9.0 and later
 */
extern OSStatus 
HandleControlDragTracking(
  ControlRef            inControl,
  DragTrackingMessage   inMessage,
  DragReference         inDrag,
  Boolean *             outLikesDrag);


/*
 *  HandleControlDragReceive()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 9.0 and later
 */
extern OSStatus 
HandleControlDragReceive(
  ControlRef      inControl,
  DragReference   inDrag);


/*
 *  SetControlDragTrackingEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 9.0 and later
 */
extern OSStatus 
SetControlDragTrackingEnabled(
  ControlRef   theControl,
  Boolean      tracks);


/*
 *  IsControlDragTrackingEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 9.0 and later
 */
extern OSStatus 
IsControlDragTrackingEnabled(
  ControlRef   theControl,
  Boolean *    tracks);


/*
 *  SetAutomaticControlDragTrackingEnabledForWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 9.0 and later
 */
extern OSStatus 
SetAutomaticControlDragTrackingEnabledForWindow(
  WindowRef   theWindow,
  Boolean     tracks);


/*
 *  IsAutomaticControlDragTrackingEnabledForWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ControlsLib 9.0 and later
 */
extern OSStatus 
IsAutomaticControlDragTrackingEnabledForWindow(
  WindowRef   theWindow,
  Boolean *   tracks);




/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ C Glue                                                                            */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
#if CALL_NOT_IN_CARBON
/*
 *  dragcontrol()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  newcontrol()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  findcontrol()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  getcontroltitle()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  setcontroltitle()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  trackcontrol()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  testcontrol()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


#endif  /* CALL_NOT_IN_CARBON */

#if OLDROUTINENAMES
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
/*  ¥ OLDROUTINENAMES                                                                   */
/*ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ*/
enum {
  useWFont                      = kControlUsesOwningWindowsFontVariant
};

enum {
  inThumb                       = kControlIndicatorPart,
  kNoHiliteControlPart          = kControlNoPart,
  kInIndicatorControlPart       = kControlIndicatorPart,
  kReservedControlPart          = kControlDisabledPart,
  kControlInactiveControlPart   = kControlInactivePart
};


#define SetCTitle(theControl, title) SetControlTitle(theControl, title)
#define GetCTitle(theControl, title) GetControlTitle(theControl, title)
#define UpdtControl(theWindow, updateRgn) UpdateControls(theWindow, updateRgn)
#define SetCtlValue(theControl, theValue) SetControlValue(theControl, theValue)
#define GetCtlValue(theControl) GetControlValue(theControl)
#define SetCtlMin(theControl, minValue) SetControlMinimum(theControl, minValue)
#define GetCtlMin(theControl) GetControlMinimum(theControl)
#define SetCtlMax(theControl, maxValue) SetControlMaximum(theControl, maxValue)
#define GetCtlMax(theControl) GetControlMaximum(theControl)
#define GetAuxCtl(theControl, acHndl) GetAuxiliaryControlRecord(theControl, acHndl)
#define SetCRefCon(theControl, data) SetControlReference(theControl, data)
#define GetCRefCon(theControl) GetControlReference(theControl)
#define SetCtlAction(theControl, actionProc) SetControlAction(theControl, actionProc)
#define GetCtlAction(theControl) GetControlAction(theControl)
#define SetCtlColor(theControl, newColorTable) SetControlColor(theControl, newColorTable)
#define GetCVariant(theControl) GetControlVariant(theControl)
#define getctitle(theControl, title) getcontroltitle(theControl, title)
#define setctitle(theControl, title) setcontroltitle(theControl, title)
#endif  /* OLDROUTINENAMES */

/* Getters */
/*
 *  GetControlBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Rect * 
GetControlBounds(
  ControlRef   control,
  Rect *       bounds);


/*
 *  IsControlHilited()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Boolean 
IsControlHilited(ControlRef control);


/*
 *  GetControlHilite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern UInt16 
GetControlHilite(ControlRef control);


/*
 *  GetControlOwner()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern WindowRef 
GetControlOwner(ControlRef control);


/*
 *  GetControlDataHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern Handle 
GetControlDataHandle(ControlRef control);


/*
 *  GetControlPopupMenuHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern MenuRef 
GetControlPopupMenuHandle(ControlRef control);


#define GetControlPopupMenuRef GetControlPopupMenuHandle
/*
 *  GetControlPopupMenuID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern short 
GetControlPopupMenuID(ControlRef control);


/* Setters */
/*
 *  SetControlDataHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetControlDataHandle(
  ControlRef   control,
  Handle       dataHandle);


/*
 *  SetControlBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetControlBounds(
  ControlRef    control,
  const Rect *  bounds);


/*
 *  SetControlPopupMenuHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetControlPopupMenuHandle(
  ControlRef   control,
  MenuRef      popupMenu);


#define SetControlPopupMenuRef SetControlPopupMenuHandle
/*
 *  SetControlPopupMenuID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
SetControlPopupMenuID(
  ControlRef   control,
  short        menuID);




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

#endif /* __CONTROLS__ */


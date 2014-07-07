/*
     File:       HIToolbox/Dialogs.h
 
     Contains:   Dialog Manager interfaces.
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1985-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __DIALOGS__
#define __DIALOGS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
#endif

#ifndef __MACWINDOWS__
#include <HIToolbox/MacWindows.h>
#endif

#ifndef __TEXTEDIT__
#include <HIToolbox/TextEdit.h>
#endif

#ifndef __CONTROLS__
#include <HIToolbox/Controls.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
#endif

#ifndef __CARBONEVENTS__
#include <HIToolbox/CarbonEvents.h>
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

enum {
                                        /* new, more standard names for dialog item types*/
  kControlDialogItem            = 4,
  kButtonDialogItem             = kControlDialogItem | 0,
  kCheckBoxDialogItem           = kControlDialogItem | 1,
  kRadioButtonDialogItem        = kControlDialogItem | 2,
  kResourceControlDialogItem    = kControlDialogItem | 3,
  kStaticTextDialogItem         = 8,
  kEditTextDialogItem           = 16,
  kIconDialogItem               = 32,
  kPictureDialogItem            = 64,
  kUserDialogItem               = 0,
  kHelpDialogItem               = 1,
  kItemDisableBit               = 128
};

enum {
                                        /* old names for dialog item types*/
  ctrlItem                      = 4,
  btnCtrl                       = 0,
  chkCtrl                       = 1,
  radCtrl                       = 2,
  resCtrl                       = 3,
  statText                      = 8,
  editText                      = 16,
  iconItem                      = 32,
  picItem                       = 64,
  userItem                      = 0,
  itemDisable                   = 128
};

enum {
                                        /* standard dialog item numbers*/
  kStdOkItemIndex               = 1,
  kStdCancelItemIndex           = 2,    /* old names*/
  ok                            = kStdOkItemIndex,
  cancel                        = kStdCancelItemIndex
};

enum {
                                        /* standard icon resource id's    */
  kStopIcon                     = 0,
  kNoteIcon                     = 1,
  kCautionIcon                  = 2,    /* old names*/
  stopIcon                      = kStopIcon,
  noteIcon                      = kNoteIcon,
  cautionIcon                   = kCautionIcon
};




#if OLDROUTINENAMES
/*
   These constants lived briefly on ETO 16.  They suggest
   that there is only one index you can use for the OK 
   item, which is not true.  You can put the ok item 
   anywhere you want in the DITL.
*/
enum {
  kOkItemIndex                  = 1,
  kCancelItemIndex              = 2
};

#endif  /* OLDROUTINENAMES */

/*  Dialog Item List Manipulation Constants */
typedef SInt16                          DITLMethod;
enum {
  overlayDITL                   = 0,
  appendDITLRight               = 1,
  appendDITLBottom              = 2
};

typedef SInt16                          StageList;
/* DialogPtr is obsolete. Use DialogRef instead.*/
typedef DialogPtr                       DialogRef;
#if !OPAQUE_TOOLBOX_STRUCTS
struct DialogRecord {
  WindowRecord        window;                 /* in Carbon use GetDialogWindow or GetDialogPort*/
  Handle              items;                  /* in Carbon use Get/SetDialogItem*/
  TEHandle            textH;                  /* in Carbon use GetDialogTextEditHandle*/
  SInt16              editField;              /* in Carbon use SelectDialogItemText/GetDialogKeyboardFocusItem*/
  SInt16              editOpen;               /* not available in Carbon */
  SInt16              aDefItem;               /* in Carbon use Get/SetDialogDefaultItem*/
};
typedef struct DialogRecord             DialogRecord;
typedef DialogRecord *                  DialogPeek;
#endif  /* !OPAQUE_TOOLBOX_STRUCTS */

struct DialogTemplate {
  Rect                boundsRect;
  SInt16              procID;
  Boolean             visible;
  Boolean             filler1;
  Boolean             goAwayFlag;
  Boolean             filler2;
  SInt32              refCon;
  SInt16              itemsID;
  Str255              title;
};
typedef struct DialogTemplate           DialogTemplate;
typedef DialogTemplate *                DialogTPtr;
typedef DialogTPtr *                    DialogTHndl;
struct AlertTemplate {
  Rect                boundsRect;
  SInt16              itemsID;
  StageList           stages;
};
typedef struct AlertTemplate            AlertTemplate;
typedef AlertTemplate *                 AlertTPtr;
typedef AlertTPtr *                     AlertTHndl;
/* new type abstractions for the dialog manager */
typedef SInt16                          DialogItemIndexZeroBased;
typedef SInt16                          DialogItemIndex;
typedef SInt16                          DialogItemType;
/* dialog manager callbacks */
typedef CALLBACK_API( void , SoundProcPtr )(SInt16 soundNumber);
typedef CALLBACK_API( Boolean , ModalFilterProcPtr )(DialogRef theDialog, EventRecord *theEvent, DialogItemIndex *itemHit);
/* ModalFilterYDProcPtr was previously in StandardFile.h */
typedef CALLBACK_API( Boolean , ModalFilterYDProcPtr )(DialogRef theDialog, EventRecord *theEvent, short *itemHit, void *yourDataPtr);
typedef CALLBACK_API( void , UserItemProcPtr )(DialogRef theDialog, DialogItemIndex itemNo);
typedef STACK_UPP_TYPE(SoundProcPtr)                            SoundUPP;
typedef STACK_UPP_TYPE(ModalFilterProcPtr)                      ModalFilterUPP;
typedef STACK_UPP_TYPE(ModalFilterYDProcPtr)                    ModalFilterYDUPP;
typedef STACK_UPP_TYPE(UserItemProcPtr)                         UserItemUPP;
/*
 *  NewSoundUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  NewModalFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ModalFilterUPP
NewModalFilterUPP(ModalFilterProcPtr userRoutine);

/*
 *  NewModalFilterYDUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ModalFilterYDUPP
NewModalFilterYDUPP(ModalFilterYDProcPtr userRoutine);

/*
 *  NewUserItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern UserItemUPP
NewUserItemUPP(UserItemProcPtr userRoutine);

/*
 *  DisposeSoundUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeModalFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeModalFilterUPP(ModalFilterUPP userUPP);

/*
 *  DisposeModalFilterYDUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeModalFilterYDUPP(ModalFilterYDUPP userUPP);

/*
 *  DisposeUserItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeUserItemUPP(UserItemUPP userUPP);

/*
 *  InvokeSoundUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeModalFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeModalFilterUPP(
  DialogRef          theDialog,
  EventRecord *      theEvent,
  DialogItemIndex *  itemHit,
  ModalFilterUPP     userUPP);

/*
 *  InvokeModalFilterYDUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeModalFilterYDUPP(
  DialogRef         theDialog,
  EventRecord *     theEvent,
  short *           itemHit,
  void *            yourDataPtr,
  ModalFilterYDUPP  userUPP);

/*
 *  InvokeUserItemUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeUserItemUPP(
  DialogRef        theDialog,
  DialogItemIndex  itemNo,
  UserItemUPP      userUPP);


/*
  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    ¥ Following types are valid with Appearance 1.0 and later
  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/
enum {
                                        /* Alert types to pass into StandardAlert */
  kAlertStopAlert               = 0,
  kAlertNoteAlert               = 1,
  kAlertCautionAlert            = 2,
  kAlertPlainAlert              = 3
};

typedef SInt16                          AlertType;
enum {
  kAlertDefaultOKText           = -1,   /* "OK"*/
  kAlertDefaultCancelText       = -1,   /* "Cancel"*/
  kAlertDefaultOtherText        = -1    /* "Don't Save"*/
};

/* StandardAlert alert button numbers */
enum {
  kAlertStdAlertOKButton        = 1,
  kAlertStdAlertCancelButton    = 2,
  kAlertStdAlertOtherButton     = 3,
  kAlertStdAlertHelpButton      = 4
};

enum {
                                        /* Dialog Flags for use in NewFeaturesDialog or dlgx resource */
  kDialogFlagsUseThemeBackground = (1 << 0),
  kDialogFlagsUseControlHierarchy = (1 << 1),
  kDialogFlagsHandleMovableModal = (1 << 2),
  kDialogFlagsUseThemeControls  = (1 << 3)
};

enum {
                                        /* Alert Flags for use in alrx resource */
  kAlertFlagsUseThemeBackground = (1 << 0),
  kAlertFlagsUseControlHierarchy = (1 << 1),
  kAlertFlagsAlertIsMovable     = (1 << 2),
  kAlertFlagsUseThemeControls   = (1 << 3)
};

/* For dftb resource */
enum {
  kDialogFontNoFontStyle        = 0,
  kDialogFontUseFontMask        = 0x0001,
  kDialogFontUseFaceMask        = 0x0002,
  kDialogFontUseSizeMask        = 0x0004,
  kDialogFontUseForeColorMask   = 0x0008,
  kDialogFontUseBackColorMask   = 0x0010,
  kDialogFontUseModeMask        = 0x0020,
  kDialogFontUseJustMask        = 0x0040,
  kDialogFontUseAllMask         = 0x00FF,
  kDialogFontAddFontSizeMask    = 0x0100,
  kDialogFontUseFontNameMask    = 0x0200,
  kDialogFontAddToMetaFontMask  = 0x0400
};

/* Also for dftb resource. This one is available in Mac OS X or later. */
/* It corresponds directly to kControlUseThemeFontIDMask from Controls.h. */
enum {
  kDialogFontUseThemeFontIDMask = 0x0080
};

struct AlertStdAlertParamRec {
  Boolean             movable;                /* Make alert movable modal */
  Boolean             helpButton;             /* Is there a help button? */
  ModalFilterUPP      filterProc;             /* Event filter */
  ConstStringPtr      defaultText;            /* Text for button in OK position */
  ConstStringPtr      cancelText;             /* Text for button in cancel position */
  ConstStringPtr      otherText;              /* Text for button in left position */
  SInt16              defaultButton;          /* Which button behaves as the default */
  SInt16              cancelButton;           /* Which one behaves as cancel (can be 0) */
  UInt16              position;               /* Position (kWindowDefaultPosition in this case */
                                              /* equals kWindowAlertPositionParentWindowScreen) */
};
typedef struct AlertStdAlertParamRec    AlertStdAlertParamRec;
typedef AlertStdAlertParamRec *         AlertStdAlertParamPtr;
enum {
  kHICommandOther               = 'othr' /* sent by standard sheet dialogs when the "other" button is pressed */
};

enum {
  kStdCFStringAlertVersionOne   = 1     /* current version of AlertStdCFStringAlertParamRec */
};


/*
 *  Summary:
 *    Flags to CreateStandardAlert that are specified in the
 *    AlertStdCFStringAlertParamRec.flags field.
 */

  /*
   * Applies to StandardSheet only. Do not dispose of the sheet window
   * after closing it; allows the sheet to be re-used again in a later
   * call to ShowSheetWindow.
   */
enum {
  kStdAlertDoNotDisposeSheet    = 1 << 0,

  /*
   * Applies to StandardSheet only. Causes the sheet window to be
   * hidden immediately without animation effects when the default
   * button is chosen by the user.
   */
  kStdAlertDoNotAnimateOnDefault = 1 << 1,

  /*
   * Applies to StandardSheet only. Causes the sheet window to be
   * hidden immediately without animation effects when the cancel
   * button is chosen by the user.
   */
  kStdAlertDoNotAnimateOnCancel = 1 << 2,

  /*
   * Applies to StandardSheet only. Causes the sheet window to be
   * hidden immediately without animation effects when the other button
   * is chosen by the user.
   */
  kStdAlertDoNotAnimateOnOther  = 1 << 3
};

struct AlertStdCFStringAlertParamRec {
  UInt32              version;                /* kStdCFStringAlertVersionOne */
  Boolean             movable;                /* Make alert movable modal */
  Boolean             helpButton;             /* Is there a help button? */
  CFStringRef         defaultText;            /* Text for button in OK position */
  CFStringRef         cancelText;             /* Text for button in cancel position */
  CFStringRef         otherText;              /* Text for button in left position */
  SInt16              defaultButton;          /* Which button behaves as the default */
  SInt16              cancelButton;           /* Which one behaves as cancel (can be 0) */
  UInt16              position;               /* Position (kWindowDefaultPosition in this case */
                                              /* equals kWindowAlertPositionParentWindowScreen) */
  OptionBits          flags;                  /* Options for the behavior of the alert or sheet */
};
typedef struct AlertStdCFStringAlertParamRec AlertStdCFStringAlertParamRec;
typedef AlertStdCFStringAlertParamRec * AlertStdCFStringAlertParamPtr;
/* ÑÑÑ end Appearance 1.0 or later stuff*/


/*
    NOTE: Code running under MultiFinder or System 7.0 or newer
    should always pass NULL to InitDialogs.
*/
/*
 *  InitDialogs()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  ErrorSound()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  NewDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern DialogRef 
NewDialog(
  void *             dStorage,
  const Rect *       boundsRect,
  ConstStr255Param   title,
  Boolean            visible,
  SInt16             procID,
  WindowRef          behind,
  Boolean            goAwayFlag,
  SInt32             refCon,
  Handle             items);


/*
 *  GetNewDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern DialogRef 
GetNewDialog(
  SInt16      dialogID,
  void *      dStorage,
  WindowRef   behind);


/*
 *  NewColorDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern DialogRef 
NewColorDialog(
  void *             dStorage,
  const Rect *       boundsRect,
  ConstStr255Param   title,
  Boolean            visible,
  SInt16             procID,
  WindowRef          behind,
  Boolean            goAwayFlag,
  SInt32             refCon,
  Handle             items);


/*
 *  CloseDialog()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  DisposeDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeDialog(DialogRef theDialog);


/*
 *  ModalDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ModalDialog(
  ModalFilterUPP     modalFilter,
  DialogItemIndex *  itemHit);


/*
 *  IsDialogEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
IsDialogEvent(const EventRecord * theEvent);


/*
 *  DialogSelect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
DialogSelect(
  const EventRecord *  theEvent,
  DialogRef *          theDialog,
  DialogItemIndex *    itemHit);


/*
 *  DrawDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DrawDialog(DialogRef theDialog);


/*
 *  UpdateDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
UpdateDialog(
  DialogRef   theDialog,
  RgnHandle   updateRgn);


/*
 *  HideDialogItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
HideDialogItem(
  DialogRef         theDialog,
  DialogItemIndex   itemNo);


/*
 *  ShowDialogItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ShowDialogItem(
  DialogRef         theDialog,
  DialogItemIndex   itemNo);


/*
 *  FindDialogItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern DialogItemIndexZeroBased 
FindDialogItem(
  DialogRef   theDialog,
  Point       thePt);


/*
 *  DialogCut()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DialogCut(DialogRef theDialog);


/*
 *  DialogPaste()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DialogPaste(DialogRef theDialog);


/*
 *  DialogCopy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DialogCopy(DialogRef theDialog);


/*
 *  DialogDelete()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DialogDelete(DialogRef theDialog);


/*
 *  Alert()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern DialogItemIndex 
Alert(
  SInt16           alertID,
  ModalFilterUPP   modalFilter);


/*
 *  StopAlert()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern DialogItemIndex 
StopAlert(
  SInt16           alertID,
  ModalFilterUPP   modalFilter);


/*
 *  NoteAlert()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern DialogItemIndex 
NoteAlert(
  SInt16           alertID,
  ModalFilterUPP   modalFilter);


/*
 *  CautionAlert()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern DialogItemIndex 
CautionAlert(
  SInt16           alertID,
  ModalFilterUPP   modalFilter);


/*
 *  GetDialogItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetDialogItem(
  DialogRef         theDialog,
  DialogItemIndex   itemNo,
  DialogItemType *  itemType,
  Handle *          item,
  Rect *            box);


/*
 *  SetDialogItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetDialogItem(
  DialogRef         theDialog,
  DialogItemIndex   itemNo,
  DialogItemType    itemType,
  Handle            item,
  const Rect *      box);


/*
 *  ParamText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ParamText(
  ConstStr255Param   param0,
  ConstStr255Param   param1,
  ConstStr255Param   param2,
  ConstStr255Param   param3);


/*
 *  SelectDialogItemText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SelectDialogItemText(
  DialogRef         theDialog,
  DialogItemIndex   itemNo,
  SInt16            strtSel,
  SInt16            endSel);


/*
 *  GetDialogItemText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetDialogItemText(
  Handle   item,
  Str255   text);


/*
 *  SetDialogItemText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetDialogItemText(
  Handle             item,
  ConstStr255Param   text);


/*
 *  GetAlertStage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16 
GetAlertStage(void);


/*
 *  SetDialogFont()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetDialogFont(SInt16 fontNum);


/*
 *  ResetAlertStage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ResetAlertStage(void);


/* APIs in Carbon*/
/*
 *  GetParamText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
GetParamText(
  StringPtr   param0,
  StringPtr   param1,
  StringPtr   param2,
  StringPtr   param3);



/*
 *  newdialog()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  newcolordialog()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  paramtext()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  getdialogitemtext()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  setdialogitemtext()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  finddialogitem()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  AppendDITL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
AppendDITL(
  DialogRef    theDialog,
  Handle       theHandle,
  DITLMethod   method);


/*
 *  CountDITL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern DialogItemIndex 
CountDITL(DialogRef theDialog);


/*
 *  ShortenDITL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
ShortenDITL(
  DialogRef         theDialog,
  DialogItemIndex   numberItems);


/*
 *  InsertDialogItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
InsertDialogItem(
  DialogRef         theDialog,
  DialogItemIndex   afterItem,
  DialogItemType    itemType,
  Handle            itemHandle,
  const Rect *      box);


/*
 *  RemoveDialogItems()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RemoveDialogItems(
  DialogRef         theDialog,
  DialogItemIndex   itemNo,
  DialogItemIndex   amountToRemove,
  Boolean           disposeItemData);


/*
 *  StdFilterProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
StdFilterProc(
  DialogRef          theDialog,
  EventRecord *      event,
  DialogItemIndex *  itemHit);


/*
 *  GetStdFilterProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetStdFilterProc(ModalFilterUPP * theProc);


/*
 *  SetDialogDefaultItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetDialogDefaultItem(
  DialogRef         theDialog,
  DialogItemIndex   newItem);


/*
 *  SetDialogCancelItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetDialogCancelItem(
  DialogRef         theDialog,
  DialogItemIndex   newItem);


/*
 *  SetDialogTracksCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetDialogTracksCursor(
  DialogRef   theDialog,
  Boolean     tracks);




/*
  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    ¥ Appearance Dialog Routines (available only with Appearance 1.0 and later)
  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/

/*
 *  NewFeaturesDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern DialogRef 
NewFeaturesDialog(
  void *             inStorage,
  const Rect *       inBoundsRect,
  ConstStr255Param   inTitle,
  Boolean            inIsVisible,
  SInt16             inProcID,
  WindowRef          inBehind,
  Boolean            inGoAwayFlag,
  SInt32             inRefCon,
  Handle             inItemListHandle,
  UInt32             inFlags);


/*
 *  AutoSizeDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
AutoSizeDialog(DialogRef inDialog);


/*
    Regarding StandardAlert and constness:
    Even though the inAlertParam parameter is marked const here, there was
    a chance Dialog Manager would modify it on versions of Mac OS prior to 9.
*/
/*
 *  StandardAlert()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
StandardAlert(
  AlertType                      inAlertType,
  ConstStr255Param               inError,
  ConstStr255Param               inExplanation,
  const AlertStdAlertParamRec *  inAlertParam,        /* can be NULL */
  SInt16 *                       outItemHit);


/* CFString-based StandardAlert and StandardSheet APIs are only available on Mac OS X and later*/

/*
 *  GetStandardAlertDefaultParams()
 *  
 *  Summary:
 *    Fills out an AlertStdCFStringAlertParamRec with default values: -
 *      not movable -   no help button -   default button with title
 *    "OK" -   no cancel or other buttons
 *  
 *  Parameters:
 *    
 *    param:
 *      The parameter block to initialize.
 *    
 *    version:
 *      The parameter block version; pass kStdCFStringAlertVersionOne.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetStandardAlertDefaultParams(
  AlertStdCFStringAlertParamPtr   param,
  UInt32                          version);


/*
 *  CreateStandardAlert()
 *  
 *  Summary:
 *    Creates an alert containing standard elements and using standard
 *    formatting rules.
 *  
 *  Discussion:
 *    CreateStandardAlert should be used in conjunction with
 *    RunStandardAlert. After CreateStandardAlert returns, the alert is
 *    still invisible. RunStandardAlert will show the alert and run a
 *    modal dialog loop to process events in the alert.
 *  
 *  Parameters:
 *    
 *    alertType:
 *      The type of alert to create.
 *    
 *    error:
 *      The error string to display.
 *    
 *    explanation:
 *      The explanation string to display. May be NULL or empty to
 *      display no explanation.
 *    
 *    param:
 *      The parameter block describing how to create the alert. May be
 *      NULL.
 *    
 *    outAlert:
 *      On exit, contains the new alert.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateStandardAlert(
  AlertType                              alertType,
  CFStringRef                            error,
  CFStringRef                            explanation,       /* can be NULL */
  const AlertStdCFStringAlertParamRec *  param,             /* can be NULL */
  DialogRef *                            outAlert);


/*
 *  RunStandardAlert()
 *  
 *  Summary:
 *    Shows and runs a standard alert using a modal dialog loop.
 *  
 *  Parameters:
 *    
 *    inAlert:
 *      The alert to display.
 *    
 *    filterProc:
 *      An event filter function for handling events that do not apply
 *      to the alert. May be NULL.
 *    
 *    outItemHit:
 *      On exit, contains the item index of the button that was pressed
 *      to close the alert.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RunStandardAlert(
  DialogRef          inAlert,
  ModalFilterUPP     filterProc,       /* can be NULL */
  DialogItemIndex *  outItemHit);


/*
 *  CreateStandardSheet()
 *  
 *  Summary:
 *    Creates an alert containing standard elements and using standard
 *    formatting rules, and prepares it to be displayed as a sheet.
 *  
 *  Discussion:
 *    CreateStandardSheet should be used in conjunction with
 *    ShowSheetWindow. After CreateStandardSheet returns, the alert is
 *    still invisible. ShowSheetWindow will show the alert and then
 *    return. Events in the sheet are handled asynchronously; the
 *    application should be prepared for the sheet window to be part of
 *    its windowlist while running its own event loop. When a button in
 *    the sheet is pressed, the EventTargetRef passed to
 *    CreateStandardSheet will receive a command event with one of the
 *    command IDs kHICommandOK, kHICommandCancel, or kHICommandOther.
 *    The sheet is closed before the command is sent.
 *  
 *  Parameters:
 *    
 *    alertType:
 *      The type of alert to create.
 *    
 *    error:
 *      The error string to display.
 *    
 *    explanation:
 *      The explanation string to display. May be NULL or empty to
 *      display no explanation.
 *    
 *    param:
 *      The parameter block describing how to create the alert. May be
 *      NULL.
 *    
 *    notifyTarget:
 *      The event target to be notified when the sheet is closed. The
 *      caller should install an event handler on this target for the
 *      [kEventClassCommand, kEventProcessCommand] event.
 *    
 *    outSheet:
 *      On exit, contains the new alert.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateStandardSheet(
  AlertType                              alertType,
  CFStringRef                            error,
  CFStringRef                            explanation,        /* can be NULL */
  const AlertStdCFStringAlertParamRec *  param,              /* can be NULL */
  EventTargetRef                         notifyTarget,
  DialogRef *                            outSheet);


/*
 *  CloseStandardSheet()
 *  
 *  Summary:
 *    Closes a standard sheet dialog and releases the dialog data
 *    structures.
 *  
 *  Discussion:
 *    CloseStandardSheet is meant to be used when you need to remove a
 *    sheet because of a higher-priority request to close the sheet's
 *    document window. For example, you might have a Save Changes sheet
 *    open on a document window. Meanwhile, the user drags the document
 *    into the trash. When your application sees that the document has
 *    been moved to the trash, it knows that it should close the
 *    document window, but first it needs to close the sheet.
 *    CloseStandardSheet should not be used by your Carbon event
 *    handler in response to a click in one of the sheet buttons; the
 *    Dialog Manager will close the sheet automatically in that case.
 *    If kStdAlertDoNotDisposeSheet was specified when the sheet was
 *    created, the sheet dialog will be hidden but not released, and
 *    you can reuse the sheet later.
 *  
 *  Parameters:
 *    
 *    inSheet:
 *      The sheet to close.
 *    
 *    inResultCommand:
 *      This command, if not zero, will be sent to the EventTarget
 *      specified when the sheet was created.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CloseStandardSheet(
  DialogRef   inSheet,
  UInt32      inResultCommand);


/*
 *  GetDialogItemAsControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
GetDialogItemAsControl(
  DialogRef     inDialog,
  SInt16        inItemNo,
  ControlRef *  outControl);


/*
 *  MoveDialogItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
MoveDialogItem(
  DialogRef   inDialog,
  SInt16      inItemNo,
  SInt16      inHoriz,
  SInt16      inVert);


/*
 *  SizeDialogItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppearanceLib 1.0 and later
 */
extern OSErr 
SizeDialogItem(
  DialogRef   inDialog,
  SInt16      inItemNo,
  SInt16      inWidth,
  SInt16      inHeight);


/*
 *  AppendDialogItemList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DialogsLib 8.5 and later
 */
extern OSErr 
AppendDialogItemList(
  DialogRef    dialog,
  SInt16       ditlID,
  DITLMethod   method);


/*
  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    ¥ Dialog Routines available only with Appearance 1.1 and later
  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/

/*
 *  SetDialogTimeout()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DialogsLib 8.5 and later
 */
extern OSStatus 
SetDialogTimeout(
  DialogRef   inDialog,
  SInt16      inButtonToPress,
  UInt32      inSecondsToWait);


/*
 *  GetDialogTimeout()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DialogsLib 8.5 and later
 */
extern OSStatus 
GetDialogTimeout(
  DialogRef   inDialog,
  SInt16 *    outButtonToPress,
  UInt32 *    outSecondsToWait,
  UInt32 *    outSecondsRemaining);


/*
 *  SetModalDialogEventMask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DialogsLib 8.5 and later
 */
extern OSStatus 
SetModalDialogEventMask(
  DialogRef   inDialog,
  EventMask   inMask);


/*
 *  GetModalDialogEventMask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in DialogsLib 8.5 and later
 */
extern OSStatus 
GetModalDialogEventMask(
  DialogRef    inDialog,
  EventMask *  outMask);




/*
  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
    ¥ Accessor functions
  ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
*/


/*
 *  GetDialogWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern WindowRef 
GetDialogWindow(DialogRef dialog);



/*
 *  GetDialogTextEditHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern TEHandle 
GetDialogTextEditHandle(DialogRef dialog);



/*
 *  GetDialogDefaultItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern SInt16 
GetDialogDefaultItem(DialogRef dialog);



/*
 *  GetDialogCancelItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern SInt16 
GetDialogCancelItem(DialogRef dialog);



/*
 *  GetDialogKeyboardFocusItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern SInt16 
GetDialogKeyboardFocusItem(DialogRef dialog);



/*
 *  SetPortDialogPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern void 
SetPortDialogPort(DialogRef dialog);



/*
 *  GetDialogPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern CGrafPtr 
GetDialogPort(DialogRef dialog);



/*
 *  GetDialogFromWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later or as macro/inline
 */
extern DialogRef 
GetDialogFromWindow(WindowRef window);




/*
 *  CouldDialog()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  FreeDialog()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CouldAlert()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  FreeAlert()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */




#if OLDROUTINENAMES
#define DisposDialog(theDialog) DisposeDialog(theDialog)
#define UpdtDialog(theDialog, updateRgn) UpdateDialog(theDialog, updateRgn)
#define GetDItem(theDialog, itemNo, itemType, item, box) GetDialogItem(theDialog, itemNo, itemType, item, box)
#define SetDItem(theDialog, itemNo, itemType, item, box) SetDialogItem(theDialog, itemNo, itemType, item, box)
#define HideDItem(theDialog, itemNo) HideDialogItem(theDialog, itemNo)
#define ShowDItem(theDialog, itemNo) ShowDialogItem(theDialog, itemNo)
#define SelIText(theDialog, itemNo, strtSel, endSel) SelectDialogItemText(theDialog, itemNo, strtSel, endSel)
#define GetIText(item, text) GetDialogItemText(item, text)
#define SetIText(item, text) SetDialogItemText(item, text)
#define FindDItem(theDialog, thePt) FindDialogItem(theDialog, thePt)
#define NewCDialog(dStorage, boundsRect, title, visible, procID, behind, goAwayFlag, refCon, items) \
NewColorDialog(dStorage, boundsRect, title, visible, procID, behind, goAwayFlag, refCon, items)
#define GetAlrtStage() GetAlertStage()
#define ResetAlrtStage() ResetAlertStage()
#define DlgCut(theDialog) DialogCut(theDialog)
#define DlgPaste(theDialog) DialogPaste(theDialog)
#define DlgCopy(theDialog) DialogCopy(theDialog)
#define DlgDelete(theDialog) DialogDelete(theDialog)
#define SetDAFont(fontNum) SetDialogFont(fontNum)
#define SetGrafPortOfDialog(dialog) SetPortDialogPort(dialog)
#if CGLUESUPPORTED
#define newcdialog(dStorage, boundsRect, title, visible, procID, behind, goAwayFlag, refCon, items) \
newcolordialog(dStorage, boundsRect, title, visible, procID, behind, goAwayFlag, refCon, items)
#define getitext(item, text) getdialogitemtext(item, text)
#define setitext(item, text) setdialogitemtext(item, text)
#define findditem(theDialog, thePt) finddialogitem(theDialog, thePt)
#endif
#endif  /* OLDROUTINENAMES */











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

#endif /* __DIALOGS__ */


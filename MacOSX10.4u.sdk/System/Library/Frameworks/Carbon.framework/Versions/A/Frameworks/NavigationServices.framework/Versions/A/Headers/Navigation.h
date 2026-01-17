/*
     File:       NavigationServices/Navigation.h
 
     Contains:   Navigation Services Interfaces
 
     Version:    NavigationServices-130~640
 
     Copyright:  © 1996-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __NAVIGATION__
#define __NAVIGATION__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __TRANSLATION__
#include <HIToolbox/Translation.h>
#endif

#ifndef __MACWINDOWS__
#include <HIToolbox/MacWindows.h>
#endif





#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

typedef UInt32 NavAskSaveChangesAction;
enum {
                                        /* input action codes for NavAskSaveChanges() */
  kNavSaveChangesClosingDocument = 1,
  kNavSaveChangesQuittingApplication = 2,
  kNavSaveChangesOther          = 0
};


typedef UInt32 NavAskSaveChangesResult;
enum {
                                        /* result codes for NavAskSaveChanges() */
  kNavAskSaveChangesSave        = 1,
  kNavAskSaveChangesCancel      = 2,
  kNavAskSaveChangesDontSave    = 3
};


typedef UInt32 NavAskDiscardChangesResult;
enum {
                                        /* result codes for NavAskDiscardChanges() */
  kNavAskDiscardChanges         = 1,
  kNavAskDiscardChangesCancel   = 2
};


typedef SInt16 NavFilterModes;
enum {
                                        /* which elements are being filtered for objects: */
  kNavFilteringBrowserList      = 0,
  kNavFilteringFavorites        = 1,
  kNavFilteringRecents          = 2,
  kNavFilteringShortCutVolumes  = 3,
  kNavFilteringLocationPopup    = 4     /* for v1.1 or greater */
};


enum {
  kNavFileOrFolderVersion       = 1
};

struct NavFileOrFolderInfo {
  UInt16              version;
  Boolean             isFolder;
  Boolean             visible;
  UInt32              creationDate;
  UInt32              modificationDate;
  union {
    struct {
      Boolean             locked;             /* file is locked */
      Boolean             resourceOpen;       /* resource fork is opened */
      Boolean             dataOpen;           /* data fork is opened */
      Boolean             reserved1;
      UInt32              dataSize;           /* size of the data fork */
      UInt32              resourceSize;       /* size of the resource fork */
      FInfo               finderInfo;         /* more file info: */
      FXInfo              finderXInfo;
    }                       fileInfo;
    struct {
      Boolean             shareable;
      Boolean             sharePoint;
      Boolean             mounted;
      Boolean             readable;
      Boolean             writeable;
      Boolean             reserved2;
      UInt32              numberOfFiles;
      DInfo               finderDInfo;
      DXInfo              finderDXInfo;
      OSType              folderType;         /* package type, For struct version >= 1 */
      OSType              folderCreator;      /* package creator, For struct version >= 1 */
      char                reserved3[206];
    }                       folderInfo;

  }                       fileAndFolder;
};
typedef struct NavFileOrFolderInfo      NavFileOrFolderInfo;
union NavEventDataInfo {
  EventRecord *       event;                  /* for event processing */
  void *              param;                  /* points to event specific data */
};
typedef union NavEventDataInfo          NavEventDataInfo;
struct NavEventData {
  NavEventDataInfo    eventDataParms;         /* the event data */
  SInt16              itemHit;                /* the dialog item number, for v1.1 or greater */
};
typedef struct NavEventData             NavEventData;

/*
 *  NavDialogRef
 *  
 *  Summary:
 *    Opaque Navigation Services dialog identifier
 *  
 *  Discussion:
 *    A NavDialogRef is an opaque reference to an instance of a
 *    Navigation Services dialog. A new NavDialogRef is returned from
 *    any of the NavCreate*Dialog functions and is later disposed with
 *    the NavDialogDispose function. NavDialogRef is the new name for
 *    the NavContext type, and thus when a client's event proc is
 *    called, the value of the NavCBRec.context field is the same as
 *    the NavDialogRef returned from the corresponding
 *    NavCreate*Dialog. A NavDialogRef is distinct from, and is not
 *    interchangable with, a Dialog Manager DialogRef.
 */
typedef struct __NavDialog*             NavDialogRef;
#if CALL_NOT_IN_CARBON
/* NavContext is the old name for NavDialogRef */

typedef NavDialogRef                    NavContext;
#endif  /* CALL_NOT_IN_CARBON */


/*
 *  NavUserAction
 *  
 *  Summary:
 *    Indicates an action taken by the user
 *  
 *  Discussion:
 *    When the user clicks a button at the bottom of a Nav Services
 *    dialog (or makes an equivalent mouse or key gesture), a
 *    kNavCBUserAction event is sent to the client's event proc
 *    indicating which action was taken. Often, the action also
 *    dismisses the dialog. User action events are only generated when
 *    using dialogs created from a NavCreate*Dialog function. In the
 *    special case of a modeless GetFile dialog (supported only on Mac
 *    OS X), the user can option-click on the open button to keep the
 *    dialog from being dismissed, but the kNavCBUserAction event is
 *    sent so the client can get the reply record and open the selected
 *    files.
 */
typedef UInt32 NavUserAction;
enum {

  /*
   * No action taken. The dialog is still running or was terminated
   * programmatically.
   */
  kNavUserActionNone            = 0,

  /*
   * The user cancelled the dialog.
   */
  kNavUserActionCancel          = 1,

  /*
   * The user clicked the Open button in the GetFile dialog.
   */
  kNavUserActionOpen            = 2,

  /*
   * The user clicked the Save button in the PutFile dialog.
   */
  kNavUserActionSaveAs          = 3,

  /*
   * The user clicked the Choose button in the ChooseFile,
   * ChooseFolder, ChooseVolume or ChooseObject dialogs.
   */
  kNavUserActionChoose          = 4,

  /*
   * The user clicked the New Folder button in the New Folder dialog.
   */
  kNavUserActionNewFolder       = 5,

  /*
   * The user clicked the Save button in an AskSaveChanges dialog.
   */
  kNavUserActionSaveChanges     = 6,

  /*
   * The user clicked the Don't Save button in an AskSaveChanges dialog.
   */
  kNavUserActionDontSaveChanges = 7,

  /*
   * The user clicked the Discard button in the AskDiscardChanges
   * dialog.
   */
  kNavUserActionDiscardChanges  = 8,

  /*
   * The user clicked the Review Unsaved button in the
   * AskReviewDocuments dialog (used only on Mac OS X).
   */
  kNavUserActionReviewDocuments = 9,

  /*
   * The user clicked the Discard Changes button in the
   * AskReviewDocuments dialog (used only on Mac OS X).
   */
  kNavUserActionDiscardDocuments = 10
};



enum {
  kNavCBRecVersion              = 1
};


/*
 *  NavCBRec
 *  
 *  Summary:
 *    A structure passed to event and preview callbacks
 *  
 *  Discussion:
 *    The NavCBRec structure is passed to the client's event proc or
 *    custom preview proc. It provides information that is specific to
 *    each event type. New for Carbon: the userAction field.
 */
struct NavCBRec {

  /*
   * The version of the struct (currently 1)
   */
  UInt16              version;

  /*
   * The NavDialogRef this callback with which this call is associated
   */
  NavDialogRef        context;

  /*
   * The dialog's window
   */
  WindowRef           window;

  /*
   * The custom control area rectangle (window coordinates)
   */
  Rect                customRect;

  /*
   * The custom preview area rectangle (window coordinates)
   */
  Rect                previewRect;

  /*
   * The event-specific data, including the EventRecord, if any
   */
  NavEventData        eventData;

  /*
   * The action taken by the user that generated a kNavCBUserAction
   * event (Carbon dialogs only)
   */
  NavUserAction       userAction;

  /*
   * Reserved for future use
   */
  char                reserved[218];
};
typedef struct NavCBRec                 NavCBRec;
typedef NavCBRec *                      NavCBRecPtr;

/*
 *  NavEventCallbackMessage
 *  
 *  Summary:
 *    Identifies the message type being sent to the client's event proc
 */
typedef SInt32 NavEventCallbackMessage;
enum {

  /*
   * An OS event has occurred. A pointer to the EventRecord is in the
   * eventData.eventDataParms.event field of the NavCBRec.
   */
  kNavCBEvent                   = 0,

  /*
   * Negotiate for custom control space. Client can set change the
   * customRect field in the NavCBRec to create space for a custom
   * area. Nav Services will continue to send the kNavCBCustomize
   * message until the client leaves the customRect field unchanged.
   */
  kNavCBCustomize               = 1,

  /*
   * This message is sent after custom area negotiation, just before
   * the dialog is made visible. Add your custom controls when you
   * receive this message.
   */
  kNavCBStart                   = 2,

  /*
   * This is the last message sent, after the dialog has been hidden.
   */
  kNavCBTerminate               = 3,

  /*
   * Sent when the dialog has been resized. Check the customRect and or
   * previewRect values to see if any relayout is needed. Nav Services
   * automatically moves controls in the custom area.
   */
  kNavCBAdjustRect              = 4,

  /*
   * The target folder of the dialog has changed. The
   * NavCBRec.eventData.eventDataParms.param field is an AEDesc*
   * containing an descriptor of the new location (ususally an FSSpec
   * or an FSRef).
   */
  kNavCBNewLocation             = 5,

  /*
   * The target folder has changed to the user's desktop folder.
   */
  kNavCBShowDesktop             = 6,

  /*
   * The user has selected or deselected a file or folder. The
   * NavCBRec.eventData.eventDataParms.param field is an AEDescList*
   * identifying the currently selected items.
   */
  kNavCBSelectEntry             = 7,

  /*
   * The value of the Show/Format popup menu has changed. The
   * NavCBRec.eventData.eventDataParms.param is a NavMenuItemSpec*
   * identifying the menu item selected. If the dialog was created
   * using the Carbon-only NavCreate*Dialog APIs, then the menuType
   * field of the NavMenuItemSpec is set to the index into the client's
   * CFArray of popupExtension strings (see NavDialogCreationOptions).
   */
  kNavCBPopupMenuSelect         = 8,

  /*
   * Sent when the user has accepted (Open, Save, etc.).
   */
  kNavCBAccept                  = 9,

  /*
   * Sent when the user has cancelled the dialog.
   */
  kNavCBCancel                  = 10,

  /*
   * The custom preview area state has changed. The
   * NavCBRec.eventData.eventDataParms.param is a Boolean* set to true
   * if the preview area is visible or false if it is not.
   */
  kNavCBAdjustPreview           = 11,

  /*
   * The user has taken one of the actions described in the
   * NavUserAction definition. The action may or may not dismiss the
   * dialog. The NavCBRec.userAction field indicates which action was
   * taken (Carbon dialogs only).
   */
  kNavCBUserAction              = 12,

  /*
   * The user has opened a folder or chosen a file. The client can
   * block navigation or dismissal by setting the appropriate action
   * state with the kNavCtlSetActionState NavCustomControl selector.
   */
  kNavCBOpenSelection           = (long)0x80000000
};


typedef void *                          NavCallBackUserData;
/* for events and customization: */
typedef CALLBACK_API( void , NavEventProcPtr )(NavEventCallbackMessage callBackSelector, NavCBRecPtr callBackParms, void *callBackUD);
/* for preview support: */
typedef CALLBACK_API( Boolean , NavPreviewProcPtr )(NavCBRecPtr callBackParms, void *callBackUD);
/* filtering callback information: */
typedef CALLBACK_API( Boolean , NavObjectFilterProcPtr )(AEDesc *theItem, void *info, void *callBackUD, NavFilterModes filterMode);
typedef STACK_UPP_TYPE(NavEventProcPtr)                         NavEventUPP;
typedef STACK_UPP_TYPE(NavPreviewProcPtr)                       NavPreviewUPP;
typedef STACK_UPP_TYPE(NavObjectFilterProcPtr)                  NavObjectFilterUPP;
/*
 *  NewNavEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern NavEventUPP
NewNavEventUPP(NavEventProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewNavPreviewUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern NavPreviewUPP
NewNavPreviewUPP(NavPreviewProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewNavObjectFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern NavObjectFilterUPP
NewNavObjectFilterUPP(NavObjectFilterProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeNavEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeNavEventUPP(NavEventUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeNavPreviewUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeNavPreviewUPP(NavPreviewUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeNavObjectFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeNavObjectFilterUPP(NavObjectFilterUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeNavEventUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeNavEventUPP(
  NavEventCallbackMessage  callBackSelector,
  NavCBRecPtr              callBackParms,
  void *                   callBackUD,
  NavEventUPP              userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeNavPreviewUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeNavPreviewUPP(
  NavCBRecPtr    callBackParms,
  void *         callBackUD,
  NavPreviewUPP  userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeNavObjectFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeNavObjectFilterUPP(
  AEDesc *            theItem,
  void *              info,
  void *              callBackUD,
  NavFilterModes      filterMode,
  NavObjectFilterUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

typedef SInt32 NavCustomControlMessage;
enum {
  kNavCtlShowDesktop            = 0,    /*    show desktop,           parms = nil */
  kNavCtlSortBy                 = 1,    /*    sort key field,       parms->NavSortKeyField */
  kNavCtlSortOrder              = 2,    /*    sort order,              parms->NavSortOrder */
  kNavCtlScrollHome             = 3,    /*    scroll list home,       parms = nil */
  kNavCtlScrollEnd              = 4,    /*    scroll list end,      parms = nil */
  kNavCtlPageUp                 = 5,    /*    page list up,          parms = nil */
  kNavCtlPageDown               = 6,    /*    page list down,          parms = nil */
  kNavCtlGetLocation            = 7,    /*    get current location,   parms<-AEDesc* */
  kNavCtlSetLocation            = 8,    /*    set current location,   parms->AEDesc* */
  kNavCtlGetSelection           = 9,    /*    get current selection,     parms<-AEDescList* */
  kNavCtlSetSelection           = 10,   /*    set current selection,     parms->AEDescList* */
  kNavCtlShowSelection          = 11,   /*    make selection visible,       parms = nil */
  kNavCtlOpenSelection          = 12,   /*    open view of selection,       parms = nil */
  kNavCtlEjectVolume            = 13,   /*    eject volume,          parms->vRefNum */
  kNavCtlNewFolder              = 14,   /*    create a new folder,     parms->StringPtr */
  kNavCtlCancel                 = 15,   /*    cancel dialog,          parms = nil */
  kNavCtlAccept                 = 16,   /*    accept dialog default,     parms = nil */
  kNavCtlIsPreviewShowing       = 17,   /*    query preview status,   parms<-Boolean */
  kNavCtlAddControl             = 18,   /*  add one control to dialog,    parms->ControlHandle */
  kNavCtlAddControlList         = 19,   /*    add control list to dialog,    parms->Handle (DITL rsrc) */
  kNavCtlGetFirstControlID      = 20,   /*    get 1st control ID,         parms<-UInt16 */
  kNavCtlSelectCustomType       = 21,   /*    select a custom menu item  parms->NavMenuItemSpec* */
  kNavCtlSelectAllType          = 22,   /*  select an "All" menu item parms->SInt16 */
  kNavCtlGetEditFileName        = 23,   /*    get save dlog's file name  parms<-StringPtr */
  kNavCtlSetEditFileName        = 24,   /*    set save dlog's file name  parms->StringPtr */
  kNavCtlSelectEditFileName     = 25,   /*    select save dlog file name parms->ControlEditTextSelectionRec*, v1.1 or greater */
  kNavCtlBrowserSelectAll       = 26,   /*  re-scan the browser list  parms = nil, v2.0 or greater */
  kNavCtlGotoParent             = 27,   /*  navigate to parent         parms = nil, v2.0 or greater */
  kNavCtlSetActionState         = 28,   /*  restrict navigation      parms->NavActionState (flags), v2.0 or greater */
  kNavCtlBrowserRedraw          = 29,   /*  rescan browser list      parms = nil, v2.0 or greater */
  kNavCtlTerminate              = 30    /*  terminate/dismiss dialog  parms = nil, v2.0 or greater */
};

typedef UInt32 NavActionState;
enum {
  kNavNormalState               = 0x00000000, /* normal/default state */
  kNavDontOpenState             = 0x00000001, /* disallow opening files/folders */
  kNavDontSaveState             = 0x00000002, /* disallow saving files */
  kNavDontChooseState           = 0x00000004, /* disallow choosing objects */
  kNavDontNewFolderState        = 0x00000010 /* disallow creating new folders */
};

typedef UInt16 NavPopupMenuItem;
enum {
  kNavAllKnownFiles             = 0,
  kNavAllReadableFiles          = 1,
  kNavAllFiles                  = 2
};

typedef UInt16 NavSortKeyField;
enum {
  kNavSortNameField             = 0,
  kNavSortDateField             = 1
};


typedef UInt16 NavSortOrder;
enum {
  kNavSortAscending             = 0,
  kNavSortDescending            = 1
};


typedef UInt32 NavDialogOptionFlags;
enum {
  kNavDefaultNavDlogOptions     = 0x000000E4, /* use defaults for all the options */
  kNavNoTypePopup               = 0x00000001, /* don't show file type/extension popup on Open/Save */
  kNavDontAutoTranslate         = 0x00000002, /* don't automatically translate on Open */
  kNavDontAddTranslateItems     = 0x00000004, /* don't add translation choices on Open/Save */
  kNavAllFilesInPopup           = 0x00000010, /* "All Files" menu item in the type popup on Open */
  kNavAllowStationery           = 0x00000020, /* allow saving of stationery files */
  kNavAllowPreviews             = 0x00000040, /* allow preview to show */
  kNavAllowMultipleFiles        = 0x00000080, /* allow multiple items to be selected */
  kNavAllowInvisibleFiles       = 0x00000100, /* allow invisible items to be shown */
  kNavDontResolveAliases        = 0x00000200, /* don't resolve aliases */
  kNavSelectDefaultLocation     = 0x00000400, /* make the default location the browser selection */
  kNavSelectAllReadableItem     = 0x00000800, /* make the dialog select "All Readable Documents" on open */
  kNavSupportPackages           = 0x00001000, /* recognize file system packages, v2.0 or greater */
  kNavAllowOpenPackages         = 0x00002000, /* allow opening of packages, v2.0 or greater */
  kNavDontAddRecents            = 0x00004000, /* don't add chosen objects to the recents list, v2.0 or greater */
  kNavDontUseCustomFrame        = 0x00008000, /* don't draw the custom area bevel frame, v2.0 or greater */
  kNavDontConfirmReplacement    = 0x00010000, /* don't show the "Replace File?" alert on save conflict, v3.0 or greater */
  kNavPreserveSaveFileExtension = 0x00020000 /* extension in default file name is preserved between dialog invocations and initially hidden, v3.1 or greater */
};


typedef UInt32 NavTranslationOptions;
enum {
  kNavTranslateInPlace          = 0,    /*    translate in place, replacing translation source file (default for Save) */
  kNavTranslateCopy             = 1     /*    translate to a copy of the source file (default for Open) */
};


enum {
  kNavMenuItemSpecVersion       = 0
};

struct NavMenuItemSpec {
  UInt16              version;
  OSType              menuCreator;
  OSType              menuType;
  Str255              menuItemName;
  char                reserved[245];
};
typedef struct NavMenuItemSpec          NavMenuItemSpec;
typedef NavMenuItemSpec *               NavMenuItemSpecArrayPtr;
typedef NavMenuItemSpecArrayPtr *       NavMenuItemSpecArrayHandle;
typedef NavMenuItemSpecArrayPtr         NavMenuItemSpecPtr;
typedef NavMenuItemSpecArrayHandle      NavMenuItemSpecHandle;
enum {
  kNavGenericSignature          = '****'
};

struct NavTypeList {
  OSType              componentSignature;
  short               reserved;
  short               osTypeCount;
  OSType              osType[1];
};
typedef struct NavTypeList              NavTypeList;
typedef NavTypeList *                   NavTypeListPtr;
typedef NavTypeListPtr *                NavTypeListHandle;
enum {
  kNavDialogOptionsVersion      = 0
};

struct NavDialogOptions {
  UInt16              version;
  NavDialogOptionFlags  dialogOptionFlags;    /* option flags for affecting the dialog's behavior */
  Point               location;               /* top-left location of the dialog, or {-1,-1} for default position */
  Str255              clientName;
  Str255              windowTitle;
  Str255              actionButtonLabel;      /* label of the default button (or null string for default) */
  Str255              cancelButtonLabel;      /* label of the cancel button (or null string for default) */
  Str255              savedFileName;          /* default name for text box in NavPutFile (or null string for default) */
  Str255              message;                /* custom message prompt (or null string for default) */
  UInt32              preferenceKey;          /* a key for to managing preferences for using multiple utility dialogs */
  NavMenuItemSpecArrayHandle  popupExtension; /* extended popup menu items, an array of NavMenuItemSpecs */
  char                reserved[494];
};
typedef struct NavDialogOptions         NavDialogOptions;
enum {
  kNavReplyRecordVersion        = 2
};


/*
 *  NavReplyRecord
 *  
 *  Summary:
 *    A structure describing the results of a Nav Services dialog
 *  
 *  Discussion:
 *    A reply record is the result of a Nav Services file dialog. Using
 *    the older API, which is always modal, the client passes the
 *    address of a reply record when invoking the dialog. In the Carbon
 *    API, dialogs may also be window modal or modeless, so the client
 *    requests the reply record by calling NavDialogGetReply when a
 *    kNavCBUserAction event is received. Either way, a reply record
 *    should be disposed of using NavDisposeReply.
 */
struct NavReplyRecord {

  /*
   * The version of the structure. The first public version of the
   * structure was version 0. Fields added after version 0, starting
   * with the saveFileName field, are noted below.
   */
  UInt16              version;

  /*
   * True if the reply contains a non-null selection
   */
  Boolean             validRecord;

  /*
   * True if this reply is from a PutFile dialog and the file to be
   * saved already exists and needs to be replaced. The user has
   * already been warned unless the kNavDontConfirmReplacement option
   * flag is used.
   */
  Boolean             replacing;

  /*
   * True if this reply is from a PutFile dialog and the user wants to
   * save the file as stationery.
   */
  Boolean             isStationery;

  /*
   * True if translation was performed on the file(s) to be opened or
   * if transtlation will be needed on the file to be saved.
   */
  Boolean             translationNeeded;

  /*
   * For GetFile or Choose dialogs, a list of items chosen by the user.
   * For the older NavPutFile dialog, a list containing one item: an
   * FSSpec of the file to be saved. ** IMPORTANT NOTE *** For the new
   * Carbon-only PutFile dialog created with NavCreatePutFileDialog,
   * the selection is a list containing one item: the DIRECTORY where
   * the file is to be saved. The file name is obtained from the
   * saveFileName field. When using the original modal API, each
   * descriptor will contain an FSSpec (typeFSS). When using the new
   * Carbon-only dialogs created via the NavCreate*Dialog functions,
   * each descriptor could contain either an FSSpec (typeFSS, used on
   * Mac OS 8 or 9) or an FSRef (typeFSRef, used on Mac OS X). This
   * divergence is caused by the need to use FSRef (for Unicode/HFS+
   * support) on Mac OS X, while being unable to provide FSRefs on Mac
   * OS 8.6.
   */
  AEDescList          selection;

  /*
   * For NavPutFile: the script system associated with the name of the
   * file to be saved.
   */
  ScriptCode          keyScript;

  /*
   * A handle to an array of type FileTranslationSpec. Each array entry
   * corresponds to an item in the selection and describes the
   * translation that was performed (GetFile) or needs to be performed
   * (PutFile) on that item.
   */
  FileTranslationSpecArrayHandle  fileTranslation;

  /*
   * Reserved for private use.
   */
  UInt32              reserved1;

  /*
   * Carbon PutFile dialog only: the name of the file to be saved. This
   * field contains the true file name to saved, even if the extension
   * will be hidden from the user. This field was added in structure
   * version 1.
   */
  CFStringRef         saveFileName;

  /*
   * The extension on the name of the saved file should be hidden. Once
   * the file has been saved, the client should call NavCompleteSave.
   * NavCompleteSave will take care of hiding the extension on the
   * file. However, the client needs to know that the extension is
   * hidden so that it can display the document name correctly in the
   * UI, such as in window titles and menus. This field is only used if
   * the client has r equested extension preservation using the
   * kNavPreserveSaveFileExtension dialog option flag. This field was
   * added in structure version 2.
   */
  Boolean             saveFileExtensionHidden;

  /*
   * Reserved for future use.
   */
  UInt8               reserved2;

  /*
   * Reserved for future use.
   */
  char                reserved[225];
};
typedef struct NavReplyRecord           NavReplyRecord;
/*
 *  NavLoad()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavLoad(void);


/*
 *  NavUnload()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavUnload(void);


/*
 *  NavLibraryVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern UInt32 
NavLibraryVersion(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavGetDefaultDialogOptions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavGetDefaultDialogOptions(NavDialogOptions * dialogOptions)  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavGetFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavGetFile(
  AEDesc *             defaultLocation,       /* can be NULL */
  NavReplyRecord *     reply,
  NavDialogOptions *   dialogOptions,         /* can be NULL */
  NavEventUPP          eventProc,             /* can be NULL */
  NavPreviewUPP        previewProc,           /* can be NULL */
  NavObjectFilterUPP   filterProc,            /* can be NULL */
  NavTypeListHandle    typeList,              /* can be NULL */
  void *               callBackUD)            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavPutFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavPutFile(
  AEDesc *            defaultLocation,       /* can be NULL */
  NavReplyRecord *    reply,
  NavDialogOptions *  dialogOptions,         /* can be NULL */
  NavEventUPP         eventProc,             /* can be NULL */
  OSType              fileType,
  OSType              fileCreator,
  void *              callBackUD)            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavAskSaveChanges()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavAskSaveChanges(
  NavDialogOptions *         dialogOptions,
  NavAskSaveChangesAction    action,
  NavAskSaveChangesResult *  reply,
  NavEventUPP                eventProc,           /* can be NULL */
  void *                     callBackUD)          /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavCustomAskSaveChanges()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavCustomAskSaveChanges(
  NavDialogOptions *         dialogOptions,
  NavAskSaveChangesResult *  reply,
  NavEventUPP                eventProc,           /* can be NULL */
  void *                     callBackUD)          /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavAskDiscardChanges()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavAskDiscardChanges(
  NavDialogOptions *            dialogOptions,
  NavAskDiscardChangesResult *  reply,
  NavEventUPP                   eventProc,           /* can be NULL */
  void *                        callBackUD)          /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavChooseFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavChooseFile(
  AEDesc *             defaultLocation,       /* can be NULL */
  NavReplyRecord *     reply,
  NavDialogOptions *   dialogOptions,         /* can be NULL */
  NavEventUPP          eventProc,             /* can be NULL */
  NavPreviewUPP        previewProc,           /* can be NULL */
  NavObjectFilterUPP   filterProc,            /* can be NULL */
  NavTypeListHandle    typeList,              /* can be NULL */
  void *               callBackUD)            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavChooseFolder()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavChooseFolder(
  AEDesc *             defaultLocation,       /* can be NULL */
  NavReplyRecord *     reply,
  NavDialogOptions *   dialogOptions,         /* can be NULL */
  NavEventUPP          eventProc,             /* can be NULL */
  NavObjectFilterUPP   filterProc,            /* can be NULL */
  void *               callBackUD)            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavChooseVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavChooseVolume(
  AEDesc *             defaultSelection,       /* can be NULL */
  NavReplyRecord *     reply,
  NavDialogOptions *   dialogOptions,          /* can be NULL */
  NavEventUPP          eventProc,              /* can be NULL */
  NavObjectFilterUPP   filterProc,             /* can be NULL */
  void *               callBackUD)             /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavChooseObject()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavChooseObject(
  AEDesc *             defaultLocation,       /* can be NULL */
  NavReplyRecord *     reply,
  NavDialogOptions *   dialogOptions,         /* can be NULL */
  NavEventUPP          eventProc,             /* can be NULL */
  NavObjectFilterUPP   filterProc,            /* can be NULL */
  void *               callBackUD)            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavNewFolder()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavNewFolder(
  AEDesc *            defaultLocation,       /* can be NULL */
  NavReplyRecord *    reply,
  NavDialogOptions *  dialogOptions,         /* can be NULL */
  NavEventUPP         eventProc,             /* can be NULL */
  void *              callBackUD)            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavTranslateFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavTranslateFile(
  NavReplyRecord *        reply,
  NavTranslationOptions   howToTranslate)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavCompleteSave()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavCompleteSave(
  NavReplyRecord *        reply,
  NavTranslationOptions   howToTranslate)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavCustomControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavCustomControl(
  NavDialogRef              dialog,
  NavCustomControlMessage   selector,
  void *                    parms)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavCreatePreview()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 2.0 and later
 */
extern OSErr 
NavCreatePreview(
  AEDesc *      theObject,
  OSType        previewDataType,
  const void *  previewData,
  Size          previewDataSize)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavDisposeReply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern OSErr 
NavDisposeReply(NavReplyRecord * reply)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavServicesCanRun()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in NavigationLib 1.0 and later
 */
extern Boolean 
NavServicesCanRun(void);



#if TARGET_RT_MAC_CFM
#ifdef __cplusplus
    inline pascal Boolean NavServicesAvailable() { return ((NavLibraryVersion != (void*)kUnresolvedCFragSymbolAddress) && NavServicesCanRun()); }
#else
    #define NavServicesAvailable()  ((NavLibraryVersion != (void*)kUnresolvedCFragSymbolAddress) && NavServicesCanRun())
#endif
#elif TARGET_RT_MAC_MACHO
/* Navigation is always available on OS X */
#ifdef __cplusplus
    inline pascal Boolean NavServicesAvailable() { return true; }
#else
    #define NavServicesAvailable()  (true)
#endif
#else
/* NavServicesAvailable() is implemented in Navigation.o for classic 68K clients*/
/*
 *  NavServicesAvailable()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


#endif  /*  */

/* Carbon API */
/* Includes support for Unicode and long file names (where available). */

enum {
  kNavDialogCreationOptionsVersion = 0
};



/*
 *  NavDialogCreationOptions
 *  
 *  Summary:
 *    Options used to control the appearance and operation of a Nav
 *    Services dialog
 *  
 *  Discussion:
 *    NavDialogCreationOptions is a preferred replacement for
 *    NavDialogOptions. The new structure uses CFStrings in place of
 *    Pascal strings, and adds fields for setting the dialog modality
 *    and the parent window (for sheet dialogs). A
 *    NavDialogCreationOptions structure can be initialized using
 *    NavDialogGetDefaultCreationOptions. Each of the NavCreate*Dialog
 *    functions accepts a pointer to the client's
 *    NavDialogCreationOptions structure.
 */
struct NavDialogCreationOptions {

  /*
   * The version of the struture. Currently, the only valid version is
   * 0, containing all the fields described here.
   */
  UInt16              version;

  /*
   * Options for the dialog. See NavDialogOptionFlags for a description
   * of each option.
   */
  NavDialogOptionFlags  optionFlags;

  /*
   * The screen position at which to place the upper left corner of the
   * dialog, in global coordinates. Specify (-1, -1) to use the default
   * (persistent) location. Ignored for sheet dialogs.
   */
  Point               location;

  /*
   * The user-readable name of the client, usually the name of the
   * current application. This value is used to construct the default
   * window title in the file dialogs, and the message text in the Ask
   * dialogs. On Mac OS 9 and earlier, this value is used as a key to
   * store persistent per-client dialog settings, so it's always a good
   * idea to set this field to a non-NULL value.
   */
  CFStringRef         clientName;

  /*
   * The custom title for the dialog window. Specify NULL to use the
   * default title.
   */
  CFStringRef         windowTitle;

  /*
   * The custom label for the default (Open/Save/Choose) button.
   * Specify NULL to use the default label.
   */
  CFStringRef         actionButtonLabel;

  /*
   * The custom label for the Cancel button. Specify NULL to use the
   * default label.
   */
  CFStringRef         cancelButtonLabel;

  /*
   * The initial value appearing in the edit text field for the file
   * name to be saved (PutFile, NavAskSaveChanges only).
   */
  CFStringRef         saveFileName;

  /*
   * For the file dialogs, a banner message appearing across the top of
   * the dialog. Specify NULL to provide no banner message. For the Ask
   * alerts, a custom message to replace the default message.
   */
  CFStringRef         message;

  /*
   * A key to uniquely identify the dialog's usage context within the
   * application. If an application uses the same class of dialog (e.g.
   * GetFile or ChooseFile) for more than one purpose, set this field
   * to a unique value for each usage in order to give each dialog its
   * own persistent settings (e.g. screen rectangle, starting target
   * folder).
   */
  UInt32              preferenceKey;

  /*
   * A CFArray of CFStrings. The strings are added as menu items to the
   * Show or Format popup menus in the GetFile or PutFile dialogs,
   * respectively.
   */
  CFArrayRef          popupExtension;

  /*
   * The modality in which to present the dialog. The default modality
   * for all dialogs is kWindowModalityAppModal. If
   * kWindowModalityWindowModal is specified, then a valid parentWindow
   * is required.
   */
  WindowModality      modality;

  /*
   * The window to which a window-modal (sheet) dialog is to be
   * attached.
   */
  WindowRef           parentWindow;

  /*
   * Reserved for future use.
   */
  char                reserved[16];
};
typedef struct NavDialogCreationOptions NavDialogCreationOptions;
/*
 *  NavGetDefaultDialogCreationOptions()
 *  
 *  Summary:
 *    Initialize the input structure to default values
 *  
 *  Discussion:
 *    Provided as a convenience to obtain the preferred default options
 *    for use in creating any Nav Services dialog.
 *  
 *  Parameters:
 *    
 *    outOptions:
 *      A pointer to the client-allocated options structure to
 *      initialize
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavGetDefaultDialogCreationOptions(NavDialogCreationOptions * outOptions) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavCreateGetFileDialog()
 *  
 *  Summary:
 *    Create a GetFile dialog
 *  
 *  Discussion:
 *    Use this function to create a dialog designed for opening
 *    document files. This function replaces NavGetFile, allowing new
 *    window modalities, and adding Unicode support. Upon successful
 *    creation, the dialog is not visible. Present and run the dialog
 *    with NavDialogRun. After the dialog is complete, dispose of it
 *    with NavDialogDispose.
 *  
 *  Parameters:
 *    
 *    inOptions:
 *      Options controlling the appearance and behavior of the dialog
 *    
 *    inTypeList:
 *      A creator signature and list of file types to show in the
 *      dialog file browser. If NULL, show all files.
 *    
 *    inEventProc:
 *      The UPP for the client's event callack, or NULL for no event
 *      callback
 *    
 *    inPreviewProc:
 *      The UPP for the client's custom file preview callback, or NULL
 *      for standard previews
 *    
 *    inFilterProc:
 *      The UPP for the client's custom filter callback, or NULL for no
 *      custom file filtering
 *    
 *    inClientData:
 *      A client-defined context value passed to all callback functions
 *    
 *    outDialog:
 *      Upon successful completion, a reference to the created dialog
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavCreateGetFileDialog(
  const NavDialogCreationOptions *  inOptions,           /* can be NULL */
  NavTypeListHandle                 inTypeList,          /* can be NULL */
  NavEventUPP                       inEventProc,         /* can be NULL */
  NavPreviewUPP                     inPreviewProc,       /* can be NULL */
  NavObjectFilterUPP                inFilterProc,        /* can be NULL */
  void *                            inClientData,        /* can be NULL */
  NavDialogRef *                    outDialog)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavCreatePutFileDialog()
 *  
 *  Summary:
 *    Create a PutFile dialog
 *  
 *  Discussion:
 *    Use this function to create a dialog designed for setting the
 *    name and location of a document file prior to saving. This
 *    function replaces NavPutFile, allowing new window modalities, and
 *    adding Unicode support. Upon successful creation, the dialog is
 *    not visible. Present and run the dialog with NavDialogRun. After
 *    the dialog is complete, dispose of it with NavDialogDispose.
 *  
 *  Parameters:
 *    
 *    inOptions:
 *      Options controlling the appearance and behavior of the dialog
 *    
 *    inFileType:
 *      The type of the file to be saved. This parameter is used in
 *      conjunction with the inFileCreator parameter to look up the
 *      kind string for the Format popup menu, and to drive the
 *      identification of translation options.
 *    
 *    inFileCreator:
 *      The creator signature of the file to be saved (see inFileType
 *      parameter)
 *    
 *    inEventProc:
 *      The UPP for the client's event callack, or NULL for no event
 *      callback
 *    
 *    inClientData:
 *      A client-defined context value passed to all callback functions
 *    
 *    outDialog:
 *      Upon successful completion, a reference to the created dialog
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavCreatePutFileDialog(
  const NavDialogCreationOptions *  inOptions,           /* can be NULL */
  OSType                            inFileType,
  OSType                            inFileCreator,
  NavEventUPP                       inEventProc,         /* can be NULL */
  void *                            inClientData,        /* can be NULL */
  NavDialogRef *                    outDialog)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavCreateAskReviewDocumentsDialog()
 *  
 *  Summary:
 *    Create an AskReviewDocumentsDialog dialog
 *  
 *  Discussion:
 *    Use this function to create a dialog which tells the user how
 *    many unsaved documents there are, and asks the user to start
 *    reviewing the documents, don't save any documents, or cancel.
 *    This dialog is appropriate to use when an application is quitting
 *    and there is more than one unsaved document. It is supported only
 *    on Mac OS X because the HI guidelines for earlier versions of Mac
 *    OS do not include this dialog as part of the application quit
 *    sequence. Upon successful creation, the dialog is not visible.
 *    Present and run the dialog with NavDialogRun. After the dialog is
 *    complete, dispose of it with NavDialogDispose. Upon dismissal of
 *    the dialog, this dialog's user action will be set to one of the
 *    following: kNavUserActionReviewDocuments,
 *    kNavUserActionDiscardDocuments, or kNavUserActionCancel.
 *  
 *  Parameters:
 *    
 *    inOptions:
 *      Options controlling the appearance and behavior of the dialog
 *    
 *    inDocumentCount:
 *      Indicates the number of documents needing review. This number
 *      appears in the text presented to the user. If for any reason
 *      the total number of unsaved documents is unknown, specify 0,
 *      and an ambiguous message will appear. Do not specifiy 1, since
 *      the HI guidelines call for this alert only when there is more
 *      than one document to be reviewed.
 *    
 *    inEventProc:
 *      The UPP for the client's event callack, or NULL for no event
 *      callback
 *    
 *    inClientData:
 *      A client-defined context value passed to all callback functions
 *    
 *    outDialog:
 *      Upon successful completion, a reference to the created dialog
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavCreateAskReviewDocumentsDialog(
  const NavDialogCreationOptions *  inOptions,
  UInt32                            inDocumentCount,
  NavEventUPP                       inEventProc,           /* can be NULL */
  void *                            inClientData,          /* can be NULL */
  NavDialogRef *                    outDialog)                AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  NavCreateAskSaveChangesDialog()
 *  
 *  Summary:
 *    Create an AskSaveChanges dialog
 *  
 *  Discussion:
 *    Use this function to create a dialog which asks the user to save,
 *    don't save or cancel closing a document with unsaved changes.
 *    This function replaces NavAskSaveChanges and
 *    NavCustomAskSaveChanges, allowing new window modalities, and
 *    adding Unicode support. Upon successful creation, the dialog is
 *    not visible. Present and run the dialog with NavDialogRun. After
 *    the dialog is complete, dispose of it with NavDialogDispose. To
 *    provide a customized message for the alert, specify an non-NULL
 *    message value in the options structure.
 *  
 *  Parameters:
 *    
 *    inOptions:
 *      Options controlling the appearance and behavior of the dialog
 *    
 *    inAction:
 *      Indicates this usage context for this dialog: closing a
 *      document or quitting an application. This setting affects the
 *      message text displayed to the user.
 *    
 *    inEventProc:
 *      The UPP for the client's event callack, or NULL for no event
 *      callback
 *    
 *    inClientData:
 *      A client-defined context value passed to all callback functions
 *    
 *    outDialog:
 *      Upon successful completion, a reference to the created dialog
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavCreateAskSaveChangesDialog(
  const NavDialogCreationOptions *  inOptions,
  NavAskSaveChangesAction           inAction,
  NavEventUPP                       inEventProc,        /* can be NULL */
  void *                            inClientData,       /* can be NULL */
  NavDialogRef *                    outDialog)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavCreateAskDiscardChangesDialog()
 *  
 *  Summary:
 *    Create an AskDiscardChanges dialog
 *  
 *  Discussion:
 *    Use this function to create a dialog which asks the user to
 *    discard changes to a document or cancel. This is most often use
 *    when the user wants to revert a a document to the last saved
 *    revision. This function replaces NavAskDiscardChanges, allowing
 *    new window modalities, and adding Unicode support. Upon
 *    successful creation, the dialog is not visible. Present and run
 *    the dialog with NavDialogRun. After the dialog is complete,
 *    dispose of it with NavDialogDispose.
 *  
 *  Parameters:
 *    
 *    inOptions:
 *      Options controlling the appearance and behavior of the dialog
 *    
 *    inEventProc:
 *      The UPP for the client's event callack, or NULL for no event
 *      callback
 *    
 *    inClientData:
 *      A client-defined context value passed to all callback functions
 *    
 *    outDialog:
 *      Upon successful completion, a reference to the created dialog
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavCreateAskDiscardChangesDialog(
  const NavDialogCreationOptions *  inOptions,
  NavEventUPP                       inEventProc,        /* can be NULL */
  void *                            inClientData,       /* can be NULL */
  NavDialogRef *                    outDialog)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavCreateChooseFileDialog()
 *  
 *  Summary:
 *    Create a ChooseFile dialog
 *  
 *  Discussion:
 *    Use this function to create a dialog designed for selecting one
 *    file as the target of an operation. A ChooseFile dialog is a
 *    simple version a GetFile dialog. This function replaces
 *    NavChooseFile, allowing new window modalities, and adding Unicode
 *    support. Upon successful creation, the dialog is not visible.
 *    Present and run the dialog with NavDialogRun. After the dialog is
 *    complete, dispose of it with NavDialogDispose.
 *  
 *  Parameters:
 *    
 *    inOptions:
 *      Options controlling the appearance and behavior of the dialog
 *    
 *    inTypeList:
 *      A creator signature and list of file types to show in the
 *      dialog file browser. If NULL, show all files.
 *    
 *    inEventProc:
 *      The UPP for the client's event callack, or NULL for no event
 *      callback
 *    
 *    inPreviewProc:
 *      The UPP for the client's custom file preview callback, or NULL
 *      for standard previews
 *    
 *    inFilterProc:
 *      The UPP for the client's custom filter callback, or NULL for no
 *      custom file filtering
 *    
 *    inClientData:
 *      A client-defined context value passed to all callback functions
 *    
 *    outDialog:
 *      Upon successful completion, a reference to the created dialog
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavCreateChooseFileDialog(
  const NavDialogCreationOptions *  inOptions,           /* can be NULL */
  NavTypeListHandle                 inTypeList,          /* can be NULL */
  NavEventUPP                       inEventProc,         /* can be NULL */
  NavPreviewUPP                     inPreviewProc,       /* can be NULL */
  NavObjectFilterUPP                inFilterProc,        /* can be NULL */
  void *                            inClientData,        /* can be NULL */
  NavDialogRef *                    outDialog)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavCreateChooseFolderDialog()
 *  
 *  Summary:
 *    Create a ChooseFolder dialog
 *  
 *  Discussion:
 *    Use this function to create a dialog designed for selecting a
 *    folder as the target of an operation. This function replaces
 *    NavChooseFolder, allowing new window modalities, and adding
 *    Unicode support. Upon successful creation, the dialog is not
 *    visible. Present and run the dialog with NavDialogRun. After the
 *    dialog is complete, dispose of it with NavDialogDispose.
 *  
 *  Parameters:
 *    
 *    inOptions:
 *      Options controlling the appearance and behavior of the dialog
 *    
 *    inEventProc:
 *      The UPP for the client's event callack, or NULL for no event
 *      callback
 *    
 *    inFilterProc:
 *      The UPP for the client's custom filter callback, or NULL for no
 *      custom file filtering
 *    
 *    inClientData:
 *      A client-defined context value passed to all callback functions
 *    
 *    outDialog:
 *      Upon successful completion, a reference to the created dialog
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavCreateChooseFolderDialog(
  const NavDialogCreationOptions *  inOptions,          /* can be NULL */
  NavEventUPP                       inEventProc,        /* can be NULL */
  NavObjectFilterUPP                inFilterProc,       /* can be NULL */
  void *                            inClientData,       /* can be NULL */
  NavDialogRef *                    outDialog)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavCreateChooseVolumeDialog()
 *  
 *  Summary:
 *    Create a ChooseVolume dialog
 *  
 *  Discussion:
 *    Use this function to create a dialog designed for selecting a
 *    volume as the target of an operation. This function replaces
 *    NavChooseVolume, allowing new window modalities, and adding
 *    Unicode support. Upon successful creation, the dialog is not
 *    visible. Present and run the dialog with NavDialogRun. After the
 *    dialog is complete, dispose of it with NavDialogDispose.
 *  
 *  Parameters:
 *    
 *    inOptions:
 *      Options controlling the appearance and behavior of the dialog
 *    
 *    inEventProc:
 *      The UPP for the client's event callack, or NULL for no event
 *      callback
 *    
 *    inFilterProc:
 *      The UPP for the client's custom filter callback, or NULL for no
 *      custom file filtering
 *    
 *    inClientData:
 *      A client-defined context value passed to all callback functions
 *    
 *    outDialog:
 *      Upon successful completion, a reference to the created dialog
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavCreateChooseVolumeDialog(
  const NavDialogCreationOptions *  inOptions,          /* can be NULL */
  NavEventUPP                       inEventProc,        /* can be NULL */
  NavObjectFilterUPP                inFilterProc,       /* can be NULL */
  void *                            inClientData,       /* can be NULL */
  NavDialogRef *                    outDialog)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavCreateChooseObjectDialog()
 *  
 *  Summary:
 *    Create a ChooseObject dialog
 *  
 *  Discussion:
 *    Use this function to create a dialog designed for selecting a
 *    file, folder, or volume as the target of an operation. This
 *    function replaces NavChooseObject, allowing new window
 *    modalities, and adding Unicode support. Upon successful creation,
 *    the dialog is not visible. Present and run the dialog with
 *    NavDialogRun. After the dialog is complete, dispose of it with
 *    NavDialogDispose.
 *  
 *  Parameters:
 *    
 *    inOptions:
 *      Options controlling the appearance and behavior of the dialog
 *    
 *    inEventProc:
 *      The UPP for the client's event callack, or NULL for no event
 *      callback
 *    
 *    inPreviewProc:
 *      The UPP for the client's custom file preview callback, or NULL
 *      for standard previews
 *    
 *    inFilterProc:
 *      The UPP for the client's custom filter callback, or NULL for no
 *      custom file filtering
 *    
 *    inClientData:
 *      A client-defined context value passed to all callback functions
 *    
 *    outDialog:
 *      Upon successful completion, a reference to the created dialog
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavCreateChooseObjectDialog(
  const NavDialogCreationOptions *  inOptions,           /* can be NULL */
  NavEventUPP                       inEventProc,         /* can be NULL */
  NavPreviewUPP                     inPreviewProc,       /* can be NULL */
  NavObjectFilterUPP                inFilterProc,        /* can be NULL */
  void *                            inClientData,        /* can be NULL */
  NavDialogRef *                    outDialog)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavCreateNewFolderDialog()
 *  
 *  Summary:
 *    Create a NewFolder dialog
 *  
 *  Discussion:
 *    Use this function to create a dialog designed for creating a new
 *    folder. Nav Services creates the folder as specified by the user
 *    and returns a reference to the folder in the selection field of
 *    the reply record. This function replaces NavNewFolder, allowing
 *    new window modalities, and adding Unicode support. Upon
 *    successful creation, the dialog is not visible. Present and run
 *    the dialog with NavDialogRun. After the dialog is complete,
 *    dispose of it with NavDialogDispose.
 *  
 *  Parameters:
 *    
 *    inOptions:
 *      Options controlling the appearance and behavior of the dialog
 *    
 *    inEventProc:
 *      The UPP for the client's event callack, or NULL for no event
 *      callback
 *    
 *    inClientData:
 *      A client-defined context value passed to all callback functions
 *    
 *    outDialog:
 *      Upon successful completion, a reference to the created dialog
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavCreateNewFolderDialog(
  const NavDialogCreationOptions *  inOptions,          /* can be NULL */
  NavEventUPP                       inEventProc,        /* can be NULL */
  void *                            inClientData,       /* can be NULL */
  NavDialogRef *                    outDialog)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavDialogRun()
 *  
 *  Summary:
 *    Show and run a Nav Services dialog
 *  
 *  Discussion:
 *    After a dialog is created with a NavCreate*Dialog function, the
 *    client can modify the dialog target folder or save file name
 *    using NavCustomControl with the appropriate selectors. The dialog
 *    is presented to the user by calling NavDialogRun. If the dialog
 *    is system modal or application modal (kWindowModalitySystemModal,
 *    kWindowModalityAppModal), NavDialogRun does not return until the
 *    dialog has been dismissed. If the dialog is modeless or window
 *    modal (kWindowModalityNone, kWindowModalityWindowModal),
 *    NavDialogRun shows the dialog and returns immediately. In order
 *    to know when the dialog has been dismissed, the client must watch
 *    for the kNavCBUserAction event sent to the client event proc.
 *    Note that on Mac OS 9 and earlier, all dialogs are modal, even if
 *    a modeless or window modal dialog is requested. However, the
 *    kNavCBUserAction event is still sent to the event proc, so it's
 *    possible to use a single programming model on OS 9 and OS X
 *    provided the client assumes NavDialogRun returns immediately
 *    after showing the dialog.
 *  
 *  Parameters:
 *    
 *    inDialog:
 *      The dialog to run
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavDialogRun(NavDialogRef inDialog)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavDialogDispose()
 *  
 *  Summary:
 *    Dispose of a Nav Services dialog
 *  
 *  Discussion:
 *    Call this function when completely finished with a Nav Services
 *    dialog. After calling NavDialogDispose, the dialog reference is
 *    no longer valid. NavDialogDispose is safe to call from within a
 *    callback to the client's Nav Services event proc.
 *  
 *  Parameters:
 *    
 *    inDialog:
 *      The dialog to dispose
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
NavDialogDispose(NavDialogRef inDialog)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavDialogGetWindow()
 *  
 *  Summary:
 *    Return the window in which a Nav Services dialog appears
 *  
 *  Discussion:
 *    Note that a valid NavDialogRef may not have a window until
 *    NavDialogRun has been called. If no window exists for the dialog,
 *    NavDialogGetWindow returns NULL.
 *  
 *  Parameters:
 *    
 *    inDialog:
 *      Which dialog
 *  
 *  Result:
 *    The window reference
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern WindowRef 
NavDialogGetWindow(NavDialogRef inDialog)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavDialogGetUserAction()
 *  
 *  Summary:
 *    Return the current user action taken by the user
 *  
 *  Discussion:
 *    A user action occurs when the user dismisses the dialog or
 *    otherwise does something generating a reply record that the
 *    client needs to act upon. If the user has not taken such an
 *    action, NavDialogGetUserAction returns kNavUserActionNone. If the
 *    dialog is terminated using the NavCustomControl selector
 *    kNavCtlTerminate, the final user action is kNavUserActionNone.
 *    For file dialogs, if the final user action is not
 *    kNavUserActionCancel, then there is a valid reply record which
 *    can be obtained with NavDialogGetReply. Although the user action
 *    is sent to the client event proc as a kNavCBUserAction event,
 *    this function is provided as a convenience for clients of modal
 *    dialogs who may find it easier to get the user action immediately
 *    after NavDialogRun returns.
 *  
 *  Parameters:
 *    
 *    inDialog:
 *      Which dialog
 *  
 *  Result:
 *    The user action
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern NavUserAction 
NavDialogGetUserAction(NavDialogRef inDialog)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavDialogGetReply()
 *  
 *  Summary:
 *    Fill in the provided reply record with the results of a user
 *    action such as kNavUserActionOpen, kNavUserActionSaveAs, or
 *    kNavUserActionChoose.
 *  
 *  Discussion:
 *    Call this function when a file dialog receives a user action
 *    other that implies an item or items to open, save, etc. Upon
 *    successful completion, the reply record describes the item(s)
 *    that the client needs to act upon. The reply record should later
 *    be disposed of with NavDisposeReply.
 *  
 *  Parameters:
 *    
 *    inDialog:
 *      Which dialog
 *    
 *    outReply:
 *      A pointer to the client-allocated reply record to be filled in
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavDialogGetReply(
  NavDialogRef      inDialog,
  NavReplyRecord *  outReply)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavDialogGetSaveFileName()
 *  
 *  Summary:
 *    Return the current value of the file name to be saved in a
 *    PutFile dialog
 *  
 *  Discussion:
 *    This function can be called at any time on a valid PutFile dialog
 *    to obtain the current value of the save file name. This function
 *    is a Unicode-based replacement for the kNavCtlGetEditFileName
 *    NavCustomControl selector. On Mac OS X, the full file name is
 *    returned, including any extenison that may be hidden from the
 *    user.
 *  
 *  Parameters:
 *    
 *    inPutFileDialog:
 *      Which dialog
 *  
 *  Result:
 *    The save file name as a CFStringRef. The string is immutable. The
 *    client should retain the string if the reference is to be held
 *    beyond the life of the dialog (standard CF retain/release
 *    semantics).
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
NavDialogGetSaveFileName(NavDialogRef inPutFileDialog)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  NavDialogSetSaveFileName()
 *  
 *  Summary:
 *    Set the current value of the file name to be saved in a PutFile
 *    dialog
 *  
 *  Discussion:
 *    This function can be called at any time to set the current save
 *    file name. Use it to set an initial name before calling
 *    NavDialogRun or to change the file name dynamically while a
 *    dialog is running. This function is a Unicode-based replacement
 *    for the kNavCtlSetEditFileName NavCustomControl selector.
 *  
 *  Parameters:
 *    
 *    inPutFileDialog:
 *      Which PutFile dialog
 *    
 *    inFileName:
 *      The file name to use. A copy of the provided string is made for
 *      use by Navigation Services.
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavDialogSetSaveFileName(
  NavDialogRef   inPutFileDialog,
  CFStringRef    inFileName)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NavDialogGetSaveFileExtensionHidden()
 *  
 *  Summary:
 *    Get the current state of the extension hiding in a PutFile dialog
 *  
 *  Discussion:
 *    This function can be called at any time to determine if a PutFile
 *    dialog is hiding the file extesion (if any) of the file to be
 *    saved.
 *  
 *  Parameters:
 *    
 *    inPutFileDialog:
 *      Which PutFile dialog
 *  
 *  Result:
 *    True if the extension is hidden, false if the extension is
 *    visible or there is no extension.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
NavDialogGetSaveFileExtensionHidden(NavDialogRef inPutFileDialog) AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/*
 *  NavDialogSetSaveFileExtensionHidden()
 *  
 *  Summary:
 *    Set the current state of the extension hiding in a PutFile dialog
 *  
 *  Discussion:
 *    This function can be called at any time to hide or show the
 *    extension of the file to be saved in a PutFile dialog. If the
 *    current file name has no extension, then hiding the extension has
 *    no effect.
 *  
 *  Parameters:
 *    
 *    inPutFileDialog:
 *      Which PutFile dialog
 *    
 *    inHidden:
 *      The new value for the hidden extension state
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavDialogSetSaveFileExtensionHidden(
  NavDialogRef   inPutFileDialog,
  Boolean        inHidden)                                    AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  NavDialogSetFilterTypeIdentifiers()
 *  
 *  Summary:
 *    Set a list Uniform Type Identifers against which all files will
 *    be automatically filtered.
 *  
 *  Discussion:
 *    This function can be called at any time to filter files shown in
 *    the dialog based on the list of type identifiers provided. This
 *    function is only applicable for GetFile and ChooseFile dialogs.
 *  
 *  Parameters:
 *    
 *    inGetFileDialog:
 *      Which GetFile or ChooseFile dialog.
 *    
 *    inTypeIdentifiers:
 *      The list of Uniform Type Identifiers describing the file types
 *      to be shown in the dialog file browser.  If an empty array is
 *      passed, all files will be filtered out. If NULL, no files are
 *      filtered. The "Enable" popup view will be automatically shown
 *      and hidden as necessary.
 *  
 *  Result:
 *    A status code
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NavDialogSetFilterTypeIdentifiers(
  NavDialogRef   inGetFileDialog,
  CFArrayRef     inTypeIdentifiers)       /* can be NULL */   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __NAVIGATION__ */


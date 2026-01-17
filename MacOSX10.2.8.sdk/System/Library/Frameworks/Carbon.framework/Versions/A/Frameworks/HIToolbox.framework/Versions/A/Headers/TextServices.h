/*
     File:       HIToolbox/TextServices.h
 
     Contains:   Text Services Manager Interfaces.
 
     Version:    HIToolbox-124.14~2
 
     Copyright:  © 1991-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __TEXTSERVICES__
#define __TEXTSERVICES__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
#endif

#ifndef __MENUS__
#include <HIToolbox/Menus.h>
#endif

#ifndef __AEINTERACTION__
#include <HIToolbox/AEInteraction.h>
#endif

#ifndef __CARBONEVENTS__
#include <HIToolbox/CarbonEvents.h>
#endif

#ifndef __ATSUNICODE__
#include <QD/ATSUnicode.h>
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
  kTextService                  = 'tsvc', /* component type for the component description */
  kTSMVersion                   = 0x0150 /* Version of the Text Services Manager is 1.5 */
};


/*
    TextServiceClass constants supported by TSM
    Same as component subtype for the component description
*/
enum {
  kKeyboardInputMethodClass     = 'inpm',
  kInkInputMethodClass          = 'ink ',
  kCharacterPaletteInputMethodClass = 'cplt'
};

typedef OSType                          TextServiceClass;
enum {
  kTSClassHonorUserSetting      = 1,
  kTSClassForceSetting          = 2,
  kTSClassForceToHonorUserSetting = 3
};

typedef UInt32                          TSClassEnablingForceLevel;
enum {
  kUnicodeDocument              = 'udoc', /* TSM Document type for Unicode-savvy application */
  kUnicodeTextService           = 'utsv' /* Component type for Unicode Text Service */
};

/* TSMDocumentID property tags*/
enum {
  kTSMDocumentPropertySupportGlyphInfo = 'dpgi' /*  property value is arbitrary*/
};


/* Language and Script constants*/
enum {
  kUnknownLanguage              = 0xFFFF,
  kUnknownScript                = 0xFFFF,
  kNeutralScript                = 0xFFFF
};


enum {
  kTextServiceVersion2          = 'tsv2' /* Interface type for V2 interfaces */
};

/* Standard collection tags*/

enum {
  kInteractiveServicesTag       = 'tmin',
  kLocaleIDTag                  = 'loce',
  kTextInputObjectTag           = 'tiot',
  kLocaleObjectRefTag           = 'lobj',
  kLocaleRefTag                 = 'lref',
  kKeyboardInputMethodContextTag = 'kinp',
  kKeyboardLocaleObjectRefTag   = 'kilo',
  kHandwritingInputMethodContextTag = 'hinp',
  kHandwritingLocaleObjectRefTag = 'hilo',
  kSpeechInputMethodContextTag  = 'sinp',
  kSpeechLocaleObjectRefTag     = 'silo',
  kPasswordModeTag              = 'pwdm',
  kRefconTag                    = 'refc',
  kUseFloatingWindowTag         = 'uswm',
  kReadOnlyDocumentTag          = 'isro',
  kSupportsMultiInlineHolesTag  = 'minl',
  kProtocolVersionTag           = 'nprt',
  kTSMContextCollectionTag      = 'tsmx'
};

/* Standard tags for input method modes*/

enum {
  kIMRomanInputMode             = 'romn',
  kIMPasswordInputMode          = 'pasw',
  kIMXingInputMode              = 'xing',
  kIMHuaInputMode               = 'huam',
  kIMPinyinInputMode            = 'piny',
  kIMQuweiInputMode             = 'quwe',
  kIMCangjieInputMode           = 'cgji',
  kIMJianyiInputMode            = 'jnyi',
  kIMZhuyinInputMode            = 'zhuy',
  kIMB5CodeInputMode            = 'b5cd',
  kIMKatakanaInputMode          = 'kata',
  kIMHiraganaInputMode          = 'hira'
};

/* Variant tags for the input modes*/

enum {
  kIM2ByteInputMode             = '2byt',
  kIM1ByteInputMode             = '1byt',
  kIMDirectInputMode            = 'dinp'
};


/* Text Services LocaleObject Attributes*/

#define kKeyboardInputMethodTypeName        "\pkeyboardinputmethod"
#define kHandwritingInputMethodTypeName     "\phandwritinginputmethod"
#define kSpeechInputMethodTypeName          "\pspeechinputmethod"
#define kTokenizeServiceTypeName            "\ptokenizetextservice"
#define kInteractiveTextServiceTypeName     "\pinteractivetextservice"
#define kInputMethodModeName                "\pinputmethodmode"
#define kInputMethodModeVariantName         "\pinputmethodvariantmode"
#define kTextServiceModeName                "\ptextservicemode"
#define kTextServiceNeedsInlineAppMode      "\ptextservicesneedsinlineapp"
#define kTextServiceNeedsGetProtocolMode    "\ptextservicesneedsGetProtocol"
#define kTextServiceAnyAppMode              "\ptextservicesanyapp"
enum {
  kNeedsInputWindow             = 1,
  kHandlesUpdateRegion          = 2,
  kHandlesGetRegion             = 3,
  kHandlesPos2Offset            = 4,
  kHandlesOffset2Pos            = 5,
  kInPasswordMode               = 6,
  kHandleMultipleHoles          = 7,
  kDocumentIsReadOnly           = 8
};

enum {
                                        /* Component Flags in ComponentDescription */
  bTakeActiveEvent              = 15,   /* bit set if the component takes active event */
  bHandleAERecording            = 16,   /* bit set if the component takes care of recording Apple Events <new in vers2.0> */
  bScriptMask                   = 0x00007F00, /* bit 8 - 14 */
  bLanguageMask                 = 0x000000FF, /* bit 0 - 7  */
  bScriptLanguageMask           = bScriptMask + bLanguageMask /* bit 0 - 14  */
};

enum {
                                        /* Typing method property constants for Input Methods */
  kIMJaTypingMethodProperty     = 'jtyp', /* Typing method property for Japanese input methods*/
  kIMJaTypingMethodRoman        = 'roma', /* Roman typing*/
  kIMJaTypingMethodKana         = 'kana' /* Kana typing*/
};

enum {
                                        /* Low level routines which are dispatched directly to the Component Manager */
  kCMGetScriptLangSupport       = 0x0001, /* Component Manager call selector 1 */
  kCMInitiateTextService        = 0x0002, /* Component Manager call selector 2 */
  kCMTerminateTextService       = 0x0003, /* Component Manager call selector 3 */
  kCMActivateTextService        = 0x0004, /* Component Manager call selector 4 */
  kCMDeactivateTextService      = 0x0005, /* Component Manager call selector 5 */
  kCMTextServiceEvent           = 0x0006, /* Component Manager call selector 6 */
  kCMGetTextServiceMenu         = 0x0007, /* Component Manager call selector 7 */
  kCMTextServiceMenuSelect      = 0x0008, /* Component Manager call selector 8 */
  kCMFixTextService             = 0x0009, /* Component Manager call selector 9 */
  kCMSetTextServiceCursor       = 0x000A, /* Component Manager call selector 10 */
  kCMHidePaletteWindows         = 0x000B, /* Component Manager call selector 11 */
  kCMGetTextServiceProperty     = 0x000C, /* Component Manager call selector 12 */
  kCMSetTextServiceProperty     = 0x000D /* Component Manager call selector 13 */
};

enum {
                                        /* New low level routines which are dispatched directly to the Component Manager */
  kCMUCTextServiceEvent         = 0x000E /* Component Manager call selector 14 */
};


/* extract Script/Language code from Component flag ... */
#define     mGetScriptCode(cdRec)       ((ScriptCode)   ((cdRec.componentFlags & bScriptMask) >> 8))
#define     mGetLanguageCode(cdRec)     ((LangCode)     cdRec.componentFlags & bLanguageMask)

/* New opaque definitions for types */
typedef struct OpaqueTSMContext*        TSMContext;
typedef struct OpaqueTSMDocumentID*     TSMDocumentID;
typedef OSType                          InterfaceTypeList[1];

/* Text Service Info List */
struct TextServiceInfo {
  Component           fComponent;
  Str255              fItemName;
};
typedef struct TextServiceInfo          TextServiceInfo;
typedef TextServiceInfo *               TextServiceInfoPtr;
struct TextServiceList {
  short               fTextServiceCount;      /* number of entries in the 'fServices' array */
  TextServiceInfo     fServices[1];           /* Note: array of 'TextServiceInfo' records follows */
};
typedef struct TextServiceList          TextServiceList;
typedef TextServiceList *               TextServiceListPtr;
typedef TextServiceListPtr *            TextServiceListHandle;
struct ScriptLanguageRecord {
  ScriptCode          fScript;
  LangCode            fLanguage;
};
typedef struct ScriptLanguageRecord     ScriptLanguageRecord;
struct ScriptLanguageSupport {
  short               fScriptLanguageCount;   /* number of entries in the 'fScriptLanguageArray' array */
  ScriptLanguageRecord  fScriptLanguageArray[1]; /* Note: array of 'ScriptLanguageRecord' records follows */
};
typedef struct ScriptLanguageSupport    ScriptLanguageSupport;
typedef ScriptLanguageSupport *         ScriptLanguageSupportPtr;
typedef ScriptLanguageSupportPtr *      ScriptLanguageSupportHandle;
struct TSMGlyphInfo {
  CFRange             range;                  /*    two SInt32s*/
  ATSFontRef          fontRef;
  UInt16              collection;             /*    kGlyphCollectionXXX enum*/
  UInt16              glyphID;                /*    GID (when collection==0) or CID*/
};
typedef struct TSMGlyphInfo             TSMGlyphInfo;
struct TSMGlyphInfoArray {
  ItemCount           numGlyphInfo;           /*    UInt32*/
  TSMGlyphInfo        glyphInfo[1];
};
typedef struct TSMGlyphInfoArray        TSMGlyphInfoArray;

/* High level TSM Doucment routines */
/*
 *  NewTSMDocument()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
NewTSMDocument(
  short               numOfInterface,
  InterfaceTypeList   supportedInterfaceTypes,
  TSMDocumentID *     idocID,
  long                refcon)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DeleteTSMDocument()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DeleteTSMDocument(TSMDocumentID idocID)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ActivateTSMDocument()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
ActivateTSMDocument(TSMDocumentID idocID)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DeactivateTSMDocument()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DeactivateTSMDocument(TSMDocumentID idocID)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FixTSMDocument()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FixTSMDocument(TSMDocumentID idocID)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetServiceList()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetServiceList(
  short                    numOfInterface,
  OSType *                 supportedInterfaceTypes,
  TextServiceListHandle *  serviceInfo,
  long *                   seedValue)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenTextService()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
OpenTextService(
  TSMDocumentID        idocID,
  Component            aComponent,
  ComponentInstance *  aComponentInstance)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CloseTextService()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
CloseTextService(
  TSMDocumentID       idocID,
  ComponentInstance   aComponentInstance)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SendAEFromTSMComponent()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SendAEFromTSMComponent(
  const AppleEvent *  theAppleEvent,
  AppleEvent *        reply,
  AESendMode          sendMode,
  AESendPriority      sendPriority,
  long                timeOutInTicks,
  AEIdleUPP           idleProc,
  AEFilterUPP         filterProc)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SendTextInputEvent()
 *  
 *  Discussion:
 *    This API replaces SendAEFromTSMComponent on Mac OS X only. Input
 *    Methods on Mac OS X are Carbon Event based instead of AppleEvent
 *    based.  The Carbon TextInput events which they generate are
 *    provided to TSM for dispatching via this API.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib N.e.v.e.r and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SendTextInputEvent(EventRef inEvent)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetDefaultInputMethod()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetDefaultInputMethod(
  Component               ts,
  ScriptLanguageRecord *  slRecordPtr)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDefaultInputMethod()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetDefaultInputMethod(
  Component *             ts,
  ScriptLanguageRecord *  slRecordPtr)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTextServiceLanguage()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetTextServiceLanguage(ScriptLanguageRecord * slRecordPtr)    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTextServiceLanguage()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetTextServiceLanguage(ScriptLanguageRecord * slRecordPtr)    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UseInputWindow()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
UseInputWindow(
  TSMDocumentID   idocID,
  Boolean         useWindow)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TSMSetInlineInputRegion()
 *  
 *  Discussion:
 *    Tell TSM about the region occupied by an inline input session. If
 *    the location of certain mouse events (clicks, mouse moved) occur
 *    within the specified inline input region, TSM will forward these
 *    events to the current Input Method so that it can interact with
 *    the user. Note: If you do not specify this information, TSM will
 *    need to intercept mouse events in the entire content region as
 *    the default, when an input method is active, in order to ensure
 *    that input methods can manage user interaction properly.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inTSMDocument:
 *      The document.
 *    
 *    inWindow:
 *      The window that contains the inline input session. You can pass
 *      NULL for this parameter to indicate the user focus window.
 *    
 *    inRegion:
 *      The region occupied by the current inline input region. This
 *      should be in the coordinates of the port associated with the
 *      window you passed to inPort. It will need to be recomputed when
 *      the text content of the inline input session content changes
 *      (i.e. due to Update Active Input Area events) and when the
 *      region moves for other reasons, such as window resized,
 *      scrolling, etc. If you pass a NULL region for this parameter,
 *      TSM will default to intercept mouse events in the focus
 *      window's content region.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TSMSetInlineInputRegion(
  TSMDocumentID   inTSMDocument,
  WindowRef       inWindow,
  RgnHandle       inRegion)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Following calls from Classic event loops not needed for Carbon clients. */
/*
 *  TSMEvent()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  TSMMenuSelect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SetTSMCursor()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/* Following ServiceWindow API replaced by Window Manager API in Carbon. */
/*
 *  NewServiceWindow()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  CloseServiceWindow()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetFrontServiceWindow()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  FindServiceWindow()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  NewCServiceWindow()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */


/* Explicit initialization not needed for Carbon clients, since TSM is */
/* instanciated per-context. */
/*
 *  InitTSMAwareApplication()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  CloseTSMAwareApplication()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */



/* Component Manager Interfaces to Input Methods */
/*
 *  GetScriptLanguageSupport()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
GetScriptLanguageSupport(
  ComponentInstance              ts,
  ScriptLanguageSupportHandle *  scriptHdl)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InitiateTextService()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
InitiateTextService(ComponentInstance ts)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TerminateTextService()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
TerminateTextService(ComponentInstance ts)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ActivateTextService()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
ActivateTextService(ComponentInstance ts)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DeactivateTextService()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
DeactivateTextService(ComponentInstance ts)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTextServiceMenu()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
GetTextServiceMenu(
  ComponentInstance   ts,
  MenuRef *           serviceMenu)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* New Text Service call in Carbon. */
/* Note: Only Raw Key and Mouse-flavored events are passed to Text Services on MacOS X. */
/*
 *  TextServiceEventRef()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
TextServiceEventRef(
  ComponentInstance   ts,
  EventRef            event)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextServiceEvent()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  UCTextServiceEvent()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */


/*
 *  TextServiceMenuSelect()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SetTextServiceCursor()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  FixTextService()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
FixTextService(ComponentInstance ts)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  HidePaletteWindows()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
HidePaletteWindows(ComponentInstance ts)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTextServiceProperty()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
GetTextServiceProperty(
  ComponentInstance   ts,
  OSType              propertySelector,
  SInt32 *            result)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTextServiceProperty()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
SetTextServiceProperty(
  ComponentInstance   ts,
  OSType              propertySelector,
  SInt32              value)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Get the active TSMDocument in the current application context.       */
/* If TSM has enabled bottom line input mode because no TSMDocument     */
/* is active, NULL will be returned.                                    */
/*
 *  TSMGetActiveDocument()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern TSMDocumentID 
TSMGetActiveDocument(void)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDefaultInputMethodOfClass()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetDefaultInputMethodOfClass(
  Component *             aComp,
  ScriptLanguageRecord *  slRecPtr,
  TextServiceClass        tsClass)                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SetDefaultInputMethodOfClass()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetDefaultInputMethodOfClass(
  Component               aComp,
  ScriptLanguageRecord *  slRecPtr,
  TextServiceClass        tsClass)                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  DeselectTextService()
 *  
 *  Discussion:
 *    This API is currently only intended for use by Character Palette
 *    class input methods. It allows such an input method to notify TSM
 *    that it has been closed by the user as a result of interaction
 *    with the input method's own UI, such a palette window's close
 *    button, instead of via the normal UI provided by the System, such
 *    as the Keyboard Menu.  Note that this API is only meant for use
 *    with "additive" text service classes (such as Character
 *    Palettes), and not with traditional input methods which are
 *    exclusively selected in a given class and script, such as
 *    keyboard input methods.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
DeselectTextService(Component aComp)                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SelectTextService()
 *  
 *  Discussion:
 *    This API is currently only intended for use by the system UI
 *    (Keyboard Menu or prefs panel) and input methods that wish to set
 *    to the "selected" state a text service which is "additive" in
 *    nature.  It is not intended for use with input methods that are
 *    "exclusive" in nature (see DeselectTextService).  It allows an
 *    input method to notify TSM that it has been selected by the user
 *    as a result of interaction with some UI (possibly another input
 *    method), instead of via the normal UI provided by the System,
 *    such as the Keyboard Menu.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SelectTextService(Component aComp)                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  TSMSetDocumentProperty()
 *  
 *  Discussion:
 *    This API is currently only needed for applications that wish to
 *    signal to TSM that it supports GlyphID specification in TSM
 *    events containing Unicode text (see
 *    kTSMDocumentPropertySupportGlyphInfo).  Input Methods call
 *    TSMGetDocumentProperty() against the currently active TSMDocument
 *    to test whether the app supports this glyph info. These TSM
 *    property API can also be freely used by applications to relate
 *    arbitrary data to a given TSMDocument.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TSMSetDocumentProperty(
  TSMDocumentID   docID,
  OSType          propertyTag,
  UInt32          propertySize,
  void *          propertyData)                               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  TSMGetDocumentProperty()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TSMGetDocumentProperty(
  TSMDocumentID   docID,
  OSType          propertyTag,
  UInt32          bufferSize,
  UInt32 *        actualSize,
  void *          propertyBuffer)       /* can be NULL */     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  TSMRemoveDocumentProperty()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TSMRemoveDocumentProperty(
  TSMDocumentID   docID,
  OSType          propertyTag)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


#if OLDROUTINENAMES
enum {
  kInputMethodService           = kKeyboardInputMethodClass
};

#endif  /* OLDROUTINENAMES */


#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __TEXTSERVICES__ */


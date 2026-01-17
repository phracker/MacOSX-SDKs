/*
     File:       HIToolbox/TextServices.h
 
     Contains:   Text Services Manager Interfaces.
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1991-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __TEXTSERVICES__
#define __TEXTSERVICES__

#ifndef __CONDITIONALMACROS__
#include <CarbonCore/ConditionalMacros.h>
#endif

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
#endif

#ifndef __MENUS__
#include <HIToolbox/Menus.h>
#endif

#ifndef __AEDATAMODEL__
#include <AE/AEDataModel.h>
#endif

#ifndef __AEREGISTRY__
#include <AE/AERegistry.h>
#endif

#ifndef __AEINTERACTION__
#include <HIToolbox/AEInteraction.h>
#endif

#ifndef __COMPONENTS__
#include <CarbonCore/Components.h>
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
  kTextService                  = 'tsvc', /* component type for the component description */
  kInputMethodService           = 'inpm', /* component subtype for the component description */
  kTSMVersion                   = 0x0150 /* Version of the Text Services Manager is 1.5 */
};

enum {
  kUnicodeDocument              = 'udoc', /* TSM Document type for Unicode-savvy application */
  kUnicodeTextService           = 'utsv' /* Component type for Unicode Text Service */
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
/* High level TSM Doucment routines */
/*
 *  NewTSMDocument()
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
  long                refcon);


/*
 *  DeleteTSMDocument()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DeleteTSMDocument(TSMDocumentID idocID);


/*
 *  ActivateTSMDocument()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
ActivateTSMDocument(TSMDocumentID idocID);


/*
 *  DeactivateTSMDocument()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DeactivateTSMDocument(TSMDocumentID idocID);


/*
 *  FixTSMDocument()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FixTSMDocument(TSMDocumentID idocID);


/*
 *  GetServiceList()
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
  long *                   seedValue);


/*
 *  OpenTextService()
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
  ComponentInstance *  aComponentInstance);


/*
 *  CloseTextService()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
CloseTextService(
  TSMDocumentID       idocID,
  ComponentInstance   aComponentInstance);


/*
 *  SendAEFromTSMComponent()
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
  AEFilterUPP         filterProc);


/*
 *  SendTextInputEvent()
 *  
 *  Discussion:
 *    This API replaces SendAEFromTSMComponent on Mac OS X only. Input
 *    Methods on Mac OS X are Carbon Event based instead of AppleEvent
 *    based.  The Carbon TextInput events which they generate are
 *    provided to TSM for dispatching via this API.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib N.e.v.e.r and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SendTextInputEvent(EventRef inEvent);


/*
 *  SetDefaultInputMethod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetDefaultInputMethod(
  Component               ts,
  ScriptLanguageRecord *  slRecordPtr);


/*
 *  GetDefaultInputMethod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetDefaultInputMethod(
  Component *             ts,
  ScriptLanguageRecord *  slRecordPtr);


/*
 *  SetTextServiceLanguage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetTextServiceLanguage(ScriptLanguageRecord * slRecordPtr);


/*
 *  GetTextServiceLanguage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetTextServiceLanguage(ScriptLanguageRecord * slRecordPtr);


/*
 *  UseInputWindow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
UseInputWindow(
  TSMDocumentID   idocID,
  Boolean         useWindow);


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
  RgnHandle       inRegion);



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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
GetScriptLanguageSupport(
  ComponentInstance              ts,
  ScriptLanguageSupportHandle *  scriptHdl);


/*
 *  InitiateTextService()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
InitiateTextService(ComponentInstance ts);


/*
 *  TerminateTextService()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
TerminateTextService(ComponentInstance ts);


/*
 *  ActivateTextService()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
ActivateTextService(ComponentInstance ts);


/*
 *  DeactivateTextService()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
DeactivateTextService(ComponentInstance ts);


/*
 *  GetTextServiceMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
GetTextServiceMenu(
  ComponentInstance   ts,
  MenuRef *           serviceMenu);


/* New Text Service call in Carbon. */
/* Note: Only Raw Key and Mouse-flavored events are passed to Text Services on MacOS X. */
/*
 *  TextServiceEventRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern ComponentResult 
TextServiceEventRef(
  ComponentInstance   ts,
  EventRef            event);


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
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
FixTextService(ComponentInstance ts);


/*
 *  HidePaletteWindows()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern ComponentResult 
HidePaletteWindows(ComponentInstance ts);


/*
 *  GetTextServiceProperty()
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
  SInt32 *            result);


/*
 *  SetTextServiceProperty()
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
  SInt32              value);


/* Get the active TSMDocument in the current application context.       */
/* If TSM has enabled bottom line input mode because no TSMDocument     */
/* is active, NULL will be returned.                                    */
/*
 *  TSMGetActiveDocument()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   not available
 */
extern TSMDocumentID 
TSMGetActiveDocument(void);




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

#endif /* __TEXTSERVICES__ */


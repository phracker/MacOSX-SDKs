/*
     File:       HIToolbox/Events.h
 
     Contains:   Event Manager Interfaces.
 
     Version:    HIToolbox-227.3~63
 
     Copyright:  © 1985-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __EVENTS__
#define __EVENTS__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

typedef UInt16                          EventKind;
typedef UInt16                          EventMask;
enum {
  nullEvent                     = 0,
  mouseDown                     = 1,
  mouseUp                       = 2,
  keyDown                       = 3,
  keyUp                         = 4,
  autoKey                       = 5,
  updateEvt                     = 6,
  diskEvt                       = 7,    /* Not sent in Carbon. See kEventClassVolume in CarbonEvents.h*/
  activateEvt                   = 8,
  osEvt                         = 15,
  kHighLevelEvent               = 23
};

enum {
  mDownMask                     = 1 << mouseDown, /* mouse button pressed*/
  mUpMask                       = 1 << mouseUp, /* mouse button released*/
  keyDownMask                   = 1 << keyDown, /* key pressed*/
  keyUpMask                     = 1 << keyUp, /* key released*/
  autoKeyMask                   = 1 << autoKey, /* key repeatedly held down*/
  updateMask                    = 1 << updateEvt, /* window needs updating*/
  diskMask                      = 1 << diskEvt, /* disk inserted*/
  activMask                     = 1 << activateEvt, /* activate/deactivate window*/
  highLevelEventMask            = 0x0400, /* high-level events (includes AppleEvents)*/
  osMask                        = 1 << osEvt, /* operating system events (suspend, resume)*/
  everyEvent                    = 0xFFFF /* all of the above*/
};

enum {
  charCodeMask                  = 0x000000FF,
  keyCodeMask                   = 0x0000FF00,
  adbAddrMask                   = 0x00FF0000,
  osEvtMessageMask              = (unsigned long)0xFF000000
};

enum {
                                        /* OS event messages.  Event (sub)code is in the high byte of the message field.*/
  mouseMovedMessage             = 0x00FA,
  suspendResumeMessage          = 0x0001
};

enum {
  resumeFlag                    = 1     /* Bit 0 of message indicates resume vs suspend*/
};

#if CALL_NOT_IN_CARBON
/*  convertClipboardFlag is not ever set under Carbon. This is because scrap conversion is  */
/*  not tied to suspend/resume events any longer. Your application should instead use the   */
/*  scrap promise mechanism and fulfill scrap requests only when your promise keeper proc   */
/*  is called. If you need to know if the scrap has changed, you can cache the last         */
/*  ScrapRef you received and compare it with the current ScrapRef                          */
enum {
  convertClipboardFlag          = 2     /* Bit 1 in resume message indicates clipboard change*/
};

#endif  /* CALL_NOT_IN_CARBON */

/*
    CARBON ALERT! BATTLESTATIONS!
    
    The EventModifiers bits defined here are also used in the newer Carbon Event
    key modifiers parameters. There are two main differences:
    
    1)  The Carbon key modifiers parameter is a UInt32, not a UInt16. Never try to
        extract the key modifiers parameter from a Carbon Event into an EventModifiers
        type. You will probably get your stack trashed.
    2)  The Carbon key modifiers is just that: key modifiers. That parameter will
        never contain the button state bit.
*/
typedef UInt16                          EventModifiers;
enum {
                                        /* modifiers */
  activeFlagBit                 = 0,    /* activate? (activateEvt and mouseDown)*/
  btnStateBit                   = 7,    /* state of button?*/
  cmdKeyBit                     = 8,    /* command key down?*/
  shiftKeyBit                   = 9,    /* shift key down?*/
  alphaLockBit                  = 10,   /* alpha lock down?*/
  optionKeyBit                  = 11,   /* option key down?*/
  controlKeyBit                 = 12,   /* control key down?*/
  rightShiftKeyBit              = 13,   /* right shift key down? Not supported on Mac OS X.*/
  rightOptionKeyBit             = 14,   /* right Option key down? Not supported on Mac OS X.*/
  rightControlKeyBit            = 15    /* right Control key down? Not supported on Mac OS X.*/
};

enum {
  activeFlag                    = 1 << activeFlagBit,
  btnState                      = 1 << btnStateBit,
  cmdKey                        = 1 << cmdKeyBit,
  shiftKey                      = 1 << shiftKeyBit,
  alphaLock                     = 1 << alphaLockBit,
  optionKey                     = 1 << optionKeyBit,
  controlKey                    = 1 << controlKeyBit,
  rightShiftKey                 = 1 << rightShiftKeyBit, /* Not supported on Mac OS X.*/
  rightOptionKey                = 1 << rightOptionKeyBit, /* Not supported on Mac OS X.*/
  rightControlKey               = 1 << rightControlKeyBit /* Not supported on Mac OS X.*/
};

/* MacRoman character codes*/
enum {
  kNullCharCode                 = 0,
  kHomeCharCode                 = 1,
  kEnterCharCode                = 3,
  kEndCharCode                  = 4,
  kHelpCharCode                 = 5,
  kBellCharCode                 = 7,
  kBackspaceCharCode            = 8,
  kTabCharCode                  = 9,
  kLineFeedCharCode             = 10,
  kVerticalTabCharCode          = 11,
  kPageUpCharCode               = 11,
  kFormFeedCharCode             = 12,
  kPageDownCharCode             = 12,
  kReturnCharCode               = 13,
  kFunctionKeyCharCode          = 16,
  kCommandCharCode              = 17,   /* glyph available only in system fonts*/
  kCheckCharCode                = 18,   /* glyph available only in system fonts*/
  kDiamondCharCode              = 19,   /* glyph available only in system fonts*/
  kAppleLogoCharCode            = 20,   /* glyph available only in system fonts*/
  kEscapeCharCode               = 27,
  kClearCharCode                = 27,
  kLeftArrowCharCode            = 28,
  kRightArrowCharCode           = 29,
  kUpArrowCharCode              = 30,
  kDownArrowCharCode            = 31,
  kSpaceCharCode                = 32,
  kDeleteCharCode               = 127,
  kBulletCharCode               = 165,
  kNonBreakingSpaceCharCode     = 202
};

/* useful Unicode code points*/
enum {
  kShiftUnicode                 = 0x21E7, /* Unicode UPWARDS WHITE ARROW*/
  kControlUnicode               = 0x2303, /* Unicode UP ARROWHEAD*/
  kOptionUnicode                = 0x2325, /* Unicode OPTION KEY*/
  kCommandUnicode               = 0x2318, /* Unicode PLACE OF INTEREST SIGN*/
  kPencilUnicode                = 0x270E, /* Unicode LOWER RIGHT PENCIL; actually pointed left until Mac OS X 10.3*/
  kPencilLeftUnicode            = 0xF802, /* Unicode LOWER LEFT PENCIL; available in Mac OS X 10.3 and later*/
  kCheckUnicode                 = 0x2713, /* Unicode CHECK MARK*/
  kDiamondUnicode               = 0x25C6, /* Unicode BLACK DIAMOND*/
  kBulletUnicode                = 0x2022, /* Unicode BULLET*/
  kAppleLogoUnicode             = 0xF8FF /* Unicode APPLE LOGO*/
};

struct EventRecord {
  EventKind           what;
  UInt32              message;
  UInt32              when;
  Point               where;
  EventModifiers      modifiers;
};
typedef struct EventRecord              EventRecord;
typedef CALLBACK_API( void , FKEYProcPtr )(void);
typedef STACK_UPP_TYPE(FKEYProcPtr)                             FKEYUPP;
/*
 *  NewFKEYUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeFKEYUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeFKEYUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  GetMouse()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetMouse(Point * mouseLoc)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Button()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
Button(void)                                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StillDown()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
StillDown(void)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WaitMouseUp()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
WaitMouseUp(void)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  KeyTranslate()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt32 
KeyTranslate(
  const void *  transData,
  UInt16        keycode,
  UInt32 *      state)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetCaretTime()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt32 
GetCaretTime(void)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* 
    QuickTime 3.0 supports GetKeys() on unix and win32
    But, on little endian machines you will have to be
    careful about bit numberings and/or use a KeyMapByteArray
    instead.
*/
#if TARGET_API_MAC_OS8

typedef UInt32                          KeyMap[4];
#else
typedef BigEndianLong                   KeyMap[4];
#endif  /* TARGET_API_MAC_OS8 */

typedef UInt8                           KeyMapByteArray[16];
/*
 *  GetKeys()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
GetKeys(KeyMap theKeys)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Obsolete event types & masks */
enum {
  networkEvt                    = 10,
  driverEvt                     = 11,
  app1Evt                       = 12,
  app2Evt                       = 13,
  app3Evt                       = 14,
  app4Evt                       = 15,
  networkMask                   = 0x0400,
  driverMask                    = 0x0800,
  app1Mask                      = 0x1000,
  app2Mask                      = 0x2000,
  app3Mask                      = 0x4000,
  app4Mask                      = 0x8000
};

struct EvQEl {
  QElemPtr            qLink;
  SInt16              qType;
  EventKind           evtQWhat;               /* this part is identical to the EventRecord as defined above */
  UInt32              evtQMessage;
  UInt32              evtQWhen;
  Point               evtQWhere;
  EventModifiers      evtQModifiers;
};
typedef struct EvQEl                    EvQEl;
typedef EvQEl *                         EvQElPtr;
typedef CALLBACK_API( void , GetNextEventFilterProcPtr )(EventRecord *theEvent, Boolean *result);
typedef STACK_UPP_TYPE(GetNextEventFilterProcPtr)               GetNextEventFilterUPP;
/*
 *  NewGetNextEventFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  DisposeGetNextEventFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

/*
 *  InvokeGetNextEventFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */

typedef GetNextEventFilterUPP           GNEFilterUPP;
/*
 *  GetDblTime()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt32 
GetDblTime(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetEventMask()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
SetEventMask(EventMask value)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetEvQHdr()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PPostEvent()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetNextEvent()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
GetNextEvent(
  EventMask      eventMask,
  EventRecord *  theEvent)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  WaitNextEvent()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
WaitNextEvent(
  EventMask      eventMask,
  EventRecord *  theEvent,
  UInt32         sleep,
  RgnHandle      mouseRgn)        /* can be NULL */           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EventAvail()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
EventAvail(
  EventMask      eventMask,
  EventRecord *  theEvent)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PostEvent()
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
PostEvent(
  EventKind   eventNum,
  UInt32      eventMsg)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    For Carbon, use EventAvail, TickCount, GetGlobalMouse,
    GetKeys, or GetCurrentKeyModifiers instead of
    OSEventAvail, and use GetNextEvent or WaitNextEvent
    instead of GetOSEvent.
*/

/*
 *  OSEventAvail()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetOSEvent()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  FlushEvents()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
FlushEvents(
  EventMask   whichMask,
  EventMask   stopMask)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SystemClick()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SystemTask()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SystemEvent()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


#if OLDROUTINENAMES
#define KeyTrans(transData, keycode, state) KeyTranslate(transData, keycode, state)
#endif  /* OLDROUTINENAMES */

/*
    GetGlobalMouse, GetCurrentKeyModifiers, and CheckEventQueueForUserCancel
    are only available as part of the Carbon API.
*/

/*
 *  GetGlobalMouse()
 *  
 *  Summary:
 *    Returns the position of the mouse in global coordinates.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    globalMouse:
 *      On exit, contains the mouse position in global coordinates.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in CarbonAccessors.o 1.0 and later
 */
extern void 
GetGlobalMouse(Point * globalMouse)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetCurrentKeyModifiers()
 *  
 *  Summary:
 *    Returns the current hardware keyboard modifier state.
 *  
 *  Discussion:
 *    In most cases, you should not use GetCurrentKeyModifiers, but
 *    should use the GetCurrentEventKeyModifiers function instead.
 *    GetCurrentEventKeyModifiers is much faster than
 *    GetCurrentKeyModifiers because it returns the locally cached
 *    modifier state; GetCurrentKeyModifiers must get the modifier
 *    state from the window server, which is slower. Using
 *    GetCurrentKeyModifiers also can prevent your application from
 *    being operated by remote posting of events, since the hardware
 *    input device is not actually changing state in that case. Most
 *    commonly, you might need to use GetCurrentKeyModifiers when your
 *    application is not the active application (as determined by the
 *    Process Manager function GetFrontProcess). In that case, the
 *    cached modifier state returned by GetCurrentEventKeyModifiers is
 *    not valid because modifier-changed events are not flowing to your
 *    application, and you must use GetCurrentKeyModifiers to determine
 *    the current hardware state.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Result:
 *    The hardware state of the keyboard modifiers. The format of the
 *    return value is the same as the modifiers field of an EventRecord
 *    (but only includes keyboard modifiers and not the other modifier
 *    flags included in an EventRecord).
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern UInt32 
GetCurrentKeyModifiers(void)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CheckEventQueueForUserCancel()
 *  
 *  Summary:
 *    Determines if there is a cancel event in the main thread's event
 *    queue.
 *  
 *  Discussion:
 *    This API supports two cancel events: Escape and Cmd-Period. The
 *    cancel event itself, as well as mouse or keyboard events in front
 *    of the cancel event in the event queue, will be removed from the
 *    queue.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
CheckEventQueueForUserCancel(void)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  KeyScript()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
KeyScript(short code)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IsCmdChar()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
IsCmdChar(
  const EventRecord *  event,
  short                test)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* 
    LowMem accessor functions previously in LowMem.h
*/
/*
 *  LMGetKeyThresh()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16 
LMGetKeyThresh(void)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetKeyThresh()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetKeyThresh(SInt16 value)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetKeyRepThresh()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16 
LMGetKeyRepThresh(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetKeyRepThresh()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetKeyRepThresh(SInt16 value)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMGetKbdLast()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8 
LMGetKbdLast(void)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetKbdLast()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetKbdLast(UInt8 value)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  LMGetKbdType()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern UInt8 
LMGetKbdType(void)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LMSetKbdType()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
LMSetKbdType(UInt8 value)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __EVENTS__ */


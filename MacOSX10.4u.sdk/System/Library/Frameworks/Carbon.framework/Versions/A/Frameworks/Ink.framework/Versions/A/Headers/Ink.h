/*
     File:       Ink/Ink.h
 
     Contains:   Ink Manager
 
     Version:    InkFramework-71~854
 
     Copyright:  © 2003-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __INK__
#define __INK__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __HITOOLBOX__
#include <HIToolbox/HIToolbox.h>
#endif

#include <IOKit/hidsystem/IOLLEvent.h>


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k


/*
 *  Ink Manager
 */

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*  • Ink Events                                                                        */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
   Ink-related events are defined in CarbonEvents.h.  The
   following discussion gives some insight into when and how
   they are best used.
*/

/*
   When the pen is first pressed to the tablet, before inking
   has started, the Ink Manager must determine whether this
   pen-down should be treated as an inking or a mousing action. 
   If the pen-down occurs over certain user interface elements,
   that the user might reasonably expect to respond to immediate
   mouse input (such as the menubar, the Dock, a window’s
   titlebar, scrollbar, or controls in general), the Ink Manager
   will treat the pen as a mouse, and will not produce ink. This
   is known as “instant mousing”, and the user interface
   elements that force instant mousing are known as “instant
   mousers”.  When it is determined that the pen down did NOT
   occur over an instant mouser, the decision about whether to
   ink or mouse is still deferred briefly, and events are queued
   internally, until this decision can be made based on what the
   user does with the pen.  If the user moves the pen a
   sufficient distance, in a short enough time, then she is
   assumed to be writing, and all of the points in the internal
   queue, plus this point, will be treated as ink.  On the other
   hand, if the user holds the pen sufficiently still for a
   sufficient length of time, then it is assumed she wishes to
   use the pen as a mouse, so queued events are reposted and
   they, plus the current event, go unhandled by the Ink
   Manager, thus propagating to the application, where they will
   be handled as ordinary mouse events.
   In order to provide a consistent user experience with ink,
   and to avoid requiring applications to implement this complex
   bit of code themselves, while still allowing apps to:
     - do their own inking
     - handle special controls even while the Ink Manager is inking
     - define their own instant mousers
     - terminate phrases when app-specific conditions are met, such
       as the pen exiting a particular region of the window/screen
   all while letting the Ink Manager do the bulk of the work
   accumulating points into strokes, strokes into phrases,
   performing recognition, and posting high-level Ink
   events, the Ink Manager generates two special Carbon
   events to allow applications to manage the flow of pen events.
   The first of these, kEventApplicationIsEventInInstantMouser, 
   is dispatched only when a pen is initially pressed to a tablet,
   at the beginning of a phrase, before it has been determined
   whether the user is writing or not.  Once the user has begun
   writing, pen-downs will not generate these instant-mouser events.
   How the application responds to this event determines whether
   the Ink Manager is allowed to treat the pen-down as ink or not.
   Cocoa applications can implement the NSResponder method
   -shouldBeTreatedAsInkEvent for these purposes.
   This event allows clients to determine whether the current
   pen-down (mouseDown) event is over an application-defined
   instant mousing region. Application desiring to implement
   their own instant mousing controls or regions will need to
   register install a handler for this event.  This test will be
   performed early in the Ink Manager’s logic that determines
   whether an event should be treated as mouse or ink.  It only
   applies to new pen-downs (before inking has started).
   The second of these, kEventInkPoint, allows clients to
   see and potentially handle all pen events that the Ink
   Manager has determined correspond to inking (as opposed to
   mousing).  Here also the app installs an event handler. 
   These events, however, are dispatched only after the Ink Manager has
   decided the event corresponds to ink (user writing).  If the
   application handles the event (returns noErr), then the Ink
   Manager does nothing further with the event. If the
   application’s function returns any other value (including
   eventNotHandledErr), the point will be processed normally by
   the Ink Manager.  I.e., the point will be added to a stroke
   (old or new, depending on pen up/down state).  Note that this
   means the app will only see mouseDown and mouseDragged events
   in this handler, and they will always have tablet
   data in them.  This permits apps to:
     - draw their own ink, but only when the user would expect ink
     - prevent inking over special controls (e.g., a “Finished
       Writing” button an app might provide for a user to indicate
       she is done entering data into the current window or field)
     - terminate the current phrase (e.g., in response to that
       “Finished Writing” button)
   Applications that want to draw their own ink, while letting
   the Ink Manager deal with data accumulation and recognition,
   will want to install a handler for this event.  (To take over
   complete control of event handling, data accumulation, and
   recognition, apps can disable the Ink Manager’s processing of
   pen events entirely, by calling
   InkSetApplicationWritingMode(kInkWriteNowhereInApp) and
   handling pen events themselves.)
   If the handler returns noErr, indicating the app has chosen
   to handle this event and inhibiting further Ink Manager
   processing of the event, the event will go unhandled by the
   Ink Manager.  This results in the original mouse event being
   dispatched to the app through the normal Carbon Event Manager
   chain.  So apps should only make the decision that this event
   is one they wish to handle (or not), never carry out any of
   the actions the app might associate with the event in the
   handler (aside from inking, if the app is drawing the ink
   instead of relying on the Ink Manager to draw the ink).  The
   app should also do minimal processing in this handler because
   these events are generated at a rapid rate while the user is
   actively inking, and it is important not to introduce a lag
   in the inking process.  If the handler returns
   eventNotHandledErr, indicating the app has chosen NOT to
   handle this event, thus allowing the Ink Manager to process
   it normally, the Ink Manager will handle the event, and the
   app will not see this particular event again.
   When the Ink Manager is allowed to handle ink-point events
   and accumulate them into strokes and phrases internally,
   or when an application sends whole strokes’ worth of data
   (that it has accumulated) at a time to the Ink Manager, and
   the current phrase is terminated (either by the user or the
   application), two types of high-level ink events may be
   generated.
   The first of these high-level ink events is the
   kEventInkGesture event. This ink-gesture event is
   only sent when the Ink Manager has recognized the ink as one
   of the known system gestures (defined below).  Ink-aware
   applications can install a handler for these events, to
   provide targeted gestures and support for context-dependent
   (tentative) gestures, as discussed below.
   The second of these high-level ink events is the
   kEventInkText event. This ink-text event is sent
   when the Ink Manager has recognized the ink as text.  In
   Roman languages the ink-text event corresponds to an
   individual word.  It contains the original ink and the
   recognized text, typically including a number of alternate
   recognition hypotheses that ink-aware applications can offer
   to the user to enhance the ink/recognition experience.
*/



/*——————————————————————————————————————————————————————————————————————————————————————*/
/*  • Ink Types                                                                         */
/*——————————————————————————————————————————————————————————————————————————————————————*/


/*
 *  InkTextRef
 *  
 *  Discussion:
 *    Primary Ink opaque object reference for ink data and recognition
 *    results. Use CFRetain & CFRelease to manage all Ink object
 *    retention. When any Ink object reference is obtained from a
 *    Carbon event, it is only guaranteed to persist for the life of
 *    the event handler.  If the client wishes to use the object at
 *    some later time, it must perform a CFRetain on the object.
 */
typedef struct OpaqueInkTextRef*        InkTextRef;

/*
 *  InkStrokeRef
 *  
 *  Discussion:
 *    Opaque reference to individual Ink strokes. 
 *    
 *    Use CFRetain & CFRelease to manage all Ink object retention.
 *    
 *    
 *    If obtained from an InkTextRef, an InkStrokeRef is only
 *    guaranteed to persist for the life of that InkTextRef. If the
 *    client wishes to use the InkStrokeRef after the InkTextRef has
 *    been released, it must perform a CFRetain on the InkStrokeRef.
 *    
 *    
 *    When any Ink object reference is obtained from a Carbon event, it
 *    is only guaranteed to persist for the life of the event handler. 
 *    If the client wishes to use the object at some later time, it
 *    must perform a CFRetain on the object.
 */
typedef struct OpaqueInkStrokeRef*      InkStrokeRef;

/*
 *  InkPoint
 *  
 *  Discussion:
 *    An InkPoint contains the minimum per-point information needed to
 *    drive system inking and recognition.
 */
struct InkPoint {

  /*
   * The location for the mouse event (kEventParamMouseLocation from
   * the mouse event).
   */
  HIPoint             point;

  /*
   * Use the data from the kEventParamTabletPointRec contained in the
   * original mouse/tablet event.
   */
  TabletPointRec      tabletPointData;

  /*
   * The modifiers that were down when the original mouse event occured
   * (kEventParamKeyModifiers from the mouse event).
   */
  UInt32              keyModifiers;
};
typedef struct InkPoint                 InkPoint;
typedef InkPoint *                      InkPointPtr;

/*
 *  InkAlternateCount
 *  
 *  Discussion:
 *    Type used for counting and indexing alternates in InkTextRef.
 *    Defined for backward compatibility only.  APIs now take and
 *    return CFIndex.
 */
typedef CFIndex                         InkAlternateCount;
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*  • Ink Constants                                                                     */
/*——————————————————————————————————————————————————————————————————————————————————————*/


/*
 *  InkUserWritingModeType
 *  
 *  Discussion:
 *    User preference (system-wide) setting constants.
 */
typedef FourCharCode                    InkUserWritingModeType;
enum {
  kInkWriteNowhere              = 'nowh',
  kInkWriteAnywhere             = 'anyw',
  kInkWriteInInkAwareAppsOnly   = 'iapp'
};



/*
 *  InkApplicationWritingModeType
 *  
 *  Discussion:
 *    Application state setting constants.
 */
typedef FourCharCode                    InkApplicationWritingModeType;
enum {
  kInkWriteNowhereInApp         = 'nowa',
  kInkWriteAnywhereInApp        = 'anya'
};



/*
 *  InkDrawingModeType
 *  
 *  Summary:
 *    Application drawing setting constants.
 */
typedef UInt32 InkDrawingModeType;
enum {
  kInkDrawNothing               = 0,
  kInkDrawInkOnly               = 1,
  kInkDrawInkAndWritingGuides   = 2
};



/*
 *  InkTextDrawFlagsType
 *  
 *  Summary:
 *    Constants for drawing an InkTextRef.
 */
typedef UInt32 InkTextDrawFlagsType;
enum {

  /*
   * Draw the ink using the default system settings. By default, ink is
   * drawn with pressure sensitive gradients, and the CGContext
   * settings are overridden for line color and width.
   */
  kInkTextDrawDefault           = 0,

  /*
   * Don't draw using pressure sensitive gradients.
   */
  kInkTextDrawIgnorePressure    = 1,

  /*
   * Honor the CGContext settings for items such as line color and
   * width.
   */
  kInkTextDrawHonorContext      = 1 << 1
};



/*
 *  InkTerminationType
 *  
 *  Discussion:
 *    Though presented to applications as InkTextRefs (words in Roman
 *    languages), internally the Ink Manager uses the concept of an ink
 *    “phrase” to decide when to erase onscreen ink and initiate
 *    recognition. The following constants define the various means by
 *    which an ink phrase can be terminated. The Timeout,
 *    OutOfProximity, and RecognizerHardBreak constants may be used as
 *    arguments to InkSetPhraseTerminationMode() to control how the Ink
 *    Manager is allowed to terminate phrases. Automatic phrase
 *    termination can be inhibited entirely by calling
 *    InkSetPhraseTerminationMode(kInkTerminationNone). Normal
 *    automatic phrase termination may be restored by calling
 *    InkSetPhraseTerminationMode(kInkTerminationDefault). More precise
 *    control over the Ink Manager’s automatic phrase termination can
 *    be obtained by combining the following constants.
 */
typedef UInt32 InkTerminationType;
enum {

  /*
   * Can be used to inhibit all automatic phrase termination.
   */
  kInkTerminationNone           = 0,

  /*
   * Occurs when the user stops writing and lifts the pen, but keeps it
   * within the tablet’s “proximity” range, and does not resume writing
   * within a user-controllable period of time.
   */
  kInkTerminationTimeOut        = 1,

  /*
   * Occurs when the user stops writing and lifts the pen entirely out
   * of the tablet’s “proximity” (the range over which the tablet can
   * sense the pen).  Users can optionally disable out-of-proximity
   * phrase terminations, if they find it interferes with their writing
   * style, but it is on by default. 
   * 
   * NOTE: The user can turn off proximity termination in the Ink
   * preferences pane.  Doing so turns off all proximity termination,
   * regardless of the value passed to InkSetPhraseTerminationMode().
   */
  kInkTerminationOutOfProximity = 1 << 1,
  kInkTerminationRecognizerHorizontalBreak = 1 << 2,
  kInkTerminationRecognizerVerticalBreak = 1 << 3,

  /*
   * Causes phrases to be terminated at the end of every stroke
   * (whenever the pen is lifted from the tablet while writing). Only
   * useful for single-stroke gesture input, not for text.
   */
  kInkTerminationStroke         = 1 << 4,

  /*
   * Restores default phrase termination matching the current user
   * settings. See above note for kInkTerminationOutOfProximity.
   */
  kInkTerminationDefault        = 0x0F, /* TimeOut | OutOfProximity | RecognizerHorizontalBreak | RecognizerVerticalBreak*/

  /*
   * Deprecated.  Use kInkTerminationDefault instead.  As of Mac OS X
   * 10.4 this value will be overriden to behave like
   * kInkTerminationDefault. Restores automatic phrase termination
   * matching the current user settings. See above note for
   * kInkTerminationOutOfProximity.
   */
  kInkTerminationAll            = (unsigned long)0xFFFFFFFF /* Deprecated*/
};



/*
 *  InkSourceType
 *  
 *  Discussion:
 *    It is possible for applications to control phrase termination for
 *    both the user-input data stream (kInkSourceUser) and an
 *    application-input data stream (kInkSourceApplication),
 *    independently.  These two constants allow the app to specify
 *    which data stream is currently being controlled by calls to
 *    InkTerminateCurrentPhrase() and InkSetPhraseTerminationMode().
 */
typedef UInt32 InkSourceType;
enum {

  /*
   * Addresses the user-input data stream.
   */
  kInkSourceUser                = 1,

  /*
   * Addresses the application-input data stream.
   */
  kInkSourceApplication         = 2
};



/*
 *  InkRecognitionType
 *  
 *  Discussion:
 *    The following recognition type constants are used as arguments
 *    for InkSetApplicationRecognitionMode().  They may be combined to
 *    produce both text and gesture recognition (the norm), or either
 *    type individually. They only affect recognition when the app is
 *    providing stroke points via InkAddStrokeToCurrentPhrase(), *not*
 *    when the user is writing.
 */
typedef UInt32 InkRecognitionType;
enum {
  kInkRecognitionNone           = 0,
  kInkRecognitionText           = 1,
  kInkRecognitionGesture        = 1 << 1,
  kInkRecognitionDefault        = 3
};



/*
 *  InkGestureKind
 *  
 *  Discussion:
 *    The following constants are the values returned for the
 *    kEventParameterInkGestureKind parameter of
 *    kEventApplicationInkGesture events, and define the complete set
 *    of system gestures which a user may invoke by drawing them.  In
 *    general, when an InkGesture event is received by an application,
 *    the app will determine the gesture kind and then take appropriate
 *    action.  The meanings and implied actions of most of these
 *    gestures are obvious (undo, cut, copy, paste, etc.), though a few
 *    clarifications follow that may be useful. 
 *    
 *    See the Ink prefPane, Gestures tab, for pictures of these
 *    gestures, and animations that show how they are drawn. 
 *    
 *    Some gestures have a defined “hotspot” that can be used to
 *    determine what the gesture should be applied to.  Used in this
 *    fashion, the gesture is called a “targeted” gesture. Because the
 *    “target” is only knowable by the application, all gestures used
 *    in non-ink-aware apps are treated as “untargeted”.  Untargeted
 *    gestures apply to the current selection or insertion point. 
 *    Targeted gestures can apply to the item under the hotspot or even
 *    the entire gesture bounds. 
 *    
 *    For example, consider the paste gesture.  If being treated as an
 *    untargeted gesture, any pasted data would flow to the current
 *    insertion point.  If, however, it was being treated as a targeted
 *    gesture, any pasted data would be inserted at the location of the
 *    gesture’s hotspot. 
 *    
 *    If the gesture doesn’t have a hotspot or that hotspot lies
 *    outside the application’s windows, the gesture should usually be
 *    treated as an untargeted gesture.  An exception is the Clear
 *    gesture, which doesn’t have a hotspot, but might be targeted to
 *    all of the text it overlaps (to a sufficient degree--say, more
 *    than 50% of each word’s onscreen area, on a word by word basis).
 *    
 *    
 *    The InkPad demonstrates the use of targeted gestures, while any
 *    non-ink-aware app demonstrates the use of untargeted gestures.
 *    
 *    
 *    If a gesture does not have a hotspot, the
 *    kEventApplicationInkGesture event will not have a
 *    kEventParamInkGestureHotspot parameter. 
 *    
 *    There are also two classes of ink gesture, identified solely by
 *    the gesture type, that require and produce different handling. 
 *    The two classes are: 
 *    
 *    Non-tentative -- Non-tentative gestures are always and only
 *    treated as gestures, regardless of where they are drawn.  They
 *    are non-tentative because they may be applied anywhere and
 *    because they have been designed to not conflict with normal
 *    alphanumeric characters. If an application fails to handle them
 *    (has no handler installed or returns eventNotHandledErr), the Ink
 *    Manager will convert them to keyDowns (typically as command-key
 *    shortcuts).  No attempt will be made to recognize and post them
 *    as text. 
 *    
 *    Tentative -- Tentative gestures should only be interpreted as
 *    gestures if it makes sense, given the context (knowable only by
 *    your application).  If an application fails to handle a tentative
 *    gesture (has no handler installed or returns eventNotHandledErr),
 *    the Ink Manager will recognize and post the corresponding ink as
 *    text. 
 *    
 *    For example, if the join gesture is received, but the top-left
 *    and top-right points of the bounding box are not near the end and
 *    beginning of two words, respectively, with a space between them,
 *    then nothing should be done, and the event containing the gesture
 *    should not be handled (return eventNotHandledErr). The event will
 *    then be recognized and posted as text, probably as an uppercase
 *    or lowercase ‘v’. (On the other hand, if the gesture is in a
 *    reasonable location relative to appropriate text, then the two
 *    affected words would be joined, and the event handler would
 *    return noErr.)  By contrast, if the undo gesture went unhandled
 *    by an application, the Ink Manager would cause a sequence of key
 *    events to be posted that simulated the user typing a command-u.
 */
typedef FourCharCode InkGestureKind;
enum {

  /*
   * Non-tentative gestures…  (All except kInkGestureJoin.)
   */
  kInkGestureUndo               = 'undo',
  kInkGestureCut                = 'cut ',
  kInkGestureCopy               = 'copy',
  kInkGesturePaste              = 'past',
  kInkGestureClear              = 'clea',
  kInkGestureSelectAll          = 'sall',

  /*
   * kInkGestureEscape corresponds to a single press of the “escape”
   * key.  If this gesture goes unhandled, an escape keypress will be
   * generated.
   */
  kInkGestureEscape             = 'not!',
  kInkGestureTab                = 'tab ',

  /*
   * kInkGestureLeftSpace and kInkGestureRightSpace both correspond to
   * a single “space” character.  The “Left” and “Right” distinction
   * has only to do with how the gesture was drawn, specifically which
   * side the long, horizontal tail is on.
   */
  kInkGestureLeftSpace          = 'lspc',
  kInkGestureRightSpace         = 'rspc',

  /*
   * kInkGestureLeftReturn and kInkGestureRightReturn both correspond
   * to a single “return” (newline) character.  The “Left” and “Right”
   * distinction has only to do with how the gesture was drawn,
   * specifically which way the small angle-bracket-like feature is
   * pointing. 
   * 
   * In general, these “Left” and “Right” variants should be treated
   * identically, though it is conceivable that some special purpose
   * application might be able to make use of the gesture orientation.
   */
  kInkGestureLeftReturn         = 'lrtn',
  kInkGestureRightReturn        = 'rrtn',

  /*
   * kInkGestureDelete corresponds to a single press of the “delete”
   * key.  If a user selection (of a range of text, say) exists, this
   * should delete the selection, just like kInkGestureClear.  However,
   * whereas kInkGestureClear should do nothing if there is no
   * selection, this gesture should result in the deletion of the item
   * immediately preceding the insertion point (unless the insertion
   * point is at the absolute head of the document).
   */
  kInkGestureDelete             = 'del ',

  /*
   * Tentative gestures…  (Just kInkGestureJoin.) 
   * 
   * kInkGestureJoin should join two words into a single word, eliding
   * the space between them.  It looks like the letter ‘v’.  The
   * affected words would be the ones closest to the top-most points at
   * the left and right tips. Note:  A “join” is the only
   * “context-dependent” (aka “tentative”) gesture currently defined by
   * Apple. 
   * 
   * When a tentative/context-dependent gesture is received and
   * handled, it should only be treated as a gesture if it makes sense,
   * given the context (knowable only by your application).  For
   * example, if the join gesture is received, but the top-left and
   * top-right points of the bounding box are not near the end and
   * beginning of two words, respectively, with a space between them,
   * then nothing should be done, and the event containing the gesture
   * should not be handled (return eventNotHandledErr). On the other
   * hand, if the gesture is in a reasonable location relative to
   * appropriate text, then the two affected words would be joined, and
   * the event handler would return noErr.
   */
  kInkGestureJoin               = 'join'
};



/*
 */
enum {

  /*
   * Menu command ID assigned to menu items inserted by
   * InkTextInsertAlternatesInMenu()…
   */
  kInkAlternateCommand          = 'inka',

  /*
   * Menu command ID assigned to the separator item between the
   * alternates and the ink drawing…
   */
  kInkSeparatorCommand          = 'inks',

  /*
   * Menu command ID assigned to the menu item containing the ink
   * drawing…
   */
  kInkDrawingCommand            = 'inkd'
};


/*
 *  Discussion:
 *    Pens used with modern graphics tablets often have both a writing
 *    tip and an eraser tip.  Some tablets also support pucks in
 *    addition to or instead of stylus-like devices.  The following
 *    constants may be used to determine what kind of pointer device
 *    and which tip of a stylus-like device is being used with a
 *    graphics tablet, by comparing them to the contents of the
 *    TabletProximityRec's pointerType element in Carbon or the value
 *    returned by the pointerType message to tablet events (or mouse
 *    events with tablet data in them) in Cocoa.  These pointerType
 *    data are only available in tablet-proximity events (not
 *    tablet-point events). 
 *    
 *    Note that these constants are defined in terms of NX_* constants
 *    from <IOKit/hidsystem/IOLLEvent.h> in order to ensure consistency
 *    between the values used by driver writers and those used by
 *    applications.
 */
enum {

  /*
   * Shouldn't happen (0)…
   */
  kInkTabletPointerUnknown      = NX_TABLET_POINTER_UNKNOWN + 0, /* shouldn't happen*/

  /*
   * Writing end of a stylus-like device (1)…
   */
  kInkTabletPointerPen          = NX_TABLET_POINTER_PEN + 0, /* writing end of a stylus-like device*/

  /*
   * Any puck-like device (2)…
   */
  kInkTabletPointerCursor       = NX_TABLET_POINTER_CURSOR + 0, /* any puck-like device*/

  /*
   * Eraser end of a stylus-like device (3)…
   */
  kInkTabletPointerEraser       = NX_TABLET_POINTER_ERASER + 0 /* eraser end of a stylus-like device*/
};


/*
 *  Discussion:
 *    Pens used with modern graphics tablets often have multiple barrel
 *    buttons that can be assigned special meaning by either the the
 *    tablet driver or by an application.  In addition, the writing or
 *    eraser tip may be engaged at any given moment.  The following
 *    constants may be used to determine which (if any) pen tip or
 *    barrel buttons are currently being held down by and-ing their
 *    contents with that of a TabletPointRec's buttons member in Carbon
 *    or the value returned by the buttonMask message sent to tablet
 *    events (or mouse events containing tablet data) in Cocoa.  These
 *    buttons and buttonMask data are only available for tablet-point
 *    events (not tablet-proximity events). 
 *    
 *    Note that these constants are defined in terms of NX_* constants
 *    from <IOKit/hidsystem/IOLLEvent.h> in order to ensure consistency
 *    between the values used by driver writers and those used by
 *    applications.
 */
enum {

  /*
   * Writing tip or eraser tip (bit 0, 0x0001)…
   */
  kInkPenTipButtonMask          = NX_TABLET_BUTTON_PENTIPMASK + 0, /* writing tip or eraser tip*/

  /*
   * Lower pen barrel button (bit 1, 0x0002)…
   */
  kInkPenLowerSideButtonMask    = NX_TABLET_BUTTON_PENLOWERSIDEMASK + 0, /* lower barrel button*/

  /*
   * Upper pen barrel button (bit 2, 0x0004)…
   */
  kInkPenUpperSideButtonMask    = NX_TABLET_BUTTON_PENUPPERSIDEMASK + 0 /* upper barrel button*/
};

/*——————————————————————————————————————————————————————————————————————————————————————*/
/*  • Ink state APIs                                                                    */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/* Read-only User Settings */
/*
   The application cannot set any of the user preferences,
   determined by the user in the Ink prefPane in System
   Preferences, since those should be changed only by the user. 
   However, two of these settings are made available (in one
   API) to the app, as they determine what the app is allowed
   to do with ink.
*/

/*
 *  InkUserWritingMode()
 *  
 *  Discussion:
 *    Returns the user’s system-wide setting for where inking and
 *    recognition are allowed: nowhere, anywhere, or only in ink-aware
 *    apps.  The “nowhere” setting corresponds to the situation in
 *    which the user has turned Ink off entirely; the Ink Manager’s
 *    services will not be available in this mode.  The “anywhere”
 *    setting corresponds to the default situation once the user has
 *    turned Ink on; in this mode the user may write anywhere on the
 *    screen and ink points and recognition results will flow to the
 *    frontmost app. The “ink-aware apps” setting requires Ink to be
 *    turned on and the user to have selected this mode from the “Allow
 *    me to write” pop-up menu; in this mode the user will only be able
 *    to write in your application if you declare yourself to be
 *    ink-aware, by calling InkSetApplicationWritingMode(). 
 *    
 *    Note that when this routine returns kInkWriteAnywhere, the
 *    application may receive pen and ink events whose screen locations
 *    lie outside the application’s windows.
 *  
 *  Result:
 *    The current system-wide writing setting.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern InkUserWritingModeType 
InkUserWritingMode(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* Read/Write Application Settings */
/*
 *  InkSetApplicationWritingMode()
 *  
 *  Discussion:
 *    Controls where inking (and recognition) are allowed in this
 *    application only.  It allows the app to turn system inking on and
 *    off when it is frontmost.  If an application wants to allow
 *    inking and recognition, and to receive ink events, even when
 *    “write anywhere” is turned off (when InkUserWritingMode() ==
 *    kInkWriteInInkAwareAppsOnly), it will need to call this with
 *    kInkWriteAnywhereInApp.  To temporarily disable inking (such as
 *    while using a paint tool), call this with kInkWriteNowhereInApp.
 *    
 *    
 *    Note that when this routine is called with
 *    kInkWriteAnywhereInApp, the application may receive pen and ink
 *    events whose screen locations lie outside the application’s
 *    windows.
 *  
 *  Parameters:
 *    
 *    iWriteWhere:
 *      Writing mode to be used for this application.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
InkSetApplicationWritingMode(InkApplicationWritingModeType iWriteWhere) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  InkSetApplicationRecognitionMode()
 *  
 *  Discussion:
 *    Controls the types of recognition that are allowed when the user
 *    is entering data on the screen.  Either gesture recognition or
 *    text recognition or both may be selected. 
 *    
 *    Note:  This API does not affect recognition of ink originating in
 *    the application, and recognized via
 *    InkAddStrokeToCurrentPhrase(). Text recognition only (no
 *    gestures) is performed on that data stream.
 *  
 *  Parameters:
 *    
 *    iRecognitionType:
 *      The recognition types to be used for this application.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
InkSetApplicationRecognitionMode(InkRecognitionType iRecognitionType) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
   Once an ink phrase has been started, it will normally
   continue until either the user removes the pen from the
   tablet’s proximity or waits a user settable period of time
   while not pressing the pen to the tablet.  Once one of these
   things happens the ink phrase will be terminated and the Ink
   Manager will erase all of the ink associated with the session
   (if any was drawn). Ink phrases may also be terminated by the
   recognizer, if the user writes sufficiently far away from the
   previous ink—either horizontally, or on a new line. If the
   client needs control over when ink phrases are terminated,
   the following API can be used to determine exactly which
   conditions are permitted to terminate phrases.
   If, for example, a client wants to force all ink drawn in a
   particular input window to be treated as a single phrase,
   until a special “Finished Writing” button is pressed,
   calling this API with an argument of zero will turn off all
   automatic phrase termination, and installing a handler for
   kEventWindowInkPoint will allow the application to see pen
   events before the Ink Manager consumes them, and thus handle
   the button tap and call InkTerminateCurrentPhrase() at the
   appropriate time.
   Clients should be sure to manage phrase termination
   reasonably themselves, if they use this API to disable
   automatic phrase termination.
*/

/*
 *  InkSetPhraseTerminationMode()
 *  
 *  Discussion:
 *    Sets the conditions under which the Ink Manager is allowed to
 *    terminate phrases.  Pass in the desired combination of
 *    InkTerminationTypes (kInkTermination* constants).  To inhibit all
 *    automatic phrase termination, pass in zero or
 *    kInkTerminationNone.  Default behavior is as if this API had been
 *    called with kInkTerminationDefault. 
 *    
 *    Using one of the InkSourceType constants (kInkSource*) allows
 *    independent control over termination of data originating with the
 *    user vs. data originating in the application.  To manage phrase
 *    termination for user input, use kInkSourceUser.  To manage phrase
 *    termination for application input (recognized via
 *    InkAddStrokeToCurrentPhrase()), use kInkSourceApplication.
 *  
 *  Parameters:
 *    
 *    iSource:
 *      The source of the data stream affected by this call.
 *    
 *    iAllowedTerminationTypes:
 *      The termination types to be used for this application.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
InkSetPhraseTerminationMode(
  InkSourceType        iSource,
  InkTerminationType   iAllowedTerminationTypes)              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  InkIsPhraseInProgress()
 *  
 *  Discussion:
 *    Returns whether the user is in the process of writing a phrase.
 *    
 *    
 *    More precisely, this API determines whether the Ink Manager has
 *    initiated and is currently maintaining an ink phrase.  Apps
 *    managing their own phrase termination in any way, will need to
 *    know this to determine when it is sensible to call
 *    InkTerminateCurrentPhrase(). 
 *    
 *    Note:  This API does not interact in any way with recognition of
 *    data originating with the application, and being recognized via
 *    InkAddStrokeToCurrentPhrase().  That application-originated data
 *    stream is completely independent of the user-originated data
 *    stream. Applications invoking recognition services directly on
 *    their own data stream should be able to tell whether such a
 *    phrase is in-progress or not.
 *  
 *  Result:
 *    Returns TRUE if an Ink phrase is in progress.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
InkIsPhraseInProgress(void)                                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* For backward compatibility only*/
#define InkIsInking InkIsPhraseInProgress
/*
   Normally, the Ink Manager automatically draws and erases the
   ink, over a standard ink background.  The client can request
   that the Ink Manager not draw the background or not draw
   either ink or background.  If ink drawing is disabled, it
   will be up to the client to receive the points (by installing
   a handler for kEventWindowInkPoint events) and draw the ink.
   This API need not be used to inhibit drawing if the client
   has called InkSetApplicationWritingMode(kInkWriteNowhereInApp),
   or, on a per-point basis, if a given point is previewed and
   handled by the application, using its kEventWindowInkPoint
   event handler.
*/
/*
 *  InkSetDrawingMode()
 *  
 *  Discussion:
 *    Enables and disables the drawing of ink and the ink background by
 *    the Ink Manager.
 *  
 *  Parameters:
 *    
 *    iDrawingMode:
 *      The drawing mode to be used for this application.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
InkSetDrawingMode(InkDrawingModeType iDrawingMode)            AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————*/
/*  • Ink phrase APIs                                                                   */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
   Applications that gather their own data, either by disabling
   the Ink Manager and handling pen events themselves, or by
   acquiring the data in some device-specific manner, may still
   take advantage of the Ink Manager’s recognition services.  To
   do so, an application should add one stroke (from pen down to
   pen up) at a time to the current phrase, and then terminate
   the phrase.  This will generate one or more InkText events,
   depending upon what was written.
*/

/*
 *  InkAddStrokeToCurrentPhrase()
 *  
 *  Discussion:
 *    Adds one stroke to the current phrase. 
 *    
 *    This application-originated data stream is independent of the
 *    user-originated data stream associated with what the user writes
 *    on-screen.  By definition, data is added to the
 *    kInkSourceApplication data stream, so the source of the data need
 *    not be specified. <BR><BR> The stroke will not be drawn.
 *  
 *  Parameters:
 *    
 *    iPointCount:
 *      The number of points in this array.
 *    
 *    iPointArray:
 *      An array of InkPoints.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
InkAddStrokeToCurrentPhrase(
  unsigned long   iPointCount,
  InkPoint *      iPointArray)                                AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  InkTerminateCurrentPhrase()
 *  
 *  Discussion:
 *    Terminates the current phrase, in either the user- or
 *    application-originated data stream. 
 *    
 *    Applications managing phrase termination of user input should
 *    call this with kInkSourceUser, to identify that data stream. In
 *    this case, any ink drawn by the Ink Manager will be erased.
 *    Normally not used in this fashion, this API should only be called
 *    if the client is managing phrase termination of user input
 *    itself. 
 *    
 *    Applications requesting recognition services on
 *    application-originated (non-user-input) data, via
 *    InkAddStrokeToCurrrentPhrase(), will need to call this API to
 *    terminate phrases, and should pass in kInkSourceApplication, to
 *    identify that data stream.
 *  
 *  Parameters:
 *    
 *    iSource:
 *      The source of the data stream affected by this call.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
InkTerminateCurrentPhrase(InkSourceType iSource)              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*——————————————————————————————————————————————————————————————————————————————————————*/
/*  • InkText APIs                                                                      */
/*——————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  InkTextAlternatesCount()
 *  
 *  Discussion:
 *    Returns the number of alternate recognition hypotheses available
 *    for the specified InkText.
 *  
 *  Parameters:
 *    
 *    iTextRef:
 *      The InkTextRef to get the alternate count from.
 *  
 *  Result:
 *    The number of alternates for this InkTextRef.  If NULL, the
 *    operation was unsuccessful, or there were no alternates (rare).
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern CFIndex 
InkTextAlternatesCount(InkTextRef iTextRef)                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  InkTextCreateCFString()
 *  
 *  Discussion:
 *    Creates and returns a CFString of the specified alternate in the
 *    specified InkText. 
 *    
 *    The top-choice result will be at index zero.  If the index is
 *    invalid, the return will be null.  Client is responsible for
 *    releasing the returned CFString.
 *  
 *  Parameters:
 *    
 *    iTextRef:
 *      The InkTextRef to get the string from.
 *    
 *    iAlternateIndex:
 *      The index of the alternate to retrieve.
 *  
 *  Result:
 *    A CFStringRef containing the alternate requested.  If NULL, the
 *    operation was unsuccessful.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
InkTextCreateCFString(
  InkTextRef   iTextRef,
  CFIndex      iAlternateIndex)                               AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
   Alternate text hypotheses lists (alternate word lists in
   Roman languages) should be invoked and handled as standard
   contextual menus, via ContextualMenuSelect().  The following
   API allows clients to insert the alternate hypotheses list
   for a given InkTextRef into an existing menu.  The Ink
   Manager will attach certain menu event handlers to this menu,
   so clients should use this MenuRef directly, rather than copy
   items out of it to another menu.
   The selection of a menu item in the alternates menu will
   result in a reordering of the InkTextRef’s alternates
   list, so that the selected item becomes the first item in the
   list. This makes the user’s choice persistent in internal
   system data structures without requiring the client to call
   any additional APIs.
   Upon return from ContextualMenuSelect(), the client can tell
   if the user has made a selection by checking the value of
   outUserSelectionType, as usual.  If a selection has been
   made, the client can examine the outMenuID and outMenuItem
   parameters of ContextualMenuSelect(), and use them to obtain
   the alternate text with CopyMenuItemTextAsCFString().
   Alternatively, the new selection will be the top-choice (at
   index zero) alternate, available using
   InkTextCreateCFString().  The app should replace the
   original text (corresponding to the original event location)
   with the alternate text obtained from either the menu or the
   reordered InkTextRef.
   Note:  After a user selection from this menu, and the
   resultant reordering of the InkTextRef’s alternates list, the
   original text will still be among the alternates.  However,
   it may be in either the second or the third alternate
   position, depending upon the particular text.  In Roman
   languages, if the first letter is alphabetic, an
   alternate-first-letter-case hypothesis will be in the second
   position and the original text will be in the third position.
   For a non-alphabetic first character, however, such as a
   number, the original will be in the second position.  (The
   client should know the identity of the original text from its
   own internal data structures and the location of the event
   that triggered the contextual/alternates menu.)
*/

/*
 *  InkTextInsertAlternatesInMenu()
 *  
 *  Discussion:
 *    Inserts an alternate hypothesis list into the specified MenuRef
 *    after the specified menu item. 
 *    
 *    Returns the number of menu items added.  If zero, the operation
 *    was unsuccessful. 
 *    
 *    The client should respond to user selections from this menu by
 *    updating its internal data structures, as described above, and
 *    displaying the new text.  If there are no text alternates, the
 *    menu will be untouched.  If the specified menu item is zero, the
 *    text alternates will be inserted at the head of the menu.  If the
 *    specified menu item is greater than or equal to the existing
 *    number of menu items, the text alternates will be appended to the
 *    end of the menu.  Remember that menu items are one-based, not
 *    zero-based.
 *  
 *  Parameters:
 *    
 *    iTextRef:
 *      The InkTextRef to get the modifier from.
 *    
 *    iMenuRef:
 *      The MenuRef of the menu you want the alternates added to.
 *    
 *    iAfterItem:
 *      The MenuItemIndex of the menu item after which you want the
 *      alternates inserted.
 *  
 *  Result:
 *    The number of items added to the menu.  If NULL, the operation
 *    was unsuccessful.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern ItemCount 
InkTextInsertAlternatesInMenu(
  InkTextRef      iTextRef,
  MenuRef         iMenuRef,
  MenuItemIndex   iAfterItem)                                 AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  InkTextKeyModifiers()
 *  
 *  Discussion:
 *    Returns which modifier keys were down when the InkTextRef (word)
 *    was being written. Uses same format as Carbon Event Manager.
 *    
 *    
 *    The Ink Manager assigns keyboard modifier keys to a stroke if
 *    those keys were held down for more than 50% of the stroke’s
 *    points.  The Ink Manager assigns the modifier keys associated
 *    with a phrase’s first stroke to the entire phrase.  The Ink
 *    Manager assigns the modifier keys associated with a phrase to all
 *    of the InkTextRefs (words) that are derived from it.
 *  
 *  Parameters:
 *    
 *    iTextRef:
 *      The InkTextRef to get the modifier from.
 *  
 *  Result:
 *    A UInt32 with the modifiers which were pressed at the time the
 *    original ink was drawn.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern UInt32 
InkTextKeyModifiers(InkTextRef iTextRef)                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  InkTextCopy()
 *  
 *  Discussion:
 *    Copies an existing InkTextRef. 
 *    
 *    Use this API to implement copy and paste functions in a
 *    deferred-recognition app, or in a text app to retain ink when
 *    text is copied and pasted. The retain count of the new InkTextRef
 *    will be one.
 *  
 *  Parameters:
 *    
 *    iTextRef:
 *      The InkTextRef to copy.
 *  
 *  Result:
 *    A new InkTextRef containing the same ink data as the original. 
 *    If NULL, the operation was unsuccessful.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern InkTextRef 
InkTextCopy(InkTextRef iTextRef)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  InkTextBounds()
 *  
 *  Discussion:
 *    Returns the bounds of the specified ink-text. 
 *    
 *    The bounds are initially in global coordinates, and may extend
 *    beyond the application’s windows.
 *  
 *  Parameters:
 *    
 *    iTextRef:
 *      The InkTextRef to get the bounds from.
 *  
 *  Result:
 *    An HIRect containing the bounds of the original ink.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern HIRect 
InkTextBounds(InkTextRef iTextRef)                            AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  InkTextDraw()
 *  
 *  Discussion:
 *    Rescales and draws the specified ink-text into the specified
 *    bounds. 
 *    
 *    The ink’s original points and bounds will be scaled and offset to
 *    fit the specified bounds, so subsequent calls to InkTextBounds
 *    will return the rescaled/destination bounds. Drawing is relative
 *    to the specified CGContextRef, and subject to the usual window
 *    and clipping constraints. Pass in NULL for iContext if you want
 *    to draw to the canonical context of the current port.
 *  
 *  Parameters:
 *    
 *    iTextRef:
 *      The InkTextRef you wish to draw.
 *    
 *    iContext:
 *      The CGContext to draw into, or NULL if you want to use the
 *      CGContext of the current port.
 *    
 *    iBounds:
 *      A pointer to a CGRect in which to draw.
 *    
 *    iFlags:
 *      Drawing settings.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
InkTextDraw(
  InkTextRef             iTextRef,
  CGContextRef           iContext,       /* can be NULL */
  const CGRect *         iBounds,
  InkTextDrawFlagsType   iFlags)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  InkTextFlatten()
 *  
 *  Discussion:
 *    Flattens the InkTextRef into a CFMutableDataRef, starting at a
 *    specifiable index in the CFMutableDataRef. 
 *    
 *    Returns the number of bytes added to the ioDataRef.  If zero, the
 *    operation was unsuccessful or iTextRef was NULL or empty.
 *    
 *    
 *    If you want to archive the InkText data for later use (e.g. in a
 *    file), it can be flattened into a CFMutableDataRef with this API.
 *    Client is responsible for creating (and releasing) the
 *    CFMutableDataRef.
 *  
 *  Parameters:
 *    
 *    iTextRef:
 *      The InkTextRef you wish to flatten.
 *    
 *    ioDataRef:
 *      A CFDataRef to flatten the data into.
 *    
 *    iIndex:
 *      A CFIndex into the CFDataRef, pointing at the location you want
 *      the data to be inserted at.
 *  
 *  Result:
 *    The number of bytes added to the CFDataRef.  If NULL, the
 *    operation was unsuccessful.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern CFIndex 
InkTextFlatten(
  InkTextRef         iTextRef,
  CFMutableDataRef   ioDataRef,
  CFIndex            iIndex)                                  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  InkTextCreateFromCFData()
 *  
 *  Discussion:
 *    Returns an InkTextRef created from data starting at a specifiable
 *    index in a CFDataRef. 
 *    
 *    If an InkTextRef was previously flattened by InkTextFlatten, it
 *    can be reconstituted with this API.  The retain count of the new
 *    InkTextRef will be one.
 *  
 *  Parameters:
 *    
 *    iFlattenedInkText:
 *      The CFDataRef containing the flattened InkTextRef you wish to
 *      extract.
 *    
 *    iIndex:
 *      A CFIndex into the CFDataRef, pointing at the start of the
 *      flattened InkTextRef.
 *  
 *  Result:
 *    A new InkTextRef containing the data, which you now own.  Call
 *    CFRelease() on it when you wish to dispose of it.  If NULL, the
 *    operation was unsuccessful.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern InkTextRef 
InkTextCreateFromCFData(
  CFDataRef   iFlattenedInkText,
  CFIndex     iIndex)                                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  InkTextGetTypeID()
 *  
 *  Discussion:
 *    Returns the CFTypeID of an InkTextRef object. 
 *    <BR> Given an InkTextRef, this routine will return its CFTypeID.
 *  
 *  Parameters:
 *    
 *    iTextRef:
 *      The InkTextRef to get the CFTypeID of.
 *  
 *  Result:
 *    The CFTypeID of an InkTextRef object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
InkTextGetTypeID(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  InkTextGetStrokeCount()
 *  
 *  Discussion:
 *    Returns the number of strokes in the specified InkTextRef.
 *    
 *    
 *    Given an InkTextRef, this routine will return the number of
 *    strokes it contains.
 *  
 *  Parameters:
 *    
 *    iTextRef:
 *      The InkTextRef to get the stroke count from.
 *  
 *  Result:
 *    A CFIndex indicating the number of strokes contained in the
 *    specified InkTextRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern CFIndex 
InkTextGetStrokeCount(InkTextRef iTextRef)                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  InkTextGetStroke()
 *  
 *  Discussion:
 *    Returns a reference to the specified stroke in an InkTextRef.
 *    
 *    
 *    Given an InkTextRef and a stroke index (between 0 and
 *    InkTextGetStrokeCount( iTextRef ) - 1), this routine will return
 *    the InkStrokeRef corresponding to the specified stroke index.
 *    
 *    
 *    The returned InkStrokeRef is only guaranteed to persist for the
 *    life of the InkTextRef from which it was obtained. If the client
 *    wishes to use the InkStrokeRef after the InkTextRef has been
 *    released, it must perform a CFRetain on the InkStrokeRef.
 *    
 *    
 *    When any Ink object reference is obtained from a Carbon event, it
 *    is only guaranteed to persist for the life of the event handler. 
 *    If the client wishes to use the object at some later time, it
 *    must perform a CFRetain on the object.
 *  
 *  Parameters:
 *    
 *    iTextRef:
 *      The InkTextRef to get the stroke from.
 *    
 *    iStrokeIndex:
 *      The index of the stroke for which an InkStrokeRef is desired.
 *  
 *  Result:
 *    An InkStrokeRef for the specified stroke of the specified
 *    InkTextRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern InkStrokeRef 
InkTextGetStroke(
  InkTextRef   iTextRef,
  CFIndex      iStrokeIndex)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*——————————————————————————————————————————————————————————————————————————————————————*/
/*  • InkStroke APIs                                                                    */
/*——————————————————————————————————————————————————————————————————————————————————————*/

/*
 *  InkStrokeGetPointCount()
 *  
 *  Discussion:
 *    Returns the number of points in the specified InkStrokeRef.
 *    
 *    
 *    Given an InkStrokeRef, this routine will return the number of
 *    points that stroke contains.
 *  
 *  Parameters:
 *    
 *    iStrokeRef:
 *      The InkStrokeRef to get the point count from.
 *  
 *  Result:
 *    A CFIndex indicating the number of points contained in the
 *    specified InkStrokeRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern CFIndex 
InkStrokeGetPointCount(InkStrokeRef iStrokeRef)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  InkStrokeGetPoints()
 *  
 *  Discussion:
 *    Fills an array with the points belonging to the specified
 *    InkStrokeRef. 
 *    
 *    Given an InkStrokeRef and a point buffer, this routine will fill
 *    that buffer with the points belonging to that stroke. 
 *    
 *    The size of the point buffer must be at least:
 *     InkStrokeGetPointCount( iStrokeRef ) * sizeof( InkPoint ).
 *     The pointer to the block of memory containing the InkPoints will
 *    be returned as the result.
 *  
 *  Parameters:
 *    
 *    iStrokeRef:
 *      The InkStrokeRef to get the points from.
 *    
 *    oPointBuffer:
 *      The point buffer into which the point data will be copied.
 *  
 *  Result:
 *    A pointer to the copied array of InkPoints from the specified
 *    InkStrokeRef (same as the oPointBuffer address provided by the
 *    app).
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern InkPoint * 
InkStrokeGetPoints(
  InkStrokeRef   iStrokeRef,
  InkPoint *     oPointBuffer)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  InkStrokeGetTypeID()
 *  
 *  Discussion:
 *    Returns the CFTypeID of an InkStrokeRef object. 
 *    <BR> Given an InkStrokeRef, this routine will return its CFTypeID.
 *  
 *  Parameters:
 *    
 *    iStrokeRef:
 *      The InkStrokeRef to get the CFTypeID of.
 *  
 *  Result:
 *    The CFTypeID of an InkStrokeRef object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
InkStrokeGetTypeID(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;




#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __INK__ */


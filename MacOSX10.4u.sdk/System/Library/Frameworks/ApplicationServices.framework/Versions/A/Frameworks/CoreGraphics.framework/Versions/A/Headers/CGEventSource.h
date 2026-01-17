/*
*  CGEventSource.h
*  CoreGraphics
*
*  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
*
*/
#ifndef __CGEVENTSOURCE_H__
#define __CGEVENTSOURCE_H__ 1

#include <CoreGraphics/CGRemoteOperation.h>
#include <CoreGraphics/CGEventTypes.h>


CG_EXTERN_C_BEGIN

/* Return the CFTypeID for CGEventSourceRefs. */
CG_EXTERN CFTypeID CGEventSourceGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Create a new CGEventSource
 *
 * The event source contains accumulated state related to event
 * generation and event posting, allowing for customized event
 * generation and processing.
 *
 * The CGEventSourceStateID refers to a global event state table.
 * These tables contain accumulated information on modifier flag state,
 * keyboard key state, mouse button state, and related internal parameters
 * placed in effect by posting events with associated sources.
 *
 * Two pre-existing tables are defined.
 *
 * The kCGEventSourceStateCombinedSessionState table reflects the combined state
 * of all event sources posting to this user login session. Mouse button,
 * keyboard state, and modifier flag state (derived from keyboard state)
 * are logically ORed together in this state table.
 *
 * The kCGEventSourceStateHIDSystemState table reflects the combined state
 * of all hardware event sources posting from the HID system. Mouse button,
 * keyboard state, and modifier flag state (derived from keyboard state)
 * for the hardware devices are logically ORed together in this state table.
 *
 * A program, or application posting from within a login session should use
 * the kCGEventSourceStateCombinedSessionState.
 *
 * A user space device driver interpreting hardware state and generating events
 * should use the kCGEventSourceStateHIDSystemState.
 *
 * Very specialized applications such as remote control programs may want to
 * generate and track event source state independent of other processes.
 * These programs should use the kCGEventSourceStatePrivate value in creating
 * their event source. An independent state table and unique CGEventSourceStateID
 * are created to track the event source's state.  The independent sate table is owned
 * by the creating event source and released with it.
 *
 * If the CGEventSourceStateID from another CGEventSourceRef
 * is released while being used in a second CGEventSourceRef, the second source
 * will behave as if all keys and buttons on input devices are up in generating
 * new events from this source.
 *
 * Default behavior without an event source, that is, passing NULL to
 * CGEvent creation functions, is identical to using an unmodified
 * CGEventSource created with the kCGEventSourceStateCombinedSystemState
 * source state ID, if running within a login session, or using
 * kCGEventSourceStateHIDSystemState if running outside of a login session,
 * as in a daemon or user space device driver.
 *
 * Returns NULL if the specified event source is not a valid CGEventSourceStateID,
 * or is a private event source owned by another process,
 * or is not a member of the following enumeration.
 *
 * The returned object should be released with CFRelease when no longer needed.
 */
CG_EXTERN CGEventSourceRef CGEventSourceCreate(CGEventSourceStateID sourceState) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Set and get the keyboard type to be used with this source
 * The value will be used with UCKeyTranslate() to drive keyboard translation
 */
CG_EXTERN CGEventSourceKeyboardType CGEventSourceGetKeyboardType(CGEventSourceRef source) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN void CGEventSourceSetKeyboardType(CGEventSourceRef source, CGEventSourceKeyboardType keyboardType) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 * Return the event source state ID associated with the event source.
 * For event sources created with the kCGEventSourceStatePrivate
 * CGEventSourceStateID, this returns the actual CGEventSourceStateID
 * created for the CGEventSourceRef.
 *
 * The value returned may be passed to CGEventSourceCreate() to create a
 * second event source sharing the same state table.  This may be useful,
 * for example, in creating seperate mouse and keyboard sources which share
 * a common private state.
 *
 * If the CGEventSourceStateID from another CGEventSourceRef
 * is released while being used in a second CGEventSourceRef, the second source
 * will behave as if all keys and buttons on input devices are up in generating
 * new events from this source.
 */
CG_EXTERN CGEventSourceStateID CGEventSourceGetSourceStateID(CGEventSourceRef source) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * The state of an event source may be queried for specialized event processing
 * purposes.
 */
CG_EXTERN bool CGEventSourceButtonState( CGEventSourceStateID sourceState, CGMouseButton button )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN bool CGEventSourceKeyState( CGEventSourceStateID sourceState, CGKeyCode key )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN CGEventFlags CGEventSourceFlagsState( CGEventSourceStateID sourceState )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Time since last event for an event source.
 *
 * The kCGAnyInputEventType eventType will report the last timestamp for any
 * input event, keyboard, mouse, or tablet.  The various system and app
 * defined events do not contribute to this event type's time.
 *
 * Again, a program or application posting from within a login session should use
 * the kCGEventSourceStateCombinedSessionState.
 *
 * A user space device driver interpreting hardware state and generating events
 * should use the kCGEventSourceStateHIDSystemState.
 */

CG_EXTERN CFTimeInterval CGEventSourceSecondsSinceLastEventType( CGEventSourceStateID source, CGEventType eventType )  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Returns a count of events of different types seen since the window server started.
 *
 * Note that modifier keys produce kCGEventFlagsChanged events, not kCGEventKeyDown
 * events, and do so both on press and release.
 *
 * Please note that some keys on the keyboard are not implemented as keys,
 * but instead are USB button devices.  We account for the ones we can see as
 * kCGEventKeyDown events. Where we don't get a different event for key-up, we
 * record both a key down and a key up.
 *
 * There is no guarantee that the number of key down and key up events will match
 * when all keyboard keys are up, due to the inconsistent nature of the USB button device keys.
 *
 * Key autorepeat events are not counted.
 *
 * Synthetic events posted into the system may also produce assymetric 'down' and 'up' event counts.
 *
 * Again, a program or application posting from within a login session should use
 * the kCGEventSourceStateCombinedSessionState.
 *
 * A user space device driver interpreting hardware state and generating events
 * should use the kCGEventSourceStateHIDSystemState.
 *
 */
CG_EXTERN uint32_t CGEventSourceCounterForEventType(CGEventSourceStateID source, CGEventType evType) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Each event carries a payload of 64 bits of user specified data.
 * The values may be individually set per event using the
 * CGEventSetIntegerValueField() API, or may be set for all events
 * created by this event source using this API.
 * This mechanism is more convenient for uses such as vendor hardware IDs.
 */
CG_EXTERN void CGEventSourceSetUserData(CGEventSourceRef source, int64_t userData) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN int64_t CGEventSourceGetUserData(CGEventSourceRef source) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * The CGRemoteOperation APIs (CoreGraphics/CGRemoteOperation.h) use an implicit event
 * source to affect system behavior on event posting.  Here we expose the same mechanism
 * on a per event source basis.  Default values are different than the remote operation API
 * exposes, based on developer feedback.
 */

/*
 * The system may optionally suppress local hardware events
 * from the keyboard and mouse during a short interval after
 * a program posts an event (see CGSetLocalEventsSuppressionInterval())
 * or while your program has a left mouse button down (mouse drag) in effect.
 *
 * Some classes of applications may want to disable events from some of the local hardware.
 * For example, an app may want to post only mouse events, and so may wish to permit local
 * keyboard hardware events to pass through while blocking local mouse events.
 * Set the event source to permit keyboard events
 * prior to creating the mouse event after which you want to get keyboard events.
 *
 * This interface lets an app specify a state (event suppression interval, or mouse drag), and
 * a mask of event categories to be passed through. The new filter state takes effect
 * with the next event your app posts that is created with this event source.
 *
 * The kCGEventSuppressionStateSuppressionInterval state allows one to set a filter that
 * permits local hardware mouse events, local keyboard events, both, or neither during the
 * specified short interval of time after your process posts an event created with this source.
 *
 * The kCGEventSuppressionStateRemoteMouseDrag state allows one to set a filter that
 * permits local hardware mouse events, local keyboard events, both, or neither during
 * the time that your event source has a left mouse button down (mouse drag) in effect.
 *
 * The default state for a CGEventSourceRef is to have all filtering off, so that local
 * hardware events are unaffected.
 *
 * When a user enters the 'Force Quit' keyboard attention sequence, Command-Option-Escape,
 * all local event supression filters in effect are disabled, and all local hardware
 * events are delivered as normal.  This allows for recovery from unfortunate programming
 * errors.
 */

CG_EXTERN void CGEventSourceSetLocalEventsFilterDuringSuppressionState(CGEventSourceRef source,
                                                                       CGEventFilterMask filter,
                                                                       CGEventSuppressionState state)AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN CGEventFilterMask CGEventSourceGetLocalEventsFilterDuringSuppressionState(CGEventSourceRef source,
                                                                                    CGEventSuppressionState state)AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Set the period of time in seconds that specified local hardware events (keyboard or mouse)
 * may suppressed after posting a CGEventRef created with this source, if the event
 * source is set to apply the kCGEventSuppressionStateSuppressionInterval.
 *
 * Defaults to 0.25 second.
 */
CG_EXTERN void CGEventSourceSetLocalEventsSuppressionInterval(CGEventSourceRef source, CFTimeInterval seconds)AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN CFTimeInterval CGEventSourceGetLocalEventsSuppressionInterval(CGEventSourceRef source)AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


CG_EXTERN_C_END

#endif /* __CGEVENTSOURCE_H__ */


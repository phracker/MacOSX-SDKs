/*
 *  CGEvent.h
 *  CoreGraphics
 *
 *  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 */
#ifndef __CGEVENT_H__
#define __CGEVENT_H__ 1

#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGGeometry.h>
#include <CoreGraphics/CGError.h>
#include <CoreGraphics/CGRemoteOperation.h>
#include <CoreGraphics/CGEventSource.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <CoreGraphics/CGEventTypes.h>


CG_EXTERN_C_BEGIN


/* Return the CFTypeID for CGEventRefs. */
CG_EXTERN CFTypeID CGEventGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* 
 * APIs provide the ability to create a NULL event, or to create specialized
 * events reflecting a state specified as parameters to the creation functions.
 */

/* Create a NULL event to be filled in.  'source' may be NULL. */
CG_EXTERN CGEventRef CGEventCreate(CGEventSourceRef source) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Functions to flatten and reconstruct a CGEventRef for network transport.
 * These may be useful in remote control and helpdesk applications.
 *
 * Returns a CGEventRef built from the flattened data representation, or NULL
 * if the eventData is invalid.
 */
CGEventRef CGEventCreateFromData(CFAllocatorRef allocator, CFDataRef eventData);

/*
 * Returns a CFDataRef containing  the flattened data representation of the event,
 * or NULL if the eventData is invalid.
 */
CFDataRef CGEventCreateData(CFAllocatorRef allocator, CGEventRef event);

/*
 * Create mouse events.
 *
 * The event source may be taken from another event, or may be NULL.
 * mouseType should be one of the mouse event types.
 * mouseCursorPosition should be the global coordinates the mouse is at for the event.
 * For kCGEventOtherMouseDown, kCGEventOtherMouseDragged, and
 * kCGEventOtherMouseUp  events, the mouseButton parameter should
 * indicate which button is changing state.
 * 
 * The current implemementation of the event system supports a maximum of thirty-two buttons.
 * Mouse button 0 is the primary button on the mouse. Mouse button 1 is the secondary
 * mouse button (right). Mouse button 2 is the center button, and the remaining
 * buttons would be in USB device order.
 */
CG_EXTERN CGEventRef CGEventCreateMouseEvent( CGEventSourceRef source,
                                              CGEventType mouseType,
                                              CGPoint mouseCursorPosition,
                                              CGMouseButton mouseButton) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 * Create keyboard events.
 *
 * The event source may be taken from another event, or may be NULL.
 * Based on the virtual key code values entered,
 * the appropriate key down, key up, or flags changed events are generated.
 *
 * All keystrokes needed to generate a character must be entered, including
 * SHIFT, CONTROL, OPTION, and COMMAND keys.  For example, to produce a 'Z',
 * the SHIFT key must be down, the 'z' key must go down, and then the SHIFT
 * and 'z' key must be released:
 *	CGEventCreateKeyboardEvent((CGKeyCode)56, true ); // shift down
 *	CGEventCreateKeyboardEvent( (CGKeyCode)6, true ); // 'z' down
 *	CGEventCreateKeyboardEvent( (CGKeyCode)6, false ); // 'z' up
 *	CGEventCreateKeyboardEvent( (CGKeyCode)56, false ); // 'shift up
 */
CG_EXTERN CGEventRef CGEventCreateKeyboardEvent( CGEventSourceRef source,
                                                 CGKeyCode virtualKey,
                                                 bool keyDown ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN CGEventRef CGEventCreateCopy(CGEventRef event) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/* 
 * CFRetain() and CFRelease() may be used to retain and release CGEventRefs.
 */

CG_EXTERN CGEventSourceRef CGEventGetSource(CGEventRef event) DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 * These functions provide access to the event source for an event.
 * Event filters may use these to generate events that are compatible
 * with an event being filtered.
 *
 * Note that CGEventCreateSourceFromEvent may return NULL if the event
 * was generated with a private CGEventSourceStateID owned by another
 * process.  Such events should be filtered based on the public state.
 */
CG_EXTERN CGEventSourceRef CGEventCreateSourceFromEvent(CGEventRef event) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN void CGEventSetSource(CGEventRef event, CGEventSourceRef source) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * The following functions will provide high level access to selected event data.
 */
CG_EXTERN CGEventType CGEventGetType(CGEventRef event) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN void CGEventSetType(CGEventRef event, CGEventType type) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN CGEventTimestamp CGEventGetTimestamp(CGEventRef event) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN void CGEventSetTimestamp(CGEventRef event, CGEventTimestamp timestamp) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN CGPoint CGEventGetLocation(CGEventRef event) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN void CGEventSetLocation(CGEventRef event, CGPoint location) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN CGEventFlags CGEventGetFlags(CGEventRef event) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN void CGEventSetFlags(CGEventRef event, CGEventFlags flags) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Access to UniChar data in keyboard events.
 *
 * There are no runtime errors associated with these functions.
 * Use on non-keyboard events leaves the event unchanged.
 * Note that many frameworks use a fixed length representation
 * of a CGEvent, and so are limited to a maximum string length
 * of 20 Unicode characters.  The CGEventRef itself is limited to 65535
 * characters.
 *
 * Calling CGEventKeyboardGetUnicodeString() with a NULL unicodeString
 * or zero maxStringLength will still return the actual count of
 * UniCode characters in the event data.
 */
CG_EXTERN void CGEventKeyboardGetUnicodeString(CGEventRef event,
                                               UniCharCount maxStringLength,
                                               UniCharCount * actualStringLength,
                                               UniChar unicodeString[]) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

CG_EXTERN void CGEventKeyboardSetUnicodeString(CGEventRef event,
                                               UniCharCount stringLength,
                                               const UniChar unicodeString[]) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 * Additional low level functions provide access to specialized fields of the events
 */

/*
 * The CGEventGetDoubleValueField and CGEventSetDoubleValueField
 * Functions renormalize certain fixed point and integer values
 * to an appropriate floating point range.  Keys this is done for
 * are:
 *
 * kCGMouseEventPressure	pressure value in the range 0-255
 * 				scaled to [0.0-1.0]
 * kCGTabletEventPointPressure	scaled pressure value; MAX=(2^16)-1, MIN=0
 * kCGTabletEventTiltX	tilt range is -((2^15)-1) to (2^15)-1 (-32767 to 32767)
 * kCGTabletEventTiltY	scaled to [0.0-1.0]
 * kCGTabletEventTangentialPressure	Same range as tilt
 * kCGTabletEventRotation	Fixed-point representation of device
 *				rotation in a 10.6 format
 */

CG_EXTERN int64_t  CGEventGetIntegerValueField(CGEventRef event, CGEventField field) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN double CGEventGetDoubleValueField(CGEventRef event, CGEventField field) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Before using the Set functions, the event type must be set
 * properly by using the appropriate type creation function or by calling
 * CGEventSetType().
 *
 * If this is to be a mouse event generated by a tablet, call
 * CGEventSetIntegerValueField(event, kCGMouseEventSubtype) with a value of
 * kCGEventMouseSubtypeTabletPoint or kCGEventMouseSubtypeTabletProximity
 * before setting other parameters.
 *
 * The correct type and subtype must be set so that the internal
 * event-specific data structures may be properly filled in.
 */
CG_EXTERN void CGEventSetIntegerValueField(CGEventRef event, CGEventField field, int64_t value) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN void CGEventSetDoubleValueField(CGEventRef event, CGEventField field, double  value) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* 
 * Registering an Event Tap
 * 
 * A function registers an event tap, taking a pointer to the
 * program's tap function and an arbitrary reference to be passed
 * to the tap function, and returning a CFMachPortRef the program
 * can add to the appropriate run loop by creating a surce and
 * using  CFRunLoopAddSource().
 * 
 * Taps may be placed at the point where HIDSystem events enter
 * the server, at the point where HIDSystem and remote control
 * events enter a session, at the point where events have been
 * annotated to flow to a specific application, or at the point
 * where events are delivered to the application.  Taps may be
 * inserted at a specified point at the head of pre-existing filters,
 * or appended after any pre-existing filters.
 * 
 * Taps may be passive event listeners, or active filters.
 * An active filter may pass an event through unmodified, modify
 * an event, or discard an event.  When a tap is registered, it
 * identifies the set of events to be observed with a mask, and
 * indicates if it is a passive or active event filter.  Multiple
 * event type bitmasks may be ORed together.
 *
 * Taps may only be placed at kCGHIDEventTap by a process running
 * as the root user.  NULL is returned for other users.
 *
 * Taps placed at kCGHIDEventTap, kCGSessionEventTap,
 * kCGAnnotatedSessionEventTap, or on a specific process may
 * only receive key up and down events if access for assistive
 * devices is enabled (Preferences Universal Access panel,
 * Keyboard view). If the tap is not permitted to monitor these
 * when the tap is being created, then the appropriate bits
 * in the mask are cleared.  If that results in an empty mask,
 * then NULL is returned.
 *
 * Releasing the CFMachPortRef will release the tap.
 * 
 * The CGEventTapProxy is an opaque reference to state within
 * the client application associated with the tap.  The tap
 * function may pass this reference to other functions, such as
 * the event-posting routines.
 *
 * The event tap callback runs from the CFRunLoop to which the
 * tap CFMachPort is added as a source. The thread safety is defined
 * by the CFRunLoop and it's environment.
 */

/* Return the a CFMachPortRef  for the event tap. */
CG_EXTERN CFMachPortRef CGEventTapCreate(CGEventTapLocation tap,
                                         CGEventTapPlacement place,
                                         CGEventTapOptions options,
                                         CGEventMask eventsOfInterest,
                                         CGEventTapCallBack callback,
                                         void * refcon ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* 
 * Events being routed to individual applications may be tapped
 * using another function.  CGEventTapCreateForPSN() will report
 * all events being routed to the specified application.
 */

/* Return the a CFMachPortRef  for an event tap for the specified process. */
CG_EXTERN CFMachPortRef CGEventTapCreateForPSN(void *processSerialNumber, /* Temp type, til def moves to CoreServices */
                                               CGEventTapPlacement place,
                                               CGEventTapOptions options,
                                               CGEventMask eventsOfInterest,
                                               CGEventTapCallBack callback,
                                               void * refcon ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Enable or disable an event tap.
 *
 * The taps are normally enabled when created.
 * If a tap becomes unresponsive, or a user requests taps be disabled,
 * then an appropriate kCGEventTapDisabled... event is passed to the
 * registered CGEventTapCallBack function.
 *
 * Event taps may be re-enabled by calling this function.
 */
CG_EXTERN void CGEventTapEnable(CFMachPortRef myTap, bool enable) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
CG_EXTERN bool CGEventTapIsEnabled(CFMachPortRef myTap) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * A function to post events from a tap is provided.  The events
 * are posted to the same points that an event returned from an
 * event tap would be posted to.  If an event tap posts new events,
 * the new events enter the system before the event returned by
 * the tap enters the system.  This order may be changed by
 * explicitly posting the filtered event along with new events
 * in the desired order, and then setting the returned event
 * *pEventOut to NULL.
 *
 * Events posted into the system will be seen by all taps placed
 * after the tap posting the event.
 */

/* Post an event from the event tap into the event stream. */
CG_EXTERN void CGEventTapPostEvent( CGEventTapProxy proxy,
                                    CGEventRef event ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* 
 * Functions to post events into the system at various points
 * are also provided.  Each event posted by these functions
 * enters the system at a point immediately before any taps
 * instantiated for that point, and will pass through any such taps.
 *
 * This mechanism permits an external process to establish an
 * event routing policy, for example, by tapping events at the
 * kCGAnnotatedSessionEventTap and then posting the events to
 * the desired PSN.
 */

/* Post an event from the event tap into the event stream. */
CG_EXTERN void CGEventPost( CGEventTapLocation tap,
                            CGEventRef event ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Post an event from the event tap into the event stream for a specific application. */
CG_EXTERN void CGEventPostToPSN( void *processSerialNumber, /* Temp type, til def moves to CoreServices */
                                 CGEventRef event ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 * Mechanism used to list event taps.
 * An array length (maxNumberOfTaps) and array of CGEventTapInformation structures
 * are passed in.
 * Up to maxNumberOfTaps elements of the array are filled in with event tap information.
 * The actual number of elements filled in is returned in eventTapCount.
 *
 * The call resets the accumulated minUsecLatency and maxUsecLatency fields.  Values
 * reported in these fields reflect the min and max values seen since the preceding call,
 * or the instantiation of the tap.
 *
 * If the CGEventTapInformation array is NULL, maxNumberOfTaps is ignored, and *eventTapCount
 * is filled in with the number of event taps that are currently installed.
 */
CG_EXTERN CGError CGGetEventTapList( CGTableCount maxNumberOfTaps,
                                     CGEventTapInformation tapList[],
                                     CGTableCount *eventTapCount ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


CG_EXTERN_C_END

#endif /* __CGEVENT_H__ */

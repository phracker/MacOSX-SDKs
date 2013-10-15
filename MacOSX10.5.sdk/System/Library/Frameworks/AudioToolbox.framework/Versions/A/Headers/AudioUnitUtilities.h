/*=============================================================================
	AudioUnitUtilities.h
		
	Copyright (c) 2002-2004 Apple Computer, Inc.  All Rights Reserved
=============================================================================*/

/*!
    @header 	AudioUnitUtilities.h
    @abstract   Contains higher-level utility functions for the use of AudioUnit clients.
    @discussion
The AU Parameter Listener is designed to provide notifications when an Audio Unit's parameters
or other state changes.  It makes it unnecessary for UI components to continually poll an Audio
Unit to determine if a parameter value has been changed. In order for this notification
mechanism to work properly, parameter values should be changed using the AUParameterSet call
(discussed below). This also makes it unnecessary for an Audio Unit to provide and support a
notification mechanism, particularly as AudioUnitSetParameter may be received by an Audio Unit
during the render process.

The AUEventListener API's extend the AUParameterListener API's by supporting event types
other than parameter changes. Events, including parameter changes are delivered serially to the 
listener, preserving the time order of the events and parameter changes.

There are also some utilities for converting between non-linear and linear value ranges. These
are useful for displaying a non-linear parameter (such as one whose units are in Hertz or
decibels) using a linear control mechanism, such as a slider, to ensure that the user has a
wider perceived range of control over the parameter value.
*/


#ifndef __AudioUnitUtilities_h__
#define __AudioUnitUtilities_h__

#include <AvailabilityMacros.h>
#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <AudioUnit/AudioUnit.h>
#else
	#include <AudioUnit.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================= */

/*!
	@enum		
	
	@abstract	
	
	@constant	kAUParameterListener_AnyParameter
					A wildcard value for an AudioUnitParameterID. Note that this is
					only valid when sending a notification (with AUParameterListenerNotify),
					not when registering to receive one.
*/
enum {
	kAUParameterListener_AnyParameter = 0xFFFFFFFF
};

/*!
	@enum		AudioUnitEventType
	
	@abstract	Types of Audio Unit Events.
	
	@constant	kAudioUnitEvent_ParameterValueChange
					The event is a change to a parameter value
	@constant	kAudioUnitEvent_BeginParameterChangeGesture
					The event signifies a gesture (e.g. mouse-down) beginning a potential series of
					related parameter value change events.
	@constant	kAudioUnitEvent_EndParameterChangeGesture
					The event signifies a gesture (e.g. mouse-up) ending a series of related
					parameter value change events.
	@constant	kAudioUnitEvent_PropertyChange
					The event is a change to a property value.
*/
enum {	// typedef UInt32 AudioUnitEventType
	kAudioUnitEvent_ParameterValueChange		= 0,
	kAudioUnitEvent_BeginParameterChangeGesture = 1,
	kAudioUnitEvent_EndParameterChangeGesture	= 2,
	kAudioUnitEvent_PropertyChange				= 3
};
typedef UInt32 AudioUnitEventType;

/* ============================================================================= */

/*!
	@typedef		AUParameterListenerRef
	@abstract		An object which receives notifications of Audio Unit parameter value changes.
	@discussion
*/
typedef struct AUListenerBase *AUParameterListenerRef;
	// opaque
	// old-style listener, may not be passed to new functions

/*!
	@typedef		AUEventListenerRef
	@abstract		An object which receives Audio Unit events.
	@discussion		An AUEventListenerRef may be passed to API's taking an AUEventListenerRef
					as an argument.
*/
typedef AUParameterListenerRef AUEventListenerRef;
	// new-style listener, can be passed to both old and new functions

/*!
	@struct		AudioUnitEvent
	@abstract	Describes a change to an Audio Unit's state.
	@field		mEventType
		The type of event.
	@field		mArgument
		Specifies the parameter or property which has changed.
*/	
typedef struct AudioUnitEvent {
	AudioUnitEventType					mEventType;
	union {
		AudioUnitParameter	mParameter;	// for parameter value change, begin and end gesture
		AudioUnitProperty	mProperty;	// for kAudioUnitEvent_PropertyChange
	}									mArgument;
} AudioUnitEvent;


/*!
	@typedef	AUParameterListenerProc
	@abstract	A function called when a parameter value changes.
	@param	inRefCon
				The value passed to AUListenerCreate when the callback function was installed.
	@param	inObject
				The object which generated the parameter change.
	@param	inParameter
				Signifies the parameter whose value changed.
	@param	inValue
				The parameter's new value.
*/
typedef void (*AUParameterListenerProc)(	void *						inRefCon,
											void *						inObject,
											const AudioUnitParameter *	inParameter,
											AudioUnitParameterValue		inValue);

/*!
	@typedef	AUParameterListenerProc
	@abstract	A function called when an Audio Unit event occurs.
	@param	inCallbackRefCon
				The value passed to AUListenerCreate when the callback function was installed.
	@param	inObject
				The object which generated the parameter change.
	@param	inEvent
				The event which occurred.
	@param	inEventHostTime
				The host time at which the event occurred.
	@param	inParameterValue
				If the event is parameter change, the parameter's new value (otherwise, undefined).
*/
typedef void (*AUEventListenerProc)(void *						inCallbackRefCon,
									void *						inObject,
									const AudioUnitEvent *		inEvent,
									UInt64						inEventHostTime,
									AudioUnitParameterValue		inParameterValue);

/* ============================================================================= */

/*!
    @functiongroup  AUListener
*/

/*!
	@function	AUListenerCreate
	@abstract	Create an object for fielding notifications when AudioUnit parameter values change.
	@param		inProc
					Function called when the parameter's value changes.
	@param		inRefCon
					A reference value for the use of the callback function.
	@param		inRunLoop
					The run loop on which the callback is called.  If NULL,
					CFRunLoopGetCurrent() is used.
	@param		inRunLoopMode
					The run loop mode in which the callback's underlying run loop source will be
					attached.  If NULL, kCFRunLoopDefaultMode is used.
	@param		inNotificationInterval
					The minimum time interval, in seconds, at which the callback will be called.
					If multiple parameter value changes occur within this time interval, the
					listener will only receive a notification for the last value change that
					occurred before the callback.  If inNotificationInterval is 0, the inRunLoop
					and inRunLoopMode arguments are ignored, and the callback will be issued
					immediately, on the thread on which the parameter was changed.
	@param		outListener
					On succcessful return, an AUParameterListenerRef.
	@discussion	
		Note that only parameter changes issued through AUParameterSet will generate
		notifications to listeners; thus, in most cases, AudioUnit clients should use
		AUParameterSet in preference to AudioUnitSetParameterValue.
*/
extern OSStatus
AUListenerCreate(					AUParameterListenerProc			inProc,
									void *							inRefCon,
									CFRunLoopRef					inRunLoop,
									CFStringRef						inRunLoopMode,
									Float32							inNotificationInterval,
									AUParameterListenerRef *		outListener)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	AUListenerDispose
	@abstract	Dispose a parameter listener object.
	@param		inListener
					The parameter listener to dispose.
	@discussion	
*/
extern OSStatus
AUListenerDispose(					AUParameterListenerRef			inListener)		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	AUListenerAddParameter
	@abstract	Connect a parameter to a listener.
	@param		inListener
					The parameter listener which will receive the callback.
	@param		inObject
					The object which is interested in the value of the parameter.  This will be
					passed as the inObject parameter to the listener callback function when the
					parameter changes.
	@param		inParameter
					The parameter whose value changes are to generate callbacks.
	@discussion	
		Associates an arbitrary object (often a user interface widget) with an
		AudioUnitParameter, and delivers notifications to the specified listener, telling it
		that the object needs to be informed of the parameter's value change.
*/
extern OSStatus
AUListenerAddParameter(				AUParameterListenerRef			inListener, 
									void *							inObject,
									const AudioUnitParameter *		inParameter)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	AUListenerRemoveParameter
	@abstract	Remove a parameter/listener connection.
	@param		inListener
					The parameter listener to stop receiving callbacks.
	@param		inObject
					The object which is no longer interested in the value of the parameter.
	@param		inParameter
					The parameter whose value changes are to stop generating callbacks.
	@discussion	
*/
extern OSStatus
AUListenerRemoveParameter(			AUParameterListenerRef			inListener, 
									void *							inObject, 
									const AudioUnitParameter *		inParameter)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*!
	@function	AUParameterSet
	@abstract	Set an AudioUnit parameter value and notify listeners.
	@param		inListener
					A parameter listener generating the change and which does not want to
					receive a callback as a result of it. May be NULL.
	@param		inObject
					The object generating the change and which does not want to receive a
					callback as a result of it. NULL is treated specially when inListener is
					non-null; it signifies that none of the specified listener's objects will
					receive notifications.
	@param		inParameter
					The parameter being changed.
	@param		inValue
					The new value of the parameter.
	@discussion	
		Calls AudioUnitSetParameter, and performs/schedules notification callbacks to all
		parameter listeners, for that parameter -- except that no callback will be generated to
		the inListener/inObject pair.
*/
extern OSStatus
AUParameterSet(						AUParameterListenerRef			inSendingListener, 
									void *							inSendingObject,
									const AudioUnitParameter *		inParameter,
									AudioUnitParameterValue			inValue,
									UInt32							inBufferOffsetInFrames)
																					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	AUParameterListenerNotify
	@abstract	Notify listeners of a past parameter change.
	@param		inListener
					A parameter listener generating the change and which does not want to
					receive a callback as a result of it. May be NULL.
	@param		inObject
					The object generating the change and which does not want to receive a
					callback as a result of it. NULL is treated specially when inListener is
					non-null; it signifies that none of the specified listener's objects will
					receive notifications.
	@param		inParameter
					The parameter which was changed changed.
	@discussion	
		Performs and schedules the notification callbacks of AUParameterSet, without
		actually setting an AudioUnit parameter value.
		
		Clients scheduling ramped parameter changes to AudioUnits must make this call
		dynamically during playback in order for AudioUnitViews to be updated.  When the view's
		listener receives a notification, it will be passed the current value of the parameter.

		A special meaning is applied if the mParameterID value of inParameter is equal to
		kAUParameterListener_AnyParameter. In this case, ANY listener for ANY parameter value
		changes on the specified AudioUnit will be notified of the current value of that
		parameter.
*/
extern OSStatus
AUParameterListenerNotify(			AUParameterListenerRef			inSendingListener,
									void *							inSendingObject,
									const AudioUnitParameter *		inParameter)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* ============================================================================= */

/*!
    @functiongroup  AUEventListener
*/

/*!
	@function	AUEventListenerCreate
	@abstract	Creates an Audio Unit event listener.
	@param		inProc
					Function called when an event occurs.
	@param		inCallbackRefCon
					A reference value for the use of the callback function.
	@param		inRunLoop
					The run loop on which the callback is called.  If NULL,
					CFRunLoopGetCurrent() is used.
	@param		inRunLoopMode
					The run loop mode in which the callback's underlying run loop source will be
					attached.  If NULL, kCFRunLoopDefaultMode is used.
	@param		inNotificationInterval
					The minimum time interval, in seconds, at which the callback will be called.
	@param		inValueChangeGranularity
					Determines how parameter value changes occuring within this interval are
					queued; when an event follows a previous one by a smaller time interval than
					the granularity, then the listener will only be notified for the second
					parameter change.
	@param		outListener
					On succcessful return, an AUEventListenerRef.
	
	@discussion
		AUEventListener is a specialization of AUParameterListener; use AUListenerDispose to
		dispose of an AUEventListener. You may use AUListenerAddParameter and
		AUListenerRemoveParameter with AUEventListerRef's, in addition to
		AUEventListenerAddEventType / AUEventListenerRemoveEventType.

		Some examples illustrating inNotificationInterval and inValueChangeGranularity:

		[1] a UI receiver: inNotificationInterval = 100 ms, inValueChangeGranularity = 100 ms.
			User interfaces almost never care about previous values, only the current one,
			and don't wish to perform redraws too often.

		[2] An automation recorder: inNotificationInterval = 200 ms, inValueChangeGranularity = 10 ms.
			Automation systems typically wish to record events with a high degree of timing precision,
			but do not need to be woken up for each event.
		
		In case [1], the listener will be called within 100 ms (the notification interval) of an
		event. It will only receive one notification for any number of value changes to the
		parameter concerned, occurring within a 100 ms window (the granularity).

		In case [2], the listener will be received within 200 ms (the notification interval) of
		an event It can receive more than one notification per parameter, for the last of each
		group of value changes occurring within a 10 ms window (the granularity).

		In both cases, thread scheduling latencies may result in more events being delivered to
		the listener callback than the theoretical maximum (notification interval /
		granularity).
*/
extern OSStatus
AUEventListenerCreate(				AUEventListenerProc			inProc,
									void *						inCallbackRefCon,
									CFRunLoopRef				inRunLoop,
									CFStringRef					inRunLoopMode,
									Float32						inNotificationInterval,		// seconds
									Float32						inValueChangeGranularity,	// seconds
									AUEventListenerRef *		outListener)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*!
	@function   AUEventListenerAddEventType
	@abstract   Begin delivering a particular type of events to a listener.
	@param		inListener
					The parameter listener which will receive the events.
	@param		inObject
					The object which is interested in the value of the parameter.  This will be
					passed as the inObject parameter to the listener callback function when the
					parameter changes.
	@param		inEvent
					The type of event to listen for.
	@result		An OSStatus error code.
*/
extern OSStatus
AUEventListenerAddEventType(		AUEventListenerRef			inListener,
									void *						inObject,
									const AudioUnitEvent *		inEvent)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	
/*!
	@function   AUEventListenerRemoveEventType
	@abstract   Stop delivering a particular type of events to a listener.
	@param		inListener
					The parameter listener to stop receiving events.
	@param		inObject
					The object which is no longer interested in the value of the parameter.
	@param		inEvent
					The type of event to stop listening for.
	@result		An OSStatus error code.
*/
extern OSStatus
AUEventListenerRemoveEventType(		AUEventListenerRef			inListener,
									void *						inObject,
									const AudioUnitEvent *		inEvent)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;			

/*!
	@function   AUEventListenerNotify
	@abstract   Deliver an AudioUnitEvent to all listeners registered to receive it.
	@param		inSendingListener
					A parameter listener generating the change and which does not want to
					receive a callback as a result of it. May be NULL.
	@param		inSendingObject
					The object generating the change and which does not want to receive a
					callback as a result of it. NULL is treated specially when inListener is
					non-null; it signifies that none of the specified listener's objects will
					receive notifications.
	@param		inEvent
					The event to be delivered.
	@result		An OSStatus error code.
*/
extern OSStatus
AUEventListenerNotify(				AUEventListenerRef			inSendingListener,
									void *						inSendingObject,
									const AudioUnitEvent *		inEvent)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
									
/* ============================================================================= */

/*!
    @functiongroup  Parameter value utilities
*/


/*!
	@function	AUParameterValueFromLinear
	@abstract	Converts a linear value to a parameter value according to the parameter's units.
	
	@param		inLinearValue
					The linear value (0.0-1.0) to convert.
	@param		inParameter
					The parameter, including its Audio Unit, that will define the conversion of
					the supplied linear value to a value that is natural to that parameter.
	@result
				The converted parameter value, in the parameter's natural units.
	@discussion	
*/
extern AudioUnitParameterValue
AUParameterValueFromLinear(			Float32						inLinearValue,		// 0-1
									const AudioUnitParameter *	inParameter)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*!
	@function	AUParameterValueToLinear
	@abstract	Converts a parameter value to a linear value according to the parameter's units.
	
	@param		inParameterValue
					The value in the natural units of the specified parameter.
		
	@param		inParameter
					The parameter, including its Audio Unit, that will define the conversion of
					the supplied parameter value to a corresponding linear value.
	@result
				A number 0.0-1.0.
	@discussion	
*/
extern Float32
AUParameterValueToLinear(			AudioUnitParameterValue		inParameterValue,
									const AudioUnitParameter *	inParameter)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
										// returns 0-1

/*!
	@function	AUParameterFormatValue
	@abstract	Format a parameter value into a string.
	@param		inParameterValue
					The parameter value to be formatted.
	@param		inParameter
					The Audio Unit, scope, element, and parameter whose value this is.
	@param		inTextBuffer
					The character array to receive the formatted text.  Should be at least 32
					characters.
	@param		inDigits
					The resolution of the string (see example above).
	@result
				<tt>inTextBuffer</tt>
	@discussion	
		Formats a floating point value into a string.  Computes a power of 10 to which the value
		will be rounded and displayed as follows:  if the the parameter is logarithmic (Hertz),
		the number of significant digits is inDigits - pow10(inParameterValue) + 1.  Otherwise,
		it is inDigits - pow10(maxValue - minValue) + 1.

	    Example for inDigits=3:
<pre>
	    pow10   range           digits after decimal place display
	    -2      .0100-.0999     4
	    -1      .100-.999       3
	    0       1.00-9.99       2
	    1       10.0-99.9       1
	    2       100-999         0
	    3       1000-9990       -1
	    4       10000-99900     -2</pre>
*/								
extern char *
AUParameterFormatValue(				Float64						inParameterValue,
									const AudioUnitParameter *	inParameter,
									char *						inTextBuffer,
									UInt32						inDigits)		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#ifdef __cplusplus
}
#endif


#endif

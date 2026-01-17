/*=============================================================================
	AudioUnitUtilities.h
		
	Copyright (c) 2002-2004 Apple Computer, Inc.  All Rights Reserved
=============================================================================*/

// Utilities for use of AudioUnit clients - higher-level functions.


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

enum {
	kAUParameterListener_AnyParameter = 0xFFFFFFFF
};

typedef struct AUListenerBase *AUParameterListenerRef;	// opaque
	// old-style listener, may not be passed to new functions
typedef AUParameterListenerRef AUEventListenerRef;
	// new-style listener, can be passed to both old and new functions

typedef void (*AUParameterListenerProc)(	void *						inRefCon,
											void *						inObject,
											const AudioUnitParameter *	inParameter,
											Float32						inValue);

/* ============================================================================= */

extern OSStatus
AUListenerCreate(					AUParameterListenerProc			inProc,
									void *							inRefCon,
									CFRunLoopRef					inRunLoop,
									CFStringRef						inRunLoopMode,
									Float32							inNotificationInterval,
									AUParameterListenerRef *		outListener)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

extern OSStatus
AUListenerDispose(					AUParameterListenerRef			inListener)		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

extern OSStatus
AUListenerAddParameter(				AUParameterListenerRef			inListener, 
									void *							inObject,
									const AudioUnitParameter *		inParameter)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

extern OSStatus
AUListenerRemoveParameter(			AUParameterListenerRef			inListener, 
									void *							inObject, 
									const AudioUnitParameter *		inParameter)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


extern OSStatus
AUParameterSet(						AUParameterListenerRef			inSendingListener, 
									void *							inSendingObject,
									const AudioUnitParameter *		inParameter,
									Float32							inValue,
									UInt32							inBufferOffsetInFrames)
																					AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


extern OSStatus
AUParameterListenerNotify(			AUParameterListenerRef			inSendingListener,
									void *							inSendingObject,
									const AudioUnitParameter *		inParameter)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/* ============================================================================= */

/*
	The AUEventListener* API's extend the above AUParameterListener* API's above
	by adding the semantic of events other than parameter changes, which are
	delivered serially to the listener interspersed with parameter changes,
	preserving the time order of the events and parameter changes.
*/

typedef UInt32 AudioUnitEventType;

enum {
	kAudioUnitEvent_ParameterValueChange		= 0,
	kAudioUnitEvent_BeginParameterChangeGesture = 1,
	kAudioUnitEvent_EndParameterChangeGesture	= 2,
	kAudioUnitEvent_PropertyChange				= 3
};

typedef struct AudioUnitEvent {
	AudioUnitEventType					mEventType;
	union {
		AudioUnitParameter	mParameter;		// for parameter value change, begin and end gesture
		AudioUnitProperty	mProperty;		// for using this mechanism for property change notifications
	}									mArgument;
} AudioUnitEvent;

typedef void (*AUEventListenerProc)(void *						inCallbackRefCon,
									void *						inObject,
									const AudioUnitEvent *		inEvent,
									UInt64						inEventHostTime,
									Float32						inParameterValue);

extern OSStatus
AUEventListenerCreate(				AUEventListenerProc			inProc,
									void *						inCallbackRefCon,
									CFRunLoopRef				inRunLoop,
									CFStringRef					inRunLoopMode,
									Float32						inNotificationInterval,		// seconds
									Float32						inValueChangeGranularity,	// seconds
									AUEventListenerRef *		outListener)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// use AUListenerDispose
	// may use AUListenerAddParameter and AUListenerRemoveParameter with AUEventListerRef's,
	// in addition to AUEventListenerAddEventType / AUEventListenerRemoveEventType

	// inNotificationInterval: this is the minimum time interval at which the receiving runloop will
	//		be woken up and the event listener proc called
	// inValueChangeGranularity: determines how parameter value changes occuring within this interval
	//		are queued; when an event follows a previous one by a smaller time interval than
	//		the granularity, then the listener will only be notified for the second parameter change.

	// Examples:
	//	[1] a UI receiver: inNotificationInterval 100 ms, inValueChangeGranularity 100 ms
	//		User interfaces almost never care about previous values, only the current one,
	//		and don't wish to perform redraws too often.
	//	[2] an automation recorder: inNotificationInterval 200 ms, inValueChangeGranularity 10 ms
	//		Automation systems typically wish to record events with a high degree of timing precision,
	//		but do not need to be woken up for each event.

	// In case [1], the listener will be called within 100 ms (the notification interval) of an event.
	// It will only receive one notification for any number of value 
	// changes to the parameter concerned, occurring within a 100 ms window (the granularity).

	// In case [2], the listener will be received within 200 ms (the notification interval) of an event
	// It can receive more than one notification per parameter,
	// for the last of each group of value changes occurring within a 10 ms window (the granularity).

	// In both cases, thread scheduling latencies may result in more events being delivered to the listener
	// callback than the theoretical maximum (notification interval / granularity).

extern OSStatus
AUEventListenerAddEventType(		AUEventListenerRef			inListener,
									void *						inObject,
									const AudioUnitEvent *		inEvent)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// inEvent can specify creation of a listener for
	//		- a parameter change
	//		- a parameter change begin/end gesture
	//		- a property change
	// i.e., all types of AudioUnitEvents
	
extern OSStatus
AUEventListenerRemoveEventType(		AUEventListenerRef			inListener,
									void *						inObject,
									const AudioUnitEvent *		inEvent)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;			

extern OSStatus
AUEventListenerNotify(				AUEventListenerRef			inSendingListener,
									void *						inSendingObject,
									const AudioUnitEvent *		inEvent)		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
									
/* ============================================================================= */

extern Float32
AUParameterValueFromLinear(			Float32						inLinearValue,		// 0-1
									const AudioUnitParameter *	inParameter)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

extern Float32
AUParameterValueToLinear(			Float32						inParameterValue,
									const AudioUnitParameter *	inParameter)	AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;
										// returns 0-1
									
extern char *
AUParameterFormatValue(				double						inParameterValue,
									const AudioUnitParameter *	inParameter,
									char *						inTextBuffer,
									UInt32						inDigits)		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#ifdef __cplusplus
}
#endif


#endif

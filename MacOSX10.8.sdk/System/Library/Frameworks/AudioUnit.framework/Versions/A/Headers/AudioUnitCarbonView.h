/*
     File:       AudioUnitCarbonView.h
 
     Contains:   AudioUnitCarbonView Interfaces
 
     Copyright:  © 2002-2008 by Apple, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AUDIOUNITCARBONVIEW__
#define __AUDIOUNITCARBONVIEW__

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <Carbon/Carbon.h>
	#include <AudioUnit/AUComponent.h>
#else
	#include <MacWindows.h>
	#include <Controls.h>
	#include <AUComponent.h>
#endif

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_IMPORT
#pragma import on
#endif

#if PRAGMA_STRUCT_ALIGN
	#pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
	#pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
	#pragma pack(2)
#endif

/*!
	@header		AudioUnitCarbonView
	@abstract	This file defines interfaces for creating and event handling in carbon-based views of Audio Units.
*/

/*!
	@typedef	AudioUnitCarbonView
	@abstract	An audio unit Carbon view is of type ComponentInstance, defined by the Component Manager.
*/
typedef ComponentInstance			   AudioUnitCarbonView;

/*!
	@enum		Carbon view component types and subtypes
	@constant	kAudioUnitCarbonViewComponentType
					The four char-code type of a carbon-based view component
	@constant	kAUCarbonViewSubType_Generic
					The four char-code subtype of a carbon-based view component
*/
enum
{
	kAudioUnitCarbonViewComponentType   = 'auvw',
	kAUCarbonViewSubType_Generic		= 'gnrc'
};


/*!
	@enum		Carbon view events
	@constant	kAudioUnitCarbonViewEvent_MouseDownInControl
					The event type indicating that the mouse is pressed in a control
	@constant	kAudioUnitCarbonViewEvent_MouseUpInControl
					The event type indicating that the mouse is released in a control
*/
enum
{
	kAudioUnitCarbonViewEvent_MouseDownInControl	= 0,
	kAudioUnitCarbonViewEvent_MouseUpInControl		= 1
};

/*!
	@typedef	AudioUnitcarbViewEventID
	@abstract	Specifies an event passed to an AudioUnitCarbonViewEventListener callback.
*/
typedef SInt32						  AudioUnitCarbonViewEventID;

/*!
	@typedef	AudioUnitCarbonViewEventListener
	@abstract	Defines a callback function that is called when certain events occur in an
				Audio Unit Carbon view, such as mouse-down and up events on a control.
				
	@param		inUserData
					A user-defined pointer that was passed to an AudioUnitCarbonViewSetEventListener callback.
	@param		inView
					The Audio unit Carbon vIew that generated the message.
	@param		inParameter
					The parameter associated with the control generating the message.
	@param		inEvent
					The type of event, as listed in Audio unit Carbon view events.
	@param		inEventParam
					Further information about the event, dependent on its type.
*/
#ifndef __LP64__
typedef void
(*AudioUnitCarbonViewEventListener)(	void *						inUserData,
										AudioUnitCarbonView			inView,
										const AudioUnitParameter *	inParameter,
										AudioUnitCarbonViewEventID	inEvent,
										const void *				inEventParam);
#endif

/*!
	@function	AudioUnitCarbonViewCreate
	@abstract	A callback that tells an Audio unit Carbon view to open its user interface (user pane).
	@discussion	The host application specifies the audio unit which the view is to control. The host 
				also provides the window, parent control, and rectangle into which the Audio unit 
				Carbon view component (of type AudioUnitCarbonView) is to create itself.

				The host application is responsible for closing the component (by calling the
				CloseComponent function) before closing its window.
				
	@param		inView
					The view component instance.
	@param		inAudioUnit
					The audio unit component instance which the view is to control.
	@param		inWindow
					The Carbon window in which the user interface is to be opened.
	@param		inParentControl
					The Carbon control into which the user interface is to be embedded. 
					(This is typically the window's root control).
	@param		inLocation
					The host application's requested location for the view. The view should 
					always create itself at the specified location.
	@param		inSize
					The host application's requested size for the view. The view may choose a 
					different size for itself. The actual dimensions of the view are described 
					by the value of the outControl parameter.
	@param		outControl
					The Carbon control which contains the entire user interface for the view.
*/
extern OSStatus
AudioUnitCarbonViewCreate(	  AudioUnitCarbonView   inView,
							  AudioUnit             inAudioUnit,
							  WindowRef             inWindow,
							  ControlRef            inParentControl,
							  const Float32Point *  inLocation,
							  const Float32Point *  inSize,
							  ControlRef *          outControl)				__OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_NA);

/*!
	@function	AudioUnitCarbonViewSetEventListener
	@abstract	Add an event listener to the carbon view.
	@deprecated	in Mac OS X version 10.4
	@discussion	Use the AUEventListener functions in <AudioToolbox/AudioUnitUtilities.h> instead.
	
	@param		inView
					The Carbon view component instance.
	@param		inCallback
					The event listener callback function.
	@param		inUserData
					A user data pointer passed to the callback.
*/
#ifndef __LP64__
extern OSStatus
AudioUnitCarbonViewSetEventListener(	AudioUnitCarbonView                inView,
										AudioUnitCarbonViewEventListener   inCallback,
										void *                             inUserData)
																			__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_2,__MAC_10_4, __IPHONE_NA, __IPHONE_NA);
#endif

/*!
	@enum		Selectors for component calls
	@constant	kAudioUnitCarbonViewRange
					Range of selectors
	@constant	kAudioUnitCarbonViewCreateSelect
					Selector for creating the carbon view
	@constant	kAudioUnitCarbonViewSetEventListenerSelect
					Selector for setting the event listener callback
*/
enum
{
	kAudioUnitCarbonViewRange                  = 0x0300,	// range of selectors
    kAudioUnitCarbonViewCreateSelect           = 0x0301,
    kAudioUnitCarbonViewSetEventListenerSelect = 0x0302
};


#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef PRAGMA_IMPORT_OFF
#pragma import off
#elif PRAGMA_IMPORT
#pragma import reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AUDIOUNITCARBONVIEW__ */


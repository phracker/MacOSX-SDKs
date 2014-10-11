/*
     File:       AudioUnitCarbonView.h
 
     Contains:   AudioUnitCarbonView Interfaces
 
     Version:    Technology: Mac OS X
                 Release:    Mac OS X
 
     Copyright:  © 2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AUDIOUNITCARBONVIEW__
#define __AUDIOUNITCARBONVIEW__

#include <Carbon/Carbon.h>
#include <AudioUnit/AUComponent.h>


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

/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   ranges
*/

enum {
  kAudioUnitCarbonViewRange     = 0x0300
};

typedef ComponentInstance               AudioUnitCarbonView;
/*
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   AudioUnit component types and subtypes
*/
enum {
  kAudioUnitCarbonViewComponentType = FOUR_CHAR_CODE('auvw'),
  kAUCarbonViewSubType_Generic  = FOUR_CHAR_CODE('gnrc')
};

enum {
  kAudioUnitCarbonViewEvent_MouseDownInControl = 0,
  kAudioUnitCarbonViewEvent_MouseUpInControl = 1
};


/*
 *  AudioUnitCarbonViewEventID
 *  
 *  Discussion:
 *    Specifies an event passed to an AudioUnitCarbonViewEventListener.
 */
typedef SInt32                          AudioUnitCarbonViewEventID;

/*
 *  AudioUnitCarbonViewEventListener
 *  
 *  Discussion:
 *    This callback function is called when certain events occur in an
 *    AudioUnitCarbonView, such as mouse-down and up events on a
 *    control.
 *  
 *  Parameters:
 *    
 *    inUserData:
 *      User-defined pointer that was passed to
 *      AudioUnitCarbonViewSetEventListener.
 *    
 *    inView:
 *      The AudioUnitCarbonVIew generating the message.
 *    
 *    inParameter:
 *      The parameter associated with the control generating the
 *      message.
 *    
 *    inEvent:
 *      The type of event.
 *    
 *    inEventParam:
 *      Further information about the event, dependent on its type.
 */
typedef CALLBACK_API_C( void , AudioUnitCarbonViewEventListener )(void *inUserData, AudioUnitCarbonView inView, const AudioUnitParameter *inParameter, AudioUnitCarbonViewEventID inEvent, const void *inEventParam);
/*
 *  AudioUnitCarbonViewCreate()
 *  
 *  Summary:
 *    Tells an AudioUnitCarbonView to open its user interface (user
 *    pane).
 *  
 *  Discussion:
 *    The host application specifies the AudioUnit which the view is to
 *    control, and provides a window, parent control, and rectangle
 *    into which the AudioUnitCarbonView component is to create itself.
 *    The host application is responsible for closing the
 *    AudioUnitCarbonView component (via CloseComponent) before closing
 *    its window.
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view component instance.
 *    
 *    inAudioUnit:
 *      The AudioUnit component instance which the view is to control.
 *    
 *    inWindow:
 *      The Carbon window in which the user interface is to be opened.
 *    
 *    inParentControl:
 *      The Carbon control into which the user interface is to be
 *      embedded (often but not necessarily the window's root control).
 *    
 *    inLocation:
 *      The host application's requested location for the view. The
 *      view should always create itself at the specified location,
 *    
 *    inSize:
 *      The host application's requested size for the view. The view
 *      may choose a different size for itself, determined by the
 *      dimensions of outControl.
 *    
 *    outControl:
 *      The Carbon control which contains the entire user interface.
 *  
 */
EXTERN_API( ComponentResult )
AudioUnitCarbonViewCreate(
  AudioUnitCarbonView   inView,
  AudioUnit             inAudioUnit,
  WindowRef             inWindow,
  ControlRef            inParentControl,
  const Float32Point *  inLocation,
  const Float32Point *  inSize,
  ControlRef *          outControl)                           FIVEWORDINLINE(0x2F3C, 0x0018, 0x0301, 0x7000, 0xA82A);


/*
 *  AudioUnitCarbonViewSetEventListener()
 *  
 *  Summary:
 *    Installs an event listener in an AudioUnitCarbonView.
 *  
 *  Parameters:
 *    
 *    inView:
 *      The view component instance.
 *    
 *    inCallback:
 *      The event listener callback function
 *    
 *    inUserData:
 *      A user data pointer passed to the callback
 *  
 */
EXTERN_API( ComponentResult )
AudioUnitCarbonViewSetEventListener(
  AudioUnitCarbonView                inView,
  AudioUnitCarbonViewEventListener   inCallback,
  void *                             inUserData)              FIVEWORDINLINE(0x2F3C, 0x0008, 0x0302, 0x7000, 0xA82A);






/* UPP call backs */

/* selectors for component calls */
enum {
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


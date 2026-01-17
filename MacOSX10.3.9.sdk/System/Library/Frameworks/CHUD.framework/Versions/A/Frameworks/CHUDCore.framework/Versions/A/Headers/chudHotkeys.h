/*
 * Copyright (c) 2002-2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
 
#ifndef CHUD_HOTKEYS_H
#define CHUD_HOTKEYS_H

/*!
  @header CHUD Hotkey Functions Macros and constants
  Use the CHUD Hot-keys to set up global key combinations that will send input to a performance
  monitor program, even when the program does not have keyboard focus, of if it is minimized.
  Hotkeys DO NOT work over remote (SSH/telnet) connections, nor will they function if the system
  running the performance monitor application is not logged into a user account.
*/

#include <CHUDCore/chudCtrl.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
    @typedef chudHotkeyCallbackFunc
    @discussion The definition of a simple function that returns the integer identifier specified when a hotkey combination is established with chudAddHotkey
    @param ident an integer identifier passed back used to determine which hotkey combination has been activated
    @result void
*/
typedef void (*chudHotkeyCallbackFunc)(unsigned long ident);

/*!
 @function  chudAddHotkey
 @discussion Use this function to assign a keyboard shortcut (modifier key or keys, and a normal key)
 that will activate the callback installed with chudAddHotkeyCallback. chudAddHotkeyCallback must be 
 called prior to calling this function, or else chudAddHotkey will fail and return a chudNoHotkeyCallback
 status.
 @param ident unsigned long a unique identifier
 @param mods unsigned long modifier keys, one or more of chudShiftKey, chudControlKey, 
 chudOptionKey, chudCommandKey can be OR'd together.
 @param key unsigned long ASCII value of the normal key to be pressed in combination with the modifier key(s).
 @result chud_status one of:  chudNoHotkeyCallback, chudAddHotkeyFailed, chudInvalidModifierKey, chudSuccess
*/
int	chudAddHotkey( unsigned long ident, unsigned long mods, unsigned long key );
/*!
 @function  chudAddCocoaHotkey
 @discussion Use this function to assign a keyboard shortcut (modifier key or keys, and a normal key)
 that will activate the callback installed with chudAddCocoaHotkeyCallback. chudAddCocoaHotkeyCallback must be 
 called prior to calling this function, or else chudAddCocoaHotkey will fail and return a chudNoHotkeyCallback
 status. see chudAddCocoaHotkeyCallback for more details.
 @param ident unsigned long a unique identifier
 @param mods unsigned long modifier keys, one or more of chudShiftKey, chudControlKey, 
 chudOptionKey, chudCommandKey can be OR'd together.
 @param key unsigned long ASCII value of the normal key to be pressed in combination with the modifier key(s).
 @result chud_status one of:  chudNoHotkeyCallback, chudAddHotkeyFailed, chudInvalidModifierKey, chudSuccess
*/
int	chudAddCocoaHotkey( unsigned long ident, unsigned long mods, unsigned long key );
/*!
 @function  chudRemoveHotkey
 @discussion Use this function to release a keyboard shortcut (modifier key or keys, and a normal key)
 @param ident the identifying value specified when the hot key was bound, see chudAddHotKey, and chudAddCocoaHotkey.
 @result chud_status one of:  chudRemoveHotkeyFailed, or chudSuccess.
*/
int	chudRemoveHotkey( unsigned long ident );

/*!
 @function  chudAddHotkeyCallback
 @discussion Add a hotkey callback function and enable the global hot key facility. 
 This function must be called prior to calling chudAddHotkey. A special listener thread is 
 started and when hot key events are received, the listener thread calls the function 
 specified as the argument to this function. If the listener thread can't be started the CHUD status
 value will be set to chudFailure, and the function returns a NULL pointer.
 Here's an example:
 
 ...
 
 void localHotkeyCallback( unsigned long ident ); //the callback functionality is app-specific
 
 ...
 
 chudAddHotkeyCallback(localHotkeyCallback);
 
 addHkeyStat = chudAddHotkey(0x6, chudControlKey, 27); //ctrl+esc (27 ascii value);
 
 ...
 
 @param chudHotkeyCallbackFunc void (*chudHotkeyCallbackFunc)(unsigned long ident) 
 @result listener thread ID (a pointer to a pthread_t)
*/
unsigned long	chudAddHotkeyCallback( chudHotkeyCallbackFunc chudcbfunc );
/*!
 @function  chudAddCocoaHotkeyCallback
 @discussion Add a hotkey callback function and enable the global hot key facility. 
 This function must be called prior to calling chudAddCocoaHotkey. A special listener thread is 
 started and when hot key events are received, the listener thread calls the function 
 specified as the argument to this function. If the listener thread can't be started the CHUD status
 value will be set to chudFailure, and the function returns a NULL pointer. The main difference 
 from chudAddHotkeyCallback is that chudAddCocoaHotkeyCallback is designed to be compatible with 
 objective-C function protocols. Since the CHUD framework is 'C'-based, an objective-C object-instance 
 function that will be used as a callback needs to pass along its hidden arguments _instnc, and _commnd.
 These hidden arguments correspond to: an instance of the object that will receive the callback usually, 'self'
 and the command message that should be sent: usually, '_cmd'.
 
 here's an example:
 
     chudCallbackFunc mpbcf; //ansi 'c' function typedef in the chud framework
     
     //1-get the obj-c instance method to use for a callback
     
     mpbcf =(chudCallbackFunc) [MYControlObject methodForSelector: selector(MYActionFunction)];
     
     //2-assign the function as a chud/Cocoa callback
     
     chudAddCocoaHotkeyCallback(mpbcf,(unsigned long)self,(unsigned long)_cmd);
    
     //3-specify the hot-key combo that triggers the callback
        
     addHkeyStat = chudAddCocoaHotkey(0xA, chudControlKey, 27); //hotkey: cmd+esc (27 ascii value)


 @param chudCallbackFunc  see the chudCtrl.h documentation for the definition of a chudCallbackFunc function pointer 
 @result listener thread ID (a pointer to a pthread_t)
*/
void 	chudAddCocoaHotkeyCallback( chudCallbackFunc chudcbfunc, unsigned long  _instnc, unsigned long _commnd );
/*!
 @function  chudCocoaHotkey
 @discussion Call the pre-established cocoa hotkey callback. This function is used to 
 send the message (referenced by '_commnd') specified in the call to chudAddCocoaHotkeyCallback,
 to the object specified by chudAddCocoaHotkeyCallback (referenced by '_instnc')
 
 This function should be called by a 'sendEvent' member function in 
 a subclass of an NSApplication object of a Cocoa application. Here's a sample sendEvent routine:

 - (void)sendEvent:(NSEvent *)event {

    NSEventType eventType;

    short subtype;

    int e_data;

    eventType = [event type];
    

    if(eventType == NSSystemDefined) {

        subtype = [event subtype];

        if(subtype == kCGSEventSystemSubtypeHotKeyCombinationPressed) {

                [self activateIgnoringOtherApps:NO]; 

                e_data = [event data1];

                chudCocoaHotkey( e_data );

		return;

        }    

    }

    [super sendEvent:event];

 }

 @param e_id integer that was established when a hotkey was bound using chudAddCocoaHotkey
 (the 'ident' argument) 
 @result void
*/
void	chudCocoaHotkey( int e_id );
                                                
//Modifier Key Masks

/*!
    @defined chudControlKey
    @discussion This constant maps to either "Control" modifier key found on Apple Keyboards.
    Use it as individual argument, or combine, with a bitwise OR operation
    of the other modifiers, to establish the modifier key sequence use to trigger a global system hot key event 
*/
#define chudControlKey 	4L

/*!
    @defined chudOptionKey
    @discussion This constant maps to the "Option or Alt" modifier key found on Apple Keyboards.
    Use it as individual argument, or combine, with a bitwise OR operation
    of the other modifiers, to establish the modifier key sequence use to trigger a global system hot key event 
*/
#define chudOptionKey 	8L

/*!
    @defined chudCommandKey
    @discussion This constant maps to the "Command" modifier key found on Apple Keyboards.
    Use it as individual argument, or combine, with a bitwise OR operation
    of the other modifiers, to establish the modifier key sequence use to trigger a global system hot key event 
*/
#define chudCommandKey 	16L

/*! 
    @defined chudShiftKey
    @discussion This constant maps to either "Shift" modifier key found on Apple Keyboards.
    Use it as individual argument, or combine, with a bitwise OR operation
    of the other modifiers, to establish the modifier key sequence use to trigger a global system hot key event 
*/
#define chudShiftKey  	2L

#ifdef __cplusplus
}
#endif

#endif /* CHUD_HOTKEYS_H */

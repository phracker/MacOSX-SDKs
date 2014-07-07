/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
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
  @header CHUD Hotkey Macros and constants
  Use the CHUD Hotkeys to set up global key combinations that will send input to a performance
  monitor program, even when the program does not have keyboard focus, of if it is minimized.
  Hotkeys DO NOT work over remote (SSH/telnet) connections, nor will they function if the system
  running the performance monitor application is not logged into a user account.
*/

#include <CHUD/chudCtrl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*chudHotkeyCallbackFunc)(unsigned long ident);

int	chudAddHotkey( unsigned long ident, unsigned long mods, unsigned long key );
int	chudAddCocoaHotkey( unsigned long ident, unsigned long mods, unsigned long key );
int	chudRemoveHotkey( unsigned long ident );

unsigned long	chudAddHotkeyCallback( chudHotkeyCallbackFunc chudcbfunc );
void 	chudAddCocoaHotkeyCallback( chudCallbackFunc chudcbfunc, unsigned long  _instnc, unsigned long _commnd );
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

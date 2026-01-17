/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * "Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.0 (the 'License').  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License."
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/* Copyright (c) 1991 NeXT Computer, Inc.  All rights reserved.
 * 
 *	File:	achitecture/adb_kb_map.h
 *
 *	Definition of ADB keyboard scancode conversion mechanism.
 *
 * HISTORY
 * 07-Oct-91  Doug Mitchell at NeXT
 *	Created
 */
 
#ifndef	_ARCHITECTURE_ADB_KB_MAP_
#define _ARCHITECTURE_ADB_KB_MAP_

#include <architecture/ascii_codes.h>
#include <architecture/adb_bus.h>

/*
 * Each key down event maps to an unsigned short. The first 128 possible
 * mapped values are the ASCII character set. Values starting at 0x100 are 
 * non-printing keys, called "super keys", which are interpreted by
 * the keyboard driver directly. 
 */
typedef unsigned short 	adb_key_val_t;

#define ADB_SUPER_BASE		0x100
#define KEY_INVALID		ADB_SUPER_BASE		/* invalid */
#define ADB_RESET		(ADB_SUPER_BASE + 1)	/* apple reset */
#define ADB_POWER		ADB_RESET		/* NeXT power */
#define BRIGHT_UP		(ADB_SUPER_BASE + 2)
#define BRIGHT_DOWN		(ADB_SUPER_BASE + 3)
#define VOLUME_UP		(ADB_SUPER_BASE + 4)
#define VOLUME_DOWN		(ADB_SUPER_BASE + 5)
#define CURS_LEFT		(ADB_SUPER_BASE + 6)	/* cursor keys */
#define CURS_RIGHT		(ADB_SUPER_BASE + 7)
#define CURS_UP			(ADB_SUPER_BASE + 8)
#define CURS_DOWN		(ADB_SUPER_BASE + 9)
#define CTL_LEFT		(ADB_SUPER_BASE + 10)	/* control keys */
#define CTL_RIGHT		(ADB_SUPER_BASE + 11)
#define SHIFT_LEFT		(ADB_SUPER_BASE + 12)	/* shift keys */
#define SHIFT_RIGHT		(ADB_SUPER_BASE + 13)
#define OPTION_LEFT		(ADB_SUPER_BASE + 14) 	/* Apple: option */
#define OPTION_RIGHT		(ADB_SUPER_BASE + 15)
#define ALT_LEFT		OPTION_LEFT		/* NeXT: Alt */
#define ALT_RIGHT		OPTION_RIGHT
#define APPLE_LEFT		(ADB_SUPER_BASE + 16)	/* Apple: Apple */
#define APPLE_RIGHT		(ADB_SUPER_BASE + 17)	
#define CMD_LEFT		APPLE_LEFT		/* NeXT: command */
#define CMD_RIGHT		APPLE_RIGHT
#define CAPS_LOCK		(ADB_SUPER_BASE + 18)
#define ADB_CLEAR		(ADB_SUPER_BASE + 19)
#define KB_INTERRUPT		(ADB_SUPER_BASE + 20)

/*
 * ASCII values for one keycode. Mapping for one keyboard consists of 
 * an array of 128 of these, one for each possible scan code.
 */
typedef struct {
	adb_key_val_t normal;		// non meta ASCII values
	adb_key_val_t shift;
	adb_key_val_t control;
	adb_key_val_t control_shift;	
} adb_key_t;

/*
 * Mapping for a keyboard described by an adbHandlerId.
 * adb_kb_map.key points to an array of NUM_ADB_KEYCODES keycodes.
 */
#define NUM_ADB_KEYCODES	128

typedef struct {
	adbHandlerId		handler_id;
	const adb_key_t		*key;
} adb_kb_map_t;

#endif	/* _ARCHITECTURE_ADB_KB_MAP_ */
